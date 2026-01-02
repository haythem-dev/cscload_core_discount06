/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxArticleCharge Class.

REVISION HISTORY

04 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTICLECHARGE_INC
#define PXARTICLECHARGE_INC

#include "pxbase/pxrecord.hpp"
#include "types/batchstatusenum.inc"
#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>

struct tARTICLECHARGE;

class pxArticleCharge : public pxDBRecord
{

public:
/*----------------------------------------------------------------------------*/
/*  Enumerations and manifest constants.                                      */
/*----------------------------------------------------------------------------*/
//     enum BatchSaleability // enum for batch status flags (SH,2012-05-25)
//     {
// 		cBatchNotYetBooked			= '1',	// 1 = WE / noch nicht aktiv
// 		cBatchSaleable				= '2',	// 2 = Abverkauf möglich
// 											// [3 = gibt es nicht mehr]
// 		cBatchSold					= '4',	// 4 = Artikel ist abverkauft
// 		cBatchRecall				= '5',	// 5 = Quarantäne (Chargenrückruf) 
// 		cBatchMissingCertificate	= '8',	// 8 = Quarantäne (Zertifikat fehlt)
// 		cBatchOverStock				= '9',	// 9 = Übervorrat
// 											// ab hier Prewhole (dynamisch!), z.B.
// 		cBatchQuarantinePrewhole	= 'D'	// D = Quarantäne Prewhole
//     };

// constructors:
                pxArticleCharge(pxArticleCharge& src);
                pxArticleCharge(pxSession *session);
                pxArticleCharge(pxSession *session, tARTICLECHARGE& src);
                pxArticleCharge(pxSession *session, const short BranchNo,
                                     const long ArticleNo,
                                     const basar::VarString& ChargenNr);
// destructor:
                virtual  ~pxArticleCharge();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArticleCharge&   operator=(const pxArticleCharge& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArticleCharge&   operator=(const tARTICLECHARGE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArticleCharge&
                Assign(pxArticleCharge& dest, const tARTICLECHARGE& src);
    friend   tARTICLECHARGE&
                Assign(tARTICLECHARGE& dest, const pxArticleCharge& src);

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
    virtual  long    AddQuantity(const long q);
    virtual  long    SubQuantity(const long q);
    virtual  long    SetQuantity(const long q);

//  Queries:
    short                   BranchNo() const             {return BranchNo_        ;}
    long                    ArticleNo() const            {return ArticleNo_       ;}
    const basar::Date&      ExpiryDate() const           {return ExpiryDate_      ;}
    const basar::VarString& ChargenNr() const            {return ChargenNr_       ;}
    long                    Stock() const                {return Stock_           ;}
    BatchStatusEnum         StateCharge() const;

//  Updates:
    void           SetExpiryDate(const basar::Date& date)  {ExpiryDate_ = date;}
    void           SetStock(const long qty)                {Stock_ = qty;}
    void           SetStateCharge(const BatchStatusEnum status);

protected:
    void        Init();

    short            BranchNo_;              // Filialnummer
    long             ArticleNo_;             // Article Number
    basar::Date      ExpiryDate_;            // Expirydate
    basar::VarString ChargenNr_;             // Chargennummer
    long             Stock_;                 // Quantity on Stock
    char             StateCharge_;           // State of charge

private:
    friend class pxArticleChargeList;

};

class pxArticleChargeList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxArticleChargeList(pxSession *session);
//  destructor:
                virtual ~pxArticleChargeList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short BranchNo, const long ArticleNo);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxArticleChargeListIter;
};

class pxArticleChargeListIter : public nDListCollectIter
{

public:
// constructors:
    pxArticleChargeListIter(pxArticleChargeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArticleChargeListIter() {;}
};
#endif
