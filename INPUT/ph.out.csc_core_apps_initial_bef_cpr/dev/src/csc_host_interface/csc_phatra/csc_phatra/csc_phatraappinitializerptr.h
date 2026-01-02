//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHATRA_CMDLINE_CSC_PHATRA_APP_INITIALIZERPTR_H
#define GUARD_CSC_PHATRA_CMDLINE_CSC_PHATRA_APP_INITIALIZERPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra
{
    namespace cmdLine
    {
        class CSC_PhatraAppInitializer;
        typedef boost::shared_ptr<csc_phatra::cmdLine::CSC_PhatraAppInitializer> CSC_PhatraAppInitializerPtr;
    }
}

#endif // end GUARD_CSC_PHATRA_CMDLINE_CSC_PHATRA_APP_INITIALIZERPTR_H

