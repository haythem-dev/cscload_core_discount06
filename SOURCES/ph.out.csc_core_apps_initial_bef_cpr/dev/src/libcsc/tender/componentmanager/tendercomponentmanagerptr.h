#ifndef GUARD_LIBCSC_TENDER_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_TENDER_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace tender
{
class TenderComponentManager;
typedef boost::shared_ptr<libcsc::tender::TenderComponentManager> TenderComponentManagerPtr;

} // end namespace tender
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_COMPONENT_MANAGER_PTR_H
