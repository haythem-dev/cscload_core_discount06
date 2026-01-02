#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_CUSTOMERINVOICINGCOLLECTIONDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_CUSTOMERINVOICINGCOLLECTIONDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "icustomerinvoicingcollection.h"

#include "componentmanager/icustomerinvoiceconnectedfactoryptr.h"

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
namespace customerInvoice
{
    class CustomerInvoicingCollectionDM : public ICustomerInvoicingCollection
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        CustomerInvoicingCollectionDM();
        ~CustomerInvoicingCollectionDM();

        void injectCustomerInvoicingCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr );
        void injectCustomerInvoiceFactory( componentManager::ICustomerInvoiceConnectedFactoryPtr );

        // from ICustomerInvoicingCollection interface
        basar::db::aspect::AccessorPropertyTableRef                 get()     const;
        bool                                                        isEmpty() const;

        void                                                        readCollection();
        void                                                        save();

    private:
        // forbidden
        CustomerInvoicingCollectionDM( const CustomerInvoicingCollectionDM& );
        CustomerInvoicingCollectionDM& operator = ( const CustomerInvoicingCollectionDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        //libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
        componentManager::ICustomerInvoiceConnectedFactoryPtr       getCustomerInvoiceFactory();
        ICustomerInvoicePtr                                         getCustomerInvoice( basar::db::aspect::AccessorPropertyTable_YIterator );
                    
        const log4cplus::Logger&                                    getLogger() const;
        void                                                        backup() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        //libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
        componentManager::ICustomerInvoiceConnectedFactoryPtr       m_CustomerInvoiceFactory;
    };

} // end namespace customerInvoice
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_CUSTOMERINVOICINGCOLLECTIONDM_H
