#include "LMDBKeyValueIO.h"

using namespace thetl;



LMDBKeyValueIO::LMDBKeyValueIO( LMDBKeyValueIO::key_index theKeyIndexes, bool asMultiMap ) :
	kvioInterface( theKeyIndexes ),
	m_env( 0 ),
	m_current( 0 ),
	m_end( 0 ),
	m_transaction( 0 ),
	m_isMultimap( asMultiMap )
{
	mdb_env_create( &m_env );
	MDB_env*									m_db;
	MDB_cursor*									m_current;
	MDB_cursor*									m_end;
	MDB_txn*									m_transaction;
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
	
	return true;
}

bool LMDBKeyValueIO::find( const RecordData& theKey )
{
	return true;
}

bool LMDBKeyValueIO::atEnd( void ) const
{
	return true;
}

bool LMDBKeyValueIO::deserialize( RecordData& theOutput )
{
	return true;
}

bool LMDBKeyValueIO::serialize( const RecordData& theInput )
{
	return true;
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
	mdb_cursor_get( m_current, &v, &v, MDB_SET );
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
