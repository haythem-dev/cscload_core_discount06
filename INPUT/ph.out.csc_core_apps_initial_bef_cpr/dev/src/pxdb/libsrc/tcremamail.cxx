/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

    Embedded SQL for C application

    Database functions

    FUNCTIONS:

        pxCremaMailStartBrowse  declare and open Cursor
        pxCremaMailGetNext      get next record
        pxCremaMailEndBrowse    close cursor
        pxCremaMailRead         get one record
        pxCremaMailReadLock     get one record with lock
        pxCremaMailInsert       Insert record
        pxCremaMailUpdate       Update record
        pxCremaMailDelete       Delete record


REVISION HISTORY

18 Mar 2013 V1.00 REV 00 written by Martin Zoephel

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* tCREMAMAIL */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tcremamail.h"
#include <pxenv.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCremaMailStartBrowse                                 */
/*                                                                   */
/*      Declare and Open a Cursor   (general)                        */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCremaMailStartBrowse
(
     struct tCREMAMAIL* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CREMAMAIL * recordp;
    char sqlStmt[2000];
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_SMTPUSERGROUPS*10+F_StartBrowse;
    recordp = (struct C_CREMAMAIL *) record;

    if (!(sizeof(struct C_CREMAMAIL) == sizeof(struct tCREMAMAIL)))
       return cDBXR_DEFINITION;

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    switch (browseid)
    {
       case cCRSDEBTMAIL_GETDATAFORPERCENTAGE:
       {
    	   EXEC SQL DECLARE C_GETDATAFORPERCENTAGE CURSOR FOR
    	   		Select sug.ID, sug.SMTPID, sug.SENTFROMADDRESS, sug.URL, s.PORT, s.SERVER, sug.crematypeid
    	   		from smtpusergroups sug
    	   		inner join smtp s on sug.smtpid = s.id
    	   		inner join crematype ct on ct.id = sug.crematypeid
    	   		inner join debtlevelformail dlfm on dlfm.id = ct.typeid and ct.type = 0
    	   		where dlfm.dlpercentage = ( Select max(dlpercentage) from DebtLevelForMail where dlpercentage <= :recordp->DLPERCENTAGE)
    	   		and sug.branchno = :recordp->BRANCHNO
#ifndef pxDATABASE_INFORMIX
   FOR BROWSE;
#else
	;
#endif
          EXEC SQL OPEN C_GETDATAFORPERCENTAGE;
          break;
       }
       case cCRSDEBTMAIL_CHECKWASSEND_ORDER:
       {
    	   EXEC SQL DECLARE C_CHECKWASSEND_ORDER CURSOR FOR
    	   		 SELECT wassend
    	   		 FROM debtmailsend dms
    	   		 inner join smtpusergroups sug on dms.smtpusergroupid = sug.id
    	   		 inner join crematype ct on ct.id = sug.crematypeid
    	   		 inner join debtlevelformail dlfm on dlfm.id = ct.typeid and ct.type = 0
    	   		 WHERE kdauftragnr = :recordp->KDAUFTRAGNR and dms.branchno = :recordp->BRANCHNO
    	   		 //AND senddate = :recordp->SENDDATE
    	   		 and  dlfm.dlpercentage = (select max(dlpercentage) from debtlevelformail where dlpercentage <= :recordp->DLPERCENTAGE and leveltype = :recordp->LEVELTYPE)
#ifndef pxDATABASE_INFORMIX
 FOR BROWSE;
#else
	;
#endif
    	   EXEC SQL OPEN C_CHECKWASSEND_ORDER;
           break;
       }
       case cCRSDEBTMAIL_GETTYPEFORPERCENTAGE:
    	  strcpy(sqlStmt,"SELECT leveltype ");
		  strcat(sqlStmt,"FROM DebtLevelForMail ");
		  strcat(sqlStmt,"WHERE dlpercentage = (select max(dlpercentage) from debtlevelformail where dlpercentage <= ?) ");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_GETTYPEFORPERCENTAGE CURSOR with hold for DynQuery;
	      EXEC SQL OPEN C_GETTYPEFORPERCENTAGE using :recordp->DLPERCENTAGE;
		  break;
       case cCRSDEBTMAIL_GETTYPEFORAMOUNT:
    	  strcpy(sqlStmt,"Select max(thresholdamount) as thresholdamount ");
		  strcat(sqlStmt,"from amountformail ");
		  strcat(sqlStmt,"where thresholdamount <= ? ");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_GETTYPEFORAMOUNT CURSOR with hold for DynQuery;
		  EXEC SQL OPEN C_GETTYPEFORAMOUNT using :recordp->THRESHOLDAMOUNT;
		  break;
       case cCRSDEBTMAIL_GETMAILADDRESSES:
    	  strcpy(sqlStmt,"SELECT sug.sentfromaddress, adr.senttoaddress, sem.emailtype ");
		  strcat(sqlStmt,"FROM smtpsendtoemailaddresses adr ");
		  strcat(sqlStmt,"inner join smtpemailtype sem on sem.id = adr.smtpemailtypeid ");
		  strcat(sqlStmt,"inner join smtpusergroups sug on sug.id=sem.smtpusergroupid ");
		  strcat(sqlStmt,"WHERE sug.id = ? AND sem.emailtype = ? ");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_GETMAILADRESSES CURSOR with hold for DynQuery;
		  EXEC SQL OPEN C_GETMAILADRESSES using :recordp->SMTPUSERGROUPID,:recordp->EMAILTYPE;
		  break;
       case cCRSDEBTMAIL_GETDATAFORAMOUNT:
    	  strcpy(sqlStmt,"Select sug.ID, sug.SMTPID, sug.SENTFROMADDRESS, sug.URL, s.PORT, s.SERVER, sug.crematypeid, afm.thresholdamount ");
		  strcat(sqlStmt,"from smtpusergroups sug ");
		  strcat(sqlStmt,"inner join smtp s on sug.smtpid = s.id ");
		  strcat(sqlStmt,"inner join crematype ct on ct.id = sug.crematypeid ");
		  strcat(sqlStmt,"inner join amountformail afm on afm.id = ct.typeid and ct.type = 1 ");
		  strcat(sqlStmt,"where afm.thresholdamount = ( ");
			  strcat(sqlStmt,"Select max(thresholdamount) ");
			  strcat(sqlStmt,"from amountformail ");
			  strcat(sqlStmt,"where thresholdamount <= ? ) ");
		  strcat(sqlStmt," and sug.branchno=? ");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_GETDATAFORAMOUNT CURSOR with hold for DynQuery;
		  EXEC SQL OPEN C_GETDATAFORAMOUNT using :recordp->WERTAUFTRAG,:recordp->BRANCHNO;
    	  break;
       case cCRSDEBTMAIL_GETAPPROVALSNEEDED:
    	  EXEC SQL DECLARE C_APPROVALS_NEEDED CURSOR FOR
    	   		 SELECT ApprovalPersonsNeeded
    	   		 FROM debtmailsend dms
    	   		 inner join smtpusergroups sug on dms.smtpusergroupid = sug.id
    	   		 inner join crematype ct on ct.id = sug.crematypeid
    	   		 inner join debtlevelformail dlfm on dlfm.id = ct.typeid and ct.type = 0
    	   		 WHERE dms.kdauftragnr = :recordp->KDAUFTRAGNR and dms.branchno = :recordp->BRANCHNO;
		  EXEC SQL OPEN C_APPROVALS_NEEDED;
    	  break;
       case cCRSDEBTMAIL_GETGVLMAIL:
    	  strcpy(sqlStmt,"SELECT sem.emailtype, gm.sendgvlmail ");
		  strcat(sqlStmt,"FROM smtpemailtype sem ");
		  strcat(sqlStmt,"inner join smtpgvlmail gm on gm.smtpemailtypeid = sem.id ");
		  strcat(sqlStmt,"inner join smtpusergroups sug on sug.id=sem.smtpusergroupid ");
		  strcat(sqlStmt,"WHERE sug.id = ? AND sem.emailtype = ? ");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_GETGVLMAIL CURSOR with hold for DynQuery;
		  EXEC SQL OPEN C_GETGVLMAIL using :recordp->SMTPUSERGROUPID, :recordp->EMAILTYPE;
    	  break;
       case cCRSDEBTMAIL_CHECKWASSEND_AMOUNT_PARTNER:
    	  strcpy(sqlStmt,"SELECT wassend ");
    	  strcat(sqlStmt,"FROM debtmailsend dms ");
		  strcat(sqlStmt,"inner join smtpusergroups sug on dms.smtpusergroupid = sug.id ");
		  strcat(sqlStmt,"inner join crematype ct on ct.id = sug.crematypeid ");
		  strcat(sqlStmt,"inner join amountformail afm on afm.id = ct.typeid and ct.type = 1 ");
		  strcat(sqlStmt,"WHERE dms.branchno = ? ");
		  strcat(sqlStmt,"and afm.thresholdamount = ");
		  strcat(sqlStmt,"(Select max(thresholdamount) from amountformail where thresholdamount <= ?) ");
		  strcat(sqlStmt,"and dms.partnerno = ? ");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_CHECKWASSEND_AMOUNT_PARTNERNR CURSOR with hold for DynQuery;
		  EXEC SQL OPEN C_CHECKWASSEND_AMOUNT_PARTNERNR using :recordp->BRANCHNO, :recordp->WERTAUFTRAG, :recordp->PARTNERNO;
		  break;
       case cCRSDEBTMAIL_CHECKWASSEND_WARNING_PARTNER:
    	  strcpy(sqlStmt,"SELECT wassend ");
    	  strcat(sqlStmt,"FROM debtmailsend dms ");
		  strcat(sqlStmt,"inner join smtpusergroups sug on sug.id = dms.smtpusergroupid ");
		  strcat(sqlStmt,"inner join crematype ct on ct.id = sug.crematypeid ");
		  strcat(sqlStmt,"inner join debtlevelformail dlfm on dlfm.id = ct.typeid and ct.type = 0 ");
		  strcat(sqlStmt,"WHERE dms.branchno = ? ");
		  strcat(sqlStmt,"and dlfm.dlpercentage = ");
		  strcat(sqlStmt,"(select max(dlpercentage) from debtlevelformail where dlpercentage <= ? and leveltype = ?) ");
		  strcat(sqlStmt,"and dms.partnerno = ? ");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_CHECKWASSEND_WARNING_PARTNERNR CURSOR with hold for DynQuery;
    	  EXEC SQL OPEN C_CHECKWASSEND_WARNING_PARTNERNR using :recordp->BRANCHNO, :recordp->DLPERCENTAGE, :recordp->LEVELTYPE, :recordp->PARTNERNO;
    	  break;

	   case cCRSDEBTMAIL_GET_DEFERRED_ORDERS:

		   EXEC SQL DECLARE C_GET_DEFERRED_ORDERS CURSOR FOR
		     	  	  SELECT DISTINCT dms.branchno, dms.kdauftragnr, dms.senddate, dms.sendtime, dlfm.approvalpersonsneeded
		     		  FROM DebtmailSend dms
		     		  INNER JOIN smtpusergroups sug on sug.id = dms.smtpusergroupid
		     		  INNER JOIN crematype ct on ct.id = sug.crematypeid
		     		  INNER JOIN debtlevelformail dlfm on dlfm.id = ct.typeid and ct.type = 0
		   			  INNER JOIN kdauftrag a on dms.kdauftragnr = a.kdauftragnr
		     		  WHERE dlfm.leveltype > 1 and a.kdauftragstat like '0001%' and a.zugrund like '1%' and dms.branchno = :recordp->BRANCHNO;

		   EXEC SQL OPEN C_GET_DEFERRED_ORDERS;
    	   break;

       case cCRSDEBTMAIL_GET_WARNING_PARTNER_VZS:
    	  strcpy(sqlStmt,"select distinct (k.filialnr) ");
		  strcat(sqlStmt,"from ");
		  strcat(sqlStmt,"kunde k ");
		  strcat(sqlStmt,"inner join kundeschalter ks on ks.idfnr = k.idfnr and ks.vertriebszentrumnr = k.filialnr ");
		  strcat(sqlStmt,"where k.partnernr=? and ks.skdkundeaegesperrt='0'");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_GET_WARNING_PARTNER_VZS CURSOR with hold for DynQuery;
    	  EXEC SQL OPEN C_GET_WARNING_PARTNER_VZS using :recordp->PARTNERNO;
		  break;
       case cCRSDEBTMAIL_GETDATAFORLEVEL:
    	  strcpy(sqlStmt,"Select sug.ID, sug.SMTPID, sug.SENTFROMADDRESS, sug.URL, s.PORT, s.SERVER, sug.crematypeid ");
		  strcat(sqlStmt,"from smtpusergroups sug ");
		  strcat(sqlStmt,"inner join smtp s on sug.smtpid = s.id ");
		  strcat(sqlStmt,"inner join crematype ct on ct.id = sug.crematypeid ");
		  strcat(sqlStmt,"inner join debtlevelformail dlfm on dlfm.id = ct.typeid and ct.type = 0 ");
		  strcat(sqlStmt,"where dlfm.leveltype <= ? and sug.branchno = ?");

		  EXEC SQL PREPARE DynQuery FROM :sqlStmt;
		  EXEC SQL declare C_GETDATAFORLEVEL CURSOR with hold for DynQuery;
    	  EXEC SQL OPEN C_GETDATAFORLEVEL using :recordp->LEVELTYPE, :recordp->BRANCHNO;
    	  break;

	   case cCRSDEBTMAIL_GETMAILDATAFORUUID:
    	  EXEC SQL DECLARE C_GETMAILDATAFORUUID CURSOR FOR
		   	   select sug.sentfromaddress, adr.senttoaddress, sem.emailtype, serv.server, serv.port
			   from debtmailsend dms
			   inner join smtpusergroups sug on sug.id=dms.smtpusergroupid
			   inner join smtpemailtype sem on sem.smtpusergroupid = sug.id
			   inner join smtpsendtoemailaddresses adr on sem.id = adr.smtpemailtypeid
			   inner join smtp serv on serv.id = sug.smtpid
			   where guid = :recordp->GUID group by adr.senttoaddress, sug.sentfromaddress, sem.emailtype, serv.server, serv.port;
	      EXEC SQL OPEN C_GETMAILDATAFORUUID;
	      break;

       case cCRSDEBTMAIL_GETLANGUAGEFORPARTNER:
           EXEC SQL DECLARE C_GETLANGUAGEFORPARTNER CURSOR FOR
			   SELECT FIRST 1 k.kzsprache, '1'
					FROM kunde k
					WHERE k.mastercstno = k.idfnr
					AND k.originalfilialnr = 0 
					AND k.partnernr =   :recordp->PARTNERNO
				 UNION
				SELECT k.kzsprache, '2'
					 FROM kunde k
					 WHERE k.partnernr =   :recordp->PARTNERNO
					 ORDER BY 2;
      	   EXEC SQL OPEN C_GETLANGUAGEFORPARTNER;
      	   break;

	  case cCRSDEBTMAIL_GETGUIDFORORDERNO:
           EXEC SQL DECLARE C_GETGUIDFORORDERNO CURSOR FOR
			   SELECT FIRST 1 GUID 
					FROM debtmailsend dms
					WHERE dms.kdauftragnr = :recordp->KDAUFTRAGNR;
      	   EXEC SQL OPEN C_GETGUIDFORORDERNO;
      	   break;

	  case cCRSDEBTMAIL_GETSMTPSERVER:
		  EXEC SQL DECLARE C_GETSMTPSERVER CURSOR FOR
			  SELECT FIRST 1 SERVER, PORT FROM SMTP;
		  EXEC SQL OPEN C_GETSMTPSERVER;
		  break;
	  default:
          EXEC SQL OPEN C_GETDATAFORPERCENTAGE;
          break;
    }
    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCremaMailGetNext                                     */
/*                                                                   */
/*      Fetch for a Cursor   (general)                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCremaMailGetNext
(
    struct tCREMAMAIL* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CREMAMAIL * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_SMTPUSERGROUPS*10+F_GetNext;
    recordp = (struct C_CREMAMAIL *) record;

    switch (browseid)
    {
    // into CREMAMAIL_ZEIGER(recordp);
       case cCRSDEBTMAIL_GETDATAFORPERCENTAGE:
          EXEC SQL FETCH C_GETDATAFORPERCENTAGE
          into :recordp->SMTPUSERGROUPID, :recordp->SMTPID, :recordp->SENTFROMADDRESS,
          :recordp->URL, :recordp->PORT, :recordp->SERVER, :recordp->CREMATYPEID;
          break;
       case cCRSDEBTMAIL_CHECKWASSEND_ORDER:
    	   EXEC SQL FETCH C_CHECKWASSEND_ORDER
    	   into :recordp->WASSEND;
		   break;
       case cCRSDEBTMAIL_GETTYPEFORPERCENTAGE:
		   EXEC SQL FETCH C_GETTYPEFORPERCENTAGE
		   into :recordp->LEVELTYPE;
		   break;
       case cCRSDEBTMAIL_GETTYPEFORAMOUNT:
		   EXEC SQL FETCH C_GETTYPEFORAMOUNT
		   into :recordp->THRESHOLDAMOUNT;
		   break;
       case cCRSDEBTMAIL_GETMAILADDRESSES:
    	  EXEC SQL FETCH C_GETMAILADRESSES
		  into :recordp->SENTFROMADDRESS, :recordp->SENTTOADDRESS, :recordp->EMAILTYPE;
		  break;
       case cCRSDEBTMAIL_GETDATAFORAMOUNT:
           EXEC SQL FETCH C_GETDATAFORAMOUNT
           into :recordp->SMTPUSERGROUPID, :recordp->SMTPID, :recordp->SENTFROMADDRESS,
           :recordp->URL, :recordp->PORT, :recordp->SERVER, :recordp->CREMATYPEID, :recordp->THRESHOLDAMOUNT;
    	   break;
       case cCRSDEBTMAIL_GETAPPROVALSNEEDED:
		   EXEC SQL FETCH C_APPROVALS_NEEDED
		   into :recordp->APPROVALPERSONSNEEDED;
    	   break;
       case cCRSDEBTMAIL_GETGVLMAIL:
		   EXEC SQL FETCH C_GETGVLMAIL
		   into :recordp->EMAILTYPE, :recordp->SENDGVLMAIL;
    	   break;
       case cCRSDEBTMAIL_CHECKWASSEND_AMOUNT_PARTNER:
		   EXEC SQL FETCH C_CHECKWASSEND_AMOUNT_PARTNERNR
    	   into :recordp->WASSEND;
		   break;
       case cCRSDEBTMAIL_CHECKWASSEND_WARNING_PARTNER:
		   EXEC SQL FETCH C_CHECKWASSEND_WARNING_PARTNERNR
    	   into :recordp->WASSEND;
    	   break;
	   case cCRSDEBTMAIL_GET_DEFERRED_ORDERS:
		   EXEC SQL FETCH C_GET_DEFERRED_ORDERS
		   INTO
		    	:recordp->BRANCHNO,
				:recordp->KDAUFTRAGNR,
				:recordp->SENDDATE,
				:recordp->SENDTIME,
				:recordp->APPROVALPERSONSNEEDED;
    	   break;
       case cCRSDEBTMAIL_GET_WARNING_PARTNER_VZS:
		   EXEC SQL FETCH C_GET_WARNING_PARTNER_VZS
    	   into :recordp->BRANCHNO;
		   break;
       case cCRSDEBTMAIL_GETDATAFORLEVEL:
           EXEC SQL FETCH C_GETDATAFORLEVEL
           into :recordp->SMTPUSERGROUPID, :recordp->SMTPID, :recordp->SENTFROMADDRESS,
           :recordp->URL, :recordp->PORT, :recordp->SERVER, :recordp->CREMATYPEID;
    	   break;
	   case cCRSDEBTMAIL_GETMAILDATAFORUUID:
    	   EXEC SQL FETCH C_GETMAILDATAFORUUID
		   into :recordp->SENTFROMADDRESS, :recordp->SENTTOADDRESS, :recordp->EMAILTYPE, :recordp->SERVER, :recordp->PORT;
    	   break;
       case cCRSDEBTMAIL_GETLANGUAGEFORPARTNER:
    	   EXEC SQL FETCH C_GETLANGUAGEFORPARTNER
		   into :recordp->GUID, :recordp->WASSEND;
    	   break;
	   case cCRSDEBTMAIL_GETGUIDFORORDERNO:
    	   EXEC SQL FETCH C_GETGUIDFORORDERNO
		   into :recordp->GUID;
    	   break;
	   case cCRSDEBTMAIL_GETSMTPSERVER:
		   EXEC SQL FETCH C_GETSMTPSERVER
		   INTO :recordp->SERVER, :recordp->PORT;
		   break;
       default:
          EXEC SQL FETCH C_GETDATAFORPERCENTAGE
          into CREMAMAIL_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCremaMailEndBrowse                                   */
/*                                                                   */
/*      Close a Cursor   (general)                                   */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCremaMailEndBrowse
(
    int browseid
)
{
    functionnr = F_SMTPUSERGROUPS*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRSDEBTMAIL_GETDATAFORPERCENTAGE:
          EXEC SQL CLOSE C_GETDATAFORPERCENTAGE;
          break;
       case cCRSDEBTMAIL_CHECKWASSEND_ORDER:
    	   EXEC SQL CLOSE C_CHECKWASSEND_ORDER;
		   break;
       case cCRSDEBTMAIL_GETTYPEFORPERCENTAGE:
		   EXEC SQL CLOSE C_GETTYPEFORPERCENTAGE;
		   break;
       case cCRSDEBTMAIL_GETTYPEFORAMOUNT:
		   EXEC SQL CLOSE C_GETTYPEFORAMOUNT;
		   break;
       case cCRSDEBTMAIL_GETMAILADDRESSES:
		   EXEC SQL CLOSE C_GETMAILADRESSES;
		  break;
       case cCRSDEBTMAIL_GETDATAFORAMOUNT:
		   EXEC SQL CLOSE C_GETDATAFORAMOUNT;
		   break;
       case cCRSDEBTMAIL_GETAPPROVALSNEEDED:
		   EXEC SQL CLOSE C_APPROVALS_NEEDED;
    	   break;
       case cCRSDEBTMAIL_GETGVLMAIL:
		   EXEC SQL CLOSE C_GETGVLMAIL;
    	   break;
       case cCRSDEBTMAIL_CHECKWASSEND_AMOUNT_PARTNER:
		   EXEC SQL CLOSE C_CHECKWASSEND_AMOUNT_PARTNERNR;
		   break;
       case cCRSDEBTMAIL_CHECKWASSEND_WARNING_PARTNER:
		   EXEC SQL CLOSE C_CHECKWASSEND_WARNING_PARTNERNR;
    	   break;
	   case cCRSDEBTMAIL_GET_DEFERRED_ORDERS:
		   EXEC SQL CLOSE C_GET_DEFERRED_ORDERS;
    	   break;
       case cCRSDEBTMAIL_GET_WARNING_PARTNER_VZS:
		   EXEC SQL CLOSE C_GET_WARNING_PARTNER_VZS;
		   break;
       case cCRSDEBTMAIL_GETDATAFORLEVEL:
           EXEC SQL CLOSE C_GETDATAFORLEVEL;
    	   break;
	   case cCRSDEBTMAIL_GETMAILDATAFORUUID:
		   EXEC SQL CLOSE C_GETMAILDATAFORUUID;
		   break;
       case cCRSDEBTMAIL_GETLANGUAGEFORPARTNER:
		   EXEC SQL CLOSE C_GETLANGUAGEFORPARTNER;
		   break;
	   case cCRSDEBTMAIL_GETGUIDFORORDERNO:
    	   EXEC SQL CLOSE C_GETGUIDFORORDERNO;
		   break;
	   case cCRSDEBTMAIL_GETSMTPSERVER:
		   EXEC SQL CLOSE C_GETSMTPSERVER;
		   break;
       default:
          EXEC SQL CLOSE C_GETDATAFORPERCENTAGE;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCremaMailInsert                                      */
/*                                                                   */
/*      Insert  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCremaMailInsert
(
    struct tCREMAMAIL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CREMAMAIL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SMTPUSERGROUPS*10+F_Insert;
    recordp = (struct C_CREMAMAIL *) record;

    EXEC SQL insert into DebtMailSend(smtpusergroupid,wassend,senddate,kdauftragnr,guid,branchno,crematypeid,sendtime,partnerno,emailtype)
    VALUES ( :recordp->SMTPUSERGROUPID, :recordp->WASSEND, :recordp->SENDDATE, :recordp->KDAUFTRAGNR, :recordp->GUID,
    		:recordp->BRANCHNO, :recordp->CREMATYPEID, :recordp->SENDTIME, :recordp->PARTNERNO, :recordp->EMAILTYPE);

    if (SQLCODE == 0)
    {
       return 0;
    }
    if (SQLCODE == -2601)
    {
       return cDBXR_ISDUPLICATE;
    }
    return cDBXR_IOERROR;
}


/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCremaMailDelete                                      */
/*                                                                   */
/*      Delete  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCremaMailDelete
(
    struct tCREMAMAIL* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_CREMAMAIL * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_SMTPUSERGROUPS*10+F_Insert;
    recordp = (struct C_CREMAMAIL *) record;

    EXEC SQL DELETE FROM debtmailsend WHERE branchno = :recordp->BRANCHNO and kdauftragnr = :recordp->KDAUFTRAGNR;

    if (SQLCODE == 0)
    {
       return 0;
    }
    if (SQLCODE == 100)
       return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
