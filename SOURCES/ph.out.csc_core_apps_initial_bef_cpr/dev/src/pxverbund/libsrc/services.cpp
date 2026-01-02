/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxServices methods.

*/

#include "pxservices.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxServices :: pxServices
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxServices :: pxServices
(
    pxServices& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tSERVICES structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxServices :: pxServices
(
    pxSession   *session,
    tSERVICES& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxServices :: pxServices
(
    pxSession   *session,
    short      Service_No,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    Service_No_        = Service_No;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxServices :: ~pxServices()
{
        ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tSERVICES structure.       */
/*----------------------------------------------------------------------------*/
tSERVICES&
Assign
(
    tSERVICES&    dest,
    const pxServices&  src
)
{
    // Copy native data types:
    dest.Service_No        = src.Service_No_;
    dest.ServiceTypeNo     = src.ServiceTypeNo_;
    // Strings:
    dest.Name[0] = ' ';
    src.Name_.GetData(dest.Name);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' structure to a pxServices object.     */
/*----------------------------------------------------------------------------*/
pxServices&
Assign
(
    pxServices&           dest,
    const tSERVICES&   src
)
{
    dest.Service_No_        = src.Service_No;
    dest.Name_              = src.Name;
    dest.ServiceTypeNo_     = src.ServiceTypeNo;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxServices :: Init()
{
    tSERVICES    record;
    memset(&record, 0 , sizeof(tSERVICES));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tSERVICES struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxServices&
pxServices :: operator=( const pxServices& src)
{
    tSERVICES record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tSERVICES structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxServices&
pxServices :: operator=( const tSERVICES& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxServices :: Get
(
    DBAccessMode mode
)

{
    tSERVICES record;
    memset(&record, 0, sizeof(tSERVICES));
    record.Service_No        = Service_No_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;             // import the data from tSERVICES struct
    /*se if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(),
                            CMSG_CST_GRP_NOTFOUND,
                            record.CustomerGroupNo, 0),
                   CMSG_CST_GRP_NOTFOUND);
    */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxServices :: Put
(
)
{
    tSERVICES record;
    memset(&record, 0, sizeof(tSERVICES));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tSERVICES));
}


/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxServices :: Read
(
    const void  *record
)
{
    return pxServicesRead((tSERVICES*)record);
}

int
pxServices :: ReadLock
(
    const void  *record
)
{
    return pxServicesReadLock((tSERVICES*)record);
}

int
pxServices :: Update
(
    const void  *record
)
{
    return pxServicesUpdate((tSERVICES*)record);
}

int
pxServices :: Insert
(
    const void  *record
)
{
    return pxServicesInsert((tSERVICES*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxServices list  */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxServices :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxServices *that = (pxServices*)That;
    int retval = (Service_No_ == that->Service_No_) ? 0
                : (Service_No_ > that->Service_No_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxServicesList :: pxServicesList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}


/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxServicesList :: Select
(
    const int     count_
)
{
    tSERVICES record;
    memset(&record, 0, sizeof(tSERVICES));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxServicesList :: Select
(
    const short   ServiceNo,
    const int     count_
)
{
    tSERVICES record;
    memset(&record, 0, sizeof(tSERVICES));  // zero out entire record buffer
    record.Service_No = ServiceNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxServicesList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxServices' object:
    pxServices *objectp = new pxServices(Session(), *(tSERVICES*)recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxServicesList :: EndBrowse
(
    const int  cursorid
)
{
    return pxServicesEndBrowse(cursorid);
}


int
pxServicesList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxServicesGetNext((tSERVICES*)recordp, cursorid);
}

int
pxServicesList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxServicesStartBrowse((tSERVICES*)keys, cursorid);
}
