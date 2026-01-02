/******************************************************************************/
/*                                                                            */
/* header  : MailDefinedUser.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:04:23 2022                                         */
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
#include "mailsystem.h"

/* MailDefinedUser: Select ****************************************************/

/* MailDefinedUser::SelAllUser ************************************************/

retClient Maildefineduser_SelAllUser(maildefineduserS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Maildefineduser_SelAllUser";
    exec sql begin declare section;
    maildefineduserS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllUser0 cursor with hold for
                  select passwd.filialnr,
                     passwd.username,
                     passwd.uid,
                     mailusers.GroupNo
                from PASSWD, outer MAILUSERS
                  where mailusers.GroupNo	 =	:d->GROUPNO	and
                        passwd.filialnr	 =	mailusers.filialnr	and
                        passwd.uid	 =	mailusers.uid
                        order by passwd.username;
        exec sql open CSelAllUser0;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllUser0" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelAllUser0;
        return CheckSql( fun, stError, "%s", "close CSelAllUser0" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllUser0 into :d->FILIALNR,
                     :d->USERNAME,
                     :d->UID,
                     :d->GROUPNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllUser0" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MailDefinedUser::SelAllUserVz **********************************************/

retClient Maildefineduser_SelAllUserVz(maildefineduserS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Maildefineduser_SelAllUserVz";
    exec sql begin declare section;
    maildefineduserS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAllUserVz1 cursor with hold for
                  select passwd.filialnr,
                     passwd.username,
                     passwd.uid,
                     mailusers.GroupNo
                from PASSWD, outer MAILUSERS
                  where mailusers.GroupNo	 =	:d->GROUPNO	and
                        passwd.filialnr	 =	mailusers.filialnr	and
                        passwd.uid	 =	mailusers.uid	and
                        passwd.filialnr	 =	:d->FILIALNR
                        order by passwd.username;
        exec sql open CSelAllUserVz1;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllUserVz1" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelAllUserVz1;
        return CheckSql( fun, stError, "%s", "close CSelAllUserVz1" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAllUserVz1 into :d->FILIALNR,
                     :d->USERNAME,
                     :d->UID,
                     :d->GROUPNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAllUserVz1" )) == IS_ERROR )
        return rc;
    return rc;
}

/* MailDefinedUser::SelOpenMail ***********************************************/

retClient Maildefineduser_SelOpenMail(maildefineduserS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Maildefineduser_SelOpenMail";
    exec sql begin declare section;
    maildefineduserS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelOpenMail2 cursor with hold for
                  select passwd.filialnr,
                     passwd.username,
                     passwd.uid,
                     mailusers.GroupNo
                from PASSWD,MAILITEMS, outer MAILUSERS
                  where mailitems.newsno	 =	:d->GROUPNO	and
                        mailusers.uid	 =	mailitems.uid	and
                        mailusers.filialnr	 =	mailitems.filialnr	and
                        passwd.filialnr	 =	mailitems.filialnr	and
                        passwd.uid	 =	mailitems.uid;
        exec sql open CSelOpenMail2;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelOpenMail2" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelOpenMail2;
        return CheckSql( fun, stError, "%s", "close CSelOpenMail2" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelOpenMail2 into :d->FILIALNR,
                     :d->USERNAME,
                     :d->UID,
                     :d->GROUPNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelOpenMail2" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MailDefinedUser: Insert ****************************************************/



/* MailDefinedUser: Update ****************************************************/



/* MailDefinedUser: Select ****************************************************/



/* MailDefinedUser: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : UserInformation.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:04:29 2022                                         */
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
#include "mailsystem.h"

/* UserInformation: Select ****************************************************/

/* UserInformation::CheckFree *************************************************/

retClient Userinformation_CheckFree(userinformationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Userinformation_CheckFree";
    exec sql begin declare section;
    userinformationS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CCheckFree3 cursor with hold for
                  select userinformation.date,
                     userinformation.ValidTimeFrom,
                     userinformation.ValidTimeTo,
                     userinformation.InfoMessage,
                     userinformation.ValidBranchNo,
                     userinformation.UserBranchNo,
                     userinformation.uid_anlage,
                     userinformation.priority
                from USERINFORMATION
                  where Userinformation.date	 =	:d->DATE	 and
                        ( ( 
                        ( Userinformation.ValidTimeFrom	<=	:d->VALIDTIMEFROM	 and
                        Userinformation.ValidTimeTo	>=	:d->VALIDTIMEFROM	) or
                        ( Userinformation.ValidTimeFrom	<=	:d->VALIDTIMETO	 and
                        Userinformation.ValidTimeTo	>=	:d->VALIDTIMETO )
                        ) or
                        ( Userinformation.ValidTimeFrom	>=	:d->VALIDTIMEFROM	 and
                        Userinformation.ValidTimeTo	<=	:d->VALIDTIMETO	)
                        );
        exec sql open CCheckFree3;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CCheckFree3" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CCheckFree3;
        return CheckSql( fun, stError, "%s", "close CCheckFree3" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CCheckFree3 into :d->DATE,
                     :d->VALIDTIMEFROM,
                     :d->VALIDTIMETO,
                     :d->INFOMESSAGE,
                     :d->VALIDBRANCHNO,
                     :d->USERBRANCHNO,
                     :d->UID_ANLAGE,
                     :d->PRIORITY;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CCheckFree3" )) == IS_ERROR )
        return rc;
    return rc;
}

/* UserInformation::SelInfo ***************************************************/

retClient Userinformation_SelInfo(userinformationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Userinformation_SelInfo";
    exec sql begin declare section;
    userinformationS *d;
    long lDate;
    long lTime;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    lTime = ppGGetTime();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelInfo4 cursor with hold for
                  select userinformation.date,
                     userinformation.ValidTimeFrom,
                     userinformation.ValidTimeTo,
                     userinformation.InfoMessage,
                     userinformation.ValidBranchNo,
                     userinformation.UserBranchNo,
                     userinformation.uid_anlage,
                     userinformation.priority
                from USERINFORMATION
                  where Userinformation.date	 =	:lDate  and
                        Userinformation.ValidTimeFrom	<=	:lTime  and
                        Userinformation.ValidTimeTo	>=	:lTime  and
                        (
                        Userinformation.ValidBranchNo	 =	0 or
                        Userinformation.ValidBranchNo	 =	:d->VALIDBRANCHNO	
                        );
        exec sql open CSelInfo4;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelInfo4" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelInfo4;
        return CheckSql( fun, stError, "%s", "close CSelInfo4" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelInfo4 into :d->DATE,
                     :d->VALIDTIMEFROM,
                     :d->VALIDTIMETO,
                     :d->INFOMESSAGE,
                     :d->VALIDBRANCHNO,
                     :d->USERBRANCHNO,
                     :d->UID_ANLAGE,
                     :d->PRIORITY;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelInfo4" )) == IS_ERROR )
        return rc;
    return rc;
}



/* UserInformation: Insert ****************************************************/

/* UserInformation::Insert ****************************************************/

retClient Userinformation_Insert(userinformationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Userinformation_Insert";
    exec sql begin declare section;
    userinformationS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->INFOMESSAGE);
    if ( *d->INFOMESSAGE == '\0' )
        strcpy( d->INFOMESSAGE, " " );
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into userinformation (date,
                     ValidTimeFrom,
                     ValidTimeTo,
                     InfoMessage,
                     ValidBranchNo,
                     UserBranchNo,
                     uid_anlage,
                     priority)
        values (:d->DATE,
                     :d->VALIDTIMEFROM,
                     :d->VALIDTIMETO,
                     :d->INFOMESSAGE,
                     :d->VALIDBRANCHNO,
                     :d->USERBRANCHNO,
                     :d->UID_ANLAGE,
                     :d->PRIORITY);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert userinformation" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}



/* UserInformation: Update ****************************************************/



/* UserInformation: Select ****************************************************/



/* UserInformation: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : mailgroup.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:04:33 2022                                         */
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
#include "mailsystem.h"

/* mailgroup: Select **********************************************************/

/* mailgroup::SelMailGroup ****************************************************/

retClient mailgroup_SelMailGroup(mailgroupS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "mailgroup_SelMailGroup";
    exec sql begin declare section;
    mailgroupS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelMailGroup5 cursor with hold for
                  select mailgroup.GroupNo,
                     mailgroup.GroupName
                from mailgroup
                  where mailgroup.GroupNo	!=	0
                        order by mailgroup.GroupName;
        exec sql open CSelMailGroup5;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelMailGroup5" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelMailGroup5;
        return CheckSql( fun, stError, "%s", "close CSelMailGroup5" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelMailGroup5 into :d->GROUPNO,
                     :d->GROUPNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelMailGroup5" )) == IS_ERROR )
        return rc;
    return rc;
}

/* mailgroup::SelMailGroupVz **************************************************/

retClient mailgroup_SelMailGroupVz(mailgroupS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "mailgroup_SelMailGroupVz";
    exec sql begin declare section;
    mailgroupS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelMailGroupVz6 cursor with hold for
                  select Distinct mailgroup.GroupNo,
                     mailgroup.GroupName
                from MAILGROUP,MAILUSERS
                  where mailgroup.GroupNo	!=	0	and
                        mailgroup.GroupNo = mailusers.GroupNo	and
                        mailusers.FilialNr = :d->GROUPNO
                        order by mailgroup.GroupName;
        exec sql open CSelMailGroupVz6;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelMailGroupVz6" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelMailGroupVz6;
        return CheckSql( fun, stError, "%s", "close CSelMailGroupVz6" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelMailGroupVz6 into :d->GROUPNO,
                     :d->GROUPNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelMailGroupVz6" )) == IS_ERROR )
        return rc;
    return rc;
}



/* mailgroup: Insert **********************************************************/

/* mailgroup::Insert **********************************************************/

retClient mailgroup_Insert(mailgroupS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "mailgroup_Insert";
    exec sql begin declare section;
    mailgroupS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select MAX(groupno) + 1 into :d->GROUPNO indicator :d->FETCH_REL from mailgroup;
if ( ( rc=CheckSql( fun, stError, "%s", "select max" ) ) != IS_OK )
 return rc;
else if ( d->FETCH_REL < 0 )
  d->GROUPNO = 1; /* start with 1 */
    exec sql insert into mailgroup (GroupNo,
                     GroupName)
        values (:d->GROUPNO,
                     :d->GROUPNAME);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert mailgroup" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}



/* mailgroup: Update **********************************************************/

/* mailgroup::UpdateMailGroup *************************************************/

retClient mailgroup_UpdateMailGroup(mailgroupS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "mailgroup_UpdateMailGroup";
    exec sql begin declare section;
    mailgroupS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdateMailGroup7 cursor with hold for
              select GroupNo,
                     GroupName
               from mailgroup
              where mailgroup.GroupNo	 =	:d->GROUPNO
              for update;
    exec sql open CUpdateMailGroup7;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdateMailGroup7" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdateMailGroup7;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdateMailGroup7" ) ) != IS_OK )
            break;
        exec sql update mailgroup set GroupNo = :d->GROUPNO,
                     GroupName = :d->GROUPNAME where current of CUpdateMailGroup7;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdateMailGroup7" ) ) != IS_OK )
            break;
        break;
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            if ( bInTrans )
            {
                if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                    return rc;
            }
        }
    }
    return rc;
}



/* mailgroup: Select **********************************************************/

/* mailgroup::DeleteMailGroup *************************************************/

retClient mailgroup_DeleteMailGroup(mailgroupS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "mailgroup_DeleteMailGroup";
    exec sql begin declare section;
    mailgroupS *d;
    exec sql end declare section;

    d = a;

    exec sql select count(*) into :d->FETCH_REL from mailusers where groupno = :d->GROUPNO;
if ( ( rc=CheckSql( fun, stError, "%s", "select count(*)" ) ) != IS_OK )
      return rc;
else if ( d->FETCH_REL > 0 )
{
    sprintf(stError->spError,"%s für diese Gruppe noch Einträge vorhanden",fun);
    return IS_WARNING;
}
    exec sql declare CDeleteMailGroup8 cursor with hold for
              select GroupNo,
                     GroupName
               from mailgroup
              where mailgroup.GroupNo	 =	:d->GROUPNO
              for update;
    exec sql open CDeleteMailGroup8;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteMailGroup8" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteMailGroup8;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteMailGroup8" ) ) != IS_OK )
            break;
        exec sql delete from mailgroup where current of CDeleteMailGroup8;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteMailGroup8" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
        {
            if ( bIsTrans )
            {
                if ( bInTrans )
                {
                    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                        return rc;
                }
            }
            if ( bIsTrans )
            {
                if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                    return rc;
                bInTrans = true;
            }
        }
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}



/* mailgroup: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : mailitems.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:04:36 2022                                         */
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
#include "mailsystem.h"

/* mailitems: Select **********************************************************/

/* mailitems::SelOpenNews *****************************************************/

retClient mailitems_SelOpenNews(mailitemsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "mailitems_SelOpenNews";
    exec sql begin declare section;
    mailitemsS *d;
    long lDate;
    long lTime;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    lTime = ppGGetTime();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelOpenNews9 cursor with hold for
                  select mailitems.filialnr,
                     mailitems.uid,
                     mailitems.NewsNo
                from MAILITEMS,MAILMESSAGE
                  where mailitems.filialnr	 =	:d->FILIALNR	and
                        mailitems.uid	 =	:d->UID	and
                        mailitems.NewsNo	 =	mailmessage.NewsNo	and
                        (mailmessage.tm_date		<	:lDate or
                        (mailmessage.tm_date		=	:lDate and
                        mailmessage.tm_time	 	<=	:lTime ));
        exec sql open CSelOpenNews9;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelOpenNews9" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelOpenNews9 into :d->FILIALNR,
                     :d->UID,
                     :d->NEWSNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelOpenNews9" )) == IS_ERROR )
        return rc;
    return rc;
}



/* mailitems: Insert **********************************************************/

/* mailitems::Insert **********************************************************/

retClient mailitems_Insert(mailitemsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "mailitems_Insert";
    exec sql begin declare section;
    mailitemsS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into mailitems (filialnr,
                     uid,
                     NewsNo)
        values (:d->FILIALNR,
                     :d->UID,
                     :d->NEWSNO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert mailitems" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}



/* mailitems: Update **********************************************************/



/* mailitems: Select **********************************************************/

/* mailitems::DeleteMessage ***************************************************/

retClient mailitems_DeleteMessage(mailitemsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "mailitems_DeleteMessage";
    exec sql begin declare section;
    mailitemsS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteMessage10 cursor with hold for
              select filialnr,
                     uid,
                     NewsNo
               from mailitems
              where mailitems.filialnr	 =	:d->FILIALNR	and
                    mailitems.uid	 =	:d->UID	and
                    mailitems.NewsNo	 =	:d->NEWSNO
              for update;
    exec sql open CDeleteMessage10;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteMessage10" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteMessage10;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteMessage10" ) ) != IS_OK )
            break;
        exec sql delete from mailitems where current of CDeleteMessage10;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteMessage10" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
        {
            if ( bIsTrans )
            {
                if ( bInTrans )
                {
                    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                        return rc;
                }
            }
            if ( bIsTrans )
            {
                if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                    return rc;
                bInTrans = true;
            }
        }
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}



/* mailitems: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : mailmessage.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:04:40 2022                                         */
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
#include "mailsystem.h"

/* mailmessage: Select ********************************************************/

/* mailmessage::SelMailMessage ************************************************/

retClient mailmessage_SelMailMessage(mailmessageS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "mailmessage_SelMailMessage";
    exec sql begin declare section;
    mailmessageS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelMailMessage11 cursor with hold for
                  select mailmessage.NewsNo,
                     mailmessage.message,
                     mailmessage.tm_date,
                     mailmessage.tm_time,
                     mailmessage.uid,
                     mailmessage.filialnr,
                     mailmessage.priority
                from mailmessage
                  where mailmessage.NewsNo	 =	:d->NEWSNO;
        exec sql open CSelMailMessage11;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelMailMessage11" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelMailMessage11;
        return CheckSql( fun, stError, "%s", "close CSelMailMessage11" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelMailMessage11 into :d->NEWSNO,
                     :d->MESSAGE,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->UID,
                     :d->FILIALNR,
                     :d->PRIORITY;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelMailMessage11" )) == IS_ERROR )
        return rc;
    return rc;
}



/* mailmessage: Insert ********************************************************/

/* mailmessage::Insert ********************************************************/

retClient mailmessage_Insert(mailmessageS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "mailmessage_Insert";
    exec sql begin declare section;
    mailmessageS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->MESSAGE);
    if ( *d->MESSAGE == '\0' )
        strcpy( d->MESSAGE, " " );
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select MAX(newsno) + 1 into :d->NEWSNO indicator :d->FETCH_REL from mailmessage;
if ( ( rc=CheckSql( fun, stError, "%s", "select max" ) ) != IS_OK )
 return rc;
else if ( d->FETCH_REL < 0 )
  d->NEWSNO = 1; /* start with 1 */
    exec sql insert into mailmessage (NewsNo,
                     message,
                     tm_date,
                     tm_time,
                     uid,
                     filialnr,
                     priority)
        values (:d->NEWSNO,
                     :d->MESSAGE,
                     :d->TM_DATE,
                     :d->TM_TIME,
                     :d->UID,
                     :d->FILIALNR,
                     :d->PRIORITY);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert mailmessage" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}



/* mailmessage: Update ********************************************************/



/* mailmessage: Select ********************************************************/



/* mailmessage: Other *********************************************************/

/* mailmessage::SelAllMessage *************************************************/

retClient mailmessage_SelAllMessage(mailmessageS *a, tError *stError, bool bIsTrans)
{
/* don't change this lines!!!!!! */
retClient rc = IS_OK;
char *fun = "SelAllMessage";

exec sql begin declare section;
mailmessageS *d;
long datumvon;
long datumbis;
exec sql end declare section;

d = a;
if ( a->FETCH_REL == SET_OPEN )
{
  if ( a->TM_DATE == 0 )
  {
    datumvon = 0;
    datumbis  = 21000101;
  }
  else
  {
    datumvon = a->TM_DATE;
    datumbis  = a->TM_DATE;
  }
  exec sql declare CSelAllMess cursor with hold for
  select
  count(mailitems.uid)
  ,mailmessage.newsno
  ,message
  ,tm_date
  ,tm_time
  from mailmessage,outer mailitems
  where mailitems.newsno = mailmessage.newsno
  and tm_date >= :datumvon
  and tm_date <= :datumbis
  group by
  mailmessage.newsno
  ,message
  ,tm_date
  ,tm_time
  order by tm_date,tm_time;
  exec sql open CSelAllMess;
  if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAllMess" ) ) != IS_OK )
    return rc;
}

if ( a->FETCH_REL == SET_CLOSE )
{
  if ( bIsTrans )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
  }
  exec sql close CSelAllMess;
  return CheckSql( fun, stError, "%s", "close CSelAllMess" );
}

if ( bIsTrans )
{
  if ( ( rc = Begin( fun, stError ) ) != IS_OK )
    return rc;
}
exec sql fetch CSelAllMess
  into
  :d->UID
  ,:d->NEWSNO
  ,:d->MESSAGE
  ,:d->TM_DATE
  ,:d->TM_TIME;
  return CheckSql( fun, stError, "%s", "fetch CSelAllMess" );
}

/* mailmessage::SelNotRead ****************************************************/

retClient mailmessage_SelNotRead(mailmessageS *a, tError *stError, bool bIsTrans)
{
/* don't change this lines!!!!!! */
retClient rc = IS_OK;
char *fun = "SelNotRead";

exec sql begin declare section;
mailmessageS *d;
long datumvon;
long datumbis;
exec sql end declare section;

d = a;
if ( a->FETCH_REL == SET_OPEN )
{
  if ( a->TM_DATE == 0 )
  {
    datumvon = 0;
    datumbis  = 21000101;
  }
  else
  {
    datumvon = a->TM_DATE;
    datumbis  = a->TM_DATE;
  }
  exec sql declare CSelNotRead cursor with hold for
  select
  count(mailitems.uid)
  ,mailmessage.newsno
  ,message
  ,tm_date
  ,tm_time
  from mailitems,mailmessage
  where mailitems.newsno = mailmessage.newsno
  and tm_date >= :datumvon
  and tm_date <= :datumbis
  group by
  mailmessage.newsno
  ,message
  ,tm_date
  ,tm_time
  order by tm_date,tm_time;
  exec sql open CSelNotRead;
  if ( ( rc=CheckSql( fun, stError, "%s", "open CSelNotRead" ) ) != IS_OK )
    return rc;
}

if ( a->FETCH_REL == SET_CLOSE )
{
  if ( bIsTrans )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
  }
  exec sql close CSelNotRead;
  return CheckSql( fun, stError, "%s", "close CSelNotRead" );
}

if ( bIsTrans )
{
  if ( ( rc = Begin( fun, stError ) ) != IS_OK )
    return rc;
}
exec sql fetch CSelNotRead
  into
  :d->UID
  ,:d->NEWSNO
  ,:d->MESSAGE
  ,:d->TM_DATE
  ,:d->TM_TIME;
  return CheckSql( fun, stError, "%s", "fetch CSelNotRead" );
}



/******************************************************************************/
/*                                                                            */
/* header  : mailusers.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:04:44 2022                                         */
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
#include "mailsystem.h"

/* mailusers: Select **********************************************************/

/* mailusers::SelAll **********************************************************/

retClient mailusers_SelAll(mailusersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "mailusers_SelAll";
    exec sql begin declare section;
    mailusersS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelAll12 cursor with hold for
                  select mailusers.GroupNo,
                     mailusers.uid,
                     mailusers.filialnr
                from mailusers
                  where mailusers.GroupNo	 =	:d->GROUPNO;
        exec sql open CSelAll12;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelAll12" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelAll12;
        return CheckSql( fun, stError, "%s", "close CSelAll12" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelAll12 into :d->GROUPNO,
                     :d->UID,
                     :d->FILIALNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelAll12" )) == IS_ERROR )
        return rc;
    return rc;
}



/* mailusers: Insert **********************************************************/

/* mailusers::Insert **********************************************************/

retClient mailusers_Insert(mailusersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "mailusers_Insert";
    exec sql begin declare section;
    mailusersS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into mailusers (GroupNo,
                     uid,
                     filialnr)
        values (:d->GROUPNO,
                     :d->UID,
                     :d->FILIALNR);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert mailusers" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}



/* mailusers: Update **********************************************************/



/* mailusers: Select **********************************************************/

/* mailusers::Delete **********************************************************/

retClient mailusers_Delete(mailusersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "mailusers_Delete";
    exec sql begin declare section;
    mailusersS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete13 cursor with hold for
              select GroupNo,
                     uid,
                     filialnr
               from mailusers
              where mailusers.GroupNo	 =	:d->GROUPNO	and
                    mailusers.uid	 =	:d->UID	and
                    mailusers.filialnr	 =	:d->FILIALNR
              for update;
    exec sql open CDelete13;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete13" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete13;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete13" ) ) != IS_OK )
            break;
        exec sql delete from mailusers where current of CDelete13;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete13" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
        {
            if ( bIsTrans )
            {
                if ( bInTrans )
                {
                    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                        return rc;
                }
            }
            if ( bIsTrans )
            {
                if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                    return rc;
                bInTrans = true;
            }
        }
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* mailusers::DeleteAll *******************************************************/

retClient mailusers_DeleteAll(mailusersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "mailusers_DeleteAll";
    exec sql begin declare section;
    mailusersS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteAll14 cursor with hold for
              select GroupNo,
                     uid,
                     filialnr
               from mailusers
              where mailusers.GroupNo	 =	:d->GROUPNO
              for update;
    exec sql open CDeleteAll14;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteAll14" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteAll14;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteAll14" ) ) != IS_OK )
            break;
        exec sql delete from mailusers where current of CDeleteAll14;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteAll14" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
        {
            if ( bIsTrans )
            {
                if ( bInTrans )
                {
                    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                        return rc;
                }
            }
            if ( bIsTrans )
            {
                if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                    return rc;
                bInTrans = true;
            }
        }
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* mailusers::DeleteAllVz *****************************************************/

retClient mailusers_DeleteAllVz(mailusersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "mailusers_DeleteAllVz";
    exec sql begin declare section;
    mailusersS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteAllVz15 cursor with hold for
              select GroupNo,
                     uid,
                     filialnr
               from mailusers
              where mailusers.GroupNo	 =	:d->GROUPNO	 and
                    mailusers.filialnr	 =	:d->FILIALNR
              for update;
    exec sql open CDeleteAllVz15;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteAllVz15" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteAllVz15;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteAllVz15" ) ) != IS_OK )
            break;
        exec sql delete from mailusers where current of CDeleteAllVz15;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteAllVz15" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
        {
            if ( bIsTrans )
            {
                if ( bInTrans )
                {
                    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                        return rc;
                }
            }
            if ( bIsTrans )
            {
                if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                    return rc;
                bInTrans = true;
            }
        }
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}



/* mailusers: Other ***********************************************************/



