#ifndef GUARD_LIBCSC_SHELL_RESULT_PROCESSOR_H
#define GUARD_LIBCSC_SHELL_RESULT_PROCESSOR_H

#include "iresultprocessor.h"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class ShellResultProcessor : public IResultProcessor
{
public:
	ShellResultProcessor();
	virtual ~ShellResultProcessor();

	virtual void process(
		const DiscountCalculatorTypeEnum calcType, 
		const IOrderBaseValueGetterPtr baseValueGetter, 
		const DiscountCalculatorResult & calcResult 
			);
	void print() const;
	void reset();

private:
	std::vector<std::string>	m_Messages;
};

typedef boost::shared_ptr<libcsc::discount::ShellResultProcessor> ShellLoggerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHELL_RESULT_PROCESSOR_H
