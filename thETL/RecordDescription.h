#if !defined __RECORD_DESCRIPTION_H__
#define __RECORD_DESCRIPTION_H__

#include <vector>
#include <string>

#include "DataField.h"
#include "dfsInterface.h"

namespace thetl
{
	typedef std::vector< dfsInterface* > RecordDescription;
}

#endif
