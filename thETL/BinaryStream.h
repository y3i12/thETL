#if !defined __BINARY_STREAM_HPP__
#define __BINARY_STREAM_HPP__

#include <algorithm>
#include <iosfwd>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/positioning.hpp>
#include "DataField.h"
#include "RecordData.h"

namespace thetl
{
	class BinaryStream
	{
	public:
		typedef unsigned char							char_type;
		typedef std::vector< char_type >				buffer;
		typedef buffer::size_type						size_type;

		BinaryStream( buffer& container );
		std::streamsize read( char_type* s, std::streamsize n );
		std::streamsize write( const char_type* s, std::streamsize n );

		operator char_type*( );
		operator const char_type*( ) const;

		char_type* data( size_type thePosition = 0 );
		const char_type* data( size_type thePosition = 0 ) const;

		template < class T >
		BinaryStream& operator << ( const T& theValue )
		{
			write( reinterpret_cast< const char_type* >( &theValue ), sizeof( T ) );
			return *this;
		}

		BinaryStream& operator << ( const RecordData& theValue );
		BinaryStream& operator << ( const DataField& theValue );
		BinaryStream& operator << ( const std::string& theValue );
		BinaryStream& operator << ( boost::blank theValue );


		template < class T >
		BinaryStream& operator >> ( T& theValue )
		{
			read( reinterpret_cast< char_type* >( &theValue ), sizeof( T ) );
			return *this;
		}

		BinaryStream& operator >> ( RecordData& theValue );
		BinaryStream& operator >> ( DataField& theValue );
		BinaryStream& operator >> ( std::string& theValue );
		BinaryStream& operator >> ( boost::blank theValue );

		void		rewind( );
		size_type	position( );

	private:
		buffer&		m_container;
		size_type   m_position;
	};
}

#endif
