/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Internal order item posting methods for a stocked product.

REVISION HISTORY

27 January 2010 V1.00 REV 00 written by Ysbrand Bouma
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcstpaymentterms.hpp"
#include "pxorder.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxdebitlimit.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/* CheckCreditLimitK2: This methode checks customers creditlimit                */
/* OldValue is the Value of the previous booking. On new item, this value     */
/* zero, but on position change we must take care of the previous booking     */
/* value.                                                                     */
/* The variable diffValue will be returned: > 0.0 = Limit exceeded, otherwise */
/* this methode waits for the next position.                                  */
/* This methode checks all articl, alse List5 article.                                  */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: CheckCreditLimitK2
(
    nMoney   OldValue
)
{
    pxCustBase                  *customer = Order().Customer();  // customer
    const pxCustOrderType&             ot = Order().OrderType();
    pxOrder&                        order = Order();
    pxCstPaymentTermsList*  cPayTermsList = customer->CstPaymentTermsList();

    pxDebitLimit*       debtlimit = NULL;                // customers debtlimit entry pointer
    double                  Qty = (double) (MengeGeliefert_ + MengeVerbund() - MengeNatra_);
    nMoney              thisValue = Qty * InvoiceValue() * (1 + (SalesTaxRate_/100));
    nMoney              newValue;
    nMoney              diffValue = pxConstants::mZero;
    // unused variable
    // nMoney          ordGrossValue = pxConstants::mZero;
    bool          QIncrease = false;

/*----------------------------------------------------------------------------*/
/*  do some sanity checks                                                     */
/*----------------------------------------------------------------------------*/
   // if ( !device->IsVideo() )           // only for manually order entry
   //    return pxConstants::mZero;

    if (!Session()->isBulgaria()) // calcultion differs from other countries
          return pxConstants::mZero;
    // SR-15068713
    if ( order.IsNoCreditLimitCheck() )
    {
        return pxConstants::mZero;
    }

    if ( order.IsPseudoLock() )          // info order or proforma order
    {
       if ( order.IsBGInfoOrder() )     // if info order, no limit check
       {
          return pxConstants::mZero;
       }
    }

    if ( order.isCashOrder()  ||  ot.IsDiscountAccount() || ot.IsManualPromotion() || ot.IsRetailSalesOrder() ) // does not affect CO and RO and MP and EH
    {
       ClearUpdateDebtlimitK2();
       return pxConstants::mZero;
    }

    if ( cPayTermsList == NULL && order.DatumValuta() == pxConstants::NullDate )
    {
       return pxConstants::mZero;      // cash payer
    }

    debtlimit = customer->DebitLimitK2(); // get pointer to customers debtlimit entry
    if ( debtlimit == NULL )
       return pxConstants::mZero;

    if ( OldValue > pxConstants::mZero && !customer->IsCashPayer( PreisTypSaved_, &order))
    {
       debtlimit->DecreaseDayTurnOver(Order().GetOrderValuesDebtlimit());
       debtlimit->Put();
       Order().SetUpdateDebtlimitK2();
    }

   /*/ temporary until K1 is available
    if (IsArticleListFiveMember() )
    {
       return pxConstants::mZero;      //  liste 5
    }
   */
    if ( cPayTermsList )
    {
        pxCstPaymentTerms* cPayTerms = cPayTermsList->Find( PreisTyp_);
       if (cPayTerms)
       {
          if ( cPayTerms->PaymentTarget() == 0 )     // cash payer
          {
             if ( order.DatumValuta() == pxConstants::NullDate )
             {
                Order().ClearUpdateDebtlimitK2();
                return pxConstants::mZero;
             }
          }
       }
       else
       if (IsArticleListFiveMember() )
       {
           cPayTerms = cPayTermsList->Find(LISTFIVE_PRICE);
          if (cPayTerms)
          {
             if ( cPayTerms->PaymentTarget() == 0 )     // cash payer
             {
                if ( order.DatumValuta() == pxConstants::NullDate )
                {
                   Order().ClearUpdateDebtlimitK2();
                   return pxConstants::mZero;
                }
             }
          }
       }
       else
       if ( order.DatumValuta() == pxConstants::NullDate )
       {
          Order().ClearUpdateDebtlimitK2();
          return pxConstants::mZero;
       }
    }

/*    debtlimit = customer->DebitLimitK2(); // get pointer to customers debtlimit entry
    if ( debtlimit == NULL )
       return pxConstants::mZero;


    if ( OldValue > pxConstants::mZero )
    {
       debtlimit->DecreaseDayTurnOver(Order().GetOrderValuesDebtlimit());
       debtlimit->Put();
       Order().SetUpdateDebtlimitK2();
    }
*/

    if ( OldValue > pxConstants::mZero && thisValue > pxConstants::mZero )
    {
       if ( thisValue > OldValue )
       {
          thisValue = thisValue - OldValue;
          QIncrease = true;
       }
       else
       {
          thisValue = OldValue - thisValue;
       }
    }

    if ( Order().IsUpdateDebtlimitK2() )
    {
       if (  QIncrease )
       {
          if ( (debtlimit->SumAdvanceAccount() + thisValue + Order().GetOrderValuesDebtlimit() ) > debtlimit->Limit() )
          {
             newValue  = debtlimit->SumAdvanceAccount() + thisValue + Order().GetOrderValuesDebtlimit();
             diffValue = newValue - debtlimit->Limit();
             return diffValue;
          }
       }
       else
       {
          if ( (debtlimit->SumAdvanceAccount() + thisValue + ( Order().GetOrderValuesDebtlimit() - OldValue ) > debtlimit->Limit() ) )
          {
             newValue  = debtlimit->SumAdvanceAccount() + thisValue + (Order().GetOrderValuesDebtlimit() - OldValue);
             diffValue = newValue - debtlimit->Limit();
             return diffValue;
          }
       }
    }
    else
    {
       if ( (debtlimit->SumAdvanceAccount() + thisValue ) > debtlimit->Limit() )
       {
          newValue  = debtlimit->SumAdvanceAccount() + thisValue;
          diffValue = newValue - debtlimit->Limit();
          return diffValue;
       }
    }


    if (!  Order().IsUpdateDebtlimitK2() )
    {
       SetUpdateDebtlimitK2();
    }
    return diffValue;
}
/*----------------------------------------------------------------------------*/
/* CheckCreditLimitK1: This methode checks customers creditlimit              */
/* OldValue is the Value of the previous booking. On new item, this value     */
/* zero, but on position change we must take care of the previous booking     */
/* value.                                                                     */
/* The variable diffValue will be returned: > 0.0 = Limit exceeded, otherwise */
/* this methode waits for the next position.                                  */
/* This methode checks all article and if  List5 == 1, then also list5 article*/
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: CheckCreditLimitK1
(
    nMoney   OldValue
)
{
    pxCustBase                  *customer = Order().Customer();  // customer
    const pxCustOrderType&             ot = Order().OrderType();
    pxOrder&                        order = Order();
    pxCstPaymentTermsList*  cPayTermsList = customer->CstPaymentTermsList();

    pxDebitLimit*       debtlimit = NULL;                // customers debtlimit entry pointer
    double                  Qty = (double) (MengeGeliefert_ + MengeVerbund() - MengeNatra_);
    nMoney              thisValue = Qty * InvoiceValue() * (1 + (SalesTaxRate_/100));
    nMoney              newValue;
    nMoney              diffValue = pxConstants::mZero;
    bool                QIncrease = false;

    // unused variable
    // nMoney          ordGrossValue = pxConstants::mZero;

/*----------------------------------------------------------------------------*/
/*  do some sanity checks                                                     */
/*----------------------------------------------------------------------------*/
    if (!Session()->isBulgaria()) // calcultion differs from other countries
          return pxConstants::mZero;
    // SR-15068713
    if ( order.IsNoCreditLimitCheck() )
    {
        return pxConstants::mZero;
    }

    if ( order.IsPseudoLock() )          // info order or proforma order
    {
       if ( order.IsBGInfoOrder() )     // if info order, no limit check
       {
          return pxConstants::mZero;
       }
    }

    if ( order.isCashOrder()  ||  ot.IsDiscountAccount() || ot.IsManualPromotion() || ot.IsRetailSalesOrder() ) // does not affect CO and RO and MP and EH
    {
       ClearUpdateDebtlimitK1();
       return pxConstants::mZero;
    }

    debtlimit = customer->DebitLimitK1(); // get pointer to customers debtlimit entry
    if ( debtlimit == NULL )
       return pxConstants::mZero;

    if ( !(debtlimit->IsListe5()) && IsArticleListFiveMember() )
       return pxConstants::mZero;

    if ( cPayTermsList == NULL && order.DatumValuta() == pxConstants::NullDate)
    {
       return pxConstants::mZero;                   // cash payer
    }

    debtlimit = customer->DebitLimitK1(); // get pointer to customers debtlimit entry
    if ( debtlimit == NULL )
       return pxConstants::mZero;


    if ( OldValue > pxConstants::mZero && !customer->IsCashPayer( PreisTypSaved_, &order))
    {
       debtlimit->DecreaseDayTurnOver(Order().GetOrderValuesDebtlimit());
       debtlimit->Put();
       Order().SetUpdateDebtlimitK1();
    }

    if ( cPayTermsList )
    {
        pxCstPaymentTerms* cPayTerms = cPayTermsList->Find( PreisTyp_);
       if (cPayTerms)
       {
          if ( cPayTerms->PaymentTarget() == 0 )    // cash payer
          {
             if ( order.DatumValuta() == pxConstants::NullDate )
             {
                Order().ClearUpdateDebtlimitK1();
                return pxConstants::mZero;
             }
          }
       }
       else
       if (IsArticleListFiveMember() )
       {
           cPayTerms = cPayTermsList->Find(LISTFIVE_PRICE);
          if (cPayTerms)
          {
             if ( cPayTerms->PaymentTarget() == 0 )     // cash payer
             {
                if ( order.DatumValuta() == pxConstants::NullDate )
                {
                   Order().ClearUpdateDebtlimitK1();
                   return pxConstants::mZero;
                }
             }
          }
       }
       else
       if ( order.DatumValuta() == pxConstants::NullDate )
       {
          Order().ClearUpdateDebtlimitK1();
          return pxConstants::mZero;
       }
    }

/*    debtlimit = customer->DebitLimitK1(); // get pointer to customers debtlimit entry
    if ( debtlimit == NULL )
       return pxConstants::mZero;


    if ( OldValue > pxConstants::mZero )
    {
       debtlimit->DecreaseDayTurnOver(Order().GetOrderValuesDebtlimit());
       debtlimit->Put();
       Order().SetUpdateDebtlimitK1();
    }
*/
    if ( OldValue > pxConstants::mZero  && thisValue > pxConstants::mZero )
    {
       if ( thisValue > OldValue )
       {
          thisValue = thisValue - OldValue;
          QIncrease = true;
       }
       else
       {
          thisValue = OldValue - thisValue;
       }
    }

    if ( Order().IsUpdateDebtlimitK1() )
    {
       if (  QIncrease )
       {
          if ( (debtlimit->SumAdvanceAccount() + thisValue + Order().GetOrderValuesDebtlimit() ) > debtlimit->Limit() )
          {
             newValue  = debtlimit->SumAdvanceAccount() + thisValue + Order().GetOrderValuesDebtlimit();
             diffValue = newValue - debtlimit->Limit();
             return diffValue;
          }
       }
       else
       {
          if ( (debtlimit->SumAdvanceAccount() + thisValue + ( Order().GetOrderValuesDebtlimit() - OldValue ) > debtlimit->Limit() ) )
          {
             newValue  = debtlimit->SumAdvanceAccount() + thisValue + (Order().GetOrderValuesDebtlimit() - OldValue);
             diffValue = newValue - debtlimit->Limit();
             return diffValue;
          }
       }
    }
    else
    {
       if ( (debtlimit->SumAdvanceAccount() + thisValue ) > debtlimit->Limit() )
       {
          newValue  = debtlimit->SumAdvanceAccount() + thisValue;
          diffValue = newValue - debtlimit->Limit();
          return diffValue;
       }
    }


    if (!  Order().IsUpdateDebtlimitK1() )
    {
       SetUpdateDebtlimitK1();
    }
    return diffValue;
}
