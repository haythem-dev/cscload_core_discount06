#ifndef GUARD_LIBCSC_CSCORDER_REPO_ICSCCALLPLANREPOSITORY_H
#define GUARD_LIBCSC_CSCORDER_REPO_ICSCCALLPLANREPOSITORY_H

#include "cscorder/csccallplan/icsccallplanptr.h"

namespace libcsc {
namespace cscorder {
namespace repo {

class ICSCCallplanRepository
{
public:
    virtual ~ICSCCallplanRepository() {};

    virtual bool saveCSCCallplan(domMod::ICSCCallplanPtr cscCallplan) = 0;
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_ICSCCALLPLANREPOSITORY_H
