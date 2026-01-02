/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXARTOLDPRICE.HPP
Article Old Price Class.

REVISION HISTORY

20 March 2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTOLDPRICE_DOTH
   #define PXARTOLDPRICE_DOTH

#include "pxbase/pxrecord.hpp"
#include <money.hpp>

struct tARTICLEOLDPRICE;

class pxArtOldPrice : public pxDBRecord
{

public:
    virtual           ~pxArtOldPrice();
                      pxArtOldPrice(pxArtOldPrice& src);
                      pxArtOldPrice(pxSession *session);
                      pxArtOldPrice(pxSession *session, short BranchNo, long ArticleNo);

    pxArtOldPrice&       operator=(const pxArtOldPrice& src);
    pxArtOldPrice&       operator=(const tARTICLEOLDPRICE& src);

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

//  Queries:
    short            BranchNo          () {return BranchNo_         ; }
    long             ArticleNo         () {return ArticleNo_        ; }
    nMoney            PreisEKApo        () {return PreisEKApo_       ; }
    nMoney            PreisVKApo        () {return PreisVKApo_       ; }
    nMoney            PreisEKGrosso     () {return PreisEKGrosso_    ; }
    nMoney            PreisEKGrossoNA   () {return PreisEKGrossoNA_  ; }

//  Updates:
    void              PreisEKApo(double aep){ PreisEKApo_ = aep; SetDirty();}
    void              PreisVKApo(double avp){ PreisVKApo_ = avp; SetDirty();}
    void              PreisEKGrosso(double gep){ PreisEKGrosso_ = gep; SetDirty();}
    void              PreisEKGrossoNA(double gepna){ PreisEKGrossoNA_ = gepna; SetDirty();}
protected:
                      pxArtOldPrice(pxSession *session, tARTICLEOLDPRICE& src);
    void              Init();
    friend
    pxArtOldPrice&       Assign(pxArtOldPrice& dest, const tARTICLEOLDPRICE& src);
    friend
    tARTICLEOLDPRICE&    Assign(tARTICLEOLDPRICE& dest, const pxArtOldPrice& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    short            BranchNo_;              // BranchNo
    long             ArticleNo_;             // Artikelnummer
    nMoney            PreisEKApo_;            // Preis EK Apotheke
    nMoney            PreisEKGrosso_;         // Preis EK Grosso
    nMoney            PreisEKGrossoNA_;       // Preis EK Grosso Nettoaktion
    nMoney            PreisVKApo_;            // Preis VK Apotheke

private:
                      pxArtOldPrice();
    friend class pxArtOldPriceList;
};

class pxArtOldPriceList : public nDListCollect, public nDBRecordSet
{

public:
// constructors:
                pxArtOldPriceList(pxSession *session);
// destructor:
                virtual  ~pxArtOldPriceList() {Clear();}
// member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}
    size_t      Select ( const short BranchNo, const long ArticleNo,
                         const int   count = 50 );
    size_t      Select ( tARTICLEOLDPRICE *a,  const int count = 50 );
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
protected:

private:
    friend class pxArtOldPriceListIter;
};

class pxArtOldPriceListIter : public nDListCollectIter
{

public:
// constructors:
    pxArtOldPriceListIter(pxArtOldPriceList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArtOldPriceListIter() {;}
};

#endif
