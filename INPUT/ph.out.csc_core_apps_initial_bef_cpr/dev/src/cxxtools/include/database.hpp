#ifndef DATABASE_INC
#define DATABASE_INC

#include "error.hpp"
#include "dlistcol.hpp"
#include "bitmap.hpp"

/*----------------------------------------------------------------------------*/
/*  Data Base Transaction levels.                                             */
/*----------------------------------------------------------------------------*/
enum tDBTransactLevel
{
    cDBTransNo,                         // No Transaction running
    cDBTransRecord,                     // Transaction set on a record basis
    cDBTransSet,                        // Transaction level is record set
    cDBTransDataBase                    // Transaction level is entire data base
};

/*----------------------------------------------------------------------------*/
/*  Data Base component access modes.                                         */
/*----------------------------------------------------------------------------*/
enum DBAccessMode
{                                       // record access modes:
    cDBGET_DEFAULT   = 0,               // read record, do not lock
    cDBGET_READONLY  = cDBGET_DEFAULT,  // read record, do not lock
    cDBGET_FORUPDATE,                   // read and lock for subsequent update

                                        // Open/Close (record sets etc.)
    cDBOPEN_DEFAULT  = 10,
    cDBOPEN_READONLY = cDBOPEN_DEFAULT, // open read-only processing
    cDBOPEN_INSERT,                     // open for inserting and/or updating
    cDBOPEN_UPDATE,                     // open for updating

    cDBCLOSE_DEFAULT = 20,
    cDBCLOSE_UNLOCK  = cDBCLOSE_DEFAULT, // close processing and release locks
    cDBCLOSE_HOLDLOCKS                  // close record processing, hold locks
};

/*----------------------------------------------------------------------------*/
/*  Data Base class definition.                                               */
/*----------------------------------------------------------------------------*/
class nDataBase : public nError
{

public:

    virtual           ~nDataBase();
                      nDataBase();

//  Public member functions:
    virtual  int     nDBBeginTransaction(const tDBTransactLevel level = cDBTransRecord);
    virtual  int     nDBCommit(const tDBTransactLevel level = cDBTransRecord);
    virtual  int     nDBRollBack();
	virtual  bool	 nDBInTransaction();

    virtual  int     nDBConnect(const std::string& datasrc);
    virtual  int     nDBDisConnect();

    virtual  void    nDBDiagnostic(nError& e, int num = 0);
    virtual
    tDBTransactLevel nDBTransactLevel()   {return TransLevel_;}
    virtual  void    WriteLog(const nString& msg, nErrorState s, int msgid) = 0;


//  The following member function are pure virtual and thus MUST be re-defined
//  when deriving from nDataBase.
    virtual int         Connect(const std::string& datasrc) = 0;
    virtual int         DisConnect()         = 0;    
    virtual bool        IsOpen() const = 0;

    virtual int         GetSqlCode()         = 0;
	virtual int         GetIsamCode()        = 0;

    virtual const std::string GetSqlMessage()      = 0;
    virtual const std::string GetTableName()       = 0;
    virtual const std::string GetFunctionName()    = 0;

private:

	virtual int         BeginTransaction()   = 0;
    virtual int         Commit()             = 0;
    virtual int         RollBack()           = 0;

    tDBTransactLevel  TransLevel_;
};

class nDBRecord : public nCollectable, public nError
{

#define   bDBRECORD_ACTIVE           0  // Flags record active
#define   bDBRECORD_LOCKED           1  // Record is locked transaction-based
#define   bDBRECORD_LOCKED_HOLD      2  // Lock is held until explicitly unlocked
#define   bDBRECORD_DIRTY            3  // At least one record field is dirty
#define   bDBRECORD_OPENED           4  // Record insert/update processing is open

#define   cDBRECORD_MAPWIDTH         8

public:

                      nDBRecord() : state_(cDBRECORD_MAPWIDTH), database_(NULL)  {;}
                      nDBRecord(nDataBase *db) : state_(cDBRECORD_MAPWIDTH), database_(db) {;}
    virtual           ~nDBRecord()   {;}

    virtual  int      nDBBeginTransaction(const tDBTransactLevel level = cDBTransRecord)
                      {return DataBase()->nDBBeginTransaction(level);}
    virtual  int      nDBCommit(const tDBTransactLevel level = cDBTransRecord)
                      {return DataBase()->nDBCommit(level);}
    virtual  int      nDBRollBack()
                      {return DataBase()->nDBRollBack();}
    virtual  int      nDBDelete(const void *record);
    virtual  int      nDBRead(const void *record);
    virtual  int      nDBReadLock(const void *record);
    virtual  int      nDBWrite(const void *record, size_t recsize);
    virtual  void     WriteLog(const nString& msg, nErrorState s, int msgid);
             nDataBase* DataBase() const   {return database_;}
             nDataBase* Session() const    {return database_;}

    virtual  int      Delete(const void * /*record*/ ) { return 1; }
    virtual  int      Insert(const void * /*record*/ ) { return 1; }
             bool     IsActive ()         { return state_.TestBit(bDBRECORD_ACTIVE); }
             bool     IsDirty  ()         { return state_.TestBit(bDBRECORD_DIRTY ); }
             bool     IsLocked ()         { return state_.TestBit(bDBRECORD_LOCKED); }
             bool     IsLockHeld()        { return state_.TestBit(bDBRECORD_LOCKED_HOLD); }
             bool     IsOpen()            { return state_.TestBit(bDBRECORD_OPENED); }
    virtual  int      Read    (const void * /*record*/ ) { return 1; };
    virtual  int      ReadLock(const void * /*record*/ ) { return 1; };
    virtual  int      Update  (const void * /*record*/ ) { return 1; };

protected:
             void     ClearActive()       { state_.ClearBit(bDBRECORD_ACTIVE   ); }
             void     ClearDirty()        { state_.ClearBit(bDBRECORD_DIRTY   ); }
             void     ClearLocked()       { state_.ClearBit(bDBRECORD_LOCKED   ); }
             void     ClearLockHeld()     { state_.ClearBit(bDBRECORD_LOCKED_HOLD); }
             void     ClearOpen()         { state_.ClearBit(bDBRECORD_OPENED); }

             void     SetActive()         { state_.SetBit(bDBRECORD_ACTIVE); }
             void     SetDirty()          { state_.SetBit(bDBRECORD_DIRTY ); }
             void     SetLocked()         { state_.SetBit(bDBRECORD_LOCKED); }
             void     SetLockHeld()       { state_.SetBit(bDBRECORD_LOCKED_HOLD); }
             void     SetOpen()           { state_.SetBit(bDBRECORD_OPENED); }
private:
    friend   class    nDBRecordSet;

             nBitMap  state_;
             nDataBase *database_;

};

class nDBRecordSet : public nError
{

protected:
    nDBRecordSet(nDataBase* db, nDListCollect* list = NULL)
                       {database_ = db, objlist_ = list, cursorid_ = 0;}

             nDataBase      *database_;
             nDListCollect  *objlist_;
             int            cursorid_;
public:

    virtual           ~nDBRecordSet()   {;}
    virtual  void     Clear();
    virtual  void     WriteLog(const nString& msg, nErrorState s, int msgid);
             nDataBase* DataBase()      {return database_;}
             int      nDBGetCursorId()  {return cursorid_;}
             void     nDBSetList(nDListCollect *list) {objlist_ = list;}
    virtual  int      nDBSelect(
                                 const void   *keys    = NULL,
                                 const int    cursorid =  0,
                                 const int    count    = 50,
                                 const void   *record = NULL
                               );

    virtual  int      EndBrowse     (const int    cursorid ) = 0;
    virtual  int      GetNext       (const void * record   ,
                                     const int    cursorid ) = 0;
    virtual  nCollectable* AddToList(const void * record   , 
                                     const int    row      ) = 0;
    virtual  int      StartBrowse   (const void * keys      , 
                                     const int    cursorid ) = 0;

};

#endif                                  // for ifndef DATABASE_DOTH
