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
#include "pxcstot.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxholiday.hpp"
#include "pxtxtdoc.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* DDProcessing:                                                              */
/* The current Order(*this) will be scanned for delayed deliverable article.  */
/* Prerequisites for delayed delivery depends on entries in the following     */
/* table:                                                                     */
/*         tDELAYEDDELIVERYCST = customers specifications                     */
/* The purpose of this methode is, to splitt the article specified by         */
/* tDELAYEDDELIVERYCST into a separate order. This order will be delivered    */
/* on the next workday specified within tDELAYEDDELIVERYCST.                  */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrder ::  DDProcessing
(
   const    long   date,
             int  *coolerq,
             int  *opiateq,
             int  *zytosq
)
{
    nDate today;
    pxOrder* delorder        = NULL;         // delayed deliver order
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    pxOrderItem *delitem;
    pxCustBase* customer = Customer();

    pxCustDelDelivery* custddel = Customer()->getDelayedDelivery(today, getWithTransportExclusion());
    pxHoliDayList*  holidaylist = Session()->HoliDayList( Customer()->Vertriebszentrum());
    bool bSameDelWeekDayAsToDay = false;

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if ((item->ArtBase()->ArtClass().IsOpiat()       && custddel->IsNarCotic())  ||
           (item->ArtBase()->ArtFlags().IsKuehlKette()  && custddel->IsColdChain()) ||
           (item->ArtBase()->ArtFlags().IsGekuehlt08()  && custddel->IsCool08())    ||
           (item->ArtBase()->ArtFlags().IsGekuehlt20()  && custddel->IsCool20()))
       {
          if (item->MengeGeliefert() > 0 && !item->IsAuxPosted() )
          {
             if ( delorder == NULL )
             {
                delorder = new pxOrder(Session(),*customer);
                if ( !delorder->IsGoodState() )
                {
                   delete delorder;
                   delorder = NULL;
                   break;
                }
                delorder->OrderType(KdAuftragArt_,KoArt_,BuchArt_);
                delorder->KdAuftragNrOrg(KdAuftragNr_);
                delorder->DatumOrg(today);
                delorder->BatchSchreiben(BatchSchreiben_);

                if ( date == NULL)
                {
                    delorder->DatumAuslieferung(CalcDeliveryDate((long)custddel->DelayedWeekDay()));
                }
                else
                {
                    delorder->DatumAuslieferung( nDate(date));
                }
                delorder->SetRouteForOrderSeparation( custddel->TourId(), delorder->DatumAuslieferung() );
                delorder->DafueAuftragNr((long) cDCTSequenceNumDDELMax);
                delorder->SetVerzoegerAusgeliefert();
                if ( DatumValuta_ != pxConstants::NullDate )
                {
                   delorder->SetDatumValuta(DatumValuta_);
                }
                // Look for Headtext
                HeadText();
                if (HeadText_)
                {
                   pxTextDocIter headiter  = pxTextDocIter(*HeadText_);
                   if (HeadText_->Entries() > 0)
                   {
                      pxTextDoc *headp = delorder->HeadText();
                      while ( (HeadText_ = (pxTextDoc *) ++headiter) != NULL )
                      {
                         //nString headline = ((pxTextLine*) headtext->First())->Text();
                         nString headline = ((pxTextLine*) HeadText_)->Text();
                         headp->NewLine(headline);
                      }
                   }
                }
                // Look for Tailtext
                TailText();
                if (TailText_)
                {
                   pxTextDocIter tailiter = pxTextDocIter(*TailText_);
                   if (TailText_->Entries() > 0)
                   {
                      pxTextDoc *tailp = delorder->TailText();
                      while ( (TailText_ = (pxTextDoc *) ++tailiter) != NULL )
                      {
                         //nString headline = ((pxTextLine*) headtext->First())->Text();
                         nString tailline = ((pxTextLine*) TailText_)->Text();
                         tailp->NewLine(tailline);
                      }
                   }
                }
                delorder->CheckDeliveryDate();
/*----------------------------------------------------------------------------*/
/*  Check for an holiday. If DatumAuslieferung is an holiday, do the next     */
/*  - look for an entry within the DelayedDeliveryCst Table for the day       */
/*  - of DatumAuslieferung                                                    */
/*  - if there is an entry, so take this one to calutate the next workday     */
/*----------------------------------------------------------------------------*/
                pxCustDelDelivery* ddel = NULL;
                for (;;)
                {
                   if ( holidaylist->CheckDateForHoliday(delorder->DatumAuslieferung(),
                                                      Customer()->FilialNr()))
                   {
                      ddel = Customer()->getDelayedDelivery(delorder->DatumAuslieferung(), getWithTransportExclusion());  // get entry for holiday
                      // SR-15013688 check for endless loop
                      if (  today.GetDayOfWeek() == (delorder->DatumAuslieferung()).GetDayOfWeek() )
                      {
                         bSameDelWeekDayAsToDay = true;
                      }
                      // SR-15013688  end check for endless loop

                      if ( ddel != NULL  && !bSameDelWeekDayAsToDay )
                      {
                            delorder->DatumAuslieferung(CalcDeliveryDate((long)ddel->DelayedWeekDay()));
                            delorder->SetRouteForOrderSeparation( ddel->TourId(), delorder->DatumAuslieferung() );
                            continue;
                      }
                      else
                      {
                         long  deliveryday = holidaylist->CalculateNextWorkDay(
                                              delorder->DatumAuslieferung(),Customer()->FilialNr() );
                         delorder->DatumAuslieferung(nDate(deliveryday));
                         delorder->RouteAssignDayType(delorder->DatumAuslieferung());
                         break;
                      }
                   }
                   break;
                }
                if (  ddel )
                {
                   delorder->CheckDeliveryDate();
                }
                custddel = Customer()->getDelayedDelivery(today, getWithTransportExclusion());

             }

             delitem = delorder->CopyOrderItem(item, pxOrderItem::DelayedDelivery, SplittType_Unknown);
             delitem->UndoRedoItemDiscount(item);
             // now delete item members
             item->MengeBestaetigt( 0L);
             item->MengeGeliefert( 0L);
             item->MengeAbgebucht( 0L);
             item->MengeNatra( 0L);
             item->SetDelayedDelivered();
             // get canned message.
             long tag   = delorder->DatumAuslieferung().GetDay();
             long month = delorder->DatumAuslieferung().GetMonth();
             long year  = delorder->DatumAuslieferung().GetYear();

             nString  datedel;
             sprintf((char*) datedel,"%02ld.%02ld.%04ld", tag,month,year);

             nMessage msg(CMsgStream(), CMSG_ITM_DELAYEDDELIVERY, (char*)&datedel);
             nString posbem = msg.String();
             posbem.Compress('\n');
             item->Bemerkungen(posbem);

             // 2013-08-12 reduce amount of narcotic lines in original order
             if ( item->ArtBase()->ArtClass().IsOpiat() )
             {
                --AnzBTM_;
                if( AnzBTM_ < 0 )
                {
                    AnzBTM_ = 0;
                }
             }

             if ( item->ArtBase()->ArtClass().IsOpiat() && Param()->IsNarcTransfer() )
             {
                if ( *opiateq > 1 )
                {
                   --*opiateq;
                }
                else
                {
                   *opiateq = 0;
                }
             }
             if (item->ArtBase()->ArtFlags().IsKuehlKette() || item->ArtBase()->ArtFlags().IsGekuehlt08() ||
                 item->ArtBase()->ArtFlags().IsGekuehlt20() )
             {
                if ( item->ArtBase()->ArtFlags().IsZytoStatikaArtikel() )
                {
                   if ( *zytosq > 1 )
                   {
                      --*zytosq;
                   }
                   else
                   {
                      *zytosq = 0;
                   }
                }
                if ( *coolerq > 1 )
                {
                   --*coolerq;
                }
                else
                {
                   *coolerq = 0;
                }
             }
          }
       }
    }
    if (NULL != delorder)
    {
        delorder->RouteAssign();
    }
    return delorder;
}
/*----------------------------------------------------------------------------*/
/* CheckDeliveryDate: if delevery day (DatumAuslieferung) Saturday            */
/* so look for a delayeddeliverycst entry for tha day                         */
/* If the member time < TourId_(4 digits) so change the deliveryday to        */
/* the entry's weekday and replace the TourId with emtry's TourId_            */
/*----------------------------------------------------------------------------*/
int pxOrder::CheckDeliveryDate()
{
    pxCustDelDelivery* custdel = NULL;
    long  delday = DatumAuslieferung().GetDayOfWeek();
    long tour = atol((char*)(nString)(TourId())(0,4));
    nClock ctour(tour * 100);

    pxHoliDayList*  holidaylist = Session()->HoliDayList( Customer()->Vertriebszentrum());
    if ( delday == 6 )
    {
        custdel = Customer()->getDelayedDelivery(DatumAuslieferung(), getWithTransportExclusion() );
        if ( custdel != NULL )
        {
            if ( custdel->Time() < ctour )   // could not be delivered on Saturday
            {
                DatumAuslieferung(CalcDeliveryDate((long)custdel->DelayedWeekDay()));
                long  deliveryday = holidaylist->CalculateNextWorkDay((DatumAuslieferung()-1) ,Customer()->FilialNr() );
                DatumAuslieferung(nDate(deliveryday));
                RouteAssignDayType(DatumAuslieferung());
            }
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* ProcessOrderDelayedDelivery()                                              */
/* The current Order(*this) will be set to delayed delivery under respect of  */
/* table:                                                                     */
/*         tDELAYEDDELIVERYCST = customers specifications                     */
/* Take care for a well constructed pxOrder object to prevent unpredictable   */
/* results                                                                    */
/*----------------------------------------------------------------------------*/
int
pxOrder ::  ProcessOrderDelayedDelivery
(
   const    long   date

)
{
    nDate today;
    pxCustDelDelivery* custddel = Customer()->getDelayedDelivery(today,getWithTransportExclusion());
    pxHoliDayList*  holidaylist = Session()->HoliDayList( Customer()->Vertriebszentrum());
    pxOrderItemListIter it(*ItemList());
    bool bSameDelWeekDayAsToDay = false;
    if ( date == NULL)
    {
       DatumAuslieferung(CalcDeliveryDate((long)custddel->DelayedWeekDay()));
    }
    else
    {
       DatumAuslieferung( nDate(date));
    }

    SetRouteForOrderSeparation( custddel->TourId(), this->DatumAuslieferung() );
    DafueAuftragNr((long) cDCTSequenceNumDDELMax);
    SetVerzoegerAusgeliefert();
    CheckDeliveryDate();
/*----------------------------------------------------------------------------*/
/*  Check for an holiday. If DatumAuslieferung is an holiday, do the next     */
/*  - look for an entry within the DelayedDeliveryCst Table for the day       */
/*  - of DatumAuslieferung                                                    */
/*  - if there is an entry, so take this one to calutate the next workday     */
/*----------------------------------------------------------------------------*/
    pxCustDelDelivery* ddel = NULL;
    for (;;)
    {
       if ( holidaylist->CheckDateForHoliday(DatumAuslieferung(), Customer()->FilialNr()))
       {
          ddel = Customer()->getDelayedDelivery(DatumAuslieferung(), getWithTransportExclusion());  // get entry for holiday
          // SR-15013688 check for endless loop
          if (  today.GetDayOfWeek() == DatumAuslieferung().GetDayOfWeek() )
          {
             bSameDelWeekDayAsToDay = true;
          }
          // SR-15013688  end check for endless loop

          if ( ddel != NULL  && !bSameDelWeekDayAsToDay )
          {
                DatumAuslieferung(CalcDeliveryDate((long)ddel->DelayedWeekDay()));
                SetRouteForOrderSeparation( ddel->TourId(), DatumAuslieferung() );
                continue;
          }
          else
          {
             long  deliveryday = holidaylist->CalculateNextWorkDay(
                                  DatumAuslieferung(),Customer()->FilialNr() );
             DatumAuslieferung(nDate(deliveryday));
             RouteAssignDayType(DatumAuslieferung());
            // SetProblemClearance();
             break;
          }
       }
       break;
    }
    if (  ddel )
    {
       CheckDeliveryDate();
    }

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* IsCoolerSplitt():                                                          */
/*----------------------------------------------------------------------------*/
int
pxOrder ::  CountCoolerSplitt
(
)
{

    nDate today;
    // unused variable
    /* pxCustBase* customer = */ Customer();

    pxCustDelDelivery* custddel = Customer()->getDelayedDelivery(today,getWithTransportExclusion());
    // unused variable
    /* pxHoliDayList*  holidaylist = */ Session()->HoliDayList( Customer()->Vertriebszentrum());
    // unused variable
    /* pxOrderEntryParam &param   = */ Param();
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    int   countcooler = 0;

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;

       if ((item->ArtBase()->ArtFlags().IsKuehlKette()  && custddel->IsColdChain()) ||
           (item->ArtBase()->ArtFlags().IsGekuehlt08()  && custddel->IsCool08())    ||
           (item->ArtBase()->ArtFlags().IsGekuehlt20()  && custddel->IsCool20()))
       {
          ++countcooler;
       }
    }

    return countcooler;
}
/*----------------------------------------------------------------------------*/
/* IsCoolerSplitt():                                                          */
/*----------------------------------------------------------------------------*/
bool
pxOrder :: IsOpiateSplitt
(
)
{
    nDate today;
    // unused variable
    /* pxCustBase* customer = */ Customer();
    pxCustDelDelivery* custddel = Customer()->getDelayedDelivery(today,  getWithTransportExclusion());
    // unused variable
    /* pxHoliDayList*  holidaylist = */ Session()->HoliDayList( Customer()->Vertriebszentrum());
    // unused variable
    /* pxOrderEntryParam &param   = */ Param();
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    bool retval = false;

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;

       if ((item->ArtBase()->ArtClass().IsOpiat()       && custddel->IsNarCotic()) )
       {
          retval = true;
       }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/* CountNoSplittPositions()                                                   */
/*----------------------------------------------------------------------------*/
int pxOrder ::  CountNoSplittPositions()
{
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    int   count = 0;

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;

       if (!(item->ArtBase()->ArtFlags().IsKuehlKette()) && !(item->ArtBase()->ArtFlags().IsGekuehlt08()) &&
           !(item->ArtBase()->ArtFlags().IsGekuehlt20()) &&  !(item->ArtBase()->ArtClass().IsOpiat()) )
       {
          ++count;
       }
    }

    return count;
}
