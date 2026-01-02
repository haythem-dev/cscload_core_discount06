#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_TURNOVERDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_TURNOVERDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "iturnoverfinder.h"

#include "domainmodule/customerorder/icustomerordercollectionfinderptr.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace turnover
{

    class TurnoverDM : public ITurnoverFinder
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        TurnoverDM();
        ~TurnoverDM();

        void                                                        injectCustomerInvoiceCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr );
        void                                                        injectCustomerOrderCollectionFinder( customerOrder::ICustomerOrderCollectionFinderPtr );

        // from ITurnover interface
        void                                                        findByPartnerNo( basar::Int32 partnerNo );

        basar::Decimal                                              getTurnoverDay()     const;
        basar::Decimal                                              getTurnoverMonth()   const;
        basar::Decimal                                              getSumReclamations() const;
        basar::Decimal                                              getSumReturns()      const;

    private:
        // forbidden
        TurnoverDM( const TurnoverDM& );
        TurnoverDM& operator = ( const TurnoverDM& );
        
        const log4cplus::Logger&                                    getLogger() const;
        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        customerOrder::ICustomerOrderCollectionFinderPtr            getCustomerOrderCollectionFinder() const;
        
        void                                                        resetSearchYit();
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
        basar::db::aspect::AccessorPropertyTable_YIterator          getSearchYit();

        basar::db::aspect::AccessorPropertyTableRef                 get() const;

        void                                                        calculateTurnover();

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
        customerOrder::ICustomerOrderCollectionFinderPtr            m_CustomerOrderCollectionFinder;

        basar::Decimal                                              m_TurnoverMonth;
        basar::Decimal                                              m_SumReturns;
        basar::Decimal                                              m_SumReclamations;
    };

} // end namespace turnover
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_TURNOVERDM_H
