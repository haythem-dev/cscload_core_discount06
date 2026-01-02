/*************************************************************************/
/*						                                                 */
/*	Quelle  : tpldartindex.cxx                                           */
/*	Autor   : Ronald Imschweiler                                         */
/*	erstellt: 22.01.08                                                   */
/*	Aufgabe	: Erstellen artikelindex aus artikelzentral                  */
/*						                                                 */
/*************************************************************************/

/*** VERSION *************************************************************/

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tpldartindex"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/*********************************************************************************************************************/
/* INCLUDES                                                                                                          */
/*********************************************************************************************************************/
#include <stdio.h>                                                           
#include <stdlib.h>
#include <string.h>

/*********************************************************************************************************************/
/* DEFINES                                                                                                           */ 
/*********************************************************************************************************************/
#define NOTFOUND			sqlca.sqlcode == SQLNOTFOUND
#define OK                  0
#define SQLCODE				sqlca.sqlcode
#define M_DURCHLAUF_COMMIT	140                  /* nach n-saetzen commit  */
#define MAX_CH_ARTIKELNAME	26
#define MAX_CH_ARTIKELLANGNAME	50

/*********************************************************************************************************************/
/* GLOBALS                                                                                                           */ 
/*********************************************************************************************************************/
int swBulgaria = 0;
int iCountDel = 0;
int iCountIns = 0;

/*********************************************************************************************************************/
/* FUNKTIONS-DEKLARATIONEN                                                                                           */
/*********************************************************************************************************************/
int PrepareLadeArtikelIndex();
int LadeArtikelIndex( long, char *);
static int err(char *fun) ;

/*********************************************************************************************************************/
/*********************************************************************************************************************/
exec sql include sqlca;                                                                             
   
/*********************************************************************************************************************/
/* main( int argc,char **argv )                                                                                      */
/*********************************************************************************************************************/
int main( int argc, char **argv )
{
	int zaehler = 0;
	char *argm;
	int  i;

	exec sql begin declare section;                                              
	char Anfang[80];
	char Ende[80];
	char bezeichnung[51];              
	char datenbank[60];
	long artikel_nr;                          
	char str[2048];
	exec sql end declare section;

	for ( i = 1; i < argc; i++ )
	{
		argm = argv[i];
		if ( !strcmp( argm, "-db" ) )
		{
			i++;
			sprintf( datenbank, "%s", argv[i] );
		}
		else if ( !strcmp( argm, "-bg" ) )
		{
			swBulgaria = 1;
		}
		else if ( !strcmp( argm, "-version" ) )
		{
			printVersion(versioninfo);
			return 0;
		}
		else
		{
			break;
		}
	}                                            

	strcpy( Anfang, "Anfang des Programmes 'c.out': ARTIKELZENTRAL --> ARTIKELINDEX" );
	printf("%s ", Anfang);

	EXEC SQL database :datenbank;
	err("open");                         
	exec sql set isolation to dirty read;
	err("open");                         
	exec sql set lock mode to wait 20;  
	err("lock");                        

	/* artikel_name char(30) */
	PrepareLadeArtikelIndex();
	strcpy(str, "select " );
	if(swBulgaria)
	{
		strcat(str, "artikel_langname, " );
	}
	else
	{
		strcat(str, "artikel_name, " );
	}
	strcat(str, "artikel_nr " );
	strcat(str, "from artikelzentral " );

	exec sql prepare sel_zentral from :str;
	err( "prepare sel_zentral" );
 
	exec sql declare CC cursor with hold for sel_zentral;
	err( "declare CC" );
                      
	exec sql open CC;     
	err("open CC");             
   
	EXEC SQL begin work;
	err("Begin Work");
                      
	for(;;)               
	{                     
		exec sql fetch CC into :bezeichnung,:artikel_nr;
		if ( sqlca.sqlcode == 100 ) break;
		if ( zaehler++ % M_DURCHLAUF_COMMIT == 0 )
		{
			EXEC SQL commit work;
			err( "Commit Work" );
	          
			EXEC SQL begin work;
			err( "Begin Work" );
		}
		LadeArtikelIndex( artikel_nr, bezeichnung );
	}
	
	EXEC SQL commit work;
	err("Begin Work");

	sprintf( Ende, "geloescht: %d\neingefuegt: %d\n",iCountDel,iCountIns );
	printf("%s ", Ende);
	strcpy( Ende, "Ende des Programmes 'c.out': ARTIKELZENTRAL --> ARTIKELINDEX" );
	printf("%s ", Ende);
	
	return 0;

}

/*********************************************************************************************************************/
/* int PrepareLadeArtikelIndex( )                                                                                    */
/*********************************************************************************************************************/
int PrepareLadeArtikelIndex()
{
	exec sql begin declare section;
	char str[2048];
	exec sql end declare section;

	strcpy( str, "delete from artikelindex where current of CupdartikelIdx " );
	exec sql prepare DupdartikelIdx from :str;
	err( "prepare DupdartikelIdx" );
 
	strcpy( str, "insert into artikelindex ( artikel_nr, suchbezeichner ) " );
	strcat( str, "values ( ?, ? )" );
   
	exec sql prepare ins_artikel_idx from :str;
	err( "prepare ins_artikel_idx" );
   
	strcpy( str, "select " );
	strcat( str, "artikel_nr " );
	strcat( str, "from artikelindex where artikel_nr = ? for update " );

	exec sql prepare dec_artikel_idx from :str;
	err( "prepare dec_artikel_idx " );
	exec sql declare CupdartikelIdx cursor for dec_artikel_idx;
   
	return OK;      
}

/*********************************************************************************************************************/
/* int LadeArtikelIndex( long artikelnr, char *artbez )                                             */
/*********************************************************************************************************************/
int LadeArtikelIndex( long artikelnr, char *artbez )
{
	exec sql begin declare section;
	long ArtikelNr;
	char *MatchCode;
	exec sql end declare section;
	int i;
	int len;
   
	ArtikelNr = artikelnr;
 
	exec sql open CupdartikelIdx using :ArtikelNr;
  
	while ( SQLCODE == OK )
	{
		exec sql fetch CupdartikelIdx;
		err( "fetch artikelindex" );
		if ( SQLCODE == 0 )
		{
			exec sql execute DupdartikelIdx;   /* delete */
			err( "delete artikelindex" );
			iCountDel++;
		}
	}

	exec sql close CupdartikelIdx;
	err( "close CupdartikelIdx" );
   
	if(swBulgaria)
	{
		artbez[MAX_CH_ARTIKELLANGNAME] = '\0';
	}
	else
	{
		artbez[MAX_CH_ARTIKELNAME] = '\0';
	}
	for( i = strlen(artbez) - 1; i >= 0; i-- )
	{
		if ( artbez[i] != ' '	)
		{
			artbez[i+1] = '\0';
			break;
		}
	}

	if ( i < 0 )
	{
		return 0;		/* Kein Name eingetragen */
	}
   
	len = i + 1 - 2;	/* bis 3 bst 			 */
	for ( i = 0; i < len && SQLCODE == OK; i++ )
	{
		MatchCode = artbez + i;
		exec sql execute ins_artikel_idx using :ArtikelNr, :MatchCode;
		err( "insert artikelindex" );
		iCountIns++;
	}

	return OK;
}

/*********************************************************************************************************************/
/* static int err(char *fun)                                                                                         */
/*********************************************************************************************************************/
static int err(char *fun) 
{                                                                            
	if ( sqlca.sqlcode < 0 )  
	{                                                                        
		printf( "err: %s %ld/%ld\n", fun, sqlca.sqlcode,sqlca.sqlerrd[1] );   
		exit(1);                                                              
    }                                                                        
	return sqlca.sqlcode;                                                     
}                                                                            
