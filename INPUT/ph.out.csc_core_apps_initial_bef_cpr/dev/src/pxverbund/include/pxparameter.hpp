/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxparameter.hpp
pxParamter Class.

REVISION HISTORY

13 March 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXPARAMETER_INC
#define PXPARAMETER_INC

#include "pxbase/pxrecord.hpp"
#include "pxparameterdef.h"

struct tPARAMETER;

class pxParameter : public pxDBRecord
{

public:


// constructors:
                pxParameter(pxParameter& src);
                pxParameter(pxSession *session);
                pxParameter(pxSession *session, tPARAMETER& src);
                pxParameter(pxSession *session, const short FilialNr,
                            const nString& ProgrammName,
                            const nString& Zweck,
                            const nString& ParameterName);
                            //DBAccessMode mode = cDBGET_READONLY);

// destructor:
                virtual  ~pxParameter();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxParameter&   operator=(const pxParameter& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxParameter&   operator=(const tPARAMETER& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxParameter&
                Assign(pxParameter& dest, const tPARAMETER& src);
    friend   tPARAMETER&
                Assign(tPARAMETER& dest, const pxParameter& src);

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

//  Queries:
    short            FilialNr()           {return FilialNr_           ;}
    nString&          ProgrammName()       {return ProgrammName_       ;}
    nString&          Zweck()              {return Zweck_              ;}
    nString&          ParameterName()      {return ParameterName_      ;}
    nString&          AusPraegung()        {return AusPraegung_        ;}
    long             Wert()               {return Wert_               ;}

protected:
    void        Init();

    short      FilialNr_          ;      // Filialnumber
    nString     ProgrammName_      ;      // Programmname
    nString     Zweck_             ;      // Zweck
    nString     ParameterName_     ;      // Parametername
    nString     AusPraegung_       ;      // Auspreagung
    long       Wert_              ;      // Wert

private:
    friend class pxParameterList;
};

class pxParameterList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxParameterList(pxSession *session);
//  destructor:
                virtual ~pxParameterList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short FilialNr, const nString& ProgrammName,
                         const nString& Zweck, const nString& ParameterName,
                         const long Wert, const int count = 50 );
    size_t      Select ( const short FilialNr, const nString& ProgrammName,
                         const nString& Zweck, const nString& ParameterName,
                         const int count = 50 );
    pxParameter*  Find(const nString& AusPraegung);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxParameterListIter;
};

class pxParameterListIter : public nDListCollectIter
{

public:
// constructors:
    pxParameterListIter(pxParameterList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxParameterListIter() {;}
};
#endif
