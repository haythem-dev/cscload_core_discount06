#ifndef GUARD_CSC_DELI_USECASE_DEBTLIMITBATCHUCPTR_H
#define GUARD_CSC_DELI_USECASE_DEBTLIMITBATCHUCPTR_H

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
        class DebtLimitBatchUC;
        typedef boost::shared_ptr< DebtLimitBatchUC > DebtLimitBatchUCPtr;
    }
}

#endif //end GUARD_CSC_DELI_USECASE_DEBTLIMITBATCHUCPTR_H
