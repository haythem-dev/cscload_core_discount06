#ifndef GUARD_LIBCSC_REPOSITORY_RESULT_PROCESSOR_H
#define GUARD_LIBCSC_REPOSITORY_RESULT_PROCESSOR_H

#include <discount/resultprocessor/repositoryresultprocessorbase.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepositoryptr.h>
#include <discount/orderpositiondiscount/orderpositiondiscountmodeenum.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class RepositoryResultProcessor : public RepositoryResultProcessorBase
{
public:
	RepositoryResultProcessor();
	virtual ~RepositoryResultProcessor();

	void inject( IOrderPositionDiscountRepositoryPtr repository );

	virtual void process( 
		const DiscountCalculatorTypeEnum calcType, 
		const IOrderBaseValueGetterPtr baseValueGetter, 
		const DiscountCalculatorResult & calcResult 
			);

private:
	void processDiscount( 
		const DiscountCalculatorTypeEnum calcType, 
		const IOrderBaseValueGetterPtr baseValueGetter,
		const DiscountCalculatorResult & calcResult 
			);

	basar::Int32 compareDiscountValues( 
		const OrderPositionDiscount & orderPositionDiscount,
		const DiscountResult & discountResult,
		const IOrderBaseValueGetterPtr baseValueGetter
			) const;
	const basar::Decimal getDiscountValue(
		const OrderPositionDiscount & orderPositionDiscount,
		const IOrderBaseValueGetterPtr baseValueGetter
			) const;
	const basar::Decimal getDiscountValue(
		const DiscountResult & discountResult,
		const IOrderBaseValueGetterPtr baseValueGetter
			) const;

	IOrderPositionDiscountRepositoryPtr		m_Repository;
};

typedef boost::shared_ptr<libcsc::discount::RepositoryResultProcessor> RepositoryResultProcessorPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_REPOSITORY_RESULT_PROCESSOR_H
