#include "pxartprc.hpp"
#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxArtPriceList :: pxArtPriceList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using ArtikelNr.                                     */
/*----------------------------------------------------------------------------*/
size_t
pxArtPriceList :: Select
(
    const long    ArtikelNr
)
{
    tARTIKELPREIS a;
    memset(&a, 0, sizeof(tARTIKELPREIS));     // zero out entire record buffer
    a.ArtikelNr = ArtikelNr;
    return Select(&a);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tARTIKELPREIS struct.  */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxArtPriceList :: Select
(
    tARTIKELPREIS *recordp,
    const int           count_
)

{
    // Set the cursor id:
    int cursorid = cCRS_DEFAULT;
    nDBSelect(recordp, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
//  Selects recordsets from artikelpreis
//  using ArtikelNr and preis_typ
/*----------------------------------------------------------------------------*/
size_t
pxArtPriceList :: Select
(
    const long    ArtikelNr,
    const PriceTypeEnum Preis_Typ,
    const int     count_                // Max number of records to read
)

{
    tARTIKELPREIS a;
    memset(&a, 0, sizeof(tARTIKELPREIS));     // zero out entire record buffer
    a.ArtikelNr = ArtikelNr;
    a.Preis_Typ = static_cast<short>(Preis_Typ);

    // Set the cursor id:
    int cursorid = cCRS_TARTBPRTYPE;
    nDBSelect(&a, cursorid, count_);

    return Entries();
}// Select

/*----------------------------------------------------------------------------*/
/*  Scan the list and delete expired prices.                                  */
/*----------------------------------------------------------------------------*/
int
pxArtPriceList :: DeleteExpired
(
)

{
    pxArtPrice     *price;              // ptr to list entry
    nDate          today;               // this days date
    pxArtPriceListIter  cursor(*this);  // define an iterator
    while ( (price = (pxArtPrice*) ++cursor) != NULL )
    {
       if ( (today > price->DatumGueltigBis_ || today < price->DatumGueltigAb_) )
          delete cursor.Remove();       // offer expired
    }

    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtPriceList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxArtPrice *objectp = new pxArtPrice(Session(), *(tARTIKELPREIS*) record); // construct new object
    InsertAscending(objectp);
    return objectp;
}

int
pxArtPriceList :: EndBrowse
(
    const int  cursorid
)
{

    return pxArtikelpreisEndBrowse(cursorid);
}


int
pxArtPriceList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxArtikelpreisGetNext((tARTIKELPREIS*)record, cursorid);
}

int
pxArtPriceList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxArtikelpreisStartBrowse((tARTIKELPREIS*)keys, cursorid);
}
/*----------------------------------------------------------------------------*/
/* Find returns a pxArtPrice pointer to the corresponding entry depend on     */
/* pricetype. If entry is not found within the list, so NULLP will be returned*/
/*----------------------------------------------------------------------------*/
pxArtPrice*
pxArtPriceList :: Find
(
    const PriceTypeEnum PriceTyp          // Search for this type and
)
{
    pxArtPriceListIter   iter( *this );  // define iterator
    pxArtPrice           *entryp;        // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxArtPrice*) ++iter) != NULL ) // browse list
    {
       if ( entryp->PreisTyp() == PriceTyp )
          break;
    }
    return   entryp;                        // return entrypointer
}
/*----------------------------------------------------------------------------*/
/* GetPreisEKApo:  Returns PreisEkApo from the PriceList depend on PriceTyp   */
/* Returns  PreisEKApo or Nullm;                                              */
/*----------------------------------------------------------------------------*/
nMoney
pxArtPriceList :: GetPreisEKApo
(
    const PriceTypeEnum  PriceTyp          // Search for this type and
)
{
    nMoney  retval(0.0);
    pxArtPrice *entryp = Find( PriceTyp );      // pointer to listentry
    if (entryp)
    {
       return (retval = entryp->PreisEKApo()); // Preis
    }
    return   retval;                           // return value
}
/*----------------------------------------------------------------------------*/
/* GetPreisVKApo:  Returns PreisVKApo from the PriceList depend on PriceTyp   */
/* Returns  PreisVKApo or Nullm;                                              */
/*----------------------------------------------------------------------------*/
nMoney
pxArtPriceList :: GetPreisVKApo
(
    const PriceTypeEnum  PriceTyp          // Search for this type and
)
{
    nMoney  retval(0.0);
    pxArtPrice *entryp = Find( PriceTyp );      // pointer to listentry
    if (entryp)
    {
       return (retval = entryp->PreisVKApo()); // Preis
    }
    return   retval;                           // return value
}
/*----------------------------------------------------------------------------*/
/* PreisEKGrosso: Returns PreisEKGrosso from the PriceList depend on PriceTyp */
/* Returns  PreisEKGrosso or Nullm;                                           */
/*----------------------------------------------------------------------------*/
nMoney
pxArtPriceList :: GetPreisEKGrosso
(
    const PriceTypeEnum  PriceTyp          // Search for this type and
)
{
    nMoney  retval(0.0);
    pxArtPrice *entryp = Find( PriceTyp );      // pointer to listentry
    if (entryp)
    {
       return (retval = entryp->PreisEKGrosso()); // Preis
    }
    return   retval;                           // return value
}
/*----------------------------------------------------------------------------*/
/* PreisEKGrossoNA: Returns PreisEKGrossoNA from the PriceList depend on Typ  */
/* Returns  PreisEKGrossoNA or Nullm;                                         */
/*----------------------------------------------------------------------------*/
nMoney
pxArtPriceList :: GetPreisEKGrossoNA
(
    const PriceTypeEnum  PriceTyp          // Search for this type and
)
{
    nMoney  retval(0.0);
    pxArtPrice *entryp = Find( PriceTyp );      // pointer to listentry
    if (entryp)
    {
       return (retval = entryp->PreisEKGrossoNA()); // Preis
    }
    return   retval;                           // return value
}
/*----------------------------------------------------------------------------*/
/* RabattFest: Returns RabattFest from the PriceList depend on Typ            */
/* Returns  RabattFest or Nullm;                                              */
/*----------------------------------------------------------------------------*/
double
pxArtPriceList :: GetRabattFest
(
    const PriceTypeEnum  PriceTyp          // Search for this type and
)
{
    double  retval(0.0);
    pxArtPrice *entryp = Find( PriceTyp );      // pointer to listentry
    if (entryp)
    {
       return (retval = entryp->RabattFest()); // Preis
    }
    return   retval;                           // return value
}
/*----------------------------------------------------------------------------*/
/* PreisProzent: Returns PreisProzent from the PriceList depend on Typ        */
/* Returns  PreisProzent or Nullm;                                            */
/*----------------------------------------------------------------------------*/
double
pxArtPriceList :: GetPreisProzent
(
    const PriceTypeEnum  PriceTyp          // Search for this type and
)
{
    double  retval(0.0);
    pxArtPrice *entryp = Find( PriceTyp );      // pointer to listentry
    if (entryp)
    {
       return (retval = entryp->PreisProzent()); // Preis
    }
    return   retval;                           // return value
}
/*----------------------------------------------------------------------------*/
/* PreisAGP: Returns PreisAGP from the PriceList depend on Typ                */
/* Returns  PreisAGP or Nullm;                                                */
/*----------------------------------------------------------------------------*/
double
pxArtPriceList :: GetPreisAGP
(
    const PriceTypeEnum  PriceTyp          // Search for this type and
)
{
    double  retval(0.0);
    pxArtPrice *entryp = Find( PriceTyp );      // pointer to listentry
    if (entryp)
    {
       return (retval = entryp->PreisAGP());   // Preis
    }
    return   retval;                           // return value
}
/*----------------------------------------------------------------------------*/
/* PreisFest: Returns PreisFest from the PriceList depend on Typ              */
/* Returns  PreisFest or Nullm;                                               */
/*----------------------------------------------------------------------------*/
nMoney
pxArtPriceList :: GetPreisFest
(
    const PriceTypeEnum  PriceTyp          // Search for this type and
)
{
    nMoney     retval(0.0);
    pxArtPrice *entryp = Find( PriceTyp );      // pointer to listentry
    if (entryp)
    {
       return (retval = entryp->PreisFest());   // Preis
    }
    return   retval;                           // return value
}
/*----------------------------------------------------------------------------*/
/* MaxAvp: Returns MaxAvp from the PriceList depend on Typ                    */
/* Returns  PreisFest or Nullm;                                               */
/*----------------------------------------------------------------------------*/
nMoney
pxArtPriceList :: GetMaxAvp
(
    const PriceTypeEnum  PriceTyp          // Search for this type and
)
{
    nMoney     retval(0.0);
    pxArtPrice *entryp = Find( PriceTyp );      // pointer to listentry
    if (entryp)
    {
       return (retval = entryp->MaxAvp());   // Preis
    }
    return   retval;                           // return value
}
