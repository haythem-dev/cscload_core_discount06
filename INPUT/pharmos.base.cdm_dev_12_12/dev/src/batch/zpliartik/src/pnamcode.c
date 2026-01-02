
/* ---------------------------------------------------------------------- *
 *                            pnamcode.c                                  *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Code-Tabelle fuer A00ONAM                             *
 *                  laut IFA                                              *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 26.10.00                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

#include <string.h>
#include "pnamcode.h"


void Upper (unsigned char *s)
{
	int i;
	for (i = 0; i < (int) strlen( (char *) s); i++)
	{
		/* ä/ö/ü/ß nicht möglich -> muss vorher umgewandelt werden */
		if ((s[i] >= 97 && s[i] <= 122))
		{
			s[i]-=32;
		}
	}
}

int GetUmlaut ( int Sign, char * Conv )
{
	if ( Sign == 196 )
		strcpy ( Conv, "AE" );
	else if ( Sign == 214 )
		strcpy ( Conv, "OE" );
	else if ( Sign == 220 )
		strcpy ( Conv, "UE" );
	else if ( Sign == 228 )
		strcpy ( Conv, "ae" );
	else if ( Sign == 246 )
		strcpy ( Conv, "oe" );
	else if ( Sign == 252 )
		strcpy ( Conv, "ue" );
	else if ( (Sign >= 192 && Sign <= 195) || (Sign >= 197 && Sign <= 198))
	{
		strcpy ( Conv, "A" );
		return 1;
	}
	else if ( Sign == 199 )
	{
		strcpy ( Conv, "C" );
		return 1;
	}
	else if ( Sign >= 200 && Sign <= 203 )
	{
		strcpy ( Conv, "E" );
		return 1;
	}
	else if ( Sign >= 204 && Sign <= 207 )
	{
		strcpy ( Conv, "I" );
		return 1;
	}
	else if ( (Sign >= 210 && Sign <= 213) || Sign == 176 || Sign == 186 )
	{
		strcpy ( Conv, "O" );
		return 1;
	}
	else if ( Sign >= 217 && Sign <= 219 )
	{
		strcpy ( Conv, "U" );
		return 1;
	}
	else if ( (Sign >= 224 && Sign <= 227) || (Sign >= 229 && Sign <= 230))
	{
		strcpy ( Conv, "a" );
		return 1;
	}
	else if ( Sign == 231 )
	{
		strcpy ( Conv, "c" );
		return 1;
	}
	else if ( Sign >= 232 && Sign <= 235 )
	{
		strcpy ( Conv, "e" );
		return 1;
	}
	else if ( Sign >= 236 && Sign <= 239 )
	{
		strcpy ( Conv, "i" );
		return 1;
	}
	else if ( Sign >= 242 && Sign <= 245 )
	{
		strcpy ( Conv, "o" );
		return 1;
	}
	else if ( Sign >= 249 && Sign <= 251 )
	{
		strcpy ( Conv, "u" );
		return 1;
	}
	else if ( Sign == 39 || Sign == 21)
	{
		strcpy ( Conv, " " );
		return 1;
	}
	else
		return 0;

	return 2;
}

void ConvertUmlaute ( unsigned char *strOrig, char * strConv )
{
	char temp[3];
	int ret;

	int iOrig;
	int iConv = 0;
	
	for ( iOrig = 0; iOrig < (int) strlen ((char *) strOrig); iOrig++ )
	{
		memset ( temp, '\0', 3 );
		
		ret = GetUmlaut ( strOrig[iOrig], temp );

		if ( ret == 2 )
		{		
			strConv[iConv] = temp [0];
			iConv++;
			strConv[iConv] = temp [1];
		}
		else if ( ret == 1 )
		{
			strConv[iConv] = temp [0];
		}
		else
		{
			strConv[iConv] = strOrig[iOrig];
		}
		iConv++;
	}
	strConv[iConv] = '\0';

	Upper(strConv);
}
