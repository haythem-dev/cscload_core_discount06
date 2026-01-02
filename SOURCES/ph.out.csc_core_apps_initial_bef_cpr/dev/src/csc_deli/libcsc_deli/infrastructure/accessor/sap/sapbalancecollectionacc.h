#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPBALANCECOLLECTIONACC_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPBALANCECOLLECTIONACC_H

#include "infrastructure/accessor/accessorbase/accessorbase.h"
#include "infrastructure/parameter/iaccparameterptr.h"

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace sap
{
    class SAPBalanceCollectionACC : public AccessorBase
    {
    public:
        SAPBalanceCollectionACC();
        ~SAPBalanceCollectionACC();

        void                                       injectACCParameter( parameter::IACCParameterPtr );

        const basar::db::aspect::ExecuteResultInfo readSAPBalanceFromFile( basar::db::aspect::AccessorPropertyTable_YIterator, bool flagExcept );
        const basar::db::aspect::ExecuteResultInfo backupSAPBalanceFile  ( basar::db::aspect::AccessorPropertyTable_YIterator, bool flagExcept );

    private:
        parameter::IACCParameterPtr                getAccParameter()   const;

        // overridden
        void                                       registerAccessorMethods( AccMethodCaller& );
        void                                       setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef ) const;

    private:
        static const basar::VarString::size_type   m_LineLength = 65;
        parameter::IACCParameterPtr                m_AccParameter;
    };

} // end namespace sap
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPBALANCECOLLECTIONACC_H
