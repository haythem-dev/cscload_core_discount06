/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXRANGEMEMBER.HPP
pxRangeMember  class

REVISION HISTORY

08 Feb. 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXRANGEMEMBER_INC
#define PXRANGEMEMBER_INC

#include "pxbase/pxrecord.hpp"

struct tDISCOUNTGRPMEM;

class pxRangeMember : public pxDBRecord
{

public:

// constructors:
                pxRangeMember(pxRangeMember& src);
                pxRangeMember(pxSession *session);
                pxRangeMember(pxSession *session, tDISCOUNTGRPMEM& src);
                pxRangeMember(pxSession *session,
                              short  BranchNo,
                              long   DiscountGrpNo,
                              long   ArticleNo);
// destructor:
                virtual  ~pxRangeMember();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxRangeMember&   operator=(const pxRangeMember& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxRangeMember&   operator=(const tDISCOUNTGRPMEM& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxRangeMember&
                Assign(pxRangeMember& dest, const tDISCOUNTGRPMEM& src);
    friend   tDISCOUNTGRPMEM&
                Assign(tDISCOUNTGRPMEM& dest, const pxRangeMember& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Read(const void *record);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

//  Queries:
    short          BranchNo()          {return BranchNo_         ;}
    long           DiscountGrpNo()     {return DiscountGrpNo_    ;}
    long           ArticleNo()         {return ArticleNo_        ;}
    short          DiscountCondition() {return DiscountCondition_;}
    long           ManufacturerNo()    {return ManufacturerNo_   ;}

    bool           IsCondPackage()     {return DiscountCondition_ == 0;}
    bool           IsCondTablets()     {return DiscountCondition_ == 1;}


protected:
    void        Init();

    short      BranchNo_          ;      // Branchnumber
    long       DiscountGrpNo_     ;      // DiscountGroup Number
    long       ArticleNo_         ;      // Article Number
    short      DiscountCondition_ ;      // DiscountCondition
    long       ManufacturerNo_    ;      // manufactures number

private:
    friend class pxRangeMemberList;
};

class pxRangeMemberList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxRangeMemberList(pxSession *session);
//  destructor:
                virtual ~pxRangeMemberList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  ArticleNo,
                         const int   count  = 1000
                       );
    size_t      Select ( const short BranchNo,
                         const long  ArticleNo,
                         const long  ManufacturerNo,
                         const int   count  = 1000
                       );
    size_t      SelectMembers ( const short BranchNo,
                                const long  DiscountGrpNo,
                                const int   count  = 1000
                              );
    size_t      SelectManuFacturer ( const short BranchNo,
                                const long  ManufacturerNo,
                                const int   count  = 1000
                              );
    bool        Find( const long ArticleNo, const long ManufacturerNo);

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxRangeMemberListIter;
};

class pxRangeMemberListIter : public nDListCollectIter
{

public:
// constructors:
    pxRangeMemberListIter(pxRangeMemberList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxRangeMemberListIter() {;}
};
#endif
