//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHABOR_CMDLINE_CSC_PHABOR_APP_INITIALIZERPTR_H
#define GUARD_CSC_PHABOR_CMDLINE_CSC_PHABOR_APP_INITIALIZERPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor
{
    namespace cmdLine
    {
        class CSC_PhaborAppInitializer;
        typedef boost::shared_ptr<csc_phabor::cmdLine::CSC_PhaborAppInitializer> CSC_PhaborAppInitializerPtr;
    }
}

#endif // end GUARD_CSC_PHABOR_CMDLINE_CSC_PHABOR_APP_INITIALIZERPTR_H
