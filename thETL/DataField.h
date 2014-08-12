#if !defined __DATA_H__
#define __DATA_H__

#include <boost\variant.hpp>
#include <string>
#include <boost\date_time\posix_time\posix_time.hpp>

namespace thetl
{

	typedef boost::variant< boost::posix_time::ptime, long long, double, std::string, boost::blank > DataFieldValue;

	class DataField
	{
	public:
		enum DataType
		{
			Time,
			Integer,
			Float,
			String,
			Blank
		};

	public:

		DataField( const DataFieldValue& theValue );
		explicit DataField( boost::posix_time::ptime& theValue );
		DataField( long long theValue );
		DataField( double theValue );
		DataField( const std::string& theValue );
		DataField( const char* theValue );
		DataField( void );
		virtual ~DataField( void );

		virtual void value( const DataFieldValue& theValue );
		virtual DataFieldValue& value( void );
		virtual const DataFieldValue& value( void ) const;

		operator DataFieldValue&( void );
		operator const DataFieldValue&( void ) const;

		DataField&	operator=( const DataFieldValue& theValue );
		DataField&	operator=( const boost::posix_time::ptime& theValue );
		DataField&	operator=( long long theValue );
		DataField&	operator=( double theValue );
		DataField&	operator=( const std::string& theValue );
		DataField&	operator=( boost::blank theValue );

		bool		operator==( const DataFieldValue& theValue ) const;
		bool		operator==( const boost::posix_time::ptime& theValue ) const;
		bool		operator==( long long theValue ) const;
		bool		operator==( double theValue ) const;
		bool		operator==( const std::string& theValue ) const;
		bool		operator==( boost::blank theValue ) const;

		bool		operator<( const DataField& theValue );
		bool		operator<( const DataField& theValue ) const;

	protected:
		DataFieldValue m_value;

	};


}

#endif
