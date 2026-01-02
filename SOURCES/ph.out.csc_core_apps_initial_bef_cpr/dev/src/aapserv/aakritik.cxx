#include<bufkon.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<memory.h>
#include "texte.h"
#include <time.h>
#include "allg.h"
#include "kritiksatz.h"

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

int AakritikSel_kritik(kritikS *d, char *error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    kritikS *a;
    short sVzVon;
    short sVzBis;
    EXEC SQL END DECLARE SECTION;

    a = d;
    AllgMakeToLike(a->TITEL,L_KRITIK_TITEL);
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        if(a->VERTRIEBSZENTRUMNR == 0)
        {
            sVzVon = 0;
            sVzBis = 99;
        }
        else sVzVon = sVzBis = a->VERTRIEBSZENTRUMNR;

        EXEC SQL declare Sel_kritik scroll cursor with hold for
        select
            KDKRITIK.IDFNR,
            KDKRITIK.DATUM,
            KDKRITIK.ZEIT,
            KDKRITIK.UID,
            KDKRITIK.TITEL,
            KDKRITIK.KRITIKNR,
            KDKRITIK.VERTRIEBSZENTRUMNR,
            KDKRITIK.KUNDENNR,
            KDKRITIK.FILIALNR,
            KDKRITIK.KRITIKLEVEL,
            KUNDE.NAMEAPO,
            KUNDE.ORT,
            NVL(PASSWD.USERNAME, KDKRITIKPOS.WINDOWSID),
            CALLBACKDIVISION.DIVISIONNAME,
            KDKRITIKPOS.KRITIKTEXT,
            CALLBACKITEMS.CALLBACKNO,
            CALLBACKITEMS.REFERENCE,
            CALLBACKSTATUS.CALLBACKSTATUSNAME
        from kdkritik
        inner join kunde on
            kunde.kundennr = kdkritik.kundennr and
            kunde.vertriebszentrumnr = kdkritik.vertriebszentrumnr
        inner join callbackitems on
            callbackitems.kritiknr = kdkritik.kritiknr
        inner join callbackdivision on
            callbackitems.callbackpartno = callbackdivision.callbackdivisionno and
            kdkritik.VertriebszentrumNr = callbackdivision.Branchno
        inner join callbackstatus on
            callbackitems.callbackstatusid = callbackstatus.callbackstatusid
        left join passwd on
            passwd.uid = kdkritik.uid and
            passwd.filialnr = kdkritik.filialnr
        left join kdkritikpos on
            kdkritikpos.filialnr = kdkritik.filialnr and
            kdkritikpos.kritiknr = kdkritik.kritiknr and
            kdkritikpos.posnr = 1
        where
        kdkritik.titel				like	:a->TITEL					and
        kdkritik.datum				>=		:a->DATUM					and
        kdkritik.datum				<=		:a->ZEIT					and
        kdkritik.vertriebszentrumnr >=		:sVzVon						and
        kdkritik.vertriebszentrumnr <=		:sVzBis						and
        kdkritik.vertriebszentrumnr in (
            select	RegionArten.RegionTeilNr
            from	RegionArten
            where	RegionArten.RegionNr	=	:a->REGIONNR and 
                    RegionArten.RegionenTyp	=	1)
        order by kdkritik.datum desc, kdkritik.zeit desc;

        EXEC SQL open Sel_kritik;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AakritikSel_kritik: open Sel_kritik %ld",
            sqlca.sqlcode);
            return -1;
        }
    }

    if(a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sel_kritik;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AakritikSel_kritik: close Sel_kritik %ld",
            sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_kritik into KRITIK_ZEIGER(a);
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AakritikSel_kritik: fetch Sel_kritik %ld",
        sqlca.sqlcode);
        EXEC SQL close Sel_kritik;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

int AakritikSel_kritik_idf(kritikS *d, char *error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    kritikS   *a;
    short sVzVon;
    short sVzBis;
    EXEC SQL END DECLARE SECTION;

    a = d;
    AllgMakeToLike(a->TITEL,L_KRITIK_TITEL);
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        if(a->VERTRIEBSZENTRUMNR == 0)
        {
            sVzVon = 0;
            sVzBis = 99;
        }
        else sVzVon = sVzBis = a->VERTRIEBSZENTRUMNR;

        EXEC SQL declare Sel_kritik_idf scroll cursor with hold for
        select
             KDKRITIK.IDFNR,
             KDKRITIK.DATUM,
             KDKRITIK.ZEIT,
             KDKRITIK.UID,
             KDKRITIK.TITEL,
             KDKRITIK.KRITIKNR,
             KDKRITIK.VERTRIEBSZENTRUMNR,
             KDKRITIK.KUNDENNR,
             KDKRITIK.FILIALNR,
             KDKRITIK.KRITIKLEVEL,
             KUNDE.NAMEAPO,
             KUNDE.ORT,
             NVL(PASSWD.USERNAME, KDKRITIKPOS.WINDOWSID),
             CALLBACKDIVISION.DIVISIONNAME,
             KDKRITIKPOS.KRITIKTEXT,
             CALLBACKITEMS.CALLBACKNO,
             CALLBACKITEMS.REFERENCE,
             CALLBACKSTATUS.CALLBACKSTATUSNAME
        from kdkritik
        inner join kunde on
            kunde.kundennr = kdkritik.kundennr and
            kunde.vertriebszentrumnr = kdkritik.vertriebszentrumnr
        inner join callbackitems on
            callbackitems.kritiknr = kdkritik.kritiknr
        inner join callbackdivision on
            callbackitems.callbackpartno = callbackdivision.callbackdivisionno and
            kdkritik.VertriebszentrumNr = callbackdivision.Branchno
        inner join callbackstatus on
            callbackitems.callbackstatusid = callbackstatus.callbackstatusid
        left join passwd on
            passwd.uid = kdkritik.uid and
            passwd.filialnr = kdkritik.filialnr
        left join kdkritikpos on
            kdkritikpos.filialnr = kdkritik.filialnr and
            kdkritikpos.kritiknr = kdkritik.kritiknr and
            kdkritikpos.posnr = 1
        where
            kdkritik.kundennr			=		:a->IDFNR					and
            kdkritik.titel				like	:a->TITEL					and
            kdkritik.datum				>=		:a->DATUM					and
            kdkritik.datum				<=		:a->ZEIT					and
            kdkritik.vertriebszentrumnr >=		:sVzVon						and
            kdkritik.vertriebszentrumnr <=		:sVzBis						and
            kdkritik.vertriebszentrumnr in (
                select	RegionArten.RegionTeilNr
                from	RegionArten
                where	RegionArten.RegionNr	=	:a->REGIONNR and 
                        RegionArten.RegionenTyp	=	1)
        order by kdkritik.datum desc, kdkritik.zeit desc;

        EXEC SQL open Sel_kritik_idf;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AakritikSel_kritik_idf: open Sel_kritik_idf %ld",
            sqlca.sqlcode);
            return -1;
        }
    }

    if(a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Sel_kritik_idf;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AakritikSel_kritik_idf: close Sel_kritik_idf %ld",
            sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_kritik_idf into KRITIK_ZEIGER(a);
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AakritikSel_kritik_idf: fetch Sel_kritik_idf %ld",
        sqlca.sqlcode);
        EXEC SQL close Sel_kritik_idf;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

int AakritikSchreibe_kopf(kritikkopfS *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
kritikkopfS   *a;
short ind;
EXEC SQL END DECLARE SECTION;

a = d;

d->DATUM = AllgGetDate();
d->ZEIT = AllgGetTime();

for(;;)
{
	EXEC SQL select
		max(kritiknr)
	into
		:a->KRITIKNR indicator :ind
	from
		kdkritik;
	if (ind < 0) a->KRITIKNR = 0;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakritikSchreibe_kopf select %ld",
		sqlca.sqlcode);
		return -1;
	}
	a->KRITIKNR++;
	EXEC SQL begin work;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakritikSchreibe_kopf begin work %ld %ld",
		sqlca.sqlcode, sqlca.sqlerrd[1]);
		return -1;
	}
	EXEC SQL insert into kdkritik (
		IDFNR,
		DATUM,
		ZEIT,
		UID,
		TITEL,
		KRITIKNR,
		VERTRIEBSZENTRUMNR,
		KUNDENNR,
		FILIALNR,
		KRITIKLEVEL)
	values (
		:a->IDFNR,	
		:a->DATUM,
		:a->ZEIT,
		:a->UID,
		:a->TITEL,
		:a->KRITIKNR,
		:a->VERTRIEBSZENTRUMNR,
		:a->KUNDENNR,
		:a->FILIALNR,
		:a->KRITIKLEVEL);

	if (sqlca.sqlcode == -239 || sqlca.sqlcode == -268 ) continue;		/* Satz bereits vorhanden */
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakritikSchreibe_kopf insert %ld",
		sqlca.sqlcode);
		return -1;
	}
	EXEC SQL commit work;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakritikSchreibe_kopf commit work %ld %ld",
		sqlca.sqlcode, sqlca.sqlerrd[1]);
		return -1;
	}
	break;
}
return 0;
}

int AakritikSchreibe_pos(kritikposS *d, char *error_msg)
{
EXEC SQL BEGIN DECLARE SECTION;
kritikposS   *a;
short ind;
EXEC SQL END DECLARE SECTION;

a = d;

a->DATUM = AllgGetDate();
a->ZEIT = AllgGetTime();

for(;;)
{
	EXEC SQL select
		max(posnr)
	into
		:a->POSNR indicator :ind
	from
		kdkritikpos
	where
		kritiknr	= :a->KRITIKNR	and
		kzposart	= :a->KZPOSART;
	if (ind < 0) a->POSNR = 0;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakritikSchreibe_pos select %ld",
		sqlca.sqlcode);
		return -1;
	}
	a->POSNR++;
	EXEC SQL begin work;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakritikSchreibe_pos commit work %ld %ld",
		sqlca.sqlcode, sqlca.sqlerrd[1]);
		return -1;
	}

	EXEC SQL insert into kdkritikpos (
			KDKRITIKPOS.KRITIKNR,
			KDKRITIKPOS.POSNR,
			KDKRITIKPOS.KZPOSART,
			KDKRITIKPOS.KRITIKTEXT,
			KDKRITIKPOS.UID,
			KDKRITIKPOS.DATUM,
			KDKRITIKPOS.ZEIT,
			KDKRITIKPOS.FILIALNR)
			values (
			:a->KRITIKNR,
			:a->POSNR,
			:a->KZPOSART,
			:a->KRITIKTEXT,
			:a->UID,
			:a->DATUM,
			:a->ZEIT,
			:a->FILIALNR);
	if (sqlca.sqlcode == 239 ) continue;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakritikSchreibe_pos insert %ld",
		sqlca.sqlcode);
		return -1;
	}
	EXEC SQL commit work;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakritikSchreibe_pos commit work %ld %ld",
		sqlca.sqlcode, sqlca.sqlerrd[1]);
		return -1;
	}
	break;
}
return 0;
}

int AakritikSelect_pos(kritikposS *d, char *error_msg)
{
    static int fst = 1;

    EXEC SQL BEGIN DECLARE SECTION;
    kritikposS  *a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = 0;
        EXEC SQL declare Select_pos scroll cursor with hold for
            select
                KDKRITIKPOS.KRITIKNR,
                KDKRITIKPOS.POSNR,
                KDKRITIKPOS.KZPOSART,
                KDKRITIKPOS.UID,
                KDKRITIKPOS.DATUM,
                KDKRITIKPOS.ZEIT,
                KDKRITIKPOS.FILIALNR,
                KDKRITIKPOS.KRITIKTEXT,
                nvl(PASSWD.USERNAME, KDKRITIKPOS.WINDOWSID)
            from kdkritikpos
            left join passwd on passwd.filialnr = kdkritikpos.filialnr and passwd.uid = kdkritikpos.uid
            where 
                kdkritikpos.kritiknr = :a->KRITIKNR
            order by kzposart,posnr;

        EXEC SQL open Select_pos;
        if (sqlca.sqlcode < 0 )
        {
            fst = 1;
            sprintf(error_msg, " AakritikSelect_pos: open Select_pos %ld", sqlca.sqlcode);
            return -1;
        }
    }

    if(a->FETCH_REL == 0)   /* close cursor */
    {
        fst = 1;
        EXEC SQL close Select_pos;
        if (sqlca.sqlcode < 0 )
        {
            sprintf(error_msg, " AakritikSelect_pos: close Select_pos %ld",
            sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Select_pos into KRITIKPOS_ZEIGER(a);
    if (sqlca.sqlcode < 0 )
    {
        fst = 1;
        sprintf(error_msg, " AakritikSelect_pos: fetch Select_pos %ld",
        sqlca.sqlcode);
        EXEC SQL close Select_pos;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

int AakritikSel_kritikuser(kritikS *d, char *error_msg)
{

	EXEC SQL BEGIN DECLARE SECTION;
	kritikS   *a;
	EXEC SQL END DECLARE SECTION;
	
	a = d;
	
	EXEC SQL select
        NVL(PASSWD.USERNAME, KDKRITIKPOS.WINDOWSID),
        KDKRITIK.KRITIKLEVEL
	into
		 :a->USERNAME64,
		 :a->KRITIKLEVEL
    from kdkritik
    left join passwd on
        passwd.uid = kdkritik.uid and
        passwd.filialnr = kdkritik.filialnr
    left join kdkritikpos on
        kdkritikpos.filialnr = kdkritik.filialnr and
        kdkritikpos.kritiknr = kdkritik.kritiknr and
        kdkritikpos.posnr = 1
	where 
		kdkritik.kritiknr	=	:a->KRITIKNR;

	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, " AakritikSel_kritikuser: select %ld",
			sqlca.sqlcode);
		return -1;
	}
	return 0;
}

