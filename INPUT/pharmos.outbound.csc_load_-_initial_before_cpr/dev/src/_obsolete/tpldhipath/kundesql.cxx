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
#include "kunde.h" 
exec sql include sqlca;

//##############################################################################################################//
// retClient loadSKundeSelect( struct S_SQLKUNDE* p, tError* pstError )
//##############################################################################################################//
retClient loadSKundeSelect( struct S_SQLKUNDE* p, struct S_Counter* pCnt, tError* pstError )
{	
	__FUNCTION__( loadSKundeSelect() )
	DEBUG_ENTER( fun ) 
	
	static unsigned int uiCursor_Already_Opened = 0;
	char szErrMsg[256];

	EXEC SQL BEGIN DECLARE SECTION;
		short sDC = p->VERTRIEBSZENTRUMNR;
		struct S_SQLKUNDE* pData = p;
	EXEC SQL END DECLARE SECTION;

	/****************************************************************/
	/* SELECT ausfuehren */
	/****************************************************************/
	if( 0 == uiCursor_Already_Opened ){
		EXEC SQL OPEN CURSELKUNDE using :sDC;
		sprintf( szErrMsg, TXT_OPEN_CURSOR_ERROR, sDC );
		if( IS_OK != CheckSql((char*)fun, pstError, szErrMsg ) ){
			return IS_ERROR;
		} else {
			uiCursor_Already_Opened = 1;
		}
	}

	/****************************************************************/
	/*  Datensaetze holen */
	/****************************************************************/
	EXEC SQL FETCH CURSELKUNDE into		:pData->KUNDENNR,
										:pData->VERTRIEBSZENTRUMNR,
                                        :pData->NAMEAPO,        
                                        :pData->ORT,
										:pData->KUNDE_TELNR,
										:pData->KZKDKLASSE,
										:pData->PHONEPRIORITY,
										:pData->CUSTOMERPHONENO_TELNR,
										:pData->KZSPRACHE;


	strcpy( szErrMsg, TXT_FETCH_CURSOR_ERROR );
	if( IS_OK != CheckSql((char*)fun, pstError, szErrMsg ) ){
		return IS_ERROR;
	}
	pCnt->ulSel++;
	DEBUG_LEAVE( fun )
	return IS_OK;
}
//##############################################################################################################//
// retClient prepareSKundeSelect( tError* pstError );
//##############################################################################################################//
retClient prepareSKundeSelect( tError* pstError )
{
	__FUNCTION__( prepareSKundeSelect() )
	DEBUG_ENTER( fun ) 

	char szErrMsg[256];

	EXEC SQL BEGIN DECLARE SECTION;
		char szSql[1024];
	EXEC SQL END DECLARE SECTION;

	/********************************************************************************************************/
	/* SELECT PREPARE */
	/********************************************************************************************************/
	strcpy( szSql,	"select k.kundennr, k.vertriebszentrumnr, k.nameapo,        k.ort, "
                    "k.telnr,    k.kzkdklasse,         k.phonepriority,  c.telnr, "
					"kzsprache "
					"from kunde k, kundeschalter s, outer customerphoneno c "
                    "where k.kundennr = s.kundennr and k.vertriebszentrumnr = s.vertriebszentrumnr "
                    "and k.kundennr = c.kundennr "
                    "and k.vertriebszentrumnr = c.vertriebszentrumnr "
                    "and (k.originalfilialnr = k.vertriebszentrumnr or k.originalfilialnr = 0) "
                    "and s.skdkundeaegesperrt = '0' "                    
                    "and k.phonepriority in ( 'V', 'S', 'A', 'B', 'C', 'D' ) "
					"and k.vertriebszentrumnr = ?"
			);
	
	EXEC SQL PREPARE PREUPD from :szSql;
	sprintf( szErrMsg, TXT_PREPARE_SELECT_ERROR, "kunde, kundeschalter, outer customerphoneno" );
	if( IS_OK != CheckSql((char*)fun, pstError, szErrMsg ) ){
		return IS_ERROR;
	}
	EXEC SQL DECLARE CURSELKUNDE cursor with hold for PREUPD;
	sprintf( szErrMsg, TXT_DECLARE_CURSOR_ERROR, "kunde, kundeschalter, outer customerphoneno" );
	if( IS_OK != CheckSql((char*)fun, pstError, szErrMsg ) ){
		return IS_ERROR;
	}

	DEBUG_LEAVE( fun )
	return IS_OK;
}
//##############################################################################################################//
// void freeSKundeSelect()
//##############################################################################################################//
void freeSKundeSelect()
{
	__FUNCTION__( freeSKundeSelect() )
	DEBUG_ENTER( fun ) 

	EXEC SQL FREE PREUPD;
	EXEC SQL CLOSE CURSELKUNDE;	
	DEBUG_LEAVE( fun )
}

