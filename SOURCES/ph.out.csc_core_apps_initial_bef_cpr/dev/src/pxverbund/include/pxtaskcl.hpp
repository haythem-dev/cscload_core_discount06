#ifndef PXTASKCL_INC
#define PXTASKCL_INC

#include "pxbase/pxrecord.hpp"

class nTime;
struct tTASKCONTROL;

class  pxTaskControl : public pxDBRecord
{

public:
// constructors:
               pxTaskControl(pxTaskControl& src);
               pxTaskControl(pxSession *session);
               pxTaskControl(pxSession *session, tTASKCONTROL& src);
               pxTaskControl(pxSession *session, short VertriebszentrumNr, nString ProgName);
//                         DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxTaskControl();
/*@DS
PUBLIC MEMBER OPERATORS
*/
   pxTaskControl&   operator=(const pxTaskControl& src);
//  Assigns the values of 'src' to self and returns a reference to it.

   pxTaskControl&   operator=(const tTASKCONTROL& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend  pxTaskControl&
                Assign(pxTaskControl& dest, const tTASKCONTROL& src);
    friend   tTASKCONTROL&
                Assign(tTASKCONTROL& dest, const pxTaskControl& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

//  Field updates

//  Queries:
    short             VertriebszentrumNr() {return VertriebszentrumNr_ ;}
    long              ZeitUnix()           {return ZeitUnix_           ;}
    nString&          ProgramName()        {return ProgrammName_       ;}

    int               TaskControl(nTime& time);

protected:
    void        Init();

    short       VertriebszentrumNr_ ;      // Vertriebszentrum
    long        ZeitUnix_           ;      // Zeitstempel
    nString     ProgrammName_       ;      // Programm Name

private:
    friend class pxTaskControlList;
};

class pxTaskControlList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
               pxTaskControlList(pxSession *session);
//  destructor:
                virtual ~pxTaskControlList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

   //pxTaskControl*    Find( const nString ProgName, const nString ProgPartner);

protected:

private:
    friend class pxTaskControlListIter;
};

class pxTaskControlListIter : public nDListCollectIter
{

public:
// constructors:
   pxTaskControlListIter(pxTaskControlList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxTaskControlListIter() {;}
};
#endif
