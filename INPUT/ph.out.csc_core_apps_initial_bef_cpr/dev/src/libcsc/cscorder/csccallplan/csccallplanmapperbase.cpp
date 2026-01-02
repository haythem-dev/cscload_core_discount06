#include "csccallplanmapperbase.h"
#include "cscorder/csccallplan/csccallplan.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCCallplanMapperBase::CSCCallplanMapperBase(domMod::ICSCCallplanPtr cscCalllplan)
    : m_CSCCallplan(cscCalllplan)
{
}

CSCCallplanMapperBase::~CSCCallplanMapperBase()
{
}

void CSCCallplanMapperBase::map()
{
    doMap();
}

void CSCCallplanMapperBase::setCallTime(basar::Int32 const calltime)
{
    domMod::CSCCallplan* cscCallplan = dynamic_cast<domMod::CSCCallplan*>(m_CSCCallplan.get());
    cscCallplan->m_CallTime = calltime;
    cscCallplan->m_CallTime.setClean();
}

void CSCCallplanMapperBase::setAction(basar::Int16 const action)
{
    domMod::CSCCallplan* cscCallplan = dynamic_cast<domMod::CSCCallplan*>(m_CSCCallplan.get());
    cscCallplan->m_Action = action;
    cscCallplan->m_Action.setClean();
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
