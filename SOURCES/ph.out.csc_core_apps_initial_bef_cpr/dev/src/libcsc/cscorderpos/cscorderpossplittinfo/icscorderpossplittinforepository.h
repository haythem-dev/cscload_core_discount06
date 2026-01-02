#ifndef GUARD_LIBCSC_CSCORDERPOS_REPO_ICSCORDERPOSSPLITTINFOREPOSITORY_H
#define GUARD_LIBCSC_CSCORDERPOS_REPO_ICSCORDERPOSSPLITTINFOREPOSITORY_H

#include <libbasar_definitions.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include "types/splitttypeenum.inc"
#include "icscorderpossplittinfoptr.h"

class pxSession;

namespace libcsc {
namespace cscorderpos {
namespace repo {

class ICSCOrderposSplittinfoRepository
{
public:
    virtual ~ICSCOrderposSplittinfoRepository() {};

    virtual domMod::ICSCOrderposSplittinfoPtr findSplittinfo(const basar::Int32 cscorderno,
        const basar::Int32 cscorderpos, const SplittTypeEnum splittype, const basar::Int32 date = 0) = 0;
    virtual bool saveSplittinfo(domMod::ICSCOrderposSplittinfoPtr splittinfo) = 0;
};

} // end namespace repo
} // end namespace cscorderpos
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERPOS_REPO_ICSCORDERPOSSPLITTINFOREPOSITORY_H
