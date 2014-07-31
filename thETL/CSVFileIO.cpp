#include "CSVFileIO.h"

#include <sstream>

using namespace thetl;

CSVFileIO::CSVFileIO( std::ios_base::openmode theOpenMode, RecordDescription* theRecordDescription, char theDelimiter, bool doIgnoreHeader ) :
	fioInterface( theOpenMode ),
	m_recordDescription( theRecordDescription ),
	m_delimiter( theDelimiter ),
	m_ignoreHeader( doIgnoreHeader )
{

}

CSVFileIO::~CSVFileIO( void )
{

}

bool CSVFileIO::deserialize( RecordData& theOutput )
{
	if ( m_ignoreHeader && m_fileStream.tellg( ) == static_cast< std::streampos >( 0 ) )
	{
		m_fileStream.ignore( std::numeric_limits< std::streamsize >::max( ), '\n' );
	}
	
	theOutput.resize( m_recordDescription->size( ) );
	size_t i = 0;

	for ( auto& aDataField : *m_recordDescription )
	{
		if ( !aDataField->deserialize( theOutput[ i++ ], &m_fileStream, m_delimiter ) )
		{
			return false;
		}
	}

	return true;
}

bool CSVFileIO::serialize( const RecordData& theInput )
{
	size_t i = 0;

	for ( auto& aDataField : *m_recordDescription )
	{
		if ( !aDataField->serialize( &m_fileStream, theInput[ i++ ], m_delimiter ) )
		{
			return false;
		}
	}
	return true;
}
