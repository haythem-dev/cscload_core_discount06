/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die Util-Datei		                          *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 08.07.2005                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "sql_zputil.h"

#include "util_form.h"

/* ---------------------------------------------------------------------- */
int  OpenUtilDatei( FILE **fd, const char * const datei, char *errmld )
{
	*fd = fopen(datei, "rt");
	if (*fd == NULL)
	{
       sprintf( errmld, "Fehler beim Oeffnen der Datei\n%s",
                        datei );
       return 1;
    }
    return 0;
}

/* ---------------------------------------------------------------------- */
void CloseUtilDatei( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int GetUtilZeile( FILE * fd, char *zeile )
{
    if (fgets(zeile, MAX_BUF, fd) == NULL)
	{
		if (feof(fd) != 0)
			return 2;/*Dateiende*/
		else
			return 1;/*Error*/
	}
	return 0;
}

/* ---------------------------------------------------------------------- */
int  OpenProtDatei	( FILE **fd, const char * const datei, char *errmld )
{
	*fd = fopen(datei, "wt");
		
	if (*fd == NULL)
	{
  	   sprintf( errmld, "Fehler beim Oeffnen des Protokoll-Files\n%s",
                        datei );
       return 1;
    }
    return 0;
}

/* ---------------------------------------------------------------------- */
void CloseProtDatei ( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int  WriteProtZeile ( FILE * fd )
{
	char val[80];

	if ( m_eUpdTable == UPD_ZARTIKEL )
	{
		sprintf(val, "%07ld", m_BufOldZArt.ARTIKEL_NR);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_ZARTWG )
	{
		sprintf(val, "%07ld - art<%s>", atol(upd_values[0]), upd_columns[1]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_CARTICLECODES )
	{
		sprintf(val, "%07ld - code_type<%s>", atol(upd_values[0]), upd_values[1]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_ZCHARGENRR )
	{
		sprintf(val, "%07ld - charge<%s>", atol(upd_values[0]), upd_values[1]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_ZARTPREIS )
	{
		if (m_ZartpreisWrToProt == ZARTPREIS_INS) {
			sprintf(val, "%07ld - datgueltab<%s>", atol(upd_values[0]), upd_values[1]);
		}
		else {
			sprintf(val, "%07ld - datgueltab<%s> - error: check failed", atol(upd_values[0]), upd_values[1]);
		}
		
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_CDISCOUNT_FLEXIBLE )
	{
		sprintf(val, "%07ld - basismenge<%s>, dat_from<%s>, dat_to<%s>", atol(upd_values[0]), upd_values[1], upd_values[2], upd_values[3]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_CDISCOUNT_STOP || m_eUpdTable == UPD_ARTVE || m_eUpdTable == UPD_ZARTFRANCE || m_eUpdTable == UPD_ZARTSWITZERLAND || m_eUpdTable == UPD_ZARTSERBIA || m_eUpdTable == UPD_ZARTAUSTRIA || m_eUpdTable == UPD_CARTICLEEXT )
	{
		sprintf(val, "%07ld", atol(upd_values[0]));
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_CDISCGRPMEM )
	{
		sprintf(val, "%07ld - gruppe<%s>", atol(upd_values[0]), upd_values[1]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_CARTCOMPACK )
	{
		sprintf(val, "%07ld - pack<%s>", atol(upd_values[0]), upd_values[1]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_CGIBATCHENTRY )
	{
		sprintf(val, "%07ld - company_code<%s>, dat_from<%s>, dat_to<%s>", atol(upd_values[0]), upd_values[1], upd_values[2], upd_values[3]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if ( m_eUpdTable == UPD_CIMEXBLOCK )
	{
		sprintf(val, "%07ld - country_code<%s>, imex_mode<%s>, blockflag<%s>", atol(upd_values[0]), upd_values[1], upd_values[2], upd_values[3]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if (m_eUpdTable == UPD_CIBT)
	{
		sprintf(val, "%07ld - <%s>", atol(upd_values[0]), upd_values[1]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if (m_eUpdTable == UPD_EAN)
	{
		switch (m_EanWrToProt)
		{
			case EAN_DEL:
				sprintf(val, "Art_nr:%07ld deleted from table ean", atol(upd_values[0]));
				break;
			case EAN_NO_DEL:
				sprintf(val, "Art_nr:%07ld not deleted from table ean", atol(upd_values[0]));
				break;
			case EAN_INS:
				sprintf(val, "Art_nr:%07ld - ean<%s> written to table ean", atol(upd_values[0]), upd_values[1]);
				break;
			case EAN_NO_INS:
				sprintf(val, "Art_nr:%07ld - ean<%s> not written to table ean", atol(upd_values[0]), upd_values[1]);
				break;
		}

		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
	{
		sprintf(val, "%07ld, %d", m_BufOldCsubsequentdeliverybrancharticleconfig.ARTICLENO, m_BufOldCsubsequentdeliverybrancharticleconfig.BRANCHNO);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if (m_eUpdTable == UPD_ZARTWG_5AG)
	{
		sprintf(val, "%07ld - art<%s>", atol(upd_values[0]), upd_values[1]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}
	else if (m_eUpdTable == UPD_BLIESORT_DIREKT)
	{
		sprintf(val, "%ld - besla_nr<%s>", atol(upd_values[0]), upd_values[1]);
		fputs(val, fd);
		/* linefeed*/
		fputs("\n", fd);
	}

	return 0;
}

