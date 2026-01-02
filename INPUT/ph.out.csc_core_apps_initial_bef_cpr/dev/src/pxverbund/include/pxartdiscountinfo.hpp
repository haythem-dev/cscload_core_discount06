/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXARTDISCOUNTINFO.HPP
Get rebates for a given Customer and a given article number

REVISION HISTORY

01 February 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTDISCOUNTINFO_INC
#define PXARTDISCOUNTINFO_INC

#include "types/pricetypeenum.inc"

class pxSession;
class pxCustBase;
class pxOrder;
class pxOrderItem;
class pxDiscountList;

class pxArtDiscountInfo
{

public:
// constructors:
                      pxArtDiscountInfo(pxSession *session);


// destructor:
    virtual           ~pxArtDiscountInfo();

// public member operators
    pxArtDiscountInfo&    operator=(const pxArtDiscountInfo& src);

// public member functions


    pxSession * Session();
    pxDiscountList*    GetDiscountList(const short BranchNo, const long CustomerNo, const long ArticleNo, const PriceTypeEnum pricetype = FREESALE_PRICE, const long Quantity=1000);
    pxDiscountList*    GetPromotionList(const short BranchNo, const long CustomerNo, const long ArticleNo, const PriceTypeEnum pricetype = FREESALE_PRICE);

//  Field updates
    void              BranchNo( short BranchNo)   {BranchNo_  = BranchNo;     }
    void              ArtikelNr( long ArticleNo)  {ArticleNo_ = ArticleNo;    }

// Queries:
             short        BranchNo   () const {return BranchNo_           ;}
             long         ArticleNo  () const {return ArticleNo_          ;}
             long         CustomerNo () const {return CustomerNo_         ;}
             pxOrderItem* Item       () const {return Item_               ;}
             pxOrder*     Order      () const {return Order_              ;}
             pxCustBase*  Customer   () const {return Customer_           ;}
protected:
                      pxArtDiscountInfo();

    void              Init();

    bool setCustomer(const short branchNo, const long customerNo);
    bool setPseudoOrder();
    bool setOrderItem(const long articleNo, const PriceTypeEnum pricetype, const long quantity);

/*----------------------------------------------------------------------------*/
/*  Data members.                                                             */
/*----------------------------------------------------------------------------*/
    short             BranchNo_;           // BranchNo
    long              ArticleNo_;          // ArticleNo
    long              CustomerNo_;         // CustomerNo
    pxSession*        Session_;            // ptr Session
    pxOrderItem*      Item_;               // ptr to current order item
    pxOrder*          Order_;              // ptr to current order
    pxCustBase*       Customer_;           // ptr to current customer

private:
};
#endif
