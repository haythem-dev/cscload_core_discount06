/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXOCLPAR.HPP
Order Close Time Class.

REVISION HISTORY

21 Jan 1997 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXOCLPAR_INC
#define PXOCLPAR_INC

#include "pxbase/pxrecord.hpp"
#include "types/origintypeenum.inc"
#include <clock.hpp>

struct tKDAUFTRAGENDEZEIT;

class pxOrderCloseParam : public pxDBRecord
{

public:

// constructors:
                pxOrderCloseParam(pxOrderCloseParam& src);
                pxOrderCloseParam(pxSession *session);
                pxOrderCloseParam(pxSession *session, tKDAUFTRAGENDEZEIT& src);
                pxOrderCloseParam(pxSession *session,
                         short FilialNr,
                         DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxOrderCloseParam();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderCloseParam&   operator=(const pxOrderCloseParam& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderCloseParam&   operator=(const tKDAUFTRAGENDEZEIT& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderCloseParam&
                Assign(pxOrderCloseParam& dest, const tKDAUFTRAGENDEZEIT& src);
    friend   tKDAUFTRAGENDEZEIT&
                Assign(tKDAUFTRAGENDEZEIT& dest, const pxOrderCloseParam& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);

//  Queries:
    bool              IsCloseModeImmediate();
    bool              IsCloseModeOnce();
    bool              IsCloseModePermanent();
    bool              IsCloseModeInternal();

    short             FilialNr()           {return FilialNr_;                  }
    OriginTypeEnum    BatchSchreiben()     {return BatchSchreiben_;            }
    short             HerkunftsFilialNr()  {return HerkunftsFilialNr_;         }
    short             AbschlussModus()     {return AbschlussModus_;            }
    nClock&           AbschlussZeit()      {return AbschlussZeit_;             }

    bool              SetModeInternal();
    bool              SetModeOnce();

    static OriginTypeEnum ConvertBatchSchreiben(const nString&);
    static nString    ConvertBatchSchreiben(OriginTypeEnum);

protected:
    void        Init();

    short       FilialNr_          ;     // Filialnummer
    OriginTypeEnum BatchSchreiben_ ;     // Herkunftstyp
    short       HerkunftsFilialNr_ ;     // Herkunftsfiliale
    short       AbschlussModus_    ;     // Abschlussmodus
    nClock      AbschlussZeit_     ;     // Abschlusszeit

private:
    friend class pxOrderCloseParamList;
};

class pxOrderCloseParamList : public nDBRecordSet, public nDListCollect
{
public:
//  constructors:
                pxOrderCloseParamList(pxSession *session);
//  destructor:
                virtual ~pxOrderCloseParamList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short  FilialNr, const int     count = 300);

    pxOrderCloseParam*           FindHerkunftsFilialNr( short HerkunftsFilialNr );
    pxOrderCloseParam*           Find( OriginTypeEnum  BatchSchreiben, short HerkunftsFilialNr );
    pxOrderCloseParam*           FindBatchSchreiben( OriginTypeEnum  BatchSchreiben);
//  returns pointer to the corresponding entry within the list.

    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxOrderCloseParamListIter;
};

class pxOrderCloseParamListIter : public nDListCollectIter
{

public:
// constructors:
    pxOrderCloseParamListIter(pxOrderCloseParamList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOrderCloseParamListIter() {;}
};
#endif
