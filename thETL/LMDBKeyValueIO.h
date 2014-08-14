#if !defined __LMDB_KEY_VALUE_IO_H__
#define __LMDB_KEY_VALUE_IO_H__

#include "kvioInterface.h"
#include "lmdb.h"

namespace thetl
{
	class LMDBKeyValueIO : public kvioInterface
	{
	public:
		using										kvioInterface::key;
		using										kvioInterface::value;
		using										kvioInterface::key_index;

		LMDBKeyValueIO( key_index theKeyIndexes, bool asMultiMap );
		virtual ~LMDBKeyValueIO( void );

		virtual bool		open( void );
		virtual void		close( void );
		virtual bool		isOpen( void );
		virtual void		flush( void );

		virtual bool		seek( int theTarget, dioInterface::SeekDirection theDirection = dioInterface::Current );
		virtual bool		find( const RecordData& theKey );
		virtual bool		atEnd( void ) const;

		virtual bool		deserialize( RecordData& theOutput );
		virtual bool		serialize( const RecordData& theInput );

		virtual void		resetCurrentCursor( void );
		virtual void		setCurrentCursor( const RecordData& theKey );

		virtual void		resetEndCursor( void );
		virtual void		setEndCursor( const RecordData& theKey );

		virtual bool		eraseCurrent( void );
		virtual bool		erase( const RecordData& theKey );

	protected:
		MDB_env*									m_env;
		MDB_dbi										m_db;
		MDB_cursor*									m_current;
		MDB_cursor*									m_end;
		MDB_txn*									m_transaction;
		bool										m_isMultimap;
	};
}

#endif