/* ---------------------------------------------------------------------- *
 *                        C O P Y D I S C O U N T S . C                   *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Rabatte kopieren (BG-178)                                    *
 * ---------------------------------------------------------------------- *
 * Autor  :  Hoerath                                                      *
 * Anfang :  29.11.2011                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hdatum/phodate.h"
#include "hdatum/phozeit.h"
#include "libscsvoodoo/libscsvoodoo.h"

#include  "wdbups/wpp_prot.h"
#include  "wdbups/wpp_dbas.h"
#include <math.h>

#include <cdiscount.h>
#include <zpznpflege.h>
#include <zgrppflege.h>

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void CopyDiscountsUsage( char *buf )
{
   strcat( buf, "- zpmasaen 11 Database User StopExistingDiscounts_Flag\n" );
   strcat( buf, "  Article_Base   DiscountGrp_Base   Manufacturer_Base   ArtCategory_Base   Customer_Base   PharmacyGroup_Base\n" );
   strcat( buf, "  Article_Target DiscountGrp_Target Manufacturer_Target ArtCategory_Target Customer_Target PharmacyGroup_Target\n" );
}


/* ----------------- Funktion ------------------------ */

static int fd_CDiscount			= -1;
static int fd_CDiscount_Store	= -1;
static int fd_zpznpflege		= -1;
static int fd_zgrppflege		= -1;

static long		tagesdatum			= -1;
static int		stopexistdiscflag	= 0;

static long		articleNo_Base		= 0;
static long		discountGrpNo_Base  = 0;
static long		manufacturerNo_Base	= 0;
static long		artCategoryNo_Base  = 0;
static long		customerNo_Base		= 0;
static char		pharmacyGroupId_Base[4] = "";

static long		articleNo_Target		= 0;
static long		discountGrpNo_Target	= 0;
static long		manufacturerNo_Target	= 0;
static long		artCategoryNo_Target	= 0;
static long		customerNo_Target		= 0;
static char		pharmacyGroupId_Target[4] = "";

static struct CDISCOUNT		BufDisc;
static struct CDISCOUNT		BufDiscOld;
static struct ZPZNPFLEGE	BufPznPflege;
static struct ZGRPPFLEGE	BufGrpPflege;

/* ---------------------------------------- */
static void Init( )
{
	fd_CDiscount_Store	= -1;
	fd_zpznpflege		= -1;
	fd_zgrppflege		= -1;
}

/* ---------------------------------------- */
static void Free( )
{
    if ( fd_CDiscount_Store >= 0 )
        CloseOneBufferDesc( fd_CDiscount_Store );
    fd_CDiscount_Store = -1;

	if ( fd_zpznpflege >= 0 )
        CloseOneBufferDesc( fd_zpznpflege );
    fd_zpznpflege = -1;

	if ( fd_zgrppflege >= 0 )
        CloseOneBufferDesc( fd_zgrppflege );
    fd_zgrppflege = -1;
}

/* ---------------------------------------- */
int GetBufferDesc_CDiscount( char *cErrmld )
{
   char *tabelle = "cdiscount";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_CDiscount_Store >= 0 ) 
	   return 0;

#ifdef WIN32
   // for debugging on windows, because key of cdiscount > 100 signs
   s = OpenBufferDesc	( &fd_CDiscount_Store, tabelle,
                           NULL, NULL, V_OHNE, errmld );
#else
   s = OpenBufferDesc	( &fd_CDiscount_Store, tabelle,
                           NULL, NULL, V_PROTO_VERTEIL, errmld );
#endif

   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_CDiscount = -1;
     return -1;
   }
   return 0;
}

/* ---------------------------------------- */
int GetBufferDesc_Zpznpflege( char *cErrmld )
{
   char *tabelle = "zpznpflege";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zpznpflege >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zpznpflege, tabelle,
                           NULL, NULL, V_OHNE, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zpznpflege = -1;
     return -1;
   }
   return 0;
}


/* ---------------------------------------- */
int GetBufferDesc_Zgrppflege( char *cErrmld )
{
   char *tabelle = "zgrppflege";
   long s;
   char errmld[100];

   *cErrmld = '\0';
   if ( fd_zgrppflege >= 0 ) 
	   return 0;
   
   s = OpenBufferDesc	( &fd_zgrppflege, tabelle,
                           NULL, NULL, V_OHNE, errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );
     fd_zgrppflege = -1;
     return -1;
   }
   return 0;
}

/*----------------------------------------------------------------------------*/
static long StoreRecord_Zpznpflege( char *buf )
{
	long lStatus;

	char PrimekeyCond[100];
	
	BufPznPflege.ARTIKEL_NR	= BufDisc.ARTICLENO;
	BufPznPflege.DATUM		= tagesdatum;

	sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld and DEZAP_SA = '28'",
									BufPznPflege.ARTIKEL_NR, BufPznPflege.DATUM );

    lStatus = FdReadRecord( fd_zpznpflege, PrimekeyCond,
				  			  &BufPznPflege, buf );

	if ( lStatus == 100 )
	{
		BufPznPflege.ARTIKEL_NR = BufDisc.ARTICLENO;
		BufPznPflege.DATUM		= tagesdatum;
		strcpy (BufPznPflege.DEZAP_SA, "28");

		lStatus = FdDelayInsertRecord( fd_zpznpflege, &BufPznPflege, PrimekeyCond, buf );
	}

	return lStatus;
}

/*----------------------------------------------------------------------------*/
static long StoreRecord_Zgrppflege( char *buf )
{
	long lStatus;

	char PrimekeyCond[100];

	// unterschiedliche Satzarten je nach Schlüsselkriterium
	if (BufDisc.DISCOUNTGRPNO > 0)
	{
		sprintf (BufGrpPflege.KEY_GRUPPE, "%5.5d", BufDisc.DISCOUNTGRPNO);
		strcpy (BufGrpPflege.DEZAP_SA, "2A");
	} 
	else if (BufDisc.MANUFACTURERNO > 0)
	{
		sprintf (BufGrpPflege.KEY_GRUPPE, "%5.5d", BufDisc.MANUFACTURERNO);
		strcpy (BufGrpPflege.DEZAP_SA, "2B");
	} 
	else if (BufDisc.ARTCATEGORYNO > 0)
	{
		sprintf (BufGrpPflege.KEY_GRUPPE, "%5.5d", BufDisc.ARTCATEGORYNO);
		strcpy (BufGrpPflege.DEZAP_SA, "2C");
	} 
	else // alle Kriterien = 0 (ist zulässig in Bulgarien)
	{
		sprintf (BufGrpPflege.KEY_GRUPPE, "00000");
		strcpy (BufGrpPflege.DEZAP_SA, "2D");
	} 

	BufGrpPflege.DATUM = tagesdatum;

	sprintf( PrimekeyCond, "KEY_GRUPPE='%s' and DATUM=%ld and DEZAP_SA = '%s'",
			 BufGrpPflege.KEY_GRUPPE, BufGrpPflege.DATUM, BufGrpPflege.DEZAP_SA );
	
	lStatus = FdReadRecord( fd_zgrppflege, PrimekeyCond,
				  			  &BufGrpPflege, buf );

	if ( lStatus == 100 )
	{
		if (BufDisc.DISCOUNTGRPNO > 0)
		{
			sprintf (BufGrpPflege.KEY_GRUPPE, "%5.5d", BufDisc.DISCOUNTGRPNO);
			strcpy (BufGrpPflege.DEZAP_SA, "2A");
		} 
		else if (BufDisc.MANUFACTURERNO > 0)
		{
			sprintf (BufGrpPflege.KEY_GRUPPE, "%5.5d", BufDisc.MANUFACTURERNO);
			strcpy (BufGrpPflege.DEZAP_SA, "2B");
		} 
		else if (BufDisc.ARTCATEGORYNO > 0)
		{
			sprintf (BufGrpPflege.KEY_GRUPPE, "%5.5d", BufDisc.ARTCATEGORYNO);
			strcpy (BufGrpPflege.DEZAP_SA, "2C");
		}

		BufGrpPflege.DATUM = tagesdatum;

		lStatus = FdDelayInsertRecord( fd_zgrppflege, &BufGrpPflege, PrimekeyCond, buf );
	}

	return lStatus;
}

/* ---------------------------------------- */
static long InsertRecord_CDiscount( char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[1000];
	
	sprintf( PrimeKeyCond, "ARTICLENO=%ld and PHARMACYGROUPID='%s' and CUSTOMERNO=%ld and BASEQTY=%ld", 
			 BufDisc.ARTICLENO, BufDisc.PHARMACYGROUPID, BufDisc.CUSTOMERNO, BufDisc.BASEQTY);

	sprintf( PrimeKeyCond, "%s and DATEFROM=%ld and DATETO=%ld and GRPDISCOUNTTYP=%d",
			 PrimeKeyCond, BufDisc.DATEFROM, BufDisc.DATETO, BufDisc.GRPDISCOUNTTYP);

	sprintf( PrimeKeyCond, "%s and DISCOUNTTYPE=%d and DISCOUNTSPEC=%d and DISCOUNTGRPNO=%ld ",
			 PrimeKeyCond, BufDisc.DISCOUNTTYPE, BufDisc.DISCOUNTSPEC, BufDisc.DISCOUNTGRPNO); 

	sprintf( PrimeKeyCond, "%s and BASE_VALUE=%f and BASE_MULT_STD_QTY=%d ",
			 PrimeKeyCond, BufDisc.BASE_VALUE, BufDisc.BASE_MULT_STD_QTY); 

	sprintf( PrimeKeyCond, "%s and MANUFACTURERNO=%ld and ARTCATEGORYNO=%ld And PAYMENTTARGETNO=%d ",
			 PrimeKeyCond, BufDisc.MANUFACTURERNO, BufDisc.ARTCATEGORYNO, BufDisc.PAYMENTTARGETNO); 

	lStatus = FdDelayInsertRecord( fd_CDiscount_Store, &BufDisc, PrimeKeyCond, buf);
	
	if ( lStatus == 0 )
	{
		if (BufDisc.ARTICLENO > 0)
			return StoreRecord_Zpznpflege( buf );
		else
			return StoreRecord_Zgrppflege( buf );
	}
	
	return lStatus;
}

/* ---------------------------------------- */
static long UpdateRecord_CDiscount( char *buf )
{
	long lStatus;
	
	char PrimeKeyCond[1000];
	
	sprintf( PrimeKeyCond, "ARTICLENO=%ld and PHARMACYGROUPID='%s' and CUSTOMERNO=%ld and BASEQTY=%ld", 
			 BufDisc.ARTICLENO, BufDisc.PHARMACYGROUPID, BufDisc.CUSTOMERNO, BufDisc.BASEQTY);

	sprintf( PrimeKeyCond, "%s and DATEFROM=%ld and DATETO=%ld and GRPDISCOUNTTYP=%d",
			 PrimeKeyCond, BufDiscOld.DATEFROM, BufDiscOld.DATETO, BufDisc.GRPDISCOUNTTYP);

	sprintf( PrimeKeyCond, "%s and DISCOUNTTYPE=%d and DISCOUNTSPEC=%d and DISCOUNTGRPNO=%ld ",
			 PrimeKeyCond, BufDisc.DISCOUNTTYPE, BufDisc.DISCOUNTSPEC, BufDisc.DISCOUNTGRPNO); 

	sprintf( PrimeKeyCond, "%s and BASE_VALUE=%f and BASE_MULT_STD_QTY=%d ",
			 PrimeKeyCond, BufDisc.BASE_VALUE, BufDisc.BASE_MULT_STD_QTY); 

	sprintf( PrimeKeyCond, "%s and MANUFACTURERNO=%ld and ARTCATEGORYNO=%ld And PAYMENTTARGETNO=%d ",
			 PrimeKeyCond, BufDisc.MANUFACTURERNO, BufDisc.ARTCATEGORYNO, BufDisc.PAYMENTTARGETNO); 

	lStatus = FdDelayUpdateRecord( fd_CDiscount_Store, &BufDisc, &BufDiscOld, PrimeKeyCond, buf);

	if ( lStatus == 0 )
	{
		if (BufDisc.ARTICLENO > 0)
			return StoreRecord_Zpznpflege( buf );
		else
			return StoreRecord_Zgrppflege( buf );
	}
	
	return lStatus;
}

/* ---------------------------------------- */
static long CopyAndStore( char *buf )
{
	long s;

//----
	if (articleNo_Target > 0)
		BufDisc.ARTICLENO = articleNo_Target;
	else if (articleNo_Base > 0)
		BufDisc.ARTICLENO = 0;

	if (discountGrpNo_Target > 0)
		BufDisc.DISCOUNTGRPNO = discountGrpNo_Target;
	else if (discountGrpNo_Base > 0)
		BufDisc.DISCOUNTGRPNO = 0;

	if (strcmp( pharmacyGroupId_Target, "000" ) != 0)
		strcpy(BufDisc.PHARMACYGROUPID, pharmacyGroupId_Target);
	else if (strcmp( pharmacyGroupId_Base, "000" ) != 0)
		strcpy(BufDisc.PHARMACYGROUPID, "000");

	if (customerNo_Target > 0)
		BufDisc.CUSTOMERNO = customerNo_Target;
	else if (customerNo_Base > 0)
		BufDisc.CUSTOMERNO = 0;

	if (artCategoryNo_Target > 0)
		BufDisc.ARTCATEGORYNO = artCategoryNo_Target;
	else if (artCategoryNo_Base > 0)
		BufDisc.ARTCATEGORYNO = 0;

	if (manufacturerNo_Target > 0)
		BufDisc.MANUFACTURERNO = manufacturerNo_Target;
	else if (manufacturerNo_Base > 0)
		BufDisc.MANUFACTURERNO = 0;
//----

	if (BufDisc.DATEFROM <= tagesdatum)
		BufDisc.DATEFROM = AddDayToPhoDate( tagesdatum, 1 );

// ausgeschlossene Einkaufsgruppe darf nur gesetzt sein, wenn Einkaufsgruppe = 000
	if (atoi(BufDisc.PHARMACYGROUPID) > 0 &&
		(atoi(BufDisc.PHARMGRPEXCLUDED) > 0 ||
		 atoi(BufDisc.PHARMGRPEXCL_2)	> 0 ||
	     atoi(BufDisc.PHARMGRPEXCL_3)	> 0))
		return -99;

// Eingabe von Einkaufsgruppen nicht zulässig, wenn IDF angegeben wurde
	if (BufDisc.CUSTOMERNO > 0 &&
		(	(strcmp( BufDisc.PHARMACYGROUPID, "000") != 0	&& strcmp( BufDisc.PHARMACYGROUPID, "   ") != 0)	||
			(strcmp( BufDisc.PHARMGRPEXCLUDED, "000") != 0	&& strcmp( BufDisc.PHARMGRPEXCLUDED, "   ") != 0)	||
			(strcmp( BufDisc.PHARMGRPEXCL_2, "000") != 0	&& strcmp( BufDisc.PHARMGRPEXCL_2, "   ") != 0)	||
			(strcmp( BufDisc.PHARMGRPEXCL_3, "000") != 0	&& strcmp( BufDisc.PHARMGRPEXCL_3, "   ") != 0)	)
		)
		return -99;
	
	s = InsertRecord_CDiscount ( buf );
	
	return s;
}

/* ---------------------------------------- */
static long StopAndStore( char *buf )
{
	long s;

	if (BufDisc.DATEFROM > tagesdatum)
		BufDisc.DATEFROM = tagesdatum;

	BufDisc.DATETO = tagesdatum;

	s = UpdateRecord_CDiscount ( buf );
	
	return s;
}

/* ---------------------------------------- */
static long Copy( char *buf )
{
	long s;
		
	s = GetBufferDesc_Zgrppflege	( buf );
	if ( s != 0 )
		return s;

	s = GetBufferDesc_Zpznpflege	( buf );
	if ( s != 0 )
		return s;
	
	s = GetBufferDesc_CDiscount		( buf );
	if ( s != 0 )
		return s;
	
	if ( s == 0 )
	{
		s = CopyAndStore ( buf );
	}
	
	return s;
}

/* ---------------------------------------- */
static long Stop( char *buf )
{
	long s;
		
	s = GetBufferDesc_Zgrppflege	( buf );
	if ( s != 0 )
		return s;

	s = GetBufferDesc_Zpznpflege	( buf );
	if ( s != 0 )
		return s;
	
	s = GetBufferDesc_CDiscount		( buf );
	if ( s != 0 )
		return s;
	
	if ( s == 0 )
	{
		s = StopAndStore ( buf );
	}
	
	return s;
}

/* ---------------------------------------- */
static long StopDiscount( char *buf )
{
   long s;

   s = SqlBeginWork();
   
   if ( s != 0 )
   {
     strcpy( buf, DynErrmld() );
     return -1;
   }

   s = Stop( buf );
   
   if ( s == 0 )
	   s = FdTransactWithoutWork( buf );

   if ( s == 0 )
   {
      s = SqlCommitWork();
      
	  if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork();


   return s;
}

/* ---------------------------------------- */
static long CopyDiscount( char *buf )
{
   long s;

 
	s = SqlBeginWork();
   
   if ( s != 0 )
   {
     strcpy( buf, DynErrmld() );
     return -1;
   }


   s = Copy( buf );
   
   if ( s == 0 )
	   s = FdTransactWithoutWork( buf );

   if ( s == 0 )
   {
      s = SqlCommitWork();
      
	  if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork();



   return s;
}

/* ---------------------------------------- */
static long StopExistingTargetDiscounts( char *buf )
{
   long s;
   char z_buf[1000];
   long anz = 0;
   long anz_duplicate = 0;

   sprintf( z_buf, "select %s from CDISCOUNT where DATETO > %ld ",
			 PROJECTION_CDISCOUNT, tagesdatum);

   if (articleNo_Target > 0)
	sprintf( z_buf, "%s and ARTICLENO = %ld ",
			 z_buf, articleNo_Target);

   if (discountGrpNo_Target > 0)
	sprintf( z_buf, "%s and DISCOUNTGRPNO = %ld ",
			 z_buf, discountGrpNo_Target);

   if (manufacturerNo_Target > 0)
	sprintf( z_buf, "%s and MANUFACTURERNO = %ld ",
			 z_buf, manufacturerNo_Target);

   if (artCategoryNo_Target > 0)
	sprintf( z_buf, "%s and ARTCATEGORYNO = %ld ",
			 z_buf, artCategoryNo_Target);

   if (customerNo_Target > 0)
	sprintf( z_buf, "%s and CUSTOMERNO = %ld ",
			 z_buf, customerNo_Target);

   if (strcmp(pharmacyGroupId_Target, "000") != 0)
	sprintf( z_buf, "%s and PHARMACYGROUPID = '%s' ",
			 z_buf, pharmacyGroupId_Target);

   s = SqlOpenCsWh( &fd_CDiscount, z_buf );

   if ( s != 0 )
   {
     strcat( buf, "CDISCOUNT\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd_CDiscount, 1, &BufDisc, NULL );
   
   if ( s == 100 )
   {
     strcat( buf, "Keine Rabatte mit den angegebenen Ziel- Kriterien vorhanden, die beendet werden koennten.\n" );
     SqlCloseCs( fd_CDiscount );
     return 0;
   }
   else if ( s != 0 )
   {
     strcat( buf, "CDISCOUNT\n" );
     strcat( buf, DynErrmld() );
     SqlCloseCs( fd_CDiscount );
     return s;
   }

   Init( );
   
   while ( s == 0 )
   {
	  BufDiscOld = BufDisc;
	  
	  s = StopDiscount( z_buf );

      if ( s == 0 || (s == 1 && strstr(z_buf, "-346" ) != NULL))
      {
         if (s == 0)
			 ++anz;
		 else
			 ++anz_duplicate;

         s = SqlFetch( fd_CDiscount, 1, &BufDisc, NULL );
         
		 if ( s != 0 && s != 100)
         {
           strcat( buf, "CDISCOUNT\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   Free( );

   SqlCloseCs( fd_CDiscount );

   sprintf( z_buf, "\nEs wurden %ld Rabatte beendet.\n%ld Rabatte wurden aus Konsistenzgruenden nicht beendet.\n", anz, anz_duplicate );

   if ( s == 100 )
   {
      s = 0;
      strcat( buf, "Beenden erfolgreich. " );
   }
   
   strcat( buf, z_buf );
   return s;

}

/* ---------------------------------------- */
static long CopyAllDiscounts( char *buf )
{
   long s;
   char z_buf[1000];
   long anz = 0;
   long anz_check_failed = 0;
   long anz_duplicate = 0;
    
   sprintf( z_buf, "select %s from CDISCOUNT where DATETO > %ld ",
			 PROJECTION_CDISCOUNT, tagesdatum);

   if (articleNo_Base > 0)
	sprintf( z_buf, "%s and ARTICLENO = %ld ",
			 z_buf, articleNo_Base);

   if (discountGrpNo_Base > 0)
	sprintf( z_buf, "%s and DISCOUNTGRPNO = %ld ",
			 z_buf, discountGrpNo_Base);

   if (manufacturerNo_Base > 0)
	sprintf( z_buf, "%s and MANUFACTURERNO = %ld ",
			 z_buf, manufacturerNo_Base);

   if (artCategoryNo_Base > 0)
	sprintf( z_buf, "%s and ARTCATEGORYNO = %ld ",
			 z_buf, artCategoryNo_Base);

   if (customerNo_Base > 0)
	sprintf( z_buf, "%s and CUSTOMERNO = %ld ",
			 z_buf, customerNo_Base);

   if (strcmp(pharmacyGroupId_Base, "000") != 0)
	sprintf( z_buf, "%s and PHARMACYGROUPID = '%s' ",
			 z_buf, pharmacyGroupId_Base);

  
   s = SqlOpenCsWh( &fd_CDiscount, z_buf );

   if ( s != 0 )
   {
     strcat( buf, "CDISCOUNT\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd_CDiscount, 1, &BufDisc, NULL );
   
   if ( s == 100 )
   {
     strcat( buf, "Keine Rabatte mit den angegebenen Basis- Kriterien vorhanden, von denen kopiert werden koennte." );
     SqlCloseCs( fd_CDiscount );
     return 0;
   }
   else if ( s != 0 )
   {
     strcat( buf, "CDISCOUNT\n" );
     strcat( buf, DynErrmld() );
     SqlCloseCs( fd_CDiscount );
     return s;
   }

   Init( );
   
   while ( s == 0 )
   {
	  s = CopyDiscount( z_buf );

      if ( s == 0 || s == -99 || (s == 1 && strstr(z_buf, "-239" ) != NULL))
      {
         if ( s == 0 )
			 ++anz;
		 else if ( s == -99 )
			++anz_check_failed;
		 else
			++anz_duplicate;

         s = SqlFetch( fd_CDiscount, 1, &BufDisc, NULL );
         
		 if ( s != 0 && s != 100)
         {
           strcat( buf, "CDISCOUNT\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   Free( );

   SqlCloseCs( fd_CDiscount );

   sprintf( z_buf, "\nEs wurden %ld Rabatte kopiert.\n%ld Rabatte wurden aus Konsistenzgruenden nicht kopiert.", anz, anz_check_failed + anz_duplicate );

   if ( s == 100 )
   {
      s = 0;
      strcat( buf, "Kopieren erfolgreich. " );
   }
   
   strcat( buf, z_buf );
   return s;
}

/* ---------------------------------------- */
long CopyDiscountsLoop ( char *db, char *user, char *stopdiscflag, 
						char *artBase,   char *discgrpBase,   char *manBase,   char *catBase,   char *custBase,   char *pharmgrpBase, 
						char *artTarget, char *discgrpTarget, char *manTarget, char *catTarget, char *custTarget, char *pharmgrpTarget, 
						char *buf )
{
	long s;
	char errmld[10];

	tagesdatum	= GetPhoDate();

	stopexistdiscflag	= atoi (stopdiscflag);

	articleNo_Base		= atol (artBase);
	discountGrpNo_Base  = atol (discgrpBase);
	manufacturerNo_Base	= atol (manBase);
	artCategoryNo_Base  = atol (catBase);
	customerNo_Base		= atol (custBase);
	strcpy(pharmacyGroupId_Base, pharmgrpBase);

	articleNo_Target		= atol (artTarget);
	discountGrpNo_Target	= atol (discgrpTarget);
	manufacturerNo_Target	= atol (manTarget);
	artCategoryNo_Target	= atol (catTarget);
	customerNo_Target		= atol (custTarget);
	strcpy(pharmacyGroupId_Target, pharmgrpTarget);

	s = OpenBase( db, buf );
   
	if ( s == 0 )
	{
		s = OpenPflege( user, buf );
     
		if ( s == 0 )
		{
			if (1 == stopexistdiscflag)
				s = StopExistingTargetDiscounts( buf );

			if ( s == 0 )
				s = CopyAllDiscounts( buf );

			ClosePflege( errmld );
		}
     
		CloseBase( );
	}

	return s;
}
