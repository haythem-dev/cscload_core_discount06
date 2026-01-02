//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief 
 *  \author 
 *  \date 
 *  \version 
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHATRA_CSC_HEARTBEAT_H
#define GUARD_CSC_PHATRA_CSC_HEARTBEAT_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "ipxvbsessionptr.h"
#include "ipxvbdbconnectionptr.h"
#include "icsc_heartbeat.h"
#include <icsc_loggerptr.h>
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra
{

    class CSC_HeartBeat : public ICSC_HeartBeat
    {
        public:
            CSC_HeartBeat(domMod::pharmosTransaction::pxVerbund::IPXVBSessionPtr ipxvbsp, domMod::pharmosTransaction::pxVerbund::IPXVBDBConnectionPtr ipxvbdbcp, libcsc_utils::ICSC_LoggerPtr csc_logger, const basar::VarString& appName, basar::Int16 branchno);
            ~CSC_HeartBeat();

            void emitHeartBeat();

        private:
            CSC_HeartBeat (const CSC_HeartBeat & );
		    CSC_HeartBeat& operator= (const CSC_HeartBeat & );
            
            domMod::pharmosTransaction::pxVerbund::IPXVBSessionPtr m_PXVBSession;
            domMod::pharmosTransaction::pxVerbund::IPXVBDBConnectionPtr  m_PXVBDBConnection;
            libcsc_utils::ICSC_LoggerPtr m_csc_logger;
            basar::VarString m_ApplicationName;
            basar::Int16 m_BranchNo;
    };
}


#endif //GUARD_CSC_PHATRA_CSC_HEARTBEAT_H

