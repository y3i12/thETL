#if !defined __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>
#include <string>

namespace thetl
{

	class GeneralException : public std::exception
	{
	public:
		GeneralException( void ) {}
		GeneralException( const char* theMessage ) : m_message( theMessage ) {}
		GeneralException( const std::string& theMessage ) : m_message( theMessage ) {}

		const char* what( ) const { return m_message.c_str( ); }

	protected:
		std::string m_message;
	};

	class NotImplemented : public GeneralException
	{
	public:
		NotImplemented( const char* theClass, const char* theMethod )
		{
			m_message = "Method not implemented: ";
			m_message += theClass;
			m_message += "::";
			m_message += theMethod;
			m_message += "()\n";
		}

		NotImplemented( const char* theFunction )
		{
			m_message = "Function not implemented: ";
			m_message += theFunction;
			m_message += "()\n";
		}
		

	};

}

#endif
