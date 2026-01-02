#ifndef PXARTEAN_INC
#define PXARTEAN_INC

#include "pxbase/pxrecord.hpp"

struct tARTIKELNUMMERN;

class pxArtEan : public pxDBRecord
{

public:
// constructors:
                pxArtEan(pxArtEan& src);
                pxArtEan(pxSession *session);
                pxArtEan(pxSession *session, tARTIKELNUMMERN& src);
                pxArtEan(pxSession *session, const nString& EanNumber,
                         DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxArtEan();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArtEan&   operator=(const pxArtEan& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArtEan&   operator=(const tARTIKELNUMMERN& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArtEan&
                Assign(pxArtEan& dest, const tARTIKELNUMMERN& src);
    friend   tARTIKELNUMMERN&
                Assign(tARTIKELNUMMERN& dest, const pxArtEan& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

//  Queries:
    long             Pzn()                {return Pzn_                ;}
    nString&          Ean()                {return Ean_                ;}
    long             ArtikelNr()          {return ArtikelNr_          ;}

// Update members

protected:
    void        Init();

    long       Pzn_               ;      // Pharmazentralnummer
    nString     Ean_               ;      // Interne KundenAuftragsnummer
    long       ArtikelNr_         ;      // Artikelnummer

private:
    friend class pxArtEanList;
};

class pxArtEanList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxArtEanList(pxSession *session);
//  destructor:
                virtual ~pxArtEanList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const nString& ean, const int count = 50);
    size_t      Select ( const long artikelnr, const int count = 50);

    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxArtEanListIter;
};

class pxArtEanListIter : public nDListCollectIter
{

public:
// constructors:
    pxArtEanListIter(pxArtEanList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArtEanListIter() {;}
};
#endif
