/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Class pxOrderItem:
UNIPHARM/PHARMOS compatibility.

REVISION HISTORY

02 May 1996 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#include "pxitem.hpp"
#include <pxrecord.h>
#include "pxsess.hpp"
#include "pxcstbas.hpp"
//#include "pxcsttmg.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"

/*----------------------------------------------------------------------------*/
/*  Set values used by old PHARMOS modules.                                   */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: ToPharmos()
{
    if ( ( (GeraetTyp() == pxDVC_DCT_SERIAL   ||
            GeraetTyp() == pxDVC_DCT_PARALLEL ||
            GeraetTyp() == pxDVC_DCT) ) &&                                  // DC active
         (SubGeraetTyp() != static_cast<short>(DISPO)) )
    {
       SetDafue();
       if ( !(Order().IsDCParallel()) )
          ETPosSchalter_.SetBit(bSeriellUebertragen);
    }

    ClearUeberMenge();
    if ( IsQStateLimitCheck() )
       SetUeberMenge();

    if ( !(Session()->Device()->IsVideo()) )
    {
       if ( IsDisponieren() )               //Customer sends Purchase
          SetCustPurchase();
       if ( IsNachliefern() )                //Customer sends Restdelivery
          SetCustRestDelivery();
    }

    if ( ArtBase() && ArtBase()->IsGoodState() )                          // just if pxArtBase object is available
    {
       if ( ArtBase_->ArtFlags().IsNeuerPreisAktiv() )
          SetNeuerPreisKsc();
    }
}
/*----------------------------------------------------------------------------*/
/*  Set additional values in the record structure used by old PHARMOS modules.*/
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: ToPharmosRecord
(
    tKDAUFTRAGPOS&       record
)
{

    if ( ArtBase() && ArtBase()->IsGoodState() )                       // just if pxArtBase object is available
    {
       record.LagerBereichNr  = ArtBase_->LagerBereichNr();
       record.LagerFachNr[0]  = ' ';
       ArtBase_->LagerFachNr().GetData (record.LagerFachNr );
       record.StationNr[0]  = ' ';
       ArtBase_->StationNr().GetData (record.StationNr );
    }
}

/*----------------------------------------------------------------------------*/
/*  Set values used by old PHARMOS modules.                                   */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: ToPharmosBatch
(
    bool Abverkaufserhoehung
)
{
       SetDafue();
       SetVerbundAuftragsPosition();

       if (Abverkaufserhoehung)
       {
           SetAbverkaufsErhoehung();
       }
}

/*----------------------------------------------------------------------------*/
/*  Set manualmaintenance on dispoitems and DCT-Parallel items                */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: ManualMaintenance
(
)
{
    const pxStockTrans&     st = Order().StockTrans();
    if ( !(Session()->Device()->IsVideo()) )  // DC active
    {
       if ( (Order().IsDCParallel() && IsQStateNotOnHand())  ||
          ( IsDispoItem()  && st.IsDebit()) )
           ETPosSchalter_.SetBit(bManualMaintenance);
    }

}
/*----------------------------------------------------------------------------*/
/*   Set InfoBit depend PurchaseOrder or Restdelivery                         */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: PharmosDispoItem
(
)
{
    if ( !(Session()->Device()->IsVideo()) && IsDispoItem() &&
          (IsDisponieren() || IsNachliefern()) )  // DC active
    {
       if (IsDisponieren() )
          SetCustPurchase();
       if (IsNachliefern() )
          SetCustRestDelivery();
       PostType(BookingTypeDefault);
    }

}

/*----------------------------------------------------------------------------*/
/* ToPharmosHMKText: A special methode for the Austrian Data Communication    */
/* System. It handles incoming Textrecords depend on texttyp                  */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: ToPharmosHMKText()
{
    ToPharmos();
    ETPosSchalter_.SetBit(bTextAuftragsKopf);
    ETPosSchalter_.SetBit(bTextOhneWert);
    ETPosSchalter_.SetBit(bArtikelUmgeschluesselt);
    SetDirty();
}
