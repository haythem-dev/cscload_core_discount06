/******************************************************************************/
/*                                                                            */
/* header  : CremaEmailAddresses.cxx                                          */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:15 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "cremamailaddresses.h"

/* CremaEmailAddresses: Select ************************************************/



/* CremaEmailAddresses: Insert ************************************************/



/* CremaEmailAddresses: Update ************************************************/



/* CremaEmailAddresses: Select ************************************************/



/* CremaEmailAddresses: Other *************************************************/

/* CremaEmailAddresses::DeleteAddress *****************************************/

retClient Cremaemailaddresses_DeleteAddress(cremaemailaddressesS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "Cremaemailaddresses_DeleteAddress";

exec sql begin declare section;

cremaemailaddressesS *d;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
EXEC SQL BEGIN WORK;

  EXEC SQL
    Delete from smtpsendtoemailaddresses where id = :d->ID;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "delete address") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* CremaEmailAddresses::InsertAddress *****************************************/

retClient Cremaemailaddresses_InsertAddress(cremaemailaddressesS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "Cremaemailaddresses_InsertAddress";

exec sql begin declare section;

cremaemailaddressesS *d;

exec sql end declare section;

d = a;

if ( a->FETCH_REL == SET_OPEN )
{
  EXEC SQL BEGIN WORK;

  EXEC SQL
    INSERT INTO smtpsendtoemailaddresses(smtpemailtypeid, senttoaddress)
    VALUES(:d->SMTPEMAILTYPEID, :d->SENTTOADDRESS);

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "insert address") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* CremaEmailAddresses::InsertGVL *********************************************/

retClient Cremaemailaddresses_InsertGVL(cremaemailaddressesS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "CremaMailAddresses_InsertGVL";

exec sql begin declare section;

cremaemailaddressesS *d;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
	  EXEC SQL
		INSERT INTO smtpgvlmail(smtpemailtypeid,sendGVLMail)
		VALUES(:d->SMTPEMAILTYPEID,:d->SENDGVLMAIL);

	   //error checks
	   if ( ( rc=CheckSql( fun, stError, "%s", "insert GVL") ) != IS_OK )
	   {
		   return rc;
	   }
}
return rc;
}

/* CremaEmailAddresses::InsertType ********************************************/

retClient Cremaemailaddresses_InsertType(cremaemailaddressesS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "CremaMailAddresses_InsertType";

exec sql begin declare section;

cremaemailaddressesS *d;

int serialIDFromInsert;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
	  EXEC SQL
		INSERT INTO smtpemailtype(emailtype,smtpusergroupid)
		VALUES(:d->EMAILTYPE,:d->SMTPUSERGROUPID);

	   //error checks
	   if ( ( rc=CheckSql( fun, stError, "%s", "insert Type") ) != IS_OK )
	   {
		   return rc;
	   }
	  serialIDFromInsert = sqlca.sqlerrd[1];//only possible if no error occured
	  a->SMTPEMAILTYPEID = serialIDFromInsert;
}
return rc;
}

/* CremaEmailAddresses::SelEmailAddresses *************************************/

retClient Cremaemailaddresses_SelEmailAddresses(cremaemailaddressesS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

char cvSentToAddress[51];
int cvType;
int cvGVL;
int cvSMTPEmailTypeID;
int cvID;
char sqlStmt[500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "EmailAddresses_SelEmailAddresses";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise
  sprintf(sqlStmt,
"select nvl(sem.senttoaddress,''), nvl(sem.id,0), et.emailtype, nvl(gvl.sendGVLMail,-1), et.id from smtpEmailType et "
"left join smtpgvlmail gvl on gvl.smtpemailtypeid = et.id "
"left join smtpsendtoemailaddresses sem on et.id=sem.smtpemailtypeid where et.smtpusergroupid = %ld",
a->SMTPUSERGROUPID);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVSelEmails SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVSelEmails;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVSelEmails" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVSelEmails;
    return CheckSql( fun, stError, "%s", "close CVSelEmails" );
}

//fetch one data line from the db
EXEC SQL fetch NEXT CVSelEmails into :cvSentToAddress, :cvID, :cvType, :cvGVL, :cvSMTPEmailTypeID;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVSelTourForIDF" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
strcpy(a->SENTTOADDRESS, cvSentToAddress);
a->EMAILTYPE = cvType;
a->SENDGVLMAIL = cvGVL;
a->SMTPEMAILTYPEID = cvSMTPEmailTypeID;
a->ID = cvID;

return rc;
}

/* CremaEmailAddresses::SelEmailType ******************************************/

retClient Cremaemailaddresses_SelEmailType(cremaemailaddressesS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

int cvEmailType;
int cvGVL;
int cvID;
char sqlStmt[500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "EmailAddresses_SelEmailType";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise
  sprintf(sqlStmt,
"select nvl(gvl.sendgvlmail,-1), et.emailtype, et.id from smtpEmailType et "
"left join smtpgvlmail gvl on gvl.smtpemailtypeid = et.id "
"where et.smtpusergroupid = %ld",
a->SMTPUSERGROUPID);

   if(a->EMAILTYPE != -1)
   {
      sprintf(sqlStmt,"%s and et.emailtype = %ld ", sqlStmt, a->EMAILTYPE);
   }

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVSelEmailType SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVSelEmailType ;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVSelEmailType " ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVSelEmailType;
    return CheckSql( fun, stError, "%s", "close CVSelEmailType " );
}

//fetch one data line from the db
EXEC SQL fetch NEXT CVSelEmailType into :cvGVL, :cvEmailType, :cvID;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVSelEmailType " ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->EMAILTYPE = cvEmailType;
a->SENDGVLMAIL = cvGVL;
a->SMTPEMAILTYPEID = cvID;

return rc;
}

/* CremaEmailAddresses::Update ************************************************/

retClient Cremaemailaddresses_Update(cremaemailaddressesS *a, tError *stError, bool bIsTrans)
{
char *fun = "Cremaemailaddresses_Update";
exec sql begin declare section;

cremaemailaddressesS *d;

exec sql end declare section;

d = a;

   exec sql update smtpsendtoemailaddresses set
                     SMTPEmailTypeID = :d->SMTPEMAILTYPEID,
                     senttoaddress = :d->SENTTOADDRESS
            where id = :d->ID;

return CheckSql( fun, stError, "%s", "update address" );
}

/* CremaEmailAddresses::UpdateEmailAddress ************************************/

retClient Cremaemailaddresses_UpdateEmailAddress(cremaemailaddressesS *a, tError *stError, bool bIsTrans)
{
char *fun = "Cremaemailaddresses_UpdateAddress";
exec sql begin declare section;

cremaemailaddressesS *d;

exec sql end declare section;

d = a;

   exec sql update smtpsendtoemailaddresses set
                     senttoaddress = :d->SENTTOADDRESS 
            where id = :d->ID;

return CheckSql( fun, stError, "%s", "update address" );
}

/* CremaEmailAddresses::UpdateGVL *********************************************/

retClient Cremaemailaddresses_UpdateGVL(cremaemailaddressesS *a, tError *stError, bool bIsTrans)
{
char *fun = "Cremaemailaddresses_UpdateGVL";
exec sql begin declare section;

cremaemailaddressesS *d;

exec sql end declare section;

d = a;

   exec sql update smtpgvlmail set
                     sendgvlmail = :d->SENDGVLMAIL 
            where smtpemailtypeid = :d->SMTPEMAILTYPEID;

return CheckSql( fun, stError, "%s", "update gvl" );
}



/******************************************************************************/
/*                                                                            */
/* header  : CremaEmailReasons.cxx                                            */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:55:17 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "cremamailaddresses.h"

/* CremaEmailReasons: Select **************************************************/



/* CremaEmailReasons: Insert **************************************************/



/* CremaEmailReasons: Update **************************************************/



/* CremaEmailReasons: Select **************************************************/



/* CremaEmailReasons: Other ***************************************************/

/* CremaEmailReasons::SelEmailReasons *****************************************/

retClient Cremaemailreasons_SelEmailReasons(cremaemailreasonsS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

int cursorPos;

cremaemailreasonsS* d;

exec sql end declare section;
int anz = 0;
retClient rc = IS_OK;
char *fun = "Cremaemailreasons_SelEmailReasons";

d = a;

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   //declare cursor for later usage
   EXEC SQL DECLARE co CURSOR FOR
       select s.id, t.type, d.dlpercentage, a.thresholdamount 
       from smtpusergroups s
       join crematype t on s.crematypeid = t.id
       left join debtlevelformail d on t.typeid = d.id and t.type = 0
       left join amountformail a on t.typeid = a.id and t.type = 1
       where s.branchno = :d->BRANCHNO
   ;

   //open cursor here, so it will be done only one time
   EXEC SQL open co;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open cursor" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close co;
    return CheckSql( fun, stError, "%s", "close cursor" );
}

//fetch one data line from the db
EXEC SQL fetch co into :d->ID, :d->TYPE, :d->DLPERCENTAGE, :d->THRESHOLDAMOUNT;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch cursor" ) ) != IS_OK )
{
    return rc;
}

return rc;
}



