//##############################################################################################################//
// INCLUDES
//##############################################################################################################//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "define.h"
#include "macro.h"
#include "sql.h" 
#include "customerroutingtable.h" 

exec sql include sqlca;

//##############################################################################################################//
// retClient prepareSCustomRoutingTable( tError* pstError )
//##############################################################################################################//
retClient prepareSCustomRoutingTable( tError* pstError )
{
	__FUNCTION__( prepareSCustomRoutingTable() )
	DEBUG_ENTER( fun ) 

	char szErrMsg[256];

	EXEC SQL BEGIN DECLARE SECTION;
		char szSql[1024];
	EXEC SQL END DECLARE SECTION;
	
	/********************************************************************************************************/
	/* UPDATE prepare ARTIKELF */
	/********************************************************************************************************/
	strcpy( szSql,	"UPDATE customroutingtable	"
					"SET " CRT_UPDATE_LIST " "
					"WHERE origin = ? ");

	EXEC SQL PREPARE PREUPDCRT from :szSql;

	sprintf( szErrMsg, TXT_PREPARE_UPDATE_ERROR, "customroutingtable");
	if( IS_OK != CheckSql((char*)fun, pstError, szErrMsg ) ){
		return IS_ERROR;
	}

	/********************************************************************************************************/
	/* INSERT prepare ARTIKELF */
	/********************************************************************************************************/

	strcpy( szSql, "INSERT INTO customroutingtable (" CRT_ATTRIBUTLISTE_AS_STRING ") "
				   "VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ? )" );
	EXEC SQL PREPARE PREINSCRT from :szSql;

	sprintf( szErrMsg, TXT_PREPARE_INSERT_ERROR, "customroutingtable" );
	if( IS_OK != CheckSql((char*)fun, pstError, szErrMsg ) ){
		return IS_ERROR;
	}	

	DEBUG_LEAVE( fun )
	return IS_OK;
}
//##############################################################################################################//
// retClient saveSCustomRoutingTable( struct SQLSCUSTOMROUTINGTABLE* p, struct S_Counter* pCnt, tError* pstError )
//##############################################################################################################//
retClient saveSCustomRoutingTable( struct SQLSCUSTOMROUTINGTABLE* p, struct S_Counter* pCnt, tError* pstError )
{	
	__FUNCTION__( saveSCustomRoutingTable() )
	DEBUG_ENTER( fun ) 
    
    char szErrMsg[256];
    EXEC SQL BEGIN DECLARE SECTION;
		struct SQLSCUSTOMROUTINGTABLE* pData = p;
	EXEC SQL END DECLARE SECTION;

	/*******************************************************************/
	/* UPDATE */
	/*******************************************************************/
	EXEC SQL EXECUTE PREUPDCRT USING CRT_INSUPD_ARGUMENTS( pData ), :pData->ORIGIN;
	sprintf( szErrMsg, TXT_EXECUTE_PREUPD, sqlca.sqlcode, "customroutingtable" );
	if( IS_OK != CheckSql((char*)fun, pstError, szErrMsg ) ){
		return IS_ERROR;
	}
	if( pstError->lUpdateNo == 0 ){
		/*******************************************************************/
		/* INSERT */
		/*******************************************************************/
        /*printf("pData: %s, %s, %d, %s, %s, %d, %s, %s, %s\n\n",    pData->ORIGIN,				
										        pData->CALLTYPE,			
										        pData->INITIALPRIORITY,		
										        pData->RESERVEAGENTID,		
										        pData->RESERVEAGENTSITE,	
										        pData->RESERVEAGENTTIME,	
										        pData->CAPTION,				
										        pData->CALLDATA,			
										        pData->DDE );*/


		EXEC SQL EXECUTE PREINSCRT USING CRT_INSUPD_ARGUMENTS( pData ); 
		sprintf( szErrMsg, TXT_EXECUTE_PREINS, sqlca.sqlcode, "customroutingtable" );
		if( IS_OK != CheckSql((char*)fun, pstError, szErrMsg ) ){
			return IS_ERROR;
		}
		// insert counter
		pCnt->ulIns++;
	} else {
		// update counter
		pCnt->ulUpd++;
	}

	DEBUG_LEAVE( fun )
	return IS_OK;
}
//##############################################################################################################//
// void freeSCustomRoutingTable()
//##############################################################################################################//
retClient eraseSCustomRoutingTable( unsigned int uiDcNo, long lDate, struct S_Counter* pCnt, tError* pstError, char* szSqlBuffer )
{
	__FUNCTION__( eraseSCustomRoutingTable() )
	DEBUG_ENTER( fun ) 
    
    char szErrMsg[256];

	EXEC SQL BEGIN DECLARE SECTION;
		char szSQL[256];
	EXEC SQL END DECLARE SECTION;

    sprintf( szSQL,     "delete from customroutingtable "
                        "where substr(caption, 1, 2) = '%02u' "
                        "and substr(caption, 10, 8 ) != '%ld'",  uiDcNo, lDate  );
//#ifndef NDEBUG
//    printf("%s(szSQL): %s\n", fun, szSQL );
//#endif
	strcpy( szSqlBuffer, szSQL );

    EXEC SQL EXECUTE IMMEDIATE :szSQL;
    if( IS_OK != CheckSql((char*)fun, pstError, szErrMsg ) ){
	    return IS_ERROR;
	} else {
        pCnt->ulDel = pstError->lUpdateNo;
    }
	DEBUG_LEAVE( fun )
    return IS_OK;
}
//##############################################################################################################//
// void freeSCustomRoutingTable()
//##############################################################################################################//
void freeSCustomRoutingTable()
{
	__FUNCTION__( freeSCustomRoutingTable() )
	DEBUG_ENTER( fun ) 

	EXEC SQL FREE PREUPDCRT;
	EXEC SQL FREE PREINSCRT;

	DEBUG_LEAVE( fun )
}
