#ifndef GUARD_EXPORTARTICLECALCULATOR_USECASE_MAINUC_H
#define GUARD_EXPORTARTICLECALCULATOR_USECASE_MAINUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "componentmanager/exportarticlecalculatorapplcompmgrptr.h"
#include "componentmanager/iusecasegetterptr.h"

#include <domainmodule/iexportexclusionparameterdmptr.h>
#include <domainmodule/iexportarticledmptr.h>
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
namespace exportarticlecalculator
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

                void                                        injectUseCaseGetter( exportarticlecalculator::componentManager::IUseCaseGetterPtr useCaseGetter);
                void										injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert );
				void										injectExportExclusionParameterDM( domMod::exportexclusionparameter::IExportExclusionParameterDMPtr exportExclsuionParameterDM );
				void										injectExportArticleDM( domMod::exportarticle::IExportArticleDMPtr exportArticleDM );
				virtual void                                run();

            private:
                MainUC(const MainUC& );
                MainUC& operator= (const MainUC& );

                exportarticlecalculator::componentManager::IUseCaseGetterPtr            getUseCaseGetter();
				infrastructure::mail::IMailAlertPtr										getMailAlert();

				void																	sendMail(basar::cmnutil::CollBString& errorList, const bool isError = true);
				void																	logExclusionParameter();
				bool																	checkForExportExclusion(basar::VarString articleVal, 
																												basar::db::aspect::AccessorPropertyTable_YIterator yitParam);
				bool																	mapAndCheckRuleIdVsArticleVal(basar::db::aspect::AccessorPropertyTable_YIterator yitParam);
		
				domMod::exportexclusionparameter::IExportExclusionParameterDMPtr		getExportExclusionParameterDM();
				domMod::exportarticle::IExportArticleDMPtr								getExportArticleDM();
				
                //////////////////////////////////////////////////////////////////////////////////////
                // member variables
                //////////////////////////////////////////////////////////////////////////////////////
                const log4cplus::Logger&												m_Logger;
                exportarticlecalculator::componentManager::IUseCaseGetterPtr            m_UseCaseGetter;

				infrastructure::mail::IMailAlertPtr										m_MailAlert;

				domMod::exportexclusionparameter::IExportExclusionParameterDMPtr		m_ExportExclusionParameterDM; // only read once per branch, resultset is collection of several parameter rows!
				domMod::exportarticle::IExportArticleDMPtr								m_ExportArticleDM; // read + write via prepared statements
		};
    } // namespace useCase
} // namespace exportarticlecalculator

#endif //end GUARD_EXPORTARTICLECALCULATOR_USECASE_MAINUC_H
