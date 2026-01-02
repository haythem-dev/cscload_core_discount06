//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author 
 *  \date 
 *  \version 
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CMDLINE_CSC_PHATRA_APP_INITIALIZER_H
#define GUARD_CMDLINE_CSC_PHATRA_APP_INITIALIZER_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <appinitializer.h>
#include <applxmlconfigwrapper.h>

#include "csc_phatracmdlineevaluatorptr.h"
//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra
{
    namespace cmdLine
    {
        class CSC_PhatraAppInitializer : public libcsc_utils::AppInitializer<CSC_PhatraCmdLineEvaluatorPtr>
	    {  
		    public:
                CSC_PhatraAppInitializer();
                ~CSC_PhatraAppInitializer();
            
            private:
                virtual void                                                doHandleAppConfiguration    (libcsc_utils::ApplXMLConfigWrapper*);
	    };
    }//end namespace cmdLine
}//end csc_phatra
#endif // end GUARD_CMDLINE_CSC_PHATRA_APP_INITIALIZER_H
