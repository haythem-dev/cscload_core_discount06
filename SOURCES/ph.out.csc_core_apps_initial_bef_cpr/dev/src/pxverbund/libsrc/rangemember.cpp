/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxRangeMember methods.

REVISION HISTORY

09 Feb 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxrangemember.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxRangeMember :: pxRangeMember
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
pxRangeMember :: pxRangeMember
(
    pxRangeMember& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tDISCOUNTGRPMEM structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxRangeMember :: pxRangeMember
(
    pxSession   *session,
    tDISCOUNTGRPMEM& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxRangeMember :: pxRangeMember
(
    pxSession    *session,
    short       BranchNo,               // Read via this type and
    long        DiscountGrpNo,          // this type
    long        ArticleNo              // this type
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_         = BranchNo;
    DiscountGrpNo_    = DiscountGrpNo;
    ArticleNo_        = ArticleNo;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxRangeMember :: ~pxRangeMember()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDISCOUNTGRPMEM structure.      */
/*----------------------------------------------------------------------------*/
tDISCOUNTGRPMEM&
Assign
(
    tDISCOUNTGRPMEM&           dest,
    const pxRangeMember&       src
)
{
    dest.BranchNo                  = src.BranchNo_               ;
    dest.DiscountGrpNo             = src.DiscountGrpNo_          ;
    dest.ArticleNo                 = src.ArticleNo_              ;
    dest.DiscountCondition         = src.DiscountCondition_      ;
    dest.ManufacturerNo            = src.ManufacturerNo_         ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDISCOUNTGRPMEM structure to                */
/*  a pxRangeMember object.                                                   */
/*----------------------------------------------------------------------------*/
pxRangeMember&
Assign
(
    pxRangeMember&              dest,
    const tDISCOUNTGRPMEM&    src
)
{
    dest.BranchNo_                  = src.BranchNo               ;
    dest.DiscountGrpNo_             = src.DiscountGrpNo          ;
    dest.ArticleNo_                 = src.ArticleNo              ;
    dest.DiscountCondition_         = src.DiscountCondition      ;
    dest.ManufacturerNo_            = src.ManufacturerNo         ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxRangeMember :: Init()
{
    tDISCOUNTGRPMEM    record;
    memset(&record, 0 , sizeof(tDISCOUNTGRPMEM));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDISCOUNTGRPMEM struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxRangeMember&
pxRangeMember :: operator=( const pxRangeMember& src)
{
    tDISCOUNTGRPMEM record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISCOUNTGRPMEM structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxRangeMember&
pxRangeMember :: operator=( const tDISCOUNTGRPMEM& src)
{
    return Assign(*this, src);
}


/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxRangeMember :: Get
(
    DBAccessMode mode
)

{
    tDISCOUNTGRPMEM record;
    memset(&record, 0, sizeof(tDISCOUNTGRPMEM));
    record.BranchNo          = BranchNo_;
    record.DiscountGrpNo     = DiscountGrpNo_;
    record.ArticleNo         = ArticleNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tDISCOUNTGRPMEM struct
   /* else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_AD_DELPOS_NOTFOUND, KdAuftragNr_,PosNr_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxRangeMember :: Read
(
    const void  *record
)
{
    return pxRangeMemberRead((tDISCOUNTGRPMEM*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeMember list objects being inserted in the                  */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxRangeMember :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxRangeMember *that = (pxRangeMember*)That;
    int retval = (DiscountGrpNo_ == that->DiscountGrpNo_) ? 0
                : (DiscountGrpNo_ > DiscountGrpNo_ ? 1 : -1);

    if ( retval == 0 )
       retval = (ArticleNo_ == that->ArticleNo_) ? 0
                : (ArticleNo_ > that->ArticleNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRangeMemberList :: pxRangeMemberList
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
pxRangeMemberList :: Select
(
    const int     count_
)
{
    tDISCOUNTGRPMEM fil;
    memset(&fil, 0, sizeof(tDISCOUNTGRPMEM));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo and ArticleNo                    */
/*----------------------------------------------------------------------------*/
size_t
pxRangeMemberList :: Select
(
    const short   BranchNo,
    const long    ArticleNo,
    const int     count_
)
{
    tDISCOUNTGRPMEM fil;
    memset(&fil, 0, sizeof(tDISCOUNTGRPMEM));  // zero out entire record buffer
    fil.BranchNo      = BranchNo;
    fil.ArticleNo     = ArticleNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo, ArticleNo and ManufacturerNo    */
/*----------------------------------------------------------------------------*/
size_t
pxRangeMemberList :: Select
(
    const short   BranchNo,
    const long    ArticleNo,
    const long    ManufacturerNo,
    const int     count_
)
{
    tDISCOUNTGRPMEM fil;
    memset(&fil, 0, sizeof(tDISCOUNTGRPMEM));  // zero out entire record buffer
    fil.BranchNo       = BranchNo;
    fil.ArticleNo      = ArticleNo;
    fil.ManufacturerNo = ManufacturerNo;
    int cursorid = cCRSGRPMEM_GRPARTMANUFACTURER;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo, DiscountGrpNo                   */
/*----------------------------------------------------------------------------*/
size_t
pxRangeMemberList :: SelectMembers
(
    const short   BranchNo,
    const long    DiscountGrpNo ,
    const int     count_
)
{
    tDISCOUNTGRPMEM fil;
    memset(&fil, 0, sizeof(tDISCOUNTGRPMEM));  // zero out entire record buffer
    fil.BranchNo      = BranchNo;
    fil.DiscountGrpNo = DiscountGrpNo;
    int cursorid = cCRSGRPMEM_GRPMEMBERS;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo, PosNr                           */
/*----------------------------------------------------------------------------*/
size_t
pxRangeMemberList :: SelectManuFacturer
(
    const short   BranchNo,
    const long    ManufacturerNo ,
    const int     count_
)
{
    tDISCOUNTGRPMEM fil;
    memset(&fil, 0, sizeof(tDISCOUNTGRPMEM));  // zero out entire record buffer
    fil.BranchNo       = BranchNo;
    fil.ManufacturerNo = ManufacturerNo;
    int cursorid = cCRSGRPMEM_GRPMANUFACTURER;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Find: looks for entry depend on ArticleNo and  ManufacturerNo             */
/*----------------------------------------------------------------------------*/
bool
pxRangeMemberList :: Find
(
    const long    ArticleNo,
    const long    ManufacturerNo
)
{
    bool retval = false;
    pxRangeMember*     rm         = NULL;
    pxRangeMemberListIter cursor(*this);        // define an iterator

    while ( (rm = (pxRangeMember*) ++cursor) != NULL )
    {
       if ( (rm->ArticleNo() == ArticleNo) || (rm->ManufacturerNo() == ManufacturerNo) )
       {
          retval = true;
          break;
       }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxRangeMemberList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxRangeMember' object:
    pxRangeMember *objectp = new pxRangeMember(Session(), *(tDISCOUNTGRPMEM*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxRangeMemberList :: EndBrowse
(
    const int  cursorid
)
{
    return pxRangeMemberEndBrowse(cursorid);
}


int
pxRangeMemberList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxRangeMemberGetNext((tDISCOUNTGRPMEM*)record, cursorid);
}

int
pxRangeMemberList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxRangeMemberStartBrowse((tDISCOUNTGRPMEM*)keys, cursorid);
}

