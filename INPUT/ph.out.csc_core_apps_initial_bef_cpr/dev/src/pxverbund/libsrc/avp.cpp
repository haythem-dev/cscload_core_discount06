/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Calculate avp (selling price for pharmacies)

REVISION HISTORY

04 May 2010 V1.00 REV 00 written by Beatrix Trömel
*/

#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxartprc.hpp"
#include "pxcstbas.hpp"
#include "pxcstprint.hpp"
#include "pxgeneralcalcavp.hpp"

#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"

#include "pxcstcalcavp.hpp"
#include "pxorderposcalcmode.hpp"
#include <boost/numeric/conversion/cast.hpp>

#include "calcavp.h"
#include <logger/loggerpool.h>

double pxOrderItem :: CalcAvp()
{
 	if( false == Session()->isBulgaria() )
    {
		return 0;
    }

	pxCustBase * customer = Order().Customer();
	if( NULL == customer )
    {
		return 0;
    }

	// table cstcalcavp
	basar::Decimal customerArticleSurchargePct( 0 );
	customerArticleSurchargePct.trunc(2);
    basar::Decimal customerArticleDeductionPct( 0 );
	customerArticleDeductionPct.trunc(2);
    short customerArticlePriceBasis = 0;

	pxArtBase * articleBase = this->ArtBase();
	if( NULL == articleBase )
    {
		return 0;
    }

	pxCstCalcAvp * cstcalcavp = new pxCstCalcAvp( Session(), customer->Vertriebszentrum(), customer->IDFNr(), 0, PreisTyp(), articleBase->AbdaCode() );
	if( NULL == cstcalcavp )
{
		return 0;
    }

	if( 0 == cstcalcavp->Get() )
        {
		customerArticleSurchargePct = basar::Decimal( cstcalcavp->SurchargePct() );
		customerArticleDeductionPct = basar::Decimal( cstcalcavp->DeductionPct() );
		customerArticlePriceBasis = cstcalcavp->SurchargeBasic();
        }
	/*
    std::stringstream s1;
    s1 << "1. pxOrderItem :: CalcAvp(customerArticleSurchargePct =" << customerArticleSurchargePct.toFloat64() << 
	",customerArticleDeductionPct=" << customerArticleDeductionPct.toFloat64() << 
	", customerArticlePriceBasis=" << customerArticlePriceBasis << ")";
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s1.str());
	*/
	// table kunde
	basar::Decimal customerSurchargePctKK( customer->SurchargePctKK() );
	customerSurchargePctKK.trunc(2);
    basar::Decimal customerDeductionPctKK( customer->DeductionPctKK() );
	customerDeductionPctKK.trunc(2);
    short customerSurchargeBasicKK = customer->SurchargeBasicKK();
	
	basar::Decimal customerSurchargePct( customer->SurchargePct() );
	customerSurchargePct.trunc(2);
    basar::Decimal customerDeductionPct( customer->DeductionPct() );
	customerDeductionPct.trunc(2);
    short customerSurchargeBasic = customer->SurchargeBasic();
	/*
	std::stringstream s2;
    s2 << "2. table kunde( customerSurchargePctKK = " << customerSurchargePctKK.toFloat64() << 
	", customerDeductionPctKK =" << customerDeductionPctKK.toFloat64() << 
	", customerSurchargeBasicKK = " << customerSurchargeBasicKK << 
	", customerSurchargePct =" << customerSurchargePct.toFloat64() << 
	",customerDeductionPct =" << customerDeductionPct.toFloat64() << 
	",customerSurchargeBasic =" << customerSurchargeBasic << 
	")";
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s2.str());
	*/
	// table generalcalcavp
	basar::Decimal generalPercentPreScript( 25 );
	generalPercentPreScript.trunc(2);
	basar::Decimal generalPercentNoPreScript( 25 );
	generalPercentNoPreScript.trunc(2);

	if( NULL != Session()->GeneralCalcAvpList() )
    {
		pxGeneralCalcAvp * generalCalcAvp = Session()->GeneralCalcAvpList()->Find( articleBase->PriceGroup(), PreisTyp() );
		if( NULL != generalCalcAvp )
        {
			generalPercentPreScript = basar::Decimal( generalCalcAvp->PercentPreScript() );
			generalPercentNoPreScript = basar::Decimal( generalCalcAvp->PercentNoPerScript() );
			/*
			std::stringstream s3;
			s3 << "3.( generalPercentPreScript =" << generalPercentPreScript.toFloat64() << 
			",generalPercentNoPreScript = " << generalPercentNoPreScript.toFloat64() << 
			")";
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s3.str());
			*/
        }
        else
        {
			generalCalcAvp = Session()->GeneralCalcAvpList()->Find( 99, PreisTyp() );
			if( NULL != generalCalcAvp )
            {
				generalPercentPreScript = basar::Decimal( generalCalcAvp->PercentPreScript() );
				generalPercentNoPreScript = basar::Decimal( generalCalcAvp->PercentNoPerScript() );
				/*
				std::stringstream s4;
				s4 << "4.( generalPercentPreScript =" << generalPercentPreScript.toFloat64() << 
				",generalPercentNoPreScript = " << generalPercentNoPreScript.toFloat64() << ")";
				BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s4.str());
				*/
            }
        }
    }

	basar::Decimal gep( 0 );
	gep.trunc(2);
	basar::Decimal aep( 0 );
	aep.trunc(2);
	basar::Decimal maxAvp( 0 );
	maxAvp.trunc(2);
	
	pxArtPriceList * priceList = this->ArtPriceList();
	if( NULL == priceList )
    {
		/*
			std::stringstream s5;
			s5 << "5.( pxArtPriceList is NULL so returning" << ")";
			BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s5.str());
		*/
		return 0;
    }

	if( HEALTHFUND_PRICE == PreisTyp() )
    {
		gep = basar::Decimal( PreisEKGrossoKK() );
		aep = basar::Decimal( PreisEKApoKK() );
		maxAvp = basar::Decimal( priceList->GetMaxAvp( HEALTHFUND_PRICE ) );
		/*
		std::stringstream s6;
		s6 << "6.( PreisType is HealthFund gep =" << gep.toFloat64() << 
		",aep = " << aep.toFloat64() << 
		",maxAvp =" << maxAvp << ")";
		BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s6.str());
		*/
		
    }
    else
    {
		gep = basar::Decimal( PreisEKGrossoFV() );
		aep = basar::Decimal( PreisEKApoFV() );
		maxAvp = basar::Decimal( priceList->GetMaxAvp( FREESALE_PRICE ) );
		/*
		std::stringstream s7;
		s7 << "7.( PreisType is NOT HealthFund gep =" << gep.toFloat64() << 
		",aep = " << aep.toFloat64() << 
		",maxAvp =" << maxAvp << ")";
		BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s7.str());
		*/
    }

	const basar::Decimal vat( SalesTaxRate() / 100 );
	const basar::Decimal preisFaktur( PreisFaktur() );
	const basar::Decimal maxSurcharge( Order().Param()->MaxSurCharge() );


	const bool isMedicine = calcavp::isMedicine( articleBase->PriceGroup() );

	const pxArtClass & articleClass = articleBase->ArtClass();
	const bool isPrescriptionNeeded = ( 0 != articleClass.IsRezeptPflichtig() );
	const bool isVatRegistered = ( 1 == customer->VatRegistered() );
	const bool isHealthFund = ( HEALTHFUND_PRICE == PreisTyp() );
	
	bool isDeduction = false;
	if ( customer->CstPrintList() )
    {
		pxCstPrint * cstPrint = customer->CstPrintList()->Find( PreisTyp() );
		if( NULL != cstPrint )
        {
			isDeduction = ( 0 != cstPrint->DeductionAvp() );
        }
    }
	/*
	std::stringstream s8;
	s8 << "8. caalling calcavp::CalcAvp( vat =" << vat.toFloat64() << 
	",preisFaktur = " << preisFaktur.toFloat64() << 
	",maxSurcharge =" << maxSurcharge.toFloat64() <<
	",isMedicine =" << isMedicine <<
	",isPrescriptionNeeded =" << isPrescriptionNeeded <<
	",isVatRegistered =" << isVatRegistered <<
	",isHealthFund =" << isHealthFund <<
	",isDeduction =" << isDeduction <<
	")";
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s8.str());
	*/
	
	basar::Decimal avp(0);
	avp.trunc(2);
	basar::Decimal avpDiscounted(0);
	avpDiscounted.trunc(2);
	basar::Decimal surchargePct(0);
	surchargePct.trunc(2);
	basar::Decimal deductionPct(0);
	deductionPct.trunc(2);
	basar::Decimal surcharge(0);
	surcharge.trunc(2);
	basar::Decimal surchargeDiscounted(0);
	surchargeDiscounted.trunc(2);
	/*
	std::stringstream strCA;
	strCA << "****CALCAVP Art and  Customer( " <<
	", Artikel Number = " << articleBase->ArtikelNr() <<
	", Customer Branch = " << customer->Vertriebszentrum() <<
	", Customer Number = " << customer->IDFNr() <<
	", PreisTyp = " << PreisTyp() <<
	", isHealthFund = " << isHealthFund <<
	", isDeduction = " << isDeduction <<
	", isMedicine = " << isMedicine <<
	", isPrescriptionNeeded = " << isPrescriptionNeeded <<
	"****)";
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), strCA.str());
	*/
	
	calcavp::CalcAvp(
		customerArticleSurchargePct,
		customerArticleDeductionPct,
		customerArticlePriceBasis,

		customerSurchargePctKK,
		customerDeductionPctKK,
		customerSurchargeBasicKK,

		customerSurchargePct,
		customerDeductionPct,
		customerSurchargeBasic,

		generalPercentPreScript,
		generalPercentNoPreScript,

		gep,
		aep,
		vat,
		preisFaktur,
		maxSurcharge, 
		maxAvp,

		isMedicine,
		isPrescriptionNeeded,
		isVatRegistered,
		isHealthFund,
		isDeduction,

		avp,
		avpDiscounted,
		surchargePct,
		deductionPct,
		surcharge,
		surchargeDiscounted
			);
	/*
	if( avpDiscounted.toFloat64() <= 0 || surchargeDiscounted.toFloat64() <= 0 ) // write log only when avpdiscountes ,surchargeDiscounted is less then equal to 0
	{
		std::stringstream s9;
		s9 << "****CALCAVP write to table Kdauftrposrechart( " <<
		", Artikel Number = " << articleBase->ArtikelNr() <<
		", Customer Branch = " << customer->Vertriebszentrum() <<
		", Customer Number = " << customer->IDFNr() <<
		", PreisTyp = " << PreisTyp() <<
		", customerArticleSurchargePct =" << customerArticleSurchargePct.toFloat64() << 
		", customerArticleDeductionPct = " << customerArticleDeductionPct.toFloat64() <<
		", customerArticlePriceBasis = " << customerArticlePriceBasis <<
		", customerSurchargePctKK = " << customerSurchargePctKK.toFloat64() <<
		", customerDeductionPctKK = " << customerDeductionPctKK.toFloat64() <<
		", customerSurchargeBasicKK = " << customerSurchargeBasicKK <<
		", customerSurchargePct = " << customerSurchargePct.toFloat64() <<
		", customerDeductionPct = " << customerDeductionPct.toFloat64() <<
		", customerSurchargeBasic = " << customerSurchargeBasic <<
		", avp =" << avp.toFloat64() << 
		",avpDiscounted = " << avpDiscounted.toFloat64() << 
		",surchargePct =" << surchargePct.toFloat64() <<
		",deductionPct =" << deductionPct.toFloat64() <<
		",surcharge =" << surcharge.toFloat64() <<
		",surchargeDiscounted =" << surchargeDiscounted.toFloat64() <<
		"****)";
		BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s9.str());
	}*/
	
	//writeToDB( surchargePct.toFloat64(), deductionPct.toFloat64(), surcharge.toFloat64(), avp.toFloat64(), surchargeDiscounted.toFloat64(), avpDiscounted.toFloat64() );
	writeToDB( surchargePct, deductionPct, surcharge, avp, surchargeDiscounted, avpDiscounted );
	return avp.toFloat64();
}

//*********************************************** writeToDB *******************************************************
//
// Descr:   Writes data into KSC table kdauftrposrechart
//
// Param:       -
//
//int pxOrderItem :: writeToDB(double SurchargePct, double DeductionPct, double SurchargeCalc, double Avp, double SurchargeCalcDis, double AvpDis)
int pxOrderItem :: writeToDB(basar::Decimal SurchargePct, basar::Decimal DeductionPct, basar::Decimal SurchargeCalc, basar::Decimal Avp, basar::Decimal SurchargeCalcDis, basar::Decimal AvpDis)
{
    if("BG" != Session()->Country())
        return -1;

	
	SurchargePct.trunc(2);
	DeductionPct.trunc(2);
	SurchargeCalc.trunc(2);
	Avp.trunc(2);
	SurchargeCalcDis.trunc(2);
	AvpDis.trunc(2);
    // table kdauftrposrechart:
    if(!OrderPosCalcMode_)
    {
        OrderPosCalcMode_ = new pxOrderPosCalcMode(Session(), this->KdAuftragNr(), this->PosNr());
        if(!OrderPosCalcMode_->Get(cDBGET_READONLY))   // 1: recordset does not exist
        {
            delete OrderPosCalcMode_;
            OrderPosCalcMode_ = NULL;
            return ErrorState();
        }
    }
	/*
	std::stringstream s9;
	s9 << "A.writeToDB SurchargePct =" << SurchargePct.toFloat64() << 
	",DeductionPct = " << DeductionPct.toFloat64() << 
	",SurchargeCalc =" << SurchargeCalc.toFloat64() <<
	",Avp =" << Avp.toFloat64() <<
	",SurchargeCalcDis =" << SurchargeCalcDis.toFloat64() <<
	",AvpDis =" << AvpDis.toFloat64() <<
	")";
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s9.str());
	*/
	
    OrderPosCalcMode_->SetSurchargePct(SurchargePct.toFloat64());
    OrderPosCalcMode_->SetDeductionPct(DeductionPct.toFloat64());
    OrderPosCalcMode_->SetSurchargeCalc(SurchargeCalc.toFloat64());
    OrderPosCalcMode_->SetCalcAvp(Avp.toFloat64());
    OrderPosCalcMode_->SetSurchargeCalcDis(SurchargeCalcDis.toFloat64());
    OrderPosCalcMode_->SetCalcAvpDis(AvpDis.toFloat64());
    OrderPosCalcMode_->Put();
    Error() = OrderPosCalcMode_->Error();
    return ErrorState();
}
