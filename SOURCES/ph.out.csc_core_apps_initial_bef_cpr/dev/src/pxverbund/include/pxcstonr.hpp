#ifndef PXCSTONR_DOTH
#define PXCSTONR_DOTH

#include "pxbase/pxrecord.hpp"
#include <money.hpp>

struct tCUSTOMERORDERNO;

class pxCustOrderNumber : public pxDBRecord
{

public:
    virtual           ~pxCustOrderNumber();
// constructors:
                      pxCustOrderNumber(pxCustOrderNumber& src);
                      pxCustOrderNumber(pxSession *session);
                      pxCustOrderNumber(pxSession *session, short BranchNo, long CustomerNo,
                                        const nString& CustomerOrderNo,
                                        const nString& ProcessNo,DBAccessMode mode = cDBGET_READONLY);
                      pxCustOrderNumber(pxSession *session, short BranchNo, long CustomerNo, nMoney OrderValue);

    pxCustOrderNumber&       operator=(const pxCustOrderNumber& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:

    short            BranchNo() const    { return BranchNo_;              }
    long             CustomerNo()        { return CustomerNo_;            }
    nString&          CustomerOrderNo()   { return CustomerOrderNo_;       }
    long             ProcessNo() const   { return ProcessNo_;             }
    nMoney            OrderValue()        { return OrderValue_;            }

// Update members
    void              SetOrderValue(nMoney ordervalue) {OrderValue_ = ordervalue;}
    void              SetCustomerOrderNo( nString& num )
                      { CustomerOrderNo_ = num;        }
protected:
    pxCustOrderNumber(pxSession *session, tCUSTOMERORDERNO& src);
    pxCustOrderNumber&       operator=(const tCUSTOMERORDERNO& src);
    friend   pxCustOrderNumber&     Assign(pxCustOrderNumber& dest, const tCUSTOMERORDERNO& src);
    friend   tCUSTOMERORDERNO&  Assign(tCUSTOMERORDERNO& dest, const pxCustOrderNumber& src);
    virtual  int     Read(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);
    void              Init();


    short            BranchNo_;        // Branchnumber
    long             CustomerNo_;      // Phoenix-Customernumber.
    nString           CustomerOrderNo_; // Pharmacy Ordernumber
    long             ProcessNo_;       // Apothekers Vorgangsnummer
    nMoney            OrderValue_;      // Auftragswert*AnzPos

private:
    friend class pxCustOrderNumberList;
};
class pxCustOrderNumberList : public nDListCollect, public nDBRecordSet
{

public:
                   pxCustOrderNumberList(pxSession *session);
    virtual        ~pxCustOrderNumberList() {Clear();}

    pxSession*     Session()         { return (pxSession*) DataBase();}
    size_t         Select (const short VertriebszentrumNr, const long KundenNr,
                           const nMoney& Ordervalue,
                           const int count = 200);
    size_t         Select (const short VertriebszentrumNr, const long KundenNr,
                           const nMoney& Ordervalue, const nString& CustomerOrderNo,
                           const int count = 200);
    void           Clear()           {nDBRecordSet::Clear();}
    virtual  int  EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int  GetNext(const void* record, const int cursorid);
    virtual  int  StartBrowse(const void *keys, const int cursorid);

protected:


private:

    friend class pxCustOrderNumberListIter;
};

class pxCustOrderNumberListIter : public nDListCollectIter
{
public:
                   pxCustOrderNumberListIter(pxCustOrderNumberList& list)
                                       : nDListCollectIter(list) {;}
    virtual        ~pxCustOrderNumberListIter() {;}
};
#endif
