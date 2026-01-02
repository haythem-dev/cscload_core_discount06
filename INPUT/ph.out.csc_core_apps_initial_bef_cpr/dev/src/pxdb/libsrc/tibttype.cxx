#include <stdio.h>
#include <string.h>
#include "pxdbfunc.h"
#include <ndefs.h>
#include <tibttype.h>

/*-------------------------------------------------------------------*/

extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
int pxIBTTypeStartBrowse(struct tIBTTYPE* record)
{
	EXEC SQL BEGIN DECLARE SECTION;
	char sql[1024];
	EXEC SQL END   DECLARE SECTION;

    UNUSED(record);

	functionnr = F_IBTTYPE*10+F_StartBrowse;

	sprintf(sql, "SELECT ibttypeid, ibttypename, purchaserelevancemode FROM ibttype;" );

	EXEC SQL PREPARE ibttype_browse_stmt from :sql;

	EXEC SQL DECLARE ibttype_browse_cur CURSOR WITH HOLD FOR ibttype_browse_stmt;
	
	EXEC SQL OPEN ibttype_browse_cur;


	if (SQLCODE == 0)        return 0;
	if (SQLCODE == 100)      return cDBXR_NOTFOUND;
	return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
int pxIBTTypeGetNext(struct tIBTTYPE* record)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct tIBTTYPE* recordp;
	EXEC SQL END   DECLARE SECTION;

	functionnr = F_IBTTYPE*10+F_GetNext;
	recordp = record;

	EXEC SQL FETCH ibttype_browse_cur INTO
		:recordp->IBTTypeId,
		:recordp->Name,
		:recordp->PurchaseRelevanceMode;

	if (SQLCODE == 0)    return 0;
	if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
	return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
int pxIBTTypeEndBrowse()
{
	functionnr = F_IBTTYPE*10+F_EndBrowse;

	EXEC SQL CLOSE ibttype_browse_cur;
	EXEC SQL FREE ibttype_browse_stmt;
	return 0;
}
/*-------------------------------------------------------------------*/
