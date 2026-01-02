#ifndef GUARD_FMDRELEVANTCALCULATOR_USECASE_MAINUC_H
#define GUARD_FMDRELEVANTCALCULATOR_USECASE_MAINUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "componentmanager/fmdrelevantcalculatorapplcompmgrptr.h"
#include "componentmanager/iusecasegetterptr.h"

#include <domainmodule/ifmddeterminationparameterdmptr.h>
#include <domainmodule/ifmdrelevantdmptr.h>
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
namespace fmdrelevantcalculator
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

                void                                        injectUseCaseGetter( fmdrelevantcalculator::componentManager::IUseCaseGetterPtr useCaseGetter);
                void										injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert );
				void										injectFmdDeterminationParameterDM( domMod::fmddeterminationparameter::IFmdDeterminationParameterDMPtr fmdExclsuionParameterDM );
				void										injectFmdRelevantDM( domMod::fmdarticle::IFmdRelevantDMPtr FmdRelevantDM );
				virtual void                                run();

            private:
                MainUC(const MainUC& );
                MainUC& operator= (const MainUC& );

                fmdrelevantcalculator::componentManager::IUseCaseGetterPtr          getUseCaseGetter();
				infrastructure::mail::IMailAlertPtr									getMailAlert();

				void																sendMail(basar::cmnutil::CollBString& errorList, const bool isError = true);
				void																logDeterminationParameter();
				basar::Int16														mapAndCheckRuleIdVsArticleVal(basar::db::aspect::AccessorPropertyTable_YIterator yitParam);
				
				void																CheckCompareStartValueIsNotNull(basar::VarString compareStartVal, basar::Int16 ruleId);
				bool															CheckCaseIfa(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseDc(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseBlacklist(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseWhitelist(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseArzneimittel(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseRezeptPfl(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseExceptionType2(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseTierarznei(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseHomoeopathikum(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseMedizinischeGase(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);
				bool															CheckCaseAtcCodeMatching(basar::db::aspect::AccessorPropertyTable_YIterator rulesIterator);

				domMod::fmddeterminationparameter::IFmdDeterminationParameterDMPtr	getFmdDeterminationParameterDM();
				domMod::fmdarticle::IFmdRelevantDMPtr								getFmdArticleDM();
				
                //////////////////////////////////////////////////////////////////////////////////////
                // member variables
                //////////////////////////////////////////////////////////////////////////////////////
                const log4cplus::Logger&											m_Logger;
                fmdrelevantcalculator::componentManager::IUseCaseGetterPtr          m_UseCaseGetter;
				bool																m_isRezeptpflActive;
				bool																m_isIfaOrDcArticle;

				infrastructure::mail::IMailAlertPtr									m_MailAlert;

				domMod::fmddeterminationparameter::IFmdDeterminationParameterDMPtr	m_FmdDeterminationParameterDM; // only read once per branch, resultset is collection of several parameter rows!
				domMod::fmdarticle::IFmdRelevantDMPtr								m_FmdRelevantDM; // read + write via prepared statements
		};
    } // namespace useCase
} // namespace fmdrelevantcalculator

#endif //end GUARD_FMDRELEVANTCALCULATOR_USECASE_MAINUC_H
