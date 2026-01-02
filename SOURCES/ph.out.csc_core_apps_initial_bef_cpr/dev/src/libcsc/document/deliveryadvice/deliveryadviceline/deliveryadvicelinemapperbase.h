#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEMAPPER_BASE_H

#include <libbasar_definitions.h>
#include <document/deliveryadvice/deliveryadviceptr.h>
#include "deliveryadvicelineptr.h"


namespace libcsc {
namespace document {

class DeliveryAdviceLineMapperBase
{
public:
	DeliveryAdviceLineMapperBase(DeliveryAdviceLinePtr deliveryAdviceLine, const DeliveryAdvicePtr& deliveryAdvice);

	void			map();
protected:
	virtual ~DeliveryAdviceLineMapperBase();

	virtual void	doMap() = 0;

	void setBranchNo( const basar::Int16 branchNo );
	void setCustomerNo( const basar::Int32 customerNo );
	void setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate );
	void setDeliveryAdviceNo( const basar::VarString & deliveryAdviceNo );
	void setDeliveryAdvicePosNo( const basar::Int32 deliveryAdvicePosNo );

	void setPharmosOrderNo(const basar::Int32 pharmosOrderNo);
	void setPharmosOrderPosNo(const basar::Int32 pharmosOrderPosNo);
	void setCscOrderPosNo( const basar::Int32 cscOrderPosNo );
	void setArticleNo( const basar::Int32 articleNo );
	void setArticleCode( const basar::VarString & articleCode );
	void setCodeType( const basar::Int16 codeType );
	void setQuantityOrdered( const basar::Int32 qtyOrdered );
	void setQuantityConfirmed( const basar::Int32 qtyConfirmed );
	void setQuantityRebateInKind( const basar::Int32 qtyRebateInKind );
	void setQuantityInvoiced( const basar::Int32 qtyInvoiced );
	void setLineReference( const basar::VarString & lineReference );
	void setVat(const basar::VarString & vat);
	void setVatPercentage(const basar::Decimal & vatPercentage);
	void setInvoicedPrice( const basar::Decimal & invoicedPrice );
	void setLogisticServiceCost( const basar::Decimal & logisticServiceCost );
	void setMinLogisticServiceCostValue( const basar::Decimal & minlogisticServiceCostValue );
	void setLineType( const basar::Int16 lineType );
	void setArticleName(const basar::VarString& articleName);
	void setArticleUnit(const basar::VarString& articleUnit);
	void setPharmaceuticalForm(const basar::VarString& pharmaceuticalForm);
	void setBasePrice(const basar::Decimal& basePrice);
	void setPharmacySellPrice( const basar::Decimal& pharmacySellPrice);
    void setQuantityFeeCalculation(const basar::Int32 qtyFeeCalculation);
    void setPrintedPricePerPiece(const basar::Decimal & printedPricePerPiece);
    void setLineValue(const basar::Decimal & lineValue);
    void setLineFee(const basar::Decimal& lineFee);
    void setPackageFee(const basar::Decimal& packageFee);

//private:
	DeliveryAdviceLinePtr m_DeliveryAdviceLine;
	DeliveryAdvicePtr m_DeliveryAdvice;

};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEMAPPER_BASE_H
