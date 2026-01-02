#include "pxcstbas.hpp"
#include "pxsess.hpp"
#include "pxcsterm.hpp"
#include "pxcstbtm.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstot.hpp"
#include "pxbranch.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxcstseporderartgrp.hpp"
#include "pxcstpaymentterms.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxcustrouteconstime.hpp"
#include "pxcustpharmgroup.hpp"
#include "pxcstprint.hpp"
#include "pxcustrouting.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxdebitlimit.hpp"
#include "pxdonepromoquotas.hpp"
#include "pxencloserscale.hpp"
#include "pxrangemember.hpp"
#include "pxrouteconstime.hpp"
#include "pxcstrou.hpp"
#include "pxcustrouteweek.hpp"
#include "pxholiday.hpp"
#include "pxoeparm.hpp"
#include "pxrange.hpp"
#include "pxttype.hpp"
#include "pxbase/pxconstants.hpp"
#include <logger/loggerpool.h>

extern int pxGlobalLanguageId;

/*----------------------------------------------------------------------------*/
/*  Language Tranlate table                                                   */
/*----------------------------------------------------------------------------*/
struct LANGUAGETabEntry
{
    char  LANGString[5];              // ordertype
    char  LANGNumber;                 // corresponding number
};

static LANGUAGETabEntry LANGUAGETable[] =
{
    {"  ",0},
    {"0000",0},
    {"  DE",0},
    {"  DE",0},
    {"  FR",1},
    {"  HR",2},
    {"CHDE",3},
    {"CHFR",4},
    {"  BG",5}
};

bool pxCustBase::isHospitalMarket() const
{
    return ("06" == KdGruppe());
}

/*----------------------------------------------------------------------------*/
/*  Index a term group entry within the term group list.                      */
/*  Returns the term group number or -1 if the index i is out of bounds.      */
/*----------------------------------------------------------------------------*/
//long
//pxCustBase :: GetTermGroup
//(
//    const int   i                       // term group index
//)
//
//{
//    pxCustTermGroup *tgp = (pxCustTermGroup*)TermGroupList()->At(i);  // ptr to term group entry
//    return tgp ? tgp->KondGruppenNr() : -1;
//}

/*----------------------------------------------------------------------------*/
/*  Find a term group entry within the term group list.                       */
/*  Returns the term group pointer or NULL if the entry is not found          */
/*----------------------------------------------------------------------------*/
//pxCustTermGroup*
//pxCustBase :: FindTermGroup
//(
//    const long   GroupNr              // term group number
//)
//
//{
//    //pxCustTermGroup   *tgp;             // ptr to term group entry
//    return  ( /*tgp =*/ TermGroupList()->Find(GroupNr) );
//}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the customer's term group list.                       */
/*  If the list is not already constructed, construction is performed and     */
/*  the term groups related to the customer are selected from the data base.  */
/*----------------------------------------------------------------------------*/
//pxCustTermGroupList*
//pxCustBase :: TermGroupList
//(
//)
//
//{
//    if (! TermGroupList_ )              // then list is not constructed
//    {
//       TermGroupList_ = new pxCustTermGroupList(Session());
//       TermGroupList_->Select(IDFNr_,VertriebszentrumNr_);  // read term groups from the data base
//
//    }
//    return TermGroupList_;
//}

/*----------------------------------------------------------------------------*/
/*  Return a reference to the customer flags.                                 */
/*----------------------------------------------------------------------------*/
pxCustomerFlags&
pxCustBase::Flags()
{
    if (!flags_)                        // then flags not there,
                                        // invoke read constructor
        flags_ = new pxCustomerFlags(Session(), VertriebszentrumNr_, KundenNr_);
    return *flags_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the CustomerGroupFlagList                             */
/*----------------------------------------------------------------------------*/
pxCustomerGrpFlagsList*
pxCustBase::CustomerGroupFlagsList()
{
    if (!CustomerGroupFlagsList_)        // then list not there
    {
        CustomerGroupFlagsList_ = new pxCustomerGrpFlagsList(Session());
        CustomerGroupFlagsList_->Select(VertriebszentrumNr_, (short)atoi(KdGruppe_));
    }
    return CustomerGroupFlagsList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to customer's terms.                                     */
/*----------------------------------------------------------------------------*/
pxCustTerms&
pxCustBase::Terms()
{
    if (!terms_)                        // not there, invole read constructor
        terms_ = new pxCustTerms(Session(), VertriebszentrumNr_, KundenNr_);
    return *terms_;
}

/*----------------------------------------------------------------------------*/
/*  Test if customer allows order quantity raising to meet terms and          */
/*  conditions                                                                */
/*----------------------------------------------------------------------------*/
bool
pxCustBase::IsQuantityRaising()
{
    return Flags().IsAutoErhoehgNNNR();
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the order type list. The list contains order types    */
/*  allowed for the customer.                                                 */
/*----------------------------------------------------------------------------*/
pxCustOrderTypeList*
pxCustBase::OrderTypeList()
{
    if (!OrderTypeList_)
    {
        OrderTypeList_ = new pxCustOrderTypeList(Session());
        OrderTypeList_->Build(VertriebszentrumNr_, KundenNr_);
    }
    return OrderTypeList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the customer's business time list.                    */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimesList*
pxCustBase::BusyList()
{
    if (!BusyList_)
    {
        BusyList_ = new pxCustBusinessTimesList(Session());
        BusyList_->Select(VertriebszentrumNr_, KundenNr_);
    }
    return BusyList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a reference to this day's business time object instance.           */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes&
pxCustBase::BusyTime()
{
    if (BusyTime_ == NULL)
    {
        pxCustBusinessTimesList* blist = BusyList();
        BusyTime_ = blist->ThisDay();
        if (BusyTime_ == NULL)
        {
            BusyTime_ = new pxCustBusinessTimes(Session(), VertriebszentrumNr_, KundenNr_);
            blist->Append(BusyTime_);
        }
    }
    return *BusyTime_;
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxTimeTypeList pointer or NULL.                   */
/*  The list contains the timewindows for the Alternate Delivery Service      */
/*----------------------------------------------------------------------------*/
pxTimeTypeList*
pxCustBase::CustTimeList
(
)
{

    if (!CustTimeList_)
    {
        nString  key;
        key = IDFNr_;
        // key.Trim(7,nString::cLEADING,'0');
        CustTimeList_ = new pxTimeTypeList(Session());
        CustTimeList_->Select(Type_ADS_Customer, key, Session()->Branch()->FilialNr());
    }

    if (CustTimeList_->Entries())      // if entries found
        return CustTimeList_;
    delete     CustTimeList_;
    return (CustTimeList_ = NULL);
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxCustPharmGroupList pointer or NULL.             */
/*  The list contains the PharmGroups for this Customer                       */
/*----------------------------------------------------------------------------*/
pxCustPharmGroupList*
pxCustBase::PharmGroupList
(
)
{

    if (!PharmGroupList_)
    {
        PharmGroupList_ = new pxCustPharmGroupList(Session());
        PharmGroupList_->Select(KundenNr_, VertriebszentrumNr_);
    }

    if (PharmGroupList_->Entries())      // if entries found
        return PharmGroupList_;

    delete     PharmGroupList_;
    return (PharmGroupList_ = NULL);
}

/*----------------------------------------------------------------------------*/
/*  GetDeferredOrder: returns the KdAuftragnr from a deferred Order or  0.    */
/*  from type NO00 or a NULLP                                                 */
/*  Take care for a well constructed pxCustBase object.This Methode is just in*/
/*  affect on NonVideo Terminals and on Customers flagged with                */
/*  AuftragZusammen == 1 and SepAuft == 0                                     */
/*----------------------------------------------------------------------------*/
long
pxCustBase::GetDeferredOrderNr
(
)
{
    long         retval = 0;
    pxOrder* order = NULL;
    pxCustomerFlags& cflags = Flags();
    pxOrderList* olist = NULL;
    pxDevice* device = Session()->Device();

    if (device->IsVideo())         // is not dct
        return retval;

    const pxOrderEntryParamPtr para = Session()->getOrderEntryParam(VertriebszentrumNr_);
    if (!para->IsGoodState())
        return retval;

    // "Auftragzusammenfuehrung"
    if (para->SAuftragZusammen() == '0')
        return retval;


    if (cflags.IsAuftragZusammen() && !cflags.IsSepAuft())
    {
        olist = new pxOrderList(Session());
        pxOrderListIter iter(*olist);      // define an iterator for it
        olist->SelectByCustomerNo(IDFNr_, "", "", VertriebszentrumNr_,
            Order::NOT_EntryInProgress,
            Order::NOT_UpdateInProgress,
            Order::EntryDeferred,
            Order::cStateLast);

        while ((order = (pxOrder*) ++iter) != NULL)
        {
            if (para->MaxPosAuftrag() > 0)
            {
                if (order->AnzPos() >= para->MaxPosAuftrag())
                {
                    delete (pxOrder*)iter.Remove();
                    continue;
                }
            }
            if (order->KdAuftragArt() == "NO" &&
                order->KoArt() == '0' &&
                order->BuchArt() == '0' &&
                order->DatumAuslieferung() == pxConstants::NullDate &&
                order->BatchSchreiben() == cORTYPE_UNKNOWN)
            {
                retval = order->KdAuftragNr();
                break;
            }
        }
    }
    if (olist)
        delete olist;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Return a reference to the customers DelayedDelivery entry.                */
/*----------------------------------------------------------------------------*/
pxCustDelDelivery* pxCustBase::getDelayedDelivery(const  nDate& Date, const bool withTransportExclusion)
{
    short dow = Date.GetDayOfWeek();
    pxCustDelDeliveryList cstDelDeliveryList(Session());

    if (DelayedDelivery_)               // then entry is there
    {
        if (dow != DelayedDelivery_->WeekDay())
        {
            delete DelayedDelivery_;
            DelayedDelivery_ = NULL;
            DelayedDeliveryRead_ = false;
        }
    }
    if (NULL == DelayedDelivery_ && false == DelayedDeliveryRead_)              // then entry not there,
    {
        cstDelDeliveryList.Select(VertriebszentrumNr_, KundenNr_, Date.GetDayOfWeek(), withTransportExclusion);
        if (cstDelDeliveryList.Entries() > 0)
        {
            DelayedDelivery_ = new  pxCustDelDelivery(*((pxCustDelDelivery*)(cstDelDeliveryList.At(0))));
        }
        DelayedDeliveryRead_ = true;
    }
    return DelayedDelivery_;
}

/*----------------------------------------------------------------------------*/
/*  Test if customers delayed delivery is activ now                           */
/*  conditions                                                                */
/*----------------------------------------------------------------------------*/
bool  pxCustBase::IsDelayedDelivery(nString& TourId, bool withTransportExclusion)
{
    long   ctoursecs = 0;
    if (IsNoSeparate())
        return false;
    nDate now;
    nClock time;
    long   tour = atol((char*)(nString)(TourId(0, 4)));
    nClock ctour(tour * 100);
    if (ctour.IsValid())
    {
        ctoursecs = ctour.GetDaySeconds();
    }
    if (!DelayedDelivery_)         // no read for delayeddeliverycst
    {
        getDelayedDelivery(now, withTransportExclusion);         // do it, take this day as base info
    }
    if (DelayedDelivery_)          // and check TourId
    {
        if (!(DelayedDelivery_->IsActiv()))
        {
            return false;
        }

        if (ctoursecs == 0)         // non valid tour
        {
            // aufgemerkt, für Touren > 24 Uhr(zum Beispiel 3045) muss generell verzögert werden
            if (tour > 2400)
            {
                return true;
            }
            ctoursecs = time.GetDaySeconds();
        }
        long dtoursecs = DelayedDelivery_->Time().GetDaySeconds();
        if (ctoursecs > dtoursecs)
            return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
/* This function translates the language string into an integer               */
/*----------------------------------------------------------------------------*/
int
pxCustBase::ConvertLanguage
(
    const nString& Language
)
{

    int LangCode = 0;
    nString   cLang = "  ";

    //if ( VertriebszentrumNr_ ==  12 || VertriebszentrumNr_ == 13 || VertriebszentrumNr_ == 16 )
    if (Session()->isSwitzerland())
    {
        cLang = "CH";
    }
    cLang += Language;
    int x = sizeof(LANGUAGETable) / sizeof(LANGUAGETabEntry);  // index calculation
    for (int i = 0; i < x; i++)
    {
        //if ( cLang == nString(LANGUAGETable[i].LANGString ))
        if (strncmp(cLang(), LANGUAGETable[i].LANGString, 4) == 0)
        {
            LangCode = LANGUAGETable[i].LANGNumber;         // match
            break;
        }
    }
    return LangCode;
}

/*----------------------------------------------------------------------------*/
/* ConsolidationTime                                                          */
/* Return Values = -1  = there are no entries on TourPlanConstime and         */
/*                       TourPlanConstime                                     */
/*                  0  = there are entries, but currentime does not match     */
/*                       entries ConsTime                                     */
/*                  1  = there is a match                                     */
/*----------------------------------------------------------------------------*/
int
pxCustBase::ConsolidationTime
(
    nString& TourId,
    const nTime& OrderDayTimeCreation
)
{
    int retval = -1;
    pxCustRouteConsTime* custentry = NULL;     // customer routeconstime entry
    pxRouteConsTime* routeentry = NULL;     // Routconstime entry
    pxCustRouteConsTimeList* custlist = NULL;     // customer routeconstime list
    pxRouteConsTimeList* routelist = NULL;     // routeconstime list
    nDate  today;
    nClock currenttime;
    long cdaysecs = currenttime.GetDaySeconds();
    long daytimecreationsecs = (OrderDayTimeCreation.GetHours() * 3600) + (OrderDayTimeCreation.GetMinutes() * 60 + OrderDayTimeCreation.GetSeconds());
    //char     ProcessState = '0';

/*----------------------------------------------------------------------------*/
/*  First select Customers Consolidationtime entries from database            */
/*  table TourPlanConstime                                                    */
/*----------------------------------------------------------------------------*/
    custlist = new pxCustRouteConsTimeList(Session());
    custlist->Select(VertriebszentrumNr_, KundenNr_, TourId, today);
    pxCustRouteConsTimeListIter  custiter(*custlist);
    if (custlist->Entries())
    {
        while ((custentry = (pxCustRouteConsTime*) ++custiter) != NULL)
        {
            retval = 0;
            if (cdaysecs >= (custentry->ConsTime().GetDaySeconds()) * 60)
            {
                if ((daytimecreationsecs < (custentry->ConsTime().GetDaySeconds()) * 60))
                {
                    retval = 1;
                    break;
                }
            }
        }
    }
    delete custlist;

    /*----------------------------------------------------------------------------*/
    /*  Second:if retval = -1 so there are no entries on Customers                */
    /*  Consolidationtime.                                                        */
    /*  Select Common Tour Consolidatime entries from the Database table          */
    /*  TourConsTime                                                              */
    /*----------------------------------------------------------------------------*/
    if (retval >= 0)
        return retval;
    routelist = new pxRouteConsTimeList(Session());
    routelist->Select(VertriebszentrumNr_, TourId, today);
    pxRouteConsTimeListIter  cursor(*routelist);
    if (routelist->Entries())
    {
        while ((routeentry = (pxRouteConsTime*) ++custiter) != NULL)
        {
            retval = 0;
            if ((daytimecreationsecs < (custentry->ConsTime().GetDaySeconds()) * 60))
            {
                retval = 1;
                break;
            }
        }
    }

    delete routelist;

    return retval;
}

/*----------------------------------------------------------------------------*/
/* IsNoRoutesToday:  This methode checks the Customers RouteList for valid    */
/* routes for today. If just one route is available and this one is not for   */
/* AutoAllocation(KzAutoZuord = 0), so we have no routes today per definition */
/* In that case, this metode returns true, otherwise false                  */
/*----------------------------------------------------------------------------*/
bool
pxCustBase::IsNoRoutesToday
(
)
{
    bool retval = false;
    pxCustRouteList* rl = RouteList();     // select customers routes for today
    pxCustRoute* route;
    nTime time;                      // construct a time object

    // unused variable
    /* long ctourkipp = */ TourenKippZeit();

    long TourenKippZeit = 0;

    if (rl)
    {
        if (!Session()->Device()->IsVideo()) // for a non videodevice
        {
            rl->Shrink(time, &TourenKippZeit); // first shrink list on TourenKippZeit
        }
        if (rl->Entries())
        {
            route = (pxCustRoute*)(rl->At(0));
            if ((route != NULL) && !route->IsAutoAllocation())     // seems the customer has no routes today
            {
                retval = true;
            }
        }
        else
        {
            retval = true;
        }
    }
    else
    {
        retval = true;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/* NextDeliveryDay:  This methode checks the Customers RouteList for valid    */
/* routes for the week. For the first route from now on, the date for         */
/* delivery is returned, otherwise current date is returned.                  */
/*----------------------------------------------------------------------------*/
nDate
pxCustBase::NextDeliveryDay
(
)
{
    nDate  now;
    long  dow = now.GetDayOfWeek();  // get current day
    long  nextday;
    short DelayedDays = 0;           // delayed days
    pxCustRouteWeekList* rwl = NULL;
    pxHoliDayList* holidaylist = Session()->HoliDayList(Vertriebszentrum());
    const pxOrderEntryParamPtr para = Session()->getOrderEntryParam(Vertriebszentrum());
    if (para->IsGoodState())
    {
        DelayedDays = para->DelayedDays();
        if (DelayedDays > 0)
        {
            now = nDate(holidaylist->CalculateNextWorkDay(((now + DelayedDays) - 1), Vertriebszentrum()));
            return now;
        }

    }

    if (IsNoRoutesToday())
    {
        rwl = RouteWeekList();
        if (rwl)
        {
            if (rwl->Entries() > 0)
            {
                nextday = rwl->GetNextDayFromNow();
                now = (dow >= nextday) ? now += (7 - (dow - nextday)) : now += (nextday - dow);
                /*----------------------------------------------------------------------------*/
                /*           Check for an holiday. If now an holiday, so calculate the next   */
                /*           workday                                                          */
                /*----------------------------------------------------------------------------*/
                if (holidaylist->CheckDateForHoliday(now, Vertriebszentrum()))
                {
                    long  deliveryday = holidaylist->CalculateNextWorkDay(
                        now,
                        Vertriebszentrum());
                    now = nDate(deliveryday);
                }
            }
        }
    }
    return  now;
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxCustPharmGroupList pointer or NULL.             */
/*  The list contains the PharmGroups for this Customer                       */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroupList*
pxCustBase::CstSepOrderArtGroupList
(
)
{

    if (!CstSepOrderArtGroupList_)
    {
        CstSepOrderArtGroupList_ = new pxCstSepOrderArtGroupList(Session());
        CstSepOrderArtGroupList_->Select(VertriebszentrumNr_, KundenNr_);
    }

    if (CstSepOrderArtGroupList_->Entries())      // if entries found
        return CstSepOrderArtGroupList_;

    delete     CstSepOrderArtGroupList_;
    return (CstSepOrderArtGroupList_ = NULL);
}

/*----------------------------------------------------------------------------*/
/*  IsHealthFundAuthorized:This function returns True if Krankenkassennr      */
/*  not empty and not "00000", otherwise false                                */
/*----------------------------------------------------------------------------*/
bool
pxCustBase::IsHealthFundAuthorized
(
)
{
    nString KKNr = KrankenKassenNr_;
    KKNr.Strip();
    return (!KKNr.IsEmpty() && KKNr != "000000");
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxDebitLimit pointer or NULL.                     */
/*  pxDebitLimit is customers database entry from table debtlimit depend      */
/*  on customers partnerno Type K2 , affects all article                      */
/*----------------------------------------------------------------------------*/
pxDebitLimit* pxCustBase::DebitLimitK2()
{
    if (DebitLimitK2_ != NULL)
    {
        delete DebitLimitK2_;
        DebitLimitK2_ = NULL;
    }
    // not a customer with credit limit check or no existing credit limit
    if ((PartnerNr_ == 0) || (DebitLimitK2InitCallDone_ && !HasDebitLimitK2()))
    {
        return NULL;
    }

    DebitLimitK2_ = new pxDebitLimit(Session(), PartnerNr_, (short)2, cDBGET_READONLY);
    //DebitLimitK2_ = new pxDebitLimit( Session(), PartnerNr_, (short)0, cDBGET_READONLY);
    if (!DebitLimitK2_->IsGoodState() || (DebitLimitK2_->Limit() == pxConstants::mZero))
    {
        ClearHasDebitLimitK2();
        delete DebitLimitK2_;
        DebitLimitK2_ = NULL;
    }
    DebitLimitK2InitCallDone_ = true;
    return DebitLimitK2_;
}

bool pxCustBase::HasDebitLimitK2()
{
    if (PartnerNr_ == 0)
    {
        return false;
    }
    // HasDebitLimitK2 does only need DebitLimitK2() once as limit is not changing throughout session (is set by nightly batch)
    if (!DebitLimitK2InitCallDone_)
    {
        DebitLimitK2();
    }
    return HasDebitLimitK2_;
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxDebitLimit pointer or NULL.                     */
/*  pxDebitLimit is customers database entry from table debtlimit depend      */
/*  on customers partnerno Type K1 , affects all article. If List5 == 0,      */
/*  then list5 article will not be checked                                    */
/*----------------------------------------------------------------------------*/
pxDebitLimit* pxCustBase::DebitLimitK1()
{
    if (DebitLimitK1_ != NULL)
    {
        delete DebitLimitK1_;
        DebitLimitK1_ = NULL;
    }
    // not a customer with credit limit check or no existing credit limit
    if ((PartnerNr_ == 0) || (DebitLimitK1InitCallDone_ && !HasDebitLimitK1()))
    {
        return NULL;
    }

    if (MainCstNo_ > 0)             // Ketten Mitglied
    {
        //PartnerNr = (FilialNr_ * 10000000)+MainCstNo_;
        // SH, 2013-04-17: debtlimit is maintained only in branch 22 in BG
        DebitLimitK1_ = new pxDebitLimit(Session(), MainCstNo_, (short)1, cDBGET_READONLY);
        if (!DebitLimitK1_->IsGoodState() || (DebitLimitK1_->Limit() == pxConstants::mZero))
        {
            delete DebitLimitK1_;
            DebitLimitK1_ = NULL;
        }
    }

    if (DebitLimitK1_ == NULL)
    {
        DebitLimitK1_ = new pxDebitLimit(Session(), PartnerNr_, (short)1, cDBGET_READONLY);
        if (!DebitLimitK1_->IsGoodState() || (DebitLimitK1_->Limit() == pxConstants::mZero))
        {
            ClearHasDebitLimitK1();
            delete DebitLimitK1_;
            DebitLimitK1_ = NULL;
        }
    }
    DebitLimitK1InitCallDone_ = true;
    return DebitLimitK1_;
}

bool pxCustBase::HasDebitLimitK1()
{
    if (PartnerNr_ == 0)
    {
        return false;
    }
    // HasDebitLimitK1 does only need DebitLimitK1() once as limit is not changing throughout session (is set by nightly batch)
    if (!DebitLimitK1InitCallDone_)
    {
        DebitLimitK1();
    }
    return HasDebitLimitK1_;
}

/*---------------------------------------------------------------------------*/
/*  This function returns a pxCstPaymentTermsList pointer or NULL.           */
/*---------------------------------------------------------------------------*/
pxCstPaymentTermsList*
pxCustBase::CstPaymentTermsList
(
)
{
    if (!CstPaymentTermsList_)
    {
        CstPaymentTermsList_ = new pxCstPaymentTermsList(Session());
        CstPaymentTermsList_->Select(VertriebszentrumNr_, KundenNr_);
        if (CstPaymentTermsList_->Entries() == 0)
        {
            delete CstPaymentTermsList_;
            return CstPaymentTermsList_ = NULL;
        }
    }
    return CstPaymentTermsList_;
}

/*----------------------------------------------------------------------------*/
/*  IsCashPayer : This function returns true or false                         */
/*  This function implements new Cash Payer workflow for BG - CPR-211062      */
/*----------------------------------------------------------------------------*/
bool
pxCustBase::IsCashPayer
(
)
{
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return false;

    pxCstPaymentTermsList* cPayTermsList = CstPaymentTermsList();

    pxDebitLimit* debtlimitK2 = DebitLimitK2(); // customers debtlimit entry pointer
    pxDebitLimit* debtlimitK1 = DebitLimitK1(); // chain debtlimit entry pointer

    if (cPayTermsList == NULL)
    {
        return true;             // cash payer
    }

    if (debtlimitK2->Limit() == nMoney(1.00) || debtlimitK1->Limit() == nMoney(1.00))    // cash payer
    {
        return true;
    }

    if (cPayTermsList) {
        pxCstPaymentTerms* cPayTerms;
        for (int pricetype = 0; pricetype < LISTFIVE_PRICE; pricetype++) {
            if (pricetype > RETAIL_PRICE) pricetype = LISTFIVE_PRICE;
            cPayTerms = cPayTermsList->Find(static_cast<PriceTypeEnum>(pricetype));
            if (cPayTerms && cPayTerms->PaymentTarget() != 0) {
                return false;
            }
        }
        return true;
    }

    return false;
}

/*----------------------------------------------------------------------------*/
/*  IsCashPayer : This function returns true or false depend on PriceType     */
/*----------------------------------------------------------------------------*/
bool
pxCustBase::IsCashPayer
(
    PriceTypeEnum  pricetype,
    pxOrder* order
)
{
    pxCstPaymentTerms* cPayTerms = NULL;

    if (!Session()->isBulgaria())   // just for bulgarien appl
        return false;

    // Wenn DatumValuta > 0
    //  -> kein CashPayer!
    // Wenn DatumValuta == 0
    //  -> Suchen nach PaymentTerm für PriceType (Freiverkauf/Krankenkasse)
    //      -> Kein Eintrag da:
    //          -> CashPayer
    //      -> Eintrag gefunden
    //          -> PaymentTarget == 0
    //              -> CashPayer

    bool retval = false;

    if (order->DatumValuta() != pxConstants::NullDate)
    {
        retval = false; // Wenn DatumValuta > 0 => Kein CashPayer
    }
    else
    {
        pxCstPaymentTermsList* cPayTermsList = CstPaymentTermsList();
        if (NULL == cPayTermsList)
        {
            retval = true; // Wenn keine Zahlungsbedingungen und DatumValuta = 0 => CashPayer
        }
        else
        {
            cPayTerms = cPayTermsList->Find(pricetype);
            if (cPayTerms)
            {
                if (0 == cPayTerms->PaymentTarget())
                {
                    retval = true; // Wenn Zahlungsbedingungen für PriceType vorhanden und Zahlungsziel = 0 => CashPayer
                }
                else
                {
                    retval = false; // Wenn Zahlungsziel für PriceType > 0 => Kein CashPayer
                }
            }
            else
            {
                retval = true;  // Wenn keine Zahlungsbedingungen für PriceType =>  CashPayer
            }
        }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  IsCashPayer : This function returns true or false depend on PriceType     */
/*----------------------------------------------------------------------------*/
bool
pxCustBase::IsCreditLimitRelevant
(
    PriceTypeEnum pricetype
)
{
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return false;

    pxCstPaymentTermsList* cPayTermsList = CstPaymentTermsList();
    if (cPayTermsList == NULL)
    {
        return false;
    }

    if (cPayTermsList)
    {
        pxCstPaymentTerms* cPayTerms = cPayTermsList->Find(pricetype);
        if ((cPayTerms != NULL) && (cPayTerms->PaymentTarget() != 0))     // cash payer
        {
            return true;
        }
    }

    return false;
}

/*----------------------------------------------------------------------------*/
/*  RestCreditLimit : This function returns customers rest credit limit       */
/*----------------------------------------------------------------------------*/
nMoney
pxCustBase::RestCreditLimit
(
)
{
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return pxConstants::mZero;

    pxDebitLimit* debtlimit = DebitLimitK1(); // customers debtlimit entry pointer K1
    if ((debtlimit == NULL) || (debtlimit->Limit() == pxConstants::mZero))  // Kein K1
    {
        debtlimit = DebitLimitK2(); // customers debtlimit entry pointer K2
        if ((debtlimit == NULL) || (debtlimit->Limit() == pxConstants::mZero))  // cash payer
        {
            return pxConstants::mZero;
        }
    }

    return debtlimit->RestCreditLimit();
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxRange pointer or NULL.                          */
/*----------------------------------------------------------------------------*/
pxRangeList*
pxCustBase::DiscountGrpListFive
(
)
{
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return DiscountGrpListFive_;

    if (Flags().IsListe5())
    {
        if (!DiscountGrpListFive_)
        {
            DiscountGrpListFive_ = new pxRangeList(Session());
            DiscountGrpListFive_->Select(VertriebszentrumNr_, (short)pxRange::DiscGrpType_ArticleGroup_List5, KundenNr_);
            if (DiscountGrpListFive_->Entries() == 0)
            {
                delete DiscountGrpListFive_;
                DiscountGrpListFive_ = NULL;
            }
        }
    }
    return DiscountGrpListFive_;
}

/*----------------------------------------------------------------------------*/
/*  DiscountGrpMemListFive: this function selects entries from table          */
/*  DiscountGrpMem depend on DiscountGrpNo within DiscountGrpListFive_ entry  */
/*  of this customer. It returns a Listpointer if entries available, otherwise*/
/*  a nil pointer.                                                            */
/*  Please take care for a well contructed pxCustBase object to prevent       */
/*  unpredictable results                                                     */
/*----------------------------------------------------------------------------*/
pxRangeMemberList* pxCustBase::DiscountGrpMemListFive()
{
    pxRange* rlentry = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return DiscountGrpMemListFive_;

    if (DiscountGrpListFive() == NULL)
        return DiscountGrpMemListFive_;

    pxRangeListIter     iter(*DiscountGrpListFive_);
    if (!DiscountGrpMemListFive_)
    {
        while ((rlentry = (pxRange*) ++iter) != NULL) // browse list
        {
            DiscountGrpMemListFive_ = new pxRangeMemberList(Session());
            DiscountGrpMemListFive_->SelectMembers(VertriebszentrumNr_, rlentry->DiscountGrpNo());
            if (DiscountGrpMemListFive_->Entries() == 0)
            {
                delete DiscountGrpMemListFive_;
                DiscountGrpMemListFive_ = NULL;
            }
        }
    }
    return DiscountGrpMemListFive_;
}

/*----------------------------------------------------------------------------*/
/*  CstPrintList: this function selects entries from table                    */
/*  CSTPRINT for this customer. It's a bulgarian special                      */
/*  It returns a Listpointer if entries available, otherwise a nil pointer    */
/*  Please take care for a well contructed pxCustBase object to prevent       */
/*  unpredictable results                                                     */
/*----------------------------------------------------------------------------*/
pxCstPrintList*
pxCustBase::CstPrintList
(
)
{
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return CstPrintList_;

    if (!CstPrintList_)
    {
        CstPrintList_ = new pxCstPrintList(Session());
        CstPrintList_->Select(VertriebszentrumNr_, IDFNr_);
        if (CstPrintList_->Entries() == 0)
        {
            delete CstPrintList_;
            CstPrintList_ = NULL;
        }
        CstPrintInitMembers();
    }
    return CstPrintList_;
}

/*----------------------------------------------------------------------------*/
/*  CstPrintInitMembers: initializes additional members for entry within      */
/*  CstPrintList_(if available) It's a bulgarian special                      */
/*----------------------------------------------------------------------------*/
int
pxCustBase::CstPrintInitMembers
(
)
{
    int retval = 0;
    pxCstPrint* entryp;         // pointer to listentry
    short   InvoiceEmail = 0;

    if (!CstPrintList_)
        return retval;
    if (Flags().IsInvoiceEmail())
        InvoiceEmail = 1;

    pxCstPrintListIter   iter(*CstPrintList_);  // define iterator
    iter.Reset();                           // top of list
    while ((entryp = (pxCstPrint*) ++iter) != NULL) // browse list
    {
        entryp->SetWithColumnNr((short)0);
        entryp->SetInvoiceEmail(InvoiceEmail);
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetPrint: this function returns  the Print value from customers           */
/*  cstprintlist(if available) depent on pricetype. It's a bulgarian special  */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
short
pxCustBase::GetPrint
(
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            retval = entryp->Print();
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetDeductionAep: this function returns  the DeductionAep value from       */
/*  customers cstprintlist(if available) depent on pricetype.                 */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
short
pxCustBase::GetDeductionAep
(
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            retval = entryp->DeductionAep();
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetDeductionAvp: this function returns  the DeductionAvp value from       */
/*  customers cstprintlist(if available) depent on pricetype.                 */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
short
pxCustBase::GetDeductionAvp
(
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            retval = entryp->DeductionAvp();
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetWithColumnNr: this function returns  the WithColumnNr value from       */
/*  customers cstprintlist(if available) depent on pricetype.                 */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
short
pxCustBase::GetWithColumnNr
(
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            retval = entryp->WithColumnNr();
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetInvoiceEmail: this function returns  the InvoiceEmail value from       */
/*  customers cstprintlist(if available) depent on pricetype.                 */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
short
pxCustBase::GetInvoiceEmail
(
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            retval = entryp->InvoiceEmail();
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  SetPrint: this function sets the print value within the CstPrintList entry*/
/*  depend on pricetyp                                                        */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
int
pxCustBase::SetPrint
(
    const short Print,
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            entryp->SetPrint(Print);
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  SetDeductionAep: this function sets the DeductionAep value within the     */
/*  CstPrintList entry depend on pricetype                                    */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
int
pxCustBase::SetDeductionAep
(
    const short DeductionAep,
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            entryp->SetDeductionAep(DeductionAep);
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  SetDeductionAvp: this function sets the DeductionAvp value within the     */
/*  CstPrintList entry depend on pricetype                                    */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
int
pxCustBase::SetDeductionAvp
(
    const short DeductionAvp,
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            entryp->SetDeductionAvp(DeductionAvp);
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  SetWithColumnNr: this function sets the WithColumnNr value within the     */
/*  CstPrintList entry depend on pricetype                                    */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
int
pxCustBase::SetWithColumnNr
(
    const short WithColumnNr,
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            entryp->SetWithColumnNr(WithColumnNr);
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  SetInvoiceEmail: this function sets the InvoiceEmail value within the     */
/*  CstPrintList entry depend on pricetype                                    */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
int
pxCustBase::SetInvoiceEmail
(
    const short InvoiceEmail,
    const PriceTypeEnum pricetype
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;

    if (CstPrintList())
    {
        entryp = CstPrintList()->Find(pricetype);
        if (entryp)
        {
            entryp->SetInvoiceEmail(InvoiceEmail);
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  CopyCstPrintList: this function copies the given CstPrintList to this     */
/*  Customer object CstPrintList. It deletes an already existing CstPrintList */
/*  It's a bulgarian special                                                  */
/*----------------------------------------------------------------------------*/
int
pxCustBase::CopyCstPrintList
(
    pxCstPrintList* CstPrintList
)
{
    short retval = 0;
    pxCstPrint* entryp = NULL;
    pxCstPrint* newentryp = NULL;
    if (!Session()->isBulgaria())   // just for bulgarien appl
        return retval;
    if (CstPrintList == NULL)
        return retval;

    pxCstPrintListIter   iter(*CstPrintList);  // define iterator
    if (CstPrintList_)
    {
        delete CstPrintList_;
        CstPrintList_ = NULL;
    }

    CstPrintList_ = new pxCstPrintList(Session());
    iter.Reset();                          // top of alterncompanylist
    while ((entryp = (pxCstPrint*) ++iter) != NULL)
    {
        newentryp = new pxCstPrint(*entryp);  // copy artstoreloc entry
        newentryp->SetWithColumnNr(entryp->WithColumnNr());
        newentryp->SetInvoiceEmail(entryp->InvoiceEmail());
        CstPrintList_->Append(newentryp);                // append to this list
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxEncloserScaleList pointer or NULL.              */
/*----------------------------------------------------------------------------*/
pxEncloserScaleList*
pxCustBase::EncloserScaleList
(
)
{
    if (!EncloserScaleList_)
    {
        EncloserScaleList_ = new pxEncloserScaleList(Session());
        EncloserScaleList_->Select(VertriebszentrumNr_, KundenNr_);
        if (EncloserScaleList_->Entries() == 0)
        {
            delete EncloserScaleList_;
            return EncloserScaleList_ = NULL;
        }
    }
    return EncloserScaleList_;
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxDonePromoQuotasList pointer or NULL.            */
/*----------------------------------------------------------------------------*/
pxDonePromoQuotasList*
pxCustBase::DonePromoQuotaList
(
)
{
    if (!Session()->isBulgaria())   // just for BG appl
        return DonePromoQuotaList_;

    if (!DonePromoQuotaList_)
    {
        DonePromoQuotaList_ = new pxDonePromoQuotasList();
    }
    return DonePromoQuotaList_;
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxCustRoutingList pointer or NULL.                */
/*----------------------------------------------------------------------------*/
pxCustRoutingList*
pxCustBase::CustomerRoutingList
(
)
{
    nDate   today;                      //
    if (!CustomerRoutingList_)
    {
        CustomerRoutingList_ = new pxCustRoutingList(Session());
        CustomerRoutingList_->Select(IDFNr_, VertriebszentrumNr_, today.GetDayOfWeek());
        if (CustomerRoutingList_->Entries() == 0)
        {
            delete CustomerRoutingList_;
            CustomerRoutingList_ = NULL;
        }
    }
    return CustomerRoutingList_;
}

/*----------------------------------------------------------------------------*/
/*  This function returns a pxCustRoutingList pointer or NULL.                */
/*----------------------------------------------------------------------------*/
short
pxCustBase::GetDayNightDestBranchNo
(
)
{
    short retvalvz = 0;
    pxCustRouting* entry = NULL;
    if (CustomerRoutingList())
    {
        pxCustRoutingListIter cursor(*CustomerRoutingList_);
        while ((entry = (pxCustRouting*) ++cursor) != NULL)
        {
            retvalvz = entry->DestBranchNo();
        }
    }
    return retvalvz;
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
bool
pxCustBase::IsRoutedFromOriginalBranchNo
(
)
{
    if (OriginalFilialNr() == 0)
        return false;

    pxCustRoutingList   custRoutingList(Session());
    pxCustRouting* custRoutingEntry;
    custRoutingList.SelectRoutingBackward(IDFNr_, FilialNr_);

    pxCustRoutingListIter cursor(custRoutingList);
    while ((custRoutingEntry = (pxCustRouting*) ++cursor) != NULL)
    {
        if (custRoutingEntry->BranchNo() == this->OriginalFilialNr())
        {
            return true;
        }
    }
    return false;
}

/*----------------------------------------------------------------------------*/
/*  ReloadSessionCustomerBranch: reloads Session_->Branch_ if                 */
/*  Session()->Branch()->FilialNr() != Vertriebszentrum()                     */
/*  This may be necessary after booking order in foreign branch during        */
/*  DayNightMerge                                                             */
/*----------------------------------------------------------------------------*/
int
pxCustBase::ReloadSessionCustomerBranch
(
)
{
    short retval = 0;
    // Must change Filiale?
    if (Session()->Branch()->FilialNr() != Vertriebszentrum())
    {
        pxBranch CustBranch(Session(), Vertriebszentrum());
        if (CustBranch.IsGoodState())
        {
            *(Session()->Branch()) = CustBranch;
        }
    }

    // Set paraauftrager for the store
    Session()->Branch()->Store() = FilialNr();
    Session()->LanguageCode(ConvertLanguage(Sprache()));
    pxGlobalLanguageId = Session()->LanguageCode();
    return retval;
}
