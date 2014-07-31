#if !defined __DATA_FIELD_SERIALIZATION_FILE_STREAM_H__
#define __DATA_FIELD_SERIALIZATION_FILE_STREAM_H__

#include "dfsInterface.h"

namespace thetl
{
	class dfsFStream : public dfsInterface
	{
	public:
		dfsFStream( DataField::DataType theType ) : dfsInterface( theType ) { }

		virtual bool deserialize( DataField& theOutput, void* theInput, char theDelimiter );
		virtual bool serialize( void* theOutput, const DataField& theInput, char theDelimiter );

		virtual bool deserialize( DataField& theOutput, void* theInput );
		virtual bool serialize( void* theOutput, const DataField& theInput );

	protected:
		virtual void parseFormat( const std::string& theFormat );

	};
}

#endif
