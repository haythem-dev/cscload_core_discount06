#ifndef GUARD_LIBCSC_TENDER_PTR_H
#define GUARD_LIBCSC_TENDER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace tender
{
class Tender;
typedef boost::shared_ptr<libcsc::tender::Tender> TenderPtr;

} // end namespace tender
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_PTR_H
