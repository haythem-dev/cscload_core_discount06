#ifndef GUARD_CSC_PHADEX_PHADEX_TRANSACTION_ACC_H
#define GUARD_CSC_PHADEX_PHADEX_TRANSACTION_ACC_H

#include <libutil/accessor.h>

namespace infrastructure
{
namespace accessor
{
namespace phadex_transaction
{
	BEGIN_QUERY_BUILDER_DECLARATION( SelectLastPhadexTransactionByPattern )
	END_BUILDER_DECLARATION

	BEGIN_QUERY_BUILDER_DECLARATION( SelectPhadexTransactionByPattern )
	END_BUILDER_DECLARATION

	BEGIN_WRITE_BUILDER_DECLARATION( InsertPhadexTransaction )
	END_BUILDER_DECLARATION

	BEGIN_WRITE_BUILDER_DECLARATION( UpdatePhadexTransaction )
	END_BUILDER_DECLARATION
}
}
}


#endif // GUARD_CSC_PHADEX_PHADEX_TRANSACTION_ACC_H
