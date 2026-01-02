#ifndef GUARD_LIBCSC_DOMMOD_CSCORDER_ICSCORDERFLAGS_H
#define GUARD_LIBCSC_DOMMOD_CSCORDER_ICSCORDERFLAGS_H

//-------------------------------------------------------------------------------------------------//

#include <libbasar_definitions.h>
#include <datatypes/int32.h>
#include <datatypes/boolean.h>

namespace libcsc {
namespace cscorder {
namespace domMod {

typedef libcsc::Property<basar::Int32> Int32;

//-------------------------------------------------------------------------------------------------//
class ICSCOrderFlags
{
    public:
        virtual ~ICSCOrderFlags(){};

        virtual Int32 const& getCscOrderNo() const = 0;
        virtual bool const& isNoDelayedDelivery() const = 0;
        virtual bool const& isWaitForIbtPicking() const = 0;

        virtual void setClean() = 0;

    public:
        virtual void setCscOrderNo(Int32 const& orderno) = 0;
        virtual void setNoDelayedDelivery(bool const& nodelayeddelivery) = 0;
        virtual void setWaitForIbtPicking(bool const& waitforibtpicking) = 0;
};

//-------------------------------------------------------------------------------------------------//

} // namespace domMod
} // namespace cscorder
} // namespace libcsc

//-------------------------------------------------------------------------------------------------//

#endif // GUARD_LIBCSC_DOMMOD_CSCORDER_ICSCORDERFLAGS_H

//-------------------------------------------------------------------------------------------------//
