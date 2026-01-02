#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxholiday.hpp"
#include "pxoeparm.hpp"
#include <logger/loggerpool.h>

/*----------------------------------------------------------------------------*/
/* DelayedDelivery:                                                           */
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
Order::States
pxOrder :: SeparateDelayedDelivery
(
   const long date,
         int  &coolerq,
         int  &opiateq,
         int  &zytosq
)

{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxOrder :: SeparateDelayedDelivery");
    // unused variable
    // int  retval = 0;
    nDate today;
    pxOrder* delorder        = NULL;         // delayed deliver order
    pxCustBase* customer = Customer();

    // unused variable
    /* pxCustDelDelivery* custddel = */ Customer()->getDelayedDelivery(today, getWithTransportExclusion());
    Order::States State = Order::LeaveAsIs;


    if ( IsPseudoLock() )                     // Do not Splitt if PreudoLock
    {
       return State;                   // INC-031782 INC-032063
    }

    if ( TourId().IsEmpty() )
       return State;

    if ( coolerq == 0 && opiateq == 0 )      // nothing to do
    {
       return State;
    }

    if ( IsDoNotSplittOrder() || this->getNoDelayedDelivery() )
    {
       return State;
    }
/*----------------------------------------------------------------------------*/
/* Do not delaydelivery for Versandapo with BA order                          */
/*----------------------------------------------------------------------------*/
    if ( customer->Flags().IsVersandApo() && customer->Flags().IsBaAuftrag() )
    {
       return State;
    }

    nString tourid = TourId();
    if ( Customer()->IsDelayedDelivery( tourid, getWithTransportExclusion() ) )  // check customers specifications
    {
       if ( CountNoSplittPositions() == 0 )            // maybe just a BTM or Cooler order
       {
          if ( coolerq > 0 && opiateq == 0 )
          {
             if ( CountCoolerSplitt() == coolerq )   // then do not splitt this order, but do delayed delivery
             {
                ProcessOrderDelayedDelivery(date);
                coolerq = 0;
                opiateq = 0;
                zytosq  = 0;
                KdAuftragNrOrg(KdAuftragNr_);
                State = Order::EntryDeferred;
                return State;
             }
          }
          if ( opiateq > 0 && coolerq == 0 )
          {
             if ( !IsOpiateSplitt() )
             {
                return State;
             }
             else
             {
                ProcessOrderDelayedDelivery(date);
                coolerq = 0;
                opiateq = 0;
                KdAuftragNrOrg(KdAuftragNr_);
                State = Order::EntryDeferred;
                return State;
             }
          }
          if ( opiateq > 0 && coolerq > 0 )
          {
             if ( (CountCoolerSplitt() == coolerq)  && IsOpiateSplitt() )
             {
                ProcessOrderDelayedDelivery(date);
                coolerq = 0;
                opiateq = 0;
                KdAuftragNrOrg(KdAuftragNr_);
                State = Order::EntryDeferred;
                return State;
             }
             delorder = DDProcessing( date, &coolerq, &opiateq, &zytosq);
             if (delorder)
             {
                delorder->checkKdAuftragDebtlimtEntry(KdAuftragNr_);
                delorder->CloseState(Order::EntryDeferred);        // set order state flags
                delorder->CloseOrder();
                if ( delorder->IsGoodState() )
                {
                   delete delorder;
                   delorder = NULL;
                }
             }
             return State;
          }

       }

       delorder = DDProcessing( date, &coolerq, &opiateq, &zytosq);
       if (delorder)
       {
          delorder->checkKdAuftragDebtlimtEntry(KdAuftragNr_);
          delorder->CloseState(Order::EntryDeferred);        // set order state flags
          delorder->CloseOrder();
          if ( delorder->IsGoodState() )
          {
              delete delorder;
              delorder = NULL;
          }
       }
    }

    return State;
}
