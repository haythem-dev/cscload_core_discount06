
//-----------------------------------------------------------------------------------------------------------------------------------//
// include section
//-----------------------------------------------------------------------------------------------------------------------------------//
#include "csc_heartbeat.h"
#include <icsc_logger.h>
#include "pvhx04_includes.h"
#include "ipxvbsessionptr.h"
#include "ipxvbsession.h"

namespace csc_phabor
{
	CSC_HeartBeat::CSC_HeartBeat(domMod::batchOrder::pxVerbund::IPXVBSessionPtr ipxvbsp, libcsc_utils::ICSC_LoggerPtr csc_logger, const basar::VarString& appName, basar::Int16 branchno) :
            m_PXVBSession(ipxvbsp), m_csc_logger(csc_logger), m_ApplicationName(appName), m_BranchNo(branchno)
    {
    }

    CSC_HeartBeat::~CSC_HeartBeat()
    {

    }

    void CSC_HeartBeat::emitHeartBeat()
    {
        nTime now;

        try
        {
			m_PXVBSession->get()->nDBBeginTransaction(cDBTransSet);

            pxTaskControl tc(m_PXVBSession->get(), m_BranchNo, m_ApplicationName.c_str());

            tc.TaskControl(now);

            if (!tc.IsGoodState())
            {
				m_PXVBSession->get()->nDBRollBack();
                basar::VarString msg;
                msg.format("sending of heartbeat %s failed.", m_ApplicationName.c_str());
                m_csc_logger->log(log4cplus::WARN_LOG_LEVEL, msg);

            }
            else
            {            
				m_PXVBSession->get()->nDBCommit(cDBTransSet);
                basar::VarString msg;
                msg.format("sent hearbeat %s, still alive.", m_ApplicationName.c_str());
                m_csc_logger->log(log4cplus::INFO_LOG_LEVEL, msg);
            }
        }
        catch(...)
        {
            basar::VarString msg;
            msg.format("unexpected exception sending heartbeat %s", m_ApplicationName.c_str());
            m_csc_logger->log(log4cplus::ERROR_LOG_LEVEL, msg);
        }
    }

}
