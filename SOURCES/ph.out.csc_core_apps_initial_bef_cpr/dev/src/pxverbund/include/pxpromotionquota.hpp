/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxpromotionquota.hpp
PROMOTIONQUOTA class

REVISION HISTORY

16 Dec 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXPROMOTIONQUOTA_INC
   #define PXPROMOTIONQUOTA_INC

#include "pxbase/pxrecord.hpp"

struct tPROMOTIONQUOTA;

class pxPromotionQuota : public pxDBRecord
{

public:


    enum QuotaEntyUsage                  // which quota entry should be used
    {
        UseBranchEntry     = 1,         // just reflect branch promoquota entry
        UseCustomerEntry,               // just reflect customer promoquota entry
        UseBothEntries                  // reflect branch and customer promoquota entry
    };


// constructors:
                pxPromotionQuota(pxPromotionQuota& src);
                pxPromotionQuota(pxSession *session);
                pxPromotionQuota(pxSession *session, tPROMOTIONQUOTA& src);
                pxPromotionQuota(pxSession *session, const pxPromotionQuota* src);
                pxPromotionQuota(pxSession *session, short BranchNo,
                                                 short  PromotionNo);

// destructor:
                virtual  ~pxPromotionQuota();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxPromotionQuota&   operator=(const pxPromotionQuota& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxPromotionQuota&   operator=(const tPROMOTIONQUOTA& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxPromotionQuota&
                Assign(pxPromotionQuota& dest, const tPROMOTIONQUOTA& src);
    friend   tPROMOTIONQUOTA&
                Assign(tPROMOTIONQUOTA& dest, const pxPromotionQuota& src);

    virtual  long    AddSoldQtyBranch(const long q);
    virtual  long    SubSoldQtyBranch(const long q);

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

// Update Fields

//  Queries:
    short          BranchNo()           {return BranchNo_             ;}
    short          PromotionNo()        {return PromotionNo_          ;}
    long           BranchQuotaQty()     {return BranchQuotaQty_       ;}
    long           CustomerQuotaQty()   {return CustomerQuotaQty_     ;}
    long           SoldQtyBranch()      {return SoldQtyBranch_        ;}
    char           Upd_Flag()           {return Upd_Flag_             ;}
    long           ArticleNo()          {return ArticleNo_            ;}
    long           CustomerMinQty()     {return CustomerMinQty_       ;}

// Set Methodes
    short          CheckPromoQuotaUsage();    // check how to use promoquota
    void            ForceUpdate()       {SetActive();}

protected:
    void        Init();

    short      BranchNo_           ;      // Branch Number
    short      PromotionNo_        ;      // PromotionNo
    long       BranchQuotaQty_     ;      // Branch promotion Quota
    long       CustomerQuotaQty_   ;      // Customer promotion Quota
    long       SoldQtyBranch_      ;      // SoldQtyBranch
    char       Upd_Flag_           ;      //
    long       ArticleNo_          ;      // Articlenumber
    long       CustomerMinQty_     ;      // CustomerMinQuantity


private:
    friend class pxPromotionQuotaList;
};

class pxPromotionQuotaList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxPromotionQuotaList(pxSession *session);
//  destructor:
                virtual ~pxPromotionQuotaList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const short PromotionNo,
                         const long ArticleNo,
                         const int   count  = 1000
                       );
// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}

    pxPromotionQuota* Find(const long ArticleNo );

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxPromotionQuotaListIter;
};

class pxPromotionQuotaListIter : public nDListCollectIter
{

public:
// constructors:
    pxPromotionQuotaListIter(pxPromotionQuotaList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxPromotionQuotaListIter() {;}
};
#endif
