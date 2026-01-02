//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_ADMISSION_CONSIDER_GROUPS_UC_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_ADMISSION_CONSIDER_GROUPS_UC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

#include <libutil/irunnable.h>
#include <libutil/irunnableptr.h>
#include "../mainwarehousearticlesrelevantcalculator/usecase/cmnuc.h"
#include "../domainmodule/admissionconsidergroups/admissionconsidergroupsdm.h"

using namespace mainwarehousearticlesrelevantcalculator::domMod::admissionconsidergroups;

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace log4cplus 
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace useCase
{
    namespace AdmissionConsiderGroup
    {
        //-------------------------------------------------------------------------------------------------//
        // class declaration
        //-------------------------------------------------------------------------------------------------//
        class AdmissionConsiderGroupsUC : public libutil::useCase::IRunnable
        {
        public:
            AdmissionConsiderGroupsUC();
            ~AdmissionConsiderGroupsUC();

            virtual void	run(); // not used in this case
            void            injectDBConnection(basar::db::aspect::ConnectionRef);
            void            initAdmissionGroups();
            void            setBranchNo(basar::Int32 branchno);
            void            setArticleno(basar::Int32 artno);
            basar::Int16    assignAdmissionGroups();

        private:
            AdmissionConsiderGroupsUC            (const AdmissionConsiderGroupsUC&);
            AdmissionConsiderGroupsUC& operator= (const AdmissionConsiderGroupsUC&);
           
            const log4cplus::Logger&            m_Logger;
            basar::db::aspect::ConnectionRef    m_DBConnection;
            basar::Int32                        m_BranchNo;
            basar::Int32                        m_ArticleNo;
            AdmissionConsiderGroupsDM*          m_pAdmissionGroupsDM;
            AdmissionGroupsVector               m_vecAdmissionGroups;
        };

        typedef boost::shared_ptr< AdmissionConsiderGroupsUC > AdmissionConsiderGroupsUCPtr;

} // namespace admissionconsidergroups
} // namespace useCase
} // namespace mainwarehousearticlesrelevantcalculator

#endif //GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_ADMISSION_CONSIDER_GROUPS_UC_H