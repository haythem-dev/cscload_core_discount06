/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Calculate what kind of charge has to use for this product

REVISION HISTORY

05 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxitembatch.hpp"
#include "pxorder.hpp"

MessageCodeEnum pxOrderItem::checkBatchRequest(const nString& batchCode, const bool fixBatch)
{
	return this->Order().isBatchValid(batchCode, fixBatch);
}

MessageCodeEnum	pxOrderItem::StoreFixBatchInfo(const nString& batchNr)
{
	return StoreBatchInfo(batchNr, true);
}

MessageCodeEnum	pxOrderItem::StoreDesiredBatchInfo(const nString& batchNr)
{
	return StoreBatchInfo(batchNr, false);
}


/*----------------------------------------------------------------------------*/
/*  StoreChargenNr: this methode inserts a kdauftragposcharge entry for this  */
/*  item depend on ChargenNr. If ChargenNr IsEmpty, no entry will be written  */
/*  Please take care of a well constructed item object to prevent             */
/*  unpredictable results. Returnvalue is MessageCodeEnum                     */
/*----------------------------------------------------------------------------*/
MessageCodeEnum pxOrderItem::StoreBatchInfo(const nString& batchNr, bool isFixBatch)
{
	nString	batchNrString = batchNr;
	batchNrString.Strip();

	MessageCodeEnum messageCode = this->Order().isBatchValid(batchNrString, isFixBatch);

	pxItemBatch* batch = new pxItemBatch(Session(), KdAuftragNr_, PosNr_);	// kdauftragposcharge object

	if(batchNrString.IsEmpty())	// empty container
	{
		if (0 == batch->Get(cDBGET_READONLY))     // no entry found
		{
			batch->Delete();
		}

		delete batch;
		return CMSG_OK;
	}

	if(CMSG_OK != messageCode)
	{
		delete batch;
		return messageCode;
	}

	//batch->nDBBeginTransaction(cDBTransRecord);

	batch->Get(cDBGET_FORUPDATE);
	if ( !batch->IsGoodState() )     // no entry found
	{
		batch->ClearError();
	}

	batch->SetFixBatch(isFixBatch);
	batch->SetBatchNr(batchNrString);
	batch->SetQuantityOrdered(0L);
	batch->Put();
	//if(batch->IsGoodState())
	//{
	//	batch->nDBCommit(cDBTransRecord);     // commit changes
	//}
	//else
	//{
	//	batch->nDBRollBack();
	//}

	Error() = batch->Error();
	delete batch;

	return messageCode;
}

/*----------------------------------------------------------------------------*/
/*  GetChargenNr: this methode returns from  a kdauftragposcharge entry for   */
/*  this item, the ChargenNr.                                                 */
/*  returnvalue is a nString empty or filled with items chargennr             */
/*  Please take care of a well constructed item object to prevent             */
/*  unpredictable results. Returnvalue is MessageCodeEnum                     */
/*----------------------------------------------------------------------------*/
basar::VarString pxOrderItem::GetChargenNr()
{
   pxItemBatch* batch = NULL;	// kdauftragposcharge object
   nString Num;
   Num.Strip();        // delete spaces

   batch = new pxItemBatch(Session(), KdAuftragNr_, PosNr_);
   batch->Get(cDBGET_READONLY);

   if(batch->IsGoodState())	// no entry found
   {
      Num = batch->BatchNr();
      Num.Strip();	// delete spaces
   }

   delete batch;
   return static_cast<basar::VarString>(Num);
}

bool pxOrderItem::IsFixBatch() const
{
    bool retval = false;
    pxItemBatch batchInfo(Session(), KdAuftragNr_, PosNr_);
    batchInfo.Get(cDBGET_READONLY);

    if (batchInfo.IsGoodState() && (1 == batchInfo.FixBatch()))
    {
        retval = true;
    }

    return retval;
}
