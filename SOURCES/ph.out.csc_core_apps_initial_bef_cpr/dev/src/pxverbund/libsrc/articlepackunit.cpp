#include "pxartpackunit.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtPackUnit :: pxArtPackUnit
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
pxArtPackUnit :: pxArtPackUnit
(
    pxArtPackUnit& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLEPACKUNIT structure to construct this instance.                */
/*----------------------------------------------------------------------------*/
pxArtPackUnit :: pxArtPackUnit
(
    pxSession   *session,
    tARTICLEPACKUNIT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtPackUnit :: ~pxArtPackUnit()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLEPACKUNIT structure.    */
/*----------------------------------------------------------------------------*/
tARTICLEPACKUNIT&
Assign
(
    tARTICLEPACKUNIT&           dest,
    const pxArtPackUnit&        src
)
{
    dest.ArticleNo     = src.ArticleNo_;
    dest.PackingUnit   = src.PackingUnit_;
    dest.RoundPct      = src.RoundPct_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLEPACKUNIT structure to              */
/*  a pxArtPackUnit object.                                                   */
/*----------------------------------------------------------------------------*/
pxArtPackUnit&
Assign
(
    pxArtPackUnit&              dest,
    const tARTICLEPACKUNIT&     src
)
{
    dest.ArticleNo_     = src.ArticleNo;
    dest.PackingUnit_   = src.PackingUnit;
    dest.RoundPct_      = src.RoundPct;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtPackUnit :: Init()
{
    tARTICLEPACKUNIT    record;
    memset(&record, 0 , sizeof(tARTICLEPACKUNIT));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTICLEPACKUNIT struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxArtPackUnit&
pxArtPackUnit :: operator=( const pxArtPackUnit& src)
{
    tARTICLEPACKUNIT record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLEPACKUNIT structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArtPackUnit&
pxArtPackUnit :: operator=( const tARTICLEPACKUNIT& src)
{
    return Assign(*this, src);
}
int
pxArtPackUnitList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArtPackUnitEndBrowse(cursorid);
}


int
pxArtPackUnitList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxArtPackUnitGetNext((tARTICLEPACKUNIT*)record, cursorid);
}

int
pxArtPackUnitList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArtPackUnitStartBrowse((tARTICLEPACKUNIT*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtPackUnit list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxArtPackUnit :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxArtPackUnit *that = (pxArtPackUnit*)That;

    int retval = (ArticleNo_ == that->ArticleNo_) ? 0
                : (ArticleNo_ > that->ArticleNo_ ? 1 : -1);

    if ( retval == 0 )
         retval = (PackingUnit_ == that->PackingUnit_) ? 0
                  : (PackingUnit_ > that->PackingUnit_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtPackUnitList :: pxArtPackUnitList
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
pxArtPackUnitList :: Select
(
    const long    ArticleNo,
    const int     count_
)
{
    tARTICLEPACKUNIT fil;
    memset(&fil, 0, sizeof(tARTICLEPACKUNIT));  // zero out entire record buffer
    fil.ArticleNo   = ArticleNo;
    int cursorid   = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtPackUnitList :: AddToList
(
    const void  *record,
    const int  /* row */
)

{
    // construct new 'pxArtPackUnit' object:
    pxArtPackUnit *objectp = new pxArtPackUnit(Session(), *(tARTICLEPACKUNIT*) record);
    InsertAscending(objectp);
    return objectp;
}

