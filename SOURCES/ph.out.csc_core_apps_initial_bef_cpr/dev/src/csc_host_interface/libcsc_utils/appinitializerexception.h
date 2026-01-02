//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      exception indicating error with initialization of the app
 *  \author     Bischof Bjoern
 *  \date       24.12.2010
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_APP_INITIALIZER_EXCEPTION_H
#define GUARD_LIBCSC_UTILS_APP_INITIALIZER_EXCEPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_exceptions.h>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{

	class AppInitializerException : public basar::Exception
	{
		public:
			/*! \brief std constructor */
			AppInitializerException( const basar::ExceptInfo& sInfo );
			/*! \brief std-destructor */
			~AppInitializerException();

		private:
			//!< forbidden
			AppInitializerException();					
			//AppInitializerException( AppInitializerException& );
			AppInitializerException& operator=( AppInitializerException& );
	};

} 

#endif 

