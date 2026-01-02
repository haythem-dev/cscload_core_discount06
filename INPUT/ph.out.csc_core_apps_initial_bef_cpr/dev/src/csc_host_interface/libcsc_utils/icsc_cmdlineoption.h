//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      common command line options for csc_phatra, csc_corpha, csc_phabor
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_ICSC_CMDLINEOPTION_H
#define GUARD_LIBCSC_UTILS_ICSC_CMDLINEOPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	class ICSC_CmdLineOption
	{
		public:
			virtual ~ICSC_CmdLineOption(){};
			
			virtual basar::Int16		getBranchNo() const = 0;
			virtual basar::VarString	getConfigFile() const = 0;
			virtual basar::VarString	getApplicationName() const = 0;
            virtual bool              isTestingSet() const = 0;
            virtual bool              isNoMailSet() const = 0;
			virtual bool				isExtendedLoggingSet() const = 0;
	};
	

}
#endif // end GUARD_LIBCSC_UTILS_ICSC_CMDLINEOPTION_H

