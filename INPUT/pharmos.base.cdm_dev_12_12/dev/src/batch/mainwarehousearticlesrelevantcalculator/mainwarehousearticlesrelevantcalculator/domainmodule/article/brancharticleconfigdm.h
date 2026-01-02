#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_BRANCHARTICLECONFIGDM_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_BRANCHARTICLECONFIGDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "iarticleconfigwriter.h"

#include "usecase/admissionconsidergroupsuc.h"
#include "usecase/admissionconsidergroupsucptr.h"

#include <libutil/irunnableptr.h>
#include <libutil/accessor.h>
#include <libutil/searchyiterator.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace article
{
    class BranchArticleConfigDM : public IArticleConfigWriter
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        BranchArticleConfigDM();
        ~BranchArticleConfigDM();

        void                                                        injectBranchArticleConfigAccessor( libutil::infrastructure::accessor::IAccessorPtr );
        void                                                        injectAdmissionConsiderGroupsUC(useCase::AdmissionConsiderGroup::AdmissionConsiderGroupsUCPtr);
        // from IArticleConfigWriter interface
        void                                                        writeConfig( domMod::article::IArticlePtr );
        void                                                        eraseDeprecatedConfig();

    private:
        // forbidden
        BranchArticleConfigDM( const BranchArticleConfigDM& );
        BranchArticleConfigDM& operator = ( const BranchArticleConfigDM& );

        const log4cplus::Logger&                                    getLogger()   const;

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();

        basar::db::aspect::AccessorPropertyTable_YIterator          get()         const;
        bool                                                        isEmpty()     const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
        useCase::AdmissionConsiderGroup::AdmissionConsiderGroupsUCPtr m_AdmissionGroupUC;
    };

} // end namespace article
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_ARTICLE_BRANCHARTICLECONFIGDM_H
