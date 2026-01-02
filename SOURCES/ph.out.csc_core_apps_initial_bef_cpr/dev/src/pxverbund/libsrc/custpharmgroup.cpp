/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxCustPharmGroup  methods.

REVISION HISTORY

29 June 2004 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxcustpharmgroup.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustPharmGroup :: pxCustPharmGroup
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
pxCustPharmGroup :: pxCustPharmGroup
(
    pxCustPharmGroup& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERPHARMACYGR structure to construct this instance.          */
/*----------------------------------------------------------------------------*/
pxCustPharmGroup :: pxCustPharmGroup
(
    pxSession   *session,
    tCUSTOMERPHARMACYGR& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustPharmGroup :: pxCustPharmGroup
(
    pxSession    *session,
    long        CustomerNo,          // this type
    short       BranchNo,            // Read via this type and
    nString&     PharmacyGroupId
)
    : pxDBRecord(session)
{
    Init();
    CustomerNo_        = CustomerNo;
    BranchNo_          = BranchNo;
    PharmacyGroupId_   = PharmacyGroupId;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustPharmGroup :: ~pxCustPharmGroup()
{
    ;
}

/*----------------------------------------------------------------------------*/
/* Assign the values of the 'src' object to a tCUSTOMERPHARMACYGR structure*/
/*----------------------------------------------------------------------------*/
tCUSTOMERPHARMACYGR&
Assign
(
    tCUSTOMERPHARMACYGR&           dest,
    const pxCustPharmGroup&       src
)
{
    dest.CustomerNo                = src.CustomerNo_                         ;
    dest.BranchNo                  = src.BranchNo_                           ;
    dest.PharmacyGroupId[0] = ' ';
    src.PharmacyGroupId_.GetData(dest.PharmacyGroupId);
    dest.Ranking                   = src.Ranking_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCUSTOMERPHARMACYGR structure to           */
/*  a pxCustPharmGroup object.                                                */
/*----------------------------------------------------------------------------*/
pxCustPharmGroup&
Assign
(
    pxCustPharmGroup&              dest,
    const tCUSTOMERPHARMACYGR&    src
)
{
    dest.BranchNo_                 = src.BranchNo                            ;
    dest.CustomerNo_               = src.CustomerNo                          ;
    dest.PharmacyGroupId_          = src.PharmacyGroupId                     ;
    dest.Ranking_                  = src.Ranking                             ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustPharmGroup :: Init()
{
    tCUSTOMERPHARMACYGR    record;
    memset(&record, 0 , sizeof(tCUSTOMERPHARMACYGR));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCUSTOMERPHARMACYGR struct and then imported to self.                     */
/*----------------------------------------------------------------------------*/
pxCustPharmGroup&
pxCustPharmGroup :: operator=( const pxCustPharmGroup& src)
{
    tCUSTOMERPHARMACYGR record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCUSTOMERPHARMACYGR structure 'src' to        */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustPharmGroup&
pxCustPharmGroup :: operator=( const tCUSTOMERPHARMACYGR& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustPharmGroup :: Get
(
    DBAccessMode mode
)

{
    tCUSTOMERPHARMACYGR record;
    memset(&record, 0, sizeof(tCUSTOMERPHARMACYGR));
    record.BranchNo      = BranchNo_;
    record.CustomerNo    = CustomerNo_;
    record.PharmacyGroupId[0] = ' ';
        PharmacyGroupId_.GetData(record.PharmacyGroupId);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tCUSTOMERPHARMACYGR struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustPharmGroup :: Put
(
)
{
    tCUSTOMERPHARMACYGR record;
    memset(&record, 0, sizeof(tCUSTOMERPHARMACYGR));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCUSTOMERPHARMACYGR));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCustPharmGroup :: Delete
(
)
{
    tCUSTOMERPHARMACYGR record;
    memset(&record, 0, sizeof(tCUSTOMERPHARMACYGR));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustPharmGroup :: Read
(
    const void  *record
)
{
    return pxCustPharmGroupRead((tCUSTOMERPHARMACYGR*)record);
}

int
pxCustPharmGroup :: ReadLock
(
    const void  *record
)
{
    return pxCustPharmGroupReadLock((tCUSTOMERPHARMACYGR*)record);
}

int
pxCustPharmGroup :: Update
(
    const void  *record
)
{
    return pxCustPharmGroupUpdate((tCUSTOMERPHARMACYGR*)record);
}

int
pxCustPharmGroup :: Delete
(
    const void  *record
)
{
    return pxCustPharmGroupDelete((tCUSTOMERPHARMACYGR*)record);
}

int
pxCustPharmGroup :: Insert
(
    const void  *record
)
{
    return pxCustPharmGroupInsert((tCUSTOMERPHARMACYGR*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCustPharmGroup list objects being inserted in the               */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxCustPharmGroup :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustPharmGroup *that = (pxCustPharmGroup*)That;
    int retval = (CustomerNo_ == that->CustomerNo_) ? 0
                : (CustomerNo_ > that->CustomerNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (Ranking_ == that->Ranking_) ? 0
                : (Ranking_ > that->Ranking_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustPharmGroupList :: pxCustPharmGroupList
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
pxCustPharmGroupList :: Select
(
    const int     count_
)
{
    tCUSTOMERPHARMACYGR fil;
    memset(&fil, 0, sizeof(tCUSTOMERPHARMACYGR));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxCustPharmGroupList :: Select
(
    const long    CustomerNo,
    const short   BranchNo,
    const int     count_
)
{
    tCUSTOMERPHARMACYGR fil;
    memset(&fil, 0, sizeof(tCUSTOMERPHARMACYGR));  // zero out entire record buffer
    fil.CustomerNo   = CustomerNo;
    fil.BranchNo     = BranchNo;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustPharmGroupList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCustPharmGroup' object:
    pxCustPharmGroup *objectp = new pxCustPharmGroup(Session(), *(tCUSTOMERPHARMACYGR*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Find entry within the List depend on PharmacyGroupId                      */
/*----------------------------------------------------------------------------*/
pxCustPharmGroup*
pxCustPharmGroupList :: Find
(
    const nString& PharmacyGroupId
)

{
    pxCustPharmGroupListIter iter( *this );  // define iterator
    pxCustPharmGroup           *entryp;      // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxCustPharmGroup*) ++iter) != NULL ) // browse list
    {
        if ( entryp->PharmacyGroupId() == PharmacyGroupId )
        {
            break;
        }
    }
    return entryp;
}

int
pxCustPharmGroupList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCustPharmGroupEndBrowse(cursorid);
}


int
pxCustPharmGroupList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxCustPharmGroupGetNext((tCUSTOMERPHARMACYGR*)record, cursorid);
}

int
pxCustPharmGroupList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCustPharmGroupStartBrowse((tCUSTOMERPHARMACYGR*)keys, cursorid);
}

