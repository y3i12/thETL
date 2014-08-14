#include "LMDBKeyValueIO.h"

using namespace thetl;


LMDBKeyValueIO::LMDBKeyValueIO( LMDBKeyValueIO::key_index theKeyIndexes, bool asMultiMap ) :
	kvioInterface( theKeyIndexes ),
	m_env( 0 ),
	m_current( 0 ),
	m_end( 0 ),
	m_transaction( 0 ),
	m_binaryStream( m_binaryBuffer ),
	m_isMultimap( asMultiMap )
{
	mdb_env_create( &m_env );
} 

LMDBKeyValueIO::~LMDBKeyValueIO( void )
{
}

bool LMDBKeyValueIO::open( void )
{
	return
		mdb_env_open( m_env, sourceString( ), MDB_NOLOCK, 0 ) == 0 &&
		mdb_txn_begin( m_env, 0, 0, &m_transaction ) == 0 &&
		mdb_dbi_open( m_transaction, 0, ( m_isMultimap ? ( MDB_CREATE | MDB_DUPSORT ) : MDB_CREATE ), &m_db ) == 0 &&
		mdb_cursor_open( m_transaction, m_db, &m_current ) == 0 &&
		mdb_cursor_open( m_transaction, m_db, &m_end ) == 0;
}

void LMDBKeyValueIO::close( void )
{
	mdb_txn_commit( m_transaction );
	mdb_cursor_close( m_current );
	mdb_cursor_close( m_end );
	mdb_dbi_close( m_env, m_db );
	mdb_env_close( m_env );

	m_transaction = 0;
	m_current = 0;
	m_end = 0;
	m_db = 0;
}

bool LMDBKeyValueIO::isOpen( void )
{
	return m_transaction != 0;
}

void LMDBKeyValueIO::flush( void )
{
	mdb_txn_commit( m_transaction );
	mdb_dbi_close( m_env, m_db );

	mdb_txn_begin( m_env, 0, 0, &m_transaction );
	mdb_dbi_open( m_transaction, 0, ( m_isMultimap ? ( MDB_CREATE | MDB_DUPSORT ) : MDB_CREATE ), &m_db );

	mdb_cursor_renew( m_transaction, m_current );
	mdb_cursor_renew( m_transaction, m_end );
}


bool LMDBKeyValueIO::seek( int theTarget, dioInterface::SeekDirection theDirection )
{
	MDB_val v;
	MDB_cursor_op dir = theTarget < 0 ? MDB_PREV : MDB_NEXT;
	theTarget = abs( theTarget );

	switch ( theDirection )
	{
	case thetl::dioInterface::Beginning:
	mdb_cursor_get( m_current, &v, &v, MDB_FIRST );
	for ( int i = 0; i < theTarget; i++ )
	{
		mdb_cursor_get( m_current, &v, &v, dir );
	}
	break;

	case thetl::dioInterface::Current:
	for ( int i = 0; i < theTarget; i++ )
	{
		mdb_cursor_get( m_current, &v, &v, dir );
	}
	break;

	case thetl::dioInterface::End:
	mdb_cursor_get( m_current, &v, &v, MDB_LAST );
	for ( int i = 0; i < theTarget; i++ )
	{
		mdb_cursor_get( m_current, &v, &v, dir );
	}
	break;

	default:
	break;
	}

	return true;
}

bool LMDBKeyValueIO::find( const RecordData& theKey )
{
	m_binaryStream.rewind( );
	m_binaryStream << theKey;

	MDB_val theMDBKey;
	theMDBKey.mv_size = m_binaryStream.position( );
	theMDBKey.mv_data = reinterpret_cast< void* >( m_binaryStream.data( ) );

	if ( MDB_NOTFOUND == mdb_cursor_get( m_current, &theMDBKey, &theMDBKey, MDB_SET ) )
	{
		return false;
	}

	return true;
}

bool LMDBKeyValueIO::atEnd( void ) const
{
	MDB_val a;
	MDB_val ad;
	MDB_val b;
	MDB_val bd;
	
	if ( mdb_cursor_get( m_current, &a, &ad, MDB_GET_CURRENT ) )
	{
		return true;
	}

	if ( mdb_cursor_get( m_end, &b, &bd, MDB_GET_CURRENT ) )
	{
		return true;
	}

	if ( mdb_cmp( m_transaction, m_db, &a, &b ) )
	{
		return false;
	}

	if ( mdb_dcmp( m_transaction, m_db, &a, &b ) )
	{
		return false;
	}

	return true;
}

bool LMDBKeyValueIO::deserialize( RecordData& theOutput )
{
	return true;
}

bool LMDBKeyValueIO::serialize( const RecordData& theInput )
{

	m_binaryStream.rewind( );
	m_binaryStream << makeKey( theInput );

	BinaryStream::size_type theDataPosition = m_binaryStream.position( );
	m_binaryStream << theInput;

	MDB_val theKey;
	theKey.mv_data = reinterpret_cast< void* >( m_binaryStream.data( ) );
	theKey.mv_size = theDataPosition;

	MDB_val theData;
	theKey.mv_data = m_binaryStream.data( theDataPosition );
	theKey.mv_size = m_binaryStream.position() - theDataPosition;
	
	return 0 == mdb_put( m_transaction, m_db, &theKey, &theData, m_isMultimap ? 0 : MDB_NOOVERWRITE );
}

void LMDBKeyValueIO::resetCurrentCursor( void )
{
	MDB_val v;
	mdb_cursor_get( m_current, &v, &v, MDB_FIRST );
}

void LMDBKeyValueIO::setCurrentCursor( const RecordData& theKey )
{
	MDB_val v;
	v.mv_size = sizeof( void* );
	v.mv_data = ( void* )&theKey;
	mdb_cursor_get( m_current, &v, &v, MDB_SET_RANGE );
}

void LMDBKeyValueIO::resetEndCursor( void )
{
	MDB_val v;
	mdb_cursor_get( m_end, &v, &v, MDB_LAST );
}

void LMDBKeyValueIO::setEndCursor( const RecordData& theKey )
{
	MDB_val v;
	v.mv_size = sizeof( void* );
	v.mv_data = ( void* )&theKey;
	mdb_cursor_get( m_end, &v, &v, MDB_SET_RANGE );
}

bool LMDBKeyValueIO::eraseCurrent( void )
{
	return m_current && 0 == mdb_cursor_del( m_current, m_isMultimap ? MDB_NODUPDATA : 0 );
}

bool LMDBKeyValueIO::erase( const RecordData& theKey )
{
	return true;
}
