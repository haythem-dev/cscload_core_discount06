#ifndef GUARD_LIBCSC_PERSISTENCE_I_ACCESSOR_FACTORY_PTR_H
#define GUARD_LIBCSC_PERSISTENCE_I_ACCESSOR_FACTORY_PTR_H

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// include section
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace persistence
{
class IAccessorFactory;
typedef boost::shared_ptr<libcsc::persistence::IAccessorFactory> IAccessorFactoryPtr;

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_I_ACCESSOR_FACTORY_PTR_H
