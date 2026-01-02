#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "pxparameter.hpp"
#include "types/messagecodeenum.inc"


bool pxOrderItem::IsRestDeliveryPossibleForArticle()
{
    bool retval = true;

    if (!ArtBase()->IsRestDelivery()) retval = false;
    if (!ArtBase()->ArtFlags().IsArtikelGefuehrt()) retval = false;
    if (ArtBase()->ArtFlags().IsAusserHandel()) retval = false;
    if (ArtBase()->ArtClass().IsOpiat()) retval = false;
    if (ArtBase()->ArtFlags().IsEinkaufsSperre()) retval = false;
    if (ArtBase()->ArtFlags().IsAuslaufArtikel()) retval = false;

    if (ArtBase()->ArtFlags().IsNichtLieferbarHersteller())
    {
        if (Order().Customer()->Flags().IsKeinNlNgh()) retval = false;
        if (Order().Customer()->Flags().IsKeinNlNghNgh()) retval = false;
    }

    if (ArtBase()->ArtFlags().IsNichtGeliefertHersteller())
    {
        if (Order().Customer()->Flags().IsKeinNlNghNgh()) retval = false;
    }

    if (Order().Customer()->IsNotRestDeliveryUser()) retval = false;

    if (IsMengenKontigentDefekt()) retval = false;

    return retval;
}

/*----------------------------------------------------------------------------*/
/* RestDeliveryService: Special function to check the capability for  an      */
/* Article to be booked into the restdeliverysystem (Swiss and Austria        */
/*----------------------------------------------------------------------------*/
int pxOrderItem::RestDeliveryService()
{
    pxCustBase         *customer  = Order().Customer();  // customer
    const pxArtFlags    &artflag  = ArtBase()->ArtFlags();
    const pxArtClass    &artclass = ArtBase()->ArtClass();
    pxDevice           *device    = Session()->Device(); // device
    pxCustomerFlags&   cflags     = customer->Flags();
    const pxCustOrderType&     ot = Order().OrderType();

    if ( !device->IsVideo() )
    {
       // articles on pseudo stocklocation
       if ( !artflag.IsArtikelGefuehrt() && !ArtBase()->IsRestDelivery())
       {
          SetDispoMoeglich();
          PostType(BookingTypeDefault);
          if ( artflag.IsAusserHandel() || IsAuxPosted() ||
               artflag.IsNichtGeliefertHersteller() ||
               artflag.IsNichtLieferbarHersteller() ||
               artflag.IsNichtUeberGrossHandel() )
          {
             ClearDispoMoeglich();           // ignore purchase order
          }
       }

       // CPR-170910 Nachlieferung verhindern wenn Artikel-WAFO-Typ = 0 (ART-NALI)
       if (Session()->isGermany())
       {
           if (!ArtBase_->IsRestDelivery())
           {
               ClearNachliefern();
               return ErrorState();
           }
       }

       if (IsNachliefern() && !IsDispoMoeglich())   // Customer sends NL
       {
          if ( IsAuxPostPossible() )                 // on AuxPostPossible -> no NL
          {
             ClearNachliefern();                    // ignore restdelivery
             return ErrorState();
          }
          if ( !ArtBase_->IsRestDelivery() )
          {
             ClearNachliefern();            // ignore restdelivery
             return ErrorState();
          }
          if ( ot.IsSAlwaysRestDel() )
          {
             return ErrorState();
          }

          if ( ot.IsRestDel() )              //  Restdelivery allowance
          {
             return ErrorState();
          }
       }

       if ( !IsDispoMoeglich() && !IsNachliefern())
       {
          if ( (MengeBestaetigt_ < MengeBestellt_) && !CheckRestDelivery()  )
          {
             if ( artflag.IsAusserHandel()    ||
                  artclass.IsOpiat()          ||
                  artflag.IsEinkaufsSperre()  ||
                  artflag.IsAuslaufArtikel())
             {
                return ErrorState();
             }

             // KeinNl = 1
             if ( cflags.IsKeinNlNgh() && artflag.IsNichtLieferbarHersteller())
             {
                return ErrorState();
             }
             // KeinNl = 2
             if ( cflags.IsKeinNlNghNgh() && (artflag.IsNichtLieferbarHersteller() ||
                  artflag.IsNichtGeliefertHersteller() ) )
             {
                return ErrorState();
             }

             if (customer->IsGeneralRestDeliveryUser()   ||
                 customer->IsImmediateRestDeliveryUser() ||
                 customer->IsReservOrderedQuantity()     ||
                 customer->IsParkRestDeliveryOrder() || ot.IsSAlwaysRestDel()  )

             {
                if ( ArtBase_->IsRestDelivery() )
                {
                   PostType( RestDelivery );
                   SetNachliefern();
                }
             }
          }
       }
    }
    else
    if ( device->IsVideo() )
    {
       CheckRestDelivery();
    }

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* Check RestDelivery capability depend on ordertype, kind of artikel and     */
/* Customers restdelivery type(Swiss and Austria                              */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CheckRestDelivery
(
)
{
    pxCustBase         *customer  = Order().Customer();  // customer
    const pxArtFlags    &artflag  = ArtBase()->ArtFlags();
    const pxArtClass    &artclass = ArtBase()->ArtClass();
    pxDevice           *device    = Session()->Device(); // device
    const pxCustOrderType&     ot = Order().OrderType();

    // CPR-170910 Nachlieferung verhindern wenn Artikel-WAFO-Typ = 0 (ART-NALI)
    if (Session()->isGermany())
    {
        if (!ArtBase_->IsRestDelivery())
        {
            ClearNachliefern();
            return ExternalError(CMsgStream(), CMSG_AD_ART_NO_RESTDELIVERY);
        }
    }

    // Check Ordertype for Restdelivery allowance
    if (!ot.IsRestDel() )
    {
        return CMSG_AD_OT_NO_RESTDEL_TYPE;
    }

    if ( !device->IsVideo() )
    {
       if ( ot.IsSAlwaysRestDel() )
       {
          return ErrorState();
       }

       if ( ot.IsRestDel() )              //  Restdelivery allowance
       {
          return ErrorState();
       }

       // Customer Restdeliverytypes 0, 1, 2, 5 no restdelivery
       if (customer->IsNotRestDeliveryUser()  || customer->IsAskCustomerForRestDelivery() ||
           customer->IsAskRestDeliveryUser() )
       {
           return CMSG_AD_CST_NO_RESTDELIVERY;
       }
       return ErrorState();
    }
    else
    if ( device->IsVideo() && IsNachliefern() )
    {
       if ( customer->IsNotRestDeliveryUser() &&  !(ot.IsSAlwaysRestDel()) )
       {
          return ExternalError( CMsgStream(), CMSG_AD_CST_NO_RESTDELIVERY, customer->IDFNr() );
       }
       if ( IsAuxPosted() )
       {
          return ExternalError( CMsgStream(), CMSG_AD_ART_NO_RESTDELIVERY );
       }
       if ( artflag.IsAusserHandel() )
       {
          return ExternalError( CMsgStream(), CMSG_AD_ART_AUSSERHANDEL, ArtikelNr_ );
       }
       if ( artflag.IsAuslaufArtikel() )
       {
          return ExternalError( CMsgStream(), CMSG_AD_ART_AUSLAUFARTIKEL, ArtikelNr_ );
       }
       if (artclass.IsOpiat() )
       {
          return ExternalError( CMsgStream(), CMSG_AD_ART_OPIAT, ArtikelNr_ );
       }
    }
    return ErrorState();

}
/*----------------------------------------------------------------------------*/
/* RestDelRedunancyCheck: is Swiss Apllications special methode               */
/* All restdelivery entries(table Nachlieferpos) are deleted, just for        */
/* PosArt_ "D" = DCT Positions.                                               */
/* Excluding some Customers located in table Parameter (ProgrammName= "KSC"   */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: RestDelRedunancyCheck
(
)
{
    short             VZ       = Order().FilialNr();
    long              IDFNr    = Order().IDFNr();
    pxVerbund::subsequentDelivery::pxDeliveryPosList* poslist  = NULL;
    pxParameterList*    parlist = NULL;
    const pxCustOrderType&   ot = Order().OrderType();

    // just for Ordertype NO
    if (!ot.IsNormal() )
    {
       return ErrorState();
    }
    // Hier muss ein Parameter her
    if ( Order().Swiss() && IsNachliefern()  && Session()->Device()->IsDCT())
    {
       poslist = new pxVerbund::subsequentDelivery::pxDeliveryPosList( Session() );
       poslist->SelectByCustomerAndArticle(VZ,IDFNr,ArtikelNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
       if ( poslist->Entries())
       {
           parlist = new pxParameterList(Session());
           parlist->Select(VZ,(nString)cPAR_KSC_GROUP ,(nString)cPAR_KSC_DEL_PURPOSE, (nString)cPAR_KSC_FOR_PARAMNAME, IDFNr);
           if (parlist->Entries() == 0 )
           {
              poslist->DeleteDCTEntries();
           }
       }
       delete poslist;
       if (parlist)
          delete parlist;
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* IsRestDeliveryPossible: check restdeliverypossibility for this article     */
/*----------------------------------------------------------------------------*/
bool
pxOrderItem :: IsRestDeliveryPossible
(
)
{
    bool retval = true;
    pxDevice  *device    = Session()->Device(); // device

    if ( !ArtBase() || !ArtBase()->IsGoodState() )
    {
       return false;
    }
    if ( !ArtBase_->IsGoodState() )     // make no since
    {
       return false;
    }

    if ( !device->IsVideo() && IsMengenKontigentDefekt() )
    {
       return false;
    }

    const pxArtFlags    &artflag  = ArtBase()->ArtFlags();
    const pxArtClass    &artclass = ArtBase()->ArtClass();

    // CPR-170910 Nachlieferung verhindern wenn Artikel-WAFO-Typ = 0 (ART-NALI)
    if (Session()->isGermany())
    {
        if (!ArtBase()->IsRestDelivery())
        {
            retval = false;
        }
    }

    if ( !artflag.IsArtikelGefuehrt() && !ArtBase()->IsRestDelivery() )
    {
        retval = false;
    }

    // articles on pseudo stocklocation
    if ( !artflag.IsArtikelGefuehrt() )
    {
       SetDispoMoeglich();
       if ( artflag.IsAusserHandel() || IsAuxPosted() ||
            artflag.IsNichtGeliefertHersteller() ||
            artflag.IsNichtLieferbarHersteller() ||
            artflag.IsNichtUeberGrossHandel() )
       {
          ClearDispoMoeglich();           // ignore purchase order
       }
    }

    if ( !IsDispoMoeglich() )
    {
       if ( artflag.IsAusserHandel()    ||
            artclass.IsOpiat()          ||
            artflag.IsEinkaufsSperre()  ||
            artflag.IsAuslaufArtikel())
       {
          retval = false;
       }
    }
    else
    {
       retval = false;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/* RestDeliveryValdate:                                                       */
/* Looks for restdelivery positions, If found, order Valdate is stored into   */
/* delivery position.                                                         */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: RestDeliveryValdate
(
)
{
    if ( AuxDelList() )
    {
        pxVerbund::subsequentDelivery::pxDeliveryPos* delpos = AuxDelList()->Find(KdAuftragNr(), PosNr(), pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
        if (delpos)
        {
           nDBBeginTransaction(cDBTransRecord);
           delpos->SetDatumValuta(Order().DatumValuta());
           delpos->Put();
           if ( delpos->IsGoodState() )
           {
              nDBCommit(cDBTransRecord);          // commit changes
           }
           else
           {
              nDBRollBack();                   // roll them back in case of any error
           }
           Error() = delpos->Error();
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  UndoRedoRestDeliveryItem: This is a split function for NL positions       */
/*  On the the original position(src), the restdelivery quantity will be      */
/*  canceled by an negativ artikelkonto entry.                                */
/*  The ordered quantity(MengeBestellt) on SRC is reduced by the restdelivery */
/*  quantity.After that, the restdelivery quantity of SRC will be booked on    */
/*  THIS object(NewOrderItem).                                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoRestDeliveryItem
(
    pxOrderItem* src                    // container item
)
{
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return
    short flags = 0;

    long MengeBestellt = src->MengeBestellt();

    long    MengeNachgeliefert  = src->MengeNachgeliefert();

    if ( !src->IsNachliefern() )
    {
       return ErrorState();
    }
    //first undo auyposting on src
    src->nDBBeginTransaction(cDBTransRecord);
    pxVerbund::subsequentDelivery::pxDeliveryPos* dp = src->AuxDelList()->Find(src->KdAuftragNr(), src->PosNr(), pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
    if (dp)
    {
       dp->Delete();
    }

    src->ClearNachliefern();              // clear restdelivery marker
    // reduce MengeBestaetig and MengeBestellt by auxdelivery quantity
    src->MengeBestaetigt( src->MengeBestaetigt() - MengeNachgeliefert);
    src->MengeBestellt( src->MengeBestellt() - MengeNachgeliefert);
    if (src->MengeBestellt() == 0 )
    {
       src->MengeBestellt(MengeBestellt);
    }
    Error() = src->Error();
    if ( IsGoodState() )
    {
       src->nDBCommit(cDBTransRecord);
    }
    else
    {
       src->nDBRollBack();
       return ErrorState();
    }

    // Now rebook the auxdelivery quantity on this object.
    // Init some member
    MengeBestellt_   = 0;
    MengeAbgebucht_  = 0;
    MengeGeliefert_  = 0;
    MengeBestaetigt_ = 0;
    flags |= bPOST_IGN_LACK;

    InitOrderItem_Core(ArtikelNr_, MengeNachgeliefert,0L,0L,
                 pxOrderItem::RestDelivery, pxOrderItem::TypeProductStocked,
                 flags);

    if (!IsGoodState())
    {
       ClearError();
    }
    return 0;
}
