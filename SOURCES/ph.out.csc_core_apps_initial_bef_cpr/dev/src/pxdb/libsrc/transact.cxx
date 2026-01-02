/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

    Embedded SQL for C application


    FILE: transact.c (.sqc)

    Database Transaction functions



    FUNCTIONS:

        pxBegin    Begin a transaction
        pxCommit   Commit a transaction
        pxRollback Rollback a transaction


REVISION HISTORY

15 Jun 1995 V1.00 REV 00 written by Dietmar Schloetel

*/


#include <ndefs.h>
#include <pxenv.h>
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxBegin                                                */
/*                                                                   */
/*      Begin Transaction                                            */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxBegin
(
)
{
#ifndef pxDATABASE_INFORMIX
    EXEC SQL BEGIN TRANSACTION;
#else
    EXEC SQL BEGIN WORK;
#endif
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxCommit                                               */
/*                                                                   */
/*      Commit Transaction                                           */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxCommit
(
)
{
#ifndef pxDATABASE_INFORMIX
    EXEC SQL COMMIT TRANSACTION;
#else
    EXEC SQL COMMIT WORK;
#endif
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxRollback                                             */
/*                                                                   */
/*      Rollback Transaction                                         */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxRollback
(
)
{
#ifndef pxDATABASE_INFORMIX
    EXEC SQL ROLLBACK TRANSACTION;
#else
    EXEC SQL ROLLBACK WORK;
#endif
    return 0;
}
