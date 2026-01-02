#include "database.hpp"
#include <string>

/*----------------------------------------------------------------------------*/
/*  Destruction.                                                              */
/*----------------------------------------------------------------------------*/
nDataBase :: ~nDataBase()
{
}
/*----------------------------------------------------------------------------*/
/*  Construction.                                                             */
/*----------------------------------------------------------------------------*/
nDataBase :: nDataBase()
{
    TransLevel_ = cDBTransNo;
}

/*----------------------------------------------------------------------------*/
/*  Retrieve data base diagnostic, store values into current nError class     */
/*  object.                                                                   */
/*----------------------------------------------------------------------------*/
void
nDataBase :: nDBDiagnostic
(
    nError&  error,                     // current error class
    int      num                        // error number returned from i/o server
)
{
    // At first get last table name and last function name
    std::string tablename = GetTableName();
    std::string functionname = GetFunctionName();
    std::string errorstring;
    int errorcode;

    if ( num == -1 )                    // then server connection broken
    {
       errorcode = num;
    }
    else
    {
       errorstring = GetSqlMessage();
       errorcode = GetSqlCode();
    }

	std::string msgstring = tablename + functionname + errorstring;
    error.DBError(nMessage(msgstring.c_str()), errorcode);
}

bool nDataBase::nDBInTransaction()
{
	return (TransLevel_ != cDBTransNo);   // then transaction running	
}

/*----------------------------------------------------------------------------*/
/*  Begin a data base transaction on a specified resource level.              */
/*  Note that if a transaction is already running, the following things       */
/*  will happen:                                                              */
/*  - If the requested level is higher than the level of the transaction      */
/*    already running, the current level is raised to the value requested.    */
/*  - If the requested level is less than or equal to the level of the        */
/*    transaction already running, the request is ignored.                    */
/*  In either case, no BeginTransaction request is issued against the data    */
/*  base if a transaction is already running.                                 */
/*----------------------------------------------------------------------------*/
int
nDataBase :: nDBBeginTransaction
(
    const tDBTransactLevel  rlevel
)
{
    tDBTransactLevel level = rlevel;
    int retval = cDBXR_NORMAL;
    if ( level  <= cDBTransNo )         // then level is invalid,
       level = cDBTransRecord;          // gracefully raise it to lowest value
    if ( TransLevel_  == cDBTransNo )   // then no transaction running
       retval = BeginTransaction();     // begin it now
    if ( (retval == cDBXR_NORMAL) && (level > TransLevel_) )
       TransLevel_ = level;             // store current level if successful
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Commit transaction.                                                       */
/*  No commit is issued against the data base if a transaction with a higher  */
/*  level is currently running.                                               */
/*----------------------------------------------------------------------------*/
int
nDataBase :: nDBCommit
(
    const tDBTransactLevel  level
)
{
    int retval = cDBXR_NORMAL;
    if ( level >= TransLevel_ )         // ensure transactions started with a higher
    {                                   // level to be continued
       TransLevel_ = cDBTransNo;
       retval = Commit();
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Transaction rollback.                                                     */
/*----------------------------------------------------------------------------*/
int
nDataBase :: nDBRollBack()
{
    TransLevel_ = cDBTransNo;           // clear transaction level,
    return RollBack();                  // then issue rollback
}

/*----------------------------------------------------------------------------*/
/*  Data Base disconnection.                                                  */
/*----------------------------------------------------------------------------*/
int
nDataBase :: nDBDisConnect()
{
    if ( TransLevel_ > cDBTransNo )     // then a transaction is running
       nDBRollBack();                   // must first roll back updates
    return DisConnect();                // then disconnect from the data base
}

/*----------------------------------------------------------------------------*/
/*  Connect the data base.                                                    */
/*----------------------------------------------------------------------------*/
int
nDataBase :: nDBConnect
(
    const std::string& datasrc
)

{
    int  retval;
    if ( (retval = Connect(datasrc)) == 0 )
    {
       return retval;
    }

    if ( retval < cDBXR_NORMAL )        // then data base returned an error,
    {                                   // so we ask for a diagnostic and
       nDBDiagnostic(Error(), retval);
    }
    return retval;
}
