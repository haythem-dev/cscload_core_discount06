#include <stdio.h>
#include <string.h>
#include "artcodes.h"

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


/*** AatartSel_Preferred (Bevorzugten Artikelcode lesen) *******************/ 

int kscartSel_Preferred(artcodesS *d, char *error_msg)
{
	static int fst = 1;
	EXEC SQL BEGIN DECLARE SECTION;
	artcodesS   *a;
	EXEC SQL END DECLARE SECTION;

	a = d;

	if (fst) /* beim ersten mal deklarieren */
	{
		fst = 0;
	
		strcpy(str,"select ");
		strcat(str,"ARTICLE_CODE, ");
		strcat(str,"CODE_TYPE ");
		strcat(str,"from ");
		strcat(str,"articlecodes ");
		strcat(str,"where articleno = ? ");
		strcat(str,"and preferred_flag = '1' ");
		EXEC SQL PREPARE dec_preferred FROM :str;
		if (sqlca.sqlcode < 0 )
		{
			fst = 1;
			sprintf(error_msg, " kscartSel_Preferred: declare dec_preferred %ld %ld %s",
					sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
			return -1;
		}
		EXEC SQL declare Sel_preferred cursor for dec_preferred;
	}
	EXEC SQL open Sel_preferred using :a->ARTICLENO;

	EXEC SQL fetch Sel_preferred into :a->ARTICLE_CODE,:a->CODE_TYPE;
	if (sqlca.sqlcode < 0 )
	{
		fst = 1;
		sprintf(error_msg, " kscartSel_Preferred: fetch Sel_preferred %ld %ld %s",
					sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
		EXEC SQL close Sel_preferred;
		return -1;
	}
	else if (sqlca.sqlcode == SQLNOTFOUND)
	{
		a->ARTICLE_CODE[0] = '\0';
		a->CODE_TYPE = 0; 
		return 1;
	}

	return 0;
}

/*** kscartSel_NoByCode (Artikelnr aus Artikelcode lesen) *******************/ 

int kscartSel_NoByCode(artcodesS *d, char *error_msg)
{
static int fst = 1;
EXEC SQL BEGIN DECLARE SECTION;
artcodesS   *a;
EXEC SQL END DECLARE SECTION;

a = d;

	if (fst) /* beim ersten mal deklarieren */
	{
		fst = 0;
	
		strcpy(str,"select ");
		strcat(str,"ARTICLENO, ");
		strcat(str,"CODE_TYPE ");
		strcat(str,"from ");
		strcat(str,"articlecodes ");
		strcat(str,"where article_code = ? ");
		EXEC SQL PREPARE dec_code FROM :str;
		if (sqlca.sqlcode < 0 )
		{
			fst = 1;
			sprintf(error_msg, " kscartSel_NoByCode: declare dec_code %ld %ld %s",
					sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
			return -1;
		}
		EXEC SQL declare Sel_code cursor for dec_code;
	}
	EXEC SQL open Sel_code using :a->ARTICLE_CODE;

	EXEC SQL fetch Sel_code into :a->ARTICLENO,:a->CODE_TYPE;
	if (sqlca.sqlcode < 0 )
	{
		fst = 1;
		sprintf(error_msg, " kscartSel_NoByCode: fetch Sel_code %ld %ld %s",
					sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
		EXEC SQL close Sel_preferred;
		return -1;
	}
	else if (sqlca.sqlcode == SQLNOTFOUND)
	{
		a->ARTICLENO = 0;
		a->CODE_TYPE = 0; 
		return 1;
	}

	return 0;
}
