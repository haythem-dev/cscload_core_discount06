#ifndef GUARD_LIBCSC_TENDER_REPOSITORY_PTR_H
#define GUARD_LIBCSC_TENDER_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace tender
{
class TenderRepository;
typedef boost::shared_ptr<libcsc::tender::TenderRepository> TenderRepositoryPtr;

} // end namespace tender
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_REPOSITORY_PTR_H
