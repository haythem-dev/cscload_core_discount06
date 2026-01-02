#ifndef __PP_CALLPLANMAINTENANCE_H_
#define __PP_CALLPLANMAINTENANCE_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of MCALLPARAMATER ********************************************/

#define L_MCALLPARAMATER_VERTRIEBSZENTRUMNR 6
#define L_MCALLPARAMATER_RUFZEITVERSCHIEBEN 6
#define L_MCALLPARAMATER_ANZRUFWIEDERHOLUNG 6
#define L_MCALLPARAMATER_RUFABWEICHUNGPH 6
#define L_MCALLPARAMATER_RUFABWEICHUNGDP 6
#define L_MCALLPARAMATER_RUFABWEICHUNGDS 6
#define L_MCALLPARAMATER_ZEITFENSTERAUFTRAG 6
#define L_MCALLPARAMATER_ZEITANZPOSAUFTRAG 6
#define L_MCALLPARAMATER_TM_DATE 11
#define L_MCALLPARAMATER_TM_TIME 11
#define L_MCALLPARAMATER_LOGINID 11
#define L_MCALLPARAMATER_CHANGEID 1
#define L_MCALLPARAMATER_UMKRUFWIEDERHOLUNG 6
#define L_MCALLPARAMATER_KABRUFWIEDERHOLUNG 6
#define L_MCALLPARAMATER_ANZRUFVERSCHIEBEN 6
#define L_MCALLPARAMATER_MINRUFVERSCHIEBEN 6
#define L_MCALLPARAMATER_CALLPLANSTARTSTOP 1
#define L_MCALLPARAMATER_STOPSTARTZEIT 6

/* Length-Define of MCALLPARAMTERTIMES ****************************************/

#define L_MCALLPARAMTERTIMES_VERTRIEBSZENTRUMNR 6
#define L_MCALLPARAMTERTIMES_RUFABWEICHUNGPH 6
#define L_MCALLPARAMTERTIMES_RUFABWEICHUNGDP 6
#define L_MCALLPARAMTERTIMES_RUFABWEICHUNGDS 6
#define L_MCALLPARAMTERTIMES_TM_DATE 11
#define L_MCALLPARAMTERTIMES_TM_TIME 11
#define L_MCALLPARAMTERTIMES_LOGINID 11
#define L_MCALLPARAMTERTIMES_CHANGEID 1

/* Length-Define of MCALLPLANLOAD *********************************************/

#define L_MCALLPLANLOAD_LADEKIPPZEIT 11
#define L_MCALLPLANLOAD_VERTRIEBSZENTRUMNR 6
#define L_MCALLPLANLOAD_DATUM 11
#define L_MCALLPLANLOAD_WOCHENTAG 2
#define L_MCALLPLANLOAD_LADEDATUM 11
#define L_MCALLPLANLOAD_LADEVZ 6
#define L_MCALLPLANLOAD_BUNDESLAND 6
#define L_MCALLPLANLOAD_TOURID 6
#define L_MCALLPLANLOAD_LADEZEITAB 11
#define L_MCALLPLANLOAD_LADEZEITBIS 11

/* Length-Define of MCUSTOMERCALLPLAN *****************************************/

#define L_MCUSTOMERCALLPLAN_IDFNR 11
#define L_MCUSTOMERCALLPLAN_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERCALLPLAN_KUNDENNR 11
#define L_MCUSTOMERCALLPLAN_TAGNR 1
#define L_MCUSTOMERCALLPLAN_URRUFZEIT 11
#define L_MCUSTOMERCALLPLAN_RUFPROTOKOLL 1
#define L_MCUSTOMERCALLPLAN_RUFSTEUERUNG 6
#define L_MCUSTOMERCALLPLAN_POOLNR 6
#define L_MCUSTOMERCALLPLAN_MODEMPOOLNR 6
#define L_MCUSTOMERCALLPLAN_RUFEINSTELLUNG 1
#define L_MCUSTOMERCALLPLAN_ANRUFTYP 1
#define L_MCUSTOMERCALLPLAN_TM_DATE 11
#define L_MCUSTOMERCALLPLAN_TM_TIME 11
#define L_MCUSTOMERCALLPLAN_LOGINID 11
#define L_MCUSTOMERCALLPLAN_CHANGEID 1
#define L_MCUSTOMERCALLPLAN_TOURID 6
#define L_MCUSTOMERCALLPLAN_SKDANRUFGENERELL 1
#define L_MCUSTOMERCALLPLAN_BEMERKUNG 240

/* Length-Define of MCUSTOMERCALLPLANPHONPROT *********************************/

#define L_MCUSTOMERCALLPLANPHONPROT_DATUM 11
#define L_MCUSTOMERCALLPLANPHONPROT_RUFZEIT 11
#define L_MCUSTOMERCALLPLANPHONPROT_IDFNR 11
#define L_MCUSTOMERCALLPLANPHONPROT_STATUS 11
#define L_MCUSTOMERCALLPLANPHONPROT_RUFZEITGEAENDERT 11
#define L_MCUSTOMERCALLPLANPHONPROT_ZEIT 11
#define L_MCUSTOMERCALLPLANPHONPROT_UID 11
#define L_MCUSTOMERCALLPLANPHONPROT_BEMERKUNG 240
#define L_MCUSTOMERCALLPLANPHONPROT_FILIALNR 6

/* Length-Define of MCUSTOMERCALLPLANTOUR *************************************/

#define L_MCUSTOMERCALLPLANTOUR_DATUMKOMMI 11
#define L_MCUSTOMERCALLPLANTOUR_ISTVERBUNDTOUR 1
#define L_MCUSTOMERCALLPLANTOUR_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERCALLPLANTOUR_KUNDENNR 11
#define L_MCUSTOMERCALLPLANTOUR_TOURID 6
#define L_MCUSTOMERCALLPLANTOUR_FILIALNR 6
#define L_MCUSTOMERCALLPLANTOUR_WEEKDAY 6

/* Length-Define of MCUSTOMERCALLPLANPHON *************************************/

#define L_MCUSTOMERCALLPLANPHON_FILIALNR 6
#define L_MCUSTOMERCALLPLANPHON_IDFNR 11
#define L_MCUSTOMERCALLPLANPHON_DATUM 11
#define L_MCUSTOMERCALLPLANPHON_RUFZEIT 11
#define L_MCUSTOMERCALLPLANPHON_LFDAKTION 6
#define L_MCUSTOMERCALLPLANPHON_PRIORITAET 6
#define L_MCUSTOMERCALLPLANPHON_WOCHENTAG 2
#define L_MCUSTOMERCALLPLANPHON_POOLID 6
#define L_MCUSTOMERCALLPLANPHON_ANRUFART 2
#define L_MCUSTOMERCALLPLANPHON_MANUELL 1
#define L_MCUSTOMERCALLPLANPHON_STAGRUECKRUF 1
#define L_MCUSTOMERCALLPLANPHON_ZUGRIFF 6
#define L_MCUSTOMERCALLPLANPHON_CALLINFO 240

/* Length-Define of MCUSTOMERDISPLAY ******************************************/

#define L_MCUSTOMERDISPLAY_IDFNR 11
#define L_MCUSTOMERDISPLAY_FILIALNR 6
#define L_MCUSTOMERDISPLAY_ANREDEKZ 6
#define L_MCUSTOMERDISPLAY_NAMEAPO 40
#define L_MCUSTOMERDISPLAY_NAMEINHABER 30
#define L_MCUSTOMERDISPLAY_STRASSE 30
#define L_MCUSTOMERDISPLAY_ORT 30
#define L_MCUSTOMERDISPLAY_POSTLEITZAHL 10
#define L_MCUSTOMERDISPLAY_TELNR 20
#define L_MCUSTOMERDISPLAY_TELNRDAFUE 20
#define L_MCUSTOMERDISPLAY_TELKURZWAHL 4
#define L_MCUSTOMERDISPLAY_SKDKUNDEAEGESPERRT 1
#define L_MCUSTOMERDISPLAY_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERDISPLAY_KUNDENNR 11
#define L_MCUSTOMERDISPLAY_SKDANRUFGENERELL 1

/* Length-Define of MDEVICEPLANMAINTENANCE ************************************/

#define L_MDEVICEPLANMAINTENANCE_REGIONENTYP 6
#define L_MDEVICEPLANMAINTENANCE_FILIALNR 6
#define L_MDEVICEPLANMAINTENANCE_GERAETEID 4
#define L_MDEVICEPLANMAINTENANCE_GERAETEART 1
#define L_MDEVICEPLANMAINTENANCE_GERAETNST 11
#define L_MDEVICEPLANMAINTENANCE_GERAETEVERW1 1
#define L_MDEVICEPLANMAINTENANCE_MODEMTYP 1
#define L_MDEVICEPLANMAINTENANCE_VERTRIEBSZENTRUMNR 6
#define L_MDEVICEPLANMAINTENANCE_UMKNR 6
#define L_MDEVICEPLANMAINTENANCE_TM_DATE 11
#define L_MDEVICEPLANMAINTENANCE_TM_TIME 11
#define L_MDEVICEPLANMAINTENANCE_LOGINID 11
#define L_MDEVICEPLANMAINTENANCE_CHANGEID 1
#define L_MDEVICEPLANMAINTENANCE_AKTIV 1
#define L_MDEVICEPLANMAINTENANCE_UMKNST 6

/* Length-Define of MREGION ***************************************************/

#define L_MREGION_REGIONENTYP 6
#define L_MREGION_REGIONNR 11
#define L_MREGION_REGIONTEILNR 11
#define L_MREGION_NAME 30
#define L_MREGION_TM_DATE 11
#define L_MREGION_TM_TIME 11
#define L_MREGION_LOGINID 11
#define L_MREGION_CHANGEID 1

/* Length-Define of MSALECENTER ***********************************************/

#define L_MSALECENTER_FILIALNR 6
#define L_MSALECENTER_NAME 30

/* Length-Define of MUMKCONNECTION ********************************************/

#define L_MUMKCONNECTION_REGIONENTYP 6
#define L_MUMKCONNECTION_REGIONNR 11
#define L_MUMKCONNECTION_FILIALNR 6
#define L_MUMKCONNECTION_UMKNR 6
#define L_MUMKCONNECTION_RECHNERNAME 15
#define L_MUMKCONNECTION_PORTNR 11
#define L_MUMKCONNECTION_TM_DATE 11
#define L_MUMKCONNECTION_TM_TIME 11
#define L_MUMKCONNECTION_LOGINID 11
#define L_MUMKCONNECTION_CHANGEID 1

/* SqlDefine of MCALLPARAMATER ************************************************/


#define MCALLPARAMATER_PLISTE \
        "ANRUFPARAMETER.VERTRIEBSZENTRUMNR,"\
        "ANRUFPARAMETER.RUFZEITVERSCHIEBEN,"\
        "ANRUFPARAMETER.ANZRUFWIEDERHOLUNG,"\
        "ANRUFPARAMETER.RUFABWEICHUNGPH,"\
        "ANRUFPARAMETER.RUFABWEICHUNGDP,"\
        "ANRUFPARAMETER.RUFABWEICHUNGDS,"\
        "ANRUFPARAMETER.ZEITFENSTERAUFTRAG,"\
        "ANRUFPARAMETER.ZEITANZPOSAUFTRAG,"\
        "ANRUFPARAMETER.TM_DATE,"\
        "ANRUFPARAMETER.TM_TIME,"\
        "ANRUFPARAMETER.LOGINID,"\
        "ANRUFPARAMETER.CHANGEID,"\
        "ANRUFPARAMETER.UMKRUFWIEDERHOLUNG,"\
        "ANRUFPARAMETER.KABRUFWIEDERHOLUNG,"\
        "ANRUFPARAMETER.ANZRUFVERSCHIEBEN,"\
        "ANRUFPARAMETER.MINRUFVERSCHIEBEN,"\
        "ANRUFPARAMETER.CALLPLANSTARTSTOP,"\
        "ANRUFPARAMETER.STOPSTARTZEIT"

/* SqlDefine of MCALLPARAMTERTIMES ********************************************/


#define MCALLPARAMTERTIMES_PLISTE \
        "ANRUFPARAMETER.VERTRIEBSZENTRUMNR,"\
        "ANRUFPARAMETER.RUFABWEICHUNGPH,"\
        "ANRUFPARAMETER.RUFABWEICHUNGDP,"\
        "ANRUFPARAMETER.RUFABWEICHUNGDS,"\
        "ANRUFPARAMETER.TM_DATE,"\
        "ANRUFPARAMETER.TM_TIME,"\
        "ANRUFPARAMETER.LOGINID,"\
        "ANRUFPARAMETER.CHANGEID"

/* SqlDefine of MCALLPLANLOAD *************************************************/


#define MCALLPLANLOAD_PLISTE \
        "LADEANRUFPLAN.VERTRIEBSZENTRUMNR,"\
        "LADEANRUFPLAN.DATUM,"\
        "LADEANRUFPLAN.WOCHENTAG,"\
        "LADEANRUFPLAN.LADEDATUM,"\
        "LADEANRUFPLAN.LADEVZ,"\
        "LADEANRUFPLAN.BUNDESLAND,"\
        "LADEANRUFPLAN.TOURID,"\
        "LADEANRUFPLAN.LADEZEITAB,"\
        "LADEANRUFPLAN.LADEZEITBIS"

/* SqlDefine of MCUSTOMERCALLPLAN *********************************************/


#define MCUSTOMERCALLPLAN_PLISTE \
        "KUNDE.IDFNR,"\
        "KUNDEMASTERPLAN.VERTRIEBSZENTRUMNR,"\
        "KUNDEMASTERPLAN.KUNDENNR,"\
        "KUNDEMASTERPLAN.TAGNR,"\
        "KUNDEMASTERPLAN.URRUFZEIT,"\
        "KUNDEMASTERPLAN.RUFPROTOKOLL,"\
        "KUNDEMASTERPLAN.RUFSTEUERUNG,"\
        "KUNDEMASTERPLAN.POOLNR,"\
        "KUNDEMASTERPLAN.MODEMPOOLNR,"\
        "KUNDEMASTERPLAN.RUFEINSTELLUNG,"\
        "KUNDEMASTERPLAN.ANRUFTYP,"\
        "KUNDEMASTERPLAN.TM_DATE,"\
        "KUNDEMASTERPLAN.TM_TIME,"\
        "KUNDEMASTERPLAN.LOGINID,"\
        "KUNDEMASTERPLAN.CHANGEID,"\
        "KUNDEMASTERPLAN.TOURID,"\
        "KUNDEMASTERPLAN.SKDANRUFGENERELL,"\
        "KUNDEMASTERPLAN.BEMERKUNG"

/* SqlDefine of MCUSTOMERCALLPLANPHONPROT *************************************/


#define MCUSTOMERCALLPLANPHONPROT_PLISTE \
        "TAGPLANEREIGNIS.DATUM,"\
        "TAGPLANEREIGNIS.RUFZEIT,"\
        "TAGPLANEREIGNIS.IDFNR,"\
        "TAGPLANEREIGNIS.STATUS,"\
        "TAGPLANEREIGNIS.RUFZEITGEAENDERT,"\
        "TAGPLANEREIGNIS.ZEIT,"\
        "TAGPLANEREIGNIS.UID,"\
        "TAGPLANEREIGNIS.BEMERKUNG,"\
        "TAGPLANEREIGNIS.FILIALNR"

/* SqlDefine of MCUSTOMERCALLPLANTOUR *****************************************/


#define MCUSTOMERCALLPLANTOUR_PLISTE \
        "TOURPLANTAG.DATUMKOMMI,"\
        "TOURPLANTAG.ISTVERBUNDTOUR,"\
        "TOURPLANTAG.VERTRIEBSZENTRUMNR,"\
        "TOURPLANTAG.KUNDENNR,"\
        "TOURPLANWOCHE.TOURID,"\
        "TOURPLANWOCHE.FILIALNR,"\
        "TOURPLANWOCHE.WEEKDAY"

/* SqlDefine of MCUSTOMERCALLPLANPHON *****************************************/


#define MCUSTOMERCALLPLANPHON_PLISTE \
        "TAGPLAN.FILIALNR,"\
        "TAGPLAN.IDFNR,"\
        "TAGPLAN.DATUM,"\
        "TAGPLAN.RUFZEIT,"\
        "TAGPLAN.LFDAKTION,"\
        "TAGPLAN.PRIORITAET,"\
        "TAGPLAN.WOCHENTAG,"\
        "TAGPLAN.POOLID,"\
        "TAGPLAN.ANRUFART,"\
        "TAGPLAN.MANUELL,"\
        "TAGPLAN.STAGRUECKRUF,"\
        "TAGPLAN.ZUGRIFF,"\
        "TAGPLAN.CALLINFO"

/* SqlDefine of MCUSTOMERDISPLAY **********************************************/


#define MCUSTOMERDISPLAY_PLISTE \
        "KUNDE.IDFNR,"\
        "KUNDE.FILIALNR,"\
        "KUNDE.ANREDEKZ,"\
        "KUNDE.NAMEAPO,"\
        "KUNDE.NAMEINHABER,"\
        "KUNDE.STRASSE,"\
        "KUNDE.ORT,"\
        "KUNDE.POSTLEITZAHL,"\
        "KUNDE.TELNR,"\
        "KUNDE.TELNRDAFUE,"\
        "KUNDE.TELKURZWAHL,"\
        "KUNDESCHALTER.SKDKUNDEAEGESPERRT,"\
        "KUNDE.VERTRIEBSZENTRUMNR,"\
        "KUNDE.KUNDENNR,"\
        "KUNDESCHALTER.SKDANRUFGENERELL"

/* SqlDefine of MDEVICEPLANMAINTENANCE ****************************************/


#define MDEVICEPLANMAINTENANCE_PLISTE \
        "REGIONARTEN.REGIONENTYP,"\
        "MODEMANRUFPLAN.FILIALNR,"\
        "MODEMANRUFPLAN.GERAETEID,"\
        "MODEMANRUFPLAN.GERAETEART,"\
        "MODEMANRUFPLAN.GERAETNST,"\
        "MODEMANRUFPLAN.GERAETEVERW1,"\
        "MODEMANRUFPLAN.MODEMTYP,"\
        "MODEMANRUFPLAN.VERTRIEBSZENTRUMNR,"\
        "MODEMANRUFPLAN.UMKNR,"\
        "MODEMANRUFPLAN.TM_DATE,"\
        "MODEMANRUFPLAN.TM_TIME,"\
        "MODEMANRUFPLAN.LOGINID,"\
        "MODEMANRUFPLAN.CHANGEID,"\
        "MODEMANRUFPLAN.AKTIV,"\
        "MODEMANRUFPLAN.UMKNST"

/* SqlDefine of MREGION *******************************************************/


#define MREGION_PLISTE \
        "REGIONARTEN.REGIONENTYP,"\
        "REGIONARTEN.REGIONNR,"\
        "REGIONARTEN.REGIONTEILNR,"\
        "FILIALE.NAME,"\
        "REGIONARTEN.TM_DATE,"\
        "REGIONARTEN.TM_TIME,"\
        "REGIONARTEN.LOGINID,"\
        "REGIONARTEN.CHANGEID"

/* SqlDefine of MSALECENTER ***************************************************/


#define MSALECENTER_PLISTE \
        "FILIALE.FILIALNR,"\
        "FILIALE.NAME"

/* SqlDefine of MUMKCONNECTION ************************************************/


#define MUMKCONNECTION_PLISTE \
        "REGIONARTEN.REGIONENTYP,"\
        "REGIONARTEN.REGIONNR,"\
        "UMKVERWALTUNG.FILIALNR,"\
        "UMKVERWALTUNG.UMKNR,"\
        "UMKVERWALTUNG.RECHNERNAME,"\
        "UMKVERWALTUNG.PORTNR,"\
        "UMKVERWALTUNG.TM_DATE,"\
        "UMKVERWALTUNG.TM_TIME,"\
        "UMKVERWALTUNG.LOGINID,"\
        "UMKVERWALTUNG.CHANGEID"

/* SqlDefine of MCALLPARAMATER ************************************************/


#define MCALLPARAMATER_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "RUFZEITVERSCHIEBEN=?,"\
        "ANZRUFWIEDERHOLUNG=?,"\
        "ZEITFENSTERAUFTRAG=?,"\
        "ZEITANZPOSAUFTRAG=?,"\
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "LOGINID=?,"\
        "CHANGEID=?,"\
        "UMKRUFWIEDERHOLUNG=?,"\
        "KABRUFWIEDERHOLUNG=?,"\
        "ANZRUFVERSCHIEBEN=?,"\
        "MINRUFVERSCHIEBEN=?,"\
        "CALLPLANSTARTSTOP=?,"\
        "STOPSTARTZEIT=?"
/* SqlDefine of MCALLPARAMTERTIMES ********************************************/


#define MCALLPARAMTERTIMES_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "RUFABWEICHUNGPH=?,"\
        "RUFABWEICHUNGDP=?,"\
        "RUFABWEICHUNGDS=?,"\
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "LOGINID=?,"\
        "CHANGEID=?"
/* SqlDefine of MCALLPLANLOAD *************************************************/


#define MCALLPLANLOAD_UPDLISTE \
        "WOCHENTAG=?,"\
        "LADEDATUM=?,"\
        "LADEVZ=?,"\
        "BUNDESLAND=?,"\
        "TOURID=?,"\
        "LADEZEITAB=?,"\
        "LADEZEITBIS=?"
/* SqlDefine of MCUSTOMERCALLPLAN *********************************************/


#define MCUSTOMERCALLPLAN_UPDLISTE \
        "RUFPROTOKOLL=?,"\
        "RUFSTEUERUNG=?,"\
        "POOLNR=?,"\
        "MODEMPOOLNR=?,"\
        "RUFEINSTELLUNG=?,"\
        "ANRUFTYP=?,"\
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "LOGINID=?,"\
        "CHANGEID=?,"\
        "TOURID=?,"\
        "SKDANRUFGENERELL=?,"\
        "BEMERKUNG=?"
/* SqlDefine of MCUSTOMERCALLPLANPHONPROT *************************************/


#define MCUSTOMERCALLPLANPHONPROT_UPDLISTE \
        "DATUM=?,"\
        "RUFZEIT=?,"\
        "IDFNR=?,"\
        "STATUS=?,"\
        "RUFZEITGEAENDERT=?,"\
        "ZEIT=?,"\
        "UID=?,"\
        "BEMERKUNG=?,"\
        "FILIALNR=?"
/* SqlDefine of MCUSTOMERCALLPLANTOUR *****************************************/


#define MCUSTOMERCALLPLANTOUR_UPDLISTE \
        "DATUMKOMMI=?,"\
        "WEEKDAY=?"
/* SqlDefine of MCUSTOMERCALLPLANPHON *****************************************/


#define MCUSTOMERCALLPLANPHON_UPDLISTE \
        "FILIALNR=?,"\
        "IDFNR=?,"\
        "DATUM=?,"\
        "RUFZEIT=?,"\
        "LFDAKTION=?,"\
        "PRIORITAET=?,"\
        "WOCHENTAG=?,"\
        "POOLID=?,"\
        "ANRUFART=?,"\
        "MANUELL=?,"\
        "STAGRUECKRUF=?,"\
        "ZUGRIFF=?,"\
        "CALLINFO=?"
/* SqlDefine of MCUSTOMERDISPLAY **********************************************/


#define MCUSTOMERDISPLAY_UPDLISTE \
        "TELNR=?,"\
        "TELNRDAFUE=?,"\
        "TELKURZWAHL=?"
/* SqlDefine of MDEVICEPLANMAINTENANCE ****************************************/


#define MDEVICEPLANMAINTENANCE_UPDLISTE \
        "GERAETEART=?,"\
        "GERAETNST=?,"\
        "GERAETEVERW1=?,"\
        "MODEMTYP=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "UMKNR=?,"\
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "LOGINID=?,"\
        "CHANGEID=?,"\
        "AKTIV=?,"\
        "UMKNST=?"
/* SqlDefine of MREGION *******************************************************/


#define MREGION_UPDLISTE \
        "REGIONENTYP=?,"\
        "REGIONNR=?,"\
        "REGIONTEILNR=?,"\
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "LOGINID=?,"\
        "CHANGEID=?"
/* SqlDefine of MSALECENTER ***************************************************/


#define MSALECENTER_UPDLISTE \
        "FILIALNR=?,"\
        "NAME=?"
/* SqlDefine of MUMKCONNECTION ************************************************/


#define MUMKCONNECTION_UPDLISTE \
        "FILIALNR=?,"\
        "UMKNR=?,"\
        "RECHNERNAME=?,"\
        "PORTNR=?,"\
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "LOGINID=?,"\
        "CHANGEID=?"
/* SqlMacros-Define of MCALLPARAMATER *****************************************/

#define MCALLPARAMATER_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->RUFZEITVERSCHIEBEN,\
        :x->ANZRUFWIEDERHOLUNG,\
        :x->ZEITFENSTERAUFTRAG,\
        :x->ZEITANZPOSAUFTRAG,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->UMKRUFWIEDERHOLUNG,\
        :x->KABRUFWIEDERHOLUNG,\
        :x->ANZRUFVERSCHIEBEN,\
        :x->MINRUFVERSCHIEBEN,\
        :x->CALLPLANSTARTSTOP,\
        :x->STOPSTARTZEIT
#define MCALLPARAMATER_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->RUFZEITVERSCHIEBEN,\
        :x->ANZRUFWIEDERHOLUNG,\
        :x->RUFABWEICHUNGPH,\
        :x->RUFABWEICHUNGDP,\
        :x->RUFABWEICHUNGDS,\
        :x->ZEITFENSTERAUFTRAG,\
        :x->ZEITANZPOSAUFTRAG,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->UMKRUFWIEDERHOLUNG,\
        :x->KABRUFWIEDERHOLUNG,\
        :x->ANZRUFVERSCHIEBEN,\
        :x->MINRUFVERSCHIEBEN,\
        :x->CALLPLANSTARTSTOP,\
        :x->STOPSTARTZEIT

/* SqlMacros-Define of MCALLPARAMTERTIMES *************************************/

#define MCALLPARAMTERTIMES_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->RUFABWEICHUNGPH,\
        :x->RUFABWEICHUNGDP,\
        :x->RUFABWEICHUNGDS,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID
#define MCALLPARAMTERTIMES_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->RUFABWEICHUNGPH,\
        :x->RUFABWEICHUNGDP,\
        :x->RUFABWEICHUNGDS,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID

/* SqlMacros-Define of MCALLPLANLOAD ******************************************/

#define MCALLPLANLOAD_ZEIGER(x) \
        :x->WOCHENTAG,\
        :x->LADEDATUM,\
        :x->LADEVZ,\
        :x->BUNDESLAND,\
        :x->TOURID,\
        :x->LADEZEITAB,\
        :x->LADEZEITBIS
#define MCALLPLANLOAD_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->DATUM,\
        :x->WOCHENTAG,\
        :x->LADEDATUM,\
        :x->LADEVZ,\
        :x->BUNDESLAND,\
        :x->TOURID,\
        :x->LADEZEITAB,\
        :x->LADEZEITBIS

/* SqlMacros-Define of MCUSTOMERCALLPLAN **************************************/

#define MCUSTOMERCALLPLAN_ZEIGER(x) \
        :x->RUFPROTOKOLL,\
        :x->RUFSTEUERUNG,\
        :x->POOLNR,\
        :x->MODEMPOOLNR,\
        :x->RUFEINSTELLUNG,\
        :x->ANRUFTYP,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->TOURID,\
        :x->SKDANRUFGENERELL,\
        :x->BEMERKUNG
#define MCUSTOMERCALLPLAN_ZEIGERSEL(x) \
        :x->IDFNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->TAGNR,\
        :x->URRUFZEIT,\
        :x->RUFPROTOKOLL,\
        :x->RUFSTEUERUNG,\
        :x->POOLNR,\
        :x->MODEMPOOLNR,\
        :x->RUFEINSTELLUNG,\
        :x->ANRUFTYP,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->TOURID,\
        :x->SKDANRUFGENERELL,\
        :x->BEMERKUNG

/* SqlMacros-Define of MCUSTOMERCALLPLANPHONPROT ******************************/

#define MCUSTOMERCALLPLANPHONPROT_ZEIGER(x) \
        :x->DATUM,\
        :x->RUFZEIT,\
        :x->IDFNR,\
        :x->STATUS,\
        :x->RUFZEITGEAENDERT,\
        :x->ZEIT,\
        :x->UID,\
        :x->BEMERKUNG,\
        :x->FILIALNR
#define MCUSTOMERCALLPLANPHONPROT_ZEIGERSEL(x) \
        :x->DATUM,\
        :x->RUFZEIT,\
        :x->IDFNR,\
        :x->STATUS,\
        :x->RUFZEITGEAENDERT,\
        :x->ZEIT,\
        :x->UID,\
        :x->BEMERKUNG,\
        :x->FILIALNR

/* SqlMacros-Define of MCUSTOMERCALLPLANTOUR **********************************/

#define MCUSTOMERCALLPLANTOUR_ZEIGER(x) \
        :x->DATUMKOMMI,\
        :x->WEEKDAY
#define MCUSTOMERCALLPLANTOUR_ZEIGERSEL(x) \
        :x->DATUMKOMMI,\
        :x->ISTVERBUNDTOUR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->TOURID,\
        :x->FILIALNR,\
        :x->WEEKDAY

/* SqlMacros-Define of MCUSTOMERCALLPLANPHON **********************************/

#define MCUSTOMERCALLPLANPHON_ZEIGER(x) \
        :x->FILIALNR,\
        :x->IDFNR,\
        :x->DATUM,\
        :x->RUFZEIT,\
        :x->LFDAKTION,\
        :x->PRIORITAET,\
        :x->WOCHENTAG,\
        :x->POOLID,\
        :x->ANRUFART,\
        :x->MANUELL,\
        :x->STAGRUECKRUF,\
        :x->ZUGRIFF,\
        :x->CALLINFO
#define MCUSTOMERCALLPLANPHON_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->IDFNR,\
        :x->DATUM,\
        :x->RUFZEIT,\
        :x->LFDAKTION,\
        :x->PRIORITAET,\
        :x->WOCHENTAG,\
        :x->POOLID,\
        :x->ANRUFART,\
        :x->MANUELL,\
        :x->STAGRUECKRUF,\
        :x->ZUGRIFF,\
        :x->CALLINFO

/* SqlMacros-Define of MCUSTOMERDISPLAY ***************************************/

#define MCUSTOMERDISPLAY_ZEIGER(x) \
        :x->TELNR,\
        :x->TELNRDAFUE,\
        :x->TELKURZWAHL
#define MCUSTOMERDISPLAY_ZEIGERSEL(x) \
        :x->IDFNR,\
        :x->FILIALNR,\
        :x->ANREDEKZ,\
        :x->NAMEAPO,\
        :x->NAMEINHABER,\
        :x->STRASSE,\
        :x->ORT,\
        :x->POSTLEITZAHL,\
        :x->TELNR,\
        :x->TELNRDAFUE,\
        :x->TELKURZWAHL,\
        :x->SKDKUNDEAEGESPERRT,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->SKDANRUFGENERELL

/* SqlMacros-Define of MDEVICEPLANMAINTENANCE *********************************/

#define MDEVICEPLANMAINTENANCE_ZEIGER(x) \
        :x->GERAETEART,\
        :x->GERAETNST,\
        :x->GERAETEVERW1,\
        :x->MODEMTYP,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->UMKNR,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->AKTIV,\
        :x->UMKNST
#define MDEVICEPLANMAINTENANCE_ZEIGERSEL(x) \
        :x->REGIONENTYP,\
        :x->FILIALNR,\
        :x->GERAETEID,\
        :x->GERAETEART,\
        :x->GERAETNST,\
        :x->GERAETEVERW1,\
        :x->MODEMTYP,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->UMKNR,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID,\
        :x->AKTIV,\
        :x->UMKNST

/* SqlMacros-Define of MREGION ************************************************/

#define MREGION_ZEIGER(x) \
        :x->REGIONENTYP,\
        :x->REGIONNR,\
        :x->REGIONTEILNR,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID
#define MREGION_ZEIGERSEL(x) \
        :x->REGIONENTYP,\
        :x->REGIONNR,\
        :x->REGIONTEILNR,\
        :x->NAME,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID

/* SqlMacros-Define of MSALECENTER ********************************************/

#define MSALECENTER_ZEIGER(x) \
        :x->FILIALNR,\
        :x->NAME
#define MSALECENTER_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->NAME

/* SqlMacros-Define of MUMKCONNECTION *****************************************/

#define MUMKCONNECTION_ZEIGER(x) \
        :x->FILIALNR,\
        :x->UMKNR,\
        :x->RECHNERNAME,\
        :x->PORTNR,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID
#define MUMKCONNECTION_ZEIGERSEL(x) \
        :x->REGIONENTYP,\
        :x->REGIONNR,\
        :x->FILIALNR,\
        :x->UMKNR,\
        :x->RECHNERNAME,\
        :x->PORTNR,\
        :x->TM_DATE,\
        :x->TM_TIME,\
        :x->LOGINID,\
        :x->CHANGEID

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define MCALLPARAMATER_H
#define MCALLPARAMATER_ANZ ( sizeof(MCALLPARAMATER_BES) / sizeof(struct buf_desc) )
#define MCALLPARAMTERTIMES_H
#define MCALLPARAMTERTIMES_ANZ ( sizeof(MCALLPARAMTERTIMES_BES) / sizeof(struct buf_desc) )
#define MCALLPLANLOAD_H
#define MCALLPLANLOAD_ANZ ( sizeof(MCALLPLANLOAD_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERCALLPLAN_H
#define MCUSTOMERCALLPLAN_ANZ ( sizeof(MCUSTOMERCALLPLAN_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERCALLPLANPHONPROT_H
#define MCUSTOMERCALLPLANPHONPROT_ANZ ( sizeof(MCUSTOMERCALLPLANPHONPROT_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERCALLPLANTOUR_H
#define MCUSTOMERCALLPLANTOUR_ANZ ( sizeof(MCUSTOMERCALLPLANTOUR_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERCALLPLANPHON_H
#define MCUSTOMERCALLPLANPHON_ANZ ( sizeof(MCUSTOMERCALLPLANPHON_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERDISPLAY_H
#define MCUSTOMERDISPLAY_ANZ ( sizeof(MCUSTOMERDISPLAY_BES) / sizeof(struct buf_desc) )
#define MDEVICEPLANMAINTENANCE_H
#define MDEVICEPLANMAINTENANCE_ANZ ( sizeof(MDEVICEPLANMAINTENANCE_BES) / sizeof(struct buf_desc) )
#define MREGION_H
#define MREGION_ANZ ( sizeof(MREGION_BES) / sizeof(struct buf_desc) )
#define MSALECENTER_H
#define MSALECENTER_ANZ ( sizeof(MSALECENTER_BES) / sizeof(struct buf_desc) )
#define MUMKCONNECTION_H
#define MUMKCONNECTION_ANZ ( sizeof(MUMKCONNECTION_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of MCALLPARAMATER ******************************************/

#ifndef TRANSCLASS
typedef struct N_MCALLPARAMATER {
    short VERTRIEBSZENTRUMNR;
    short RUFZEITVERSCHIEBEN;
    short ANZRUFWIEDERHOLUNG;
    short RUFABWEICHUNGPH;
    short RUFABWEICHUNGDP;
    short RUFABWEICHUNGDS;
    short ZEITFENSTERAUFTRAG;
    short ZEITANZPOSAUFTRAG;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    short UMKRUFWIEDERHOLUNG;
    short KABRUFWIEDERHOLUNG;
    short ANZRUFVERSCHIEBEN;
    short MINRUFVERSCHIEBEN;
    char CALLPLANSTARTSTOP[2];
    short STOPSTARTZEIT;
    long FETCH_REL;
} mcallparamaterS;
#else /* TRANSCLASS */
typedef struct N_MCALLPARAMATER {
    short VERTRIEBSZENTRUMNR;
    short RUFZEITVERSCHIEBEN;
    short ANZRUFWIEDERHOLUNG;
    short RUFABWEICHUNGPH;
    short RUFABWEICHUNGDP;
    short RUFABWEICHUNGDS;
    short ZEITFENSTERAUFTRAG;
    short ZEITANZPOSAUFTRAG;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    short UMKRUFWIEDERHOLUNG;
    short KABRUFWIEDERHOLUNG;
    short ANZRUFVERSCHIEBEN;
    short MINRUFVERSCHIEBEN;
    char CALLPLANSTARTSTOP[2];
    short STOPSTARTZEIT;
    long FETCH_REL;
    bool operator == (const N_MCALLPARAMATER& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            RUFZEITVERSCHIEBEN == right.RUFZEITVERSCHIEBEN &&
            ANZRUFWIEDERHOLUNG == right.ANZRUFWIEDERHOLUNG &&
            RUFABWEICHUNGPH == right.RUFABWEICHUNGPH &&
            RUFABWEICHUNGDP == right.RUFABWEICHUNGDP &&
            RUFABWEICHUNGDS == right.RUFABWEICHUNGDS &&
            ZEITFENSTERAUFTRAG == right.ZEITFENSTERAUFTRAG &&
            ZEITANZPOSAUFTRAG == right.ZEITANZPOSAUFTRAG &&
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME &&
            LOGINID == right.LOGINID &&
            !strcmp(CHANGEID, right.CHANGEID) &&
            UMKRUFWIEDERHOLUNG == right.UMKRUFWIEDERHOLUNG &&
            KABRUFWIEDERHOLUNG == right.KABRUFWIEDERHOLUNG &&
            ANZRUFVERSCHIEBEN == right.ANZRUFVERSCHIEBEN &&
            MINRUFVERSCHIEBEN == right.MINRUFVERSCHIEBEN &&
            !strcmp(CALLPLANSTARTSTOP, right.CALLPLANSTARTSTOP) &&
            STOPSTARTZEIT == right.STOPSTARTZEIT
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        RUFZEITVERSCHIEBEN = 0;
        ANZRUFWIEDERHOLUNG = 0;
        RUFABWEICHUNGPH = 0;
        RUFABWEICHUNGDP = 0;
        RUFABWEICHUNGDS = 0;
        ZEITFENSTERAUFTRAG = 0;
        ZEITANZPOSAUFTRAG = 0;
        TM_DATE = 0;
        TM_TIME = 0;
        LOGINID = 0;
        strcpy(CHANGEID, " " );
        UMKRUFWIEDERHOLUNG = 0;
        KABRUFWIEDERHOLUNG = 0;
        ANZRUFVERSCHIEBEN = 0;
        MINRUFVERSCHIEBEN = 0;
        strcpy(CALLPLANSTARTSTOP, " " );
        STOPSTARTZEIT = 0;
#endif
    }
} mcallparamaterS;
#endif /* TRANSCLASS */

/* original struct of MCALLPARAMTERTIMES **************************************/

#ifndef TRANSCLASS
typedef struct N_MCALLPARAMTERTIMES {
    short VERTRIEBSZENTRUMNR;
    short RUFABWEICHUNGPH;
    short RUFABWEICHUNGDP;
    short RUFABWEICHUNGDS;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    long FETCH_REL;
} mcallparamtertimesS;
#else /* TRANSCLASS */
typedef struct N_MCALLPARAMTERTIMES {
    short VERTRIEBSZENTRUMNR;
    short RUFABWEICHUNGPH;
    short RUFABWEICHUNGDP;
    short RUFABWEICHUNGDS;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    long FETCH_REL;
    bool operator == (const N_MCALLPARAMTERTIMES& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            RUFABWEICHUNGPH == right.RUFABWEICHUNGPH &&
            RUFABWEICHUNGDP == right.RUFABWEICHUNGDP &&
            RUFABWEICHUNGDS == right.RUFABWEICHUNGDS &&
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME &&
            LOGINID == right.LOGINID &&
            !strcmp(CHANGEID, right.CHANGEID)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        RUFABWEICHUNGPH = 0;
        RUFABWEICHUNGDP = 0;
        RUFABWEICHUNGDS = 0;
        TM_DATE = 0;
        TM_TIME = 0;
        LOGINID = 0;
        strcpy(CHANGEID, " " );
#endif
    }
} mcallparamtertimesS;
#endif /* TRANSCLASS */

/* original struct of MCALLPLANLOAD *******************************************/

#ifndef TRANSCLASS
typedef struct N_MCALLPLANLOAD {
    long LADEKIPPZEIT;
    short VERTRIEBSZENTRUMNR;
    long DATUM;
    char WOCHENTAG[3];
    long LADEDATUM;
    short LADEVZ;
    char BUNDESLAND[7];
    char TOURID[7];
    long LADEZEITAB;
    long LADEZEITBIS;
    long FETCH_REL;
} mcallplanloadS;
#else /* TRANSCLASS */
typedef struct N_MCALLPLANLOAD {
    long LADEKIPPZEIT;
    short VERTRIEBSZENTRUMNR;
    long DATUM;
    char WOCHENTAG[3];
    long LADEDATUM;
    short LADEVZ;
    char BUNDESLAND[7];
    char TOURID[7];
    long LADEZEITAB;
    long LADEZEITBIS;
    long FETCH_REL;
    bool operator == (const N_MCALLPLANLOAD& right) const {
        return (
            LADEKIPPZEIT == right.LADEKIPPZEIT &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            DATUM == right.DATUM &&
            !strcmp(WOCHENTAG, right.WOCHENTAG) &&
            LADEDATUM == right.LADEDATUM &&
            LADEVZ == right.LADEVZ &&
            !strcmp(BUNDESLAND, right.BUNDESLAND) &&
            !strcmp(TOURID, right.TOURID) &&
            LADEZEITAB == right.LADEZEITAB &&
            LADEZEITBIS == right.LADEZEITBIS
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        LADEKIPPZEIT = 0;
        VERTRIEBSZENTRUMNR = 0;
        DATUM = 0;
        strcpy(WOCHENTAG, " " );
        LADEDATUM = 0;
        LADEVZ = 0;
        strcpy(BUNDESLAND, " " );
        strcpy(TOURID, " " );
        LADEZEITAB = 0;
        LADEZEITBIS = 0;
#endif
    }
} mcallplanloadS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERCALLPLAN ***************************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERCALLPLAN {
    long IDFNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TAGNR[2];
    long URRUFZEIT;
    char RUFPROTOKOLL[2];
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG[2];
    char ANRUFTYP[2];
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    char TOURID[7];
    char SKDANRUFGENERELL[2];
    char BEMERKUNG[241];
    long FETCH_REL;
} mcustomercallplanS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERCALLPLAN {
    long IDFNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TAGNR[2];
    long URRUFZEIT;
    char RUFPROTOKOLL[2];
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG[2];
    char ANRUFTYP[2];
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    char TOURID[7];
    char SKDANRUFGENERELL[2];
    char BEMERKUNG[241];
    long FETCH_REL;
    bool operator == (const N_MCUSTOMERCALLPLAN& right) const {
        return (
            IDFNR == right.IDFNR &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(TAGNR, right.TAGNR) &&
            URRUFZEIT == right.URRUFZEIT &&
            !strcmp(RUFPROTOKOLL, right.RUFPROTOKOLL) &&
            RUFSTEUERUNG == right.RUFSTEUERUNG &&
            POOLNR == right.POOLNR &&
            MODEMPOOLNR == right.MODEMPOOLNR &&
            !strcmp(RUFEINSTELLUNG, right.RUFEINSTELLUNG) &&
            !strcmp(ANRUFTYP, right.ANRUFTYP) &&
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME &&
            LOGINID == right.LOGINID &&
            !strcmp(CHANGEID, right.CHANGEID) &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(SKDANRUFGENERELL, right.SKDANRUFGENERELL) &&
            !strcmp(BEMERKUNG, right.BEMERKUNG)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        IDFNR = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(TAGNR, " " );
        URRUFZEIT = 0;
        strcpy(RUFPROTOKOLL, " " );
        RUFSTEUERUNG = 0;
        POOLNR = 0;
        MODEMPOOLNR = 0;
        strcpy(RUFEINSTELLUNG, " " );
        strcpy(ANRUFTYP, " " );
        TM_DATE = 0;
        TM_TIME = 0;
        LOGINID = 0;
        strcpy(CHANGEID, " " );
        strcpy(TOURID, " " );
        strcpy(SKDANRUFGENERELL, " " );
        strcpy(BEMERKUNG, " " );
#endif
    }
} mcustomercallplanS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERCALLPLANPHONPROT *******************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERCALLPLANPHONPROT {
    long DATUM;
    long RUFZEIT;
    long IDFNR;
    long STATUS;
    long RUFZEITGEAENDERT;
    long ZEIT;
    long UID;
    char BEMERKUNG[241];
    short FILIALNR;
    long FETCH_REL;
} mcustomercallplanphonprotS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERCALLPLANPHONPROT {
    long DATUM;
    long RUFZEIT;
    long IDFNR;
    long STATUS;
    long RUFZEITGEAENDERT;
    long ZEIT;
    long UID;
    char BEMERKUNG[241];
    short FILIALNR;
    long FETCH_REL;
    bool operator == (const N_MCUSTOMERCALLPLANPHONPROT& right) const {
        return (
            DATUM == right.DATUM &&
            RUFZEIT == right.RUFZEIT &&
            IDFNR == right.IDFNR &&
            STATUS == right.STATUS &&
            RUFZEITGEAENDERT == right.RUFZEITGEAENDERT &&
            ZEIT == right.ZEIT &&
            UID == right.UID &&
            !strcmp(BEMERKUNG, right.BEMERKUNG) &&
            FILIALNR == right.FILIALNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUM = 0;
        RUFZEIT = 0;
        IDFNR = 0;
        STATUS = 0;
        RUFZEITGEAENDERT = 0;
        ZEIT = 0;
        UID = 0;
        strcpy(BEMERKUNG, " " );
        FILIALNR = 0;
#endif
    }
} mcustomercallplanphonprotS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERCALLPLANTOUR ***********************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERCALLPLANTOUR {
    long DATUMKOMMI;
    char ISTVERBUNDTOUR[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TOURID[7];
    short FILIALNR;
    short WEEKDAY;
    long FETCH_REL;
} mcustomercallplantourS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERCALLPLANTOUR {
    long DATUMKOMMI;
    char ISTVERBUNDTOUR[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TOURID[7];
    short FILIALNR;
    short WEEKDAY;
    long FETCH_REL;
    bool operator == (const N_MCUSTOMERCALLPLANTOUR& right) const {
        return (
            DATUMKOMMI == right.DATUMKOMMI &&
            !strcmp(ISTVERBUNDTOUR, right.ISTVERBUNDTOUR) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(TOURID, right.TOURID) &&
            FILIALNR == right.FILIALNR &&
            WEEKDAY == right.WEEKDAY
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        DATUMKOMMI = 0;
        strcpy(ISTVERBUNDTOUR, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(TOURID, " " );
        FILIALNR = 0;
        WEEKDAY = 0;
#endif
    }
} mcustomercallplantourS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERCALLPLANPHON ***********************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERCALLPLANPHON {
    short FILIALNR;
    long IDFNR;
    long DATUM;
    long RUFZEIT;
    short LFDAKTION;
    short PRIORITAET;
    char WOCHENTAG[3];
    short POOLID;
    char ANRUFART[3];
    char MANUELL[2];
    char STAGRUECKRUF[2];
    short ZUGRIFF;
    char CALLINFO[241];
} mcustomercallplanphonS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERCALLPLANPHON {
    short FILIALNR;
    long IDFNR;
    long DATUM;
    long RUFZEIT;
    short LFDAKTION;
    short PRIORITAET;
    char WOCHENTAG[3];
    short POOLID;
    char ANRUFART[3];
    char MANUELL[2];
    char STAGRUECKRUF[2];
    short ZUGRIFF;
    char CALLINFO[241];

    bool operator == (const N_MCUSTOMERCALLPLANPHON& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            IDFNR == right.IDFNR &&
            DATUM == right.DATUM &&
            RUFZEIT == right.RUFZEIT &&
            LFDAKTION == right.LFDAKTION &&
            PRIORITAET == right.PRIORITAET &&
            !strcmp(WOCHENTAG, right.WOCHENTAG) &&
            POOLID == right.POOLID &&
            !strcmp(ANRUFART, right.ANRUFART) &&
            !strcmp(MANUELL, right.MANUELL) &&
            !strcmp(STAGRUECKRUF, right.STAGRUECKRUF) &&
            ZUGRIFF == right.ZUGRIFF &&
            !strcmp(CALLINFO, right.CALLINFO)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        IDFNR = 0;
        DATUM = 0;
        RUFZEIT = 0;
        LFDAKTION = 0;
        PRIORITAET = 0;
        strcpy(WOCHENTAG, " " );
        POOLID = 0;
        strcpy(ANRUFART, " " );
        strcpy(MANUELL, " " );
        strcpy(STAGRUECKRUF, " " );
        ZUGRIFF = 0;
        strcpy(CALLINFO, " " );
#endif
    }
} mcustomercallplanphonS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERDISPLAY ****************************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERDISPLAY {
    long IDFNR;
    short FILIALNR;
    short ANREDEKZ;
    char NAMEAPO[41];
    char NAMEINHABER[31];
    char STRASSE[31];
    char ORT[31];
    char POSTLEITZAHL[11];
    char TELNR[21];
    char TELNRDAFUE[21];
    char TELKURZWAHL[5];
    char SKDKUNDEAEGESPERRT[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char SKDANRUFGENERELL[2];
} mcustomerdisplayS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERDISPLAY {
    long IDFNR;
    short FILIALNR;
    short ANREDEKZ;
    char NAMEAPO[41];
    char NAMEINHABER[31];
    char STRASSE[31];
    char ORT[31];
    char POSTLEITZAHL[11];
    char TELNR[21];
    char TELNRDAFUE[21];
    char TELKURZWAHL[5];
    char SKDKUNDEAEGESPERRT[2];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char SKDANRUFGENERELL[2];

    bool operator == (const N_MCUSTOMERDISPLAY& right) const {
        return (
            IDFNR == right.IDFNR &&
            FILIALNR == right.FILIALNR &&
            ANREDEKZ == right.ANREDEKZ &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(NAMEINHABER, right.NAMEINHABER) &&
            !strcmp(STRASSE, right.STRASSE) &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(POSTLEITZAHL, right.POSTLEITZAHL) &&
            !strcmp(TELNR, right.TELNR) &&
            !strcmp(TELNRDAFUE, right.TELNRDAFUE) &&
            !strcmp(TELKURZWAHL, right.TELKURZWAHL) &&
            !strcmp(SKDKUNDEAEGESPERRT, right.SKDKUNDEAEGESPERRT) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            !strcmp(SKDANRUFGENERELL, right.SKDANRUFGENERELL)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        IDFNR = 0;
        FILIALNR = 0;
        ANREDEKZ = 0;
        strcpy(NAMEAPO, " " );
        strcpy(NAMEINHABER, " " );
        strcpy(STRASSE, " " );
        strcpy(ORT, " " );
        strcpy(POSTLEITZAHL, " " );
        strcpy(TELNR, " " );
        strcpy(TELNRDAFUE, " " );
        strcpy(TELKURZWAHL, " " );
        strcpy(SKDKUNDEAEGESPERRT, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        strcpy(SKDANRUFGENERELL, " " );
#endif
    }
} mcustomerdisplayS;
#endif /* TRANSCLASS */

/* original struct of MDEVICEPLANMAINTENANCE **********************************/

#ifndef TRANSCLASS
typedef struct N_MDEVICEPLANMAINTENANCE {
    short REGIONENTYP;
    short FILIALNR;
    char GERAETEID[5];
    char GERAETEART[2];
    long GERAETNST;
    char GERAETEVERW1[2];
    char MODEMTYP[2];
    short VERTRIEBSZENTRUMNR;
    short UMKNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    char AKTIV[2];
    short UMKNST;
    long FETCH_REL;
} mdeviceplanmaintenanceS;
#else /* TRANSCLASS */
typedef struct N_MDEVICEPLANMAINTENANCE {
    short REGIONENTYP;
    short FILIALNR;
    char GERAETEID[5];
    char GERAETEART[2];
    long GERAETNST;
    char GERAETEVERW1[2];
    char MODEMTYP[2];
    short VERTRIEBSZENTRUMNR;
    short UMKNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    char AKTIV[2];
    short UMKNST;
    long FETCH_REL;
    bool operator == (const N_MDEVICEPLANMAINTENANCE& right) const {
        return (
            REGIONENTYP == right.REGIONENTYP &&
            FILIALNR == right.FILIALNR &&
            !strcmp(GERAETEID, right.GERAETEID) &&
            !strcmp(GERAETEART, right.GERAETEART) &&
            GERAETNST == right.GERAETNST &&
            !strcmp(GERAETEVERW1, right.GERAETEVERW1) &&
            !strcmp(MODEMTYP, right.MODEMTYP) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            UMKNR == right.UMKNR &&
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME &&
            LOGINID == right.LOGINID &&
            !strcmp(CHANGEID, right.CHANGEID) &&
            !strcmp(AKTIV, right.AKTIV) &&
            UMKNST == right.UMKNST
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REGIONENTYP = 0;
        FILIALNR = 0;
        strcpy(GERAETEID, " " );
        strcpy(GERAETEART, " " );
        GERAETNST = 0;
        strcpy(GERAETEVERW1, " " );
        strcpy(MODEMTYP, " " );
        VERTRIEBSZENTRUMNR = 0;
        UMKNR = 0;
        TM_DATE = 0;
        TM_TIME = 0;
        LOGINID = 0;
        strcpy(CHANGEID, " " );
        strcpy(AKTIV, " " );
        UMKNST = 0;
#endif
    }
} mdeviceplanmaintenanceS;
#endif /* TRANSCLASS */

/* original struct of MREGION *************************************************/

#ifndef TRANSCLASS
typedef struct N_MREGION {
    short REGIONENTYP;
    long REGIONNR;
    long REGIONTEILNR;
    char NAME[31];
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    long FETCH_REL;
} mregionS;
#else /* TRANSCLASS */
typedef struct N_MREGION {
    short REGIONENTYP;
    long REGIONNR;
    long REGIONTEILNR;
    char NAME[31];
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    long FETCH_REL;
    bool operator == (const N_MREGION& right) const {
        return (
            REGIONENTYP == right.REGIONENTYP &&
            REGIONNR == right.REGIONNR &&
            REGIONTEILNR == right.REGIONTEILNR &&
            !strcmp(NAME, right.NAME) &&
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME &&
            LOGINID == right.LOGINID &&
            !strcmp(CHANGEID, right.CHANGEID)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REGIONENTYP = 0;
        REGIONNR = 0;
        REGIONTEILNR = 0;
        strcpy(NAME, " " );
        TM_DATE = 0;
        TM_TIME = 0;
        LOGINID = 0;
        strcpy(CHANGEID, " " );
#endif
    }
} mregionS;
#endif /* TRANSCLASS */

/* original struct of MSALECENTER *********************************************/

#ifndef TRANSCLASS
typedef struct N_MSALECENTER {
    short FILIALNR;
    char NAME[31];
    long FETCH_REL;
} msalecenterS;
#else /* TRANSCLASS */
typedef struct N_MSALECENTER {
    short FILIALNR;
    char NAME[31];
    long FETCH_REL;
    bool operator == (const N_MSALECENTER& right) const {
        return (
            FILIALNR == right.FILIALNR &&
            !strcmp(NAME, right.NAME)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FILIALNR = 0;
        strcpy(NAME, " " );
#endif
    }
} msalecenterS;
#endif /* TRANSCLASS */

/* original struct of MUMKCONNECTION ******************************************/

#ifndef TRANSCLASS
typedef struct N_MUMKCONNECTION {
    short REGIONENTYP;
    long REGIONNR;
    short FILIALNR;
    short UMKNR;
    char RECHNERNAME[16];
    long PORTNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    long FETCH_REL;
} mumkconnectionS;
#else /* TRANSCLASS */
typedef struct N_MUMKCONNECTION {
    short REGIONENTYP;
    long REGIONNR;
    short FILIALNR;
    short UMKNR;
    char RECHNERNAME[16];
    long PORTNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID[2];
    long FETCH_REL;
    bool operator == (const N_MUMKCONNECTION& right) const {
        return (
            REGIONENTYP == right.REGIONENTYP &&
            REGIONNR == right.REGIONNR &&
            FILIALNR == right.FILIALNR &&
            UMKNR == right.UMKNR &&
            !strcmp(RECHNERNAME, right.RECHNERNAME) &&
            PORTNR == right.PORTNR &&
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME &&
            LOGINID == right.LOGINID &&
            !strcmp(CHANGEID, right.CHANGEID)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REGIONENTYP = 0;
        REGIONNR = 0;
        FILIALNR = 0;
        UMKNR = 0;
        strcpy(RECHNERNAME, " " );
        PORTNR = 0;
        TM_DATE = 0;
        TM_TIME = 0;
        LOGINID = 0;
        strcpy(CHANGEID, " " );
#endif
    }
} mumkconnectionS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of MCALLPARAMATER ******************************/

struct C_MCALLPARAMATER {
    short VERTRIEBSZENTRUMNR;
    short RUFZEITVERSCHIEBEN;
    short ANZRUFWIEDERHOLUNG;
    short RUFABWEICHUNGPH;
    short RUFABWEICHUNGDP;
    short RUFABWEICHUNGDS;
    short ZEITFENSTERAUFTRAG;
    short ZEITANZPOSAUFTRAG;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID;
    short UMKRUFWIEDERHOLUNG;
    short KABRUFWIEDERHOLUNG;
    short ANZRUFVERSCHIEBEN;
    short MINRUFVERSCHIEBEN;
    char CALLPLANSTARTSTOP;
    short STOPSTARTZEIT;
    long FETCH_REL;
};
/* Structur with real chartype of MCALLPARAMTERTIMES **************************/

struct C_MCALLPARAMTERTIMES {
    short VERTRIEBSZENTRUMNR;
    short RUFABWEICHUNGPH;
    short RUFABWEICHUNGDP;
    short RUFABWEICHUNGDS;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID;
    long FETCH_REL;
};
/* Structur with real chartype of MCALLPLANLOAD *******************************/

struct C_MCALLPLANLOAD {
    long LADEKIPPZEIT;
    short VERTRIEBSZENTRUMNR;
    long DATUM;
    char WOCHENTAG[3];
    long LADEDATUM;
    short LADEVZ;
    char BUNDESLAND[7];
    char TOURID[7];
    long LADEZEITAB;
    long LADEZEITBIS;
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMERCALLPLAN ***************************/

struct C_MCUSTOMERCALLPLAN {
    long IDFNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TAGNR;
    long URRUFZEIT;
    char RUFPROTOKOLL;
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG;
    char ANRUFTYP;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID;
    char TOURID[7];
    char SKDANRUFGENERELL;
    char BEMERKUNG[241];
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMERCALLPLANPHONPROT *******************/

struct C_MCUSTOMERCALLPLANPHONPROT {
    long DATUM;
    long RUFZEIT;
    long IDFNR;
    long STATUS;
    long RUFZEITGEAENDERT;
    long ZEIT;
    long UID;
    char BEMERKUNG[241];
    short FILIALNR;
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMERCALLPLANTOUR ***********************/

struct C_MCUSTOMERCALLPLANTOUR {
    long DATUMKOMMI;
    char ISTVERBUNDTOUR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char TOURID[7];
    short FILIALNR;
    short WEEKDAY;
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMERCALLPLANPHON ***********************/

struct C_MCUSTOMERCALLPLANPHON {
    short FILIALNR;
    long IDFNR;
    long DATUM;
    long RUFZEIT;
    short LFDAKTION;
    short PRIORITAET;
    char WOCHENTAG[3];
    short POOLID;
    char ANRUFART[3];
    char MANUELL;
    char STAGRUECKRUF;
    short ZUGRIFF;
    char CALLINFO[241];
};
/* Structur with real chartype of MCUSTOMERDISPLAY ****************************/

struct C_MCUSTOMERDISPLAY {
    long IDFNR;
    short FILIALNR;
    short ANREDEKZ;
    char NAMEAPO[41];
    char NAMEINHABER[31];
    char STRASSE[31];
    char ORT[31];
    char POSTLEITZAHL[11];
    char TELNR[21];
    char TELNRDAFUE[21];
    char TELKURZWAHL[5];
    char SKDKUNDEAEGESPERRT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    char SKDANRUFGENERELL;
};
/* Structur with real chartype of MDEVICEPLANMAINTENANCE **********************/

struct C_MDEVICEPLANMAINTENANCE {
    short REGIONENTYP;
    short FILIALNR;
    char GERAETEID[5];
    char GERAETEART;
    long GERAETNST;
    char GERAETEVERW1;
    char MODEMTYP;
    short VERTRIEBSZENTRUMNR;
    short UMKNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID;
    char AKTIV;
    short UMKNST;
    long FETCH_REL;
};
/* Structur with real chartype of MREGION *************************************/

struct C_MREGION {
    short REGIONENTYP;
    long REGIONNR;
    long REGIONTEILNR;
    char NAME[31];
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID;
    long FETCH_REL;
};
/* Structur with real chartype of MSALECENTER *********************************/

struct C_MSALECENTER {
    short FILIALNR;
    char NAME[31];
    long FETCH_REL;
};
/* Structur with real chartype of MUMKCONNECTION ******************************/

struct C_MUMKCONNECTION {
    short REGIONENTYP;
    long REGIONNR;
    short FILIALNR;
    short UMKNR;
    char RECHNERNAME[16];
    long PORTNR;
    long TM_DATE;
    long TM_TIME;
    long LOGINID;
    char CHANGEID;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of MCALLPARAMATER ****************************/

struct I_MCALLPARAMATER {
    short VERTRIEBSZENTRUMNR;
    short RUFZEITVERSCHIEBEN;
    short ANZRUFWIEDERHOLUNG;
    short RUFABWEICHUNGPH;
    short RUFABWEICHUNGDP;
    short RUFABWEICHUNGDS;
    short ZEITFENSTERAUFTRAG;
    short ZEITANZPOSAUFTRAG;
    short TM_DATE;
    short TM_TIME;
    short LOGINID;
    short CHANGEID;
    short UMKRUFWIEDERHOLUNG;
    short KABRUFWIEDERHOLUNG;
    short ANZRUFVERSCHIEBEN;
    short MINRUFVERSCHIEBEN;
    short CALLPLANSTARTSTOP;
    short STOPSTARTZEIT;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCALLPARAMTERTIMES ************************/

struct I_MCALLPARAMTERTIMES {
    short VERTRIEBSZENTRUMNR;
    short RUFABWEICHUNGPH;
    short RUFABWEICHUNGDP;
    short RUFABWEICHUNGDS;
    short TM_DATE;
    short TM_TIME;
    short LOGINID;
    short CHANGEID;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCALLPLANLOAD *****************************/

struct I_MCALLPLANLOAD {
    short LADEKIPPZEIT;
    short VERTRIEBSZENTRUMNR;
    short DATUM;
    short WOCHENTAG;
    short LADEDATUM;
    short LADEVZ;
    short BUNDESLAND;
    short TOURID;
    short LADEZEITAB;
    short LADEZEITBIS;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERCALLPLAN *************************/

struct I_MCUSTOMERCALLPLAN {
    short IDFNR;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short TAGNR;
    short URRUFZEIT;
    short RUFPROTOKOLL;
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    short RUFEINSTELLUNG;
    short ANRUFTYP;
    short TM_DATE;
    short TM_TIME;
    short LOGINID;
    short CHANGEID;
    short TOURID;
    short SKDANRUFGENERELL;
    short BEMERKUNG;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERCALLPLANPHONPROT *****************/

struct I_MCUSTOMERCALLPLANPHONPROT {
    short DATUM;
    short RUFZEIT;
    short IDFNR;
    short STATUS;
    short RUFZEITGEAENDERT;
    short ZEIT;
    short UID;
    short BEMERKUNG;
    short FILIALNR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERCALLPLANTOUR *********************/

struct I_MCUSTOMERCALLPLANTOUR {
    short DATUMKOMMI;
    short ISTVERBUNDTOUR;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short TOURID;
    short FILIALNR;
    short WEEKDAY;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERCALLPLANPHON *********************/

struct I_MCUSTOMERCALLPLANPHON {
    short FILIALNR;
    short IDFNR;
    short DATUM;
    short RUFZEIT;
    short LFDAKTION;
    short PRIORITAET;
    short WOCHENTAG;
    short POOLID;
    short ANRUFART;
    short MANUELL;
    short STAGRUECKRUF;
    short ZUGRIFF;
    short CALLINFO;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERDISPLAY **************************/

struct I_MCUSTOMERDISPLAY {
    short IDFNR;
    short FILIALNR;
    short ANREDEKZ;
    short NAMEAPO;
    short NAMEINHABER;
    short STRASSE;
    short ORT;
    short POSTLEITZAHL;
    short TELNR;
    short TELNRDAFUE;
    short TELKURZWAHL;
    short SKDKUNDEAEGESPERRT;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short SKDANRUFGENERELL;
};
/* Sizetype  Structur (buf_desc) of MDEVICEPLANMAINTENANCE ********************/

struct I_MDEVICEPLANMAINTENANCE {
    short REGIONENTYP;
    short FILIALNR;
    short GERAETEID;
    short GERAETEART;
    short GERAETNST;
    short GERAETEVERW1;
    short MODEMTYP;
    short VERTRIEBSZENTRUMNR;
    short UMKNR;
    short TM_DATE;
    short TM_TIME;
    short LOGINID;
    short CHANGEID;
    short AKTIV;
    short UMKNST;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MREGION ***********************************/

struct I_MREGION {
    short REGIONENTYP;
    short REGIONNR;
    short REGIONTEILNR;
    short NAME;
    short TM_DATE;
    short TM_TIME;
    short LOGINID;
    short CHANGEID;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MSALECENTER *******************************/

struct I_MSALECENTER {
    short FILIALNR;
    short NAME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MUMKCONNECTION ****************************/

struct I_MUMKCONNECTION {
    short REGIONENTYP;
    short REGIONNR;
    short FILIALNR;
    short UMKNR;
    short RECHNERNAME;
    short PORTNR;
    short TM_DATE;
    short TM_TIME;
    short LOGINID;
    short CHANGEID;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of MCALLPARAMATER **************************************/

#if defined (BUF_DESC)
static struct buf_desc MCALLPARAMATER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCALLPARAMATER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCALLPARAMTERTIMES **********************************/

#if defined (BUF_DESC)
static struct buf_desc MCALLPARAMTERTIMES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCALLPARAMTERTIMES_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCALLPLANLOAD ***************************************/

#if defined (BUF_DESC)
static struct buf_desc MCALLPLANLOAD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCALLPLANLOAD_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERCALLPLAN ***********************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLAN_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 240, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLAN_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 240, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERCALLPLANPHONPROT ***************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANPHONPROT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANPHONPROT_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERCALLPLANTOUR *******************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANTOUR_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANTOUR_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERCALLPLANPHON *******************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANPHON_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANPHON_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERDISPLAY ************************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERDISPLAY_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 4, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERDISPLAY_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 4, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
};
#endif

/* Structur (buf_desc) of MDEVICEPLANMAINTENANCE ******************************/

#if defined (BUF_DESC)
static struct buf_desc MDEVICEPLANMAINTENANCE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 4, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MDEVICEPLANMAINTENANCE_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 4, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MREGION *********************************************/

#if defined (BUF_DESC)
static struct buf_desc MREGION_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MREGION_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MSALECENTER *****************************************/

#if defined (BUF_DESC)
static struct buf_desc MSALECENTER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MSALECENTER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MUMKCONNECTION **************************************/

#if defined (BUF_DESC)
static struct buf_desc MUMKCONNECTION_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MUMKCONNECTION_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of MCallParamater ************************************/

#define MCALLPARAMATER_DELCALLPARAMETER 1070
#define MCALLPARAMATER_INSERT 1068
#define MCALLPARAMATER_SELCALLPARAMETER 1067
#define MCALLPARAMATER_SELLIST 1097
#define MCALLPARAMATER_UPDCALLPARAMETER 1069

/* FunctionNumber-Define of MCallParamterTimes ********************************/

#define MCALLPARAMTERTIMES_INSERT 1127
#define MCALLPARAMTERTIMES_SELPARAMETER 1125
#define MCALLPARAMTERTIMES_UPDPARAMETER 1126

/* FunctionNumber-Define of MCallPlanLoad *************************************/

#define MCALLPLANLOAD_AINCLUDEDUMMY 1772
#define MCALLPLANLOAD_DELCALLPLANLOAD 1109
#define MCALLPLANLOAD_DELCALLPLANLOADOLDER 1230
#define MCALLPLANLOAD_GETINITIALIZEDATA 1102
#define MCALLPLANLOAD_INSERT 1100
#define MCALLPLANLOAD_SELCALLPLANLOAD 1098
#define MCALLPLANLOAD_SELLIST 1274
#define MCALLPLANLOAD_UPDCALLPLANLOAD 1099

/* FunctionNumber-Define of MCustomerCallPlan *********************************/

#define MCUSTOMERCALLPLAN_DELALLCUSTOMERCALLPLAN 1079
#define MCUSTOMERCALLPLAN_DELALLWITHOUTSATURDAY 1082
#define MCUSTOMERCALLPLAN_DELCALLPLANCOMPLETLY 1247
#define MCUSTOMERCALLPLAN_DELCUSTOMERCALLPLAN 1063
#define MCUSTOMERCALLPLAN_INSERT 1062
#define MCUSTOMERCALLPLAN_INSERTALL 1076
#define MCUSTOMERCALLPLAN_INSERTALLWITHOUTSATURDAY 1080
#define MCUSTOMERCALLPLAN_SELALLDISABLED 1248
#define MCUSTOMERCALLPLAN_SELLIST 1060
#define MCUSTOMERCALLPLAN_SELLISTHIST 1186
#define MCUSTOMERCALLPLAN_SELLISTUNDERTAKE 1103
#define MCUSTOMERCALLPLAN_STARTBROWSEUNDERTAKE 1101
#define MCUSTOMERCALLPLAN_UPDALLCUSTOMERCALLPLAN 1078
#define MCUSTOMERCALLPLAN_UPDALLWITHOUTSATURDAY 1081
#define MCUSTOMERCALLPLAN_UPDCALLPLANDISABLE 1249
#define MCUSTOMERCALLPLAN_UPDCALLPLANENABLE 1250
#define MCUSTOMERCALLPLAN_UPDCUSTOMERCALLPLAN 1061
#define MCUSTOMERCALLPLAN_UPDTIMEALLCUSTOMERCALLPLAN 1210
#define MCUSTOMERCALLPLAN_UPDTIMEALLWITHOUTSATURDAY 1209
#define MCUSTOMERCALLPLAN_UPDTIMECUSTOMERCALLPLAN 1208

/* FunctionNumber-Define of MCustomerCallPlanPhonProt *************************/

#define MCUSTOMERCALLPLANPHONPROT_DELALL 1217
#define MCUSTOMERCALLPLANPHONPROT_DELALLOLDER 1225
#define MCUSTOMERCALLPLANPHONPROT_INSERT 1213

/* FunctionNumber-Define of MCustomerCallPlanTour *****************************/

#define MCUSTOMERCALLPLANTOUR_SELLIST 1253
#define MCUSTOMERCALLPLANTOUR_SELLISTHIST 1254

/* FunctionNumber-Define of MCustomerCallplanPhon *****************************/

#define MCUSTOMERCALLPLANPHON_DELALL 1216
#define MCUSTOMERCALLPLANPHON_DELALLOLDER 1224
#define MCUSTOMERCALLPLANPHON_INSERT 1212

/* FunctionNumber-Define of MCustomerDisplay **********************************/

#define MCUSTOMERDISPLAY_SELCUSTOMER 1075
#define MCUSTOMERDISPLAY_UPDPROPERTIES 1255
#define MCUSTOMERDISPLAY_UPDTELNO 1241

/* FunctionNumber-Define of MDevicePlanMaintenance ****************************/

#define MDEVICEPLANMAINTENANCE_DELETE 1114
#define MDEVICEPLANMAINTENANCE_INSERTDEVICE 1191
#define MDEVICEPLANMAINTENANCE_SELDEVICEPLANUNI 1115
#define MDEVICEPLANMAINTENANCE_SELLIST 1111
#define MDEVICEPLANMAINTENANCE_SELNST 1192
#define MDEVICEPLANMAINTENANCE_UPDDEVICEPLAN 1112
#define MDEVICEPLANMAINTENANCE_UPDSALECENTERNO 1120

/* FunctionNumber-Define of MRegion *******************************************/

#define MREGION_DELREGION 1180
#define MREGION_INSERT 1181
#define MREGION_SELLIST 1173
#define MREGION_SELREGION 1361

/* FunctionNumber-Define of MSaleCenter ***************************************/

#define MSALECENTER_SELLIST 1178
#define MSALECENTER_SELSALECENTER 1179

/* FunctionNumber-Define of MUmkConnection ************************************/

#define MUMKCONNECTION_DELUMKCONNECTION 1171
#define MUMKCONNECTION_INSERT 1169
#define MUMKCONNECTION_SELLIST 1129
#define MUMKCONNECTION_SELUMKCONNECTION 1160
#define MUMKCONNECTION_UPDUMKCONNECTION 1170
#define MUMKCONNECTION_WRITELOG 1161

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of MCallParamater ********************************/

#define DelCallParameter 1070
#define Insert 1068
#define SelCallParameter 1067
#define SelList 1097
#define UpdCallparameter 1069

/* Old-FunctionNumber-Define of MCallParamterTimes ****************************/

#define Insert 1127
#define SelParameter 1125
#define UpdParameter 1126

/* Old-FunctionNumber-Define of MCallPlanLoad *********************************/

#define AIncludeDummy 1772
#define DelCallPlanLoad 1109
#define DelCallPlanLoadOlder 1230
#define GetInitializeData 1102
#define Insert 1100
#define SelCallPlanLoad 1098
#define SelList 1274
#define UpdCallPlanLoad 1099

/* Old-FunctionNumber-Define of MCustomerCallPlan *****************************/

#define DelAllCustomerCallPlan 1079
#define DelAllWithoutSaturday 1082
#define DelCallPlanCompletly 1247
#define DelCustomerCallPlan 1063
#define Insert 1062
#define InsertAll 1076
#define InsertAllWithoutSaturday 1080
#define SelAllDisabled 1248
#define SelList 1060
#define SelListHist 1186
#define SelListUndertake 1103
#define StartBrowseUndertake 1101
#define UpdAllCustomerCallPlan 1078
#define UpdAllWithoutSaturday 1081
#define UpdCallPlanDisable 1249
#define UpdCallPlanEnable 1250
#define UpdCustomerCallPlan 1061
#define UpdTimeAllCustomerCallPlan 1210
#define UpdTimeAllWithoutSaturday 1209
#define UpdTimeCustomerCallPlan 1208

/* Old-FunctionNumber-Define of MCustomerCallPlanPhonProt *********************/

#define DelAll 1217
#define DelAllOlder 1225
#define Insert 1213

/* Old-FunctionNumber-Define of MCustomerCallPlanTour *************************/

#define SelList 1253
#define SelListHist 1254

/* Old-FunctionNumber-Define of MCustomerCallplanPhon *************************/

#define DelAll 1216
#define DelAllOlder 1224
#define Insert 1212

/* Old-FunctionNumber-Define of MCustomerDisplay ******************************/

#define SelCustomer 1075
#define UpdProperties 1255
#define UpdTelNo 1241

/* Old-FunctionNumber-Define of MDevicePlanMaintenance ************************/

#define Delete 1114
#define InsertDevice 1191
#define SelDevicePlanUni 1115
#define SelList 1111
#define SelNst 1192
#define UpdDevicePlan 1112
#define UpdSaleCenterNo 1120

/* Old-FunctionNumber-Define of MRegion ***************************************/

#define DelRegion 1180
#define Insert 1181
#define SelList 1173
#define SelRegion 1361

/* Old-FunctionNumber-Define of MSaleCenter ***********************************/

#define SelList 1178
#define SelSaleCenter 1179

/* Old-FunctionNumber-Define of MUmkConnection ********************************/

#define DelUmkConnection 1171
#define Insert 1169
#define SelList 1129
#define SelUmkConnection 1160
#define UpdUmkConnection 1170
#define WriteLog 1161

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

class CMCALLPARAMATER : public ppDadeVirtual {
public:
    mcallparamaterS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcallparamaterS> lst; // class list

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
                     vector< mcallparamaterS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcallparamaterS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcallparamaterS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcallparamaterS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcallparamaterS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    short        GetRufzeitverschieben() const { return s.RUFZEITVERSCHIEBEN; }
    short        GetAnzrufwiederholung() const { return s.ANZRUFWIEDERHOLUNG; }
    short        GetRufabweichungph() const { return s.RUFABWEICHUNGPH; }
    short        GetRufabweichungdp() const { return s.RUFABWEICHUNGDP; }
    short        GetRufabweichungds() const { return s.RUFABWEICHUNGDS; }
    short        GetZeitfensterauftrag() const { return s.ZEITFENSTERAUFTRAG; }
    short        GetZeitanzposauftrag() const { return s.ZEITANZPOSAUFTRAG; }
    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }
    long         GetLoginid() const { return s.LOGINID; }
    char         GetChangeid() const { return s.CHANGEID[0]; }
    short        GetUmkrufwiederholung() const { return s.UMKRUFWIEDERHOLUNG; }
    short        GetKabrufwiederholung() const { return s.KABRUFWIEDERHOLUNG; }
    short        GetAnzrufverschieben() const { return s.ANZRUFVERSCHIEBEN; }
    short        GetMinrufverschieben() const { return s.MINRUFVERSCHIEBEN; }
    char         GetCallplanstartstop() const { return s.CALLPLANSTARTSTOP[0]; }
    short        GetStopstartzeit() const { return s.STOPSTARTZEIT; }

    const mcallparamaterS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetRufzeitverschieben(short t) { s.RUFZEITVERSCHIEBEN = t; }
    void         SetAnzrufwiederholung(short t) { s.ANZRUFWIEDERHOLUNG = t; }
    void         SetRufabweichungph(short t) { s.RUFABWEICHUNGPH = t; }
    void         SetRufabweichungdp(short t) { s.RUFABWEICHUNGDP = t; }
    void         SetRufabweichungds(short t) { s.RUFABWEICHUNGDS = t; }
    void         SetZeitfensterauftrag(short t) { s.ZEITFENSTERAUFTRAG = t; }
    void         SetZeitanzposauftrag(short t) { s.ZEITANZPOSAUFTRAG = t; }
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }
    void         SetLoginid(long t) { s.LOGINID = t; }
    void         SetChangeid(char t) { s.CHANGEID[0] = t; s.CHANGEID[1] = '\0';}
    void         SetUmkrufwiederholung(short t) { s.UMKRUFWIEDERHOLUNG = t; }
    void         SetKabrufwiederholung(short t) { s.KABRUFWIEDERHOLUNG = t; }
    void         SetAnzrufverschieben(short t) { s.ANZRUFVERSCHIEBEN = t; }
    void         SetMinrufverschieben(short t) { s.MINRUFVERSCHIEBEN = t; }
    void         SetCallplanstartstop(char t) { s.CALLPLANSTARTSTOP[0] = t; s.CALLPLANSTARTSTOP[1] = '\0';}
    void         SetStopstartzeit(short t) { s.STOPSTARTZEIT = t; }

    void         SetStruct(const mcallparamaterS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DelCallParameter(int pos = 0) { return UniqueServerCall(1070, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1068, pos); Strip(s); return ret; }
    int          SelCallParameter(int pos = 0) { int ret = UniqueServerCall(1067, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1097, FetchRel, pos); return ret; }
    int          UpdCallparameter(int pos = 0) { int ret = UniqueServerCall(1069, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCALLPARAMATER() {
        ::buf_default((void *)&s, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCALLPARAMATER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCALLPARAMATER_BES, MCALLPARAMATER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPARAMATER_BES, (int)MCALLPARAMATER_ANZ, error_msg);
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
        if ( fkt_nr == 1070 ) return UniqueServerCall(1070, pos);
        if ( fkt_nr == 1068 ) return UniqueServerCall(1068, pos);
        if ( fkt_nr == 1067 ) return UniqueServerCall(1067, pos);
        if ( fkt_nr == 1097 ) return CursorServerCall(1097, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1069 ) return UniqueServerCall(1069, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCALLPARAMATER & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCALLPARAMATER_BES, (int)MCALLPARAMATER_ANZ, error_msg);
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
        CMCALLPARAMATER c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPARAMATER_BES, (int)MCALLPARAMATER_ANZ, error_msg);
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

class CMCALLPARAMTERTIMES : public ppDadeVirtual {
public:
    mcallparamtertimesS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcallparamtertimesS> lst; // class list

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
                     vector< mcallparamtertimesS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcallparamtertimesS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcallparamtertimesS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcallparamtertimesS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcallparamtertimesS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    short        GetRufabweichungph() const { return s.RUFABWEICHUNGPH; }
    short        GetRufabweichungdp() const { return s.RUFABWEICHUNGDP; }
    short        GetRufabweichungds() const { return s.RUFABWEICHUNGDS; }
    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }
    long         GetLoginid() const { return s.LOGINID; }
    char         GetChangeid() const { return s.CHANGEID[0]; }

    const mcallparamtertimesS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetRufabweichungph(short t) { s.RUFABWEICHUNGPH = t; }
    void         SetRufabweichungdp(short t) { s.RUFABWEICHUNGDP = t; }
    void         SetRufabweichungds(short t) { s.RUFABWEICHUNGDS = t; }
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }
    void         SetLoginid(long t) { s.LOGINID = t; }
    void         SetChangeid(char t) { s.CHANGEID[0] = t; s.CHANGEID[1] = '\0';}

    void         SetStruct(const mcallparamtertimesS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Insert(int pos = 0) { int ret = UniqueServerCall(1127, pos); Strip(s); return ret; }
    int          SelParameter(int pos = 0) { int ret = UniqueServerCall(1125, pos); Strip(s); return ret; }
    int          UpdParameter(int pos = 0) { int ret = UniqueServerCall(1126, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCALLPARAMTERTIMES() {
        ::buf_default((void *)&s, MCALLPARAMTERTIMES_BES, MCALLPARAMTERTIMES_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCALLPARAMTERTIMES() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCALLPARAMTERTIMES_BES, MCALLPARAMTERTIMES_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPARAMTERTIMES_BES, (int)MCALLPARAMTERTIMES_ANZ, error_msg);
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
        if ( fkt_nr == 1127 ) return UniqueServerCall(1127, pos);
        if ( fkt_nr == 1125 ) return UniqueServerCall(1125, pos);
        if ( fkt_nr == 1126 ) return UniqueServerCall(1126, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCALLPARAMTERTIMES & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCALLPARAMTERTIMES_BES, (int)MCALLPARAMTERTIMES_ANZ, error_msg);
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
        CMCALLPARAMTERTIMES c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPARAMTERTIMES_BES, (int)MCALLPARAMTERTIMES_ANZ, error_msg);
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

class CMCALLPLANLOAD : public ppDadeVirtual {
public:
    mcallplanloadS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcallplanloadS> lst; // class list

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
                     vector< mcallplanloadS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcallplanloadS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcallplanloadS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcallplanloadS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcallplanloadS>::iterator
                 endList  () { return lst.end  (); }

    long         GetLadekippzeit() const { return s.LADEKIPPZEIT; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetDatum() const { return s.DATUM; }
    const char*  GetWochentag(ppString & t) const { t = s.WOCHENTAG; t.erasespace(ppString::END); return t.c_str(); }
    long         GetLadedatum() const { return s.LADEDATUM; }
    short        GetLadevz() const { return s.LADEVZ; }
    const char*  GetBundesland(ppString & t) const { t = s.BUNDESLAND; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetLadezeitab() const { return s.LADEZEITAB; }
    long         GetLadezeitbis() const { return s.LADEZEITBIS; }

    const mcallplanloadS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetLadekippzeit(long t) { s.LADEKIPPZEIT = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetWochentag(const ppString & t) { ppGStrCopy(s.WOCHENTAG, t.c_str(), L_MCALLPLANLOAD_WOCHENTAG); }
    void         SetLadedatum(long t) { s.LADEDATUM = t; }
    void         SetLadevz(short t) { s.LADEVZ = t; }
    void         SetBundesland(const ppString & t) { ppGStrCopy(s.BUNDESLAND, t.c_str(), L_MCALLPLANLOAD_BUNDESLAND); }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_MCALLPLANLOAD_TOURID); }
    void         SetLadezeitab(long t) { s.LADEZEITAB = t; }
    void         SetLadezeitbis(long t) { s.LADEZEITBIS = t; }

    void         SetStruct(const mcallplanloadS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          AIncludeDummy(int pos = 0) { int ret = UniqueServerCall(1772, pos); Strip(s); return ret; }
    int          DelCallPlanLoad(int pos = 0) { return UniqueServerCall(1109, pos); }
    int          DelCallPlanLoadOlder(int pos = 0) { return UniqueServerCall(1230, pos); }
    int          GetInitializeData(int pos = 0) { int ret = UniqueServerCall(1102, pos); Strip(s); return ret; }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1100, pos); Strip(s); return ret; }
    int          SelCallPlanLoad(int pos = 0) { int ret = UniqueServerCall(1098, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1274, FetchRel, pos); return ret; }
    int          UpdCallPlanLoad(int pos = 0) { int ret = UniqueServerCall(1099, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCALLPLANLOAD() {
        ::buf_default((void *)&s, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCALLPLANLOAD() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCALLPLANLOAD_BES, MCALLPLANLOAD_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPLANLOAD_BES, (int)MCALLPLANLOAD_ANZ, error_msg);
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
        if ( fkt_nr == 1772 ) return UniqueServerCall(1772, pos);
        if ( fkt_nr == 1109 ) return UniqueServerCall(1109, pos);
        if ( fkt_nr == 1230 ) return UniqueServerCall(1230, pos);
        if ( fkt_nr == 1102 ) return UniqueServerCall(1102, pos);
        if ( fkt_nr == 1100 ) return UniqueServerCall(1100, pos);
        if ( fkt_nr == 1098 ) return UniqueServerCall(1098, pos);
        if ( fkt_nr == 1274 ) return CursorServerCall(1274, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1099 ) return UniqueServerCall(1099, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCALLPLANLOAD & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.WOCHENTAG);
        ppGStripLast(d.BUNDESLAND);
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCALLPLANLOAD_BES, (int)MCALLPLANLOAD_ANZ, error_msg);
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
        CMCALLPLANLOAD c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPLANLOAD_BES, (int)MCALLPLANLOAD_ANZ, error_msg);
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

class CMCUSTOMERCALLPLAN : public ppDadeVirtual {
public:
    mcustomercallplanS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomercallplanS> lst; // class list

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
                     vector< mcustomercallplanS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomercallplanS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomercallplanS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomercallplanS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomercallplanS>::iterator
                 endList  () { return lst.end  (); }

    long         GetIdfnr() const { return s.IDFNR; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    char         GetTagnr() const { return s.TAGNR[0]; }
    long         GetUrrufzeit() const { return s.URRUFZEIT; }
    char         GetRufprotokoll() const { return s.RUFPROTOKOLL[0]; }
    short        GetRufsteuerung() const { return s.RUFSTEUERUNG; }
    short        GetPoolnr() const { return s.POOLNR; }
    short        GetModempoolnr() const { return s.MODEMPOOLNR; }
    char         GetRufeinstellung() const { return s.RUFEINSTELLUNG[0]; }
    char         GetAnruftyp() const { return s.ANRUFTYP[0]; }
    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }
    long         GetLoginid() const { return s.LOGINID; }
    char         GetChangeid() const { return s.CHANGEID[0]; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    char         GetSkdanrufgenerell() const { return s.SKDANRUFGENERELL[0]; }
    const char*  GetBemerkung(ppString & t) const { t = s.BEMERKUNG; t.erasespace(ppString::END); return t.c_str(); }

    const mcustomercallplanS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetTagnr(char t) { s.TAGNR[0] = t; s.TAGNR[1] = '\0';}
    void         SetUrrufzeit(long t) { s.URRUFZEIT = t; }
    void         SetRufprotokoll(char t) { s.RUFPROTOKOLL[0] = t; s.RUFPROTOKOLL[1] = '\0';}
    void         SetRufsteuerung(short t) { s.RUFSTEUERUNG = t; }
    void         SetPoolnr(short t) { s.POOLNR = t; }
    void         SetModempoolnr(short t) { s.MODEMPOOLNR = t; }
    void         SetRufeinstellung(char t) { s.RUFEINSTELLUNG[0] = t; s.RUFEINSTELLUNG[1] = '\0';}
    void         SetAnruftyp(char t) { s.ANRUFTYP[0] = t; s.ANRUFTYP[1] = '\0';}
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }
    void         SetLoginid(long t) { s.LOGINID = t; }
    void         SetChangeid(char t) { s.CHANGEID[0] = t; s.CHANGEID[1] = '\0';}
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_MCUSTOMERCALLPLAN_TOURID); }
    void         SetSkdanrufgenerell(char t) { s.SKDANRUFGENERELL[0] = t; s.SKDANRUFGENERELL[1] = '\0';}
    void         SetBemerkung(const ppString & t) { ppGStrCopy(s.BEMERKUNG, t.c_str(), L_MCUSTOMERCALLPLAN_BEMERKUNG); }

    void         SetStruct(const mcustomercallplanS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DelAllCustomerCallPlan(int pos = 0) { return UniqueServerCall(1079, pos); }
    int          DelAllWithoutSaturday(int pos = 0) { return UniqueServerCall(1082, pos); }
    int          DelCallPlanCompletly(int pos = 0) { return UniqueServerCall(1247, pos); }
    int          DelCustomerCallPlan(int pos = 0) { return UniqueServerCall(1063, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1062, pos); Strip(s); return ret; }
    int          InsertAll(int pos = 0) { int ret = UniqueServerCall(1076, pos); Strip(s); return ret; }
    int          InsertAllWithoutSaturday(int pos = 0) { int ret = UniqueServerCall(1080, pos); Strip(s); return ret; }
    int          SelAllDisabled(int pos = 0) { int ret = UniqueServerCall(1248, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1060, FetchRel, pos); return ret; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1186, FetchRel, pos); return ret; }
    int          SelListUndertake(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1103, FetchRel, pos); return ret; }
    int          StartBrowseUndertake(int pos = 0) { int ret = UniqueServerCall(1101, pos); Strip(s); return ret; }
    int          UpdAllCustomerCallPlan(int pos = 0) { int ret = UniqueServerCall(1078, pos); Strip(s); return ret; }
    int          UpdAllWithoutSaturday(int pos = 0) { int ret = UniqueServerCall(1081, pos); Strip(s); return ret; }
    int          UpdCallPlanDisable(int pos = 0) { int ret = UniqueServerCall(1249, pos); Strip(s); return ret; }
    int          UpdCallPlanEnable(int pos = 0) { int ret = UniqueServerCall(1250, pos); Strip(s); return ret; }
    int          UpdCustomerCallPlan(int pos = 0) { int ret = UniqueServerCall(1061, pos); Strip(s); return ret; }
    int          UpdTimeAllCustomerCallPlan(int pos = 0) { int ret = UniqueServerCall(1210, pos); Strip(s); return ret; }
    int          UpdTimeAllWithoutSaturday(int pos = 0) { int ret = UniqueServerCall(1209, pos); Strip(s); return ret; }
    int          UpdTimeCustomerCallPlan(int pos = 0) { int ret = UniqueServerCall(1208, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERCALLPLAN() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERCALLPLAN() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLAN_BES, MCUSTOMERCALLPLAN_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLAN_BES, (int)MCUSTOMERCALLPLAN_ANZ, error_msg);
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
        if ( fkt_nr == 1079 ) return UniqueServerCall(1079, pos);
        if ( fkt_nr == 1082 ) return UniqueServerCall(1082, pos);
        if ( fkt_nr == 1247 ) return UniqueServerCall(1247, pos);
        if ( fkt_nr == 1063 ) return UniqueServerCall(1063, pos);
        if ( fkt_nr == 1062 ) return UniqueServerCall(1062, pos);
        if ( fkt_nr == 1076 ) return UniqueServerCall(1076, pos);
        if ( fkt_nr == 1080 ) return UniqueServerCall(1080, pos);
        if ( fkt_nr == 1248 ) return UniqueServerCall(1248, pos);
        if ( fkt_nr == 1060 ) return CursorServerCall(1060, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1186 ) return CursorServerCall(1186, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1103 ) return CursorServerCall(1103, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1101 ) return UniqueServerCall(1101, pos);
        if ( fkt_nr == 1078 ) return UniqueServerCall(1078, pos);
        if ( fkt_nr == 1081 ) return UniqueServerCall(1081, pos);
        if ( fkt_nr == 1249 ) return UniqueServerCall(1249, pos);
        if ( fkt_nr == 1250 ) return UniqueServerCall(1250, pos);
        if ( fkt_nr == 1061 ) return UniqueServerCall(1061, pos);
        if ( fkt_nr == 1210 ) return UniqueServerCall(1210, pos);
        if ( fkt_nr == 1209 ) return UniqueServerCall(1209, pos);
        if ( fkt_nr == 1208 ) return UniqueServerCall(1208, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERCALLPLAN & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.BEMERKUNG);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERCALLPLAN_BES, (int)MCUSTOMERCALLPLAN_ANZ, error_msg);
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
        CMCUSTOMERCALLPLAN c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLAN_BES, (int)MCUSTOMERCALLPLAN_ANZ, error_msg);
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

class CMCUSTOMERCALLPLANPHONPROT : public ppDadeVirtual {
public:
    mcustomercallplanphonprotS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomercallplanphonprotS> lst; // class list

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
                     vector< mcustomercallplanphonprotS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomercallplanphonprotS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomercallplanphonprotS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomercallplanphonprotS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomercallplanphonprotS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatum() const { return s.DATUM; }
    long         GetRufzeit() const { return s.RUFZEIT; }
    long         GetIdfnr() const { return s.IDFNR; }
    long         GetStatus() const { return s.STATUS; }
    long         GetRufzeitgeaendert() const { return s.RUFZEITGEAENDERT; }
    long         GetZeit() const { return s.ZEIT; }
    long         GetUid() const { return s.UID; }
    const char*  GetBemerkung(ppString & t) const { t = s.BEMERKUNG; t.erasespace(ppString::END); return t.c_str(); }
    short        GetFilialnr() const { return s.FILIALNR; }

    const mcustomercallplanphonprotS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetDatum(long t) { s.DATUM = t; }
    void         SetRufzeit(long t) { s.RUFZEIT = t; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetStatus(long t) { s.STATUS = t; }
    void         SetRufzeitgeaendert(long t) { s.RUFZEITGEAENDERT = t; }
    void         SetZeit(long t) { s.ZEIT = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetBemerkung(const ppString & t) { ppGStrCopy(s.BEMERKUNG, t.c_str(), L_MCUSTOMERCALLPLANPHONPROT_BEMERKUNG); }
    void         SetFilialnr(short t) { s.FILIALNR = t; }

    void         SetStruct(const mcustomercallplanphonprotS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DelAll(int pos = 0) { return UniqueServerCall(1217, pos); }
    int          DelAllOlder(int pos = 0) { return UniqueServerCall(1225, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1213, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERCALLPLANPHONPROT() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANPHONPROT_BES, MCUSTOMERCALLPLANPHONPROT_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERCALLPLANPHONPROT() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANPHONPROT_BES, MCUSTOMERCALLPLANPHONPROT_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANPHONPROT_BES, (int)MCUSTOMERCALLPLANPHONPROT_ANZ, error_msg);
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
        if ( fkt_nr == 1217 ) return UniqueServerCall(1217, pos);
        if ( fkt_nr == 1225 ) return UniqueServerCall(1225, pos);
        if ( fkt_nr == 1213 ) return UniqueServerCall(1213, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERCALLPLANPHONPROT & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.BEMERKUNG);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERCALLPLANPHONPROT_BES, (int)MCUSTOMERCALLPLANPHONPROT_ANZ, error_msg);
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
        CMCUSTOMERCALLPLANPHONPROT c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANPHONPROT_BES, (int)MCUSTOMERCALLPLANPHONPROT_ANZ, error_msg);
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

class CMCUSTOMERCALLPLANTOUR : public ppDadeVirtual {
public:
    mcustomercallplantourS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomercallplantourS> lst; // class list

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
                     vector< mcustomercallplantourS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomercallplantourS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomercallplantourS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomercallplantourS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomercallplantourS>::iterator
                 endList  () { return lst.end  (); }

    long         GetDatumkommi() const { return s.DATUMKOMMI; }
    char         GetIstverbundtour() const { return s.ISTVERBUNDTOUR[0]; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetWeekday() const { return s.WEEKDAY; }

    const mcustomercallplantourS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetDatumkommi(long t) { s.DATUMKOMMI = t; }
    void         SetIstverbundtour(char t) { s.ISTVERBUNDTOUR[0] = t; s.ISTVERBUNDTOUR[1] = '\0';}
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_MCUSTOMERCALLPLANTOUR_TOURID); }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }

    void         SetStruct(const mcustomercallplantourS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1253, FetchRel, pos); return ret; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1254, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERCALLPLANTOUR() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANTOUR_BES, MCUSTOMERCALLPLANTOUR_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERCALLPLANTOUR() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANTOUR_BES, MCUSTOMERCALLPLANTOUR_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANTOUR_BES, (int)MCUSTOMERCALLPLANTOUR_ANZ, error_msg);
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
        if ( fkt_nr == 1253 ) return CursorServerCall(1253, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1254 ) return CursorServerCall(1254, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERCALLPLANTOUR & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERCALLPLANTOUR_BES, (int)MCUSTOMERCALLPLANTOUR_ANZ, error_msg);
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
        CMCUSTOMERCALLPLANTOUR c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANTOUR_BES, (int)MCUSTOMERCALLPLANTOUR_ANZ, error_msg);
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

class CMCUSTOMERCALLPLANPHON : public ppDadeVirtual {
public:
    mcustomercallplanphonS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomercallplanphonS> lst; // class list

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
                     vector< mcustomercallplanphonS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomercallplanphonS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomercallplanphonS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomercallplanphonS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomercallplanphonS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetIdfnr() const { return s.IDFNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetRufzeit() const { return s.RUFZEIT; }
    short        GetLfdaktion() const { return s.LFDAKTION; }
    short        GetPrioritaet() const { return s.PRIORITAET; }
    const char*  GetWochentag(ppString & t) const { t = s.WOCHENTAG; t.erasespace(ppString::END); return t.c_str(); }
    short        GetPoolid() const { return s.POOLID; }
    const char*  GetAnrufart(ppString & t) const { t = s.ANRUFART; t.erasespace(ppString::END); return t.c_str(); }
    char         GetManuell() const { return s.MANUELL[0]; }
    char         GetStagrueckruf() const { return s.STAGRUECKRUF[0]; }
    short        GetZugriff() const { return s.ZUGRIFF; }
    const char*  GetCallinfo(ppString & t) const { t = s.CALLINFO; t.erasespace(ppString::END); return t.c_str(); }

    const mcustomercallplanphonS &
                 GetStruct() const { return s; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetRufzeit(long t) { s.RUFZEIT = t; }
    void         SetLfdaktion(short t) { s.LFDAKTION = t; }
    void         SetPrioritaet(short t) { s.PRIORITAET = t; }
    void         SetWochentag(const ppString & t) { ppGStrCopy(s.WOCHENTAG, t.c_str(), L_MCUSTOMERCALLPLANPHON_WOCHENTAG); }
    void         SetPoolid(short t) { s.POOLID = t; }
    void         SetAnrufart(const ppString & t) { ppGStrCopy(s.ANRUFART, t.c_str(), L_MCUSTOMERCALLPLANPHON_ANRUFART); }
    void         SetManuell(char t) { s.MANUELL[0] = t; s.MANUELL[1] = '\0';}
    void         SetStagrueckruf(char t) { s.STAGRUECKRUF[0] = t; s.STAGRUECKRUF[1] = '\0';}
    void         SetZugriff(short t) { s.ZUGRIFF = t; }
    void         SetCallinfo(const ppString & t) { ppGStrCopy(s.CALLINFO, t.c_str(), L_MCUSTOMERCALLPLANPHON_CALLINFO); }

    void         SetStruct(const mcustomercallplanphonS & t) { s = t; }

    int          DelAll(int pos = 0) { return UniqueServerCall(1216, pos); }
    int          DelAllOlder(int pos = 0) { return UniqueServerCall(1224, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1212, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERCALLPLANPHON() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANPHON_BES, MCUSTOMERCALLPLANPHON_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERCALLPLANPHON() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANPHON_BES, MCUSTOMERCALLPLANPHON_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1216 ) return UniqueServerCall(1216, pos);
        if ( fkt_nr == 1224 ) return UniqueServerCall(1224, pos);
        if ( fkt_nr == 1212 ) return UniqueServerCall(1212, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERCALLPLANPHON & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.WOCHENTAG);
        ppGStripLast(d.ANRUFART);
        ppGStripLast(d.CALLINFO);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERCALLPLANPHON_BES, (int)MCUSTOMERCALLPLANPHON_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CMCUSTOMERDISPLAY : public ppDadeVirtual {
public:
    mcustomerdisplayS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomerdisplayS> lst; // class list

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
                     vector< mcustomerdisplayS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomerdisplayS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomerdisplayS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomerdisplayS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomerdisplayS>::iterator
                 endList  () { return lst.end  (); }

    long         GetIdfnr() const { return s.IDFNR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetAnredekz() const { return s.ANREDEKZ; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetNameinhaber(ppString & t) const { t = s.NAMEINHABER; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStrasse(ppString & t) const { t = s.STRASSE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetPostleitzahl(ppString & t) const { t = s.POSTLEITZAHL; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelnr(ppString & t) const { t = s.TELNR; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelnrdafue(ppString & t) const { t = s.TELNRDAFUE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelkurzwahl(ppString & t) const { t = s.TELKURZWAHL; t.erasespace(ppString::END); return t.c_str(); }
    char         GetSkdkundeaegesperrt() const { return s.SKDKUNDEAEGESPERRT[0]; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    char         GetSkdanrufgenerell() const { return s.SKDANRUFGENERELL[0]; }

    const mcustomerdisplayS &
                 GetStruct() const { return s; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetAnredekz(short t) { s.ANREDEKZ = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_MCUSTOMERDISPLAY_NAMEAPO); }
    void         SetNameinhaber(const ppString & t) { ppGStrCopy(s.NAMEINHABER, t.c_str(), L_MCUSTOMERDISPLAY_NAMEINHABER); }
    void         SetStrasse(const ppString & t) { ppGStrCopy(s.STRASSE, t.c_str(), L_MCUSTOMERDISPLAY_STRASSE); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_MCUSTOMERDISPLAY_ORT); }
    void         SetPostleitzahl(const ppString & t) { ppGStrCopy(s.POSTLEITZAHL, t.c_str(), L_MCUSTOMERDISPLAY_POSTLEITZAHL); }
    void         SetTelnr(const ppString & t) { ppGStrCopy(s.TELNR, t.c_str(), L_MCUSTOMERDISPLAY_TELNR); }
    void         SetTelnrdafue(const ppString & t) { ppGStrCopy(s.TELNRDAFUE, t.c_str(), L_MCUSTOMERDISPLAY_TELNRDAFUE); }
    void         SetTelkurzwahl(const ppString & t) { ppGStrCopy(s.TELKURZWAHL, t.c_str(), L_MCUSTOMERDISPLAY_TELKURZWAHL); }
    void         SetSkdkundeaegesperrt(char t) { s.SKDKUNDEAEGESPERRT[0] = t; s.SKDKUNDEAEGESPERRT[1] = '\0';}
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetSkdanrufgenerell(char t) { s.SKDANRUFGENERELL[0] = t; s.SKDANRUFGENERELL[1] = '\0';}

    void         SetStruct(const mcustomerdisplayS & t) { s = t; }

    int          SelCustomer(int pos = 0) { int ret = UniqueServerCall(1075, pos); Strip(s); return ret; }
    int          UpdProperties(int pos = 0) { int ret = UniqueServerCall(1255, pos); Strip(s); return ret; }
    int          UpdTelNo(int pos = 0) { int ret = UniqueServerCall(1241, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERDISPLAY() {
        ::buf_default((void *)&s, MCUSTOMERDISPLAY_BES, MCUSTOMERDISPLAY_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERDISPLAY() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERDISPLAY_BES, MCUSTOMERDISPLAY_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1075 ) return UniqueServerCall(1075, pos);
        if ( fkt_nr == 1255 ) return UniqueServerCall(1255, pos);
        if ( fkt_nr == 1241 ) return UniqueServerCall(1241, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERDISPLAY & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.NAMEINHABER);
        ppGStripLast(d.STRASSE);
        ppGStripLast(d.ORT);
        ppGStripLast(d.POSTLEITZAHL);
        ppGStripLast(d.TELNR);
        ppGStripLast(d.TELNRDAFUE);
        ppGStripLast(d.TELKURZWAHL);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERDISPLAY_BES, (int)MCUSTOMERDISPLAY_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CMDEVICEPLANMAINTENANCE : public ppDadeVirtual {
public:
    mdeviceplanmaintenanceS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mdeviceplanmaintenanceS> lst; // class list

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
                     vector< mdeviceplanmaintenanceS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mdeviceplanmaintenanceS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mdeviceplanmaintenanceS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mdeviceplanmaintenanceS>::iterator
                 beginList() { return lst.begin(); }
    vector<mdeviceplanmaintenanceS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRegionentyp() const { return s.REGIONENTYP; }
    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetGeraeteid(ppString & t) const { t = s.GERAETEID; t.erasespace(ppString::END); return t.c_str(); }
    char         GetGeraeteart() const { return s.GERAETEART[0]; }
    long         GetGeraetnst() const { return s.GERAETNST; }
    char         GetGeraeteverw1() const { return s.GERAETEVERW1[0]; }
    char         GetModemtyp() const { return s.MODEMTYP[0]; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    short        GetUmknr() const { return s.UMKNR; }
    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }
    long         GetLoginid() const { return s.LOGINID; }
    char         GetChangeid() const { return s.CHANGEID[0]; }
    char         GetAktiv() const { return s.AKTIV[0]; }
    short        GetUmknst() const { return s.UMKNST; }

    const mdeviceplanmaintenanceS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetRegionentyp(short t) { s.REGIONENTYP = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetGeraeteid(const ppString & t) { ppGStrCopy(s.GERAETEID, t.c_str(), L_MDEVICEPLANMAINTENANCE_GERAETEID); }
    void         SetGeraeteart(char t) { s.GERAETEART[0] = t; s.GERAETEART[1] = '\0';}
    void         SetGeraetnst(long t) { s.GERAETNST = t; }
    void         SetGeraeteverw1(char t) { s.GERAETEVERW1[0] = t; s.GERAETEVERW1[1] = '\0';}
    void         SetModemtyp(char t) { s.MODEMTYP[0] = t; s.MODEMTYP[1] = '\0';}
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetUmknr(short t) { s.UMKNR = t; }
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }
    void         SetLoginid(long t) { s.LOGINID = t; }
    void         SetChangeid(char t) { s.CHANGEID[0] = t; s.CHANGEID[1] = '\0';}
    void         SetAktiv(char t) { s.AKTIV[0] = t; s.AKTIV[1] = '\0';}
    void         SetUmknst(short t) { s.UMKNST = t; }

    void         SetStruct(const mdeviceplanmaintenanceS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1114, pos); }
    int          InsertDevice(int pos = 0) { int ret = UniqueServerCall(1191, pos); Strip(s); return ret; }
    int          SelDevicePlanUni(int pos = 0) { int ret = UniqueServerCall(1115, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1111, FetchRel, pos); return ret; }
    int          SelNst(int pos = 0) { int ret = UniqueServerCall(1192, pos); Strip(s); return ret; }
    int          UpdDevicePlan(int pos = 0) { int ret = UniqueServerCall(1112, pos); Strip(s); return ret; }
    int          UpdSaleCenterNo(int pos = 0) { int ret = UniqueServerCall(1120, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMDEVICEPLANMAINTENANCE() {
        ::buf_default((void *)&s, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMDEVICEPLANMAINTENANCE() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MDEVICEPLANMAINTENANCE_BES, MDEVICEPLANMAINTENANCE_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MDEVICEPLANMAINTENANCE_BES, (int)MDEVICEPLANMAINTENANCE_ANZ, error_msg);
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
        if ( fkt_nr == 1114 ) return UniqueServerCall(1114, pos);
        if ( fkt_nr == 1191 ) return UniqueServerCall(1191, pos);
        if ( fkt_nr == 1115 ) return UniqueServerCall(1115, pos);
        if ( fkt_nr == 1111 ) return CursorServerCall(1111, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1192 ) return UniqueServerCall(1192, pos);
        if ( fkt_nr == 1112 ) return UniqueServerCall(1112, pos);
        if ( fkt_nr == 1120 ) return UniqueServerCall(1120, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MDEVICEPLANMAINTENANCE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.GERAETEID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MDEVICEPLANMAINTENANCE_BES, (int)MDEVICEPLANMAINTENANCE_ANZ, error_msg);
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
        CMDEVICEPLANMAINTENANCE c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MDEVICEPLANMAINTENANCE_BES, (int)MDEVICEPLANMAINTENANCE_ANZ, error_msg);
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

class CMREGION : public ppDadeVirtual {
public:
    mregionS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mregionS> lst; // class list

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
                     vector< mregionS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mregionS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mregionS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mregionS>::iterator
                 beginList() { return lst.begin(); }
    vector<mregionS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRegionentyp() const { return s.REGIONENTYP; }
    long         GetRegionnr() const { return s.REGIONNR; }
    long         GetRegionteilnr() const { return s.REGIONTEILNR; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }
    long         GetLoginid() const { return s.LOGINID; }
    char         GetChangeid() const { return s.CHANGEID[0]; }

    const mregionS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetRegionentyp(short t) { s.REGIONENTYP = t; }
    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetRegionteilnr(long t) { s.REGIONTEILNR = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_MREGION_NAME); }
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }
    void         SetLoginid(long t) { s.LOGINID = t; }
    void         SetChangeid(char t) { s.CHANGEID[0] = t; s.CHANGEID[1] = '\0';}

    void         SetStruct(const mregionS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DelRegion(int pos = 0) { return UniqueServerCall(1180, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1181, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1173, FetchRel, pos); return ret; }
    int          SelRegion(int pos = 0) { int ret = UniqueServerCall(1361, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMREGION() {
        ::buf_default((void *)&s, MREGION_BES, MREGION_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMREGION() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MREGION_BES, MREGION_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MREGION_BES, (int)MREGION_ANZ, error_msg);
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
        if ( fkt_nr == 1180 ) return UniqueServerCall(1180, pos);
        if ( fkt_nr == 1181 ) return UniqueServerCall(1181, pos);
        if ( fkt_nr == 1173 ) return CursorServerCall(1173, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1361 ) return UniqueServerCall(1361, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MREGION & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MREGION_BES, (int)MREGION_ANZ, error_msg);
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
        CMREGION c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MREGION_BES, (int)MREGION_ANZ, error_msg);
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

class CMSALECENTER : public ppDadeVirtual {
public:
    msalecenterS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<msalecenterS> lst; // class list

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
                     vector< msalecenterS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     msalecenterS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< msalecenterS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<msalecenterS>::iterator
                 beginList() { return lst.begin(); }
    vector<msalecenterS>::iterator
                 endList  () { return lst.end  (); }

    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetName(ppString & t) const { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }

    const msalecenterS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetName(const ppString & t) { ppGStrCopy(s.NAME, t.c_str(), L_MSALECENTER_NAME); }

    void         SetStruct(const msalecenterS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1178, FetchRel, pos); return ret; }
    int          SelSaleCenter(int pos = 0) { int ret = UniqueServerCall(1179, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMSALECENTER() {
        ::buf_default((void *)&s, MSALECENTER_BES, MSALECENTER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMSALECENTER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MSALECENTER_BES, MSALECENTER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSALECENTER_BES, (int)MSALECENTER_ANZ, error_msg);
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
        if ( fkt_nr == 1178 ) return CursorServerCall(1178, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1179 ) return UniqueServerCall(1179, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MSALECENTER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MSALECENTER_BES, (int)MSALECENTER_ANZ, error_msg);
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
        CMSALECENTER c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MSALECENTER_BES, (int)MSALECENTER_ANZ, error_msg);
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

class CMUMKCONNECTION : public ppDadeVirtual {
public:
    mumkconnectionS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mumkconnectionS> lst; // class list

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
                     vector< mumkconnectionS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mumkconnectionS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mumkconnectionS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mumkconnectionS>::iterator
                 beginList() { return lst.begin(); }
    vector<mumkconnectionS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRegionentyp() const { return s.REGIONENTYP; }
    long         GetRegionnr() const { return s.REGIONNR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetUmknr() const { return s.UMKNR; }
    const char*  GetRechnername(ppString & t) const { t = s.RECHNERNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetPortnr() const { return s.PORTNR; }
    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }
    long         GetLoginid() const { return s.LOGINID; }
    char         GetChangeid() const { return s.CHANGEID[0]; }

    const mumkconnectionS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetRegionentyp(short t) { s.REGIONENTYP = t; }
    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetUmknr(short t) { s.UMKNR = t; }
    void         SetRechnername(const ppString & t) { ppGStrCopy(s.RECHNERNAME, t.c_str(), L_MUMKCONNECTION_RECHNERNAME); }
    void         SetPortnr(long t) { s.PORTNR = t; }
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }
    void         SetLoginid(long t) { s.LOGINID = t; }
    void         SetChangeid(char t) { s.CHANGEID[0] = t; s.CHANGEID[1] = '\0';}

    void         SetStruct(const mumkconnectionS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DelUmkConnection(int pos = 0) { return UniqueServerCall(1171, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1169, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1129, FetchRel, pos); return ret; }
    int          SelUmkConnection(int pos = 0) { int ret = UniqueServerCall(1160, pos); Strip(s); return ret; }
    int          UpdUmkConnection(int pos = 0) { int ret = UniqueServerCall(1170, pos); Strip(s); return ret; }
    int          WriteLog(int pos = 0) { int ret = UniqueServerCall(1161, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMUMKCONNECTION() {
        ::buf_default((void *)&s, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMUMKCONNECTION() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MUMKCONNECTION_BES, MUMKCONNECTION_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MUMKCONNECTION_BES, (int)MUMKCONNECTION_ANZ, error_msg);
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
        if ( fkt_nr == 1171 ) return UniqueServerCall(1171, pos);
        if ( fkt_nr == 1169 ) return UniqueServerCall(1169, pos);
        if ( fkt_nr == 1129 ) return CursorServerCall(1129, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1160 ) return UniqueServerCall(1160, pos);
        if ( fkt_nr == 1170 ) return UniqueServerCall(1170, pos);
        if ( fkt_nr == 1161 ) return UniqueServerCall(1161, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MUMKCONNECTION & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.RECHNERNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MUMKCONNECTION_BES, (int)MUMKCONNECTION_ANZ, error_msg);
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
        CMUMKCONNECTION c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MUMKCONNECTION_BES, (int)MUMKCONNECTION_ANZ, error_msg);
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
