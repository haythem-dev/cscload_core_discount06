#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME "tplddkkui"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "libtpld/struct.h"
#include "libtpld/coboltoasci.h"
#include "libtpld/define.h"
#include "customerspecials.h"
#include "dkkui_neu.h"

exec sql include sqlca;

#undef NULL  

#define INSERT             1
/* #define NOT_FOUND          1 */
#define FILE_NOT_FOUND     1
#define HINW             'H'
#define FEHL             'F'
#define RIO_EOF          110
#define RIO_NOFIND       111
#define VB				 "VB"
#define BLANC            ' '
#define BLANK            "         "
#define NULLEN           "000000000"
#define ERROR_MSG2(x)       if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
                               return -1; }
#define ERROR_MSG3(x,y)     if ( sqlca.sqlcode < 0 ) { \
                               sprintf( error_msg, "%s %d/%d %s %s %7.7s",\
								x,\
                                sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm,\
								"IDF:",\
								 y ); \
                               PrintMsg( fun, error_msg, FEHL, -1 ); \
							if ( sqlca.sqlcode == -1213 ) return 0; \
							if ( sqlca.sqlcode == -1226 ) return 0; \
                               return -1; }


/*** DECLARATION * EXETRN *************************************************************/

//extern int  WandelAsci( char *, char *, struct AUFB [], int );

/***** GLOBALE **************************************************************/
 
#define DATABASE "phosix"

exec sql begin declare section;
	char str[2048];
	char datenbank[60];
exec sql end declare section;
 
FILE *dkkuidat;
char  dateiname[1000];

 char log_file [400 + 1];
 int debug_enabled  = NO;
 int explain = NO;
 int load_all 		= NO;
 int Schweiz = NO;
 int Bulgarien = NO;
 int Frankreich = NO;
 int Kroatien = NO;
 int Austria = NO;
 int Serbia = NO;
 int iHaus = 99;

 /***** DECLARATION **********************************************************/
 
 int main( int, char ** );
 void PrintMsg( char *fun, char *error_msg, char mld, int rc );
 void WriteLogInfo( char *error_msg, char mld, int rc );
 int StarteLadenderKundeRelationen( char *error_msg);

 int PrepareLoadTables(char *error_msg);
 int LoadTables(struct S_DKKUI *kun, char *error_msg);
 int AfterLoadTables(char *error_msg);

 int PrepareLoadKunde( char *error_msg);
 int LadeKunde(struct S_DKKUI *, char *);
 int AfterLoadKunde( char *error_msg);
 int PrepareLoadKundeSchalter( char *error_msg);
 int LadeKundeSchalter(struct S_DKKUI *, char *);
 int AfterLoadKundeSchalter( char *error_msg);
 int PrepareLoadCustomerSpecials( char *error_msg);
 int LadeCustomerSpecials(struct S_DKKUI *, char *);
 int AfterLoadCustomerSpecials( char *error_msg);

/***** MAIN *****************************************************************/

int main( int argc, char **argv  )
{
	char error_msg[81];
	char *fun = "Main";
	char	*LOG_FILE = "tplddkkui.log";
	char	*LOG_PATH;
	char	logpath[256+1];
	char *schalter;
	int 	i;

	setbuf( stdout, 0 );              /* printf sofort */

	sprintf(datenbank,"%s",DATABASE);

	for ( i = 1; i < argc; i++ )
	{
		schalter = argv[i];
		if ( !strcmp( schalter, "-dg" ) )
		{
			debug_enabled = YES;
		}
		else if ( !strcmp( schalter, "-db" ) )
		{
			i++;
			sprintf( datenbank, "%s", argv[i] );
		}
		else if ( !strcmp( schalter, "-ch" ) )
			Schweiz = YES;
		else if ( !strcmp( schalter, "-g" ) )
			Schweiz = NO;
		else if ( !strcmp( schalter, "-bg" ) )
			Bulgarien = YES;
		else if ( !strcmp( schalter, "-hr" ) )
			Kroatien = YES;
		else if ( !strcmp( schalter, "-fr" ) )
			Frankreich = YES;
		else if ( !strcmp( schalter, "-au" ) )
			Austria = YES;
		else if ( !strcmp( schalter, "-rs" ) )
			Serbia = YES;
		else if ( !strcmp( schalter, "-lf" ) )
		{
			i++;
			iHaus = atoi(argv[i]);
		}
		else if ( !strcmp( schalter, "-version" ) )
		{
			printVersion(versioninfo);
			return OK;
		}
		else
		{
			printf( "  usage: %s\n\t"
				" { -dg <Debugging> }\n\t"
				" [ -db <Datenbank>\n\t", argv[0] );
			exit ( 2 );
		}
	}                                            

	DEBUG_SECTION
	setbuf( stderr, 0 );
	END_DEBUG_SECTION

	if ((LOG_PATH = getenv("LOG_PATH")) == (char *)0)
	{
		strcpy(logpath, ".");
	}
	else
	{
		strcpy(logpath, LOG_PATH);
	}
	sprintf(log_file, "%s/%s", logpath, LOG_FILE);
	
	if (StarteLadenderKundeRelationen(error_msg) != 0)
	{
		return 1;
	}
	PrintMsg( fun, "Ende", HINW, 0 );

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

   
   DEBUG_PRINT( fun, error_msg, SQLCODE, rc )
   
   if ( rc > INSERT )
      return;

   pid = getpid();
   hour1 = time( &hour1 );
   zeit  = localtime( &hour1 );
   fp = fopen( log_file, "a" );
   fprintf( fp, "%c %.2d %02d.%02d.%02d %02d:%02d:%02d pid=%05ld %.9s %s",
	    mld,
	    iHaus,
	    zeit->tm_mday,
        zeit->tm_mon + 1,
        (zeit->tm_year+1900)%100,
        zeit->tm_hour,
        zeit->tm_min,
        zeit->tm_sec,
	    pid,
	    "tplddkkui",
	    fun );

   fprintf(fp,"%s\n", error_msg );
   fclose(fp);
}

/***** STARTE DAS LADEN DER Kunde-TABELLEN **************************************/

int StarteLadenderKundeRelationen( char *error_msg )
{
	int zaehler, rc;
	char *fun = "StarteLadenderKundeRelationen";
	char *XVSAM;
	char datpath[256+1];
	char huelse[20];
 	struct AUFB aufb[] = { DKKUI_SATZ }; 
	char satz[2000];
    int len = 750;	/* dkkui = 750!!!!!! */
	
	exec sql begin declare section;
	struct S_DKKUI  kunlang;
	struct S_DKKUI  *kun;
	short int filialnr;
	exec sql end declare section;

    kun = &kunlang;
   	
   	exec sql database :datenbank;
   	if (SQLCODE != 0)  /* Datenbankfehler */
    {
      	ERROR_MSG2( "database:" )
 	  	PrintMsg( fun, error_msg, FEHL, ERROR );
      	return ERROR;
    }
   	exec sql set lock mode to wait 20;
   	if (sqlca.sqlcode != 0)  /* Datenbankfehler */
    {
      	ERROR_MSG2( "Lock Mode:" )
 	  	PrintMsg( fun, error_msg, FEHL, ERROR );
		return ERROR;
    }
   	exec sql set isolation to dirty read;
   	if ((SQLCODE != 0) && (SQLCODE != -256))  /* Datenbankfehler */
    {
      	ERROR_MSG2( "Set Isolation:" )
 	  	PrintMsg( fun, error_msg, FEHL, -1 );
      	return ERROR;
    }
	
	PrintMsg( "Main", "Start", HINW, 0 );

	if( (rc = PrepareLoadTables(error_msg)) != 0 )
	{
		return rc;	
	}
	if ((XVSAM = getenv("XVSAM")) == (char *)0)
	{
		strcpy(datpath, ".");
	}
	else
	{
		strcpy(datpath, XVSAM);
	}

	sprintf( dateiname, "%s/UCATPH4/DKKUI.P.dat", datpath );
	if ( ( dkkuidat = fopen( dateiname, "r" ) ) == (FILE *)0 )
	{
		PrintMsg( "tplddkkui ", dateiname, FEHL, 0 );
		PrintMsg( "tplddkkui ", "DKKUI nicht vorhanden", FEHL, 0 );
		return -1;
	}
	PrintMsg(fun, dateiname, HINW, 0);
    
    exec sql begin work;
    if (SQLCODE < 0 )
    {
    	ERROR_MSG2( "begin Work:" )
 	  	PrintMsg( fun, error_msg, FEHL, ERROR );
       	return ERROR;
    }

	for(zaehler=0 ;;zaehler++ )
	{
		if (zaehler%50 == 0)
		{
			exec sql commit work;
            if (SQLCODE < 0 )
    		{
    			ERROR_MSG2( "Commit Work:" )
 	  			PrintMsg( fun, error_msg, FEHL, -1 );
       			return -1;
    		}
			exec sql begin work;
			if (SQLCODE < 0 )
			{
				ERROR_MSG2( "begin Work:" )
				PrintMsg( fun, error_msg, FEHL, ERROR );
				return -1;
			}
		}
		
		if (zaehler%50 == 0)
		{
			DEBUG_SECTION
			sprintf(error_msg," %d Saetze geladen",zaehler);
			PrintMsg( fun, error_msg, HINW, -1 );
			END_DEBUG_SECTION
		}
		
		if(fread( satz ,len, 1 , dkkuidat ) == 0)
			break;

		// reset kunde struct
		memset( (char *)kun, BLANC, sizeof( struct S_DKKUI ) );
		// transfer row from file into kunde struct
		int len = WandelAsci( (char *)kun, satz, aufb, sizeof(aufb)/sizeof(struct AUFB) );
		if (len != sizeof(struct S_DKKUI))
		{
			// definition between struct and count of AUFB is not equal to struct S_DKKUI
			sprintf(error_msg, "size of kun: %d, size of satz: %d, size of aufb: %d, count of aufb: %d, size fo WandelAsci: %d", sizeof(struct S_DKKUI), sizeof(satz), sizeof(aufb), sizeof(aufb) / sizeof(struct AUFB), len);
			PrintMsg(fun, error_msg, FEHL, 0);
			PrintMsg(fun, "parsing rows from file into DKKUI struct fails, verify the definitions (WandelAsci size != kun size)", FEHL, 0);
			return -1;
		}

		if (zaehler == 0)
		{
			if(iHaus == 99)
			{
				sprintf(huelse,"%*.*s",L_DKKUI_KUIFIL,L_DKKUI_KUIFIL,kun->KUIFIL);
				iHaus = atoi(huelse);
			}
		}
		sprintf(huelse,"%*.*s",L_DKKUI_KUIFIL,L_DKKUI_KUIFIL,kun->KUIFIL);
		if(	iHaus == atoi(huelse) )
		{
			if( (rc = LoadTables(kun, error_msg)) != 0 )
			{
				return rc;	
			}	
		}
		else if(iHaus == 49 && atoi(huelse) == 48 )
		{
			strncpy(kun->KUIFIL,"49",L_DKKUI_KUIFIL);
			if( (rc = LoadTables(kun, error_msg)) != 0 )
			{
				return rc;	
			}	
		}
	}

	EXEC SQL commit work;
	if (sqlca.sqlcode < 0 )
	{
		sprintf(error_msg, "commit work2 %ld", sqlca.sqlcode);
		PrintMsg( fun, error_msg, FEHL, -1 );
		return -1;
	}
	
	fclose( dkkuidat);
	sprintf(error_msg," %d Saetze geladen",zaehler);
	PrintMsg( fun, error_msg, HINW, -1 );
	
	if( (rc = AfterLoadTables(error_msg)) != 0 )
	{
		return rc;	
	}
	return OK;
}


int PrepareLoadTables(char *error_msg)
{
	int rc;
	if ( (rc = PrepareLoadKunde( error_msg)) < 0) return rc;
	if ( (rc = PrepareLoadKundeSchalter( error_msg)) < 0) return rc;
	if ( (rc = PrepareLoadCustomerSpecials( error_msg)) < 0) return rc;
	return 0;
}

int LoadTables(struct S_DKKUI *kun, char *error_msg)
{
	int rc;
	if ( (rc = LadeKunde(kun, error_msg)) < 0) return rc;
	if ( (rc = LadeKundeSchalter(kun, error_msg)) < 0) return rc;
	if ( (rc = LadeCustomerSpecials(kun, error_msg)) < 0) return rc;
	return 0;
}

int AfterLoadTables(char *error_msg)
{
	int rc;
	int rcode = 0;
	if ( (rc = AfterLoadKunde( error_msg)) < 0) rcode = rc;
	if ( (rc = AfterLoadKundeSchalter( error_msg)) < 0) rcode = rc;
	if ( (rc = AfterLoadCustomerSpecials( error_msg)) < 0) rcode = rc;
	return rcode;
}

int PrepareLoadKunde( char *error_msg)
{
	char *fun = "PrepareLoadKunde";
	int rc;

	strcpy(str,"update kunde set ");
	strcat(str,"emailadresse = ?, ");
	strcat(str,"xmlpreislevel = ?, ");
	strcat(str,"xmlinfolevel = ?, ");
	strcat(str,"ratiocustomerno = ?, ");
	strcat(str,"nationalcustomerno = ?, ");
	strcat(str,"kundeean = ? ");
	strcat(str,"where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ? ");
	strcat(str,"and ");
	strcat(str,"KUNDENNR = ?");

	EXEC SQL PREPARE upd_kunde FROM :str;
	ERROR_MSG2( "prepare upd_kunde" )

	return OK;
}

int PrepareLoadKundeSchalter( char *error_msg)
{
	char *fun = "PrepareLoadKundeSchalter";
	int rc;

	strcpy(str,"update kundeschalter set ");
	strcat(str,"skdmidas = ?, ");
	strcat(str,"skdcharge = ?, ");
	strcat(str,"skdversandapo = ?, ");
	strcat(str,"skdretailpermit = ?, ");
	strcat(str,"skdtournee = ?, ");
	strcat(str,"skdrxa = ?");
	strcat(str,"where ");
	strcat(str,"VERTRIEBSZENTRUMNR = ? ");          
	strcat(str,"and ");          
	strcat(str,"KUNDENNR = ?");          

	EXEC SQL PREPARE upd_kundeschalter FROM :str;
	ERROR_MSG2( "prepare upd_kundeschalter" )

	return OK;
}

int PrepareLoadCustomerSpecials( char *error_msg)
{
	char *fun = "PrepareLoadCustomerSpecials";
	int rc;

	strcpy(str,"insert into customerspecials (");
	strcat(str,CUSTOMERSPECIALS_PELISTE);          
	strcat(str,") values ");          
	strcat(str,"( ?, ?, ?, ?, ?, ? )");          

	EXEC SQL PREPARE ins_special FROM :str;
	ERROR_MSG2( "prepare ins_special" )

	strcpy(str,"select customerno from customerspecials ");
	strcat(str," where branchno = ?" );
	strcat(str," and customerno = ?");
	strcat(str," for update");

	EXEC SQL PREPARE sel_special FROM :str;
	ERROR_MSG2( "prepare sel_special" )
	exec sql declare DelSpecial Cursor with hold for sel_special;
	 
	strcpy( str, "delete from customerspecials " );
	strcat( str, "where current of DelSpecial " );
	
	exec sql prepare del_special from :str;
	ERROR_MSG2( "prepare del_special" )

	return OK;
}

int LadeKunde( struct S_DKKUI *kun, char *error_msg)
{
	char *fun = "LadeKunde";
	char huelse[20];

	exec sql begin declare section;
	struct S_DKKUI *d;
	char KUIBIDF[13];
	char KUIEAN[14];
	long bidf;
	long lPartner;
	long ean;
	exec sql end declare section;

	d = kun;

	sprintf(huelse,"%*.*s",LS_DKKUI_KUIBIDF,LS_DKKUI_KUIBIDF,d->KUIBIDF);    
	bidf = atol(huelse);
	sprintf(KUIBIDF,"%07d",bidf);
	sprintf(huelse,"%*.*s",LS_DKKUI_KUIEAN,LS_DKKUI_KUIEAN,d->KUIEAN);    
	ean = atol(huelse);
	if(ean < 0) ean = ean * (-1);
	sprintf(KUIEAN,"%13ld",ean);

	if(d->KUIEMAIL[0] != ' ')	/*weils die in Pharmos nciht fertig bringen @ einzugeben */
	{
		for(int i = 0;i < strlen(d->KUIEMAIL);i++)
		{
			if(d->KUIEMAIL[i] == '@') break;	/* bereits korrekt versorgt */
			if(d->KUIEMAIL[i] == ' ')
			{
				d->KUIEMAIL[i] = '@';
				break;
			}
		}
	}
	DEBUG_SECTION
	    printf("#%*.*s#\n",L_DKKUI_KUIFIL,L_DKKUI_KUIFIL,d->KUIFIL);
	    printf("#%*.*s#\n",L_DKKUI_KUIIDF,L_DKKUI_KUIIDF,d->KUIIDF);
	    printf("#%*.*s#\n",L_DKKUI_KUIEMAIL,L_DKKUI_KUIEMAIL,d->KUIEMAIL);
	    printf("#%*.*s#\n",L_DKKUI_KUISPEDI,L_DKKUI_KUISPEDI,d->KUISPEDI);
	END_DEBUG_SECTION

	if(Bulgarien == YES)
	{
		EXEC SQL EXECUTE upd_kunde USING :d->KUIEMAIL,
	                                 :d->KUIKUKO,
	                                 :d->KUIANXML,
	                                 :d->KUISPEDI,
	                                 :KUIBIDF,
	                                 :KUIEAN,
	                                 :d->KUIFIL,
									 :d->KUIIDF;
		ERROR_MSG3( "upd kunde:",d->KUIIDF )
	}
	else
	{
		EXEC SQL EXECUTE upd_kunde USING :d->KUIEMAIL,
	                                 :d->KUIKUKO,
	                                 :d->KUIANXML,
	                                 :d->KUISPEDI,
	                                 :KUIBIDF,
	                                 :KUIEAN,
	                                 :d->KUIFIL,
									 :d->KUIIDF;
		ERROR_MSG3( "upd kunde:",d->KUIIDF )
	}
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		sprintf( error_msg, "IDF-Nummer: %7.7s fehlt",d->KUIIDF );
	/*		PrintMsg( fun, error_msg, HINW, -1 );	*/
	}
	return OK;
}


int LadeKundeSchalter( struct S_DKKUI *kun, char *error_msg)
{
	char *fun = "LadeKundeSchalter";
	char huelse[8];

	exec sql begin declare section;
	struct S_DKKUI *d;
	char   SKDMIDAS[1 + 1];
	char   SKDCHARGE[1 + 1];
	char   KUIVSAPO[1 + 1];
	char   SKDRETAILPERMIT[1 + 1];
	exec sql end declare section;

	d = kun;

	if(Bulgarien == YES)
	{
		if(d->KUIMEVI[0] == 'J' || d->KUIMEVI[0] == '1')   strcpy(SKDRETAILPERMIT,"1");
		else strcpy(SKDRETAILPERMIT,"0");
		strcpy(SKDMIDAS,"0");
	}
	else
	{
		if(d->KUIMEVI[0] == 'J' || d->KUIMEVI[0] == '1')   strcpy(SKDMIDAS,"1");
		else strcpy(SKDMIDAS,"0");
		strcpy(SKDRETAILPERMIT,"0");
	}
	if(d->KUICHARGE[0] == 'J' || d->KUICHARGE[0] == '1')   strcpy(SKDCHARGE,"1");
	else strcpy(SKDCHARGE,"0");
	if(d->KUIVSAPO[0] == 'J' || d->KUIVSAPO[0] == '1')   strcpy(KUIVSAPO,"1");
	else strcpy(KUIVSAPO,"0");

	DEBUG_SECTION
	    printf("#%*.*s#\n",L_DKKUI_KUIFIL,L_DKKUI_KUIFIL,d->KUIFIL);
	    printf("#%*.*s#\n",L_DKKUI_KUIIDF,L_DKKUI_KUIIDF,d->KUIIDF);
	    printf("#%s#\n",SKDMIDAS);
	    printf("#%s#\n",SKDCHARGE);
	    printf("#%s#\n",KUIVSAPO);
	END_DEBUG_SECTION

	EXEC SQL EXECUTE upd_kundeschalter USING :SKDMIDAS,
	                                 :SKDCHARGE,
	                                 :KUIVSAPO,
									 :SKDRETAILPERMIT,
									 :d->KUITOUR,
									 :d->KUIRXA,
	                                 :d->KUIFIL,
									 :d->KUIIDF;
	ERROR_MSG3( "upd kundeschalter:",d->KUIIDF )
	if (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0 )  /* NotFound */
	{
		sprintf( error_msg, "IDF-Nummer: %7.7s fehlt",d->KUIIDF );
	}
	return OK;
}

int LadeCustomerSpecials( struct S_DKKUI *kun, char *error_msg)
{
	char *fun = "LadeCustomerSpecials";
	char huelse[8];

	exec sql begin declare section;
	struct	S_DKKUI *d;
	short	sWeekDay;
	char	cActiv[2];
    exec sql end declare section;

	d = kun;

	EXEC SQL open DelSpecial using	:d->KUIFIL,
									:d->KUIIDF;
	ERROR_MSG3( "open DelSpecial:",d->KUIIDF )

	for(;;)
	{
		EXEC SQL fetch DelSpecial;
		if ( sqlca.sqlcode == 100 ) break;
		ERROR_MSG2( "fetch DelSpecial" )
		EXEC SQL EXECUTE del_special;
		ERROR_MSG2( "del_special" )
	}

	sprintf(huelse,"%*.*s",L_DKKUI_KUIUWIDF,L_DKKUI_KUIUWIDF,kun->KUIUWIDF);
	if((!strncmp(d->KUIUWTOUR,BLANK,L_DKKUI_KUIUWTOUR) ||
		!strncmp(d->KUIUWTOUR,NULLEN,L_DKKUI_KUIUWTOUR)) &&
		atol(huelse) == 0)
	{
		return OK;
	}

	for(sWeekDay = 0;sWeekDay < 7;sWeekDay++)
	{
		if(sWeekDay == 0)
		{
			cActiv[0] = '0';
		}
		else if(d->KUIUWTAG[sWeekDay-1] == 'J')
		{
			cActiv[0] = '1';
		}
		else
		{
			cActiv[0] = '0';
		}
		cActiv[1] = '\0';
		EXEC SQL EXECUTE ins_special using
				:d->KUIFIL,
				:d->KUIIDF,
				:d->KUIUWIDF,
				:d->KUIUWTOUR,
				:sWeekDay,
				:cActiv
			;
		ERROR_MSG2( "ins_special" )
	}
}

int AfterLoadKunde( char *error_msg)
{
	char *fun = "AfterLoadKunde";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	return OK;
}

int AfterLoadKundeSchalter( char *error_msg)
{
	char *fun = "AfterLoadKundeSchalter";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	return OK;
}

int AfterLoadCustomerSpecials( char *error_msg)
{
	char *fun = "AfterLoadCustomerSpecials";
	int rc = 0;
	sprintf(error_msg,"%s%d",fun,rc);	/* damit kompiler nicht motzt */
	return OK;
}
