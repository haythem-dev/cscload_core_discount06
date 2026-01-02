/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxTenderPos methods.

REVISION HISTORY

17 Sept 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxtenderpos.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTenderPos :: pxTenderPos
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
pxTenderPos :: pxTenderPos
(
    pxTenderPos& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTENDERPOS structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxTenderPos :: pxTenderPos
(
    pxSession   *session,
    tTENDERPOS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderPos :: pxTenderPos
(
    pxSession *session,
   const pxTenderPos *src
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
pxTenderPos :: pxTenderPos
(
    pxSession    *session,
    long         TenderNo,            // TenderNumber
    long         ArticleNo            // Article number

)
    : pxDBRecord(session)
{
    Init();
    TenderNo_    = TenderNo;
    ArticleNo_   = ArticleNo;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTenderPos :: ~pxTenderPos()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTENDERPOS structure.         */
/*----------------------------------------------------------------------------*/
tTENDERPOS&
Assign
(
    tTENDERPOS&           dest,
    const pxTenderPos&       src
)
{
    dest.TenderNo                 = src.TenderNo_              ;
    dest.ArticleNo                = src.ArticleNo_             ;
    dest.ContractQty              = src.ContractQty_           ;
    dest.ContractPrice            = src.ContractPrice_         ;
    dest.RemainingLife            = src.RemainingLife_         ;
    dest.AddDiscountPct           = src.AddDiscountPct_        ;
    dest.Aep                      = src.Aep_                   ;
    dest.TenderState              = src.TenderState_           ;
    dest.ChangeDate               = src.ChangeDate_.GetYYYYMMDD();
    dest.NameOfUser[0] = ' ';
    src.NameOfUser_.GetData(dest.NameOfUser);
    dest.PriceDiff                = src.PriceDiff_        ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTENDERPOS structure to                   */
/*  a pxTenderPos object.                                                    */
/*----------------------------------------------------------------------------*/
pxTenderPos&
Assign
(
    pxTenderPos&              dest,
    const tTENDERPOS&    src
)
{
    dest.TenderNo_                 = src.TenderNo              ;
    dest.ArticleNo_                = src.ArticleNo             ;
    dest.ContractQty_              = src.ContractQty           ;
    dest.ContractPrice_            = src.ContractPrice         ;
    dest.RemainingLife_            = src.RemainingLife         ;
    dest.AddDiscountPct_           = src.AddDiscountPct        ;
    dest.Aep_                      = src.Aep                   ;
    dest.TenderState_              = src.TenderState           ;
    dest.ChangeDate_               = nDate(src.ChangeDate)     ;
    dest.NameOfUser_               = src.NameOfUser            ;
    dest.PriceDiff_                = src.PriceDiff             ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTenderPos :: Init()
{
    tTENDERPOS    record;
    memset(&record, 0 , sizeof(tTENDERPOS));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTENDERPOS struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxTenderPos&
pxTenderPos :: operator=( const pxTenderPos& src)
{
    tTENDERPOS record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTENDERPOS structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxTenderPos&
pxTenderPos :: operator=( const tTENDERPOS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxTenderPos list objects being inserted in the                */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo                                                      */
/*----------------------------------------------------------------------------*/
int
pxTenderPos :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxTenderPos *that = (pxTenderPos*)That;
    int retval = (TenderNo_ == that->TenderNo_) ? 0
                : (TenderNo_ > TenderNo_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderPosList :: pxTenderPosList
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
pxTenderPosList :: Select
(
    const int     count_
)
{
    tTENDERPOS fil;
    memset(&fil, 0, sizeof(tTENDERPOS));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via TenderNo,ArticleNo                        */
/*----------------------------------------------------------------------------*/
size_t
pxTenderPosList :: Select
(
    const long    TenderNo,
    const long    ArticleNo,
    const int     count_
)
{
    tTENDERPOS fil;
    memset(&fil, 0, sizeof(tTENDERPOS));  // zero out entire record buffer
    fil.TenderNo   = TenderNo;
    fil.ArticleNo  = ArticleNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via TenderNo,TenderState                      */
/*  This select searches entries with Tenderstate_ NOT EQUAL to TenderState   */
/*----------------------------------------------------------------------------*/
size_t
pxTenderPosList :: Select
(
    const long    TenderNo,
    const char    TenderState,
    const int     count_
)
{
    tTENDERPOS fil;
    memset(&fil, 0, sizeof(tTENDERPOS));  // zero out entire record buffer
    fil.TenderNo    = TenderNo;
    fil.TenderState = TenderState;
    int cursorid  = cCRTPTENDERNOSTATE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxTenderPosList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxTenderPos' object:
    pxTenderPos *objectp = new pxTenderPos(Session(), *(tTENDERPOS*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxTenderPos :: Get
(
    DBAccessMode mode
)

{
    tTENDERPOS record;
    memset(&record, 0, sizeof(tTENDERPOS));
    record.TenderNo   = TenderNo_;
    record.ArticleNo  = ArticleNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLEQUOTA struct
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
pxTenderPos :: Put
(
)
{
    tTENDERPOS record;
    memset(&record, 0, sizeof(tTENDERPOS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTENDERPOS));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxTenderPos :: Delete
(
)
{
    tTENDERPOS record;
    memset(&record, 0, sizeof(tTENDERPOS));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxTenderPos :: Read
(
    const void  *record
)
{
    return pxTenderPosRead((tTENDERPOS*)record);
}

int
pxTenderPos :: ReadLock
(
    const void  *record
)
{
    return pxTenderPosReadLock((tTENDERPOS*)record);
}

int
pxTenderPos :: Update
(
    const void  *record
)
{
    return pxTenderPosUpdate((tTENDERPOS*)record);
}

int
pxTenderPos :: Delete
(
    const void  *record
)
{
    return pxTenderPosDelete((tTENDERPOS*)record);
}

int
pxTenderPos :: Insert
(
    const void  *record
)
{
    return pxTenderPosInsert((tTENDERPOS*)record);
}

int
pxTenderPosList :: EndBrowse
(
    const int  cursorid
)
{
    return pxTenderPosEndBrowse(cursorid);
}


int
pxTenderPosList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxTenderPosGetNext((tTENDERPOS*)record, cursorid);
}

int
pxTenderPosList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxTenderPosStartBrowse((tTENDERPOS*)keys, cursorid);
}
