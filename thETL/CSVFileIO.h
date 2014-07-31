#if !defined __CSV_FILE_IO_H__
#define __CSV_FILE_IO_H__

#include "fioInterface.h"

namespace thetl
{

	class CSVFileIO : public fioInterface
	{
	public:
		CSVFileIO( std::ios_base::openmode theOpenMode, RecordDescription* theRecordDescription, char theDelimiter = ';', bool doIgnoreHeader = false );
		virtual ~CSVFileIO( void );

		virtual bool deserialize( RecordData& theOutput );
		virtual bool serialize( const RecordData& theInput );

	protected:
		RecordDescription*	m_recordDescription;
		char				m_delimiter;
		bool				m_ignoreHeader;

	};
}

#endif
