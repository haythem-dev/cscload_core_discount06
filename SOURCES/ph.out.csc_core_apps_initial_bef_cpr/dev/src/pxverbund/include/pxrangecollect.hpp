/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXCALCRANGE.HPP

REVISION HISTORY

05 Jan 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXRANGECOLLECT_DOTH
#define PXRANGECOLLECT_DOTH

#include "types/pricetypeenum.inc"

class pxRangeCollect : public nCollectable
{

public:
// constructors:
                pxRangeCollect(const short  BranchNo,
                               const long   DiscountGrpNo,
                               const long   PosNr,
                               const long   ArtcleNo,
                               const long   Quantity,
                               const long   QtyPack,
                               const long   ManufacturerNo,
                               double       ShipValue,
                               const long   ArtCategoryNo,
                               const PriceTypeEnum  priceType
                              );

                pxRangeCollect(const pxRangeCollect &src);

// destructor:
                virtual  ~pxRangeCollect();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxRangeCollect&   operator=(const pxRangeCollect& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;


// Some Queries
    short         BranchNo()            { return BranchNo_;          }
    long          DiscountGrpNo()       { return DiscountGrpNo_ ;    }
    long          PosNr()               { return PosNr_ ;            }
    long          ArticleNo()           { return ArticleNo_         ;}
    long          Quantity()            { return Quantity_ ;         }
    long          QtyPack()             { return QtyPack_;           }
    long          ManufacturerNo()      { return ManufacturerNo_    ;}
    nMoney        ShipValue()           { return ShipValue_         ;}
    long          ArtCategoryNo()       { return ArtCategoryNo_     ;}
    PriceTypeEnum PreisTyp()            { return PreisTyp_          ;}
    nMoney        InvoiceValue()        { return InvoiceValue_      ;}
    nMoney        NaturalRebateValue()  { return NaturalRebateValue_ ;}

//  Some additional Queries and Settings:
    void        SetInvoiceValue(nMoney value)
                {InvoiceValue_ = value;}
    void        SetNaturalRebateValue(nMoney value)
                {NaturalRebateValue_ = value;}


protected:
    short         BranchNo_;            // Branchno
    long          DiscountGrpNo_;       // discountgroup number
    long          PosNr_;               // positionnummer witin order
    long          ArticleNo_;           // Articlenumber
    long          Quantity_;            // number packages or pieces
    long          QtyPack_;             // Standard Einheit
    long          ManufacturerNo_;      // manufactures number
    nMoney        ShipValue_;           // Ship value of this position
    long          ArtCategoryNo_;       // Article Groupno
    PriceTypeEnum PreisTyp_;            // PreisType
    nMoney        InvoiceValue_;        // Invoice Value of this position
    nMoney        NaturalRebateValue_;  // Rebate Value of this position if MengeNatra > 0

private:
    friend class pxRangeCollectList;
};

class pxRangeCollectList : public nDListCollect
{

public:
// constructors:

// destructor:
                virtual  ~pxRangeCollectList() {Clear();}
// member functions:
    void            Clear();
    long            SumQtyCollect(const long ArticleNo,const long DiscountGrpNo);
    double          SumShipValue( const long ManufactureNo,const long DiscountGrpNo);
    double          SumInvoiceValue(const long DiscountGrpNo);
    double          ArticleSumShipValue(const long ArticleNo,const long DiscountGrpNo);
    pxRangeCollect* Find(const long ArticleNo,const long DiscountGrpNo);
    int             DeleteInvalidEntries( const long DiscountGrpNo, const PriceTypeEnum PreisTyp);

protected:
private:
    friend class pxRangeCollectListIter;
};

class pxRangeCollectListIter : public nDListCollectIter
{

public:
// constructors:
    pxRangeCollectListIter(pxRangeCollectList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxRangeCollectListIter() {;}
};
#endif
