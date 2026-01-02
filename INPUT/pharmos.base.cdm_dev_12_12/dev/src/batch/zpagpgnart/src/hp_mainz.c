/* ---------------------------------------------------------------------- *
 *   Aufgabe        : Start of zpagpgnart				                  *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 03.08.2021                                          *
 *   Autor          : Kirtan Singh                                        *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.0.0.0 : zpagpgnart 03/08/2021 Kirtan Singh";
}

 /*!
 \page page44 zpagpgnart - AGP Preise von import Tabelle in zartpreis transferrieren

 ________________________________________________________________________________________
 \version	1.0.0.0
 \date		03.08.2021
 \internal
 - KS: CPR-200938 - transfer AGP Preise von cagpoart, cagpart in zartpreis
 \endinternal
 ________________________________________________________________________________________

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "libscsvoodoo/libscsvoodoo.h"
#include "logfile.h"
#include "agpTransfer.h"
#include "agpTransaction.h"

 /* ---------------- UebertragungsPuffer ------------ */
static char ret_buf[5000];

void handle_options(int argc, char* argv[], argopts_t* argopts)
{
	/*
	** Expected arguments passing format:
	** -key value
	*/
	memset(argopts, 0, sizeof(argopts_t));

	for (int p = 1; p < argc-1; p+=2)	
	{
		char* optValue = argv[p+1];

		if (!strncmp(argv[p], "-db", 3))
		{
			strncpy(argopts->dbname, optValue, sizeof(argopts->dbname) - 1);
		}
		else if (!strncmp(argv[p], "-import", 7))
		{
			argopts->importNo = atoi(optValue);
		}
		else if (!strncmp(argv[p], "-loglevel", 9))
		{
			wrap_logging(atoi(optValue), NULL, NULL);
		}
		else if (!strncmp(argv[p], "-prog", 5))
		{
			argopts->progNr = atoi(optValue);
		}
		else if (!strncmp(argv[p], "-pznFrom", 8))
		{
			argopts->pznFrom = atol(optValue);
		}
		else if (!strncmp(argv[p], "-pznTo", 6))
		{
			argopts->pznTo = atol(optValue);
		}
		else if (!strncmp(argv[p], "-srv", 4))
		{
			strncpy(argopts->srvname, optValue, sizeof(argopts->srvname) - 1);
		}
	}

	if (argopts->pznFrom > argopts->pznTo)
	{
		long swap = argopts->pznFrom;
		argopts->pznFrom = argopts->pznTo;
		argopts->pznTo = swap;
	}
}

/* ---------------- main-Programm WINDOWS ------------------ */
#if defined(WIN32)

void main(int argc, char *argv[])
{
	long      s;
	HNMP      handle;
	argopts_t argopts;

	handle_options(argc, argv, &argopts);
	if ((s = ViaEshuOpenEx(&handle, argopts.srvname, "uiserv", 55260)) == 0)
	{
		if (argopts.progNr)
		{
			s = ProgAuswahl(&argopts, ret_buf, sizeof(ret_buf));
		}
		else
		{
			s = SQL_NOK;
			ProgUsage(ret_buf);
		}
		NmpCloseHandle(handle);
	}
	else
	{
		snprintf(ret_buf, sizeof(ret_buf) - 1, "Pipe nicht eroeffnet: %s", DynErrmld());
	}

	printf("%s\n", ret_buf);
	exit(SQL_OK == s ? 0 : 1);
}

/* --- UNIX ------------------------------------------- */
#else

#include <sys/types.h>
#include <sys/stat.h>

/* --- Signal-Behandlung ------------------------------------------- */
#include <signal.h>

/* ---------- Abbruch-Signal------------------------------------- */
static int sig_accepted = 0;

static void intrpt_term(int sig)
{
	signal(SIGTERM, SIG_IGN);
	sig_accepted = 1;
}

static void signal_beh(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
}

/* ------------ LogFile ------------------------------ */
#include "logfile.h"

#define MAX_PROG 30
static char program[MAX_PROG + 1];              /* Programmname */

void LogOut(int status, char *str)
{
	if (*str)
		write_logfile(status, program, str);
}

static void LogOutParam(int status, int anz, char *str[])
{
	char *str1;
	int lng;
	int i;

	lng = 0;
	for (i = 0; i < anz; i++)
		lng += strlen(str[i]);

	str1 = malloc(lng + anz + 1);
	if (str1 == NULL)
		return;

	*str1 = '\0';
	for (i = 0; i < anz; i++)
	{
		strcat(str1, str[i]);
		if (i < anz - 1)
			strcat(str1, " ");
	}

	write_logfile(status, program, str1);
	free(str1);
}

static void GetProgram(char *prog, char *str)
{
	int i;
	int found;
	found = 0;
	i = strlen(str) - 1;

	while (i >= 0 && !found)
	{
		found = str[i] == ':' || str[i] == '\\' || str[i] == '/';
		if (!found) i--;
	}
	i++;
	if (strlen(&str[i]) <= MAX_PROG)
		strcpy(prog, &str[i]);
	else
	{
		memcpy(prog, &str[i], MAX_PROG);
		prog[MAX_PROG] = '\0';
	}
}

/* --- Main-Programm UNIX ----------------------------------------------- */
void main(int argc, char *argv[])
{
	int  lng;
	int  anz_arg;
	argopts_t argopts;
	int  lokal;
	long s;

	/* dummy call to prevent from optimizing version string out of binary */
	const char* version = getVersion();

	GetProgram(program, argv[0]);              /* Programmname */
	handle_options(argc, argv, &argopts);

	/* --- Signal-Behandlung */
	signal_beh();

	lng = PipwRead(argc, argv, ret_buf, 0);   /* nichts lesen */
	if (lng == -1)
	{
		anz_arg = argc;     /* Programm wurde lokal aufgerufen */
		lokal = 1;
	}
	else
	{
		anz_arg = argc - 1;  /* von PipwRead wurde ein Zusatzparam. anghaengt */
							 /* argc darf nicht veraendert werden !!!!! */
		lokal = 0;
	}

	LogOut(S_HINWEIS, "--------------------------------------------------");
	LogOut(S_HINWEIS, "START");

	if (anz_arg > 1)
	{
		sig_accepted = 0;
		signal(SIGTERM, intrpt_term);
		LogOutParam(S_HINWEIS, anz_arg - 1, &argv[1]);
		s = ProgAuswahl(&argopts, ret_buf, sizeof(ret_buf));
	}
	else
	{
		s = 1;
		ProgUsage(ret_buf);
	}

	if (!lokal)
		PipwWrite(argc, argv, ret_buf, strlen(ret_buf));

	/* 	else */
	if (s == 0)
	{
		printf("%s\n", ret_buf);
		LogOut(S_HINWEIS, ret_buf);
	}
	else
	{
		printf("%s\n", ret_buf);
		LogOut(S_FEHLER, ret_buf);
	}

	LogOut(S_HINWEIS, "ENDE");

	if (s == 0)
		exit(0);
	else
		exit(1);
}

#endif  /* MSDOS */
