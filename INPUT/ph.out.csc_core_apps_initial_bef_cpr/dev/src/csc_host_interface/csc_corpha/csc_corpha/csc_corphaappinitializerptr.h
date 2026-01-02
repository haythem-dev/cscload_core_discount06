//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_CORPHA_CMDLINE_CSC_CORPHA_APP_INITIALIZERPTR_H
#define GUARD_CSC_CORPHA_CMDLINE_CSC_CORPHA_APP_INITIALIZERPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_corpha
{
    namespace cmdLine
    {
        class CSC_CorphaAppInitializer;
        typedef boost::shared_ptr<csc_corpha::cmdLine::CSC_CorphaAppInitializer> CSC_CorphaAppInitializerPtr;
    }
}

#endif // end GUARD_CSC_CORPHA_CMDLINE_CSC_CORPHA_APP_INITIALIZERPTR_H
