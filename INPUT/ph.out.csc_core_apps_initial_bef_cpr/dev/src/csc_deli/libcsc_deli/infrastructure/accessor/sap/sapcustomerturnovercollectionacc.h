#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPCUSTOMERTURNOVERCOLLECTIONACC_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPCUSTOMERTURNOVERCOLLECTIONACC_H

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

    class SAPCustomerTurnoverCollectionACC : public AccessorBase
    {
    public:
        SAPCustomerTurnoverCollectionACC();
        ~SAPCustomerTurnoverCollectionACC();

        void                                       injectACCParameter( parameter::IACCParameterPtr );

        const basar::db::aspect::ExecuteResultInfo writeCustomerTurnoverCollection( basar::db::aspect::AccessorPropertyTable_YIterator, 
                                                                                    bool flagExcept );

    private:
        const log4cplus::Logger&                   getLogger() const;
        parameter::IACCParameterPtr                getAccParameter()   const;

        // overridden
        void                                       registerAccessorMethods( AccMethodCaller& );
        void                                       setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef ) const;

    private:
        const log4cplus::Logger&                   m_Logger;
        parameter::IACCParameterPtr                m_AccParameter;
    };

} // end namespace sap
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPCUSTOMERTURNOVERCOLLECTIONACC_H
