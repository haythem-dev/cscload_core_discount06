#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcstpaymentterms.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxdebitlimit.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxvaluescollect.hpp"
#include "pxordervalues.hpp"
#include "pxordtaxvalues.hpp"
#include "pxtxtdoc.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Calculate an order item's values and update value sums in self.           */
/*----------------------------------------------------------------------------*/
void
pxOrder::ItemValues(pxOrderItem* item, pxItemDiscountList* discl)
{
    if (item->IsGoodState())          // ensure object is well constructed
    {
        nMoney shipv = pxConstants::mZero;
        AnzPos_ = static_cast<long>(ItemList()->Entries());
        if (!item->IsCancelled())      // ensure item is not cancelled
        {
            if (Session()->isCroatia())
            {
                WertNetto_ += item->ShipValueDisc();
                //              WertNetto_ += item->OrderValueDisc();
                //              shipv = item->ShipValueDisc();
            }

            WertAuftrag_ += item->OrderValue();
            shipv = item->ShipValue();
            //DefektWert_  += item->OrderCorruptValue();
            item->InvoiceValue();
            if (discl)
            {
                shipv = item->InvoiceValue(discl);
            }
        }
        if (shipv <= pxConstants::mZero) // then item without a chargeable value
            ++AnzPosOB_;                  // count no. of items not chargeable
        else
            WertLieferung_ += shipv;      // update order ship value

        // Bulgarien apllication
        WertNetto_ += item->WertNetto();
        WertRabatt_ += item->WertRabatt();
        ValuesCollectList()->SetValueNetCash(item->WertNetto(), item->PreisTyp());
        ValuesCollectList()->SetValueSalesTax(item->CalcSalesTax(), item->PreisTyp());
        if (item->IsArticleListFiveMember())
        {
            ValuesCollectList()->SetValueNetCash(item->WertNetto(), LISTFIVE_PRICE);
            ValuesCollectList()->SetValueSalesTax(item->CalcSalesTax(), LISTFIVE_PRICE);
        }
        if (OrderValues())
        {
            if (item->IsUpdateDebtlimitK2() || item->IsUpdateDebtlimitK1())
            {
                SaveOrderValuesDebtLimit();
            }
            OrderValues()->CalcOrderValues(item);
            SetCurrentCstDiscAccBalance((short)0);
            if (item->IsUpdateDebtlimitK2())
            {
                UpdateCustomerDebtlimitK2();
                item->ClearUpdateDebtlimitK2();
            }
            if (item->IsUpdateDebtlimitK1())
            {
                UpdateCustomerDebtlimitK1();
                item->ClearUpdateDebtlimitK1();
            }
        }
        SetDirty();                      // set object state to dirty
    }
}

/*----------------------------------------------------------------------------*/
/*  Calculate average item value.                                             */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::AverageItemValue()
{
    const long pos = AnzPos_ - AnzPosOB_;   // number of chargeable items
    if (pos > 0L)                      // then calc average item value
        WertZeilen_ = WertLieferung_ / (double)pos;
    if (WertZeilen_ < pxConstants::mZero)
        WertZeilen_ = pxConstants::mZero; // avoid negative value
    SetDirty();                         // set object state to dirty
    return WertZeilen_;
}

/*----------------------------------------------------------------------------*/
/*  Re-calculate the entire order values.                                     */
/*  Returns average item value.                                               */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::ReCalcValues()
{
    InitValues();
    pxOrderItemListIter cursor(*ItemList_); // define an iterator
    pxOrderItem* item;
    while ((item = (pxOrderItem*) ++cursor) != NULL)
    {
        ItemValues(item);
        OrdTaxValues()->SetOrderValues(item);
    }

    if (IsUpdateDebtlimitK2() && (AnzPos_ > 0))
    {
        CompleteCustomerDebtlimitK2();
        ClearUpdateDebtlimitK2();
    }
    if (IsUpdateDebtlimitK1() && (AnzPos_ > 0))
    {
        CompleteCustomerDebtlimitK1();
        ClearUpdateDebtlimitK1();
    }
    return AverageItemValue();
}

/*----------------------------------------------------------------------------*/
/*  ReCalcValuesCollectList; recalculates ValuesCollectList_                  */
/*----------------------------------------------------------------------------*/
void
pxOrder::ReCalcValuesCollectList()
{
    pxOrderItemListIter cursor(*ItemList_); // define an iterator
    pxOrderItem* item;
    while ((item = (pxOrderItem*) ++cursor) != NULL)
    {
        ValuesCollectList()->SetValueNetCash(item->WertNetto(), item->PreisTyp());
        ValuesCollectList()->SetValueSalesTax(item->CalcSalesTax(), item->PreisTyp());
        if (item->IsArticleListFiveMember())
        {
            ValuesCollectList()->SetValueNetCash(item->WertNetto(), LISTFIVE_PRICE);
            ValuesCollectList()->SetValueSalesTax(item->CalcSalesTax(), LISTFIVE_PRICE);
        }
    }
}

/*----------------------------------------------------------------------------*/
/*  Re-calculate the entire order values under respect off discl.             */
/*  Returns average item value.                                               */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::ReCalcValuesProforma(pxItemDiscountList* discl)
{
    if (ItemListProforma_ == NULL)
        return AverageItemValue();

    InitValues();

    pxOrderItemListIter cursor(*ItemListProforma_); // define an iterator
    pxOrderItem* item;
    while ((item = (pxOrderItem*) ++cursor) != NULL)
    {
        ItemValues(item, discl);
        OrdTaxValues()->SetOrderValues(item);
    }

    return AverageItemValue();
}

/*----------------------------------------------------------------------------*/
/*  Re-calculate the OrderValues for KdAuftragWerte                           */
/*----------------------------------------------------------------------------*/
void
pxOrder::ReCalcValuesOrderValues()
{
    if (OrderValues() == NULL)
        return;

    OrderValues()->InitOrderValues();

    pxOrderItemListIter cursor(*ItemList()); // define an iterator
    pxOrderItem* item;
    while ((item = (pxOrderItem*) ++cursor) != NULL)
    {
        OrderValues()->CalcOrderValues(item);
    }
}

/*----------------------------------------------------------------------------*/
/*  Initialize order values to nulls.                                         */
/*----------------------------------------------------------------------------*/
void
pxOrder::InitValues()
{
    WertAuftrag_ = pxConstants::mZero;
    WertLieferung_ = pxConstants::mZero;
    WertZeilen_ = pxConstants::mZero;
    DefektWert_ = pxConstants::mZero;
    WertNetto_ = pxConstants::mZero;
    WertRabatt_ = pxConstants::mZero;
    AnzPosOB_ = 0L;

    if (OrdTaxValues_ != NULL)
    {
        delete OrdTaxValues_;
        OrdTaxValues_ = NULL;
    }
    if (ValuesCollectList() != NULL)
    {
        ValuesCollectList_->InitValues();
    }
    if (OrderValues() != NULL)
    {
        OrderValues()->InitOrderValues();
    }
}

/*----------------------------------------------------------------------------*/
/*  IsCreditOnTop: if Customers Partnerno > 0, so we try to find an entry     */
/*  within the DEBTLIMIT Table depend on Customers PartneNo.                  */
/*  If the Creditlimit is reached, the returnvalue will be true,             */
/*  Otherwise the DayTurnOver in this entry will be increased and false is   */
/*  returned.                                                                 */
/*----------------------------------------------------------------------------*/
bool
pxOrder::IsCreditSumOnTop()
{
    const long partnerno = Customer()->PartnerNr();

    if (   (partnerno == 0L)                         //just if there is a partnernumber
        || !IsOrderAffectingCreditLimit()
        || IsSeparatedOrder()
        || (Session()->isBulgaria() && Customer()->IsCashPayer()) ) // In case of cash payer
    {
        return false;
    }

    bool limit = false;


    if (Session()->isBulgaria())
    {
        pxDebitLimit* debtLimitBG = NULL;
        const nMoney orderValue = CalcGrossShipValue();

        // Checks debtlimit for BG at partnerno level (type = 2) for all articles
        debtLimitBG = Customer()->DebitLimitK2();
        if (!debtLimitBG->IsGoodState() || (debtLimitBG->Limit() == pxConstants::mZero) || !((debtLimitBG->SumAdvanceAccount() + orderValue) > debtLimitBG->Limit()))
        {
            debtLimitBG = NULL;
            // Checks debtlimit for BG at chain level (type = 1) 
            debtLimitBG = Customer()->DebitLimitK1();
            if (!debtLimitBG->IsGoodState() || (debtLimitBG->Limit() == pxConstants::mZero))
            {
                return false;
            }
        }

        if (debtLimitBG != NULL)
        {
            //set email values
            UsedCustomerCredit_ = debtLimitBG->SumAdvanceAccount() + orderValue;
            DLPercentage_ = UsedCustomerCredit_ / debtLimitBG->Limit() * 100;
            OrderValue_ = orderValue;
            CustomerDebtLimit_ = debtLimitBG->Limit();

            bool bIncreaseDayTurnOver = false;
            if (UsedCustomerCredit_ > debtLimitBG->Limit())
            {
                limit = true;
                if (!IsKreditLimitErreicht())
                {
                    if (Param()->IsSCrema())
                    {
                        AddHeadTextLine(UsedCustomerCredit_ - debtLimitBG->Limit());
                        bIncreaseDayTurnOver = true;

                    }
                }
            }
            else
            {
                bIncreaseDayTurnOver = true;
            }

            if (bIncreaseDayTurnOver)
            {
                // Increases dayturnover for K1 and K2
                RedoCreditDayTurnOver(OrderValue_);
            }
        }
    }
    else
    {
        // Checks debtlimit for other countries type = 0
        boost::shared_ptr<pxDebitLimit> lm = boost::make_shared<pxDebitLimit>(Session(), partnerno);
        const nMoney orderValue = WertLieferung_;
        if (!lm->IsGoodState() || (lm->Limit() == pxConstants::mZero))
        {
            return false;
        }

        //set email values
        UsedCustomerCredit_ = lm->SumAdvanceAccount() + orderValue;
        DLPercentage_ = UsedCustomerCredit_ / lm->Limit() * 100;
        OrderValue_ = orderValue;
        CustomerDebtLimit_ = lm->Limit();


        bool bIncreaseDayTurnOver = false;

        if (UsedCustomerCredit_ > lm->Limit())
        {
            limit = true;
            if (!IsKreditLimitErreicht())
            {
                if (!(Session()->isGermany() || Param()->IsSCrema()))
                {
                    AddHeadTextLine(UsedCustomerCredit_ - lm->Limit());
                }
                if (Param()->IsSCrema())
                {
                    bIncreaseDayTurnOver = true;
                }
            }
        }
        else
        {
            bIncreaseDayTurnOver = true;
        }

        if (bIncreaseDayTurnOver)
        {
            IncreaseDayTurnOver(lm.get(), orderValue);
        }

    }

    return limit;
}

void pxOrder::AddHeadTextLine(double lDif)
{
    nString temp;
    temp.Trim(15);
    sprintf((char*)temp, "%06.2f", lDif);
    nMessage text(CMsgStream(), CMSG_ORD_CREDITLIMIT_EXEED_VALUE);
    nString newline;
    newline = text.String();
    newline.Trim(newline.Length() - 1);
    newline = newline + "   " + temp;

    HeadText()->NewLine(newline);
}

void pxOrder::IncreaseDayTurnOver(pxDebitLimit* lm, nMoney orderValue)
{
    nDBBeginTransaction(cDBTransRecord);
    lm->IncreaseDayTurnOver(orderValue);
    lm->Put();
    if (!lm->IsGoodState())
    {
        nDBRollBack();
    }
    else
    {
        nDBCommit(cDBTransRecord);
    }
}

/*----------------------------------------------------------------------------*/
/*  CheckForCreditSumOnTop: if Customers Partnerno > 0, so we try to find     */
/*  an entry within the DEBTLIMIT Table depend on Customers PartneNo.         */
/*  If the Creditlimit is reached, the returnvalue will be true,             */
/*  Otherwise false is returned                                              */
/*----------------------------------------------------------------------------*/
bool pxOrder::CheckForCreditSumOnTop()
{
    const long partnerno = Customer()->PartnerNr();

    if (partnerno == 0L)                        //just if there is a partnernumber
        return false;
    if (IsKreditLimitErreicht())
        return true;

    if (this->isCashOrder() || OrderType().IsDiscountAccount())
    {
        return false;
    }

    boost::shared_ptr<pxDebitLimit> lm = boost::make_shared<pxDebitLimit>(Session(), partnerno);
    if (!lm->IsGoodState() || (lm->Limit() == pxConstants::mZero))
    {
        return false;
    }

    bool limit = false;
    const nMoney orderValue = Session()->isBulgaria() ? CalcGrossShipValue() : WertLieferung_;

    if ((lm->SumAdvanceAccount() + orderValue) > lm->Limit())
    {
        if (!Session()->isGermany())
        {
            AddHeadTextLine(lm->SumAdvanceAccount() + WertLieferung_ - lm->Limit());
        }
        limit = true;
    }

    return limit;
}

/*----------------------------------------------------------------------------*/
/*  CompleteCreditLimit():                                                    */
/*  The DayTurnOver in the entry for customers partnerno will be increased    */
/*----------------------------------------------------------------------------*/
int
pxOrder::CompleteCreditLimit()
{
    // debtlimit is canceled during open order, so we must rewrite debtlimit
    /* if ( Param()->IsSCrema() )                   // OrderValue already written
    {
       return ErrorState();
    }
    */

    const long partnerno = Customer()->PartnerNr();

    if (   (partnerno == 0L)                    //just if there is a partnernumber
        || !IsOrderAffectingCreditLimit()
        || IsSeparatedOrder() )
    {
        return ErrorState();
    }

    if (Session()->isBulgaria())
    {
        // Increases K1 and K2 dayturnover
        const nMoney orderValue = CalcGrossShipValue();
        RedoCreditDayTurnOver(orderValue);
    }
    else
    {

        boost::shared_ptr<pxDebitLimit> lm = boost::make_shared<pxDebitLimit>(Session(), partnerno);
        if (!lm->IsGoodState()
            || (!Session()->isBulgaria() && (lm->Limit() == pxConstants::mZero)))
        {
            return ErrorState();
        }

        const nMoney orderValue = WertLieferung_;
        IncreaseDayTurnOver(lm.get(), orderValue);
    }
    return ErrorState();
}

bool pxOrder::IsOrderAffectingCreditLimit()
{
    return isCashOrder()
        || OrderType().IsDiscountAccount()
        || OrderType().IsBuyBack()
        || OrderType().IsProformaOrder()
        ? false : true;
}

/*----------------------------------------------------------------------------*/
/*  CheckCorruptLimit: check every Position within this order for corrupt     */
/*  limit, depend on entry within paraauftragbearb(DefwertKeinAbschl).        */
/*  If the Limit is reached on one Position within this order, so true       */
/*  will be returned, otherwise false is returned back to the caller.        */
/*  Please take care for a well constructed pxOrder object.                   */
/*----------------------------------------------------------------------------*/
bool
pxOrder::CheckCorruptLimit()
{
    nMoney corruptlimit = (double)Param()->DefwertKeinAbschl();
    if (corruptlimit == pxConstants::mZero)
        return false;

    // now check every position wihin this order
    bool limit = false;
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem* item;
    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (item->OrderCorruptValue() > corruptlimit)
        {
            limit = true;
            break;
        }
    }
    return limit;
}

nMoney
pxOrder::GetValueNetCash(const PriceTypeEnum pricetype)
{
    pxValuesCollect* entryp = ValuesCollectList()->Find(pricetype);
    return (entryp == NULL) ? pxConstants::mZero : entryp->ValueNetCash();
}

nMoney
pxOrder::GetValueSalesTax(const PriceTypeEnum pricetype)
{
    pxValuesCollect* entryp = ValuesCollectList()->Find(pricetype);
    return (entryp == NULL) ? pxConstants::mZero : entryp->ValueSalesTax();
}

/*----------------------------------------------------------------------------*/
/* ShowCreditLimit: This methode checks customers creditlimit depend on this  */
/* orders ShipValue.                                                          */
/* Reurns: bookable restvalue                                                 */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::ShowCreditLimit()
{
    return ShowCreditLimit2();
}

/*----------------------------------------------------------------------------*/
/* ShowCreditLimit1: This methode checks customers creditlimit depend on this */
/* orders ShipValue.                                                          */
/* Reurns: bookable restvalue from CreditLimitK1                              */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::ShowCreditLimit1()
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK1();                // get pointer to customers debtlimit entry
    return ShowCreditLimit(debtlimit);
}

/*----------------------------------------------------------------------------*/
/* ShowCreditLimit2: This methode checks customers creditlimit depend on this  */
/* orders ShipValue.                                                          */
/* Reurns: bookable restvalue                                                 */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::ShowCreditLimit2()
{
    pxDebitLimit* debtlimit = Customer()->DebitLimitK2();                // get pointer to customers debtlimit entry
    return ShowCreditLimit(debtlimit);
}

nMoney pxOrder::ShowCreditLimit(pxDebitLimit* debtlimit)
{
    if ((debtlimit == NULL) || !Session()->Device()->IsVideo() || (&OrderType() == NULL))  // only for manually order entry
    {
        return pxConstants::mZero;
    }

    return (debtlimit->Limit() - debtlimit->SumAdvanceAccount());
}

/*----------------------------------------------------------------------------*/
/* CalcShipValue: This methode checks the shipvalue depend on customers       */
/* paymentterms entries. This functions is used for the correct Creditlimit   */
/* calculation. If customers partnerno = 0(no CredeitLimit), no action done   */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::CalcGrossShipValue()
{
    pxCstPaymentTermsList* cPayTermsList = Customer()->CstPaymentTermsList();

    /*----------------------------------------------------------------------------*/
    /*  do some sanity checks                                                     */
    /*----------------------------------------------------------------------------*/
    if (   isCashOrder() || OrderType().IsDiscountAccount() || (Customer()->PartnerNr() == 0L)
        || (Session()->isBulgaria() && !Param()->IsSCrema() && (cPayTermsList == NULL)) ) // does not affect Cashorder and Rebateorder
    {
        return pxConstants::mZero;
    }

    nMoney shipValue = pxConstants::mZero;
    /*
    if ( cPayTermsList )                               // action
    {
        pxCstPaymentTerms* cPayTerms;
        pxCstPaymentTermsListIter iter( *cPayTermsList );      // define iterator
        iter.Reset();                                   // top of list
        while ( (cPayTerms = ( pxCstPaymentTerms*) ++iter) != NULL ) // browse list
        {
            if ( cPayTerms->PaymentTarget() == 0 )
                continue;
            if ( cPayTerms->PreisTyp() == LISTFIVE_PRICE )
            {
                shipValue -= GetValueNetCash(cPayTerms->PreisTyp());
                shipValue -= GetValueSalesTax(cPayTerms->PreisTyp());
            }
            else
            {
                shipValue += GetValueNetCash(cPayTerms->PreisTyp());
                shipValue += GetValueSalesTax(cPayTerms->PreisTyp());
            }
        }
        return shipValue;
    }
    */

    pxValuesCollectList* vCollist = ValuesCollectList();
    if (vCollist)
    {
        pxValuesCollect* entryp;
        pxValuesCollectListIter cursor(*vCollist);
        while ((entryp = (pxValuesCollect*) ++cursor) != NULL) // browse list
        {
            if (entryp->PriceType() != LISTFIVE_PRICE) // List5 items are added twice in list I-23061033
            {
                shipValue += entryp->ValueNetCash();
                shipValue += entryp->ValueSalesTax();
            }
        }
    }

    return shipValue;
}

/*----------------------------------------------------------------------------*/
/*  UndoCreditDayTurnOver():                                                  */
/*  The DayTurnOver in the entry for customers partnerno will be decreased by */
/*  the odervalue which is related to the sum of all positions checked against*/
/*  the Creditlimit This is for the bulgarian application without taking into account*/
/*  list5 items                                                               */
/*----------------------------------------------------------------------------*/
int
pxOrder::UndoCreditDayTurnOver()
{
    if (this->isCashOrder() || OrderType().IsDiscountAccount() || !Session()->isBulgaria())
    {
        return ErrorState();
    }

    nMoney orderValue = CalcGrossShipValue();

    /*
    nMoney List5Value;
    nMoney FreeSaleValue;
    nMoney HealtHFundValue;
    GetPriceTypeValues(List5Value, FreeSaleValue, HealtHFundValue);

    if (HealtHFundValue > pxConstants::mZero)
    {
        HealtHFundValue = HealtHFundValue - List5Value;
    }

    if ( (FreeSaleValue + HealtHFundValue + List5Value) == pxConstants::mZero )
    {
        return ErrorState();
    }

    if (UndoCreditDayTurnOver(Customer()->DebitLimitK2(), FreeSaleValue, HealtHFundValue, List5Value, false))
    {
        UndoCreditDayTurnOver(Customer()->DebitLimitK1(), FreeSaleValue, HealtHFundValue, List5Value, true);
    }
    */
    if (orderValue == pxConstants::mZero)
    {
        return ErrorState();
    }

    if (UndoCreditDayTurnOver(Customer()->DebitLimitK2(), orderValue))
    {
        UndoCreditDayTurnOver(Customer()->DebitLimitK1(), orderValue);
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  UndoCreditDayTurnOver(pxDebitLimit* lm, nMoney orderValue):               */
/*  The DayTurnOver in the entry for customers partnerno will be decreased by */
/*  the odervalue against the Creditlimit This is for the bulgarian application */
/*----------------------------------------------------------------------------*/
bool pxOrder::UndoCreditDayTurnOver(pxDebitLimit* lm, nMoney orderValue)
{
    if (lm == NULL)
    {
        return true;
    }

    lm->Get(cDBGET_READONLY);
    if (!lm->IsGoodState() || (lm->Limit() == pxConstants::mZero))
    {
        return false;
    }


    DecreaseDayTurnOver(lm, orderValue);

    return true;
}

// return: no error = true; otherwise = false
bool pxOrder::UndoCreditDayTurnOver(pxDebitLimit* lm, nMoney freeSaleValue, nMoney healtHFundValue, nMoney list5Value, bool bHandleListe5)
{
    if (lm == NULL)
    {
        return true;
    }

    lm->Get(cDBGET_READONLY);
    if (!lm->IsGoodState() || (lm->Limit() == pxConstants::mZero))
    {
        return false;
    }

    if (bHandleListe5 && !lm->IsListe5())
    {
        list5Value = pxConstants::mZero;
    }

    DecreaseDayTurnOver(lm, freeSaleValue + healtHFundValue + list5Value);

    return true;
}

/*----------------------------------------------------------------------------*/
/*  CancelCurrentCreditDayTurnOver:                                           */
/*  The DayTurnOver in the entry for customers partnerno will be decreased by */
/*  the odervalue which is related to the sum of all positions checked against*/
/*  the Creditlimit This is for the bulgarian application                     */
/*----------------------------------------------------------------------------*/
int
pxOrder::CancelCurrentCreditDayTurnOver()
{
    const long partnerno = Customer()->PartnerNr();

    if (   (partnerno == 0L)                         //just if there is a partnernumber
        || !Session()->isBulgaria() )
    {
        return ErrorState();
    }
    if (CancelCurrentCreditDayTurnOver(Customer()->DebitLimitK2()))
    {
        CancelCurrentCreditDayTurnOver(Customer()->DebitLimitK1());
    }

    return ErrorState();
}

// return: no error = true; otherwise = false
bool pxOrder::CancelCurrentCreditDayTurnOver(pxDebitLimit* lm)
{
    if (lm == NULL)
    {
        return false;
    }

    lm->Get(cDBGET_READONLY);
    if (!lm->IsGoodState() || (lm->Limit() == pxConstants::mZero))
    {
        return false;
    }

    DecreaseDayTurnOver(lm, GetOrderValuesDebtlimit());
    return true;
}

void pxOrder::DecreaseDayTurnOver(pxDebitLimit* lm, nMoney orderValue)
{
    nDBBeginTransaction(cDBTransRecord);
    {
        lm->DecreaseDayTurnOver(orderValue);
    }
    lm->Put();
    if (!lm->IsGoodState())
    {
        nDBRollBack();
    }
    else
    {
        nDBCommit(cDBTransRecord);
    }
}

/*----------------------------------------------------------------------------*/
/*  GetOrderValue: returns the order value depend on pricetype                */
/*  Cautions: just free sale and healthfund are reflected.                    */
/*  This methode is used in UndoCreditDayTurnOver for the bulgarian           */
/*  application during cancel order,  to decrease dayrurnover of the customers*/
/*  creditlimit.                                                              */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::GetOrderValue(const PriceTypeEnum pricetype)
{
    nMoney orderValue(0.0);

    if (!Session()->isBulgaria())
    {
        return orderValue;
    }

    if (OrderValues())
    {
        switch (pricetype)
        {
        case FREESALE_PRICE:
        {
            orderValue = Customer()->IsRebateMethFreeSale() ? OrderValues()->OrdValFtaxFS() : OrderValues()->OrdValFtaxFSDisc();
            break;
        }
        case HEALTHFUND_PRICE:
        {
            orderValue = Customer()->IsRebateMethHealthf() ? OrderValues()->OrdValFtaxHF() : OrderValues()->OrdValFtaxHFDisc();
            break;
        }
        case LISTFIVE_PRICE:
        {
            orderValue = GetOrderValueListFiveMembers();
            ReCalcValuesOrderValues();
            break;
        }
        default:
            break;
        }
    }
    return orderValue;
}

/*----------------------------------------------------------------------------*/
/*  GetOrderValueValueListFiveMembers: returns the order value for List5Pos   */
/*  Cautions: just healthfund are reflected.                                  */
/*  This methode is used in UndoCreditDayTurnOver for the bulgarian           */
/*  application during cancel order,  to decrease dayrurnover of the customers*/
/*  creditlimit.                                                              */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder::GetOrderValueListFiveMembers()
{
    nMoney healtHFundValue(0.0);

    if (!Session()->isBulgaria() || !OrderValues())
    {
        return healtHFundValue;
    }

    //save  HealtHFundValue for later use
    const nMoney saveHealtHFundValue = Customer()->IsRebateMethHealthf() ? OrderValues()->OrdValFtaxHF() : OrderValues()->OrdValFtaxHFDisc();

    pxOrderItemListIter iterator(*ItemList());
    pxOrderItem* item;
    while ((item = (pxOrderItem*) ++iterator) != NULL) // browse item list
    {
        if (item->IsArticleListFiveMember())
        {
            OrderValues()->ReduceOrderValues(item, item->MengeBestaetigt());
        }
    }
    healtHFundValue = Customer()->IsRebateMethHealthf() ? OrderValues()->OrdValFtaxHF() : OrderValues()->OrdValFtaxHFDisc();

    return saveHealtHFundValue - healtHFundValue;
}

/*----------------------------------------------------------------------------*/
/*  RedoCreditDayTurnOver():                                                  */
/*  The DayTurnOver in the entry for customers partnerno will be increased by */
/*  the odervalue which is related to the sum of all positions checked against*/
/*  the Creditlimit This is for the bulgarian application                     */
/*----------------------------------------------------------------------------*/
int
pxOrder::RedoCreditDayTurnOver(nMoney orderValue)
{
    if ((AnzPos_ == 0) || !IsOrderAffectingCreditLimit() || !Session()->isBulgaria())
    {
        return ErrorState();
    }

    /*
    nMoney List5Value;
    nMoney FreeSaleValue;
    nMoney HealtHFundValue;
    GetPriceTypeValues(List5Value, FreeSaleValue, HealtHFundValue);
    */

    if (orderValue == pxConstants::mZero)
    {
        return ErrorState();
    }

    if (RedoCreditDayTurnOver(Customer()->DebitLimitK2(), orderValue))
    {
        RedoCreditDayTurnOver(Customer()->DebitLimitK1(), orderValue);
    }

    return ErrorState();
}


void pxOrder::GetPriceTypeValues(nMoney& list5Value, nMoney& freeSaleValue, nMoney& healtHFundValue)
{
    const long AnzPosFreeSale = CountPriceTypeItems(FREESALE_PRICE);
    const long AnzPosHealthFund = CountPriceTypeItems(HEALTHFUND_PRICE);
    const long AnzPosList5 = CountPriceTypeItems(LISTFIVE_PRICE);

    list5Value = (AnzPosList5 > 0) ? CalculatePriceTypeValue(LISTFIVE_PRICE) : nMoney(0.0);
    freeSaleValue = (AnzPosFreeSale > 0) ? CalculatePriceTypeValue(FREESALE_PRICE) : nMoney(0.0);
    healtHFundValue = (AnzPosHealthFund > 0) ? CalculatePriceTypeValue(HEALTHFUND_PRICE) : nMoney(0.0);
}

nMoney pxOrder::CalculatePriceTypeValue(PriceTypeEnum priceType)
{
    nMoney value(0.0);

    if (!(Customer()->IsCashPayer()))
    {
        value = GetOrderValue(priceType);
    }
    //else if ((priceType != LISTFIVE_PRICE) && (DatumValuta_ != pxConstants::NullDate))
    else if (DatumValuta_ != pxConstants::NullDate)
    {
        value = GetOrderValue(priceType);
    }
    return value;
}

// return: no error = true; otherwise = false
bool pxOrder::RedoCreditDayTurnOver(pxDebitLimit* lm, nMoney orderValue)
{
    if (lm == NULL)
    {
        return true;
    }

    lm->Get(cDBGET_READONLY);
    if (!lm->IsGoodState() || (lm->Limit() == pxConstants::mZero))
    {
        return false;
    }

    //if (!(lmK->IsListe5())) only with lmK1 !!!
    //{
    //    List5Value = pxConstants::mZero;
    //}
    //IncreaseDayTurnOver(lmK, FreeSaleValue + HealtHFundValue + List5Value);

    IncreaseDayTurnOver(lm, orderValue);

    return true;
}

/*----------------------------------------------------------------------------*/
/*  checkCreditLimitOverflow():                                               */
/*----------------------------------------------------------------------------*/
nMoney pxOrder::checkCreditLimitOverflow()
{
    nMoney diffValue = 0.0;

    if (isCashOrder() || OrderType().IsDiscountAccount() || !Session()->isBulgaria())   // does not affect Cashorder and Rebateorder
    {
        return diffValue;
    }

    // Ticket SR-17110160
    if (mustDoCheckCreditLimitCheck() == false)
    {
        return diffValue;
    }

    if (!checkCreditLimitOverflow(Customer()->DebitLimitK2(), diffValue))
    {
        checkCreditLimitOverflow(Customer()->DebitLimitK1(), diffValue);
    }

    return diffValue;
}

// return: diffValue calculated = true; otherwise = false
bool pxOrder::checkCreditLimitOverflow(pxDebitLimit* lm, nMoney& diffValue)
{
    diffValue = 0.0;

    if (lm == NULL)
    {
        return false;
    }

    lm->Get(cDBGET_READONLY);
    if (!lm->IsGoodState() || (lm->Limit() == pxConstants::mZero))
    {
        return true;
    }

    if (lm->SumAdvanceAccount() > lm->Limit())
    {
        diffValue = lm->SumAdvanceAccount() - lm->Limit();
        return true;
    }

    return false;
}
