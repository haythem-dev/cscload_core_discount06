/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxKdAuftraDebtRel Class.

REVISION HISTORY

 08 June 2012 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXKDAUFTRAGDEBTREL_INC
   #define PXKDAUFTRAGDEBTREL_INC

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAGDEBTREL;

class pxKdAuftragDebtRel : public pxDBRecord
{
public:
// constructors:
    pxKdAuftragDebtRel(pxKdAuftragDebtRel& src);
    pxKdAuftragDebtRel(pxSession *session);
    pxKdAuftragDebtRel(pxSession *session, tKDAUFTRAGDEBTREL& src);
    pxKdAuftragDebtRel(pxSession *session, const long KdAuftragNr, const long relCounter);
// destructor:
    virtual  ~pxKdAuftragDebtRel();

// PUBLIC MEMBER OPERATORS
    pxKdAuftragDebtRel& operator=(const pxKdAuftragDebtRel& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxKdAuftragDebtRel& operator=(const tKDAUFTRAGDEBTREL& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

// PUBLIC MEMBER FUNCTIONS
    friend   pxKdAuftragDebtRel&
                Assign(pxKdAuftragDebtRel& dest, const tKDAUFTRAGDEBTREL& src);
    friend   tKDAUFTRAGDEBTREL&
                Assign(tKDAUFTRAGDEBTREL& dest, const pxKdAuftragDebtRel& src);

    virtual  int CompareTo(const nCollectable* that, void* p, const long lparm) const;

    virtual  int Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int Put();
    virtual  int Delete();

    virtual  int Read(const void* record);
    virtual  int ReadLock(const void* record);
    virtual  int Insert(const void* record);
    virtual  int Update(const void* record);
    virtual  int Delete(const void* record);

//  Queries:
    long        KdAuftragNr()           { return KdAuftragNr_     ; }
    nString&    RelReason()             { return RelReason_       ; }
    nString&    RelComment()            { return RelComment_      ; }
    nString&    RelUser()               { return RelUser_         ; }
    short&      IsReleased()            { return IsReleased_      ; }
    short&      IsDiscussionNeeded()    { return DiscussionNeeded_; }
    long&       RelCounter()            { return RelCounter_      ; }
    short&      CancelCounter()         { return CancelCounter_   ; }
    short&      ApprovalCounter()       { return ApprovalCounter_ ; }
    double&     DebtLimit()             { return DebtLimit_       ; }
    double&     UsedDebtLimit()         { return UsedDebtLimit_   ; }
    double&     OrderValue()            { return OrderValue_      ; }

//  Field Updates:
    void        SetRelReason(const nString& ref)
                { RelReason_ = ref; SetDirty(); }
    void        SetRelComment(const nString& ref)
                { RelComment_ = ref; SetDirty(); }
    void        SetRelUser(const nString& ref)
                { RelUser_ = ref; SetDirty(); }
    void        SetIsReleased(const short& ref)
                { IsReleased_ = ref; SetDirty(); }
    void        SetDiscussionNeeded(const short& ref)
                { DiscussionNeeded_ = ref; SetDirty(); }
    void        SetRelCounter(const long& ref)
                { RelCounter_ = ref; SetDirty(); }
    void        SetApprovalCounter(const short& ref)
                { ApprovalCounter_ = ref; SetDirty(); }
    void        SetCancelCounter(const short& ref)
                { CancelCounter_ = ref; SetDirty(); }
    void        SetDebtLimit(const double& ref)
                { DebtLimit_ = ref; SetDirty(); }
    void        SetUsedDebtLimit(const double& ref)
                { UsedDebtLimit_ = ref; SetDirty(); }
    void        SetOrderValue(const double& ref)
                { OrderValue_ = ref; SetDirty(); }

protected:
    void        Init();

    long        KdAuftragNr_;           // Ordernumber
    nString     RelReason_;             // Release reason
    nString     RelComment_;            // Release comment
    nString     RelUser_;               // Release user
    short       IsReleased_;            // Release user
    short       DiscussionNeeded_;
    long        RelCounter_;
    short       CancelCounter_;
    short       ApprovalCounter_;
    double      DebtLimit_;
    double      UsedDebtLimit_;
    double      OrderValue_;

private:
    friend class pxKdAuftragDebtRelList;
};

class pxKdAuftragDebtRelList : public nDBRecordSet, public nDListCollect
{
public:
//  constructors:
    pxKdAuftragDebtRelList(pxSession *session);
//  destructor:
    virtual ~pxKdAuftragDebtRelList() { Clear(); }

//  member functions:
    pxSession* Session() { return (pxSession*) DataBase(); }

    size_t  Select(const long KdAuftragNr,const int count = 500);
    size_t  SelectApprovalData(const long KdAuftragNr, const int count = 500);
    int     SelectDataForMaxRelCount(const long KdAuftragNr, const int count = 500);
    int     SelectUserVote(const long KdAuftragNr, const nString& userName, const int count = 500);
    int     SelectVote(const long KdAuftragNr, const int count = 500);
    int     SelectForCopy(const long KdAuftragNr, const int count = 500);
    void    Clear() { nDBRecordSet::Clear(); }

    virtual nCollectable*
                AddToList(const void* record, const int row);
    virtual int GetNext(const void *record, const int cursorid);
    virtual int StartBrowse(const void* keys, const int cursorid);
    virtual int EndBrowse(const int cursorid);

private:
    friend class pxKdAuftragDebtRelListIter;
};

class pxKdAuftragDebtRelListIter : public nDListCollectIter
{
public:
// constructors:
    pxKdAuftragDebtRelListIter(pxKdAuftragDebtRelList& list) : nDListCollectIter(list) {}
// destructor:
    virtual  ~pxKdAuftragDebtRelListIter() {}
};

#endif
