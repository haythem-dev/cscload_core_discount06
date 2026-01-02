/* ---------------------------------------------------------------------- *
 *                            CP_IFA.C                                    *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die IFA-Artikeldatei ein und integriert         *
 *                  die Saetze in den lokalen UPDATE-POOL                 *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 04.03.00                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <zifaart.h>

#include "ifa_satz.h"
#include "g_ifoart.h"

#include "pnamcode.h"
#include "znb_gen.h"

/* ---- Plausibilitaet kopieren ---- */

struct CpPlausi
{
   int Zifaart;
   int IfaOart;
};

/*
    {  PL_A00SSATZ    ,  P_IFAOART_A00SSATZ     } ,
    {  PL_A00LKZ      ,  P_IFAOART_A00LKZ       } ,
*/


static struct CpPlausi CpPl[] =
{
     {  PL_A00PZN      ,  P_ZIFAOART_A00PZN       } ,
     {  PL_A00PBEZ     ,  P_ZIFAOART_A00PBEZ      } ,
     {  PL_A00PGMENG   ,  P_ZIFAOART_A00PGMENG    } ,
     {  PL_A00PGEINH   ,  P_ZIFAOART_A00PGEINH    } ,
     {  PL_A00DARFO    ,  P_ZIFAOART_A00DARFO     } ,
     {  PL_A00ANBNR    ,  P_ZIFAOART_A00ANBNR     } ,
     {  PL_A00ATYP     ,  P_ZIFAOART_A00ATYP      } ,
     {  PL_A00EAN      ,  P_ZIFAOART_A00EAN       } ,
     {  PL_A00ARTNR    ,  P_ZIFAOART_A00ARTNR     } ,
     {  PL_A05VFDAT    ,  P_ZIFAOART_A05VFDAT     } ,
     {  PL_A05LZEIT    ,  P_ZIFAOART_A05LZEIT     } ,
     {  PL_A05KKETTE   ,  P_ZIFAOART_A05KKETTE    } ,
     {  PL_A05TMAX     ,  P_ZIFAOART_A05TMAX      } ,
     {  PL_A05TMIN     ,  P_ZIFAOART_A05TMIN      } ,
     {  PL_A05LICHT    ,  P_ZIFAOART_A05LICHT     } ,
     {  PL_A05FEUCHT   ,  P_ZIFAOART_A05FEUCHT    } ,
     {  PL_A05LAGE     ,  P_ZIFAOART_A05LAGE      } ,
     {  PL_A05ZERBR    ,  P_ZIFAOART_A05ZERBR     } ,
     {  PL_A04LAENGE   ,  P_ZIFAOART_A04LAENGE    } ,
     {  PL_A04HOEHE    ,  P_ZIFAOART_A04HOEHE     } ,
     {  PL_A04BREITE   ,  P_ZIFAOART_A04BREITE    } ,
     {  PL_A04GWCHT    ,  P_ZIFAOART_A04GWCHT     } ,
     {  PL_A01AMPVAMG  ,  P_ZIFAOART_A01AMPVAMG   } ,
     {  PL_A01AMPVSGB  ,  P_ZIFAOART_A01AMPVSGB   } ,
     {  PL_A01ZBV      ,  P_ZIFAOART_A01ZBV       } ,   /* EAVP */
     {  PL_A01GEPDM    ,  P_ZIFAOART_A01GEPDM     } ,
	 {  PL_A01UVP      ,  P_ZIFAOART_A01UVP       } ,
     {  PL_A01AEPDM    ,  P_ZIFAOART_A01AEPDM     } ,
     {  PL_A01AVPDM    ,  P_ZIFAOART_A01AVPDM     } ,
     {  PL_A01MWST     ,  P_ZIFAOART_A01MWST      } ,
     {  PL_A02AM       ,  P_ZIFAOART_A02AM        } ,
     {  PL_A02MP       ,  P_ZIFAOART_A02MP        } ,
     {  PL_A02APPFL    ,  P_ZIFAOART_A02APPFL     } ,
     {  PL_A02VSPFL    ,  P_ZIFAOART_A02VSPFL     } ,
     {  PL_A02BTM      ,  P_ZIFAOART_A02BTM       } ,
     {  PL_A02TFG      ,  P_ZIFAOART_A02TFG       } ,
     {  PL_A02DROCH    ,  P_ZIFAOART_A02DROCH     } ,
     {  PL_A02TIERAM   ,  P_ZIFAOART_A02TIERAM    } ,
     {  PL_A02NEGLIS   ,  P_ZIFAOART_A02NEGLIS    } ,
     {  PL_A03VTSTAT   ,  P_ZIFAOART_A03VTSTAT    } ,
     {  PL_A03VWGGH    ,  P_ZIFAOART_A03VWGGH     } ,
     {  PL_A03VWGAPO   ,  P_ZIFAOART_A03VWGAPO    } ,
     {  PL_A03VWGKAP   ,  P_ZIFAOART_A03VWGKAP    } ,
     {  PL_A03VWGSEH   ,  P_ZIFAOART_A03VWGSEH    } ,
     {  PL_A03VKSTAT   ,  P_ZIFAOART_A03VKSTAT    } ,
     {  PL_A06PZNNF    ,  P_ZIFAOART_A06PZNNF     } ,
	 {  PL_A02HMZV     ,  P_ZIFAOART_A02HMZV      } ,
	 {  PL_A02LIFSTYL  ,  P_ZIFAOART_A02LIFSTYL   } ,
	 {	PL_A02AUSNREI  ,  P_ZIFAOART_A02AUSNREI	  } ,
	 {	PL_A02GENER	   ,  P_ZIFAOART_A02GENER	  } ,
	 {	PL_A02SDB	   ,  P_ZIFAOART_A02SDB		  } ,
	 {	PL_A02NEM	   ,  P_ZIFAOART_A02NEM		  } ,
	 {	PL_A06PZNORIG  ,  P_ZIFAOART_A06PZNORIG   } ,
     {  PL_A02LEBENSM  ,  P_ZIFAOART_A02LEBENSM   } ,
     {  PL_A02DIAET    ,  P_ZIFAOART_A02DIAET     } ,
 
     {  PL_A02HOMOEO   ,  P_ZIFAOART_A02HOMOEO    } ,
     {  PL_A02ANTHRO   ,  P_ZIFAOART_A02ANTHRO    } ,
     {  PL_A02PHYTO    ,  P_ZIFAOART_A02PHYTO     } ,
     {  PL_A02BIOZID   ,  P_ZIFAOART_A02BIOZID    } ,
     {  PL_A02PSM      ,  P_ZIFAOART_A02PSM       } ,
     {  PL_A02TREZEP   ,  P_ZIFAOART_A02TREZEP    } ,
     {  PL_A0247AMG    ,  P_ZIFAOART_A0247AMG     } ,
	 {  PL_A02ZULREG   ,  P_ZIFAOART_A02ZULREG    } ,
	 {  PL_A01SERSTAT  ,  P_ZIFAOART_A01ERSTATT   } ,
	 
	 {  PL_A00PPN	   ,  P_ZIFAOART_A00PPN	   } ,
	 {  PL_A01SAB130A  ,  P_ZIFAOART_A01AB130A2   } ,
	 {  PL_A02VERIFIZ  ,  P_ZIFAOART_A02VERIFIZ   } ,
	 {  PL_A0252B	   ,  P_ZIFAOART_A0252B		   } ,
	 {  PL_A02BIOSIEG  ,  P_ZIFAOART_A02BIOSIEG	   } ,
	 {  PL_A02KOSMET   ,  P_ZIFAOART_A02KOSMET	   } ,
	 {  PL_A02STERIL   ,  P_ZIFAOART_A02STERIL	   } ,
	 {  PL_A01RESERV1  ,  P_ZIFAOART_A01RESERV1   } ,
	 {  PL_A01RESERV2  ,  P_ZIFAOART_A01RESERV2   } ,
	 {  PL_A01RESERV3  ,  P_ZIFAOART_A01RESERV3   } ,
	 {  PL_A02RESERV1  ,  P_ZIFAOART_A02RESERV1   } ,
	 {  PL_A02RESERV2  ,  P_ZIFAOART_A02RESERV2   } ,
	 {  PL_A02RESERV3  ,  P_ZIFAOART_A02RESERV3   } ,
	 {  PL_A02130A18   ,  P_ZIFAOART_A02130A18   } ,
	 {  PL_A02130A1A8  ,  P_ZIFAOART_A02130A1A8   } ,
	 {  PL_A02ELEKTRO  ,  P_ZIFAOART_A02ELEKTRO      } ,
     {  PL_A02WIRKSTO  ,  P_ZIFAOART_A02WIRKSTO      } ,    
	 {  PL_A00NTIN	   ,  P_ZIFAOART_A00NTIN      } ,    
	 
	 {  PL_A01PPU	   ,  P_ZIFAOART_A01PPU   } ,
	 {  PL_A01APU783A  ,  P_ZIFAOART_A01APU783A   } ,
	 {  PL_A01AEPPPU   ,  P_ZIFAOART_A01AEPPPU   } ,
	 {  PL_A01AVPPPU   ,  P_ZIFAOART_A01AVPPPU   } ,
	 {  PL_A02EB130B  ,   P_ZIFAOART_A02EB130B   } ,
	 {  PL_A02EXPLOS  ,   P_ZIFAOART_A02EXPLOS   } ,
	 {  PL_A02BIOTECH  ,  P_ZIFAOART_A02BIOTECH  } ,
	 {  PL_A02STIFEAR  ,  P_ZIFAOART_A02STIFEAR  } ,
	 {  PL_A02WEEEREG  ,  P_ZIFAOART_A02WEEEREG  } ,
	 {  PL_A02BATTG		, P_ZIFAOART_A02BATTG  } ,
	 {  PL_A02UNNR	   ,  P_ZIFAOART_A02UNNR    } ,
	 {  PL_A11VERIPFL  ,  P_ZIFAOART_A11VERIPFL  } ,
	 
     {  PL_A02SWUNDB   ,  P_ZIFAOART_A02SWUNDB   } ,
     {  PL_A02ATMP     ,  P_ZIFAOART_A02ATMP     } ,
     {  PL_A02AUSIMPF  ,  P_ZIFAOART_A02AUSIMPF  } ,
     {  PL_A02EUNOVEL  ,  P_ZIFAOART_A02EUNOVEL  } ,
     {  PL_A02ORDRUG   ,  P_ZIFAOART_A02ORDRUG   } ,
     {  PL_A02BEDZUL   ,  P_ZIFAOART_A02BEDZUL   } ,
     {  PL_A02ZULAUSN  ,  P_ZIFAOART_A02ZULAUSN  } ,
     {  PL_A02AMNOG    ,  P_ZIFAOART_A02AMNOG    } ,
     {  PL_A02PRSTRMO  ,  P_ZIFAOART_A02PRSTRMO  } ,
     {  PL_A00GTIN	   ,  P_ZIFAOART_A00GTIN     } ,

     /* --------- IFA Version 20244 --------- */
     {  PL_A02AMDARKI  ,  P_ZIFAOART_A02AMDARKI  } ,
     {  PL_A02AMAUFFB  ,  P_ZIFAOART_A02AMAUFFB  } ,
     {  PL_A02AMBEKI   ,  P_ZIFAOART_A02AMBEKI   } ,
     {  PL_A02AMVEKRW  ,  P_ZIFAOART_A02AMVEKRW  } ,
     {  PL_A01DAPU78   ,  P_ZIFAOART_A01DAPU78   } ,
     {  PL_A02D130A18  ,  P_ZIFAOART_A02D130A18  } ,

     /* --------- IFA Version 20248 --------- */
     {  PL_A02MEDCG    ,  P_ZIFAOART_A02MEDCG    },
     {  PL_A05LGTMPB   ,  P_ZIFAOART_A05LGTMPB   },

     /* --------- IFA Version 20252 --------- */
     { PL_A01B130B1C   ,  P_ZIFAOART_A01B130B1C  },
     { PL_A01DAT78     ,  P_ZIFAOART_A01DAT78    },
     { PL_A01RAB130A   ,  P_ZIFAOART_A01RAB130A  },
     { PL_A01ZUZAH61   ,  P_ZIFAOART_A01ZUZAH61  },

     {  -1             ,  -1                     }
 };

static struct CpPlausi CpZuzahl[] =
{
     {  PL_ZUZAHL  ,  P_ZIFAOART_A09THGP    } ,
     {  -1         ,  -1                    }
};

static void CopyPlausi( char *NB_PLAUSI_Zifaart )
{
   int i;
   char *NB_PLAUSI_IfaOart;
   NB_PLAUSI_IfaOart = GetRefToIfaOartPlausi();
   i = 0;
   while ( CpPl[i].Zifaart != - 1 )
   {
     NB_PLAUSI_Zifaart[ CpPl[i].Zifaart ] = NB_PLAUSI_IfaOart[ CpPl[i].IfaOart ];
     i++;
   }
}

static void PlausiZuzahl( char *NB_PLAUSI_Zifaart )
{
   int i;
   char *NB_PLAUSI_IfaOart;
   NB_PLAUSI_IfaOart = GetRefToIfaOartPlausi();
   i = 0;
   while ( CpZuzahl[i].Zifaart != - 1 &&
      NB_PLAUSI_IfaOart[ CpZuzahl[i].IfaOart ] == NOVALUE_PL ) i++;
   if ( CpZuzahl[i].Zifaart == - 1 )
      NB_PLAUSI_Zifaart[ PL_ZUZAHL ] = NOVALUE_PL;          
   else
      NB_PLAUSI_Zifaart[ PL_ZUZAHL ] = '0'; 
}
   
/* ---------- Zuzahlung -------------------------------- */

static void Zuzahlung_Build( struct ZIFAART *zifa, struct P_IFAOART *oifa )
{
   memset( zifa->ZUZAHL, '0', L_ZIFAART_ZUZAHL );

   if ( strcmp (oifa->A09THGP, "  ") == 0)
		zifa->ZUZAHL[0] = '2';
   else if ( strcmp (oifa->A09THGP, "00") == 0)
		zifa->ZUZAHL[0] = '1';
   else if ( strcmp (oifa->A09THGP, "01") == 0)
		zifa->ZUZAHL[0] = '3';
   else if ( strcmp (oifa->A09THGP, "02") == 0)
		zifa->ZUZAHL[0] = '5';
   else if ( strcmp (oifa->A09THGP, "03") == 0)
		zifa->ZUZAHL[0] = '6';
   else if ( strcmp (oifa->A09THGP, "04") == 0)
		zifa->ZUZAHL[0] = '1';
   
   zifa->ZUZAHL[L_ZIFAART_ZUZAHL] = '\0';
}


int OifaToZifa( struct ZIFAART *zifa, struct P_IFAOART *oifa )
{
   char temp[110];

   /* Artikelname */
   strcpy( zifa->A00PBEZ, oifa->A00PBEZ );

   /* Packung: Menge  */
   strcpy( zifa->A00PGMENG , oifa->A00PGMENG );

   /* Packung:  Mengeneinheit */
   strcpy( zifa->A00PGEINH, oifa->A00PGEINH );
 
   /* Darreichung */
   strcpy( zifa->A00DARFO, oifa->A00DARFO );
   if ( strcmp( zifa->A00DARFO, "---" ) == 0 )
        strcpy( zifa->A00DARFO, "   " );

   /* Herstellernummer */
   zifa->A00ANBNR = oifa->A00ANBNR;

   /* Artikeltyp: Klinikpackung */
   strcpy( zifa->A00ATYP, oifa->A00ATYP );

   /* EAN-Nummer */
   strcpy( zifa->A00EAN, oifa->A00EAN );

   /* GTIN */
   strcpy(zifa->A00GTIN, oifa->A00GTIN);

   /* NTIN */
   strcpy( zifa->A00NTIN, oifa->A00NTIN );

   /* ArtikelNr-Hersteller */
   strcpy( zifa->A00ARTNR, oifa->A00ARTNR );

   /* Kennz. Verfalldatum  */
   strcpy( zifa->A05VFDAT, oifa->A05VFDAT );

   /* Laufzeit in Monaten <= 60 */
   zifa->A05LZEIT = oifa->A05LZEIT;

   /* Kennzeichen Kuehlkette */
   strcpy( zifa->A05KKETTE, oifa->A05KKETTE );

   /* Lagertemperatur max */
   strcpy( zifa->A05TMAX, oifa->A05TMAX );

   /* Lagertemperatur min */
   strcpy( zifa->A05TMIN, oifa->A05TMIN );

   /* Kennz. lichtempfindlich */
   strcpy( zifa->A05LICHT, oifa->A05LICHT );

   /* Kennz. feuchtempfindlich */
   strcpy( zifa->A05FEUCHT, oifa->A05FEUCHT );

   /* Kennz. lageempfindlich */
   strcpy( zifa->A05LAGE, oifa->A05LAGE );

   /* Kennz. zerbrechlich */
   strcpy( zifa->A05ZERBR, oifa->A05ZERBR );

   /* Laenge */
   strcpy( zifa->A04LAENGE, oifa->A04LAENGE );

   /* Hoehe  */
   strcpy( zifa->A04HOEHE, oifa->A04HOEHE );

   /* Breite */
   strcpy( zifa->A04BREITE, oifa->A04BREITE );

   /* Gewicht */
   strcpy( zifa->A04GWCHT, oifa->A04GWCHT );

   /* Kennz. AMPreisV: Taxplichtig, Nettoaertikel */
   strcpy( zifa->A01AMPVAMG, oifa->A01AMPVAMG );
   strcpy( zifa->A01AMPVSGB, oifa->A01AMPVSGB );

   /* Datenfeld zur besonderen Verwendung */
   zifa->A01ZBV   = oifa->A01ZBV;	/* EAVP */
 
   /* UVP */
   zifa->A01UVP = oifa->A01UVP;

   /* Herstellerabgabepreis 8,2 */
   zifa->A01GEPDM = oifa->A01GEPDM;

   /* Apo EK 8,2 */
   zifa->A01AEPDM = oifa->A01AEPDM;

   /* Apo VK incl MWST 8,2 */
   zifa->A01AVPDM = oifa->A01AVPDM;

   /* MWST Kennzeichen */
   strcpy( zifa->A01MWST, oifa->A01MWST );

   /* Kennz. Arzneimittel */
   strcpy( zifa->A02AM, oifa->A02AM );

   /* Kennz. Medizinprodukt */
   strcpy( zifa->A02MP, oifa->A02MP );

   /* Kennz. Apothekenpflichtig */
   strcpy( zifa->A02APPFL, oifa->A02APPFL );

   /* Kennz. Verschreibungspflichtig */
   strcpy( zifa->A02VSPFL, oifa->A02VSPFL );

   /* Betaeubungsmittel */
   strcpy( zifa->A02BTM, oifa->A02BTM );

   /* Kennz. TFG */
   strcpy( zifa->A02TFG, oifa->A02TFG );

   /* Kennz. Droge/Chemikalie */
   strcpy( zifa->A02DROCH, oifa->A02DROCH );

   /* Kennz. Tier-AM */
   strcpy( zifa->A02TIERAM, oifa->A02TIERAM );

   /* Negativ-Kennzeichen */
   strcpy( zifa->A02NEGLIS, oifa->A02NEGLIS );

   /* Vertriebsstatus */
   strcpy( zifa->A03VTSTAT, oifa->A03VTSTAT );

   /* Kennz. Vertriebsweg Grosshandel */
   strcpy( zifa->A03VWGGH, oifa->A03VWGGH );

   /* Kennz. Vertriebsweg Apotheke */
   strcpy( zifa->A03VWGAPO, oifa->A03VWGAPO );

   /* Kennz. Vertriebsweg Krankenhaus-Apotheke */
   strcpy( zifa->A03VWGKAP, oifa->A03VWGKAP );

   /* Kennz. Vertriebsweg sonstiger Einzelhandel */
   strcpy( zifa->A03VWGSEH, oifa->A03VWGSEH );

   /* Verkehrsfaehigkeits-Status */
   strcpy( zifa->A03VKSTAT, oifa->A03VKSTAT );

   /* PZN Nachfolger */
   zifa->A06PZNNF = oifa->A06PZNNF;
   zifa->A06PZNNF8 = oifa->A06PZNNF8;

  /* Gueltigkeits-Datum TTMMJJ */
   zifa->DATUMGUELTIGAB = oifa->DATUMGUELTIGAB;

   /* Zuzahlung */
   Zuzahlung_Build( zifa, oifa );

   CopyPlausi  ( zifa->NB_PLAUSI );
   PlausiZuzahl( zifa->NB_PLAUSI );

   /* Preise zum Aendern */
   zifa->GROSSO = zifa->A01GEPDM;
   zifa->AEP    = zifa->A01AEPDM;
   zifa->AVP    = zifa->A01AVPDM;

   /* Hilfsmittel zu Verbrauch */
   strcpy( zifa->A02HMZV, oifa->A02HMZV );

   /* Preise zum Aendern */
   zifa->EAVP = zifa->A01UVP;

   /* wird nicht mehr von der IFA gepflegt ab 01.01.2004 verbleibt aber im Satz */
   strcpy( zifa->A02IMPFST,  "  " );
   strcpy( zifa->A02REZEPAM, "  " );
   strcpy( zifa->A02KONTRAZ, "  " );
   strcpy( zifa->A01AMPV,    "  " );

   /* pnam */
   ConvertUmlaute ( ( unsigned char *) oifa->A00PNAM, temp );
   Upper ( ( unsigned char *) temp );

   strncpy( zifa->A00PNAM, temp, L_ZIFAOART_A00PNAM );


    /* lifestyle */
   strcpy( zifa->A02LIFSTYL, oifa->A02LIFSTYL );

   strcpy( zifa->A02AUSNREI,	oifa->A02AUSNREI );
   strcpy( zifa->A02GENER,		oifa->A02GENER );
   strcpy( zifa->A02SDB,		oifa->A02SDB );

   strcpy( zifa->A02NEM,		oifa->A02NEM );
   zifa->A06PZNORIG			=	oifa->A06PZNORIG;
   zifa->A06PZNORIG8		=	oifa->A06PZNORIG8;

   strcpy( zifa->A02LEBENSM, oifa->A02LEBENSM );
   strcpy( zifa->A02DIAET,   oifa->A02DIAET );
   strcpy( zifa->A02ZULREG,   oifa->A02ZULREG );

   strcpy( zifa->A02HOMOEO,   oifa->A02HOMOEO );
   strcpy( zifa->A02ANTHRO,   oifa->A02ANTHRO );
   strcpy( zifa->A02PHYTO,    oifa->A02PHYTO );
   strcpy( zifa->A02BIOZID,   oifa->A02BIOZID );
   strcpy( zifa->A02PSM,      oifa->A02PSM );
   strcpy( zifa->A02TREZEP,   oifa->A02TREZEP );
   strcpy( zifa->A0247AMG,    oifa->A0247AMG );
   
   // zifa->A01ERSTATT = oifa->A01ERSTATT; ab 01.04.2014 nicht mehr geliefert

   zifa->A01AB130A2 = oifa->A01AB130A2;
   strcpy( zifa->A00PPN,    oifa->A00PPN );
   strcpy( zifa->A02VERIFIZ, oifa->A02VERIFIZ );
   strcpy( zifa->A0252B,     oifa->A0252B );
   strcpy( zifa->A02BIOSIEG,    oifa->A02BIOSIEG );
   strcpy( zifa->A02KOSMET,     oifa->A02KOSMET );
   strcpy( zifa->A02STERIL,     oifa->A02STERIL );

   /* RESERVE-Felder werden mit IFA-Version 252 nicht mehr geliefert
   strcpy( zifa->A02RESERV1,     oifa->A02RESERV1 );
   strcpy( zifa->A02RESERV2,     oifa->A02RESERV2 );
   strcpy( zifa->A02RESERV3,     oifa->A02RESERV3 );

   zifa->A01RESERV1 = oifa->A01RESERV1;
   zifa->A01RESERV2 = oifa->A01RESERV2;
   zifa->A01RESERV3 = oifa->A01RESERV3;
   */

   strcpy( zifa->A02ELEKTRO, oifa->A02ELEKTRO );
   strcpy( zifa->A02WIRKSTO, oifa->A02WIRKSTO );

   zifa->A01PPU		= oifa->A01PPU;
   zifa->A01APU783A = oifa->A01APU783A;
   zifa->A01AEPPPU  = oifa->A01AEPPPU;
   zifa->A01AVPPPU	= oifa->A01AVPPPU;
   strcpy( zifa->A02EB130B,     oifa->A02EB130B );
   strcpy( zifa->A02EXPLOS,     oifa->A02EXPLOS );
   strcpy( zifa->A02BIOTECH,    oifa->A02BIOTECH );

   strcpy( zifa->A02STIFEAR,    oifa->A02STIFEAR );
   strcpy( zifa->A02WEEEREG,    oifa->A02WEEEREG );
   strcpy( zifa->A02BATTG,		oifa->A02BATTG );
   strcpy( zifa->A02UNNR,		oifa->A02UNNR );

   strcpy( zifa->A11VERIPFL,	oifa->A11VERIPFL );

   strcpy( zifa->A00UDIDI,      oifa->A00UDIDI );

   zifa->A02ATMP    = oifa->A02ATMP;
   zifa->A02AUSIMPF = oifa->A02AUSIMPF;
   zifa->A02EUNOVEL = oifa->A02EUNOVEL;
   zifa->A02SWUNDB  = oifa->A02SWUNDB;
   strcpy(zifa->A02BATTREG,     oifa->A02BATTREG);
   strcpy(zifa->A00OEVNR,       oifa->A00OEVNR);
   strcpy(zifa->A00ZINNR,       oifa->A00ZINNR);
   strcpy(zifa->A02AMNOG,       oifa->A02AMNOG);
   strcpy(zifa->A02BEDZUL,      oifa->A02BEDZUL);
   strcpy(zifa->A02ORDRUG,      oifa->A02ORDRUG);
   strcpy(zifa->A02PRSTRMO,     oifa->A02PRSTRMO);
   strcpy(zifa->A02ZULAUSN,     oifa->A02ZULAUSN);

   // IFA Version 20244
   strcpy(zifa->A02AMDARKI,     oifa->A02AMDARKI);
   strcpy(zifa->A02AMAUFFB,     oifa->A02AMAUFFB);
   strcpy(zifa->A02AMBEKI,      oifa->A02AMBEKI);
   strcpy(zifa->A02AMVEKRW,     oifa->A02AMVEKRW);
   zifa->A01DAPU78  = oifa->A01DAPU78;
   zifa->A02D130A18 = oifa->A02D130A18;

   // IFA Version 20248
   strcpy(zifa->A02MEDCG,       oifa->A02MEDCG);
   strcpy(zifa->A05LGTMPB,      oifa->A05LGTMPB);

   // IFA Version 20252
   strcpy(zifa->A01B130B1C,     oifa->A01B130B1C);
   zifa->A01DAT78   = oifa->A01DAT78;
   zifa->A01RAB130A = oifa->A01RAB130A;
   zifa->A01ZUZAH61 = oifa->A01ZUZAH61;

   // keine Übernahme nach zifaart: oifa->A02BOPST, A11GDAT, A02MP31, A02VERB31, A02CMR, A11VERIHOC, A02MPKLASS, A02INVITRO
   
   return 0;
}


