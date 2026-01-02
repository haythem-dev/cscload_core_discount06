#ifndef GUARD_IBTRELEVANTCALCULATOR_USECASE_MAINUC_H
#define GUARD_IBTRELEVANTCALCULATOR_USECASE_MAINUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "componentmanager/ibtrelevantcalculatorapplcompmgrptr.h"
#include "componentmanager/iusecasegetterptr.h"

#include <domainmodule/iibtrelevantbranchparameterdmptr.h>
#include <domainmodule/iibtrelevantparameterdmptr.h>
#include <domainmodule/iibtarticledmptr.h>
#include <infrastructure/mail/imailalertptr.h>
#include "articlebasevaluesptr.h"
#include "excludeparametervaluesptr.h"
#include "branchrelevancevaluesptr.h"

#include <libutil/irunnable.h>

#include <libbasarcmnutil_bstring.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
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

                void                                        injectUseCaseGetter( ibtrelevantcalculator::componentManager::IUseCaseGetterPtr useCaseGetter);
                void										injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert );
				void										injectIbtRelevantParameterDM( domMod::ibtRelevantParameter::IIbtRelevantParameterDMPtr ibtRelevantParameterDM );
				void										injectIbtRelevantBranchParameterDM( domMod::ibtRelevantBranchParameter::IIbtRelevantBranchParameterDMPtr ibtRelevantBranchParameterDM );
				void										injectIbtArticleDM( domMod::ibtArticle::IIbtArticleDMPtr ibtArticleDM );
				virtual void                                run();

            private:
                MainUC(const MainUC& );
                MainUC& operator= (const MainUC& );

                ibtrelevantcalculator::componentManager::IUseCaseGetterPtr              getUseCaseGetter();
				infrastructure::mail::IMailAlertPtr										getMailAlert();

				void																	sendMail(basar::cmnutil::CollBString& errorList, const bool isError = true);
		
				domMod::ibtRelevantParameter::IIbtRelevantParameterDMPtr				getIbtRelevantParameterDM();
				domMod::ibtRelevantBranchParameter::IIbtRelevantBranchParameterDMPtr	getIbtRelevantBranchParameterDM();
				domMod::ibtArticle::IIbtArticleDMPtr									getIbtArticleDM();
				int																		checkisRegionalIbt(ArticleBaseValuesPtr articleData);
				bool																	calcIbtRelevance(ArticleBaseValuesPtr articleData, ExcludeParameterValuesPtr paramData);
				basar::Int32															calcAssortmentType(ArticleBaseValuesPtr articleData);

                //////////////////////////////////////////////////////////////////////////////////////
                // member variables
                //////////////////////////////////////////////////////////////////////////////////////
                const log4cplus::Logger&												m_Logger;
                ibtrelevantcalculator::componentManager::IUseCaseGetterPtr              m_UseCaseGetter;

				infrastructure::mail::IMailAlertPtr										m_MailAlert;
				
				domMod::ibtRelevantBranchParameter::IIbtRelevantBranchParameterDMPtr			m_IbtRelevantBranchParameterDM;
				domMod::ibtRelevantParameter::IIbtRelevantParameterDMPtr				m_IbtRelevantParameterDM; // only read once per branch, resultset is collection of several parameter rows!
				domMod::ibtArticle::IIbtArticleDMPtr									m_IbtArticleDM; // read + write via prepared statements
		};
    } // namespace useCase
} // namespace ibtrelevantcalculator

#endif //end GUARD_IBTRELEVANTCALCULATOR_USECASE_MAINUC_H
