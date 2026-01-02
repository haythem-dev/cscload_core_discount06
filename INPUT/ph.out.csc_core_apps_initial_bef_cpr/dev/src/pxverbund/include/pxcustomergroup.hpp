#ifndef PXCUSTOMERGROUP_INC
#define PXCUSTOMERGROUP_INC

/*----------------------------------------------------------------------------*/

#include "pxbase/pxrecord.hpp"

struct tCUSTOMERGROUP;

/*----------------------------------------------------------------------------*/

class pxCustomerGroup : public pxDBRecord
{
public:


// destructor:
    virtual           ~pxCustomerGroup();
// constructors:
                      pxCustomerGroup(pxCustomerGroup& src);
                      pxCustomerGroup(pxSession *session);
                      pxCustomerGroup(pxSession *session, short BranchNo, short CustomerGroupNo,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxCustomerGroup&      operator=(const pxCustomerGroup& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:

    short            BranchNo        () {return BranchNo_;                    }
    short            CustomerGroupNo () {return CustomerGroupNo_;             }
    nString&          Name            () {return Name_;                        }
    nString&          Sales_Restr_PH  () {return Sales_Restr_PH_;              }
    short            Block_Flag      () {return Block_Flag_;                  }
    short            BasisNatra_Flag () {return BasisNatra_Flag_;             }


protected:
                      pxCustomerGroup(pxSession *session, tCUSTOMERGROUP& src);
    pxCustomerGroup&      operator=(const tCUSTOMERGROUP& src);
    friend
    pxCustomerGroup&      Assign(pxCustomerGroup& dest, const tCUSTOMERGROUP& src);
    friend
    tCUSTOMERGROUP&    Assign(tCUSTOMERGROUP& dest, const pxCustomerGroup& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    void              Init();

    short            BranchNo_;        // Branchno
    short            CustomerGroupNo_; // Kundengruppe
    nString           Name_;            // Kundengruppe Text
    nString           Sales_Restr_PH_;  // Vertriebsbindungen
    short            Block_Flag_;      // ??
    short            BasisNatra_Flag_; // ??

private:
    friend class pxCustomerGroupList;
};

class pxCustomerGroupList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxCustomerGroupList() {Clear();}
                      pxCustomerGroupList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const short BranchNo, const short CustomerGroupNo, const int count = cDEFAULT);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxCustomerGroupListIter;
};

class pxCustomerGroupListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustomerGroupListIter(pxCustomerGroupList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustomerGroupListIter() {;}

};

#endif
