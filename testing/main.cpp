#include "csv_test.h"
#include "map_test.h"

#include <cstdlib>
#include "lmdb.h"
#include "BinaryStream.h"

//#define TEST_CSV_IO
//#define MAP_TEST_IO

int main( int c, char** v )
{
	int i = 1;
	thetl::BinaryStream::buffer mem_buff;
	thetl::BinaryStream bs( mem_buff );
	
	thetl::RecordData record_a;

	record_a.push_back( thetl::DataField( "string" ) );
	record_a.push_back( thetl::DataField( 10ll ) );
	record_a.push_back( thetl::DataField( 19.6 ) );

	bs << record_a;

	bs.rewind( );

	thetl::RecordData record_b;
	record_b.push_back( thetl::DataField( "" ) );
	record_b.push_back( thetl::DataField( 0ll ) );
	record_b.push_back( thetl::DataField( 0.0 ) );

	bs >> record_b;
	
	std::cout << record_b << std::endl;

	return 0;
	MDB_env*									m_env;
	MDB_dbi										m_db;
	MDB_cursor*									m_current;
	MDB_cursor*									m_end;
	MDB_txn*									m_transaction;
	mdb_env_create( &m_env );
	mdb_env_open( m_env, ".", MDB_NOLOCK, 0 );
	mdb_txn_begin( m_env, 0, 0, &m_transaction );
	mdb_dbi_open( m_transaction, 0, MDB_CREATE | MDB_DUPSORT, &m_db );

	long kv = 1;
	MDB_val key;
	key.mv_size = sizeof( long );
	key.mv_data = ( void* )&kv;
	
	long vv = -1;
	MDB_val val;
	val.mv_size = sizeof( long );
	val.mv_data = &vv;

	mdb_put( m_transaction, m_db, &key, &val, 0 );

	kv = 999;
	vv = -999;
	mdb_put( m_transaction, m_db, &key, &val, 0 );

	kv = 3;
	vv = -3;
	mdb_put( m_transaction, m_db, &key, &val, 0 );

	kv = 999;
	mdb_get( m_transaction, m_db, &key, &val );

	mdb_cursor_open( m_transaction, m_db, &m_current );
	mdb_cursor_open( m_transaction, m_db, &m_end );

	mdb_cursor_get( m_current, &key, &val, MDB_FIRST );

	mdb_txn_commit( m_transaction );
	mdb_dbi_close( m_env, m_db );

#if defined TEST_CSV_IO
	csv_test();
	system( "pause" );
#endif

#if defined MAP_TEST_IO
	map_test( );
	system( "pause" );
#endif
	return 0;
}