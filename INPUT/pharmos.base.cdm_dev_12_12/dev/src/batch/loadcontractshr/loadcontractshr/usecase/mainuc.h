#ifndef GUARD_LOADCONTRACTSHR_USECASE_MAINUC_H
#define GUARD_LOADCONTRACTSHR_USECASE_MAINUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "componentmanager/loadcontractshrapplcompmgrptr.h"
#include "componentmanager/iusecasegetterptr.h"

//#include <domainmodule/ifmddeterminationparameterdmptr.h>
#include <domainmodule/iloadcontractshrdmptr.h>
#include <infrastructure/mail/imailalertptr.h>

#include <libutil/irunnable.h>

#include <libbasarcmnutil_bstring.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace log4cplus
{
    class Logger;
}

namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
        }
    }
}


//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace loadcontractshr
{
    namespace useCase
    {
		//-------------------------------------------------------------------------------------------------//
        // class declaration
        //-------------------------------------------------------------------------------------------------//
        class MainUC : public libutil::useCase::IRunnable
        {
            public:
                MainUC();
                virtual ~MainUC();
                void                                        injectUseCaseGetter( loadcontractshr::componentManager::IUseCaseGetterPtr useCaseGetter);
                void										injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert );
				void										injectLoadContractsHrDM( domMod::loadcontractshrdm::ILoadContractsHrDMPtr LoadContractsHrDM );
				virtual void                                run();

            private:
                MainUC(const MainUC& );
                MainUC& operator= (const MainUC& );
                loadcontractshr::componentManager::IUseCaseGetterPtr				getUseCaseGetter();
				infrastructure::mail::IMailAlertPtr									getMailAlert();
				void																sendMail(basar::cmnutil::CollBString& errorList, const bool isError = true);	
				domMod::loadcontractshrdm::ILoadContractsHrDMPtr					getContractsLoaderDM();
				void																writeResults(std::stringstream* ss, const std::string& loc);
				
                //////////////////////////////////////////////////////////////////////////////////////
                // member variables
                //////////////////////////////////////////////////////////////////////////////////////
                const log4cplus::Logger&											m_Logger;
                loadcontractshr::componentManager::IUseCaseGetterPtr				m_UseCaseGetter;
				bool																m_isRezeptpflActive;
				bool																m_isIfaOrDcArticle;

				infrastructure::mail::IMailAlertPtr									m_MailAlert;
				domMod::loadcontractshrdm::ILoadContractsHrDMPtr							m_LoadContractsHrDM; // read + write via prepared statements
		};
    } // namespace useCase
} // namespace loadcontractshr

#endif //end GUARD_LOADCONTRACTSHR_USECASE_MAINUC_H
