#include "BinaryStream.h"

#include <boost/variant/static_visitor.hpp>

using namespace thetl;

BinaryStream::BinaryStream( buffer& container ) : m_container( container ), m_position( 0 )
{
}

std::streamsize BinaryStream::read( char_type* s, std::streamsize n )
{
	size_type amt = m_container.size( ) - m_position;
	size_type result = ( std::min )( static_cast< size_type >( n ), amt );

	if ( result != 0 )
	{
		std::copy( m_container.begin( ) + m_position, m_container.begin( ) + m_position + result, s );
		m_position += result;
		return result;
	}
	else
	{
		return -1; // EOF
	}
}

std::streamsize BinaryStream::write( const char_type* s, std::streamsize n )
{
	size_type result = 0;

	if ( m_position != m_container.size( ) )
	{
		size_type amt = m_container.size( ) - m_position;
		size_type result = ( std::min )( static_cast< size_type >( n ), amt );
		std::copy( s, s + result, m_container.begin( ) + m_position );
		m_position += result;
	}

	if ( result < n )
	{
		m_container.insert( m_container.end( ), s, s + n );
		m_position = m_container.size( );
	}

	return n;
}

BinaryStream::operator BinaryStream::char_type*( )
{
	return &m_container[ 0 ];
}

BinaryStream::operator const BinaryStream::char_type*( ) const
{
	return &m_container[ 0 ];
}

BinaryStream& BinaryStream::operator << ( const RecordData& theValue )
{
	for ( auto& value : theValue )
	{
		( *this ) << value;
	}
	return *this;
}

BinaryStream& BinaryStream::operator << ( const DataField& data )
{
	boost::apply_visitor( writer_visitor< BinaryStream >( *this ), const_cast< DataField& >( data ).value( ) );
	return *this;
}

BinaryStream& BinaryStream::operator << ( const std::string& theValue )
{
	write( reinterpret_cast< const char_type* >( theValue.c_str() ), theValue.size( ) + 1 );
	return *this;
}

BinaryStream& BinaryStream::operator << ( boost::blank theValue )
{
	return *this;
}


BinaryStream& BinaryStream::operator >> ( RecordData& theValue )
{
	for ( auto& value : theValue )
	{
		( *this ) >> value;
	}
	return *this;
}

BinaryStream& BinaryStream::operator >> ( DataField& data )
{
	boost::apply_visitor( reader_visitor< BinaryStream >( *this ), data.value() );
	return *this;
}

BinaryStream& BinaryStream::operator >> ( std::string& theValue )
{
	theValue.assign( reinterpret_cast< char* >( &m_container[ m_position ] ) );
	m_position += theValue.size( ) + 1;
	return *this;
}

BinaryStream& BinaryStream::operator >> ( boost::blank theValue )
{
	return *this;
}

void BinaryStream::rewind( )
{
	m_position = 0;
}
