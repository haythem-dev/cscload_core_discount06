#ifndef PXCUSTPHARMGROUP_INC
#define PXCUSTPHARMGROUP_INC

#include "pxbase/pxrecord.hpp"

struct tCUSTOMERPHARMACYGR;

class pxCustPharmGroup : public pxDBRecord
{

public:
// constructors:
                pxCustPharmGroup(pxCustPharmGroup& src);
                pxCustPharmGroup(pxSession *session);
                pxCustPharmGroup(pxSession *session, tCUSTOMERPHARMACYGR& src);
                pxCustPharmGroup(pxSession *session, long CustomerNo, short BranchNo, nString& PharmacyGroupId);
// destructor:
                virtual  ~pxCustPharmGroup();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustPharmGroup&   operator=(const pxCustPharmGroup& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustPharmGroup&   operator=(const tCUSTOMERPHARMACYGR& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustPharmGroup&
                Assign(pxCustPharmGroup& dest, const tCUSTOMERPHARMACYGR& src);
    friend   tCUSTOMERPHARMACYGR&
                Assign(tCUSTOMERPHARMACYGR& dest, const pxCustPharmGroup& src);

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
    long           CustomerNo()        {return CustomerNo_      ;}
    short          BranchNo()          {return BranchNo_        ;}
    nString&        PharmacyGroupId()   {return PharmacyGroupId_ ;}
    short          Ranking()           {return Ranking_         ;}

protected:
    void        Init();

    long       CustomerNo_        ;      // Customernumber
    short      BranchNo_          ;      // Branchnumber
    nString     PharmacyGroupId_   ;      // PharmacyGroupId
    short      Ranking_           ;      // Ranking

private:
    friend class pxCustPharmGroupList;
};

class pxCustPharmGroupList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCustPharmGroupList(pxSession *session);
//  destructor:
                virtual ~pxCustPharmGroupList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long CustomerNo, const short BranchNo,
                         const int     count = 50 );

    void        Clear()        {nDBRecordSet::Clear();}

    pxCustPharmGroup* Find( const nString& PharmacyGroupId );
    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxCustPharmGroupListIter;
};

class pxCustPharmGroupListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustPharmGroupListIter(pxCustPharmGroupList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustPharmGroupListIter() {;}
};
#endif
