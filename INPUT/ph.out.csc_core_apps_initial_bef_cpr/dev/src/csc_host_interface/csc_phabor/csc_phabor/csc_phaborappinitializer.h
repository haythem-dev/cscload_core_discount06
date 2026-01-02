//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author 
 *  \date 
 *  \version 
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CMDLINE_CSC_PHABOR_APP_INITIALIZER_H
#define GUARD_CMDLINE_CSC_PHABOR_APP_INITIALIZER_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <appinitializer.h>
#include <applxmlconfigwrapper.h>
#include "csc_phaborcmdlineevaluatorptr.h"

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor
{
    namespace cmdLine
    {
        class CSC_PhaborAppInitializer : public libcsc_utils::AppInitializer<CSC_PhaborCmdLineEvaluatorPtr>
	    {  
		    public:
                CSC_PhaborAppInitializer();
                ~CSC_PhaborAppInitializer();
            
            private:
                virtual void                                                doHandleAppConfiguration    (libcsc_utils::ApplXMLConfigWrapper*);
	    };
    }//end namespace cmdLine
}//end csc_phabor
#endif // end GUARD_CMDLINE_CSC_PHABOR_APP_INITIALIZER_H
