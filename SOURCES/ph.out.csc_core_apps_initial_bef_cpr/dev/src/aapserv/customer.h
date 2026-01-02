#ifndef __PP_CUSTOMER_H_
#define __PP_CUSTOMER_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\Customer ****/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CHAINCUSTOMERS ********************************************/

#define L_CHAINCUSTOMERS_NAMEAPO 40
#define L_CHAINCUSTOMERS_STRASSE 30
#define L_CHAINCUSTOMERS_ORT 30
#define L_CHAINCUSTOMERS_VERTRIEBSZENTRUMNR 6
#define L_CHAINCUSTOMERS_KUNDENNR 11
#define L_CHAINCUSTOMERS_MAINCSTNO 11

/* Length-Define of CHECKCUSTOMEREXIST ****************************************/

#define L_CHECKCUSTOMEREXIST_VERTRIEBSZENTRUMNR 6
#define L_CHECKCUSTOMEREXIST_KUNDENNR 11

/* Length-Define of CHECKLISTE5 ***********************************************/

#define L_CHECKLISTE5_BRANCHNO 6
#define L_CHECKLISTE5_ARTICLENO 11
#define L_CHECKLISTE5_CUSTOMERNO 11

/* Length-Define of CSTBRANCHINFO *********************************************/

#define L_CSTBRANCHINFO_BRANCHNO 6
#define L_CSTBRANCHINFO_LFDNR 11
#define L_CSTBRANCHINFO_INFOTEXT 256
#define L_CSTBRANCHINFO_DATETO 11
#define L_CSTBRANCHINFO_TIMETO 11

/* Length-Define of CSTBULGARIA ***********************************************/

#define L_CSTBULGARIA_VERTRIEBSZENTRUMNR 6
#define L_CSTBULGARIA_KUNDENNR 11
#define L_CSTBULGARIA_REBATEMETHFREESALE 6
#define L_CSTBULGARIA_REBATEMETHHEALTHF 6
#define L_CSTBULGARIA_MAINCSTNO 11

/* Length-Define of CSTBUYINGOPTIONS ******************************************/

#define L_CSTBUYINGOPTIONS_ETARTKLASSE1 5
#define L_CSTBUYINGOPTIONS_VERTRIEBSZENTRUMNR 6
#define L_CSTBUYINGOPTIONS_KUNDENNR 11
#define L_CSTBUYINGOPTIONS_KZPSYCHOSTOFFE 1

/* Length-Define of CSTDISCACC ************************************************/

#define L_CSTDISCACC_BRANCHNO 6
#define L_CSTDISCACC_CUSTOMERNO 11
#define L_CSTDISCACC_MAINCSTNO 11
#define L_CSTDISCACC_DATUM 11
#define L_CSTDISCACC_BALANCE 11
#define N_CSTDISCACC_BALANCE 2
#define L_CSTDISCACC_UPD_FLAG 1
#define L_CSTDISCACC_KDAUFTRAGNR 11
#define L_CSTDISCACC_DATE 11
#define L_CSTDISCACC_INVOICENUMBER 15
#define L_CSTDISCACC_INVOICEAMOUNT 11
#define N_CSTDISCACC_INVOICEAMOUNT 2
#define L_CSTDISCACC_VOUCHERTYP 2
#define L_CSTDISCACC_PREIS_TYP 6
#define L_CSTDISCACC_PRIORITY 6
#define L_CSTDISCACC_KDAUFTRAGNRSPLIT 11
#define L_CSTDISCACC_INVOICEPAID 11
#define N_CSTDISCACC_INVOICEPAID 2
#define L_CSTDISCACC_PAYMENTARGET 6
#define L_CSTDISCACC_LFDNR 11

/* Length-Define of CSTDISCACCANZ *********************************************/

#define L_CSTDISCACCANZ_BRANCHNO 6
#define L_CSTDISCACCANZ_CUSTOMERNO 11
#define L_CSTDISCACCANZ_MAINCSTNO 11
#define L_CSTDISCACCANZ_NAMEAPO 40
#define L_CSTDISCACCANZ_STRASSE 30
#define L_CSTDISCACCANZ_ORT 30

/* Length-Define of CSTDISCCONT ***********************************************/

#define L_CSTDISCCONT_BRANCHNO 6
#define L_CSTDISCCONT_CUSTOMERNO 11
#define L_CSTDISCCONT_ORDER_TYPE 2
#define L_CSTDISCCONT_PHARMACYGROUPID 3
#define L_CSTDISCCONT_SUB_ORDER_TYPE 3
#define L_CSTDISCCONT_PAYMENT_TERM 4
#define L_CSTDISCCONT_VALUTA_DAYS 6
#define L_CSTDISCCONT_MIN_ORDER_VALUE 9
#define N_CSTDISCCONT_MIN_ORDER_VALUE 2
#define L_CSTDISCCONT_MIN_TUBES 6
#define L_CSTDISCCONT_LOSS_IN_DISCOUNT 5
#define N_CSTDISCCONT_LOSS_IN_DISCOUNT 2
#define L_CSTDISCCONT_UPD_FLAG 1

/* Length-Define of CSTPAYTERM ************************************************/

#define L_CSTPAYTERM_BRANCHNO 6
#define L_CSTPAYTERM_CUSTOMERNO 11
#define L_CSTPAYTERM_PREIS_TYP 6
#define L_CSTPAYTERM_PAYMENTARGET 6

/* Length-Define of CSTREBATETYPE *********************************************/

#define L_CSTREBATETYPE_VERTRIEBSZENTRUMNR 6
#define L_CSTREBATETYPE_KUNDENNR 11
#define L_CSTREBATETYPE_REBATEMETHFREESALE 6
#define L_CSTREBATETYPE_REBATEMETHHEALTHF 6

/* Length-Define of CUSTPHARMA ************************************************/

#define L_CUSTPHARMA_CUSTOMERNO 11
#define L_CUSTPHARMA_BRANCHNO 6
#define L_CUSTPHARMA_PHARMACYGROUPID 3
#define L_CUSTPHARMA_RANKING 6

/* Length-Define of CUSTPHON **************************************************/

#define L_CUSTPHON_VERTRIEBSZENTRUMNR 6
#define L_CUSTPHON_KUNDENNR 11
#define L_CUSTPHON_TELNR 20
#define L_CUSTPHON_DATUM 11

/* Length-Define of CUSTROUT **************************************************/

#define L_CUSTROUT_CUSTOMERNO 11
#define L_CUSTROUT_BRANCHNO 6
#define L_CUSTROUT_TIMEFROM 11
#define L_CUSTROUT_TIMETO 11
#define L_CUSTROUT_DESTBRANCHNO 6
#define L_CUSTROUT_DAYOFWEEK 2
#define L_CUSTROUT_WEEKDAY 6
#define L_CUSTROUT_ZEIT_VON 11

/* Length-Define of CUSTOMERDOUBLES *******************************************/

#define L_CUSTOMERDOUBLES_NAME 30
#define L_CUSTOMERDOUBLES_VERTRIEBSZENTRUMNR 6
#define L_CUSTOMERDOUBLES_KUNDENNR 11

/* Length-Define of DISTRESSROUTING *******************************************/

#define L_DISTRESSROUTING_BRANCHNO 6
#define L_DISTRESSROUTING_CUSTOMERNO 11
#define L_DISTRESSROUTING_DESTBRANCHNO 6
#define L_DISTRESSROUTING_NAMEAPO 40
#define L_DISTRESSROUTING_ORT 30
#define L_DISTRESSROUTING_POSTLEITZAHL 10
#define L_DISTRESSROUTING_PERSONALNRVERTR 11
#define L_DISTRESSROUTING_KZKDKLASSE 3

/* Length-Define of ENCLOSERTIMES *********************************************/

#define L_ENCLOSERTIMES_BRANCHNO 6
#define L_ENCLOSERTIMES_CUSTOMERNO 11
#define L_ENCLOSERTIMES_TIMEDIFF 6
#define L_ENCLOSERTIMES_MAXPOSITIONS 6
#define L_ENCLOSERTIMES_KUNDENNR 11

/* Length-Define of KNDTOURFENSTER ********************************************/

#define L_KNDTOURFENSTER_CUSTOMERNO 11
#define L_KNDTOURFENSTER_TOURID 6
#define L_KNDTOURFENSTER_BRANCHNO 6
#define L_KNDTOURFENSTER_WEEKDAY 6
#define L_KNDTOURFENSTER_FROMTIME 11
#define L_KNDTOURFENSTER_TOTIME 11
#define L_KNDTOURFENSTER_MAINTIME 11

/* Length-Define of KNDTOURWOCHE **********************************************/

#define L_KNDTOURWOCHE_VERTRIEBSZENTRUMNR 6
#define L_KNDTOURWOCHE_KUNDENNR 11
#define L_KNDTOURWOCHE_WEEKDAY 6
#define L_KNDTOURWOCHE_ISTVERBUNDTOUR 1
#define L_KNDTOURWOCHE_KDAUFTRAGART 2
#define L_KNDTOURWOCHE_ISBTM 6
#define L_KNDTOURWOCHE_ISKK 6
#define L_KNDTOURWOCHE_ISK08 6
#define L_KNDTOURWOCHE_ISK20 6
#define L_KNDTOURWOCHE_PHARMACYLOCKACCESS 6
#define L_KNDTOURWOCHE_REMARKLACKITEMPROCESSING 40
#define L_KNDTOURWOCHE_RETURNSTOUR 6
#define L_KNDTOURWOCHE_REMARKLACKCALLBACK 40
#define L_KNDTOURWOCHE_TRANSPEXCLPSYCHO 6
#define L_KNDTOURWOCHE_TRANSPEXCLCOOLED 6
#define L_KNDTOURWOCHE_TRANSPEXCLEXPENSIVE 6
#define L_KNDTOURWOCHE_CHECKPOSITIONS 6
#define L_KNDTOURWOCHE_CHECKREMARK 40
#define L_KNDTOURWOCHE_PLANNEDCALL 11
#define L_KNDTOURWOCHE_KZAUTOZUORD 1
#define L_KNDTOURWOCHE_SCHECKORDER 6
#define L_KNDTOURWOCHE_CHECKTIMETOTOUR 6
#define L_KNDTOURWOCHE_BEMERKUNGEN 240
#define L_KNDTOURWOCHE_TOURID 6
#define L_KNDTOURWOCHE_TAGESTYP 6

/* Length-Define of KNDTOURWOCHE2 *********************************************/

#define L_KNDTOURWOCHE2_VERTRIEBSZENTRUMNR 6
#define L_KNDTOURWOCHE2_KUNDENNR 11
#define L_KNDTOURWOCHE2_TOURID 6
#define L_KNDTOURWOCHE2_DATUMKOMMI 11
#define L_KNDTOURWOCHE2_CONSTIME 11

/* Length-Define of KNDTOURWOCHE3 *********************************************/

#define L_KNDTOURWOCHE3_FILIALNR 6
#define L_KNDTOURWOCHE3_TOURID 6
#define L_KNDTOURWOCHE3_DATUMKOMMI 11
#define L_KNDTOURWOCHE3_CONSTIME 11

/* Length-Define of KNDFILINFO ************************************************/

#define L_KNDFILINFO_KUNDENNR 11
#define L_KNDFILINFO_VERTRIEBSZENTRUMNR 6
#define L_KNDFILINFO_DISPOGEBUEHR 5
#define N_KNDFILINFO_DISPOGEBUEHR 2
#define L_KNDFILINFO_BTMGEBUEHR 5
#define N_KNDFILINFO_BTMGEBUEHR 2
#define L_KNDFILINFO_DOKUGEBUEHR 5
#define N_KNDFILINFO_DOKUGEBUEHR 2
#define L_KNDFILINFO_TOURENKIPPZEIT 11

/* Length-Define of KNDFILINFO2 ***********************************************/

#define L_KNDFILINFO2_FILIALNR 6
#define L_KNDFILINFO2_DURCHLAUFNORMAL 11
#define L_KNDFILINFO2_DURCHLAUFEILBOTE 11
#define L_KNDFILINFO2_TOURVERSPAETUNG 11
#define L_KNDFILINFO2_TOURENKIPPZEIT 11

/* Length-Define of KREDITLIMIT ***********************************************/

#define L_KREDITLIMIT_PARTNERNO 11
#define L_KREDITLIMIT_PARTNERNAME 30
#define L_KREDITLIMIT_LIMIT 13
#define N_KREDITLIMIT_LIMIT 2
#define L_KREDITLIMIT_SUM_DEBITSIDE 13
#define N_KREDITLIMIT_SUM_DEBITSIDE 2
#define L_KREDITLIMIT_SUM_CREDITSIDE 13
#define N_KREDITLIMIT_SUM_CREDITSIDE 2
#define L_KREDITLIMIT_SUM_MONTURNOVER 13
#define N_KREDITLIMIT_SUM_MONTURNOVER 2
#define L_KREDITLIMIT_SUM_DAYTURNOVER 13
#define N_KREDITLIMIT_SUM_DAYTURNOVER 2
#define L_KREDITLIMIT_SUM_RETURNS 13
#define N_KREDITLIMIT_SUM_RETURNS 2
#define L_KREDITLIMIT_SUM_GOODSRECEIPT 13
#define N_KREDITLIMIT_SUM_GOODSRECEIPT 2
#define L_KREDITLIMIT_LIMITTYPE 6
#define L_KREDITLIMIT_LISTE5 1
#define L_KREDITLIMIT_VERTRIEBSZENTRUMNR 6
#define L_KREDITLIMIT_KUNDENNR 11

/* Length-Define of KUNDELIZENSEN *********************************************/

#define L_KUNDELIZENSEN_VERTRIEBSZENTRUMNR 6
#define L_KUNDELIZENSEN_KUNDENNR 11
#define L_KUNDELIZENSEN_APOLIZENS 20
#define L_KUNDELIZENSEN_BTMLIZENS 20

/* Length-Define of KUNDEVERBUNDFILIALE ***************************************/

#define L_KUNDEVERBUNDFILIALE_VERTRIEBSZENTRUMNR 6
#define L_KUNDEVERBUNDFILIALE_KUNDENNR 11
#define L_KUNDEVERBUNDFILIALE_REIHENFOLGENR 11
#define L_KUNDEVERBUNDFILIALE_VERBUNDFILIALNR 6

/* Length-Define of LISTE5 ****************************************************/

#define L_LISTE5_BRANCHNO 6
#define L_LISTE5_ARTICLENO 11
#define L_LISTE5_PREISEKAPO 9
#define N_LISTE5_PREISEKAPO 2
#define L_LISTE5_CUSTOMERNO 11
#define L_LISTE5_PREIS_TYP 6
#define L_LISTE5_TAXLEVEL 6
#define L_LISTE5_ARTIKEL_LANGNAME 50

/* Length-Define of MCUSTOMEREMERGENCYSERVICEPLAN *****************************/

#define L_MCUSTOMEREMERGENCYSERVICEPLAN_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMEREMERGENCYSERVICEPLAN_KUNDENNR 11
#define L_MCUSTOMEREMERGENCYSERVICEPLAN_DATUM 11
#define L_MCUSTOMEREMERGENCYSERVICEPLAN_UHRZEITVON 11
#define L_MCUSTOMEREMERGENCYSERVICEPLAN_UHRZEITBIS 11
#define L_MCUSTOMEREMERGENCYSERVICEPLAN_BEMERKUNGEN 240
#define L_MCUSTOMEREMERGENCYSERVICEPLAN_ISBTM 6
#define L_MCUSTOMEREMERGENCYSERVICEPLAN_ISKK 6
#define L_MCUSTOMEREMERGENCYSERVICEPLAN_ISK08 6
#define L_MCUSTOMEREMERGENCYSERVICEPLAN_ISK20 6

/* Length-Define of MCUSTOMERVACATION *****************************************/

#define L_MCUSTOMERVACATION_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERVACATION_KUNDENNR 11
#define L_MCUSTOMERVACATION_DATUMGUELTIGAB 11
#define L_MCUSTOMERVACATION_DATUMGUELTIGBIS 11

/* Length-Define of PAYTERM ***************************************************/

#define L_PAYTERM_PAYMENT_TERM 4
#define L_PAYTERM_PAYMENTARGET 6
#define L_PAYTERM_CASHDISOUNT 5
#define N_PAYTERM_CASHDISOUNT 2
#define L_PAYTERM_VERTRIEBSZENTRUMNR 6
#define L_PAYTERM_KUNDENNR 11

/* Length-Define of PAYMENTLIST ***********************************************/

#define L_PAYMENTLIST_BRANCHNO 6
#define L_PAYMENTLIST_CUSTOMERNO 11
#define L_PAYMENTLIST_INVOICENUMBER 15
#define L_PAYMENTLIST_TOTALINVOICEAMOUNT 11
#define N_PAYMENTLIST_TOTALINVOICEAMOUNT 2
#define L_PAYMENTLIST_OPENINVOICEAMOUNT 11
#define N_PAYMENTLIST_OPENINVOICEAMOUNT 2
#define L_PAYMENTLIST_PAIDINVOICEAMOUNT 11
#define N_PAYMENTLIST_PAIDINVOICEAMOUNT 2
#define L_PAYMENTLIST_DRIVERID 11
#define L_PAYMENTLIST_PAYMENTDATE 11
#define L_PAYMENTLIST_INVOICEDATE 11
#define L_PAYMENTLIST_PAYMENTSPEC 1

/* Length-Define of PREWHOLECST ***********************************************/

#define L_PREWHOLECST_VERTRIEBSZENTRUMNR 6
#define L_PREWHOLECST_KUNDENNR 11
#define L_PREWHOLECST_MAINCSTNO 11

/* Length-Define of SHIPAUXNO *************************************************/

#define L_SHIPAUXNO_BRANCHNO 6
#define L_SHIPAUXNO_CUSTOMERNO 11
#define L_SHIPAUXNO_AUXBRANCHNO 6
#define L_SHIPAUXNO_AUXBGANO 11

/* Length-Define of TOURPFLEGE ************************************************/

#define L_TOURPFLEGE_TOURID 6
#define L_TOURPFLEGE_REIHENFOLGENR 11
#define L_TOURPFLEGE_FAHRTZEIT 11
#define L_TOURPFLEGE_BEMERKUNGEN 240
#define L_TOURPFLEGE_VERTRIEBSZENTRUMNR 6
#define L_TOURPFLEGE_KUNDENNR 11
#define L_TOURPFLEGE_TM_DATE 11
#define L_TOURPFLEGE_TM_TIME 11
#define L_TOURPFLEGE_LOGINID 11
#define L_TOURPFLEGE_CHANGEID 1
#define L_TOURPFLEGE_KOART 1

/* Length-Define of DELAYEDCST ************************************************/

#define L_DELAYEDCST_BRANCHNO 6
#define L_DELAYEDCST_CUSTOMERNO 11
#define L_DELAYEDCST_WEEKDAY 6
#define L_DELAYEDCST_TIME 11
#define L_DELAYEDCST_TOURID 6
#define L_DELAYEDCST_ACTIV 1
#define L_DELAYEDCST_DELAYEDWEEKDAY 6
#define L_DELAYEDCST_NARCOTIC 1
#define L_DELAYEDCST_COLDCHAIN 1
#define L_DELAYEDCST_COOL08 1
#define L_DELAYEDCST_COOL20 1

/* Length-Define of DELAYEDDELIVERYCSTSPECIAL *********************************/

#define L_DELAYEDDELIVERYCSTSPECIAL_BRANCHNO 6
#define L_DELAYEDDELIVERYCSTSPECIAL_CUSTOMERNO 11
#define L_DELAYEDDELIVERYCSTSPECIAL_WEEKDAY 6
#define L_DELAYEDDELIVERYCSTSPECIAL_TIME 11
#define L_DELAYEDDELIVERYCSTSPECIAL_ACTIV 1
#define L_DELAYEDDELIVERYCSTSPECIAL_DELAYEDWEEKDAY 6
#define L_DELAYEDDELIVERYCSTSPECIAL_NARCOTIC 1
#define L_DELAYEDDELIVERYCSTSPECIAL_COLDCHAIN 1
#define L_DELAYEDDELIVERYCSTSPECIAL_COOL08 1
#define L_DELAYEDDELIVERYCSTSPECIAL_COOL20 1
#define L_DELAYEDDELIVERYCSTSPECIAL_DATEFROM 11
#define L_DELAYEDDELIVERYCSTSPECIAL_DATETO 11

/* SqlDefine of CHAINCUSTOMERS ************************************************/


#define CHAINCUSTOMERS_PLISTE \
        "KUNDE.NAMEAPO,"\
        "KUNDE.STRASSE,"\
        "KUNDE.ORT,"\
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR,"\
        "KUNDE.MAINCSTNO"

/* SqlDefine of CHECKCUSTOMEREXIST ********************************************/


#define CHECKCUSTOMEREXIST_PLISTE \
        "KUNDESCHALTER.VERTRIEBSZENTRUMNR,"\
        "KUNDESCHALTER.KUNDENNR"

/* SqlDefine of CHECKLISTE5 ***************************************************/


#define CHECKLISTE5_PLISTE \
        "DISCOUNTGRP.BRANCHNO,"\
        "DISCOUNTGRPMEM.ARTICLENO,"\
        "DISCOUNTGRP.CUSTOMERNO"

/* SqlDefine of CSTBRANCHINFO *************************************************/


#define CSTBRANCHINFO_PLISTE \
        "CSTBRANCHINFO.BRANCHNO,"\
        "CSTBRANCHINFO.LFDNR,"\
        "CSTBRANCHINFO.INFOTEXT,"\
        "CSTBRANCHINFO.DATETO,"\
        "CSTBRANCHINFO.TIMETO"

/* SqlDefine of CSTBULGARIA ***************************************************/


#define CSTBULGARIA_PLISTE \
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR,"\
        "KUNDE.REBATEMETHFREESALE,"\
        "KUNDE.REBATEMETHHEALTHF,"\
        "KUNDE.MAINCSTNO"

/* SqlDefine of CSTBUYINGOPTIONS **********************************************/


#define CSTBUYINGOPTIONS_PLISTE \
        "KUNDE.ETARTKLASSE1,"\
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR,"\
        "KUNDE.KZPSYCHOSTOFFE"

/* SqlDefine of CSTDISCACC ****************************************************/


#define CSTDISCACC_PLISTE \
        "CSTDISCACC.BRANCHNO,"\
        "CSTDISCACC.CUSTOMERNO,"\
        "CSTDISCACC.MAINCSTNO,"\
        "CSTDISCACC.BALANCE,"\
        "CSTDISCACC.UPD_FLAG,"\
        "CSTDISCACC.KDAUFTRAGNR,"\
        "CSTDISCACC.DATE,"\
        "CSTDISCACC.INVOICENUMBER,"\
        "CSTDISCACC.INVOICEAMOUNT,"\
        "CSTDISCACC.VOUCHERTYP,"\
        "CSTDISCACC.PREIS_TYP,"\
        "CSTDISCACC.PRIORITY,"\
        "CSTDISCACC.KDAUFTRAGNRSPLIT,"\
        "CSTDISCACC.INVOICEPAID,"\
        "CSTDISCACC.PAYMENTARGET,"\
        "CSTDISCACC.LFDNR"

/* SqlDefine of CSTDISCACCANZ *************************************************/


#define CSTDISCACCANZ_PLISTE \
        "CSTDISCACC.BRANCHNO,"\
        "CSTDISCACC.CUSTOMERNO,"\
        "CSTDISCACC.MAINCSTNO,"\
        "KUNDE.NAMEAPO,"\
        "KUNDE.STRASSE,"\
        "KUNDE.ORT"

/* SqlDefine of CSTDISCCONT ***************************************************/


#define CSTDISCCONT_PLISTE \
        "CSTDISCOUNTCONT.BRANCHNO,"\
        "CSTDISCOUNTCONT.CUSTOMERNO,"\
        "CSTDISCOUNTCONT.ORDER_TYPE,"\
        "DISCOUNTLIST.PHARMACYGROUPID,"\
        "CSTDISCOUNTCONT.SUB_ORDER_TYPE,"\
        "CSTDISCOUNTCONT.PAYMENT_TERM,"\
        "CSTDISCOUNTCONT.VALUTA_DAYS,"\
        "CSTDISCOUNTCONT.MIN_ORDER_VALUE,"\
        "CSTDISCOUNTCONT.MIN_TUBES,"\
        "CSTDISCOUNTCONT.LOSS_IN_DISCOUNT,"\
        "CSTDISCOUNTCONT.UPD_FLAG"

/* SqlDefine of CSTPAYTERM ****************************************************/


#define CSTPAYTERM_PLISTE \
        "CSTPAYMENTTERMS.BRANCHNO,"\
        "CSTPAYMENTTERMS.CUSTOMERNO,"\
        "CSTPAYMENTTERMS.PREIS_TYP,"\
        "CSTPAYMENTTERMS.PAYMENTARGET"

/* SqlDefine of CSTREBATETYPE *************************************************/


#define CSTREBATETYPE_PLISTE \
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR,"\
        "KUNDE.REBATEMETHFREESALE,"\
        "KUNDE.REBATEMETHHEALTHF"

/* SqlDefine of CUSTPHARMA ****************************************************/


#define CUSTPHARMA_PLISTE \
        "CUSTOMERPHARMACYGR.CUSTOMERNO,"\
        "CUSTOMERPHARMACYGR.BRANCHNO,"\
        "CUSTOMERPHARMACYGR.PHARMACYGROUPID,"\
        "CUSTOMERPHARMACYGR.RANKING"

/* SqlDefine of CUSTPHON ******************************************************/


#define CUSTPHON_PLISTE \
        "CUSTOMERPHONENO.VERTRIEBSZENTRUMNR,"\
        "CUSTOMERPHONENO.KUNDENNR,"\
        "CUSTOMERPHONENO.TELNR,"\
        "CUSTOMERPHONENO.DATUM"

/* SqlDefine of CUSTROUT ******************************************************/


#define CUSTROUT_PLISTE \
        "CUSTOMERROUTING.CUSTOMERNO,"\
        "CUSTOMERROUTING.BRANCHNO,"\
        "CUSTOMERROUTING.TIMEFROM,"\
        "CUSTOMERROUTING.TIMETO,"\
        "CUSTOMERROUTING.DESTBRANCHNO,"\
        "CUSTOMERROUTING.DAYOFWEEK,"\
        "CUSTOMERROUTING.WEEKDAY"

/* SqlDefine of CUSTOMERDOUBLES ***********************************************/


#define CUSTOMERDOUBLES_PLISTE \
        "FILIALE.NAME,"\
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR"

/* SqlDefine of DISTRESSROUTING ***********************************************/


#define DISTRESSROUTING_PLISTE \
        "DISTRESSROUTING.BRANCHNO,"\
        "DISTRESSROUTING.CUSTOMERNO,"\
        "DISTRESSROUTING.DESTBRANCHNO,"\
        "KUNDE.NAMEAPO,"\
        "KUNDE.ORT,"\
        "KUNDE.POSTLEITZAHL,"\
        "KUNDE.PERSONALNRVERTR,"\
        "KUNDE.KZKDKLASSE"

/* SqlDefine of ENCLOSERTIMES *************************************************/


#define ENCLOSERTIMES_PLISTE \
        "ENCLOSERSCALE.BRANCHNO,"\
        "ENCLOSERSCALE.CUSTOMERNO,"\
        "ENCLOSERSCALE.TIMEDIFF,"\
        "ENCLOSERSCALE.MAXPOSITIONS"

/* SqlDefine of KNDTOURFENSTER ************************************************/


#define KNDTOURFENSTER_PLISTE \
        "ORDERPERIOD.CUSTOMERNO,"\
        "ORDERPERIOD.TOURID,"\
        "ORDERPERIOD.BRANCHNO,"\
        "ORDERPERIOD.WEEKDAY,"\
        "ORDERPERIODTIME.FROMTIME,"\
        "ORDERPERIODTIME.TOTIME,"\
        "ORDERPERIODTIME.MAINTIME"

/* SqlDefine of KNDTOURWOCHE **************************************************/


#define KNDTOURWOCHE_PLISTE \
        "TOURPLANTAGWOCHE.VERTRIEBSZENTRUMNR,"\
        "TOURPLANTAGWOCHE.KUNDENNR,"\
        "TOURPLANTAGWOCHE.WEEKDAY,"\
        "TOURPLANTAGWOCHE.ISTVERBUNDTOUR,"\
        "TOURPLANTAGWOCHE.KDAUFTRAGART,"\
        "TOURPLANTAGWOCHE.ISBTM,"\
        "TOURPLANTAGWOCHE.ISKK,"\
        "TOURPLANTAGWOCHE.ISK08,"\
        "TOURPLANTAGWOCHE.ISK20,"\
        "CUSTOMERTOURDETAILS.PHARMACYLOCKACCESS,"\
        "CUSTOMERTOURDETAILS.REMARKLACKITEMPROCESSING,"\
        "TOURPLANTAGWOCHE.RETURNSTOUR,"\
        "CUSTOMERTOURDETAILS.REMARKLACKCALLBACK,"\
        "TOURPLANTAGWOCHE.TRANSPEXCLPSYCHO,"\
        "TOURPLANTAGWOCHE.TRANSPEXCLCOOLED,"\
        "TOURPLANTAGWOCHE.TRANSPEXCLEXPENSIVE,"\
        "TOURPLANTAGWOCHE.CHECKPOSITIONS,"\
        "TOURPLANTAGWOCHE.CHECKREMARK,"\
        "TOURPLANTAGWOCHE.PLANNEDCALL,"\
        "TOURPLANTAGWOCHE.KZAUTOZUORD,"\
        "TOURPLANTAGWOCHE.SCHECKORDER,"\
        "TOURPLANTAGWOCHE.CHECKTIMETOTOUR,"\
        "TOURPLANTAGWOCHE.BEMERKUNGEN,"\
        "TOURPLANWOCHE.TOURID,"\
        "TOURPLANWOCHE.TAGESTYP"

/* SqlDefine of KNDTOURWOCHE2 *************************************************/


#define KNDTOURWOCHE2_PLISTE \
        "TOURPLANCONSTIME.VERTRIEBSZENTRUMNR,"\
        "TOURPLANCONSTIME.KUNDENNR,"\
        "TOURPLANCONSTIME.TOURID,"\
        "TOURPLANCONSTIME.DATUMKOMMI,"\
        "TOURPLANCONSTIME.CONSTIME"

/* SqlDefine of KNDTOURWOCHE3 *************************************************/


#define KNDTOURWOCHE3_PLISTE \
        "TOURCONSTIME.FILIALNR,"\
        "TOURCONSTIME.TOURID,"\
        "TOURCONSTIME.DATUMKOMMI,"\
        "TOURCONSTIME.CONSTIME"

/* SqlDefine of KNDFILINFO ****************************************************/


#define KNDFILINFO_PLISTE \
        "KNDAUSKU.KUNDENNR,"\
        "KNDAUSKU.VERTRIEBSZENTRUMNR,"\
        "KNDAUSKU.DISPOGEBUEHR,"\
        "KNDAUSKU.BTMGEBUEHR,"\
        "KNDAUSKU.DOKUGEBUEHR,"\
        "KUNDE.TOURENKIPPZEIT"

/* SqlDefine of KNDFILINFO2 ***************************************************/


#define KNDFILINFO2_PLISTE \
        "PARAAUFTRAGBEARB.FILIALNR,"\
        "PARAAUFTRAGBEARB.DURCHLAUFNORMAL,"\
        "PARAAUFTRAGBEARB.DURCHLAUFEILBOTE,"\
        "PARAAUFTRAGBEARB.TOURVERSPAETUNG,"\
        "PARAAUFTRAGBEARB.TOURENKIPPZEIT"

/* SqlDefine of KREDITLIMIT ***************************************************/


#define KREDITLIMIT_PLISTE \
        "DEBTLIMIT.PARTNERNO,"\
        "DEBTLIMIT.PARTNERNAME,"\
        "DEBTLIMIT.LIMIT,"\
        "DEBTLIMIT.SUM_DEBITSIDE,"\
        "DEBTLIMIT.SUM_CREDITSIDE,"\
        "DEBTLIMIT.SUM_MONTURNOVER,"\
        "DEBTLIMIT.SUM_DAYTURNOVER,"\
        "DEBTLIMIT.SUM_RETURNS,"\
        "DEBTLIMIT.SUM_GOODSRECEIPT,"\
        "DEBTLIMIT.LIMITTYPE,"\
        "DEBTLIMIT.LISTE5,"\
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR"

/* SqlDefine of KUNDELIZENSEN *************************************************/


#define KUNDELIZENSEN_PLISTE \
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR,"\
        "KUNDE.APOLIZENS,"\
        "KUNDE.BTMLIZENS"

/* SqlDefine of KUNDEVERBUNDFILIALE *******************************************/


#define KUNDEVERBUNDFILIALE_PLISTE \
        "KDVERBUNDFILIALE.VERTRIEBSZENTRUMNR,"\
        "KDVERBUNDFILIALE.KUNDENNR,"\
        "KDVERBUNDFILIALE.REIHENFOLGENR,"\
        "KDVERBUNDFILIALE.VERBUNDFILIALNR"

/* SqlDefine of LISTE5 ********************************************************/


#define LISTE5_PLISTE \
        "DISCOUNTGRP.BRANCHNO,"\
        "DISCOUNTGRPMEM.ARTICLENO,"\
        "ARTIKELPREIS.PREISEKAPO,"\
        "DISCOUNTGRP.CUSTOMERNO,"\
        "ARTIKELPREIS.PREIS_TYP,"\
        "ARTIKELZENTRAL.TAXLEVEL,"\
        "ARTIKELZENTRAL.ARTIKEL_LANGNAME"

/* SqlDefine of MCUSTOMEREMERGENCYSERVICEPLAN *********************************/


#define MCUSTOMEREMERGENCYSERVICEPLAN_PLISTE \
        "KUNDENOTDIENSTPLAN.VERTRIEBSZENTRUMNR,"\
        "KUNDENOTDIENSTPLAN.KUNDENNR,"\
        "KUNDENOTDIENSTPLAN.DATUM,"\
        "KUNDENOTDIENSTPLAN.UHRZEITVON,"\
        "KUNDENOTDIENSTPLAN.UHRZEITBIS,"\
        "KUNDENOTDIENSTPLAN.BEMERKUNGEN,"\
        "KUNDENOTDIENSTPLAN.ISBTM,"\
        "KUNDENOTDIENSTPLAN.ISKK,"\
        "KUNDENOTDIENSTPLAN.ISK08,"\
        "KUNDENOTDIENSTPLAN.ISK20"

/* SqlDefine of MCUSTOMERVACATION *********************************************/


#define MCUSTOMERVACATION_PLISTE \
        "KUNDEURLAUB.VERTRIEBSZENTRUMNR,"\
        "KUNDEURLAUB.KUNDENNR,"\
        "KUNDEURLAUB.DATUMGUELTIGAB,"\
        "KUNDEURLAUB.DATUMGUELTIGBIS"

/* SqlDefine of PAYTERM *******************************************************/


#define PAYTERM_PLISTE \
        "PAYMENTTERMS.PAYMENT_TERM,"\
        "PAYMENTTERMS.PAYMENTARGET,"\
        "PAYMENTTERMS.CASHDISOUNT"

/* SqlDefine of PAYMENTLIST ***************************************************/


#define PAYMENTLIST_PLISTE \
        "CSTPAYMENTLIST.BRANCHNO,"\
        "CSTPAYMENTLIST.CUSTOMERNO,"\
        "CSTPAYMENTLIST.INVOICENUMBER,"\
        "CSTPAYMENTLIST.TOTALINVOICEAMOUNT,"\
        "CSTPAYMENTLIST.OPENINVOICEAMOUNT,"\
        "CSTPAYMENTLIST.PAIDINVOICEAMOUNT,"\
        "CSTPAYMENTLIST.DRIVERID,"\
        "CSTPAYMENTLIST.PAYMENTDATE,"\
        "CSTPAYMENTLIST.INVOICEDATE,"\
        "CSTPAYMENTLIST.PAYMENTSPEC"

/* SqlDefine of PREWHOLECST ***************************************************/


#define PREWHOLECST_PLISTE \
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR,"\
        "KUNDE.MAINCSTNO"

/* SqlDefine of SHIPAUXNO *****************************************************/


#define SHIPAUXNO_PLISTE \
        "SHIPAUXNO.BRANCHNO,"\
        "SHIPAUXNO.CUSTOMERNO,"\
        "SHIPAUXNO.AUXBRANCHNO,"\
        "SHIPAUXNO.AUXBGANO"

/* SqlDefine of TOURPFLEGE ****************************************************/


#define TOURPFLEGE_PLISTE \
        "TOURPLANTAG.TOURID,"\
        "TOURPLANTAG.REIHENFOLGENR,"\
        "TOURPLANTAG.FAHRTZEIT,"\
        "TOURPLANTAG.BEMERKUNGEN,"\
        "TOURPLANTAG.VERTRIEBSZENTRUMNR,"\
        "TOURPLANTAG.KUNDENNR,"\
        "TOURPLANTAG.TM_DATE,"\
        "TOURPLANTAG.TM_TIME,"\
        "TOURPLANTAG.LOGINID,"\
        "TOURPLANTAG.CHANGEID,"\
        "TOURPLANTAG.KOART"

/* SqlDefine of DELAYEDCST ****************************************************/


#define DELAYEDCST_PLISTE \
        "DELAYEDDELIVERYCST.BRANCHNO,"\
        "DELAYEDDELIVERYCST.CUSTOMERNO,"\
        "DELAYEDDELIVERYCST.WEEKDAY,"\
        "DELAYEDDELIVERYCST.TIME,"\
        "DELAYEDDELIVERYCST.TOURID,"\
        "DELAYEDDELIVERYCST.ACTIV,"\
        "DELAYEDDELIVERYCST.DELAYEDWEEKDAY,"\
        "DELAYEDDELIVERYCST.NARCOTIC,"\
        "DELAYEDDELIVERYCST.COLDCHAIN,"\
        "DELAYEDDELIVERYCST.COOL08,"\
        "DELAYEDDELIVERYCST.COOL20"

/* SqlDefine of DELAYEDDELIVERYCSTSPECIAL *************************************/


#define DELAYEDDELIVERYCSTSPECIAL_PLISTE \
        "DELAYEDDELIVERYCST.BRANCHNO,"\
        "DELAYEDDELIVERYCST.CUSTOMERNO,"\
        "DELAYEDDELIVERYCST.WEEKDAY,"\
        "DELAYEDDELIVERYCST.TIME,"\
        "DELAYEDDELIVERYCST.ACTIV,"\
        "DELAYEDDELIVERYCST.DELAYEDWEEKDAY,"\
        "DELAYEDDELIVERYCST.NARCOTIC,"\
        "DELAYEDDELIVERYCST.COLDCHAIN,"\
        "DELAYEDDELIVERYCST.COOL08,"\
        "DELAYEDDELIVERYCST.COOL20,"\
        "DELAYEDDELIVERYCST.DATEFROM,"\
        "DELAYEDDELIVERYCST.DATETO"

/* SqlDefine of CHAINCUSTOMERS ************************************************/


#define CHAINCUSTOMERS_UPDLISTE \
        "NAMEAPO=?,"\
        "STRASSE=?,"\
        "ORT=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "MAINCSTNO=?"
/* SqlDefine of CHECKCUSTOMEREXIST ********************************************/


#define CHECKCUSTOMEREXIST_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?"
/* SqlDefine of CHECKLISTE5 ***************************************************/


#define CHECKLISTE5_UPDLISTE \
        "BRANCHNO=?,"\
        "ARTICLENO=?,"\
        "CUSTOMERNO=?"
/* SqlDefine of CSTBRANCHINFO *************************************************/


#define CSTBRANCHINFO_UPDLISTE \
        "BRANCHNO=?,"\
        "INFOTEXT=?,"\
        "DATETO=?,"\
        "TIMETO=?"
/* SqlDefine of CSTBULGARIA ***************************************************/


#define CSTBULGARIA_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "REBATEMETHFREESALE=?,"\
        "REBATEMETHHEALTHF=?,"\
        "MAINCSTNO=?"
/* SqlDefine of CSTBUYINGOPTIONS **********************************************/


#define CSTBUYINGOPTIONS_UPDLISTE \
        "ETARTKLASSE1=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "KZPSYCHOSTOFFE=?"
/* SqlDefine of CSTDISCACC ****************************************************/


#define CSTDISCACC_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "MAINCSTNO=?,"\
        "BALANCE=?,"\
        "UPD_FLAG=?,"\
        "KDAUFTRAGNR=?,"\
        "DATE=?,"\
        "INVOICENUMBER=?,"\
        "INVOICEAMOUNT=?,"\
        "VOUCHERTYP=?,"\
        "PREIS_TYP=?,"\
        "PRIORITY=?,"\
        "KDAUFTRAGNRSPLIT=?,"\
        "INVOICEPAID=?,"\
        "PAYMENTARGET=?,"\
        "LFDNR=?"
/* SqlDefine of CSTDISCACCANZ *************************************************/


#define CSTDISCACCANZ_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "MAINCSTNO=?,"\
        "NAMEAPO=?,"\
        "STRASSE=?,"\
        "ORT=?"
/* SqlDefine of CSTDISCCONT ***************************************************/


#define CSTDISCCONT_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "ORDER_TYPE=?,"\
        "PHARMACYGROUPID=?,"\
        "SUB_ORDER_TYPE=?,"\
        "PAYMENT_TERM=?,"\
        "VALUTA_DAYS=?,"\
        "MIN_ORDER_VALUE=?,"\
        "MIN_TUBES=?,"\
        "LOSS_IN_DISCOUNT=?,"\
        "UPD_FLAG=?"
/* SqlDefine of CSTPAYTERM ****************************************************/


#define CSTPAYTERM_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "PREIS_TYP=?,"\
        "PAYMENTARGET=?"
/* SqlDefine of CSTREBATETYPE *************************************************/


#define CSTREBATETYPE_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "REBATEMETHFREESALE=?,"\
        "REBATEMETHHEALTHF=?"
/* SqlDefine of CUSTPHARMA ****************************************************/


#define CUSTPHARMA_UPDLISTE \
        "CUSTOMERNO=?,"\
        "BRANCHNO=?,"\
        "PHARMACYGROUPID=?,"\
        "RANKING=?"
/* SqlDefine of CUSTPHON ******************************************************/


#define CUSTPHON_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "TELNR=?,"\
        "DATUM=?"
/* SqlDefine of CUSTROUT ******************************************************/


#define CUSTROUT_UPDLISTE \
        "CUSTOMERNO=?,"\
        "BRANCHNO=?,"\
        "TIMEFROM=?,"\
        "TIMETO=?,"\
        "DESTBRANCHNO=?,"\
        "DAYOFWEEK=?,"\
        "WEEKDAY=?"
/* SqlDefine of CUSTOMERDOUBLES ***********************************************/


#define CUSTOMERDOUBLES_UPDLISTE \
        "NAME=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?"
/* SqlDefine of DISTRESSROUTING ***********************************************/


#define DISTRESSROUTING_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "DESTBRANCHNO=?"
/* SqlDefine of ENCLOSERTIMES *************************************************/


#define ENCLOSERTIMES_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "TIMEDIFF=?,"\
        "MAXPOSITIONS=?"
/* SqlDefine of KNDTOURFENSTER ************************************************/


#define KNDTOURFENSTER_UPDLISTE \
        "CUSTOMERNO=?,"\
        "TOURID=?,"\
        "BRANCHNO=?,"\
        "WEEKDAY=?,"\
        "FROMTIME=?,"\
        "TOTIME=?,"\
        "MAINTIME=?"
/* SqlDefine of KNDTOURWOCHE **************************************************/


#define KNDTOURWOCHE_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "WEEKDAY=?,"\
        "ISTVERBUNDTOUR=?,"\
        "KDAUFTRAGART=?,"\
        "ISBTM=?,"\
        "ISKK=?,"\
        "ISK08=?,"\
        "ISK20=?,"\
        "PHARMACYLOCKACCESS=?,"\
        "REMARKLACKITEMPROCESSING=?,"\
        "RETURNSTOUR=?,"\
        "REMARKLACKCALLBACK=?,"\
        "TRANSPEXCLPSYCHO=?,"\
        "TRANSPEXCLCOOLED=?,"\
        "TRANSPEXCLEXPENSIVE=?,"\
        "CHECKPOSITIONS=?,"\
        "CHECKREMARK=?,"\
        "PLANNEDCALL=?,"\
        "KZAUTOZUORD=?,"\
        "SCHECKORDER=?,"\
        "CHECKTIMETOTOUR=?,"\
        "BEMERKUNGEN=?,"\
        "TOURID=?,"\
        "TAGESTYP=?"
/* SqlDefine of KNDTOURWOCHE2 *************************************************/


#define KNDTOURWOCHE2_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "TOURID=?,"\
        "DATUMKOMMI=?,"\
        "CONSTIME=?"
/* SqlDefine of KNDTOURWOCHE3 *************************************************/


#define KNDTOURWOCHE3_UPDLISTE \
        "FILIALNR=?,"\
        "TOURID=?,"\
        "DATUMKOMMI=?,"\
        "CONSTIME=?"
/* SqlDefine of KNDFILINFO ****************************************************/


#define KNDFILINFO_UPDLISTE \
        "KUNDENNR=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "DISPOGEBUEHR=?,"\
        "BTMGEBUEHR=?,"\
        "DOKUGEBUEHR=?,"\
        "TOURENKIPPZEIT=?"
/* SqlDefine of KNDFILINFO2 ***************************************************/


#define KNDFILINFO2_UPDLISTE \
        "FILIALNR=?,"\
        "DURCHLAUFNORMAL=?,"\
        "DURCHLAUFEILBOTE=?,"\
        "TOURVERSPAETUNG=?,"\
        "TOURENKIPPZEIT=?"
/* SqlDefine of KREDITLIMIT ***************************************************/


#define KREDITLIMIT_UPDLISTE \
        "PARTNERNO=?,"\
        "PARTNERNAME=?,"\
        "LIMIT=?,"\
        "SUM_DEBITSIDE=?,"\
        "SUM_CREDITSIDE=?,"\
        "SUM_MONTURNOVER=?,"\
        "SUM_DAYTURNOVER=?,"\
        "SUM_RETURNS=?,"\
        "SUM_GOODSRECEIPT=?,"\
        "LIMITTYPE=?,"\
        "LISTE5=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?"
/* SqlDefine of KUNDELIZENSEN *************************************************/


#define KUNDELIZENSEN_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "APOLIZENS=?,"\
        "BTMLIZENS=?"
/* SqlDefine of KUNDEVERBUNDFILIALE *******************************************/


#define KUNDEVERBUNDFILIALE_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "REIHENFOLGENR=?,"\
        "VERBUNDFILIALNR=?"
/* SqlDefine of LISTE5 ********************************************************/


#define LISTE5_UPDLISTE \
        "BRANCHNO=?,"\
        "ARTICLENO=?,"\
        "PREISEKAPO=?,"\
        "CUSTOMERNO=?,"\
        "PREIS_TYP=?,"\
        "TAXLEVEL=?,"\
        "ARTIKEL_LANGNAME=?"
/* SqlDefine of MCUSTOMEREMERGENCYSERVICEPLAN *********************************/


#define MCUSTOMEREMERGENCYSERVICEPLAN_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "DATUM=?,"\
        "UHRZEITVON=?,"\
        "UHRZEITBIS=?,"\
        "BEMERKUNGEN=?,"\
        "ISBTM=?,"\
        "ISKK=?,"\
        "ISK08=?,"\
        "ISK20=?"
/* SqlDefine of MCUSTOMERVACATION *********************************************/


#define MCUSTOMERVACATION_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "DATUMGUELTIGAB=?,"\
        "DATUMGUELTIGBIS=?"
/* SqlDefine of PAYTERM *******************************************************/


#define PAYTERM_UPDLISTE \
        "PAYMENT_TERM=?,"\
        "PAYMENTARGET=?,"\
        "CASHDISOUNT=?"
/* SqlDefine of PAYMENTLIST ***************************************************/


#define PAYMENTLIST_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "INVOICENUMBER=?,"\
        "TOTALINVOICEAMOUNT=?,"\
        "OPENINVOICEAMOUNT=?,"\
        "PAIDINVOICEAMOUNT=?,"\
        "DRIVERID=?,"\
        "PAYMENTDATE=?,"\
        "INVOICEDATE=?,"\
        "PAYMENTSPEC=?"
/* SqlDefine of PREWHOLECST ***************************************************/


#define PREWHOLECST_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "MAINCSTNO=?"
/* SqlDefine of SHIPAUXNO *****************************************************/


#define SHIPAUXNO_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "AUXBRANCHNO=?,"\
        "AUXBGANO=?"
/* SqlDefine of TOURPFLEGE ****************************************************/


#define TOURPFLEGE_UPDLISTE \
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "LOGINID=?,"\
        "CHANGEID=?,"\
        "KOART=?"
/* SqlDefine of DELAYEDCST ****************************************************/


#define DELAYEDCST_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "WEEKDAY=?,"\
        "TIME=?,"\
        "TOURID=?,"\
        "ACTIV=?,"\
        "DELAYEDWEEKDAY=?,"\
        "NARCOTIC=?,"\
        "COLDCHAIN=?,"\
        "COOL08=?,"\
        "COOL20=?"
/* SqlDefine of DELAYEDDELIVERYCSTSPECIAL *************************************/


#define DELAYEDDELIVERYCSTSPECIAL_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "WEEKDAY=?,"\
        "TIME=?,"\
        "ACTIV=?,"\
        "DELAYEDWEEKDAY=?,"\
        "NARCOTIC=?,"\
        "COLDCHAIN=?,"\
        "COOL08=?,"\
        "COOL20=?,"\
        "DATEFROM=?,"\
        "DATETO=?"
/* SqlMacros-Define of CHAINCUSTOMERS *****************************************/

#define CHAINCUSTOMERS_ZEIGER(x) \
        :x->NAMEAPO,\
        :x->STRASSE,\
        :x->ORT,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->MAINCSTNO
#define CHAINCUSTOMERS_ZEIGERSEL(x) \
        :x->NAMEAPO,\
        :x->STRASSE,\
        :x->ORT,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->MAINCSTNO

/* SqlMacros-Define of CHECKCUSTOMEREXIST *************************************/

#define CHECKCUSTOMEREXIST_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR
#define CHECKCUSTOMEREXIST_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR

/* SqlMacros-Define of CHECKLISTE5 ********************************************/

#define CHECKLISTE5_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->ARTICLENO,\
        :x->CUSTOMERNO
#define CHECKLISTE5_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->ARTICLENO,\
        :x->CUSTOMERNO

/* SqlMacros-Define of CSTBRANCHINFO ******************************************/

#define CSTBRANCHINFO_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->INFOTEXT,\
        :x->DATETO,\
        :x->TIMETO
#define CSTBRANCHINFO_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->LFDNR,\
        :x->INFOTEXT,\
        :x->DATETO,\
        :x->TIMETO

/* SqlMacros-Define of CSTBULGARIA ********************************************/

#define CSTBULGARIA_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->REBATEMETHFREESALE,\
        :x->REBATEMETHHEALTHF,\
        :x->MAINCSTNO
#define CSTBULGARIA_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->REBATEMETHFREESALE,\
        :x->REBATEMETHHEALTHF,\
        :x->MAINCSTNO

/* SqlMacros-Define of CSTBUYINGOPTIONS ***************************************/

#define CSTBUYINGOPTIONS_ZEIGER(x) \
        :x->ETARTKLASSE1,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->KZPSYCHOSTOFFE
#define CSTBUYINGOPTIONS_ZEIGERSEL(x) \
        :x->ETARTKLASSE1,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->KZPSYCHOSTOFFE

/* SqlMacros-Define of CSTDISCACC *********************************************/

#define CSTDISCACC_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->MAINCSTNO,\
        :x->BALANCE,\
        :x->UPD_FLAG,\
        :x->KDAUFTRAGNR,\
        :x->DATE,\
        :x->INVOICENUMBER,\
        :x->INVOICEAMOUNT,\
        :x->VOUCHERTYP,\
        :x->PREIS_TYP,\
        :x->PRIORITY,\
        :x->KDAUFTRAGNRSPLIT,\
        :x->INVOICEPAID,\
        :x->PAYMENTARGET,\
        :x->LFDNR
#define CSTDISCACC_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->MAINCSTNO,\
        :x->BALANCE,\
        :x->UPD_FLAG,\
        :x->KDAUFTRAGNR,\
        :x->DATE,\
        :x->INVOICENUMBER,\
        :x->INVOICEAMOUNT,\
        :x->VOUCHERTYP,\
        :x->PREIS_TYP,\
        :x->PRIORITY,\
        :x->KDAUFTRAGNRSPLIT,\
        :x->INVOICEPAID,\
        :x->PAYMENTARGET,\
        :x->LFDNR

/* SqlMacros-Define of CSTDISCACCANZ ******************************************/

#define CSTDISCACCANZ_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->MAINCSTNO,\
        :x->NAMEAPO,\
        :x->STRASSE,\
        :x->ORT
#define CSTDISCACCANZ_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->MAINCSTNO,\
        :x->NAMEAPO,\
        :x->STRASSE,\
        :x->ORT

/* SqlMacros-Define of CSTDISCCONT ********************************************/

#define CSTDISCCONT_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ORDER_TYPE,\
        :x->PHARMACYGROUPID,\
        :x->SUB_ORDER_TYPE,\
        :x->PAYMENT_TERM,\
        :x->VALUTA_DAYS,\
        :x->MIN_ORDER_VALUE,\
        :x->MIN_TUBES,\
        :x->LOSS_IN_DISCOUNT,\
        :x->UPD_FLAG
#define CSTDISCCONT_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->ORDER_TYPE,\
        :x->PHARMACYGROUPID,\
        :x->SUB_ORDER_TYPE,\
        :x->PAYMENT_TERM,\
        :x->VALUTA_DAYS,\
        :x->MIN_ORDER_VALUE,\
        :x->MIN_TUBES,\
        :x->LOSS_IN_DISCOUNT,\
        :x->UPD_FLAG

/* SqlMacros-Define of CSTPAYTERM *********************************************/

#define CSTPAYTERM_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->PREIS_TYP,\
        :x->PAYMENTARGET
#define CSTPAYTERM_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->PREIS_TYP,\
        :x->PAYMENTARGET

/* SqlMacros-Define of CSTREBATETYPE ******************************************/

#define CSTREBATETYPE_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->REBATEMETHFREESALE,\
        :x->REBATEMETHHEALTHF
#define CSTREBATETYPE_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->REBATEMETHFREESALE,\
        :x->REBATEMETHHEALTHF

/* SqlMacros-Define of CUSTPHARMA *********************************************/

#define CUSTPHARMA_ZEIGER(x) \
        :x->CUSTOMERNO,\
        :x->BRANCHNO,\
        :x->PHARMACYGROUPID,\
        :x->RANKING
#define CUSTPHARMA_ZEIGERSEL(x) \
        :x->CUSTOMERNO,\
        :x->BRANCHNO,\
        :x->PHARMACYGROUPID,\
        :x->RANKING

/* SqlMacros-Define of CUSTPHON ***********************************************/

#define CUSTPHON_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->TELNR,\
        :x->DATUM
#define CUSTPHON_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->TELNR,\
        :x->DATUM

/* SqlMacros-Define of CUSTROUT ***********************************************/

#define CUSTROUT_ZEIGER(x) \
        :x->CUSTOMERNO,\
        :x->BRANCHNO,\
        :x->TIMEFROM,\
        :x->TIMETO,\
        :x->DESTBRANCHNO,\
        :x->DAYOFWEEK,\
        :x->WEEKDAY
#define CUSTROUT_ZEIGERSEL(x) \
        :x->CUSTOMERNO,\
        :x->BRANCHNO,\
        :x->TIMEFROM,\
        :x->TIMETO,\
        :x->DESTBRANCHNO,\
        :x->DAYOFWEEK,\
        :x->WEEKDAY

/* SqlMacros-Define of CUSTOMERDOUBLES ****************************************/

#define CUSTOMERDOUBLES_ZEIGER(x) \
        :x->NAME,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR
#define CUSTOMERDOUBLES_ZEIGERSEL(x) \
        :x->NAME,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR

/* SqlMacros-Define of DISTRESSROUTING ****************************************/

#define DISTRESSROUTING_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DESTBRANCHNO
#define DISTRESSROUTING_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->DESTBRANCHNO,\
        :x->NAMEAPO,\
        :x->ORT,\
        :x->POSTLEITZAHL,\
        :x->PERSONALNRVERTR,\
        :x->KZKDKLASSE

/* SqlMacros-Define of ENCLOSERTIMES ******************************************/

#define ENCLOSERTIMES_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->TIMEDIFF,\
        :x->MAXPOSITIONS
#define ENCLOSERTIMES_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->TIMEDIFF,\
        :x->MAXPOSITIONS

/* SqlMacros-Define of KNDTOURFENSTER *****************************************/

#define KNDTOURFENSTER_ZEIGER(x) \
        :x->CUSTOMERNO,\
        :x->TOURID,\
        :x->BRANCHNO,\
        :x->WEEKDAY,\
        :x->FROMTIME,\
        :x->TOTIME,\
        :x->MAINTIME
#define KNDTOURFENSTER_ZEIGERSEL(x) \
        :x->CUSTOMERNO,\
        :x->TOURID,\
        :x->BRANCHNO,\
        :x->WEEKDAY,\
        :x->FROMTIME,\
        :x->TOTIME,\
        :x->MAINTIME

/* SqlMacros-Define of KNDTOURWOCHE *******************************************/

#define KNDTOURWOCHE_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->WEEKDAY,\
        :x->ISTVERBUNDTOUR,\
        :x->KDAUFTRAGART,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20,\
        :x->PHARMACYLOCKACCESS,\
        :x->REMARKLACKITEMPROCESSING,\
        :x->RETURNSTOUR,\
        :x->REMARKLACKCALLBACK,\
        :x->TRANSPEXCLPSYCHO,\
        :x->TRANSPEXCLCOOLED,\
        :x->TRANSPEXCLEXPENSIVE,\
        :x->CHECKPOSITIONS,\
        :x->CHECKREMARK,\
        :x->PLANNEDCALL,\
        :x->KZAUTOZUORD,\
        :x->SCHECKORDER,\
        :x->CHECKTIMETOTOUR,\
        :x->BEMERKUNGEN,\
        :x->TOURID,\
        :x->TAGESTYP
#define KNDTOURWOCHE_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->WEEKDAY,\
        :x->ISTVERBUNDTOUR,\
        :x->KDAUFTRAGART,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20,\
        :x->PHARMACYLOCKACCESS,\
        :x->REMARKLACKITEMPROCESSING,\
        :x->RETURNSTOUR,\
        :x->REMARKLACKCALLBACK,\
        :x->TRANSPEXCLPSYCHO,\
        :x->TRANSPEXCLCOOLED,\
        :x->TRANSPEXCLEXPENSIVE,\
        :x->CHECKPOSITIONS,\
        :x->CHECKREMARK,\
        :x->PLANNEDCALL,\
        :x->KZAUTOZUORD,\
        :x->SCHECKORDER,\
        :x->CHECKTIMETOTOUR,\
        :x->BEMERKUNGEN,\
        :x->TOURID,\
        :x->TAGESTYP

/* SqlMacros-Define of KNDTOURWOCHE2 ******************************************/

#define KNDTOURWOCHE2_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->TOURID,\
        :x->DATUMKOMMI,\
        :x->CONSTIME
#define KNDTOURWOCHE2_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->TOURID,\
        :x->DATUMKOMMI,\
        :x->CONSTIME

/* SqlMacros-Define of KNDTOURWOCHE3 ******************************************/

#define KNDTOURWOCHE3_ZEIGER(x) \
        :x->FILIALNR,\
        :x->TOURID,\
        :x->DATUMKOMMI,\
        :x->CONSTIME
#define KNDTOURWOCHE3_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->TOURID,\
        :x->DATUMKOMMI,\
        :x->CONSTIME

/* SqlMacros-Define of KNDFILINFO *********************************************/

#define KNDFILINFO_ZEIGER(x) \
        :x->KUNDENNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->DISPOGEBUEHR,\
        :x->BTMGEBUEHR,\
        :x->DOKUGEBUEHR,\
        :x->TOURENKIPPZEIT
#define KNDFILINFO_ZEIGERSEL(x) \
        :x->KUNDENNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->DISPOGEBUEHR,\
        :x->BTMGEBUEHR,\
        :x->DOKUGEBUEHR,\
        :x->TOURENKIPPZEIT

/* SqlMacros-Define of KNDFILINFO2 ********************************************/

#define KNDFILINFO2_ZEIGER(x) \
        :x->FILIALNR,\
        :x->DURCHLAUFNORMAL,\
        :x->DURCHLAUFEILBOTE,\
        :x->TOURVERSPAETUNG,\
        :x->TOURENKIPPZEIT
#define KNDFILINFO2_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->DURCHLAUFNORMAL,\
        :x->DURCHLAUFEILBOTE,\
        :x->TOURVERSPAETUNG,\
        :x->TOURENKIPPZEIT

/* SqlMacros-Define of KREDITLIMIT ********************************************/

#define KREDITLIMIT_ZEIGER(x) \
        :x->PARTNERNO,\
        :x->PARTNERNAME,\
        :x->LIMIT,\
        :x->SUM_DEBITSIDE,\
        :x->SUM_CREDITSIDE,\
        :x->SUM_MONTURNOVER,\
        :x->SUM_DAYTURNOVER,\
        :x->SUM_RETURNS,\
        :x->SUM_GOODSRECEIPT,\
        :x->LIMITTYPE,\
        :x->LISTE5,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR
#define KREDITLIMIT_ZEIGERSEL(x) \
        :x->PARTNERNO,\
        :x->PARTNERNAME,\
        :x->LIMIT,\
        :x->SUM_DEBITSIDE,\
        :x->SUM_CREDITSIDE,\
        :x->SUM_MONTURNOVER,\
        :x->SUM_DAYTURNOVER,\
        :x->SUM_RETURNS,\
        :x->SUM_GOODSRECEIPT,\
        :x->LIMITTYPE,\
        :x->LISTE5,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR

/* SqlMacros-Define of KUNDELIZENSEN ******************************************/

#define KUNDELIZENSEN_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->APOLIZENS,\
        :x->BTMLIZENS
#define KUNDELIZENSEN_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->APOLIZENS,\
        :x->BTMLIZENS

/* SqlMacros-Define of KUNDEVERBUNDFILIALE ************************************/

#define KUNDEVERBUNDFILIALE_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->REIHENFOLGENR,\
        :x->VERBUNDFILIALNR
#define KUNDEVERBUNDFILIALE_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->REIHENFOLGENR,\
        :x->VERBUNDFILIALNR

/* SqlMacros-Define of LISTE5 *************************************************/

#define LISTE5_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->ARTICLENO,\
        :x->PREISEKAPO,\
        :x->CUSTOMERNO,\
        :x->PREIS_TYP,\
        :x->TAXLEVEL,\
        :x->ARTIKEL_LANGNAME
#define LISTE5_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->ARTICLENO,\
        :x->PREISEKAPO,\
        :x->CUSTOMERNO,\
        :x->PREIS_TYP,\
        :x->TAXLEVEL,\
        :x->ARTIKEL_LANGNAME

/* SqlMacros-Define of MCUSTOMEREMERGENCYSERVICEPLAN **************************/

#define MCUSTOMEREMERGENCYSERVICEPLAN_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUM,\
        :x->UHRZEITVON,\
        :x->UHRZEITBIS,\
        :x->BEMERKUNGEN,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20
#define MCUSTOMEREMERGENCYSERVICEPLAN_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUM,\
        :x->UHRZEITVON,\
        :x->UHRZEITBIS,\
        :x->BEMERKUNGEN,\
        :x->ISBTM,\
        :x->ISKK,\
        :x->ISK08,\
        :x->ISK20

/* SqlMacros-Define of MCUSTOMERVACATION **************************************/

#define MCUSTOMERVACATION_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUMGUELTIGAB,\
        :x->DATUMGUELTIGBIS
#define MCUSTOMERVACATION_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUMGUELTIGAB,\
        :x->DATUMGUELTIGBIS

/* SqlMacros-Define of PAYTERM ************************************************/

#define PAYTERM_ZEIGER(x) \
        :x->PAYMENT_TERM,\
        :x->PAYMENTARGET,\
        :x->CASHDISOUNT
#define PAYTERM_ZEIGERSEL(x) \
        :x->PAYMENT_TERM,\
        :x->PAYMENTARGET,\
        :x->CASHDISOUNT

/* SqlMacros-Define of PAYMENTLIST ********************************************/

#define PAYMENTLIST_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->INVOICENUMBER,\
        :x->TOTALINVOICEAMOUNT,\
        :x->OPENINVOICEAMOUNT,\
        :x->PAIDINVOICEAMOUNT,\
        :x->DRIVERID,\
        :x->PAYMENTDATE,\
        :x->INVOICEDATE,\
        :x->PAYMENTSPEC
#define PAYMENTLIST_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->INVOICENUMBER,\
        :x->TOTALINVOICEAMOUNT,\
        :x->OPENINVOICEAMOUNT,\
        :x->PAIDINVOICEAMOUNT,\
        :x->DRIVERID,\
        :x->PAYMENTDATE,\
        :x->INVOICEDATE,\
        :x->PAYMENTSPEC

/* SqlMacros-Define of PREWHOLECST ********************************************/

#define PREWHOLECST_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->MAINCSTNO
#define PREWHOLECST_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->MAINCSTNO

/* SqlMacros-Define of SHIPAUXNO **********************************************/

#define SHIPAUXNO_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->AUXBRANCHNO,\
        :x->AUXBGANO
#define SHIPAUXNO_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->AUXBRANCHNO,\
        :x->AUXBGANO

/* SqlMacros-Define of TOURPFLEGE *********************************************/

#define TOURPFLEGE_ZEIGER(x) \
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->KOART
#define TOURPFLEGE_ZEIGERSEL(x) \
        :x->TOURID,\
        :x->REIHENFOLGENR,\
        :x->FAHRTZEIT,\
        :x->BEMERKUNGEN,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->KOART

/* SqlMacros-Define of DELAYEDCST *********************************************/

#define DELAYEDCST_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->WEEKDAY,\
        :x->TIME,\
        :x->TOURID,\
        :x->ACTIV,\
        :x->DELAYEDWEEKDAY,\
        :x->NARCOTIC,\
        :x->COLDCHAIN,\
        :x->COOL08,\
        :x->COOL20
#define DELAYEDCST_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->WEEKDAY,\
        :x->TIME,\
        :x->TOURID,\
        :x->ACTIV,\
        :x->DELAYEDWEEKDAY,\
        :x->NARCOTIC,\
        :x->COLDCHAIN,\
        :x->COOL08,\
        :x->COOL20

/* SqlMacros-Define of DELAYEDDELIVERYCSTSPECIAL ******************************/

#define DELAYEDDELIVERYCSTSPECIAL_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->WEEKDAY,\
        :x->TIME,\
        :x->ACTIV,\
        :x->DELAYEDWEEKDAY,\
        :x->NARCOTIC,\
        :x->COLDCHAIN,\
        :x->COOL08,\
        :x->COOL20,\
        :x->DATEFROM,\
        :x->DATETO
#define DELAYEDDELIVERYCSTSPECIAL_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->CUSTOMERNO,\
        :x->WEEKDAY,\
        :x->TIME,\
        :x->ACTIV,\
        :x->DELAYEDWEEKDAY,\
        :x->NARCOTIC,\
        :x->COLDCHAIN,\
        :x->COOL08,\
        :x->COOL20,\
        :x->DATEFROM,\
        :x->DATETO

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CHAINCUSTOMERS_H
#define CHAINCUSTOMERS_ANZ ( sizeof(CHAINCUSTOMERS_BES) / sizeof(struct buf_desc) )
#define CHECKCUSTOMEREXIST_H
#define CHECKCUSTOMEREXIST_ANZ ( sizeof(CHECKCUSTOMEREXIST_BES) / sizeof(struct buf_desc) )
#define CHECKLISTE5_H
#define CHECKLISTE5_ANZ ( sizeof(CHECKLISTE5_BES) / sizeof(struct buf_desc) )
#define CSTBRANCHINFO_H
#define CSTBRANCHINFO_ANZ ( sizeof(CSTBRANCHINFO_BES) / sizeof(struct buf_desc) )
#define CSTBULGARIA_H
#define CSTBULGARIA_ANZ ( sizeof(CSTBULGARIA_BES) / sizeof(struct buf_desc) )
#define CSTBUYINGOPTIONS_H
#define CSTBUYINGOPTIONS_ANZ ( sizeof(CSTBUYINGOPTIONS_BES) / sizeof(struct buf_desc) )
#define CSTDISCACC_H
#define CSTDISCACC_ANZ ( sizeof(CSTDISCACC_BES) / sizeof(struct buf_desc) )
#define CSTDISCACCANZ_H
#define CSTDISCACCANZ_ANZ ( sizeof(CSTDISCACCANZ_BES) / sizeof(struct buf_desc) )
#define CSTDISCCONT_H
#define CSTDISCCONT_ANZ ( sizeof(CSTDISCCONT_BES) / sizeof(struct buf_desc) )
#define CSTPAYTERM_H
#define CSTPAYTERM_ANZ ( sizeof(CSTPAYTERM_BES) / sizeof(struct buf_desc) )
#define CSTREBATETYPE_H
#define CSTREBATETYPE_ANZ ( sizeof(CSTREBATETYPE_BES) / sizeof(struct buf_desc) )
#define CUSTPHARMA_H
#define CUSTPHARMA_ANZ ( sizeof(CUSTPHARMA_BES) / sizeof(struct buf_desc) )
#define CUSTPHON_H
#define CUSTPHON_ANZ ( sizeof(CUSTPHON_BES) / sizeof(struct buf_desc) )
#define CUSTROUT_H
#define CUSTROUT_ANZ ( sizeof(CUSTROUT_BES) / sizeof(struct buf_desc) )
#define CUSTOMERDOUBLES_H
#define CUSTOMERDOUBLES_ANZ ( sizeof(CUSTOMERDOUBLES_BES) / sizeof(struct buf_desc) )
#define DISTRESSROUTING_H
#define DISTRESSROUTING_ANZ ( sizeof(DISTRESSROUTING_BES) / sizeof(struct buf_desc) )
#define ENCLOSERTIMES_H
#define ENCLOSERTIMES_ANZ ( sizeof(ENCLOSERTIMES_BES) / sizeof(struct buf_desc) )
#define KNDTOURFENSTER_H
#define KNDTOURFENSTER_ANZ ( sizeof(KNDTOURFENSTER_BES) / sizeof(struct buf_desc) )
#define KNDTOURWOCHE_H
#define KNDTOURWOCHE_ANZ ( sizeof(KNDTOURWOCHE_BES) / sizeof(struct buf_desc) )
#define KNDTOURWOCHE2_H
#define KNDTOURWOCHE2_ANZ ( sizeof(KNDTOURWOCHE2_BES) / sizeof(struct buf_desc) )
#define KNDTOURWOCHE3_H
#define KNDTOURWOCHE3_ANZ ( sizeof(KNDTOURWOCHE3_BES) / sizeof(struct buf_desc) )
#define KNDFILINFO_H
#define KNDFILINFO_ANZ ( sizeof(KNDFILINFO_BES) / sizeof(struct buf_desc) )
#define KNDFILINFO2_H
#define KNDFILINFO2_ANZ ( sizeof(KNDFILINFO2_BES) / sizeof(struct buf_desc) )
#define KREDITLIMIT_H
#define KREDITLIMIT_ANZ ( sizeof(KREDITLIMIT_BES) / sizeof(struct buf_desc) )
#define KUNDELIZENSEN_H
#define KUNDELIZENSEN_ANZ ( sizeof(KUNDELIZENSEN_BES) / sizeof(struct buf_desc) )
#define KUNDEVERBUNDFILIALE_H
#define KUNDEVERBUNDFILIALE_ANZ ( sizeof(KUNDEVERBUNDFILIALE_BES) / sizeof(struct buf_desc) )
#define LISTE5_H
#define LISTE5_ANZ ( sizeof(LISTE5_BES) / sizeof(struct buf_desc) )
#define MCUSTOMEREMERGENCYSERVICEPLAN_H
#define MCUSTOMEREMERGENCYSERVICEPLAN_ANZ ( sizeof(MCUSTOMEREMERGENCYSERVICEPLAN_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERVACATION_H
#define MCUSTOMERVACATION_ANZ ( sizeof(MCUSTOMERVACATION_BES) / sizeof(struct buf_desc) )
#define PAYTERM_H
#define PAYTERM_ANZ ( sizeof(PAYTERM_BES) / sizeof(struct buf_desc) )
#define PAYMENTLIST_H
#define PAYMENTLIST_ANZ ( sizeof(PAYMENTLIST_BES) / sizeof(struct buf_desc) )
#define PREWHOLECST_H
#define PREWHOLECST_ANZ ( sizeof(PREWHOLECST_BES) / sizeof(struct buf_desc) )
#define SHIPAUXNO_H
#define SHIPAUXNO_ANZ ( sizeof(SHIPAUXNO_BES) / sizeof(struct buf_desc) )
#define TOURPFLEGE_H
#define TOURPFLEGE_ANZ ( sizeof(TOURPFLEGE_BES) / sizeof(struct buf_desc) )
#define DELAYEDCST_H
#define DELAYEDCST_ANZ ( sizeof(DELAYEDCST_BES) / sizeof(struct buf_desc) )
#define DELAYEDDELIVERYCSTSPECIAL_H
#define DELAYEDDELIVERYCSTSPECIAL_ANZ ( sizeof(DELAYEDDELIVERYCSTSPECIAL_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CHAINCUSTOMERS ******************************************/

#ifndef TRANSCLASS
typedef struct N_CHAINCUSTOMERS {
    char NAMEAPO[41];
    char STRASSE[31];
    char ORT[31];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long MAINCSTNO;
    long FETCH_REL;
} chaincustomersS;
#else /* TRANSCLASS */
typedef struct N_CHAINCUSTOMERS {
    char NAMEAPO[41];
    char STRASSE[31];
    char ORT[31];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long MAINCSTNO;
    long FETCH_REL;
    bool operator == (const N_CHAINCUSTOMERS& right) const {
        return (
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(STRASSE, right.STRASSE) &&
            !strcmp(ORT, right.ORT) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            MAINCSTNO == right.MAINCSTNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(NAMEAPO, " " );
        strcpy(STRASSE, " " );
        strcpy(ORT, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        MAINCSTNO = 0;
#endif
    }
} chaincustomersS;
#endif /* TRANSCLASS */

/* original struct of CHECKCUSTOMEREXIST **************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKCUSTOMEREXIST {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
} checkcustomerexistS;
#else /* TRANSCLASS */
typedef struct N_CHECKCUSTOMEREXIST {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;

    bool operator == (const N_CHECKCUSTOMEREXIST& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
#endif
    }
} checkcustomerexistS;
#endif /* TRANSCLASS */

/* original struct of CHECKLISTE5 *********************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKLISTE5 {
    short BRANCHNO;
    long ARTICLENO;
    long CUSTOMERNO;
} checkliste5S;
#else /* TRANSCLASS */
typedef struct N_CHECKLISTE5 {
    short BRANCHNO;
    long ARTICLENO;
    long CUSTOMERNO;

    bool operator == (const N_CHECKLISTE5& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            ARTICLENO == right.ARTICLENO &&
            CUSTOMERNO == right.CUSTOMERNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        ARTICLENO = 0;
        CUSTOMERNO = 0;
#endif
    }
} checkliste5S;
#endif /* TRANSCLASS */

/* original struct of CSTBRANCHINFO *******************************************/

#ifndef TRANSCLASS
typedef struct N_CSTBRANCHINFO {
    short BRANCHNO;
    long LFDNR;
    char INFOTEXT[257];
    long DATETO;
    long TIMETO;
    long FETCH_REL;
} cstbranchinfoS;
#else /* TRANSCLASS */
typedef struct N_CSTBRANCHINFO {
    short BRANCHNO;
    long LFDNR;
    char INFOTEXT[257];
    long DATETO;
    long TIMETO;
    long FETCH_REL;
    bool operator == (const N_CSTBRANCHINFO& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            LFDNR == right.LFDNR &&
            !strcmp(INFOTEXT, right.INFOTEXT) &&
            DATETO == right.DATETO &&
            TIMETO == right.TIMETO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        LFDNR = 0;
        strcpy(INFOTEXT, " " );
        DATETO = 0;
        TIMETO = 0;
#endif
    }
} cstbranchinfoS;
#endif /* TRANSCLASS */

/* original struct of CSTBULGARIA *********************************************/

#ifndef TRANSCLASS
typedef struct N_CSTBULGARIA {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short REBATEMETHFREESALE;
    short REBATEMETHHEALTHF;
    long MAINCSTNO;
} cstbulgariaS;
#else /* TRANSCLASS */
typedef struct N_CSTBULGARIA {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short REBATEMETHFREESALE;
    short REBATEMETHHEALTHF;
    long MAINCSTNO;

    bool operator == (const N_CSTBULGARIA& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            REBATEMETHFREESALE == right.REBATEMETHFREESALE &&
            REBATEMETHHEALTHF == right.REBATEMETHHEALTHF &&
            MAINCSTNO == right.MAINCSTNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        REBATEMETHFREESALE = 0;
        REBATEMETHHEALTHF = 0;
        MAINCSTNO = 0;
#endif
    }
} cstbulgariaS;
#endif /* TRANSCLASS */

/* original struct of CSTBUYINGOPTIONS ****************************************/

#ifndef TRANSCLASS
typedef struct N_CSTBUYINGOPTIONS {
    long ETARTKLASSE1;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char KZPSYCHOSTOFFE[2];
} cstbuyingoptionsS;
#else /* TRANSCLASS */
typedef struct N_CSTBUYINGOPTIONS {
    long ETARTKLASSE1;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char KZPSYCHOSTOFFE[2];

    bool operator == (const N_CSTBUYINGOPTIONS& right) const {
        return (
            ETARTKLASSE1 == right.ETARTKLASSE1 &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(KZPSYCHOSTOFFE, right.KZPSYCHOSTOFFE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        ETARTKLASSE1 = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(KZPSYCHOSTOFFE, " " );
#endif
    }
} cstbuyingoptionsS;
#endif /* TRANSCLASS */

/* original struct of CSTDISCACC **********************************************/

#ifndef TRANSCLASS
typedef struct N_CSTDISCACC {
    short BRANCHNO;
    long CUSTOMERNO;
    long MAINCSTNO;
    long DATUM;
    double BALANCE;
    char UPD_FLAG[2];
    long KDAUFTRAGNR;
    long DATE;
    char INVOICENUMBER[16];
    double INVOICEAMOUNT;
    char VOUCHERTYP[3];
    short PREIS_TYP;
    short PRIORITY;
    long KDAUFTRAGNRSPLIT;
    double INVOICEPAID;
    short PAYMENTARGET;
    long LFDNR;
    long FETCH_REL;
} cstdiscaccS;
#else /* TRANSCLASS */
typedef struct N_CSTDISCACC {
    short BRANCHNO;
    long CUSTOMERNO;
    long MAINCSTNO;
    long DATUM;
    double BALANCE;
    char UPD_FLAG[2];
    long KDAUFTRAGNR;
    long DATE;
    char INVOICENUMBER[16];
    double INVOICEAMOUNT;
    char VOUCHERTYP[3];
    short PREIS_TYP;
    short PRIORITY;
    long KDAUFTRAGNRSPLIT;
    double INVOICEPAID;
    short PAYMENTARGET;
    long LFDNR;
    long FETCH_REL;
    bool operator == (const N_CSTDISCACC& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            MAINCSTNO == right.MAINCSTNO &&
            DATUM == right.DATUM &&
            BALANCE == right.BALANCE &&
            !strcmp(UPD_FLAG, right.UPD_FLAG) &&
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            DATE == right.DATE &&
            !strcmp(INVOICENUMBER, right.INVOICENUMBER) &&
            INVOICEAMOUNT == right.INVOICEAMOUNT &&
            !strcmp(VOUCHERTYP, right.VOUCHERTYP) &&
            PREIS_TYP == right.PREIS_TYP &&
            PRIORITY == right.PRIORITY &&
            KDAUFTRAGNRSPLIT == right.KDAUFTRAGNRSPLIT &&
            INVOICEPAID == right.INVOICEPAID &&
            PAYMENTARGET == right.PAYMENTARGET &&
            LFDNR == right.LFDNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        MAINCSTNO = 0;
        DATUM = 0;
        BALANCE = 0;
        strcpy(UPD_FLAG, " " );
        KDAUFTRAGNR = 0;
        DATE = 0;
        strcpy(INVOICENUMBER, " " );
        INVOICEAMOUNT = 0;
        strcpy(VOUCHERTYP, " " );
        PREIS_TYP = 0;
        PRIORITY = 0;
        KDAUFTRAGNRSPLIT = 0;
        INVOICEPAID = 0;
        PAYMENTARGET = 0;
        LFDNR = 0;
#endif
    }
} cstdiscaccS;
#endif /* TRANSCLASS */

/* original struct of CSTDISCACCANZ *******************************************/

#ifndef TRANSCLASS
typedef struct N_CSTDISCACCANZ {
    short BRANCHNO;
    long CUSTOMERNO;
    long MAINCSTNO;
    char NAMEAPO[41];
    char STRASSE[31];
    char ORT[31];
    long FETCH_REL;
} cstdiscaccanzS;
#else /* TRANSCLASS */
typedef struct N_CSTDISCACCANZ {
    short BRANCHNO;
    long CUSTOMERNO;
    long MAINCSTNO;
    char NAMEAPO[41];
    char STRASSE[31];
    char ORT[31];
    long FETCH_REL;
    bool operator == (const N_CSTDISCACCANZ& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            MAINCSTNO == right.MAINCSTNO &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(STRASSE, right.STRASSE) &&
            !strcmp(ORT, right.ORT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        MAINCSTNO = 0;
        strcpy(NAMEAPO, " " );
        strcpy(STRASSE, " " );
        strcpy(ORT, " " );
#endif
    }
} cstdiscaccanzS;
#endif /* TRANSCLASS */

/* original struct of CSTDISCCONT *********************************************/

#ifndef TRANSCLASS
typedef struct N_CSTDISCCONT {
    short BRANCHNO;
    long CUSTOMERNO;
    char ORDER_TYPE[3];
    char PHARMACYGROUPID[4];
    char SUB_ORDER_TYPE[4];
    char PAYMENT_TERM[5];
    short VALUTA_DAYS;
    double MIN_ORDER_VALUE;
    short MIN_TUBES;
    double LOSS_IN_DISCOUNT;
    char UPD_FLAG[2];
    long FETCH_REL;
} cstdisccontS;
#else /* TRANSCLASS */
typedef struct N_CSTDISCCONT {
    short BRANCHNO;
    long CUSTOMERNO;
    char ORDER_TYPE[3];
    char PHARMACYGROUPID[4];
    char SUB_ORDER_TYPE[4];
    char PAYMENT_TERM[5];
    short VALUTA_DAYS;
    double MIN_ORDER_VALUE;
    short MIN_TUBES;
    double LOSS_IN_DISCOUNT;
    char UPD_FLAG[2];
    long FETCH_REL;
    bool operator == (const N_CSTDISCCONT& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(ORDER_TYPE, right.ORDER_TYPE) &&
            !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
            !strcmp(SUB_ORDER_TYPE, right.SUB_ORDER_TYPE) &&
            !strcmp(PAYMENT_TERM, right.PAYMENT_TERM) &&
            VALUTA_DAYS == right.VALUTA_DAYS &&
            MIN_ORDER_VALUE == right.MIN_ORDER_VALUE &&
            MIN_TUBES == right.MIN_TUBES &&
            LOSS_IN_DISCOUNT == right.LOSS_IN_DISCOUNT &&
            !strcmp(UPD_FLAG, right.UPD_FLAG)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        strcpy(ORDER_TYPE, " " );
        strcpy(PHARMACYGROUPID, " " );
        strcpy(SUB_ORDER_TYPE, " " );
        strcpy(PAYMENT_TERM, " " );
        VALUTA_DAYS = 0;
        MIN_ORDER_VALUE = 0;
        MIN_TUBES = 0;
        LOSS_IN_DISCOUNT = 0;
        strcpy(UPD_FLAG, " " );
#endif
    }
} cstdisccontS;
#endif /* TRANSCLASS */

/* original struct of CSTPAYTERM **********************************************/

#ifndef TRANSCLASS
typedef struct N_CSTPAYTERM {
    short BRANCHNO;
    long CUSTOMERNO;
    short PREIS_TYP;
    short PAYMENTARGET;
    long FETCH_REL;
} cstpaytermS;
#else /* TRANSCLASS */
typedef struct N_CSTPAYTERM {
    short BRANCHNO;
    long CUSTOMERNO;
    short PREIS_TYP;
    short PAYMENTARGET;
    long FETCH_REL;
    bool operator == (const N_CSTPAYTERM& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            PREIS_TYP == right.PREIS_TYP &&
            PAYMENTARGET == right.PAYMENTARGET
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        PREIS_TYP = 0;
        PAYMENTARGET = 0;
#endif
    }
} cstpaytermS;
#endif /* TRANSCLASS */

/* original struct of CSTREBATETYPE *******************************************/

#ifndef TRANSCLASS
typedef struct N_CSTREBATETYPE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short REBATEMETHFREESALE;
    short REBATEMETHHEALTHF;
} cstrebatetypeS;
#else /* TRANSCLASS */
typedef struct N_CSTREBATETYPE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short REBATEMETHFREESALE;
    short REBATEMETHHEALTHF;

    bool operator == (const N_CSTREBATETYPE& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            REBATEMETHFREESALE == right.REBATEMETHFREESALE &&
            REBATEMETHHEALTHF == right.REBATEMETHHEALTHF
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        REBATEMETHFREESALE = 0;
        REBATEMETHHEALTHF = 0;
#endif
    }
} cstrebatetypeS;
#endif /* TRANSCLASS */

/* original struct of CUSTPHARMA **********************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTPHARMA {
    long CUSTOMERNO;
    short BRANCHNO;
    char PHARMACYGROUPID[4];
    short RANKING;
    long FETCH_REL;
} custpharmaS;
#else /* TRANSCLASS */
typedef struct N_CUSTPHARMA {
    long CUSTOMERNO;
    short BRANCHNO;
    char PHARMACYGROUPID[4];
    short RANKING;
    long FETCH_REL;
    bool operator == (const N_CUSTPHARMA& right) const {
        return (
            CUSTOMERNO == right.CUSTOMERNO &&
            BRANCHNO == right.BRANCHNO &&
            !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
            RANKING == right.RANKING
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CUSTOMERNO = 0;
        BRANCHNO = 0;
        strcpy(PHARMACYGROUPID, " " );
        RANKING = 0;
#endif
    }
} custpharmaS;
#endif /* TRANSCLASS */

/* original struct of CUSTPHON ************************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTPHON {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TELNR[21];
    long DATUM;
    long FETCH_REL;
} custphonS;
#else /* TRANSCLASS */
typedef struct N_CUSTPHON {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TELNR[21];
    long DATUM;
    long FETCH_REL;
    bool operator == (const N_CUSTPHON& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(TELNR, right.TELNR) &&
            DATUM == right.DATUM
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(TELNR, " " );
        DATUM = 0;
#endif
    }
} custphonS;
#endif /* TRANSCLASS */

/* original struct of CUSTROUT ************************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTROUT {
    long CUSTOMERNO;
    short BRANCHNO;
    long TIMEFROM;
    long TIMETO;
    short DESTBRANCHNO;
    char DAYOFWEEK[3];
    short WEEKDAY;
    long ZEIT_VON;
    long FETCH_REL;
} custroutS;
#else /* TRANSCLASS */
typedef struct N_CUSTROUT {
    long CUSTOMERNO;
    short BRANCHNO;
    long TIMEFROM;
    long TIMETO;
    short DESTBRANCHNO;
    char DAYOFWEEK[3];
    short WEEKDAY;
    long ZEIT_VON;
    long FETCH_REL;
    bool operator == (const N_CUSTROUT& right) const {
        return (
            CUSTOMERNO == right.CUSTOMERNO &&
            BRANCHNO == right.BRANCHNO &&
            TIMEFROM == right.TIMEFROM &&
            TIMETO == right.TIMETO &&
            DESTBRANCHNO == right.DESTBRANCHNO &&
            !strcmp(DAYOFWEEK, right.DAYOFWEEK) &&
            WEEKDAY == right.WEEKDAY &&
            ZEIT_VON == right.ZEIT_VON
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CUSTOMERNO = 0;
        BRANCHNO = 0;
        TIMEFROM = 0;
        TIMETO = 0;
        DESTBRANCHNO = 0;
        strcpy(DAYOFWEEK, " " );
        WEEKDAY = 0;
        ZEIT_VON = 0;
#endif
    }
} custroutS;
#endif /* TRANSCLASS */

/* original struct of CUSTOMERDOUBLES *****************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTOMERDOUBLES {
    char NAME[31];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
} customerdoublesS;
#else /* TRANSCLASS */
typedef struct N_CUSTOMERDOUBLES {
    char NAME[31];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
    bool operator == (const N_CUSTOMERDOUBLES& right) const {
        return (
            !strcmp(NAME, right.NAME) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(NAME, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
#endif
    }
} customerdoublesS;
#endif /* TRANSCLASS */

/* original struct of DISTRESSROUTING *****************************************/

#ifndef TRANSCLASS
typedef struct N_DISTRESSROUTING {
    short BRANCHNO;
    long CUSTOMERNO;
    short DESTBRANCHNO;
    char NAMEAPO[41];
    char ORT[31];
    char POSTLEITZAHL[11];
    long PERSONALNRVERTR;
    char KZKDKLASSE[4];
    long FETCH_REL;
} distressroutingS;
#else /* TRANSCLASS */
typedef struct N_DISTRESSROUTING {
    short BRANCHNO;
    long CUSTOMERNO;
    short DESTBRANCHNO;
    char NAMEAPO[41];
    char ORT[31];
    char POSTLEITZAHL[11];
    long PERSONALNRVERTR;
    char KZKDKLASSE[4];
    long FETCH_REL;
    bool operator == (const N_DISTRESSROUTING& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            DESTBRANCHNO == right.DESTBRANCHNO &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(POSTLEITZAHL, right.POSTLEITZAHL) &&
            PERSONALNRVERTR == right.PERSONALNRVERTR &&
            !strcmp(KZKDKLASSE, right.KZKDKLASSE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        DESTBRANCHNO = 0;
        strcpy(NAMEAPO, " " );
        strcpy(ORT, " " );
        strcpy(POSTLEITZAHL, " " );
        PERSONALNRVERTR = 0;
        strcpy(KZKDKLASSE, " " );
#endif
    }
} distressroutingS;
#endif /* TRANSCLASS */

/* original struct of ENCLOSERTIMES *******************************************/

#ifndef TRANSCLASS
typedef struct N_ENCLOSERTIMES {
    short BRANCHNO;
    long CUSTOMERNO;
    short TIMEDIFF;
    short MAXPOSITIONS;
    long KUNDENNR;
    long FETCH_REL;
} enclosertimesS;
#else /* TRANSCLASS */
typedef struct N_ENCLOSERTIMES {
    short BRANCHNO;
    long CUSTOMERNO;
    short TIMEDIFF;
    short MAXPOSITIONS;
    long KUNDENNR;
    long FETCH_REL;
    bool operator == (const N_ENCLOSERTIMES& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            TIMEDIFF == right.TIMEDIFF &&
            MAXPOSITIONS == right.MAXPOSITIONS &&
            KUNDENNR == right.KUNDENNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        TIMEDIFF = 0;
        MAXPOSITIONS = 0;
        KUNDENNR = 0;
#endif
    }
} enclosertimesS;
#endif /* TRANSCLASS */

/* original struct of KNDTOURFENSTER ******************************************/

#ifndef TRANSCLASS
typedef struct N_KNDTOURFENSTER {
    long CUSTOMERNO;
    char TOURID[7];
    short BRANCHNO;
    short WEEKDAY;
    long FROMTIME;
    long TOTIME;
    long MAINTIME;
    long FETCH_REL;
} kndtourfensterS;
#else /* TRANSCLASS */
typedef struct N_KNDTOURFENSTER {
    long CUSTOMERNO;
    char TOURID[7];
    short BRANCHNO;
    short WEEKDAY;
    long FROMTIME;
    long TOTIME;
    long MAINTIME;
    long FETCH_REL;
    bool operator == (const N_KNDTOURFENSTER& right) const {
        return (
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(TOURID, right.TOURID) &&
            BRANCHNO == right.BRANCHNO &&
            WEEKDAY == right.WEEKDAY &&
            FROMTIME == right.FROMTIME &&
            TOTIME == right.TOTIME &&
            MAINTIME == right.MAINTIME
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CUSTOMERNO = 0;
        strcpy(TOURID, " " );
        BRANCHNO = 0;
        WEEKDAY = 0;
        FROMTIME = 0;
        TOTIME = 0;
        MAINTIME = 0;
#endif
    }
} kndtourfensterS;
#endif /* TRANSCLASS */

/* original struct of KNDTOURWOCHE ********************************************/

#ifndef TRANSCLASS
typedef struct N_KNDTOURWOCHE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short WEEKDAY;
    char ISTVERBUNDTOUR[2];
    char KDAUFTRAGART[3];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short PHARMACYLOCKACCESS;
    char REMARKLACKITEMPROCESSING[41];
    short RETURNSTOUR;
    char REMARKLACKCALLBACK[41];
    short TRANSPEXCLPSYCHO;
    short TRANSPEXCLCOOLED;
    short TRANSPEXCLEXPENSIVE;
    short CHECKPOSITIONS;
    char CHECKREMARK[41];
    long PLANNEDCALL;
    char KZAUTOZUORD[2];
    short SCHECKORDER;
    short CHECKTIMETOTOUR;
    char BEMERKUNGEN[241];
    char TOURID[7];
    char TAGESTYP[7];
    long FETCH_REL;
} kndtourwocheS;
#else /* TRANSCLASS */
typedef struct N_KNDTOURWOCHE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short WEEKDAY;
    char ISTVERBUNDTOUR[2];
    char KDAUFTRAGART[3];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short PHARMACYLOCKACCESS;
    char REMARKLACKITEMPROCESSING[41];
    short RETURNSTOUR;
    char REMARKLACKCALLBACK[41];
    short TRANSPEXCLPSYCHO;
    short TRANSPEXCLCOOLED;
    short TRANSPEXCLEXPENSIVE;
    short CHECKPOSITIONS;
    char CHECKREMARK[41];
    long PLANNEDCALL;
    char KZAUTOZUORD[2];
    short SCHECKORDER;
    short CHECKTIMETOTOUR;
    char BEMERKUNGEN[241];
    char TOURID[7];
    char TAGESTYP[7];
    long FETCH_REL;
    bool operator == (const N_KNDTOURWOCHE& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            WEEKDAY == right.WEEKDAY &&
            !strcmp(ISTVERBUNDTOUR, right.ISTVERBUNDTOUR) &&
            !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
            ISBTM == right.ISBTM &&
            ISKK == right.ISKK &&
            ISK08 == right.ISK08 &&
            ISK20 == right.ISK20 &&
            PHARMACYLOCKACCESS == right.PHARMACYLOCKACCESS &&
            !strcmp(REMARKLACKITEMPROCESSING, right.REMARKLACKITEMPROCESSING) &&
            RETURNSTOUR == right.RETURNSTOUR &&
            !strcmp(REMARKLACKCALLBACK, right.REMARKLACKCALLBACK) &&
            TRANSPEXCLPSYCHO == right.TRANSPEXCLPSYCHO &&
            TRANSPEXCLCOOLED == right.TRANSPEXCLCOOLED &&
            TRANSPEXCLEXPENSIVE == right.TRANSPEXCLEXPENSIVE &&
            CHECKPOSITIONS == right.CHECKPOSITIONS &&
            !strcmp(CHECKREMARK, right.CHECKREMARK) &&
            PLANNEDCALL == right.PLANNEDCALL &&
            !strcmp(KZAUTOZUORD, right.KZAUTOZUORD) &&
            SCHECKORDER == right.SCHECKORDER &&
            CHECKTIMETOTOUR == right.CHECKTIMETOTOUR &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(TAGESTYP, right.TAGESTYP)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        WEEKDAY = 0;
        strcpy(ISTVERBUNDTOUR, " " );
        strcpy(KDAUFTRAGART, " " );
        ISBTM = 0;
        ISKK = 0;
        ISK08 = 0;
        ISK20 = 0;
        PHARMACYLOCKACCESS = 0;
        strcpy(REMARKLACKITEMPROCESSING, " " );
        RETURNSTOUR = 0;
        strcpy(REMARKLACKCALLBACK, " " );
        TRANSPEXCLPSYCHO = 0;
        TRANSPEXCLCOOLED = 0;
        TRANSPEXCLEXPENSIVE = 0;
        CHECKPOSITIONS = 0;
        strcpy(CHECKREMARK, " " );
        PLANNEDCALL = 0;
        strcpy(KZAUTOZUORD, " " );
        SCHECKORDER = 0;
        CHECKTIMETOTOUR = 0;
        strcpy(BEMERKUNGEN, " " );
        strcpy(TOURID, " " );
        strcpy(TAGESTYP, " " );
#endif
    }
} kndtourwocheS;
#endif /* TRANSCLASS */

/* original struct of KNDTOURWOCHE2 *******************************************/

#ifndef TRANSCLASS
typedef struct N_KNDTOURWOCHE2 {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TOURID[7];
    long DATUMKOMMI;
    long CONSTIME;
    long FETCH_REL;
} kndtourwoche2S;
#else /* TRANSCLASS */
typedef struct N_KNDTOURWOCHE2 {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TOURID[7];
    long DATUMKOMMI;
    long CONSTIME;
    long FETCH_REL;
    bool operator == (const N_KNDTOURWOCHE2& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(TOURID, right.TOURID) &&
            DATUMKOMMI == right.DATUMKOMMI &&
            CONSTIME == right.CONSTIME
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(TOURID, " " );
        DATUMKOMMI = 0;
        CONSTIME = 0;
#endif
    }
} kndtourwoche2S;
#endif /* TRANSCLASS */

/* original struct of KNDTOURWOCHE3 *******************************************/

#ifndef TRANSCLASS
typedef struct N_KNDTOURWOCHE3 {
    short FILIALNR;
    char TOURID[7];
    long DATUMKOMMI;
    long CONSTIME;
    long FETCH_REL;
} kndtourwoche3S;
#else /* TRANSCLASS */
typedef struct N_KNDTOURWOCHE3 {
    short FILIALNR;
    char TOURID[7];
    long DATUMKOMMI;
    long CONSTIME;
    long FETCH_REL;
    bool operator == (const N_KNDTOURWOCHE3& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            !strcmp(TOURID, right.TOURID) &&
            DATUMKOMMI == right.DATUMKOMMI &&
            CONSTIME == right.CONSTIME
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        strcpy(TOURID, " " );
        DATUMKOMMI = 0;
        CONSTIME = 0;
#endif
    }
} kndtourwoche3S;
#endif /* TRANSCLASS */

/* original struct of KNDFILINFO **********************************************/

#ifndef TRANSCLASS
typedef struct N_KNDFILINFO {
    long KUNDENNR;
    short VERTRIEBSZENTRUMNR;
    double DISPOGEBUEHR;
    double BTMGEBUEHR;
    double DOKUGEBUEHR;
    long TOURENKIPPZEIT;
} kndfilinfoS;
#else /* TRANSCLASS */
typedef struct N_KNDFILINFO {
    long KUNDENNR;
    short VERTRIEBSZENTRUMNR;
    double DISPOGEBUEHR;
    double BTMGEBUEHR;
    double DOKUGEBUEHR;
    long TOURENKIPPZEIT;

    bool operator == (const N_KNDFILINFO& right) const {
        return (
            KUNDENNR == right.KUNDENNR &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            DISPOGEBUEHR == right.DISPOGEBUEHR &&
            BTMGEBUEHR == right.BTMGEBUEHR &&
            DOKUGEBUEHR == right.DOKUGEBUEHR &&
            TOURENKIPPZEIT == right.TOURENKIPPZEIT
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KUNDENNR = 0;
        VERTRIEBSZENTRUMNR = 0;
        DISPOGEBUEHR = 0;
        BTMGEBUEHR = 0;
        DOKUGEBUEHR = 0;
        TOURENKIPPZEIT = 0;
#endif
    }
} kndfilinfoS;
#endif /* TRANSCLASS */

/* original struct of KNDFILINFO2 *********************************************/

#ifndef TRANSCLASS
typedef struct N_KNDFILINFO2 {
    short FILIALNR;
    long DURCHLAUFNORMAL;
    long DURCHLAUFEILBOTE;
    long TOURVERSPAETUNG;
    long TOURENKIPPZEIT;
} kndfilinfo2S;
#else /* TRANSCLASS */
typedef struct N_KNDFILINFO2 {
    short FILIALNR;
    long DURCHLAUFNORMAL;
    long DURCHLAUFEILBOTE;
    long TOURVERSPAETUNG;
    long TOURENKIPPZEIT;

    bool operator == (const N_KNDFILINFO2& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            DURCHLAUFNORMAL == right.DURCHLAUFNORMAL &&
            DURCHLAUFEILBOTE == right.DURCHLAUFEILBOTE &&
            TOURVERSPAETUNG == right.TOURVERSPAETUNG &&
            TOURENKIPPZEIT == right.TOURENKIPPZEIT
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        DURCHLAUFNORMAL = 0;
        DURCHLAUFEILBOTE = 0;
        TOURVERSPAETUNG = 0;
        TOURENKIPPZEIT = 0;
#endif
    }
} kndfilinfo2S;
#endif /* TRANSCLASS */

/* original struct of KREDITLIMIT *********************************************/

#ifndef TRANSCLASS
typedef struct N_KREDITLIMIT {
    long PARTNERNO;
    char PARTNERNAME[31];
    double LIMIT;
    double SUM_DEBITSIDE;
    double SUM_CREDITSIDE;
    double SUM_MONTURNOVER;
    double SUM_DAYTURNOVER;
    double SUM_RETURNS;
    double SUM_GOODSRECEIPT;
    short LIMITTYPE;
    char LISTE5[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
} kreditlimitS;
#else /* TRANSCLASS */
typedef struct N_KREDITLIMIT {
    long PARTNERNO;
    char PARTNERNAME[31];
    double LIMIT;
    double SUM_DEBITSIDE;
    double SUM_CREDITSIDE;
    double SUM_MONTURNOVER;
    double SUM_DAYTURNOVER;
    double SUM_RETURNS;
    double SUM_GOODSRECEIPT;
    short LIMITTYPE;
    char LISTE5[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;

    bool operator == (const N_KREDITLIMIT& right) const {
        return (
            PARTNERNO == right.PARTNERNO &&
            !strcmp(PARTNERNAME, right.PARTNERNAME) &&
            LIMIT == right.LIMIT &&
            SUM_DEBITSIDE == right.SUM_DEBITSIDE &&
            SUM_CREDITSIDE == right.SUM_CREDITSIDE &&
            SUM_MONTURNOVER == right.SUM_MONTURNOVER &&
            SUM_DAYTURNOVER == right.SUM_DAYTURNOVER &&
            SUM_RETURNS == right.SUM_RETURNS &&
            SUM_GOODSRECEIPT == right.SUM_GOODSRECEIPT &&
            LIMITTYPE == right.LIMITTYPE &&
            !strcmp(LISTE5, right.LISTE5) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        PARTNERNO = 0;
        strcpy(PARTNERNAME, " " );
        LIMIT = 0;
        SUM_DEBITSIDE = 0;
        SUM_CREDITSIDE = 0;
        SUM_MONTURNOVER = 0;
        SUM_DAYTURNOVER = 0;
        SUM_RETURNS = 0;
        SUM_GOODSRECEIPT = 0;
        LIMITTYPE = 0;
        strcpy(LISTE5, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
#endif
    }
} kreditlimitS;
#endif /* TRANSCLASS */

/* original struct of KUNDELIZENSEN *******************************************/

#ifndef TRANSCLASS
typedef struct N_KUNDELIZENSEN {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char APOLIZENS[21];
    char BTMLIZENS[21];
} kundelizensenS;
#else /* TRANSCLASS */
typedef struct N_KUNDELIZENSEN {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char APOLIZENS[21];
    char BTMLIZENS[21];

    bool operator == (const N_KUNDELIZENSEN& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(APOLIZENS, right.APOLIZENS) &&
            !strcmp(BTMLIZENS, right.BTMLIZENS)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(APOLIZENS, " " );
        strcpy(BTMLIZENS, " " );
#endif
    }
} kundelizensenS;
#endif /* TRANSCLASS */

/* original struct of KUNDEVERBUNDFILIALE *************************************/

#ifndef TRANSCLASS
typedef struct N_KUNDEVERBUNDFILIALE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long REIHENFOLGENR;
    short VERBUNDFILIALNR;
    long FETCH_REL;
} kundeverbundfilialeS;
#else /* TRANSCLASS */
typedef struct N_KUNDEVERBUNDFILIALE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long REIHENFOLGENR;
    short VERBUNDFILIALNR;
    long FETCH_REL;
    bool operator == (const N_KUNDEVERBUNDFILIALE& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            REIHENFOLGENR == right.REIHENFOLGENR &&
            VERBUNDFILIALNR == right.VERBUNDFILIALNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        REIHENFOLGENR = 0;
        VERBUNDFILIALNR = 0;
#endif
    }
} kundeverbundfilialeS;
#endif /* TRANSCLASS */

/* original struct of LISTE5 **************************************************/

#ifndef TRANSCLASS
typedef struct N_LISTE5 {
    short BRANCHNO;
    long ARTICLENO;
    double PREISEKAPO;
    long CUSTOMERNO;
    short PREIS_TYP;
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
} liste5S;
#else /* TRANSCLASS */
typedef struct N_LISTE5 {
    short BRANCHNO;
    long ARTICLENO;
    double PREISEKAPO;
    long CUSTOMERNO;
    short PREIS_TYP;
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
    bool operator == (const N_LISTE5& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            ARTICLENO == right.ARTICLENO &&
            PREISEKAPO == right.PREISEKAPO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            PREIS_TYP == right.PREIS_TYP &&
            TAXLEVEL == right.TAXLEVEL &&
            !strcmp(ARTIKEL_LANGNAME, right.ARTIKEL_LANGNAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        ARTICLENO = 0;
        PREISEKAPO = 0;
        CUSTOMERNO = 0;
        PREIS_TYP = 0;
        TAXLEVEL = 0;
        strcpy(ARTIKEL_LANGNAME, " " );
#endif
    }
} liste5S;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMEREMERGENCYSERVICEPLAN ***************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMEREMERGENCYSERVICEPLAN {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long UHRZEITVON;
    long UHRZEITBIS;
    char BEMERKUNGEN[241];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    long FETCH_REL;
} mcustomeremergencyserviceplanS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMEREMERGENCYSERVICEPLAN {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long UHRZEITVON;
    long UHRZEITBIS;
    char BEMERKUNGEN[241];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    long FETCH_REL;
    bool operator == (const N_MCUSTOMEREMERGENCYSERVICEPLAN& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            DATUM == right.DATUM &&
            UHRZEITVON == right.UHRZEITVON &&
            UHRZEITBIS == right.UHRZEITBIS &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            ISBTM == right.ISBTM &&
            ISKK == right.ISKK &&
            ISK08 == right.ISK08 &&
            ISK20 == right.ISK20
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        DATUM = 0;
        UHRZEITVON = 0;
        UHRZEITBIS = 0;
        strcpy(BEMERKUNGEN, " " );
        ISBTM = 0;
        ISKK = 0;
        ISK08 = 0;
        ISK20 = 0;
#endif
    }
} mcustomeremergencyserviceplanS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERVACATION ***************************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERVACATION {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUMGUELTIGAB;
    long DATUMGUELTIGBIS;
    long FETCH_REL;
} mcustomervacationS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERVACATION {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUMGUELTIGAB;
    long DATUMGUELTIGBIS;
    long FETCH_REL;
    bool operator == (const N_MCUSTOMERVACATION& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            DATUMGUELTIGAB == right.DATUMGUELTIGAB &&
            DATUMGUELTIGBIS == right.DATUMGUELTIGBIS
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        DATUMGUELTIGAB = 0;
        DATUMGUELTIGBIS = 0;
#endif
    }
} mcustomervacationS;
#endif /* TRANSCLASS */

/* original struct of PAYTERM *************************************************/

#ifndef TRANSCLASS
typedef struct N_PAYTERM {
    char PAYMENT_TERM[5];
    short PAYMENTARGET;
    double CASHDISOUNT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
} paytermS;
#else /* TRANSCLASS */
typedef struct N_PAYTERM {
    char PAYMENT_TERM[5];
    short PAYMENTARGET;
    double CASHDISOUNT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
    bool operator == (const N_PAYTERM& right) const {
        return (
            !strcmp(PAYMENT_TERM, right.PAYMENT_TERM) &&
            PAYMENTARGET == right.PAYMENTARGET &&
            CASHDISOUNT == right.CASHDISOUNT &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(PAYMENT_TERM, " " );
        PAYMENTARGET = 0;
        CASHDISOUNT = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
#endif
    }
} paytermS;
#endif /* TRANSCLASS */

/* original struct of PAYMENTLIST *********************************************/

#ifndef TRANSCLASS
typedef struct N_PAYMENTLIST {
    short BRANCHNO;
    long CUSTOMERNO;
    char INVOICENUMBER[16];
    double TOTALINVOICEAMOUNT;
    double OPENINVOICEAMOUNT;
    double PAIDINVOICEAMOUNT;
    long DRIVERID;
    long PAYMENTDATE;
    long INVOICEDATE;
    char PAYMENTSPEC[2];
    long FETCH_REL;
} paymentlistS;
#else /* TRANSCLASS */
typedef struct N_PAYMENTLIST {
    short BRANCHNO;
    long CUSTOMERNO;
    char INVOICENUMBER[16];
    double TOTALINVOICEAMOUNT;
    double OPENINVOICEAMOUNT;
    double PAIDINVOICEAMOUNT;
    long DRIVERID;
    long PAYMENTDATE;
    long INVOICEDATE;
    char PAYMENTSPEC[2];
    long FETCH_REL;
    bool operator == (const N_PAYMENTLIST& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            !strcmp(INVOICENUMBER, right.INVOICENUMBER) &&
            TOTALINVOICEAMOUNT == right.TOTALINVOICEAMOUNT &&
            OPENINVOICEAMOUNT == right.OPENINVOICEAMOUNT &&
            PAIDINVOICEAMOUNT == right.PAIDINVOICEAMOUNT &&
            DRIVERID == right.DRIVERID &&
            PAYMENTDATE == right.PAYMENTDATE &&
            INVOICEDATE == right.INVOICEDATE &&
            !strcmp(PAYMENTSPEC, right.PAYMENTSPEC)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        strcpy(INVOICENUMBER, " " );
        TOTALINVOICEAMOUNT = 0;
        OPENINVOICEAMOUNT = 0;
        PAIDINVOICEAMOUNT = 0;
        DRIVERID = 0;
        PAYMENTDATE = 0;
        INVOICEDATE = 0;
        strcpy(PAYMENTSPEC, " " );
#endif
    }
} paymentlistS;
#endif /* TRANSCLASS */

/* original struct of PREWHOLECST *********************************************/

#ifndef TRANSCLASS
typedef struct N_PREWHOLECST {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long MAINCSTNO;
} prewholecstS;
#else /* TRANSCLASS */
typedef struct N_PREWHOLECST {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long MAINCSTNO;

    bool operator == (const N_PREWHOLECST& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            MAINCSTNO == right.MAINCSTNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        MAINCSTNO = 0;
#endif
    }
} prewholecstS;
#endif /* TRANSCLASS */

/* original struct of SHIPAUXNO ***********************************************/

#ifndef TRANSCLASS
typedef struct N_SHIPAUXNO {
    short BRANCHNO;
    long CUSTOMERNO;
    short AUXBRANCHNO;
    long AUXBGANO;
    long FETCH_REL;
} shipauxnoS;
#else /* TRANSCLASS */
typedef struct N_SHIPAUXNO {
    short BRANCHNO;
    long CUSTOMERNO;
    short AUXBRANCHNO;
    long AUXBGANO;
    long FETCH_REL;
    bool operator == (const N_SHIPAUXNO& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            AUXBRANCHNO == right.AUXBRANCHNO &&
            AUXBGANO == right.AUXBGANO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        AUXBRANCHNO = 0;
        AUXBGANO = 0;
#endif
    }
} shipauxnoS;
#endif /* TRANSCLASS */

/* original struct of TOURPFLEGE **********************************************/

#ifndef TRANSCLASS
typedef struct N_TOURPFLEGE {
    char TOURID[7];
    long REIHENFOLGENR;
    long FAHRTZEIT;
    char BEMERKUNGEN[241];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    char KOART[2];
    long FETCH_REL;
} tourpflegeS;
#else /* TRANSCLASS */
typedef struct N_TOURPFLEGE {
    char TOURID[7];
    long REIHENFOLGENR;
    long FAHRTZEIT;
    char BEMERKUNGEN[241];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    char KOART[2];
    long FETCH_REL;
    bool operator == (const N_TOURPFLEGE& right) const {
        return (
            !strcmp(TOURID, right.TOURID) &&
            REIHENFOLGENR == right.REIHENFOLGENR &&
            FAHRTZEIT == right.FAHRTZEIT &&
            !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME &&
            LOGINID == right.LOGINID &&
            !strcmp(CHANGEID, right.CHANGEID) &&
            !strcmp(KOART, right.KOART)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(TOURID, " " );
        REIHENFOLGENR = 0;
        FAHRTZEIT = 0;
        strcpy(BEMERKUNGEN, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        TM_DATE = 0;
        TM_TIME = 0;
        LOGINID = 0;
        strcpy(CHANGEID, " " );
        strcpy(KOART, " " );
#endif
    }
} tourpflegeS;
#endif /* TRANSCLASS */

/* original struct of DELAYEDCST **********************************************/

#ifndef TRANSCLASS
typedef struct N_DELAYEDCST {
    short BRANCHNO;
    long CUSTOMERNO;
    short WEEKDAY;
    long TIME;
    char TOURID[7];
    char ACTIV[2];
    short DELAYEDWEEKDAY;
    char NARCOTIC[2];
    char COLDCHAIN[2];
    char COOL08[2];
    char COOL20[2];
    long FETCH_REL;
} delayedcstS;
#else /* TRANSCLASS */
typedef struct N_DELAYEDCST {
    short BRANCHNO;
    long CUSTOMERNO;
    short WEEKDAY;
    long TIME;
    char TOURID[7];
    char ACTIV[2];
    short DELAYEDWEEKDAY;
    char NARCOTIC[2];
    char COLDCHAIN[2];
    char COOL08[2];
    char COOL20[2];
    long FETCH_REL;
    bool operator == (const N_DELAYEDCST& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            WEEKDAY == right.WEEKDAY &&
            TIME == right.TIME &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(ACTIV, right.ACTIV) &&
            DELAYEDWEEKDAY == right.DELAYEDWEEKDAY &&
            !strcmp(NARCOTIC, right.NARCOTIC) &&
            !strcmp(COLDCHAIN, right.COLDCHAIN) &&
            !strcmp(COOL08, right.COOL08) &&
            !strcmp(COOL20, right.COOL20)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        WEEKDAY = 0;
        TIME = 0;
        strcpy(TOURID, " " );
        strcpy(ACTIV, " " );
        DELAYEDWEEKDAY = 0;
        strcpy(NARCOTIC, " " );
        strcpy(COLDCHAIN, " " );
        strcpy(COOL08, " " );
        strcpy(COOL20, " " );
#endif
    }
} delayedcstS;
#endif /* TRANSCLASS */

/* original struct of DELAYEDDELIVERYCSTSPECIAL *******************************/

#ifndef TRANSCLASS
typedef struct N_DELAYEDDELIVERYCSTSPECIAL {
    short BRANCHNO;
    long CUSTOMERNO;
    short WEEKDAY;
    long TIME;
    char ACTIV[2];
    short DELAYEDWEEKDAY;
    char NARCOTIC[2];
    char COLDCHAIN[2];
    char COOL08[2];
    char COOL20[2];
    long DATEFROM;
    long DATETO;
    long FETCH_REL;
} delayeddeliverycstspecialS;
#else /* TRANSCLASS */
typedef struct N_DELAYEDDELIVERYCSTSPECIAL {
    short BRANCHNO;
    long CUSTOMERNO;
    short WEEKDAY;
    long TIME;
    char ACTIV[2];
    short DELAYEDWEEKDAY;
    char NARCOTIC[2];
    char COLDCHAIN[2];
    char COOL08[2];
    char COOL20[2];
    long DATEFROM;
    long DATETO;
    long FETCH_REL;
    bool operator == (const N_DELAYEDDELIVERYCSTSPECIAL& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            CUSTOMERNO == right.CUSTOMERNO &&
            WEEKDAY == right.WEEKDAY &&
            TIME == right.TIME &&
            !strcmp(ACTIV, right.ACTIV) &&
            DELAYEDWEEKDAY == right.DELAYEDWEEKDAY &&
            !strcmp(NARCOTIC, right.NARCOTIC) &&
            !strcmp(COLDCHAIN, right.COLDCHAIN) &&
            !strcmp(COOL08, right.COOL08) &&
            !strcmp(COOL20, right.COOL20) &&
            DATEFROM == right.DATEFROM &&
            DATETO == right.DATETO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        CUSTOMERNO = 0;
        WEEKDAY = 0;
        TIME = 0;
        strcpy(ACTIV, " " );
        DELAYEDWEEKDAY = 0;
        strcpy(NARCOTIC, " " );
        strcpy(COLDCHAIN, " " );
        strcpy(COOL08, " " );
        strcpy(COOL20, " " );
        DATEFROM = 0;
        DATETO = 0;
#endif
    }
} delayeddeliverycstspecialS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CHAINCUSTOMERS ******************************/

struct C_CHAINCUSTOMERS {
    char NAMEAPO[41];
    char STRASSE[31];
    char ORT[31];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long MAINCSTNO;
    long FETCH_REL;
};
/* Structur with real chartype of CHECKCUSTOMEREXIST **************************/

struct C_CHECKCUSTOMEREXIST {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
};
/* Structur with real chartype of CHECKLISTE5 *********************************/

struct C_CHECKLISTE5 {
    short BRANCHNO;
    long ARTICLENO;
    long CUSTOMERNO;
};
/* Structur with real chartype of CSTBRANCHINFO *******************************/

struct C_CSTBRANCHINFO {
    short BRANCHNO;
    long LFDNR;
    char INFOTEXT[257];
    long DATETO;
    long TIMETO;
    long FETCH_REL;
};
/* Structur with real chartype of CSTBULGARIA *********************************/

struct C_CSTBULGARIA {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short REBATEMETHFREESALE;
    short REBATEMETHHEALTHF;
    long MAINCSTNO;
};
/* Structur with real chartype of CSTBUYINGOPTIONS ****************************/

struct C_CSTBUYINGOPTIONS {
    long ETARTKLASSE1;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char KZPSYCHOSTOFFE;
};
/* Structur with real chartype of CSTDISCACC **********************************/

struct C_CSTDISCACC {
    short BRANCHNO;
    long CUSTOMERNO;
    long MAINCSTNO;
    long DATUM;
    double BALANCE;
    char UPD_FLAG;
    long KDAUFTRAGNR;
    long DATE;
    char INVOICENUMBER[16];
    double INVOICEAMOUNT;
    char VOUCHERTYP[3];
    short PREIS_TYP;
    short PRIORITY;
    long KDAUFTRAGNRSPLIT;
    double INVOICEPAID;
    short PAYMENTARGET;
    long LFDNR;
    long FETCH_REL;
};
/* Structur with real chartype of CSTDISCACCANZ *******************************/

struct C_CSTDISCACCANZ {
    short BRANCHNO;
    long CUSTOMERNO;
    long MAINCSTNO;
    char NAMEAPO[41];
    char STRASSE[31];
    char ORT[31];
    long FETCH_REL;
};
/* Structur with real chartype of CSTDISCCONT *********************************/

struct C_CSTDISCCONT {
    short BRANCHNO;
    long CUSTOMERNO;
    char ORDER_TYPE[3];
    char PHARMACYGROUPID[4];
    char SUB_ORDER_TYPE[4];
    char PAYMENT_TERM[5];
    short VALUTA_DAYS;
    double MIN_ORDER_VALUE;
    short MIN_TUBES;
    double LOSS_IN_DISCOUNT;
    char UPD_FLAG;
    long FETCH_REL;
};
/* Structur with real chartype of CSTPAYTERM **********************************/

struct C_CSTPAYTERM {
    short BRANCHNO;
    long CUSTOMERNO;
    short PREIS_TYP;
    short PAYMENTARGET;
    long FETCH_REL;
};
/* Structur with real chartype of CSTREBATETYPE *******************************/

struct C_CSTREBATETYPE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short REBATEMETHFREESALE;
    short REBATEMETHHEALTHF;
};
/* Structur with real chartype of CUSTPHARMA **********************************/

struct C_CUSTPHARMA {
    long CUSTOMERNO;
    short BRANCHNO;
    char PHARMACYGROUPID[4];
    short RANKING;
    long FETCH_REL;
};
/* Structur with real chartype of CUSTPHON ************************************/

struct C_CUSTPHON {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TELNR[21];
    long DATUM;
    long FETCH_REL;
};
/* Structur with real chartype of CUSTROUT ************************************/

struct C_CUSTROUT {
    long CUSTOMERNO;
    short BRANCHNO;
    long TIMEFROM;
    long TIMETO;
    short DESTBRANCHNO;
    char DAYOFWEEK[3];
    short WEEKDAY;
    long ZEIT_VON;
    long FETCH_REL;
};
/* Structur with real chartype of CUSTOMERDOUBLES *****************************/

struct C_CUSTOMERDOUBLES {
    char NAME[31];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
};
/* Structur with real chartype of DISTRESSROUTING *****************************/

struct C_DISTRESSROUTING {
    short BRANCHNO;
    long CUSTOMERNO;
    short DESTBRANCHNO;
    char NAMEAPO[41];
    char ORT[31];
    char POSTLEITZAHL[11];
    long PERSONALNRVERTR;
    char KZKDKLASSE[4];
    long FETCH_REL;
};
/* Structur with real chartype of ENCLOSERTIMES *******************************/

struct C_ENCLOSERTIMES {
    short BRANCHNO;
    long CUSTOMERNO;
    short TIMEDIFF;
    short MAXPOSITIONS;
    long KUNDENNR;
    long FETCH_REL;
};
/* Structur with real chartype of KNDTOURFENSTER ******************************/

struct C_KNDTOURFENSTER {
    long CUSTOMERNO;
    char TOURID[7];
    short BRANCHNO;
    short WEEKDAY;
    long FROMTIME;
    long TOTIME;
    long MAINTIME;
    long FETCH_REL;
};
/* Structur with real chartype of KNDTOURWOCHE ********************************/

struct C_KNDTOURWOCHE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short WEEKDAY;
    char ISTVERBUNDTOUR;
    char KDAUFTRAGART[3];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short PHARMACYLOCKACCESS;
    char REMARKLACKITEMPROCESSING[41];
    short RETURNSTOUR;
    char REMARKLACKCALLBACK[41];
    short TRANSPEXCLPSYCHO;
    short TRANSPEXCLCOOLED;
    short TRANSPEXCLEXPENSIVE;
    short CHECKPOSITIONS;
    char CHECKREMARK[41];
    long PLANNEDCALL;
    char KZAUTOZUORD;
    short SCHECKORDER;
    short CHECKTIMETOTOUR;
    char BEMERKUNGEN[241];
    char TOURID[7];
    char TAGESTYP[7];
    long FETCH_REL;
};
/* Structur with real chartype of KNDTOURWOCHE2 *******************************/

struct C_KNDTOURWOCHE2 {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TOURID[7];
    long DATUMKOMMI;
    long CONSTIME;
    long FETCH_REL;
};
/* Structur with real chartype of KNDTOURWOCHE3 *******************************/

struct C_KNDTOURWOCHE3 {
    short FILIALNR;
    char TOURID[7];
    long DATUMKOMMI;
    long CONSTIME;
    long FETCH_REL;
};
/* Structur with real chartype of KNDFILINFO **********************************/

struct C_KNDFILINFO {
    long KUNDENNR;
    short VERTRIEBSZENTRUMNR;
    double DISPOGEBUEHR;
    double BTMGEBUEHR;
    double DOKUGEBUEHR;
    long TOURENKIPPZEIT;
};
/* Structur with real chartype of KNDFILINFO2 *********************************/

struct C_KNDFILINFO2 {
    short FILIALNR;
    long DURCHLAUFNORMAL;
    long DURCHLAUFEILBOTE;
    long TOURVERSPAETUNG;
    long TOURENKIPPZEIT;
};
/* Structur with real chartype of KREDITLIMIT *********************************/

struct C_KREDITLIMIT {
    long PARTNERNO;
    char PARTNERNAME[31];
    double LIMIT;
    double SUM_DEBITSIDE;
    double SUM_CREDITSIDE;
    double SUM_MONTURNOVER;
    double SUM_DAYTURNOVER;
    double SUM_RETURNS;
    double SUM_GOODSRECEIPT;
    short LIMITTYPE;
    char LISTE5;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
};
/* Structur with real chartype of KUNDELIZENSEN *******************************/

struct C_KUNDELIZENSEN {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char APOLIZENS[21];
    char BTMLIZENS[21];
};
/* Structur with real chartype of KUNDEVERBUNDFILIALE *************************/

struct C_KUNDEVERBUNDFILIALE {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long REIHENFOLGENR;
    short VERBUNDFILIALNR;
    long FETCH_REL;
};
/* Structur with real chartype of LISTE5 **************************************/

struct C_LISTE5 {
    short BRANCHNO;
    long ARTICLENO;
    double PREISEKAPO;
    long CUSTOMERNO;
    short PREIS_TYP;
    short TAXLEVEL;
    char ARTIKEL_LANGNAME[51];
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMEREMERGENCYSERVICEPLAN ***************/

struct C_MCUSTOMEREMERGENCYSERVICEPLAN {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long UHRZEITVON;
    long UHRZEITBIS;
    char BEMERKUNGEN[241];
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMERVACATION ***************************/

struct C_MCUSTOMERVACATION {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUMGUELTIGAB;
    long DATUMGUELTIGBIS;
    long FETCH_REL;
};
/* Structur with real chartype of PAYTERM *************************************/

struct C_PAYTERM {
    char PAYMENT_TERM[5];
    short PAYMENTARGET;
    double CASHDISOUNT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long FETCH_REL;
};
/* Structur with real chartype of PAYMENTLIST *********************************/

struct C_PAYMENTLIST {
    short BRANCHNO;
    long CUSTOMERNO;
    char INVOICENUMBER[16];
    double TOTALINVOICEAMOUNT;
    double OPENINVOICEAMOUNT;
    double PAIDINVOICEAMOUNT;
    long DRIVERID;
    long PAYMENTDATE;
    long INVOICEDATE;
    char PAYMENTSPEC;
    long FETCH_REL;
};
/* Structur with real chartype of PREWHOLECST *********************************/

struct C_PREWHOLECST {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long MAINCSTNO;
};
/* Structur with real chartype of SHIPAUXNO ***********************************/

struct C_SHIPAUXNO {
    short BRANCHNO;
    long CUSTOMERNO;
    short AUXBRANCHNO;
    long AUXBGANO;
    long FETCH_REL;
};
/* Structur with real chartype of TOURPFLEGE **********************************/

struct C_TOURPFLEGE {
    char TOURID[7];
    long REIHENFOLGENR;
    long FAHRTZEIT;
    char BEMERKUNGEN[241];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID;
    char KOART;
    long FETCH_REL;
};
/* Structur with real chartype of DELAYEDCST **********************************/

struct C_DELAYEDCST {
    short BRANCHNO;
    long CUSTOMERNO;
    short WEEKDAY;
    long TIME;
    char TOURID[7];
    char ACTIV;
    short DELAYEDWEEKDAY;
    char NARCOTIC;
    char COLDCHAIN;
    char COOL08;
    char COOL20;
    long FETCH_REL;
};
/* Structur with real chartype of DELAYEDDELIVERYCSTSPECIAL *******************/

struct C_DELAYEDDELIVERYCSTSPECIAL {
    short BRANCHNO;
    long CUSTOMERNO;
    short WEEKDAY;
    long TIME;
    char ACTIV;
    short DELAYEDWEEKDAY;
    char NARCOTIC;
    char COLDCHAIN;
    char COOL08;
    char COOL20;
    long DATEFROM;
    long DATETO;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CHAINCUSTOMERS ****************************/

struct I_CHAINCUSTOMERS {
    short NAMEAPO;
    short STRASSE;
    short ORT;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short MAINCSTNO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CHECKCUSTOMEREXIST ************************/

struct I_CHECKCUSTOMEREXIST {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
};
/* Sizetype  Structur (buf_desc) of CHECKLISTE5 *******************************/

struct I_CHECKLISTE5 {
    short BRANCHNO;
    short ARTICLENO;
    short CUSTOMERNO;
};
/* Sizetype  Structur (buf_desc) of CSTBRANCHINFO *****************************/

struct I_CSTBRANCHINFO {
    short BRANCHNO;
    short LFDNR;
    short INFOTEXT;
    short DATETO;
    short TIMETO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CSTBULGARIA *******************************/

struct I_CSTBULGARIA {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short REBATEMETHFREESALE;
    short REBATEMETHHEALTHF;
    short MAINCSTNO;
};
/* Sizetype  Structur (buf_desc) of CSTBUYINGOPTIONS **************************/

struct I_CSTBUYINGOPTIONS {
    short ETARTKLASSE1;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short KZPSYCHOSTOFFE;
};
/* Sizetype  Structur (buf_desc) of CSTDISCACC ********************************/

struct I_CSTDISCACC {
    short BRANCHNO;
    short CUSTOMERNO;
    short MAINCSTNO;
    short DATUM;
    short BALANCE;
    short UPD_FLAG;
    short KDAUFTRAGNR;
    short DATE;
    short INVOICENUMBER;
    short INVOICEAMOUNT;
    short VOUCHERTYP;
    short PREIS_TYP;
    short PRIORITY;
    short KDAUFTRAGNRSPLIT;
    short INVOICEPAID;
    short PAYMENTARGET;
    short LFDNR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CSTDISCACCANZ *****************************/

struct I_CSTDISCACCANZ {
    short BRANCHNO;
    short CUSTOMERNO;
    short MAINCSTNO;
    short NAMEAPO;
    short STRASSE;
    short ORT;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CSTDISCCONT *******************************/

struct I_CSTDISCCONT {
    short BRANCHNO;
    short CUSTOMERNO;
    short ORDER_TYPE;
    short PHARMACYGROUPID;
    short SUB_ORDER_TYPE;
    short PAYMENT_TERM;
    short VALUTA_DAYS;
    short MIN_ORDER_VALUE;
    short MIN_TUBES;
    short LOSS_IN_DISCOUNT;
    short UPD_FLAG;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CSTPAYTERM ********************************/

struct I_CSTPAYTERM {
    short BRANCHNO;
    short CUSTOMERNO;
    short PREIS_TYP;
    short PAYMENTARGET;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CSTREBATETYPE *****************************/

struct I_CSTREBATETYPE {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short REBATEMETHFREESALE;
    short REBATEMETHHEALTHF;
};
/* Sizetype  Structur (buf_desc) of CUSTPHARMA ********************************/

struct I_CUSTPHARMA {
    short CUSTOMERNO;
    short BRANCHNO;
    short PHARMACYGROUPID;
    short RANKING;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CUSTPHON **********************************/

struct I_CUSTPHON {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short TELNR;
    short DATUM;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CUSTROUT **********************************/

struct I_CUSTROUT {
    short CUSTOMERNO;
    short BRANCHNO;
    short TIMEFROM;
    short TIMETO;
    short DESTBRANCHNO;
    short DAYOFWEEK;
    short WEEKDAY;
    short ZEIT_VON;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CUSTOMERDOUBLES ***************************/

struct I_CUSTOMERDOUBLES {
    short NAME;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of DISTRESSROUTING ***************************/

struct I_DISTRESSROUTING {
    short BRANCHNO;
    short CUSTOMERNO;
    short DESTBRANCHNO;
    short NAMEAPO;
    short ORT;
    short POSTLEITZAHL;
    short PERSONALNRVERTR;
    short KZKDKLASSE;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of ENCLOSERTIMES *****************************/

struct I_ENCLOSERTIMES {
    short BRANCHNO;
    short CUSTOMERNO;
    short TIMEDIFF;
    short MAXPOSITIONS;
    short KUNDENNR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of KNDTOURFENSTER ****************************/

struct I_KNDTOURFENSTER {
    short CUSTOMERNO;
    short TOURID;
    short BRANCHNO;
    short WEEKDAY;
    short FROMTIME;
    short TOTIME;
    short MAINTIME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of KNDTOURWOCHE ******************************/

struct I_KNDTOURWOCHE {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short WEEKDAY;
    short ISTVERBUNDTOUR;
    short KDAUFTRAGART;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short PHARMACYLOCKACCESS;
    short REMARKLACKITEMPROCESSING;
    short RETURNSTOUR;
    short REMARKLACKCALLBACK;
    short TRANSPEXCLPSYCHO;
    short TRANSPEXCLCOOLED;
    short TRANSPEXCLEXPENSIVE;
    short CHECKPOSITIONS;
    short CHECKREMARK;
    short PLANNEDCALL;
    short KZAUTOZUORD;
    short SCHECKORDER;
    short CHECKTIMETOTOUR;
    short BEMERKUNGEN;
    short TOURID;
    short TAGESTYP;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of KNDTOURWOCHE2 *****************************/

struct I_KNDTOURWOCHE2 {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short TOURID;
    short DATUMKOMMI;
    short CONSTIME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of KNDTOURWOCHE3 *****************************/

struct I_KNDTOURWOCHE3 {
    short FILIALNR;
    short TOURID;
    short DATUMKOMMI;
    short CONSTIME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of KNDFILINFO ********************************/

struct I_KNDFILINFO {
    short KUNDENNR;
    short VERTRIEBSZENTRUMNR;
    short DISPOGEBUEHR;
    short BTMGEBUEHR;
    short DOKUGEBUEHR;
    short TOURENKIPPZEIT;
};
/* Sizetype  Structur (buf_desc) of KNDFILINFO2 *******************************/

struct I_KNDFILINFO2 {
    short FILIALNR;
    short DURCHLAUFNORMAL;
    short DURCHLAUFEILBOTE;
    short TOURVERSPAETUNG;
    short TOURENKIPPZEIT;
};
/* Sizetype  Structur (buf_desc) of KREDITLIMIT *******************************/

struct I_KREDITLIMIT {
    short PARTNERNO;
    short PARTNERNAME;
    short LIMIT;
    short SUM_DEBITSIDE;
    short SUM_CREDITSIDE;
    short SUM_MONTURNOVER;
    short SUM_DAYTURNOVER;
    short SUM_RETURNS;
    short SUM_GOODSRECEIPT;
    short LIMITTYPE;
    short LISTE5;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
};
/* Sizetype  Structur (buf_desc) of KUNDELIZENSEN *****************************/

struct I_KUNDELIZENSEN {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short APOLIZENS;
    short BTMLIZENS;
};
/* Sizetype  Structur (buf_desc) of KUNDEVERBUNDFILIALE ***********************/

struct I_KUNDEVERBUNDFILIALE {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short REIHENFOLGENR;
    short VERBUNDFILIALNR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of LISTE5 ************************************/

struct I_LISTE5 {
    short BRANCHNO;
    short ARTICLENO;
    short PREISEKAPO;
    short CUSTOMERNO;
    short PREIS_TYP;
    short TAXLEVEL;
    short ARTIKEL_LANGNAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMEREMERGENCYSERVICEPLAN *************/

struct I_MCUSTOMEREMERGENCYSERVICEPLAN {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short DATUM;
    short UHRZEITVON;
    short UHRZEITBIS;
    short BEMERKUNGEN;
    short ISBTM;
    short ISKK;
    short ISK08;
    short ISK20;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERVACATION *************************/

struct I_MCUSTOMERVACATION {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short DATUMGUELTIGAB;
    short DATUMGUELTIGBIS;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of PAYTERM ***********************************/

struct I_PAYTERM {
    short PAYMENT_TERM;
    short PAYMENTARGET;
    short CASHDISOUNT;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of PAYMENTLIST *******************************/

struct I_PAYMENTLIST {
    short BRANCHNO;
    short CUSTOMERNO;
    short INVOICENUMBER;
    short TOTALINVOICEAMOUNT;
    short OPENINVOICEAMOUNT;
    short PAIDINVOICEAMOUNT;
    short DRIVERID;
    short PAYMENTDATE;
    short INVOICEDATE;
    short PAYMENTSPEC;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of PREWHOLECST *******************************/

struct I_PREWHOLECST {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short MAINCSTNO;
};
/* Sizetype  Structur (buf_desc) of SHIPAUXNO *********************************/

struct I_SHIPAUXNO {
    short BRANCHNO;
    short CUSTOMERNO;
    short AUXBRANCHNO;
    short AUXBGANO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of TOURPFLEGE ********************************/

struct I_TOURPFLEGE {
    short TOURID;
    short REIHENFOLGENR;
    short FAHRTZEIT;
    short BEMERKUNGEN;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short TM_DATE;
    short TM_TIME;
    short LOGINID;
    short CHANGEID;
    short KOART;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of DELAYEDCST ********************************/

struct I_DELAYEDCST {
    short BRANCHNO;
    short CUSTOMERNO;
    short WEEKDAY;
    short TIME;
    short TOURID;
    short ACTIV;
    short DELAYEDWEEKDAY;
    short NARCOTIC;
    short COLDCHAIN;
    short COOL08;
    short COOL20;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of DELAYEDDELIVERYCSTSPECIAL *****************/

struct I_DELAYEDDELIVERYCSTSPECIAL {
    short BRANCHNO;
    short CUSTOMERNO;
    short WEEKDAY;
    short TIME;
    short ACTIV;
    short DELAYEDWEEKDAY;
    short NARCOTIC;
    short COLDCHAIN;
    short COOL08;
    short COOL20;
    short DATEFROM;
    short DATETO;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CHAINCUSTOMERS **************************************/

#if defined (BUF_DESC)
static struct buf_desc CHAINCUSTOMERS_BES [] = {
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHAINCUSTOMERS_BES [] = {
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CHECKCUSTOMEREXIST **********************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKCUSTOMEREXIST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKCUSTOMEREXIST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CHECKLISTE5 *****************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKLISTE5_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKLISTE5_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CSTBRANCHINFO ***************************************/

#if defined (BUF_DESC)
static struct buf_desc CSTBRANCHINFO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L ,  11, 0 },
   { TYP_C, 256, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSTBRANCHINFO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L ,  11, 0 },
   { TYP_C, 256, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CSTBULGARIA *****************************************/

#if defined (BUF_DESC)
static struct buf_desc CSTBULGARIA_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSTBULGARIA_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CSTBUYINGOPTIONS ************************************/

#if defined (BUF_DESC)
static struct buf_desc CSTBUYINGOPTIONS_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSTBUYINGOPTIONS_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
};
#endif

/* Structur (buf_desc) of CSTDISCACC ******************************************/

#if defined (BUF_DESC)
static struct buf_desc CSTDISCACC_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_D, 11, 2 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSTDISCACC_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_D, 11, 2 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CSTDISCACCANZ ***************************************/

#if defined (BUF_DESC)
static struct buf_desc CSTDISCACCANZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSTDISCACCANZ_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CSTDISCCONT *****************************************/

#if defined (BUF_DESC)
static struct buf_desc CSTDISCCONT_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSTDISCCONT_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CSTPAYTERM ******************************************/

#if defined (BUF_DESC)
static struct buf_desc CSTPAYTERM_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSTPAYTERM_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CSTREBATETYPE ***************************************/

#if defined (BUF_DESC)
static struct buf_desc CSTREBATETYPE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSTREBATETYPE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of CUSTPHARMA ******************************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTPHARMA_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTPHARMA_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CUSTPHON ********************************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTPHON_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTPHON_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CUSTROUT ********************************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTROUT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTROUT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CUSTOMERDOUBLES *************************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTOMERDOUBLES_BES [] = {
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTOMERDOUBLES_BES [] = {
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of DISTRESSROUTING *************************************/

#if defined (BUF_DESC)
static struct buf_desc DISTRESSROUTING_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DISTRESSROUTING_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of ENCLOSERTIMES ***************************************/

#if defined (BUF_DESC)
static struct buf_desc ENCLOSERTIMES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc ENCLOSERTIMES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of KNDTOURFENSTER **************************************/

#if defined (BUF_DESC)
static struct buf_desc KNDTOURFENSTER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KNDTOURFENSTER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of KNDTOURWOCHE ****************************************/

#if defined (BUF_DESC)
static struct buf_desc KNDTOURWOCHE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KNDTOURWOCHE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of KNDTOURWOCHE2 ***************************************/

#if defined (BUF_DESC)
static struct buf_desc KNDTOURWOCHE2_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KNDTOURWOCHE2_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of KNDTOURWOCHE3 ***************************************/

#if defined (BUF_DESC)
static struct buf_desc KNDTOURWOCHE3_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KNDTOURWOCHE3_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of KNDFILINFO ******************************************/

#if defined (BUF_DESC)
static struct buf_desc KNDFILINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KNDFILINFO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of KNDFILINFO2 *****************************************/

#if defined (BUF_DESC)
static struct buf_desc KNDFILINFO2_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KNDFILINFO2_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of KREDITLIMIT *****************************************/

#if defined (BUF_DESC)
static struct buf_desc KREDITLIMIT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KREDITLIMIT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of KUNDELIZENSEN ***************************************/

#if defined (BUF_DESC)
static struct buf_desc KUNDELIZENSEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KUNDELIZENSEN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
};
#endif

/* Structur (buf_desc) of KUNDEVERBUNDFILIALE *********************************/

#if defined (BUF_DESC)
static struct buf_desc KUNDEVERBUNDFILIALE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc KUNDEVERBUNDFILIALE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of LISTE5 **********************************************/

#if defined (BUF_DESC)
static struct buf_desc LISTE5_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc LISTE5_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMEREMERGENCYSERVICEPLAN ***********************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMEREMERGENCYSERVICEPLAN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMEREMERGENCYSERVICEPLAN_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERVACATION ***********************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERVACATION_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERVACATION_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of PAYTERM *********************************************/

#if defined (BUF_DESC)
static struct buf_desc PAYTERM_BES [] = {
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PAYTERM_BES [] = {
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of PAYMENTLIST *****************************************/

#if defined (BUF_DESC)
static struct buf_desc PAYMENTLIST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PAYMENTLIST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of PREWHOLECST *****************************************/

#if defined (BUF_DESC)
static struct buf_desc PREWHOLECST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc PREWHOLECST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of SHIPAUXNO *******************************************/

#if defined (BUF_DESC)
static struct buf_desc SHIPAUXNO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SHIPAUXNO_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of TOURPFLEGE ******************************************/

#if defined (BUF_DESC)
static struct buf_desc TOURPFLEGE_BES [] = {
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc TOURPFLEGE_BES [] = {
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of DELAYEDCST ******************************************/

#if defined (BUF_DESC)
static struct buf_desc DELAYEDCST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELAYEDCST_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of DELAYEDDELIVERYCSTSPECIAL ***************************/

#if defined (BUF_DESC)
static struct buf_desc DELAYEDDELIVERYCSTSPECIAL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc DELAYEDDELIVERYCSTSPECIAL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of ChainCustomers ************************************/

#define CHAINCUSTOMERS_SELLIST 1584

/* FunctionNumber-Define of CheckCustomerExist ********************************/

#define CHECKCUSTOMEREXIST_SELEXIST 1457

/* FunctionNumber-Define of CheckListe5 ***************************************/

#define CHECKLISTE5_ISLISTE5 1591

/* FunctionNumber-Define of CstBranchInfo *************************************/

#define CSTBRANCHINFO_DELETE 1667
#define CSTBRANCHINFO_INSERT 1668
#define CSTBRANCHINFO_SELLIST 1664
#define CSTBRANCHINFO_SELLISTVALID 1665
#define CSTBRANCHINFO_UPDATE 1666

/* FunctionNumber-Define of CstBulgaria ***************************************/

#define CSTBULGARIA_SELCST 1533

/* FunctionNumber-Define of CstBuyingOptions **********************************/

#define CSTBUYINGOPTIONS_SELBUYINGOPTIONS 1745

/* FunctionNumber-Define of CstDiscAcc ****************************************/

#define CSTDISCACC_CHECKEXIST 1522
#define CSTDISCACC_SELLISTCST 1520
#define CSTDISCACC_SELLISTGRP 1521

/* FunctionNumber-Define of CstDiscAccAnz *************************************/

#define CSTDISCACCANZ_CHECKMAIN 1509
#define CSTDISCACCANZ_CHECKMEMBER 1510
#define CSTDISCACCANZ_SELLIST 1511
#define CSTDISCACCANZ_SELMAIN 1512

/* FunctionNumber-Define of CstDiscCont ***************************************/

#define CSTDISCCONT_SELLIST 1431

/* FunctionNumber-Define of CstPayTerm ****************************************/

#define CSTPAYTERM_SELLIST 1525

/* FunctionNumber-Define of CstRebateType *************************************/

#define CSTREBATETYPE_SELREBATETYPE 1531

/* FunctionNumber-Define of CustPharma ****************************************/

#define CUSTPHARMA_SELLIST 1346

/* FunctionNumber-Define of CustPhon ******************************************/

#define CUSTPHON_DELETE 1345
#define CUSTPHON_INSERT 1344
#define CUSTPHON_SELLIST 1343
#define CUSTPHON_SELPHONENO 1342

/* FunctionNumber-Define of CustRout ******************************************/

#define CUSTROUT_DELETE 1337
#define CUSTROUT_INSERT 1339
#define CUSTROUT_SELACTROUTING 1410
#define CUSTROUT_SELLIST 1335
#define CUSTROUT_UPDATE 1336

/* FunctionNumber-Define of CustomerDoubles ***********************************/

#define CUSTOMERDOUBLES_SELDOUBLE 1780

/* FunctionNumber-Define of DistressRouting ***********************************/

#define DISTRESSROUTING_GETCOUNT 1456
#define DISTRESSROUTING_SELNOT 1446
#define DISTRESSROUTING_SELROUTED 1447
#define DISTRESSROUTING_UPDATE 1448

/* FunctionNumber-Define of EncloserTimes *************************************/

#define ENCLOSERTIMES_COPYENCLOSER 1569
#define ENCLOSERTIMES_DELETE 1567
#define ENCLOSERTIMES_INSERT 1566
#define ENCLOSERTIMES_SELLIST 1565
#define ENCLOSERTIMES_UPDATE 1568

/* FunctionNumber-Define of KNDTOURFENSTER ************************************/

#define KNDTOURFENSTER_SELPERIODS 1722

/* FunctionNumber-Define of KNDTOURWOCHE **************************************/

#define KNDTOURWOCHE_SELLIST 1406

/* FunctionNumber-Define of KNDTOURWOCHE2 *************************************/

#define KNDTOURWOCHE2_SELLIST 1407

/* FunctionNumber-Define of KNDTOURWOCHE3 *************************************/

#define KNDTOURWOCHE3_SELLIST 1408

/* FunctionNumber-Define of KndFilInfo ****************************************/

#define KNDFILINFO_SELKND 1387

/* FunctionNumber-Define of KndFilInfo2 ***************************************/

#define KNDFILINFO2_SELINFO 1388

/* FunctionNumber-Define of KreditLimit ***************************************/

#define KREDITLIMIT_SELLIMIT 1485
#define KREDITLIMIT_SELLIMIT1 1585
#define KREDITLIMIT_SELLIMIT2 1586
#define KREDITLIMIT_SELLIMITMAIN 1587

/* FunctionNumber-Define of KundeLizensen *************************************/

#define KUNDELIZENSEN_SELLICENSES 1516

/* FunctionNumber-Define of KundeVerbundFiliale *******************************/

#define KUNDEVERBUNDFILIALE_DELETE 1278
#define KUNDEVERBUNDFILIALE_INSERT 1277
#define KUNDEVERBUNDFILIALE_SEL 1275
#define KUNDEVERBUNDFILIALE_UPDATE 1276

/* FunctionNumber-Define of Liste5 ********************************************/

#define LISTE5_SELLIST 1590

/* FunctionNumber-Define of MCustomerEmergencyServicePlan *********************/

#define MCUSTOMEREMERGENCYSERVICEPLAN_DELETE 1246
#define MCUSTOMEREMERGENCYSERVICEPLAN_INSERT 1245
#define MCUSTOMEREMERGENCYSERVICEPLAN_SELLIST 1242
#define MCUSTOMEREMERGENCYSERVICEPLAN_SELLISTHIST 1243
#define MCUSTOMEREMERGENCYSERVICEPLAN_SELUNI 1256
#define MCUSTOMEREMERGENCYSERVICEPLAN_UPDATE 1244

/* FunctionNumber-Define of MCustomerVacation *********************************/

#define MCUSTOMERVACATION_DELETE 1264
#define MCUSTOMERVACATION_INSERT 1263
#define MCUSTOMERVACATION_SELLIST 1262
#define MCUSTOMERVACATION_SELNEXTEFFECTIVE 1267
#define MCUSTOMERVACATION_SELUNI 1266
#define MCUSTOMERVACATION_UPDATE 1265

/* FunctionNumber-Define of PayTerm *******************************************/

#define PAYTERM_SELLIST 1526

/* FunctionNumber-Define of PaymentList ***************************************/

#define PAYMENTLIST_SELLIST 1551

/* FunctionNumber-Define of PrewholeCst ***************************************/

#define PREWHOLECST_ISPREWHOLECST 1600

/* FunctionNumber-Define of ShipAuxNo *****************************************/

#define SHIPAUXNO_DELETE 1455
#define SHIPAUXNO_INSERT 1454
#define SHIPAUXNO_SELLIST 1451
#define SHIPAUXNO_UPDATE 1453

/* FunctionNumber-Define of TourPflege ****************************************/

#define TOURPFLEGE_SELTOURENKUNDE 1272
#define TOURPFLEGE_UPDATE 1273

/* FunctionNumber-Define of delayedcst ****************************************/

#define DELAYEDCST_DELETE 1373
#define DELAYEDCST_DELETEALL 1378
#define DELAYEDCST_INSERT 1372
#define DELAYEDCST_INSERTALL 1376
#define DELAYEDCST_SELDAY 1384
#define DELAYEDCST_SELLIST 1370
#define DELAYEDCST_SELECTACTTOUREN 1385
#define DELAYEDCST_SELECTTOUREN 1379
#define DELAYEDCST_SETACTIV 1377
#define DELAYEDCST_UPDATE 1371

/* FunctionNumber-Define of delayeddeliverycstspecial *************************/

#define DELAYEDDELIVERYCSTSPECIAL_DELETE 1735
#define DELAYEDDELIVERYCSTSPECIAL_INSERT 1734
#define DELAYEDDELIVERYCSTSPECIAL_SEL 1732
#define DELAYEDDELIVERYCSTSPECIAL_SELUNI 1738
#define DELAYEDDELIVERYCSTSPECIAL_UPDATE 1733

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ChainCustomers ********************************/

#define SelList 1584

/* Old-FunctionNumber-Define of CheckCustomerExist ****************************/

#define SelExist 1457

/* Old-FunctionNumber-Define of CheckListe5 ***********************************/

#define IsListe5 1591

/* Old-FunctionNumber-Define of CstBranchInfo *********************************/

#define Delete 1667
#define Insert 1668
#define SelList 1664
#define SelListValid 1665
#define Update 1666

/* Old-FunctionNumber-Define of CstBulgaria ***********************************/

#define SelCst 1533

/* Old-FunctionNumber-Define of CstBuyingOptions ******************************/

#define SelBuyingOptions 1745

/* Old-FunctionNumber-Define of CstDiscAcc ************************************/

#define CheckExist 1522
#define SelListCst 1520
#define SelListGrp 1521

/* Old-FunctionNumber-Define of CstDiscAccAnz *********************************/

#define CheckMain 1509
#define CheckMember 1510
#define SelList 1511
#define SelMain 1512

/* Old-FunctionNumber-Define of CstDiscCont ***********************************/

#define SelList 1431

/* Old-FunctionNumber-Define of CstPayTerm ************************************/

#define SelList 1525

/* Old-FunctionNumber-Define of CstRebateType *********************************/

#define SelRebateType 1531

/* Old-FunctionNumber-Define of CustPharma ************************************/

#define SelList 1346

/* Old-FunctionNumber-Define of CustPhon **************************************/

#define Delete 1345
#define Insert 1344
#define SelList 1343
#define SelPhoneNo 1342

/* Old-FunctionNumber-Define of CustRout **************************************/

#define Delete 1337
#define Insert 1339
#define SelActRouting 1410
#define SelList 1335
#define Update 1336

/* Old-FunctionNumber-Define of CustomerDoubles *******************************/

#define SelDouble 1780

/* Old-FunctionNumber-Define of DistressRouting *******************************/

#define GetCount 1456
#define SelNot 1446
#define SelRouted 1447
#define Update 1448

/* Old-FunctionNumber-Define of EncloserTimes *********************************/

#define CopyEncloser 1569
#define Delete 1567
#define Insert 1566
#define SelList 1565
#define Update 1568

/* Old-FunctionNumber-Define of KNDTOURFENSTER ********************************/

#define SelPeriods 1722

/* Old-FunctionNumber-Define of KNDTOURWOCHE **********************************/

#define SelList 1406

/* Old-FunctionNumber-Define of KNDTOURWOCHE2 *********************************/

#define SelList 1407

/* Old-FunctionNumber-Define of KNDTOURWOCHE3 *********************************/

#define SelList 1408

/* Old-FunctionNumber-Define of KndFilInfo ************************************/

#define SelKnd 1387

/* Old-FunctionNumber-Define of KndFilInfo2 ***********************************/

#define SelInfo 1388

/* Old-FunctionNumber-Define of KreditLimit ***********************************/

#define SelLimit 1485
#define SelLimit1 1585
#define SelLimit2 1586
#define SelLimitMain 1587

/* Old-FunctionNumber-Define of KundeLizensen *********************************/

#define SelLicenses 1516

/* Old-FunctionNumber-Define of KundeVerbundFiliale ***************************/

#define Delete 1278
#define Insert 1277
#define Sel 1275
#define Update 1276

/* Old-FunctionNumber-Define of Liste5 ****************************************/

#define SelList 1590

/* Old-FunctionNumber-Define of MCustomerEmergencyServicePlan *****************/

#define Delete 1246
#define Insert 1245
#define SelList 1242
#define SelListHist 1243
#define SelUni 1256
#define Update 1244

/* Old-FunctionNumber-Define of MCustomerVacation *****************************/

#define Delete 1264
#define Insert 1263
#define SelList 1262
#define SelNextEffective 1267
#define SelUni 1266
#define Update 1265

/* Old-FunctionNumber-Define of PayTerm ***************************************/

#define SelList 1526

/* Old-FunctionNumber-Define of PaymentList ***********************************/

#define SelList 1551

/* Old-FunctionNumber-Define of PrewholeCst ***********************************/

#define IsPrewholeCst 1600

/* Old-FunctionNumber-Define of ShipAuxNo *************************************/

#define Delete 1455
#define Insert 1454
#define SelList 1451
#define Update 1453

/* Old-FunctionNumber-Define of TourPflege ************************************/

#define SelTourenKunde 1272
#define Update 1273

/* Old-FunctionNumber-Define of delayedcst ************************************/

#define Delete 1373
#define DeleteAll 1378
#define Insert 1372
#define InsertAll 1376
#define SelDay 1384
#define SelList 1370
#define SelectActTouren 1385
#define SelectTouren 1379
#define SetActiv 1377
#define Update 1371

/* Old-FunctionNumber-Define of delayeddeliverycstspecial *********************/

#define Delete 1735
#define Insert 1734
#define Sel 1732
#define SelUni 1738
#define Update 1733

#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS

#include<vector>
using namespace std;

/* ppunixc */
#include <sockclient.h>
#include <ppstring.h>
#include <ppgeneric.h>

/* must be implemented */
void FehlerBehandlung(int rc, const char * const error_msg);

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual {
public:
    virtual    ~ppDadeVirtual() {};
    virtual int SelList      (int FetchRel = 1, int pos = 0) = 0;
    virtual int SelListHist  (int FetchRel = 1, int pos = 0) = 0;
    virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
    virtual int Load         (int pos = 0                  ) = 0;
    virtual int Delete       (int pos = 0                  ) = 0;
    virtual int Save         (int pos = 0                  ) = 0;
};
#endif

class CCHAINCUSTOMERS : public ppDadeVirtual {
public:
    chaincustomersS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<chaincustomersS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< chaincustomersS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     chaincustomersS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< chaincustomersS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<chaincustomersS>::iterator
                 beginList() { return lst.begin(); }
    vector<chaincustomersS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStrasse(ppString & t) const { t = s.STRASSE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetMaincstno() const { return s.MAINCSTNO; }

    const chaincustomersS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_CHAINCUSTOMERS_NAMEAPO); }
    void         SetStrasse(const ppString & t) { ppGStrCopy(s.STRASSE, t.c_str(), L_CHAINCUSTOMERS_STRASSE); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_CHAINCUSTOMERS_ORT); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetMaincstno(long t) { s.MAINCSTNO = t; }

    void         SetStruct(const chaincustomersS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1584, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHAINCUSTOMERS() {
        ::buf_default((void *)&s, CHAINCUSTOMERS_BES, CHAINCUSTOMERS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHAINCUSTOMERS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHAINCUSTOMERS_BES, CHAINCUSTOMERS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CHAINCUSTOMERS_BES, (int)CHAINCUSTOMERS_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1584 ) return CursorServerCall(1584, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHAINCUSTOMERS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.STRASSE);
        ppGStripLast(d.ORT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHAINCUSTOMERS_BES, (int)CHAINCUSTOMERS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCHAINCUSTOMERS c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CHAINCUSTOMERS_BES, (int)CHAINCUSTOMERS_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCHECKCUSTOMEREXIST : public ppDadeVirtual {
public:
    checkcustomerexistS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkcustomerexistS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkcustomerexistS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkcustomerexistS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkcustomerexistS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkcustomerexistS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkcustomerexistS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }

    const checkcustomerexistS &
                 GetStruct() const { return s; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }

    void         SetStruct(const checkcustomerexistS & t) { s = t; }

    int          SelExist(int pos = 0) { int ret = UniqueServerCall(1457, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKCUSTOMEREXIST() {
        ::buf_default((void *)&s, CHECKCUSTOMEREXIST_BES, CHECKCUSTOMEREXIST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKCUSTOMEREXIST() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKCUSTOMEREXIST_BES, CHECKCUSTOMEREXIST_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1457 ) return UniqueServerCall(1457, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKCUSTOMEREXIST & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKCUSTOMEREXIST_BES, (int)CHECKCUSTOMEREXIST_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCHECKLISTE5 : public ppDadeVirtual {
public:
    checkliste5S s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkliste5S> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkliste5S >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkliste5S c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkliste5S >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkliste5S>::iterator
                 beginList() { return lst.begin(); }
    vector<checkliste5S>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }

    const checkliste5S &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }

    void         SetStruct(const checkliste5S & t) { s = t; }

    int          IsListe5(int pos = 0) { int ret = UniqueServerCall(1591, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKLISTE5() {
        ::buf_default((void *)&s, CHECKLISTE5_BES, CHECKLISTE5_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKLISTE5() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKLISTE5_BES, CHECKLISTE5_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1591 ) return UniqueServerCall(1591, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKLISTE5 & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKLISTE5_BES, (int)CHECKLISTE5_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCSTBRANCHINFO : public ppDadeVirtual {
public:
    cstbranchinfoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cstbranchinfoS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstbranchinfoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cstbranchinfoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstbranchinfoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cstbranchinfoS>::iterator
                 beginList() { return lst.begin(); }
    vector<cstbranchinfoS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetLfdnr() const { return s.LFDNR; }
    const char*  GetInfotext(ppString & t) const { t = s.INFOTEXT; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDateto() const { return s.DATETO; }
    long         GetTimeto() const { return s.TIMETO; }

    const cstbranchinfoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetLfdnr(long t) { s.LFDNR = t; }
    void         SetInfotext(const ppString & t) { ppGStrCopy(s.INFOTEXT, t.c_str(), L_CSTBRANCHINFO_INFOTEXT); }
    void         SetDateto(long t) { s.DATETO = t; }
    void         SetTimeto(long t) { s.TIMETO = t; }

    void         SetStruct(const cstbranchinfoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1667, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1668, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1664, FetchRel, pos); return ret; }
    int          SelListValid(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1665, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1666, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSTBRANCHINFO() {
        ::buf_default((void *)&s, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSTBRANCHINFO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSTBRANCHINFO_BES, CSTBRANCHINFO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTBRANCHINFO_BES, (int)CSTBRANCHINFO_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1667 ) return UniqueServerCall(1667, pos);
        if ( fkt_nr == 1668 ) return UniqueServerCall(1668, pos);
        if ( fkt_nr == 1664 ) return CursorServerCall(1664, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1665 ) return CursorServerCall(1665, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1666 ) return UniqueServerCall(1666, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CSTBRANCHINFO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.INFOTEXT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSTBRANCHINFO_BES, (int)CSTBRANCHINFO_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCSTBRANCHINFO c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTBRANCHINFO_BES, (int)CSTBRANCHINFO_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCSTBULGARIA : public ppDadeVirtual {
public:
    cstbulgariaS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cstbulgariaS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstbulgariaS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cstbulgariaS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstbulgariaS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cstbulgariaS>::iterator
                 beginList() { return lst.begin(); }
    vector<cstbulgariaS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    short        GetRebatemethfreesale() const { return s.REBATEMETHFREESALE; }
    short        GetRebatemethhealthf() const { return s.REBATEMETHHEALTHF; }
    long         GetMaincstno() const { return s.MAINCSTNO; }

    const cstbulgariaS &
                 GetStruct() const { return s; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetRebatemethfreesale(short t) { s.REBATEMETHFREESALE = t; }
    void         SetRebatemethhealthf(short t) { s.REBATEMETHHEALTHF = t; }
    void         SetMaincstno(long t) { s.MAINCSTNO = t; }

    void         SetStruct(const cstbulgariaS & t) { s = t; }

    int          SelCst(int pos = 0) { int ret = UniqueServerCall(1533, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSTBULGARIA() {
        ::buf_default((void *)&s, CSTBULGARIA_BES, CSTBULGARIA_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSTBULGARIA() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSTBULGARIA_BES, CSTBULGARIA_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1533 ) return UniqueServerCall(1533, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CSTBULGARIA & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSTBULGARIA_BES, (int)CSTBULGARIA_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCSTBUYINGOPTIONS : public ppDadeVirtual {
public:
    cstbuyingoptionsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cstbuyingoptionsS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstbuyingoptionsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cstbuyingoptionsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstbuyingoptionsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cstbuyingoptionsS>::iterator
                 beginList() { return lst.begin(); }
    vector<cstbuyingoptionsS>::iterator
                 endList  () { return lst.end  (); }

    long         GetEtartklasse1() const { return s.ETARTKLASSE1; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    char         GetKzpsychostoffe() const { return s.KZPSYCHOSTOFFE[0]; }

    const cstbuyingoptionsS &
                 GetStruct() const { return s; }
    void         SetEtartklasse1(long t) { s.ETARTKLASSE1 = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetKzpsychostoffe(char t) { s.KZPSYCHOSTOFFE[0] = t; s.KZPSYCHOSTOFFE[1] = '\0';}

    void         SetStruct(const cstbuyingoptionsS & t) { s = t; }

    int          SelBuyingOptions(int pos = 0) { int ret = UniqueServerCall(1745, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSTBUYINGOPTIONS() {
        ::buf_default((void *)&s, CSTBUYINGOPTIONS_BES, CSTBUYINGOPTIONS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSTBUYINGOPTIONS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSTBUYINGOPTIONS_BES, CSTBUYINGOPTIONS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1745 ) return UniqueServerCall(1745, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CSTBUYINGOPTIONS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSTBUYINGOPTIONS_BES, (int)CSTBUYINGOPTIONS_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCSTDISCACC : public ppDadeVirtual {
public:
    cstdiscaccS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cstdiscaccS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstdiscaccS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cstdiscaccS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstdiscaccS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cstdiscaccS>::iterator
                 beginList() { return lst.begin(); }
    vector<cstdiscaccS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetMaincstno() const { return s.MAINCSTNO; }
    long         GetDatum() const { return s.DATUM; }
    double       GetBalance() const { return s.BALANCE; }
    char         GetUpd_flag() const { return s.UPD_FLAG[0]; }
    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    long         GetDate() const { return s.DATE; }
    const char*  GetInvoicenumber(ppString & t) const { t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }
    double       GetInvoiceamount() const { return s.INVOICEAMOUNT; }
    const char*  GetVouchertyp(ppString & t) const { t = s.VOUCHERTYP; t.erasespace(ppString::END); return t.c_str(); }
    short        GetPreis_typ() const { return s.PREIS_TYP; }
    short        GetPriority() const { return s.PRIORITY; }
    long         GetKdauftragnrsplit() const { return s.KDAUFTRAGNRSPLIT; }
    double       GetInvoicepaid() const { return s.INVOICEPAID; }
    short        GetPaymentarget() const { return s.PAYMENTARGET; }
    long         GetLfdnr() const { return s.LFDNR; }

    const cstdiscaccS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetMaincstno(long t) { s.MAINCSTNO = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetBalance(double t) { s.BALANCE = t; }
    void         SetUpd_flag(char t) { s.UPD_FLAG[0] = t; s.UPD_FLAG[1] = '\0';}
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetDate(long t) { s.DATE = t; }
    void         SetInvoicenumber(const ppString & t) { ppGStrCopy(s.INVOICENUMBER, t.c_str(), L_CSTDISCACC_INVOICENUMBER); }
    void         SetInvoiceamount(double t) { s.INVOICEAMOUNT = t; }
    void         SetVouchertyp(const ppString & t) { ppGStrCopy(s.VOUCHERTYP, t.c_str(), L_CSTDISCACC_VOUCHERTYP); }
    void         SetPreis_typ(short t) { s.PREIS_TYP = t; }
    void         SetPriority(short t) { s.PRIORITY = t; }
    void         SetKdauftragnrsplit(long t) { s.KDAUFTRAGNRSPLIT = t; }
    void         SetInvoicepaid(double t) { s.INVOICEPAID = t; }
    void         SetPaymentarget(short t) { s.PAYMENTARGET = t; }
    void         SetLfdnr(long t) { s.LFDNR = t; }

    void         SetStruct(const cstdiscaccS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          CheckExist(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1522, FetchRel, pos); return ret; }
    int          SelListCst(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1520, FetchRel, pos); return ret; }
    int          SelListGrp(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1521, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSTDISCACC() {
        ::buf_default((void *)&s, CSTDISCACC_BES, CSTDISCACC_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSTDISCACC() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSTDISCACC_BES, CSTDISCACC_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTDISCACC_BES, (int)CSTDISCACC_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1522 ) return CursorServerCall(1522, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1520 ) return CursorServerCall(1520, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1521 ) return CursorServerCall(1521, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CSTDISCACC & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.INVOICENUMBER);
        ppGStripLast(d.VOUCHERTYP);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSTDISCACC_BES, (int)CSTDISCACC_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCSTDISCACC c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTDISCACC_BES, (int)CSTDISCACC_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCSTDISCACCANZ : public ppDadeVirtual {
public:
    cstdiscaccanzS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cstdiscaccanzS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstdiscaccanzS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cstdiscaccanzS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstdiscaccanzS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cstdiscaccanzS>::iterator
                 beginList() { return lst.begin(); }
    vector<cstdiscaccanzS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetMaincstno() const { return s.MAINCSTNO; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStrasse(ppString & t) const { t = s.STRASSE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }

    const cstdiscaccanzS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetMaincstno(long t) { s.MAINCSTNO = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_CSTDISCACCANZ_NAMEAPO); }
    void         SetStrasse(const ppString & t) { ppGStrCopy(s.STRASSE, t.c_str(), L_CSTDISCACCANZ_STRASSE); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_CSTDISCACCANZ_ORT); }

    void         SetStruct(const cstdiscaccanzS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          CheckMain(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1509, FetchRel, pos); return ret; }
    int          CheckMember(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1510, FetchRel, pos); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1511, FetchRel, pos); return ret; }
    int          SelMain(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1512, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSTDISCACCANZ() {
        ::buf_default((void *)&s, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSTDISCACCANZ() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSTDISCACCANZ_BES, CSTDISCACCANZ_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTDISCACCANZ_BES, (int)CSTDISCACCANZ_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1509 ) return CursorServerCall(1509, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1510 ) return CursorServerCall(1510, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1511 ) return CursorServerCall(1511, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1512 ) return CursorServerCall(1512, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CSTDISCACCANZ & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.STRASSE);
        ppGStripLast(d.ORT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSTDISCACCANZ_BES, (int)CSTDISCACCANZ_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCSTDISCACCANZ c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTDISCACCANZ_BES, (int)CSTDISCACCANZ_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCSTDISCCONT : public ppDadeVirtual {
public:
    cstdisccontS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cstdisccontS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstdisccontS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cstdisccontS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstdisccontS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cstdisccontS>::iterator
                 beginList() { return lst.begin(); }
    vector<cstdisccontS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    const char*  GetOrder_type(ppString & t) const { t = s.ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPharmacygroupid(ppString & t) const { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetSub_order_type(ppString & t) const { t = s.SUB_ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPayment_term(ppString & t) const { t = s.PAYMENT_TERM; t.erasespace(ppString::END); return t.c_str(); }
    short        GetValuta_days() const { return s.VALUTA_DAYS; }
    double       GetMin_order_value() const { return s.MIN_ORDER_VALUE; }
    short        GetMin_tubes() const { return s.MIN_TUBES; }
    double       GetLoss_in_discount() const { return s.LOSS_IN_DISCOUNT; }
    char         GetUpd_flag() const { return s.UPD_FLAG[0]; }

    const cstdisccontS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetOrder_type(const ppString & t) { ppGStrCopy(s.ORDER_TYPE, t.c_str(), L_CSTDISCCONT_ORDER_TYPE); }
    void         SetPharmacygroupid(const ppString & t) { ppGStrCopy(s.PHARMACYGROUPID, t.c_str(), L_CSTDISCCONT_PHARMACYGROUPID); }
    void         SetSub_order_type(const ppString & t) { ppGStrCopy(s.SUB_ORDER_TYPE, t.c_str(), L_CSTDISCCONT_SUB_ORDER_TYPE); }
    void         SetPayment_term(const ppString & t) { ppGStrCopy(s.PAYMENT_TERM, t.c_str(), L_CSTDISCCONT_PAYMENT_TERM); }
    void         SetValuta_days(short t) { s.VALUTA_DAYS = t; }
    void         SetMin_order_value(double t) { s.MIN_ORDER_VALUE = t; }
    void         SetMin_tubes(short t) { s.MIN_TUBES = t; }
    void         SetLoss_in_discount(double t) { s.LOSS_IN_DISCOUNT = t; }
    void         SetUpd_flag(char t) { s.UPD_FLAG[0] = t; s.UPD_FLAG[1] = '\0';}

    void         SetStruct(const cstdisccontS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1431, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSTDISCCONT() {
        ::buf_default((void *)&s, CSTDISCCONT_BES, CSTDISCCONT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSTDISCCONT() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSTDISCCONT_BES, CSTDISCCONT_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTDISCCONT_BES, (int)CSTDISCCONT_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1431 ) return CursorServerCall(1431, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CSTDISCCONT & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.ORDER_TYPE);
        ppGStripLast(d.PHARMACYGROUPID);
        ppGStripLast(d.SUB_ORDER_TYPE);
        ppGStripLast(d.PAYMENT_TERM);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSTDISCCONT_BES, (int)CSTDISCCONT_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCSTDISCCONT c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTDISCCONT_BES, (int)CSTDISCCONT_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCSTPAYTERM : public ppDadeVirtual {
public:
    cstpaytermS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cstpaytermS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstpaytermS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cstpaytermS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstpaytermS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cstpaytermS>::iterator
                 beginList() { return lst.begin(); }
    vector<cstpaytermS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetPreis_typ() const { return s.PREIS_TYP; }
    short        GetPaymentarget() const { return s.PAYMENTARGET; }

    const cstpaytermS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetPreis_typ(short t) { s.PREIS_TYP = t; }
    void         SetPaymentarget(short t) { s.PAYMENTARGET = t; }

    void         SetStruct(const cstpaytermS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1525, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSTPAYTERM() {
        ::buf_default((void *)&s, CSTPAYTERM_BES, CSTPAYTERM_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSTPAYTERM() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSTPAYTERM_BES, CSTPAYTERM_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTPAYTERM_BES, (int)CSTPAYTERM_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1525 ) return CursorServerCall(1525, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CSTPAYTERM & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSTPAYTERM_BES, (int)CSTPAYTERM_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCSTPAYTERM c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTPAYTERM_BES, (int)CSTPAYTERM_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCSTREBATETYPE : public ppDadeVirtual {
public:
    cstrebatetypeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cstrebatetypeS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstrebatetypeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cstrebatetypeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cstrebatetypeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cstrebatetypeS>::iterator
                 beginList() { return lst.begin(); }
    vector<cstrebatetypeS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    short        GetRebatemethfreesale() const { return s.REBATEMETHFREESALE; }
    short        GetRebatemethhealthf() const { return s.REBATEMETHHEALTHF; }

    const cstrebatetypeS &
                 GetStruct() const { return s; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetRebatemethfreesale(short t) { s.REBATEMETHFREESALE = t; }
    void         SetRebatemethhealthf(short t) { s.REBATEMETHHEALTHF = t; }

    void         SetStruct(const cstrebatetypeS & t) { s = t; }

    int          SelRebateType(int pos = 0) { int ret = UniqueServerCall(1531, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSTREBATETYPE() {
        ::buf_default((void *)&s, CSTREBATETYPE_BES, CSTREBATETYPE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSTREBATETYPE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSTREBATETYPE_BES, CSTREBATETYPE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1531 ) return UniqueServerCall(1531, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CSTREBATETYPE & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSTREBATETYPE_BES, (int)CSTREBATETYPE_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CCUSTPHARMA : public ppDadeVirtual {
public:
    custpharmaS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<custpharmaS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< custpharmaS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     custpharmaS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< custpharmaS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<custpharmaS>::iterator
                 beginList() { return lst.begin(); }
    vector<custpharmaS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetBranchno() const { return s.BRANCHNO; }
    const char*  GetPharmacygroupid(ppString & t) const { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetRanking() const { return s.RANKING; }

    const custpharmaS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetPharmacygroupid(const ppString & t) { ppGStrCopy(s.PHARMACYGROUPID, t.c_str(), L_CUSTPHARMA_PHARMACYGROUPID); }
    void         SetRanking(short t) { s.RANKING = t; }

    void         SetStruct(const custpharmaS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1346, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTPHARMA() {
        ::buf_default((void *)&s, CUSTPHARMA_BES, CUSTPHARMA_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTPHARMA() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTPHARMA_BES, CUSTPHARMA_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTPHARMA_BES, (int)CUSTPHARMA_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1346 ) return CursorServerCall(1346, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CUSTPHARMA & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PHARMACYGROUPID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTPHARMA_BES, (int)CUSTPHARMA_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCUSTPHARMA c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTPHARMA_BES, (int)CUSTPHARMA_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCUSTPHON : public ppDadeVirtual {
public:
    custphonS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<custphonS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< custphonS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     custphonS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< custphonS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<custphonS>::iterator
                 beginList() { return lst.begin(); }
    vector<custphonS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    const char*  GetTelnr(ppString & t) const { t = s.TELNR; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatum() const { return s.DATUM; }

    const custphonS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetTelnr(const ppString & t) { ppGStrCopy(s.TELNR, t.c_str(), L_CUSTPHON_TELNR); }
    void         SetDatum(long t) { s.DATUM = t; }

    void         SetStruct(const custphonS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1345, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1344, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1343, FetchRel, pos); return ret; }
    int          SelPhoneNo(int pos = 0) { int ret = UniqueServerCall(1342, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTPHON() {
        ::buf_default((void *)&s, CUSTPHON_BES, CUSTPHON_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTPHON() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTPHON_BES, CUSTPHON_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTPHON_BES, (int)CUSTPHON_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1345 ) return UniqueServerCall(1345, pos);
        if ( fkt_nr == 1344 ) return UniqueServerCall(1344, pos);
        if ( fkt_nr == 1343 ) return CursorServerCall(1343, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1342 ) return UniqueServerCall(1342, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CUSTPHON & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TELNR);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTPHON_BES, (int)CUSTPHON_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCUSTPHON c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTPHON_BES, (int)CUSTPHON_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCUSTROUT : public ppDadeVirtual {
public:
    custroutS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<custroutS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< custroutS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     custroutS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< custroutS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<custroutS>::iterator
                 beginList() { return lst.begin(); }
    vector<custroutS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetTimefrom() const { return s.TIMEFROM; }
    long         GetTimeto() const { return s.TIMETO; }
    short        GetDestbranchno() const { return s.DESTBRANCHNO; }
    const char*  GetDayofweek(ppString & t) const { t = s.DAYOFWEEK; t.erasespace(ppString::END); return t.c_str(); }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetZeit_von() const { return s.ZEIT_VON; }

    const custroutS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetTimefrom(long t) { s.TIMEFROM = t; }
    void         SetTimeto(long t) { s.TIMETO = t; }
    void         SetDestbranchno(short t) { s.DESTBRANCHNO = t; }
    void         SetDayofweek(const ppString & t) { ppGStrCopy(s.DAYOFWEEK, t.c_str(), L_CUSTROUT_DAYOFWEEK); }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetZeit_von(long t) { s.ZEIT_VON = t; }

    void         SetStruct(const custroutS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1337, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1339, pos); Strip(s); return ret; }
    int          SelActRouting(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1410, FetchRel, pos); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1335, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1336, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTROUT() {
        ::buf_default((void *)&s, CUSTROUT_BES, CUSTROUT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTROUT() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTROUT_BES, CUSTROUT_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTROUT_BES, (int)CUSTROUT_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1337 ) return UniqueServerCall(1337, pos);
        if ( fkt_nr == 1339 ) return UniqueServerCall(1339, pos);
        if ( fkt_nr == 1410 ) return CursorServerCall(1410, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1335 ) return CursorServerCall(1335, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1336 ) return UniqueServerCall(1336, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CUSTROUT & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DAYOFWEEK);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTROUT_BES, (int)CUSTROUT_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCUSTROUT c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTROUT_BES, (int)CUSTROUT_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CCUSTOMERDOUBLES : public ppDadeVirtual {
public:
    customerdoublesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<customerdoublesS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< customerdoublesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     customerdoublesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< customerdoublesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<customerdoublesS>::iterator
                 beginList() { return lst.begin(); }
    vector<customerdoublesS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }

    const customerdoublesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_CUSTOMERDOUBLES_NAME); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }

    void         SetStruct(const customerdoublesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelDouble(int pos = 0) { int ret = UniqueServerCall(1780, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTOMERDOUBLES() {
        ::buf_default((void *)&s, CUSTOMERDOUBLES_BES, CUSTOMERDOUBLES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTOMERDOUBLES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTOMERDOUBLES_BES, CUSTOMERDOUBLES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTOMERDOUBLES_BES, (int)CUSTOMERDOUBLES_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1780 ) return UniqueServerCall(1780, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CUSTOMERDOUBLES & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERDOUBLES_BES, (int)CUSTOMERDOUBLES_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CCUSTOMERDOUBLES c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CUSTOMERDOUBLES_BES, (int)CUSTOMERDOUBLES_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CDISTRESSROUTING : public ppDadeVirtual {
public:
    distressroutingS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<distressroutingS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< distressroutingS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     distressroutingS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< distressroutingS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<distressroutingS>::iterator
                 beginList() { return lst.begin(); }
    vector<distressroutingS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetDestbranchno() const { return s.DESTBRANCHNO; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPostleitzahl(ppString & t) const { t = s.POSTLEITZAHL; t.erasespace(ppString::END); return t.c_str(); }
    long         GetPersonalnrvertr() const { return s.PERSONALNRVERTR; }
    const char*  GetKzkdklasse(ppString & t) const { t = s.KZKDKLASSE; t.erasespace(ppString::END); return t.c_str(); }

    const distressroutingS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetDestbranchno(short t) { s.DESTBRANCHNO = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_DISTRESSROUTING_NAMEAPO); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_DISTRESSROUTING_ORT); }
    void         SetPostleitzahl(const ppString & t) { ppGStrCopy(s.POSTLEITZAHL, t.c_str(), L_DISTRESSROUTING_POSTLEITZAHL); }
    void         SetPersonalnrvertr(long t) { s.PERSONALNRVERTR = t; }
    void         SetKzkdklasse(const ppString & t) { ppGStrCopy(s.KZKDKLASSE, t.c_str(), L_DISTRESSROUTING_KZKDKLASSE); }

    void         SetStruct(const distressroutingS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          GetCount(int pos = 0) { int ret = UniqueServerCall(1456, pos); Strip(s); return ret; }
    int          SelNot(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1446, FetchRel, pos); return ret; }
    int          SelRouted(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1447, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1448, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDISTRESSROUTING() {
        ::buf_default((void *)&s, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDISTRESSROUTING() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DISTRESSROUTING_BES, DISTRESSROUTING_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, DISTRESSROUTING_BES, (int)DISTRESSROUTING_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1456 ) return UniqueServerCall(1456, pos);
        if ( fkt_nr == 1446 ) return CursorServerCall(1446, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1447 ) return CursorServerCall(1447, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1448 ) return UniqueServerCall(1448, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_DISTRESSROUTING & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.ORT);
        ppGStripLast(d.POSTLEITZAHL);
        ppGStripLast(d.KZKDKLASSE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DISTRESSROUTING_BES, (int)DISTRESSROUTING_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CDISTRESSROUTING c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, DISTRESSROUTING_BES, (int)DISTRESSROUTING_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CENCLOSERTIMES : public ppDadeVirtual {
public:
    enclosertimesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<enclosertimesS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< enclosertimesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     enclosertimesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< enclosertimesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<enclosertimesS>::iterator
                 beginList() { return lst.begin(); }
    vector<enclosertimesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetTimediff() const { return s.TIMEDIFF; }
    short        GetMaxpositions() const { return s.MAXPOSITIONS; }
    long         GetKundennr() const { return s.KUNDENNR; }

    const enclosertimesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetTimediff(short t) { s.TIMEDIFF = t; }
    void         SetMaxpositions(short t) { s.MAXPOSITIONS = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }

    void         SetStruct(const enclosertimesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          CopyEncloser(int pos = 0) { int ret = UniqueServerCall(1569, pos); Strip(s); return ret; }
    int          Delete(int pos = 0) { return UniqueServerCall(1567, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1566, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1565, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1568, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CENCLOSERTIMES() {
        ::buf_default((void *)&s, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CENCLOSERTIMES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, ENCLOSERTIMES_BES, ENCLOSERTIMES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ENCLOSERTIMES_BES, (int)ENCLOSERTIMES_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1569 ) return UniqueServerCall(1569, pos);
        if ( fkt_nr == 1567 ) return UniqueServerCall(1567, pos);
        if ( fkt_nr == 1566 ) return UniqueServerCall(1566, pos);
        if ( fkt_nr == 1565 ) return CursorServerCall(1565, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1568 ) return UniqueServerCall(1568, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_ENCLOSERTIMES & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, ENCLOSERTIMES_BES, (int)ENCLOSERTIMES_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CENCLOSERTIMES c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, ENCLOSERTIMES_BES, (int)ENCLOSERTIMES_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CKNDTOURFENSTER : public ppDadeVirtual {
public:
    kndtourfensterS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kndtourfensterS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndtourfensterS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kndtourfensterS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndtourfensterS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kndtourfensterS>::iterator
                 beginList() { return lst.begin(); }
    vector<kndtourfensterS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCustomerno() const { return s.CUSTOMERNO; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetFromtime() const { return s.FROMTIME; }
    long         GetTotime() const { return s.TOTIME; }
    long         GetMaintime() const { return s.MAINTIME; }

    const kndtourfensterS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_KNDTOURFENSTER_TOURID); }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetFromtime(long t) { s.FROMTIME = t; }
    void         SetTotime(long t) { s.TOTIME = t; }
    void         SetMaintime(long t) { s.MAINTIME = t; }

    void         SetStruct(const kndtourfensterS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelPeriods(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1722, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKNDTOURFENSTER() {
        ::buf_default((void *)&s, KNDTOURFENSTER_BES, KNDTOURFENSTER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKNDTOURFENSTER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KNDTOURFENSTER_BES, KNDTOURFENSTER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KNDTOURFENSTER_BES, (int)KNDTOURFENSTER_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1722 ) return CursorServerCall(1722, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_KNDTOURFENSTER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KNDTOURFENSTER_BES, (int)KNDTOURFENSTER_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CKNDTOURFENSTER c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KNDTOURFENSTER_BES, (int)KNDTOURFENSTER_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CKNDTOURWOCHE : public ppDadeVirtual {
public:
    kndtourwocheS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kndtourwocheS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndtourwocheS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kndtourwocheS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndtourwocheS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kndtourwocheS>::iterator
                 beginList() { return lst.begin(); }
    vector<kndtourwocheS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    short        GetWeekday() const { return s.WEEKDAY; }
    char         GetIstverbundtour() const { return s.ISTVERBUNDTOUR[0]; }
    const char*  GetKdauftragart(ppString & t) const { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
    short        GetIsbtm() const { return s.ISBTM; }
    short        GetIskk() const { return s.ISKK; }
    short        GetIsk08() const { return s.ISK08; }
    short        GetIsk20() const { return s.ISK20; }
    short        GetPharmacylockaccess() const { return s.PHARMACYLOCKACCESS; }
    const char*  GetRemarklackitemprocessing(ppString & t) const { t = s.REMARKLACKITEMPROCESSING; t.erasespace(ppString::END); return t.c_str(); }
    short        GetReturnstour() const { return s.RETURNSTOUR; }
    const char*  GetRemarklackcallback(ppString & t) const { t = s.REMARKLACKCALLBACK; t.erasespace(ppString::END); return t.c_str(); }
    short        GetTranspexclpsycho() const { return s.TRANSPEXCLPSYCHO; }
    short        GetTranspexclcooled() const { return s.TRANSPEXCLCOOLED; }
    short        GetTranspexclexpensive() const { return s.TRANSPEXCLEXPENSIVE; }
    short        GetCheckpositions() const { return s.CHECKPOSITIONS; }
    const char*  GetCheckremark(ppString & t) const { t = s.CHECKREMARK; t.erasespace(ppString::END); return t.c_str(); }
    long         GetPlannedcall() const { return s.PLANNEDCALL; }
    char         GetKzautozuord() const { return s.KZAUTOZUORD[0]; }
    short        GetScheckorder() const { return s.SCHECKORDER; }
    short        GetChecktimetotour() const { return s.CHECKTIMETOTOUR; }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTagestyp(ppString & t) const { t = s.TAGESTYP; t.erasespace(ppString::END); return t.c_str(); }

    const kndtourwocheS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetIstverbundtour(char t) { s.ISTVERBUNDTOUR[0] = t; s.ISTVERBUNDTOUR[1] = '\0';}
    void         SetKdauftragart(const ppString & t) { ppGStrCopy(s.KDAUFTRAGART, t.c_str(), L_KNDTOURWOCHE_KDAUFTRAGART); }
    void         SetIsbtm(short t) { s.ISBTM = t; }
    void         SetIskk(short t) { s.ISKK = t; }
    void         SetIsk08(short t) { s.ISK08 = t; }
    void         SetIsk20(short t) { s.ISK20 = t; }
    void         SetPharmacylockaccess(short t) { s.PHARMACYLOCKACCESS = t; }
    void         SetRemarklackitemprocessing(const ppString & t) { ppGStrCopy(s.REMARKLACKITEMPROCESSING, t.c_str(), L_KNDTOURWOCHE_REMARKLACKITEMPROCESSING); }
    void         SetReturnstour(short t) { s.RETURNSTOUR = t; }
    void         SetRemarklackcallback(const ppString & t) { ppGStrCopy(s.REMARKLACKCALLBACK, t.c_str(), L_KNDTOURWOCHE_REMARKLACKCALLBACK); }
    void         SetTranspexclpsycho(short t) { s.TRANSPEXCLPSYCHO = t; }
    void         SetTranspexclcooled(short t) { s.TRANSPEXCLCOOLED = t; }
    void         SetTranspexclexpensive(short t) { s.TRANSPEXCLEXPENSIVE = t; }
    void         SetCheckpositions(short t) { s.CHECKPOSITIONS = t; }
    void         SetCheckremark(const ppString & t) { ppGStrCopy(s.CHECKREMARK, t.c_str(), L_KNDTOURWOCHE_CHECKREMARK); }
    void         SetPlannedcall(long t) { s.PLANNEDCALL = t; }
    void         SetKzautozuord(char t) { s.KZAUTOZUORD[0] = t; s.KZAUTOZUORD[1] = '\0';}
    void         SetScheckorder(short t) { s.SCHECKORDER = t; }
    void         SetChecktimetotour(short t) { s.CHECKTIMETOTOUR = t; }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_KNDTOURWOCHE_BEMERKUNGEN); }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_KNDTOURWOCHE_TOURID); }
    void         SetTagestyp(const ppString & t) { ppGStrCopy(s.TAGESTYP, t.c_str(), L_KNDTOURWOCHE_TAGESTYP); }

    void         SetStruct(const kndtourwocheS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1406, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKNDTOURWOCHE() {
        ::buf_default((void *)&s, KNDTOURWOCHE_BES, KNDTOURWOCHE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKNDTOURWOCHE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KNDTOURWOCHE_BES, KNDTOURWOCHE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KNDTOURWOCHE_BES, (int)KNDTOURWOCHE_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1406 ) return CursorServerCall(1406, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_KNDTOURWOCHE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGART);
        ppGStripLast(d.REMARKLACKITEMPROCESSING);
        ppGStripLast(d.REMARKLACKCALLBACK);
        ppGStripLast(d.CHECKREMARK);
        ppGStripLast(d.BEMERKUNGEN);
        ppGStripLast(d.TOURID);
        ppGStripLast(d.TAGESTYP);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KNDTOURWOCHE_BES, (int)KNDTOURWOCHE_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CKNDTOURWOCHE c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KNDTOURWOCHE_BES, (int)KNDTOURWOCHE_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CKNDTOURWOCHE2 : public ppDadeVirtual {
public:
    kndtourwoche2S s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kndtourwoche2S> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndtourwoche2S >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kndtourwoche2S c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndtourwoche2S >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kndtourwoche2S>::iterator
                 beginList() { return lst.begin(); }
    vector<kndtourwoche2S>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatumkommi() const { return s.DATUMKOMMI; }
    long         GetConstime() const { return s.CONSTIME; }

    const kndtourwoche2S &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_KNDTOURWOCHE2_TOURID); }
    void         SetDatumkommi(long t) { s.DATUMKOMMI = t; }
    void         SetConstime(long t) { s.CONSTIME = t; }

    void         SetStruct(const kndtourwoche2S & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1407, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKNDTOURWOCHE2() {
        ::buf_default((void *)&s, KNDTOURWOCHE2_BES, KNDTOURWOCHE2_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKNDTOURWOCHE2() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KNDTOURWOCHE2_BES, KNDTOURWOCHE2_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KNDTOURWOCHE2_BES, (int)KNDTOURWOCHE2_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1407 ) return CursorServerCall(1407, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_KNDTOURWOCHE2 & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KNDTOURWOCHE2_BES, (int)KNDTOURWOCHE2_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CKNDTOURWOCHE2 c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KNDTOURWOCHE2_BES, (int)KNDTOURWOCHE2_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CKNDTOURWOCHE3 : public ppDadeVirtual {
public:
    kndtourwoche3S s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kndtourwoche3S> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndtourwoche3S >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kndtourwoche3S c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndtourwoche3S >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kndtourwoche3S>::iterator
                 beginList() { return lst.begin(); }
    vector<kndtourwoche3S>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatumkommi() const { return s.DATUMKOMMI; }
    long         GetConstime() const { return s.CONSTIME; }

    const kndtourwoche3S &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_KNDTOURWOCHE3_TOURID); }
    void         SetDatumkommi(long t) { s.DATUMKOMMI = t; }
    void         SetConstime(long t) { s.CONSTIME = t; }

    void         SetStruct(const kndtourwoche3S & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1408, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKNDTOURWOCHE3() {
        ::buf_default((void *)&s, KNDTOURWOCHE3_BES, KNDTOURWOCHE3_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKNDTOURWOCHE3() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KNDTOURWOCHE3_BES, KNDTOURWOCHE3_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KNDTOURWOCHE3_BES, (int)KNDTOURWOCHE3_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1408 ) return CursorServerCall(1408, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_KNDTOURWOCHE3 & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KNDTOURWOCHE3_BES, (int)KNDTOURWOCHE3_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CKNDTOURWOCHE3 c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KNDTOURWOCHE3_BES, (int)KNDTOURWOCHE3_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CKNDFILINFO : public ppDadeVirtual {
public:
    kndfilinfoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kndfilinfoS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndfilinfoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kndfilinfoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndfilinfoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kndfilinfoS>::iterator
                 beginList() { return lst.begin(); }
    vector<kndfilinfoS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKundennr() const { return s.KUNDENNR; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    double       GetDispogebuehr() const { return s.DISPOGEBUEHR; }
    double       GetBtmgebuehr() const { return s.BTMGEBUEHR; }
    double       GetDokugebuehr() const { return s.DOKUGEBUEHR; }
    long         GetTourenkippzeit() const { return s.TOURENKIPPZEIT; }

    const kndfilinfoS &
                 GetStruct() const { return s; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetDispogebuehr(double t) { s.DISPOGEBUEHR = t; }
    void         SetBtmgebuehr(double t) { s.BTMGEBUEHR = t; }
    void         SetDokugebuehr(double t) { s.DOKUGEBUEHR = t; }
    void         SetTourenkippzeit(long t) { s.TOURENKIPPZEIT = t; }

    void         SetStruct(const kndfilinfoS & t) { s = t; }

    int          SelKnd(int pos = 0) { int ret = UniqueServerCall(1387, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKNDFILINFO() {
        ::buf_default((void *)&s, KNDFILINFO_BES, KNDFILINFO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKNDFILINFO() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KNDFILINFO_BES, KNDFILINFO_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1387 ) return UniqueServerCall(1387, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_KNDFILINFO & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KNDFILINFO_BES, (int)KNDFILINFO_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CKNDFILINFO2 : public ppDadeVirtual {
public:
    kndfilinfo2S s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kndfilinfo2S> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndfilinfo2S >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kndfilinfo2S c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kndfilinfo2S >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kndfilinfo2S>::iterator
                 beginList() { return lst.begin(); }
    vector<kndfilinfo2S>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetDurchlaufnormal() const { return s.DURCHLAUFNORMAL; }
    long         GetDurchlaufeilbote() const { return s.DURCHLAUFEILBOTE; }
    long         GetTourverspaetung() const { return s.TOURVERSPAETUNG; }
    long         GetTourenkippzeit() const { return s.TOURENKIPPZEIT; }

    const kndfilinfo2S &
                 GetStruct() const { return s; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetDurchlaufnormal(long t) { s.DURCHLAUFNORMAL = t; }
    void         SetDurchlaufeilbote(long t) { s.DURCHLAUFEILBOTE = t; }
    void         SetTourverspaetung(long t) { s.TOURVERSPAETUNG = t; }
    void         SetTourenkippzeit(long t) { s.TOURENKIPPZEIT = t; }

    void         SetStruct(const kndfilinfo2S & t) { s = t; }

    int          SelInfo(int pos = 0) { int ret = UniqueServerCall(1388, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKNDFILINFO2() {
        ::buf_default((void *)&s, KNDFILINFO2_BES, KNDFILINFO2_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKNDFILINFO2() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KNDFILINFO2_BES, KNDFILINFO2_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1388 ) return UniqueServerCall(1388, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_KNDFILINFO2 & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KNDFILINFO2_BES, (int)KNDFILINFO2_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CKREDITLIMIT : public ppDadeVirtual {
public:
    kreditlimitS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kreditlimitS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kreditlimitS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kreditlimitS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kreditlimitS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kreditlimitS>::iterator
                 beginList() { return lst.begin(); }
    vector<kreditlimitS>::iterator
                 endList  () { return lst.end  (); }

    long         GetPartnerno() const { return s.PARTNERNO; }
    const char*  GetPartnername(ppString & t) const { t = s.PARTNERNAME; t.erasespace(ppString::END); return t.c_str(); }
    double       GetLimit() const { return s.LIMIT; }
    double       GetSum_debitside() const { return s.SUM_DEBITSIDE; }
    double       GetSum_creditside() const { return s.SUM_CREDITSIDE; }
    double       GetSum_monturnover() const { return s.SUM_MONTURNOVER; }
    double       GetSum_dayturnover() const { return s.SUM_DAYTURNOVER; }
    double       GetSum_returns() const { return s.SUM_RETURNS; }
    double       GetSum_goodsreceipt() const { return s.SUM_GOODSRECEIPT; }
    short        GetLimittype() const { return s.LIMITTYPE; }
    char         GetListe5() const { return s.LISTE5[0]; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }

    const kreditlimitS &
                 GetStruct() const { return s; }
    void         SetPartnerno(long t) { s.PARTNERNO = t; }
    void         SetPartnername(const ppString & t) { ppGStrCopy(s.PARTNERNAME, t.c_str(), L_KREDITLIMIT_PARTNERNAME); }
    void         SetLimit(double t) { s.LIMIT = t; }
    void         SetSum_debitside(double t) { s.SUM_DEBITSIDE = t; }
    void         SetSum_creditside(double t) { s.SUM_CREDITSIDE = t; }
    void         SetSum_monturnover(double t) { s.SUM_MONTURNOVER = t; }
    void         SetSum_dayturnover(double t) { s.SUM_DAYTURNOVER = t; }
    void         SetSum_returns(double t) { s.SUM_RETURNS = t; }
    void         SetSum_goodsreceipt(double t) { s.SUM_GOODSRECEIPT = t; }
    void         SetLimittype(short t) { s.LIMITTYPE = t; }
    void         SetListe5(char t) { s.LISTE5[0] = t; s.LISTE5[1] = '\0';}
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }

    void         SetStruct(const kreditlimitS & t) { s = t; }

    int          SelLimit(int pos = 0) { int ret = UniqueServerCall(1485, pos); Strip(s); return ret; }
    int          SelLimit1(int pos = 0) { int ret = UniqueServerCall(1585, pos); Strip(s); return ret; }
    int          SelLimit2(int pos = 0) { int ret = UniqueServerCall(1586, pos); Strip(s); return ret; }
    int          SelLimitMain(int pos = 0) { int ret = UniqueServerCall(1587, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKREDITLIMIT() {
        ::buf_default((void *)&s, KREDITLIMIT_BES, KREDITLIMIT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKREDITLIMIT() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KREDITLIMIT_BES, KREDITLIMIT_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1485 ) return UniqueServerCall(1485, pos);
        if ( fkt_nr == 1585 ) return UniqueServerCall(1585, pos);
        if ( fkt_nr == 1586 ) return UniqueServerCall(1586, pos);
        if ( fkt_nr == 1587 ) return UniqueServerCall(1587, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_KREDITLIMIT & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PARTNERNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KREDITLIMIT_BES, (int)KREDITLIMIT_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CKUNDELIZENSEN : public ppDadeVirtual {
public:
    kundelizensenS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kundelizensenS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kundelizensenS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kundelizensenS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kundelizensenS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kundelizensenS>::iterator
                 beginList() { return lst.begin(); }
    vector<kundelizensenS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    const char*  GetApolizens(ppString & t) const { t = s.APOLIZENS; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetBtmlizens(ppString & t) const { t = s.BTMLIZENS; t.erasespace(ppString::END); return t.c_str(); }

    const kundelizensenS &
                 GetStruct() const { return s; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetApolizens(const ppString & t) { ppGStrCopy(s.APOLIZENS, t.c_str(), L_KUNDELIZENSEN_APOLIZENS); }
    void         SetBtmlizens(const ppString & t) { ppGStrCopy(s.BTMLIZENS, t.c_str(), L_KUNDELIZENSEN_BTMLIZENS); }

    void         SetStruct(const kundelizensenS & t) { s = t; }

    int          SelLicenses(int pos = 0) { int ret = UniqueServerCall(1516, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKUNDELIZENSEN() {
        ::buf_default((void *)&s, KUNDELIZENSEN_BES, KUNDELIZENSEN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKUNDELIZENSEN() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KUNDELIZENSEN_BES, KUNDELIZENSEN_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1516 ) return UniqueServerCall(1516, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_KUNDELIZENSEN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.APOLIZENS);
        ppGStripLast(d.BTMLIZENS);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KUNDELIZENSEN_BES, (int)KUNDELIZENSEN_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CKUNDEVERBUNDFILIALE : public ppDadeVirtual {
public:
    kundeverbundfilialeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<kundeverbundfilialeS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kundeverbundfilialeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     kundeverbundfilialeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< kundeverbundfilialeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<kundeverbundfilialeS>::iterator
                 beginList() { return lst.begin(); }
    vector<kundeverbundfilialeS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetReihenfolgenr() const { return s.REIHENFOLGENR; }
    short        GetVerbundfilialnr() const { return s.VERBUNDFILIALNR; }

    const kundeverbundfilialeS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetReihenfolgenr(long t) { s.REIHENFOLGENR = t; }
    void         SetVerbundfilialnr(short t) { s.VERBUNDFILIALNR = t; }

    void         SetStruct(const kundeverbundfilialeS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1278, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1277, pos); Strip(s); return ret; }
    int          Sel(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1275, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1276, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CKUNDEVERBUNDFILIALE() {
        ::buf_default((void *)&s, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CKUNDEVERBUNDFILIALE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, KUNDEVERBUNDFILIALE_BES, KUNDEVERBUNDFILIALE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KUNDEVERBUNDFILIALE_BES, (int)KUNDEVERBUNDFILIALE_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1278 ) return UniqueServerCall(1278, pos);
        if ( fkt_nr == 1277 ) return UniqueServerCall(1277, pos);
        if ( fkt_nr == 1275 ) return CursorServerCall(1275, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1276 ) return UniqueServerCall(1276, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_KUNDEVERBUNDFILIALE & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, KUNDEVERBUNDFILIALE_BES, (int)KUNDEVERBUNDFILIALE_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CKUNDEVERBUNDFILIALE c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, KUNDEVERBUNDFILIALE_BES, (int)KUNDEVERBUNDFILIALE_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CLISTE5 : public ppDadeVirtual {
public:
    liste5S s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<liste5S> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< liste5S >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     liste5S c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< liste5S >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<liste5S>::iterator
                 beginList() { return lst.begin(); }
    vector<liste5S>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetArticleno() const { return s.ARTICLENO; }
    double       GetPreisekapo() const { return s.PREISEKAPO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetPreis_typ() const { return s.PREIS_TYP; }
    short        GetTaxlevel() const { return s.TAXLEVEL; }
    const char*  GetArtikel_langname(ppString & t) const { t = s.ARTIKEL_LANGNAME; t.erasespace(ppString::END); return t.c_str(); }

    const liste5S &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetArticleno(long t) { s.ARTICLENO = t; }
    void         SetPreisekapo(double t) { s.PREISEKAPO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetPreis_typ(short t) { s.PREIS_TYP = t; }
    void         SetTaxlevel(short t) { s.TAXLEVEL = t; }
    void         SetArtikel_langname(const ppString & t) { ppGStrCopy(s.ARTIKEL_LANGNAME, t.c_str(), L_LISTE5_ARTIKEL_LANGNAME); }

    void         SetStruct(const liste5S & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1590, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CLISTE5() {
        ::buf_default((void *)&s, LISTE5_BES, LISTE5_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CLISTE5() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, LISTE5_BES, LISTE5_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, LISTE5_BES, (int)LISTE5_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1590 ) return CursorServerCall(1590, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_LISTE5 & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.ARTIKEL_LANGNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, LISTE5_BES, (int)LISTE5_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CLISTE5 c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, LISTE5_BES, (int)LISTE5_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CMCUSTOMEREMERGENCYSERVICEPLAN : public ppDadeVirtual {
public:
    mcustomeremergencyserviceplanS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomeremergencyserviceplanS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomeremergencyserviceplanS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomeremergencyserviceplanS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomeremergencyserviceplanS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomeremergencyserviceplanS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomeremergencyserviceplanS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetUhrzeitvon() const { return s.UHRZEITVON; }
    long         GetUhrzeitbis() const { return s.UHRZEITBIS; }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    short        GetIsbtm() const { return s.ISBTM; }
    short        GetIskk() const { return s.ISKK; }
    short        GetIsk08() const { return s.ISK08; }
    short        GetIsk20() const { return s.ISK20; }

    const mcustomeremergencyserviceplanS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetUhrzeitvon(long t) { s.UHRZEITVON = t; }
    void         SetUhrzeitbis(long t) { s.UHRZEITBIS = t; }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_MCUSTOMEREMERGENCYSERVICEPLAN_BEMERKUNGEN); }
    void         SetIsbtm(short t) { s.ISBTM = t; }
    void         SetIskk(short t) { s.ISKK = t; }
    void         SetIsk08(short t) { s.ISK08 = t; }
    void         SetIsk20(short t) { s.ISK20 = t; }

    void         SetStruct(const mcustomeremergencyserviceplanS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1246, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1245, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1242, FetchRel, pos); return ret; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1243, FetchRel, pos); return ret; }
    int          SelUni(int pos = 0) { int ret = UniqueServerCall(1256, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1244, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMEREMERGENCYSERVICEPLAN() {
        ::buf_default((void *)&s, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMEREMERGENCYSERVICEPLAN() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMEREMERGENCYSERVICEPLAN_BES, MCUSTOMEREMERGENCYSERVICEPLAN_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMEREMERGENCYSERVICEPLAN_BES, (int)MCUSTOMEREMERGENCYSERVICEPLAN_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1246 ) return UniqueServerCall(1246, pos);
        if ( fkt_nr == 1245 ) return UniqueServerCall(1245, pos);
        if ( fkt_nr == 1242 ) return CursorServerCall(1242, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1243 ) return CursorServerCall(1243, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1256 ) return UniqueServerCall(1256, pos);
        if ( fkt_nr == 1244 ) return UniqueServerCall(1244, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMEREMERGENCYSERVICEPLAN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.BEMERKUNGEN);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMEREMERGENCYSERVICEPLAN_BES, (int)MCUSTOMEREMERGENCYSERVICEPLAN_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CMCUSTOMEREMERGENCYSERVICEPLAN c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMEREMERGENCYSERVICEPLAN_BES, (int)MCUSTOMEREMERGENCYSERVICEPLAN_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CMCUSTOMERVACATION : public ppDadeVirtual {
public:
    mcustomervacationS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomervacationS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomervacationS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomervacationS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomervacationS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomervacationS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomervacationS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetDatumgueltigab() const { return s.DATUMGUELTIGAB; }
    long         GetDatumgueltigbis() const { return s.DATUMGUELTIGBIS; }

    const mcustomervacationS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetDatumgueltigab(long t) { s.DATUMGUELTIGAB = t; }
    void         SetDatumgueltigbis(long t) { s.DATUMGUELTIGBIS = t; }

    void         SetStruct(const mcustomervacationS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1264, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1263, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1262, FetchRel, pos); return ret; }
    int          SelNextEffective(int pos = 0) { int ret = UniqueServerCall(1267, pos); Strip(s); return ret; }
    int          SelUni(int pos = 0) { int ret = UniqueServerCall(1266, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1265, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERVACATION() {
        ::buf_default((void *)&s, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERVACATION() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERVACATION_BES, MCUSTOMERVACATION_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERVACATION_BES, (int)MCUSTOMERVACATION_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1264 ) return UniqueServerCall(1264, pos);
        if ( fkt_nr == 1263 ) return UniqueServerCall(1263, pos);
        if ( fkt_nr == 1262 ) return CursorServerCall(1262, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1267 ) return UniqueServerCall(1267, pos);
        if ( fkt_nr == 1266 ) return UniqueServerCall(1266, pos);
        if ( fkt_nr == 1265 ) return UniqueServerCall(1265, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERVACATION & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERVACATION_BES, (int)MCUSTOMERVACATION_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CMCUSTOMERVACATION c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERVACATION_BES, (int)MCUSTOMERVACATION_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CPAYTERM : public ppDadeVirtual {
public:
    paytermS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<paytermS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< paytermS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     paytermS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< paytermS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<paytermS>::iterator
                 beginList() { return lst.begin(); }
    vector<paytermS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetPayment_term(ppString & t) const { t = s.PAYMENT_TERM; t.erasespace(ppString::END); return t.c_str(); }
    short        GetPaymentarget() const { return s.PAYMENTARGET; }
    double       GetCashdisount() const { return s.CASHDISOUNT; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }

    const paytermS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetPayment_term(const ppString & t) { ppGStrCopy(s.PAYMENT_TERM, t.c_str(), L_PAYTERM_PAYMENT_TERM); }
    void         SetPaymentarget(short t) { s.PAYMENTARGET = t; }
    void         SetCashdisount(double t) { s.CASHDISOUNT = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }

    void         SetStruct(const paytermS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1526, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPAYTERM() {
        ::buf_default((void *)&s, PAYTERM_BES, PAYTERM_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPAYTERM() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PAYTERM_BES, PAYTERM_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PAYTERM_BES, (int)PAYTERM_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1526 ) return CursorServerCall(1526, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PAYTERM & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.PAYMENT_TERM);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PAYTERM_BES, (int)PAYTERM_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPAYTERM c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PAYTERM_BES, (int)PAYTERM_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CPAYMENTLIST : public ppDadeVirtual {
public:
    paymentlistS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<paymentlistS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< paymentlistS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     paymentlistS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< paymentlistS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<paymentlistS>::iterator
                 beginList() { return lst.begin(); }
    vector<paymentlistS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    const char*  GetInvoicenumber(ppString & t) const { t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }
    double       GetTotalinvoiceamount() const { return s.TOTALINVOICEAMOUNT; }
    double       GetOpeninvoiceamount() const { return s.OPENINVOICEAMOUNT; }
    double       GetPaidinvoiceamount() const { return s.PAIDINVOICEAMOUNT; }
    long         GetDriverid() const { return s.DRIVERID; }
    long         GetPaymentdate() const { return s.PAYMENTDATE; }
    long         GetInvoicedate() const { return s.INVOICEDATE; }
    char         GetPaymentspec() const { return s.PAYMENTSPEC[0]; }

    const paymentlistS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetInvoicenumber(const ppString & t) { ppGStrCopy(s.INVOICENUMBER, t.c_str(), L_PAYMENTLIST_INVOICENUMBER); }
    void         SetTotalinvoiceamount(double t) { s.TOTALINVOICEAMOUNT = t; }
    void         SetOpeninvoiceamount(double t) { s.OPENINVOICEAMOUNT = t; }
    void         SetPaidinvoiceamount(double t) { s.PAIDINVOICEAMOUNT = t; }
    void         SetDriverid(long t) { s.DRIVERID = t; }
    void         SetPaymentdate(long t) { s.PAYMENTDATE = t; }
    void         SetInvoicedate(long t) { s.INVOICEDATE = t; }
    void         SetPaymentspec(char t) { s.PAYMENTSPEC[0] = t; s.PAYMENTSPEC[1] = '\0';}

    void         SetStruct(const paymentlistS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1551, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPAYMENTLIST() {
        ::buf_default((void *)&s, PAYMENTLIST_BES, PAYMENTLIST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPAYMENTLIST() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PAYMENTLIST_BES, PAYMENTLIST_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PAYMENTLIST_BES, (int)PAYMENTLIST_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1551 ) return CursorServerCall(1551, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PAYMENTLIST & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.INVOICENUMBER);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PAYMENTLIST_BES, (int)PAYMENTLIST_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CPAYMENTLIST c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, PAYMENTLIST_BES, (int)PAYMENTLIST_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CPREWHOLECST : public ppDadeVirtual {
public:
    prewholecstS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<prewholecstS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< prewholecstS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     prewholecstS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< prewholecstS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<prewholecstS>::iterator
                 beginList() { return lst.begin(); }
    vector<prewholecstS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetMaincstno() const { return s.MAINCSTNO; }

    const prewholecstS &
                 GetStruct() const { return s; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetMaincstno(long t) { s.MAINCSTNO = t; }

    void         SetStruct(const prewholecstS & t) { s = t; }

    int          IsPrewholeCst(int pos = 0) { int ret = UniqueServerCall(1600, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CPREWHOLECST() {
        ::buf_default((void *)&s, PREWHOLECST_BES, PREWHOLECST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CPREWHOLECST() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, PREWHOLECST_BES, PREWHOLECST_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1600 ) return UniqueServerCall(1600, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_PREWHOLECST & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, PREWHOLECST_BES, (int)PREWHOLECST_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CSHIPAUXNO : public ppDadeVirtual {
public:
    shipauxnoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<shipauxnoS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< shipauxnoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     shipauxnoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< shipauxnoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<shipauxnoS>::iterator
                 beginList() { return lst.begin(); }
    vector<shipauxnoS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetAuxbranchno() const { return s.AUXBRANCHNO; }
    long         GetAuxbgano() const { return s.AUXBGANO; }

    const shipauxnoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetAuxbranchno(short t) { s.AUXBRANCHNO = t; }
    void         SetAuxbgano(long t) { s.AUXBGANO = t; }

    void         SetStruct(const shipauxnoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1455, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1454, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1451, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1453, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSHIPAUXNO() {
        ::buf_default((void *)&s, SHIPAUXNO_BES, SHIPAUXNO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSHIPAUXNO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SHIPAUXNO_BES, SHIPAUXNO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SHIPAUXNO_BES, (int)SHIPAUXNO_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1455 ) return UniqueServerCall(1455, pos);
        if ( fkt_nr == 1454 ) return UniqueServerCall(1454, pos);
        if ( fkt_nr == 1451 ) return CursorServerCall(1451, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1453 ) return UniqueServerCall(1453, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_SHIPAUXNO & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SHIPAUXNO_BES, (int)SHIPAUXNO_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CSHIPAUXNO c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, SHIPAUXNO_BES, (int)SHIPAUXNO_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CTOURPFLEGE : public ppDadeVirtual {
public:
    tourpflegeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<tourpflegeS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tourpflegeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     tourpflegeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< tourpflegeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<tourpflegeS>::iterator
                 beginList() { return lst.begin(); }
    vector<tourpflegeS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetReihenfolgenr() const { return s.REIHENFOLGENR; }
    long         GetFahrtzeit() const { return s.FAHRTZEIT; }
    const char*  GetBemerkungen(ppString & t) const { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }
    long         GetLoginid() const { return s.LOGINID; }
    char         GetChangeid() const { return s.CHANGEID[0]; }
    char         GetKoart() const { return s.KOART[0]; }

    const tourpflegeS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_TOURPFLEGE_TOURID); }
    void         SetReihenfolgenr(long t) { s.REIHENFOLGENR = t; }
    void         SetFahrtzeit(long t) { s.FAHRTZEIT = t; }
    void         SetBemerkungen(const ppString & t) { ppGStrCopy(s.BEMERKUNGEN, t.c_str(), L_TOURPFLEGE_BEMERKUNGEN); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }
    void         SetLoginid(long t) { s.LOGINID = t; }
    void         SetChangeid(char t) { s.CHANGEID[0] = t; s.CHANGEID[1] = '\0';}
    void         SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}

    void         SetStruct(const tourpflegeS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelTourenKunde(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1272, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1273, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CTOURPFLEGE() {
        ::buf_default((void *)&s, TOURPFLEGE_BES, TOURPFLEGE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CTOURPFLEGE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, TOURPFLEGE_BES, TOURPFLEGE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TOURPFLEGE_BES, (int)TOURPFLEGE_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1272 ) return CursorServerCall(1272, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1273 ) return UniqueServerCall(1273, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_TOURPFLEGE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.BEMERKUNGEN);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, TOURPFLEGE_BES, (int)TOURPFLEGE_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CTOURPFLEGE c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, TOURPFLEGE_BES, (int)TOURPFLEGE_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CDELAYEDCST : public ppDadeVirtual {
public:
    delayedcstS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<delayedcstS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< delayedcstS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     delayedcstS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< delayedcstS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<delayedcstS>::iterator
                 beginList() { return lst.begin(); }
    vector<delayedcstS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetTime() const { return s.TIME; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    char         GetActiv() const { return s.ACTIV[0]; }
    short        GetDelayedweekday() const { return s.DELAYEDWEEKDAY; }
    char         GetNarcotic() const { return s.NARCOTIC[0]; }
    char         GetColdchain() const { return s.COLDCHAIN[0]; }
    char         GetCool08() const { return s.COOL08[0]; }
    char         GetCool20() const { return s.COOL20[0]; }

    const delayedcstS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetTime(long t) { s.TIME = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_DELAYEDCST_TOURID); }
    void         SetActiv(char t) { s.ACTIV[0] = t; s.ACTIV[1] = '\0';}
    void         SetDelayedweekday(short t) { s.DELAYEDWEEKDAY = t; }
    void         SetNarcotic(char t) { s.NARCOTIC[0] = t; s.NARCOTIC[1] = '\0';}
    void         SetColdchain(char t) { s.COLDCHAIN[0] = t; s.COLDCHAIN[1] = '\0';}
    void         SetCool08(char t) { s.COOL08[0] = t; s.COOL08[1] = '\0';}
    void         SetCool20(char t) { s.COOL20[0] = t; s.COOL20[1] = '\0';}

    void         SetStruct(const delayedcstS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1373, pos); }
    int          DeleteAll(int pos = 0) { int ret = UniqueServerCall(1378, pos); Strip(s); return ret; }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1372, pos); Strip(s); return ret; }
    int          InsertAll(int pos = 0) { int ret = UniqueServerCall(1376, pos); Strip(s); return ret; }
    int          SelDay(int pos = 0) { int ret = UniqueServerCall(1384, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1370, FetchRel, pos); return ret; }
    int          SelectActTouren(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1385, FetchRel, pos); return ret; }
    int          SelectTouren(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1379, FetchRel, pos); return ret; }
    int          SetActiv(int pos = 0) { int ret = UniqueServerCall(1377, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1371, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELAYEDCST() {
        ::buf_default((void *)&s, DELAYEDCST_BES, DELAYEDCST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELAYEDCST() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELAYEDCST_BES, DELAYEDCST_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, DELAYEDCST_BES, (int)DELAYEDCST_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1373 ) return UniqueServerCall(1373, pos);
        if ( fkt_nr == 1378 ) return UniqueServerCall(1378, pos);
        if ( fkt_nr == 1372 ) return UniqueServerCall(1372, pos);
        if ( fkt_nr == 1376 ) return UniqueServerCall(1376, pos);
        if ( fkt_nr == 1384 ) return UniqueServerCall(1384, pos);
        if ( fkt_nr == 1370 ) return CursorServerCall(1370, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1385 ) return CursorServerCall(1385, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1379 ) return CursorServerCall(1379, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1377 ) return UniqueServerCall(1377, pos);
        if ( fkt_nr == 1371 ) return UniqueServerCall(1371, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_DELAYEDCST & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELAYEDCST_BES, (int)DELAYEDCST_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CDELAYEDCST c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, DELAYEDCST_BES, (int)DELAYEDCST_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};

class CDELAYEDDELIVERYCSTSPECIAL : public ppDadeVirtual {
public:
    delayeddeliverycstspecialS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<delayeddeliverycstspecialS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< delayeddeliverycstspecialS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     delayeddeliverycstspecialS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< delayeddeliverycstspecialS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<delayeddeliverycstspecialS>::iterator
                 beginList() { return lst.begin(); }
    vector<delayeddeliverycstspecialS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    long         GetCustomerno() const { return s.CUSTOMERNO; }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetTime() const { return s.TIME; }
    char         GetActiv() const { return s.ACTIV[0]; }
    short        GetDelayedweekday() const { return s.DELAYEDWEEKDAY; }
    char         GetNarcotic() const { return s.NARCOTIC[0]; }
    char         GetColdchain() const { return s.COLDCHAIN[0]; }
    char         GetCool08() const { return s.COOL08[0]; }
    char         GetCool20() const { return s.COOL20[0]; }
    long         GetDatefrom() const { return s.DATEFROM; }
    long         GetDateto() const { return s.DATETO; }

    const delayeddeliverycstspecialS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetTime(long t) { s.TIME = t; }
    void         SetActiv(char t) { s.ACTIV[0] = t; s.ACTIV[1] = '\0';}
    void         SetDelayedweekday(short t) { s.DELAYEDWEEKDAY = t; }
    void         SetNarcotic(char t) { s.NARCOTIC[0] = t; s.NARCOTIC[1] = '\0';}
    void         SetColdchain(char t) { s.COLDCHAIN[0] = t; s.COLDCHAIN[1] = '\0';}
    void         SetCool08(char t) { s.COOL08[0] = t; s.COOL08[1] = '\0';}
    void         SetCool20(char t) { s.COOL20[0] = t; s.COOL20[1] = '\0';}
    void         SetDatefrom(long t) { s.DATEFROM = t; }
    void         SetDateto(long t) { s.DATETO = t; }

    void         SetStruct(const delayeddeliverycstspecialS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1735, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1734, pos); Strip(s); return ret; }
    int          Sel(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1732, FetchRel, pos); return ret; }
    int          SelUni(int pos = 0) { int ret = UniqueServerCall(1738, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1733, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CDELAYEDDELIVERYCSTSPECIAL() {
        ::buf_default((void *)&s, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CDELAYEDDELIVERYCSTSPECIAL() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, DELAYEDDELIVERYCSTSPECIAL_BES, DELAYEDDELIVERYCSTSPECIAL_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, DELAYEDDELIVERYCSTSPECIAL_BES, (int)DELAYEDDELIVERYCSTSPECIAL_ANZ, error_msg);
    #else
        pos = pos;
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        bOpenCursor  = false;
        bEndOfSelect = false;
        FncNumber    = 0;
        CursorPos    = 0;
        AnzPos       = 0;
        if (rc < 0)
            FehlerBehandlung(rc, error_msg);
        return rc;
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1735 ) return UniqueServerCall(1735, pos);
        if ( fkt_nr == 1734 ) return UniqueServerCall(1734, pos);
        if ( fkt_nr == 1732 ) return CursorServerCall(1732, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1738 ) return UniqueServerCall(1738, pos);
        if ( fkt_nr == 1733 ) return UniqueServerCall(1733, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_DELAYEDDELIVERYCSTSPECIAL & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, DELAYEDDELIVERYCSTSPECIAL_BES, (int)DELAYEDDELIVERYCSTSPECIAL_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }

    int CursorServerCall(int FncNr,int FetchRel = 1, int pos = 0) {
        if      (FetchRel == 0) return CloseCursor(pos);
        else if (FetchRel == 1) return GetNext(pos, FncNr);
        else if (FetchRel <  0) return ChangeCursor(FetchRel);
        else {
            FehlerBehandlung(-1, "False cursor position!");
            return -1;
        }
    }

    int GetNext(int pos, int FncNr) {
        CDELAYEDDELIVERYCSTSPECIAL c;
        if ( bOpenCursor && FncNumber != FncNr )
            CloseCursor(pos);
        if( bOpenCursor )
            s.FETCH_REL = 1;
        else {
            s.FETCH_REL = 2;
            bOpenCursor = true;
            FncNumber   = FncNr;
            AnzPos      = 0;
            lst.clear();
        }
        if ( (CursorPos == AnzPos) && bEndOfSelect ) {
            rc = 1;
            return 1;
        }
        else if( CursorPos < AnzPos ) {
            s = lst.at(CursorPos);
            CursorPos++;
            return 0;
        }
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, DELAYEDDELIVERYCSTSPECIAL_BES, (int)DELAYEDDELIVERYCSTSPECIAL_ANZ, error_msg);
    #else
        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
    #endif
        if (rc == 0) {
            Strip(s);
            c.s = s;
            lst.insert(lst.end(), c.s);
            bEndOfSelect = false;
            CursorPos++;
            AnzPos++;
        }
        else if (rc == 1)
            bEndOfSelect = true;
        else if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

    // FetchRel is a negative value
    int ChangeCursor(int FetchRel) {
        CursorPos = (CursorPos + FetchRel) < 0 ?
                     0                         :
                     CursorPos + FetchRel - 1;
        if ( CursorPos >= AnzPos ) {
            FehlerBehandlung (-1, "False cursor position!");
            return -1;
        }
        s = lst.at(CursorPos);
        CursorPos++;
        rc = 0;
        return 0;
    }
};
#endif    // TRANSCLASS

#endif   // GUARD
