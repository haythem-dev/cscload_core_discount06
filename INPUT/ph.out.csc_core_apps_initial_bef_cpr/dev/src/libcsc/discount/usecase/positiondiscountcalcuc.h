#ifndef GUARD_LIBCSC_POSITION_DISCOUNT_CALC_UC_H
#define GUARD_LIBCSC_POSITION_DISCOUNT_CALC_UC_H

#include <base/irunnable.h>
#include <boost/shared_ptr.hpp>
#include <discount/calculator/commands/idiscountcalculatorcommandptr.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepositoryptr.h>
#include <discount/resultprocessor/irebateinkindrepositoryptr.h>
#include <discount/logger/discountlogger/idiscountloggerptr.h>
#include <discount/basevalues/discountbasevalue/idiscountbasevaluerepositoryptr.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>

class pxOrder;
class pxOrderItem;
namespace libcsc
{
namespace discount
{
class PositionDiscountCalcUC : public base::IRunnable
{
public:
	PositionDiscountCalcUC();
	virtual ~PositionDiscountCalcUC();

	void inject( IDiscountCalculatorCommandPtr calculator );
	void inject( IOrderPositionDiscountRepositoryPtr orderPositionDiscountRepository );
	void inject( IRebateInKindRepositoryPtr rebateInKindRepository );
	void inject( IDiscountBaseValueRepositoryPtr discountBaseValueRepository );
	void inject( IOrderBaseValueGetterPtr orderBaseValueGetter );
	void inject( IDiscountLoggerPtr logger );
	
	virtual void run();

private:
	IDiscountCalculatorCommandPtr			m_Calculator;
	IOrderPositionDiscountRepositoryPtr		m_OrderPositionDiscountRepository;
	IRebateInKindRepositoryPtr				m_RebateInKindRepository;
	IDiscountBaseValueRepositoryPtr			m_DiscountBaseValueRepository;
	IDiscountLoggerPtr						m_Logger;
	IOrderBaseValueGetterPtr				m_OrderBaseValueGetter;
};

typedef boost::shared_ptr<libcsc::discount::PositionDiscountCalcUC> PositionDiscountCalcUCPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_POSITION_DISCOUNT_CALC_UC_H
