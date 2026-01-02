#ifndef GUARD_LIBCSC_NULL_DISCOUNT_CALC_UC_H
#define GUARD_LIBCSC_NULL_DISCOUNT_CALC_UC_H

#include <base/irunnable.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
    class NullDiscountCalcUC : public base::IRunnable
{
public:
	NullDiscountCalcUC() {}
	virtual ~NullDiscountCalcUC() {}

	virtual void run() {}
};

typedef boost::shared_ptr<libcsc::discount::NullDiscountCalcUC> NullDiscountCalcUCPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_NULL_DISCOUNT_CALC_UC_H
