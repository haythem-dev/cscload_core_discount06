/*
 * This class wrapps pxverbund cremaMailHandler to be usable in obst2.0 program
 */

#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITMAILDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITMAILDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "idebtlimitmailprocessor.h"

#include <pxsessionptr.h> // from pxverbund
#include "pxcremamailhandlerptr.h"

#include <libutil/classinfo.h>
#include <libutil/parameter.h>
#include <libutil/session.h>
#include <libutil/util.h>

#include <libbasardbsql_connectionref.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
class pxSessionInitialization;

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace debtLimit
{
    class DebtLimitMailDM : public IDebtLimitMailProcessor
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        DebtLimitMailDM();
        ~DebtLimitMailDM();

        void                                                        injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr );
        void                                                        injectConnection      ( basar::db::sql::ConnectionRef );
        void                                                        setSession            ( libutil::infrastructure::session::ISessionPtr );

        // from IDebtLimitMailProcessor interface
        void                                                        processCremaMails( basar::Int32 partnerNo );

    private:
        // forbidden
        DebtLimitMailDM( const DebtLimitMailDM& );
        DebtLimitMailDM& operator = ( const DebtLimitMailDM& );
                    
        const log4cplus::Logger&                                    getLogger() const;
        libutil::infrastructure::parameter::IParameterGatewayPtr    getParameterGateway();
        basar::db::sql::ConnectionRef                               getConnection();
        libutil::infrastructure::session::ISessionPtr               getSession();
        PxSessionPtr                                                getPxSession();
        PxCremaMailHandlerPtr                                       getPxCremaMailHandler();

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::infrastructure::parameter::IParameterGatewayPtr    m_ParameterGateway;
        basar::db::sql::ConnectionRef                               m_Connection;
        libutil::infrastructure::session::ISessionPtr               m_Session;
        PxSessionPtr                                                m_PxSession;
        PxCremaMailHandlerPtr                                       m_PxCremaMailHandler;
    };

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITMAILDM_H
