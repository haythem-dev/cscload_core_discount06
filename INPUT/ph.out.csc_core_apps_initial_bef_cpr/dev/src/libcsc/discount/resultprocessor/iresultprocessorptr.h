#ifndef GUARD_LIBCSC_I_RESULT_PROCESSOR_PTR_H
#define GUARD_LIBCSC_I_RESULT_PROCESSOR_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class IResultProcessor;
typedef boost::shared_ptr<libcsc::discount::IResultProcessor> IResultProcessorPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_RESULT_PROCESSOR_PTR_H
