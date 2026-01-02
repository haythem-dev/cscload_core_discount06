#include <stdio.h>                             
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phodate.h"
#include "phozeit.h"
#include "libscsvoodoo.h"

#include <wpp_prot.h>
#include <wpp_dbas.h>
#include <math.h>
#include "cagpart.h"
#include "cagpoart.h"
#include "zartprei.h"
#include "logfile.h"
#include "agpTransaction.h"

#define MAX_PRICES_PER_ART 100
#define MAX_DAYS_DEL_TRA_CLEANUP 90 // Max days to keep for transferred and deleted imports
#define MAX_DAYS_IMP_CLEANUP 180    // Max days to keep for imported imports
#define MAX_ARTIKEL_NR 9999999L

/*-------------------------------------------------------*/
static long TransferAgpRecords(long agpNr, long pznfrom, long pznto);
static long TransferAgpRecord(long artikel_nr, long gultigab_Datum, double agp);
static long UpdateInsert_ZartPreis(struct ZARTPREIS **zartpreis_recs, long zartpreis_rec_count, long agp_artikel_nr, long agp_gultigab_Datum, double agp_agp);
static long UpdateRecord_ZartPreis(struct ZARTPREIS *zrecord);
static long InsertRecord_ZartPreis(struct ZARTPREIS *zrecord);
static long ReadRecord_ZartPreis(long artikel_nr, long datumgueltigab, struct ZARTPREIS *BufOldZartPreis, char *errmld);
static int  WriteZAPflege(long art_no, long date, char * errmld);
static long GetBufferDesc_Generic(char* cErrmld, size_t len, int* fd, char* tabelle);
static long GetBufferDesc_ZartPreis(char *cErrmld, size_t len);
static long UpdateRecord_Cagpoart(long agpNr);
static long GetBufferDesc_Cagpoart(char *cErrmld, size_t len);
static long ReadRecord_Cagpoart(long agpNr, struct CAGPOART *BufCagpoartOld, char *errmld);

/*---------Cleanup prototypes-------------------------------*/
static long CleanupAgpImport(long agpNr, short txnState, long created);

static int		fd_zartpreis = -1;
static int		fd_cagpoart = -1;
static char		errmld[200];

/*-----------------Transfer API--------------------------*/

// selects all eligible AGP imports
long BeginTransfer(int importno, long pznfrom, long pznto)
{
	int fd;
	char sql[150];
	long s;
	long agpNr;
	char sqlino[50] = { 0 };
	int cnt = 0;
	char msg[150];

	snprintf(msg, sizeof(msg) - 1, "Process started with parameters import=%i, pzn_from=%i, pzn_to=%i", importno, pznfrom, pznto);
	wrap_logging(S_HINWEIS, "Transfer", msg);
	// Select all eligible AGP import ids with status 1-Imported and have no fehler records
	if (importno > 0)
	{
		snprintf(sqlino, sizeof(sqlino) - 1, " AND agp_nr = %i", importno);
	}
	snprintf(sql, sizeof(sql) - 1, "SELECT agp_nr FROM cagpoart WHERE txn_status = 1 AND rec_fehler < 1 %s ORDER BY agp_nr ASC", sqlino);
	// Open DB Cursor
	s = SqlOpenCsWh(&fd, sql);

	if (SQL_OK == s)
	{
		// Begin Fetch
		while (SQL_OK == (s = SqlFetch(fd, 1, &agpNr, NULL)))
		{
			if (agpNr > 0)
			{
				s = TransferAgpRecords(agpNr, pznfrom, pznto);
				cnt++;
			}
		}
		(void)SqlCloseCs(fd);
	}

	if (SQL_OK == s || SQL_NO_MORE_DATA == s)
	{
		s = SQL_OK;
		snprintf(msg, sizeof(msg) - 1, "Process ended with checked %i imports in total.", cnt);
		wrap_logging(S_HINWEIS, "Transfer", msg);
	}
	else
	{
		s = SQL_NOK;
		if (!strlen(errmld))
		{
			snprintf(errmld, sizeof(errmld) - 1, "Error in transferring AGP imports.");
		}
		wrap_logging(S_FEHLER, "Transfer", errmld);
	}

	return s;
}

// Transfers AGP prices to zartpreis
static long TransferAgpRecords(long agpNr, long pznfrom, long pznto)
{
	char sql[250];
	long s;
	int  fd;
	long cnt = 0;
	struct CAGPART cagpart_rec;
	char sqlpznfrom[50] = { 0 };
	char sqlpznto[50] = { 0 };

	//--- start transaction
	s = SqlBeginWork();

	if ((pznfrom > 0) && (pznfrom < MAX_ARTIKEL_NR))
	{
		snprintf(sqlpznfrom, sizeof(sqlpznfrom) - 1, " AND pzn >= %i", pznfrom);
	}
	if ((pznto > 0) && (pznto < MAX_ARTIKEL_NR))
	{
		snprintf(sqlpznto, sizeof(sqlpznto) - 1, " AND pzn <= %i", pznto);
	}

	// Query to select all records for AGP Nr
	snprintf(sql, sizeof(sql) - 1,
		"SELECT agp_nr, pzn, zeile_nr, agp, gueltig_ab, zeile_status, status_detail FROM cagpart"
		" WHERE agp_nr = %ld AND zeile_status IN (0,1) %s %s ORDER BY pzn ASC, gueltig_ab DESC ", agpNr, sqlpznfrom, sqlpznto);

	// Open DB Cursor
	s = SqlOpenCsWh(&fd, sql);
	if (SQL_OK == s)
	{
		// Begin Fetch
		while (SQL_OK == (s = SqlFetch(fd, 1, &cagpart_rec, NULL)))
		{
			s = TransferAgpRecord(cagpart_rec.PZN, cagpart_rec.GUELTIG_AB, cagpart_rec.AGP);
			if (s != SQL_OK) break;
			memset(&cagpart_rec, 0, sizeof(cagpart_rec));
			cnt++;
		}
		SqlCloseCs(fd);
	}
	if (SQL_OK == s || SQL_NO_MORE_DATA == s)
	{
		s = UpdateRecord_Cagpoart(agpNr);
	}

	if (SQL_OK == s)
	{
		s = SqlCommitWork(); // Commit when all is ok
		char msg[150];
		snprintf(msg, sizeof(msg) - 1, "Import with AGP No:%i successfully processed with %i records transferred.", agpNr, cnt);
		wrap_logging(S_HINWEIS, "Transfer", msg);
	}
	else
	{
		SqlRollbackWork(); // Rollback for issues
		if (!strlen(errmld))
		{
			snprintf(errmld, sizeof(errmld) - 1, "Error in transferring records for AGP Nr: %ld.", agpNr);
		}
		wrap_logging(S_FEHLER, "Transfer", errmld);
	}
	return s;
}


// Reads each record of ZartPreis
static long TransferAgpRecord(long artikel_nr, long gueltigab_Datum, double agp)
{
	char sql[500];
	double count = -1;
	long s = SQL_NOK;
	int fd;
	int anz;
	struct ZARTPREIS *zartpreis_reclist[MAX_PRICES_PER_ART];

	memset(zartpreis_reclist, 0, sizeof(struct ZARTPREIS));

	s = GetBufferDesc_ZartPreis(errmld, sizeof(errmld));
	if (SQL_OK == s)
	{
		snprintf(sql, sizeof(sql) - 1, "SELECT count(*) FROM ZARTPREIS z1"
			" INNER JOIN"
			" (SELECT ARTIKEL_NR, MAX(DATUMGUELTIGAB) AS MAX_GUEABVORHER FROM ZARTPREIS"
			" WHERE DATUMGUELTIGAB <= %ld AND ARTIKEL_NR = %ld"
			" GROUP BY ARTIKEL_NR) z2"
			" ON z1.ARTIKEL_NR = z2.ARTIKEL_NR AND (z1.DATUMGUELTIGAB > %ld OR z1.DATUMGUELTIGAB = z2.MAX_GUEABVORHER)",
			gueltigab_Datum, artikel_nr, gueltigab_Datum);

		s = SqlRead(sql, &count, NULL); // Checks row counts to select from zartpreis
		if (SQL_OK == s && count > 0 && count <= MAX_PRICES_PER_ART)
		{
			snprintf(sql, sizeof(sql) - 1, "SELECT z1.* FROM ZARTPREIS z1 "
				" INNER JOIN"
				" (SELECT ARTIKEL_NR, MAX(DATUMGUELTIGAB) AS MAX_GUEABVORHER FROM ZARTPREIS"
				" WHERE(DATUMGUELTIGAB <= %ld) AND ARTIKEL_NR = %ld"
				" GROUP BY ARTIKEL_NR) z2"
				" ON z1.ARTIKEL_NR = z2.ARTIKEL_NR AND(z1.DATUMGUELTIGAB > %ld OR z1.DATUMGUELTIGAB = z2.MAX_GUEABVORHER)"
				" ORDER BY z1.ARTIKEL_NR ASC, z1.DATUMGUELTIGAB ASC",
				gueltigab_Datum, artikel_nr, gueltigab_Datum);
			// Open DB Cursor
			s = SqlOpenCsWh(&fd, sql);
			if (SQL_OK == s)
			{
				anz = 0;
				zartpreis_reclist[anz] = malloc(sizeof(struct ZARTPREIS));
				// Begin Fetch
				while (SQL_OK == (s = SqlFetch(fd, 1, zartpreis_reclist[anz], NULL)))
				{
					anz++;
					if (anz >= count) break;
					zartpreis_reclist[anz] = malloc(sizeof(struct ZARTPREIS));
				}

				SqlCloseCs(fd);
				s = UpdateInsert_ZartPreis(zartpreis_reclist, (long)count, artikel_nr, gueltigab_Datum, agp);
			}
		}
	}

	if (SQL_OK != s)
	{
		if (!strlen(errmld))
		{
			sprintf(errmld, "Error in transferring record for Artikel_Nr: %ld, GUELTIGABDATUM: %ld, AGP: %.2f", artikel_nr, gueltigab_Datum, agp);
		}
		wrap_logging(S_FEHLER, "Transfer", errmld);
	}

	// deallocates memory for record list
	for (int i = 0; i < MAX_PRICES_PER_ART; i++)
	{
		if (zartpreis_reclist[i] == NULL)
		{
			break;
		}
		free(zartpreis_reclist[i]);
		zartpreis_reclist[i] = NULL;
	}
	return s;
}


// Inserts or updates ZartPreis table 
static long UpdateInsert_ZartPreis(struct ZARTPREIS **zartpreis_recs, long zartpreis_rec_count, long agp_artikel_nr, long agp_gueltigab_Datum, double agp_agp)
{
	char msg[200];
	long status = SQL_OK;

	if (zartpreis_rec_count > 0)
	{
		for (int index = 0; index < zartpreis_rec_count; index++)
		{
			if (zartpreis_recs[index]->DATUMGUELTIGAB > agp_gueltigab_Datum)
			{
				if (zartpreis_recs[index]->AGP < 0.01f)
				{
					// Update record
					zartpreis_recs[index]->AGP = agp_agp;
					status = UpdateRecord_ZartPreis(zartpreis_recs[index]);
					snprintf(msg, sizeof(msg) - 1,
						"Update: Artikel_Nr %ld, Gueltig Ab: %ld, Grosso: %.2f, Agp: %.2f",
						zartpreis_recs[index]->ARTIKEL_NR, zartpreis_recs[index]->DATUMGUELTIGAB, zartpreis_recs[index]->GROSSO, zartpreis_recs[index]->AGP);
					wrap_logging(S_DEBUG, "Transfer", msg);
				}
				else 
				{
					// We found a non-zero AGP in the future, so we stop propagating this AGP
					break;
				}
			}
			else if (zartpreis_recs[index]->DATUMGUELTIGAB == agp_gueltigab_Datum)
			{
				// Update record
				zartpreis_recs[index]->AGP = agp_agp;
				status = UpdateRecord_ZartPreis(zartpreis_recs[index]);
				snprintf(msg, sizeof(msg) - 1,
					"Update: Artikel_Nr %ld, Gueltig Ab: %ld, Grosso: %.2f, Agp: %.2f",
					zartpreis_recs[index]->ARTIKEL_NR, zartpreis_recs[index]->DATUMGUELTIGAB, zartpreis_recs[index]->GROSSO, zartpreis_recs[index]->AGP);
				wrap_logging(S_DEBUG, "Transfer", msg);

			}
			else if (zartpreis_recs[index]->DATUMGUELTIGAB < agp_gueltigab_Datum)
			{
				// Insert Record use old values for other fields
				zartpreis_recs[index]->AGP = agp_agp;
				zartpreis_recs[index]->DATUMGUELTIGAB = agp_gueltigab_Datum;
				InsertRecord_ZartPreis(zartpreis_recs[index]);
				snprintf(msg, sizeof(msg) - 1,
					"Insert: Artikel_Nr %ld, Gueltig Ab: %ld, Grosso: %.2f, Agp: %.2f",
					zartpreis_recs[index]->ARTIKEL_NR, agp_gueltigab_Datum, zartpreis_recs[index]->GROSSO, zartpreis_recs[index]->AGP);
				wrap_logging(S_DEBUG, "Transfer", msg);
			}
		}
	}

	return status;
}

// Updates existing record ZartPreis
static long UpdateRecord_ZartPreis(struct ZARTPREIS *zrecord)
{
	// Write Update logic
	long lStatus;
	char PrimeKeyCond[100];
	struct ZARTPREIS BufPreisOld;

	snprintf(PrimeKeyCond, sizeof(PrimeKeyCond) - 1, "ARTIKEL_NR = %7ld and DATUMGUELTIGAB = %ld", zrecord->ARTIKEL_NR, zrecord->DATUMGUELTIGAB);

	lStatus = ReadRecord_ZartPreis(zrecord->ARTIKEL_NR, zrecord->DATUMGUELTIGAB, &BufPreisOld, errmld);
	if (SQL_OK == lStatus)
	{
		lStatus = FdDelayUpdateRecord(fd_zartpreis, zrecord, &BufPreisOld, PrimeKeyCond, errmld);
	}
	if (SQL_OK == lStatus)
	{
		lStatus = WriteZAPflege(zrecord->ARTIKEL_NR, zrecord->DATUMGUELTIGAB, errmld);
		if (SQL_OK == lStatus)
		{
			lStatus = FdTransactWithoutWork(errmld);
		}
	}

	return lStatus;
}

// Inserts new record into ZartPreis
static long InsertRecord_ZartPreis(struct ZARTPREIS *zrecord)
{
	// Write Insert logic
	long lStatus;
	char PrimeKeyCond[100];
	char errmld[100];

	snprintf(PrimeKeyCond, sizeof(PrimeKeyCond) - 1, "ARTIKEL_NR = %7ld and DATUMGUELTIGAB = %ld",
		zrecord->ARTIKEL_NR, zrecord->DATUMGUELTIGAB);

	if (SQL_OK == (lStatus = FdDelayInsertRecord(fd_zartpreis, zrecord, PrimeKeyCond, errmld)))
	{
		lStatus = WriteZAPflege(zrecord->ARTIKEL_NR, zrecord->DATUMGUELTIGAB, errmld);
		if (SQL_OK == lStatus)
		{
			lStatus = FdTransactWithoutWork(errmld);
		}
	}

	return lStatus;
}

/* ---------------------------------------- */
static long ReadRecord_ZartPreis(long artikel_nr, long datumgueltigab, struct ZARTPREIS* BufPreisOld, char *errmld)
{
	char PrimeKeyCond[100];

	sprintf(PrimeKeyCond, "ARTIKEL_NR = %7ld and DATUMGUELTIGAB = %ld", artikel_nr, datumgueltigab);

	return FdReadRecord(fd_zartpreis, PrimeKeyCond, BufPreisOld, errmld);
}


// Writes to ZAPFlege table
static int WriteZAPflege(long art_no, long date, char * errmld)
{
	long status;
	char sql[100];
	long dummy;

	snprintf(sql, sizeof(sql) - 1,
		"SELECT datum FROM zapflege"
		" WHERE artikel_nr = %ld AND datum = %ld",
		art_no, date);

	status = SqlRead(sql, &dummy, NULL);

	if (100L == status)
	{
		snprintf(sql, sizeof(sql) - 1,
			"INSERT INTO zapflege (artikel_nr, datum)"
			" VALUES (%ld, %ld)",
			art_no, date);

		status = SqlExecuteImm(sql);
	}

	if (SQL_OK != status)
	{
		snprintf(errmld, sizeof(errmld) - 1, "zapflege (Insert einer Zeile): %s", DynErrmld());
	}

	return status;
}

static long GetBufferDesc_Generic(char* cErrmld, size_t len, int* fd, char* tabelle) {
	long s;
	char errmld[100];

	memset(cErrmld, 0, len);
	if (*fd >= 0)
	{
		return SQL_OK;
	}

	if (SQL_OK != (s = OpenBufferDesc(fd, tabelle, NULL, NULL, V_PROTO_VERTEIL, errmld)))
	{
		snprintf(cErrmld, len - 1, "%s\ntabelle %s", errmld, tabelle);
		*fd = -1;
	}
	return s;
}

static long GetBufferDesc_ZartPreis(char *cErrmld, size_t len)
{
	return GetBufferDesc_Generic(cErrmld, len, &fd_zartpreis, "zartpreis");
}

static long GetBufferDesc_Cagpoart(char *cErrmld, size_t len)
{
	return GetBufferDesc_Generic(cErrmld, len, &fd_cagpoart, "cagpoart");
}

/* ---------------------------------------- */
static long ReadRecord_Cagpoart(long agpNr, struct CAGPOART *BufCagpoartOld, char *errmld)
{
	char PrimeKeyCond[50];
	sprintf(PrimeKeyCond, "AGP_NR = %ld", agpNr);

	return FdReadRecord(fd_cagpoart, PrimeKeyCond, BufCagpoartOld, errmld);
}

// Updates existing record ZartPreis
static long UpdateRecord_Cagpoart(long agpNr)
{
	// Write Update logic
	long lStatus;
	char PrimeKeyCond[50];
	struct CAGPOART BufCagpoartOld;
	struct CAGPOART cagpoart_rec;

	if (SQL_OK == (lStatus = GetBufferDesc_Cagpoart(errmld, sizeof(errmld))))
	{
		sprintf(PrimeKeyCond, "AGP_NR = %ld ", agpNr);
		lStatus = ReadRecord_Cagpoart(agpNr, &BufCagpoartOld, errmld);
		cagpoart_rec = BufCagpoartOld;
		cagpoart_rec.TXN_STATUS = 2;
		cagpoart_rec.DATUM_AENDER = GetPhoDate();

		if (SQL_OK == lStatus)
		{
			lStatus = FdDelayUpdateRecord(fd_cagpoart, &cagpoart_rec, &BufCagpoartOld, PrimeKeyCond, errmld);
			if (SQL_OK == lStatus)
			{
				lStatus = FdTransactWithoutWork(errmld);
			}
		}
	}
	return lStatus;
}


/*-----------------Cleanup API--------------------------*/

/*------Cleanup AGP import data----------------------------------------------
 1. Cleanup imports in status transferred and deleted older than 3 months.
 2. Cleanup imports in imported status older than 6 months.
 3. Cleanup tables cagpart and cagpoart for selected imports in step 1 and 2.
------------------------------------------------------------------------------*/
long BeginAgpCleanup()
{
	int    fd;
	char   sql[200];
	long   s, created, agpNr = -1;
	long   currentDate, cutoffDate1, cutoffDate2;
	short  txnState;
	double count = -1;
	// Gets cutoff dates for AGP nr selection
	currentDate = GetPhoDate();
	cutoffDate1 = AddDayToPhoDate(currentDate, -MAX_DAYS_DEL_TRA_CLEANUP);
	cutoffDate2 = AddDayToPhoDate(currentDate, -MAX_DAYS_IMP_CLEANUP);

	// Logs beginning of cleanup job
	snprintf(errmld, sizeof(errmld) - 1, " Starting AGP import cleanup with current date: %ld, Cutoff date deleted and "
		"transferred: %ld, Cutoff date imported: %ld.", currentDate, cutoffDate1, cutoffDate2);
	wrap_logging(S_HINWEIS, "Cleanup", errmld);

	// Select eligible AGP Nr for cleanup
	snprintf(sql, sizeof(sql) - 1, "SELECT COUNT(*) FROM CAGPOART WHERE (( TXN_STATUS IN ( 2, 4) AND DATUM_ANLAGE < %ld ) "
		" OR ( TXN_STATUS = 1 AND DATUM_ANLAGE < %ld )) ", cutoffDate1, cutoffDate2);
	//test only 
	/*snprintf(sql, sizeof(sql) - 1, "SELECT COUNT(*) FROM CAGPOART WHERE (( TXN_STATUS IN ( 2, 4) AND DATUM_ANLAGE < %ld ) "
								   " OR ( TXN_STATUS = 1 AND DATUM_ANLAGE < %ld )) AND AGP_NR = 1 ", cutoffDate1, cutoffDate2);*/
	s = SqlRead(sql, &count, NULL);

	if (SQL_OK == s)
	{
		if (count > 0)
		{
			snprintf(errmld, sizeof(errmld) - 1, " %d AGP import(s) eligible for cleanup in CAGPOART.", (int)count);
			wrap_logging(S_HINWEIS, "Cleanup", errmld);
			// Select eligible AGP Nr for cleanup			
			snprintf(sql, sizeof(sql) - 1,
				"SELECT AGP_NR, TXN_STATUS, DATUM_ANLAGE FROM CAGPOART"
				"  WHERE ((TXN_STATUS IN ( 2, 4) AND DATUM_ANLAGE < %ld ) OR "
				" (TXN_STATUS = 1 AND DATUM_ANLAGE < %ld )) ORDER BY DATUM_ANLAGE ASC", cutoffDate1, cutoffDate2);

			// Open DB Cursor
			s = SqlOpenCsWh(&fd, sql);

			if (SQL_OK == s)
			{
				// Begin Fetch
				while (SQL_OK == (s = SqlFetch(fd, 1, &agpNr, &txnState, &created, NULL)))
				{
					if (agpNr > 0)
					{
						s = CleanupAgpImport(agpNr, txnState, created);
						if (SQL_NOK == s)
						{
							// When cleanup failed
							snprintf(errmld, sizeof(errmld) - 1, " Cleanup failed for AGP NR: %ld.", agpNr);
							wrap_logging(S_FEHLER, "Cleanup", errmld);
						}
					}
				}
				(void)SqlCloseCs(fd);
			}

			if (SQL_OK == s || SQL_NO_MORE_DATA == s)
			{
				s = SQL_OK;
			}
			else
			{
				s = SQL_NOK;
				wrap_logging(S_FEHLER, "Cleanup", "Error in AGP imports cleanup.");
			}
		}
		else
		{
			// When no entry is eligible for cleanup
			wrap_logging(S_HINWEIS, "Cleanup", "No AGP import eligible for cleanup in CAGPOART.");
		}
	}
	else
	{
		s = SQL_NOK;
		wrap_logging(S_FEHLER, "Cleanup", "Error reading CAGPOART data for cleanup.");
	}

	// Logs ending of cleanup job
	wrap_logging(S_HINWEIS, "Cleanup", "Finishing AGP import cleanup.");

	return s;
}

// Cleanup of AGP import data 
static long CleanupAgpImport(long agpNr, short txnState, long created)
{	
	char sql[150];
	long s;

	// Logs beginning of cleanup 
	snprintf(errmld, sizeof(errmld) - 1,
		"Starting cleanup for AGP NR: %ld (state: %d, created: %ld).",
		agpNr, txnState, created);
	wrap_logging(S_HINWEIS, "Cleanup", errmld);

	s = SqlBeginWork(); // Starts transaction

	if (SQL_OK != s)
	{
		wrap_logging(S_FEHLER, "Cleanup", "Error starting transaction.");
		return SQL_NOK;
	}

	// Deletes the CAGPART datei
	snprintf(sql, sizeof(sql) - 1, "DELETE FROM CAGPART WHERE AGP_NR = %ld", agpNr);
	s = SqlExecuteImm(sql);

	if (SQL_OK != s)
	{
		snprintf(errmld, sizeof(errmld) - 1, "Error deleting CAGPART data for AGP_NR: %ld.", agpNr);
		wrap_logging(S_FEHLER, "Cleanup", errmld);
		s = SQL_NOK;
	}
	else
	{
		// Deletes the CAGPOART datei
		snprintf(sql, sizeof(sql) - 1, "DELETE FROM CAGPOART WHERE AGP_NR = %ld", agpNr);
		s = SqlExecuteImm(sql);
		if (SQL_OK != s)
		{
			snprintf(errmld, sizeof(errmld) - 1, "Error deleting CAGPOART data for AGP_NR: %ld.", agpNr);
			wrap_logging(S_FEHLER, "Cleanup", errmld);
			s = SQL_NOK;
		}
	}
	if (SQL_OK == s)
	{
		SqlCommitWork();   // Commits all transactions
		snprintf(errmld, sizeof(errmld) - 1, "Finished cleanup for AGP NR: %ld.", agpNr);
		wrap_logging(S_HINWEIS, "Cleanup", errmld);
	}
	else
	{
		SqlRollbackWork(); // Rollback all transactions
	}

	return s;
}
