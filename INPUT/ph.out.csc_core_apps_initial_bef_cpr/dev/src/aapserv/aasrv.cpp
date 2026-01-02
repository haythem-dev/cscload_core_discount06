#undef TRANSCLASS

/*****************************************************************************/
/* Includes                                                                  */
/*****************************************************************************/

#include "tourutil.hpp"
#include "bufkon.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include "auftrag.h"
#include "ordervalues.h"
#include "kndsel.h"
#include "texte.h"
#include "pxsess.hpp"
#include "pxorder.hpp"
#include "pxcountrycodes.hpp"
#include "pxxmldefs.h"
#include "lockview.h"
#include <liblockmanager/lockmanager/ilockmanager.h>
#include <pxparameter.hpp>
#include "aasrv.h"
#include "rabattorder.h"
#include <signal.h>
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstbtm.hpp"
#include "pxcustrouteweek.hpp"
#include "artikel.h"
#include "pxartdiscountinfo.hpp"
#include "rebateprice.h"
#include "invoicesettings.h"
#include "customer.h"
#include "artsel.h"
#include "auftraginfo.h"
#include "rangelist.h"
#include "sendmail.h"
#include "emailhandler.h"
#include "pxorderpospromo.hpp"
#include "pxstockbooking.hpp"
#include "taufartk.h"
#include <logger/loggerpool.h>
#include <pxorderremarks.hpp>
#include <pxordervalues.hpp>
#include <pxtxtdoc.hpp>
#include <pxordtaxvalues.hpp>
#include <pxcstdiscacc.hpp>
#include <pxrangecollect.hpp>
#include <pxrangecontrol.hpp>
#include <pxoeparm.hpp>
#include <pxcstrou.hpp>
#include <pxcstot.hpp>
#include <pxcomtyp.hpp>
#include <pxcustomergrpflags.hpp>
#include <pxdevice.hpp>
#include <pxvartikellokal.hpp>
#include <pxvartikellokallist.hpp>
#include "tourinfo.hpp"
#include "tourdelay.h"
#include "tourassignmentutil.hpp"
#include "verbundcheck.h"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"
#include <ibt/componentmanager/ibtcomponentmanager.h>
//#include <ibt/bookingcompletedchecker/ibookingcompletedchecker.h>
#include <subseqdelivery/workupcompletedchecker/iworkupcompletedchecker.h>
#include <stockbooking/componentmanager/stockbookingcomponentmanager.h>
#include <stockbooking/reservationconfig/ireservationconfigrepositoryptr.h>
#include <stockbooking/reservationconfig/ireservationconfigrepository.h>
#include <stockbooking/reservationconfig/ireservationtype.h>
#include <stockbooking/reservationconfig/iordertypereservationconfig.h>
#include <stockbooking/reservationconfig/iordertypereservationconfigpharmacygroupptr.h>
#include <stockbooking/reservationconfig/iordertypereservationconfigpharmacygroup.h>
#include "callbackmaillink.h"
#include "articleomg.h"
#include "cscreservationtypes.h"
#include "ordertypereservationconfig.h"
#include "ordertypereservationconfigcpg.h"
#include <parameter/componentmanager/parametercomponentmanager.h>
#include <parameter/csvorderimport/icsvorderimportrepositoryptr.h>
#include <parameter/csvorderimport/icsvorderimportrepository.h>
#include <parameter/csvorderimport/icscorderimportfields.h>
#include <parameter/csvorderimport/icscorderimportcsvformats.h>
#include <parameter/csvorderimport/icscorderimportcsvcolumnsptr.h>
#include <parameter/csvorderimport/icscorderimportcsvcolumns.h>
#include "cscorderimportcsvformats.h"
#include "cscorderimportcsvcolumns.h"
#include "cscorderimportfields.h"
#include "cscorderimportcsvfile.h"
#include "cscorderimport.h"
#include "auftragsart.h"
#include <cscordertype/componentmanager/cscordertypecomponentmanager.h>
#include <cscordertype/componentmanager/cscordertypecomponentmanagerptr.h>
#include <cscordertype/cscordertypebatchconfig/icscordertypebatchconfig.h>
#include <cscordertype/cscordertypebatchconfig/icscordertypebatchconfigptr.h>
#include <cscordertype/repository/icscordertyperepository.h>
#include <cscordertype/icscordertype.h>
#include <cscordertype/ordertypeflagtype/ordertypeflagtypeenum.h>
#include <cscordertype/icscordertypeptr.h>
#include <deliveryadvicehead.h>
#include <deliveryadviceline.h>
#include <deliveryadvicelinedetails.h>
#include <deliveryadvicelinediscounts.h>
#include <deliveryadvicelineibtlink.h>
#include <deliveryadvicelinereturn.h>
#include <deliveryadviceremark.h>
#include <deliveryadvicevattotals.h>
#include <deliveryadvicedocument.h>
#include <document/componentmanager/documentcomponentmanager.h>
#include <document/componentmanager/documentcomponentmanagerptr.h>
#include <document/deliveryadvice/deliveryadvice.h>
#include <document/deliveryadvice/deliveryadviceptr.h>
#include <document/deliveryadvice/deliveryadvicekey.h>
#include <document/deliveryadvice/deliveryadviceinformationfilter.h>
#include <document/deliveryadvice/deliveryadvicerepository.h>
#include <document/deliveryadvice/deliveryadvicevattotals.h>
#include <document/deliveryadvice/deliveryadvicevattotalsptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadviceline.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelineptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetails.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetailsptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinediscount.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinediscountptr.h>
#include <document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlink.h>
#include <document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlinkptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinereturn.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinereturnptr.h>
#include <document/deliveryadvice/deliveryadviceremarks.h>
#include <document/deliveryadvice/deliveryadviceremarksptr.h>
#include <document/documentarchiveinfo/documentarchiveinforepository.h>
#include <document/documentarchiveinfo/documentarchiveinfo.h>
#include <document/documentarchiveinfo/documentarchiveinfoptr.h>

#include <shipmenttracking/componentmanager/shipmenttrackingcomponentmanager.h>
#include <shipmenttracking/componentmanager/shipmenttrackingcomponentmanagerptr.h>
#include <shipmenttracking/configuration/etadelayevaluation.h>
#include <shipmenttracking/configuration/etadelayevaluationptr.h>
#include <shipmenttracking/configuration/etadelaypresentation.h>
#include <shipmenttracking/configuration/etadelaypresentationptr.h>
#include <shipmenttracking/tourinformation/shipmenttrackingtourinformation.h>
#include <shipmenttracking/tourinformation/shipmenttrackingtourinformationptr.h>
#include <shipmenttracking/shipmenttrackingdatafilter.h>
#include <shipmenttracking/shipmenttrackingrepository.h>

#include <libbasarcmnutil_date.h>

#include <discount/discountcollectionfinder/idiscountcollectionfinderptr.h>
#include <discount/discountcollectionfinder/idiscountcollectionfinder.h>
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepository.h>

using pxVerbund::subsequentDelivery::pxDeliveryPos;

extern "C"
{
    extern short sVzNr;
    extern short sUserVz;
    extern long lUID;
    extern long lKundenNr;
    extern char cKdauftragArt[3];
    extern char cCountry[3];
    #include"allg.h"
    void WriteLogInfo( const char *err_str, int err_num, int fehler_art );
    int AatartSel_Preferred(struct ARTAESEL *d, char *error_msg);
}

/*****************************************************************************/
/* Definitionen                                                              */
/*****************************************************************************/
#define NOT_FOUND        1
#define FILE_NOT_FOUND   1

#define UNUSED(x) (void)(x)

/*****************************************************************************/
/* externe Funktionen                                                        */
/*****************************************************************************/

extern "C"
{
    long Pzn2Artikelnr(long artikelnr);
    long Artikelnr2Pzn(long pzn);
}

/*****************************************************************************/
/* Globale Variablen                                                         */
/*****************************************************************************/
static pxSession *ps = NULL;                           //Pointer auf die Session
static pxOrderItemList   *oItemList;                   //Liste von Positionen
static pxOrderList  *oSelList;                         //Liste der Aufträge Selektion
static pxOrder      *order;                       //Auftrag
static pxOrder      *InfoOrder;                   //Auftrag
static libcsc::document::DeliveryAdvicePtr deliveryadvicehead;

pxSession& getSession()
{
    if (NULL == ps)
    {
        char* envir = getenv("INI_PATH");
        basar::VarString inifile;
        if (NULL != envir)
        {
            inifile = envir;
        }
        else
        {
            inifile = "..";
        }
#ifdef WIN32
        inifile += "\\";
#else
        inifile += "/";
#endif
        inifile += "aasunix.ini";

        ps = new pxSession(inifile);
    }
    return *ps;
}

// Internal declarations
static int handleError(nError* order, char *error_msg);
static int getReturnCodeOnError(nError* error);
static int handleErrorAndCloseItem(pxOrderItem* item, char *error_msg);
static void copyCharToString(char* szDest, char src);
static void handleProblemClearance(struct AUFTRAG* d, pxOrder* o);
static bool handleCloseOrderBG(pxSession* session, struct AUFTRAG* d, pxOrder* o);
static void setOrderValues(struct AUFTRAG* d, pxOrder* o);
static void setOrderValues(struct AUFPOSBUCH* d, pxOrder* o);
static void setAuftragLieferZeilen(struct AUFPOSBUCH* d, pxOrder* o);
static void setValuesOnMsgArtQLack(struct AUFPOSBUCH* d, pxOrder* o);
static void setValuesOnMsgOrdCreditLimitExhausted(struct AUFPOSBUCH* d, pxOrder* o);

/*****************************************************************************/
/** Session                                                                 **/
/*****************************************************************************/

/*****************************************************************************/
/* Oeffnen einer Serversitzung                                               */
/*****************************************************************************/
int AasrvOpensession(struct AUFTRAG *d,char *error_msg)
{
    getSession().Device()->Name(d->GERAETNAME);
    getSession().Device()->Type(pxDVC_VIDEO_WORKSTATION);
    AllgEntfSpaces( d->BEMERKUNGEN ); //Rechnername

    if ( ! (getSession().IsGoodState()) )
    {
        if (getSession().ErrorNumber() == -1)    //Fehler beim Oeffnen der Pipe
        {
            AllgStrCopy(error_msg, TXT_KEINE_ASPIPE_VERB, MAX_ERROR_MSG_AE);
            return -2;
        }
        AllgStrCopy(error_msg, getSession().ErrorMsg(), MAX_ERROR_MSG_AE);
        return -1;
    }
    getSession().PersonnelNo(d->UID);
    getSession().UsersFilialNr(d->VERTRIEBSZENTRUMNR);
    sUserVz = d->VERTRIEBSZENTRUMNR;
    lUID = d->UID;

//    pxSession & session = getSession();
//    ps = &session;
    oSelList  = new pxOrderList(ps);
    ps->Country().copy(d->SUB_ORDER_TYPE,2);
    ps->Country().copy(cCountry,2);
    return 0;
}

/*****************************************************************************/
/* Oeffnen einer Serversitzung als Non-Video                                 */
/*****************************************************************************/
int AasrvOpensessionNonVideo(struct AUFTRAG *d, char *error_msg)
{
    getSession().Device()->Name(d->GERAETNAME);
    getSession().Device()->Type(pxDVC_DCT_SERIAL);

    if ( ! (getSession().IsGoodState()) )
    {
        if (getSession().ErrorNumber() == -1)    //Fehler beim Oeffnen der Pipe
        {
            AllgStrCopy(error_msg, TXT_KEINE_ASPIPE_VERB, MAX_ERROR_MSG_AE);
            return -2;
        }
        AllgStrCopy(error_msg, getSession().ErrorMsg(), MAX_ERROR_MSG_AE);
        return -1;
    }
    getSession().PersonnelNo(d->UID);
    pxSession & session = getSession();
    ps = &session;
    oSelList  = new pxOrderList(ps);
    return 0;
}

/*****************************************************************************/
/* Schliessen einer Serversitzung                                            */
/*****************************************************************************/
int AasrvClosesession(struct AUFTRAG * /*d*/,char *error_msg)
{
    delete oSelList;

    getSession().Close();
    if ( ! (getSession().IsGoodState()) )
    {
        AllgStrCopy(error_msg, getSession().ErrorMsg(), MAX_ERROR_MSG_AE);
        return -1;
    }

    return 0;
}

/*****************************************************************************/
/* Liefert Informationen über eine Session                                   */
/*****************************************************************************/
int AasrvGetsession(struct AUFSESS *d, char *error_msg)
{
    AllgStrCopy(d->GERAETNAME, ps->Device()->Name(), L_AUFSESS_GERAETNAME);
    if ( ! (ps->IsGoodState()) )        //nase macht das so Sinn ???
    {
        return handleError(ps, error_msg);
    }
    return 0;
}

/*****************************************************************************/
/** Auftrag                                                                 **/
/*****************************************************************************/

/* Auftragsinfo */
static void AasrvGetOrderInf(pxOrder *o, struct AUFTRAG *d)
{
    nClock   now;
    nString NStr;

    copyCharToString(d->KZDEFOFLOW, '0');

    now += 30L * 60;    //aktuelle Zeit plus 30 Minuten
    d->KDAUFTRAGNR      = o->KdAuftragNr();
    d->IDFNR       = o->IDFNr();
    d->KUNDENNR    = o->KundenNr();
    d->VERTRIEBSZENTRUMNR = o->Vertriebszentrum();
    lKundenNr    = o->KundenNr();
    sVzNr = o->Vertriebszentrum();
    AllgStrCopy(d->NAMEAPO,o->Customer()->NameApo(), L_AUFTRAG_NAMEAPO);
    AllgStrCopy(d->KZKDKLASSE,o->Customer()->KzKdKlasse(), L_AUFTRAG_KZKDKLASSE);
    AllgStrCopy(d->KZSPRACHE,o->Customer()->Sprache(), L_AUFTRAG_KZSPRACHE);
    if (now <= o->Customer()->BusyTime().EndAM())
        NStr = o->Customer()->BusyTime().EndAM().AsString("%H:%M");
    else
        NStr = o->Customer()->BusyTime().EndPM().AsString("%H:%M");
    AllgStrCopy(d->APOENDZEIT,NStr, L_AUFTRAG_APOENDZEIT);
    AllgStrCopy(d->TOURID,        o->TourId(), L_AUFTRAG_TOURID);
    d->DELIVERYDATE = o->getDeliveryDate();
    AllgStrCopy(d->GERAETNAME,    o->GeraetName(), L_AUFTRAG_GERAETNAME);
    AllgStrCopy(d->KDAUFTRAGART, o->KdAuftragArt(), L_AUFTRAG_KDAUFTRAGART);
    AllgStrCopy(cKdauftragArt, o->KdAuftragArt(), L_AUFTRAG_KDAUFTRAGART);
    AllgStrCopy(d->BEMERKUNGEN,  o->Bemerkungen(), L_AUFTRAG_BEMERKUNGEN);
    copyCharToString(d->DAFUEART, o->IsDCParallel() ? 'P' : ' ');
    copyCharToString(d->KOART, o->KoArt());
    copyCharToString(d->BUCHART, o->BuchArt());
    d->WERTAUFTRAG      = o->WertAuftrag();
    d->WERTLIEFERUNG= o->WertLieferung();
    d->WERTZEILEN  = o->WertZeilen();
    d->ANZPOS           = o->AnzPos();
    d->ANZPOSOB    = o->AnzAlphaText();        //nase von ohne bestand auf alpha, bitte prÆfen
    d->ANZDEFEKTUB    = o->AnzPosOB();
    d->ANZPOSDAFUE = o->AnzPosDafue();
    d->VALUTAMONATE = o->ValMonth();
    d->DATUMVALUTA = o->DatumValuta().GetYYYYMMDD();
    d->BATCHSCHREIBEN = o->BatchSchreiben();
    d->RECHNUNGNR = o->RechnungNr();
    d->SENDESTATUS = static_cast<short>(o->SendeStatus());
    d->KDAUFTRAGNRFILIALE = o->VSEAuftragNr();
    d->TENDERNO = o->TenderNo();
    d->WERTNETTO      = o->WertNetto();
    d->WERTRABATT      = o->WertRabatt();
    d->PAYMENTDATE      = o->PaymentDate().GetYYYYMMDD();
    copyCharToString(d->PAYMENTTYPE, o->PaymentType());
    setOrderValues(d, o);
    if (o->CstDiscountAccount() != NULL)
    {
        d->BALANCE = o->GetCstDiscAccBalance(0);
//      d->BALANCE2 = o->GetCstDiscAccBalance(1);
    }
    if ( o->IsKreditLimitErreicht() ) d->ZUGRUND[ZU_KREDITLIMIT] = '1';
    if ( o->IsDefferedForInternet() ) d->ZUGRUND[ZU_INTERNET] = '1';
    if ( o->IsDefferedForBackRouting() ) d->ZUGRUND[ZU_BACKROUTING] = '1';
    if ( o->IsDDNotClose() ) d->ZUGRUND[ZU_DD_OHNE] = '1';
    if ( o->IsSeparateArtGroup() ) d->ZUGRUND[ZU_BTM] = '1';
    if ( o->IsRebateArtSelection () ) d->ZUGRUND[ZU_WAHL_STELLER] = '1';
    if ( o->IsNoRebateQty () ) d->ZUGRUND[ZU_NO_QTY_NR] = '1';
    if ( o->IsNoCics () ) d->ZUGRUND[ZU_NO_CICS] = '1';
    if ( o->IsNullDocument () ) d->ZUGRUND[ZU_NULL_DOKU] = '1';
    if ( o->IsHighValuePosition () ) d->ZUGRUND[ZU_HIGH_VALUE] = '1';
    if ( o->IsManufacturerInventory () ) d->ZUGRUND[ZU_INVENTUR_HERST] = '1';
    if ( o->IsKonsigPartnerInventory () ) d->ZUGRUND[ZU_INVENTUR_KONSIG] = '1';
    copyCharToString(d->NACHLIEFERTYP, o->Customer()->NachLieferTyp());
    copyCharToString(d->EILSPERRE, o->Customer()->Flags().IsEilSperre() ? '1' : '0');
    d->DATUMAUSLIEFERUNG = (o->DatumAuslieferung().GetYYYYMMDD());
    AllgStrCopy(d->SUB_ORDER_TYPE, o->SubOrderType(), L_AUFTRAG_SUB_ORDER_TYPE);
    copyCharToString(d->KZKDKK, o->Customer()->IsHealthFundAuthorized() ? '1' : '0');
    copyCharToString(d->SKDRETAILPERMIT, o->Customer()->Flags().IsRetailPermit() ? '1' : '0');
    d->DATUMBTM = (o->DatumBTM().GetYYYYMMDD());
    AllgStrCopy(d->BTMFORMULARNR, o->BTMFormularNr(), L_AUFTRAG_BTMFORMULARNR);
    copyCharToString(d->QUOTAINHERITANCE, o->Customer()->CustomerGroupFlagsList()->isGroupNoQuotaInheritance() ? '0' : '1'); //genau umgekehrt
    d->RELATIONNO = o->getIVCVoucherNo();

    /* Reihenfolge ist wichtig !! */
    if      ( o->IsCancelled() )                       d->STATUS = ORD_STORNIERT;
    else if ( o->IsInvoiced() )                        d->STATUS = ORD_FAKTUR_ENDE;
    else if ( o->IsInvoiceable() )                     d->STATUS = ORD_BEREIT_ZUR_FAKTUR;
    else if ( o->IsShipmentClosed() )                  d->STATUS = ORD_KOMMI_ENDE;
    else if ( o->IsShipmentInProgress() )              d->STATUS = ORD_IN_KOMMI;
    else if ( o->IsEntryClosed() )                     d->STATUS = ORD_ERFASST;
    else if ( o->IsUpdateInProgress() )                d->STATUS = ORD_IN_AENDERUNG;
    else if ( o->IsEntryInProgress() )                 d->STATUS = ORD_IN_ERFASSUNG;
    else if ( o->IsProblemClearance() )                d->STATUS = ORD_DAFUE_FEHLER;
    else if ( o->IsEntryDeferred() )                   d->STATUS = ORD_ZURUECKGESTELLT;
    else if ( o->IsKreditLimitErreicht() )             d->STATUS = ORD_UNBEDINGT;
    else                                               d->STATUS = ORD_UNBEKANNT;

    d->WERTEXCLUSIVE = 0.0;
    if (ps->isBulgaria())
    {
        int pos;
        pxOrderItemList *itemList = NULL;
        itemList = o->ItemList();
        if (itemList == NULL)
            return;
        for (pos = 0; ; pos++)
        {
            pxOrderItem* item = (pxOrderItem *)itemList->At(pos);
            if (item)
            {
                if ((item->ArtBase() != NULL) && item->ArtBase()->IsGoodState() && (item->ArtBase()->AbdaCode()()[0] == '2'))
                {
                    d->WERTEXCLUSIVE += (double)(item->MengeBestaetigt() * (double)item->PreisFaktur() * ( (100 + (double)item->SalesTaxRate())/100) );
                }
            }
            else
                break;
        }
    }
}

/*****************************************************************************/
/* Pruefen Tour auf Vorgabe KommiArt                                         */
/*****************************************************************************/
static void TourKoArt(pxOrder * /*o*/, struct AUFTRAG *d)
{
    pxCustRouteList *rl = order->RouteList();
    if (rl == NULL)
    {
        return;
    }
    for (int anz = 0; ; anz++)
    {
        pxCustRoute* route = (pxCustRoute*)rl->At(anz);
        if (route)
        {
            if (!strncmp(d->TOURID, route->TourId(), L_KNDTOUREN_TOURID))
            {
                if (route->KoArt() != ' ')
                    d->KOART[0] = route->KoArt();
                return;
            }
        }
        else
        {
            return;
        }
    }
}

/*****************************************************************************/
/* Information über einen Auftrag                                            */
/*****************************************************************************/
int AasrvGetOrderInfo(struct AUFTRAG *d, char * /*error_msg*/)
{
    AasrvGetOrderInf(order,d);
    return 0;
}

/*****************************************************************************/
/* Schreiben IVC-Nummer                                                      */
/*****************************************************************************/
int AasrvSetIVCVoucherNo(struct AUFTRAG *d, char * /*error_msg*/)
{
    if(d->RELATIONNO == 0) order->removeIVCVoucherNo();
    else order->setIVCVoucherNo( d->RELATIONNO );
    return 0;
}

/*****************************************************************************/
/* Schreiben Original-Rechnungsnummer                                        */
/*****************************************************************************/
int AasrvSetOriginalInvoiceNo(struct AUFTRAG *d, char * /*error_msg*/)
{
    if(d->RELATIONNO == 0) order->removeOriginalInvoiceNo();
    else order->setOriginalInvoiceNo(d->RELATIONNO);
    return 0;
}

/*****************************************************************************/
/* Anzahl zurückgestellter Aufträge                                              */
/*****************************************************************************/
int AasrvAnzzrorder(struct AUFTRAG *d, char *error_msg)
{
    AllgEntfSpaces( d->TOURID );
    AllgEntfSpaces( d->GERAETNAME );
    AllgEntfSpaces( d->ZUGRUND );
    d->ANZPOS = oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0, Order::EntryDeferred, Order::cStateLast);
    if ( ! (oSelList->IsGoodState()) )
    {
        AllgStrCopy(error_msg, oSelList->ErrorMsg(), MAX_ERROR_MSG_AE);
        if ( oSelList->IsFatalErrorState() || oSelList->IsAbendState() )
        {
            return -1;
        }
        else
        {
            oSelList->Clear();
            return -2;
        }
    }
    oSelList->Clear();
    return 0;
}

/*****************************************************************************/
/* Selektion von Auftraegen                                                  */
/*****************************************************************************/
int AasrvSelOrder(struct AUFTRAG *d, char *error_msg)
{
    static int anz = 0;

    if (!anz)
    {
        oSelList->ClearError();
        oSelList->Clear();
        AllgEntfSpaces( d->TOURID );
        AllgEntfSpaces( d->GERAETNAME );

        switch (d->FETCH_REL)
        {
        case SORT_ORDER_ORDNUMBER:
            oSelList->SortOrder(pxOrderList::SortDefault);
            break;
        case SORT_ORDER_IDF:
            oSelList->SortOrder(pxOrderList::SortIDFNr);
            break;
        case SORT_ORDER_TOUR:
            oSelList->SortOrder(pxOrderList::SortTourId);
            break;
        case SORT_ORDER_APO_ENDE:
            oSelList->SortOrder(pxOrderList::SortBusyTime);
            break;
        default:
            oSelList->SortOrder(pxOrderList::SortDefault);
            break;
        }

        switch (d->STATUS)
        {
        case ORD_UNBEKANNT:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0, Order::cStateLast);
            break;
        case ORD_STORNIERT:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0, Order::Cancelled, Order::cStateLast);
            break;
        case ORD_FAKTUR_ENDE:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0, Order::Invoiced, Order::NOT_Cancelled, Order::cStateLast);
            break;
        case ORD_BEREIT_ZUR_FAKTUR:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0,
                             Order::Invoiceable, Order::NOT_Invoiced, Order::NOT_Cancelled, Order::cStateLast);
            break;
        case ORD_KOMMI_ENDE:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0,
                             Order::ShipmentClosed, Order::NOT_Invoiceable, Order::NOT_Invoiced, Order::NOT_Cancelled, Order::cStateLast);
            break;
        case ORD_IN_KOMMI:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0,
                             Order::ShipmentInProgress, Order::NOT_ShipmentClosed, Order::NOT_Invoiceable,
                             Order::NOT_Invoiced, Order::NOT_Cancelled, Order::cStateLast);
            break;
        case ORD_ERFASST:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0,
                             Order::EntryClosed, Order::NOT_ShipmentInProgress, Order::NOT_ShipmentClosed, Order::NOT_Invoiceable,
                             Order::NOT_Invoiced, Order::NOT_Cancelled, Order::cStateLast);
            break;
        case ORD_IN_AENDERUNG:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0, Order::UpdateInProgress, Order::cStateLast);
            break;
        case ORD_IN_ERFASSUNG:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0, Order::EntryInProgress, Order::cStateLast);
            break;
        case ORD_ZURUECKGESTELLT:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0, Order::EntryDeferred, Order::cStateLast);
            break;
        case ORD_DAFUE_FEHLER:
            oSelList->SelectByCustomerNo(d->IDFNR, d->TOURID, d->GERAETNAME, 0, Order::NOT_EntryInProgress, Order::ProblemClearance, Order::cStateLast);
            break;
        default:
            break;
        }

        if ( ! (oSelList->IsGoodState()) )
        {
            anz = 0;
            oSelList->Clear();
            return handleError(oSelList, error_msg);
        }
    }
    pxOrder* o = (pxOrder *)oSelList->At(anz);
    if (o)
    {
        AasrvGetOrderInf(o, d);
        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        oSelList->Clear();
        return 1;
    }
}

/*****************************************************************************/
/* Oeffnen eines Auftrages                                                   */
/*****************************************************************************/
int AasrvOpenorder(struct AUFTRAG *d, char *error_msg)
{
    ps->resetOrderEntryParam();
    order = new pxOrder(ps, d->KDAUFTRAGNR, cDBOPEN_INSERT);
    if (order ==  NULL)
    {
        AllgStrCopy(error_msg, TXT_AUFTR_NICHT_OFFEN , MAX_ERROR_MSG_AE);
        return -2;
    }
    order->OpenOrder(cDBOPEN_INSERT);
    if ( ! (order->IsGoodState()) )
    {
        AllgStrCopy(error_msg, order->ErrorMsg(), MAX_ERROR_MSG_AE);
        if ( order->IsFatalErrorState() || order->IsAbendState() )
        {
            return -1;
        }
        else
        {
            if (order->IsChangeable())
            {
                AasrvGetOrderInf(order, d);     //nase alte Bemerkung wird überschrieben
                AllgStrCopy(d->BEMERKUNGEN, order->ErrorMsg(), L_AUFTRAG_BEMERKUNGEN);
                handleProblemClearance(d, order);
                d->FEHLER = -2;
                return 0;
            }
            return -2;
        }
    }
    AasrvGetOrderInf(order, d);
    handleProblemClearance(d, order);
    copyCharToString(d->NOMOREPOS, (order->IsSeparatedOrder() || (order->KdAuftragNrOrg() > 0)) ? '1' : '0');

    if ( order->IsKreditLimitErreicht() )
    {
        d->ZUGRUND[ZU_KREDITLIMIT] = '1';
    }
    if ( order->IsDefferedForInternet() )
    {
        d->ZUGRUND[ZU_INTERNET] = '1';
    }
    if ( order->IsDefferedForBackRouting() )
    {
        d->ZUGRUND[ZU_BACKROUTING] = '1';
    }
    if ( order->IsDDNotClose() )
    {
        d->ZUGRUND[ZU_DD_OHNE] = '1';
    }
    if ( order->IsSeparateArtGroup() )
    {
        d->ZUGRUND[ZU_BTM] = '1';
    }
    if ( order->IsOverDriveCondition() )
    {
        d->ZUGRUND[ZU_OV] = '1';
    }
    if ( order->IsRebateArtSelection() )
    {
        d->ZUGRUND[ZU_WAHL_STELLER] = '1';
    }
    if ( order->IsNoRebateQty() )
    {
        d->ZUGRUND[ZU_NO_QTY_NR] = '1';
    }
    if ( order->IsNoCics() )
    {
        d->ZUGRUND[ZU_NO_CICS] = '1';
    }
    if ( order->IsNullDocument() )
    {
        d->ZUGRUND[ZU_NULL_DOKU] = '1';
    }
    if ( order->IsHighValuePosition() )
    {
        d->ZUGRUND[ZU_HIGH_VALUE] = '1';
    }
    if ( order->IsManufacturerInventory() )
    {
        d->ZUGRUND[ZU_INVENTUR_HERST] = '1';
    }
    if ( order->IsKonsigPartnerInventory() )
    {
        d->ZUGRUND[ZU_INVENTUR_KONSIG] = '1';
    }

    return 0;
}

static void handleProblemClearance(struct AUFTRAG* d, pxOrder* o)
{
    if (o->IsProblemClearance())
    {
        d->STATUS = o->IsCallBack() ? ORD_DAFUE_RR : ORD_DAFUE_FEHLER; //echter Status ist in Erfassung
        copyCharToString(d->KZDEFOFLOW, o->IsCorruptLimitCheck() ? '1' : '0');
    }
}

/*****************************************************************************/
/* Oeffnen eines neuen Auftrages                                             */
/*****************************************************************************/
int AasrvNeworder(struct AUFTRAG *d, char *error_msg)
{
    ps->resetOrderEntryParam();
    d->VERTRIEBSZENTRUMNR = pxCustomerRouting(ps, d->VERTRIEBSZENTRUMNR, d->KUNDENNR);

    pxCustBase customer(ps, d->VERTRIEBSZENTRUMNR, d->KUNDENNR);
    if ( !customer.IsGoodState() )
    {
        AllgStrCopy(error_msg, customer.ErrorMsg(), MAX_ERROR_MSG_AE);
        return -1;
    }

    if ((d->KDAUFTRAGNR = customer.GetDeferredOrderNr()) != 0 )
    {
        return AasrvOpenorder(d,error_msg);
    }

    order = new pxOrder(ps, customer);
    if (order ==  NULL )
    {
        AllgStrCopy(error_msg, TXT_AUFTR_NICHT_OFFEN , MAX_ERROR_MSG_AE);
        return -2;
    }
    if ( !order->IsGoodState() )
    {
        AllgStrCopy(error_msg, order->ErrorMsg(), MAX_ERROR_MSG_AE);
        if ( order->IsFatalErrorState() || order->IsAbendState() )
        {
            return -1;
        }
        else
        {
            if (order->IsChangeable())
            {
                AasrvGetOrderInf(order, d);
                AllgStrCopy(d->BEMERKUNGEN, order->ErrorMsg(), L_AUFTRAG_BEMERKUNGEN);
                d->FEHLER = -2;
                return 0;
            }
            else
                return -2;
        }
    }
    if (ps->Device()->IsDCT())
    {
        order->SetAuftragVomXML();
    }

    AasrvGetOrderInf(order, d);
    TourKoArt(order, d);
    return 0;
}

/*****************************************************************************/
/* Oeffnen eines InfoAuftrages                                               */
/*****************************************************************************/
int AasrvOpenInfoorder(struct AUFTRAG *d, char *error_msg)
{
    ps->resetOrderEntryParam();
    if (InfoOrder !=  NULL )
        delete InfoOrder;
    InfoOrder = new pxOrder(ps, d->KDAUFTRAGNR, cDBOPEN_READONLY);
    if (InfoOrder ==  NULL)
    {
        AllgStrCopy(error_msg, TXT_AUFTR_NICHT_OFFEN , MAX_ERROR_MSG_AE);
        return -2;
    }
    InfoOrder->OpenOrder(cDBOPEN_READONLY);
    if ( ! (InfoOrder->IsGoodState()) )
    {
        return handleError(InfoOrder, error_msg);
    }
    AasrvGetOrderInf(InfoOrder, d);

    pxGenericOrderRemarkList remarklist(ps);
    if (remarklist.SelectOrderRemarksByOrderNoAndType(d->KDAUFTRAGNR, eSAPReferenceNo))
    {
        pxGenericOrderRemark* remark = (pxGenericOrderRemark*)remarklist.First();
        AllgStrCopy(d->SAP_REFERENCENO, remark->RemarkText().c_str(), L_AUFTRAG_SAP_REFERENCENO);
    }

    return 0;
}

/*****************************************************************************/
/* Schliessen des aktuellen Auftrages                                        */
/*****************************************************************************/
int AasrvCloseorder(struct AUFTRAG *d, char *error_msg)
{
//  int bIsProblemClearance = order->IsProblemClearance();
    order->ClearError();
    order->ClearProblemClearance();
    if (d->SETORDERLABEL[0] == '1')
    {
        order->SetDefaultOrderLabel();
    }
    switch (d->STATUS)
    {
    case ORD_ERFASST:
    case ORD_WEITERER_AUFTRAG:
    case ORD_ERFASST_NO_COND:
        order->ClearSepDefectOrder();
        if ( order->IsDefferedForInternet() || order->IsKreditLimitErreicht() )
        {
            AllgStrCopy(error_msg, "not allowed", MAX_ERROR_MSG_AE);
            return -2;
        }
        if ( order->IsOrderConsolidation() && d->STATUS != ORD_ERFASST_NO_COND ) //Auftragszusammenfuehrung(nur bei NO00)
        {
            order->ClearDDNotClose();
            order->Close();
        }
        else
        {
            order->ClearDDNotClose();
            order->Close(Order::EntryClosed);
        }
        if (handleCloseOrderBG(ps, d, order))
        {
            return 0;
        }
        break;
    case ORD_UNBEDINGT:
        order->ClearDefferedForInternet();
        if ( order->IsOrderConsolidation() ) //Auftragszusammenfuehrung(nur bei NO00)
        {
            if ( order->IsKreditLimitErreicht() || order->IsSeparateArtGroup() )    //bei seperate Group kann nichts mehr angehängt werden, also sofort abschliessen
            {
                order->Close(Order::EntryClosed, Order::cClose_UnConditional);
            }
            else
            {
                order->Close();
            }
        }
        else
        {
            order->Close(Order::EntryClosed, Order::cClose_UnConditional);
        }
        break;
    case ORD_ZURUECKGESTELLT:
        order->Close();
        break;
    case ORD_ZU_INTERNET:
        order->SetProblemClearance();
        order->SetDefferedForInternet();
        if (order->EstimateDepartureTime(error_msg) == 0)
            AllgStrCopy(d->TOURID,error_msg, L_AUFTRAG_TOURID);
        order->Close();
        break;
    case ORD_ZU_CLEAR_INTERNET:
        order->ClearDefferedForInternet();
        if (order->EstimateDepartureTime(error_msg) == 0)
            AllgStrCopy(d->TOURID,error_msg, L_AUFTRAG_TOURID);
        if (   order->IsOrderConsolidation()  //Auftragszusammenfuehrung(nur bei NO00)
            || order->Customer()->Flags().IsAuftragZurueck() ) //Auftrag immer zurückstellen
        {
            if ( order->Customer()->Flags().IsAuftragZurueck() ) //Auftrag immer zurückstellen
                order->SetProblemClearance();
            order->Close();
        }
        else
        {
            order->Close(Order::EntryClosed);
        }
        break;
    case ORD_ZU_DD_OHNE:
        order->SetProblemClearance();
        order->SetDDNotClose();
        order->Close();
        if (handleCloseOrderBG(ps, d, order))
        {
            return 0;
        }
        break;
    case ORD_ZU_CLEAR_DD_OHNE:
        order->ClearDDNotClose();
        order->Close();
        if (handleCloseOrderBG(ps, d, order))
        {
            return 0;
        }
        break;
    case ORD_ZURUECKGEST_DAFUE:
        order->SetProblemClearance();
        if ( ! (order->IsGoodState()) )
        {
            return handleError(order, error_msg);
        }
        order->Close();
        break;
    case ORD_KEIN_AUFTRAG:
        order->CancelOrder(pxDVC_UNDEFINED);
        break; //nase Herr Hoppe klaert gegfls. neuen Parameter
    case ORD_STORNIERT:
        order->CancelOrder(pxDVC_UNDEFINED);
        if (ps->isBulgaria() && order->IsNoCics())
        {
            d->ZUGRUND[ZU_NO_CICS] = '1';
            return 0;
        }
        break;
    case ORD_STORNO_UNBEDINGT:
        order->CancelOrder(pxDVC_UNDEFINED, Order::cCancel_UnConditional);
        break;
    case ORD_STORNO_DAFUE:
        order->CancelOrder(pxDVC_DCT);
        break;
    default:
        AllgStrCopy(error_msg, "AasrvCloseorder: ORD_ FALSE", MAX_ERROR_MSG_AE);
        return -1;
    }

    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    if ( d->STATUS != ORD_STORNO_DAFUE )
    {
        delete order;
        order = NULL;
    }
    return 0;
}

static bool handleCloseOrderBG(pxSession* session, struct AUFTRAG* d, pxOrder* o)
{
    if (session->isBulgaria())
    {
        if (o->IsRebateArtSelection())
        {
            d->ZUGRUND[ZU_WAHL_STELLER] = '1';
        }
        if (o->IsNoRebateQty())
        {
            d->ZUGRUND[ZU_NO_QTY_NR] = '1';
        }
        if (o->IsNoCics())
        {
            d->ZUGRUND[ZU_NO_CICS] = '1';
        }
        return (o->IsRebateArtSelection() || o->IsNoRebateQty() || o->IsNoCics());
    }
    return false;
}

/*****************************************************************************/
/* Aendern von Auftrags und Kommiart des aktuellen Auftrags                  */
/*****************************************************************************/
int AasrvChangeorder(struct AUFTRAG *d, char *error_msg)
{
    nString     text;             // ein String-Objekt
    text = d->KDAUFTRAGART;
    nString     sub;             // ein String-Objekt
    sub = d->SUB_ORDER_TYPE;
    char KoArt[1];
    KoArt[0] = order->KoArt();
    order->ClearError();
    if (order->AnzPos() == 0 && d->TENDERNO > 0)
        order->SetTenderNo(d->TENDERNO);
    if (ps->isBulgaria() && !strncmp(d->KDAUFTRAGART, "CO", 2))
    {
        order->ClearKreditLimitErreicht();
    }
    int AnzDefDurchUmbuch = order->OrderType(text, d->KOART[0], d->BUCHART[0], sub);
    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    AllgStrCopy(cKdauftragArt, order->KdAuftragArt(), L_AUFTRAG_KDAUFTRAGART);
    d->ANZDEFEKTUB = (long) AnzDefDurchUmbuch;
    if (order->CstDiscountAccount() != NULL)
    {
        d->BALANCE = order->GetCstDiscAccBalance(0);
//      d->BALANCE2 = order->GetCstDiscAccBalance(1);
    }
    AllgStrCopy(d->TOURID, order->TourId(), L_AUFTRAG_TOURID);
    d->DELIVERYDATE = order->getDeliveryDate();
    if (KoArt[0] != d->KOART[0])
    {
        order->WriteCommiTypeChangeEvent();
    }

    return 0;
}

/*****************************************************************************/
/* Aendern der Auftragsbemerkung                                             */
/*****************************************************************************/
int AasrvChangeOrdBem(struct AUFTRAG *d, char *error_msg)
{
    nString   nStr = d->BEMERKUNGEN;
    nStr.Strip();
    order->ClearError();
    order->Bemerkungen(nStr);
    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    order->SetOrderRemarkText(nStr);
    return 0;
}

/*****************************************************************************/
/* Aendern der Auftragsvaluta                                                */
/*****************************************************************************/
int AasrvChangeValuta(struct AUFTRAG *d, char *error_msg)
{
    order->ValDate(d->VALUTAMONATE);
    d->STATUS = ITEM_STAT_NORMAL;
    if ( ! (order->IsGoodState()) )
    {
        if ( order->ErrorNumber() == CMSG_ORD_CREDITLIMIT_EXHAUSTED)
        {
            d->STATUS = ITEM_STAT_KREDITLIMIT;
            return 0;
        }
        else
        {
            return handleError(order, error_msg);
        }
    }
    return 0;
}

/*****************************************************************************/
/* Aendern der Tour                                                          */
/*****************************************************************************/
int AasrvChangeTour(struct AUFTRAG *d, char *error_msg)
{
    nString     text;             // ein String-Objekt
    nString     tourid;            // ein String-Objekt
    text = d->TOURID;
    tourid = order->TourId();

    order->RouteAssignSpecificTour(text); // OK
    order->getTourAssignmentUtil()->isTourValidForOrderClosure(text);

    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    if (tourid != text)
    {
        order->WriteTourIdChangeEvent();
    }
    d->DELIVERYDATE = order->getDeliveryDate();
   return 0;
}

/*****************************************************************************/
/* Aendern der Tour                                                          */
/*****************************************************************************/
/* Wird nie aufgerufen
int AasrvChangeTourFutur(struct AUFTRAG *d,char *error_msg)
{
    nString     text;             // ein String-Objekt
    text = d->TOURID;
    order->RouteAssignSpecificTour(text);
    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    return 0;
}
*/

/*****************************************************************************/
/* Aendern der Tour                                                          */
/*****************************************************************************/
/* Wird nie aufgerufen
int AasrvChangeTourSonder(struct AUFTRAG *d,char *error_msg)
{
    nString     text;             // ein String-Objekt
    text = d->TOURID;
    order->RouteAssignSpecificTour(text);
    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    return 0;
}
*/

/*****************************************************************************/
/* Aendern des Kunden                                                        */
/*****************************************************************************/
int AasrvChangeCustomer(struct AUFTRAG *d, char *error_msg)
{
    order->ClearError();
    order->ChangeCustomer(d->IDFNR,d->VERTRIEBSZENTRUMNR);
    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    AasrvGetOrderInf(order, d);
    return 0;
}

/******************************************************************************/
/* Liefert die dedizierte auftragartkd zu einem bestehenden VZ / IDF / AufArt */
/******************************************************************************/
int AasrvGetCustOrderType(auftragartkdS *d, char * /*error_msg*/)
{
    pxCustOrderType* customerOrderType = new pxCustOrderType(&getSession());

    if ( 0 == customerOrderType->getCustomerOrderType( d->VERTRIEBSZENTRUMNR, d->IDFNR, d->KDAUFTRAGART ) )
    {
        d->ORDERLABELCOUNT = customerOrderType->OrderLabelCount();
        // add further fields from auftragartkd, if necessary
        return 0;
    }

    return 1; // not found
}

/*****************************************************************************/
/* Liefert erlaubte Auftragsarten fuer einen Kunden                          */
/*****************************************************************************/
int AasrvGetaartes(struct AUFARTES *d, char * /*error_msg*/)
{
    static unsigned int anz = 0;

    bool currentOrderTypeHasReservationConfig = false;
    libcsc::stockbooking::IOrderTypeReservationConfigCollectionPtr current_configs =
                ps->getStockBookingComponentManager()->getReservationConfigRepository()->findOrderTypeReservationConfig(order->KdAuftragArt()());
    if (NULL != current_configs.get() && current_configs->size() > 0)
    {
        currentOrderTypeHasReservationConfig = true;
    }


    pxCustOrderTypeList* oCustTypeList = order->Customer()->OrderTypeList(); //Auftragsartenliste
    while (anz < order->Customer()->OrderTypeList()->Entries())
    {
        pxCustOrderType* oType = (pxCustOrderType*)oCustTypeList->At(anz);
        if (oType)
        {
            nString ot = oType->KdAuftragArt();
            if (true == currentOrderTypeHasReservationConfig && order->KdAuftragArt() != ot && order->AnzPos() > 0)
            {
                ++anz;
                continue;
            }
            libcsc::stockbooking::IOrderTypeReservationConfigCollectionPtr configs =
                ps->getStockBookingComponentManager()->getReservationConfigRepository()->findOrderTypeReservationConfig(ot());
            if (NULL != configs.get() && configs->size() > 0 && order->KdAuftragArt() != ot && order->AnzPos() > 0)
            {
                ++anz;
                continue;
            }

            AllgStrCopy(d->KDAUFTRAGART, oType->KdAuftragArt(), L_AUFARTES_KDAUFTRAGART);
            AllgStrCopy(d->BEZEICHNUNG, oType->Bezeichnung(), L_AUFARTES_BEZEICHNUNG);
            d->VALUTAMONATE = oType->ValMonths();
            d->SMUSTSUBORDER[0] = (oType->IsMustSubOrder()) ? '1' : '0';
            d->SONLYEH[0] = (oType->IsOnlyEH()) ? '1' : '0';
            ++anz;
            return 0;
        }
        ++anz;
    }
    anz = 0;
    return 1;
}

/*****************************************************************************/
/* Liefert mögliche Touren für den Auftrag                                   */
/*****************************************************************************/
int AasrvGettouren(kndtourenS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static pxCustRouteList *rl = NULL;
    if ((order->BatchSchreiben() == cORTYPE_AUXILIARY) && order->Param()->IsSIbtCstOrg())
    {
        rl = order->ShuttleRouteList(d->KDAUFTRAGART);
    }
    else
    {
        rl = order->RouteList(d->KDAUFTRAGART);
    }
    if (rl == NULL)
    {
        anz = 0;
        return 1;
    }
    pxCustRoute* route = (pxCustRoute*)rl->At(anz);
    if (route)
    {
        AllgStrCopy(d->TOURID, route->TourId(), L_KNDTOUREN_TOURID);
        d->FAHRTZEIT = static_cast<short>(route->FahrtZeit());
        d->KOART[0] = route->KoArt();
        d->KZAUTOZUORD[0] = route->KZAutoZuord();
        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*****************************************************************************/
/* Liefert mögliche Touren für den Auftrag bei                               */
/*****************************************************************************/
int AasrvGettourenAufArt(kndtourenS *d, char * /*error_msg*/)
{
    static int anz = 0;
    char kdauftragart[3];
    static pxCustRouteList *rl;
    if (anz == 0)
    {
        sprintf(kdauftragart,"%2.2s", d->TOURID);
        rl = NULL;
        order->ClearError();
        anz = 0;
        return 1;
    }
    pxCustRoute* route = (pxCustRoute*)rl->At(anz);
    if (route)
    {
        AllgStrCopy(d->TOURID, route->TourId(), L_KNDTOUREN_TOURID);
        d->FAHRTZEIT = static_cast<short>(route->FahrtZeit());
        d->KOART[0] = route->KoArt();
        d->KZAUTOZUORD[0] = route->KZAutoZuord();
        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*****************************************************************************/
/** Auftragsposition                                                        **/
/*****************************************************************************/

/*****************************************************************************/
/* Liefert die Positionsart einer Position                                   */
/*****************************************************************************/
static void GetPosArt(pxOrderItem *item, char *pa)
{
    /* 1.Position */
    pa[0] = '*';
    if ( item->GeraetTyp() == pxDVC_VIDEO_WORKSTATION ||
         item->GeraetTyp() == pxDVC_VIDEO_TERMINAL    ||
         item->GeraetTyp() == pxDVC_VIDEO )
    {
        pa[0] = '0';
    }
    if (item->GeraetTyp() == pxDVC_DCT_PARALLEL ||
        item->GeraetTyp() == pxDVC_DCT )
    {
        pa[0] = '1';
    }
    if ((item->GeraetTyp() != pxDVC_DCT_SERIAL && item->IsText()) || item->IsDispoItem())
    {
        pa[0] = '2';
    }
    if (item->IsCancelled())
    {
        pa[0] = '3';
    }
    if (item->GeraetTyp() == pxDVC_DCT_SERIAL && !item->IsText())
    {
        pa[0] = '5';
    }
    if (item->GeraetTyp() == pxDVC_DCT_SERIAL && item->IsText())
    {
        pa[0] = '6';
    }

    /* 2.Position */
    nString bem = item->Bemerkungen();
    bem.Strip();
    if (item->IsDispoItemValued())
    {
        pa[1] = '2';
    }
    else if (item->IsText() || (item->IsDispoItem() && !item->IsDispoItemValued()))
    {
        pa[1] = '3';
    }
    else if (!bem.IsEmpty())
    {
        pa[1] = '4';
    }
    else
    {
        pa[1] = '0';
    }

    pa[2] = '\0';
}

/* Liefert Positionsinformationen                                               */
static void AasrvPosInfNormal(pxOrderItem *item, struct AUFPOSBUCH *d)
{
    d->ETARTSCHALTER1 = 0; //Initialisierung
    d->ETARTKLASSE1 = 0; //Initialisierung
    d->ETARTSCHALTER2 = 0; //Initialisierung
    d->ETPOSSCHALTER2 = 0; //Initialisierung
    if (item->IsSperreRabattManuell())
        d->ETPOSSCHALTER2 += 16; //Artikel nicht aenderbar
    if (item->IsDelayedDelivered())
        d->ETPOSSCHALTER2 += 256; //gesplittet verzoegerte
    if (item->IsSeparatePosition())
        d->ETPOSSCHALTER2 += 32; //gesplittet anderer Auftrag
    copyCharToString(d->KZFREITEXT, '0');

    d->PRODUSERQUOTA = item->IsProduserQuotaDefect() ? 1 : 0;

    nString CStr("");
    if (item->ArtBase() != NULL && item->ArtBase()->IsGoodState())   //Artikel befindet sich im Artikelstamm
    {
        AllgStrCopy(d->ARTIKEL_NAME, item->ArtBase()->Bezeichnung(), L_AUFPOSBUCH_ARTIKEL_NAME);
        AllgStrCopy(d->ARTIKEL_LANGNAME, item->ArtBase()->ArtikelLangname(), L_AUFPOSBUCH_ARTIKEL_LANGNAME);
        AllgStrCopy(d->EINHEIT, item->ArtBase()->Einheit(), L_AUFPOSBUCH_EINHEIT);
        AllgStrCopy(d->DARREICHFORM, item->ArtBase()->Darreichform(), L_AUFPOSBUCH_DARREICHFORM);
        d->LAGERBEREICHNR = item->ArtBase()->LagerBereichNr();
        d->TAXLEVEL = item->ArtBase()->TaxLevel();
        if (item->ArtBase()->ArtFlags().IsContainerArtikel())
            d->ETARTSCHALTER2 += 512; //nase
        if (item->ArtBase()->ArtClass().IsOpiat())
            d->ETARTKLASSE1 += 512; //nase
        if (item->ArtBase()->ArtFlags().IsGekuehlt08())
            d->ETARTSCHALTER1 += 128; //nase
        if (item->ArtBase()->ArtFlags().IsGekuehlt20())
            d->ETARTSCHALTER1 += 64; //nase
        if (item->ArtBase()->ArtFlags().IsKuehlKette())
            d->ETARTSCHALTER1 += 32; //nase

        //Kurzbemerkung Artikelstatis
        //ist noch einmal in aafview.cpp definiert !!!!!!
        if (item->ArtBase()->ArtFlags().IsSekundaerBezeichnung())
            CStr += "9";        // Sekundaerbezeichner
        if (item->ArtBase()->ArtFlags().IsNachfolgeArtikel())
            CStr += "E";        // Nachfolgeartikel
        switch (item->ArtBase()->Prisoart())
        {
        case '1':
            CStr += "SL";
            break;
        case '2':
            CStr += "SZ";
            break;
        case '3':
            CStr += "SB";
            break;
        default:
            break;
        }
        if (item->ArtBase()->ArtFlags().IsAusserHandel            ())    CStr += "A";        // ausser Handel
        if (item->ArtBase()->ArtFlags().IsNichtUeberGrossHandel   ())    CStr += "G";        // nicht ueber Grosshandel
        if (item->ArtBase()->ArtFlags().IsNichtGeliefertHersteller())    CStr += "H";        // vom Hersteller nicht geliefert
        if (item->ArtBase()->ArtFlags().IsNichtLieferbarHersteller())    CStr += "L";        // vom Hersteller nicht lieferbar
        if (item->ArtBase()->ArtFlags().IsNettoAktion             ())    CStr += "P";        // Netto
        if (item->ArtBase()->ArtFlags().IsNatraArtikel            ())    CStr += "N";        // Natra
        if (item->ArtBase()->ArtFlags().IsReimportArtikel         ())    CStr += "R";        // Reimport
        if (   !item->ArtBase()->ArtFlags().IsArtikelGefuehrt()
            && item->Session()->getStockBooking()->GetAvailableQtyInStock(*item->ArtBase()) == 0) CStr += "F";      // Artikel wird nicht gefuehrt
    }
    else                          //Artikel nicht im Artikelstamm
    {
        d->ARTIKEL_NAME[0] = '\0';
        d->EINHEIT[0] = '\0';
        d->DARREICHFORM[0] = '\0';
    }
    AllgStrCopy(d->KURZBEZKONDI, CStr, L_AUFPOSBUCH_KURZBEZKONDI);
    AllgStrCopy(d->BEMERKUNG, item->Bemerkungen(), L_AUFPOSBUCH_BEMERKUNG);
    AllgStrCopy(d->CHARGENNR, item->GetChargenNr().c_str(), L_AUFPOSBUCH_CHARGENNR);

    if (item->IsFixBatch())
    {
        d->FIXBATCH = 1;
    }
    else
    {
        d->FIXBATCH = 0;
    }


    d->ARTIKEL_NR       =  item->ArtikelNr();
    d->MENGEBESTELLT    =  item->MengeBestellt();
    d->MENGENATRA       =  item->MengeNatra();
    d->MENGEABGEBUCHT   =  item->MengeBestaetigt();
    d->MENGEGELIEFERT   =  item->MengeGeliefert();
    d->MENGEBESTELLTNATRA  =  item->MengeBestelltNatra();
    d->MENGE            =  item->MengeVerbund();
    if ( (d->PREISEKAPO = item->PreisEKApoNetto()) == 0)
        d->PREISEKAPO = item->PreisEKApo();
    d->PREISEKAPOFREE   =  item->PreisEKApoFree();
    d->PREISVKAPO       =  item->GetCalcAvp();
    d->FILIALNR1        =  item->VerbundFilialNr();
    d->FEHLERMENGE      =  item->IsNetPrice() ? static_cast<short>(d->MENGEBESTELLT) : 0;

    copyCharToString(d->KZLIMITCHK, item->IsQStateLimitCheck() ? '1' : '0');

    // if ( d->MENGEBESTELLT > d->MENGEABGEBUCHT)
    copyCharToString(d->KZDEFEKT, (!item->IsQStateGood() || !item->IsArtStateGood()) ? '1' : '0');
    d->PREIS_TYP = static_cast<short>(item->PreisTyp());
    d->ARTICLE_NO_PACK = item->ArticleNoPack();
    d->IBTTYPE = item->IBTType();
    d->DISCOUNTVALUEPCT = item->GetDiscountValuePct();
    d->DISCOUNTVALPCTMAN = item->GetDiscountValPctMan();
    if (ps->isCroatia()) // only for Croatia
    {
        d->DISCOUNTVALPCTMAN = d->DISCOUNTVALUEPCT;
    }
    d->PROMOTYP = item->PromoTyp();
    d->PROMOTION_NO = item->PromotionNo();
    d->PREISFAKTUR = item->InvoiceValue();      // Rabattierter Preis
    d->CODE_TYPE = item->CodeType();
    AllgStrCopy(d->ARTICLE_CODE, item->ArticleCode(), L_AUFPOSBUCH_ARTICLE_CODE);
    if (order != NULL)
    {
        if (ps->isBulgaria())
        {
            d->WERTKL = order->ShowCreditLimit2();  // Restliches Kreditlimit K2
            d->WERTKL1 = order->ShowCreditLimit1(); // Restliches Kreditlimit K1
        }
        else
        {
//          d->WERTKL = order->ShowCreditLimit();   // Restliches Kreditlimit
            d->WERTKL = 0.0;    // Restliches Kreditlimit
            d->WERTKL1 = 0.0;   // Restliches Kreditlimit K1
        }
    }
    if (d->PROMOTION_NO > 0)
    {
        pxOrderPosPromo* pospromo = item->GetOrderPosPromo(d->PROMOTION_NO);
        if (pospromo != NULL)
        {
            d->DISCOUNTGRPNO = pospromo->DiscountGrpNo();
            d->BASEQTY = pospromo->BaseQty();
            d->BASE_VALUE = pospromo->BaseValue();
            d->CUSTOMERNO = pospromo->CustomerNo();
            AllgStrCopy(d->PHARMACYGROUPID, pospromo->PharmacyGroupId(), L_AUFPOSBUCH_BEMERKUNG);
        }
    }
    d->PROBLEMSTATE = item->ProblemState();
    d->LINKPOSNR = item->LinkPosNr();
    d->HIGHERCOND = item->IsHigherConditionsAvailable();
    d->IBTTYPEID = item->getNLevelIBTTypeID();
    if ( item->TotalIBTQuantity() > 0 || item->getOriginalIBTQtyFromSplittedOrder() > 0 ) //if (orderitem->MengeVerbund() > 0)
    {
        TourInfo* ti = item->getItemTourInformation();
        if ( ti->getTourFound() )
        {
            char cTour[30];
            d->DELIVERYTIME = item->getItemDeliveryTime(*cTour, true);
            d->DELIVERYDATE = item->getItemDeliveryDate( true );
            AllgStrCopy(d->TOURID, cTour, L_AUFPOSBUCH_TOURID);
        }
    }
    else
    {
        TourInfo* ti = item->getItemTourInformation();
        if ( ti->getTourFound() )
        {
            char cTour[30];
            d->DELIVERYTIME = item->getItemDeliveryTime(*cTour, false);
            d->DELIVERYDATE = item->getItemDeliveryDate( false );
            AllgStrCopy(d->TOURID, cTour, L_AUFPOSBUCH_TOURID);
        }
    }
}

/* Liefert Positionsinformationen bei Freitextposition                                              */
static void AasrvPosInfFreiText(pxOrderItem *item, struct AUFPOSBUCH *d)
{
    tDISPOITEM  di;
    copyCharToString(d->KZFREITEXT, '1');
    d->MENGE            = 0; //Verbundmenge
    item->DispoGet(di);
    AllgStrCopy(d->ARTIKEL_NAME, di.Bezeichnung, L_AUFPOSBUCH_ARTIKEL_NAME);
    AllgStrCopy(d->ARTIKEL_LANGNAME, di.Bezeichnung, L_AUFPOSBUCH_ARTIKEL_NAME);
    AllgStrCopy(d->EINHEIT, di.Einheit, L_AUFPOSBUCH_EINHEIT);
    AllgStrCopy(d->DARREICHFORM, di.Darreichform, L_AUFPOSBUCH_DARREICHFORM);
    AllgStrCopy(d->BEMERKUNG, di.Bemerkungen, L_AUFPOSBUCH_BEMERKUNG);
    d->PREISEKAPO       =    di.PreisEKApo;
    d->PREISEKGROSSO    =    di.PreisEKGrosso;
    d->ARTIKEL_NR       =    ITEM_ARTNR_FREITEXT;
    d->MENGEBESTELLT    =    di.MengeBestellt;
    d->MENGENATRA       =    item->MengeNatra();
    d->MENGEABGEBUCHT   =    item->MengeBestaetigt();
    d->MENGEGELIEFERT   =    item->MengeGeliefert();
    d->RABATTFESTDM     =    di.RabattFestDM;
    d->RABATTFEST       =    di.RabattFest;
    sprintf(d->MWSTSCHLUESSEL,"%d", di.MWSTSchluessel);
    d->TAXLEVEL = static_cast<short>(di.MWSTSchluessel);
    d->TAXPFLICHTIG[0]  =    di.TaxPflichtig ? '1' : '0';
    d->RABATTFAEHIG[0]  =    di.Rabattfaehig ? '1' : '0';
    AllgStrCopy(d->WARENGRUPPEEIGEN, di.WarenGruppeEigen, L_AUFPOSBUCH_WARENGRUPPEEIGEN);
    d->URSPRUNGAUFTRAGNR =   di.UrsprungAuftragnr;
    d->URSPRUNGPOSNR    =    di.UrsprungPosnr;
    d->GEBUEHRBEARB     =    di.GebuehrBearb;
    d->KZPRISO[0]       =    di.KzPriso;
    d->PREISFAKTUR = item->InvoiceValue();      // Rabattierter Preis
}

/* Liefert Positionsinformationen                                               */
static void AasrvPosInf(pxOrderItem *item, struct AUFPOSBUCH *d)
{
    GetPosArt(item, d->POSART);
    d->POSNR  =    item->PosNr();
    if      (item->IsDisponieren())    d->STATUS = ITEM_STAT_DISPO;
    else if (item->IsZugesagt())       d->STATUS = ITEM_STAT_ZUGESAGT;
    else if (item->IsNachliefern())    d->STATUS = ITEM_STAT_NACHLIEFERN; //nase zugesagt klaeren
//  else if (ps->isBulgaria() && d->STATUS == ITEM_STAT_NOREBATE) ;    //so belassen
    else if (d->STATUS == ITEM_STAT_NOREBATE) ;  //so belassen
    else                               d->STATUS = ITEM_STAT_NORMAL;

    switch (item->GeraetTyp())
    {
    case pxDVC_DCT_PARALLEL:
        copyCharToString(d->DAFUEART, ITEM_ART_PARA);
        break;
    case pxDVC_DCT_SERIAL:
        copyCharToString(d->DAFUEART, ITEM_ART_SERA);
        break;
    case pxDVC_DCT:
        copyCharToString(d->DAFUEART, ITEM_ART_DAFUE);
        break;
    default:
        copyCharToString(d->DAFUEART, ITEM_ART_NO_DAFUE);
        break;
    }

    if ( item->IsCustPurchase() )
    {
        copyCharToString(d->KZAPODINL, ITEM_APO_DISPO);
    }
    else if ( item->IsCustRestDelivery() )
    {
        copyCharToString(d->KZAPODINL, ITEM_APO_NACHL);
    }
    else
    {
        copyCharToString(d->KZAPODINL, ITEM_APO_NO_DI_OR_NL);
    }

    copyCharToString(d->KZNACHBEARB, item->IsManualMaintenance() ? '1' : '0');  // Sera-Nachbearbeitung
    copyCharToString(d->KZAUFGENOMMEN, item->IsArtikelUmgeschluesselt() ? '1' : '0');  // Artikel wurde aufgenommen
    copyCharToString(d->KZINFOTEXT, item->IsInfoBelegDrucken() ? '1' : '0');  // Infotext wurde erstellt

    d->SENDESTATUS = static_cast<short>(item->SendeStatus());

    AllgStrCopy(d->KURZBEZKONDI, "", L_AUFPOSBUCH_KURZBEZKONDI);
    if ( item->IsDispoItem() )
        AasrvPosInfFreiText(item, d);
    else
        AasrvPosInfNormal(item, d);
}

/* Liefert Auftragsinformationen nach Pos.-Buchung                              */
static void AasrvAuftrWerte(struct AUFPOSBUCH *d)
{
    d->BESTAND = order->LastStock();
    d->ANZPOS           =   order->AnzPos();
    setAuftragLieferZeilen(d, order);
    d->WERTNETTO        =   order->WertNetto();
    d->WERTRABATT       =   order->WertRabatt();
    setOrderValues(d, order);
    if (order->CstDiscountAccount() != NULL)
    {
        d->BALANCE  =   order->GetCstDiscAccBalance(0);
//      d->BALANCE2 =   order->GetCstDiscAccBalance(1);
    }
    d->WERTEXCLUSIVE = 0.0;
    if (ps->isBulgaria())
    {
        int pos;
        pxOrderItemList *itemList = NULL;
        itemList = order->ItemList();
        if (itemList == NULL) return;
        for (pos = 0; ; pos++)
        {
            pxOrderItem* item = (pxOrderItem*)itemList->At(pos);
            if (item)
            {
                if ((item->ArtBase() != NULL) && item->ArtBase()->IsGoodState() && (item->ArtBase()->AbdaCode()()[0] == '2'))
                {
                    d->WERTEXCLUSIVE += (double)(item->MengeBestaetigt() * (double)item->PreisFaktur() * ( (100 + (double)item->SalesTaxRate())/100) );
//                  d->WERTEXCLUSIVE += (double)(item->MengeBestaetigt() * (double)item->PreisFaktur());
                }
            }
            else
                break;
        }
    }
}

/* Liefert Buchungsart                            */
static pxOrderItem::BookingType GetBuchArt(long status)
{
     switch (status)
     {
     default:
     case ITEM_STAT_NORMAL: // break through
     case ITEM_STAT_IGNORE_PRICELIMIT:
         return pxOrderItem::BookingTypeDefault;
     case ITEM_STAT_DISPO:
         return pxOrderItem::PurchaseOrder;
     case ITEM_STAT_ZUGESAGT:
         return pxOrderItem::DeliveryConfirmed;
     case ITEM_STAT_NACHLIEFERN:
         return pxOrderItem::RestDelivery;
     case ITEM_STAT_NACHFRAGE:
         return pxOrderItem::DemandBooking;
     case ITEM_STAT_NACHLIEFUPD:
         return pxOrderItem::UpdateDelPos;
     }
}

/*****************************************************************************/
/* bucht eine neue Position auf den aktuellen Auftrag                        */
/*****************************************************************************/
int AasrvWritepos(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItem *item = NULL;
    pxOrderItem::BookingType bookingType = GetBuchArt(d->STATUS);
    int bookingFlags = bPOST_DEFAULT;
    if( d->STATUS == ITEM_STAT_IGNORE_PRICELIMIT ){ bookingFlags |= bPOST_IGNORE_PRICELIMIT; }

    bool eIsAux = false;
    order->ClearError();
    d->ARTIKEL_NR = d->ARTIKEL_NR; // BB?
    if ( d->MENGE && d->FILIALNR1) //Verbundmenge
    {
        //Verbundbuchung
        eIsAux = true;
        if (d->PREISEKAPOFREE != 0)
        {
            item = order->NewOrderItem_09( d->ARTIKEL_NR,
                                           d->MENGEBESTAETIGT,
                                           d->FILIALNR1,
                                           (nMoney)d->PREISEKAPOFREE,
                                           d->MENGENATRA,
                                           d->MENGEBESTELLT,
                                           static_cast<PriceTypeEnum>(d->PREIS_TYP),
                                           bookingType,
                                           pxOrderItem::TypeProductStocked,
                                           bookingFlags );
        }
        else
        {
            item = order->NewOrderItem_08( d->ARTIKEL_NR,
                                           d->MENGEBESTAETIGT,
                                           d->FILIALNR1,
                                           d->MENGENATRA,
                                           d->MENGEBESTELLT,
                                           static_cast<PriceTypeEnum>(d->PREIS_TYP),
                                           bookingType,
                                           pxOrderItem::TypeProductStocked,
                                           bookingFlags );
        }
    }
    else
    {
//      if (d->MENGEBESTAETIGT == 0) order->SetProblemClearance();
        //Normalbuchung
        //Preis für die Position setzen
        if (d->PREISEKAPOFREE != 0)
        {
            //Manueller Rabatt für die Position setzen
            if (d->DISCOUNTVALPCTMAN > 0)
            {
                item = order->NewOrderItem_06( d->ARTIKEL_NR,
                                               d->MENGEBESTAETIGT,
                                               d->MENGENATRA,
                                               d->MENGEBESTELLT,
                                               (nMoney)d->PREISEKAPOFREE,
                                               d->DISCOUNTVALPCTMAN,
                                               static_cast<PriceTypeEnum>(d->PREIS_TYP),
                                               bookingType,
                                               pxOrderItem::TypeProductStocked,
                                               bookingFlags,
                                               d->MENGEBESTELLTNATRA);
            }
            else
            {
                item = order->NewOrderItem_05( d->ARTIKEL_NR,
                                               d->MENGEBESTAETIGT,
                                               d->MENGENATRA,
                                               d->MENGEBESTELLT,
                                               (nMoney)d->PREISEKAPOFREE,
                                               static_cast<PriceTypeEnum>(d->PREIS_TYP),
                                               bookingType,
                                               pxOrderItem::TypeProductStocked,
                                               bookingFlags,
                                               d->MENGEBESTELLTNATRA);

            }
        }
        else
        {
            //Manueller Rabatt für die Position setzen
            if (d->DISCOUNTVALPCTMAN > 0)
            {
                item = order->NewOrderItem_04( d->ARTIKEL_NR,
                                               d->MENGEBESTAETIGT,
                                               d->MENGENATRA,
                                               d->MENGEBESTELLT,
                                               d->DISCOUNTVALPCTMAN,
                                               static_cast<PriceTypeEnum>(d->PREIS_TYP),
                                               bookingType,
                                               pxOrderItem::TypeProductStocked,
                                               bookingFlags,
                                               d->MENGEBESTELLTNATRA);
            }
            else
            {
                item = order->NewOrderItem_03( d->ARTIKEL_NR,
                                               d->MENGEBESTAETIGT,
                                               d->MENGENATRA,
                                               d->MENGEBESTELLT,
                                               static_cast<PriceTypeEnum>(d->PREIS_TYP),
                                               bookingType,
                                               pxOrderItem::TypeProductStocked,
                                               bookingFlags,
                                               d->MENGEBESTELLTNATRA);
            }
        }
    }

    if ( ! (order->IsGoodState()) )
    {
        AllgStrCopy(error_msg, order->ErrorMsg(), MAX_ERROR_MSG_AE);
        int err = order->ErrorNumber();
        switch (err)
        {
            case CMSG_ART_QLACK:
                setValuesOnMsgArtQLack(d, order);
                return 0;
            case CMSG_ART_REVERSESUBSTITUTION:
                d->ARTIKEL_NR = order->subArticleNo();
                d->STATUS  = ITEM_STAT_REVERSE;
                return 0;
            case CMSG_ITM_ARTQUOTA_EXEEDED:
                // Restkontigent (RestQuota) oder Restbestand (LastStock)
                d->BESTAND = (order->LastStock() > order->RestQuota()) ? order->RestQuota() : order->LastStock();
                d->MENGE   = 0;                        // Verbundmenge
                d->FILIALNR1 = 0;                      // Verbundfiliale
                d->STATUS  = ITEM_STAT_NACHLIEFUPD;
                return 0;
            case CMSG_ORD_CREDITLIMIT_EXHAUSTED:
                setValuesOnMsgOrdCreditLimitExhausted(d, order);
                return 0;
            case CMSG_ORD_CSTDISCACC_EXHAUSTED:
                d->STATUS = ITEM_STAT_ROEXHAUSTED;
                return 0;
            case CMSG_AD_NOTPOSSIBLE:
                if (eIsAux)
                {
                    d->STATUS = ITEM_STAT_VERBUND_NICHT_MOEGLICH;
                    return 0;
                }
                break;
            case CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE: // fall through
                d->STATUS = ITEM_STAT_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE;
                return 0;

            case CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE: // fall through
                d->STATUS = ITEM_STAT_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE;
                return 0;

            case CMSG_ITM_PRICE_LIMIT_PRODUCT_PRICE_DELETION: // fall through
                if (order->Customer()->KdGruppe() == "06")
                {
                    d->STATUS = ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION_06;
                }
                else
                {
                    d->STATUS = ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION;
                }
                return 0;

            case CMSG_ITM_PRICE_LIMIT_MWP_EXCEEDANCE:
                    // open ??!!??
                 d->STATUS = ITEM_STAT_LIMIT_MWP_EXCEEDANCE;
                 return 0;
            default:
                break;
        }

        if ( order->IsFatalErrorState() || order->IsAbendState() )
        {
            return -1;
        }

        if (err == CMSG_ART_QLACK_DISC_ARTICLE)
        {
            AllgStrCopy(error_msg, item->ErrorMsg(), MAX_ERROR_MSG_AE);
            d->STATUS = ITEM_STAT_NOREBATE;
        }
        else
        {
            return -2;
        }
    }


    if(d->FIXBATCH == 0)
    {
        item->StoreDesiredBatchInfo(d->CHARGENNR);
    }
    else
    {
        item->StoreFixBatchInfo(d->CHARGENNR);
    }


    struct ARTAESEL code;
    if (d->CODE_TYPE == 0)
    {
        code.ARTIKEL_NR = d->ARTIKEL_NR;
        AatartSel_Preferred(&code, error_msg);
        d->CODE_TYPE = code.CODE_TYPE;
        strncpy(d->ARTICLE_CODE, code.ARTICLE_CODE, 25);
    }

    if (item != 0)
    {
        item->SetArticleCodeValues(d->CODE_TYPE, d->ARTICLE_CODE);
    }

    order->ReCalcValues();
    //Bemerkung für die Position setzen
    AllgEntfSpaces( d->BEMERKUNG );
    if (strlen( d->BEMERKUNG ) > 0 )
    {
        nString nStr = d->BEMERKUNG;
        item->Bemerkungen( nStr );
        if ( ! (item->IsGoodState()) )
        {
            return handleError(item, error_msg);
        }
    }
    AasrvAuftrWerte(d);
    if (item != NULL)
    {
//      if (item->ArtBase() != NULL && item->ArtBase()->IsGoodState())
//      {
//          d->BESTAND = item->Session()->getStockBooking()->GetAvailableQtyInStock(*item->ArtBase());
//      }
        AasrvPosInf(item,d);

        // bei abgetrennten Positionen MengeBestätigt der verlinkten Positionen addieren
        long confirmedqty = item->MengeBestaetigt();
        if ( item->LinkPosNr() > 0 )
        {
            pxOrderItem* ibtpos = (pxOrderItem*)order->ItemList()->At(item->LinkPosNr() - 1);
            if (ibtpos)
            {
                confirmedqty += ibtpos->MengeBestaetigt();
            }
        }

        //if ((d->MENGEBESTAETIGT > item->MengeBestaetigt()) && eIsAux)   /* bei nicht */
        if ((d->MENGEBESTAETIGT > confirmedqty) && eIsAux)   /* bei nicht */
        {                                                    /* ausreichender */
            //d->MENGEBESTAETIGT = item->MengeBestaetigt();  /* Verbundmenge */
            d->MENGEBESTAETIGT = confirmedqty;               /* Verbundmenge */
            d->STATUS = ITEM_STAT_VERBUND_REICHT_NICHT;
        }
    }

    return 0;
}

/************************************************************************************/
/* bucht eine neue Position auf den aktuellen Auftrag mit Rückmeldung der Restmenge */
/************************************************************************************/
int AasrvWriteposition(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItem *item;
    pxOrderItem::BookingType bookingType = GetBuchArt(d->STATUS);
    bool eIsAux = false;

    order->ClearError();
    d->ARTIKEL_NR = d->ARTIKEL_NR;
    if ( d->MENGE && d->FILIALNR1) //Verbundmenge
    {
        //Verbundbuchung
        eIsAux = true;
        item = order->NewOrderItem_08( d->ARTIKEL_NR,
                                       d->MENGEBESTAETIGT,
                                       d->FILIALNR1,
                                       d->MENGENATRA,
                                       d->MENGEBESTELLT,
                                       static_cast<PriceTypeEnum>(d->PREIS_TYP),
                                       bookingType );
    }
    else
    {
        //Normalbuchung
        item = order->NewOrderItem_03( d->ARTIKEL_NR,
                                       d->MENGEBESTAETIGT,
                                       d->MENGENATRA,
                                       d->MENGEBESTELLT,
                                       static_cast<PriceTypeEnum>(d->PREIS_TYP),
                                       bookingType,
                                       pxOrderItem::TypeProductStocked );
    }
    AllgStrCopy(error_msg, order->ErrorMsg(), MAX_ERROR_MSG_AE);
    d->FETCH_REL = order->ErrorNumber();
    if ( ! (order->IsGoodState()) )
    {
        AllgStrCopy(error_msg, order->ErrorMsg(), MAX_ERROR_MSG_AE);
        int err = order->ErrorNumber();
        switch (err)
        {
        case CMSG_ART_QLACK:
            setValuesOnMsgArtQLack(d, order);
            d->FETCH_REL = err;
            return 0;
        case CMSG_AD_NOTPOSSIBLE:
            if (eIsAux)
            {
                d->STATUS = ITEM_STAT_VERBUND_NICHT_MOEGLICH;
                return 0;
            }
            break;
        default:
            break;
        }

        d->FETCH_REL = err;
        d->BESTAND = order->LastStock();
        return getReturnCodeOnError(order);
    }

/* printf("err = %d\n",d->FETCH_REL);fflush(stdout);
printf("error_msg = %s\n",error_msg);fflush(stdout);
printf("error_msgorg = %s\n",order->ErrorMsg());fflush(stdout); */
    //Bemerkung für die Position setzen
    AllgEntfSpaces( d->BEMERKUNG );
    if (strlen( d->BEMERKUNG ) > 0 )
    {
        nString nStr = d->BEMERKUNG;
        item->Bemerkungen( nStr );
        if ( ! (item->IsGoodState()) )
        {
            return handleError(item, error_msg);
        }
    }
    d->FETCH_REL = item->GetError(error_msg);
    AasrvAuftrWerte(d);
    if (item != NULL)
    {
        AasrvPosInf(item,d);
    }
    if ((d->MENGEBESTAETIGT > item->MengeBestaetigt()) && eIsAux)   /* bei nicht */
    {                                                               /* ausreichender */
        d->MENGEBESTAETIGT = item->MengeBestaetigt();               /* Verbundmenge */
        d->STATUS  = ITEM_STAT_VERBUND_REICHT_NICHT;
    }
    d->MENGE = item->MengeVerbund();
    d->FEHLERMENGE = static_cast<short>(item->MengeNachgeliefert());
    return 0;
}

/* versorgt Dispostruktur                 */
static void AasrvWriteDispoStruct(tDISPOITEM  *di, struct AUFPOSBUCH *d)
{
     di->Bezeichnung            = d->ARTIKEL_NAME               ;
     di->Einheit                = d->EINHEIT                    ;
     di->Darreichform           = d->DARREICHFORM               ;
     di->Bemerkungen            = d->BEMERKUNG                  ;
     di->PreisEKApo             = d->PREISEKAPO                 ;
     di->PreisEKGrosso          = d->PREISEKGROSSO              ;
     di->MengeBestellt          = d->MENGEBESTELLT              ;
     di->RabattFestDM           = d->RABATTFESTDM               ;
     di->RabattFest             = d->RABATTFEST                 ;
     di->MWSTSchluessel         = static_cast<pxMWSTSchluessel>(atoi(d->MWSTSCHLUESSEL));
     di->TaxPflichtig           = d->TAXPFLICHTIG[0]    == '0' ? false : true;
     di->Rabattfaehig           = d->RABATTFAEHIG[0]    == '0' ? false : true;
     di->WarenGruppeEigen       = d->WARENGRUPPEEIGEN           ;
     di->UrsprungAuftragnr      = d->URSPRUNGAUFTRAGNR          ;
     di->UrsprungPosnr          = d->URSPRUNGPOSNR              ;
     di->GebuehrBearb           = d->GEBUEHRBEARB               ;
     di->NetPrice               = d->NETPRICE                   ;
     di->Service_No             = d->CODE_TYPE                  ;
     di->KzPriso                = d->KZPRISO[0]                 ;
}

/*****************************************************************************/
/* bucht eine neue Text-Position auf den aktuellen Auftrag                   */
/*****************************************************************************/
int AasrvWritetextpos(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItem *item;
    tDISPOITEM  di;
    pxOrderItem::BookingType bookingType = GetBuchArt(d->STATUS);

    order->ClearError();
    AasrvWriteDispoStruct(&di,d);
    item = order->NewOrderItem_15(di, bookingType);
    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    if ( d->KZAUFGENOMMEN[0] == '1' )
        item->SetArtikelUmgeschluesselt();     // Artikel wurde aufgenommen
    else
        item->ClearArtikelUmgeschluesselt();

    if ( d->KZINFOTEXT[0] == '1' )
        item->SetInfoBelegDrucken();     // Infotext wurde erstellt
    else
        item->ClearInfoBelegDrucken();

//      order->SetProblemClearance();
     AasrvAuftrWerte(d);
    if (item != NULL)
    {
        AasrvPosInf(item, d);
    }

     return 0;
}

/*****************************************************************************/
/* Aendern einer Position                                                    */
/*****************************************************************************/
int AasrvChangepos(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItemList *itemList;
    pxOrderItem *item;
    pxOrderItem::BookingType bookingType = GetBuchArt(d->STATUS);
    short VerbFiliale;

    MessageCodeEnum messageCode = CMSG_OK;

    VerbFiliale = d->FILIALNR1 ? d->FILIALNR1 : cDEFAULT; //FILIALNR1 == 0 bedeutet, dass kein Verbund gebucht wird
    order->ClearError();
    itemList = order->ItemList();
    item = (pxOrderItem *)itemList->At(d->POSNR - 1);
    if (item->Open() == nSTATE_GOOD)
    {
        //Preis für die Position setzen
        if (d->PREISEKAPOFREE != 0)
        {
            item->SetPreisEKApoFree(d->PREISEKAPOFREE);
        }

        item->PreisTyp(static_cast<PriceTypeEnum>(d->PREIS_TYP));
        item->SetDiscountValPctMan(d->DISCOUNTVALPCTMAN);
        item->OrderQuantity(
            d->MENGEBESTAETIGT,
            d->MENGENATRA,
            d->MENGEBESTELLT,
            bookingType,
            bPOST_DEFAULT,
            VerbFiliale,
            d->DISCOUNTVALUEPCT,
            d->MENGEBESTELLTNATRA,
            d->CHARGENNR,
            d->FIXBATCH);
    }
    if ( ! (item->IsGoodState()) )
    {
        switch (item->ErrorNumber())
        {
        case CMSG_ART_QLACK:
            setValuesOnMsgArtQLack(d, order);
            item->Close();
            return 0;
        case CMSG_ORD_CREDITLIMIT_EXHAUSTED:
            //ErrorNumber wird nicht durchgeschlaeust
            setValuesOnMsgOrdCreditLimitExhausted(d, order);
            return 0;
        default:
            return handleErrorAndCloseItem(item, error_msg);
        }
    }

    if(CMSG_OK != messageCode)
    {
        return handleErrorAndCloseItem(item, error_msg);
    }

    //Bemerkung für die Position setzen
    AllgEntfSpaces( d->BEMERKUNG );
    if (strlen( d->BEMERKUNG ) > 0)
    {
        nString nStr = d->BEMERKUNG;
        item->Bemerkungen( nStr );
        if ( ! (item->IsGoodState()) )
        {
            return handleErrorAndCloseItem(item, error_msg);
        }
    }
   // item->Close();
    order->ReCalcValues();
    item->Close();
    AasrvAuftrWerte(d);
    AasrvPosInf(item, d);

    return 0;
}

/*****************************************************************************/
/* Liefert die die moeglichen Verbundmengen pro Filiale                      */
/*****************************************************************************/
int AasrvGetVerbMoegl(struct AUFALTLAGORT *d, char * /*error_msg*/)
{
    static pxVartikelLokalList* stl = NULL;
    static int cursor = 0;

    if (!cursor)
    {
        // check if this type of article can be delivered to the customer concerning transport exclusion on customer tour level
        if( order->Param()->IsUseTourManagerWithTransportExclusion() && !order->getTourAssignmentUtil()->isArticleDeliverableByArticleNo( d->ARTIKEL_NR) )
        {
            return 1;
        }

        stl = new pxVartikelLokalList(ps, order->Param());
        stl->getIBTWarehouseStockList( d->ARTIKEL_NR, order->FilialNr(), order->IDFNr(), order );
        if ( 0 == stl->Entries() )
        {
            delete stl;
            stl = NULL;
            return 1;
        }
    }

    if ( stl )
    {
        if ( stl->Entries() > 0 )
        {
            pxVartikelLokal* entryp = (pxVartikelLokal*)stl->At(cursor);
            if (entryp)
            {
                AllgStrCopy( d->IBTTYPENAME, "", L_AUFALTLAGORT_IBTTYPENAME );
                d->DELIVERYDATEIBT = 0;
                d->DELIVERYTIMEIBT = 0;

                // NLevelIBT -> NLevelIBT-Infos und Touren zu Verbundmöglichkeiten bei Buchung an AE zurückmelden
                if ( order->Param()->IsNlevelIBT() || order->Param()->IsUseTourManagerWithTransportExclusion() )
                {
                    bool deliverable = true;
                    nDate deliverydatetime = entryp->getIBTDeliveryDateTime( order, deliverable );

                    // Ist Lieferung mit Shuttle-Tour möglich?
                    if( order->Param()->IsUseTourManagerWithTransportExclusion() && !deliverable )
                    {
                        ++cursor;
                        pxVartikelLokal* entryp = (pxVartikelLokal*)stl->At(cursor);
                        if( !entryp )
                        {
                            delete stl;
                            stl = NULL;
                            cursor = 0;
                            return 1;
                        }
                    }

                    if ( TourUtil::getNullDate() != deliverydatetime )
                    {
                        d->DELIVERYDATEIBT = deliverydatetime.GetYYYYMMDD();
                        d->DELIVERYTIMEIBT = TourUtil::getLongTime( deliverydatetime );
                    }

                    pxIBTType* ibtType = ps->IBTTypeList()->Find(entryp->getNLevelIBTTypeId());
                    if (NULL != ibtType)
                    {
                        AllgStrCopy(d->IBTTYPENAME, ibtType->Name() , L_AUFALTLAGORT_IBTTYPENAME);
                    }
                }

                d->FILIALNR = entryp->FilialNr();
                d->BESTAND  = entryp->Bestand();

                ++cursor;
                return 0;
            }
        }
        delete stl;
        stl = NULL;
        cursor = 0;
    }

    if ( cursor )
    {
        cursor = 0;
    }
    return 1;
}

/*****************************************************************************/
/* Liefert die die moeglichen Verbundmengen pro Filiale                      */
/*****************************************************************************/
int AasrvGetIBTStockLevel(struct AUFALTLAGORT *d, char * /*error_msg*/) // NLevelIBT -> NLevelIBT-Infos für Artikel-Info in AE (F11)
{
    static pxVartikelLokalList* stl = NULL;
    static int cursor = 0;

    if (!cursor)
    {
        stl = new pxVartikelLokalList(ps, ps->getOrderEntryParam( d->FILIALNR ));
        stl->getIBTWarehouseStockListGeneral( d->ARTIKEL_NR, d->FILIALNR );
        if ( 0 == stl->Entries() )
        {
            delete stl;
            stl = NULL;
            return 1;
        }
    }

    if ( stl )
    {
        if ( stl->Entries() > 0 )
        {
            pxVartikelLokal* entryp = (pxVartikelLokal *)stl->At(cursor);
            if (entryp)
            {
                d->FILIALNR = entryp->FilialNr();
                d->BESTAND  = entryp->Bestand();
                AllgStrCopy( d->IBTTYPENAME, "", L_AUFALTLAGORT_IBTTYPENAME );
                d->DELIVERYDATEIBT = 0;
                d->DELIVERYTIMEIBT = entryp->getIBTQtyAvailabilityPercentage(); // 0 = Zeitart nicht aktiv; 1 = Zeitart aktiv!
                pxIBTType* ibtType = ps->IBTTypeList()->Find(entryp->getNLevelIBTTypeId());
                if (NULL != ibtType)
                {
                    AllgStrCopy(d->IBTTYPENAME, ibtType->Name() , L_AUFALTLAGORT_IBTTYPENAME);
                }
                ++cursor;
                return 0;
            }
        }
        delete stl;
        stl = NULL;
        cursor = 0;
    }

    if ( cursor )
    {
        cursor = 0;
    }
    return 1;
}

/*****************************************************************************/
/* Liefert moeglichen Verbund                                                 */
/*****************************************************************************/
int AasrvCheckIBTStockLevel(struct AUFALTLAGORT *d, char * /*error_msg*/) // NLevelIBT -> NLevelIBT-Infos für Verbund möglich Anzeige
{
    static pxVartikelLokalList* stl = NULL;
    static int cursor = 0;

    if (!cursor)
    {
        stl = new pxVartikelLokalList(ps, ps->getOrderEntryParam( d->FILIALNR ));
        stl->getIBTWarehouseStockListGeneral( d->ARTIKEL_NR, d->FILIALNR );
        if ( 0 == stl->Entries() )
        {
            delete stl;
            stl = NULL;
            return 1;
        }
    }

    if ( stl )
    {
        if ( stl->Entries() > 0 )
        {
            for(;;)
            {
                pxVartikelLokal* entryp = (pxVartikelLokal *)stl->At(cursor);
                if (entryp)
                {
                    d->FILIALNR = entryp->FilialNr();
                    d->BESTAND  = entryp->Bestand();
                    AllgStrCopy( d->IBTTYPENAME, "", L_AUFALTLAGORT_IBTTYPENAME );
                    d->DELIVERYDATEIBT = 0;
                    d->DELIVERYTIMEIBT = entryp->getIBTQtyAvailabilityPercentage(); // 0 = Zeitart nicht aktiv; 1 = Zeitart aktiv!
                    pxIBTType* ibtType = ps->IBTTypeList()->Find(entryp->getNLevelIBTTypeId());
                    if (NULL != ibtType)
                    {
                        AllgStrCopy(d->IBTTYPENAME, ibtType->Name() , L_AUFALTLAGORT_IBTTYPENAME);
                    }
                    ++cursor;
                    if(d->DELIVERYTIMEIBT == 0) continue;   // nur aktive
                    if(d->BESTAND == 0) continue;   // und nur mit Bestand
                    delete stl;
                    stl = NULL;
                    cursor = 0;
                    return 0;
                }
                delete stl;
                stl = NULL;
                cursor = 0;
                return 1;
            }
        }
        delete stl;
        stl = NULL;
        cursor = 0;
    }

    if ( cursor )
    {
        cursor = 0;
    }
    return 1;
}

/*****************************************************************************/
/* Aendern einer Text-Position                                               */
/*****************************************************************************/
int AasrvChangetextpos(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItemList *itemList;
    pxOrderItem *item;
    pxOrderItem::BookingType bookingType = GetBuchArt(d->STATUS);

    order->ClearError();
    itemList = order->ItemList();
    item = (pxOrderItem *)itemList->At(d->POSNR - 1);
    if (item->Open() == nSTATE_GOOD)
    {
        if ( item->IsDispoItem() )
        {
            tDISPOITEM di;
            item->DispoGet(di);
            d->CODE_TYPE =  di.Service_No;
            AasrvWriteDispoStruct(&di, d);
            if ( d->KZAUFGENOMMEN[0] == '1' )
                item->SetArtikelUmgeschluesselt();     // Artikel wurde aufgenommen
            else
                item->ClearArtikelUmgeschluesselt();

            if ( d->KZINFOTEXT[0] == '1' )
                item->SetInfoBelegDrucken();     // Infotext wurde erstellt
            else
                item->ClearInfoBelegDrucken();
            item->DispoSet(di, bookingType);
        }
        else
        {
            AllgStrCopy(error_msg, TXT_KEINE_TXT_POS, MAX_ERROR_MSG_AE);
            return -2;
        }
    }
    if ( ! (item->IsGoodState()) )
    {
        return handleErrorAndCloseItem(item, error_msg);
    }
    item->Close();
    order->ReCalcValues();
    AasrvAuftrWerte(d);
    AasrvPosInf(item, d);

    return 0;
}

/*****************************************************************************/
/* Liefert eine Positionen des aktuellen Auftrages                           */
/*****************************************************************************/
int AasrvInfposnr(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItem* item = (pxOrderItem *)order->ItemList()->At(d->POSNR - 1);
    if (item)
    {
        AasrvPosInf(item, d);
        return 0;
    }
    else
    {
        AllgStrCopy(error_msg, TXT_KEINE_POS, MAX_ERROR_MSG_AE);
        return -2;
    }
}

/*****************************************************************************/
/* Liefert die Positionen des aktuellen Auftrages                            */
/*****************************************************************************/
int AasrvSelpos(struct AUFPOSBUCH *d, char * /*error_msg*/)
{
    static int anz = 0;

    if (!anz)
    {
        oItemList = order->ItemList();
    }
    pxOrderItem* item = (pxOrderItem*)oItemList->At(anz);
    if (item)
    {
        AasrvPosInf(item,d);
        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*****************************************************************************/
/* Liefert die Positionen des aktuellen Auftrages                            */
/*****************************************************************************/
int AasrvSeldeforalphapos(struct AUFPOSBUCH *d, char * /*error_msg*/)
{
    static int anz = 0;

    for(;;)
    {
        if (!anz)
        {
            oItemList = order->ItemList();
        }
        pxOrderItem* item = (pxOrderItem*)oItemList->At(anz);
        if (item)
        {
            ++anz;
            if ( //Reihenfolge ist wichtig
                 item->MengeVerbund() != 0       ||
                 item->IsManualMaintenance() ||  //d->KZNACHBEARB[0]     == '1'
                 item->IsDispoItem()                     ||      //d->KZFREITEXT[0]      == '1'
                 item->IsQStateLimitCheck()      ||      //d->KZLIMITCHK[0]      == '1'
                 ( !(item->IsQStateGood()) || !(item->IsArtStateGood()))
                 //d->KZDEFEKT[0]        == '1'
                 )
            {
                AasrvPosInf(item, d);
                return 0;
            }
            else
                continue;
        }
        else
        {
            anz = 0;
            return 1;
        }
    }
}

/*****************************************************************************/
/* Liefert die Positionen des InfoAuftrages                                  */
/*****************************************************************************/
int AasrvSelposInfAuf(struct AUFPOSBUCH *d,char * /*error_msg*/)
{
    static int anz = 0;

    if (!anz)
    {
        oItemList = InfoOrder->ItemList();
    }
    pxOrderItem* item = (pxOrderItem *)oItemList->At(anz);
    if (item)
    {
        AasrvPosInf(item, d);
        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*****************************************************************************/
/* Liefert die Kopf- bzw. Fusszeilen eines Auftrages                         */
/*****************************************************************************/
int AasrvSelKopfZlnAuf(struct AUFTEXTE *d, char * /*error_msg*/)
{
    static short anz = 0;
    pxTextDoc *doc;

    switch (d->BEMERKUNGSART)
    {
    case AUF_TEXT_KOPF:
        doc = order->HeadText();
        break;
    case AUF_TEXT_KOPF_INFO:
        doc = InfoOrder->HeadText();
        break;
    case AUF_TEXT_FUSS:
        doc = order->TailText();
        break;
    case AUF_TEXT_FUSS_INFO:
        doc = InfoOrder->TailText();
        break;
    default:
        anz = 0;
        return 1;
    }

    pxTextLine* line = (pxTextLine*)doc->At(anz);
    if (line)
    {
        AllgStrCopy(d->BEMERKUNGEN, line->Text(), L_AUFTEXTE_BEMERKUNGEN);
        d->BEMERKUNGSNR = anz;
        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*****************************************************************************/
/* Fügt eine Kopf bzw. Fusszeile ein                                         */
/*****************************************************************************/
int AasrvInsKopfZlnAuf(struct AUFTEXTE *d, char * /*error_msg*/)
{
    pxTextDoc *doc = (d->BEMERKUNGSART == AUF_TEXT_KOPF) ? order->HeadText() : order->TailText();
    doc->NewLine(d->BEMERKUNGEN);
    return 0;
}

/*****************************************************************************/
/* Loescht eine Kopf bzw. Fusszeile                                          */
/*****************************************************************************/
int AasrvDelKopfZlnAuf(struct AUFTEXTE *d,char * /*error_msg*/)
{
    pxTextDoc *doc = (d->BEMERKUNGSART == AUF_TEXT_KOPF) ? order->HeadText() : order->TailText();
    doc->RemoveAt(d->BEMERKUNGSNR);
    return 0;
}

/*****************************************************************************/
/* entlockt gelockte Auftraege lt. Auftragnr (in key)                        */
/*****************************************************************************/
int AasrvUnlock(struct LOCKMAN *d, char *error_msg)
{
    int ret = 1;
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "AasrvUnlock");

    libLockManager::ILockManagerPtr lockManager = ps->getCustomerOrderLockManager();
    libLockManager::IKeyPtr         key         = ps->createCustomerOrderLockKey( atoi((char*)d->RESOURCEKEY) );

    try
    {
        lockManager->forceUnlock( *key );
        sprintf(error_msg, "Auftrag entsperrt: %6.6s durch %4.4s", d->RESOURCEKEY, d->NAMEWORKSTATION);
        BLOG_WARN(libcsc::LoggerPool::getLoggerSession(),error_msg);
        ret = 0;
    }
    catch( ... )
    {
        AllgStrCopy(error_msg, TXT_SYSTEM_ERROR, MAX_ERROR_MSG_AE);
        ret = -2;
    }

    lockManager->eraseStaleLocks();

    return ret;
}

/*****************************************************************************/
/* Wegsetzen Kennzeichen Nachbearbeitung                                     */
/*****************************************************************************/
int AasrvChangeKzNachBearb(struct AUFPOSNACH *d, char *error_msg)
{
//    pxOrderItemList *itemList;

    order->ClearError();
//    itemList = order->ItemList();
    pxOrderItem* item = (pxOrderItem*)order->ItemList()->At(d->POSNR - 1);
    if (item)
    {
        item->Open();
        if (d->KZNACHBEARB[0] == '0')
            item->ClearManualMaintenance();
        else
            item->SetManualMaintenance();
        if (d->KZAUFGENOMMEN[0] == '0')
            item->ClearArtikelUmgeschluesselt();
        else
            item->SetArtikelUmgeschluesselt();
        item->Close();
        return 0;
    }
    else
    {
        AllgStrCopy(error_msg, TXT_KEINE_POS, MAX_ERROR_MSG_AE);
        return -2;
    }
}

/*****************************************************************************/
/* Setzen Kennzeichen direkter Ausdruck                                      */
/*****************************************************************************/
int AasrvSetprintdirect(struct AUFTRAG * /*d*/, char *error_msg)
{
    order->ClearError();
    order->SetImmediatePrint();
    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    return 0;
}

/****************************************************************************************/
/* bucht eine neue Position aufgrund einer Nachlieferposition auf den aktuellen Auftrag */
/****************************************************************************************/
int AasrvWriteposNL(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItem *item = NULL;
    pxOrderItem::BookingType bookingType = GetBuchArt(d->STATUS);
    pxDeliveryPos delpos(ps);
    order->ClearError();
    d->ARTIKEL_NR = d->ARTIKEL_NR;
    delpos.SetArtikelNr(d->ARTIKEL_NR);
    delpos.SetMenge(d->MENGEBESTELLT);
    delpos.SetPreisEKApoNetto((nMoney)d->PREISEKGROSSO);
    delpos.SetDeliveryPosTyp((pxVerbund::subsequentDelivery::pxDelPosTyp) d->POSTYP);
    delpos.SetMengeBestellt(d->MENGEGELIEFERT);
    delpos.SetPreisTyp(static_cast<PriceTypeEnum>(d->PREIS_TYP));
    delpos.SetDiscountValuePct(d->DISCOUNTVALUEPCT);

    item = order->NewOrderItem_16( &delpos, bookingType );
    if ( ! (order->IsGoodState()) )
    {
/*    Menge nicht ausreichend wg. Kontigent   */
        switch (order->ErrorNumber())
        {
        case CMSG_ART_QLACK:
            d->BESTAND = order->LastStock();
            d->STATUS  = ITEM_STAT_KEINE_MENGE;
            return 0;
        case CMSG_ITM_ARTQUOTA_EXEEDED:
            d->BESTAND = order->RestQuota(); // Hier Restkontigent
            d->STATUS  = ITEM_STAT_NACHLIEFUPD;
            return 0;
        default:
            return handleError(order, error_msg);
        }
    }
    if (item != NULL)
    {
        item->SetArticleCodeValues(d->CODE_TYPE, d->ARTICLE_CODE);
    }

    //Bemerkung für die Position setzen
    AllgEntfSpaces( d->BEMERKUNG );
    if (strlen( d->BEMERKUNG ) > 0 )
    {
        nString nStr = d->BEMERKUNG;
        item->Bemerkungen( nStr );
        if ( ! (item->IsGoodState()) )
        {
            return handleError(item, error_msg);
        }
    }
    AasrvAuftrWerte(d);
    if (item != NULL)
    {
        AasrvPosInf(item, d);
    }
    return 0;
}

/*****************************************************************************/
/* Setzen Datum verzögerte Auslieferung                                      */
/*****************************************************************************/
int AasrvSetdelayeddate(struct AUFTRAG *d, char *error_msg)
{
    order->SetDatumAuslieferung(d->DATUMAUSLIEFERUNG);
    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    return 0;
}

/*****************************************************************************/
/* Deaktivieren verzögerte Auslieferung                                      */
/*****************************************************************************/
int AasrvSetNoSeperate(struct AUFTRAG * d, char * /*error_msg*/)
{
    bool bSeparate = true;
    if(d->STATUS == 1) bSeparate = false;
    order->Customer()->SetNoSeparate(bSeparate);
    order->setNoDelayedDelivery(bSeparate);
    return 0;
}

/*****************************************************************************/
/* Prüfen Referenznummer vorhanden                                           */
/*****************************************************************************/
int AasrvCheckReference(struct AUFTRAG *d, char *error_msg)
{
    int rc;
    strncpy(error_msg, d->BEMERKUNGEN, 9);
    d->FEHLER = 0;
    if ( (rc = pxCheckReferenceNr(ps, d->VERTRIEBSZENTRUMNR, d->KUNDENNR, error_msg )) != 0)
    {
        d->FEHLER = rc*(-1);
    }
    return 0;
}

/*****************************************************************************/
/* Schreiben Referenznummer                                                  */
/*****************************************************************************/
int AasrvInsertReference(struct AUFTRAG *d,char *error_msg)
{
    int rc;
    strncpy(error_msg, d->BEMERKUNGEN, 9);
    d->FEHLER = 0;
    if ( (rc = pxInsertReferenceNr(ps, d->VERTRIEBSZENTRUMNR, d->KUNDENNR, error_msg )) != 0)
    {
        d->FEHLER = rc*(-1);
    }
    return 0;
}

/*****************************************************************************/
/* Liefert mögliche Touren für den Auftrag                                   */
/*****************************************************************************/
int AasrvGetWeektouren(kndtourenS *d, char * /*error_msg*/)
{
    static int anz = 0;
    pxCustRouteWeekList   *rwl = NULL;
    rwl = order->RouteWeekList(d->KDAUFTRAGART);
    if (rwl == NULL)
    {
        anz = 0;
        return 1;
    }
    pxCustRouteWeek* route = (pxCustRouteWeek*)rwl->At(anz);
    if (route)
    {
        AllgStrCopy(d->TOURID,route->TourId(), L_KNDTOUREN_TOURID);
        d->WEEKDAY = route->WeekDay();
        d->FAHRTZEIT = static_cast<short>(route->FahrtZeit());
        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*****************************************************************************/
/* Berechnen proforma Lieferwert                                             */
/*****************************************************************************/
int AasrvProforma(struct AUFPOSBUCH *d, char * /*error_msg*/)
{
    static int anz = 0;
//  static int maxanz = 0;

    if (ps->isBulgaria())
    {
        if (!anz)
        {
            order->ProformaInvoice(d->PREIS_TYP);
            oItemList = order->ItemListProforma();
        }
        pxOrderItem* item = (pxOrderItem*)oItemList->At(anz);
        if (item)
        {
            AasrvPosInf(item, d);
            d->DISCOUNTVALUEPCT =   item->DiscountValPctProforma();
            setAuftragLieferZeilen(d, order);
            setOrderValues(d, order);
            ++anz;
            return 0;
        }
        anz = 0;
        return 1;
    }
    order->ProformaInvoice();
    setAuftragLieferZeilen(d, order);
    setOrderValues(d, order);
    return 0;
}

/*****************************************************************************/
/* Ausgeben Auftragswerte                                                    */
/*****************************************************************************/
int AasrvGetOrderVals(ordervaluesS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static OrderTaxValueMap::const_iterator it;

    if (!anz)
    {
        it = order->OrdTaxValues()->GetOrdTaxValueMap().begin();
    }
    if (it != order->OrdTaxValues()->GetOrdTaxValueMap().end())
    {
        d->TAXLEVEL = (*it).second.TaxLevel;
        d->SALESTAXRATE = (*it).second.SalesTaxRate;
        d->ORDVALNET = (*it).second.ShipValue;
        d->ORDVALTAX = (*it).second.TaxValue;
        ++anz;
        ++it;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*************************************************************************/
// AasrvSetBTMLicense
/*************************************************************************/
int AasrvSetBTMLicense(struct AUFTRAG *d, char * /*error_msg*/)
{
    nString btmlicense;             // ein String-Objekt
    btmlicense = d->BTMFORMULARNR;
    order->SetBTMFormularNr(d->DATUMBTM, btmlicense);
    return 0;
}

/*************************************************************************/
// AasrvSetROParam
/*************************************************************************/
int AasrvSetROParam(rabattorderS *d, char *error_msg)
{
    int rc = 0;
    order->CancelRebateOrder();
    order->SetRODateFrom(d->DATEFROM);
    order->SetRODateTo(d->DATETO);
    order->SetROChain(d->SWCHAIN);
    rc = order->SyncCstDiscAccVse();
    if (rc == 0)
    {
        AllgStrCopy(error_msg, order->ErrorMsg(), MAX_ERROR_MSG_AE);
        return -2;
    }
    return 0;
}

/*************************************************************************/
// AasrvGetROMembers
/*************************************************************************/
int AasrvGetROMembers(cstdiscaccS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = 0;

    static pxCstDiscAcc *entryp = NULL;
    static pxCstDiscAccList* accliste = NULL;
    if (!anz)
    {
        accliste = order->CstDiscountAccount();
        if (accliste == NULL)    // keine Liste vorhanden
            return 1;
        maxanz = accliste->Entries();
        if (!maxanz) // keine Eintraege vorhanden
            return 1;
    }
    if (anz >= maxanz)   // Ende der Liste
    {
        anz = 0;
        entryp = NULL;
        return 1;
    }
    entryp = (pxCstDiscAcc*)(accliste->At(anz));
    if (entryp)
    {
        d->BRANCHNO = entryp->BranchNo();
        d->CUSTOMERNO = entryp->CustomerNo();
        d->MAINCSTNO = entryp->MainCstNo();
        d->BALANCE = entryp->Balance();
        d->DATE = entryp->Date().GetYYYYMMDD();
        strncpy(d->INVOICENUMBER, entryp->InvoiceNumber(), L_CSTDISCACC_INVOICENUMBER);
        d->INVOICEAMOUNT = entryp->InvoiceAmount();
        strncpy(d->VOUCHERTYP, entryp->VoucherTyp(), L_CSTDISCACC_VOUCHERTYP);
        d->PREIS_TYP = static_cast<short>(entryp->PreisTyp());
        d->PRIORITY = entryp->Priority();
        d->INVOICEPAID = entryp->InvoicePaid();
        d->PAYMENTARGET = entryp->PaymentTarget();
        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        entryp = NULL;
        return 1;
    }
}

/*************************************************************************/
// AasrvChangeROMembers
/*************************************************************************/
int AasrvChangeROMembers(cstdiscaccS *d, char * /*error_msg*/)
{
    if (d->UPD_FLAG[0] == '0')
    {
        order->ChangeUsageCstDiscAcc( d->BRANCHNO,
                                      d->CUSTOMERNO,
                                      d->DATE,
                                      d->INVOICENUMBER,
                                      d->VOUCHERTYP );
    }
    else
    {
        order->ChangePriorityCstDiscAcc( d->BRANCHNO,
                                         d->CUSTOMERNO,
                                         d->DATE,
                                         d->INVOICENUMBER,
                                         d->VOUCHERTYP,
                                         d->PRIORITY );
    }
    return 0;
}

/***********************************************************************************/
/* berechnet eine neue Position im aktuellen Auftrag mit Rückmeldung der Restmenge */
/***********************************************************************************/
int AasrvCalcpos(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItem *item;
    pxOrderItem::BookingType bookingType = GetBuchArt(d->STATUS);
    int bookingFlags = bPOST_DEFAULT;
    if (d->STATUS == ITEM_STAT_IGNORE_PRICELIMIT) { bookingFlags |= bPOST_IGNORE_PRICELIMIT; }

    order->ClearError();
    d->ARTIKEL_NR = d->ARTIKEL_NR;
    //Normalbuchung
    item = order->CalcOrderItem( d->ARTIKEL_NR,
                                 d->MENGEBESTAETIGT,
                                 d->MENGENATRA,
                                 d->MENGEBESTELLT,
                                 static_cast<PriceTypeEnum>(d->PREIS_TYP),
                                 bookingType,
                                 pxOrderItem::TypeProductStocked,
                                 bookingFlags);
    AllgStrCopy(error_msg, order->ErrorMsg(), MAX_ERROR_MSG_AE);
    d->FETCH_REL = order->ErrorNumber();
    if ( ! (order->IsGoodState()) )
    {
        AllgStrCopy(error_msg, order->ErrorMsg(), MAX_ERROR_MSG_AE);
        int err = order->ErrorNumber();
        switch (err)
        {
        case CMSG_ART_QLACK:
            setValuesOnMsgArtQLack(d, order);
            d->FETCH_REL = err;
            return 0;
        case CMSG_ORD_CREDITLIMIT_EXHAUSTED:
            setValuesOnMsgOrdCreditLimitExhausted(d, order);
            return 0;
        case CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE: // fall through
            d->STATUS = ITEM_STAT_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE;
            return 0;

        case CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE: // fall through
            d->STATUS = ITEM_STAT_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE;
            return 0;

        case CMSG_ITM_PRICE_LIMIT_PRODUCT_PRICE_DELETION: // fall through
            if (order->Customer()->KdGruppe() == "06")
            {
                d->STATUS = ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION_06;
            }
            else
            {
                d->STATUS = ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION;
            }
            return 0;

        case CMSG_ITM_PRICE_LIMIT_MWP_EXCEEDANCE:
            // open ??!!??
            d->STATUS = ITEM_STAT_LIMIT_MWP_EXCEEDANCE;
            return 0;
        default:
            d->FETCH_REL = err;
            d->BESTAND = order->LastStock();
            return getReturnCodeOnError(order);
        }
    }

    if (d->DISCOUNTVALPCTMAN > 0)
    {
        item->bookDiscountValPctManProforma(d->DISCOUNTVALPCTMAN);
        //item->SetDiscountValPctMan(d->DISCOUNTVALPCTMAN);
        //item->ItemUpdateDiscountList();
    }

    d->PREISFAKTUR = item->InvoiceValue();  // Rabattierter Preis
    d->PREISVKAPO = item->GetCalcAvp();
    d->FETCH_REL = item->GetError(error_msg);
    return 0;
}

/*****************************************************************************/
/* ermitteln Rabatte lt Kaskade */
/*****************************************************************************/
int AasrvGetRebates( discountanzS *d, char * /*error_msg*/)
{
    static int anz = 0;

    int qty = (d->BASEQTY > 0) ? d->BASEQTY : 1000;

    if (ps->getOrderEntryParam(d->BRANCHNO)->IsUseNewDiscountCalc())
    {
        try
        {
            static libcsc::discount::IDiscountCollectionFinderPtr discountCollectionFinder( (getSession().getDiscountCollectionFinder()) );
            static libcsc::discount::DiscountBaseValueList::const_iterator discountIterator;

            if (0 == anz)
            {
                discountCollectionFinder->clear();
                const libcsc::discount::DiscountBaseValueList& coll = discountCollectionFinder->find(order, d->ARTICLENO, qty);
                if (coll.empty())
                {
                    anz = 0;
                    return 1;
                }
                discountIterator = discountCollectionFinder->get().begin();
                anz = 1;
            }

            const libcsc::discount::DiscountBaseValueList& coll = discountCollectionFinder->get();
            if (coll.end() == discountIterator)
            {
                anz = 0;
                return 1;
            }

            d->BRANCHNO = (*discountIterator)->getBranchno();
            d->ARTICLENO = (*discountIterator)->getArticleNo();
            d->DISCOUNTGRPNO = (*discountIterator)->getDiscountGrpNo();
            strncpy(d->PHARMACYGROUPID, (*discountIterator)->getPharmacyGrpId().c_str(), L_DISCOUNTANZ_PHARMACYGROUPID);
            d->CUSTOMERNO = (*discountIterator)->getCustomerNo();
            d->GRPDISCOUNTTYP = static_cast<short>((*discountIterator)->getGrpDiscountType());
            d->DATEFROM = (*discountIterator)->getDateFrom().getDate();
            d->DATETO = (*discountIterator)->getDateTo().getDate();
            d->BASEQTY = (*discountIterator)->getBaseQty();
            d->DISCOUNTSPEC = static_cast<short>((*discountIterator)->getDiscountSpec());
            d->DISCOUNTTYPE = static_cast<short>((*discountIterator)->getDiscountType());
            d->DISCOUNTQTY = static_cast<short>((*discountIterator)->getDiscountQty());
            d->DISCOUNTVALUEPCT = (*discountIterator)->getDiscountValuePct().toFloat64();
            d->DISCOUNTQTYPCT = (*discountIterator)->getDiscountQtyPct().toFloat64();
            d->SURCHARGEPCT = (*discountIterator)->getSurchargePct().toFloat64();
            //strncpy(d->PHARMGRPEXCLUDED, (*discountIterator)->PharmGrpExcluded(), L_DISCOUNTANZ_PHARMGRPEXCLUDED); // ==> Ask Ronni
            d->FIXEDPRICE = (*discountIterator)->getFixedPrice().toFloat64();
            d->REFUNDPCT = (*discountIterator)->getRefundPct().toFloat64();
            d->INTERNALDISCOUNT[0] = (*discountIterator)->getInternalDiscount().c_str()[0];
            d->DISCOUNTARTICLE = (*discountIterator)->getDiscountArticle();
            d->BASE_VALUE = (*discountIterator)->getBaseValue().toFloat64();
            d->BASE_MULT_STD_QTY = (*discountIterator)->getBaseMultStdQty();
            d->NO_MULTIPLE_QTY[0] = (*discountIterator)->getNoMultipleQty().c_str()[0];
            d->FIXEDDISCOUNTVALUE = (*discountIterator)->getFixedDiscountVal().toFloat64();
            d->MANUFACTURERNO = (*discountIterator)->getManufacturerNo();
            d->ARTCATEGORYNO = (*discountIterator)->getArtCategoryNo();
            d->PAYMENTTARGETNO = static_cast<short>((*discountIterator)->getPaymentTargetNo());
            d->GROSSPROFITPCT = (*discountIterator)->getGrossProfitPct().toFloat64();
            d->ADDONDISCOUNTOK[0] = (*discountIterator)->getAddOnDiscountOk().c_str()[0];
            d->PAYMENTTERMTYPE[0] = (*discountIterator)->getPaymentTermType().c_str()[0];
            d->TARGETQTY = (*discountIterator)->getTargetQty();
            d->EXCEEDANCEPCT = (*discountIterator)->getExceedancePct().toFloat64();
            d->ARTICLE_NO_PACK = (*discountIterator)->getArticleNoPack();
            d->PROMOTION_NO = (*discountIterator)->getPromotionNo();
            d->REFUNDVALUE = (*discountIterator)->getRefundValue().toFloat64();

            ++discountIterator;

            return 0;
        }
        catch (::libcsc::exceptions::InvalidParameterException& ex )
        {
            ex;
            return 1;
        }
    }
    else
    {
        static int maxanz = 0;
        static pxArtDiscountInfo* ArtDisc = NULL;
        static pxDiscountList* dlist = NULL;
        static pxDiscount*   entryp = NULL;

        if (!anz)
        {
            ArtDisc = new pxArtDiscountInfo(ps);
            dlist = ArtDisc->GetDiscountList(d->BRANCHNO, d->CUSTOMERNO, d->ARTICLENO, static_cast<PriceTypeEnum>(d->PREIS_TYP), qty);
            if (dlist == NULL)
            {
                anz = 0;
                delete ArtDisc;
                return 1;
            }
            maxanz = dlist->Entries();
        }

        if (anz >= maxanz)   // Ende der Liste
        {
            anz = 0;
            delete ArtDisc;
            return 1;
        }

        entryp = (pxDiscount*)(dlist->At(anz));
        if (entryp)
        {
            d->BRANCHNO = entryp->BranchNo();
            d->ARTICLENO = entryp->ArticleNo();
            d->DISCOUNTGRPNO = entryp->DiscountGrpNo();
            strncpy(d->PHARMACYGROUPID, entryp->PharmacyGroupId(), L_DISCOUNTANZ_PHARMACYGROUPID);
            d->CUSTOMERNO = entryp->CustomerNo();
            d->GRPDISCOUNTTYP = entryp->GrpDiscountTyp();
            d->DATEFROM = entryp->DateFrom().GetYYYYMMDD();
            d->DATETO = entryp->DateTo().GetYYYYMMDD();
            d->BASEQTY = entryp->BaseQty();
            d->DISCOUNTSPEC = entryp->DiscountSpec();
            d->DISCOUNTTYPE = entryp->DiscountType();
            d->DISCOUNTQTY = entryp->DiscountQty();
            d->DISCOUNTVALUEPCT = entryp->DiscountValuePct();
            d->DISCOUNTQTYPCT = entryp->DiscountQtyPct();
            d->SURCHARGEPCT = entryp->SurchargePct();
            strncpy(d->PHARMGRPEXCLUDED, entryp->PharmGrpExcluded(), L_DISCOUNTANZ_PHARMGRPEXCLUDED);
            d->FIXEDPRICE = entryp->FixedPrice();
            d->REFUNDPCT = entryp->RefundPct();
            d->INTERNALDISCOUNT[0] = entryp->InternalDiscount();
            d->DISCOUNTARTICLE = entryp->DiscountArticle();
            d->BASE_VALUE = entryp->BaseValue();
            d->BASE_MULT_STD_QTY = entryp->BaseMultSTDQty();
            d->NO_MULTIPLE_QTY[0] = entryp->NoMultipleQty();
            d->FIXEDDISCOUNTVALUE = entryp->FixedDiscountValue();
            d->MANUFACTURERNO = entryp->ManufacturerNo();
            d->ARTCATEGORYNO = entryp->ArtCategoryNo();
            d->PAYMENTTARGETNO = entryp->PaymentTargetNo();
            d->GROSSPROFITPCT = entryp->GrossProfitPct();
            d->ADDONDISCOUNTOK[0] = entryp->AddonDiscountOk();
            d->PAYMENTTERMTYPE[0] = entryp->PaymentTermType();
            d->TARGETQTY = entryp->TargetQty();
            d->EXCEEDANCEPCT = entryp->ExceedancePct();
            d->ARTICLE_NO_PACK = entryp->ArticleNoPack();
            d->PROMOTION_NO = entryp->PromotionNo();
            d->REFUNDVALUE = entryp->RefundValue();
            ++anz;
            return 0;
        }
        else
        {
            anz = 0;
            delete ArtDisc;
            return 1;
        }
    }
}

/*****************************************************************************/
/* ermitteln aktuelle Promotionen */
/*****************************************************************************/
int AasrvGetPromotions( discountanzS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = 0;
    static pxDiscountList* dlist = NULL;
    static pxDiscount*   entryp = NULL;
    static pxArtDiscountInfo* ArtDisc = NULL;
    if (!anz)
    {
        ArtDisc = new pxArtDiscountInfo(ps);
        dlist = ArtDisc->GetPromotionList(d->BRANCHNO, d->CUSTOMERNO, d->ARTICLENO, static_cast<PriceTypeEnum>(d->PREIS_TYP));
        if (dlist == NULL)
        {
            anz = 0;
            delete ArtDisc;
            return 1;
        }
        maxanz = dlist->Entries();
    }
    if (anz >= maxanz)   // Ende der Liste
    {
        anz = 0;
        delete ArtDisc;
        return 1;
    }
    entryp = (pxDiscount*)(dlist->At(anz));
    if (entryp)
    {
        d->BRANCHNO = entryp->BranchNo();
        d->ARTICLENO = entryp->ArticleNo();
        d->DISCOUNTGRPNO = entryp->DiscountGrpNo();
        strncpy(d->PHARMACYGROUPID, entryp->PharmacyGroupId(), L_DISCOUNTANZ_PHARMACYGROUPID);
        d->CUSTOMERNO = entryp->CustomerNo();
        d->GRPDISCOUNTTYP = entryp->GrpDiscountTyp();
        d->DATEFROM = entryp->DateFrom().GetYYYYMMDD();
        d->DATETO = entryp->DateTo().GetYYYYMMDD();
        d->BASEQTY = entryp->BaseQty();
        d->DISCOUNTSPEC = entryp->DiscountSpec();
        d->DISCOUNTTYPE = entryp->DiscountType();
        d->DISCOUNTQTY = entryp->DiscountQty();
        d->DISCOUNTVALUEPCT = entryp->DiscountValuePct();
        d->DISCOUNTQTYPCT = entryp->DiscountQtyPct();
        d->SURCHARGEPCT = entryp->SurchargePct();
        strncpy(d->PHARMGRPEXCLUDED, entryp->PharmGrpExcluded(), L_DISCOUNTANZ_PHARMGRPEXCLUDED);
        d->FIXEDPRICE = entryp->FixedPrice();
        d->REFUNDPCT = entryp->RefundPct();
        d->INTERNALDISCOUNT[0] = entryp->InternalDiscount();
        d->DISCOUNTARTICLE = entryp->DiscountArticle();
        d->BASE_VALUE = entryp->BaseValue();
        d->BASE_MULT_STD_QTY = entryp->BaseMultSTDQty();
        d->NO_MULTIPLE_QTY[0] = entryp->NoMultipleQty();
        d->FIXEDDISCOUNTVALUE = entryp->FixedDiscountValue();
        d->MANUFACTURERNO = entryp->ManufacturerNo();
        d->ARTCATEGORYNO = entryp->ArtCategoryNo();
        d->PAYMENTTARGETNO = entryp->PaymentTargetNo();
        d->GROSSPROFITPCT = entryp->GrossProfitPct();
        d->ADDONDISCOUNTOK[0] = entryp->AddonDiscountOk();
        d->PAYMENTTERMTYPE[0] = entryp->PaymentTermType();
        d->TARGETQTY = entryp->TargetQty();
        d->EXCEEDANCEPCT = entryp->ExceedancePct();
        d->ARTICLE_NO_PACK = entryp->ArticleNoPack();
        d->PROMOTION_NO = entryp->PromotionNo();
        d->REFUNDVALUE = entryp->RefundValue();
        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        delete ArtDisc;
        return 1;
    }
}

/*****************************************************************************/
/* ermitteln Rabattpreis */
/*****************************************************************************/

int AasrvGetRebatePrice( rebatepriceS *d, char * /*error_msg*/)
{
    d->PREISFAKTUR = order->CalcAepInvoiceValue(d->PREISEKAPO, d->DISCOUNTVALUEPCT);
    return 0;
}

/*****************************************************************************/
/* bucht eine neue Promotions-Position auf den aktuellen Auftrag             */
/*****************************************************************************/
int AasrvWritePromoPos(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItem *item = NULL;
    nString nStr = d->PHARMACYGROUPID;
    struct ARTAESEL code;

    order->ClearError();
    if (d->DISCOUNTGRPNO > 0)
    {
        item = order->NewOrderItem_11( d->ARTIKEL_NR,
                                       d->MENGEBESTAETIGT,
                                       d->MENGENATRA,
                                       d->DISCOUNTVALUEPCT,
                                       d->PROMOTYP,
                                       d->PROMOTION_NO,
                                       nStr,
                                       d->DISCOUNTGRPNO,
                                       d->BASEQTY,
                                       d->BASE_VALUE,
                                       d->CUSTOMERNO,
                                       static_cast<PriceTypeEnum>(d->PREIS_TYP) );
    }
    else
    {
        item = order->NewOrderItem_10( d->ARTIKEL_NR,
                                       d->MENGEBESTAETIGT,
                                       d->MENGENATRA,
                                       d->DISCOUNTVALUEPCT,
                                       d->PROMOTYP,
                                       d->PROMOTION_NO,
                                       nStr,
                                       static_cast<PriceTypeEnum>(d->PREIS_TYP) );
    }
    if ( ! (order->IsGoodState()) )
    {
        AllgStrCopy(error_msg, order->ErrorMsg(), MAX_ERROR_MSG_AE);
        switch (order->ErrorNumber())
        {
        case CMSG_ART_QLACK:
            setValuesOnMsgArtQLack(d, order);
            return 0;
        case CMSG_ITM_ARTQUOTA_EXEEDED:
            d->BESTAND  = order->RestQuota();   // Hier Restkontigent
            d->MENGE    = 0;                    // Verbundmenge
            d->FILIALNR1 = 0;                   // Verbundfiliale
            d->STATUS   = ITEM_STAT_NACHLIEFUPD;
            return 0;
        case CMSG_ORD_CREDITLIMIT_EXHAUSTED:
            setValuesOnMsgOrdCreditLimitExhausted(d, order);
            return 0;
        default:
            return getReturnCodeOnError(order);
        }
    }
    code.ARTIKEL_NR = d->ARTIKEL_NR;
    AatartSel_Preferred(&code, error_msg);
    if (item != NULL)
    {
        item->SetArticleCodeValues(code.CODE_TYPE, code.ARTICLE_CODE);
    }

    order->ReCalcValues();
    AasrvAuftrWerte(d);
    if (item != NULL)
    {
        AasrvPosInf(item, d);
    }

    return 0;
}

/*****************************************************************************/
/* Lesen Rechnungsdruckeinstellungen */
/*****************************************************************************/
int AasrvGetInvoiceSettings( invoicesettingsS *d, char * /*error_msg*/)
{
    d->PRINT = order->Customer()->GetPrint(static_cast<PriceTypeEnum>(d->PREIS_TYP));
    d->DEDUCTION_AEP = order->Customer()->GetDeductionAep(static_cast<PriceTypeEnum>(d->PREIS_TYP));
    d->DEDUCTION_AVP = order->Customer()->GetDeductionAvp(static_cast<PriceTypeEnum>(d->PREIS_TYP));
    d->WITHCOLUMNNR = order->Customer()->GetWithColumnNr(static_cast<PriceTypeEnum>(d->PREIS_TYP));
    d->BYEMAIL = order->Customer()->GetInvoiceEmail(static_cast<PriceTypeEnum>(d->PREIS_TYP));
    return 0;
}

/*****************************************************************************/
/* Schreiben Rechnungsdruckeinstellungen */
/*****************************************************************************/
int AasrvWriteInvoiceSettings( invoicesettingsS *d, char * /*error_msg*/)
{
    order->Customer()->SetPrint(d->PRINT, static_cast<PriceTypeEnum>(d->PREIS_TYP));
    order->Customer()->SetDeductionAep(d->DEDUCTION_AEP, static_cast<PriceTypeEnum>(d->PREIS_TYP));
    order->Customer()->SetDeductionAvp(d->DEDUCTION_AVP, static_cast<PriceTypeEnum>(d->PREIS_TYP));
    order->Customer()->SetWithColumnNr(d->WITHCOLUMNNR, static_cast<PriceTypeEnum>(d->PREIS_TYP));
    order->Customer()->SetInvoiceEmail(d->BYEMAIL, static_cast<PriceTypeEnum>(d->PREIS_TYP));
    return 0;
}

/*************************************************************************/
// AasrvClearROParam
/*************************************************************************/
int AasrvClearROParam(rabattorderS * /*d*/, char * /*error_msg*/)
{
    order->CancelRebateOrder();
    return 0;
}

/*************************************************************************/
// AasrvConfirmRO
/*************************************************************************/
int AasrvConfirmRO(rabattorderS * /*d*/, char * /*error_msg*/)
{
    order->ConfirmOrderDiscAcc();
    return 0;
}

/*************************************************************************/
// AasrvSetNatra
/*************************************************************************/
int AasrvSetNatra(struct AUFPOSBUCH *d, char *error_msg)
{
    pxOrderItemList *itemList;
    pxOrderItem *item;

    order->ClearError();
    itemList = order->ItemList();
    item = (pxOrderItem *)itemList->At(d->POSNR - 1);
    if (item->Open() == nSTATE_GOOD)
    {
        //Natramenge für die Position setzen
        item->SetMengeNatra(d->MENGENATRA);
    }
    if ( ! (item->IsGoodState()) )
    {
        return handleErrorAndCloseItem(item, error_msg);
    }
    item->Close();
    AasrvPosInf(item, d);

    return 0;
}

/*************************************************************************/
// AasrvClearZU
/*************************************************************************/
int AasrvClearZU(struct AUFTRAG *d, char * /*error_msg*/)
{
    if ( d->ZUGRUND[ZU_KREDITLIMIT] == '0')
    {
        order->ClearKreditLimitErreicht();
    }
    if ( d->ZUGRUND[ZU_INTERNET] == '0')
    {
        order->ClearDefferedForInternet();
    }
    if ( d->ZUGRUND[ZU_BACKROUTING] == '0')
    {
        order->ClearDefferedForBackRouting();
    }
    if ( d->ZUGRUND[ZU_DD_OHNE] == '0')
    {
        order->ClearDDNotClose();
    }
    if ( d->ZUGRUND[ZU_BTM] == '0')
    {
        order->ClearSeparateArtGroup();
    }
    if ( d->ZUGRUND[ZU_OV] == '0')
    {
        order->ClearOverDriveCondition();
    }
    if ( d->ZUGRUND[ZU_WAHL_STELLER] == '0')
    {
        order->ClearRebateArtSelection();
    }
    if ( d->ZUGRUND[ZU_NO_QTY_NR] == '0')
    {
        order->ClearNoRebateQty();
    }
    if ( d->ZUGRUND[ZU_NO_CICS] == '0')
    {
        order->ClearNoCics();
    }
    if ( d->ZUGRUND[ZU_INVENTUR_HERST] == '0')
    {
        order->ClearManufacturerInventory();
    }
    if ( d->ZUGRUND[ZU_INVENTUR_KONSIG] == '0')
    {
        order->ClearKonsigPartnerInventory();
    }
    return 0;
}

/*************************************************************************/
// AasrvWriteProLink
/*************************************************************************/
int AasrvWriteProLink(prolinkS *d, char * /*error_msg*/)
{
    order->WriteProLink(d->DATEPROFORMA, d->INVOICENUMBERPRO, d->KDAUFTRAGNRPRO);

    return 0;
}

/*************************************************************************/
// AasrvSetCashRebate
/*************************************************************************/
int AasrvSetCashRebate(struct AUFTRAG *d, char * /*error_msg*/)
{
    if (d->NORABATTKONTO[0] == '0')
        order->ClearNoRebateAccount();
    else
        order->SetNoRebateAccount();
    return 0;
}

/*************************************************************************/
// AasrvGetRanges
/*************************************************************************/
int AasrvGetRanges(rangelistS *d, char *error_msg)
{
    if ( !order->OrderType().IsDiscountable() )
    {
        // Anzahl wird zur Uebergabe der Ablehnung eines Rabattes missbraucht
        strcpy(error_msg, "Ordertype without rebates");
        return -2;
    }
    if ( !(order->Customer()->CustomerGroupFlagsList()->IsKscDiscountEnabled()) )
    {
        // Anzahl wird zur Uebergabe der Ablehnung eines Rabattes missbraucht
        strcpy(error_msg, "Customergroup without rebates");
        return -2;
    }
    static int anz = 0;
    static int first = 0;
    static int anzdisc = 0;
    static int maxanz = 0;
    static int maxanzdisc = 0;
    static pxRangeControl*   entryp = NULL;
    static pxRangeControlList* rangecl = NULL;
    pxDiscountList*         discpl = NULL;             // Discount entries
    pxDiscount*             discp = NULL;             // Discount entries
//  int itest;

    if (!first)
    {
        order->RangeCollectList();
        order->BuildRangeCollectList();
        if (order->RangeCollectList()->Entries() == 0)
        {
            return 1;
        }
        rangecl = order->BuildRangeControleList();
        if (rangecl == NULL)
        {
            delete rangecl;
            return 1;
        }
        pxRangeControlListIter it(*rangecl);
        while ( (entryp = (pxRangeControl*) ++it) != NULL )
        {
            if (!entryp->RangeConditionPreview(order->Session(), order))
            {
                delete it.Remove();
                continue;
            }
            discpl = (pxDiscountList*)entryp->RangePreviewList();
//          itest = discpl->Entries();
        }
        maxanz = rangecl->Entries();
        first = 1;
    }
    if (anz >= maxanz)   // Ende der Liste
    {
        anz = 0;
        first = 0;
        anzdisc = 0;
        order->DeleteRangeCollectList();
        delete rangecl;
        return 1;
    }
    entryp = (pxRangeControl*)(rangecl->At(anz));
    if (entryp)
    {
        discpl = (pxDiscountList*)entryp->RangePreviewList();
        maxanzdisc = discpl->Entries();
        discp = (pxDiscount*)discpl->At(anzdisc);

        d->DISCOUNTGRPNO = entryp->DiscountGrpNo();

        if (getSession().isCroatia()) {
            d->ARTICLENO = 0;
            if (d->DISCOUNTGRPNO == 0)
            {
                d->ARTICLENO = entryp->ArticleNo();

            }
        }

        d->BASEQTY = discp->BaseQty();
        d->DISCOUNTQTY = discp->DiscountQty();
        d->DISCOUNTVALUEPCT = discp->DiscountValuePct();
        d->DISCOUNTARTICLE = discp->DiscountArticle();
        d->BASE_VALUE = discp->BaseValue();
        d->ORDVALNET = entryp->ShipValue();
        d->ANZAHL = entryp->QtyInRange();
        ++anzdisc;
        if (anzdisc >= maxanzdisc)
        {
            anzdisc = 0;
            ++anz;
        }
        return 0;
    }
    else
    {
        anz = 0;
        first = 0;
        anzdisc = 0;
        order->DeleteRangeCollectList();
        delete rangecl;
        return 1;
    }
}

/*************************************************************************/
// AasrvGetRangesBG
/*************************************************************************/
int AasrvGetRangesBG(rangelistS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int first = 0;
    static int anzdisc = 0;
    static int maxanz = 0;
    static int maxanzdisc = 0;
    static pxRangeCollect*   collect = NULL;
    static pxRangeControl*   entryp = NULL;
    static pxRangeControlList* rangecl = NULL;
    pxDiscountList*         discpl = NULL;             // Discount entries
    pxDiscount*             discp = NULL;             // Discount entries
//  int itest;

    if (!first)
    {
        order->RangeCollectList();
        order->TargetPromotionCollectList();
        if (order->RangeCollectList()->Entries() == 0)
        {
            return 1;
        }
        rangecl = order->TargetPromotionControleList();
        if (rangecl == NULL)
        {
            delete rangecl;
            return 1;
        }
        pxRangeControlListIter it(*rangecl);
        while ( (entryp = (pxRangeControl*) ++it) != NULL )
        {
            if (!entryp->RangeConditionPreview(order->Session(), order))
            {
                delete it.Remove();
                continue;
            }
            discpl = (pxDiscountList*)entryp->RangePreviewList();
//          itest = discpl->Entries();
        }
        maxanz = rangecl->Entries();
        first = 1;
    }
    if (anz >= maxanz)  // Ende der Liste
    {
        anz = 0;
        first = 0;
        anzdisc = 0;
        order->DeleteRangeCollectList();
        delete rangecl;
        return 1;
    }
    entryp = (pxRangeControl*)(rangecl->At(anz));
    if (entryp)
    {
        discpl = (pxDiscountList*)entryp->RangePreviewList();
        maxanzdisc = discpl->Entries();
        discp = (pxDiscount*)discpl->At(anzdisc);

        if (discp->ArticleNo() == 0)
        {
            d->ANZAHL = entryp->QtyInRange();
        }
        else
        {
            collect = order->RangeCollectList()->Find(discp->ArticleNo(),entryp->DiscountGrpNo());
            d->ANZAHL = (collect == NULL) ? 0 : collect->Quantity();
        }
        d->ARTICLENO = discp->ArticleNo();
        d->DISCOUNTGRPNO = entryp->DiscountGrpNo();
        d->BASEQTY = discp->BaseQty();
        d->DISCOUNTQTY = discp->DiscountQty();
        d->DISCOUNTVALUEPCT = discp->DiscountValuePct();
        d->DISCOUNTARTICLE = discp->DiscountArticle();
        d->BASE_VALUE = discp->BaseValue();
        d->ORDVALNET = entryp->ShipValue();
        ++anzdisc;
        if (anzdisc >= maxanzdisc)
        {
            anzdisc = 0;
            ++anz;
        }
        return 0;
    }
    else
    {
        anz = 0;
        first = 0;
        anzdisc = 0;
        order->DeleteRangeCollectList();
        delete rangecl;
        return 1;
    }
}

/*************************************************************************/
// AasrvCheckKippzeit
/*************************************************************************/
int AasrvCheckKippzeit(struct AUFTRAG * /*d*/, char * /*error_msg*/)
{
    // Keine Prüfung wenn keine Kommi erfolgt
    if( order->CommType().IsNoShipment() )
    {
        return 0;
    }

    // Prüfung über TourManager
    if( order->getTourAssignmentUtil()->isTourValid(order->TourId()) )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*****************************************************************************/
/* Uebergeben Positionen zur Berechnung best TA                              */
/*****************************************************************************/
int AasrvWriteProformaPos(struct AUFPOSBUCH *d, char * /*error_msg*/)
{
    nString nStr = d->PHARMACYGROUPID;
    order->NewOrderTemporaryItem( d->ARTIKEL_NR,
                                  d->MENGEBESTAETIGT,
                                  d->MENGENATRA,
                                  d->DISCOUNTVALUEPCT,
                                  d->PROMOTYP,
                                  d->PROMOTION_NO,
                                  nStr,
                                  static_cast<PriceTypeEnum>(d->PREIS_TYP ));

    return 0;
}

/*****************************************************************************/
/* Holen best TA                                                             */
/*****************************************************************************/
int AasrvGetBestTA(struct AUFPOSBUCH *d, char * /*error_msg*/)
{
    long BestPromotion = 0;
    order->BestTargetPromotion( &BestPromotion);
    d->PROMOTION_NO = static_cast<short>(BestPromotion);
    order->DeleteItemListTemporary();

    return 0;
}

/*****************************************************************************/
/* Setzen Auftrag auf Barzahlung                                             */
/*****************************************************************************/
int AasrvSetOrderToCash(struct AUFTRAG *d, char * /*error_msg*/)
{
    if (d->PAYMENTTYPE[0] == 'C')
    {
        order->SetOrderToCashAe();
    }
    else
    {
        order->SetOrderWithTimeForPayment();
        if ( ! (order->IsGoodState()) )
        {
//      if (err = order->ErrorNumber()) == CMSG_ORD_CREDITLIMIT_EXHAUSTED)
            d->STATUS = ITEM_STAT_KREDITLIMIT;
        }
    }
    return 0;
}

/*****************************************************************************/
/* Versenden eMail                                                           */
/*****************************************************************************/
int AasrvSendEMail(sendmailS *d, char *error_msg)
{
    if (ps->getSmtpServer().empty())
    {
        strcpy(error_msg, "eMail not sent: no mailserver configured");
        return -2;
    }
    EMailHandler mail(ps->getSmtpServer(), ps->getSmtpPort());
    mail.setSender(d->EMAILADRESSE);
    AllgEntfSpaces(d->MAILINGLIST);
    mail.setRecipientList(d->MAILINGLIST);

    mail.setSubject(d->MAILSUBJECT);
    mail.setText(d->MAILTEXT);
    if (!mail.sendMail())
    {
        strcpy(error_msg, "eMail not sent");
        return -2;
    }
    return 0;
}

/*****************************************************************************/

int AasrvInsertArticleReservation(artikelreserveS* d, char* error_msg)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "AasrvInsertArticleReservation");

    int retval = 0;
    ps->nDBBeginTransaction(cDBTransSet);
    pxArtBase* article = pxArtBase::CreateArticle(ps, d->ARTICLENO, d->BRANCHNO);
    ps->getStockBooking()->CreateEmptyArticleReservation(*article, static_cast<ReservationTypeEnum>(d->RESERVTYPE), d->PHARMACYGROUPID, d->MAXQTY, d->RESERVEPCT);
    if (!ps->getStockBooking()->IsGoodState())
    {
        strcpy(error_msg, ps->getStockBooking()->ErrorMsg());
        retval = -2;
        ps->nDBRollBack();
    }
    else
    {
        ps->nDBCommit(cDBTransSet);
    }
    delete article;
    return retval;
}

int AasrvUpdateArticleReservation(artikelreserveS* d, char* error_msg)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "AasrvUpdateArticleReservation");

    // TODO FN update reservpct and maxqty????
    int retval = 0;
    ps->nDBBeginTransaction(cDBTransSet);
    pxArtBase* article = pxArtBase::CreateArticle(ps, d->ARTICLENO, d->BRANCHNO);
    ps->getStockBooking()->SetAbsoluteArticleReservation(*article, static_cast<ReservationTypeEnum>(d->RESERVTYPE), d->PHARMACYGROUPID, d->RESERVEDQTY);
    if (!ps->getStockBooking()->IsGoodState())
    {
        strcpy(error_msg, ps->getStockBooking()->ErrorMsg());
        retval = -2;
        ps->nDBRollBack();
    }
    else
    {
        ps->nDBCommit(cDBTransSet);
    }
    delete article;
    return retval;
}

int AasrvDeleteArticleReservation(artikelreserveS* d, char* error_msg)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "AasrvDeleteArticleReservation");

    int retval = 0;
    ps->nDBBeginTransaction(cDBTransSet);
    pxArtBase* article = pxArtBase::CreateArticle(ps, d->ARTICLENO, d->BRANCHNO);
    ps->getStockBooking()->DeleteArticleReservation(*article, static_cast<ReservationTypeEnum>(d->RESERVTYPE), d->PHARMACYGROUPID);
    if (!ps->getStockBooking()->IsGoodState())
    {
        strcpy(error_msg, ps->getStockBooking()->ErrorMsg());
        retval = -2;
        ps->nDBRollBack();
    }
    else
    {
        ps->nDBCommit(cDBTransSet);
    }
    delete article;
    return retval;
}

int AasrvInsertBestandArticleReservation(artikelreserveS* d, char* error_msg)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "AasrvInsertBestandArticleReservation");

    int retval = 0;
    ps->nDBBeginTransaction(cDBTransSet);
    pxArtBase* article = pxArtBase::CreateArticle(ps, d->ARTICLENO, d->BRANCHNO);
    ps->getStockBooking()->CreateEmptyArticleReservation(*article, static_cast<ReservationTypeEnum>(d->RESERVTYPE), d->PHARMACYGROUPID, d->MAXQTY, d->RESERVEPCT);

    // jetzt reservepct vom freien bestand rüberbuchen
    d->RESERVEDQTY = ps->getStockBooking()->GetAvailableQtyInStock(*article) * d->RESERVEPCT / 100;
//  if (d->RESERVEDQTY > d->MAXQTY) d->RESERVEDQTY = d->MAXQTY;
    ps->getStockBooking()->AddArticleReservation(*article, static_cast<ReservationTypeEnum>(d->RESERVTYPE), d->PHARMACYGROUPID, d->RESERVEDQTY);
    if (!ps->getStockBooking()->IsGoodState())
    {
        strcpy(error_msg, ps->getStockBooking()->ErrorMsg());
        retval = -2;
        ps->nDBRollBack();
    }
    else
    {
        ps->nDBCommit(cDBTransSet);
    }
    delete article;
    return retval;
}

int AasrvReserveStockAbsArticleReservation(artikelreserveS* d, char* error_msg)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "AasrvReserveStockAbsArticleReservation");

    int retval = 0;
    ps->nDBBeginTransaction(cDBTransSet);
    pxArtBase* article = pxArtBase::CreateArticle(ps, d->ARTICLENO, d->BRANCHNO);
    ps->getStockBooking()->SetAbsoluteArticleReservation(*article, static_cast<ReservationTypeEnum>(d->RESERVTYPE), d->PHARMACYGROUPID, d->RESERVEDQTY);
    if (!ps->getStockBooking()->IsGoodState())
    {
        strcpy(error_msg, ps->getStockBooking()->ErrorMsg());
        retval = -2;
        ps->nDBRollBack();
    }
    else
    {
        ps->nDBCommit(cDBTransSet);
    }
    delete article;
    return retval;
}

/*****************************************************************************/
/* möglichen Verbund                                                         */
/*****************************************************************************/

int AasrvIBTPossible(verbundmoeglS * /*d*/, char* /*error_msg*/)
{
    return 0;
}
/*****************************************************************************/
/* ist Position bereits verarbeitete Nachliefer-/Dispo-Position ?            */
/*****************************************************************************/

int AasrvSpecialPosDone(struct AUFPOSBUCH* d, char* /*error_msg*/)
{
    if( ps->getSudWorkupCompletedChecker()->isSUDWorkupCompleted(order->KdAuftragNr(), order->IDFNr(), d->POSNR ))
    {
        return 1; // position already processed
    }
    return 0;
}

/*****************************************************************************/
/* enthält Auftrag bereits verarbeitete Nachliefer-/Dispo-Position ?         */
/*****************************************************************************/

int AasrvOrderSpecialPosDone(struct AUFTRAG* d, char* /*error_msg*/)
{
    if( ps->getSudWorkupCompletedChecker()->isSUDWorkupCompleted( d->KDAUFTRAGNR, order->IDFNr() ))
    {
        return 1; // at least one special position already processed
    }
    return 0;
}

/*****************************************************************************/
/* Verbund-Position bereits verarbeitet ?                                    */
/*****************************************************************************/

int AasrvIBTPosDone(struct AUFPOSBUCH* d, char* /*error_msg*/)
{
    pxOrderItemList *itemList;
    pxOrderItem *item;

    itemList = order->ItemList();
    item = (pxOrderItem *)itemList->At(d->POSNR - 1);
    if( item->isIbtBookingCompleted() )
    {
        return 1; // IBT position already processed
    }
    return 0;


    //if (item->Open() == nSTATE_GOOD)
 //   {
 //   }
}

/*****************************************************************************/
/* enthält Auftrag bereits verarbeitete Verbund-Positionen ?                 */
/*****************************************************************************/

int AasrvIBTOrderPosDone(struct AUFTRAG* , char* /*error_msg*/)
{
    if( order->hasAtLeastOneCompletedIbtBooking() )
    {
        return 1; // at least one IBT position of order already processed
    }
    return 0;
}

/*****************************************************************************/
/* Stornieren eines Auftrages bei Kreditlimitueberschreitung                 */
/*****************************************************************************/
int AasrvCancelorderDebtLimit(struct AUFTRAG * /*d*/, char *error_msg)
{
    nString reason;
    nString comment;
    nString user;
    user = ps->Device()->Name();
    reason = "Cancellation via AE";
    comment = " ";
    order->SetReleaseInfos(reason, comment, user, Order::CANCEL);
    order->SetNoDebtLimitCheck();
    order->CancelOrder(pxDVC_UNDEFINED, Order::cCancel_UnConditional);

    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    order->DeleteCremaMail(order->KdAuftragNr(), order->Vertriebszentrum());
    delete order;
    order = NULL;

    return 0;
}

/*****************************************************************************/
/* Abschliessen eines Auftrages bei Kreditlimitueberschreitung               */
/*****************************************************************************/
int AasrvCloseorderDebtLimit(struct AUFTRAG * /*d*/, char *error_msg)
{
    nString reason;
    nString comment;
    nString user;
    user = ps->Device()->Name();
    reason = "Urgent release via AE";
    comment = "Notfreigabe durch IT";
    order->SetReleaseInfos(reason, comment, user, Order::CLOSE);

    if (getSession().isBulgaria()) // In case of approval in Bulgaria, orders are set to cash 
    {
        order->SetOrderToCash();
    }
    order->SetNoDebtLimitCheck();
    order->Close(Order::EntryClosed, Order::cClose_UnConditional);

    if ( ! (order->IsGoodState()) )
    {
        return handleError(order, error_msg);
    }
    order->DeleteCremaMail(order->KdAuftragNr(), order->Vertriebszentrum());
    delete order;
    order = NULL;

    return 0;
}

/*****************************************************************************/
/* ermitteln OMG Rabatte  */
/*****************************************************************************/
int AasrvGetOMGRebates( articleomgS *d, char * /*error_msg*/)
{
    static size_t index = 0;
    using namespace libcsc::discount;
    static TenderDiscountListPtr list;

    if( 0 == index )
{
        TenderDiscountSearchParams searchParams( d->CUSTOMERNO, d->ARTICLENO, false );
        if( -1 == searchParams.customerNo )
    {
            searchParams.customerNo.setUnset();
        }
        list = getSession().getTenderDiscountFinder()->findByPattern( searchParams );
        if( list->empty() )
        {
            index = 0;
            list.reset();
            return 1;
        }
    }
    if( index >= list->size() )   // Ende der Liste
    {
        index = 0;
        list.reset();
        return 1;
    }
    TenderDiscountPtr td( list->at( index ) );
    if( td.get() )
    {
        d->BRANCHNO = td->getBranchNumber();
        d->ARTICLENO = td->getArticleNumber();
        strncpy( d->PHARMACYGROUPID, td->getPharmacyGroupId().c_str(), L_DISCOUNTANZ_PHARMACYGROUPID );
        //d->CUSTOMERNO = td->CustomerNo();
        if( 1 != td->getTenderState() )
        {
            d->DATEFROM = 99991231;
            d->DATETO = 99991231;
        }
        else
        {
            d->DATEFROM = static_cast<const basar::Date &>( td->getFromDate() ).getDate();
            d->DATETO = static_cast<const basar::Date &>( td->getToDate() ).getDate();
        }
        d->RESTQTY = td->getAvailableQuantity();
        d->ADDDISCOUNTPCT = static_cast<const basar::Decimal &>( td->getDiscountPercent() ).toFloat64();
        d->CONTRACTQTY = td->getContractQuantity();
        d->DISCOUNTCALCFROM = td->getDiscountCalcFrom();
        d->DISCOUNTAPPLYTO = td->getDiscountApplyTo();
        ++index;
        return 0;
    }
    else
    {
        index = 0;
        list.reset();
        return 1;
    }
}

/*****************************************************************************/
/* Get information if mail link is enabled and the base url of the link      */
/*****************************************************************************/
int AasrvCallbackGetMailLink(callbackmaillinkS* d, char* /*error_msg*/)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "AasrvCallbackGetMailLink");

    pxParameter* param;
    nString programName("AE");
    nString objective("Callback");
    nString paramName("MailLink");

    param  = new pxParameter(ps, d->BRANCHNO, programName, objective, paramName);

    int rc = param->Get(cDBGET_READONLY);
    if (rc != cDBXR_NORMAL)
    {
        std::stringstream ss;
        ss << "AasrvCallbackGetMailLink rc = " << rc;
        BLOG_WARN(libcsc::LoggerPool::getLoggerSession(), ss.str().c_str());
        d->ENABLED = 0;
        AllgStrCopy(d->WEBSITEBASEURL, "", L_CALLBACKMAILLINK_WEBSITEBASEURL);
    }
    else
    {
        d->ENABLED = (param->Wert() == 1) ? 1 : 0;
        AllgStrCopy(d->WEBSITEBASEURL, param->AusPraegung(), L_CALLBACKMAILLINK_WEBSITEBASEURL);
    }

    delete param;
    return 0;
}

static int handleError(nError* error, char *error_msg)
{
    AllgStrCopy(error_msg, error->ErrorMsg(), MAX_ERROR_MSG_AE);
    return getReturnCodeOnError(error);
}

static int getReturnCodeOnError(nError* error)
{
    return (error->IsFatalErrorState() || error->IsAbendState()) ? -1 : -2;
}

static int handleErrorAndCloseItem(pxOrderItem* item, char *error_msg)
{
    int result = handleError(item, error_msg);
    item->Close();
    return result;
}

static void copyCharToString(char* szDest, char src)
{
    szDest[0] = src;
    szDest[1] = '\0';
}

static double getWertNettoFV(pxOrder* o)
{
    return   o->OrderValues()->OrdValFtaxFSDisc()
            + o->OrderValues()->OrdValLtaxFSDisc()
            + o->OrderValues()->OrdValNtaxFSDisc();
}

static double getWertTaxFV(pxOrder* o)
{
    return   o->OrderValues()->OrdValFtaxFS()
            + o->OrderValues()->OrdValLtaxFS()
            + o->OrderValues()->OrdValNtaxFS()
            - o->OrderValues()->OrdValFtaxFSDisc()
            - o->OrderValues()->OrdValLtaxFSDisc()
            - o->OrderValues()->OrdValNtaxFSDisc();
}

static double getWertNettoKK(pxOrder* o)
{
    return   o->OrderValues()->OrdValFtaxHFDisc()
            + o->OrderValues()->OrdValLtaxHFDisc()
            + o->OrderValues()->OrdValNtaxHFDisc();
}

static double getWertTaxKK(pxOrder* o)
{
    return   o->OrderValues()->OrdValFtaxHF()
            + o->OrderValues()->OrdValLtaxHF()
            + o->OrderValues()->OrdValNtaxHF()
            - o->OrderValues()->OrdValFtaxHFDisc()
            - o->OrderValues()->OrdValLtaxHFDisc()
            - o->OrderValues()->OrdValNtaxHFDisc();
}

static double getWertNettoEH(pxOrder* o)
{
    return   o->OrderValues()->OrdValFtaxRSDisc()
            + o->OrderValues()->OrdValLtaxRSDisc()
            + o->OrderValues()->OrdValNtaxRSDisc();
}

static double getWertTaxEH(pxOrder* o)
{
    return   o->OrderValues()->OrdValFtaxRS()
            + o->OrderValues()->OrdValLtaxRS()
            + o->OrderValues()->OrdValNtaxRS()
            - o->OrderValues()->OrdValFtaxRSDisc()
            - o->OrderValues()->OrdValLtaxRSDisc()
            - o->OrderValues()->OrdValNtaxRSDisc();
}

static void setOrderValues(struct AUFTRAG* d, pxOrder* o)
{
    if ( o->OrderValues() )
    {
        d->WERTNETTO_FV = getWertNettoFV(o);
        d->WERTTAX_FV   = getWertTaxFV(o);
        d->WERTNETTO_KK = getWertNettoKK(o);
        d->WERTTAX_KK   = getWertTaxKK(o);
        d->WERTNETTO_EH = getWertNettoEH(o);
        d->WERTTAX_EH   = getWertTaxEH(o);
    }
}

static void setOrderValues(struct AUFPOSBUCH* d, pxOrder* o)
{
    if ( o->OrderValues() )
    {
        d->WERTNETTO_FV = getWertNettoFV(o);
        d->WERTTAX_FV   = getWertTaxFV(o);
        d->WERTNETTO_KK = getWertNettoKK(o);
        d->WERTTAX_KK   = getWertTaxKK(o);
        d->WERTNETTO_EH = getWertNettoEH(o);
        d->WERTTAX_EH   = getWertTaxEH(o);
    }
}

static void setAuftragLieferZeilen(struct AUFPOSBUCH* d, pxOrder* o)
{
    d->WERTAUFTRAG   = o->WertAuftrag();
    d->WERTLIEFERUNG = o->WertLieferung();
    d->WERTZEILEN    = o->WertZeilen();
    d->WERTNETTO     = o->WertNetto();
}

static void setValuesOnMsgArtQLack(struct AUFPOSBUCH* d, pxOrder* /*o*/)
{
    d->BESTAND = order->LastStock();
    d->MENGE   = order->AuxStock();     // Verbundmenge
    d->FILIALNR1 = order->AuxFil();     // Verbundfiliale
    d->STATUS  = ITEM_STAT_KEINE_MENGE;
}

static void setValuesOnMsgOrdCreditLimitExhausted(struct AUFPOSBUCH* d, pxOrder* o)
{
    d->BESTAND  = o->LastStock();       // Hier Restbestand
    d->MENGE    = 0;                    // Verbundmenge
    d->FILIALNR1 = 0;                   // Verbundfiliale
    d->STATUS   = ITEM_STAT_KREDITLIMIT;
}

/*************************************************************************/
// AasrvGetReservationConfigListByOrderType
/*************************************************************************/

int AasrvGetReservationConfigListByOrderType(ordertypereservationconfigS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = 0;
    static libcsc::stockbooking::IOrderTypeReservationConfigCollectionPtr configs;
    if (0 == anz)
    {
        ps->getStockBookingComponentManager()->getReservationConfigRepository()->reset();
        configs = ps->getStockBookingComponentManager()->getReservationConfigRepository()->findOrderTypeReservationConfig(d->CSCORDERTYPE);
        if (NULL == configs.get() || configs->empty())
        {
            anz = 0;
            configs.reset();
            return 1;
        }
        maxanz = configs->size();
    }
    if (anz >= maxanz)   // Ende der Liste
    {
        anz = 0;
        configs.reset();
        return 1;
    }
    libcsc::stockbooking::IOrderTypeReservationConfigPtr config = configs->at(anz);
    if (config.get())
    {
        d->ID = config->getId();
        strncpy(d->CSCORDERTYPE, config->getOrderType().c_str(), L_ORDERTYPERESERVATIONCONFIG_CSCORDERTYPE);;
        d->CSCRESERVATIONTYPE = config->getReservationType();
        d->FREESTOCKHASPRIORITY = config->getFreeStockHasPriority();
        strncpy(d->ORDERTYPERESERVATIONCONFIGNAME, config->getOrderTypeReservationConfigName().c_str(), L_ORDERTYPERESERVATIONCONFIG_ORDERTYPERESERVATIONCONFIGNAME);
        d->PRIORITY = config->getPriority();
        d->RESERVEDSTOCKONLY = config->getReservedStockOnly();
        ++anz;
        return 0;
    }
    anz = 0;
    configs.reset();
    return 1;
}

/*************************************************************************/
// AasrvGetReservationConfigByID
/*************************************************************************/
int AasrvGetReservationConfigByID(ordertypereservationconfigS *d, char * /*error_msg*/)
{
    libcsc::stockbooking::IOrderTypeReservationConfigPtr config;
    ps->getStockBookingComponentManager()->getReservationConfigRepository()->reset();
    config = ps->getStockBookingComponentManager()->getReservationConfigRepository()->findOrderTypeReservationConfigById(d->ID);
    if (config->isClean())
    {
        d->ID = config->getId();
        strncpy(d->CSCORDERTYPE, config->getOrderType().c_str(), L_ORDERTYPERESERVATIONCONFIG_CSCORDERTYPE);;
        d->CSCRESERVATIONTYPE = config->getReservationType();
        d->FREESTOCKHASPRIORITY = config->getFreeStockHasPriority() ? 1 : 0;
        strncpy(d->ORDERTYPERESERVATIONCONFIGNAME, config->getReservationName().c_str(), L_ORDERTYPERESERVATIONCONFIG_ORDERTYPERESERVATIONCONFIGNAME);
        d->PRIORITY = config->getPriority();
        d->RESERVEDSTOCKONLY = config->getReservedStockOnly() ? 1 : 0;
    }
    return 0;
}

/*************************************************************************/
// AasrvInsertReservationConfig
/*************************************************************************/
int AasrvInsertReservationConfig(ordertypereservationconfigS* d, char* error_msg)
{
    basar::VarString orderType(d->CSCORDERTYPE);
    orderType.trim();
    if (orderType.empty())
    {
        strncpy(error_msg, "ordertype empty!", MAX_ERROR_MSG_AE);
        return -2;
    }
    libcsc::stockbooking::IOrderTypeReservationConfigPtr config;
    ps->getStockBookingComponentManager()->getReservationConfigRepository()->reset();
    config = ps->getStockBookingComponentManager()->getReservationConfigRepository()->getEmptyOrderTypeReservationConfig();
    config->setOrderType(orderType);
    basar::VarString name(d->ORDERTYPERESERVATIONCONFIGNAME);
    name.trim();
    config->setOrderTypeReservationConfigName(name);
    config->setPriority(d->PRIORITY);
    config->setReservationType(d->CSCRESERVATIONTYPE);
    config->setReservedStockOnly(d->RESERVEDSTOCKONLY == 1);
    config->setFreeStockHasPriority(d->FREESTOCKHASPRIORITY == 1);
    ps->getStockBookingComponentManager()->getReservationConfigRepository()->saveOrderTypeReservationConfig(config);

    //return structur with new ID
    d->ID = config->getId();
    return 0;
}

/*************************************************************************/
// AasrvUpdateReservationConfig
/*************************************************************************/
int AasrvUpdateReservationConfig(ordertypereservationconfigS *d, char * /*error_msg*/)
{
    libcsc::stockbooking::IOrderTypeReservationConfigPtr config;
    ps->getStockBookingComponentManager()->getReservationConfigRepository()->reset();
    config = ps->getStockBookingComponentManager()->getReservationConfigRepository()->findOrderTypeReservationConfigById(d->ID);
    if (NULL != config.get())
    {
        basar::VarString orderType(d->CSCORDERTYPE);
        orderType.trim();
        config->setOrderType(orderType);
        basar::VarString name(d->ORDERTYPERESERVATIONCONFIGNAME);
        name.trim();
        config->setOrderTypeReservationConfigName(name);
        config->setPriority(d->PRIORITY);
        config->setReservationType(d->CSCRESERVATIONTYPE);
        config->setReservedStockOnly(d->RESERVEDSTOCKONLY == 1);
        config->setFreeStockHasPriority(d->FREESTOCKHASPRIORITY == 1);
        ps->getStockBookingComponentManager()->getReservationConfigRepository()->saveOrderTypeReservationConfig(config);
    }
    return 0;
}

/*************************************************************************/
// AasrvDeleteReservationConfig
/*************************************************************************/
int AasrvDeleteReservationConfig(ordertypereservationconfigS *d, char * /*error_msg*/)
{
    libcsc::stockbooking::IOrderTypeReservationConfigPtr config;
    ps->getStockBookingComponentManager()->getReservationConfigRepository()->reset();
    config = ps->getStockBookingComponentManager()->getReservationConfigRepository()->findOrderTypeReservationConfigById(d->ID);
    if (NULL != config.get() && config->isClean())
    {
        ps->getStockBookingComponentManager()->getReservationConfigRepository()->deleteOrderTypeReservationConfig(config);
    }
    return 1;
}

/*************************************************************************/
// AasrvGetReservationConfigcpgListByConfigID
/*************************************************************************/
int AasrvGetReservationConfigcpgListByConfigID(ordertypereservationconfigcpgS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = 0;
    static libcsc::stockbooking::IOrderTypeReservationConfigPtr config;

    if (0 == anz)
    {
        ps->getStockBookingComponentManager()->getReservationConfigRepository()->reset();
        config = ps->getStockBookingComponentManager()->getReservationConfigRepository()->findOrderTypeReservationConfigById(d->ORDERTYPERESERVATIONCONFIG_ID);
        if (NULL == config.get() || false == config->isClean() || config->getPharmacyGroups()->empty())
        {
            anz = 0;
            config.reset();
            return 1;
        }
        maxanz = config->getPharmacyGroups()->size();
    }
    if (anz >= maxanz)   // Ende der Liste
    {
        anz = 0;
        config.reset();
        return 1;
    }

    d->ID = config->getPharmacyGroups()->at(anz)->getId();
    strncpy(d->PHARMACYGROUPID, config->getPharmacyGroups()->at(anz)->getPharmacyGroupId().c_str(),
        L_ORDERTYPERESERVATIONCONFIGCPG_PHARMACYGROUPID);
    d->ORDERTYPERESERVATIONCONFIG_ID = config->getPharmacyGroups()->at(anz)->getOrderTypeReservationConfigId();
    ++anz;
    return 0;
}

/*************************************************************************/
// AasrvInsertReservationConfigcpg
/*************************************************************************/
int AasrvInsertReservationConfigcpg(ordertypereservationconfigcpgS *d, char * /*error_msg*/)
{
    libcsc::stockbooking::IOrderTypeReservationConfigPtr config;
    ps->getStockBookingComponentManager()->getReservationConfigRepository()->reset();
    config = ps->getStockBookingComponentManager()->getReservationConfigRepository()->findOrderTypeReservationConfigById(d->ORDERTYPERESERVATIONCONFIG_ID);
    if (NULL != config.get())
    {
        libcsc::stockbooking::IOrderTypeReservationConfigPharmacyGroupPtr pharmGrp;
        pharmGrp = config->addPharmacyGroup(d->PHARMACYGROUPID);
        ps->getStockBookingComponentManager()->getReservationConfigRepository()->saveOrderTypeReservationConfig(config);
        d->ID = pharmGrp->getId();
    }
    return 0;
    //return structur with new ID
}

/*************************************************************************/
// AasrvDeleteReservationConfigcpgConfigID
/*************************************************************************/
int AasrvDeleteReservationConfigcpgConfigID(ordertypereservationconfigcpgS * /*d*/, char * /*error_msg*/)
{
    return 0;
}

/*************************************************************************/
// AasrvDeleteReservationConfigcpg
/*************************************************************************/
int AasrvDeleteReservationConfigcpg(ordertypereservationconfigcpgS *d, char * /*error_msg*/)
{
    ps->getStockBookingComponentManager()->getReservationConfigRepository()->deleteOrderTypeReservationConfigPharmacyGroupById(d->ID);
    return 0;
}

/*************************************************************************/
// AasrvGetCSCReservationTypeList
/*************************************************************************/
int AasrvGetCSCReservationTypeList(cscreservationtypesS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = 0;
    static libcsc::stockbooking::IReservationTypeCollectionPtr types;
    if (0 == anz)
    {
        ps->getStockBookingComponentManager()->getReservationConfigRepository()->reset();
        types = ps->getStockBookingComponentManager()->getReservationConfigRepository()->findReservationTypes();
        if (types->empty())
        {
            anz = 0;
            types.reset();
            return 1;
        }
        maxanz = types->size();
    }
    if (anz >= maxanz)   // Ende der Liste
    {
        anz = 0;
        types.reset();
        return 1;
    }
    libcsc::stockbooking::IReservationTypePtr type = types->at(anz);
    if (type.get())
    {
        d->ID = type->getId();
        d->CSCRESERVATIONTYPE = type->getReservationType();
        strncpy(d->CSCRESERVATIONTYPENAME, type->getReservationName().c_str(), L_CSCRESERVATIONTYPES_CSCRESERVATIONTYPENAME);
        d->WITHPHARMACYGROUP = type->getWithPharmacyGroup();
        ++anz;
        return 0;
    }
    anz = 0;
    types.reset();
    return 1;
}

/*************************************************************************/
// AasrvGetCSCReservationTypeByTyp
/*************************************************************************/
int AasrvGetCSCReservationTypeByTyp(cscreservationtypesS *d, char * /*error_msg*/)
{
    libcsc::stockbooking::IReservationTypePtr reservationType;
    ps->getStockBookingComponentManager()->getReservationConfigRepository()->reset();
    reservationType = ps->getStockBookingComponentManager()->getReservationConfigRepository()->findReservationType(d->CSCRESERVATIONTYPE);
    if (NULL != reservationType.get())
    {
        d->CSCRESERVATIONTYPE = reservationType->getReservationType();
        strncpy(d->CSCRESERVATIONTYPENAME, reservationType->getReservationName().c_str(), L_CSCRESERVATIONTYPES_CSCRESERVATIONTYPENAME);
        d->ID = reservationType->getId();
        if (true == reservationType->getWithPharmacyGroup())
            d->WITHPHARMACYGROUP = 1;
        else
            d->WITHPHARMACYGROUP = 0;
    }
    return 0;
}

/*************************************************************************/
// AasrvDeleteCSCOrderImportCSVFormats
/*************************************************************************/
int AasrvDeleteCSCOrderImportCSVFormats(cscorderimportcsvformatsS *d, char * /*error_msg*/)
{
    libcsc::parameter::ICSCOrderImportCSVFormatsPtr format;
    ps->getParameterComponentManager()->getCSVOrderImportRepository()->reset();
    format = ps->getParameterComponentManager()->getCSVOrderImportRepository()->findCSCOrderImportCSVFormatsById(d->CSCORDERIMPORTFORMATID);
    if (NULL != format.get())
    {
        ps->getParameterComponentManager()->getCSVOrderImportRepository()->deleteCSCOrderImportCSVFormats(format);
    }
    return 1;
}


/*************************************************************************/
// AasrvGetCSCOrderImportCSVFormats
/*************************************************************************/
int AasrvGetCSCOrderImportCSVFormats(cscorderimportcsvformatsS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = 0;
    static libcsc::parameter::ICSCOrderImportCSVFormatsCollectionPtr formats;
    if (0 == anz)
    {
        ps->getParameterComponentManager()->getCSVOrderImportRepository()->reset();
        formats = ps->getParameterComponentManager()->getCSVOrderImportRepository()->findCSCOrderImportCSVFormats();
        if (NULL == formats.get() || formats->empty())
        {
            anz = 0;
            formats.reset();
            return 1;
        }
        maxanz = formats->size();
    }
    for (;;)
    {
        if (anz >= maxanz)   // Ende der Liste
        {
            anz = 0;
            formats.reset();
            return 1;
        }
        libcsc::parameter::ICSCOrderImportCSVFormatsPtr format = formats->at(anz);
        if (format.get())
        {
            if (d->ISVALID)
            {
                if (!ps->getParameterComponentManager()->getCSVOrderImportRepository()->areMandatoryFieldsSet(format))
                {
                    anz++;
                    continue;
                }
            }

            d->CSCORDERIMPORTFORMATID = format->getCSCOrderImportFormatID();
            strncpy(d->CSVFORMATNAME, format->getCSVFormatName().c_str(), L_CSCORDERIMPORTCSVFORMATS_CSVFORMATNAME);;
            d->DATASTARTINGLINE = format->getDataStartingLine();
            d->POSTPONEORDER = format->getPostponeOrder();
            ++anz;
            return 0;
        }
        else break;
    }
    anz = 0;
    formats.reset();
    return 1;
}

/*************************************************************************/
// AasrvGetCSCOrderImportFields
/*************************************************************************/
int AasrvGetCSCOrderImportFields(cscorderimportfieldsS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = 0;
    static libcsc::parameter::ICSCOrderImportFieldsCollectionPtr types;
    if (0 == anz)
    {
        ps->getParameterComponentManager()->getCSVOrderImportRepository()->reset();
        types = ps->getParameterComponentManager()->getCSVOrderImportRepository()->findCSCOrderImportCSVFields();
        if (types->empty())
        {
            anz = 0;
            types.reset();
            return 1;
        }
        maxanz = types->size();
    }
    if (anz >= maxanz)   // Ende der Liste
    {
        anz = 0;
        types.reset();
        return 1;
    }
    libcsc::parameter::ICSCOrderImportFieldsPtr type = types->at(anz);
    if (type.get())
    {
        d->FIELDNAMEID = type->getFieldNameId();
        strncpy(d->IMPORTFIELDNAME, type->getImportFieldName().c_str(), L_CSCORDERIMPORTFIELDS_IMPORTFIELDNAME);
        strncpy(d->DISPLAYNAME, type->getDisplayName().c_str(), L_CSCORDERIMPORTFIELDS_DISPLAYNAME);
        d->IMPORTMANDATORY = type->getImportMandatory();
        ++anz;
        return 0;
    }
    anz = 0;
    types.reset();
    return 1;
}

/*************************************************************************/
// AasrvGetCSCOrderImportCSVColumns
/*************************************************************************/
int AasrvGetCSCOrderImportCSVColumns(cscorderimportcsvcolumnsS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = 0;
    static libcsc::parameter::ICSCOrderImportCSVFormatsPtr format;

    if (0 == anz)
    {
        ps->getParameterComponentManager()->getCSVOrderImportRepository()->reset();
        format = ps->getParameterComponentManager()->getCSVOrderImportRepository()->findCSCOrderImportCSVFormatsById(d->CSCORDERIMPORTFORMATID);
        if (NULL == format.get() || false == format->isClean() || format->getCSCOrderImportCSVColums()->empty())
        {
            anz = 0;
            format.reset();
            return 1;
        }
        maxanz = format->getCSCOrderImportCSVColums()->size();
    }
    if (anz >= maxanz)   // Ende der Liste
    {
        anz = 0;
        format.reset();
        return 1;
    }

    d->COLUMNNO = format->getCSCOrderImportCSVColums()->at(anz)->getColumnNo();
    d->CSCORDERIMPORTFORMATID = format->getCSCOrderImportCSVColums()->at(anz)->getCscOrderImportFormatId();
    d->FIELDNAMEID = format->getCSCOrderImportCSVColums()->at(anz)->getFieldNameId();
    d->GROUPING = format->getCSCOrderImportCSVColums()->at(anz)->getGrouping();
    ++anz;
    return 0;
}

/*************************************************************************/
// AasrvDeleteCSCOrderImportCSVColumns
/*************************************************************************/
int AasrvDeleteCSCOrderImportCSVColumns(cscorderimportcsvcolumnsS *d, char * /*error_msg*/)
{
    ps->getParameterComponentManager()->getCSVOrderImportRepository()->deleteCSCOrderImportCSVColumnsByKey( d->COLUMNNO, d->CSCORDERIMPORTFORMATID);
    return 0;
}

/*************************************************************************/
// AasrvInsertCSCOrderImportCSVFormats
/*************************************************************************/
int AasrvInsertCSCOrderImportCSVFormats(cscorderimportcsvformatsS *d, char  *error_msg)
{
    basar::VarString FormatName(d->CSVFORMATNAME);
    FormatName.trim();
    if (FormatName.empty())
    {
        strncpy(error_msg, "FormatName empty!", MAX_ERROR_MSG_AE);
        return -2;
    }
    libcsc::parameter::ICSCOrderImportCSVFormatsPtr format;
    ps->getParameterComponentManager()->getCSVOrderImportRepository()->reset();
    format = ps->getParameterComponentManager()->getCSVOrderImportRepository()->getEmptyCSCOrderImportCSVFormats();
    format->setCSVFormatName(FormatName);
//  format->setCSCOrderImportFormatID(0);
    format->setDataStartingLine(d->DATASTARTINGLINE);
    format->setPostponeOrder(d->POSTPONEORDER);
    ps->getParameterComponentManager()->getCSVOrderImportRepository()->saveCSCOrderImportCSVFormats(format);

    //return structur with new ID
    d->CSCORDERIMPORTFORMATID = format->getCSCOrderImportFormatID();
    return 0;
}

/*************************************************************************/
// AasrvUpdateCSCOrderImportCSVFormats
/*************************************************************************/
int AasrvUpdateCSCOrderImportCSVFormats(cscorderimportcsvformatsS *d, char * /*error_msg*/)
{
    libcsc::parameter::ICSCOrderImportCSVFormatsPtr format;
    ps->getParameterComponentManager()->getCSVOrderImportRepository()->reset();
    format = ps->getParameterComponentManager()->getCSVOrderImportRepository()->findCSCOrderImportCSVFormatsById(d->CSCORDERIMPORTFORMATID);
    if (NULL != format.get())
    {
        basar::VarString FomatName(d->CSVFORMATNAME);
        FomatName.trim();
        format->setCSVFormatName(FomatName);
        format->setDataStartingLine(d->DATASTARTINGLINE);
        format->setPostponeOrder(d->POSTPONEORDER);
        ps->getParameterComponentManager()->getCSVOrderImportRepository()->saveCSCOrderImportCSVFormats(format);
    }
    return 0;
}

/*************************************************************************/
// AasrvInsertCSCOrderImportCSVColumns
/*************************************************************************/
int AasrvInsertCSCOrderImportCSVColumns(cscorderimportcsvcolumnsS *d, char * /*error_msg*/)
{
    libcsc::parameter::ICSCOrderImportCSVFormatsPtr format;
    ps->getParameterComponentManager()->getCSVOrderImportRepository()->reset();
    format = ps->getParameterComponentManager()->getCSVOrderImportRepository()->findCSCOrderImportCSVFormatsById(d->CSCORDERIMPORTFORMATID);
    if (NULL != format.get())
    {
        format->addCSCOrderImportCSVColums(d->COLUMNNO,d->FIELDNAMEID,d->GROUPING);
        ps->getParameterComponentManager()->getCSVOrderImportRepository()->saveCSCOrderImportCSVFormats(format);
    }
    return 0;
}

/*************************************************************************/
// AasrvCSCOrderImport
/*************************************************************************/
int AasrvCSCOrderImport(cscorderimportcsvfileS *d, char * error_msg)
{
    int rc;
    sprintf(error_msg, "%s", "Test");
    basar::VarString DateiName(d->DATEINAME);
    DateiName.trim();
    basar::VarString DateiNameOrg(d->DATEINAMEORG);
    DateiNameOrg.trim();
    sprintf(d->CSVLOGFILE,"%*.*slog", (int)(DateiName.length() - 3), (int)(DateiName.length() - 3), DateiName.c_str());
    getSession().Device()->Type(pxDVC_DCT_SERIAL);

    // Hier Verarbeitung
    CSCOrderImport orderimport(*ps);
    rc = orderimport.GenerateOrders(DateiName, d->CSVLOGFILE, DateiNameOrg, d->CSVREPORTFILE, d->CSCORDERIMPORTFORMATID, d->CSVFORMATNAME, d->LANGUAGE);
    getSession().Device()->Type(pxDVC_VIDEO_WORKSTATION);
    if (rc == OrdImpRCFormatNotFound)
    {
        basar::VarString msg = orderimport.GetMessage(CMSG_ORDIMPORT_GETFORMAT_FAILURE);
        basar::VarString err = "";
        err.format(msg.c_str(), d->CSCORDERIMPORTFORMATID, d->CSVFORMATNAME);
        AllgStrCopy(d->CSVFEHLERTEXT, err.c_str(), L_CSCORDERIMPORTCSVFILE_CSVFEHLERTEXT);  //kann eigentlich nicht sein
        d->FEHLER = OrdImpRCFormatNotFound;
        return 0;
    }
    if (rc == OrdImpRCInputFileFailed)
    {
        basar::VarString msg = orderimport.GetMessage(CMSG_ORDIMPORT_OPEN_FILE_ERROR);
        basar::VarString err = "";
        err.format(msg.c_str(), d->DATEINAME);
        AllgStrCopy(d->CSVFEHLERTEXT, err.c_str(), L_CSCORDERIMPORTCSVFILE_CSVFEHLERTEXT);  //kann eigentlich nicht sein
        d->FEHLER = OrdImpRCInputFileFailed;
        return 0;
    }
    if (rc == OrdImpRCReportFileFailed)
    {
        basar::VarString msg = orderimport.GetMessage(CMSG_ORDIMPORT_OPEN_FILE_ERROR);
        basar::VarString err = "";
        err.format(msg.c_str(), d->CSVREPORTFILE);
        AllgStrCopy(d->CSVFEHLERTEXT, err.c_str(), L_CSCORDERIMPORTCSVFILE_CSVFEHLERTEXT);  //kann eigentlich nicht sein
        d->FEHLER = OrdImpRCReportFileFailed;
        return 0;
    }
    if (rc == OrdImpRCCreateOrdersError)
    {
        basar::VarString msg = orderimport.GetMessage(CMSG_ORDIMPORT_CREATE_ORDERS_FAILED);
        basar::VarString err = "";
        err.format(msg.c_str(), d->CSVREPORTFILE);
        AllgStrCopy(d->CSVFEHLERTEXT, err.c_str(), L_CSCORDERIMPORTCSVFILE_CSVFEHLERTEXT);
        d->FEHLER = OrdImpRCCreateOrdersError;
        return 0;
    }
    if (rc == OrdImpRCWrongFormat)
    {
        basar::VarString msg = orderimport.GetMessage(CMSG_ORDIMPORT_IMPORT_FORMAT_FAILED);
        basar::VarString err = "";
        err.format(msg.c_str(), d->DATEINAME, d->CSCORDERIMPORTFORMATID, d->CSVFORMATNAME);
        AllgStrCopy(d->CSVFEHLERTEXT, err.c_str(), L_CSCORDERIMPORTCSVFILE_CSVFEHLERTEXT);
        d->FEHLER = OrdImpRCWrongFormat;
        return 0;
    }

    return 0;
}

/*************************************************************************/
// AasrvUpdateCscOrderType
/*************************************************************************/
int AasrvUpdateCscOrderType(auftragsartS *d, char * error_msg)
{
    basar::VarString AufArt(d->KDAUFTRAGART);
    AufArt.trim();
    if (AufArt.empty() || d->BRANCHNO == 0)
    {
        strncpy(error_msg, "ordertype/branchno empty!", MAX_ERROR_MSG_AE);
        return -2;
    }
    libcsc::cscordertype::ICSCOrderTypePtr orderType;
//  ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->reset();
    orderType = ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->findOrderType(d->BRANCHNO, AufArt);
    orderType->setDescription(d->BEZEICHNUNG);
    orderType->setGlobal(d->SGLOBAL[0] == '1');
    orderType->setNatra(d->SKDAUFTRAGARTNATRA[0] == '1');
    orderType->setNetto(d->SKDAUFTRAGARTNETTO[0] == '1');
    orderType->setBild(d->SBILDSCHIRM[0] == '1');
    orderType->setHand(d->DISINKINDENTERABLE[0] == '1');
    orderType->setDafue(d->SDAFUE[0] == '1');
    orderType->setDiscount(d->SDISCOUNTABLE[0] == '1');
    orderType->setStandard(d->SSTANDARD[0] == '1');
    orderType->setMuss(d->SMUSTSUBORDER[0] == '1');
    orderType->setFreePrice(d->SFREEPRICE[0] == '1');
    orderType->setAufCons(d->SORDERCONS[0] == '1');
    orderType->setAufNachl(d->SRESTDEL[0] == '1');
    orderType->setNoQuota(d->SNOQUOTA[0] == '1');
    orderType->setDeferOrder(d->SDEFERORDER[0] == '1');
    orderType->setNoPart(d->SNOPARTQTY[0] == '1');
    orderType->setNoDD(d->SNODD[0] == '1');
    orderType->setOnlyEH(d->SONLYEH[0] == '1');
    orderType->setIVC(d->SIVCVOUCHERNO == 1);
    orderType->setOrgInvoice(d->SORIGINALINVOICENO == 1);
    orderType->setNoPromo(d->SNOPROMOTIONS == 1);
    orderType->setDefaultKennung(d->SDEFAULTKENNUNG == 1);
    orderType->setStockreservation(d->STOCKRESERVATION == 1);
//  orderType->getBatchConfig()->setBranchNo(d->BRANCHNO);
//  orderType->getBatchConfig()->setOrderType(AufArt);
    orderType->getBatchConfig()->setAllowDesiredBatch(d->ALLOWDESIREDBATCH == 1);
    orderType->getBatchConfig()->setAllowFixedBatch(d->ALLOWFIXEDBATCH == 1);
    orderType->getBatchConfig()->setForbidUserChange(d->FORBIDUSERCHANGE == 1);

    ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->saveOrderType(orderType);

    return 0;
}

/*************************************************************************/
// AasrvInsertCscOrderType
/*************************************************************************/
int AasrvInsertCscOrderType(auftragsartS *d, char * error_msg)
{
    basar::VarString AufArt(d->KDAUFTRAGART);
    AufArt.trim();
    if (AufArt.empty() || d->BRANCHNO == 0)
    {
        strncpy(error_msg, "ordertype/branchno empty!", MAX_ERROR_MSG_AE);
        return -2;
    }
    libcsc::cscordertype::ICSCOrderTypePtr orderType;
//  ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->reset();
    orderType = ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->createOrderType();
    orderType->setBranchNo(d->BRANCHNO);
    orderType->setOrderType(AufArt);
    orderType->setDescription(d->BEZEICHNUNG);
    orderType->setGlobal(d->SGLOBAL[0] == '1');
    orderType->setNatra(d->SKDAUFTRAGARTNATRA[0] == '1');
    orderType->setNetto(d->SKDAUFTRAGARTNETTO[0] == '1');
    orderType->setBild(d->SBILDSCHIRM[0] == '1');
    orderType->setHand(d->DISINKINDENTERABLE[0] == '1');
    orderType->setDafue(d->SDAFUE[0] == '1');
    orderType->setDiscount(d->SDISCOUNTABLE[0] == '1');
    orderType->setStandard(d->SSTANDARD[0] == '1');
    orderType->setMuss(d->SMUSTSUBORDER[0] == '1');
    orderType->setFreePrice(d->SFREEPRICE[0] == '1');
    orderType->setAufCons(d->SORDERCONS[0] == '1');
    orderType->setAufNachl(d->SRESTDEL[0] == '1');
    orderType->setNoQuota(d->SNOQUOTA[0] == '1');
    orderType->setDeferOrder(d->SDEFERORDER[0] == '1');
    orderType->setNoPart(d->SNOPARTQTY[0] == '1');
    orderType->setNoDD(d->SNODD[0] == '1');
    orderType->setOnlyEH(d->SONLYEH[0] == '1');
    orderType->setIVC(d->SIVCVOUCHERNO == 1);
    orderType->setOrgInvoice(d->SORIGINALINVOICENO == 1);
    orderType->setNoPromo(d->SNOPROMOTIONS == 1);
    orderType->setDefaultKennung(d->SDEFAULTKENNUNG == 1);
    orderType->setStockreservation(d->STOCKRESERVATION == 1);
    orderType->getBatchConfig()->setBranchNo(d->BRANCHNO);
    orderType->getBatchConfig()->setOrderType(AufArt);
    orderType->getBatchConfig()->setAllowDesiredBatch(d->ALLOWDESIREDBATCH == 1);
    orderType->getBatchConfig()->setAllowFixedBatch(d->ALLOWFIXEDBATCH == 1);
    orderType->getBatchConfig()->setForbidUserChange(d->FORBIDUSERCHANGE == 1);

    ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->saveOrderType(orderType);

    return 0;
}

/*************************************************************************/
// AasrvSelAllCscOrderType
/*************************************************************************/
int AasrvSelAllCscOrderType(auftragsartS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = 0;
    static libcsc::cscordertype::CSCOrderTypeCollectionPtr types;
    if (0 == anz)
    {
        ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->reset();
        types = ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->findOrderTypes(d->BRANCHNO);
        if (types->empty())
        {
            anz = 0;
            types.reset();
            return 1;
        }
        maxanz = types->size();
    }
    if (anz >= maxanz)   // Ende der Liste
    {
        anz = 0;
        types.reset();
        return 1;
    }
    libcsc::cscordertype::ICSCOrderTypePtr type = types->at(anz);
    if (type.get())
    {
        strncpy(d->KDAUFTRAGART, type->getOrderType().c_str(), L_AUFTRAGSART_KDAUFTRAGART);
        d->ALLOWDESIREDBATCH = (type->getBatchConfig()->getAllowDesiredBatch() ? 1 : 0);
        d->ALLOWFIXEDBATCH = (type->getBatchConfig()->getAllowFixedBatch() ? 1 : 0);
        strncpy(d->BEZEICHNUNG, type->getDescription().c_str(), L_AUFTRAGSART_BEZEICHNUNG);
        d->FORBIDUSERCHANGE = (type->getBatchConfig()->getForbidUserChange() ? 1 : 0);
        d->SKDAUFTRAGARTNATRA[0] = (type->getNatra() ? '1' : '0');
        d->SKDAUFTRAGARTNETTO[0] = (type->getNetto() ? '1' : '0');
        d->SGLOBAL[0] = (type->getGlobal() ? '1' : '0');
        d->SBILDSCHIRM[0] = (type->getBild() ? '1' : '0');
        d->SDAFUE[0] = (type->getDafue() ? '1' : '0');
        d->SSTANDARD[0] = (type->getStandard() ? '1' : '0');
        d->BRANCHNO = type->getBranchNo();
        d->DISINKINDENTERABLE[0] = (type->getHand() ? '1' : '0');
        d->SDISCOUNTABLE[0] = (type->getDiscount() ? '1' : '0');
        d->SMUSTSUBORDER[0] = (type->getMuss() ? '1' : '0');
        d->SFREEPRICE[0] = (type->getFreePrice() ? '1' : '0');
        d->SORDERCONS[0] = (type->getAufCons() ? '1' : '0');
        d->SRESTDEL[0] = (type->getAufNachl() ? '1' : '0');
        d->SNOQUOTA[0] = (type->getNoQuota() ? '1' : '0');
        d->SNOPARTQTY[0] = (type->getNoPart() ? '1' : '0');
        d->SDEFERORDER[0] = (type->getDeferOrder() ? '1' : '0');
        d->SNODD[0] = (type->getNoDD() ? '1' : '0');
        d->SONLYEH[0] = (type->getOnlyEH() ? '1' : '0');
        d->SNOPROMOTIONS = (type->getNoPromo() ? 1 : 0);
        d->SDEFAULTKENNUNG = (type->getDefaultKennung() ? 1 : 0);
        d->SIVCVOUCHERNO = (type->getIVC() ? 1 : 0);
        d->SORIGINALINVOICENO = (type->getOrgInvoice() ? 1 : 0);
        d->STOCKRESERVATION = (type->getStockreservation() ? 1 : 0);
        d->SCONSULTATIONNEEDED = (type->isFlagSet(libcsc::cscordertype::CONSULTATION_FOR_MSV3_RETURNS_NECESSARY) ? 1 : 0);
        d->SNOLINEFEE = (type->isFlagSet(libcsc::cscordertype::NO_LINEFEE_CALCULATION) ? 1 : 0);
        d->SNOPACKAGEFEE = (type->isFlagSet(libcsc::cscordertype::NO_PACKAGEFEE_CALCULATION) ? 1 : 0);
        d->SMUSTHEADLINE = (type->isFlagSet(libcsc::cscordertype::MUST_HEADLINE) ? 1 : 0);
        ++anz;
        return 0;
    }
    anz = 0;
    types.reset();
    return 1;
}

/*************************************************************************/
// AasrvDelCscOrderType
/*************************************************************************/
int AasrvDelCscOrderType(auftragsartS *d, char * /*error_msg*/)
{
    libcsc::cscordertype::ICSCOrderTypePtr orderType;
    ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->reset();
    orderType = ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->findOrderType(d->BRANCHNO, d->KDAUFTRAGART);
    if (NULL != orderType.get() && orderType->isClean())
    {
        ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->deleteOrderType(orderType);
    }
    return 1;
}

/*************************************************************************/
// AasrvSelCscOrderType
/*************************************************************************/
int AasrvSelCscOrderType(auftragsartS *d, char * /*error_msg*/)
{
    libcsc::cscordertype::ICSCOrderTypePtr orderType;
    ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->reset();
    orderType = ps->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->findOrderType(d->BRANCHNO,d->KDAUFTRAGART);
    if (NULL != orderType.get())
    {
        strncpy(d->KDAUFTRAGART, orderType->getOrderType().c_str(), L_AUFTRAGSART_KDAUFTRAGART);
        d->ALLOWDESIREDBATCH = (orderType->getBatchConfig()->getAllowDesiredBatch() ? 1 : 0);
        d->ALLOWFIXEDBATCH = (orderType->getBatchConfig()->getAllowFixedBatch() ? 1 : 0);
        strncpy(d->BEZEICHNUNG, orderType->getDescription().c_str(), L_AUFTRAGSART_BEZEICHNUNG);
        d->FORBIDUSERCHANGE = (orderType->getBatchConfig()->getForbidUserChange() ? 1 : 0);
        d->SKDAUFTRAGARTNATRA[0] = (orderType->getNatra() ? '1' : '0');
        d->SKDAUFTRAGARTNETTO[0] = (orderType->getNetto() ? '1' : '0');
        d->SGLOBAL[0] = (orderType->getGlobal() ? '1' : '0');
        d->SBILDSCHIRM[0] = (orderType->getBild() ? '1' : '0');
        d->SDAFUE[0] = (orderType->getDafue() ? '1' : '0');
        d->SSTANDARD[0] = (orderType->getStandard() ? '1' : '0');
        d->BRANCHNO = orderType->getBranchNo();
        d->DISINKINDENTERABLE[0] = (orderType->getHand() ? '1' : '0');
        d->SDISCOUNTABLE[0] = (orderType->getDiscount() ? '1' : '0');
        d->SMUSTSUBORDER[0] = (orderType->getMuss() ? '1' : '0');
        d->SFREEPRICE[0] = (orderType->getFreePrice() ? '1' : '0');
        d->SORDERCONS[0] = (orderType->getAufCons() ? '1' : '0');
        d->SRESTDEL[0] = (orderType->getAufNachl() ? '1' : '0');
        d->SNOQUOTA[0] = (orderType->getNoQuota() ? '1' : '0');
        d->SNOPARTQTY[0] = (orderType->getNoPart() ? '1' : '0');
        d->SDEFERORDER[0] = (orderType->getDeferOrder() ? '1' : '0');
        d->SNODD[0] = (orderType->getNoDD() ? '1' : '0');
        d->SONLYEH[0] = (orderType->getOnlyEH() ? '1' : '0');
        d->SNOPROMOTIONS = (orderType->getNoPromo() ? 1 : 0);
        d->SDEFAULTKENNUNG = (orderType->getDefaultKennung() ? 1 : 0);
        d->SIVCVOUCHERNO = (orderType->getIVC() ? 1 : 0);
        d->SORIGINALINVOICENO = (orderType->getOrgInvoice() ? 1 : 0);
        d->STOCKRESERVATION = (orderType->getStockreservation() ? 1 : 0);
        d->SCONSULTATIONNEEDED = (orderType->isFlagSet(libcsc::cscordertype::CONSULTATION_FOR_MSV3_RETURNS_NECESSARY) ? 1 : 0);
        d->SNOLINEFEE = (orderType->isFlagSet(libcsc::cscordertype::NO_LINEFEE_CALCULATION) ? 1 : 0);
        d->SNOPACKAGEFEE = (orderType->isFlagSet(libcsc::cscordertype::NO_PACKAGEFEE_CALCULATION) ? 1 : 0);
        d->SMUSTHEADLINE = (orderType->isFlagSet(libcsc::cscordertype::MUST_HEADLINE) ? 1 : 0);
        return 0;
    }
    return 1;
}

/*************************************************************************/
// AasrvSelDeliveryAdviceHead
/*************************************************************************/
int AasrvSelDeliveryAdviceHead(deliveryadviceheadS *d, char * /*error_msg*/)
{
    libcsc::document::DeliveryAdviceInformationFilter filter;
    libcsc::document::DeliveryAdviceKey key;
    filter.SendTotals = true;
    filter.SendLineInformation = true;
    filter.SendLineDiscountInformation = true;
    filter.SendLinePickingInformation = true;
    filter.SendLineReturn = true;
    filter.SendCustomerInformation = true;
    key.branchNo = d->BRANCHNO;
    key.customerNo = d->CUSTOMERNO;
    key.deliveryAdviceDate = d->DELIVERYADVICEDATE;
    key.deliveryAdviceNo = d->DELIVERYADVICENO;
    bool incrementRequestCounter = false;
    bool completedOnly = true;
    deliveryadvicehead = ps->getDocumentComponentManager()->getDeliveryAdviceRepository()->findDeliveryAdvice(key, filter, incrementRequestCounter, completedOnly);
    if (NULL != deliveryadvicehead.get())
    {
        strncpy(d->KDAUFTRAGART, deliveryadvicehead->getOrderType().c_str(), L_DELIVERYADVICEHEAD_KDAUFTRAGART);
        strncpy(d->PICKINGTYPE, deliveryadvicehead->getPickingType().c_str(), L_DELIVERYADVICEHEAD_PICKINGTYPE);
        strncpy(d->BOOKINGTYPE, deliveryadvicehead->getBookingType().c_str(), L_DELIVERYADVICEHEAD_BOOKINGTYPE);
        d->PHARMOSORDERNO = deliveryadvicehead->getPharmosOrderNo();
        d->CSCORDERNO = deliveryadvicehead->getCscOrderNo();
        strncpy(d->COMPLETED, deliveryadvicehead->getCompleted().c_str(), L_DELIVERYADVICEHEAD_COMPLETED);
        strncpy(d->SPECIALDOCUMENTTYPE, deliveryadvicehead->getSpecialDocumentType().c_str(), L_DELIVERYADVICEHEAD_SPECIALDOCUMENTTYPE);
        strncpy(d->TOURID, deliveryadvicehead->getTourId().c_str(), L_DELIVERYADVICEHEAD_TOURID);
        if (deliveryadvicehead->getDueDate().isValid())
        {
            d->DUEDATE = deliveryadvicehead->getDueDate().getDate();
        }
        else
        {
            d->DUEDATE = 0;
        }
        d->REQUESTED = deliveryadvicehead->getRequested();
        d->CONFIRMED = deliveryadvicehead->getConfirmed();
        strncpy(d->ORDERLABEL, deliveryadvicehead->getOrderLabel().c_str(), L_DELIVERYADVICEHEAD_ORDERLABEL);
        d->CANCELLED = deliveryadvicehead->getCancelled();
        d->DEPOSITVALUE = deliveryadvicehead->getDepositValue().toFloat64();
        d->LOGISTICSERVICECOST = deliveryadvicehead->getLogisticServiceCost().toFloat64();
        d->BATCHCORRECTIONADVICE = deliveryadvicehead->getBatchCorrectionAdvice();
        strncpy(d->CONTRACTID, deliveryadvicehead->getContractId().c_str(), L_DELIVERYADVICEHEAD_CONTRACTID);
        return 0;
    }
    return 1;
}

/*************************************************************************/
// AasrvSelDeliveryAdviceVATTotals
/*************************************************************************/
int AasrvSelDeliveryAdviceVATTotals(deliveryadvicevattotalsS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = deliveryadvicehead->getDeliveryAdviceVatTotalsCollection()->size();
    static libcsc::document::DeliveryAdviceVatTotalsCollection::const_iterator vatIt;
    if (maxanz == 0)    //keine Saetze vorhanden
    {
        return 1;
    }
    if (0 == anz)
    {
        if(deliveryadvicehead->getDeliveryAdviceVatTotalsCollection()->empty()) return 1;
        vatIt = deliveryadvicehead->getDeliveryAdviceVatTotalsCollection()->begin();
        anz = 1;
    }
    if (vatIt != deliveryadvicehead->getDeliveryAdviceVatTotalsCollection()->end())   // Ende der Liste
    {
        strncpy(d->DAVAT, (*vatIt)->getVat().c_str(), L_DELIVERYADVICEVATTOTALS_DAVAT);
        d->VATPERCENTAGE = (*vatIt)->getVatPercentage().toFloat64();
        d->NETVALUE = (*vatIt)->getNetValue().toFloat64();
        d->VATVALUE = (*vatIt)->getVatValue().toFloat64();
        vatIt++;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*************************************************************************/
// AasrvSelDeliveryAdviceLine
/*************************************************************************/
int AasrvSelDeliveryAdviceLine(deliveryadvicelineS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static int maxanz = deliveryadvicehead->getDeliveryAdviceLineCollection()->size();
    static libcsc::document::DeliveryAdviceLineCollection::const_iterator lineIt;
    if (maxanz == 0)    //keine Saetze vorhanden
    {
        return 1;
    }
    if (0 == anz)
    {
        lineIt = deliveryadvicehead->getDeliveryAdviceLineCollection()->begin();
        anz = 1;
    }
    if (lineIt != deliveryadvicehead->getDeliveryAdviceLineCollection()->end())   // Ende der Liste
    {
        strncpy(d->DAVAT, (*lineIt)->getVat().c_str(), L_DELIVERYADVICELINE_DAVAT);
        d->LOGISTICSERVICECOST = (*lineIt)->getLogisticServiceCost().toFloat64();
        d->DELIVERYADVICEPOSNO = (*lineIt)->getDeliveryAdvicePosNo();
        d->PHARMOSORDERPOSNO = (*lineIt)->getPharmosOrderPosNo();
        d->CSCORDERPOSNO = (*lineIt)->getCscOrderPosNo();
        d->ARTICLENO = (*lineIt)->getArticleNo();
        strncpy(d->ARTICLE_CODE, (*lineIt)->getArticleCode().c_str(), L_DELIVERYADVICELINE_ARTICLE_CODE);
        d->QTY_ORDERED = (*lineIt)->getQuantityOrdered();
        d->QTY_CONFIRMED = (*lineIt)->getQuantityConfirmed();
        d->QTY_REBATEINKIND = (*lineIt)->getQuantityRebateInKind();
        d->QTY_INVOICED = (*lineIt)->getQuantityInvoiced();
        strncpy(d->LINEREFERENCE, (*lineIt)->getLineReference().c_str(), L_DELIVERYADVICELINE_LINEREFERENCE);
        d->DAINVOICEDPRICE = (*lineIt)->getInvoicedPrice().toFloat64();
        d->MINLOGISTICSERVICECOSTVALUE = (*lineIt)->getMinLogisticServiceCostValue().toFloat64();
        d->LINETYPE = static_cast<short>((*lineIt)->getLineType());
        strncpy(d->DAARTICLENAME, (*lineIt)->getArticleName().c_str(), L_DELIVERYADVICELINE_DAARTICLENAME);
        strncpy(d->ARTICLEUNIT, (*lineIt)->getArticleUnit().c_str(), L_DELIVERYADVICELINE_ARTICLEUNIT);
        strncpy(d->PHARMACEUTICALFORM, (*lineIt)->getPharmaceuticalForm().c_str(), L_DELIVERYADVICELINE_PHARMACEUTICALFORM);
        d->DABASEPRICE = (*lineIt)->getBasePrice().toFloat64();
        lineIt++;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*************************************************************************/
// AasrvSelDeliveryAdviceLineDetails
/*************************************************************************/
int AasrvSelDeliveryAdviceLineDetails(deliveryadvicelinedetailsS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static libcsc::document::DeliveryAdviceLineCollectionPtr lines;
    static libcsc::document::DeliveryAdviceLinePtr line;
    static libcsc::document::DeliveryAdviceLineDetailsCollection::const_iterator lineIt;
    if (0 == anz)
    {
        lines = deliveryadvicehead->getDeliveryAdviceLineCollection();
        if (lines == NULL) return 1;
        line = lines->at(d->DELIVERYPOSNO);
        if (line->getDetailsCollection()->empty()) return 1;
        lineIt = line->getDetailsCollection()->begin();
        anz = 1;
    }
    if (lineIt != line->getDetailsCollection()->end())   // Ende der Liste
    {
        d->BRANCHNO = (*lineIt)->getBranchNo();
        d->CUSTOMERNO = (*lineIt)->getCustomerNo();
        d->DELIVERYADVICEDATE = (*lineIt)->getDeliveryAdviceDate().getDate();
        d->PHARMOSORDERNO = (*lineIt)->getPharmosOrderNo();
        d->PHARMOSORDERPOSNO = (*lineIt)->getPharmosOrderPosNo();
        d->QTY_DELIVERY = (*lineIt)->getQuantityDelivery();
        strncpy(d->BATCH, (*lineIt)->getBatch().c_str(), L_DELIVERYADVICELINEDETAILS_BATCH);
        if ((*lineIt)->getExpiryDate().isValid())
        {
            d->EXPIRYDATE = (*lineIt)->getExpiryDate().getDate();
        }
        else
        {
            d->EXPIRYDATE = 0;
        }
        d->PACKAGEID = (*lineIt)->getPackageId();
        strncpy(d->TRACKINGID, (*lineIt)->getTrackingId().c_str(), L_DELIVERYADVICELINEDETAILS_TRACKINGID);
        d->QTY_LACK = (*lineIt)->getQuantityLack();
        d->DELIVERYPOSNO = (*lineIt)->getDeliveryPosNo();
        lineIt++;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*************************************************************************/
// AasrvSelDeliveryAdviceLineDiscount
/*************************************************************************/
int AasrvSelDeliveryAdviceLineDiscount(deliveryadvicelinediscountsS *d, char * /*error_msg*/)
{
//  return 1;
    static int anz = 0;
    static libcsc::document::DeliveryAdviceLineCollectionPtr lines;
    static libcsc::document::DeliveryAdviceLinePtr line;
    static libcsc::document::DeliveryAdviceLineDiscountCollection::const_iterator lineIt;
    if (0 == anz)
    {
        lines = deliveryadvicehead->getDeliveryAdviceLineCollection();
        if (lines == NULL) return 1;
        line = lines->at(d->DELIVERYADVICEPOSNO);
        if (line->getDiscountCollection()->empty()) return 1;
        lineIt = line->getDiscountCollection()->begin();
        anz = 1;
    }
    if (lineIt != line->getDiscountCollection()->end())   // Ende der Liste
    {
        d->BRANCHNO = (*lineIt)->getBranchNo();
        d->CUSTOMERNO = (*lineIt)->getCustomerNo();
        d->DELIVERYADVICEDATE = (*lineIt)->getDeliveryAdviceDate().getDate();
        strncpy(d->DELIVERYADVICENO, line->getDeliveryAdviceNo().c_str(), L_DELIVERYADVICELINEDISCOUNTS_DELIVERYADVICENO);
        d->DELIVERYADVICEPOSNO = line->getDeliveryAdvicePosNo();
        d->DISCOUNTMODE = (*lineIt)->getDiscountMode();
        strncpy(d->DISCOUNTMODENAME, (*lineIt)->getDiscountModeName().c_str(), L_DELIVERYADVICELINEDISCOUNTS_DISCOUNTMODENAME);
        d->DISCOUNT = (*lineIt)->getDiscount().toFloat64();
        strncpy(d->DAORIGIN, (*lineIt)->getOrigin().c_str(), L_DELIVERYADVICELINEDISCOUNTS_DAORIGIN);
        d->DELETEREASON = (*lineIt)->getDeleteReason();
        d->DADISCOUNTVALUE = (*lineIt)->getDiscountValue().toFloat64();
        d->DISCOUNTTYPE = (*lineIt)->getDiscountType();
        d->HIERARCHY = (*lineIt)->getHierarchy();
        d->CALCULATIONBASIS = (*lineIt)->getCalculationBasis();
        lineIt++;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*************************************************************************/
// AasrvSelDeliveryAdviceLineIBTLink
/*************************************************************************/
int AasrvSelDeliveryAdviceLineIBTLink(deliveryadvicelineibtlinkS *d, char * /*error_msg*/)
{
    static libcsc::document::DeliveryAdviceLineCollectionPtr lines;
    static libcsc::document::DeliveryAdviceLinePtr line;
    static libcsc::document::DeliveryAdviceLineIbtLinkPtr ibtLink;

    lines = deliveryadvicehead->getDeliveryAdviceLineCollection();
    if (lines == NULL)
        return 1;
    line = lines->at(d->DELIVERYADVICEPOSNO);
    ibtLink = line->getIbtLink();
    if (ibtLink == NULL)
        return 1;

    d->BRANCHNO = ibtLink->getBranchNo();
    d->CUSTOMERNO = ibtLink->getCustomerNo();
    d->DELIVERYADVICEDATE = ibtLink->getDeliveryAdviceDate().getDate();
    strncpy(d->DELIVERYADVICENO, ibtLink->getDeliveryAdviceNo().c_str(), L_DELIVERYADVICELINEIBTLINK_DELIVERYADVICENO);
    d->DELIVERYADVICEPOSNO = ibtLink->getDeliveryAdvicePosNo();
    d->CSCORDERNO = ibtLink->getCscOrderNo();
    d->CSCORDERPOSNO = ibtLink->getCscOrderPosNo();
    d->IBTBRANCHNO = ibtLink->getIbtBranchNo();
    d->IBTCUSTOMERNO = ibtLink->getIbtCustomerNo();
    d->IBTDELIVERYADVICEDATE = ibtLink->getIbtDeliveryAdviceDate().getDate();
    strncpy(d->IBTDELIVERYADVICENO, ibtLink->getIbtDeliveryAdviceNo().c_str(), L_DELIVERYADVICELINEIBTLINK_IBTDELIVERYADVICENO);
    d->IBTDELIVERYADVICEPOSNO = ibtLink->getIbtDeliveryAdvicePosNo();
    d->IBTCSCORDERNO = ibtLink->getIbtCscOrderNo();
    d->IBTCSCORDERPOSNO = ibtLink->getIbtCscOrderPosNo();
    return 0;
}

/*************************************************************************/
// AasrvSelDeliveryAdviceLineReturn
/*************************************************************************/
int AasrvSelDeliveryAdviceLineReturn(deliveryadvicelinereturnS *d, char * /*error_msg*/)
{
//  return 1;
    static int anz = 0;
    static libcsc::document::DeliveryAdviceLineCollectionPtr lines;
    static libcsc::document::DeliveryAdviceLinePtr line;
    static libcsc::document::DeliveryAdviceLineReturnCollection::const_iterator lineIt;
    if (0 == anz)
    {
        lines = deliveryadvicehead->getDeliveryAdviceLineCollection();
        if (lines == NULL) return 1;
        line = lines->at(d->DELIVERYADVICEPOSNO);
        if (line->getReturnCollection()->empty()) return 1;
        lineIt = line->getReturnCollection()->begin();
        anz = 1;
    }
    if (lineIt != line->getReturnCollection()->end())   // Ende der Liste
    {
        d->BRANCHNO = (*lineIt)->getBranchNo();
        d->CUSTOMERNO = (*lineIt)->getCustomerNo();
        d->DELIVERYADVICEDATE = (*lineIt)->getDeliveryAdviceDate().getDate();
        strncpy(d->DELIVERYADVICENO, (*lineIt)->getDeliveryAdviceNo().c_str(), L_DELIVERYADVICELINEDISCOUNTS_DELIVERYADVICENO);
        d->DELIVERYADVICEPOSNO = (*lineIt)->getDeliveryAdvicePosNo();
        d->BLOCKEDFORRETURNS = (*lineIt)->getBlockedForreturns();
        d->QTY_RETURNED = (*lineIt)->getQuantityReturned();
        d->QTY_RETURNED_REBATEINKIND = (*lineIt)->getQuantityReturnedRebateInKind();
        d->QTY_RETURN_REJECTED = (*lineIt)->getQuantityReturnRejected();
        lineIt++;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*************************************************************************/
// AasrvSelDeliveryAdviceRemarks
/*************************************************************************/
int AasrvSelDeliveryAdviceRemarks(deliveryadviceremarkS *d, char * /*error_msg*/)
{
    static int anz = 0;
    static libcsc::document::DeliveryAdviceLineCollectionPtr lines;
    static libcsc::document::DeliveryAdviceLinePtr line;
    static libcsc::document::DeliveryAdviceRemarksCollection::const_iterator lineIt;
    if (0 == anz)
    {
        lines = deliveryadvicehead->getDeliveryAdviceLineCollection();
        if (lines == NULL) return 1;
        line = lines->at(d->CSCORDERPOSNO);
        if (line->getRemarksCollection()->empty()) return 1;
        lineIt = line->getRemarksCollection()->begin();
        anz = 1;
    }
    if (lineIt != line->getRemarksCollection()->end())   // Ende der Liste
    {
        d->REMARKTYPE = static_cast<short>((*lineIt)->getRemarkType());
        strncpy(d->REMARKTEXT, (*lineIt)->getRemarkText().c_str(), L_DELIVERYADVICEREMARK_REMARKTEXT);
        lineIt++;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}

/*************************************************************************/
// AasrvGetDocumentLink
/*************************************************************************/
int AasrvGetDocumentLink(deliveryadvicedocumentS *d, char * /*error_msg*/)
{
    libcsc::document::DocumentArchiveInfoPtr deliveryadvicedocument;
    deliveryadvicedocument = ps->getDocumentComponentManager()->getDocumentArchiveInfoRepository()->findDocumentArchiveInfo(d->BRANCHNO,d->CUSTOMERNO, Invoice,d->DELIVERYADVICENO,d->DELIVERYADVICEDATE);
    if (NULL != deliveryadvicedocument.get())
    {
        strncpy(d->DOCUMENTLINK, deliveryadvicedocument->getDocumentLink().c_str(), L_DELIVERYADVICEDOCUMENT_DOCUMENTLINK);
        return 0;
    }
    return 1;
}

/*************************************************************************/
// AasrvGetBatchAdviceLink
/*************************************************************************/
int AasrvGetBatchAdviceLink(deliveryadvicedocumentS *d, char * /*error_msg*/)
{
    libcsc::document::DocumentArchiveInfoPtr deliveryadvicedocument;
    deliveryadvicedocument = ps->getDocumentComponentManager()->getDocumentArchiveInfoRepository()->findDocumentArchiveInfo(d->BRANCHNO, d->CUSTOMERNO, BatchChangeAdvice, d->DELIVERYADVICENO, d->DELIVERYADVICEDATE);
    if (NULL != deliveryadvicedocument.get())
    {
        strncpy(d->DOCUMENTLINK, deliveryadvicedocument->getDocumentLink().c_str(), L_DELIVERYADVICEDOCUMENT_DOCUMENTLINK);
        return 0;
    }
    return 1;
}

/*************************************************************************/
// AasrvSelTourDelay
/*************************************************************************/
int AasrvSelTourDelay(tourdelayS *d, char * /*error_msg*/)
{
    libcsc::shipmenttracking::ShipmentTrackingDataFilter filter;
    filter.SpecificTourID = d->TOURID;
    if (d->DATUMKOMMI > 0)
    {
        filter.PickingDate.setDate(basar::cmnutil::Date(d->DATUMKOMMI));
    }

    std::string exceptionMessage;
    try
    {
        libcsc::shipmenttracking::ShipmentTrackingTourInformationCollectionPtr shipmentTrackingTourInformationCollection =
        ps->getShipmentTrackingComponentManager()->getShipmentTrackingRepository()->findShipmentTracking(
            d->VERTRIEBSZENTRUMNR,
            d->KUNDENNR,
            filter
        );

        if (NULL != shipmentTrackingTourInformationCollection.get() &&
            shipmentTrackingTourInformationCollection->begin() != shipmentTrackingTourInformationCollection->end()
            )
        {
            // -----------------------------
            // take per default the 1st tour, used as the last fallback:
            libcsc::shipmenttracking::ShipmentTrackingTourInformationPtr tourInfo = shipmentTrackingTourInformationCollection->front();

            // ---------------------
            // remember redirections and handle them now:
            basar::VarString requiredTargetTour = filter.SpecificTourID;

            for (libcsc::shipmenttracking::ShipmentTrackingTourInformationCollection::const_iterator libcscTourIter = shipmentTrackingTourInformationCollection->begin();
                libcscTourIter != shipmentTrackingTourInformationCollection->end();
                libcscTourIter++
                )
            {
                libcsc::shipmenttracking::ShipmentTrackingTourInformationPtr libcscTourInformation = *libcscTourIter;

                if (libcscTourInformation->getTourData()->getTourId() == requiredTargetTour)
                {
                    bool hasValidPackage = false;

                    basar::VarString firstValidRedirection = "";

                    // found the requested tour, but check, if there is at least 1 valid package for this tour.
                    // If no, then take the first redirected package and then try to find the redirected tour.
                    for (libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollection::const_iterator libcscPackageIter = libcscTourInformation->getPackageInformationCollection()->begin();
                        libcscPackageIter != libcscTourInformation->getPackageInformationCollection()->end();
                        libcscPackageIter++
                        )
                    {
                        libcsc::shipmenttracking::ShipmentTrackingPackageInformationPtr packageInfo = *libcscPackageIter;

                        if (d->KDAUFTRAGNR > 0 &&
                            packageInfo->getPackageProperties()->getCscOrderNo() != d->KDAUFTRAGNR)
                        {
                            continue;
                        }

                        // Same checking logic apllies here, as in: ShipmentTrackingTourInformation::getValidPickingDateAndBarcodeList()

                        //if (packageInfo->getPackageProperties()->getToteDeletedAt().isValid())   <--> NOTE: taking deleted too, as we have seen a case with Mihai, where the only package was deleted, but then Deliverd according to ST-CSV StateId 45!
                        //{
                        //    continue;   // skip this tote, because it does not contribute to this Tour information's delivery tracking!
                        //}
                        if (packageInfo->getRedirectedToTourData().get() != NULL)
                        {
                            if (firstValidRedirection.empty())
                            {
                                firstValidRedirection = packageInfo->getRedirectedToTourData()->getTourId();
                            }

                            continue;   // skip this tote, because it does not contribute to this Tour information's delivery tracking!
                        }

                        // if the current package (tote) is not redirected, and has a valid barcode, then:
                        if (!packageInfo->getPackageProperties()->getTrackingBarcode().empty())
                        {
                            // ... then take this tour. I.e. only here we accept this tour:
                            hasValidPackage = true;
                            break;
                        }
                    }

                    if (hasValidPackage ||                              // <-- requested tour found, i.e. the tour in libcscTourInformation has a valid package. OR
                        firstValidRedirection.empty() ||                // <-- there is no redirection found at all
                        firstValidRedirection == filter.SpecificTourID  // <-- avoiding cyclic search
                        )
                    {
                        // found requested tour, or there is no redirection to use --> then take it and quit:
                        tourInfo = libcscTourInformation;
                        break;
                    }
                    else
                    {
                        // here, at this point it is true, that: (!hasValidPackage && !firstValidRedirection.empty()) AND we are not redirecting to the original searched tour: filter.SpecificTourID

                        // set the "request" to search for a new TourId --> the redirected one
                        requiredTargetTour = firstValidRedirection;

                        // Lt's start the search from beginning.
                        libcscTourIter = shipmentTrackingTourInformationCollection->begin();
                    }
                }
            }

            // ------------------
            // now we have a tour, with some fallbacks in this priority:
            // 1. the requested tour: filter.SpecificTourID
            // 2. redirected tour, if filter.SpecificTourID has no valid package
            // 3. first tour, if 1. and 2. failed....

            bool pannedTimeIsValid = tourInfo->getTourData()->getPlannedTimeOfArrival().isValid();
            bool deliveredAtIsValid = tourInfo->getEtaAndDeliveryData()->getDeliveredAt().isValid();
            bool etaIsValid = tourInfo->getEtaAndDeliveryData()->getEstimatedTimeOfArrival().isValid();

            if (!pannedTimeIsValid ||
                (!etaIsValid && !deliveredAtIsValid)
                )
            {
                if (!tourInfo->getEtaAndDeliveryData()->getDelayInfo().empty() &&
                    // Efficient way to check if std::string has only spaces:
                    // https://stackoverflow.com/questions/6444842/efficient-way-to-check-if-stdstring-has-only-spaces/36535031
                    tourInfo->getEtaAndDeliveryData()->getDelayInfo().find_first_not_of(' ') != std::string::npos
                    )
                {
                    sprintf(d->DELAYTEXT, "%s", tourInfo->getEtaAndDeliveryData()->getDelayInfo().c_str());
                    return 0;
                }

                return 1;
            }

            short delaymin = tourInfo->getEtaAndDeliveryData()->getDelayInMinutes();

            std::stringstream redrectionMsg;
            if (requiredTargetTour != filter.SpecificTourID)
            {
                redrectionMsg << " (Umgebucht auf: ";

                if (requiredTargetTour.length() == 6)
                {
                    redrectionMsg << requiredTargetTour.substr(0, 2) << ":" << requiredTargetTour.substr(2, 2) << "/" << requiredTargetTour.substr(4, 2);
                }
                else
                {
                    redrectionMsg << requiredTargetTour;
                }

                redrectionMsg << " Tour)";
            }

            short minh;     //für debug Zwecke
            short minm;
            short mins;
            short maxh;
            short maxm;
            short maxs;

            if (deliveredAtIsValid)
            {
                minh = tourInfo->getEtaAndDeliveryData()->getDeliveredAt().getHour();
                minm = tourInfo->getEtaAndDeliveryData()->getDeliveredAt().getMinute();
                mins = tourInfo->getEtaAndDeliveryData()->getDeliveredAt().getSec();

                sprintf(d->DELAYTEXT, "%02d:%02d, %d %%s %s%s",
                    minh,
                    minm,
                    delaymin,
                    tourInfo->getEtaAndDeliveryData()->getDelayInfo().c_str(),
                    redrectionMsg.str().c_str()
                );
            }
            else // ETA:
            {
                minh = tourInfo->getEtaAndDeliveryData()->getEstimatedTimeOfArrivalMin().getHour();
                minm = tourInfo->getEtaAndDeliveryData()->getEstimatedTimeOfArrivalMin().getMinute();
                mins = tourInfo->getEtaAndDeliveryData()->getEstimatedTimeOfArrivalMin().getSec();
                maxh = tourInfo->getEtaAndDeliveryData()->getEstimatedTimeOfArrivalMax().getHour();
                maxm = tourInfo->getEtaAndDeliveryData()->getEstimatedTimeOfArrivalMax().getMinute();
                maxs = tourInfo->getEtaAndDeliveryData()->getEstimatedTimeOfArrivalMax().getSec();

                sprintf(d->DELAYTEXT, "%02d:%02d - %02d:%02d, %d %%s %s%s",
                    minh,
                    minm,
                    maxh,
                    maxm,
                    delaymin,
                    tourInfo->getEtaAndDeliveryData()->getDelayInfo().c_str(),
                    redrectionMsg.str().c_str()
                );
            }

            return 0;
        }
    }
    catch (basar::Exception const& ex)
    {
            exceptionMessage = (ex.getStackTrace().size() > 0) ? ex.stackTrace() : ex.what();
    }
    catch (...)
    {
            exceptionMessage = "unknown exception.";
    }

    if (!exceptionMessage.empty())
    {
            std::stringstream ss;
            ss << "AasrvSelTourDelay(" << d->VERTRIEBSZENTRUMNR << ", " << d->KUNDENNR << ", " << filter << "): Get Shipment Tracking Info: " << std::endl << exceptionMessage;
            exceptionMessage = ss.str();

            BLOG_ERROR(libcsc::LoggerPool::getLoggerCallback(), exceptionMessage);
    }

    return 1;
}

/*************************************************************************/
/* AasrvDiscountMode                                                     */
/*************************************************************************/
int AasrvDiscountMode(struct AUFPOSBUCH* d, char* /*error_msg*/)
{

    libcsc::discount::IOrderPositionDiscountRepositoryPtr repo = ps->getOrderPositionDiscountRepository();

    if (!repo)
        return -2;

    libcsc::discount::OrderPositionDiscountListPtr list = repo->findByID(d->KDAUFTRAGNR, d->POSNR);
    d->DISCOUNTMODE = libcsc::discount::DM_UNSET;

    if (list && !list->empty())
    {
        boost::shared_ptr<libcsc::discount::OrderPositionDiscount> opdPtr = *(list->begin());

        if (opdPtr && opdPtr->isDiscountValid())
        {
            d->DISCOUNTMODE = opdPtr->getDiscountMode().get();
        }
    }

    return 0;
}              