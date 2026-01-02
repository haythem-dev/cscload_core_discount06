#include "../../../cdm_version.h"

const char* getVersion()
{
    // in binary embedded full version string
    return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.3.7: zplignart 22.04.2024 : KT";
}

/*!
\page page28 zplignart
__________________________________________________________________________
\version	1.3.7
\date		22.04.2024
\internal
- KT: SR-23013365: Wird ein Artikel bei der Logindex-Einspielung auf AH gesetzt, wird automatisch auch eine Retourensperre gesetzt
- KT: CPR-210673: Automatisches Setzen von zartikel.chargenartikel bei Logindex-Einspielung
\endinternal
__________________________________________________________________________
\version	1.3.6
\date		14.09.2021
\internal
- TA: CPR-200938 Aufnahme neuer Voodoo-Table-Header für erweiterte zartpreis Tabelle
\endinternal
__________________________________________________________________________
\version	1.3.5
\date		23.02.2018
\internal
- TH: CPR-171010 Zurücksetzen des RR- Datums
\endinternal
__________________________________________________________________________
\version	1.3.4
\date		02.11.2017
\internal
- TH: I-17041832 Übernahme Grosso auch bei herst_prozent < 0
\endinternal
__________________________________________________________________________
\version	1.3.3
\date		14.06.2017
\internal
- TH: SR-17055491 keine Änderung des Artikelnamens, wenn datum_ah = 0 war und bleibt
- TH: SR-17066347 GTIN14 / code_type 19 ohne führende Nullen; Übernahme H-Sätze von LogIndex korrigiert
\endinternal
__________________________________________________________________________
\version	1.3.2
\date		09.05.2017
\internal
- TH: SR-17040503 retourensperre bei Neuanlagen = 0
\endinternal
__________________________________________________________________________
\version	1.3.1
\date		24.03.2017
\internal
- TH: SR-17028701 zapflege auch mit Preisdatum (in der Zukunft) schreiben
- TH: SR-17036614 AH- Datum aus Artikelname auch wieder entfernen.
- TH: SR-17035559 PRODUCT.blood --> zartikel.chargenartikel (nicht mehr zartikel.tfg!)
- Änderung bei Ermittlung zartikel.arzneimittel / zartikel.impfstoff
\endinternal
___________________________________________________________________________
\version	1.3.0
\date		11.01.2017
\internal
- TH: CR-14D152
\endinternal
___________________________________________________________________________
\version	1.2.2
\date		06.09.2016
\internal
- TH: SR-16070839 GTIN14 --> carticlecodes mit code_type = 19
\endinternal
___________________________________________________________________________
\version	1.2.1
\date		19.07.2016
\internal
- TH: SR-16060256 Übernahme herstel.zentralppelist --> zartikel.zentralppelist bei Neuaufnahmen
\endinternal
___________________________________________________________________________
\version	1.2.0
\date		08.06.2016
\internal
- TH: CR-16D039 Änderung Preisübernahme (LBP, GEP, HerstProz); Übernahme cdso1 als articlecode (type 21)
\endinternal
___________________________________________________________________________
\version	1.1.9
\date		05.02.2016
\internal
- SR-16010608: Übernahme GEP analog AVP
\endinternal
___________________________________________________________________________
\version	1.1.8
\date		24.11.2015
\internal
- SR-15061064: Nicht- IKS = alles, was nicht A-E ist
\endinternal
___________________________________________________________________________
\version	1.1.7
\date		16.07.2015
\internal
- Erweiterung zartikel
\endinternal
___________________________________________________________________________
\version	1.1.6
\date		27.04.2015
\internal
- SR-15017599: Nachkommastellen bei Einheit berücksichtigen.
\endinternal
___________________________________________________________________________
\version	1.1.5
\date		21.04.2015
\internal
- CR-14D138: Setzen zartikel.datum_ah.
\endinternal
___________________________________________________________________________
\version	1.1.4
\date		09.04.2015
\internal
- SR-15014882: CDBG = A --> psychotrop = N, btm = 1.
\endinternal
___________________________________________________________________________
\version	1.1.3
\date		03.03.15
\internal
- SR-15009529: Zurücksetzen awl_aktiv, Prüflesen dfo, awl1 nie auf 0 zurücksetzen.
\endinternal
___________________________________________________________________________
\version	1.1.2
\date		20.02.2015
\internal
- CR-14D132 = Korrekturen für Neuanlagen.
\endinternal
___________________________________________________________________________
\version	1.1.1
\date		05.02.2015
\internal
- CR-14D132 = ARTNO1 statt COMPNO; Versorgung clioart.hersteller_nr.
\endinternal
___________________________________________________________________________
\version	1.1.0
\date		08.01.2015
\internal
- CR-14D133 = nur tatsächlich geänderte Werte übernehmen; Änderung Protokoll.
\endinternal

*/

/* 1.0.0  11.11.13	Hörath	first shot */
/* 1.0.1  23.12.13	Serial_Number = 0 für ATC- Code */
/* 1.0.2  03.01.14	Eintrag Ersatz_Nr in Vorgänger */
/* 1.0.3  09.01.14	Eintrag Ersatz_Nr_aktiv in Vorgänger */
/* 1.0.4  29.01.14	SR-112613: keine Versorgung des Vorgängers wg Pharmos- Problemen */
/* 1.0.5  11.03.14	Erweiterung zartikel */
/* 1.0.6  10.04.14  wandeln mit neuer zartikel/zartpreis-Struktur */
/* 1.0.7  05.09.14  Verfall- KZ nicht mehr in Abhängigkeit von laufzeitmonate setzen; Übernahme artikel_nr_herst nur bei Neuanlagen. */
/* 1.0.8  05.11.14  BugFix für Preisdatum in der Vergangenheit. */
/* 1.0.9  27.11.14  zapflege für AH- Datum. */
/* 1.1.0  08.01.15  CR-14D133 = nur tatsächlich geänderte Werte übernehmen; Änderung Protokoll. */
/* 1.1.1  05.02.15  CR-14D132 = ARTNO1 statt COMPNO; Versorgung clioart.hersteller_nr. */
/* 1.1.2  20.02.15  CR-14D132 = Korrekturen für Neuanlagen. */
/* 1.1.3  03.03.15  SR-15009529: Zurücksetzen awl_aktiv, Prüflesen dfo, awl1 nie auf 0 zurücksetzen. */
/* 1.1.4  09.04.15  SR-15014882: CDBG = A --> psychotrop = N, btm = 1. */
/* 1.1.5  21.04.15  CR-14D138: Setzen zartikel.datum_ah. */
/* 1.1.6  27.04.15  SR-15017599: Nachkommastellen bei Einheit berücksichtigen. */
/* 1.1.7  16.07.15	Erweiterung zartikel */


/* --- Includes   ------------------------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo/libscsvoodoo.h>
#include "zplignart.h"


static void Usage( char *spBuf )
{
   strcpy( spBuf, "usage:\n" );
}

void ProgUsage(  char *spBuf, const char *spProgname)
{
   Usage( spBuf );
   GenArtUsage( spBuf, spProgname );
   Cliart_Protokol_Usage( spBuf, spProgname );
}

long ProgSelect( int argc, char *argv[], char *spBuf, const char *spProgname )
{
   long lRetCode;

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   if ( strlen( argv[0] ) != 1 )
   {
     lRetCode = 1;
     strcpy( spBuf, "Programm-Teil: " );
     strcat( spBuf, argv[0] );
     strcat( spBuf, " nicht vorhanden" );
     return 1;
   }

   switch ( *argv[0] )
    {
      case '0':
      case '1':
	  case '2':
	  case '4':
		/* order argv[1], argv[0], is correct !!!!!!  */
        if ( argc == 4  )
           lRetCode = GenArtLoop( argv[1], argv[0], argv[2], argv[3], NULL,    spBuf );
        else if ( argc == 5 )
           lRetCode = GenArtLoop( argv[1], argv[0], argv[2], argv[3], argv[4], spBuf );
        else
        {
          lRetCode = 1;
          Usage( spBuf );
          GenArtUsage( spBuf, spProgname );
        }
        break;

      case '3':
        if ( argc == 3 )
        {
          lRetCode = Cliart_Protokol_Loop( argv[1], argv[2], NULL, spBuf );
        }
        else if ( argc == 4 )
        {
          lRetCode = Cliart_Protokol_Loop( argv[1], argv[2], argv[3],spBuf );
        }
        else
        {
          lRetCode = 1;
          Usage( spBuf );
          Cliart_Protokol_Usage(spBuf, spProgname );
        }
        break;

      default:
        lRetCode = 1;
        strcpy( spBuf, "Programm-Teil: " );
        strcat( spBuf, argv[0] );
        strcat( spBuf, " nicht vorhanden" );
        break;
     }
   return lRetCode;
}


