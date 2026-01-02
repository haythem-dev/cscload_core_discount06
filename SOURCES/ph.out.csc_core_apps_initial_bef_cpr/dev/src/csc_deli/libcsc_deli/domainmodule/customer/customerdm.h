#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_CUSTOMERDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_CUSTOMERDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "icustomerfinder.h"

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
namespace customer
{
    class CustomerDM : public ICustomerFinder
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        CustomerDM();
        ~CustomerDM();

        void injectCustomerAccessor( libutil::infrastructure::accessor::IAccessorPtr );

        // from ICustomerFinder interface
        basar::db::aspect::AccessorPropertyTable_YIterator          get()     const;
        bool                                                        isEmpty() const;

        void                                                        findByPartnerNo( basar::Int32 );

    private:
        // forbidden
        CustomerDM( const CustomerDM& );
        CustomerDM& operator = ( const CustomerDM& );

        libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
        libutil::domMod::SearchYIteratorPtr                         getSearchYIterator();
                    
        const log4cplus::Logger&                                    getLogger() const;

    private:
        const log4cplus::Logger&                                    m_Logger;
        libutil::domMod::SearchYIteratorPtr                         m_SearchYIterator;
        libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
    };

} // end namespace customer
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_CUSTOMERDM_H
