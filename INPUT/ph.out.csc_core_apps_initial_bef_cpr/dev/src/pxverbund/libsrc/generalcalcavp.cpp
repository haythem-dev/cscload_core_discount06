#include "pxgeneralcalcavp.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvp :: pxGeneralCalcAvp
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
pxGeneralCalcAvp :: pxGeneralCalcAvp
(
    pxGeneralCalcAvp& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tGENERALCALCAVP structure to construct this instance.             */
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvp :: pxGeneralCalcAvp
(
    pxSession   *session,
    tGENERALCALCAVP& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvp :: pxGeneralCalcAvp
(
    pxSession    *session,
    const short   PriceGroup,         
    const PriceTypeEnum   PreisTyp
)
    : pxDBRecord(session)
{
    Init();
    PriceGroup_      = PriceGroup;
    PreisTyp_        = PreisTyp;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvp :: ~pxGeneralCalcAvp()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tGENERALCALCAVP structure.     */
/*----------------------------------------------------------------------------*/
tGENERALCALCAVP&
Assign
(
    tGENERALCALCAVP&           dest,
    const pxGeneralCalcAvp&     src
)
{
    dest.Price_Group             = src.PriceGroup_             ;
    dest.PercentPreScript        = src.PercentPreScript_       ;
    dest.PercentNoPerScript      = src.PercentNoPerScript_     ;
    dest.PreisTyp                = static_cast<short>(src.PreisTyp_);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tGENERALCALCAVP structure to               */
/*  a pxGeneralCalcAvp object.                                                */
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvp&
Assign
(
    pxGeneralCalcAvp&              dest,
    const tGENERALCALCAVP&         src
)
{
    dest.PriceGroup_              = src.Price_Group            ;
    dest.PercentPreScript_        = src.PercentPreScript       ;
    dest.PercentNoPerScript_      = src.PercentNoPerScript     ;
    dest.PreisTyp_                = static_cast<PriceTypeEnum>(src.PreisTyp);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxGeneralCalcAvp :: Init()
{
    tGENERALCALCAVP    record;
    memset(&record, 0 , sizeof(tGENERALCALCAVP));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tGENERALCALCAVP struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvp&
pxGeneralCalcAvp :: operator=( const pxGeneralCalcAvp& src)
{
    tGENERALCALCAVP record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tGENERALCALCAVP structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvp&
pxGeneralCalcAvp :: operator=( const tGENERALCALCAVP& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxGeneralCalcAvp :: Get
(
    DBAccessMode mode
)

{
    tGENERALCALCAVP record;
    memset(&record, 0, sizeof(tGENERALCALCAVP));
    record.Price_Group    = PriceGroup_ ;
    record.PreisTyp       = static_cast<short>(PreisTyp_);

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tGENERALCALCAVP struct
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
pxGeneralCalcAvp :: Put
(
)
{
    tGENERALCALCAVP record;
    memset(&record, 0, sizeof(tGENERALCALCAVP));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tGENERALCALCAVP));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxGeneralCalcAvp :: Delete
(
)
{
    tGENERALCALCAVP record;
    memset(&record, 0, sizeof(tGENERALCALCAVP));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxGeneralCalcAvp :: Read
(
    const void  *record
)
{
    return pxGeneralCalcAvpRead((tGENERALCALCAVP*)record);
}

int
pxGeneralCalcAvp :: ReadLock
(
    const void  *record
)
{
    return pxGeneralCalcAvpReadLock((tGENERALCALCAVP*)record);
}

int
pxGeneralCalcAvp :: Update
(
    const void  *record
)
{
    return pxGeneralCalcAvpUpdate((tGENERALCALCAVP*)record);
}

int
pxGeneralCalcAvp :: Delete
(
    const void  *record
)
{
    return pxGeneralCalcAvpDelete((tGENERALCALCAVP*)record);
}

int
pxGeneralCalcAvp :: Insert
(
    const void  *record
)
{
    return pxGeneralCalcAvpInsert((tGENERALCALCAVP*)record);
}

int
pxGeneralCalcAvpList :: EndBrowse
(
    const int  cursorid
)
{
    return pxGeneralCalcAvpEndBrowse(cursorid);
}


int
pxGeneralCalcAvpList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxGeneralCalcAvpGetNext((tGENERALCALCAVP*)record, cursorid);
}

int
pxGeneralCalcAvpList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxGeneralCalcAvpStartBrowse((tGENERALCALCAVP*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxGeneralCalcAvp list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxGeneralCalcAvp :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxGeneralCalcAvp *that = (pxGeneralCalcAvp*)That;

    int retval = (PriceGroup_ == that->PriceGroup_) ? 0
                : (PriceGroup_ > that->PriceGroup_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvpList :: pxGeneralCalcAvpList
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
pxGeneralCalcAvpList :: Select
(
    const int    count_
)
{
    tGENERALCALCAVP fil;
    memset(&fil, 0, sizeof(tGENERALCALCAVP));  // zero out entire record buffer
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxGeneralCalcAvpList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxGeneralCalcAvp' object:
    pxGeneralCalcAvp *objectp = new pxGeneralCalcAvp(Session(), *(tGENERALCALCAVP*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/* Find returns a pxGeneralCalcAvpList pointer to the corresponding entry depend on     */
/* pricegroup. If entry is not found within the list, so NULLP will be returned*/
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvp*
pxGeneralCalcAvpList :: Find
(
    const short  PriceGroup,         // Search for this Group and
    const PriceTypeEnum PreisTyp            // Search for this Typ and
)
{
    pxGeneralCalcAvpListIter   iter( *this );  // define iterator
    pxGeneralCalcAvp          *entryp;         // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxGeneralCalcAvp*) ++iter) != NULL ) // browse list
    {
       if ( entryp->PriceGroup() == PriceGroup
            && entryp->PreisTyp() == PreisTyp )
          break;
    }
    return   entryp;                        // return entrypointer
}
