/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXRANGE.HPP
pxRange  class

REVISION HISTORY

08 Feb. 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXRANGE_INC
   #define PXRANGE_INC

#include "pxbase/pxrecord.hpp"

struct tDISCOUNTGRP;

class pxRange : public pxDBRecord
{

public:
/*----------------------------------------------------------------------------*/
/*  DiscountGroupType enumeration.                                            */
/*----------------------------------------------------------------------------*/
    enum  tDiscountGrpType
    {
       DiscGrpType_Range,                // Range   type        = 0
       DiscGrpType_ArticleGroup_C2,      // Gruppe von Artikeln für Kaskade 2 (Serbien)    = 1
       DiscGrpType_ArticleGroup_C5,      // Gruppe von Artikeln für Kaskade 5 (Serbien)    = 2
       DiscGrpType_ArticleGroup_List5,   // Artikel pro Kunde für neue Liste 5 (Bulgarien) = 3
       DiscGrpType_Nomonthlyrebate       // Artikel / Hersteller pro Kunde für Monatsrabattierungsausschluss (Bulgarien) = 4
    };

// constructors:
                pxRange(pxRange& src);
                pxRange(pxSession *session);
                pxRange(pxSession *session, tDISCOUNTGRP& src);
                pxRange(pxSession *session,
                         short  BranchNo,
                         long   DiscountGrpNo);
                pxRange(pxSession *session,
                         short  BranchNo,
                         short  DiscountGrpType,
                         long   CustomerNo);
// destructor:
                virtual  ~pxRange();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxRange&   operator=(const pxRange& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxRange&   operator=(const tDISCOUNTGRP& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxRange&
                Assign(pxRange& dest, const tDISCOUNTGRP& src);
    friend   tDISCOUNTGRP&
                Assign(tDISCOUNTGRP& dest, const pxRange& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Read(const void *record);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

//  Queries:
    short          BranchNo()          {return BranchNo_         ;}
    long           DiscountGrpNo()     {return DiscountGrpNo_    ;}
    nString&        Description()       {return Description_      ;}
    short          DiscountGrpType()   {return DiscountGrpType_  ;}
    long           CustomerNo()        {return CustomerNo_       ;}

//  Some additional Queries:
    bool        IsRange()                      const
                {return DiscountGrpType_ == DiscGrpType_Range;       }
    bool        IsGroupOfArticleC2()             const
                {return DiscountGrpType_ == DiscGrpType_ArticleGroup_C2;}
    bool        IsGroupOfArticleC5()             const
                {return DiscountGrpType_ == DiscGrpType_ArticleGroup_C5;}
    bool        IsArticleGroupList5()             const
                {return DiscountGrpType_ == DiscGrpType_ArticleGroup_List5;}

protected:
    void        Init();

    short      BranchNo_          ;      // Branchnumber
    long       DiscountGrpNo_     ;      // DiscountGroup Number
    nString     Description_       ;      // Description
    short      DiscountGrpType_   ;      // DiscountGreopType
    long       CustomerNo_        ;      // customer number

private:
    friend class pxRangeList;
};

class pxRangeList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxRangeList(pxSession *session);
//  destructor:
                virtual ~pxRangeList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  DiscountGrpNo,
                         const int   count  = 100
                       );
    size_t      Select ( const short BranchNo,
                         const short DiscountGrpType,
                         const long  CustomerNo,
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

    friend class pxRangeListIter;
};

class pxRangeListIter : public nDListCollectIter
{

public:
// constructors:
    pxRangeListIter(pxRangeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxRangeListIter() {;}
};
#endif
