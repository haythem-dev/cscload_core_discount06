/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: tasbc18.c (.sqc)

    Database functions




    FUNCTIONS:

        tasbc18 declare and open Cursor,get next record,close cursor


REVISION HISTORY

06 Oct 1995 V1.00 REV 00 written by Dietmar Schloetel

*/


#include "tasbccommon.h"


int tasbc18
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
          from KDAUFTRAG
          Ktasbc18
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
