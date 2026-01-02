#ifndef GUARD_CSC_PHADEX_USECASE_MAINUC_H
#define GUARD_CSC_PHADEX_USECASE_MAINUC_H

#include "componentmanager/csc_phadexapplcompmgrptr.h"
#include "componentmanager/iusecasegetterptr.h"
#include "domainmodule/taskcontrol/itaskcontrolptr.h"
#include <libbasar_definitions.h>
#include <libutil/irunnable.h>
#include <libutil/irunnableptr.h>
#include <csc_signalhandler.h>
#include <isignalreceiver.h>

namespace basar
{
namespace appl
{
class IEventSource;
struct EventReturnStruct;
}
}

namespace basar
{
namespace db
{
namespace aspect
{
	class AccessorPropertyTable_YIterator;
	class Manager;
}
}
}

namespace log4cplus
{
	class Logger;
}

namespace csc_phadex
{
namespace useCase
{
class MainUC : public libutil::useCase::IRunnable,
			   public libcsc_utils::ISignalReceiver
{
public:
	MainUC();
	virtual ~MainUC();

	void injectUseCaseGetter( csc_phadex::componentManager::IUseCaseGetterPtr useCaseGetter );
	void injectTaskControl( csc_phadex::domMod::ITaskControlPtr );
	void setSleepDuration( const basar::Int32 milliSeconds );
	void setNoCICS(const bool noCICS);
	virtual void run();
	virtual void receiveSignal( int signal );

private:
	MainUC(	const MainUC & );
	MainUC & operator= ( const MainUC & );

	void doRunWithCICS();
	void doRunWithoutCICS();

	csc_phadex::componentManager::IUseCaseGetterPtr getUseCaseGetter();
	void checkConnections();
	void processSleep();

	const log4cplus::Logger &							m_Logger;
	csc_phadex::componentManager::IUseCaseGetterPtr		m_UseCaseGetter;
	csc_phadex::domMod::ITaskControlPtr					m_TaskControl;
	libcsc_utils::CSC_SignalHandler                     m_SignalHandler;
	bool												m_ExitGraceful;
	basar::Int32										m_SleepDuration;
	bool												m_NoCICS;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_MAINUC_H
