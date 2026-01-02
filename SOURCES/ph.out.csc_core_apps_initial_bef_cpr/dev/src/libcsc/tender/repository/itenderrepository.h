#ifndef GUARD_LIBCSC_I_TENDER_REPOSITORY_H
#define GUARD_LIBCSC_I_TENDER_REPOSITORY_H

#include <libbasar_definitions.h>

namespace libcsc
{
namespace tender
{
class ITenderRepository
{
public:
	virtual ~ITenderRepository() {}

	virtual void switchTenderState( const basar::Int32 tenderNo ) = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_TENDER_REPOSITORY_H
