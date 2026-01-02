#include <stdio.h>
#include <string.h>
#include "promotions.h"

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

#define NOT_FOUND        1
#define FILE_NOT_FOUND   1
#define ERROR           -1
#define WARNING         -2

/*  externeGLOBALE C-VARIABLEN  */

EXEC SQL BEGIN DECLARE SECTION;
char str[2048];
EXEC SQL END DECLARE SECTION;


/*** kscSel_Promotion (Promotion lesen) *******************/ 

int kscSel_Promotion(promotionsS *d, char *error_msg)
{
	static int fst = 1;
	EXEC SQL BEGIN DECLARE SECTION;
	promotionsS *a;
	EXEC SQL END DECLARE SECTION;

	a = d;

	if (fst) /* beim ersten mal deklarieren */
	{
		fst = 0;
	
		strcpy(str,"select ");
		strcat(str,"NAME ");
		strcat(str,"from ");
		strcat(str,"promotions ");
		strcat(str,"where PROMOTION_NO = ? ");
		EXEC SQL PREPARE dec_promotion FROM :str;
		if (sqlca.sqlcode < 0 )
		{
			fst = 1;
			sprintf(error_msg, " kscSel_Promotion: declare dec_promotion %ld %ld %s",
					sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
			return -1;
		}
	EXEC SQL declare Sel_promotion cursor for dec_promotion;
	}
	EXEC SQL open Sel_promotion using :a->PROMOTION_NO;

	EXEC SQL fetch Sel_promotion into :a->NAME;
	if (sqlca.sqlcode < 0 )
	{
		fst = 1;
		sprintf(error_msg, " kscSel_Promotion: fetch Sel_promotion %ld %ld %s",
					sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
		EXEC SQL close Sel_preferred;
		return -1;
	}
	else if (sqlca.sqlcode == SQLNOTFOUND)
	{
		a->NAME[0] = '\0';
		return 1;
	}

	return 0;
}
