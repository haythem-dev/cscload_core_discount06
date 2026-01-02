#ifndef GUARD_LIBCSC_IBT_IBTRESPONSE_PTR_H
#define GUARD_LIBCSC_IBT_IBTRESPONSE_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
	class IbtResponse;
	typedef boost::shared_ptr<libcsc::ibt::IbtResponse> IbtResponsePtr;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTRESPONSE_PTR_H
