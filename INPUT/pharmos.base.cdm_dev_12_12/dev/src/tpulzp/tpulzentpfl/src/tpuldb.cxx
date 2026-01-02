
/******************************************************************************/
/*     Hauptmodul: tpulzentpfl                                                */
/*         Source: tpuldb.cxx                                                 */
/*          Autor: A. Schmidt-Rehschuh                                        */
/*       Erstellt: 01042.1998                                                 */
/*        Sprache: C/Esql-C                                                   */
/*        Erzeugt: manuell                                                    */
/*        Aufgabe: sätze aus DB lesen                                         */
/*                                                                            */
/******************************************************************************/

/*** INCLUDE ******************************************************************/


 #ifndef ESQL_C
 #define ESQL_C 
 #endif

 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <memory.h>

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

 #include <voodoo_table_header/zartwg.h>
 #include <voodoo_table_header/carticlecodes.h>
 #include <voodoo_table_header/herstellersalescondition.h>
 #include <voodoo_table_header/zartsekb.h>
 #include <voodoo_table_header/cdeposittypes.h>
 #include <voodoo_table_header/zartfeb2.h>
 #include <voodoo_table_header/csafetydatasheet.h>
 #include <voodoo_table_header/carticleext.h>
 #include <voodoo_table_header/zautidemsperre.h>
/*  #include "cgibatchentry.h" */
 #include <voodoo_table_header/artve.h>
 #include <voodoo_table_header/herstel.h>
 #include <voodoo_table_header/ean.h>
 #include <voodoo_table_header/zartprei.h>
 #include <voodoo_table_header/zartikel.h>
 #include <voodoo_table_header/zapflege.h>
 #include <voodoo_table_header/zartaustria.h>
 #include <voodoo_table_header/zartcroatia.h>
 #include <voodoo_table_header/zartbulgaria.h>
 #include <voodoo_table_header/zartserbia.h>
 #include <voodoo_table_header/zgrppflege.h>
 #include <voodoo_table_header/zpznpflege.h>
 #include <voodoo_table_header/zdkwgr.h>
 #include <voodoo_table_header/artkatg.h>
 #include <voodoo_table_header/zdktgr.h>
/* #include "zdkbtm.h" */
/* #include "zdkwir.h" */
 #include <voodoo_table_header/carticletext.h>
 #include <voodoo_table_header/zchargenrueckruf.h>
 #include <voodoo_table_header/cdiscount.h>
 #include <voodoo_table_header/zartswitzerland.h>
 #include <voodoo_table_header/carticlelang.h>
 #include <voodoo_table_header/cartcompack.h>
 #include <voodoo_table_header/ccpvalidityperiod.h>
 #include <voodoo_table_header/cdiscgrp.h>
/* #include "cgaloart.h"
   #include "cgalonam.h"
   #include "cgalocom.h" */
 #include <voodoo_table_header/herstel_dispo.h>
 #include <voodoo_table_header/zartfrance.h>
 #include <voodoo_table_header/zartverk.h>
 #include <voodoo_table_header/cpharmgrp.h>
 #include <voodoo_table_header/zrabgrp.h>
 #include <voodoo_table_header/zzahlbed.h>
 #include <voodoo_table_header/cdisclist.h>
 #include <voodoo_table_header/cservices.h>
 #include <voodoo_table_header/cdiscgrpmem.h>
 #include <voodoo_table_header/cdiscmodel.h>
 #include <voodoo_table_header/cmonthdiscsort.h>
 #include <voodoo_table_header/chighpaymtargetfee.h>
 #include <voodoo_table_header/ccustomergroup.h>
 #include <voodoo_table_header/ccustgrpflagtypes.h>
 #include <voodoo_table_header/ccustomergrpflags.h>
 #include <voodoo_table_header/cordertype.h>
 #include <voodoo_table_header/cordertypeflagtype.h>
 #include <voodoo_table_header/cordertypeflags.h>
 #include <voodoo_table_header/cmonthvirtsort.h>
/* #include "ccustservices.h" */
 #include <voodoo_table_header/cstoragecriteria.h>
 #include <voodoo_table_header/cintrastatcountry.h>
 #include <voodoo_table_header/cformtypes.h>
 #include <voodoo_table_header/cdiscform.h>
 #include <voodoo_table_header/cshipper.h>
 #include <voodoo_table_header/cpromotions.h>
 #include <voodoo_table_header/cregisters.h>
 #include <voodoo_table_header/cbaselistarticles.h>

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* #include "dezapzep.h" */
 #include "tpulzentpfl.h"
 #include "cdb.h"
 #include "logfile.h"

 #include "tpuldb.h"

 exec sql include sqlca;
 
/*** MACRO *********************************************************************/

 #define VERIFY(x) { int rc; if ( (rc = x) !=0 ) { \
                     return (rterror)(rc == SQLNOTFOUND ? eof:db_error);} }
 
/*** DECLARATION ***************************************************************/

/* hajo: warum dieser Schwachsinn ???????? */

/*   static int verify( char *spFun, int iError, char *spText );  */
 
/*** VERIFY ********************************************************************/

 static int verify( const char *spFun, const char *spText )
 {
   if ( sqlca.sqlcode < 0 )
      WriteLog( spFun, sqlca.sqlcode, "%s", spText );
   return sqlca.sqlcode;
 }

/*** START-BROWSE ******************************************************/

 rterror startBrowse( const long lDateCurrent, const long lDateUntil, const long lDateDelete, const char *spDatabase, const char *spKuerzel, const short sPrewhole )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lDateOfTheDay;
   long lDateTo;
   long lDateSince;
   exec sql end declare section;
   const char *fun = "startBrowse";

   lDateOfTheDay = lDateCurrent;
   lDateTo = lDateUntil;
   lDateSince    = lDateDelete;

   /* prepare for zartikel */
   /* musste umgebaut werden, weil die HSQL-Header-Files keinen Join erlauben */
   /* außerdem wird damit zukünftig vermieden, dass eine PZN doppelt in der DEZAP enthalten ist */
/* strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTIKEL );
   strcat( szBuf, " from zartikel, zapflege where " );
   strcat( szBuf, "zartikel.artikel_nr = zapflege.artikel_nr " );
   strcat( szBuf, "and zapflege.datum >= ? " );
   strcat( szBuf, "and zapflege.datum <= ? " ); */
   
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTIKEL );
   strcat( szBuf, " from zartikel where artikel_nr in " );
   strcat( szBuf, "(select distinct artikel_nr from zapflege " );
   strcat( szBuf, "where datum >= ? " );
   strcat( szBuf, "and datum <= ? )" ); 

   exec sql prepare pre_zartikel from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartikel" ) );
	
   /* prepare for zgrppflege */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZGRPPFLEGE );
   strcat( szBuf, " from zgrppflege " );
   strcat( szBuf, "where datum >= ? " );
   strcat( szBuf, "and datum <= ? " ); 
   strcat( szBuf, "order by dezap_sa " ); 

   exec sql prepare pre_zgrppflege from :szBuf;
   VERIFY( verify( fun, "prepare pre_zgrppflege" ) );
	
   /* prepare for zpznpflege */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZPZNPFLEGE );
   strcat( szBuf, " from zpznpflege " );
   strcat( szBuf, "where datum >= ? " );
   strcat( szBuf, "and datum <= ? " ); 

   exec sql prepare pre_zpznpflege from :szBuf;
   VERIFY( verify( fun, "prepare pre_zpznpflege" ) );
	
   /* prepare for zartpreis */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTPREIS );
   strcat( szBuf, " from zartpreis where artikel_nr = ? " );
   strcat( szBuf, "and preis_typ = 0 " );   /* Default für alle Länder für Übertragung ins Pharmos */
   strcat( szBuf, "and datumgueltigab <= ? " );   /* muss evtl. erweitert werden! */
   strcat( szBuf, "order by datumgueltigab desc " );  
   
   exec sql prepare pre_zartpreis from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartpreis" ) );
	
   /* prepare for zartsekbez */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTSEKBEZ );
   strcat( szBuf, " from zartsekbez where artikel_nr = ? " );
   strcat( szBuf, "and pharmos_sekbez = \"1\" " );
   
   exec sql prepare pre_zartsekbez from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartsekbez" ) );
	
   /* prepare for cdeposittypes */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CDEPOSITTYPES );
   strcat( szBuf, " from cdeposittypes where deposit_type = ? " );
   
   exec sql prepare pre_cdeposittypes from :szBuf;
   VERIFY( verify( fun, "prepare pre_cdeposittypes" ) );
	
    /* prepare for zartwg */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTWG );
   strcat( szBuf, " from zartwg where artikel_nr = ? and art != \" \" " );
   
   exec sql prepare pre_zartwg from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartwg" ) );
	
    /* prepare for carticlecodes */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CARTICLECODES );
   strcat( szBuf, " from carticlecodes where articleno = ? " );
   
   exec sql prepare pre_carticlecodes from :szBuf;
   VERIFY( verify( fun, "prepare pre_carticlecodes" ) );
	
    /* prepare for herstellersalescondition */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_HERSTELLERSALESCONDITION );
   strcat( szBuf, " from herstellersalescondition where hersteller_nr = ?" );
   
   exec sql prepare pre_hsalescond from :szBuf;
   VERIFY( verify( fun, "prepare pre_hsalescond" ) );
	
    /* prepare for ean */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_EAN );
   strcat( szBuf, " from ean where artikel_nr = ? " );
   
   exec sql prepare pre_ean from :szBuf;
   VERIFY( verify( fun, "prepare pre_ean" ) );

    /* prepare for herstel */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_HERSTEL );
   strcat( szBuf, " from herstel where hersteller_nr = ? " );
   
   exec sql prepare pre_herstel from :szBuf;
   VERIFY( verify( fun, "prepare pre_herstel" ) );

    /* prepare for herstel_dispo */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_HERSTEL_DISPO );
   strcat( szBuf, " from herstel_dispo where hersteller_nr = ? " );
   
   exec sql prepare pre_herstel_dispo from :szBuf;
   VERIFY( verify( fun, "prepare pre_herstel_dispo" ) );

    /* prepare for zartfeb2 */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTFEB2 );
   strcat( szBuf, " from zartfeb2 where artikel_nr = ? " );
   
   exec sql prepare pre_zartfeb2 from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartfeb2" ) );

    /* prepare for csafetydatasheet */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CSAFETYDATASHEET );
   strcat( szBuf, " from csafetydatasheet where articleno = ? " );
   
   exec sql prepare pre_csafetydatasheet from :szBuf;
   VERIFY( verify( fun, "prepare pre_csafetydatasheet" ) );

    /* prepare for carticlext */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CARTICLEEXT );
   strcat( szBuf, " from carticleext where articleno = ? " );
   
   exec sql prepare pre_carticleext from :szBuf;
   VERIFY( verify( fun, "prepare pre_carticleext" ) );

    /* prepare for zautidemsperre */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZAUTIDEMSPERRE );
   strcat( szBuf, " from zautidemsperre where artikel_nr = ? " );
   
   exec sql prepare pre_zautidemsperre from :szBuf;
   VERIFY( verify( fun, "prepare pre_zautidemsperre" ) );

    /* prepare for cgibatchentry 
   strcpy( szBuf, "select first 1 " );
   strcat( szBuf, PROJECTION_CGIBATCHENTRY );
   strcat( szBuf, " from cgibatchentry where articleno = ? " );
   
   exec sql prepare pre_cgibatchentry from :szBuf;
   VERIFY( verify( fun, "prepare pre_cgibatchentry" ) ); */

    /* prepare for artve */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ARTVE );
   strcat( szBuf, " from artve where artikel_nr = ? " );
   
   exec sql prepare pre_artve from :szBuf;
   VERIFY( verify( fun, "prepare pre_artve" ) );

    /* prepare for zartikel (wird für SA 10, 33 & 39 nochmal benötigt) */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTIKEL );
   strcat( szBuf, " from zartikel where artikel_nr = ? " );
   
   exec sql prepare pre_zartikel2 from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartikel2" ) );

    /* prepare for ccpvalidityperiod */
	strcpy( szBuf, "select " );
	strcat( szBuf, PROJECTION_CCPVALIDITYPERIOD );
	strcat( szBuf, " from ccpvalidityperiod where article_no_pack = ? " );
		
	exec sql prepare pre_ccpvalidityperiod from :szBuf;
	VERIFY( verify( fun, "prepare pre_ccpvalidityperiod" ) );

    /* prepare for cdiscgrp */
	strcpy( szBuf, "select " );
	strcat( szBuf, PROJECTION_CDISCGRP );
	strcat( szBuf, " from cdiscgrp where discountgrpno = ? " );
		
	exec sql prepare pre_cdiscgrp from :szBuf;
	VERIFY( verify( fun, "prepare pre_cdiscgrp" ) );

	/* prepare for zartaustria (nur in Österreich) */
    if (strcmp(spKuerzel, "A") == 0)
	{
		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_ZARTAUSTRIA );
		strcat( szBuf, " from zartaustria where artikel_nr = ? " );
		   
		exec sql prepare pre_zartaustria from :szBuf;
		VERIFY( verify( fun, "prepare pre_zartaustria" ) );
	}

    /* prepare for zartcroatia (nur in Kroatien) */
    if (strcmp(spKuerzel, "HR") == 0)
	{
		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_ZARTCROATIA );
		strcat( szBuf, " from zartcroatia where articleno = ? " );
		   
		exec sql prepare pre_zartcroatia from :szBuf;
		VERIFY( verify( fun, "prepare pre_zartcroatia" ) );
	}

    /* prepare for zartbulgaria (nur in Bulgarien) */
    if (strcmp(spKuerzel, "BG") == 0)
	{
		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_ZARTBULGARIA );
		strcat( szBuf, " from zartbulgaria where articleno = ? " );
		   
		exec sql prepare pre_zartbulgaria from :szBuf;
		VERIFY( verify( fun, "prepare pre_zartbulgaria" ) );
	}

    /* prepare for zartserbia (nur in Serbien) */
    if (strcmp(spKuerzel, "RS") == 0)
	{
		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_ZARTSERBIA );
		strcat( szBuf, " from zartserbia where articleno = ? " );
		   
		exec sql prepare pre_zartserbia from :szBuf;
		VERIFY( verify( fun, "prepare pre_zartserbia" ) );
	}

    /* prepare for carticlelang (nur in der Schweiz und Bulgarien) */
    if (strcmp(spKuerzel, "CH") == 0 ||
		strcmp(spKuerzel, "BG") == 0)
	{
		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_CARTICLELANG );
		strcat( szBuf, " from carticlelang where articleno = ? " );
		strcat( szBuf, " and langid = ? " );
		   
		exec sql prepare pre_carticlelang from :szBuf;
		VERIFY( verify( fun, "prepare pre_carticlelang" ) );
	}

    /* prepare for zartswitzerland & cgalo* (nur in der Schweiz) */
    if (strcmp(spKuerzel, "CH") == 0)
	{
		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_ZARTSWITZERLAND );
		strcat( szBuf, " from zartswitzerland where artikel_nr = ? " );
		   
		exec sql prepare pre_zartswitzerland from :szBuf;
		VERIFY( verify( fun, "prepare pre_zartswitzerland" ) );

/*		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_CGALOCOM );
		strcat( szBuf, " from cgalocom where comp_no = ? " );
		   
		exec sql prepare pre_cgalocom from :szBuf;
		VERIFY( verify( fun, "prepare pre_cgalocom" ) );

		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_CGALOART );
		strcat( szBuf, " from cgaloart where articleno = ? " );
		   
		exec sql prepare pre_cgaloart from :szBuf;
		VERIFY( verify( fun, "prepare pre_cgaloart" ) );

		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_CGALONAM );
		strcat( szBuf, " from cgalonam where articleno = ? " );
		   
		exec sql prepare pre_cgalonam from :szBuf;
		VERIFY( verify( fun, "prepare pre_cgalonam" ) );

 		exec sql declare cu_cgalonam cursor for pre_cgalonam; */
	}

    /* prepare for zartfrance & cdisclist (nur in Frankreich) */
    if (strcmp(spKuerzel, "F") == 0)
	{
		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_ZARTFRANCE );
		strcat( szBuf, " from zartfrance where articleno = ? " );
		   
		exec sql prepare pre_zartfrance from :szBuf;
		VERIFY( verify( fun, "prepare pre_zartfrance" ) );

		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_CDISCLIST );
		strcat( szBuf, " from cdisclist where order_type = ? and sub_order_type = ?" );
		   
		exec sql prepare pre_cdisclist from :szBuf;
		VERIFY( verify( fun, "prepare pre_cdisclist" ) );
	}

    /* prepare for cservices (nur in Frankreich und neu auch in Bulgarien) */
    if (strcmp(spKuerzel, "F") == 0 ||
		strcmp(spKuerzel, "BG") == 0)
	{
		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_CSERVICES );
		strcat( szBuf, " from cservices where service_no = ?" );
		   
		exec sql prepare pre_cservices from :szBuf;
		VERIFY( verify( fun, "prepare pre_cservices" ) );
	}

    /* prepare for zdkwgr */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZDKWGR );
   strcat( szBuf, " from zdkwgr where wgr_gruppe = ? " );
   
   exec sql prepare pre_zdkwgr from :szBuf;
   VERIFY( verify( fun, "prepare pre_zdkwgr" ) );

    /* prepare for artkatg */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ARTKATG );
   strcat( szBuf, " from artkatg where warengruppe = ? " );
   
   exec sql prepare pre_zdkiwg from :szBuf;
   VERIFY( verify( fun, "prepare pre_zdkiwg" ) );

    /* prepare for zdktgr */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZDKTGR );
   strcat( szBuf, " from zdktgr where tgr_gruppe = ? " );
   
   exec sql prepare pre_zdktgr from :szBuf;
   VERIFY( verify( fun, "prepare pre_zdktgr" ) );

    /* prepare for zdkbtm 
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZDKBTM );
   strcat( szBuf, " from zdkbtm where btm_gruppe = ? " );
   
   exec sql prepare pre_zdkbgr from :szBuf;
   VERIFY( verify( fun, "prepare pre_zdkbgr" ) ); */

    /* prepare for zrabgrp */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZRABGRP );
   strcat( szBuf, " from zrabgrp where rabattgruppe = ? " );
   
   exec sql prepare pre_zrabgrp from :szBuf;
   VERIFY( verify( fun, "prepare pre_zrabgrp" ) );

    /* prepare for zzahlbed */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZZAHLBED );
   strcat( szBuf, " from zzahlbed where zahlungsbedingung = ? " );
   
   exec sql prepare pre_zzahlbed from :szBuf;
   VERIFY( verify( fun, "prepare pre_zzahlbed" ) );

    /* prepare for cdiscmodel */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CDISCMODEL );
   strcat( szBuf, " from cdiscmodel where discountmodelno = ? " );
   
   exec sql prepare pre_cdiscmodel from :szBuf;
   VERIFY( verify( fun, "prepare pre_cdiscmodel" ) );

    /* prepare for cmonthdiscsort */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CMONTHDISCSORT );
   strcat( szBuf, " from cmonthdiscsort where monthlydiscountgrp = ? " );
   
   exec sql prepare pre_cmonthdiscsort from :szBuf;
   VERIFY( verify( fun, "prepare pre_cmonthdiscsort" ) );

    /* prepare for chighpaymtargetfee (nur für Großhandel Frankreich) */
    if (strcmp(spKuerzel, "F") == 0 && sPrewhole == 0)
	{
		strcpy( szBuf, "select " );
		strcat( szBuf, PROJECTION_CHIGHPAYMTARGETFEE );
		strcat( szBuf, " from chighpaymtargetfee where custclassification = ? " );
		strcat( szBuf, " and frompaymtargetdays = ? " );
   
		exec sql prepare pre_chighpaymtargetfee from :szBuf;
		VERIFY( verify( fun, "prepare pre_chighpaymtargetfee" ) );
	}

    /* prepare for ccustomergroup */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CCUSTOMERGROUP );
   strcat( szBuf, " from ccustomergroup where customergroupno = ? " );
   
   exec sql prepare pre_ccustomergroup from :szBuf;
   VERIFY( verify( fun, "prepare pre_cccustomergroup" ) );

    /* prepare for cordertype */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CORDERTYPE );
   strcat( szBuf, " from cordertype where cscordertype = ? " );
   
   exec sql prepare pre_cordertype from :szBuf;
   VERIFY( verify( fun, "prepare pre_cordertype" ) );

    /* prepare for cmonthvirtsort */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CMONTHVIRTSORT );
   strcat( szBuf, " from cmonthvirtsort where monthlyvirtualgroup = ? " );
   
   exec sql prepare pre_cmonthvirtsort from :szBuf;
   VERIFY( verify( fun, "prepare pre_cmonthvirtsort" ) );

    /* prepare for ccustservices *
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CCUSTSERVICES );
   strcat( szBuf, " from ccustservices where service_no = ? " );
   
   exec sql prepare pre_ccustservices from :szBuf;
   VERIFY( verify( fun, "prepare pre_ccustservices" ) ); */

    /* prepare for cstoragecriteria */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CSTORAGECRITERIA );
   strcat( szBuf, " from cstoragecriteria where storagecriteriano = ? " );
   
   exec sql prepare pre_cstoragecriteria from :szBuf;
   VERIFY( verify( fun, "prepare pre_cstoragecriteria" ) );

    /* prepare for cintrastatcountry */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CINTRASTATCOUNTRY );
   strcat( szBuf, " from cintrastatcountry where countrycode = ? " );
   
   exec sql prepare pre_cintrastatcountry from :szBuf;
   VERIFY( verify( fun, "prepare pre_cintrastatcountry" ) );

    /* prepare for cformtypes */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CFORMTYPES );
   strcat( szBuf, " from cformtypes where formtype = ? " );
   
   exec sql prepare pre_cformtypes from :szBuf;
   VERIFY( verify( fun, "prepare pre_cformtypes" ) );

    /* prepare for cdiscform */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CDISCFORM );
   strcat( szBuf, " from cdiscform where discountformno = ? " );
   
   exec sql prepare pre_cdiscform from :szBuf;
   VERIFY( verify( fun, "prepare pre_cdiscform" ) );

    /* prepare for cshipper */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CSHIPPER );
   strcat( szBuf, " from cshipper where shipperno = ? " );
   
   exec sql prepare pre_cshipper from :szBuf;
   VERIFY( verify( fun, "prepare pre_cshipper" ) );

    /* prepare for cpromotions */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CPROMOTIONS );
   strcat( szBuf, " from cpromotions where promotion_no = ? " );
   
   exec sql prepare pre_cpromotions from :szBuf;
   VERIFY( verify( fun, "prepare pre_cpromotions" ) );

    /* prepare for cregisters */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CREGISTERS );
   strcat( szBuf, " from cregisters where ministryproductcode = ? " );
   
   exec sql prepare pre_cregisters from :szBuf;
   VERIFY( verify( fun, "prepare pre_cregisters" ) );

    /* prepare for zdkwir 
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZDKWIR );
   strcat( szBuf, " from zdkwir where wir_bereich = ? " );
   
   exec sql prepare pre_zdkwir from :szBuf;
   VERIFY( verify( fun, "prepare pre_zdkwir" ) ); */

    /* prepare for carticletext */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CARTICLETEXT );
   strcat( szBuf, " from carticletext where textno = ? " );
   
   exec sql prepare pre_carticletext from :szBuf;
   VERIFY( verify( fun, "prepare pre_carticletext" ) );

    /* prepare for cpharmgrp */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CPHARMGRP );
   strcat( szBuf, " from cpharmgrp where pharmacygroupid = ? " );
   
   exec sql prepare pre_cpharmgrp from :szBuf;
   VERIFY( verify( fun, "prepare pre_cpharmgrp" ) );

   /* prepare for delete zapflege */
   strcpy( szBuf, "select artikel_nr from zapflege " );
   strcat( szBuf, "where zapflege.datum <= ? for update " );
   
   exec sql prepare pre_zapflege from :szBuf;
   VERIFY( verify( fun, "prepare pre_zapflege" ) );

   strcpy( szBuf, "delete from zapflege where current of cu_zapflege " );
   exec sql prepare del_zapflege from :szBuf;
   VERIFY( verify( fun, "prepare del_zapflege" ) );
   
   /* prepare for delete zgrppflege */
   strcpy( szBuf, "select key_gruppe from zgrppflege " );
   strcat( szBuf, "where zgrppflege.datum <= ? for update " );
   
   exec sql prepare pre_delzgrppflege from :szBuf;
   VERIFY( verify( fun, "prepare pre_delzgrppflege" ) );

   strcpy( szBuf, "delete from zgrppflege where current of cu_delzgrppflege " );
   exec sql prepare del_zgrppflege from :szBuf;
   VERIFY( verify( fun, "prepare del_zgrppflege" ) );
   
   /* prepare for delete zpznpflege */
   strcpy( szBuf, "select artikel_nr from zpznpflege " );
   strcat( szBuf, "where zpznpflege.datum <= ? for update " );
   
   exec sql prepare pre_delzpznpflege from :szBuf;
   VERIFY( verify( fun, "prepare pre_delzpznpflege" ) );

   strcpy( szBuf, "delete from zpznpflege where current of cu_delzpznpflege " );
   exec sql prepare del_zpznpflege from :szBuf;
   VERIFY( verify( fun, "prepare del_zpznpflege" ) );
   
   /* declare for zartikel with open */
   exec sql declare cu_zartikel cursor for pre_zartikel;
   exec sql open cu_zartikel using :lDateOfTheDay, :lDateTo;
   VERIFY( verify( fun, "open cu_zartikel" ) );

   /* declare for zgrppflege with open */
   exec sql declare cu_zgrppflege cursor for pre_zgrppflege;
   exec sql open cu_zgrppflege using :lDateOfTheDay, :lDateTo;
   VERIFY( verify( fun, "open cu_zgrppflege" ) );

   /* declare for zpznpflege with open */
   exec sql declare cu_zpznpflege cursor for pre_zpznpflege;
   exec sql open cu_zpznpflege using :lDateOfTheDay, :lDateTo;
   VERIFY( verify( fun, "open cu_zpznpflege" ) );

   /* declare for zartpreis */
   exec sql declare cu_zartpreis cursor for pre_zartpreis;
   
   /* declare for zartsekbez */
   exec sql declare cu_zartsekbez cursor for pre_zartsekbez;
   
   /* declare for cdeposittypes */
   exec sql declare cu_cdeposittypes cursor for pre_cdeposittypes;
   
   /* declare for zartwg */
   exec sql declare cu_zartwg cursor for pre_zartwg;

   /* declare for carticlecodes */
   exec sql declare cu_carticlecodes cursor for pre_carticlecodes;

   /* declare for herstellsalescondition */
   exec sql declare cu_hsalescond cursor for pre_hsalescond;

   /* declare for ean */
   exec sql declare cu_ean cursor for pre_ean;

   /* declare for herstel */
   exec sql declare cu_herstel cursor for pre_herstel;

   /* declare for herstel_dispo */
   exec sql declare cu_herstel_dispo cursor for pre_herstel_dispo;

   /* declare for zapflege */
   exec sql declare cu_zapflege cursor with hold for pre_zapflege;
   exec sql open cu_zapflege using :lDateSince;
   VERIFY( verify( fun, "open cu_zapflege" ) );

   /* declare for delete zgrppflege */
   exec sql declare cu_delzgrppflege cursor with hold for pre_delzgrppflege;
   exec sql open cu_delzgrppflege using :lDateSince;
   VERIFY( verify( fun, "open cu_delzgrppflege" ) );

   /* declare for delete zpznpflege */
   exec sql declare cu_delzpznpflege cursor with hold for pre_delzpznpflege;
   exec sql open cu_delzpznpflege using :lDateSince;
   VERIFY( verify( fun, "open cu_delzpznpflege" ) );

  return no_error;
 }

/*** END-BROWSE ********************************************************/

 rterror endBrowse( const bool bCloseAll  )
 {
   const char *fun = "endBrowse";

   exec sql close cu_zartikel;
   VERIFY( verify( fun, "close cu_zartikel" ) );
   if ( bCloseAll )
   {
      exec sql close cu_zartpreis;
      VERIFY( verify( fun, "close cu_zartpreis" ) );
      exec sql close cu_zartsekbez;
      VERIFY( verify( fun, "close cu_zartsekbez" ) );
      exec sql close cu_cdeposittypes;
      VERIFY( verify( fun, "close cu_cdeposittypes" ) );
      exec sql close cu_herstel;
      VERIFY( verify( fun, "close cu_herstel" ) );
      exec sql close cu_zartwg;
      VERIFY( verify( fun, "close cu_zartwg" ) );
      exec sql close cu_carticlecodes;
      VERIFY( verify( fun, "close cu_zcarticlecodes" ) );
      exec sql close cu_hsalescond;
      VERIFY( verify( fun, "close cu_hsalescond" ) );
      exec sql close cu_ean;
      VERIFY( verify( fun, "close cu_ean" ) );
   }

   return no_error;
 }

/*** START-BROWSE-ZCHARGENRUECKRUF ******************************************************/

 rterror startBrowseZchargenrueckruf( const long artikel_nr )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lartikel_nr;
   exec sql end declare section;
   const char *fun = "startBrowseZchargenrueckruf";

   lartikel_nr = artikel_nr;

   /* prepare for zchargenrueckruf */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZCHARGENRUECKRUF );
   strcat( szBuf, " from zchargenrueckruf " );
   strcat( szBuf, "where artikel_nr = ? " );

   exec sql prepare pre_zchargenrueckruf from :szBuf;
   VERIFY( verify( fun, "prepare pre_zchargenrueckruf" ) );
	
   /* declare for pre_zchargenrueckruf with open */
   exec sql declare cu_zchargenrueckruf cursor for pre_zchargenrueckruf;
   exec sql open cu_zchargenrueckruf using :lartikel_nr;
   VERIFY( verify( fun, "open cu_zchargenrueckruf" ) );

  return no_error;
 }

/*** END-BROWSE-ZCHARGENRUECKRUF ********************************************************/

 rterror endBrowseZchargenrueckruf( )
 {
   const char *fun = "endBrowseZchargenrueckruf";

   exec sql close cu_zchargenrueckruf;
   VERIFY( verify( fun, "close cu_zchargenrueckruf" ) );

   return no_error;
 }

/*** START-BROWSE-CBASELISTARTICLES ******************************************************/

 rterror startBrowseCbaselistarticles( const long artikel_nr )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lartikel_nr;
   exec sql end declare section;
   const char *fun = "startBrowseCbaselistarticles";

   lartikel_nr = artikel_nr;

   /* prepare for cbaselistarticles */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CBASELISTARTICLES );
   strcat( szBuf, " from cbaselistarticles " );
   strcat( szBuf, "where articleno = ? " );

   exec sql prepare pre_cbaselistarticles from :szBuf;
   VERIFY( verify( fun, "prepare pre_cbaselistarticles" ) );
	
   /* declare for pre_cbaselistarticles with open */
   exec sql declare cu_cbaselistarticles cursor for pre_cbaselistarticles;
   exec sql open cu_cbaselistarticles using :lartikel_nr;
   VERIFY( verify( fun, "open cu_cbaselistarticles" ) );

  return no_error;
 }

/*** END-BROWSE-CBASELISTARTICLES ********************************************************/

 rterror endBrowseCbaselistarticles( )
 {
   const char *fun = "endBrowseCbaselistarticles";

   exec sql close cu_cbaselistarticles;
   VERIFY( verify( fun, "close cu_cbaselistarticles" ) );

   return no_error;
 }

/*** START-BROWSE-CARTICLECODES ******************************************************/

 rterror startBrowseCarticlecodes( const long artikel_nr )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lartikel_nr;
   exec sql end declare section;
   const char *fun = "startBrowseCarticlecodes";

   lartikel_nr = artikel_nr;

   /* prepare for carticlecodes */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CARTICLECODES );
   strcat( szBuf, " from carticlecodes " );
   strcat( szBuf, "where articleno = ? " );

   exec sql prepare pre_carticlecodes_34 from :szBuf;
   VERIFY( verify( fun, "prepare pre_carticlecodes_34" ) );
	
   /* declare for pre_carticlecodes with open */
   exec sql declare cu_carticlecodes_34 cursor for pre_carticlecodes_34;
   exec sql open cu_carticlecodes_34 using :lartikel_nr;
   VERIFY( verify( fun, "open cu_carticlecodes_34" ) );

  return no_error;
 }

/*** END-BROWSE-CARTICLECODES ********************************************************/

 rterror endBrowseCarticlecodes( )
 {
   const char *fun = "endBrowseCarticlecodes";

   exec sql close cu_carticlecodes_34;
   VERIFY( verify( fun, "close cu_carticlecodes_34" ) );

   return no_error;
 }

/*** START-BROWSE-CDISCOUNT_PZN ******************************************************/

 rterror startBrowseCdiscount_Pzn( const long artikel_nr, const long date )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lartikel_nr, ldate;
   exec sql end declare section;
   const char *fun = "startBrowseCdiscount_Pzn";

   lartikel_nr = artikel_nr;
   ldate = date;

   /* prepare for cdiscount */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CDISCOUNT );
   strcat( szBuf, " from cdiscount " );
   strcat( szBuf, "where articleno = ? " );
   strcat( szBuf, "and dateto >= ? " );

   exec sql prepare pre_cdiscount_pzn from :szBuf;
   VERIFY( verify( fun, "prepare pre_cdiscount_pzn" ) );
	
   /* declare for pre_cdiscount_pzn with open */
   exec sql declare cu_cdiscount_pzn cursor for pre_cdiscount_pzn;
   exec sql open cu_cdiscount_pzn using :lartikel_nr, :ldate;
   VERIFY( verify( fun, "open cu_cdiscount_pzn" ) );

  return no_error;
 }

/*** END-BROWSE-CDISCOUNT_PZN ********************************************************/

 rterror endBrowseCdiscount_Pzn( )
 {
   const char *fun = "endBrowse";

   exec sql close cu_cdiscount_pzn;
   VERIFY( verify( fun, "close cu_cdiscount_pzn" ) );

   return no_error;
 }

/*** START-BROWSE-CDISCOUNT_RPG ******************************************************/

 rterror startBrowseCdiscount_Rpg( const long rabgrp_nr )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lrabgrp_nr;
   exec sql end declare section;
   const char *fun = "startBrowseCdiscount_Rpg";

   lrabgrp_nr = rabgrp_nr;

   /* prepare for cdiscount */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CDISCOUNT );
   strcat( szBuf, " from cdiscount " );
   strcat( szBuf, "where discountgrpno = ? " );

   exec sql prepare pre_cdiscount_rpg from :szBuf;
   VERIFY( verify( fun, "prepare pre_cdiscount_rpg" ) );
	
   /* declare for pre_cdiscount_rpg with open */
   exec sql declare cu_cdiscount_rpg cursor for pre_cdiscount_rpg;
   exec sql open cu_cdiscount_rpg using :lrabgrp_nr;
   VERIFY( verify( fun, "open cu_cdiscount_rpg" ) );

  return no_error;
 }

/*** END-BROWSE-CDISCOUNT_RPG ********************************************************/

 rterror endBrowseCdiscount_Rpg( )
 {
   const char *fun = "endBrowse";

   exec sql close cu_cdiscount_rpg;
   VERIFY( verify( fun, "close cu_cdiscount_rpg" ) );

   return no_error;
 }

/*** START-BROWSE-CDISCOUNT_HNR ******************************************************/

 rterror startBrowseCdiscount_Hnr( const long hersteller_nr )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lhersteller_nr;
   exec sql end declare section;
   const char *fun = "startBrowseCdiscount_Hnr";

   lhersteller_nr = hersteller_nr;

   /* prepare for cdiscount */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CDISCOUNT );
   strcat( szBuf, " from cdiscount " );
   strcat( szBuf, "where manufacturerno = ? " );

   exec sql prepare pre_cdiscount_hnr from :szBuf;
   VERIFY( verify( fun, "prepare pre_cdiscount_hnr" ) );
	
   /* declare for pre_cdiscount_hnr with open */
   exec sql declare cu_cdiscount_hnr cursor for pre_cdiscount_hnr;
   exec sql open cu_cdiscount_hnr using :lhersteller_nr;
   VERIFY( verify( fun, "open cu_cdiscount_hnr" ) );

  return no_error;
 }

/*** END-BROWSE-CDISCOUNT_HNR ********************************************************/

 rterror endBrowseCdiscount_Hnr( )
 {
   const char *fun = "endBrowse";

   exec sql close cu_cdiscount_hnr;
   VERIFY( verify( fun, "close cu_cdiscount_hnr" ) );

   return no_error;
 }

/*** START-BROWSE-CDISCOUNT_AGN ******************************************************/

 rterror startBrowseCdiscount_Agn( const long artkat_nr )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lartkat_nr;
   exec sql end declare section;
   const char *fun = "startBrowseCdiscount_Agn";

   lartkat_nr = artkat_nr;

   /* prepare for cdiscount */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CDISCOUNT );
   strcat( szBuf, " from cdiscount " );
   strcat( szBuf, "where artcategoryno = ? " );

   exec sql prepare pre_cdiscount_agn from :szBuf;
   VERIFY( verify( fun, "prepare pre_cdiscount_agn" ) );
	
   /* declare for pre_cdiscount_agn with open */
   exec sql declare cu_cdiscount_agn cursor for pre_cdiscount_agn;
   exec sql open cu_cdiscount_agn using :lartkat_nr;
   VERIFY( verify( fun, "open cu_cdiscount_agn" ) );

  return no_error;
 }

/*** END-BROWSE-CDISCOUNT_AGN ********************************************************/

 rterror endBrowseCdiscount_Agn( )
 {
   const char *fun = "endBrowse";

   exec sql close cu_cdiscount_agn;
   VERIFY( verify( fun, "close cu_cdiscount_agn" ) );

   return no_error;
 }

/*** START-BROWSE-CARTCOMPACK ******************************************************/

 rterror startBrowseCartcompack ( const long artikel_nr )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lartikel_nr;
   exec sql end declare section;
   const char *fun = "startBrowseCartcompack";

   lartikel_nr = artikel_nr;

   /* prepare for cartcompack */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CARTCOMPACK );
   strcat( szBuf, " from cartcompack " );
   strcat( szBuf, "where article_no_pack = ? " );

   exec sql prepare pre_cartcompack from :szBuf;
   VERIFY( verify( fun, "prepare pre_cartcompack" ) );
	
   /* declare for pre_cartcompack with open */
   exec sql declare cu_cartcompack cursor for pre_cartcompack;
   exec sql open cu_cartcompack using :lartikel_nr;
   VERIFY( verify( fun, "open cu_cartcompack" ) );

  return no_error;
 }

/*** END-BROWSE-CARTCOMPACK ********************************************************/

 rterror endBrowseCartcompack( )
 {
   const char *fun = "endBrowse";

   exec sql close cu_cartcompack;
   VERIFY( verify( fun, "close cu_cartcompack" ) );

   return no_error;
 }

/*** START-BROWSE-ZARTVERK ******************************************************/

 rterror startBrowseZartverk ( const long artikel_nr )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long lartikel_nr;
   exec sql end declare section;
   const char *fun = "startBrowseZartverk";

   lartikel_nr = artikel_nr;

   /* prepare for zartverk */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_ZARTVERK );
   strcat( szBuf, " from zartverk " );
   strcat( szBuf, "where artikel_nr_bas = ? " );
   strcat( szBuf, "order by prioritaet " );

   exec sql prepare pre_zartverk from :szBuf;
   VERIFY( verify( fun, "prepare pre_zartverk" ) );
	
   /* declare for pre_zartverk with open */
   exec sql declare cu_zartverk cursor for pre_zartverk;
   exec sql open cu_zartverk using :lartikel_nr;
   VERIFY( verify( fun, "open cu_zartverk" ) );

  return no_error;
 }

/*** END-BROWSE-ZARTVERK ********************************************************/

 rterror endBrowseZartverk( )
 {
   const char *fun = "endBrowse";

   exec sql close cu_zartverk;
   VERIFY( verify( fun, "close cu_zartverk" ) );

   return no_error;
 }

/*** START-BROWSE-CDISCGRPMEM ******************************************************/

 rterror startBrowseCdiscgrpmem( const long discountgrpno )
 {
   exec sql begin declare section;
   char szBuf[4096];
   long ldiscountgrpno;
   exec sql end declare section;
   const char *fun = "startBrowseCdiscgrpmem";

   ldiscountgrpno = discountgrpno;

   /* prepare for cdiscgrpmem */
   strcpy( szBuf, "select " );
   strcat( szBuf, PROJECTION_CDISCGRPMEM );
   strcat( szBuf, " from cdiscgrpmem " );
   strcat( szBuf, "where discountgrpno = ? " );

   exec sql prepare pre_cdiscgrpmem from :szBuf;
   VERIFY( verify( fun, "prepare pre_cdiscgrpmem" ) );
	
   /* declare for pre_cdiscgrpmem with open */
   exec sql declare cu_cdiscgrpmem cursor for pre_cdiscgrpmem;
   exec sql open cu_cdiscgrpmem using :ldiscountgrpno;
   VERIFY( verify( fun, "open cu_cdiscgrpmem" ) );

  return no_error;
 }

/*** END-BROWSE-CDISCGRPMEM ********************************************************/

 rterror endBrowseCdiscgrpmem( )
 {
   const char *fun = "endBrowse";

   exec sql close cu_cdiscgrpmem;
   VERIFY( verify( fun, "close cu_cdiscgrpmem" ) );

   return no_error;
 }

/*** START-BROWSE-CCUSTOMERGROUPFLAGS ******************************************************/

 rterror startBrowseCcustomergroupflags( const short sKundengruppe )
 {
   exec sql begin declare section;
   char szBuf[4096];
   short skgr;
   exec sql end declare section;
   const char *fun = "startBrowseCcustomergroupflags";

   skgr = sKundengruppe;

   /* prepare for ccustomergroupflags */
   strcpy( szBuf, "select " );
   strcat( szBuf, "ccustomergrpflags.customergrpflag, ccustgrpflagtypes.index_dkkgr ");
   strcat( szBuf, "from ccustgrpflagtypes, ccustomergrpflags " );
   strcat( szBuf, "where customergroupno = ? " );
   strcat( szBuf, "and index_dkkgr > 0 " );
   strcat( szBuf, "and ccustgrpflagtypes.custgrpflagtype = ccustomergrpflags.custgrpflagtype " );

   exec sql prepare pre_ccustomergroupflags from :szBuf;
   VERIFY( verify( fun, "prepare pre_ccustomergroupflags" ) );
	
   /* declare for pre_ccustomergroupflags with open */
   exec sql declare cu_ccustomergroupflags cursor for pre_ccustomergroupflags;
   exec sql open cu_ccustomergroupflags using :skgr;
   VERIFY( verify( fun, "open cu_ccustomergroupflags" ) );

  return no_error;
 }

/*** END-BROWSE-CCUSTOMERGROUPFLAGS ********************************************************/

 rterror endBrowseCcustomergroupflags( )
 {
   const char *fun = "endBrowseCcustomergroupflags";

   exec sql close cu_ccustomergroupflags;
   VERIFY( verify( fun, "close cu_ccustomergroupflags" ) );

   return no_error;
 }

/*** START-BROWSE-CORDERTYPEFLAGS ******************************************************/

 rterror startBrowseCordertypeflags( const char *cAuftragsart )
 {
   exec sql begin declare section;
   char szBuf[4096];
   char cAart[3];
   exec sql end declare section;
   const char *fun = "startBrowseCordertypeflags";

   strncpy (cAart, cAuftragsart, 2);
   cAart[2] = '\0';

   /* prepare for cordertypeflags */
   strcpy( szBuf, "select " );
   strcat( szBuf, "cordertypeflags.ordertypeflag, cordertypeflagtype.index_dkaua ");
   strcat( szBuf, "from cordertypeflagtype, cordertypeflags " );
   strcat( szBuf, "where cscordertype = ? " );
   strcat( szBuf, "and index_dkaua > 0 " );
   strcat( szBuf, "and cordertypeflagtype.ordertypeflagtype = cordertypeflags.ordertypeflagtype " );

   exec sql prepare pre_cordertypeflags from :szBuf;
   VERIFY( verify( fun, "prepare pre_cordertypeflags" ) );
	
   /* declare for pre_ccustomergroupflags with open */
   exec sql declare cu_cordertypeflags cursor for pre_cordertypeflags;
   exec sql open cu_cordertypeflags using :cAart;
   VERIFY( verify( fun, "open cu_cordertypeflags" ) );

  return no_error;
 }

/*** END-BROWSE-CORDERTYPEFLAGS ********************************************************/

 rterror endBrowseCordertypeflags( )
 {
   const char *fun = "endBrowseCordertypeflags";

   exec sql close cu_cordertypeflags;
   VERIFY( verify( fun, "close cu_cordertypeflags" ) );

   return no_error;
 }

/*** GET-NEXT-ARTICLE **********************************************************/
 
 rterror GetNextArticle( dezapzartikelSTR *article )
 {
   exec sql begin declare section;
   dezapzartikelSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextArticle";

   d = article;	 
   memset( (char *)d, ' ', sizeof( dezapzartikelSTR ) );
   
   exec sql fetch cu_zartikel into :*d;
   VERIFY( verify( fun, "fetch cu_zartikel" ) );

   return no_error;
 }

/*** GET-NEXT-GROUP **********************************************************/
 
 rterror GetNextGroup( dezapzgrppflegeSTR *zgrppflege )
 {
   exec sql begin declare section;
   dezapzgrppflegeSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextGroup";

   d = zgrppflege;	 
   memset( (char *)d, ' ', sizeof( dezapzgrppflegeSTR ) );
   
   exec sql fetch cu_zgrppflege into :*d;

   VERIFY( verify( fun, "fetch cu_zgrppflege" ) );

   return no_error;
 }

/*** GET-NEXT-PZN **********************************************************/
 
 rterror GetNextPZN( dezapzpznpflegeSTR *zpznpflege )
 {
   exec sql begin declare section;
   dezapzpznpflegeSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextPZN";

   d = zpznpflege;	 
   memset( (char *)d, ' ', sizeof( dezapzpznpflegeSTR ) );
   
   exec sql fetch cu_zpznpflege into :*d;

   VERIFY( verify( fun, "fetch cu_zpznpflege" ) );

   return no_error;
 }

/*** GET-PRICE-OF-ARTICLE (only the first) *************************************/
 
 rterror GetPriceOfArticle( dezapzartpreisSTR *price )
 {
   exec sql begin declare section;
   dezapzartpreisSTR *d;
   exec sql end declare section;
   const char *fun = "GetPriceOfArticle";

   d = price;	 

   exec sql open cu_zartpreis using :d->ARTIKEL_NR, :d->DATUMGUELTIGAB;
   memset( (char *)d, ' ', sizeof( dezapzartpreisSTR ) ); 
   exec sql fetch cu_zartpreis into :*d;
   VERIFY( verify( fun, "fetch cu_zartpreis" ) ); 

   return no_error;
 }

/*** GET-SECONDARY-OF-ARTICLE (only the first) *********************************/
  rterror GetSecondaryOfArticle( dezapzartsekbezSTR *secondary )
 {
   exec sql begin declare section;
   dezapzartsekbezSTR *d;
   exec sql end declare section;
   const char *fun = "GetSecondaryOfArticle";

   d = secondary;	 
   exec sql open cu_zartsekbez using :d->ARTIKEL_NR;
   memset( (char *)d, ' ', sizeof( dezapzartsekbezSTR ) );
   exec sql fetch cu_zartsekbez into :*d;
   VERIFY( verify( fun, "fetch cu_zartsekbez" ) );

   return no_error;
 }

/*** GET-DEPOSIT-VALUE-OF-ARTICLE *********************************/
  rterror GetDepositValueOfArticle( dezapcdeposittypesSTR *deposittypes )
 {
   exec sql begin declare section;
   dezapcdeposittypesSTR *d;
   exec sql end declare section;
   const char *fun = "GetDepositValueOfArticle";

   d = deposittypes;	 
   exec sql open cu_cdeposittypes using :d->DEPOSIT_TYPE;
   memset( (char *)d, ' ', sizeof( dezapcdeposittypesSTR ) );
   exec sql fetch cu_cdeposittypes into :*d;
   VERIFY( verify( fun, "fetch cu_cdeposittypes" ) );

   return no_error;
 }

/*** GET-MANUFACTURER-OF-ARTICLE ***********************************************/

 rterror GetManufacturerOfArticle( dezapherstelSTR *manufacturer ) 
 {
   exec sql begin declare section;
   dezapherstelSTR *d;
   exec sql end declare section;
   const char *fun = "GetManufacturerOfArticle";

   d = manufacturer;	 
   exec sql open cu_herstel using :d->HERSTELLER_NR;
   memset( (char *)d, ' ', sizeof( dezapherstelSTR ) );
   exec sql fetch cu_herstel into :*d;
   VERIFY( verify( fun, "fetch cu_herstel" ) );

   return no_error;
 }

/*** GET-MANUFACTURER_DISPO ***********************************************/

 rterror GetManufacturer_Dispo( dezapherstel_dispoSTR *manufacturer_dispo ) 
 {
   exec sql begin declare section;
   dezapherstel_dispoSTR *d;
   exec sql end declare section;
   const char *fun = "GetManufacturer_Dispo";

   d = manufacturer_dispo;	 
   exec sql open cu_herstel_dispo using :d->HERSTELLER_NR;
   memset( (char *)d, ' ', sizeof( dezapherstel_dispoSTR ) );
   exec sql fetch cu_herstel_dispo into :*d;
   VERIFY( verify( fun, "fetch cu_herstel_dispo" ) );

   return no_error;
 }

/*** GET-EAN ***********************************************/

 rterror GetEan( dezapeanSTR *ean ) 
 {
   exec sql begin declare section;
   dezapeanSTR *d;
   exec sql end declare section;
   const char *fun = "GetEan";

   d = ean;
   exec sql open cu_ean using :d->ARTIKEL_NR;
   VERIFY( verify( fun, "open cu_ean" ) );
   memset( (char *)d, ' ', sizeof( dezapeanSTR ) );
   exec sql fetch cu_ean into :*d;
   VERIFY( verify( fun, "fetch cu_ean" ) );

   return no_error;
 }

/*** INIT-GOODS-GROUP-OF-ARTICLE ***********************************************/

 rterror InitGoodsgroupOfArticle( dezapzartwgSTR *goodsgroup )
 {
   exec sql begin declare section;
   dezapzartwgSTR *d;
   exec sql end declare section;
   const char *fun = "InitGoodsgroupOfArticle";

   d = goodsgroup;	 
   exec sql open cu_zartwg using :d->ARTIKEL_NR;
   VERIFY( verify( fun, "init cu_zartwg" ) );

   return no_error;
 }

/*** GET-GOODS-GROUP-OF-ARTICLE ************************************************/

 rterror GetGoodsgroupOfArticle( dezapzartwgSTR *goodsgroup )
 {
   exec sql begin declare section;
   dezapzartwgSTR *d;
   exec sql end declare section;
   const char *fun = "GetGoodsgroupOfArticle";

   d = goodsgroup;	 
   memset( (char *)d, ' ', sizeof( dezapzartwgSTR ) );
   exec sql fetch cu_zartwg into :*d;
   VERIFY( verify( fun, "fetch cu_zartwg" ) );

   return no_error;
 }															

/*** INIT-CODES ***********************************************/

 rterror InitCodes( dezapcarticlecodesSTR *articlecodes )
 {
   exec sql begin declare section;
   dezapcarticlecodesSTR *d;
   exec sql end declare section;
   const char *fun = "InitCodes";

   d = articlecodes;	 
   exec sql open cu_carticlecodes using :d->ARTICLENO;
   VERIFY( verify( fun, "init cu_carticlecodes" ) );

   return no_error;
 }

/*** GET-CODES ************************************************/

 rterror GetCodes( dezapcarticlecodesSTR *articlecodes )
 {
   exec sql begin declare section;
   dezapcarticlecodesSTR *d;
   exec sql end declare section;
   const char *fun = "GetCodes";

   d = articlecodes;	 
   memset( (char *)d, ' ', sizeof( dezapcarticlecodesSTR ) );
   exec sql fetch cu_carticlecodes into :*d;
   VERIFY( verify( fun, "fetch cu_carticlecodes" ) );

   return no_error;
 }															

/*** INIT-HSALESCONDITION ***********************************************/

 rterror InitHSalesCondition( dezaphsalescondSTR *hsalescond )
 {
   exec sql begin declare section;
   dezaphsalescondSTR *d;
   exec sql end declare section;
   const char *fun = "InitHSalesCondition";

   d = hsalescond;	 
   exec sql open cu_hsalescond using :d->HERSTELLER_NR;
   VERIFY( verify( fun, "init cu_hsalescond" ) );

   return no_error;
 }

/*** GET-HSALESCONDITION ************************************************/

 rterror GetHSalesCondition( dezaphsalescondSTR *hsalescond )
 {
   exec sql begin declare section;
   dezaphsalescondSTR *d;
   exec sql end declare section;
   const char *fun = "GetHSalesCondition";

   d = hsalescond;	 
   memset( (char *)d, ' ', sizeof( dezaphsalescondSTR ) );
   exec sql fetch cu_hsalescond into :*d;
   VERIFY( verify( fun, "fetch cu_hsalescond" ) );

   return no_error;
 }															

/*** INIT-CGALONAM ***********************************************

 rterror InitCgalonam( dezapcgalonamSTR *cgalonam )
 {
   exec sql begin declare section;
   dezapcgalonamSTR *d;
   exec sql end declare section;
   const char *fun = "InitCgalonam";

   d = cgalonam;	 
   exec sql open cu_cgalonam using :d->ARTICLENO;
   VERIFY( verify( fun, "init cu_cgalonam" ) );

   return no_error;
 } */

/*** GET-CGALONAM ************************************************

 rterror GetCgalonam( dezapcgalonamSTR *cgalonam )
 {
   exec sql begin declare section;
   dezapcgalonamSTR *d;
   exec sql end declare section;
   const char *fun = "GetCgalonam";

   d = cgalonam;	 
   memset( (char *)d, ' ', sizeof( dezapcgalonamSTR ) );
   exec sql fetch cu_cgalonam into :*d;

   VERIFY( verify( fun, "fetch cu_cgalonam" ) );

   return no_error;
 } */

/*** GET-FIXED-AMOUNT-OF-ARTICLE ***********************************************/

 rterror GetFixedAmountOfArticle( dezapzartfeb2STR *fixedamount )
 {
   exec sql begin declare section;
   dezapzartfeb2STR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetFixedAmountOfArticle";

   d = fixedamount;	 
   lArticleNo = d->ARTIKEL_NR; 
   memset( (char *)d, ' ', sizeof( dezapzartfeb2STR ) );
   exec sql execute pre_zartfeb2 into :*d using :lArticleNo;
   VERIFY( verify( fun, "fetch cu_zartfeb2" ) );

   return no_error;
 }

/*** GET-CSAFETYDATASHEET ***********************************************/

 rterror GetCsafetydatasheet( dezapcsafetydatasheetSTR *safetydatasheet )
 {
   exec sql begin declare section;
   dezapcsafetydatasheetSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetCsafetydatasheet";

   d = safetydatasheet;	 
   lArticleNo = d->ARTICLENO; 
   memset( (char *)d, ' ', sizeof( dezapcsafetydatasheetSTR ) );
   exec sql execute pre_csafetydatasheet into :*d using :lArticleNo;
   VERIFY( verify( fun, "fetch cu_csafetydatasheet" ) );

   return no_error;
 }

/*** GET-CARTICLEEXT ***********************************************/

 rterror GetCarticleext( dezapcarticleextSTR *articleext )
 {
   exec sql begin declare section;
   dezapcarticleextSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetCarticleext";

   d = articleext;	 
   lArticleNo = d->ARTICLENO; 
   memset( (char *)d, ' ', sizeof( dezapcarticleextSTR ) );
   exec sql execute pre_carticleext into :*d using :lArticleNo;
   VERIFY( verify( fun, "fetch cu_carticleext" ) );

   return no_error;
 }

/*** GET-ZAUTIDEMSPERRE ***********************************************/

 rterror GetZautidemsperre( dezapzautidemsperreSTR *zautidemsperre )
 {
   exec sql begin declare section;
   dezapzautidemsperreSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetZautidemsperre";

   d = zautidemsperre;	 
   lArticleNo = d->ARTIKEL_NR; 
   memset( (char *)d, ' ', sizeof( dezapzautidemsperreSTR ) );
   exec sql execute pre_zautidemsperre into :*d using :lArticleNo;
   VERIFY( verify( fun, "fetch cu_zautidemsperre" ) );

   return no_error;
 }

/*** GET-CGIBATCHENTRY ***********************************************

 rterror GetCgibatchentry( dezapcgibatchentrySTR *cgibatchentry )
 {
   exec sql begin declare section;
   dezapcgibatchentrySTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetCgibatchentry";

   d = cgibatchentry;	 
   lArticleNo = d->ARTICLENO; 
   memset( (char *)d, ' ', sizeof( dezapcgibatchentrySTR ) );
   exec sql execute pre_cgibatchentry into :*d using :lArticleNo;
   VERIFY( verify( fun, "fetch cu_cgibatchentry" ) );

   return no_error;
 } */

/*** GET-ARTVE ***********************************************/

 rterror GetArtve( dezapartveSTR *artve )
 {
   exec sql begin declare section;
   dezapartveSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetArtve";

   d = artve;	 
   lArticleNo = d->ARTIKEL_NR; 
   memset( (char *)d, ' ', sizeof( dezapartveSTR ) );
   exec sql execute pre_artve into :*d using :lArticleNo;
   VERIFY( verify( fun, "fetch cu_artve" ) );

   return no_error;
 }

/*** GET-ZARTIKEL ***********************************************/

 rterror GetZartikel( dezapzartikelSTR *zartikel )
 {
   exec sql begin declare section;
   dezapzartikelSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetZartikel";

   d = zartikel;	 
   lArticleNo = d->ARTIKEL_NR; 
   memset( (char *)d, ' ', sizeof( dezapzartikelSTR ) );
   exec sql execute pre_zartikel2 into :*d using :lArticleNo;
   VERIFY( verify( fun, "fetch cu_zartikel2" ) );

   return no_error;
 }

/*** GET-ZDKWGR ***********************************************/

 rterror GetZdkwgr( dezapzdkwgrSTR *zdkwgr )
 {
   exec sql begin declare section;
   dezapzdkwgrSTR *d;		
   char cWgr_Gruppe[6];
   exec sql end declare section;
   const char *fun = "GetZdkwgr";

   d = zdkwgr;	 
   strcpy (cWgr_Gruppe, d->WGR_GRUPPE); 
   memset( (char *)d, ' ', sizeof( dezapzdkwgrSTR ) );
   exec sql execute pre_zdkwgr into :*d using :cWgr_Gruppe;
   VERIFY( verify( fun, "fetch cu_zdkwgr" ) );

   return no_error;
 }

/*** GET-ZDKIWG ***********************************************/

 rterror GetZdkiwg( dezapzdkiwgSTR *zdkiwg )
 {
   exec sql begin declare section;
   dezapzdkiwgSTR *d;		
   char cWarengruppe[6];
   exec sql end declare section;
   const char *fun = "GetZdkiwg";

   d = zdkiwg;	 
   strcpy (cWarengruppe, d->WARENGRUPPE); 
   memset( (char *)d, ' ', sizeof( dezapzdkiwgSTR ) );
   exec sql execute pre_zdkiwg into :*d using :cWarengruppe;
   VERIFY( verify( fun, "fetch cu_zdkiwg" ) );

   return no_error;
 }

/*** GET-ZDKTGR ***********************************************/

 rterror GetZdktgr( dezapzdktgrSTR *zdktgr )
 {
   exec sql begin declare section;
   dezapzdktgrSTR *d;		
   char cTgr_Gruppe[6];
   exec sql end declare section;
   const char *fun = "GetZdktgr";

   d = zdktgr;	 
   strcpy (cTgr_Gruppe, d->TGR_GRUPPE); 
   memset( (char *)d, ' ', sizeof( dezapzdktgrSTR ) );
   exec sql execute pre_zdktgr into :*d using :cTgr_Gruppe;
   VERIFY( verify( fun, "fetch cu_zdktgr" ) );

   return no_error;
 }

/*** GET-ZRABGRP ***********************************************/

 rterror GetZrabgrp( dezapzrabgrpSTR *zrabgrp )
 {
   exec sql begin declare section;
   dezapzrabgrpSTR *d;		
   char cRabattgruppe[4];
   exec sql end declare section;
   const char *fun = "GetZrabgrp";

   d = zrabgrp;	 
   strcpy (cRabattgruppe, d->RABATTGRUPPE); 
   memset( (char *)d, ' ', sizeof( dezapzrabgrpSTR ) );
   exec sql execute pre_zrabgrp into :*d using :cRabattgruppe;
   VERIFY( verify( fun, "fetch cu_zrabgrp" ) );

   return no_error;
 }

/*** GET-ZZAHLBED ***********************************************/

 rterror GetZzahlbed( dezapzzahlbedSTR *zzahlbed )
 {
   exec sql begin declare section;
   dezapzzahlbedSTR *d;		
   char cZahlungsbedingung[5];
   exec sql end declare section;
   const char *fun = "GetZzahlbed";

   d = zzahlbed;	 
   strcpy (cZahlungsbedingung, d->ZAHLUNGSBEDINGUNG); 
   memset( (char *)d, ' ', sizeof( dezapzzahlbedSTR ) );
   exec sql execute pre_zzahlbed into :*d using :cZahlungsbedingung;
   VERIFY( verify( fun, "fetch cu_zzahlbed" ) );

   return no_error;
 }

/*** GET-CDISCMODEL ***********************************************/

 rterror GetCdiscmodel( dezapcdiscmodelSTR *cdiscmodel )
 {
   exec sql begin declare section;
   dezapcdiscmodelSTR *d;		
   short sdiscountmodelno;
   exec sql end declare section;
   const char *fun = "GetCdiscmodel";

   d = cdiscmodel;	 
   sdiscountmodelno = d->DISCOUNTMODELNO; 
   memset( (char *)d, ' ', sizeof( dezapcdiscmodelSTR ) );
   exec sql execute pre_cdiscmodel into :*d using :sdiscountmodelno;
   VERIFY( verify( fun, "fetch cu_cdiscmodel" ) );

   return no_error;
 }

/*** GET-CMONTHDISCSORT ***********************************************/

 rterror GetCmonthdiscsort( dezapcmonthdiscsortSTR *cmonthdiscsort )
 {
   exec sql begin declare section;
   dezapcmonthdiscsortSTR *d;		
   short smonthlydiscountgrp;
   exec sql end declare section;
   const char *fun = "GetCmonthdiscsort";

   d = cmonthdiscsort;	 
   smonthlydiscountgrp = d->MONTHLYDISCOUNTGRP;
   memset( (char *)d, ' ', sizeof( dezapcmonthdiscsortSTR ) );
   exec sql execute pre_cmonthdiscsort into :*d using :smonthlydiscountgrp;
   VERIFY( verify( fun, "fetch cu_cmonthdiscsort" ) );

   return no_error;
 }

/*** GET-CHIGHPAYMTARGETFEE ***********************************************/

 rterror GetChighpaymtargetfee( dezapchighpaymtargetfeeSTR *chighpaymtargetfee )
 {
   exec sql begin declare section;
   dezapchighpaymtargetfeeSTR *d;		
   char cKundenKlassifikation[2];
   short sAbAnzTage;
   exec sql end declare section;
   const char *fun = "GetChighpaymtargetfee";

   d = chighpaymtargetfee;	 
   strcpy (cKundenKlassifikation, d->CUSTCLASSIFICATION); 
   sAbAnzTage = d->FROMPAYMTARGETDAYS;
   memset( (char *)d, ' ', sizeof( dezapchighpaymtargetfeeSTR ) );
   exec sql execute pre_chighpaymtargetfee into :*d using :cKundenKlassifikation, :sAbAnzTage;
   VERIFY( verify( fun, "fetch cu_chighpaymtargetfee" ) );

   return no_error;
 }

/*** GET-CCUSTOMERGROUP ***********************************************/

 rterror GetCcustomergroup( dezapccustomergroupSTR *ccustomergroup )
 {
   exec sql begin declare section;
   dezapccustomergroupSTR *d;
   short customergroupno;
   exec sql end declare section;
   const char *fun = "GetCcustomergroup";

   d = ccustomergroup;	 
   customergroupno = d->CUSTOMERGROUPNO;
   memset( (char *)d, ' ', sizeof( dezapccustomergroupSTR ) );
   exec sql execute pre_ccustomergroup into :*d using :customergroupno;
   VERIFY( verify( fun, "fetch cu_ccustomergroup" ) );

   return no_error;
 }

/*** GET-CORDERTYPE ***********************************************/

 rterror GetCordertype( dezapcordertypeSTR *cordertype )
 {
   exec sql begin declare section;
   dezapcordertypeSTR *d;
   char cscordertype[3];
   exec sql end declare section;
   const char *fun = "GetCordertype";

   d = cordertype;	 
   strcpy (cscordertype, d->CSCORDERTYPE);
   memset( (char *)d, ' ', sizeof( dezapcordertypeSTR ) );
   exec sql execute pre_cordertype into :*d using :cscordertype;
   VERIFY( verify( fun, "fetch cu_cordertype" ) );

   return no_error;
 }

/*** GET-CMONTHVIRTSORT ***********************************************/

 rterror GetCmonthvirtsort( dezapcmonthvirtsortSTR *cmonthvirtsort )
 {
   exec sql begin declare section;
   dezapcmonthvirtsortSTR *d;		
   short smonthlyvirtualgroup;
   exec sql end declare section;
   const char *fun = "GetCmonthvirtsort";

   d = cmonthvirtsort;	 
   smonthlyvirtualgroup = d->MONTHLYVIRTUALGROUP;
   memset( (char *)d, ' ', sizeof( dezapcmonthvirtsortSTR ) );
   exec sql execute pre_cmonthvirtsort into :*d using :smonthlyvirtualgroup;
   VERIFY( verify( fun, "fetch cu_cmonthvirtsort" ) );

   return no_error;
 }

/*** GET-CCUSTSERVICES ***********************************************

 rterror GetCcustservices( dezapccustservicesSTR *ccustservices )
 {
   exec sql begin declare section;
   dezapccustservicesSTR *d;		
   short sservice_no;
   exec sql end declare section;
   const char *fun = "GetCcustservices";

   d = ccustservices;	 
   sservice_no = d->SERVICE_NO;
   memset( (char *)d, ' ', sizeof( dezapccustservicesSTR ) );
   exec sql execute pre_ccustservices into :*d using :sservice_no;
   VERIFY( verify( fun, "fetch cu_ccustservices" ) );

   return no_error;
 } */

/*** GET-CSTORAGECRITERIA ***********************************************/

 rterror GetCstoragecriteria( dezapcstoragecriteriaSTR *cstoragecriteria )
 {
   exec sql begin declare section;
   dezapcstoragecriteriaSTR *d;		
   short sstoragecriteriano;
   exec sql end declare section;
   const char *fun = "GetCstoragecriteria";

   d = cstoragecriteria;	 
   sstoragecriteriano = d->STORAGECRITERIANO;
   memset( (char *)d, ' ', sizeof( dezapcstoragecriteriaSTR ) );
   exec sql execute pre_cstoragecriteria into :*d using :sstoragecriteriano;
   VERIFY( verify( fun, "fetch cu_cstoragecriteria" ) );

   return no_error;
 }

/*** GET-CINTRASTATCOUNTRY ***********************************************/

 rterror GetCintrastatcountry( dezapcintrastatcountrySTR *cintrastatcountry )
 {
   exec sql begin declare section;
   dezapcintrastatcountrySTR *d;		
   char ccountrycode[3];
   exec sql end declare section;
   const char *fun = "GetCintrastatcountry";

   d = cintrastatcountry;	 
   strcpy (ccountrycode, d->COUNTRYCODE); 
   memset( (char *)d, ' ', sizeof( dezapcintrastatcountrySTR ) );
   exec sql execute pre_cintrastatcountry into :*d using :ccountrycode;
   VERIFY( verify( fun, "fetch cu_cintrastatcountry" ) );

   return no_error;
 }

/*** GET-CFORMTYPES ***********************************************/

 rterror GetCformtypes( dezapcformtypesSTR *cformtypes )
 {
   exec sql begin declare section;
   dezapcformtypesSTR *d;		
   char cFormtype[3];
   exec sql end declare section;
   const char *fun = "GetCformtypes";

   d = cformtypes;	 
   strcpy (cFormtype, d->FORMTYPE); 
   memset( (char *)d, ' ', sizeof( dezapcformtypesSTR ) );
   exec sql execute pre_cformtypes into :*d using :cFormtype;
   VERIFY( verify( fun, "fetch cu_cformtypes" ) );

   return no_error;
 }

/*** GET-CDISCFORM ***********************************************/

 rterror GetCdiscform( dezapcdiscformSTR *cdiscform )
 {
   exec sql begin declare section;
   dezapcdiscformSTR *d;		
   short sdiscountformno;
   exec sql end declare section;
   const char *fun = "GetCdiscform";

   d = cdiscform;	 
   sdiscountformno = d->DISCOUNTFORMNO;
   memset( (char *)d, ' ', sizeof( dezapcdiscformSTR ) );
   exec sql execute pre_cdiscform into :*d using :sdiscountformno;
   VERIFY( verify( fun, "fetch cu_cdiscform" ) );

   return no_error;
 }

/*** GET-CSHIPPER ***********************************************/

 rterror GetCshipper( dezapcshipperSTR *cshipper )
 {
   exec sql begin declare section;
   dezapcshipperSTR *d;		
   short sshipperno;
   exec sql end declare section;
   const char *fun = "GetCshipper";

   d = cshipper;	 
   sshipperno = d->SHIPPERNO;
   memset( (char *)d, ' ', sizeof( dezapcshipperSTR ) );
   exec sql execute pre_cshipper into :*d using :sshipperno;
   VERIFY( verify( fun, "fetch cu_cshipper" ) );

   return no_error;
 }

/*** GET-CPROMOTIONS ***********************************************/

 rterror GetCpromotions( dezapcpromotionsSTR *cpromotions )
 {
   exec sql begin declare section;
   dezapcpromotionsSTR *d;		
   short spromono;
   exec sql end declare section;
   const char *fun = "GetCpromotions";

   d = cpromotions;	 
   spromono = d->PROMOTION_NO;
   memset( (char *)d, ' ', sizeof( dezapcpromotionsSTR ) );
   exec sql execute pre_cpromotions into :*d using :spromono;
   VERIFY( verify( fun, "fetch cu_cpromotions" ) );

   return no_error;
 }

/*** GET-CREGISTERS ***********************************************/

 rterror GetCregisters( dezapcregistersSTR *cregisters )
 {
   exec sql begin declare section;
   dezapcregistersSTR *d;		
   char ministryproductcode[5];
   exec sql end declare section;
   const char *fun = "GetCregisters";

   d = cregisters;	 
   strncpy (ministryproductcode, d->MINISTRYPRODUCTCODE, 5); 
   memset( (char *)d, ' ', sizeof( dezapcregistersSTR ) );
   exec sql execute pre_cregisters into :*d using :ministryproductcode;
   VERIFY( verify( fun, "fetch cu_cregisters" ) );

   return no_error;
 }


/*** GET-CDISCLIST ***********************************************/

 rterror GetCdisclist( dezapcdisclistSTR *cdisclist )
 {
   exec sql begin declare section;
   dezapcdisclistSTR *d;		
   char cAuftragsart[3];
   char cSubauftragsart[4];
   exec sql end declare section;
   const char *fun = "GetCdisclist";

   d = cdisclist;	 
   strcpy (cAuftragsart, d->ORDER_TYPE); 
   strcpy (cSubauftragsart, d->SUB_ORDER_TYPE); 
   memset( (char *)d, ' ', sizeof( dezapcdisclistSTR ) );
   exec sql execute pre_cdisclist into :*d using :cAuftragsart, :cSubauftragsart;
   VERIFY( verify( fun, "fetch cu_cdisclist" ) );

   return no_error;
 }

/*** GET-CSERVICES ***********************************************/

 rterror GetCservices( dezapcservicesSTR *cservices )
 {
   exec sql begin declare section;
   dezapcservicesSTR *d;		
   short service_no;
   exec sql end declare section;
   const char *fun = "GetCservices";

   d = cservices;
   service_no = d->SERVICE_NO;
   memset( (char *)d, ' ', sizeof( dezapcservicesSTR ) );
   exec sql execute pre_cservices into :*d using :service_no;
   VERIFY( verify( fun, "fetch cu_cservices" ) );

   return no_error;
 }

/*** GET-ZDKWIR ***********************************************

 rterror GetZdkwir( dezapzdkwirSTR *zdkwir )
 {
   exec sql begin declare section;
   dezapzdkwirSTR *d;		
   char cWir_Bereich[4];
   exec sql end declare section;
   const char *fun = "GetZdkwir";

   d = zdkwir;	 
   strcpy (cWir_Bereich, d->WIR_BEREICH); 
   memset( (char *)d, ' ', sizeof( dezapzdkwirSTR ) );
   exec sql execute pre_zdkwir into :*d using :cWir_Bereich;
   VERIFY( verify( fun, "fetch cu_zdkwir" ) );

   return no_error;
 } */

/*** GET-AUSTRIAN-FIELDS ***********************************************/

 rterror GetAustrianFields( dezapzartaustriaSTR *austria )
 {
   exec sql begin declare section;
   dezapzartaustriaSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetAustrianFields";

   d = austria;	 
   lArticleNo = d->ARTIKEL_NR; 
   memset( (char *)d, ' ', sizeof( dezapzartaustriaSTR ) );
   exec sql execute pre_zartaustria into :*d using :lArticleNo; 
   VERIFY( verify( fun, "fetch cu_zartaustria" ) );

   return no_error;
 }

/*** GET-CROATIAN-FIELDS ***********************************************/

 rterror GetCroatianFields( dezapzartcroatiaSTR *croatia )
 {
   exec sql begin declare section;
   dezapzartcroatiaSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetCroatianFields";

   d = croatia;	 
   lArticleNo = d->ARTICLENO; 
   memset( (char *)d, ' ', sizeof( dezapzartcroatiaSTR ) );
   exec sql execute pre_zartcroatia into :*d using :lArticleNo; 
   VERIFY( verify( fun, "fetch cu_zartcroatia" ) );

   return no_error;
 }

/*** GET-BULGARIAN-FIELDS ***********************************************/

 rterror GetBulgarianFields( dezapzartbulgariaSTR *bulgaria )
 {
   exec sql begin declare section;
   dezapzartbulgariaSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetBulgarianFields";

   d = bulgaria;	 
   lArticleNo = d->ARTICLENO; 
   memset( (char *)d, ' ', sizeof( dezapzartbulgariaSTR ) );
   exec sql execute pre_zartbulgaria into :*d using :lArticleNo; 
   VERIFY( verify( fun, "fetch cu_zartbulgaria" ) );

   return no_error;
 }

/*** GET-SERBIAN-FIELDS ***********************************************/

 rterror GetSerbianFields( dezapzartserbiaSTR *serbia )
 {
   exec sql begin declare section;
   dezapzartserbiaSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetSerbianFields";

   d = serbia;	 
   lArticleNo = d->ARTICLENO; 
   memset( (char *)d, ' ', sizeof( dezapzartserbiaSTR ) );
   exec sql execute pre_zartserbia into :*d using :lArticleNo; 
   VERIFY( verify( fun, "fetch cu_zartserbia" ) );

   return no_error;
 }

/*** GET-SWISS-FIELDS ***********************************************/

 rterror GetSwissFields(  dezapzartswitzerlandSTR *switzerland )
 {
   exec sql begin declare section;
   dezapzartswitzerlandSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetSwissFields";

   d = switzerland;	 
   lArticleNo = d->ARTIKEL_NR; 
   memset( (char *)d, ' ', sizeof( dezapzartswitzerlandSTR ) );
   exec sql execute pre_zartswitzerland into :*d using :lArticleNo; 
   VERIFY( verify( fun, "fetch cu_zartswitzerland" ) );

   return no_error;
 }

/*** GET-FRENCH-FIELDS ***********************************************/

 rterror GetFrenchFields(  dezapzartfranceSTR *france )
 {
   exec sql begin declare section;
   dezapzartfranceSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetFrenchFields";

   d = france;	 
   lArticleNo = d->ARTICLENO; 
   memset( (char *)d, ' ', sizeof( dezapzartfranceSTR ) );
   exec sql execute pre_zartfrance into :*d using :lArticleNo; 
   VERIFY( verify( fun, "fetch cu_zartfrance" ) );

   return no_error;
 }

/*** GET-CARTICLETEXT ***********************************************/

 rterror GetCarticletext( dezapcarticletextSTR *carticletext )
 {
   exec sql begin declare section;
   dezapcarticletextSTR *d;		
   char cAtx_Tx[3];
   exec sql end declare section;
   const char *fun = "GetCarticletext";

   d = carticletext;	 
   strcpy (cAtx_Tx, d->TEXTNO); 
   memset( (char *)d, ' ', sizeof( dezapcarticletextSTR ) );
   exec sql execute pre_carticletext into :*d using :cAtx_Tx;
   VERIFY( verify( fun, "fetch cu_carticletext" ) );

   return no_error;
 }

/*** GET-CGALOCOM ***********************************************

 rterror GetCgalocom( dezapcgalocomSTR *cgalocom )
 {
   exec sql begin declare section;
   dezapcgalocomSTR *d;		
   long lComp_no;
   exec sql end declare section;
   const char *fun = "GetCgalocom";

   d = cgalocom;	 
   lComp_no = d->COMP_NO; 
   memset( (char *)d, ' ', sizeof( dezapcgalocomSTR ) );
   exec sql execute pre_cgalocom into :*d using :lComp_no;
   VERIFY( verify( fun, "fetch cu_cgalocom" ) );

   return no_error;
 } */

/*** GET-CPHARMGRP ***********************************************/

 rterror GetCpharmgrp( dezapcpharmgrpSTR *cpharmgrp )
 {
   exec sql begin declare section;
   dezapcpharmgrpSTR *d;		
   char cEgr_Gruppe[4];
   exec sql end declare section;
   const char *fun = "GetCpharmgrp";

   d = cpharmgrp;	 
   strcpy (cEgr_Gruppe, d->PHARMACYGROUPID); 
   memset( (char *)d, ' ', sizeof( dezapcpharmgrpSTR ) );
   exec sql execute pre_cpharmgrp into :*d using :cEgr_Gruppe;
   VERIFY( verify( fun, "fetch cu_cpharmgrp" ) );

   return no_error;
 }

/*** GET-NEXT-ZCHARGENRUECKRUF **********************************************************/
 
 rterror GetNextZchargenrueckruf( dezapzchargenrueckrufSTR *zchargenrueckruf )
 {
   exec sql begin declare section;
   dezapzchargenrueckrufSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextZchargenrueckruf";

   d = zchargenrueckruf;	 
   memset( (char *)d, ' ', sizeof( dezapzchargenrueckrufSTR ) );
   
   exec sql fetch cu_zchargenrueckruf into :*d;

   VERIFY( verify( fun, "fetch cu_zchargenrueckruf" ) );

   return no_error;
 }

/*** GET-NEXT-CBASELISTARTICLES **********************************************************/
 
 rterror GetNextCbaselistarticles( dezapcbaselistarticlesSTR *cbaselistarticles )
 {
   exec sql begin declare section;
   dezapcbaselistarticlesSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCbaselistarticles";

   d = cbaselistarticles;	 
   memset( (char *)d, ' ', sizeof( dezapcbaselistarticlesSTR ) );
   
   exec sql fetch cu_cbaselistarticles into :*d;

   VERIFY( verify( fun, "fetch cu_cbaselistarticles" ) );

   return no_error;
 }

/*** GET-NEXT-CARTICLECODES **********************************************************/
 
 rterror GetNextCarticlecodes( dezapcarticlecodesSTR *carticlecodes )
 {
   exec sql begin declare section;
   dezapcarticlecodesSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCarticlecodes";

   d = carticlecodes;	 
   memset( (char *)d, ' ', sizeof( dezapcarticlecodesSTR ) );
   
   exec sql fetch cu_carticlecodes_34 into :*d;

   VERIFY( verify( fun, "fetch cu_carticlecodes_34" ) );

   return no_error;
 }

/*** GET-NEXT-CDISCOUNT_PZN **********************************************************/
 
 rterror GetNextCdiscount_Pzn( dezapcdiscountSTR *cdiscount )
 {
   exec sql begin declare section;
   dezapcdiscountSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCdiscount_Pzn";

   d = cdiscount;	 
   memset( (char *)d, ' ', sizeof( dezapcdiscountSTR ) );
   
   exec sql fetch cu_cdiscount_pzn into :*d;

   VERIFY( verify( fun, "fetch cu_cdiscount_pzn" ) );

   return no_error;
 }

/*** GET-NEXT-CDISCOUNT_RPG **********************************************************/
 
 rterror GetNextCdiscount_Rpg( dezapcdiscountSTR *cdiscount )
 {
   exec sql begin declare section;
   dezapcdiscountSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCdiscount_Rpg";

   d = cdiscount;	 
   memset( (char *)d, ' ', sizeof( dezapcdiscountSTR ) );
   
   exec sql fetch cu_cdiscount_rpg into :*d;

   VERIFY( verify( fun, "fetch cu_cdiscount_rpg" ) );

   return no_error;
 }

/*** GET-NEXT-CDISCOUNT_HNR **********************************************************/
 
 rterror GetNextCdiscount_Hnr( dezapcdiscountSTR *cdiscount )
 {
   exec sql begin declare section;
   dezapcdiscountSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCdiscount_Hnr";

   d = cdiscount;	 
   memset( (char *)d, ' ', sizeof( dezapcdiscountSTR ) );
   
   exec sql fetch cu_cdiscount_hnr into :*d;

   VERIFY( verify( fun, "fetch cu_cdiscount_hnr" ) );

   return no_error;
 }

/*** GET-NEXT-CDISCOUNT_AGN **********************************************************/
 
 rterror GetNextCdiscount_Agn( dezapcdiscountSTR *cdiscount )
 {
   exec sql begin declare section;
   dezapcdiscountSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCdiscount_Agn";

   d = cdiscount;	 
   memset( (char *)d, ' ', sizeof( dezapcdiscountSTR ) );
   
   exec sql fetch cu_cdiscount_agn into :*d;

   VERIFY( verify( fun, "fetch cu_cdiscount_agn" ) );

   return no_error;
 }

/*** GET-NEXT-CARTCOMPACK **********************************************************/
 
 rterror GetNextCartcompack( dezapcartcompackSTR *cartcompack )
 {
   exec sql begin declare section;
   dezapcartcompackSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCartcompack";

   d = cartcompack;	 
   memset( (char *)d, ' ', sizeof( dezapcartcompackSTR ) );
   
   exec sql fetch cu_cartcompack into :*d;

   VERIFY( verify( fun, "fetch cu_cartcompack" ) );

   return no_error;
 }

/*** GET-NEXT-ZARTVERK **********************************************************/
 
 rterror GetNextZartverk( dezapzartverkSTR *zartverk )
 {
   exec sql begin declare section;
   dezapzartverkSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextZartverk";

   d = zartverk;	 
   memset( (char *)d, ' ', sizeof( dezapzartverkSTR ) );
   
   exec sql fetch cu_zartverk into :*d;

   VERIFY( verify( fun, "fetch cu_zartverk" ) );

   return no_error;
 }

/*** GET-NEXT-CDISCGRPMEM **********************************************************/
 
 rterror GetNextCdiscgrpmem( dezapcdiscgrpmemSTR *cdiscgrpmem )
 {
   exec sql begin declare section;
   dezapcdiscgrpmemSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCdiscgrpmem";

   d = cdiscgrpmem;	 
   memset( (char *)d, ' ', sizeof( dezapcdiscgrpmemSTR ) );
   
   exec sql fetch cu_cdiscgrpmem into :*d;

   VERIFY( verify( fun, "fetch cu_cdiscgrpmem" ) );

   return no_error;
 }

/*** GET-NEXT-CCUSTOMERGRPFLAGS **********************************************************/
 
 rterror GetNextCcustomergrpflags( dezapccustomergrpflagSTR *ccustomergrpflag )
 {
   exec sql begin declare section;
   dezapccustomergrpflagSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCcustomergrpflags";

   d = ccustomergrpflag;	 
   memset( (char *)d, ' ', sizeof( dezapccustomergrpflagSTR ) );
   
   exec sql fetch cu_ccustomergroupflags into :*d;

   VERIFY( verify( fun, "fetch cu_ccustomergroupflags" ) );

   return no_error;
 }

/*** GET-NEXT-CORDERTYPEFLAGS **********************************************************/
 rterror GetNextCordertypeflags( dezapcordertypeflagSTR *cordertypeflag )
 {
   exec sql begin declare section;
   dezapcordertypeflagSTR *d;
   exec sql end declare section;
   const char *fun = "GetNextCordertypeflags";

   d = cordertypeflag;	 
   memset( (char *)d, ' ', sizeof( dezapcordertypeflagSTR ) );
   
   exec sql fetch cu_cordertypeflags into :*d;

   VERIFY( verify( fun, "fetch cu_cordertypeflags" ) );

   return no_error;
 }

/*** GET-CARTICLELANG ***********************************************/

 rterror GetCarticlelang( dezapcarticlelangSTR *carticlelang )
 {
   exec sql begin declare section;
   dezapcarticlelangSTR *d;		
   long lArticleNo;
   char clangid[3];
   exec sql end declare section;
   const char *fun = "GetCarticlelang";

   d = carticlelang;

   strcpy (clangid, d->LANGID);
   lArticleNo = d->ARTICLENO;

   memset( (char *)d, ' ', sizeof( dezapcarticlelangSTR ) );
   exec sql execute pre_carticlelang into :*d using :lArticleNo, :clangid;
   VERIFY( verify( fun, "fetch cu_carticlelang" ) );

   return no_error;
 }

/*** GET-CCPVALIDITYPERIOD ***********************************************/

 rterror GetCcpvalidityperiod( dezapccpvalidityperiodSTR *ccpvalidityperiod )
 {
   exec sql begin declare section;
   dezapccpvalidityperiodSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetCcpvalidityperiod";

   d = ccpvalidityperiod;

   lArticleNo = d->ARTICLE_NO_PACK;

   memset( (char *)d, ' ', sizeof( dezapccpvalidityperiodSTR ) );
   exec sql execute pre_ccpvalidityperiod into :*d using :lArticleNo;
   VERIFY( verify( fun, "fetch cu_ccpvalidityperiod" ) );

   return no_error;
 }

/*** GET-CDISCGRP ***********************************************/

 rterror GetCdiscgrp( dezapcdiscgrpSTR *cdiscgrp )
 {
   exec sql begin declare section;
   dezapcdiscgrpSTR *d;		
   long lDiscountGrpNo;
   exec sql end declare section;
   const char *fun = "GetCdiscgrp";

   d = cdiscgrp;

   lDiscountGrpNo = d->DISCOUNTGRPNO;

   memset( (char *)d, ' ', sizeof( dezapcdiscgrpSTR ) );
   exec sql execute pre_cdiscgrp into :*d using :lDiscountGrpNo;
   VERIFY( verify( fun, "fetch cu_cdiscgrp" ) );

   return no_error;
 }

/*** GET-CGALOART ***********************************************

 rterror GetCgaloart( dezapcgaloartSTR *cgaloart )
 {
   exec sql begin declare section;
   dezapcgaloartSTR *d;		
   long lArticleNo;
   exec sql end declare section;
   const char *fun = "GetCgaloart";

   d = cgaloart;

   lArticleNo = d->ARTICLENO; 

   memset( (char *)d, ' ', sizeof( dezapcgaloartSTR ) );
   exec sql execute pre_cgaloart into :*d using :lArticleNo;
   VERIFY( verify( fun, "fetch cu_cgaloart" ) );

   return no_error;
 } */

/*** DELETE-NEXT-ARTICLE *******************************************************/
 
 rterror DeleteNextArticle( void )
 {
   const char *fun = "DeleteNextArticle";

   exec sql fetch cu_zapflege;
   VERIFY( verify( fun, "fetch cu_zapflege" ) );
   exec sql execute del_zapflege;

   return no_error;
 }

 /*** DELETE-NEXT-GROUP *******************************************************/
 
 rterror DeleteNextGroup( void )
 {
   const char *fun = "DeleteNextGroup";

   exec sql fetch cu_delzgrppflege;
   VERIFY( verify( fun, "fetch cu_delzgrppflege" ) );
   exec sql execute del_zgrppflege;

   return no_error;
 }

 /*** DELETE-NEXT-PZN *******************************************************/
 
 rterror DeleteNextPZN( void )
 {
   const char *fun = "DeleteNextPZN";

   exec sql fetch cu_delzpznpflege;
   VERIFY( verify( fun, "fetch cu_delzpznpflege" ) );
   exec sql execute del_zpznpflege;

   return no_error;
 }
