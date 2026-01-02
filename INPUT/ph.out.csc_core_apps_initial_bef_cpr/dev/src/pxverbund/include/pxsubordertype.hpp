/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXSUBORDERTYPE.HPP
SubOrdertyp DiscountList Class
REVISION HISTORY

24 November 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXSUBORDERTYPE_INC
#define PXSUBORDERTYPE_INC

#include "pxbase/pxrecord.hpp"

struct tDISCOUNTLIST;

class pxSubOrderType : public pxDBRecord
{

public:

// constructors:
                pxSubOrderType(pxSubOrderType& src);
                pxSubOrderType(pxSession *session);
                pxSubOrderType(pxSession *session, tDISCOUNTLIST& src);
                pxSubOrderType(pxSession *session, nString& OrderType, nString& SubOrderType);
// destructor:
                virtual  ~pxSubOrderType();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxSubOrderType&   operator=(const pxSubOrderType& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxSubOrderType&   operator=(const tDISCOUNTLIST& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxSubOrderType&
                Assign(pxSubOrderType& dest, const tDISCOUNTLIST& src);
    friend   tDISCOUNTLIST&
                Assign(tDISCOUNTLIST& dest, const pxSubOrderType& src);

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);

//  Queries:
    nString&        OrderType()         {return OrderType_       ;}
    nString&        SubOrderType()      {return SubOrderType_    ;}
    nString&        PharmacyGroupId()   {return PharmacyGroupId_ ;}
    nString&        PaymentTerm()       {return PaymentTerm_     ;}
    short           ValutaDays()        {return ValutaDays_      ;}

//  Field Updates:
protected:
    void        Init();

    nString     OrderType_         ;      // ordertype
    nString     SubOrderType_      ;      // subordertype
    nString     PharmacyGroupId_   ;      // pharmacygroupid
    nString     PaymentTerm_       ;      // payment terms
    double      MonthlyDiscPct_    ;      // monthly discount percentage
    short       ValutaDays_        ;      // count of valutadays
private:
};
#endif
