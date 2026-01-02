#include "pxartsto.hpp"
#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxArtStoreLocList :: pxArtStoreLocList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using only article number.                           */
/*----------------------------------------------------------------------------*/
size_t
pxArtStoreLocList :: Select
(
    const long    ArtikelNr,
    const int     count_                // Max number of records to read
)

{
    tARTIKELLAGERORT a;

    memset(&a, 0, sizeof(tARTIKELLAGERORT));    // zero out entire record buffer
    a.ArtikelNr = ArtikelNr;                    // assign article number

    return Select(&a, count_);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using article number and branch number.              */
/*----------------------------------------------------------------------------*/
size_t
pxArtStoreLocList :: Select
(
    const long    ArtikelNr,
    const short   FilialNr,
    const int     count_                // Max number of records to read
)
{
    tARTIKELLAGERORT a;

    memset(&a, 0, sizeof(tARTIKELLAGERORT));    // zero out entire record buffer
    a.ArtikelNr = ArtikelNr;                    // Assign article number
    a.FilialNr  = FilialNr;                     // Assign branch number

    return Select(&a, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tARTIKELLAGERORT       */
/*  structure. Note that unused search criteria must have the appropiate      */
/*  default values, i.e. '\0' for a string value, 0 for an integer etc.       */
/*----------------------------------------------------------------------------*/
size_t
pxArtStoreLocList :: Select
(
          tARTIKELLAGERORT  *artikellagerortp,
    const int               count_
)

{
    // Set the default cursor id (for Artikelnr only)
    int cursorid = cCRS_DEFAULT;

    if ((artikellagerortp->FilialNr))
       cursorid = cCRSART_STO_ArtikelNrFilialNr;
    // Set cursor id for ArtikelNr and Filialnr

    nDBSelect(artikellagerortp, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtStoreLocList :: AddToList
(
    const void  *record,
    const int  /* row */
)

{
    // construct new object
    pxArtStoreLoc *objectp = new pxArtStoreLoc(Session(), *(tARTIKELLAGERORT*) record);
    InsertAscending(objectp);
    return objectp;
}

int pxArtStoreLocList::StartBrowse(const void *keys, const int cursorid)
{
    return pxLagerortStartBrowse((tARTIKELLAGERORT*)keys, cursorid);
}

int pxArtStoreLocList::EndBrowse(const int cursorid)
{
    return pxLagerortEndBrowse(cursorid);
}

int pxArtStoreLocList::GetNext(const void* record, const int cursorid)
{
    return pxLagerortGetNext((tARTIKELLAGERORT*)record, cursorid);
}

/*----------------------------------------------------------------------------*/
/* Find returns a pxArtStoreLoc pointer to the corresponding entry. If the    */
/* entry is not found within the list , so NULLP will be returned             */
/*----------------------------------------------------------------------------*/
pxArtStoreLoc*
pxArtStoreLocList :: Find
(
    const short FilialNr
)
{
    pxArtStoreLocListIter   iter( *this );  // define iterator
    pxArtStoreLoc          *entryp;         // pointer to listentry


    if (!( FilialNr > 0))
       return  ( entryp = (pxArtStoreLoc*)At(0) ) ;

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxArtStoreLoc *) ++iter) != NULL ) // browse list
    {
       if ( entryp->FilialNr() == FilialNr )
          break;
    }
    return   entryp;                           // return entrypointer
}
