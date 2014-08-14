#if !defined __RECORD_DATA_H__
#define __RECORD_DATA_H__

#include "DataField.h"
#include "RecordDescription.h"
#include <vector>
#include <ostream>

namespace thetl
{
	typedef std::vector< DataField > RecordData;
}

std::ostream & operator<<( std::ostream &os, const thetl::RecordData& theRecordData );

#endif
