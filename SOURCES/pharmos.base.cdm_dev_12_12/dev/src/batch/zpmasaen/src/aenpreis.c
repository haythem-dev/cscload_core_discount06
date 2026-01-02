
/* ---------------------------------------------------------------------- *
 *                         A E N P R E I S . C                            *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Massenaenderung Preise                                       *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  03.09.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

 /* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hdatum/phodate.h"
#include "libscsvoodoo/libscsvoodoo.h"
#include "wdbups/wpp_dbas.h"

#include "logfile.h"
#include "zpmasaen_common.h"

struct  UPD_PREIS
{
	long    DATUMGUELTIGAB;
	double  GROSSO;
	double  AEP;
	double  AVP;
	double  EAVP;
	char    KE_MWST[2];
	double  AGP;
};

#define PROJ_PREIS "DATUMGUELTIGAB,GROSSO,AEP,AVP,EAVP,KE_MWST,AGP"

/* ----------------- Prototype ------------------------ */

void CloseBase(void);
long OpenBase(char *db, char *errmld);

long Insert_Preis(long artikel_nr, opt_prog1_t* params, long tagesdatum, double herst_prozent, char *ke_mwst, char *errmld);

void Free_Preis(void);
/* ----------------- Usage ------------------------ */

void PreisUsage(char *buf)
{
	strcat(buf, "- zpmasaen 1 Database USER HNR GROSSO_ALT AEP_ALT AVP_ALT EAVP_ALT AGP_ALT\n");
	strcat(buf, "             GROSSO_NEU AEP_NEU AVP_NEU EAVP_NEU AGP_NEU DATUM_NEU\n");
	strcat(buf, "  Massenaenderung Preise\n");
}

/* ----------- Preise Lesen -------------------------- */

static int preis_fd = -1;

static long DeclarePreis(opt_prog1_t* params, long tagesdatum, char *buf)
{
	long s;
	char sql[500] = { 0 };

	/* in der Schweiz AEP und EAVP nicht berücksichtigen */
	if (!strcmp(params->db, "zpps1ch") || !strcmp(params->db, "zpps1pch") ||
		!strcmp(params->db, "ich21") || !strcmp(params->db, "ich21pre"))
	{
           if(params->hasAGP) {
		snprintf(sql, sizeof(sql) - 1, "select %s " \
			"from ZARTPREIS where ARTIKEL_NR=? " \
			"and GROSSO=%s and AVP=%s and AGP=%s " \
			"and DATUMGUELTIGAB<=? " \
			"and DATUMGUELTIGAB=" \
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where " \
			"DATUMGUELTIGAB<=%ld " \
			"and ARTIKEL_NR=?)",
			PROJ_PREIS,
			params->cGroAlt, params->cAvpAlt, params->cAgpAlt,
			tagesdatum);
           } else {
		snprintf(sql, sizeof(sql) - 1, "select %s " \
			"from ZARTPREIS where ARTIKEL_NR=? " \
			"and GROSSO=%s and AVP=%s " \
			"and DATUMGUELTIGAB<=? " \
			"and DATUMGUELTIGAB=" \
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where " \
			"DATUMGUELTIGAB<=%ld " \
			"and ARTIKEL_NR=?)",
			PROJ_PREIS,
			params->cGroAlt, params->cAvpAlt,
			tagesdatum);
           }
	}
	/* in allen Ländern außer Deutschland EAVP nicht berücksichtigen */
	else if (!strcmp(params->db, "zpps1de") && !strcmp(params->db, "ide21"))
	{
		snprintf(sql, sizeof(sql) - 1, "select %s " \
			"from ZARTPREIS where ARTIKEL_NR=? " \
			"and GROSSO=%s and AEP=%s and AVP=%s " \
			"and DATUMGUELTIGAB<=? " \
			"and DATUMGUELTIGAB=" \
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where " \
			"DATUMGUELTIGAB<=%ld " \
			"and ARTIKEL_NR=?)",
			PROJ_PREIS,
			params->cGroAlt, params->cAepAlt, params->cAvpAlt,
			tagesdatum);
	}
	else
	{
		snprintf(sql, sizeof(sql) - 1, "select %s " \
			"from ZARTPREIS where ARTIKEL_NR=? " \
			"and GROSSO=%s and AEP=%s and AVP=%s and EAVP=%s " \
			"and DATUMGUELTIGAB<=? " \
			"and DATUMGUELTIGAB=" \
			"(select max(DATUMGUELTIGAB) from ZARTPREIS where " \
			"DATUMGUELTIGAB<=%ld " \
			"and ARTIKEL_NR=?)",
			PROJ_PREIS,
			params->cGroAlt, params->cAepAlt, params->cAvpAlt, params->cEAvpAlt,
			tagesdatum);
	}
	write_logfile(S_HINWEIS, 0, params->progname, sql);

	s = SqlDeclareCsWh(&preis_fd, sql,
		"ZARTPREIS.ARTIKEL_NR",
		"ZARTPREIS.DATUMGUELTIGAB",
		"ZARTPREIS.ARTIKEL_NR", NULL);
	if (s != 0)
		strcpy(buf, DynErrmld());

	return s;
}

static long SchreibePreis(long artikel_nr, opt_prog1_t* params, long tagesdatum, double herst_prozent, char *buf)
{
	long s;
	long art_nr;
	long aenderdatum;
	char msg[200] = { 0 };
	struct UPD_PREIS p;

	art_nr = artikel_nr;
	aenderdatum = params->lDatum;

	memset(&p, 0, sizeof(p));
	s = SqlReadDeclCs(preis_fd, &p, NULL,
		&art_nr, &aenderdatum, &art_nr, NULL);

	if (!(s == 0 || s == 100))
	{
		strcpy(buf, DynErrmld());
		snprintf(msg, sizeof(msg) - 1,
			"SchreibePreis - SqlReadDeclCs(%ld,%ld)): %ld [%s]",
			art_nr, aenderdatum, s, buf);
		write_logfile(S_WARNUNG, 0, params->progname, msg);
		return s;
	}

	if (s == 100) {
		snprintf(msg, sizeof(msg) - 1,
			"SchreibePreis - SqlReadDeclCs(%ld,%ld): %ld",
			art_nr, aenderdatum, s);
		write_logfile(S_HINWEIS, 0, params->progname, msg);
		return s;
	}

	snprintf(msg, sizeof(msg) - 1,
		"SchreibePreis - SqlReadDeclCs(%ld,%ld): DATUMGUELTIGAB[%ld], GROSSO[%.2f], AEP[%.2f], AVP[%.2f], EAVP[%.2f], KE_MWST[%s], AGP[%.2f]",
		art_nr, aenderdatum, p.DATUMGUELTIGAB, p.GROSSO, p.AEP, p.AVP, p.EAVP, p.KE_MWST, p.AGP);
	write_logfile(S_HINWEIS, 0, params->progname, msg);
	s = Insert_Preis(artikel_nr, params, tagesdatum, herst_prozent, p.KE_MWST, buf);
	return s;
}

static void ClosePreis()
{
	SqlCloseCs(preis_fd);
	preis_fd = -1;
}

/* ----------------- Leseschleife Artikel -------------------- */
static
long ArtikelLoop(opt_prog1_t* params, char *buf)
{
	long anz_art;
	long anz_preis;
	int  art_fd;
	long s;
	long artikel_nr;
	long tagesdatum;
	double herst_prozent;
	char sql[100] = { 0 };
	char msg[500] = { 0 };

	memset(msg, 0, sizeof(msg));
	snprintf(msg, sizeof(msg) - 1,
		"ArtikelLoop() -> Hersteller: %ld, GROSSO: %.2f->%.2f, AEP: %.2f->%.2f"
		" AVP: %.2f->%.2f, EAVP: %.2f->%.2f, AGP: %.2f->%.2f, ab: %s, hasAGP: %d",
		params->lHnr,
		params->dGroAlt, params->dGroNeu,
		params->dAepAlt, params->dAepNeu,
		params->dAvpAlt, params->dAvpNeu,
		params->dEAvpAlt, params->dEAvpNeu,
		params->dAgpAlt, params->dAgpNeu,
		params->cDatum, params->hasAGP);
	write_logfile(S_HINWEIS, 0, params->progname, msg);

	snprintf(sql, sizeof(sql) - 1, "select ARTIKEL_NR,HERST_PROZENT from ZARTIKEL " \
		"where HERSTELLER_NR=%ld",
		params->lHnr);
	write_logfile(S_HINWEIS, 0, params->progname, sql);
	s = SqlOpenCsWh(&art_fd, sql);
	if (s != 0)
	{
		strcpy(buf, DynErrmld());
		snprintf(msg, sizeof(msg) - 1, " SqlOpenCsWh(%s): %ld[%s]", sql, s, buf);
		write_logfile(S_FEHLER, 0, params->progname, msg);
		return s;
	}
	s = SqlFetch(art_fd, 1, &artikel_nr, &herst_prozent, NULL);
	if (s == 100)
	{
		snprintf(msg, sizeof(msg) - 1, "Kein Artikel von Hersteller Nr %ld vorhanden", params->lHnr);
		write_logfile(S_HINWEIS, 0, params->progname, msg);
		return s;
	}
	if (s != 0)
	{
		strcpy(buf, DynErrmld());
		snprintf(msg, sizeof(msg) - 1, "SqlFetch(): %ld[%s]", s, buf);
		write_logfile(S_FEHLER, 0, params->progname, msg);
		return s;
	}

	tagesdatum = GetPhoDate();

	s = DeclarePreis(params, tagesdatum, buf);
	snprintf(msg, sizeof(msg) - 1, "DeclarePreis(%ld): %ld (%s)", tagesdatum, s, buf);
	write_logfile(S_HINWEIS, 0, params->progname, msg);
	if (s != 0)
	{
		SqlCloseCs(art_fd);
		return s;
	}

	anz_art = 0;
	anz_preis = 0;
	do
	{
		anz_art++;

		s = SchreibePreis(artikel_nr, params, tagesdatum, herst_prozent, buf);
		snprintf(msg, sizeof(msg) - 1, "[Artikel: %ld] SchreibePreis(%ld, %ld, %.1f): %ld (%s)", anz_art, artikel_nr, tagesdatum, herst_prozent, s, buf);
		write_logfile(S_HINWEIS, 0, params->progname, msg);
		if (s == 0)
		{
			anz_preis++;
		}
		else if (s == 100)
		{
			s = 0;
		}


		if (s == 0)
		{
			s = SqlFetch(art_fd, 1, &artikel_nr, NULL);
			if (!(s == 0 || s == 100))
				strcpy(buf, DynErrmld());
		}
	} while (s == 0);


	if (s == 100)
		s = 0;

	Free_Preis();
	SqlCloseCs(art_fd);
	ClosePreis();

	if (s == 0) {
		sprintf(buf, "Anzahl Artikel gelesen    : %ld\n" \
			"Anzahl Preise  geschrieben: %ld\n",
			anz_art,
			anz_preis
		);
		write_logfile(S_HINWEIS, 0, params->progname, buf);
	}
	return s;
}


/* ----------------- Hauptschleife --------------------------- */

long PreisLoop(int argc, char **argv, char *buf)
{
        int    p=0;
	opt_prog1_t params;
	char errmld[10];
	long   s;

	memset(&params, 0, sizeof(opt_prog1_t));
        params.hasAGP = (15==argc);
	strncpy(params.progname, "zpmasaen", sizeof(params.progname) - 1);
	strncpy(params.db, argv[++p], sizeof(params.db) - 1);
	strncpy(params.user, argv[++p], sizeof(params.user) - 1);
	strncpy(params.cHnr, argv[++p], sizeof(params.cHnr) - 1);
	strncpy(params.cGroAlt, argv[++p], sizeof(params.cGroAlt) - 1);
	strncpy(params.cAepAlt, argv[++p], sizeof(params.cAepAlt) - 1);
	strncpy(params.cAvpAlt, argv[++p], sizeof(params.cAvpAlt) - 1);
	strncpy(params.cEAvpAlt, argv[++p], sizeof(params.cEAvpAlt) - 1);
	if(params.hasAGP) {
	  strncpy(params.cAgpAlt, argv[++p], sizeof(params.cAgpAlt) - 1);
	}
	strncpy(params.cGroNeu, argv[++p], sizeof(params.cGroNeu) - 1);
	strncpy(params.cAepNeu, argv[++p], sizeof(params.cAepNeu) - 1);
	strncpy(params.cAvpNeu, argv[++p], sizeof(params.cAvpNeu) - 1);
	strncpy(params.cEAvpNeu, argv[++p], sizeof(params.cEAvpNeu) - 1);
	if(params.hasAGP) {
	  strncpy(params.cAgpNeu, argv[++p], sizeof(params.cAgpNeu) - 1);
	}
	strncpy(params.cDatum, argv[++p], sizeof(params.cDatum) - 1);

	params.lHnr = atol(params.cHnr);
	params.dGroAlt = atof(params.cGroAlt);
	params.dAepAlt = atof(params.cAepAlt);
	params.dAvpAlt = atof(params.cAvpAlt);
	params.dEAvpAlt = atof(params.cEAvpAlt);
	params.dGroNeu = atof(params.cGroNeu);
	params.dAepNeu = atof(params.cAepNeu);
	params.dAvpNeu = atof(params.cAvpNeu);
	params.dEAvpNeu = atof(params.cEAvpNeu);
	if(params.hasAGP) {
	  params.dAgpAlt = atof(params.cAgpAlt);
	  params.dAgpNeu = atof(params.cAgpNeu);
	}
	params.lDatum = atol(params.cDatum);

	s = OpenBase(params.db, buf);
	if (s == 0)
	{
		s = OpenPflege(params.user, buf);
		if (s == 0)
		{
			s = ArtikelLoop(&params, buf);
			ClosePflege(errmld);
		}
		CloseBase();
	}
	return s;
}
