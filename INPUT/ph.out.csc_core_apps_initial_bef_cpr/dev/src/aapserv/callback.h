#ifndef __PP_CALLBACK_H_
#define __PP_CALLBACK_H_

/******************************************************************************/
/* c:\git\pharmos.outbound.csc_core_applications\dev\src\aapserv\CallBack *****/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CALLBACKATTACH ********************************************/

#define L_CALLBACKATTACH_REGIONNR 11
#define L_CALLBACKATTACH_UID 11
#define L_CALLBACKATTACH_CALLBACKPARTNO 11
#define L_CALLBACKATTACH_VERTRIEBSZENTRUMNR 6
#define L_CALLBACKATTACH_FILIALNR 6
#define L_CALLBACKATTACH_REASONNO 6

/* Length-Define of CALLBACKPARTNER *******************************************/

#define L_CALLBACKPARTNER_CALLBACKPARTNO 11
#define L_CALLBACKPARTNER_CALLBACKPARTNER 30
#define L_CALLBACKPARTNER_REGIONNR 11
#define L_CALLBACKPARTNER_CALLBACKTIME 6
#define L_CALLBACKPARTNER_VERTRIEBSZENTRUMNR 6

/* Length-Define of CALLBACKTIME **********************************************/

#define L_CALLBACKTIME_CALLBACKPARTNO 11
#define L_CALLBACKTIME_OFFICEDAY 6
#define L_CALLBACKTIME_BEGINTIME 6
#define L_CALLBACKTIME_ENDTIME 6

/* Length-Define of CALLBACKCRITICAL ******************************************/

#define L_CALLBACKCRITICAL_DIVISIONNAME 20
#define L_CALLBACKCRITICAL_DATUM 11
#define L_CALLBACKCRITICAL_TITEL 30
#define L_CALLBACKCRITICAL_KRITIKNR 11
#define L_CALLBACKCRITICAL_POSNR_DONE 11
#define L_CALLBACKCRITICAL_STATUSID 6
#define L_CALLBACKCRITICAL_VERTRIEBSZENTRUMNR 6
#define L_CALLBACKCRITICAL_KUNDENNR 11
#define L_CALLBACKCRITICAL_KRITIKLEVEL 6
#define L_CALLBACKCRITICAL_KRITIKTEXT 2048
#define L_CALLBACKCRITICAL_USERNAME64 64

/* Length-Define of CALLBACKDIVISION ******************************************/

#define L_CALLBACKDIVISION_BRANCHNO 6
#define L_CALLBACKDIVISION_DIVISIONNAME 20
#define L_CALLBACKDIVISION_REGIONNR 11
#define L_CALLBACKDIVISION_MAILINGLIST 254
#define L_CALLBACKDIVISION_CALLBACKDIVISIONNO 6
#define L_CALLBACKDIVISION_CALLBACKSTART 11
#define L_CALLBACKDIVISION_CALLBACKEND 11

/* Length-Define of CALLBACKREASONS *******************************************/

#define L_CALLBACKREASONS_REASONNO 6
#define L_CALLBACKREASONS_CALLBACKREASON 30
#define L_CALLBACKREASONS_CALLBACKDIVISIONNO 6
#define L_CALLBACKREASONS_MAILINGLIST 254
#define L_CALLBACKREASONS_BRANCHNO 6
#define L_CALLBACKREASONS_SWONLYMAIL 6

/* Length-Define of CALLBACKREMARKS *******************************************/

#define L_CALLBACKREMARKS_REMARKNO 11
#define L_CALLBACKREMARKS_CALLBACKREMARKTEXT 254
#define L_CALLBACKREMARKS_CALLBACKREMARKHEADER 254

/* Length-Define of CALLBACKTODO **********************************************/

#define L_CALLBACKTODO_CALLBACKNO 11
#define L_CALLBACKTODO_CALLBACKPARTNO 11
#define L_CALLBACKTODO_IDFNR 11
#define L_CALLBACKTODO_CALLBACKPARTNER 30
#define L_CALLBACKTODO_REGIONNR 11
#define L_CALLBACKTODO_KRITIKNR 11
#define L_CALLBACKTODO_POSNR 11
#define L_CALLBACKTODO_KZPOSART 1
#define L_CALLBACKTODO_TITEL 30
#define L_CALLBACKTODO_VERTRIEBSZENTRUMNR 6
#define L_CALLBACKTODO_CALLBACKTIMEWISHED 11
#define L_CALLBACKTODO_CALLBACKDATEWISHED 11
#define L_CALLBACKTODO_STATE 1
#define L_CALLBACKTODO_NAMEAPO 40
#define L_CALLBACKTODO_KRITIKTEXT 2048
#define L_CALLBACKTODO_SHIFTCOUNT 6
#define L_CALLBACKTODO_ORT 30
#define L_CALLBACKTODO_KZKDKLASSE 3
#define L_CALLBACKTODO_UID 11
#define L_CALLBACKTODO_FILIALNR 6
#define L_CALLBACKTODO_REFERENCE 150
#define L_CALLBACKTODO_STATUS 50

/* Length-Define of CALLBACKTODONEW *******************************************/

#define L_CALLBACKTODONEW_CALLBACKNO 11
#define L_CALLBACKTODONEW_IDFNR 11
#define L_CALLBACKTODONEW_REGIONNR 11
#define L_CALLBACKTODONEW_DIVISIONNAME 20
#define L_CALLBACKTODONEW_KRITIKNR 11
#define L_CALLBACKTODONEW_POSNR 11
#define L_CALLBACKTODONEW_CALLBACKDIVISIONNO 6
#define L_CALLBACKTODONEW_TITEL 30
#define L_CALLBACKTODONEW_KZPOSART 1
#define L_CALLBACKTODONEW_CALLBACKTIMEWISHED 11
#define L_CALLBACKTODONEW_VERTRIEBSZENTRUMNR 6
#define L_CALLBACKTODONEW_CALLBACKDATEWISHED 11
#define L_CALLBACKTODONEW_STATE 1
#define L_CALLBACKTODONEW_KRITIKLEVEL 6
#define L_CALLBACKTODONEW_NAMEAPO 40
#define L_CALLBACKTODONEW_KRITIKTEXT 2048
#define L_CALLBACKTODONEW_SHIFTCOUNT 6
#define L_CALLBACKTODONEW_ORT 30
#define L_CALLBACKTODONEW_KZKDKLASSE 3
#define L_CALLBACKTODONEW_UID 11
#define L_CALLBACKTODONEW_FILIALNR 6
#define L_CALLBACKTODONEW_REFERENCE 150
#define L_CALLBACKTODONEW_STATUS 50

/* Length-Define of CALLBACSTATUS *********************************************/

#define L_CALLBACSTATUS_STATUSID 6
#define L_CALLBACSTATUS_STATUSNAME 50
#define L_CALLBACSTATUS_STATUSTAG 6

/* Length-Define of CALLBACKITEMS *********************************************/

#define L_CALLBACKITEMS_CALLBACKNO 11
#define L_CALLBACKITEMS_CALLBACKPARTNO 11
#define L_CALLBACKITEMS_KRITIKNR 11
#define L_CALLBACKITEMS_POSNR 11
#define L_CALLBACKITEMS_KZPOSART 1
#define L_CALLBACKITEMS_POSNR_DONE 11
#define L_CALLBACKITEMS_CALLBACKTIMEWISHED 11
#define L_CALLBACKITEMS_CALLBACKDATEWISHED 11
#define L_CALLBACKITEMS_CALLBACKTIME 6
#define L_CALLBACKITEMS_STATE 1
#define L_CALLBACKITEMS_LOCKKZ 1
#define L_CALLBACKITEMS_SHIFTCOUNT 6
#define L_CALLBACKITEMS_REASONNO 6
#define L_CALLBACKITEMS_REFERENCE 150
#define L_CALLBACKITEMS_STATUSID 6

/* SqlDefine of CALLBACKATTACH ************************************************/


#define CALLBACKATTACH_PLISTE \
        "CALLBACKATTACH.UID,"\
        "CALLBACKATTACH.CALLBACKPARTNO,"\
        "CALLBACKATTACH.VERTRIEBSZENTRUMNR,"\
        "CALLBACKATTACH.FILIALNR,"\
        "CALLBACKATTACH.REASONNO"

/* SqlDefine of CALLBACKPARTNER ***********************************************/


#define CALLBACKPARTNER_PLISTE \
        "CALLBACKPARTNER.CALLBACKPARTNO,"\
        "CALLBACKPARTNER.CALLBACKPARTNER,"\
        "CALLBACKPARTNER.CALLBACKTIME,"\
        "CALLBACKPARTNER.VERTRIEBSZENTRUMNR"

/* SqlDefine of CALLBACKTIME **************************************************/


#define CALLBACKTIME_PLISTE \
        "CALLBACKOFFTIME.CALLBACKPARTNO,"\
        "CALLBACKOFFTIME.OFFICEDAY,"\
        "CALLBACKOFFTIME.BEGINTIME,"\
        "CALLBACKOFFTIME.ENDTIME"

/* SqlDefine of CALLBACKCRITICAL **********************************************/


#define CALLBACKCRITICAL_PLISTE \
        "CALLBACKDIVISION.DIVISIONNAME,"\
        "KDKRITIK.DATUM,"\
        "KDKRITIK.TITEL,"\
        "KDKRITIK.KRITIKNR,"\
        "CALLBACKITEMS.POSNR_DONE,"\
        "CALLBACKITEMS.STATUSID,"\
        "KDKRITIK.VERTRIEBSZENTRUMNR,"\
        "KDKRITIK.KUNDENNR,"\
        "KDKRITIK.KRITIKLEVEL,"\
        "KDKRITIKPOS.KRITIKTEXT,"\
        "AADUMMY.USERNAME64"

/* SqlDefine of CALLBACKDIVISION **********************************************/


#define CALLBACKDIVISION_PLISTE \
        "CALLBACKDIVISION.BRANCHNO,"\
        "CALLBACKDIVISION.DIVISIONNAME,"\
        "CALLBACKDIVISION.MAILINGLIST,"\
        "CALLBACKDIVISION.CALLBACKDIVISIONNO"

/* SqlDefine of CALLBACKREASONS ***********************************************/


#define CALLBACKREASONS_PLISTE \
        "CALLBACKREASONS.REASONNO,"\
        "CALLBACKREASONS.CALLBACKREASON,"\
        "CALLBACKREASONS.CALLBACKDIVISIONNO,"\
        "CALLBACKREASONS.MAILINGLIST,"\
        "CALLBACKREASONS.BRANCHNO,"\
        "CALLBACKREASONS.SWONLYMAIL"

/* SqlDefine of CALLBACKREMARKS ***********************************************/


#define CALLBACKREMARKS_PLISTE \
        "CALLBACKREMARKS.REMARKNO,"\
        "CALLBACKREMARKS.CALLBACKREMARKTEXT,"\
        "CALLBACKREMARKS.CALLBACKREMARKHEADER"

/* SqlDefine of CALLBACKTODO **************************************************/


#define CALLBACKTODO_PLISTE \
        "CALLBACKITEMS.CALLBACKNO,"\
        "CALLBACKPARTNER.CALLBACKPARTNO,"\
        "KDKRITIK.IDFNR,"\
        "CALLBACKPARTNER.CALLBACKPARTNER,"\
        "CALLBACKITEMS.KRITIKNR,"\
        "CALLBACKITEMS.POSNR,"\
        "CALLBACKITEMS.KZPOSART,"\
        "KDKRITIK.TITEL,"\
        "KDKRITIK.VERTRIEBSZENTRUMNR,"\
        "CALLBACKITEMS.CALLBACKTIMEWISHED,"\
        "CALLBACKITEMS.CALLBACKDATEWISHED,"\
        "CALLBACKITEMS.STATE,"\
        "KUNDE.NAMEAPO,"\
        "KDKRITIKPOS.KRITIKTEXT,"\
        "CALLBACKITEMS.SHIFTCOUNT,"\
        "KUNDE.ORT,"\
        "KUNDE.KZKDKLASSE,"\
        "CALLBACKITEMS.REFERENCE,"\
        "CALLBACKSTATUS.CALLBACKSTATUSNAME"

/* SqlDefine of CALLBACKTODONEW ***********************************************/


#define CALLBACKTODONEW_PLISTE \
        "CALLBACKITEMS.CALLBACKNO,"\
        "KDKRITIK.IDFNR,"\
        "CALLBACKDIVISION.DIVISIONNAME,"\
        "CALLBACKITEMS.KRITIKNR,"\
        "CALLBACKITEMS.POSNR,"\
        "CALLBACKDIVISION.CALLBACKDIVISIONNO,"\
        "KDKRITIK.TITEL,"\
        "CALLBACKITEMS.KZPOSART,"\
        "CALLBACKITEMS.CALLBACKTIMEWISHED,"\
        "KDKRITIK.VERTRIEBSZENTRUMNR,"\
        "CALLBACKITEMS.CALLBACKDATEWISHED,"\
        "CALLBACKITEMS.STATE,"\
        "KDKRITIK.KRITIKLEVEL,"\
        "KUNDE.NAMEAPO,"\
        "KDKRITIKPOS.KRITIKTEXT,"\
        "CALLBACKITEMS.SHIFTCOUNT,"\
        "KUNDE.ORT,"\
        "KUNDE.KZKDKLASSE,"\
        "CALLBACKITEMS.REFERENCE,"\
        "CALLBACKSTATUS.CALLBACKSTATUSNAME"

/* SqlDefine of CALLBACKSTATUS *************************************************/


#define CALLBACKSTATUS_PLISTE \
        "CALLBACKSTATUS.CALLBACKSTATUSID,"\
        "CALLBACKSTATUS.CALLBACKSTATUSNAME"

/* SqlDefine of CALLBACKITEMS *************************************************/


#define CALLBACKITEMS_PLISTE \
        "CALLBACKITEMS.CALLBACKNO,"\
        "CALLBACKITEMS.CALLBACKPARTNO,"\
        "CALLBACKITEMS.KRITIKNR,"\
        "CALLBACKITEMS.POSNR,"\
        "CALLBACKITEMS.KZPOSART,"\
        "CALLBACKITEMS.POSNR_DONE,"\
        "CALLBACKITEMS.CALLBACKTIMEWISHED,"\
        "CALLBACKITEMS.CALLBACKDATEWISHED,"\
        "CALLBACKITEMS.CALLBACKTIME,"\
        "CALLBACKITEMS.STATE,"\
        "CALLBACKITEMS.LOCKKZ,"\
        "CALLBACKITEMS.SHIFTCOUNT,"\
        "CALLBACKITEMS.REASONNO,"\
        "CALLBACKITEMS.REFERENCE,"\
        "CALLBACKITEMS.CALLBACKSTATUSID"

/* SqlDefine of CALLBACKATTACH ************************************************/


#define CALLBACKATTACH_UPDLISTE \
        "UID=?,"\
        "CALLBACKPARTNO=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "FILIALNR=?,"\
        "REASONNO=?"
/* SqlDefine of CALLBACKPARTNER ***********************************************/


#define CALLBACKPARTNER_UPDLISTE \
        "CALLBACKPARTNO=?,"\
        "CALLBACKPARTNER=?,"\
        "CALLBACKTIME=?,"\
        "VERTRIEBSZENTRUMNR=?"
/* SqlDefine of CALLBACKTIME **************************************************/


#define CALLBACKTIME_UPDLISTE \
        "CALLBACKPARTNO=?,"\
        "OFFICEDAY=?,"\
        "BEGINTIME=?,"\
        "ENDTIME=?"
/* SqlDefine of CALLBACKCRITICAL **********************************************/


#define CALLBACKCRITICAL_UPDLISTE \
        "DIVISIONNAME=?,"\
        "DATUM=?,"\
        "TITEL=?,"\
        "KRITIKNR=?,"\
        "POSNR_DONE=?,"\
        "STATUSID=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "KUNDENNR=?,"\
        "KRITIKLEVEL=?,"\
        "KRITIKTEXT=?,"\
        "USERNAME64=?"
/* SqlDefine of CALLBACKDIVISION **********************************************/


#define CALLBACKDIVISION_UPDLISTE \
        "BRANCHNO=?,"\
        "DIVISIONNAME=?,"\
        "MAILINGLIST=?,"\
        "CALLBACKDIVISIONNO=?"
/* SqlDefine of CALLBACKREASONS ***********************************************/


#define CALLBACKREASONS_UPDLISTE \
        "REASONNO=?,"\
        "CALLBACKREASON=?,"\
        "CALLBACKDIVISIONNO=?,"\
        "MAILINGLIST=?,"\
        "BRANCHNO=?,"\
        "SWONLYMAIL=?"
/* SqlDefine of CALLBACKREMARKS ***********************************************/


#define CALLBACKREMARKS_UPDLISTE \
        "CALLBACKREMARKTEXT=?,"\
        "CALLBACKREMARKHEADER=?"
/* SqlDefine of CALLBACKTODO **************************************************/


#define CALLBACKTODO_UPDLISTE \
        "CALLBACKNO=?,"\
        "CALLBACKPARTNO=?,"\
        "IDFNR=?,"\
        "CALLBACKPARTNER=?,"\
        "KRITIKNR=?,"\
        "POSNR=?,"\
        "KZPOSART=?,"\
        "TITEL=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "CALLBACKTIMEWISHED=?,"\
        "CALLBACKDATEWISHED=?,"\
        "STATE=?,"\
        "NAMEAPO=?,"\
        "KRITIKTEXT=?,"\
        "SHIFTCOUNT=?,"\
        "ORT=?,"\
        "KZKDKLASSE=?,"\
        "REFERENCE=?,"\
        "CALLBACKSTATUSNAME=?"
/* SqlDefine of CALLBACKTODONEW ***********************************************/


#define CALLBACKTODONEW_UPDLISTE \
        "CALLBACKNO=?,"\
        "IDFNR=?,"\
        "DIVISIONNAME=?,"\
        "KRITIKNR=?,"\
        "POSNR=?,"\
        "CALLBACKDIVISIONNO=?,"\
        "TITEL=?,"\
        "KZPOSART=?,"\
        "CALLBACKTIMEWISHED=?,"\
        "VERTRIEBSZENTRUMNR=?,"\
        "CALLBACKDATEWISHED=?,"\
        "STATE=?,"\
        "KRITIKLEVEL=?,"\
        "NAMEAPO=?,"\
        "KRITIKTEXT=?,"\
        "SHIFTCOUNT=?,"\
        "ORT=?,"\
        "KZKDKLASSE=?,"\
        "REFERENCE=?,"\
        "CALLBACKSTATUSNAME=?"
/* SqlDefine of CALLBACKITEMS *************************************************/


#define CALLBACKITEMS_UPDLISTE \
        "CALLBACKNO=?,"\
        "CALLBACKPARTNO=?,"\
        "KRITIKNR=?,"\
        "POSNR=?,"\
        "KZPOSART=?,"\
        "POSNR_DONE=?,"\
        "CALLBACKTIMEWISHED=?,"\
        "CALLBACKDATEWISHED=?,"\
        "CALLBACKTIME=?,"\
        "STATE=?,"\
        "LOCKKZ=?,"\
        "SHIFTCOUNT=?,"\
        "REASONNO=?,"\
        "REFERENCE=?,"\
        "CALLBACKSTATUSID=?"
/* SqlMacros-Define of CALLBACKATTACH *****************************************/

#define CALLBACKATTACH_ZEIGER(x) \
        :x->UID,\
        :x->CALLBACKPARTNO,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->FILIALNR,\
        :x->REASONNO
#define CALLBACKATTACH_ZEIGERSEL(x) \
        :x->UID,\
        :x->CALLBACKPARTNO,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->FILIALNR,\
        :x->REASONNO

/* SqlMacros-Define of CALLBACKPARTNER ****************************************/

#define CALLBACKPARTNER_ZEIGER(x) \
        :x->CALLBACKPARTNO,\
        :x->CALLBACKPARTNER,\
        :x->CALLBACKTIME,\
        :x->VERTRIEBSZENTRUMNR
#define CALLBACKPARTNER_ZEIGERSEL(x) \
        :x->CALLBACKPARTNO,\
        :x->CALLBACKPARTNER,\
        :x->CALLBACKTIME,\
        :x->VERTRIEBSZENTRUMNR

/* SqlMacros-Define of CALLBACKTIME *******************************************/

#define CALLBACKTIME_ZEIGER(x) \
        :x->CALLBACKPARTNO,\
        :x->OFFICEDAY,\
        :x->BEGINTIME,\
        :x->ENDTIME
#define CALLBACKTIME_ZEIGERSEL(x) \
        :x->CALLBACKPARTNO,\
        :x->OFFICEDAY,\
        :x->BEGINTIME,\
        :x->ENDTIME

/* SqlMacros-Define of CALLBACKCRITICAL ***************************************/

#define CALLBACKCRITICAL_ZEIGER(x) \
        :x->DIVISIONNAME,\
        :x->DATUM,\
        :x->TITEL,\
        :x->KRITIKNR,\
        :x->POSNR_DONE,\
        :x->STATUSID,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->KRITIKLEVEL,\
        :x->KRITIKTEXT,\
        :x->USERNAME64
#define CALLBACKCRITICAL_ZEIGERSEL(x) \
        :x->DIVISIONNAME,\
        :x->DATUM,\
        :x->TITEL,\
        :x->KRITIKNR,\
        :x->POSNR_DONE,\
        :x->STATUSID,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->KUNDENNR,\
        :x->KRITIKLEVEL,\
        :x->KRITIKTEXT,\
        :x->USERNAME64

/* SqlMacros-Define of CALLBACKDIVISION ***************************************/

#define CALLBACKDIVISION_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->DIVISIONNAME,\
        :x->MAILINGLIST,\
        :x->CALLBACKDIVISIONNO
#define CALLBACKDIVISION_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->DIVISIONNAME,\
        :x->MAILINGLIST,\
        :x->CALLBACKDIVISIONNO

/* SqlMacros-Define of CALLBACKREASONS ****************************************/

#define CALLBACKREASONS_ZEIGER(x) \
        :x->REASONNO,\
        :x->CALLBACKREASON,\
        :x->CALLBACKDIVISIONNO,\
        :x->MAILINGLIST,\
        :x->BRANCHNO,\
        :x->SWONLYMAIL
#define CALLBACKREASONS_ZEIGERSEL(x) \
        :x->REASONNO,\
        :x->CALLBACKREASON,\
        :x->CALLBACKDIVISIONNO,\
        :x->MAILINGLIST,\
        :x->BRANCHNO,\
        :x->SWONLYMAIL

/* SqlMacros-Define of CALLBACKREMARKS ****************************************/

#define CALLBACKREMARKS_ZEIGER(x) \
        :x->CALLBACKREMARKTEXT,\
        :x->CALLBACKREMARKHEADER
#define CALLBACKREMARKS_ZEIGERSEL(x) \
        :x->REMARKNO,\
        :x->CALLBACKREMARKTEXT,\
        :x->CALLBACKREMARKHEADER

/* SqlMacros-Define of CALLBACKTODO *******************************************/

#define CALLBACKTODO_ZEIGER(x) \
        :x->CALLBACKNO,\
        :x->CALLBACKPARTNO,\
        :x->IDFNR,\
        :x->CALLBACKPARTNER,\
        :x->KRITIKNR,\
        :x->POSNR,\
        :x->KZPOSART,\
        :x->TITEL,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->CALLBACKTIMEWISHED,\
        :x->CALLBACKDATEWISHED,\
        :x->STATE,\
        :x->NAMEAPO,\
        :x->KRITIKTEXT,\
        :x->SHIFTCOUNT,\
        :x->ORT,\
        :x->REFERENCE,\
        :x->KZKDKLASSE
#define CALLBACKTODO_ZEIGERSEL(x) \
        :x->CALLBACKNO,\
        :x->CALLBACKPARTNO,\
        :x->IDFNR,\
        :x->CALLBACKPARTNER,\
        :x->KRITIKNR,\
        :x->POSNR,\
        :x->KZPOSART,\
        :x->TITEL,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->CALLBACKTIMEWISHED,\
        :x->CALLBACKDATEWISHED,\
        :x->STATE,\
        :x->NAMEAPO,\
        :x->KRITIKTEXT,\
        :x->SHIFTCOUNT,\
        :x->ORT,\
        :x->REFERENCE,\
        :x->KZKDKLASSE

/* SqlMacros-Define of CALLBACKTODONEW ****************************************/

#define CALLBACKTODONEW_ZEIGER(x) \
        :x->CALLBACKNO,\
        :x->IDFNR,\
        :x->DIVISIONNAME,\
        :x->KRITIKNR,\
        :x->POSNR,\
        :x->CALLBACKDIVISIONNO,\
        :x->TITEL,\
        :x->KZPOSART,\
        :x->CALLBACKTIMEWISHED,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->CALLBACKDATEWISHED,\
        :x->STATE,\
        :x->KRITIKLEVEL,\
        :x->NAMEAPO,\
        :x->KRITIKTEXT,\
        :x->SHIFTCOUNT,\
        :x->ORT,\
        :x->REFERENCE,\
        :x->KZKDKLASSE
#define CALLBACKTODONEW_ZEIGERSEL(x) \
        :x->CALLBACKNO,\
        :x->IDFNR,\
        :x->DIVISIONNAME,\
        :x->KRITIKNR,\
        :x->POSNR,\
        :x->CALLBACKDIVISIONNO,\
        :x->TITEL,\
        :x->KZPOSART,\
        :x->CALLBACKTIMEWISHED,\
        :x->VERTRIEBSZENTRUMNR,\
        :x->CALLBACKDATEWISHED,\
        :x->STATE,\
        :x->KRITIKLEVEL,\
        :x->NAMEAPO,\
        :x->KRITIKTEXT,\
        :x->SHIFTCOUNT,\
        :x->ORT,\
        :x->REFERENCE,\
        :x->KZKDKLASSE

/* SqlMacros-Define of CALLBACKITEMS ******************************************/

#define CALLBACKITEMS_ZEIGER(x) \
        :x->CALLBACKNO,\
        :x->CALLBACKPARTNO,\
        :x->KRITIKNR,\
        :x->POSNR,\
        :x->KZPOSART,\
        :x->POSNR_DONE,\
        :x->CALLBACKTIMEWISHED,\
        :x->CALLBACKDATEWISHED,\
        :x->CALLBACKTIME,\
        :x->STATE,\
        :x->LOCKKZ,\
        :x->SHIFTCOUNT,\
        :x->REASONNO,\
        :x->REFERENCE,\
        :x->CALLBACKSTATUSID
#define CALLBACKITEMS_ZEIGERSEL(x) \
        :x->CALLBACKNO,\
        :x->CALLBACKPARTNO,\
        :x->KRITIKNR,\
        :x->POSNR,\
        :x->KZPOSART,\
        :x->POSNR_DONE,\
        :x->CALLBACKTIMEWISHED,\
        :x->CALLBACKDATEWISHED,\
        :x->CALLBACKTIME,\
        :x->STATE,\
        :x->LOCKKZ,\
        :x->SHIFTCOUNT,\
        :x->REASONNO,\
        :x->REFERENCE,\
        :x->CALLBACKSTATUSID

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CALLBACKATTACH_H
#define CALLBACKATTACH_ANZ ( sizeof(CALLBACKATTACH_BES) / sizeof(struct buf_desc) )
#define CALLBACKPARTNER_H
#define CALLBACKPARTNER_ANZ ( sizeof(CALLBACKPARTNER_BES) / sizeof(struct buf_desc) )
#define CALLBACKTIME_H
#define CALLBACKTIME_ANZ ( sizeof(CALLBACKTIME_BES) / sizeof(struct buf_desc) )
#define CALLBACKCRITICAL_H
#define CALLBACKCRITICAL_ANZ ( sizeof(CALLBACKCRITICAL_BES) / sizeof(struct buf_desc) )
#define CALLBACKDIVISION_H
#define CALLBACKDIVISION_ANZ ( sizeof(CALLBACKDIVISION_BES) / sizeof(struct buf_desc) )
#define CALLBACKREASONS_H
#define CALLBACKREASONS_ANZ ( sizeof(CALLBACKREASONS_BES) / sizeof(struct buf_desc) )
#define CALLBACKREMARKS_H
#define CALLBACKREMARKS_ANZ ( sizeof(CALLBACKREMARKS_BES) / sizeof(struct buf_desc) )
#define CALLBACKTODO_H
#define CALLBACKTODO_ANZ ( sizeof(CALLBACKTODO_BES) / sizeof(struct buf_desc) )
#define CALLBACKTODONEW_H
#define CALLBACKTODONEW_ANZ ( sizeof(CALLBACKTODONEW_BES) / sizeof(struct buf_desc) )
#define CALLBACKSTATUS_H
#define CALLBACKSTATUS_ANZ ( sizeof(CALLBACKSTATUS_BES) / sizeof(struct buf_desc) )
#define CALLBACKITEMS_H
#define CALLBACKITEMS_ANZ ( sizeof(CALLBACKITEMS_BES) / sizeof(struct buf_desc) )
#endif

#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CALLBACKATTACH ******************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKATTACH {
    long REGIONNR;
    long UID;
    long CALLBACKPARTNO;
    short VERTRIEBSZENTRUMNR;
    short FILIALNR;
    short REASONNO;
    long FETCH_REL;
} callbackattachS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKATTACH {
    long REGIONNR;
    long UID;
    long CALLBACKPARTNO;
    short VERTRIEBSZENTRUMNR;
    short FILIALNR;
    short REASONNO;
    long FETCH_REL;
    bool operator == (const N_CALLBACKATTACH& right) const {
        return (
            REGIONNR == right.REGIONNR &&
            UID == right.UID &&
            CALLBACKPARTNO == right.CALLBACKPARTNO &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            FILIALNR == right.FILIALNR &&
            REASONNO == right.REASONNO
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REGIONNR = 0;
        UID = 0;
        CALLBACKPARTNO = 0;
        VERTRIEBSZENTRUMNR = 0;
        FILIALNR = 0;
        REASONNO = 0;
#endif
    }
} callbackattachS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKPARTNER *****************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKPARTNER {
    long CALLBACKPARTNO;
    char CALLBACKPARTNER[31];
    long REGIONNR;
    short CALLBACKTIME;
    short VERTRIEBSZENTRUMNR;
    long FETCH_REL;
} callbackpartnerS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKPARTNER {
    long CALLBACKPARTNO;
    char CALLBACKPARTNER[31];
    long REGIONNR;
    short CALLBACKTIME;
    short VERTRIEBSZENTRUMNR;
    long FETCH_REL;
    bool operator == (const N_CALLBACKPARTNER& right) const {
        return (
            CALLBACKPARTNO == right.CALLBACKPARTNO &&
            !strcmp(CALLBACKPARTNER, right.CALLBACKPARTNER) &&
            REGIONNR == right.REGIONNR &&
            CALLBACKTIME == right.CALLBACKTIME &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CALLBACKPARTNO = 0;
        strcpy(CALLBACKPARTNER, " " );
        REGIONNR = 0;
        CALLBACKTIME = 0;
        VERTRIEBSZENTRUMNR = 0;
#endif
    }
} callbackpartnerS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKTIME ********************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKTIME {
    long CALLBACKPARTNO;
    short OFFICEDAY;
    short BEGINTIME;
    short ENDTIME;
    long FETCH_REL;
} callbacktimeS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKTIME {
    long CALLBACKPARTNO;
    short OFFICEDAY;
    short BEGINTIME;
    short ENDTIME;
    long FETCH_REL;
    bool operator == (const N_CALLBACKTIME& right) const {
        return (
            CALLBACKPARTNO == right.CALLBACKPARTNO &&
            OFFICEDAY == right.OFFICEDAY &&
            BEGINTIME == right.BEGINTIME &&
            ENDTIME == right.ENDTIME
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CALLBACKPARTNO = 0;
        OFFICEDAY = 0;
        BEGINTIME = 0;
        ENDTIME = 0;
#endif
    }
} callbacktimeS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKCRITICAL ****************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKCRITICAL {
    char DIVISIONNAME[21];
    long DATUM;
    char TITEL[31];
    long KRITIKNR;
    long POSNR_DONE;
    short STATUSID;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short KRITIKLEVEL;
    char KRITIKTEXT[2049];
    char USERNAME64[65];
    long FETCH_REL;
} callbackcriticalS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKCRITICAL {
    char DIVISIONNAME[21];
    long DATUM;
    char TITEL[31];
    long KRITIKNR;
    long POSNR_DONE;
    short STATUSID;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short KRITIKLEVEL;
    char KRITIKTEXT[2049];
    char USERNAME64[65];
    long FETCH_REL;
    bool operator == (const N_CALLBACKCRITICAL& right) const {
        return (
            !strcmp(DIVISIONNAME, right.DIVISIONNAME) &&
            DATUM == right.DATUM &&
            !strcmp(TITEL, right.TITEL) &&
            KRITIKNR == right.KRITIKNR &&
            POSNR_DONE == right.POSNR_DONE &&
            STATUSID == right.STATUSID &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            KUNDENNR == right.KUNDENNR &&
            KRITIKLEVEL == right.KRITIKLEVEL &&
            !strcmp(KRITIKTEXT, right.KRITIKTEXT) &&
            !strcmp(USERNAME64, right.USERNAME64)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(DIVISIONNAME, " " );
        DATUM = 0;
        strcpy(TITEL, " " );
        KRITIKNR = 0;
        POSNR_DONE = 0;
        STATUSID = 0;
        VERTRIEBSZENTRUMNR = 0;
        KUNDENNR = 0;
        KRITIKLEVEL = 0;
        strcpy(KRITIKTEXT, " " );
        strcpy(USERNAME64, " " );
#endif
    }
} callbackcriticalS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKDIVISION ****************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKDIVISION {
    short BRANCHNO;
    char DIVISIONNAME[21];
    long REGIONNR;
    char MAILINGLIST[255];
    short CALLBACKDIVISIONNO;
    long CALLBACKSTART;
    long CALLBACKEND;
    long FETCH_REL;
} callbackdivisionS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKDIVISION {
    short BRANCHNO;
    char DIVISIONNAME[21];
    long REGIONNR;
    char MAILINGLIST[255];
    short CALLBACKDIVISIONNO;
    long CALLBACKSTART;
    long CALLBACKEND;
    long FETCH_REL;
    bool operator == (const N_CALLBACKDIVISION& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            !strcmp(DIVISIONNAME, right.DIVISIONNAME) &&
            REGIONNR == right.REGIONNR &&
            !strcmp(MAILINGLIST, right.MAILINGLIST) &&
            CALLBACKDIVISIONNO == right.CALLBACKDIVISIONNO &&
            CALLBACKSTART == right.CALLBACKSTART &&
            CALLBACKEND == right.CALLBACKEND
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        strcpy(DIVISIONNAME, " " );
        REGIONNR = 0;
        strcpy(MAILINGLIST, " " );
        CALLBACKDIVISIONNO = 0;
        CALLBACKSTART = 0;
        CALLBACKEND = 0;
#endif
    }
} callbackdivisionS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKREASONS *****************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKREASONS {
    short REASONNO;
    char CALLBACKREASON[31];
    short CALLBACKDIVISIONNO;
    char MAILINGLIST[255];
    short BRANCHNO;
    short SWONLYMAIL;
    long FETCH_REL;
} callbackreasonsS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKREASONS {
    short REASONNO;
    char CALLBACKREASON[31];
    short CALLBACKDIVISIONNO;
    char MAILINGLIST[255];
    short BRANCHNO;
    short SWONLYMAIL;
    long FETCH_REL;
    bool operator == (const N_CALLBACKREASONS& right) const {
        return (
            REASONNO == right.REASONNO &&
            !strcmp(CALLBACKREASON, right.CALLBACKREASON) &&
            CALLBACKDIVISIONNO == right.CALLBACKDIVISIONNO &&
            !strcmp(MAILINGLIST, right.MAILINGLIST) &&
            BRANCHNO == right.BRANCHNO &&
            SWONLYMAIL == right.SWONLYMAIL
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REASONNO = 0;
        strcpy(CALLBACKREASON, " " );
        CALLBACKDIVISIONNO = 0;
        strcpy(MAILINGLIST, " " );
        BRANCHNO = 0;
        SWONLYMAIL = 0;
#endif
    }
} callbackreasonsS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKREMARKS *****************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKREMARKS {
    long REMARKNO;
    char CALLBACKREMARKTEXT[255];
    char CALLBACKREMARKHEADER[255];
    long FETCH_REL;
} callbackremarksS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKREMARKS {
    long REMARKNO;
    char CALLBACKREMARKTEXT[255];
    char CALLBACKREMARKHEADER[255];
    long FETCH_REL;
    bool operator == (const N_CALLBACKREMARKS& right) const {
        return (
            REMARKNO == right.REMARKNO &&
            !strcmp(CALLBACKREMARKTEXT, right.CALLBACKREMARKTEXT) &&
            !strcmp(CALLBACKREMARKHEADER, right.CALLBACKREMARKHEADER)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        REMARKNO = 0;
        strcpy(CALLBACKREMARKTEXT, " " );
        strcpy(CALLBACKREMARKHEADER, " " );
#endif
    }
} callbackremarksS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKTODO ********************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKTODO {
    long CALLBACKNO;
    long CALLBACKPARTNO;
    long IDFNR;
    char CALLBACKPARTNER[31];
    long REGIONNR;
    long KRITIKNR;
    long POSNR;
    char KZPOSART[2];
    char TITEL[31];
    short VERTRIEBSZENTRUMNR;
    long CALLBACKTIMEWISHED;
    long CALLBACKDATEWISHED;
    char STATE[2];
    char NAMEAPO[41];
    char KRITIKTEXT[2049];
    short SHIFTCOUNT;
    char ORT[31];
    char KZKDKLASSE[4];
    long UID;
    short FILIALNR;
    char REFERENCE[151];
    char STATUS[51];
    long FETCH_REL;
} callbacktodoS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKTODO {
    long CALLBACKNO;
    long CALLBACKPARTNO;
    long IDFNR;
    char CALLBACKPARTNER[31];
    long REGIONNR;
    long KRITIKNR;
    long POSNR;
    char KZPOSART[2];
    char TITEL[31];
    short VERTRIEBSZENTRUMNR;
    long CALLBACKTIMEWISHED;
    long CALLBACKDATEWISHED;
    char STATE[2];
    char NAMEAPO[41];
    char KRITIKTEXT[2049];
    short SHIFTCOUNT;
    char ORT[31];
    char KZKDKLASSE[4];
    long UID;
    short FILIALNR;
    char REFERENCE[151];
    char STATUS[51];
    long FETCH_REL;
    bool operator == (const N_CALLBACKTODO& right) const {
        return (
            CALLBACKNO == right.CALLBACKNO &&
            CALLBACKPARTNO == right.CALLBACKPARTNO &&
            IDFNR == right.IDFNR &&
            !strcmp(CALLBACKPARTNER, right.CALLBACKPARTNER) &&
            REGIONNR == right.REGIONNR &&
            KRITIKNR == right.KRITIKNR &&
            POSNR == right.POSNR &&
            !strcmp(KZPOSART, right.KZPOSART) &&
            !strcmp(TITEL, right.TITEL) &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            CALLBACKTIMEWISHED == right.CALLBACKTIMEWISHED &&
            CALLBACKDATEWISHED == right.CALLBACKDATEWISHED &&
            !strcmp(STATE, right.STATE) &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(KRITIKTEXT, right.KRITIKTEXT) &&
            SHIFTCOUNT == right.SHIFTCOUNT &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(KZKDKLASSE, right.KZKDKLASSE) &&
            UID == right.UID &&
            FILIALNR == right.FILIALNR &&
            !strcmp(REFERENCE, right.REFERENCE) &&
            !strcmp(STATUS, right.STATUS)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CALLBACKNO = 0;
        CALLBACKPARTNO = 0;
        IDFNR = 0;
        strcpy(CALLBACKPARTNER, " " );
        REGIONNR = 0;
        KRITIKNR = 0;
        POSNR = 0;
        strcpy(KZPOSART, " " );
        strcpy(TITEL, " " );
        VERTRIEBSZENTRUMNR = 0;
        CALLBACKTIMEWISHED = 0;
        CALLBACKDATEWISHED = 0;
        strcpy(STATE, " " );
        strcpy(NAMEAPO, " " );
        strcpy(KRITIKTEXT, " " );
        SHIFTCOUNT = 0;
        strcpy(ORT, " " );
        strcpy(KZKDKLASSE, " " );
        UID = 0;
        FILIALNR = 0;
        strcpy(REFERENCE, "");
        strcpy(STATUS, "");
#endif
    }
} callbacktodoS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKTODONEW *****************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKTODONEW {
    long CALLBACKNO;
    long IDFNR;
    long REGIONNR;
    char DIVISIONNAME[21];
    long KRITIKNR;
    long POSNR;
    short CALLBACKDIVISIONNO;
    char TITEL[31];
    char KZPOSART[2];
    long CALLBACKTIMEWISHED;
    short VERTRIEBSZENTRUMNR;
    long CALLBACKDATEWISHED;
    char STATE[2];
    short KRITIKLEVEL;
    char NAMEAPO[41];
    char KRITIKTEXT[2049];
    short SHIFTCOUNT;
    char ORT[31];
    char KZKDKLASSE[4];
    long UID;
    short FILIALNR;
    char REFERENCE[151];
    char STATUS[51];
    long FETCH_REL;
} callbacktodonewS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKTODONEW {
    long CALLBACKNO;
    long IDFNR;
    long REGIONNR;
    char DIVISIONNAME[21];
    long KRITIKNR;
    long POSNR;
    short CALLBACKDIVISIONNO;
    char TITEL[31];
    char KZPOSART[2];
    long CALLBACKTIMEWISHED;
    short VERTRIEBSZENTRUMNR;
    long CALLBACKDATEWISHED;
    char STATE[2];
    short KRITIKLEVEL;
    char NAMEAPO[41];
    char KRITIKTEXT[2049];
    short SHIFTCOUNT;
    char ORT[31];
    char KZKDKLASSE[4];
    long UID;
    short FILIALNR;
    char REFERENCE[151];
    char STATUS[51];
    long FETCH_REL;
    bool operator == (const N_CALLBACKTODONEW& right) const {
        return (
            CALLBACKNO == right.CALLBACKNO &&
            IDFNR == right.IDFNR &&
            REGIONNR == right.REGIONNR &&
            !strcmp(DIVISIONNAME, right.DIVISIONNAME) &&
            KRITIKNR == right.KRITIKNR &&
            POSNR == right.POSNR &&
            CALLBACKDIVISIONNO == right.CALLBACKDIVISIONNO &&
            !strcmp(TITEL, right.TITEL) &&
            !strcmp(KZPOSART, right.KZPOSART) &&
            CALLBACKTIMEWISHED == right.CALLBACKTIMEWISHED &&
            VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
            CALLBACKDATEWISHED == right.CALLBACKDATEWISHED &&
            !strcmp(STATE, right.STATE) &&
            KRITIKLEVEL == right.KRITIKLEVEL &&
            !strcmp(NAMEAPO, right.NAMEAPO) &&
            !strcmp(KRITIKTEXT, right.KRITIKTEXT) &&
            SHIFTCOUNT == right.SHIFTCOUNT &&
            !strcmp(ORT, right.ORT) &&
            !strcmp(KZKDKLASSE, right.KZKDKLASSE) &&
            UID == right.UID &&
            FILIALNR == right.FILIALNR &&
            !strcmp(REFERENCE, right.REFERENCE) &&
            !strcmp(STATUS, right.STATUS)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CALLBACKNO = 0;
        IDFNR = 0;
        REGIONNR = 0;
        strcpy(DIVISIONNAME, " " );
        KRITIKNR = 0;
        POSNR = 0;
        CALLBACKDIVISIONNO = 0;
        strcpy(TITEL, " " );
        strcpy(KZPOSART, " " );
        CALLBACKTIMEWISHED = 0;
        VERTRIEBSZENTRUMNR = 0;
        CALLBACKDATEWISHED = 0;
        strcpy(STATE, " " );
        KRITIKLEVEL = 0;
        strcpy(NAMEAPO, " " );
        strcpy(KRITIKTEXT, " " );
        SHIFTCOUNT = 0;
        strcpy(ORT, " " );
        strcpy(KZKDKLASSE, " " );
        UID = 0;
        FILIALNR = 0;
        strcpy(REFERENCE, "");
        strcpy(STATUS, "");
#endif
    }
} callbacktodonewS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKSTATUS *****************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKSTATUS {
    short STATUSID;
    char  STATUSNAME[51];
    short STATUSTAG;
    long FETCH_REL;
} callbackstatusS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKSTATUS {
    short STATUSID;
    char  STATUSNAME[51];
    short STATUSTAG;
    long FETCH_REL;
    bool operator == (const N_CALLBACKSTATUS& right) const {
        return (
            STATUSID == right.STATUSID &&
            !strcmp(STATUSNAME, right.STATUSNAME) &&
            STATUSTAG == right.STATUSTAG
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        STATUSID = 0;
        strcpy(STATUSNAME, "" );
        STATUSTAG = 0;
#endif
    }
} callbackstatusS;
#endif /* TRANSCLASS */

/* original struct of CALLBACKITEMS *******************************************/

#ifndef TRANSCLASS
typedef struct N_CALLBACKITEMS {
    long CALLBACKNO;
    long CALLBACKPARTNO;
    long KRITIKNR;
    long POSNR;
    char KZPOSART[2];
    long POSNR_DONE;
    long CALLBACKTIMEWISHED;
    long CALLBACKDATEWISHED;
    short CALLBACKTIME;
    char STATE[2];
    char LOCKKZ[2];
    short SHIFTCOUNT;
    short REASONNO;
    char REFERENCE[151];
    short STATUSID;
    long FETCH_REL;
} callbackitemsS;
#else /* TRANSCLASS */
typedef struct N_CALLBACKITEMS {
    long CALLBACKNO;
    long CALLBACKPARTNO;
    long KRITIKNR;
    long POSNR;
    char KZPOSART[2];
    long POSNR_DONE;
    long CALLBACKTIMEWISHED;
    long CALLBACKDATEWISHED;
    short CALLBACKTIME;
    char STATE[2];
    char LOCKKZ[2];
    short SHIFTCOUNT;
    short REASONNO;
    char REFERENCE[151];
    short STATUSID;
    long FETCH_REL;
    bool operator == (const N_CALLBACKITEMS& right) const {
        return (
            CALLBACKNO == right.CALLBACKNO &&
            CALLBACKPARTNO == right.CALLBACKPARTNO &&
            KRITIKNR == right.KRITIKNR &&
            POSNR == right.POSNR &&
            !strcmp(KZPOSART, right.KZPOSART) &&
            POSNR_DONE == right.POSNR_DONE &&
            CALLBACKTIMEWISHED == right.CALLBACKTIMEWISHED &&
            CALLBACKDATEWISHED == right.CALLBACKDATEWISHED &&
            CALLBACKTIME == right.CALLBACKTIME &&
            !strcmp(STATE, right.STATE) &&
            !strcmp(LOCKKZ, right.LOCKKZ) &&
            SHIFTCOUNT == right.SHIFTCOUNT &&
            REASONNO == right.REASONNO &&
            !strcmp(REFERENCE, right.REFERENCE) &&
            STATUSID == right.STATUSID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CALLBACKNO = 0;
        CALLBACKPARTNO = 0;
        KRITIKNR = 0;
        POSNR = 0;
        strcpy(KZPOSART, " " );
        POSNR_DONE = 0;
        CALLBACKTIMEWISHED = 0;
        CALLBACKDATEWISHED = 0;
        CALLBACKTIME = 0;
        strcpy(STATE, " " );
        strcpy(LOCKKZ, " " );
        SHIFTCOUNT = 0;
        REASONNO = 0;
        strcpy(REFERENCE, "");
        STATUSID = 0;
#endif
    }
} callbackitemsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CALLBACKATTACH ******************************/

struct C_CALLBACKATTACH {
    long REGIONNR;
    long UID;
    long CALLBACKPARTNO;
    short VERTRIEBSZENTRUMNR;
    short FILIALNR;
    short REASONNO;
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKPARTNER *****************************/

struct C_CALLBACKPARTNER {
    long CALLBACKPARTNO;
    char CALLBACKPARTNER[31];
    long REGIONNR;
    short CALLBACKTIME;
    short VERTRIEBSZENTRUMNR;
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKTIME ********************************/

struct C_CALLBACKTIME {
    long CALLBACKPARTNO;
    short OFFICEDAY;
    short BEGINTIME;
    short ENDTIME;
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKCRITICAL ****************************/

struct C_CALLBACKCRITICAL {
    char DIVISIONNAME[21];
    long DATUM;
    char TITEL[31];
    long KRITIKNR;
    long POSNR_DONE;
    short STATUSID;
    short VERTRIEBSZENTRUMNR;
    long KUNDENNR;
    short KRITIKLEVEL;
    char KRITIKTEXT[2049];
    char USERNAME64[65];
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKDIVISION ****************************/

struct C_CALLBACKDIVISION {
    short BRANCHNO;
    char DIVISIONNAME[21];
    long REGIONNR;
    char MAILINGLIST[255];
    short CALLBACKDIVISIONNO;
    long CALLBACKSTART;
    long CALLBACKEND;
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKREASONS *****************************/

struct C_CALLBACKREASONS {
    short REASONNO;
    char CALLBACKREASON[31];
    short CALLBACKDIVISIONNO;
    char MAILINGLIST[255];
    short BRANCHNO;
    short SWONLYMAIL;
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKREMARKS *****************************/

struct C_CALLBACKREMARKS {
    long REMARKNO;
    char CALLBACKREMARKTEXT[255];
    char CALLBACKREMARKHEADER[255];
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKTODO ********************************/

struct C_CALLBACKTODO {
    long CALLBACKNO;
    long CALLBACKPARTNO;
    long IDFNR;
    char CALLBACKPARTNER[31];
    long REGIONNR;
    long KRITIKNR;
    long POSNR;
    char KZPOSART;
    char TITEL[31];
    short VERTRIEBSZENTRUMNR;
    long CALLBACKTIMEWISHED;
    long CALLBACKDATEWISHED;
    char STATE;
    char NAMEAPO[41];
    char KRITIKTEXT[2049];
    short SHIFTCOUNT;
    char ORT[31];
    char KZKDKLASSE[4];
    long UID;
    short FILIALNR;
    char REFERENCE[151];
    char STATUS[51];
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKTODONEW *****************************/

struct C_CALLBACKTODONEW {
    long CALLBACKNO;
    long IDFNR;
    long REGIONNR;
    char DIVISIONNAME[21];
    long KRITIKNR;
    long POSNR;
    short CALLBACKDIVISIONNO;
    char TITEL[31];
    char KZPOSART;
    long CALLBACKTIMEWISHED;
    short VERTRIEBSZENTRUMNR;
    long CALLBACKDATEWISHED;
    char STATE;
    short KRITIKLEVEL;
    char NAMEAPO[41];
    char KRITIKTEXT[2049];
    short SHIFTCOUNT;
    char ORT[31];
    char KZKDKLASSE[4];
    long UID;
    short FILIALNR;
    char REFERENCE[151];
    char STATUS[51];
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKSTATUS *****************************/

struct C_CALLBACKSTATUS {

    short STATUSID;
    char  STATUSNAME[51];
    short STATUSTAG;
    long FETCH_REL;
};
/* Structur with real chartype of CALLBACKITEMS *******************************/

struct C_CALLBACKITEMS {
    long CALLBACKNO;
    long CALLBACKPARTNO;
    long KRITIKNR;
    long POSNR;
    char KZPOSART;
    long POSNR_DONE;
    long CALLBACKTIMEWISHED;
    long CALLBACKDATEWISHED;
    short CALLBACKTIME;
    char STATE;
    char LOCKKZ;
    short SHIFTCOUNT;
    short REASONNO;
    char REFERENCE[151];
    short STATUSID;
    long FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CALLBACKATTACH ****************************/

struct I_CALLBACKATTACH {
    short REGIONNR;
    short UID;
    short CALLBACKPARTNO;
    short VERTRIEBSZENTRUMNR;
    short FILIALNR;
    short REASONNO;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKPARTNER ***************************/

struct I_CALLBACKPARTNER {
    short CALLBACKPARTNO;
    short CALLBACKPARTNER;
    short REGIONNR;
    short CALLBACKTIME;
    short VERTRIEBSZENTRUMNR;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKTIME ******************************/

struct I_CALLBACKTIME {
    short CALLBACKPARTNO;
    short OFFICEDAY;
    short BEGINTIME;
    short ENDTIME;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKCRITICAL **************************/

struct I_CALLBACKCRITICAL {
    short DIVISIONNAME;
    short DATUM;
    short TITEL;
    short KRITIKNR;
    short POSNR_DONE;
    short STATUSID;
    short VERTRIEBSZENTRUMNR;
    short KUNDENNR;
    short KRITIKLEVEL;
    short KRITIKTEXT;
    short USERNAME64;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKDIVISION **************************/

struct I_CALLBACKDIVISION {
    short BRANCHNO;
    short DIVISIONNAME;
    short REGIONNR;
    short MAILINGLIST;
    short CALLBACKDIVISIONNO;
    short CALLBACKSTART;
    short CALLBACKEND;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKREASONS ***************************/

struct I_CALLBACKREASONS {
    short REASONNO;
    short CALLBACKREASON;
    short CALLBACKDIVISIONNO;
    short MAILINGLIST;
    short BRANCHNO;
    short SWONLYMAIL;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKREMARKS ***************************/

struct I_CALLBACKREMARKS {
    short REMARKNO;
    short CALLBACKREMARKTEXT;
    short CALLBACKREMARKHEADER;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKTODO ******************************/

struct I_CALLBACKTODO {
    short CALLBACKNO;
    short CALLBACKPARTNO;
    short IDFNR;
    short CALLBACKPARTNER;
    short REGIONNR;
    short KRITIKNR;
    short POSNR;
    short KZPOSART;
    short TITEL;
    short VERTRIEBSZENTRUMNR;
    short CALLBACKTIMEWISHED;
    short CALLBACKDATEWISHED;
    short STATE;
    short NAMEAPO;
    short KRITIKTEXT;
    short SHIFTCOUNT;
    short ORT;
    short KZKDKLASSE;
    short UID;
    short FILIALNR;
    short REFERENCE;
    short STATUS;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKTODONEW ***************************/

struct I_CALLBACKTODONEW {
    short CALLBACKNO;
    short IDFNR;
    short REGIONNR;
    short DIVISIONNAME;
    short KRITIKNR;
    short POSNR;
    short CALLBACKDIVISIONNO;
    short TITEL;
    short KZPOSART;
    short CALLBACKTIMEWISHED;
    short VERTRIEBSZENTRUMNR;
    short CALLBACKDATEWISHED;
    short STATE;
    short KRITIKLEVEL;
    short NAMEAPO;
    short KRITIKTEXT;
    short SHIFTCOUNT;
    short ORT;
    short KZKDKLASSE;
    short UID;
    short FILIALNR;
    short REFERENCE;
    short STATUS;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKSTATUS ***************************/

struct I_CALLBACKSTATUS {
    short STATUSID;
    short STATUSNAME;
    short STATUSTAG;
    short FETCH_REL;
};
/* Sizetype  Structur (buf_desc) of CALLBACKITEMS *****************************/

struct I_CALLBACKITEMS {
    short CALLBACKNO;
    short CALLBACKPARTNO;
    short KRITIKNR;
    short POSNR;
    short KZPOSART;
    short POSNR_DONE;
    short CALLBACKTIMEWISHED;
    short CALLBACKDATEWISHED;
    short CALLBACKTIME;
    short STATE;
    short LOCKKZ;
    short SHIFTCOUNT;
    short REASONNO;
    short REFERENCE;
    short STATUSID;
    short FETCH_REL;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CALLBACKATTACH **************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKATTACH_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKATTACH_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKPARTNER *************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKPARTNER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKPARTNER_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKTIME ****************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKTIME_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKTIME_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKCRITICAL ************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKCRITICAL_BES [] = {
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2048, 0 },
   { TYP_C, 64, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKCRITICAL_BES [] = {
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2048, 0 },
   { TYP_C, 64, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKDIVISION ************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKDIVISION_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKDIVISION_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKREASONS *************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKREASONS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKREASONS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKREMARKS *************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKREMARKS_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 254, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKREMARKS_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 254, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKTODO ****************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKTODO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 2048, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 150, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKTODO_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 2048, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 150, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKTODONEW *************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKTODONEW_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 2048, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 150, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKTODONEW_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 40, 0 },
   { TYP_C, 2048, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 150, 0 },
   { TYP_C, 50, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKSTATUS ***************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKSTATUS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKSTATUS_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 50, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* Structur (buf_desc) of CALLBACKITEMS ***************************************/

#if defined (BUF_DESC)
static struct buf_desc CALLBACKITEMS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 150, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CALLBACKITEMS_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 150, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
};
#endif

/* FunctionNumber-Define of CallBackAttach ************************************/

#define CALLBACKATTACH_DELETE 1010
#define CALLBACKATTACH_INSERT 1009
#define CALLBACKATTACH_SEL 1012
#define CALLBACKATTACH_SELVZ 1321

/* FunctionNumber-Define of CallBackPartner ***********************************/

#define CALLBACKPARTNER_DELETECALLBACKPARTNER 1001
#define CALLBACKPARTNER_INSERTWITHNEWNO 1002
#define CALLBACKPARTNER_SELPARTNER 1032
#define CALLBACKPARTNER_SELECTALL 1000
#define CALLBACKPARTNER_SELECTALLVZ 1315
#define CALLBACKPARTNER_UPDATE 1008

/* FunctionNumber-Define of CallBackTime **************************************/

#define CALLBACKTIME_DELETEALLNO 1007
#define CALLBACKTIME_DELETECALLBACKTIME 1004
#define CALLBACKTIME_INSERT 1005
#define CALLBACKTIME_SELECTCALLBACKPARTNER 1003

/* FunctionNumber-Define of CallbackCritical **********************************/

#define CALLBACKCRITICAL_SELCRITICAL 1719

/* FunctionNumber-Define of CallbackDivision **********************************/

#define CALLBACKDIVISION_DELETE 1649
#define CALLBACKDIVISION_INSERTWITHNEWNO 1646
#define CALLBACKDIVISION_SELDIVISION 1677
#define CALLBACKDIVISION_SELLIST 1644
#define CALLBACKDIVISION_SELLISTALL 1647
#define CALLBACKDIVISION_UPDATE 1648

/* FunctionNumber-Define of CallbackReasons ***********************************/

#define CALLBACKREASONS_DELETE 1652
#define CALLBACKREASONS_DELETEALLNO 1653
#define CALLBACKREASONS_INSERTWITHNEWNO 1650
#define CALLBACKREASONS_SELLIST 1645
#define CALLBACKREASONS_UPDATE 1651

/* FunctionNumber-Define of CallbackRemarks ***********************************/

#define CALLBACKREMARKS_DELETEREMARK 1727
#define CALLBACKREMARKS_INSERT 1726
#define CALLBACKREMARKS_SELLIST 1723
#define CALLBACKREMARKS_SELREMARK 1725
#define CALLBACKREMARKS_UPDATE 1724

/* FunctionNumber-Define of CallbackToDo **************************************/

#define CALLBACKTODO_SELALLLOCKED 1041
#define CALLBACKTODO_SELALLLOCKEDVZ 1316
#define CALLBACKTODO_SELALLNOTDONE 1039
#define CALLBACKTODO_SELALLNOTDONEVZ 1317
#define CALLBACKTODO_SELCALLBACKFUTURE 1036
#define CALLBACKTODO_SELCALLBACKFUTUREVZ 1318
#define CALLBACKTODO_SELCALLBACKOPEN 1033
#define CALLBACKTODO_SELCALLBACKOPENVZ 1319
#define CALLBACKTODO_SELCALLBACKWISHED 1035
#define CALLBACKTODO_SELCALLBACKWISHEDVZ 1320

/* FunctionNumber-Define of CallbackToDoNew ***********************************/

#define CALLBACKTODONEW_SELALLLOCKED 1654
#define CALLBACKTODONEW_SELALLLOCKEDVZ 1655
#define CALLBACKTODONEW_SELALLNOTDONE 1656
#define CALLBACKTODONEW_SELALLNOTDONEVZ 1657
#define CALLBACKTODONEW_SELCALLBACKFUTURE 1658
#define CALLBACKTODONEW_SELCALLBACKFUTUREVZ 1659
#define CALLBACKTODONEW_SELCALLBACKOPEN 1660
#define CALLBACKTODONEW_SELCALLBACKOPENVZ 1661
#define CALLBACKTODONEW_SELCALLBACKWISHED 1662
#define CALLBACKTODONEW_SELCALLBACKWISHEDVZ 1663

/* FunctionNumber-Define of CallbackStatus ***********************************/

#define CALLBACKSATATUS_SELECTALL 1670

/* FunctionNumber-Define of callbackitems *************************************/

#define CALLBACKITEMS_INSERTWITHNEWNO 1030
#define CALLBACKITEMS_SELCALLBACKWISH 1031
#define CALLBACKITEMS_SELNO 1034
#define CALLBACKITEMS_SELNOTDONE 1037
#define CALLBACKITEMS_SELLOCKED 1040
#define CALLBACKITEMS_UPDATEITEM 1029

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CallBackAttach ********************************/

#define Delete 1010
#define Insert 1009
#define Sel 1012
#define SelVz 1321

/* Old-FunctionNumber-Define of CallBackPartner *******************************/

#define DeleteCallbackPartner 1001
#define InsertWithNewNo 1002
#define SelPartner 1032
#define SelectAll 1000
#define SelectAllVz 1315
#define Update 1008

/* Old-FunctionNumber-Define of CallBackTime **********************************/

#define DeleteAllNo 1007
#define DeleteCallbackTime 1004
#define Insert 1005
#define SelectCallbackPartner 1003

/* Old-FunctionNumber-Define of CallbackCritical ******************************/

#define SelCritical 1719

/* Old-FunctionNumber-Define of CallbackDivision ******************************/

#define Delete 1649
#define InsertWithNewNo 1646
#define SelDivision 1677
#define SelList 1644
#define SelListAll 1647
#define Update 1648

/* Old-FunctionNumber-Define of CallbackReasons *******************************/

#define Delete 1652
#define DeleteAllNo 1653
#define InsertWithNewNo 1650
#define SelList 1645
#define Update 1651

/* Old-FunctionNumber-Define of CallbackRemarks *******************************/

#define DeleteRemark 1727
#define Insert 1726
#define SelList 1723
#define SelRemark 1725
#define Update 1724

/* Old-FunctionNumber-Define of CallbackToDo **********************************/

#define SelAllLocked 1041
#define SelAllLockedVz 1316
#define SelAllNotDone 1039
#define SelAllNotDoneVz 1317
#define SelCallbackFuture 1036
#define SelCallbackFutureVz 1318
#define SelCallbackOpen 1033
#define SelCallbackOpenVz 1319
#define SelCallbackWished 1035
#define SelCallbackWishedVz 1320

/* Old-FunctionNumber-Define of CallbackToDoNew *******************************/

#define SelAllLocked 1654
#define SelAllLockedVz 1655
#define SelAllNotDone 1656
#define SelAllNotDoneVz 1657
#define SelCallbackFuture 1658
#define SelCallbackFutureVz 1659
#define SelCallbackOpen 1660
#define SelCallbackOpenVz 1661
#define SelCallbackWished 1662
#define SelCallbackWishedVz 1663

/* Old-FunctionNumber-Define of callbackitems *********************************/

#define InsertWithNewNo 1030
#define SelCallbackWish 1031
#define SelNo 1034
#define SelNotDone 1037
#define Sellocked 1040
#define UpdateItem 1029

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

class CCALLBACKATTACH : public ppDadeVirtual {
public:
    callbackattachS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbackattachS> lst; // class list

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
                     vector< callbackattachS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbackattachS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbackattachS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbackattachS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbackattachS>::iterator
                 endList  () { return lst.end  (); }

    long         GetRegionnr() const { return s.REGIONNR; }
    long         GetUid() const { return s.UID; }
    long         GetCallbackpartno() const { return s.CALLBACKPARTNO; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    short        GetFilialnr() const { return s.FILIALNR; }
    short        GetReasonno() const { return s.REASONNO; }

    const callbackattachS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetUid(long t) { s.UID = t; }
    void         SetCallbackpartno(long t) { s.CALLBACKPARTNO = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetReasonno(short t) { s.REASONNO = t; }

    void         SetStruct(const callbackattachS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1010, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1009, pos); Strip(s); return ret; }
    int          Sel(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1012, FetchRel, pos); return ret; }
    int          SelVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1321, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKATTACH() {
        ::buf_default((void *)&s, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKATTACH() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKATTACH_BES, CALLBACKATTACH_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKATTACH_BES, (int)CALLBACKATTACH_ANZ, error_msg);
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
        if ( fkt_nr == 1010 ) return UniqueServerCall(1010, pos);
        if ( fkt_nr == 1009 ) return UniqueServerCall(1009, pos);
        if ( fkt_nr == 1012 ) return CursorServerCall(1012, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1321 ) return CursorServerCall(1321, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKATTACH & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKATTACH_BES, (int)CALLBACKATTACH_ANZ, error_msg);
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
        CCALLBACKATTACH c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKATTACH_BES, (int)CALLBACKATTACH_ANZ, error_msg);
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

class CCALLBACKPARTNER : public ppDadeVirtual {
public:
    callbackpartnerS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbackpartnerS> lst; // class list

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
                     vector< callbackpartnerS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbackpartnerS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbackpartnerS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbackpartnerS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbackpartnerS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCallbackpartno() const { return s.CALLBACKPARTNO; }
    const char*  GetCallbackpartner(ppString & t) const { t = s.CALLBACKPARTNER; t.erasespace(ppString::END); return t.c_str(); }
    long         GetRegionnr() const { return s.REGIONNR; }
    short        GetCallbacktime() const { return s.CALLBACKTIME; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }

    const callbackpartnerS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCallbackpartno(long t) { s.CALLBACKPARTNO = t; }
    void         SetCallbackpartner(const ppString & t) { ppGStrCopy(s.CALLBACKPARTNER, t.c_str(), L_CALLBACKPARTNER_CALLBACKPARTNER); }
    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetCallbacktime(short t) { s.CALLBACKTIME = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }

    void         SetStruct(const callbackpartnerS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DeleteCallbackPartner(int pos = 0) { return UniqueServerCall(1001, pos); }
    int          InsertWithNewNo(int pos = 0) { int ret = UniqueServerCall(1002, pos); Strip(s); return ret; }
    int          SelPartner(int pos = 0) { int ret = UniqueServerCall(1032, pos); Strip(s); return ret; }
    int          SelectAll(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1000, FetchRel, pos); return ret; }
    int          SelectAllVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1315, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1008, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKPARTNER() {
        ::buf_default((void *)&s, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKPARTNER() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKPARTNER_BES, CALLBACKPARTNER_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKPARTNER_BES, (int)CALLBACKPARTNER_ANZ, error_msg);
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
        if ( fkt_nr == 1001 ) return UniqueServerCall(1001, pos);
        if ( fkt_nr == 1002 ) return UniqueServerCall(1002, pos);
        if ( fkt_nr == 1032 ) return UniqueServerCall(1032, pos);
        if ( fkt_nr == 1000 ) return CursorServerCall(1000, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1315 ) return CursorServerCall(1315, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1008 ) return UniqueServerCall(1008, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKPARTNER & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CALLBACKPARTNER);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKPARTNER_BES, (int)CALLBACKPARTNER_ANZ, error_msg);
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
        CCALLBACKPARTNER c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKPARTNER_BES, (int)CALLBACKPARTNER_ANZ, error_msg);
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

class CCALLBACKTIME : public ppDadeVirtual {
public:
    callbacktimeS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbacktimeS> lst; // class list

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
                     vector< callbacktimeS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbacktimeS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbacktimeS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbacktimeS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbacktimeS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCallbackpartno() const { return s.CALLBACKPARTNO; }
    short        GetOfficeday() const { return s.OFFICEDAY; }
    short        GetBegintime() const { return s.BEGINTIME; }
    short        GetEndtime() const { return s.ENDTIME; }

    const callbacktimeS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCallbackpartno(long t) { s.CALLBACKPARTNO = t; }
    void         SetOfficeday(short t) { s.OFFICEDAY = t; }
    void         SetBegintime(short t) { s.BEGINTIME = t; }
    void         SetEndtime(short t) { s.ENDTIME = t; }

    void         SetStruct(const callbacktimeS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DeleteAllNo(int pos = 0) { return UniqueServerCall(1007, pos); }
    int          DeleteCallbackTime(int pos = 0) { return UniqueServerCall(1004, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1005, pos); Strip(s); return ret; }
    int          SelectCallbackPartner(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1003, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKTIME() {
        ::buf_default((void *)&s, CALLBACKTIME_BES, CALLBACKTIME_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKTIME() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKTIME_BES, CALLBACKTIME_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKTIME_BES, (int)CALLBACKTIME_ANZ, error_msg);
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
        if ( fkt_nr == 1007 ) return UniqueServerCall(1007, pos);
        if ( fkt_nr == 1004 ) return UniqueServerCall(1004, pos);
        if ( fkt_nr == 1005 ) return UniqueServerCall(1005, pos);
        if ( fkt_nr == 1003 ) return CursorServerCall(1003, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKTIME & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKTIME_BES, (int)CALLBACKTIME_ANZ, error_msg);
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
        CCALLBACKTIME c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKTIME_BES, (int)CALLBACKTIME_ANZ, error_msg);
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

class CCALLBACKCRITICAL : public ppDadeVirtual {
public:
    callbackcriticalS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbackcriticalS> lst; // class list

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
                     vector< callbackcriticalS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbackcriticalS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbackcriticalS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbackcriticalS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbackcriticalS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetDivisionname(ppString & t) const { t = s.DIVISIONNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDatum() const { return s.DATUM; }
    const char*  GetTitel(ppString & t) const { t = s.TITEL; t.erasespace(ppString::END); return t.c_str(); }
    long         GetKritiknr() const { return s.KRITIKNR; }
    long         GetPosnr_done() const { return s.POSNR_DONE; }
    short        GetStatusID() const { return s.STATUSID; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetKundennr() const { return s.KUNDENNR; }
    short        GetKritiklevel() const { return s.KRITIKLEVEL; }
    const char*  GetKritiktext(ppString & t) const { t = s.KRITIKTEXT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetUsername64(ppString & t) const { t = s.USERNAME64; t.erasespace(ppString::END); return t.c_str(); }

    const callbackcriticalS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetDivisionname(const ppString & t) { ppGStrCopy(s.DIVISIONNAME, t.c_str(), L_CALLBACKCRITICAL_DIVISIONNAME); }
    void         SetDatum(long t) { s.DATUM = t; }
    void         SetTitel(const ppString & t) { ppGStrCopy(s.TITEL, t.c_str(), L_CALLBACKCRITICAL_TITEL); }
    void         SetKritiknr(long t) { s.KRITIKNR = t; }
    void         SetPosnr_done(long t) { s.POSNR_DONE = t; }
    void         SetStatusID(short t) { s.STATUSID = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetKundennr(long t) { s.KUNDENNR = t; }
    void         SetKritiklevel(short t) { s.KRITIKLEVEL = t; }
    void         SetKritiktext(const ppString & t) { ppGStrCopy(s.KRITIKTEXT, t.c_str(), L_CALLBACKCRITICAL_KRITIKTEXT); }
    void         SetUsername64(const ppString & t) { ppGStrCopy(s.USERNAME64, t.c_str(), L_CALLBACKCRITICAL_USERNAME64); }

    void         SetStruct(const callbackcriticalS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelCritical(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1719, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKCRITICAL() {
        ::buf_default((void *)&s, CALLBACKCRITICAL_BES, CALLBACKCRITICAL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKCRITICAL() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKCRITICAL_BES, CALLBACKCRITICAL_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKCRITICAL_BES, (int)CALLBACKCRITICAL_ANZ, error_msg);
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
        if ( fkt_nr == 1719 ) return CursorServerCall(1719, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKCRITICAL & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DIVISIONNAME);
        ppGStripLast(d.TITEL);
        ppGStripLast(d.KRITIKTEXT);
        ppGStripLast(d.USERNAME64);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKCRITICAL_BES, (int)CALLBACKCRITICAL_ANZ, error_msg);
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
        CCALLBACKCRITICAL c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKCRITICAL_BES, (int)CALLBACKCRITICAL_ANZ, error_msg);
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

class CCALLBACKDIVISION : public ppDadeVirtual {
public:
    callbackdivisionS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbackdivisionS> lst; // class list

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
                     vector< callbackdivisionS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbackdivisionS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbackdivisionS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbackdivisionS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbackdivisionS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    const char*  GetDivisionname(ppString & t) const { t = s.DIVISIONNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetRegionnr() const { return s.REGIONNR; }
    const char*  GetMailinglist(ppString & t) const { t = s.MAILINGLIST; t.erasespace(ppString::END); return t.c_str(); }
    short        GetCallbackdivisionno() const { return s.CALLBACKDIVISIONNO; }
    long         GetCallbackstart() const { return s.CALLBACKSTART; }
    long         GetCallbackend() const { return s.CALLBACKEND; }

    const callbackdivisionS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetDivisionname(const ppString & t) { ppGStrCopy(s.DIVISIONNAME, t.c_str(), L_CALLBACKDIVISION_DIVISIONNAME); }
    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetMailinglist(const ppString & t) { ppGStrCopy(s.MAILINGLIST, t.c_str(), L_CALLBACKDIVISION_MAILINGLIST); }
    void         SetCallbackdivisionno(short t) { s.CALLBACKDIVISIONNO = t; }
    void         SetCallbackstart(long t) { s.CALLBACKSTART = t; }
    void         SetCallbackend(long t) { s.CALLBACKEND = t; }

    void         SetStruct(const callbackdivisionS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1649, pos); }
    int          InsertWithNewNo(int pos = 0) { int ret = UniqueServerCall(1646, pos); Strip(s); return ret; }
    int          SelDivision(int pos = 0) { int ret = UniqueServerCall(1677, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1644, FetchRel, pos); return ret; }
    int          SelListAll(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1647, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1648, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKDIVISION() {
        ::buf_default((void *)&s, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKDIVISION() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKDIVISION_BES, CALLBACKDIVISION_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKDIVISION_BES, (int)CALLBACKDIVISION_ANZ, error_msg);
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
        if ( fkt_nr == 1649 ) return UniqueServerCall(1649, pos);
        if ( fkt_nr == 1646 ) return UniqueServerCall(1646, pos);
        if ( fkt_nr == 1677 ) return UniqueServerCall(1677, pos);
        if ( fkt_nr == 1644 ) return CursorServerCall(1644, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1647 ) return CursorServerCall(1647, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1648 ) return UniqueServerCall(1648, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKDIVISION & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DIVISIONNAME);
        ppGStripLast(d.MAILINGLIST);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKDIVISION_BES, (int)CALLBACKDIVISION_ANZ, error_msg);
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
        CCALLBACKDIVISION c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKDIVISION_BES, (int)CALLBACKDIVISION_ANZ, error_msg);
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

class CCALLBACKREASONS : public ppDadeVirtual {
public:
    callbackreasonsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbackreasonsS> lst; // class list

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
                     vector< callbackreasonsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbackreasonsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbackreasonsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbackreasonsS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbackreasonsS>::iterator
                 endList  () { return lst.end  (); }

    short        GetReasonno() const { return s.REASONNO; }
    const char*  GetCallbackreason(ppString & t) const { t = s.CALLBACKREASON; t.erasespace(ppString::END); return t.c_str(); }
    short        GetCallbackdivisionno() const { return s.CALLBACKDIVISIONNO; }
    const char*  GetMailinglist(ppString & t) const { t = s.MAILINGLIST; t.erasespace(ppString::END); return t.c_str(); }
    short        GetBranchno() const { return s.BRANCHNO; }
    short        GetSwonlymail() const { return s.SWONLYMAIL; }

    const callbackreasonsS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetReasonno(short t) { s.REASONNO = t; }
    void         SetCallbackreason(const ppString & t) { ppGStrCopy(s.CALLBACKREASON, t.c_str(), L_CALLBACKREASONS_CALLBACKREASON); }
    void         SetCallbackdivisionno(short t) { s.CALLBACKDIVISIONNO = t; }
    void         SetMailinglist(const ppString & t) { ppGStrCopy(s.MAILINGLIST, t.c_str(), L_CALLBACKREASONS_MAILINGLIST); }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetSwonlymail(short t) { s.SWONLYMAIL = t; }

    void         SetStruct(const callbackreasonsS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          Delete(int pos = 0) { return UniqueServerCall(1652, pos); }
    int          DeleteAllNo(int pos = 0) { return UniqueServerCall(1653, pos); }
    int          InsertWithNewNo(int pos = 0) { int ret = UniqueServerCall(1650, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1645, FetchRel, pos); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1651, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKREASONS() {
        ::buf_default((void *)&s, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKREASONS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKREASONS_BES, CALLBACKREASONS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKREASONS_BES, (int)CALLBACKREASONS_ANZ, error_msg);
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
        if ( fkt_nr == 1652 ) return UniqueServerCall(1652, pos);
        if ( fkt_nr == 1653 ) return UniqueServerCall(1653, pos);
        if ( fkt_nr == 1650 ) return UniqueServerCall(1650, pos);
        if ( fkt_nr == 1645 ) return CursorServerCall(1645, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1651 ) return UniqueServerCall(1651, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKREASONS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CALLBACKREASON);
        ppGStripLast(d.MAILINGLIST);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKREASONS_BES, (int)CALLBACKREASONS_ANZ, error_msg);
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
        CCALLBACKREASONS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKREASONS_BES, (int)CALLBACKREASONS_ANZ, error_msg);
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

class CCALLBACKREMARKS : public ppDadeVirtual {
public:
    callbackremarksS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbackremarksS> lst; // class list

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
                     vector< callbackremarksS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbackremarksS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbackremarksS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbackremarksS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbackremarksS>::iterator
                 endList  () { return lst.end  (); }

    long         GetRemarkno() const { return s.REMARKNO; }
    const char*  GetCallbackremarktext(ppString & t) const { t = s.CALLBACKREMARKTEXT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetCallbackremarkheader(ppString & t) const { t = s.CALLBACKREMARKHEADER; t.erasespace(ppString::END); return t.c_str(); }

    const callbackremarksS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetRemarkno(long t) { s.REMARKNO = t; }
    void         SetCallbackremarktext(const ppString & t) { ppGStrCopy(s.CALLBACKREMARKTEXT, t.c_str(), L_CALLBACKREMARKS_CALLBACKREMARKTEXT); }
    void         SetCallbackremarkheader(const ppString & t) { ppGStrCopy(s.CALLBACKREMARKHEADER, t.c_str(), L_CALLBACKREMARKS_CALLBACKREMARKHEADER); }

    void         SetStruct(const callbackremarksS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          DeleteRemark(int pos = 0) { return UniqueServerCall(1727, pos); }
    int          Insert(int pos = 0) { int ret = UniqueServerCall(1726, pos); Strip(s); return ret; }
    int          SelList(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1723, FetchRel, pos); return ret; }
    int          SelRemark(int pos = 0) { int ret = UniqueServerCall(1725, pos); Strip(s); return ret; }
    int          Update(int pos = 0) { int ret = UniqueServerCall(1724, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKREMARKS() {
        ::buf_default((void *)&s, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKREMARKS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKREMARKS_BES, CALLBACKREMARKS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKREMARKS_BES, (int)CALLBACKREMARKS_ANZ, error_msg);
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
        if ( fkt_nr == 1727 ) return UniqueServerCall(1727, pos);
        if ( fkt_nr == 1726 ) return UniqueServerCall(1726, pos);
        if ( fkt_nr == 1723 ) return CursorServerCall(1723, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1725 ) return UniqueServerCall(1725, pos);
        if ( fkt_nr == 1724 ) return UniqueServerCall(1724, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKREMARKS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CALLBACKREMARKTEXT);
        ppGStripLast(d.CALLBACKREMARKHEADER);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKREMARKS_BES, (int)CALLBACKREMARKS_ANZ, error_msg);
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
        CCALLBACKREMARKS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKREMARKS_BES, (int)CALLBACKREMARKS_ANZ, error_msg);
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

class CCALLBACKTODO : public ppDadeVirtual {
public:
    callbacktodoS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbacktodoS> lst; // class list

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
                     vector< callbacktodoS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbacktodoS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbacktodoS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbacktodoS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbacktodoS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCallbackno() const { return s.CALLBACKNO; }
    long         GetCallbackpartno() const { return s.CALLBACKPARTNO; }
    long         GetIdfnr() const { return s.IDFNR; }
    const char*  GetCallbackpartner(ppString & t) const { t = s.CALLBACKPARTNER; t.erasespace(ppString::END); return t.c_str(); }
    long         GetRegionnr() const { return s.REGIONNR; }
    long         GetKritiknr() const { return s.KRITIKNR; }
    long         GetPosnr() const { return s.POSNR; }
    char         GetKzposart() const { return s.KZPOSART[0]; }
    const char*  GetTitel(ppString & t) const { t = s.TITEL; t.erasespace(ppString::END); return t.c_str(); }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetCallbacktimewished() const { return s.CALLBACKTIMEWISHED; }
    long         GetCallbackdatewished() const { return s.CALLBACKDATEWISHED; }
    char         GetState() const { return s.STATE[0]; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKritiktext(ppString & t) const { t = s.KRITIKTEXT; t.erasespace(ppString::END); return t.c_str(); }
    short        GetShiftcount() const { return s.SHIFTCOUNT; }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKzkdklasse(ppString & t) const { t = s.KZKDKLASSE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetUid() const { return s.UID; }
    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetReference(ppString& t) const { t = s.REFERENCE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStatus(ppString& t) const { t = s.STATUS; t.erasespace(ppString::END); return t.c_str(); }

    const callbacktodoS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCallbackno(long t) { s.CALLBACKNO = t; }
    void         SetCallbackpartno(long t) { s.CALLBACKPARTNO = t; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetCallbackpartner(const ppString & t) { ppGStrCopy(s.CALLBACKPARTNER, t.c_str(), L_CALLBACKTODO_CALLBACKPARTNER); }
    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetKritiknr(long t) { s.KRITIKNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetKzposart(char t) { s.KZPOSART[0] = t; s.KZPOSART[1] = '\0';}
    void         SetTitel(const ppString & t) { ppGStrCopy(s.TITEL, t.c_str(), L_CALLBACKTODO_TITEL); }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetCallbacktimewished(long t) { s.CALLBACKTIMEWISHED = t; }
    void         SetCallbackdatewished(long t) { s.CALLBACKDATEWISHED = t; }
    void         SetState(char t) { s.STATE[0] = t; s.STATE[1] = '\0';}
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_CALLBACKTODO_NAMEAPO); }
    void         SetKritiktext(const ppString & t) { ppGStrCopy(s.KRITIKTEXT, t.c_str(), L_CALLBACKTODO_KRITIKTEXT); }
    void         SetShiftcount(short t) { s.SHIFTCOUNT = t; }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_CALLBACKTODO_ORT); }
    void         SetKzkdklasse(const ppString & t) { ppGStrCopy(s.KZKDKLASSE, t.c_str(), L_CALLBACKTODO_KZKDKLASSE); }
    void         SetUid(long t) { s.UID = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetReference(const ppString& t) { ppGStrCopy(s.REFERENCE, t.c_str(), L_CALLBACKTODO_REFERENCE); }
    void         SetStatus(const ppString& t) { ppGStrCopy(s.STATUS, t.c_str(), L_CALLBACKTODONEW_STATUS); }

    void         SetStruct(const callbacktodoS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelAllLocked(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1041, FetchRel, pos); return ret; }
    int          SelAllLockedVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1316, FetchRel, pos); return ret; }
    int          SelAllNotDone(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1039, FetchRel, pos); return ret; }
    int          SelAllNotDoneVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1317, FetchRel, pos); return ret; }
    int          SelCallbackFuture(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1036, FetchRel, pos); return ret; }
    int          SelCallbackFutureVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1318, FetchRel, pos); return ret; }
    int          SelCallbackOpen(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1033, FetchRel, pos); return ret; }
    int          SelCallbackOpenVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1319, FetchRel, pos); return ret; }
    int          SelCallbackWished(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1035, FetchRel, pos); return ret; }
    int          SelCallbackWishedVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1320, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKTODO() {
        ::buf_default((void *)&s, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKTODO() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKTODO_BES, CALLBACKTODO_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKTODO_BES, (int)CALLBACKTODO_ANZ, error_msg);
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
        if ( fkt_nr == 1041 ) return CursorServerCall(1041, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1316 ) return CursorServerCall(1316, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1039 ) return CursorServerCall(1039, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1317 ) return CursorServerCall(1317, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1036 ) return CursorServerCall(1036, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1318 ) return CursorServerCall(1318, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1033 ) return CursorServerCall(1033, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1319 ) return CursorServerCall(1319, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1035 ) return CursorServerCall(1035, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1320 ) return CursorServerCall(1320, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKTODO & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CALLBACKPARTNER);
        ppGStripLast(d.TITEL);
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.KRITIKTEXT);
        ppGStripLast(d.ORT);
        ppGStripLast(d.KZKDKLASSE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKTODO_BES, (int)CALLBACKTODO_ANZ, error_msg);
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
        CCALLBACKTODO c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKTODO_BES, (int)CALLBACKTODO_ANZ, error_msg);
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

class CCALLBACKTODONEW : public ppDadeVirtual {
public:
    callbacktodonewS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbacktodonewS> lst; // class list

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
                     vector< callbacktodonewS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbacktodonewS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbacktodonewS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbacktodonewS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbacktodonewS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCallbackno() const { return s.CALLBACKNO; }
    long         GetIdfnr() const { return s.IDFNR; }
    long         GetRegionnr() const { return s.REGIONNR; }
    const char*  GetDivisionname(ppString & t) const { t = s.DIVISIONNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetKritiknr() const { return s.KRITIKNR; }
    long         GetPosnr() const { return s.POSNR; }
    short        GetCallbackdivisionno() const { return s.CALLBACKDIVISIONNO; }
    const char*  GetTitel(ppString & t) const { t = s.TITEL; t.erasespace(ppString::END); return t.c_str(); }
    char         GetKzposart() const { return s.KZPOSART[0]; }
    long         GetCallbacktimewished() const { return s.CALLBACKTIMEWISHED; }
    short        GetVertriebszentrumnr() const { return s.VERTRIEBSZENTRUMNR; }
    long         GetCallbackdatewished() const { return s.CALLBACKDATEWISHED; }
    char         GetState() const { return s.STATE[0]; }
    short        GetKritiklevel() const { return s.KRITIKLEVEL; }
    const char*  GetNameapo(ppString & t) const { t = s.NAMEAPO; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKritiktext(ppString & t) const { t = s.KRITIKTEXT; t.erasespace(ppString::END); return t.c_str(); }
    short        GetShiftcount() const { return s.SHIFTCOUNT; }
    const char*  GetOrt(ppString & t) const { t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetKzkdklasse(ppString & t) const { t = s.KZKDKLASSE; t.erasespace(ppString::END); return t.c_str(); }
    long         GetUid() const { return s.UID; }
    short        GetFilialnr() const { return s.FILIALNR; }
    const char*  GetReference(ppString& t) const { t = s.REFERENCE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetStatus(ppString& t) const { t = s.STATUS; t.erasespace(ppString::END); return t.c_str(); }

    const callbacktodonewS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCallbackno(long t) { s.CALLBACKNO = t; }
    void         SetIdfnr(long t) { s.IDFNR = t; }
    void         SetRegionnr(long t) { s.REGIONNR = t; }
    void         SetDivisionname(const ppString & t) { ppGStrCopy(s.DIVISIONNAME, t.c_str(), L_CALLBACKTODONEW_DIVISIONNAME); }
    void         SetKritiknr(long t) { s.KRITIKNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetCallbackdivisionno(short t) { s.CALLBACKDIVISIONNO = t; }
    void         SetTitel(const ppString & t) { ppGStrCopy(s.TITEL, t.c_str(), L_CALLBACKTODONEW_TITEL); }
    void         SetKzposart(char t) { s.KZPOSART[0] = t; s.KZPOSART[1] = '\0';}
    void         SetCallbacktimewished(long t) { s.CALLBACKTIMEWISHED = t; }
    void         SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
    void         SetCallbackdatewished(long t) { s.CALLBACKDATEWISHED = t; }
    void         SetState(char t) { s.STATE[0] = t; s.STATE[1] = '\0';}
    void         SetKritiklevel(short t) { s.KRITIKLEVEL = t; }
    void         SetNameapo(const ppString & t) { ppGStrCopy(s.NAMEAPO, t.c_str(), L_CALLBACKTODONEW_NAMEAPO); }
    void         SetKritiktext(const ppString & t) { ppGStrCopy(s.KRITIKTEXT, t.c_str(), L_CALLBACKTODONEW_KRITIKTEXT); }
    void         SetShiftcount(short t) { s.SHIFTCOUNT = t; }
    void         SetOrt(const ppString & t) { ppGStrCopy(s.ORT, t.c_str(), L_CALLBACKTODONEW_ORT); }
    void         SetKzkdklasse(const ppString & t) { ppGStrCopy(s.KZKDKLASSE, t.c_str(), L_CALLBACKTODONEW_KZKDKLASSE); }
    void         SetUid(long t) { s.UID = t; }
    void         SetFilialnr(short t) { s.FILIALNR = t; }
    void         SetReference(const ppString & t) { ppGStrCopy(s.REFERENCE, t.c_str(), L_CALLBACKTODONEW_REFERENCE); }
    void         SetStatus(const ppString& t) { ppGStrCopy(s.STATUS, t.c_str(), L_CALLBACKTODONEW_STATUS); }

    void         SetStruct(const callbacktodonewS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelAllLocked(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1654, FetchRel, pos); return ret; }
    int          SelAllLockedVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1655, FetchRel, pos); return ret; }
    int          SelAllNotDone(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1656, FetchRel, pos); return ret; }
    int          SelAllNotDoneVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1657, FetchRel, pos); return ret; }
    int          SelCallbackFuture(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1658, FetchRel, pos); return ret; }
    int          SelCallbackFutureVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1659, FetchRel, pos); return ret; }
    int          SelCallbackOpen(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1660, FetchRel, pos); return ret; }
    int          SelCallbackOpenVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1661, FetchRel, pos); return ret; }
    int          SelCallbackWished(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1662, FetchRel, pos); return ret; }
    int          SelCallbackWishedVz(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1663, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKTODONEW() {
        ::buf_default((void *)&s, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKTODONEW() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKTODONEW_BES, CALLBACKTODONEW_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKTODONEW_BES, (int)CALLBACKTODONEW_ANZ, error_msg);
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
        if ( fkt_nr == 1654 ) return CursorServerCall(1654, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1655 ) return CursorServerCall(1655, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1656 ) return CursorServerCall(1656, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1657 ) return CursorServerCall(1657, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1658 ) return CursorServerCall(1658, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1659 ) return CursorServerCall(1659, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1660 ) return CursorServerCall(1660, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1661 ) return CursorServerCall(1661, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1662 ) return CursorServerCall(1662, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1663 ) return CursorServerCall(1663, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKTODONEW & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.DIVISIONNAME);
        ppGStripLast(d.TITEL);
        ppGStripLast(d.NAMEAPO);
        ppGStripLast(d.KRITIKTEXT);
        ppGStripLast(d.ORT);
        ppGStripLast(d.KZKDKLASSE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKTODONEW_BES, (int)CALLBACKTODONEW_ANZ, error_msg);
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
        CCALLBACKTODONEW c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKTODONEW_BES, (int)CALLBACKTODONEW_ANZ, error_msg);
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

class CCALLBACKSTATUS : public ppDadeVirtual {
public:
    callbackstatusS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbackstatusS> lst; // class list

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
                     vector< callbackstatusS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbackstatusS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbackstatusS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbackstatusS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbackstatusS>::iterator
                 endList  () { return lst.end  (); }

    short        GetStatusID() const { return s.STATUSID; }
    const char*  GetStatusName(ppString& t) const { t = s.STATUSNAME; t.erasespace(ppString::END); return t.c_str(); }
    short GetStatusTag() const { return s.STATUSTAG; }

    const callbackstatusS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetStatusID(short t) { s.STATUSID = t; }
    void         SetStatusName(const ppString& t) { ppGStrCopy(s.STATUSNAME, t.c_str(), L_CALLBACSTATUS_STATUSNAME); }
    void         SetStatusTag(short t) { s.STATUSTAG = t; }

    void         SetStruct(const callbackstatusS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          SelectAll(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1670, FetchRel, pos); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKSTATUS() {
        ::buf_default((void *)&s, CALLBACKSTATUS_BES, CALLBACKSTATUS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKSTATUS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKSTATUS_BES, CALLBACKSTATUS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKSTATUS_BES, (int)CALLBACKSTATUS_ANZ, error_msg);
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
        if ( fkt_nr == 1719 ) return CursorServerCall(1670, (int)s.FETCH_REL, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKSTATUS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKSTATUS_BES, (int)CALLBACKSTATUS_ANZ, error_msg);
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
        CCALLBACKSTATUS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKSTATUS_BES, (int)CALLBACKSTATUS_ANZ, error_msg);
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

class CCALLBACKITEMS : public ppDadeVirtual {
public:
    callbackitemsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<callbackitemsS> lst; // class list

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
                     vector< callbackitemsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     callbackitemsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< callbackitemsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<callbackitemsS>::iterator
                 beginList() { return lst.begin(); }
    vector<callbackitemsS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCallbackno() const { return s.CALLBACKNO; }
    long         GetCallbackpartno() const { return s.CALLBACKPARTNO; }
    long         GetKritiknr() const { return s.KRITIKNR; }
    long         GetPosnr() const { return s.POSNR; }
    char         GetKzposart() const { return s.KZPOSART[0]; }
    long         GetPosnr_done() const { return s.POSNR_DONE; }
    long         GetCallbacktimewished() const { return s.CALLBACKTIMEWISHED; }
    long         GetCallbackdatewished() const { return s.CALLBACKDATEWISHED; }
    short        GetCallbacktime() const { return s.CALLBACKTIME; }
    char         GetState() const { return s.STATE[0]; }
    char         GetLockkz() const { return s.LOCKKZ[0]; }
    short        GetShiftcount() const { return s.SHIFTCOUNT; }
    short        GetReasonno() const { return s.REASONNO; }
    const char* GetReference(ppString& t) const { t = s.REFERENCE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetStatusId() const { return s.STATUSID; }

    const callbackitemsS &
                 GetStruct() const { return s; }
    long         GetFetch_rel() const { return s.FETCH_REL; }

    void         SetCallbackno(long t) { s.CALLBACKNO = t; }
    void         SetCallbackpartno(long t) { s.CALLBACKPARTNO = t; }
    void         SetKritiknr(long t) { s.KRITIKNR = t; }
    void         SetPosnr(long t) { s.POSNR = t; }
    void         SetKzposart(char t) { s.KZPOSART[0] = t; s.KZPOSART[1] = '\0';}
    void         SetPosnr_done(long t) { s.POSNR_DONE = t; }
    void         SetCallbacktimewished(long t) { s.CALLBACKTIMEWISHED = t; }
    void         SetCallbackdatewished(long t) { s.CALLBACKDATEWISHED = t; }
    void         SetCallbacktime(short t) { s.CALLBACKTIME = t; }
    void         SetState(char t) { s.STATE[0] = t; s.STATE[1] = '\0';}
    void         SetLockkz(char t) { s.LOCKKZ[0] = t; s.LOCKKZ[1] = '\0';}
    void         SetShiftcount(short t) { s.SHIFTCOUNT = t; }
    void         SetReasonno(short t) { s.REASONNO = t; }
    void         SetReference(const ppString& t) { ppGStrCopy(s.REFERENCE, t.c_str(), L_CALLBACKITEMS_REFERENCE); }
    void         SetStatusId(short t) { s.STATUSID = t; }

    void         SetStruct(const callbackitemsS & t) { s = t; }
    void         SetFetch_rel(const long t) { s.FETCH_REL = t; }

    int          InsertWithNewNo(int pos = 0) { int ret = UniqueServerCall(1030, pos); Strip(s); return ret; }
    int          SelCallbackWish(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1031, FetchRel, pos); return ret; }
    int          SelNo(int pos = 0) { int ret = UniqueServerCall(1034, pos); Strip(s); return ret; }
    int          SelNotDone(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1037, FetchRel, pos); return ret; }
    int          Sellocked(int FetchRel = 1, int pos = 0) { int ret = CursorServerCall(1040, FetchRel, pos); return ret; }
    int          UpdateItem(int pos = 0) { int ret = UniqueServerCall(1029, pos); Strip(s); return ret; }

    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCALLBACKITEMS() {
        ::buf_default((void *)&s, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCALLBACKITEMS() {
        CloseCursor();
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CALLBACKITEMS_BES, CALLBACKITEMS_ANZ);
    }

    // close db cursor
    int CloseCursor(int pos = 0) {
        if ( !bOpenCursor )
            return 0;
        s.FETCH_REL = 0;
    #ifndef __DADE_LOAD__
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKITEMS_BES, (int)CALLBACKITEMS_ANZ, error_msg);
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
        if ( fkt_nr == 1030 ) return UniqueServerCall(1030, pos);
        if ( fkt_nr == 1031 ) return CursorServerCall(1031, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1034 ) return UniqueServerCall(1034, pos);
        if ( fkt_nr == 1037 ) return CursorServerCall(1037, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1040 ) return CursorServerCall(1040, (int)s.FETCH_REL, pos);
        if ( fkt_nr == 1029 ) return UniqueServerCall(1029, pos);
        FehlerBehandlung(-1, "False function number!");
        return -1;
     }

private:
    void Strip(N_CALLBACKITEMS & d) {
        d = d;
    #ifdef WIN32
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CALLBACKITEMS_BES, (int)CALLBACKITEMS_ANZ, error_msg);
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
        CCALLBACKITEMS c;
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
        rc = ::ServerNr(pos, FncNumber, (void *)&s, CALLBACKITEMS_BES, (int)CALLBACKITEMS_ANZ, error_msg);
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
