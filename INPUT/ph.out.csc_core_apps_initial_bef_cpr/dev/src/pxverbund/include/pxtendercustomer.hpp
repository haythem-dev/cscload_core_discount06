/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxtendercustomer.hpp
TENDERCUSTOMER  class

REVISION HISTORY

24 Oct 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXTENDERCUSTOMER_INC
   #define PXTENDERCUSTOMER_INC

#include "pxbase/pxrecord.hpp"

struct tTENDERCUSTOMER;

class pxTenderCustomer : public pxDBRecord
{

public:
// constructors:
                pxTenderCustomer(pxTenderCustomer& src);
                pxTenderCustomer(pxSession *session);
                pxTenderCustomer(pxSession *session, tTENDERCUSTOMER& src);
                pxTenderCustomer(pxSession *session, const pxTenderCustomer* src);
                pxTenderCustomer(pxSession *session, long TenderNo,
                                                 short BranchNo,
                                                 long  CustomerNo);

// destructor:
                virtual  ~pxTenderCustomer();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxTenderCustomer&   operator=(const pxTenderCustomer& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxTenderCustomer&   operator=(const tTENDERCUSTOMER& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxTenderCustomer&
                Assign(pxTenderCustomer& dest, const tTENDERCUSTOMER& src);
    friend   tTENDERCUSTOMER&
                Assign(tTENDERCUSTOMER& dest, const pxTenderCustomer& src);

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

// Update Fields

//  Queries:
    long           TenderNo()     {return TenderNo_             ;}
    short          BranchNo()     {return BranchNo_             ;}
    long           CustomerNo()   {return CustomerNo_           ;}

// Set Methodes

protected:
    void        Init();

    long       TenderNo_           ;      // Tender Number
    short      BranchNo_           ;      // Branch Number
    long       CustomerNo_         ;      // Customer Number

private:
    friend class pxTenderCustomerList;
};

class pxTenderCustomerList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxTenderCustomerList(pxSession *session);
//  destructor:
                virtual ~pxTenderCustomerList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long TenderNo,
                         const short BranchNo,
                         const long  CustomerNo,
                         const int   count  = 1000
                       );

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxTenderCustomerListIter;
};

class pxTenderCustomerListIter : public nDListCollectIter
{

public:
// constructors:
    pxTenderCustomerListIter(pxTenderCustomerList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxTenderCustomerListIter() {;}
};
#endif
