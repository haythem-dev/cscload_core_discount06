#include <stddef.h>         
#include <stdio.h>          
#include <pxrecord.h>       
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tibtbrancharticleconfig.h"
#include <pxenv.h>
#include <keys.h>
#include "pxdatetime.h"

extern int  functionnr;

#define UNUSED(x) (void)(x)

int pxIBTBranchArticleConfigRead( struct tIBTBRANCHARTICLECONFIG* record )
{
    EXEC SQL BEGIN DECLARE SECTION;
	struct C_IBTBRANCHARTICLECONFIG* recordp;	
	char query[2048] = {' '};
    EXEC SQL END DECLARE SECTION;	
	
	recordp = (struct C_IBTBRANCHARTICLECONFIG*) record;	
		
	sprintf( query, 
		"select c.articleno, c.branchno, c.ibttypeid, c.ibtassortmenttypeid "
		"from ibtbrancharticleconfig c "
		"where c.branchno=? and c.articleno=?;" );

	EXEC SQL PREPARE pxibtbrancharticleconfigread_stmt FROM :query;
	EXEC SQL DECLARE pxibtbrancharticleconfigread_cur CURSOR WITH HOLD FOR pxibtbrancharticleconfigread_stmt;
	EXEC SQL OPEN pxibtbrancharticleconfigread_cur USING :recordp->BRANCHNO, :recordp->ARTICLENO;

	switch( SQLCODE )
	{
		case 0:
			break;
		case 100:
			return cDBXR_NOTFOUND;	
		default:
			return cDBXR_IOERROR;
	} 

	EXEC SQL FETCH pxibtbrancharticleconfigread_cur INTO 
		:recordp->ARTICLENO,
		:recordp->BRANCHNO,
		:recordp->IBTTYPEID,
		:recordp->IBTASSORTMENTTYPEID;

	switch( SQLCODE )
	{
		case 0:
			break;
		case 100:
			EXEC SQL CLOSE pxibtbrancharticleconfigread_cur;
			EXEC SQL FREE pxibtbrancharticleconfigread_stmt;	
			return cDBXR_ENDOFDATA;
		default:
			EXEC SQL CLOSE pxibtbrancharticleconfigread_cur;
			EXEC SQL FREE pxibtbrancharticleconfigread_stmt;	
			return cDBXR_IOERROR;
	}		

	EXEC SQL CLOSE pxibtbrancharticleconfigread_cur;
	EXEC SQL FREE pxibtbrancharticleconfigread_stmt;	
	return 0;
}
