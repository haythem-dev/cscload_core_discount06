#ifndef GUARD_LIBCSC_CSCORDER_DOMMOD_CSCORDERIBTPICKINGDATA_H
#define GUARD_LIBCSC_CSCORDER_DOMMOD_CSCORDERIBTPICKINGDATA_H

#include "icscorderibtpickingdata.h"

namespace libcsc {
namespace cscorder {
namespace repo {
class CSCOrderIBTPickingdataMapperBase;
}
namespace domMod {

class CSCOrderIBTPickingdata : public ICSCOrderIBTPickingdata
{
    // because of OR mapping
    friend class repo::CSCOrderIBTPickingdataMapperBase;

public:
    CSCOrderIBTPickingdata();
    virtual ~CSCOrderIBTPickingdata();

    virtual Int32 const& getCscOrderNo() const;
    virtual Int32 const& getCscOrderPosNo() const;
    virtual Int32 const& getDeliveryPosNo() const;
    virtual Int32 const& getQuantity() const;
    virtual VarString const& getBatch() const;
    virtual Int32 const& getExpiryDate() const;

    virtual void setCscOrderNo(Int32 const& cscorderno);
    virtual void setCscOrderPosNo(Int32 const& cscorderposno);
    virtual void setDeliveryPosNo(Int32 const& deliveryposno);
    virtual void setQuantity(Int32 const& quantity);
    virtual void setBatch(VarString const& batch);
    virtual void setExpiryDate(Int32 const& expirydate);

private:
    Int32 m_CscOrderNo;
    Int32 m_CscOrderPosNo;
    Int32 m_DeliveryPosNo;
    Int32 m_Quantity;
    VarString m_Batch;
    Int32 m_ExpiryDate;

    CSCOrderIBTPickingdata(const CSCOrderIBTPickingdata&);
    CSCOrderIBTPickingdata& operator=(const CSCOrderIBTPickingdata&);
};

} // namespace domMod
} // namespace cscorder
} // namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_DOMMOD_CSCORDERIBTPICKINGDATA_H
