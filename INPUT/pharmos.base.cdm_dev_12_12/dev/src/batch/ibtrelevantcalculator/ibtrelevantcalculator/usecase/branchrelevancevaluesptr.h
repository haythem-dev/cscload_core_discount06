#ifndef GUARD_IBTRELEVANTCALCULATOR_USECASE_BRANCHRELEVANCEVALUESPTR_H
#define GUARD_IBTRELEVANTCALCULATOR_USECASE_BRANCHRELEVANCEVALUESPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace useCase
    {
        class BranchRelevanceValues;
        typedef boost::shared_ptr< BranchRelevanceValues > BranchRelevanceValuePtr;
    }
}

#endif //end GUARD_IBTRELEVANTCALCULATOR_USECASE_BRANCHRELEVANCEVALUESPTR_H