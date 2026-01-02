#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "pxcstdiscacc.hpp"
#include "pxttype.hpp"
#include <tcawrap.h>
#include "pxtcasession.hpp"
#include "pxtcarecord.h"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

#include "pxdkrakresult.hpp"
#include "dkraklockstmt.hpp"
#include "dkrakinvoicelockedstmt.hpp"
#include "dkrakusagestmt.hpp"
#include "dkrakreleasestmt.hpp"
#include "dkrakprioritystmt.hpp"
#include "dkrakbookordervaluestmt.hpp"
#include "dkrakreleasechangestmt.hpp"
#include "dkrakcanceldeldeliveryorderstmt.hpp"
#include "pxbalancecollect.hpp"
#include "pxorderdiscacc.hpp"
#include "pxordervalues.hpp"

/*----------------------------------------------------------------------------*/
/*  SyncCstDiscAccVse:                                                        */
/*----------------------------------------------------------------------------*/
int
pxOrder :: SyncCstDiscAccVse
(
)
{
    int  retval    = 0;
    char    ResultBuffer[1024];
    nString key;

    // Check Time slot
    pxTimeTypeList timelist( Session() );
    timelist.Select( Type_ADS_REBATE_ORDER, key, Customer()->Vertriebszentrum() );
    if ( timelist.Entries() )
    {
        if ( !timelist.TimeInWindow() )
        {
            ExternalError( CMsgStream(), CMSG_ORD_ROTIME_NOTINWINDOW );
            return 0;
        }
    }

    pxTcaSession* vse = Session()->GetTcaSessionEntry( FilialNr_ );
    if ( vse == NULL )
    {
        ExternalError( CMsgStream(), CMSG_TCACCESS_NO_INIFILE, FilialNr_ );
        return 0;
    }

    if ( !IsPseudoLock() )          // order entry
    {
       retval = vse->ConnectToCics();
       if ( retval == 0 )
       {
          if ( CstDiscountAccount_ )
          {
             delete CstDiscountAccount_;
             CstDiscountAccount_ = NULL;
          }
          ROMainCstNo_   = 0;
          ROChain_       = 0;
          SetRODateFrom( 0L );
          SetRODateTo(   0L );
          ExternalError( CMsgStream(), CMSG_TCACCESS_ERROR );
          return retval;
       }
    }

    if ( CstDiscountAccount() == NULL )
    {
        ExternalError( CMsgStream(), CMSG_ORD_CSTDISCACC_NOENTRIES );
        return  0;
    }
    else if ( GetCstDiscAccBalance((short)0) <= 0.0 )
    {
        ExternalError(CMsgStream(), CMSG_ORD_CSTDISCACC_NOBALANCE);
        return  0;
    }

    // also set by pxOrder::OpenInfo
    if ( IsPseudoLock() )          // proforma order
       return 1;

    DKRAKLockStmt lockStmt;
    lockStmt.SetBranchNo( FilialNr_ );
    lockStmt.SetCustomerNo( IDFNr_ );
    lockStmt.SetDateFrom( RODateFrom_.GetYYYYMMDD() );
    lockStmt.SetDateTo( RODateTo_.GetYYYYMMDD() );
    lockStmt.SetOrderNo( KdAuftragNr_ );
    lockStmt.SetRabateChainEnabled( ROChain_ == 1 );

    retval = vse->SendDataToCics( lockStmt.ToString(), ResultBuffer, sizeof(ResultBuffer) );
    if ( retval == 0 ) // on error
    {
       UnLockCstDiscAccEntries();
       if ( IsGoodState() )
       {
          delete CstDiscountAccount_;
          CstDiscountAccount_ = NULL;
          SetRODateFrom(0L);
          SetRODateTo(0L);
       }
       return retval;
    }

    pxDkrakResult dkrakresult( ResultBuffer );  // hard bound to ResultBuffer pointer
    double CstDiscAccBalance  = GetCstDiscAccBalance( (short)0 );
    double DkrakNormalBalance = dkrakresult.NormalBalance();

    // are both values equal (with two digits decimal precision)
    if( int(CstDiscAccBalance * 100) != int(DkrakNormalBalance * 100) )
    {
       while ( dkrakresult.LockCount() > 0 )
       {
           pxCstDiscAcc* entryp = CstDiscountAccount()->Find( dkrakresult.BranchNo(), dkrakresult.CustomerNo(), dkrakresult.DocumentNo(),
                                                              dkrakresult.VoucherType(), dkrakresult.LfdNr() );
          if ( entryp )
          {
              entryp->SetInvoicePaid(    dkrakresult.InvoiceAmountPaid() );
              entryp->CalcPaymentTarget( dkrakresult.DueDate(), dkrakresult.LastPaymentDate() );
              entryp->SetRemainInList();  // entry found must stay in list
          }

          if ( dkrakresult.LockCount() == 1 )
              break;

          DKRAKInvoiceLockedStmt invoiceLockStmt;
          invoiceLockStmt.SetAvailability(       entryp != NULL            );
          invoiceLockStmt.SetBranchNo(           dkrakresult.BranchNo()    );
          invoiceLockStmt.SetCustomerNo(         dkrakresult.CustomerNo()  );
          invoiceLockStmt.SetDocumentType(       dkrakresult.VoucherType() );
          invoiceLockStmt.SetInvoiceNo(          dkrakresult.DocumentNo()  );
          invoiceLockStmt.SetLockCount(          dkrakresult.LockCount()   );
          invoiceLockStmt.SetManufacturerNo(     dkrakresult.LfdNr()       );
          invoiceLockStmt.SetOrderNo(            KdAuftragNr_              );
          invoiceLockStmt.SetRabateChainEnabled( ROChain_ == 1             );

          // this statement automatically changes dkrakresult because it is bound to ResultBuffer pointer
          retval = vse->SendDataToCics( invoiceLockStmt.ToString(), ResultBuffer, sizeof(ResultBuffer) );
          if ( retval == 0 )
             return retval;
       }
    }
    else // values not equal
    {
        CstDiscountAccount()->MarkEntriesRemainInList();
    }

    CstDiscountAccount()->ShrinkAndUnlockRemainInList();
    if ( BalanceCollectList() )
    {
       delete  BalanceCollectList_;
       BalanceCollectList_ = NULL;
       GetCstDiscAccBalance((short)0);
    }

    if ( CstDiscountAccount()->Entries() == 0 )
    {
       // do some init work to prevent unpredictable results
       delete  CstDiscountAccount_;
       CstDiscountAccount_ = NULL;
       ROMainCstNo_   = 0;
       ROChain_       = 0;
       SetRODateFrom( 0L );
       SetRODateTo(   0L );
       retval         = 0;
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  ChangeUsageCstDiscAcc:                                                    */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ChangeUsageCstDiscAcc
(
    const short     BranchNo,
    const long     CustomerNo,
    const long     InvoiceDate,
    const nString&  InvoiceNo,
    const nString&  VoucherTyp
)
{
    int  retval = 0;
    char  ResultBuffer[1024];

    pxTcaSession* vse = Session()->GetTcaSessionEntry(FilialNr_);
    if ( vse == NULL )
       return 1;

    retval = vse->ConnectToCics();
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       return retval;
    }

    if ( CstDiscountAccount() == NULL )
    {
       return retval;
    }

    pxCstDiscAcc* entryp = CstDiscountAccount()->Find( BranchNo, CustomerNo, nDate(InvoiceDate), InvoiceNo, VoucherTyp );
    if (entryp == NULL )
    {
       return retval;
    }

    DKRAKUsageStmt usageStmt;
    usageStmt.SetBranchNo(       entryp->BranchNo() );
    usageStmt.SetCustomerNo(     entryp->CustomerNo() );
    usageStmt.SetDateFrom(       entryp->Date() );
    usageStmt.SetDocumentType(   VoucherTyp() );
    usageStmt.SetInvoiceNo(      entryp->InvoiceNumber() );
    usageStmt.SetManufacturerNo( entryp->LfdNr() );
    usageStmt.SetOrderNo(        KdAuftragNr_ );
    usageStmt.SetRabateChainEnabled( ROChain_ == 1 );

    retval = vse->SendDataToCics( usageStmt.ToString(), ResultBuffer, sizeof(ResultBuffer) );
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       return retval;
    }

    UnlockCstDiscAccEntry( entryp );

    DecreaseCstDiscAcc( entryp->Balance(), (short)0 );
    BalanceCollectList()->DecreaseTotalBalance( entryp->Balance(), (short)0 );

    // and delete entryp from the list
    delete CstDiscountAccount()->Remove(entryp);
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  ChangePriorityCstDiscAcc:                                                 */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ChangePriorityCstDiscAcc
(
    const short     BranchNo,
    const long     CustomerNo,
    const long     InvoiceDate,
    const nString&  InvoiceNo,
    const nString&  VoucherTyp,
    const short    Priority
)
{
    int  retval = 0;
    char  ResultBuffer[1024];
    pxCstDiscAcc* entryp  = NULL;

    pxTcaSession* vse = Session()->GetTcaSessionEntry(FilialNr_);
    if ( vse == NULL )
        return 1;

    retval = vse->ConnectToCics();
    if ( retval == 0 )
    {
        ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
        return retval;
    }

    if ( CstDiscountAccount() == NULL )
    {
        return retval;
    }

    entryp = CstDiscountAccount()->Find( BranchNo, CustomerNo, nDate(InvoiceDate), InvoiceNo, VoucherTyp );
    if ( entryp == NULL )
    {
        return retval;
    }

    DKRAKPriorityStmt priorityStmt;
    priorityStmt.SetBranchNo( entryp->BranchNo() );
    priorityStmt.SetCustomerNo( entryp->CustomerNo() );
    priorityStmt.SetDateFrom( entryp->Date() );
    priorityStmt.SetDocumentType( entryp->VoucherTyp() );
    priorityStmt.SetInvoiceNo( entryp->InvoiceNumber() );
    priorityStmt.SetManufacturerNo( entryp->LfdNr() );
    priorityStmt.SetOrderNo( KdAuftragNr_ );
    priorityStmt.SetRabateChainEnabled( ROChain_ == 1 );
    priorityStmt.SetPriorityEnabled( Priority == 1 );

    retval = vse->SendDataToCics( priorityStmt.ToString(), ResultBuffer, sizeof(ResultBuffer) );
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       return retval;
    }

    nDBBeginTransaction(cDBTransRecord);
    entryp->Get(cDBGET_FORUPDATE);
    if ( entryp->IsGoodState() )
    {
       entryp->SetPriority( Priority );
       entryp->Put();
       if ( entryp->IsGoodState() )
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

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  ReleaseCstDiscAccVSE                                                      */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ReleaseCstDiscAccVSE
(
)
{
    int  retval = 0;
    char  ResultBuffer[1024];

    if ( CstDiscountAccount() == NULL )
    {
       return retval;
    }

    pxTcaSession* vse = Session()->GetTcaSessionEntry(FilialNr_);
    if ( vse == NULL )
       return 1;

    retval = vse->ConnectToCics();
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       SetNoCics();
       return retval;
    }

    // call VSE
    DKRAKReleaseStmt releaseStmt;
    releaseStmt.SetBranchNo(   FilialNr_    );
    releaseStmt.SetCustomerNo( IDFNr_       );
    releaseStmt.SetDateFrom(   RODateFrom_  );
    releaseStmt.SetDateTo(     RODateTo_    );
    releaseStmt.SetOrderNo(    KdAuftragNr_ );

    retval = vse->SendDataToCics( releaseStmt.ToString(), ResultBuffer, sizeof(ResultBuffer) );
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       SetNoCics();
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  BookOrderValueCstDiscAccVSE                                               */
/*----------------------------------------------------------------------------*/
int
pxOrder :: BookOrderValueCstDiscAccVSE
(
)
{
    int  retval = 0;
    char  ResultBuffer[1024];

    if ( !(OrderType().IsDiscountAccount()) )
       return retval;

    // maybe this is a splitted Rebate order
    if ( CstDiscountAccount() == NULL )
    {
       if ( OrderDiscAccList() )
       {
          if ( OrderDiscAccList()->Entries() == 0  && KdAuftragNrOrg_ == 0 )
          {
             return retval;
          }
       }
    }

    pxTcaSession* vse = Session()->GetTcaSessionEntry(FilialNr_);
    if ( vse == NULL )
       return 1;

    retval = vse->ConnectToCics();
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       SetNoCics();
       return retval;
    }

    DKRAKBookOrderValueStmt bookOrderValueStmt;
    bookOrderValueStmt.SetBranchNo( FilialNr_ );
    bookOrderValueStmt.SetCustomerNo( IDFNr_ );
    bookOrderValueStmt.SetDateFrom( RODateFrom_ );
    bookOrderValueStmt.SetDateTo( RODateTo_ );
    bookOrderValueStmt.SetRabateChainEnabled( ROChain_ == 1 );

    if ( OrderValues() )
    {
        if ( OrderValues()->OrdValNetFS() > pxConstants::mZero )
        {
             bookOrderValueStmt.SetOrderValueNet( OrderValues()->OrdValNetFS() );
        }
        else if ( OrderValues()->OrdValNetHF()   > pxConstants::mZero )
        {
             bookOrderValueStmt.SetOrderValueNet( OrderValues()->OrdValNetHF() );
        }
        else if ( OrderValues()->OrdValNetRS()  > pxConstants::mZero )
        {
             bookOrderValueStmt.SetOrderValueNet( OrderValues()->OrdValNetRS() );
        }

        if ( OrderValues()->OrdValGrossFS() > pxConstants::mZero )
        {
            bookOrderValueStmt.SetOrderValueGross( OrderValues()->OrdValGrossFS() );
        }
        else if ( OrderValues()->OrdValGrossHF()  > pxConstants::mZero )
        {
            bookOrderValueStmt.SetOrderValueGross( OrderValues()->OrdValGrossHF() );
        }
        else if ( OrderValues()->OrdValGrossRS()  > pxConstants::mZero )
        {
            bookOrderValueStmt.SetOrderValueGross( OrderValues()->OrdValGrossRS() );
        }
    }

    // KdAuftragNr
    if ( KdAuftragNrOrg_ > 0 && KdAuftragNrOrgRO_ > 0)
    {
        bookOrderValueStmt.SetOrderNo( KdAuftragNrOrgRO_ );
        bookOrderValueStmt.SetSplittOrderNo( KdAuftragNr_ );
    }
    else
    {
        bookOrderValueStmt.SetOrderNo( KdAuftragNr_ );
        bookOrderValueStmt.SetSplittOrderNo( KdAuftragNr_ );
    }

    retval = vse->SendDataToCics( bookOrderValueStmt.ToString(), ResultBuffer, sizeof(ResultBuffer) );
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       SetNoCics();
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  ReleaseChangeCstDiscAccVSE                                                */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ReleaseChangeCstDiscAccVSE
(
)
{
    int  retval = 0;
    char  ResultBuffer[1024];

    if ( CstDiscountAccount() == NULL )
    {
       return retval;
    }

    pxTcaSession* vse = Session()->GetTcaSessionEntry(FilialNr_);
    if ( vse == NULL )
       return 1;

    retval = vse->ConnectToCics();
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       SetNoCics();
       return retval;
    }

    // call VSE
    DKRAKReleaseChangeStmt releaseChangeStmt;
    releaseChangeStmt.SetBranchNo(   FilialNr_ );
    releaseChangeStmt.SetCustomerNo( IDFNr_ );
    releaseChangeStmt.SetOrderNo(    KdAuftragNr_ );
    releaseChangeStmt.SetDateFrom(   RODateFrom_ );
    releaseChangeStmt.SetDateTo(     RODateTo_ );
    releaseChangeStmt.SetRabateChainEnabled( ROChain_ == 1 );

    retval = vse->SendDataToCics( releaseChangeStmt.ToString(), ResultBuffer, sizeof(ResultBuffer) );
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       SetNoCics();
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  CancelDelayedDeliveryOrderVSE Cancel delayed delivery RO order            */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CancelDelayedDeliveryOrderVSE
(
)
{
    int  retval = 0;
    char  ResultBuffer[1024];

    if ( DatumAuslieferung() == nDate(0L) )
       return ErrorState();

    pxTcaSession* vse = Session()->GetTcaSessionEntry(FilialNr_);
    if ( vse == NULL )
       return 1;

    retval = vse->ConnectToCics();
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       SetNoCics();
       return retval;
    }

    // call VSE
    DKRAKCancelDelelayedDeliveryOrderStmt cancelDeliveryOrderStmt;
    cancelDeliveryOrderStmt.SetBranchNo( FilialNr_ );
    cancelDeliveryOrderStmt.SetCustomerNo( IDFNr_ );
    cancelDeliveryOrderStmt.SetOrderNo( KdAuftragNr_ );
    cancelDeliveryOrderStmt.SetDateFrom( RODateFrom_ );
    cancelDeliveryOrderStmt.SetDateTo( RODateTo_ );
    cancelDeliveryOrderStmt.SetRabateChainEnabled( ROChain_ == 1 );

    retval = vse->SendDataToCics( cancelDeliveryOrderStmt.ToString(), ResultBuffer, sizeof(ResultBuffer) );
    if ( retval == 0 )
    {
       ExternalError(CMsgStream(), CMSG_TCACCESS_ERROR);
       SetNoCics();
    }
    return retval;
}
