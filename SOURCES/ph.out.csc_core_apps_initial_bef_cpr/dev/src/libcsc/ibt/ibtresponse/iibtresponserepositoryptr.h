#ifndef GUARD_LIBCSC_IBT_I_IBTRESPONSE_REPOSITORY_PTR_H
#define GUARD_LIBCSC_IBT_I_IBTRESPONSE_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
	class IIbtResponseRepository;
	typedef boost::shared_ptr<libcsc::ibt::IIbtResponseRepository> IIbtResponseRepositoryPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTRESPONSE_REPOSITORY_PTR_H
