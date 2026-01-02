#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxoeparm.hpp"
#include "pxdelpos.hpp"
#include "pxdellog.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxordevt.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxcstot.hpp"
#include "pxcstpaymentterms.hpp"
#include "pxbranch.hpp"
#include "pxcstonr.hpp"
#include "pxseporderartgrp.hpp"
#include "pxcstprint.hpp"
#include "pxorderprolink.hpp"
#include "pxkdauftragdebtrel.hpp"
#include "pxordervalues.hpp"
#include "pxordercalcmode.hpp"
#include "pxdebitlimit.hpp"
#include "pxcremamail.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"
#include "cremamailhandler.h"
#include "pxtxtdoc.hpp"

/*----------------------------------------------------------------------------*/
bool pxOrder::Croatia()
{
    return Session()->isCroatia();  //return FilialNr_ == 71 || FilialNr_ == 72 || FilialNr_ == 73 || FilialNr_ == 74 || FilialNr_ == 77;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::Austria()
{
    return Session()->isAustria(); //return FilialNr_ == 61 || FilialNr_ == 62 || FilialNr_ == 63 || FilialNr_ == 64;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::Swiss()
{
    return Session()->isSwitzerland(); //return FilialNr_ == 12 || FilialNr_ == 13;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::Serbia()
{
    return Session()->isSerbia(); //return FilialNr_ == 3 || FilialNr_ == 84 || FilialNr_ == 85;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::Bulgaria()
{
    return Session()->isBulgaria(); //return FilialNr_ == 22 || FilialNr_ == 23 || FilialNr_ == 25 || FilialNr_ == 26 || FilialNr_ == 28 || FilialNr_ == 29;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::France()
{
    return Session()->isFrance() || Session()->isFrancePrewhole();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::German()
{
    return Session()->isGermany();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  CalcAepInvoiceValue:                                                      */
/*  already referenced, its read constructor is called.                       */
/*----------------------------------------------------------------------------*/
double
pxOrder::CalcAepInvoiceValue
(
    double  Aep,
    double  Percentage
)
{
    double       PreisFaktur(0.0);
    double       Reb = Percentage;
    pxCustBase& customer = *Customer();

    nMoney   Bprice = Aep;                      // AEP

    if (customer.IsCommercialRounding())
    {
        PreisFaktur = Bprice * (1 - (Reb / (100 + Reb)));          // commerercial calculation;
    }
    else
    {
        PreisFaktur = Bprice - ((Bprice * Reb) / 100.0);           // mathematical calculation;
    }
    return PreisFaktur;
}

/*----------------------------------------------------------------------------*/
/*  CloseOrderCalcMode(): this methode refreshes the values within the        */
/*  the tabel kdauftragrechart depend on customers cstprintlist               */
/*----------------------------------------------------------------------------*/
int
pxOrder::CloseOrderCalcMode
(
)
{
    PriceTypeEnum PreisType = FREESALE_PRICE;
    pxCstPrint* cstprint = NULL;
    int retval = 0;

    if (OrderCalcMode() && Customer()->CstPrintList())
    {
        if (OrderValues())
        {
            if (OrderValues()->OrdValFtaxHFDisc() > pxConstants::mZero)
            {
                PreisType = HEALTHFUND_PRICE;
            }
            if (OrderValues()->OrdValFtaxRSDisc() > pxConstants::mZero)
            {
                PreisType = RETAIL_PRICE;
            }
        }
        cstprint = Customer()->CstPrintList()->Find(PreisType);
        if (cstprint)
        {
            OrderCalcMode_->SetPrint(cstprint->Print());
            OrderCalcMode_->SetDeductionAep(cstprint->DeductionAep());
            OrderCalcMode_->SetDeductionAvp(cstprint->DeductionAvp());
            OrderCalcMode_->SetWithColumnNr(cstprint->WithColumnNr());
            OrderCalcMode_->SetByEmail(cstprint->InvoiceEmail());
            OrderCalcMode_->Put();
        }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  UpdateCustomerDebtlimitK2(): Updates Customers Debtlimit database entry   */
/*  with values within the OderValues object under respect of Customers Flags */
/*  RebateMethFreeSale_, RebateMethHealthf_                                   */
/*  This methode                                                              */
/*----------------------------------------------------------------------------*/
int
pxOrder::UpdateCustomerDebtlimitK2
(
)
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK2();       // get pointer to customers debtlimit entry
    return updateCustomerDebtlimit(debtlimit);
}

/*----------------------------------------------------------------------------*/
/*  UpdateCustomerDebtlimitK1(): Updates Customers Debtlimit database entry   */
/*  with values within the OderValues object under respect of Customers Flags */
/*  RebateMethFreeSale_, RebateMethHealthf_                                   */
/*  This methode                                                              */
/*----------------------------------------------------------------------------*/
int
pxOrder::UpdateCustomerDebtlimitK1
(
)
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK1();       // get pointer to customers debtlimit entry
    return updateCustomerDebtlimit(debtlimit);
}

int pxOrder::updateCustomerDebtlimit(pxDebitLimit* debtlimit)
{
    int retval = 0;

    if (!Session()->isBulgaria())
    {
        return retval;
    }
    if (debtlimit == NULL)
    {
        return retval;
    }

    nMoney rebateMethValue;
    if (!getRebateMethValueOnCustomerFlags(rebateMethValue))
    {
        return retval;
    }

    increaseDayTurnOverAndPutItem(debtlimit, (rebateMethValue - SaveOrderValueDL_));

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  SaveOrderValuesDebtLimit:                                                 */
/*----------------------------------------------------------------------------*/
int
pxOrder::SaveOrderValuesDebtLimit
(
)
{
    int retval = 0;

    if (!Session()->isBulgaria())
    {
        return retval;
    }

    nMoney rebateMethValue;
    if (getRebateMethValueOnCustomerFlags(rebateMethValue))
    {
        SaveOrderValueDL_ = rebateMethValue;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetOrderValuesDebtLimit:                                                  */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::GetOrderValuesDebtlimit
(
)
{
    nMoney DebtLimitValue(0.0);

    if (!Session()->isBulgaria())
    {
        return DebtLimitValue;
    }

    nMoney rebateMethValue;
    if (getRebateMethValueOnCustomerFlags(rebateMethValue))
    {
        DebtLimitValue = rebateMethValue;
    }
    return DebtLimitValue;
}

/*----------------------------------------------------------------------------*/
/*  CompleteCustomerDebtlimitK2: Updates Cusromers Debtlimit database entry   */
/*  with values within the OderValues object under respect of Customers Flags */
/*  RebateMethFreeSale_, RebateMethHealthf_                                   */
/*  This methode affect debtlimittype 2                                        */
/*----------------------------------------------------------------------------*/
int
pxOrder::CompleteCustomerDebtlimitK2
(
)
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK2();       // get pointer to customers debtlimit entry
    return completeCustomerDebtlimit(debtlimit);
}

/*----------------------------------------------------------------------------*/
/*  CompleteCustomerDebtlimitK1: Updates Cusromers Debtlimit database entry   */
/*  with values within the OderValues object under respect of Customers Flags */
/*  RebateMethFreeSale_, RebateMethHealthf_                                   */
/*  This methode affect debtlimittype 1                                        */
/*----------------------------------------------------------------------------*/
int
pxOrder::CompleteCustomerDebtlimitK1
(
)
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK1();       // get pointer to customers debtlimit entry
    return completeCustomerDebtlimit(debtlimit);
}

int pxOrder::completeCustomerDebtlimit(pxDebitLimit* debtlimit)
{
    int retval = 0;

    if (!Session()->isBulgaria())
    {
        return retval;
    }

    if (debtlimit == NULL)
    {
        return retval;
    }
    increaseDayTurnOverAndPutItem(debtlimit, GetOrderValuesDebtlimit());

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetOrderValueCstDiscAcc: Get OrderValue without Tax.                      */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::GetOrderValueCstDiscAcc
(
)
{
    nMoney OrderValue(0.0);
    pxOrderItemListIter iterator(*ItemList());
    pxOrderItem* item;

    if (!Session()->isBulgaria())
    {
        return OrderValue;
    }

    if (!(OrderType().IsDiscountAccount()))
    {
        return OrderValue;
    }

    while ((item = (pxOrderItem*) ++iterator) != NULL) // browse item list
    {
        OrderValue += (item->MengeGeliefert() * (double)item->Price());
    }
    return OrderValue;
}

/*----------------------------------------------------------------------------*/
/*  WriteProLink: Write date and InvoiceNumberPro into kdauftragprolink       */
/*----------------------------------------------------------------------------*/
int
pxOrder::WriteProLink
(
    const long       date,
    const nString& InvoiceNumberPro,
    const long       KdAuftragNrPro
)
{
    pxOrderProLink* ProLink = NULL;
    nDate DateProforma(date);

    ProLink = new pxOrderProLink(Session(), KdAuftragNr_);
    ProLink->Get(cDBGET_FORUPDATE);      // record does not exist

    ProLink->SetInvoiceNumberPro(InvoiceNumberPro);
    ProLink->SetDateProforma(DateProforma);
    ProLink->SetKdAuftragNrPro(KdAuftragNrPro);
    ProLink->Put();
    delete ProLink;
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  CountSpecialProducts                                                      */
/*----------------------------------------------------------------------------*/
int
pxOrder::CountSpecialProducts
(
    int& coolerq,
    int& opiateq,
    int& zytosq
)
{
    int k04 = 0;        // no. of KuehlKetten Artikel
    int k08 = 0;        // no. of Gekuehlt08  Artikel
    int k20 = 0;        // no. of Gekuehlt20  Artikel
    coolerq = 0;
    opiateq = 0;
    zytosq = 0;
    /*----------------------------------------------------------------------------*/
    /*  Now scan the list of positions                                            */
    /*----------------------------------------------------------------------------*/
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem* item;
    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (!item->IsCancelled())
        {
            if (((item->MengeGeliefert() + item->MengeVerbund()) > 0) && item->IsProductStocked())
            {
                if (item->MengeGeliefert() > 0)
                {
                    zytosq += item->ArtBase()->ArtFlags().IsZytoStatikaArtikel();
                }
                if (item->MengeGeliefert() > 0)
                {
                    k04 += item->ArtBase()->ArtFlags().IsKuehlKette();
                    k08 += item->ArtBase()->ArtFlags().IsGekuehlt08();
                    k20 += item->ArtBase()->ArtFlags().IsGekuehlt20();
                }
                opiateq += item->ArtBase()->ArtClass().IsOpiat();
            }
        }
    }
    coolerq += (k04 + k08 + k20);
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  CheckCustomerDebtlimitK2: this methode is used for customer with          */
/*   credit limit but no paymentterms during setting of a paymentterm         */
/*  Datumvaluta_.                                                             */
/*  First we try to get the debtlimit entry (K2) for this orders customer     */
/*  If Found we check the customer paymentterm list                           */
/*  The check takes place if the paymentterm list is empty, but K2 was found  */
/*----------------------------------------------------------------------------*/

nMoney
pxOrder::OrderValuesToCustomerDebtlimitK2
(
)
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK2();       // get pointer to customers debtlimit entry
    return pxOrder::orderValuesToCustomerDebtlimit(debtlimit);
}

/*----------------------------------------------------------------------------*/
/*  CheckCustomerDebtlimitK1: this methode is used for customer with          */
/*   credit limit but no paymentterms during setting of a paymentterm         */
/*  Datumvaluta_.                                                             */
/*  First we try to get the debtlimit entry (K1) for this orders customer     */
/*  If Found we check the customer paymentterm list                           */
/*  The check takes place if the paymentterm list is empty, but K1 was found  */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::OrderValuesToCustomerDebtlimitK1
(
)
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK1();       // get pointer to customers debtlimit entry
    return pxOrder::orderValuesToCustomerDebtlimit(debtlimit);
}

nMoney pxOrder::orderValuesToCustomerDebtlimit(pxDebitLimit* debtlimit)
{
    Session()->Device(); // Init Device
    long AnzPosFreeSale = 0;
    long AnzPosHealthFund = 0;
    long AnzPosList5 = 0;
    nMoney diffValue = pxConstants::mZero;
    bool FreeSaleCreditLimitRelevant = Customer()->IsCreditLimitRelevant(FREESALE_PRICE);
    bool HealthFundCreditLimitRelevant = Customer()->IsCreditLimitRelevant(HEALTHFUND_PRICE);
    bool ListFiveCreditLimitRelevant = Customer()->IsCreditLimitRelevant(LISTFIVE_PRICE);
    nMoney FreeSaleValue(0.0);
    nMoney HealthFundValue(0.0);
    nMoney List5Value(0.0);

    if (   !Session()->isBulgaria()
        || OrderType().IsDiscountAccount()
        || (DatumValuta_ == pxConstants::NullDate) )
    {
        return diffValue;
    }

    SetPaymentType('0');

    if (debtlimit == NULL)
    {
        return diffValue;
    }

    AnzPosFreeSale = CountPriceTypeItems(FREESALE_PRICE);
    AnzPosHealthFund = CountPriceTypeItems(HEALTHFUND_PRICE);
    AnzPosList5 = CountPriceTypeItems(LISTFIVE_PRICE);

    nMoney tmpDiffValue;

    if (hasPositionsOrNotIsCashPayer(AnzPosList5, LISTFIVE_PRICE))
    {
        List5Value = GetOrderValue(LISTFIVE_PRICE);
        if (!ListFiveCreditLimitRelevant)
        {
            if (getOrderDiffValue(debtlimit, List5Value, tmpDiffValue))
            {
                return tmpDiffValue;
            }
            increaseDayTurnOverAndPutItem(debtlimit, List5Value);
        }
    }

    if (hasPositionsOrNotIsCashPayer(AnzPosFreeSale, FREESALE_PRICE))
    {
        FreeSaleValue = GetOrderValue(FREESALE_PRICE);
        if (!FreeSaleCreditLimitRelevant)
        {
            if (getOrderDiffValue(debtlimit, FreeSaleValue, tmpDiffValue))
            {
                return tmpDiffValue;
            }
            increaseDayTurnOverAndPutItem(debtlimit, FreeSaleValue);
        }
    }

    if (hasPositionsOrNotIsCashPayer(AnzPosHealthFund, HEALTHFUND_PRICE))
    {
        HealthFundValue = GetOrderValue(HEALTHFUND_PRICE);
        if (!HealthFundCreditLimitRelevant)
        {
            nMoney orderValue = (HealthFundValue - List5Value);
            if (getOrderDiffValue(debtlimit, orderValue, tmpDiffValue))
            {
                return tmpDiffValue;
            }
            increaseDayTurnOverAndPutItem(debtlimit, orderValue);
        }
    }

    return diffValue;
}

bool pxOrder::hasPositionsOrNotIsCashPayer(long anzPos, PriceTypeEnum priceType)
{
    return ((anzPos > 0) && !Customer()->IsCashPayer(priceType, this));
}

bool pxOrder::getOrderDiffValue(pxDebitLimit* debtlimit, nMoney orderValue, nMoney& diffValue)
{
    if ((debtlimit->SumAdvanceAccount() + orderValue) > debtlimit->Limit())
    {
        nMoney newValue = debtlimit->SumAdvanceAccount() + orderValue;
        diffValue = newValue - debtlimit->Limit();
        return true;
    }
    diffValue = 0.0;
    return false;
}

void pxOrder::increaseDayTurnOverAndPutItem(pxDebitLimit* debtlimit, nMoney orderValue)
{
    debtlimit->IncreaseDayTurnOver(orderValue);
    putItem(debtlimit);
}

void pxOrder::decreaseDayTurnOverAndPutItem(pxDebitLimit* debtlimit, nMoney orderValue)
{
    debtlimit->DecreaseDayTurnOver(orderValue);
    putItem(debtlimit);
}

void pxOrder::putItem(pxDebitLimit* debtlimit)
{
    nDBBeginTransaction(cDBTransRecord);
    debtlimit->Put();
    if (debtlimit->IsGoodState())
    {
        nDBCommit(cDBTransRecord);
    }
}

/*----------------------------------------------------------------------------*/
/*  CheckHighValuePositions: this methode is used for the serbian apllication */
/*  Every position within this order is checked for shipvalue higher then     */
/*  10.000.000 SD, depend on PreisEKApo and PreisEKGrosso.                    */
/*  If one position exceeds this limit, the order will be deferred for manual */
/*  correction                                                                */
/*----------------------------------------------------------------------------*/
bool
pxOrder::CheckHighValuePositions
(
)
{
    bool retval = false;
    nMoney        ValueLimit(10000000.0);

    if (!Session()->isSerbia())
    {
        return false;
    }
    /*----------------------------------------------------------------------------*/
    /*  Now scan the list of positions                                            */
    /*----------------------------------------------------------------------------*/
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem* item;
    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (   (((double)item->MengeBestaetigt() * item->PreisEKApo()) > ValueLimit)
            || (((double)item->MengeBestaetigt() * item->PreisEKGrosso()) > ValueLimit) )
        {
            ExternalCondition(CMsgStream(), CMSG_ITM_HIGHVALUE_EXCEEDED, item->PosNr());
            retval = true;
            break;
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  CheckPaymentDate: this methode is used for the bulgarian apllication      */
/*  It sets paymentdate on table kdauftrag depend on kind of order and        */
/*  customers paymentterms(table cstpaymentterms)                             */
/*  It's like DatumValuta, but in an other way                                */
/*----------------------------------------------------------------------------*/
int
pxOrder::CheckPaymentDate
(
)
{
    long AnzPosFreeSale = 0;
    long AnzPosHealthFund = 0;
    nDate today;

    if (   IsPseudoLock()
        || this->isCashOrder() || OrderType().IsDiscountAccount()
        || !Session()->isBulgaria()
        || !IsEntryClosed() )   // state must be entryclosed
    {
        return ErrorState();
    }

    if (DatumValuta_ != pxConstants::NullDate)
    {
        SetPaymentDate(DatumValuta_);
        SetPaymentType('Z');
        return ErrorState();
    }

    if (!Customer()->HasDebitLimitK2() && !Customer()->HasDebitLimitK1())
    {
        SetPaymentType('C');
        return ErrorState();
    }

    AnzPosFreeSale = CountPriceTypeItems(FREESALE_PRICE);
    AnzPosHealthFund = CountPriceTypeItems(HEALTHFUND_PRICE);

    if (AnzPosFreeSale > 0)
    {
        setPaymentDateAndType(FREESALE_PRICE);
        return ErrorState();
    }

    if (AnzPosHealthFund > 0)
    {
        if (IsBulgariaListFive())         // order is just list 5 products
        {
            setPaymentDateAndType(LISTFIVE_PRICE);
            /* if ( !Customer()->IsCashPayer(LISTFIVE_PRICE, this) )
             {
                 setPaymentDateAndTypeOnArtPrice(LISTFIVE_PRICE);
             }
             else
             if ( !Customer()->IsCashPayer(HEALTHFUND_PRICE, this) )
             {
                 if (!setPaymentDateAndTypeOnArtPrice(HEALTHFUND_PRICE))
                 {
                     SetPaymentType( 'C');
                 }
             }
             else
             {
                 SetPaymentType('C');
             }*/
        }
        else
        {
            setPaymentDateAndType(HEALTHFUND_PRICE);
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  mustDoRecalculateOrder: this methode is used for the bulgarian            */
/*  apllication.                                                              */
/*  Check Freesale and Healthfund positions within this order and check for   */
/*  customers paymentterms(table cstpaymentterms)                             */
/*----------------------------------------------------------------------------*/
bool
pxOrder::mustDoRecalculateOrder
(
)
{
    bool retval = false;
    long AnzPosFreeSale = 0;
    long AnzPosHealthFund = 0;
    long countTargetItemsFreesale = 0;
    long countTargetItemsHealthFund = 0;
    long countProductPromotionItemsFreesale = 0;
    long countProductPromotionItemsHealthFund = 0;

    nDate today;
    AnzPosFreeSale = CountPriceTypeItems(FREESALE_PRICE);
    AnzPosHealthFund = CountPriceTypeItems(HEALTHFUND_PRICE);
    countTargetItemsFreesale = countPriceTypeTargetItems(FREESALE_PRICE);
    countTargetItemsHealthFund = countPriceTypeTargetItems(HEALTHFUND_PRICE);
    countProductPromotionItemsFreesale = countPriceTypeProductPromotionItems(FREESALE_PRICE);
    countProductPromotionItemsHealthFund = countPriceTypeProductPromotionItems(HEALTHFUND_PRICE);

    // do, if there are freesale positions and  ( countTargetItemsFreesale  > 0 or countProductPromotionItemsFreesale )
    if (AnzPosFreeSale > 0 && (countTargetItemsFreesale > 0 || countProductPromotionItemsFreesale > 0))
    {
        retval = true;
        return retval;  // we must leave now, because we must recalculate the complete order, independable of healthfund positions.
    }

    // do, if there are healtfund positions  and (countTargetItemsHealthFund or countProductPromotionItemsHealthFund)
    if (AnzPosHealthFund > 0 && (countTargetItemsHealthFund > 0 || countProductPromotionItemsHealthFund > 0))
    {
        retval = true;
    }

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  mustDoCheckCreditLimitCheck: this methode is used for the bulgarian       */
/*  apllication.                                                              */
/*  Check Freesale and Healthfund positions within this order and check for   */
/*  customers paymentterms(table cstpaymentterms)                             */
/*----------------------------------------------------------------------------*/
bool pxOrder::mustDoCheckCreditLimitCheck()
{
    bool retval = true;
    long AnzPosFreeSale = 0;
    long AnzPosHealthFund = 0;
    long AnzPosList5 = 0;

    nDate today;
    AnzPosFreeSale = CountPriceTypeItems(FREESALE_PRICE);
    AnzPosHealthFund = CountPriceTypeItems(HEALTHFUND_PRICE);
    AnzPosList5 = CountPriceTypeItems(LISTFIVE_PRICE);

    // if there are freesale positions and  Customer is cash payer for freesale
    if (AnzPosFreeSale > 0 && Customer()->IsCashPayer(FREESALE_PRICE, this))
    {
        retval = false;
    }

    // if there are healtfund positions  and Customer is cash payer for healthfund
    if (AnzPosHealthFund > 0 && Customer()->IsCashPayer(HEALTHFUND_PRICE, this))
    {
        retval = false;
    }
    // if there are List5 positions  and Customer is cash payer for listfive
    if (AnzPosList5 > 0 && Customer()->IsCashPayer(LISTFIVE_PRICE, this))
    {
        retval = false;
    }

    return retval;
}

void pxOrder::setPaymentDateAndType(PriceTypeEnum priceType)
{
    if (Customer()->IsCashPayer(priceType, this))
    {
        SetPaymentType('C');
    }
    else
    {
        setPaymentDateAndTypeOnArtPrice(priceType);
    }
}

bool pxOrder::setPaymentDateAndTypeOnArtPrice(PriceTypeEnum priceType)
{
    pxCstPaymentTermsList* cPayTermsList = Customer()->CstPaymentTermsList();
    pxCstPaymentTerms* cPayTerms = cPayTermsList->Find(priceType);
    if (cPayTerms != NULL)
    {
        nDate today;
        SetPaymentDate(today + cPayTerms->PaymentTarget());
        SetPaymentType('Z');
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
/*  UndoCustomerDebtlimitK2: this methode is used for customer with           */
/*   credit limit but no paymentterms during setting of a paymentterm         */
/*  Datumvaluta_.                                                             */
/*  DatumValuta was not pxConstants::NullDate, but within the orderentry DatumValuta was */
/*  set to zero days order->ValDate(d->VALUTAMONATE);,                        */
/*  where d->VALUTAMONATE = 0                                                 */
/*  First we try to get the debtlimit entry (K2) for this orders customer     */
/*  If Found we check the customer paymentterm list                           */
/*  The undo takes place if the paymentterm list is empty, but K2 was found   */
/*----------------------------------------------------------------------------*/

nMoney
pxOrder::UndoCustomerDebtlimitK2
(
)
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK2();       // get pointer to customers debtlimit entry
    return undoCustomerDebtlimit(debtlimit);
}

/*----------------------------------------------------------------------------*/
/*  UndoCustomerDebtlimitK1: this methode is used for customer with           */
/*   credit limit but no paymentterms during setting of a paymentterm         */
/*  Datumvaluta_.                                                             */
/*  DatumValuta was not pxConstants::NullDate, but within the orderentry DatumValuta was */
/*  set to zero days order->ValDate(d->VALUTAMONATE);,                        */
/*  where d->VALUTAMONATE = 0                                                 */
/*  First we try to get the debtlimit entry (K1) for this orders customer     */
/*  If Found we check the customer paymentterm list                           */
/*  The undo takes place if the paymentterm list is empty, but K1 was found   */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::UndoCustomerDebtlimitK1
(
)
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK1();       // get pointer to customers debtlimit entry
    return undoCustomerDebtlimit(debtlimit);
}

nMoney pxOrder::undoCustomerDebtlimit(pxDebitLimit* debtlimit)
{
    Session()->Device(); // Init Device
    long AnzPosFreeSale = 0;
    long AnzPosHealthFund = 0;
    long AnzPosList5 = 0;
    nMoney diffValue = pxConstants::mZero;
    bool FreeSaleCreditLimitRelevant = Customer()->IsCreditLimitRelevant(FREESALE_PRICE);
    bool HealthFundCreditLimitRelevant = Customer()->IsCreditLimitRelevant(HEALTHFUND_PRICE);
    bool ListFiveCreditLimitRelevant = Customer()->IsCreditLimitRelevant(LISTFIVE_PRICE);
    nMoney FreeSaleValue(0.0);
    nMoney HealthFundValue(0.0);
    nMoney List5Value(0.0);

    if (   !Session()->isBulgaria()
        || (DatumValuta_ == pxConstants::NullDate)
        || this->isCashOrder() || OrderType().IsDiscountAccount()
        || (debtlimit == NULL) )
    {
        return diffValue;
    }

    AnzPosFreeSale = CountPriceTypeItems(FREESALE_PRICE);
    AnzPosHealthFund = CountPriceTypeItems(HEALTHFUND_PRICE);
    AnzPosList5 = CountPriceTypeItems(LISTFIVE_PRICE);

    if (hasPositionsOrNotIsCashPayer(AnzPosList5, LISTFIVE_PRICE))
    {
        List5Value = GetOrderValue(LISTFIVE_PRICE);
        if (!ListFiveCreditLimitRelevant)
        {
            decreaseDayTurnOverAndPutItem(debtlimit, List5Value);
        }
    }

    if (hasPositionsOrNotIsCashPayer(AnzPosFreeSale, FREESALE_PRICE))
    {
        FreeSaleValue = GetOrderValue(FREESALE_PRICE);
        if (!FreeSaleCreditLimitRelevant)
        {
            decreaseDayTurnOverAndPutItem(debtlimit, FreeSaleValue);
        }
    }

    if (hasPositionsOrNotIsCashPayer(AnzPosHealthFund, HEALTHFUND_PRICE))
    {
        HealthFundValue = GetOrderValue(HEALTHFUND_PRICE);
        if (!HealthFundCreditLimitRelevant)
        {
            decreaseDayTurnOverAndPutItem(debtlimit, (HealthFundValue - List5Value));
        }
    }

    return diffValue;
}

int
pxOrder::GetReleaseApprovalValues(const long orderNo, const short branchNo, short& ApprovalMax, short& ApprovalCancel, short& ApprovalClose)
{
    ApprovalCancel = 0;
    ApprovalClose = 0;
    ApprovalMax = 0;

    pxKdAuftragDebtRelList debtRel(Session());

    debtRel.SelectApprovalData(orderNo);
    if (debtRel.Entries() == 0)
    {
        ApprovalCancel = 0;
        ApprovalClose = 0;
    }
    else
    {
        pxKdAuftragDebtRel* drp;               // ptr to list entry
        pxKdAuftragDebtRelListIter cursorDR(debtRel);  // define an iterator
        while ((drp = (pxKdAuftragDebtRel*) ++cursorDR) != NULL)
        {
            ApprovalCancel = drp->CancelCounter();
            ApprovalClose = drp->ApprovalCounter();
        }
    }

    debtRel.Clear();

    pxCremaMailList mail(Session());

    mail.SelectMaxApprovalNeeded(orderNo, branchNo);
    if (mail.Entries() == 0)
    {
        ApprovalMax = 0;
    }

    pxCremaMail* dikp;               // ptr to list entry
    pxCremaMailListIter cursorMail(mail);  // define an iterator
    while ((dikp = (pxCremaMail*) ++cursorMail) != NULL)
    {
        ApprovalMax = dikp->ApprovalPersonsNeeded();
    }
    debtRel.Clear();

    return ErrorState();
}

bool pxOrder::IsCremaInsert(const nString& RelUser)
{
    bool insert = true;

    pxKdAuftragDebtRel* DebtRel = NULL;
    pxKdAuftragDebtRelList debtRelList(Session());

    //check User votes
    debtRelList.SelectUserVote(KdAuftragNr_, RelUser);
    if (debtRelList.Entries() > 0)
    {
        pxKdAuftragDebtRelListIter cursorDR(debtRelList);
        DebtRel = (pxKdAuftragDebtRel*) ++cursorDR;
        if (DebtRel->RelCounter() > 0)
        {
            insert = false;
        }
    }
    else
    {
        insert = true;
    }
    debtRelList.Clear();

    return insert;
}

bool pxOrder::UpdateCounterOnUpdate(const nString& RelUser, Order::CloseType type, short& changeValue)
{
    bool processedUser = true;

    pxKdAuftragDebtRel* latestUserEntry = NULL;
    pxKdAuftragDebtRel* lastEntry = NULL;
    pxKdAuftragDebtRel* curEntry = NULL;
    pxKdAuftragDebtRelList debtRelList(Session());

    //check User votes
    debtRelList.SelectVote(KdAuftragNr_);

    pxKdAuftragDebtRelListIter cursor(debtRelList);

    if (debtRelList.Entries() == 1)
    {
        curEntry = (pxKdAuftragDebtRel*) ++cursor;
        if (curEntry->RelUser() == RelUser)
        {
            if ((type == Order::CLOSE && curEntry->ApprovalCounter() == 1) || (type == Order::CANCEL && curEntry->CancelCounter() == 1))
            {
                changeValue = 0;
            }
        }
    }
    else if (debtRelList.Entries() > 1)
    {
        processedUser = false;

        while ((curEntry = (pxKdAuftragDebtRel*) ++cursor) != NULL)
        {
            if (latestUserEntry == NULL && curEntry->RelUser() == RelUser)
            {
                latestUserEntry = curEntry;
            }
            if (latestUserEntry != NULL && latestUserEntry != curEntry)
            {
                //both are set, perform checks
                if (latestUserEntry->ApprovalCounter() > curEntry->ApprovalCounter() && type == Order::CLOSE)
                {
                    changeValue = 0;
                    processedUser = true;
                    break;
                }
                else if (latestUserEntry->CancelCounter() > curEntry->CancelCounter() && type == Order::CANCEL)
                {
                    changeValue = 0;
                    processedUser = true;
                    break;
                }
                /*
                else if(latestUserEntry->CancelCounter() == curEntry->CancelCounter() &&
                        latestUserEntry->ApprovalCounter() == curEntry->ApprovalCounter())
                {
                    //Umentscheidung, weitersuchen
                }*/
            }
            //if ((curEntry != cursor.end()) && (curEntry + 1 != cursor.end()))
            {
                lastEntry = curEntry;
            }
        }
        if (!processedUser && lastEntry != NULL && latestUserEntry != NULL)
        {
            //both are set, perform checks
            if (latestUserEntry->ApprovalCounter() > lastEntry->ApprovalCounter() && type == Order::CLOSE)
            {
                changeValue = 0;
            }
            else if (latestUserEntry->CancelCounter() > lastEntry->CancelCounter() && type == Order::CANCEL)
            {
                changeValue = 0;
            }
            processedUser = true;
        }
    }

    debtRelList.Clear();

    return changeValue == 0 ? false : true;
}

bool pxOrder::IsCremaOrderApproved(Order::CloseType closeType, bool insert, bool updateCounterOnUpdate, short changeValue)
{
    short approvalCancel = 0;
    short approvalClose = 0;
    short approvalMax = 0;
    GetReleaseApprovalValues(KdAuftragNr_, FilialNr_, approvalMax, approvalCancel, approvalClose);

    if (insert || (!insert && updateCounterOnUpdate))
    {
        if (closeType == Order::CLOSE)
        {
            approvalClose += changeValue;
            if (updateCounterOnUpdate)
            {
                approvalCancel -= changeValue;
            }
        }
        else
        {
            approvalCancel += changeValue;
            if (updateCounterOnUpdate)
            {
                approvalClose -= changeValue;
            }
        }
    }

    IsReleased_ = (approvalClose == approvalMax || approvalCancel == approvalMax) ? true : false;
    ApprovalsNeeded_ = approvalMax - (approvalClose > approvalCancel ? approvalClose : approvalCancel);

    if (!IsReleased_)
    {
        if (approvalClose > 0 && approvalCancel > 0 && approvalMax % 2 == 0 && approvalMax == approvalClose + approvalCancel)
        {
            DiscussionNeeded_ = true;
            ExternalError(CMsgStream(), CMSG_ORD_CREMA_APPROVAL_DISCUSSION, ApprovalsNeeded_, approvalMax, approvalClose, approvalCancel);
        }
        else
        {
            int msgId = (closeType == Order::CLOSE) ? CMSG_ORD_CREMA_APPROVAL_CLOSE : CMSG_ORD_CREMA_APPROVAL_CANCEL;
            ExternalError(CMsgStream(), CMSG_ORD_CREMA_APPROVAL_MISSING, ApprovalsNeeded_, (char*)nMessage(CMsgStream(), msgId).String());
        }
    }

    return IsReleased_;
}

int
pxOrder::CopyReleaseInfos(const long orderNo)
{
    pxKdAuftragDebtRelList debtRelList(Session());

    debtRelList.SelectForCopy(orderNo);

    if (debtRelList.Entries() > 0)
    {
        nDBBeginTransaction(cDBTransRecord);

        pxKdAuftragDebtRel* debtRel;
        pxKdAuftragDebtRelListIter cursor(debtRelList);
        while ((debtRel = (pxKdAuftragDebtRel*) ++cursor) != NULL)
        {
            tKDAUFTRAGDEBTREL record;
            memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
            Assign(record, *debtRel);
            record.KdAuftragNr = KdAuftragNr_;
            debtRel->Insert(&record);

            if (!IsGoodState())
            {
                Error() = debtRel->Error();
                break;
            }
        }
        if (IsGoodState())
        {
            nDBCommit(cDBTransRecord);
        }
        else
        {
            nDBRollBack();
        }
    }

    debtRelList.Clear();

    return ErrorState();
}

bool pxOrder::SendCremaReleaseInfoMail(Order::CloseType closeType, const nString& RelReason, const nString& RelUser, const nString& guid, const nString& URL, const nString& Comment, Order::ApprovalType approvalType)
{
    bool success = false;
    CremaMailHandler handler(Session());

    nString tmp = Customer_->Land();
    tmp.Strip();
    std::string custLocation = tmp();
    custLocation.append(" ");
    tmp = Customer_->Postleitzahl();
    tmp.Strip();
    custLocation.append(tmp());
    custLocation.append(" ");
    tmp = Customer_->Ort();
    tmp.Strip();
    custLocation.append(tmp());

    if (IsReleased_)
    {
        if (closeType == Order::CLOSE)
        {
            success = handler.SendCremaClosedInfoMail(guid(), KdAuftragNr_, IDFNr_, Customer_->NameApo()(),
                Customer_->NameInhaber()(), custLocation, RelUser(), RelReason(), Comment(), static_cast<int>(approvalType));
        }
        else
        {
            success = handler.SendCremaCancelInfoMail(guid(), KdAuftragNr_, IDFNr_, Customer_->NameApo()(),
                Customer_->NameInhaber()(), custLocation, RelUser(), RelReason(), Comment());
        }
    }
    else if (URL.Length() > 0 && DiscussionNeeded_)
    {
        success = handler.SendCremaDiscussionInfoMail(guid(), KdAuftragNr_, IDFNr_, Customer_->NameApo()(),
            Customer_->NameInhaber()(), custLocation, WertLieferung_, URL());
    }

    return success;
}


/*----------------------------------------------------------------------------*/
/*  SetReleaseInfos: Write reason,comment and user to kdauftragdebtrel        */
/*----------------------------------------------------------------------------*/
int
pxOrder::SetReleaseInfos
(
    const nString& RelReason,
    const nString& RelComment,
    const nString& RelUser,
    Order::CloseType type,
    const nString& guid,
    const nString& URL,
    Order::ApprovalType approvalType
)
{
    short changeValue = 1;
    bool updateCounterOnUpdate = false;
    nMoney debtLimitAmount = 0.0;
    nMoney sumAdvanceAccount = 0.0;

    if (Session()->isBulgaria())
    {
        pxDebitLimit* debtLimitBG = NULL;
        // Checks debtlimit for BG at partnerno level (type = 2) for all articles
        debtLimitBG = Customer()->DebitLimitK2();

        if (!debtLimitBG->IsGoodState() || (debtLimitBG->Limit() == pxConstants::mZero) || !(debtLimitBG->SumAdvanceAccount() > debtLimitBG->Limit()))
        {
            debtLimitBG = NULL;
            // Checks debtlimit for BG at partnerno level (type = 1) for all articles except List5 and uses chain level if exists
            debtLimitBG = Customer()->DebitLimitK1();
            if (!debtLimitBG->IsGoodState() || (debtLimitBG->Limit() == pxConstants::mZero))
            {
                return false;

            }
        }
        debtLimitAmount = debtLimitBG->Limit();
        sumAdvanceAccount = debtLimitBG->SumAdvanceAccount();
    }
    else
    {
        pxDebitLimit debtLimit(Session(), Customer_->PartnerNr(), cDBGET_READONLY);
        if (!debtLimit.IsGoodState())
        {
            return false;
        }
        debtLimitAmount = debtLimit.Limit();
        sumAdvanceAccount = debtLimit.SumAdvanceAccount();

    }

    bool insert = IsCremaInsert(RelUser);
    if (!insert)
    {
        updateCounterOnUpdate = UpdateCounterOnUpdate(RelUser, type, changeValue);
    }

    bool isReleased = IsCremaOrderApproved(type, insert, updateCounterOnUpdate, changeValue);

    pxKdAuftragDebtRel* DebtRel = NULL;

    pxKdAuftragDebtRelList debtRelList(Session());

    //select data for insert/update
    debtRelList.SelectDataForMaxRelCount(KdAuftragNr_);

    if (debtRelList.Entries() > 0)
    {
        pxKdAuftragDebtRelListIter cursorDR(debtRelList);
        DebtRel = (pxKdAuftragDebtRel*) ++cursorDR;
    }
    else
    {
        DebtRel = new pxKdAuftragDebtRel(Session(), KdAuftragNr_, 0);
    }

    //get again because cxxtools wont let us define other ReadLock methods/add parameters. Here we need the entry with the max(RelCounter)

    DebtRel->nDBBeginTransaction(cDBTransRecord);
    DebtRel->Get(cDBGET_FORUPDATE);

    DebtRel->SetRelReason(RelReason);
    DebtRel->SetRelComment(RelComment);
    DebtRel->SetRelUser(RelUser);
    DebtRel->SetIsReleased(isReleased);

    DebtRel->SetOrderValue(WertLieferung_);
    DebtRel->SetDebtLimit(debtLimitAmount);
    DebtRel->SetUsedDebtLimit(sumAdvanceAccount);

    if (insert)
    {
        DebtRel->SetRelCounter(DebtRel->RelCounter() + 1);
        if (type == Order::CLOSE)
        {
            DebtRel->SetApprovalCounter(DebtRel->ApprovalCounter() + 1);
        }
        else
        {
            DebtRel->SetCancelCounter(DebtRel->CancelCounter() + 1);
        }
        tKDAUFTRAGDEBTREL record;
        memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
        Assign(record, *DebtRel);
        DebtRel->Insert(&record);
    }
    else
    {
        if (updateCounterOnUpdate)
        {
            if (type == Order::CLOSE)
            {
                DebtRel->SetApprovalCounter(DebtRel->ApprovalCounter() + changeValue);
                DebtRel->SetCancelCounter(DebtRel->CancelCounter() - changeValue);
            }
            else
            {
                DebtRel->SetCancelCounter(DebtRel->CancelCounter() + changeValue);
                DebtRel->SetApprovalCounter(DebtRel->ApprovalCounter() - changeValue);
            }
        }
        DebtRel->SetRelCounter(DebtRel->RelCounter() + 1);

        tKDAUFTRAGDEBTREL record;
        memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
        Assign(record, *DebtRel);
        DebtRel->Insert(&record);
    }

    SendCremaReleaseInfoMail(type, RelReason, RelUser, guid, URL, RelComment, approvalType);

    commitOrRollback(DebtRel);

    if (debtRelList.Entries() > 0)
    {
        debtRelList.Clear();
    }
    else
    {
        delete DebtRel;
    }

    return ErrorState();
}

bool pxOrder::DeleteCremaMail(long orderNo, short branchNo)
{
    CremaMailHandler mail(Session());
    return mail.deleteMail(orderNo, branchNo);
}

bool pxOrder::WasOrderReleased()
{
    bool wasReleased = false;
    pxKdAuftragDebtRel* debtRel = NULL;

    pxKdAuftragDebtRelList debtRelList(Session());
    debtRelList.SelectDataForMaxRelCount(KdAuftragNr_);
    if (debtRelList.Entries() > 0)
    {
        pxKdAuftragDebtRelListIter cursorDR(debtRelList);
        debtRel = (pxKdAuftragDebtRel*) ++cursorDR;
    }
    else
    {
        debtRel = new pxKdAuftragDebtRel(Session(), KdAuftragNr_, 0);
    }

    debtRel->Get(cDBGET_READONLY);
    wasReleased = (debtRel->IsReleased() != 0);

    if (debtRelList.Entries() > 0)
    {
        debtRelList.Clear();
    }
    else
    {
        delete debtRel;
    }

    return wasReleased;
}


/*----------------------------------------------------------------------------*/
/*  checkKdAuftragDebtlimtEntry: looks for an kdauftragdebtrel entry for      */
/*  KdAuftragNr, if avaiable, insert a new entry for this->KdauftragNr_ and   */
/*  do a SetReleaseInfos for this order with the values of the select entry   */
/*  This works only within the Crema environment                              */
/*----------------------------------------------------------------------------*/
int
pxOrder::checkKdAuftragDebtlimtEntry
(
    const long KdAuftragNr
)
{
    CopyReleaseInfos(KdAuftragNr);
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  WriteTourIdChangeEvent: This methode is called from the ksc order entry   */
/*  server after the tourid has been changed                                  */
/*----------------------------------------------------------------------------*/
int pxOrder::WriteTourIdChangeEvent()
{
    return writeChangeEvent(Order::ChangedTourId);
}

/*----------------------------------------------------------------------------*/
/*  WriteCommiTypeChangeEvent()This methode is called from the ksc order entry*/
/*  server after the commitype has been changed                               */
/*----------------------------------------------------------------------------*/
int pxOrder::WriteCommiTypeChangeEvent()
{
    return writeChangeEvent(Order::ChangedCommiType);
}
/*----------------------------------------------------------------------------*/
/*  WriteOrderCreationEvent: This methode is called from the ksc order entry  */
/*  server during creation of a new order                                     */
/*----------------------------------------------------------------------------*/
int pxOrder::WriteOrderCreationEvent()
{
    return writeChangeEvent(Order::OrderCreation);
}

/*----------------------------------------------------------------------------*/
/*  write an event that the orderlabel has been changed to default            */
/*----------------------------------------------------------------------------*/
void pxOrder::WriteOrderLabelChangedToDefaultEvent()
{
    writeChangeEvent(Order::ChangedToDefaultMSV3OrderLabel);
}

/*----------------------------------------------------------------------------*/
/*  WriteOrderTypeChangeEvent()This methode is called from the ksc order entry*/
/*  server after the ordertype has been changed                               */
/*----------------------------------------------------------------------------*/
int pxOrder::WriteOrderTypeChangeEvent()
{
    return writeChangeEvent(Order::ChangedOrderType);
}

int pxOrder::writeChangeEvent(Order::States state)
{
    pxOrderEvent event(*this);          // construct order event
    event.SetEvent(state);
    event.Put();                        // write it into the data base
    return ErrorState();
}

bool pxOrder::getRebateMethValueOnCustomerFlags(nMoney& rebateMethValue)
{
    if (OrderValues() == NULL)
    {
        return false;
    }

    bool cstRebateMethFreeSale = Customer()->IsRebateMethFreeSale();
    bool cstRebateMethHealthf = Customer()->IsRebateMethHealthf();

    nMoney freeSaleValue = cstRebateMethFreeSale ? OrderValues()->OrdValFtaxFS() : OrderValues()->OrdValFtaxFSDisc();
    nMoney healtHFundValue = cstRebateMethHealthf ? OrderValues()->OrdValFtaxHF() : OrderValues()->OrdValFtaxHFDisc();

    rebateMethValue = healtHFundValue + freeSaleValue;
    return true;
}

void pxOrder::commitOrRollback(pxKdAuftragDebtRel* debtRel)
{
    if (debtRel->IsGoodState())
    {
        debtRel->nDBCommit(cDBTransRecord);
    }
    else
    {
        debtRel->nDBRollBack();
    }
}
int pxOrder::CopyOrderHeadAndTailText(pxOrder* seporder)
{
    // Look for Headtext
    pxTextDoc* headtext = HeadText();
    pxTextDoc* tailtext = TailText();
    pxTextDocIter headiter = pxTextDocIter(*headtext);
    pxTextDocIter tailiter = pxTextDocIter(*tailtext);
    if (headtext->Entries() > 0)
    {
        pxTextDoc* headp = seporder->HeadText();
        while ((headtext = (pxTextDoc*) ++headiter) != NULL)
        {
            nString headline = ((pxTextLine*)headtext)->Text();
            headp->NewLine(headline);
        }
    }
    // Look for Tailtext
    if (tailtext->Entries() > 0)
    {
        pxTextDoc* tailp = seporder->TailText();
        while ((tailtext = (pxTextDoc*) ++tailiter) != NULL)
        {
            nString tailline = ((pxTextLine*)tailtext)->Text();
            tailp->NewLine(tailline);
        }
    }
    return ErrorState();
}
bool pxOrder::checkReleasedDeliveryPosInSameOrder(const long KdAuftragNr, const long ArtikelNr)
{
    bool retval = false;
    nDate dayOffcreation;
    dayOffcreation = this->DateTimeCreated();
    pxDeliveryLogList* delloglist = new pxDeliveryLogList(Session());
    pxDeliveryLogListIter iterator(*delloglist);
    pxDeliveryLog* dlogentry;
    delloglist->Select(KdAuftragNr, ArtikelNr);
    while ((dlogentry = (pxDeliveryLog*) ++iterator) != NULL)
    {
        if (dlogentry->KdAuftragNr() == dlogentry->KdAuftragNrNeu())
        {
            retval = true;
        }
    }
    delete delloglist;
    return retval;
}

