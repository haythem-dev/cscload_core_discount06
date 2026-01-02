
/* ---------------------------------------------------------------------- *
 *                         G - A R T P R E . C                            *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   ARTPREIS generieren                                          *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  10.03.1999                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

#ifdef MIT_ARTPREIS_PFLEGE

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* -------  Spezielle includes ----------------------------------------- */

#include  "wdbups/wpp_prot.h"
#include  "wdbups/wpp_dbas.h"

/* ------- Tabellen includes -----------------------------------*/

#include <zartprei.h>
#include <artpreis.h>

#define L_ARTIKEL_NR 7

/* -----  Artpreis ------------------------ */

static int  mFd_Preis = -1;

static struct ARTPREIS *Buf_preis = NULL;


static void FreeBufferDesc_Preis( )
{
   if ( mFd_Preis >= 0 )
      CloseOneBufferDesc( mFd_Preis );
   mFd_Preis = -1;
}

static void FreeBuffer_Preis(  )
{
   if ( Buf_preis != NULL )
      free( Buf_preis );
   Buf_preis = NULL;
}

void m_ArtpreisDoc_FreeBufferDesc( )
{
   FreeBufferDesc_Preis( );
   FreeBuffer_Preis( );
}

static int GetBufferDesc_Preis( char * errmld )
{
   char *tabelle = "artpreis";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( mFd_Preis >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &mFd_Preis, tabelle, PROJECTION_ARTPREIS,
                                 NULL, NULL,
                                 V_ONLY_PROTO_VERTEIL,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     mFd_Preis = -1;
     return -1;
   }
   return 0;
}

static int AllocBuffer_Preis( char *errmld )
{
   int  lng_akt;
   int  lng_buf;

   if ( Buf_preis != NULL ) return 0;

   lng_akt = FdGetBufferLen( mFd_Preis );
   lng_buf = sizeof( struct ARTPREIS );

   if ( lng_akt < lng_buf ) lng_akt = lng_buf;

   Buf_preis = ( struct ARTPREIS *) malloc( lng_akt + 1 );
   if ( Buf_preis == NULL )
   {
     strcpy( errmld, "Tabelle artpreis: Puffer nicht allokiert" );
     return -1;
   }

   return 0;
}

int m_ArtpreisDoc_GetBufferDesc( char *errmld )
{
   if ( GetBufferDesc_Preis( errmld ) == -1 )  return -1;
   if ( AllocBuffer_Preis( errmld ) == -1 )    return -1;
   return 0;
}

#ifdef AAA
int m_ArtpreisDoc_IsToInsert( struct ZARTPREIS *pre1,
                              struct ZARTPREIS *pre2 )
{
/*
   if ( pre1->ARTIKEL_NR     != pre2->ARTIKEL_NR     ) return 1;
   if ( pre1->DATUMGUELTIGAB != pre2->DATUMGUELTIGAB ) return 1;
*/
   if ( pre1->GROSSO         != pre2->GROSSO         ) return 1;
   if ( pre1->AEP            != pre2->AEP            ) return 1;
   if ( pre1->AVP            != pre2->AVP            ) return 1;
   if ( strcmp( pre1->KE_MWST, pre2->KE_MWST ) != 0  ) return 1;
   return 0;
}
#endif

static void Copy_ZpreisToPreis( struct ARTPREIS  *preis,
                                struct ZARTPREIS *zpreis )
{
   preis->ARTIKEL_NR = zpreis->ARTIKEL_NR;
   preis->DATUMGUELTIGAB = zpreis->DATUMGUELTIGAB;
   preis->GROSSO         = zpreis->GROSSO        ;
   preis->AEP            = zpreis->AEP           ;
   preis->AVP            = zpreis->AVP           ;
   strcpy( preis->KE_MWST, zpreis->KE_MWST );
}

long m_ArtpreisDoc_InsertRecord( struct ZARTPREIS *preis, char *errmld )
{
   char PrimekeyCond[60];
   char format[60];

   FdInitTabBuf( mFd_Preis, Buf_preis );
   Copy_ZpreisToPreis( Buf_preis, preis );

   sprintf( format, "ARTIKEL_NR=%c%d.ld and DATUMGUELTIGAB=%cld",
                    '%', L_ARTIKEL_NR, '%' );
   sprintf( PrimekeyCond, format,
            Buf_preis->ARTIKEL_NR,
            Buf_preis->DATUMGUELTIGAB );

   return FdDelayInsertRecord( mFd_Preis, Buf_preis, PrimekeyCond, errmld );
}

/* MIT_ARTPREIS_PFLEGE */
#endif 
