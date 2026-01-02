#ifndef GUARD_CSC_PHADEX_DOMMOD_TASK_CONTROL_DM_H
#define GUARD_CSC_PHADEX_DOMMOD_TASK_CONTROL_DM_H

#include "itaskcontrol.h"
#include <libbasardbsql_connectionref.h>
#include <libutil/util.h>

namespace csc_phadex
{
namespace domMod
{
class TaskControlDM : public ITaskControl
{
public:
	TaskControlDM();
	virtual ~TaskControlDM();

	void injectConnection( const basar::db::sql::ConnectionRef );
	void setConfig( const basar::Int16 branchno, const basar::VarString & applicationName );

	virtual void heartBeat( const basar::Int16 branchno, const basar::VarString & applicationName );
	virtual void heartBeat();

private:
	TaskControlDM( const TaskControlDM & );
	TaskControlDM & operator = ( const TaskControlDM & );

	const log4cplus::Logger &			m_Logger;
	basar::db::sql::ConnectionRef		m_Connection;
	basar::Int16						m_Branchno;
	basar::VarString					m_ApplicationName;
	basar::Int32						m_MaxTimeout;
};

} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_TASK_CONTROL_DM_H
