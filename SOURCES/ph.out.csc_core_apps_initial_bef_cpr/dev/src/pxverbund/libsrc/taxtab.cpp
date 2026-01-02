#include "pxtaxtab.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTaxTab :: pxTaxTab
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
pxTaxTab :: pxTaxTab
(
    pxTaxTab& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTAXTAB structure to construct this instance.          */
/*----------------------------------------------------------------------------*/
pxTaxTab :: pxTaxTab
(
    pxSession   *session,
    tTAXTAB& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTaxTab :: ~pxTaxTab()
{
    ;
}

/*----------------------------------------------------------------------------*/
/* Assign the values of the 'src' object to a tTAXTAB structure*/
/*----------------------------------------------------------------------------*/
tTAXTAB&
Assign
(
    tTAXTAB&           dest,
    const pxTaxTab&       src
)
{
    dest.TaxArt                  = src.TaxArt_;
    dest.TaxVonDm                  = src.TaxVonDm_;
    dest.TaxProz                   = src.TaxProz_;
    dest.TaxBetrag                   = src.TaxBetrag_;
    dest.TaxFixpreis                   = src.TaxFixpreis_;
    dest.TaxMaxBetrag                   = src.TaxMaxBetrag_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTAXTAB structure to           */
/*  a pxTaxTab object.                                                */
/*----------------------------------------------------------------------------*/
pxTaxTab&
Assign
(
    pxTaxTab&              dest,
    const tTAXTAB&    src
)
{
    dest.TaxArt_                 = src.TaxArt                            ;
    dest.TaxVonDm_                 = src.TaxVonDm                            ;
    dest.TaxProz_                 = src.TaxProz                            ;
    dest.TaxBetrag_                 = src.TaxBetrag                            ;
    dest.TaxFixpreis_               = src.TaxFixpreis                          ;
    dest.TaxMaxBetrag_          = src.TaxMaxBetrag                     ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTaxTab :: Init()
{
    tTAXTAB    record;
    memset(&record, 0 , sizeof(tTAXTAB));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTAXTAB struct and then imported to self.                     */
/*----------------------------------------------------------------------------*/
pxTaxTab&
pxTaxTab :: operator=( const pxTaxTab& src)
{
    tTAXTAB record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTAXTAB structure 'src' to        */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxTaxTab&
pxTaxTab :: operator=( const tTAXTAB& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxTaxTab :: Get
(
    DBAccessMode mode
)

{
    tTAXTAB record;
    memset(&record, 0, sizeof(tTAXTAB));
    
    record.TaxArt      = TaxArt_;
    record.TaxVonDm      = TaxVonDm_;
    record.TaxProz      = TaxProz_;
    record.TaxBetrag      = TaxBetrag_;
    record.TaxFixpreis      = TaxFixpreis_;
    record.TaxMaxBetrag    = TaxMaxBetrag_;
    
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tTAXTAB struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxTaxTab :: Put
(
)
{
    tTAXTAB record;
    memset(&record, 0, sizeof(tTAXTAB));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTAXTAB));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxTaxTab :: Read
(
    const void  *record
)
{
    return pxTaxTabRead((tTAXTAB*)record);
}

int
pxTaxTab :: ReadLock
(
    const void  *record
)
{
    return pxTaxTabReadLock((tTAXTAB*)record);
}

int
pxTaxTab :: Update
(
    const void  *record
)
{
    return pxTaxTabUpdate((tTAXTAB*)record);
}


int
pxTaxTab :: Insert
(
    const void  *record
)
{
    return pxTaxTabInsert((tTAXTAB*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxTaxTab list objects being inserted in the               */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxTaxTab :: CompareTo
(
    const nCollectable   *That,
    void           * /* p */,
    const long           /* lparm */
)   const
{
    pxTaxTab *that = (pxTaxTab*)That;
    int retval = (TaxArt_ == that->TaxArt_) ? 0
                : (TaxArt_ > that->TaxArt_ ? 1 : -1);
    if ( retval == 0 )
       retval = (TaxVonDm_ == that->TaxVonDm_) ? 0
                : (TaxVonDm_ > that->TaxVonDm_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTaxTabList :: pxTaxTabList
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
pxTaxTabList :: Select
(
    const int     count_
)
{
    tTAXTAB fil;
    memset(&fil, 0, sizeof(tTAXTAB));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxTaxTabList :: Select
(
    const char    TaxArt,
    const int     TaxVonDm,
    const int     count_
)
{
    tTAXTAB fil;
    memset(&fil, 0, sizeof(tTAXTAB));  // zero out entire record buffer
    fil.TaxArt = TaxArt;
    fil.TaxVonDm     = TaxVonDm;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxTaxTabList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxTaxTab' object:
    pxTaxTab *objectp = new pxTaxTab(Session(), *(tTAXTAB*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Find entry within the List depend on PharmacyGroupId                      */
/*----------------------------------------------------------------------------*/
/*pxTaxTab*
pxTaxTabList :: Find
(
    const nString& PharmacyGroupId
)

{
    pxTaxTabListIter iter( *this );  // define iterator
    pxTaxTab           *entryp;      // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxTaxTab*) ++iter) != NULL ) // browse list
    {
        if ( entryp->PharmacyGroupId() == PharmacyGroupId )
        {
            break;
        }
    }
    return entryp;
}
*/

int
pxTaxTabList :: EndBrowse
(
    const int  cursorid
)
{
    return pxTaxTabEndBrowse(cursorid);
}


int
pxTaxTabList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxTaxTabGetNext((tTAXTAB*)record, cursorid);
}

int
pxTaxTabList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxTaxTabStartBrowse((tTAXTAB*)keys, cursorid);
}

