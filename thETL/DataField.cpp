#include "DataField.h"


using namespace thetl;

DataField::DataField( void )
{

}

DataField::~DataField( void )
{

}

void DataField::value( const DataFieldValue& theValue )
{
	m_value = theValue;
}

DataFieldValue& DataField::value( void )
{
	return m_value;
}

const DataFieldValue& DataField::value( void ) const
{
	return m_value;
}

DataField::operator DataFieldValue&( void )
{
	return m_value;
}

DataField::operator const DataFieldValue&( void ) const
{
	return m_value;
}

DataFieldValue& DataField::operator=( const DataFieldValue& theValue )
{
	m_value = theValue;
}

DataFieldValue& DataField::operator=( boost::posix_time::ptime& theValue )
{
	m_value = theValue;
}

DataFieldValue& DataField::operator=( long long theValue )
{
	m_value = theValue;
}

DataFieldValue& DataField::operator=( double theValue )
{
	m_value = theValue;
}

DataFieldValue& DataField::operator=( const std::string& theValue )
{
	m_value = theValue;
}

DataFieldValue& DataField::operator=( boost::blank theValue )
{
	m_value = theValue;
}