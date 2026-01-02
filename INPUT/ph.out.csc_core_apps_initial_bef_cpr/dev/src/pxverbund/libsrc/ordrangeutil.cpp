#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"

#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxrangemember.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxrangecontrol.hpp"
#include "pxartcompack.hpp"
#include "pxcpvalidityperiod.hpp"
#include <logger/loggerpool.h>
#include <sstream>

/*----------------------------------------------------------------------------*/
/*  Book FreeArticle Position or a Package of Positions                       */
/*----------------------------------------------------------------------------*/
int
pxOrder :: RangeDiscountArticle
(
    const long  ArticleNo,
    const long  Qty,
    const short DiscountSpec,
	const bool internalDiscountFlag,
	const tDiscountCategory category,
	const nString& pharmacyGroup
)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrder(), "pxOrder::RangeDiscountArticle()" );

    pxOrderItem *newitem  = NULL;
    pxOrderItem *item     = NULL;

    pxArtComPackList        *acpl   = NULL;
    pxArtComPack        *acpentry   = NULL;
    pxCPValidityPeriodList *cpvpl   = NULL;
    pxCPValidityPeriod  *cpventry   = NULL;
    PriceTypeEnum PriceType = FREESALE_PRICE;

    if ( ArticleNo == 0 || Qty == 0 )
    {
        BLOG_TRACE( libcsc::LoggerPool::getLoggerOrder(), "ArticleNo == 0 || Qty == 0" );
       return ErrorState();
    }

	item = ItemList_->getItemInhibitManualUpdateByArticleNo(ArticleNo);
	if ( item )
	{
		if (!Param()->UseNewDiscountCalc())
		{
			return ErrorState();
		}
	}

    if ( DiscountSpec ==  DiscSpec_HealthFund )
       PriceType = HEALTHFUND_PRICE;

    if ( AnzPos_ == CountPriceTypeItems(HEALTHFUND_PRICE ) )
        PriceType = HEALTHFUND_PRICE;

    // check DiscountArticle_, maybe it is a Steller Article. In that case
    // we must check the type be select the cpvalidityperiod entry
    cpvpl = new pxCPValidityPeriodList(Session());
    cpvpl->Select(ArticleNo);
    cpvpl->ReduceToValidEntries();
    if (cpvpl->Entries() == 0 )
    {
        delete cpvpl;
    }
    else
    {
        cpventry = (pxCPValidityPeriod*)( cpvpl->At(0)); // entry to be checked
    }

    if ( cpventry )
    {
        if ( cpventry->IsReplaceDiscArticle() )          // = 4 Rebate from the artcompack list
        {
            // now get the members belonging to this Pseudo article
            acpl = new pxArtComPackList(Session());
            acpl->Select( ArticleNo);
            if (acpl->Entries() == 0 )                   // nothing found
            {
                delete acpl;
                acpl = NULL;
                return ErrorState();
            }
        }
    }
    // now book the members belonging to  item->DiscountArticleNo()
    // till now it's a bulgarian speciality
    if ( acpl )
    {
        pxArtComPackListIter iter(*acpl);
        while ( (acpentry = (pxArtComPack*) ++iter) != NULL )
        {
            newitem = NewOrderItem_03_NatraWithRangeArticle(acpentry->ArticleNoElement(), (long)acpentry->Quantity(), PriceType);
            if ( newitem == NULL )
            {
                ClearError();                           // to prevent Error during booking
            }
            else
            if ( newitem->IsGoodState() )
            {
                newitem->SetSperreRabattManuell();      // mark position
                Error() = newitem->Error();
            }
        }
        delete acpl;
        delete cpvpl;
        return ErrorState();
    }

    newitem = NewOrderItem_03_NatraWithRangeArticle(ArticleNo, Qty, PriceType);

    if ( newitem == NULL )
    {
        ClearError();              // to prevent Error during booking
    }
    else
    {
        if ( newitem->IsGoodState() )
        {
            if( libcsc::LoggerPool::getLoggerOrder().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
            {
                std::stringstream ss;
                ss << "Rebate-in-kind article added: positionNo=<" << newitem->PosNr() << ">, articleNo=<" << newitem->ArtikelNr() << ">";
                libcsc::LoggerPool::getLoggerOrder().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
            }

            Error() = newitem->Error();
            newitem->SetSperreRabattManuell();         // mark position
			if (true == internalDiscountFlag)
			{
				newitem->SetNaturalRabattIntern();
			}
			newitem->SetNatraCategory(category);
			newitem->SetNatraPharmacyGroup(pharmacyGroup);
			newitem->SetDirty();
        }
    }

    return ErrorState();
}
