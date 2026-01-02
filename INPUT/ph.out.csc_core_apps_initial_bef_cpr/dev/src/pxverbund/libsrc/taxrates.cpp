/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxTaxRates  methods.

REVISION HISTORY

12 December 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxtaxrates.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTaxRates :: pxTaxRates
(
    pxSession *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTaxRates :: pxTaxRates
(
    pxTaxRates& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTAXRATES structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxTaxRates :: pxTaxRates
(
    pxSession  *session,
    tTAXRATES& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTaxRates :: ~pxTaxRates()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTAXRATES structure.           */
/*----------------------------------------------------------------------------*/
tTAXRATES&
Assign
(
    tTAXRATES&           dest,
    const pxTaxRates&    src
)
{
    dest.TaxLevel      = src.TaxLevel_     ;
    dest.SalesTaxRate  = src.SalesTaxRate_ ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTAXRATES structure to                     */
/*  a pxTaxRates object.                                                      */
/*----------------------------------------------------------------------------*/
pxTaxRates&
Assign
(
    pxTaxRates&          dest,
    const tTAXRATES&     src
)
{
    dest.TaxLevel_      = src.TaxLevel     ;
    dest.SalesTaxRate_  = src.SalesTaxRate ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTaxRates :: Init()
{
    tTAXRATES record;
    memset(&record, 0 , sizeof(tTAXRATES));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTAXRATES struct and then imported to self.                               */
/*----------------------------------------------------------------------------*/
pxTaxRates&
pxTaxRates :: operator=( const pxTaxRates& src)
{
    tTAXRATES record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTAXRATES structure 'src' to                     */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxTaxRates&
pxTaxRates :: operator=( const tTAXRATES& src)
{
    return Assign(*this, src);
}

int
pxTaxRatesList :: EndBrowse
(
    const int cursorid
)
{
    return pxTaxRatesEndBrowse(cursorid);
}

int
pxTaxRatesList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxTaxRatesGetNext((tTAXRATES*)record, cursorid);
}

int
pxTaxRatesList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxTaxRatesStartBrowse((tTAXRATES*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxTaxRates list objects being inserted in the                     */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxTaxRates :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxTaxRates *that = (pxTaxRates*)That;

    int retval = (TaxLevel_ == that->TaxLevel_) ? 0
               : (TaxLevel_ > that->TaxLevel_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTaxRatesList :: pxTaxRatesList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxTaxRatesList :: Select
(
    const int count_
)
{
    tTAXRATES fil;
    memset(&fil, 0, sizeof(tTAXRATES));  // zero out entire record buffer
    int cursorid   = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxTaxRatesList :: AddToList
(
    const void *record,
    const int  /* row */
)
{
    // construct new 'pxTaxRates' object:
    pxTaxRates *objectp = new pxTaxRates(Session(), *(tTAXRATES*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Find entry depend on TaxLevel                                             */
/*----------------------------------------------------------------------------*/
pxTaxRates*
pxTaxRatesList :: Find
(
    const short  TaxLevel
)
{
    pxTaxRatesListIter cursor(*this);
    pxTaxRates   *entryp;
    while ( (entryp = (pxTaxRates*) ++cursor) != NULL )
    {
        if ( entryp->TaxLevel_ == TaxLevel )
            break;
    }
    return entryp;
}
