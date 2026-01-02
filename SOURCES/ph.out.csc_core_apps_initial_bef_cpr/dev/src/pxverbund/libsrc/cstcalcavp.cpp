#include "pxcstcalcavp.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCstCalcAvp :: pxCstCalcAvp
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
pxCstCalcAvp :: pxCstCalcAvp
(
    pxCstCalcAvp& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCSTCALCAVP structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxCstCalcAvp :: pxCstCalcAvp
(
    pxSession   *session,
    tCSTCALCAVP& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstCalcAvp :: pxCstCalcAvp
(
    pxSession *session,
   const pxCstCalcAvp *src
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
pxCstCalcAvp :: pxCstCalcAvp
(
    pxSession    *session,
    short        BranchNo,            // Branchnumber
    long         CustomerNo,          // Customernumber
    short         PriceGroup,
    PriceTypeEnum PreisTyp,
    nString       AbdaCode             // Abdacode

)
    : pxDBRecord(session)
{
    Init();
    BranchNo_    = BranchNo;
    CustomerNo_  = CustomerNo;
    PriceGroup_  = PriceGroup;
    PreisTyp_    = PreisTyp;
    AbdaCode_    = AbdaCode;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCstCalcAvp :: ~pxCstCalcAvp()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCSTCALCAVP structure.         */
/*----------------------------------------------------------------------------*/
tCSTCALCAVP&
Assign
(
    tCSTCALCAVP&           dest,
    const pxCstCalcAvp&       src
)
{
    dest.BranchNo                 = src.BranchNo_              ;
    dest.CustomerNo               = src.CustomerNo_            ;
    dest.AbdaCode[0] = ' ';
    src.AbdaCode_.GetData(dest.AbdaCode);
    dest.Surcharge_Basic          = src.SurchargeBasic_        ;
    dest.Deduction_Basic          = src.DeductionBasic_        ;
    dest.SurchargePct             = src.SurchargePct_          ;
    dest.DeductionPct             = src.DeductionPct_          ;
    dest.PriceGroup               = src.PriceGroup_            ;
    dest.PreisTyp                 = static_cast<short>(src.PreisTyp_);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCSTCALCAVP structure to                   */
/*  a pxCstCalcAvp object.                                                    */
/*----------------------------------------------------------------------------*/
pxCstCalcAvp&
Assign
(
    pxCstCalcAvp&              dest,
    const tCSTCALCAVP&    src
)
{
    dest.BranchNo_                 = src.BranchNo              ;
    dest.CustomerNo_               = src.CustomerNo            ;
    dest.AbdaCode_                 = src.AbdaCode              ;
    dest.SurchargeBasic_           = src.Surcharge_Basic       ;
    dest.DeductionBasic_           = src.Deduction_Basic       ;
    dest.SurchargePct_             = src.SurchargePct          ;
    dest.DeductionPct_             = src.DeductionPct          ;
    dest.PriceGroup_               = src.PriceGroup            ;
    dest.PreisTyp_                 = static_cast<PriceTypeEnum>(src.PreisTyp);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCstCalcAvp :: Init()
{
    tCSTCALCAVP    record;
    memset(&record, 0 , sizeof(tCSTCALCAVP));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCSTCALCAVP struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxCstCalcAvp&
pxCstCalcAvp :: operator=( const pxCstCalcAvp& src)
{
    tCSTCALCAVP record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCSTCALCAVP structure 'src' to                   */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCstCalcAvp&
pxCstCalcAvp :: operator=( const tCSTCALCAVP& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCstCalcAvp list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                       */
/*----------------------------------------------------------------------------*/
int
pxCstCalcAvp :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCstCalcAvp *that = (pxCstCalcAvp*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > BranchNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (CustomerNo_ == that->CustomerNo_) ? 0
              : (CustomerNo_ > CustomerNo_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstCalcAvpList :: pxCstCalcAvpList
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
pxCstCalcAvpList :: Select
(
    const int     count_
)
{
    tCSTCALCAVP fil;
    memset(&fil, 0, sizeof(tCSTCALCAVP));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxCstCalcAvpList :: Select
(
    const short   BranchNo,
    const long    CustomerNo,
    const short   PriceGroup,
    const PriceTypeEnum PreisTyp,
    const int     count_
)
{
    tCSTCALCAVP fil;
    memset(&fil, 0, sizeof(tCSTCALCAVP));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.PriceGroup = PriceGroup;
    fil.PreisTyp   = static_cast<short>(PreisTyp);
    int cursorid  = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCstCalcAvpList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCstCalcAvp' object:
    pxCstCalcAvp *objectp = new pxCstCalcAvp(Session(), *(tCSTCALCAVP*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCstCalcAvp :: Get
(
    DBAccessMode mode
)

{
    tCSTCALCAVP record;
    memset(&record, 0, sizeof(tCSTCALCAVP));
    record.BranchNo   = BranchNo_;
    record.CustomerNo = CustomerNo_;
    record.PriceGroup = PriceGroup_;
    record.PreisTyp   = static_cast<short>(PreisTyp_);
    record.AbdaCode[0] = ' ';
    AbdaCode_.GetData(record.AbdaCode);
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
pxCstCalcAvp :: Put
(
)
{
    tCSTCALCAVP record;
    memset(&record, 0, sizeof(tCSTCALCAVP));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCSTCALCAVP));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCstCalcAvp :: Delete
(
)
{
    tCSTCALCAVP record;
    memset(&record, 0, sizeof(tCSTCALCAVP));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCstCalcAvp :: Read
(
    const void  *record
)
{
    return pxCstCalcAvpRead((tCSTCALCAVP*)record);
}

int
pxCstCalcAvp :: ReadLock
(
    const void  *record
)
{
    return pxCstCalcAvpReadLock((tCSTCALCAVP*)record);
}

int
pxCstCalcAvp :: Update
(
    const void  *record
)
{
    return pxCstCalcAvpUpdate((tCSTCALCAVP*)record);
}

int
pxCstCalcAvp :: Delete
(
    const void  *record
)
{
    return pxCstCalcAvpDelete((tCSTCALCAVP*)record);
}

int
pxCstCalcAvp :: Insert
(
    const void  *record
)
{
    return pxCstCalcAvpInsert((tCSTCALCAVP*)record);
}

int
pxCstCalcAvpList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCstCalcAvpEndBrowse(cursorid);
}


int
pxCstCalcAvpList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxCstCalcAvpGetNext((tCSTCALCAVP*)record, cursorid);
}

int
pxCstCalcAvpList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCstCalcAvpStartBrowse((tCSTCALCAVP*)keys, cursorid);
}
