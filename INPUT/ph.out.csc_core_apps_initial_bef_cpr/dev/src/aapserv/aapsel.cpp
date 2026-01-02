#define BUF_DESC
#define COMMITTED   1
#define DIRTY       0

void    FehlerBehandlung(int rc, char* error_msg);
int     Server(int FktNr, void* stru, struct buf_desc bd[], int anz, char* error_msg);

#include <stdio.h>
#include <stdlib.h>
#include "fscincl.h"
#include "bufkon.h"
#include "aarufpl.h"
#include "kndsel.h"
#include "artsel.h"
#include "param.h"
#include "aepwd.h"
#include "articleomg.h"
#include "auftrag.h"
#include "filinf.h"
#include "lieferinfo.h"
#include "passwd.h"     /* nase iftsel spaeter entfernen */
#include "telview.h"
#include "koplist.h"
#include "aatour.h"
#include "alterfil.h"
#include "zeitart.h"
#include "usertexte.h"
#include "seralog.h"
#include "lockview.h"
#include "nachlief.h"
#include "nachlart.h"
#include "nachlprot.h"
#include "druckpara.h"
#include <string.h>
#include "kritiksatz.h"
#include <memory.h>
#include "tm.h"
#include "vblief.h"
#include "vbbuch.h"
#include "vbcount.h"
#include "controlling.h"
#include "tender.h"
#include "ordervalues.h"
#include "rabattorder.h"
#include "artikel.h"
#include "rebateprice.h"
#include "invoicesettings.h"
#include "customer.h"
#include "auftraginfo.h"
#include "rangelist.h"
#include "sendmail.h"
#include "pxsess.hpp"
#include "pxstockbooking.hpp"
#include "pxartbas.hpp"
#include "taufartk.h"
#include "verbundcheck.h"
#include <map>
#include "callbackmaillink.h"
#include "fcorderssel.h"
#include "cscreservationtypes.h"
#include "ordertypereservationconfig.h"
#include "ordertypereservationconfigcpg.h"
#include "cscorderimportcsvformats.h"
#include "cscorderimportcsvcolumns.h"
#include "cscorderimportfields.h"
#include "cscorderimportcsvfile.h"
#include "auftragsart.h"
#include "tourdelay.h"
#include "parameter_change_logging.h"
#include "parameter_change_log_defs.h"
#include <deliveryadvicehead.h>
#include <deliveryadviceline.h>
#include <deliveryadvicelinedetails.h>
#include <deliveryadvicelinediscounts.h>
#include <deliveryadvicelineibtlink.h>
#include <deliveryadvicelinereturn.h>
#include <deliveryadviceremark.h>
#include <deliveryadvicevattotals.h>
#include <deliveryadvicedocument.h>

/*** DEFINE/CONST ************************************************************/
/*--- Dade-functions start with 1000! */
#ifdef __ONLY_DISTRIBUTE__
static const int DADE_FUNCTION_NO = 1000;
#endif /*__ONLY_DISTRIBUTE__*/



extern "C" {
/* PROTOTYPES */
int AafilSelLogParameterDefinitions(parameter_change_log_defsS* d, char* error_msg);
int AafilSelLogParameter(parameter_change_loggingS* d, char* error_msg);
int AafilLogParameter(char* Tabelle, struct PARAUFBEARB* d, struct PARAUFBEARB* old, char* error_msg);
int AatartAa_select(struct ARTAESEL* vez, char* error_msg);
int AaauftSelList_FCOrdersToSolve(fcordersselS* vez, char* error_msg);
int AaauftSelList_FCOrdersToClose(fcordersselS* vez, char* error_msg);
int AaauftSelList_FCOrdersAll(fcordersselS* vez, char* error_msg);
int AaauftSelList_Auftrag(struct AUSTINF* vez, char* error_msg);
int AafilGet_filiale_Procenter(struct FILINF* vez, char* error_msg);
int AaauftSelzurauft_o_sortfield(struct AUSTINF* vez, char* error_msg);
int AaauftSelzurauft_o_branch(struct AUSTINF* vez, char* error_msg);
int AaauftSelProLink(struct AUSTINF* vez, char* error_msg);
int AafilSel_zeit_heute(struct ZEITARTV* vez, char* error_msg);
int AatartSel_NoByCode(struct ARTAESEL* d, char* error_msg);
int AatartSel_Preferred(struct ARTAESEL* d, char* error_msg);
int AaauftSelzurauft_o_pos(struct AUSTINF* vez, char* error_msg);
int AaauftSelzurauft_o_kdklasse(struct AUSTINF* vez, char* error_msg);
int AadruckNachl_liefer(struct DRUCKPARA* vez, char* error_msg);
int AaauftSelzurauftDD(struct AUSTINF* vez, char* error_msg);
int AakundeSel_knd_info_hipath(struct KNDINF* vez, char* error_msg);
int AatartSel_ean(struct ARTSEL* vez, char* error_msg);
int AakundeSel_name(struct KNDSEL* vez, char* error_msg);
int AaauftSel_valutatage(struct AUFARTES* vez, char* error_msg);
int AafilSet_sprache(lgtextS* vez, char* error_msg);
int AakundeSel_telnr(struct KNDINF* vez, char* error_msg);
int AatartFetch_artnrlief(struct ARTSEL* vez, char* error_msg);
int AaauftSelzurauft_o_aart(struct AUSTINF* vez, char* error_msg);
int AaauftCheck_auftnr(struct AUFIE* vez, char* error_msg);
int AaauftSel_fili_auft_nr(struct AUSTINF* vez, char* error_msg);
int AakundeSel_nachttouren(kndtourenS* vez, char* error_msg);
int AadruckMasterplan(struct DRUCKPARA* vez, char* error_msg);
int AakundeSel_idf(struct KNDSEL* vez, char* error_msg);
int AafilSet_actualfiliale(struct FILINF* d, char* error_msg);
int AadruckNachl_vbmoegl(struct DRUCKPARA* vez, char* error_msg);
int AafilChecktour(struct PARKABAKOMB* vez, char* error_msg);
int AaauftSelzurauftpzn(struct AUSTINF* vez, char* error_msg);
int AaauftSel_kndnlprio(struct NACHLIEF* vez, char* error_msg);
int AaauftSel_valutaauto(struct AUFARTES* vez, char* error_msg);
int AaauftSperr_auft(struct AUFIE* vez, char* error_msg);
int AaauftSel_defekte(struct N_VBBUCH* vez, char* error_msg);
int AaauftSel_vbcount(struct VBCOUNT* vez, char* error_msg);
int Aaauft_Sel_vbmoegl(struct N_VBBUCH* vez, char* error_msg);
int Aaauft_Sel_vblief(struct VBLIEF* vez, char* error_msg);
int AaauftIns_nachl(struct NACHLIEF* vez, char* error_msg);
int AatartSel_folge(struct ARTFOLGE* vez, char* error_msg);
int AaauftSel_lauftnr(struct AUFLAGER* vez, char* error_msg);
int AadruckNachl(struct DRUCKPARA* vez, char* error_msg);
int AaauftSel_lager_auft_nr(struct AUSTINF* vez, char* error_msg);
int AatartSel_artlief(struct ARTLIEFER* vez, char* error_msg);
int AaauftSel_tub_pos(struct AUFWANNEN* vez, char* error_msg);
int AakundeSel_monums(struct KNDMONUMS* vez, char* error_msg);
int AafilIs_new_order_possi(struct AUFIE* vez, char* error_msg);
int AakundeDel_aufart(struct KNDAUFART* vez, char* error_msg);
int AakundeIns_aufart(struct KNDAUFART* vez, char* error_msg);
int AaauftGetfirstordertime(struct AUSTINF* vez, char* error_msg);
int AafilIns_auftrendzeit(struct PARAUFTRENDZEIT* vez, char* error_msg);
int AafilDel_auftrendzeit(struct PARAUFTRENDZEIT* vez, char* error_msg);
int AafilSel_auftrendzeit(struct PARAUFTRENDZEIT* vez, char* error_msg);
int AaauftGet_prot_nl(struct NACHLPROTV* vez, char* error_msg);
int AaauftIns_prot(struct NACHLPROT* vez, char* error_msg);
int AaauftSel_end_art(struct AUFENDART* vez, char* error_msg);
int AaauftSel_art_pos(struct AUFENDPOS* vez, char* error_msg);
int AaauftSel_ean_uni(struct AUFEAN* vez, char* error_msg);
int AaauftSel_kndnl(struct NACHLIEF* vez, char* error_msg);
int AaauftSel_end_pos(struct AUFENDPOS* vez, char* error_msg);
int AaauftSel_end_kopf(struct AUFENDKOPF* vez, char* error_msg);
int AaauftSel_frt(struct AUFPOSBUCH* vez, char* error_msg);
int AaauftSel_nachlart(struct NACHLART* vez, char* error_msg);
int AafilSel_verbund(struct ZEITARTV* vez, char* error_msg);
int AatartSel_lagerbest(struct ARTLAGER* vez, char* error_msg);
int AaauftIns_auft_ereig(struct AUFEREIG* vez, char* error_msg);
int AaauftStatplan_sel(struct AUFSTPLAN* vez, char* error_msg);
int AaplanVor_sel_ins(struct RUFPTAGVOR* vez, char* error_msg);
int AaplanVor_sel_upd(struct RUFPTAGVOR* vez, char* error_msg);
int AaplanVor_sel_uni(struct RUFPTAGVOR* vez, char* error_msg);
int AafilSel_aa_passwd(struct AEPWD* vez, char* error_msg);
int AaplanSel_tour(struct RUFPTAGTOUR* vez, char* error_msg);
int AaplanSel_count(struct RUFPTAGSUM* vez, char* error_msg);
int AaauftUpd_nachl(struct NACHLIEF* vez, char* error_msg);
int AaauftLoe_nachl(struct NACHLIEF* vez, char* error_msg);
int AaauftSel_nachl(struct NACHLIEF* vez, char* error_msg);
int AakundeSel_kndschalter(struct KNDSCHALTER* vez, char* error_msg);
int AaauftSel_alt_pos(struct AUFPOSBUCH* vez, char* error_msg);
int AaauftSel_alt_auft(struct AUFTRAG* vez, char* error_msg);
int AaauftSel_alt_kopf(struct AUFTEXTE* vez, char* error_msg);
int AaplanUni_tag_plan(struct RUFPTAG* vez, char* error_msg);
int AaplanSel_tag_plan_inf(struct RUFPTAGINF* vez, char* error_msg);
int AafilDel_usertext(struct USERTEXTV* vez, char* error_msg);
int AafilIns_usertext(struct USERTEXTV* vez, char* error_msg);
int AafilSel_usertext(struct USERTEXTV* vez, char* error_msg);
int AatartAa_sel_index(struct ARTAESEL* vez, char* error_msg);
int AatartSel_offene_bstlng(struct ARTINFBESTEL* vez, char* error_msg);
int AatartSel_hersteller(struct ARTINFHERSTE* vez, char* error_msg);
int AaplanUpd_tag_plan(struct RUFPTAG* vez, char* error_msg);
int AaplanIns_tag_plan(struct RUFPTAG* vez, char* error_msg);
int AaseraLes_data(struct SERALOGD* vez, char* error_msg);
int AaseraLes_dir(struct SERALOGH* vez, char* error_msg);
int AafilDel_zeitart(struct ZEITARTV* vez, char* error_msg);
int AafilDel_altfil(struct N_ALTFIL* vez, char* error_msg);
int AafilIns_zeitarten(struct ZEITARTV* vez, char* error_msg);
int AafilUpd_zeitarten(struct ZEITARTV* vez, char* error_msg);
int AafilSel_zeitarten(struct ZEITARTV* vez, char* error_msg);
int AafilIns_altfil(struct N_ALTFIL* vez, char* error_msg);
int AafilUpd_altfil(struct N_ALTFIL* vez, char* error_msg);
int AafilSel_altfil(struct N_ALTFIL* vez, char* error_msg);
int AaplanSel_tag_plan(struct RUFPTAG* vez, char* error_msg);
int AakritikSelect_pos(kritikposS* vez, char* error_msg);
int AakritikSchreibe_pos(kritikposS* vez, char* error_msg);
int AakritikSchreibe_kopf(kritikkopfS* vez, char* error_msg);
int AakritikSel_kritik_idf(kritikS* vez, char* error_msg);
int AakritikSel_kritik(kritikS* vez, char* error_msg);
int AatourGet_tour_kopf(struct TOURUEBERS* vez, char* error_msg);
int AatourUpd_folgenr(struct TOURINHALT* vez, char* error_msg);
int AatourUpd_auf_tour(struct TOURINHALT* vez, char* error_msg);
int AatourUpd_sond_wann(struct TOURINHALT* vez, char* error_msg);
int AatourSel_auf_tour(struct TOURINHALT* vez, char* error_msg);
int AatourSel_tour_uebers(struct TOURUEBERS* vez, char* error_msg);
int AaauftZeilenstatistik(struct AUFZLNSTAT* vez, char* error_msg);
int AaauftStatusae(struct AUFSTATUS* vez, char* error_msg);
int IftselSel_suchbez(struct VTELARTAK* vez, char* error_msg);
int IftselVers_kontr(struct PASSWD* vez, char* error_msg);
int IftselSel_tellistt(struct KOPLIST* a, char* error_msg);
int IftselUpd_tellistt(struct KOPLIST* a, char* error_msg);
int IftselIns_tellistt(struct KOPLIST* a, char* error_msg);
int IftselDel_tellistt(struct KOPLIST* a, char* error_msg);
int IftselSel_info(struct KOPLIST* a, char* error_msg);
int AaauftAusg_auft_ereig(struct AUFEREIG* vez, char* error_msg);
int AaplanSel_mplan_idf(struct RUFPMASTER* vez, char* error_msg);
int AaauftAnz_zur_geraet(struct AUSTINF* vez, char* error_msg);
int AaauftAnz_zur_knd(struct AUSTINF* vez, char* error_msg);
int AaauftSelzurauftknde(struct AUSTINF* vez, char* error_msg);
int AaauftSelzurauft_o_ende(struct AUSTINF* vez, char* error_msg);
int AaauftSelzurauft_o_idf(struct AUSTINF* vez, char* error_msg);
int AaauftSelzurauft_o_tour(struct AUSTINF* vez, char* error_msg);
int AaauftSelzurauft(struct AUSTINF* vez, char* error_msg);
int AafilInspasswd(struct AEPWD* vez, char* error_msg);
int AafilGetversion(struct PARVERSION* vez, char* error_msg);
int AafilUpdpasswd(struct AEPWD* vez, char* error_msg);
int AafilDelkommi(struct PARKOMMI* vez, char* error_msg);
int AafilInskommi(struct PARKOMMI* vez, char* error_msg);
int AafilUpdkommi(struct PARKOMMI* vez, char* error_msg);
int AafilSelkommi(struct PARKOMMI* vez, char* error_msg);
int AafilDelaufbearb(struct PARAUFBEARB* vez, char* error_msg);
int AafilInsaufbearb(struct PARAUFBEARB* vez, char* error_msg);
int AafilUpdaufbearb(struct PARAUFBEARB* vez, char* error_msg);
int AafilSelaufbearb(struct PARAUFBEARB* vez, char* error_msg);
int AafilDelauferg(struct PARAUFERG* vez, char* error_msg);
int AafilInsauferg(struct PARAUFERG* vez, char* error_msg);
int AafilUpdauferg(struct PARAUFERG* vez, char* error_msg);
int AafilSelauferg(struct PARAUFERG* vez, char* error_msg);
int AafilDelnachart(struct PARNACHRART* vez, char* error_msg);
int AafilInsnachart(struct PARNACHRART* vez, char* error_msg);
int AafilUpdnachart(struct PARNACHRART* vez, char* error_msg);
int AafilSelnachart(struct PARNACHRART* vez, char* error_msg);
int AafilDelkobehtyp(struct PARKOBEHTYP* vez, char* error_msg);
int AafilInskobehtyp(struct PARKOBEHTYP* vez, char* error_msg);
int AafilUpdkobehtyp(struct PARKOBEHTYP* vez, char* error_msg);
int AafilSelkobehtyp(struct PARKOBEHTYP* vez, char* error_msg);
int AafilDelkondgr(struct PARKONGRP* vez, char* error_msg);
int AafilInskondgr(struct PARKONGRP* vez, char* error_msg);
int AafilUpdkondgr(struct PARKONGRP* vez, char* error_msg);
int AafilSelkondgr(struct PARKONGRP* vez, char* error_msg);
int AafilDelkabakomb(struct PARKABAKOMB* vez, char* error_msg);
int AafilInskabakomb(struct PARKABAKOMB* vez, char* error_msg);
int AafilSelkabakomb(struct PARKABAKOMB* vez, char* error_msg);
int AafilDelbuchart(struct PARBUCHART* vez, char* error_msg);
int AafilInsbuchart(struct PARBUCHART* vez, char* error_msg);
int AafilUpdbuchart(struct PARBUCHART* vez, char* error_msg);
int AafilSelbuchart(struct PARBUCHART* vez, char* error_msg);
int AafilDelkoart(struct PARKOART* vez, char* error_msg);
int AafilInskoart(struct PARKOART* vez, char* error_msg);
int AafilUpdkoart(struct PARKOART* vez, char* error_msg);
int AafilSelkoart(struct PARKOART* vez, char* error_msg);
int AafilDelaart(struct PARAART* vez, char* error_msg);
int AafilInsaart(struct PARAART* d, char* error_msg);
int AafilUpdaart(struct PARAART* d, char* error_msg);
int AafilSelaart(struct PARAART* d, char* error_msg);
int AafilReadpasswd(struct AEPWD* d, char* error_msg);
int AatartSel_art_altern(struct ARTALT* vez, char* error_msg);
int AatartAa_sel_artnr(struct ARTAESEL* vez, char* error_msg);
int AakundeSel_ausku(struct KNDAUSKU* vez, char* error_msg);
int AakundeSel_touren(kndtourenS* vez, char* error_msg);
int AakundeSel_offen(struct KNDOFFEN* vez, char* error_msg);
int AakundeSel_aufart(struct KNDAUFART* vez, char* error_msg);
int AafilGetdatetime(struct TM* vez, char* error_msg);
int AatartLagerinf(struct ARTLAGER* vez, char* error_msg);
int AatartInf_verfall(struct ARTVERFALL* vez, char* error_msg);
int AatartInf_preis(struct ARTPREIS* vez, char* error_msg);
int AafilGet_filiale(struct FILINF* vez, char* error_msg);
int AafilWriteOldVersion(struct FILINF* vez, char* error_msg);
int AatartInf_art_nr(struct ARTINF* vez, char* error_msg);
int AatartSel_mc_pkgr(struct ARTSEL* vez, char* error_msg);
int AatartSel_mc(struct ARTSEL* vez, char* error_msg);
int AatartSel_art_nr(struct ARTSEL* vez, char* error_msg);
int AakundeSel_knd_info(struct KNDINF* vez, char* error_msg);
int AakundeSel_mc(struct KNDSEL* vez, char* error_msg);
int AakundeSel_kndnr(struct KNDSEL* vez, char* error_msg);
int AakritikSel_kritikuser(kritikS* vez, char* error_msg);
int AatartSel_herstname(struct ARTSEL* vez, char* error_msg);
void AatartIvrylab(char* tab_name);
int AafilUpdkabakomb(struct PARKABAKOMB* vez, char* error_msg);
int LieferselSel_info(struct LIEFERINFO* liefer, char* error_msg);
bool AatartSel_service_type_exists(const char* service_type, char* error_msg);
bool AatartSel_service_number_exists_and_valid(const char* service_no, const char* service_type, char* result, char* error_msg);
bool AatartSel_taxlevel_exists(const short taxlevel, char* error_msg);

void WriteLogInfo( const char* err_str, int err_num, int fehler_art );

/*  GLOBALE C-VARIABLEN  */
extern long UID;
extern short FilialNr;
}

#ifdef __ONLY_DISTRIBUTE__
extern int DistributorFunPublic( const int iFunNo, char* spIn, char* spOut, int* ipLen);
#endif /*__ONLY_DISTRIBUTE__*/

int FktvertFkt_selekt(int fkt_nr, char* in, char* out, int* out_len);
int FktvertPuffer_anp(char* WriteBuf, char* ReadBuf, int a_lng);

int AasrvSelTourDelay(tourdelayS* d, char*  /*error_msg*/);
int AasrvGetDocumentLink(deliveryadvicedocumentS* d, char*  /*error_msg*/);
int AasrvGetBatchAdviceLink(deliveryadvicedocumentS* d, char*  /*error_msg*/);
int AasrvSelDeliveryAdviceVATTotals(deliveryadvicevattotalsS* d, char*  /*error_msg*/);
int AasrvSelDeliveryAdviceRemarks(deliveryadviceremarkS* d, char*  /*error_msg*/);
int AasrvSelDeliveryAdviceLineReturn(deliveryadvicelinereturnS* d, char*  /*error_msg*/);
int AasrvSelDeliveryAdviceLineIBTLink(deliveryadvicelineibtlinkS* d, char*  /*error_msg*/);
int AasrvSelDeliveryAdviceLineDiscount(deliveryadvicelinediscountsS* d, char*  /*error_msg*/);
int AasrvSelDeliveryAdviceLineDetails(deliveryadvicelinedetailsS* d, char*  /*error_msg*/);
int AasrvSelDeliveryAdviceLine(deliveryadvicelineS* d, char*  /*error_msg*/);
int AasrvSelDeliveryAdviceHead(deliveryadviceheadS* d, char*  /*error_msg*/);
int AasrvSelCscOrderType(auftragsartS* d, char*  /*error_msg*/);
int AasrvDelCscOrderType(auftragsartS* d, char*  /*error_msg*/);
int AasrvSelAllCscOrderType(auftragsartS* d, char*  /*error_msg*/);
int AasrvInsertCscOrderType(auftragsartS* d, char*  /*error_msg*/);
int AasrvUpdateCscOrderType(auftragsartS* d, char*  /*error_msg*/);
int AasrvCSCOrderImport(cscorderimportcsvfileS* d, char*  /*error_msg*/);
int AasrvDeleteCSCOrderImportCSVFormats(cscorderimportcsvformatsS* d, char*  /*error_msg*/);
int AasrvGetCSCOrderImportCSVFormats(cscorderimportcsvformatsS* d, char*  /*error_msg*/);
int AasrvGetCSCOrderImportFields(cscorderimportfieldsS* d, char*  /*error_msg*/);
int AasrvGetCSCOrderImportCSVColumns(cscorderimportcsvcolumnsS* d, char*  /*error_msg*/);
int AasrvDeleteCSCOrderImportCSVColumns(cscorderimportcsvcolumnsS* d, char*  /*error_msg*/);
int AasrvInsertCSCOrderImportCSVFormats(cscorderimportcsvformatsS* d, char*  /*error_msg*/);
int AasrvUpdateCSCOrderImportCSVFormats(cscorderimportcsvformatsS* d, char*  /*error_msg*/);
int AasrvInsertCSCOrderImportCSVColumns(cscorderimportcsvcolumnsS* d, char*  /*error_msg*/);
int AasrvDeleteReservationConfigcpgConfigID(ordertypereservationconfigcpgS* d, char*  /*error_msg*/);
int AasrvGetReservationConfigListByOrderType(ordertypereservationconfigS* d, char*  /*error_msg*/);
int AasrvGetReservationConfigByID(ordertypereservationconfigS* d, char*  /*error_msg*/);
int AasrvInsertReservationConfig(ordertypereservationconfigS* d, char*  /*error_msg*/);
int AasrvUpdateReservationConfig(ordertypereservationconfigS* d, char*  /*error_msg*/);
int AasrvDeleteReservationConfig(ordertypereservationconfigS* d, char*  /*error_msg*/);
int AasrvGetReservationConfigcpgListByConfigID(ordertypereservationconfigcpgS* d, char*  /*error_msg*/);
int AasrvInsertReservationConfigcpg(ordertypereservationconfigcpgS* d, char*  /*error_msg*/);
int AasrvDeleteReservationConfigcpg(ordertypereservationconfigcpgS* d, char*  /*error_msg*/);
int AasrvGetCSCReservationTypeList(cscreservationtypesS* d, char*  /*error_msg*/);
int AasrvGetCSCReservationTypeByTyp(cscreservationtypesS* d, char*  /*error_msg*/);
int AasrvSpecialPosDone(struct AUFPOSBUCH* d, char* error_msg);
int AasrvOrderSpecialPosDone(struct AUFTRAG* d, char* error_msg);
int AasrvCallbackGetMailLink(callbackmaillinkS* d, char* error_msg);
int AasrvCloseorderDebtLimit(struct AUFTRAG* d, char* error_msg);
int AasrvSetIVCVoucherNo(struct AUFTRAG* d, char* error_msg);
int AasrvSetOriginalInvoiceNo(struct AUFTRAG* d, char* error_msg);
int AasrvCancelorderDebtLimit(struct AUFTRAG* d, char* error_msg);
int AasrvIBTOrderPosDone(struct AUFTRAG* d, char* error_msg);
int AasrvIBTPosDone(struct AUFPOSBUCH* d, char* error_msg);
int AasrvIBTPossible(verbundmoeglS* d, char* error_msg);
int AasrvGetOMGRebates(articleomgS* d, char* error_msg);
int AasrvSetOrderToCash(struct AUFTRAG* d, char* error_msg);
int AasrvReserveStockAbsArticleReservation(artikelreserveS* d, char* error_msg);
int AasrvInsertBestandArticleReservation(artikelreserveS* d, char* error_msg);
int AasrvDeleteArticleReservation(artikelreserveS* d, char* error_msg);
int AasrvUpdateArticleReservation(artikelreserveS* d, char* error_msg);
int AasrvInsertArticleReservation(artikelreserveS* d, char* error_msg);
int AasrvSendEMail(sendmailS* d, char* error_msg);
int AasrvGetBestTA(struct AUFPOSBUCH* d, char* error_msg);
int AasrvWriteProformaPos(struct AUFPOSBUCH* d, char* error_msg);
int AasrvCheckKippzeit(struct AUFTRAG* d, char* error_msg);
int AasrvGetRangesBG(rangelistS* d, char* error_msg);
int AasrvGetRanges(rangelistS* d, char* error_msg);
int AasrvSetCashRebate(struct AUFTRAG* d, char* error_msg);
int AasrvWriteProLink(prolinkS* d, char* error_msg);
int AasrvConfirmRO(rabattorderS* d, char* error_msg);
int AasrvClearZU(struct AUFTRAG* d, char* error_msg);
int AasrvSetNatra(struct AUFPOSBUCH* d, char* error_msg);
int AasrvClearROParam(rabattorderS* d, char* error_msg);
int AasrvChangeROMembers(cstdiscaccS* d, char* error_msg);
int AasrvGetROMembers(cstdiscaccS* d, char* error_msg);
int AasrvWriteInvoiceSettings(invoicesettingsS* d, char* error_msg);
int AasrvGetInvoiceSettings(invoicesettingsS* d, char* error_msg);
int AasrvWritePromoPos(struct AUFPOSBUCH* d, char* error_msg);
int AasrvGetRebatePrice( rebatepriceS* d, char* error_msg);
int AasrvGetPromotions(discountanzS* d, char* error_msg);
int AasrvGetRebates(discountanzS* d, char* error_msg);
int AasrvCalcpos(struct AUFPOSBUCH* d, char* error_msg);
int AasrvSetROParam(rabattorderS* d, char* error_msg);
int AasrvSetBTMLicense(struct AUFTRAG* d, char* error_msg);
int AasrvGetOrderVals(ordervaluesS* d, char* error_msg);
int AasrvProforma(struct AUFPOSBUCH* d, char* error_msg);
int AasrvGetWeektouren(kndtourenS* d, char* error_msg);
int AasrvGettourenAufArt(kndtourenS* d, char* error_msg);
int AasrvWriteposNL(struct AUFPOSBUCH* d, char* error_msg);
int AasrvUnlock(struct LOCKMAN* d, char* error_msg);
int AasrvGetVerbMoegl(struct AUFALTLAGORT* d, char* error_msg);
int AasrvGetIBTStockLevel(struct AUFALTLAGORT* d, char* error_msg);
int AasrvCheckIBTStockLevel(struct AUFALTLAGORT* d, char* error_msg);
int AasrvGetOrderInfo(struct AUFTRAG* d, char* error_msg);
int AasrvDelKopfZlnAuf(struct AUFTEXTE* d, char* error_msg);
int AasrvInsKopfZlnAuf(struct AUFTEXTE* d, char* error_msg);
int AasrvSelKopfZlnAuf(struct AUFTEXTE* d, char* error_msg);
int AasrvOpenInfoorder(struct AUFTRAG* d, char* error_msg);
int AasrvSelposInfAuf(struct AUFPOSBUCH* d, char* error_msg);
int AasrvInfposnr(struct AUFPOSBUCH* d, char* error_msg);
int AasrvWritetextpos(struct AUFPOSBUCH* d, char* error_msg);
int AasrvChangetextpos(struct AUFPOSBUCH* d, char* error_msg);
int AasrvGetsession(struct AUFSESS* d, char* error_msg);
int AasrvAnzzrorder(struct AUFTRAG* d, char* error_msg);
int AasrvSeldeforalphapos(struct AUFPOSBUCH* d, char* error_msg);
int AasrvSelpos(struct AUFPOSBUCH* d, char* error_msg);
int AasrvSelOrder(struct AUFTRAG* d, char* error_msg);
int AasrvChangeOrdBem(struct AUFTRAG* d, char* error_msg);
int AasrvChangeValuta(struct AUFTRAG* d, char* error_msg);
int AasrvChangeTour(struct AUFTRAG* d, char* error_msg);
int AasrvChangeCustomer(struct AUFTRAG* d, char* error_msg);
int AasrvGettouren(kndtourenS* d, char* error_msg);
int AasrvGetaartes(struct AUFARTES* d, char* error_msg);
int AasrvGetCustOrderType(auftragartkdS* d, char* error_msg);
int AasrvChangepos(struct AUFPOSBUCH* d, char* error_msg);
int AasrvWritepos(struct AUFPOSBUCH* d, char* error_msg);
int AasrvChangeorder(struct AUFTRAG* d, char* error_msg);
int AasrvCloseorder(struct AUFTRAG* d, char* error_msg);
int AasrvOpenorder(struct AUFTRAG* d, char* error_msg);
int AasrvNeworder(struct AUFTRAG* d, char* error_msg);
int AasrvClosesession(struct AUFTRAG* d, char* error_msg);
int AasrvOpensession(struct AUFTRAG* d, char* error_msg);
int AasrvOpensessionNonVideo(struct AUFTRAG* d, char* error_msg);
int AasrvChangeKzNachBearb(struct AUFPOSNACH* d, char* error_msg);
int AasrvSetprintdirect(struct AUFTRAG* d, char* error_msg);
int AasrvWriteposition(struct AUFPOSBUCH* d, char* error_msg);
int AasrvSetdelayeddate(struct AUFTRAG* d, char* error_msg);
int AasrvSetNoSeperate(struct AUFTRAG* d, char* error_msg);
int AasrvCheckReference(struct AUFTRAG* d, char* error_msg);
int AasrvInsertReference(struct AUFTRAG* d, char* error_msg);
int WepselFkt_selekt(int fkt_nr, char* in, char* out, int* out_len) ;
int WepselPuffer_anp(char* WriteBuf, char* ReadBuf, int a_lng) ;
int AasrvDiscountMode(struct AUFPOSBUCH* d, char* /*error_msg*/);

extern pxSession& getSession();

/*  GLOBALE VARIABLEN  */

static std::map<int, int> redirectFunctions;
static bool define()
{
    redirectFunctions[ARTIKELRESERVE_INSERT]            = 767;
    redirectFunctions[ARTIKELRESERVE_UPDATE]            = 768;
    redirectFunctions[ARTIKELRESERVE_DELETE]            = 769;
    redirectFunctions[ARTIKELRESERVE_INSERTBESTAND]     = 770;
    redirectFunctions[ARTIKELRESERVE_RESERVSTOCKABS]    = 771;
    return true;
}
static const bool dummy = define();

int handleResult(int rc, void* stru, char* out, int* out_len, char* error_msg, struct buf_desc bd[], size_t anz)
{
    if (rc < 0)
    {
        strcpy(out, error_msg);
        *out_len = strlen(out) + 1;
    }
    else
    {
        *out_len = buf_kon(TO_UEB, stru, out, bd, anz);
    }
    return rc;
}

/* function definitions for WEPSEL */
/*  FKT_SELEKT  */
int FktvertFkt_selekt(int fkt_nr, char* in, char* out, int* out_len)
{
    /*  fkt_selekt  */

    /* fkt_nr = Nummer der auszufuehrenden Funktion */
    /* in     = Dateneingabe der Funktion */
    /* out    = Ergebnis der Funktion bei rc==-1 Fehlertext */
    int rc;
    char error_msg[81];
    if (redirectFunctions.find(fkt_nr) != redirectFunctions.end())
    {
       return FktvertFkt_selekt(redirectFunctions[fkt_nr], in, out, out_len);
    }


#ifdef __ONLY_DISTRIBUTE__
    if ( fkt_nr >= DADE_FUNCTION_NO )
    {
       return DistributorFunPublic( fkt_nr, in, out, out_len );
    }
#endif /*__ONLY_DISTRIBUTE__*/

    switch(fkt_nr)
    {

    case 213:
        {
            parameter_change_log_defsS d;
            buf_kon(FROM_UEB, (char* )&d, in, PARAMETER_CHANGE_LOG_DEFS_BES, PARAMETER_CHANGE_LOG_DEFS_ANZ);
            rc = AafilSelLogParameterDefinitions(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAMETER_CHANGE_LOG_DEFS_BES, PARAMETER_CHANGE_LOG_DEFS_ANZ);
        }
    case 212:
    {
        parameter_change_loggingS d;
        buf_kon(FROM_UEB, (char* )&d, in, PARAMETER_CHANGE_LOGGING_BES, PARAMETER_CHANGE_LOGGING_ANZ);
        rc = AafilSelLogParameter(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAMETER_CHANGE_LOGGING_BES, PARAMETER_CHANGE_LOGGING_ANZ);
    }
    case 210:
        {
            struct ARTAESEL d;
            buf_kon(FROM_UEB, (char* )&d, in, ARTAESEL_BES, ARTAESEL_ANZ);
            rc = AatartAa_select(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTAESEL_BES, ARTAESEL_ANZ);
        }
    case 209:
        {
            fcordersselS d;
            buf_kon(FROM_UEB, (char* )&d, in , FCORDERSSEL_BES,FCORDERSSEL_ANZ);
            rc = AaauftSelList_FCOrdersToSolve(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, FCORDERSSEL_BES, FCORDERSSEL_ANZ);
        }
    case 208:
        {
            fcordersselS d;
            buf_kon(FROM_UEB, (char* )&d, in , FCORDERSSEL_BES,FCORDERSSEL_ANZ);
            rc = AaauftSelList_FCOrdersToClose(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, FCORDERSSEL_BES, FCORDERSSEL_ANZ);
        }
    case 207:
        {
            fcordersselS d;
            buf_kon(FROM_UEB, (char* )&d, in , FCORDERSSEL_BES,FCORDERSSEL_ANZ);
            rc = AaauftSelList_FCOrdersAll(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, FCORDERSSEL_BES, FCORDERSSEL_ANZ);
        }
    case 206:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelList_Auftrag(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 205:
        {
            struct FILINF d;
            buf_kon(FROM_UEB, (char* )&d, in , FILINF_BES,FILINF_ANZ);
            rc = AafilGet_filiale_Procenter(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, FILINF_BES, FILINF_ANZ);
        }
    case 204:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauft_o_sortfield(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 203:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauft_o_branch(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 202:
        {
            struct PARKABAKOMB d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKABAKOMB_BES,PARKABAKOMB_ANZ);
            rc = AafilUpdkabakomb(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKABAKOMB_BES, PARKABAKOMB_ANZ);
        }
    case 201:
        {
            struct ARTSEL d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTSEL_BES,ARTSEL_ANZ);
            rc = AatartSel_herstname(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTSEL_BES, ARTSEL_ANZ);
        }
    case 200:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelProLink(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 199:
        {
            struct ZEITARTV d;
            buf_kon(FROM_UEB, (char* )&d, in,ZEITARTV_BES,ZEITARTV_ANZ);
            rc= AafilSel_zeit_heute(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ZEITARTV_BES, ZEITARTV_ANZ);
        }
    case 198:
        {
            struct ARTAESEL d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTAESEL_BES,ARTAESEL_ANZ);
            rc = AatartSel_NoByCode(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTAESEL_BES, ARTAESEL_ANZ);
        }
    case 197:
        {
            struct ARTAESEL d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTAESEL_BES,ARTAESEL_ANZ);
            rc = AatartSel_Preferred(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTAESEL_BES, ARTAESEL_ANZ);
        }
    case 196:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauft_o_pos(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 195:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauft_o_kdklasse(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    //case 194:
    //    {
    //        struct ARTAESEL d;
    //        buf_kon(FROM_UEB, (char* )&d, in , ARTAESEL_BES,ARTAESEL_ANZ);
    //        rc = AatartCheck_natra(&d, error_msg);
    //        return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTAESEL_BES, ARTAESEL_ANZ);
    //    }
    case 193:
        {
            struct DRUCKPARA d;
            buf_kon(FROM_UEB, (char* )&d, in,DRUCKPARA_BES,DRUCKPARA_ANZ);
            rc= AadruckNachl_liefer(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, DRUCKPARA_BES, DRUCKPARA_ANZ);
        }
    case 192:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauftDD(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 191:
        {
            struct KNDINF d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDINF_BES,KNDINF_ANZ);
            rc = AakundeSel_knd_info_hipath(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDINF_BES, KNDINF_ANZ);
        }
    case 190:
        {
            struct ARTSEL d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTSEL_BES,ARTSEL_ANZ);
            rc = AatartSel_ean(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTSEL_BES, ARTSEL_ANZ);
        }
    case 189:
        {
            struct KNDSEL d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDSEL_BES,KNDSEL_ANZ);
            rc = AakundeSel_name(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDSEL_BES, KNDSEL_ANZ);
        }
    case 188:
        {
            struct AUFARTES d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFARTES_BES,AUFARTES_ANZ);
            rc= AaauftSel_valutatage(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFARTES_BES, AUFARTES_ANZ);
        }
    case 187:
        {
            lgtextS d;
            buf_kon(FROM_UEB, (char* )&d, in , LGTEXT_BES,LGTEXT_ANZ);
            rc = AafilSet_sprache(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, LGTEXT_BES, LGTEXT_ANZ);
        }
    case 186:
        {
            struct KNDINF d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDINF_BES,KNDINF_ANZ);
            rc = AakundeSel_telnr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDINF_BES, KNDINF_ANZ);
        }
    case 185:
        {
            struct ARTSEL d;
            buf_kon(FROM_UEB, (char* )&d, in,ARTSEL_BES,ARTSEL_ANZ);
            rc= AatartFetch_artnrlief(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTSEL_BES, ARTSEL_ANZ);
        }
    case 183:
        {
            kritikS d;
            buf_kon(FROM_UEB, (char* )&d, in,KRITIK_BES,KRITIK_ANZ);
            rc= AakritikSel_kritikuser(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KRITIK_BES, KRITIK_ANZ);
        }
    case 182:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauft_o_aart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 181:
        {
            struct AUFIE d;
            buf_kon(FROM_UEB, (char* )&d, in , AUFIE_BES,AUFIE_ANZ);
            rc = AaauftCheck_auftnr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFIE_BES, AUFIE_ANZ);
        }
    case 180:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSel_fili_auft_nr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 179:
        {
            kndtourenS d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDTOUREN_BES,KNDTOUREN_ANZ);
            rc = AakundeSel_nachttouren(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDTOUREN_BES, KNDTOUREN_ANZ);
        }
    case 178:
        {
            struct DRUCKPARA d;
            buf_kon(FROM_UEB, (char* )&d, in,DRUCKPARA_BES,DRUCKPARA_ANZ);
            rc= AadruckMasterplan(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, DRUCKPARA_BES, DRUCKPARA_ANZ);
        }
    case 177:
        {
            struct KNDSEL d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDSEL_BES,KNDSEL_ANZ);
            rc = AakundeSel_idf(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDSEL_BES, KNDSEL_ANZ);
        }
    case 176:
        {
            struct FILINF d;
            buf_kon(FROM_UEB, (char* )&d, in , FILINF_BES,FILINF_ANZ);
            rc = AafilSet_actualfiliale(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, FILINF_BES, FILINF_ANZ);
        }
    case 175:
        {
            struct DRUCKPARA d;
            buf_kon(FROM_UEB, (char* )&d, in,DRUCKPARA_BES,DRUCKPARA_ANZ);
            rc= AadruckNachl_vbmoegl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, DRUCKPARA_BES, DRUCKPARA_ANZ);
        }
    case 174:
        {
            struct PARKABAKOMB d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKABAKOMB_BES,PARKABAKOMB_ANZ);
            rc = AafilChecktour(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKABAKOMB_BES, PARKABAKOMB_ANZ);
        }
    case 173:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauftpzn(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 172:
        {
            struct NACHLIEF d;
            buf_kon(FROM_UEB, (char* )&d, in,NACHLIEF_BES,NACHLIEF_ANZ);
            rc= AaauftSel_kndnlprio(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, NACHLIEF_BES, NACHLIEF_ANZ);
        }
    case 171:
        {
            struct AUFARTES d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFARTES_BES,AUFARTES_ANZ);
            rc= AaauftSel_valutaauto(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFARTES_BES, AUFARTES_ANZ);
        }
    case 170:
        {
            struct AUFIE d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFIE_BES,AUFIE_ANZ);
            rc= AaauftSperr_auft(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFIE_BES, AUFIE_ANZ);
        }
    case 169:
        {
            struct N_VBBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, VBBUCH_BES, VBBUCH_ANZ);
            rc= AaauftSel_defekte(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, VBBUCH_BES, VBBUCH_ANZ);
        }
    case 168:
        {
            struct VBCOUNT d;
            buf_kon(FROM_UEB, (char* )&d, in, VBCOUNT_BES, VBCOUNT_ANZ);
            rc= AaauftSel_vbcount(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, VBCOUNT_BES, VBCOUNT_ANZ);
        }
    case 167:
        {
            struct N_VBBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, VBBUCH_BES, VBBUCH_ANZ);
            rc= Aaauft_Sel_vbmoegl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, VBBUCH_BES, VBBUCH_ANZ);
        }
    case 166:
        {
            struct VBLIEF d;
            buf_kon(FROM_UEB, (char* )&d, in, VBLIEF_BES, VBLIEF_ANZ);
            rc= Aaauft_Sel_vblief(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, VBLIEF_BES, VBLIEF_ANZ);
        }
    case 165:
        {
            struct NACHLIEF d;
            buf_kon(FROM_UEB, (char* )&d, in,NACHLIEF_BES,NACHLIEF_ANZ);
            rc= AaauftIns_nachl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, NACHLIEF_BES, NACHLIEF_ANZ);
        }
    case 164:
        {
            struct ARTFOLGE d;
            buf_kon(FROM_UEB, (char* )&d, in,ARTFOLGE_BES,ARTFOLGE_ANZ);
            rc= AatartSel_folge(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTFOLGE_BES, ARTFOLGE_ANZ);
        }
    case 163:
        {
            struct AUFLAGER d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFLAGER_BES,AUFLAGER_ANZ);
            rc= AaauftSel_lauftnr(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFLAGER_BES, AUFLAGER_ANZ);
        }
    case 162:
        {
            struct DRUCKPARA d;
            buf_kon(FROM_UEB, (char* )&d, in,DRUCKPARA_BES,DRUCKPARA_ANZ);
            rc= AadruckNachl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, DRUCKPARA_BES, DRUCKPARA_ANZ);
        }
    case 161:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in,AUSTINF_BES,AUSTINF_ANZ);
            rc= AaauftSel_lager_auft_nr(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 160:
        {
            struct ARTLIEFER d;
            buf_kon(FROM_UEB, (char* )&d, in,ARTLIEFER_BES,ARTLIEFER_ANZ);
            rc= AatartSel_artlief(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTLIEFER_BES, ARTLIEFER_ANZ);
        }
    case 159:
        {
            struct AUFWANNEN d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFWANNEN_BES,AUFWANNEN_ANZ);
            rc= AaauftSel_tub_pos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFWANNEN_BES, AUFWANNEN_ANZ);
        }
    case 156:
        {
            struct KNDMONUMS d;
            buf_kon(FROM_UEB, (char* )&d, in,KNDMONUMS_BES,KNDMONUMS_ANZ);
            rc= AakundeSel_monums(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDMONUMS_BES, KNDMONUMS_ANZ);
        }
    case 155:
        {
            struct AUFIE d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFIE_BES,AUFIE_ANZ);
            rc= AafilIs_new_order_possi(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFIE_BES, AUFIE_ANZ);
        }
    case 154:
        {
            struct KNDAUFART d;
            buf_kon(FROM_UEB, (char* )&d, in,KNDAUFART_BES,KNDAUFART_ANZ);
            rc= AakundeDel_aufart(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDAUFART_BES, KNDAUFART_ANZ);
        }
    case 153:
        {
            struct KNDAUFART d;
            buf_kon(FROM_UEB, (char* )&d, in,KNDAUFART_BES,KNDAUFART_ANZ);
            rc= AakundeIns_aufart(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDAUFART_BES, KNDAUFART_ANZ);
        }
    case 152:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in,AUSTINF_BES,AUSTINF_ANZ);
            rc= AaauftGetfirstordertime(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 151:
        {
            struct PARAUFTRENDZEIT d;
            buf_kon(FROM_UEB, (char* )&d, in,PARAUFTRENDZEIT_BES,PARAUFTRENDZEIT_ANZ);
            rc= AafilIns_auftrendzeit(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFTRENDZEIT_BES, PARAUFTRENDZEIT_ANZ);
        }
    case 150:
        {
            struct PARAUFTRENDZEIT d;
            buf_kon(FROM_UEB, (char* )&d, in,PARAUFTRENDZEIT_BES,PARAUFTRENDZEIT_ANZ);
            rc= AafilDel_auftrendzeit(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFTRENDZEIT_BES, PARAUFTRENDZEIT_ANZ);
        }
    case 149:
        {
            struct PARAUFTRENDZEIT d;
            buf_kon(FROM_UEB, (char* )&d, in,PARAUFTRENDZEIT_BES,PARAUFTRENDZEIT_ANZ);
            rc= AafilSel_auftrendzeit(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFTRENDZEIT_BES, PARAUFTRENDZEIT_ANZ);
        }
    case 148:
        {
            struct NACHLPROTV d;
            buf_kon(FROM_UEB, (char* )&d, in,NACHLPROTV_BES,NACHLPROTV_ANZ);
            rc= AaauftGet_prot_nl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, NACHLPROTV_BES, NACHLPROTV_ANZ);
        }
    case 147:
        {
            struct NACHLPROT d;
            buf_kon(FROM_UEB, (char* )&d, in,NACHLPROT_BES,NACHLPROT_ANZ);
            rc= AaauftIns_prot(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, NACHLPROT_BES, NACHLPROT_ANZ);
        }
    case 146:
        {
            struct AUFENDART d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFENDART_BES,AUFENDART_ANZ);
            rc= AaauftSel_end_art(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFENDART_BES, AUFENDART_ANZ);
        }
    case 145:
        {
            struct AUFENDPOS d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFENDPOS_BES,AUFENDPOS_ANZ);
            rc= AaauftSel_art_pos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFENDPOS_BES, AUFENDPOS_ANZ);
        }
    case 144:
        {
            struct AUFEAN d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFEAN_BES,AUFEAN_ANZ);
            rc= AaauftSel_ean_uni(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFEAN_BES, AUFEAN_ANZ);
        }
    case 143:
        {
            struct NACHLIEF d;
            buf_kon(FROM_UEB, (char* )&d, in,NACHLIEF_BES,NACHLIEF_ANZ);
            rc= AaauftSel_kndnl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, NACHLIEF_BES, NACHLIEF_ANZ);
        }
    case 142:
        {
            struct AUFENDPOS d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFENDPOS_BES,AUFENDPOS_ANZ);
            rc= AaauftSel_end_pos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFENDPOS_BES, AUFENDPOS_ANZ);
        }
    case 141:
        {
            struct AUFENDKOPF d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFENDKOPF_BES,AUFENDKOPF_ANZ);
            rc= AaauftSel_end_kopf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFENDKOPF_BES, AUFENDKOPF_ANZ);
        }
    case 140:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFPOSBUCH_BES,AUFPOSBUCH_ANZ);
            rc= AaauftSel_frt(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 139:
        {
            struct NACHLART d;
            buf_kon(FROM_UEB, (char* )&d, in,NACHLART_BES,NACHLART_ANZ);
            rc= AaauftSel_nachlart(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, NACHLART_BES, NACHLART_ANZ);
        }
    case 138:
        {
            struct ZEITARTV d;
            buf_kon(FROM_UEB, (char* )&d, in,ZEITARTV_BES,ZEITARTV_ANZ);
            rc= AafilSel_verbund(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ZEITARTV_BES, ZEITARTV_ANZ);
        }
    case 137:
        {
            struct ARTLAGER d;
            buf_kon(FROM_UEB, (char* )&d, in,ARTLAGER_BES,ARTLAGER_ANZ);
            rc= AatartSel_lagerbest(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTLAGER_BES, ARTLAGER_ANZ);
        }
    case 136:
        {
            struct AUFEREIG d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFEREIG_BES,AUFEREIG_ANZ);
            rc= AaauftIns_auft_ereig(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFEREIG_BES, AUFEREIG_ANZ);
        }
    case 135:
        {
            struct AUFSTPLAN d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFSTPLAN_BES,AUFSTPLAN_ANZ);
            rc= AaauftStatplan_sel(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFSTPLAN_BES, AUFSTPLAN_ANZ);
        }
    case 134:
        {
            struct RUFPTAGVOR d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAGVOR_BES,RUFPTAGVOR_ANZ);
            rc= AaplanVor_sel_ins(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAGVOR_BES, RUFPTAGVOR_ANZ);
        }
    case 133:
        {
            struct RUFPTAGVOR d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAGVOR_BES,RUFPTAGVOR_ANZ);
            rc= AaplanVor_sel_upd(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAGVOR_BES, RUFPTAGVOR_ANZ);
        }
    case 132:
        {
            struct RUFPTAGVOR d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAGVOR_BES,RUFPTAGVOR_ANZ);
            rc= AaplanVor_sel_uni(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAGVOR_BES, RUFPTAGVOR_ANZ);
        }
    case 131:
        {
            struct AEPWD d;
            buf_kon(FROM_UEB, (char* )&d, in,AEPWD_BES,AEPWD_ANZ);
            rc= AafilSel_aa_passwd(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AEPWD_BES, AEPWD_ANZ);
        }
    case 130:
        {
            struct RUFPTAGTOUR d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAGTOUR_BES,RUFPTAGTOUR_ANZ);
            rc= AaplanSel_tour(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAGTOUR_BES, RUFPTAGTOUR_ANZ);
        }
    case 129:
        {
            struct RUFPTAGSUM d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAGSUM_BES,RUFPTAGSUM_ANZ);
            rc= AaplanSel_count(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAGSUM_BES, RUFPTAGSUM_ANZ);
        }
    case 128:
        {
            struct NACHLIEF d;
            buf_kon(FROM_UEB, (char* )&d, in,NACHLIEF_BES,NACHLIEF_ANZ);
            rc= AaauftUpd_nachl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, NACHLIEF_BES, NACHLIEF_ANZ);
        }
    case 127:
        {
            struct NACHLIEF d;
            buf_kon(FROM_UEB, (char* )&d, in,NACHLIEF_BES,NACHLIEF_ANZ);
            rc= AaauftLoe_nachl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, NACHLIEF_BES, NACHLIEF_ANZ);
        }
    case 126:
        {
            struct NACHLIEF d;
            buf_kon(FROM_UEB, (char* )&d, in,NACHLIEF_BES,NACHLIEF_ANZ);
            rc= AaauftSel_nachl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, NACHLIEF_BES, NACHLIEF_ANZ);
        }
    case 125:
        {
            struct KNDSCHALTER d;
            buf_kon(FROM_UEB, (char* )&d, in,KNDSCHALTER_BES,KNDSCHALTER_ANZ);
            rc= AakundeSel_kndschalter(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDSCHALTER_BES, KNDSCHALTER_ANZ);
        }
    case 124:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFPOSBUCH_BES,AUFPOSBUCH_ANZ);
            rc= AaauftSel_alt_pos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 123:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFTRAG_BES,AUFTRAG_ANZ);
            rc= AaauftSel_alt_auft(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 122:
        {
            struct AUFTEXTE d;
            buf_kon(FROM_UEB, (char* )&d, in,AUFTEXTE_BES,AUFTEXTE_ANZ);
            rc= AaauftSel_alt_kopf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTEXTE_BES, AUFTEXTE_ANZ);
        }
    case 121:
        {
            struct RUFPTAG d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAG_BES,RUFPTAG_ANZ);
            rc= AaplanUni_tag_plan(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAG_BES, RUFPTAG_ANZ);
        }
    case 120:
        {
            struct RUFPTAGINF d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAGINF_BES,RUFPTAGINF_ANZ);
            rc= AaplanSel_tag_plan_inf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAGINF_BES, RUFPTAGINF_ANZ);
        }
    case 119:
        {
            struct USERTEXTV d;
            buf_kon(FROM_UEB, (char* )&d, in,USERTEXTV_BES,USERTEXTV_ANZ);
            rc= AafilDel_usertext(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, USERTEXTV_BES, USERTEXTV_ANZ);
        }
    case 118:
        {
            struct USERTEXTV d;
            buf_kon(FROM_UEB, (char* )&d, in,USERTEXTV_BES,USERTEXTV_ANZ);
            rc= AafilIns_usertext(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, USERTEXTV_BES, USERTEXTV_ANZ);
        }
    case 117:
        {
            struct USERTEXTV d;
            buf_kon(FROM_UEB, (char* )&d, in,USERTEXTV_BES,USERTEXTV_ANZ);
            rc= AafilSel_usertext(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, USERTEXTV_BES, USERTEXTV_ANZ);
        }
    case 115:
        {
            struct ARTAESEL d;
            buf_kon(FROM_UEB, (char* )&d, in,ARTAESEL_BES,ARTAESEL_ANZ);
            rc= AatartAa_sel_index(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTAESEL_BES, ARTAESEL_ANZ);
        }
    case 112:
        {
            struct ARTINFBESTEL d;
            buf_kon(FROM_UEB, (char* )&d, in,ARTINFBESTEL_BES,ARTINFBESTEL_ANZ);
            rc= AatartSel_offene_bstlng(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTINFBESTEL_BES, ARTINFBESTEL_ANZ);
        }
    case 111:
        {
            struct ARTINFHERSTE d;
            buf_kon(FROM_UEB, (char* )&d, in,ARTINFHERSTE_BES,ARTINFHERSTE_ANZ);
            rc= AatartSel_hersteller(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTINFHERSTE_BES, ARTINFHERSTE_ANZ);
        }
    case 110:
        {
            struct RUFPTAG d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAG_BES,RUFPTAG_ANZ);
            rc= AaplanUpd_tag_plan(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAG_BES, RUFPTAG_ANZ);
        }
    case 109:
        {
            struct RUFPTAG d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAG_BES,RUFPTAG_ANZ);
            rc= AaplanIns_tag_plan(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAG_BES, RUFPTAG_ANZ);
        }
    case 108:
        {
            struct SERALOGD d;
            buf_kon(FROM_UEB, (char* )&d, in, SERALOGD_BES, SERALOGD_ANZ);
            rc= AaseraLes_data(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, SERALOGD_BES, SERALOGD_ANZ);
        }
    case 107:
        {
            struct SERALOGH d;
            buf_kon(FROM_UEB, (char* )&d, in, SERALOGH_BES, SERALOGH_ANZ);
            rc= AaseraLes_dir(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, SERALOGH_BES, SERALOGH_ANZ);
        }
    case 106:
        {
            struct ZEITARTV d;
            buf_kon(FROM_UEB, (char* )&d, in,ZEITARTV_BES,ZEITARTV_ANZ);
            rc= AafilDel_zeitart(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ZEITARTV_BES, ZEITARTV_ANZ);
        }
    case 105:
        {
            struct N_ALTFIL d;
            buf_kon(FROM_UEB, (char* )&d, in,ALTFIL_BES,ALTFIL_ANZ);
            rc= AafilDel_altfil(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ALTFIL_BES, ALTFIL_ANZ);
        }
    case 104:
        {
            struct ZEITARTV d;
            buf_kon(FROM_UEB, (char* )&d, in,ZEITARTV_BES,ZEITARTV_ANZ);
            rc= AafilIns_zeitarten(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ZEITARTV_BES, ZEITARTV_ANZ);
        }
    case 103:
        {
            struct ZEITARTV d;
            buf_kon(FROM_UEB, (char* )&d, in,ZEITARTV_BES,ZEITARTV_ANZ);
            rc= AafilUpd_zeitarten(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ZEITARTV_BES, ZEITARTV_ANZ);
        }
    case 102:
        {
            struct ZEITARTV d;
            buf_kon(FROM_UEB, (char* )&d, in,ZEITARTV_BES,ZEITARTV_ANZ);
            rc= AafilSel_zeitarten(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ZEITARTV_BES, ZEITARTV_ANZ);
        }
    case 101:
        {
            struct N_ALTFIL d;
            buf_kon(FROM_UEB, (char* )&d, in,ALTFIL_BES,ALTFIL_ANZ);
            rc= AafilIns_altfil(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ALTFIL_BES, ALTFIL_ANZ);
        }
    case 100:
        {
            struct N_ALTFIL d;
            buf_kon(FROM_UEB, (char* )&d, in,ALTFIL_BES,ALTFIL_ANZ);
            rc= AafilUpd_altfil(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ALTFIL_BES, ALTFIL_ANZ);
        }
    case 99:
        {
            struct N_ALTFIL d;
            buf_kon(FROM_UEB, (char* )&d, in,ALTFIL_BES,ALTFIL_ANZ);
            rc= AafilSel_altfil(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ALTFIL_BES, ALTFIL_ANZ);
        }
    case 98:
        {
            struct RUFPTAG d;
            buf_kon(FROM_UEB, (char* )&d, in,RUFPTAG_BES,RUFPTAG_ANZ);
            rc= AaplanSel_tag_plan(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPTAG_BES, RUFPTAG_ANZ);
        }
    case 97:
        {
            kritikposS d;
            buf_kon(FROM_UEB, (char* )&d, in,KRITIKPOS_BES,KRITIKPOS_ANZ);
            rc= AakritikSelect_pos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KRITIKPOS_BES, KRITIKPOS_ANZ);
        }
    case 96:
        {
            kritikposS d;
            buf_kon(FROM_UEB, (char* )&d, in,KRITIKPOS_BES,KRITIKPOS_ANZ);
            rc= AakritikSchreibe_pos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KRITIKPOS_BES, KRITIKPOS_ANZ);
        }
    case 95:
        {
            kritikkopfS d;
            buf_kon(FROM_UEB, (char* )&d, in,KRITIKKOPF_BES,KRITIKKOPF_ANZ);
            rc= AakritikSchreibe_kopf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KRITIKKOPF_BES, KRITIKKOPF_ANZ);
        }
    case 94:
        {
            kritikS d;
            buf_kon(FROM_UEB, (char* )&d, in,KRITIK_BES,KRITIK_ANZ);
            rc= AakritikSel_kritik_idf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KRITIK_BES, KRITIK_ANZ);
        }
    case 93:
        {
            kritikS d;
            buf_kon(FROM_UEB, (char* )&d, in,KRITIK_BES,KRITIK_ANZ);
            rc= AakritikSel_kritik(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KRITIK_BES, KRITIK_ANZ);
        }
    case 92:
        {
            struct TOURUEBERS d;
            buf_kon(FROM_UEB, (char* )&d, in,TOURUEBERS_BES,TOURUEBERS_ANZ);
            rc= AatourGet_tour_kopf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, TOURUEBERS_BES, TOURUEBERS_ANZ);
        }
    case 91:
        {
            struct TOURINHALT d;
            buf_kon(FROM_UEB, (char* )&d, in,TOURINHALT_BES,TOURINHALT_ANZ);
            rc= AatourUpd_folgenr(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, TOURINHALT_BES, TOURINHALT_ANZ);
        }
    case 90:
        {
            struct TOURINHALT d;
            buf_kon(FROM_UEB, (char* )&d, in,TOURINHALT_BES,TOURINHALT_ANZ);
            rc= AatourUpd_auf_tour(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, TOURINHALT_BES, TOURINHALT_ANZ);
        }
    case 89:
        {
            struct TOURINHALT d;
            buf_kon(FROM_UEB, (char* )&d, in,TOURINHALT_BES,TOURINHALT_ANZ);
            rc= AatourUpd_sond_wann(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, TOURINHALT_BES, TOURINHALT_ANZ);
        }
    case 88:
        {
            struct TOURINHALT d;
            buf_kon(FROM_UEB, (char* )&d, in,TOURINHALT_BES,TOURINHALT_ANZ);
            rc= AatourSel_auf_tour(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, TOURINHALT_BES, TOURINHALT_ANZ);
        }
    case 87:
        {
            struct TOURUEBERS d;
            buf_kon(FROM_UEB, (char* )&d, in,TOURUEBERS_BES,TOURUEBERS_ANZ);
            rc= AatourSel_tour_uebers(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, TOURUEBERS_BES, TOURUEBERS_ANZ);
        }
    case 86:
        {
            struct AUFZLNSTAT d;
            buf_kon(FROM_UEB, (char* )&d, in , AUFZLNSTAT_BES,AUFZLNSTAT_ANZ);
            rc = AaauftZeilenstatistik(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFZLNSTAT_BES, AUFZLNSTAT_ANZ);
        }
    case 85:
        {
            struct AUFSTATUS d;
            buf_kon(FROM_UEB, (char* )&d, in , AUFSTATUS_BES,AUFSTATUS_ANZ);
            rc = AaauftStatusae(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFSTATUS_BES, AUFSTATUS_ANZ);
        }
    case 900:
        {
            struct VTELARTAK d;
            buf_kon(FROM_UEB, (char* )&d, in, VTELARTAK_BES, VTELARTAK_ANZ);
            rc = IftselSel_suchbez(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, VTELARTAK_BES, VTELARTAK_ANZ);
        }
    case 901:
        {
            struct PASSWD d;
            buf_kon(FROM_UEB, (char* )&d, in,PASSWD_BES, PASSWD_ANZ);
            rc = IftselVers_kontr(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PASSWD_BES, PASSWD_ANZ);
        }
    case 902:
        {
            struct KOPLIST d;
            buf_kon(FROM_UEB, (char* )&d, in,KOPLIST_BES, KOPLIST_ANZ);
            rc = IftselSel_tellistt(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KOPLIST_BES, KOPLIST_ANZ);
        }
    case 903:
        {
            struct KOPLIST d;
            buf_kon(FROM_UEB, (char* )&d, in,KOPLIST_BES, KOPLIST_ANZ);
            rc = IftselUpd_tellistt(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KOPLIST_BES, KOPLIST_ANZ);
        }
    case 904:
        {
            struct KOPLIST d;
            buf_kon(FROM_UEB, (char* )&d, in,KOPLIST_BES, KOPLIST_ANZ);
            rc = IftselIns_tellistt(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KOPLIST_BES, KOPLIST_ANZ);
        }
    case 905:
        {
            struct KOPLIST d;
            buf_kon(FROM_UEB, (char* )&d, in,KOPLIST_BES, KOPLIST_ANZ);
            rc = IftselDel_tellistt(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KOPLIST_BES, KOPLIST_ANZ);
        }
    case 906:
        {
            struct KOPLIST d;
            buf_kon(FROM_UEB, (char* )&d, in,KOPLIST_BES, KOPLIST_ANZ);
            rc = IftselSel_info(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KOPLIST_BES, KOPLIST_ANZ);
        }
    case 920:
        {
            struct LIEFERINFO d;
            buf_kon(FROM_UEB, (char* )&d, in, LIEFERINFO_BES, LIEFERINFO_ANZ);
            rc = LieferselSel_info(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, LIEFERINFO_BES, LIEFERINFO_ANZ);
        }
    case 84:
        {
            struct AUFEREIG d;
            buf_kon(FROM_UEB, (char* )&d, in , AUFEREIG_BES,AUFEREIG_ANZ);
            rc = AaauftAusg_auft_ereig(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFEREIG_BES, AUFEREIG_ANZ);
        }
    case 83:
        {
            struct RUFPMASTER d;
            buf_kon(FROM_UEB, (char* )&d, in , RUFPMASTER_BES,RUFPMASTER_ANZ);
            rc = AaplanSel_mplan_idf(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RUFPMASTER_BES, RUFPMASTER_ANZ);
        }
    case 82:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftAnz_zur_geraet(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 81:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftAnz_zur_knd(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 80:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauftknde(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 79:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauft_o_ende(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 78:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauft_o_idf(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 77:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauft_o_tour(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 76:
        {
            struct AUSTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , AUSTINF_BES,AUSTINF_ANZ);
            rc = AaauftSelzurauft(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUSTINF_BES, AUSTINF_ANZ);
        }
    case 75:
        {
            struct AEPWD d;
            buf_kon(FROM_UEB, (char* )&d, in , AEPWD_BES,AEPWD_ANZ);
            rc = AafilInspasswd(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AEPWD_BES, AEPWD_ANZ);
        }
    case 74:
        {
            struct PARVERSION d;
            buf_kon(FROM_UEB, (char* )&d, in , PARVERSION_BES,PARVERSION_ANZ);
            rc = AafilGetversion(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARVERSION_BES, PARVERSION_ANZ);
        }
    case 73:
        {
            struct AEPWD d;
            buf_kon(FROM_UEB, (char* )&d, in , AEPWD_BES,AEPWD_ANZ);
            rc = AafilUpdpasswd(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AEPWD_BES, AEPWD_ANZ);
        }
    case 72:
        {
            struct PARKOMMI d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOMMI_BES,PARKOMMI_ANZ);
            rc = AafilDelkommi(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOMMI_BES, PARKOMMI_ANZ);
        }
    case 71:
        {
            struct PARKOMMI d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOMMI_BES,PARKOMMI_ANZ);
            rc = AafilInskommi(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOMMI_BES, PARKOMMI_ANZ);
        }
    case 70:
        {
            struct PARKOMMI d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOMMI_BES,PARKOMMI_ANZ);
            rc = AafilUpdkommi(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOMMI_BES, PARKOMMI_ANZ);
        }
    case 69:
        {
            struct PARKOMMI d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOMMI_BES,PARKOMMI_ANZ);
            rc = AafilSelkommi(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOMMI_BES, PARKOMMI_ANZ);
        }
    case 68:
        {
            struct PARAUFBEARB d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAUFBEARB_BES,PARAUFBEARB_ANZ);
            rc = AafilDelaufbearb(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFBEARB_BES, PARAUFBEARB_ANZ);
        }
    case 67:
        {
            struct PARAUFBEARB d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAUFBEARB_BES,PARAUFBEARB_ANZ);
            rc = AafilInsaufbearb(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFBEARB_BES, PARAUFBEARB_ANZ);
        }
    case 66:
        {
            struct PARAUFBEARB d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAUFBEARB_BES,PARAUFBEARB_ANZ);
            rc = AafilUpdaufbearb(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFBEARB_BES, PARAUFBEARB_ANZ);
        }
    case 65:
        {
            struct PARAUFBEARB d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAUFBEARB_BES,PARAUFBEARB_ANZ);
            rc = AafilSelaufbearb(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFBEARB_BES, PARAUFBEARB_ANZ);
        }
    case 64:
        {
            struct PARAUFERG d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAUFERG_BES,PARAUFERG_ANZ);
            rc = AafilDelauferg(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFERG_BES, PARAUFERG_ANZ);
        }
    case 63:
        {
            struct PARAUFERG d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAUFERG_BES,PARAUFERG_ANZ);
            rc = AafilInsauferg(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFERG_BES, PARAUFERG_ANZ);
        }
    case 62:
        {
            struct PARAUFERG d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAUFERG_BES,PARAUFERG_ANZ);
            rc = AafilUpdauferg(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFERG_BES, PARAUFERG_ANZ);
        }
    case 61:
        {
            struct PARAUFERG d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAUFERG_BES,PARAUFERG_ANZ);
            rc = AafilSelauferg(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAUFERG_BES, PARAUFERG_ANZ);
        }
    case 60:
        {
            struct PARNACHRART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARNACHRART_BES,PARNACHRART_ANZ);
            rc = AafilDelnachart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARNACHRART_BES, PARNACHRART_ANZ);
        }
    case 59:
        {
            struct PARNACHRART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARNACHRART_BES,PARNACHRART_ANZ);
            rc = AafilInsnachart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARNACHRART_BES, PARNACHRART_ANZ);
        }
    case 58:
        {
            struct PARNACHRART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARNACHRART_BES,PARNACHRART_ANZ);
            rc = AafilUpdnachart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARNACHRART_BES, PARNACHRART_ANZ);
        }
    case 57:
        {
            struct PARNACHRART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARNACHRART_BES,PARNACHRART_ANZ);
            rc = AafilSelnachart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARNACHRART_BES, PARNACHRART_ANZ);
        }
    case 56:
        {
            struct PARKOBEHTYP d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOBEHTYP_BES,PARKOBEHTYP_ANZ);
            rc = AafilDelkobehtyp(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOBEHTYP_BES, PARKOBEHTYP_ANZ);
        }
    case 55:
        {
            struct PARKOBEHTYP d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOBEHTYP_BES,PARKOBEHTYP_ANZ);
            rc = AafilInskobehtyp(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOBEHTYP_BES, PARKOBEHTYP_ANZ);
        }
    case 54:
        {
            struct PARKOBEHTYP d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOBEHTYP_BES,PARKOBEHTYP_ANZ);
            rc = AafilUpdkobehtyp(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOBEHTYP_BES, PARKOBEHTYP_ANZ);
        }
    case 53:
        {
            struct PARKOBEHTYP d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOBEHTYP_BES,PARKOBEHTYP_ANZ);
            rc = AafilSelkobehtyp(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOBEHTYP_BES, PARKOBEHTYP_ANZ);
        }
    case 52:
        {
            struct PARKONGRP d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKONGRP_BES,PARKONGRP_ANZ);
            rc = AafilDelkondgr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKONGRP_BES, PARKONGRP_ANZ);
        }
    case 51:
        {
            struct PARKONGRP d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKONGRP_BES,PARKONGRP_ANZ);
            rc = AafilInskondgr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKONGRP_BES, PARKONGRP_ANZ);
        }
    case 50:
        {
            struct PARKONGRP d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKONGRP_BES,PARKONGRP_ANZ);
            rc = AafilUpdkondgr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKONGRP_BES, PARKONGRP_ANZ);
        }
    case 49:
        {
            struct PARKONGRP d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKONGRP_BES,PARKONGRP_ANZ);
            rc = AafilSelkondgr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKONGRP_BES, PARKONGRP_ANZ);
        }
    case 48:
        {
            struct PARKABAKOMB d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKABAKOMB_BES,PARKABAKOMB_ANZ);
            rc = AafilDelkabakomb(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKABAKOMB_BES, PARKABAKOMB_ANZ);
        }
    case 47:
        {
            struct PARKABAKOMB d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKABAKOMB_BES,PARKABAKOMB_ANZ);
            rc = AafilInskabakomb(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKABAKOMB_BES, PARKABAKOMB_ANZ);
        }
    case 45:
        {
            struct PARKABAKOMB d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKABAKOMB_BES,PARKABAKOMB_ANZ);
            rc = AafilSelkabakomb(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKABAKOMB_BES, PARKABAKOMB_ANZ);
        }
    case 44:
        {
            struct PARBUCHART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARBUCHART_BES,PARBUCHART_ANZ);
            rc = AafilDelbuchart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARBUCHART_BES, PARBUCHART_ANZ);
        }
    case 43:
        {
            struct PARBUCHART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARBUCHART_BES,PARBUCHART_ANZ);
            rc = AafilInsbuchart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARBUCHART_BES, PARBUCHART_ANZ);
        }
    case 42:
        {
            struct PARBUCHART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARBUCHART_BES,PARBUCHART_ANZ);
            rc = AafilUpdbuchart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARBUCHART_BES, PARBUCHART_ANZ);
        }
    case 41:
        {
            struct PARBUCHART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARBUCHART_BES,PARBUCHART_ANZ);
            rc = AafilSelbuchart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARBUCHART_BES, PARBUCHART_ANZ);
        }
    case 40:
        {
            struct PARKOART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOART_BES,PARKOART_ANZ);
            rc = AafilDelkoart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOART_BES, PARKOART_ANZ);
        }
    case 39:
        {
            struct PARKOART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOART_BES,PARKOART_ANZ);
            rc = AafilInskoart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOART_BES, PARKOART_ANZ);
        }
    case 38:
        {
            struct PARKOART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOART_BES,PARKOART_ANZ);
            rc = AafilUpdkoart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOART_BES, PARKOART_ANZ);
        }
    case 37:
        {
            struct PARKOART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARKOART_BES,PARKOART_ANZ);
            rc = AafilSelkoart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARKOART_BES, PARKOART_ANZ);
        }
    case 36:
        {
            struct PARAART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAART_BES,PARAART_ANZ);
            rc = AafilDelaart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAART_BES, PARAART_ANZ);
        }
    case 35:
        {
            struct PARAART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAART_BES,PARAART_ANZ);
            rc = AafilInsaart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAART_BES, PARAART_ANZ);
        }
    case 34:
        {
            struct PARAART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAART_BES,PARAART_ANZ);
            rc = AafilUpdaart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAART_BES, PARAART_ANZ);
        }
    case 33:
        {
            struct PARAART d;
            buf_kon(FROM_UEB, (char* )&d, in , PARAART_BES,PARAART_ANZ);
            rc = AafilSelaart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PARAART_BES, PARAART_ANZ);
        }
    case 32:
        {
            struct AEPWD d;
            buf_kon(FROM_UEB, (char* )&d, in , AEPWD_BES,AEPWD_ANZ);
            rc = AafilReadpasswd(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AEPWD_BES, AEPWD_ANZ);
        }
    case 31:
        {
            struct ARTALT d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTALT_BES,ARTALT_ANZ);
            rc = AatartSel_art_altern(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTALT_BES, ARTALT_ANZ);
        }
    case 30:
        {
            struct ARTAESEL d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTAESEL_BES,ARTAESEL_ANZ);
            rc = AatartAa_sel_artnr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTAESEL_BES, ARTAESEL_ANZ);
        }
    case 29:
        {
            struct KNDAUSKU d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDAUSKU_BES,KNDAUSKU_ANZ);
            rc = AakundeSel_ausku(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDAUSKU_BES, KNDAUSKU_ANZ);
        }
    case 27:
        {
            kndtourenS d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDTOUREN_BES,KNDTOUREN_ANZ);
            rc = AakundeSel_touren(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDTOUREN_BES, KNDTOUREN_ANZ);
        }
    case 26:
        {
            struct KNDOFFEN d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDOFFEN_BES,KNDOFFEN_ANZ);
            rc = AakundeSel_offen(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDOFFEN_BES, KNDOFFEN_ANZ);
        }
    case 25:
        {
            struct KNDAUFART d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDAUFART_BES,KNDAUFART_ANZ);
            rc = AakundeSel_aufart(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDAUFART_BES, KNDAUFART_ANZ);
        }
    case 24:
        {
            struct TM d;
            buf_kon(FROM_UEB, (char* )&d, in , TM_BES,TM_ANZ);
            rc = AafilGetdatetime(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, TM_BES, TM_ANZ);
        }
    //case 20:
    //    {
    //        struct ARTNET d;
    //        buf_kon(FROM_UEB, (char* )&d, in , ARTNET_BES,ARTNET_ANZ);
    //        rc = AatartNettoaktion(&d, error_msg);
    //        return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTNET_BES, ARTNET_ANZ);
    //    }
    //case 19:
    //    {
    //        struct ARTNAT d;
    //        buf_kon(FROM_UEB, (char* )&d, in , ARTNAT_BES,ARTNAT_ANZ);
    //        rc = AatartNatraaktion(&d, error_msg);
    //        return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTNAT_BES, ARTNAT_ANZ);
    //    }
    case 18:
        {
            struct ARTLAGER d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTLAGER_BES,ARTLAGER_ANZ);
            rc = AatartLagerinf(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTLAGER_BES, ARTLAGER_ANZ);
        }
    case 17:
        {
            struct ARTVERFALL d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTVERFALL_BES,ARTVERFALL_ANZ);
            rc = AatartInf_verfall(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTVERFALL_BES, ARTVERFALL_ANZ);
        }
    case 16:
        {
            struct ARTPREIS d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTPREIS_BES,ARTPREIS_ANZ);
            rc = AatartInf_preis(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTPREIS_BES, ARTPREIS_ANZ);
        }
    case 15:
        {
            struct FILINF d;
            buf_kon(FROM_UEB, (char* )&d, in , FILINF_BES,FILINF_ANZ);
            rc = AafilWriteOldVersion(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, FILINF_BES, FILINF_ANZ);
        }
    case 14:
        {
            struct ARTINF d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTINF_BES,ARTINF_ANZ);
            rc = AatartInf_art_nr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTINF_BES, ARTINF_ANZ);
        }
    case 13:
        {
            struct ARTSEL d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTSEL_BES,ARTSEL_ANZ);
            rc = AatartSel_mc_pkgr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTSEL_BES, ARTSEL_ANZ);
        }
    case 12:
        {
            struct ARTSEL d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTSEL_BES,ARTSEL_ANZ);
            rc = AatartSel_mc(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTSEL_BES, ARTSEL_ANZ);
        }
    case 11:
        {
            struct ARTSEL d;
            buf_kon(FROM_UEB, (char* )&d, in , ARTSEL_BES,ARTSEL_ANZ);
            rc = AatartSel_art_nr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTSEL_BES, ARTSEL_ANZ);
        }
    case 10:
        {
            struct KNDINF d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDINF_BES,KNDINF_ANZ);
            rc = AakundeSel_knd_info(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDINF_BES, KNDINF_ANZ);
        }
    case 9:
        {
            struct KNDSEL d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDSEL_BES,KNDSEL_ANZ);
            rc = AakundeSel_mc(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDSEL_BES, KNDSEL_ANZ);
        }
    case 8:
        {
            struct KNDSEL d;
            buf_kon(FROM_UEB, (char* )&d, in , KNDSEL_BES,KNDSEL_ANZ);
            rc = AakundeSel_kndnr(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDSEL_BES, KNDSEL_ANZ);
        }
    case 7:
        {
            struct FILINF d;
            buf_kon(FROM_UEB, (char* )&d, in , FILINF_BES,FILINF_ANZ);
            rc = AafilGet_filiale(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, FILINF_BES, FILINF_ANZ);
        }
    case 822:
    {
        tourdelayS d;
        buf_kon(FROM_UEB, (char* )&d, in, TOURDELAY_BES, TOURDELAY_ANZ);
        rc = AasrvSelTourDelay(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, TOURDELAY_BES, TOURDELAY_ANZ);
    }
    case 821:
    {
        deliveryadvicedocumentS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICEDOCUMENT_BES, DELIVERYADVICEDOCUMENT_ANZ);
        rc = AasrvGetBatchAdviceLink(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICEDOCUMENT_BES, DELIVERYADVICEDOCUMENT_ANZ);
    }
    case 820:
    {
        deliveryadvicedocumentS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICEDOCUMENT_BES, DELIVERYADVICEDOCUMENT_ANZ);
        rc = AasrvGetDocumentLink(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICEDOCUMENT_BES, DELIVERYADVICEDOCUMENT_ANZ);
    }
    case 819:
    {
        deliveryadvicevattotalsS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICEVATTOTALS_BES, DELIVERYADVICEVATTOTALS_ANZ);
        rc = AasrvSelDeliveryAdviceVATTotals(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICEVATTOTALS_BES, DELIVERYADVICEVATTOTALS_ANZ);
    }
    case 818:
    {
        deliveryadviceremarkS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICEREMARK_BES, DELIVERYADVICEREMARK_ANZ);
        rc = AasrvSelDeliveryAdviceRemarks(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICEREMARK_BES, DELIVERYADVICEREMARK_ANZ);
    }
    case 817:
    {
        deliveryadvicelinereturnS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICELINERETURN_BES, DELIVERYADVICELINERETURN_ANZ);
        rc = AasrvSelDeliveryAdviceLineReturn(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICELINERETURN_BES, DELIVERYADVICELINERETURN_ANZ);
    }
    case 816:
    {
        deliveryadvicelineibtlinkS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICELINEIBTLINK_BES, DELIVERYADVICELINEIBTLINK_ANZ);
        rc = AasrvSelDeliveryAdviceLineIBTLink(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICELINEIBTLINK_BES, DELIVERYADVICELINEIBTLINK_ANZ);
    }
    case 815:
    {
        deliveryadvicelinediscountsS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICELINEDISCOUNTS_BES, DELIVERYADVICELINEDISCOUNTS_ANZ);
        rc = AasrvSelDeliveryAdviceLineDiscount(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICELINEDISCOUNTS_BES, DELIVERYADVICELINEDISCOUNTS_ANZ);
    }
    case 814:
    {
        deliveryadvicelinedetailsS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICELINEDETAILS_BES, DELIVERYADVICELINEDETAILS_ANZ);
        rc = AasrvSelDeliveryAdviceLineDetails(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICELINEDETAILS_BES, DELIVERYADVICELINEDETAILS_ANZ);
    }
    case 813:
    {
        deliveryadvicelineS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICELINE_BES, DELIVERYADVICELINE_ANZ);
        rc = AasrvSelDeliveryAdviceLine(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICELINE_BES, DELIVERYADVICELINE_ANZ);
    }
    case 812:
    {
        deliveryadviceheadS d;
        buf_kon(FROM_UEB, (char* )&d, in, DELIVERYADVICEHEAD_BES, DELIVERYADVICEHEAD_ANZ);
        rc = AasrvSelDeliveryAdviceHead(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, DELIVERYADVICEHEAD_BES, DELIVERYADVICEHEAD_ANZ);
    }
    case 811:
    {
        auftragsartS d;
        buf_kon(FROM_UEB, (char* )&d, in, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
        rc = AasrvSelCscOrderType(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
    }
    case 810:
    {
        auftragsartS d;
        buf_kon(FROM_UEB, (char* )&d, in, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
        rc = AasrvDelCscOrderType(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
    }
    case 809:
    {
        auftragsartS d;
        buf_kon(FROM_UEB, (char* )&d, in, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
        rc = AasrvSelAllCscOrderType(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
    }
    case 808:
    {
        auftragsartS d;
        buf_kon(FROM_UEB, (char* )&d, in, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
        rc = AasrvInsertCscOrderType(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
    }
    case 807:
    {
        auftragsartS d;
        buf_kon(FROM_UEB, (char* )&d, in, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
        rc = AasrvUpdateCscOrderType(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAGSART_BES, AUFTRAGSART_ANZ);
    }
    case 806:
    {
        cscorderimportcsvfileS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCORDERIMPORTCSVFILE_BES, CSCORDERIMPORTCSVFILE_ANZ);
        rc = AasrvCSCOrderImport(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCORDERIMPORTCSVFILE_BES, CSCORDERIMPORTCSVFILE_ANZ);
    }
    case 805:
    {
        cscorderimportcsvcolumnsS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ);
        rc = AasrvInsertCSCOrderImportCSVColumns(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ);
    }
    case 804:
    {
        cscorderimportcsvformatsS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
        rc = AasrvUpdateCSCOrderImportCSVFormats(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
    }
    case 803:
    {
        cscorderimportcsvformatsS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
        rc = AasrvInsertCSCOrderImportCSVFormats(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
    }
    case 802:
    {
        cscorderimportcsvcolumnsS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ);
        rc = AasrvDeleteCSCOrderImportCSVColumns(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ);
    }
    case 801:
    {
        cscorderimportcsvcolumnsS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ);
        rc = AasrvGetCSCOrderImportCSVColumns(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ);
    }
    case 800:
    {
        cscorderimportfieldsS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCORDERIMPORTFIELDS_BES, CSCORDERIMPORTFIELDS_ANZ);
        rc = AasrvGetCSCOrderImportFields(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCORDERIMPORTFIELDS_BES, CSCORDERIMPORTFIELDS_ANZ);
    }
    case 799:
    {
        cscorderimportcsvformatsS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
        rc = AasrvGetCSCOrderImportCSVFormats(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
    }
    case 798:
    {
        cscorderimportcsvformatsS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
        rc = AasrvDeleteCSCOrderImportCSVFormats(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
    }
    case 797:
    {
        ordertypereservationconfigcpgS d;
        buf_kon(FROM_UEB, (char* )&d, in, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
        rc = AasrvDeleteReservationConfigcpgConfigID(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
    }
    case 796:
    {
        ordertypereservationconfigS d;
        buf_kon(FROM_UEB, (char* )&d, in, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
        rc = AasrvGetReservationConfigListByOrderType(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
    }
    case 795:
    {
        ordertypereservationconfigS d;
        buf_kon(FROM_UEB, (char* )&d, in, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
        rc = AasrvGetReservationConfigByID(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
    }
    case 794:
    {
        ordertypereservationconfigS d;
        buf_kon(FROM_UEB, (char* )&d, in, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
        rc = AasrvInsertReservationConfig(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
    }
    case 793:
    {
        ordertypereservationconfigS d;
        buf_kon(FROM_UEB, (char* )&d, in, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
        rc = AasrvUpdateReservationConfig(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
    }
    case 792:
    {
        ordertypereservationconfigS d;
        buf_kon(FROM_UEB, (char* )&d, in, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
        rc = AasrvDeleteReservationConfig(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ);
    }
    case 791:
    {
        ordertypereservationconfigcpgS d;
        buf_kon(FROM_UEB, (char* )&d, in, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
        rc = AasrvGetReservationConfigcpgListByConfigID(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
    }
    case 790:
    {
        ordertypereservationconfigcpgS d;
        buf_kon(FROM_UEB, (char* )&d, in, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
        rc = AasrvInsertReservationConfigcpg(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
    }
    case 789:
    {
        ordertypereservationconfigcpgS d;
        buf_kon(FROM_UEB, (char* )&d, in, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
        rc = AasrvDeleteReservationConfigcpg(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ);
    }
    case 788:
    {
        cscreservationtypesS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCRESERVATIONTYPES_BES, CSCRESERVATIONTYPES_ANZ);
        rc = AasrvGetCSCReservationTypeList(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCRESERVATIONTYPES_BES, CSCRESERVATIONTYPES_ANZ);
    }
    case 787:
    {
        cscreservationtypesS d;
        buf_kon(FROM_UEB, (char* )&d, in, CSCRESERVATIONTYPES_BES, CSCRESERVATIONTYPES_ANZ);
        rc = AasrvGetCSCReservationTypeByTyp(&d, error_msg);
        return handleResult(rc, (char*)&d, out, out_len, error_msg, CSCRESERVATIONTYPES_BES, CSCRESERVATIONTYPES_ANZ);
    }
    case 786:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvSpecialPosDone(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 785:
        {
            articleomgS d;
            buf_kon(FROM_UEB, (char* )&d, in, ARTICLEOMG_BES, ARTICLEOMG_ANZ);
            rc = AasrvGetOMGRebates(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTICLEOMG_BES, ARTICLEOMG_ANZ);
        }
    case 784:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvSetOriginalInvoiceNo(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 783:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvOrderSpecialPosDone(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 782:
        {
            callbackmaillinkS d;
            buf_kon(FROM_UEB, (char*)&d, in, CALLBACKMAILLINK_BES, CALLBACKMAILLINK_ANZ);
            rc = AasrvCallbackGetMailLink(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, CALLBACKMAILLINK_BES, CALLBACKMAILLINK_ANZ);
        }
    case 781:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvCloseorderDebtLimit(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 780:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvSetIVCVoucherNo(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
       }
    case 779:
        {
            struct AUFALTLAGORT d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFALTLAGORT_BES, AUFALTLAGORT_ANZ);
            rc = AasrvCheckIBTStockLevel(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFALTLAGORT_BES, AUFALTLAGORT_ANZ);
        }
    case 778:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvCancelorderDebtLimit(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 777:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvIBTOrderPosDone(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 776:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvIBTPosDone(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 775:
        {
            verbundmoeglS d;
            buf_kon(FROM_UEB, (char* )&d, in, VERBUNDMOEGL_BES, VERBUNDMOEGL_ANZ);
            rc = AasrvIBTPossible(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, VERBUNDMOEGL_BES, VERBUNDMOEGL_ANZ);
        }
    case 774:
        {
            struct AUFALTLAGORT d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFALTLAGORT_BES, AUFALTLAGORT_ANZ);
            rc = AasrvGetIBTStockLevel(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFALTLAGORT_BES, AUFALTLAGORT_ANZ);
        }
    case 773:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvSetOrderToCash(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 772:
        {
                auftragartkdS d;
                buf_kon(FROM_UEB, (char* )&d, in, AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ);
                rc = AasrvGetCustOrderType(&d,error_msg);
                return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ);
        }
    case 771: // AasrvReserveStockAbsArticleReservation
    case 770: // AasrvInserBestandArticleReservation
    case 769: // AasrvDeleteArticleReservation
    case 768: // AasrvUpdateArticleReservation
    case 767: // AasrvInsertArticleReservation
        {
            artikelreserveS d;
            buf_kon(FROM_UEB, (char* )&d, in, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
            switch (fkt_nr)
            {
                case 771: // AasrvReserveStockAbsArticleReservation
                    rc = AasrvReserveStockAbsArticleReservation(&d,error_msg);
                    break;
                case 770: // AasrvInserBestandArticleReservation
                    rc = AasrvInsertBestandArticleReservation(&d,error_msg);
                    break;
                case 769: // AasrvDeleteArticleReservation
                    rc = AasrvDeleteArticleReservation(&d,error_msg);
                    break;
                case 768: // AasrvUpdateArticleReservation
                    rc = AasrvUpdateArticleReservation(&d,error_msg);
                    break;
                case 767: // AasrvInsertArticleReservation
                    rc = AasrvInsertArticleReservation(&d,error_msg);
                    break;
                default: // how should this ever happen? (see outer switch/case)
                    rc = -1;
                    break;
            }
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTIKELRESERVE_BES, ARTIKELRESERVE_ANZ);
        }
    case 766:
        {
            sendmailS d;
            buf_kon(FROM_UEB, (char* )&d, in, SENDMAIL_BES, SENDMAIL_ANZ);
            rc = AasrvSendEMail(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, SENDMAIL_BES, SENDMAIL_ANZ);
        }
    case 765:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvGetBestTA(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 764:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvWriteProformaPos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 763:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvCheckKippzeit(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 762:
        {
            rangelistS d;
            buf_kon(FROM_UEB, (char* )&d, in, RANGELIST_BES, RANGELIST_ANZ);
            rc = AasrvGetRangesBG(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RANGELIST_BES, RANGELIST_ANZ);
        }
    case 761:
        {
            rangelistS d;
            buf_kon(FROM_UEB, (char* )&d, in, RANGELIST_BES, RANGELIST_ANZ);
            rc = AasrvGetRanges(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RANGELIST_BES, RANGELIST_ANZ);
       }
    case 760:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvSetCashRebate(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 759:
        {
            prolinkS d;
            buf_kon(FROM_UEB, (char* )&d, in, PROLINK_BES, PROLINK_ANZ);
            rc = AasrvWriteProLink(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, PROLINK_BES, PROLINK_ANZ);
        }
    case 758:
        {
            rabattorderS d;
            buf_kon(FROM_UEB, (char* )&d, in, RABATTORDER_BES, RABATTORDER_ANZ);
            rc = AasrvConfirmRO(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RABATTORDER_BES, RABATTORDER_ANZ);
        }
    case 757:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvClearZU(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 756:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvSetNatra(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 755:
        {
            rabattorderS d;
            buf_kon(FROM_UEB, (char* )&d, in, RABATTORDER_BES, RABATTORDER_ANZ);
            rc = AasrvClearROParam(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RABATTORDER_BES, RABATTORDER_ANZ);
        }
    case 754:
        {
            cstdiscaccS d;
            buf_kon(FROM_UEB, (char* )&d, in, CSTDISCACC_BES, CSTDISCACC_ANZ);
            rc = AasrvChangeROMembers(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, CSTDISCACC_BES, CSTDISCACC_ANZ);
        }
    case 753:
        {
            cstdiscaccS d;
            buf_kon(FROM_UEB, (char* )&d, in, CSTDISCACC_BES, CSTDISCACC_ANZ);
            rc = AasrvGetROMembers(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, CSTDISCACC_BES, CSTDISCACC_ANZ);
        }
    case 752:
        {
            invoicesettingsS d;
            buf_kon(FROM_UEB, (char* )&d, in, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ);
            rc = AasrvWriteInvoiceSettings(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ);
        }
    case 751:
        {
            invoicesettingsS d;
            buf_kon(FROM_UEB, (char* )&d, in, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ);
            rc = AasrvGetInvoiceSettings(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ);
        }
    case 750:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvWritePromoPos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 749:
        {
            rebatepriceS d;
            buf_kon(FROM_UEB, (char* )&d, in, REBATEPRICE_BES, REBATEPRICE_ANZ);
            rc = AasrvGetRebatePrice(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, REBATEPRICE_BES, REBATEPRICE_ANZ);
        }
    case 748:
        {
            discountanzS d;
            buf_kon(FROM_UEB, (char* )&d, in, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
            rc = AasrvGetPromotions(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
        }
    case 747:
        {
            discountanzS d;
            buf_kon(FROM_UEB, (char* )&d, in, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
            rc = AasrvGetRebates(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
        }
    case 746:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvCalcpos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 745:
        {
            rabattorderS d;
            buf_kon(FROM_UEB, (char* )&d, in, RABATTORDER_BES, RABATTORDER_ANZ);
            rc = AasrvSetROParam(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, RABATTORDER_BES, RABATTORDER_ANZ);
        }
    case 744:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvSetBTMLicense(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
       }
    case 743:
        {
            ordervaluesS d;
            buf_kon(FROM_UEB, (char* )&d, in, ORDERVALUES_BES, ORDERVALUES_ANZ);
            rc = AasrvGetOrderVals(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ORDERVALUES_BES, ORDERVALUES_ANZ);
        }
    case 742:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvProforma(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 741:
        {
            kndtourenS d;
            buf_kon(FROM_UEB, (char* )&d, in, KNDTOUREN_BES, KNDTOUREN_ANZ);
            rc = AasrvGetWeektouren(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDTOUREN_BES, KNDTOUREN_ANZ);
        }
    case 740:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvInsertReference(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 739:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvCheckReference(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 738:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvSetNoSeperate(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 737:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvSetdelayeddate(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 736:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvOpensessionNonVideo(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 735:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvWriteposition(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 734:
        {
            kndtourenS d;
            buf_kon(FROM_UEB, (char* )&d, in, KNDTOUREN_BES, KNDTOUREN_ANZ);
            rc = AasrvGettourenAufArt(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDTOUREN_BES, KNDTOUREN_ANZ);
        }
    case 733:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvWriteposNL(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 732:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvSetprintdirect(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 731:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvSeldeforalphapos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 730:
        {
            struct AUFPOSNACH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSNACH_BES, AUFPOSNACH_ANZ);
            rc = AasrvChangeKzNachBearb(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSNACH_BES, AUFPOSNACH_ANZ);
        }
    case 729:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvChangeCustomer(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 727:
        {
            struct LOCKMAN d;
            buf_kon(FROM_UEB, (char* )&d, in, LOCKMAN_BES, LOCKMAN_ANZ);
            rc = AasrvUnlock(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, LOCKMAN_BES, LOCKMAN_ANZ);
        }
    case 726:
        {
            struct AUFALTLAGORT d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFALTLAGORT_BES, AUFALTLAGORT_ANZ);
            rc = AasrvGetVerbMoegl(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFALTLAGORT_BES, AUFALTLAGORT_ANZ);
        }
    case 725:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvGetOrderInfo(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 724:
        {
            struct AUFTEXTE d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTEXTE_BES, AUFTEXTE_ANZ);
            rc = AasrvDelKopfZlnAuf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTEXTE_BES, AUFTEXTE_ANZ);
        }
    case 723:
        {
            struct AUFTEXTE d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTEXTE_BES, AUFTEXTE_ANZ);
            rc = AasrvInsKopfZlnAuf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTEXTE_BES, AUFTEXTE_ANZ);
        }
    case 722:
        {
            struct AUFTEXTE d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTEXTE_BES, AUFTEXTE_ANZ);
            rc = AasrvSelKopfZlnAuf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTEXTE_BES, AUFTEXTE_ANZ);
        }
    case 721:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvOpenInfoorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 720:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvSelposInfAuf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 719:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvInfposnr(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 718:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvWritetextpos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 717:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvChangetextpos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 716:
        {
            struct AUFSESS d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFSESS_BES, AUFSESS_ANZ);
            rc = AasrvGetsession(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFSESS_BES, AUFSESS_ANZ);
        }
    case 715:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvAnzzrorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 714:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvSelpos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 713:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvSelOrder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 712:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvChangeOrdBem(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 711:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvChangeValuta(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 710:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvChangeTour(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 709:
        {
            kndtourenS d;
            buf_kon(FROM_UEB, (char* )&d, in, KNDTOUREN_BES, KNDTOUREN_ANZ);
            rc = AasrvGettouren(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KNDTOUREN_BES, KNDTOUREN_ANZ);
        }
    case 708:
        {
            struct AUFARTES d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFARTES_BES, AUFARTES_ANZ);
            rc = AasrvGetaartes(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFARTES_BES, AUFARTES_ANZ);
       }
    case 707:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvChangepos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 706:
        {
            struct AUFPOSBUCH d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
            rc = AasrvWritepos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
        }
    case 705:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvChangeorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 704:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvCloseorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 703:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvOpenorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 702:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvNeworder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 701:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvClosesession(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
    case 700:
        {
            struct AUFTRAG d;
            buf_kon(FROM_UEB, (char* )&d, in, AUFTRAG_BES, AUFTRAG_ANZ);
            rc = AasrvOpensession(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFTRAG_BES, AUFTRAG_ANZ);
        }
	case 823:
	    {
	    	struct AUFPOSBUCH d;
	    	buf_kon(FROM_UEB, (char*)&d, in, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
	    	rc = AasrvDiscountMode(&d, error_msg);
	    	return handleResult(rc, (char*)&d, out, out_len, error_msg, AUFPOSBUCH_BES, AUFPOSBUCH_ANZ);
	    }
    default:
        sprintf(out,"FktvertFkt_selekt: %d",fkt_nr);
        *out_len=(int)strlen(out)+1;
        return -1; /* Fehler */
    }
}

int FktvertPuffer_anp (char* WriteBuf, char* ReadBuf, int /*a_lng*/)
{
    int rc;
    int out_len;
    int fkt_nr;
    static int db_open = 0;

    if (db_open == 0)
    {
        getSession().OpenDBConnection();
        db_open = 1;
    }

    sscanf(ReadBuf, "%4d", &fkt_nr);

    rc = FktvertFkt_selekt(fkt_nr, ReadBuf+4, WriteBuf+1, &out_len);

    switch (rc)
    {
    case -1:
    {
        char str[100 + 1];

        *WriteBuf = 'F';
        /* schwerwiegende Fehler werden in die Log-Datei eingetragen */
        snprintf(str, 100, "%s UID: %ld", WriteBuf + 1, UID);
        WriteLogInfo (str, rc, -1);
        break;
    }
    case -2:    /* Warnung */
        *WriteBuf = 'W';
        break;
    case -5:    /* Keine neuen Aufträge */
        *WriteBuf = 'X';
        break;
    case 1:    /* SQLNOTFOUND */
        *WriteBuf = '1', *(WriteBuf+1) = '\0';
        break;
    case 2:    /* FETCH wurde unterbrochen (max.Anzahl) */
        *WriteBuf = '2', *(WriteBuf+1) = '\0';
        break;
    case 3:    /* Warnung */
        *WriteBuf = '3'; /* schneller FETCH (perm. Schreiben in die Pipe) */
        break;
    case 4:    /* Warnung */
        *WriteBuf = '4'; /* für User gesperrter Zugriff */
        break;
    case 5:    /* Warnung */
        *WriteBuf = '5'; /* Key bereits vorhanden */
        break;
    default:
        *WriteBuf = '0';   /* normales Ergebnis (select bzw. fetch usw.) */
        break;
    }
    return out_len+1;
}

void FehlerBehandlung(int /*rc*/, char* /*error_msg*/)
{
    return;     //nase Wird noch nicht unterstützt
}

int Server(int /*FktNr*/, void* /*stru*/, struct buf_desc /*bd*/[], int /*anz*/, char* /*error_msg*/)
{
    return 0;   //nase Wird noch nicht unterstützt
}
