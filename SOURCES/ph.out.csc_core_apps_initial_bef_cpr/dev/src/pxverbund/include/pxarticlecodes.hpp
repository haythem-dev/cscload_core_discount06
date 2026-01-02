/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxArticleCodes Class.

REVISION HISTORY

22 Oct 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTICLECODES_INC
#define PXARTICLECODES_INC

#include "pxbase/pxrecord.hpp"

struct tARTICLECODES;

class pxArticleCodes : public pxDBRecord
{

public:

// constructors:
                pxArticleCodes(pxArticleCodes& src);
                pxArticleCodes(pxSession *session);
                pxArticleCodes(pxSession *session, tARTICLECODES& src);
                pxArticleCodes(pxSession *session, const nString& ArticleCode);
// destructor:
                virtual  ~pxArticleCodes();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArticleCodes&   operator=(const pxArticleCodes& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArticleCodes&   operator=(const tARTICLECODES& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArticleCodes&
                Assign(pxArticleCodes& dest, const tARTICLECODES& src);
    friend   tARTICLECODES&
                Assign(tARTICLECODES& dest, const pxArticleCodes& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

//  Queries:
    long           ArticleNo()             {return ArticleNo_       ;}
    short          CodeType()              {return CodeType_        ;}
    nString&       ArticleCode()           {return ArticleCode_     ;}
    short          PreferredFlag()         {return PreferredFlag_   ;}

//  Updates:

protected:
    void        Init();

    long          ArticleNo_;             // Article Number
    short         CodeType_;              // CodeType
    nString        ArticleCode_;           // ArticleCode
    short         PreferredFlag_;         // PreferredFlag 0/1

private:
    friend class pxArticleCodesList;

};

class pxArticleCodesList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxArticleCodesList(pxSession *session);
//  destructor:
                virtual ~pxArticleCodesList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

//    size_t      Select ( const nString& ArticleCode, const short PreferredFlag = 1, const int count = 50);
//    size_t      Select ( const long ArticleNo, const short PreferredFlag, const int count = 50);
    size_t      SelectPreferred(const long ArticleNo);
    size_t      SelectByCodeType(const long ArticleNo, const short codeType);
	void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxArticleCodesListIter;
};

class pxArticleCodesListIter : public nDListCollectIter
{

public:
// constructors:
    pxArticleCodesListIter(pxArticleCodesList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArticleCodesListIter() {;}
};
#endif
