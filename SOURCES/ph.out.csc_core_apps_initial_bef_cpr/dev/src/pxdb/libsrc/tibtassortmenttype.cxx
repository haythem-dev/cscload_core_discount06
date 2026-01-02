#include <stddef.h>
#include <stdio.h>
#include <pxrecord.h>
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tibtassortmenttype.h"
#include <pxenv.h>
#include <keys.h>
#include "pxdatetime.h"

extern int  functionnr;

#define UNUSED(x) (void)(x)
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
int pxIBTAssortmentTypeStartBrowse
(
     struct tIBTASSORTMENTTYPE* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
#ifdef MCtibtassortmenttype
    struct C_IBTASSORTMENTTYPE * recordp;
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_IBTASSORTMENTTYPE*10+F_StartBrowse;
#ifdef MCtibtassortmenttype
    recordp = (struct C_IBTASSORTMENTTYPE *) record;
#else
    UNUSED(record);
#endif

    if (!(sizeof(struct C_IBTASSORTMENTTYPE) == sizeof(struct tIBTASSORTMENTTYPE)))
       return cDBXR_DEFINITION;


#ifdef MCtibtassortmenttype
    strcpy(matchcode,recordp->MCttaxrates);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        IBTASSORTMENTTYPE_LISTE
    from IBTASSORTMENTTYPE
    DWtibtassortmenttype
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        IBTASSORTMENTTYPE_LISTE
    from IBTASSORTMENTTYPE
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL OPEN C0;
          break;
       default:
          EXEC SQL OPEN C1;
          break;
    }
    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
int pxIBTAssortmentTypeGetNext
(
    struct tIBTASSORTMENTTYPE * record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_IBTASSORTMENTTYPE * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_IBTASSORTMENTTYPE*10+F_GetNext;
    recordp = (struct C_IBTASSORTMENTTYPE*) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into IBTASSORTMENTTYPE_ZEIGER(recordp);
          break;
       default:
          EXEC SQL FETCH C1
          into IBTASSORTMENTTYPE_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
int pxIBTAssortmentTypeEndBrowse
(
    int browseid
)
{
    functionnr = F_TAXRATES*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}

int pxIBTAssortmentTypeRead( struct tIBTASSORTMENTTYPE* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
	struct C_IBTASSORTMENTTYPE* recordp;
	char query[2048] = {' '};
    EXEC SQL END DECLARE SECTION;	
	
	recordp = (struct C_IBTASSORTMENTTYPE*) record;	
		
	sprintf( query,
		"select c.ibtassortmenttypeid, c.ibtcustomersonly, c.ibtperiodneeded "
		"from ibtassortmenttype c "
		"where c.ibtassortmenttypeid=?" );

	EXEC SQL PREPARE pxibtassortmenttyperead_stmt FROM :query;
	EXEC SQL DECLARE pxibtassortmenttyperead_cur CURSOR WITH HOLD FOR pxibtassortmenttyperead_stmt;
	EXEC SQL OPEN pxibtassortmenttyperead_cur USING :recordp->IBTASSORTMENTTYPEID;

	switch( SQLCODE )
	{
		case 0:
			break;
		case 100:
			return cDBXR_NOTFOUND;	
		default:
			return cDBXR_IOERROR;
	}

	EXEC SQL FETCH pxibtassortmenttyperead_cur INTO
		:recordp->IBTASSORTMENTTYPEID,
		:recordp->IBTCUSTOMERSONLY,
		:recordp->IBTPERIODNEEDED;

	switch( SQLCODE )
	{
		case 0:
			break;
		case 100:
			EXEC SQL CLOSE pxibtassortmenttyperead_cur;
			EXEC SQL FREE pxibtbrancharticleconfigread_stmt;	
			return cDBXR_ENDOFDATA;
		default:
			EXEC SQL CLOSE pxibtbrancharticleconfigread_cur;
			EXEC SQL FREE pxibtassortmenttyperead_stmt;	
			return cDBXR_IOERROR;
	}		

	EXEC SQL CLOSE pxibtbrancharticleconfigread_cur;
	EXEC SQL FREE pxibtassortmenttyperead_stmt;	
	return 0;
}
