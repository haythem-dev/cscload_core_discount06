#ifndef GUARD_LIBCSC_I_TENDER_REPOSITORY_PTR_H
#define GUARD_LIBCSC_I_TENDER_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace tender
{
class ITenderRepository;
typedef boost::shared_ptr<libcsc::tender::ITenderRepository> ITenderRepositoryPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_TENDER_REPOSITORY_PTR_H
