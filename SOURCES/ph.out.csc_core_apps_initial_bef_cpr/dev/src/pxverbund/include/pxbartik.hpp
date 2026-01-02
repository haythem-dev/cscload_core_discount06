/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1999 by NORDAT Network GmbH
                              All rights reserved

PXBARTIK.HPP
Artikel Interface Class.
*/

#ifndef PXBARTIK_DOTH
#define PXBARTIK_DOTH

#include "pxerrorloggable.hpp"
#include "pxartvza.hpp"
#include "pxartmas.hpp"
#include "pxartmasfr.hpp"
#include "pxartflg.hpp"
#include "pxartspecialcond.hpp"
#include "iarticlestockbooking.hpp"
#include "ibtbrancharticleconfig.h"

class pxBArtikel : public pxErrorLoggable, public pxArtBase, public IArticleStockBooking
{

public:
    // nDBRecord delegates
    virtual int         Get(DBAccessMode mode = cDBGET_READONLY);
    virtual int         Put();
    virtual void        UnLock();
    virtual bool        IsActive();
    virtual bool        IsDirty();
    virtual bool        IsLocked();
    virtual bool        IsLockHeld();
    virtual bool        IsOpen();

    // nError delegates
    virtual  bool       IsGoodState()    { return nError::IsGoodState(); }
    virtual  nError&    Error()          { return nError::Error(); }
    virtual  int        ExternalError(const nMessage& msg, const int errornum = 0) { return nError::ExternalError(msg, errornum); }
    virtual  int        ExternalCondition(std::ifstream *stream, const int errornum, ...)
    {
        va_list arglist;
        va_start (arglist, errornum);
        int ret = nError::ExternalCondition(stream, errornum, arglist);
        va_end(arglist);
        return ret;
    }

    // IArticleStockBooking interface implementation
    virtual  long       AddQuantity(const long q);
    virtual  long       SubQuantity(const long q);
    virtual  long       SetQuantity(const long q);
    virtual  long       GetQuantity() const               {return ArtikelFil_->Bestand();}

    virtual  void       NachFrage(const long q) {ArtikelFil_->NachFrage(q);}
    virtual  void       StopSelling() {ArtikelFil_->StopSelling();}
    virtual  void       ReleaseStopSelling() {ArtikelFil_->ReleaseStopSelling();}
    virtual  void       CodeBlocage(const char cb) {ArtikelFil_->CodeBlocage( cb );}
    virtual  void       SetNotSaleable() {ArtikelFil_->SetNotSaleable();}
    virtual  void       SetLagerBereichNr(const short l) { ArtikelFil_->SetLagerBereichNr(l); }
    virtual  void       SetLagerFachNr(const nString& l) { ArtikelFil_->SetLagerFachNr(l); }
    virtual  void       SetStationNr(const nString& s)   { ArtikelFil_->SetStationNr(s); }

//  Queries:
    virtual bool      IsFullDiscountable() const
                      {return (ArtikelFil_->IsFullDiscountable());}
    virtual bool      IsNotDiscountable() const
                      {return (ArtikelFil_->IsNotDiscountable());}
    virtual bool      IsDiscountLimitedInsulin() const
                      {return (ArtikelFil_->IsDiscountLimitedInsulin());}  // Insulin
    virtual bool      IsDiscountLimitedSerum() const
                      {return (ArtikelFil_->IsDiscountLimitedSerum());}  // Serum
    virtual bool      IsDiscountConditional() const
                      {return (ArtikelFil_->IsDiscountConditional());}
    virtual bool      IsNotSaleable() const
                      {return (ArtikelFil_->IsNotSaleable());}
    virtual bool      IsAktivAndOnStore() const
                      {return (ArtikelFil_->IsAktivAndOnStore());}
    virtual bool      IsAktivAndNotOnStore() const
                      {return (ArtikelFil_->IsAktivAndNotOnStore());}
    virtual bool      IsAuxStockProduct() const
                      {return ( ArtikelFil_->IsAuxStockProduct());}
    virtual bool      IsAuxStockProductAnyway() const
                      {return ( ArtikelFil_->IsAuxStockProductAnyway());}
    virtual bool      IsPrivatProductRange() const
                      {return ( ArtikelFil_->IsPrivatProductRange());}
    virtual bool      IsAllPrivatProductRange() const
                      {return ( ArtikelFil_->IsAllPrivatProductRange());}
    virtual bool      IsStopSelling() const
                      {return ( ArtikelFil_->IsStopSelling());}
    virtual bool      IsKzPsychoStoffe() const
                      {return ( ArtikelMast_->IsKzPsychoStoffe());}
    virtual bool      IsRestDelivery() const
                      {return ( ArtikelFil_->IsRestDelivery());}

    virtual bool      IsRangeMember() const
                      {return ( ArtikelFil_->IsRangeMember());}
    virtual bool      IsNewProduct() const
                      {return ( ArtikelFil_->IsNewProduct());}
    virtual bool      IsReserveHospital() const
                      {return ( ArtikelMast_->IsReserveHospital());}
    virtual bool      IsRoundUpToSTDQty() const
                      {return ( ArtikelMast_->IsRoundUpToSTDQty());}
    virtual bool      IsNotViaDCT() const
                      {return ( ArtikelMast_->IsNotViaDCT());}
    virtual bool      IsNotViaXML() const
                      {return ( ArtikelMast_->IsNotViaXML());}
    virtual bool      IsZuschlagsArtikel() const
                      {return ( ArtikelMast_->IsZuschlagsArtikel());}
    virtual bool      IsAuxStockProductRegional() const
                      {return ( ArtikelFil_->IsAuxStockProductRegional());}
    virtual bool      IsSteller() const
                      {return ( ArtikelMast_->IsSteller());}
    virtual bool      IsPositivListe() const
                      {return ( ArtikelMast_->IsPositivListe());}
    virtual bool      IsSortiment1() const
                      {return ( ArtikelMast_->IsSortiment1());}
    virtual bool      IsSortiment2() const
                      {return ( ArtikelMast_->IsSortiment2());}
    virtual bool      IsSortiment3() const
                      {return ( ArtikelMast_->IsSortiment3());}
    virtual bool      IsSortiment4() const
                      {return ( ArtikelMast_->IsSortiment4());}
    virtual bool      IsSortiment5() const
                      {return ( ArtikelMast_->IsSortiment5());}
    virtual bool      IsBusinessWholeSale() const
                      {return ( ArtikelMast_->IsBusinessWholeSale());}
    virtual bool      IsBusinessPreWholeSale() const
                      {return ( ArtikelMast_->IsBusinessPreWholeSale());}
    virtual bool      IsBusinessPlatform() const
                      {return ( ArtikelMast_->IsBusinessPlatform());}
    virtual bool      IsBusinessSra() const
                      {return ( ArtikelMast_->IsBusinessSra());}
    virtual bool      IsBusinessCap() const
                      {return ( ArtikelMast_->IsBusinessCap());}
    virtual bool      IsListe5() const
                      {return ( ArtikelMast_->IsListe5());}
    virtual bool      IsMedProdABGVerord() const
                      {return ( ArtikelMast_->IsMedProdABGVerord());}
    virtual bool      IsProduserQuota() const
                      {return ( ArtikelMast_->IsProduserQuota());}
    virtual bool      IsMedicalProduct() const
                      {return ( ArtikelMast_->IsMedicalProduct());}
    virtual bool      IsImportArticle() const
                      {return (ArtikelMast_->IsImportArticle());}
    virtual bool      IsKontingentPPE() const
                      {return (ArtikelMast_->IsKontingentPPE());}

    pxSession*        Session()         {return Session_;}
    std::ifstream*    CMsgStream()      {return Session()->CMsgStream()       ;}
    const pxArtClass& ArtClass       () const {return ArtikelMast_->ArtClass()      ; }
    const pxArtFlags& ArtFlags       () const {return ETArtSchalter_                ; }
    long              ArtikelNr      () const {return ArtikelMast_->ArtikelNr()     ; }
    short             FilialNr       () const {return ArtikelFil_->FilialNr()       ; }
    const nString&    MatchCode      () const {return ArtikelMast_->MatchCode()     ; }
    long              PackGroesse    () const {return ArtikelMast_->PackGroesse()   ; }
    const nString&    Darreichform   () const;
    const nString&    NormPackung    () const {return ArtikelMast_->NormPackung()   ; }
    const nString&    Einheit        () const;
    const nString&    Bezeichnung    () const;
    long              VerkaufEinheit () const {return ArtikelFil_->VerkaufEinheit();}
    long              ContainerGroesse() const {return ArtikelFil_->ContainerGroesse();}
    long              Laenge         () const {return ArtikelMast_->Laenge()        ; }
    long              Hoehe          () const {return ArtikelMast_->Hoehe()         ; }
    long              Breite         () const {return ArtikelMast_->Breite()        ; }
    long              Gewicht        () const {return ArtikelMast_->Gewicht()       ; }
    long              NachFrage      () const {return ArtikelFil_->NachFrage()      ; }
    long              NatraStaffelNr () const {return ArtikelFil_->NatraStaffelNr() ; }
    char              Zuzahlung      () const {return ArtikelFil_->Zuzahlung()      ; }
    int               DiscountCode   () const {return ArtikelFil_->DiscountCode()   ; }
    char              Prisoart       () const {return ArtikelFil_->Prisoart()       ; }
    char              Artikelaktiv   () const {return ArtikelFil_->Artikelaktiv()   ; }
    short             LagerBereichNr () const {return ArtikelFil_->LagerBereichNr() ; }
    const nString&    StationNr      () const {return ArtikelFil_->StationNr()      ; }
    const nString&    LagerFachNr    () const {return ArtikelFil_->LagerFachNr()    ; }
    char              VerbundArtikel () const {return ArtikelFil_->VerbundArtikel() ; }

    short             getIBTType() const { return this->VerbundArtikel() - '0'; }

    long              HerstellerNr() const      { return ArtikelMast_->HerstellerNr();           }
    long              LaufzeitMonate()  const   { return ArtikelMast_->LaufzeitMonate();         }
    const nString&    WarenGruppeEigen() const  { return ArtikelMast_->WarenGruppeEigen();       }
    const nString&    Hersteller_Code() const   { return ArtikelMast_->Hersteller_Code();        }
    char              KzPsychoStoffe() const    { return ArtikelMast_->KzPsychoStoffe();         }
    short             TaxLevel() const          { return ArtikelMast_->TaxLevel();               }
    short             TextKey_Hospital() const  { return ArtikelMast_->TextKey_Hospital();       }
    char              KzReserveHospital() const { return ArtikelMast_->KzReserveHospital();      }
    short             TextKey() const           { return ArtikelFil_->TextKey();                 }
    char              ChargenArtikel() const    { return ArtikelFil_->ChargenArtikel();          }
    char              WafoTyp() const           { return ArtikelFil_->WafoTyp();                 }
    char              KZRange() const           { return ArtikelFil_->KZRange();                 }
    char              MoreConditions() const    { return ArtikelFil_->MoreConditions();          }
    long              BestandTagesAnfang() const {return ArtikelFil_->BestandTagesAnfang();      }
    char              CodeBlocage() const       { return ArtikelFil_->CodeBlocage();             }
    bool    IsArticleBlockedForReturns() const  { return ArtikelFil_->IsArticleBlockedForReturns(); }
    short             STDMenge() const          { return ArtikelMast_->STDMenge();               }
    char              KzRundungsSTDMge() const  { return ArtikelMast_->KzRundungsSTDMge();       }
    const nString&    HealthFundCode()  const   { return ArtikelMast_->HealthFundCode();         }
    const nString&    Wirkstoff_NR()  const     { return ArtikelMast_->Wirkstoff_NR();           }
    const nString&    AbdaCode() const          { return ArtikelMast_->AbdaCode();               }
    long              KonsigPartnerNr() const   { return ArtikelMast_->KonsigPartnerNr();        }
    const nString&    ArtikelLangname() const   { return ArtikelMast_->ArtikelLangname();        }
    short             PriceGroup() const        { return ArtikelMast_->PriceGroup();             }
    short             BusinessTypeNo() const    { return ArtikelMast_->BusinessTypeNo();         }
    short             Liste_5 () const          { return ArtikelMast_->Liste_5();                }
    const nDate&      DatumAnlage() const       { return ArtikelMast_->Datum_Anlage();           }
    const nDate&      DateOutOfTrade() const    { return ArtikelMast_->DateOutOfTrade();         }
    char              ArticleBlocked() const    { return ArtikelMast_->ArticleBlocked();         }
    char              IKSCode() const           { return ArtikelMast_->IKSCode();                }
    long              BatchRecallDateReturns() const { return ArtikelMast_->BatchRecallDateReturns(); }
    short             ImportArticle() const     { return ArtikelMast_->ImportArticle(); }
    double            BtmFaktor() const         { return ArtikelMast_->BtmFaktor(); }
    char              TFG() const               { return ArtikelMast_->TFG(); }
    char              KontingentPPE() const     { return ArtikelMast_->KontingentPPE(); }
    const nDate&      Datum_Lieferbar_Ab() const { return ArtikelMast_->Datum_Lieferbar_Ab(); }
    char              MedizinProdukt()     const { return ArtikelMast_->MedizinProdukt(); }
    short             Frozen()             const { return ArtikelMast_->Frozen();         }
    const nDate&      Datum_Aender()       const { return ArtikelMast_->Datum_Aender();   }
    const nString&    ATC_Code()           const { return ArtikelMast_->ATC_Code();       }
    const nString&    MinistryProductCode() const { return ArtikelMast_->MinistryProductCode(); }
    const nString&    HealthFundCodeHospital()  const { return ArtikelMast_->HealthFundCodeHospital(); }
    bool              HasBatchRecallForReturns() const { return ArtikelMast_->HasBatchRecallForReturns(); }
    bool              HasManufacturerRecall() const { return ArtikelMast_->HasManufacturerRecall(); }
    bool              isDispositionExclusion() const { return ArtikelMast_->isDispositionExclusion(); }
    bool              IsTaxPflichtigOTC() const { return ArtikelMast_->IsTaxPflichtigOTC(); }
    bool              IsTaxPflichtigRX()  const { return ArtikelMast_->IsTaxPflichtigRX(); }
    bool              IsTaxPflichtig()    const { return ArtikelMast_->IsTaxPflichtig(); }

    

    pxArtPackUnitList* PackageUnitList();
    void              SetSprache(const nString& Sprache) { Sprache_ = Sprache;        }

    // virtual functions on ArtSpecialCond
    double          InvoiceRebatePct  () const;
    double          RebateInKindPct   () const;
    double          AnnualInvRebPct   () const;
    double          AnnualRebIKPct    () const;
    double          CustRebRedPct     () const;
    double          HiReimBursement   () const;
    double          SupplHiReimb      () const;
    double          SupplFsReimb      () const;
    double          SupplDiscountPct  () const;

    // getIBTBranchArticleConfigPtr
    virtual  IBTBranchArticleConfig* getIBTBranchArticleConfigPtr();

    // if codeblocage changes on stockreceipt, so mark article
    // depend on entry within table countrycodes selected by the
    // new codeblocage
    virtual  int        CheckCodeBlocage(const char codeblocage);
    virtual  nString    GetCBPrintCode() {return ArtikelFil_->GetCBPrintCode();       }

protected:
                        pxBArtikel(pxBArtikel& src);
                        pxBArtikel(pxSession *session, long ArtikelNr, short FilialNr, DBAccessMode mode = cDBGET_READONLY);
    virtual             ~pxBArtikel();
    // members

    long            ArtikelNr_;       // Artikelnummer
    short           FilialNr_;        // Filialnummer
    pxArtMaster   * ArtikelMast_;
    pxArtMasterFr * ArtikelMastFr_;
    pxArtFiliale  * ArtikelFil_;
    pxArtFlags      ETArtSchalter_;
    pxSession     * Session_;
    pxArtPackUnitList* PackageUnitList_;
    pxArtSpecialCond*  ArtSpecialCond_;
    IBTBranchArticleConfig* IBTBranchArticleConfigPtr_;
    nString         Sprache_;

    void        Init();

private:
    friend class pxArtBase;
};

#endif
