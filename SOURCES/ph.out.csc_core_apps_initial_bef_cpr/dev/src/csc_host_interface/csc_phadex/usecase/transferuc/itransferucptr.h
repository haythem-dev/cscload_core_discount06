#ifndef GUARD_CSC_PHADEX_USECASE_I_TRANSFER_UC_PTR_H
#define GUARD_CSC_PHADEX_USECASE_I_TRANSFER_UC_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace useCase
{
	class ITransferUC;
	typedef boost::shared_ptr< ITransferUC > ITransferUCPtr;
}
}

#endif //end GUARD_CSC_PHADEX_USECASE_I_TRANSFER_UC_PTR_H
