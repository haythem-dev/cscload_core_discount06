#ifndef GUARD_LIBCSC_SHELL_DISCOUNT_LOGGER_H
#define GUARD_LIBCSC_SHELL_DISCOUNT_LOGGER_H

#include <discount/logger/discountlogger/idiscountlogger.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class Log4CplusDiscountLogger : public IDiscountLogger
{
public:
	Log4CplusDiscountLogger();
	virtual ~Log4CplusDiscountLogger();

	virtual void log( const DiscountCalculatorTypeEnum calcType, const DiscountCalculatorResult & calcResult );
	virtual void save();
	void reset();
};

typedef boost::shared_ptr<libcsc::discount::Log4CplusDiscountLogger> Log4CplusDiscountLoggerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHELL_DISCOUNT_LOGGER_H
