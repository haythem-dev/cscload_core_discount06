#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>

#include <document/deliveryadvice/deliveryadviceremarksptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinediscountptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetailsptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinereturnptr.h>
#include <document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlinkptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelineextrasatptr.h>

#include <pxorderremarktypes.hpp>

namespace libcsc {
namespace document {

class DeliveryAdviceLine
{
	friend class DeliveryAdviceLineMapperBase;
	friend class DeliveryAdviceRepository;

public:
	enum DeliveryAdviceLineTypeEnum
	{
		LINETYPE_NORMAL = 0,
		LINETYPE_IBT = 1,
		LINETYPE_RESTDELIVERY = 2
	};

	DeliveryAdviceLine();
	virtual ~DeliveryAdviceLine();

	virtual const basar::Int16&			getBranchNo() const;
	virtual const basar::Int32&			getCustomerNo() const;
	virtual const basar::Date&			getDeliveryAdviceDate() const;
	virtual const basar::VarString&		getDeliveryAdviceNo() const;

	virtual const basar::Int32&			getDeliveryAdvicePosNo() const;
	
	virtual const basar::Int32&			getPharmosOrderNo() const;
	virtual const basar::Int32&			getPharmosOrderPosNo() const;
	virtual const basar::Int32&			getCscOrderPosNo() const;
	virtual const basar::Int32&			getArticleNo() const;
	virtual const basar::VarString&		getArticleCode() const;
	virtual const basar::Int16&			getCodeType() const;
	virtual const basar::Int32&			getQuantityOrdered() const;
	virtual const basar::Int32&			getQuantityConfirmed() const;
	virtual const basar::Int32&			getQuantityRebateInKind() const;
	virtual const basar::Int32&			getQuantityInvoiced() const;
	virtual const basar::VarString&		getLineReference() const;
	virtual const basar::VarString&		getVat() const;
	virtual const basar::Decimal&		getVatPercentage() const;
	virtual const basar::Decimal&		getInvoicedPrice() const;
	virtual const basar::Decimal&		getLogisticServiceCost() const;
	virtual const basar::Decimal&		getMinLogisticServiceCostValue() const;
	virtual DeliveryAdviceLineTypeEnum	getLineType() const;
	virtual const basar::VarString&		getArticleName() const;
	virtual const basar::VarString&		getArticleUnit() const;
	virtual const basar::VarString&		getPharmaceuticalForm() const;
	virtual const basar::Decimal&		getBasePrice() const;
	virtual const basar::Decimal&		getPharmacySellPrice() const;
    virtual const basar::Int32&			getQuantityFeeCalculation() const;
    virtual const basar::Decimal&		getPrintedPricePerPiece() const;
    virtual const basar::Decimal&		getLineValue() const;

    // properties derived from DeliveryAdvice(Head) and specialized here based on m_QuantityFeeCalculation value:
    virtual const basar::Decimal&		getLineFee() const;
    virtual const basar::Decimal&		getPackageFee() const;

	virtual const DeliveryAdviceRemarksCollectionPtr		getRemarksCollection() const;
	virtual const DeliveryAdviceLineDiscountCollectionPtr	getDiscountCollection() const;
	virtual const DeliveryAdviceLineDetailsCollectionPtr	getDetailsCollection() const;
	virtual const DeliveryAdviceLineReturnCollectionPtr		getReturnCollection() const;
	virtual const DeliveryAdviceLineIbtLinkPtr				getIbtLink() const;
    virtual const DeliveryAdviceLineExtrasATPtr				getExtrasAT() const;


private:
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::Date						m_DeliveryAdviceDate;
	libcsc::VarString					m_DeliveryAdviceNo;

	libcsc::Int32						m_DeliveryAdvicePosNo;

	libcsc::Int32						m_PharmosOrderNo;
	libcsc::Int32						m_PharmosOrderPosNo;
	libcsc::Int32						m_CscOrderPosNo;
	libcsc::Int32						m_ArticleNo;
	libcsc::VarString					m_ArticleCode;
	libcsc::Int16						m_CodeType;
	libcsc::Int32						m_QuantityOrdered;
	libcsc::Int32						m_QuantityConfirmed;
	libcsc::Int32						m_QuantityRebateInKind;
	libcsc::Int32						m_QuantityInvoiced;
	libcsc::VarString					m_LineReference;
	libcsc::VarString					m_Vat;
	libcsc::Decimal						m_VatPercentage;
	libcsc::Decimal						m_InvoicedPrice;
	libcsc::Decimal						m_LogisticServiceCost;
	libcsc::Decimal						m_MinLogisticServiceCostValue;
	libcsc::Int16						m_LineType;
	libcsc::VarString					m_ArticleName;
	libcsc::VarString					m_ArticleUnit;
	libcsc::VarString					m_PharmaceuticalForm;
	libcsc::Decimal						m_BasePrice;
	libcsc::Decimal						m_PharmacySellPrice;
    libcsc::Int32						m_QuantityFeeCalculation;
    libcsc::Decimal						m_PrintedPricePerPiece;
    libcsc::Decimal						m_LineValue;

    // properties derived from DeliveryAdvice(Head) and specialized here based on m_QuantityFeeCalculation value:
    libcsc::Decimal						m_LineFee;
    libcsc::Decimal						m_PackageFee;

	DeliveryAdviceRemarksCollectionPtr		m_Remarks;
	DeliveryAdviceLineDiscountCollectionPtr	m_Discounts;
	DeliveryAdviceLineDetailsCollectionPtr	m_Details;
	DeliveryAdviceLineReturnCollectionPtr	m_Return;
	DeliveryAdviceLineIbtLinkPtr			m_IbtLink;
	DeliveryAdviceLineExtrasATPtr			m_ExtrasAT;
};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_H
