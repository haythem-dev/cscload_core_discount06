#ifndef GUARD_LIBCSC_I_CSCORDERTYPE_PTR_H
#define GUARD_LIBCSC_I_CSCORDERTYPE_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc
{
namespace cscordertype
{
	class ICSCOrderType;
	typedef boost::shared_ptr<libcsc::cscordertype::ICSCOrderType> ICSCOrderTypePtr;

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_CSCORDERTYPE_PTR_H
