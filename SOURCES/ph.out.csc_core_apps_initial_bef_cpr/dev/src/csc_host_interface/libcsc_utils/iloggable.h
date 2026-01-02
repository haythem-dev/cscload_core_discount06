//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_ILOGGABLE_H
#define GUARD_LIBCSC_UTILS_ILOGGABLE_H


//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace basar
{
	namespace cmnutil
	{
		class BString;
	}
}



//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//


namespace libcsc_utils
{
	class ILoggable
	{
		public:
			virtual ~ILoggable(){};
			virtual basar::VarString getLogMessage() const = 0;
	};
}//end namspace util

#endif //#ifndef GUARD_LIBCSC_UTILS_ILOGGABLE_H
