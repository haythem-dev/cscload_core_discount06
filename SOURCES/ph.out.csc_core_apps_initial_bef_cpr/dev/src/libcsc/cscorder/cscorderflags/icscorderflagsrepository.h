#ifndef GUARD_LIBCSC_CSCORDER_REPO_ICSCORDERFLAGSREPOSITORY_H
#define GUARD_LIBCSC_CSCORDER_REPO_ICSCORDERFLAGSREPOSITORY_H

#include <libbasar_definitions.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include "cscorder/cscorderflags/icscorderflagsptr.h"

class pxSession;

namespace libcsc {
namespace cscorder {

namespace domMod {
class ICSCOrderFlags;
}

namespace repo {

class ICSCOrderFlagsRepository
{
public:
    virtual ~ICSCOrderFlagsRepository() {};    

	virtual domMod::ICSCOrderFlagsPtr findCSCOrderFlags(const basar::Int32 cscorderno) = 0;           	        
	virtual bool saveCSCOrderFlags(domMod::ICSCOrderFlagsPtr cscOrderFlags) = 0;
    virtual bool deleteCSCOrderFlags(basar::Int32 const& cscorderno) = 0;    
};

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_ICSCORDERFLAGSREPOSITORY_H
