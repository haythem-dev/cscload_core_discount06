/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXORDERCRITERIA.HPP
OrderCriteria class

REVISION HISTORY

16 Oct 2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXORDERCRITERIA_INC
   #define PXORDERCRITERIA_INC

#include "pxbase/pxrecord.hpp"

struct tORDERCRITERIA;

class pxOrderCriteria : public pxDBRecord
{
    #include "pxordercriteriadefs.h"

public:

// constructors:
                pxOrderCriteria(pxOrderCriteria& src);
                pxOrderCriteria(pxSession *session);
                pxOrderCriteria(pxSession *session, tORDERCRITERIA& src);
                pxOrderCriteria(pxSession *session,
                                short  BranchNo,
                                long  ArticleNo);
// destructor:
                virtual  ~pxOrderCriteria();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderCriteria&   operator=(const pxOrderCriteria& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderCriteria&   operator=(const tORDERCRITERIA& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderCriteria&
                Assign(pxOrderCriteria& dest, const tORDERCRITERIA& src);
    friend   tORDERCRITERIA&
                Assign(tORDERCRITERIA& dest, const pxOrderCriteria& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Read(const void *record);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
   // virtual  long    AddQuantity(const long q, const int id = 0, const int key = 0);
   // virtual  long    SubQuantity(const long q, const int id = 0, const int key = 0);

//  Queries:
    short          BranchNo()          {return BranchNo_              ;}
    long           ArticleNo()         {return ArticleNo_             ;}
    long           ManufacturerNo()    {return ManufacturerNo_        ;}
    nString&        PharmacyGroupId()   {return PharmacyGroupId_       ;}
    long           CustomerNo()        {return CustomerNo_            ;}
    nString&        OrderType()         {return OrderType_             ;}
    long           MinOrderQty()       {return MinOrderQty_           ;}
    double        MinOrderValue()     {return MinOrderValue_         ;}
    nString&        LimitAction()       {return LimitAction_           ;}
    long           AddOnChargeArtNo()  {return AddOnChargeArtNo_      ;}
    double        AddOnChargePct()    {return AddOnChargePct_        ;}

//  Some additional Queries:
    bool            IsZeroing()               {return LimitAction_ == "00";   }
    bool            IsRoundupToLimit()        {return LimitAction_ == "01";   }
    bool            IsCalcAddOnCharge()       {return LimitAction_ == "02";   }
    bool            IsForceRework()           {return LimitAction_ == "03";   }
    bool            IsCalcAddOnChargeArtNo()  {return LimitAction_ == "04";   }

// Set Methodes


protected:
    void        Init();

    short      BranchNo_          ;      // Branchnumber
    long       ArticleNo_         ;      // Articlenumber
    long       ManufacturerNo_    ;      // ManufacturerNo(Herstellernummer)
    nString     PharmacyGroupId_   ;      // Pharmacy Group Id
    long       CustomerNo_        ;      // Customerno
    nString     OrderType_         ;      // OrderType
    long       MinOrderQty_       ;      // Minimum Order Quantity
    double    MinOrderValue_     ;      // Minimum Order Value
    nString     LimitAction_       ;      // Limit Action
    nString     ActionRestriction_ ;      // Action Restriction
    long       AddOnChargeArtNo_  ;      // AddOnCharge ArticleNo
    double    AddOnChargePct_    ;      // AddOnCharge Percentage

private:
    friend class pxOrderCriteriaList;
};

class pxOrderCriteriaList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxOrderCriteriaList(pxSession *session);
//  destructor:
                virtual ~pxOrderCriteriaList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  ArticleNo,
                         const int   count  = 100
                       );

    size_t      Select ( const short BranchNo,
                         const long  ArticleNo,
                         const nString& OrderType,
                         const nString& PharmacyGroupId,
                         const int   count  = 100
                       );

    size_t      SelectAddOnChargeArtNo ( const short BranchNo,
                         const long  CustomerNo,
                         const nString& OrderType,
                         const nString& LimitAction,
                         const int   count  = 100
                       );

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}

    pxOrderCriteria* Find(const long CustomerNo );


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxOrderCriteriaListIter;
};

class pxOrderCriteriaListIter : public nDListCollectIter
{

public:
// constructors:
    pxOrderCriteriaListIter(pxOrderCriteriaList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOrderCriteriaListIter() {;}
};
#endif
