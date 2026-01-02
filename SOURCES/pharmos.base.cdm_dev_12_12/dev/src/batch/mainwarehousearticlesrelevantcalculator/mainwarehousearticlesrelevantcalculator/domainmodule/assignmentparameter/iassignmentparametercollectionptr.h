#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ASSIGNMENTPARAMETER_IASSIGNMENTPARAMETERCOLLECTIONPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ASSIGNMENTPARAMETER_IASSIGNMENTPARAMETERCOLLECTIONPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace domMod
    {
        namespace assignmentParameter
        {
            class IAssignmentParameterCollection;
            typedef boost::shared_ptr< IAssignmentParameterCollection > IAssignmentParameterCollectionPtr;
        }
    }
}

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ASSIGNMENTPARAMETER_IASSIGNMENTPARAMETERCOLLECTIONPTR_H
