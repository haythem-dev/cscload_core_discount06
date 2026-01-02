#include "pxcstprint.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCstPrint :: pxCstPrint
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
pxCstPrint :: pxCstPrint
(
    pxCstPrint& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCSTPRINT structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxCstPrint :: pxCstPrint
(
    pxSession   *session,
    tCSTPRINT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstPrint :: pxCstPrint
(
    pxSession *session,
   const pxCstPrint *src
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
pxCstPrint :: pxCstPrint
(
    pxSession    *session,
    short        BranchNo,            // Branchnumber
    long         CustomerNo,          // Customernumber
    PriceTypeEnum PreisTyp             // Preistyp

)
    : pxDBRecord(session)
{
    Init();
    BranchNo_    = BranchNo;
    CustomerNo_  = CustomerNo;
    PreisTyp_    = PreisTyp;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCstPrint :: ~pxCstPrint()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCSTPRINT structure.         */
/*----------------------------------------------------------------------------*/
tCSTPRINT&
Assign
(
    tCSTPRINT&           dest,
    const pxCstPrint&       src
)
{
    dest.BranchNo                 = src.BranchNo_              ;
    dest.CustomerNo               = src.CustomerNo_            ;
    dest.Preis_Typ                = static_cast<short>(src.PreisTyp_);
    dest.Deduction_Aep            = src.DeductionAep_          ;
    dest.Deduction_Avp            = src.DeductionAvp_          ;
    dest.Print                    = src.Print_                 ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCSTPRINT structure to                   */
/*  a pxCstPrint object.                                                    */
/*----------------------------------------------------------------------------*/
pxCstPrint&
Assign
(
    pxCstPrint&              dest,
    const tCSTPRINT&    src
)
{
    dest.BranchNo_                 = src.BranchNo              ;
    dest.CustomerNo_               = src.CustomerNo            ;
    dest.PreisTyp_                 = static_cast<PriceTypeEnum>(src.Preis_Typ);
    dest.DeductionAep_             = src.Deduction_Aep         ;
    dest.DeductionAvp_             = src.Deduction_Avp         ;
    dest.Print_                    = src.Print                 ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCstPrint :: Init()
{
    tCSTPRINT    record;
    memset(&record, 0 , sizeof(tCSTPRINT));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCSTPRINT struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxCstPrint&
pxCstPrint :: operator=( const pxCstPrint& src)
{
    tCSTPRINT record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCSTPRINT structure 'src' to                   */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCstPrint&
pxCstPrint :: operator=( const tCSTPRINT& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCstPrint list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                       */
/*----------------------------------------------------------------------------*/
int
pxCstPrint :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxCstPrint *that = (pxCstPrint*)That;
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
pxCstPrintList :: pxCstPrintList
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
pxCstPrintList :: Select
(
    const int     count_
)
{
    tCSTPRINT fil;
    memset(&fil, 0, sizeof(tCSTPRINT));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxCstPrintList :: Select
(
    const short   BranchNo,
    const long    CustomerNo,
    const int     count_
)
{
    tCSTPRINT fil;
    memset(&fil, 0, sizeof(tCSTPRINT));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCstPrintList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCstPrint' object:
    pxCstPrint *objectp = new pxCstPrint(Session(), *(tCSTPRINT*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/* Find returns a pxCstPrint pointer to the corresponding entry depend on     */
/* pricetype. If entry is not found within the list, so NULLP will be returned*/
/*----------------------------------------------------------------------------*/
pxCstPrint*
pxCstPrintList :: Find
(
    const PriceTypeEnum PriceTyp          // Search for this type and
)
{
    pxCstPrintListIter   iter( *this );  // define iterator
    pxCstPrint          *entryp;         // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxCstPrint*) ++iter) != NULL ) // browse list
    {
       if ( entryp->PreisTyp() == PriceTyp )
          break;
    }
    return   entryp;                        // return entrypointer
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCstPrint :: Get
(
    DBAccessMode mode
)

{
    tCSTPRINT record;
    memset(&record, 0, sizeof(tCSTPRINT));
    record.BranchNo   = BranchNo_;
    record.CustomerNo = CustomerNo_;
    record.Preis_Typ  = static_cast<short>(PreisTyp_);
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
pxCstPrint :: Put
(
)
{
    tCSTPRINT record;
    memset(&record, 0, sizeof(tCSTPRINT));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCSTPRINT));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCstPrint :: Delete
(
)
{
    tCSTPRINT record;
    memset(&record, 0, sizeof(tCSTPRINT));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCstPrint :: Read
(
    const void  *record
)
{
    return pxCstPrintRead((tCSTPRINT*)record);
}

int
pxCstPrint :: ReadLock
(
    const void  *record
)
{
    return pxCstPrintReadLock((tCSTPRINT*)record);
}

int
pxCstPrint :: Update
(
    const void  *record
)
{
    return pxCstPrintUpdate((tCSTPRINT*)record);
}

int
pxCstPrint :: Delete
(
    const void  *record
)
{
    return pxCstPrintDelete((tCSTPRINT*)record);
}

int
pxCstPrint :: Insert
(
    const void  *record
)
{
    return pxCstPrintInsert((tCSTPRINT*)record);
}

int
pxCstPrintList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCstPrintEndBrowse(cursorid);
}


int
pxCstPrintList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxCstPrintGetNext((tCSTPRINT*)record, cursorid);
}

int
pxCstPrintList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCstPrintStartBrowse((tCSTPRINT*)keys, cursorid);
}
