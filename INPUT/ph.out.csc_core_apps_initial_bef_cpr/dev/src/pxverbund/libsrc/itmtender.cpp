/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
the main purpose of this methode is handling Tenderpositiones

REVISION HISTORY

18 Sept 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "pxitemdiscount.hpp"
#include "pxdiscountdef.h"
#include "pxtenderhead.hpp"
#include "pxtenderpos.hpp"
#include "pxtenderprogress.hpp"
#include "pxorderremarks.hpp"
#include "pxbase/pxconstants.hpp"
#include <tender/repository/itenderrepository.h>

/*----------------------------------------------------------------------------*/
/*  UndoTenderProgress: This methode looks under special circumstances for an */
/*  TenderProgress entry for this items ArtikelNr and this items order and    */
/*  orders creation date. If found, it will be deleted.                       */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoTenderProgress
(
)
{
    if( Session()->isSwitzerland() )
    {
        return UndoTenderProgressCH();
    }

    pxTenderProgress*  TPentry;      // TenderProgress entry
    const pxCustOrderType&  ot = Order().OrderType();
    pxDevice  *device = Session()->Device();
    if ( !(device->IsVideo()) )         // only for Video devices
       return ErrorState();

    if ( !(ot.IsTenderOrder()) && !(ot.IsTenderInvoice()) )
       return ErrorState();

    if ( Order().TenderNo() == 0 )      // just check for not needed work
       return ErrorState();

    nDate tmp = (nDate) Order().DateTimeCreated();
    TPentry = new pxTenderProgress(Session(), Order().TenderNo(), ArtikelNr_,
         Order().KdAuftragNr(), tmp, PosNr_);
    if ( TPentry->Get(cDBGET_READONLY))
    {
       Error() = TPentry->Error();
       delete TPentry;
    }
    else
    {
       TPentry->Delete();        // delete from database
       Error() = TPentry->Error();
       delete TPentry;
    }

    return ErrorState();
}

int pxOrderItem::UndoTenderProgressCH()
{
    int tenderno = 0;

    // get tender no from remarks
    pxGenericOrderRemarkList remarklist( Session() );
    remarklist.SelectOrderRemarksByOrderLineAndType( KdAuftragNr(), PosNr(), eTenderNo );
    if( remarklist.Entries() > 0 )
    {
        pxGenericOrderRemarkListIter iter = ::pxGenericOrderRemarkListIter( remarklist );
        pxGenericOrderRemark * remark;

        if( NULL != (remark = (pxGenericOrderRemark*)++iter) )
        {
            basar::VarString strRem = basar::VarString( remark->RemarkText() );
            if ( strRem.isDigit() )
            {
                tenderno = atoi( strRem.c_str() );
            }

            // delete remark
            remarklist.RemoveOrderRemark( KdAuftragNr(), PosNr(), eTenderNo, strRem );
        }
    }

    if( 0 == tenderno )
    {
        return ErrorState();
    }

    nDate tmp = (nDate) Order().DateTimeCreated();
    pxTenderProgress tp( Session(), tenderno, ArtikelNr(), Order().KdAuftragNr(), tmp, PosNr() );
    if( tp.Get( cDBGET_READONLY ) )
    {
       Error() = tp.Error();
    }
    else
    {
       tp.Delete();        // delete from database
       Error() = tp.Error();
    }

    Session()->getTenderRepository()->switchTenderState( tenderno );
    return ErrorState();
}

int pxOrderItem::UndoRedoTenderProgressCH(pxOrderItem* src)
{
    int tenderno = 0;

    // get tender no from src->remarks
    pxGenericOrderRemarkList remarklist(Session());
    remarklist.SelectOrderRemarksByOrderLineAndType(src->KdAuftragNr(), src->PosNr(), eTenderNo);
    if (remarklist.Entries() > 0)
    {
        pxGenericOrderRemarkListIter iter = ::pxGenericOrderRemarkListIter(remarklist);
        pxGenericOrderRemark * remark;

        if (NULL != (remark = (pxGenericOrderRemark*)++iter))
        {
            basar::VarString strRem = basar::VarString(remark->RemarkText());
            if (strRem.isDigit())
            {
                tenderno = atoi(strRem.c_str());
            }
            if (tenderno > 0)
            {
                //copy remark
                getGenericOrderRemarks()->AddOrderRemark(KdAuftragNr(), PosNr(), remark->RemarkType(), remark->RemarkText());
            }
            // delete remark
            remarklist.RemoveOrderRemark(src->KdAuftragNr(), src->PosNr(), eTenderNo, strRem);
        }
    }

    if (0 == tenderno)
    {
        return ErrorState();
    }

    nDate tmp = (nDate)Order().DateTimeCreated();
    pxTenderProgress* newtp = NULL;
    pxTenderProgress tp(Session(), tenderno, ArtikelNr(),src->KdAuftragNr(), tmp, src->PosNr());
    if (tp.Get(cDBGET_READONLY))
    {
        Error() = tp.Error();
    }
    else
    {
        newtp = new pxTenderProgress(Session(), tenderno, ArtikelNr(), KdAuftragNr(), tmp, PosNr());
        newtp->SetDeliveryQty(tp.DeliveryQty());
        newtp->SetChargedPrice(tp.ChargedPrice());
        newtp->SetChargedPrice(tp.ChargedPrice());
        newtp->SetReturnQty(tp.ReturnQty());
        newtp->SetOrderTime(tp.OrderTime());
        newtp->SetCustomerNo(tp.CustomerNo());
        newtp->SetAEP(tp.AEP());
        newtp->SetBookingTenderNo(tp.BookingTenderNo());
        newtp->SetInvoiceNo(tp.InvoiceNo());
        newtp->SetInvoiceDate(tp.InvoiceDate());
        newtp->SetKdAuftragArt(tp.KdAuftragArt());
        newtp->SetGEP(tp.GEP());
        newtp->SetInvoiceTime(tp.InvoiceTime());
        newtp->SetBranchNo(tp.BranchNo());
        newtp->SetDiscountPct(tp.DiscountPct());
        newtp->SetChangeDate(basar::cmnutil::Date::getCurrent().getDate());
        newtp->Put();
        if (newtp->IsGoodState())
        {
            tp.Delete();        // delete from database
            Error() = tp.Error();
        }

    }

    //Session()->getTenderRepository()->switchTenderState(tenderno);
    return ErrorState();
}

int pxOrderItem::GetTenderNoFromRemark()
{
    int tenderno = 0;
    pxGenericOrderRemarkList remarklist( Session() );
    remarklist.SelectOrderRemarksByOrderLineAndType( KdAuftragNr(), PosNr(), eTenderNo );
    if( remarklist.Entries() > 0 )
    {
        pxGenericOrderRemarkListIter iter = ::pxGenericOrderRemarkListIter( remarklist );
        pxGenericOrderRemark * remark;

        if( NULL != (remark = (pxGenericOrderRemark*)++iter) )
        {
            basar::VarString strRem = basar::VarString( remark->RemarkText() );
            if ( strRem.isDigit() )
            {
                tenderno = atoi( strRem.c_str() );
            }
        }
    }

    return tenderno;
}

long pxOrderItem::GetBookedTenderQty( const int tenderNo )
{
    nDate tmp = (nDate) Order().DateTimeCreated();
    pxTenderProgress tp( Session(), tenderNo, ArtikelNr(), Order().KdAuftragNr(), tmp, PosNr() );
    if( 0 == tp.Get( cDBGET_READONLY ) )
    {
        return tp.DeliveryQty();
    }

    return 0;
}

/*----------------------------------------------------------------------------*/
/*  GetTenderContractPrice: This methode looks for a Tenderpos entry and if   */
/*  available, it returns the contractprice of the TenderPos, otherwise       */
/*  pxConstants::mZero will be returned                                       */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: GetTenderContractPrice
(
)
{
    nMoney  price(0.0);
    if ( TenderPos() )
    {
        price = TenderPos()->ContractPrice();
    }
    return price;
}
/*----------------------------------------------------------------------------*/
/*  GetTenderAddDiscountPct: This methode looks for a Tenderpos entry and if  */
/*  available, it returns the AddDiscountPct of the TenderPos, otherwise      */
/*  pxConstants::dZero will be returned                                       */
/*----------------------------------------------------------------------------*/
double
pxOrderItem :: GetTenderAddDiscountPct
(
)
{
    double AddDiscountPct(0.0);
    if ( TenderPos() )
    {
        AddDiscountPct = TenderPos()->AddDiscountPct();
    }
    return AddDiscountPct;
}

/*----------------------------------------------------------------------------*/
bool
pxOrderItem :: CalcTenderDiscount
(
)
{
    const pxCustOrderType& ot = Order().OrderType();
    if (!(ot.IsTenderOrder()) && !(ot.IsTenderInvoice()))
        return false;

    if (Order().TenderNo() == 0)
        return false;

    if (!Session()->isFrancePrewhole()) // TODO What about BG/RS
        return false;

    if (GetTenderAddDiscountPct() > 0.0)
    {
        pxItemDiscount* discount = new pxItemDiscount(Session(), KdAuftragNr_,
            PosNr_, (short)BestBuy_ValuePctCash, nString("000"));
        discount->SetDiscountValuePct(GetTenderAddDiscountPct());
        discount->Put();
        if (discount->IsGoodState())
        {
            ItemDiscountList()->Append(discount);
        }
    }
    return true;
}

/*----------------------------------------------------------------------------*/
/*  TenderChargedPrice: This methode calculates the charged price for a       */
/*  Tender Position. Dependentcies: TenderPos Contractprice = PreisEkApo,     */
/*  TenderPos AddDiscountPct and maybe an additional Rebate from ZDP.         */
/*  Formel: chargedprice = contractprice - (adddiscountpct + ZDP Rebate)      */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: TenderChargedPrice
(
)
{
    nMoney  ChargedPrice(0.0);
    double AddDiscountPct(0.0);
    double Reb(0.0);
    if ( TenderPos() )
    {
       ChargedPrice    = TenderPos()->ContractPrice();
       AddDiscountPct  = TenderPos()->AddDiscountPct();
       Reb             = GetDiscountValuePct();
       AddDiscountPct += Reb;
       ChargedPrice    = ChargedPrice/(1+(AddDiscountPct/100));
    }
    if ( ChargedPrice == pxConstants::mZero )
       ChargedPrice = PreisEKApo_;

    return ChargedPrice;
}
/*----------------------------------------------------------------------------*/
/*  CloseTenderPos: This methode just works in RS and BG and only on          */
/*  ortype TO = TenderOrder.                                                  */
/*  It calculates the sum of delivery within table tenderprogress depend on   */
/*  TenderNo (order) and articleno(this). If the sum equals the contractqty   */
/*  of the tenderpos + ExceedancePct (tenderhead), so the state of            */
/*  of the tenderpos changes to close (= '9')                                 */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CloseTenderPos
(
)
{
    long   ContractQty = 0;
    double ExceedancePct(0.0);
    double faktor;
    double maxqty;
    long   TotalQty;

    pxTenderProgressList* tpgl = NULL;
    if ( TenderPos() == NULL )
       return ErrorState();
    if ( Order().TenderHead() == NULL )
       return ErrorState();

    ContractQty    = TenderPos()->ContractQty();
    ExceedancePct  = Order().TenderHead()->ExceedancePct();

    if (ExceedancePct != pxConstants::dZero)
    {
       faktor = (ExceedancePct + 100)/100;
       maxqty = ContractQty * faktor;
       maxqty = maxqty+0.99;
       TotalQty = (long)maxqty;
    }
    else
    {
       TotalQty = ContractQty;
    }

    tpgl = new pxTenderProgressList(Session());
    tpgl->Select(Order().TenderNo(), ArtikelNr_);
    if (tpgl->Entries() > 0 )
    {
       if ( (tpgl->SumDeliveryQty() - tpgl->SumReturnQty() )  >= TotalQty )
       {
          nDBBeginTransaction(cDBTransRecord);
          TenderPos()->SetAutoBlock();
          TenderPos()->Put();
          Error() = TenderPos()->Error();
          if ( IsGoodState() )
          {
             nDBCommit(cDBTransRecord);          // commit changes
          }
          else
          {
             nDBRollBack();                      // roll them back in case of any error
          }
          ClearError();                          // for safety continue
       }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  getFreeTenderQty:This methode just works in RS and BG and only on         */
/*  ordertype TenderOrder(TI,TO).                                             */
/*  It calculates the freetenderqty depend on entries within tenderprogress.  */
/*  Select is done with tenderno and articleno.                               */
/*  From the list we get SumDeliveryQty and SumReturnQty, so we are able to   */
/*  calculate the free tender quantity                                        */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: getFreeTenderQty
(
)
{
    long   ContractQty = 0;
    long   sumDeliveryQty = 0;
    long   sumReturnQty   = 0;
    long   freeTenderQty  = 0;

    pxTenderProgressList* tpgl = NULL;
    if ( TenderPos() == NULL )
       return freeTenderQty;
    if ( Order().TenderHead() == NULL )
       return freeTenderQty;

    ContractQty    = TenderPos()->ContractQty();
    tpgl = new pxTenderProgressList(Session());
    tpgl->Select(Order().TenderNo(), ArtikelNr_);
    if (tpgl->Entries() > 0 )
    {
       sumDeliveryQty  =  tpgl->SumDeliveryQty();
       sumReturnQty    =  tpgl->SumReturnQty();
    }

    freeTenderQty = (ContractQty - sumDeliveryQty ) +  sumReturnQty;

    return freeTenderQty;
}
