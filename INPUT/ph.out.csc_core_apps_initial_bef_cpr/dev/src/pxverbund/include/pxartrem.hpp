/* *********************************************** */

#ifndef PXARTREM_DOTH
#define PXARTREM_DOTH

/* *********************************************** */

#include "pxbase/pxrecord.hpp"
#include "iarticlestockbooking.hpp"

struct tFARTIKEL;
/* *********************************************** */

class pxArtRemote : public pxDBRecord, public IArticleStockBooking
{

public:
    virtual           ~pxArtRemote();
                      pxArtRemote(pxArtRemote& src);
                      pxArtRemote(pxSession *session);
                      pxArtRemote(pxSession *session, long ArtikelNr,
                                short FilialNr,
                                DBAccessMode mode = cDBGET_FORUPDATE);

    pxArtRemote&        operator=(const tFARTIKEL& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.
    pxArtRemote&        operator=(const pxArtRemote& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    virtual  int     Get(DBAccessMode mode = cDBGET_FORUPDATE);
    virtual  int     Put();

    virtual  nError& Error() { return nError::Error(); }
    virtual  bool    IsGoodState() {return nError::IsGoodState(); }

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Update(const void *record);
    virtual  long    AddQuantity(const long q);
    virtual  long    SubQuantity(const long q);
    virtual  long    SetQuantity(const long q);
    virtual  long    GetQuantity() const {return Bestand_; }

//  Queries:
    bool              IsNotSaleable() const
                      {return (Artikelaktiv_ == '0');}
//     bool              IsAuxStockProduct()  const
//                       {return ( VerbundArtikel_ == '1' ||
//                                 VerbundArtikel_ == '3'  );}
//     bool              IsAuxStockProductAnyway()  const
//                       {return ( VerbundArtikel_ == '1'  ||
//                                 VerbundArtikel_ == '2' );}
    bool              IsStopSelling()     const
                      {return (Artikelaktiv_ > '2');}
//     bool              IsAuxStockProductRegional()  const
//                       {return ( VerbundArtikel_ == '3');}


    long              ArtikelNr      () const {return ArtikelNr_              ; }
    short             FilialNr       () const {return FilialNr_               ; }
    char              Artikelaktiv   () const {return Artikelaktiv_           ; }
//     char              VerbundArtikel () const {return VerbundArtikel_         ; }
//     short             getIBTType     () const { return this->VerbundArtikel() - '0'; }

protected:

    friend pxArtRemote& Assign(pxArtRemote& dest, const tFARTIKEL& src);
    friend tFARTIKEL&  Assign(tFARTIKEL& dest, const pxArtRemote& src);

    void              Init();

    nString           DBName_;          // Datenbank, auf dem sich dieser Bestand befindet
    long              ArtikelNr_;       // Artikelnummer
    short             FilialNr_;        // Filialnummer
    long              Bestand_;         // Bestand
//    long              BestandReserviert_; // BestandReserviert
    char              Artikelaktiv_;    // Artikelaktiv
//    char              VerbundArtikel_;  // Verbund Artikel
};

#endif
