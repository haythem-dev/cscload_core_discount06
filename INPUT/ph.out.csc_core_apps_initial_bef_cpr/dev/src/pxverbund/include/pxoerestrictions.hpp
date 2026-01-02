/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXOERESTRICTIONS
Customer Group Class.

REVISION HISTORY

06 Aug 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXOERESTRICTIONS_INC
   #define PXOERESTRICTIONS_INC

#include "pxbase/pxrecord.hpp"

struct tORDERENTRYRESTRICTIONS;

class pxOeRestrictions : public pxDBRecord
{
public:


    enum tRestrictionTypes
    {
       RestrictionType_Business				= 1, // 1 = Businesss type
       RestrictionType_Manufacturer			= 2, // 2 = Manufacture
	   RestrictionType_LongTermLackCheck	= 3  // 3 = check longtermlack depending on subdevicetype
    };



// destructor:
    virtual           ~pxOeRestrictions();
// constructors:
                      pxOeRestrictions(pxOeRestrictions& src);
                      pxOeRestrictions(pxSession *session);
                      pxOeRestrictions(pxSession *session, short BranchNo, short RestrictionType,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxOeRestrictions&      operator=(const pxOeRestrictions& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:

    short            BranchNo         () {return BranchNo_;                    }
    short            RestrictionType  () {return RestrictionType_;             }
    short            RestrictionValue () {return RestrictionValue_;            }
    short            OriginType       () {return OriginType_;                  }


protected:
                      pxOeRestrictions(pxSession *session, tORDERENTRYRESTRICTIONS& src);
    pxOeRestrictions&      operator=(const tORDERENTRYRESTRICTIONS& src);
    friend
    pxOeRestrictions&      Assign(pxOeRestrictions& dest, const tORDERENTRYRESTRICTIONS& src);
    friend
    tORDERENTRYRESTRICTIONS&    Assign(tORDERENTRYRESTRICTIONS& dest, const pxOeRestrictions& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    void              Init();

    short            BranchNo_;         // Branchno
    short            RestrictionType_;  // Restriction Type
    short            RestrictionValue_; // Restriction Value
    short            OriginType_;       // Origin Type

private:
    friend class pxOeRestrictionsList;
};

class pxOeRestrictionsList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxOeRestrictionsList() {Clear();}
                      pxOeRestrictionsList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const short BranchNo, const int count = cDEFAULT);
    size_t            Select(const short BranchNo, const short RestrictionType, const short RestrictionValue, const short OriginType, int count = cDEFAULT);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxOeRestrictionsListIter;
};

class pxOeRestrictionsListIter : public nDListCollectIter
{

public:
// constructors:
    pxOeRestrictionsListIter(pxOeRestrictionsList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOeRestrictionsListIter() {;}

};

#endif
