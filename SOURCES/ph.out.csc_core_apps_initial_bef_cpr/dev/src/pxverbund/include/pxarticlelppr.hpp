/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXARTICLELPPR.HPP
Article reimbursement  Class.

REVISION HISTORY

25 April 2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTICLELPPR_DOTH
   #define PXARTICLELPPR_DOTH

#include "pxbase/pxrecord.hpp"
#include <money.hpp>

struct tARTICLELPPR;

class pxArticleLppr : public pxDBRecord
{

public:
    virtual           ~pxArticleLppr();
                      pxArticleLppr(pxArticleLppr& src);
                      pxArticleLppr(pxSession *session);
                      pxArticleLppr(pxSession *session, long ArticleNo, char Type);

    pxArticleLppr&       operator=(const pxArticleLppr& src);
    pxArticleLppr&       operator=(const tARTICLELPPR& src);

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);

//  Queries:
    long             ArticleNo         () {return ArticleNo_         ; }
    char             ReimbursementType () {return ReimbursementType_ ; }
    nMoney            ReimbursementPrice() {return ReimbursementPrice_; }

//  Updates:
protected:
                      pxArticleLppr(pxSession *session, tARTICLELPPR& src);
    void              Init();
    friend
    pxArticleLppr&       Assign(pxArticleLppr& dest, const tARTICLELPPR& src);
    friend
    tARTICLELPPR&    Assign(tARTICLELPPR& dest, const pxArticleLppr& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    long             ArticleNo_;             // Artikelnummer
    char             ReimbursementType_;     // reimbursementtypee
    nMoney            ReimbursementPrice_;    // Preis Reimburesement

private:
                      pxArticleLppr();
    friend class pxArticleLpprList;
};

class pxArticleLpprList : public nDListCollect, public nDBRecordSet
{

public:
// constructors:
                pxArticleLpprList(pxSession *session);
// destructor:
                virtual  ~pxArticleLpprList() {Clear();}
// member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}
    size_t      Select ( const long   ArticleNo, const char typ,
                         const int    count = 50 );
    size_t      Select ( tARTICLELPPR *a,  const int count = 50 );
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
protected:

private:
    friend class pxArticleLpprListIter;
};

class pxArticleLpprListIter : public nDListCollectIter
{

public:
// constructors:
    pxArticleLpprListIter(pxArticleLpprList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArticleLpprListIter() {;}
};

#endif
