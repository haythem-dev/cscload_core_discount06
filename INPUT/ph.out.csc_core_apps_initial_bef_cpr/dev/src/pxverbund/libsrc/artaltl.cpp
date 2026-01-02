#include "pxartalt.hpp"
#include "pxdbxx.h"
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxArtAlternList :: pxArtAlternList
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
pxArtAlternList :: Select
(
    const int     count_
)
{
    tARTIKELALTERN record;
    memset(&record, 0, sizeof(tARTIKELALTERN));    // zero out record buffer

    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using ArtikelNr.                                     */
/*----------------------------------------------------------------------------*/
size_t
pxArtAlternList :: Select
(
    const long    ArtikelNr,
    const short   FilialNr,
    const int     count_
)
{
    tARTIKELALTERN record;
    memset(&record, 0, sizeof(tARTIKELALTERN));  // zero out record buffer
    record.ArtikelNr = ArtikelNr;
        record.FilialNr  = FilialNr;

    return Select(&record, count_);
}
/*----------------------------------------------------------------------------*/
size_t pxArtAlternList::SelectForward(const long Artikel_Nr, const short FilialNr, const int count_)
{
    tARTIKELALTERN record;
    memset(&record, 0, sizeof(tARTIKELALTERN));  // zero out record buffer
    record.ArtikelNr = Artikel_Nr;
    record.FilialNr  = FilialNr;
    int cursorid = cCRSARTIKELALTERN_FORWARD;
    nDBSelect(&record, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
size_t pxArtAlternList::SelectReverse(const long Artikel_Nr_Altern, const short FilialNr, const int count_)
{
    tARTIKELALTERN record;
    memset(&record, 0, sizeof(tARTIKELALTERN));  // zero out record buffer
    record.ArtikelAlternNr = Artikel_Nr_Altern;
    record.FilialNr  = FilialNr;
    int cursorid = cCRSARTIKELALTERN_REVERSE;
    nDBSelect(&record, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Do the selection with default where clause based upon the values stored   */
/*  in the record structure.                                                  */
/*----------------------------------------------------------------------------*/
size_t
pxArtAlternList :: Select
(
    const tARTIKELALTERN    *recordp,
    const int              count_
)
{
    int cursorid = cCRS_DEFAULT;
    nDBSelect(recordp, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtAlternList :: AddToList
(
    const void  *recordp,
    const int  /*row*/
)
{
    // construct new 'pxArtAltern  ' object:
    pxArtAltern *objectp =
                   new pxArtAltern(Session(), *(tARTIKELALTERN*) recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxArtAlternList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArtikelAlternEndBrowse(cursorid);
}

int
pxArtAlternList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxArtikelAlternGetNext((tARTIKELALTERN*)recordp, cursorid);
}

int
pxArtAlternList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArtikelAlternStartBrowse((tARTIKELALTERN*)keys, cursorid);
}
