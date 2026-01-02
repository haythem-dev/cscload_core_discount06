#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_CUSTOMERINVOICEDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_CUSTOMERINVOICEDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "icustomerinvoice.h"
#include "icustomerinvoiceflag.h"

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
    class CustomerInvoiceDM : public ICustomerInvoice, public ICustomerInvoiceFlag
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        CustomerInvoiceDM();
        ~CustomerInvoiceDM();

        void                                                        injectCustomerInvoiceAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from ICustomerInvoice interface {
        basar::db::aspect::AccessorPropertyTable_YIterator          get()     const;

        void                                                        resetSearchYit();
        basar::db::aspect::AccessorPropertyTable_YIterator          getSearchYit();
        void                                                        findByPattern( basar::db::aspect::AccessorPropertyTable_YIterator );

        void                                                        createEmptyInvoice();
        bool                                                        isEmpty() const;

        void                                                        save();
        // }

        // from ICustomerInvoiceFlag interface
        void                                                        saveInvoicedFlag( basar::db::aspect::AccessorPropertyTable_YIterator );

    private:
        // forbidden
        CustomerInvoiceDM( const CustomerInvoiceDM& );
        CustomerInvoiceDM& operator = ( const CustomerInvoiceDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
        const log4cplus::Logger&                                    getLogger() const;

        bool                                                        isChanged() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
    };

} // end namespace customerInvoice
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_CUSTOMERINVOICEDM_H
