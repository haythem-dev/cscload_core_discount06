/******************************************************************************/
/*                                                                            */
/* header  : ServiceMember.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:34 2022                                         */
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
#include "serviceorder.h"

/* ServiceMember: Select ******************************************************/

/* ServiceMember::SelList *****************************************************/

retClient Servicemember_SelList(servicememberS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Servicemember_SelList";
    exec sql begin declare section;
    servicememberS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList0 cursor with hold for
                  select services.service_no,
                     services.name,
                     services.servicetypeno
                from SERVICES
                  where Services.servicetypeno	 =	:d->SERVICETYPENO	
                        order by Services.name;
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
    exec sql fetch CSelList0 into :d->SERVICE_NO,
                     :d->NAME,
                     :d->SERVICETYPENO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ServiceMember: Insert ******************************************************/



/* ServiceMember: Update ******************************************************/



/* ServiceMember: Select ******************************************************/



/* ServiceMember: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ServiceOrder.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 14:01:35 2022                                         */
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
#include "serviceorder.h"

/* ServiceOrder: Select *******************************************************/

/* ServiceOrder::SelType ******************************************************/

retClient Serviceorder_SelType(serviceorderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Serviceorder_SelType";
    exec sql begin declare section;
    serviceorderS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select servicetypes.servicetypeno,
                     servicetypes.name,
                     servicetypes.order_type
                into :d->SERVICETYPENO,
                     :d->NAME,
                     :d->ORDER_TYPE
                from SERVICETYPES
              where ServiceTypes.order_type	 =	:d->ORDER_TYPE;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ServiceOrder: Insert *******************************************************/



/* ServiceOrder: Update *******************************************************/



/* ServiceOrder: Select *******************************************************/



/* ServiceOrder: Other ********************************************************/



