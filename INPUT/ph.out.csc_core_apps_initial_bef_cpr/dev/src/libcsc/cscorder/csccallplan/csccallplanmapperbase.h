#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANMAPPERBASE_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANMAPPERBASE_H

#include <libbasar_definitions.h>
#include "cscorder/csccallplan/icsccallplanptr.h"

namespace libcsc {
namespace cscorder {
namespace repo {

class CSCCallplanMapperBase
{
public:
    CSCCallplanMapperBase(domMod::ICSCCallplanPtr cscCallplan);

    void map();

protected:
    virtual ~CSCCallplanMapperBase();

    virtual void doMap() = 0;

    void setCallTime(basar::Int32 const calltime);
    void setAction(basar::Int16 const action);

private:
    domMod::ICSCCallplanPtr m_CSCCallplan;

    CSCCallplanMapperBase& operator=(CSCCallplanMapperBase const& CSCCallplanMapperBase);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCCALLPLANMAPPERBASE_H
