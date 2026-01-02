#ifndef GUARD_LIBCSC_DISCOUNT_LOG_POSITION_MAPPER_BASE_H
#define GUARD_LIBCSC_DISCOUNT_LOG_POSITION_MAPPER_BASE_H

#include <discount/logger/discountlogger/discountlogpositionptr.h>
#include <libbasar_definitions.h>
#include <discount/calculator/discountcalculatortypeenum.h>

namespace libcsc
{
namespace discount
{
class DiscountLogPositionMapperBase
{
public:
	DiscountLogPositionMapperBase( DiscountLogPositionPtr discountLogPosition );

	void map();

protected:
	virtual ~DiscountLogPositionMapperBase();

	virtual void doMap() = 0;

	void setOrderNo( const basar::Int32 orderNo );
	void setPositionNo( const basar::Int32 positionNo );
	void setDiscountCalculatorType( const DiscountCalculatorTypeEnum discountCalculatorType );
	void setDiscountValue( const basar::Decimal & discountValue );
	void setDiscountPercent( const basar::Decimal & discountPercent );
	void setDiscountQty( const basar::Int32 discountQty );

private:
	DiscountLogPositionPtr	m_DiscountLogPosition;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_LOG_POSITION_MAPPER_BASE_H
