//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author 
 *  \date 
 *  \version 
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CMDLINE_CSC_CORPHA_APP_INITIALIZER_H
#define GUARD_CMDLINE_CSC_CORPHA_APP_INITIALIZER_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <appinitializer.h>
#include <applxmlconfigwrapper.h>
#include "csc_corphacmdlineevaluatorptr.h"
//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_corpha
{
    namespace cmdLine
    {
        class CSC_CorphaAppInitializer : public libcsc_utils::AppInitializer<CSC_CorphaCmdLineEvaluatorPtr>
	    {  
		    public:
                CSC_CorphaAppInitializer();
                ~CSC_CorphaAppInitializer();
            
            private:
				virtual void                                                doHandleAppConfiguration    ( libcsc_utils::ApplXMLConfigWrapper* );
	    };
    }//end namespace cmdLine
}//end csc_phatra
#endif // end GUARD_CMDLINE_CSC_CORPHA_APP_INITIALIZER_H
