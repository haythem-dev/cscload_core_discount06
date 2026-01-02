/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Internal order item posting methods for a stocked product.

REVISION HISTORY

13 December 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxartbas.hpp"
#include "pxorder.hpp"
#include "pxsess.hpp"
#include "pxstktra.hpp"
#include "types/origintypeenum.inc"
#include "pxstockbooking.hpp"

/*----------------------------------------------------------------------------*/
/*  Post quantities on order item entry.                                      */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CalculateContainer
(
    pxOrderItem* src                    // container item
)
{
    const pxStockTrans&   srcst = Order().StockTrans();
    long ContainerSize  = src->ArtBase()->ContainerGroesse();
    long countContainer = src->MengeAbgebucht()/ContainerSize;
    long MengeNatra     = src->MengeNatra();
    long RestMengeNatra = 0;
    if ( srcst.IsNoTransaction() )
        countContainer =  src->MengeBestaetigt()/ContainerSize;
    long MengeBestellt = src->MengeBestellt();
    long MengeContainer = countContainer*ContainerSize;
    long MengeRest = 0;

    if ( countContainer > 0 )
    {
       MengeRest = MengeAbgebucht_ - MengeContainer;
       if ( srcst.IsNoTransaction() )
           MengeRest = MengeBestaetigt_ - MengeContainer;
       // first reduce containerposition depend on countContainer
       if ( MengeRest > 0 )
       {
          src->MengeBestellt(MengeRest);

       }
       if ( srcst.IsNoTransaction() )
       {
          src->MengeAbgebucht(0L);
          MengeAbgebucht_ = 0;
       }
       else
       {
            src->MengeAbgebucht(MengeRest);
            MengeAbgebucht_   = MengeContainer;
            Session()->getStockBooking()->CancelReservationForOpenOrder(*src, MengeContainer);
            Session()->getStockBooking()->AddReservationForOpenOrder(*this, MengeContainer);
       }
       src->MengeBestaetigt(MengeRest);
       src->MengeGeliefert(MengeRest);
       // now correct the amountfields new position and
       // clear containerbit and mulibeipack bit
       MengeBestellt_    = MengeContainer+src->MengeVerbund();
       MengeBestaetigt_  = MengeContainer+src->MengeVerbund();
       MengeGeliefert_   = MengeContainer;
       src->ClearContainerPack();
       src->ClearBeiPackMulti();

       // devide src-MengeNatra
       if ( MengeNatra > MengeContainer )
       {
          RestMengeNatra = MengeNatra - MengeContainer;
          MengeNatra_ = MengeContainer;
          if ( MengeNatraGrossH_ > 0 )
          {
             MengeNatraGrossH_ = MengeContainer;
          }
          else
          {
             MengeNatraHerst_ = MengeContainer;
          }

          src->MengeNatra(RestMengeNatra);
          if ( src->MengeNatraGrossH() > 0 )
          {
             src->MengeNatraGrossH(RestMengeNatra);
          }
          else
          {
             src->MengeNatraHerst(RestMengeNatra);
          }
       }
       else
       {
          MengeNatra_ = MengeNatra;
          if ( MengeNatraGrossH_ > 0 )
          {
             MengeNatraGrossH_ = MengeNatra;
          }
          else
          {
             MengeNatraHerst_ = MengeNatra;
          }

          src->MengeNatra(0);
          src->MengeNatraGrossH(0);
          src->MengeNatraHerst(0);
       }

       if (MengeBestellt == 0 )         // Just Rebate Position (present)
       {
          MengeBestellt_ = 0;
          MengeBestaetigt_ = 0;
          src->MengeBestellt(0);
          src->MengeBestaetigt(0);
       }
       else
       {
          MengeBestellt_    = MengeBestellt_ - MengeNatra_;
          MengeBestaetigt_  = MengeBestaetigt_ - MengeNatra_;
          src->MengeBestellt( src->MengeBestellt() - src->MengeNatra());
          src->MengeBestaetigt( src->MengeBestaetigt() - src->MengeNatra());
       }
       if ( !Order().BatchSchreiben() == cORTYPE_AUXILIARY )
           return 0;
       //IBTDeliveryItem(src);
       if ( !IsGoodState() )
       {
          ClearError();
       }
    }
    return 0;
}
