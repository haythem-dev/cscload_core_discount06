#include "pxarticlegroup.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArticleGroup :: pxArticleGroup
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
pxArticleGroup :: pxArticleGroup
(
    pxArticleGroup& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLEGROUP structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxArticleGroup :: pxArticleGroup
(
    pxSession   *session,
    tARTICLEGROUP& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleGroup :: pxArticleGroup
(
    pxSession *session,
   const pxArticleGroup *src
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
pxArticleGroup :: ~pxArticleGroup()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLEGROUP structure.   */
/*----------------------------------------------------------------------------*/
tARTICLEGROUP&
Assign
(
    tARTICLEGROUP&           dest,
    const pxArticleGroup&       src
)
{
    dest.ArticleNo                 = src.ArticleNo_              ;
    dest.ArtCategoryNo            = src.ArtCategoryNo_         ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLEGROUP structure to                    */
/*  a pxArticleGroup object.                                                 */
/*----------------------------------------------------------------------------*/
pxArticleGroup&
Assign
(
    pxArticleGroup&              dest,
    const tARTICLEGROUP&    src
)
{
    dest.ArticleNo_                = src.ArticleNo               ;
    dest.ArtCategoryNo_           = src.ArtCategoryNo          ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArticleGroup :: Init()
{
    tARTICLEGROUP    record;
    memset(&record, 0 , sizeof(tARTICLEGROUP));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTICLEGROUP struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxArticleGroup&
pxArticleGroup :: operator=( const pxArticleGroup& src)
{
    tARTICLEGROUP record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLEGROUP structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArticleGroup&
pxArticleGroup :: operator=( const tARTICLEGROUP& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArticleGroup list objects being inserted in the                */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo                                                      */
/*----------------------------------------------------------------------------*/
int
pxArticleGroup :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxArticleGroup *that = (pxArticleGroup*)That;
    int retval = (ArtCategoryNo_ == that->ArtCategoryNo_) ? 0
                : (ArtCategoryNo_ > ArtCategoryNo_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleGroupList :: pxArticleGroupList
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
pxArticleGroupList :: Select
(
    const int     count_
)
{
    tARTICLEGROUP fil;
    memset(&fil, 0, sizeof(tARTICLEGROUP));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via ArticleNo                       */
/*----------------------------------------------------------------------------*/
size_t
pxArticleGroupList :: Select
(
    const long    ArticleNo,
    const int     count_
)
{
    tARTICLEGROUP fil;
    memset(&fil, 0, sizeof(tARTICLEGROUP));  // zero out entire record buffer
    fil.ArticleNo   = ArticleNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArticleGroupList :: AddToList
(
    const void  *record,
    const int  /* row */
)

{
    // construct new 'pxArticleGroup' object:
    pxArticleGroup *objectp = new pxArticleGroup(Session(), *(tARTICLEGROUP*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArticleGroup :: Get
(
    DBAccessMode mode
)

{
    tARTICLEGROUP record;
    memset(&record, 0, sizeof(tARTICLEGROUP));
    record.ArticleNo   = ArticleNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLEQUOTA struct
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
pxArticleGroup :: Put
(
)
{
    tARTICLEGROUP record;
    memset(&record, 0, sizeof(tARTICLEGROUP));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTICLEGROUP));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArticleGroup :: Delete
(
)
{
    tARTICLEGROUP record;
    memset(&record, 0, sizeof(tARTICLEGROUP));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArticleGroup :: Read
(
    const void  *record
)
{
    return pxArticleGrpRead((tARTICLEGROUP*)record);
}

int
pxArticleGroup :: ReadLock
(
    const void  *record
)
{
    return pxArticleGrpReadLock((tARTICLEGROUP*)record);
}

int
pxArticleGroup :: Update
(
    const void  *record
)
{
    return pxArticleGrpUpdate((tARTICLEGROUP*)record);
}

int
pxArticleGroup :: Delete
(
    const void  *record
)
{
    return pxArticleGrpDelete((tARTICLEGROUP*)record);
}

int
pxArticleGroup :: Insert
(
    const void  *record
)
{
    return pxArticleGrpInsert((tARTICLEGROUP*)record);
}

int
pxArticleGroupList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArticleGrpEndBrowse(cursorid);
}


int
pxArticleGroupList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxArticleGrpGetNext((tARTICLEGROUP*)record, cursorid);
}

int
pxArticleGroupList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArticleGrpStartBrowse((tARTICLEGROUP*)keys, cursorid);
}
