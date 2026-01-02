#ifndef GUARD_LIBCSC_CSCORDER_REPO_ICSCORDERIBTPICKINGDATAREPOSITORY_H
#define GUARD_LIBCSC_CSCORDER_REPO_ICSCORDERIBTPICKINGDATAREPOSITORY_H

#include <libbasar_definitions.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include "icscorderibtpickingdataptr.h"
#include "cscorderibtpickingdatacollectionptr.h"


class pxSession;

namespace libcsc {
namespace cscorder {
namespace repo {

class ICSCOrderIBTPickingdataRepository
{
public:
    virtual ~ICSCOrderIBTPickingdataRepository() {};

    virtual domMod::CSCOrderIBTPickingdataCollectionPtr findPickingdata(
        const basar::Int32 cscorderno, const basar::Int32 cscorderpos) = 0;
    virtual bool savePickingdata(domMod::ICSCOrderIBTPickingdataPtr pickingdata) = 0;
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_ICSCORDERIBTPICKINGDATAREPOSITORY_H
