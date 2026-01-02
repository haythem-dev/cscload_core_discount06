#include "pxartrip.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxArtReImport :: pxArtReImport
(
)
{
    Init();
}

pxArtReImport :: pxArtReImport
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
pxArtReImport :: pxArtReImport
(
    pxArtReImport& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTIKELREIMPORT structure to construct this instance.                */
/*----------------------------------------------------------------------------*/
pxArtReImport :: pxArtReImport
(
    pxSession   *session,
    tARTIKELREIMPORT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxArtReImport :: pxArtReImport
(
    pxSession   *session,
    short FilialNr,
    long  ArtikelNr,
    long  ArtikelAlternNr,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    FilialNr_  = FilialNr;
    ArtikelNr_ = ArtikelNr;
    ArtikelAlternNr_ = ArtikelAlternNr;
    Get(mode);
}


/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtReImport :: ~pxArtReImport()
{
//  delete subobjects;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTIKELREIMPORT structure.    */
/*----------------------------------------------------------------------------*/
tARTIKELREIMPORT&
Assign
(
          tARTIKELREIMPORT&   dest,
    const pxArtReImport&      src
)
{
    // Copy native data types:
    dest.FilialNr        = src.FilialNr_;
    dest.ArtikelNr       = src.ArtikelNr_;
    dest.ArtikelAlternNr = src.ArtikelAlternNr_;
    dest.KZAktivPassiv   = src.KZAktivPassiv_;
    dest.ReihenFolge     = src.ReihenFolge_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKELREIMPORT structure                       */
/*  to a pxArtReImport object.                                                */
/*----------------------------------------------------------------------------*/
pxArtReImport&
Assign
(
          pxArtReImport&      dest,
    const tARTIKELREIMPORT&   src
)
{
    // Copy native data types:
    dest.FilialNr_          = src.FilialNr;
    dest.ArtikelNr_         = src.ArtikelNr;
    dest.ArtikelAlternNr_   = src.ArtikelAlternNr;
    dest.KZAktivPassiv_     = src.KZAktivPassiv;
    dest.ReihenFolge_       = src.ReihenFolge;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtReImport :: Init()
{
    tARTIKELREIMPORT    record;
    memset(&record, 0 , sizeof(tARTIKELREIMPORT));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTIKELREIMPORT struct and then imported to self.                        */
/*----------------------------------------------------------------------------*/
pxArtReImport&
pxArtReImport :: operator=( const pxArtReImport& src)
{
    tARTIKELREIMPORT record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKELREIMPORT structure to this instance.     */
/*----------------------------------------------------------------------------*/
pxArtReImport&
pxArtReImport :: operator=( const tARTIKELREIMPORT& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtReImport :: Get
(
    DBAccessMode mode
)
{
    tARTIKELREIMPORT record;
    memset(&record, 0, sizeof(tARTIKELREIMPORT));
    record.FilialNr  = FilialNr_;
    record.ArtikelNr = ArtikelNr_;
    record.ArtikelAlternNr = ArtikelAlternNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;           // import the data from tARTIKELREIMPORT struct
    else if ( retval > cDBXR_NORMAL )
        DBCondition(nMessage(CMsgStream(),
                    CMSG_ART_REIMPORT_NOTFOUND,
                    record.ArtikelNr,
                    CMSG_ART_REIMPORT_NOTFOUND));
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtReImport :: Read
(
    const void  *record
)
{
    return pxArtikelReimportRead((tARTIKELREIMPORT*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxArtReImport list*/
/*  objects being inserted in the following ascending sequence:               */
/*----------------------------------------------------------------------------*/
int
pxArtReImport :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxArtReImport *that = (pxArtReImport*)That;
    int retval;

    retval = (ReihenFolge_ == that->ReihenFolge_) ? 0
             : (ReihenFolge_ < that->ReihenFolge_ ? -1 : 1);

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtReImportList :: pxArtReImportList
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
pxArtReImportList :: Select
(
    const int count_
)
{
    tARTIKELREIMPORT record;
    memset(&record, 0, sizeof(tARTIKELREIMPORT));    // zero out record buffer

    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using ArtikelNr.                                     */
/*----------------------------------------------------------------------------*/
size_t
pxArtReImportList :: Select
(
    const short   FilialNr,
    const long    ArtikelNr,
    const int     count_
)
{
    tARTIKELREIMPORT record;
    memset(&record, 0, sizeof(tARTIKELREIMPORT));  // zero out record buffer
    record.FilialNr  = FilialNr;
    record.ArtikelNr = ArtikelNr;

    return Select(&record, count_);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using ArtikelNr.                                     */
/*----------------------------------------------------------------------------*/
size_t
pxArtReImportList :: Select
(
    const long    ArtikelNr,
    const int     count_
)
{
    tARTIKELREIMPORT record;
    memset(&record, 0, sizeof(tARTIKELREIMPORT));  // zero out record buffer
    record.ArtikelNr = ArtikelNr;

    return Select(&record, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection with default where clause based upon the values stored   */
/*  in the record structure.                                                  */
/*----------------------------------------------------------------------------*/
size_t
pxArtReImportList :: Select
(
    const tARTIKELREIMPORT *recordp,
    const int              count_
)
{
    int cursorid = cCRS_DEFAULT;
    nDBSelect(recordp, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Shrink removes all entries from the list where mode is not equal to       */
/*  entry's KZAktivPassiv. Returns count of remained entries                  */
/*----------------------------------------------------------------------------*/
int
pxArtReImportList :: Shrink
(
    REIMPShrinkMode mode
)
{
    pxArtReImportListIter   cursor(*this);   // iterator reimportlist
    pxArtReImport           *entryp;         // pxArtReImport pointer

    cursor.Reset();                          // top of artstoreloclist
    while ( ( entryp = ( pxArtReImport *) ++cursor) != NULL ) // browse list
    {
        switch (mode)
        {
            case cREIMPAktiv :
            {
                if ( entryp->IsPassivLinkage() )
                {
                    delete cursor.Remove();      // remove non entry from list
                }
                break;
            }

            case cREIMPDefault :
            {
                if ( entryp->IsActivLinkage() )
                {
                    delete cursor.Remove();      // remove non entry from list
                }
                break;
            }

            default :
                break;
        }
    }
    return static_cast<int>(Entries());
 }

/*----------------------------------------------------------------------------*/
/*  Build returns a new pxArtReImportList depend on mode                      */
/*----------------------------------------------------------------------------*/
pxArtReImportList*
pxArtReImportList :: Build
(
    REIMPShrinkMode mode
)
{
    char action = static_cast<char>(mode + 48);
    int                      objects = 0;    // count in list
    pxArtReImportListIter     cursor(*this);  // iterator reimportlist
    pxArtReImport             *entryp;        // pxArtReImport pointer
    pxArtReImport             *newentryp;     // pxArtReImport pointer
    pxArtReImportList         *newlist=new pxArtReImportList ( Session() );
    pxArtReImportListIter     iter(*newlist); // iterator reimportlist

    cursor.Reset();                          // top of reimportlist
    while ( ( entryp = ( pxArtReImport *) ++cursor) != NULL ) // browse list
    {
        if ( entryp->KZAktivPassiv() == action )
        {
            newentryp = new pxArtReImport(*entryp);
            if (! newentryp->IsGoodState() )
            {
                delete newentryp;
            }
            else
            {
                newentryp->SetActive();
                newlist->Append(newentryp);
                objects ++;                // count objects
            }
        }
    }

    return newlist;
 }

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtReImportList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxArtReImport  ' object:
    pxArtReImport *objectp = new pxArtReImport(Session(), *(tARTIKELREIMPORT*) recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxArtReImportList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArtikelReimportEndBrowse(cursorid);
}

int
pxArtReImportList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxArtikelReimportGetNext((tARTIKELREIMPORT*)recordp, cursorid);
}

int
pxArtReImportList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArtikelReimportStartBrowse((tARTIKELREIMPORT*)keys, cursorid);
}
