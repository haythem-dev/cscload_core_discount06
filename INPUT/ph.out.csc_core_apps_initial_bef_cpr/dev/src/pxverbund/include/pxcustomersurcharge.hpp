/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxcustomersurcharge.hpp
CUSTOMERSURCHARGE class

REVISION HISTORY

16 Dec 2011 V1.00 REV 00 written by Machata Julian.
*/

#ifndef PXCUSTOMERSURCHARGE_INC
   #define PXCUSTOMERSURCHARGE_INC

#include "pxbase/pxrecord.hpp"

struct tCUSTOMERSURCHARGE;

class pxCustomerSurcharge : public pxDBRecord
{

public:

// constructors:
                pxCustomerSurcharge(pxCustomerSurcharge& src);
                pxCustomerSurcharge(pxSession *session);
                pxCustomerSurcharge(pxSession *session, tCUSTOMERSURCHARGE& src);
                pxCustomerSurcharge(pxSession *session, const pxCustomerSurcharge* src);
                pxCustomerSurcharge(pxSession *session, short BranchNo, long CustomerNo,
														long ManufacturerNo);

// destructor:
                virtual  ~pxCustomerSurcharge();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustomerSurcharge&   operator=(const pxCustomerSurcharge& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustomerSurcharge&   operator=(const tCUSTOMERSURCHARGE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustomerSurcharge&
                Assign(pxCustomerSurcharge& dest, const tCUSTOMERSURCHARGE& src);
    friend   tCUSTOMERSURCHARGE&
                Assign(tCUSTOMERSURCHARGE& dest, const pxCustomerSurcharge& src);
				
    //virtual  int      CompareTo(const nCollectable *that, void *p,
    //                           const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    //virtual  int     Insert(const void *record); // no insert necessary for the moment
    //virtual  int     Update(const void *record); // no update necessary for the moment
    //virtual  int     Delete(const void *record); // no delete necessary for the moment

// Update Fields

//  Queries:
    short          BranchNo()           {return BranchNo_             ;}
    long           CustomerNo()         {return CustomerNo_           ;}
    long           ManufacturerNo()     {return ManufacturerNo_       ;}
    double         SurchargePct()       {return SurchargePct_         ;}

protected:
    void        Init();

    short      BranchNo_           ;      // Branch Number
    long      	CustomerNo_        	;      // Customer Number
    long       ManufacturerNo_     ;      // Manufacturer Number
    double    SurchargePct_		;      // Surcharge Percentage
   
private:
    friend class pxCustomerSurchargeList;
};

class pxCustomerSurchargeList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCustomerSurchargeList(pxSession *session);
//  destructor:
                virtual ~pxCustomerSurchargeList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long CustomerNo,
                         const long ManufacturerNo,
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

    friend class pxCustomerSurchargeListIter;
};

class pxCustomerSurchargeListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustomerSurchargeListIter(pxCustomerSurchargeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustomerSurchargeListIter() {;}
};
#endif
