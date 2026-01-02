#include "calcavp.h"
#include <logger/loggerpool.h>
namespace calcavp
{
static basar::Decimal zero( 0 );

// TODO DK: structs?
 const basar::Decimal  CalcAvp(
    const basar::Decimal & customerArticleSurchargePct, // aus cstcalcavp
    const basar::Decimal & customerArticleDeductionPct, // aus cstcalcavp
    const short customerArticlePriceBasis, // aus cstcalcavp

    const basar::Decimal & customerSurchargePctKK, // aus kunde
    const basar::Decimal & customerDeductionPctKK, // aus kunde
    const short customerSurchargeBasicKK, // aus kunde

    const basar::Decimal & customerSurchargePct, // aus kunde
    const basar::Decimal & customerDeductionPct, // aus kunde
    const short customerSurchargeBasic, // aus kunde

    const basar::Decimal & generalPercentPreScript, // aus generalcalcavp
    const basar::Decimal & generalPercentNoPreScript,   // aus generalcalcavp

    const basar::Decimal & gep,
    const basar::Decimal & aep,
    const basar::Decimal & vat,
    const basar::Decimal & PreisFaktur,
    const basar::Decimal & maxSurcharge,
    const basar::Decimal & maxAvp,

    const bool isMedicine,
    const bool isPrescriptionNeeded,
    const bool isVatRegistered,
    const bool isHealthFund,
    const bool isDeduction,

    basar::Decimal & avp,
    basar::Decimal & avpDiscounted,
    basar::Decimal & surchargePct,
    basar::Decimal & deductionPct,
    basar::Decimal & surcharge,
    basar::Decimal & surchargeDiscounted
        )
{
    avp = basar::Decimal( 0 );
    avpDiscounted = basar::Decimal( 0 );
    surchargePct = basar::Decimal( 0 );
    deductionPct = basar::Decimal( 0 );
    surcharge = basar::Decimal( 0 );
    surchargeDiscounted = basar::Decimal( 0 );

    short PriceBasis = 0;   // TODO DK: rename ( 0=AEP, 1=GEP )
    basar::Decimal basePrice( 0 );
    basePrice.trunc(2);

    if( isHealthFund )
    {
        avp = maxAvp;
        avp.trunc(2);
        /*
        std::stringstream s1;
        s1 << "A. CalcAvp( This is HEalthfund avp =" << avp.toFloat64() << ")";
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s1.str());
        */
    }

    if(    false == isHealthFund
        || isDeduction )
    {
        getSurchargePercentage(
            customerArticleSurchargePct, customerArticleDeductionPct, customerArticlePriceBasis,
            customerSurchargePctKK, customerDeductionPctKK, customerSurchargeBasicKK,
            customerSurchargePct, customerDeductionPct, customerSurchargeBasic,
            generalPercentPreScript, generalPercentNoPreScript,
            isPrescriptionNeeded, isHealthFund,
            PriceBasis, surchargePct, deductionPct  );
        if( 0 == PriceBasis )
        {
            basePrice = aep;
            /*
            std::stringstream s3;
            s3 << "(L.)PriceBasis = 0 SO BasePrice = aep = " << basePrice.toFloat64() << "surchargePCT = " << surchargePct.toFloat64()
            << "deductionPCT = " << deductionPct.toFloat64() << ")";
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s3.str());
            */
        }
        else
        {
            basePrice = gep;
            /*
            std::stringstream s4;
            s4 << "(M.)BasePrice = gep = " <<  basePrice.toFloat64() << "surchargePCT = " << surchargePct.toFloat64()
            << "deductionPCT = " << deductionPct.toFloat64() << ")";
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s4.str());
            */
        }
        surcharge = CalcSurcharge( basePrice, surchargePct, maxSurcharge, vat, isMedicine, isVatRegistered );
        surcharge.trunc(2);
        avp = ( basar::Decimal( 1 ) + vat ) * aep + surcharge;
        avp.trunc(2);
        /*
        std::stringstream s5;
        s5 << "(R.)AEP = " << aep.toFloat64() << " SURCHARGE = " << surcharge.toFloat64() <<
        " PHARMACYSELLPRICE AVP = " << avp.toFloat64() << ")";
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s5.str());
        */

        if(    avp > maxAvp
            && maxAvp > zero )
        {
            avp = maxAvp;
            avp.trunc(2);
            /*
            std::stringstream s6;
            s6 << "(S.)AVP > maxAVP so  AVP = maxAvp =" <<  avp.toFloat64() << ")";
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s6.str());
            */
        }
    }


    if(    false == isHealthFund
        || !isDeduction )
    {
        getSurchargePercentage(
            customerArticleSurchargePct, customerArticleDeductionPct, customerArticlePriceBasis,
            customerSurchargePctKK, customerDeductionPctKK, customerSurchargeBasicKK,
            customerSurchargePct, customerDeductionPct, customerSurchargeBasic,
            generalPercentPreScript, generalPercentNoPreScript,
            isPrescriptionNeeded, isHealthFund,
            PriceBasis, surchargePct, deductionPct  );
        if( 0 == PriceBasis )
        {
            basePrice = PreisFaktur;
            basePrice.trunc(2);
            /*
            std::stringstream s8;
            s8 << "(U.)PriceBasis = 0 , BasePrice = PreisFaktur = " << basePrice.toFloat64() << "surchargePCT = " << surchargePct.toFloat64()
            << "deductionPCT = " << deductionPct.toFloat64() << ")";
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s8.str());
            */
        }
        else
        {
            basePrice = gep;
            basePrice.trunc(2);
            /*
            std::stringstream s9;
            s9 << "(V.)BasePrice = gep = " <<  basePrice.toFloat64() << "surchargePCT = " << surchargePct.toFloat64()
            << "deductionPCT = " << deductionPct.toFloat64() << ")";
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s9.str());
            */
        }
        surchargeDiscounted = CalcSurcharge( basePrice, surchargePct, maxSurcharge, vat, isMedicine, isVatRegistered );
        surchargeDiscounted.trunc(2);
        avpDiscounted = ( basar::Decimal( 1 ) + vat ) * PreisFaktur + surchargeDiscounted;
        avpDiscounted.trunc(2);
        /*
        std::stringstream s10;
        s10 << "(W.) AVPDISCOUNTED " << avpDiscounted.toFloat64() << "PreisFaktur = " << PreisFaktur.toFloat64() <<
        "surchargeDiscounted = " << surchargeDiscounted.toFloat64() << ")";
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s10.str());
        */
        if(    avpDiscounted > maxAvp
            && maxAvp > zero )
        {
            avpDiscounted = maxAvp;
            avpDiscounted.trunc(2);
            /*
            std::stringstream s11;
            s11 << "(X.)Since avpDiscounted > maxAvp,  avpDiscounted =" << avpDiscounted.toFloat64() << "maxAvp = " << maxAvp.toFloat64() << ")";
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s11.str());
            */
        }
    }

    std::stringstream s12;
    s12 << "****CALCAVP calcualtion avpDiscounted = " << avpDiscounted.toFloat64() <<
    ", surchargeDiscounted = " << surchargeDiscounted.toFloat64() <<
    ", maxAvp = " << maxAvp.toFloat64() <<
    ", basePrice = " << basePrice.toFloat64() <<
    ", surchargePct = " << surchargePct.toFloat64() <<
    ", maxSurcharge = " << maxSurcharge.toFloat64() <<
    ", vat = " << vat.toFloat64() <<
    ", PreisFaktur = " << PreisFaktur.toFloat64() <<
    ", PriceBasis = " << PriceBasis <<
    ", customerArticleSurchargePct = " << customerArticleSurchargePct.toFloat64() <<
    ", customerArticleDeductionPct = " << customerArticleDeductionPct.toFloat64() <<
    ", customerArticlePriceBasis = " << customerArticlePriceBasis <<
    ", customerSurchargePctKK = " << customerSurchargePctKK.toFloat64() <<
    ", customerDeductionPctKK = " << customerDeductionPctKK.toFloat64() <<
    ", customerSurchargeBasicKK = " << customerSurchargeBasicKK <<
    ", customerSurchargePct = " << customerSurchargePct.toFloat64() <<
    ", customerDeductionPct = " << customerDeductionPct.toFloat64() <<
    ", customerSurchargeBasic = " << customerSurchargeBasic <<
    ", generalPercentPreScript = " << generalPercentPreScript.toFloat64() <<
    ", generalPercentNoPreScript = " <<  generalPercentNoPreScript.toFloat64() <<
    ", gep = " << gep.toFloat64() <<
    ", aep = " << aep.toFloat64() <<
    ", isMedicine = " << isMedicine <<
    ", isPrescriptionNeeded = " << isPrescriptionNeeded <<
    ", isVatRegistered = " << isVatRegistered <<
    ", isHealthFund = " << isHealthFund <<
    ", isDeduction = " << isDeduction <<
    ", avp = " << avp.toFloat64() <<
    ", deductionPct = " << deductionPct.toFloat64() <<
    ", surcharge = " << surcharge.toFloat64() <<
    "****)";
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s12.str());

    /*
    std::stringstream s12;
    s12 << "(Y.) avp returned is AVP =" << avp.toFloat64() << ")";
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s12.str());
    */
    return avp;
}

const basar::Decimal getSurchargePercentage(
    const basar::Decimal & customerArticleSurchargePct, // aus cstcalcavp
    const basar::Decimal & customerArticleDeductionPct, // aus cstcalcavp
    const short customerArticlePriceBasis, // aus cstcalcavp

    const basar::Decimal & customerSurchargePctKK, // aus kunde
    const basar::Decimal & customerDeductionPctKK, // aus kunde
    const short customerSurchargeBasicKK, // aus kunde

    const basar::Decimal & customerSurchargePct, // aus kunde
    const basar::Decimal & customerDeductionPct, // aus kunde
    const short customerSurchargeBasic, // aus kunde

    const basar::Decimal & generalPercentPreScript, // aus generalcalcavp
    const basar::Decimal & generalPercentNoPreScript,   // aus generalcalcavp

    const bool isPrescriptionNeeded,
    const bool isHealthFund,

    short & PriceBasis,
    basar::Decimal & surchargePct,
    basar::Decimal & deductionPct
        )
{
    surchargePct = zero;
    deductionPct = zero;
    PriceBasis = 0; // 0=AEP, 1=GEP
    bool blnFound = false;

/*
Optimierungspotential:

select branchno, customerno from CSTCALCAVP where customerno=17
union
select filialnr, idfnr from kunde where idfnr=17

- union repräsentiert priorität
*/

    // Level 1: Gibt es einen Eintrag für Kunde + Artikel? (2a)
    if( customerArticleSurchargePct > zero || customerArticleDeductionPct > zero )
    {
        surchargePct = customerArticleSurchargePct;
        deductionPct = customerArticleDeductionPct;
        PriceBasis = customerArticlePriceBasis;

        if( surchargePct > zero ) // if ==0: take default value for surchargepct from table below
            blnFound = true;
        /*
        std::stringstream s2;
        s2 << "(D.)GSP Level1 surchargePct = " << surchargePct.toFloat64() <<
        " deductionPct =" << deductionPct.toFloat64() <<
        " PriceBasis =" << PriceBasis << ")";
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s2.str());
        */
    }

    // Level 2: Gibt es festen Zuschlagsprozentsatz für Kunden (s. Kundenstamm) (2b):
    if( !blnFound )
    {
        if( isHealthFund )
        {
            if( customerSurchargePctKK > zero || customerDeductionPctKK > zero )
            {
                surchargePct = customerSurchargePctKK;
                deductionPct = customerDeductionPctKK;
                PriceBasis = customerSurchargeBasicKK;

                if( surchargePct > zero ) // if ==0: take default value for surchargepct from table below
                        blnFound = true;
                /*
                std::stringstream s4;
                s4 << "(F.)GSP LEVEL2 KK surchargePct = " << surchargePct.toFloat64() <<
                " deductionPct =" << deductionPct.toFloat64() <<
                " PriceBasis =" << PriceBasis << ")";
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s4.str());
                */
            }
        }
        else
        {
            if( customerSurchargePct > zero || customerDeductionPct > zero )
            {
                surchargePct = customerSurchargePct;
                deductionPct = customerDeductionPct;
                PriceBasis = customerSurchargeBasic;

                if( surchargePct > zero ) // if ==0: take default value for surchargepct from table below
                        blnFound = true;
                /*
                std::stringstream s6;
                s6 << "(G.)LEVEL2: Not KK, surchargePct = " << surchargePct.toFloat64() <<
                " deductionPct =" << deductionPct.toFloat64() <<
                " PriceBasis =" << PriceBasis << ")";
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s6.str());
                */
            }
        }
    }

    // Level 3: Nimm Zuschlagsprozentsatz in Abhängigkeit von Preisgruppe und KZ isMedicine (2c)
    if( !blnFound )
    {
        if( isPrescriptionNeeded )
            surchargePct = generalPercentPreScript;
        else
            surchargePct = generalPercentNoPreScript;
        PriceBasis = customerSurchargeBasic;
        blnFound = true;

        /*
        std::stringstream s7;
        s7 << "(H.)Level 3 isPrescriptionNeeded = " << isPrescriptionNeeded <<
        " surchargePct = " << surchargePct.toFloat64() <<
        " PriceBasis =" << PriceBasis << ")";
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s7.str());
        */
    }
    /*
    std::stringstream s8;
    s8 << "(J.)GSP Returns surchargePct - deductionPct = " << surchargePct.toFloat64() << ")";
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s8.str());
    */
    // (2d):
    surchargePct = surchargePct - deductionPct;

    // (2e):
    if( surchargePct < zero )
        return zero;
    return surchargePct;
}

const basar::Decimal CalcSurcharge(
    const basar::Decimal & basePrice,
    const basar::Decimal & surchargePct,
    const basar::Decimal & maxSurcharge,
    const basar::Decimal & vat,
    const bool isMedicine,
    const bool isVatRegistered
        )
{
    /*
    std::stringstream s1;
    s1 << "(N.) In CalcSurcharge parameters are basePrice = " << basePrice.toFloat64() <<
    " ,surchargePct = " << surchargePct.toFloat64() <<
    " ,maxSurcharge = " << maxSurcharge.toFloat64() <<
    " ,vat = " << vat.toFloat64() <<
    ", isMedicine =" << isMedicine <<
    ", isVatRegistered =" << isVatRegistered <<
    ")";
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s1.str());
    */
    basar::Decimal surcharge = basePrice * surchargePct / basar::Decimal( 100 );
    surcharge.trunc( 2 );
    /*
    std::stringstream s2;
    s2 << "(O.)In CalcSurcharge surcharge = " << surcharge.toFloat64() << ")";
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s2.str());
    */
    if( isMedicine )
    {
        if( surcharge > maxSurcharge )
        {
            surcharge = maxSurcharge;
            surcharge.trunc( 2 );
            /*
            std::stringstream s3;
            s3 << "(P.)In CalcSurcharge isMedicine is TRUE and if surcharge > maxSurcharge, surcharge = " << surcharge.toFloat64() << ")";
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s3.str());
            */
        }
    }

    if( isVatRegistered )
    {
        surcharge = surcharge + ( surcharge * vat );
        surcharge.trunc( 2 );
        /*
        std::stringstream s4;
        s4 << "(Q.)In CalcSurcharge surcharge with VAT = " << surcharge.toFloat64() << ")";
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s4.str());
        */
    }
    /*
    std::stringstream s5;
    s5 << "(R.)In CalcSurcharge SURCHARGE returned is  = " << surcharge.toFloat64() << ")";
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s5.str());
    */
    return surcharge;
}

bool isMedicine(
    const short priceGroup
        )
{
    return ( priceGroup >= 1 && priceGroup <= 3 );
}

} // end namespace calcavp
