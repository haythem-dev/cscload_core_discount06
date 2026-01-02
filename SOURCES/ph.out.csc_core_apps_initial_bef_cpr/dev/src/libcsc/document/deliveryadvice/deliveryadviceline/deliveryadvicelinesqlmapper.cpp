#include "deliveryadvicelinesqlmapper.h"
#include "deliveryadviceline.h"
#include <libbasarcmnutil_date.h>
#include <document/deliveryadvice/deliveryadvice.h>

namespace libcsc {
namespace document {

DeliveryAdviceLineSQLMapper::DeliveryAdviceLineSQLMapper(DeliveryAdviceLinePtr deliveryAdviceLine, const DeliveryAdvicePtr& deliveryAdvice, const basar::db::sql::ResultsetRef resultSet) :
	DeliveryAdviceLineMapperBase(deliveryAdviceLine, deliveryAdvice),
	m_ResultSet(resultSet)
{
}

DeliveryAdviceLineSQLMapper::~DeliveryAdviceLineSQLMapper()
{
}

const basar::VarString DeliveryAdviceLineSQLMapper::getSelectSQL(
	const basar::VarString & dbName,
	const basar::Int16 branchNo,
	const basar::Int32 customerNo,
	const basar::Date& deliveryAdviceDate,
	const basar::VarString & deliveryAdviceNo,
	const bool onlyInvoicedLines)
{
	std::stringstream sSql;

	sSql <<
		"SELECT "
		"branchno, "
		"customerno, "
		"deliveryadvicedate, "
		"deliveryadviceno, "
		"deliveryadviceposno, "
		"pharmosorderno, "
		"pharmosorderposno, "
		"cscorderposno, "
		"articleno, "
		"article_code, "
		"code_type, "
		"qty_ordered, "
		"qty_confirmed, "
		"qty_rebateinkind, "
		"qty_invoiced, "
		"linereference, "
		"vat, "
		"vatpercentage, "
		"invoicedprice, "
		"logisticservicecost, "
		"minlogisticservicecostvalue, "
		"linetype, "
		"articlename, "
		"articleunit, "
		"pharmaceuticalform, "
		"baseprice, "
		"pharmacysellprice, "
        "qty_feecalculation, "
        "printedpriceperpiece, "
        "linevalue "
		"FROM " << dbName << ":deliveryadviceline "
		"WHERE ";
	sSql << " branchno = " << branchNo << " and customerno = " << customerNo << " and deliveryadvicedate = " << deliveryAdviceDate.getDate() <<
		" and deliveryadviceno = '" << deliveryAdviceNo << "'";

	if (onlyInvoicedLines)
	{
		sSql << " AND qty_invoiced > 0";
	}

	return sSql.str();
}


const basar::VarString DeliveryAdviceLineSQLMapper::getSelectSingleSQL(
	const basar::VarString& dbName,
	const basar::Int16 branchNo,
	const basar::Int32 customerNo,
	const basar::Date& deliveryAdviceDate,
	const basar::VarString& deliveryAdviceNo,
	const basar::Int32 deliveryAdvicePosNo)
{
	std::stringstream sSql;

	sSql <<
		"SELECT "
		"branchno, "
		"customerno, "
		"deliveryadvicedate, "
		"deliveryadviceno, "
		"deliveryadviceposno, "
		"pharmosorderno, "
		"pharmosorderposno, "
		"cscorderposno, "
		"articleno, "
		"article_code, "
		"code_type, "
		"qty_ordered, "
		"qty_confirmed, "
		"qty_rebateinkind, "
		"qty_invoiced, "
		"linereference, "
		"vat, "
		"vatpercentage, "
		"invoicedprice, "
		"logisticservicecost, "
		"minlogisticservicecostvalue, "
		"linetype, "
		"articlename, "
		"articleunit, "
		"pharmaceuticalform, "
		"baseprice, "
		"pharmacysellprice, "
        "qty_feecalculation, "
        "printedpriceperpiece, "
        "linevalue "
		"FROM " << dbName << ":deliveryadviceline "
		"WHERE ";
	sSql << " branchno = " << branchNo << " and customerno = " << customerNo << " and deliveryadvicedate = " << deliveryAdviceDate.getDate() <<
		" and deliveryadviceno = '" << deliveryAdviceNo << "' and deliveryadviceposno = " << deliveryAdvicePosNo;
	return sSql.str();
}


//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DeliveryAdviceLineSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo						( m_ResultSet.getInt16("branchno") );
	setCustomerNo					( m_ResultSet.getInt32("customerno") );
	setDeliveryAdviceDate			( basar::Date(m_ResultSet.getInt32("deliveryadvicedate")) );
	setDeliveryAdviceNo				( m_ResultSet.getString("deliveryadviceno") );
	setDeliveryAdvicePosNo			( m_ResultSet.getInt32("deliveryadviceposno") );

	setPharmosOrderNo				( m_ResultSet.getInt32("pharmosorderno") );
	setPharmosOrderPosNo			( m_ResultSet.getInt32("pharmosorderposno") );
	setCscOrderPosNo				( m_ResultSet.getInt32("cscorderposno") );
	setArticleNo					( m_ResultSet.getInt32("articleno") );
	setArticleCode					( m_ResultSet.getString("article_code") );
	setCodeType						( m_ResultSet.getInt16("code_type") );
	setQuantityOrdered				( m_ResultSet.getInt32("qty_ordered") );
	setQuantityConfirmed			( m_ResultSet.getInt32("qty_confirmed") );
	setQuantityRebateInKind			( m_ResultSet.getInt32("qty_rebateinkind") );
	setQuantityInvoiced				( m_ResultSet.getInt32("qty_invoiced") );
	setLineReference				( m_ResultSet.getString("linereference") );
	setVat							( m_ResultSet.getString("vat") );
	setVatPercentage				( m_ResultSet.getDecimal("vatpercentage") );
	setInvoicedPrice				( m_ResultSet.getDecimal("invoicedprice") );
	setLogisticServiceCost			( m_ResultSet.getDecimal("logisticservicecost") );
	setMinLogisticServiceCostValue	( m_ResultSet.getDecimal("minlogisticservicecostvalue") );
	setLineType						( m_ResultSet.getInt16("linetype") );
	setArticleName					( m_ResultSet.getString("articlename") );
	setArticleUnit					( m_ResultSet.getString("articleunit") );
	setPharmaceuticalForm			( m_ResultSet.getString("pharmaceuticalform") );
	setBasePrice					( m_ResultSet.getDecimal("baseprice") );
	setPharmacySellPrice			( m_ResultSet.getDecimal("pharmacysellprice") );
	setQuantityFeeCalculation		( m_ResultSet.getInt32("qty_feecalculation") );
	setPrintedPricePerPiece			( m_ResultSet.getDecimal("printedpriceperpiece") );
	setLineValue    				( m_ResultSet.getDecimal("linevalue") );


    // Following logic is impelemted on behalf of: CPR-190072 - PKS1 - CSC: Requirement 6008: XML Lieferschein - Übertragung Kosten pro Zeile/Packung (Topic #6)
    basar::Decimal lineFee(0);
    basar::Decimal packageFee(0);

    if (m_DeliveryAdvice.get() != NULL)
    {
        const basar::Int32& qtyFeeCalculation = m_DeliveryAdviceLine->getQuantityFeeCalculation();

        if (qtyFeeCalculation > 0)
        {
            lineFee = m_DeliveryAdvice->getLineFee();
        }

        packageFee = m_DeliveryAdvice->getPackageFee() * qtyFeeCalculation;
    }

    //NOTE: this must be always called, else the necessary "m_DeliveryAdviceLine->m_*Fee.setClean();" is not called, which would result in PropertyUnsetException !!
    setLineFee                      (lineFee);
    setPackageFee                   (packageFee);
}

} // end namespace document
} // end namespace libcsc
