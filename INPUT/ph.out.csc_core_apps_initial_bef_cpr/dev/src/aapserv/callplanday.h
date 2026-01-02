#ifndef __PP_CALLPLANDAY_H_
#define __PP_CALLPLANDAY_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\CallPlanDay **/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CHECKORDEREXIST *******************************************/

#define L_CHECKORDEREXIST_KDAUFTRAGNR 11
#define L_CHECKORDEREXIST_VERTRIEBSZENTRUMNR 6
#define L_CHECKORDEREXIST_KUNDENNR 11
#define L_CHECKORDEREXIST_TM_TIME 11

/* Length-Define of MCALLPARAMTERDRIVER ***************************************/

#define L_MCALLPARAMTERDRIVER_VERTRIEBSZENTRUMNR 6
#define L_MCALLPARAMTERDRIVER_RUFZEITVERSCHIEBEN 6
#define L_MCALLPARAMTERDRIVER_ANZRUFWIEDERHOLUNG 6
#define L_MCALLPARAMTERDRIVER_RUFABWEICHUNGPH 6
#define L_MCALLPARAMTERDRIVER_RUFABWEICHUNGDP 6
#define L_MCALLPARAMTERDRIVER_RUFABWEICHUNGDS 6
#define L_MCALLPARAMTERDRIVER_ZEITFENSTERAUFTRAG 6
#define L_MCALLPARAMTERDRIVER_ZEITANZPOSAUFTRAG 6
#define L_MCALLPARAMTERDRIVER_TM_DATE 11
#define L_MCALLPARAMTERDRIVER_TM_TIME 11
#define L_MCALLPARAMTERDRIVER_LOGINID 11
#define L_MCALLPARAMTERDRIVER_CHANGEID 1
#define L_MCALLPARAMTERDRIVER_UMKRUFWIEDERHOLUNG 6
#define L_MCALLPARAMTERDRIVER_KABRUFWIEDERHOLUNG 6
#define L_MCALLPARAMTERDRIVER_CALLPLANSTARTSTOP 1
#define L_MCALLPARAMTERDRIVER_STOPSTARTZEIT 6

/* Length-Define of MCUSTOMERCALLPLANDAY **************************************/

#define L_MCUSTOMERCALLPLANDAY_IDFNR 11
#define L_MCUSTOMERCALLPLANDAY_NAMEAPO 40
#define L_MCUSTOMERCALLPLANDAY_ORT 30
#define L_MCUSTOMERCALLPLANDAY_TELNR 20
#define L_MCUSTOMERCALLPLANDAY_TELKURZWAHL 4
#define L_MCUSTOMERCALLPLANDAY_KZKDKLASSE 3
#define L_MCUSTOMERCALLPLANDAY_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERCALLPLANDAY_KUNDENNR 11
#define L_MCUSTOMERCALLPLANDAY_DATUM 11
#define L_MCUSTOMERCALLPLANDAY_URRUFZEIT 11
#define L_MCUSTOMERCALLPLANDAY_RUFZEIT 11
#define L_MCUSTOMERCALLPLANDAY_UMKSTATUS 6
#define L_MCUSTOMERCALLPLANDAY_ANRUFSTATUS 6
#define L_MCUSTOMERCALLPLANDAY_ANRUFZAEHLER 6
#define L_MCUSTOMERCALLPLANDAY_TAGNR 1
#define L_MCUSTOMERCALLPLANDAY_TOURID 6
#define L_MCUSTOMERCALLPLANDAY_STOURDEFINITIV 1
#define L_MCUSTOMERCALLPLANDAY_RUFPROTOKOLL 1
#define L_MCUSTOMERCALLPLANDAY_RUFSTEUERUNG 6
#define L_MCUSTOMERCALLPLANDAY_POOLNR 6
#define L_MCUSTOMERCALLPLANDAY_MODEMPOOLNR 6
#define L_MCUSTOMERCALLPLANDAY_RUFEINSTELLUNG 1
#define L_MCUSTOMERCALLPLANDAY_ANRUFTYP 1
#define L_MCUSTOMERCALLPLANDAY_SKDANRUFGENERELL 1

/* Length-Define of MCUSTOMERCALLPLANDAYHIST **********************************/

#define L_MCUSTOMERCALLPLANDAYHIST_USERNAME 8
#define L_MCUSTOMERCALLPLANDAYHIST_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERCALLPLANDAYHIST_KUNDENNR 11
#define L_MCUSTOMERCALLPLANDAYHIST_DATUM 11
#define L_MCUSTOMERCALLPLANDAYHIST_URRUFZEIT 11
#define L_MCUSTOMERCALLPLANDAYHIST_EREIGNIS 6
#define L_MCUSTOMERCALLPLANDAYHIST_RUFZEIT 11
#define L_MCUSTOMERCALLPLANDAYHIST_UMKSTATUS 6
#define L_MCUSTOMERCALLPLANDAYHIST_ANRUFSTATUS 6
#define L_MCUSTOMERCALLPLANDAYHIST_FILIALNR 6
#define L_MCUSTOMERCALLPLANDAYHIST_MODEMNR 11
#define L_MCUSTOMERCALLPLANDAYHIST_UHRZEIT 11
#define L_MCUSTOMERCALLPLANDAYHIST_GERAETEID 4
#define L_MCUSTOMERCALLPLANDAYHIST_UID 11
#define L_MCUSTOMERCALLPLANDAYHIST_DATUMANLAGE 11

/* Length-Define of MCUSTOMERCALLPLANRECALLINWORK *****************************/

#define L_MCUSTOMERCALLPLANRECALLINWORK_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERCALLPLANRECALLINWORK_KUNDENNR 11
#define L_MCUSTOMERCALLPLANRECALLINWORK_URRUFZEIT 11
#define L_MCUSTOMERCALLPLANRECALLINWORK_DATUM 11
#define L_MCUSTOMERCALLPLANRECALLINWORK_FILIALNR 6
#define L_MCUSTOMERCALLPLANRECALLINWORK_UID 11
#define L_MCUSTOMERCALLPLANRECALLINWORK_TM_TIME 11

/* Length-Define of MCUSTOMERCALLPLANDAYDRIVER ********************************/

#define L_MCUSTOMERCALLPLANDAYDRIVER_NAMEAPO 40
#define L_MCUSTOMERCALLPLANDAYDRIVER_TELNR 20
#define L_MCUSTOMERCALLPLANDAYDRIVER_TELNRDAFUE 20
#define L_MCUSTOMERCALLPLANDAYDRIVER_TELKURZWAHL 4
#define L_MCUSTOMERCALLPLANDAYDRIVER_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERCALLPLANDAYDRIVER_KUNDENNR 11
#define L_MCUSTOMERCALLPLANDAYDRIVER_DATUM 11
#define L_MCUSTOMERCALLPLANDAYDRIVER_URRUFZEIT 11
#define L_MCUSTOMERCALLPLANDAYDRIVER_RUFZEIT 11
#define L_MCUSTOMERCALLPLANDAYDRIVER_UMKSTATUS 6
#define L_MCUSTOMERCALLPLANDAYDRIVER_ANRUFSTATUS 6
#define L_MCUSTOMERCALLPLANDAYDRIVER_ANRUFZAEHLER 6
#define L_MCUSTOMERCALLPLANDAYDRIVER_TAGNR 1
#define L_MCUSTOMERCALLPLANDAYDRIVER_TOURID 6
#define L_MCUSTOMERCALLPLANDAYDRIVER_STOURDEFINITIV 1
#define L_MCUSTOMERCALLPLANDAYDRIVER_RUFPROTOKOLL 1
#define L_MCUSTOMERCALLPLANDAYDRIVER_RUFSTEUERUNG 6
#define L_MCUSTOMERCALLPLANDAYDRIVER_POOLNR 6
#define L_MCUSTOMERCALLPLANDAYDRIVER_MODEMPOOLNR 6
#define L_MCUSTOMERCALLPLANDAYDRIVER_RUFEINSTELLUNG 1
#define L_MCUSTOMERCALLPLANDAYDRIVER_ANRUFTYP 1
#define L_MCUSTOMERCALLPLANDAYDRIVER_SKDANRUFGENERELL 1
#define L_MCUSTOMERCALLPLANDAYDRIVER_EREIGNIS 6
#define L_MCUSTOMERCALLPLANDAYDRIVER_UHRZEIT 11
#define L_MCUSTOMERCALLPLANDAYDRIVER_GERAETEID 4
#define L_MCUSTOMERCALLPLANDAYDRIVER_UID 11

/* Length-Define of MCUSTOMERLASTCALL *****************************************/

#define L_MCUSTOMERLASTCALL_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERLASTCALL_KUNDENNR 11
#define L_MCUSTOMERLASTCALL_DATUM 11
#define L_MCUSTOMERLASTCALL_URRUFZEIT 11
#define L_MCUSTOMERLASTCALL_ANRUFSTATUS 6
#define L_MCUSTOMERLASTCALL_UHRZEIT 11

/* Length-Define of MCUSTOMERORDER ********************************************/

#define L_MCUSTOMERORDER_KDAUFTRAGNR 11
#define L_MCUSTOMERORDER_KDAUFTRAGSTAT 16
#define L_MCUSTOMERORDER_ZEIT 11
#define L_MCUSTOMERORDER_GERAETNAME 8
#define L_MCUSTOMERORDER_ANZPOS 11
#define L_MCUSTOMERORDER_VERTRIEBSZENTRUMNR 6
#define L_MCUSTOMERORDER_KUNDENNR 11

/* Length-Define of MDEVICEPLANCHECK ******************************************/

#define L_MDEVICEPLANCHECK_REGIONENTYP 6
#define L_MDEVICEPLANCHECK_FILIALNR 6
#define L_MDEVICEPLANCHECK_GERAETEID 4
#define L_MDEVICEPLANCHECK_SEQUENZNR 11
#define L_MDEVICEPLANCHECK_GERAETNST 11
#define L_MDEVICEPLANCHECK_GERAETEVERW1 1
#define L_MDEVICEPLANCHECK_TERMINALSTATUS 1
#define L_MDEVICEPLANCHECK_STARTZEIT 11
#define L_MDEVICEPLANCHECK_ENDEZEIT 11
#define L_MDEVICEPLANCHECK_VERTRIEBSZENTRUMNR 6
#define L_MDEVICEPLANCHECK_KUNDENNR 11
#define L_MDEVICEPLANCHECK_URRUFZEIT 11
#define L_MDEVICEPLANCHECK_DATUM 11
#define L_MDEVICEPLANCHECK_AUFTRAGSTATUS 1
#define L_MDEVICEPLANCHECK_KDAUFTRAGNR1 11
#define L_MDEVICEPLANCHECK_POOLNR 6
#define L_MDEVICEPLANCHECK_UMKNR 6
#define L_MDEVICEPLANCHECK_AKTIV 1

/* Length-Define of MDEVICEPLANDRIVER *****************************************/

#define L_MDEVICEPLANDRIVER_REGIONENTYP 6
#define L_MDEVICEPLANDRIVER_SCHLUESSEL 11
#define L_MDEVICEPLANDRIVER_FILIALNR 6
#define L_MDEVICEPLANDRIVER_GERAETEID 4
#define L_MDEVICEPLANDRIVER_SEQUENZNR 11
#define L_MDEVICEPLANDRIVER_GERAETEART 1
#define L_MDEVICEPLANDRIVER_GERAETEVERW1 1
#define L_MDEVICEPLANDRIVER_TERMINALSTATUS 1
#define L_MDEVICEPLANDRIVER_MODEMTYP 1
#define L_MDEVICEPLANDRIVER_STARTZEIT 11
#define L_MDEVICEPLANDRIVER_ENDEZEIT 11
#define L_MDEVICEPLANDRIVER_VERTRIEBSZENTRUMNR 6
#define L_MDEVICEPLANDRIVER_KUNDENNR 11
#define L_MDEVICEPLANDRIVER_URRUFZEIT 11
#define L_MDEVICEPLANDRIVER_DATUM 11
#define L_MDEVICEPLANDRIVER_AUFTRAGSTATUS 1
#define L_MDEVICEPLANDRIVER_KDAUFTRAGNR1 11
#define L_MDEVICEPLANDRIVER_POOLNR 6
#define L_MDEVICEPLANDRIVER_UMKNR 6
#define L_MDEVICEPLANDRIVER_TOURID 6
#define L_MDEVICEPLANDRIVER_AKTIV 1
#define L_MDEVICEPLANDRIVER_UMKNST 6

/* Length-Define of MNUMBER ***************************************************/

#define L_MNUMBER_NUMMERTYP 6
#define L_MNUMBER_NUMMERWERT 11
#define L_MNUMBER_NUMMERMINDEST 11
#define L_MNUMBER_NUMMERHOECHST 11
#define L_MNUMBER_NUMMERINKREMENT 11
#define L_MNUMBER_NUMMERMODUS 6

/* Length-Define of MTRANSAKTION **********************************************/

#define L_MTRANSAKTION_TM_DATE 11
#define L_MTRANSAKTION_TM_TIME 11

/* SqlDefine of CHECKORDEREXIST ***********************************************/


#define CHECKORDEREXIST_PLISTE \
        "KDAUFTRAG.KDAUFTRAGNR,"\
        "KDAUFTRAG.VERTRIEBSZENTRUMNR,"\
        "KDAUFTRAG.KUNDENNR"

/* SqlDefine of MCALLPARAMTERDRIVER *******************************************/


#define MCALLPARAMTERDRIVER_PLISTE \
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
        "ANRUFPARAMETER.CALLPLANSTARTSTOP,"\
        "ANRUFPARAMETER.STOPSTARTZEIT"

/* SqlDefine of MCUSTOMERCALLPLANDAY ******************************************/


#define MCUSTOMERCALLPLANDAY_PLISTE \
        "KUNDE.IDFNR,"\
        "KUNDE.NAMEAPO,"\
        "KUNDE.ORT,"\
        "KUNDE.TELNR,"\
        "KUNDE.TELKURZWAHL,"\
        "KUNDE.KZKDKLASSE,"\
        "KUNDEANRUFPLANTAG.VERTRIEBSZENTRUMNR,"\
        "KUNDEANRUFPLANTAG.KUNDENNR,"\
        "KUNDEANRUFPLANTAG.DATUM,"\
        "KUNDEANRUFPLANTAG.URRUFZEIT,"\
        "KUNDEANRUFPLANTAG.RUFZEIT,"\
        "KUNDEANRUFPLANTAG.UMKSTATUS,"\
        "KUNDEANRUFPLANTAG.ANRUFSTATUS,"\
        "KUNDEANRUFPLANTAG.ANRUFZAEHLER,"\
        "KUNDEANRUFPLANTAG.TAGNR,"\
        "KUNDEANRUFPLANTAG.TOURID,"\
        "KUNDEANRUFPLANTAG.STOURDEFINITIV,"\
        "KUNDEANRUFPLANTAG.RUFPROTOKOLL,"\
        "KUNDEANRUFPLANTAG.RUFSTEUERUNG,"\
        "KUNDEANRUFPLANTAG.POOLNR,"\
        "KUNDEANRUFPLANTAG.MODEMPOOLNR,"\
        "KUNDEANRUFPLANTAG.RUFEINSTELLUNG,"\
        "KUNDEANRUFPLANTAG.ANRUFTYP,"\
        "KUNDEANRUFPLANTAG.SKDANRUFGENERELL"

/* SqlDefine of MCUSTOMERCALLPLANDAYHIST **************************************/


#define MCUSTOMERCALLPLANDAYHIST_PLISTE \
        "PASSWD.USERNAME,"\
        "KUNDEANRUFPLANPROT.VERTRIEBSZENTRUMNR,"\
        "KUNDEANRUFPLANPROT.KUNDENNR,"\
        "KUNDEANRUFPLANPROT.DATUM,"\
        "KUNDEANRUFPLANPROT.URRUFZEIT,"\
        "KUNDEANRUFPLANPROT.EREIGNIS,"\
        "KUNDEANRUFPLANPROT.RUFZEIT,"\
        "KUNDEANRUFPLANPROT.UMKSTATUS,"\
        "KUNDEANRUFPLANPROT.ANRUFSTATUS,"\
        "KUNDEANRUFPLANPROT.FILIALNR,"\
        "KUNDEANRUFPLANPROT.MODEMNR,"\
        "KUNDEANRUFPLANPROT.UHRZEIT,"\
        "KUNDEANRUFPLANPROT.GERAETEID,"\
        "KUNDEANRUFPLANPROT.UID,"\
        "KUNDEANRUFPLANPROT.DATUMANLAGE"

/* SqlDefine of MCUSTOMERCALLPLANRECALLINWORK *********************************/


#define MCUSTOMERCALLPLANRECALLINWORK_PLISTE \
        "KUNDEANRUFPLANRR.VERTRIEBSZENTRUMNR,"\
        "KUNDEANRUFPLANRR.KUNDENNR,"\
        "KUNDEANRUFPLANRR.URRUFZEIT,"\
        "KUNDEANRUFPLANRR.DATUM,"\
        "KUNDEANRUFPLANRR.FILIALNR,"\
        "KUNDEANRUFPLANRR.UID,"\
        "KUNDEANRUFPLANRR.TM_TIME"

/* SqlDefine of MCUSTOMERCALLPLANDAYDRIVER ************************************/


#define MCUSTOMERCALLPLANDAYDRIVER_PLISTE \
        "KUNDE.NAMEAPO,"\
        "KUNDE.TELNR,"\
        "KUNDE.TELNRDAFUE,"\
        "KUNDE.TELKURZWAHL,"\
        "KUNDEANRUFPLANTAG.VERTRIEBSZENTRUMNR,"\
        "KUNDEANRUFPLANTAG.KUNDENNR,"\
        "KUNDEANRUFPLANTAG.DATUM,"\
        "KUNDEANRUFPLANTAG.URRUFZEIT,"\
        "KUNDEANRUFPLANTAG.RUFZEIT,"\
        "KUNDEANRUFPLANTAG.UMKSTATUS,"\
        "KUNDEANRUFPLANTAG.ANRUFSTATUS,"\
        "KUNDEANRUFPLANTAG.ANRUFZAEHLER,"\
        "KUNDEANRUFPLANTAG.TAGNR,"\
        "KUNDEANRUFPLANTAG.TOURID,"\
        "KUNDEANRUFPLANTAG.STOURDEFINITIV,"\
        "KUNDEANRUFPLANTAG.RUFPROTOKOLL,"\
        "KUNDEANRUFPLANTAG.RUFSTEUERUNG,"\
        "KUNDEANRUFPLANTAG.POOLNR,"\
        "KUNDEANRUFPLANTAG.MODEMPOOLNR,"\
        "KUNDEANRUFPLANTAG.RUFEINSTELLUNG,"\
        "KUNDEANRUFPLANTAG.ANRUFTYP,"\
        "KUNDEANRUFPLANTAG.SKDANRUFGENERELL,"\
        "KUNDEANRUFPLANPROT.EREIGNIS,"\
        "KUNDEANRUFPLANPROT.UHRZEIT,"\
        "KUNDEANRUFPLANPROT.UID"

/* SqlDefine of MCUSTOMERLASTCALL *********************************************/


#define MCUSTOMERLASTCALL_PLISTE \
        "KUNDEANRUFPLANPROT.ANRUFSTATUS,"\
        "KUNDEANRUFPLANPROT.UHRZEIT"

/* SqlDefine of MCUSTOMERORDER ************************************************/


#define MCUSTOMERORDER_PLISTE \
        "KDAUFTRAG.KDAUFTRAGNR,"\
        "KDAUFTRAG.KDAUFTRAGSTAT,"\
        "KDAUFTRAGEREIGNIS.ZEIT,"\
        "KDAUFTRAG.GERAETNAME,"\
        "KDAUFTRAG.ANZPOS,"\
        "KDAUFTRAG.VERTRIEBSZENTRUMNR,"\
        "KDAUFTRAG.KUNDENNR"

/* SqlDefine of MDEVICEPLANCHECK **********************************************/


#define MDEVICEPLANCHECK_PLISTE \
        "REGIONARTEN.REGIONENTYP,"\
        "MODEMANRUFPLAN.FILIALNR,"\
        "MODEMANRUFPLAN.GERAETEID,"\
        "MODEMANRUFPLAN.SEQUENZNR,"\
        "MODEMANRUFPLAN.GERAETNST,"\
        "MODEMANRUFPLAN.GERAETEVERW1,"\
        "MODEMANRUFPLAN.TERMINALSTATUS,"\
        "MODEMANRUFPLAN.STARTZEIT,"\
        "MODEMANRUFPLAN.ENDEZEIT,"\
        "MODEMANRUFPLAN.VERTRIEBSZENTRUMNR,"\
        "MODEMANRUFPLAN.KUNDENNR,"\
        "MODEMANRUFPLAN.URRUFZEIT,"\
        "MODEMANRUFPLAN.DATUM,"\
        "MODEMANRUFPLAN.AUFTRAGSTATUS,"\
        "MODEMANRUFPLAN.KDAUFTRAGNR1,"\
        "MODEMANRUFPLAN.POOLNR,"\
        "MODEMANRUFPLAN.UMKNR,"\
        "MODEMANRUFPLAN.AKTIV"

/* SqlDefine of MDEVICEPLANDRIVER *********************************************/


#define MDEVICEPLANDRIVER_PLISTE \
        "MODEMANRUFPLAN.FILIALNR,"\
        "MODEMANRUFPLAN.GERAETEID,"\
        "MODEMANRUFPLAN.SEQUENZNR,"\
        "MODEMANRUFPLAN.GERAETEART,"\
        "MODEMANRUFPLAN.GERAETEVERW1,"\
        "MODEMANRUFPLAN.TERMINALSTATUS,"\
        "MODEMANRUFPLAN.MODEMTYP,"\
        "MODEMANRUFPLAN.STARTZEIT,"\
        "MODEMANRUFPLAN.ENDEZEIT,"\
        "MODEMANRUFPLAN.VERTRIEBSZENTRUMNR,"\
        "MODEMANRUFPLAN.KUNDENNR,"\
        "MODEMANRUFPLAN.URRUFZEIT,"\
        "MODEMANRUFPLAN.DATUM,"\
        "MODEMANRUFPLAN.AUFTRAGSTATUS,"\
        "MODEMANRUFPLAN.KDAUFTRAGNR1,"\
        "MODEMANRUFPLAN.POOLNR,"\
        "MODEMANRUFPLAN.UMKNR,"\
        "MODEMANRUFPLAN.TOURID,"\
        "MODEMANRUFPLAN.AKTIV,"\
        "MODEMANRUFPLAN.UMKNST"

/* SqlDefine of MNUMBER *******************************************************/


#define MNUMBER_PLISTE \
        "NUMMER.NUMMERTYP,"\
        "NUMMER.NUMMERWERT,"\
        "NUMMER.NUMMERMINDEST,"\
        "NUMMER.NUMMERHOECHST,"\
        "NUMMER.NUMMERINKREMENT,"\
        "NUMMER.NUMMERMODUS"

/* SqlDefine of MTRANSAKTION **************************************************/


#define MTRANSAKTION_PLISTE \
        "AADUMMY.TM_DATE,"\
        "AADUMMY.TM_TIME"

/* SqlDefine of CHECKORDEREXIST ***********************************************/


#define CHECKORDEREXIST_UPDLISTE \
        "KDAUFTRAGNR=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?"
/* SqlDefine of MCALLPARAMTERDRIVER *******************************************/


#define MCALLPARAMTERDRIVER_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "RUFZEITVERSCHIEBEN=?,"\
        "ANZRUFWIEDERHOLUNG=?,"\
        "RUFABWEICHUNGPH=?,"\
        "RUFABWEICHUNGDP=?,"\
        "RUFABWEICHUNGDS=?,"\
        "ZEITFENSTERAUFTRAG=?,"\
        "ZEITANZPOSAUFTRAG=?,"\
        "TM_DATE=?,"\
        "TM_TIME=?,"\
        "LOGINID=?,"\
        "CHANGEID=?,"\
        "UMKRUFWIEDERHOLUNG=?,"\
        "KABRUFWIEDERHOLUNG=?,"\
        "CALLPLANSTARTSTOP=?,"\
        "STOPSTARTZEIT=?"
/* SqlDefine of MCUSTOMERCALLPLANDAY ******************************************/


#define MCUSTOMERCALLPLANDAY_UPDLISTE \
        "RUFZEIT=?,"\
        "UMKSTATUS=?,"\
        "ANRUFSTATUS=?,"\
        "ANRUFZAEHLER=?,"\
        "TAGNR=?,"\
        "TOURID=?,"\
        "STOURDEFINITIV=?,"\
        "RUFPROTOKOLL=?,"\
        "RUFSTEUERUNG=?,"\
        "POOLNR=?,"\
        "MODEMPOOLNR=?,"\
        "RUFEINSTELLUNG=?,"\
        "ANRUFTYP=?,"\
        "SKDANRUFGENERELL=?"
/* SqlDefine of MCUSTOMERCALLPLANDAYHIST **************************************/


#define MCUSTOMERCALLPLANDAYHIST_UPDLISTE \
        "EREIGNIS=?,"\
        "RUFZEIT=?,"\
        "UMKSTATUS=?,"\
        "ANRUFSTATUS=?,"\
        "FILIALNR=?,"\
        "MODEMNR=?,"\
        "GERAETEID=?,"\
        "UID=?,"\
        "DATUMANLAGE=?"
/* SqlDefine of MCUSTOMERCALLPLANRECALLINWORK *********************************/


#define MCUSTOMERCALLPLANRECALLINWORK_UPDLISTE \
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "URRUFZEIT=?,"\
        "DATUM=?,"\
        "FILIALNR=?,"\
        "UID=?,"\
        "TM_TIME=?"
/* SqlDefine of MCUSTOMERCALLPLANDAYDRIVER ************************************/


#define MCUSTOMERCALLPLANDAYDRIVER_UPDLISTE \
        "RUFZEIT=?,"\
        "UMKSTATUS=?,"\
        "ANRUFSTATUS=?,"\
        "ANRUFZAEHLER=?,"\
        "TOURID=?"
/* SqlDefine of MCUSTOMERLASTCALL *********************************************/


#define MCUSTOMERLASTCALL_UPDLISTE \
        "UHRZEIT=?"
/* SqlDefine of MCUSTOMERORDER ************************************************/


#define MCUSTOMERORDER_UPDLISTE \
        "ZEIT=?"
/* SqlDefine of MDEVICEPLANCHECK **********************************************/


#define MDEVICEPLANCHECK_UPDLISTE \
        "SEQUENZNR=?,"\
        "TERMINALSTATUS=?,"\
        "STARTZEIT=?,"\
        "ENDEZEIT=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "URRUFZEIT=?,"\
        "DATUM=?,"\
        "AUFTRAGSTATUS=?,"\
        "KDAUFTRAGNR1=?,"\
        "AKTIV=?"
/* SqlDefine of MDEVICEPLANDRIVER *********************************************/


#define MDEVICEPLANDRIVER_UPDLISTE \
        "SEQUENZNR=?,"\
        "TERMINALSTATUS=?,"\
        "STARTZEIT=?,"\
        "ENDEZEIT=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "URRUFZEIT=?,"\
        "DATUM=?,"\
        "AUFTRAGSTATUS=?,"\
        "KDAUFTRAGNR1=?,"\
        "POOLNR=?,"\
        "TOURID=?,"\
        "AKTIV=?,"\
        "UMKNST=?"
/* SqlDefine of MNUMBER *******************************************************/


#define MNUMBER_UPDLISTE \
        "NUMMERWERT=?"
/* SqlDefine of MTRANSAKTION **************************************************/


#define MTRANSAKTION_UPDLISTE \
        "TM_DATE=?,"\
        "TM_TIME=?"
/* SqlMacros-Define of CHECKORDEREXIST ****************************************/

#define CHECKORDEREXIST_ZEIGER(x) \
        :x->KDAUFTRAGNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR
#define CHECKORDEREXIST_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR

/* SqlMacros-Define of MCALLPARAMTERDRIVER ************************************/

#define MCALLPARAMTERDRIVER_ZEIGER(x) \
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
        :x->CALLPLANSTARTSTOP,\
        :x->STOPSTARTZEIT
#define MCALLPARAMTERDRIVER_ZEIGERSEL(x) \
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
        :x->CALLPLANSTARTSTOP,\
        :x->STOPSTARTZEIT

/* SqlMacros-Define of MCUSTOMERCALLPLANDAY ***********************************/

#define MCUSTOMERCALLPLANDAY_ZEIGER(x) \
        :x->RUFZEIT,\
        :x->UMKSTATUS,\
        :x->ANRUFSTATUS,\
        :x->ANRUFZAEHLER,\
        :x->TAGNR,\
        :x->TOURID,\
        :x->STOURDEFINITIV,\
        :x->RUFPROTOKOLL,\
        :x->RUFSTEUERUNG,\
        :x->POOLNR,\
        :x->MODEMPOOLNR,\
        :x->RUFEINSTELLUNG,\
        :x->ANRUFTYP,\
        :x->SKDANRUFGENERELL
#define MCUSTOMERCALLPLANDAY_ZEIGERSEL(x) \
        :x->IDFNR,\
        :x->NAMEAPO,\
        :x->ORT,\
        :x->TELNR,\
        :x->TELKURZWAHL,\
        :x->KZKDKLASSE,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUM,\
        :x->URRUFZEIT,\
        :x->RUFZEIT,\
        :x->UMKSTATUS,\
        :x->ANRUFSTATUS,\
        :x->ANRUFZAEHLER,\
        :x->TAGNR,\
        :x->TOURID,\
        :x->STOURDEFINITIV,\
        :x->RUFPROTOKOLL,\
        :x->RUFSTEUERUNG,\
        :x->POOLNR,\
        :x->MODEMPOOLNR,\
        :x->RUFEINSTELLUNG,\
        :x->ANRUFTYP,\
        :x->SKDANRUFGENERELL

/* SqlMacros-Define of MCUSTOMERCALLPLANDAYHIST *******************************/

#define MCUSTOMERCALLPLANDAYHIST_ZEIGER(x) \
        :x->EREIGNIS,\
        :x->RUFZEIT,\
        :x->UMKSTATUS,\
        :x->ANRUFSTATUS,\
        :x->FILIALNR,\
        :x->MODEMNR,\
        :x->GERAETEID,\
        :x->UID,\
        :x->DATUMANLAGE
#define MCUSTOMERCALLPLANDAYHIST_ZEIGERSEL(x) \
        :x->USERNAME,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUM,\
        :x->URRUFZEIT,\
        :x->EREIGNIS,\
        :x->RUFZEIT,\
        :x->UMKSTATUS,\
        :x->ANRUFSTATUS,\
        :x->FILIALNR,\
        :x->MODEMNR,\
        :x->UHRZEIT,\
        :x->GERAETEID,\
        :x->UID,\
        :x->DATUMANLAGE

/* SqlMacros-Define of MCUSTOMERCALLPLANRECALLINWORK **************************/

#define MCUSTOMERCALLPLANRECALLINWORK_ZEIGER(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->URRUFZEIT,\
        :x->DATUM,\
        :x->FILIALNR,\
        :x->UID,\
        :x->TM_TIME
#define MCUSTOMERCALLPLANRECALLINWORK_ZEIGERSEL(x) \
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->URRUFZEIT,\
        :x->DATUM,\
        :x->FILIALNR,\
        :x->UID,\
        :x->TM_TIME

/* SqlMacros-Define of MCUSTOMERCALLPLANDAYDRIVER *****************************/

#define MCUSTOMERCALLPLANDAYDRIVER_ZEIGER(x) \
        :x->RUFZEIT,\
        :x->UMKSTATUS,\
        :x->ANRUFSTATUS,\
        :x->ANRUFZAEHLER,\
        :x->TOURID
#define MCUSTOMERCALLPLANDAYDRIVER_ZEIGERSEL(x) \
        :x->NAMEAPO,\
        :x->TELNR,\
        :x->TELNRDAFUE,\
        :x->TELKURZWAHL,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->DATUM,\
        :x->URRUFZEIT,\
        :x->RUFZEIT,\
        :x->UMKSTATUS,\
        :x->ANRUFSTATUS,\
        :x->ANRUFZAEHLER,\
        :x->TAGNR,\
        :x->TOURID,\
        :x->STOURDEFINITIV,\
        :x->RUFPROTOKOLL,\
        :x->RUFSTEUERUNG,\
        :x->POOLNR,\
        :x->MODEMPOOLNR,\
        :x->RUFEINSTELLUNG,\
        :x->ANRUFTYP,\
        :x->SKDANRUFGENERELL,\
        :x->EREIGNIS,\
        :x->UHRZEIT,\
        :x->UID

/* SqlMacros-Define of MCUSTOMERLASTCALL **************************************/

#define MCUSTOMERLASTCALL_ZEIGER(x) \
        :x->UHRZEIT
#define MCUSTOMERLASTCALL_ZEIGERSEL(x) \
        :x->ANRUFSTATUS,\
        :x->UHRZEIT

/* SqlMacros-Define of MCUSTOMERORDER *****************************************/

#define MCUSTOMERORDER_ZEIGER(x) \
        :x->ZEIT
#define MCUSTOMERORDER_ZEIGERSEL(x) \
        :x->KDAUFTRAGNR,\
        :x->KDAUFTRAGSTAT,\
        :x->ZEIT,\
        :x->GERAETNAME,\
        :x->ANZPOS,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR

/* SqlMacros-Define of MDEVICEPLANCHECK ***************************************/

#define MDEVICEPLANCHECK_ZEIGER(x) \
        :x->SEQUENZNR,\
        :x->TERMINALSTATUS,\
        :x->STARTZEIT,\
        :x->ENDEZEIT,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->URRUFZEIT,\
        :x->DATUM,\
        :x->AUFTRAGSTATUS,\
        :x->KDAUFTRAGNR1,\
        :x->AKTIV
#define MDEVICEPLANCHECK_ZEIGERSEL(x) \
        :x->REGIONENTYP,\
        :x->FILIALNR,\
        :x->GERAETEID,\
        :x->SEQUENZNR,\
        :x->GERAETNST,\
        :x->GERAETEVERW1,\
        :x->TERMINALSTATUS,\
        :x->STARTZEIT,\
        :x->ENDEZEIT,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->URRUFZEIT,\
        :x->DATUM,\
        :x->AUFTRAGSTATUS,\
        :x->KDAUFTRAGNR1,\
        :x->POOLNR,\
        :x->UMKNR,\
        :x->AKTIV

/* SqlMacros-Define of MDEVICEPLANDRIVER **************************************/

#define MDEVICEPLANDRIVER_ZEIGER(x) \
        :x->SEQUENZNR,\
        :x->TERMINALSTATUS,\
        :x->STARTZEIT,\
        :x->ENDEZEIT,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->URRUFZEIT,\
        :x->DATUM,\
        :x->AUFTRAGSTATUS,\
        :x->KDAUFTRAGNR1,\
        :x->POOLNR,\
        :x->TOURID,\
        :x->AKTIV,\
        :x->UMKNST
#define MDEVICEPLANDRIVER_ZEIGERSEL(x) \
        :x->FILIALNR,\
        :x->GERAETEID,\
        :x->SEQUENZNR,\
        :x->GERAETEART,\
        :x->GERAETEVERW1,\
        :x->TERMINALSTATUS,\
        :x->MODEMTYP,\
        :x->STARTZEIT,\
        :x->ENDEZEIT,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->URRUFZEIT,\
        :x->DATUM,\
        :x->AUFTRAGSTATUS,\
        :x->KDAUFTRAGNR1,\
        :x->POOLNR,\
        :x->UMKNR,\
        :x->TOURID,\
        :x->AKTIV,\
        :x->UMKNST

/* SqlMacros-Define of MNUMBER ************************************************/

#define MNUMBER_ZEIGER(x) \
        :x->NUMMERWERT
#define MNUMBER_ZEIGERSEL(x) \
        :x->NUMMERTYP,\
        :x->NUMMERWERT,\
        :x->NUMMERMINDEST,\
        :x->NUMMERHOECHST,\
        :x->NUMMERINKREMENT,\
        :x->NUMMERMODUS

/* SqlMacros-Define of MTRANSAKTION *******************************************/

#define MTRANSAKTION_ZEIGER(x) \
        :x->TM_DATE,\
        :x->TM_TIME
#define MTRANSAKTION_ZEIGERSEL(x) \
        :x->TM_DATE,\
        :x->TM_TIME

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CHECKORDEREXIST_H
#define CHECKORDEREXIST_ANZ ( sizeof(CHECKORDEREXIST_BES) / sizeof(struct buf_desc) )
#define MCALLPARAMTERDRIVER_H
#define MCALLPARAMTERDRIVER_ANZ ( sizeof(MCALLPARAMTERDRIVER_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERCALLPLANDAY_H
#define MCUSTOMERCALLPLANDAY_ANZ ( sizeof(MCUSTOMERCALLPLANDAY_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERCALLPLANDAYHIST_H
#define MCUSTOMERCALLPLANDAYHIST_ANZ ( sizeof(MCUSTOMERCALLPLANDAYHIST_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERCALLPLANRECALLINWORK_H
#define MCUSTOMERCALLPLANRECALLINWORK_ANZ ( sizeof(MCUSTOMERCALLPLANRECALLINWORK_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERCALLPLANDAYDRIVER_H
#define MCUSTOMERCALLPLANDAYDRIVER_ANZ ( sizeof(MCUSTOMERCALLPLANDAYDRIVER_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERLASTCALL_H
#define MCUSTOMERLASTCALL_ANZ ( sizeof(MCUSTOMERLASTCALL_BES) / sizeof(struct buf_desc) )
#define MCUSTOMERORDER_H
#define MCUSTOMERORDER_ANZ ( sizeof(MCUSTOMERORDER_BES) / sizeof(struct buf_desc) )
#define MDEVICEPLANCHECK_H
#define MDEVICEPLANCHECK_ANZ ( sizeof(MDEVICEPLANCHECK_BES) / sizeof(struct buf_desc) )
#define MDEVICEPLANDRIVER_H
#define MDEVICEPLANDRIVER_ANZ ( sizeof(MDEVICEPLANDRIVER_BES) / sizeof(struct buf_desc) )
#define MNUMBER_H
#define MNUMBER_ANZ ( sizeof(MNUMBER_BES) / sizeof(struct buf_desc) )
#define MTRANSAKTION_H
#define MTRANSAKTION_ANZ ( sizeof(MTRANSAKTION_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CHECKORDEREXIST *****************************************/

#ifndef TRANSCLASS
typedef struct N_CHECKORDEREXIST {
    long KDAUFTRAGNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long TM_TIME;
} checkorderexistS;
#else /* TRANSCLASS */
typedef struct N_CHECKORDEREXIST {
    long KDAUFTRAGNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long TM_TIME;

    bool operator == (const N_CHECKORDEREXIST& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            TM_TIME == right.TM_TIME
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        TM_TIME = 0;
#endif
    }
} checkorderexistS;
#endif /* TRANSCLASS */

/* original struct of MCALLPARAMTERDRIVER *************************************/

#ifndef TRANSCLASS
typedef struct N_MCALLPARAMTERDRIVER {
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
    char CALLPLANSTARTSTOP[2];
    short STOPSTARTZEIT;
    long FETCH_REL;
} mcallparamterdriverS;
#else /* TRANSCLASS */
typedef struct N_MCALLPARAMTERDRIVER {
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
    char CALLPLANSTARTSTOP[2];
    short STOPSTARTZEIT;
    long FETCH_REL;
    bool operator == (const N_MCALLPARAMTERDRIVER& right) const {
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
        strcpy(CALLPLANSTARTSTOP, " " );
        STOPSTARTZEIT = 0;
#endif
    }
} mcallparamterdriverS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERCALLPLANDAY ************************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERCALLPLANDAY {
    long IDFNR;
    char NAMEAPO[41];
    char ORT[31];
    char TELNR[21];
    char TELKURZWAHL[5];
    char KZKDKLASSE[4];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    char TAGNR[2];
    char TOURID[7];
    char STOURDEFINITIV[2];
    char RUFPROTOKOLL[2];
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG[2];
    char ANRUFTYP[2];
    char SKDANRUFGENERELL[2];
    long FETCH_REL;
} mcustomercallplandayS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERCALLPLANDAY {
    long IDFNR;
    char NAMEAPO[41];
    char ORT[31];
    char TELNR[21];
    char TELKURZWAHL[5];
    char KZKDKLASSE[4];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    char TAGNR[2];
    char TOURID[7];
    char STOURDEFINITIV[2];
    char RUFPROTOKOLL[2];
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG[2];
    char ANRUFTYP[2];
    char SKDANRUFGENERELL[2];
    long FETCH_REL;
    bool operator == (const N_MCUSTOMERCALLPLANDAY& right) const {
        return (
            IDFNR == right.IDFNR &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(TELNR, right.TELNR) &&
            !strcmp(TELKURZWAHL, right.TELKURZWAHL) &&
            !strcmp(KZKDKLASSE, right.KZKDKLASSE) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            DATUM == right.DATUM &&
            URRUFZEIT == right.URRUFZEIT &&
            RUFZEIT == right.RUFZEIT &&
            UMKSTATUS == right.UMKSTATUS &&
            ANRUFSTATUS == right.ANRUFSTATUS &&
            ANRUFZAEHLER == right.ANRUFZAEHLER &&
            !strcmp(TAGNR, right.TAGNR) &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(STOURDEFINITIV, right.STOURDEFINITIV) &&
            !strcmp(RUFPROTOKOLL, right.RUFPROTOKOLL) &&
            RUFSTEUERUNG == right.RUFSTEUERUNG &&
            POOLNR == right.POOLNR &&
            MODEMPOOLNR == right.MODEMPOOLNR &&
            !strcmp(RUFEINSTELLUNG, right.RUFEINSTELLUNG) &&
            !strcmp(ANRUFTYP, right.ANRUFTYP) &&
            !strcmp(SKDANRUFGENERELL, right.SKDANRUFGENERELL)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        IDFNR = 0;
        strcpy(NAMEAPO, " " );
        strcpy(ORT, " " );
        strcpy(TELNR, " " );
        strcpy(TELKURZWAHL, " " );
        strcpy(KZKDKLASSE, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        DATUM = 0;
        URRUFZEIT = 0;
        RUFZEIT = 0;
        UMKSTATUS = 0;
        ANRUFSTATUS = 0;
        ANRUFZAEHLER = 0;
        strcpy(TAGNR, " " );
        strcpy(TOURID, " " );
        strcpy(STOURDEFINITIV, " " );
        strcpy(RUFPROTOKOLL, " " );
        RUFSTEUERUNG = 0;
        POOLNR = 0;
        MODEMPOOLNR = 0;
        strcpy(RUFEINSTELLUNG, " " );
        strcpy(ANRUFTYP, " " );
        strcpy(SKDANRUFGENERELL, " " );
#endif
    }
} mcustomercallplandayS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERCALLPLANDAYHIST ********************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERCALLPLANDAYHIST {
    char USERNAME[9];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    short EREIGNIS;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short FILIALNR;
    long MODEMNR;
    long UHRZEIT;
    char GERAETEID[5];
    long UID;
    long DATUMANLAGE;
    long FETCH_REL;
} mcustomercallplandayhistS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERCALLPLANDAYHIST {
    char USERNAME[9];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    short EREIGNIS;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short FILIALNR;
    long MODEMNR;
    long UHRZEIT;
    char GERAETEID[5];
    long UID;
    long DATUMANLAGE;
    long FETCH_REL;
    bool operator == (const N_MCUSTOMERCALLPLANDAYHIST& right) const {
        return (
            !strcmp(USERNAME, right.USERNAME) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            DATUM == right.DATUM &&
            URRUFZEIT == right.URRUFZEIT &&
            EREIGNIS == right.EREIGNIS &&
            RUFZEIT == right.RUFZEIT &&
            UMKSTATUS == right.UMKSTATUS &&
            ANRUFSTATUS == right.ANRUFSTATUS &&
            FILIALNR == right.FILIALNR &&
            MODEMNR == right.MODEMNR &&
            UHRZEIT == right.UHRZEIT &&
            !strcmp(GERAETEID, right.GERAETEID) &&
            UID == right.UID &&
            DATUMANLAGE == right.DATUMANLAGE
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(USERNAME, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        DATUM = 0;
        URRUFZEIT = 0;
        EREIGNIS = 0;
        RUFZEIT = 0;
        UMKSTATUS = 0;
        ANRUFSTATUS = 0;
        FILIALNR = 0;
        MODEMNR = 0;
        UHRZEIT = 0;
        strcpy(GERAETEID, " " );
        UID = 0;
        DATUMANLAGE = 0;
#endif
    }
} mcustomercallplandayhistS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERCALLPLANRECALLINWORK ***************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERCALLPLANRECALLINWORK {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long URRUFZEIT;
    long DATUM;
    short FILIALNR;
    long UID;
    long TM_TIME;
} mcustomercallplanrecallinworkS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERCALLPLANRECALLINWORK {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long URRUFZEIT;
    long DATUM;
    short FILIALNR;
    long UID;
    long TM_TIME;

    bool operator == (const N_MCUSTOMERCALLPLANRECALLINWORK& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            URRUFZEIT == right.URRUFZEIT &&
            DATUM == right.DATUM &&
            FILIALNR == right.FILIALNR &&
            UID == right.UID &&
            TM_TIME == right.TM_TIME
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        URRUFZEIT = 0;
        DATUM = 0;
        FILIALNR = 0;
        UID = 0;
        TM_TIME = 0;
#endif
    }
} mcustomercallplanrecallinworkS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERCALLPLANDAYDRIVER ******************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERCALLPLANDAYDRIVER {
    char NAMEAPO[41];
    char TELNR[21];
    char TELNRDAFUE[21];
    char TELKURZWAHL[5];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    char TAGNR[2];
    char TOURID[7];
    char STOURDEFINITIV[2];
    char RUFPROTOKOLL[2];
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG[2];
    char ANRUFTYP[2];
    char SKDANRUFGENERELL[2];
    short EREIGNIS;
    long UHRZEIT;
    char GERAETEID[5];
    long UID;
    long FETCH_REL;
} mcustomercallplandaydriverS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERCALLPLANDAYDRIVER {
    char NAMEAPO[41];
    char TELNR[21];
    char TELNRDAFUE[21];
    char TELKURZWAHL[5];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    char TAGNR[2];
    char TOURID[7];
    char STOURDEFINITIV[2];
    char RUFPROTOKOLL[2];
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG[2];
    char ANRUFTYP[2];
    char SKDANRUFGENERELL[2];
    short EREIGNIS;
    long UHRZEIT;
    char GERAETEID[5];
    long UID;
    long FETCH_REL;
    bool operator == (const N_MCUSTOMERCALLPLANDAYDRIVER& right) const {
        return (
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(TELNR, right.TELNR) &&
            !strcmp(TELNRDAFUE, right.TELNRDAFUE) &&
            !strcmp(TELKURZWAHL, right.TELKURZWAHL) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            DATUM == right.DATUM &&
            URRUFZEIT == right.URRUFZEIT &&
            RUFZEIT == right.RUFZEIT &&
            UMKSTATUS == right.UMKSTATUS &&
            ANRUFSTATUS == right.ANRUFSTATUS &&
            ANRUFZAEHLER == right.ANRUFZAEHLER &&
            !strcmp(TAGNR, right.TAGNR) &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(STOURDEFINITIV, right.STOURDEFINITIV) &&
            !strcmp(RUFPROTOKOLL, right.RUFPROTOKOLL) &&
            RUFSTEUERUNG == right.RUFSTEUERUNG &&
            POOLNR == right.POOLNR &&
            MODEMPOOLNR == right.MODEMPOOLNR &&
            !strcmp(RUFEINSTELLUNG, right.RUFEINSTELLUNG) &&
            !strcmp(ANRUFTYP, right.ANRUFTYP) &&
            !strcmp(SKDANRUFGENERELL, right.SKDANRUFGENERELL) &&
            EREIGNIS == right.EREIGNIS &&
            UHRZEIT == right.UHRZEIT &&
            !strcmp(GERAETEID, right.GERAETEID) &&
            UID == right.UID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(NAMEAPO, " " );
        strcpy(TELNR, " " );
        strcpy(TELNRDAFUE, " " );
        strcpy(TELKURZWAHL, " " );
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        DATUM = 0;
        URRUFZEIT = 0;
        RUFZEIT = 0;
        UMKSTATUS = 0;
        ANRUFSTATUS = 0;
        ANRUFZAEHLER = 0;
        strcpy(TAGNR, " " );
        strcpy(TOURID, " " );
        strcpy(STOURDEFINITIV, " " );
        strcpy(RUFPROTOKOLL, " " );
        RUFSTEUERUNG = 0;
        POOLNR = 0;
        MODEMPOOLNR = 0;
        strcpy(RUFEINSTELLUNG, " " );
        strcpy(ANRUFTYP, " " );
        strcpy(SKDANRUFGENERELL, " " );
        EREIGNIS = 0;
        UHRZEIT = 0;
        strcpy(GERAETEID, " " );
        UID = 0;
#endif
    }
} mcustomercallplandaydriverS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERLASTCALL ***************************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERLASTCALL {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    short ANRUFSTATUS;
    long UHRZEIT;
} mcustomerlastcallS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERLASTCALL {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    short ANRUFSTATUS;
    long UHRZEIT;

    bool operator == (const N_MCUSTOMERLASTCALL& right) const {
        return (
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            DATUM == right.DATUM &&
            URRUFZEIT == right.URRUFZEIT &&
            ANRUFSTATUS == right.ANRUFSTATUS &&
            UHRZEIT == right.UHRZEIT
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        DATUM = 0;
        URRUFZEIT = 0;
        ANRUFSTATUS = 0;
        UHRZEIT = 0;
#endif
    }
} mcustomerlastcallS;
#endif /* TRANSCLASS */

/* original struct of MCUSTOMERORDER ******************************************/

#ifndef TRANSCLASS
typedef struct N_MCUSTOMERORDER {
    long KDAUFTRAGNR;
    char KDAUFTRAGSTAT[17];
    long ZEIT;
    char GERAETNAME[9];
    long ANZPOS;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
} mcustomerorderS;
#else /* TRANSCLASS */
typedef struct N_MCUSTOMERORDER {
    long KDAUFTRAGNR;
    char KDAUFTRAGSTAT[17];
    long ZEIT;
    char GERAETNAME[9];
    long ANZPOS;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;

    bool operator == (const N_MCUSTOMERORDER& right) const {
        return (
            KDAUFTRAGNR == right.KDAUFTRAGNR &&
            !strcmp(KDAUFTRAGSTAT, right.KDAUFTRAGSTAT) &&
            ZEIT == right.ZEIT &&
            !strcmp(GERAETNAME, right.GERAETNAME) &&
            ANZPOS == right.ANZPOS &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        KDAUFTRAGNR = 0;
        strcpy(KDAUFTRAGSTAT, " " );
        ZEIT = 0;
        strcpy(GERAETNAME, " " );
        ANZPOS = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
#endif
    }
} mcustomerorderS;
#endif /* TRANSCLASS */

/* original struct of MDEVICEPLANCHECK ****************************************/

#ifndef TRANSCLASS
typedef struct N_MDEVICEPLANCHECK {
    short REGIONENTYP;
    short FILIALNR;
    char GERAETEID[5];
    long SEQUENZNR;
    long GERAETNST;
    char GERAETEVERW1[2];
    char TERMINALSTATUS[2];
    long STARTZEIT;
    long ENDEZEIT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long URRUFZEIT;
    long DATUM;
    char AUFTRAGSTATUS[2];
    long KDAUFTRAGNR1;
    short POOLNR;
    short UMKNR;
    char AKTIV[2];
    long FETCH_REL;
} mdeviceplancheckS;
#else /* TRANSCLASS */
typedef struct N_MDEVICEPLANCHECK {
    short REGIONENTYP;
    short FILIALNR;
    char GERAETEID[5];
    long SEQUENZNR;
    long GERAETNST;
    char GERAETEVERW1[2];
    char TERMINALSTATUS[2];
    long STARTZEIT;
    long ENDEZEIT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long URRUFZEIT;
    long DATUM;
    char AUFTRAGSTATUS[2];
    long KDAUFTRAGNR1;
    short POOLNR;
    short UMKNR;
    char AKTIV[2];
    long FETCH_REL;
    bool operator == (const N_MDEVICEPLANCHECK& right) const {
        return (
            REGIONENTYP == right.REGIONENTYP &&
            FILIALNR == right.FILIALNR &&
            !strcmp(GERAETEID, right.GERAETEID) &&
            SEQUENZNR == right.SEQUENZNR &&
            GERAETNST == right.GERAETNST &&
            !strcmp(GERAETEVERW1, right.GERAETEVERW1) &&
            !strcmp(TERMINALSTATUS, right.TERMINALSTATUS) &&
            STARTZEIT == right.STARTZEIT &&
            ENDEZEIT == right.ENDEZEIT &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            URRUFZEIT == right.URRUFZEIT &&
            DATUM == right.DATUM &&
            !strcmp(AUFTRAGSTATUS, right.AUFTRAGSTATUS) &&
            KDAUFTRAGNR1 == right.KDAUFTRAGNR1 &&
            POOLNR == right.POOLNR &&
            UMKNR == right.UMKNR &&
            !strcmp(AKTIV, right.AKTIV)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REGIONENTYP = 0;
        FILIALNR = 0;
        strcpy(GERAETEID, " " );
        SEQUENZNR = 0;
        GERAETNST = 0;
        strcpy(GERAETEVERW1, " " );
        strcpy(TERMINALSTATUS, " " );
        STARTZEIT = 0;
        ENDEZEIT = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        URRUFZEIT = 0;
        DATUM = 0;
        strcpy(AUFTRAGSTATUS, " " );
        KDAUFTRAGNR1 = 0;
        POOLNR = 0;
        UMKNR = 0;
        strcpy(AKTIV, " " );
#endif
    }
} mdeviceplancheckS;
#endif /* TRANSCLASS */

/* original struct of MDEVICEPLANDRIVER ***************************************/

#ifndef TRANSCLASS
typedef struct N_MDEVICEPLANDRIVER {
    short REGIONENTYP;
    long SCHLUESSEL;
    short FILIALNR;
    char GERAETEID[5];
    long SEQUENZNR;
    char GERAETEART[2];
    char GERAETEVERW1[2];
    char TERMINALSTATUS[2];
    char MODEMTYP[2];
    long STARTZEIT;
    long ENDEZEIT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long URRUFZEIT;
    long DATUM;
    char AUFTRAGSTATUS[2];
    long KDAUFTRAGNR1;
    short POOLNR;
    short UMKNR;
    char TOURID[7];
    char AKTIV[2];
    short UMKNST;
    long FETCH_REL;
} mdeviceplandriverS;
#else /* TRANSCLASS */
typedef struct N_MDEVICEPLANDRIVER {
    short REGIONENTYP;
    long SCHLUESSEL;
    short FILIALNR;
    char GERAETEID[5];
    long SEQUENZNR;
    char GERAETEART[2];
    char GERAETEVERW1[2];
    char TERMINALSTATUS[2];
    char MODEMTYP[2];
    long STARTZEIT;
    long ENDEZEIT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long URRUFZEIT;
    long DATUM;
    char AUFTRAGSTATUS[2];
    long KDAUFTRAGNR1;
    short POOLNR;
    short UMKNR;
    char TOURID[7];
    char AKTIV[2];
    short UMKNST;
    long FETCH_REL;
    bool operator == (const N_MDEVICEPLANDRIVER& right) const {
        return (
            REGIONENTYP == right.REGIONENTYP &&
            SCHLUESSEL == right.SCHLUESSEL &&
            FILIALNR == right.FILIALNR &&
            !strcmp(GERAETEID, right.GERAETEID) &&
            SEQUENZNR == right.SEQUENZNR &&
            !strcmp(GERAETEART, right.GERAETEART) &&
            !strcmp(GERAETEVERW1, right.GERAETEVERW1) &&
            !strcmp(TERMINALSTATUS, right.TERMINALSTATUS) &&
            !strcmp(MODEMTYP, right.MODEMTYP) &&
            STARTZEIT == right.STARTZEIT &&
            ENDEZEIT == right.ENDEZEIT &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            URRUFZEIT == right.URRUFZEIT &&
            DATUM == right.DATUM &&
            !strcmp(AUFTRAGSTATUS, right.AUFTRAGSTATUS) &&
            KDAUFTRAGNR1 == right.KDAUFTRAGNR1 &&
            POOLNR == right.POOLNR &&
            UMKNR == right.UMKNR &&
            !strcmp(TOURID, right.TOURID) &&
            !strcmp(AKTIV, right.AKTIV) &&
            UMKNST == right.UMKNST
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REGIONENTYP = 0;
        SCHLUESSEL = 0;
        FILIALNR = 0;
        strcpy(GERAETEID, " " );
        SEQUENZNR = 0;
        strcpy(GERAETEART, " " );
        strcpy(GERAETEVERW1, " " );
        strcpy(TERMINALSTATUS, " " );
        strcpy(MODEMTYP, " " );
        STARTZEIT = 0;
        ENDEZEIT = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        URRUFZEIT = 0;
        DATUM = 0;
        strcpy(AUFTRAGSTATUS, " " );
        KDAUFTRAGNR1 = 0;
        POOLNR = 0;
        UMKNR = 0;
        strcpy(TOURID, " " );
        strcpy(AKTIV, " " );
        UMKNST = 0;
#endif
    }
} mdeviceplandriverS;
#endif /* TRANSCLASS */

/* original struct of MNUMBER *************************************************/

#ifndef TRANSCLASS
typedef struct N_MNUMBER {
    short NUMMERTYP;
    long NUMMERWERT;
    long NUMMERMINDEST;
    long NUMMERHOECHST;
    long NUMMERINKREMENT;
    short NUMMERMODUS;
} mnumberS;
#else /* TRANSCLASS */
typedef struct N_MNUMBER {
    short NUMMERTYP;
    long NUMMERWERT;
    long NUMMERMINDEST;
    long NUMMERHOECHST;
    long NUMMERINKREMENT;
    short NUMMERMODUS;

    bool operator == (const N_MNUMBER& right) const {
        return (
            NUMMERTYP == right.NUMMERTYP &&
            NUMMERWERT == right.NUMMERWERT &&
            NUMMERMINDEST == right.NUMMERMINDEST &&
            NUMMERHOECHST == right.NUMMERHOECHST &&
            NUMMERINKREMENT == right.NUMMERINKREMENT &&
            NUMMERMODUS == right.NUMMERMODUS
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        NUMMERTYP = 0;
        NUMMERWERT = 0;
        NUMMERMINDEST = 0;
        NUMMERHOECHST = 0;
        NUMMERINKREMENT = 0;
        NUMMERMODUS = 0;
#endif
    }
} mnumberS;
#endif /* TRANSCLASS */

/* original struct of MTRANSAKTION ********************************************/

#ifndef TRANSCLASS
typedef struct N_MTRANSAKTION {
    long TM_DATE;
    long TM_TIME;
} mtransaktionS;
#else /* TRANSCLASS */
typedef struct N_MTRANSAKTION {
    long TM_DATE;
    long TM_TIME;

    bool operator == (const N_MTRANSAKTION& right) const {
        return (
            TM_DATE == right.TM_DATE &&
            TM_TIME == right.TM_TIME
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        TM_DATE = 0;
        TM_TIME = 0;
#endif
    }
} mtransaktionS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CHECKORDEREXIST *****************************/

struct C_CHECKORDEREXIST {
    long KDAUFTRAGNR;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long TM_TIME;
};
/* Structur with real chartype of MCALLPARAMTERDRIVER *************************/

struct C_MCALLPARAMTERDRIVER {
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
    char CALLPLANSTARTSTOP;
    short STOPSTARTZEIT;
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMERCALLPLANDAY ************************/

struct C_MCUSTOMERCALLPLANDAY {
    long IDFNR;
    char NAMEAPO[41];
    char ORT[31];
    char TELNR[21];
    char TELKURZWAHL[5];
    char KZKDKLASSE[4];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    char TAGNR;
    char TOURID[7];
    char STOURDEFINITIV;
    char RUFPROTOKOLL;
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG;
    char ANRUFTYP;
    char SKDANRUFGENERELL;
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMERCALLPLANDAYHIST ********************/

struct C_MCUSTOMERCALLPLANDAYHIST {
    char USERNAME[9];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    short EREIGNIS;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short FILIALNR;
    long MODEMNR;
    long UHRZEIT;
    char GERAETEID[5];
    long UID;
    long DATUMANLAGE;
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMERCALLPLANRECALLINWORK ***************/

struct C_MCUSTOMERCALLPLANRECALLINWORK {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long URRUFZEIT;
    long DATUM;
    short FILIALNR;
    long UID;
    long TM_TIME;
};
/* Structur with real chartype of MCUSTOMERCALLPLANDAYDRIVER ******************/

struct C_MCUSTOMERCALLPLANDAYDRIVER {
    char NAMEAPO[41];
    char TELNR[21];
    char TELNRDAFUE[21];
    char TELKURZWAHL[5];
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    long RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    char TAGNR;
    char TOURID[7];
    char STOURDEFINITIV;
    char RUFPROTOKOLL;
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    char RUFEINSTELLUNG;
    char ANRUFTYP;
    char SKDANRUFGENERELL;
    short EREIGNIS;
    long UHRZEIT;
    char GERAETEID[5];
    long UID;
    long FETCH_REL;
};
/* Structur with real chartype of MCUSTOMERLASTCALL ***************************/

struct C_MCUSTOMERLASTCALL {
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long DATUM;
    long URRUFZEIT;
    short ANRUFSTATUS;
    long UHRZEIT;
};
/* Structur with real chartype of MCUSTOMERORDER ******************************/

struct C_MCUSTOMERORDER {
    long KDAUFTRAGNR;
    char KDAUFTRAGSTAT[17];
    long ZEIT;
    char GERAETNAME[9];
    long ANZPOS;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
};
/* Structur with real chartype of MDEVICEPLANCHECK ****************************/

struct C_MDEVICEPLANCHECK {
    short REGIONENTYP;
    short FILIALNR;
    char GERAETEID[5];
    long SEQUENZNR;
    long GERAETNST;
    char GERAETEVERW1;
    char TERMINALSTATUS;
    long STARTZEIT;
    long ENDEZEIT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long URRUFZEIT;
    long DATUM;
    char AUFTRAGSTATUS;
    long KDAUFTRAGNR1;
    short POOLNR;
    short UMKNR;
    char AKTIV;
    long FETCH_REL;
};
/* Structur with real chartype of MDEVICEPLANDRIVER ***************************/

struct C_MDEVICEPLANDRIVER {
    short REGIONENTYP;
    long SCHLUESSEL;
    short FILIALNR;
    char GERAETEID[5];
    long SEQUENZNR;
    char GERAETEART;
    char GERAETEVERW1;
    char TERMINALSTATUS;
    char MODEMTYP;
    long STARTZEIT;
    long ENDEZEIT;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    long URRUFZEIT;
    long DATUM;
    char AUFTRAGSTATUS;
    long KDAUFTRAGNR1;
    short POOLNR;
    short UMKNR;
    char TOURID[7];
    char AKTIV;
    short UMKNST;
    long FETCH_REL;
};
/* Structur with real chartype of MNUMBER *************************************/

struct C_MNUMBER {
    short NUMMERTYP;
    long NUMMERWERT;
    long NUMMERMINDEST;
    long NUMMERHOECHST;
    long NUMMERINKREMENT;
    short NUMMERMODUS;
};
/* Structur with real chartype of MTRANSAKTION ********************************/

struct C_MTRANSAKTION {
    long TM_DATE;
    long TM_TIME;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CHECKORDEREXIST ***************************/

struct I_CHECKORDEREXIST {
    short KDAUFTRAGNR;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short TM_TIME;
};
/* Sizetype  Structur (buf_desc) of MCALLPARAMTERDRIVER ***********************/

struct I_MCALLPARAMTERDRIVER {
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
    short CALLPLANSTARTSTOP;
    short STOPSTARTZEIT;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERCALLPLANDAY **********************/

struct I_MCUSTOMERCALLPLANDAY {
    short IDFNR;
    short NAMEAPO;
    short ORT;
    short TELNR;
    short TELKURZWAHL;
    short KZKDKLASSE;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short DATUM;
    short URRUFZEIT;
    short RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    short TAGNR;
    short TOURID;
    short STOURDEFINITIV;
    short RUFPROTOKOLL;
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    short RUFEINSTELLUNG;
    short ANRUFTYP;
    short SKDANRUFGENERELL;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERCALLPLANDAYHIST ******************/

struct I_MCUSTOMERCALLPLANDAYHIST {
    short USERNAME;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short DATUM;
    short URRUFZEIT;
    short EREIGNIS;
    short RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short FILIALNR;
    short MODEMNR;
    short UHRZEIT;
    short GERAETEID;
    short UID;
    short DATUMANLAGE;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERCALLPLANRECALLINWORK *************/

struct I_MCUSTOMERCALLPLANRECALLINWORK {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short URRUFZEIT;
    short DATUM;
    short FILIALNR;
    short UID;
    short TM_TIME;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERCALLPLANDAYDRIVER ****************/

struct I_MCUSTOMERCALLPLANDAYDRIVER {
    short NAMEAPO;
    short TELNR;
    short TELNRDAFUE;
    short TELKURZWAHL;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short DATUM;
    short URRUFZEIT;
    short RUFZEIT;
    short UMKSTATUS;
    short ANRUFSTATUS;
    short ANRUFZAEHLER;
    short TAGNR;
    short TOURID;
    short STOURDEFINITIV;
    short RUFPROTOKOLL;
    short RUFSTEUERUNG;
    short POOLNR;
    short MODEMPOOLNR;
    short RUFEINSTELLUNG;
    short ANRUFTYP;
    short SKDANRUFGENERELL;
    short EREIGNIS;
    short UHRZEIT;
    short GERAETEID;
    short UID;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERLASTCALL *************************/

struct I_MCUSTOMERLASTCALL {
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short DATUM;
    short URRUFZEIT;
    short ANRUFSTATUS;
    short UHRZEIT;
};
/* Sizetype  Structur (buf_desc) of MCUSTOMERORDER ****************************/

struct I_MCUSTOMERORDER {
    short KDAUFTRAGNR;
    short KDAUFTRAGSTAT;
    short ZEIT;
    short GERAETNAME;
    short ANZPOS;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
};
/* Sizetype  Structur (buf_desc) of MDEVICEPLANCHECK **************************/

struct I_MDEVICEPLANCHECK {
    short REGIONENTYP;
    short FILIALNR;
    short GERAETEID;
    short SEQUENZNR;
    short GERAETNST;
    short GERAETEVERW1;
    short TERMINALSTATUS;
    short STARTZEIT;
    short ENDEZEIT;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short URRUFZEIT;
    short DATUM;
    short AUFTRAGSTATUS;
    short KDAUFTRAGNR1;
    short POOLNR;
    short UMKNR;
    short AKTIV;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MDEVICEPLANDRIVER *************************/

struct I_MDEVICEPLANDRIVER {
    short REGIONENTYP;
    short SCHLUESSEL;
    short FILIALNR;
    short GERAETEID;
    short SEQUENZNR;
    short GERAETEART;
    short GERAETEVERW1;
    short TERMINALSTATUS;
    short MODEMTYP;
    short STARTZEIT;
    short ENDEZEIT;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short URRUFZEIT;
    short DATUM;
    short AUFTRAGSTATUS;
    short KDAUFTRAGNR1;
    short POOLNR;
    short UMKNR;
    short TOURID;
    short AKTIV;
    short UMKNST;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of MNUMBER ***********************************/

struct I_MNUMBER {
    short NUMMERTYP;
    short NUMMERWERT;
    short NUMMERMINDEST;
    short NUMMERHOECHST;
    short NUMMERINKREMENT;
    short NUMMERMODUS;
};
/* Sizetype  Structur (buf_desc) of MTRANSAKTION ******************************/

struct I_MTRANSAKTION {
    short TM_DATE;
    short TM_TIME;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CHECKORDEREXIST *************************************/

#if defined (BUF_DESC)
static struct buf_desc CHECKORDEREXIST_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CHECKORDEREXIST_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCALLPARAMTERDRIVER *********************************/

#if defined (BUF_DESC)
static struct buf_desc MCALLPARAMTERDRIVER_BES [] = {
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
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCALLPARAMTERDRIVER_BES [] = {
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
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERCALLPLANDAY ********************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANDAY_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 4, 0 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANDAY_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 4, 0 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERCALLPLANDAYHIST ****************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANDAYHIST_BES [] = {
   { TYP_C, 8, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANDAYHIST_BES [] = {
   { TYP_C, 8, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERCALLPLANRECALLINWORK ***********************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANRECALLINWORK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANRECALLINWORK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERCALLPLANDAYDRIVER **************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANDAYDRIVER_BES [] = {
   { TYP_C, 40, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERCALLPLANDAYDRIVER_BES [] = {
   { TYP_C, 40, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERLASTCALL ***********************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERLASTCALL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERLASTCALL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MCUSTOMERORDER **************************************/

#if defined (BUF_DESC)
static struct buf_desc MCUSTOMERORDER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 16, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 8, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MCUSTOMERORDER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 16, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 8, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MDEVICEPLANCHECK ************************************/

#if defined (BUF_DESC)
static struct buf_desc MDEVICEPLANCHECK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MDEVICEPLANCHECK_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MDEVICEPLANDRIVER ***********************************/

#if defined (BUF_DESC)
static struct buf_desc MDEVICEPLANDRIVER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MDEVICEPLANDRIVER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 4, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of MNUMBER *********************************************/

#if defined (BUF_DESC)
static struct buf_desc MNUMBER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MNUMBER_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* Structur (buf_desc) of MTRANSAKTION ****************************************/

#if defined (BUF_DESC)
static struct buf_desc MTRANSAKTION_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc MTRANSAKTION_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of CheckOrderExist ***********************************/

#define CHECKORDEREXIST_SELAUFTRAG 1312

/* FunctionNumber-Define of MCallParamterDriver *******************************/

#define MCALLPARAMTERDRIVER_SELPARAMETER 1128
#define MCALLPARAMTERDRIVER_SETCALLSTOFINISH 1257
#define MCALLPARAMTERDRIVER_UPDTIME 1260

/* FunctionNumber-Define of MCustomerCallPlanDay ******************************/

#define MCUSTOMERCALLPLANDAY_ENDBROWSE 1090
#define MCUSTOMERCALLPLANDAY_INSERT 1088
#define MCUSTOMERCALLPLANDAY_SELCALLPLANDAY 1162
#define MCUSTOMERCALLPLANDAY_SELLIST 1087
#define MCUSTOMERCALLPLANDAY_SELLISTFUTURE 1164
#define MCUSTOMERCALLPLANDAY_SELLISTHIST 1168
#define MCUSTOMERCALLPLANDAY_SETCUSTOMERCALLFREE 1239
#define MCUSTOMERCALLPLANDAY_STARTBROWSE 1089
#define MCUSTOMERCALLPLANDAY_UPDCUSTOMERCALLPLANDAY 1091

/* FunctionNumber-Define of MCustomerCallPlanDayHist **************************/

#define MCUSTOMERCALLPLANDAYHIST_DELALL 1166
#define MCUSTOMERCALLPLANDAYHIST_DELALLOLDER 1229
#define MCUSTOMERCALLPLANDAYHIST_SELLIST 1165

/* FunctionNumber-Define of MCustomerCallPlanRecallInWork *********************/

#define MCUSTOMERCALLPLANRECALLINWORK_DELETE 1189
#define MCUSTOMERCALLPLANRECALLINWORK_INSERT 1187
#define MCUSTOMERCALLPLANRECALLINWORK_SELECT 1190
#define MCUSTOMERCALLPLANRECALLINWORK_UPDATE 1188

/* FunctionNumber-Define of MCustomerCallplanDayDriver ************************/

#define MCUSTOMERCALLPLANDAYDRIVER_ENDBROWSE 1145
#define MCUSTOMERCALLPLANDAYDRIVER_SELLIST 1148
#define MCUSTOMERCALLPLANDAYDRIVER_SELUNICUSTOMERCALLPLAN 1183
#define MCUSTOMERCALLPLANDAYDRIVER_STARTBROWSE 1144
#define MCUSTOMERCALLPLANDAYDRIVER_UPDCUSTOMERCALLPLAN 1147
#define MCUSTOMERCALLPLANDAYDRIVER_UPDCUSTOMERCALLPLANWITHOUTTRANSACTION 1200
#define MCUSTOMERCALLPLANDAYDRIVER_UPDWITHOUTTRANSACTION 1149

/* FunctionNumber-Define of MCustomerLastCall *********************************/

#define MCUSTOMERLASTCALL_ENDBROWSE 1206
#define MCUSTOMERLASTCALL_SELCUSTOMERCALLSTATE 1205
#define MCUSTOMERLASTCALL_STARTBROWSE 1204

/* FunctionNumber-Define of MCustomerOrder ************************************/

#define MCUSTOMERORDER_ENDBROWSE 1157
#define MCUSTOMERORDER_SELAVAILABLEORDER 1279
#define MCUSTOMERORDER_SELCUSTOMERCALLED 1194
#define MCUSTOMERORDER_SELDEVICEORDER 1159
#define MCUSTOMERORDER_STARTBROWSE 1156

/* FunctionNumber-Define of MDevicePlanCheck **********************************/

#define MDEVICEPLANCHECK_SELDEVICEID 1240
#define MDEVICEPLANCHECK_SELLIST 1116
#define MDEVICEPLANCHECK_SELLISTHIST 1199
#define MDEVICEPLANCHECK_UPDUMKDECIVEPLAN 1196
#define MDEVICEPLANCHECK_UPDATEDIRECT 1221

/* FunctionNumber-Define of MDevicePlanDriver *********************************/

#define MDEVICEPLANDRIVER_ENDBROWSE 1136
#define MDEVICEPLANDRIVER_SELLIST 1134
#define MDEVICEPLANDRIVER_SELWITHSEQUENZNO 1182
#define MDEVICEPLANDRIVER_STARTBROWSE 1133
#define MDEVICEPLANDRIVER_UPDDEVICEPLAN 1135
#define MDEVICEPLANDRIVER_UPDUMKDEVICEPLAN 1197
#define MDEVICEPLANDRIVER_UPDWITHOUTTRANSACTION 1137
#define MDEVICEPLANDRIVER_UPDWITHOUTTRANSACTIONDIRECT 1184

/* FunctionNumber-Define of MNumber *******************************************/

#define MNUMBER_INCREMENT 1143
#define MNUMBER_INSERT 1150
#define MNUMBER_SELNUMBER 1141
#define MNUMBER_UPDNUMBER 1142

/* FunctionNumber-Define of MTransaktion **************************************/

#define MTRANSAKTION_BEGINTRANSACTION 1138
#define MTRANSAKTION_ENDTRANSACTION 1139
#define MTRANSAKTION_GETDATE 1153
#define MTRANSAKTION_GETDATETIME 1151
#define MTRANSAKTION_GETTIME 1152
#define MTRANSAKTION_ROLLBACKTRANSACTION 1140
#define MTRANSAKTION_SETCOMMITEDREAD 1155
#define MTRANSAKTION_SETDIRTYREAD 1154

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CheckOrderExist *******************************/

#define SelAuftrag 1312

/* Old-FunctionNumber-Define of MCallParamterDriver ***************************/

#define SelParameter 1128
#define SetCallsToFinish 1257
#define UpdTime 1260

/* Old-FunctionNumber-Define of MCustomerCallPlanDay **************************/

#define EndBrowse 1090
#define Insert 1088
#define SelCallPlanDay 1162
#define SelList 1087
#define SelListFuture 1164
#define SelListHist 1168
#define SetCustomerCallFree 1239
#define StartBrowse 1089
#define UpdCustomerCallPlanDay 1091

/* Old-FunctionNumber-Define of MCustomerCallPlanDayHist **********************/

#define DelAll 1166
#define DelAllOlder 1229
#define SelList 1165

/* Old-FunctionNumber-Define of MCustomerCallPlanRecallInWork *****************/

#define Delete 1189
#define Insert 1187
#define Select 1190
#define Update 1188

/* Old-FunctionNumber-Define of MCustomerCallplanDayDriver ********************/

#define EndBrowse 1145
#define SelList 1148
#define SelUniCustomerCallplan 1183
#define StartBrowse 1144
#define UpdCustomerCallplan 1147
#define UpdCustomerCallplanWithoutTransaction 1200
#define UpdWithoutTransaction 1149

/* Old-FunctionNumber-Define of MCustomerLastCall *****************************/

#define EndBrowse 1206
#define SelCustomerCallState 1205
#define StartBrowse 1204

/* Old-FunctionNumber-Define of MCustomerOrder ********************************/

#define EndBrowse 1157
#define SelAvailableOrder 1279
#define SelCustomerCalled 1194
#define SelDeviceOrder 1159
#define StartBrowse 1156

/* Old-FunctionNumber-Define of MDevicePlanCheck ******************************/

#define SelDeviceID 1240
#define SelList 1116
#define SelListHist 1199
#define UpdUMKDecivePlan 1196
#define UpdateDirect 1221

/* Old-FunctionNumber-Define of MDevicePlanDriver *****************************/

#define EndBrowse 1136
#define SelList 1134
#define SelWithSequenzNo 1182
#define StartBrowse 1133
#define UpdDevicePlan 1135
#define UpdUMKDevicePlan 1197
#define UpdWithoutTransaction 1137
#define UpdWithoutTransactionDirect 1184

/* Old-FunctionNumber-Define of MNumber ***************************************/

#define Increment 1143
#define Insert 1150
#define SelNumber 1141
#define UpdNumber 1142

/* Old-FunctionNumber-Define of MTransaktion **********************************/

#define BeginTransaction 1138
#define EndTransaction 1139
#define GetDate 1153
#define GetDateTime 1151
#define GetTime 1152
#define RollbackTransaction 1140
#define SetCommitedRead 1155
#define SetDirtyRead 1154

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

class CCHECKORDEREXIST : public ppDadeVirtual {
public:
    checkorderexistS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<checkorderexistS> lst; // class list

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
                     vector< checkorderexistS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     checkorderexistS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< checkorderexistS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<checkorderexistS>::iterator
                 beginList() { return lst.begin(); }
    vector<checkorderexistS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetTm_time() const { return s.TM_TIME; }

    const checkorderexistS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }

    void         SetStruct(const checkorderexistS & t) { s = t; }

    int          SelAuftrag(int pos = 0) { int ret = UniqueServerCall(1312, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCHECKORDEREXIST() {
        ::buf_default((void *)&s, CHECKORDEREXIST_BES, CHECKORDEREXIST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCHECKORDEREXIST() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CHECKORDEREXIST_BES, CHECKORDEREXIST_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1312 ) return UniqueServerCall(1312, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CHECKORDEREXIST & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CHECKORDEREXIST_BES, (int)CHECKORDEREXIST_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CMCALLPARAMTERDRIVER : public ppDadeVirtual {
public:
    mcallparamterdriverS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcallparamterdriverS> lst; // class list

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
                     vector< mcallparamterdriverS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcallparamterdriverS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcallparamterdriverS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcallparamterdriverS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcallparamterdriverS>::iterator
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
    char         GetCallplanstartstop() const { return s.CALLPLANSTARTSTOP[0]; }
    short        GetStopstartzeit() const { return s.STOPSTARTZEIT; }

    const mcallparamterdriverS &
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
    void         SetCallplanstartstop(char t) { s.CALLPLANSTARTSTOP[0] = t; s.CALLPLANSTARTSTOP[1] = '\0';}
    void         SetStopstartzeit(short t) { s.STOPSTARTZEIT = t; }

    void         SetStruct(const mcallparamterdriverS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelParameter(int pos = 0) { int ret = UniqueServerCall(1128, pos); Strip(s); return ret; }
    int          SetCallsToFinish(int pos = 0) { int ret = UniqueServerCall(1257, pos); Strip(s); return ret; }
    int          UpdTime(int pos = 0) { int ret = UniqueServerCall(1260, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCALLPARAMTERDRIVER() {
        ::buf_default((void *)&s, MCALLPARAMTERDRIVER_BES, MCALLPARAMTERDRIVER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCALLPARAMTERDRIVER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCALLPARAMTERDRIVER_BES, MCALLPARAMTERDRIVER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPARAMTERDRIVER_BES, (int)MCALLPARAMTERDRIVER_ANZ, error_msg);
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
        if ( fkt_nr == 1128 ) return UniqueServerCall(1128, pos);
        if ( fkt_nr == 1257 ) return UniqueServerCall(1257, pos);
        if ( fkt_nr == 1260 ) return UniqueServerCall(1260, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCALLPARAMTERDRIVER & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCALLPARAMTERDRIVER_BES, (int)MCALLPARAMTERDRIVER_ANZ, error_msg);
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
        CMCALLPARAMTERDRIVER c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCALLPARAMTERDRIVER_BES, (int)MCALLPARAMTERDRIVER_ANZ, error_msg);
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

class CMCUSTOMERCALLPLANDAY : public ppDadeVirtual {
public:
    mcustomercallplandayS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomercallplandayS> lst; // class list

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
                     vector< mcustomercallplandayS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomercallplandayS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomercallplandayS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomercallplandayS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomercallplandayS>::iterator
                 endList  () { return lst.end  (); }

    long         GetIdfnr() const { return s.IDFNR; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelnr(ppString & t) const { t = s.TELNR; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelkurzwahl(ppString & t) const { t = s.TELKURZWAHL; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKzkdklasse(ppString & t) const { t = s.KZKDKLASSE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetUrrufzeit() const { return s.URRUFZEIT; }
    long         GetRufzeit() const { return s.RUFZEIT; }
    short        GetUmkstatus() const { return s.UMKSTATUS; }
    short        GetAnrufstatus() const { return s.ANRUFSTATUS; }
    short        GetAnrufzaehler() const { return s.ANRUFZAEHLER; }
    char         GetTagnr() const { return s.TAGNR[0]; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    char         GetStourdefinitiv() const { return s.STOURDEFINITIV[0]; }
    char         GetRufprotokoll() const { return s.RUFPROTOKOLL[0]; }
    short        GetRufsteuerung() const { return s.RUFSTEUERUNG; }
    short        GetPoolnr() const { return s.POOLNR; }
    short        GetModempoolnr() const { return s.MODEMPOOLNR; }
    char         GetRufeinstellung() const { return s.RUFEINSTELLUNG[0]; }
    char         GetAnruftyp() const { return s.ANRUFTYP[0]; }
    char         GetSkdanrufgenerell() const { return s.SKDANRUFGENERELL[0]; }

    const mcustomercallplandayS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_MCUSTOMERCALLPLANDAY_NAMEAPO); }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_MCUSTOMERCALLPLANDAY_ORT); }
    void         SetTelnr(const ppString & t) { ppGStrCopy(s.TELNR, t.c_str(), L_MCUSTOMERCALLPLANDAY_TELNR); }
    void         SetTelkurzwahl(const ppString & t) { ppGStrCopy(s.TELKURZWAHL, t.c_str(), L_MCUSTOMERCALLPLANDAY_TELKURZWAHL); }
    void         SetKzkdklasse(const ppString & t) { ppGStrCopy(s.KZKDKLASSE, t.c_str(), L_MCUSTOMERCALLPLANDAY_KZKDKLASSE); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetUrrufzeit(long t) { s.URRUFZEIT = t; }
    void         SetRufzeit(long t) { s.RUFZEIT = t; }
    void         SetUmkstatus(short t) { s.UMKSTATUS = t; }
    void         SetAnrufstatus(short t) { s.ANRUFSTATUS = t; }
    void         SetAnrufzaehler(short t) { s.ANRUFZAEHLER = t; }
    void         SetTagnr(char t) { s.TAGNR[0] = t; s.TAGNR[1] = '\0';}
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_MCUSTOMERCALLPLANDAY_TOURID); }
    void         SetStourdefinitiv(char t) { s.STOURDEFINITIV[0] = t; s.STOURDEFINITIV[1] = '\0';}
    void         SetRufprotokoll(char t) { s.RUFPROTOKOLL[0] = t; s.RUFPROTOKOLL[1] = '\0';}
    void         SetRufsteuerung(short t) { s.RUFSTEUERUNG = t; }
    void         SetPoolnr(short t) { s.POOLNR = t; }
    void         SetModempoolnr(short t) { s.MODEMPOOLNR = t; }
    void         SetRufeinstellung(char t) { s.RUFEINSTELLUNG[0] = t; s.RUFEINSTELLUNG[1] = '\0';}
    void         SetAnruftyp(char t) { s.ANRUFTYP[0] = t; s.ANRUFTYP[1] = '\0';}
    void         SetSkdanrufgenerell(char t) { s.SKDANRUFGENERELL[0] = t; s.SKDANRUFGENERELL[1] = '\0';}

    void         SetStruct(const mcustomercallplandayS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          EndBrowse(int pos = 0) { int ret = UniqueServerCall(1090, pos); Strip(s); return ret; }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1088, pos); Strip(s); return ret; }
    int          SelCallPlanDay(int pos = 0) { int ret = UniqueServerCall(1162, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1087, FetchRel, pos); return ret; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1164, FetchRel, pos); return ret; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1168, FetchRel, pos); return ret; }
    int          SetCustomerCallFree(int pos = 0) { int ret = UniqueServerCall(1239, pos); Strip(s); return ret; }
    int          StartBrowse(int pos = 0) { int ret = UniqueServerCall(1089, pos); Strip(s); return ret; }
    int          UpdCustomerCallPlanDay(int pos = 0) { int ret = UniqueServerCall(1091, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }

    // constructor
    CMCUSTOMERCALLPLANDAY() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERCALLPLANDAY() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANDAY_BES, MCUSTOMERCALLPLANDAY_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANDAY_BES, (int)MCUSTOMERCALLPLANDAY_ANZ, error_msg);
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
        if ( fkt_nr == 1090 ) return UniqueServerCall(1090, pos);
        if ( fkt_nr == 1088 ) return UniqueServerCall(1088, pos);
        if ( fkt_nr == 1162 ) return UniqueServerCall(1162, pos);
        if ( fkt_nr == 1087 ) return CursorServerCall(1087, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1164 ) return CursorServerCall(1164, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1168 ) return CursorServerCall(1168, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1239 ) return UniqueServerCall(1239, pos);
        if ( fkt_nr == 1089 ) return UniqueServerCall(1089, pos);
        if ( fkt_nr == 1091 ) return UniqueServerCall(1091, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERCALLPLANDAY & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.ORT);
        ppGStripLast(d.TELNR);
        ppGStripLast(d.TELKURZWAHL);
        ppGStripLast(d.KZKDKLASSE);
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERCALLPLANDAY_BES, (int)MCUSTOMERCALLPLANDAY_ANZ, error_msg);
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
        CMCUSTOMERCALLPLANDAY c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANDAY_BES, (int)MCUSTOMERCALLPLANDAY_ANZ, error_msg);
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

class CMCUSTOMERCALLPLANDAYHIST : public ppDadeVirtual {
public:
    mcustomercallplandayhistS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomercallplandayhistS> lst; // class list

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
                     vector< mcustomercallplandayhistS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomercallplandayhistS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomercallplandayhistS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomercallplandayhistS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomercallplandayhistS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetUsername(ppString & t) const { t = s.USERNAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetUrrufzeit() const { return s.URRUFZEIT; }
    short        GetEreignis() const { return s.EREIGNIS; }
    long         GetRufzeit() const { return s.RUFZEIT; }
    short        GetUmkstatus() const { return s.UMKSTATUS; }
    short        GetAnrufstatus() const { return s.ANRUFSTATUS; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetModemnr() const { return s.MODEMNR; }
    long         GetUhrzeit() const { return s.UHRZEIT; }
    const char*  GetGeraeteid(ppString & t) const { t = s.GERAETEID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetUid() const { return s.UID; }
    long         GetDatumanlage() const { return s.DATUMANLAGE; }

    const mcustomercallplandayhistS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetUsername(const ppString & t) { ppGStrCopy(s.USERNAME, t.c_str(), L_MCUSTOMERCALLPLANDAYHIST_USERNAME); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetUrrufzeit(long t) { s.URRUFZEIT = t; }
    void         SetEreignis(short t) { s.EREIGNIS = t; }
    void         SetRufzeit(long t) { s.RUFZEIT = t; }
    void         SetUmkstatus(short t) { s.UMKSTATUS = t; }
    void         SetAnrufstatus(short t) { s.ANRUFSTATUS = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetModemnr(long t) { s.MODEMNR = t; }
    void         SetUhrzeit(long t) { s.UHRZEIT = t; }
    void         SetGeraeteid(const ppString & t) { ppGStrCopy(s.GERAETEID, t.c_str(), L_MCUSTOMERCALLPLANDAYHIST_GERAETEID); }
    void         SetUid(long t) { s.UID = t; }
    void         SetDatumanlage(long t) { s.DATUMANLAGE = t; }

    void         SetStruct(const mcustomercallplandayhistS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DelAll(int pos = 0) { return UniqueServerCall(1166, pos); }
    int          DelAllOlder(int pos = 0) { return UniqueServerCall(1229, pos); }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1165, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERCALLPLANDAYHIST() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANDAYHIST_BES, MCUSTOMERCALLPLANDAYHIST_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERCALLPLANDAYHIST() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANDAYHIST_BES, MCUSTOMERCALLPLANDAYHIST_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANDAYHIST_BES, (int)MCUSTOMERCALLPLANDAYHIST_ANZ, error_msg);
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
        if ( fkt_nr == 1166 ) return UniqueServerCall(1166, pos);
        if ( fkt_nr == 1229 ) return UniqueServerCall(1229, pos);
        if ( fkt_nr == 1165 ) return CursorServerCall(1165, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERCALLPLANDAYHIST & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.USERNAME);
        ppGStripLast(d.GERAETEID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERCALLPLANDAYHIST_BES, (int)MCUSTOMERCALLPLANDAYHIST_ANZ, error_msg);
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
        CMCUSTOMERCALLPLANDAYHIST c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANDAYHIST_BES, (int)MCUSTOMERCALLPLANDAYHIST_ANZ, error_msg);
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

class CMCUSTOMERCALLPLANRECALLINWORK : public ppDadeVirtual {
public:
    mcustomercallplanrecallinworkS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomercallplanrecallinworkS> lst; // class list

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
                     vector< mcustomercallplanrecallinworkS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomercallplanrecallinworkS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomercallplanrecallinworkS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomercallplanrecallinworkS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomercallplanrecallinworkS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetUrrufzeit() const { return s.URRUFZEIT; }
    long         GetDatum() const { return s.DATUM; }
    short        GetFilialnr() const { return s.FILIALNR; }
    long         GetUid() const { return s.UID; }
    long         GetTm_time() const { return s.TM_TIME; }

    const mcustomercallplanrecallinworkS &
                 GetStruct() const { return s; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetUrrufzeit(long t) { s.URRUFZEIT = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }

    void         SetStruct(const mcustomercallplanrecallinworkS & t) { s = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1189, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1187, pos); Strip(s); return ret; }
    int          Select(int pos = 0) { int ret = UniqueServerCall(1190, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1188, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERCALLPLANRECALLINWORK() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERCALLPLANRECALLINWORK() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANRECALLINWORK_BES, MCUSTOMERCALLPLANRECALLINWORK_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1189 ) return UniqueServerCall(1189, pos);
        if ( fkt_nr == 1187 ) return UniqueServerCall(1187, pos);
        if ( fkt_nr == 1190 ) return UniqueServerCall(1190, pos);
        if ( fkt_nr == 1188 ) return UniqueServerCall(1188, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERCALLPLANRECALLINWORK & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERCALLPLANRECALLINWORK_BES, (int)MCUSTOMERCALLPLANRECALLINWORK_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CMCUSTOMERCALLPLANDAYDRIVER : public ppDadeVirtual {
public:
    mcustomercallplandaydriverS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomercallplandaydriverS> lst; // class list

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
                     vector< mcustomercallplandaydriverS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomercallplandaydriverS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomercallplandaydriverS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomercallplandaydriverS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomercallplandaydriverS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelnr(ppString & t) const { t = s.TELNR; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelnrdafue(ppString & t) const { t = s.TELNRDAFUE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTelkurzwahl(ppString & t) const { t = s.TELKURZWAHL; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetUrrufzeit() const { return s.URRUFZEIT; }
    long         GetRufzeit() const { return s.RUFZEIT; }
    short        GetUmkstatus() const { return s.UMKSTATUS; }
    short        GetAnrufstatus() const { return s.ANRUFSTATUS; }
    short        GetAnrufzaehler() const { return s.ANRUFZAEHLER; }
    char         GetTagnr() const { return s.TAGNR[0]; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    char         GetStourdefinitiv() const { return s.STOURDEFINITIV[0]; }
    char         GetRufprotokoll() const { return s.RUFPROTOKOLL[0]; }
    short        GetRufsteuerung() const { return s.RUFSTEUERUNG; }
    short        GetPoolnr() const { return s.POOLNR; }
    short        GetModempoolnr() const { return s.MODEMPOOLNR; }
    char         GetRufeinstellung() const { return s.RUFEINSTELLUNG[0]; }
    char         GetAnruftyp() const { return s.ANRUFTYP[0]; }
    char         GetSkdanrufgenerell() const { return s.SKDANRUFGENERELL[0]; }
    short        GetEreignis() const { return s.EREIGNIS; }
    long         GetUhrzeit() const { return s.UHRZEIT; }
    const char*  GetGeraeteid(ppString & t) const { t = s.GERAETEID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetUid() const { return s.UID; }

    const mcustomercallplandaydriverS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_MCUSTOMERCALLPLANDAYDRIVER_NAMEAPO); }
    void         SetTelnr(const ppString & t) { ppGStrCopy(s.TELNR, t.c_str(), L_MCUSTOMERCALLPLANDAYDRIVER_TELNR); }
    void         SetTelnrdafue(const ppString & t) { ppGStrCopy(s.TELNRDAFUE, t.c_str(), L_MCUSTOMERCALLPLANDAYDRIVER_TELNRDAFUE); }
    void         SetTelkurzwahl(const ppString & t) { ppGStrCopy(s.TELKURZWAHL, t.c_str(), L_MCUSTOMERCALLPLANDAYDRIVER_TELKURZWAHL); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetUrrufzeit(long t) { s.URRUFZEIT = t; }
    void         SetRufzeit(long t) { s.RUFZEIT = t; }
    void         SetUmkstatus(short t) { s.UMKSTATUS = t; }
    void         SetAnrufstatus(short t) { s.ANRUFSTATUS = t; }
    void         SetAnrufzaehler(short t) { s.ANRUFZAEHLER = t; }
    void         SetTagnr(char t) { s.TAGNR[0] = t; s.TAGNR[1] = '\0';}
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_MCUSTOMERCALLPLANDAYDRIVER_TOURID); }
    void         SetStourdefinitiv(char t) { s.STOURDEFINITIV[0] = t; s.STOURDEFINITIV[1] = '\0';}
    void         SetRufprotokoll(char t) { s.RUFPROTOKOLL[0] = t; s.RUFPROTOKOLL[1] = '\0';}
    void         SetRufsteuerung(short t) { s.RUFSTEUERUNG = t; }
    void         SetPoolnr(short t) { s.POOLNR = t; }
    void         SetModempoolnr(short t) { s.MODEMPOOLNR = t; }
    void         SetRufeinstellung(char t) { s.RUFEINSTELLUNG[0] = t; s.RUFEINSTELLUNG[1] = '\0';}
    void         SetAnruftyp(char t) { s.ANRUFTYP[0] = t; s.ANRUFTYP[1] = '\0';}
    void         SetSkdanrufgenerell(char t) { s.SKDANRUFGENERELL[0] = t; s.SKDANRUFGENERELL[1] = '\0';}
    void         SetEreignis(short t) { s.EREIGNIS = t; }
    void         SetUhrzeit(long t) { s.UHRZEIT = t; }
    void         SetGeraeteid(const ppString & t) { ppGStrCopy(s.GERAETEID, t.c_str(), L_MCUSTOMERCALLPLANDAYDRIVER_GERAETEID); }
    void         SetUid(long t) { s.UID = t; }

    void         SetStruct(const mcustomercallplandaydriverS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          EndBrowse(int pos = 0) { int ret = UniqueServerCall(1145, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1148, FetchRel, pos); return ret; }
    int          SelUniCustomerCallplan(int pos = 0) { int ret = UniqueServerCall(1183, pos); Strip(s); return ret; }
    int          StartBrowse(int pos = 0) { int ret = UniqueServerCall(1144, pos); Strip(s); return ret; }
    int          UpdCustomerCallplan(int pos = 0) { int ret = UniqueServerCall(1147, pos); Strip(s); return ret; }
    int          UpdCustomerCallplanWithoutTransaction(int pos = 0) { int ret = UniqueServerCall(1200, pos); Strip(s); return ret; }
    int          UpdWithoutTransaction(int pos = 0) { int ret = UniqueServerCall(1149, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERCALLPLANDAYDRIVER() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERCALLPLANDAYDRIVER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERCALLPLANDAYDRIVER_BES, MCUSTOMERCALLPLANDAYDRIVER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANDAYDRIVER_BES, (int)MCUSTOMERCALLPLANDAYDRIVER_ANZ, error_msg);
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
        if ( fkt_nr == 1145 ) return UniqueServerCall(1145, pos);
        if ( fkt_nr == 1148 ) return CursorServerCall(1148, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1183 ) return UniqueServerCall(1183, pos);
        if ( fkt_nr == 1144 ) return UniqueServerCall(1144, pos);
        if ( fkt_nr == 1147 ) return UniqueServerCall(1147, pos);
        if ( fkt_nr == 1200 ) return UniqueServerCall(1200, pos);
        if ( fkt_nr == 1149 ) return UniqueServerCall(1149, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERCALLPLANDAYDRIVER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.TELNR);
        ppGStripLast(d.TELNRDAFUE);
        ppGStripLast(d.TELKURZWAHL);
        ppGStripLast(d.TOURID);
        ppGStripLast(d.GERAETEID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERCALLPLANDAYDRIVER_BES, (int)MCUSTOMERCALLPLANDAYDRIVER_ANZ, error_msg);
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
        CMCUSTOMERCALLPLANDAYDRIVER c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MCUSTOMERCALLPLANDAYDRIVER_BES, (int)MCUSTOMERCALLPLANDAYDRIVER_ANZ, error_msg);
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

class CMCUSTOMERLASTCALL : public ppDadeVirtual {
public:
    mcustomerlastcallS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomerlastcallS> lst; // class list

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
                     vector< mcustomerlastcallS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomerlastcallS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomerlastcallS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomerlastcallS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomerlastcallS>::iterator
                 endList  () { return lst.end  (); }

    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetDatum() const { return s.DATUM; }
    long         GetUrrufzeit() const { return s.URRUFZEIT; }
    short        GetAnrufstatus() const { return s.ANRUFSTATUS; }
    long         GetUhrzeit() const { return s.UHRZEIT; }

    const mcustomerlastcallS &
                 GetStruct() const { return s; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetUrrufzeit(long t) { s.URRUFZEIT = t; }
    void         SetAnrufstatus(short t) { s.ANRUFSTATUS = t; }
    void         SetUhrzeit(long t) { s.UHRZEIT = t; }

    void         SetStruct(const mcustomerlastcallS & t) { s = t; }

    int          EndBrowse(int pos = 0) { int ret = UniqueServerCall(1206, pos); Strip(s); return ret; }
    int          SelCustomerCallState(int pos = 0) { int ret = UniqueServerCall(1205, pos); Strip(s); return ret; }
    int          StartBrowse(int pos = 0) { int ret = UniqueServerCall(1204, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERLASTCALL() {
        ::buf_default((void *)&s, MCUSTOMERLASTCALL_BES, MCUSTOMERLASTCALL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERLASTCALL() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERLASTCALL_BES, MCUSTOMERLASTCALL_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1206 ) return UniqueServerCall(1206, pos);
        if ( fkt_nr == 1205 ) return UniqueServerCall(1205, pos);
        if ( fkt_nr == 1204 ) return UniqueServerCall(1204, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERLASTCALL & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERLASTCALL_BES, (int)MCUSTOMERLASTCALL_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CMCUSTOMERORDER : public ppDadeVirtual {
public:
    mcustomerorderS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mcustomerorderS> lst; // class list

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
                     vector< mcustomerorderS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mcustomerorderS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mcustomerorderS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mcustomerorderS>::iterator
                 beginList() { return lst.begin(); }
    vector<mcustomerorderS>::iterator
                 endList  () { return lst.end  (); }

    long         GetKdauftragnr() const { return s.KDAUFTRAGNR; }
    const char*  GetKdauftragstat(ppString & t) const { t = s.KDAUFTRAGSTAT; t.erasespace(ppString::END); return t.c_str(); }
    long         GetZeit() const { return s.ZEIT; }
    const char*  GetGeraetname(ppString & t) const { t = s.GERAETNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetAnzpos() const { return s.ANZPOS; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }

    const mcustomerorderS &
                 GetStruct() const { return s; }
    void         SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
    void         SetKdauftragstat(const ppString & t) { ppGStrCopy(s.KDAUFTRAGSTAT, t.c_str(), L_MCUSTOMERORDER_KDAUFTRAGSTAT); }
    void         SetZeit(long t) { s.ZEIT = t; }
    void         SetGeraetname(const ppString & t) { ppGStrCopy(s.GERAETNAME, t.c_str(), L_MCUSTOMERORDER_GERAETNAME); }
    void         SetAnzpos(long t) { s.ANZPOS = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }

    void         SetStruct(const mcustomerorderS & t) { s = t; }

    int          EndBrowse(int pos = 0) { int ret = UniqueServerCall(1157, pos); Strip(s); return ret; }
    int          SelAvailableOrder(int pos = 0) { int ret = UniqueServerCall(1279, pos); Strip(s); return ret; }
    int          SelCustomerCalled(int pos = 0) { int ret = UniqueServerCall(1194, pos); Strip(s); return ret; }
    int          SelDeviceOrder(int pos = 0) { int ret = UniqueServerCall(1159, pos); Strip(s); return ret; }
    int          StartBrowse(int pos = 0) { int ret = UniqueServerCall(1156, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMCUSTOMERORDER() {
        ::buf_default((void *)&s, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMCUSTOMERORDER() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MCUSTOMERORDER_BES, MCUSTOMERORDER_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1157 ) return UniqueServerCall(1157, pos);
        if ( fkt_nr == 1279 ) return UniqueServerCall(1279, pos);
        if ( fkt_nr == 1194 ) return UniqueServerCall(1194, pos);
        if ( fkt_nr == 1159 ) return UniqueServerCall(1159, pos);
        if ( fkt_nr == 1156 ) return UniqueServerCall(1156, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MCUSTOMERORDER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.KDAUFTRAGSTAT);
        ppGStripLast(d.GERAETNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MCUSTOMERORDER_BES, (int)MCUSTOMERORDER_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CMDEVICEPLANCHECK : public ppDadeVirtual {
public:
    mdeviceplancheckS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mdeviceplancheckS> lst; // class list

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
                     vector< mdeviceplancheckS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mdeviceplancheckS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mdeviceplancheckS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mdeviceplancheckS>::iterator
                 beginList() { return lst.begin(); }
    vector<mdeviceplancheckS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRegionentyp() const { return s.REGIONENTYP; }
    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetGeraeteid(ppString & t) const { t = s.GERAETEID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetSequenznr() const { return s.SEQUENZNR; }
    long         GetGeraetnst() const { return s.GERAETNST; }
    char         GetGeraeteverw1() const { return s.GERAETEVERW1[0]; }
    char         GetTerminalstatus() const { return s.TERMINALSTATUS[0]; }
    long         GetStartzeit() const { return s.STARTZEIT; }
    long         GetEndezeit() const { return s.ENDEZEIT; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetUrrufzeit() const { return s.URRUFZEIT; }
    long         GetDatum() const { return s.DATUM; }
    char         GetAuftragstatus() const { return s.AUFTRAGSTATUS[0]; }
    long         GetKdauftragnr1() const { return s.KDAUFTRAGNR1; }
    short        GetPoolnr() const { return s.POOLNR; }
    short        GetUmknr() const { return s.UMKNR; }
    char         GetAktiv() const { return s.AKTIV[0]; }

    const mdeviceplancheckS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetRegionentyp(short t) { s.REGIONENTYP = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetGeraeteid(const ppString & t) { ppGStrCopy(s.GERAETEID, t.c_str(), L_MDEVICEPLANCHECK_GERAETEID); }
    void         SetSequenznr(long t) { s.SEQUENZNR = t; }
    void         SetGeraetnst(long t) { s.GERAETNST = t; }
    void         SetGeraeteverw1(char t) { s.GERAETEVERW1[0] = t; s.GERAETEVERW1[1] = '\0';}
    void         SetTerminalstatus(char t) { s.TERMINALSTATUS[0] = t; s.TERMINALSTATUS[1] = '\0';}
    void         SetStartzeit(long t) { s.STARTZEIT = t; }
    void         SetEndezeit(long t) { s.ENDEZEIT = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetUrrufzeit(long t) { s.URRUFZEIT = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetAuftragstatus(char t) { s.AUFTRAGSTATUS[0] = t; s.AUFTRAGSTATUS[1] = '\0';}
    void         SetKdauftragnr1(long t) { s.KDAUFTRAGNR1 = t; }
    void         SetPoolnr(short t) { s.POOLNR = t; }
    void         SetUmknr(short t) { s.UMKNR = t; }
    void         SetAktiv(char t) { s.AKTIV[0] = t; s.AKTIV[1] = '\0';}

    void         SetStruct(const mdeviceplancheckS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelDeviceID(int pos = 0) { int ret = UniqueServerCall(1240, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1116, FetchRel, pos); return ret; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1199, FetchRel, pos); return ret; }
    int          UpdUMKDecivePlan(int pos = 0) { int ret = UniqueServerCall(1196, pos); Strip(s); return ret; }
    int          UpdateDirect(int pos = 0) { int ret = UniqueServerCall(1221, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMDEVICEPLANCHECK() {
        ::buf_default((void *)&s, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMDEVICEPLANCHECK() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MDEVICEPLANCHECK_BES, MDEVICEPLANCHECK_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MDEVICEPLANCHECK_BES, (int)MDEVICEPLANCHECK_ANZ, error_msg);
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
        if ( fkt_nr == 1240 ) return UniqueServerCall(1240, pos);
        if ( fkt_nr == 1116 ) return CursorServerCall(1116, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1199 ) return CursorServerCall(1199, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1196 ) return UniqueServerCall(1196, pos);
        if ( fkt_nr == 1221 ) return UniqueServerCall(1221, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MDEVICEPLANCHECK & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.GERAETEID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MDEVICEPLANCHECK_BES, (int)MDEVICEPLANCHECK_ANZ, error_msg);
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
        CMDEVICEPLANCHECK c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MDEVICEPLANCHECK_BES, (int)MDEVICEPLANCHECK_ANZ, error_msg);
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

class CMDEVICEPLANDRIVER : public ppDadeVirtual {
public:
    mdeviceplandriverS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mdeviceplandriverS> lst; // class list

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
                     vector< mdeviceplandriverS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mdeviceplandriverS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mdeviceplandriverS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mdeviceplandriverS>::iterator
                 beginList() { return lst.begin(); }
    vector<mdeviceplandriverS>::iterator
                 endList  () { return lst.end  (); }

    short        GetRegionentyp() const { return s.REGIONENTYP; }
    long         GetSchluessel() const { return s.SCHLUESSEL; }
    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetGeraeteid(ppString & t) const { t = s.GERAETEID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetSequenznr() const { return s.SEQUENZNR; }
    char         GetGeraeteart() const { return s.GERAETEART[0]; }
    char         GetGeraeteverw1() const { return s.GERAETEVERW1[0]; }
    char         GetTerminalstatus() const { return s.TERMINALSTATUS[0]; }
    char         GetModemtyp() const { return s.MODEMTYP[0]; }
    long         GetStartzeit() const { return s.STARTZEIT; }
    long         GetEndezeit() const { return s.ENDEZEIT; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    long         GetUrrufzeit() const { return s.URRUFZEIT; }
    long         GetDatum() const { return s.DATUM; }
    char         GetAuftragstatus() const { return s.AUFTRAGSTATUS[0]; }
    long         GetKdauftragnr1() const { return s.KDAUFTRAGNR1; }
    short        GetPoolnr() const { return s.POOLNR; }
    short        GetUmknr() const { return s.UMKNR; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    char         GetAktiv() const { return s.AKTIV[0]; }
    short        GetUmknst() const { return s.UMKNST; }

    const mdeviceplandriverS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetRegionentyp(short t) { s.REGIONENTYP = t; }
    void         SetSchluessel(long t) { s.SCHLUESSEL = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetGeraeteid(const ppString & t) { ppGStrCopy(s.GERAETEID, t.c_str(), L_MDEVICEPLANDRIVER_GERAETEID); }
    void         SetSequenznr(long t) { s.SEQUENZNR = t; }
    void         SetGeraeteart(char t) { s.GERAETEART[0] = t; s.GERAETEART[1] = '\0';}
    void         SetGeraeteverw1(char t) { s.GERAETEVERW1[0] = t; s.GERAETEVERW1[1] = '\0';}
    void         SetTerminalstatus(char t) { s.TERMINALSTATUS[0] = t; s.TERMINALSTATUS[1] = '\0';}
    void         SetModemtyp(char t) { s.MODEMTYP[0] = t; s.MODEMTYP[1] = '\0';}
    void         SetStartzeit(long t) { s.STARTZEIT = t; }
    void         SetEndezeit(long t) { s.ENDEZEIT = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetUrrufzeit(long t) { s.URRUFZEIT = t; }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetAuftragstatus(char t) { s.AUFTRAGSTATUS[0] = t; s.AUFTRAGSTATUS[1] = '\0';}
    void         SetKdauftragnr1(long t) { s.KDAUFTRAGNR1 = t; }
    void         SetPoolnr(short t) { s.POOLNR = t; }
    void         SetUmknr(short t) { s.UMKNR = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_MDEVICEPLANDRIVER_TOURID); }
    void         SetAktiv(char t) { s.AKTIV[0] = t; s.AKTIV[1] = '\0';}
    void         SetUmknst(short t) { s.UMKNST = t; }

    void         SetStruct(const mdeviceplandriverS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          EndBrowse(int pos = 0) { int ret = UniqueServerCall(1136, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1134, FetchRel, pos); return ret; }
    int          SelWithSequenzNo(int pos = 0) { int ret = UniqueServerCall(1182, pos); Strip(s); return ret; }
    int          StartBrowse(int pos = 0) { int ret = UniqueServerCall(1133, pos); Strip(s); return ret; }
    int          UpdDevicePlan(int pos = 0) { int ret = UniqueServerCall(1135, pos); Strip(s); return ret; }
    int          UpdUMKDevicePlan(int pos = 0) { int ret = UniqueServerCall(1197, pos); Strip(s); return ret; }
    int          UpdWithoutTransaction(int pos = 0) { int ret = UniqueServerCall(1137, pos); Strip(s); return ret; }
    int          UpdWithoutTransactionDirect(int pos = 0) { int ret = UniqueServerCall(1184, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMDEVICEPLANDRIVER() {
        ::buf_default((void *)&s, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMDEVICEPLANDRIVER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MDEVICEPLANDRIVER_BES, MDEVICEPLANDRIVER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MDEVICEPLANDRIVER_BES, (int)MDEVICEPLANDRIVER_ANZ, error_msg);
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
        if ( fkt_nr == 1136 ) return UniqueServerCall(1136, pos);
        if ( fkt_nr == 1134 ) return CursorServerCall(1134, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1182 ) return UniqueServerCall(1182, pos);
        if ( fkt_nr == 1133 ) return UniqueServerCall(1133, pos);
        if ( fkt_nr == 1135 ) return UniqueServerCall(1135, pos);
        if ( fkt_nr == 1197 ) return UniqueServerCall(1197, pos);
        if ( fkt_nr == 1137 ) return UniqueServerCall(1137, pos);
        if ( fkt_nr == 1184 ) return UniqueServerCall(1184, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MDEVICEPLANDRIVER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.GERAETEID);
        ppGStripLast(d.TOURID);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MDEVICEPLANDRIVER_BES, (int)MDEVICEPLANDRIVER_ANZ, error_msg);
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
        CMDEVICEPLANDRIVER c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, MDEVICEPLANDRIVER_BES, (int)MDEVICEPLANDRIVER_ANZ, error_msg);
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

class CMNUMBER : public ppDadeVirtual {
public:
    mnumberS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mnumberS> lst; // class list

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
                     vector< mnumberS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mnumberS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mnumberS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mnumberS>::iterator
                 beginList() { return lst.begin(); }
    vector<mnumberS>::iterator
                 endList  () { return lst.end  (); }

    short        GetNummertyp() const { return s.NUMMERTYP; }
    long         GetNummerwert() const { return s.NUMMERWERT; }
    long         GetNummermindest() const { return s.NUMMERMINDEST; }
    long         GetNummerhoechst() const { return s.NUMMERHOECHST; }
    long         GetNummerinkrement() const { return s.NUMMERINKREMENT; }
    short        GetNummermodus() const { return s.NUMMERMODUS; }

    const mnumberS &
                 GetStruct() const { return s; }
    void         SetNummertyp(short t) { s.NUMMERTYP = t; }
    void         SetNummerwert(long t) { s.NUMMERWERT = t; }
    void         SetNummermindest(long t) { s.NUMMERMINDEST = t; }
    void         SetNummerhoechst(long t) { s.NUMMERHOECHST = t; }
    void         SetNummerinkrement(long t) { s.NUMMERINKREMENT = t; }
    void         SetNummermodus(short t) { s.NUMMERMODUS = t; }

    void         SetStruct(const mnumberS & t) { s = t; }

    int          Increment(int pos = 0) { int ret = UniqueServerCall(1143, pos); Strip(s); return ret; }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1150, pos); Strip(s); return ret; }
    int          SelNumber(int pos = 0) { int ret = UniqueServerCall(1141, pos); Strip(s); return ret; }
    int          UpdNumber(int pos = 0) { int ret = UniqueServerCall(1142, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMNUMBER() {
        ::buf_default((void *)&s, MNUMBER_BES, MNUMBER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMNUMBER() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MNUMBER_BES, MNUMBER_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1143 ) return UniqueServerCall(1143, pos);
        if ( fkt_nr == 1150 ) return UniqueServerCall(1150, pos);
        if ( fkt_nr == 1141 ) return UniqueServerCall(1141, pos);
        if ( fkt_nr == 1142 ) return UniqueServerCall(1142, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MNUMBER & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MNUMBER_BES, (int)MNUMBER_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};

class CMTRANSAKTION : public ppDadeVirtual {
public:
    mtransaktionS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<mtransaktionS> lst; // class list

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
                     vector< mtransaktionS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     mtransaktionS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< mtransaktionS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<mtransaktionS>::iterator
                 beginList() { return lst.begin(); }
    vector<mtransaktionS>::iterator
                 endList  () { return lst.end  (); }

    long         GetTm_date() const { return s.TM_DATE; }
    long         GetTm_time() const { return s.TM_TIME; }

    const mtransaktionS &
                 GetStruct() const { return s; }
    void         SetTm_date(long t) { s.TM_DATE = t; }
    void         SetTm_time(long t) { s.TM_TIME = t; }

    void         SetStruct(const mtransaktionS & t) { s = t; }

    int          BeginTransaction(int pos = 0) { int ret = UniqueServerCall(1138, pos); Strip(s); return ret; }
    int          EndTransaction(int pos = 0) { int ret = UniqueServerCall(1139, pos); Strip(s); return ret; }
    int          GetDate(int pos = 0) { int ret = UniqueServerCall(1153, pos); Strip(s); return ret; }
    int          GetDateTime(int pos = 0) { int ret = UniqueServerCall(1151, pos); Strip(s); return ret; }
    int          GetTime(int pos = 0) { int ret = UniqueServerCall(1152, pos); Strip(s); return ret; }
    int          RollbackTransaction(int pos = 0) { int ret = UniqueServerCall(1140, pos); Strip(s); return ret; }
    int          SetCommitedRead(int pos = 0) { int ret = UniqueServerCall(1155, pos); Strip(s); return ret; }
    int          SetDirtyRead(int pos = 0) { int ret = UniqueServerCall(1154, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CMTRANSAKTION() {
        ::buf_default((void *)&s, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CMTRANSAKTION() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, MTRANSAKTION_BES, MTRANSAKTION_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
        if ( fkt_nr == 1138 ) return UniqueServerCall(1138, pos);
        if ( fkt_nr == 1139 ) return UniqueServerCall(1139, pos);
        if ( fkt_nr == 1153 ) return UniqueServerCall(1153, pos);
        if ( fkt_nr == 1151 ) return UniqueServerCall(1151, pos);
        if ( fkt_nr == 1152 ) return UniqueServerCall(1152, pos);
        if ( fkt_nr == 1140 ) return UniqueServerCall(1140, pos);
        if ( fkt_nr == 1155 ) return UniqueServerCall(1155, pos);
        if ( fkt_nr == 1154 ) return UniqueServerCall(1154, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_MTRANSAKTION & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, MTRANSAKTION_BES, (int)MTRANSAKTION_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};
#endif    // TRANSCLASS

#endif   // GUARD
