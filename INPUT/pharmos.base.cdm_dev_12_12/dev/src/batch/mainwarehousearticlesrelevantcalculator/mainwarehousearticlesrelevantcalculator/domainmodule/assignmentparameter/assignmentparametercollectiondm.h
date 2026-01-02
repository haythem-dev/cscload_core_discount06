#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ASSIGNMENTPARAMETER_ASSIGNMENTPARAMETERCOLLECTIONDM_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ASSIGNMENTPARAMETER_ASSIGNMENTPARAMETERCOLLECTIONDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "iassignmentparametercollection.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>

#include <map>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace assignmentParameter
{
    class AssignmentParameterCollectionDM : public IAssignmentParameterCollection
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        AssignmentParameterCollectionDM();
        ~AssignmentParameterCollectionDM();

        void injectAssignmentParameterCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from IAssignmentParameter interface
        basar::db::aspect::AccessorPropertyTableRef                 get()     const;
        basar::db::aspect::AccessorPropertyTable_YIterator          getFirstParameterByName( const basar::VarString& ) const;
        bool                                                        isEmpty() const;

        void                                                        findByBranchNo( basar::Int16 );

    private:
        // forbidden
        AssignmentParameterCollectionDM( const AssignmentParameterCollectionDM& );
        AssignmentParameterCollectionDM& operator = ( const AssignmentParameterCollectionDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
                    
        const log4cplus::Logger&                                    getLogger() const;
        void                                                        createIndex();

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;

        typedef std::map< basar::VarString, basar::db::aspect::AccessorPropertyTable_YIterator > ParameterIndex;
        ParameterIndex                                              m_ParameterIndex;
    };

} // end namespace assignmentParameter
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ASSIGNMENTPARAMETER_ASSIGNMENTPARAMETERCOLLECTIONDM_H