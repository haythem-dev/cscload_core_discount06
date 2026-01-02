/******************************************************************************/
/*                                                                            */
/* header  : SonderTouren.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:02:52 2022                                         */
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
#include "touren.h"

/* SonderTouren: Select *******************************************************/

/* SonderTouren::SelList ******************************************************/

retClient Sondertouren_SelList(sondertourenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Sondertouren_SelList";
    exec sql begin declare section;
    sondertourenS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList0 cursor with hold for
                  select sondertouren.tourid,
                     sondertouren.kdauftragart,
                     sondertouren.filialnr
                from SONDERTOUREN
                  where sondertouren.filialnr	 =	:d->FILIALNR;
        exec sql open CSelList0;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList0" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList0;
        return CheckSql( fun, stError, "%s", "close CSelList0" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList0 into :d->TOURID,
                     :d->KDAUFTRAGART,
                     :d->FILIALNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* SonderTouren: Insert *******************************************************/

/* SonderTouren::Insert *******************************************************/

retClient Sondertouren_Insert(sondertourenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Sondertouren_Insert";
    exec sql begin declare section;
    sondertourenS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into sondertouren (tourid,
                     kdauftragart,
                     filialnr)
        values (:d->TOURID,
                     :d->KDAUFTRAGART,
                     :d->FILIALNR);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert sondertouren" ) ) != IS_OK )
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



/* SonderTouren: Update *******************************************************/

/* SonderTouren::Update *******************************************************/

retClient Sondertouren_Update(sondertourenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Sondertouren_Update";
    exec sql begin declare section;
    sondertourenS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate1 cursor with hold for
              select tourid,
                     kdauftragart,
                     filialnr
               from SONDERTOUREN
              where sondertouren.filialnr	 =	:d->FILIALNR	 and
                    sondertouren.tourid	 =	:d->TOURID
              for update;
    exec sql open CUpdate1;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate1" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate1;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate1" ) ) != IS_OK )
            break;
        exec sql update sondertouren set tourid = :d->TOURID,
                     kdauftragart = :d->KDAUFTRAGART,
                     filialnr = :d->FILIALNR where current of CUpdate1;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate1" ) ) != IS_OK )
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



/* SonderTouren: Select *******************************************************/

/* SonderTouren::Delete *******************************************************/

retClient Sondertouren_Delete(sondertourenS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Sondertouren_Delete";
    exec sql begin declare section;
    sondertourenS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete2 cursor with hold for
              select tourid,
                     kdauftragart,
                     filialnr
               from SONDERTOUREN
              where sondertouren.filialnr	 =	:d->FILIALNR	 and
                    sondertouren.tourid	 =	:d->TOURID
              for update;
    exec sql open CDelete2;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete2" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete2;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete2" ) ) != IS_OK )
            break;
        exec sql delete from sondertouren where current of CDelete2;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete2" ) ) != IS_OK )
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
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc;
}



/* SonderTouren: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : TourPlanPflege.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:02:57 2022                                         */
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
#include "touren.h"

/* TourPlanPflege: Select *****************************************************/

/* TourPlanPflege::SelList ****************************************************/

retClient Tourplanpflege_SelList(tourplanpflegeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tourplanpflege_SelList";
    exec sql begin declare section;
    tourplanpflegeS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList3 cursor with hold for
                  select tourplantag.datumkommi,
                     tourplantag.tourid,
                     tourplantag.VertriebszentrumNr,
                     tourplantag.KundenNr,
                     tourplantag.kzautozuord,
                     tourplantag.IsBTM,
                     tourplantag.IsKK,
                     tourplantag.IsK08,
                     tourplantag.IsK20
                from Tourplantag
                  where tourplantag.datumkommi	 =	:d->DATUMKOMMI	 and
                        tourplantag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        tourplantag.KundenNr		 =	:d->KUNDENNR and
                        tourplantag.tourinaktiv	!=	'1';
        exec sql open CSelList3;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList3" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList3;
        return CheckSql( fun, stError, "%s", "close CSelList3" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList3 into :d->DATUMKOMMI,
                     :d->TOURID,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->KZAUTOZUORD,
                     :d->ISBTM,
                     :d->ISKK,
                     :d->ISK08,
                     :d->ISK20;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList3" )) == IS_ERROR )
        return rc;
    return rc;
}

/* TourPlanPflege::SelTour ****************************************************/

retClient Tourplanpflege_SelTour(tourplanpflegeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Tourplanpflege_SelTour";
    exec sql begin declare section;
    tourplanpflegeS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select tourplantag.datumkommi,
                     tourplantag.tourid,
                     tourplantag.VertriebszentrumNr,
                     tourplantag.KundenNr,
                     tourplantag.kzautozuord,
                     tourplantag.IsBTM,
                     tourplantag.IsKK,
                     tourplantag.IsK08,
                     tourplantag.IsK20
                into :d->DATUMKOMMI,
                     :d->TOURID,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->KUNDENNR,
                     :d->KZAUTOZUORD,
                     :d->ISBTM,
                     :d->ISKK,
                     :d->ISK08,
                     :d->ISK20
                from Tourplantag
              where tourplantag.datumkommi	 =	:d->DATUMKOMMI	 and
                    tourplantag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    tourplantag.KundenNr		 =	:d->KUNDENNR and
                    tourplantag.tourinaktiv	!=	'1' and
                    tourplantag.tourid	 =	:d->TOURID;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* TourPlanPflege: Insert *****************************************************/



/* TourPlanPflege: Update *****************************************************/

/* TourPlanPflege::Update *****************************************************/

retClient Tourplanpflege_Update(tourplanpflegeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Tourplanpflege_Update";
    exec sql begin declare section;
    tourplanpflegeS *d;
    exec sql end declare section;

    d = a;

    sprintf(stError->spError,"User %s changed Tour %s for Customer %d %d to %d %d %d %d",d->TERMID,
d->TOURID,d->VERTRIEBSZENTRUMNR,d->KUNDENNR,
d->ISBTM,d->ISKK,d->ISK08,d->ISK20);
WriteLogInfo(stError->spError,0,0);


    exec sql declare CUpdate5 cursor with hold for
              select kzautozuord,
                     IsBTM,
                     IsKK,
                     IsK08,
                     IsK20
               from Tourplantag
              where tourplantag.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                    tourplantag.KundenNr	 =	:d->KUNDENNR	 and
                    tourplantag.datumkommi	 =	:d->DATUMKOMMI	 and
                    tourplantag.tourid	 =	:d->TOURID
              for update;
    exec sql open CUpdate5;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate5" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate5;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate5" ) ) != IS_OK )
            break;
        exec sql update tourplantag set kzautozuord = :d->KZAUTOZUORD,
                     IsBTM = :d->ISBTM,
                     IsKK = :d->ISKK,
                     IsK08 = :d->ISK08,
                     IsK20 = :d->ISK20 where current of CUpdate5;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate5" ) ) != IS_OK )
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



/* TourPlanPflege: Select *****************************************************/



/* TourPlanPflege: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : TourSperre.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:03:00 2022                                         */
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
#include "touren.h"

/* TourSperre: Select *********************************************************/

/* TourSperre::SelList ********************************************************/

retClient Toursperre_SelList(toursperreS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Toursperre_SelList";
    exec sql begin declare section;
    toursperreS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList6 cursor with hold for
                  select tour.datumkommi,
                     tour.tourid,
                     tour.bezeichnung,
                     tour.filialnr,
                     tour.tourinaktiv,
                     tour.ersatzfilialnr
                from tour
                  where tour.datumkommi	 =	:lDate	 and
                        tour.filialnr	 =	:d->FILIALNR	 and
                        tour.tourid	>=	:d->TOURID and
                        (tour.tourid	 <	"475900" or
                        tour.tourid	 	 >	"476000");
        exec sql open CSelList6;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList6" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList6;
        return CheckSql( fun, stError, "%s", "close CSelList6" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList6 into :d->DATUMKOMMI,
                     :d->TOURID,
                     :d->BEZEICHNUNG,
                     :d->FILIALNR,
                     :d->TOURINAKTIV,
                     :d->ERSATZFILIALNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList6" )) == IS_ERROR )
        return rc;
    return rc;
}



/* TourSperre: Insert *********************************************************/



/* TourSperre: Update *********************************************************/

/* TourSperre::Update *********************************************************/

retClient Toursperre_Update(toursperreS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Toursperre_Update";
    exec sql begin declare section;
    toursperreS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();


    exec sql declare CUpdate7 cursor with hold for
              select datumkommi,
                     tourid,
                     bezeichnung,
                     filialnr,
                     tourinaktiv,
                     ersatzfilialnr
               from tour
              where tour.datumkommi	 =	:lDate	 and
                    tour.filialnr	 =	:d->FILIALNR	 and
                    tour.tourid	 =	:d->TOURID
              for update;
    exec sql open CUpdate7;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate7" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate7;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate7" ) ) != IS_OK )
            break;
        exec sql update tour set datumkommi = :d->DATUMKOMMI,
                     tourid = :d->TOURID,
                     bezeichnung = :d->BEZEICHNUNG,
                     filialnr = :d->FILIALNR,
                     tourinaktiv = :d->TOURINAKTIV,
                     ersatzfilialnr = :d->ERSATZFILIALNR where current of CUpdate7;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate7" ) ) != IS_OK )
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



/* TourSperre: Select *********************************************************/



/* TourSperre: Other **********************************************************/



