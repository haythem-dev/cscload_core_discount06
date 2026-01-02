#ifndef GUARD_LIBCSC_REPOSITORY_DISCOUNT_LOGGER_H
#define GUARD_LIBCSC_REPOSITORY_DISCOUNT_LOGGER_H

#include <discount/logger/discountlogger/idiscountlogger.h>
#include <discount/logger/discountlogger/idiscountlogpositionrepositoryptr.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class RepositoryDiscountLogger : public IDiscountLogger
{
public:
	RepositoryDiscountLogger();
	virtual ~RepositoryDiscountLogger();

	void inject( IDiscountLogPositionRepositoryPtr repository );

	virtual void log( const DiscountCalculatorTypeEnum calcType, const DiscountCalculatorResult & calcResult );
	virtual void save();
	void reset();
};

typedef boost::shared_ptr<libcsc::discount::RepositoryDiscountLogger> RepositoryDiscountLoggerPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_REPOSITORY_DISCOUNT_LOGGER_H
