#include "database.hpp"

/*----------------------------------------------------------------------------*/
/*  Clear the record set.                                                     */
/*----------------------------------------------------------------------------*/
void
nDBRecordSet :: Clear()
{
    nDListCollectIter cursor(*objlist_);    // define an iterator
    nDBRecord   *objectp;               // points at current object instance

    while ( (objectp = (nDBRecord*) ++(cursor)) != NULL )
    {
       cursor.Remove();                 // remove instance from the list
       delete objectp;                  // and destruct it
    }
}
/*----------------------------------------------------------------------------*/
/*  Select a set of records from the data base.                               */
/*----------------------------------------------------------------------------*/
int
nDBRecordSet :: nDBSelect
(
    const void    *keys,               // where the selection keys are stored
    const int     cursorid,            // cursor identification (browse id)
    const int     count,               // max number of rows to fetch
    const void    *record              // buffer where the record is fetched into
)
{
    int         objects = 0;            // number of objects created
    void  *record_ = (void*)record;     // cast away constness
    cursorid_ = 0;                      // Reset cursor id
    ClearError();                       // clear last error condition
    if ( record_ == NULL )              // if no record buffer passed,
       record_ = (void*)keys;           // then use key buffer to store the record

    if ( record_ )
    {
       if (! objlist_->IsEmpty())
          Clear();                      // empty the list
       int errornum = StartBrowse(keys, cursorid);
       if ( errornum == 0 )
       {                                // browse started successfully,
          cursorid_ = cursorid;         // set cursor active
          while ( (count > objects || count == cDEFAULT)
                  && ((errornum = GetNext(record_, cursorid)) == 0) )
          {
             nDBRecord   *objectp;
                                        // pass record to enable object creation:
             if ( (objectp = (nDBRecord*) AddToList(record_, objects)) != NULL )
             {
                ++objects;
                objectp->SetActive();   // set this record active
             }
          }
          EndBrowse(cursorid);          // terminate browse currency
          cursorid_ = 0;

       }

/*----------------------------------------------------------------------------*/
/*  Test for data base errors.                                                */
/*----------------------------------------------------------------------------*/
       if ( errornum != cDBXR_NORMAL    // these are recoverable conditions
            && errornum != cDBXR_ENDOFDATA
            && errornum != cDBXR_NOTFOUND )
       {                                // all other values are errors
          DataBase()->nDBDiagnostic(Error(), errornum);
       }

    }
    return objects;
}

void nDBRecordSet::WriteLog(const nString& message, nErrorState state, int msgid)
{
	database_->WriteLog(message, state, msgid);
}
