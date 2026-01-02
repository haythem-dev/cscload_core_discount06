/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

 pxcstpaymentterms.hpp
 SERVICES   class

REVISION HISTORY

22 Febr 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCSTPAYMENTTERMS_INC
#define PXCSTPAYMENTTERMS_INC

#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"

struct tCSTPAYMENTTERMS;

class pxCstPaymentTerms : public pxDBRecord
{

public:

// constructors:
                pxCstPaymentTerms(pxCstPaymentTerms& src);
                pxCstPaymentTerms(pxSession *session);
                pxCstPaymentTerms(pxSession *session, tCSTPAYMENTTERMS& src);
                pxCstPaymentTerms(pxSession *session, const pxCstPaymentTerms* src);
                pxCstPaymentTerms(pxSession *session, const short BranchNo, const long CustomerNo,
                                  const PriceTypeEnum PriceType,
                                 DBAccessMode mode = cDBGET_READONLY );

// destructor:
                virtual  ~pxCstPaymentTerms();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCstPaymentTerms&   operator=(const pxCstPaymentTerms& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCstPaymentTerms&   operator=(const tCSTPAYMENTTERMS& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCstPaymentTerms&
                Assign(pxCstPaymentTerms& dest, const tCSTPAYMENTTERMS& src);
    friend   tCSTPAYMENTTERMS&
                Assign(tCSTPAYMENTTERMS& dest, const pxCstPaymentTerms& src);

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
    short          BranchNo()          { return BranchNo_        ;}
    long           CustomerNo()        { return CustomerNo_      ;}
    PriceTypeEnum  PreisTyp()          { return PreisTyp_        ;}
    short          PaymentTarget()     { return PaymentTarget_   ;}

// Set Methodes


protected:
    void        Init();

    short         BranchNo_       ;            // Filialnummer
    long          CustomerNo_     ;            // Customerno
    PriceTypeEnum PreisTyp_       ;            // Preistype
    short         PaymentTarget_  ;            // PaymentTarget

private:
    friend class pxCstPaymentTermsList;
};

class pxCstPaymentTermsList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCstPaymentTermsList(pxSession *session);
//  destructor:
                virtual ~pxCstPaymentTermsList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  CustomerNo,
                         const int   count  = 100
                       );
    pxCstPaymentTerms*  Find( const PriceTypeEnum Pricetype);

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxCstPaymentTermsListIter;
};

class pxCstPaymentTermsListIter : public nDListCollectIter
{

public:
// constructors:
    pxCstPaymentTermsListIter(pxCstPaymentTermsList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCstPaymentTermsListIter() {;}
};
#endif
