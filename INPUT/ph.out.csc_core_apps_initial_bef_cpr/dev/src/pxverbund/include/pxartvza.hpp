#ifndef PXARTVZA_DOTH
#define PXARTVZA_DOTH

#include "pxbase/pxrecord.hpp"
#include "pxartflf.hpp"

class pxItemAttributes;
struct tFARTIKEL;

class pxArtFiliale : public pxDBRecord
{
public:
    enum IBTProduct                      // What kind of IBT Product
    {
       IBTProductNone             = 0,   // No IBT Product
       IBTProductNormal           = 1,   // IBT ProductNormal
       IBTProductPrivatSortiment  = 2,   // IBT Product Privatsortiment
       IBTProductVeterinary       = 3,   // IBT Product Veterinary
       IBTProductRegional         = 4,   // IBT ProductRegional
       IBTProductNational         = 5,   // IBT ProductNational
       IBTProductNatRegional      = 6,   // IBT ProductNatRegional
       IBTProductLokNational      = 7,   // IBT Product Lokal/National
       IBTProductLokRegional      = 8,   // IBT Product Lokal/Regional
       IBTProductOverAll          = 9    // IBT Product over all House Types
    };

    virtual           ~pxArtFiliale();
                      pxArtFiliale();
                      pxArtFiliale(pxArtFiliale& src);
                      pxArtFiliale(pxSession *session);
                      pxArtFiliale(pxSession *session, long ArtikelNr,
                                DBAccessMode mode = cDBGET_READONLY);
                      pxArtFiliale(pxSession *session, char *ArtikelNr,
                                DBAccessMode mode = cDBGET_READONLY);
                      pxArtFiliale(pxSession *session, long ArtikelNr,
                                short FilialNr,
                                DBAccessMode mode = cDBGET_READONLY);
                      pxArtFiliale(pxSession *session, char *ArtikelNr,
                                short FilialNr,
                                DBAccessMode mode = cDBGET_READONLY);

    pxArtFiliale&        operator=(const tFARTIKEL& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.
    pxArtFiliale&        operator=(const pxArtFiliale& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  long    AddQuantity(const long q);
    virtual  long    SubQuantity(const long q);
    virtual  long    SetQuantity(const long q);

    virtual  void     NachFrage(const long q)
                      {NachFrage_ += q; SetDirty();}
    void              UnLock()
                      {ClearLocked(); ClearDirty();}
    void              StopSelling();
    void              ReleaseStopSelling();
    void              CodeBlocage( const char cb)
                      {CodeBlocage_ = cb; SetDirty();}
    void              SetNotSaleable()
                      {Artikelaktiv_ = '0'; SetDirty();}
	void              SetLagerBereichNr(const short l)
                      {LagerBereichNr_ = l; SetDirty();}
	void              SetLagerFachNr(const nString& l) { LagerFachNr_ = l; SetDirty(); }
	void              SetStationNr(const nString& s) { StationNr_ = s; SetDirty(); }


//  Queries:
    bool              IsFullDiscountable() const
                      {return (Rabattfaehig_ == 0);}
    bool              IsNotDiscountable() const
                      {return (Rabattfaehig_ == 1);}
    bool              IsDiscountLimitedInsulin() const
                      {return (Rabattfaehig_ == 2);}  // Insulin
    bool              IsDiscountLimitedSerum() const
                      {return (Rabattfaehig_ == 3);}  // Serum
    bool              IsDiscountConditional() const
                      {return (Rabattfaehig_ == 4);}
    bool              IsNotSaleable() const
                      {return (Artikelaktiv_ == '0');}
    bool              IsAktivAndOnStore() const
                      {return (Artikelaktiv_ == '1');}
    bool              IsAktivAndNotOnStore() const
                      {return (Artikelaktiv_ == '2');}

    bool              IsAuxStockProduct()  const
                      {return ( VerbundArtikel_ == '1' ||
                                VerbundArtikel_ == '2' ||
                                VerbundArtikel_ == '3' ||
                                VerbundArtikel_ == '4' ||
                                VerbundArtikel_ == '5' ||
                                VerbundArtikel_ == '6' ||
                                VerbundArtikel_ == '7' ||
                                VerbundArtikel_ == '8' ||
                                VerbundArtikel_ == '9' );}

    bool              IsAuxStockProductAnyway()  const
                      {return ( VerbundArtikel_ == '1'  ||
                                VerbundArtikel_ == '2'  ||
                                VerbundArtikel_ == '3'  ||
                                VerbundArtikel_ == '4'  ||
                                VerbundArtikel_ == '5'  ||
                                VerbundArtikel_ == '6'  ||
                                VerbundArtikel_ == '7'  ||
                                VerbundArtikel_ == '8'  ||
                                VerbundArtikel_ == '9'  );}

    bool              IsPrivatProductRange()     const
                      {return ( Prisoart_ == '1'  ||
                                Prisoart_ == '2' );}
    bool              IsAllPrivatProductRange()     const
                      {return ( Prisoart_ > '0' );}
    bool              IsStopSelling()     const
                      {return (Artikelaktiv_ > '2');}
    //bool            IsNotRestDelivery()  const {return (WafoTyp_ == '0');}
    bool              IsRestDelivery()     const {return (WafoTyp_ == '1');}

    bool              IsRangeMember()               const
                      {return (KZRange_ == '1');}
    bool              IsNewProduct()                const
                      {return (CodeBlocage_ == '9');}
    bool              IsAuxStockProductRegional()  const
                      {return ( VerbundArtikel_ == '3');}
	bool			  IsArticleBlockedForReturns() const
					  {return (BlockedForReturns_ > 0);}

    const pxArtFFlags& ArtFFlags    () const {return ETArtFSchalter_         ; }
    long             ArtikelNr      () const {return ArtikelNr_              ; }
    short            FilialNr       () const {return FilialNr_               ; }
    long             Bestand        () const {return Bestand_                ; }
    long             NachFrage      () const {return NachFrage_              ; }
    long             NatraStaffelNr () const {return NatraStaffelNr_         ; }
    char             Zuzahlung      () const {return Zuzahlung_              ; }
    int              DiscountCode   () const {return Rabattfaehig_           ; }
    char             Prisoart       () const {return Prisoart_               ; }
    char             Artikelaktiv   () const {return Artikelaktiv_           ; }
    short            LagerBereichNr () const {return LagerBereichNr_         ; }
    const nString&   StationNr      () const {return StationNr_              ; }
    const nString&   LagerFachNr    () const {return LagerFachNr_            ; }
    char             VerbundArtikel () const {return VerbundArtikel_         ; }
    short            getIBTType     () const {return this->VerbundArtikel() - '0'; }

    long             ContainerGroesse  () const	{return ContainerGroesse_	 ; }
    long             VerkaufEinheit    () const	{return VerkaufEinheit_      ; }
    char             ChargenArtikel    () const	{return ChargenArtikel_      ; }
    short            TextKey           () const	{return TextKey_             ; }
    char             WafoTyp           () const	{return WafoTyp_             ; }
    char             KZRange           () const	{return KZRange_             ; }
    char             MoreConditions    () const	{return MoreConditions_      ; }
    long             BestandTagesAnfang() const {return BestandTagesAnfang_	 ; }
    char             CodeBlocage       () const	{return CodeBlocage_         ; }
	short            BlockedForReturns () const	{return BlockedForReturns_   ; }

    // if codeblocage changes on stockreceipt, so mark article
    // depend on entry within table countrycodes selected by the
    // new codeblocage
    int              CheckCodeBlocage(const char codeblocage);
    nString          GetCBPrintCode();


protected:

    friend pxArtFiliale& Assign(pxArtFiliale& dest, const tFARTIKEL& src);
    friend tFARTIKEL&  Assign(tFARTIKEL& dest, const pxArtFiliale& src);
    virtual int        CompareTo(const nCollectable*, void*, const long) const
                       {
                           return NULL;
                       }
    void               Init();
// ds! hier noch die entsprechenden readmodules
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);

    long             ArtikelNr_;			// Artikelnummer
    short            FilialNr_;				// Filialnummer
    pxArtFFlags      ETArtFSchalter_;		// Bit Map Artikel Schalter
    long             Bestand_;				// Bestand
    long             NachFrage_;			// Nachfrage
    char             Zuzahlung_;			// Kz Zuzahlung
    int              Rabattfaehig_;			// Rabattfaehigkeit Hinweis
    long             NatraStaffelNr_;		// Naturalrabatt-Staffel
    char             Prisoart_;				// Kz Privatsortiment
    char             Artikelaktiv_;			// Kz Artikelaktiv
    short            LagerBereichNr_;		// Kz Artikelaktiv
    nString          StationNr_;			// Stationsnummer
    nString          LagerFachNr_;			// Lagerfachnummer
    char             VerbundArtikel_;		// Kz Verbundartikel
    long             VerkaufEinheit_;		// VerkaufEinheit
    long             ContainerGroesse_;		// Groesse Container
    char             ChargenArtikel_;		// Chargenartikel
    short            TextKey_;				// Textkey für ArticleTextTabel
    long             BestandReserviert_;	// Bestand reserviert
    char             WafoTyp_;				// Wafotyp
    char             KZRange_;				// KZ Range
    char             MoreConditions_;		// KZ Mehr Artikelkonditionen
    long             BestandTagesAnfang_;	// Bestand Anfang des Tages
    char             CodeBlocage_;			// Code Blocage
	short			 BlockedForReturns_;	// Retouren Sperre

private:
      friend class pxBArtikel;
};

#endif
