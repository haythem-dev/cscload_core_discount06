#include "pxartacc.hpp"
#include "tartacct.h"
#include "pxsess.hpp"
#include "time.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtAccount::pxArtAccount
(
	pxSession   *session
)
	: pxDBRecord(session)
{
	Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtAccount::pxArtAccount
(
	pxArtAccount& src
)
	: pxDBRecord(src.Session())
{
	Init();
	(*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTIKELKONTO structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxArtAccount::pxArtAccount
(
	pxSession   *session,
	const tARTIKELKONTO& src
)
	: pxDBRecord(session)
{
	Init();
	(*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use pxOrderItem to construct this instance.                               */
/*----------------------------------------------------------------------------*/
pxArtAccount::pxArtAccount
(

	pxSession   *session,
	const  char  transactiontype
)
	: pxDBRecord(session)
{
	nTime now;
	Init();

	LfdNr_ = 0;                        // serial   number
	BewegungsArt_ = transactiontype;          // transaction type
	ZeitUnix_ = static_cast<long>(now.GetSecs());            // time in seconds since
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtAccount :: ~pxArtAccount()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTIKELKONTO structure.       */
/*----------------------------------------------------------------------------*/
tARTIKELKONTO&
Assign
(
	tARTIKELKONTO&           dest,
	const pxArtAccount&       src
)
{
	dest.LfdNr = src.LfdNr_;
	dest.FilialNr = src.FilialNr_;
	dest.ArtikelNr = src.ArtikelNr_;
	dest.BewegungsArt = src.BewegungsArt_;
	dest.Menge = src.Menge_;
	dest.BelegNr = src.BelegNr_;
	dest.Uid = src.Uid_;
	dest.IDFNr = src.IDFNr_;
	dest.MengeNeu = src.MengeNeu_;
	dest.ZeitUnix = src.ZeitUnix_;
	dest.BewegungSchluessel = src.BewegungSchluessel_;
	dest.StockReserved = src.StockReserved_;
	dest.MoveType = static_cast<short>(src.MoveType_);
	dest.PosNr = src.PosNr_;

	dest.BelegArt[0] = ' ';
	src.BelegArt_.GetData(dest.BelegArt);

	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTIKELKONTO structure to construct       */
/*  a pxArtAccount object.                                                    */
/*----------------------------------------------------------------------------*/
pxArtAccount&
Assign
(
	pxArtAccount&              dest,
	const tARTIKELKONTO&        src
)
{
	dest.LfdNr_ = src.LfdNr;
	dest.FilialNr_ = src.FilialNr;
	dest.ArtikelNr_ = src.ArtikelNr;
	dest.BewegungsArt_ = src.BewegungsArt;
	dest.Menge_ = src.Menge;
	dest.BelegNr_ = src.BelegNr;
	dest.Uid_ = src.Uid;
	dest.IDFNr_ = src.IDFNr;
	dest.MengeNeu_ = src.MengeNeu;
	dest.ZeitUnix_ = src.ZeitUnix;
	dest.BewegungSchluessel_ = src.BewegungSchluessel;
	dest.StockReserved_ = src.StockReserved;
	dest.MoveType_ = static_cast<ReservationTypeEnum>(src.MoveType);
	dest.PosNr_ = src.PosNr;
	dest.BelegArt_ = src.BelegArt;

	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtAccount::Init()
{
	tARTIKELKONTO    record;
	memset(&record, 0, sizeof(tARTIKELKONTO));
	Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTIKELKONTO struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxArtAccount&
pxArtAccount :: operator=(const pxArtAccount& src)
{
	tARTIKELKONTO record;               // used to export the data of 'src'
	Assign(*this, Assign(record, src));
	return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKELKONTO structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArtAccount&
pxArtAccount :: operator=(const tARTIKELKONTO& src)
{
	return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Builds the transactionkey from the arguments into a long.                 */
/*  Arguments:  Type of order, Type of Stocktransaction, type of shipment,    */
/*              Reason code                                                   */
/*----------------------------------------------------------------------------*/
long
pxArtAccount::TransActionKey
(
	const enum BookingTypeEnum bookingType,
	const enum PickingTypeEnum pickingType
)
{
	pxOrderType::tOrderTypeCode cCategory = pxOrderType::Normal;

	return BewegungSchluessel_ = (bookingType * 10000000) + (cCategory * 1000) + (pickingType * 100);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtAccount::Get
(
	DBAccessMode mode
)

{
	tARTIKELKONTO record;
	memset(&record, 0, sizeof(tARTIKELKONTO));
	record.LfdNr = LfdNr_;
	int retval = (mode == cDBGET_FORUPDATE) ? nDBReadLock(&record)
		: nDBRead(&record);
	if (!retval)
		(*this) = record;          // import the data from tARTIKELKONTO
	else if (retval > cDBXR_NORMAL)
		ExternalCondition(CMsgStream(),
			CMSG_ACC_ENTRY_NOTFOUND, LfdNr_);

	return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArtAccount::Put
(
)
{
	tARTIKELKONTO record;
	memset(&record, 0, sizeof(tARTIKELKONTO));
	Assign(record, *this);
	return nDBWrite(&record, sizeof(tARTIKELKONTO));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArtAccount::Delete
(
)
{
	tARTIKELKONTO record;
	memset(&record, 0, sizeof(tARTIKELKONTO));
	Assign(record, *this);
	return Delete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtAccount::Read
(
	const void  *record
)
{
	tARTIKELKONTO* recordp = (tARTIKELKONTO*)record;
	return pxRArtikelKontoRead(recordp, Session()->getDatabaseName(recordp->FilialNr).c_str());
}

int
pxArtAccount::ReadLock
(
	const void  *record
)
{
	tARTIKELKONTO* recordp = (tARTIKELKONTO*)record;
	return pxRArtikelKontoReadLock(recordp, Session()->getDatabaseName(recordp->FilialNr).c_str());
}

int
pxArtAccount::Update
(
	const void  *record
)
{
	tARTIKELKONTO* recordp = (tARTIKELKONTO*)record;
	return pxRArtikelKontoUpdate(recordp, Session()->getDatabaseName(recordp->FilialNr).c_str());
}

int
pxArtAccount::Delete
(
	const void  *record
)
{
	tARTIKELKONTO* recordp = (tARTIKELKONTO*)record;
	return pxRArtikelKontoDelete(recordp, Session()->getDatabaseName(recordp->FilialNr).c_str());
}

int
pxArtAccount::Insert
(
	const void  *record
)
{
	tARTIKELKONTO* recordp = (tARTIKELKONTO*)record;
	return pxRArtikelKontoInsert(recordp, Session()->getDatabaseName(recordp->FilialNr).c_str());
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtAccount list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxArtAccount::CompareTo
(
	const nCollectable   *That,
	void           * /*p*/,
	const long           /*lparm*/
)   const

{
	pxArtAccount *that = (pxArtAccount*)That;
	int retval = (ZeitUnix_ == that->ZeitUnix_) ? 0
		: (ZeitUnix_ > that->ZeitUnix_ ? 1 : -1);

	return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtAccountList::pxArtAccountList
(
	pxSession   *session
)
	: nDBRecordSet(session)
{
	nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxArtAccountList::Select
(
	const int     count_
)
{
	tARTIKELKONTO fil;
	memset(&fil, 0, sizeof(tARTIKELKONTO));  // zero out entire record buffer
	int cursorid = cCRSARTIKELKONTO_Default;
	nDBSelect(&fil, cursorid, count_);

	return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records belongs to KdAufftragNr. of    */
/*  the current customer.                                                     */
/*----------------------------------------------------------------------------*/
size_t
pxArtAccountList::Select
(
	const long    BelegNr,
	const long    IDFNr,
	const int     count_
)
{
	tARTIKELKONTO fil;
	memset(&fil, 0, sizeof(tARTIKELKONTO));  // zero out entire record buffer
	fil.BelegNr = BelegNr;
	fil.IDFNr = IDFNr;
	int cursorid = cCRSARTIKELKONTO_Beleg;
	nDBSelect(&fil, cursorid, count_);

	return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtAccountList::AddToList
(
	const void  *record,
	const int  /*row*/
)

{
	// construct new 'pxArtAccount' object:
	pxArtAccount *objectp = new pxArtAccount(Session(), *(tARTIKELKONTO*)record);
	InsertAscending(objectp);
	return objectp;
}

int
pxArtAccountList::EndBrowse
(
	const int  /*cursorid*/
)
{
	return pxRArtikelKontoEndBrowse();
}


int
pxArtAccountList::GetNext
(
	const void  *record,
	const int  /*cursorid*/
)
{
	tARTIKELKONTO* recordp = (tARTIKELKONTO*)record;
	return pxRArtikelKontoGetNext(recordp);
}

int
pxArtAccountList::StartBrowse
(
	const void  *record,
	const int  cursorid
)
{
	tARTIKELKONTO* recordp = (tARTIKELKONTO*)record;
	return pxRArtikelKontoStartBrowse(recordp, Session()->getDatabaseName(recordp->FilialNr).c_str(), cursorid);
}
