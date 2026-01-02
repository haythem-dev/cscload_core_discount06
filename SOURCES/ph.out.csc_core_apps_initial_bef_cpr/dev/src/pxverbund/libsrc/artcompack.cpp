/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxArtComPack methods.

REVISION HISTORY

16 July 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/
#include "pxartcompack.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtComPack :: pxArtComPack
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
pxArtComPack :: pxArtComPack
(
    pxArtComPack& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTCOMPACK structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxArtComPack :: pxArtComPack
(
    pxSession   *session,
    tARTCOMPACK& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtComPack :: pxArtComPack
(
    pxSession *session,
   const pxArtComPack *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
       (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtComPack :: ~pxArtComPack()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTCOMPACK structure.   */
/*----------------------------------------------------------------------------*/
tARTCOMPACK&
Assign
(
    tARTCOMPACK&           dest,
    const pxArtComPack&       src
)
{
    dest.Article_No_Pack           = src.ArticleNoPack_          ;
    dest.Article_No_Element        = src.ArticleNoElement_       ;
    dest.Quantity                  = src.Quantity_               ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTCOMPACK structure to                    */
/*  a pxArtComPack object.                                                 */
/*----------------------------------------------------------------------------*/
pxArtComPack&
Assign
(
    pxArtComPack&              dest,
    const tARTCOMPACK&    src
)
{
    dest.ArticleNoPack_           = src.Article_No_Pack          ;
    dest.ArticleNoElement_        = src.Article_No_Element       ;
    dest.Quantity_                = src.Quantity                 ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtComPack :: Init()
{
    tARTCOMPACK    record;
    memset(&record, 0 , sizeof(tARTCOMPACK));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTCOMPACK struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxArtComPack&
pxArtComPack :: operator=( const pxArtComPack& src)
{
    tARTCOMPACK record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTCOMPACK structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArtComPack&
pxArtComPack :: operator=( const tARTCOMPACK& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtComPack list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*----------------------------------------------------------------------------*/
int
pxArtComPack :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const

{
    pxArtComPack *that = (pxArtComPack*)That;
    int retval = (ArticleNoPack_ == that->ArticleNoPack_) ? 0
                : (ArticleNoPack_ > that->ArticleNoPack_ ? 1 : -1);


    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtComPackList :: pxArtComPackList
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
pxArtComPackList :: Select
(
    const int     count_
)
{
    tARTCOMPACK fil;
    memset(&fil, 0, sizeof(tARTCOMPACK));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxArtComPackList :: Select
(
    const long    ArticleNoPack,
    const int     count_
)
{
    tARTCOMPACK fil;
    memset(&fil, 0, sizeof(tARTCOMPACK));  // zero out entire record buffer
    fil.Article_No_Pack   = ArticleNoPack;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Find return entryp depend on articleno                                    */
/*----------------------------------------------------------------------------*/
pxArtComPack*
pxArtComPackList :: Find
(
    const long ArticleNoElement
)
{
    pxArtComPack *curp = NULL;             // ptr to current entry
    pxArtComPackListIter  cursor(*this);   // define an iterator
    while ( (curp = (pxArtComPack*) ++cursor) != NULL )
    {
       if (curp->ArticleNoElement() == ArticleNoElement )
       {
          break;
       }
    }
    return curp;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtComPackList :: AddToList
(
    const void  *record,
    const int  /*row*/
) 
{
    // construct new 'pxArtComPack' object:
    pxArtComPack *objectp = new pxArtComPack(Session(), *(tARTCOMPACK*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtComPackList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArtComPackEndBrowse(cursorid);
}


int
pxArtComPackList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxArtComPackGetNext((tARTCOMPACK*)record, cursorid);
}

int
pxArtComPackList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArtComPackStartBrowse((tARTCOMPACK*)keys, cursorid);
}
