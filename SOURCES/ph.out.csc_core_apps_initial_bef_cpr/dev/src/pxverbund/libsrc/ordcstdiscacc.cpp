#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxbase/pxconstants.hpp"

#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxcstdiscacc.hpp"
#include "pxcstdiscaccdef.h"
#include "pxtcasession.hpp"
#include "pxbalancecollect.hpp"
#include "pxordervalues.hpp"
#include "pxorderdiscacc.hpp"

/*----------------------------------------------------------------------------*/
/*  DecreaseCstDiscAcc: this methode decreases customer discount account      */
/*  by ShipValue()(table cstdiscacc). Take care for a well constructed        */
/*  pxOrder object to prevent unpredictable results.                          */
/*  Return values:  nMoney object with current Balance  or                    */
/*                  pxConstants::mZero if there is no entry found             */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder :: DecreaseCstDiscAcc
(
    nMoney   ShipValue,
    short
)
{
    if (CstDiscountAccount() == NULL )        // maybe we are not in BG
    {
        return pxConstants::mZero;
    }
    if ( ShipValue == pxConstants::mZero )                 // maybe new item
    {
        return pxConstants::mZero;
    }
    SumCstDiscAccBalances();
    BalanceCollectList()->DecreaseBalance(ShipValue, 0);

    return BalanceCollectList()->GetBalance(0);
}

/*----------------------------------------------------------------------------*/
/*  IncreaseCstDiscAcc: this methode adds the sipvalue back to                */
/*  customers discount account(table cstdiscacc). Take care for a well        */
/*  constucted pxOrder object to prevent unpredictable results                */
/*  Return values:  nMoney object with current Balance  or                    */
/*                  pxConstants::mZero if there is no entry found             */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder :: IncreaseCstDiscAcc
(
    nMoney ShipValue,
    short
)
{
    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        return pxConstants::mZero;
    }
    SumCstDiscAccBalances();

    if ( ShipValue == pxConstants::mZero )                   // maybe new item
    {
        return BalanceCollectList()->GetBalance(0);
    }
    BalanceCollectList()->IncreaseBalance(ShipValue, 0);

    return BalanceCollectList()->GetBalance(0);
}

/*----------------------------------------------------------------------------*/
/*  SetCurrentCstDiscAccBalance: sets the current Restbalance into the        */
/*  BalanceCollectionList depend on the value of the already booked ordervalue*/
/*  within the OrderValues Object and the TaxLevel.                           */
/*  It returns the current Balance in the Listvel.                            */
/*  This is a special methode for the Bulgarien application on Ordertype RO   */
/*----------------------------------------------------------------------------*/
nMoney
pxOrder :: SetCurrentCstDiscAccBalance
(
    short
)
{
    nMoney         ordervalue(0.0);

    if (!Session()->isBulgaria())
    {
        return pxConstants::mZero;
    }
    if ( RODateFrom_ == pxConstants::NullDate && RODateTo_ == pxConstants::NullDate )
    {
        return pxConstants::mZero;
    }

    if ( OrderValues() )
    {
        if ( OrderValues()->OrdValGrossFS() > pxConstants::mZero )
        {
            ordervalue = OrderValues()->OrdValGrossFS();
        }

        if ( OrderValues()->OrdValGrossHF()  > pxConstants::mZero )
        {
            ordervalue += OrderValues()->OrdValGrossHF();
        }

        if ( OrderValues()->OrdValGrossRS()  > pxConstants::mZero )
        {
            ordervalue += OrderValues()->OrdValGrossRS();
        }
        BalanceCollectList()->SetBalance(ordervalue, 0);
    }
    return BalanceCollectList()->GetBalance(0);
}

/*----------------------------------------------------------------------------*/
/*  CloseCstDiscAccBalance: this methode loops thru the item list and reduces */
/*  the balance values withhin the  CstDiscountAccountList under respect of   */
/*  Items TaxLevel. Also the Branch numbers are stored into                   */
/*  CstDiscountAccountList->ArrayBranchNo. This is necessary for later use    */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CloseCstDiscAccBalance
(
)
{
    pxOrderDiscAcc *DiscAccEntryp = NULL;
    bool bOrderNoCics = false;

    if ( !(OrderType().IsDiscountAccount()) )
        return ErrorState();

    if ( IsPseudoLock() )               // no action
    {
        return ErrorState();
    }

    if ( IsDoNotConnectDKRAK() )
    {
        return ErrorState();
    }

    if ( AnzPos_ == 0 )
    {
        return ErrorState();
    }

    if ( IsEntryClosed() || DatumAuslieferung() != pxConstants::NullDate)
    {
        BookOrderValueCstDiscAccVSE();
        if ( !IsGoodState() )
        {
            if ( !(Session()->Device()->IsVideo()))
            {
                ConfirmOrderDiscAcc();
            }
            return ErrorState();
        }
        if ( DatumAuslieferung() != pxConstants::NullDate )
        {
            SetDoNotConnectDKRAK();
        }
    }

    if ( CstDiscountAccount() == NULL)           // maybe we are not in BG
    {                                            // only main order should have CstDiscountAccount pointer
        if ( OrderDiscAccList() )
        {
            if ( OrderDiscAccList()->Entries() == 0 )
            {
                return ErrorState();
            }
            else
            {
                bOrderNoCics = true;
            }
        }
    }

    if ( RODateFrom_ > pxConstants::NullDate && RODateTo_ > pxConstants::NullDate && !bOrderNoCics)
    {
        CstDiscountAccount()->SetArrayBranchNo(Customer()->Vertriebszentrum());
    }

    if ( !bOrderNoCics )
    {
        short*     ArrayBranchNo = CstDiscountAccount()->ArrayBranchNo(); // Array of discounttypes within dlist
        int        ArrayIndex = 0;                                   // Index for this Array
/*----------------------------------------------------------------------------*/
/*  Now scan the ArrayBranchNo                                                */
/*  For each branchno found within this array, an KDAUFTRAGDISCACC will be    */
/*  written to the Datebase                                                   */
/*----------------------------------------------------------------------------*/
        for (ArrayIndex = 0; ArrayBranchNo[ArrayIndex] > 0 ; ++ArrayIndex)
        {
            if (OrderDiscAccList() )
            {
                DiscAccEntryp = new  pxOrderDiscAcc(Session(), CstDiscountAccount()->GetArrayBranchNo(ArrayIndex), KdAuftragNr_);
                if ( !DiscAccEntryp->Get(cDBGET_READONLY) )   // record already written
                {
                    continue;
                }
                DiscAccEntryp->SetSwChain( ROChain_ );
                DiscAccEntryp->SetDateFrom( RODateFrom_ );
                DiscAccEntryp->SetDateTo( RODateTo_ );
                DiscAccEntryp->Put();
                if ( DiscAccEntryp->IsGoodState() )
                {
                    OrderDiscAccList()->Append( DiscAccEntryp);
                }
            }
        }
    }

    if ( IsEntryClosed() || DatumAuslieferung() != pxConstants::NullDate )
    {
        RemoveDiscAccEntries();
    }
    return ErrorState();
}

void
pxOrder :: UnlockCstDiscAccEntry
(
    pxCstDiscAcc* entryp
)
{
    nDBBeginTransaction(cDBTransRecord);
    entryp->Get(cDBGET_FORUPDATE);
    if ( IsGoodState() )
    {
        entryp->SetKdAuftragNr(0);
        entryp->Put();
        if ( IsGoodState() )
        {
            nDBCommit(cDBTransRecord);
        }
        else
        {
            nDBRollBack();
        }
        Error() = entryp->Error();
    }
    else
    {
        nDBRollBack();
    }
}

/*----------------------------------------------------------------------------*/
/* UnLockCstDiscAcc: this methode updates the customers discount account      */
/* entries.It looks for entries where kdauftragnr == current kdauftragnr and  */
/* if equal, kdauftragnr will be set to 0 on those entries                    */
/*----------------------------------------------------------------------------*/
int
pxOrder :: UnLockCstDiscAccEntries
(
)
{
    ClearError();
    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        return ErrorState();
    }

    pxCstDiscAccListIter   iter( *CstDiscountAccount_ );    // define iterator
    pxCstDiscAcc           *entryp = NULL;                  // pointer to listentry

    iter.Reset();                                           // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( entryp->KdAuftragNr() == KdAuftragNr() )
        {
            UnlockCstDiscAccEntry( entryp );
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* LockCstDiscAcc: this methode updates the customers discount account entries*/
/* The currenr order number will be placed into each entry of the             */
/* CsrDiscountAccountList                                                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: LockCstDiscAccEntries
(
)
{
    ClearError();
    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        return ErrorState();
    }

    if ( IsPseudoLock() )               // no action
    {
        return ErrorState();
    }

    pxCstDiscAccListIter   iter( *CstDiscountAccount_ );    // define iterator
    pxCstDiscAcc           *entryp = NULL;                  // pointer to list entry

    iter.Reset();                                           // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( entryp->KdAuftragNr() == 0 )
        {
            if ( entryp->VoucherTyp() == cDISCACC_CREDIT_VOUCHER  )
            {
                entryp->SetRemainInList();
                continue;
            }
            nDBBeginTransaction(cDBTransRecord);
            entryp->Get(cDBGET_FORUPDATE);
            if ( IsGoodState() )
            {
                entryp->SetKdAuftragNr(KdAuftragNr_);
                entryp->Put();
                if ( IsGoodState() )
                {
                    nDBCommit(cDBTransRecord);
                }
                Error() = entryp->Error();
            }
        }
    }

    nDBBeginTransaction(cDBTransSet);

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* GetCstDiscAccMainCstNo: this methode looks for a MainCstNo within the list */
/* Returns MainCstNo or 0 if nothing found                                    */
/*----------------------------------------------------------------------------*/
long
pxOrder :: GetCstDiscAccMainCstNo
(
)
{
    long retval = 0;
    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        return retval;
    }

    pxCstDiscAccListIter   iter( *CstDiscountAccount_ );    // define iterator
    pxCstDiscAcc           *entryp = NULL;                  // pointer to listentry


    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( entryp->MainCstNo() != 0 )
        {
            retval = entryp->MainCstNo();
            break;
        }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/* ShrinkCstDiscountAccount: this methode shrinks this list to valid entries  */
/* for this CustomerNo                                                        */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ShrinkCstDiscountAccount
(
    const long CustomerNo
)
{
    int retval = 0;
    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        return retval;
    }

    if ( ROChain_ != 0 )                        // it reflect the string of customer
        return retval;

    pxCstDiscAccListIter   iter( *CstDiscountAccount_ );    // define iterator
    pxCstDiscAcc           *entryp = NULL;                  // pointer to listentry


    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( entryp->CustomerNo() != CustomerNo )
        {
            delete iter.Remove();
            continue;
        }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  SumCstDiscAccBalances: this methode buildsup the temp list                */
/*  BalanceCollectList                                                        */
/*----------------------------------------------------------------------------*/
int
pxOrder :: SumCstDiscAccBalances
(
)
{
    pxBalanceCollect* collectentryp = NULL;
    pxCstDiscAccList* vlistp = NULL;
    nMoney CreditVoucher(0.0);

    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        return ErrorState();
    }
    if ( BalanceCollectList() && (BalanceCollectList()->Entries() > 0))
    {
        return ErrorState();
    }
    pxCstDiscAccListIter   iter( *CstDiscountAccount_ );    // define iterator
    pxCstDiscAcc           *entryp = NULL;                  // pointer to listentry

    iter.Reset();                                           // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( entryp->VoucherTyp() == cDISCACC_CREDIT_VOUCHER  )
        {
            CreditVoucher += entryp->Balance();
            continue;
        }
        if ( collectentryp == NULL )
        {
            collectentryp = new pxBalanceCollect( entryp->Balance(), entryp->Balance(), 0 );
            BalanceCollectList_->Append( collectentryp );
        }
        else
        {
            collectentryp->IncreaseBalance(      entryp->Balance() );
            collectentryp->IncreaseTotalBalance( entryp->Balance() );
        }
    }

    if ( collectentryp )
    {
        collectentryp->DecreaseBalance(CreditVoucher);
        collectentryp->DecreaseTotalBalance(CreditVoucher);
    }
    if ( !IsNewOrder() )
    {
        vlistp = new pxCstDiscAccList( Session() );
        if ( ROChain_ == 0 )
        {
            vlistp->Select(Customer()->Vertriebszentrum(),IDFNr_,RODateFrom_,RODateTo_,cDISCACC_CREDIT_VOUCHER);
        }
        else
        {
            vlistp->Select( Customer()->MainCstNo(), RODateFrom_, RODateTo_,cDISCACC_CREDIT_VOUCHER);
        }
        if ( vlistp->Entries() > 0 )
        {
            pxCstDiscAccListIter   cursor( *vlistp );    // define iterator
            while ( ( entryp = ( pxCstDiscAcc*) ++cursor) != NULL ) // browse list
            {
                if ( entryp->VoucherTyp() == cDISCACC_CREDIT_VOUCHER  )
                {
                    CreditVoucher += entryp->Balance();
                }
            }
            if ( collectentryp )
            {
                collectentryp->DecreaseBalance(CreditVoucher);
                collectentryp->DecreaseTotalBalance(CreditVoucher);
            }
        }
        delete vlistp;
        ReCalcSumCstDiscAccBalances();
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  GetCstDiscAccBalance: this methode returns the Balance for a given        */
/*  TaxLevel. Source is the BalanceCollectList                                */
/*  Take care for a well constructed  BalanceCollectList                      */
/*----------------------------------------------------------------------------*/
double
pxOrder :: GetCstDiscAccBalance
(
    const short
)
{
    double  balance(0.0);

    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        return balance;
    }
    SumCstDiscAccBalances();                    // Build up sum collection list
    if ( BalanceCollectList() )
    {
        if ( BalanceCollectList()->Entries() > 0 )
        {
            return BalanceCollectList()->GetBalance(0);
        }
    }
    return balance;
}

/*----------------------------------------------------------------------------*/
/*  ReCalcSumCstDiscAccBalances: loop thru the ItemList to reduce the balance */
/*  within the BalanceCollectList under respect of Items TaxLevel             */
/*  Take care for a well constructed  BalanceCollectList                      */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ReCalcSumCstDiscAccBalances
(
)
{
    int  retval  = 0;

    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        return retval;
    }
    if ( BalanceCollectList() )
    {
        if ( BalanceCollectList()->Entries() == 0 )
        {
            return retval;
        }
    }
    SetCurrentCstDiscAccBalance((short) 0);
    return retval;
}

/*----------------------------------------------------------------------------*/
/* RemoveDiscAccEntries: this methode removes all entries within              */
/* CstDiscountAccount list.                                                   */
/*----------------------------------------------------------------------------*/
int
pxOrder :: RemoveDiscAccEntries
(
)
{
    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        return ErrorState();
    }

    if ( CstDiscountAccount()->Entries() == 0 )
    {
        return ErrorState();
    }

    pxCstDiscAccListIter   iter( *CstDiscountAccount_ );    // define iterator
    pxCstDiscAcc           *entryp = NULL;                  // pointer to listentry

    if ( KdAuftragNrOrg_ == 0 )
    {
        ReleaseCstDiscAccVSE();
        if ( !IsGoodState() )
        {
            return ErrorState();
        }
    }

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( entryp->KdAuftragNr() == KdAuftragNr() )
        {
            nDBBeginTransaction(cDBTransRecord);
            entryp->Delete();
            if ( entryp->IsGoodState() )
            {
                nDBCommit(cDBTransRecord);
            }
            Error() = entryp->Error();
            delete iter.Remove();
            entryp = NULL;
        }
    }

    nDBBeginTransaction(cDBTransSet);
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* CancelRebateOrder: this methode removes all entries within                 */
/* CstDiscountAccount list and release DKRAK records on Pharmos side.         */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CancelRebateOrder
(
)
{
    if (!Session()->isBulgaria())
    {
        return ErrorState();
    }

    if ( CstDiscountAccount() == NULL )         // maybe we are not in BG
    {
        if ( OrderDiscAccList() )
        {
            if ( OrderDiscAccList()->Entries() == 0 )
            {
                return ErrorState();
            }
        }
    }

    if ( DatumAuslieferung() != pxConstants::NullDate )
    {
        if ( KdAuftragNrOrg_ == 0 && AnzPos_ > 0 && !IsNewOrder() )
        {
            CancelDelayedDeliveryOrderVSE();
            return ErrorState();
        }
    }

    if ( KdAuftragNrOrg_ == 0 )
    {
        ReleaseChangeCstDiscAccVSE();
        if (!IsGoodState() )
        {
            return ErrorState();
        }
    }
    UnLockCstDiscAccEntries();
    if ( IsGoodState() )
    {
        delete CstDiscountAccount_;
        CstDiscountAccount_ = NULL;
        SetRODateFrom(0L);
        SetRODateTo(0L);
    }

    nDBBeginTransaction(cDBTransSet);
    nDBCommit(cDBTransSet);          // commit changes
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* ConfirmOrderDiscAcc: this methode inserts an entry within the table        */
/* kdauftragdiscacc, This is important for reopening an order                 */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ConfirmOrderDiscAcc
(
)
{
    pxOrderDiscAcc *DiscAccEntryp = NULL;
    if ( CstDiscountAccount() == NULL )          // maybe we are not in BG
    {                                            // only main order should have CstDiscountAccount pointer
        return ErrorState();
    }
    if ( RODateFrom_ > pxConstants::NullDate && RODateTo_ > pxConstants::NullDate )
    {
        CstDiscountAccount()->SetArrayBranchNo( Customer()->Vertriebszentrum() );
    }

    short* ArrayBranchNo = CstDiscountAccount()->ArrayBranchNo(); // Array of discounttypes within dlist

    /*----------------------------------------------------------------------------*/
    /*  Now scan the ArrayBranchNo                                                */
    /*  For each branchno found within this array, an KDAUFTRAGDISCACC will be    */
    /*  written to the Datebase                                                   */
    /*----------------------------------------------------------------------------*/
    for (int ArrayIndex = 0; ArrayBranchNo[ArrayIndex] > 0 ; ++ArrayIndex)
    {
        if (OrderDiscAccList() )
        {
            DiscAccEntryp = new pxOrderDiscAcc( Session(), CstDiscountAccount()->GetArrayBranchNo(ArrayIndex), KdAuftragNr_ );
            if ( !DiscAccEntryp->Get(cDBGET_READONLY) )   // record already written
            {
                delete DiscAccEntryp;
                DiscAccEntryp = NULL;
                continue;
            }
            nDBBeginTransaction(cDBTransRecord);
            DiscAccEntryp->SetSwChain( ROChain_ );
            DiscAccEntryp->SetDateFrom( RODateFrom_ );
            DiscAccEntryp->SetDateTo( RODateTo_ );
            DiscAccEntryp->Put();
            if ( DiscAccEntryp->IsGoodState() )
            {
                OrderDiscAccList()->Append( DiscAccEntryp);
                if ( DiscAccEntryp->IsGoodState() )
                {
                    nDBCommit(cDBTransRecord);
                }
                Error() = DiscAccEntryp->Error();
            }
        }
    }

    nDBBeginTransaction(cDBTransSet);
    return ErrorState();
}
