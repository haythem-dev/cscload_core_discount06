#ifndef GUARD_LIBCSC_CSCORDERTYPE_COLLECTION_PTR_H
#define GUARD_LIBCSC_CSCORDERTYPE_COLLECTION_PTR_H

#include <cscordertype/cscordertypecollection.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace cscordertype
{
typedef boost::shared_ptr<libcsc::cscordertype::CSCOrderTypeCollection> CSCOrderTypeCollectionPtr;

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_COLLECTION_PTR_H
