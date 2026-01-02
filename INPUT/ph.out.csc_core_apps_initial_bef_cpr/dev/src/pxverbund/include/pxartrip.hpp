/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXARTRIP.HPP
ArtReImport Class.

REVISION HISTORY

19 Oct 1999 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTRIP_INC
   #define PXARTRIP_INC

#include "pxbase/pxrecord.hpp"

struct tARTIKELREIMPORT;

class pxArtReImport : public pxDBRecord
{

public:


// constructors:
                      pxArtReImport();
                      pxArtReImport(pxArtReImport& src);
                      pxArtReImport(pxSession *session);
                      pxArtReImport(pxSession *session, tARTIKELREIMPORT& src);
                      pxArtReImport(pxSession *session, short FilialNr,
                                  long ArtikelNr,
                                  long ArtikelAlternNr,
                                  DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxArtReImport();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArtReImport&   operator=(const pxArtReImport& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArtReImport&   operator=(const tARTIKELREIMPORT& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArtReImport&
                      Assign(pxArtReImport& dest,
                             const tARTIKELREIMPORT& src);
    friend   tARTIKELREIMPORT&
                      Assign(tARTIKELREIMPORT& dest,
                             const pxArtReImport& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

    virtual  int     Read(const void *record);

//  Queries:
             short   FilialNr          () {return  FilialNr_;            }
             long    ArtikelNr         () {return ArtikelNr_;            }
             long    ArtikelAlternNr   () {return ArtikelAlternNr_;      }
             char    KZAktivPassiv     () {return KZAktivPassiv_;        }
             bool    IsPassivLinkage   () const {return KZAktivPassiv_ == '0'; }
             bool    IsActivLinkage    () const {return KZAktivPassiv_ == '1'; }
             short   ReihenFolge       () {return  ReihenFolge_;         }


protected:
             void     Init();

    short      FilialNr_;              // Filial Nummer
    long       ArtikelNr_;             // Nr. Artikel
    long       ArtikelAlternNr_;       // Nr. Alternativ-Artikel
    char       KZAktivPassiv_;         // KZ. Aktive-,passive Verknüpfung
    short      ReihenFolge_;           // Reihenfolgenummer

private:
    friend class pxArtReImportList;
};

class pxArtReImportList : public nDListCollect,public nDBRecordSet
{

public:
enum REIMPShrinkMode
{
    cREIMPDefault,                      // shrink on passiv entries
    cREIMPAktiv                         // shrink on aktiv entries
};
//  constructors:
                      pxArtReImportList(pxSession *session);

//  destructor:
    virtual           ~pxArtReImportList() {Clear();}

//  member functions:
             pxSession*
                      Session()      { return (pxSession*) DataBase();}



             size_t   Select ( const int count = 50 );

             size_t   Select ( const short FilialNr, const long ArtikelNr,
                               const int count = 50 );
             size_t   Select ( const long ArtikelNr, const int count = 50 );

             size_t   Select ( const tARTIKELREIMPORT    *recordp,
                               const int              count );

             void     Clear()        {nDBRecordSet::Clear();}
             int     Shrink(REIMPShrinkMode mode = cREIMPDefault);
pxArtReImportList*    Build(REIMPShrinkMode mode = cREIMPDefault);

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxArtReImportListIter;
};

class pxArtReImportListIter : public nDListCollectIter
{

public:
// constructors:
                      pxArtReImportListIter(pxArtReImportList& list)
                         : nDListCollectIter(list) {;}
// destructor:
    virtual           ~pxArtReImportListIter() {;}

//  public member functions

};

#endif
