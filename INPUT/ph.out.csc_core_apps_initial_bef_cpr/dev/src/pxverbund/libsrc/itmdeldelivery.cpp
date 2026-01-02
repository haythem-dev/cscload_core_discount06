/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Implementation of oveloaded order item entry methods.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxartbas.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"

/*----------------------------------------------------------------------------*/
/*  IsDelayedDelivery : this method looks for the possibility of delayed      */
/*  delivery, depend on type of Article(BTM,KK,K04,K08 etc) and on customers  */
/*  entry within the table DELAYEDDELIVERYCST, where the article are specified*/
/*  for delayed delivery                                                      */
/*----------------------------------------------------------------------------*/
bool
pxOrderItem :: IsDelayedDelivery
(
)
{
    nDate today;
    pxCustBase* customer        = Order().Customer();
    pxArtBase&          artbase = *ArtBase();
    const pxArtFlags&  artflags = artbase.ArtFlags();
	const pxArtClass&  artclass = artbase.ArtClass();
    // do just for non video devices
    if ( (Session()->Device()->IsVideo()) )
       return false;

    pxCustDelDelivery* custddel = customer->getDelayedDelivery(today, Order().getWithTransportExclusion());
    if (custddel == NULL )
       return false;

    // now check item
    if ( IsCancelled() || ArtikelNr() == 0 || !IsKnownProduct() )
       return false;

    // now check type of article and custdel values
    if ((artclass.IsOpiat()       && custddel->IsNarCotic())  ||
        (artflags.IsKuehlKette()  && custddel->IsColdChain()) ||
        (artflags.IsGekuehlt08()  && custddel->IsCool08())    ||
        (artflags.IsGekuehlt20()  && custddel->IsCool20()))
    {
       if ( MengeGeliefert() > 0 && !IsAuxPosted() && !IsNachliefern() )
       {
          if ( Order().TourId().IsEmpty() )
              Order().RouteAssign();
          if ( Order().TourId().IsEmpty() )
             return false;
          // check customers specifications		  
          nString tourid = Order().TourId();
          if ( customer->IsDelayedDelivery( tourid, Order().getWithTransportExclusion() ) )  // check customers specifications
             return true;
       }
    }
    return false;
}
