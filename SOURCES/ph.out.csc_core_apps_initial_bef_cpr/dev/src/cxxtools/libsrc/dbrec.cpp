#include "database.hpp"
#include <stdlib.h>

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
/*  Delete a record in   the database.                                        */
/*----------------------------------------------------------------------------*/
int
nDBRecord :: nDBDelete
(
    const void     *record              // buffer where the record to delete is
)
{
    int  retval = 0;
    ClearError();
    if ( pxGlobalNoDatabaseWrite)
       return retval;
    retval = Delete(record);
    ( retval == 0 ) ? ClearActive() : SetActive();
    if ( retval < cDBXR_NORMAL )        // then data base returned an error,
    {                                   // so we ask for a diagnostic and
       DataBase()->nDBDiagnostic(Error(),
                                 retval); // store it into the error class
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Read one record from the database.                                        */
/*----------------------------------------------------------------------------*/
int
nDBRecord :: nDBRead
(
    const void     *record              // buffer where the record is read into
)
{
    ClearError();                       // clear last error condition
    int retval = Read(record);
    ( retval == 0 ) ? SetActive() : ClearActive();
    if ( retval < cDBXR_NORMAL )        // then data base returned an error,
    {                                   // so we ask for a diagnostic and
       DataBase()->nDBDiagnostic(Error(),
                                 retval); // store it into the error class
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Read and lock a record for a subsequent update.                           */
/*----------------------------------------------------------------------------*/
int
nDBRecord :: nDBReadLock
(
    const void     *record              // buffer where the record is read into
)
{
    if (true == pxGlobalNoDatabaseWrite)
    {
       return nDBRead(record);
    }
    ClearError();
    int retval = ReadLock(record);
    ( retval == 0 ) ? SetActive(), SetLocked() : ClearActive();
    if ( retval < cDBXR_NORMAL )        // then an error occured
    {
       DataBase()->nDBDiagnostic(Error(), retval);
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Write a record into the data base.                                        */
/*----------------------------------------------------------------------------*/
int
nDBRecord :: nDBWrite
(
    const void     *record,             // buffer where the record is written from
          size_t   recsize              // size of the record
)
{
    int  retval = 0;
    ClearError();
    if ( pxGlobalNoDatabaseWrite)
       return retval;
/*----------------------------------------------------------------------------*/
/*  If the record is active but not locked, we read-lock it into a temporary  */
/*  buffer to preserve the changes made within the buffer passed as argument  */
/*  'record'. The update is then done using this buffer. Seems to be a bit    */
/*  dangerous, but we think the caller must know what he is doing.            */
/*----------------------------------------------------------------------------*/
    if ( IsActive() && !IsLocked() )    // then record active but not locked
    {
       void* temp = malloc(recsize);
       if ( temp != NULL ) // acquire temporary buffer
       {
          memcpy(temp, record, recsize);// copy record contents to get the key(s)
          retval = nDBReadLock(temp);  // do the lock
          free(temp);                   // release temp buffer
       }
       else                             // no memory got
       {
          AllocError(nMessage("nDBWrite: Out of memory while requesting %d bytes\n",
                               (int) recsize), -1000);
          return -1000;
       }
    }

    if ( retval )                       // then error occured while re-reading,
    {                                   // and this should never happen
       // DataBase()->nDBDiagnostic(Error(), retval);
       ClearLocked();                   // always clear the lock bit
       return retval;
    }

/*----------------------------------------------------------------------------*/
/*  Now do the write operation.                                               */
/*----------------------------------------------------------------------------*/
    if ( IsActive() )                   // then it is an update
    {
       retval = Update(record);
       //if ( (retval = Update(record)) ) // and an error during update
       //   DataBase()->nDBDiagnostic(Error()); // is a hard error
    }
    else
       retval = Insert(record);         // insert a new record

    if ( retval == cDBXR_NORMAL )       // success
    {
       ClearDirty();                    // clear dirty state for this object
       SetActive();                     // and the record is active now
    }
    else if ( retval != cDBXR_ISDUPLICATE ) // only a duplicate might occur
       DataBase()->nDBDiagnostic(Error(), retval);  // during insert

    ClearLocked();                      // always clear the lock bit
    return retval;
}

void nDBRecord::WriteLog(const nString& message, nErrorState state, int msgid)
{
	database_->WriteLog(message, state, msgid);
}

