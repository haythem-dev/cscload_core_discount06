#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_USECASE_MAINUC_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_USECASE_MAINUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "componentmanager/subsequentdeliveryrelevantcalculatorapplcompmgrptr.h"
#include "componentmanager/iusecasegetterptr.h"

#include <domainmodule/article/articledm.h>
#include <domainmodule/deliveryparam/deliveryparamdm.h>
#include <domainmodule/subsequentdeliveryconfig/subsequentdeliveryconfigdm.h>

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
namespace subsequentdeliveryrelevantcalculator
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

                void                                        injectUseCaseGetter(subsequentdeliveryrelevantcalculator::componentManager::IUseCaseGetterPtr useCaseGetter);
				void										injectArticleDM(domMod::article::ArticleDMPtr articleDM);
				void										injectDeliveryParamDM(domMod::deliveryparam::DeliveryParamDMPtr deliveryParamsDM);
				void										injectSubsequentDeliveryConfigDM(domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDMPtr subsequentDeliveryConfigDM);
				void                                        setBranchNo(basar::Int16 branchNo) { m_branchNo = branchNo; }
				void                                        setAbortType(basar::Int16 abortType) { m_abortType = abortType; }
				void                                        setAbortArticleNo(basar::Int32 abortArticleNo) { m_abortArticleNo = abortArticleNo; }
                void                                        setCalcDate(basar::Date calcDate) { m_CalcDate = calcDate; }
                void                                        setCalcTime(basar::Time calcTime) { m_CalcTime = calcTime; }
				virtual void		                        run();

            private:
                MainUC(const MainUC& );
                MainUC& operator= (const MainUC& );

                subsequentdeliveryrelevantcalculator::componentManager::IUseCaseGetterPtr  getUseCaseGetter();

				domMod::article::ArticleDMPtr	                                        getArticleDM();
				domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDMPtr         getSubsequentDeliveryConfigDM();
				domMod::deliveryparam::DeliveryParamDMPtr								getDeliveryParamDM();

				basar::Int16                                                            getBranchNo() const { return m_branchNo; };
				basar::Int16                                                            getAbortType() const { return m_abortType; };
				basar::Int32                                                            getAbortArticleNo() const { return m_abortArticleNo; };
                basar::Date                                                             getCalcDate() const { return m_CalcDate; };
                basar::Time                                                             getCalcTime() const { return m_CalcTime; };

                //////////////////////////////////////////////////////////////////////////////////////
                // member variables
                //////////////////////////////////////////////////////////////////////////////////////
                const log4cplus::Logger&								        m_Logger;
                subsequentdeliveryrelevantcalculator::componentManager::IUseCaseGetterPtr m_UseCaseGetter;

				domMod::article::ArticleDMPtr									m_ArticleDM;
				domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDMPtr m_SubsequentDeliveryConfigDM;
				domMod::deliveryparam::DeliveryParamDMPtr						m_DeliveryParamDM;
				basar::Int16                                                    m_branchNo;
				basar::Int16                                                    m_abortType;
				basar::Int32                                                    m_abortArticleNo;
                basar::Date                                                     m_CalcDate;
                basar::Time                                                     m_CalcTime;
		};
    } // namespace useCase
} // namespace subsequentdeliveryrelevantcalculator

#endif //end GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_USECASE_MAINUC_H
