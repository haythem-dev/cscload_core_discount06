#ifndef GUARD_LIBCSC_SHELL_HIERARCHY_LOGGER_H
#define GUARD_LIBCSC_SHELL_HIERARCHY_LOGGER_H

#include <discount/logger/hierarchylogger/ihierarchylogger.h>
#include <boost/shared_ptr.hpp>
#include <map>
#include <ostream>

namespace libcsc
{
namespace discount
{
class ShellHierarchyLogger : public IHierarchyLogger
{
public:
	ShellHierarchyLogger();
	virtual ~ShellHierarchyLogger();

	virtual void log(
		const DiscountCalculatorTypeEnum parentCalcType, 
		const DiscountCalculatorTypeEnum calcType, 
		const DiscountCalculatorResult & calcResult 
			);
	void print() const;
	std::ostream & toStream( std::ostream & str ) const;
	void reset();

private:
	std::vector<std::string>							m_Messages;
	std::map<DiscountCalculatorTypeEnum, std::string>	m_LineIndents;
};

typedef boost::shared_ptr<libcsc::discount::ShellHierarchyLogger> ShellHierarchyLoggerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHELL_HIERARCHY_LOGGER_H
