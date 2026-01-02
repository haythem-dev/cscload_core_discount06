/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXARTALT.HPP
ArtAltern Class.

REVISION HISTORY

22 Nov 1995 V1.00 REV 00 written by Peter Hoernich.
*/

#ifndef PXARTALT_INC
#define PXARTALT_INC

#include "pxbase/pxrecord.hpp"

struct tARTIKELALTERN;

class pxArtAltern : public pxDBRecord
{

public:
// constructors:
                      pxArtAltern();
                      pxArtAltern(pxArtAltern& src);
                      pxArtAltern(pxSession *session);
                      pxArtAltern(pxSession *session, tARTIKELALTERN& src);
                      pxArtAltern(pxSession *session,
                                  long ArtikelNr,
                                  long ArtikelAlternNr,
                                  short FilailNr,
                                  DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxArtAltern();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArtAltern&   operator=(const pxArtAltern& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArtAltern&   operator=(const tARTIKELALTERN& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArtAltern&
                      Assign(pxArtAltern& dest,
                             const tARTIKELALTERN& src);
    friend   tARTIKELALTERN&
                      Assign(tARTIKELALTERN& dest,
                             const pxArtAltern& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);

//  Queries:
             long     ArtikelNr         () {return ArtikelNr_;            }
             long     ArtikelAlternNr   () {return ArtikelAlternNr_;      }
             nString& Bemerkungen       () {return Bemerkungen_;          }
             short    FilialNr    () const {return FilialNr_;             }

protected:
             void     Init();

    long        ArtikelNr_;             // Nr. Artikel
    long        ArtikelAlternNr_;       // Nr. Alternativ-Artikel
    nString     Bemerkungen_;           // ergaenzende Bemerkungen
    short       FilialNr_;              // Filialnummer

private:
    friend class pxArtAlternList;
};

class pxArtAlternList : public nDBRecordSet, public nDListCollect
{

public:
//  constructors:
                      pxArtAlternList(pxSession *session);

//  destructor:
    virtual           ~pxArtAlternList() {Clear();}

//  member functions:
             pxSession*
                      Session()      { return (pxSession*) DataBase();}



             size_t   Select ( const int  count = 50 );

             size_t   Select ( const long ArtikelNr,const short Filialnr = 0,
                               const int  count= 50 );

             size_t   SelectForward ( const long Artikel_Nr,const short Filialnr = 0,
                               const int  count= 50 );

             size_t   SelectReverse ( const long Artikel_Nr_altern ,const short Filialnr = 0,
                               const int  count= 50 );

             size_t   Select ( const tARTIKELALTERN *recordp,
                               const int            count );

             void     Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int      GetNext(const void* record, const int cursorid);
    virtual  int      StartBrowse(const void *keys, const int cursorid);
    virtual  int      EndBrowse(const int cursorid);

protected:

private:
    friend class pxArtAlternListIter;
};

class pxArtAlternListIter : public nDListCollectIter
{

public:
// constructors:
                      pxArtAlternListIter(pxArtAlternList& list)
                         : nDListCollectIter(list) {;}
// destructor:
    virtual           ~pxArtAlternListIter() {;}
};

#endif
