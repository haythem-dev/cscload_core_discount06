
/* ---------------------------------------------------------------------- *
 *                         D E L P R O T . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Loescht das Protokoll                                        *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  09.07.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>

/* --------- relation UPFINFO -------------------------- */

static int fd_read_updinfo = -1;

#ifdef LESE_UEBER_UPDINFO

long Updinfo_DeclareCsWh( char *errmld )
{
    long s;

    s = SqlDeclareCsWh( &fd_read_updinfo,
                        "select PROTOKOL_NR from UPDINFO where PROTOKOL_NR=?",
                        "UPDINFO.PROTOKOL_NR", NULL );
    if ( s != 0 )
    {
      fd_read_updinfo = -1;
      sprintf( errmld, "UPDINFO DeclaseCsWh: %s", DynErrmld() );
    }
    return s;
}

long Updinfo_ReadDeclCs( long protokol_nr, char *errmld )
{
    long s;
    long nr;

    s = SqlReadDeclCs( fd_read_updinfo, &nr, NULL, &protokol_nr, NULL  );

    if ( !( s == 100 || s == 0 ) )
      sprintf( errmld, "UPDINFO ReadDeclCs: %s", DynErrmld() );
    return s;
}

void Updinfo_CloseDeclCs(  )
{
   if ( fd_read_updinfo != -1 )
   {
      SqlCloseCs( fd_read_updinfo );
      fd_read_updinfo = -1;
   }
}

#else

long Updinfo_DeclareCsWh( char *errmld )
{
    long s;

    s = SqlDeclareCsWh( &fd_read_updinfo,
                        "select PROTOKOL_NR from VERTINFO where PROTOKOL_NR=?",
                        "VERTINFO.PROTOKOL_NR", NULL );
    if ( s != 0 )
    {
      fd_read_updinfo = -1;
      sprintf( errmld, "VERTINFO DeclaseCsWh: %s", DynErrmld() );
    }
    return s;
}

long Updinfo_ReadDeclCs( long protokol_nr, char *errmld )
{
    long s;
    long nr;

    s = SqlReadDeclCs( fd_read_updinfo, &nr, NULL, &protokol_nr, NULL  );

    if ( !( s == 100 || s == 0 ) )
      sprintf( errmld, "VERTINFO ReadDeclCs: %s", DynErrmld() );
    return s;
}

void Updinfo_CloseDeclCs(  )
{
   if ( fd_read_updinfo != -1 )
   {
      SqlCloseCs( fd_read_updinfo );
      fd_read_updinfo = -1;
   }
}

#endif   /* LESE_UEBER_UPDINFO  */


/* --------- relation PROTOKOL ------------------------- */

static int fd_del_protokol = -1;

static long Protokol_PrepDelete( char *errmld )
{
    long s;
    s = SqlPrepareStmnt ( &fd_del_protokol,
                          "delete from PROTOKOL where PROTOKOL_NR=?",
                          "PROTOKOL.PROTOKOL_NR", NULL );
    if ( s != 0 )
    {
      fd_del_protokol = -1;
      sprintf( errmld, "PROTOKOLL PrepDelete: %s", DynErrmld() );
    }
    return s;
}

static long Protokol_ExecuteDelete( long protokol_nr, char *errmld )
{
    long s;
    long nr;
    nr  = protokol_nr;
    s = SqlExecutePrepare( fd_del_protokol, &nr, NULL );
    if ( s != 0 )
      sprintf( errmld, "PROTOKOL ExecDelete: %s", DynErrmld() );
    return s;
}

static long Protokol_FreeDelete( char *errmld )
{
    long s;
    if ( fd_del_protokol == -1 )  return 0;
    s = SqlFreePrepare( fd_del_protokol );
    if ( s != 0 && errmld != NULL )
        sprintf( errmld, "PROTOKOL FreeDelete: %s", DynErrmld() );
    fd_del_protokol = -1;
    return s;
}

/* --------- relation PROTINFO ------------------------- */

static int fd_del_protinfo = -1;

static long Protinfo_PrepDelete( char *errmld )
{
    long s;
    s = SqlPrepareStmnt ( &fd_del_protinfo,
                          "delete from PROTINFO where PROTOKOL_NR=?",
                          "PROTINFO.PROTOKOL_NR", NULL );
    if ( s != 0 )
    {
      fd_del_protinfo = -1;
      sprintf( errmld, "PROTOINFO PrepDelete: %s", DynErrmld() );
    }
    return s;
}

static long Protinfo_ExecuteDelete( long protokol_nr, char *errmld )
{
    long s;
    long nr;
    nr  = protokol_nr;
    s = SqlExecutePrepare( fd_del_protinfo, &nr, NULL );
    if ( s != 0 )
      sprintf( errmld, "PROTINFO ExecDelete: %s", DynErrmld() );
    return s;
}

static long Protinfo_FreeDelete( char *errmld )
{
    long s;
    if ( fd_del_protinfo == -1 )  return 0;
    s = SqlFreePrepare( fd_del_protinfo );
    if ( s != 0 && errmld != NULL )
        sprintf( errmld, "PROTINFO FreeDelete: %s", DynErrmld() );
    fd_del_protinfo = -1;
    return s;
}


/* --------- Transaktion  ------------------------------ */

static long StartWork( char *errmld )
{
   long s;
   s = SqlBeginWork( );
   if ( s != 0 )
   {
     strcpy( errmld, "BeginWork: " );
     strcat( errmld, DynErrmld() );
   }
   return s;
}

static long EndWork( long status, char *errmld )
{
   long s;
   if ( status == 0 )
   {
      s = SqlCommitWork( );
      if ( s != 0 )
      {
         strcpy( errmld, "CommitWork: " );
         strcat( errmld, DynErrmld() );
       }
      return s;
    }
    else
    {
      s = SqlRollbackWork( );
      return status;
    }
}

/* --------------- Externals ------------------------- */

long PrepareProtokolForDelete ( char *errmld )
{
   long s;
   s = Protokol_PrepDelete( errmld );
   if ( s != 0 ) return s;
   s = Protinfo_PrepDelete( errmld );
   if ( s != 0 )
      Protokol_FreeDelete( NULL );
   return s;
}

void FreeProtokolForDelete (  )
{
  Protinfo_FreeDelete( NULL );
  Protokol_FreeDelete( NULL );
}

long ExecuteProtokolForDelete( long protokol_nr, char *errmld )
{
   long s;
   s = StartWork( errmld );
   if ( s == 0 )
   {
      s = Protokol_ExecuteDelete( protokol_nr, errmld );
      if ( s == 0 )
        s = Protinfo_ExecuteDelete( protokol_nr, errmld );
      s = EndWork( s, errmld );
   }
   return s;
}

/* ------------------ Spezial -------------------------------- */


long SpezialLoesche( long nr, long *count, char *errmld )
{
   long s;
   char sql[100];
   s = StartWork( errmld );
   if ( s == 0 )
   {
       sprintf( sql, "delete from protokol where protokol_nr<=%ld", nr );
       s = SqlExecuteImm( sql );
       if ( s == 0 )
       {
           *count = SqlRowsProcessed();
            sprintf( sql, "delete from protinfo where protokol_nr<=%ld", nr );
            s = SqlExecuteImm( sql );
       }
       if ( s != 0 )
       {
            strcpy( errmld, "SpezialLoesche: " );
            strcat( errmld, DynErrmld() );
       }
       s = EndWork( s, errmld );
   }
   return s;
}


long ProtInfoLoesche( long nr, long *count, char *errmld )
{
   long s;
   char sql[100];
   s = StartWork( errmld );
   if ( s == 0 )
   {
        sprintf( sql, "delete from protinfo where protokol_nr<=%ld", nr );
        s = SqlExecuteImm( sql );
        if ( s == 0 )
            *count = SqlRowsProcessed();
        else
        {
            strcpy( errmld, "ProtInfoLoesche: " );
            strcat( errmld, DynErrmld() );
        }
        s = EndWork( s, errmld );
   }
   return s;
}


