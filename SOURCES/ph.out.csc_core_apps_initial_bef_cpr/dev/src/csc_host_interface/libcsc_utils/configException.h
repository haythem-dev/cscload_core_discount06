//--------------------------------------------------------------------------------------------------//
/*! \file		configexception.h
*  \brief      exception for config
*  \author     Andre Egerer
*  \date       23.04.2012
*/
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CONFIG_EXCEPTION_H
#define GUARD_LIBCSC_UTILS_CONFIG_EXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	namespace config
	{
		class ConfigException : public basar::Exception
		{
		public:
			/*! \brief std constructor */
			ConfigException( const basar::ExceptInfo& sInfo );
			/*! \brief std-destructor */
			~ConfigException();

		private:
			//!< forbidden
			ConfigException();					
			//ConfigException( ConfigException& );
			ConfigException& operator=( ConfigException& );
		};
	}
} // end namespace csc_phatra

#endif // end GUARD_LIBCSC_UTILS_CONFIG_EXCEPTION_H

