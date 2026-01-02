#ifndef GUARD_LIBCSC_ORDER_DISCOUNT_CALC_UC_H
#define GUARD_LIBCSC_ORDER_DISCOUNT_CALC_UC_H

#include <base/irunnable.h>
#include <boost/shared_ptr.hpp>
#include <discount/calculator/commands/idiscountcalculatorcommandptr.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepositoryptr.h>
#include <discount/resultprocessor/irebateinkindrepositoryptr.h>
#include <discount/logger/discountlogger/idiscountloggerptr.h>
#include <discount/basevalues/discountbasevalue/idiscountbasevaluerepositoryptr.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>
#include <discount/orderpositiondiscountprocessed/iorderpositiondiscountprocessedrepositoryptr.h>

namespace libcsc
{
namespace discount
{
    class OrderDiscountCalcUC : public base::IRunnable
{
public:
	OrderDiscountCalcUC();
	virtual ~OrderDiscountCalcUC();

	void inject( IDiscountCalculatorCommandPtr calculator );
	void inject( IOrderPositionDiscountRepositoryPtr orderPositionDiscountRepository );
	void inject( IRebateInKindRepositoryPtr rebateInKindRepository );
	void inject( IDiscountBaseValueRepositoryPtr discountBaseValueRepository );
	void inject( IOrderBaseValueGetterPtr orderBaseValueGetter );
	void inject( IDiscountLoggerPtr logger );
	void inject( IOrderPositionDiscountProcessedRepositoryPtr orderPositionDiscountProcessedRepository );

	virtual void run();

private:
	void markOrderPositionsProcessed();

	IDiscountCalculatorCommandPtr					m_Calculator;
	IOrderPositionDiscountRepositoryPtr				m_OrderPositionDiscountRepository;
	IRebateInKindRepositoryPtr						m_RebateInKindRepository;
	IDiscountBaseValueRepositoryPtr					m_DiscountBaseValueRepository;
	IDiscountLoggerPtr								m_Logger;
	IOrderBaseValueGetterPtr						m_OrderBaseValueGetter;
	IOrderPositionDiscountProcessedRepositoryPtr	m_OrderPositionDiscountProcessedRepository;
};

typedef boost::shared_ptr<libcsc::discount::OrderDiscountCalcUC> OrderDiscountCalcUCPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_DISCOUNT_CALC_UC_H
