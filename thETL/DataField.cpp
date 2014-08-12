#include "DataField.h"


using namespace thetl;

DataField::DataField( const DataFieldValue& theValue ) :
	m_value( theValue )
{

}

DataField::DataField( boost::posix_time::ptime& theValue ) :
	m_value( theValue )
{

}

DataField::DataField( long long theValue ) :
	m_value( theValue )
{

}

DataField::DataField( double theValue ) :
	m_value( theValue )
{

}

DataField::DataField( const std::string& theValue ) :
	m_value( theValue )
{

}

DataField::DataField( const char* theValue ) :
	m_value( std::string( theValue ) )
{

}

DataField::DataField( void ) :
	m_value( boost::blank() )
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

DataField& DataField::operator=( const DataFieldValue& theValue )
{
	m_value = theValue;
	return *this;

}

DataField& DataField::operator=( const boost::posix_time::ptime& theValue )
{
	m_value = theValue;
	return *this;
}

DataField& DataField::operator=( long long theValue )
{
	m_value = theValue;
	return *this;
}

DataField& DataField::operator=( double theValue )
{
	m_value = theValue;
	return *this;
}

DataField& DataField::operator=( const std::string& theValue )
{
	m_value = theValue;
	return *this;
}

DataField& DataField::operator=( boost::blank theValue )
{
	m_value = theValue;
	return *this;
}

bool DataField::operator==( const DataFieldValue& theValue ) const
{
	return m_value == theValue;
}

bool DataField::operator==( const boost::posix_time::ptime& theValue ) const
{
	return boost::get< boost::posix_time::ptime >( m_value ) == theValue;
}

bool DataField::operator==( long long theValue ) const
{
	return boost::get< long long >( m_value ) == theValue;
}

bool DataField::operator==( double theValue ) const
{
	return boost::get< double >( m_value ) == theValue;
}

bool DataField::operator==( const std::string& theValue ) const
{
	return boost::get< std::string >( m_value ) == theValue;
}

bool DataField::operator==( boost::blank theValue ) const
{
	return boost::get< boost::blank >( m_value ) == theValue;
}

bool DataField::operator<( const DataField& theValue )
{
	return m_value < theValue.m_value;
}

bool DataField::operator<( const DataField& theValue ) const
{
	return m_value < theValue.m_value;
}