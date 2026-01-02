#include "pxcustomerflags.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxCustomerFlags::pxCustomerFlags
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerFlags::pxCustomerFlags
(
    const pxCustomerFlags& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKUNDESCHALTER structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxCustomerFlags::pxCustomerFlags
(
    pxSession   *session,
    tKUNDESCHALTER&     src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerFlags::pxCustomerFlags
(
    pxSession   *session,
    short VZNr,
    long KundenNr,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    VertriebszentrumNr_ = VZNr;
    KundenNr_ = KundenNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKUNDESCHALTER structure.      */
/*----------------------------------------------------------------------------*/
tKUNDESCHALTER&
Assign
(
    tKUNDESCHALTER&    dest,
    const pxCustomerFlags& src
)
{

    dest.IDFNr = src.IDFNr_;
    dest.SKdWerbeFachBelegt = (src.IsWerbeFachBelegt() ? '1' : '0');
    dest.SKdKdFachAktiv = (src.IsKdFachAktiv() ? '1' : '0');
    dest.SKdNatraRestAkzept = (src.IsNatraRestAkzeptanz() ? '1' : '0');
    dest.SKdNettoAktion = (src.IsNettoAktion() ? '1' : '0');
    dest.SKdEtikettService = (src.IsEtikettService() ? '1' : '0');
    dest.SKdDefektLiefern = (src.IsDefektLiefern() ? '1' : '0');
    dest.SKdDefektAbsagen = (src.IsDefektAbsagen() ? '1' : '0');
    dest.SKdSammlDafue = (src.IsSammlDafue() ? '1' : '0');
    dest.SKdApoEKStatisitik = (src.IsApoEKStatisitik() ? '1' : '0');
    dest.SKdAutoErhoehgNNNR = (src.IsAutoErhoehgNNNR() ? '1' : '0');
    dest.SKdDefektMeldgAusw = (src.IsDefektMeldgAusw() ? '1' : '0');
    dest.SKdKontrKoBelege = (src.IsKontrKoBelege() ? '1' : '0');
    dest.SKdAuftragZusammen = (src.IsAuftragZusammen() ? '1' : '0');
    dest.SKdMWSTHalb = (src.IsMWSTHalb() ? '1' : '0');
    dest.SKdStadtKunde = (src.IsStadtKunde() ? '1' : '0');
    dest.SKdValutaSperre = (src.IsValutaSperre() ? '1' : '0');
    dest.SKdSchwerPunkt1 = (src.IsSchwerPunkt1() ? '1' : '0');
    dest.SKdSchwerPunkt2 = (src.IsSchwerPunkt2() ? '1' : '0');
    dest.SKdSchwerPunkt3 = (src.IsSchwerPunkt3() ? '1' : '0');
    dest.SKdSchwerPunkt4 = (src.IsSchwerPunkt4() ? '1' : '0');
    dest.SKdSchwerPunkt5 = (src.IsSchwerPunkt5() ? '1' : '0');
    dest.SKdVerbundGanz = (src.IsVerbundGanz() ? '1' : '0');
    dest.SKdAbschlagrechn = (src.IsAbschlagrechn() ? '1' : '0');
    dest.SKdKdkritisch = (src.IsKdkritisch() ? '1' : '0');
    dest.SKdEilSperre = (src.IsEilSperre() ? '1' : '0');
    dest.SKdAbsagen = (src.IsAbsagen() ? '1' : '0');
    dest.SKdVIPKunde = (src.IsVipKunde() ? '1' : '0');
    dest.SKdAuftragSplit = (src.IsAuftragSplit() ? '1' : '0');
    dest.SKdMussKopf = (src.IsMussKopf() ? '1' : '0');
    dest.SKdSepAuft = (src.IsSepAuft() ? '1' : '0');
    dest.SKdAuftragZurueck = (src.IsAuftragZurueck() ? '1' : '0');
    dest.SKdBestZeit = (src.IsBestellZeit() ? '1' : '0');
    dest.SKdWirdBearb = (src.IsWirdBearbeitet() ? '1' : '0');
    dest.SKdReimport = (src.IsReimportArtikel() ? '1' : '0');
    dest.VertriebszentrumNr = src.VertriebszentrumNr_;;
    dest.KundenNr = src.KundenNr_;
    //dest.TM_Date            = src.TM_Date_.GetYYYYMMDD()      ;
    //dest.TM_Time            = src.TM_Time_.GetHHMMSS()               ;
    dest.SkdVBFilialeMeld = (src.IsVBRueckMeldungNeu() ? '1' : '0');
    dest.SKdKundeAEGesperrt = (src.IsKundeGesperrt() ? '1' : '0');
    dest.SKdWareNachliefern = (src.IsWareNachLiefern() ? '1' : '0');
    dest.SKdRRAbSchluss     = (src.IsAbSchlussRR() ? '1' : '0');
    dest.SKdAbSchlussEil    = (src.IsAbSchlussRREil() ? '1' : '0');
    dest.SKdTrennAlphaText  = (src.IsTrennAlphaText() ? '1' : '0');
    dest.SKdRR0800          = (src.IsRR0800() ? '1' : '0');
    dest.SKdTrennAlphaURR   = (src.IsTrennAlphaURR() ? '1' : '0');
    dest.SKdOriginalMeld    = (src.IsOriginalMeld() ? '1' : '0');
    dest.SKdMehrfachBestell = (src.IsMehrfachBestell() ? '1' : '0');
    dest.SKdOmgKunde        = (src.IsOmgKunde() ? '1' : '0');
    dest.SKdCharge          = (src.IsCharge() ? '1' : '0');
    dest.SKdFMD             = (src.IsFMDCustomer() ? 1 : 0);

    //dest.SKdKeinNl          = (src.IsKeinNl() ? '1' : '0');
    dest.SKdKeinNl          =  src.SWafo_;


    dest.SKdTrennDefekt     = (src.IsTrennDefekt() ? '1' : '0');
    dest.SKdVersandApo      = (src.IsVersandApo() ? '1' : '0');
    dest.SKdNoCloseDefVB    = (src.IsNoCloseDefVB() ? '1' : '0');
    dest.SKdParternariat    = (src.IsParternariat() ? '1' : '0');
    dest.SKdBaAuftrag       = (src.IsBaAuftrag() ? '1' : '0');
    dest.SKdCheckDouble     = (src.IsCheckDouble() ? '1' : '0');
    dest.SKdNoSub           = (src.IsNoSubstitution() ? '1' : '0');
    dest.SKdRetailPermit    = (src.IsRetailPermit() ? '1' : '0');
    dest.SKdHalfMargin      = (src.IsHalfMargin() ? '1' : '0');
    dest.SKdDiscountExcept  = (src.IsDiscountExcept() ? '1' : '0');
    dest.SKdListe5          = (src.IsListe5() ? '1' : '0');
    dest.SKdInvoiceDisc     = (src.IsInvoiceDisc() ? '1' : '0');
    dest.SKdInvoiceEmail    = (src.IsInvoiceEmail() ? '1' : '0');
    //dest.SKdNoExpiryInfo    = (src.IsNoExpiryInfo() ? '1' : '0');
    dest.SKdNoExpiryInfo    = src.ExpiryInfo_;
    dest.MedProd_ABG_Verord = (src.IsMedProdABGVerord() ? '1' : '0');
    dest.SKdNoShortReport   = (src.IsNoShortReport() ? '1' : '0');
    dest.SKdGiveProdQuota   = (src.IsGiveProdQuota() ? '1' : '0');
    dest.KZUpd             = (src.IsUpd() ? '1' : '0');
    dest.SKdPinKunde        = (src.IsPinKunde() ? '1' : '0');
    dest.SKdADGKunde        = (src.IsADGKunde() ? '1' : '0');
    dest.SKdDruckBetaPharm  = (src.IsDruckBetaPharm() ? '1' : '0');
    dest.SKdFax400          = (src.IsFax400() ? '1' : '0');
    dest.SKdDruckEtikett    = (src.IsDruckEtikett() ? '1' : '0');
    dest.SKdDruckTierArznei = (src.IsDruckTierArznei() ? '1' : '0');
    dest.SKdDruckKaufStrukt = (src.IsDruckKaufStrukt() ? '1' : '0');
    dest.SKdKaufStruktArt   = (src.IsKaufStruktArt() ? '1' : '0');
    dest.SKdMonatsRabatt    = (src.IsMonatsRabatt() ? '1' : '0');
    dest.SKdDruckUmsatz     = (src.IsDruckUmsatz() ? '1' : '0');
    dest.ChangeId           = (src.IsChangeId() ? '1' : '0');
    dest.SKdAnrufGenerell   = (src.IsAnrufGenerell() ? '1' : '0');
    dest.SKdBlickPunktAbo   = (src.IsBlickPunktAbo() ? '1' : '0');
    dest.SKdBuecher         = (src.IsBuecher() ? '1' : '0');
    dest.SKdVertriebBindung = (src.IsVertriebBindung() ? '1' : '0');
    dest.SKdPool            = (src.IsPool() ? '1' : '0');
    dest.SKdBouhon          = (src.IsBouhon() ? '1' : '0');
    dest.SKdRoche           = (src.IsRoche() ? '1' : '0');
    dest.SKdVichy           = (src.IsVichy() ? '1' : '0');
    dest.SKdMidas           = (src.IsMidas() ? '1' : '0');
    dest.SKdWatchOrder      = (src.IsWatchOrder() ? '1' : '0');


	dest.SKdFaxInvoice            = (src.IsFaxInvoice() ? 1 : 0);
	dest.SKdFaxBatchChangeAdvice  = (src.IsFaxBatchChangeAdvice() ? 1 : 0);
	dest.SKdMailInvoice           = (src.IsMailInvoice() ? 1 : 0);
	dest.SKdMailBatchChangeAdvice = (src.IsMailBatchChangeAdvice() ? 1 : 0);

	dest.SKdAvoidDefectClearing	= src.AvoidDefectClearing_;
    dest.SMSV3DayIBTInfo		= src.SMSV3DayIBTInfo_;
	dest.MSV3NoOrderCons		= src.MSV3NoOrderCons_;
	dest.NoOrderConsAfterMot	= src.NoOrderConsAfterMot_;
    dest.SKdRXA                 = src.RXAFlag_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKUNDESCHALTER structure to a pxCustomerFlags  */
/*  object.                                                                   */
/*----------------------------------------------------------------------------*/
pxCustomerFlags&
Assign
(
    pxCustomerFlags&   dest,
    const tKUNDESCHALTER&  src
)
{
    dest.IDFNr_        = src.IDFNr;
    dest.VertriebszentrumNr_ = src.VertriebszentrumNr;
    dest.KundenNr_ = src.KundenNr;
    //dest.TM_Date_            = nDate(src.TM_Date);
    //dest.TM_Time_            = src.TM_Time;

    dest.flags_.Resize(pxCustomerFlags::CustFlagCount);
    src.SKdWerbeFachBelegt == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::WerbeFachBelegt) :
        dest.flags_.ClearBit(pxCustomerFlags::WerbeFachBelegt);

    src.SKdKdFachAktiv == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::KdFachAktiv) :
        dest.flags_.ClearBit(pxCustomerFlags::KdFachAktiv);

    src.SKdNatraRestAkzept == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::NatraRestAkzeptanz) :
        dest.flags_.ClearBit(pxCustomerFlags::NatraRestAkzeptanz);

    src.SKdNettoAktion == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::NettoAktion) :
        dest.flags_.ClearBit(pxCustomerFlags::NettoAktion);

    src.SKdEtikettService == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::EtikettService) :
        dest.flags_.ClearBit(pxCustomerFlags::EtikettService);

    src.SKdDefektLiefern == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::DefektLiefern) :
        dest.flags_.ClearBit(pxCustomerFlags::DefektLiefern);

    src.SKdDefektAbsagen == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::DefektAbsagen) :
        dest.flags_.ClearBit(pxCustomerFlags::DefektAbsagen);

    src.SKdSammlDafue == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::SammlDafue) :
        dest.flags_.ClearBit(pxCustomerFlags::SammlDafue);

    src.SKdApoEKStatisitik == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::ApoEKStatisitik) :
        dest.flags_.ClearBit(pxCustomerFlags::ApoEKStatisitik);

    src.SKdAutoErhoehgNNNR == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::AutoErhoehgNNNR) :
        dest.flags_.ClearBit(pxCustomerFlags::AutoErhoehgNNNR);

    src.SKdDefektMeldgAusw == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::DefektMeldgAusw) :
        dest.flags_.ClearBit(pxCustomerFlags::DefektMeldgAusw);

    src.SKdKontrKoBelege == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::KontrKoBelege) :
        dest.flags_.ClearBit(pxCustomerFlags::KontrKoBelege);

    src.SKdAuftragZusammen == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::AuftragZusammen) :
        dest.flags_.ClearBit(pxCustomerFlags::AuftragZusammen);

    src.SKdMWSTHalb == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::MWSTHalb) :
        dest.flags_.ClearBit(pxCustomerFlags::MWSTHalb);

    src.SKdStadtKunde == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::StadtKunde) :
        dest.flags_.ClearBit(pxCustomerFlags::StadtKunde);

    src.SKdValutaSperre == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::ValutaSperre) :
        dest.flags_.ClearBit(pxCustomerFlags::ValutaSperre);

    src.SKdSchwerPunkt1 == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::SchwerPunkt1) :
        dest.flags_.ClearBit(pxCustomerFlags::SchwerPunkt1);

    src.SKdSchwerPunkt2 == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::SchwerPunkt2) :
        dest.flags_.ClearBit(pxCustomerFlags::SchwerPunkt2);

    src.SKdSchwerPunkt3 == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::SchwerPunkt3) :
        dest.flags_.ClearBit(pxCustomerFlags::SchwerPunkt3);

    src.SKdSchwerPunkt4 == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::SchwerPunkt4) :
        dest.flags_.ClearBit(pxCustomerFlags::SchwerPunkt4);

    src.SKdSchwerPunkt5 == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::SchwerPunkt5) :
        dest.flags_.ClearBit(pxCustomerFlags::SchwerPunkt5);

    src.SKdVerbundGanz == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::VerbundGanz) :
        dest.flags_.ClearBit(pxCustomerFlags::VerbundGanz);

    src.SKdAbschlagrechn == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Abschlagrechn) :
        dest.flags_.ClearBit(pxCustomerFlags::Abschlagrechn);

    src.SKdKdkritisch == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Kdkritisch) :
        dest.flags_.ClearBit(pxCustomerFlags::Kdkritisch);

    src.SKdEilSperre == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::EilSperre) :
        dest.flags_.ClearBit(pxCustomerFlags::EilSperre);

    src.SKdAbsagen == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Absagen) :
        dest.flags_.ClearBit(pxCustomerFlags::Absagen);

    src.SKdVIPKunde == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::VipKunde) :
        dest.flags_.ClearBit(pxCustomerFlags::VipKunde);

    src.SKdAuftragSplit == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::AuftragSplit) :
        dest.flags_.ClearBit(pxCustomerFlags::AuftragSplit);

    src.SKdMussKopf == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::MussKopf) :
        dest.flags_.ClearBit(pxCustomerFlags::MussKopf);

    src.SKdSepAuft == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::SepAuft) :
        dest.flags_.ClearBit(pxCustomerFlags::SepAuft);

    src.SKdAuftragZurueck == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::AuftragZurueck) :
        dest.flags_.ClearBit(pxCustomerFlags::AuftragZurueck);

    src.SKdBestZeit == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::BestellZeit) :
        dest.flags_.ClearBit(pxCustomerFlags::BestellZeit);

    src.SKdWirdBearb == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::WirdBearbeitet) :
        dest.flags_.ClearBit(pxCustomerFlags::WirdBearbeitet);

    src.SKdReimport == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::ReimportArtikel) :
        dest.flags_.ClearBit(pxCustomerFlags::ReimportArtikel);

    src.SkdVBFilialeMeld == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::VBRueckMeldungNeu) :
        dest.flags_.ClearBit(pxCustomerFlags::VBRueckMeldungNeu);

    src.SKdKundeAEGesperrt == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::KundeGesperrt) :
        dest.flags_.ClearBit(pxCustomerFlags::KundeGesperrt);

    src.SKdWareNachliefern == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::WareNachLiefern) :
        dest.flags_.ClearBit(pxCustomerFlags::WareNachLiefern);

    src.SKdRRAbSchluss == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::AbSchlussRR) :
        dest.flags_.ClearBit(pxCustomerFlags::AbSchlussRR);

    src.SKdAbSchlussEil == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::AbSchlussRREil) :
        dest.flags_.ClearBit(pxCustomerFlags::AbSchlussRREil);

    src.SKdTrennAlphaText == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::TrennAlphaText) :
        dest.flags_.ClearBit(pxCustomerFlags::TrennAlphaText);

    src.SKdRR0800  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::RR0800) :
        dest.flags_.ClearBit(pxCustomerFlags::RR0800);

    src.SKdTrennAlphaURR  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::TrennAlphaURR) :
        dest.flags_.ClearBit(pxCustomerFlags::TrennAlphaURR);

    src.SKdOriginalMeld  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::OriginalMeld) :
        dest.flags_.ClearBit(pxCustomerFlags::OriginalMeld);

    src.SKdMehrfachBestell  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::MehrfachBestell) :
        dest.flags_.ClearBit(pxCustomerFlags::MehrfachBestell);

    src.SKdOmgKunde  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::OmgKunde) :
        dest.flags_.ClearBit(pxCustomerFlags::OmgKunde);

    src.SKdCharge  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Charge) :
        dest.flags_.ClearBit(pxCustomerFlags::Charge);


    // SKdKeinNl hat 3 Werte (0,1,2) deshalb keine Bitsteuerung für diese Spalte
    // SKdKeinNl wir übernommen in SWafo_
    /*src.SKdKeinNl  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::KeinNl) :
        dest.flags_.ClearBit(pxCustomerFlags::KeinNl);
    */

    dest.SWafo_      = src.SKdKeinNl;

    src.SKdTrennDefekt  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::TrennDefekt) :
        dest.flags_.ClearBit(pxCustomerFlags::TrennDefekt);

    src.SKdVersandApo  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::VersandApo) :
        dest.flags_.ClearBit(pxCustomerFlags::VersandApo);

    src.SKdNoCloseDefVB  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::NoCloseDefVB) :
        dest.flags_.ClearBit(pxCustomerFlags::NoCloseDefVB);

    src.SKdParternariat  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Parternariat) :
        dest.flags_.ClearBit(pxCustomerFlags::Parternariat);

    src.SKdBaAuftrag  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::BaAuftrag) :
        dest.flags_.ClearBit(pxCustomerFlags::BaAuftrag);

    src.SKdCheckDouble  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::CheckDouble) :
        dest.flags_.ClearBit(pxCustomerFlags::CheckDouble);

    src.SKdNoSub  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::NoSub) :
        dest.flags_.ClearBit(pxCustomerFlags::NoSub);

    src.SKdRetailPermit  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::RetailPermit) :
        dest.flags_.ClearBit(pxCustomerFlags::RetailPermit);

    src.SKdHalfMargin  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::HalfMargin) :
        dest.flags_.ClearBit(pxCustomerFlags::HalfMargin);

    src.SKdDiscountExcept  == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::DiscountExcept) :
        dest.flags_.ClearBit(pxCustomerFlags::DiscountExcept);

    src.SKdListe5 == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Liste5) :
        dest.flags_.ClearBit(pxCustomerFlags::Liste5);

    src.SKdInvoiceDisc == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::InvoiceDisc) :
        dest.flags_.ClearBit(pxCustomerFlags::InvoiceDisc);

    src.SKdInvoiceEmail == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::InvoiceEmail) :
        dest.flags_.ClearBit(pxCustomerFlags::InvoiceEmail);

    src.MedProd_ABG_Verord == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::MedProd_ABG_Verord) :
        dest.flags_.ClearBit(pxCustomerFlags::MedProd_ABG_Verord);

    src.SKdNoShortReport == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::NoShortReport) :
        dest.flags_.ClearBit(pxCustomerFlags::NoShortReport);

    src.SKdGiveProdQuota == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::GiveProdQuota) :
        dest.flags_.ClearBit(pxCustomerFlags::GiveProdQuota);

    src.KZUpd == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Upd) :
        dest.flags_.ClearBit(pxCustomerFlags::Upd);

    src.SKdPinKunde == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::PinKunde) :
        dest.flags_.ClearBit(pxCustomerFlags::PinKunde);

    src.SKdADGKunde == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::ADGKunde) :
        dest.flags_.ClearBit(pxCustomerFlags::ADGKunde);

    src.SKdDruckBetaPharm == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::DruckBetaPharm) :
        dest.flags_.ClearBit(pxCustomerFlags::DruckBetaPharm);

    src.SKdFax400 == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Fax400) :
        dest.flags_.ClearBit(pxCustomerFlags::Fax400);

    src.SKdDruckEtikett == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::DruckEtikett) :
        dest.flags_.ClearBit(pxCustomerFlags::DruckEtikett);

    src.SKdDruckTierArznei == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::DruckTierArznei) :
        dest.flags_.ClearBit(pxCustomerFlags::DruckTierArznei);

    src.SKdDruckKaufStrukt == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::DruckKaufStrukt) :
        dest.flags_.ClearBit(pxCustomerFlags::DruckKaufStrukt);

    src.SKdKaufStruktArt == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::KaufStruktArt) :
        dest.flags_.ClearBit(pxCustomerFlags::KaufStruktArt);

    src.SKdMonatsRabatt == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::MonatsRabatt) :
        dest.flags_.ClearBit(pxCustomerFlags::MonatsRabatt);

    src.SKdDruckUmsatz == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::DruckUmsatz) :
        dest.flags_.ClearBit(pxCustomerFlags::DruckUmsatz);

    src.ChangeId == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::ChangeId) :
        dest.flags_.ClearBit(pxCustomerFlags::ChangeId);

    src.SKdAnrufGenerell == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::AnrufGenerell) :
        dest.flags_.ClearBit(pxCustomerFlags::AnrufGenerell);

    src.SKdBlickPunktAbo == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::BlickPunktAbo) :
        dest.flags_.ClearBit(pxCustomerFlags::BlickPunktAbo);

    src.SKdBuecher == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Buecher) :
        dest.flags_.ClearBit(pxCustomerFlags::Buecher);

    src.SKdVertriebBindung == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::VertriebBindung ):
        dest.flags_.ClearBit(pxCustomerFlags::VertriebBindung);

    src.SKdPool == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Pool ):
        dest.flags_.ClearBit(pxCustomerFlags::Pool);

    src.SKdBouhon == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Bouhon ):
        dest.flags_.ClearBit(pxCustomerFlags::Bouhon);

    src.SKdRoche == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Roche ):
        dest.flags_.ClearBit(pxCustomerFlags::Roche);

    src.SKdVichy == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Vichy ):
        dest.flags_.ClearBit(pxCustomerFlags::Vichy);

    src.SKdMidas == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::Midas ):
        dest.flags_.ClearBit(pxCustomerFlags::Midas);

    src.SKdWatchOrder == '1' ?
        dest.flags_.SetBit(pxCustomerFlags::WatchOrder ):
        dest.flags_.ClearBit(pxCustomerFlags::WatchOrder);

	src.SKdFaxInvoice == 1 ?
		dest.flags_.SetBit(pxCustomerFlags::FaxInvoice):
		dest.flags_.ClearBit(pxCustomerFlags::FaxInvoice);

	src.SKdFaxBatchChangeAdvice == 1 ?
		dest.flags_.SetBit(pxCustomerFlags::FaxBatchChangeAdvice):
		dest.flags_.ClearBit(pxCustomerFlags::FaxBatchChangeAdvice);

	src.SKdMailInvoice == 1 ?
		dest.flags_.SetBit(pxCustomerFlags::MailInvoice):
		dest.flags_.ClearBit(pxCustomerFlags::MailInvoice);

	src.SKdMailBatchChangeAdvice == 1 ?
		dest.flags_.SetBit(pxCustomerFlags::MailBatchChangeAdvice):
		dest.flags_.ClearBit(pxCustomerFlags::MailBatchChangeAdvice);

    dest.ExpiryInfo_          = src.SKdNoExpiryInfo;
    dest.AvoidDefectClearing_ = src.SKdAvoidDefectClearing;
    dest.SMSV3DayIBTInfo_     = src.SMSV3DayIBTInfo;
	dest.MSV3NoOrderCons_     = src.MSV3NoOrderCons;
	dest.NoOrderConsAfterMot_ = src.NoOrderConsAfterMot;
    dest.FMDCustomer_         = src.SKdFMD;
    dest.RXAFlag_             = src.SKdRXA;

    // NoExpiryInfo hat die Werte 0 -4
    //src.SKdNoExpiryInfo == '1' ?
    //    dest.flags_.SetBit(pxCustomerFlags::NoExpiryInfo) :
    //    dest.flags_.ClearBit(pxCustomerFlags::NoExpiryInfo);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustomerFlags:: Init()
{
    tKUNDESCHALTER    record;
    memset(&record, 0 , sizeof(tKUNDESCHALTER));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the record structure    */
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxCustomerFlags&
pxCustomerFlags :: operator=( const pxCustomerFlags& src)
{
    tKUNDESCHALTER    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKUNDESCHALTER structure 'src' to this instance. */
/*----------------------------------------------------------------------------*/
pxCustomerFlags&
pxCustomerFlags :: operator=( const tKUNDESCHALTER& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustomerFlags:: Get
(
    DBAccessMode mode
)

{
    tKUNDESCHALTER record;
    memset(&record, 0, sizeof(tKUNDESCHALTER));
    //record.IDFNr = IDFNr_;
    record.KundenNr = KundenNr_;
    record.VertriebszentrumNr = VertriebszentrumNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record)
                                               : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tKUNDESCHALTER struct
    else
       DBCondition(nMessage(CMsgStream(), CMSG_CST_NOFLAGS, IDFNr_),
                   retval);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustomerFlags :: Put()
{
    tKUNDESCHALTER record;
    memset(&record, 0, sizeof(tKUNDESCHALTER));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKUNDESCHALTER));
}

int
pxCustomerFlags :: Read
(
	const void *record
)
{
	return pxKundeSchalterRead((tKUNDESCHALTER*)record);
}

int
pxCustomerFlags :: ReadLock
(
	const void *record
)
{
	return pxKundeSchalterReadLock((tKUNDESCHALTER*)record);
}

int
pxCustomerFlags :: Insert
(
	const void *record
)
{
	return pxKundeSchalterInsert((tKUNDESCHALTER*)record);
}

int
pxCustomerFlags :: Update
(
	const void *record
)
{
	return pxKundeSchalterUpdate((tKUNDESCHALTER*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCustomerFlags list objects being inserted in the                    */
/*  following ascending sequence:                                             */
/*  KundenNr                                                                  */
/*----------------------------------------------------------------------------*/
int
pxCustomerFlags::CompareTo
(
    const nCollectable*   That,
          void*           /*p*/,
    const long            /*lparm*/
)   const

{
    pxCustomerFlags*that = (pxCustomerFlags*)That;
    int retval = (KundenNr_ == that->KundenNr_) ? 0
                : (KundenNr_ > that->KundenNr_ ? 1 : -1);

    return retval;
}
