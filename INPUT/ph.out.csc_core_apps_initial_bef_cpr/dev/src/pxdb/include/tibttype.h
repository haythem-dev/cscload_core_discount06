#ifndef GUARD_IBTTYPE_H
#define GUARD_IBTTYPE_H

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the ibttype table                                */
/*----------------------------------------------------------------------------*/
enum tCRSID_IBTTYPE
{
	cCRSIBTTYPE_Default = 1
};

/*----------------------------------------------------------------------------*/
/*  ibttype Table                                                             */
/*----------------------------------------------------------------------------*/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tIBTTYPE
{
	short	IBTTypeId;
	char	Name[20+1];
	short	PurchaseRelevanceMode;
};

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/*----------------------------------------------------------------------------*/
/* forward declarations for pxverbund                                         */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

int pxIBTTypeStartBrowse(struct tIBTTYPE* record);
int pxIBTTypeGetNext(struct tIBTTYPE* record);
int pxIBTTypeEndBrowse();

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/

#endif   // GUARD_IBTTYPE_H

/*----------------------------------------------------------------------------*/
