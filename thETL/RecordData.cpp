#include "RecordData.h"

std::ostream & operator<<( std::ostream &os, const thetl::RecordData& theRecordData )
{
	for ( auto value : theRecordData )
	{
		os << value.value( );
	}
	return os;
}