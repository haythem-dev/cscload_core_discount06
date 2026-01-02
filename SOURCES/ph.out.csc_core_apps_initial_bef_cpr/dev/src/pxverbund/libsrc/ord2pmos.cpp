#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxcstrou.hpp"

/*----------------------------------------------------------------------------*/
/*  Set values used by old PHARMOS modules.                                   */
/*----------------------------------------------------------------------------*/
void
pxOrder :: ToPharmos
(
)

{
    ClearErfassungZurueckGestellt();
    ClearErfassungAbgeschlossen();

    if ( IsEntryDeferred() )
       SetErfassungZurueckGestellt();
    if (IsEntryClosed())
       SetErfassungAbgeschlossen();
    if (IsShipmentInProgress())
       SetKommiBegonnen();
    if (IsShipmentClosed())
       SetKommiBeendet();
    if (IsInvoiceable())
       SetFakturierbar();
    if (IsInvoiced())
       SetFakturiert();
    if (IsCancelled())
       SetStorniert();
    if (IsProtected())
       SetNichtAenderbar();

/*----------------------------------------------------------------------------*/
/*  Set Next- and LastTourId (special pharmos requirement)                    */
/*----------------------------------------------------------------------------*/
    //OrderTourId_.Strip();                    // strip of trailing spaces
    NaechsteTour_.Strip();              // strip of trailing spaces
    LetzteTour_.Strip();                // strip of trailing spaces

    if (! this->TourId().IsEmpty() )           // just if TourId_
    {
       pxCustRouteList   *rl = Customer()->RouteList();
       if ( rl->Entries() )
       {
          LetzteTour_           = Customer()->LastTourId();
          pxCustRouteListIter cursor(*rl); // define an iterator
          pxCustRoute              *route; // entry pointer
          while ( ( (route = (pxCustRoute*) ++cursor) != NULL ) && route->TourId() != this->TourId() )
          {
             ;
          }

          if ( this->TourId() ==  LetzteTour_ )
             NaechsteTour_ = Customer()->FirstTourId();
          else
          if ( (route = (pxCustRoute*) ++cursor) != NULL )
          {
             NaechsteTour_ =  route->TourId();
             if ( NaechsteTour_ ==  LetzteTour_ && !Customer()->FirstTourId().IsEmpty() )
                NaechsteTour_ = Customer()->FirstTourId();
          }
       }
    }

}
/*----------------------------------------------------------------------------*/
/*  Get values from old PHARMOS modules.                                      */
/*----------------------------------------------------------------------------*/
void
pxOrder :: FromPharmos
(
)

{
    if (IsKommiBegonnen())
       SetShipmentInProgress();
    else
       ClearShipmentInProgress();
    if (IsKommiBeendet())
       SetShipmentClosed();
    if (IsFakturierbar())
       SetInvoiceable();
    else
       ClearInvoiceable();
    if (IsFakturiert())
       SetInvoiced();
    if (IsStorniert())
       SetCancelled();
    if (IsNichtAenderbar())
       SetProtected();
}
