/************************************************************************************************/
/*     Hauptmodul: loadsaparticlestock.cxx														*/
/*         Source: 																				*/
/*          Autor: Frank Naumann   																*/
/*       Erstellt: 14.12.2023																	*/
/*        Sprache: C																			*/
/*        Erzeugt: manuell																		*/
/*        Aufgabe: Bestand aus SAP laden	^													*/
/*         Aufruf: loadsaparticlestock.sh -start -branchno NN									*/
/*																								*/
/************************************************************************************************/

/********************************************************************************/
/* VERSION */
/********************************************************************************/
#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "loadsaparticlestock"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

/********************************************************************************/
/* INCLUDE */
/********************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>


/********************************************************************************/
/* DEFINE */
/********************************************************************************/
#define SQLNOTFOUND       100
#define SQLCODE           sqlca.sqlcode            /* Sql-Fehler             */
#define SQLISAM           sqlca.sqlerrd[1]         /* Sql-Cisam-Fehler       */
#define NOTFOUND          sqlca.sqlcode == SQLNOTFOUND
#define OK                0
#define ERROR             -1
#define HINW              'H'
#define FEHL              'F'

/********************************************************************************/
/* MACROS */
/********************************************************************************/
#define ERROR_MSG( x )      if( SQLCODE < 0 ){				\
                               sprintf( error_msg, "%s %d/%d %s", x,\
                                        sqlca.sqlcode, sqlca.sqlerrd[1],\
                                        sqlca.sqlerrm); \
								PrintMsg( fun, x, FEHL , -1); \
								return ERROR;				\
							}

/********************************************************************************/
/* MODUL-GLOBALE VARIABLEN */
/********************************************************************************/

int zaehlerIns = 0;
int zaehlerUpd = 0;
char error_msg[181];

EXEC SQL BEGIN DECLARE SECTION;
char sql[2048];
char indatenbank[60];
short sBranchNo = 0;
short sExplain = FALSE;
short sDebug = FALSE;
int zeroqty = 0;

struct N_ARTICLE
{
	short branchno;
	long articleno;
};

struct N_ARTICLESTOCKREPLICATION
{
	short branchno;
	long articleno;
	short reservtype;
	char pharmacygroupid[4];
	long quantity;
};

struct N_BATCHREPLICATION
{
	short branchno;
	long articleno;
	char sapbatchid[11];
	long quantity;
};

struct N_ARTICLE structArticle;
struct N_ARTICLESTOCKREPLICATION structSapQty;
struct N_BATCHREPLICATION structBatch;
EXEC SQL END DECLARE SECTION;


/********************************************************************************/
/* VORWAERTS-DECLARATION */
/********************************************************************************/
int main(int, char**);
int ReadCommandLine();
int OpenDatabase();
int CloseDatabase();

int CreateTempTables();
int FillArticleTempTable();
int PrepareInsertTempTables();
int PrepareStockUpdateStatements();
int OuterLoop();
int CleanupTempTables();
int FillTempTables();
int InnerLoopStock();
int InnerLoopBatch();

static void PrintMsg(char *fun, char *error_msg, char mld , int rc);


/********************************************************************************/
/* int main( int argc, char **argv ) */
/********************************************************************************/
int main(int argc, char* argv[])
{
	char* fun = "Main";
	
	if (ReadCommandLine(argc, argv) != OK)
	{
		PrintMsg(fun, "mit Fehler beendet ReadCommandLine", FEHL, ERROR);
		return ERROR;
	}

	if (OpenDatabase() != OK)
	{
		PrintMsg(fun, "mit Fehler beendet OpenDatabase", FEHL, ERROR);
		return ERROR;
	}

	if (CreateTempTables() != OK)
	{
		PrintMsg(fun, "mit Fehler beendet CreateTempTables", FEHL, ERROR);
		return ERROR;
	}

	if (PrepareInsertTempTables() != OK)
	{
		PrintMsg(fun, "mit Fehler beendet PrepareInsertTempTables", FEHL, ERROR);
		return ERROR;
	}

	if (PrepareStockUpdateStatements() != OK)
	{
		PrintMsg(fun, "mit Fehler beendet PrepareStockUpdateStatements", FEHL, ERROR);
		return ERROR;
	}

	if (FillArticleTempTable() != OK)
	{
		PrintMsg(fun, "mit Fehler beendet FillArticleTempTable", FEHL, ERROR);
		return ERROR;
	}

	if (OuterLoop() != OK)
	{
		PrintMsg(fun, "mit Fehler beendet OuterLoop", FEHL, ERROR);
		return ERROR;
	}

	if(CloseDatabase() != OK )
	{
		PrintMsg(fun, "mit Fehler beendet CloseDatabase", FEHL, ERROR);
		return ERROR;
	}
	return OK;
}

/***** READ COMMAND LINE ********************************************************/
int ReadCommandLine(int argc, char* argv[])
{
	char* fun = "ReadCommandLine";
	char start_msg[255];

	sprintf(start_msg, "gestartet mit: ");
	for (int i = 0; i < argc; i++)
	{
		strcat(start_msg, argv[i]);
		strcat(start_msg, " ");
	}
	PrintMsg(fun, start_msg, HINW, OK);

	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-dbin"))
		{
			strcat(start_msg, " -dbin");
			i++;
			sprintf(indatenbank, "%s", argv[i]);
		}
		else if (!strcmp(argv[i], "-branchno"))
		{
			strcat(start_msg, " -branchno");
			i++;
			sBranchNo = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-explain"))
		{
			sExplain = TRUE;
		}
		else if (!strcmp(argv[i], "-debug"))
		{
			sDebug = TRUE;
		}
		else if (!strcmp(argv[i], "-version"))
		{
			printVersion(versioninfo);
			exit(OK);
		}
	}

	//if ( argc == 1 || skip == ERROR )
	if (argc == 1)
	{
		printf("  usage: %s\n\t"
			" { -dbin datenbankname <Datenbankname Eingabe> }\n\t"
			" { -branchno filialnr }\n\t"
			, argv[0]);
		exit(ERROR);
	}
	return OK;
}

/***** OPEN DATABASE ************************************************************/
int OpenDatabase()
{
	char* fun = "OpenDatabase";

	EXEC SQL DATABASE :indatenbank;
	ERROR_MSG("Fehler oeffnen DB")

	EXEC SQL SET LOCK MODE TO WAIT 20;
	ERROR_MSG("Set LockMode to Wait")

	EXEC SQL SET ISOLATION TO DIRTY READ;
	ERROR_MSG("Set Isolation to Dirty Read")

	if (sExplain == TRUE)
	{
		EXEC SQL SET EXPLAIN ON;
		ERROR_MSG("SET EXPLAIN ON")
	}

	return OK;
}

/***** CLOSE DATABASE ***********************************************************/
int CloseDatabase()
{
	char* fun = "CloseDatabase";

	EXEC SQL CLOSE database;
	ERROR_MSG("Close DB")

	return OK;
}

/***** CREATE TEMP TABLES *******************************************************/
int CreateTempTables()
{
	char* fun = "CreateTempTables";

	EXEC SQL CREATE TEMP TABLE tmp_distinctarticle(branchno integer, articleno integer);
	ERROR_MSG("create temp table tmp_distinctarticle");

	EXEC SQL CREATE TEMP TABLE tmp_sumqtysapstkrep(branchno integer, articleno integer, reservtype integer, pharmacygroupid CHAR(3), quantity integer);
	ERROR_MSG("create temp table tmp_sumqtysapstkrep");

	EXEC SQL CREATE TEMP TABLE tmp_sapconfirmedissues(branchno integer, articleno integer, reservtype integer, pharmacygroupid CHAR(3), quantity integer);
	ERROR_MSG("create temp table tmp_sapconfirmedissues");

	EXEC SQL CREATE TEMP TABLE tmp_cststockreserved(branchno integer, articleno integer, reservtype integer, pharmacygroupid CHAR(3), quantity integer);
	ERROR_MSG("create temp table tmp_cststockreserved");

	EXEC SQL CREATE TEMP TABLE tmp_articlereservation(branchno integer, articleno integer, reservtype integer, pharmacygroupid CHAR(3), quantity integer);
	ERROR_MSG("create temp table tmp_articlereservation");

	EXEC SQL CREATE TEMP TABLE tmp_sumuparticleqty(branchno integer, articleno integer, reservtype integer, pharmacygroupid CHAR(3), quantity integer);
	ERROR_MSG("create temp table tmp_sumuparticleqty");

	EXEC SQL CREATE TEMP TABLE tmp_batch(branchno integer, articleno integer, sapbatchid CHAR(10), quantity integer);
	ERROR_MSG("create temp table tmp_batch");

	return OK;
}

/***** FILL ARTICLE TEMP TABLE **************************************************/
int FillArticleTempTable()
{
	char* fun = "FillArticleTempTable";

	strcpy(sql,
		"insert into tmp_distinctarticle "
			"select distinct branchno, articleno "
			"from sapmaterialstockreplication "
			"where branchno = ? ");
	EXEC SQL PREPARE select_distinctarticle FROM :sql;
	ERROR_MSG("prepare select_distinctarticle");

	//Copy to Temp Table SAPStockReplication distinct article
	EXEC SQL EXECUTE select_distinctarticle USING :sBranchNo;
	ERROR_MSG("EXEC SQL EXECUTE select_distinctarticle");

	return OK;
}

/***** PREPARE INSERT TEMP TABLES ***********************************************/
int PrepareInsertTempTables()
{
	char* fun = "PrepareInsertTempTables";

	strcpy(sql,
		"insert into tmp_sumqtysapstkrep "
			"select branchno, articleno, reservtype, pharmacygroupid, sum(quantity) as quantity "
			"from sapmaterialstockreplication "
			"where branchno = ? and articleno = ? "
			"group by 1, 2, 3, 4 ");
	EXEC SQL PREPARE insert_sumqtysapstkrep FROM :sql;
	ERROR_MSG("prepare insert_sumqtysapstkrep");

	strcpy(sql,
		"insert into tmp_sapconfirmedissues "
			"select branchno, articleno ,reservtype, pharmacygroupid, sum(quantity) as quantity "
			"from sapconfirmedissues "
			"where branchno = ? and articleno = ? "
			"group by 1, 2, 3, 4 ");
	EXEC SQL PREPARE insert_sapconfirmedissues FROM :sql;
	ERROR_MSG("prepare insert_sapconfirmedissues");

	strcpy(sql,
		"insert into tmp_cststockreserved "
			"select branchno, articleno , -1, cast('' as CHAR(3)) as pharmacygroupid, sum(reservedqty) as quantity "
			"from cststockreserved "
			"where branchno = ? and articleno = ? "
			"group by 1, 2, 3, 4 ");
	EXEC SQL PREPARE insert_cststockreserved FROM :sql;
	ERROR_MSG("prepare insert_cststockreserved");

	strcpy(sql,
		"insert into tmp_articlereservation "
			"select branchno, articleno , -1, cast('' as CHAR(3)) as pharmacygroupid, sum(reservedqty) as quantity "
			"from articlereservation "
			"where branchno = ? and articleno = ? and reservtype in (0, 2) "
			"group by 1, 2, 3, 4 ");
	EXEC SQL PREPARE insert_articlereservation FROM :sql;
	ERROR_MSG("prepare insert_articlereservation");

	strcpy(sql,
		"insert into tmp_sumuparticleqty "
			"select tmp_sumqtysapstkrep.branchno, tmp_sumqtysapstkrep.articleno, tmp_sumqtysapstkrep.reservtype, tmp_sumqtysapstkrep.pharmacygroupid, "
			"(tmp_sumqtysapstkrep.quantity - NVL(tmp_sapconfirmedissues.quantity, 0) - NVL(tmp_cststockreserved.quantity,0) - NVL(tmp_articlereservation.quantity,0)) as quantity "
			"from tmp_sumqtysapstkrep "
			"left outer join tmp_sapconfirmedissues on tmp_sumqtysapstkrep.branchno = tmp_sapconfirmedissues.branchno and tmp_sumqtysapstkrep.articleno = tmp_sapconfirmedissues.articleno and tmp_sumqtysapstkrep.reservtype = tmp_sapconfirmedissues.reservtype and tmp_sumqtysapstkrep.pharmacygroupid = tmp_sapconfirmedissues.pharmacygroupid "
			"left outer join tmp_cststockreserved on tmp_sumqtysapstkrep.branchno = tmp_cststockreserved.branchno and tmp_sumqtysapstkrep.articleno = tmp_cststockreserved.articleno and tmp_sumqtysapstkrep.reservtype = tmp_cststockreserved.reservtype and tmp_sumqtysapstkrep.pharmacygroupid = tmp_cststockreserved.pharmacygroupid "
			"left outer join tmp_articlereservation on tmp_sumqtysapstkrep.branchno = tmp_articlereservation.branchno and tmp_sumqtysapstkrep.articleno = tmp_articlereservation.articleno and tmp_sumqtysapstkrep.reservtype = tmp_articlereservation.reservtype and tmp_sumqtysapstkrep.pharmacygroupid = tmp_articlereservation.pharmacygroupid "
			"where tmp_sumqtysapstkrep.branchno = ? and tmp_sumqtysapstkrep.articleno = ? ");
	EXEC SQL PREPARE insert_sumuparticleqty FROM :sql;
	ERROR_MSG("prepare insert_sumuparticleqty");

	strcpy(sql,
		"insert into tmp_batch "
			"select branchno, articleno, sapbatchid, sum(quantity) as quantity "
			"from sapmaterialstockreplication "
			"where branchno = ? and articleno = ? "
			"group by 1, 2, 3 ");
	EXEC SQL PREPARE insert_tmpbatch FROM :sql;
	ERROR_MSG("prepare insert_tmpbatch");

	return OK;
}

/***** PREPARE STOCK UPDATE STATEMENTS ******************************************/
int PrepareStockUpdateStatements()
{
	char* fun = "PrepareStockUpdateStatements";

	//update statement for artikellokal
	strcpy(sql,
		"update artikellokal set bestand = ? "
		"where filialnr = ? and artikel_nr = ? ");
	EXEC SQL PREPARE upd_artikellokal FROM :sql;
	ERROR_MSG("prepare upd_artikellokal");

	strcpy(sql,
		"delete from articlereservation where branchno = ? and articleno = ? and reservtype not in (0, 2)");
	EXEC SQL PREPARE del_artreserv FROM :sql;
	ERROR_MSG("prepare del_artreserv");

	//insert statement for articlereservation
	strcpy(sql,
		"insert into articlereservation (branchno, pharmacygroupid, articleno, reservtype, reservedqty) "
		"values ( ?, ?, ?, ?, ? )");
	EXEC SQL PREPARE ins_artreserv FROM :sql;
	ERROR_MSG("prepare ins_artreserv");

	//update statement for articlecharge
	strcpy(sql,
		"update articlecharge set stock = ? "
		"where branchno = ? and articleno = ? ");
	EXEC SQL PREPARE upd_articlecharge FROM :sql;
	ERROR_MSG("prepare upd_articlecharge");

	//update statement for articlecharge 2
	strcpy(sql,
		"update articlecharge set stock = ? "
		"where branchno = ? and articleno = ? and sapbatchid = ?");
	EXEC SQL PREPARE upd_articlecharge2 FROM :sql;
	ERROR_MSG("prepare upd_articlecharge2");

	return OK;
}

/***** CLEANUP TEMP TABLES *******************************************************/
int CleanupTempTables()
{
	char* fun = "CleanupTempTables";

	EXEC SQL TRUNCATE TABLE tmp_sumqtysapstkrep;
	ERROR_MSG("truncate table tmp_sumqtysapstkrep");

	EXEC SQL TRUNCATE TABLE tmp_sapconfirmedissues;
	ERROR_MSG("truncate table tmp_sapconfirmedissues");

	EXEC SQL TRUNCATE TABLE tmp_cststockreserved;
	ERROR_MSG("truncate table tmp_cststockreserved");

	EXEC SQL TRUNCATE TABLE tmp_articlereservation;
	ERROR_MSG("truncate table tmp_articlereservation");

	EXEC SQL TRUNCATE TABLE tmp_sumuparticleqty;
	ERROR_MSG("truncate table tmp_sumuparticleqty");

	EXEC SQL TRUNCATE TABLE tmp_batch;
	ERROR_MSG("truncate table tmp_batch");

	return OK;
}

/***** FILL TEMP TABLES **********************************************************/
int FillTempTables()
{
	char* fun = "FillTempTables";

	//Copy to Temp Table sapmaterialstockreplication
	EXEC SQL EXECUTE insert_sumqtysapstkrep USING :structArticle;
	ERROR_MSG("EXEC SQL EXECUTE insert_sumqtysapstkrep");

	//Copy to Temp Table SAPConfirmedissues		
	EXEC SQL EXECUTE insert_sapconfirmedissues USING :structArticle;
	ERROR_MSG("EXEC SQL EXECUTE insert_sapconfirmedissues");

	//Copy to Temp Table cststockreserved
	EXEC SQL EXECUTE insert_cststockreserved USING :structArticle;
	ERROR_MSG("EXEC SQL EXECUTE insert_cststockreserved");

	//Copy to Temp Table articlereservation
	EXEC SQL EXECUTE insert_articlereservation USING :structArticle;
	ERROR_MSG("EXEC SQL EXECUTE insert_articlereservation");

	EXEC SQL EXECUTE insert_sumuparticleqty USING :structArticle;
	ERROR_MSG("EXEC SQL EXECUTE insert_sumuparticleqty");
	
	EXEC SQL EXECUTE insert_tmpbatch USING :structArticle;
	ERROR_MSG("EXEC SQL EXECUTE insert_tmpbatch");

	return OK;
}

/***** OUTER LOOP (ARTICLES) *****************************************************/
int OuterLoop()
{
	char* fun = "OuterLoop";

	//Read from Temp Table and iterate 
	EXEC SQL PREPARE select_tmpdistinctarticle from
		"select branchno, articleno from tmp_distinctarticle";
	ERROR_MSG("prepare select_tmpdistinctarticle");

	EXEC SQL DECLARE objCursor_tmpdistinctarticle CURSOR WITH HOLD FOR select_tmpdistinctarticle;
	ERROR_MSG("declare objCursor_tmpdistinctarticle");

	EXEC SQL OPEN objCursor_tmpdistinctarticle;
	ERROR_MSG("open objCursor_tmpdistinctarticle");

	//Populate Temp Tables with sum of Qty for each article
	while (TRUE)
	{
		EXEC SQL FETCH objCursor_tmpdistinctarticle INTO :structArticle;
		ERROR_MSG("fetch objCursor_tmpdistinctarticle");

		if (NOTFOUND)
		{
			EXEC SQL CLOSE objCursor_tmpdistinctarticle;
			ERROR_MSG("EXEC SQL CLOSE objCursor_tmpdistinctarticle!");
			break;
		}

		if (CleanupTempTables() != OK)
		{
			PrintMsg(fun, "mit Fehler beendet CleanupTempTables", FEHL, ERROR);
			return ERROR;
		}
		if (FillTempTables() != OK)
		{
			PrintMsg(fun, "mit Fehler beendet FillTempTables", FEHL, ERROR);
			return ERROR;
		}
		if (InnerLoopStock() != OK)
		{
			PrintMsg(fun, "mit Fehler beendet InnerLoopStock", FEHL, ERROR);
			return ERROR;
		}
		if (InnerLoopBatch() != OK)
		{
			PrintMsg(fun, "mit Fehler beendet InnerLoopBatch", FEHL, ERROR);
			return ERROR;
		}
	}
	return OK;
}

/***** INNER LOOP (STOCK) ********************************************************/
int InnerLoopStock()
{
	char* fun = "InnerLoopStock";

	//Prepare to iterate over the temp table
	strcpy(sql, "select * from tmp_sumuparticleqty ");
	EXEC SQL PREPARE select_sumuparticleqty FROM :sql;
	ERROR_MSG("prepare select_sumuparticleqty");

	EXEC SQL DECLARE objCursor_sumuparticleqty CURSOR WITH HOLD FOR select_sumuparticleqty;
	ERROR_MSG("declare objCursor_sumuparticleqty");

	EXEC SQL OPEN objCursor_sumuparticleqty;
	ERROR_MSG("open objCursor_sumuparticleqty");
	
	//	
	//	EXEC SQL SELECT COUNT(*) INTO :recordsumupartqty FROM tmp_sumuparticleqty;
	//	ERROR_MSG("SELECT COUNT(*) tmp_sumuparticleqty");
	//
	EXEC SQL BEGIN WORK;
	ERROR_MSG("Begin Work");

	{
		//update artikellokal set bestand = 0 where filialnr = 61 and artikel_nr = 14;
		EXEC SQL EXECUTE upd_artikellokal USING
			:zeroqty,
			:structArticle.branchno,
			:structArticle.articleno;
		ERROR_MSG("execute upd_artikellokal");

		//delete from articlereservation where branchno = 61 and articleno = 14 and reservtype not in (0, 2);
		EXEC SQL EXECUTE del_artreserv USING
			:structArticle.branchno,
			:structArticle.articleno;
		ERROR_MSG("execute del_artreserv");
	}

	// Iterate and read each article from Temp Table and do calculate.
	while (TRUE)
	{
		EXEC SQL FETCH objCursor_sumuparticleqty INTO :structSapQty;
		ERROR_MSG("fetch objCursor_sumuparticleqty");

		if (NOTFOUND)
		{
			EXEC SQL CLOSE objCursor_sumuparticleqty;
			ERROR_MSG("EXEC SQL CLOSE objCursor_sumuparticleqty!");
			break;
		}

		if (sDebug == TRUE)
		{
			sprintf(error_msg, "%d %d %d %s %d", structSapQty.branchno, structSapQty.articleno, structSapQty.reservtype,
				structSapQty.pharmacygroupid, structSapQty.quantity);
			PrintMsg(fun, error_msg, HINW, OK);
		}

		if (structSapQty.quantity < 0)
		{
			structSapQty.quantity = 0;
		}

		if (structSapQty.reservtype == -1)
		{
			EXEC SQL EXECUTE upd_artikellokal USING
				:structSapQty.quantity,
				:structSapQty.branchno,
				:structSapQty.articleno;
			ERROR_MSG("execute upd_artikellokal");
			zaehlerUpd++;
		}
		else
		{
			EXEC SQL EXECUTE ins_artreserv USING
				:structSapQty.branchno,
				:structSapQty.pharmacygroupid,
				:structSapQty.articleno,
				:structSapQty.reservtype,
				:structSapQty.quantity;
			ERROR_MSG("execute ins_artreserv");
			zaehlerIns++;
		}
	}
	EXEC SQL COMMIT WORK;
	ERROR_MSG("Commit Work")
	return OK;
}


/***** INNER LOOP (BATCH) ********************************************************/
int InnerLoopBatch()
{
	char* fun = "InnerLoopBatch";

	//Prepare to iterate over the temp table
	strcpy(sql, "select branchno, articleno, sapbatchid, quantity from tmp_batch");
	EXEC SQL PREPARE select_tmpbatch FROM :sql;
	ERROR_MSG("prepare select_tmpbatch");

	EXEC SQL DECLARE objCursor_tmpbatch CURSOR WITH HOLD FOR select_tmpbatch;
	ERROR_MSG("declare objCursor_tmpbatch");

	EXEC SQL OPEN objCursor_tmpbatch;
	ERROR_MSG("open objCursor_tmpbatch");

	EXEC SQL BEGIN WORK;
	ERROR_MSG("Begin Work");


	//update articlecharge set stock = 0 where branchno = 61 and articleno = 14
	EXEC SQL EXECUTE upd_articlecharge USING
		:zeroqty,
		:structArticle.branchno,
		:structArticle.articleno;
	ERROR_MSG("execute upd_articlecharge");

	// Iterate and read each article from Temp Table and do update batch qty.
	while (TRUE)
	{
		EXEC SQL FETCH objCursor_tmpbatch INTO :structBatch;
		ERROR_MSG("fetch objCursor_tmpbatch");

		if (NOTFOUND)
		{
			EXEC SQL CLOSE objCursor_tmpbatch;
			ERROR_MSG("EXEC SQL CLOSE objCursor_tmpbatch!");
			break;
		}
		EXEC SQL EXECUTE upd_articlecharge2 USING
			:structBatch.quantity,
			:structBatch.branchno,
			:structBatch.articleno,
			:structBatch.sapbatchid;
		ERROR_MSG("execute upd_articlecharge2");
	}

	EXEC SQL COMMIT WORK;
	ERROR_MSG("Commit Work")
	return OK;
}


/************************************************************************************************************/
/* static void PrintMsg(char *fun, char *error_msg, char mld ) */
/************************************************************************************************************/
static void PrintMsg( char *fun, char *error_msg, char mld ,int rc)
{
	FILE *fp;
	struct tm *localtime();
	struct tm *zeit;
	long hour1;
	pid_t pid;
	long time();
	char logFile[1024];
    char *env;

	pid = getpid();
	hour1 = time( &hour1 );
	zeit  = localtime( &hour1 );

	env = getenv( "LOG_PATH" );
	if ( env == NULL )
		env = ".";
	//sprintf( logFile, "%s/wws.log", env );
	sprintf( logFile, "%s/loadsaparticlestock.log", env );
	if ( ( fp = fopen( logFile, "a" ) ) == (FILE *)0 )
		return;

	if(	zeit->tm_year > 99 ) zeit->tm_year -= 100;

	fprintf( fp, "%c %02d.%02d.%02d %02d:%02d:%02d "
			"pid=%05ld %.18s %s %s->%d/%d\n",
			mld,
			zeit->tm_mday,
			zeit->tm_mon + 1,
			zeit->tm_year,
			zeit->tm_hour,
			zeit->tm_min,
			zeit->tm_sec,
			pid,
			"loadsaparticlestock",
			fun,
			error_msg, 
			SQLCODE,
			SQLISAM );

	fclose(fp);
}
