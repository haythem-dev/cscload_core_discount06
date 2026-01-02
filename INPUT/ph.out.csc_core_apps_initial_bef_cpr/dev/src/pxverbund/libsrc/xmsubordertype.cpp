#include "pxxmit.hpp"
#include "pxcstbas.hpp"
#include "pxcstot.hpp"
#include "pxcustdisccondition.hpp"
#include "pxsubordertype.hpp"
#include "pxorder.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  SubOrderType:                                                             */
/*  Cases:        OrderType = "  "                                            */
/*                Open Order as Normal Order                                  */
/*                OrderType != "  " and SubOrderType = "   "                  */
/*                Check duty Flag on OrderType Tableentry                     */
/*                If 1 , we need a SubOrderType, so this methode returns a    */
/*                Nil Pointer                                                 */
/*                If 0 , open Order with give OrderType                       */
/*                OrderType != "  " and SubOrderType != "   "                 */
/*                Check OrderType and SubOrderType against table              */
/*                cstdiscountcont. If no entry found, return a Nil Pointer    */
/*                otherwise, open Order with given OrderType                  */
/* Take care on a well constructed  pxOrderTransmit object, if no Customer    */
/* available, a Nil pointer returns.                                          */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderTransmit :: SubOrderType
(
    const nString& Ot,
    const nString& SubOrderType,
    const long DeliveryDate
)
{
    short   BranchNo;
    nString ordertype(Ot);                          // beware constantnous
    nString subordertype(SubOrderType);                    // beware constantnous
    ordertype.Strip();                                     // delete leading and trailing blanks
    subordertype.Strip();                                  // delete leading and trailing blanks
    pxOrder*   order = NULL;

    // check customer
    if ( Customer_ == NULL )                               // No Customer
    {
        ExternalError(CMsgStream(), CMSG_XMIT_NO_CUSTOMER_AVAILABLE);
       return NULL;
    }

    // is DeliveryDate available ?
    if ( DeliveryDate > 0 )
    {
       SetDeliveryDate(DeliveryDate);
    }

    if ( !ordertype.IsEmpty())
    {
       pxCustOrderType *ot = Customer()->OrderTypeList()->Find(ordertype,Customer()->Vertriebszentrum(),Customer()->KundenNr());
       if (ot)
       {
          if (!ot->IsValidViaDCT() )
          {
             ExternalError(CMsgStream(), CMSG_XMIT_ORDERTYPE_NOT_NOT_ALLOWED,ordertype());
             return NULL;
          }
       }
       else
       {
          ExternalError(CMsgStream(), CMSG_XMIT_ORDERTYPE_NOT_NOT_ALLOWED,ordertype());
          return NULL;
       }
    }

    // check OrderType
    if ( ordertype.IsEmpty() )                             // = there is no ordertype
    {
        if ((order =  OrderType("NO", "0") ))         // open order NO or standardot
        {
           ordertype = order->KdAuftragArt();
        }
        else
        {
           return NULL;
        }
    }

    BranchNo = Customer_->Vertriebszentrum();              // BranchNo
    pxOrderType  otp(Session(), ordertype, BranchNo);
    if ( otp.Get() )                                       // No entry found
    {
        return OrderType("NO", "0");                // open order NO  (removed #define from libumk!)
    }

    if ( subordertype.IsEmpty() )                          // no subordertype
    {
       if ( !otp.IsMustSubOrder() )                         // OrderType and SubOrderType belong together
       {
          if (order )                                       // already opened ??
          {
              return order;
          }
          return OrderType(ordertype,"0");                  // open order
       }
    }

    // now ordertype is available and subordertype may be available
    if ( Customer_->DiscountConditions(ordertype,subordertype) ) // check customers discountconditions
    {
        Error() = (Customer_->Error() ) ;                   // copy error
        return  NULL;
    }

    if ( order == NULL )
    {
       order = OrderType(ordertype,"0");                    // open order
    }
    if ( order )
    {
        nString csubot = Customer_->CustDiscCondition()->SubOrderType();
        csubot.Strip();
        order->SetSubOrderType( csubot);
        nString cpaymentterm = Customer_->CustDiscCondition()->PaymentTerm();
        nString paymentterm  = Customer_->SubOrderType()->PaymentTerm();
        cpaymentterm.Strip();
        paymentterm.Strip();
        order->SetPaymentTerm( paymentterm);
        if ( !cpaymentterm.IsEmpty() )
          order->SetPaymentTerm( cpaymentterm);
    }
    return order;                                           // return order
}

/*----------------------------------------------------------------------------*/
/*  SubOrderType:                                                             */
/*  Cases:        OrderType = "  "                                            */
/*                Open Order as Normal Order                                  */
/*                OrderType != "  " and SubOrderType = "   "                  */
/*                Check duty Flag on OrderType Tableentry                     */
/*                If 1 , we need a SubOrderType, so this methode returns a    */
/*                Nil Pointer                                                 */
/*                If 0 , open Order with give OrderType                       */
/*                OrderType != "  " and SubOrderType != "   "                 */
/*                Check OrderType and SubOrderType against table              */
/*                cstdiscountcont. If no entry found, return a Nil Pointer    */
/*                otherwise, open Order with given OrderType                  */
/* Take care on a well constructed  pxOrderTransmit object, if no Customer    */
/* available, a Nil pointer returns.                                          */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderTransmit :: SubOrderType
(
    const nString& Ot,
    const nString& number,
    const char St,
    const char Bt,
    const OriginTypeEnum bs,
    const nString& SubOrderType,
    const long DeliveryDate,
    const nString& desiredTour
)
{
    short   BranchNo;
    nString ordertype(Ot);			                       // beware constantnous
    nString reference(number);			                    // beware constantnous
    nString subordertype(SubOrderType);                    // beware constantnous
    ordertype.Strip();                                     // delete leading and trailing blanks
    reference.Strip();                                     // delete leading and trailing blanks
    subordertype.Strip();                                  // delete leading and trailing blanks

    char shippingtype = St;                          // beware constantnous
    char bookingtype = Bt;                          // beware constantnous
	OriginTypeEnum batchschreiben = bs;
    pxOrder*   order = NULL;

    // check customer
    if ( Customer_ == NULL )                               // No Customer
    {
        ExternalError(CMsgStream(), CMSG_XMIT_NO_CUSTOMER_AVAILABLE);
       return NULL;
    }
    // is DerliveryDate available ?
    if ( DeliveryDate > 0 )
    {
       SetDeliveryDate(DeliveryDate);
    }


    if ( !ordertype.IsEmpty())
    {
       pxCustOrderType *ot = Customer()->OrderTypeList()->Find(ordertype,Customer()->Vertriebszentrum(),Customer()->KundenNr());
       if (ot)
       {
          if (!ot->IsValidViaDCT() )
          {
             ExternalError(CMsgStream(), CMSG_XMIT_ORDERTYPE_NOT_NOT_ALLOWED,ordertype());
             return NULL;
          }
       }
       else
       {
          ExternalError(CMsgStream(), CMSG_XMIT_ORDERTYPE_NOT_NOT_ALLOWED,ordertype());
          return NULL;
       }
    }

    // check OrderType
    if ( ordertype.IsEmpty() )                             // = there is no ordertype
    {
        if ((order =  OrderType("NO", "0") ))         // open order NO or standardot  (removed #define from libumk!)
        {
           ordertype = order->KdAuftragArt();
        }
        else
        {
           return NULL;
        }
    }

    BranchNo = Customer_->Vertriebszentrum();              // BranchNo
    pxOrderType  otp(Session(), ordertype, BranchNo);
    if ( otp.Get() )                                       // No entry found
    {
        return OrderType("NO", "0");                       // open order NO (removed #define from libumk!) 
    }

    if ( subordertype.IsEmpty() )                          // no subordertype
    {
       if ( !otp.IsMustSubOrder() )                         // OrderType and SubOrderType belong together
       {
          if (order )                                       // already opened ??
          {
              return order;
          }
          return OrderType(ordertype,reference,shippingtype,bookingtype,batchschreiben, 0, desiredTour);                  // open order
       }
    }

    // now ordertype is available and subordertype may be available
    if ( Customer_->DiscountConditions(ordertype,subordertype) ) // check customers discountconditions
    {
        Error() = (Customer_->Error() ) ;                   // copy error
        return  NULL;
    }

    if ( order == NULL )
    {
       order = OrderType(ordertype,reference,shippingtype,bookingtype,batchschreiben, 0, desiredTour);                  // open order
    }
    if ( order )
    {
        nString csubot = Customer_->CustDiscCondition()->SubOrderType();
        csubot.Strip();
        order->SetSubOrderType( csubot);
        nString cpaymentterm = Customer_->CustDiscCondition()->PaymentTerm();
        nString paymentterm  = Customer_->SubOrderType()->PaymentTerm();
        cpaymentterm.Strip();
        paymentterm.Strip();
        order->SetPaymentTerm( paymentterm);
        if ( !cpaymentterm.IsEmpty() )
          order->SetPaymentTerm( cpaymentterm);
    }
    return order;                                           // return order
}
