#ifndef GUARD_LIBCSC_TENDER_COLLECTION_PTR_H
#define GUARD_LIBCSC_TENDER_COLLECTION_PTR_H

#include <tender/tendercollection.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace tender
{
typedef boost::shared_ptr<libcsc::tender::TenderList> TenderListPtr;

} // end namespace tender
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_COLLECTION_PTR_H
