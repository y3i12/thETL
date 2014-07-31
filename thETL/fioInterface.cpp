#include "fioInterface.h"
#include "Exceptions.h"

using namespace thetl;

fioInterface::fioInterface( std::ios_base::openmode theOpenMode ) :
    m_openMode( theOpenMode )
{
}

fioInterface::~fioInterface( void )
{
	close( );
}

bool fioInterface::open( void )
{
	m_fileStream.open( sourceString( ), m_openMode );
	return isOpen( );
}

void fioInterface::close( void )
{
	if ( !isOpen( ) )
	{
		return;
	}

	flush( );
	m_fileStream.close( );
}

bool fioInterface::isOpen( void )
{
	return m_fileStream.is_open( );
}

void fioInterface::flush( void )
{
	m_fileStream.flush( );
}

bool fioInterface::atEnd( void ) const
{
	return m_fileStream.eof( );
}

bool fioInterface::seek( int theTarget, dioInterface::SeekDirection theDirection )
{
	throw NotImplemented( "fioInterface", "seek" );
}

bool fioInterface::find( const RecordData& theKey )
{
	throw NotImplemented( "fioInterface", "find" );
}
