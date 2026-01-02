#include <stddef.h>
#include <stdio.h>
#include <pxrecord.h>
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tibtbranches.h"
#include <pxenv.h>
#include <keys.h>

extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
/* open cursor                                                       */
/*-------------------------------------------------------------------*/
int IBTBranchesStartBrowse( struct tIBTBRANCHES* record, const char* dbNameLocal, const char* dbNameIBT, int browseid )
{
    EXEC SQL BEGIN DECLARE SECTION;
        struct C_IBTBRANCHES* recordp;
        char query[1024] = {' '};
    EXEC SQL END DECLARE SECTION;

    UNUSED(dbNameIBT);
    recordp = (struct C_IBTBRANCHES*) record;

    switch( browseid )
    {
		case cIBTBRANCHES_NLEVELIBTARTICLENO:
			if( recordp->IBTBRANCHNO > 0 )
			{
				sprintf( query,
					 "select b.branchno, b.priority, b.ibtbranchno, b.ibttype, b.dayibt, "
					 "case when b.ibtcustomerno = 0 then f.bganr_ek else b.ibtcustomerno end as ibtcustomerno, "
					 "b.active_flag, b.nlevelibttypeid, b.nlevelibtassortmenttypeid "
					 "from ibtbranches b "
					 "join filiale f on f.filialnr=b.branchno "
					 "join ibtbrancharticleconfig bac on bac.branchno=b.branchno and bac.articleno=? " // articleno
					 "where b.active_flag=1 and b.branchno=? and b.nlevelibttypeid in (3, bac.ibttypeid) and b.nlevelibtassortmenttypeid=bac.ibtassortmenttypeid " // branchno
					 "and b.ibtbranchno=%d " // ibtbranchno
					 "and b.nlevelibttypeid > 0 "
					 "order by b.priority;", recordp->IBTBRANCHNO );			
			}
			else
			{
				sprintf( query,
					 "select b.branchno, b.priority, b.ibtbranchno, b.ibttype, b.dayibt, "
					 "case when b.ibtcustomerno = 0 then f.bganr_ek else b.ibtcustomerno end as ibtcustomerno, "
					 "b.active_flag, b.nlevelibttypeid, b.nlevelibtassortmenttypeid "
					 "from ibtbranches b "
					 "join filiale f on f.filialnr=b.branchno "
					 "join ibtbrancharticleconfig bac on bac.branchno=b.branchno and bac.articleno=? " // articleno
					 "where b.active_flag=1 and b.branchno=? and b.nlevelibttypeid in (3, bac.ibttypeid) and b.nlevelibtassortmenttypeid=bac.ibtassortmenttypeid " // branchno					 
					 "and b.nlevelibttypeid > 0 "
					 "order by b.priority;" );			
			}
			break;

		case cIBTBRANCHES_NLEVELIBT:
			sprintf( query,
					 "select b.branchno, b.priority, b.ibtbranchno, b.ibttype, b.dayibt, "
					 "case when b.ibtcustomerno = 0 then f.bganr_ek else b.ibtcustomerno end as ibtcustomerno, "
					 "b.active_flag, b.nlevelibttypeid, b.nlevelibtassortmenttypeid "
					 "from ibtbranches b "						 
					 "join filiale f on f.filialnr=b.branchno "
					 "where b.active_flag=1 and b.branchno=? and b.nlevelibttypeid=? order by b.priority;" );			
			break;

		case cIBTBRANCHES_RELEVANTNLEVELIBTBRANCHES:
			sprintf( query,
					 "select b.branchno, b.priority, b.ibtbranchno, b.ibttype, b.dayibt, "
					 "case when b.ibtcustomerno = 0 then f.bganr_ek else b.ibtcustomerno end as ibtcustomerno, "
					 "b.active_flag, b.nlevelibttypeid, b.nlevelibtassortmenttypeid "
					 "from ibtbrancharticleconfig ac "
					 "join ibtbranches b on b.branchno=ac.branchno and b.nlevelibtassortmenttypeid=ac.ibtassortmenttypeid "
					 "join filiale f on f.filialnr=b.branchno "
					 "where b.active_flag=1 and ac.branchno=? and ac.articleno=?;" );
			break;

		case cIBTBRANCHES_ALLENTRIES:
			sprintf( query,
					 "select ib.branchno, ib.ibtbranchno, ib.ibttype "
					 ", case when ib.ibtcustomerno = 0 then f.bganr_ek else ib.ibtcustomerno end as ibtcustomerno "
					 ", ib.priority, ib.dayibt "
					 "from %s:ibtbranches ib "
					 "join %s:filiale f on f.filialnr=ib.branchno "
					 "where ib.branchno = ? and ib.active_flag = 1 "
					 "and ( (9=? and ib.ibttype in (0,3,5)) "
					 "or	(8=? and ib.ibttype in (0,3)) "
					 "or	(7=? and ib.ibttype in (0,5)) "
					 "or	(6=? and ib.ibttype in (3,5)) "
					 "or	(5=? and ib.ibttype = 5) "
					 "or	(3=? and ib.ibttype = 3) "
					 "or	(2=? and ib.ibttype = 2) "
					 "or	(1=? and ib.ibttype = 1) "
					 "or	(0=? and ib.ibttype = 0) ) "
					 "order by ib.priority asc; "
					 , dbNameLocal, dbNameLocal );
			break;

		case cIBTBRANCHES_DEFAULT:
		default:
			sprintf( query,
					 "select ib.branchno, ib.ibtbranchno, ib.ibttype "
					 ", case when ib.ibtcustomerno = 0 then f.bganr_ek else ib.ibtcustomerno end as ibtcustomerno "
					 ", ib.priority, ib.dayibt "
					 "from %s:ibtbranches ib "
					 "join %s:filiale f on f.filialnr=ib.branchno "
					 "where ib.branchno = ? and ib.ibtbranchno = ? and ib.active_flag = 1 "
					 "and ( (9=? and ib.ibttype in (0,3,5)) "
					 "or	(8=? and ib.ibttype in (0,3)) "
					 "or	(7=? and ib.ibttype in (0,5)) "
					 "or	(6=? and ib.ibttype in (3,5)) "
					 "or	(5=? and ib.ibttype = 5) "
					 "or	(3=? and ib.ibttype = 3) "
					 "or	(2=? and ib.ibttype = 2) "
					 "or	(1=? and ib.ibttype = 1) "
					 "or	(0=? and ib.ibttype = 0) ) "
					 "order by ib.priority asc; "
					 , dbNameLocal, dbNameLocal );
			break;
    }

    EXEC SQL PREPARE ibtbranchesstartbrowse_stmt FROM :query;
    EXEC SQL DECLARE ibtbranchesstartbrowse_cur CURSOR WITH HOLD FOR ibtbranchesstartbrowse_stmt;

    switch( browseid )
    {
		case cIBTBRANCHES_NLEVELIBTARTICLENO:
			EXEC SQL OPEN ibtbranchesstartbrowse_cur USING :recordp->ARTICLENO, :recordp->BRANCHNO;
			break;

		case cIBTBRANCHES_NLEVELIBT:
			EXEC SQL OPEN ibtbranchesstartbrowse_cur USING :recordp->BRANCHNO, :recordp->IBTTYPE;
			break;

		case cIBTBRANCHES_RELEVANTNLEVELIBTBRANCHES:
			EXEC SQL OPEN ibtbranchesstartbrowse_cur USING :recordp->BRANCHNO, :recordp->ARTICLENO;
			break;

		case cIBTBRANCHES_ALLENTRIES:
			EXEC SQL OPEN ibtbranchesstartbrowse_cur USING :recordp->BRANCHNO,
			:recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE,
			:recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE;
			break;

		case cIBTBRANCHES_DEFAULT:
		default:
			EXEC SQL OPEN ibtbranchesstartbrowse_cur USING :recordp->BRANCHNO, :recordp->IBTBRANCHNO,
			:recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE,
			:recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE, :recordp->IBTTYPE;
			break;
    }


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

/*-------------------------------------------------------------------*/
/* get next cursors                                                  */
/*-------------------------------------------------------------------*/
int IBTBranchesGetNext( struct tIBTBRANCHES* record, int browseid )
{
    EXEC SQL BEGIN DECLARE SECTION;
        struct C_IBTBRANCHES* recordp;
    EXEC SQL END DECLARE SECTION;

    recordp = (struct C_IBTBRANCHES*) record;

    switch( browseid )
    {
		case cIBTBRANCHES_NLEVELIBTARTICLENO:
		case cIBTBRANCHES_NLEVELIBT:
		case cIBTBRANCHES_RELEVANTNLEVELIBTBRANCHES:
			EXEC SQL FETCH ibtbranchesstartbrowse_cur INTO
			:recordp->BRANCHNO,
			:recordp->PRIORITY,
			:recordp->IBTBRANCHNO,
			:recordp->IBTTYPE,
			:recordp->DAYIBT,
			:recordp->IBTCUSTOMERNO,
			:recordp->ACTIVE_FLAG,
			:recordp->NLEVELIBTTYPEID,
			:recordp->NLEVELIBTASSORTMENTTYPEID;
			break;

		case cIBTBRANCHES_ALLENTRIES: // fall through, same values like default case
		case cIBTBRANCHES_DEFAULT:
		default:
			EXEC SQL FETCH ibtbranchesstartbrowse_cur INTO
			:recordp->BRANCHNO,
			:recordp->IBTBRANCHNO,
			:recordp->IBTTYPE,
			:recordp->IBTCUSTOMERNO,
			:recordp->PRIORITY,
			:recordp->DAYIBT;
			break;
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

/*-------------------------------------------------------------------*/
/* close cursor                                                      */
/*-------------------------------------------------------------------*/
int IBTBranchesEndBrowse( int browseid )
{
    UNUSED(browseid);
    EXEC SQL CLOSE ibtbranchesstartbrowse_cur;
    EXEC SQL FREE ibtbranchesstartbrowse_stmt;
    return 0;
}


