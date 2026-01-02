/******************************************************************************/
/*                                                                            */
/* header  : ausrvfkt.cpp                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:04:55 2022                                         */
/* language: C/C++                                                            */
/* describe: functiondistributor for C/S                                      */
/*           don't change this file by yourself!                              */
/*                                                                            */
/******************************************************************************/

/* Version ********************************************************************/

const char * const SCCSID = "(#)Phoenix $Header: DadeProduceDistributor.cpp 41    08.04.13 12:48 developer $";

/* Precompiler ****************************************************************/

#ifndef BUF_DESC
#define BUF_DESC
#endif

/* Include ********************************************************************/

#include <stdio.h>
#include <string.h>
#include <memory.h>
#ifdef _OPEN_EDITION
#include <unistd.h>
#endif
#include <bufkon.h>
#include "ausrvfkt.h"
#include <dadedb.h>

/* Declaration ****************************************************************/

#ifndef __DADE_LOAD__
int DistributorFunPublic(const int iFunNo, char *spIn , char *spOut, int *ipLen);
#else
int DistributorFunPublic(const int iFunNo, void *spBuf, char *spOut, int *ipLen);
#endif

/* generated headerfiles ******************************************************/

/* _DEFINES__ */
/* _HEADER__ */
#include "artikel.h"
#include "auftraginfo.h"
#include "callback.h"
#include "callplanday.h"
#include "callplanmaintenance.h"
#include "callplanundertake.h"
#include "collectivorders.h"
#include "controlling.h"
#include "cremamailaddresses.h"
#include "customer.h"
#include "eilbotendruck.h"
#include "hersteller.h"
#include "msv3.h"
#include "orders.h"
#include "processcheck.h"
#include "promo.h"
#include "promoinfo.h"
#include "ranges.h"
#include "serviceorder.h"
#include "statistics.h"
#include "tender.h"
#include "touren.h"
#include "verbundcheck.h"
#include "filialpartner.h"
#include "mailsystem.h"
#include "cststockreservation.h"
/* _HEADER__ */

#ifdef __CPLUS__
extern "C" {
#endif
/* _DECLARATION__ */
retClient Artbuyingoptions_SelBuyingOptions(artbuyingoptionsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artcharge_SelList(artchargeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artcharge_SelListQua(artchargeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artinfbg_SelArtInfBG(artinfbgS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artinsert_SelBeilage(artinsertS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artinsert_Insert(artinsertS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artinsert_Delete(artinsertS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artlangname_SelLangname(artlangnameS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artprice_SelPrice(artpriceS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artpsycho_SelArticle(artpsychoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articleagentgroup_SelAgent(articleagentgroupS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articleagentgroup_SelArtikel(articleagentgroupS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articleagentgroup_SelList(articleagentgroupS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articlelpprreimb_SelListArt(articlelpprreimbS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articlequotadetail_SelCount(articlequotadetailS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articlequotadetail_SelKumVzDetail(articlequotadetailS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articlequotaekg_SelArticle(articlequotaekgS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articlequotaekg_SelListEKG(articlequotaekgS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articlequotaekg_Insert(articlequotaekgS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articlequotaekg_Update(articlequotaekgS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articlequotaekg_Delete(articlequotaekgS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articlequotaekg_DeleteAllEKG(articlequotaekgS * d, tError * tErrorMsg, bool bIsTrans);
retClient Articletax_SelTax(articletaxS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikellppr_SelList(artikellpprS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_SelListAllNoBat(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_SelListArt(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_SelListArtNoBat(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_SelListKnd(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_SelListKndNoBat(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_SelQuota(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_Insert(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_Update(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_Delete(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_DeleteAllArt(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_DeleteAllKnd(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_CheckQuota(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquota_SelKumVz(artikelquotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquotapf_CopyQuota(artikelquotapfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquotapf_DeleteKundeEKG(artikelquotapfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquotapf_InsertKlasse(artikelquotapfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquotapf_InsertKlasse09(artikelquotapfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquotapf_InsertKundeEKG(artikelquotapfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquotapf_UpdateKundeEKG(artikelquotapfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquotapf_UpdateQuota(artikelquotapfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelquotapf_UpdateQuota09(artikelquotapfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelreserve_SelArt(artikelreserveS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelreserve_SelArtKnd(artikelreserveS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelreserve_Insert(artikelreserveS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelreserve_Update(artikelreserveS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelreserve_Delete(artikelreserveS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelreserve_InsertBestand(artikelreserveS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelreserve_ReservStockAbs(artikelreserveS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelreserve_SelListBestand(artikelreserveS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikeltext_Select(artikeltextS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelverfall_CheckShortExpiry(artikelverfallS * d, tError * tErrorMsg, bool bIsTrans);
retClient Aticleaux_SelList(aticleauxS * d, tError * tErrorMsg, bool bIsTrans);
retClient Aticleaux_Insert(aticleauxS * d, tError * tErrorMsg, bool bIsTrans);
retClient Aticleaux_Update(aticleauxS * d, tError * tErrorMsg, bool bIsTrans);
retClient Aticleaux_Delete(aticleauxS * d, tError * tErrorMsg, bool bIsTrans);
retClient Ccode_Sel(ccodeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Ccode_Insert(ccodeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Ccode_Update(ccodeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Ccode_Delete(ccodeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkimexblockexist_SelExist(checkimexblockexistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkimportarticle_SelImport(checkimportarticleS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkliste5zentral_IsListe5(checkliste5zentralS * d, tError * tErrorMsg, bool bIsTrans);
retClient Codeblocageinfo_SelText(codeblocageinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Dispoinfo_SelDispoInfo(dispoinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Hersteller_SelHersteller(herstellerS * d, tError * tErrorMsg, bool bIsTrans);
retClient Lpprcode_Sel(lpprcodeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Maxarticlequota_SelMax(maxarticlequotaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Occasion_SelList(occasionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Pharmgrp_Sel(pharmgrpS * d, tError * tErrorMsg, bool bIsTrans);
retClient Preisanztyp_SelPreis(preisanztypS * d, tError * tErrorMsg, bool bIsTrans);
retClient Pricehist_Sel(pricehistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoanz_SelPromo(promoanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Reimport_SelAuswahl(reimportS * d, tError * tErrorMsg, bool bIsTrans);
retClient Steller_SelList(stellerS * d, tError * tErrorMsg, bool bIsTrans);
retClient Stellertyp_SelTyp(stellertypS * d, tError * tErrorMsg, bool bIsTrans);
retClient Stockreservation_SelList(stockreservationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Stockreservation_SelSum(stockreservationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Stockreservation_SelListAll(stockreservationS* d, tError* tErrorMsg, bool bIsTrans);
retClient Stockreservation_DeleteEntry(stockreservationS* d, tError* tErrorMsg, bool bIsTrans);
retClient Stockreservation_SelArtikelLokal(stockreservationartikellokalS* d, tError* tErrorMsg, bool bIsTrans);
retClient Stockreservation_SelArticleReserv(stockreservationarticlereservS* d, tError* tErrorMsg, bool bIsTrans);
retClient Stockreservation_SelIBTRequet(stockreservationibtrequestS* d, tError* tErrorMsg, bool bIsTrans);
retClient Stockreservation_SelNachlieferPos(stockreservationnachlieferposS* d, tError* tErrorMsg, bool bIsTrans);
retClient Stockreservation_UpdateArtikelLokal(stockreservationartikellokalS* d, tError* tErrorMsg, bool bIsTrans);
retClient Stockreservation_UpdateArticleReservation(stockreservationarticlereservS* d, tError* tErrorMsg, bool bIsTrans);
retClient Stockreservation_DeleteNachlieferPos(stockreservationnachlieferposS* d, tError* tErrorMsg, bool bIsTrans);
retClient Stockreservation_SelOrder(stockreservationorderS* d, tError* tErrorMsg, bool bIsTrans);
retClient Supplinfo_SelSuppInfo(supplinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedart_Sel(delayedartS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedart_Insert(delayedartS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedart_Update(delayedartS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedart_Delete(delayedartS * d, tError * tErrorMsg, bool bIsTrans);
retClient discountanz_SelList(discountanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient discountanz_SelListCst(discountanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient discountanz_SelListCstEKG(discountanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient discountanz_SelListDG(discountanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient discountanz_SelListGrp(discountanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient discountanz_SelListGrpHerst(discountanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient discountanz_SelListHerst(discountanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient discountanz_SellListGrpDG(discountanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient stockentry_SelList(stockentryS * d, tError * tErrorMsg, bool bIsTrans);
retClient Aufposrab_SelList(aufposrabS * d, tError * tErrorMsg, bool bIsTrans);
retClient Auftragwerte_SelWerte(auftragwerteS * d, tError * tErrorMsg, bool bIsTrans);
retClient Auftragwertealt_SelWerte(auftragwertealtS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkorderiv_SelKonsig(checkorderivS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkorderiv_SelManu(checkorderivS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collectiveorders_SelCVOrder(collectiveordersS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collectiveorders_SelCVOrderCount(collectiveordersS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collectiveorders_SelCVOrderDE(collectiveordersS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kndppflag_GetZurueckFlag(kndppflagS * d, tError * tErrorMsg, bool bIsTrans);
retClient Poschange_SelList(poschangeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Poschange_Update(poschangeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Poschangehist_SelList(poschangehistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Poschangehist_Update(poschangehistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Prolink_SelProLink(prolinkS * d, tError * tErrorMsg, bool bIsTrans);
retClient Prolink_Insert(prolinkS * d, tError * tErrorMsg, bool bIsTrans);
retClient Prolinkact_SelProLink(prolinkactS * d, tError * tErrorMsg, bool bIsTrans);
retClient Prolinkact_Insert(prolinkactS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackattach_Sel(callbackattachS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackattach_SelVz(callbackattachS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackattach_Insert(callbackattachS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackattach_Delete(callbackattachS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackpartner_SelPartner(callbackpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackpartner_SelectAll(callbackpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackpartner_SelectAllVz(callbackpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackpartner_Update(callbackpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackpartner_DeleteCallbackPartner(callbackpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackpartner_InsertWithNewNo(callbackpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktime_SelectCallbackPartner(callbacktimeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktime_Insert(callbacktimeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktime_DeleteAllNo(callbacktimeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktime_DeleteCallbackTime(callbacktimeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackcritical_SelCritical(callbackcriticalS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackdivision_SelDivision(callbackdivisionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackdivision_SelList(callbackdivisionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackdivision_SelListAll(callbackdivisionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackdivision_Update(callbackdivisionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackdivision_Delete(callbackdivisionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackdivision_InsertWithNewNo(callbackdivisionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackreasons_SelList(callbackreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackreasons_Update(callbackreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackreasons_Delete(callbackreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackreasons_DeleteAllNo(callbackreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackreasons_InsertWithNewNo(callbackreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackremarks_SelList(callbackremarksS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackremarks_SelRemark(callbackremarksS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackremarks_Insert(callbackremarksS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackremarks_Update(callbackremarksS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackremarks_DeleteRemark(callbackremarksS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelAllLocked(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelAllLockedVz(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelAllNotDone(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelAllNotDoneVz(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelCallbackFuture(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelCallbackFutureVz(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelCallbackOpen(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelCallbackOpenVz(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelCallbackWished(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodo_SelCallbackWishedVz(callbacktodoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelAllLocked(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelAllLockedVz(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelAllNotDone(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelAllNotDoneVz(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelCallbackFuture(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelCallbackFutureVz(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelCallbackOpen(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelCallbackOpenVz(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelCallbackWished(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbacktodonew_SelCallbackWishedVz(callbacktodonewS * d, tError * tErrorMsg, bool bIsTrans);
retClient Callbackstatus_SelectAll(callbackstatusS* a, tError* stError, bool bIsTrans);
retClient callbackitems_SelCallbackWish(callbackitemsS * d, tError * tErrorMsg, bool bIsTrans);
retClient callbackitems_SelNo(callbackitemsS * d, tError * tErrorMsg, bool bIsTrans);
retClient callbackitems_SelNotDone(callbackitemsS * d, tError * tErrorMsg, bool bIsTrans);
retClient callbackitems_Sellocked(callbackitemsS * d, tError * tErrorMsg, bool bIsTrans);
retClient callbackitems_UpdateItem(callbackitemsS * d, tError * tErrorMsg, bool bIsTrans);
retClient callbackitems_InsertWithNewNo(callbackitemsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkorderexist_SelAuftrag(checkorderexistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamterdriver_SelParameter(mcallparamterdriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamterdriver_UpdTime(mcallparamterdriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamterdriver_SetCallsToFinish(mcallparamterdriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanday_SelCallPlanDay(mcustomercallplandayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanday_SelListFuture(mcustomercallplandayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanday_EndBrowse(mcustomercallplandayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanday_Insert(mcustomercallplandayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanday_SelList(mcustomercallplandayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanday_SelListHist(mcustomercallplandayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanday_SetCustomerCallFree(mcustomercallplandayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanday_StartBrowse(mcustomercallplandayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanday_UpdCustomerCallPlanDay(mcustomercallplandayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandayhist_SelList(mcustomercallplandayhistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandayhist_DelAll(mcustomercallplandayhistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandayhist_DelAllOlder(mcustomercallplandayhistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanrecallinwork_Select(mcustomercallplanrecallinworkS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanrecallinwork_Insert(mcustomercallplanrecallinworkS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanrecallinwork_Update(mcustomercallplanrecallinworkS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanrecallinwork_Delete(mcustomercallplanrecallinworkS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandaydriver_EndBrowse(mcustomercallplandaydriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandaydriver_SelList(mcustomercallplandaydriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandaydriver_SelUniCustomerCallplan(mcustomercallplandaydriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandaydriver_StartBrowse(mcustomercallplandaydriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandaydriver_UpdCustomerCallplan(mcustomercallplandaydriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandaydriver_UpdCustomerCallplanWithoutTransaction(mcustomercallplandaydriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplandaydriver_UpdWithoutTransaction(mcustomercallplandaydriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerlastcall_EndBrowse(mcustomerlastcallS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerlastcall_SelCustomerCallState(mcustomerlastcallS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerlastcall_StartBrowse(mcustomerlastcallS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerorder_EndBrowse(mcustomerorderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerorder_SelAvailableOrder(mcustomerorderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerorder_SelCustomerCalled(mcustomerorderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerorder_SelDeviceOrder(mcustomerorderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerorder_StartBrowse(mcustomerorderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplancheck_SelDeviceID(mdeviceplancheckS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplancheck_SelList(mdeviceplancheckS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplancheck_SelListHist(mdeviceplancheckS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplancheck_UpdUMKDecivePlan(mdeviceplancheckS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplancheck_UpdateDirect(mdeviceplancheckS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplandriver_EndBrowse(mdeviceplandriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplandriver_SelList(mdeviceplandriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplandriver_SelWithSequenzNo(mdeviceplandriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplandriver_StartBrowse(mdeviceplandriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplandriver_UpdDevicePlan(mdeviceplandriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplandriver_UpdUMKDevicePlan(mdeviceplandriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplandriver_UpdWithoutTransaction(mdeviceplandriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplandriver_UpdWithoutTransactionDirect(mdeviceplandriverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mnumber_SelNumber(mnumberS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mnumber_Insert(mnumberS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mnumber_UpdNumber(mnumberS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mnumber_Increment(mnumberS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mtransaktion_BeginTransaction(mtransaktionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mtransaktion_EndTransaction(mtransaktionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mtransaktion_GetDate(mtransaktionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mtransaktion_GetDateTime(mtransaktionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mtransaktion_GetTime(mtransaktionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mtransaktion_RollbackTransaction(mtransaktionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mtransaktion_SetCommitedRead(mtransaktionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mtransaktion_SetDirtyRead(mtransaktionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamater_SelCallParameter(mcallparamaterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamater_SelList(mcallparamaterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamater_Insert(mcallparamaterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamater_UpdCallparameter(mcallparamaterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamater_DelCallParameter(mcallparamaterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamtertimes_SelParameter(mcallparamtertimesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamtertimes_Insert(mcallparamtertimesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallparamtertimes_UpdParameter(mcallparamtertimesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanload_SelCallPlanLoad(mcallplanloadS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanload_SelList(mcallplanloadS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanload_Insert(mcallplanloadS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanload_UpdCallPlanLoad(mcallplanloadS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanload_DelCallPlanLoad(mcallplanloadS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanload_DelCallPlanLoadOlder(mcallplanloadS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanload_AIncludeDummy(mcallplanloadS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanload_GetInitializeData(mcallplanloadS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_SelAllDisabled(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_SelList(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_SelListHist(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_Insert(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_UpdAllCustomerCallPlan(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_UpdAllWithoutSaturday(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_UpdCustomerCallPlan(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_DelAllCustomerCallPlan(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_DelAllWithoutSaturday(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_DelCallPlanCompletly(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_DelCustomerCallPlan(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_InsertAll(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_InsertAllWithoutSaturday(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_SelListUndertake(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_StartBrowseUndertake(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_UpdCallPlanDisable(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_UpdCallPlanEnable(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_UpdTimeAllCustomerCallPlan(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_UpdTimeAllWithoutSaturday(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplan_UpdTimeCustomerCallPlan(mcustomercallplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanphonprot_Insert(mcustomercallplanphonprotS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanphonprot_DelAll(mcustomercallplanphonprotS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanphonprot_DelAllOlder(mcustomercallplanphonprotS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplantour_SelList(mcustomercallplantourS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplantour_SelListHist(mcustomercallplantourS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanphon_Insert(mcustomercallplanphonS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanphon_DelAll(mcustomercallplanphonS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomercallplanphon_DelAllOlder(mcustomercallplanphonS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerdisplay_SelCustomer(mcustomerdisplayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerdisplay_UpdTelNo(mcustomerdisplayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomerdisplay_UpdProperties(mcustomerdisplayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplanmaintenance_SelDevicePlanUni(mdeviceplanmaintenanceS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplanmaintenance_SelList(mdeviceplanmaintenanceS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplanmaintenance_SelNst(mdeviceplanmaintenanceS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplanmaintenance_UpdDevicePlan(mdeviceplanmaintenanceS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplanmaintenance_UpdSaleCenterNo(mdeviceplanmaintenanceS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplanmaintenance_Delete(mdeviceplanmaintenanceS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mdeviceplanmaintenance_InsertDevice(mdeviceplanmaintenanceS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mregion_SelList(mregionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mregion_SelRegion(mregionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mregion_Insert(mregionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mregion_DelRegion(mregionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Msalecenter_SelList(msalecenterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Msalecenter_SelSaleCenter(msalecenterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkconnection_SelList(mumkconnectionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkconnection_SelUmkConnection(mumkconnectionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkconnection_Insert(mumkconnectionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkconnection_UpdUmkConnection(mumkconnectionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkconnection_DelUmkConnection(mumkconnectionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkconnection_WriteLog(mumkconnectionS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_SelCountAvailable(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_SelCountAvailablePhon(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_Insert(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_DelAll(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_DelAllOlder(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_AIncludeDummy(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_CheckAvailableEntries(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_CheckAvailableEntriesPhon(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_DelAllPhon(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_DelAllPhonOlder(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_DelCallPlanLoadOlder(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_DelEvents(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_DelEventsOlder(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_DelEventsPhon(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_DelEventsPhonOlder(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_UndertakeCallplan(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcallplanundertake_UndertakeCallplanPhon(mcallplanundertakeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mholiday_SelCount(mholidayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mholiday_SelHoliday(mholidayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mholiday_EndBrowse(mholidayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mholiday_IsHoliday(mholidayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mholiday_StartBrowse(mholidayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mholiday_inline_GetBuffer(mholidayS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collordergrp_SelList(collordergrpS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collordergrp_Insert(collordergrpS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collordergrp_Update(collordergrpS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collordergrp_Delete(collordergrpS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collordergrpmem_SelList(collordergrpmemS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collordergrpmem_Insert(collordergrpmemS * d, tError * tErrorMsg, bool bIsTrans);
retClient Collordergrpmem_Delete(collordergrpmemS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkdistress_IsInWork(checkdistressS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstseporder_SelList(cstseporderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstseporder_Insert(cstseporderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstseporder_Update(cstseporderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstseporder_Delete(cstseporderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Dealerumsatz_SelList(dealerumsatzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Forbiddenwords_SelWordList(forbiddenwordsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Forbiddenwords_SelWords(forbiddenwordsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Forbiddenwords_Insert(forbiddenwordsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Forbiddenwords_UpdateWord(forbiddenwordsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Forbiddenwords_DeleteWord(forbiddenwordsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Invoicenumber_GetNumber(invoicenumberS * d, tError * tErrorMsg, bool bIsTrans);
retClient Invoicenumberold_GetNumber(invoicenumberoldS * d, tError * tErrorMsg, bool bIsTrans);
retClient Parameter_SelParameter(parameterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Parameter_SelZweck(parameterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Seporder_Sel(seporderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Seporder_Insert(seporderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Seporder_Update(seporderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Seporder_Delete(seporderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Sepordergrp_Sel(sepordergrpS * d, tError * tErrorMsg, bool bIsTrans);
retClient Sepordergrp_Insert(sepordergrpS * d, tError * tErrorMsg, bool bIsTrans);
retClient Sepordergrp_Update(sepordergrpS * d, tError * tErrorMsg, bool bIsTrans);
retClient Sepordergrp_Delete(sepordergrpS * d, tError * tErrorMsg, bool bIsTrans);
retClient Taskcontrol_CheckTimes(taskcontrolS * d, tError * tErrorMsg, bool bIsTrans);
retClient Taxes_SelList(taxesS * d, tError * tErrorMsg, bool bIsTrans);
retClient customerordercheck_SelList(customerordercheckS * d, tError * tErrorMsg, bool bIsTrans);
retClient lgtext_Sel(lgtextS * d, tError * tErrorMsg, bool bIsTrans);
retClient lgtext_SetLanguage(lgtextS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailaddresses_DeleteAddress(cremaemailaddressesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailaddresses_InsertAddress(cremaemailaddressesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailaddresses_InsertGVL(cremaemailaddressesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailaddresses_InsertType(cremaemailaddressesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailaddresses_SelEmailAddresses(cremaemailaddressesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailaddresses_SelEmailType(cremaemailaddressesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailaddresses_Update(cremaemailaddressesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailaddresses_UpdateEmailAddress(cremaemailaddressesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailaddresses_UpdateGVL(cremaemailaddressesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cremaemailreasons_SelEmailReasons(cremaemailreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Chaincustomers_SelList(chaincustomersS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkcustomerexist_SelExist(checkcustomerexistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkliste5_IsListe5(checkliste5S * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstbranchinfo_SelList(cstbranchinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstbranchinfo_SelListValid(cstbranchinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstbranchinfo_Insert(cstbranchinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstbranchinfo_Update(cstbranchinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstbranchinfo_Delete(cstbranchinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstbulgaria_SelCst(cstbulgariaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstbuyingoptions_SelBuyingOptions(cstbuyingoptionsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstdiscacc_CheckExist(cstdiscaccS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstdiscacc_SelListCst(cstdiscaccS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstdiscacc_SelListGrp(cstdiscaccS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstdiscaccanz_CheckMain(cstdiscaccanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstdiscaccanz_CheckMember(cstdiscaccanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstdiscaccanz_SelList(cstdiscaccanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstdiscaccanz_SelMain(cstdiscaccanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstdisccont_SelList(cstdisccontS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstpayterm_SelList(cstpaytermS * d, tError * tErrorMsg, bool bIsTrans);
retClient Cstrebatetype_SelRebateType(cstrebatetypeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custpharma_SelList(custpharmaS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custphon_SelList(custphonS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custphon_SelPhoneNo(custphonS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custphon_Insert(custphonS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custphon_Delete(custphonS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custrout_SelActRouting(custroutS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custrout_SelList(custroutS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custrout_Insert(custroutS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custrout_Update(custroutS * d, tError * tErrorMsg, bool bIsTrans);
retClient Custrout_Delete(custroutS * d, tError * tErrorMsg, bool bIsTrans);
retClient Customerdoubles_SelDouble(customerdoublesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Distressrouting_SelNot(distressroutingS * d, tError * tErrorMsg, bool bIsTrans);
retClient Distressrouting_SelRouted(distressroutingS * d, tError * tErrorMsg, bool bIsTrans);
retClient Distressrouting_Update(distressroutingS * d, tError * tErrorMsg, bool bIsTrans);
retClient Distressrouting_GetCount(distressroutingS * d, tError * tErrorMsg, bool bIsTrans);
retClient Enclosertimes_SelList(enclosertimesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Enclosertimes_Insert(enclosertimesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Enclosertimes_Update(enclosertimesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Enclosertimes_Delete(enclosertimesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Enclosertimes_CopyEncloser(enclosertimesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kndtourfenster_SelPeriods(kndtourfensterS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kndtourwoche_SelList(kndtourwocheS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kndtourwoche2_SelList(kndtourwoche2S * d, tError * tErrorMsg, bool bIsTrans);
retClient Kndtourwoche3_SelList(kndtourwoche3S * d, tError * tErrorMsg, bool bIsTrans);
retClient Kndfilinfo_SelKnd(kndfilinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kndfilinfo2_SelInfo(kndfilinfo2S * d, tError * tErrorMsg, bool bIsTrans);
retClient Kreditlimit_SelLimit(kreditlimitS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kreditlimit_SelLimit1(kreditlimitS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kreditlimit_SelLimit2(kreditlimitS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kreditlimit_SelLimitMain(kreditlimitS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kundelizensen_SelLicenses(kundelizensenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kundeverbundfiliale_Sel(kundeverbundfilialeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kundeverbundfiliale_Insert(kundeverbundfilialeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kundeverbundfiliale_Update(kundeverbundfilialeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Kundeverbundfiliale_Delete(kundeverbundfilialeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Liste5_SelList(liste5S * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomeremergencyserviceplan_SelList(mcustomeremergencyserviceplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomeremergencyserviceplan_SelListHist(mcustomeremergencyserviceplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomeremergencyserviceplan_SelUni(mcustomeremergencyserviceplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomeremergencyserviceplan_Insert(mcustomeremergencyserviceplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomeremergencyserviceplan_Update(mcustomeremergencyserviceplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomeremergencyserviceplan_Delete(mcustomeremergencyserviceplanS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomervacation_SelList(mcustomervacationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomervacation_SelUni(mcustomervacationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomervacation_Insert(mcustomervacationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomervacation_Update(mcustomervacationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomervacation_Delete(mcustomervacationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcustomervacation_SelNextEffective(mcustomervacationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Payterm_SelList(paytermS * d, tError * tErrorMsg, bool bIsTrans);
retClient Paymentlist_SelList(paymentlistS * d, tError * tErrorMsg, bool bIsTrans);
retClient Prewholecst_IsPrewholeCst(prewholecstS * d, tError * tErrorMsg, bool bIsTrans);
retClient Shipauxno_SelList(shipauxnoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Shipauxno_Insert(shipauxnoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Shipauxno_Update(shipauxnoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Shipauxno_Delete(shipauxnoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tourpflege_SelTourenKunde(tourpflegeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tourpflege_Update(tourpflegeS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_SelDay(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_SelList(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_Insert(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_Update(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_Delete(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_DeleteAll(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_InsertAll(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_SelectActTouren(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_SelectTouren(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayedcst_SetActiv(delayedcstS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayeddeliverycstspecial_Sel(delayeddeliverycstspecialS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayeddeliverycstspecial_SelUni(delayeddeliverycstspecialS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayeddeliverycstspecial_Insert(delayeddeliverycstspecialS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayeddeliverycstspecial_Update(delayeddeliverycstspecialS * d, tError * tErrorMsg, bool bIsTrans);
retClient delayeddeliverycstspecial_Delete(delayeddeliverycstspecialS * d, tError * tErrorMsg, bool bIsTrans);
retClient Eilbotendruck_druckeil(eilbotendruckS * d, tError * tErrorMsg, bool bIsTrans);
retClient Extratourreasons_SelList(extratourreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Extratourreasons_SelListAll(extratourreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Extratourreasons_Insert(extratourreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Extratourreasons_Delete(extratourreasonsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Herstellerliste_SelList(herstellerlisteS * d, tError * tErrorMsg, bool bIsTrans);
retClient Msv3cstinfo_SelCstInfo(msv3cstinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Msv3einstellungen_SelAdjustments(msv3einstellungenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Msv3info_SelMSV3(msv3infoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Msv3orderinfo_SelMSV3Orders(msv3orderinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Msv3tourinfo_SelBFToday(msv3tourinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkdfreason_SelEvent(checkdfreasonS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkklreleased_SelReleased(checkklreleasedS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkordernodd_CheckNoDD(checkordernoddS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkorderzerod_SelAufwert(checkorderzerodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkorderzerodold_SelAufwert(checkorderzerodoldS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkorderlabel_SelLabelType(checkorderlabelS * d, tError * tErrorMsg, bool bIsTrans);
retClient Driver_SelAct(driverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Driver_SelOld(driverS * d, tError * tErrorMsg, bool bIsTrans);
retClient Invoicenos_SelList(invoicenosS * d, tError * tErrorMsg, bool bIsTrans);
retClient Invoicenosold_SelList(invoicenosoldS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_CheckOPOverLap(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_DelOPOPTForDay(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_DeleteOPAndOPT(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_DeleteOPForDay(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_DeleteOPT(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_DeleteOPTForDay(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_InsertOPAndOPT(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_InsertOPT(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_SelConsTime(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_SelHighKippTime(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_SelOPChildCount(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_SelOPWeekdays(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_SelTimesLastTour(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_SelTourData(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_SelTourForIDF(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_SelWeekdays4Tour(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_UpdateTime(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Orderperiod_UpdateTimeSingle(orderperiodS * d, tError * tErrorMsg, bool bIsTrans);
retClient Origintypesettingspf_SelList(origintypesettingspfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Origintypesettingspf_Insert(origintypesettingspfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Origintypesettingspf_Update(origintypesettingspfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Origintypesettingspf_Delete(origintypesettingspfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Origintypesettingspf_SelListNotDefined(origintypesettingspfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Remarktypes_SelList(remarktypesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Specialnumbers_SelNumber(specialnumbersS * d, tError * tErrorMsg, bool bIsTrans);
retClient Specialnumbersold_SelNumber(specialnumbersoldS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcheckprocess_SelProcess(mcheckprocessS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcheckprocess_Insert(mcheckprocessS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcheckprocess_UpdProcess(mcheckprocessS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mcheckprocess_DelProcess(mcheckprocessS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkprocesses_SelList(mumkprocessesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkprocesses_StartCallplan(mumkprocessesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkprocesses_StartUmkAll(mumkprocessesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkprocesses_StartUmkUnique(mumkprocessesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkprocesses_StopCallplan(mumkprocessesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkprocesses_StopUmkAll(mumkprocessesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Mumkprocesses_StopUmkUnique(mumkprocessesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Productpromo_SelList(productpromoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoherst_SelList(promoherstS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promomanufact_SelManuNo(promomanufactS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promomembers_SelList(promomembersS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promotionen_SelList(promotionenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promotionen_SelListManu(promotionenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promotionen_SelPromoNo(promotionenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promotionen_SelPromoNoManu(promotionenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Stotinken_SelList(stotinkenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkpromoscale_PromoScaleExist(checkpromoscaleS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoquotaanz_SelList(promoquotaanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoquotaanz_SelQuota(promoquotaanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoquotaanz_SelQuotaPzn(promoquotaanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoquotacheck_SelQuota(promoquotacheckS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoquotacstanz_SelList(promoquotacstanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoquotacstanz_SelListCst(promoquotacstanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoquotacstanz_SelListPromo(promoquotacstanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Promoquotacstanz_SelQuota(promoquotacstanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Discountgroup_Selgroup(discountgroupS * d, tError * tErrorMsg, bool bIsTrans);
retClient Rangemembers_SelArticle(rangemembersS * d, tError * tErrorMsg, bool bIsTrans);
retClient Rangemembers_SelManu(rangemembersS * d, tError * tErrorMsg, bool bIsTrans);
retClient Servicemember_SelList(servicememberS * d, tError * tErrorMsg, bool bIsTrans);
retClient Serviceorder_SelType(serviceorderS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artikelkontoanz_SelList(artikelkontoanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Aufwertherst_SelList(aufwertherstS * d, tError * tErrorMsg, bool bIsTrans);
retClient Feiertag_SelAll(feiertagS * d, tError * tErrorMsg, bool bIsTrans);
retClient Feiertag_Insert(feiertagS * d, tError * tErrorMsg, bool bIsTrans);
retClient Feiertag_Update(feiertagS * d, tError * tErrorMsg, bool bIsTrans);
retClient Feiertag_Delete(feiertagS * d, tError * tErrorMsg, bool bIsTrans);
retClient Lagerrevisionanz_SelList(lagerrevisionanzS * d, tError * tErrorMsg, bool bIsTrans);
retClient Oecustomercalls_Insert(oecustomercallsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Oecustomercalls_Update(oecustomercallsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Offenauftrag_SelList(offenauftragS * d, tError * tErrorMsg, bool bIsTrans);
retClient Rufstat_Sel_Tagstat(rufstatS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tourzeit_SelNextTour(tourzeitS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tenderarticle_SelArt(tenderarticleS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tenderarticle_SelList(tenderarticleS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tenderinfo_SelList(tenderinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tenderinfo_SelListChain(tenderinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tenderinfo_SelListPos(tenderinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tenderinfo_SelListStaat(tenderinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tenderinfo_SelTender(tenderinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tenderstock_SelQty(tenderstockS * d, tError * tErrorMsg, bool bIsTrans);
retClient Sondertouren_SelList(sondertourenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Sondertouren_Insert(sondertourenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Sondertouren_Update(sondertourenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Sondertouren_Delete(sondertourenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tourplanpflege_SelList(tourplanpflegeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tourplanpflege_SelTour(tourplanpflegeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Tourplanpflege_Update(tourplanpflegeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Toursperre_SelList(toursperreS * d, tError * tErrorMsg, bool bIsTrans);
retClient Toursperre_Update(toursperreS * d, tError * tErrorMsg, bool bIsTrans);
retClient Artstock_SelList(artstockS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkibtdone_IsIBTDone(checkibtdoneS * d, tError * tErrorMsg, bool bIsTrans);
retClient Checkibtdone_SelIBTDoneOrder(checkibtdoneS * d, tError * tErrorMsg, bool bIsTrans);
retClient Verbundmoegl_SelVbBestandNeu(verbundmoeglS * d, tError * tErrorMsg, bool bIsTrans);
retClient Verbundmoegl_SelVbBestandTM(verbundmoeglS * d, tError * tErrorMsg, bool bIsTrans);
retClient articlenlevelibttype_SelList(articlenlevelibttypeS * d, tError * tErrorMsg, bool bIsTrans);
retClient Backrout_SelList(backroutS * d, tError * tErrorMsg, bool bIsTrans);
retClient Backrout_Insert(backroutS * d, tError * tErrorMsg, bool bIsTrans);
retClient Backrout_Delete(backroutS * d, tError * tErrorMsg, bool bIsTrans);
retClient Branchinfo_SelInfo(branchinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Branchinfo_Insert(branchinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Branchinfo_Update(branchinfoS * d, tError * tErrorMsg, bool bIsTrans);
retClient Branchnames_SelList(branchnamesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Ibtbranchesadmin_SelList(ibtbranchesadminS * d, tError * tErrorMsg, bool bIsTrans);
retClient Ibtbranchesadmin_Insert(ibtbranchesadminS * d, tError * tErrorMsg, bool bIsTrans);
retClient Ibtbranchesadmin_Update(ibtbranchesadminS * d, tError * tErrorMsg, bool bIsTrans);
retClient Ibtbranchesadmin_Delete(ibtbranchesadminS * d, tError * tErrorMsg, bool bIsTrans);
retClient Nlevelibtbranches_SelIBTBranches(nlevelibtbranchesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Regionbranches_SelList(regionbranchesS * d, tError * tErrorMsg, bool bIsTrans);
retClient Regions_SelRegion(regionsS * d, tError * tErrorMsg, bool bIsTrans);
retClient Vbfilialen_SelVbFilialen(vbfilialenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Verbundidf_SelVBIdf(verbundidfS * d, tError * tErrorMsg, bool bIsTrans);
retClient Zielfilialen_SelList(zielfilialenS * d, tError * tErrorMsg, bool bIsTrans);
retClient filialpartner_Sel(filialpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient filialpartner_SelSupportTime(filialpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient filialpartner_Insert(filialpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient filialpartner_Update(filialpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient filialpartner_Delete(filialpartnerS * d, tError * tErrorMsg, bool bIsTrans);
retClient filialzeiten_SelZeiten(filialzeitenS * d, tError * tErrorMsg, bool bIsTrans);
retClient filialzeiten_UpdateZeiten(filialzeitenS * d, tError * tErrorMsg, bool bIsTrans);
retClient Maildefineduser_SelAllUser(maildefineduserS * d, tError * tErrorMsg, bool bIsTrans);
retClient Maildefineduser_SelAllUserVz(maildefineduserS * d, tError * tErrorMsg, bool bIsTrans);
retClient Maildefineduser_SelOpenMail(maildefineduserS * d, tError * tErrorMsg, bool bIsTrans);
retClient Userinformation_CheckFree(userinformationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Userinformation_SelInfo(userinformationS * d, tError * tErrorMsg, bool bIsTrans);
retClient Userinformation_Insert(userinformationS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailgroup_SelMailGroup(mailgroupS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailgroup_SelMailGroupVz(mailgroupS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailgroup_Insert(mailgroupS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailgroup_UpdateMailGroup(mailgroupS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailgroup_DeleteMailGroup(mailgroupS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailitems_SelOpenNews(mailitemsS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailitems_Insert(mailitemsS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailitems_DeleteMessage(mailitemsS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailmessage_SelMailMessage(mailmessageS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailmessage_Insert(mailmessageS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailmessage_SelAllMessage(mailmessageS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailmessage_SelNotRead(mailmessageS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailusers_SelAll(mailusersS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailusers_Insert(mailusersS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailusers_Delete(mailusersS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailusers_DeleteAll(mailusersS * d, tError * tErrorMsg, bool bIsTrans);
retClient mailusers_DeleteAllVz(mailusersS * d, tError * tErrorMsg, bool bIsTrans);
/* _DECLARATION__ */
#ifdef __CPLUS__
}
#endif

/* _C++DECLARATION__ */
/* _C++DECLARATION__ */

/* DistributorFunPublic  ******************************************************/

#ifndef __DADE_LOAD__
int DistributorFunPublic(const int iFunNo, char *spIn , char *spOut, int *ipLen)
#else
int DistributorFunPublic(const int iFunNo, void *spBuf, char *spOut, int *ipLen)
#endif
{
    int    rc;
    tError tErrorMsg;

    switch (iFunNo)
    {
/* _SWITCH__ */
    case ARTBUYINGOPTIONS_SELBUYINGOPTIONS: {
        artbuyingoptionsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTBUYINGOPTIONS_BES, ARTBUYINGOPTIONS_ANZ);
#else
        d = (artbuyingoptionsS *)spBuf;
#endif

        if ( (rc = Artbuyingoptions_SelBuyingOptions(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTBUYINGOPTIONS_BES, ARTBUYINGOPTIONS_ANZ );
#else
        {
            void * pUnused = ARTBUYINGOPTIONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTCHARGE_SELLIST: {
        artchargeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTCHARGE_BES, ARTCHARGE_ANZ);
#else
        d = (artchargeS *)spBuf;
#endif

        if ( (rc = Artcharge_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTCHARGE_BES, ARTCHARGE_ANZ );
#else
        {
            void * pUnused = ARTCHARGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTCHARGE_SELLISTQUA: {
        artchargeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTCHARGE_BES, ARTCHARGE_ANZ);
#else
        d = (artchargeS *)spBuf;
#endif

        if ( (rc = Artcharge_SelListQua(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTCHARGE_BES, ARTCHARGE_ANZ );
#else
        {
            void * pUnused = ARTCHARGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTINFBG_SELARTINFBG: {
        artinfbgS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTINFBG_BES, ARTINFBG_ANZ);
#else
        d = (artinfbgS *)spBuf;
#endif

        if ( (rc = Artinfbg_SelArtInfBG(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTINFBG_BES, ARTINFBG_ANZ );
#else
        {
            void * pUnused = ARTINFBG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTINSERT_SELBEILAGE: {
        artinsertS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTINSERT_BES, ARTINSERT_ANZ);
#else
        d = (artinsertS *)spBuf;
#endif

        if ( (rc = Artinsert_SelBeilage(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTINSERT_BES, ARTINSERT_ANZ );
#else
        {
            void * pUnused = ARTINSERT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTINSERT_INSERT: {
        artinsertS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTINSERT_BES, ARTINSERT_ANZ);
#else
        d = (artinsertS *)spBuf;
#endif

        if ( (rc = Artinsert_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTINSERT_BES, ARTINSERT_ANZ );
#else
        {
            void * pUnused = ARTINSERT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTINSERT_DELETE: {
        artinsertS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTINSERT_BES, ARTINSERT_ANZ);
#else
        d = (artinsertS *)spBuf;
#endif

        if ( (rc = Artinsert_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTINSERT_BES, ARTINSERT_ANZ );
#else
        {
            void * pUnused = ARTINSERT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTLANGNAME_SELLANGNAME: {
        artlangnameS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTLANGNAME_BES, ARTLANGNAME_ANZ);
#else
        d = (artlangnameS *)spBuf;
#endif

        if ( (rc = Artlangname_SelLangname(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTLANGNAME_BES, ARTLANGNAME_ANZ );
#else
        {
            void * pUnused = ARTLANGNAME_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTPRICE_SELPRICE: {
        artpriceS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTPRICE_BES, ARTPRICE_ANZ);
#else
        d = (artpriceS *)spBuf;
#endif

        if ( (rc = Artprice_SelPrice(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTPRICE_BES, ARTPRICE_ANZ );
#else
        {
            void * pUnused = ARTPRICE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTPSYCHO_SELARTICLE: {
        artpsychoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTPSYCHO_BES, ARTPSYCHO_ANZ);
#else
        d = (artpsychoS *)spBuf;
#endif

        if ( (rc = Artpsycho_SelArticle(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTPSYCHO_BES, ARTPSYCHO_ANZ );
#else
        {
            void * pUnused = ARTPSYCHO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEAGENTGROUP_SELAGENT: {
        articleagentgroupS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEAGENTGROUP_BES, ARTICLEAGENTGROUP_ANZ);
#else
        d = (articleagentgroupS *)spBuf;
#endif

        if ( (rc = Articleagentgroup_SelAgent(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEAGENTGROUP_BES, ARTICLEAGENTGROUP_ANZ );
#else
        {
            void * pUnused = ARTICLEAGENTGROUP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEAGENTGROUP_SELARTIKEL: {
        articleagentgroupS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEAGENTGROUP_BES, ARTICLEAGENTGROUP_ANZ);
#else
        d = (articleagentgroupS *)spBuf;
#endif

        if ( (rc = Articleagentgroup_SelArtikel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEAGENTGROUP_BES, ARTICLEAGENTGROUP_ANZ );
#else
        {
            void * pUnused = ARTICLEAGENTGROUP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEAGENTGROUP_SELLIST: {
        articleagentgroupS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEAGENTGROUP_BES, ARTICLEAGENTGROUP_ANZ);
#else
        d = (articleagentgroupS *)spBuf;
#endif

        if ( (rc = Articleagentgroup_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEAGENTGROUP_BES, ARTICLEAGENTGROUP_ANZ );
#else
        {
            void * pUnused = ARTICLEAGENTGROUP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLELPPRREIMB_SELLISTART: {
        articlelpprreimbS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLELPPRREIMB_BES, ARTICLELPPRREIMB_ANZ);
#else
        d = (articlelpprreimbS *)spBuf;
#endif

        if ( (rc = Articlelpprreimb_SelListArt(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLELPPRREIMB_BES, ARTICLELPPRREIMB_ANZ );
#else
        {
            void * pUnused = ARTICLELPPRREIMB_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEQUOTADETAIL_SELCOUNT: {
        articlequotadetailS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEQUOTADETAIL_BES, ARTICLEQUOTADETAIL_ANZ);
#else
        d = (articlequotadetailS *)spBuf;
#endif

        if ( (rc = Articlequotadetail_SelCount(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEQUOTADETAIL_BES, ARTICLEQUOTADETAIL_ANZ );
#else
        {
            void * pUnused = ARTICLEQUOTADETAIL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEQUOTADETAIL_SELKUMVZDETAIL: {
        articlequotadetailS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEQUOTADETAIL_BES, ARTICLEQUOTADETAIL_ANZ);
#else
        d = (articlequotadetailS *)spBuf;
#endif

        if ( (rc = Articlequotadetail_SelKumVzDetail(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEQUOTADETAIL_BES, ARTICLEQUOTADETAIL_ANZ );
#else
        {
            void * pUnused = ARTICLEQUOTADETAIL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEQUOTAEKG_SELARTICLE: {
        articlequotaekgS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ);
#else
        d = (articlequotaekgS *)spBuf;
#endif

        if ( (rc = Articlequotaekg_SelArticle(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ );
#else
        {
            void * pUnused = ARTICLEQUOTAEKG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEQUOTAEKG_SELLISTEKG: {
        articlequotaekgS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ);
#else
        d = (articlequotaekgS *)spBuf;
#endif

        if ( (rc = Articlequotaekg_SelListEKG(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ );
#else
        {
            void * pUnused = ARTICLEQUOTAEKG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEQUOTAEKG_INSERT: {
        articlequotaekgS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ);
#else
        d = (articlequotaekgS *)spBuf;
#endif

        if ( (rc = Articlequotaekg_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ );
#else
        {
            void * pUnused = ARTICLEQUOTAEKG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEQUOTAEKG_UPDATE: {
        articlequotaekgS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ);
#else
        d = (articlequotaekgS *)spBuf;
#endif

        if ( (rc = Articlequotaekg_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ );
#else
        {
            void * pUnused = ARTICLEQUOTAEKG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEQUOTAEKG_DELETE: {
        articlequotaekgS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ);
#else
        d = (articlequotaekgS *)spBuf;
#endif

        if ( (rc = Articlequotaekg_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ );
#else
        {
            void * pUnused = ARTICLEQUOTAEKG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLEQUOTAEKG_DELETEALLEKG: {
        articlequotaekgS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ);
#else
        d = (articlequotaekgS *)spBuf;
#endif

        if ( (rc = Articlequotaekg_DeleteAllEKG(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLEQUOTAEKG_BES, ARTICLEQUOTAEKG_ANZ );
#else
        {
            void * pUnused = ARTICLEQUOTAEKG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLETAX_SELTAX: {
        articletaxS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLETAX_BES, ARTICLETAX_ANZ);
#else
        d = (articletaxS *)spBuf;
#endif

        if ( (rc = Articletax_SelTax(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLETAX_BES, ARTICLETAX_ANZ );
#else
        {
            void * pUnused = ARTICLETAX_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELLPPR_SELLIST: {
        artikellpprS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELLPPR_BES, ARTIKELLPPR_ANZ);
#else
        d = (artikellpprS *)spBuf;
#endif

        if ( (rc = Artikellppr_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELLPPR_BES, ARTIKELLPPR_ANZ );
#else
        {
            void * pUnused = ARTIKELLPPR_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_SELLISTALLNOBAT: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_SelListAllNoBat(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_SELLISTART: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_SelListArt(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_SELLISTARTNOBAT: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_SelListArtNoBat(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_SELLISTKND: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_SelListKnd(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_SELLISTKNDNOBAT: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_SelListKndNoBat(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_SELQUOTA: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_SelQuota(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_INSERT: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_UPDATE: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_DELETE: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_DELETEALLART: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_DeleteAllArt(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_DELETEALLKND: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_DeleteAllKnd(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_CHECKQUOTA: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_CheckQuota(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTA_SELKUMVZ: {
        artikelquotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ);
#else
        d = (artikelquotaS *)spBuf;
#endif

        if ( (rc = Artikelquota_SelKumVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTA_BES, ARTIKELQUOTA_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTAPF_COPYQUOTA: {
        artikelquotapfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ);
#else
        d = (artikelquotapfS *)spBuf;
#endif

        if ( (rc = Artikelquotapf_CopyQuota(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTAPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTAPF_DELETEKUNDEEKG: {
        artikelquotapfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ);
#else
        d = (artikelquotapfS *)spBuf;
#endif

        if ( (rc = Artikelquotapf_DeleteKundeEKG(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTAPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTAPF_INSERTKLASSE: {
        artikelquotapfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ);
#else
        d = (artikelquotapfS *)spBuf;
#endif

        if ( (rc = Artikelquotapf_InsertKlasse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTAPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTAPF_INSERTKLASSE09: {
        artikelquotapfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ);
#else
        d = (artikelquotapfS *)spBuf;
#endif

        if ( (rc = Artikelquotapf_InsertKlasse09(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTAPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTAPF_INSERTKUNDEEKG: {
        artikelquotapfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ);
#else
        d = (artikelquotapfS *)spBuf;
#endif

        if ( (rc = Artikelquotapf_InsertKundeEKG(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTAPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTAPF_UPDATEKUNDEEKG: {
        artikelquotapfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ);
#else
        d = (artikelquotapfS *)spBuf;
#endif

        if ( (rc = Artikelquotapf_UpdateKundeEKG(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTAPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTAPF_UPDATEQUOTA: {
        artikelquotapfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ);
#else
        d = (artikelquotapfS *)spBuf;
#endif

        if ( (rc = Artikelquotapf_UpdateQuota(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTAPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELQUOTAPF_UPDATEQUOTA09: {
        artikelquotapfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ);
#else
        d = (artikelquotapfS *)spBuf;
#endif

        if ( (rc = Artikelquotapf_UpdateQuota09(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELQUOTAPF_BES, ARTIKELQUOTAPF_ANZ );
#else
        {
            void * pUnused = ARTIKELQUOTAPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELRESERVE_SELART: {
        artikelreserveS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
#else
        d = (artikelreserveS *)spBuf;
#endif

        if ( (rc = Artikelreserve_SelArt(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ );
#else
        {
            void * pUnused = ARTIKELRESERVE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELRESERVE_SELARTKND: {
        artikelreserveS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
#else
        d = (artikelreserveS *)spBuf;
#endif

        if ( (rc = Artikelreserve_SelArtKnd(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ );
#else
        {
            void * pUnused = ARTIKELRESERVE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELRESERVE_INSERT: {
        artikelreserveS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
#else
        d = (artikelreserveS *)spBuf;
#endif

        if ( (rc = Artikelreserve_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ );
#else
        {
            void * pUnused = ARTIKELRESERVE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELRESERVE_UPDATE: {
        artikelreserveS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
#else
        d = (artikelreserveS *)spBuf;
#endif

        if ( (rc = Artikelreserve_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ );
#else
        {
            void * pUnused = ARTIKELRESERVE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELRESERVE_DELETE: {
        artikelreserveS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
#else
        d = (artikelreserveS *)spBuf;
#endif

        if ( (rc = Artikelreserve_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ );
#else
        {
            void * pUnused = ARTIKELRESERVE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELRESERVE_INSERTBESTAND: {
        artikelreserveS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
#else
        d = (artikelreserveS *)spBuf;
#endif

        if ( (rc = Artikelreserve_InsertBestand(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ );
#else
        {
            void * pUnused = ARTIKELRESERVE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELRESERVE_RESERVSTOCKABS: {
        artikelreserveS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
#else
        d = (artikelreserveS *)spBuf;
#endif

        if ( (rc = Artikelreserve_ReservStockAbs(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ );
#else
        {
            void * pUnused = ARTIKELRESERVE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELRESERVE_SELLISTBESTAND: {
        artikelreserveS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
#else
        d = (artikelreserveS *)spBuf;
#endif

        if ( (rc = Artikelreserve_SelListBestand(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ );
#else
        {
            void * pUnused = ARTIKELRESERVE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELTEXT_SELECT: {
        artikeltextS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELTEXT_BES, ARTIKELTEXT_ANZ);
#else
        d = (artikeltextS *)spBuf;
#endif

        if ( (rc = Artikeltext_Select(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELTEXT_BES, ARTIKELTEXT_ANZ );
#else
        {
            void * pUnused = ARTIKELTEXT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELVERFALL_CHECKSHORTEXPIRY: {
        artikelverfallS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELVERFALL_BES, ARTIKELVERFALL_ANZ);
#else
        d = (artikelverfallS *)spBuf;
#endif

        if ( (rc = Artikelverfall_CheckShortExpiry(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELVERFALL_BES, ARTIKELVERFALL_ANZ );
#else
        {
            void * pUnused = ARTIKELVERFALL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ATICLEAUX_SELLIST: {
        aticleauxS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ATICLEAUX_BES, ATICLEAUX_ANZ);
#else
        d = (aticleauxS *)spBuf;
#endif

        if ( (rc = Aticleaux_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ATICLEAUX_BES, ATICLEAUX_ANZ );
#else
        {
            void * pUnused = ATICLEAUX_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ATICLEAUX_INSERT: {
        aticleauxS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ATICLEAUX_BES, ATICLEAUX_ANZ);
#else
        d = (aticleauxS *)spBuf;
#endif

        if ( (rc = Aticleaux_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ATICLEAUX_BES, ATICLEAUX_ANZ );
#else
        {
            void * pUnused = ATICLEAUX_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ATICLEAUX_UPDATE: {
        aticleauxS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ATICLEAUX_BES, ATICLEAUX_ANZ);
#else
        d = (aticleauxS *)spBuf;
#endif

        if ( (rc = Aticleaux_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ATICLEAUX_BES, ATICLEAUX_ANZ );
#else
        {
            void * pUnused = ATICLEAUX_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ATICLEAUX_DELETE: {
        aticleauxS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ATICLEAUX_BES, ATICLEAUX_ANZ);
#else
        d = (aticleauxS *)spBuf;
#endif

        if ( (rc = Aticleaux_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ATICLEAUX_BES, ATICLEAUX_ANZ );
#else
        {
            void * pUnused = ATICLEAUX_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CCODE_SEL: {
        ccodeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CCODE_BES, CCODE_ANZ);
#else
        d = (ccodeS *)spBuf;
#endif

        if ( (rc = Ccode_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CCODE_BES, CCODE_ANZ );
#else
        {
            void * pUnused = CCODE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CCODE_INSERT: {
        ccodeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CCODE_BES, CCODE_ANZ);
#else
        d = (ccodeS *)spBuf;
#endif

        if ( (rc = Ccode_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CCODE_BES, CCODE_ANZ );
#else
        {
            void * pUnused = CCODE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CCODE_UPDATE: {
        ccodeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CCODE_BES, CCODE_ANZ);
#else
        d = (ccodeS *)spBuf;
#endif

        if ( (rc = Ccode_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CCODE_BES, CCODE_ANZ );
#else
        {
            void * pUnused = CCODE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CCODE_DELETE: {
        ccodeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CCODE_BES, CCODE_ANZ);
#else
        d = (ccodeS *)spBuf;
#endif

        if ( (rc = Ccode_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CCODE_BES, CCODE_ANZ );
#else
        {
            void * pUnused = CCODE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKIMEXBLOCKEXIST_SELEXIST: {
        checkimexblockexistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKIMEXBLOCKEXIST_BES, CHECKIMEXBLOCKEXIST_ANZ);
#else
        d = (checkimexblockexistS *)spBuf;
#endif

        if ( (rc = Checkimexblockexist_SelExist(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKIMEXBLOCKEXIST_BES, CHECKIMEXBLOCKEXIST_ANZ );
#else
        {
            void * pUnused = CHECKIMEXBLOCKEXIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKIMPORTARTICLE_SELIMPORT: {
        checkimportarticleS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKIMPORTARTICLE_BES, CHECKIMPORTARTICLE_ANZ);
#else
        d = (checkimportarticleS *)spBuf;
#endif

        if ( (rc = Checkimportarticle_SelImport(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKIMPORTARTICLE_BES, CHECKIMPORTARTICLE_ANZ );
#else
        {
            void * pUnused = CHECKIMPORTARTICLE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKLISTE5ZENTRAL_ISLISTE5: {
        checkliste5zentralS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKLISTE5ZENTRAL_BES, CHECKLISTE5ZENTRAL_ANZ);
#else
        d = (checkliste5zentralS *)spBuf;
#endif

        if ( (rc = Checkliste5zentral_IsListe5(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKLISTE5ZENTRAL_BES, CHECKLISTE5ZENTRAL_ANZ );
#else
        {
            void * pUnused = CHECKLISTE5ZENTRAL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CODEBLOCAGEINFO_SELTEXT: {
        codeblocageinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CODEBLOCAGEINFO_BES, CODEBLOCAGEINFO_ANZ);
#else
        d = (codeblocageinfoS *)spBuf;
#endif

        if ( (rc = Codeblocageinfo_SelText(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CODEBLOCAGEINFO_BES, CODEBLOCAGEINFO_ANZ );
#else
        {
            void * pUnused = CODEBLOCAGEINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISPOINFO_SELDISPOINFO: {
        dispoinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISPOINFO_BES, DISPOINFO_ANZ);
#else
        d = (dispoinfoS *)spBuf;
#endif

        if ( (rc = Dispoinfo_SelDispoInfo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISPOINFO_BES, DISPOINFO_ANZ );
#else
        {
            void * pUnused = DISPOINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case HERSTELLER_SELHERSTELLER: {
        herstellerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, HERSTELLER_BES, HERSTELLER_ANZ);
#else
        d = (herstellerS *)spBuf;
#endif

        if ( (rc = Hersteller_SelHersteller(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, HERSTELLER_BES, HERSTELLER_ANZ );
#else
        {
            void * pUnused = HERSTELLER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case LPPRCODE_SEL: {
        lpprcodeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, LPPRCODE_BES, LPPRCODE_ANZ);
#else
        d = (lpprcodeS *)spBuf;
#endif

        if ( (rc = Lpprcode_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, LPPRCODE_BES, LPPRCODE_ANZ );
#else
        {
            void * pUnused = LPPRCODE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAXARTICLEQUOTA_SELMAX: {
        maxarticlequotaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAXARTICLEQUOTA_BES, MAXARTICLEQUOTA_ANZ);
#else
        d = (maxarticlequotaS *)spBuf;
#endif

        if ( (rc = Maxarticlequota_SelMax(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAXARTICLEQUOTA_BES, MAXARTICLEQUOTA_ANZ );
#else
        {
            void * pUnused = MAXARTICLEQUOTA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case OCCASION_SELLIST: {
        occasionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, OCCASION_BES, OCCASION_ANZ);
#else
        d = (occasionS *)spBuf;
#endif

        if ( (rc = Occasion_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, OCCASION_BES, OCCASION_ANZ );
#else
        {
            void * pUnused = OCCASION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PHARMGRP_SEL: {
        pharmgrpS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PHARMGRP_BES, PHARMGRP_ANZ);
#else
        d = (pharmgrpS *)spBuf;
#endif

        if ( (rc = Pharmgrp_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PHARMGRP_BES, PHARMGRP_ANZ );
#else
        {
            void * pUnused = PHARMGRP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PREISANZTYP_SELPREIS: {
        preisanztypS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PREISANZTYP_BES, PREISANZTYP_ANZ);
#else
        d = (preisanztypS *)spBuf;
#endif

        if ( (rc = Preisanztyp_SelPreis(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PREISANZTYP_BES, PREISANZTYP_ANZ );
#else
        {
            void * pUnused = PREISANZTYP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PRICEHIST_SEL: {
        pricehistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PRICEHIST_BES, PRICEHIST_ANZ);
#else
        d = (pricehistS *)spBuf;
#endif

        if ( (rc = Pricehist_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PRICEHIST_BES, PRICEHIST_ANZ );
#else
        {
            void * pUnused = PRICEHIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOANZ_SELPROMO: {
        promoanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOANZ_BES, PROMOANZ_ANZ);
#else
        d = (promoanzS *)spBuf;
#endif

        if ( (rc = Promoanz_SelPromo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOANZ_BES, PROMOANZ_ANZ );
#else
        {
            void * pUnused = PROMOANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case REIMPORT_SELAUSWAHL: {
        reimportS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, REIMPORT_BES, REIMPORT_ANZ);
#else
        d = (reimportS *)spBuf;
#endif

        if ( (rc = Reimport_SelAuswahl(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, REIMPORT_BES, REIMPORT_ANZ );
#else
        {
            void * pUnused = REIMPORT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STELLER_SELLIST: {
        stellerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, STELLER_BES, STELLER_ANZ);
#else
        d = (stellerS *)spBuf;
#endif

        if ( (rc = Steller_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, STELLER_BES, STELLER_ANZ );
#else
        {
            void * pUnused = STELLER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STELLERTYP_SELTYP: 
    {
        stellertypS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, STELLERTYP_BES, STELLERTYP_ANZ);
#else
        d = (stellertypS *)spBuf;
#endif

        if ( (rc = Stellertyp_SelTyp(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, STELLERTYP_BES, STELLERTYP_ANZ );
#else
        {
            void * pUnused = STELLERTYP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATION_SELLIST:
    {
        stockreservationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, STOCKRESERVATION_BES, STOCKRESERVATION_ANZ);
#else
        d = (stockreservationS *)spBuf;
#endif

        if ( (rc = Stockreservation_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, STOCKRESERVATION_BES, STOCKRESERVATION_ANZ );
#else
        {
            void * pUnused = STOCKRESERVATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATION_SELSUM: {
        stockreservationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, STOCKRESERVATION_BES, STOCKRESERVATION_ANZ);
#else
        d = (stockreservationS *)spBuf;
#endif

        if ( (rc = Stockreservation_SelSum(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, STOCKRESERVATION_BES, STOCKRESERVATION_ANZ );
#else
        {
            void * pUnused = STOCKRESERVATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATION_SELLISTALL:
    {
        stockreservationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATION_BES, STOCKRESERVATION_ANZ);
#else
        d = (stockreservationS*)spBuf;
#endif

        if ((rc = Stockreservation_SelListAll(d, &tErrorMsg, false)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATION_BES, STOCKRESERVATION_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATION_DELETEENTRY: {
        stockreservationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATION_BES, STOCKRESERVATION_ANZ);
#else
        d = (stockreservationS*)spBuf;
#endif
        CstStockReservation stockreservation(d);
        if ((rc = stockreservation.DeleteEntry(&tErrorMsg, false)) < 0)
        //if ((rc = Stockreservation_DeleteEntry(d, &tErrorMsg, true)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATION_BES, STOCKRESERVATION_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }   
    case STOCKRESERVATIONIBTREQUEST_SELIBTREQUEST: {
        stockreservationibtrequestS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATIONIBTREQUEST_BES, STOCKRESERVATIONIBTREQUEST_ANZ);
#else
        d = (stockreservationibtrequestS*)spBuf;
#endif

        if ((rc = Stockreservation_SelIBTRequet(d, &tErrorMsg, false)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATIONIBTREQUEST_BES, STOCKRESERVATIONIBTREQUEST_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATIONIBTREQUEST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATIONARTICLERESERV_SELARTICLERESERVATION: {
        stockreservationarticlereservS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATIONARTICLERESERV_BES, STOCKRESERVATIONARTICLERESERV_ANZ);
#else
        d = (stockreservationarticlereservS*)spBuf;
#endif

        if ((rc = Stockreservation_SelArticleReserv(d, &tErrorMsg, false)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATIONARTICLERESERV_BES, STOCKRESERVATIONARTICLERESERV_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATIONARTICLERESERV_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATIONARTICLERESERV_UPDATEARTICLERESERVATION: {
        stockreservationarticlereservS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATIONARTICLERESERV_BES, STOCKRESERVATIONARTICLERESERV_ANZ);
#else
        d = (stockreservationarticlereservS*)spBuf;
#endif

        if ((rc = Stockreservation_UpdateArticleReservation(d, &tErrorMsg, true)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATIONARTICLERESERV_BES, STOCKRESERVATIONARTICLERESERV_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATIONARTICLERESERV_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATIONARTIKELLOKAL_SELARTIKELLOKAL: {
        stockreservationartikellokalS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATIONARTIKELLOKAL_BES, STOCKRESERVATIONARTIKELLOKAL_ANZ);
#else
        d = (stockreservationartikellokalS*)spBuf;
#endif

        if ((rc = Stockreservation_SelArtikelLokal(d, &tErrorMsg, false)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATIONARTIKELLOKAL_BES, STOCKRESERVATIONARTIKELLOKAL_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATIONARTIKELLOKAL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATIONARTIKELLOKAL_UPDATEARTIKELLOKAL: {
        stockreservationartikellokalS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATIONARTIKELLOKAL_BES, STOCKRESERVATIONARTIKELLOKAL_ANZ);
#else
        d = (stockreservationartikellokalS*)spBuf;
#endif

        if ((rc = Stockreservation_UpdateArtikelLokal(d, &tErrorMsg, true)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATIONARTIKELLOKAL_BES, STOCKRESERVATIONARTIKELLOKAL_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATIONARTIKELLOKAL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATIONNACHLIEFERPOS_SELNACHLIEFERPOS: {
        stockreservationnachlieferposS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATIONNACHLIEFERPOS_BES, STOCKRESERVATIONNACHLIEFERPOS_ANZ);
#else
        d = (stockreservationnachlieferposS*)spBuf;
#endif

        if ((rc = Stockreservation_SelNachlieferPos(d, &tErrorMsg, false)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATIONNACHLIEFERPOS_BES, STOCKRESERVATIONNACHLIEFERPOS_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATIONNACHLIEFERPOS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATIONORDER_SELORDER: {
        stockreservationorderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATIONORDER_BES, STOCKRESERVATIONORDER_ANZ);
#else
        d = (stockreservationnachlieferposS*)spBuf;
#endif

        if ((rc = Stockreservation_SelOrder(d, &tErrorMsg, false)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATIONORDER_BES, STOCKRESERVATIONORDER_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATIONORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKRESERVATIONNACHLIEFERPOS_DELETENACHLIEFERPOS: {
        stockreservationnachlieferposS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, STOCKRESERVATIONNACHLIEFERPOS_BES, STOCKRESERVATIONNACHLIEFERPOS_ANZ);
#else
        d = (stockreservationnachlieferposS*)spBuf;
#endif

        if ((rc = Stockreservation_DeleteNachlieferPos(d, &tErrorMsg, true)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        * ipLen = buf_kon(TO_UEB, (char*)d, spOut, STOCKRESERVATIONNACHLIEFERPOS_BES, STOCKRESERVATIONNACHLIEFERPOS_ANZ);
#else
        {
            void* pUnused = STOCKRESERVATIONNACHLIEFERPOS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SUPPLINFO_SELSUPPINFO: {
        supplinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SUPPLINFO_BES, SUPPLINFO_ANZ);
#else
        d = (supplinfoS *)spBuf;
#endif

        if ( (rc = Supplinfo_SelSuppInfo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SUPPLINFO_BES, SUPPLINFO_ANZ );
#else
        {
            void * pUnused = SUPPLINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDART_SEL: {
        delayedartS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDART_BES, DELAYEDART_ANZ);
#else
        d = (delayedartS *)spBuf;
#endif

        if ( (rc = delayedart_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDART_BES, DELAYEDART_ANZ );
#else
        {
            void * pUnused = DELAYEDART_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDART_INSERT: {
        delayedartS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDART_BES, DELAYEDART_ANZ);
#else
        d = (delayedartS *)spBuf;
#endif

        if ( (rc = delayedart_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDART_BES, DELAYEDART_ANZ );
#else
        {
            void * pUnused = DELAYEDART_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDART_UPDATE: {
        delayedartS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDART_BES, DELAYEDART_ANZ);
#else
        d = (delayedartS *)spBuf;
#endif

        if ( (rc = delayedart_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDART_BES, DELAYEDART_ANZ );
#else
        {
            void * pUnused = DELAYEDART_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDART_DELETE: {
        delayedartS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDART_BES, DELAYEDART_ANZ);
#else
        d = (delayedartS *)spBuf;
#endif

        if ( (rc = delayedart_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDART_BES, DELAYEDART_ANZ );
#else
        {
            void * pUnused = DELAYEDART_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISCOUNTANZ_SELLIST: {
        discountanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
#else
        d = (discountanzS *)spBuf;
#endif

        if ( (rc = discountanz_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ );
#else
        {
            void * pUnused = DISCOUNTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISCOUNTANZ_SELLISTCST: {
        discountanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
#else
        d = (discountanzS *)spBuf;
#endif

        if ( (rc = discountanz_SelListCst(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ );
#else
        {
            void * pUnused = DISCOUNTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISCOUNTANZ_SELLISTCSTEKG: {
        discountanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
#else
        d = (discountanzS *)spBuf;
#endif

        if ( (rc = discountanz_SelListCstEKG(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ );
#else
        {
            void * pUnused = DISCOUNTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISCOUNTANZ_SELLISTDG: {
        discountanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
#else
        d = (discountanzS *)spBuf;
#endif

        if ( (rc = discountanz_SelListDG(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ );
#else
        {
            void * pUnused = DISCOUNTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISCOUNTANZ_SELLISTGRP: {
        discountanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
#else
        d = (discountanzS *)spBuf;
#endif

        if ( (rc = discountanz_SelListGrp(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ );
#else
        {
            void * pUnused = DISCOUNTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISCOUNTANZ_SELLISTGRPHERST: {
        discountanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
#else
        d = (discountanzS *)spBuf;
#endif

        if ( (rc = discountanz_SelListGrpHerst(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ );
#else
        {
            void * pUnused = DISCOUNTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISCOUNTANZ_SELLISTHERST: {
        discountanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
#else
        d = (discountanzS *)spBuf;
#endif

        if ( (rc = discountanz_SelListHerst(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ );
#else
        {
            void * pUnused = DISCOUNTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISCOUNTANZ_SELLLISTGRPDG: {
        discountanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
#else
        d = (discountanzS *)spBuf;
#endif

        if ( (rc = discountanz_SellListGrpDG(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ );
#else
        {
            void * pUnused = DISCOUNTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOCKENTRY_SELLIST: {
        stockentryS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, STOCKENTRY_BES, STOCKENTRY_ANZ);
#else
        d = (stockentryS *)spBuf;
#endif

        if ( (rc = stockentry_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, STOCKENTRY_BES, STOCKENTRY_ANZ );
#else
        {
            void * pUnused = STOCKENTRY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case AUFPOSRAB_SELLIST: {
        aufposrabS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, AUFPOSRAB_BES, AUFPOSRAB_ANZ);
#else
        d = (aufposrabS *)spBuf;
#endif

        if ( (rc = Aufposrab_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, AUFPOSRAB_BES, AUFPOSRAB_ANZ );
#else
        {
            void * pUnused = AUFPOSRAB_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case AUFTRAGWERTE_SELWERTE: {
        auftragwerteS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, AUFTRAGWERTE_BES, AUFTRAGWERTE_ANZ);
#else
        d = (auftragwerteS *)spBuf;
#endif

        if ( (rc = Auftragwerte_SelWerte(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, AUFTRAGWERTE_BES, AUFTRAGWERTE_ANZ );
#else
        {
            void * pUnused = AUFTRAGWERTE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case AUFTRAGWERTEALT_SELWERTE: {
        auftragwertealtS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, AUFTRAGWERTEALT_BES, AUFTRAGWERTEALT_ANZ);
#else
        d = (auftragwertealtS *)spBuf;
#endif

        if ( (rc = Auftragwertealt_SelWerte(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, AUFTRAGWERTEALT_BES, AUFTRAGWERTEALT_ANZ );
#else
        {
            void * pUnused = AUFTRAGWERTEALT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKORDERIV_SELKONSIG: {
        checkorderivS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKORDERIV_BES, CHECKORDERIV_ANZ);
#else
        d = (checkorderivS *)spBuf;
#endif

        if ( (rc = Checkorderiv_SelKonsig(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKORDERIV_BES, CHECKORDERIV_ANZ );
#else
        {
            void * pUnused = CHECKORDERIV_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKORDERIV_SELMANU: {
        checkorderivS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKORDERIV_BES, CHECKORDERIV_ANZ);
#else
        d = (checkorderivS *)spBuf;
#endif

        if ( (rc = Checkorderiv_SelManu(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKORDERIV_BES, CHECKORDERIV_ANZ );
#else
        {
            void * pUnused = CHECKORDERIV_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case COLLECTIVEORDERS_SELCVORDER:
    {
        collectiveordersS s, * d;
        d = &s;

        int len = 0;


#ifndef __DADE_LOAD__
        len = buf_kon(FROM_UEB, (char*)d, spIn, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ);

#else
        d = (collectiveordersS*)spBuf;
#endif

        if ((rc = Collectiveorders_SelCVOrder(d, &tErrorMsg, false)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
        }
        else
        {

#ifndef __DADE_LOAD__
            len = buf_kon(TO_UEB, (char*)d, spOut, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ);
            *ipLen = len;
#else
            {
                void* pUnused = COLLECTIVEORDERS_BES;
                pUnused = pUnused;
            }
#endif
        }
        return rc;
    }
    case COLLECTIVEORDERS_SELCVORDERCOUNT:
    {
        collectiveordersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char*)d, spIn, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ);
#else
        d = (collectiveordersS*)spBuf;
#endif

        if ((rc = Collectiveorders_SelCVOrderCount(d, &tErrorMsg, false)) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);

        }
        else
        {
#ifndef __DADE_LOAD__
            * ipLen = buf_kon(TO_UEB, (char*)d, spOut, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ);
#else
            {
                void* pUnused = COLLECTIVEORDERS_BES;
                pUnused = pUnused;
            }
#endif
        }
        return rc;
    }
    case COLLECTIVEORDERS_SELCVORDERDE:
    {
        collectiveordersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ);
#else
        d = (collectiveordersS *)spBuf;
#endif

        if ( (rc = Collectiveorders_SelCVOrderDE(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, COLLECTIVEORDERS_BES, COLLECTIVEORDERS_ANZ );
#else
        {
            void * pUnused = COLLECTIVEORDERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KNDPPFLAG_GETZURUECKFLAG: {
        kndppflagS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KNDPPFLAG_BES, KNDPPFLAG_ANZ);
#else
        d = (kndppflagS *)spBuf;
#endif

        if ( (rc = Kndppflag_GetZurueckFlag(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KNDPPFLAG_BES, KNDPPFLAG_ANZ );
#else
        {
            void * pUnused = KNDPPFLAG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case POSCHANGE_SELLIST: {
        poschangeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, POSCHANGE_BES, POSCHANGE_ANZ);
#else
        d = (poschangeS *)spBuf;
#endif

        if ( (rc = Poschange_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, POSCHANGE_BES, POSCHANGE_ANZ );
#else
        {
            void * pUnused = POSCHANGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case POSCHANGE_UPDATE: {
        poschangeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, POSCHANGE_BES, POSCHANGE_ANZ);
#else
        d = (poschangeS *)spBuf;
#endif

        if ( (rc = Poschange_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, POSCHANGE_BES, POSCHANGE_ANZ );
#else
        {
            void * pUnused = POSCHANGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case POSCHANGEHIST_SELLIST: {
        poschangehistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, POSCHANGEHIST_BES, POSCHANGEHIST_ANZ);
#else
        d = (poschangehistS *)spBuf;
#endif

        if ( (rc = Poschangehist_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, POSCHANGEHIST_BES, POSCHANGEHIST_ANZ );
#else
        {
            void * pUnused = POSCHANGEHIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case POSCHANGEHIST_UPDATE: {
        poschangehistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, POSCHANGEHIST_BES, POSCHANGEHIST_ANZ);
#else
        d = (poschangehistS *)spBuf;
#endif

        if ( (rc = Poschangehist_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, POSCHANGEHIST_BES, POSCHANGEHIST_ANZ );
#else
        {
            void * pUnused = POSCHANGEHIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROLINK_SELPROLINK: {
        prolinkS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROLINK_BES, PROLINK_ANZ);
#else
        d = (prolinkS *)spBuf;
#endif

        if ( (rc = Prolink_SelProLink(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROLINK_BES, PROLINK_ANZ );
#else
        {
            void * pUnused = PROLINK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROLINK_INSERT: {
        prolinkS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROLINK_BES, PROLINK_ANZ);
#else
        d = (prolinkS *)spBuf;
#endif

        if ( (rc = Prolink_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROLINK_BES, PROLINK_ANZ );
#else
        {
            void * pUnused = PROLINK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROLINKACT_SELPROLINK: {
        prolinkactS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROLINKACT_BES, PROLINKACT_ANZ);
#else
        d = (prolinkactS *)spBuf;
#endif

        if ( (rc = Prolinkact_SelProLink(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROLINKACT_BES, PROLINKACT_ANZ );
#else
        {
            void * pUnused = PROLINKACT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROLINKACT_INSERT: {
        prolinkactS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROLINKACT_BES, PROLINKACT_ANZ);
#else
        d = (prolinkactS *)spBuf;
#endif

        if ( (rc = Prolinkact_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROLINKACT_BES, PROLINKACT_ANZ );
#else
        {
            void * pUnused = PROLINKACT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKATTACH_SEL: {
        callbackattachS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ);
#else
        d = (callbackattachS *)spBuf;
#endif

        if ( (rc = Callbackattach_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ );
#else
        {
            void * pUnused = CALLBACKATTACH_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKATTACH_SELVZ: {
        callbackattachS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ);
#else
        d = (callbackattachS *)spBuf;
#endif

        if ( (rc = Callbackattach_SelVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ );
#else
        {
            void * pUnused = CALLBACKATTACH_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKATTACH_INSERT: {
        callbackattachS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ);
#else
        d = (callbackattachS *)spBuf;
#endif

        if ( (rc = Callbackattach_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ );
#else
        {
            void * pUnused = CALLBACKATTACH_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKATTACH_DELETE: {
        callbackattachS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ);
#else
        d = (callbackattachS *)spBuf;
#endif

        if ( (rc = Callbackattach_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ );
#else
        {
            void * pUnused = CALLBACKATTACH_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKPARTNER_SELPARTNER: {
        callbackpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ);
#else
        d = (callbackpartnerS *)spBuf;
#endif

        if ( (rc = Callbackpartner_SelPartner(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ );
#else
        {
            void * pUnused = CALLBACKPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKPARTNER_SELECTALL: {
        callbackpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ);
#else
        d = (callbackpartnerS *)spBuf;
#endif

        if ( (rc = Callbackpartner_SelectAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ );
#else
        {
            void * pUnused = CALLBACKPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKPARTNER_SELECTALLVZ: {
        callbackpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ);
#else
        d = (callbackpartnerS *)spBuf;
#endif

        if ( (rc = Callbackpartner_SelectAllVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ );
#else
        {
            void * pUnused = CALLBACKPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKPARTNER_UPDATE: {
        callbackpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ);
#else
        d = (callbackpartnerS *)spBuf;
#endif

        if ( (rc = Callbackpartner_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ );
#else
        {
            void * pUnused = CALLBACKPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKPARTNER_DELETECALLBACKPARTNER: {
        callbackpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ);
#else
        d = (callbackpartnerS *)spBuf;
#endif

        if ( (rc = Callbackpartner_DeleteCallbackPartner(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ );
#else
        {
            void * pUnused = CALLBACKPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKPARTNER_INSERTWITHNEWNO: {
        callbackpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ);
#else
        d = (callbackpartnerS *)spBuf;
#endif

        if ( (rc = Callbackpartner_InsertWithNewNo(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ );
#else
        {
            void * pUnused = CALLBACKPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTIME_SELECTCALLBACKPARTNER: {
        callbacktimeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTIME_BES, CALLBACKTIME_ANZ);
#else
        d = (callbacktimeS *)spBuf;
#endif

        if ( (rc = Callbacktime_SelectCallbackPartner(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTIME_BES, CALLBACKTIME_ANZ );
#else
        {
            void * pUnused = CALLBACKTIME_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTIME_INSERT: {
        callbacktimeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTIME_BES, CALLBACKTIME_ANZ);
#else
        d = (callbacktimeS *)spBuf;
#endif

        if ( (rc = Callbacktime_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTIME_BES, CALLBACKTIME_ANZ );
#else
        {
            void * pUnused = CALLBACKTIME_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTIME_DELETEALLNO: {
        callbacktimeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTIME_BES, CALLBACKTIME_ANZ);
#else
        d = (callbacktimeS *)spBuf;
#endif

        if ( (rc = Callbacktime_DeleteAllNo(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTIME_BES, CALLBACKTIME_ANZ );
#else
        {
            void * pUnused = CALLBACKTIME_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTIME_DELETECALLBACKTIME: {
        callbacktimeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTIME_BES, CALLBACKTIME_ANZ);
#else
        d = (callbacktimeS *)spBuf;
#endif

        if ( (rc = Callbacktime_DeleteCallbackTime(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTIME_BES, CALLBACKTIME_ANZ );
#else
        {
            void * pUnused = CALLBACKTIME_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKCRITICAL_SELCRITICAL: {
        callbackcriticalS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKCRITICAL_BES, CALLBACKCRITICAL_ANZ);
#else
        d = (callbackcriticalS *)spBuf;
#endif

        if ( (rc = Callbackcritical_SelCritical(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKCRITICAL_BES, CALLBACKCRITICAL_ANZ );
#else
        {
            void * pUnused = CALLBACKCRITICAL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKDIVISION_SELDIVISION: {
        callbackdivisionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ);
#else
        d = (callbackdivisionS *)spBuf;
#endif

        if ( (rc = Callbackdivision_SelDivision(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ );
#else
        {
            void * pUnused = CALLBACKDIVISION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKDIVISION_SELLIST: {
        callbackdivisionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ);
#else
        d = (callbackdivisionS *)spBuf;
#endif

        if ( (rc = Callbackdivision_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ );
#else
        {
            void * pUnused = CALLBACKDIVISION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKDIVISION_SELLISTALL: {
        callbackdivisionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ);
#else
        d = (callbackdivisionS *)spBuf;
#endif

        if ( (rc = Callbackdivision_SelListAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ );
#else
        {
            void * pUnused = CALLBACKDIVISION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKDIVISION_UPDATE: {
        callbackdivisionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ);
#else
        d = (callbackdivisionS *)spBuf;
#endif

        if ( (rc = Callbackdivision_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ );
#else
        {
            void * pUnused = CALLBACKDIVISION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKDIVISION_DELETE: {
        callbackdivisionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ);
#else
        d = (callbackdivisionS *)spBuf;
#endif

        if ( (rc = Callbackdivision_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ );
#else
        {
            void * pUnused = CALLBACKDIVISION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKDIVISION_INSERTWITHNEWNO: {
        callbackdivisionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ);
#else
        d = (callbackdivisionS *)spBuf;
#endif

        if ( (rc = Callbackdivision_InsertWithNewNo(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ );
#else
        {
            void * pUnused = CALLBACKDIVISION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREASONS_SELLIST: {
        callbackreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ);
#else
        d = (callbackreasonsS *)spBuf;
#endif

        if ( (rc = Callbackreasons_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ );
#else
        {
            void * pUnused = CALLBACKREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREASONS_UPDATE: {
        callbackreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ);
#else
        d = (callbackreasonsS *)spBuf;
#endif

        if ( (rc = Callbackreasons_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ );
#else
        {
            void * pUnused = CALLBACKREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREASONS_DELETE: {
        callbackreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ);
#else
        d = (callbackreasonsS *)spBuf;
#endif

        if ( (rc = Callbackreasons_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ );
#else
        {
            void * pUnused = CALLBACKREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREASONS_DELETEALLNO: {
        callbackreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ);
#else
        d = (callbackreasonsS *)spBuf;
#endif

        if ( (rc = Callbackreasons_DeleteAllNo(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ );
#else
        {
            void * pUnused = CALLBACKREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREASONS_INSERTWITHNEWNO: {
        callbackreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ);
#else
        d = (callbackreasonsS *)spBuf;
#endif

        if ( (rc = Callbackreasons_InsertWithNewNo(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ );
#else
        {
            void * pUnused = CALLBACKREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREMARKS_SELLIST: {
        callbackremarksS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ);
#else
        d = (callbackremarksS *)spBuf;
#endif

        if ( (rc = Callbackremarks_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ );
#else
        {
            void * pUnused = CALLBACKREMARKS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREMARKS_SELREMARK: {
        callbackremarksS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ);
#else
        d = (callbackremarksS *)spBuf;
#endif

        if ( (rc = Callbackremarks_SelRemark(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ );
#else
        {
            void * pUnused = CALLBACKREMARKS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREMARKS_INSERT: {
        callbackremarksS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ);
#else
        d = (callbackremarksS *)spBuf;
#endif

        if ( (rc = Callbackremarks_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ );
#else
        {
            void * pUnused = CALLBACKREMARKS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREMARKS_UPDATE: {
        callbackremarksS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ);
#else
        d = (callbackremarksS *)spBuf;
#endif

        if ( (rc = Callbackremarks_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ );
#else
        {
            void * pUnused = CALLBACKREMARKS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKREMARKS_DELETEREMARK: {
        callbackremarksS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ);
#else
        d = (callbackremarksS *)spBuf;
#endif

        if ( (rc = Callbackremarks_DeleteRemark(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ );
#else
        {
            void * pUnused = CALLBACKREMARKS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELALLLOCKED: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelAllLocked(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELALLLOCKEDVZ: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelAllLockedVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELALLNOTDONE: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelAllNotDone(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELALLNOTDONEVZ: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelAllNotDoneVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELCALLBACKFUTURE: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelCallbackFuture(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELCALLBACKFUTUREVZ: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelCallbackFutureVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELCALLBACKOPEN: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelCallbackOpen(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELCALLBACKOPENVZ: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelCallbackOpenVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELCALLBACKWISHED: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelCallbackWished(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODO_SELCALLBACKWISHEDVZ: {
        callbacktodoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
#else
        d = (callbacktodoS *)spBuf;
#endif

        if ( (rc = Callbacktodo_SelCallbackWishedVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODO_BES, CALLBACKTODO_ANZ );
#else
        {
            void * pUnused = CALLBACKTODO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELALLLOCKED: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelAllLocked(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELALLLOCKEDVZ: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelAllLockedVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELALLNOTDONE: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelAllNotDone(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELALLNOTDONEVZ: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelAllNotDoneVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELCALLBACKFUTURE: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelCallbackFuture(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELCALLBACKFUTUREVZ: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelCallbackFutureVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELCALLBACKOPEN: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelCallbackOpen(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELCALLBACKOPENVZ: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelCallbackOpenVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELCALLBACKWISHED: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelCallbackWished(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKTODONEW_SELCALLBACKWISHEDVZ: {
        callbacktodonewS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
#else
        d = (callbacktodonewS *)spBuf;
#endif

        if ( (rc = Callbacktodonew_SelCallbackWishedVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ );
#else
        {
            void * pUnused = CALLBACKTODONEW_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKSATATUS_SELECTALL: {
        callbackstatusS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKSTATUS_BES, CALLBACKSTATUS_ANZ);
#else
        d = (callbackstatusS *)spBuf;
#endif

        if ( (rc = Callbackstatus_SelectAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKSTATUS_BES, CALLBACKSTATUS_ANZ);
#else
        {
            void * pUnused = CALLBACKSTATUS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKITEMS_SELCALLBACKWISH: {
        callbackitemsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ);
#else
        d = (callbackitemsS *)spBuf;
#endif

        if ( (rc = callbackitems_SelCallbackWish(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ );
#else
        {
            void * pUnused = CALLBACKITEMS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKITEMS_SELNO: {
        callbackitemsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ);
#else
        d = (callbackitemsS *)spBuf;
#endif

        if ( (rc = callbackitems_SelNo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ );
#else
        {
            void * pUnused = CALLBACKITEMS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKITEMS_SELNOTDONE: {
        callbackitemsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ);
#else
        d = (callbackitemsS *)spBuf;
#endif

        if ( (rc = callbackitems_SelNotDone(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ );
#else
        {
            void * pUnused = CALLBACKITEMS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKITEMS_SELLOCKED: {
        callbackitemsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ);
#else
        d = (callbackitemsS *)spBuf;
#endif

        if ( (rc = callbackitems_Sellocked(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ );
#else
        {
            void * pUnused = CALLBACKITEMS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKITEMS_UPDATEITEM: {
        callbackitemsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ);
#else
        d = (callbackitemsS *)spBuf;
#endif

        if ( (rc = callbackitems_UpdateItem(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ );
#else
        {
            void * pUnused = CALLBACKITEMS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CALLBACKITEMS_INSERTWITHNEWNO: {
        callbackitemsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ);
#else
        d = (callbackitemsS *)spBuf;
#endif

        if ( (rc = callbackitems_InsertWithNewNo(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ );
#else
        {
            void * pUnused = CALLBACKITEMS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKORDEREXIST_SELAUFTRAG: {
        checkorderexistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKORDEREXIST_BES, CHECKORDEREXIST_ANZ);
#else
        d = (checkorderexistS *)spBuf;
#endif

        if ( (rc = Checkorderexist_SelAuftrag(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKORDEREXIST_BES, CHECKORDEREXIST_ANZ );
#else
        {
            void * pUnused = CHECKORDEREXIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMTERDRIVER_SELPARAMETER: {
        mcallparamterdriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMTERDRIVER_BES, MCALLPARAMTERDRIVER_ANZ);
#else
        d = (mcallparamterdriverS *)spBuf;
#endif

        if ( (rc = Mcallparamterdriver_SelParameter(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMTERDRIVER_BES, MCALLPARAMTERDRIVER_ANZ );
#else
        {
            void * pUnused = MCALLPARAMTERDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMTERDRIVER_UPDTIME: {
        mcallparamterdriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMTERDRIVER_BES, MCALLPARAMTERDRIVER_ANZ);
#else
        d = (mcallparamterdriverS *)spBuf;
#endif

        if ( (rc = Mcallparamterdriver_UpdTime(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMTERDRIVER_BES, MCALLPARAMTERDRIVER_ANZ );
#else
        {
            void * pUnused = MCALLPARAMTERDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMTERDRIVER_SETCALLSTOFINISH: {
        mcallparamterdriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMTERDRIVER_BES, MCALLPARAMTERDRIVER_ANZ);
#else
        d = (mcallparamterdriverS *)spBuf;
#endif

        if ( (rc = Mcallparamterdriver_SetCallsToFinish(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMTERDRIVER_BES, MCALLPARAMTERDRIVER_ANZ );
#else
        {
            void * pUnused = MCALLPARAMTERDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAY_SELCALLPLANDAY: {
        mcustomercallplandayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
#else
        d = (mcustomercallplandayS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanday_SelCallPlanDay(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAY_SELLISTFUTURE: {
        mcustomercallplandayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
#else
        d = (mcustomercallplandayS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanday_SelListFuture(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAY_ENDBROWSE: {
        mcustomercallplandayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
#else
        d = (mcustomercallplandayS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanday_EndBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAY_INSERT: {
        mcustomercallplandayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
#else
        d = (mcustomercallplandayS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanday_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAY_SELLIST: {
        mcustomercallplandayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
#else
        d = (mcustomercallplandayS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanday_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAY_SELLISTHIST: {
        mcustomercallplandayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
#else
        d = (mcustomercallplandayS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanday_SelListHist(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAY_SETCUSTOMERCALLFREE: {
        mcustomercallplandayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
#else
        d = (mcustomercallplandayS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanday_SetCustomerCallFree(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAY_STARTBROWSE: {
        mcustomercallplandayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
#else
        d = (mcustomercallplandayS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanday_StartBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAY_UPDCUSTOMERCALLPLANDAY: {
        mcustomercallplandayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
#else
        d = (mcustomercallplandayS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanday_UpdCustomerCallPlanDay(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYHIST_SELLIST: {
        mcustomercallplandayhistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYHIST_BES, MCUSTOMERCALLPLANDAYHIST_ANZ);
#else
        d = (mcustomercallplandayhistS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandayhist_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYHIST_BES, MCUSTOMERCALLPLANDAYHIST_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYHIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYHIST_DELALL: {
        mcustomercallplandayhistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYHIST_BES, MCUSTOMERCALLPLANDAYHIST_ANZ);
#else
        d = (mcustomercallplandayhistS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandayhist_DelAll(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYHIST_BES, MCUSTOMERCALLPLANDAYHIST_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYHIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYHIST_DELALLOLDER: {
        mcustomercallplandayhistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYHIST_BES, MCUSTOMERCALLPLANDAYHIST_ANZ);
#else
        d = (mcustomercallplandayhistS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandayhist_DelAllOlder(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYHIST_BES, MCUSTOMERCALLPLANDAYHIST_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYHIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANRECALLINWORK_SELECT: {
        mcustomercallplanrecallinworkS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ);
#else
        d = (mcustomercallplanrecallinworkS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanrecallinwork_Select(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANRECALLINWORK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANRECALLINWORK_INSERT: {
        mcustomercallplanrecallinworkS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ);
#else
        d = (mcustomercallplanrecallinworkS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanrecallinwork_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANRECALLINWORK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANRECALLINWORK_UPDATE: {
        mcustomercallplanrecallinworkS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ);
#else
        d = (mcustomercallplanrecallinworkS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanrecallinwork_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANRECALLINWORK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANRECALLINWORK_DELETE: {
        mcustomercallplanrecallinworkS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ);
#else
        d = (mcustomercallplanrecallinworkS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanrecallinwork_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANRECALLINWORK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYDRIVER_ENDBROWSE: {
        mcustomercallplandaydriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ);
#else
        d = (mcustomercallplandaydriverS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandaydriver_EndBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYDRIVER_SELLIST: {
        mcustomercallplandaydriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ);
#else
        d = (mcustomercallplandaydriverS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandaydriver_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYDRIVER_SELUNICUSTOMERCALLPLAN: {
        mcustomercallplandaydriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ);
#else
        d = (mcustomercallplandaydriverS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandaydriver_SelUniCustomerCallplan(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYDRIVER_STARTBROWSE: {
        mcustomercallplandaydriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ);
#else
        d = (mcustomercallplandaydriverS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandaydriver_StartBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYDRIVER_UPDCUSTOMERCALLPLAN: {
        mcustomercallplandaydriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ);
#else
        d = (mcustomercallplandaydriverS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandaydriver_UpdCustomerCallplan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYDRIVER_UPDCUSTOMERCALLPLANWITHOUTTRANSACTION: {
        mcustomercallplandaydriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ);
#else
        d = (mcustomercallplandaydriverS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandaydriver_UpdCustomerCallplanWithoutTransaction(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANDAYDRIVER_UPDWITHOUTTRANSACTION: {
        mcustomercallplandaydriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ);
#else
        d = (mcustomercallplandaydriverS *)spBuf;
#endif

        if ( (rc = Mcustomercallplandaydriver_UpdWithoutTransaction(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANDAYDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERLASTCALL_ENDBROWSE: {
        mcustomerlastcallS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERLASTCALL_BES, MCUSTOMERLASTCALL_ANZ);
#else
        d = (mcustomerlastcallS *)spBuf;
#endif

        if ( (rc = Mcustomerlastcall_EndBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERLASTCALL_BES, MCUSTOMERLASTCALL_ANZ );
#else
        {
            void * pUnused = MCUSTOMERLASTCALL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERLASTCALL_SELCUSTOMERCALLSTATE: {
        mcustomerlastcallS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERLASTCALL_BES, MCUSTOMERLASTCALL_ANZ);
#else
        d = (mcustomerlastcallS *)spBuf;
#endif

        if ( (rc = Mcustomerlastcall_SelCustomerCallState(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERLASTCALL_BES, MCUSTOMERLASTCALL_ANZ );
#else
        {
            void * pUnused = MCUSTOMERLASTCALL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERLASTCALL_STARTBROWSE: {
        mcustomerlastcallS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERLASTCALL_BES, MCUSTOMERLASTCALL_ANZ);
#else
        d = (mcustomerlastcallS *)spBuf;
#endif

        if ( (rc = Mcustomerlastcall_StartBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERLASTCALL_BES, MCUSTOMERLASTCALL_ANZ );
#else
        {
            void * pUnused = MCUSTOMERLASTCALL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERORDER_ENDBROWSE: {
        mcustomerorderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ);
#else
        d = (mcustomerorderS *)spBuf;
#endif

        if ( (rc = Mcustomerorder_EndBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERORDER_SELAVAILABLEORDER: {
        mcustomerorderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ);
#else
        d = (mcustomerorderS *)spBuf;
#endif

        if ( (rc = Mcustomerorder_SelAvailableOrder(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERORDER_SELCUSTOMERCALLED: {
        mcustomerorderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ);
#else
        d = (mcustomerorderS *)spBuf;
#endif

        if ( (rc = Mcustomerorder_SelCustomerCalled(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERORDER_SELDEVICEORDER: {
        mcustomerorderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ);
#else
        d = (mcustomerorderS *)spBuf;
#endif

        if ( (rc = Mcustomerorder_SelDeviceOrder(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERORDER_STARTBROWSE: {
        mcustomerorderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ);
#else
        d = (mcustomerorderS *)spBuf;
#endif

        if ( (rc = Mcustomerorder_StartBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ );
#else
        {
            void * pUnused = MCUSTOMERORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANCHECK_SELDEVICEID: {
        mdeviceplancheckS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ);
#else
        d = (mdeviceplancheckS *)spBuf;
#endif

        if ( (rc = Mdeviceplancheck_SelDeviceID(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANCHECK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANCHECK_SELLIST: {
        mdeviceplancheckS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ);
#else
        d = (mdeviceplancheckS *)spBuf;
#endif

        if ( (rc = Mdeviceplancheck_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANCHECK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANCHECK_SELLISTHIST: {
        mdeviceplancheckS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ);
#else
        d = (mdeviceplancheckS *)spBuf;
#endif

        if ( (rc = Mdeviceplancheck_SelListHist(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANCHECK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANCHECK_UPDUMKDECIVEPLAN: {
        mdeviceplancheckS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ);
#else
        d = (mdeviceplancheckS *)spBuf;
#endif

        if ( (rc = Mdeviceplancheck_UpdUMKDecivePlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANCHECK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANCHECK_UPDATEDIRECT: {
        mdeviceplancheckS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ);
#else
        d = (mdeviceplancheckS *)spBuf;
#endif

        if ( (rc = Mdeviceplancheck_UpdateDirect(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANCHECK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANDRIVER_ENDBROWSE: {
        mdeviceplandriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
#else
        d = (mdeviceplandriverS *)spBuf;
#endif

        if ( (rc = Mdeviceplandriver_EndBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANDRIVER_SELLIST: {
        mdeviceplandriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
#else
        d = (mdeviceplandriverS *)spBuf;
#endif

        if ( (rc = Mdeviceplandriver_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANDRIVER_SELWITHSEQUENZNO: {
        mdeviceplandriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
#else
        d = (mdeviceplandriverS *)spBuf;
#endif

        if ( (rc = Mdeviceplandriver_SelWithSequenzNo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANDRIVER_STARTBROWSE: {
        mdeviceplandriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
#else
        d = (mdeviceplandriverS *)spBuf;
#endif

        if ( (rc = Mdeviceplandriver_StartBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANDRIVER_UPDDEVICEPLAN: {
        mdeviceplandriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
#else
        d = (mdeviceplandriverS *)spBuf;
#endif

        if ( (rc = Mdeviceplandriver_UpdDevicePlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANDRIVER_UPDUMKDEVICEPLAN: {
        mdeviceplandriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
#else
        d = (mdeviceplandriverS *)spBuf;
#endif

        if ( (rc = Mdeviceplandriver_UpdUMKDevicePlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANDRIVER_UPDWITHOUTTRANSACTION: {
        mdeviceplandriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
#else
        d = (mdeviceplandriverS *)spBuf;
#endif

        if ( (rc = Mdeviceplandriver_UpdWithoutTransaction(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANDRIVER_UPDWITHOUTTRANSACTIONDIRECT: {
        mdeviceplandriverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
#else
        d = (mdeviceplandriverS *)spBuf;
#endif

        if ( (rc = Mdeviceplandriver_UpdWithoutTransactionDirect(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANDRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MNUMBER_SELNUMBER: {
        mnumberS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MNUMBER_BES, MNUMBER_ANZ);
#else
        d = (mnumberS *)spBuf;
#endif

        if ( (rc = Mnumber_SelNumber(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MNUMBER_BES, MNUMBER_ANZ );
#else
        {
            void * pUnused = MNUMBER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MNUMBER_INSERT: {
        mnumberS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MNUMBER_BES, MNUMBER_ANZ);
#else
        d = (mnumberS *)spBuf;
#endif

        if ( (rc = Mnumber_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MNUMBER_BES, MNUMBER_ANZ );
#else
        {
            void * pUnused = MNUMBER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MNUMBER_UPDNUMBER: {
        mnumberS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MNUMBER_BES, MNUMBER_ANZ);
#else
        d = (mnumberS *)spBuf;
#endif

        if ( (rc = Mnumber_UpdNumber(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MNUMBER_BES, MNUMBER_ANZ );
#else
        {
            void * pUnused = MNUMBER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MNUMBER_INCREMENT: {
        mnumberS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MNUMBER_BES, MNUMBER_ANZ);
#else
        d = (mnumberS *)spBuf;
#endif

        if ( (rc = Mnumber_Increment(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MNUMBER_BES, MNUMBER_ANZ );
#else
        {
            void * pUnused = MNUMBER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MTRANSAKTION_BEGINTRANSACTION: {
        mtransaktionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
#else
        d = (mtransaktionS *)spBuf;
#endif

        if ( (rc = Mtransaktion_BeginTransaction(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MTRANSAKTION_BES, MTRANSAKTION_ANZ );
#else
        {
            void * pUnused = MTRANSAKTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MTRANSAKTION_ENDTRANSACTION: {
        mtransaktionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
#else
        d = (mtransaktionS *)spBuf;
#endif

        if ( (rc = Mtransaktion_EndTransaction(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MTRANSAKTION_BES, MTRANSAKTION_ANZ );
#else
        {
            void * pUnused = MTRANSAKTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MTRANSAKTION_GETDATE: {
        mtransaktionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
#else
        d = (mtransaktionS *)spBuf;
#endif

        if ( (rc = Mtransaktion_GetDate(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MTRANSAKTION_BES, MTRANSAKTION_ANZ );
#else
        {
            void * pUnused = MTRANSAKTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MTRANSAKTION_GETDATETIME: {
        mtransaktionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
#else
        d = (mtransaktionS *)spBuf;
#endif

        if ( (rc = Mtransaktion_GetDateTime(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MTRANSAKTION_BES, MTRANSAKTION_ANZ );
#else
        {
            void * pUnused = MTRANSAKTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MTRANSAKTION_GETTIME: {
        mtransaktionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
#else
        d = (mtransaktionS *)spBuf;
#endif

        if ( (rc = Mtransaktion_GetTime(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MTRANSAKTION_BES, MTRANSAKTION_ANZ );
#else
        {
            void * pUnused = MTRANSAKTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MTRANSAKTION_ROLLBACKTRANSACTION: {
        mtransaktionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
#else
        d = (mtransaktionS *)spBuf;
#endif

        if ( (rc = Mtransaktion_RollbackTransaction(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MTRANSAKTION_BES, MTRANSAKTION_ANZ );
#else
        {
            void * pUnused = MTRANSAKTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MTRANSAKTION_SETCOMMITEDREAD: {
        mtransaktionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
#else
        d = (mtransaktionS *)spBuf;
#endif

        if ( (rc = Mtransaktion_SetCommitedRead(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MTRANSAKTION_BES, MTRANSAKTION_ANZ );
#else
        {
            void * pUnused = MTRANSAKTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MTRANSAKTION_SETDIRTYREAD: {
        mtransaktionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
#else
        d = (mtransaktionS *)spBuf;
#endif

        if ( (rc = Mtransaktion_SetDirtyRead(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MTRANSAKTION_BES, MTRANSAKTION_ANZ );
#else
        {
            void * pUnused = MTRANSAKTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMATER_SELCALLPARAMETER: {
        mcallparamaterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ);
#else
        d = (mcallparamaterS *)spBuf;
#endif

        if ( (rc = Mcallparamater_SelCallParameter(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ );
#else
        {
            void * pUnused = MCALLPARAMATER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMATER_SELLIST: {
        mcallparamaterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ);
#else
        d = (mcallparamaterS *)spBuf;
#endif

        if ( (rc = Mcallparamater_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ );
#else
        {
            void * pUnused = MCALLPARAMATER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMATER_INSERT: {
        mcallparamaterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ);
#else
        d = (mcallparamaterS *)spBuf;
#endif

        if ( (rc = Mcallparamater_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ );
#else
        {
            void * pUnused = MCALLPARAMATER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMATER_UPDCALLPARAMETER: {
        mcallparamaterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ);
#else
        d = (mcallparamaterS *)spBuf;
#endif

        if ( (rc = Mcallparamater_UpdCallparameter(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ );
#else
        {
            void * pUnused = MCALLPARAMATER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMATER_DELCALLPARAMETER: {
        mcallparamaterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ);
#else
        d = (mcallparamaterS *)spBuf;
#endif

        if ( (rc = Mcallparamater_DelCallParameter(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ );
#else
        {
            void * pUnused = MCALLPARAMATER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMTERTIMES_SELPARAMETER: {
        mcallparamtertimesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMTERTIMES_BES, MCALLPARAMTERTIMES_ANZ);
#else
        d = (mcallparamtertimesS *)spBuf;
#endif

        if ( (rc = Mcallparamtertimes_SelParameter(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMTERTIMES_BES, MCALLPARAMTERTIMES_ANZ );
#else
        {
            void * pUnused = MCALLPARAMTERTIMES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMTERTIMES_INSERT: {
        mcallparamtertimesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMTERTIMES_BES, MCALLPARAMTERTIMES_ANZ);
#else
        d = (mcallparamtertimesS *)spBuf;
#endif

        if ( (rc = Mcallparamtertimes_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMTERTIMES_BES, MCALLPARAMTERTIMES_ANZ );
#else
        {
            void * pUnused = MCALLPARAMTERTIMES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPARAMTERTIMES_UPDPARAMETER: {
        mcallparamtertimesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPARAMTERTIMES_BES, MCALLPARAMTERTIMES_ANZ);
#else
        d = (mcallparamtertimesS *)spBuf;
#endif

        if ( (rc = Mcallparamtertimes_UpdParameter(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPARAMTERTIMES_BES, MCALLPARAMTERTIMES_ANZ );
#else
        {
            void * pUnused = MCALLPARAMTERTIMES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANLOAD_SELCALLPLANLOAD: {
        mcallplanloadS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
#else
        d = (mcallplanloadS *)spBuf;
#endif

        if ( (rc = Mcallplanload_SelCallPlanLoad(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ );
#else
        {
            void * pUnused = MCALLPLANLOAD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANLOAD_SELLIST: {
        mcallplanloadS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
#else
        d = (mcallplanloadS *)spBuf;
#endif

        if ( (rc = Mcallplanload_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ );
#else
        {
            void * pUnused = MCALLPLANLOAD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANLOAD_INSERT: {
        mcallplanloadS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
#else
        d = (mcallplanloadS *)spBuf;
#endif

        if ( (rc = Mcallplanload_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ );
#else
        {
            void * pUnused = MCALLPLANLOAD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANLOAD_UPDCALLPLANLOAD: {
        mcallplanloadS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
#else
        d = (mcallplanloadS *)spBuf;
#endif

        if ( (rc = Mcallplanload_UpdCallPlanLoad(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ );
#else
        {
            void * pUnused = MCALLPLANLOAD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANLOAD_DELCALLPLANLOAD: {
        mcallplanloadS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
#else
        d = (mcallplanloadS *)spBuf;
#endif

        if ( (rc = Mcallplanload_DelCallPlanLoad(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ );
#else
        {
            void * pUnused = MCALLPLANLOAD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANLOAD_DELCALLPLANLOADOLDER: {
        mcallplanloadS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
#else
        d = (mcallplanloadS *)spBuf;
#endif

        if ( (rc = Mcallplanload_DelCallPlanLoadOlder(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ );
#else
        {
            void * pUnused = MCALLPLANLOAD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANLOAD_AINCLUDEDUMMY: {
        mcallplanloadS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
#else
        d = (mcallplanloadS *)spBuf;
#endif

        if ( (rc = Mcallplanload_AIncludeDummy(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ );
#else
        {
            void * pUnused = MCALLPLANLOAD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANLOAD_GETINITIALIZEDATA: {
        mcallplanloadS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
#else
        d = (mcallplanloadS *)spBuf;
#endif

        if ( (rc = Mcallplanload_GetInitializeData(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ );
#else
        {
            void * pUnused = MCALLPLANLOAD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_SELALLDISABLED: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_SelAllDisabled(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_SELLIST: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_SELLISTHIST: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_SelListHist(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_INSERT: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_UPDALLCUSTOMERCALLPLAN: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_UpdAllCustomerCallPlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_UPDALLWITHOUTSATURDAY: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_UpdAllWithoutSaturday(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_UPDCUSTOMERCALLPLAN: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_UpdCustomerCallPlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_DELALLCUSTOMERCALLPLAN: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_DelAllCustomerCallPlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_DELALLWITHOUTSATURDAY: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_DelAllWithoutSaturday(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_DELCALLPLANCOMPLETLY: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_DelCallPlanCompletly(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_DELCUSTOMERCALLPLAN: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_DelCustomerCallPlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_INSERTALL: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_InsertAll(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_INSERTALLWITHOUTSATURDAY: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_InsertAllWithoutSaturday(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_SELLISTUNDERTAKE: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_SelListUndertake(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_STARTBROWSEUNDERTAKE: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_StartBrowseUndertake(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_UPDCALLPLANDISABLE: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_UpdCallPlanDisable(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_UPDCALLPLANENABLE: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_UpdCallPlanEnable(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_UPDTIMEALLCUSTOMERCALLPLAN: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_UpdTimeAllCustomerCallPlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_UPDTIMEALLWITHOUTSATURDAY: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_UpdTimeAllWithoutSaturday(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLAN_UPDTIMECUSTOMERCALLPLAN: {
        mcustomercallplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
#else
        d = (mcustomercallplanS *)spBuf;
#endif

        if ( (rc = Mcustomercallplan_UpdTimeCustomerCallPlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANPHONPROT_INSERT: {
        mcustomercallplanphonprotS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANPHONPROT_BES, MCUSTOMERCALLPLANPHONPROT_ANZ);
#else
        d = (mcustomercallplanphonprotS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanphonprot_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANPHONPROT_BES, MCUSTOMERCALLPLANPHONPROT_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANPHONPROT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANPHONPROT_DELALL: {
        mcustomercallplanphonprotS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANPHONPROT_BES, MCUSTOMERCALLPLANPHONPROT_ANZ);
#else
        d = (mcustomercallplanphonprotS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanphonprot_DelAll(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANPHONPROT_BES, MCUSTOMERCALLPLANPHONPROT_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANPHONPROT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANPHONPROT_DELALLOLDER: {
        mcustomercallplanphonprotS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANPHONPROT_BES, MCUSTOMERCALLPLANPHONPROT_ANZ);
#else
        d = (mcustomercallplanphonprotS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanphonprot_DelAllOlder(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANPHONPROT_BES, MCUSTOMERCALLPLANPHONPROT_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANPHONPROT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANTOUR_SELLIST: {
        mcustomercallplantourS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANTOUR_BES, MCUSTOMERCALLPLANTOUR_ANZ);
#else
        d = (mcustomercallplantourS *)spBuf;
#endif

        if ( (rc = Mcustomercallplantour_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANTOUR_BES, MCUSTOMERCALLPLANTOUR_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANTOUR_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANTOUR_SELLISTHIST: {
        mcustomercallplantourS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANTOUR_BES, MCUSTOMERCALLPLANTOUR_ANZ);
#else
        d = (mcustomercallplantourS *)spBuf;
#endif

        if ( (rc = Mcustomercallplantour_SelListHist(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANTOUR_BES, MCUSTOMERCALLPLANTOUR_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANTOUR_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANPHON_INSERT: {
        mcustomercallplanphonS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANPHON_BES, MCUSTOMERCALLPLANPHON_ANZ);
#else
        d = (mcustomercallplanphonS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanphon_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANPHON_BES, MCUSTOMERCALLPLANPHON_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANPHON_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANPHON_DELALL: {
        mcustomercallplanphonS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANPHON_BES, MCUSTOMERCALLPLANPHON_ANZ);
#else
        d = (mcustomercallplanphonS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanphon_DelAll(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANPHON_BES, MCUSTOMERCALLPLANPHON_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANPHON_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERCALLPLANPHON_DELALLOLDER: {
        mcustomercallplanphonS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERCALLPLANPHON_BES, MCUSTOMERCALLPLANPHON_ANZ);
#else
        d = (mcustomercallplanphonS *)spBuf;
#endif

        if ( (rc = Mcustomercallplanphon_DelAllOlder(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERCALLPLANPHON_BES, MCUSTOMERCALLPLANPHON_ANZ );
#else
        {
            void * pUnused = MCUSTOMERCALLPLANPHON_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERDISPLAY_SELCUSTOMER: {
        mcustomerdisplayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERDISPLAY_BES, MCUSTOMERDISPLAY_ANZ);
#else
        d = (mcustomerdisplayS *)spBuf;
#endif

        if ( (rc = Mcustomerdisplay_SelCustomer(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERDISPLAY_BES, MCUSTOMERDISPLAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERDISPLAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERDISPLAY_UPDTELNO: {
        mcustomerdisplayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERDISPLAY_BES, MCUSTOMERDISPLAY_ANZ);
#else
        d = (mcustomerdisplayS *)spBuf;
#endif

        if ( (rc = Mcustomerdisplay_UpdTelNo(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERDISPLAY_BES, MCUSTOMERDISPLAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERDISPLAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERDISPLAY_UPDPROPERTIES: {
        mcustomerdisplayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERDISPLAY_BES, MCUSTOMERDISPLAY_ANZ);
#else
        d = (mcustomerdisplayS *)spBuf;
#endif

        if ( (rc = Mcustomerdisplay_UpdProperties(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERDISPLAY_BES, MCUSTOMERDISPLAY_ANZ );
#else
        {
            void * pUnused = MCUSTOMERDISPLAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANMAINTENANCE_SELDEVICEPLANUNI: {
        mdeviceplanmaintenanceS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ);
#else
        d = (mdeviceplanmaintenanceS *)spBuf;
#endif

        if ( (rc = Mdeviceplanmaintenance_SelDevicePlanUni(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANMAINTENANCE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANMAINTENANCE_SELLIST: {
        mdeviceplanmaintenanceS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ);
#else
        d = (mdeviceplanmaintenanceS *)spBuf;
#endif

        if ( (rc = Mdeviceplanmaintenance_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANMAINTENANCE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANMAINTENANCE_SELNST: {
        mdeviceplanmaintenanceS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ);
#else
        d = (mdeviceplanmaintenanceS *)spBuf;
#endif

        if ( (rc = Mdeviceplanmaintenance_SelNst(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANMAINTENANCE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANMAINTENANCE_UPDDEVICEPLAN: {
        mdeviceplanmaintenanceS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ);
#else
        d = (mdeviceplanmaintenanceS *)spBuf;
#endif

        if ( (rc = Mdeviceplanmaintenance_UpdDevicePlan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANMAINTENANCE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANMAINTENANCE_UPDSALECENTERNO: {
        mdeviceplanmaintenanceS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ);
#else
        d = (mdeviceplanmaintenanceS *)spBuf;
#endif

        if ( (rc = Mdeviceplanmaintenance_UpdSaleCenterNo(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANMAINTENANCE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANMAINTENANCE_DELETE: {
        mdeviceplanmaintenanceS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ);
#else
        d = (mdeviceplanmaintenanceS *)spBuf;
#endif

        if ( (rc = Mdeviceplanmaintenance_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANMAINTENANCE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MDEVICEPLANMAINTENANCE_INSERTDEVICE: {
        mdeviceplanmaintenanceS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ);
#else
        d = (mdeviceplanmaintenanceS *)spBuf;
#endif

        if ( (rc = Mdeviceplanmaintenance_InsertDevice(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ );
#else
        {
            void * pUnused = MDEVICEPLANMAINTENANCE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MREGION_SELLIST: {
        mregionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MREGION_BES, MREGION_ANZ);
#else
        d = (mregionS *)spBuf;
#endif

        if ( (rc = Mregion_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MREGION_BES, MREGION_ANZ );
#else
        {
            void * pUnused = MREGION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MREGION_SELREGION: {
        mregionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MREGION_BES, MREGION_ANZ);
#else
        d = (mregionS *)spBuf;
#endif

        if ( (rc = Mregion_SelRegion(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MREGION_BES, MREGION_ANZ );
#else
        {
            void * pUnused = MREGION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MREGION_INSERT: {
        mregionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MREGION_BES, MREGION_ANZ);
#else
        d = (mregionS *)spBuf;
#endif

        if ( (rc = Mregion_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MREGION_BES, MREGION_ANZ );
#else
        {
            void * pUnused = MREGION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MREGION_DELREGION: {
        mregionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MREGION_BES, MREGION_ANZ);
#else
        d = (mregionS *)spBuf;
#endif

        if ( (rc = Mregion_DelRegion(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MREGION_BES, MREGION_ANZ );
#else
        {
            void * pUnused = MREGION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MSALECENTER_SELLIST: {
        msalecenterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MSALECENTER_BES, MSALECENTER_ANZ);
#else
        d = (msalecenterS *)spBuf;
#endif

        if ( (rc = Msalecenter_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MSALECENTER_BES, MSALECENTER_ANZ );
#else
        {
            void * pUnused = MSALECENTER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MSALECENTER_SELSALECENTER: {
        msalecenterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MSALECENTER_BES, MSALECENTER_ANZ);
#else
        d = (msalecenterS *)spBuf;
#endif

        if ( (rc = Msalecenter_SelSaleCenter(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MSALECENTER_BES, MSALECENTER_ANZ );
#else
        {
            void * pUnused = MSALECENTER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKCONNECTION_SELLIST: {
        mumkconnectionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ);
#else
        d = (mumkconnectionS *)spBuf;
#endif

        if ( (rc = Mumkconnection_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ );
#else
        {
            void * pUnused = MUMKCONNECTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKCONNECTION_SELUMKCONNECTION: {
        mumkconnectionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ);
#else
        d = (mumkconnectionS *)spBuf;
#endif

        if ( (rc = Mumkconnection_SelUmkConnection(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ );
#else
        {
            void * pUnused = MUMKCONNECTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKCONNECTION_INSERT: {
        mumkconnectionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ);
#else
        d = (mumkconnectionS *)spBuf;
#endif

        if ( (rc = Mumkconnection_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ );
#else
        {
            void * pUnused = MUMKCONNECTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKCONNECTION_UPDUMKCONNECTION: {
        mumkconnectionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ);
#else
        d = (mumkconnectionS *)spBuf;
#endif

        if ( (rc = Mumkconnection_UpdUmkConnection(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ );
#else
        {
            void * pUnused = MUMKCONNECTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKCONNECTION_DELUMKCONNECTION: {
        mumkconnectionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ);
#else
        d = (mumkconnectionS *)spBuf;
#endif

        if ( (rc = Mumkconnection_DelUmkConnection(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ );
#else
        {
            void * pUnused = MUMKCONNECTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKCONNECTION_WRITELOG: {
        mumkconnectionS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ);
#else
        d = (mumkconnectionS *)spBuf;
#endif

        if ( (rc = Mumkconnection_WriteLog(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ );
#else
        {
            void * pUnused = MUMKCONNECTION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_SELCOUNTAVAILABLE: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_SelCountAvailable(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_SELCOUNTAVAILABLEPHON: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_SelCountAvailablePhon(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_INSERT: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_DELALL: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_DelAll(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_DELALLOLDER: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_DelAllOlder(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_AINCLUDEDUMMY: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_AIncludeDummy(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_CHECKAVAILABLEENTRIES: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_CheckAvailableEntries(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_CHECKAVAILABLEENTRIESPHON: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_CheckAvailableEntriesPhon(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_DELALLPHON: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_DelAllPhon(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_DELALLPHONOLDER: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_DelAllPhonOlder(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_DELCALLPLANLOADOLDER: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_DelCallPlanLoadOlder(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_DELEVENTS: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_DelEvents(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_DELEVENTSOLDER: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_DelEventsOlder(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_DELEVENTSPHON: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_DelEventsPhon(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_DELEVENTSPHONOLDER: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_DelEventsPhonOlder(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_UNDERTAKECALLPLAN: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_UndertakeCallplan(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCALLPLANUNDERTAKE_UNDERTAKECALLPLANPHON: {
        mcallplanundertakeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ);
#else
        d = (mcallplanundertakeS *)spBuf;
#endif

        if ( (rc = Mcallplanundertake_UndertakeCallplanPhon(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCALLPLANUNDERTAKE_BES, MCALLPLANUNDERTAKE_ANZ );
#else
        {
            void * pUnused = MCALLPLANUNDERTAKE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MHOLIDAY_SELCOUNT: {
        mholidayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MHOLIDAY_BES, MHOLIDAY_ANZ);
#else
        d = (mholidayS *)spBuf;
#endif

        if ( (rc = Mholiday_SelCount(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MHOLIDAY_BES, MHOLIDAY_ANZ );
#else
        {
            void * pUnused = MHOLIDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MHOLIDAY_SELHOLIDAY: {
        mholidayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MHOLIDAY_BES, MHOLIDAY_ANZ);
#else
        d = (mholidayS *)spBuf;
#endif

        if ( (rc = Mholiday_SelHoliday(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MHOLIDAY_BES, MHOLIDAY_ANZ );
#else
        {
            void * pUnused = MHOLIDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MHOLIDAY_ENDBROWSE: {
        mholidayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MHOLIDAY_BES, MHOLIDAY_ANZ);
#else
        d = (mholidayS *)spBuf;
#endif

        if ( (rc = Mholiday_EndBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MHOLIDAY_BES, MHOLIDAY_ANZ );
#else
        {
            void * pUnused = MHOLIDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MHOLIDAY_ISHOLIDAY: {
        mholidayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MHOLIDAY_BES, MHOLIDAY_ANZ);
#else
        d = (mholidayS *)spBuf;
#endif

        if ( (rc = Mholiday_IsHoliday(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MHOLIDAY_BES, MHOLIDAY_ANZ );
#else
        {
            void * pUnused = MHOLIDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MHOLIDAY_STARTBROWSE: {
        mholidayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MHOLIDAY_BES, MHOLIDAY_ANZ);
#else
        d = (mholidayS *)spBuf;
#endif

        if ( (rc = Mholiday_StartBrowse(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MHOLIDAY_BES, MHOLIDAY_ANZ );
#else
        {
            void * pUnused = MHOLIDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MHOLIDAY_INLINE_GETBUFFER: {
        mholidayS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MHOLIDAY_BES, MHOLIDAY_ANZ);
#else
        d = (mholidayS *)spBuf;
#endif

        if ( (rc = Mholiday_inline_GetBuffer(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MHOLIDAY_BES, MHOLIDAY_ANZ );
#else
        {
            void * pUnused = MHOLIDAY_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case COLLORDERGRP_SELLIST: {
        collordergrpS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, COLLORDERGRP_BES, COLLORDERGRP_ANZ);
#else
        d = (collordergrpS *)spBuf;
#endif

        if ( (rc = Collordergrp_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, COLLORDERGRP_BES, COLLORDERGRP_ANZ );
#else
        {
            void * pUnused = COLLORDERGRP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case COLLORDERGRP_INSERT: {
        collordergrpS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, COLLORDERGRP_BES, COLLORDERGRP_ANZ);
#else
        d = (collordergrpS *)spBuf;
#endif

        if ( (rc = Collordergrp_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, COLLORDERGRP_BES, COLLORDERGRP_ANZ );
#else
        {
            void * pUnused = COLLORDERGRP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case COLLORDERGRP_UPDATE: {
        collordergrpS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, COLLORDERGRP_BES, COLLORDERGRP_ANZ);
#else
        d = (collordergrpS *)spBuf;
#endif

        if ( (rc = Collordergrp_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, COLLORDERGRP_BES, COLLORDERGRP_ANZ );
#else
        {
            void * pUnused = COLLORDERGRP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case COLLORDERGRP_DELETE: {
        collordergrpS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, COLLORDERGRP_BES, COLLORDERGRP_ANZ);
#else
        d = (collordergrpS *)spBuf;
#endif

        if ( (rc = Collordergrp_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, COLLORDERGRP_BES, COLLORDERGRP_ANZ );
#else
        {
            void * pUnused = COLLORDERGRP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case COLLORDERGRPMEM_SELLIST: {
        collordergrpmemS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, COLLORDERGRPMEM_BES, COLLORDERGRPMEM_ANZ);
#else
        d = (collordergrpmemS *)spBuf;
#endif

        if ( (rc = Collordergrpmem_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, COLLORDERGRPMEM_BES, COLLORDERGRPMEM_ANZ );
#else
        {
            void * pUnused = COLLORDERGRPMEM_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case COLLORDERGRPMEM_INSERT: {
        collordergrpmemS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, COLLORDERGRPMEM_BES, COLLORDERGRPMEM_ANZ);
#else
        d = (collordergrpmemS *)spBuf;
#endif

        if ( (rc = Collordergrpmem_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, COLLORDERGRPMEM_BES, COLLORDERGRPMEM_ANZ );
#else
        {
            void * pUnused = COLLORDERGRPMEM_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case COLLORDERGRPMEM_DELETE: {
        collordergrpmemS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, COLLORDERGRPMEM_BES, COLLORDERGRPMEM_ANZ);
#else
        d = (collordergrpmemS *)spBuf;
#endif

        if ( (rc = Collordergrpmem_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, COLLORDERGRPMEM_BES, COLLORDERGRPMEM_ANZ );
#else
        {
            void * pUnused = COLLORDERGRPMEM_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKDISTRESS_ISINWORK: {
        checkdistressS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKDISTRESS_BES, CHECKDISTRESS_ANZ);
#else
        d = (checkdistressS *)spBuf;
#endif

        if ( (rc = Checkdistress_IsInWork(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKDISTRESS_BES, CHECKDISTRESS_ANZ );
#else
        {
            void * pUnused = CHECKDISTRESS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTSEPORDER_SELLIST: {
        cstseporderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTSEPORDER_BES, CSTSEPORDER_ANZ);
#else
        d = (cstseporderS *)spBuf;
#endif

        if ( (rc = Cstseporder_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTSEPORDER_BES, CSTSEPORDER_ANZ );
#else
        {
            void * pUnused = CSTSEPORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTSEPORDER_INSERT: {
        cstseporderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTSEPORDER_BES, CSTSEPORDER_ANZ);
#else
        d = (cstseporderS *)spBuf;
#endif

        if ( (rc = Cstseporder_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTSEPORDER_BES, CSTSEPORDER_ANZ );
#else
        {
            void * pUnused = CSTSEPORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTSEPORDER_UPDATE: {
        cstseporderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTSEPORDER_BES, CSTSEPORDER_ANZ);
#else
        d = (cstseporderS *)spBuf;
#endif

        if ( (rc = Cstseporder_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTSEPORDER_BES, CSTSEPORDER_ANZ );
#else
        {
            void * pUnused = CSTSEPORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTSEPORDER_DELETE: {
        cstseporderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTSEPORDER_BES, CSTSEPORDER_ANZ);
#else
        d = (cstseporderS *)spBuf;
#endif

        if ( (rc = Cstseporder_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTSEPORDER_BES, CSTSEPORDER_ANZ );
#else
        {
            void * pUnused = CSTSEPORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DEALERUMSATZ_SELLIST: {
        dealerumsatzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DEALERUMSATZ_BES, DEALERUMSATZ_ANZ);
#else
        d = (dealerumsatzS *)spBuf;
#endif

        if ( (rc = Dealerumsatz_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DEALERUMSATZ_BES, DEALERUMSATZ_ANZ );
#else
        {
            void * pUnused = DEALERUMSATZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FORBIDDENWORDS_SELWORDLIST: {
        forbiddenwordsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ);
#else
        d = (forbiddenwordsS *)spBuf;
#endif

        if ( (rc = Forbiddenwords_SelWordList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ );
#else
        {
            void * pUnused = FORBIDDENWORDS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FORBIDDENWORDS_SELWORDS: {
        forbiddenwordsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ);
#else
        d = (forbiddenwordsS *)spBuf;
#endif

        if ( (rc = Forbiddenwords_SelWords(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ );
#else
        {
            void * pUnused = FORBIDDENWORDS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FORBIDDENWORDS_INSERT: {
        forbiddenwordsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ);
#else
        d = (forbiddenwordsS *)spBuf;
#endif

        if ( (rc = Forbiddenwords_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ );
#else
        {
            void * pUnused = FORBIDDENWORDS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FORBIDDENWORDS_UPDATEWORD: {
        forbiddenwordsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ);
#else
        d = (forbiddenwordsS *)spBuf;
#endif

        if ( (rc = Forbiddenwords_UpdateWord(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ );
#else
        {
            void * pUnused = FORBIDDENWORDS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FORBIDDENWORDS_DELETEWORD: {
        forbiddenwordsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ);
#else
        d = (forbiddenwordsS *)spBuf;
#endif

        if ( (rc = Forbiddenwords_DeleteWord(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FORBIDDENWORDS_BES, FORBIDDENWORDS_ANZ );
#else
        {
            void * pUnused = FORBIDDENWORDS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case INVOICENUMBER_GETNUMBER: {
        invoicenumberS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, INVOICENUMBER_BES, INVOICENUMBER_ANZ);
#else
        d = (invoicenumberS *)spBuf;
#endif

        if ( (rc = Invoicenumber_GetNumber(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, INVOICENUMBER_BES, INVOICENUMBER_ANZ );
#else
        {
            void * pUnused = INVOICENUMBER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case INVOICENUMBEROLD_GETNUMBER: {
        invoicenumberoldS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, INVOICENUMBEROLD_BES, INVOICENUMBEROLD_ANZ);
#else
        d = (invoicenumberoldS *)spBuf;
#endif

        if ( (rc = Invoicenumberold_GetNumber(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, INVOICENUMBEROLD_BES, INVOICENUMBEROLD_ANZ );
#else
        {
            void * pUnused = INVOICENUMBEROLD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PARAMETER_SELPARAMETER: {
        parameterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PARAMETER_BES, PARAMETER_ANZ);
#else
        d = (parameterS *)spBuf;
#endif

        if ( (rc = Parameter_SelParameter(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PARAMETER_BES, PARAMETER_ANZ );
#else
        {
            void * pUnused = PARAMETER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PARAMETER_SELZWECK: {
        parameterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PARAMETER_BES, PARAMETER_ANZ);
#else
        d = (parameterS *)spBuf;
#endif

        if ( (rc = Parameter_SelZweck(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PARAMETER_BES, PARAMETER_ANZ );
#else
        {
            void * pUnused = PARAMETER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SEPORDER_SEL: {
        seporderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SEPORDER_BES, SEPORDER_ANZ);
#else
        d = (seporderS *)spBuf;
#endif

        if ( (rc = Seporder_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SEPORDER_BES, SEPORDER_ANZ );
#else
        {
            void * pUnused = SEPORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SEPORDER_INSERT: {
        seporderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SEPORDER_BES, SEPORDER_ANZ);
#else
        d = (seporderS *)spBuf;
#endif

        if ( (rc = Seporder_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SEPORDER_BES, SEPORDER_ANZ );
#else
        {
            void * pUnused = SEPORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SEPORDER_UPDATE: {
        seporderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SEPORDER_BES, SEPORDER_ANZ);
#else
        d = (seporderS *)spBuf;
#endif

        if ( (rc = Seporder_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SEPORDER_BES, SEPORDER_ANZ );
#else
        {
            void * pUnused = SEPORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SEPORDER_DELETE: {
        seporderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SEPORDER_BES, SEPORDER_ANZ);
#else
        d = (seporderS *)spBuf;
#endif

        if ( (rc = Seporder_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SEPORDER_BES, SEPORDER_ANZ );
#else
        {
            void * pUnused = SEPORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SEPORDERGRP_SEL: {
        sepordergrpS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SEPORDERGRP_BES, SEPORDERGRP_ANZ);
#else
        d = (sepordergrpS *)spBuf;
#endif

        if ( (rc = Sepordergrp_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SEPORDERGRP_BES, SEPORDERGRP_ANZ );
#else
        {
            void * pUnused = SEPORDERGRP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SEPORDERGRP_INSERT: {
        sepordergrpS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SEPORDERGRP_BES, SEPORDERGRP_ANZ);
#else
        d = (sepordergrpS *)spBuf;
#endif

        if ( (rc = Sepordergrp_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SEPORDERGRP_BES, SEPORDERGRP_ANZ );
#else
        {
            void * pUnused = SEPORDERGRP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SEPORDERGRP_UPDATE: {
        sepordergrpS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SEPORDERGRP_BES, SEPORDERGRP_ANZ);
#else
        d = (sepordergrpS *)spBuf;
#endif

        if ( (rc = Sepordergrp_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SEPORDERGRP_BES, SEPORDERGRP_ANZ );
#else
        {
            void * pUnused = SEPORDERGRP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SEPORDERGRP_DELETE: {
        sepordergrpS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SEPORDERGRP_BES, SEPORDERGRP_ANZ);
#else
        d = (sepordergrpS *)spBuf;
#endif

        if ( (rc = Sepordergrp_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SEPORDERGRP_BES, SEPORDERGRP_ANZ );
#else
        {
            void * pUnused = SEPORDERGRP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TASKCONTROL_CHECKTIMES: {
        taskcontrolS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TASKCONTROL_BES, TASKCONTROL_ANZ);
#else
        d = (taskcontrolS *)spBuf;
#endif

        if ( (rc = Taskcontrol_CheckTimes(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TASKCONTROL_BES, TASKCONTROL_ANZ );
#else
        {
            void * pUnused = TASKCONTROL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TAXES_SELLIST: {
        taxesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TAXES_BES, TAXES_ANZ);
#else
        d = (taxesS *)spBuf;
#endif

        if ( (rc = Taxes_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TAXES_BES, TAXES_ANZ );
#else
        {
            void * pUnused = TAXES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTOMERORDERCHECK_SELLIST: {
        customerordercheckS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTOMERORDERCHECK_BES, CUSTOMERORDERCHECK_ANZ);
#else
        d = (customerordercheckS *)spBuf;
#endif

        if ( (rc = customerordercheck_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTOMERORDERCHECK_BES, CUSTOMERORDERCHECK_ANZ );
#else
        {
            void * pUnused = CUSTOMERORDERCHECK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case LGTEXT_SEL: {
        lgtextS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, LGTEXT_BES, LGTEXT_ANZ);
#else
        d = (lgtextS *)spBuf;
#endif

        if ( (rc = lgtext_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, LGTEXT_BES, LGTEXT_ANZ );
#else
        {
            void * pUnused = LGTEXT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case LGTEXT_SETLANGUAGE: {
        lgtextS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, LGTEXT_BES, LGTEXT_ANZ);
#else
        d = (lgtextS *)spBuf;
#endif

        if ( (rc = lgtext_SetLanguage(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, LGTEXT_BES, LGTEXT_ANZ );
#else
        {
            void * pUnused = LGTEXT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILADDRESSES_DELETEADDRESS: {
        cremaemailaddressesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
#else
        d = (cremaemailaddressesS *)spBuf;
#endif

        if ( (rc = Cremaemailaddresses_DeleteAddress(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ );
#else
        {
            void * pUnused = CREMAEMAILADDRESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILADDRESSES_INSERTADDRESS: {
        cremaemailaddressesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
#else
        d = (cremaemailaddressesS *)spBuf;
#endif

        if ( (rc = Cremaemailaddresses_InsertAddress(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ );
#else
        {
            void * pUnused = CREMAEMAILADDRESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILADDRESSES_INSERTGVL: {
        cremaemailaddressesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
#else
        d = (cremaemailaddressesS *)spBuf;
#endif

        if ( (rc = Cremaemailaddresses_InsertGVL(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ );
#else
        {
            void * pUnused = CREMAEMAILADDRESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILADDRESSES_INSERTTYPE: {
        cremaemailaddressesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
#else
        d = (cremaemailaddressesS *)spBuf;
#endif

        if ( (rc = Cremaemailaddresses_InsertType(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ );
#else
        {
            void * pUnused = CREMAEMAILADDRESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILADDRESSES_SELEMAILADDRESSES: {
        cremaemailaddressesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
#else
        d = (cremaemailaddressesS *)spBuf;
#endif

        if ( (rc = Cremaemailaddresses_SelEmailAddresses(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ );
#else
        {
            void * pUnused = CREMAEMAILADDRESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILADDRESSES_SELEMAILTYPE: {
        cremaemailaddressesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
#else
        d = (cremaemailaddressesS *)spBuf;
#endif

        if ( (rc = Cremaemailaddresses_SelEmailType(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ );
#else
        {
            void * pUnused = CREMAEMAILADDRESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILADDRESSES_UPDATE: {
        cremaemailaddressesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
#else
        d = (cremaemailaddressesS *)spBuf;
#endif

        if ( (rc = Cremaemailaddresses_Update(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ );
#else
        {
            void * pUnused = CREMAEMAILADDRESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILADDRESSES_UPDATEEMAILADDRESS: {
        cremaemailaddressesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
#else
        d = (cremaemailaddressesS *)spBuf;
#endif

        if ( (rc = Cremaemailaddresses_UpdateEmailAddress(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ );
#else
        {
            void * pUnused = CREMAEMAILADDRESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILADDRESSES_UPDATEGVL: {
        cremaemailaddressesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ);
#else
        d = (cremaemailaddressesS *)spBuf;
#endif

        if ( (rc = Cremaemailaddresses_UpdateGVL(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILADDRESSES_BES, CREMAEMAILADDRESSES_ANZ );
#else
        {
            void * pUnused = CREMAEMAILADDRESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CREMAEMAILREASONS_SELEMAILREASONS: {
        cremaemailreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CREMAEMAILREASONS_BES, CREMAEMAILREASONS_ANZ);
#else
        d = (cremaemailreasonsS *)spBuf;
#endif

        if ( (rc = Cremaemailreasons_SelEmailReasons(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CREMAEMAILREASONS_BES, CREMAEMAILREASONS_ANZ );
#else
        {
            void * pUnused = CREMAEMAILREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHAINCUSTOMERS_SELLIST: {
        chaincustomersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHAINCUSTOMERS_BES, CHAINCUSTOMERS_ANZ);
#else
        d = (chaincustomersS *)spBuf;
#endif

        if ( (rc = Chaincustomers_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHAINCUSTOMERS_BES, CHAINCUSTOMERS_ANZ );
#else
        {
            void * pUnused = CHAINCUSTOMERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKCUSTOMEREXIST_SELEXIST: {
        checkcustomerexistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKCUSTOMEREXIST_BES, CHECKCUSTOMEREXIST_ANZ);
#else
        d = (checkcustomerexistS *)spBuf;
#endif

        if ( (rc = Checkcustomerexist_SelExist(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKCUSTOMEREXIST_BES, CHECKCUSTOMEREXIST_ANZ );
#else
        {
            void * pUnused = CHECKCUSTOMEREXIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKLISTE5_ISLISTE5: {
        checkliste5S s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKLISTE5_BES, CHECKLISTE5_ANZ);
#else
        d = (checkliste5S *)spBuf;
#endif

        if ( (rc = Checkliste5_IsListe5(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKLISTE5_BES, CHECKLISTE5_ANZ );
#else
        {
            void * pUnused = CHECKLISTE5_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTBRANCHINFO_SELLIST: {
        cstbranchinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ);
#else
        d = (cstbranchinfoS *)spBuf;
#endif

        if ( (rc = Cstbranchinfo_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ );
#else
        {
            void * pUnused = CSTBRANCHINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTBRANCHINFO_SELLISTVALID: {
        cstbranchinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ);
#else
        d = (cstbranchinfoS *)spBuf;
#endif

        if ( (rc = Cstbranchinfo_SelListValid(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ );
#else
        {
            void * pUnused = CSTBRANCHINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTBRANCHINFO_INSERT: {
        cstbranchinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ);
#else
        d = (cstbranchinfoS *)spBuf;
#endif

        if ( (rc = Cstbranchinfo_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ );
#else
        {
            void * pUnused = CSTBRANCHINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTBRANCHINFO_UPDATE: {
        cstbranchinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ);
#else
        d = (cstbranchinfoS *)spBuf;
#endif

        if ( (rc = Cstbranchinfo_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ );
#else
        {
            void * pUnused = CSTBRANCHINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTBRANCHINFO_DELETE: {
        cstbranchinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ);
#else
        d = (cstbranchinfoS *)spBuf;
#endif

        if ( (rc = Cstbranchinfo_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ );
#else
        {
            void * pUnused = CSTBRANCHINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTBULGARIA_SELCST: {
        cstbulgariaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTBULGARIA_BES, CSTBULGARIA_ANZ);
#else
        d = (cstbulgariaS *)spBuf;
#endif

        if ( (rc = Cstbulgaria_SelCst(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTBULGARIA_BES, CSTBULGARIA_ANZ );
#else
        {
            void * pUnused = CSTBULGARIA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTBUYINGOPTIONS_SELBUYINGOPTIONS: {
        cstbuyingoptionsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTBUYINGOPTIONS_BES, CSTBUYINGOPTIONS_ANZ);
#else
        d = (cstbuyingoptionsS *)spBuf;
#endif

        if ( (rc = Cstbuyingoptions_SelBuyingOptions(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTBUYINGOPTIONS_BES, CSTBUYINGOPTIONS_ANZ );
#else
        {
            void * pUnused = CSTBUYINGOPTIONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTDISCACC_CHECKEXIST: {
        cstdiscaccS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTDISCACC_BES, CSTDISCACC_ANZ);
#else
        d = (cstdiscaccS *)spBuf;
#endif

        if ( (rc = Cstdiscacc_CheckExist(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTDISCACC_BES, CSTDISCACC_ANZ );
#else
        {
            void * pUnused = CSTDISCACC_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTDISCACC_SELLISTCST: {
        cstdiscaccS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTDISCACC_BES, CSTDISCACC_ANZ);
#else
        d = (cstdiscaccS *)spBuf;
#endif

        if ( (rc = Cstdiscacc_SelListCst(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTDISCACC_BES, CSTDISCACC_ANZ );
#else
        {
            void * pUnused = CSTDISCACC_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTDISCACC_SELLISTGRP: {
        cstdiscaccS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTDISCACC_BES, CSTDISCACC_ANZ);
#else
        d = (cstdiscaccS *)spBuf;
#endif

        if ( (rc = Cstdiscacc_SelListGrp(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTDISCACC_BES, CSTDISCACC_ANZ );
#else
        {
            void * pUnused = CSTDISCACC_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTDISCACCANZ_CHECKMAIN: {
        cstdiscaccanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ);
#else
        d = (cstdiscaccanzS *)spBuf;
#endif

        if ( (rc = Cstdiscaccanz_CheckMain(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ );
#else
        {
            void * pUnused = CSTDISCACCANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTDISCACCANZ_CHECKMEMBER: {
        cstdiscaccanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ);
#else
        d = (cstdiscaccanzS *)spBuf;
#endif

        if ( (rc = Cstdiscaccanz_CheckMember(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ );
#else
        {
            void * pUnused = CSTDISCACCANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTDISCACCANZ_SELLIST: {
        cstdiscaccanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ);
#else
        d = (cstdiscaccanzS *)spBuf;
#endif

        if ( (rc = Cstdiscaccanz_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ );
#else
        {
            void * pUnused = CSTDISCACCANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTDISCACCANZ_SELMAIN: {
        cstdiscaccanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ);
#else
        d = (cstdiscaccanzS *)spBuf;
#endif

        if ( (rc = Cstdiscaccanz_SelMain(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ );
#else
        {
            void * pUnused = CSTDISCACCANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTDISCCONT_SELLIST: {
        cstdisccontS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTDISCCONT_BES, CSTDISCCONT_ANZ);
#else
        d = (cstdisccontS *)spBuf;
#endif

        if ( (rc = Cstdisccont_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTDISCCONT_BES, CSTDISCCONT_ANZ );
#else
        {
            void * pUnused = CSTDISCCONT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTPAYTERM_SELLIST: {
        cstpaytermS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTPAYTERM_BES, CSTPAYTERM_ANZ);
#else
        d = (cstpaytermS *)spBuf;
#endif

        if ( (rc = Cstpayterm_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTPAYTERM_BES, CSTPAYTERM_ANZ );
#else
        {
            void * pUnused = CSTPAYTERM_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CSTREBATETYPE_SELREBATETYPE: {
        cstrebatetypeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CSTREBATETYPE_BES, CSTREBATETYPE_ANZ);
#else
        d = (cstrebatetypeS *)spBuf;
#endif

        if ( (rc = Cstrebatetype_SelRebateType(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CSTREBATETYPE_BES, CSTREBATETYPE_ANZ );
#else
        {
            void * pUnused = CSTREBATETYPE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTPHARMA_SELLIST: {
        custpharmaS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTPHARMA_BES, CUSTPHARMA_ANZ);
#else
        d = (custpharmaS *)spBuf;
#endif

        if ( (rc = Custpharma_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTPHARMA_BES, CUSTPHARMA_ANZ );
#else
        {
            void * pUnused = CUSTPHARMA_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTPHON_SELLIST: {
        custphonS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTPHON_BES, CUSTPHON_ANZ);
#else
        d = (custphonS *)spBuf;
#endif

        if ( (rc = Custphon_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTPHON_BES, CUSTPHON_ANZ );
#else
        {
            void * pUnused = CUSTPHON_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTPHON_SELPHONENO: {
        custphonS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTPHON_BES, CUSTPHON_ANZ);
#else
        d = (custphonS *)spBuf;
#endif

        if ( (rc = Custphon_SelPhoneNo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTPHON_BES, CUSTPHON_ANZ );
#else
        {
            void * pUnused = CUSTPHON_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTPHON_INSERT: {
        custphonS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTPHON_BES, CUSTPHON_ANZ);
#else
        d = (custphonS *)spBuf;
#endif

        if ( (rc = Custphon_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTPHON_BES, CUSTPHON_ANZ );
#else
        {
            void * pUnused = CUSTPHON_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTPHON_DELETE: {
        custphonS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTPHON_BES, CUSTPHON_ANZ);
#else
        d = (custphonS *)spBuf;
#endif

        if ( (rc = Custphon_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTPHON_BES, CUSTPHON_ANZ );
#else
        {
            void * pUnused = CUSTPHON_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTROUT_SELACTROUTING: {
        custroutS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTROUT_BES, CUSTROUT_ANZ);
#else
        d = (custroutS *)spBuf;
#endif

        if ( (rc = Custrout_SelActRouting(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTROUT_BES, CUSTROUT_ANZ );
#else
        {
            void * pUnused = CUSTROUT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTROUT_SELLIST: {
        custroutS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTROUT_BES, CUSTROUT_ANZ);
#else
        d = (custroutS *)spBuf;
#endif

        if ( (rc = Custrout_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTROUT_BES, CUSTROUT_ANZ );
#else
        {
            void * pUnused = CUSTROUT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTROUT_INSERT: {
        custroutS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTROUT_BES, CUSTROUT_ANZ);
#else
        d = (custroutS *)spBuf;
#endif

        if ( (rc = Custrout_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTROUT_BES, CUSTROUT_ANZ );
#else
        {
            void * pUnused = CUSTROUT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTROUT_UPDATE: {
        custroutS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTROUT_BES, CUSTROUT_ANZ);
#else
        d = (custroutS *)spBuf;
#endif

        if ( (rc = Custrout_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTROUT_BES, CUSTROUT_ANZ );
#else
        {
            void * pUnused = CUSTROUT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTROUT_DELETE: {
        custroutS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTROUT_BES, CUSTROUT_ANZ);
#else
        d = (custroutS *)spBuf;
#endif

        if ( (rc = Custrout_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTROUT_BES, CUSTROUT_ANZ );
#else
        {
            void * pUnused = CUSTROUT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CUSTOMERDOUBLES_SELDOUBLE: {
        customerdoublesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CUSTOMERDOUBLES_BES, CUSTOMERDOUBLES_ANZ);
#else
        d = (customerdoublesS *)spBuf;
#endif

        if ( (rc = Customerdoubles_SelDouble(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CUSTOMERDOUBLES_BES, CUSTOMERDOUBLES_ANZ );
#else
        {
            void * pUnused = CUSTOMERDOUBLES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISTRESSROUTING_SELNOT: {
        distressroutingS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ);
#else
        d = (distressroutingS *)spBuf;
#endif

        if ( (rc = Distressrouting_SelNot(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ );
#else
        {
            void * pUnused = DISTRESSROUTING_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISTRESSROUTING_SELROUTED: {
        distressroutingS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ);
#else
        d = (distressroutingS *)spBuf;
#endif

        if ( (rc = Distressrouting_SelRouted(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ );
#else
        {
            void * pUnused = DISTRESSROUTING_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISTRESSROUTING_UPDATE: {
        distressroutingS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ);
#else
        d = (distressroutingS *)spBuf;
#endif

        if ( (rc = Distressrouting_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ );
#else
        {
            void * pUnused = DISTRESSROUTING_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISTRESSROUTING_GETCOUNT: {
        distressroutingS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ);
#else
        d = (distressroutingS *)spBuf;
#endif

        if ( (rc = Distressrouting_GetCount(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ );
#else
        {
            void * pUnused = DISTRESSROUTING_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ENCLOSERTIMES_SELLIST: {
        enclosertimesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ);
#else
        d = (enclosertimesS *)spBuf;
#endif

        if ( (rc = Enclosertimes_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ );
#else
        {
            void * pUnused = ENCLOSERTIMES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ENCLOSERTIMES_INSERT: {
        enclosertimesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ);
#else
        d = (enclosertimesS *)spBuf;
#endif

        if ( (rc = Enclosertimes_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ );
#else
        {
            void * pUnused = ENCLOSERTIMES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ENCLOSERTIMES_UPDATE: {
        enclosertimesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ);
#else
        d = (enclosertimesS *)spBuf;
#endif

        if ( (rc = Enclosertimes_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ );
#else
        {
            void * pUnused = ENCLOSERTIMES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ENCLOSERTIMES_DELETE: {
        enclosertimesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ);
#else
        d = (enclosertimesS *)spBuf;
#endif

        if ( (rc = Enclosertimes_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ );
#else
        {
            void * pUnused = ENCLOSERTIMES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ENCLOSERTIMES_COPYENCLOSER: {
        enclosertimesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ);
#else
        d = (enclosertimesS *)spBuf;
#endif

        if ( (rc = Enclosertimes_CopyEncloser(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ );
#else
        {
            void * pUnused = ENCLOSERTIMES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KNDTOURFENSTER_SELPERIODS: {
        kndtourfensterS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KNDTOURFENSTER_BES, KNDTOURFENSTER_ANZ);
#else
        d = (kndtourfensterS *)spBuf;
#endif

        if ( (rc = Kndtourfenster_SelPeriods(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KNDTOURFENSTER_BES, KNDTOURFENSTER_ANZ );
#else
        {
            void * pUnused = KNDTOURFENSTER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KNDTOURWOCHE_SELLIST: {
        kndtourwocheS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KNDTOURWOCHE_BES, KNDTOURWOCHE_ANZ);
#else
        d = (kndtourwocheS *)spBuf;
#endif

        if ( (rc = Kndtourwoche_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KNDTOURWOCHE_BES, KNDTOURWOCHE_ANZ );
#else
        {
            void * pUnused = KNDTOURWOCHE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KNDTOURWOCHE2_SELLIST: {
        kndtourwoche2S s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KNDTOURWOCHE2_BES, KNDTOURWOCHE2_ANZ);
#else
        d = (kndtourwoche2S *)spBuf;
#endif

        if ( (rc = Kndtourwoche2_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KNDTOURWOCHE2_BES, KNDTOURWOCHE2_ANZ );
#else
        {
            void * pUnused = KNDTOURWOCHE2_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KNDTOURWOCHE3_SELLIST: {
        kndtourwoche3S s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KNDTOURWOCHE3_BES, KNDTOURWOCHE3_ANZ);
#else
        d = (kndtourwoche3S *)spBuf;
#endif

        if ( (rc = Kndtourwoche3_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KNDTOURWOCHE3_BES, KNDTOURWOCHE3_ANZ );
#else
        {
            void * pUnused = KNDTOURWOCHE3_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KNDFILINFO_SELKND: {
        kndfilinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KNDFILINFO_BES, KNDFILINFO_ANZ);
#else
        d = (kndfilinfoS *)spBuf;
#endif

        if ( (rc = Kndfilinfo_SelKnd(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KNDFILINFO_BES, KNDFILINFO_ANZ );
#else
        {
            void * pUnused = KNDFILINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KNDFILINFO2_SELINFO: {
        kndfilinfo2S s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KNDFILINFO2_BES, KNDFILINFO2_ANZ);
#else
        d = (kndfilinfo2S *)spBuf;
#endif

        if ( (rc = Kndfilinfo2_SelInfo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KNDFILINFO2_BES, KNDFILINFO2_ANZ );
#else
        {
            void * pUnused = KNDFILINFO2_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KREDITLIMIT_SELLIMIT: {
        kreditlimitS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KREDITLIMIT_BES, KREDITLIMIT_ANZ);
#else
        d = (kreditlimitS *)spBuf;
#endif

        if ( (rc = Kreditlimit_SelLimit(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KREDITLIMIT_BES, KREDITLIMIT_ANZ );
#else
        {
            void * pUnused = KREDITLIMIT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KREDITLIMIT_SELLIMIT1: {
        kreditlimitS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KREDITLIMIT_BES, KREDITLIMIT_ANZ);
#else
        d = (kreditlimitS *)spBuf;
#endif

        if ( (rc = Kreditlimit_SelLimit1(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KREDITLIMIT_BES, KREDITLIMIT_ANZ );
#else
        {
            void * pUnused = KREDITLIMIT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KREDITLIMIT_SELLIMIT2: {
        kreditlimitS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KREDITLIMIT_BES, KREDITLIMIT_ANZ);
#else
        d = (kreditlimitS *)spBuf;
#endif

        if ( (rc = Kreditlimit_SelLimit2(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KREDITLIMIT_BES, KREDITLIMIT_ANZ );
#else
        {
            void * pUnused = KREDITLIMIT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KREDITLIMIT_SELLIMITMAIN: {
        kreditlimitS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KREDITLIMIT_BES, KREDITLIMIT_ANZ);
#else
        d = (kreditlimitS *)spBuf;
#endif

        if ( (rc = Kreditlimit_SelLimitMain(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KREDITLIMIT_BES, KREDITLIMIT_ANZ );
#else
        {
            void * pUnused = KREDITLIMIT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KUNDELIZENSEN_SELLICENSES: {
        kundelizensenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KUNDELIZENSEN_BES, KUNDELIZENSEN_ANZ);
#else
        d = (kundelizensenS *)spBuf;
#endif

        if ( (rc = Kundelizensen_SelLicenses(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KUNDELIZENSEN_BES, KUNDELIZENSEN_ANZ );
#else
        {
            void * pUnused = KUNDELIZENSEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KUNDEVERBUNDFILIALE_SEL: {
        kundeverbundfilialeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ);
#else
        d = (kundeverbundfilialeS *)spBuf;
#endif

        if ( (rc = Kundeverbundfiliale_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ );
#else
        {
            void * pUnused = KUNDEVERBUNDFILIALE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KUNDEVERBUNDFILIALE_INSERT: {
        kundeverbundfilialeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ);
#else
        d = (kundeverbundfilialeS *)spBuf;
#endif

        if ( (rc = Kundeverbundfiliale_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ );
#else
        {
            void * pUnused = KUNDEVERBUNDFILIALE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KUNDEVERBUNDFILIALE_UPDATE: {
        kundeverbundfilialeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ);
#else
        d = (kundeverbundfilialeS *)spBuf;
#endif

        if ( (rc = Kundeverbundfiliale_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ );
#else
        {
            void * pUnused = KUNDEVERBUNDFILIALE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case KUNDEVERBUNDFILIALE_DELETE: {
        kundeverbundfilialeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ);
#else
        d = (kundeverbundfilialeS *)spBuf;
#endif

        if ( (rc = Kundeverbundfiliale_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ );
#else
        {
            void * pUnused = KUNDEVERBUNDFILIALE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case LISTE5_SELLIST: {
        liste5S s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, LISTE5_BES, LISTE5_ANZ);
#else
        d = (liste5S *)spBuf;
#endif

        if ( (rc = Liste5_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, LISTE5_BES, LISTE5_ANZ );
#else
        {
            void * pUnused = LISTE5_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMEREMERGENCYSERVICEPLAN_SELLIST: {
        mcustomeremergencyserviceplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ);
#else
        d = (mcustomeremergencyserviceplanS *)spBuf;
#endif

        if ( (rc = Mcustomeremergencyserviceplan_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMEREMERGENCYSERVICEPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMEREMERGENCYSERVICEPLAN_SELLISTHIST: {
        mcustomeremergencyserviceplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ);
#else
        d = (mcustomeremergencyserviceplanS *)spBuf;
#endif

        if ( (rc = Mcustomeremergencyserviceplan_SelListHist(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMEREMERGENCYSERVICEPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMEREMERGENCYSERVICEPLAN_SELUNI: {
        mcustomeremergencyserviceplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ);
#else
        d = (mcustomeremergencyserviceplanS *)spBuf;
#endif

        if ( (rc = Mcustomeremergencyserviceplan_SelUni(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMEREMERGENCYSERVICEPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMEREMERGENCYSERVICEPLAN_INSERT: {
        mcustomeremergencyserviceplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ);
#else
        d = (mcustomeremergencyserviceplanS *)spBuf;
#endif

        if ( (rc = Mcustomeremergencyserviceplan_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMEREMERGENCYSERVICEPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMEREMERGENCYSERVICEPLAN_UPDATE: {
        mcustomeremergencyserviceplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ);
#else
        d = (mcustomeremergencyserviceplanS *)spBuf;
#endif

        if ( (rc = Mcustomeremergencyserviceplan_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMEREMERGENCYSERVICEPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMEREMERGENCYSERVICEPLAN_DELETE: {
        mcustomeremergencyserviceplanS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ);
#else
        d = (mcustomeremergencyserviceplanS *)spBuf;
#endif

        if ( (rc = Mcustomeremergencyserviceplan_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ );
#else
        {
            void * pUnused = MCUSTOMEREMERGENCYSERVICEPLAN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERVACATION_SELLIST: {
        mcustomervacationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ);
#else
        d = (mcustomervacationS *)spBuf;
#endif

        if ( (rc = Mcustomervacation_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ );
#else
        {
            void * pUnused = MCUSTOMERVACATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERVACATION_SELUNI: {
        mcustomervacationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ);
#else
        d = (mcustomervacationS *)spBuf;
#endif

        if ( (rc = Mcustomervacation_SelUni(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ );
#else
        {
            void * pUnused = MCUSTOMERVACATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERVACATION_INSERT: {
        mcustomervacationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ);
#else
        d = (mcustomervacationS *)spBuf;
#endif

        if ( (rc = Mcustomervacation_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ );
#else
        {
            void * pUnused = MCUSTOMERVACATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERVACATION_UPDATE: {
        mcustomervacationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ);
#else
        d = (mcustomervacationS *)spBuf;
#endif

        if ( (rc = Mcustomervacation_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ );
#else
        {
            void * pUnused = MCUSTOMERVACATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERVACATION_DELETE: {
        mcustomervacationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ);
#else
        d = (mcustomervacationS *)spBuf;
#endif

        if ( (rc = Mcustomervacation_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ );
#else
        {
            void * pUnused = MCUSTOMERVACATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCUSTOMERVACATION_SELNEXTEFFECTIVE: {
        mcustomervacationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ);
#else
        d = (mcustomervacationS *)spBuf;
#endif

        if ( (rc = Mcustomervacation_SelNextEffective(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ );
#else
        {
            void * pUnused = MCUSTOMERVACATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PAYTERM_SELLIST: {
        paytermS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PAYTERM_BES, PAYTERM_ANZ);
#else
        d = (paytermS *)spBuf;
#endif

        if ( (rc = Payterm_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PAYTERM_BES, PAYTERM_ANZ );
#else
        {
            void * pUnused = PAYTERM_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PAYMENTLIST_SELLIST: {
        paymentlistS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PAYMENTLIST_BES, PAYMENTLIST_ANZ);
#else
        d = (paymentlistS *)spBuf;
#endif

        if ( (rc = Paymentlist_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PAYMENTLIST_BES, PAYMENTLIST_ANZ );
#else
        {
            void * pUnused = PAYMENTLIST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PREWHOLECST_ISPREWHOLECST: {
        prewholecstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PREWHOLECST_BES, PREWHOLECST_ANZ);
#else
        d = (prewholecstS *)spBuf;
#endif

        if ( (rc = Prewholecst_IsPrewholeCst(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PREWHOLECST_BES, PREWHOLECST_ANZ );
#else
        {
            void * pUnused = PREWHOLECST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SHIPAUXNO_SELLIST: {
        shipauxnoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SHIPAUXNO_BES, SHIPAUXNO_ANZ);
#else
        d = (shipauxnoS *)spBuf;
#endif

        if ( (rc = Shipauxno_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SHIPAUXNO_BES, SHIPAUXNO_ANZ );
#else
        {
            void * pUnused = SHIPAUXNO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SHIPAUXNO_INSERT: {
        shipauxnoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SHIPAUXNO_BES, SHIPAUXNO_ANZ);
#else
        d = (shipauxnoS *)spBuf;
#endif

        if ( (rc = Shipauxno_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SHIPAUXNO_BES, SHIPAUXNO_ANZ );
#else
        {
            void * pUnused = SHIPAUXNO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SHIPAUXNO_UPDATE: {
        shipauxnoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SHIPAUXNO_BES, SHIPAUXNO_ANZ);
#else
        d = (shipauxnoS *)spBuf;
#endif

        if ( (rc = Shipauxno_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SHIPAUXNO_BES, SHIPAUXNO_ANZ );
#else
        {
            void * pUnused = SHIPAUXNO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SHIPAUXNO_DELETE: {
        shipauxnoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SHIPAUXNO_BES, SHIPAUXNO_ANZ);
#else
        d = (shipauxnoS *)spBuf;
#endif

        if ( (rc = Shipauxno_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SHIPAUXNO_BES, SHIPAUXNO_ANZ );
#else
        {
            void * pUnused = SHIPAUXNO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TOURPFLEGE_SELTOURENKUNDE: {
        tourpflegeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TOURPFLEGE_BES, TOURPFLEGE_ANZ);
#else
        d = (tourpflegeS *)spBuf;
#endif

        if ( (rc = Tourpflege_SelTourenKunde(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TOURPFLEGE_BES, TOURPFLEGE_ANZ );
#else
        {
            void * pUnused = TOURPFLEGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TOURPFLEGE_UPDATE: {
        tourpflegeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TOURPFLEGE_BES, TOURPFLEGE_ANZ);
#else
        d = (tourpflegeS *)spBuf;
#endif

        if ( (rc = Tourpflege_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TOURPFLEGE_BES, TOURPFLEGE_ANZ );
#else
        {
            void * pUnused = TOURPFLEGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_SELDAY: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_SelDay(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_SELLIST: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_INSERT: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_UPDATE: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_DELETE: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_DELETEALL: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_DeleteAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_INSERTALL: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_InsertAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_SELECTACTTOUREN: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_SelectActTouren(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_SELECTTOUREN: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_SelectTouren(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDCST_SETACTIV: {
        delayedcstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDCST_BES, DELAYEDCST_ANZ);
#else
        d = (delayedcstS *)spBuf;
#endif

        if ( (rc = delayedcst_SetActiv(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDCST_BES, DELAYEDCST_ANZ );
#else
        {
            void * pUnused = DELAYEDCST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDDELIVERYCSTSPECIAL_SEL: {
        delayeddeliverycstspecialS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ);
#else
        d = (delayeddeliverycstspecialS *)spBuf;
#endif

        if ( (rc = delayeddeliverycstspecial_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ );
#else
        {
            void * pUnused = DELAYEDDELIVERYCSTSPECIAL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDDELIVERYCSTSPECIAL_SELUNI: {
        delayeddeliverycstspecialS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ);
#else
        d = (delayeddeliverycstspecialS *)spBuf;
#endif

        if ( (rc = delayeddeliverycstspecial_SelUni(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ );
#else
        {
            void * pUnused = DELAYEDDELIVERYCSTSPECIAL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDDELIVERYCSTSPECIAL_INSERT: {
        delayeddeliverycstspecialS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ);
#else
        d = (delayeddeliverycstspecialS *)spBuf;
#endif

        if ( (rc = delayeddeliverycstspecial_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ );
#else
        {
            void * pUnused = DELAYEDDELIVERYCSTSPECIAL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDDELIVERYCSTSPECIAL_UPDATE: {
        delayeddeliverycstspecialS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ);
#else
        d = (delayeddeliverycstspecialS *)spBuf;
#endif

        if ( (rc = delayeddeliverycstspecial_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ );
#else
        {
            void * pUnused = DELAYEDDELIVERYCSTSPECIAL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DELAYEDDELIVERYCSTSPECIAL_DELETE: {
        delayeddeliverycstspecialS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ);
#else
        d = (delayeddeliverycstspecialS *)spBuf;
#endif

        if ( (rc = delayeddeliverycstspecial_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ );
#else
        {
            void * pUnused = DELAYEDDELIVERYCSTSPECIAL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case EILBOTENDRUCK_DRUCKEIL: {
        eilbotendruckS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, EILBOTENDRUCK_BES, EILBOTENDRUCK_ANZ);
#else
        d = (eilbotendruckS *)spBuf;
#endif

        if ( (rc = Eilbotendruck_druckeil(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, EILBOTENDRUCK_BES, EILBOTENDRUCK_ANZ );
#else
        {
            void * pUnused = EILBOTENDRUCK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case EXTRATOURREASONS_SELLIST: {
        extratourreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ);
#else
        d = (extratourreasonsS *)spBuf;
#endif

        if ( (rc = Extratourreasons_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ );
#else
        {
            void * pUnused = EXTRATOURREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case EXTRATOURREASONS_SELLISTALL: {
        extratourreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ);
#else
        d = (extratourreasonsS *)spBuf;
#endif

        if ( (rc = Extratourreasons_SelListAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ );
#else
        {
            void * pUnused = EXTRATOURREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case EXTRATOURREASONS_INSERT: {
        extratourreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ);
#else
        d = (extratourreasonsS *)spBuf;
#endif

        if ( (rc = Extratourreasons_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ );
#else
        {
            void * pUnused = EXTRATOURREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case EXTRATOURREASONS_DELETE: {
        extratourreasonsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ);
#else
        d = (extratourreasonsS *)spBuf;
#endif

        if ( (rc = Extratourreasons_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, EXTRATOURREASONS_BES, EXTRATOURREASONS_ANZ );
#else
        {
            void * pUnused = EXTRATOURREASONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case HERSTELLERLISTE_SELLIST: {
        herstellerlisteS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, HERSTELLERLISTE_BES, HERSTELLERLISTE_ANZ);
#else
        d = (herstellerlisteS *)spBuf;
#endif

        if ( (rc = Herstellerliste_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, HERSTELLERLISTE_BES, HERSTELLERLISTE_ANZ );
#else
        {
            void * pUnused = HERSTELLERLISTE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MSV3CSTINFO_SELCSTINFO: {
        msv3cstinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MSV3CSTINFO_BES, MSV3CSTINFO_ANZ);
#else
        d = (msv3cstinfoS *)spBuf;
#endif

        if ( (rc = Msv3cstinfo_SelCstInfo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MSV3CSTINFO_BES, MSV3CSTINFO_ANZ );
#else
        {
            void * pUnused = MSV3CSTINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MSV3EINSTELLUNGEN_SELADJUSTMENTS: {
        msv3einstellungenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MSV3EINSTELLUNGEN_BES, MSV3EINSTELLUNGEN_ANZ);
#else
        d = (msv3einstellungenS *)spBuf;
#endif

        if ( (rc = Msv3einstellungen_SelAdjustments(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MSV3EINSTELLUNGEN_BES, MSV3EINSTELLUNGEN_ANZ );
#else
        {
            void * pUnused = MSV3EINSTELLUNGEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MSV3INFO_SELMSV3: {
        msv3infoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MSV3INFO_BES, MSV3INFO_ANZ);
#else
        d = (msv3infoS *)spBuf;
#endif

        if ( (rc = Msv3info_SelMSV3(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MSV3INFO_BES, MSV3INFO_ANZ );
#else
        {
            void * pUnused = MSV3INFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MSV3ORDERINFO_SELMSV3ORDERS: {
        msv3orderinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MSV3ORDERINFO_BES, MSV3ORDERINFO_ANZ);
#else
        d = (msv3orderinfoS *)spBuf;
#endif

        if ( (rc = Msv3orderinfo_SelMSV3Orders(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MSV3ORDERINFO_BES, MSV3ORDERINFO_ANZ );
#else
        {
            void * pUnused = MSV3ORDERINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MSV3TOURINFO_SELBFTODAY: {
        msv3tourinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MSV3TOURINFO_BES, MSV3TOURINFO_ANZ);
#else
        d = (msv3tourinfoS *)spBuf;
#endif

        if ( (rc = Msv3tourinfo_SelBFToday(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MSV3TOURINFO_BES, MSV3TOURINFO_ANZ );
#else
        {
            void * pUnused = MSV3TOURINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKDFREASON_SELEVENT: {
        checkdfreasonS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKDFREASON_BES, CHECKDFREASON_ANZ);
#else
        d = (checkdfreasonS *)spBuf;
#endif

        if ( (rc = Checkdfreason_SelEvent(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKDFREASON_BES, CHECKDFREASON_ANZ );
#else
        {
            void * pUnused = CHECKDFREASON_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKKLRELEASED_SELRELEASED: {
        checkklreleasedS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKKLRELEASED_BES, CHECKKLRELEASED_ANZ);
#else
        d = (checkklreleasedS *)spBuf;
#endif

        if ( (rc = Checkklreleased_SelReleased(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKKLRELEASED_BES, CHECKKLRELEASED_ANZ );
#else
        {
            void * pUnused = CHECKKLRELEASED_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKORDERNODD_CHECKNODD: {
        checkordernoddS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKORDERNODD_BES, CHECKORDERNODD_ANZ);
#else
        d = (checkordernoddS *)spBuf;
#endif

        if ( (rc = Checkordernodd_CheckNoDD(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKORDERNODD_BES, CHECKORDERNODD_ANZ );
#else
        {
            void * pUnused = CHECKORDERNODD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKORDERZEROD_SELAUFWERT: {
        checkorderzerodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKORDERZEROD_BES, CHECKORDERZEROD_ANZ);
#else
        d = (checkorderzerodS *)spBuf;
#endif

        if ( (rc = Checkorderzerod_SelAufwert(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKORDERZEROD_BES, CHECKORDERZEROD_ANZ );
#else
        {
            void * pUnused = CHECKORDERZEROD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKORDERZERODOLD_SELAUFWERT: {
        checkorderzerodoldS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKORDERZERODOLD_BES, CHECKORDERZERODOLD_ANZ);
#else
        d = (checkorderzerodoldS *)spBuf;
#endif

        if ( (rc = Checkorderzerodold_SelAufwert(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKORDERZERODOLD_BES, CHECKORDERZERODOLD_ANZ );
#else
        {
            void * pUnused = CHECKORDERZERODOLD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKORDERLABEL_SELLABELTYPE: {
        checkorderlabelS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKORDERLABEL_BES, CHECKORDERLABEL_ANZ);
#else
        d = (checkorderlabelS *)spBuf;
#endif

        if ( (rc = Checkorderlabel_SelLabelType(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKORDERLABEL_BES, CHECKORDERLABEL_ANZ );
#else
        {
            void * pUnused = CHECKORDERLABEL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DRIVER_SELACT: {
        driverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DRIVER_BES, DRIVER_ANZ);
#else
        d = (driverS *)spBuf;
#endif

        if ( (rc = Driver_SelAct(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DRIVER_BES, DRIVER_ANZ );
#else
        {
            void * pUnused = DRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DRIVER_SELOLD: {
        driverS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DRIVER_BES, DRIVER_ANZ);
#else
        d = (driverS *)spBuf;
#endif

        if ( (rc = Driver_SelOld(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DRIVER_BES, DRIVER_ANZ );
#else
        {
            void * pUnused = DRIVER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case INVOICENOS_SELLIST: {
        invoicenosS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, INVOICENOS_BES, INVOICENOS_ANZ);
#else
        d = (invoicenosS *)spBuf;
#endif

        if ( (rc = Invoicenos_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, INVOICENOS_BES, INVOICENOS_ANZ );
#else
        {
            void * pUnused = INVOICENOS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case INVOICENOSOLD_SELLIST: {
        invoicenosoldS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, INVOICENOSOLD_BES, INVOICENOSOLD_ANZ);
#else
        d = (invoicenosoldS *)spBuf;
#endif

        if ( (rc = Invoicenosold_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, INVOICENOSOLD_BES, INVOICENOSOLD_ANZ );
#else
        {
            void * pUnused = INVOICENOSOLD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_CHECKOPOVERLAP: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_CheckOPOverLap(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_DELOPOPTFORDAY: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_DelOPOPTForDay(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_DELETEOPANDOPT: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_DeleteOPAndOPT(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_DELETEOPFORDAY: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_DeleteOPForDay(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_DELETEOPT: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_DeleteOPT(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_DELETEOPTFORDAY: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_DeleteOPTForDay(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_INSERTOPANDOPT: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_InsertOPAndOPT(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_INSERTOPT: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_InsertOPT(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_SELCONSTIME: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_SelConsTime(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_SELHIGHKIPPTIME: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_SelHighKippTime(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_SELOPCHILDCOUNT: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_SelOPChildCount(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_SELOPWEEKDAYS: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_SelOPWeekdays(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_SELTIMESLASTTOUR: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_SelTimesLastTour(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_SELTOURDATA: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_SelTourData(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_SELTOURFORIDF: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_SelTourForIDF(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_SELWEEKDAYS4TOUR: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_SelWeekdays4Tour(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_UPDATETIME: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_UpdateTime(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORDERPERIOD_UPDATETIMESINGLE: {
        orderperiodS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORDERPERIOD_BES, ORDERPERIOD_ANZ);
#else
        d = (orderperiodS *)spBuf;
#endif

        if ( (rc = Orderperiod_UpdateTimeSingle(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORDERPERIOD_BES, ORDERPERIOD_ANZ );
#else
        {
            void * pUnused = ORDERPERIOD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORIGINTYPESETTINGSPF_SELLIST: {
        origintypesettingspfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ);
#else
        d = (origintypesettingspfS *)spBuf;
#endif

        if ( (rc = Origintypesettingspf_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ );
#else
        {
            void * pUnused = ORIGINTYPESETTINGSPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORIGINTYPESETTINGSPF_INSERT: {
        origintypesettingspfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ);
#else
        d = (origintypesettingspfS *)spBuf;
#endif

        if ( (rc = Origintypesettingspf_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ );
#else
        {
            void * pUnused = ORIGINTYPESETTINGSPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORIGINTYPESETTINGSPF_UPDATE: {
        origintypesettingspfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ);
#else
        d = (origintypesettingspfS *)spBuf;
#endif

        if ( (rc = Origintypesettingspf_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ );
#else
        {
            void * pUnused = ORIGINTYPESETTINGSPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORIGINTYPESETTINGSPF_DELETE: {
        origintypesettingspfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ);
#else
        d = (origintypesettingspfS *)spBuf;
#endif

        if ( (rc = Origintypesettingspf_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ );
#else
        {
            void * pUnused = ORIGINTYPESETTINGSPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ORIGINTYPESETTINGSPF_SELLISTNOTDEFINED: {
        origintypesettingspfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ);
#else
        d = (origintypesettingspfS *)spBuf;
#endif

        if ( (rc = Origintypesettingspf_SelListNotDefined(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ORIGINTYPESETTINGSPF_BES, ORIGINTYPESETTINGSPF_ANZ );
#else
        {
            void * pUnused = ORIGINTYPESETTINGSPF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case REMARKTYPES_SELLIST: {
        remarktypesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, REMARKTYPES_BES, REMARKTYPES_ANZ);
#else
        d = (remarktypesS *)spBuf;
#endif

        if ( (rc = Remarktypes_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, REMARKTYPES_BES, REMARKTYPES_ANZ );
#else
        {
            void * pUnused = REMARKTYPES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SPECIALNUMBERS_SELNUMBER: {
        specialnumbersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SPECIALNUMBERS_BES, SPECIALNUMBERS_ANZ);
#else
        d = (specialnumbersS *)spBuf;
#endif

        if ( (rc = Specialnumbers_SelNumber(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SPECIALNUMBERS_BES, SPECIALNUMBERS_ANZ );
#else
        {
            void * pUnused = SPECIALNUMBERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SPECIALNUMBERSOLD_SELNUMBER: {
        specialnumbersoldS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SPECIALNUMBERSOLD_BES, SPECIALNUMBERSOLD_ANZ);
#else
        d = (specialnumbersoldS *)spBuf;
#endif

        if ( (rc = Specialnumbersold_SelNumber(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SPECIALNUMBERSOLD_BES, SPECIALNUMBERSOLD_ANZ );
#else
        {
            void * pUnused = SPECIALNUMBERSOLD_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCHECKPROCESS_SELPROCESS: {
        mcheckprocessS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ);
#else
        d = (mcheckprocessS *)spBuf;
#endif

        if ( (rc = Mcheckprocess_SelProcess(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ );
#else
        {
            void * pUnused = MCHECKPROCESS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCHECKPROCESS_INSERT: {
        mcheckprocessS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ);
#else
        d = (mcheckprocessS *)spBuf;
#endif

        if ( (rc = Mcheckprocess_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ );
#else
        {
            void * pUnused = MCHECKPROCESS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCHECKPROCESS_UPDPROCESS: {
        mcheckprocessS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ);
#else
        d = (mcheckprocessS *)spBuf;
#endif

        if ( (rc = Mcheckprocess_UpdProcess(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ );
#else
        {
            void * pUnused = MCHECKPROCESS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MCHECKPROCESS_DELPROCESS: {
        mcheckprocessS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ);
#else
        d = (mcheckprocessS *)spBuf;
#endif

        if ( (rc = Mcheckprocess_DelProcess(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MCHECKPROCESS_BES, MCHECKPROCESS_ANZ );
#else
        {
            void * pUnused = MCHECKPROCESS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKPROCESSES_SELLIST: {
        mumkprocessesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ);
#else
        d = (mumkprocessesS *)spBuf;
#endif

        if ( (rc = Mumkprocesses_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ );
#else
        {
            void * pUnused = MUMKPROCESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKPROCESSES_STARTCALLPLAN: {
        mumkprocessesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ);
#else
        d = (mumkprocessesS *)spBuf;
#endif

        if ( (rc = Mumkprocesses_StartCallplan(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ );
#else
        {
            void * pUnused = MUMKPROCESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKPROCESSES_STARTUMKALL: {
        mumkprocessesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ);
#else
        d = (mumkprocessesS *)spBuf;
#endif

        if ( (rc = Mumkprocesses_StartUmkAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ );
#else
        {
            void * pUnused = MUMKPROCESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKPROCESSES_STARTUMKUNIQUE: {
        mumkprocessesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ);
#else
        d = (mumkprocessesS *)spBuf;
#endif

        if ( (rc = Mumkprocesses_StartUmkUnique(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ );
#else
        {
            void * pUnused = MUMKPROCESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKPROCESSES_STOPCALLPLAN: {
        mumkprocessesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ);
#else
        d = (mumkprocessesS *)spBuf;
#endif

        if ( (rc = Mumkprocesses_StopCallplan(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ );
#else
        {
            void * pUnused = MUMKPROCESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKPROCESSES_STOPUMKALL: {
        mumkprocessesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ);
#else
        d = (mumkprocessesS *)spBuf;
#endif

        if ( (rc = Mumkprocesses_StopUmkAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ );
#else
        {
            void * pUnused = MUMKPROCESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MUMKPROCESSES_STOPUMKUNIQUE: {
        mumkprocessesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ);
#else
        d = (mumkprocessesS *)spBuf;
#endif

        if ( (rc = Mumkprocesses_StopUmkUnique(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MUMKPROCESSES_BES, MUMKPROCESSES_ANZ );
#else
        {
            void * pUnused = MUMKPROCESSES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PRODUCTPROMO_SELLIST: {
        productpromoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PRODUCTPROMO_BES, PRODUCTPROMO_ANZ);
#else
        d = (productpromoS *)spBuf;
#endif

        if ( (rc = Productpromo_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PRODUCTPROMO_BES, PRODUCTPROMO_ANZ );
#else
        {
            void * pUnused = PRODUCTPROMO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOHERST_SELLIST: {
        promoherstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOHERST_BES, PROMOHERST_ANZ);
#else
        d = (promoherstS *)spBuf;
#endif

        if ( (rc = Promoherst_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOHERST_BES, PROMOHERST_ANZ );
#else
        {
            void * pUnused = PROMOHERST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOMANUFACT_SELMANUNO: {
        promomanufactS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOMANUFACT_BES, PROMOMANUFACT_ANZ);
#else
        d = (promomanufactS *)spBuf;
#endif

        if ( (rc = Promomanufact_SelManuNo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOMANUFACT_BES, PROMOMANUFACT_ANZ );
#else
        {
            void * pUnused = PROMOMANUFACT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOMEMBERS_SELLIST: {
        promomembersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOMEMBERS_BES, PROMOMEMBERS_ANZ);
#else
        d = (promomembersS *)spBuf;
#endif

        if ( (rc = Promomembers_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOMEMBERS_BES, PROMOMEMBERS_ANZ );
#else
        {
            void * pUnused = PROMOMEMBERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOTIONEN_SELLIST: {
        promotionenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOTIONEN_BES, PROMOTIONEN_ANZ);
#else
        d = (promotionenS *)spBuf;
#endif

        if ( (rc = Promotionen_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOTIONEN_BES, PROMOTIONEN_ANZ );
#else
        {
            void * pUnused = PROMOTIONEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOTIONEN_SELLISTMANU: {
        promotionenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOTIONEN_BES, PROMOTIONEN_ANZ);
#else
        d = (promotionenS *)spBuf;
#endif

        if ( (rc = Promotionen_SelListManu(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOTIONEN_BES, PROMOTIONEN_ANZ );
#else
        {
            void * pUnused = PROMOTIONEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOTIONEN_SELPROMONO: {
        promotionenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOTIONEN_BES, PROMOTIONEN_ANZ);
#else
        d = (promotionenS *)spBuf;
#endif

        if ( (rc = Promotionen_SelPromoNo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOTIONEN_BES, PROMOTIONEN_ANZ );
#else
        {
            void * pUnused = PROMOTIONEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOTIONEN_SELPROMONOMANU: {
        promotionenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOTIONEN_BES, PROMOTIONEN_ANZ);
#else
        d = (promotionenS *)spBuf;
#endif

        if ( (rc = Promotionen_SelPromoNoManu(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOTIONEN_BES, PROMOTIONEN_ANZ );
#else
        {
            void * pUnused = PROMOTIONEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case STOTINKEN_SELLIST: {
        stotinkenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, STOTINKEN_BES, STOTINKEN_ANZ);
#else
        d = (stotinkenS *)spBuf;
#endif

        if ( (rc = Stotinken_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, STOTINKEN_BES, STOTINKEN_ANZ );
#else
        {
            void * pUnused = STOTINKEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKPROMOSCALE_PROMOSCALEEXIST: {
        checkpromoscaleS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKPROMOSCALE_BES, CHECKPROMOSCALE_ANZ);
#else
        d = (checkpromoscaleS *)spBuf;
#endif

        if ( (rc = Checkpromoscale_PromoScaleExist(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKPROMOSCALE_BES, CHECKPROMOSCALE_ANZ );
#else
        {
            void * pUnused = CHECKPROMOSCALE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOQUOTAANZ_SELLIST: {
        promoquotaanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOQUOTAANZ_BES, PROMOQUOTAANZ_ANZ);
#else
        d = (promoquotaanzS *)spBuf;
#endif

        if ( (rc = Promoquotaanz_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOQUOTAANZ_BES, PROMOQUOTAANZ_ANZ );
#else
        {
            void * pUnused = PROMOQUOTAANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOQUOTAANZ_SELQUOTA: {
        promoquotaanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOQUOTAANZ_BES, PROMOQUOTAANZ_ANZ);
#else
        d = (promoquotaanzS *)spBuf;
#endif

        if ( (rc = Promoquotaanz_SelQuota(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOQUOTAANZ_BES, PROMOQUOTAANZ_ANZ );
#else
        {
            void * pUnused = PROMOQUOTAANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOQUOTAANZ_SELQUOTAPZN: {
        promoquotaanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOQUOTAANZ_BES, PROMOQUOTAANZ_ANZ);
#else
        d = (promoquotaanzS *)spBuf;
#endif

        if ( (rc = Promoquotaanz_SelQuotaPzn(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOQUOTAANZ_BES, PROMOQUOTAANZ_ANZ );
#else
        {
            void * pUnused = PROMOQUOTAANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOQUOTACHECK_SELQUOTA: {
        promoquotacheckS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOQUOTACHECK_BES, PROMOQUOTACHECK_ANZ);
#else
        d = (promoquotacheckS *)spBuf;
#endif

        if ( (rc = Promoquotacheck_SelQuota(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOQUOTACHECK_BES, PROMOQUOTACHECK_ANZ );
#else
        {
            void * pUnused = PROMOQUOTACHECK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOQUOTACSTANZ_SELLIST: {
        promoquotacstanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ);
#else
        d = (promoquotacstanzS *)spBuf;
#endif

        if ( (rc = Promoquotacstanz_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ );
#else
        {
            void * pUnused = PROMOQUOTACSTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOQUOTACSTANZ_SELLISTCST: {
        promoquotacstanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ);
#else
        d = (promoquotacstanzS *)spBuf;
#endif

        if ( (rc = Promoquotacstanz_SelListCst(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ );
#else
        {
            void * pUnused = PROMOQUOTACSTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOQUOTACSTANZ_SELLISTPROMO: {
        promoquotacstanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ);
#else
        d = (promoquotacstanzS *)spBuf;
#endif

        if ( (rc = Promoquotacstanz_SelListPromo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ );
#else
        {
            void * pUnused = PROMOQUOTACSTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case PROMOQUOTACSTANZ_SELQUOTA: {
        promoquotacstanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ);
#else
        d = (promoquotacstanzS *)spBuf;
#endif

        if ( (rc = Promoquotacstanz_SelQuota(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, PROMOQUOTACSTANZ_BES, PROMOQUOTACSTANZ_ANZ );
#else
        {
            void * pUnused = PROMOQUOTACSTANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case DISCOUNTGROUP_SELGROUP: {
        discountgroupS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, DISCOUNTGROUP_BES, DISCOUNTGROUP_ANZ);
#else
        d = (discountgroupS *)spBuf;
#endif

        if ( (rc = Discountgroup_Selgroup(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, DISCOUNTGROUP_BES, DISCOUNTGROUP_ANZ );
#else
        {
            void * pUnused = DISCOUNTGROUP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case RANGEMEMBERS_SELARTICLE: {
        rangemembersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, RANGEMEMBERS_BES, RANGEMEMBERS_ANZ);
#else
        d = (rangemembersS *)spBuf;
#endif

        if ( (rc = Rangemembers_SelArticle(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, RANGEMEMBERS_BES, RANGEMEMBERS_ANZ );
#else
        {
            void * pUnused = RANGEMEMBERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case RANGEMEMBERS_SELMANU: {
        rangemembersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, RANGEMEMBERS_BES, RANGEMEMBERS_ANZ);
#else
        d = (rangemembersS *)spBuf;
#endif

        if ( (rc = Rangemembers_SelManu(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, RANGEMEMBERS_BES, RANGEMEMBERS_ANZ );
#else
        {
            void * pUnused = RANGEMEMBERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SERVICEMEMBER_SELLIST: {
        servicememberS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SERVICEMEMBER_BES, SERVICEMEMBER_ANZ);
#else
        d = (servicememberS *)spBuf;
#endif

        if ( (rc = Servicemember_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SERVICEMEMBER_BES, SERVICEMEMBER_ANZ );
#else
        {
            void * pUnused = SERVICEMEMBER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SERVICEORDER_SELTYPE: {
        serviceorderS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SERVICEORDER_BES, SERVICEORDER_ANZ);
#else
        d = (serviceorderS *)spBuf;
#endif

        if ( (rc = Serviceorder_SelType(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SERVICEORDER_BES, SERVICEORDER_ANZ );
#else
        {
            void * pUnused = SERVICEORDER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTIKELKONTOANZ_SELLIST: {
        artikelkontoanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTIKELKONTOANZ_BES, ARTIKELKONTOANZ_ANZ);
#else
        d = (artikelkontoanzS *)spBuf;
#endif

        if ( (rc = Artikelkontoanz_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTIKELKONTOANZ_BES, ARTIKELKONTOANZ_ANZ );
#else
        {
            void * pUnused = ARTIKELKONTOANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case AUFWERTHERST_SELLIST: {
        aufwertherstS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, AUFWERTHERST_BES, AUFWERTHERST_ANZ);
#else
        d = (aufwertherstS *)spBuf;
#endif

        if ( (rc = Aufwertherst_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, AUFWERTHERST_BES, AUFWERTHERST_ANZ );
#else
        {
            void * pUnused = AUFWERTHERST_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FEIERTAG_SELALL: {
        feiertagS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FEIERTAG_BES, FEIERTAG_ANZ);
#else
        d = (feiertagS *)spBuf;
#endif

        if ( (rc = Feiertag_SelAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FEIERTAG_BES, FEIERTAG_ANZ );
#else
        {
            void * pUnused = FEIERTAG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FEIERTAG_INSERT: {
        feiertagS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FEIERTAG_BES, FEIERTAG_ANZ);
#else
        d = (feiertagS *)spBuf;
#endif

        if ( (rc = Feiertag_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FEIERTAG_BES, FEIERTAG_ANZ );
#else
        {
            void * pUnused = FEIERTAG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FEIERTAG_UPDATE: {
        feiertagS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FEIERTAG_BES, FEIERTAG_ANZ);
#else
        d = (feiertagS *)spBuf;
#endif

        if ( (rc = Feiertag_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FEIERTAG_BES, FEIERTAG_ANZ );
#else
        {
            void * pUnused = FEIERTAG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FEIERTAG_DELETE: {
        feiertagS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FEIERTAG_BES, FEIERTAG_ANZ);
#else
        d = (feiertagS *)spBuf;
#endif

        if ( (rc = Feiertag_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FEIERTAG_BES, FEIERTAG_ANZ );
#else
        {
            void * pUnused = FEIERTAG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case LAGERREVISIONANZ_SELLIST: {
        lagerrevisionanzS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, LAGERREVISIONANZ_BES, LAGERREVISIONANZ_ANZ);
#else
        d = (lagerrevisionanzS *)spBuf;
#endif

        if ( (rc = Lagerrevisionanz_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, LAGERREVISIONANZ_BES, LAGERREVISIONANZ_ANZ );
#else
        {
            void * pUnused = LAGERREVISIONANZ_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case OECUSTOMERCALLS_INSERT: {
        oecustomercallsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, OECUSTOMERCALLS_BES, OECUSTOMERCALLS_ANZ);
#else
        d = (oecustomercallsS *)spBuf;
#endif

        if ( (rc = Oecustomercalls_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, OECUSTOMERCALLS_BES, OECUSTOMERCALLS_ANZ );
#else
        {
            void * pUnused = OECUSTOMERCALLS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case OECUSTOMERCALLS_UPDATE: {
        oecustomercallsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, OECUSTOMERCALLS_BES, OECUSTOMERCALLS_ANZ);
#else
        d = (oecustomercallsS *)spBuf;
#endif

        if ( (rc = Oecustomercalls_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, OECUSTOMERCALLS_BES, OECUSTOMERCALLS_ANZ );
#else
        {
            void * pUnused = OECUSTOMERCALLS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case OFFENAUFTRAG_SELLIST: {
        offenauftragS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, OFFENAUFTRAG_BES, OFFENAUFTRAG_ANZ);
#else
        d = (offenauftragS *)spBuf;
#endif

        if ( (rc = Offenauftrag_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, OFFENAUFTRAG_BES, OFFENAUFTRAG_ANZ );
#else
        {
            void * pUnused = OFFENAUFTRAG_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case RUFSTAT_SEL_TAGSTAT: {
        rufstatS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, RUFSTAT_BES, RUFSTAT_ANZ);
#else
        d = (rufstatS *)spBuf;
#endif

        if ( (rc = Rufstat_Sel_Tagstat(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, RUFSTAT_BES, RUFSTAT_ANZ );
#else
        {
            void * pUnused = RUFSTAT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TOURZEIT_SELNEXTTOUR: {
        tourzeitS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TOURZEIT_BES, TOURZEIT_ANZ);
#else
        d = (tourzeitS *)spBuf;
#endif

        if ( (rc = Tourzeit_SelNextTour(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TOURZEIT_BES, TOURZEIT_ANZ );
#else
        {
            void * pUnused = TOURZEIT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TENDERARTICLE_SELART: {
        tenderarticleS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TENDERARTICLE_BES, TENDERARTICLE_ANZ);
#else
        d = (tenderarticleS *)spBuf;
#endif

        if ( (rc = Tenderarticle_SelArt(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TENDERARTICLE_BES, TENDERARTICLE_ANZ );
#else
        {
            void * pUnused = TENDERARTICLE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TENDERARTICLE_SELLIST: {
        tenderarticleS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TENDERARTICLE_BES, TENDERARTICLE_ANZ);
#else
        d = (tenderarticleS *)spBuf;
#endif

        if ( (rc = Tenderarticle_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TENDERARTICLE_BES, TENDERARTICLE_ANZ );
#else
        {
            void * pUnused = TENDERARTICLE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TENDERINFO_SELLIST: {
        tenderinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TENDERINFO_BES, TENDERINFO_ANZ);
#else
        d = (tenderinfoS *)spBuf;
#endif

        if ( (rc = Tenderinfo_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TENDERINFO_BES, TENDERINFO_ANZ );
#else
        {
            void * pUnused = TENDERINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TENDERINFO_SELLISTCHAIN: {
        tenderinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TENDERINFO_BES, TENDERINFO_ANZ);
#else
        d = (tenderinfoS *)spBuf;
#endif

        if ( (rc = Tenderinfo_SelListChain(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TENDERINFO_BES, TENDERINFO_ANZ );
#else
        {
            void * pUnused = TENDERINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TENDERINFO_SELLISTPOS: {
        tenderinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TENDERINFO_BES, TENDERINFO_ANZ);
#else
        d = (tenderinfoS *)spBuf;
#endif

        if ( (rc = Tenderinfo_SelListPos(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TENDERINFO_BES, TENDERINFO_ANZ );
#else
        {
            void * pUnused = TENDERINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TENDERINFO_SELLISTSTAAT: {
        tenderinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TENDERINFO_BES, TENDERINFO_ANZ);
#else
        d = (tenderinfoS *)spBuf;
#endif

        if ( (rc = Tenderinfo_SelListStaat(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TENDERINFO_BES, TENDERINFO_ANZ );
#else
        {
            void * pUnused = TENDERINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TENDERINFO_SELTENDER: {
        tenderinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TENDERINFO_BES, TENDERINFO_ANZ);
#else
        d = (tenderinfoS *)spBuf;
#endif

        if ( (rc = Tenderinfo_SelTender(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TENDERINFO_BES, TENDERINFO_ANZ );
#else
        {
            void * pUnused = TENDERINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TENDERSTOCK_SELQTY: {
        tenderstockS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TENDERSTOCK_BES, TENDERSTOCK_ANZ);
#else
        d = (tenderstockS *)spBuf;
#endif

        if ( (rc = Tenderstock_SelQty(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TENDERSTOCK_BES, TENDERSTOCK_ANZ );
#else
        {
            void * pUnused = TENDERSTOCK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SONDERTOUREN_SELLIST: {
        sondertourenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SONDERTOUREN_BES, SONDERTOUREN_ANZ);
#else
        d = (sondertourenS *)spBuf;
#endif

        if ( (rc = Sondertouren_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SONDERTOUREN_BES, SONDERTOUREN_ANZ );
#else
        {
            void * pUnused = SONDERTOUREN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SONDERTOUREN_INSERT: {
        sondertourenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SONDERTOUREN_BES, SONDERTOUREN_ANZ);
#else
        d = (sondertourenS *)spBuf;
#endif

        if ( (rc = Sondertouren_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SONDERTOUREN_BES, SONDERTOUREN_ANZ );
#else
        {
            void * pUnused = SONDERTOUREN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SONDERTOUREN_UPDATE: {
        sondertourenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SONDERTOUREN_BES, SONDERTOUREN_ANZ);
#else
        d = (sondertourenS *)spBuf;
#endif

        if ( (rc = Sondertouren_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SONDERTOUREN_BES, SONDERTOUREN_ANZ );
#else
        {
            void * pUnused = SONDERTOUREN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case SONDERTOUREN_DELETE: {
        sondertourenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, SONDERTOUREN_BES, SONDERTOUREN_ANZ);
#else
        d = (sondertourenS *)spBuf;
#endif

        if ( (rc = Sondertouren_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, SONDERTOUREN_BES, SONDERTOUREN_ANZ );
#else
        {
            void * pUnused = SONDERTOUREN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TOURPLANPFLEGE_SELLIST: {
        tourplanpflegeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TOURPLANPFLEGE_BES, TOURPLANPFLEGE_ANZ);
#else
        d = (tourplanpflegeS *)spBuf;
#endif

        if ( (rc = Tourplanpflege_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TOURPLANPFLEGE_BES, TOURPLANPFLEGE_ANZ );
#else
        {
            void * pUnused = TOURPLANPFLEGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TOURPLANPFLEGE_SELTOUR: {
        tourplanpflegeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TOURPLANPFLEGE_BES, TOURPLANPFLEGE_ANZ);
#else
        d = (tourplanpflegeS *)spBuf;
#endif

        if ( (rc = Tourplanpflege_SelTour(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TOURPLANPFLEGE_BES, TOURPLANPFLEGE_ANZ );
#else
        {
            void * pUnused = TOURPLANPFLEGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TOURPLANPFLEGE_UPDATE: {
        tourplanpflegeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TOURPLANPFLEGE_BES, TOURPLANPFLEGE_ANZ);
#else
        d = (tourplanpflegeS *)spBuf;
#endif

        if ( (rc = Tourplanpflege_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TOURPLANPFLEGE_BES, TOURPLANPFLEGE_ANZ );
#else
        {
            void * pUnused = TOURPLANPFLEGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TOURSPERRE_SELLIST: {
        toursperreS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TOURSPERRE_BES, TOURSPERRE_ANZ);
#else
        d = (toursperreS *)spBuf;
#endif

        if ( (rc = Toursperre_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TOURSPERRE_BES, TOURSPERRE_ANZ );
#else
        {
            void * pUnused = TOURSPERRE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case TOURSPERRE_UPDATE: {
        toursperreS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, TOURSPERRE_BES, TOURSPERRE_ANZ);
#else
        d = (toursperreS *)spBuf;
#endif

        if ( (rc = Toursperre_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, TOURSPERRE_BES, TOURSPERRE_ANZ );
#else
        {
            void * pUnused = TOURSPERRE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTSTOCK_SELLIST: {
        artstockS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTSTOCK_BES, ARTSTOCK_ANZ);
#else
        d = (artstockS *)spBuf;
#endif

        if ( (rc = Artstock_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTSTOCK_BES, ARTSTOCK_ANZ );
#else
        {
            void * pUnused = ARTSTOCK_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKIBTDONE_ISIBTDONE: {
        checkibtdoneS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKIBTDONE_BES, CHECKIBTDONE_ANZ);
#else
        d = (checkibtdoneS *)spBuf;
#endif

        if ( (rc = Checkibtdone_IsIBTDone(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKIBTDONE_BES, CHECKIBTDONE_ANZ );
#else
        {
            void * pUnused = CHECKIBTDONE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case CHECKIBTDONE_SELIBTDONEORDER: {
        checkibtdoneS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, CHECKIBTDONE_BES, CHECKIBTDONE_ANZ);
#else
        d = (checkibtdoneS *)spBuf;
#endif

        if ( (rc = Checkibtdone_SelIBTDoneOrder(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, CHECKIBTDONE_BES, CHECKIBTDONE_ANZ );
#else
        {
            void * pUnused = CHECKIBTDONE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case VERBUNDMOEGL_SELVBBESTANDNEU: {
        verbundmoeglS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, VERBUNDMOEGL_BES, VERBUNDMOEGL_ANZ);
#else
        d = (verbundmoeglS *)spBuf;
#endif

        if ( (rc = Verbundmoegl_SelVbBestandNeu(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, VERBUNDMOEGL_BES, VERBUNDMOEGL_ANZ );
#else
        {
            void * pUnused = VERBUNDMOEGL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case VERBUNDMOEGL_SELVBBESTANDTM: {
        verbundmoeglS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, VERBUNDMOEGL_BES, VERBUNDMOEGL_ANZ);
#else
        d = (verbundmoeglS *)spBuf;
#endif

        if ( (rc = Verbundmoegl_SelVbBestandTM(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, VERBUNDMOEGL_BES, VERBUNDMOEGL_ANZ );
#else
        {
            void * pUnused = VERBUNDMOEGL_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ARTICLENLEVELIBTTYPE_SELLIST: {
        articlenlevelibttypeS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ARTICLENLEVELIBTTYPE_BES, ARTICLENLEVELIBTTYPE_ANZ);
#else
        d = (articlenlevelibttypeS *)spBuf;
#endif

        if ( (rc = articlenlevelibttype_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ARTICLENLEVELIBTTYPE_BES, ARTICLENLEVELIBTTYPE_ANZ );
#else
        {
            void * pUnused = ARTICLENLEVELIBTTYPE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case BACKROUT_SELLIST: {
        backroutS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, BACKROUT_BES, BACKROUT_ANZ);
#else
        d = (backroutS *)spBuf;
#endif

        if ( (rc = Backrout_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, BACKROUT_BES, BACKROUT_ANZ );
#else
        {
            void * pUnused = BACKROUT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case BACKROUT_INSERT: {
        backroutS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, BACKROUT_BES, BACKROUT_ANZ);
#else
        d = (backroutS *)spBuf;
#endif

        if ( (rc = Backrout_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, BACKROUT_BES, BACKROUT_ANZ );
#else
        {
            void * pUnused = BACKROUT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case BACKROUT_DELETE: {
        backroutS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, BACKROUT_BES, BACKROUT_ANZ);
#else
        d = (backroutS *)spBuf;
#endif

        if ( (rc = Backrout_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, BACKROUT_BES, BACKROUT_ANZ );
#else
        {
            void * pUnused = BACKROUT_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case BRANCHINFO_SELINFO: {
        branchinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, BRANCHINFO_BES, BRANCHINFO_ANZ);
#else
        d = (branchinfoS *)spBuf;
#endif

        if ( (rc = Branchinfo_SelInfo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, BRANCHINFO_BES, BRANCHINFO_ANZ );
#else
        {
            void * pUnused = BRANCHINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case BRANCHINFO_INSERT: {
        branchinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, BRANCHINFO_BES, BRANCHINFO_ANZ);
#else
        d = (branchinfoS *)spBuf;
#endif

        if ( (rc = Branchinfo_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, BRANCHINFO_BES, BRANCHINFO_ANZ );
#else
        {
            void * pUnused = BRANCHINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case BRANCHINFO_UPDATE: {
        branchinfoS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, BRANCHINFO_BES, BRANCHINFO_ANZ);
#else
        d = (branchinfoS *)spBuf;
#endif

        if ( (rc = Branchinfo_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, BRANCHINFO_BES, BRANCHINFO_ANZ );
#else
        {
            void * pUnused = BRANCHINFO_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case BRANCHNAMES_SELLIST: {
        branchnamesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, BRANCHNAMES_BES, BRANCHNAMES_ANZ);
#else
        d = (branchnamesS *)spBuf;
#endif

        if ( (rc = Branchnames_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, BRANCHNAMES_BES, BRANCHNAMES_ANZ );
#else
        {
            void * pUnused = BRANCHNAMES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case IBTBRANCHESADMIN_SELLIST: {
        ibtbranchesadminS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ);
#else
        d = (ibtbranchesadminS *)spBuf;
#endif

        if ( (rc = Ibtbranchesadmin_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ );
#else
        {
            void * pUnused = IBTBRANCHESADMIN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case IBTBRANCHESADMIN_INSERT: {
        ibtbranchesadminS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ);
#else
        d = (ibtbranchesadminS *)spBuf;
#endif

        if ( (rc = Ibtbranchesadmin_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ );
#else
        {
            void * pUnused = IBTBRANCHESADMIN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case IBTBRANCHESADMIN_UPDATE: {
        ibtbranchesadminS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ);
#else
        d = (ibtbranchesadminS *)spBuf;
#endif

        if ( (rc = Ibtbranchesadmin_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ );
#else
        {
            void * pUnused = IBTBRANCHESADMIN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case IBTBRANCHESADMIN_DELETE: {
        ibtbranchesadminS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ);
#else
        d = (ibtbranchesadminS *)spBuf;
#endif

        if ( (rc = Ibtbranchesadmin_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, IBTBRANCHESADMIN_BES, IBTBRANCHESADMIN_ANZ );
#else
        {
            void * pUnused = IBTBRANCHESADMIN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case NLEVELIBTBRANCHES_SELIBTBRANCHES: {
        nlevelibtbranchesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, NLEVELIBTBRANCHES_BES, NLEVELIBTBRANCHES_ANZ);
#else
        d = (nlevelibtbranchesS *)spBuf;
#endif

        if ( (rc = Nlevelibtbranches_SelIBTBranches(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, NLEVELIBTBRANCHES_BES, NLEVELIBTBRANCHES_ANZ );
#else
        {
            void * pUnused = NLEVELIBTBRANCHES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case REGIONBRANCHES_SELLIST: {
        regionbranchesS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, REGIONBRANCHES_BES, REGIONBRANCHES_ANZ);
#else
        d = (regionbranchesS *)spBuf;
#endif

        if ( (rc = Regionbranches_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, REGIONBRANCHES_BES, REGIONBRANCHES_ANZ );
#else
        {
            void * pUnused = REGIONBRANCHES_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case REGIONS_SELREGION: {
        regionsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, REGIONS_BES, REGIONS_ANZ);
#else
        d = (regionsS *)spBuf;
#endif

        if ( (rc = Regions_SelRegion(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, REGIONS_BES, REGIONS_ANZ );
#else
        {
            void * pUnused = REGIONS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case VBFILIALEN_SELVBFILIALEN: {
        vbfilialenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, VBFILIALEN_BES, VBFILIALEN_ANZ);
#else
        d = (vbfilialenS *)spBuf;
#endif

        if ( (rc = Vbfilialen_SelVbFilialen(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, VBFILIALEN_BES, VBFILIALEN_ANZ );
#else
        {
            void * pUnused = VBFILIALEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case VERBUNDIDF_SELVBIDF: {
        verbundidfS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, VERBUNDIDF_BES, VERBUNDIDF_ANZ);
#else
        d = (verbundidfS *)spBuf;
#endif

        if ( (rc = Verbundidf_SelVBIdf(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, VERBUNDIDF_BES, VERBUNDIDF_ANZ );
#else
        {
            void * pUnused = VERBUNDIDF_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case ZIELFILIALEN_SELLIST: {
        zielfilialenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, ZIELFILIALEN_BES, ZIELFILIALEN_ANZ);
#else
        d = (zielfilialenS *)spBuf;
#endif

        if ( (rc = Zielfilialen_SelList(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, ZIELFILIALEN_BES, ZIELFILIALEN_ANZ );
#else
        {
            void * pUnused = ZIELFILIALEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FILIALPARTNER_SEL: {
        filialpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FILIALPARTNER_BES, FILIALPARTNER_ANZ);
#else
        d = (filialpartnerS *)spBuf;
#endif

        if ( (rc = filialpartner_Sel(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FILIALPARTNER_BES, FILIALPARTNER_ANZ );
#else
        {
            void * pUnused = FILIALPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FILIALPARTNER_SELSUPPORTTIME: {
        filialpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FILIALPARTNER_BES, FILIALPARTNER_ANZ);
#else
        d = (filialpartnerS *)spBuf;
#endif

        if ( (rc = filialpartner_SelSupportTime(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FILIALPARTNER_BES, FILIALPARTNER_ANZ );
#else
        {
            void * pUnused = FILIALPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FILIALPARTNER_INSERT: {
        filialpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FILIALPARTNER_BES, FILIALPARTNER_ANZ);
#else
        d = (filialpartnerS *)spBuf;
#endif

        if ( (rc = filialpartner_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FILIALPARTNER_BES, FILIALPARTNER_ANZ );
#else
        {
            void * pUnused = FILIALPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FILIALPARTNER_UPDATE: {
        filialpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FILIALPARTNER_BES, FILIALPARTNER_ANZ);
#else
        d = (filialpartnerS *)spBuf;
#endif

        if ( (rc = filialpartner_Update(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FILIALPARTNER_BES, FILIALPARTNER_ANZ );
#else
        {
            void * pUnused = FILIALPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FILIALPARTNER_DELETE: {
        filialpartnerS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FILIALPARTNER_BES, FILIALPARTNER_ANZ);
#else
        d = (filialpartnerS *)spBuf;
#endif

        if ( (rc = filialpartner_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FILIALPARTNER_BES, FILIALPARTNER_ANZ );
#else
        {
            void * pUnused = FILIALPARTNER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FILIALZEITEN_SELZEITEN: {
        filialzeitenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FILIALZEITEN_BES, FILIALZEITEN_ANZ);
#else
        d = (filialzeitenS *)spBuf;
#endif

        if ( (rc = filialzeiten_SelZeiten(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FILIALZEITEN_BES, FILIALZEITEN_ANZ );
#else
        {
            void * pUnused = FILIALZEITEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case FILIALZEITEN_UPDATEZEITEN: {
        filialzeitenS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, FILIALZEITEN_BES, FILIALZEITEN_ANZ);
#else
        d = (filialzeitenS *)spBuf;
#endif

        if ( (rc = filialzeiten_UpdateZeiten(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, FILIALZEITEN_BES, FILIALZEITEN_ANZ );
#else
        {
            void * pUnused = FILIALZEITEN_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILDEFINEDUSER_SELALLUSER: {
        maildefineduserS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILDEFINEDUSER_BES, MAILDEFINEDUSER_ANZ);
#else
        d = (maildefineduserS *)spBuf;
#endif

        if ( (rc = Maildefineduser_SelAllUser(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILDEFINEDUSER_BES, MAILDEFINEDUSER_ANZ );
#else
        {
            void * pUnused = MAILDEFINEDUSER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILDEFINEDUSER_SELALLUSERVZ: {
        maildefineduserS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILDEFINEDUSER_BES, MAILDEFINEDUSER_ANZ);
#else
        d = (maildefineduserS *)spBuf;
#endif

        if ( (rc = Maildefineduser_SelAllUserVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILDEFINEDUSER_BES, MAILDEFINEDUSER_ANZ );
#else
        {
            void * pUnused = MAILDEFINEDUSER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILDEFINEDUSER_SELOPENMAIL: {
        maildefineduserS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILDEFINEDUSER_BES, MAILDEFINEDUSER_ANZ);
#else
        d = (maildefineduserS *)spBuf;
#endif

        if ( (rc = Maildefineduser_SelOpenMail(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILDEFINEDUSER_BES, MAILDEFINEDUSER_ANZ );
#else
        {
            void * pUnused = MAILDEFINEDUSER_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case USERINFORMATION_CHECKFREE: {
        userinformationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, USERINFORMATION_BES, USERINFORMATION_ANZ);
#else
        d = (userinformationS *)spBuf;
#endif

        if ( (rc = Userinformation_CheckFree(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, USERINFORMATION_BES, USERINFORMATION_ANZ );
#else
        {
            void * pUnused = USERINFORMATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case USERINFORMATION_SELINFO: {
        userinformationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, USERINFORMATION_BES, USERINFORMATION_ANZ);
#else
        d = (userinformationS *)spBuf;
#endif

        if ( (rc = Userinformation_SelInfo(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, USERINFORMATION_BES, USERINFORMATION_ANZ );
#else
        {
            void * pUnused = USERINFORMATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case USERINFORMATION_INSERT: {
        userinformationS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, USERINFORMATION_BES, USERINFORMATION_ANZ);
#else
        d = (userinformationS *)spBuf;
#endif

        if ( (rc = Userinformation_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, USERINFORMATION_BES, USERINFORMATION_ANZ );
#else
        {
            void * pUnused = USERINFORMATION_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILGROUP_SELMAILGROUP: {
        mailgroupS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILGROUP_BES, MAILGROUP_ANZ);
#else
        d = (mailgroupS *)spBuf;
#endif

        if ( (rc = mailgroup_SelMailGroup(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILGROUP_BES, MAILGROUP_ANZ );
#else
        {
            void * pUnused = MAILGROUP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILGROUP_SELMAILGROUPVZ: {
        mailgroupS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILGROUP_BES, MAILGROUP_ANZ);
#else
        d = (mailgroupS *)spBuf;
#endif

        if ( (rc = mailgroup_SelMailGroupVz(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILGROUP_BES, MAILGROUP_ANZ );
#else
        {
            void * pUnused = MAILGROUP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILGROUP_INSERT: {
        mailgroupS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILGROUP_BES, MAILGROUP_ANZ);
#else
        d = (mailgroupS *)spBuf;
#endif

        if ( (rc = mailgroup_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILGROUP_BES, MAILGROUP_ANZ );
#else
        {
            void * pUnused = MAILGROUP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILGROUP_UPDATEMAILGROUP: {
        mailgroupS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILGROUP_BES, MAILGROUP_ANZ);
#else
        d = (mailgroupS *)spBuf;
#endif

        if ( (rc = mailgroup_UpdateMailGroup(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILGROUP_BES, MAILGROUP_ANZ );
#else
        {
            void * pUnused = MAILGROUP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILGROUP_DELETEMAILGROUP: {
        mailgroupS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILGROUP_BES, MAILGROUP_ANZ);
#else
        d = (mailgroupS *)spBuf;
#endif

        if ( (rc = mailgroup_DeleteMailGroup(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILGROUP_BES, MAILGROUP_ANZ );
#else
        {
            void * pUnused = MAILGROUP_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILITEMS_SELOPENNEWS: {
        mailitemsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILITEMS_BES, MAILITEMS_ANZ);
#else
        d = (mailitemsS *)spBuf;
#endif

        if ( (rc = mailitems_SelOpenNews(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILITEMS_BES, MAILITEMS_ANZ );
#else
        {
            void * pUnused = MAILITEMS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILITEMS_INSERT: {
        mailitemsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILITEMS_BES, MAILITEMS_ANZ);
#else
        d = (mailitemsS *)spBuf;
#endif

        if ( (rc = mailitems_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILITEMS_BES, MAILITEMS_ANZ );
#else
        {
            void * pUnused = MAILITEMS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILITEMS_DELETEMESSAGE: {
        mailitemsS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILITEMS_BES, MAILITEMS_ANZ);
#else
        d = (mailitemsS *)spBuf;
#endif

        if ( (rc = mailitems_DeleteMessage(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILITEMS_BES, MAILITEMS_ANZ );
#else
        {
            void * pUnused = MAILITEMS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILMESSAGE_SELMAILMESSAGE: {
        mailmessageS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILMESSAGE_BES, MAILMESSAGE_ANZ);
#else
        d = (mailmessageS *)spBuf;
#endif

        if ( (rc = mailmessage_SelMailMessage(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILMESSAGE_BES, MAILMESSAGE_ANZ );
#else
        {
            void * pUnused = MAILMESSAGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILMESSAGE_INSERT: {
        mailmessageS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILMESSAGE_BES, MAILMESSAGE_ANZ);
#else
        d = (mailmessageS *)spBuf;
#endif

        if ( (rc = mailmessage_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILMESSAGE_BES, MAILMESSAGE_ANZ );
#else
        {
            void * pUnused = MAILMESSAGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILMESSAGE_SELALLMESSAGE: {
        mailmessageS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILMESSAGE_BES, MAILMESSAGE_ANZ);
#else
        d = (mailmessageS *)spBuf;
#endif

        if ( (rc = mailmessage_SelAllMessage(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILMESSAGE_BES, MAILMESSAGE_ANZ );
#else
        {
            void * pUnused = MAILMESSAGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILMESSAGE_SELNOTREAD: {
        mailmessageS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILMESSAGE_BES, MAILMESSAGE_ANZ);
#else
        d = (mailmessageS *)spBuf;
#endif

        if ( (rc = mailmessage_SelNotRead(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILMESSAGE_BES, MAILMESSAGE_ANZ );
#else
        {
            void * pUnused = MAILMESSAGE_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILUSERS_SELALL: {
        mailusersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILUSERS_BES, MAILUSERS_ANZ);
#else
        d = (mailusersS *)spBuf;
#endif

        if ( (rc = mailusers_SelAll(d, &tErrorMsg, false) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILUSERS_BES, MAILUSERS_ANZ );
#else
        {
            void * pUnused = MAILUSERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILUSERS_INSERT: {
        mailusersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILUSERS_BES, MAILUSERS_ANZ);
#else
        d = (mailusersS *)spBuf;
#endif

        if ( (rc = mailusers_Insert(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILUSERS_BES, MAILUSERS_ANZ );
#else
        {
            void * pUnused = MAILUSERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILUSERS_DELETE: {
        mailusersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILUSERS_BES, MAILUSERS_ANZ);
#else
        d = (mailusersS *)spBuf;
#endif

        if ( (rc = mailusers_Delete(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILUSERS_BES, MAILUSERS_ANZ );
#else
        {
            void * pUnused = MAILUSERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILUSERS_DELETEALL: {
        mailusersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILUSERS_BES, MAILUSERS_ANZ);
#else
        d = (mailusersS *)spBuf;
#endif

        if ( (rc = mailusers_DeleteAll(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILUSERS_BES, MAILUSERS_ANZ );
#else
        {
            void * pUnused = MAILUSERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
    case MAILUSERS_DELETEALLVZ: {
        mailusersS s, * d;
        d = &s;

#ifndef __DADE_LOAD__
        buf_kon(FROM_UEB, (char *)d, spIn, MAILUSERS_BES, MAILUSERS_ANZ);
#else
        d = (mailusersS *)spBuf;
#endif

        if ( (rc = mailusers_DeleteAllVz(d, &tErrorMsg, true) ) < 0)
        {
            *ipLen = (int)strlen(tErrorMsg.spError) + 1;
            strcpy(spOut, tErrorMsg.spError);
            return rc;
        }

#ifndef __DADE_LOAD__
        *ipLen = buf_kon(TO_UEB, (char *)d, spOut, MAILUSERS_BES, MAILUSERS_ANZ );
#else
        {
            void * pUnused = MAILUSERS_BES;
            pUnused = pUnused;
        }
#endif
        return rc;
    }
/* _SWITCH__ */
    default:
        sprintf(spOut, "DistributorFunPublic: %d", iFunNo);
        *ipLen = (int)strlen(spOut) + 1;
        return -1;
    }
}
