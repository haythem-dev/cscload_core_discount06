/*###########################################################################*/
/*#																			#*/
/*#	BITTE VERLASSEN SIE DIESES PROGRAMM SO, WIE SIE ES VORZUFINDEN WÜNSCHEN #*/
/*#																			#*/
/*###########################################################################*/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tpldchrab"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include "natrastaffeln.h"
#include "artnat.h"
#include "validdiscount.h"
#include <math.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>                                     

exec sql include sqlca;
exec sql include sqltypes;

/*#undef NULL */ 

#define ERROR_MSG(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1] ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define ERROR_MSG2(x,y)       if(sqlca.sqlcode<0) { \
                              sprintf(error_msg,"%s %d/%d bei PZN: %7.7s",x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1],y ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define NOTFOUND           sqlca.sqlcode == SQLNOTFOUND

#define OK                   0
#define NO                   0
#define YES                  1
#define ERROR               -1
#define INSERT               1
#define NOT_FOUND            1
#define FILE_NOT_FOUND       1
#define WARNING             -2
#define HINW               'H'
#define FEHL               'F'
#define RIO_EOF            110
#define RIO_NOFIND         111
#define DATABASE           "pos2ch@db1_pos2_shm"
#define BLANC              ' '
#define STR_ENDE           '\0'
#define L_TEXT             81
#define SQLCODE            sqlca.sqlcode
#define M_DURCHLAUF_COMMIT 140                  /* nach n-saetzen commit  */

FILE *lokaldat;

exec sql begin declare section;
struct RABATTE
{
	char Filiale[2];
	char semi1[1];
	char Artikelnr[7];
	char semi2[1];
	char EKGruppe[3];
	char semi3[1];
	char Von[8];
	char semi4[1];
	char Bis[8];
	char semi5[1];
	char RabattArt[1];
	char semi6[1];
	char StaffelNr[3];
	char semi7[1];
	char RabattEigen[1];
	char semi8[1];
};
struct BARRABATTE
{
	char Filiale[2];
	char semi1[1];
	char Artikelnr[7];
	char semi2[1];
	char EKGruppe[3];
	char semi3[1];
	char Von[8];
	char semi4[1];
	char Bis[8];
	char semi5[1];
	char RabattArt[1];
	char semi6[1];
	char StaffelNr1[3];
	char semi7[1];
	char StaffelWert1[7];
	char semi8[1];
	char StaffelNr2[3];
	char semi9[1];
	char StaffelWert2[7];
	char semi10[1];
	char StaffelNr3[3];
	char semi11[1];
	char StaffelWert3[7];
	char semi12[1];
	char StaffelNr4[3];
	char semi13[1];
	char StaffelWert4[7];
	char semi14[1];
	char StaffelNr5[3];
	char semi15[1];
	char StaffelWert5[7];
	char semi16[1];
	char StaffelNr6[3];
	char semi17[1];
	char StaffelWert6[7];
	char semi18[1];
	char RabattEigen[1];
	char semi19[1];
	char RabattTyp[1];
	char semi20[1];
	char RabattForm[2];
	char semi21[1];
};
exec sql end declare section;

struct RABATTE rabatt;
struct BARRABATTE barrabatt;
char input[1048];
static int RABATTE_LEN = sizeof(rabatt);
char log_file [300 + 1];
char  dateiname[L_TEXT];
int explain = NO;
static int filialnr = 99;
static int lPZN = 0;
static int first = 1;

/***** DECLARATION **********************************************************/

int main						( int, char ** );
void PrintMsg					( char *fun, char *error_msg, char mld, int rc );
int StarteLadenDerRabatte		( char *error_msg);
int PrepareLoadTables			( char *error_msg);
int LoadTables					( char *input, char *error_msg);
int AfterLoadTables				( char *error_msg);
int PrepareLadeDiscountInfo		( char *error_msg);
int PrepareLadeDiscountInfoBar	( char *error_msg);
int PrepareLadeArtikelnatra		( char *error_msg);
int LadeDiscountInfo			( char *input, char *error_msg);
int LadeDiscountInfoBar			( char *input, char *error_msg);
int LadeArtikelnatra			( char *input, char *error_msg);
int DelDiscountInfo				( char *input, char *error_msg);
int DelArtikelnatra				( char *input, char *error_msg);
int AfterLadeDiscountInfo		( char *error_msg);
int AfterLadeDiscountInfoBar	( char *error_msg);
int AfterLadeArtikelnatra		( char *error_msg);
int CloseDatabase				( void );
int LoadParameter				( char *error_msg);

/***** MAIN *****************************************************************/

int main( int argc, char **argv  )
{
	char  error_msg[181];
	char  *schalter;
	int   i;
	char  *fun = "Main";
	char  *LOG_FILE = "wws.log";
	char  *LOG_PATH;
	char  logpath[256 + 1];
	int   rc;
	char  start_msg[121];
	int   status = 0;

	exec sql begin declare section;
	char datenbank[60];
	exec sql end declare section;

	setbuf(stdout,0);

	sprintf(datenbank,"%s",DATABASE);

	strcpy(start_msg, "gestartet mit:");
	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-file" ) )
		{
			strcat(start_msg, " -file");
			i++;
			sprintf( dateiname, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
			status = 1;
			if ( !strncmp( dateiname+strlen(dateiname)-6, "sorbar",6 ) )
			{
				RABATTE_LEN = sizeof(barrabatt);
			}
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			strcat(start_msg, " -db");
			i++;
			sprintf( datenbank, "%s", argv[i] );
			sprintf(start_msg,"%s %s",start_msg,argv[i]);
		}
		else if ( !strcmp( schalter, "-ex" ) )
		{
			strcat(start_msg, " -ex");
			explain = YES;
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
		else
		{
			printf( "  usage: %s\n\t"
				" { -file dateiname <Dateiname> }\n\t"
				" { -db datenbankname <Datenbankname> }\n\t"
				" [ -ex <Explain> ]\n\t",
				argv[0] );
			return 1;
		}
	}
	if(status == 0)
	{
		printf( "  usage: %s\n\t"
			" { -file dateiname <Dateiname> }\n\t"
			" { -db datenbankname <Datenbankname> }\n\t",
			argv[0] );
		return 1;
	}
	filialnr = atoi(dateiname+strlen(dateiname)-9);
	if ( ( lokaldat = fopen( dateiname, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( "main ", "Ladedatei nicht vorhanden", FEHL, 0 );
		return -1;
	}
      

	if ( ( LOG_PATH = getenv("LOG_PATH")) == (char *)0 )
		strcpy( logpath, "." );
	else
		strcpy( logpath, LOG_PATH );
   
	sprintf( log_file, "%s/%s", logpath, LOG_FILE );

	PrintMsg( fun, start_msg, HINW, 0 );
	exec sql database :datenbank;
	ERROR_MSG( "Fehler oeffnen DB" )

	exec sql set lock mode to wait 20;
	ERROR_MSG( "Set LockMode to Wait" )

	exec sql set isolation to dirty read;
	ERROR_MSG( "Set Isolation to Dirty Read" )

	if (explain == YES)
	{
		exec sql set explain on;
		ERROR_MSG( "Set Explain On" )
	}
	if ( PrepareLoadTables( error_msg ) != OK )
		return 8;  
   
	if ( ( rc = StarteLadenDerRabatte( error_msg ) ) != 0 )
	{
		sprintf(start_msg, "Fili: %d %s ",filialnr,fun);
		PrintMsg( start_msg, "mit Fehler beendet", FEHL, rc );
		return 9; 
	}
	sprintf(start_msg, "Fili: %d %s ",filialnr,fun);
	PrintMsg( start_msg, "korrekt beendet", HINW, rc );
	return 0;   
}
 
 /***** STARTE DAS LADEN DER RABATT-TABELLEN ************************************/

int StarteLadenDerRabatte( char *error_msg)
{
	int  zaehler = 0;
	int  rc = OK;
	int  idx;
	int  ende = NO;
	char huelse[20];
	char *fun = "StarteLadenDerRabatte";
	struct RABATTE *rab;

	EXEC SQL begin work;
	ERROR_MSG( "Begin Work" )

	while ( !ende  )
	{
		if(fread( input ,RABATTE_LEN+1, 1 , lokaldat ) == 0)
			break;

/*		if ( zaehler == 0 )
		{
			rab = input;
			sprintf( huelse, "%*.*s",
				2,
				2,
				rab->Filiale );
			filialnr = atoi(huelse);
		}
*/		 
	    if ( zaehler++ % M_DURCHLAUF_COMMIT == 0)
        {
           EXEC SQL commit work;
           ERROR_MSG( "Commit Work" )
          
           EXEC SQL begin work;
           ERROR_MSG( "Begin Work" )
        }
            
        if ( ( rc = LoadTables( input, error_msg ) ) < 0 )
        {
			PrintMsg( fun, error_msg, FEHL, ERROR );
			return ERROR;
		}
        else if ( explain == YES )
           if ( zaehler > 100 ) break;   /* Nur 100 Saetze verarbeiten */

	}      /* ende while */

	EXEC SQL commit work;
	ERROR_MSG( "Commit Work" )

/*	sprintf( error_msg, "Fili: %d Artikellokal ins/upd/del: %d/%d/%d",filialnr, zaehlerInslokal, zaehlerUpdlokal, zaehlerDellokal );
	PrintMsg( fun, error_msg, HINW, OK );
	sprintf( error_msg, "Fili: %d Artikellagerort ins/upd/del: %d/%d/%d",filialnr, zaehlerInsort, zaehlerUpdort, zaehlerDelort );
	PrintMsg( fun, error_msg, HINW, OK );
*/
	rc = OK;
	rc = AfterLoadTables( error_msg );
   
	return rc;
}

/***** PREPARE-LOAD-TABLES *******************************************************/

int PrepareLoadTables( char *error_msg )
{
	int rc;
	if ( ( rc = PrepareLadeDiscountInfo( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeDiscountInfoBar( error_msg ) ) < 0 ) return rc;
	if ( ( rc = PrepareLadeArtikelnatra( error_msg ) ) < 0 ) return rc;

	return OK;
}
 
/***** LOAD-TABLES ***************************************************************/

int LoadTables(char *input, char *error_msg)
{
	int rc = OK;
	struct RABATTE *rab;
	rab = input;

	/* neue Tabellen schreiben */
	if(rab->RabattArt[0] == '2')
	{
		if ( (rc = LadeDiscountInfoBar(input, error_msg)) < 0) return rc;
	}
	else if(rab->RabattArt[0] == '3')
	{
		if ( (rc = LadeDiscountInfo(input, error_msg)) < 0) return rc;
	}
	else
	{
		if ( (rc = LadeArtikelnatra(input, error_msg)) < 0) return rc;
	}

	return OK;
}

/***** AFTER-LOAD-TABLES *********************************************************/

int AfterLoadTables( char *error_msg)
{
	int rc;
	if ( (rc = AfterLadeDiscountInfo(error_msg)) < 0) return rc;
	if ( (rc = AfterLadeDiscountInfoBar(error_msg)) < 0) return rc;
	if ( (rc = AfterLadeArtikelnatra(error_msg)) < 0) return rc;

	return OK;
}

/*** PREPARE-LADE-ARTIKELNATRA **************************************************/

int PrepareLadeArtikelnatra( char *error_msg )
{
	char *fun = "PrepareLadeArtikelnatra";
	int rc;
	
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;
	
	strcpy( str, "insert into artikelnatra (" );
	strcat( str, ARTIKELNATRA_PELISTE );          
	strcat( str, ",EINKAUFSGRUPPE " );
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )" );

	exec sql prepare ins_natra from :str;
	ERROR_MSG( "prepare ins_natra" )
	
	strcpy( str, "select " );
	strcat( str, NATRASTAFFELN_PELISTE );
	strcat( str, " from natrastaffeln" );
	strcat( str, " where NATRASTAFFELNR = ?" );

	exec sql prepare dec_natra from :str;
	ERROR_MSG( "prepare dec_natra" )
	exec sql declare Cselnatra cursor for dec_natra;
	
	strcpy( str, "select" );
	strcat( str, " natrastaffelnr" );
	strcat( str, " from artikellokal" );
	strcat( str, " where artikel_nr = ?" );
	strcat( str, " and filialnr = ?" );
	strcat( str, " for update " );

	exec sql prepare dec_artikellokal from :str;
	ERROR_MSG( "prepare dec_artikellokal" )
	exec sql declare Cupdartikellokal cursor for dec_artikellokal;

	strcpy( str, "update artikellokal " );
	strcat( str, "set natrastaffelnr = ? " );
	strcat( str, "where current of Cupdartikellokal" );

	exec sql prepare upd_lokal from :str;
	ERROR_MSG( "prepare upd_lokal" )

	return OK;   
}

/*** PREPARE-LADE-DISCOUNT-INFO **************************************************/

int PrepareLadeDiscountInfo( char *error_msg )
{
	char *fun = "PrepareLadeDiscountInfo";
	int rc;
	
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;
	
	strcpy( str, "insert into validdiscountinfo (" );
	strcat( str, VALIDDISCOUNT_PELISTE );          
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, 0, \" \",\" \", 0 )" );

	exec sql prepare ins_discount from :str;
	ERROR_MSG( "prepare ins_discount" )
	
	return OK;   
}

/*** PREPARE-LADE-DISCOUNT-INFO-BAR *********************************************/

int PrepareLadeDiscountInfoBar( char *error_msg )
{
	char *fun = "PrepareLadeDiscountInfoBar";
	int rc;
	
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;
	
	strcpy( str, "insert into validdiscountinfo (" );
	strcat( str, VALIDDISCOUNT_PELISTE );          
	strcat( str, " ) values " );
	strcat( str, "( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 0 )" );

	exec sql prepare ins_discountbar from :str;
	ERROR_MSG( "prepare ins_discountbar" )
	
	return OK;   
}

/*** LADE-ARTIKEL-NATRA *********************************************************/

int LadeArtikelnatra( char *input, char *error_msg )
{
	char *fun = "LadeArtikelnatra";
	char huelse[20];
	int i;
	int rc;
	
	exec sql begin declare section;
	struct RABATTE *a;
	int	 filiale;
	long staffelnr;
	struct C_NATRASTAFFELN natra;
	short RABATTSCHLUESSEL;
	char NRINTERN[2];
	exec sql end declare section;

	filiale = filialnr;
	a = input;

	if (first == 1)
	{
		first = 0;
		DelArtikelnatra( a, error_msg );
	}

	sprintf(huelse,"%s", a->StaffelNr );
	staffelnr = atol(huelse);
	if(staffelnr == 0) return OK;
	exec sql open Cselnatra using :staffelnr;
	ERROR_MSG( "open Cselnatra" )
    RABATTSCHLUESSEL = 1;
	if( a->RabattEigen[0] == 'J')
		NRINTERN[0] = '1';
	else
		NRINTERN[0] = '0';
	NRINTERN[1] = '\0';
	
	for ( ;; )
	{
		exec sql fetch Cselnatra into :natra;
		ERROR_MSG( "fetch Cselnatra" )
		if (NOTFOUND) break;
/*		printf("Artnr: %d\n",a->Artikelnr);fflush(stdout);
		printf("RABATTSCHLUESSEL: %d\n",RABATTSCHLUESSEL);fflush(stdout);
		printf("Von: %d\n",a->Von);fflush(stdout);
		printf("Bis: %d\n",a->Bis);fflush(stdout);
		printf("KONDGRUPPENNR: %d\n",natra.KONDGRUPPENNR);fflush(stdout);
		printf("NATRABASISMENGE: %d\n",natra.NATRABASISMENGE);fflush(stdout);
		printf("NATRAMENGE: %d\n",natra.NATRAMENGE);fflush(stdout);
		printf("filiale: %d\n",filiale);fflush(stdout);
		printf("NRINTERN: #%s#\n",NRINTERN);fflush(stdout);
		printf("EKGruppe: #%3.3s#\n",a->EKGruppe);fflush(stdout);
*/
		EXEC SQL EXECUTE ins_natra USING
			:a->Artikelnr,
			:RABATTSCHLUESSEL,
			:a->Von,
			:a->Bis,
			:natra.KONDGRUPPENNR,
			:natra.NATRABASISMENGE,
			:natra.NATRAMENGE,
			:filiale,
			:NRINTERN,
			:a->EKGruppe;
		if ( sqlca.sqlcode == -239 )
		{
			continue;
/*		printf("Artnr: %7.7s\n",a->Artikelnr);fflush(stdout);
		printf("RABATTSCHLUESSEL: %d\n",RABATTSCHLUESSEL);fflush(stdout);
		printf("Von: %8.8s\n",a->Von);fflush(stdout);
		printf("Bis: %8.8s\n",a->Bis);fflush(stdout);
		printf("KONDGRUPPENNR: %d\n",natra.KONDGRUPPENNR);fflush(stdout);
		printf("NATRABASISMENGE: %d\n",natra.NATRABASISMENGE);fflush(stdout);
		printf("NATRAMENGE: %d\n",natra.NATRAMENGE);fflush(stdout);
		printf("filiale: %d\n",filiale);fflush(stdout);
		printf("NRINTERN: #%s#\n",NRINTERN);fflush(stdout);
		printf("EKGruppe: #%3.3s#\n",a->EKGruppe);fflush(stdout);
*/		}
		ERROR_MSG( "insert artikelnatra" )
	}
	exec sql open Cupdartikellokal using :a->Artikelnr,:filiale;
	ERROR_MSG( "open Cupdartikellokal" )
	exec sql fetch Cupdartikellokal into :staffelnr;
	ERROR_MSG( "fetch Cupdartikellokal" )
	if (!(NOTFOUND))
	{
		if ( staffelnr == 0)
			EXEC SQL EXECUTE upd_lokal USING :a->Artikelnr;
	}

	return OK;
}

/*** LADE-DISCOUNT-INFO *********************************************************/

int LadeDiscountInfo( char *input, char *error_msg )
{
	char *fun = "LadeDiscountInfo";
	char huelse[20];
	int i;
	int rc;
	
	exec sql begin declare section;
	struct RABATTE *a;
	int	 filiale;
	long staffelnr;
	struct C_NATRASTAFFELN natra;
	exec sql end declare section;

	filiale = filialnr;
	a = input;

	if (first == 1)
	{
		first = 0;
		DelDiscountInfo( a, error_msg );
	}

	EXEC SQL EXECUTE ins_discount USING
			:filiale,
			:a->Artikelnr,
			:a->EKGruppe,
			:a->Von,
			:a->Bis,
			:a->RabattArt,
			:a->StaffelNr;

	if ( sqlca.sqlcode == -239 )
	{
		sprintf(error_msg,"PZN: %7.7s EKGruppe: %3.3s",a->Artikelnr,a->EKGruppe);
		PrintMsg( fun, error_msg, FEHL, -1 );
		return OK;
	}

	ERROR_MSG( "insert validdiscountinfo" )

	return OK;
}

/*** LADE-DISCOUNT-INFO-BAR *********************************************************/

int LadeDiscountInfoBar( char *input, char *error_msg )
{
	char *fun = "LadeDiscountInfoBar";
	char huelse[20];
	int i;
	int rc;
	
	exec sql begin declare section;
	struct BARRABATTE *a;
	int	 filiale;
	long staffelnr;
	exec sql end declare section;

	filiale = filialnr;
	a = input;

	if (first == 1)
	{
		first = 0;
		DelDiscountInfo( a, error_msg );
	}
/*	printf("inout: %s\n",input);fflush(stdout);
	printf("filiale: %d\n",filiale);fflush(stdout);
	printf("Artikelnr: %7.7s\n",a->Artikelnr);fflush(stdout);
	printf("EKGruppe: %3.3s\n",a->EKGruppe);fflush(stdout);
	printf("Von: %8.8s\n",a->Von);fflush(stdout);
	printf("Bis: %8.8s\n",a->Bis);fflush(stdout);
	printf("RabattArt: %1.1s\n",a->RabattArt);fflush(stdout);
	printf("StaffelNr1: %3.3s\n",a->StaffelNr1);fflush(stdout);
	printf("StaffelWert1: %7.7s\n",a->StaffelWert1);fflush(stdout);
	printf("RabattTyp: %2.2s\n",a->RabattTyp);fflush(stdout);
	printf("RabattForm: %2.2s\n",a->RabattForm);fflush(stdout);
*/
	if( strncmp(a->StaffelNr1,"000",3) )
	{
		EXEC SQL EXECUTE ins_discountbar USING
			:filiale,
			:a->Artikelnr,
			:a->EKGruppe,
			:a->Von,
			:a->Bis,
			:a->RabattArt,
			:a->StaffelNr1,
			:a->StaffelWert1,
			:a->RabattTyp,
			:a->RabattForm;

		if ( sqlca.sqlcode == -239 )
		{
			sprintf(error_msg,"PZN: %7.7s EKGruppe: %3.3s",a->Artikelnr,a->EKGruppe);
			PrintMsg( fun, error_msg, FEHL, -1 );
		}
		else
		{
			ERROR_MSG( "insert validdiscountinfobar1" )
		}
	}

	if( strncmp(a->StaffelNr2,"000",3) )
	{
		EXEC SQL EXECUTE ins_discountbar USING
			:filiale,
			:a->Artikelnr,
			:a->EKGruppe,
			:a->Von,
			:a->Bis,
			:a->RabattArt,
			:a->StaffelNr2,
			:a->StaffelWert2,
			:a->RabattTyp,
			:a->RabattForm;

		if ( sqlca.sqlcode == -239 )
		{
			sprintf(error_msg,"PZN: %7.7s EKGruppe: %3.3s",a->Artikelnr,a->EKGruppe);
			PrintMsg( fun, error_msg, FEHL, -1 );
		}
		else
		{
			ERROR_MSG( "insert validdiscountinfobar2" )
		}
	}

	if( strncmp(a->StaffelNr3,"000",3) )
	{
		EXEC SQL EXECUTE ins_discountbar USING
			:filiale,
			:a->Artikelnr,
			:a->EKGruppe,
			:a->Von,
			:a->Bis,
			:a->RabattArt,
			:a->StaffelNr3,
			:a->StaffelWert3,
			:a->RabattTyp,
			:a->RabattForm;

		if ( sqlca.sqlcode == -239 )
		{
			sprintf(error_msg,"PZN: %7.7s EKGruppe: %3.3s",a->Artikelnr,a->EKGruppe);
			PrintMsg( fun, error_msg, FEHL, -1 );
	}
		else
		{
			ERROR_MSG( "insert validdiscountinfobar3" )
		}
	}

	if( strncmp(a->StaffelNr4,"000",3) )
	{
		EXEC SQL EXECUTE ins_discountbar USING
			:filiale,
			:a->Artikelnr,
			:a->EKGruppe,
			:a->Von,
			:a->Bis,
			:a->RabattArt,
			:a->StaffelNr4,
			:a->StaffelWert4,
			:a->RabattTyp,
			:a->RabattForm;

		if ( sqlca.sqlcode == -239 )
		{
			sprintf(error_msg,"PZN: %7.7s EKGruppe: %3.3s",a->Artikelnr,a->EKGruppe);
			PrintMsg( fun, error_msg, FEHL, -1 );
		}
		else
		{
			ERROR_MSG( "insert validdiscountinfobar4" )
		}
	}

	if( strncmp(a->StaffelNr5,"000",3) )
	{
		EXEC SQL EXECUTE ins_discountbar USING
			:filiale,
			:a->Artikelnr,
			:a->EKGruppe,
			:a->Von,
			:a->Bis,
			:a->RabattArt,
			:a->StaffelNr5,
			:a->StaffelWert5,
			:a->RabattTyp,
			:a->RabattForm;

		if ( sqlca.sqlcode == -239 )
		{
			sprintf(error_msg,"PZN: %7.7s EKGruppe: %3.3s",a->Artikelnr,a->EKGruppe);
			PrintMsg( fun, error_msg, FEHL, -1 );
		}
		else
		{
			ERROR_MSG( "insert validdiscountinfobar5" )
		}
	}

	if( strncmp(a->StaffelNr6,"000",3) )
	{
		EXEC SQL EXECUTE ins_discountbar USING
			:filiale,
			:a->Artikelnr,
			:a->EKGruppe,
			:a->Von,
			:a->Bis,
			:a->RabattArt,
			:a->StaffelNr6,
			:a->StaffelWert6,
			:a->RabattTyp,
			:a->RabattForm;

		if ( sqlca.sqlcode == -239 )
		{
			sprintf(error_msg,"PZN: %7.7s EKGruppe: %3.3s",a->Artikelnr,a->EKGruppe);
			PrintMsg( fun, error_msg, FEHL, -1 );
		}
		else
		{
			ERROR_MSG( "insert validdiscountinfobar6" )
		}
	}

	return OK;
}

/***** AFTER-LADE-ARTIKEL-NATRA *********************************************/

int AfterLadeArtikelnatra( char *error_msg )
{
//	char *fun = "AfterLadeArtikelLokal";

	return OK;
}

/***** AFTER-LADE-DISCOUNT-INFO *********************************************/

int AfterLadeDiscountInfo( char *error_msg )
{
//	char *fun = "AfterLadeDiscountInfo";

	return OK;
}

/***** AFTER-LADE-DISCOUNT-INFO *********************************************/

int AfterLadeDiscountInfoBar( char *error_msg )
{
//	char *fun = "AfterLadeDiscountInfoBar";

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
	char logFile[L_TEXT];
    char *env;
		
	if ( rc > INSERT )
		return;
   
	pid = getpid();
	hour1 = time( &hour1 );
	zeit  = localtime( &hour1 );
   
/*	sprintf( logFile, "%s/wws.log", (char *)getenv( "LOG_PATH" ) ); */
	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	sprintf( logFile, "%s/wws.log", env );

	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;
   
	fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %s %s %s\n",
		mld,
		filialnr,
		zeit->tm_mday,
		zeit->tm_mon + 1,
		(zeit->tm_year+1900)%100,
		zeit->tm_hour,
		zeit->tm_min,
		zeit->tm_sec,
		pid,
		"tpldchrab",
		fun,
		error_msg );

	fclose(fp);
}

/***** CLOSE-DATABASE *******************************************************/

int CloseDatabase( void )
{
	char error_msg[L_TEXT];
	char *fun = "CloseDatabase";

	exec sql close database;
	ERROR_MSG( "Close DB" )
  
	return OK;
}

/*** DELETE-ARTIKELNATRA **************************************************/

int DelArtikelnatra( char *input, char *error_msg )
{
	char *fun = "DelArtikelnatra";
	int rc;
	
	exec sql begin declare section;
	char str[2048];
	struct RABATTE *a;
	int	 filiale;
	exec sql end declare section;
	
	filiale = filialnr;
	a = input;

	strcpy( str, "select " );
	strcat( str, ARTIKELNATRA_PELISTE );
	strcat( str, " from artikelnatra" );
	strcat( str, " where VERTRIEBSZENTRUMNR = ?" );
	strcat( str, " and EINKAUFSGRUPPE != ' '" );
	strcat( str, " for update " );

	exec sql prepare sel_artikelnatra from :str;
	ERROR_MSG( "prepare sel_artikelnatra" )
	exec sql declare CDelartikelnatra cursor for sel_artikelnatra;

	strcpy( str, "delete from artikelnatra " );
	strcat( str, "where current of CDelartikelnatra" );

	exec sql prepare delete_natra from :str;
	ERROR_MSG( "prepare delete_natra" )

	exec sql open CDelartikelnatra using :filiale;
	ERROR_MSG( "open CDelartikelnatra" )
	
	for ( ;; )
    {
	    exec sql fetch CDelartikelnatra;
	    ERROR_MSG( "fetch CDelartikelnatra" )

		if ( sqlca.sqlcode == 0 )
		{
			EXEC SQL EXECUTE delete_natra;
			ERROR_MSG( "execute delete_natra" ) 
		}
	    if ( sqlca.sqlcode == 100 ) break;
	}

	return OK;   
}

/*** DELETE-DISCOUNT-INFO **************************************************/

int DelDiscountInfo( char *input, char *error_msg )
{
	char *fun = "DelDiscountInfo";
	int rc;
	
	exec sql begin declare section;
	char str[2048];
	struct RABATTE *a;
	int	 filiale;
	exec sql end declare section;
	
	filiale = filialnr;
	a = input;

	strcpy( str, "select " );
	strcat( str, VALIDDISCOUNT_PELISTE );
	strcat( str, " from validdiscountinfo" );
	strcat( str, " where BRANCHNO = ?" );
	strcat( str, " and TYPEOFDISCOUNT = ?" );
	strcat( str, " for update " );

	exec sql prepare sel_discount from :str;
	ERROR_MSG( "prepare sel_discount" )
	exec sql declare CDeldiscount cursor for sel_discount;

	strcpy( str, "delete from validdiscountinfo " );
	strcat( str, "where current of CDeldiscount" );

	exec sql prepare delete_discount from :str;
	ERROR_MSG( "prepare delete_discount" )

	exec sql open CDeldiscount using :filiale,:a->RabattArt;
	ERROR_MSG( "open CDeldiscount" )
	
	for ( ;; )
    {
	    exec sql fetch CDeldiscount;
	    ERROR_MSG( "fetch CDeldiscount" )

		if ( sqlca.sqlcode == 0 )
		{
			EXEC SQL EXECUTE delete_discount;
			ERROR_MSG( "execute delete_discount" ) 
		}
	    if ( sqlca.sqlcode == 100 ) break;
	}

	return OK;   
}

/***** ENDE *****************************************************************/

