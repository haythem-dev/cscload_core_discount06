#ifndef PXCUSTOMERFLAGS_INC
#define PXCUSTOMERFLAGS_INC

#include "pxbase/pxrecord.hpp"

struct tKUNDESCHALTER;

class pxCustomerFlags : public pxDBRecord
{
/*----------------------------------------------------------------------------*/
/*  Enumerate the customer flag positions.                                    */
/*----------------------------------------------------------------------------*/
public:
    enum tCustFlags
    {
        WerbeFachBelegt,                // SKd Werbefach belegt
        KdFachAktiv,                    // SKd Kundenfach aktiv
        NatraRestAkzeptanz,             // SKd Natra Restakzeptanz
        NettoAktion,                    // SKd Nettoaktion
        EtikettService,                 // SKd Etiketten Service
        DefektLiefern,                  // SKd Defekte nachliefern
        DefektAbsagen,                  // SKd Defekte absagen
        SammlDafue,                     // SKd Datensammlung aus Dafue
        ApoEKStatisitik,                // SKd Apo EK Statisitik
        AutoErhoehgNNNR,                // SKd Autom Mengenerhoehung NN/NR
        DefektMeldgAusw,                // SKd Defektmeldung Ausweichart.
        KontrKoBelege,                  // SKd Druck Kontroll Kommibelege
        AuftragZusammen,                // SKd Auftragzusammenfuehrung
        MWSTHalb,                       // SKd MWST Satz halb
        StadtKunde,                     // SKd Stadtkunde
        ValutaSperre,                   // SKd Valutasperre
        SchwerPunkt1,                   // SKd Schwerpunkt 1
        SchwerPunkt2,                   // SKd Schwerpunkt 2
        SchwerPunkt3,                   // SKd Schwerpunkt 3
        SchwerPunkt4,                   // SKd Schwerpunkt 4
        SchwerPunkt5,                   // SKd Schwerpunkt 5
        VerbundGanz,                    // SKd Verbundservice ganztags
        Abschlagrechn,                  // SKd Abschlag rechnen
        Kdkritisch,                     // SKd Kunde kritisch
        EilSperre,                      // SKd Eilbotensperre
        Absagen,                        // SKd Absagen
        VipKunde,                       // SKd Vipkunde
        AuftragSplit,                   // SKd Auftragsplit
        MussKopf,                       // SKd MussKopf
        SepAuft,                        // SKd SepAuft
        AuftragZurueck,                 // SKd AuftragZurueck
        BestellZeit,                    // SKd Bestell Zeit
        WirdBearbeitet,                 // SKd Wird Bearbeitet
        Upd,                            // SKd Upd
        ReimportArtikel,                // Skd Reimport
        WareNachLiefern,                // Skd WarenNachliefern
        PinKunde,                       // Skd Pin Kunde
        ADGKunde,                       // Skd ADG Kunde
        DruckBetaPharm,                 // Skd Druck Beta Pharm
        Fax400,                         // Skd Fax 400
        KundeGesperrt,                  // Skd KundeAEGesperrt
        DruckEtikett,                   // Skd Druck Etikett
        DruckTierArznei,                // Skd Druck TierArznei
        DruckKaufStrukt,                // Skd Druck KaufStrukt
        KaufStruktArt,                  // Skd KaufStruktArt
        MonatsRabatt,                   // Skd MonatsRabatt
        DruckUmsatz,                    // Skd DruckUmsatz
        ChangeId,                       // Skd ChangeId
        AnrufGenerell,                  // Skd Anruf Generell
        BlickPunktAbo,                  // Skd Anruf Generell
        Buecher,                        // Skd Buecher
        VertriebBindung,                // Skd Vertrieb Bindung
        Pool,                           // Skd Pool
        Bouhon,                         // Skd Bouhon
        Roche,                          // Skd Roche
        Vichy,                          // Skd Vichy
        VBRueckMeldungNeu,              // Skd VBFilialeMeld
        AbSchlussRR,                    // Skd RRAbSchluss
        AbSchlussRREil,                 // Skd AbSchlussEil
        TrennAlphaText,                 // Skd TrennAlphaText
        RR0800,                         // Skd RR0800
        TrennAlphaURR,                  // Skd TrennAlphaURR
        OriginalMeld,                   // Skd OriginalMeld
        Midas,                          // Skd Midas
        MehrfachBestell,                // Skd MehrfachBestell
        OmgKunde,                       // Skd Omg Kunde(Swiss special)
        Charge,                         // Skd Charge
        KeinNl,                         // Skd KeinNl bei nicht lieferbar Hersteller
        TrennDefekt,                    // Skd TrennDefekt vom normalen Auftrag
        VersandApo,                     // Skd VersandApo
        NoCloseDefVB,                   // Skd No Close Defekt & Verbund
        Parternariat,                   // Skd Parternariat
        BaAuftrag,                      // Skd BaAuftrag
        CheckDouble,                    // SKd CheckDouble
        NoSub,                          // SKd NoSub
        WatchOrder,                     // SKd Watch Order
        RetailPermit,                   // SKd RetailPermit
        HalfMargin,                     // SKd HalfMargin
        DiscountExcept,                 // SKd DiscountExcept
        Liste5,                         // SKd Liste5
        InvoiceDisc,                    // SKd InvoiceDisc
        InvoiceEmail,                   // SKd InvoiceEmail
        NoExpiryInfo,                   // SKd NoExpiryInfo
        MedProd_ABG_Verord,             // MedProd_ABG_Verord
        NoShortReport,                  // No Short Report
        GiveProdQuota,                  // Give Proct Quota
		FaxInvoice,						// Skd FaxInvoice
		FaxBatchChangeAdvice,			// Skd FaxBatchChangeAdvice
		MailInvoice,					// Skd MailInvoice
		MailBatchChangeAdvice,			// Skd MailBatchChangeAdvice
		CustFlagCount                   // last flag, counts number of flags

    };


    virtual           ~pxCustomerFlags()    {;}
                      pxCustomerFlags(pxSession *session);
                      pxCustomerFlags(const pxCustomerFlags& src);
                      pxCustomerFlags(pxSession *session, short VZNr, long KundenNr,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxCustomerFlags&      operator=(const pxCustomerFlags& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
//  Queries:
    long              IDFNr()                 const { return IDFNr_;                    }
    short             VertriebszentrumNr()    const { return VertriebszentrumNr_;       }
    short             AvoidDefectClearing()   const { return AvoidDefectClearing_;      }
    short             SMSV3DayIBTInfo()       const { return SMSV3DayIBTInfo_;          }
	short			  MSV3NoOrderCons()       const { return MSV3NoOrderCons_;          }
	bool			  IsNoOrderConsAfterMot() const	{ return NoOrderConsAfterMot_ == 1; }
    bool              IsFMDCustomer()         const { return FMDCustomer_ == 1;         }
    char              ExpiryInfo()            const { return ExpiryInfo_;               }
    char              RXAFlag()               const { return RXAFlag_;                  }

    bool     IsWerbeFachBelegt       () const {return flags_.TestBit (WerbeFachBelegt   );}
    void     SetWerbeFachBelegt      ()       {       flags_.SetBit  (WerbeFachBelegt   );}
    void     ClearWerbeFachBelegt    ()       {       flags_.ClearBit(WerbeFachBelegt   );}
    bool     IsKdFachAktiv           () const {return flags_.TestBit(KdFachAktiv        );}
    bool     IsNatraRestAkzeptanz    () const {return flags_.TestBit(NatraRestAkzeptanz );}
    bool     IsNettoAktion           () const {return flags_.TestBit(NettoAktion        );}
    bool     IsEtikettService        () const {return flags_.TestBit(EtikettService     );}
    bool     IsDefektLiefern         () const {return flags_.TestBit(DefektLiefern      );}
    bool     IsDefektAbsagen         () const {return flags_.TestBit(DefektAbsagen      );}
    bool     IsSammlDafue            () const {return flags_.TestBit(SammlDafue         );}
    bool     IsApoEKStatisitik       () const {return flags_.TestBit(ApoEKStatisitik    );}
    bool     IsAutoErhoehgNNNR       () const {return flags_.TestBit(AutoErhoehgNNNR    );}
    bool     IsDefektMeldgAusw       () const {return flags_.TestBit(DefektMeldgAusw    );}
    bool     IsKontrKoBelege         () const {return flags_.TestBit(KontrKoBelege      );}
    bool     IsAuftragZusammen       () const {return flags_.TestBit(AuftragZusammen    );}
    bool     IsMWSTHalb              () const {return flags_.TestBit(MWSTHalb           );}
    bool     IsStadtKunde            () const {return flags_.TestBit(StadtKunde         );}
    bool     IsValutaSperre          () const {return flags_.TestBit(ValutaSperre       );}
    bool     IsSchwerPunkt1          () const {return flags_.TestBit(SchwerPunkt1       );}
    bool     IsSchwerPunkt2          () const {return flags_.TestBit(SchwerPunkt2       );}
    bool     IsSchwerPunkt3          () const {return flags_.TestBit(SchwerPunkt3       );}
    bool     IsSchwerPunkt4          () const {return flags_.TestBit(SchwerPunkt4       );}
    bool     IsSchwerPunkt5          () const {return flags_.TestBit(SchwerPunkt5       );}
    bool     IsVerbundGanz           () const {return flags_.TestBit(VerbundGanz        );}
    bool     IsAbschlagrechn         () const {return flags_.TestBit(Abschlagrechn      );}
    bool     IsKdkritisch            () const {return flags_.TestBit(Kdkritisch         );}
    bool     IsAbsagen               () const {return flags_.TestBit(Absagen            );}
    bool     IsEilSperre             () const {return flags_.TestBit(EilSperre          );}
    bool     IsVipKunde              () const {return flags_.TestBit(VipKunde           );}
    bool     IsAuftragSplit          () const {return flags_.TestBit(AuftragSplit       );}
    bool     IsMussKopf              () const {return flags_.TestBit(MussKopf           );}
    bool     IsSepAuft               () const {return flags_.TestBit(SepAuft            );}
    bool     IsAuftragZurueck        () const {return flags_.TestBit(AuftragZurueck     );}
    bool     IsBestellZeit           () const {return flags_.TestBit(BestellZeit        );}
    bool     IsWirdBearbeitet        () const {return flags_.TestBit(WirdBearbeitet     );}
    bool     IsReimportArtikel       () const {return flags_.TestBit(ReimportArtikel    );}
    bool     IsVBRueckMeldungNeu     () const {return flags_.TestBit(VBRueckMeldungNeu  );}
    bool     IsKundeGesperrt         () const {return flags_.TestBit(KundeGesperrt      );}
    bool     IsWareNachLiefern       () const {return flags_.TestBit(WareNachLiefern    );}
    bool     IsAbSchlussRR           () const {return flags_.TestBit(AbSchlussRR        );}
    bool     IsAbSchlussRREil        () const {return flags_.TestBit(AbSchlussRREil     );}
    bool     IsTrennAlphaText        () const {return flags_.TestBit(TrennAlphaText     );}
    bool     IsRR0800                () const {return flags_.TestBit(RR0800             );}
    bool     IsTrennAlphaURR         () const {return flags_.TestBit(TrennAlphaURR      );}
    bool     IsOriginalMeld          () const {return flags_.TestBit(OriginalMeld       );}
    bool     IsMehrfachBestell       () const {return flags_.TestBit(MehrfachBestell    );}
    bool     IsOmgKunde              () const {return flags_.TestBit(OmgKunde           );}
    bool     IsCharge                () const {return flags_.TestBit(Charge             );}
   // bool     IsKeinNl                () const {return flags_.TestBit(KeinNl             );}
    bool     IsTrennDefekt           () const {return flags_.TestBit(TrennDefekt        );}
    bool     IsVersandApo            () const {return flags_.TestBit(VersandApo         );}
    bool     IsNoCloseDefVB          () const {return flags_.TestBit(NoCloseDefVB       );}
    bool     IsParternariat          () const {return flags_.TestBit(Parternariat       );}
    bool     IsBaAuftrag             () const {return flags_.TestBit(BaAuftrag          );}
    bool     IsCheckDouble           () const {return flags_.TestBit(CheckDouble        );}
    bool     IsNoSubstitution        () const {return flags_.TestBit(NoSub              );}
    bool     IsRetailPermit          () const {return flags_.TestBit(RetailPermit       );}
    bool     IsHalfMargin            () const {return flags_.TestBit(HalfMargin         );}
    bool     IsDiscountExcept        () const {return flags_.TestBit(DiscountExcept     );}
    bool     IsListe5                () const {return flags_.TestBit(Liste5             );}
    bool     IsInvoiceDisc           () const {return flags_.TestBit(InvoiceDisc        );}
    bool     IsInvoiceEmail          () const {return flags_.TestBit(InvoiceEmail       );}
    //bool     IsNoExpiryInfo        () const {return flags_.TestBit(NoExpiryInfo       );}
    bool     IsMedProdABGVerord      () const {return flags_.TestBit(MedProd_ABG_Verord );}
    bool     IsNoShortReport         () const {return flags_.TestBit(NoShortReport      );}
    bool     IsGiveProdQuota         () const {return flags_.TestBit(GiveProdQuota      );}
    bool     IsUpd                   () const {return flags_.TestBit(Upd                );}
    bool     IsPinKunde              () const {return flags_.TestBit(PinKunde           );}
    bool     IsADGKunde              () const {return flags_.TestBit(ADGKunde           );}
    bool     IsDruckBetaPharm        () const {return flags_.TestBit(DruckBetaPharm     );}
    bool     IsFax400                () const {return flags_.TestBit(Fax400             );}
    bool     IsDruckEtikett          () const {return flags_.TestBit(DruckEtikett       );}
    bool     IsDruckTierArznei       () const {return flags_.TestBit(DruckTierArznei    );}
    bool     IsDruckKaufStrukt       () const {return flags_.TestBit(DruckKaufStrukt    );}
    bool     IsKaufStruktArt         () const {return flags_.TestBit(KaufStruktArt      );}
    bool     IsMonatsRabatt          () const {return flags_.TestBit(MonatsRabatt       );}
    bool     IsDruckUmsatz           () const {return flags_.TestBit(DruckUmsatz        );}
    bool     IsChangeId              () const {return flags_.TestBit(ChangeId           );}
    bool     IsAnrufGenerell         () const {return flags_.TestBit(AnrufGenerell      );}
    bool     IsBlickPunktAbo         () const {return flags_.TestBit(BlickPunktAbo      );}
    bool     IsBuecher               () const {return flags_.TestBit(Buecher            );}
    bool     IsVertriebBindung       () const {return flags_.TestBit(VertriebBindung    );}
    bool     IsPool                  () const {return flags_.TestBit(Pool               );}
    bool     IsBouhon                () const {return flags_.TestBit(Bouhon             );}
    bool     IsRoche                 () const {return flags_.TestBit(Roche              );}
    bool     IsVichy                 () const {return flags_.TestBit(Vichy              );}
    bool     IsMidas                 () const {return flags_.TestBit(Midas              );}
    bool     IsWatchOrder            () const {return flags_.TestBit(WatchOrder         );}
	bool     IsFaxInvoice            () const {return flags_.TestBit(FaxInvoice         );}
	bool     IsFaxBatchChangeAdvice  () const {return flags_.TestBit(FaxBatchChangeAdvice);}
	bool     IsMailInvoice           () const {return flags_.TestBit(MailInvoice        );}
	bool     IsMailBatchChangeAdvice () const {return flags_.TestBit(MailBatchChangeAdvice);}

    bool     IsKeinNlNghNgh          () const {return SWafo_ == '2';}
    bool     IsKeinNlNgh             () const {return SWafo_ == '1';}
    bool     IsKeinNl                () const {return SWafo_ == '0';}

protected:
    pxCustomerFlags(pxSession *session, tKUNDESCHALTER& src);
    pxCustomerFlags&      operator=(const tKUNDESCHALTER& src);
    friend
    pxCustomerFlags&      Assign(pxCustomerFlags& dest, const tKUNDESCHALTER& src);
    friend
    tKUNDESCHALTER&   Assign(tKUNDESCHALTER& dest, const pxCustomerFlags& src);
    virtual  int      Read(const void *record);
    virtual  int      ReadLock(const void *record);
    virtual  int      Insert(const void *record);
    virtual  int      Update(const void *record);
    void              Init();

    long              IDFNr_;           // Kundennummer IDF
    short             VertriebszentrumNr_;           // VZ
    long              KundenNr_;           // Kundennummer
    nBitMap           flags_;
    char              SWafo_;              // Wafo schalter bezogen auf skdkeinnl
    char              ExpiryInfo_;         // ExpiryInfo bezogen auf SkdNoExpiryInfo
    short             AvoidDefectClearing_; // avoid defect clearing
    short             SMSV3DayIBTInfo_;     // tagverbundinfo
	short			  MSV3NoOrderCons_;		// keine Auftragszusammenführung zw. Hauptbestellzeitpunkt und Bestellfensterende
	short			  NoOrderConsAfterMot_;	// keine Auftragszusammenführung nach Hauptbestellzeitpunkt
    short             FMDCustomer_;
    char              RXAFlag_;
};

#endif // PXCUSTOMERFLAGS_INC
