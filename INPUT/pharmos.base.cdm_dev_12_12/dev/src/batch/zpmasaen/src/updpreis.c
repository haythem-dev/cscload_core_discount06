
/* ---------------------------------------------------------------------- *
 *                         U P D P R E I S . C                            *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Generiert die Preise bei Massenaenderungen                   *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  28.06.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

 /* -------  Spezielle includes ----------------------------------------- */

#include <zartprei.h>
#include <zartikel.h>
#include <zapflege.h>

#include "wdbups/wpp_prot.h"
#include "wdbups/wpp_dbas.h"
#include "libscsvoodoo/libscsvoodoo.h"

#include "logfile.h"
#include "zpmasaen_common.h"

#define L_ARTIKEL_NR   7

/* ----------------- artpreis ------------------------------- */

#ifdef MIT_ARTPREIS_PFLEGE

#include <artpreis.h>

void m_ArtpreisDoc_FreeBufferDesc(void);
int  m_ArtpreisDoc_GetBufferDesc(char *errmld);
long m_ArtpreisDoc_InsertRecord(struct ZARTPREIS *preis, char *errmld);

#endif

static long fixAGPbeforeUpdates(opt_prog1_t* params, struct ZARTPREIS* dataset);

/* -----  Zapflege  ------------------------- */

static int  Fd_Zapflege = -1;

static struct ZAPFLEGE Buf_zapflege;

static int GetBufferDesc_Zapflege(char * errmld)
{
	char *tabelle = "zapflege";
	long lStatus;
	char errstr[80];

	strcpy(errmld, "");
	if (Fd_Zapflege >= 0) return 0;

	lStatus = OpenBufferDescProj(&Fd_Zapflege, tabelle, PROJECTION_ZAPFLEGE,
		NULL, NULL,
		V_OHNE,
		errstr);
	if (lStatus != 0)
	{
		sprintf(errmld, "%s: %s", tabelle, errstr);
		Fd_Zapflege = -1;
		return -1;
	}
	return 0;
}

static long StoreRecord_Zapflege(long artikel_nr, long datum, char* cErrmld)
{
	long lStatus;
	char PrimekeyCond[50];

	Buf_zapflege.ARTIKEL_NR = artikel_nr;
	Buf_zapflege.DATUM = datum;

	strcpy(cErrmld, "");

	sprintf(PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld",
		Buf_zapflege.ARTIKEL_NR,
		Buf_zapflege.DATUM);

	lStatus = FdReadRecord(Fd_Zapflege, PrimekeyCond,
		&Buf_zapflege, cErrmld);

	if (!(lStatus == 0 || lStatus == 100)) return -1;

	if (lStatus == 100)
	{
		Buf_zapflege.ARTIKEL_NR = artikel_nr;
		Buf_zapflege.DATUM = datum;
		lStatus = FdDelayInsertRecord(Fd_Zapflege, &Buf_zapflege,
			PrimekeyCond, cErrmld);
	}
	return lStatus;
}

/* ----- Zartikel ------------------------- */

static int  Fd_Zartikel = -1;

static long lStatus_Zartikel;

static struct ZARTIKEL Buf_zartikel;
static struct ZARTIKEL BufOld_zartikel;
static char CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];

static int GetBufferDesc_Zartikel(char * errmld)
{
	char *tabelle = "zartikel";
	long lStatus;
	char errstr[80];

	strcpy(errmld, "");
	if (Fd_Zartikel >= 0) return 0;

	memset(CmpIndikator_Zartikel, '0', POSANZ_ZARTIKEL);
	CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';
	CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_AENDER] = '1';
	CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER] = '1';

	lStatus = OpenBufferDescProj(&Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
		CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr);
	/* !!!!!!!bis 21.12.2000    V_PROTOKOL  */
	if (lStatus != 0)
	{
		sprintf(errmld, "%s: %s", tabelle, errstr);
		Fd_Zartikel = -1;
		return -1;
	}
	return 0;
}

static long StoreRecord_Zartikel(opt_prog1_t* params, long artikel_nr, long datum,
	char* cErrmld)
{
	long lStatus;
	char PrimekeyCond[50];
	char format[50];

	Buf_zartikel.ARTIKEL_NR = artikel_nr;

	strcpy(cErrmld, "");

	sprintf(format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR);
	sprintf(PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR);

	/* sprintf( PrimekeyCond, "ARTIKEL_NR=%ld", Buf_zartikel.ARTIKEL_NR ); */

	lStatus = FdReadRecord(Fd_Zartikel, PrimekeyCond,
		&Buf_zartikel, cErrmld);

	if (lStatus != 0) return lStatus;

	BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */

	Buf_zartikel.DATUM_AENDER = datum;
	strcpy(Buf_zartikel.BEARBEITER, params->user);

	lStatus = FdDelayUpdateRecord(Fd_Zartikel, &Buf_zartikel,
		&BufOld_zartikel,
		PrimekeyCond, cErrmld);
	return lStatus;
}


/* ----- Zpreis   ------------------------- */

static int  Fd_Zpreis = -1;

static long lStatus_Zpreis;

static struct ZARTPREIS Buf_zpreis;
static struct ZARTPREIS BufOld_zpreis;

static char PrimekeyCond_Zpreis[100];

static int GetBufferDesc_Zpreis(char * errmld)
{
	char *tabelle = "zartpreis";
	long lStatus;
	char errstr[80];

	strcpy(errmld, "");
	if (Fd_Zpreis >= 0) return 0;

	lStatus = OpenBufferDescProj(&Fd_Zpreis, tabelle, PROJECTION_ZARTPREIS,
		NULL, NULL, V_PROTO_VERTEIL, errstr);
	/* !!!!!!!bis 21.12.2000       V_PROTOKOL   */
	if (lStatus != 0)
	{
		sprintf(errmld, "%s: %s", tabelle, errstr);
		Fd_Zpreis = -1;
		return -1;
	}
	return 0;
}

static void FillRecord_Zpreis(long artikel_nr, opt_prog1_t* params, double herst_prozent, char *ke_mwst, struct ZARTPREIS *zp)
{
	char msg[300] = { 0 };

	zp->ARTIKEL_NR = artikel_nr;
	zp->DATUMGUELTIGAB = params->lDatum;
	zp->GROSSO = params->dGroNeu;
	zp->AEP = params->dAepNeu;
	zp->AVP = params->dAvpNeu;
	strncpy(zp->KE_MWST, ke_mwst, sizeof(zp->KE_MWST) - 1);
	zp->HERST_PROZENT = herst_prozent;
	zp->EAVP = params->dEAvpNeu;
	zp->AGP = params->dAgpNeu;

	snprintf(msg, sizeof(msg) - 1,
		"FillRecord_Zpreis(): ARTIKEL_NR[%ld], DATUMGUELTIGAB[%ld], GROSSO[%.2f],"
		" AEP[%.2f], AVP[%.2f], KDE_MWST[%s], HERST_PROZENT[%.2f], EAVP[%.2f], AGP[%.2f]",
		zp->ARTIKEL_NR, zp->DATUMGUELTIGAB, zp->GROSSO, zp->AEP, zp->AVP, zp->KE_MWST, zp->HERST_PROZENT, zp->EAVP, zp->AGP);
	write_logfile(S_HINWEIS, 0, params->progname, msg);
}

static void SetPrimekeyCondition_Zpreis()
{
	char format[50];
	sprintf(format, "ARTIKEL_NR=%c%d.ld and DATUMGUELTIGAB=%cld",
		'%', L_ARTIKEL_NR, '%');
	sprintf(PrimekeyCond_Zpreis, format,
		Buf_zpreis.ARTIKEL_NR,
		Buf_zpreis.DATUMGUELTIGAB);
	/*
	  sprintf( PrimekeyCond_Zpreis,
			   "ARTIKEL_NR=%ld and DATUMGUELTIGAB=%ld",
				Buf_zpreis.ARTIKEL_NR,
				Buf_zpreis.DATUMGUELTIGAB );
	*/
}

static long ReadRecord_Zpreis(opt_prog1_t* params, char *cErrmld)
{
	long lStatus;
	char msg[200] = { 0 };

	SetPrimekeyCondition_Zpreis();
	lStatus = FdReadRecord(Fd_Zpreis, PrimekeyCond_Zpreis,
		&BufOld_zpreis, msg);

	if (lStatus == 0)
	{
		strcpy(cErrmld, "");
	}
	else if (lStatus != 100)
	{
		strcpy(cErrmld, msg);
	}

	snprintf(msg, sizeof(msg) - 1, "ReadRecord_Zpreis() :%ld [%s]",
		lStatus, PrimekeyCond_Zpreis);
	write_logfile(S_HINWEIS, 0, params->progname, msg);
	lStatus_Zpreis = lStatus;
	return lStatus;
}


static long StoreRecord_Zpreis(opt_prog1_t* params, char *cErrmld)
{
	long lStatus;
	char errmld[200];
	char msg[300] = { 0 };

	SetPrimekeyCondition_Zpreis();

        if(!params->hasAGP) {
           lStatus = fixAGPbeforeUpdates(params, &Buf_zpreis);
        }
	if (lStatus_Zpreis == 100) {
		lStatus = FdDelayInsertRecord(Fd_Zpreis, &Buf_zpreis,
			PrimekeyCond_Zpreis, errmld);
		snprintf(msg, sizeof(msg) - 1,
			"StoreRecord_Zpreis() -> INSERT(%s): %ld",
			PrimekeyCond_Zpreis, lStatus);
		write_logfile(S_HINWEIS, 0, params->progname, msg);
	}
	else if (lStatus_Zpreis == 0) {
		lStatus = FdDelayUpdateRecord(Fd_Zpreis, &Buf_zpreis,
			&BufOld_zpreis,
			PrimekeyCond_Zpreis, errmld);
		snprintf(msg, sizeof(msg) - 1,
			"StoreRecord_Zpreis() -> UPDATE(%s): %ld",
			PrimekeyCond_Zpreis, lStatus);
		write_logfile(S_HINWEIS, 0, params->progname, msg);
	}
	else
	{
		lStatus = lStatus_Zpreis;
		strcpy(errmld, "Interner Fehler");
		snprintf(msg, sizeof(msg) - 1,
			"StoreRecord_Zpreis() -> %s (%s): %ld",
			errmld, PrimekeyCond_Zpreis, lStatus_Zpreis);
		write_logfile(S_WARNUNG, 0, params->progname, msg);
	}
	if (lStatus != 0)
		strcpy(cErrmld, errmld);
	else
		strcpy(cErrmld, "");

	return lStatus;
}



long Insert_Preis(long artikel_nr, opt_prog1_t* params, long tagesdatum, double herst_prozent, char *ke_mwst, char *errmld)
{
	char msg[300] = { 0 };
	long s;
	if (GetBufferDesc_Zartikel(errmld) != 0) return -1;
	if (GetBufferDesc_Zpreis(errmld) != 0) return -1;
	if (GetBufferDesc_Zapflege(errmld) != 0) return -1;
#ifdef MIT_ARTPREIS_PFLEGE
	if (m_ArtpreisDoc_GetBufferDesc(errmld) != 0) return -1;
#endif

	FillRecord_Zpreis(artikel_nr, params, herst_prozent, ke_mwst, &Buf_zpreis);

	s = ReadRecord_Zpreis(params, errmld);
	if (!(s == 0 || s == 100)) return -1;

	s = StoreRecord_Zartikel(params, artikel_nr, tagesdatum, errmld);

	if (s == 0)
	{
		s = StoreRecord_Zpreis(params, errmld);
#ifdef MIT_ARTPREIS_PFLEGE
		if (s == 0)
			s = m_ArtpreisDoc_InsertRecord(&Buf_zpreis, errmld);
#endif
	}

	if (s == 0)
	{
		s = StoreRecord_Zapflege(artikel_nr, (params->lDatum <= tagesdatum ? tagesdatum : params->lDatum), errmld);
		snprintf(msg, sizeof(msg) - 1,
			"StoreRecord_Zapflege(%ld, %ld): %ld (%s)",
			artikel_nr, (params->lDatum <= tagesdatum ? tagesdatum : params->lDatum), s, errmld);
		write_logfile(S_HINWEIS, 0, params->progname, msg);
	}
	if (s == 0)
		s = FdTransact(errmld);
	return s;
}

void Free_Preis()
{
#ifdef MIT_ARTPREIS_PFLEGE
	m_ArtpreisDoc_FreeBufferDesc();
#endif
}

/*
** Adjust AGP when it is not supported yet (backward compatability)
*/
static long fixAGPbeforeUpdates(opt_prog1_t* params, struct ZARTPREIS* dataset) {

  long s = 0L, art_no, valid_from;
  double agp;
  char msg[200] = {0};
  char sql[300] = {0};

  snprintf(sql, sizeof(sql)-1,
    "SELECT datumgueltigab, artikel_nr, agp FROM zartpreis"
    "  WHERE artikel_nr=%ld AND datumgueltigab IN ("
    "    SELECT MAX(datumgueltigab) FROM zartpreis "
    "      WHERE artikel_nr=%ld AND datumgueltigab <= %ld"
    "      GROUP BY artikel_nr)",
    dataset->ARTIKEL_NR, dataset->ARTIKEL_NR, dataset->DATUMGUELTIGAB);


  if(0L == (s = SqlRead(sql, &valid_from, &art_no, &agp, NULL))) {
    snprintf(msg, sizeof(msg) - 1,
             "Artikel(%ld,%ld) hat ergaenzten AGP: %.2f", art_no, valid_from, agp);
    write_logfile(S_HINWEIS, 0, params->progname, msg);
  } else {
    agp = 0;
    snprintf(msg, sizeof(msg) - 1,
             "Artikel(%ld,%ld) hat keinen ergaenzten AGP", art_no, valid_from);
    write_logfile(S_WARNUNG, 0, params->progname, msg);
  }
  dataset->AGP = agp;

  return s;
}
