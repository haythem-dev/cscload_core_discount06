
/* ////////// ZpDrMain.c /////////////// */
/* // Server SrvZdpDruck.so fuer ZdpDruck.exe ///////////// */

#include <stdio.h>                                
#include <stdlib.h>
#include <string.h>

#include <libscsvoodoo.h>
//#include <konvbuf.h>


/* ---------- Version ---------------- */
static char *SCCSID =
       "@(#)PHOENIX Stand: SrvZdpDruck 1.02 / 12.11.2001 Hajo Schmitt";

/* ----------------------------------- */

#define L_ANWENDER 8
static char anwender[L_ANWENDER + 1];


#ifdef MIT_DATABASE

/* --- SET ISOLATION-Fehler bei SE -------------------- */
                                                       
#define SQL_SETISOLA_ERROR   (-554)                    
                                                       
static void CloseBase(  )                                     
{                                                      
   SqlExecuteImm( "close database" );                  
}                                                      
                                                       
static long OpenBase( char *dbase, char *errmld )                          
{                                  
   long s;                         
   char db[100];
   strcpy( db, "database ");
   strcat( db, dbase );
                                                       
   s = SqlExecuteImm( db );             
   if ( s != 0 )   
   {                                                    
      strcpy( errmld, db ); 
      strcat( errmld, ": " );
      strcat( errmld, DynErrmld() );                    
      return s;                                         
   }                                                    
                                                        
   s = SqlExecuteImm("set isolation to dirty read" );   
   if ( s == SQL_SETISOLA_ERROR ) s = 0;                
   if ( s != 0 )                                        
   {                                                    
     strcpy( errmld, "set isolation: " );                      
     strcat( errmld, DynErrmld() );                   
     CloseBase( );                                    
     return s;                                        
   }                                                  
                                                      
   s = SqlExecuteImm( "SET LOCK MODE TO WAIT 10" );   
   if ( s == SQL_SETISOLA_ERROR ) s = 0;              
   if ( s != 0 )                                      
   {                                                  
     strcat( errmld, "set lock mode: ");              
     strcat( errmld, DynErrmld() );   
     CloseBase( );                    
     return s;                        
   }                                  
   return 0;                          
}                                     

#endif


#define LNG_DBASE 20

long SrvZdpDruck_Init(  char *w_buf, int w_lng, char *r_buf, int *r_lng )
{

    long  s;

    char  *buf;
    
    char dbase[LNG_DBASE + 1];
    char version[200];

    buf = w_buf;
    buf = DtFieldConvert ( TO_STRUCT,  anwender, buf, DT_CHAR,  L_ANWENDER );
    buf = DtFieldConvert ( TO_STRUCT,  dbase,    buf, DT_CHAR,  0 );
    buf = DtFieldConvert ( TO_STRUCT,  version,  buf, DT_CHAR,  0 );

    s = 0;
    if ( memcmp( &SCCSID[19], version, 24 ) != 0 )
    {
        s = 4710;
        strcpy( r_buf, &SCCSID[19] );
        r_buf[24] = '\0';
    }

#ifdef MIT_DATABASE
    if ( s == 0 )
        s = OpenBase( dbase, r_buf );
#endif

    if ( s == 0 )
    {
/*
        InitPflegeDesc_ArtikelfDoc( anwender );
        InitPflegeDesc_GartikelfDoc( anwender );
        InitPflegeDesc_ArtprogDoc( anwender );
        InitPflegeDesc_FlieferDoc( anwender );
        InitPflegeDesc_EkparamDoc( anwender );
        InitPflegeDesc_FilialeDoc( anwender );
        InitPflegeDesc_RgblinfoDoc( anwender );
        InitPflegeDesc_FeierDoc( anwender );
        InitPflegeDesc_FilabgDoc( anwender );
        InitPflegeDesc_FilbesDoc( anwender ); 
*/
        *r_buf = '\0';
    }
    *r_lng = strlen( r_buf );   
    return s;
}

long SrvZdpDruck_Exit( char *w_buf, int w_lng, char *r_buf, int *r_lng )
{
/*
    FreeBufferDesc_ArtikelfDoc( );
    FreeBufferDesc_GartikelfDoc( );
    FreeBufferDesc_ArtprogDoc( );
    FreeBufferDesc_FlieferDoc( );
    FreeBufferDesc_EkparamDoc( );
    FreeBufferDesc_FilialeDoc( );
    FreeBufferDesc_RgblinfoDoc( );
    FreeBufferDesc_FeierDoc( );
    FreeBufferDesc_FilabgDoc( );
    FreeBufferDesc_FilbesDoc( ); 
*/

#ifdef MIT_DATABASE
    CloseBase();
#endif

    *r_buf = '\0';
    *r_lng = strlen( r_buf );   
    return 0;
}


/* ------------------- ????????? multiply defined in ------------------- */
/*
void _fini( )
{
    FreeBufferDesc_FlieferDoc( );

    CloseBase();
}
*/
