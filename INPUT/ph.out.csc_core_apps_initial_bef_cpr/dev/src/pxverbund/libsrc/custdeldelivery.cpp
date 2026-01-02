#include "pxcustdeldelivery.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
//#include "emergencyservice.h"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery :: pxCustDelDelivery
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
pxCustDelDelivery :: pxCustDelDelivery
(
    pxCustDelDelivery& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tDELAYEDDELIVERYCST structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery :: pxCustDelDelivery
(
    pxSession   *session,
    tDELAYEDDELIVERYCST& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery :: pxCustDelDelivery
(
    pxSession    *session,
    const short        BranchNo,            // Branchnumber
    const long         CustomerNo,          // Customernumber
    const short        WeekDay             // Day of Week
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_    = BranchNo;
    CustomerNo_  = CustomerNo;
    WeekDay_     = WeekDay;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery :: ~pxCustDelDelivery()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDELAYEDDELIVERYCST structure.       */
/*----------------------------------------------------------------------------*/
tDELAYEDDELIVERYCST&
Assign
(
    tDELAYEDDELIVERYCST&           dest,
    const pxCustDelDelivery&     src
)
{
    dest.BranchNo     = src.BranchNo_;
    dest.CustomerNo   = src.CustomerNo_;
    dest.WeekDay      = src.WeekDay_;
    dest.Time         = src.Time_.GetHHMMSS()/100;
    dest.TourId[0] = ' ';
    src.TourId_.GetData(dest.TourId);
    dest.Activ         = src.Activ_;
    dest.DelayedWeekDay = src.DelayedWeekDay_;
    dest.NarCotic      = src.NarCotic_       ;
    dest.ColdChain     = src.ColdChain_      ;
    dest.Cool08        = src.Cool08_         ;
    dest.Cool20        = src.Cool20_         ;
    dest.DateFrom      = src.DateFrom_.GetYYYYMMDD()  ;
    dest.DateTo        = src.DateTo_.GetYYYYMMDD()    ;


    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDELAYEDDELIVERYCST structure to                 */
/*  a pxCustDelDelivery object.                                                  */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery&
Assign
(
    pxCustDelDelivery&              dest,
    const tDELAYEDDELIVERYCST&         src
)
{
    dest.BranchNo_     = src.BranchNo;
    dest.CustomerNo_   = src.CustomerNo;
    dest.WeekDay_      = src.WeekDay;
    dest.Time_         = src.Time*100;
    dest.TourId_       = src.TourId;
    dest.Activ_        = src.Activ;
    dest.DelayedWeekDay_ = src.DelayedWeekDay;
    dest.NarCotic_      = src.NarCotic       ;
    dest.ColdChain_     = src.ColdChain      ;
    dest.Cool08_        = src.Cool08         ;
    dest.Cool20_        = src.Cool20         ;
    dest.DateFrom_      = nDate(src.DateFrom);
    dest.DateTo_        = nDate(src.DateTo)  ;


    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustDelDelivery :: Init()
{
    tDELAYEDDELIVERYCST    record;
    memset(&record, 0 , sizeof(tDELAYEDDELIVERYCST));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDELAYEDDELIVERYCST struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery&
pxCustDelDelivery :: operator=( const pxCustDelDelivery& src)
{
    tDELAYEDDELIVERYCST record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDELAYEDDELIVERYCST structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery&
pxCustDelDelivery :: operator=( const tDELAYEDDELIVERYCST& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustDelDelivery :: Get
(
    DBAccessMode mode
)

{
    tDELAYEDDELIVERYCST record;
    memset(&record, 0, sizeof(tDELAYEDDELIVERYCST));
    record.BranchNo    = BranchNo_;
    record.CustomerNo  = CustomerNo_;
    record.WeekDay     = WeekDay_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tDELAYEDDELIVERYCST struct
   /* else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_AQUOT_ENTRY_NOTFOUND, BranchNo_, CustomerNo_, ArticleNo_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustDelDelivery :: Put
(
)
{
    tDELAYEDDELIVERYCST record;
    memset(&record, 0, sizeof(tDELAYEDDELIVERYCST));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tDELAYEDDELIVERYCST));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCustDelDelivery :: Delete
(
)
{
    tDELAYEDDELIVERYCST record;
    memset(&record, 0, sizeof(tDELAYEDDELIVERYCST));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustDelDelivery :: Read
(
    const void  *record
)
{
    return pxCustDelDeliveryRead((tDELAYEDDELIVERYCST*)record);
}

int
pxCustDelDelivery :: ReadLock
(
    const void  *record
)
{
    return pxCustDelDeliveryReadLock((tDELAYEDDELIVERYCST*)record);
}

int
pxCustDelDelivery :: Update
(
    const void  *record
)
{
    return pxCustDelDeliveryUpdate((tDELAYEDDELIVERYCST*)record);
}

int
pxCustDelDelivery :: Delete
(
    const void  *record
)
{
    return pxCustDelDeliveryDelete((tDELAYEDDELIVERYCST*)record);
}

int
pxCustDelDelivery :: Insert
(
    const void  *record
)
{
    return pxCustDelDeliveryInsert((tDELAYEDDELIVERYCST*)record);
}

int
pxCustDelDeliveryList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCustDelDeliveryEndBrowse(cursorid);
}


int
pxCustDelDeliveryList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxCustDelDeliveryGetNext((tDELAYEDDELIVERYCST*)record, cursorid);
}

int
pxCustDelDeliveryList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCustDelDeliveryStartBrowse((tDELAYEDDELIVERYCST*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCustDelDelivery list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxCustDelDelivery :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustDelDelivery *that = (pxCustDelDelivery*)That;

    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
         retval = (CustomerNo_ == that->CustomerNo_) ? 0
                  : (CustomerNo_ > that->CustomerNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustDelDeliveryList :: pxCustDelDeliveryList
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
pxCustDelDeliveryList::SelectForDate
(
    const short  BranchNo,
    const long   CustomerNo,
    const long  PickingDate,
    const short  WeekDay,
    const int     count_
)
{
    tDELAYEDDELIVERYCST fil;
    memset(&fil, 0, sizeof(tDELAYEDDELIVERYCST));  // zero out entire record buffer
    fil.BranchNo = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.WeekDay = WeekDay;
    fil.DateFrom = PickingDate;
    fil.DateTo = PickingDate;
    int cursorid = cCRDELDELIVERYCST_USETOURMANAGER_DATE_2;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}


/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustDelDeliveryList :: Select
(
    const short  BranchNo,
    const long   CustomerNo,
    const short  WeekDay,
    const bool   withTransportExclusion,
    const int     count_
)
{
    tDELAYEDDELIVERYCST fil;
    memset(&fil, 0, sizeof(tDELAYEDDELIVERYCST));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.WeekDay    = WeekDay;
    int cursorid    = cCRDELDELIVERYCST_NOTUSETOURMANAGER_2;
    if ( withTransportExclusion )
    {
       cursorid    = cCRDELDELIVERYCST_USETOURMANAGER_2;
    }
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustDelDeliveryList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCustDelDelivery' object:
    pxCustDelDelivery *objectp = new pxCustDelDelivery(Session(), *(tDELAYEDDELIVERYCST*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  getDelayedDeliveryForDate                                                 */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery* pxCustDelDeliveryList::getDelayedDeliveryForDate(const short BranchNo, const long CustomerNo, const long PickingDate, const short WeekDay, pxArtBase* article)
{
    this->SelectForDate(BranchNo, CustomerNo, PickingDate, WeekDay); // TourManager 2 mit Transportausschluss: Nur Sätze mit IDF=0 sind gültig!
    if (Entries() == 0) return NULL;

    pxCustDelDelivery* custdel = NULL;
    pxCustDelDeliveryListIter listiter(*this);
    while (NULL != (custdel = (pxCustDelDelivery*)(++listiter)))
    {
        if (custdel->isValidForArticle(article))
        {
            return custdel;
        }
    }
    return NULL;
}

/*----------------------------------------------------------------------------*/
/*  getDelayedDelivery                                                        */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery* pxCustDelDeliveryList::getDelayedDelivery(
    const short BranchNo, const long CustomerNo, const short WeekDay,
    const bool withTransportExclusion, pxArtBase* article)
{
    this->Select(BranchNo, CustomerNo, WeekDay, withTransportExclusion); // TourManager 2 mit Transportausschluss: Nur Sätze mit IDF=0 sind gültig!
    if( Entries() == 0 ) return NULL;

    pxCustDelDelivery* custdel = NULL;
    pxCustDelDeliveryListIter listiter(*this);
    while( NULL != (custdel = (pxCustDelDelivery*)(++listiter)) )
    {
        if( custdel->isValidForArticle(article) )
        {
            return custdel;
        }
    }
    return NULL;
}

/*----------------------------------------------------------------------------*/
/*  isValidForArticle                                                         */
/*----------------------------------------------------------------------------*/
bool pxCustDelDelivery::isValidForArticle( pxArtBase* article ) const
{
    if( this->IsColdChain() && article->ArtFlags().IsKuehlKette() ) return true;
    if( this->IsCool08()    && article->ArtFlags().IsGekuehlt08() ) return true;
    if( this->IsCool20()	&& article->ArtFlags().IsGekuehlt20() ) return true;
    if( this->IsNarCotic()	&& article->ArtClass().IsOpiat()      ) return true;
    return false;
}

///*----------------------------------------------------------------------------*/
///*  delayDeliveryDespiteEmergencyService									  */
///*----------------------------------------------------------------------------*/
//bool pxCustDelDelivery::delayDeliveryDespiteEmergencyService(const short branchno, const long customerno, pxArtBase* article) const
//{
//	// Prüfung ob der Kunde heute Notdienst hat und der Artikel trotzdem verzögert werden soll!
//	// Prüfung hier falsch!
//	/*
//	EmergencyService esvc( this->Session(), branchno, customerno );
//	if( esvc.Get() )
//	{
//		if( !esvc.delayDeliveryForArticle(article) )
//		{
//			return false;
//		}
//	}
//	*/
//	return true;
//}

