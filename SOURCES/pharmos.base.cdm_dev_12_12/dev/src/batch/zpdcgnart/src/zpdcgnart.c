#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.4.10: zpdcgnart";
}

/*!
\page page12 zpdcgnart Datacare generieren
___________________________________________________________________________________
\version	1.4.10
\date		19.04.2022
\internal
- KT: CPR-210859 Setze Flag 'serial_number_tracking', wenn Medprod-Klasse='K' (AT)
\endinternal
___________________________________________________________________________________
\version	1.4.9
\date		25.02.2021
\internal
- WH: CPR-210023 0% Mwst (AT)
- WH: CPR-201327 Kühlkennzeichnung COVID 19 Impfstoffe (AT)
\endinternal
___________________________________________________________________________________
\version	1.4.8
\date		05.05.2020
\internal
- WH: CPR-200362 neuer Wert für vertrbind_sp
\endinternal

___________________________________________________________________________________
\version	1.4.7
\date		30.07.2019
\internal
- TH: SR-19077822 neue Logik zur Ermittlung von zartikel.nahrungstest
\endinternal
___________________________________________________________________________________
\version	1.4.6
\date		03.07.2019
\internal
- TH: SR-19068900 neuer Wert "W" für DC_ARTIKELGRUPPE
\endinternal
___________________________________________________________________________
\version	1.4.5
\date		27.03.2019
\internal
- TH: init zartikel.chargenartikel bei Neuanlagen in DE & AT
- TH: CPR-190326 neuer Wert "L" für DC_ARTIKELGRUPPE
\endinternal
___________________________________________________________________________________
\version	1.4.4
\date		21.01.2019
\internal
- TH: BatchTracking ==> Übernahme von DC_FAELSCHSICHER / DC_CHARGE nach zartikel.CHARGENARTIKEL wieder aktiviert
\endinternal
___________________________________________________________________________________
\version	1.4.3
\date		12.10.2018
\internal
- TH: Versorgung zaneuheit bei Herstellerwechsel
\endinternal
___________________________________________________________________________________
\version	1.4.2
\date		10.04.2018
\internal
- TH: BatchTracking ==> temporär keine Übernahme von DC_FAELSCHSICHER / DC_CHARGE nach zartikel.CHARGENARTIKEL, bis im Warehouse / MDE alle notwendigen Programme ausgerollt wurden ...
\endinternal
___________________________________________________________________________________
\version	1.4.1
\date		09.01.2018
\internal
- TH: SR-18002614 Psychotrop
- TH: BatchTracking ==> DC_FAELSCHSICHER
\endinternal
___________________________________________________________________________________
\version	1.4.0
\date		16.08.2016
\internal
- TH: CR-16D098 Versorgung artnrbl
\endinternal
___________________________________________________________________________________
\version	1.3.9
\date		01.03.2016
\internal
- TH: CR-15D146 Antibiotikum
\endinternal
________________________________________________________________________
\version	1.3.8
\date		06.11.15
\internal
- TH: Anpassungen wegen 3rd VAT
\endinternal
_______________________________________________________________________________________
\version	1.3.7
\date		17.09.15
\internal
- DZ: CR-15D107 Erweiterung um Biosiegel
\endinternal
_______________________________________________________________________________________
\version	1.3.6
\date		16.07.15
\internal
- TH: Erweiterung zartikel
\endinternal
_______________________________________________________________________________________
\version	1.3.5
\date		06.05.15
\internal
- TH: Übernahme der Skontofähigkeit von zdkwgr.wgr_sktof(J/N) auf zartikel.skontofaehig(1/0).
\endinternal
_______________________________________________________________________________________
\version	1.3.4
\date		10.04.14
\internal
- TH: wandeln mit neuer zartikel/zartpreis-Struktur
\endinternal

*/

/* 1.0.2  15.07.05	Hinz	Nahrungstest aussetzen */
/* 1.0.3  19.07.05	Hinz	Init auf GS_LICHTGESCH */
/* 1.0.4  31.08.05	Raab	nahrungstest ungleich K / Blank nicht überschreiben */
/* 1.0.5  24.10.05  Hinz	Nahrungstest andrucken unabhängig vom Inhalt */
/* 1.0.6. 21.11.05	Hinz	Bei Neuanlage Artikel und Warengruppe 01720 oder 01730 Verfall aktivieren */
/* 1.0.7  16.01.06  Hinz	Bei Zytostatika Darreichform nicht übernehmen */
/* 1.0.8  07.07.08  Raab	Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
							Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.0.9  15.12.08  Raab	zartikel.psychotrop auf "N" setzen, falls andere Kriterien nicht erfüllt */
/* 1.1.0  17.12.08  Raab	Korrektur Rundungsfehler in kf_rund.c */
/* 1.2.0  23.12.09  TH:		neue Datacare- Struktur */
/* 1.2.1  05.01.10  TH:		zusätzliche automatische Übernahmen in zartikel / zartaustria */
/* 1.2.2  24.06.10  Raab    Anpassung in DRFO-Übernahme für Zytostatika */
/* 1.2.3  08.07.10  Raab    Chargenartikel für HNR 1969 nicht übernehmen */
/* 1.2.4  16.08.10  TH:     Schreiben CArticleCodes bei Artikel- Neuanlagen */
/* 1.2.5  14.01.11  TH:     zartikel.NETTOARTIKEL auf 0 setzen, wenn zartikel.TAXPFL != 0 wird */
/* 1.2.6  25.07.12  TH:     voodoo table header */
/* 1.3.0  18.03.13  TH:     AIX build */
/* 1.3.1  09.04.13  TH:		CR-Logistics, 13D020   */
/* 1.3.2  21.01.14  TH:		CR-12D099 = laden von EAN´s bei Neuanlagen; Erweiterung zdcart.dc_ean_nr */
/* 1.3.3  11.03.14  TH:		Erweiterung zartikel */
/* 1.3.4  10.04.14  TH:		wandeln mit neuer zartikel/zartpreis-Struktur */
/* 1.3.5  06.05.15  TH:		Übernahme der Skontofähigkeit von zdkwgr.wgr_sktof(J/N) auf zartikel.skontofaehig(1/0). */
/* 1.3.6  16.07.15  TH:		Erweiterung zartikel */
/* 1.3.7  17.09.15  DZ:		CR-15D107 Erweiterung um Biosiegel */
/* 1.3.8  06.11.15  TH:		Anpassungen wegen 3rd VAT */



/* --- Includes   ------------------------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo/libscsvoodoo.h>
#include "zpdcgnart.h"


static void Usage( char *spBuf )
{
   strcpy( spBuf, "usage:\n" );
}

void ProgUsage(  char *spBuf, const char *spProgname)
{
   Usage( spBuf );
   GenArtUsage( spBuf, spProgname );
   Zdcart_Protokol_Usage( spBuf, spProgname );
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
          lRetCode = Zdcart_Protokol_Loop( argv[1], argv[2], NULL, spBuf );
        }
        else if ( argc == 4 )
        {
          lRetCode = Zdcart_Protokol_Loop( argv[1], argv[2], argv[3],spBuf );
        }
        else
        {
          lRetCode = 1;
          Usage( spBuf );
          Zdcart_Protokol_Usage(spBuf, spProgname );
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


