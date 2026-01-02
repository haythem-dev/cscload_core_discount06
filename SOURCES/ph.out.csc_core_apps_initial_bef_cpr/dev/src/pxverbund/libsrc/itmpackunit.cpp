/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Calculate package unit depend on quantity ordered
*/

#include "pxitem.hpp"
#include "pxartbas.hpp"
#include "pxartpackunit.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxposparking.hpp"

/*----------------------------------------------------------------------------*/
/*  CheckPackageUnit.                                                         */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: CheckPackageUnit
(
    const long QToPost,           // quantity to post
    const long /*QInStock*/       // quantity currently available in stock
)
{
    long orderq    = QToPost;
    pxArtBase&        artbase      = *ArtBase();
    pxArtPackUnitList* PUnitList   = artbase.PackageUnitList();
    pxArtPackUnit*           PUnit = NULL;
    pxPosParkingList*     ParkList = NULL;
    pxPosParking*            Parkp = NULL;
    short                BranchNo = Order().Customer()->Vertriebszentrum();
    long               CustomerNo = Order().Customer()->IDFNr();
    long                   deltaq = 0;
    long                    parkq = 0;
    bool                  QRoundOK = false;
    bool                  PUReached = false;

    if ( PUnitList == NULL )
       return -1;                       // no articlepackunit entries
    if ( PUnitList->Entries()  == NULL )
       return -1;                       // no articlepackunit entries

    // look first for exiting positionparking entries
    ParkList = new pxPosParkingList(Session());
    ParkList->Select(BranchNo, CustomerNo, ArtikelNr_);
    pxPosParkingListIter Iter(*ParkList);
    while ( (Parkp = (pxPosParking*) ++Iter) != NULL )
    {
       parkq += Parkp->OrderQty();
    }

    orderq += parkq;
    // now check for package units
    pxArtPackUnitListIter cursor(*PUnitList);
    for ( cursor.ToLast(); (PUnit = ( pxArtPackUnit*)cursor.Current()) != NULL; --cursor )
    {
       if ( (orderq % PUnit->PackingUnit()) == 0 )
       {
          QRoundOK = true;
          break;
       }
       deltaq = PUnit->PackingUnit() - (orderq % PUnit->PackingUnit());
       if ( deltaq < PUnit->PackingUnit() &&
            deltaq <= ((PUnit->PackingUnit() * (PUnit->RoundPct()*10) + 500) / 1000) )
       {
          orderq += deltaq;
          QRoundOK = true;
          break;
       }
       if ( orderq > PUnit->PackingUnit() )
          PUReached = true;
    }

    // now check what to do
    if ( QRoundOK )                  // Modulo check = 0 or quantity raised
    {
       if ( parkq  > 0 )
       {
          Iter.Reset();
          while ( (Parkp = (pxPosParking*) ++Iter) != NULL )
          {
             Parkp->Delete();        // delete from database
             delete Iter.Remove();   // delete from list
          }
       }
       delete ParkList;
       return orderq;
    }

    if ( PUReached )                 // Modulo check !0 and not quantity raised
    {
       orderq += deltaq;             // from the smallest PU
       if ( parkq > 0 )
       {
          Iter.Reset();
          while ( (Parkp = (pxPosParking*) ++Iter) != NULL )
          {
             Parkp->Delete();        // delete from database
             delete Iter.Remove();   // delete from list
          }
       }
       delete ParkList;
       return orderq;
    }

    Parkp = new pxPosParking(Session(),BranchNo,CustomerNo,ArtikelNr_,KdAuftragNr_,QToPost);
    Parkp->Put();
    orderq = 0;
    delete ParkList;

    return orderq;

}
