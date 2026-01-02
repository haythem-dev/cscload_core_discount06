#ifndef GUARD_LIBCSC_IBT_I_IBTREQUEST_FACTORY_PTR_H
#define GUARD_LIBCSC_IBT_I_IBTREQUEST_FACTORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace ibt
{
	class IIbtRequestFactory;
	typedef boost::shared_ptr<libcsc::ibt::IIbtRequestFactory> IIbtRequestFactoryPtr;

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUEST_FACTORY_PTR_H
