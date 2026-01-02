#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxoclpar.hpp"
#include "pxeventreason.hpp"
#include "pxordercriteria.hpp"
#include "pxbase/pxconstants.hpp"
#include <logger/loggerpool.h>
/*----------------------------------------------------------------------------*/
/*  BookAddOnChargeArticleNoDependOnCodeBlocage.                              */
/*  This methode looks for an entry within table ordercriteria, depend on     */
/*  OrderType and LimitAction "04" (LIMITACTION_CALCADDONCHARGEARTNO)         */
/*  Upon order entry close, we check OrderValue depend on code blocage and    */
/*  compare this value against minordervalue of ordercriteria entry(if found) */
/*  If OrderValue_ less then minordervalue, addonchargeartno will be booked   */
/*  automatically to this order, otherwise no action.                         */
/*----------------------------------------------------------------------------*/
int
pxOrder :: BookAddOnChargeArticleNoDependOnCodeBlocage()
{
    long  orderq = 1;                   // current order quantity
    pxOrderItem* item;
    pxOrderCriteriaList* oCrList  = NULL;
    pxOrderCriteria*     oCrEntry = NULL;
    nMoney minOrderValue;
    nMoney thisOrderValue;

    if ( WertAuftrag() >  pxConstants::mZero && WertLieferung() > pxConstants::mZero )
    {
    	// this addon charge article must be excluded for OCP orders
    	// as they have their own dynamic addon charge
        if (!IsOCPOrder())
        {
            oCrList = new  pxOrderCriteriaList(Session());
            oCrList->SelectAddOnChargeArtNo(Customer()->Vertriebszentrum(), IDFNr_, KdAuftragArt(), LIMITACTION_CALCADDONCHARGEARTNO);
            if (oCrList->Entries() == NULL)
            {
                delete oCrList;
                return ErrorState();
            }
            oCrEntry = oCrList->Find(IDFNr_);   // is there a special entry for customer with pharmacgroupid ?
            if (oCrEntry == NULL)
            {
                oCrEntry = (pxOrderCriteria*)oCrList->At(0);
            }
            if (oCrEntry->AddOnChargeArtNo() == 0)
            {
                delete oCrList;
                return ErrorState();
            }
            thisOrderValue = calculateOrderValueForAddOnChargeArticle();
            minOrderValue = oCrEntry->MinOrderValue();
            if (thisOrderValue < minOrderValue)
            {
                std::stringstream ovalue;
                ovalue.str(std::string());
                ovalue << "Booking addoncharge as thisOrderValue = " << thisOrderValue << " less then minOrderValue = " << minOrderValue;
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), ovalue.str());

                // now book additional addoncharge article
                item = NewOrderItem_03_DefaultWithAutoItemAndIgnLack(oCrEntry->AddOnChargeArtNo(), orderq);
                Error() = item->Error();
            }
            else
            {
                std::stringstream s;
                s << "Not adding addoncharge as thisOrderValue = " << thisOrderValue << " greater then minOrderValue = " << minOrderValue;
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s.str());
            }

            delete oCrList;
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  calculateOrderValueForAddOnChargeArticle.                                 */
/*  at the moment just codeblocage 0 and 1 are affected                       */
/*----------------------------------------------------------------------------*/
nMoney pxOrder :: calculateOrderValueForAddOnChargeArticle()
{
    nMoney orderValue;
    orderValue = calculateOrderValueDependOnCodeBlocage('0') + calculateOrderValueDependOnCodeBlocage('1') +
        calculateOrderValueDependOnCodeBlocage('9') + calculateOrderValueDependOnCodeBlocage('S');
    return orderValue;
}

/*----------------------------------------------------------------------------*/
/*  calculateOrderValueForAddOnChargeArticle.                                 */
/*----------------------------------------------------------------------------*/
nMoney pxOrder :: calculateOrderValueDependOnCodeBlocage(const char codeblocage)
{
    nMoney orderValue(0.00);
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem* item;
    while ( ((item = (pxOrderItem*) ++it) != NULL) && IsGoodState() )
    {
        if ( item->IsProductStocked() && !item->IsCancelled() && item->ArtBase() )
        {
            if ( item->ArtBase()->CodeBlocage() != codeblocage )
            {
                std::stringstream s1;
                s1 << "For Article = " << item->ArtBase()->ArtikelNr() <<" codeblockage = " << item->ArtBase()->CodeBlocage() << " passed in codeblockage = " << codeblocage;
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s1.str());
                continue;
            }
            else
            {
                std::stringstream s2;
                s2 << "calculating OV For Article = " << item->ArtBase()->ArtikelNr() <<" with codeblockage = " << item->ArtBase()->CodeBlocage() << " passed in codeblockage = " << codeblocage;
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s2.str());
            }

            if ((double)item->InvoiceValue() == (0.00))
            {
                orderValue = orderValue + (item->MengeBestellt() * (double)item->PreisEKApo());

                std::stringstream s8;
                s8 << "invoicevalue is 0 so using preisekapo for calulating the orderValue =" << orderValue << " with Menge Bestellt = " << item->MengeBestellt() << " multiplied by PreisEKApo = " << (double)item->PreisEKApo();
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s8.str());
            }
            else
            {
                if (item->MengeBestaetigt() < item->MengeBestellt())
                {
                    orderValue = orderValue + (item->MengeBestellt() * (double)item->InvoiceValue() );
                    std::stringstream s4;
                    s4 << "OV is = " << orderValue << " For Article = " << item->ArtBase()->ArtikelNr() << " with codeblockage = " << item->ArtBase()->CodeBlocage() << " MengeBestellt = " << item->MengeBestellt() << " and InvoiceValue = " << (double)item->InvoiceValue();
                    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s4.str());
                }
                else
                {
                    //orderValue = orderValue + (item->MengeBestellt() * (double)item->InvoiceValue() );
                    orderValue = orderValue + (item->MengeBestaetigt() * (double)item->InvoiceValue() );
                    std::stringstream s3;
                    s3 << "OV is = " << orderValue << " For Article = " << item->ArtBase()->ArtikelNr() <<" with codeblockage = " << item->ArtBase()->CodeBlocage() << " MengeBestaetigt = " << item->MengeBestaetigt() << " and InvoiceValue = " << (double)item->InvoiceValue();
                    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s3.str());
                }
            }
        }
    }
    return orderValue;
}
