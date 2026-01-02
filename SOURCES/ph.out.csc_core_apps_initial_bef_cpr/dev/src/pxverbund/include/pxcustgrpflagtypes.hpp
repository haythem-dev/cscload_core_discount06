/*----------------------------------------------------------------------------*/

#ifndef PXCUSTGRPFLAGTYPES_INC
#define PXCUSTGRPFLAGTYPES_INC

/*----------------------------------------------------------------------------*/

#include "pxbase/pxrecord.hpp"

struct tCUSTGRPFLAGTYPES;

class pxCustGrpFlagTypes : public pxDBRecord
{
public:


// destructor:
    virtual           ~pxCustGrpFlagTypes();
// constructors:
                      pxCustGrpFlagTypes(pxCustGrpFlagTypes& src);
                      pxCustGrpFlagTypes(pxSession *session);
                      pxCustGrpFlagTypes(pxSession *session, short BranchNo, short CustGrpFlagType,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxCustGrpFlagTypes&      operator=(const pxCustGrpFlagTypes& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:

    short            BranchNo        () {return BranchNo_;                    }
    short            CustGrpFlagType () {return CustGrpFlagType_;             }
    nString&          Description     () {return Description_;                 }
    short            Index_DKKGR     () {return Index_DKKGR_;                 }


protected:
                      pxCustGrpFlagTypes(pxSession *session, tCUSTGRPFLAGTYPES& src);
    pxCustGrpFlagTypes&      operator=(const tCUSTGRPFLAGTYPES& src);
    friend
    pxCustGrpFlagTypes&      Assign(pxCustGrpFlagTypes& dest, const tCUSTGRPFLAGTYPES& src);
    friend
    tCUSTGRPFLAGTYPES&    Assign(tCUSTGRPFLAGTYPES& dest, const pxCustGrpFlagTypes& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    void              Init();

    short            BranchNo_;        // Branchno
    short            CustGrpFlagType_; // Flagtype
    nString           Description_;     // Description
    short            Index_DKKGR_;     // Index

private:
    friend class pxCustGrpFlagTypesList;
};

class pxCustGrpFlagTypesList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxCustGrpFlagTypesList() {Clear();}
                      pxCustGrpFlagTypesList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const short BranchNo, const int count = cDEFAULT);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxCustGrpFlagTypesListIter;
};

class pxCustGrpFlagTypesListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustGrpFlagTypesListIter(pxCustGrpFlagTypesList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustGrpFlagTypesListIter() {;}

};

#endif
