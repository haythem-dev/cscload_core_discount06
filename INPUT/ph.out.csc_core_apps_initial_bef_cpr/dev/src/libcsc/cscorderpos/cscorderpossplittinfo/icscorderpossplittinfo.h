#ifndef GUARD_LIBCSC_CSCORDERPOS_DOMMOD_ICSCORDERPOSSPLITTINFO_H
#define GUARD_LIBCSC_CSCORDERPOS_DOMMOD_ICSCORDERPOSSPLITTINFO_H

#include <datatypes/int32.h>
#include <datatypes/property.hpp>
#include "types/splitttypeenum.inc"
#include "types/splittorigintypeenum.inc"

namespace libcsc {
namespace cscorderpos {
namespace domMod {

typedef libcsc::Property< ::SplittTypeEnum> SplittTypeEnum;
typedef libcsc::Property< ::SplittOriginTypeEnum> SplittOriginTypeEnum;

class ICSCOrderposSplittinfo
{
    public:
        virtual ~ICSCOrderposSplittinfo(){};

        virtual Int32 const& getCscOrderNo() const = 0;
        virtual Int32 const& getCscOrderPosNo() const = 0;
        virtual SplittTypeEnum const& getSplittType() const = 0;
        virtual SplittOriginTypeEnum const& getOriginal() const = 0;
        virtual Int32 const& getOrderNo() const = 0;
        virtual Int32 const& getOrderPosNo() const = 0;

        virtual void setCscOrderNo(Int32 const& cscorderno) = 0;
        virtual void setCscOrderPosNo(Int32 const& cscorderposno) = 0;
        virtual void setSplittType(SplittTypeEnum const& splittype) = 0;
        virtual void setOriginal(SplittOriginTypeEnum const& original) = 0;
        virtual void setOrderNo(Int32 const& orderno) = 0;
        virtual void setOrderPosNo(Int32 const& orderposno) = 0;
};

} // namespace domMod
} // namespace cscorderpos
} // namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERPOS_DOMMOD_ICSCORDERPOSSPLITTINFO_H
