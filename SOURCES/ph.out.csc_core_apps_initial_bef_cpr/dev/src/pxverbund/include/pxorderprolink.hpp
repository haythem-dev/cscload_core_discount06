/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxOrderProLink.hpp
KDAUFTRAGPROLINK  class

REVISION HISTORY

21 July 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXORDERPROLINK_INC
   #define PXORDERPROLINK_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>

struct tKDAUFTRAGPROLINK;

class pxOrderProLink : public pxDBRecord
{

public:

// constructors:
                pxOrderProLink(pxOrderProLink& src);
                pxOrderProLink(pxSession *session);
                pxOrderProLink(pxSession *session, tKDAUFTRAGPROLINK& src);
                pxOrderProLink(pxSession *session, const pxOrderProLink* src);
                pxOrderProLink(pxSession *session, long  KdauftragNr);

// destructor:
                virtual  ~pxOrderProLink();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderProLink&   operator=(const pxOrderProLink& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderProLink&   operator=(const tKDAUFTRAGPROLINK& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderProLink&
                Assign(pxOrderProLink& dest, const tKDAUFTRAGPROLINK& src);
    friend   tKDAUFTRAGPROLINK&
                Assign(tKDAUFTRAGPROLINK& dest, const pxOrderProLink& src);

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
    void              SetKdAuftragNr(const long KdAuftragNr)       { KdAuftragNr_ = KdAuftragNr; SetDirty();}
    void              SetInvoiceNumberPro(const nString& num)      { InvoiceNumberPro_ = num; SetDirty();   }
    void              SetInvoiceNumber(const nString& num)         { InvoiceNumber_ = num; SetDirty();      }
    void              SetDateProforma(const nDate& date)           { DateProforma_ = date; SetDirty();      }
    void              SetKdAuftragNrPro(const long KdAuftragNrPro) { KdAuftragNrPro_ = KdAuftragNrPro; SetDirty();}


//  Queries:
    long            KdAuftragNr() const        {return KdAuftragNr_           ;}
    const nString&  InvoiceNumberPro() const   {return InvoiceNumberPro_      ;}
    const nString&  InvoiceNumber() const      {return InvoiceNumber_         ;}
    const nDate&    DateProforma() const       {return DateProforma_          ;}
    long            KdAuftragNrPro() const     {return KdAuftragNrPro_        ;}


// Set Methodes


protected:
    void        Init();

    long       KdAuftragNr_        ;      // Kundenauftragsnummer
    nString     InvoiceNumberPro_   ;      // Proforma Invoice number
    nString     InvoiceNumber_      ;      // Invoice number
    nDate       DateProforma_       ;      // Date Proforma
    long       KdAuftragNrPro_     ;      // Kundenauftragsnummer


private:
    friend class pxOrderProLinkList;
};

class pxOrderProLinkList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxOrderProLinkList(pxSession *session);
//  destructor:
                virtual ~pxOrderProLinkList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long  KdAuftragNr,
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

    friend class pxOrderProLinkListIter;
};

class pxOrderProLinkListIter : public nDListCollectIter
{

public:
// constructors:
    pxOrderProLinkListIter(pxOrderProLinkList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOrderProLinkListIter() {;}
};
#endif
