#ifndef GUARD_LIBCSC_IBT_I_IBTRESPONSE_FACTORY_PTR_H
#define GUARD_LIBCSC_IBT_I_IBTRESPONSE_FACTORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
	class IIbtResponseFactory;
	typedef boost::shared_ptr<libcsc::ibt::IIbtResponseFactory> IIbtResponseFactoryPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTRESPONSE_FACTORY_PTR_H
