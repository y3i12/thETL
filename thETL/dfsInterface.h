#if !defined __DATA_FIELD_SERIALIZATION_INTERFACE_H__
#define __DATA_FIELD_SERIALIZATION_INTERFACE_H__

#include "DataField.h"
#include <string>

namespace thetl
{
    // Data Field Serialization Interface
	class dfsInterface
	{
	public:
		dfsInterface( DataField::DataType theType ) : m_type( theType ) { }

		virtual bool deserialize( DataField& theOutput, void* theInput, char theDelimiter ) { return deserialize( theOutput, theInput ); }
		virtual bool serialize( void* theOutput, const DataField& theInput, char theDelimiter ) { return serialize( theOutput, theInput ); }

		virtual bool deserialize( DataField& theOutput, void* theInput ) = 0;
		virtual bool serialize( void* theOutput, const DataField& theInput ) = 0;
		
		virtual void        format( const std::string& theFormat ) { parseFormat( theFormat ); m_format = theFormat; }
		const std::string&  format( void ) const { return m_format; }

		const DataField::DataType m_type;

	protected:
		virtual void parseFormat( const std::string& theFormat ) = 0;

	private:
		std::string m_format;
	};
}

#endif
