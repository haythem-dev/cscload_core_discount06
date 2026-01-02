/* ---------------------------------------------------------------------- *
 * Aufgabe        : Funktionalität zum Prüfen der Werte aus DC-Datei      *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 31.01.2005                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <libscsvoodoo/libscsvoodoo.h>

#include <voodoo_table_header/cliart.h>
#include <voodoo_table_header/clioart.h>
#include <voodoo_table_header/ean.h>
#include <voodoo_table_header/carticlelang.h>

#include "znb_gen_li.h"
#include "sql_zliart.h"
#include "g_liartik.h"
#include "check_plausi.h"


/* ---------------------------------------------------------------------- */
int CheckPruefziffer ( long pzn )
{
	if ( pzn <= 0 || pzn > 9999999) 
		return 0;

    /*
	int i;
	long zahl, prziff;

	zahl = pzn;
	
	prziff = 0;
    for (i=7; i>=2; i--)
    {
		zahl /= 10;
        prziff += i * ( zahl % 10 );
    }
    prziff %= 11;

    if (prziff == 10) 
		prziff = 0;

	if ( prziff == ( pzn % 10 ) )
		return 1;
    else
        return 0;
	*/

	return 1;
}

/* ---------------------------------------------------------------------- */
static int IsNoChange(const struct CLIART *li, const int pos )
{
	return li->NB_LI_PLAUSI[ pos ] == NB_PL_NO_VAL;
}

/* ---------------------------------------------------------------------- */
void SetNZwing ( struct CLIART *li, char *errmld)
{
	if ( (!IsNoChange ( li, PL_PRICE_PEXF ) || !IsNoChange ( li, PL_PRICE_PPUB)) && li->OUTSAL > 0)
		SetLITrueFalse ( 1, li->NB_LI_NZWING, NZ_AH_PRICE_CHANGE);

	if ( strcmp (li->ZAENDERUNG, ZAENDERUNG_NEU) != 0 ) // nicht für Neuanlagen
	{
		// hints also occure if zartikel already exists, but clioart doesn´t!
		if ( !IsNoChange ( li, PL_OUTSAL ) && li->OUTSAL > 0 )
			SetLITrueFalse ( 1, li->NB_LI_NZWING, NZ_CHANGE_AH );

		if ( !IsNoChange ( li, PL_SMCDAT ) || !IsNoChange ( li, PL_SIST ) || !IsNoChange ( li, PL_ESIST ) )
			SetLITrueFalse ( 1, li->NB_LI_NZWING, NZ_CHANGE_RR );

		if ( !IsNoChange ( li, PL_SMCAT ) )
			SetLITrueFalse ( 1, li->NB_LI_NZWING, NZ_CHANGE_IKSCODE );

	}

	// Fuer Neuanlagen von Blut-Produkten nichtzwingende Meldung
	if ( strcmp(li->ZAENDERUNG, ZAENDERUNG_NEU) == 0 && li->BLOOD == 1 )
		SetLITrueFalse(1, li->NB_LI_NZWING, NZ_HINT_BLOOD);
}

/* ---------------------------------------------------------------------- */
void SetZwing ( struct CLIART *li, char *errmld)
{
	long status;
    long artikel_nr;
    char ean_nr [L_EAN_EAN_NR + 1] = {0};

	if (li->HERSTELLER_NR <= 0)
	{
		li->HERSTELLER_NR = -1;
		SetLITrueFalse( 1, li->NB_LI_ZWING, ZW_HNR_UNSET );
	}

	if ( m_eFileArt == ARTICLE_ARTBAR && !IsNoChange ( li, PL_GTIN14 ) )
	{
		Trim(li->GTIN14);

		if (TestEanNr( li->GTIN14 ) == 1 )  // Test nur bei gueltiger GTIN 14
		{
			if (checkGtin14Exists(li->PHAR, li->GTIN14)) // code bereits für einen anderen Artikel hinterlegt?
			{
				SetLITrueFalse( 1, li->NB_LI_ZWING, ZW_GTIN14_EXISTS );
			}
		}
	}
    
	// EAN-Nr lesen 
    if ( m_eFileArt == ARTICLE_ARTBAR && !IsLIFeldErr( li->NB_LI_PLAUSI, PL_BC ) )
    {
        Trim(li->BC);

		if ( TestEanNr( li->BC ) == 1 )  // Test nur bei gueltiger EAN-NR 
        {
            status = sel_ean_by_pzn( li->PHAR, ean_nr, errmld );
            if ( !( status == 0 || status == 100 )) 
				return;

            if ( status == 0 )
            {
				if ( strcmp( ean_nr, li->BC ) != 0 )
					SetLITrueFalse( 1, li->NB_LI_ZWING, ZW_EAN_DIFF );
            }

            status = sel_ean_by_ean( &artikel_nr, li->BC, errmld );
            
			if ( !( status == 0 || status == 100 )) 
				return;

            if ( status == 0 )
            {
				if ( artikel_nr != li->PHAR )
					SetLITrueFalse( 1, li->NB_LI_ZWING, ZW_EAN_MEHRFACH );
            }
        }
    }

	// PZN-Neu lesen 
    if ( m_eFileArt == ARTICLE_ARTCH && !IsLIFeldErr( li->NB_LI_PLAUSI, PL_PHAR2 ) && li->PHAR2 > 0 )
    {
        // PZN-neu = PZN 
        if ( li->PHAR2 == li->PHAR )
			SetLITrueFalse( 1, li->NB_LI_ZWING, ZW_PZNNF_GLEICH );

        if (  li->PHAR2 != li->PHAR )
        {
			status = sel_ersatz( li->PHAR2, errmld ); 
			
			if ( !( status == 0 || status == 100 )) 
				return;

			if ( status == 100 )
				SetLITrueFalse( 1, li->NB_LI_NZWING, NZ_PZNNF_NVOR );
        }
    }   

	if ( strcmp (li->ZAENDERUNG, ZAENDERUNG_NEU) != 0 ) // nicht für Neuanlagen
	{
		// hints also occure if zartikel already exists, but clioart doesn´t!
		if ( !IsNoChange ( li, PL_BG ) )
			SetLITrueFalse ( 1, li->NB_LI_ZWING, ZW_CHANGE_BTM );

		if ( !IsNoChange ( li, PL_CDBG ) )
			SetLITrueFalse ( 1, li->NB_LI_ZWING, ZW_CHANGE_PSYCHOTROP );

		if ( !IsNoChange ( li, PL_COOL ) )
			SetLITrueFalse ( 1, li->NB_LI_ZWING, ZW_CHANGE_COOL );

		if ( !IsNoChange ( li, PL_SUPPLNO ) && li->COMPNO != li->SUPPLNO)
			SetLITrueFalse ( 1, li->NB_LI_ZWING, ZW_CHANGE_AWL );
		
		if ( !IsNoChange ( li, PL_COMPNO ) )
			SetLITrueFalse ( 1, li->NB_LI_ZWING, ZW_CHANGE_HNR );

		if ( !IsNoChange ( li, PL_DSCRD ) || !IsNoChange ( li, PL_DSCRF ) )
			SetLITrueFalse ( 1, li->NB_LI_ZWING, ZW_CHANGE_NAME );

		if ( li->NINCD != 10 
			&& strcmp (li->SMCAT, "A") != 0 
			&& strcmp (li->SMCAT, "B") != 0
			&& strcmp (li->SMCAT, "C") != 0
			&& strcmp (li->SMCAT, "D") != 0
			&& strcmp (li->SMCAT, "E") != 0 )
		{// ZWING bei Preisänderung für nicht 1 / A / B / C / D / E
			SetLITrueFalse ( !IsNoChange ( li, PL_PRICE_PEXF ) || !IsNoChange ( li, PL_VAT ) || !IsNoChange ( li, PL_PRICE_PPUB ), li->NB_LI_ZWING, ZW_CHANGE_PRICE );
		}
	}
	else
	{
		// zwingender Fehler bei Neuanlagen, wenn AWL != HNR, aber Namensmatching nicht erfolgreich
		if (li->SUPPLNO > 0 && li->SUPPLNO != li->COMPNO && li->AWL1 == 0)
			SetLITrueFalse ( 1, li->NB_LI_ZWING, ZW_CHANGE_AWL );
	}

	if ( strcmp (li->ZAENDERUNG, ZAENDERUNG_NEU) == 0 || !IsNoChange ( li, PL_PRICE_PEXF ) ) // Neuanlagen oder Preisänderungen
	{
		SetLITrueFalse ( li->PRICE_PEXF <= 0.0, li->NB_LI_ZWING, ZW_GEP_ERR );
	}
}

/* ---------------------------------------------------------------------- */
void CalcKZs ( struct  CLIART *li, char *errmld ) 
{
	if ( m_eFileArt == ARTICLE_ART )
	{
		if ( strcmp (li->ZAENDERUNG, ZAENDERUNG_NEU) != 0 ) 
		{	// Artikel-Änderung, keine Neuanlage

			// DFO und Einheit editierbar machen / als geändert kennzeichnen, wenn ein Artikelname geändert wurde
			if (!IsNoChange ( li, PL_DSCRD ))
			{
				li->NB_LI_PLAUSI[ PL_QTYUD ]	= NB_PL_OK;
				li->NB_LI_PLAUSI[ PL_PCKTYPD ]	= NB_PL_OK;
				
				if (IsNoChange ( li, PL_NOPCS ))
					li->NB_LI_PLAUSI[ PL_NOPCS ]	= NB_PL_OK;

				if (IsNoChange ( li, PL_QTY ))
					li->NB_LI_PLAUSI[ PL_QTY ]	= NB_PL_OK;
			}

			if (!IsNoChange ( li, PL_DSCRF ))
			{
				li->NB_LI_PLAUSI[ PL_QTYUF ]	= NB_PL_OK;
				li->NB_LI_PLAUSI[ PL_PCKTYPF ]	= NB_PL_OK;

				if (IsNoChange ( li, PL_NOPCS ))
					li->NB_LI_PLAUSI[ PL_NOPCS ]	= NB_PL_OK;

				if (IsNoChange ( li, PL_QTY ))
					li->NB_LI_PLAUSI[ PL_QTY ]	= NB_PL_OK;
			}
		}
	}

	if (strcmp (li->ZAENDERUNG, ZAENDERUNG_NEU) == 0)
	{
		if (li->PRICE_PEXF <= 0.0 || strcmp(li->SALECD, "P") == 0 || strcmp(li->SALECD, "R") == 0 )	
			strcpy(li->ARTIKEL_GESPERRT,		"1");
		else
			strcpy(li->ARTIKEL_GESPERRT,		"0");
	}
}
