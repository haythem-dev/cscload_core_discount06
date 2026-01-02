/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXOERESTRICTIONTYPES
Customer Group Class.

REVISION HISTORY

27 Aug 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXOERESTRICTIONTYPES_INC
   #define PXOERESTRICTIONTYPES_INC

#include "pxbase/pxrecord.hpp"

struct tOERESTRICTIONTYPES;

class pxOeRestrictionTypes : public pxDBRecord
{
public:


// destructor:
    virtual           ~pxOeRestrictionTypes();
// constructors:
                      pxOeRestrictionTypes(pxOeRestrictionTypes& src);
                      pxOeRestrictionTypes(pxSession *session);
                      pxOeRestrictionTypes(pxSession *session, short RestrictionType,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxOeRestrictionTypes&      operator=(const pxOeRestrictionTypes& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:

    short            RestrictionType      () {return RestrictionType_;              }
    nString&          RestrictionName      () {return RestrictionName_;              }


protected:
                      pxOeRestrictionTypes(pxSession *session, tOERESTRICTIONTYPES& src);
    pxOeRestrictionTypes&      operator=(const tOERESTRICTIONTYPES& src);
    friend
    pxOeRestrictionTypes&      Assign(pxOeRestrictionTypes& dest, const tOERESTRICTIONTYPES& src);
    friend
    tOERESTRICTIONTYPES&    Assign(tOERESTRICTIONTYPES& dest, const pxOeRestrictionTypes& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    void              Init();

    short            RestrictionType_;      // Restriction Type
    nString           RestrictionName_;      // Restriction Name

private:
    friend class pxOeRestrictionTypesList;
};

class pxOeRestrictionTypesList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxOeRestrictionTypesList() {Clear();}
                      pxOeRestrictionTypesList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const short RestrictionType, const int count = cDEFAULT);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxOeRestrictionTypesListIter;
};

class pxOeRestrictionTypesListIter : public nDListCollectIter
{

public:
// constructors:
    pxOeRestrictionTypesListIter(pxOeRestrictionTypesList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOeRestrictionTypesListIter() {;}

};

#endif
