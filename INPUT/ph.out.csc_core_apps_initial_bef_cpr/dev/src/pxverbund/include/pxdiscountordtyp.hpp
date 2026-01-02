/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PCDISCOUNTORDTYP.HPP
pxDiscountOrdTyp  class

REVISION HISTORY

09 Feb. 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXDISCOUNTORDTYP_INC
   #define PXDISCOUNTORDTYP_INC

#include "pxbase/pxrecord.hpp"

struct tDISCOUNTORDERTYP;

class pxDiscountOrdTyp : public pxDBRecord
{

public:

// constructors:
                pxDiscountOrdTyp(pxDiscountOrdTyp& src);
                pxDiscountOrdTyp(pxSession *session);
                pxDiscountOrdTyp(pxSession *session, tDISCOUNTORDERTYP& src);
                pxDiscountOrdTyp(pxSession *session,
                                 short  DiscountType,
                                 nString& KdauftragArt);
// destructor:
                virtual  ~pxDiscountOrdTyp();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxDiscountOrdTyp&   operator=(const pxDiscountOrdTyp& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxDiscountOrdTyp&   operator=(const tDISCOUNTORDERTYP& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxDiscountOrdTyp&
                Assign(pxDiscountOrdTyp& dest, const tDISCOUNTORDERTYP& src);
    friend   tDISCOUNTORDERTYP&
                Assign(tDISCOUNTORDERTYP& dest, const pxDiscountOrdTyp& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Read(const void *record);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

//  Queries:
    short          DiscountType()      {return DiscountType_     ;}
    nString&        KdAuftragArt()      {return KdAuftragArt_     ;}


protected:
    void        Init();

    short      DiscountType_      ;      // DiscountType
    nString     KdAuftragArt_      ;      // Kunden Auftragart

private:
    friend class pxDiscountOrdTypList;
};

class pxDiscountOrdTypList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxDiscountOrdTypList(pxSession *session);
//  destructor:
                virtual ~pxDiscountOrdTypList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );

    short      Find(const nString& KdAuftragArt);
    short      Find(const nString& KdAuftragArt, const short DiscountType);

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxDiscountOrdTypListIter;
};

class pxDiscountOrdTypListIter : public nDListCollectIter
{

public:
// constructors:
    pxDiscountOrdTypListIter(pxDiscountOrdTypList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxDiscountOrdTypListIter() {;}
};
#endif
