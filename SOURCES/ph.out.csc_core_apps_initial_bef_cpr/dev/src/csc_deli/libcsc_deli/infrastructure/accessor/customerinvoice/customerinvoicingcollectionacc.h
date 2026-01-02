#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICINGCOLLECTIONACC_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICINGCOLLECTIONACC_H

#include "infrastructure/accessor/accessorbase/accessorbase.h"
#include "infrastructure/parameter/iaccparameterptr.h"

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace customerInvoice
{

    class CustomerInvoicingCollectionACC : public AccessorBase
    {
    public:
        CustomerInvoicingCollectionACC();
        ~CustomerInvoicingCollectionACC();

        void                                       injectACCParameter( parameter::IACCParameterPtr );

        const basar::db::aspect::ExecuteResultInfo readCustomerInvoiceCollection( basar::db::aspect::AccessorPropertyTable_YIterator, 
                                                                                  bool flagExcept );
        const basar::db::aspect::ExecuteResultInfo backupFiles( basar::db::aspect::AccessorPropertyTable_YIterator, bool flagExcept );

    private:
        void                                       checkFileExisting( const basar::VarString& filePath ) const;

        const log4cplus::Logger&                   getLogger() const;
        parameter::IACCParameterPtr                getAccParameter()   const;

        basar::db::aspect::ExecuteResultInfo       readCustomerInvoiceCollectionFromFile( const basar::VarString& filePath );

        // helper
        basar::VarString                           stripLeadingZeros( const basar::VarString& ) const;

        // overridden
        void                                       registerAccessorMethods( AccMethodCaller& );
        void                                       setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef ) const;

    private:
        static const std::size_t                   m_RowSize = 8; // equals number of separators + 1 (semicolons) in file

        const log4cplus::Logger&                   m_Logger;
        parameter::IACCParameterPtr                m_AccParameter;
    };

} // end namespace customerInvoice
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICINGCOLLECTIONACC_H
