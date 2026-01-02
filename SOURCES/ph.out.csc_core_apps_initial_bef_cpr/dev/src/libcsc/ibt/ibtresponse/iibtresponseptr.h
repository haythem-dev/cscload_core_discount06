#ifndef GUARD_LIBCSC_IBT_I_IBTRESPONSE_PTR_H
#define GUARD_LIBCSC_IBT_I_IBTRESPONSE_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
	class IIbtResponse;
	typedef boost::shared_ptr<libcsc::ibt::IIbtResponse> IIbtResponsePtr;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTRESPONSE_PTR_H
