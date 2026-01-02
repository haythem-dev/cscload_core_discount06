/* dbinit.cxx */
#include<stdio.h>
#include<string.h>

#define UNUSED(x) (void)(x)

EXEC SQL include sqlca;
EXEC SQL include sqltypes; 

long UID=0;
static int iIsolation=0;

EXEC SQL begin declare section;
     short filiale;
EXEC SQL end declare section;

int DbinitOpen_database(char *szDatabase, char *error_msg)
{
   EXEC SQL begin declare section;
   char sqlDb[81];
   EXEC SQL end declare section;

   if ( szDatabase == NULL )
   {
      sprintf (error_msg, "DbinitOpen_database: database==NULL");
      return -1;
   }
   else
   {
      strcpy( sqlDb, szDatabase );
   }

   EXEC SQL connect to :sqlDb;
   if (sqlca.sqlcode != 0)  /* Datenbankfehler */
     {
      sprintf (error_msg, "DbinitOpen_database: database: %ld %ld",
                          sqlca.sqlcode, sqlca.sqlerrd[1]);
      return -1;
     }

   EXEC SQL set lock mode to wait 20;
   if (sqlca.sqlcode != 0)  /* Datenbankfehler */
     {
      sprintf (error_msg, "DbinitOpen_database: lock %ld %ld",
                          sqlca.sqlcode, sqlca.sqlerrd[1]);
      return -1;
     }
   EXEC SQL set isolation to dirty read;
   if ((sqlca.sqlcode != 0) && (sqlca.sqlcode != -256))  /* Datenbankfehler */
     {
      sprintf (error_msg, "DbinitOpen_database: set iso: %ld %ld",
                          sqlca.sqlcode, sqlca.sqlerrd[1]);
      return -1;
     }

   UID = 0;                                  /* UID noch nicht vergeben */
   return 0;
}

int DbinitClose_database(char *error_msg)
{
   EXEC SQL disconnect all; 

   if (sqlca.sqlcode != 0)  /* Datenbankfehler */
     {
      sprintf (error_msg, "DbinitClose_database: %ld %ld",
                          sqlca.sqlcode, sqlca.sqlerrd[1]);
      return -1;
     }
   return 0;
}

int DbinitCommitWork(char *error_msg)
{
   EXEC SQL commit work; 
   if (sqlca.sqlcode != 0)  /* Datenbankfehler */
     {
      sprintf (error_msg, "DbinitCommitWork: %ld %ld",
                          sqlca.sqlcode, sqlca.sqlerrd[1]);
      return -1;
     }
   return 0;
}

int DbinitSetIsolation(int isolation_typ , char *error_msg)
{
    UNUSED(error_msg);

	if (isolation_typ)
	{
		if(iIsolation == isolation_typ) return 0;
		EXEC SQL set isolation to committed read;
		/* keine Fehlerabfrage, da nur Fehler, wenn Datenbank weg */ 
		iIsolation = isolation_typ;
	}
	else
	{
		if(iIsolation == isolation_typ) return 0;
		EXEC SQL set isolation to dirty read;
		iIsolation = isolation_typ;
	}
   return 0;
}
