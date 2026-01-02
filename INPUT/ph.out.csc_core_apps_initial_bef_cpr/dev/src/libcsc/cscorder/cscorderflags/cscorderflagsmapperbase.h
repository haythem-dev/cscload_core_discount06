#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSMAPPERBASE_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSMAPPERBASE_H

#include <libbasar_definitions.h>
#include "cscorder/cscorderflags/icscorderflagsptr.h"
#include "cscorder/cscorderflags/cscorderflagsptr.h"

namespace libcsc {
namespace cscorder {

namespace domMod {
class CSCOrderFlags;
}

namespace repo {

class CSCOrderFlagsMapperBase
{
    public:
        CSCOrderFlagsMapperBase(domMod::CSCOrderFlagsPtr cscOrderFlags);

        void map();

    protected:
        virtual ~CSCOrderFlagsMapperBase();

        virtual void doMap() = 0;

        void setCscOrderNo(basar::Int32 const cscOrderNo);
        void setNoDelayedDelivery(bool const noDelayedDelivery);
        void setWaitForIbtPicking(bool const waitforibtpicking);

    private:
        domMod::CSCOrderFlagsPtr m_CSCOrderFlags;

        CSCOrderFlagsMapperBase& operator=(CSCOrderFlagsMapperBase const& CSCOrderFlagsMapperBase);
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSMAPPERBASE_H
