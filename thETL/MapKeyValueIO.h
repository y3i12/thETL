#if !defined __MAP_KEY_VALUE_IO_H__
#define __MAP_KEY_VALUE_IO_H__

#include <vector>
#include <map>

#include "kvioInterface.h"

namespace thetl
{
	template < class T >
	class stdMap_KeyValueIO : public kvioInterface
	{
	public:
		using										kvioInterface::key;
		using										kvioInterface::value;
		typedef std::pair< key, value >				key_value;
		typedef typename T							db;
		typedef typename T::iterator				iterator;
		using										kvioInterface::key_index;

		stdMap_KeyValueIO( key_index theKeyIndexes );
		virtual ~stdMap_KeyValueIO( void );

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
		db											m_db;
		iterator									m_current;
		iterator									m_end;
	};

	template < class T >
	stdMap_KeyValueIO< T >::stdMap_KeyValueIO( kvioInterface::key_index theKeyIndexes ) :
		kvioInterface( theKeyIndexes )
	{

	}

	template < class T >
	stdMap_KeyValueIO< T >::~stdMap_KeyValueIO( void )
	{
		close( );
	}

	template < class T >
	bool stdMap_KeyValueIO< T >::open( void )
	{
		return true;
	}

	template < class T >
	void stdMap_KeyValueIO< T >::close( void )
	{
		m_current = m_db.begin( );
		m_end = m_db.end( );

		for ( ; m_current != m_end; ++m_current )
		{
			delete m_current->second;
		}
		m_db.clear( );

		m_current = m_end = m_db.end( );
	}

	template < class T >
	bool stdMap_KeyValueIO< T >::isOpen( void )
	{
		return true;
	}

	template < class T >
	void stdMap_KeyValueIO< T >::flush( void )
	{
	}

	template < class T >
	bool stdMap_KeyValueIO< T >::seek( int theTarget, dioInterface::SeekDirection theDirection )
	{
		switch ( theDirection )
		{
		case dioInterface::Beginning:	m_current = m_db.begin( ); break;
		case dioInterface::Current:		break;
		case dioInterface::End:			m_current = m_db.end( ); break;
		}

		int dir = theTarget;
		theTarget = abs( theDirection );
		dir = dir / theTarget;

		for ( int i = 0; i < theTarget; ++i )
		{
			if ( dir < 0 )
			{
				--m_current;
			}
			else
			{
				++m_current;
			}
		}

		return true;
	}

	template < class T >
	bool stdMap_KeyValueIO< T >::find( const RecordData& theKey )
	{
		m_current = m_db.find( theKey );

		return m_current != m_db.end( );
	}

	template < class T >
	bool stdMap_KeyValueIO< T >::atEnd( void ) const
	{
		return m_current == m_end;
	}

	template < class T >
	bool stdMap_KeyValueIO< T >::deserialize( RecordData& theOutput )
	{
		if ( atEnd( ) )
		{
			return false;
		}

		theOutput = *m_current->second;
		++m_current;

		return true;
	}

	template < class T >
	bool stdMap_KeyValueIO< T >::serialize( const RecordData& theInput )
	{
		key_value theKeyValue( makeKey( theInput ), 0 );

		std::pair< iterator, bool > theInsertion = m_db.insert( theKeyValue );

		if ( theInsertion.second )
		{
			iterator& itr = theInsertion.first;
			itr->second = new RecordData( theInput );
			return true;
		}

		return false;
	}

	template < >
	bool stdMap_KeyValueIO< std::multimap< kvioInterface::key, kvioInterface::value > >::serialize( const RecordData& theInput )
	{
		m_db.insert( key_value( makeKey( theInput ), new RecordData( theInput ) ) );
		return true;
	}

	template < class T >
	void stdMap_KeyValueIO< T >::resetCurrentCursor( void )
	{
		m_current = m_db.begin( );
	}

	template < class T >
	void stdMap_KeyValueIO< T >::setCurrentCursor( const RecordData& theKey )
	{
		m_current = m_db.lower_bound( theKey );
	}

	template < class T >
	void stdMap_KeyValueIO< T >::resetEndCursor( void )
	{
		m_end = m_db.end( );
	}

	template < class T >
	void stdMap_KeyValueIO< T >::setEndCursor( const RecordData& theKey )
	{
		m_end = m_db.upper_bound( theKey );
	}

	template < class T >
	bool stdMap_KeyValueIO< T >::eraseCurrent( void )
	{
		if ( m_current == m_end )
		{
			return false;
		}

		iterator tempItr = m_current++;
		delete tempItr->second;
		m_db.erase( m_current );
		return true;
	}

	template < class T >
	bool stdMap_KeyValueIO< T >::erase( const RecordData& theKey )
	{
		iterator tempItr = m_db.find( theKey );
		if ( tempItr == m_db.end( ) )
		{
			return false;
		}

		delete tempItr->second;
		m_db.erase( m_current );
		return true;
	}

	typedef stdMap_KeyValueIO < std::map< kvioInterface::key, kvioInterface::value > > MapKeyValueIO;
	typedef stdMap_KeyValueIO < std::multimap< kvioInterface::key, kvioInterface::value > > MultiMapKeyValueIO;
}

#endif