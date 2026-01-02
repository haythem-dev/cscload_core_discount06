#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATAMAPPERBASE_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATAMAPPERBASE_H

#include <libbasar_definitions.h>
#include "cscorderibtpickingdata.h"
#include "cscorderibtpickingdataptr.h"
#include "icscorderibtpickingdataptr.h"

namespace libcsc {
namespace cscorder {
namespace repo {

class CSCOrderIBTPickingdataMapperBase
{
    public:
        CSCOrderIBTPickingdataMapperBase(domMod::ICSCOrderIBTPickingdataPtr pickingdata);

        void map();
        static void setClean(domMod::CSCOrderIBTPickingdataPtr pickingdata);

    protected:
        virtual ~CSCOrderIBTPickingdataMapperBase();

        virtual void doMap() = 0;

        void setCscOrderNo(basar::Int32 const cscorderno);
        void setCscOrderPosNo(basar::Int32 const cscorderposno);
        void setDeliveryPosNo(basar::Int32 const deliveryposno);
        void setQuantity(basar::Int32 const quantity);
        void setBatch(basar::VarString const batch);
        void setExpiryDate(basar::Int32 const expirydate);

    private:
        domMod::CSCOrderIBTPickingdata& m_Pickingdata;

        CSCOrderIBTPickingdataMapperBase& operator=(CSCOrderIBTPickingdataMapperBase const&);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERIBTPICKINGDATAMAPPERBASE_H
