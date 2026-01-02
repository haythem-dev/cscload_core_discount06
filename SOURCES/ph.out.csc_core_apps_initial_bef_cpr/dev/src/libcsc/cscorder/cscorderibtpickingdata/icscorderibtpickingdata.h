#ifndef GUARD_LIBCSC_CSCORDER_DOMMOD_ICSCORDERIBTPICKINGDATA_H
#define GUARD_LIBCSC_CSCORDER_DOMMOD_ICSCORDERIBTPICKINGDATA_H

#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <datatypes/property.hpp>

namespace libcsc {
namespace cscorder {
namespace domMod {

class ICSCOrderIBTPickingdata
{
    public:
        virtual ~ICSCOrderIBTPickingdata(){};

        virtual Int32 const& getCscOrderNo() const = 0;
        virtual Int32 const& getCscOrderPosNo() const = 0;
        virtual Int32 const& getDeliveryPosNo() const = 0;
        virtual Int32 const& getQuantity() const = 0;
        virtual VarString const& getBatch() const = 0;
        virtual Int32 const& getExpiryDate() const = 0;

        virtual void setCscOrderNo(Int32 const& cscorderno) = 0;
        virtual void setCscOrderPosNo(Int32 const& cscorderposno) = 0;
        virtual void setDeliveryPosNo(Int32 const& deliveryposno) = 0;
        virtual void setQuantity(Int32 const& quantity) = 0;
        virtual void setBatch(VarString const& batch) = 0;
        virtual void setExpiryDate(Int32 const& expirydate) = 0;
};

} // namespace domMod
} // namespace cscorder
} // namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_DOMMOD_ICSCORDERIBTPICKINGDATA_H
