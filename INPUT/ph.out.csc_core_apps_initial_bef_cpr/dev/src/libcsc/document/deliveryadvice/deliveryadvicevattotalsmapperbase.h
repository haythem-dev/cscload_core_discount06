#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALSMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALSMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "deliveryadvicevattotalsptr.h"


namespace libcsc {
namespace document {

class DeliveryAdviceVatTotalsMapperBase
{
public:
	DeliveryAdviceVatTotalsMapperBase(DeliveryAdviceVatTotalsPtr deliveryAdviceVatTotals);

	void			map();
protected:
	virtual ~DeliveryAdviceVatTotalsMapperBase();

	virtual void	doMap() = 0;

	void		setBranchNo( const basar::Int16 branchNo );
	void		setCustomerNo( const basar::Int32 customerNo );
	void		setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate );
	void		setDeliveryAdviceNo( const basar::VarString& deliveryAdviceNo );

	void		setVat( const basar::VarString & vat );

	void		setVatPercentage( const basar::Decimal & vatPercentage );
	void		setNetValue( const basar::Decimal & netValue );
	void		setVatValue( const basar::Decimal & vatValue );
    void		setSumLineFee(const basar::Decimal & sumLineFee);
    void		setSumPackageFee(const basar::Decimal & sumPackageFee);



//private:
	DeliveryAdviceVatTotalsPtr m_DeliveryAdviceVatTotals;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEVATTOTALSMAPPER_BASE_H
