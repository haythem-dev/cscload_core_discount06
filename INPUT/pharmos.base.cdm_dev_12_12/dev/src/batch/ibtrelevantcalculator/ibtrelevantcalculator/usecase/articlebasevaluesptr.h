#ifndef GUARD_IBTRELEVANTCALCULATOR_USECASE_ARTICLEBASEVALUESPTR_H
#define GUARD_IBTRELEVANTCALCULATOR_USECASE_ARTICLEBASEVALUESPTR_H

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
        class ArticleBaseValues;
        typedef boost::shared_ptr< ArticleBaseValues > ArticleBaseValuesPtr;
    }
}

#endif //end GUARD_IBTRELEVANTCALCULATOR_USECASE_ARTICLEBASEVALUESPTR_H