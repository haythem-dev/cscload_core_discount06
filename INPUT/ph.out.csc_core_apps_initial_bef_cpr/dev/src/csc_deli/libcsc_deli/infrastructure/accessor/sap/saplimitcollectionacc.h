#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPLIMITCOLLECTIONACC_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPLIMITCOLLECTIONACC_H

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
    class SAPLimitCollectionACC : public AccessorBase
    {
    public:
        SAPLimitCollectionACC();
        ~SAPLimitCollectionACC();

        void                                       injectACCParameter( parameter::IACCParameterPtr );

        const basar::db::aspect::ExecuteResultInfo readSAPLimitsFromFile( basar::db::aspect::AccessorPropertyTable_YIterator, bool flagExcept );
        const basar::db::aspect::ExecuteResultInfo backupSAPLimitFile   ( basar::db::aspect::AccessorPropertyTable_YIterator, bool flagExcept );

    private:
        parameter::IACCParameterPtr                getAccParameter() const;
        bool                                       isFileExisting()  const;

        // overridden
        void                                       registerAccessorMethods( AccMethodCaller& );
        void                                       setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef ) const;

    private:
        static const char                          m_RecordType = 'L'; // our record type
        static const basar::VarString::size_type   m_LineLength = 38;
        parameter::IACCParameterPtr                m_AccParameter;
    };

} // end namespace sap
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_SAPLIMITCOLLECTIONACC_H

