#include <stddef.h>         
#include <stdio.h>          
#include <pxrecord.h>       
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include <pxenv.h>
#include <tvartikellokal.h>
#include <keys.h>

extern int  functionnr;

#define UNUSED(x) (void)(x)

/*--------------------------------------------------------------------------------------------------*/
int pxVartikelLokalStartBrowse( struct tVARTIKELLOKAL* record, short timecheck, short useview, short weekday, long currenttime, int browseid)
{
	EXEC SQL BEGIN DECLARE SECTION;
		struct C_VARTIKELLOKAL* recordp;
		char query[3000] = {' '};						
	EXEC SQL END DECLARE SECTION;

	char useVartikellokal[20] = {' '};		
	char joinTimeTypes[100] = {' '};
	char whereTimeTypes[120] = {' '};	

	EXEC SQL SET ISOLATION TO DIRTY READ;

    recordp = (struct C_VARTIKELLOKAL*) record;	

	// vartikellokal oder artikellokal?
	if( useview > 0 )
	{
		sprintf( useVartikellokal, "vartikellokal" );
	}
	else
	{
		sprintf( useVartikellokal, "artikellokal" );
	}	

	switch( browseid )
	{				
		case cCRS_IBTBRANCHES_NLEVELIBT_INACTIVE: // TourManager aktiv, NLevelIBT aktiv, außerhalb Filialverbundfenster
			sprintf( query,
				"SELECT 0, min(ib.priority), ib.ibtbranchno, icfg.articleno, vbart.bestand, vbart.artikelaktiv, vbart.verbundartikel, ib.nlevelibttypeid, case when NVL(CAST(za.zeitschluessel AS INTEGER),0) > 0 then 1 else 0 end as active "
				"FROM ibtbranches ib "
				"JOIN ibtbrancharticleconfig icfg ON icfg.branchno=ib.branchno AND icfg.ibtassortmenttypeid=ib.nlevelibtassortmenttypeid AND icfg.ibttypeid=ib.nlevelibttypeid "
				"JOIN %s vbart ON vbart.filialnr=ib.ibtbranchno AND vbart.artikel_nr=icfg.articleno " // %s = useVartikellokal
				"LEFT JOIN zeitarten za ON za.vertriebszentrumnr=ib.branchno AND za.zeitart=2 and CAST(za.zeitschluessel AS INTEGER)=ib.ibtbranchno "
				"AND za.zeitbegin <= %ld AND za.zeitende >= %ld AND za.weekday = %d " // %ld = currenttime, %ld = currenttime, %d = weekday
				"WHERE ib.nlevelibttypeid>0 AND ib.active_flag=1 AND ib.branchno=%d AND icfg.articleno=%ld " // %d = recordp->FILIALNR, %ld = recordp->ARTIKEL_NR
				"AND vbart.bestand>=0 AND vbart.artikelaktiv='1' AND icfg.ibttypeid > 0 "
				"AND ib.ibtbranchno IN (SELECT CAST(z.zeitschluessel AS integer) FROM zeitarten z WHERE z.zeitart=2 AND CAST(z.zeitschluessel AS integer)=ib.ibtbranchno AND z.vertriebszentrumnr=ib.branchno) "
				"GROUP BY 1, ib.ibtbranchno, icfg.articleno, vbart.bestand, vbart.artikelaktiv, vbart.verbundartikel, ib.nlevelibttypeid, za.zeitschluessel "
				"UNION "
				"SELECT 1, min(ib.priority), ib.ibtbranchno, icfg.articleno, vbart.bestand, vbart.artikelaktiv, vbart.verbundartikel, ib.nlevelibttypeid, case when NVL(CAST(za.zeitschluessel AS INTEGER),0) > 0 then 1 else 0 end as active "
				"FROM ibtbranches ib "
				"JOIN ibtbrancharticleconfig icfg ON icfg.branchno=ib.branchno AND icfg.ibtassortmenttypeid=ib.nlevelibtassortmenttypeid "
				"JOIN %s vbart ON vbart.filialnr=ib.ibtbranchno AND vbart.artikel_nr=icfg.articleno " // %s = useVartikellokal
				"LEFT JOIN zeitarten za ON za.vertriebszentrumnr=ib.branchno AND za.zeitart=2 and CAST(za.zeitschluessel AS INTEGER)=ib.ibtbranchno "
				"AND za.zeitbegin <= %ld AND za.zeitende >= %ld AND za.weekday = %d " // %ld = currenttime, %ld = currenttime, %d = weekday
				"WHERE ib.nlevelibttypeid>0 AND ib.active_flag=1 AND ib.branchno=%d AND icfg.articleno=%ld and ib.nlevelibttypeid=3 " // %d = recordp->FILIALNR, %ld = recordp->ARTIKEL_NR
				"AND vbart.bestand>=0 AND vbart.artikelaktiv='1' AND icfg.ibttypeid > 0 "
				"AND ib.ibtbranchno IN (SELECT CAST(z.zeitschluessel AS integer) FROM zeitarten z WHERE z.zeitart=2 AND CAST(z.zeitschluessel AS integer)=ib.ibtbranchno AND z.vertriebszentrumnr=ib.branchno) "
				"GROUP BY 1, ib.ibtbranchno, icfg.articleno, vbart.bestand, vbart.artikelaktiv, vbart.verbundartikel, ib.nlevelibttypeid, za.zeitschluessel "
				"ORDER BY 1, 2; "
				, useVartikellokal, currenttime, currenttime, weekday, recordp->FILIALNR, recordp->ARTIKEL_NR
				, useVartikellokal, currenttime, currenttime, weekday, recordp->FILIALNR, recordp->ARTIKEL_NR
			);
			break;

		case cCRS_IBTBRANCHES_NLEVELIBT: // TourManager aktiv, NLevelIBT aktiv, innerhalb Filialverbundfenster
			if( timecheck > 0 )
			{		
				sprintf( joinTimeTypes, "JOIN zeitarten za ON za.vertriebszentrumnr=ib.branchno AND za.zeitschluessel=ib.ibtbranchno" );
				sprintf( whereTimeTypes, "AND za.zeitart = 2 AND za.zeitbegin <= %ld AND za.zeitende >= %ld AND za.weekday = %d", currenttime, currenttime, weekday );				
			}		
			sprintf( query,
				"SELECT 0, min(ib.priority), ib.ibtbranchno, icfg.articleno, vbart.bestand, vbart.artikelaktiv, vbart.verbundartikel, ib.nlevelibttypeid, para.ibtqtyavailabilitypercentage " // first column for order by
				"FROM ibtbranches ib "
				"JOIN ibtbrancharticleconfig icfg ON icfg.branchno=ib.branchno AND icfg.ibtassortmenttypeid=ib.nlevelibtassortmenttypeid AND icfg.ibttypeid=ib.nlevelibttypeid "
				" %s " // %s => joinTimeTypes
				"JOIN %s vbart ON vbart.filialnr=ib.ibtbranchno AND vbart.artikel_nr=icfg.articleno " // %s => useVartikellokal
				"JOIN paraauftragbearb para ON para.filialnr=ib.branchno "
				"WHERE ib.nlevelibttypeid>0 AND ib.active_flag=1 AND ib.branchno=%d AND icfg.articleno=%ld " // %d => recordp->FILIALNR, %ld => recordp->ARTIKEL_NR
				" %s " // %s => whereTimeTypes
				"AND vbart.bestand>0 AND vbart.artikelaktiv='1' AND icfg.ibttypeid > 0 "
				"GROUP BY 1, ib.ibtbranchno, icfg.articleno, vbart.bestand, vbart.artikelaktiv, vbart.verbundartikel, ib.nlevelibttypeid, para.ibtqtyavailabilitypercentage "
				"UNION "
				"SELECT 1, min(ib.priority), ib.ibtbranchno, icfg.articleno, vbart.bestand, vbart.artikelaktiv, vbart.verbundartikel, ib.nlevelibttypeid, para.ibtqtyavailabilitypercentage " // first column for order by
				"FROM ibtbranches ib "
				"JOIN ibtbrancharticleconfig icfg ON icfg.branchno=ib.branchno AND icfg.ibtassortmenttypeid=ib.nlevelibtassortmenttypeid "
				" %s " // %s => joinTimeTypes
				"JOIN %s vbart ON vbart.filialnr=ib.ibtbranchno AND vbart.artikel_nr=icfg.articleno " // %s => useVartikellokal
				"JOIN paraauftragbearb para ON para.filialnr=ib.branchno "
				"WHERE ib.nlevelibttypeid>0 AND ib.active_flag=1 AND ib.branchno=%d AND icfg.articleno=%ld and ib.nlevelibttypeid=3 " // %d => recordp->FILIALNR, %ld => recordp->ARTIKEL_NR
				" %s " // %s => whereTimeTypes
				"AND vbart.bestand>0 AND vbart.artikelaktiv='1' AND icfg.ibttypeid > 0 "
				"GROUP BY 1, ib.ibtbranchno, icfg.articleno, vbart.bestand, vbart.artikelaktiv, vbart.verbundartikel, ib.nlevelibttypeid, para.ibtqtyavailabilitypercentage "
				"ORDER BY 1, 2; "
				, joinTimeTypes, useVartikellokal, recordp->FILIALNR, recordp->ARTIKEL_NR, whereTimeTypes
				, joinTimeTypes, useVartikellokal, recordp->FILIALNR, recordp->ARTIKEL_NR, whereTimeTypes				
				);
			break;

		case cCRS_IBTBRANCHES: // TourManager aktiv, Kein NLevelIBT
		default:
			if( timecheck > 0 )
			{		
				sprintf( joinTimeTypes, "JOIN zeitarten za ON za.vertriebszentrumnr=ib.branchno AND za.zeitschluessel=ib.ibtbranchno" );
				sprintf( whereTimeTypes, "AND za.zeitart = 2 AND za.zeitbegin <= %ld AND za.zeitende >= %ld AND za.weekday = %d", currenttime, currenttime, weekday );
			}		
			sprintf( query,
				"SELECT al.filialnr, al.artikel_nr, al.bestand, al.artikelaktiv, al.verbundartikel, 0, 100, min(ib.priority) "
				"FROM ibtbranches ib " 
				"%s "
				"JOIN %s al ON al.filialnr=ib.ibtbranchno "
				"JOIN artikellokal allok ON allok.filialnr=ib.branchno AND allok.artikel_nr=al.artikel_nr "
				"WHERE ib.active_flag=1 AND ib.branchno=%d AND al.artikel_nr=%ld AND al.verbundartikel!='0' AND al.artikelaktiv='1' AND al.bestand >= 0 "
				"%s "
				"AND ( ( allok.verbundartikel='1' AND ib.ibttype=0 ) "
				"OR ( allok.verbundartikel='2' AND ib.ibttype=1 ) "
				"OR ( allok.verbundartikel='3' AND ib.ibttype=2 ) "
				"OR ( allok.verbundartikel='4' AND ib.ibttype=3 ) "
				"OR ( allok.verbundartikel='5' AND ib.ibttype=5 ) "
				"OR ( allok.verbundartikel='6' AND ib.ibttype in (3,5) ) "
				"OR ( allok.verbundartikel='7' AND ib.ibttype in (0,5) ) "
				"OR ( allok.verbundartikel='8' AND ib.ibttype in (0,3) ) "
				"OR ( allok.verbundartikel='9' ) ) "
				"GROUP BY al.filialnr, al.artikel_nr, al.bestand, al.artikelaktiv, al.verbundartikel "
				"ORDER BY min(ib.priority) ASC; "
				, joinTimeTypes, useVartikellokal, recordp->FILIALNR, recordp->ARTIKEL_NR, whereTimeTypes );
			break;
	}

	EXEC SQL PREPARE pxvartikellokal2startbrowse_stmt FROM :query;
	EXEC SQL DECLARE pxvartikellokal2startbrowse_cur CURSOR WITH HOLD FOR pxvartikellokal2startbrowse_stmt;
	EXEC SQL OPEN pxvartikellokal2startbrowse_cur; 

	switch( SQLCODE )
	{
		case 0:
			return 0;
		case 100:
			return cDBXR_NOTFOUND;	
		default:
			return cDBXR_IOERROR;
	}  
}

/*--------------------------------------------------------------------------------------------------*/
int pxVartikelLokalGetNext( struct tVARTIKELLOKAL* record, int browseid )
{
    EXEC SQL BEGIN DECLARE SECTION;
		struct C_VARTIKELLOKAL * recordp;
		short dummyvalue = 0;
    EXEC SQL END   DECLARE SECTION;
    
    recordp = (struct C_VARTIKELLOKAL *) record;

	switch( browseid )
	{
		case cCRS_IBTBRANCHES_NLEVELIBT_INACTIVE:
		case cCRS_IBTBRANCHES_NLEVELIBT:			
			EXEC SQL FETCH pxvartikellokal2startbrowse_cur INTO
				:dummyvalue,
				:dummyvalue,
				:recordp->FILIALNR,
				:recordp->ARTIKEL_NR,
				:recordp->BESTAND,
				:recordp->ARTIKELAKTIV,
				:recordp->VERBUNDARTIKEL,
				:recordp->NLEVELIBTTYPEID,
				:recordp->IBTQTYAVAILABILITYPERCENTAGE;
			break;			
		case cCRS_IBTBRANCHES:
		default:
			EXEC SQL FETCH pxvartikellokal2startbrowse_cur INTO 
				:recordp->FILIALNR,
				:recordp->ARTIKEL_NR,
				:recordp->BESTAND,
				:recordp->ARTIKELAKTIV,
				:recordp->VERBUNDARTIKEL,
				:recordp->NLEVELIBTTYPEID,
				:recordp->IBTQTYAVAILABILITYPERCENTAGE,
				:dummyvalue;						
	}
	   
	switch( SQLCODE )
	{
		case 0:
			return 0;
		case 100:
			return cDBXR_ENDOFDATA;	
		default:
			return cDBXR_IOERROR;
	}  
}

/*--------------------------------------------------------------------------------------------------*/
int pxVartikelLokalEndBrowse( int browseid )
{
    UNUSED(browseid);
	EXEC SQL CLOSE pxvartikellokal2startbrowse_cur;
	EXEC SQL SET ISOLATION TO COMMITTED READ;	
    return 0;
}

