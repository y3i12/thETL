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
		DataField( void );
		virtual ~DataField( void );

		virtual void value( const DataFieldValue& theValue );
		virtual DataFieldValue& value( void );
		virtual const DataFieldValue& value( void ) const;

		operator DataFieldValue&( void );
		operator const DataFieldValue&( void ) const;

		DataFieldValue& operator=( const DataFieldValue& theValue );

		DataFieldValue& operator=( boost::posix_time::ptime& theValue );
		DataFieldValue& operator=( long long theValue );
		DataFieldValue& operator=( double theValue );
		DataFieldValue& operator=( const std::string& theValue );
		DataFieldValue& operator=( boost::blank theValue );

	protected:
		DataFieldValue m_value;

	};


}

#endif
