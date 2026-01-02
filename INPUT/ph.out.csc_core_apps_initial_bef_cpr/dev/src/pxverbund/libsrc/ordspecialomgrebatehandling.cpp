#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordervalues.hpp"
#include "pxordevt.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxoclpar.hpp"
#include "pxshuttlecustinfo.hpp"
#include "pxeventreason.hpp"
#include "cremamailhandler.h"
#include "pxstockbooking.hpp"
#include "pxtxtdoc.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"
#include <libbasarcmnutil_datetime.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_datetimetools.h>
#include <libbasarcmnutil_timespan.h>
#ifdef WIN32
#include <windows.h>
#endif
/*----------------------------------------------------------------------------*/
/* SpecialOmgRebateHandling                                                   */
/* This a special function for the Swiss order entry application.             */
/*----------------------------------------------------------------------------*/
int pxOrder::SpecialOmgRebateHandling()
{
    if ( Session()->isSwitzerland() )              // just forr save
    {
        pxOrderItemListIter it(*ItemList_);
        pxOrderItem *item;
        while ((item = (pxOrderItem*) ++it) != NULL)
        {
            if (item->IsCancelled())
            {
                continue;
            }
            int tenderNo = item->GetTenderNoFromRemark();
            if (0 == tenderNo)
            {
                continue;
            }
            long tenderBookedQty = item->GetBookedTenderQty(tenderNo);
            if (0 == tenderBookedQty)
            {
                // paranoia: this shouldn't happen
                continue;
            }
            if (tenderBookedQty == item->MengeBestaetigt())
            {
                continue;
            }
            int missingQty = item->MengeBestaetigt() - tenderBookedQty;
            if (0 > missingQty)
            {
                std::stringstream ss;
                ss << "pxOrder::Close: missingQty < 0! BranchNo=<" << FilialNr() << ">, OrderNo=<" << item->KdAuftragNr() << ">, PosNo=<" << item->PosNr() << ">";
                ss << ", item->MengeBestellt()=<" << item->MengeBestellt() << ">, item->MengeBestaetigt()=<" << item->MengeBestaetigt();
                ss << ">, item->MengeGeliefert()=<" << item->MengeGeliefert() << ">, item->MengeVerbund()=<" << item->MengeVerbund();
                ss << ">, item->MengeNachgeliefert()=<" << item->MengeNachgeliefert() << ">, item->MengeDisponiert()=<" << item->MengeDisponiert();
                ss << ">, tenderBookedQty=<" << tenderBookedQty << ">";
                BLOG_ERROR(libcsc::LoggerPool::getLoggerIbtRequest(), ss.str().c_str());
                continue;
            }

            // justify confirmed quantity to available tender quantity
            //item->OrderQuantity(tenderBookedQty);

            const int ibtqty = item->MengeVerbund();
            const short FirstPartnerNr = item->VerbundFilialNr();
            if (item->IsAuxPosted())
            {
                item->nDBBeginTransaction(cDBTransRecord);
                item->UndoAuxPosting();
                if (item->IsGoodState())
                {
                    item->nDBCommit(cDBTransRecord);
                }
                else
                {
                    item->nDBRollBack();
                    std::stringstream ss;
                    ss << "pxOrder::Close(): Error creating tender split item for OrderNo<" << KdAuftragNr() << ">, ArticleNo<" << item->ArtikelNr() << ">, PosNo<" << item->PosNr() << ">";
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), ss.str().c_str());
                }
            }
            if (item->IsGoodState())
            {
                if (FirstPartnerNr > 0)
                {
                    item->OrderQuantity(tenderBookedQty, 0, tenderBookedQty, pxOrderItem::AuxDelivery, bPOST_IGN_LACK, FirstPartnerNr);
                }
                else
                {
                    item->OrderQuantity(tenderBookedQty, 0, tenderBookedQty, pxOrderItem::BookingTypeDefault, bPOST_IGN_LACK);
                }
            }

            // split item to get discount from new tender
            pxOrderItem * newItem = NULL;
            if (ibtqty > 0 && FirstPartnerNr > 0)
            {
                newItem = NewOrderItem_08(item->ArtikelNr(), static_cast<long>(missingQty), FirstPartnerNr, 0, static_cast<long>(missingQty), item->PreisTyp(), pxOrderItem::AuxDelivery);
            }
            else
            {
                newItem = NewOrderItem_03_DefaultWithAutoItemAndIgnLack(item->ArtikelNr(), static_cast<long>(missingQty));
            }
            if (false == newItem->IsGoodState())
            {
                std::stringstream ss;
                ss << "pxOrder::Close(): Error creating tender split item for OrderNo<" << KdAuftragNr() << ">, ArticleNo<" << item->ArtikelNr() << ">, PosNo<" << item->PosNr() << ">";
                BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), ss.str().c_str());
            }
        }
    }
    return ErrorState();
}
