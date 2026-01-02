/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxTenderHead methods.

REVISION HISTORY

16 Sept 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxtenderhead.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTenderHead :: pxTenderHead
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
pxTenderHead :: pxTenderHead
(
    pxTenderHead& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTENDERHEAD structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxTenderHead :: pxTenderHead
(
    pxSession   *session,
    tTENDERHEAD& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderHead :: pxTenderHead
(
    pxSession *session,
   const pxTenderHead *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
       (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderHead :: pxTenderHead
(
    pxSession    *session,
    long         TenderNo
)
    : pxDBRecord(session)
{
    Init();
    TenderNo_    = TenderNo;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTenderHead :: ~pxTenderHead()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTENDERHEAD structure.         */
/*----------------------------------------------------------------------------*/
tTENDERHEAD&
Assign
(
    tTENDERHEAD&           dest,
    const pxTenderHead&       src
)
{
    dest.TenderNo                 = src.TenderNo_              ;
    dest.TenderType               = src.TenderType_            ;
    dest.ContractNo[0] = ' ';
    src.ContractNo_.GetData(dest.ContractNo);
    dest.BranchNo                 = src.BranchNo_              ;
    dest.CustomerNo               = src.CustomerNo_            ;
    dest.AccBranchNo              = src.AccBranchNo_           ;
    dest.AccCustomerNo            = src.AccCustomerNo_         ;
    dest.DateFrom                 = src.DateFrom_.GetYYYYMMDD();
    dest.DateTo                   = src.DateTo_.GetYYYYMMDD()  ;
    dest.ExceedancePct            = src.ExceedancePct_         ;
    dest.TenderState              = src.TenderState_           ;
    dest.ChangeDate               = src.ChangeDate_.GetYYYYMMDD();
    dest.NameOfUser[0] = ' ';
    src.NameOfUser_.GetData(dest.NameOfUser);
    dest.PharmacyChainNo          = src.PharmacyChainNo_       ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTENDERHEAD structure to                   */
/*  a pxTenderHead object.                                                    */
/*----------------------------------------------------------------------------*/
pxTenderHead&
Assign
(
    pxTenderHead&              dest,
    const tTENDERHEAD&    src
)
{
    dest.TenderNo_                 = src.TenderNo              ;
    dest.TenderType_               = src.TenderType            ;
    dest.ContractNo_               = src.ContractNo            ;
    dest.BranchNo_                 = src.BranchNo              ;
    dest.CustomerNo_               = src.CustomerNo            ;
    dest.AccBranchNo_              = src.AccBranchNo           ;
    dest.AccCustomerNo_            = src.AccCustomerNo         ;
    dest.DateFrom_                 = nDate(src.DateFrom)       ;
    dest.DateTo_                   = nDate(src.DateTo)         ;
    dest.ExceedancePct_            = src.ExceedancePct         ;
    dest.TenderState_              = src.TenderState           ;
    dest.ChangeDate_               = nDate(src.ChangeDate)     ;
    dest.NameOfUser_               = src.NameOfUser            ;
    dest.PharmacyChainNo_          = src.PharmacyChainNo       ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTenderHead :: Init()
{
    tTENDERHEAD    record;
    memset(&record, 0 , sizeof(tTENDERHEAD));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTENDERHEAD struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxTenderHead&
pxTenderHead :: operator=( const pxTenderHead& src)
{
    tTENDERHEAD record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTENDERHEAD structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxTenderHead&
pxTenderHead :: operator=( const tTENDERHEAD& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxTenderHead list objects being inserted in the                */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo                                                      */
/*----------------------------------------------------------------------------*/
int
pxTenderHead :: CompareTo
(
    const nCollectable*  That,
          void*          /*p*/,
    const long           /*lparm*/
)   const

{
    pxTenderHead *that = (pxTenderHead*)That;
    int retval = (TenderNo_ == that->TenderNo_) ? 0
                : (TenderNo_ > TenderNo_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderHeadList :: pxTenderHeadList
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
pxTenderHeadList :: Select
(
    const int     count_
)
{
    tTENDERHEAD fil;
    memset(&fil, 0, sizeof(tTENDERHEAD));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxTenderHeadList :: AddToList
(
    const void  *record,
    const int  /*row*/
)
{
    // construct new 'pxTenderHead' object:
    pxTenderHead *objectp = new pxTenderHead(Session(), *(tTENDERHEAD*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxTenderHead :: Get
(
    DBAccessMode mode
)
{
    tTENDERHEAD record;
    memset(&record, 0, sizeof(tTENDERHEAD));
    record.TenderNo   = TenderNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxTenderHead :: Put
(
)
{
    tTENDERHEAD record;
    memset(&record, 0, sizeof(tTENDERHEAD));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTENDERHEAD));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxTenderHead :: Delete
(
)
{
    tTENDERHEAD record;
    memset(&record, 0, sizeof(tTENDERHEAD));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxTenderHead :: Read
(
    const void  *record
)
{
    return pxTenderHeadRead((tTENDERHEAD*)record);
}

int
pxTenderHead :: ReadLock
(
    const void  *record
)
{
    return pxTenderHeadReadLock((tTENDERHEAD*)record);
}

int
pxTenderHead :: Update
(
    const void  *record
)
{
    return pxTenderHeadUpdate((tTENDERHEAD*)record);
}

int
pxTenderHead :: Delete
(
    const void  *record
)
{
    return pxTenderHeadDelete((tTENDERHEAD*)record);
}

int
pxTenderHead :: Insert
(
    const void  *record
)
{
    return pxTenderHeadInsert((tTENDERHEAD*)record);
}

int
pxTenderHeadList :: EndBrowse
(
    const int  cursorid
)
{
    return pxTenderHeadEndBrowse(cursorid);
}


int
pxTenderHeadList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxTenderHeadGetNext((tTENDERHEAD*)record, cursorid);
}

int
pxTenderHeadList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxTenderHeadStartBrowse((tTENDERHEAD*)keys, cursorid);
}
