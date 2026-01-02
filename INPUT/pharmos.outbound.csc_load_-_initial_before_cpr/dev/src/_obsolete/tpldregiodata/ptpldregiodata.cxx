
/*****************************************************************************/
/*                                                                           */
/*   source     : ptpldregiodata.cxx                                         */
/*   Author     : A. Schmidt-Rehschuh (644)                                  */
/*   made       : 08.02.99                                                   */
/*   language   : C/Esql                                                     */
/*                                                                           */
/*   declaration: select data from artikel, artfil, besposi, beskopf         */
/*                                                                           */
/*****************************************************************************/

/*** Include *****************************************************************/

 #include <stdio.h>
 #include "libtpld/dadedb.h"
 #include "regiodata.h"

/*** Declaration (private) ***************************************************/

 static bool pCheckResult( tError *dbError, char *spText );
 static bool pGetUpdRow( tError *dbError );
 static bool pGetDelRow( tError *dbError );
 static bool pGetMinStockRow( tError *dbError );


/*** DBStartDataWarehouseData ************************************************/

void fmeld (regiodataS *a, char *text)
{
   printf ( "<%ld> - <%s> - <%d> <%ld> <%ld> <%ld> <%ld> <%ld>"\
            " <%ld> <%ld> <%ld> <%d> <%s> <%s> <%ld> <%ld> <%f>"\
            " <%ld>  <%s> <%ld> <%ld> <%f> <%ld>\n"
          , sqlca.sqlcode
          , text
          , a->sBranchNo 
          , a->ARTIKEL_NR
          , a->BESLA_NR
          , a->DATUM_AKTIV
          , a->DATUM_PASSIV
          , a->DATUM_LIEFERBAR
          , a->DATUM_N_LIEFERBAR
          , a->BESTAND
          , a->NATRASTAFFELNR
          , a->LAGERBEREICHNR
          , a->STATIONNR
          , a->LAGERFACHNR
          , a->WOCHENNACHFRAGE
          , a->UMSATZ_LFD_JAHR
          , a->DURCHSCHNITTPREIS
          , a->UMSATZ_LFD_MONAT
          , a->AUTOM_NR
          , a->ARTIKELAKTIV
          , a->KLASSE_FAKTOR
          , a->KLASSE_PARAM
          , a->BARRABATT
          , a->OBM_MENGE
          );
                                   
   fflush(stdout);
}

 extern bool DBStartBrowse( tError *dbError, const short sBranchNo )
 {
   exec sql begin declare section;
   char szBuf[1024];
   const short DBsBranchNo = sBranchNo;
   exec sql end declare section;

   strcpy( szBuf, "select artikelf.filialnr, artikelf.artikel_nr " );            
   strcat( szBuf, "from artikelf " );                  
   strcat( szBuf, "where filialnr=? " );            
   strcat( szBuf, "for update " );                     
  
   exec sql prepare p_SelArt from :szBuf;
   if ( !pCheckResult( dbError, "prepare p_SelArt" ) )
	  return FALSE;

   exec sql declare CSelArt cursor with hold for p_SelArt;
   exec sql free p_SelArt;
   if ( !pCheckResult( dbError, "free p_SelArt" ) )
	  return FALSE;
   exec sql open CSelArt using :DBsBranchNo;
   if ( !pCheckResult( dbError, "open CSelArt" ) )
	  return FALSE;

   strcpy( szBuf, "update artikelf set " );
   strcat( szBuf, "internesteuerung=0," );                            
   strcat( szBuf, "offene_bestmenge=0 " );
   strcat( szBuf, "where current of CSelArt" );
   exec sql prepare p_UpdIni from :szBuf;
   if ( !pCheckResult( dbError, "prepare p_UpdIni" ) )
	  return FALSE;
   
   strcpy( szBuf, "select artikelf.filialnr, artikelf.artikel_nr " );            
   strcat( szBuf, "from artikelf " );                  
   strcat( szBuf, "where filialnr=? " );            
   strcat( szBuf, "and internesteuerung = 0 " );            
   strcat( szBuf, "for update " );                     
  
   exec sql prepare p_SelDelArt from :szBuf;
   if ( !pCheckResult( dbError, "prepare p_SelDelArt" ) )
	  return FALSE;

   exec sql declare CSelDelArt cursor with hold for p_SelDelArt;
   exec sql free p_SelDelArt;
   if ( !pCheckResult( dbError, "free p_SelDelArt" ) )
	  return FALSE;
   exec sql open CSelDelArt using :DBsBranchNo;
   if ( !pCheckResult( dbError, "open CSelDelArt" ) )
	  return FALSE;

   strcpy( szBuf, "select artikelf.filialnr, artikelf.artikel_nr " );            
   strcat( szBuf, "from artikelf " );                  
   strcat( szBuf, "where filialnr=? " );            
   strcat( szBuf, "and bestand_min > 0 " );            
   strcat( szBuf, "for update " );                     
  
   exec sql prepare p_SelMinStockArt from :szBuf;
   if ( !pCheckResult( dbError, "prepare p_SelMinStockArt" ) )
	  return FALSE;

   exec sql declare CSelMinStockArt cursor with hold for p_SelMinStockArt;
   exec sql free p_SelMinStockArt;
   if ( !pCheckResult( dbError, "free p_SelMinStockArt" ) )
	  return FALSE;
   exec sql open CSelMinStockArt using :DBsBranchNo;
   if ( !pCheckResult( dbError, "open CSelMinstockArt" ) )
	  return FALSE;

   strcpy( szBuf, "delete from artikelf " );
   strcat( szBuf, "where current of CSelDelArt" );
   exec sql prepare p_DelIni from :szBuf;
   if ( !pCheckResult( dbError, "prepare p_DelIni" ) )
	  return FALSE;
   
   strcpy( szBuf, "update artikelf set artikelaktiv=\"2\" " );
   strcat( szBuf, "where current of CSelDelArt" );
   exec sql prepare p_UpdDeactiveIni from :szBuf;
   if ( !pCheckResult( dbError, "prepare p_DelIni" ) )
	  return FALSE;

   strcpy( szBuf, "update artikelf set menge_austauschbar= " );
   strcat( szBuf, "bestand - bestand_min " );
   strcat( szBuf, "where current of CSelMinStockArt" );
   exec sql prepare p_UpdMinStockIni from :szBuf;
   if ( !pCheckResult( dbError, "prepare p_MinStockIni" ) )
	  return FALSE;

   strcpy( szBuf, "select " );
   strcat( szBuf, ARTIKELF_PLISTE );
   strcat( szBuf, " from artikelf where filialnr=? and artikel_nr=? " );
   strcat( szBuf, "for update ");
   exec sql prepare pSelUni from :szBuf;
   if ( !pCheckResult( dbError, "prepare p_SelUni" ) )
	  return FALSE;

   exec sql declare CUpdUni cursor with hold for pSelUni;
   exec sql free pSelUni;
   if ( !pCheckResult( dbError, "free p_SelUni" ) )
	  return FALSE;

   strcpy( szBuf, "update artikelf set " );
   strcat( szBuf, ARTIKELF_UPDLISTE );
   strcat( szBuf, " where current of CUpdUni " );
   exec sql prepare p_UpdArt from :szBuf;
   if ( !pCheckResult( dbError, "prepare p_UpdArt" ) )
	  return FALSE;

   strcpy( szBuf, "insert into artikelf (" );
   strcat( szBuf, ARTIKELF_PLISTE );
   strcat( szBuf, ") values (" );
   strcat( szBuf, "?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)" );
   exec sql prepare p_InsArt from :szBuf;
   return (bool)pCheckResult( dbError, "prepare p_InsArt" );
 }

/*** DBEndDataWarehouseData ***************************************************/

 extern bool DBEndBrowse( tError *dbError )
 {
   exec sql close CSelArt;
   exec sql free p_UpdIni;
   exec sql free p_DelIni;
   exec sql free p_MinStockIni;
   exec sql free p_UpdDeactiveIni;
   exec sql free p_UpdMinStockIni;
   exec sql free p_SelUni;
   exec sql free p_UpdArt;
   exec sql free p_InsArt;
   return (bool)pCheckResult( dbError, "free p_InsArt" );
 }

/*** DBInitialize *************************************************************/
 
 extern bool DBInitialize( tError *dbError )
 {
   const int iTrans = 50;
   long  lCount = 0;
   char *fun = "DBInitialize";

   if ( Begin( fun, dbError ) != IS_OK )
	  return FALSE;

   while ( pGetUpdRow( dbError ) )
   {
	  exec sql execute p_UpdIni;
      if ( !pCheckResult( dbError, "execute p_UpdIni" ) )
	  {
		 Rollback( fun, dbError ); 
	     return FALSE;
	  }
	  if ( ++lCount % iTrans == 0 )
	  {
         if ( Commit( fun, dbError ) != IS_OK )
	        return FALSE;
         if ( Begin( fun, dbError ) != IS_OK )
	        return FALSE;
	  }
   }
   return (bool)(Commit( fun, dbError ) == IS_OK ? TRUE : FALSE);
 }

/*** DBPostprocessing *********************************************************/
 
 extern bool DBPostprocessing( long *lCount, tError *dbError )
 {
   const int iTrans = 50;
   char *fun = "DBPostprocessing";
   *lCount = 0;

   if ( Begin( fun, dbError ) != IS_OK )
	  return FALSE;

   while ( pGetDelRow( dbError ) )
   {
	  exec sql execute p_UpdDeactiveIni;
      if ( !pCheckResult( dbError, "execute p_UpdDeactiveIni" ) )
	  {
		 Rollback( fun, dbError ); 
	     return FALSE;
	  }
	  if ( ++(*lCount) % iTrans == 0 )
	  {
         if ( Commit( fun, dbError ) != IS_OK )
	        return FALSE;
         if ( Begin( fun, dbError ) != IS_OK )
	        return FALSE;
	  }
   }
   return (bool)(Commit( fun, dbError ) == IS_OK ? TRUE : FALSE);
 }

/*** DBPostprocessing *********************************************************/
 
 extern bool DBMinStockUpd( long *lCount, tError *dbError )
 {
   const int iTrans = 50;
   char *fun = "DBMinStockUpd";
   *lCount = 0;

   if ( Begin( fun, dbError ) != IS_OK )
	  return FALSE;

   while ( pGetMinStockRow( dbError ) )
   {
	  exec sql execute p_UpdMinStockIni;
      if ( !pCheckResult( dbError, "execute p_UpdMinStockIni" ) )
	  {
		 Rollback( fun, dbError ); 
	     return FALSE;
	  }
	  if ( ++(*lCount) % iTrans == 0 )
	  {
         if ( Commit( fun, dbError ) != IS_OK )
	        return FALSE;
         if ( Begin( fun, dbError ) != IS_OK )
	        return FALSE;
	  }
   }

   return (bool)(Commit( fun, dbError ) == IS_OK ? TRUE : FALSE);
 }
/*** DBGetNextRow *************************************************************/

 extern bool DBGetNextRow( regiodataS *a, tError *dbError )
 {
   exec sql begin declare section;
   regiodataS *d;
   exec sql end declare section;

   d = a;
   exec sql open CUpdUni using :d->sBranchNo, :d->ARTIKEL_NR;
   if ( !pCheckResult( dbError, "open CUpdUni" ) )
	  return FALSE;
   exec sql fetch CUpdUni;      
   return (bool)pCheckResult( dbError, "fetch CUpdUni" );
 }

/*** DBPutData ****************************************************************/

 extern bool DBPutData( regiodataS *a, tError *dbError )
 {
   exec sql begin declare section;
   regiodataS *d;
   const int iIsNew = 1;
   exec sql end declare section;

   d = a;
   exec sql execute p_InsArt using ARTIKELF_ZEIGER(d), :iIsNew;

   if (sqlca.sqlcode != 0)
   {                                     
      fmeld (a, "Insert");
   }

   return (bool)pCheckResult( dbError, "execute p_InsArt" );
 }

/*** DBUpdData ****************************************************************/

 extern bool DBUpdData( regiodataS *a, tError *dbError )
 {
   exec sql begin declare section;
   regiodataS *d;
   const int iIsNew = 1;
   exec sql end declare section;

   d = a;
   exec sql execute p_UpdArt using ARTIKELF_ZEIGER_UPD(d), :iIsNew;

   if (sqlca.sqlcode != 0)
   {                                     
      fmeld (a, "Update");
   }

   return (bool)pCheckResult( dbError, "execute p_UpdArt" );
 }

/*****************************************************************************/
/*** PrivateFunction *********************************************************/
/*****************************************************************************/

/*** pCheckResult ************************************************************/

 static bool pCheckResult( tError *dbError, char *spText )
 {
   dbError->lSqlcode = sqlca.sqlcode;
   dbError->lSqlcisam = sqlca.sqlerrd[1];
   strcpy( dbError->spError, spText );

   return (bool)(!sqlca.sqlcode ? TRUE : FALSE );
 }

/*** pGetUpdRow **************************************************************/

 static bool pGetUpdRow( tError *dbError )
 {
   exec sql fetch CSelArt;
   return (bool)pCheckResult( dbError, "fetch CSelArt" );
 }

/*** pGetMinStockRow *********************************************************/

 static bool pGetMinStockRow( tError *dbError )
 {
   exec sql fetch CSelMinStockArt;
   return (bool)pCheckResult( dbError, "fetch CSelArt" );
 }

 /*** pGetDelRow **************************************************************/

 static bool pGetDelRow( tError *dbError )
 {
   exec sql fetch CSelDelArt;
   return (bool)pCheckResult( dbError, "fetch CSelArt" );
 }
