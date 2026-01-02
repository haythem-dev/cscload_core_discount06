#ifndef GUARD_LIBCSC_PERSISTENCE_CONNECTION_PTR_H
#define GUARD_LIBCSC_PERSISTENCE_CONNECTION_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace persistence
{
class Connection;
typedef boost::shared_ptr<libcsc::persistence::Connection> ConnectionPtr;

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_CONNECTION_PTR_H
