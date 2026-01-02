/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1996 by NORDAT Network GmbH
                              All rights reserved

PXARTSTO.HPP
Article Store Location Class.

REVISION HISTORY

29 Jan 1996 V1.00 REV 00 written by Peter Hoernich.
*/

#ifndef PXARTSTO_INC
#define PXARTSTO_INC

#include "pxbase/pxrecord.hpp"

struct tARTIKELLAGERORT;

class pxArtStoreLoc : public pxDBRecord
{

public:

#define cARTST_CENTRAL_STORE  27

    virtual           ~pxArtStoreLoc();
// constructors:
                      pxArtStoreLoc(pxArtStoreLoc& src);
                      pxArtStoreLoc(pxSession *session);
                      pxArtStoreLoc(pxSession *session, tARTIKELLAGERORT& src);
                      pxArtStoreLoc(pxSession *session,
                                    long     ArtikelNr,
                                    short    FilialNr,
                                    short    LagerBereichNr,
                                    char  *LagerFachNr,
                                    DBAccessMode mode = cDBGET_READONLY);

    pxArtStoreLoc&    operator=(const pxArtStoreLoc& src);
    pxArtStoreLoc&    operator=(const tARTIKELLAGERORT& src);

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();
    virtual  long    AddQuantity(const long q);
    virtual  long    SubQuantity(const long q);
    virtual  long    SetQuantity(const long q);
    void             UnLock() {ClearLocked(); ClearDirty();}

//  Queries:
             long    ArtikelNr      () const {return ArtikelNr_              ;}
             short   FilialNr       () const {return FilialNr_               ;}
             short   LagerBereichNr () const {return LagerBereichNr_         ;}
             nString StationNr      () const {return StationNr_              ;}
             nString LagerFachNr    () const {return LagerFachNr_            ;}
             long    DatumVerfall   () const {return DatumVerfall_           ;}
             long    Bestand        () const {return Bestand_                ;}
             char    VerbundArtikel () const {return VerbundArtikel_         ;}
             short   getIBTType() const {return this->VerbundArtikel() - '0' ;}

             bool     IsAuxStockProduct()  const
                      {return ( VerbundArtikel_ == '1' || VerbundArtikel_ == '3' );}
             bool     IsAuxStockProductAnyway()  const
                      {return ( VerbundArtikel_ == '1' || VerbundArtikel_ == '2' );}
             bool     IsAuxStockProductRegional()  const
                      {return ( VerbundArtikel_ == '3');}
//  Updates:
             void     LagerBereichNr(short lgnr) {LagerBereichNr_ = lgnr; SetDirty();}
             void     LagerFachNr(nString lgfnr) {LagerFachNr_ = lgfnr; SetDirty();}
             void     DatumVerfall(long verf) {DatumVerfall_ = verf; SetDirty();}
             void     StationNr(nString stat) {StationNr_ = stat; SetDirty();}
             void     VerbundArtikel( char vb) {VerbundArtikel_ = vb; SetDirty();}

protected:
                      pxArtStoreLoc();
    friend
    pxArtStoreLoc&    Assign(pxArtStoreLoc& dest, const tARTIKELLAGERORT& src);
    friend
    tARTIKELLAGERORT& Assign(tARTIKELLAGERORT& dest, const pxArtStoreLoc& src);

    virtual  int      CompareTo(const nCollectable *that, void *p, const long lparm) const;
    void              Init();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Delete(const void *record);

    long             ArtikelNr_;
    short            FilialNr_;
    short            LagerBereichNr_;
    nString          StationNr_;      // Lager Stationsnummer
    nString          LagerFachNr_;
    long             DatumVerfall_;
    long             Bestand_;
    char             VerbundArtikel_;  // Kz Verbundartikel

private:
    friend class pxArtStoreLocList;
};

class pxArtStoreLocList : public nDListCollect, public nDBRecordSet
{
public:

    enum ASLLAccessMode
    {
        cASLL_NOZEROENTRIES     = 1,    // list no entries with bestand = 0
        cASLL_WITHZEROENTRIES   = 2,    // list also entries with bestand = 0
        cASLL_NOPRIVATPRODUCT   = 4     // list no privatproduct from zentralstore
    };

    virtual           ~pxArtStoreLocList() {Clear();}
                      pxArtStoreLocList(pxSession *session);

    void              Clear()           {nDBRecordSet::Clear();}
    pxSession*        Session()         { return (pxSession*) DataBase();}

    size_t            Select ( const long    ArtikelNr,
                               const int     count = cDEFAULT );
    size_t            Select ( const long    ArtikelNr,
                               const short   FilialNr,
                               const int     count = cDEFAULT );

    size_t            SelectLocations ( const short   FilialNr,
                                        const long    ArtikelNr,
                                        const int     count = cDEFAULT );

    pxArtStoreLoc*    Find( const short FilialNr );

protected:
    size_t            Select ( tARTIKELLAGERORT *a, const int count = cDEFAULT);
    virtual
    nCollectable*     AddToList(const void *record, const int row);

    virtual  int      StartBrowse(const void *keys, const int cursorid);
    virtual  int      EndBrowse(const int cursorid);
    virtual  int      GetNext(const void* record, const int cursorid);

private:
    friend class pxArtStoreLocListIter;
};

class pxArtStoreLocListIter : public nDListCollectIter
{
public:
    virtual           ~pxArtStoreLocListIter() {;}
                      pxArtStoreLocListIter(pxArtStoreLocList& list)
                      : nDListCollectIter(list) {;}
};

#endif
