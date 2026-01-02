//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Michael Helmich
 *  \date       25.08.2021
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IMPORTPRICELIST_USECASE_MAINUCPTR_H
#define GUARD_IMPORTPRICELIST_USECASE_MAINUCPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace useCase
    {
        class MainUC;
        typedef boost::shared_ptr< MainUC > MainUCPtr;
    }
}

#endif //end GUARD_IMPORTPRICELIST_USECASE_MAINUCPTR_H
