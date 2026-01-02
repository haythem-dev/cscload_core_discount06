/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-2002 by NORDAT Network GmbH
                              All rights reserved

PXSTKREV.HPP
Classes dealing stock revision.

REVISION HISTORY

13 Sept 2001 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXSTKREV_INC
   #define PXSTKREV_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include <clock.hpp>

struct tLAGERREVISION;

class pxStockRev : public pxDBRecord
{
public:

// constructors:
                pxStockRev(pxSession *session);
              // Default mit Session Informationen
                pxStockRev(const pxStockRev& src);
              // Copy constructor
                pxStockRev(pxSession *session,tLAGERREVISION& src);
              // record constructor
                pxStockRev(pxSession *session,
                       const short FilialNr,
                       const long  ArtikelNr,
                       DBAccessMode mode = cDBGET_READONLY);
              // Read contructor
                pxStockRev(pxSession *session,short FilialNr,
                       const long  ArtikelNr,
                       const long  BestandKSC,
                       const long  BestandVSE);
//@DE
// destructor:
                virtual  ~pxStockRev();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxStockRev&   operator=(const pxStockRev& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxStockRev&   operator=(const tLAGERREVISION& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxStockRev&  Assign(pxStockRev& dest, const tLAGERREVISION& src);
    friend   tLAGERREVISION&   Assign(tLAGERREVISION& dest, const pxStockRev& src);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Delete(const void *record);

// Queries:
    short            FilialNr()
                      {return FilialNr_;      }
    long             ArtikelNr()
                      {return ArtikelNr_;     }
    nDate             Datum() const
                      {return Datum_;}
    const nClock&     UhrZeit()
                      const {return UhrZeit_; }
    long             BestandKSC()
                      {return BestandKSC_;    }
    long             BestandVSE()
                      {return BestandVSE_;    }

protected:
    void              Init();

    short            FilialNr_;        // Filialnummer
    long             ArtikelNr_;       // Artikelnummer
    nDate             Datum_;           // Datum
    nClock            UhrZeit_;         // Uhrzeit
    long             BestandKSC_;      // Bestand KSC
    long             BestandVSE_;      // Bestand VSE
private:
    friend class pxStockRevLis;
};

class pxStockRevList : public nDListCollect, public nDBRecordSet
{

public:
// constructors:
                pxStockRevList(pxSession *session);
// destructor:
                virtual  ~pxStockRevList() {Clear();}
// member functions:
             pxSession*  Session()       { return (pxSession*) DataBase();}
             size_t      Select (const short FilialNr,
                                 const long  ArtikelNr,
                                 const int    count = 50 );

             size_t      Select ( tLAGERREVISION* lagrev,
                                  const int    count = 50 );
             void        Clear()        {nDBRecordSet::Clear();}
             pxStockRev*  Find( const long ArtikelNR);
             // Liefert Pointer auf gesuchte Artikelnummer

    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
protected:

private:
    friend class pxStockRevListIter;
};

class pxStockRevListIter : public nDListCollectIter
{
public:
// constructors:
    pxStockRevListIter(pxStockRevList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxStockRevListIter() {;}
};

#endif

