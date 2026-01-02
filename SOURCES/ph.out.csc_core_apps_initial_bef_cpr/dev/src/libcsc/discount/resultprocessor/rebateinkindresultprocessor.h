#ifndef GUARD_LIBCSC_REBATE_IN_KIND_RESULT_PROCESSOR_H
#define GUARD_LIBCSC_REBATE_IN_KIND_RESULT_PROCESSOR_H

#include <discount/resultprocessor/repositoryresultprocessorbase.h>
#include <discount/resultprocessor/irebateinkindrepository.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepositoryptr.h>
#include <discount/orderpositiondiscount/orderpositiondiscountmodeenum.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>
#include <set>
#include <boost/shared_ptr.hpp>

class pxOrderItem;

namespace libcsc
{
namespace discount
{
class RebateInKindResultProcessor : public RepositoryResultProcessorBase,
									public IRebateInKindRepository
{
public:
	RebateInKindResultProcessor();
	virtual ~RebateInKindResultProcessor();

	void inject( IOrderPositionDiscountRepositoryPtr repository );

	virtual void process( 
		const DiscountCalculatorTypeEnum calcType, 
		const IOrderBaseValueGetterPtr baseValueGetter, 
		const DiscountCalculatorResult & calcResult 
			);

	virtual void reset();
	virtual void save();
	virtual void save4ever();

private:
	struct RebateInKindEntry
	{
		DiscountCalculatorTypeEnum			origin;
		libcsc::Int32						articleNo;
		pxOrderItem *						orderItem;
		const RebateInKindValue				rebateInKindValue;
		const DiscountResultBaseValue		baseValue;

		RebateInKindEntry( 
			const DiscountCalculatorTypeEnum _origin,
			const libcsc::Int32 _articleNo,
			pxOrderItem * _orderItem,
			const RebateInKindValue & _rebateInKindValue,
			const DiscountResultBaseValue & _baseValue
				);
		RebateInKindEntry( const RebateInKindEntry & rhs );

		bool operator<( const RebateInKindEntry & rhs ) const;

	private:
		RebateInKindEntry & operator=( const RebateInKindEntry & rhs );
	};

	typedef std::set<RebateInKindEntry> RebateInKindCollection;

	void processRebateInKind( 
		const DiscountCalculatorTypeEnum calcType, 
		const IOrderBaseValueGetterPtr baseValueGetter, 
		const DiscountCalculatorResult & calcResult 
			);

	void processRebateInKind(
		const RebateInKindEntry & rebateInKindEntry, const basar::Int32 mode = CE_POSITIONDISCOUNTCALCUC);
	basar::Int32 findRebateInKindPos(DiscountCalculatorTypeEnum calcType) const;
	basar::Int32 compareDiscountValues( 
		const OrderPositionDiscount & orderPositionDiscount,
		const RebateInKindValue & rebateInKindValue
			) const;

	RebateInKindCollection					m_RebateInKinds;
	IOrderPositionDiscountRepositoryPtr		m_Repository;
	IOrderBaseValueGetterPtr				m_OrderBaseValueGetter;
};

typedef boost::shared_ptr<libcsc::discount::RebateInKindResultProcessor> RebateInKindResultProcessorPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_REBATE_IN_KIND_RESULT_PROCESSOR_H
