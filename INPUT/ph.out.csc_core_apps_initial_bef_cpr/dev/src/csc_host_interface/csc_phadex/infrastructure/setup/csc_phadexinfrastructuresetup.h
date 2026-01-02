#ifndef GUARD_CSC_PHADEX_INFRASTRUCTURE_SETUP_CSC_PHADEXINFRASTRUCTURESETUP_H
#define GUARD_CSC_PHADEX_INFRASTRUCTURE_SETUP_CSC_PHADEXINFRASTRUCTURESETUP_H

#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/icsc_phadexlogingetterptr.h"
#include <infrastructure/config/phadexconfigstruct.h>

namespace csc_phadex
{
namespace infrastructure
{
namespace setup
{
class CscPhadexInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
{
public:
    CscPhadexInfrastructureSetup();
	virtual ~CscPhadexInfrastructureSetup();
        	    
    void injectLoginGetter( ICscPhadexLoginGetterConstPtr );
	//void injectTCAConnection( libutil::infrastructure::db::dbConnection::IDBConnectionPtr tcaConnection );
	basar::db::aspect::ConnectionRef getCICSConnection();
	libutil::infrastructure::db::dbConnection::IDBConnectionPtr getDBConnection();
	const PhadexConfigStruct & getConfig() const;

protected:
    virtual void doInit();
	virtual void doShutdown();
        	    
private:
    CscPhadexInfrastructureSetup( const CscPhadexInfrastructureSetup& r );
	CscPhadexInfrastructureSetup& operator=( const CscPhadexInfrastructureSetup& r );

	void readXMLConfig();
    void login();
    void prepareLogin();
	void establishTCAConnection();
	void releaseTCAConnection();
	const libutil::infrastructure::db::dbConnection::DBServerInfo getDBServerInfo() const;
	const libutil::infrastructure::db::dbConnection::DBServerInfo getCICSServerInfo() const;

    ICscPhadexLoginGetterConstPtr									m_CscPhadexLoginGetter;
	//libutil::infrastructure::db::dbConnection::IDBConnectionPtr		m_TCAConnection;
	basar::db::aspect::ConnectionRef								m_CICSConnection;
	PhadexConfigStruct												m_Config;
};
}
}
}

#endif
