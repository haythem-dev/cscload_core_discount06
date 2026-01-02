#ifndef GUARD_LIBCSC_CSCORDERPOS_DOMMOD_CSCORDERPOSSPLITTINFO_H
#define GUARD_LIBCSC_CSCORDERPOS_DOMMOD_CSCORDERPOSSPLITTINFO_H

#include "icscorderpossplittinfo.h"

namespace libcsc {
namespace cscorderpos {
namespace repo {
class CSCOrderposSplittinfoMapperBase;
}
namespace domMod {

class CSCOrderposSplittinfo : public ICSCOrderposSplittinfo
{
    // because of OR mapping
    friend class repo::CSCOrderposSplittinfoMapperBase;

public:
    CSCOrderposSplittinfo();
    virtual ~CSCOrderposSplittinfo();

    virtual Int32 const& getCscOrderNo() const;
    virtual Int32 const& getCscOrderPosNo() const;
    virtual SplittTypeEnum const& getSplittType() const;
    virtual SplittOriginTypeEnum const& getOriginal() const;
    virtual Int32 const& getOrderNo() const;
    virtual Int32 const& getOrderPosNo() const;

    virtual void setCscOrderNo(Int32 const& cscorderno);
    virtual void setCscOrderPosNo(Int32 const& cscorderposno);
    virtual void setSplittType(SplittTypeEnum const& splittype);
    virtual void setOriginal(SplittOriginTypeEnum const& original);
    virtual void setOrderNo(Int32 const& orderno);
    virtual void setOrderPosNo(Int32 const& orderposno);

private:
    Int32 m_CscOrderNo;
    Int32 m_CscOrderPosNo;
    SplittTypeEnum m_SplittType;
    SplittOriginTypeEnum m_Original;
    Int32 m_OrderNo;
    Int32 m_OrderPosNo;

    CSCOrderposSplittinfo(const CSCOrderposSplittinfo&);
    CSCOrderposSplittinfo& operator=(const CSCOrderposSplittinfo&);
};

} // namespace domMod
} // namespace cscorderpos
} // namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERPOS_DOMMOD_CSCORDERPOSSPLITTINFO_H
