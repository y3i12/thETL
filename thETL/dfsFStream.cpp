#include "dfsFStream.h"
#include "Exceptions.h"

#include <string>
#include <fstream>
#include <ctime>
#include <boost\blank.hpp>

#include "strptime.h"

using namespace thetl;

bool dfsFStream::deserialize( DataField& theOutput, void* theInput, char theDelimiter )
{
	std::fstream& input = *static_cast< std::fstream* >( theInput );
	std::string str;
	std::getline( input, str, theDelimiter );

	switch ( m_type )
	{
	case DataField::Time:
	{
		tm timeStruct;
		strptime( str.c_str( ), format( ).c_str( ), &timeStruct );
		theOutput = boost::posix_time::from_time_t( mktime( &timeStruct ) );
		break;
	}
	case DataField::Integer:
	{
		// TODO: sscanf to parse complex formats
		theOutput = atoll( str.c_str( ) );
		break;
	}
	case DataField::Float:
	{
		// TODO: sscanf to parse complex formats
		theOutput = atof( str.c_str( ) );
		break;
	}
	case DataField::String:
	{
		theOutput = str;
		break;
	}
	case DataField::Blank:
	{
		theOutput = boost::blank( );
		break;
	}
	}
	return true;
}

bool dfsFStream::serialize( void* theOutput, const DataField& theInput, char theDelimiter )
{
	switch ( m_type )
	{
	case DataField::Time: 		throw NotImplemented( "dfsFStream", "serialize Time" );
	case DataField::Integer:	throw NotImplemented( "dfsFStream", "serialize Integer" );
	case DataField::Float:		throw NotImplemented( "dfsFStream", "serialize Float" );
	case DataField::String:		throw NotImplemented( "dfsFStream", "serialize String" );
	case DataField::Blank:		throw NotImplemented( "dfsFStream", "serialize Blank" );
	}
	return true;
}

bool dfsFStream::deserialize( DataField& theOutput, void* theInput )
{
	throw NotImplemented( "dfsFStream", "deserialize" );
	return true;
}

bool dfsFStream::serialize( void* theOutput, const DataField& theInput )
{
	throw NotImplemented( "dfsFStream", "serialize" );
	return true;
}

void dfsFStream::parseFormat( const std::string& theFormat )
{

}