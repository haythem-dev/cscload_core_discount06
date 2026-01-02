#ifndef GUARD_LIBCSC_IBT_I_IBTRESPONSE_FACTORY_H
#define GUARD_LIBCSC_IBT_I_IBTRESPONSE_FACTORY_H

#include <libbasar_definitions.h>
#include <ibt/ibtresponse/iibtresponseptr.h>

namespace libcsc
{
namespace ibt
{
class IIbtResponseFactory
{
public:
	virtual ~IIbtResponseFactory() {};

	virtual IIbtResponsePtr createResponse( const basar::Int32 ibtRequestId ) = 0;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTRESPONSE_FACTORY_H
