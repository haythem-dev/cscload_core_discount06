#ifndef PXARTMAS_DOTH
   #define PXARTMAS_DOTH

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include "pxartcls.hpp"
#include "pxartflm.hpp"

struct tMARTIKEL;

class pxArtMaster : public pxDBRecord
{

public:
    virtual           ~pxArtMaster();
                      pxArtMaster(pxSession *session);
                      pxArtMaster(pxSession *session, long ArtikelNr, DBAccessMode mode = cDBGET_READONLY);

    pxArtMaster&        operator=(const tMARTIKEL& src);
    pxArtMaster&        operator=(const pxArtMaster& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
             int     Put();

    bool              IsKzPsychoStoffe()  const {return  KzPsychoStoffe_ == 'J' ||
                                                         KzPsychoStoffe_ == 'P' ||
                                                         KzPsychoStoffe_ == 'B' ||
                                                         KzPsychoStoffe_ == 'C' ||
                                                         KzPsychoStoffe_ == 'D' ||
                                                         KzPsychoStoffe_ == 'E' ||
                                                         KzPsychoStoffe_ == 'F' ||
                                                         KzPsychoStoffe_ == 'T';}
    bool              IsReserveHospital()			const	{return  KzReserveHospital_ == '1';}
    bool              IsRoundUpToSTDQty()			const	{return  KzRundungsSTDMge_ == '1';}
    bool              IsNotViaDCT()					const	{return  Nicht_Ueber_Dafue_ == '1';}
    bool              IsNotViaXML()					const	{return  Nicht_Ueber_XML_ == '1';}
    bool              IsZuschlagsArtikel()			const	{return KzZuschlagsArtikel_ == '1';}
    bool              IsSteller()					const	{return Steller_ == 'S';}
    bool              IsPositivListe()				const	{return PositivListe_ == '1';}
    bool              IsSortiment1()				const	{return Sortiment1_ == '1';}
    bool              IsSortiment2()				const	{return Sortiment2_ == '1';}
    bool              IsSortiment3()				const	{return Sortiment3_ == '1';}
    bool              IsSortiment4()				const	{return Sortiment4_ == '1';}
    bool              IsSortiment5()				const	{return Sortiment5_ == '1';}
    bool              IsBusinessWholeSale()			const	{return BusinessTypeNo_ == 0;}
    bool              IsBusinessPreWholeSale()		const	{return BusinessTypeNo_ == 1;}
    bool              IsBusinessPlatform()			const	{return BusinessTypeNo_ == 2;}
    bool              IsBusinessSra()				const	{return BusinessTypeNo_ == 3;}
    bool              IsBusinessCap()				const	{return BusinessTypeNo_ == 4;}
    bool              IsListe5()					const	{return Liste_5_ == 1;}
    bool              IsMedProdABGVerord()			const	{return (MedProd_ABG_Verord_ != '0' && MedProd_ABG_Verord_ != ' ');}
    bool              IsProduserQuota()				const	{return ProduserQuota_ == 1;}
    bool              IsMedicalProduct()			const   {return MedicalProduct_ == 1;}
    bool              IsImportArticle()             const   {return ImportArticle_ == 1;}
    bool              IsKontingentPPE()             const   {return KontingentPPE_ == '1';}
    bool              HasBatchRecallForReturns()	const   {return BatchRecallDateReturns_ > 0;}
    bool              HasManufacturerRecall()		const   {return HasBatchRecallForReturns();}
    bool              isDispositionExclusion()      const   {return (AbdaCode() == "GUEG1" || AbdaCode() == "GUEG2");}
    

//  Queries:

    const pxArtClass& ArtClass      () const   {return ETArtKlasse_          ; }
    pxArtMFlags&     ArtMFlags      ()         {return ETArtMSchalter_       ; }
    long             ArtikelNr      () const   {return ArtikelNr_            ; }
    const nString&   MatchCode      () const   {return MatchCode_            ; }
    long             PackGroesse    () const   {return PackGroesse_          ; }
    const nString&   Darreichform   () const   {return Darreichform_         ; }
    const nString&   NormPackung    () const   {return NormPackung_          ; }
    const nString&   Einheit        () const   {return Einheit_              ; }
    const nString&   Bezeichnung    () const   {return Bezeichnung_          ; }
    long             Laenge         () const   {return Laenge_               ; }
    long             Hoehe          () const   {return Hoehe_                ; }
    long             Breite         () const   {return Breite_               ; }
    long             Gewicht        () const   {return Gewicht_              ; }
    long             HerstellerNr   () const   {return HerstellerNr_         ; }
    long             LaufzeitMonate () const   {return LaufzeitMonate_       ; }
    const nString&   WarenGruppeEigen()	const  {return WarenGruppeEigen_     ; }
    const nString&   Hersteller_Code()	const  {return Hersteller_Code_      ; }
    char             KzPsychoStoffe ()   const {return KzPsychoStoffe_       ; }
    short            TaxLevel       ()   const {return TaxLevel_             ; }
    short            TextKey_Hospital()  const {return TextKey_Hospital_     ; }
    char             KzReserveHospital() const {return KzReserveHospital_    ; }
    short            STDMenge()          const {return STDMenge_             ; }
    char             KzRundungsSTDMge() const  {return KzRundungsSTDMge_     ; }
    char             Nicht_Ueber_Dafue() const {return Nicht_Ueber_Dafue_    ; }
    char             Nicht_Ueber_XML()   const {return Nicht_Ueber_XML_      ; }
    char             KzZuschlagsArtikel() const {return KzZuschlagsArtikel_  ; }
    const nString&   Wirkstoff_NR()      const {return Wirkstoff_NR_         ; }
    const nString&   HealthFundCode()    const {return HealthFundCode_       ; }
    char             Steller()           const {return Steller_              ; }
    char             PositivListe()      const {return PositivListe_         ; }
    const nString&   AbdaCode()          const {return AbdaCode_             ; }
    long             KonsigPartnerNr()   const {return KonsigPartnerNr_      ; }
    const nString&   ArtikelLangname()   const {return ArtikelLangname_      ; }
    short            PriceGroup()        const {return PriceGroup_           ; }
    char             Sortiment1()        const {return Sortiment1_           ; }
    char             Sortiment2()        const {return Sortiment2_           ; }
    char             Sortiment3()        const {return Sortiment3_           ; }
    char             Sortiment4()        const {return Sortiment4_           ; }
    char             Sortiment5()        const {return Sortiment5_           ; }
    const nDate&     Datum_Anlage()      const {return Datum_Anlage_		 ; }
    short            BusinessTypeNo()    const {return BusinessTypeNo_       ; }
    short            Liste_5()           const {return Liste_5_              ; }
    char             Upd_Flag()          const {return Upd_Flag_             ; }
    const nString&   Artikel_NR_Herst()  const {return Artikel_NR_Herst_     ; }
    char             MedProd_ABG_Verord() const {return MedProd_ABG_Verord_  ; }
    short            ProduserQuota()     const {return ProduserQuota_        ; }
    short            MedicalProduct()    const {return MedicalProduct_		 ; }
    const nDate&     DateOutOfTrade()    const {return DateOutOfTrade_		 ; }
	char			 ArticleBlocked()    const {return ArticleBlocked_       ; }
	char			 IKSCode()           const {return IKSCode_              ; }
	long			 BatchRecallDateReturns() const {return BatchRecallDateReturns_; }
	short            ImportArticle()     const {return ImportArticle_        ; }
    double           BtmFaktor()         const {return BtmFaktor_            ; }
    char             TFG()               const {return TFG_                  ; }
	char             KontingentPPE()     const {return KontingentPPE_        ; }
	const nDate&     Datum_Lieferbar_Ab() const { return Datum_Lieferbar_Ab_ ; }
	char             MedizinProdukt()    const { return MedizinProdukt_      ; }
	short            Frozen()            const { return Frozen_              ; }
	const nDate&     Datum_Aender()      const { return Datum_Aender_		 ; }
	const nString&   ATC_Code()          const { return ATC_Code_; }
	const nString&   MinistryProductCode() const { return MinistryProductCode_; }
	const nString&   HealthFundCodeHospital() const { return HealthFundCodeHospital_; }
    bool             CMIFlag()           const { return CMIFlag_ == 1; }
    bool             IsTaxPflichtigOTC() const { return TaxPflichtig_ == '1'; }
    bool             IsTaxPflichtigRX()  const { return TaxPflichtig_ == '2'; }
    bool             IsTaxPflichtig()    const { return IsTaxPflichtigOTC() || IsTaxPflichtigRX(); }


protected:
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

    friend pxArtMaster& Assign(pxArtMaster& dest, const tMARTIKEL& src);
    friend tMARTIKEL&  Assign(tMARTIKEL& dest, const pxArtMaster& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    void              Init();

// ds! hier noch die entsprechenden readmodules  s.o.
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);


    long            ArtikelNr_;					// Artikelnummer
    nString         MatchCode_;					// MatchCode
    long            PackGroesse_;				// Groesse Packung
    nString			Darreichform_;				// Darreichform
    nString			NormPackung_;				// Schluessel Normpackung (N1-N3, K1-K3)
    nString			Einheit_;					// Einheit
    nString			Bezeichnung_;				// Bezeichnung
    pxArtClass		ETArtKlasse_;				// Bit Map Artikel Klassifizierung
    pxArtMFlags		ETArtMSchalter_;			// Bit Map Artikel Schalter
    long            HerstellerNr_;				// Herstellernummer
    nString         WarenGruppe_;				// Warengruppe
    nString         TherapieGruppe_;			// Therapiegruppe
    long            Laenge_;					// Laenge
    long            Hoehe_;						// Hoehe
    long            Breite_;					// Breite
    long            Gewicht_;					// Gewicht
    long            LaufzeitMonate_;			// Artikellaufzeit in Monate
    nString         WarenGruppeEigen_;			// Warengruppe Eigen
    nString         Hersteller_Code_;			// Herstellercode
    char            KzPsychoStoffe_;			// Kz.Psychotropische Stoffe
    short           TaxLevel_;					// MWSt Level
    short           TextKey_Hospital_;			// Textschlüssel Hospital Artikel
    char			KzReserveHospital_;			// Kz Hospital Artikel
    short			STDMenge_;					// Standard Menge
    char			KzRundungsSTDMge_;			// Kennzeichen Rundung standard Menge
    char			Nicht_Ueber_Dafue_;			// Kennzeichen Nicht ueber Dafue
    char			Nicht_Ueber_XML_;			// Kennzeichen Nicht ueber XML
    char			KzZuschlagsArtikel_;		// Kennzeichen Artikel mit Bestellzuschlag
    nString         Wirkstoff_NR_;				// Wirkstoffnummer
    nString         HealthFundCode_;			// Healthfundcode
    char            Steller_;					// Steller Artikel
    char			PositivListe_;				// PositivListenartikel(RS)
    nString			AbdaCode_;					// Abdacode
    long			KonsigPartnerNr_;			// KonsigPartnerNr
    nString			ArtikelLangname_;			// Artikellangname
    short			PriceGroup_;				// Preisgruppe
    char			Sortiment1_;				// Sortiment1
    char			Sortiment2_;				// Sortiment2
    char			Sortiment3_;				// Sortiment3
    char			Sortiment4_;				// Sortiment4
    char			Sortiment5_;				// Sortiment5
    nDate           Datum_Anlage_;				// DatumAnlage
    short			BusinessTypeNo_;			// Business TypeNo Ivrylab
    short			Liste_5_;					// Kennzeichen Liste5
    char			Upd_Flag_;					// Update Flag
    nString         Artikel_NR_Herst_;			// Artikel_nr Hersteller
    char			MedProd_ABG_Verord_;		// MedProd_ABG_Verord
    short			ProduserQuota_;				// Produser Quota
    short			MedicalProduct_;			// medical product
    nDate			DateOutOfTrade_;			// DatumAusserHandel
	char			ArticleBlocked_;			// Artikel Gesperrt
	char			IKSCode_;					// IKS Code
	long			BatchRecallDateReturns_;	// Datum Retourensperre für Chargenrückruf;
    short           ImportArticle_;             // Importarticle
    double          BtmFaktor_;                 // BTM Faktor
    char            TFG_;                       // TFG
    char            KontingentPPE_;             // Kontingent PPE
	nDate			Datum_Lieferbar_Ab_;		// Datum Lieferbar ab
	char			MedizinProdukt_;			// MedizinProdukt
	short           Frozen_;                    // Frozen
	nDate           Datum_Aender_;              // Anderungsdatum
	nString			ATC_Code_;			        // ATC_Code
	nString			MinistryProductCode_;		// MinistryProductCode (BG)
	nString			HealthFundCodeHospital_;	// HealthFundCodeHospital (BG)
    short           CMIFlag_;
    char            TaxPflichtig_;
};

#endif
