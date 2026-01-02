/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxPromotionScalecale methods.

REVISION HISTORY

20 March 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxpromotionscale.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxPromotionScale :: pxPromotionScale
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
pxPromotionScale :: pxPromotionScale
(
    pxPromotionScale& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tPROMOTIONSCALE structure to construct this instance.                 */
/*----------------------------------------------------------------------------*/
pxPromotionScale :: pxPromotionScale
(
    pxSession   *session,
    tPROMOTIONSCALE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPromotionScale :: pxPromotionScale
(
    pxSession *session,
   const pxPromotionScale *src
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
pxPromotionScale :: pxPromotionScale
(
    pxSession *session,
    const short    PromotionNo,               // Promotion Number
    DBAccessMode /*mode*/
)
    : pxDBRecord(session)
{
    Init();
    PromotionNo_ = PromotionNo;
   //et(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxPromotionScale :: ~pxPromotionScale()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tPROMOTIONSCALE structure.     */
/*----------------------------------------------------------------------------*/
tPROMOTIONSCALE&
Assign
(
    tPROMOTIONSCALE&           dest,
    const pxPromotionScale&       src
)
{
    dest.BasePromotion            = src.BasePromotion_  ;
    dest.Promotion_No             = src.PromotionNo_    ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tPROMOTIONSCALE structure to               */
/*  a pxPromotionScale object.                                                */
/*----------------------------------------------------------------------------*/
pxPromotionScale&
Assign
(
    pxPromotionScale&              dest,
    const tPROMOTIONSCALE&    src
)
{
    dest.BasePromotion_            = src.BasePromotion  ;
    dest.PromotionNo_              = src.Promotion_No    ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxPromotionScale :: Init()
{
    tPROMOTIONSCALE    record;
    memset(&record, 0 , sizeof(tPROMOTIONSCALE));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tPROMOTIONSCALE struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxPromotionScale&
pxPromotionScale :: operator=( const pxPromotionScale& src)
{
    tPROMOTIONSCALE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tPROMOTIONSCALE structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxPromotionScale&
pxPromotionScale :: operator=( const tPROMOTIONSCALE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxPromotionScale list objects being inserted in the               */
/*  following ascending sequence:                                             */
/*----------------------------------------------------------------------------*/
int
pxPromotionScale :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxPromotionScale *that = (pxPromotionScale*)That;
    int retval = (BasePromotion_ == that->BasePromotion_) ? 0
                : (BasePromotion_ > that->BasePromotion_ ? 1 : -1);


    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxPromotionScale :: Get
(
    DBAccessMode mode
)

{
    tPROMOTIONSCALE record;
    memset(&record, 0, sizeof(tPROMOTIONSCALE));
    record.BasePromotion  = BasePromotion_;
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
pxPromotionScale :: Put
(
)
{
    tPROMOTIONSCALE record;
    memset(&record, 0, sizeof(tPROMOTIONSCALE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tPROMOTIONSCALE));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxPromotionScale :: Delete
(
)
{
    tPROMOTIONSCALE record;
    memset(&record, 0, sizeof(tPROMOTIONSCALE));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxPromotionScale :: Read
(
    const void  *record
)
{
    return pxPromotionScaleRead((tPROMOTIONSCALE*)record);
}

int
pxPromotionScale :: ReadLock
(
    const void  *record
)
{
    return pxPromotionScaleReadLock((tPROMOTIONSCALE*)record);
}

int
pxPromotionScale :: Update
(
    const void  *record
)
{
    return pxPromotionScaleUpdate((tPROMOTIONSCALE*)record);
}

int
pxPromotionScale :: Delete
(
    const void  *record
)
{
    return pxPromotionScaleDelete((tPROMOTIONSCALE*)record);
}

int
pxPromotionScale :: Insert
(
    const void  *record
)
{
    return pxPromotionScaleInsert((tPROMOTIONSCALE*)record);
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPromotionScaleList :: pxPromotionScaleList
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
pxPromotionScaleList :: Select
(
    const int     count_
)
{
    tPROMOTIONSCALE fil;
    memset(&fil, 0, sizeof(tPROMOTIONSCALE));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via Promotion Number                          */
/*----------------------------------------------------------------------------*/
size_t
pxPromotionScaleList :: Select
(
    const short    PromotionNo,
    const int     count_
)
{
    tPROMOTIONSCALE fil;
    memset(&fil, 0, sizeof(tPROMOTIONSCALE));  // zero out entire record buffer
    fil.Promotion_No   = PromotionNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BasePromotion Number                      */
/*----------------------------------------------------------------------------*/
size_t
pxPromotionScaleList :: Select
(
    const long    BasePromotion,
    const int     count_
)
{
    tPROMOTIONSCALE fil;
    memset(&fil, 0, sizeof(tPROMOTIONSCALE));  // zero out entire record buffer
    fil.BasePromotion   = BasePromotion;
    int cursorid = cCRS_BASEPROMOTION;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxPromotionScaleList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxPromotionScale' object:
    pxPromotionScale *objectp = new pxPromotionScale(Session(), *(tPROMOTIONSCALE*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxPromotionScaleList :: EndBrowse
(
    const int  cursorid
)
{
    return pxPromotionScaleEndBrowse(cursorid);
}


int
pxPromotionScaleList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxPromotionScaleGetNext((tPROMOTIONSCALE*)record, cursorid);
}

int
pxPromotionScaleList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxPromotionScaleStartBrowse((tPROMOTIONSCALE*)keys, cursorid);
}
