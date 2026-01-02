//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      exception indicating inconsistant config values
 *  \author     Marco Köppendörfer
 *  \date       10.01.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CONFIG_DATA_INCONSISTANT_EXCEPTION_H
#define GUARD_LIBCSC_UTILS_CONFIG_DATA_INCONSISTANT_EXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

	class ConfigDataInconsistantException : public basar::Exception
	{
		public:
			/*! \brief std constructor */
			ConfigDataInconsistantException( const basar::ExceptInfo& sInfo );
			/*! \brief std-destructor */
			~ConfigDataInconsistantException();

		private:
			//!< forbidden
			ConfigDataInconsistantException();					
			//AppInitializerException( AppInitializerException& );
			ConfigDataInconsistantException& operator=( ConfigDataInconsistantException& );
	};

} 

#endif 