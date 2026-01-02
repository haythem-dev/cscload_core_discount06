/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxPromotions methods.

REVISION HISTORY

17 Febr 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxpromotions.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxPromotions :: pxPromotions
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
pxPromotions :: pxPromotions
(
    pxPromotions& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tPROMOTIONS structure to construct this instance.                 */
/*----------------------------------------------------------------------------*/
pxPromotions :: pxPromotions
(
    pxSession   *session,
    tPROMOTIONS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPromotions :: pxPromotions
(
    pxSession *session,
   const pxPromotions *src
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
pxPromotions :: pxPromotions
(
    pxSession *session,
    const short    PromotionNo,               // Promotion Number
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    PromotionNo_ = PromotionNo;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxPromotions :: ~pxPromotions()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tPROMOTIONS structure.         */
/*----------------------------------------------------------------------------*/
tPROMOTIONS&
Assign
(
    tPROMOTIONS&           dest,
    const pxPromotions&       src
)
{
    dest.Promotion_No            = src.PromotionNo_  ;
    dest.Name[0] = ' '                              ;
    src.Name_.GetData(dest.Name)                    ;
    dest.Description[0] = ' '                       ;
    src.Description_.GetData(dest.Description)      ;
        dest.Promotion_Type                     = src.PromotionType_;
    dest.AddOnPromoDiscOk       = src.AddOnPromoDiscOk_;
    dest.AddOnStdDiscOk         = src.AddOnStdDiscOk_;
    dest.Priority               = src.Priority_;
    dest.SNotBySaleseWeb        = src.SNotBySaleseWeb_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tPROMOTIONS structure to                   */
/*  a pxPromotions object.                                                    */
/*----------------------------------------------------------------------------*/
pxPromotions&
Assign
(
    pxPromotions&              dest,
    const tPROMOTIONS&    src
)
{
    dest.PromotionNo_               = src.Promotion_No ;
    dest.Name_                      = src.Name         ;
    dest.Description_               = src.Description  ;
        dest.PromotionType_                     = src.Promotion_Type;
    dest.AddOnPromoDiscOk_          = src.AddOnPromoDiscOk;
    dest.AddOnStdDiscOk_            = src.AddOnStdDiscOk;
    dest.Priority_                  = src.Priority;
    dest.SNotBySaleseWeb_          = src.SNotBySaleseWeb;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxPromotions :: Init()
{
    tPROMOTIONS    record;
    memset(&record, 0 , sizeof(tPROMOTIONS));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tPROMOTIONS struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxPromotions&
pxPromotions :: operator=( const pxPromotions& src)
{
    tPROMOTIONS record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tPROMOTIONS structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxPromotions&
pxPromotions :: operator=( const tPROMOTIONS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxPromotions list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*----------------------------------------------------------------------------*/
int
pxPromotions :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxPromotions *that = (pxPromotions*)That;
    int retval = (PromotionNo_ == that->PromotionNo_) ? 0
                : (PromotionNo_ > that->PromotionNo_ ? 1 : -1);


    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxPromotions :: Get
(
    DBAccessMode mode
)

{
    tPROMOTIONS record;
    memset(&record, 0, sizeof(tPROMOTIONS));
    record.Promotion_No   = PromotionNo_;
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
pxPromotions :: Put
(
)
{
    tPROMOTIONS record;
    memset(&record, 0, sizeof(tPROMOTIONS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tPROMOTIONS));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxPromotions :: Delete
(
)
{
    tPROMOTIONS record;
    memset(&record, 0, sizeof(tPROMOTIONS));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxPromotions :: Read
(
    const void  *record
)
{
    return pxPromotionsRead((tPROMOTIONS*)record);
}

int
pxPromotions :: ReadLock
(
    const void  *record
)
{
    return pxPromotionsReadLock((tPROMOTIONS*)record);
}

int
pxPromotions :: Update
(
    const void  *record
)
{
    return pxPromotionsUpdate((tPROMOTIONS*)record);
}

int
pxPromotions :: Delete
(
    const void  *record
)
{
    return pxPromotionsDelete((tPROMOTIONS*)record);
}

int
pxPromotions :: Insert
(
    const void  *record
)
{
    return pxPromotionsInsert((tPROMOTIONS*)record);
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPromotionsList :: pxPromotionsList
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
pxPromotionsList :: Select
(
    const int     count_
)
{
    tPROMOTIONS fil;
    memset(&fil, 0, sizeof(tPROMOTIONS));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via Promotion Number                          */
/*----------------------------------------------------------------------------*/
size_t
pxPromotionsList :: Select
(
    const short    PromotionNo,
    const int     count_
)
{
    tPROMOTIONS fil;
    memset(&fil, 0, sizeof(tPROMOTIONS));  // zero out entire record buffer
    fil.Promotion_No   = PromotionNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxPromotionsList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxPromotions' object:
    pxPromotions *objectp = new pxPromotions(Session(), *(tPROMOTIONS*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxPromotionsList :: EndBrowse
(
    const int  cursorid
)
{
    return pxPromotionsEndBrowse(cursorid);
}


int
pxPromotionsList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxPromotionsGetNext((tPROMOTIONS*)record, cursorid);
}

int
pxPromotionsList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxPromotionsStartBrowse((tPROMOTIONS*)keys, cursorid);
}
