/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxCustomerSpecials.
*/

#include "pxcustomerspecials.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustomerSpecials :: pxCustomerSpecials
(
    pxSession *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerSpecials :: pxCustomerSpecials
(
    pxCustomerSpecials& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERSPECIALS structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxCustomerSpecials :: pxCustomerSpecials
(
    pxSession *session,
    tCUSTOMERSPECIALS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerSpecials :: pxCustomerSpecials
(
    pxSession *session,
   const pxCustomerSpecials *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
        (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  read one table entry to construct this instance                           */
/*----------------------------------------------------------------------------*/
pxCustomerSpecials :: pxCustomerSpecials
(
    pxSession *session,
    const short    BranchNo,               // BranchNo
    const long     CustomerNo,             // CustomerNo
    const short    WeekDay,                // CustomerNo
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_   = BranchNo;
    CustomerNo_ = CustomerNo;
    WeekDay_    = WeekDay;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustomerSpecials :: ~pxCustomerSpecials()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCUSTOMERSPECIALS structure    */
/*----------------------------------------------------------------------------*/
tCUSTOMERSPECIALS&
Assign
(
    tCUSTOMERSPECIALS&           dest,
    const pxCustomerSpecials&    src
)
{
    dest.BranchNo             = src.BranchNo_;
    dest.CustomerNo           = src.CustomerNo_;
    dest.UW_IDF               = src.UW_IDF_;
    dest.WeekDay              = src.WeekDay_;
    dest.Activ                = src.Activ_;

    dest.UW_Tour[0] = ' ';
    src.UW_Tour_.GetData(dest.UW_Tour);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCUSTOMERSPECIALS structure to             */
/*  a pxCustomerSpecials object.                                              */
/*----------------------------------------------------------------------------*/
pxCustomerSpecials&
Assign
(
    pxCustomerSpecials&         dest,
    const tCUSTOMERSPECIALS&    src
)
{
    dest.BranchNo_             = src.BranchNo;
    dest.CustomerNo_           = src.CustomerNo;
    dest.UW_IDF_               = src.UW_IDF;
    dest.UW_Tour_              = src.UW_Tour;
    dest.WeekDay_              = src.WeekDay;
    dest.Activ_                = src.Activ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustomerSpecials :: Init()
{
    tCUSTOMERSPECIALS record;
    memset(&record, 0, sizeof(tCUSTOMERSPECIALS));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCUSTOMERSPECIALS struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCustomerSpecials&
pxCustomerSpecials :: operator=( const pxCustomerSpecials& src)
{
    tCUSTOMERSPECIALS record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCUSTOMERSPECIALS structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustomerSpecials&
pxCustomerSpecials :: operator=( const tCUSTOMERSPECIALS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCustomerSpecials list objects being inserted in the             */
/*  following ascending sequence:                                             */
/*----------------------------------------------------------------------------*/
int
pxCustomerSpecials :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxCustomerSpecials *that = (pxCustomerSpecials*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0 : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
        retval = (WeekDay_ == that->WeekDay_) ? 0 : (WeekDay_ > WeekDay_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustomerSpecials :: Get
(
    DBAccessMode mode
)
{
    tCUSTOMERSPECIALS record;
    memset(&record, 0, sizeof(tCUSTOMERSPECIALS));
    record.BranchNo   = BranchNo_;
    record.CustomerNo = CustomerNo_;
    record.WeekDay    = WeekDay_;

    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;        // import the data from tARTICLEQUOTA struct
   /* else if ( retval > cDBXR_NORMAL )
        ExternalCondition(CMsgStream(), CMSG_AQUOT_ENTRY_NOTFOUND, BranchNo_, CustomerNo_, ArticleNo_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int pxCustomerSpecials :: Put()
{
    tCUSTOMERSPECIALS record;
    memset(&record, 0, sizeof(tCUSTOMERSPECIALS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCUSTOMERSPECIALS));
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int pxCustomerSpecials :: Delete()
{
    tCUSTOMERSPECIALS record;
    memset(&record, 0, sizeof(tCUSTOMERSPECIALS));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int pxCustomerSpecials :: Read( const void *record)
{
    return pxCustomerSpecialsRead((tCUSTOMERSPECIALS*)record);
}

int pxCustomerSpecials :: ReadLock( const void *record)
{
    return pxCustomerSpecialsReadLock((tCUSTOMERSPECIALS*)record);
}

int pxCustomerSpecials :: Update( const void *record)
{
    return pxCustomerSpecialsUpdate((tCUSTOMERSPECIALS*)record);
}

int pxCustomerSpecials :: Delete( const void *record)
{
    return pxCustomerSpecialsDelete((tCUSTOMERSPECIALS*)record);
}

int pxCustomerSpecials :: Insert( const void *record)
{
    return pxCustomerSpecialsInsert((tCUSTOMERSPECIALS*)record);
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerSpecialsList :: pxCustomerSpecialsList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t pxCustomerSpecialsList :: Select( const int count_)
{
    tCUSTOMERSPECIALS fil;
    memset(&fil, 0, sizeof(tCUSTOMERSPECIALS));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo CustomerNo                       */
/*----------------------------------------------------------------------------*/
size_t pxCustomerSpecialsList :: Select( const short BranchNo, const long CustomerNo, const int count_)
{
    tCUSTOMERSPECIALS fil;
    memset(&fil, 0, sizeof(tCUSTOMERSPECIALS));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo CustomerNo(First UW_IDF          */
/*----------------------------------------------------------------------------*/
size_t pxCustomerSpecialsList :: SelectFirstUWIDF(const short BranchNo, const long CustomerNo, const int count_)
{
    tCUSTOMERSPECIALS fil;
    memset(&fil, 0, sizeof(tCUSTOMERSPECIALS));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    int cursorid = cCRSCUSTOMERSPECIALS_FIRST_UW_IDF;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo CustomerNo(First UW_IDF          */
/*----------------------------------------------------------------------------*/
size_t pxCustomerSpecialsList :: SelectUWIDF(const short BranchNo, const long UW_IDF, const int count_)
{
    tCUSTOMERSPECIALS fil;
    memset(&fil, 0, sizeof(tCUSTOMERSPECIALS));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.UW_IDF = UW_IDF;
    int cursorid = cCRSCUSTOMERSPECIALS_UW_IDF;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable* pxCustomerSpecialsList :: AddToList( const void *record, const int  /* row */)
{
    // construct new 'pxCustomerSpecials' object:
    pxCustomerSpecials *objectp = new pxCustomerSpecials(Session(), *(tCUSTOMERSPECIALS*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int pxCustomerSpecialsList :: EndBrowse( const int cursorid )
{
    return pxCustomerSpecialsEndBrowse(cursorid);
}


int pxCustomerSpecialsList :: GetNext( const void *record, const int cursorid)
{
    return pxCustomerSpecialsGetNext((tCUSTOMERSPECIALS*)record, cursorid);
}

int pxCustomerSpecialsList :: StartBrowse( const void *keys, const int cursorid)
{
    return pxCustomerSpecialsStartBrowse((tCUSTOMERSPECIALS*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
pxCustomerSpecials* pxCustomerSpecialsList :: FindActivDow( const short dayofweek)
{
    pxCustomerSpecialsListIter cursor(*this);
    pxCustomerSpecials* entryp = NULL;

    while ( (entryp = (pxCustomerSpecials*) ++cursor) != NULL )
    {
        if ( entryp->WeekDay() == dayofweek )
        {
            if ( entryp->IsActiv() )
            {
                break;
            }
        }
    }
    if ( entryp )
    {
        return entryp;
    }

    // now try to find an entry with weekday > today
    cursor.Reset();
    while ( (entryp = (pxCustomerSpecials*) ++cursor) != NULL )
    {
        if ( entryp->WeekDay() >  dayofweek )
        {
            if ( entryp->IsActiv() )
            {
                break;
            }
        }
    }

    if ( entryp )
    {
        return entryp;
    }
    // now find the first valid entry 
    cursor.Reset();
    while ( (entryp = (pxCustomerSpecials*) ++cursor) != NULL )
    {
        if ( entryp->IsActiv() )
        {
            break;
        }
    }
    return entryp;
}
