#include "pxorder.hpp"
#include "pxnarctransfer.hpp"
#include "pxcomtyp.hpp"

/*----------------------------------------------------------------------------*/
/*  CompleteNarcTransferEntries: this methode looks for                       */
/*  narctransactiontransfer(on BTM positions) entries to comlete them for     */
/*  further use. This methode is called within the order transfer program     */
/*----------------------------------------------------------------------------*/
int pxOrder::CompleteNarcTransferEntries( long PharmosOrderNo )
{
    pxNarcTransfer*        entriep;
    pxNarcTransferList*    NarcList = NULL;
    char                  complete = '1';

    if( 0 == PharmosOrderNo )
    {
       return ErrorState();
    }

    NarcList = new pxNarcTransferList(Session());
    NarcList->Select( FilialNr_, KdAuftragNr_);
    if (NarcList->Entries())
    {
       pxNarcTransferListIter Iter(*NarcList);
       while ( (entriep = (pxNarcTransfer*) ++Iter) != NULL )
       {
          nDBBeginTransaction(cDBTransRecord);
          entriep->Get(cDBGET_FORUPDATE);
          entriep->PurchaseOrderNo(PharmosOrderNo);
          entriep->CompletedFlag(complete);
		  if (CommType().IsNoShipment())
		  {
			  entriep->CompletedFlag('2');
		  }
          entriep->SetTourId(this->TourId());
          entriep->Put();
          if (entriep->IsGoodState() )
          {
             nDBCommit(cDBTransRecord);
          }
          else
          {
             nDBRollBack();             // roll back all changes done
          }
       }
    }
    delete NarcList;
    NarcList = NULL;
    return ErrorState();
}
