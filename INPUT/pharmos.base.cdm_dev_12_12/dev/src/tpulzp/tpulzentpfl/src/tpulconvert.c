/******************************************************************************/
/*     Hauptmodul: tpulzentpfl                                                */
/*         Source: tpulconvert.c                                              */
/*          Autor: A. Schmidt-Rehschuh                                        */
/*       Erstellt: 02.04.1998                                                 */
/*        Sprache: C/Esql-C                                                   */
/*        Erzeugt: manuell                                                    */
/*        Aufgabe: db-selection auf cobol-satzauslegung konvertieren          */
/*                                                                            */
/******************************************************************************/


/*** INCLUDE ******************************************************************/

 #include <stdio.h>
 #include <math.h>
 #include <string.h>
 #include <stdlib.h>

 #include "dezap.h"
/* #include "dezapean.h" */
 #include "dezapdksoa.h"
 #include "dezapdkris.h"
 #include "dezapdkean.h"
 #include "dezapdkwgr.h"
 #include "dezapdkiwg.h"
 #include "dezapdktgr.h"
/* #include "dezapdkbgr.h" */
 #include "dezapdkrgr.h"
 #include "dezapdkzab.h"
/* #include "dezapdkwir.h" */
 #include "dezapdklif.h"
 #include "dezapdkatx.h"
 #include "dezapdkcrr.h"
 #include "dezapdkrab.h"
 #include "dezapdkaff.h"
 #include "dezapdkste.h"
/* #include "dezapdkgal.h"
 #include "dezapdkgah.h" */
 #include "dezapdklid.h"
 #include "dezapdkegr.h"
 #include "dezapdkral.h"
 #include "dezapdkser.h"
 #include "dezapdkrpg.h"
 #include "dezapdkazb.h"
/* #include "dezapdkgfg.h" */
 #include "dezapdkaco.h"
 #include "dezapdrram.h"
 #include "dezapdkmrs.h"
 #include "dezapdkghz.h"
 #include "dezapdepau.h"
 #include "dezapdkkgr.h"
 #include "dezapdkmvs.h"
/* #include "dezapdkllv.h" */
 #include "dezapdklkr.h"
 #include "dezapdklkz.h"
 #include "dezapdkfok.h"
 #include "dezapdkrbf.h"
 #include "dezapdksps.h"
 #include "dezapdkaua.h"
 #include "dezapdkpro.h"
 #include "dezapdkain.h"

/*  #include "dezapzep.h" */

 #include "tpulzentpfl.h"
 #include "struct.h"
 #include "cdb.h"
 #include "logfile.h"
 #include "allgemein.h"

 #include "conv.h"

 #include "tpulconvert.h"

 #include <voodoo_table_header/zartwg.h>
 #include <voodoo_table_header/carticlecodes.h>
 #include <voodoo_table_header/herstellersalescondition.h>
 #include <voodoo_table_header/zartsekb.h>
 #include <voodoo_table_header/cdeposittypes.h>
 #include <voodoo_table_header/zartfeb2.h>
 #include <voodoo_table_header/csafetydatasheet.h>
 #include <voodoo_table_header/carticleext.h>
 #include <voodoo_table_header/zautidemsperre.h>
 /* #include "cgibatchentry.h" */
 #include <voodoo_table_header/artve.h>
 #include <voodoo_table_header/herstel.h>
 #include <voodoo_table_header/herstel_dispo.h>
 #include <voodoo_table_header/ean.h>
 #include <voodoo_table_header/zartprei.h>
 #include <voodoo_table_header/zartikel.h>
 #include <voodoo_table_header/zartaustria.h>
 #include <voodoo_table_header/zartcroatia.h>
 #include <voodoo_table_header/zartbulgaria.h>
 #include <voodoo_table_header/zartserbia.h>
 #include <voodoo_table_header/zdkwgr.h>
 #include <voodoo_table_header/artkatg.h>
 #include <voodoo_table_header/zdktgr.h>
/*  #include "zdkbtm.h" */
 #include <voodoo_table_header/zdkwir.h>
 #include <voodoo_table_header/carticletext.h>
 #include <voodoo_table_header/zchargenrueckruf.h>
 #include <voodoo_table_header/cdiscount.h>
 #include <voodoo_table_header/zartswitzerland.h>
 #include <voodoo_table_header/carticlelang.h>
 #include <voodoo_table_header/cartcompack.h>
 #include <voodoo_table_header/ccpvalidityperiod.h>
 #include <voodoo_table_header/cdiscgrp.h>
/* #include "cgaloart.h"
 #include "cgalonam.h"
 #include "cgalocom.h" */
 #include <voodoo_table_header/zartfrance.h>
 #include <voodoo_table_header/zartverk.h>
 #include <voodoo_table_header/cpharmgrp.h>
 #include <voodoo_table_header/zrabgrp.h>
 #include <voodoo_table_header/zzahlbed.h>
 #include <voodoo_table_header/cdisclist.h>
 #include <voodoo_table_header/cservices.h>
 #include <voodoo_table_header/cdiscgrpmem.h>
 #include <voodoo_table_header/cdiscmodel.h>
 #include <voodoo_table_header/cmonthdiscsort.h>
 #include <voodoo_table_header/chighpaymtargetfee.h>
 #include <voodoo_table_header/ccustomergroup.h>
 #include <voodoo_table_header/cordertype.h>
 #include <voodoo_table_header/cmonthvirtsort.h>
/* #include "ccustservices.h" */
 #include <voodoo_table_header/cstoragecriteria.h>
 #include <voodoo_table_header/cintrastatcountry.h>
 #include <voodoo_table_header/cformtypes.h>
 #include <voodoo_table_header/cdiscform.h>
 #include <voodoo_table_header/cshipper.h>
 #include <voodoo_table_header/cpromotions.h>
 #include <voodoo_table_header/cregisters.h>
 #include <voodoo_table_header/cbaselistarticles.h>

/*** DEFINE *******************************************************************/

 #define SATZART_ARTIKEL "00"
 #define SATZART_DKSOA   "03"
 #define SATZART_DKRIS   "08"
 #define SATZART_DKEAN   "09"
/* #define SATZART_DKGFG   "10" */
 #define SATZART_DKAFF   "11"
 #define SATZART_DKEGR   "12"
 #define SATZART_DKSTE   "13"
 #define SATZART_DKWGR   "15"
 #define SATZART_DKIWG   "16"
 #define SATZART_DKTGR   "17"
/* #define SATZART_DKBGR   "18" */
/* #define SATZART_DKWIR   "19" */
 #define SATZART_DKLIF   "20"
 #define SATZART_DKATX   "21"
 #define SATZART_DKCRR   "22"
/* #define SATZART_DKGAL   "23"
   #define SATZART_DKGAH   "24" */
 #define SATZART_DKLID   "25"
 #define SATZART_DKRGR   "26"
 #define SATZART_DKZAB   "27"
 #define SATZART_DKRAB   "28"
 #define SATZART_DKRAL   "29"
 #define SATZART_DKSER   "30"
 #define SATZART_DKRPG   "31"
 #define SATZART_DKAZB   "33"
 #define SATZART_DKACO   "34"
 #define SATZART_DRRAM   "35"
 #define SATZART_DKMRS   "36"
 #define SATZART_DKGHZ   "37"
 #define SATZART_DEPAU   "39"
 #define SATZART_DKKGR   "42"
 #define SATZART_DKMVS   "45"
/* #define SATZART_DKLLV   "46" */
 #define SATZART_DKRBF   "47"
 #define SATZART_DKLKR   "48"
 #define SATZART_DKLKZ   "49"
 #define SATZART_DKFOK   "51"
 #define SATZART_DKSPS   "52"
 #define SATZART_DKAUA   "53"
 #define SATZART_DKPRO   "54"
 #define SATZART_DKAIN   "55"
 #define NONE            "0"
 #define KUEHL8          "1"
 #define KUEHL20         "2"
 #define KUEHL25         "3"
 #define KUEHLKETTE      "4"
 #define HERSTELLDATUM   "2"
 #define VERFALLDATUM    "1"
 #define STD_VOLUME      "00500"
 #define COMPTANT		 "A"
 #define NI_COMPTANT	 "B"

/*** DECLARATION **************************************************************/

 static char *GetPacketSize( const dezapzartikelSTR *a, char *spBuf );
 long		  GetVolume( const dezapzartikelSTR *a );
 static char *GetUnit( const char *spValue, char *spBuf );
 static char *GetCompare( const char *spValue, const char *spBuf );
 static char *GetUnwholesome( const dezapzartikelSTR *a, const dezapcsafetydatasheetSTR *s, char *spBuf );
 static char *GetInflammable( const dezapzartikelSTR *a, const dezapcsafetydatasheetSTR *s, char *spBuf );

/*** MACRO ********************************************************************/

 /*fix for TRUE and FALSE (aix knows true / false, solaris doesn't)*/
 #ifndef TRUE
 #define TRUE 1
 #endif
 
 #ifndef FALSE
 #define FALSE 0
 #endif

 /*still using a macro out of layziness (don't want to rewrite 400+ macros)*/
 #define CONV(_a_, _b_, _c_, _d_) convert_format(_a_, _b_, &des[_c_], _d_);
 #define CONVB(_a_, _b_, _c_, _d_) if ( *_b_ == ' ' ){ *_b_ = 'N';} memcpy( _a_, Rbuendig( _b_, &des[_c_] ), _d_ );
 

 
/*** privat *******************************************************************/
/*** ASSERT(former assert macro) **********************************************/
/*** caller is responsible to offer \0-terminated non-null char pointer       */
static void ASSERT(char* dest, const char* flag)
{
	/*see atoi definition*/
	if (atoi(flag))
	{
		/*same as "*dest" - more readable */
		dest[0] = 'J';
	}
	else
	{
		dest[0] = 'N';
	}
}

/*** CHECK(former check macro) **********************************************************/
 static bool CHECK(const char* flag)
 {
	if ('1' == *flag)
	{
		return TRUE;
	}
	return FALSE;
 }
/*** GET-PACKET-SIZE **********************************************************/

 static char *GetPacketSize( const dezapzartikelSTR *a, char *spBuf )
 {
   sprintf( spBuf, "%0*d", L_DEZAP_ZAPAPCK, atoi( a->EINHEIT ) );
   return spBuf;
 }

/*** GET-VOLUME ***************************************************************/

 long GetVolume( const dezapzartikelSTR *a )
 {
   unsigned long iVol;

   iVol = ((a->LAENGE * a->BREITE * a->HOEHE) + 500) / 1000; 

   /* so war's fr¸her (ohne Rundung)  
   iVol = (a->LAENGE * a->BREITE * a->HOEHE) / 1000; */

   if (iVol < 1)
   {
		iVol = atoi(STD_VOLUME);
   }
   else if (iVol > 99999)
   {
        iVol = 99999;
   }

   return iVol;
 }

/*** GET-UNIT *****************************************************************/

 static char *GetUnit( const char *spValue, char *spBuf )
 {
   sprintf( spBuf, "%*s", L_DEZAP_ZAPEINH, spValue );
   return spBuf;
 }

/*** GET-COMPARE **************************************************************/

 static char *GetCompare( const char *spValue, const char *spBuf )
 {
    /*returns addess to temporary - circumvented by static*/
	 static char szReturn[2] = {0};

    /*only first byte is set*/
    if ( *spValue == *spBuf )
		szReturn[0] = '1';
    else
		szReturn[0] = '0';

	return szReturn;
}

/*** GET-UNWHOLESOME **********************************************************/

 static char *GetUnwholesome( const dezapzartikelSTR *a, const dezapcsafetydatasheetSTR *s, char *spBuf )
 {
   if ( CHECK( a->GS_SEHRGIFTIG ) )
      strcpy( spBuf, "T+" );
   else if ( CHECK( a->GS_GIFTIG ) )
      strcpy( spBuf, "T " );
   else if ( CHECK( a->GS_GESUNDHSCH ) )
      strcpy( spBuf, "XN" );
   else if ( CHECK( a->GS_REIZEND ) )
      strcpy( spBuf, "XI" );
   else if ( CHECK( a->GS_UMWELT ) )            /* hajo: neu: Peetz 28.11.02 */
      strcpy( spBuf, "N " );
   else if ( CHECK( a->GS_SVORSLAGERN ) )       /* hajo: vertauscht mit GS_VORSLAGERN: Peetz 28.11.02 */
      strcpy( spBuf, "SV" );
   else if ( CHECK( a->GS_VORSLAGERN ) )        /* hajo: vertauscht mit GS_SVORSLAGERN: Peetz 28.11.02 */
      strcpy( spBuf, "V " );
   else if ( s->PICTOGRAM06_FLAG == 1 )         /* RR: ab hier zus‰tzliche Checks auf Flags in csafetydatasheet */
      strcpy( spBuf, "T+" );
   else if ( s->PICTOGRAM08_FLAG == 1 )         
      strcpy( spBuf, "XN" );
   else if ( s->PICTOGRAM07_FLAG == 1 )         
      strcpy( spBuf, "XI" );
   else if ( s->PICTOGRAM09_FLAG == 1 )         
      strcpy( spBuf, "N " );
   else
      strcpy( spBuf, "00" );

   return spBuf;
 }

/*** GET-INFLAMMABLE **********************************************************/

 static char *GetInflammable( const dezapzartikelSTR *a, const dezapcsafetydatasheetSTR *s, char *spBuf )
 {
   if ( CHECK( a->GS_EXPLOSION ) )
      strcpy( spBuf, "E " );
   else if ( CHECK( a->GS_HOCHENTZ ) )
      strcpy( spBuf, "F+" );
   else if ( CHECK( a->GS_LEICHTENTZ ) )
      strcpy( spBuf, "F " );
   else if ( CHECK( a->GS_AETZEND ) )
      strcpy( spBuf, "C " );
   else if ( CHECK( a->GS_BRAND ) )
      strcpy( spBuf, "O " );
   else if ( CHECK( a->GS_LICHTGESCH ) )
      strcpy( spBuf, "L " );
   else if ( s->PICTOGRAM02_FLAG == 1 )         /* RR: ab hier zus‰tzliche Checks auf Flags in csafetydatasheet */
      strcpy( spBuf, "F+" );
   else if ( s->PICTOGRAM01_FLAG == 1 || s->PICTOGRAM04_FLAG == 1)
      strcpy( spBuf, "E " );
   else if ( s->PICTOGRAM03_FLAG == 1 )         
      strcpy( spBuf, "O " );
   else if ( s->PICTOGRAM05_FLAG == 1 )         
      strcpy( spBuf, "C " );
   else
      strcpy( spBuf, "00" );

   return spBuf;
 }

/*** GET-LIGHT ****************************************************************

 static char *GetLight( const dezapzartikelSTR *a, char *spBuf )
 {
    *spBuf = '0';
    if ( a->GS_BRAND[0] == '1' ||
         a->GS_EXPLOSION[0] == '1' ||
         a->GS_HOCHENTZ[0] == '1' ||
         a->GS_LEICHTENTZ[0] == '1' ||
         a->GS_AETZEND[0] == '1' )
    {
         *spBuf = '1';
    }

    *(spBuf+1) = '\0';
    return spBuf;
 } */

/*** GET-ADDITIONAL-PAYMENT ***************************************************/

 static char *GetAdditionalPayment( const char *spPayment, char *spBuf )
 {
	if ( !memcmp( spPayment, "1000000", 7 ) )
		*spBuf = '0';
	else if ( !memcmp( spPayment, "2000000", 7 ) )
		*spBuf = ' ';
	else if ( !memcmp( spPayment, "3000000", 7 ) )
		*spBuf = '1';
	else if ( !memcmp( spPayment, "4000000", 7 ) )  /* 3 and 4 are equal! */
		*spBuf = '1';
	else if ( !memcmp( spPayment, "5000000", 7 ) )
		*spBuf = '2';
	else if ( !memcmp( spPayment, "6000000", 7 ) )
		*spBuf = '3';
	else if ( !memcmp( spPayment, "7000000", 7 ) )
		*spBuf = '4';
	else if ( !memcmp( spPayment, "8000000", 7 ) )
		*spBuf = '5';
	else if ( !memcmp( spPayment, "9000000", 7 ) )
		*spBuf = 'P';
	else
		*spBuf = 'K';

	*(spBuf+1) = '\0';
	return spBuf;
 }

/*** GET-PPE *******************************************************************/

 static char *GetPpe( const char *spPpe, char *spBuf )
 {
	if ( *spPpe == '1' )
		*spBuf = 'I';
    else if ( *spPpe == '2' )	/* kann eigentlich nicht sein, weil das Feld im EkZdp nur eine Checkbox ist */
        *spBuf = 'B';
    else
        *spBuf = 'N';

    *(spBuf+1) = '\0';
    return spBuf;
 }

/*** GET-PRISMA WEEK ***********************************************************/

 static char *GetPrismaWeek( long iWeek, char *spBuf )
 {
    if ( iWeek == 0 )
		strcpy( spBuf, "  " );
    else
        sprintf( spBuf, "%02ld", iWeek );

   return spBuf;
 }

/*** GET-STREET *******************************************************************/

 static char *GetStreet( int mode, const dezapherstelSTR *a, char *spBuf )
 {
    if (mode == 1)
	{
        int i, j, k = 0;
        char szBuf[10] = {0}; 
        char syBuf[10] = {0};

		/* erstmal die L‰nge von Hausnr. + Zusatz ermitteln */
		strcpy(szBuf, a->HAUSNR_VON);
		Trim(szBuf);
		i = strlen(szBuf);
		strcpy(szBuf+i, a->HAUSNR_VON_ZUS);
		Trim(szBuf);
		i = strlen(szBuf);

		strcpy(syBuf, a->HAUSNR_BIS);
		Trim(syBuf);
		k = strlen(syBuf);
		strcpy(syBuf+k, a->HAUSNR_BIS_ZUS);
		Trim(syBuf);
		k = strlen(syBuf);

		if (strlen(a->STRASSE) <= 30)
		{
            strcpy(spBuf, a->STRASSE);
		}
		else
		{
			strncpy(spBuf, a->STRASSE, 30);
			memset(spBuf+30, '\0', 1);
		}

		Trim(spBuf);
		j = strlen(spBuf);

		/* Hausnr. von und Zusatz von sollen auf jeden Fall mit rein */
		if (j >= (30-i))
		{
			j = 29 - i; 
		}

		*(spBuf+j) = ' ';
		j++;
		strcpy(spBuf+j, szBuf);
        
		/* wenn Platz ist, auch noch Hausnr. bis und Zusatz bis */
		j = strlen(spBuf);

		if ((j <= (29-k)) && (k > 0))
		{
			strcpy(spBuf+j, "-");
			j++;
			strcpy(spBuf+j, syBuf);
		}
	} else if (mode == 2)
	{
		strcpy (spBuf, "POSTFACH ");
		strcpy (spBuf+9, a->POST_FACH);
	}
	
    *(spBuf+30) = '\0';
    return spBuf;
 }

 static char *GetTel( char *spVorwahl, char *spNummer, char *spBuf )
 {
	int i,j = 0;

	/*intentionally not copying \0 - we want all 16 bytes*/
	strncpy(spBuf, spVorwahl, strlen(spVorwahl));
	Trim(spBuf);
	i = strlen(spBuf);

	Trim(spNummer);

	/* Telefonnummer aufbereiten: nur numerische Werte, alles ab '/' eliminieren (auﬂer bei Vorwahl 00xx) */
	for (j=0; j<15; j++)
	{
		if (i == 15)
		{
			break;
		}

		if ((spNummer[j] >= '0') && (spNummer[j] <= '9'))
		{
			spBuf[i] = spNummer[j];
			i++;
		}
		else if ((spNummer[j] == '/' && strncmp(spVorwahl,"00",2) != 0) || (spNummer[j] == '\0'))
		{
			break;
		}
	}
	
	spBuf[15] = '\0';
	
    return spBuf;

 }
 
 static bool IsStringAllSpaces(const char* str)
{
	return (strspn(str, " ") ==	strlen(str));
}
 
/*** public *******************************************************************/

/*** IsCountry **********************************************************/
bool IsCountry(const char* countryCode, const char* const countryCodeToCompair)
{
	return (0 == strncmp(countryCode, countryCodeToCompair, strlen(countryCodeToCompair)) );
}

/*** CONVERT-MANUFACTURER **********************************************************/

 void ConvertManufacturer( dezapdklifO *d, dezapherstelSTR *a, struct AUFB des[], parameter *p )
 {
   /*tailing bytes after telecommunication numbers (syBuf is used for them) should be spaces*/
   char syBuf[16] = {0};
   memset(syBuf, ' ', 15);
      
   char szBuf[31] = {0};

   char chnr[6] = {0};
   char cplz[8] = {0};

   CONV( d->ZAPSA20, SATZART_DKLIF, DEZAPDKLIFZAPSA20, L_DEZAPDKLIF_ZAPSA20 );

   sprintf(chnr, "%5.5ld", a->HERSTELLER_NR);
   CONV( d->ZAP20HNR, chnr, DEZAPDKLIFZAP20HNR, L_DEZAPDKLIF_ZAP20HNR );

   strncpy(d->ZAP20KUBZ, a->SORTIERNAME, strlen(a->SORTIERNAME));
   strncpy(d->ZAP20HNAME1, a->NAME, strlen(a->NAME));
   strncpy(d->ZAP20HNAME2, a->ZUSATZ_NAME, strlen(a->ZUSATZ_NAME));

/* jetzt kommt die komplizierte Aufbereitung Straﬂe / PLZ / Ort */
   if (atoi(a->PLZ))
   {
	   CONV( d->ZAP20HORT, a->ORT, DEZAPDKLIFZAP20HORT, L_DEZAPDKLIF_ZAP20HORT );

	   /* ist nˆtig, weil PLZ links- oder rechtsb¸ndig drinstehen kann */
	   sprintf(cplz, "%7.7d", atoi(a->PLZ));
	   CONV( d->ZAP20HPLZ, cplz, DEZAPDKLIFZAP20HPLZ, L_DEZAPDKLIF_ZAP20HPLZ );

   	   strcpy (m_String, GetStreet( 1, a, szBuf ));
	   strncpy(d->ZAP20HSTR, m_String, strlen(szBuf));
   } else if (atoi(a->PLZ2))
   {
	   CONV( d->ZAP20HORT, a->POSTFACHORT, DEZAPDKLIFZAP20HORT, L_DEZAPDKLIF_ZAP20HORT );

	   /* ist nˆtig, weil PLZ links- oder rechtsb¸ndig drinstehen kann */
	   sprintf(cplz, "%7.7d", atoi(a->PLZ2));
	   CONV( d->ZAP20HPLZ, cplz, DEZAPDKLIFZAP20HPLZ, L_DEZAPDKLIF_ZAP20HPLZ );

   	   strcpy (m_String, GetStreet( 2, a, szBuf ));
	   strncpy(d->ZAP20HSTR, m_String, strlen(szBuf));
   } else if (atoi(a->PLZ_GROSSKUNDE))
   {
	   CONV( d->ZAP20HORT, a->POSTFACHORT, DEZAPDKLIFZAP20HORT, L_DEZAPDKLIF_ZAP20HORT );
	   
	   /* ist nˆtig, weil PLZ links- oder rechtsb¸ndig drinstehen kann */
	   sprintf(cplz, "%7.7d", atoi(a->PLZ_GROSSKUNDE));
	   CONV( d->ZAP20HPLZ, cplz, DEZAPDKLIFZAP20HPLZ, L_DEZAPDKLIF_ZAP20HPLZ );
   } else
   {
	   strncpy(d->ZAP20HPLZ, "0000000", L_DEZAPDKLIF_ZAP20HPLZ );

	   Trim(a->STRASSE);
	   Trim(a->POST_FACH);

	   if (strlen(a->STRASSE) > 0)
	   {
			CONV( d->ZAP20HORT, a->ORT, DEZAPDKLIFZAP20HORT, L_DEZAPDKLIF_ZAP20HORT );

   			strcpy (m_String, GetStreet( 1, a, szBuf ));
			strncpy(d->ZAP20HSTR, m_String, strlen(szBuf));
	   } else if (strlen(a->POST_FACH) > 0)
	   {
	     	CONV( d->ZAP20HORT, a->POSTFACHORT, DEZAPDKLIFZAP20HORT, L_DEZAPDKLIF_ZAP20HORT );

			strcpy (m_String, GetStreet( 2, a, szBuf ));
			strncpy(d->ZAP20HSTR, m_String, strlen(szBuf));
	   }
   }

   /* und jetzt m¸ssen noch Telefon- und Faxnummer zusammengemantscht werden */
   /* Note: third parameter is modified in GetTel, so return value is not needed */
   
   /* Spezialfall: nur die Vorwahl ist gepflegt (kommt vereinzelt vor) */
   if ( !IsStringAllSpaces(a->VORWAHL) && IsStringAllSpaces(a->TELEFON_NR) )
   {
   		strncpy(syBuf, a->VORWAHL, strlen(a->VORWAHL));
		CONV( d->ZAP20HTELNR, syBuf, DEZAPDKLIFZAP20HTELNR, strlen(syBuf) );
   }
   else if (! (IsStringAllSpaces(a->VORWAHL) && IsStringAllSpaces(a->TELEFON_NR)) )
   {
		GetTel(a->VORWAHL, a->TELEFON_NR, syBuf);
		CONV( d->ZAP20HTELNR, syBuf, DEZAPDKLIFZAP20HTELNR, strlen(syBuf) );
   }
   else
   {
		/*don't call convert, if there is nothing to be done - just add empty field*/
		strncpy(d->ZAP20HTELNR, syBuf, 14);
   }
   
   /* clear buffer */
   memset(syBuf, ' ', 15);

   /* Spezialfall: nur die Vorwahl ist gepflegt (kommt vereinzelt vor) */
   if ( !IsStringAllSpaces(a->VORWAHL_TELEFAX) && IsStringAllSpaces(a->FAX_NR) )
   {
   		strncpy(syBuf, a->VORWAHL_TELEFAX, strlen(a->VORWAHL_TELEFAX));
		CONV( d->ZAP20HTFAX, syBuf, DEZAPDKLIFZAP20HTFAX, strlen(syBuf) );
   }
   else if (! (IsStringAllSpaces(a->VORWAHL_TELEFAX) && IsStringAllSpaces(a->FAX_NR)) )
   {
		GetTel(a->VORWAHL_TELEFAX, a->FAX_NR, syBuf);
		CONV( d->ZAP20HTFAX, syBuf, DEZAPDKLIFZAP20HTFAX, strlen(syBuf) );
   }
   else
   {
		/*don't call convert, if there is nothing to be done - just add empty field*/
		strncpy(d->ZAP20HTFAX, syBuf, 14);
   }
   
   
   CONV( d->ZAP20LKZ, a->LANDESKUERZEL, DEZAPDKLIFZAP20LKZ, L_DEZAPDKLIF_ZAP20LKZ );
   CONV( d->ZAP20SHZDP, a->ZENTRALPPELIST, DEZAPDKLIFZAP20SHZDP, L_DEZAPDKLIF_ZAP20SHZDP );
   CONV( d->ZAP20PCODE, a->HERSTELLER_CODE, DEZAPDKLIFZAP20PCODE, L_DEZAPDKLIF_ZAP20PCODE );

   CONV( d->ZAP20HBMERK, a->BEMERKUNGEN, DEZAPDKLIFZAP20HBMERK, L_DEZAPDKLIF_ZAP20HBMERK );

   /* Kleinbuchstaben in Bemerkung in Groﬂbuchstaben ‰ndern */
   Upper(d->ZAP20HBMERK);

   /* erstmal Preislistenfeld sauber initialisieren */
   strncpy(d->ZAP20PREISL, "0000", L_DEZAPDKLIF_ZAP20PREISL );

   /* in Kroatien Feld verwenden fuer KZ Rechnungssplitt */
   if (IsCountry(p->Kuerzel, "HR"))
   {
		LongToStringWithLength((long)a->RECHNUNGSSPLITT, L_DEZAPDKLIF_ZAP20PREISL);
		CONV( d->ZAP20PREISL, m_String, DEZAPDKLIFZAP20PREISL, L_DEZAPDKLIF_ZAP20PREISL );
   }
   else
   {
        char plm1[2] = {0};
        char plm2[2] = {0};
        char plj1[2] = {0};
        char plj2[2] = {0};


		/* ansonsten Preisliste versorgen, wenn Bemerkung mit nn.nn beginnt */
		strncpy(plm1, a->BEMERKUNGEN, 1);
		strncpy(plm2, a->BEMERKUNGEN+1, 1);
		strncpy(plj1, a->BEMERKUNGEN+3, 1);
		strncpy(plj2, a->BEMERKUNGEN+4, 1);

		if ((strncmp(a->BEMERKUNGEN+2, ".", 1) == 0) && 
				(atoi(plm1) || (plm1[0] == '0')) &&
				(atoi(plm2) || (plm2[0] == '0')) &&
				(atoi(plj1) || (plj1[0] == '0')) &&
				(atoi(plj2) || (plj2[0] == '0')))
		{
			strncpy(d->ZAP20PREISL, plm1, 1);
			strncpy(d->ZAP20PREISL+1, plm2, 1);
			strncpy(d->ZAP20PREISL+2, plj1, 1);
			strncpy(d->ZAP20PREISL+3, plj2, 1);
		}
   }

   LongToString(a->DATUM_LOESCH);
   ASSERT( d->ZAP20HLOEKZ, m_String );

   /* auch Retourenadresse versorgen */
   strncpy(d->ZAP20RNAME1, a->R_NAME, strlen(a->R_NAME));
   strncpy(d->ZAP20RORT, a->R_ORT, strlen(a->R_ORT));
   strncpy(d->ZAP20RSTR, a->R_STRASSE, strlen(a->R_STRASSE));

   /* neu 13.05.15: 2. Name versorgen */
   strncpy(d->ZAP20RNAME2, a->R_NAME2, strlen(a->R_NAME2));

   /* ist nˆtig, weil PLZ links- oder rechtsb¸ndig drinstehen kann */
   sprintf(cplz, "%7.7d", atoi(a->R_PLZ));
   CONV( d->ZAP20RPLZ, cplz, DEZAPDKLIFZAP20RPLZ, L_DEZAPDKLIF_ZAP20RPLZ );

	DoubleToString(a->ADM_PAUSCHALE, L_DEZAPDKLIF_ZAP20PAPA, N_DEZAPDKLIF_ZAP20PAPA);
	AvoidOverflow( m_String, des[DEZAPDKLIFZAP20PAPA].laenge); 
	CONV( d->ZAP20PAPA, m_String, DEZAPDKLIFZAP20PAPA, L_DEZAPDKLIF_ZAP20PAPA );

   return;
 }

/*** CONVERT-SALES-CONDITION **********************************************************/

 void ConvertSalesCondition( dezapdklifO *d, dezaphsalescondSTR *a, struct AUFB des[], parameter *p, int i  )
 {
	LongToString(a->ARTID);
    CONV( d->ZAP20PA09TAB[i].ZAP20P09ART, m_String, DEZAPDKLIFZAP20P09TAB + (ANZ_DKLIF_P09_FELDER_PRO_ELEMENT * i), L_DEZAPDKLIF_ZAP20P09ART );

	DoubleToString(atof(a->SALESCONDITIONVALUE), L_DEZAPDKLIF_ZAP20P09WERT, N_DEZAPDKLIF_ZAP20P09WERT);
	AvoidOverflow( m_String, des[DEZAPDKLIFZAP20P09TAB + (ANZ_DKLIF_P09_FELDER_PRO_ELEMENT * i) + 1].laenge); 
	CONV( d->ZAP20PA09TAB[i].ZAP20P09WERT, m_String, DEZAPDKLIFZAP20P09TAB + (ANZ_DKLIF_P09_FELDER_PRO_ELEMENT * i) + 1, L_DEZAPDKLIF_ZAP20P09WERT );

/*	printf("\n%d: %3.3s %5.5s", i, d->ZAP20PA09TAB[i].ZAP20P09ART, d->ZAP20PA09TAB[i].ZAP20P09WERT); */
 }

 /*** CONVERT-MANUFACTURER-ARTICLE **********************************************************/

 void ConvertManufacturerArticle( dezapO *d, dezapherstelSTR *a, struct AUFB des[] )
 {
   char szBuf[2] = {0};

   CONV( d->ZAPSEK, GetPpe( a->PPE_KENNZ, szBuf ), DEZAPZAPSEK, L_DEZAP_ZAPSEK );
   return;
 }


/*** CONVERT-ARTICLE **********************************************************/

 void ConvertArticle( dezapO *d, dezapzartikelSTR *a, const dezapcsafetydatasheetSTR *s, struct AUFB des[], parameter *p )
 {
   char szBuf[36] = {0};
   int hts;
   const char *fun = "ConvertArticle";

   CONV( d->ZAPSA, SATZART_ARTIKEL, DEZAPZAPSA, L_DEZAP_ZAPSA );
   CONV( d->ZAPKUBZ, a->ARTIKEL_MC, DEZAPZAPKUBZ, L_DEZAP_ZAPKUBZ );

   LongToString(a->ARTIKEL_NR);
   CONV( d->ZAPPZN, m_String, DEZAPZAPPZN, L_DEZAP_ZAPPZN );

   LongToString(a->HERSTELLER_NR);
   CONV( d->ZAPHLNR, m_String, DEZAPZAPHLNR, L_DEZAP_ZAPHLNR );

   CONV( d->ZAPANRH, a->ARTIKEL_NR_HERST, DEZAPZAPANRH, L_DEZAP_ZAPANRH );

   /* MAM war das alte (2-stellige) Feld und ist jetzt nur noch Filler */
   /* und jetzt gibt es daf¸r das neue Feld PROZ1 */
/* CONV( d->ZAPMAM, m_String, DEZAPZAPMAM, L_DEZAP_ZAPMAM ); */
/* CONV( d->ZAPFILL3, "  ", DEZAPZAPFILL3, L_DEZAP_ZAPFILL3 ); */
   LongToString(a->WARNTAGEVORVERF);
   CONV( d->ZAPPROZ1, m_String, DEZAPZAPPROZ1, L_DEZAP_ZAPPROZ1 );

   LongToString(a->MINDESTBEZUG);
   CONV( d->ZAPMAMN, m_String, DEZAPZAPMAMN, L_DEZAP_ZAPMAMN );

   LongToString(a->VPE_PHARMOS);
   CONV( d->ZAPVE, m_String, DEZAPZAPVE, L_DEZAP_ZAPVE );

   ASSERT( d->ZAPLOE, a->ARTIKEL_GELOESCHT );
   ASSERT( d->ZAPSPERR, a->ARTIKEL_GESPERRT );

   LongToString(CutCentury(a->DATUM_IFAAENDER));
   CONV( d->ZAPABDA, m_String, DEZAPZAPABDA, L_DEZAP_ZAPABDA );     /* 0JJMMTT DON'T FORGET! */

   LongToString(CutCentury(a->DATUM_AH));
   CONV( d->ZAPAHDAT, m_String, DEZAPZAPAHDAT, L_DEZAP_ZAPAHDAT );  /* 0JJMMTT DON'T FORGET! */

   DoubleToString(a->HERST_PROZENT, L_ZARTIKEL_HERST_PROZENT, N_ZARTIKEL_HERST_PROZENT);
   AvoidOverflow( m_String, des[DEZAPZAPPRZUAB].laenge); 
   CONV( d->ZAPPRZUAB, m_String, DEZAPZAPPRZUAB, L_DEZAP_ZAPPRZUAB );

   CONV( d->ZAPGESKL, GetUnwholesome( a, s, szBuf ), DEZAPZAPGESKL, L_DEZAP_ZAPGESKL );
   CONV( d->ZAPFEUKL, GetInflammable( a, s, szBuf ), DEZAPZAPFEUKL, L_DEZAP_ZAPFEUKL );

   /* Wirkstoffgruppe ab 18.05.14 nicht mehr aus zartikel, sondern aus zartwg
   CONV( d->ZAPWIRK, a->WIRKSTOFF_NR, DEZAPZAPWIRK, L_DEZAP_ZAPWIRK ); */

   DoubleToString(a->FESTBETRAG1, L_ZARTIKEL_FESTBETRAG1, N_ZARTIKEL_FESTBETRAG1);
   hts = AvoidOverflow( m_String, des[DEZAPZAPFEPR].laenge); 
   CONV( d->ZAPFEPR, m_String, DEZAPZAPFEPR, L_DEZAP_ZAPFEPR );

	if (hts >= 10)
	{
		WriteLog( fun, 100, "Artikel %d hat Festpreis >= 1.000.000!", a->ARTIKEL_NR ); 
		CONV( d->ZAPHTFEPR, "0", DEZAPZAPHTFEPR, L_DEZAP_ZAPHTFEPR ); 
	}
	else
	{
		LongToString(hts);
		CONV( d->ZAPHTFEPR, m_String, DEZAPZAPHTFEPR, L_DEZAP_ZAPHTFEPR );
	}

   CONVB( d->ZAPMEDK, a->FESTBREGEL, DEZAPZAPMEDK, L_DEZAP_ZAPMEDK );
   CONV( d->ZAPKAT4, a->KATALOG, DEZAPZAPKAT4, L_DEZAP_ZAPKAT4 );
   CONVB( d->ZAPGREPG, a->SONDERGROSSO, DEZAPZAPGREPG, L_DEZAP_ZAPGREPG );
   
   CONV( d->ZAPINFGR, GetPrismaWeek( a->PRISMAEWOCHE, szBuf ), DEZAPZAPINFGR, L_DEZAP_ZAPINFGR );

   /* andere Versorgung f¸r Ivrylab */
   	if (IsCountry(p->Kuerzel, "F") &&
	    p->Prewhole == 1)
	{
        char cINFGR[3] = {0};

		sprintf( cINFGR, "%02d", a->BUSINESSTYPENO );
		CONV( d->ZAPINFGR, cINFGR, DEZAPZAPINFGR, L_DEZAP_ZAPINFGR );
	}
   
   ASSERT( d->ZAPKOLO, a->PREIS0ARTIKEL ); /* geaendert */

   LongToString(a->ERSATZ_NR);
   CONV( d->ZAPAANR, m_String, DEZAPZAPAANR, L_DEZAP_ZAPAANR );

   CONV( d->ZAPNRTI, "0000000", DEZAPZAPNRTI, L_DEZAP_ZAPNRTI ); 

   /* RR 16.02.12: Filler anderweitig verwendet */
   /* RR 28.10.04: Filler statt AKBEZ (wie in Pharmos auch) */
   /* CONV( d->ZAPFILL2, "            ", DEZAPZAPFILL2, L_DEZAP_ZAPFILL2 ); */
   /* CONV( d->ZAPAKBEZ, a->ARTIKEL_MC, DEZAPZAPAKBEZ, L_DEZAP_ZAPAKBEZ );*/

   CONV( d->ZAPEINH, GetUnit( a->EINHEIT, szBuf ), DEZAPZAPEINH, L_DEZAP_ZAPEINH ); /* rechtsbuendig! */
   CONV( d->ZAPABEZ, a->ARTIKEL_NAME, DEZAPZAPABEZ, L_DEZAP_ZAPABEZ ); /* letzen 4 stellen */
   CONV( d->ZAPDRFO, a->DARREICHFORM, DEZAPZAPDRFO, L_DEZAP_ZAPDRFO );
   CONV( d->ZAPAPCK, GetPacketSize( a, szBuf ), DEZAPZAPAPCK, L_DEZAP_ZAPAPCK );

   LongToString(a->LAENGE);
   CONV( d->ZAPLGE, m_String, DEZAPZAPLGE, L_DEZAP_ZAPLGE );

   LongToString(a->BREITE);
   CONV( d->ZAPBRE, m_String, DEZAPZAPBRE, L_DEZAP_ZAPBRE );

   LongToString(a->HOEHE);
   CONV( d->ZAPHOE, m_String, DEZAPZAPHOE, L_DEZAP_ZAPHOE );

   LongToString(GetVolume( a ));
   CONV( d->ZAPVOL, m_String, DEZAPZAPVOL, L_DEZAP_ZAPVOL );

   LongToString(a->GEWICHT);
   CONV( d->ZAPGEW, m_String, DEZAPZAPGEW, L_DEZAP_ZAPGEW );

   CONV( d->ZAPBUEN, "000", DEZAPZAPBUEN, L_DEZAP_ZAPBUEN );
   CONV( d->ZAPMINM, "000", DEZAPZAPMINM, L_DEZAP_ZAPMINM );

   DoubleToString(a->PERSONALRABATT, L_ZARTIKEL_PERSONALRABATT, N_ZARTIKEL_PERSONALRABATT);
   AvoidOverflow( m_String, des[DEZAPZAPZURA].laenge); 
   CONV( d->ZAPZURA, m_String, DEZAPZAPZURA, L_DEZAP_ZAPZURA );
   
   CONV( d->ZAPKRABHV, a->RABATTFAEHIG, DEZAPZAPKRABHV, L_DEZAP_ZAPKRABHV );

   LongToString(a->LAUFZEITMONATE);
   CONV( d->ZAPLZEIT, m_String, DEZAPZAPLZEIT, L_DEZAP_ZAPLZEIT );

   if(d->ZAPGESKL[0] == 'T')
   {
                d->ZAPGIFT1[0] = 'J';
                d->ZAPGIFT2[0] = 'J';
                d->ZAPGIFT3[0] = 'J';
   }
   else if(!strncmp(d->ZAPGESKL,"XN",L_DEZAP_ZAPGESKL))
   {
                d->ZAPGIFT1[0] = 'J';
                d->ZAPGIFT2[0] = 'J';
                d->ZAPGIFT3[0] = 'N';
   }
   else if(!strncmp(d->ZAPGESKL,"XI",L_DEZAP_ZAPGESKL))
   {
                d->ZAPGIFT1[0] = 'J';
                d->ZAPGIFT2[0] = 'N';
                d->ZAPGIFT3[0] = 'N';
   }
   else
   {
                d->ZAPGIFT1[0] = 'N';
                d->ZAPGIFT2[0] = 'N';
                d->ZAPGIFT3[0] = 'N';
   }
   /*
   ASSERT( d->ZAPGIFT1, a->GS_SEHRGIFTIG );
   ASSERT( d->ZAPGIFT2, a->GS_GIFTIG );
   ASSERT( d->ZAPGIFT3, a->GS_GESUNDHSCH );
   */
   ASSERT( d->ZAPREZ, a->REZEPTPFL );
   ASSERT( d->ZAPAPO, a->APOTHEKENPFL );
   ASSERT( d->ZAPTAX, a->TAXPFL );
   ASSERT( d->ZAPOPI, a->BTM );
   ASSERT( d->ZAPTIER, a->TIERARZNEI );

   ASSERT( d->ZAPVBED, a->VERTRBIND_IFA );
   ASSERT( d->ZAPVBA, GetCompare( a->VERTRBIND, "A" ) );
   ASSERT( d->ZAPVB1, GetCompare( a->VERTRBIND, "B" ) );
   ASSERT( d->ZAPVB2, GetCompare( a->VERTRBIND, "C" ) );
   ASSERT( d->ZAPVB3, GetCompare( a->VERTRBIND, "D" ) );
   ASSERT( d->ZAPVB4, GetCompare( a->VERTRBIND, "E" ) );
   ASSERT( d->ZAPVBB, GetCompare( a->VERTRBIND, "F" ) );
   ASSERT( d->ZAPVBC, GetCompare( a->VERTRBIND, "G" ) );

   ASSERT( d->ZAPSEKB, NONE );                  /* ungekl‰rt */
   ASSERT( d->ZAPNF, a->ERSATZ_NR_AKTIV );
   ASSERT( d->ZAPPZNS, NONE );

// LongToString(a->DATUM_AH);
   LongToStringDateCheck(a->DATUM_AH, p->lDateTo);
   ASSERT( d->ZAPAHDL, m_String );

   // Feld Auslauf generell f¸llen, wird dann im PSA425 nur f¸r ÷sterreich eingespielt
   LongToString(a->DATUM_AV);
   ASSERT( d->ZAPAUSL, m_String );
   // ASSERT( d->ZAPAUSL, NONE );

// LongToString(a->DATUM_RR);
   LongToStringDateCheck(a->DATUM_RR, p->lDateTo);
   ASSERT( d->ZAPRAKT, m_String );

   ASSERT( d->ZAPNAK, NONE );
   ASSERT( d->ZAPNART, a->NETTOARTIKEL );
   ASSERT( d->ZAPK08, GetCompare( a->KUEHLARTIKEL, KUEHL8 ) );
   ASSERT( d->ZAPK20, GetCompare( a->KUEHLARTIKEL, KUEHL20 ) );
   ASSERT( d->ZAPKK, GetCompare( a->KUEHLARTIKEL, KUEHLKETTE ) );
   ASSERT( d->ZAPK25, GetCompare( a->KUEHLARTIKEL, KUEHL25 ) );
   ASSERT( d->ZAPNLH, NONE );

   // setzen NLH auf "J", wenn Datum wieder lieferbar noch nicht erreicht
   // wird dann im PSA410 nur f¸r Deutschland eingespielt
   if ( a->DATUM_LIEFERBAR_AB > p->lDateTo ) 
	   d->ZAPNLH[0] = 'J';
   
   LongToString(a->DATUM_IFALOESCH);
   ASSERT( d->ZAPNGH, m_String );

   ASSERT( d->ZAPNGR, a->NICHTUEBERGH );
   ASSERT( d->ZAPKLIP, a->KLINIKPACKUNG );
   ASSERT( d->ZAPRESP, a->RETOURENSPERRE );
   ASSERT( d->ZAPMELD, a->MELDEPFL );

   ASSERT( d->ZAPHERD, GetCompare( a->VERFALL, HERSTELLDATUM ) );

   ASSERT( d->ZAPVERD, GetCompare( a->VERFALL, VERFALLDATUM ) );
   ASSERT( d->ZAPVEDM, NONE );
   ASSERT( d->ZAPBBU, a->BESTANDSBUCHUNG );
   ASSERT( d->ZAPBKCA, NONE );
   ASSERT( d->ZAPBKVK, NONE );
   ASSERT( d->ZAPFEUER, NONE );		/* RR 26.08.14: Feld wird im Pharmos aus PA14 gef¸llt und nicht von ZDP ¸bernommen
   ASSERT( d->ZAPFEUER, GetLight( a, szBuf ) ); */
   ASSERT( d->ZAPBKZO, NONE );
   ASSERT( d->ZAPAUTO, NONE );
   ASSERT( d->ZAPDYN, NONE );
   ASSERT( d->ZAPWAKO, NONE );
   ASSERT( d->ZAPHORE, NONE );
   ASSERT( d->ZAPNGF, NONE );

   LongToString(a->DATUM_MWE);
   ASSERT( d->ZAPMWE, m_String );

   ASSERT( d->ZAPAFEPR, NONE );
   ASSERT( d->ZAPNEGA, a->NEGATIVLISTE );
   ASSERT( d->ZAPPOOL, NONE );
   ASSERT( d->ZAPHOME, NONE );
   ASSERT( d->ZAPGSG, NONE );
   ASSERT( d->ZAPLWA, NONE );
   ASSERT( d->ZAPKV, a->NURKVA );
   ASSERT( d->ZAPSKTOF, a->SKONTOFAEHIG );
   ASSERT( d->ZAPPRISMA, NONE );

   CONV( d->ZAPPRISO, a->PRIVATSORTIMENT, DEZAPZAPPRISO, L_DEZAP_ZAPPRISO );
   ASSERT( d->ZAPKBEZU, a->BESTELLSPERRE );
/*
   ASSERT( d->ZAPK25, GetCompare( a->KUEHLARTIKEL, KUEHL25 ) );     nachfragen
   ASSERT( d->ZAPIHNR, NONE );
   ASSERT( d->ZAPIZLA, NONE );
*/

/* *d->ZAPIHNR = ' ';
   *d->ZAPIZLA = ' '; */

   ASSERT( d->ZAPIHNR, a->NIEDRSPANNE_ELAC );
   ASSERT( d->ZAPIZLA, a->NIEDRSPANNE_SONST );

   if (d->ZAPIHNR[0] == 'N')
   {
	   d->ZAPIHNR[0] = ' ';
   }

   if (d->ZAPIZLA[0] == 'N')
   {
	   d->ZAPIZLA[0] = ' ';
   }

   *d->ZAPGEGU = 'N';

   ASSERT( d->ZAPS1, a->SORTIMENT_1 );
   ASSERT( d->ZAPS2, a->SORTIMENT_2 );
   ASSERT( d->ZAPS3, a->SORTIMENT_3 );
   ASSERT( d->ZAPS4, a->SORTIMENT_4 );
   ASSERT( d->ZAPS5, a->SORTIMENT_5 );
   ASSERT( d->ZAPPERF, a->PERF );
   ASSERT( d->ZAPZYTO, a->ZYTOSTATIKA );
   ASSERT( d->ZAPZEKS, a->ZENTR_EKSPERRE );
   ASSERT( d->ZAPTFG, a->TFG );
   ASSERT( d->ZAPSKK, a->SOMMER_KK );
   ASSERT( d->ZAPINFO, NONE );
   ASSERT( d->ZAPKZBUEN, NONE );
   ASSERT( d->ZAPPRISMAE, a->PRISMAEDISK );

/* HAEMOPHILIE setzen, wenn TFG = '2' */
   d->ZAPHAEMO[0] = 'N';

   if (a->TFG[0] == '2')
   {
	   d->ZAPHAEMO[0] = 'J';
   }

   /* neu 11.03.05: Psychotrop gibt's jetzt im zartikel */
   /* ASSERT( d->ZAPPSS, NONE ); */
   strncpy(d->ZAPPSS, a->PSYCHOTROP, 1); /* wird 1:1 ¸bernommen (Werte N/P/T) */

   /* neu 16.07.01 */
   CONV( d->ZAPNEKZ, a->NAHRUNGSERGAENZUNG, DEZAPZAPNEKZ, L_DEZAP_ZAPNEKZ );
   CONV( d->ZAPNEINF, a->NAHRUNGSTEST, DEZAPZAPNEINF, L_DEZAP_ZAPNEINF );

   /* neu 21.11.05 */
   CONV( d->ZAPELEKTRO, a->ELEKTROSCHROTT, DEZAPZAPELEKTRO, L_DEZAP_ZAPELEKTRO );

   /* hajo: neu 16.12.02 */
   /* lt. Raab (12.12.02) wird BSSICHG (1/0) nach ZAP-WART (J/N) abgebildet */
   ASSERT( d->ZAPWART, a->BSSICHG );

   /* RR neu 28.10.04: neue Kennzeichen ARZMI und EKORG, Init von VRIS und MIDAS */
   ASSERT( d->ZAPVRIS, NONE );
   ASSERT( d->ZAPMIDAS, NONE );
   ASSERT( d->ZAPARZMI, a->ARZNEIMITTEL );
   ASSERT( d->ZAPEKORG, a->EKORIGINALHS );

   /* RR neu 19.06.06: neue Kennzeichen */
   ASSERT( d->ZAPMEDGAS, a->MEDIZINISCHE_GASE);
   ASSERT( d->ZAPAMGAURE, a->AMG_AUSNAHMEREG );
   ASSERT( d->ZAPKONTPPE, a->KONTINGENT_PPE );

/* ASSERT( d->ZAPPFLSV, a->PFLSCHUTZ_VERORD ); */
   if(a->PFLSCHUTZ_VERORD[0] == 'E' || 
	  a->PFLSCHUTZ_VERORD[0] == 'J' || 
	  a->PFLSCHUTZ_VERORD[0] == 'R')
     {
	   d->ZAPPFLSV[0] = 'J';
     }
   else
   {
	   d->ZAPPFLSV[0] = 'N';
   }

   /* RR neu 10.11.08: neues Feld */
   LongToString(a->KONSIG_PARTNER_NR);
   CONV( d->ZAPKONSNR, m_String, DEZAPZAPKONSNR, L_DEZAP_ZAPKONSNR );

   /* RR 20.01.09: war bisher im else-Zweig der folgenden if-Anweisung (wg. Versorgung aus zartaustria) */
   CONV( d->ZAPORPA, a->PRODUKTART, DEZAPZAPORPA, L_DEZAP_ZAPORPA );

   /* RR neu 18.05.11: neues Kennzeichen */
   ASSERT( d->ZAPFAELGEF, a->FAELSCH_GEFAHR);

   /* RR neu 18.11.13: neues Kennzeichen + Init eines neuen Feldes */
   LongToString(a->KOSMETIKUM);
   ASSERT( d->ZAPKOSM, m_String);
   d->ZAPELAC[0] = 'N';

   /* RR neu 13.12.13: neues Kennzeichen */
   LongToString(a->BIOSIEGEL);
   ASSERT( d->ZAPEUBIO, m_String);

   /* RR neu 02.04.14: neues Feld */
   LongToString(a->LAGEEMPF);
   CONV( d->ZAPLAGEEMPF, m_String, DEZAPZAPLAGEEMPF, L_DEZAP_ZAPLAGEEMPF );

   /* RR neu 12.10.11: neue Felder */
   LongToString(a->SPANNENCLUSTER);
   CONV( d->ZAPMAM, m_String, DEZAPZAPMAM, L_DEZAP_ZAPMAM );

   DoubleToString(a->AKTIONSGROSSO, L_ZARTIKEL_AKTIONSGROSSO, N_ZARTIKEL_AKTIONSGROSSO);
   AvoidOverflow( m_String, des[DEZAPZAPAGR].laenge); 
   CONV( d->ZAPAGR, m_String, DEZAPZAPAGR, L_DEZAP_ZAPAGR );

   /* RR neu 16.02.12: neues Feld */
   LongToString(a->ARTIKEL_NR_ORIG);
   CONV( d->ZAPORGPZN, m_String, DEZAPZAPORGPZN, L_DEZAP_ZAPORGPZN );

   /* RR neu 16.11.15: 2 neue Felder */
   CONV( d->ZAPUNNR, a->G_UN_NR, DEZAPZAPUNNR, L_DEZAP_ZAPUNNR );
	
   /* erst LGK aus SDB, falls diese nicht gef¸llt, dann berechnete */
   CONV( d->ZAPLGK, a->G_VCI, DEZAPZAPLGK, L_DEZAP_ZAPLGK ); 

   if (strncmp(d->ZAPLGK, "    ", L_DEZAP_ZAPLGK) == 0)
		CONV( d->ZAPLGK, s->CALCSTORAGECLASSID, DEZAPZAPLGK, L_DEZAP_ZAPLGK ); 
      
   /* RR neu 12.02.16: neues Feld */
   LongToString(s->DANGERGOODSTOREROOM);
   CONV( d->ZAPGSRAUM, m_String, DEZAPZAPGSRAUM, L_DEZAP_ZAPGSRAUM );
   
   /* RR 03.03.17: 2 neue Felder + Init eines Feldes */
   LongToString(a->APO_AUTO_FAEHIG_ROWA);
   ASSERT( d->ZAPAAFROW, m_String);

   LongToString(a->APO_AUTO_FAEHIG_KNAPP);
   ASSERT( d->ZAPAAFKNA, m_String);

   d->ZAPGHLGVB[0] = 'N';

   /* RR 31.10.18: neues Feld */
   LongToString(a->FMD_RELEVANT);
   ASSERT( d->ZAPFMDREL, m_String);

   /* RR 22.01.20: neues Feld */
   LongToString(CutCentury(a->DATUM_FMDPFLICHT));
   CONV( d->ZAPSHDAT, m_String, DEZAPZAPSHDAT, L_DEZAP_ZAPSHDAT );

   /* RR 08.12.20: neues Feld */
   CONV( d->ZAPKUEHLKZ, a->KUEHLARTIKEL, DEZAPZAPKUEHLKZ, L_DEZAP_ZAPKUEHLKZ );

   /* RR 20.01.22: 2 neue Felder */
   LongToString(a->CMI_FLAG);
   ASSERT( d->ZAPCMI, m_String);
    
   LongToString(a->SERIAL_NUMBER_TRACKING);
   ASSERT( d->ZAPSNT, m_String);

   /* RR neu 29.11.23: neues Kennzeichen */
   ASSERT( d->ZAPMEDPROD, a->MEDIZINPRODUKT);

   /* ab hier l‰nderspezifisches F¸llen einzelner Felder */
   if (IsCountry(p->Kuerzel, "A"))
   {
		/* in ÷sterreich sind die beiden Ausweichlieferanten vertauscht */
		LongToString(a->AWL1);
		CONV( d->ZAPALNR2, m_String, DEZAPZAPALNR2, L_DEZAP_ZAPALNR2 );

		strncpy( d->ZAPKZAL2, a->AWL_AKTIV, L_DEZAP_ZAPKZAL2 );  

		LongToString(a->AWL2);	
		CONV( d->ZAPALNR1, m_String, DEZAPZAPALNR1, L_DEZAP_ZAPALNR1 );
	 
		ASSERT( d->ZAPKZAL1, NONE );

		/* SIW und ORPA werden aus zartaustria gef¸llt */
   }
   else
   {
		LongToString(a->AWL1);
		CONV( d->ZAPALNR1, m_String, DEZAPZAPALNR1, L_DEZAP_ZAPALNR1 );

		strcpy( d->ZAPKZAL1, a->AWL_AKTIV );  /*z.Zt steht N und J im FELD auf DB (nicht ok) */

		LongToString(a->AWL2);
		CONV( d->ZAPALNR2, m_String, DEZAPZAPALNR2, L_DEZAP_ZAPALNR2 );
		 
		ASSERT( d->ZAPKZAL2, NONE );

		ASSERT( d->ZAPSIW, a->SICHTWAHL );
   }

   /* Zuzahlung und Stammhaus-KZ nur in D */
   if (IsCountry(p->Kuerzel, "D"))
   {
		CONV( d->ZAPZUZA, GetAdditionalPayment( a->ZUZAHLUNG_IFA, szBuf ), DEZAPZAPZUZA, L_DEZAP_ZAPZUZA );

		/* 27.04.21: MVDA-Beschaffungskennzeichen zumindest mal in DEZAP stellen, wird derzeit im PSA425 nicht weiterverarbeitet */
		strncpy( d->ZAPPOOL, a->MVDAARTIKEL, L_DEZAP_ZAPGST );  

		/* hajo: neu 07.07.03 */
	    /* lt. Raab (03.07.03) wird ZENTRALPPELIST nach ZAP-GST abgebildet */
		CONV( d->ZAPGST, a->ZENTRALPPELIST, DEZAPZAPGST, L_DEZAP_ZAPGST );

		/* ZAP-ERSTWERT nur in D aus zartikel versorgen (in F & BG erfolgt das aus der jeweiligen Landestabelle) */
		/* in D nicht mehr aus zartikel 
		DoubleToString(a->ERSTATTBETRAG, L_ZARTIKEL_ERSTATTBETRAG, N_ZARTIKEL_ERSTATTBETRAG); 
		AvoidOverflow( m_String, des[DEZAPZAPERSTWERT].laenge); 
		CONV( d->ZAPERSTWERT, m_String, DEZAPZAPERSTWERT, L_DEZAP_ZAPERSTWERT ); */
   }
   else
   {
		*d->ZAPZUZA = ' ';

		/* wird in Deutschland & Frankreich aus zautidemsperre gef¸llt und in Kroatien aus zartcroatia */
		if (!IsCountry(p->Kuerzel, "HR"))
			ASSERT( d->ZAPPAEND, NONE ); 

		/* Getr‰nkesteuer mit '0' liefern statt mit 'N' */
		strncpy( d->ZAPGST, "0", L_DEZAP_ZAPGST );  
		/* ASSERT( d->ZAPGST, NONE ); */
   }

   return;
 }

/*** CONVERT-PRICE ************************************************************/

void ConvertPrice( dezapO *d, dezapzartpreisSTR *p, struct AUFB des[], parameter *par )
{
	int hts;
	const char *fun = "ConvertPrice";

	DoubleToString(p->AEP, L_ZARTPREIS_AEP, N_ZARTPREIS_AEP);
	hts = AvoidOverflow( m_String, des[DEZAPZAPAEP].laenge); 
	CONV( d->ZAPAEP, m_String, DEZAPZAPAEP, L_DEZAP_ZAPAEP );
  
	if (hts >= 1000)
	{
		WriteLog( fun, 100, "Artikel %d hat AEP >= 100.000.000!", p->ARTIKEL_NR ); 
 		CONV( d->ZAPZMHSAEP, "000", DEZAPZAPZMHSAEP, L_DEZAP_ZAPZMHSAEP ); 
	}
	else 
	{
		LongToString(hts);
		CONV( d->ZAPZMHSAEP, m_String, DEZAPZAPZMHSAEP, L_DEZAP_ZAPZMHSAEP );

		if (hts >= 10)
		{
			WriteLog( fun, 100, "Artikel %d hat AEP >= 1.000.000!", p->ARTIKEL_NR ); 
 			CONV( d->ZAPHTAEP, "0", DEZAPZAPHTAEP, L_DEZAP_ZAPHTAEP ); 
		}
		else
		{
			LongToString(hts);
			CONV( d->ZAPHTAEP, m_String, DEZAPZAPHTAEP, L_DEZAP_ZAPHTAEP );
		}
	}

	/* in der Schweiz den AGP ins AEP-Feld stellen (f¸r Einspielung in DKSOA), weil der im PSA425 sowieso nicht ¸bernommen wird */
	if (IsCountry(par->Kuerzel, "CH") &&
		par->Prewhole == 0)
	{
		DoubleToString(p->AGP, L_ZARTPREIS_AGP, N_ZARTPREIS_AGP);
		hts = AvoidOverflow( m_String, des[DEZAPZAPAEP].laenge); 
		CONV( d->ZAPAEP, m_String, DEZAPZAPAEP, L_DEZAP_ZAPAEP );
  
		if (hts >= 1000)
		{
			WriteLog( fun, 100, "Artikel %d hat AGP >= 100.000.000!", p->ARTIKEL_NR ); 
 			CONV( d->ZAPZMHSAEP, "000", DEZAPZAPZMHSAEP, L_DEZAP_ZAPZMHSAEP ); 
		}
		else 
		{
			LongToString(hts);
			CONV( d->ZAPZMHSAEP, m_String, DEZAPZAPZMHSAEP, L_DEZAP_ZAPZMHSAEP );
		}
	}
	
	/* AVP-Typ versorgen
		0: KEIN AVP VORHANDEN
		1: UNVERBINDL. (D AB 07/13)
		2: VERBINDL. WG. TAXE */
	Runden(&p->AVP, 2); 
	Runden(&p->EAVP, 2); 
	
	if (p->AVP == 0.0)
		d->ZAPAVPTYP[0] = '0';
	else
		d->ZAPAVPTYP[0] = '2';

	/* EAVP statt AVP ans Pharmos schicken, falls nur dieser gef¸llt; AVP-Typ = 1 */
	if (p->AVP == 0.0 && 
		p->EAVP > 0.0)
	{
		p->AVP = p->EAVP;
		d->ZAPAVPTYP[0] = '1';
	}

	DoubleToString(p->AVP, L_ZARTPREIS_AVP, N_ZARTPREIS_AVP);
	hts = AvoidOverflow( m_String, des[DEZAPZAPAVP].laenge); 
    CONV( d->ZAPAVP, m_String, DEZAPZAPAVP, L_DEZAP_ZAPAVP );

	if (hts >= 10)
	{
		WriteLog( fun, 100, "Artikel %d hat AVP >= 1.000.000!", p->ARTIKEL_NR ); 
 		CONV( d->ZAPHTAVP, "0", DEZAPZAPHTAVP, L_DEZAP_ZAPHTAVP ); 
	}
	else
	{
		LongToString(hts);
		CONV( d->ZAPHTAVP, m_String, DEZAPZAPHTAVP, L_DEZAP_ZAPHTAVP );
	}

	DoubleToString(p->GROSSO, L_ZARTPREIS_GROSSO, N_ZARTPREIS_GROSSO);
	hts = AvoidOverflow( m_String, des[DEZAPZAPGEP].laenge); 
    CONV( d->ZAPGEP, m_String, DEZAPZAPGEP, L_DEZAP_ZAPGEP );

	if (hts >= 1000)
	{
		WriteLog( fun, 100, "Artikel %d hat GEP >= 100.000.000!", p->ARTIKEL_NR ); 
 		CONV( d->ZAPZMHSGEP, "000", DEZAPZAPZMHSGEP, L_DEZAP_ZAPZMHSGEP ); 
	}
	else 
	{
		LongToString(hts);
		CONV( d->ZAPZMHSGEP, m_String, DEZAPZAPZMHSGEP, L_DEZAP_ZAPZMHSGEP );

		if (hts >= 10)
		{
			WriteLog( fun, 100, "Artikel %d hat GEP >= 1.000.000!", p->ARTIKEL_NR ); 
 			CONV( d->ZAPHTGEP, "0", DEZAPZAPHTGEP, L_DEZAP_ZAPHTGEP ); 
		}
		else
		{
			LongToString(hts);
			CONV( d->ZAPHTGEP, m_String, DEZAPZAPHTGEP, L_DEZAP_ZAPHTGEP );
		}
	}

/*  CONV( d->ZAPGEPNA, "0000000", DEZAPZAPGEPNA, L_DEZAP_ZAPGEPNA ); <-- Umstellung wegen Segmentation fault auf AIX: */
	LongToString(0);
	CONV( d->ZAPGEPNA, m_String, DEZAPZAPGEPNA, L_DEZAP_ZAPGEPNA );
	
 	CONV( d->ZAPHTGEPNA, "0", DEZAPZAPHTGEPNA, L_DEZAP_ZAPHTGEPNA ); 

	LongToString (p->DISC_DEDUCED_YET);
	ASSERT( d->ZAPABZ130, m_String ); 

	/* ZAP-ERSTWERT nur in D aus zartpreis versorgen (in F & BG erfolgt das aus der jeweiligen Landestabelle) */
	if (IsCountry(par->Kuerzel, "D"))
	{
        /* nur versorgen, wenn Preis nicht schon um den Rabatt reduziert ist */
		if (p->DISC_DEDUCED_YET == 0)
		{
			DoubleToString(p->ERSTATTBETRAG, L_ZARTPREIS_ERSTATTBETRAG, N_ZARTPREIS_ERSTATTBETRAG); 
			AvoidOverflow( m_String, des[DEZAPZAPERSTWERT].laenge); 
			CONV( d->ZAPERSTWERT, m_String, DEZAPZAPERSTWERT, L_DEZAP_ZAPERSTWERT ); 
		}
	}

	/* in Frankreich, Kroatien (ab 02/2012), ÷sterreich (ab 12/2015) & Prewhole Schweiz MWST-Wert unver‰ndert ¸bergeben, nicht auf J/N konvertieren */
	if (IsCountry(par->Kuerzel, "F")  ||
		IsCountry(par->Kuerzel, "HR") ||
		IsCountry(par->Kuerzel, "A") ||
       (IsCountry(par->Kuerzel, "CH") && par->Prewhole == 1))
	{
		CONV( d->ZAPMWST, p->KE_MWST, DEZAPZAPMWST, L_DEZAP_ZAPMWST );
	}
	else
        ASSERT( d->ZAPMWST, p->KE_MWST );

	/* neues Feld ZAP-VAT generell 1:1 aus KE-MWST versorgen; wenn auf Pharmos-Seite alle Zugriffe auf ZAP-MWST auf ZAP-VAT umgestellt sind, kann die obige Abfrage und damit die Versorgung des Feldes entfallen */
	CONV( d->ZAPVAT, p->KE_MWST, DEZAPZAPVAT, L_DEZAP_ZAPVAT );

	return;
 }

/*** CONVERT-DKEAN ************************************************************/

 bool ConvertDkean( dezapeanO *d, dezapeanSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKEAN_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKEAN_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP09TABELLE[i].ZAP09PZN,"       ",L_DEZAPDKEAN_ZAP09PZN) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA09, SATZART_DKEAN, DEZAPDKEANZAPSA09, L_DEZAPDKEAN_ZAPSA09 );
			}

		    LongToString(p->ARTIKEL_NR);
			CONV( d->ZAP09TABELLE[i].ZAP09PZN, m_String, DEZAPDKEANZAP09PZN + (ANZ_DKEAN_FELDER_PRO_ELEMENT * i), L_DEZAPDKEAN_ZAP09PZN );
			strncpy(d->ZAP09TABELLE[i].ZAP09VFIL, "00", 2);

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP09TABELLE[i].ZAP09LOEKZ, "J", DEZAPDKEANZAP09LOEKZ + (ANZ_DKEAN_FELDER_PRO_ELEMENT * i), L_DEZAPDKEAN_ZAP09LOEKZ );
			}
			else
			{
				CONV( d->ZAP09TABELLE[i].ZAP09EAN, p->EAN_NR, DEZAPDKEANZAP09EAN + (ANZ_DKEAN_FELDER_PRO_ELEMENT * i), L_DEZAPDKEAN_ZAP09EAN );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKWGR ************************************************************/

 bool ConvertDkwgr( dezapdkwgrO *d, dezapzdkwgrSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKWGR_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKWGR_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP15TABELLE[i].ZAP15GRUPPE,"     ",L_DEZAPDKWGR_ZAP15GRUPPE) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA15, SATZART_DKWGR, DEZAPDKWGRZAPSA15, L_DEZAPDKWGR_ZAPSA15 );
			}

			CONV( d->ZAP15TABELLE[i].ZAP15GRUPPE, p->WGR_GRUPPE, DEZAPDKWGRZAP15GRUPPE + (ANZ_DKWGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKWGR_ZAP15GRUPPE );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP15TABELLE[i].ZAP15LOEKZ, "J", DEZAPDKWGRZAP15LOEKZ + (ANZ_DKWGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKWGR_ZAP15LOEKZ );
			}
			else
			{
				CONV( d->ZAP15TABELLE[i].ZAP15BEZ, p->WGR_BEZ, DEZAPDKWGRZAP15BEZ + (ANZ_DKWGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKWGR_ZAP15BEZ );
				CONV( d->ZAP15TABELLE[i].ZAP15SKTOF, p->WGR_SKTOF, DEZAPDKWGRZAP15SKTOF + (ANZ_DKWGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKWGR_ZAP15SKTOF );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKIWG ************************************************************/

 bool ConvertDkiwg( dezapdkiwgO *d, dezapzdkiwgSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKIWG_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKIWG_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP16TABELLE[i].ZAP16GRUPPE,"     ",L_DEZAPDKIWG_ZAP16GRUPPE) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA16, SATZART_DKIWG, DEZAPDKIWGZAPSA16, L_DEZAPDKIWG_ZAPSA16 );
			}

			CONV( d->ZAP16TABELLE[i].ZAP16GRUPPE, p->WARENGRUPPE, DEZAPDKIWGZAP16GRUPPE + (ANZ_DKIWG_FELDER_PRO_ELEMENT * i), L_DEZAPDKIWG_ZAP16GRUPPE );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP16TABELLE[i].ZAP16LOEKZ, "J", DEZAPDKIWGZAP16LOEKZ + (ANZ_DKWGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKIWG_ZAP16LOEKZ );
			}
			else
			{
				CONV( d->ZAP16TABELLE[i].ZAP16BEZ, p->BEZEICHNUNG, DEZAPDKIWGZAP16BEZ + (ANZ_DKIWG_FELDER_PRO_ELEMENT * i), L_DEZAPDKIWG_ZAP16BEZ );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKTGR ************************************************************/

 bool ConvertDktgr( dezapdktgrO *d, dezapzdktgrSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKTGR_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKTGR_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP17TABELLE[i].ZAP17GRUPPE,"     ",L_DEZAPDKTGR_ZAP17GRUPPE) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA17, SATZART_DKTGR, DEZAPDKTGRZAPSA17, L_DEZAPDKTGR_ZAPSA17 );
			}

			CONV( d->ZAP17TABELLE[i].ZAP17GRUPPE, p->TGR_GRUPPE, DEZAPDKTGRZAP17GRUPPE + (ANZ_DKTGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKTGR_ZAP17GRUPPE );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP17TABELLE[i].ZAP17LOEKZ, "J", DEZAPDKTGRZAP17LOEKZ + (ANZ_DKTGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKTGR_ZAP17LOEKZ );
			}
			else
			{
				CONV( d->ZAP17TABELLE[i].ZAP17BEZ, p->TGR_BEZ, DEZAPDKTGRZAP17BEZ + (ANZ_DKTGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKTGR_ZAP17BEZ );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKBGR ***********************************************************

 bool ConvertDkbgr( dezapdkbgrO *d, dezapzdkbgrSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKBGR_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKBGR_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP18TABELLE[i].ZAP18GRUPPE,"   ",L_DEZAPDKBGR_ZAP18GRUPPE) || (i == j))
		{
			// beim ersten F¸llen Satzart miteinstellen 
			if (i == 0)
			{
				CONV( d->ZAPSA18, SATZART_DKBGR, DEZAPDKBGRZAPSA18, L_DEZAPDKBGR_ZAPSA18 );
			}

			CONV( d->ZAP18TABELLE[i].ZAP18GRUPPE, p->BTM_GRUPPE, DEZAPDKBGRZAP18GRUPPE + (ANZ_DKBGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKBGR_ZAP18GRUPPE );

			// jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen 
			if ( rc == eof )
			{
 				CONV( d->ZAP18TABELLE[i].ZAP18LOEKZ, "J", DEZAPDKBGRZAP18LOEKZ + (ANZ_DKBGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKBGR_ZAP18LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP18TABELLE[i].ZAP18BEZ, p->BTM_BEZ, DEZAPDKBGRZAP18BEZ + (ANZ_DKBGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKBGR_ZAP18BEZ );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
} */

/*** CONVERT-DKRGR ************************************************************/

 bool ConvertDkrgr( dezapdkrgrO *d, dezapzrabgrpSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKRGR_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKRGR_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP26TABELLE[i].ZAP26GRUPPE,"   ",L_DEZAPDKRGR_ZAP26GRUPPE) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA26, SATZART_DKRGR, DEZAPDKRGRZAPSA26, L_DEZAPDKRGR_ZAPSA26 );
			}

			CONV( d->ZAP26TABELLE[i].ZAP26GRUPPE, p->RABATTGRUPPE, DEZAPDKRGRZAP26GRUPPE + (ANZ_DKRGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKRGR_ZAP26GRUPPE );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP26TABELLE[i].ZAP26LOEKZ, "J", DEZAPDKRGRZAP26LOEKZ + (ANZ_DKRGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKRGR_ZAP26LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP26TABELLE[i].ZAP26BEZ, p->BEZEICHNUNG, DEZAPDKRGRZAP26BEZ + (ANZ_DKRGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKRGR_ZAP26BEZ );
				CONV( d->ZAP26TABELLE[i].ZAP26PRBAS, p->PREIS_BASIS, DEZAPDKRGRZAP26PRBAS + (ANZ_DKRGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKRGR_ZAP26PRBAS );
				CONV( d->ZAP26TABELLE[i].ZAP26RABART, p->RABATTIERUNGSART, DEZAPDKRGRZAP26RABART + (ANZ_DKRGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKRGR_ZAP26RABART );
				ASSERT( d->ZAP26TABELLE[i].ZAP26KEINRAB, p->KEINE_RABATTIERUNG );

				LongToString(p->DRUCK_GEP_AUF_RECHNUNG);
				ASSERT( d->ZAP26TABELLE[i].ZAP26DRGEP, m_String );

				DoubleToString(p->MAXIMUM, L_DEZAPDKRGR_ZAP26MAXIMUM, N_DEZAPDKRGR_ZAP26MAXIMUM);
				AvoidOverflow( m_String, des[DEZAPDKRGRZAP26MAXIMUM].laenge); 
				CONV( d->ZAP26TABELLE[i].ZAP26MAXIMUM, m_String, DEZAPDKRGRZAP26MAXIMUM + (ANZ_DKRGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKRGR_ZAP26MAXIMUM );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKZAB ************************************************************/

 bool ConvertDkzab( dezapdkzabO *d, dezapzzahlbedSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKZAB_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKZAB_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP27TABELLE[i].ZAP27BEDI,"    ",L_DEZAPDKZAB_ZAP27BEDI) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA27, SATZART_DKZAB, DEZAPDKZABZAPSA27, L_DEZAPDKZAB_ZAPSA27 );
			}

			CONV( d->ZAP27TABELLE[i].ZAP27BEDI, p->ZAHLUNGSBEDINGUNG, DEZAPDKZABZAP27BEDI + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27BEDI );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP27TABELLE[i].ZAP27LOEKZ, "J", DEZAPDKZABZAP27LOEKZ + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP27TABELLE[i].ZAP27LST0, p->LSTERMIN_0, DEZAPDKZABZAP27LST0 + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27LST0 );
				CONV( d->ZAP27TABELLE[i].ZAP27LST1, p->LSTERMIN_1, DEZAPDKZABZAP27LST1 + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27LST1 );
				CONV( d->ZAP27TABELLE[i].ZAP27LST2, p->LSTERMIN_2, DEZAPDKZABZAP27LST2 + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27LST2 );
				CONV( d->ZAP27TABELLE[i].ZAP27LST3, p->LSTERMIN_3, DEZAPDKZABZAP27LST3 + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27LST3 );

				DoubleToString(p->SKONTOMONPROZ, L_DEZAPDKZAB_ZAP27SKMP, N_DEZAPDKZAB_ZAP27SKMP);
				AvoidOverflow( m_String, des[DEZAPDKZABZAP27SKMP].laenge); 
				CONV( d->ZAP27TABELLE[i].ZAP27SKMP, m_String, DEZAPDKZABZAP27SKMP + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27SKMP );

				DoubleToString(p->SKONTHALBMONPROZ, L_DEZAPDKZAB_ZAP27SKMP, N_DEZAPDKZAB_ZAP27SKMP);
				AvoidOverflow( m_String, des[DEZAPDKZABZAP27SKHMP].laenge); 
				CONV( d->ZAP27TABELLE[i].ZAP27SKHMP, m_String, DEZAPDKZABZAP27SKHMP + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27SKHMP );

				DoubleToString(p->SKONTDEKADEPROZ, L_DEZAPDKZAB_ZAP27SKMP, N_DEZAPDKZAB_ZAP27SKMP);
				AvoidOverflow( m_String, des[DEZAPDKZABZAP27SDEKA].laenge); 
				CONV( d->ZAP27TABELLE[i].ZAP27SDEKA, m_String, DEZAPDKZABZAP27SDEKA + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27SDEKA );

				DoubleToString(p->SKONTWOCHPROZ, L_DEZAPDKZAB_ZAP27SKWO, N_DEZAPDKZAB_ZAP27SKWO);
				AvoidOverflow( m_String, des[DEZAPDKZABZAP27SKWO].laenge); 
				CONV( d->ZAP27TABELLE[i].ZAP27SKWO, m_String, DEZAPDKZABZAP27SKWO + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27SKWO );

			    LongToString(p->NETTO_TAGE);
				CONV( d->ZAP27TABELLE[i].ZAP27NTAG, m_String, DEZAPDKZABZAP27NTAG + (ANZ_DKZAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKZAB_ZAP27NTAG );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKRAL ************************************************************/

 bool ConvertDkral( dezapdkralO *d, dezapcdisclistSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKRAL_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKRAL_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP29TABELLE[i].ZAP29AART,"  ",L_DEZAPDKRAL_ZAP29AART) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA29, SATZART_DKRAL, DEZAPDKRALZAPSA29, L_DEZAPDKRAL_ZAPSA29 );
			}

			/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
			CONV( d->ZAP29TABELLE[i].ZAP29FIL, "00", DEZAPDKRALZAP29FIL + (ANZ_DKRAL_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAL_ZAP29FIL );

			CONV( d->ZAP29TABELLE[i].ZAP29AART, p->ORDER_TYPE, DEZAPDKRALZAP29AART + (ANZ_DKRAL_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAL_ZAP29AART );
			CONV( d->ZAP29TABELLE[i].ZAP29SUBAA, p->SUB_ORDER_TYPE, DEZAPDKRALZAP29SUBAA + (ANZ_DKRAL_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAL_ZAP29SUBAA );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP29TABELLE[i].ZAP29LOEKZ, "J", DEZAPDKRALZAP29LOEKZ + (ANZ_DKRAL_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAL_ZAP29LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP29TABELLE[i].ZAP29EGR, p->PHARMACYGROUPID, DEZAPDKRALZAP29EGR + (ANZ_DKRAL_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAL_ZAP29EGR );
				CONV( d->ZAP29TABELLE[i].ZAP29ZAHLBED, p->PAYMENT_TERM, DEZAPDKRALZAP29ZAHLBED + (ANZ_DKRAL_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAL_ZAP29ZAHLBED );

				DoubleToString(p->MONTHLY_DISC_PCT, L_DEZAPDKRAL_ZAP29MONRAB, N_DEZAPDKRAL_ZAP29MONRAB);
				AvoidOverflow( m_String, des[DEZAPDKRALZAP29MONRAB].laenge); 
				CONV( d->ZAP29TABELLE[i].ZAP29MONRAB, m_String, DEZAPDKRALZAP29MONRAB + (ANZ_DKRAL_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAL_ZAP29MONRAB );

				LongToString(p->VALUTA_DAYS);
				CONV( d->ZAP29TABELLE[i].ZAP29VALTAGE, m_String, DEZAPDKRALZAP29VALTAGE + (ANZ_DKRAL_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAL_ZAP29VALTAGE );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKSER ************************************************************/
 bool ConvertDkser( dezapdkserO *d, dezapcservicesSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKSER_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKSER_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP30TABELLE[i].ZAP30SNR,"   ",L_DEZAPDKSER_ZAP30SNR) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA30, SATZART_DKSER, DEZAPDKSERZAPSA30, L_DEZAPDKSER_ZAPSA30 );
			}

			/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
			CONV( d->ZAP30TABELLE[i].ZAP30FIL, "00", DEZAPDKSERZAP30FIL + (ANZ_DKSER_FELDER_PRO_ELEMENT * i), L_DEZAPDKSER_ZAP30FIL );

			LongToString(p->SERVICE_NO);
			CONV( d->ZAP30TABELLE[i].ZAP30SNR, m_String, DEZAPDKSERZAP30SNR + (ANZ_DKSER_FELDER_PRO_ELEMENT * i), L_DEZAPDKSER_ZAP30SNR );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP30TABELLE[i].ZAP30LOEKZ, "J", DEZAPDKSERZAP30LOEKZ + (ANZ_DKSER_FELDER_PRO_ELEMENT * i), L_DEZAPDKSER_ZAP30LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP30TABELLE[i].ZAP30BEZ, p->NAME, DEZAPDKSERZAP30BEZ + (ANZ_DKSER_FELDER_PRO_ELEMENT * i), L_DEZAPDKSER_ZAP30BEZ );
				CONV( d->ZAP30TABELLE[i].ZAP30TXSCHL, p->TEXT_KEY_DKFAM, DEZAPDKSERZAP30TXSCHL + (ANZ_DKSER_FELDER_PRO_ELEMENT * i), L_DEZAPDKSER_ZAP30TXSCHL );

				DoubleToString(p->SERVICE_CHARGE, L_DEZAPDKSER_ZAP30WERT, N_DEZAPDKSER_ZAP30WERT);
				AvoidOverflow( m_String, des[DEZAPDKSERZAP30WERT].laenge); 
				CONV( d->ZAP30TABELLE[i].ZAP30WERT, m_String, DEZAPDKSERZAP30WERT + (ANZ_DKSER_FELDER_PRO_ELEMENT * i), L_DEZAPDKSER_ZAP30WERT );

				LongToString(p->SERVICETYPENO);
				CONV( d->ZAP30TABELLE[i].ZAP30STYP, m_String, DEZAPDKSERZAP30STYP + (ANZ_DKSER_FELDER_PRO_ELEMENT * i), L_DEZAPDKSER_ZAP30STYP );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKAZB ************************************************************/
 bool ConvertDkazb( dezapdkazbO *d, dezapzartikelSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKAZB_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKAZB_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP33TABELLE[i].ZAP33PZN,"       ",L_DEZAPDKAZB_ZAP33PZN) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA33, SATZART_DKAZB, DEZAPDKAZBZAPSA33, L_DEZAPDKAZB_ZAPSA33 );
			}

			/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
			CONV( d->ZAP33TABELLE[i].ZAP33FIL, "00", DEZAPDKAZBZAP33FIL + (ANZ_DKAZB_FELDER_PRO_ELEMENT * i), L_DEZAPDKAZB_ZAP33FIL );

			LongToString(p->ARTIKEL_NR);
			CONV( d->ZAP33TABELLE[i].ZAP33PZN, m_String, DEZAPDKAZBZAP33PZN + (ANZ_DKAZB_FELDER_PRO_ELEMENT * i), L_DEZAPDKAZB_ZAP33PZN );

			/* wenn Langname leer oder kein Satz gefunden, Lˆschkennzeichen setzen, ansonsten Langname einstellen */
			if ( rc == eof ||
			     strncmp (p->ARTIKEL_LANGNAME, "                                                  ", L_ZARTIKEL_ARTIKEL_LANGNAME) == 0 )
			{
				CONV( d->ZAP33TABELLE[i].ZAP33LOEKZ, "J", DEZAPDKAZBZAP33LOEKZ + (ANZ_DKAZB_FELDER_PRO_ELEMENT * i), L_DEZAPDKAZB_ZAP33LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP33TABELLE[i].ZAP33LABEZ, p->ARTIKEL_LANGNAME, DEZAPDKAZBZAP33LABEZ + (ANZ_DKAZB_FELDER_PRO_ELEMENT * i), L_DEZAPDKAZB_ZAP33LABEZ );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DEPAU ************************************************************/
 bool ConvertDepau( dezapdepauO *d, dezapzartikelSTR *p, struct AUFB des[], rterror rc )
 {
    if (rc) {}

	int i;
	int j = ANZ_DEPAU_ELEMENTE - 1;

	for (i = 0; i < ANZ_DEPAU_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP39TABELLE[i].ZAP39PZNPSEU,"       ",L_DEZAPDEPAU_ZAP39PZNPSEU) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA39, SATZART_DEPAU, DEZAPDEPAUZAPSA39, L_DEZAPDEPAU_ZAPSA39 );
			}

			/* Filiale, Datum & Status immer mit 00 initialisieren (wird im PSA410 aus VLK geholt) */
			CONV( d->ZAP39TABELLE[i].ZAP39FIL,		"00",		DEZAPDEPAUZAP39FIL + (ANZ_DEPAU_FELDER_PRO_ELEMENT * i),	L_DEZAPDEPAU_ZAP39FIL );
			CONV( d->ZAP39TABELLE[i].ZAP39DATUM,	"00000000",	DEZAPDEPAUZAP39DATUM + (ANZ_DEPAU_FELDER_PRO_ELEMENT * i),	L_DEZAPDEPAU_ZAP39DATUM );
			CONV( d->ZAP39TABELLE[i].ZAP39STATUS,	"00",		DEZAPDEPAUZAP39STATUS + (ANZ_DEPAU_FELDER_PRO_ELEMENT * i),	L_DEZAPDEPAU_ZAP39STATUS );

			/* vorerst wird nur Satzart 01 versorgt */
			CONV( d->ZAP39TABELLE[i].ZAP39SA, "01", DEZAPDEPAUZAP39SA + (ANZ_DEPAU_FELDER_PRO_ELEMENT * i), L_DEZAPDEPAU_ZAP39SA );

			LongToString(p->ARTIKEL_NR);
			CONV( d->ZAP39TABELLE[i].ZAP39PZNPSEU, m_String, DEZAPDEPAUZAP39PZNPSEU + (ANZ_DEPAU_FELDER_PRO_ELEMENT * i), L_DEZAPDEPAU_ZAP39PZNPSEU );

			LongToString(p->ERSATZ_NR);
			CONV( d->ZAP39TABELLE[i].ZAP39PZNECHT, m_String, DEZAPDEPAUZAP39PZNECHT + (ANZ_DEPAU_FELDER_PRO_ELEMENT * i), L_DEZAPDEPAU_ZAP39PZNECHT );

			/* Artikelnummer des Herstellers enth‰lt vorangestelltes '#', das muss f¸r die ‹bergabe entfernt werden, deswegen + 1 bzw. -1 */
			CONV( d->ZAP39TABELLE[i].ZAP39MANRALT, p->ARTIKEL_NR_HERST + 1, DEZAPDEPAUZAP39MANRALT + (ANZ_DEPAU_FELDER_PRO_ELEMENT * i), L_DEZAPDEPAU_ZAP39MANRALT - 1);
			CONV( d->ZAP39TABELLE[i].ZAP39MANRNEU, p->ARTIKEL_NR_HERST + 1, DEZAPDEPAUZAP39MANRNEU + (ANZ_DEPAU_FELDER_PRO_ELEMENT * i), L_DEZAPDEPAU_ZAP39MANRNEU - 1);

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKGFG ************************************************************
 void ConvertDkgfg( dezapdkgfgO *d, dezapzartikelSTR *p, struct AUFB des[], rterror rc )
 {
    if (rc) {}

	CONV( d->ZAPSA10, SATZART_DKGFG, DEZAPDKGFGZAPSA10, L_DEZAPDKGFG_ZAPSA10 );

	// Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) 
	CONV( d->ZAP10FIL, "00", DEZAPDKGFGZAP10FIL, L_DEZAPDKGFG_ZAP10FIL );

    LongToString(p->ARTIKEL_NR);
	CONV( d->ZAP10PZN, m_String, DEZAPDKGFGZAP10PZN, L_DEZAPDKGFG_ZAP10PZN );

	ASSERT( d->ZAP10GSFP, p->GS_HOCHENTZ );
	ASSERT( d->ZAP10GSF,  p->GS_LEICHTENTZ );
	ASSERT( d->ZAP10GSE,  p->GS_EXPLOSION );
	ASSERT( d->ZAP10GSO,  p->GS_BRAND );
	ASSERT( d->ZAP10GSC,  p->GS_AETZEND );
	ASSERT( d->ZAP10GSTP, p->GS_SEHRGIFTIG );
	ASSERT( d->ZAP10GST,  p->GS_GIFTIG );
	ASSERT( d->ZAP10GSXN, p->GS_GESUNDHSCH );
	ASSERT( d->ZAP10GSXI, p->GS_REIZEND );
	ASSERT( d->ZAP10GSN,  p->GS_UMWELT );

	// zusaetzliche Felder uebertragen 12.04.2013 
	CONV( d->ZAP10UNNR,		p->G_UN_NR,			DEZAPDKGFGZAP10UNNR,	L_DEZAPDKGFG_ZAP10UNNR );
	CONV( d->ZAP10KLA,		p->GG_KLASSE,		DEZAPDKGFGZAP10KLA,		L_DEZAPDKGFG_ZAP10KLA );
	CONV( d->ZAP10ZIF,		p->GG_ZIFFER,		DEZAPDKGFGZAP10ZIF,		L_DEZAPDKGFG_ZAP10ZIF );
	CONV( d->ZAP10ALPHA,	p->GG_BUCHSTABE,	DEZAPDKGFGZAP10ALPHA,	L_DEZAPDKGFG_ZAP10ALPHA );
	CONV( d->ZAP10VBF,		p->G_VBF,			DEZAPDKGFGZAP10VBF,		L_DEZAPDKGFG_ZAP10VBF );
	CONV( d->ZAP10WGK,		p->G_WASSER,		DEZAPDKGFGZAP10WGK,		L_DEZAPDKGFG_ZAP10WGK );
	CONV( d->ZAP10VCI,		p->G_VCI,			DEZAPDKGFGZAP10VCI,		L_DEZAPDKGFG_ZAP10VCI );

	return;
} */

/*** CONVERT-DKWIR ************************************************************

 bool ConvertDkwir( dezapdkwirO *d, dezapzdkwirSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKWIR_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKWIR_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP19TABELLE[i].ZAP19GRUPPE,"   ",L_DEZAPDKWIR_ZAP19GRUPPE) || (i == j))
		{
			// beim ersten F¸llen Satzart miteinstellen 
			if (i == 0)
			{
				CONV( d->ZAPSA19, SATZART_DKWIR, DEZAPDKWIRZAPSA19, L_DEZAPDKWIR_ZAPSA19 );
			}

			CONV( d->ZAP19TABELLE[i].ZAP19GRUPPE, p->WIR_BEREICH, DEZAPDKWIRZAP19GRUPPE + (ANZ_DKWIR_FELDER_PRO_ELEMENT * i), L_DEZAPDKWIR_ZAP19GRUPPE );

			// jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen 
			if ( rc == eof )
			{
				CONV( d->ZAP19TABELLE[i].ZAP19LOEKZ, "J", DEZAPDKWIRZAP19LOEKZ + (ANZ_DKWIR_FELDER_PRO_ELEMENT * i), L_DEZAPDKWIR_ZAP19LOEKZ );
			}
			else
			{
				CONV( d->ZAP19TABELLE[i].ZAP19BEZ, p->WIR_BEZ, DEZAPDKWIRZAP19BEZ + (ANZ_DKWIR_FELDER_PRO_ELEMENT * i), L_DEZAPDKWIR_ZAP19BEZ );
				CONV( d->ZAP19TABELLE[i].ZAP19AKTIV, p->WIR_AKTIV, DEZAPDKWIRZAP19AKTIV + (ANZ_DKWIR_FELDER_PRO_ELEMENT * i), L_DEZAPDKWIR_ZAP19AKTIV );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
} */

/*** CONVERT-DKATX ************************************************************/

 bool ConvertDkatx( dezapdkatxO *d, dezapcarticletextSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKATX_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKATX_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP21TABELLE[i].ZAP21TXSCHL,"  ",L_DEZAPDKATX_ZAP21TXSCHL) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA21, SATZART_DKATX, DEZAPDKATXZAPSA21, L_DEZAPDKATX_ZAPSA21 );
			}

			/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
			CONV( d->ZAP21TABELLE[i].ZAP21FIL, "00", DEZAPDKATXZAP21FIL + (ANZ_DKATX_FELDER_PRO_ELEMENT * i), L_DEZAPDKATX_ZAP21FIL );

			CONV( d->ZAP21TABELLE[i].ZAP21TXSCHL, p->TEXTNO, DEZAPDKATXZAP21TXSCHL + (ANZ_DKATX_FELDER_PRO_ELEMENT * i), L_DEZAPDKATX_ZAP21TXSCHL );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP21TABELLE[i].ZAP21LOEKZ, "J", DEZAPDKATXZAP21LOEKZ + (ANZ_DKATX_FELDER_PRO_ELEMENT * i), L_DEZAPDKATX_ZAP21LOE );
			}
			else
			{
				CONV( d->ZAP21TABELLE[i].ZAP21TEXT1, p->TEXTLINE1, DEZAPDKATXZAP21TEXT1 + (ANZ_DKATX_FELDER_PRO_ELEMENT * i), L_DEZAPDKATX_ZAP21TEXT1 );
				CONV( d->ZAP21TABELLE[i].ZAP21TEXT2, p->TEXTLINE2, DEZAPDKATXZAP21TEXT2 + (ANZ_DKATX_FELDER_PRO_ELEMENT * i), L_DEZAPDKATX_ZAP21TEXT2 );
			    ASSERT( d->ZAP21TABELLE[i].ZAP21DRRE, p->PR_INVOICE );
			    ASSERT( d->ZAP21TABELLE[i].ZAP21DRKB, p->PR_PICKLIST );
			    ASSERT( d->ZAP21TABELLE[i].ZAP21ANKS, p->SH_CALLCENTER );
			    ASSERT( d->ZAP21TABELLE[i].ZAP21DRBV, p->PR_ORDERPROP );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKLID ************************************************************/

 bool ConvertDklid( dezapdklidO *d, dezapherstel_dispoSTR *p, struct AUFB des[], rterror rc )
 {
    if (rc) {}

	int i;
	int j = ANZ_DKLID_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKLID_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP25TABELLE[i].ZAP25HNR,"     ",L_DEZAPDKLID_ZAP25HNR) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA25, SATZART_DKLID, DEZAPDKLIDZAPSA25, L_DEZAPDKLID_ZAPSA25 );
			}

			LongToString(p->HERSTELLER_NR);
			CONV( d->ZAP25TABELLE[i].ZAP25HNR, m_String, DEZAPDKLIDZAP25HNR + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25HNR );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
/*			if ( rc == eof )
			{
				CONV( d->ZAP21TABELLE[i].ZAP21LOEKZ, "J", DEZAPDKATXZAP21LOEKZ + (ANZ_DKATX_FELDER_PRO_ELEMENT * i), L_DEZAPDKATX_ZAP21LOE );
			}
			else */
			{
				CONV( d->ZAP25TABELLE[i].ZAP25KONTAKT, p->ANSPRECHPARTNER, DEZAPDKLIDZAP25KONTAKT + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25KONTAKT );
				ASSERT( d->ZAP25TABELLE[i].ZAP25EDISPO, p->EINZELDISPO_OK );

				DoubleToString(p->MINDAUFTWERT, L_HERSTEL_DISPO_MINDAUFTWERT, N_HERSTEL_DISPO_MINDAUFTWERT);
				AvoidOverflow( m_String, des[DEZAPDKLIDZAP25MAWERT].laenge); 
				CONV( d->ZAP25TABELLE[i].ZAP25MAWERT, m_String, DEZAPDKLIDZAP25MAWERT + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25MAWERT );

				LongToString(p->MINDABMENGE1);
				CONV( d->ZAP25TABELLE[i].ZAP25MAM1, m_String, DEZAPDKLIDZAP25MAM1 + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25MAM1 );

				LongToString(p->MINDABMENGE2);
				CONV( d->ZAP25TABELLE[i].ZAP25MAM2, m_String, DEZAPDKLIDZAP25MAM2 + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25MAM2 );

				DoubleToString(p->MINDMENGZUSCHLAG, L_HERSTEL_DISPO_MINDMENGZUSCHLAG, N_HERSTEL_DISPO_MINDMENGZUSCHLAG);
				AvoidOverflow( m_String, des[DEZAPDKLIDZAP25MMZU].laenge); 
				CONV( d->ZAP25TABELLE[i].ZAP25MMZU, m_String, DEZAPDKLIDZAP25MMZU + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25MMZU );

				DoubleToString(p->MMZUWERT, L_HERSTEL_DISPO_MMZUWERT, N_HERSTEL_DISPO_MMZUWERT);
				AvoidOverflow( m_String, des[DEZAPDKLIDZAP25MMZUW].laenge); 
				CONV( d->ZAP25TABELLE[i].ZAP25MMZUW, m_String, DEZAPDKLIDZAP25MMZUW + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25MMZUW );

				DoubleToString(p->VERSKOSTPAUSCH, L_HERSTEL_DISPO_VERSKOSTPAUSCH, N_HERSTEL_DISPO_VERSKOSTPAUSCH);
				AvoidOverflow( m_String, des[DEZAPDKLIDZAP25VKOST].laenge); 
				CONV( d->ZAP25TABELLE[i].ZAP25VKOST, m_String, DEZAPDKLIDZAP25VKOST + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25VKOST );

				DoubleToString(p->VKOSTWERT, L_HERSTEL_DISPO_VKOSTWERT, N_HERSTEL_DISPO_VKOSTWERT);
				AvoidOverflow( m_String, des[DEZAPDKLIDZAP25VKOSTW].laenge); 
				CONV( d->ZAP25TABELLE[i].ZAP25VKOSTW, m_String, DEZAPDKLIDZAP25VKOSTW + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25VKOSTW );

				CONV( d->ZAP25TABELLE[i].ZAP25LZIEL, p->LIEFERZIEL, DEZAPDKLIDZAP25LZIEL + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25LZIEL );
				CONV( d->ZAP25TABELLE[i].ZAP25RZIEL, p->RECHNUNGSZIEL, DEZAPDKLIDZAP25RZIEL + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25RZIEL );
				CONV( d->ZAP25TABELLE[i].ZAP25VART1, p->VERSART1, DEZAPDKLIDZAP25VART1 + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25VART1 );
				CONV( d->ZAP25TABELLE[i].ZAP25VART2, p->VERSART2, DEZAPDKLIDZAP25VART2 + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25VART2 );
				CONV( d->ZAP25TABELLE[i].ZAP25TEXT, p->FREITXT, DEZAPDKLIDZAP25TEXT + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25TEXT );

				LongToString(p->LIEFERZEIT_MIN);
				CONV( d->ZAP25TABELLE[i].ZAP25LZMIN, m_String, DEZAPDKLIDZAP25LZMIN + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25LZMIN );

				LongToString(p->LIEFERZEIT_MAX);
				CONV( d->ZAP25TABELLE[i].ZAP25LZMAX, m_String, DEZAPDKLIDZAP25LZMAX + (ANZ_DKLID_FELDER_PRO_ELEMENT * i), L_DEZAPDKLID_ZAP25LZMAX );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKCRR ************************************************************/

 bool ConvertDkcrr( dezapdkcrrO *d, dezapzchargenrueckrufSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKCRR_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKCRR_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP22TABELLE[i].ZAP22PZN,"       ",L_DEZAPDKCRR_ZAP22PZN) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA22, SATZART_DKCRR, DEZAPDKCRRZAPSA22, L_DEZAPDKCRR_ZAPSA22 );
			}

			/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
			CONV( d->ZAP22TABELLE[i].ZAP22FIL, "00", DEZAPDKCRRZAP22FIL + (ANZ_DKCRR_FELDER_PRO_ELEMENT * i), L_DEZAPDKCRR_ZAP22FIL );

		    LongToString(p->ARTIKEL_NR);
			CONV( d->ZAP22TABELLE[i].ZAP22PZN, m_String, DEZAPDKCRRZAP22PZN + (ANZ_DKCRR_FELDER_PRO_ELEMENT * i), L_DEZAPDKCRR_ZAP22PZN );

			/* falls alle Chargenr¸ckrufe eines Artikels gelˆscht wurden */
			if ( rc == eof )
			{
				CONV( d->ZAP22TABELLE[i].ZAP22LOEKZ, "J", DEZAPDKCRRZAP22LOEKZ + (ANZ_DKCRR_FELDER_PRO_ELEMENT * i), L_DEZAPDKCRR_ZAP22LOE );
			}
			else
			{
				CONV( d->ZAP22TABELLE[i].ZAP22CHARGE, p->CHARGE, DEZAPDKCRRZAP22CHARGE + (ANZ_DKCRR_FELDER_PRO_ELEMENT * i), L_DEZAPDKCRR_ZAP22CHARGE );
				CONV( d->ZAP22TABELLE[i].ZAP22RRKZ, p->RUECKRUF_KZ, DEZAPDKCRRZAP22RRKZ + (ANZ_DKCRR_FELDER_PRO_ELEMENT * i), L_DEZAPDKCRR_ZAP22RRKZ );
				CONV( d->ZAP22TABELLE[i].ZAP22EINSCHR, p->EINSCHRAENKUNGEN, DEZAPDKCRRZAP22EINSCHR + (ANZ_DKCRR_FELDER_PRO_ELEMENT * i), L_DEZAPDKCRR_ZAP22EINSCHR );

				LongToString(p->DATUM_ANLAGE);
				CONV( d->ZAP22TABELLE[i].ZAP22DERST, m_String, DEZAPDKCRRZAP22DERST + (ANZ_DKCRR_FELDER_PRO_ELEMENT * i), L_DEZAPDKCRR_ZAP22DERST );

				LongToString(p->DATETO_CUSTRETURNS);
				CONV( d->ZAP22TABELLE[i].ZAP22LOEDAT, m_String, DEZAPDKCRRZAP22LOEDAT + (ANZ_DKCRR_FELDER_PRO_ELEMENT * i), L_DEZAPDKCRR_ZAP22DERST );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKSOA ************************************************************/

  bool ConvertDksoa( dezapdksoaO *d, dezapcbaselistarticlesSTR *p, struct AUFB des[], rterror rc )
  {
	int i;
	int j = ANZ_DKSOA_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKSOA_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP03TABELLE[i].ZAP03PZN,"       ",L_DEZAPDKSOA_ZAP03PZN) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA03, SATZART_DKSOA, DEZAPDKSOAZAPSA03, L_DEZAPDKSOA_ZAPSA03 );
			}

		    LongToString(p->ARTICLENO);
			CONV( d->ZAP03TABELLE[i].ZAP03PZN, m_String, DEZAPDKSOAZAP03PZN + (ANZ_DKSOA_FELDER_PRO_ELEMENT * i), L_DEZAPDKSOA_ZAP03PZN );

			/* falls alle Eintr‰ge eines Artikels gelˆscht wurden */
			if ( rc == eof )
			{
				CONV( d->ZAP03TABELLE[i].ZAP03LOEKZ, "J", DEZAPDKSOAZAP03LOEKZ + (ANZ_DKSOA_FELDER_PRO_ELEMENT * i), L_DEZAPDKSOA_ZAP03LOEKZ );
			}
			else
			{
				CONV( d->ZAP03TABELLE[i].ZAP03KZ, p->BASELIST_ID, DEZAPDKSOAZAP03KZ + (ANZ_DKSOA_FELDER_PRO_ELEMENT * i), L_DEZAPDKSOA_ZAP03KZ );
				CONV( d->ZAP03TABELLE[i].ZAP03MENGE, "000", DEZAPDKSOAZAP03MENGE + (ANZ_DKSOA_FELDER_PRO_ELEMENT * i), L_DEZAPDKSOA_ZAP03MENGE );
				CONV( d->ZAP03TABELLE[i].ZAP03PREIS, "0000000", DEZAPDKSOAZAP03PREIS + (ANZ_DKSOA_FELDER_PRO_ELEMENT * i), L_DEZAPDKSOA_ZAP03PREIS );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKACO ************************************************************/

 bool ConvertDkaco( dezapdkacoO *d, dezapcarticlecodesSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKACO_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKACO_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP34TABELLE[i].ZAP34PZN,"       ", L_DEZAPDKACO_ZAP34PZN) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA34, SATZART_DKACO, DEZAPDKACOZAPSA34, L_DEZAPDKACO_ZAPSA34 );
			}

			/* Filialen immer mit 00 initialisieren (werden im PSA425 aus VLK geholt) */
			CONV( d->ZAP34TABELLE[i].ZAP34FIL, "00", DEZAPDKACOZAP34FIL + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34FIL );
			CONV( d->ZAP34TABELLE[i].ZAP34FIL2, "00", DEZAPDKACOZAP34FIL2 + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34FIL2 );

		    LongToString(p->ARTICLENO);
			CONV( d->ZAP34TABELLE[i].ZAP34PZN, m_String, DEZAPDKACOZAP34PZN + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34PZN );
			CONV( d->ZAP34TABELLE[i].ZAP34PZN2, m_String, DEZAPDKACOZAP34PZN2 + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34PZN2 );

			/* falls alle Chargenr¸ckrufe eines Artikels gelˆscht wurden */
			if ( rc == eof )
			{
				CONV( d->ZAP34TABELLE[i].ZAP34LOEKZ, "J", DEZAPDKACOZAP34LOEKZ + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34LOE );
			}
			else
			{
				LongToString(p->PREFERRED_FLAG);
				ASSERT( d->ZAP34TABELLE[i].ZAP34PREF, m_String );

				CONV( d->ZAP34TABELLE[i].ZAP34CODE, p->ARTICLE_CODE, DEZAPDKACOZAP34CODE + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34CODE );
				CONV( d->ZAP34TABELLE[i].ZAP34CODE2, p->ARTICLE_CODE, DEZAPDKACOZAP34CODE2 + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34CODE2 );

				LongToString(p->CODE_TYPE);
				CONV( d->ZAP34TABELLE[i].ZAP34CTYP, m_String, DEZAPDKACOZAP34CTYP + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34CTYP );
				CONV( d->ZAP34TABELLE[i].ZAP34CTYP2, m_String, DEZAPDKACOZAP34CTYP2 + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34CTYP2 );

				LongToString(p->SERIAL_NUMBER);
				CONV( d->ZAP34TABELLE[i].ZAP34LFD, m_String, DEZAPDKACOZAP34LFD + (ANZ_DKACO_FELDER_PRO_ELEMENT * i), L_DEZAPDKACO_ZAP34LFD );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKRAB ************************************************************/

 bool ConvertDkrab( dezapdkrabO *d, dezapcdiscountSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKRAB_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKRAB_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP28TABELLE[i].ZAP28PZN,"       ",L_DEZAPDKRAB_ZAP28PZN) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA28, SATZART_DKRAB, DEZAPDKRABZAPSA28, L_DEZAPDKRAB_ZAPSA28 );
			}

			/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
			CONV( d->ZAP28TABELLE[i].ZAP28FIL, "00", DEZAPDKRABZAP28FIL + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28FIL );

			/* immer die Kombination PZN / RGN / HNR / AGN behandeln, jeweils einer dieser beiden Werte ist gef¸llt) */
			LongToString(p->ARTICLENO);
			CONV( d->ZAP28TABELLE[i].ZAP28PZN, m_String, DEZAPDKRABZAP28PZN + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28PZN );

			LongToString(p->DISCOUNTGRPNO);
			CONV( d->ZAP28TABELLE[i].ZAP28RGN, m_String, DEZAPDKRABZAP28RGN + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28RGN );

			LongToString(p->MANUFACTURERNO);
			CONV( d->ZAP28TABELLE[i].ZAP28HNR, m_String, DEZAPDKRABZAP28HNR + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28HNR );

			LongToString(p->ARTCATEGORYNO);
			CONV( d->ZAP28TABELLE[i].ZAP28AGN, m_String, DEZAPDKRABZAP28AGN + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28AGN );

			/* falls alle Rabatte eines Artikels gelˆscht wurden */
			if ( rc == eof )
			{
				CONV( d->ZAP28TABELLE[i].ZAP28LOEKZ, "J", DEZAPDKRABZAP28LOEKZ + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28LOE );
			}
			else
			{
				CONV( d->ZAP28TABELLE[i].ZAP28EGR, p->PHARMACYGROUPID, DEZAPDKRABZAP28EGR + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28EGR );

				LongToString(p->CUSTOMERNO);
				CONV( d->ZAP28TABELLE[i].ZAP28IDF, m_String, DEZAPDKRABZAP28IDF + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28IDF );

				LongToString(p->BASEQTY);
				CONV( d->ZAP28TABELLE[i].ZAP28BASIS, m_String, DEZAPDKRABZAP28BASIS + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28BASIS );

				DoubleToString(p->BASE_VALUE, L_DEZAPDKRAB_ZAP28BASWERT, N_DEZAPDKRAB_ZAP28BASWERT);
				AvoidOverflow( m_String, des[DEZAPDKRABZAP28BASWERT].laenge); 
				CONV( d->ZAP28TABELLE[i].ZAP28BASWERT, m_String, DEZAPDKRABZAP28BASWERT + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28BASWERT );

				LongToString(p->BASE_MULT_STD_QTY);
				CONV( d->ZAP28TABELLE[i].ZAP28BASMULT, m_String, DEZAPDKRABZAP28BASMULT + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28BASMULT );

				LongToString(p->DATEFROM);
				CONV( d->ZAP28TABELLE[i].ZAP28DABE, m_String, DEZAPDKRABZAP28DABE + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28DABE );

				LongToString(p->DATETO);
				CONV( d->ZAP28TABELLE[i].ZAP28DAEN, m_String, DEZAPDKRABZAP28DAEN + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28DAEN );

				LongToString(p->GRPDISCOUNTTYP);
				CONV( d->ZAP28TABELLE[i].ZAP28RGT, m_String, DEZAPDKRABZAP28RGT + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28RGT );

				LongToString(p->DISCOUNTTYPE);
				CONV( d->ZAP28TABELLE[i].ZAP28RABTYP, m_String, DEZAPDKRABZAP28RABTYP + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28RABTYP );

				LongToString(p->DISCOUNTSPEC);
				CONV( d->ZAP28TABELLE[i].ZAP28RABSPEZ, m_String, DEZAPDKRABZAP28RABSPEZ + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28RABSPEZ );

				LongToString(p->PAYMENTTARGETNO);
				CONV( d->ZAP28TABELLE[i].ZAP28ZZNR, m_String, DEZAPDKRABZAP28ZZNR + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28ZZNR );

				LongToString(p->DISCOUNTQTY);
				CONV( d->ZAP28TABELLE[i].ZAP28NRMENG, m_String, DEZAPDKRABZAP28NRMENG + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28NRMENG );

				DoubleToString(p->DISCOUNTVALUEPCT, L_DEZAPDKRAB_ZAP28PROZWERT, N_DEZAPDKRAB_ZAP28PROZWERT);
				AvoidOverflow( m_String, des[DEZAPDKRABZAP28PROZWERT].laenge); 
				CONV( d->ZAP28TABELLE[i].ZAP28PROZWERT, m_String, DEZAPDKRABZAP28PROZWERT + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28PROZWERT );

				DoubleToString(p->DISCOUNTQTYPCT, L_DEZAPDKRAB_ZAP28PROZMENG, N_DEZAPDKRAB_ZAP28PROZMENG);
				AvoidOverflow( m_String, des[DEZAPDKRABZAP28PROZMENG].laenge); 
				CONV( d->ZAP28TABELLE[i].ZAP28PROZMENG, m_String, DEZAPDKRABZAP28PROZMENG + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28PROZMENG );

				DoubleToString(p->SURCHARGEPCT, L_DEZAPDKRAB_ZAP28AUFSCHLAG, N_DEZAPDKRAB_ZAP28AUFSCHLAG);
				AvoidOverflow( m_String, des[DEZAPDKRABZAP28AUFSCHLAG].laenge); 
				CONV( d->ZAP28TABELLE[i].ZAP28AUFSCHLAG, m_String, DEZAPDKRABZAP28AUFSCHLAG + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28AUFSCHLAG );

				CONV( d->ZAP28TABELLE[i].ZAP28NGEG1, p->PHARMGRPEXCLUDED, DEZAPDKRABZAP28NGEG1 + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28NGEG1 );
				CONV( d->ZAP28TABELLE[i].ZAP28NGEG2, p->PHARMGRPEXCL_2, DEZAPDKRABZAP28NGEG2 + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28NGEG2 );
				CONV( d->ZAP28TABELLE[i].ZAP28NGEG3, p->PHARMGRPEXCL_3, DEZAPDKRABZAP28NGEG3 + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28NGEG3 );

				DoubleToString(p->FIXEDPRICE, L_DEZAPDKRAB_ZAP28FIXPREIS, N_DEZAPDKRAB_ZAP28FIXPREIS);
				AvoidOverflow( m_String, des[DEZAPDKRABZAP28FIXPREIS].laenge); 
				CONV( d->ZAP28TABELLE[i].ZAP28FIXPREIS, m_String, DEZAPDKRABZAP28FIXPREIS + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28FIXPREIS );

				DoubleToString(p->REFUNDPCT, L_DEZAPDKRAB_ZAP28PROZERST, N_DEZAPDKRAB_ZAP28PROZERST);
				AvoidOverflow( m_String, des[DEZAPDKRABZAP28PROZERST].laenge); 
				CONV( d->ZAP28TABELLE[i].ZAP28PROZERST, m_String, DEZAPDKRABZAP28PROZERST + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28PROZERST );

				/* Monatsrabatt 1:1 ¸bernehmen (wg. neuem Wert 2) 
				ASSERT( d->ZAP28TABELLE[i].ZAP28MONRAB, p->MONTHLYDISCOUNT ); */
			    strncpy(d->ZAP28TABELLE[i].ZAP28MONRAB, p->MONTHLYDISCOUNT, 1); 

				ASSERT( d->ZAP28TABELLE[i].ZAP28INTERN, p->INTERNALDISCOUNT );
				ASSERT( d->ZAP28TABELLE[i].ZAP28NOPROP, p->NO_MULTIPLE_QTY );

				LongToString(p->DISCOUNTARTICLE);
				CONV( d->ZAP28TABELLE[i].ZAP28NRPZN, m_String, DEZAPDKRABZAP28NRPZN + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28NRPZN );

				DoubleToString(p->FIXEDDISCOUNTVALUE, L_DEZAPDKRAB_ZAP28FIXWERT, N_DEZAPDKRAB_ZAP28FIXWERT);
				AvoidOverflow( m_String, des[DEZAPDKRABZAP28FIXWERT].laenge); 
				CONV( d->ZAP28TABELLE[i].ZAP28FIXWERT, m_String, DEZAPDKRABZAP28FIXWERT + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28FIXWERT );

				DoubleToString(p->GROSSPROFITPCT, L_DEZAPDKRAB_ZAP28ROHERTR, N_DEZAPDKRAB_ZAP28ROHERTR);
				AvoidOverflow( m_String, des[DEZAPDKRABZAP28ROHERTR].laenge); 
				CONV( d->ZAP28TABELLE[i].ZAP28ROHERTR, m_String, DEZAPDKRABZAP28ROHERTR + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28ROHERTR );

				ASSERT( d->ZAP28TABELLE[i].ZAP28ZURABOK, p->ADDONDISCOUNTOK );
				ASSERT( d->ZAP28TABELLE[i].ZAP28ZAHLART, p->PAYMENTTERMTYPE );

				LongToString(p->REFUNDTYPE);
				CONV( d->ZAP28TABELLE[i].ZAP28ERSTTYP, m_String, DEZAPDKRABZAP28ERSTTYP + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28ERSTTYP );

				LongToString(p->ARTICLE_NO_PACK);
				CONV( d->ZAP28TABELLE[i].ZAP28STPZN, m_String, DEZAPDKRABZAP28STPZN + (ANZ_DKRAB_FELDER_PRO_ELEMENT * i), L_DEZAPDKRAB_ZAP28STPZN );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKRPG ************************************************************/

 bool ConvertDkrpg( dezapdkrpgO *d, dezapcdiscgrpSTR *o, dezapcdiscgrpmemSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKRPG_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKRPG_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP31TABELLE[i].ZAP31RPG,"     ",L_DEZAPDKRPG_ZAP31RPG) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA31, SATZART_DKRPG, DEZAPDKRPGZAPSA31, L_DEZAPDKRPG_ZAPSA31 );
			}

			/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
			CONV( d->ZAP31TABELLE[i].ZAP31FIL,  "00", DEZAPDKRPGZAP31FIL  + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31FIL  );
			CONV( d->ZAP31TABELLE[i].ZAP31FIL2, "00", DEZAPDKRPGZAP31FIL2 + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31FIL2 );

			LongToString(o->DISCOUNTGRPNO);
			CONV( d->ZAP31TABELLE[i].ZAP31RPG, m_String, DEZAPDKRPGZAP31RPG + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31RPG );

			/* falls alle Artikel einer Rabatt-Produktgruppe gelˆscht wurden */
			if ( rc == eof )
			{
				CONV( d->ZAP31TABELLE[i].ZAP31LOEKZ, "J", DEZAPDKRPGZAP31LOEKZ + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31LOE );
			}
			else
			{
				LongToString(p->ARTICLENO);
				CONV( d->ZAP31TABELLE[i].ZAP31PZN,  m_String, DEZAPDKRPGZAP31PZN  + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31PZN  );
				CONV( d->ZAP31TABELLE[i].ZAP31PZN2, m_String, DEZAPDKRPGZAP31PZN2 + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31PZN2 );

				LongToString(p->MANUFACTURERNO);
				CONV( d->ZAP31TABELLE[i].ZAP31HNR,  m_String, DEZAPDKRPGZAP31HNR  + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31HNR  );
				CONV( d->ZAP31TABELLE[i].ZAP31HNR2, m_String, DEZAPDKRPGZAP31HNR2 + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31HNR2 );

				LongToString(o->CUSTOMERNO);
				CONV( d->ZAP31TABELLE[i].ZAP31IDF2, m_String, DEZAPDKRPGZAP31IDF2 + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31IDF2 );

				LongToString(o->DISCOUNTGRPNO);
				CONV( d->ZAP31TABELLE[i].ZAP31RPG2, m_String, DEZAPDKRPGZAP31RPG2 + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31RPG2 );

				LongToString(p->DISCOUNTCONDITION);
				CONV( d->ZAP31TABELLE[i].ZAP31KOND, m_String, DEZAPDKRPGZAP31KOND  + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31KOND );

				LongToString(o->DISCOUNTGRPTYPE);
				CONV( d->ZAP31TABELLE[i].ZAP31GRPART, m_String, DEZAPDKRPGZAP31GRPART  + (ANZ_DKRPG_FELDER_PRO_ELEMENT * i), L_DEZAPDKRPG_ZAP31GRPART );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKAFF ************************************************************/

 bool ConvertDkaff( dezapdkaffO *d, dezapcarticlelangSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKAFF_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKAFF_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP11TABELLE[i].ZAP11PZN,"       ",L_DEZAPDKAFF_ZAP11PZN) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA11, SATZART_DKAFF, DEZAPDKAFFZAPSA11, L_DEZAPDKAFF_ZAPSA11 );
			}

		    LongToString(p->ARTICLENO);
			CONV( d->ZAP11TABELLE[i].ZAP11PZN, m_String, DEZAPDKAFFZAP11PZN + (ANZ_DKAFF_FELDER_PRO_ELEMENT * i), L_DEZAPDKAFF_ZAP11PZN );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				/* CONV( d->ZAP11TABELLE[i].ZAP11LOEKZ, "J", DEZAPDKAFFZAP11LOEKZ + (ANZ_DKAFF_FELDER_PRO_ELEMENT * i), L_DEZAPDKAFF_ZAP11LOE ); */
			}
			else
			{
				CONV( d->ZAP11TABELLE[i].ZAP11SKZ, p->LANGID, DEZAPDKAFFZAP11SKZ + (ANZ_DKAFF_FELDER_PRO_ELEMENT * i), L_DEZAPDKAFF_ZAP11SKZ );
				CONV( d->ZAP11TABELLE[i].ZAP11KUBZ, p->ARTICLEMC, DEZAPDKAFFZAP11KUBZ + (ANZ_DKAFF_FELDER_PRO_ELEMENT * i), L_DEZAPDKAFF_ZAP11KUBZ );
				CONV( d->ZAP11TABELLE[i].ZAP11EINH, p->PACKAGINGUNIT, DEZAPDKAFFZAP11EINH + (ANZ_DKAFF_FELDER_PRO_ELEMENT * i), L_DEZAPDKAFF_ZAP11EINH );
				CONV( d->ZAP11TABELLE[i].ZAP11ABEZ, p->ARTICLENAME, DEZAPDKAFFZAP11ABEZ + (ANZ_DKAFF_FELDER_PRO_ELEMENT * i), L_DEZAPDKAFF_ZAP11ABEZ );
				CONV( d->ZAP11TABELLE[i].ZAP11DRFO, p->PHARMAFORM, DEZAPDKAFFZAP11DRFO + (ANZ_DKAFF_FELDER_PRO_ELEMENT * i), L_DEZAPDKAFF_ZAP11DRFO );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKSTE ************************************************************/

bool ConvertDkste( dezapdksteO *d, dezapcartcompackSTR *p, dezapccpvalidityperiodSTR *v, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKSTE_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKSTE_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP13TABELLE[i].ZAP13PZN,"       ",L_DEZAPDKSTE_ZAP13PZN) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA13, SATZART_DKSTE, DEZAPDKSTEZAPSA13, L_DEZAPDKSTE_ZAPSA13 );
			}

			/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
			CONV( d->ZAP13TABELLE[i].ZAP13FIL, "00", DEZAPDKSTEZAP13FIL + (ANZ_DKSTE_FELDER_PRO_ELEMENT * i), L_DEZAPDKSTE_ZAP13FIL );

		    LongToString(v->ARTICLE_NO_PACK);
			CONV( d->ZAP13TABELLE[i].ZAP13PZN, m_String, DEZAPDKSTEZAP13PZN + (ANZ_DKSTE_FELDER_PRO_ELEMENT * i), L_DEZAPDKSTE_ZAP13PZN );

			/* falls alle S‰tze eines Artikels gelˆscht wurden */
			if ( rc == eof )
			{
				CONV( d->ZAP13TABELLE[i].ZAP13LOEKZ, "J", DEZAPDKSTEZAP13LOEKZ + (ANZ_DKSTE_FELDER_PRO_ELEMENT * i), L_DEZAPDKSTE_ZAP13LOE );
			}
			else
			{
				LongToString(p->ARTICLE_NO_ELEMENT);
				CONV( d->ZAP13TABELLE[i].ZAP13EPZN, m_String, DEZAPDKSTEZAP13EPZN + (ANZ_DKSTE_FELDER_PRO_ELEMENT * i), L_DEZAPDKSTE_ZAP13EPZN );

				LongToString(p->QUANTITY);
				CONV( d->ZAP13TABELLE[i].ZAP13EMEN, m_String, DEZAPDKSTEZAP13EMEN + (ANZ_DKSTE_FELDER_PRO_ELEMENT * i), L_DEZAPDKSTE_ZAP13EMEN );

				LongToString(v->DATEFROM);
				CONV( d->ZAP13TABELLE[i].ZAP13DATVON, m_String, DEZAPDKSTEZAP13DATVON + (ANZ_DKSTE_FELDER_PRO_ELEMENT * i), L_DEZAPDKSTE_ZAP13DATVON );

				LongToString(v->DATETO);
				CONV( d->ZAP13TABELLE[i].ZAP13DATBIS, m_String, DEZAPDKSTEZAP13DATBIS + (ANZ_DKSTE_FELDER_PRO_ELEMENT * i), L_DEZAPDKSTE_ZAP13DATBIS );

				LongToString(v->COMPACK_TYPE);
				CONV( d->ZAP13TABELLE[i].ZAP13TYP, m_String, DEZAPDKSTEZAP13TYP + (ANZ_DKSTE_FELDER_PRO_ELEMENT * i), L_DEZAPDKSTE_ZAP13TYP );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DRRAM **********************************************************/

 void ConvertDrram( dezapdrramO *d, dezapcdiscmodelSTR *a, struct AUFB des[], rterror rc )
 {
   CONV( d->ZAPSA35, SATZART_DRRAM, DEZAPDRRAMZAPSA35, L_DEZAPDRRAM_ZAPSA35 );

   LongToString(a->DISCOUNTMODELNO);
   CONV( d->ZAP35ART, m_String, DEZAPDRRAMZAP35ART, L_DEZAPDRRAM_ZAP35ART );

	/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
	if ( rc == eof )
	{
		CONV( d->ZAP35LOEKZ, "J", DEZAPDRRAMZAP35LOEKZ, L_DEZAPDRRAM_ZAP35LOEKZ );
	}
	else
	{
		CONV( d->ZAP35BEZ, a->DISCOUNTMODELNAME, DEZAPDRRAMZAP35BEZ, L_DEZAPDRRAM_ZAP35BEZ );

		LongToString(a->BASENO1);
		CONV( d->ZAP35BAS1, m_String, DEZAPDRRAMZAP35BAS1, L_DEZAPDRRAM_ZAP35BAS1);

		LongToString(a->BASENO2);
		CONV( d->ZAP35BAS2, m_String, DEZAPDRRAMZAP35BAS2, L_DEZAPDRRAM_ZAP35BAS2);

		LongToString(a->BASENO3);
		CONV( d->ZAP35BAS3, m_String, DEZAPDRRAMZAP35BAS3, L_DEZAPDRRAM_ZAP35BAS3);

		LongToString(a->BASENO4);
		CONV( d->ZAP35BAS4, m_String, DEZAPDRRAMZAP35BAS4, L_DEZAPDRRAM_ZAP35BAS4);

		LongToString(a->BASENO5);
		CONV( d->ZAP35BAS5, m_String, DEZAPDRRAMZAP35BAS5, L_DEZAPDRRAM_ZAP35BAS5);

		LongToString(a->BASENO6);
		CONV( d->ZAP35BAS6, m_String, DEZAPDRRAMZAP35BAS6, L_DEZAPDRRAM_ZAP35BAS6);

		LongToString(a->BASENO7);
		CONV( d->ZAP35BAS7, m_String, DEZAPDRRAMZAP35BAS7, L_DEZAPDRRAM_ZAP35BAS7);

		LongToString(a->BASENO8);
		CONV( d->ZAP35BAS8, m_String, DEZAPDRRAMZAP35BAS8, L_DEZAPDRRAM_ZAP35BAS8);

		LongToString(a->BASENO9);
		CONV( d->ZAP35BAS9, m_String, DEZAPDRRAMZAP35BAS9, L_DEZAPDRRAM_ZAP35BAS9);

		LongToString(a->BASENO10);
		CONV( d->ZAP35BAS10, m_String, DEZAPDRRAMZAP35BAS10, L_DEZAPDRRAM_ZAP35BAS10);
	}

	return;
 }

/*** CONVERT-DKMRS ************************************************************/

 bool ConvertDkmrs( dezapdkmrsO *d, dezapcmonthdiscsortSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKMRS_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKMRS_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP36TABELLE[i].ZAP36MORASO,"    ",L_DEZAPDKMRS_ZAP36MORASO) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA36, SATZART_DKMRS, DEZAPDKMRSZAPSA36, L_DEZAPDKMRS_ZAPSA36 );

			LongToString(p->MONTHLYDISCOUNTGRP);
			CONV( d->ZAP36TABELLE[i].ZAP36MORASO, m_String, DEZAPDKMRSZAP36MORASO + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36MORASO );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP36TABELLE[i].ZAP36LOEKZ, "J", DEZAPDKMRSZAP36LOEKZ + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP36TABELLE[i].ZAP36OBER, p->NAME1, DEZAPDKMRSZAP36OBER + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36OBER );
				CONV( d->ZAP36TABELLE[i].ZAP36BEZ, p->NAME2, DEZAPDKMRSZAP36BEZ + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36BEZ );
				CONV( d->ZAP36TABELLE[i].ZAP36PROG, p->PROGRAM_NAME, DEZAPDKMRSZAP36PROG + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36PROG );

			    LongToString(p->CUSTOMERFIELDID);
				CONV( d->ZAP36TABELLE[i].ZAP36RABART, m_String, DEZAPDKMRSZAP36RABART + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36RABART );

				LongToString(p->CASH_DISC_POSSIBLE);
				CONV( d->ZAP36TABELLE[i].ZAP36SKF, m_String, DEZAPDKMRSZAP36SKF + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36SKF );
/*				ASSERT( d->ZAP36TABELLE[i].ZAP36SKF, m_String ); */
				
				LongToString(p->TYPE);
				CONV( d->ZAP36TABELLE[i].ZAP36TYP, m_String, DEZAPDKMRSZAP36TYP + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36TYP );

				LongToString(p->DISCOUNTBASE);
				CONV( d->ZAP36TABELLE[i].ZAP36UMSBAS, m_String, DEZAPDKMRSZAP36UMSBAS + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36UMSBAS );

				LongToString(p->STD_DEDUCTION);
				CONV( d->ZAP36TABELLE[i].ZAP36SOCKEL, m_String, DEZAPDKMRSZAP36SOCKEL + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36SOCKEL );

				DoubleToString(p->CAPDISCPCT, L_DEZAPDKMRS_ZAP36DECKRP, N_DEZAPDKMRS_ZAP36DECKRP);
				AvoidOverflow( m_String, des[DEZAPDKMRSZAP36DECKRP].laenge); 
				CONV( d->ZAP36TABELLE[i].ZAP36DECKRP, m_String, DEZAPDKMRSZAP36DECKRP + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36DECKRP );

				DoubleToString(p->CAPDISCRATE, L_DEZAPDKMRS_ZAP36DECKRS, N_DEZAPDKMRS_ZAP36DECKRS);
				AvoidOverflow( m_String, des[DEZAPDKMRSZAP36DECKRS].laenge); 
				CONV( d->ZAP36TABELLE[i].ZAP36DECKRS, m_String, DEZAPDKMRSZAP36DECKRS + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36DECKRS );

				LongToString(p->CUSTMINTURNOVER);
				CONV( d->ZAP36TABELLE[i].ZAP36KRABBU, m_String, DEZAPDKMRSZAP36KRABBU + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36KRABBU );

				LongToString(p->STREBER_FORMULA);
				CONV( d->ZAP36TABELLE[i].ZAP36STFORM, m_String, DEZAPDKMRSZAP36STFORM + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36STFORM );

				LongToString(p->REPOSTING);
				CONV( d->ZAP36TABELLE[i].ZAP36UMBUCH, m_String, DEZAPDKMRSZAP36UMBUCH + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36UMBUCH );

				LongToString(p->SPEC_CASH_DISC_TYP);
				CONV( d->ZAP36TABELLE[i].ZAP36SOSKOTYP, m_String, DEZAPDKMRSZAP36SOSKOTYP + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36SOSKOTYP );

				DoubleToString(p->SCD_RATE, L_DEZAPDKMRS_ZAP36SOSKOPROZ, N_DEZAPDKMRS_ZAP36SOSKOPROZ);
				AvoidOverflow( m_String, des[DEZAPDKMRSZAP36SOSKOPROZ].laenge); 
				CONV( d->ZAP36TABELLE[i].ZAP36SOSKOPROZ, m_String, DEZAPDKMRSZAP36SOSKOPROZ + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36SOSKOPROZ );

				CONV( d->ZAP36TABELLE[i].ZAP36SOSKOPROG, p->SCD_PROGRAM_NAME, DEZAPDKMRSZAP36SOSKOPROG + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36SOSKOPROG );

				LongToString(p->GDP_EXEMPTION);
				CONV( d->ZAP36TABELLE[i].ZAP36GDPAUS, m_String, DEZAPDKMRSZAP36GDPAUS + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36GDPAUS );

				LongToString(p->KVA_RELEVANT);
				CONV( d->ZAP36TABELLE[i].ZAP36KVAREL, m_String, DEZAPDKMRSZAP36KVAREL + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36KVAREL );

				LongToString(p->BRANCH_PHARMACY_CALC);
				CONV( d->ZAP36TABELLE[i].ZAP36FILAPO, m_String, DEZAPDKMRSZAP36FILAPO + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36FILAPO );

				LongToString(p->CAPINDEX_TRBB);
				CONV( d->ZAP36TABELLE[i].ZAP36DECKITRBB, m_String, DEZAPDKMRSZAP36DECKITRBB + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36DECKITRBB );

				LongToString(p->CUST_SPEC_TURNOVER_BASE_DEDUCTION);
				CONV( d->ZAP36TABELLE[i].ZAP36USREDUZ, m_String, DEZAPDKMRSZAP36USREDUZ + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36USREDUZ );

				LongToString(p->HIGHPRICEFLAG);
				CONV( d->ZAP36TABELLE[i].ZAP36HOPR, m_String, DEZAPDKMRSZAP36HOPR + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36HOPR );

				LongToString(p->INVOICEDISCCALCTYPE);
				CONV( d->ZAP36TABELLE[i].ZAP36RRBERART, m_String, DEZAPDKMRSZAP36RRBERART + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36RRBERART );

				LongToString(p->NOCOMPENSATIONFLAG);
				CONV( d->ZAP36TABELLE[i].ZAP36KEINENV, m_String, DEZAPDKMRSZAP36KEINENV + (ANZ_DKMRS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMRS_ZAP36KEINENV );
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
}

/*** CONVERT-DKGHZ ************************************************************/

 bool ConvertDkghz( dezapdkghzO *d, dezapchighpaymtargetfeeSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKGHZ_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKGHZ_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP37TABELLE[i].ZAP37KUKLA," ",L_DEZAPDKGHZ_ZAP37KUKLA) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA37, SATZART_DKGHZ, DEZAPDKGHZZAPSA37, L_DEZAPDKGHZ_ZAPSA37 );

			/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
			CONV( d->ZAP37TABELLE[i].ZAP37FIL, "00", DEZAPDKGHZZAP37FIL + (ANZ_DKGHZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKGHZ_ZAP37FIL );

			CONV( d->ZAP37TABELLE[i].ZAP37KUKLA, p->CUSTCLASSIFICATION, DEZAPDKGHZZAP37KUKLA + (ANZ_DKGHZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKGHZ_ZAP37KUKLA );

			LongToString(p->FROMPAYMTARGETDAYS);
			CONV( d->ZAP37TABELLE[i].ZAP37ABTAGE, m_String, DEZAPDKGHZZAP37ABTAGE + (ANZ_DKGHZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKGHZ_ZAP37ABTAGE );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP37TABELLE[i].ZAP37LOEKZ, "J", DEZAPDKGHZZAP37LOEKZ + (ANZ_DKGHZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKGHZ_ZAP37LOEKZ ); 
			}
			else
			{
				DoubleToString(p->FEE_PCT, L_DEZAPDKGHZ_ZAP37GEB, N_DEZAPDKGHZ_ZAP37GEB);
				AvoidOverflow( m_String, des[DEZAPDKGHZZAP37GEB].laenge); 
				CONV( d->ZAP37TABELLE[i].ZAP37GEB, m_String, DEZAPDKGHZZAP37GEB + (ANZ_DKGHZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKGHZ_ZAP37GEB );
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
}

/*** CONVERT-DKKGR ************************************************************/

 bool ConvertDkkgr( dezapdkkgrO *d, dezapccustomergroupSTR *p, struct AUFB des[], rterror rc )
 {
	int i, k;
	int j = ANZ_DKKGR_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKKGR_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP42TABELLE[i].ZAP42KGR,"  ",L_DEZAPDKKGR_ZAP42KGR) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA42, SATZART_DKKGR, DEZAPDKKGRZAPSA42, L_DEZAPDKKGR_ZAPSA42 );

			LongToString(p->CUSTOMERGROUPNO);
			CONV( d->ZAP42TABELLE[i].ZAP42KGR, m_String, DEZAPDKKGRZAP42KGR + (ANZ_DKKGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKKGR_ZAP42KGR );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP42TABELLE[i].ZAP42LOEKZ, "J", DEZAPDKKGRZAP42LOEKZ + (ANZ_DKKGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKKGR_ZAP42LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP42TABELLE[i].ZAP42TEXT, p->NAME,			DEZAPDKKGRZAP42TEXT + (ANZ_DKKGR_FELDER_PRO_ELEMENT * i),	L_DEZAPDKKGR_ZAP42TEXT );
				CONV( d->ZAP42TABELLE[i].ZAP42BER,	p->SALES_RESTR_PH,	DEZAPDKKGRZAP42BER + (ANZ_DKKGR_FELDER_PRO_ELEMENT * i),	L_DEZAPDKKGR_ZAP42BER );

				LongToString(p->BLOCK_FLAG);
				ASSERT( d->ZAP42TABELLE[i].ZAP42SPERRKZ, m_String ); 

				LongToString(p->BASISNATRA_FLAG);
				ASSERT( d->ZAP42TABELLE[i].ZAP42FREIKZ, m_String ); 

				/* Flag-Tabelle aus interner Tabelle versorgen */
				for (k = 0; k < ANZ_DKKGR_TABELEMENTE; k++)
				{
					LongToString(dkkgr_flags[k]);
					CONV( d->ZAP42TABELLE[i].ZAP42KGRTAB[k].ZAP42TFLAG, m_String, DEZAPDKKGRZAP42TFLAG + k, L_DEZAPDKKGR_ZAP42TFLAG );
				}
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
}

/*** CONVERT-DKAUA ************************************************************/

 bool ConvertDkaua( dezapdkauaO *d, dezapcordertypeSTR *p, struct AUFB des[], rterror rc )
 {

	int i, k;
	int j = ANZ_DKAUA_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKAUA_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP53TABELLE[i].ZAP53AART,"  ",L_DEZAPDKAUA_ZAP53AART) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA53, SATZART_DKAUA, DEZAPDKAUAZAPSA53, L_DEZAPDKAUA_ZAPSA53 );

			CONV( d->ZAP53TABELLE[i].ZAP53AART, p->CSCORDERTYPE, DEZAPDKAUAZAP53AART + (ANZ_DKAUA_FELDER_PRO_ELEMENT * i), L_DEZAPDKAUA_ZAP53AART );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP53TABELLE[i].ZAP53LOEKZ, "J", DEZAPDKAUAZAP53LOEKZ + (ANZ_DKAUA_FELDER_PRO_ELEMENT * i), L_DEZAPDKAUA_ZAP53LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP53TABELLE[i].ZAP53TEXT, p->NAME, DEZAPDKAUAZAP53TEXT + (ANZ_DKAUA_FELDER_PRO_ELEMENT * i),	L_DEZAPDKAUA_ZAP53TEXT );

				/* Flag-Tabelle aus interner Tabelle versorgen */
				for (k = 0; k < ANZ_DKAUA_TABELEMENTE; k++)
				{
					LongToString(dkaua_flags[k]);
					CONV( d->ZAP53TABELLE[i].ZAP53AUATAB[k].ZAP53TFLAG, m_String, DEZAPDKAUAZAP53TFLAG + k, L_DEZAPDKAUA_ZAP53TFLAG );
				}
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else 
		return FALSE;
}

/*** CONVERT-DKMVS ************************************************************/

 bool ConvertDkmvs( dezapdkmvsO *d, dezapcmonthvirtsortSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKMVS_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKMVS_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP45TABELLE[i].ZAP45MOVISO,"    ",L_DEZAPDKMVS_ZAP45MOVISO) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA45, SATZART_DKMVS, DEZAPDKMVSZAPSA45, L_DEZAPDKMVS_ZAPSA45 );

			LongToString(p->MONTHLYVIRTUALGROUP);
			CONV( d->ZAP45TABELLE[i].ZAP45MOVISO, m_String, DEZAPDKMVSZAP45MOVISO + (ANZ_DKMVS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMVS_ZAP45MOVISO );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP45TABELLE[i].ZAP45LOEKZ, "J", DEZAPDKMVSZAP45LOEKZ + (ANZ_DKMVS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMVS_ZAP45LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP45TABELLE[i].ZAP45BEZ, p->NAME, DEZAPDKMVSZAP45BEZ + (ANZ_DKMVS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMVS_ZAP45BEZ );

			    LongToString(p->TYPE);
				CONV( d->ZAP45TABELLE[i].ZAP45ART, m_String, DEZAPDKMVSZAP45ART + (ANZ_DKMVS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMVS_ZAP45ART );

			    LongToString(p->ASSORTMENT_TYPE);
				CONV( d->ZAP45TABELLE[i].ZAP45SORT, m_String, DEZAPDKMVSZAP45SORT + (ANZ_DKMVS_FELDER_PRO_ELEMENT * i), L_DEZAPDKMVS_ZAP45SORT );

			    LongToString(p->HIGHPRICEFLAG);
			    ASSERT( d->ZAP45TABELLE[i].ZAP45HOPR, m_String );
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
}

/*** CONVERT-DKLLV ************************************************************

 bool ConvertDkllv( dezapdkllvO *d, dezapccustservicesSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKLLV_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKLLV_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP46TABELLE[i].ZAP46LNR,"    ",L_DEZAPDKLLV_ZAP46LNR) || (i == j))
		{
			// beim ersten F¸llen Satzart miteinstellen 
			if (i == 0)
				CONV( d->ZAPSA46, SATZART_DKLLV, DEZAPDKLLVZAPSA46, L_DEZAPDKLLV_ZAPSA46 );

			LongToString(p->SERVICE_NO);
			CONV( d->ZAP46TABELLE[i].ZAP46LNR, m_String, DEZAPDKLLVZAP46LNR + (ANZ_DKLLV_FELDER_PRO_ELEMENT * i), L_DEZAPDKLLV_ZAP46LNR );

			// jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen 
			if ( rc == eof )
			{
 				CONV( d->ZAP46TABELLE[i].ZAP46LOEKZ, "J", DEZAPDKLLVZAP46LOEKZ + (ANZ_DKLLV_FELDER_PRO_ELEMENT * i), L_DEZAPDKLLV_ZAP46LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP46TABELLE[i].ZAP46BEZ, p->NAME, DEZAPDKLLVZAP46BEZ + (ANZ_DKLLV_FELDER_PRO_ELEMENT * i), L_DEZAPDKLLV_ZAP46BEZ );

			    LongToString(p->SERVICETYPENO);
				CONV( d->ZAP46TABELLE[i].ZAP46ART, m_String, DEZAPDKLLVZAP46ART + (ANZ_DKLLV_FELDER_PRO_ELEMENT * i), L_DEZAPDKLLV_ZAP46ART );
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
} */

/*** CONVERT-DKRBF ************************************************************/

 bool ConvertDkrbf( dezapdkrbfO *d, dezapcdiscformSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKRBF_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKRBF_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP47TABELLE[i].ZAP47RBF,"     ",L_DEZAPDKRBF_ZAP47RBF) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA47, SATZART_DKRBF, DEZAPDKRBFZAPSA47, L_DEZAPDKRBF_ZAPSA47 );

			LongToString(p->DISCOUNTFORMNO);
			CONV( d->ZAP47TABELLE[i].ZAP47RBF, m_String, DEZAPDKRBFZAP47RBF + (ANZ_DKRBF_FELDER_PRO_ELEMENT * i), L_DEZAPDKRBF_ZAP47RBF );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP47TABELLE[i].ZAP47LOE, "J", DEZAPDKRBFZAP47LOE + (ANZ_DKRBF_FELDER_PRO_ELEMENT * i), L_DEZAPDKRBF_ZAP47LOE ); 
			}
			else
			{
				CONV( d->ZAP47TABELLE[i].ZAP47BEZ, p->NAME, DEZAPDKRBFZAP47BEZ + (ANZ_DKRBF_FELDER_PRO_ELEMENT * i), L_DEZAPDKRBF_ZAP47BEZ );

			    LongToString(p->ACTIVE_FLAG);
				/* RR 20.01.22: Wert 1:1 ¸bertragen wegen neuer Werte 2 & 3 
			    ASSERT( d->ZAP47TABELLE[i].ZAP47AKT, m_String ); */
				CONV( d->ZAP47TABELLE[i].ZAP47AKT, m_String, DEZAPDKRBFZAP47AKT + (ANZ_DKRBF_FELDER_PRO_ELEMENT * i), L_DEZAPDKRBF_ZAP47AKT );

			    LongToStringWithLength(p->KINDOFDISCOUNT, L_DEZAPDKRBF_ZAP47ART);
				CONV( d->ZAP47TABELLE[i].ZAP47ART, m_String, DEZAPDKRBFZAP47ART + (ANZ_DKRBF_FELDER_PRO_ELEMENT * i), L_DEZAPDKRBF_ZAP47ART );

			    LongToStringWithLength(p->RELEVANT_BABR, L_DEZAPDKRBF_ZAP47BABRREL);
				CONV( d->ZAP47TABELLE[i].ZAP47BABRREL, m_String, DEZAPDKRBFZAP47BABRREL + (ANZ_DKRBF_FELDER_PRO_ELEMENT * i), L_DEZAPDKRBF_ZAP47BABRREL );
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
}

/*** CONVERT-DKLKR ************************************************************/

 bool ConvertDklkr( dezapdklkrO *d, dezapcstoragecriteriaSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKLKR_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKLKR_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP48TABELLE[i].ZAP48KRNR,"   ",L_DEZAPDKLKR_ZAP48KRNR) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA48, SATZART_DKLKR, DEZAPDKLKRZAPSA48, L_DEZAPDKLKR_ZAPSA48 );

			LongToString(p->STORAGECRITERIANO);
			CONV( d->ZAP48TABELLE[i].ZAP48KRNR, m_String, DEZAPDKLKRZAP48KRNR + (ANZ_DKLKR_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKR_ZAP48KRNR );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP48TABELLE[i].ZAP48LOEKZ, "J", DEZAPDKLKRZAP48LOEKZ + (ANZ_DKLKR_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKR_ZAP48LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP48TABELLE[i].ZAP48NAME, p->NAME, DEZAPDKLKRZAP48NAME + (ANZ_DKLKR_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKR_ZAP48NAME );

				CONV( d->ZAP48TABELLE[i].ZAP48AFNAME, p->FIELD_NAME_DKART,  DEZAPDKLKRZAP48AFNAME + (ANZ_DKLKR_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKR_ZAP48AFNAME );
				CONV( d->ZAP48TABELLE[i].ZAP48AFTYP,  p->FIELD_TYPE_DKART,  DEZAPDKLKRZAP48AFTYP  + (ANZ_DKLKR_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKR_ZAP48AFTYP );
				CONV( d->ZAP48TABELLE[i].ZAP48AFWERT, p->FIELD_VALUE_DKART, DEZAPDKLKRZAP48AFWERT + (ANZ_DKLKR_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKR_ZAP48AFWERT );
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
}

/*** CONVERT-DKLKZ ************************************************************/

 bool ConvertDklkz( dezapdklkzO *d, dezapcintrastatcountrySTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKLKZ_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKLKZ_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP49TABELLE[i].ZAP49LKZ,"  ",L_DEZAPDKLKZ_ZAP49LKZ) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA49, SATZART_DKLKZ, DEZAPDKLKZZAPSA49, L_DEZAPDKLKZ_ZAPSA49 );

			CONV( d->ZAP49TABELLE[i].ZAP49LKZ, p->COUNTRYCODE, DEZAPDKLKZZAP49LKZ + (ANZ_DKLKZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKZ_ZAP49LKZ );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP49TABELLE[i].ZAP49LOEKZ, "J", DEZAPDKLKZZAP49LOEKZ + (ANZ_DKLKZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKZ_ZAP49LOEKZ ); 
			}
			else
			{
				CONV( d->ZAP49TABELLE[i].ZAP49IFALKZ, p->IFACODE, DEZAPDKLKZZAP49IFALKZ + (ANZ_DKLKZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKZ_ZAP49IFALKZ );
				CONV( d->ZAP49TABELLE[i].ZAP49NAME,   p->COUNTRY, DEZAPDKLKZZAP49NAME   + (ANZ_DKLKZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKZ_ZAP49NAME );

			    LongToString(p->COUNTRYNO);
				CONV( d->ZAP49TABELLE[i].ZAP49ISNR, m_String, DEZAPDKLKZZAP49ISNR + (ANZ_DKLKZ_FELDER_PRO_ELEMENT * i), L_DEZAPDKLKZ_ZAP49ISNR );

			    LongToString(p->HOMECOUNTRYFLAG);
			    ASSERT( d->ZAP49TABELLE[i].ZAP49EIGEN, m_String );

			    LongToString(p->EUROPEANUNIONFLAG);
			    ASSERT( d->ZAP49TABELLE[i].ZAP49EU, m_String );

			    LongToString(p->ALPHANUMERICPOSTALCODEFLAG);
			    ASSERT( d->ZAP49TABELLE[i].ZAP49ALPHAPLZ, m_String );
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
}

/*** CONVERT-DKFOK ************************************************************/

 bool ConvertDkfok( dezapdkfokO *d, dezapcformtypesSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKFOK_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKFOK_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP51TABELLE[i].ZAP51FORMKZ,"  ",L_DEZAPDKFOK_ZAP51FORMKZ) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA51, SATZART_DKFOK, DEZAPDKFOKZAPSA51, L_DEZAPDKFOK_ZAPSA51 );
			}

			CONV( d->ZAP51TABELLE[i].ZAP51FORMKZ, p->FORMTYPE, DEZAPDKFOKZAP51FORMKZ + (ANZ_DKFOK_FELDER_PRO_ELEMENT * i), L_DEZAPDKFOK_ZAP51FORMKZ );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP51TABELLE[i].ZAP51LOEKZ, "J", DEZAPDKFOKZAP51LOEKZ + (ANZ_DKFOK_FELDER_PRO_ELEMENT * i), L_DEZAPDKFOK_ZAP51LOEKZ );
			}
			else
			{
				CONV( d->ZAP51TABELLE[i].ZAP51BEZ, p->NAME_LONG, DEZAPDKFOKZAP51BEZ + (ANZ_DKFOK_FELDER_PRO_ELEMENT * i), L_DEZAPDKFOK_ZAP51BEZ );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-DKSPS ************************************************************/

 bool ConvertDksps( dezapdkspsO *d, dezapcshipperSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKSPS_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKSPS_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP52TABELLE[i].ZAP52SPNR,"     ",L_DEZAPDKSPS_ZAP52SPNR) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA52, SATZART_DKSPS, DEZAPDKSPSZAPSA52, L_DEZAPDKSPS_ZAPSA52 );

			LongToString(p->SHIPPERNO);
			CONV( d->ZAP52TABELLE[i].ZAP52SPNR, m_String, DEZAPDKSPSZAP52SPNR + (ANZ_DKSPS_FELDER_PRO_ELEMENT * i), L_DEZAPDKSPS_ZAP52SPNR );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP52TABELLE[i].ZAP52LOE, "J", DEZAPDKSPSZAP52LOE + (ANZ_DKSPS_FELDER_PRO_ELEMENT * i), L_DEZAPDKSPS_ZAP52LOE ); 
			}
			else
			{
				CONV( d->ZAP52TABELLE[i].ZAP52NAME, p->NAME,    DEZAPDKSPSZAP52NAME + (ANZ_DKSPS_FELDER_PRO_ELEMENT * i), L_DEZAPDKSPS_ZAP52NAME );
				CONV( d->ZAP52TABELLE[i].ZAP52STR,  p->STRASSE, DEZAPDKSPSZAP52STR  + (ANZ_DKSPS_FELDER_PRO_ELEMENT * i), L_DEZAPDKSPS_ZAP52STR );
				CONV( d->ZAP52TABELLE[i].ZAP52PLZ,  p->PLZ,     DEZAPDKSPSZAP52PLZ  + (ANZ_DKSPS_FELDER_PRO_ELEMENT * i), L_DEZAPDKSPS_ZAP52PLZ );
				CONV( d->ZAP52TABELLE[i].ZAP52ORT,  p->ORT,     DEZAPDKSPSZAP52ORT  + (ANZ_DKSPS_FELDER_PRO_ELEMENT * i), L_DEZAPDKSPS_ZAP52ORT );

			    LongToString(p->SIREN_NO);
				CONV( d->ZAP52TABELLE[i].ZAP52SIREN, m_String, DEZAPDKSPSZAP52SIREN + (ANZ_DKSPS_FELDER_PRO_ELEMENT * i), L_DEZAPDKSPS_ZAP52SIREN );
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
}

/*** CONVERT-DKPRO ************************************************************/

 bool ConvertDkpro( dezapdkproO *d, dezapcpromotionsSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKPRO_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKPRO_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP54TABELLE[i].ZAP54PROMONR,"     ",L_DEZAPDKPRO_ZAP54PROMONR) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
				CONV( d->ZAPSA54, SATZART_DKPRO, DEZAPDKPROZAPSA54, L_DEZAPDKPRO_ZAPSA54 );

			LongToString(p->PROMOTION_NO);
			CONV( d->ZAP54TABELLE[i].ZAP54PROMONR, m_String, DEZAPDKPROZAP54PROMONR + (ANZ_DKPRO_FELDER_PRO_ELEMENT * i), L_DEZAPDKPRO_ZAP54PROMONR );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
 				CONV( d->ZAP54TABELLE[i].ZAP54LOE, "J", DEZAPDKPROZAP54LOE + (ANZ_DKPRO_FELDER_PRO_ELEMENT * i), L_DEZAPDKPRO_ZAP54LOE ); 
			}
			else
			{
				CONV( d->ZAP54TABELLE[i].ZAP54NAME, p->NAME,    DEZAPDKPROZAP54NAME + (ANZ_DKPRO_FELDER_PRO_ELEMENT * i), L_DEZAPDKPRO_ZAP54NAME );

			    LongToString(p->PROMOTION_TYPE);
				CONV( d->ZAP54TABELLE[i].ZAP54TYP, m_String,	DEZAPDKPROZAP54TYP + (ANZ_DKPRO_FELDER_PRO_ELEMENT * i), L_DEZAPDKPRO_ZAP54TYP );

			    LongToString(p->PRIORITY);
				CONV( d->ZAP54TABELLE[i].ZAP54PRIO, m_String,	DEZAPDKPROZAP54PRIO + (ANZ_DKPRO_FELDER_PRO_ELEMENT * i), L_DEZAPDKPRO_ZAP54PRIO );

				ASSERT( d->ZAP54TABELLE[i].ZAP54KZKOPR,		p->ADDONPROMODISCOK );
				ASSERT( d->ZAP54TABELLE[i].ZAP54KZKOSR,		p->ADDONSTDDISCOK );
				ASSERT( d->ZAP54TABELLE[i].ZAP54KZNSWEB,	p->SNOTBYSALESEWEB );
			}

			break;
		}
	}
			
	if (i == j)
		return TRUE;
	else
		return FALSE;
}

/*** CONVERT-DKAIN ************************************************************/

 void ConvertDkain( dezapdkainO *d, dezapcregistersSTR *p, struct AUFB des[], rterror rc )
 {
	CONV( d->ZAPSA55,			SATZART_DKAIN,				DEZAPDKAINZAPSA55,		L_DEZAPDKAIN_ZAPSA55 );

	/* Filiale immer mit 00 initialisieren (wird im PSA410 aus VLK geholt) */
	CONV( d->ZAP55FIL,			"00",						DEZAPDKAINZAP55FIL,		L_DEZAPDKAIN_ZAP55FIL );

	CONV( d->ZAP55WIRK,			p->MINISTRYPRODUCTCODE,		DEZAPDKAINZAP55WIRK,	L_DEZAPDKAIN_ZAP55WIRK );

	if ( rc == eof )
	{
 		CONV( d->ZAP55LOEKZ,	"J",						DEZAPDKAINZAP55LOEKZ,	L_DEZAPDKAIN_ZAP55LOEKZ ); 
	}
	else
	/* Aufteilung der INN auf 2 Felder, weil im WandelCobol der Puffer nur mit maximal 256 definiert ist und es sonst zu einem Segmentation Fault kommt */
	/* Hinweis: WandelCobol() ist im File ascitocobol.c implementiert, das sich wiederum in der Bibliothek libtpld befindet (im TFS unter pharmos.base.libtpld) */
	{
		CONV( d->ZAP55INN1,		p->INTERNONPROPNAME,		DEZAPDKAINZAP55INN1,	L_DEZAPDKAIN_ZAP55INN1 );
		CONV( d->ZAP55INN2,		p->INTERNONPROPNAME + 240,	DEZAPDKAINZAP55INN2,	L_DEZAPDKAIN_ZAP55INN2 );
	}

	return;
}

/*** CONVERT-DKGAL **********************************************************

 void ConvertDkgal( dezapdkgalO *d, dezapcgaloartSTR *a, struct AUFB des[], rterror rc )
 {
   CONV( d->ZAPSA23, SATZART_DKGAL, DEZAPDKGALZAPSA23, L_DEZAPDKGAL_ZAPSA23 );

   LongToString(a->ARTICLENO);
   CONV( d->ZAP23PZN, m_String, DEZAPDKGALZAP23PZN, L_DEZAPDKGAL_ZAP23PZN );

	// jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen 
	if ( rc == eof )
	{
		CONV( d->ZAP23LOEKZ, "J", DEZAPDKGALZAP23LOEKZ, L_DEZAPDKGAL_ZAP23LOEKZ );
	}
	else
	{
		CONV( d->ZAP23EAN, a->EAN, DEZAPDKGALZAP23EAN, L_DEZAPDKGAL_ZAP23EAN );
		CONV( d->ZAP23WGR, a->ASSORT_KEY, DEZAPDKGALZAP23WGR, L_DEZAPDKGAL_ZAP23WGR );
		CONV( d->ZAP23IKS, a->IKS_CAT, DEZAPDKGALZAP23IKS, L_DEZAPDKGAL_ZAP23IKS );
		CONV( d->ZAP23ANRH, a->SUPP_PROD_NO, DEZAPDKGALZAP23ANRH, L_DEZAPDKGAL_ZAP23ANRH );

		LongToString(a->REPL_ARTICLE);
		CONV( d->ZAP23AANR, m_String, DEZAPDKGALZAP23AANR, L_DEZAPDKGAL_ZAP23AANR );

		CONV( d->ZAP23KKCODE, a->INS_CODE, DEZAPDKGALZAP23KKCODE, L_DEZAPDKGAL_ZAP23KKCODE );
		CONV( d->ZAP23IKSNR, a->IKS_KEY, DEZAPDKGALZAP23IKSNR, L_DEZAPDKGAL_ZAP23IKSNR );
		CONV( d->ZAP23GF, a->GRD_FR_CODE, DEZAPDKGALZAP23GF, L_DEZAPDKGAL_ZAP23GF );

		LongToString(a->EXPIRY);
		CONV( d->ZAP23LDAU, m_String, DEZAPDKGALZAP23LDAU, L_DEZAPDKGAL_ZAP23LDAU );

		LongToString(a->DATEVALIDFROM);
		CONV( d->ZAP23GUELT, m_String, DEZAPDKGALZAP23GUELT, L_DEZAPDKGAL_ZAP23GUELT );

		CONV( d->ZAP23RETBED, a->RET_DELAY, DEZAPDKGALZAP23RETBED, L_DEZAPDKGAL_ZAP23RETBED );
		CONV( d->ZAP23LTEMP, a->STOCK_TEMP, DEZAPDKGALZAP23LTEMP, L_DEZAPDKGAL_ZAP23LTEMP );
		CONV( d->ZAP23GHNR, a->COMP_KEY, DEZAPDKGALZAP23GHNR, L_DEZAPDKGAL_ZAP23GHNR );
		CONV( d->ZAP23FOCODE, a->FORMCODE, DEZAPDKGALZAP23FOCODE, L_DEZAPDKGAL_ZAP23FOCODE );

		DoubleToString(a->PRICE_PHARM, L_DEZAPDKGAL_ZAP23AEP, N_DEZAPDKGAL_ZAP23AEP);
		AvoidOverflow( m_String, des[DEZAPDKGALZAP23AEP].laenge); 
		CONV( d->ZAP23AEP, m_String, DEZAPDKGALZAP23AEP, L_DEZAPDKGAL_ZAP23AEP );
  
		DoubleToString(a->PRICE_PUBL, L_DEZAPDKGAL_ZAP23AVP, N_DEZAPDKGAL_ZAP23AVP);
		AvoidOverflow( m_String, des[DEZAPDKGALZAP23AVP].laenge); 
		CONV( d->ZAP23AVP, m_String, DEZAPDKGALZAP23AVP, L_DEZAPDKGAL_ZAP23AVP );
  
        char cFeld[2] = {0};

		if (strncmp(a->DEPOTCODE, "Y", 1) == 0)
			cFeld[0] = 'J';
		else
			cFeld[0] = 'N';

		CONV( d->ZAP23NG, cFeld, DEZAPDKGALZAP23NG, L_DEZAPDKGAL_ZAP23NG );

		if (strncmp(a->VAT_CODE, "2", 1) == 0)
			cFeld[0] = 'J';
		else
			cFeld[0] = 'N';

		CONV( d->ZAP23MWST, cFeld, DEZAPDKGALZAP23MWST, L_DEZAPDKGAL_ZAP23MWST );

		if (strncmp(a->HOSPCODE, "Y", 1) == 0)
			cFeld[0] = 'J';
		else
			cFeld[0] = 'N';

		CONV( d->ZAP23KLIP, cFeld, DEZAPDKGALZAP23KLIP, L_DEZAPDKGAL_ZAP23KLIP );

		if (strncmp(a->STOCK_FRIDGE, "1", 1) == 0 || strncmp(a->STOCK_FRIDGE, "2", 1) == 0)
			cFeld[0] = 'J';
		else
			cFeld[0] = 'N';

		CONV( d->ZAP23KUEHL, cFeld, DEZAPDKGALZAP23KUEHL, L_DEZAPDKGAL_ZAP23KUEHL );

		if (strncmp(a->INS_CODE_LIM, "Y", 1) == 0)
			cFeld[0] = 'J';
		else
			cFeld[0] = 'N';

		CONV( d->ZAP23KKLIM, cFeld, DEZAPDKGALZAP23KKLIM, L_DEZAPDKGAL_ZAP23KKLIM );

		if (strncmp(a->SALECODE, "H", 1) == 0)
			cFeld[0] = 'J';
		else
			cFeld[0] = 'N';

		CONV( d->ZAP23AHDL, cFeld, DEZAPDKGALZAP23AHDL, L_DEZAPDKGAL_ZAP23AHDL );

		if (strncmp(a->STOCK_NARC, "Y", 1) == 0)
			cFeld[0] = 'J';
		else
			cFeld[0] = 'N';

		CONV( d->ZAP23BTM, cFeld, DEZAPDKGALZAP23BTM, L_DEZAPDKGAL_ZAP23BTM );

		if (strncmp(a->STOCK_TOX, "Y", 1) == 0)
			cFeld[0] = 'J';
		else
			cFeld[0] = 'N';

		CONV( d->ZAP23GIFT, cFeld, DEZAPDKGALZAP23GIFT, L_DEZAPDKGAL_ZAP23GIFT );

		// Punkte aus Therapiegruppe eliminieren 
		DiscardNotNumerics(a->THERAP_KEY);
		CONV( d->ZAP23THERGRP, m_String, DEZAPDKGALZAP23THERGRP, L_DEZAPDKGAL_ZAP23THERGRP );
	}

	return;
 } */

/*** CONVERT-CGALONAM *******************************************************

 void ConvertCgalonam( dezapdkgalO *d, dezapcgalonamSTR *g, struct AUFB des[] )
 {
	Upper(g->COMP_NAME);
				  
	// vielleicht werden sp‰ter auch mal Einheit, Bezeichnung und Darreichform versorgt 
	switch( *g->LANG_CODE )
	{
		case 'D': CONV( d->ZAP23TOTBEZ, g->COMP_NAME, DEZAPDKGALZAP23TOTBEZ, L_DEZAPDKGAL_ZAP23TOTBEZ );
                  break;
		case 'F': CONV( d->ZAP23TOTBEZF, g->COMP_NAME, DEZAPDKGALZAP23TOTBEZF, L_DEZAPDKGAL_ZAP23TOTBEZF );
				  break;
	}

	return;
 } */

/*** CONVERT-DKGAH **********************************************************

 void ConvertDkgah( dezapdkgahO *d, dezapcgalocomSTR *a, struct AUFB des[], rterror rc )
 {
   char chnr[14] = {0};
   CONV( d->ZAPSA24, SATZART_DKGAH, DEZAPDKGAHZAPSA24, L_DEZAPDKGAH_ZAPSA24 );

   sprintf(chnr, "%13.13ld", a->COMP_NO);
   CONV( d->ZAP24HNR, chnr, DEZAPDKGAHZAP24HNR, L_DEZAPDKGAH_ZAP24HNR );

	// jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen 
	if ( rc == eof )
	{
		CONV( d->ZAP24LOEKZ, "J", DEZAPDKGAHZAP24LOEKZ, L_DEZAPDKGAH_ZAP24LOEKZ );
	}
	else
	{
		CONV( d->ZAP24EAN, a->EAN, DEZAPDKGAHZAP24EAN, L_DEZAPDKGAH_ZAP24EAN );

		Upper(a->NAME_SHORT);
		strncpy(d->ZAP24KUBZ, a->NAME_SHORT, strlen(a->NAME_SHORT));

		Upper(a->NAME_LONG);
		strncpy(d->ZAP24NAME, a->NAME_LONG, strlen(a->NAME_LONG));

		Upper(a->STREET);
		strncpy(d->ZAP24STR, a->STREET, strlen(a->STREET));

		Upper(a->COUNTRY);
		strncpy(d->ZAP24LKZ, a->COUNTRY, strlen(a->COUNTRY));

        char cplz[8] = {0};

		// wg. rechtsbuendiger Aufbereitung der PLZ 
		sprintf(cplz, "%7.7d", atoi(a->POSTAL_CODE));
		strncpy(d->ZAP24PLZ, cplz, L_DEZAPDKGAH_ZAP24PLZ);

		Upper(a->CITY_NAME);
		strncpy(d->ZAP24ORT, a->CITY_NAME, strlen(a->CITY_NAME));

		Upper(a->PHONE_NO);
		strncpy(d->ZAP24RTEL, a->PHONE_NO, strlen(a->PHONE_NO));

		Upper(a->PHONE_NO_2);
		strncpy(d->ZAP24BTEL, a->PHONE_NO_2, strlen(a->PHONE_NO_2));

		Upper(a->FAX_NO);
		strncpy(d->ZAP24FAX, a->FAX_NO, strlen(a->FAX_NO));
	}

   return;
 } */

/*** CONVERT-DKRIS ************************************************************/

 void ConvertDkris( dezapdkrisO *d, dezapzartverkSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKRIS_TABELEMENTE - 1;

	for (i = 0; i < ANZ_DKRIS_TABELEMENTE; i++)
	{
		if(!strncmp(d->ZAP08TABELLE[i].ZAP08TPZN,"       ", L_DEZAPDKRIS_ZAP08TPZN) || (i == j))
		{
			/* beim ersten F¸llen alle Felder auﬂerhalb der Tabelle miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA08, SATZART_DKRIS, DEZAPDKRISZAPSA08, L_DEZAPDKRIS_ZAPSA08 );

				/* Filiale immer mit 00 initialisieren (wird im PSA425 aus VLK geholt) */
				CONV( d->ZAP08FIL1, "00", DEZAPDKRISZAP08FIL1, L_DEZAPDKRIS_ZAP08FIL1 );
				CONV( d->ZAP08FIL2, "00", DEZAPDKRISZAP08FIL2, L_DEZAPDKRIS_ZAP08FIL2 );

				/* Kurzbezeichnung, Original-PZN und HNR erstmal nur initialisieren, mal sehen, ob die noch gef¸llt werden muessen */
				CONV( d->ZAP08KUBZ, "            ", DEZAPDKRISZAP08KUBZ, L_DEZAPDKRIS_ZAP08KUBZ );
				CONV( d->ZAP08OPZN, "0000000", DEZAPDKRISZAP08OPZN, L_DEZAPDKRIS_ZAP08OPZN );
				CONV( d->ZAP08HNR, "00000", DEZAPDKRISZAP08HNR, L_DEZAPDKRIS_ZAP08HNR );

				LongToString(p->ARTIKEL_NR_BAS);
				CONV( d->ZAP08PZN1, m_String, DEZAPDKRISZAP08PZN1, L_DEZAPDKRIS_ZAP08PZN1 );
				CONV( d->ZAP08PZN2, m_String, DEZAPDKRISZAP08PZN2, L_DEZAPDKRIS_ZAP08PZN2 );
			}

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP08LOEKZ, "J", DEZAPDKRISZAP08LOEKZ, L_DEZAPDKRIS_ZAP08LOEKZ );
			}
			else
			{
				LongToString(p->ARTIKEL_NR_VERK);
				CONV( d->ZAP08TABELLE[i].ZAP08TPZN, m_String, DEZAPDKRISZAP08TPZN + (ANZ_DKRIS_FELDER_PRO_TABELEMENT * i), L_DEZAPDKRIS_ZAP08TPZN );

				ASSERT( d->ZAP08TABELLE[i].ZAP08TKZMAN, p->MANUELL );
				CONV( d->ZAP08TABELLE[i].ZAP08TFIL1, "00000", DEZAPDKRISZAP08TFIL1 + (ANZ_DKRIS_FELDER_PRO_TABELEMENT * i), L_DEZAPDKRIS_ZAP08TFIL1 );
				CONV( d->ZAP08TABELLE[i].ZAP08TSORKZ, p->SORTIMENT, DEZAPDKRISZAP08TSORKZ + (ANZ_DKRIS_FELDER_PRO_TABELEMENT * i), L_DEZAPDKRIS_ZAP08TSORKZ );
				CONV( d->ZAP08TABELLE[i].ZAP08TVKART, p->VERK_ART, DEZAPDKRISZAP08TVKART + (ANZ_DKRIS_FELDER_PRO_TABELEMENT * i), L_DEZAPDKRIS_ZAP08TVKART );
				CONV( d->ZAP08TABELLE[i].ZAP08TFIL2, "               ", DEZAPDKRISZAP08TFIL2 + (ANZ_DKRIS_FELDER_PRO_TABELEMENT * i), L_DEZAPDKRIS_ZAP08TFIL2 );
			}

			break;
		}
	}
			
	return;
}

/*** CONVERT-DKEGR ************************************************************/

 bool ConvertDkegr( dezapdkegrO *d, dezapcpharmgrpSTR *p, struct AUFB des[], rterror rc )
 {
	int i;
	int j = ANZ_DKEGR_ELEMENTE - 1;

	for (i = 0; i < ANZ_DKEGR_ELEMENTE; i++)
	{
		if(!strncmp(d->ZAP12TABELLE[i].ZAP12EKG,"     ",L_DEZAPDKEGR_ZAP12EGR) || (i == j))
		{
			/* beim ersten F¸llen Satzart miteinstellen */
			if (i == 0)
			{
				CONV( d->ZAPSA12, SATZART_DKEGR, DEZAPDKEGRZAPSA12, L_DEZAPDKEGR_ZAPSA12 );
			}

			CONV( d->ZAP12TABELLE[i].ZAP12EKG, p->PHARMACYGROUPID, DEZAPDKEGRZAP12EKG + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12EGR );

			/* jetzt sollen auch Lˆschungen in die DEZAP, daher rc abfragen und LOEKZ versorgen */
			if ( rc == eof )
			{
				CONV( d->ZAP12TABELLE[i].ZAP12LOEKZ, "J", DEZAPDKEGRZAP12LOEKZ + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12LOE );
			}
			else
			{
				CONV( d->ZAP12TABELLE[i].ZAP12BEZ, p->GROUP_NAME, DEZAPDKEGRZAP12BEZ + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12BEZ );
				CONV( d->ZAP12TABELLE[i].ZAP12AURAB, p->GROUP_TYPE, DEZAPDKEGRZAP12AURAB + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12AURAB );

				DoubleToString(p->PERCENT, L_CPHARMGRP_PERCENT, N_CPHARMGRP_PERCENT);
				AvoidOverflow( m_String, des[DEZAPDKEGRZAP12PROZ].laenge); 
				CONV( d->ZAP12TABELLE[i].ZAP12PROZ, m_String, DEZAPDKEGRZAP12PROZ + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12PROZ );

				DoubleToString(p->CONTRIBUTION, L_CPHARMGRP_CONTRIBUTION, N_CPHARMGRP_CONTRIBUTION);
				AvoidOverflow( m_String, des[DEZAPDKEGRZAP12BEITRAG].laenge); 
				CONV( d->ZAP12TABELLE[i].ZAP12BEITRAG, m_String, DEZAPDKEGRZAP12BEITRAG + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12BEITRAG );

				LongToString(p->CUSTOMERNO);
				CONV( d->ZAP12TABELLE[i].ZAP12IDF, m_String, DEZAPDKEGRZAP12IDF + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12IDF );

				CONV( d->ZAP12TABELLE[i].ZAP12BEAB, "00000", DEZAPDKEGRZAP12BEAB + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12BEAB );

				ASSERT( d->ZAP12TABELLE[i].ZAP12OMGEKO, p->OMG_OWN_CONT );
				ASSERT( d->ZAP12TABELLE[i].ZAP12AEPBAS, p->PRICE_BASIS_PURCH );
				ASSERT( d->ZAP12TABELLE[i].ZAP12OMGRF,  p->RECLAIM_OMG_DISC );

				LongToString(p->SPECIALGROUP);
				CONV( d->ZAP12TABELLE[i].ZAP12SOGRP, m_String, DEZAPDKEGRZAP12SOGRP + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12SOGRP );

				LongToString(p->SPECIALGROUPREFNO);
				CONV( d->ZAP12TABELLE[i].ZAP12REFNR, m_String, DEZAPDKEGRZAP12REFNR + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12REFNR );

				LongToString(p->GROUPING_VIS);
				CONV( d->ZAP12TABELLE[i].ZAP12GRPVIS, m_String, DEZAPDKEGRZAP12GRPVIS + (ANZ_DKEGR_FELDER_PRO_ELEMENT * i), L_DEZAPDKEGR_ZAP12GRPVIS );
			}

			break;
		}
	}
			
	if (i == j)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*** CONVERT-SECONDARY ********************************************************/
 void ConvertSecondary( dezapO *d, dezapzartsekbezSTR *s, struct AUFB des[] )
 {
   CONV( d->ZAPSBEZ, s->ARTIKEL_NAME, DEZAPZAPSBEZ, L_DEZAP_ZAPSBEZ );

   /* SKUBZ wird aus Platzgr¸nden nicht mehr versorgt, sondern im PSA425 aus SBEZ ermittelt */
   /* CONV( d->ZAPSKUBZ, s->ARTIKEL_MC, DEZAPZAPSKUBZ, L_DEZAP_ZAPSKUBZ ); */

   /* FILL4 ist jetzt ELEKTRO */
   /* CONV( d->ZAPFILL4, " ", DEZAPZAPFILL4, L_DEZAP_ZAPFILL4 ); */

   return;
 }

/*** CONVERT-DEPOSIT ********************************************************/
void ConvertDeposit( dezapO *d, dezapcdeposittypesSTR *s, struct AUFB des[] )
{
	DoubleToString(s->DEPOSIT_VALUE, L_CDEPOSITTYPES_DEPOSIT_VALUE, N_CDEPOSITTYPES_DEPOSIT_VALUE);
	AvoidOverflow( m_String, des[DEZAPZAPPFAND].laenge); 
    CONV( d->ZAPPFAND, m_String, DEZAPZAPPFAND, L_DEZAP_ZAPPFAND ); 

	return;
}

/*** CONVERT-GOODSGROUP *******************************************************/
 void ConvertGoodsgroup( dezapO *d, dezapzartwgSTR *g, struct AUFB des[], parameter *p )
 {
   switch( *g->ART )
   {
     case '1': CONV( d->ZAPIMSC, g->WARENGRUPPE, DEZAPZAPIMSC, L_DEZAP_ZAPIMSC );
                       break;
     case '2': CONV( d->ZAPWGR, g->WARENGRUPPE, DEZAPZAPWGR, L_DEZAP_ZAPWGR );
                       break;
     case '3': CONV( d->ZAPTHER, g->WARENGRUPPE, DEZAPZAPTHER, L_DEZAP_ZAPTHER );
                       break;
     case '4': CONV( d->ZAPABDC, g->WARENGRUPPE, DEZAPZAPABDC, L_DEZAP_ZAPABDC );
                       break;
/*   case '5': CONV( d->ZAPSART, g->WARENGRUPPE, DEZAPZAPSART, L_DEZAP_ZAPSART );
                       break; */
	 case '6': CONV( d->ZAPBGN,    g->WARENGRUPPE, DEZAPZAPBGN,    L_DEZAP_ZAPBGN );
                       break;
	 case '7': CONV( d->ZAPKEYTXT, g->WARENGRUPPE, DEZAPZAPKEYTXT, L_DEZAP_ZAPKEYTXT );
                       break;
	 case '9': CONV( d->ZAPWGRRGRP, g->WARENGRUPPE, DEZAPZAPWGRRGRP, L_DEZAP_ZAPWGRRGRP );
                       break;
     case 'B': CONV( d->ZAPTHER, g->WARENGRUPPE, DEZAPZAPTHER, L_DEZAP_ZAPTHER );
                       break;
     case 'D': CONV( d->ZAPSPARTTYP, g->WARENGRUPPE, DEZAPZAPSPARTTYP, L_DEZAP_ZAPSPARTTYP );
                       break;
   /* Wirkstoffgruppe ab 18.05.14 nicht mehr aus zartikel, sondern aus zartwg */
   /* 03.03.17: nicht mehr f¸r ÷sterreich, da Werte dort alphanumerisch und DEZAP-Zielfeld numerisch */
     case 'E': strncpy (d->ZAPWIRK, "00000", 5);
			   if (!IsCountry(p->Kuerzel, "A"))
				   CONV( d->ZAPWIRK, g->WARENGRUPPE, DEZAPZAPWIRK, L_DEZAP_ZAPWIRK );
                       break;

   /* Clubnummer steht 5-stellig mit f¸hrenden Nullen in zartwg und muss daher entsprechend aufbereitet werden */
     case 'F':	LongToString(atoi (g->WARENGRUPPE));
				CONV( d->ZAPVCLUBNR, m_String, DEZAPZAPVCLUBNR, L_DEZAP_ZAPVCLUBNR );
                       break;
   }

   /* in ÷sterreich 2. Saisonart statt 1. ins Pharmos stellen */

   if ((IsCountry(p->Kuerzel, "A") && g->ART[0] == 'A') || 
	   (!IsCountry(p->Kuerzel, "A") && g->ART[0] == '5'))
	{
	   CONV( d->ZAPSART, g->WARENGRUPPE, DEZAPZAPSART, L_DEZAP_ZAPSART );
	}

	/* alte BTM-Gruppe nicht mehr aus zartwg f¸llen */
	CONV( d->ZAPBTMGRP, "000", DEZAPZAPBTMGRP, L_DEZAP_ZAPBTMGRP );

/* CONV( d->ZAPSVON, "00000", DEZAPZAPSVON, L_DEZAP_ZAPSVON );
   CONV( d->ZAPSBIS, "00000", DEZAPZAPSBIS, L_DEZAP_ZAPSBIS );
   CONV( d->ZAPSRYT, "000", DEZAPZAPSRYT, L_DEZAP_ZAPSRYT ); */

   return;
 }

/*** CONVERT-CODES *******************************************************/

 void ConvertCodes( dezapO *d, dezapcarticlecodesSTR *g, struct AUFB des[], parameter *p )
 {
   switch( g->CODE_TYPE )
   {
	   case 2: CONV( d->ZAPATCCODE, g->ARTICLE_CODE, DEZAPZAPATCCCODE, L_DEZAP_ZAPATCCODE );
                  break;
   }

   if (IsCountry(p->Kuerzel, "RS") && g->CODE_TYPE == 17)
   {
		CONV( d->ZAPTHER,		g->ARTICLE_CODE,		DEZAPZAPTHER,		L_DEZAP_ZAPTHER );
		CONV( d->ZAPUEBEINH,	g->ARTICLE_CODE + 5,	DEZAPZAPUEBEINH,	L_DEZAP_ZAPUEBEINH );
   }

   if (IsCountry(p->Kuerzel, "BG") && g->CODE_TYPE == 23)
   {
		CONV( d->ZAPWIRK,		g->ARTICLE_CODE,		DEZAPZAPWIRK,		L_DEZAP_ZAPWIRK );
   }

   return;
 }

/*** CONVERT-FIXEDAMOUNT ******************************************************/

 void ConvertFixedAmount( dezapO *d, dezapzartfeb2STR *a, struct AUFB des[] )
 {
	DoubleToString(a->FESTBETRAG2, L_ZARTFEB2_FESTBETRAG2, N_ZARTFEB2_FESTBETRAG2);
	AvoidOverflow( m_String, des[DEZAPZAPMISK].laenge); 
    CONV( d->ZAPMISK, m_String, DEZAPZAPMISK, L_DEZAP_ZAPMISK ); 

    return;
 }

/*** CONVERT-ARTICLEEXT ******************************************************/

 void ConvertArticleExt( dezapO *d, dezapcarticleextSTR *a )
 {
    LongToString(a->SHORTEXPIRYFLAG);
	ASSERT( d->ZAPKUVERF, m_String );

    return;
 }

/*** CONVERT-ZAUTIDEMSPERRE ******************************************************/

 void ConvertZautidemsperre( dezapO *d, dezapzautidemsperreSTR *a, struct AUFB des[] )
 {
    if (des) {}

    LongToString(a->DATUMGUELTIGAB);
	ASSERT( d->ZAPPAEND, m_String );

    return;
 }

/*** CONVERT-BATCHINFO ******************************************************/

 void ConvertBatchInfo( dezapO *d, dezapzartikelSTR *a, dezapzartswitzerlandSTR *s, struct AUFB des[], parameter *p )
 {
    if (des) {}

	/* echter Chargenartikel ---> Wert "C" */
   if (a->CHARGENARTIKEL[0] == '1')
	  strncpy(d->ZAPCHARGE, "C", 1);

	/* Chargenpr¸fung im WE ---> Wert "A" --> wird nicht mehr benˆtigt, da GI jetzt direkt die Tabelle cgibatchentry liest 
   else if (g->COMPANY_CODE > 0)
	  strncpy(d->ZAPCHARGE, "A", 1); */

	/* Chargenpr¸fung bei der Endkontrolle (nur in D seit 04.07.17 f¸r Arzneimittel statt RX / OTC) ---> Wert "E" */
   else if (IsCountry(p->Kuerzel, "D") && 
			a->ARZNEIMITTEL[0] == '1')
	  strncpy(d->ZAPCHARGE, "E", 1);

	/* Chargenpr¸fung bei der Endkontrolle II (nur in A) ---> Wert "E" */
   else if (IsCountry(p->Kuerzel, "A") && 
			(a->APOTHEKENPFL[0] == '1' || 
			 a->REZEPTPFL[0] == '1'))
	  strncpy(d->ZAPCHARGE, "E", 1);

	/* Chargenpr¸fung bei der Endkontrolle III (nur in CH); am 04.07.17 ge‰ndert von A-E auf A-B ---> Wert "E" */
   else if (IsCountry(p->Kuerzel, "CH") &&
		    s->IKS_CODE[0] >= 'A' &&
		    s->IKS_CODE[0] <= 'B')
	  strncpy(d->ZAPCHARGE, "E", 1);

	/* keine Chargenpr¸fung ---> Wert "N" */
   else
	  strncpy(d->ZAPCHARGE, "N", 1);

    return;
 }

/*** CONVERT-ARTVE ******************************************************/

 void ConvertArtve( dezapO *d, dezapartveSTR *a, struct AUFB des[], parameter *p )
 {
	// f¸r Frankreich ZAPBUEN und ZAPMINM f¸llen
    if (IsCountry(p->Kuerzel, "F") &&
		p->Prewhole == 0)
	{
		LongToString(a->VERPACKEINHEIT2);
		CONV( d->ZAPBUEN, m_String, DEZAPZAPBUEN, L_DEZAP_ZAPBUEN );

		LongToString(a->VERPACKEINHEIT3);
		CONV( d->ZAPMINM, m_String, DEZAPZAPMINM, L_DEZAP_ZAPMINM );
	}

	/* f¸r die Schweiz ZAPVE f¸llen */
    if (IsCountry(p->Kuerzel, "CH"))
	{
		LongToString(a->ORIGINALKARTON);
		CONV( d->ZAPVE, m_String, DEZAPZAPVE, L_DEZAP_ZAPVE );
	}

	/* f¸r Kroatien ZAPBUEN f¸llen */
	if (IsCountry(p->Kuerzel, "HR"))
	{
		LongToString(a->ORIGINALKARTON);
		AvoidOverflow( m_String, des[DEZAPZAPBUEN].laenge - 1);	/* -1, weil AvoidOverflow() f¸r Gleitkommawerte vorgesehen war und wegen dem Komma die ¸bergebene L‰nge um 1 erhˆht wird */
		CONV( d->ZAPBUEN, m_String, DEZAPZAPBUEN, L_DEZAP_ZAPBUEN );
	}

	/* f¸r Bulgarien ZAPMINM f¸llen */
	if (IsCountry(p->Kuerzel, "BG"))
	{
		LongToString(a->ORIGINALKARTON);
		AvoidOverflow( m_String, des[DEZAPZAPMINM].laenge - 1);	/* -1, weil AvoidOverflow() f¸r Gleitkommawerte vorgesehen war und wegen dem Komma die ¸bergebene L‰nge um 1 erhˆht wird */
		CONV( d->ZAPMINM, m_String, DEZAPZAPMINM, L_DEZAP_ZAPMINM );
	}

    return;
 }

/*** CONVERT-AUSTRIA ******************************************************/

 void ConvertAustria( dezapO *d, dezapzartaustriaSTR *a, struct AUFB des[] )
 {
    strncpy( d->ZAPNALI, a->NACHLIEFERUNG, L_DEZAP_ZAPNALI );  /* im Pharmos stehen auch die Werte 0/1 */

    ASSERT( d->ZAPWART, a->WECHSELARTIKEL );
    ASSERT( d->ZAPKZBUEN, a->BUENDELPACKUNG );

	/* Chargenkennzeichen wird jetzt ¸ber zartikel versorgt 
	ASSERT( d->ZAPCHARGE, a->CHARGENARTIKEL );
    */

	/* Umsetzung Chargenartikel von "J" auf "C" 
	if (strncmp(d->ZAPCHARGE, "J", 1) == 0)
	{
		strncpy(d->ZAPCHARGE, "C", 1);
	} */

	/* im Pharmos stehen in dem Feld IMSC das OELHV_SORT (1-4) und HV_BOX (5)*/
	char IMSC[6] = {0};

	strncpy (IMSC, a->OELHV_SORT, 4);
	strncat (IMSC, a->HV_BOX, L_ZARTAUSTRIA_HV_BOX);
	strncpy ( d->ZAPIMSC, IMSC, L_DEZAP_ZAPIMSC);

	/* Umsetzung Vertriebsbindungen ÷sterreich */
    ASSERT( d->ZAPVBED, a->VERTRBIND_PLPL );
    ASSERT( d->ZAPVBA, a->VERTRBIND_S1S5 );
    ASSERT( d->ZAPVBB, a->VERTRBIND_VPL );
    ASSERT( d->ZAPVBC, a->VERTRBIND_SP );
/*  ASSERT( d->ZAPVB1, NONE ); */
    ASSERT( d->ZAPVB1, a->VERTRBIND_BDORF );
    ASSERT( d->ZAPVB2, GetCompare( a->VERTRBIND_COMPTANT , COMPTANT ) );
    ASSERT( d->ZAPVB3, GetCompare( a->VERTRBIND_COMPTANT, NI_COMPTANT ) );
    ASSERT( d->ZAPVB4, a->VERTRBIND_NEUFORM );

	/* andere Bedeutung f¸r SIW und ORPA in ÷sterreich --> deaktiviert RR 03.03.17
	ASSERT( d->ZAPSIW, a->RUECK_MON_VOR_VERF ); */
	
	/* Generika-Kennzeichnung wird nun benˆtigt ---> ZAPIHNR statt ZAPORPA verwenden */
	/*CONV( d->ZAPORPA, a->RUECK_MON_VOR_VERF, DEZAPZAPORPA, L_DEZAP_ZAPORPA );*/
	
	CONV( d->ZAPIHNR, a->RUECK_MON_VOR_VERF, DEZAPZAPORPA, L_DEZAP_ZAPORPA );

    if (d->ZAPIHNR[0] == '0')
		d->ZAPIHNR[0] = ' ';

   /* RR 03.03.17: neues Feld */
   LongToString(a->GH_LAGERUNG_VERBOTEN);
   ASSERT( d->ZAPGHLGVB, m_String);

    return;
 }

/*** CONVERT-CROATIA ******************************************************/

 void ConvertCroatia( dezapO *d, dezapzartcroatiaSTR *a, struct AUFB des[] )
 {
    if (des) {}

	/* Chargenkennzeichen wird jetzt ¸ber zartikel versorgt 
	ASSERT( d->ZAPCHARGE, a->BATCHARTICLE );
    */

	/* Umsetzung Chargenartikel von "J" auf "C" 
	if (strncmp(d->ZAPCHARGE, "J", 1) == 0)
	{
		strncpy(d->ZAPCHARGE, "C", 1);
	} */

	/* Umsetzung Vertriebsbindungen Kroatien */
    ASSERT( d->ZAPVBED, a->DISTR_RESTR_MED2A );
    ASSERT( d->ZAPVBA, a->DISTR_RESTR_MED2B3 );
    ASSERT( d->ZAPVBB, a->DISTR_RESTR_HUDRUG );
    ASSERT( d->ZAPVBC, a->DISTR_RESTR_BRDRUG );
    ASSERT( d->ZAPVB1, a->DISTR_RESTR_ALCOH );
    ASSERT( d->ZAPVB2, a->DISTR_RESTR_VETMED );
    ASSERT( d->ZAPVB3, a->DISTR_RESTR_VEDRUG );
    ASSERT( d->ZAPVB4, a->DISTR_RESTR_HUDRVE );

    return;
 }

/*** CONVERT-CROATIA-SPECIAL ******************************************************/

 void ConvertCroatiaSpecial( dezapO *d, dezapzartcroatiaSTR *a, dezapzartpreisSTR *p, struct AUFB des[] )
 {
    if (des) {}

	/* PAEND setzen, wenn Umrechnung nur aufgrund von Euro-Faktor-ƒnderung */
	if ( a->DATE_EXCHANGE_CALC == GetCurrentDate() &&
		 a->DATE_EXCHANGE_CALC > p->DATUMGUELTIGAB )	  
	{
		strncpy(d->ZAPPAEND, "U", 1);
	}

    return;
 }

/*** CONVERT-BULGARIA ******************************************************/

 void ConvertBulgaria( dezapO *d, dezapzartbulgariaSTR *a, dezapzartpreisSTR *p, struct AUFB des[] )
 {
	double dGepna;
	int hts;
	const char *fun = "ConvertBulgaria";
	char cINFGR[3] = {0};

/* 22.09.09: ANNUAL_INV_REB_PCT nicht mehr ber¸cksichtigen (mail Julian Nedelchev) */
/*	dGepna = p->GROSSO - (p->GROSSO * ((a->INVOICE_REBATE_PCT + a->ANNUAL_INV_REB_PCT) / 100.0)); */

/* 27.09.10: REBATE_IN_KIND_PCT mitber¸cksichtigen (mail Boyan Karaivanov)
	dGepna = p->GROSSO - (p->GROSSO * (a->INVOICE_REBATE_PCT / 100.0)); */

	dGepna = p->GROSSO * (1 - (a->INVOICE_REBATE_PCT / 100.0)) / (1 + (a->REBATE_IN_KIND_PCT / 100.0));

	Runden (&dGepna, 2);

	/* Test 
	printf("\n%d %f", a->ARTICLENO, dGepna); */

	DoubleToString(dGepna, 9, 2);
	hts = AvoidOverflow( m_String, des[DEZAPZAPGEPNA].laenge); 
    CONV( d->ZAPGEPNA, m_String, DEZAPZAPGEPNA, L_DEZAP_ZAPGEPNA );

	if (hts >= 10)
	{
		WriteLog( fun, 100, "Artikel %d hat Gepna >= 1.000.000!", a->ARTICLENO ); 
		CONV( d->ZAPHTGEPNA, "0", DEZAPZAPHTGEPNA, L_DEZAP_ZAPHTGEPNA );
	}
	else
	{
		LongToString(hts);
		CONV( d->ZAPHTGEPNA, m_String, DEZAPZAPHTGEPNA, L_DEZAP_ZAPHTGEPNA );
	}

	LongToStringWithLength(a->HI_STICKER, 1);
	ASSERT( d->ZAPGST, m_String );

	DoubleToString(a->CREDIT_NOTE_PRICE, L_ZARTBULGARIA_CREDIT_NOTE_PRICE, N_ZARTBULGARIA_CREDIT_NOTE_PRICE); 
	AvoidOverflow( m_String, des[DEZAPZAPWEBU].laenge); 
	CONV( d->ZAPWEBU, m_String, DEZAPZAPWEBU, L_DEZAP_ZAPWEBU ); 

	sprintf( cINFGR, "%02d", a->PRICE_GROUP );
	CONV( d->ZAPINFGR, cINFGR, DEZAPZAPINFGR, L_DEZAP_ZAPINFGR );

	/* Umsetzung Vertriebsbindungen Bulgarien */
	if (strncmp(cINFGR, "04", 2) != 0)
		strncpy(d->ZAPVBED, "J", 1);

	LongToStringWithLength(a->DISTR_RESTR_NODRST, 1);
	ASSERT( d->ZAPVBA, m_String );

	/* 4 neue Felder versorgen RR 16.02.12 */
	DoubleToString(a->SUPPL_HI_REIMB, L_ZARTBULGARIA_SUPPL_HI_REIMB, N_ZARTBULGARIA_SUPPL_HI_REIMB); 
	AvoidOverflow( m_String, des[DEZAPZAPERSTWERT].laenge); 
	CONV( d->ZAPERSTWERT, m_String, DEZAPZAPERSTWERT, L_DEZAP_ZAPERSTWERT ); 

	DoubleToString(a->YEARLY_BONUS_PCT, L_ZARTBULGARIA_YEARLY_BONUS_PCT, N_ZARTBULGARIA_YEARLY_BONUS_PCT); 
	AvoidOverflow( m_String, des[DEZAPZAPKDIFF].laenge); 
	CONV( d->ZAPKDIFF, m_String, DEZAPZAPKDIFF, L_DEZAP_ZAPKDIFF ); 

	DoubleToString(a->OTHER_REBATES_PCT, L_ZARTBULGARIA_OTHER_REBATES_PCT, N_ZARTBULGARIA_OTHER_REBATES_PCT); 
	AvoidOverflow( m_String, des[DEZAPZAPKDIFFA].laenge); 
	CONV( d->ZAPKDIFFA, m_String, DEZAPZAPKDIFFA, L_DEZAP_ZAPKDIFFA ); 

	DoubleToString(a->SUPPL_DISCOUNT_PCT, L_ZARTBULGARIA_SUPPL_DISCOUNT_PCT, N_ZARTBULGARIA_SUPPL_DISCOUNT_PCT); 
	AvoidOverflow( m_String, des[DEZAPZAPERSTPROZ].laenge); 
	CONV( d->ZAPERSTPROZ, m_String, DEZAPZAPERSTPROZ, L_DEZAP_ZAPERSTPROZ ); 

    return;
 }

/*** CONVERT-SERBIA ******************************************************/

 void ConvertSerbia( dezapO *d, dezapzartserbiaSTR *a, struct AUFB des[] )
 {
	char cINFGR[3] = {0};

	LongToStringWithLength(a->PACKAGE_INSERT, 1);
	ASSERT( d->ZAPWART, m_String );

	sprintf( cINFGR, "%02d", a->ARTICLETYPE );
	CONV( d->ZAPINFGR, cINFGR, DEZAPZAPINFGR, L_DEZAP_ZAPINFGR );

	LongToStringWithLength(a->REFUNDTYPE, 1);
	strncpy(d->ZAPZUZA, m_String, 1);

	LongToStringWithLength(a->CERTIFICATEFLAG, 1);
	ASSERT( d->ZAPGST, m_String );

	LongToString(a->MAXPAYMENTTARGET);
	CONV( d->ZAPMGUEINH, m_String, DEZAPZAPMGUEINH, L_DEZAP_ZAPMGUEINH );

	LongToString(a->PACK_SIZE);
	CONV( d->ZAPMINM, m_String, DEZAPZAPMINM, L_DEZAP_ZAPMINM );

	return;
 }

/*** CONVERT-SWITZERLAND ******************************************************/

 void ConvertSwitzerland( dezapO *d, dezapzartswitzerlandSTR *a, struct AUFB des[] )
 {
    ASSERT( d->ZAPKZBUEN, a->BUENDELPACKUNG );
	CONV( d->ZAPIHNR, a->IKS_CODE, DEZAPZAPIHNR, L_DEZAP_ZAPIHNR );

	/* Umsetzung Vertriebsbindungen Schweiz */
	ASSERT( d->ZAPVBED, a->VERTRBIND_NUR_APO );
	ASSERT( d->ZAPVBA, a->VERTRBIND_NUR_SPIT );
	ASSERT( d->ZAPVBB, a->VERTRBIND_KUENZLE );
	ASSERT( d->ZAPVBC, a->VERTRBIND_INLAND );
	ASSERT( d->ZAPVB1, a->VERTRBIND_KANTONAL );
	ASSERT( d->ZAPVB2, a->VERTRBIND_PREWHOLE );
	ASSERT( d->ZAPVB3, a->VERTRBIND_LISTE_C );
	ASSERT( d->ZAPVB4, a->VERTRBIND_LISTE_D );

	/* Swissmedic-Registrierungsnummer in der Schweiz in die Therapiegruppe einstellen */
	if (a->SWISSMEDIC_REGNR == 0)
	{
		strncpy (d->ZAPTHER, "00000", 5);
	}
	else
	{
		LongToStringWithLength(a->SWISSMEDIC_REGNR, L_DEZAP_ZAPTHER);
		CONV( d->ZAPTHER, m_String, DEZAPZAPTHER, L_DEZAP_ZAPTHER );
	}

	/* und den Zusatz in die Wirkstoffgruppe einstellen */
	if (a->SWISSMEDIC_ZUSATZ == 0)
	{
		strncpy (d->ZAPWIRK, "00000", 5);
	}
	else
	{
		LongToStringWithLength(a->SWISSMEDIC_ZUSATZ, L_DEZAP_ZAPWIRK);
		CONV( d->ZAPWIRK, m_String, DEZAPZAPWIRK, L_DEZAP_ZAPWIRK );
	}

	/* neue Felder f¸r Prewhole */
	DoubleToString(a->WARNPROZVORPLM, L_ZARTSWITZERLAND_WARNPROZVORPLM, N_ZARTSWITZERLAND_WARNPROZVORPLM + 1); /* + 1, weil Feld in DB 1 NK-Stelle hat und Ausgabefeld 2 */
	AvoidOverflow( m_String, des[DEZAPZAPERSTPROZ].laenge); 
	CONV( d->ZAPERSTPROZ, m_String, DEZAPZAPERSTPROZ, L_DEZAP_ZAPERSTPROZ ); 

	LongToString(a->PFLICHTLAGERMENGE);
	CONV( d->ZAPMBEST, m_String, DEZAPZAPMBEST, L_DEZAP_ZAPMBEST );

	if (a->ANTIBIOTIKA_FNR == 0)
	{
		strncpy (d->ZAPIMSC, "00000", 5);
	}
	else
	{
		LongToStringWithLength(a->ANTIBIOTIKA_FNR, L_DEZAP_ZAPIMSC);
		CONV( d->ZAPIMSC, m_String, DEZAPZAPIMSC, L_DEZAP_ZAPIMSC );
	}

	/* wenn ein Wert im Feld MIGCD steht, dann MEDK = 'J' (= Produkt der MiGeL) */
	ASSERT( d->ZAPMEDK, a->MIGCD );

    return;
 }

/*** CONVERT-FRANCE ******************************************************/

 void ConvertFrance( dezapO *d, dezapzartfranceSTR *a, struct AUFB des[], parameter *p )
 {
	DoubleToString(a->REIMBURSEMENT_VAL, L_ZARTFRANCE_REIMBURSEMENT_VAL, N_ZARTFRANCE_REIMBURSEMENT_VAL); 
	AvoidOverflow( m_String, des[DEZAPZAPERSTWERT].laenge); 
	CONV( d->ZAPERSTWERT, m_String, DEZAPZAPERSTWERT, L_DEZAP_ZAPERSTWERT ); 

	DoubleToString(a->REIMBURSEMENT_PERC, L_ZARTFRANCE_REIMBURSEMENT_PERC, N_ZARTFRANCE_REIMBURSEMENT_PERC); 
	AvoidOverflow( m_String, des[DEZAPZAPERSTPROZ].laenge); 
	CONV( d->ZAPERSTPROZ, m_String, DEZAPZAPERSTPROZ, L_DEZAP_ZAPERSTPROZ ); 

	LongToString(a->QTY_SUBMULTIPLE);
	CONV( d->ZAPMGUEINH, m_String, DEZAPZAPMGUEINH, L_DEZAP_ZAPMGUEINH );

	CONV( d->ZAPUEBEINH, a->UNIT_MULTIPLE, DEZAPZAPUEBEINH, L_DEZAP_ZAPUEBEINH );
	CONV( d->ZAPCBL, a->CODE_BLOQUAGE, DEZAPZAPCBL, L_DEZAP_ZAPCBL );

	/* Umsetzung Vertriebsbindungen Frankreich */
	ASSERT( d->ZAPVBED, a->DISTR_RESTR_LEGALL );
	ASSERT( d->ZAPVBA, a->DISTR_RESTR_BREIZH );
	ASSERT( d->ZAPVBB, a->DISTR_RESTR_HOSP );

	/* neu 09.10.2019 */
	LongToStringWithLength(a->DISTR_RESTR_EXPORT, 1);
	ASSERT( d->ZAPVBC, m_String );
	
	/* spezielle Rabattgruppe in INFGR (rechte 2 Stellen) */
	if (p->Prewhole != 1)
	{
		strncpy(d->ZAPINFGR, a->REBATE_GROUP_SPEC + 1, 2);
	}

	return;
 }

/* Aufbereitung double-Werte als String f¸r CONV-Makro */
/*  void DoubleToString (double source, int vorkomma, int nachkomma) */
 void DoubleToString (double source, int laenge_gesamt, int nachkomma)
 {
/*	int length = vorkomma + nachkomma + 1 + 1; Version vor 25.07.2013: nachkomma ist ja aber in vorkomma enthalten */
/*      ja, und wenn man's nicht so (also zu lang) macht, dann geht serbien nicht mehr :(                              */
/*	int length = laenge_gesamt + 1 + 1 + 1;  1 Byte f¸r's Komma, 1 Byte f¸r's Line-End, 1 Byte f¸r's Vielleicht-Minus  - obsolete*/
	 
	char format[20] = {0};
	sprintf(format, "%c-.%df", '%', nachkomma);
	
	/*sprintf auto-terminates*/
	sprintf(m_String, format, source);
 }

/* Aufbereitung long-Werte als String f¸r CONV-Makro */
 void LongToString (long source)
 {
	char format[20] = {0};
	sprintf(format, "%c-11d", '%');
	
	sprintf(m_String, format, source);
	m_String[10] = '\0';
 }

/* Aufbereitung long-Werte als String mit exakt definierter L‰nge f¸r CONV-Makro (Felder, die im cobolbuf.h als character definiert sind) */
 void LongToStringWithLength (long source, int length)
 {
	char format[20] = {0};

	sprintf(format, "%c%d.%dd", '%', length, length);
	sprintf(m_String, format, source);
	m_String[length] = '\0';
 }

/* Aufbereitung long-Werte als String f¸r CONV-Makro inklusive Pr¸fung, ob Datum schon erreicht (f¸r AH- / RR-Datum) */
 void LongToStringDateCheck (long source, long checkdate)
 {
	if (source > checkdate)
		source = 0;

	LongToString (source);
 }

/* Jahrhundert bei Datumswerten abschneiden (DEZAP nur 6-stellig) */
 long CutCentury (long source)
 {
	while (source >= 1000000)
	{
		 source -= 1000000;
	}

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
	for (size_t i = 0; i < strlen(s); i++)
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

	for (size_t i = 0; i < strlen(s); i++)
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
	char temp[3] = {0};

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

/* ¸berz‰hlige Stellen (z.B. bei 6-stelligem AEP) eliminieren */
 int AvoidOverflow (char *s, int length)
 {
	 int i, j, k, l, m;

	 Trim(s);
	 i = strlen(s);
	 j = (length + 1);	/* +1 wegen enthaltenem Komma */

	 if (i <= j)
	 {
		 return 0;
	 }
	 
	 l = 0;
	 m = i - j;

	 for (k = 0; k <= i; k++)
	 {
		 /* eliminierte Stellen wertm‰ﬂig ermitteln */
		 if (k < m)
		 {
			l *= 10;

			if (s[k] >= 49 && s[k] <= 57)
				l += (s[k] - 48);
		 }

         s[k] = s[k + m];
	 }

	 return l;
 }

/* 1:1 kopiert aus PhxUtil.cpp */
void Runden( double *wert, int stellen )
{
	if ( stellen >= 0 )
	{
		int i;
		double rund;
		double result;
		double rest;

		rund = 1.0;
		for ( i = 0; i < stellen; i++ ) rund *= 10.0;

		i = 1;
		result = *wert;
		if ( result < 0.0 )
		{
			result = -result;
			i = -1;
		}

		rest = modf( result*rund + 0.5, &result );

		if ( rest >= 0.99999999 ) 
			result += 1.0;

		result /= rund;
		if ( i == 1 )
			*wert = result;
		else
			*wert = -result;
	}
}

void InitCustGrpFlagArray( )
{
	int i;

	/* Flag-Tabelle initialisieren */
	for (i = 0; i < ANZ_DKKGR_TABELEMENTE; i++)
	{
		dkkgr_flags[i] = 0;
	}
}

void FillCustGrpFlagArray( short scustomergrpflag, short sindex_skkgr )
{
	dkkgr_flags[sindex_skkgr - 1] = scustomergrpflag;
}

void InitOrderTypeFlagArray( )
{
	int i;

	/* Flag-Tabelle initialisieren */
	for (i = 0; i < ANZ_DKAUA_TABELEMENTE; i++)
	{
		dkaua_flags[i] = 0;
	}
}

void FillOrderTypeFlagArray( short sordertypeflag, short sindex_sdkaua )
{
	dkaua_flags[sindex_sdkaua - 1] = sordertypeflag;
}
