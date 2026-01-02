/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxarticlegroup.hpp
ARTICLEGROUP  class

REVISION HISTORY

14 May 2009 V1.00 REV 00 written by Beatrix Trömel.
*/

#ifndef PXARTICLEGROUP_INC
#define PXARTICLEGROUP_INC

#include "pxbase/pxrecord.hpp"

struct tARTICLEGROUP;

class pxArticleGroup : public pxDBRecord
{

public:

// constructors:
                pxArticleGroup(pxArticleGroup& src);
                pxArticleGroup(pxSession *session);
                pxArticleGroup(pxSession *session, tARTICLEGROUP& src);
                pxArticleGroup(pxSession *session, const pxArticleGroup* src);

// destructor:
                virtual  ~pxArticleGroup();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArticleGroup&   operator=(const pxArticleGroup& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArticleGroup&   operator=(const tARTICLEGROUP& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArticleGroup&
                Assign(pxArticleGroup& dest, const tARTICLEGROUP& src);
    friend   tARTICLEGROUP&
                Assign(tARTICLEGROUP& dest, const pxArticleGroup& src);

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
    long           ArticleNo()     {return ArticleNo_             ;}
    long           ArtCategoryNo() {return ArtCategoryNo_     ;}

// Set Methodes


protected:
    void        Init();

    long       ArticleNo_         ;      // Article number
    long       ArtCategoryNo_     ;      // Article category number

private:
    friend class pxArticleGroupList;
};

class pxArticleGroupList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxArticleGroupList(pxSession *session);
//  destructor:
                virtual ~pxArticleGroupList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long ArticleNo,
                         const int  count  = 100
                       );

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxArticleGroupListIter;
};

class pxArticleGroupListIter : public nDListCollectIter
{

public:
// constructors:
    pxArticleGroupListIter(pxArticleGroupList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArticleGroupListIter() {;}
};
#endif
