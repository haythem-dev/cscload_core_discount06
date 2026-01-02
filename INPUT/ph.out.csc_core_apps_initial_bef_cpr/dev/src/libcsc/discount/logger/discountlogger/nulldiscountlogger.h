#ifndef GUARD_LIBCSC_NULL_DISCOUNT_LOGGER_H
#define GUARD_LIBCSC_NULL_DISCOUNT_LOGGER_H

#include <discount/logger/discountlogger/idiscountlogger.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class NullDiscountLogger : public IDiscountLogger
{
public:
	NullDiscountLogger();
	virtual ~NullDiscountLogger();

	virtual void log( const DiscountCalculatorTypeEnum calcType, const DiscountCalculatorResult & calcResult );
	virtual void save();
};

typedef boost::shared_ptr<libcsc::discount::NullDiscountLogger> NullDiscountLoggerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_NULL_DISCOUNT_LOGGER_H
