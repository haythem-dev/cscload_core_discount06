#ifndef GUARD_LIBCSC_SHELL_DISCOUNT_LOGGER_H
#define GUARD_LIBCSC_SHELL_DISCOUNT_LOGGER_H

#include <discount/logger/discountlogger/idiscountlogger.h>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class ShellDiscountLogger : public IDiscountLogger
{
public:
	ShellDiscountLogger();
	virtual ~ShellDiscountLogger();

	virtual void log( const DiscountCalculatorTypeEnum calcType, const DiscountCalculatorResult & calcResult );
	virtual void save();
	void reset();

private:
	std::vector<std::string>	m_Messages;
};

typedef boost::shared_ptr<libcsc::discount::ShellDiscountLogger> ShellLoggerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHELL_DISCOUNT_LOGGER_H
