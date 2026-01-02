/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1999 by NORDAT Network GmbH
                              All rights reserved

PXIARTIK.HPP
Artikel Interface Class.
*/

#ifndef PXIARTIK_DOTH
#define PXIARTIK_DOTH

#include "database.hpp"

class nDate;
class pxSession;
class pxArtClass;
class pxArtFlags;
class pxArtPackUnitList;
class pxItemAttributes;
class pxArtSpecialCond;
class IBTBranchArticleConfig;


class pxArtBase
{

public:

    virtual           ~pxArtBase() {}

// interface nDBRecordSet
    virtual  int         Get(DBAccessMode mode = cDBGET_READONLY) = 0;
    virtual  int         Put() = 0;
    virtual  void        UnLock() = 0;
    virtual  bool        IsActive() = 0;
    virtual  bool        IsDirty  () = 0;
    virtual  bool        IsLocked () = 0;
    virtual  bool        IsLockHeld() = 0;
    virtual  bool        IsOpen() = 0;

    // interface nError
    virtual  bool        IsGoodState() = 0;
    virtual  nError&     Error() = 0;
    virtual  int         ExternalError(const nMessage& msg, const int errornum = 0) = 0;
    virtual  int         ExternalCondition(std::ifstream *stream, const int errornum, ...) = 0;

    virtual  void        NachFrage(const long q) = 0;
    virtual  void        StopSelling() = 0;
    virtual  void        ReleaseStopSelling() = 0;
    virtual  void        CodeBlocage( const char cb) = 0;
    virtual  void        SetNotSaleable() = 0;
	virtual  void        SetLagerBereichNr(const short l) = 0;
	virtual  void        SetLagerFachNr(const nString& l) = 0;
	virtual  void        SetStationNr(const nString& s) = 0;


//  Queries:
    virtual  bool        IsFullDiscountable()       const = 0;
    virtual  bool        IsNotDiscountable()        const = 0;
    virtual  bool        IsDiscountLimitedInsulin() const = 0;  // Insulin
    virtual  bool        IsDiscountLimitedSerum()   const = 0;    // Serum
    virtual  bool        IsDiscountConditional()    const = 0;
    virtual  bool        IsNotSaleable()            const = 0;
    virtual  bool        IsAktivAndOnStore()        const = 0;
    virtual  bool        IsAktivAndNotOnStore()     const = 0;
    virtual  bool        IsAuxStockProduct()        const = 0;
    virtual  bool        IsAuxStockProductAnyway()  const = 0;
    virtual  bool        IsPrivatProductRange()     const = 0;
    virtual  bool        IsAllPrivatProductRange()  const = 0;
    virtual  bool        IsStopSelling()            const = 0;
    virtual  bool        IsKzPsychoStoffe()         const = 0;
    virtual  bool        IsRestDelivery()           const = 0;
    virtual  bool        IsRangeMember()            const = 0;
    virtual  bool        IsReserveHospital()        const = 0;
    virtual  bool        IsRoundUpToSTDQty()        const = 0;
    virtual  bool        IsNewProduct()             const = 0;
    virtual  bool        IsNotViaDCT()              const = 0;
    virtual  bool        IsNotViaXML()              const = 0;
    virtual  bool        IsZuschlagsArtikel()       const = 0;
    virtual  bool        IsAuxStockProductRegional() const = 0;
    virtual  bool        IsSteller()                const = 0;
    virtual  bool        IsPositivListe()           const = 0;
    virtual  bool        IsSortiment1()             const = 0;
    virtual  bool        IsSortiment2()             const = 0;
    virtual  bool        IsSortiment3()             const = 0;
    virtual  bool        IsSortiment4()             const = 0;
    virtual  bool        IsSortiment5()             const = 0;
    virtual  bool        IsBusinessWholeSale()      const = 0;
    virtual  bool        IsBusinessPreWholeSale()   const = 0;
    virtual  bool        IsBusinessPlatform()       const = 0;
    virtual  bool        IsBusinessSra()            const = 0;
    virtual  bool        IsBusinessCap()            const = 0;
    virtual  bool        IsListe5()                 const = 0;
    virtual  bool        IsMedProdABGVerord()       const = 0;

    virtual  bool        IsProduserQuota()          const = 0;
    virtual  bool        IsMedicalProduct()         const = 0;

    virtual bool         IsImportArticle() const = 0;
    virtual bool         IsKontingentPPE() const = 0;


    virtual  pxSession*  Session        () = 0;
	virtual  IBTBranchArticleConfig* getIBTBranchArticleConfigPtr() = 0;

    virtual  std::ifstream* CMsgStream     () = 0;
    virtual  const pxArtClass& ArtClass    () const = 0;
    virtual  const pxArtFlags& ArtFlags    () const = 0;
    virtual  long           ArtikelNr      () const = 0;
    virtual  short          FilialNr       () const = 0;
    virtual  const nString& MatchCode      () const = 0;
    virtual  long           PackGroesse    () const = 0;
    virtual  const nString& Darreichform   () const = 0;
    virtual  const nString& NormPackung    () const = 0;
    virtual  const nString& Einheit        () const = 0;
    virtual  const nString& Bezeichnung    () const = 0;
    virtual  long       VerkaufEinheit () const = 0;
    virtual  long       ContainerGroesse() const = 0;
    virtual  long       Laenge         () const = 0;
    virtual  long       Hoehe          () const = 0;
    virtual  long       Breite         () const = 0;
    virtual  long       Gewicht        () const = 0;
    virtual  long       NachFrage      () const = 0;
    virtual  long       NatraStaffelNr () const = 0;
    virtual  char       Zuzahlung      () const = 0;
    virtual  int        DiscountCode   () const = 0;
    virtual  char       Prisoart       () const = 0;
    virtual  char       Artikelaktiv   () const = 0;
    virtual  short      LagerBereichNr () const = 0;
    virtual  const nString& StationNr  () const = 0;
    virtual  const nString& LagerFachNr() const = 0;
    virtual  char       VerbundArtikel () const = 0;
    virtual  short      getIBTType     () const = 0;
    virtual  long       HerstellerNr   () const = 0;
    virtual  long       LaufzeitMonate () const = 0;
    virtual  const nString& WarenGruppeEigen() const = 0;
    virtual  const nString& Hersteller_Code() const = 0;
    virtual  char       KzPsychoStoffe () const = 0;
    virtual  short      TaxLevel       () const = 0;
    virtual  short      TextKey_Hospital()const = 0;
    virtual  char       KzReserveHospital()const = 0;
    virtual  short      TextKey        () const = 0;
    virtual  char       ChargenArtikel () const = 0;
    virtual  char       WafoTyp        () const = 0;
    virtual  char       KZRange        () const = 0;
    virtual  char       MoreConditions () const = 0;
    virtual  long       BestandTagesAnfang () const = 0;
    virtual  char       CodeBlocage    () const = 0;
    virtual  short      STDMenge       () const  = 0;
    virtual  char       KzRundungsSTDMge() const  = 0;
    virtual  const nString& HealthFundCode () const = 0;
    virtual  const nString& Wirkstoff_NR() const    = 0;
    virtual  const nString& AbdaCode () const  = 0;
    virtual  long           KonsigPartnerNr() const = 0;
    virtual  const nString& ArtikelLangname() const = 0;
    virtual  short      PriceGroup     () const = 0;
    virtual  short      BusinessTypeNo () const = 0;
    virtual  short      Liste_5         () const = 0;

    virtual  pxArtPackUnitList* PackageUnitList() = 0;
    virtual  void      SetSprache(const nString& Sprache) = 0;
    virtual  double    InvoiceRebatePct()	const = 0;
    virtual  double    RebateInKindPct()	const = 0;
    virtual  double    AnnualInvRebPct()	const = 0;
    virtual  double    AnnualRebIKPct()		const = 0;
    virtual  double    CustRebRedPct()		const = 0;
    virtual  double    HiReimBursement()	const = 0;
    virtual  double    SupplHiReimb()		const = 0;
    virtual  double    SupplFsReimb()		const = 0;
    virtual  double    SupplDiscountPct()	const = 0;
    virtual  const nDate& DatumAnlage()		const = 0;
    virtual  const nDate& DateOutOfTrade()	const = 0;
    virtual  char      ArticleBlocked()		const = 0;
    virtual  char      IKSCode()			const = 0;
    virtual  long      BatchRecallDateReturns() const = 0;
    virtual  short     ImportArticle()      const = 0;
    virtual  double    BtmFaktor()          const = 0;
    virtual  char      TFG()                const = 0;
    virtual  char      KontingentPPE()      const = 0;
	virtual  const nDate& Datum_Lieferbar_Ab() const = 0;
	virtual  char      MedizinProdukt()     const = 0;
	virtual  short     Frozen()             const = 0;
	virtual const nDate& Datum_Aender()     const = 0; 
	virtual const nString& ATC_Code()       const = 0;
	virtual const nString& MinistryProductCode() const = 0;
	virtual  const nString& HealthFundCodeHospital() const = 0;
	virtual  bool      IsArticleBlockedForReturns() const = 0;
	virtual  bool      HasBatchRecallForReturns() const = 0;
	virtual  bool      HasManufacturerRecall() const = 0;
    virtual  bool      isDispositionExclusion() const = 0;
    virtual  bool      IsTaxPflichtigOTC() const = 0;
    virtual  bool      IsTaxPflichtigRX()  const = 0;
    virtual  bool      IsTaxPflichtig()    const = 0;


    // if codeblocage changes on stockreceipt, so mark article
    // depend on entry within table countrycodes selected by the
    // new codeblocage
    virtual  int         CheckCodeBlocage(const char codeblocage) = 0;
    virtual  nString      GetCBPrintCode() = 0;
    // Create an instance of article
    static   pxArtBase*  CreateArticle(pxSession * session,
                                      long ArtikelNr, short FilialNr,
                                      DBAccessMode mode = cDBGET_READONLY);
    // create a copy of article
    static   pxArtBase*  CopyArticle(pxArtBase * IArtikel);
};

#endif
