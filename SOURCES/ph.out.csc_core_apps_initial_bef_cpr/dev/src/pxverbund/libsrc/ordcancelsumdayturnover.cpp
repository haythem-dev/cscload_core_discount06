#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxdebitlimit.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  CancelDebtLimitSumDayTurnOver: This Methode is called during              */
/*  pxOrder::Cancel() and works at the moment only for the Crema              */
/*  implementation. It decreases the sumdayturnover value wihin Customers     */
/*  debtlimit by pxOrder::WertLieferung_                                      */
/*----------------------------------------------------------------------------*/
int
pxOrder::CancelDebtLimitSumDayTurnOver
(
)
{
    long partnerno = Customer()->PartnerNr();
    pxDebitLimit* lm = NULL;
    nMoney  OrderValue;

    if (!(Param()->IsSCrema()))                // just for branches using Crema implementaion
    {
        return ErrorState();
    }
    if (Param()->IsSStopCrema())               // just for branches using Crema implementaion
    {
        return ErrorState();
    }

    if (KdAuftragNrOrg_ > 0)                   // gesplitteter Auftrag , Crema released 12.09.2018
    {
        return ErrorState();
    }

    if (partnerno == 0)                         //just if there is a partnernumber
    {
        return ErrorState();
    }

    if (Session()->isBulgaria())
    {
        // Increases K1 and K2 dayturnover
        OrderValue = CalcGrossShipValue();
        UndoCreditDayTurnOver();
    }
    else
    {
        OrderValue = WertLieferung_;
        lm = new pxDebitLimit(Session(), partnerno, cDBGET_READONLY);

        if (!lm->IsGoodState())
        {
            return ErrorState();
        }

        if (lm->Limit() == pxConstants::mZero)
        {
            delete lm;
            return ErrorState();
        }

        nDBBeginTransaction(cDBTransRecord);
        lm->DecreaseDayTurnOver(OrderValue);
        lm->Put();
        if (!lm->IsGoodState())
        {
            nDBRollBack();
        }
        else
        {
            nDBCommit(cDBTransRecord);
        }
        delete lm;
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/* Since Orders dont always get closed with a single user deciscion           */
/* revert the value if order doesnt get closed/canceled                       */
/*----------------------------------------------------------------------------*/
int
pxOrder::RevertCancelDebtLimitSumDayTurnOver
(
)
{
    long partnerno = Customer()->PartnerNr();
    pxDebitLimit* lm = NULL;
    nMoney  OrderValue;

    if (!(Param()->IsSCrema()))                // just for branches using Crema implementaion
    {
        return ErrorState();
    }
    if (Param()->IsSStopCrema())               // just for branches using Crema implementaion
    {
        return ErrorState();
    }

    if (partnerno == 0)                         //just if there is a partnernumber
    {
        return ErrorState();
    }



    if (Session()->isBulgaria())
    {
        // Increases K1 and K2 dayturnover
        OrderValue = CalcGrossShipValue();
        RedoCreditDayTurnOver(OrderValue);
    }
    else
    {
        OrderValue = WertLieferung_;
        lm = new pxDebitLimit(Session(), partnerno, cDBGET_READONLY);


        if (!lm->IsGoodState())
        {
            return ErrorState();
        }

        if (lm->Limit() == pxConstants::mZero)
        {
            delete lm;
            return ErrorState();
        }

        nDBBeginTransaction(cDBTransRecord);
        lm->IncreaseDayTurnOver(OrderValue);
        lm->Put();
        if (!lm->IsGoodState())
        {
            nDBRollBack();
        }
        else
        {
            nDBCommit(cDBTransRecord);
        }
        delete lm;
    }

    return ErrorState();
}
