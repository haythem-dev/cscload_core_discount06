#ifndef GUARD_DOMMOD_LOADCONTRACTSHR_ILOADCONTRACTSHRDMPTR_H
#define GUARD_DOMMOD_LOADCONTRACTSHR_ILOADCONTRACTSHRDMPTR_H

#include <boost/shared_ptr.hpp>

namespace loadcontractshr {
namespace domMod {
namespace loadcontractshrdm {

	class ILoadContractsHrDM;
	typedef boost::shared_ptr< ILoadContractsHrDM > ILoadContractsHrDMPtr;

}
}
}

#endif // GUARD_DOMMOD_LOADCONTRACTSHR_ILOADCONTRACTSHRDMPTR_H
