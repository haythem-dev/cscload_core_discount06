/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXOEORIGINTYPES
Customer Group Class.

REVISION HISTORY

27 Aug 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXOEORIGINTYPES_INC
   #define PXOEORIGINTYPES_INC

#include "pxbase/pxrecord.hpp"

struct tOEORIGINTYPES;

class pxOeOriginTypes : public pxDBRecord
{
public:


// destructor:
    virtual           ~pxOeOriginTypes();
// constructors:
                      pxOeOriginTypes(pxOeOriginTypes& src);
                      pxOeOriginTypes(pxSession *session);
                      pxOeOriginTypes(pxSession *session, short OriginType,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxOeOriginTypes&      operator=(const pxOeOriginTypes& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:

    short            OriginType      () {return OriginType_;                   }
    nString&          OriginDevice    () {return OriginDevice_;                 }


protected:
                      pxOeOriginTypes(pxSession *session, tOEORIGINTYPES& src);
    pxOeOriginTypes&      operator=(const tOEORIGINTYPES& src);
    friend
    pxOeOriginTypes&      Assign(pxOeOriginTypes& dest, const tOEORIGINTYPES& src);
    friend
    tOEORIGINTYPES&    Assign(tOEORIGINTYPES& dest, const pxOeOriginTypes& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    void              Init();

    short            OriginType_;      // OriginType
    nString           OriginDevice_;    // Origin Device

private:
    friend class pxOeOriginTypesList;
};

class pxOeOriginTypesList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxOeOriginTypesList() {Clear();}
                      pxOeOriginTypesList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const nString& OriginDevice, const int count = cDEFAULT);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxOeOriginTypesListIter;
};

class pxOeOriginTypesListIter : public nDListCollectIter
{

public:
// constructors:
    pxOeOriginTypesListIter(pxOeOriginTypesList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOeOriginTypesListIter() {;}

};

#endif
