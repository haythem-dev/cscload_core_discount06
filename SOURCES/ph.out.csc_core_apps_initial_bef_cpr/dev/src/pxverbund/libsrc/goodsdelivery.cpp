#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxgoodsdelivery.hpp"
#include "pxorder.hpp"

/*----------------------------------------------------------------------------*/
/* Constructor to build up a list of pxGoodsDelivery Objects.                 */
/* Every Object contains important members for correct stockreceipt           */
/* processing                                                                 */
/* Some members are not used at this moment, but I stored them for future     */
/* use                                                                        */
/* The list is build depend on ArtikelNr and FilialNr and is sorted depend    */
/* on  customers ABC Kz(= KUNDE.KzKdKlasse).                                  */
/* Within the group is date the sortcriterion(Ascending).                                  */
/*----------------------------------------------------------------------------*/
pxGoodsDeliveryList :: pxGoodsDeliveryList
(
    pxSession*     session,
    long          ArtikelNr,
    short         FilialNr
)
{
    session_   = session;
    ArtikelNr_ = ArtikelNr;
    FilialNr_  = FilialNr;
    pxVerbund::subsequentDelivery::pxDeliveryPosList     *dellist = new pxVerbund::subsequentDelivery::pxDeliveryPosList( Session() );
    pxVerbund::subsequentDelivery::pxDeliveryPosListIter  cursor(*dellist);
    pxVerbund::subsequentDelivery::pxDeliveryPos         *delpos;
        nString         KdAuftragArt;

    // Select a list of NachLieferPos entries from type restdelivery
    dellist->SelectByArticle( FilialNr_, ArtikelNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
    if ( dellist->Entries() )
    {
       cursor.Reset();                  // top of list
       while ( ( delpos = (pxVerbund::subsequentDelivery::pxDeliveryPos *) ++cursor ) != NULL )
       {
          KdAuftragArt = delpos->KdAuftragArt();
          KdAuftragArt.Strip();

          pxCustBase customer(session_, FilialNr_, delpos->IDFNr());
          if ( !customer.IsGoodState() )
             continue;

          if ( customer.Flags().IsKundeGesperrt() )
             continue;

           if ( KdAuftragArt == "UW" )
             continue;

           pxVerbund::subsequentDelivery::pxDeliveryPos* liefpos = new pxVerbund::subsequentDelivery::pxDeliveryPos(*delpos);
		   InsertAscending(new pxGoodsDelivery(liefpos,customer.KzKdKlasse(),customer.NachLieferTyp()));
       }
    }
}
/*----------------------------------------------------------------------------*/
/* Constructor to build up a list of pxGoodsDelivery Objects.                 */
/* Every Object contains important members for correct stockreceipt           */
/* processing                                                                 */
/* Some members are not used at this moment, but I stored them for future     */
/* use                                                                        */
/* The list is build depend on ArtikelNr and FilialNr and is sorted depend    */
/* on  customers ABC Kz(= KUNDE.KzKdKlasse).                                  */
/* Within the group is date the sortcriterion(Ascending).                                  */
/*----------------------------------------------------------------------------*/
pxGoodsDeliveryList :: pxGoodsDeliveryList
(
    pxSession*     session,
    long          ArtikelNr,
    short         FilialNr,
    nString&       KdAuftragArt
)
{
    session_   = session;
    ArtikelNr_ = ArtikelNr;
    FilialNr_  = FilialNr;
    pxVerbund::subsequentDelivery::pxDeliveryPosList     *dellist = new pxVerbund::subsequentDelivery::pxDeliveryPosList( Session() );
    pxVerbund::subsequentDelivery::pxDeliveryPosListIter  cursor(*dellist);
    pxVerbund::subsequentDelivery::pxDeliveryPos         *delpos;

    // Select a list of NachLieferPos entries from type restdelivery
    dellist->SelectByArticleAndOrderType( FilialNr_,ArtikelNr_, (short)pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM, KdAuftragArt);
    if ( dellist->Entries() )
    {
       cursor.Reset();                  // top of list
       while ( ( delpos = (pxVerbund::subsequentDelivery::pxDeliveryPos *) ++cursor ) != NULL )
       {
          // fetch KUNDE, just NachLieferTyp 4 and 5 and 6 are in affected.
          pxCustBase customer(session_, FilialNr_, delpos->IDFNr());
          if ( !customer.IsGoodState() )
             continue;

          if ( customer.Flags().IsKundeGesperrt() )
             continue;

          pxVerbund::subsequentDelivery::pxDeliveryPos* liefpos = new pxVerbund::subsequentDelivery::pxDeliveryPos(*delpos);
          InsertAscending(new pxGoodsDelivery(liefpos,customer.KzKdKlasse(),customer.NachLieferTyp()));
       }
    }
}

/*----------------------------------------------------------------------------*/
/* Constructor to build up a list of pxGoodsDelivery Objects.                 */
/* Every Object contains important members for correct stockreceipt           */
/* processing                                                                 */
/* Some members are not used at this moment, but I stored them for future     */
/* use                                                                        */
/* The list is build depend on ArtikelNr and FilialNr and is sorted depend    */
/* on  customers ABC Kz(= KUNDE.KzKdKlasse).                                  */
/* Within the group is date the sortcriterion(Ascending).                                  */
/*----------------------------------------------------------------------------*/
pxGoodsDeliveryList::pxGoodsDeliveryList
(
    pxSession* session,
    long          kdAuftragNr,
    short FilialNr,
    long IdfNr,
    nString& KdAuftragArt
)
{
    session_ = session;
    FilialNr_ = FilialNr;

    pxVerbund::subsequentDelivery::pxDeliveryPosList* dellist = new pxVerbund::subsequentDelivery::pxDeliveryPosList(Session());
    pxVerbund::subsequentDelivery::pxDeliveryPosListIter  cursor(*dellist);
    pxVerbund::subsequentDelivery::pxDeliveryPos* delpos;

    dellist->SelectByOrderAndCustomerAndOrderTyp(kdAuftragNr, FilialNr, IdfNr, KdAuftragArt);

    if (dellist->IsGoodState() && dellist->Entries() > 0)
    {
        cursor.Reset();
        while ((delpos = (pxVerbund::subsequentDelivery::pxDeliveryPos*) ++cursor) != NULL) {

            pxCustBase customer(session_, FilialNr_, delpos->IDFNr());
            if (!customer.IsGoodState())
                continue;

            if (customer.Flags().IsKundeGesperrt())
                continue;

            pxVerbund::subsequentDelivery::pxDeliveryPos* liefpos = new pxVerbund::subsequentDelivery::pxDeliveryPos(*delpos);
            Append(new pxGoodsDelivery(liefpos, customer.KzKdKlasse(), customer.NachLieferTyp()));
        }
    }
}
/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxGoodsDeliveryList :: Clear()
{

    pxGoodsDelivery  *curp;
    pxGoodsDeliveryListIter cursor(*this);
    while ( (curp = (pxGoodsDelivery*) ++cursor) != NULL )
    {
       cursor.Remove();
       delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/*  Constructor of class pxDisInKind.                                         */
/*----------------------------------------------------------------------------*/
pxGoodsDelivery :: pxGoodsDelivery
(
    pxVerbund::subsequentDelivery::pxDeliveryPos*   delpos,
    const nString&   KzKdKlasse,
    char             NachLieferTyp
)
{
    DeliveryPos_    = delpos;
    KzKdKlasse_     = KzKdKlasse;
    NachLieferTyp_  = NachLieferTyp;
    ArtikelNr_      = delpos->ArtikelNr();
    IDFNr_          = delpos->IDFNr();
    FilialNr_       = delpos->VertriebszentrumNr();
    date_           = delpos->Datum();
	ArtReservation_ = false;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxGoodsDelivery :: pxGoodsDelivery
(
    const pxGoodsDelivery& src
)
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxGoodsDelivery :: ~pxGoodsDelivery()
{
   if (DeliveryPos_)
     delete DeliveryPos_;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxGoodsDelivery list objects being inserted in the following      */
/*  ascending  sequence:                                                      */
/*  ABC-Kz, Datum                                                              */
/*----------------------------------------------------------------------------*/
int
pxGoodsDelivery :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxGoodsDelivery *that = (pxGoodsDelivery*)That;

    int  retval = (KzKdKlasse_ == that->KzKdKlasse_) ? 0
                  : (KzKdKlasse_ > that->KzKdKlasse_ ? 1 : -1);

    if ( retval == 0 )
        retval = (date_ == that->date_) ? 0
                  : (date_ > that->date_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/* check if item is available for subsequent delivery order	processing        */
/*----------------------------------------------------------------------------*/
bool pxGoodsDelivery::IsAvailableForOrderProcessing( pxSession* session, long kdauftragnr )
{
    bool retval = true;
    pxOrder* original_order = new pxOrder(session, kdauftragnr, cDBGET_READONLY);
    if ( original_order->IsGoodState() )
    {
        if( !original_order->IsEntryClosed() )
        {
            retval = false;
        }
    }
    delete original_order;
    original_order = NULL;
    return retval;
}
