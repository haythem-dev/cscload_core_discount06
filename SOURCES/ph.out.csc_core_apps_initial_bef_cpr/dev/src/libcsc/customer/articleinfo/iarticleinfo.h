#ifndef GUARD_LIBCSC_CUSTOMER_IARTICLEINFO_H
#define GUARD_LIBCSC_CUSTOMER_IARTICLEINFO_H

#include <libbasar_definitions.h>


namespace libcsc {
namespace customer {

class IArticleInfo
{
public:
    virtual ~IArticleInfo() {}

    virtual basar::Int16            getBranchNo() const = 0;
    virtual basar::Int32            getArticleNo() const = 0;
    virtual basar::VarString        getEAN() const = 0;
    virtual basar::VarString        getName() const = 0;
    virtual basar::VarString        getAlternateName() const = 0;
    virtual basar::VarString        getManufacturerName() const = 0;
    virtual basar::Decimal          getBasePrice() const = 0;
    virtual basar::Decimal          getVatPercentage() const = 0;
    virtual bool                    getPositiveList() const = 0;
    virtual bool                    getActiveFlag() const = 0;
    virtual bool                    getBlockedFlag() const = 0;
    virtual basar::Date            	getCreationDate() const = 0;
    virtual basar::Date            	getChangeDate() const = 0;
    virtual basar::VarString        getArtInfoText() const = 0;
    virtual basar::Decimal          getAvailableFrom() const = 0;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_IARTICLEINFO_H
