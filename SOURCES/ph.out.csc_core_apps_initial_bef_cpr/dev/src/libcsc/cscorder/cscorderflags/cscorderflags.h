#ifndef GUARD_LIBCSC_DOMMOD_CSCORDER_CSCORDERFLAGS_H
#define GUARD_LIBCSC_DOMMOD_CSCORDER_CSCORDERFLAGS_H

#include "icscorderflagsptr.h"
#include "icscorderflags.h"

namespace libcsc {
namespace cscorder {

namespace repo {
class CSCOrderFlagsMapperBase;
}

namespace domMod {

class CSCOrderFlags : public ICSCOrderFlags
{
    // because of OR mapping
    friend class repo::CSCOrderFlagsMapperBase;

public:
    CSCOrderFlags();
    virtual ~CSCOrderFlags();

    virtual Int32 const& getCscOrderNo() const;
    virtual bool const& isNoDelayedDelivery() const;
    virtual bool const& isWaitForIbtPicking() const;

    virtual void setClean();

public:
    virtual void setCscOrderNo(Int32 const& orderno);
    virtual void setNoDelayedDelivery(bool const& nodelayeddelivery);
    virtual void setWaitForIbtPicking(bool const& waitforibtpicking);

private:
    Int32   m_CscOrderNo;
    Bool    m_NoDelayedDelivery;
    Bool    m_WaitForIbtPicking;

    CSCOrderFlags(const CSCOrderFlags&);
    CSCOrderFlags& operator=(const CSCOrderFlags&);
};

} // namespace domMod
} // namespace cscorder
} // namespace libcsc

#endif // GUARD_LIBCSC_DOMMOD_CSCORDER_CSCORDERFLAGS_H
