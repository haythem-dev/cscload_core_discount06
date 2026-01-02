/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxcstprint.hpp
CSTPRINT  class

REVISION HISTORY

06 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCSTPRINT_INC
   #define PXCSTPRINT_INC

#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"

struct tCSTPRINT;

class pxCstPrint : public pxDBRecord
{

public:

// constructors:
                pxCstPrint(pxCstPrint& src);
                pxCstPrint(pxSession *session);
                pxCstPrint(pxSession *session, tCSTPRINT& src);
                pxCstPrint(pxSession *session, const pxCstPrint* src);
                pxCstPrint(pxSession *session, short BranchNo,
                                               long  CustomerNo,
                                               PriceTypeEnum PreisTyp);

// destructor:
                virtual  ~pxCstPrint();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCstPrint&   operator=(const pxCstPrint& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCstPrint&   operator=(const tCSTPRINT& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCstPrint&
                Assign(pxCstPrint& dest, const tCSTPRINT& src);
    friend   tCSTPRINT&
                Assign(tCSTPRINT& dest, const pxCstPrint& src);

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
    short          BranchNo()       {return BranchNo_             ;}
    long           CustomerNo()     {return CustomerNo_           ;}
    PriceTypeEnum  PreisTyp()       {return PreisTyp_             ;}
    short          DeductionAep()   {return DeductionAep_         ;}
    short          DeductionAvp()   {return DeductionAvp_         ;}
    short          Print()          {return Print_                ;}
    short          WithColumnNr()   {return WithColumnNr_         ;}
    short          InvoiceEmail()   {return InvoiceEmail_         ;}

// Set Methodes
    void           SetPrint(short Print)
                   {Print_ = Print;}
    void           SetDeductionAep(short DeductionAep)
                   {DeductionAep_ = DeductionAep; }
    void           SetDeductionAvp(short DeductionAvp)
                   {DeductionAvp_ = DeductionAvp; }
    void           SetWithColumnNr(short WithColumnNr)
                   {WithColumnNr_ = WithColumnNr;}
    void           SetInvoiceEmail(short InvoiceEmail)
                   {InvoiceEmail_ = InvoiceEmail;}


protected:
    void        Init();

    short      BranchNo_           ;      // Branch Number
    long       CustomerNo_         ;      // Customer Number
    PriceTypeEnum PreisTyp_        ;      // preistyp
    short      DeductionAep_       ;      // Abschlag Aep
    short      DeductionAvp_       ;      // Abschlag Avp
    short      Print_              ;      // print ????

    short      WithColumnNr_       ;      // WithColumnNr(only on RO)
    short      InvoiceEmail_       ;      // InvoiceEmail


private:
    friend class pxCstPrintList;
};

class pxCstPrintList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCstPrintList(pxSession *session);
//  destructor:
                virtual ~pxCstPrintList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  CustomerNo,
                         const int   count  = 1000
                       );
// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}
    pxCstPrint* Find(const PriceTypeEnum pricetyp);


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxCstPrintListIter;
};

class pxCstPrintListIter : public nDListCollectIter
{

public:
// constructors:
    pxCstPrintListIter(pxCstPrintList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCstPrintListIter() {;}
};
#endif
