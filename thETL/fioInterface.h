#if !defined __FILE_IO_INTERFACE_H__
#define __FILE_IO_INTERFACE_H__

#include "dioInterface.h"
#include <fstream>
#include <string>
#include <list>

namespace thetl
{
	// file I/O Interface
	class fioInterface : public dioInterface
	{
	public:
		fioInterface( std::ios_base::openmode theOpenMode );
		virtual ~fioInterface( void );

		virtual bool open( void );
		virtual void close( void );
		virtual bool isOpen( void );

		virtual void flush( void );

		virtual bool seek( int theTarget, dioInterface::SeekDirection theDirection = dioInterface::Current );
		virtual bool find( const RecordData& theKey );
		virtual bool atEnd( void ) const;

		virtual bool deserialize( RecordData& theOutput ) = 0;
		virtual bool serialize( const RecordData& theInput ) = 0;
		
	protected:
		std::ios_base::openmode m_openMode;
		std::fstream			m_fileStream;


	};


}

#endif
