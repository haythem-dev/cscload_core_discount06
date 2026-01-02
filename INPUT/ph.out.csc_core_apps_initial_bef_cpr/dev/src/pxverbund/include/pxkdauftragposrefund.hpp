/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXKDAUFTRAGPOSREFUND.HPP
Customer Group Class.

REVISION HISTORY

27 May 2010 V1.00 REV 00 written by Beatrix Troemel
*/

#ifndef PXKDAUFTRAGPOSREFUND_INC
   #define PXKDAUFTRAGPOSREFUND_INC

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAGPOSREFUND;

class pxKdAuftragPosRefund : public pxDBRecord
{
public:
// destructor:
    virtual           ~pxKdAuftragPosRefund();

        // constructors:
        pxKdAuftragPosRefund(pxKdAuftragPosRefund& src);
        pxKdAuftragPosRefund(pxSession *session);
        pxKdAuftragPosRefund(pxSession *session, const long KdAuftragNr, const long PosNr, const double RefundValue, const short RefundSrc, const short Promotion_No);

    pxKdAuftragPosRefund&      operator=(const pxKdAuftragPosRefund& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

//  Queries:

    long KdAuftragNr() {return KdAuftragNr_;}
    long PosNr() {return PosNr_;}
    double RefundValue() {return RefundValue_;}
    short RefundSrc() {return RefundSrc_;}
    short Promotion_No() {return Promotion_No_;}

protected:
        pxKdAuftragPosRefund(pxSession *session, tKDAUFTRAGPOSREFUND& src);
    pxKdAuftragPosRefund&      operator=(const tKDAUFTRAGPOSREFUND& src);

        friend
    pxKdAuftragPosRefund&      Assign(pxKdAuftragPosRefund& dest, const tKDAUFTRAGPOSREFUND& src);

        friend
    tKDAUFTRAGPOSREFUND&    Assign(tKDAUFTRAGPOSREFUND& dest, const pxKdAuftragPosRefund& src);

        virtual  int      CompareTo(const nCollectable *that, void *p, const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);
    void              Init();

    long KdAuftragNr_;
    long PosNr_;
    double RefundValue_;
    short RefundSrc_;
    short Promotion_No_;

private:
    friend class pxKdAuftragPosRefundList;
};

class pxKdAuftragPosRefundList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxKdAuftragPosRefundList() {Clear();}
                      pxKdAuftragPosRefundList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const long KdAuftragNr, const long PosNr, const int count = cDEFAULT);
    pxKdAuftragPosRefund* Find(const short PomotionNo);

    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxKdAuftragPosRefundListIter;
};

class pxKdAuftragPosRefundListIter : public nDListCollectIter
{

public:
// constructors:
    pxKdAuftragPosRefundListIter(pxKdAuftragPosRefundList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxKdAuftragPosRefundListIter() {;}

};

#endif
