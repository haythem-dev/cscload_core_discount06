
/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ctype.h>
#include <phodate.h>
#include <phozeit.h>
#include <libscsvoodoo.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>
#include <math.h>
#include "agpTransaction.h"
#include "agpTransfer.h"

/* ------------------------------------------------------------------- */
#define SQL_SETISOLA_ERROR   (-554)
void CloseBase()
{
	SqlExecuteImm("close database");
}

/* ------------------------------------------------------------------- */
long OpenBase(const char * const db, char *errmld)
{
	long s;

	char base[50];
	strcpy(base, "database ");
	strcat(base, db);

	s = SqlExecuteImm(base);
	if (s != 0)
	{
		strcpy(errmld, base);
		strcat(errmld, ": ");
		strcat(errmld, DynErrmld());
		return s;
	}

	s = SqlExecuteImm("set isolation to dirty read");
	if (s == SQL_SETISOLA_ERROR) s = 0;
	if (s != 0)
	{
		strcpy(errmld, "set isolation: ");
		strcat(errmld, DynErrmld());
		CloseBase();
		return s;
	}

	s = SqlExecuteImm("SET LOCK MODE TO WAIT 10");
	if (s == SQL_SETISOLA_ERROR) s = 0;
	if (s != 0)
	{
		strcat(errmld, "set lock mode: ");
		strcat(errmld, DynErrmld());
		CloseBase();
		return s;
	}
	return 0;
}

/* ---------------- Programm-Ausahl ----------------- */
static void Usage(char *buf)
{
	strcpy(buf, "usage:\n");
}

/* ---------------------------------------------------------------------- */
static void LadeUsage(char *buf)
{
	strcat(buf, "- zpagpgnart -srv <Server> -db <DB Name> -prog <Programm Nr.>\n\n"
		"Der Batch transferiert den AGP (spezifisch für CH) in die Tabelle zartpreis. Parameter:\n"
		"\t-srv: Name des DB Servers\n\t-db: Name der Datenbank\n\t-prog: 1 für den AGP Transfer, 2 für den AGP Cleanup\n");

}

/* ---------------------------------------------------------------------- */
void ProgUsage(char *buf)
{
	Usage(buf);
	LadeUsage(buf);
}

/* ---------------------------------------------------------------------- */
long ProgAuswahl(argopts_t* argopts, char *buf, size_t buflen)
{
	char errmld[10];
	long s = OpenBase(argopts->dbname, buf);

	if (SQL_OK == s)
	{
		s = OpenPflege("zpagpgnart", buf);
		if (SQL_OK == s)
		{
			switch (argopts->progNr)
			{
			case 1:
				s = BeginTransfer(argopts->importNo, argopts->pznFrom, argopts->pznTo);
				break;
			case 2:
				s = BeginAgpCleanup();
				break;
			default:
				s = SQL_NOK;
				snprintf(buf, buflen - 1, "Programm-Teil: %d nicht vorhanden", argopts->progNr);
				break;
			}
			ClosePflege(errmld);
		}

		CloseBase();
	}
	return s;
}
