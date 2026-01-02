#ifndef PXARTICLEQUOTA_INC
#define PXARTICLEQUOTA_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>

struct tARTICLEQUOTA;

class pxArticleQuota : public pxDBRecord
{

public:
// constructors:
                pxArticleQuota(pxArticleQuota& src);
                pxArticleQuota(pxSession *session);
                pxArticleQuota(pxSession *session, tARTICLEQUOTA& src);
                pxArticleQuota(pxSession *session, short BranchNo,
                               long CustomerNo, long ArticleNo);
                             //  DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxArticleQuota();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArticleQuota&   operator=(const pxArticleQuota& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArticleQuota&   operator=(const tARTICLEQUOTA& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

    virtual  long    AddQuantity(const long q);
    virtual  long    SubQuantity(const long q);

/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArticleQuota&
                Assign(pxArticleQuota& dest, const tARTICLEQUOTA& src);
    friend   tARTICLEQUOTA&
                Assign(tARTICLEQUOTA& dest, const pxArticleQuota& src);

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
    short            BranchNo()        const {return BranchNo_         ;}
    long             CustomerNo()      const {return CustomerNo_       ;}
    long             ArticleNo()       const {return ArticleNo_        ;}
    long             Quota()           const {return Quota_            ;}
    long             KumQty()          const {return KumQty_           ;}
    char             SDafueQuota()     const {return SDafueQuota_      ;}
    char             Validity()        const {return Validity_         ;}
    const nDate&     DateFrom()        const {return DateFrom_         ;}
    const nDate&     DateTo()          const {return DateTo_           ;}
    const nString&   PharmacyGroupId() const {return PharmacyGroupId_  ;}

    void             SetCustomerNo (const long customerno)  { CustomerNo_ = customerno; }

    int              FindQuotaEntry(DBAccessMode mode = cDBGET_READONLY);

protected:
    void        Init();

    short      BranchNo_         ;       // Branchnumber
    long       CustomerNo_       ;       // Customernumber
    long       ArticleNo_        ;       // Articlenumber
    long       Quota_            ;       // ArticleQuota
    long       KumQty_           ;       // Acumulated quantity
    char       Validity_         ;       // Validity T,M,J
    char       SDafueQuota_      ;       // recognize DafueQuota
    nDate      DateFrom_         ;       // Date from
    nDate      DateTo_           ;       // Date to
    nString    PharmacyGroupId_  ;       // Pharmacy Group Id

private:
    friend class pxArticleQuotaList;
};

class pxArticleQuotaList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxArticleQuotaList(pxSession *session);
//  destructor:
                virtual ~pxArticleQuotaList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int count = 50 );
    size_t      Select ( const short BranchNo, const long CustomerNo,
                         const long  ArticleNo, const int count = 50 );
    size_t      SelectOriginal ( const short BranchNo, const long CustomerNo,
                                 const long  ArticleNo, const int count = 50 );
    size_t      SelectBasic ( const short BranchNo, const long  ArticleNo, const int count = 50 );
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxArticleQuotaListIter;
};

class pxArticleQuotaListIter : public nDListCollectIter
{

public:
// constructors:
    pxArticleQuotaListIter(pxArticleQuotaList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArticleQuotaListIter() {;}
};
#endif
