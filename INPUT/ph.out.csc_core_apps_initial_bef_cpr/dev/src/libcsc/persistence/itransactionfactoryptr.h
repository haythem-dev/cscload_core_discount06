#ifndef GUARD_LIBCSC_PERSISTENCE_I_TRANSACTION_FACTORY_PTR_H
#define GUARD_LIBCSC_PERSISTENCE_I_TRANSACTION_FACTORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace persistence
{
class ITransactionFactory;
typedef boost::shared_ptr<libcsc::persistence::ITransactionFactory> ITransactionFactoryPtr;

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_I_TRANSACTION_FACTORY_PTR_H
