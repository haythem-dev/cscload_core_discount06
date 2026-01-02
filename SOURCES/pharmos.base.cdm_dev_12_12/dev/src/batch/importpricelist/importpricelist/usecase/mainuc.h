#ifndef GUARD_IMPORTPRICELIST_USECASE_MAINUC_H
#define GUARD_IMPORTPRICELIST_USECASE_MAINUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <set>
#include <boost/ptr_container/ptr_list.hpp>

#include "componentmanager/importpricelistapplcompmgrptr.h"
#include "componentmanager/iusecasegetterptr.h"

#include <domainmodule/articlecodes/articlecodesdm.h>
#include <domainmodule/pricedata/pricedatadm.h>
#include "domainmodule/pricelist/pricelistvalidator.h"
#include <domainmodule/pricelist2pharmacygroup/pricelist2pharmacygroupdm.h>
#include <domainmodule/pricelistproc/pricelistprocdm.h>

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
namespace importpricelist
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

                void                                        injectUseCaseGetter( importpricelist::componentManager::IUseCaseGetterPtr useCaseGetter);
				void										injectPriceDataDM( domMod::pricedata::PriceDataDMPtr priceDataDM );
				void										injectPriceList2PharmacyGroupDM(domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDMPtr priceList2PharmacyGroupDM);
				void										injectPriceListProcDM(domMod::pricelistproc::PriceListProcDMPtr priceListProcDM);
				void										injectArticleCodesDM(domMod::articlecodes::ArticleCodesDMPtr articleCodesDM);
				void                                        setInputFileName(const basar::VarString& inputFileName) { m_inputFileName = inputFileName; };
				void                                        setProcDate(const basar::Date& procDate) { m_procDate = procDate; }
				void                                        setAbortType(basar::Int16 abortType) { m_abortType = abortType; }
				void                                        setAbortArticleNo(basar::Int32 abortArticleNo) { m_abortArticleNo = abortArticleNo; }
				virtual void		                        run();

            private:
                MainUC(const MainUC& );
                MainUC& operator= (const MainUC& );

                importpricelist::componentManager::IUseCaseGetterPtr            getUseCaseGetter();

				bool                                                                    validatePriceList(const basar::VarString& listPath, 
					                                                                                      domMod::pricelist::ListHeaderData& listHeader,
					                                                                                      boost::ptr_list<domMod::pricelist::ListPriceData>& listPrices,
                                                                                       					  domMod::pricelist::ListControlData& listControl);
				void                                                                    processPriceList(const basar::VarString& listPath,
					                                                                                     const domMod::pricelist::ListHeaderData& listHeader,
					                                                                                     const boost::ptr_list<domMod::pricelist::ListPriceData>& listPrices,
                                                                                              			 const domMod::pricelist::ListControlData& listControl);
				bool                                                                    validatePriceListHeader(const basar::VarString& filePath, const domMod::pricelist::ListHeaderData& listHeaderData, basar::Int32 procDate);
				void                                                                    selectArticlesWithValidPrices(basar::Int32 pharmacyGroupId, basar::Int32 dateFrom, std::set<basar::Int32>& articles);
				void                                                                    cleanupPrices(basar::Int32 pharmacyGroupId, basar::Int32 newValidityDate);
				void                                                                    cleanupPricesForNotIncludedArticles(basar::Int32 pharmacyGroupId, basar::Int32 newValidityDate, const std::set<basar::Int32>& articles);
				void                                                                    invalidatePrices(basar::Int32 pharmacyGroupId, basar::Int32 newValidToDate);
				void                                                                    deleteFuturePrices(basar::Int32 pharmacyGroupId, basar::Int32 dateDeleteAfter);
				void                                                                    cleanupPricesForArticle(basar::Int32 pharmacyGroupId, basar::Int32 articleNo, basar::Int32 newValidityDate);
				void                                                                    invalidatePricesForArticle(basar::Int32 pharmacyGroupId, basar::Int32 articleNo, basar::Int32 newValidToDate);
				void                                                                    deleteFuturePricesForArticle(basar::Int32 pharmacyGroupId, basar::Int32 articleNo, basar::Int32 dateDeleteAfter);
				void                                                                    createPriceListProcRejected(const basar::VarString& fileName,
                                                                                                			        const basar::Int32 pharmacyGroupId,
					                                                                                                const basar::Int32 procDate,
					                                                                                                const domMod::pricelist::ListHeaderData& listHeaderData);
				void                                                                    createPriceListProcEntry(const basar::VarString& fileName,
					                                                                                             const basar::Int32 pharmacyGroupId, 
					                                                                                             const basar::Int32 procDate,
					                                                                                             const domMod::pricelist::ListHeaderData& listHeaderData,
					                                                                                             const domMod::pricelist::ListControlData& listControlData,
					                                                                                             domMod::pricelistproc::PriceListProc& priceListProc);
				void                                                                    updatePriceListProcEntry(const domMod::pricelistproc::PriceListProc& priceListProc);
				void                                                                    getPharmacyGroupForPriceList(basar::Int32 priceListId, domMod::pricelist2pharmacygroup::PriceList2PharmacyGroup& priceList2PharmacyGroup);
				void                                                                    reportPricesNotInZArtikel(basar::Int32 priceListId, basar::Int32 pharmacyGroupId, basar::Int32 dateFrom);
				basar::Int32                                                            getArticleNoFromPZN(basar::Int32 pzn);
				domMod::pricedata::PriceDataDMPtr		                                getPriceDataDM();
				domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDMPtr           getPriceList2PharmacyGroupDM();
				domMod::pricelistproc::PriceListProcDMPtr						        getPriceListProcDM();
				domMod::articlecodes::ArticleCodesDMPtr							        getArticleCodesDM();
				basar::VarString                                                        getInputFileName() const { return m_inputFileName; };
				basar::Date                                                             getProcDate() const { return m_procDate; };
				basar::Int16                                                            getAbortType() const { return m_abortType; };
				basar::Int32                                                            getAbortArticleNo() const { return m_abortArticleNo; };

                //////////////////////////////////////////////////////////////////////////////////////
                // member variables
                //////////////////////////////////////////////////////////////////////////////////////
                const log4cplus::Logger&								        m_Logger;
                importpricelist::componentManager::IUseCaseGetterPtr            m_UseCaseGetter;

				domMod::pricedata::PriceDataDMPtr                               m_PriceDataDM;
				domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDMPtr   m_PriceList2PharmacyGroupDM;
				domMod::pricelistproc::PriceListProcDMPtr                       m_PriceListProcDM;
				domMod::articlecodes::ArticleCodesDMPtr                         m_ArticleCodesDM;
				basar::VarString                                                m_inputFileName;
				basar::Date                                                     m_procDate;
				basar::Int16                                                    m_abortType;
				basar::Int32                                                    m_abortArticleNo;
		};
    } // namespace useCase
} // namespace importpricelist

#endif //end GUARD_IMPORTPRICELIST_USECASE_MAINUC_H
