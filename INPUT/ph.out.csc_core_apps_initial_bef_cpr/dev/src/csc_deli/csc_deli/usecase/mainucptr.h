#ifndef GUARD_CSC_DELI_USECASE_MAINUCPTR_H
#define GUARD_CSC_DELI_USECASE_MAINUCPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_deli
{
    namespace useCase
    {
        class MainUC;
        typedef boost::shared_ptr< MainUC > MainUCPtr;
    }
}

#endif //end GUARD_CSC_DELI_USECASE_MAINUCPTR_H
