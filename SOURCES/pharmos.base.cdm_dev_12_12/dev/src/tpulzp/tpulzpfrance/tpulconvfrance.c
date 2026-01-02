/******************************************************************************/
/*     Hauptmodul: tpulzpfrance                                               */
/*         Source: tpulconfrance.c                                            */
/*          Autor: R. Raab                                                    */
/*       Erstellt: 05.05.2006                                                 */
/*        Sprache: C/Esql-C                                                   */
/*        Erzeugt: basierend auf tpulzentpfl                                  */
/*        Aufgabe: db-selection auf cobol-satzauslegung konvertieren          */
/*                                                                            */
/******************************************************************************/


/*** INCLUDE ******************************************************************/

 #include <stdio.h>
 #include <string.h>
 #include "tpulconvfrance.h"

/*** DEFINE *******************************************************************/

 #define NONE            "0"
 #define VICHY           "B"
 #define BOUHON          "C"
 #define MVDA            "D"
 #define BUECHER         "E"
 #define ROC             "A"
 #define KUEHL8          "1"
 #define KUEHL20         "2"
 #define KUEHL25         "3"
 #define KUEHLKETTE      "4"
 #define HERSTELLDATUM   "2"
 #define VERFALLDATUM    "1"
 #define STD_VOLUME      "00500"
 #define COMPTANT		 "A"
 #define NI_COMPTANT	 "B"

/*** MACRO ********************************************************************/

 #define ASSERT(_x_, _y_) *_x_ = atoi(_y_) ? 'J' : 'N';
 #define CONV(_a_, _b_, _c_, _d_) memcpy( _a_, Rbuendig( _b_, &des[_c_] ), _d_ );
 #define CONVB(_a_, _b_, _c_, _d_) if ( *_b_ == ' ' ){ *_b_ = 'N';} memcpy( _a_, Rbuendig( _b_, &des[_c_] ), _d_ );
 #define CHECK(_x_) (bool)*_x_== '0' ? FALSE : TRUE

/*** public *******************************************************************/

/*** mAssert Funktion ***************************************************************************/

char* mAssert (char *x, char *y)
{
        if (!strcmp(x, "J"))
           return ("J");
        else if (!strcmp( x,"N"))
           return ("N");
        else if (!strcmp( x,""))
           return (y);

return (x);

}

/* Aufbereitung double-Werte als String f¸r CONV-Makro */
 void DoubleToString (double source, int vorkomma, int nachkomma)
 {
	int length = vorkomma + nachkomma + 1 + 1; /* 1 Byte f¸r's Komma, 1 Byte f¸r's Line-End */

	char format[20];
	sprintf(format, "%c-%d.%df", '%', length-1, nachkomma);
	
	sprintf(m_String, format, source);
	m_String[length - 1] = '\0';
 }

/* Aufbereitung long-Werte als String f¸r CONV-Makro */
 void LongToString (long source)
 {
	char format[20];
	sprintf(format, "%c-11d", '%');
	
	sprintf(m_String, format, source);
	m_String[10] = '\0';
 }

/* Jahrhundert bei Datumswerten abschneiden (DEZAP nur 6-stellig) */
 long CutCentury (long source)
 {
	 while (source >= 1000000)
		 source -= 1000000;

	 return source;
 }

 /* Blanks am Ende eines Strings eliminieren */
 int Trim (char *s)
 {
	 int i;
	 
	 for (i = strlen(s)-1; i >= 0; i--)
	 {
		 if (s[i] != ' ')
		 {
			 break;
		 }
	 }

	 s[i+1] = '\0';
 
	 return i;
 }

 /* Klein- in Groﬂbuchstaben umwandeln */
 void Upper (char *s)
 {
	for (int i = 0; i < strlen(s); i++)
	{
		/* Funktion wird derzeit nur f¸r HBMERK genutzt und dort ist im EkZdp keine Eingabe von ‰/ˆ/¸/ﬂ mˆglich ---> keine Sonderbehandlung nˆtig */
		if ((s[i] >= 97 && s[i] <= 122))
		{
			s[i]-=32;
		}
	}
 }

 /* nicht-numerische Werte eines Strings eliminieren */
 void DiscardNotNumerics (char *s)
 {
	int j = 0;

	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			m_String[j] = s[i];
			j++;
		}
	}

	m_String[j] = '\0';
 }

 int GetUmlaut ( int Sign, char *Conv )
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
	else if ( Sign == 223 )
		strcpy ( Conv, "ss" );
	else
		return 0;

	return 1;
 }

 void ConvertUmlaute ( unsigned char *strOrig, char *strConv )
 {
	char temp[3];

	int iOrig;
	int iConv = 0;
	
	for ( iOrig = 0; iOrig < (int) strlen ((char *) strOrig); iOrig++ )
	{
		memset ( temp, '\0', 3 );
		
		if ( GetUmlaut ( strOrig[iOrig], temp ) == 1 )
		{		
			strConv[iConv] = temp [0];
			iConv++;
			strConv[iConv] = temp [1];
		}
		else
		{
			strConv[iConv] = strOrig[iOrig];
		}
		iConv++;
	}
 }

void ConvertDate ( long datum, char *s )
{
	int iTag, iMonat, iJahr;
									/* z.B. datum = 20060510 */
	iJahr = datum / 10000;			/* z.B. 2006 */
	datum-=(iJahr*10000);			/* z.B. 0510 */
	iMonat = datum / 100;			/* z.B. 05 */
	datum-=(iMonat*100);			/* z.B. 10 */
	iTag = datum;					/* z.B. 10 */

	sprintf(s, "%2.2d/%2.2d/%4.4d", iTag, iMonat, iJahr);
}
