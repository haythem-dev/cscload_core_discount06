#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "pxoeparm.hpp"
#include "pxitemattributes.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"


using pxVerbund::subsequentDelivery::pxDeliveryPos;

/*----------------------------------------------------------------------------*/
/* This function inserts or manupulates pxDeliveryPos entries depend on       */
/* bookingtypes and auxiliary delivery for the distributors customerservice.  */
/*----------------------------------------------------------------------------*/
int pxOrderItem::AuxShipment()
{
    pxDeliveryPos            *dp  = NULL;                // auxdelivery pos
    pxDeliveryPos      *dpinlist  = NULL;                // auxdelivery pos
    pxCustBase         *customer  = Order().Customer();  // customer
    pxDevice           *device    = Session()->Device(); // device
    bool                update    = false;
    const pxCustOrderType&     ot = Order().OrderType();

    if ( !device->IsVideo() && IsMengenKontigentDefekt() )
    {
		ClearDisponieren();           // ignore purchase order
        ClearNachliefern();            // ignore restdelivery
        return ErrorState();
    }

/*----------------------------------------------------------------------------*/
/*  Auxiliary posted items                                                    */
/*----------------------------------------------------------------------------*/
    if ( IsAuxPosted() )                 // auxiliary booked item
    {
       if ( (customer->IsSpecialAuxDeliveryUser()) &&
            (!device->IsVideo()) &&  (IsDisponieren() || IsNachliefern()) )
       {
          if ( MengeBestaetigt_ >= MengeBestellt_ )
          {
             PostType(BookingTypeDefault);
          }
       }
    }

/*----------------------------------------------------------------------------*/
/*  Check purchaseorder for Branches depend on Table paraauftragbearb->       */
/*  Column DefektDispo  for non video devices                                 */
/*----------------------------------------------------------------------------*/
    if ( MengeBestaetigt_ < MengeBestellt_  &&  Order().Param()->IsDefektDispo() )
    {
       RestDeliveryService();
       if ( !IsGoodState() )
          return ErrorState();
    }

/*----------------------------------------------------------------------------*/
/*  Check Ordertype for Restdelivery allowance                                */
/*----------------------------------------------------------------------------*/
    if (IsNachliefern())
    {
		// CPR-170910 Nachlieferung verhindern wenn Artikel-WAFO-Typ = 0 (ART-NALI)
		if (Session()->isGermany())
		{
			if (!ArtBase()->IsRestDelivery() && false == Session()->Device()->IsVideo())
			{
				ClearNachliefern();            // ignore restdelivery
			}
		}

        if ( !ot.IsRestDel() )              // no Restdelivery allowance
        {
			ClearNachliefern();            // ignore restdelivery
            return CMSG_AD_OT_NO_RESTDEL_TYPE;
        }
    }
    if ( MengeBestaetigt_ < MengeBestellt_            &&
         !(ArtBase()->ArtFlags().IsArtikelGefuehrt()) &&
         !device->IsVideo() && !Order().Param()->IsDefektDispo() &&
         !(IsNachliefern() && Session()->IsSubDeviceTypeOf(DISPO)) ) // this rule is not allowed for DISPO-RestDel orders!
    {
        if (IsNachliefern())
        {
            // Implemenatation of ItemAttributes Class
            if (ItemAttributes())
            {
                if (!ItemAttributes()->IsPurchaseOrder())
                {
					ClearNachliefern();            // ignore restdelivery
                    PostType(BookingTypeDefault);
                }
                else
                {
                    PostType(PurchaseOrder);
                }
            }
            else
            {
                PostType(PurchaseOrder);
            }
        }
        else
        {
            // Implemenatation of ItemAttributes Class
            if (ItemAttributes())
            {
                if (ItemAttributes()->IsPurchaseOrder())
                {
                    PostType(PurchaseOrder);
                }
                else
                {
                    PostType(BookingTypeDefault);
                }
            }
        }
    }
/*----------------------------------------------------------------------------*/
/*  Build delivery item for purchaseorder and restdelivery                    */
/*----------------------------------------------------------------------------*/
    if ( MengeBestaetigt_ < MengeBestellt_ )
    {
       // Start maybe DI is set within ItemAttributes (INC-042412)
       if (!IsDisponieren() && !IsNachliefern() )
       {
          // Implemenatation of ItemAttributes Class
          if ( ItemAttributes() )
          {
             if ( ItemAttributes()->IsPurchaseOrder() )
             {
                PostType(PurchaseOrder);
             }
          }
       }
       // End maybe DI is set within ItemAttributes (INC-042412)

       if (ArtBase()->ArtClass().IsOpiat() || (Session()->isGermany() && ArtBase()->IsAktivAndOnStore() && false == Session()->Device()->IsVideo()))
       {
           ClearDisponieren();           // ignore purchase order
       }

       if (IsDisponieren())
       {
           if ( (Session()->isGermany() && ArtBase()->isDispositionExclusion() && false == Session()->Device()->IsVideo()) )
           {
               ClearDisponieren();           // ignore purchase order
               return CMSG_SDC_FEHLT_ZUR_ZEIT;
           }
       }

       if (IsDisponieren() )
       {
          //maybe change from restdelivery to purchase
          dpinlist = AuxDelList()->Find(KdAuftragNr_,
                     PosNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
          if ( (dp = AuxDelList()->Find(KdAuftragNr_,
                PosNr_, pxVerbund::subsequentDelivery::pxDPT_DISPOSAL_ITEM)) == NULL )
          {
             dp = NewDeliveryPos(pxVerbund::subsequentDelivery::pxDPT_DISPOSAL_ITEM );

             if ( dpinlist )
             {
                dpinlist->Delete();              // delete entry
                delete AuxDelList()->Remove(dpinlist);  // remove entry from list
             }
          }
          else
                update = true;
       }

       if (IsNachliefern())
       {
			// CPR-170910 Nachlieferung verhindern wenn Artikel-WAFO-Typ = 0 (ART-NALI)
			if (Session()->isGermany() && !ArtBase()->IsRestDelivery() && false == Session()->Device()->IsVideo())
			{
				ClearDisponieren();
				ClearNachliefern();
			}
			else
			{
				//maybe change from purchase  to restdelivery
				dpinlist = AuxDelList()->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_DISPOSAL_ITEM);

				if ((dp = AuxDelList()->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM)) == NULL)
				{
					dp = NewDeliveryPos(pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);

					if (dpinlist)
					{
						dpinlist->Delete();              // delete entry
						delete AuxDelList()->Remove(dpinlist);  // remove entry from list
					}
				}
				else
				{
					update = true;
				}
			}
       }
    }
    else
    {
        ClearDisponieren();           // ignore purchase order
		ClearNachliefern();            // ignore restdelivery
    }

/*----------------------------------------------------------------------------*/
/*  Insert or update delivery item                                            */
/*----------------------------------------------------------------------------*/

    if ( dp )
    {
       dp->UndoQuantityPosting();       // init delpos
       long Menge = (MengeBestellt_ + MengeNatra_) - (MengeBestaetigt_+ MengeNatra_);
       dp->AddQuantity( Menge);
       RestDelRedunancyCheck();

       CalcDiscount( MengeBestellt_);
	   // SR-16044865 krükke
	   // MengeNatra_ == 0 kommt aus der Methode PostOrderQuantity(itmstock.cpp)
	   // MengeNatraGrossH_ und MengeNatraHerst_ werden in CalcDiscount ermittelt andhand MengeBestellt_
	   if ( (MengeNatraGrossH_ > 0 || MengeNatraHerst_ > 0) && MengeNatra_ == 0 )
	   {
		   MengeNatraGrossH_ = MengeNatraHerst_=0;
	   }
       if (MengeGeliefert_  == 0 )
       {
          UndoItemDiscount();
       }

       if ( dp->IsRestDeliveryItem() )
       {
          if ( PreisEKApoNetto_ > pxConstants::mZero && (false == Session()->isGermany()) )
          {
             dp->SetPreisEKApoNetto(PreisEKApoNetto_);
          }
		  dp->SetMengeBestellt(MengeBestellt_);
		  dp->SetPreisTyp(PreisTyp_);
          if ( dp->KdAuftragArt() != "NO")
          {
             if (false == Session()->isGermany())
             {
                dp->SetPreisEKApo(PreisEKApo_);
                dp->SetPreisVKApo(PreisVKApo_);
                dp->SetPreisAGP(PreisAGP_);
             }
             if  ( Session()->Device()->IsVideo() && MengeBestaetigt_ == 0 && MengeGeliefert_ == 0 && MengeNatra_ > 0 )
             {
                dp->SetMengeNatra(MengeNatra_ );
                MengeNatra_ = MengeNatraGrossH_ = MengeNatraHerst_ = 0;
             }
             dp->SetBemerkungen(Bemerkungen_);
          }
	   }
	   dp->Put();                       // insert/update item
       if ( !update)
          AuxDelList()->Append( dp );   // append to list
       Error() = dp->Error();           // copy error object
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* GetBackDeliveryPos: tries to find a valid deliverypos entry depend on      */
/* this item state.                                                           */
/* Returns: NULLP or a valid deliverypos entry                                */
/*----------------------------------------------------------------------------*/
pxDeliveryPos*
pxOrderItem :: GetBackDeliveryPos
(
)
{
    //pxVerbund::subsequentDelivery::pxDeliveryPos* dpAuxDel   = NULL;

    if  ( Session()->Device()->IsVideo() )     //just for compiler on unix
    {
       // was position already booked before, then get corresponding entry
       //if ( IsAuxPosted() )
       //{
       //   dpAuxDel = AuxDelList()->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_AUXDELIVERY_ITEM);
       //}

       if (IsDisponieren())
       {
           pxVerbund::subsequentDelivery::pxDeliveryPos* dpPurchase = AuxDelList()->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_DISPOSAL_ITEM);
          if (dpPurchase)
          {
             dpPurchase->Delete();
             delete AuxDelList()->Remove(dpPurchase);  // remove entry from list
             dpPurchase = NULL;
          }
       }

       if (IsNachliefern())
       {
           pxVerbund::subsequentDelivery::pxDeliveryPos* dpRestDel = AuxDelList()->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
          if (dpRestDel)
          {
             dpRestDel->Delete();
             delete AuxDelList()->Remove(dpRestDel);  // remove entry from list
             dpRestDel = NULL;
          }
       }
    }
    //return dpAuxDel;
    return NULL;
}
