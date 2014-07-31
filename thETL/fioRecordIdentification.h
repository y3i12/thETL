#if !defined __FILE_IO_RECORD_IDENTIFICATION_H__
#define __FILE_IO_RECORD_IDENTIFICATION_H__

#include "RecordData.h"
#include <string>

namespace thetl
{
    ////////////////////////////////////////////////////////////////////////////
    // IDENTIFICATION TOKEN
	////////////////////////////////////////////////////////////////////////////
	template < class T >
	struct IdentificationToken
	{
		IdentificationToken( size_t thePosition, const T& theValue ) :
		    m_position( thePosition ),
		    m_value( theValue )
		{

		}

		size_t  m_position;
		T       m_value;
	};

	////////////////////////////////////////////////////////////////////////////
	// Record Identification Interface
	////////////////////////////////////////////////////////////////////////////
	template < class T >
	struct riInterface
	{
		virtual bool fitsInRecord( const T& theRecord ) = 0;
	};

	////////////////////////////////////////////////////////////////////////////
    // Single Record
	////////////////////////////////////////////////////////////////////////////
	template < class T >
	struct SingleRecord : public riInterface< T >
	{
		virtual bool fitsInRecord( const T& theRecord ) { return true; }
	};


	////////////////////////////////////////////////////////////////////////////
    // Records with patterns
	////////////////////////////////////////////////////////////////////////////
	template < class T > struct PatternRecord;

	// string specialization
	template < >
	struct PatternRecord < std::string > : public riInterface< std::string >
	{
		PatternRecord( size_t thePosition, const std::string& theValue ) :
		m_identifcation( thePosition, theValue )
		{
		}

		virtual bool fitsInRecord( const std::string& theRecord )
		{
			return m_identifcation.m_value == theRecord.substr( m_identifcation.m_position, m_identifcation.m_value.size( ) );
		}

		IdentificationToken< std::string > m_identifcation;
	};

	// RecordData specialization
	template < >
	struct PatternRecord < DataField > : public riInterface< DataField >
	{
		PatternRecord( size_t thePosition, const DataField& theValue ) :
		    m_identifcation( thePosition, theValue )
		{
		}

		virtual bool fitsInRecord( const RecordData& theRecord )
		{
			return m_identifcation.m_value == theRecord[ m_identifcation.m_position ];
		}

		IdentificationToken< DataField > m_identifcation;
	};

    // TODO: regex?

}

#endif
