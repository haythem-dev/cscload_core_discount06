#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_CUSTOMERORDERCOLLECTIONDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_CUSTOMERORDERCOLLECTIONDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "icustomerordercollectionfinder.h"

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
namespace customerOrder
{
    class CustomerOrderCollectionDM : public ICustomerOrderCollectionFinder
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        CustomerOrderCollectionDM();
        ~CustomerOrderCollectionDM();

        void injectCustomerOrderCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from ICustomerOrderCollectionFinder interface
        basar::db::aspect::AccessorPropertyTableRef                 get()     const;
        bool                                                        isEmpty() const;

        void                                                        findByPartnerNo( basar::Int32 );
        basar::Decimal                                              getDeliveryValue();

    private:
        // forbidden
        CustomerOrderCollectionDM( const CustomerOrderCollectionDM& );
        CustomerOrderCollectionDM& operator = ( const CustomerOrderCollectionDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();

        void                                                        resetSearchYit();
        basar::db::aspect::AccessorPropertyTable_YIterator          getSearchYit();
                    
        const log4cplus::Logger&                                    getLogger() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
    };

} // end namespace customerOrder
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_CUSTOMERORDERCOLLECTIONDM_H
