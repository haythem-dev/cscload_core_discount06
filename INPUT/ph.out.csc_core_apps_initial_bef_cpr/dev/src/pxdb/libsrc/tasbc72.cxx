/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

    Embedded SQL for C application

    FILE: tasbc72.c (.sqc)

    Database functions

    FUNCTIONS:

        tasbc72 declare and open Cursor,get next record,close cursor

REVISION HISTORY
20 July 2005 V1.00 REV 00 written by Ysbrand Bouma

*/


#include "tasbccommon.h"


int tasbc72
(
     struct tKDAUFTRAG* record,
     int mode
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_KDAUFTRAG * recordp;
    EXEC SQL END DECLARE SECTION;
#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif
    recordp = (struct C_KDAUFTRAG *) record;

    switch (mode)
    {
       case 1: /* open */
          EXEC SQL DECLARE C1 CURSOR FOR
			SELECT 
			KDAUFTRAG_LISTE
			FROM kdauftrag
			WHERE FILIALNR = :recordp->FILIALNR
			AND IDFNR = :recordp->IDFNR
			AND ORDERPERIODID = :recordp->ORDERPERIODID
			AND KDAUFTRAGART = :recordp->KDAUFTRAGART			
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
          EXEC SQL OPEN C1;

          if (SQLCODE == 0)    return 0;
          if (SQLCODE == 100)  return cDBXR_NOTFOUND;
          return cDBXR_IOERROR;

       case 2: /* fetch */
          EXEC SQL FETCH C1
          into KDAUFTRAG_ZEIGER(recordp);
          if (SQLCODE == 0)   return 0;
          if (SQLCODE == 100) return cDBXR_ENDOFDATA;
          return cDBXR_IOERROR;

       default: /* close */
          EXEC SQL CLOSE C1;
          return 0;
    }
}
