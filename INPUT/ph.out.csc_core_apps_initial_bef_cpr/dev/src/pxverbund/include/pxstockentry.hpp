#ifndef PXSTOCKENTRY_INC
#define PXSTOCKENTRY_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>

struct tSTOCKENTRY;

class pxStockEntry : public pxDBRecord
{

public:
// constructors:
                pxStockEntry(pxStockEntry& src);
                pxStockEntry(pxSession *session);
                pxStockEntry(pxSession *session, tSTOCKENTRY& src);
                pxStockEntry(pxSession *session,
                         nDate& date, short BranchNo, long ArticleNo,
                         DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxStockEntry();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxStockEntry&   operator=(const pxStockEntry& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxStockEntry&   operator=(const tSTOCKENTRY& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxStockEntry&
                Assign(pxStockEntry& dest, const tSTOCKENTRY& src);
    friend   tSTOCKENTRY&
                Assign(tSTOCKENTRY& dest, const pxStockEntry& src);

    virtual  int     CompareTo(const nCollectable *that, void *p,
                               const long lparm) const;
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

    bool              CheckProcess();
    bool              IsAllReadyActiv();
//  Field updates

//  Queries:
    nDate&            Date()               {return Date_              ;}
    short             BranchNo()           {return BranchNo_          ;}
    long              ArticleNo()          {return ArticleNo_         ;}

protected:
    void        Init();

    nDate       Date_              ;      // Date
    short       BranchNo_          ;      // Branch number
    long        ArticleNo_         ;      // Article number

private:
    friend class pxStockEntryList;
};

class pxStockEntryList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxStockEntryList(pxSession *session);
//  destructor:
                virtual ~pxStockEntryList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxStockEntryListIter;
};

class pxStockEntryListIter : public nDListCollectIter
{

public:
// constructors:
    pxStockEntryListIter(pxStockEntryList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxStockEntryListIter() {;}
};
#endif
