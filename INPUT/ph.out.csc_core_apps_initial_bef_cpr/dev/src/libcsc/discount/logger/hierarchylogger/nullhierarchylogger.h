#ifndef GUARD_LIBCSC_NULL_HIERARCHY_LOGGER_H
#define GUARD_LIBCSC_NULL_HIERARCHY_LOGGER_H

#include <discount/logger/hierarchylogger/ihierarchylogger.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class NullHierarchyLogger : public IHierarchyLogger
{
public:
	NullHierarchyLogger();
	virtual ~NullHierarchyLogger();

	virtual void log(
		const DiscountCalculatorTypeEnum parentCalcType, 
		const DiscountCalculatorTypeEnum calcType, 
		const DiscountCalculatorResult & calcResult 
			);
};

typedef boost::shared_ptr<libcsc::discount::NullHierarchyLogger> NullHierarchyLoggerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_NULL_HIERARCHY_LOGGER_H
