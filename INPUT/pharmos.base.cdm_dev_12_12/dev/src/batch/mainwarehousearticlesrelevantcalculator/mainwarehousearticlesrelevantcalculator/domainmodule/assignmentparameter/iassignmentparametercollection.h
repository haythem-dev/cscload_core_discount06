#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ASSIGNMENTPARAMETER_IASSIGNMENTPARAMETERCOLLECTION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ASSIGNMENTPARAMETER_IASSIGNMENTPARAMETERCOLLECTION_H

#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTableRef;
            class AccessorPropertyTable_YIterator;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace assignmentParameter
{
    class IAssignmentParameterCollection
    {
    public:
        virtual ~IAssignmentParameterCollection() {}

        virtual void                                               findByBranchNo( basar::Int16 )                           = 0;

        virtual basar::db::aspect::AccessorPropertyTableRef        get()                                              const = 0;
        virtual basar::db::aspect::AccessorPropertyTable_YIterator getFirstParameterByName( const basar::VarString& ) const = 0;

        virtual bool                                               isEmpty()                                          const = 0;
    };

} // end namespace assignmentParameter
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ASSIGNMENTPARAMETER_IASSIGNMENTPARAMETERCOLLECTION_H
