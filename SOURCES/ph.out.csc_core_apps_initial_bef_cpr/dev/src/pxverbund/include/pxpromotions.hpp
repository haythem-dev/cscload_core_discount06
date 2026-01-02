/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

 pxpromotions.hpp
 PROMOTIONS   class

REVISION HISTORY

17 Febr 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXPROMOTIONS_INC
#define PXPROMOTIONS_INC

#include "pxbase/pxrecord.hpp"

struct tPROMOTIONS;

class pxPromotions : public pxDBRecord
{

public:
/*----------------------------------------------------------------------------*/
/*  PromotionType  enumeration.                                               */
/*----------------------------------------------------------------------------*/
enum  tPromoType
{
    PromoType_Manually           = 1,   // Manually Promotion
    PromoType_Target,                   // Target   Promotion
    PromoType_Product,                  // Product  Promotion
    PromoType_Last
};


// constructors:
                pxPromotions(pxPromotions& src);
                pxPromotions(pxSession *session);
                pxPromotions(pxSession *session, tPROMOTIONS& src);
                pxPromotions(pxSession *session, const pxPromotions* src);
                pxPromotions(pxSession *session, const short PromotionNo,
                                 DBAccessMode mode = cDBGET_READONLY );

// destructor:
                virtual  ~pxPromotions();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxPromotions&   operator=(const pxPromotions& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxPromotions&   operator=(const tPROMOTIONS& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxPromotions&
                Assign(pxPromotions& dest, const tPROMOTIONS& src);
    friend   tPROMOTIONS&
                Assign(tPROMOTIONS& dest, const pxPromotions& src);

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
    short           PromotionNo()      const { return PromotionNo_  ;}
    const nString&  PromotionName()    const { return Name_         ;}
    const nString&  Description()      const { return Description_  ;}
    short           PromotionType()    const { return PromotionType_;}
    char            AddOnPromoDiscOk() const { return AddOnPromoDiscOk_;}
    char            AddOnStdDiscOk()   const { return AddOnStdDiscOk_;}
    short           Priority()         const { return Priority_;}
    char            SNotBySaleseWeb()  const { return SNotBySaleseWeb_;}

    bool            IsManuallyPromotion()   const
                    {return PromotionType_ == PromoType_Manually;    }
    bool            IsTargetPromotion()     const
                    {return PromotionType_ == PromoType_Target;      }
    bool            IsProductPromotion()    const
                    {return PromotionType_ == PromoType_Product;     }
    bool            IsSNotBySaleseWeb()    const
                    {return SNotBySaleseWeb_ == '1'; }

// Set Methodes


protected:
    void        Init();

    short      PromotionNo_       ;      // Promotion Number
    nString     Name_              ;      // Name of promotion
    nString     Description_       ;      // Description
        short      PromotionType_;
    char       AddOnPromoDiscOk_;
    char       AddOnStdDiscOk_;
    short      Priority_;
    char       SNotBySaleseWeb_;

private:
    friend class pxPromotionsList;
};

class pxPromotionsList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxPromotionsList(pxSession *session);
//  destructor:
                virtual ~pxPromotionsList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short PromotionNo,
                         const int   count  = 100
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

    friend class pxPromotionsListIter;
};

class pxPromotionsListIter : public nDListCollectIter
{

public:
// constructors:
    pxPromotionsListIter(pxPromotionsList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxPromotionsListIter() {;}
};
#endif
