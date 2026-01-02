#include "pxcstbas.hpp"
#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxCustBaseList :: pxCustBaseList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using single string value arguments.                 */
/*----------------------------------------------------------------------------*/
size_t
pxCustBaseList :: Select
(
    const char  *MatchCode,
    const int     count_                // Max number of records to read
)

{

    tKUNDE k;
    memset(&k, 0, sizeof(tKUNDE));     // zero out entire record buffer
    nString  mc = MatchCode;
    mc.ToUpper();
    mc.GetData(k.MatchCode);
    return Select(&k, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tKUNDE structure.      */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxCustBaseList :: Select
(
          tKUNDE   *kundep,
    const int     count_
)

{
    // Set the cursor id:
    int cursorid = cCRS_DEFAULT;
    nDBSelect(kundep, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustBaseList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxCustBase *objectp = new pxCustBase(Session(), *(tKUNDE*) record); // construct new object
    InsertAscending(objectp);
    return objectp;
}

int
pxCustBaseList :: EndBrowse
(
    const int  cursorid
)
{

    return pxKundeEndBrowse(cursorid);
}


int
pxCustBaseList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxKundeGetNext((tKUNDE*)record, cursorid);
}

int
pxCustBaseList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxKundeStartBrowse((tKUNDE*)keys, cursorid);
}
