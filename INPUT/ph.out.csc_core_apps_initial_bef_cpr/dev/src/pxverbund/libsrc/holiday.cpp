/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxHoliDay  methods.

REVISION HISTORY

16 May 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxholiday.hpp"
#include <pxdbxx.h>
#include <date.hpp>
#include "pxsess.hpp"
#include "pxholidaydef.h"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxHoliDay :: pxHoliDay
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
pxHoliDay :: pxHoliDay
(
    pxHoliDay& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tFEIERTAG structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxHoliDay :: pxHoliDay
(
    pxSession   *session,
    tFEIERTAG& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  "Copy" constructor using a pointer to the source rather than a reference. */
/*  NULL pointer safe.                                                        */
/*----------------------------------------------------------------------------*/
pxHoliDay :: pxHoliDay
(
    pxSession *session,
    const pxHoliDay  *srcp
)
    : pxDBRecord(session)
{
    Init();
    if (srcp != NULL)
       (*this) = *srcp;
}
/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxHoliDay :: pxHoliDay
(
    pxSession    *session,
    const short        FilialNr,            // Branchnumber
    const short        Modus,
    const short        Tag
)
    : pxDBRecord(session)
{
    Init();
    FilialNr_    = FilialNr;
    Modus_       = Modus;
    Tag_         = Tag;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxHoliDay :: ~pxHoliDay()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tFEIERTAG structure.       */
/*----------------------------------------------------------------------------*/
tFEIERTAG&
Assign
(
    tFEIERTAG&           dest,
    const pxHoliDay&     src
)
{
    dest.FilialNr     = src.FilialNr_;
    dest.Modus        = src.Modus_   ;
    dest.Tag          = src.Tag_     ;
    dest.Von_Jahr     = src.Von_Jahr_;
    dest.Bis_Jahr     = src.Bis_Jahr_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tFEIERTAG structure to                     */
/*  a pxHoliDay object.                                                       */
/*----------------------------------------------------------------------------*/
pxHoliDay&
Assign
(
    pxHoliDay&              dest,
    const tFEIERTAG&         src
)
{
    dest.FilialNr_    = src.FilialNr;
    dest.Modus_       = src.Modus   ;
    dest.Tag_         = src.Tag     ;
    dest.Von_Jahr_    = src.Von_Jahr;
    dest.Bis_Jahr_    = src.Bis_Jahr;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxHoliDay :: Init()
{
    tFEIERTAG    record;
    memset(&record, 0 , sizeof(tFEIERTAG));
    Assign(*this, record);
    Datum_ = 0;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tFEIERTAG struct and then imported to self.                               */
/*----------------------------------------------------------------------------*/
pxHoliDay&
pxHoliDay :: operator=( const pxHoliDay& src)
{
    tFEIERTAG record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tFEIERTAG structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxHoliDay&
pxHoliDay :: operator=( const tFEIERTAG& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxHoliDay :: Get
(
    DBAccessMode mode
)

{
    tFEIERTAG record;
    memset(&record, 0, sizeof(tFEIERTAG));
    record.FilialNr    = FilialNr_;
    record.Modus       = Modus_   ;
    record.Tag         = Tag_     ;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tFEIERTAG struct
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
pxHoliDay :: Put
(
)
{
    tFEIERTAG record;
    memset(&record, 0, sizeof(tFEIERTAG));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tFEIERTAG));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxHoliDay :: Delete
(
)
{
    tFEIERTAG record;
    memset(&record, 0, sizeof(tFEIERTAG));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxHoliDay :: Read
(
    const void  *record
)
{
    return pxHoliDayRead((tFEIERTAG*)record);
}

int
pxHoliDay :: ReadLock
(
    const void  *record
)
{
    return pxHoliDayReadLock((tFEIERTAG*)record);
}

int
pxHoliDay :: Update
(
    const void  *record
)
{
    return pxHoliDayUpdate((tFEIERTAG*)record);
}

int
pxHoliDay :: Delete
(
    const void  *record
)
{
    return pxHoliDayDelete((tFEIERTAG*)record);
}

int
pxHoliDay :: Insert
(
    const void  *record
)
{
    return pxHoliDayInsert((tFEIERTAG*)record);
}

int
pxHoliDayList :: EndBrowse
(
    const int  cursorid
)
{
    return pxHoliDayEndBrowse(cursorid);
}


int
pxHoliDayList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxHoliDayGetNext((tFEIERTAG*)record, cursorid);
}

int
pxHoliDayList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxHoliDayStartBrowse((tFEIERTAG*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxHoliDay list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxHoliDay :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxHoliDay *that = (pxHoliDay*)That;

    int retval = (FilialNr_ == that->FilialNr_) ? 0
                : (FilialNr_ > that->FilialNr_ ? 1 : -1);

    if ( retval == 0 )
         retval = (Modus_ == that->Modus_) ? 0
                  : (Modus_ > that->Modus_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxHoliDayList :: pxHoliDayList
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
pxHoliDayList :: Select
(
    const short  FilialNr,
    const int     count_
)
{
    tFEIERTAG fil;
    memset(&fil, 0, sizeof(tFEIERTAG));  // zero out entire record buffer
    fil.FilialNr   = FilialNr;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Find entry depend on param                                                */
/*----------------------------------------------------------------------------*/
pxHoliDay*
pxHoliDayList :: Find
(
    const short  Modus,
    const short  Tag,
    const short  VZ
)
{
    pxHoliDayListIter   iter( *this );  // define iterator
    pxHoliDay           *entryp;        // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxHoliDay*) ++iter) != NULL ) // browse list
    {
       if ( (entryp->Modus() == Modus) && (entryp->Tag() == Tag) && (entryp->FilialNr() == VZ) )
          break;
    }
    return   entryp;                        // return entrypointer
}
/*----------------------------------------------------------------------------*/
/*  Find entry depend on param                                                */
/*----------------------------------------------------------------------------*/
pxHoliDay*
pxHoliDayList :: Find
(
    const long  datum,
    const short  VZ
)
{
    pxHoliDayListIter   iter( *this );  // define iterator
    pxHoliDay           *entryp;        // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxHoliDay*) ++iter) != NULL ) // browse list
    {
       if ( (entryp->Datum() == datum)  && (entryp->FilialNr() == VZ) )
          break;
    }
    return   entryp;                        // return entrypointer
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
short
pxHoliDayList :: Find
(
    const short  VZ
)
{
    short BranchNo = 0;
    pxHoliDayListIter   iter( *this );  // define iterator
    pxHoliDay           *entryp;        // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxHoliDay*) ++iter) != NULL ) // browse list
    {
       if ( entryp->FilialNr() == VZ )
       {
          BranchNo = entryp->FilialNr();
          break;
       }
    }
    return   BranchNo;                   // return BranchNumber
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxHoliDayList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxHoliDay' object:
    pxHoliDay *objectp = new pxHoliDay(Session(), *(tFEIERTAG*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Calculate Dates: per entry within the list, the corresponding date will   */
/*  calculated and is placed as a long (YYYYMMDD) into the entry object.      */
/*----------------------------------------------------------------------------*/
int
pxHoliDayList :: CalculateDates
(
)
{
    pxHoliDayListIter   iter( *this );      // define iterator
    pxHoliDay           *entryp;            // pointer to listentry
    nDate now;                              // current date
    long cYear          = now.GetYear();   // current Year
    long cMonth         = now.GetMonth();  // current Month

    // unused variable
    /* long cDay           = */ now.GetDay();    // current Day

    long eMonth         = 0;               // month from entryp TAG
    long eDay           = 0;               // day from entryp TAG
    long DayOfWeek      = 0;               // day of week on Fexible entries
    long CntDayOfWeek   = 0;               // Count how many within month
    long nYear          = 0;               // next year
    nDate EasterSunday(now.GetEasterYYYYMMDD(now.GetYear()));


    iter.Reset();                           // top of list
    while ( ( entryp = ( pxHoliDay*) ++iter) != NULL ) // browse list
    {
        if ( entryp->Datum_ > 0 )      // already set
           continue;

        // check for guilty entry
        if ( entryp->Von_Jahr_ > 0 && entryp->Bis_Jahr_ > 0)
        {
            if ( cYear > entryp->Bis_Jahr_ )
                continue;
        }

        switch (entryp->Modus_ )
        {

/*----------------------------------------------------------------------------*/
/*         Those are entries where the holiday is fix on every year           */
/*         p.e new years day, first and second christmas day etc              */
/*         The mint of TAG within entry: MMDD                                 */
/*----------------------------------------------------------------------------*/
           case cHOL_FIX_MODUS    :
           {
              eMonth = (entryp->Tag_)/100;
              eDay   = (entryp->Tag_)%100;
              if ( cMonth > eMonth )    // just for looking forward
                  nYear +=1;

              entryp->Datum_ = ((cYear+nYear)*10000)+(eMonth*100)+eDay;
              nYear = 0;
              break;
           }

/*----------------------------------------------------------------------------*/
/*         Those are entries which depend on Eastesunday.                     */
/*         p.e Good Friday, Ascension day, Withsun etc                        */
/*         The mint of TAG within entry: CC = count of days before or after   */
/*         Eastersunday                                                       */
/*----------------------------------------------------------------------------*/
           case cHOL_NONFIX_MODUS    :
           {
              if ( entryp->Tag_ == cHOL_EASTERSUN_DAY )        // TAG == 0
              {
                  entryp->Datum_ = EasterSunday.GetYYYYMMDD();
              }
              else
              if ( entryp->Tag_ == cHOL_GOODFRI_DAY )          // TAG == -2
              {
                  entryp->Datum_ = (EasterSunday+cHOL_GOODFRI_DAY).GetYYYYMMDD();
              }
              else
              if ( entryp->Tag_ == cHOL_EASTERMON_DAY )        // TAG == 1
              {
                  entryp->Datum_ = (EasterSunday+cHOL_EASTERMON_DAY).GetYYYYMMDD();
              }
              else
              if ( entryp->Tag_ == cHOL_ASCENSION_DAY )        // TAG == 39
              {
                  entryp->Datum_ = (EasterSunday+cHOL_ASCENSION_DAY).GetYYYYMMDD();
              }
              else
              if ( entryp->Tag_ == cHOL_WITHSUN_DAY )          // TAG == 49
              {
                  entryp->Datum_ = (EasterSunday+cHOL_WITHSUN_DAY).GetYYYYMMDD();
              }
              else
              if ( entryp->Tag_ == cHOL_WITHMON_DAY )          // TAG == 50
              {
                  entryp->Datum_ = (EasterSunday+cHOL_WITHMON_DAY).GetYYYYMMDD();
                          }
              else
              if ( entryp->Tag_ == cHOL_CORPUS_CHRISTI_DAY )   // TAG == 60
              {
                  entryp->Datum_ = (EasterSunday+cHOL_CORPUS_CHRISTI_DAY).GetYYYYMMDD();
              }
              break;
           }

/*----------------------------------------------------------------------------*/
/*         Those are entries which are flexible, like Buss und Bettag         */
/*         The mint of TAG within entry: MMCD, where MM = the month,          */
/*         C = the how maniest D wihin this month.                            */
/*         p.E  1142 means, the fourth's Wednesday within November            */
/*         Remarks: take care of the 2 within this entry, because the         */
/*         serviceprogram for this table starts with monday as the first      */
/*         day of week == 0 and that is officialy wrong, because all standard */
/*         library functions are starting with  zero as Sunday                */
/*----------------------------------------------------------------------------*/
           case cHOL_FLEXIBLE_MODUS  :
           {
              eMonth        = (entryp->Tag_)/100;        // p.e 11
              eDay          = (entryp->Tag_)%100;        // p.e 42
              CntDayOfWeek  = eDay/10;                   // p.e 4
              DayOfWeek     = (eDay%10+1);               // p.e 2(+1) == Wednesday
              nDate fDayOfMonth((cYear*10000)+(eMonth*100)+1); // the first of 11
              long fDow    = fDayOfMonth.GetDayOfWeek(); // Get day of week of that day
              if ( fDow == DayOfWeek)                     // if it is a wednesday
              {
                 fDayOfMonth = fDayOfMonth+(7*( CntDayOfWeek-1));  // first of month + (7*4)
              }
              else
              if ( fDow < DayOfWeek)                      // its a day before wednesday
              {
                 fDayOfMonth = fDayOfMonth+( DayOfWeek-fDow)+ (7*( CntDayOfWeek-1));
              }
              else                                        // its a day after wednesday
              {
                 fDayOfMonth = fDayOfMonth+(7-(fDow-DayOfWeek))+(7*( CntDayOfWeek-1));
              }
              entryp->Datum_ = fDayOfMonth.GetYYYYMMDD();
              break;
           }
        }
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/*  CheckDateForHoliday: a given nDate object is checked for holiday          */
/*  depend on entries within the table FEIERTAG and the known holidays like   */
/*  Eastern, Christmas etc.                                                   */
/*  Returnvalues: True if date is a holiday, otherwise False                  */
/*----------------------------------------------------------------------------*/
bool
pxHoliDayList :: CheckDateForHoliday
(
    const nDate& date,
    const short VZ
)
{
    if ( Entries() )
    {
      long cdate = date.GetYYYYMMDD();    // format YYYYMMDD
      pxHoliDay* holiday = Find(cdate, VZ);
      if (holiday != NULL)
      {
          return true;
      }
    }
    return false;
}
/*----------------------------------------------------------------------------*/
/*  CalculateNextWorkDay: a given nDate object is checked for holiday         */
/*  depend on entries within the table FEIERTAG and the known holidays like   */
/*  Eastern, Christmas etc.                                                   */
/*  Returnvalues: True if date is a holiday, otherwise False                  */
/*----------------------------------------------------------------------------*/
long
pxHoliDayList  :: CalculateNextWorkDay

(
    const nDate& date,
    const short VZ
)
{
    long NextWorkDay = 0;
    nDate nextday = date+1;
    for (;;)
    {
       if ( !CheckDateForHoliday(nextday, VZ) )
       {
          break;
       }
       nextday = nextday+1;
    }
    if ( nextday.GetDayOfWeek() == 0 )    // Sunday
       nextday = nextday+1;

    NextWorkDay = nextday.GetYYYYMMDD();
    return NextWorkDay;
}

