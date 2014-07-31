#if !defined __DATA_IO_INTERFACE_H__
#define __DATA_IO_INTERFACE_H__

#include "RecordData.h"
#include "RecordDescription.h"
#include <string>

namespace thetl
{
	// Data I/O Interface
	class dioInterface
	{
	public:
		enum SeekDirection
		{
			Beginning,
			Current,
			End
		};

	public:
		virtual ~dioInterface( void ) {}

		void            sourceString( const char* theSourceString ) { m_sourceString = theSourceString;	}
		const char*     sourceString( void ) const                  { return m_sourceString.c_str( );   }

		virtual bool    open( void )    = 0;
		virtual void    close( void )   = 0;
		virtual bool    isOpen( void )  = 0;
		virtual void    flush( void )   = 0;

		virtual bool    seek( int theTarget, SeekDirection theDirection = Current ) = 0;
		virtual bool    find( const RecordData& theKey ) = 0;
		virtual bool    atEnd( void ) const = 0;

		virtual bool    deserialize( RecordData& theOutput )     = 0;
		virtual bool    serialize( const RecordData& theInput ) = 0;
		
	protected:
		std::string     m_sourceString;
	};

}

#endif
