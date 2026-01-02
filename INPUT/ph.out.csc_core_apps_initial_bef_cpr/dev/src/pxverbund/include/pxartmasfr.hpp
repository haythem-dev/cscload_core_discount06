/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXARTMASFR.HPP
Artikel MasterFr Class (artikelzentralfr).

REVISION HISTORY

21 October 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTMASFR_DOTH
   #define PXARTMASFR_DOTH

#include "pxbase/pxrecord.hpp"

struct tMARTIKELFR;

class pxArtMasterFr : public pxDBRecord
{

public:
    virtual           ~pxArtMasterFr();

    pxArtMasterFr&        operator=(const tMARTIKELFR& src);
    pxArtMasterFr&        operator=(const pxArtMasterFr& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
             int     Put();

//  Queries:
    long             ArtikelNr      () const {return ArtikelNr_              ; }
    const nString&   MatchCode      () const {return MatchCode_              ; }
    const nString&   Bezeichnung    () const {return Bezeichnung_            ; }
    const nString&   Einheit        () const {return Einheit_                ; }
    const nString&   Darreichform   () const {return Darreichform_           ; }

protected:
                      pxArtMasterFr(pxSession *session);
                      pxArtMasterFr(pxSession *session, long ArtikelNr,
                                DBAccessMode mode = cDBGET_READONLY);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

    friend pxArtMasterFr& Assign(pxArtMasterFr& dest, const tMARTIKELFR& src);
    friend tMARTIKELFR&  Assign(tMARTIKELFR& dest, const pxArtMasterFr& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    void              Init();

// ds! hier noch die entsprechenden readmodules  s.o.
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);


    long              ArtikelNr_;         // Artikelnummer
    nString           MatchCode_;         // MatchCode
    nString           Bezeichnung_;       // Bezeichnung
    nString           Einheit_;           // Einheit
    nString           Darreichform_;      // Darreichform

private:
      friend class pxBArtikel;
};

#endif
