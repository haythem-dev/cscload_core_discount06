#ifndef GUARD_CSC_PHADEX_CICS_DATA_ACC_H
#define GUARD_CSC_PHADEX_CICS_DATA_ACC_H

#include <libutil/accessor.h>

namespace infrastructure
{
namespace accessor
{
namespace drksc
{
	BEGIN_QUERY_BUILDER_DECLARATION( SelectDRKSCByPattern )
	END_BUILDER_DECLARATION		

    BEGIN_WRITE_BUILDER_DECLARATION( UpdateDRKSC )
	END_BUILDER_DECLARATION
}
}
}


#endif // GUARD_CSC_PHADEX_CICS_DATA_ACC_H
