/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

 pxpromotions.hpp
 PROMOTIONSCALE   class

REVISION HISTORY

20 March 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXPROMOTIONSCALE_INC
   #define PXPROMOTIONSCALE_INC

#include "pxbase/pxrecord.hpp"

struct tPROMOTIONSCALE;

class pxPromotionScale : public pxDBRecord
{

public:

// constructors:
                pxPromotionScale(pxPromotionScale& src);
                pxPromotionScale(pxSession *session);
                pxPromotionScale(pxSession *session, tPROMOTIONSCALE& src);
                pxPromotionScale(pxSession *session, const pxPromotionScale* src);
                pxPromotionScale(pxSession *session, const short PromotionNo,
                                 DBAccessMode mode = cDBGET_READONLY );

// destructor:
                virtual  ~pxPromotionScale();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxPromotionScale&   operator=(const pxPromotionScale& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxPromotionScale&   operator=(const tPROMOTIONSCALE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxPromotionScale&
                Assign(pxPromotionScale& dest, const tPROMOTIONSCALE& src);
    friend   tPROMOTIONSCALE&
                Assign(tPROMOTIONSCALE& dest, const pxPromotionScale& src);

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
    long           BasePromotion()       { return BasePromotion_  ;}
    short          PromotionNo()         { return PromotionNo_    ;}

// Set Methodes


protected:
    void        Init();

    long       BasePromotion_       ;      // Base Promotion Number
    short      PromotionNo_         ;      // Promotion Number

private:
    friend class pxPromotionScaleList;
};

class pxPromotionScaleList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxPromotionScaleList(pxSession *session);
//  destructor:
                virtual ~pxPromotionScaleList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short PromotionNo,
                         const int   count  = 100
                       );
    size_t      Select ( const long  BasePromotion,
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

    friend class pxPromotionScaleListIter;
};

class pxPromotionScaleListIter : public nDListCollectIter
{

public:
// constructors:
    pxPromotionScaleListIter(pxPromotionScaleList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxPromotionScaleListIter() {;}
};
#endif
