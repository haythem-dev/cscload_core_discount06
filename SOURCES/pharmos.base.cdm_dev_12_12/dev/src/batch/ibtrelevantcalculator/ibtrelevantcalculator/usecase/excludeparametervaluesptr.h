#ifndef GUARD_IBTRELEVANTCALCULATOR_USECASE_EXCLUDEPARAMETERVALUESPTR_H
#define GUARD_IBTRELEVANTCALCULATOR_USECASE_EXCLUDEPARAMETERVALUESPTR_H

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
        class ExcludeParameterValues;
        typedef boost::shared_ptr< ExcludeParameterValues > ExcludeParameterValuesPtr;
    }
}

#endif //end GUARD_IBTRELEVANTCALCULATOR_USECASE_EXCLUDEPARAMETERVALUESPTR_H