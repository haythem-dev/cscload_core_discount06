#include "pxarticlecodes.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArticleCodes :: pxArticleCodes
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
pxArticleCodes :: pxArticleCodes
(
    pxArticleCodes& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLECODES structure to construct this instance.             */
/*----------------------------------------------------------------------------*/
pxArticleCodes :: pxArticleCodes
(
    pxSession   *session,
    tARTICLECODES& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleCodes :: pxArticleCodes
(
    pxSession    *session,
    const nString&      ArticleCode         // Article Code
)
    : pxDBRecord(session)
{
    Init();
    ArticleCode_   = ArticleCode;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArticleCodes :: ~pxArticleCodes()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLECODES structure.       */
/*----------------------------------------------------------------------------*/
tARTICLECODES&
Assign
(
    tARTICLECODES&           dest,
    const pxArticleCodes&     src
)
{
    dest.ArticleNo                 = src.ArticleNo_      ;
    dest.Code_Type                 = src.CodeType_       ;
    dest.Article_Code[0] = ' ';
    src.ArticleCode_.GetData(dest.Article_Code)          ;
    dest.Preferred_Flag            = src.PreferredFlag_  ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLECODES structure to                 */
/*  a pxArticleCodes object.                                                  */
/*----------------------------------------------------------------------------*/
pxArticleCodes&
Assign
(
    pxArticleCodes&              dest,
    const tARTICLECODES&         src
)
{
    dest.ArticleNo_                = src.ArticleNo        ;
    dest.CodeType_                 = src.Code_Type        ;
    dest.ArticleCode_              = src.Article_Code     ;
    dest.PreferredFlag_            = src.Preferred_Flag   ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArticleCodes :: Init()
{
    tARTICLECODES    record;
    memset(&record, 0 , sizeof(tARTICLECODES));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTICLECODES struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxArticleCodes&
pxArticleCodes :: operator=( const pxArticleCodes& src)
{
    tARTICLECODES record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLECODES structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArticleCodes&
pxArticleCodes :: operator=( const tARTICLECODES& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArticleCodes :: Get
(
    DBAccessMode mode
)

{
    tARTICLECODES record;
    memset(&record, 0, sizeof(tARTICLECODES));
    record.Article_Code[0] = ' ';
    ArticleCode_.GetData(record.Article_Code);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLECODES struct
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
pxArticleCodes :: Put
(
)
{
    tARTICLECODES record;
    memset(&record, 0, sizeof(tARTICLECODES));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTICLECODES));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArticleCodes :: Delete
(
)
{
    tARTICLECODES record;
    memset(&record, 0, sizeof(tARTICLECODES));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArticleCodes :: Read
(
    const void  *record
)
{
    return pxArticleCodesRead((tARTICLECODES*)record);
}

int
pxArticleCodes :: ReadLock
(
    const void  *record
)
{
    return pxArticleCodesReadLock((tARTICLECODES*)record);
}

int
pxArticleCodes :: Update
(
    const void  *record
)
{
    return pxArticleCodesUpdate((tARTICLECODES*)record);
}

int
pxArticleCodes :: Delete
(
    const void  *record
)
{
    return pxArticleCodesDelete((tARTICLECODES*)record);
}

int
pxArticleCodes :: Insert
(
    const void  *record
)
{
    return pxArticleCodesInsert((tARTICLECODES*)record);
}

int
pxArticleCodesList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArticleCodesEndBrowse(cursorid);
}


int
pxArticleCodesList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxArticleCodesGetNext((tARTICLECODES*)record, cursorid);
}

int
pxArticleCodesList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArticleCodesStartBrowse((tARTICLECODES*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArticleCodes list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxArticleCodes :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxArticleCodes *that = (pxArticleCodes*)That;

    int retval = (ArticleCode_ == that->ArticleCode_) ? 0
                : (ArticleCode_ > that->ArticleCode_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleCodesList :: pxArticleCodesList
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
//size_t
//pxArticleCodesList :: Select
//(
//    const nString& ArticleCode,
//    const short   PreferredFlag,
//    const int    count
//)
//{
//    tARTICLECODES fil;
//    memset(&fil, 0, sizeof(tARTICLECODES));  // zero out entire record buffer
//    fil.Article_Code[0] = ' ';
//    ArticleCode.GetData(fil.Article_Code);
//    fil.Preferred_Flag = PreferredFlag;
//    int cursorid    = cCRS_DEFAULT;
//    nDBSelect(&fil, cursorid, count);
//
//    return Entries();
//}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
//size_t
//pxArticleCodesList :: Select
//(
//    const long    ArticleNo,
//    const short   PreferredFlag,
//    const int    count
//)
//{
//    tARTICLECODES fil;
//    memset(&fil, 0, sizeof(tARTICLECODES));  // zero out entire record buffer
//    fil.ArticleNo = ArticleNo;
//    fil.Preferred_Flag = PreferredFlag;
//    int cursorid    = cCRSARTICLENO;
//    nDBSelect(&fil, cursorid, count);
//
//    return Entries();
//}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records depending on ArticleNo         */
/*----------------------------------------------------------------------------*/
size_t
pxArticleCodesList :: SelectPreferred
(
    const long ArticleNo
)
{
    tARTICLECODES fil;
    memset(&fil, 0, sizeof(tARTICLECODES));  // zero out entire record buffer
    fil.ArticleNo = ArticleNo;
    int cursorid    = cCRSARTICLENO_PREFERRED;
    nDBSelect(&fil, cursorid);
    return Entries();
}

/*----------------------------------------------------------------------------*/
size_t
pxArticleCodesList::SelectByCodeType
(
	const long ArticleNo,
	const short codeType
)
{
	tARTICLECODES fil;
	memset(&fil, 0, sizeof(tARTICLECODES));  // zero out entire record buffer
	fil.ArticleNo = ArticleNo;
	fil.Code_Type = codeType;
	int cursorid = cCRSARTICLENO_CODETYPE;
	nDBSelect(&fil, cursorid);
	return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArticleCodesList :: AddToList
(
    const void  *record,
    const int  /* row */
)

{
    // construct new 'pxArticleCodes' object:
    pxArticleCodes *objectp = new pxArticleCodes(Session(), *(tARTICLECODES*) record);
    InsertAscending(objectp);
    return objectp;
}

