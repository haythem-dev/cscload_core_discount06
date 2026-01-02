//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//

//#include "../mainwarehousearticlesrelevantcalculator/usecase/cmnuc.h"

#include "admissionconsidergroupsuc.h"
#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

#include "../infrastructure/accessor/admissiongroups/admissiongroups.h"
#include <libutil/exception.h>
#include <libutil/util.h>
//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace useCase
{
namespace AdmissionConsiderGroup
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdmissionConsiderGroupsUC::AdmissionConsiderGroupsUC()
: m_Logger(mainwarehousearticlesrelevantcalculator::LoggerPool::getLoggerUseCases())
{
	METHODNAME_DEF(AdmissionConsiderGroupsUC, AdmissionConsiderGroupsUC)
    BLOG_TRACE_METHOD( m_Logger, fun );

    m_pAdmissionGroupsDM = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdmissionConsiderGroupsUC::~AdmissionConsiderGroupsUC()
{
	METHODNAME_DEF(AdmissionConsiderGroupsUC, ~AdmissionConsiderGroupsUC)
    BLOG_TRACE_METHOD( m_Logger, fun );

    if (m_pAdmissionGroupsDM != NULL)
    {
        delete m_pAdmissionGroupsDM;
        m_pAdmissionGroupsDM = NULL;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdmissionConsiderGroupsUC::setArticleno(basar::Int32 artno)
{
    m_ArticleNo = artno;
}

void AdmissionConsiderGroupsUC::run()
{
	METHODNAME_DEF(AdmissionConsiderGroupsUC, run )
    BLOG_TRACE_METHOD( m_Logger, fun );

    try
    {
        BLOG_INFO_STREAM( m_Logger, "------------------------------------------------------------------------------------------" );
        BLOG_INFO_STREAM( m_Logger, "AdmissionConsiderGroups - START" );
        BLOG_INFO_STREAM( m_Logger, "------------------------------------------------------------------------------------------" );

        // not used here, the assignAdmissionGroups are called directly to the brancharticleconfigdm
        //assignAdmissionGroups();

        BLOG_INFO_STREAM( m_Logger, "------------------------------------------------------------------------------------------" );
        BLOG_INFO_STREAM( m_Logger, "AdmissionConsiderGroups - END" );
        BLOG_INFO_STREAM( m_Logger, "------------------------------------------------------------------------------------------" );
    }
	catch( basar::Exception& e )
	{
		libutil::exceptions::ExceptionHandler::processBasarException( e, m_Logger, fun, __FILE__, __LINE__ );
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdmissionConsiderGroupsUC::injectDBConnection(basar::db::aspect::ConnectionRef connection)
{
    METHODNAME_DEF(IBTLevelAssignmentCompMgr, injectDBConnection)
	BLOG_TRACE_METHOD(m_Logger, fun);

    m_DBConnection = connection;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdmissionConsiderGroupsUC::setBranchNo(basar::Int32 branchno)
{
    m_BranchNo = branchno;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdmissionConsiderGroupsUC::initAdmissionGroups()
{
    if ((m_pAdmissionGroupsDM == NULL) && (m_DBConnection.isNull() == false))
    {
        m_pAdmissionGroupsDM = new AdmissionConsiderGroupsDM(m_DBConnection);
        m_vecAdmissionGroups = m_pAdmissionGroupsDM->getActiveGroups();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
basar::Int16 AdmissionConsiderGroupsUC::assignAdmissionGroups()
{
    METHODNAME_DEF(AdmissionConsiderGroupsUC, assignAdmGroups)
        BLOG_TRACE_METHOD(m_Logger, fun);

    using namespace mainwarehousearticlesrelevantcalculator::domMod::admissionconsidergroups;
    BLOG_TRACE(m_Logger, "AdmissionConsiderGroupsUC::assignAdmGroups() START");

    basar::Int16 paramgroupid = 0;

    if (m_pAdmissionGroupsDM != NULL)
    {
        try
        {
            // iterate admission param groups and execute condition sqls
            for (size_t i = 0; i < m_vecAdmissionGroups.size(); i++)
            {
                if (m_vecAdmissionGroups[i]->hasConditions())
                {
                    basar::VarString sqlSelect = m_vecAdmissionGroups[i]->getSql(m_ArticleNo, m_BranchNo);
                    BLOG_INFO_STREAM(m_Logger, sqlSelect.c_str());

                    basar::db::sql::ResultsetRef resultSet = m_pAdmissionGroupsDM->executeqry(sqlSelect);
                    while (resultSet.next())
                    {
                        basar::Decimal id = resultSet.getDecimal(0);
                        if (id.toInt32() > 0)
                        {
                            paramgroupid = m_vecAdmissionGroups[i]->Id();
                            return paramgroupid;
                        }
                    }
                }
            }
        }
        catch (basar::Exception&)
        {
            throw;
        }
    }

    BLOG_TRACE(m_Logger, "AdmissionConsiderGroupsUC::assignAdmGroups() END");
    return paramgroupid;
}

} // namespace AdmissionConsiderGroup
} // namespace useCase
} // namespace mainwarehousearticlesrelevantcalculator