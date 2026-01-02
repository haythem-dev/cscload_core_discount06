/* loadpharmgrpvse.cxx */

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadpharmgrpvse"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "pharmacygroups.h"
#include "pplib/allg.h"
#include "errno.h"
EXEC SQL include sqlca;

/* #undef NULL */

#define DEBUG_SECTION      if ( debug_enabled ) {
#define END_DEBUG_SECTION  }
#define OK                 0
#define NO                 0
#define YES                1
#define ERROR             -1
#define INSERT             1
#define NOT_FOUND          1
#define FILE_NOT_FOUND     1
#define WARNING           -2
#define HINW             'H'
#define FEHL             'F'
#define RIO_EOF          110
#define BLANC            ' '
#define STR_NULL         "+000000000000000"
#define SQLCODE            sqlca.sqlcode
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND
#define CHAR_FIELD_SEPARATOR ';'
#define NUMBER_OF_FIELDS  13

#define DATABASE "phosix"
#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                   sqlca.sqlcode, sqlca.sqlerrd[1],sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return sqlca.sqlcode; }

// Längen der Felder, wie sie in der Inputdatei geliefert werden
// (weichen teilweise von den DB-Feldlängen ab)
#define LEN_FILE_PHARMACYGROUPID      3
#define LEN_FILE_GROUP_NAME          30
#define LEN_FILE_GROUP_TYPE           1
#define LEN_FILE_PERCENT              6
#define LEN_FILE_CONTRIBUTION         4
#define LEN_FILE_CUSTOMERNO           7
#define LEN_FILE_OMG_OWN_CONT         1
#define LEN_FILE_PRICE_BASIS_PURCH    1
#define LEN_FILE_RECLAIM_OMG_DISC     1
#define LEN_FILE_SPECIALGROUP         3
#define LEN_FILE_SPECIALGROUPREFNO    7
#define LEN_FILE_GROUPING_VIS         1
#define LEN_FILE_BRANCHNO             2

 /***** GLOBALE **************************************************************/

 FILE *pharmgrpfile;
 char pfadpharmgrp[81];
 char log_file [300 + 1];
 int debug_enabled = NO;

 EXEC SQL BEGIN DECLARE SECTION;
 short filialnr = 0;
 struct s_PHARMGRPREC {
	 char    PHARMACYGROUPID[LEN_FILE_PHARMACYGROUPID + 1];
	 char    GROUP_NAME[LEN_FILE_GROUP_NAME + 1];
	 char    GROUP_TYPE[LEN_FILE_GROUP_TYPE + 1];
	 char    PERCENT[LEN_FILE_PERCENT + 1];
	 char    CONTRIBUTION[LEN_FILE_CONTRIBUTION + 1];
	 char    CUSTOMERNO[LEN_FILE_CUSTOMERNO + 1];
	 char    OMG_OWN_CONT[LEN_FILE_OMG_OWN_CONT + 1];
	 char    PRICE_BASIS_PURCH[LEN_FILE_PRICE_BASIS_PURCH + 1];
	 char    RECLAIM_OMG_DISC[LEN_FILE_RECLAIM_OMG_DISC + 1];
	 char    SPECIALGROUP[LEN_FILE_SPECIALGROUP + 1];
	 char    SPECIALGROUPREFNO[LEN_FILE_SPECIALGROUPREFNO + 1];
	 char    GROUPING_VIS[LEN_FILE_GROUPING_VIS + 1];
	 char    BRANCHNO[LEN_FILE_BRANCHNO + 1];
 };
 EXEC SQL END DECLARE SECTION;

 EXEC SQL BEGIN DECLARE SECTION;
	char datenbank[60];
 EXEC SQL END DECLARE SECTION;

 
 /***** DECLARATION **********************************************************/
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char mld, int rc );
 void WriteLogInfo( char *error_msg, char mld, int rc );
 int StartLoadPharmGrp( char *error_msg );
 int PreparePharmGrpRec( struct s_PHARMGRPREC * pPharmGrpRec, int recno );
 int PrepareLoadPharmGrp( char *error_msg );
 int LoadPharmGrp( struct s_PHARMGRPREC * pPharmGrpRec, char *error_msg );
 
 /***** MAIN *****************************************************************/

 int main( int argc, char **argv  )
 {
   char 	error_msg[81];
   char 	*schalter;
   int 		i;
   int 		skip;
   int 		datum = 0;
   int 		rc = 0;
   char 	*fun = "main";
   char *LOG_FILE = "wws.log";
   char *LOG_PATH;
   char logpath[256+1];

   if ((LOG_PATH = getenv("LOG_PATH")) == (char *)0)
   {
	   strcpy(logpath, ".");
   }
   else
   {
	   strcpy(logpath, LOG_PATH);
   }
   sprintf(log_file, "%s/%s", logpath, LOG_FILE);

   PrintMsg(fun, "START", HINW, 0);

   sprintf(datenbank,"%s",DATABASE);
     
   setbuf( stdout, 0 );              /* printf sofort */
   skip = NO;
   for ( i = 1; i < argc; i++ )
   {
     	if ( skip )
	  	{
	  		skip = NO;
	  		continue;
	  	}
       	schalter = argv[i];
       	if ( !strcmp( schalter, "-dg" ) )
	   		debug_enabled = YES;
		else if ( !strcmp( schalter, "-file" ) )
		{
			i++;
			if (strlen(argv[i]) >= sizeof(pfadpharmgrp))
			{
				printf("value for parameter -file too long\n");
				skip = ERROR;
				break;
			}
			strcpy( pfadpharmgrp, argv[i] );
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			if (strlen(argv[i]) >= sizeof(datenbank))
			{
				printf("value for parameter -db too long\n");
				skip = ERROR;
				break;
			}
			strcpy( datenbank, argv[i] );
		}
		else if ( !strcmp( schalter, "-vz" ) )
		{
			filialnr = atoi(argv[i + 1]);
			skip = YES;
		}
  		else if ( !strcmp( schalter, "-la" ) )
	   		;
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return OK;
		}
        else
	  	{
	  		skip = ERROR;
	  		break;
	  	}
   }                                            
   if ( argc == 1 || skip == ERROR )
   {
      printf( "  usage: %s\n\t"
	      " { -dg <Debugging> }\n\t"
		  " { -db datenbankname <Datenbankname> }\n\t"
		  " { -file dateiname <Name der Eingabedatei> }\n\t"
	      " [ -la]\n\t"
		  , argv[0] );
      return 2;
   }
	
   if (strlen(pfadpharmgrp) == 0)
   {
	   PrintMsg(fun, "keine Eingabedatei angegeben", FEHL, 0);
	   return 2;
   }

   if ( (rc = StartLoadPharmGrp(error_msg)) != 0 )
   {
	  PrintMsg( fun, "mit Fehler beendet", FEHL, 0 );
      return rc;
   }
 
   PrintMsg( fun, "ENDE", HINW, 0 );
   return OK;
 }

 /***** PRINT-MSG ************************************************************/

 void PrintMsg( char *fun, char *error_msg, char mld, int rc )
 {
   FILE *fp;
   struct tm *localtime();
   struct tm *zeit;
   long hour1;
   pid_t pid;
   long time();

   if ( rc > INSERT )
      return;

   pid = getpid();
   hour1 = time( &hour1 );
   zeit  = localtime( &hour1 );
   fp = fopen( log_file, "a" );
   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s",
	    mld,
	    filialnr,
		zeit->tm_mday,
        zeit->tm_mon + 1,
        (zeit->tm_year+1900)%100,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    PROJECTNAME,
	    fun );

   fprintf(fp," %s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER EINKAUFSGRUPPEN *************************************/

 int StartLoadPharmGrp(char *error_msg )
{
	char *fun = "StartLoadPharmGrp";
	
	int zaehler, rc;
	char msg[128];
	char rec[1000];
	char prevBranchNo[LEN_FILE_BRANCHNO + 1];

	EXEC SQL BEGIN DECLARE SECTION;
	short filno;
	struct s_PHARMGRPREC* pPharmGrpRec;
	EXEC SQL END DECLARE SECTION;
	
	pPharmGrpRec = (struct s_PHARMGRPREC*) rec;

	sprintf(msg, "gestartet ");
	PrintMsg(fun, msg, HINW, 0);

	EXEC SQL set lock mode to wait 20;
	ERROR_MSG2("lock mode:")
   	EXEC SQL database :datenbank;
	ERROR_MSG2("database:")
   	EXEC SQL set isolation to dirty read;
	ERROR_MSG2("set isolation:")

	strcpy(prevBranchNo, "");

	if ( (rc = PrepareLoadPharmGrp(error_msg)) != 0 )
	{
		return rc;	
	}
	
	if ( (pharmgrpfile = fopen( pfadpharmgrp, "r" ) ) == NULL )
	{
		PrintMsg( fun, pfadpharmgrp, FEHL, 0 );
		PrintMsg( fun, "Inputdatei kann nicht geoeffnet werden", FEHL, 0 );
		return -1;
	}

	/* wir erhalten in einer Inputdatei alle Pharmacygruppen einer Filiale
	   da pro Filiale max. 1000 Pharmacygruppen existieren koennen, fuehren wir alle
   	   Datenaenderungen in einer einzigen Transaktion durch
	   wir loeschen alle Pharmacygruppen der Filiale und fuegen anschliessend die in
	   in der Inputdatei gelieferten Gruppen neu ein
	   wenn etwas schiefgeht, wird beim exit ein implizites ROLLBACK ausgefuehrt,
	   und der Ausgangszustand ist wieder hergestellt */

	EXEC SQL begin work;
	ERROR_MSG2("begin work(0):")

	for ( zaehler = 0; ; zaehler++ )
	{
		if (fread(rec, sizeof(struct s_PHARMGRPREC) + 1, 1, pharmgrpfile) == 0)
        {
		   	DEBUG_SECTION
			fprintf(stderr,"%d Saetze gelesen\n", zaehler);
   			END_DEBUG_SECTION
			break;
	 	}
	   	DEBUG_SECTION
		fprintf(stderr,"%s\n", rec);
		END_DEBUG_SECTION

		if ((rc = PreparePharmGrpRec(pPharmGrpRec, zaehler)) < 0)
		{
			return rc;
		}

		if (strcmp(pPharmGrpRec->BRANCHNO, prevBranchNo) != 0)
		{
			if (strcmp(prevBranchNo, "") != 0)
			{
				EXEC SQL commit work;
				ERROR_MSG2("commit work:")

				EXEC SQL begin work;
				ERROR_MSG2("begin work:")
			}

			EXEC SQL EXECUTE del_pharmgrp using :pPharmGrpRec->BRANCHNO;
			ERROR_MSG2("execute del_pharmgrp:")

			strcpy(prevBranchNo, pPharmGrpRec->BRANCHNO);
		}

		if ((rc = LoadPharmGrp(pPharmGrpRec, error_msg)) < 0)
		{
			return rc;
		}
	}

	EXEC SQL commit work;
	ERROR_MSG2("commit work(0):")

	sprintf(error_msg, "beendet - PHARMACYGROUPS Saetze gelesen/eingefuegt: %d", zaehler);
 	PrintMsg( fun, error_msg, HINW, -1 );

	fclose(pharmgrpfile);

	return OK;
}

int PreparePharmGrpRec(struct s_PHARMGRPREC* pPharmGrpRec, int recno)
{
   char *fun = "PreparePharmGrpRec";
   int rc = 0;
   char msg[80];
   int fld_len = 0;
   char *fld_name = NULL;
   char *fld_val = NULL;
   char *pch = NULL;

   // sanity check: pruefe, ob jedes Feld mit einem Feldseparator (';') abgeschlossen wird
   for (int i = 0; i < NUMBER_OF_FIELDS; i++)
   {
	   switch (i)
	   {
	   case 0:
		   fld_val = pPharmGrpRec->PHARMACYGROUPID;
		   fld_name = "PHARMACYGROUPID";
		   fld_len = LEN_FILE_PHARMACYGROUPID;
		   break;
	   case 1:
		   fld_val = pPharmGrpRec->GROUP_NAME;
		   fld_name = "GROUP_NAME";
		   fld_len = LEN_FILE_GROUP_NAME;
		   break;
	   case 2:
		   fld_val = pPharmGrpRec->GROUP_TYPE;
		   fld_name = "GROUP_TYPE";
		   fld_len = LEN_FILE_GROUP_TYPE;
		   break;
	   case 3:
		   fld_val = pPharmGrpRec->PERCENT;
		   fld_name = "PERCENT";
		   fld_len = LEN_FILE_PERCENT;
		   break;
	   case 4:
		   fld_val = pPharmGrpRec->CONTRIBUTION;
		   fld_name = "CONTRIBUTION";
		   fld_len = LEN_FILE_CONTRIBUTION;
		   break;
	   case 5:
		   fld_val = pPharmGrpRec->CUSTOMERNO;
		   fld_name = "CUSTOMERNO";
		   fld_len = LEN_FILE_CUSTOMERNO;
		   break;
	   case 6:
		   fld_val = pPharmGrpRec->OMG_OWN_CONT;
		   fld_name = "OMG_OWN_CONT";
		   fld_len = LEN_FILE_OMG_OWN_CONT;
		   break;
	   case 7:
		   fld_val = pPharmGrpRec->PRICE_BASIS_PURCH;
		   fld_name = "PRICE_BASIS_PURCH";
		   fld_len = LEN_FILE_PRICE_BASIS_PURCH;
		   break;
	   case 8:
		   fld_val = pPharmGrpRec->RECLAIM_OMG_DISC;
		   fld_name = "RECLAIM_OMG_DISC";
		   fld_len = LEN_FILE_RECLAIM_OMG_DISC;
		   break;
	   case 9:
		   fld_val = pPharmGrpRec->SPECIALGROUP;
		   fld_name = "SPECIALGROUP";
		   fld_len = LEN_FILE_SPECIALGROUP;
		   break;
	   case 10:
		   fld_val = pPharmGrpRec->SPECIALGROUPREFNO;
		   fld_name = "SPECIALGROUPREFNO";
		   fld_len = LEN_FILE_SPECIALGROUPREFNO;
		   break;
	   case 11:
		   fld_val = pPharmGrpRec->GROUPING_VIS;
		   fld_name = "GROUPING_VIS";
		   fld_len = LEN_FILE_GROUPING_VIS;
		   break;
	   case 12:
		   fld_val = pPharmGrpRec->BRANCHNO;
		   fld_name = "BRANCHNO";
		   fld_len = LEN_FILE_BRANCHNO;
		   break;
	   default:
		   break;
	   }

	   if (fld_val[fld_len] == CHAR_FIELD_SEPARATOR)
	   {
		   // ersetze Feldseparator durch 0-Byte
		   fld_val[fld_len] = '\0';
	   }
	   else
	   {
		   sprintf(msg, "Satz #%03.3d: ungueltiger Separator nach %s", recno + 1, fld_name);
		   PrintMsg(fun, msg, FEHL, 0);
		   return -1;
	   }
   }

   // fuer die Dezimalwerte ',' durch '.' ersetzen
   if ((pch = strchr(pPharmGrpRec->PERCENT, ',')) != NULL)
   {
	   *pch = '.';
   }
   if ((pch = strchr(pPharmGrpRec->CONTRIBUTION, ',')) != NULL)
   {
	   *pch = '.';
   }

   return 0;
}

int PrepareLoadPharmGrp(char *error_msg)
{
	char *fun = "PrepareLoadPharmGrp";
	int rc = 0;

	EXEC SQL BEGIN DECLARE SECTION;
	char str[2048];
	EXEC SQL END DECLARE SECTION;

	strcpy(str, "insert into pharmacygroups (");
	strcat(str, PHARMACYGROUPS_PELISTE);
	strcat(str, " ) values ");
	strcat(str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ) ");

	exec sql prepare ins_pharmgrp from :str;
	ERROR_MSG2("prepare ins_pharmgrp")

	strcpy(str, "delete from pharmacygroups");
	strcat(str, " where branchno = ?");

	exec sql prepare del_pharmgrp from :str;
	ERROR_MSG2("prepare del_pharmgrp")

	return 0;
}

 
int LoadPharmGrp(struct s_PHARMGRPREC* pPharmGrpRec, char *error_msg)
{
	char *fun = "LoadPharmGrp";

	EXEC SQL BEGIN DECLARE SECTION;
	struct s_PHARMGRPREC* prec;
	EXEC SQL END DECLARE SECTION;

	prec = pPharmGrpRec;

	EXEC SQL EXECUTE ins_pharmgrp using
					:prec->PHARMACYGROUPID,
		            :prec->GROUP_NAME,
					:prec->GROUP_TYPE,
					:prec->PERCENT,
					:prec->CONTRIBUTION,
					:prec->CUSTOMERNO,
					:prec->OMG_OWN_CONT,
					:prec->PRICE_BASIS_PURCH,
					:prec->RECLAIM_OMG_DISC,
					:prec->SPECIALGROUP,
					:prec->SPECIALGROUPREFNO,
					:prec->GROUPING_VIS,
					:prec->BRANCHNO
		            ;
    ERROR_MSG2("ins_pharmgrp:")

	return OK;
}

/***** ENDE *****************************************************************/
