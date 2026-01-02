#ifndef GUARD_LIBCSC_I_DISCOUNT_LOG_POSITION_REPOSITORY_H
#define GUARD_LIBCSC_I_DISCOUNT_LOG_POSITION_REPOSITORY_H

#include <discount/logger/discountlogger/discountlogpositioncollection.h>

namespace libcsc
{
namespace discount
{
class IDiscountLogPositionRepository
{
public:
	virtual ~IDiscountLogPositionRepository() {}

	virtual DiscountLogPositionCollectionPtr get() = 0;
	virtual void save() = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_LOG_POSITION_REPOSITORY_H
