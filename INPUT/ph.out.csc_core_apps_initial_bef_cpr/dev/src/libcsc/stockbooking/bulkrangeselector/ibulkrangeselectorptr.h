#ifndef GUARD_LIBCSC_IBT_I_BULKRANGESELECTOR_PTR_H
#define GUARD_LIBCSC_IBT_I_BULKRANGESELECTOR_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace stockbooking
{
class IBulkRangeSelector;
typedef boost::shared_ptr<IBulkRangeSelector> IBulkRangeSelectorPtr;

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_BULKRANGESELECTOR_PTR_H
