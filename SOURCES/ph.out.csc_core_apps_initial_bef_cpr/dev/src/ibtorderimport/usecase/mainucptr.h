//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       28.07.2011
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTORDERIMPORT_USECASE_MAINUCPTR_H
#define GUARD_IBTORDERIMPORT_USECASE_MAINUCPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace ibtorderimport
{
    namespace useCase
    {
        class MainUC;
        typedef boost::shared_ptr< MainUC > MainUCPtr;
    }
}

#endif //end GUARD_IBTORDERIMPORT_USECASE_MAINUCPTR_H
