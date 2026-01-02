/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxManufacturerGroup Class.

REVISION HISTORY

06 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXMANUFACTURERGROUP_INC
#define PXMANUFACTURERGROUP_INC

#include "pxbase/pxrecord.hpp"

struct tMANUFACTURERGROUP;

class pxManufacturerGroup : public pxDBRecord
{

public:


// constructors:
                pxManufacturerGroup(pxManufacturerGroup& src);
                pxManufacturerGroup(pxSession *session);
                pxManufacturerGroup(pxSession *session, tMANUFACTURERGROUP& src);
// destructor:
                virtual  ~pxManufacturerGroup();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxManufacturerGroup&   operator=(const pxManufacturerGroup& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxManufacturerGroup&   operator=(const tMANUFACTURERGROUP& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxManufacturerGroup&
                Assign(pxManufacturerGroup& dest, const tMANUFACTURERGROUP& src);
    friend   tMANUFACTURERGROUP&
                Assign(tMANUFACTURERGROUP& dest, const pxManufacturerGroup& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

//  Queries:

    nString&        PharmacyGroupID()      {return PharmacyGroupID_      ;}
    long          KonsigPartnerNr()      {return KonsigPartnerNr_      ;}

//  Field Updates:


protected:
    void        Init();

    nString        PharmacyGroupID_;       // Einkaufsgruppe
    long          KonsigPartnerNr_;       // Konsignationspartnernummer

private:
    friend class pxManufacturerGroupList;

};

class pxManufacturerGroupList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxManufacturerGroupList(pxSession *session);
//  destructor:
                virtual ~pxManufacturerGroupList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int count = 100);
    size_t      SelectExist (  long konsigpartnerno, const int count = 100);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

    short          BranchNo()         {return BranchNo_             ;}
    long           CustomerNo()       {return CustomerNo_           ;}

    void            SetBranchNo(const short BranchNo){ BranchNo_ = BranchNo;}
    void            SetCustomerNo(const long CustomerNo){ CustomerNo_ = CustomerNo;}

protected:
    short      BranchNo_           ;      // Branch Number
    long       CustomerNo_         ;      // Customer Number

private:
    friend class pxManufacturerGroupListIter;
};

class pxManufacturerGroupListIter : public nDListCollectIter
{

public:
// constructors:
    pxManufacturerGroupListIter(pxManufacturerGroupList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxManufacturerGroupListIter() {;}
};
#endif
