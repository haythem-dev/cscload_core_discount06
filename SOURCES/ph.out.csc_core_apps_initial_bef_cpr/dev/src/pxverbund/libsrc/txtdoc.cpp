/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1996 by NORDAT Network GmbH
                              All rights reserved

Implementation of class pxTextLine methods.

REVISION HISTORY

29 Jan 1996 V1.00 REV 00 written by Peter Hoernich.
*/

#include "pxtxtdoc.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"

#define cTXTDOC_NOTFOUND       1        // textdoc not found
#define mDOK2BEM(rec)                                    \
    tTEXTDOK       *docp = (tTEXTDOK *) rec;             \
    tKDAUFTRAGBEM   bem;                                 \
    tKDAUFTRAGBEM  *bufp = &bem;                         \
    memset(bufp, 0, sizeof(tKDAUFTRAGBEM));              \
    bufp->KdAuftragNr = atol(docp->DokName);             \
    bufp->Bemerkungsart = (short) docp->DokTyp;          \
    bufp->Bemerkungsnr  = (short) docp->DokZeilenNr;     \
    strcpy(bufp->Bemerkungen, docp->DokText)             \

typedef struct
{
    int           DokTyp;              // Dokument Type
    char          DokName[16+1];       // Dokument Name
    int           DokZeilenNr;         // Dokument Zeilennr.
    char          DokText[240+1];      // Dokument Textzeile
} tTEXTDOK, * tTEXTDOKP;

/*----------------------------------------------------------------------------*/
/*  Destruction.                                                              */
/*  The current implementation uses a simple approach: The user must know     */
/*  what she or he is doing. Prior to destruction, the document should be     */
/*  written to the data base using the Put() method, otherwise any changes    */
/*  are lost. If you are unsure, use IsDirty() to determine if the document   */
/*  has been updated.                                                         */
/*----------------------------------------------------------------------------*/
pxTextDoc :: ~pxTextDoc()
{
    Clear();
}

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxTextDoc :: pxTextDoc
(
    pxSession*          session,
    const pxTextDocType type,
    const nString&      name
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
    LinesRead_  = 0;
    DocType_    = type;
    DocName_    = name;
    DocName_.Trim(mSIZEOF(tTEXTDOK,DokName) -1);
}

/*----------------------------------------------------------------------------*/
/*  Read entire document from the data base.                                  */
/*----------------------------------------------------------------------------*/
int
pxTextDoc :: Get
(
)
{
    tTEXTDOK record;
    ToRecord(&record);
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, 999999);
    LinesRead_ = static_cast<int>(Entries());
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  Write document into data base. Since each text line is a single data base */
/*  row in the underlying RDBMS, we do not update existing rows, delete       */
/*  removed text lines and insert new ones. To keep things simple, all rows   */
/*  of a document are deleted and then inserted from the document container.  */
/*----------------------------------------------------------------------------*/
int
pxTextDoc :: Put
(
)
{
    int retval = 0;
    tTEXTDOK record;
    if ( IsDirty() )
    {
        ToRecord(&record);
        mDOK2BEM(&record);
        retval = pxAuftragBemDelete(bufp);  // delete all bems
        if (retval == cTXTDOC_NOTFOUND )
            retval = 0;

        if ( retval ==  0 )
        {
            pxTextDocIter it(*this);
            pxTextLine* curp;
            int count_ = 0;
            while ( ((curp = (pxTextLine *) ++it) != NULL) && (retval == 0))
            {
                curp->ClearActive();          // Clear active bit
                if ( !curp->Text_.IsEmpty() ) // Ensure text is not empty
                {
                    curp->Number_ = ++count_;  // number this line
                    ToRecord(&record, curp);
                    retval = curp->nDBWrite(&record, sizeof(tTEXTDOK));
                }
            }
        }
    }

    if ( retval == 0 )                              // In case of success: document contains
        LinesRead_ = static_cast<int>(Entries());   // the same than the data base
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Construct a new line and append it to the document.                       */
/*----------------------------------------------------------------------------*/
pxTextLine*
pxTextDoc :: NewLine
(
    const nString& Text
)
{
    pxTextLine* lp = new pxTextLine(Session(), Text);
    Append(lp);
    return lp;
}

/*----------------------------------------------------------------------------*/
/*  Removes and returns the first item with the specified address from the    */
/*  list, or returns NULL if no item with matching address is found.          */
/*----------------------------------------------------------------------------*/
pxTextLine*
pxTextDoc :: Remove
(
    pxTextLine* lp
)
{
    return (pxTextLine *) nDListCollect::Remove(lp);
}

/*----------------------------------------------------------------------------*/
/*  Determine if document is 'dirty'. This state is flagged if any updates    */
/*  occurred.                                                                 */
/*----------------------------------------------------------------------------*/
bool
pxTextDoc :: IsDirty() const
{
    if ( LinesRead_ != (int)Entries() ) // then lines have been inserted or
        return true;                    // deleted

    pxTextDocIter it((pxTextDoc&)*this); // must iterate thru document
    pxTextLine* curp;
    while ( (curp = (pxTextLine *) ++it) != NULL )
    {
        if ( !(curp->IsActive()) || curp->IsDirty() )
            return true;                 // new or updated line
    }

    return false;
}

/*----------------------------------------------------------------------------*/
/*  Copy document contents into a data base record structure.                 */
/*----------------------------------------------------------------------------*/
void
pxTextDoc::ToRecord                     // from document
(
    void *recp
)   const
{
    tTEXTDOK *record = (tTEXTDOK *) recp;
    memset(record, 0, sizeof(tTEXTDOK));
    record->DokTyp = DocType_;
    DocName_.GetData(record->DokName);
}

void
pxTextDoc::ToRecord                     // from text line
(
    void        *recp,
    pxTextLine  *line
)   const
{
    tTEXTDOK *record = (tTEXTDOK *) recp;
    record->DokZeilenNr = line->Number_;
    line->Text_.GetData(record->DokText);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxTextDoc :: AddToList
(
    const void *record,
    const int  /* row */
)
{
/*###
The following should be uncommented when changing data base table format
    tTEXTDOK  *recp = (tTEXTDOK*)record;
    pxTextLine *objectp = new pxTextLine(Session(), recp->DokText,
                                         recp->DokZeilenNr);
*/
    tKDAUFTRAGBEM  *recp = (tKDAUFTRAGBEM*)record;
    pxTextLine *objectp = new pxTextLine(Session(), recp->Bemerkungen, (int)recp->Bemerkungsnr);
    InsertAscending(objectp);
    return objectp;
}

int
pxTextDoc :: EndBrowse
(
    const int  cursorid
)
{
    return pxAuftragBemEndBrowse(cursorid);
}

int
pxTextDoc :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxAuftragBemGetNext((tKDAUFTRAGBEM *)record, cursorid);
}

int
pxTextDoc :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    mDOK2BEM(keys);
    return pxAuftragBemStartBrowse(bufp, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  Text line class implementation.                                           */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTextLine :: pxTextLine
(
    pxSession      *session,            // The session pointer
    const nString& text                 // text for this document line
)
    : pxDBRecord(session)
{
    Init(text);
}

/*----------------------------------------------------------------------------*/
/*  Protected construction, used when reading the entire document.            */
/*----------------------------------------------------------------------------*/
pxTextLine :: pxTextLine
(
    pxSession      *session,            // The session pointer
    const nString& text,                // text for this document line
    const int number                    // line number
)
    : pxDBRecord(session)
{
    Init(text, number);
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTextLine :: pxTextLine
(
    pxTextLine& src
)
    : pxDBRecord(src.Session())
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTextLine :: Init
(
    const nString& text,
    const int      number
)
{
    Text_ = text;
    Number_ = number;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxTextLine&
pxTextLine :: operator=( const pxTextLine& src)
{
    Text_   = src.Text_;
    Number_ = src.Number_;
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxTextLine :: Insert
(
    const void *record
)
{
    mDOK2BEM(record);
    return pxAuftragBemInsert(bufp);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*----------------------------------------------------------------------------*/
int
pxTextLine :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxTextLine *that = (pxTextLine*) That;
    return (Number_ == that->Number_) ? 0 : (Number_ > that->Number_ ? 1 : -1);
}
