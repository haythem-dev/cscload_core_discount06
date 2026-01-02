/*  Do not allow to include the file more than once                           */
#ifndef pxrecord_DOTH
#define pxrecord_DOTH

/*****************************************************************************/
/*  Kunde                                                                    */
/*  Kundenstammsatz                                                          */
/*****************************************************************************/

struct tKUNDE
{
	long           IDFNr;                        /* Kundennummer IDF */
	char           MatchCode[12+1];              /* MatchCode */
	short          FilialNr;                     /* Filialnummer */
	long           KdNr;                         /* Kundennummer Intern */
	long           ETArtKlasse1;                 /* ETab Artikel Klasse 1 */
	long           ETArtKlasse2;                 /* ETab Artikel Klasse 2 */
	long           ETKdMerkmal1;                 /* ETab Kunde Merkmale */
	long           ETKdMerkmal2;                 /* ETab Kunde Merkmale 2 */
	short          AnredeKz;                     /* Kennzeichen Anrede */
	char           NameApo[40+1];                /* Name Apotheke */
	char           NameInhaber[30+1];            /* Name Inhaber */
	char           Strasse[30+1];                /* Strasse */
	char           Ort[30+1];                    /* Ort */
	char           Postleitzahl[10+1];            /* Postleitzahl */
	char           TelNr[20+1];                  /* Telefonnummer */
	char           TelNrDafue[20+1];             /* Telefonnummer Dafue */
	char           FaxNr[25+1];                  /* Faxnummer */
	char           TelKurzwahl[4+1];             /* Telefon Kurzwahl */
	long           IMSBezirkNr;                  /* IMS Bezirksnummer */
	char           KdGruppe[2+1];                /* Kundengruppe */
	long           PersonalNrVertr;              /* Personalnummer Vertreter */
	char           DafueSystem[2+1];             /* Dafue System */
	char           KzKdDoppelKontr;              /* KzKd Doppelkontrolle */
	char           LagerFachNrRgBei[4+1];        /* Lager Fachnummer Rechn. Beilage */
	short          AnzPosLS_RG;                  /* Anzahl Positionen LS/RG */
	short          AnzPosSortBehaelt;            /* Anzahl Positionen Sort Behaelter */
	char           KzKdKlasse[3+1];              /* KzKd Klassifizierung */
	short          OriginalFilialNr;             /* Filialnummer Original */
	short          NotFilialNr;                  /* Filialnummer Not */
	char           Bemerkungen[240+1];           /* Bemerkungen */
	char           KundeText[240+1];             /* Kunde Text */
	char           VerbundKunde;                 /* KzKd Verbundkunde */
	char           StdAufKoBuart[4+1];           /* Standard Auftrag Kommi Buchart */
	char           PassWord[8+1];                /* Password */
	char           KuehlBox;                     /* KzKd KuehlBox */
	long           TourenKippZeit;               /* Tour Kippzeit */
	char           VZKk1;                        /* VZKK1*/
	char           Land[3+1];                    /* LAND */
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           KundenNr;                     /* Kunden Nummer VZ */
	char           EmailAdresse[60+1];           /* Email Adresse */
	char           NachLieferTyp;                /* Nachliefertyp Wafosystem*/
	long           PartnerNr;                    /* Partnernummer/kreditlimit*/
	char           KzSprache[2+1];               /* Sprachkennzeichen*/
	char           KzPsychoStoffe;               /* Kennzeichen Psychotropische Staffe*/
	char           XMLPreisLevel;                /* Kennzeichen XMLPreisLevel*/
	char           PreWholeTyp;                  /* Kennzeichen Prewholetyp*/
	char           XMLInfoLevel;                 /* Kennzeichen XMLInfolevel*/
	char           NationalCustomerNo[18+1];     /* National CustomerNo*/
	char           RatioCustomerNo[12+1];        /* Ratiopharm Customerno*/
	short          AnzAufClose;                  /* Anzahl Auftr„ge ab wann close*/
	char           KrankenKassenNr[6+1];         /* Krankenkassennummer*/
	char           CalculationType;              /* Kennzeichen Calculationtype*/
	short          Surcharge_Basic;              /* Basis Zuschlag 0 = AEP 1 = GEP*/
	short          Deduction_Basic;              /* Basis Abschlag 0 = AEP 1 = GEP*/
	double         SurchargePct;                 /* Zuschlag percentage*/
	double         DeductionPct;                 /* Abschlag percentage*/
	short          VatRegistered;                /* Mehrwertsteuer registriert*/
	short          RebateMethFreeSale;           /* Rebatemethode Freesale*/
	short          RebateMethHealthf;            /* Rebatemethode Healthfund*/
	long           MainCstNo;                    /* Chainnumber*/
	short          Surcharge_BasicKK;            /* Basis Zuschlag 0 = AEP 1 = GEP Krankenkasse*/
	short          Deduction_BasicKK;            /* Basis Abschlag 0 = AEP 1 = GEP Krankenkasse*/
	double         SurchargePctKK;               /* Zuschlag percentage Krankenkasse*/
	double         DeductionPctKK;               /* Abschlag percentage Krankenkasse*/
	short          LieferMeldung;                /* LieferMeldung*/
	long           ManufacturerNo;               /* manufacturerno*/
	long           MSV3CfgChangeDate;            /* MSV3 configuration change date */
};


/*****************************************************************************/
/*  Kundenauftrag                                                            */
/*  Kundenauftragstabelle                                                    */
/*****************************************************************************/

struct tKDAUFTRAG
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	char           KdAuftragStat[16+1];          /* Kunde Auftrag Status */
	long           IDFNr;                        /* Kundennummer IDF */
	char           GeraetName[8+1];              /* Geraet Name */
	char           TourId[6+1];                  /* Tour Identifikation */
	char           TourIdAlt[6+1];               /* Tour Identifikation Alt */
	long           PersonalNr;                   /* Personalnummer */
	char           MatchCode[12+1];              /* MatchCode */
	long           RechnungNr;                   /* Rechnungsnummer */
	short          FilialNr;                     /* Filialnummer */
	long           ETAuftragSchalter1;           /* ETab Auftrag Schalter 1 */
	long           ETAuftragSchalter2;           /* ETab Auftrag Schalter 2 */
	long           ETAuftragSchalter3;           /* ETab Auftrag Schalter 3 */
	long           ETAuftragSchalter4;           /* ETab Auftrag Schalter 4 */
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
	char           KoArt;                        /* Kommissionierungsart */
	char           BuchArt;                      /* Buchungsart */
	long           DatumValuta;                  /* Datum Valuta */
	double         WertAuftrag;                  /* Wert Auftrag */
	double         WertLieferung;                /* Wert Lieferung */
	double         WertZeilen;                   /* Wert Zeilendurchschnitt */
	long           AnzPos;                       /* Anzahl Positionen */
	long           AnzPosOB;                     /* Anzahl Positionen ohne Berechng */
	long           AnzPosletzte;                 /* Anzahl Pos letzter Abschluss */
	long           AnzPosDafue;                  /* Anzahl Positionen Dafue */
	long           AnzPosDafueFehler;            /* Anzahl Positionen Dafue Fehler */
	long           AnzAlphaText;                 /* Anzahl Alphatexte */
	long           AnzBTM;                       /* Anzahl Betaeubungsmittel */
	long           AnzContainer;                 /* Anzahl Container */
	long           AnzBehaeltWechsel;            /* Anzahl Behaelterwechsel */
	long           AnzBehaelt;                   /* Anzahl Kommi Behaelter */
	long           AnzSonderwanne;               /* Anzahl Sonderwannen */
	long           BehaelterGewicht;             /* Gewicht Behaelter */
	double         RabattBarProz;                /* Rabatt Bar in Prozent */
	long           ZeitEndeAM;                   /* Zeit Betriebsende morgens */
	long           ZeitEndePM;                   /* Zeit Betriebsende abends */
	char           LagernrRechnung;              /* Lagernummer Rechn. Ausloesend */
	long           AuftragNrKo;                  /* Kommi Auftrag Nummer */
	long           DMobilPlatzNr;                /* Datamobil Platznummer */
	unsigned char  SKdDefektAbsagen;             /* SKd Defekte absagen */
	long           Druckposition;                /* Druckposition (LORBAS) */
	long           BatchSchreiben;               /* Herkunftstyp */
	char           Bemerkungen[240+1];           /* Bemerkungen */
	char           KundeText[240+1];             /* Kunde Text */
	short          HerkunftFiliale;              /* Herkunft Filiale */
	char           NaechsteTour[6+1];            /* Naechste Tour */
	char           LetzteTour[6+1];              /* Letzte Tour */
	long           DafueAuftragNr;               /* Dafue Auftragnummer */
	char           DafueGeraeteName[2+1];        /* Dafue Geraete Name */
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           KundenNr;                     /* Generelle Kundennr */
	long           KdAuftragNrFiliale;           /* Filialbezogene KdAuftragNr (VSE) */
	short          SendeStatus;                  /* ›bertragungsstatus (VSE) */
	short          PoolTyp;                      /* Pooltype*/
	short          PoolNr;                       /* PoolNummer*/
	char           ZuGrund[16+1];                /* Zur’ckstellgrund*/
	long           DatumAuslieferung;            /* Datum Ausfieferung*/
	long           KdAuftragNrOrg;               /* Auftragnummer original*/
	long           DatumOrg;                     /* Datum Auftragnummer original*/
	char           KzRestored;                   /* Kennzeichen Auftrag restored*/
	long           BatchAuftragNr;               /* Batch Auftragsnummer*/
	char           SubOrderType[3+1];            /* Ordertype Subordertype*/
	char           PaymentTerm[4+1];             /* Payment condition*/
	short          AnzAuf;                       /* Anzahl Auftr„ge(Auftragzusammenf’hrung)*/
	long           DatumValutaBatch;             /* Datum Valuta aus Batch */
	short          ValutaMonAuto;                /* Automatisches Valuta aus Kundestamm*/
	short          ValutaMonManuell;             /* Valuta aus der manuellen Eingabe*/
	long           TenderNo;                     /* TenderNo(RS/BG)*/
	long           DatumVersand;                 /* Datum Versand*/
	long           DatumBTM;                     /* Datum BTM*/
	char           BTMFormularNr[10+1];          /* BTM Formular Nummer*/
	double         WertNetto;                    /* Wert Netto */
	double         WertRabatt;                   /* Wert Rabatt*/
	char           InvoiceNumber[15+1];          /* Rechnungsnummer*/
	long           PaymentDate;                  /* Payment date*/
	char           PaymentType;                  /* C = Bar,Z = Zielkauf*/
	long           ETAuftragSchalter5;           /* ETab Auftrag Schalter 5 */
	long           ETAuftragSchalter6;           /* ETab Auftrag Schalter 6 */
	long           DriverID;                     /* Driver Id(BG)*/
	char           XMLReferenceNo[9+1];          /* XML Reference Number*/
	long           LogisticVolume;               /* LogisticVolume Collectiv Order (FR)*/
	char           OrderLabel[40+1];             /* MSV3 Order Label (DE) */
	short 		   DPODays;					     /* Days for documentdate after invoice date */
	long 		   OrderPeriodID;				 /* MSV3 order period id */
};


/*****************************************************************************/
/*  Kundenauftrag Bestellposition                                            */
/*  Kundenauftrags-Bestellposition                                           */
/*****************************************************************************/

struct tKDAUFTRAGPOS
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	long           ArtikelNr;                    /* Artikelnummer */
	short          PosTyp;                       /* Position Typ */
	short          GeraetTyp;                    /* Geraete Typ */
	short          FehlerMenge;                  /* Fehler Menge */
	short          FehlerArtikel;                /* Fehler Artikel */
	long           ETPosSchalter1;               /* ETab Position Schalter 1 */
	long           ETPosSchalter2;               /* ETab Position Schalter 2 */
	long           ETPosSchalter3;               /* ETab Position Schalter 3 */
	long           ETPosSchalter4;               /* ETab Position Schalter 4 */
	long           ETPosSchalter5;               /* ETab Position Schalter 5 */
	long           ETPosSchalter6;               /* ETab Position Schalter 6 */
	long           MengeBestellt;                /* Menge Bestellt */
	long           MengeBestaetigt;              /* Menge Bestaetigt */
	long           MengeGeliefert;               /* Menge Geliefert */
	long           MengeAbgebucht;               /* Menge Abgebucht */
	long           MengeNatra;                   /* Menge Naturalrabatt */
	long           MengeNatraBasis;              /* Menge Naturalrabatt Basis */
	long           MengeNatraGrossH;             /* Menge Naturalrabatt Grosshandel */
	long           MengeNatraHerst;              /* Menge Naturalrabatt Hersteller */
	double         PreisEKApo;                   /* Preis EK Apotheke */
	double         PreisVKApo;                   /* Preis VK Apotheke */
	double         PreisEKApoNetto;              /* Preis EK Apotheke Nettoaktion */
	double         PreisEKGrosso;                /* Preis EK Grosso */
	double         PreisEKGrossoNA;              /* Preis EK Grosso Nettoaktion */
	double         RabattFestDM;                 /* Rabatt Fest in DM */
	double         PreisFest;                    /* Preis Fest */
	double         RabattFest;                   /* Rabatt Fest in Prozent */
	double         PreisProzent;                 /* Preis in Prozent */
	long           KoBehaeltNr;                  /* Kommi Einheit Nummer */
	char           Rabatthilfe;                  /* Rabatthilfsfeld */
	char           Rabattfaehig[2+1];            /* Rabattfaehigkeit Hinweis */
	long           ArtBestNachUpd;               /* Bestand nach Update */
	long           UhrZeitBestNachUpd;           /* Bestand nach Update Aenderzeit */
	long           DatumVerfall;                 /* Datum Verfall */
	long           MengeGutschrift;              /* Menge Gutschrift */
	short          LagerBereichNr;               /* Lagerbereichsnummer */
	char           StationNr[2+1];               /* Lager Stationsnummer */
	char           LagerFachNr[10+1];            /* Lager Fachnummer */
	char           Zuzahlung;                    /* Kz Zuzahlung */
	char           Bemerkungen[240+1];           /* Bemerkungen */
	long           ETArtKlasse1;                 /* ETab Artikel Klasse 1 */
	long           ETArtSchalter1;               /* ETab Artikel Schalter 1 */
	long           ETArtSchalter2;               /* ETab Artikel Schalter 2 */
	long           ETArtSchalter3;               /* ETab Artikel Schalter 3 */
	long           ContSplitMenge;               /* Container Splitmenge */
	short          SendeStatus;                  /* ›bertragungsstatus (VSE) */
	char           Hinweis[2+1];                 /* Artikel bezogerner Hinweis */
	long           WannenNr;                     /* Wannennummer*/
	long           MengeVorausBezug;             /* Menge Vorausbezug */
	long           BatchPosNr;                   /* Batch Position Number*/
	char           BewegungsArt;                 /* Artikelkonto bewegungsart*/
	double         SalesTaxRate ;                /* MWST Satz*/
	char           KdAuftragBestellNr[9+1];      /* KundenBestellNummer*/
	char           CodeBlocage;                  /* code blocage*/
	double         PreisEKApoFree;               /* Preis EK Apotheke freier Preis*/
	long           LinkPosNr;                    /* Linkposistion Number*/
	short          Preis_Typ;                    /* Preistype(BG) */
	long           Article_No_Pack;              /* Steller Pseudoartikelnummer*/
	double         PreisFaktur;                  /* Preis Faktur */
	short          MaxTargetNo;                  /* Max Zahlungsziel*/
	short          ContainerLevel;               /* Lagerebene f’r Container*/
	double         RefundValue;                  /* Refund Value */
	short          Promotion_No;                 /* Promotion No*/
	short          PromoTyp;                     /* Promotion Type*/
	short          Code_Type;                    /* ArticleCode  Code_Type*/
	char           Article_Code[25+1];           /* ArticleCode */
	short          ProblemState;                 /* ProblemState 0 = nothing, 1 = RabateNoQty, 2 = RabateArt. Not Av*/
	long           ETPosSchalter7;               /* ETab Position Schalter 7 */
	long           ETPosSchalter8;               /* ETab Position Schalter 8 */
	short          SubGeraetTyp;                 /* SubGeraetTyp 0 = phonetik,1 = edi,2 = salesweb,3 = propo*/
	char           KzPriso;		                 /* Kz Privatsortiment */
	short          BusinessTypeNo;               /* Business TypeNo Ivrylab Cap/Plattform/pharmacy plus */
	char           TourIdIBT[6+1];               /* Verbundtour */
	short          IBTTourWeekDay;               /* Verbundtour Wochentag */
	short          IBTType;                      /* Verbundtype(TagNacht/Normal) */
	short          IsDayIBT;                     /* TagVerbund */
	short          IBTTypeID;                    /* N-Level-Verbundtyp */
	long           PurchaseRelevantQty;          /* Abverkaufswirksame Menge für Einkauf */
	long           MengeBestellt_Org;            /* */
	long           MengeBestelltNatra;           /* */
	short          NatraCategory;                /* */
	char           NatraPharmacyGroup[3 + 1];
	double         PreisEKAgp;                   /* Preis EK AGP */
};


/*****************************************************************************/
/*  Artikel Lagerorte                                                        */
/*                                                                           */
/*****************************************************************************/

struct tARTIKELLAGERORT
{
	short          FilialNr;                     /* Filialnummer */
	long           ArtikelNr;                    /* Artikelnummer */
	short          LagerBereichNr;               /* Lagerbereichsnummer */
	char           StationNr[2+1];               /* Lager Stationsnummer */
	char           LagerFachNr[10+1];            /* Lager Fachnummer */
	long           DatumVerfall;                 /* Datum Verfall */
	long           Bestand;                      /* Bestand */
	char           VerbundArtikel;               /* Verbund Artikel */
};


/*****************************************************************************/
/*  Kundenauftrag Rueckstand                                                 */
/*                                                                           */
/*****************************************************************************/

struct tNACHLIEFERPOS
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	long           Datum;                        /* Datum */
	short          PosTyp;                       /* Position Typ */
	long           IDFNr;                        /* Kundennummer IDF */
	long           ArtikelNr;                    /* Artikelnummer */
	long           Menge;                        /* Menge */
	short          FilialNr1;                    /* Filialnummer Partner 1 */
	short          FilialNr2;                    /* Filialnummer Partner 2 */
	short          FilialNr3;                    /* Filialnummer Partner 3 */
	long           Status;                       /* Status Nachlieferpos */
	long           UrsprungAuftragNr;            /* Ursprungs Auftragnummer */
	long           UrsprungPosNr;                /* Ursprungs Positionsnummer */
	long           KundenNr;                     /* Kunden Nummer VZ */
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           Erfasst;                      /* Erfasst*/
	char           KdAuftragArt[2+1];            /* KdAuftragart*/
	char           PosArt[2+1];                  /* KdAuftragart*/
	double         PreisEKApoNetto;              /* Preis EK Apotheke Nettoaktion */
	long           BatchAuftragNr;               /* Batchorder number from VSE Batchorder */
	long           BatchPosNr;                   /* Batchpos number from VSE Batchorder */
	long           MengeNatra;                   /* MengeNatra aus Org. Position*/
	char           Bemerkungen[240+1];           /* Bemerkungen */
	double         PreisEKApo;                   /* Preis EK Apotheke */
	double         PreisVKApo;                   /* Preis VK Apotheke */
	double         PreisAGP;                     /* Spezial Preis Schweiz*/
	long           DatumValuta;                  /* Datum Valuta */
	char           KoArt;                        /* Kommissionierungsart */
	char           BuchArt;                      /* Buchungsart */
	short          Code_Type;                    /* ArticleCode  Code_Type*/
	char           Article_Code[25+1];           /* ArticleCode */
	double         DiscountValuePct;             /* DiscountValue Percent*/
	long           MengeBestellt;                /* Menge bestellt */
	short          Preis_Typ;                    /* Preistype */

};

/*****************************************************************************/
/*  Artikel Basispreise                                                      */
/*  Artikel Basispreistabelle                                                */
/*****************************************************************************/

struct tARTIKELPREIS
{
	long           ArtikelNr;                    /* Artikelnummer */
	long           DatumGueltigAb;               /* Datum gueltig ab */
	long           DatumGueltigBis;              /* Datum gueltig bis */
	double         PreisEKApo;                   /* Preis EK Apotheke */
	double         PreisEKGrosso;                /* Preis EK Grosso */
	double         PreisEKGrossoNA;              /* Preis EK Grosso Nettoaktion */
	double         PreisVKApo;                   /* Preis VK Apotheke */
	double         RabattFest;                   /* Rabatt Fest in Prozent */
	double         RabattFestDM;                 /* Rabatt Fest in DM */
	double         PreisFest;                    /* Preis Fest */
	double         PreisProzent;                 /* Preis in Prozent */
	double         PreisAGP;                     /* Spezial Preis Schweiz*/
	short          Preis_Typ;                    /* Preistyp */
	double         MaxAvp;                       /* Preis Max Avp */
};


/*****************************************************************************/
/*  Artikel Mengenpreise                                                     */
/*  Artikel Mengenpreise f’r Nettoaktionen                                   */
/*****************************************************************************/

//struct tARTIKELMGPREIS
//{
//	long           ArtikelNr;                    /* Artikelnummer */
//	long           DatumGueltigAb;               /* Datum gueltig ab */
//	long           DatumGueltigBis;              /* Datum gueltig bis */
//	long           KondGruppenNr;                /* Kond Gruppen Nummer */
//	long           Menge;                        /* Menge */
//	double         PreisEKApoNetto;              /* Preis EK Apotheke Nettoaktion */
//	short          VertriebszentrumNr;           /* Vertriebszentrum */
//};


/*****************************************************************************/
/*  Artikel Naturalrabatte                                                   */
/*  Artikel Naturalrabattstaffeln                                            */
/*****************************************************************************/

//struct tARTIKELNATRA
//{
//	long           NatraStaffelNr;               /* Natra Staffel Nummer */
//	short          RabattSchluessel;             /* Rabatt Schluessel */
//	long           DatumGueltigAb;               /* Datum gueltig ab */
//	long           DatumGueltigBis;              /* Datum gueltig bis */
//	long           KondGruppenNr;                /* Kond Gruppen Nummer */
//	long           MengeNatraBasis;              /* Menge Naturalrabatt Basis */
//	long           MengeNatra;                   /* Menge Naturalrabatt */
//	short          VertriebszentrumNr;           /* Vertriebszentrum */
//	char           EinKaufsGruppe[3+1];          /* Einkaufsgruppe*/
//	char           NrIntern;                     /* Natra intern*/
//};


/*****************************************************************************/
/*  Kundenauftrag Ereignis                                                   */
/*  Protokoll der Auftragsereignisse                                         */
/*****************************************************************************/

struct tKDAUFTRAGEREIGNIS
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           Datum;                        /* Datum */
	long           Zeit;                         /* Zeit */
	short          EreignisArt;                  /* Ereignisart */
	long           PersonalNr;                   /* Personalnummer */
	char           GeraetName[8+1];              /* Geraet Name */
	short          FilialNr;                     /* Filialnummer User*/
	short          EventCode;                    /* Event Code for table eventreasons*/
};


/*****************************************************************************/
/*  Artikel Alternativen                                                     */
/*                                                                           */
/*****************************************************************************/

struct tARTIKELALTERN
{
	long           ArtikelNr;                    /* Artikelnummer */
	long           ArtikelAlternNr;              /* Artikelnummer Alternativartikel */
	char           Bemerkungen[240+1];           /* Bemerkungen */
	short          FilialNr;                     /* Filialnummer */
};


/*****************************************************************************/
/*  Tour                                                                     */
/*  Touren Tabelle                                                           */
/*****************************************************************************/

struct tTOUR
{
	long           DatumKommi;                   /* Datum Kommi */
	char           TourId[6+1];                  /* Tour Identifikation */
	long           ZeitKoEnde;                   /* Zeit Kommissionierungsende */
	long           DatumVersand;                 /* Datum Versand */
	long           ZeitVersand;                  /* Zeit Versand */
	short          BahnhofVersand;               /* Versandort */
	char           TourStat;                     /* Tour Status */
	long           LagRechTour;                  /* Tour Identifikation Lagerrechner */
	short          FilialNr;                     /* Filialnummer */
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
	char           TourInaktiv;                  /* Tour ist nicht aktiv*/
	short          ErsatzFilialNr;               /* Tour (inaktiv) wird in Ersatzfiliale ger’stet*/
	short          KippZeit;                     /* Tour Kippzeit*/
	short          CheckTimeToTour;              /* CheckTimeToTour*/
	short          ScheckOrder;                  /* ScheckOrder*/
	short          KarenzZeit;                   /* KarenzZeit*/
};


/*****************************************************************************/
/*  Filiale                                                                  */
/*                                                                           */
/*****************************************************************************/

struct tFILIALE
{
	short          FilialNr;                     /* Filialnummer */
	char           Bezeichnung[30+1];            /* Bezeichnung */
	char           Strasse[30+1];                /* Strasse (30 Zeichen) */
	char           Postleitzahl[7+1];            /* Postleitzahl */
	char           Ort[30+1];                    /* Ort */
	char           Vorwahl[10+1];                /* Vorwahl */
	char           TelNrOVw[20+1];               /* Telefonnummer ohne Vorwahl */
	char           FaxNrOVw[20+1];               /* Faxnummer ohne Vorwahl */
	long           BGANr;                        /* BGA Nummer */
	long           BGANr_EK;                     /* BGA Nummer Einkauf */
};


/*****************************************************************************/
/*  Kundenauftrag Art                                                        */
/*  Tabelle der Kundenauftragsarten                                          */
/*****************************************************************************/

struct tKDAUFTRAGART
{
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
	long           AuftragArtTyp;                /* Auftrag Art Typ */
	char           Bezeichnung[30+1];            /* Bezeichnung */
	long           ValutaMonate;                 /* Valuta Monate */
	unsigned char  SKdAuftragartNatra;           /* SKd Auftragart Natra rechnen */
	unsigned char  SKdAuftragartNetto;           /* SKd Auftragart Netto rechnen */
	unsigned char  SKdAuftragartBANR;            /* SKd Auftragart BANR rechnen */
	unsigned char  SKdAuftragartMonat;           /* SKd Auftragart Monatrab rechnen */
	unsigned char  SkdAuftragVerbund;            /* Skd Auftrag Verbund */
	unsigned char  SKdAuftragartValS;            /* SKd Auftragart Valutasperre */
	unsigned char  SGlobal;                      /* Schalter Global */
	unsigned char  SBildschirm;                  /* Schalter Bildschirm */
	unsigned char  SDafue;                       /* Schalter Dafue */
	unsigned char  SStandard;                    /* Schalter Standard */
	short          BranchNo;                     /* Branch number*/
	unsigned char  DisinkindEnterable;           /* Schalter Rabatt h„ndisch eingeben*/
	unsigned char  SDiscountable;                /* Schalter rabattf„hig*/
	unsigned char  SMustSubOrder;                /* Schalter Dutyflag SubOrderType*/
	unsigned char  SFreePrice;                   /* Schalter ordertyp for Freeprices*/
	unsigned char  SOrderCons;                   /* Schalter ordertyp for Consolidation*/
	unsigned char  SRestDel;                     /* Schalter ordertyp for Restdelivery*/
	unsigned char  SNoQuota;                     /* Schalter ordertyp no Quota*/
	unsigned char  SNoPartQty;                   /* Schalter ordertyp no partial Quantity*/
	unsigned char  SDeferOrder;                  /* Schalter ordertyp defer order general*/
	unsigned char  SServiceOrder;                /* Schalter ordertyp service*/
	unsigned char  SNoDD;                        /* Schalter ordertyp no delayed delivery*/
	unsigned char  SOnlyEH;                      /* Schalter ordertyp nur Einzelhandel(BG)*/
	short          SNoPromotions;                /* SNoPromotions(BG)*/
	short          SDefaultKennung;              /* MSV3 default Kennung*/
	short          SAlwaysRestDel;               /* Always restdelivery, ignore Customers defenition*/
	short		   Stockreservation;             /* Stockreservation*/

};


/*****************************************************************************/
/*  Kunde Auftragarten                                                       */
/*  Moegliche Auftragsarten pro Kunde                                        */
/*****************************************************************************/

struct tAUFTRAGARTKD
{
	long           IDFNr;                        /* Kundennummer IDF */
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
	long           ValutaMonate;                 /* Valuta Monate */
	unsigned char  SKdAuftragartNatra;           /* SKd Auftragart Natra rechnen */
	unsigned char  SKdAuftragartNetto;           /* SKd Auftragart Netto rechnen */
	unsigned char  SKdAuftragartBANR;            /* SKd Auftragart BANR rechnen */
	unsigned char  SKdAuftragartMonat;           /* SKd Auftragart Monatrab rechnen */
	unsigned char  SkdAuftragVerbund;            /* Skd Auftrag Verbund */
	unsigned char  SKdAuftragartValS;            /* SKd Auftragart Valutasperre */
	short          ValutaMonAuto;                /* Valuta Monate Automatisch */
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           KundenNr;                     /* Kunden Nummer VZ */
	unsigned char  SKdAuftragartDD;              /* SKd Auftragart Delayed Delivery */
	short          OrderLabelCount;              /* OrderLabelCount */
	short          SWMSV3;                       /* msv3 Schalter*/
	short          SWPartDel;                    /* Teilmengen Schalter*/
	char           OrderIdentificatio[10+1];     /* Auftragidentification */
};


/*****************************************************************************/
/*  Tour Plan Arbeitstag                                                     */
/*  Geplante Touren pro Kunde-Arbeitstag                                     */
/*****************************************************************************/

struct tTOURPLANTAG
{
	long           IDFNr;                        /* Kundennummer IDF */
	long           DatumKommi;                   /* Datum Kommi */
	char           TourId[6+1];                  /* Tour Identifikation */
	long           ReihenFolgeNr;                /* Reihenfolgenummer */
	long           FahrtZeit;                    /* Fahrtzeit */
	char           Bemerkungen[240+1];           /* Bemerkungen */
	unsigned char  KZUpd;                        /* SKd Update */
	unsigned char  IstVerbundTour;               /* Schalter Ist Verbundtour */
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           KundenNr;                     /* Kunden Nummer VZ */
	char           KoArt;                        /* Kommissionierungsart */
	unsigned char  TourInaktiv;                  /* Kennzeichen  Tour ist nicht aktiv*/
	short          KippZeit;                     /* Kunden Touren Kippzeit*/
	unsigned char  KZAutoZuord;                  /* Kennzeichen Tour automatisch zuordnen*/
	unsigned char  IstVaTour;                    /* Schalter Ist VersandApoTour */
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
	short          DeliverBranchNo;              /* Lieferfiliale der Shuttle Touren(FR new suivra)*/
	char           SencloserDone;                /* Beifueger getaetigt(CH XML Beifueger) */
	short          OrderLabelCount;              /* OrderLabelCount*/
};


/*****************************************************************************/
/*  Kunde Betriebszeiten                                                     */
/*  Tabelle der Betriebsendezeiten                                           */
/*****************************************************************************/

struct tKDBETRIEBSENDE
{
	long           IDFNr;                        /* Kundennummer IDF */
	char           TagesTyp[6+1];                /* Tagestyp */
	long           ZeitBeginAM;                  /* Zeit Betriebsanfang morgens */
	long           ZeitEndeAM;                   /* Zeit Betriebsende morgens */
	long           ZeitBeginPM;                  /* Zeit Betriebsanfang abends */
	long           ZeitEndePM;                   /* Zeit Betriebsende abends */
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           KundenNr;                     /* Kunden Nummer VZ */
	short          WeekDay;                      /* DayOfWeek*/
};


/*****************************************************************************/
/*  Kunde Konditionen                                                        */
/*                                                                           */
/*****************************************************************************/

struct tKUNDEKONDI
{
	long           IDFNr;                        /* Kundennummer IDF */
	double         BuendelRundungProz;           /* Buendel Rundung Prozent */
	long           MengeNatraBasis;              /* Menge Naturalrabatt Basis */
	long           MengeNatra;                   /* Menge Naturalrabatt */
	unsigned char  SKdNatraRabatt04;             /* SKd Natra Rabatt04 */
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           KundenNr;                     /* Kunden Nummer VZ */
	short          TagAutoValuta;                /* Automatischer Valuta Tag */
	short          ValutaTageMax;                /* Automatischer  max Tage */
};


/*****************************************************************************/
/*  Kunde Kennzeichen                                                        */
/*  Kunde Kennzeichen                                                        */
/*****************************************************************************/

struct tKUNDESCHALTER
{
	long           IDFNr;                        /* Kundennummer IDF */
	unsigned char  SKdWerbeFachBelegt;           /* SKd Werbefach belegt */
	unsigned char  SKdKdFachAktiv;               /* SKd Kundenfach aktiv */
	unsigned char  SKdNatraRestAkzept;           /* SKd Natra Restakzeptanz */
	unsigned char  SKdNettoAktion;               /* SKd Nettoaktion */
	unsigned char  SKdEtikettService;            /* SKd Etiketten Service */
	unsigned char  SKdDefektLiefern;             /* SKd Defekte nachliefern */
	unsigned char  SKdDefektAbsagen;             /* SKd Defekte absagen */
	unsigned char  SKdSammlDafue;                /* SKd Datensammlung aus Dafue */
	unsigned char  SKdApoEKStatisitik;           /* SKd Apo EK Statisitik */
	unsigned char  SKdAutoErhoehgNNNR;           /* SKd Autom Mengenerhoehung NN/NR */
	unsigned char  SKdDefektMeldgAusw;           /* SKd Defektmeldung Ausweichart. */
	unsigned char  SKdKontrKoBelege;             /* SKd Druck Kontroll Kommibelege */
	unsigned char  SKdAuftragZusammen;           /* SKd Auftragzusammenfuehrung */
	unsigned char  SKdMWSTHalb;                  /* SKd MWST Satz halb */
	unsigned char  SKdStadtKunde;                /* SKd Stadtkunde */
	unsigned char  SKdValutaSperre;              /* SKd Valutasperre */
	unsigned char  SKdSchwerPunkt1;              /* SKd Schwerpunkt 1 */
	unsigned char  SKdSchwerPunkt2;              /* SKd Schwerpunkt 2 */
	unsigned char  SKdSchwerPunkt3;              /* SKd Schwerpunkt 3 */
	unsigned char  SKdSchwerPunkt4;              /* SKd Schwerpunkt 4 */
	unsigned char  SKdSchwerPunkt5;              /* SKd Schwerpunkt 5 */
	unsigned char  SKdVerbundGanz;               /* SKd Verbundservice ganztags */
	unsigned char  SKdAbschlagrechn;             /* SKd Abschlag rechnen */
	unsigned char  SKdKdkritisch;                /* SKd Kunde kritisch */
	unsigned char  SKdEilSperre;                 /* SKd EilSperre */
	unsigned char  SKdAbsagen;                   /* SKd Absagen */
	unsigned char  SKdVIPKunde;                  /* SKd VIP Kunde */
	unsigned char  SKdAuftragSplit;              /* SKd Auftragsplit */
	unsigned char  SKdMussKopf;                  /* SKd MussKopf */
	unsigned char  SKdSepAuft;                   /* SKd SepAuft */
	unsigned char  SKdAuftragZurueck;            /* Skd Auftrag Zurueck Stellen */
	unsigned char  SKdBestZeit;                  /* Skd Bestell Zeit */
	unsigned char  SKdWirdBearb;                 /* Skd Wird Bearbeitet */
	unsigned char  KZUpd;                        /* Update flag*/
	unsigned char  SKdReimport;                  /* SKd Reimport */
	unsigned char  SKdWareNachliefern;           /* SKd Ware Nachliefern */
	unsigned char  SKdPinKunde;                  /* SKd Pin Kunde*/
	unsigned char  SKdADGKunde;                  /* SKd ADG Kunde*/
	unsigned char  SKdDruckBetaPharm;            /* SKd Druck Betapharm*/
	unsigned char  SKdFax400;                    /* SKd Fax400*/
	unsigned char  SKdKundeAEGesperrt;           /* SKd Kunde fuer AE gesperrt */
	unsigned char  SKdDruckEtikett;              /* SKd Druck Etikett */
	unsigned char  SKdDruckTierArznei;           /* Skd Druck Tierarznei*/
	unsigned char  SKdDruckKaufStrukt;           /* Skd Druck Kaufstrukt*/
	unsigned char  SKdKaufStruktArt;             /* Skd Druck KaufStruktArt*/
	unsigned char  SKdMonatsRabatt;              /* Skd Monats Rabatt*/
	unsigned char  SKdDruckUmsatz;               /* Skd Druck Umsatzt*/
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           KundenNr;                     /* Kunden Nummer VZ */
	long           TM_Date;                      /* Date */
	long           TM_Time;                      /* Time */
	long           LoginId;                      /* Login*/
	unsigned char  ChangeId;                     /* ChangeId*/
	unsigned char  SKdAnrufGenerell;             /* Skd Anruf Generell*/
	unsigned char  SKdBlickPunktAbo;             /* Skd Blick Punkt Abo*/
	unsigned char  SKdBuecher;                   /* Skd Buecher*/
	unsigned char  SKdVertriebBindung;           /* Skd Vertriebbindung*/
	unsigned char  SKdPool;                      /* Skd Pool*/
	unsigned char  SKdBouhon;                    /* Skd Bouhon*/
	unsigned char  SKdRoche;                     /* Skd Roche*/
	unsigned char  SKdVichy;                     /* Skd Vichy*/
	unsigned char  SkdVBFilialeMeld;             /* Skd VBFilialeMeld */
	unsigned char  SKdRRAbSchluss;               /* SKd Rueckruf Abschluss */
	unsigned char  SKdAbSchlussEil;              /* SKd Eilabschluss */
	unsigned char  SKdTrennAlphaText;            /* SKd Trenn bei Alphatext */
	unsigned char  SKdRR0800;                    /* SKd RR 0800 */
	unsigned char  SKdTrennAlphaURR;             /* SKd Trenn Alpha URR */
	unsigned char  SKdOriginalMeld;              /* SKd meld original pzn bei AWA */
	unsigned char  SKdMidas;                     /* SKd Midas*/
	unsigned char  SKdMehrfachBestell;           /* SKd mehrfach Bestellung Schweiz*/
	unsigned char  SKdOmgKunde;                  /* SKd Omg Kunde (Swiss special)*/
	unsigned char  SKdCharge;                    /* SKd Charge*/
	unsigned char  SKdKeinNl;                    /* SKd kein nl wenn vom Herst.nicht lieferbarf*/
	unsigned char  SKdTrennDefekt;               /* SKd Trenn Defekte*/
	unsigned char  SKdVersandApo;                /* SKd Versnad Apotheke*/
	unsigned char  SKdNoCloseDefVB;              /* SKd No Close bei Defekte und Verbund*/
	unsigned char  SKdParternariat;              /* SKd Parternariat*/
	unsigned char  SKdBaAuftrag;                 /* SKd Beschaffungsauftragskunde*/
	unsigned char  SKdCheckDouble;               /* SKd Check Double Order*/
	unsigned char  SKdNoSub;                     /* SKd No Substitution*/
	unsigned char  SKdWatchOrder;                /* SKd watch order*/
	unsigned char  SKdRetailPermit;              /* SKd Retail Permit*/
	unsigned char  SKdHalfMargin;                /* SKd Half Margin*/
	unsigned char  SKdDiscountExcept;            /* SKd DiscountExcept*/
	unsigned char  SKdListe5;                    /* SKd Liste 5 BG*/
	unsigned char  SKdInvoiceDisc;               /* SKd Invoice per Disc*/
	unsigned char  SKdInvoiceEmail;              /* SKd Invoice per Email*/
	unsigned char  SKdNoExpiryInfo ;             /* SKD NOEXPIRYINFO */
	unsigned char  MedProd_ABG_Verord;           /* MEDPROD_ABG_VERORD*/
	unsigned char  SKdNoShortReport;             /* No Short report*/
	unsigned char  SKdGiveProdQuota;             /* give product quota*/
	short          SKdAvoidDefectClearing;       /* avoid defect clearing*/
	short          SMSV3DayIBTInfo;				 /* avoid defect clearing*/
	short 		   SKdPseudoIDFNrUW;
	short 		   MSV3NoOrderCons;				 /* no order consolidation between main order time and end of order period */
	short 		   NoOrderConsAfterMot;			 /* no order consolidation after main order time */
	short          SKdMailInvoice;
	short          SKdMailBatchChangeAdvice;
	short          SKdFaxInvoice;
	short          SKdFaxBatchChangeAdvice;
    short          SKdFMD;
	unsigned char  SKdRXA;
};


/*****************************************************************************/
/*  Auftragart Kombination                                                   */
/*  Verarbeitungskombin.fuer Auftragarten                                    */
/*****************************************************************************/

struct tAUFTRAGARTKOMB
{
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
	char           BuchArt;                      /* Buchungsart */
	char           KoArt;                        /* Kommissionierungsart */
	char           KZStandard;                   /* Kennzeichen Standard */
	char           TourId[6+1];                  /* Tour Identifikation */
	short          VertriebszentrumNr;           /* Branch number*/
	short 		   CalcExpressDeliveryCharge;	 /* Eilbotengebühr rechnen */
};


/*****************************************************************************/
/*  Buchungsarten                                                            */
/*  Moegliche Buchungsarten                                                  */
/*****************************************************************************/

struct tBUCHUNGSART
{
	char           BuchArt;                      /* Buchungsart */
	long           BuchMethode;                  /* Buchungsmethode */
	char           Bezeichnung[30+1];            /* Bezeichnung */
	short          BranchNo;                     /* Branch number*/
};


/*****************************************************************************/
/*  Kommissionierung Arten                                                   */
/*  Kommissionierungsarten                                                   */
/*****************************************************************************/

struct tKOMMIARTEN
{
	char           KoArt;                        /* Kommissionierungsart */
	long           KoMethode;                    /* Kommissionierungsmethode */
	char           Bezeichnung[30+1];            /* Bezeichnung */
	short          BranchNo;                     /* Branch number*/
};

/*****************************************************************************/
/*  Kunde Kondition Gruppe                                                   */
/*                                                                           */
/*****************************************************************************/

//struct tKDKONDITIONGRUPPE
//{
//	long           IDFNr;                        /* Kundennummer IDF */
//	long           KondGruppenNr;                /* Kond Gruppen Nummer */
//	short          VertriebszentrumNr;           /* Vertriebszentrum */
//	long           KundenNr;                     /* Kunden Nummer VZ */
//};


/*****************************************************************************/
/*  Parameter Auftragbearbeitung                                             */
/*                                                                           */
/*****************************************************************************/

struct tPARAAUFTRAGBEARB
{
	short 			FilialNr;						/* Filialnummer */
	char   			KdAuftragArt[2+1];				/* Kunde Auftrag Art */
	char 			BuchArt;						/* Buchungsart */
	char 			KoArt;							/* Kommissionierungsart */
	long 			DurchlaufNormal;				/* Lagerdurchlaufzeit normal */
	long 			DurchlaufEilbote;				/* Lagerdurchlaufzeit Eilbote */
	long 			KarenzTourSchein;				/* Karenzzeit Tourenschein */
	unsigned char	SSammelKommi;					/* Schalter Sammelkommissionierung */
	unsigned char	SVorfaktura;					/* Schalter Vorfaktura */
	unsigned char	SBTMSchein;						/* Schalter BTMSchein */
	unsigned char	SWerbung;						/* Schalter Werbung */
	long 			PZNKuehlBox1;					/* PZN Kuehlbox 1 */
	long 			PZNKuehlBox2;					/* PZN Kuehlbox 2 */
	long 			PZNBTMSchein;					/* PZN BTMSchein */
	long 			PZNWerbefach;					/* PZN Werbefach */
	long 			PZNWerbefach2;					/* PZN Werbefach 2 */
	long 			AnzArtAlphaWSort;				/* Anzahl Artikel Alpha Wannensort */
	long 			MaxPosMenge;					/* Maximale Menge einer Position */
	char   			TourWochentag[2+1];				/* Tour Wochentag */
	long 			TourVerspaetung;				/* Tour Verspaetung */
	char   			BahnhofDoppelkontr[2+1];		/* Bahnhof fuer Doppelkontrolle */
	unsigned char	SErweiterteTourAnz;				/* Schalter Erweiterte Touranzeige */
	unsigned char	SAuftragZusammen;				/* Schalter Auftragzusammenfuehrung */
	long 			AuftragZusammenMMM;				/* Auftragzusammenfuehrung Minuten */
	long 			AuftragZusammenHHH;				/* Auftragzusammenfuehrung Stunden */
	unsigned char	SSepWannenEilbote;				/* Schalter Separate Wannen Eilbote */
	short 			SepWannenTyp;					/* Separate Wannen Typ */
	long 			SepWannenRestzeit;				/* Separate Wannen Restzeit */
	unsigned char	SKdAuftragSplit;				/* SKd Auftragsplit */
	long 			TourenKippZeit;					/* Tour Kippzeit */
	unsigned char	AutomNachLief;					/* Schalter Automatisch Nachliefern */
	unsigned char	DafueEntsDIorNL;				/* Schalter Entscheidung DI oder NL */
	long 			DefwertKeinAbschl;				/* Defektwert kein Abschluss */
	long 			MaxPosVerbund;					/* Maximale Anz. Verbundpositionen */
	unsigned char	SKuehlU8Grad;					/* Schalter Kuehlbox unter 8 Grad */
	unsigned char	SRRSa02;						/* Schalter Rueckruf Sa02 */
	unsigned char	STrennBei10ner;					/* Schalter Auftragsplit bei Zehner */
	unsigned char	SText99Nak;						/* Schalter Kopftext 99 */
	unsigned char	SBearb06;						/* Schalter Bearbeitung Sa06 */
	unsigned char	BTM_Extra;						/* Schalter BTM Extra */
	long 			Time_No_BTM;					/* Zeit Kein BTM */
	unsigned char	SVerbundDirect;					/* Schalter Verbund Direct */
	long 			PZNZytostatika;					/* PZN Zytostatika */
	unsigned char	DefektDispo;					/* Schalter Dispo bei Defekt*/
	unsigned char	SVorausBezg;					/* Schalter Vorausbezug(Swiss Special)*/
	unsigned char	SBTMKommi;						/* Schalter Kommi f’r BTM artikel*/
	unsigned char	SNOToAK;						/* Schalter Auftragart NO nach AK*/
	short 			MaxPosAuftrag;					/* Maxmimal Anzahl Positionen pro Auftrag*/
	long 			AnzPosZu;						/* Anz. Pos. ab wann ein Auftrag zur’ckgestellt wird*/
	long 			MaxPosEil;						/* Anz. Pos. ab wann Eilbote nicht mehr erlaubz ist*/
	unsigned char	SNewDiscount;					/* Schalter neue Rabatttabelle discount*/
	short 			NoRoutingMM;					/* Norouting Minuten*/
	unsigned char	SBatchTeilMenge;				/* Teilmenengen inm Batch buchen 1 = ja, 0 = nein*/
	unsigned char	SVERunden;						/* Verpackungseinheit runden     1 = ja, 0 = nein*/
	long 			PlusZeitBTM;					/* Tourenkippzeit f’r BTM*/
	long 			ETArtNoNatra;					/* Artklasse wo kein Natra erlaubt ist*/
	long 			MindestBestellWert;				/* Mindest Auftrags Bestellwert*/
	long 			PZNAddOnCharge;					/* Artikelnummer Zusatzgebuehr*/
	short 			ReservePeriod;					/* Seserveduration in Minutes*/
	short 			ReserveMaxQty;					/* Max Value for reservation(ArticleUnfo XML*/
	double  		RangePricePct;					/* Rangepct for freeprice input*/
	char 			SNarcTrans;						/* Narctransaction transfer using*/
	char 			SPosSplit;						/* Position Split Container*/
	char 			SDayNight;						/* Schalter Tag/Nacht*/
	short 			TourCheckTime;					/* Tour Check Time*/
	long 			PZNFranko;						/* Artikelnummer Frankozeile*/
	long 			PZNFreightage;					/* Artikelnummer Frachtkosten*/
	short 			AnzAufClose;					/* Anzahl Auftr„ge ab wann close*/
	short 			AnzPosClose;					/* Anzahl Positione ab wann close*/
	char 			SNoCangeVal;					/* Schalter No Change Valuta*/
	char 			SKumPos;						/* Schalter Kummulieren Pos gleicher PZN*/
	char 			SAnzPrintCode;					/* Schalter Anzeigen Pront Code (Countrycode)*/
	char 			SKLClose;						/* Schalter ??*/
	char 			SOrderCriteria;					/* Schalter Bestellzuschl„ge*/
	long 			MaxLineValue;					/* Max Line Value*/
	short 			WakeTime1;						/* Waketime1 vor Tourabfahrt*/
	short 			WakeTime2;						/* Waketime2 vor Tourabfahrt*/
	short 			ContainerLevel;					/* Lagerebene f’r Container*/
	char 			SIbtCstOrg;						/* Schalter Kunde Verbund original*/
	double  		MaxSurCharge;					/* Max Zuschlag AVP*/
	char 			SDefOrderDF;					/* defekt Auftrag 0=ZU,1=DF*/
	long 			EncloserTiltTime;				/* Encloser Kipp Zeit in MM*/
	char 			SCrema;							/* Kredit Management*/
	short 			MaxQtyRequest;					/*  MaxQtyRequest*/
	short 			CheckTimeToClose;				/* CheckTimeToClose*/
	short 			MaxDPODays;						/* MaxDPODays*/
	short 			DelayedDays;					/* DelayedDays(FR PFR) Anzahl Tage der Verzoegerung*/
	short 			SDiscountLocal;					/* Umstellung Tabelle Discount ohne BranchNo*/
	short 			SDeferOrders;					/* Schalter mit oder ohne delayeddays(doppelt gemoppelt)*/
	short 			SDayNightMerge;					/* Schalter mit oder ohne daynightmerge*/
	short 			SCloseIBTAtonce;				/* Schalter Verbundposition sofort verarbeiten*/
	short 			ConsolidationDelay;				/* Zeit in Sekunden fuer aaordclose Abschlusslogik*/
	short 			AutoIBTSubst;					/* Ausweichartikel auch im Vebrund buchen(FR)*/
	short 			SWNewCallback;					/* new callback*/
	short 			SRangeCalcBase;					/* range calculation base(0 = MengeBestaetigt, 1 = MengeBestellt*/
	short 			SDiscountCalcBase;				/* Discount calculation base(0 = MengeBestaetigt, 1 = MengeBestellt*/
	short 			MSV3DeliveryTimeFrame;			/* MSV3 Delivery Time Frame*/
	short 			SendMSV3DeliveryTime;			/* send MSV3 Delivery Time*/
	short 			MSV3TourOption;					/* MSV3 Tour Option*/
	short 			UseTourManager;					/* use new tour manager*/
	short 			TourWeekDay;					/* if tours have been loaded for a specific day, the weekday is in this field. if the tours were loaded normally, it contains -1 */
	short 			OrderPeriodTourAssignment;		/* defines wether there is a fixed binding between orderperiodtime and tourid */
	short 			MSV3OrderPeriodClosure;			/* MSV3: close orders after end of the order period and after the main order time */
	short 			MSV3ClosureTimeAdjustment;		/* MSV3: minutes added on order period endtime and main order time for automatic closure */
	short 			UseIBTCustomerForDeliveryTime;	/* TourManager: use IBT customer for delivery time determination */
	short 			UseNewDiscountCalc;             /* Neue Rabattlogik */
	short 			NlevelIBT;                      /* nlevelIBT */
	short 			IBTQtyAvailabilityPercentage;   /* IBTQtyAvailabilityPercentage*/
	short 			ReverseSubstitutionDays;        /* ReverseSubstitutionDays*/
	short			SStopCrema;
	short			TimeCancelCremaOrder;
	short			SNoDispoClosed;
	short			IBTNormalTourActive;
	short			SCloseRestDeliveryAtOnce;
	short			SCloseDispoAtOnce;
	short			SCool20;
	short			DisableGT24ToursForHoliday;
	short			SNewF6;
	short			SDispoImport;
	short			DaysHandoverToDelivery;
	short			UseLatestIbtTour;
};


/*****************************************************************************/
/*  Kunden Gruppe                                                            */
/*  KundenGuppe Stammsatz                                                    */
/*****************************************************************************/

struct tKUNDENGRUPPE
{
	char           KdGruppe[2+1];                /* Kundengruppe */
	char           Bezeichnung[30+1];            /* Bezeichnung */
	unsigned char  SArtGiftKlasse1;              /* SArt GiftKlasse1 */
	unsigned char  SArtGiftKlasse2;              /* SArt GiftKlasse2 */
	unsigned char  SArtGiftKlasse3;              /* SArt GiftKlasse3 */
	unsigned char  SArtRezeptPfl;                /* SArt RezeptPflichtig */
	unsigned char  SArtApothekenPfl;             /* SArt ApothekenPflichtig */
	unsigned char  SArtTaxPfl;                   /* SArt TaxPflichtig */
	unsigned char  SArtOpiat;                    /* SArt Opiat */
	unsigned char  SArtTierArznei;               /* SArt TierArznei */
	unsigned char  SArtVertriebsgeb;             /* SArt Vertriebsgebunden */
	unsigned char  SArtLieferSperre;             /* SArt LieferSperre */
	unsigned char  SArtAbschlag;                 /* SArt Abschlag */
	unsigned char  SArtPreisErmaess;             /* SArt PreisErmaessigung */
	unsigned char  SArtVertriebsbind1;           /* SArt Vertriebsbindung1 */
	unsigned char  SArtVertriebsbind2;           /* SArt Vertriebsbindung2 */
	unsigned char  SArtVertriebsbind3;           /* SArt Vertriebsbindung3 */
	unsigned char  SArtVertriebsbind4;           /* SArt Vertriebsbindung4 */
	char           KdGruppeSperrKZ;              /* Kundengruppe SperrKZ */
	char           KdGruppeFreiKZ;               /* Kundengruppe FreiKZ */
};


/*****************************************************************************/
/*  Dispo Artikel                                                            */
/*                                                                           */
/*****************************************************************************/

struct tDISPOARTIKEL
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	char           Darreichform[3+1];            /* Darreichform */
	char           Einheit[9+1];                 /* Einheit */
	char           Bezeichnung[30+1];            /* Bezeichnung */
	long           ETArtKlasse1;                 /* ETab Artikel Klasse 1 */
	long           ETArtKlasse2;                 /* ETab Artikel Klasse 2 */
	long           ETArtSchalter1;               /* ETab Artikel Schalter 1 */
	long           ETArtSchalter2;               /* ETab Artikel Schalter 2 */
	long           ETArtSchalter3;               /* ETab Artikel Schalter 3 */
	long           ETArtSchalter4;               /* ETab Artikel Schalter 4 */
	long           ETArtSchalter5;               /* ETab Artikel Schalter 5 */
	double         PreisEKApo;                   /* Preis EK Apotheke */
	double         PreisEKGrosso;                /* Preis EK Grosso */
	double         RabattFestDM;                 /* Rabatt Fest in DM */
	double         RabattFest;                   /* Rabatt Fest in Prozent */
	char           Rabattfaehig[2+1];            /* Rabattfaehigkeit Hinweis */
	char           WarenGruppeEigen[5+1];        /* Eigene Warengruppe */
	double         GebuehrBearb;                 /* Bearbeitungsgebuehr */
	long           UrsprungAuftragnr;            /* Ursprungauftragsnummer */
	long           UrsprungPosnr;                /* Ursprungposistionsnummer */
	short          TaxLevel;                     /* TaxLevel */
	double         NetPrice;                     /* Netto Preis*/
	short          Service_No;                   /* ServiceNumber BG */
};


/*****************************************************************************/
/*  Kundenauftrag Bemerkung                                                  */
/*  Kundenauftrags-Bemerkung                                                 */
/*****************************************************************************/

struct tKDAUFTRAGBEM
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	short          Bemerkungsart;                /* Bemerkungsart */
	short          Bemerkungsnr;                 /* Bemerkungsnummer */
	char           Bemerkungen[240+1];           /* Bemerkungen */
};


/*****************************************************************************/
/*  Zeitarten                                                                */
/*  Zeitarten Definitionen                                                   */
/*****************************************************************************/

struct tZEITARTEN
{
	long           LfdNr;                        /* Laufende Nummer */
	long           ZeitArt;                      /* Zeit Art */
	char           ZeitSchluessel[16+1];         /* Zeit Schluessel */
	char           TagesTyp[6+1];                /* Tagestyp */
	long           ZeitBegin;                    /* Zeitraster Anfang */
	long           ZeitEnde;                     /* Zeitraster Ende */
	unsigned char  ZeitZusatz;                   /* Zeit Zusatz Info */
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	short          WeekDay;                      /* DayOfWeek*/
};


/*****************************************************************************/
/*  Auftrag Abschlusszeit                                                    */
/*  Abschlusszeiten f’r Batchauftr„ge                                        */
/*****************************************************************************/

struct tKDAUFTRAGENDEZEIT
{
	short          FilialNr;                     /* Filialnummer */
	long           BatchSchreiben;               /* Herkunftstyp */
	short          HerkunftsFilialNr;            /* Herkunfts Filialnr */
	short          AbschlussModus;               /* Abschluss Modus */
	long           AbschlussZeit;                /* Zeit Auftrags-Abschluss */
};


/*****************************************************************************/
/*  Kunden R’ckstand Protokoll                                               */
/*  Kundenauftrag Rueckstand Protokoll                                       */
/*****************************************************************************/

struct tNACHLIEFPROT
{
	long           ArtikelNr;                    /* Artikelnummer */
	long           IDFNr;                        /* Kundennummer IDF */
	long           MengeAlt;                     /* Menge Alt */
	short          AenderungsTyp;                /* Aenderungs Typ */
	short          PosTyp;                       /* Position Typ */
	long           Datum;                        /* Datum */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           Zeit;                         /* Zeit */
	long           DatumNeu;                     /* Datum Neu */
	long           KdAuftragNrNeu;               /* Kunden Auftrag Nummer Neu */
	long           MengeAktuell;                 /* Menge Aktuell */
	long           MengeGeliefert;               /* Menge Geliefert */
	long           MengeNeu;                     /* Menge Neu */
	long           Uid;                          /* Benutzer Nummer */
	short          UserBranchNo;                 /* Branchno of user*/
};

/*****************************************************************************/
/*  Rechner Tabelle                                                          */
/*  Rechner Tabelle                                                          */
/*****************************************************************************/

struct tRECHNER
{
	short          FilialNr;                     /* Filialnummer */
	char           Rechner_Name[7+1];            /* Rechner Name */
	char           Standort[15+1];               /* Standort */
	char           Pflege;                       /* Schalter Pflege */
	char           DBName[35+1];                 /* Datenbank Name Outbound */
	char           S_Zentral;                    /* Schalter Zentral */
	char           DBNameWarehouse[35 + 1];      /* Datenbank Name Warehouse */
	char           DBNameInbound[35 + 1];        /* Datenbank Name Inbound */
};


/*****************************************************************************/
/*  Artikel Reimport                                                         */
/*  Artikel Reimporte                                                        */
/*****************************************************************************/

struct tARTIKELREIMPORT
{
	short          FilialNr;                     /* Filialnummer */
	long           ArtikelNr;                    /* Artikelnummer */
	long           ArtikelAlternNr;              /* Artikelnummer Alternativartikel */
	unsigned char  KZUpd;                        /* SKd Update */
	unsigned char  KZAktivPassiv;                /* SKd AktivPassiv*/
	short          ReihenFolge;                  /* Reihenfolgenr */
};


/*****************************************************************************/
/*  Artikel Zentral                                                          */
/*  Artikelstammsatz Zentral / Master                                        */
/*****************************************************************************/

struct tMARTIKEL
{
	long           ArtikelNr;                    /* Artikelnummer */
	char           MatchCode[12+1];              /* MatchCode */
	long           PackGroesse;                  /* Groesse Packung */
	char           Darreichform[3+1];            /* Darreichform */
	char           NormPackung[2+1];             /* Norm Packung */
	char           Einheit[9+1];                 /* Einheit */
	char           Bezeichnung[30+1];            /* Bezeichnung */
	long           ETArtKlasse1;                 /* ETab Artikel Klasse 1 */
	long           ETArtSchalter1;               /* ETab Artikel Schalter 1 */
	long           ETArtSchalter2;               /* ETab Artikel Schalter 2 */
	long           ETArtSchalter3;               /* ETab Artikel Schalter 3 */
	long           ETArtSchalter4;               /* ETab Artikel Schalter 4 */
	long           ETArtSchalter5;               /* ETab Artikel Schalter 5 */
	long           HerstellerNr;                 /* Herstellernummer */
	char           WarenGruppe[5+1];             /* Warengruppe */
	char           TherapieGruppe[5+1];          /* Therapiegruppe */
	long           Laenge;                       /* Laenge */
	long           Hoehe;                        /* Hoehe */
	long           Breite;                       /* Breite */
	long           Gewicht;                      /* Gewicht */
	long           LaufzeitMonate;               /* Artikel Laufzeit in Monaten */
	char           WarenGruppeEigen[5+1];        /* Warengruppeneigenschaft */
	char           Hersteller_Code[5+1];         /* Herstellercode*/
	char           KzPsychoStoffe;               /* Kennzeichen Psychotropische Staffe*/
	short          TaxLevel;                     /* Steuerlevel*/
	short          TextKey_Hospital;             /* Textschl’ssel Hospital Artikel*/
	char           KzReserveHospital;            /* Kz Hospital Artikel*/
	short          STD_Menge;                    /* standard menge*/
	char           Rundungs_STD_MGE;             /* Kz Rundung auf standard Menge*/
	char           Nicht_Ueber_Dafue;            /* Artikel nicht ueber Dafue*/
	char           Nicht_Ueber_XML;              /* Artikel nicht ueber XML*/
	char           KzZuschlagsArtikel;           /* Artikel mit bestellzuschlag*/
	char           Wirkstoff_NR[3+1];            /* Wirkstoffnummer*/
	char           HealthFundCode[5+1];          /* Healthfundcode */
	char           Steller;                      /* Steller Artikel*/
	char           PositivListe;                 /* Positivliste(RS)*/
	char           AbdaCode[5+1];                /* Abdacode */
	long           Konsig_Partner_Nr;            /* Konsig_Partner_Nr*/
	char           Artikel_Langname[50+1];       /* Artikel Langname*/
	short          Price_Group;                  /* Preisgruppe*/
	char           Sortiment1;                   /* Sortiment1*/
	char           Sortiment2;                   /* Sortiment2*/
	char           Sortiment3;                   /* Sortiment3*/
	char           Sortiment4;                   /* Sortiment4*/
	char           Sortiment5;                   /* Sortiment5*/
	long           Datum_Anlage;                 /* DatumAnlage*/
	short          BusinessTypeNo;               /* Business TypeNo Ivrylab Cap/Plattform/pharmacy plus */
	short          Liste_5;                      /* Liste5 artikel Kennzeichen */
	char           Upd_Flag;                     /* Update Flag*/
	char           Artikel_NR_Herst[15+1];       /* ArtikelNr vom Hersteller*/
	char           MedProd_ABG_Verord;           /* MEDPROD_ABG_VERORD*/
	short          ProduserQuota;                /* ProduserQuota*/
	short          MedicalProduct;               /* Medical Product*/
	long           DateOutOfTrade;               /* DatumAusserHandel*/
	char           ArticleBlocked;               /* ArtikelGesperrt*/
	char           IKSCode;                      /* IKS Code*/
	long           BatchRecallDateReturns;       /* Datum Retourensperre für Chargenrückruf*/
    short          ImportArticle;                /* Importarticle*/
    double         BtmFaktor;                    /* BTM Faktor*/
    char           TFG;                          /* TFG*/
    char           KontingentPPE;                /* Kontingent PPE*/
	long           Datum_Lieferbar_Ab;           /* Datum_Lieferbar_Ab*/
	char           MedizinProdukt;               /* MedizinProdukt*/
	short          Frozen;                       /* Frozen*/
	long           Datum_Aender;                 /* Datum Aender*/
	char           ATC_Code[25+1];               /* ATC_Code*/    
	char           MinistryProductCode[25+1];    /* Ministry Product Code (BG)*/
	char           HealthFundCodeHospital[25+1]; /* Healthfund Code Hospital(BG)*/
	short          CMIFlag;
	char           TaxPflichtig;
};


/*****************************************************************************/
/*  Artikel Lokal                                                            */
/*  Artikelsatz Vertriebszentrum/Filiale                                     */
/*****************************************************************************/

struct tFARTIKEL
{
	short          FilialNr;                     /* Filialnummer */
	long           ArtikelNr;                    /* Artikelnummer */
	long           Bestand;                      /* Bestand */
	long           NachFrage;                    /* Nachfrage */
	char           Zuzahlung;                    /* Kz Zuzahlung */
	char           Rabattfaehig[2+1];            /* Rabattfaehigkeit Hinweis */
	long           NatraStaffelNr;               /* Natra Staffel Nummer */
	char           Prisoart;                     /* Priso Artikel */
	char           Artikelaktiv;                 /* Kz Artikel Aktiv */
	short          LagerBereichNr;               /* Lagerbereichsnummer */
	char           StationNr[2+1];               /* Stationsnummer */
	char           LagerFachNr[10+1];            /* Lager Fachnummer */
	char           VerbundArtikel;               /* Verbund Artikel */
	long           ETArtSchalter1;               /* ETab Artikel Schalter 1 */
	long           ETArtSchalter2;               /* ETab Artikel Schalter 2 */
	long           ETArtSchalter3;               /* ETab Artikel Schalter 3 */
	long           ETArtSchalter4;               /* ETab Artikel Schalter 4 */
	long           ETArtSchalter5;               /* ETab Artikel Schalter 5 */
	long           VerkaufEinheit;               /* VerkaufEinheit */
	long           ContainerGroesse;             /* Groesse Container */
	short          KontigentMenge;               /* Menge Maximale Abgabe */
	char           ChargenArtikel;               /* Chargenartikel*/
	short          TextKey;                      /* Textkey f’r ArticleText*/
	long           BestandReserviert;            /* Bestand Reserviert prehold*/
	char           WafoTyp;                      /* Wafotyp*/
	char           KZRange;                      /* Kennzeichen Rangeartikel*/
	char           MoreConditions;               /* Kennzeichen Artikelkonditionen*/
	long           BestandTagesAnfang;           /* Bestand am Anfang des Tages*/
	char           CodeBlocage;                  /* Kennzeichen CodeBlocage*/
	short		   BlockedForReturns;		     /* Retouren-Sperre*/
};


/*****************************************************************************/
/*  Regionen Arten                                                           */
/*                                                                           */
/*****************************************************************************/

struct tREGIONARTEN
{
	short          RegionenTyp;                  /* RegionenTyp */
	long           RegionNr;                     /* RegionNr */
	long           RegionTeilNr;                 /* RegionTeilNr */
};


/*****************************************************************************/
/*  Lager Revision                                                           */
/*  Lager Revision                                                           */
/*****************************************************************************/

struct tLAGERREVISION
{
	short          FilialNr;                     /* Filialnummer */
	long           ArtikelNr;                    /* Artikelnummer */
	long           Datum;                        /* Datum */
	long           UhrZeit;                      /* Uhrzeit */
	long           BestandKSC;                   /* BestandKSC */
	long           BestandVSE;                   /* BestandVSE */
};


/*****************************************************************************/
/*  Task Control                                                             */
/*  Task Control Table                                                       */
/*****************************************************************************/

struct tTASKCONTROL
{
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           ZeitUnix;                     /* Zeit Unix */
	char           ProgrammName[15+1];           /* ProgrammName */
};


/*****************************************************************************/
/*  Artikelnummern Tabelle mit EAN                                           */
/*  Artilelnummern Table                                                     */
/*****************************************************************************/

struct tARTIKELNUMMERN
{
	long           Pzn;                          /* Pharmazentralnummer*/
	char           Ean[13+1];                    /* Pharmazentralnummer*/
	long           ArtikelNr;                    /* Artikelnummer*/
};



/*****************************************************************************/
/*  Kunden Bestellnummern Tabelle                                            */
/*  Kunden Bestellnummern Table                                              */
/*****************************************************************************/

struct tCUSTOMERORDERNO
{
	short          BranchNo;                     /* Branchnummer*/
	long           CustomerNo;                   /* Customernumber   */
	long           ProcessNo;                    /* Procesnumbert*/
	char           CustomerOrderNo[30+1];         /* KundenBestellNummer*/
	double         OrderValue;                   /* Auftragswert*AnzPos*/
};



/*****************************************************************************/
/*  Kunden BestellInfo Tabelle                                            */
/*  Kunden BestellInfo Table                                              */
/*****************************************************************************/

struct tKDAUFTRAGINFO
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	char           KdAuftragBestellNr[9+1];      /* KundenBestellNummer*/
	long           IDFNrIntern;                  /* interne Kundennummer*/
	char           ApoTourId[10+1];              /* interne Tourid      */
	char           VersandArt[2+1];              /* interne Versandart  */
	long           ProcessNr;                    /* interne Vorgangsnummer*/
	unsigned char  EdiLieferSchein;              /* Edi Lieferschein*/
	long           BatchAuftragNr;               /* Batch Auftragnummer*/
};

/*****************************************************************************/
/*  Customer Routing Table                                                   */
/*  Customer Routing Table                                                   */
/*****************************************************************************/

struct tCUSTOMERROUTING
{
	long           CustomerNo;                   /* Customernumber*/
	short          BranchNo;                     /* Branchnummer*/
	long           TimeFrom;                     /* Time from*/
	long           TimeTo;                       /* Time to*/
	short          DestBranchNo;                 /* Branchnummer*/
	char           DayOfWeek[2+1];               /* Day of week*/
	short          WeekDay;                      /* DayOfWeek*/
};

/*****************************************************************************/
/*  Customer Pharmac Group Table                                             */
/*  Customer Pharmac Group Table                                             */
/*****************************************************************************/

struct tCUSTOMERPHARMACYGR
{
	long           CustomerNo;                   /* Customernumber*/
	short          BranchNo;                     /* Branchnummer*/
	char           PharmacyGroupId[3+1];         /* Pharmacy Group Id*/
	short          Ranking;                      /* Ranking*/
};

/*****************************************************************************/
/*  Valid Discount Informatione Table                                        */
/*  Valid Discount Informatione Table                                        */
/*****************************************************************************/

//struct tVALIDDISCOUNTINFO
//{
//	short          BranchNo;                     /* Branchnummer*/
//	long           ArticleNo;                    /* Article Number*/
//	char           PharmacyGroupId[3+1];         /* Pharmacy Group Id*/
//	long           DateFrom;                     /* Date From*/
//	long           DateTo;                       /* Date To*/
//	char           TypeOfDiscount;               /* Type of Discount*/
//	long           BaseQty;                      /* base quantity just for Typbar*/
//	long           DiscountValue;                /* Discount value*/
//	char           TypeOfValue[2+1];             /* TypeOfValue*/
//};

/*****************************************************************************/
/*  Stockentry  Table                                                        */
/*  Stockentry  Table                                                        */
/*****************************************************************************/

struct tSTOCKENTRY
{
	long           Date;                         /* Date*/
	short          BranchNo;                     /* Branchnummer*/
	long           ArticleNo;                    /* Article Number*/
};

/*****************************************************************************/
/*  Debtlimit Table                                                          */
/*  Debtlimit Table                                                          */
/*****************************************************************************/

struct tDEBTLIMIT
{
	long           PartnerNo;                    /* Partner Number*/
	char           PartnerName[30+1];            /* Partner Name*/
	double         Limit;                        /* Credit Limit*/
	double         Sum_DebitSide;                /* Sum Debitside*/
	double         Sum_CreditSide;               /* Sum Creditside*/
	double         Sum_MonTurnOver;              /* Sum Months Turnover*/
	double         Sum_DayTurnOver;              /* Sum Day    Turnover*/
	double         Sum_Returns;                  /* Sum Returns*/
	double         Sum_GoodsReceipt;             /* Sum Good Receipt*/
	short          LimitType;                    /* LimitType (k1,k2 == 1,2)*/
	char           Liste5;                       /* Liste 5 (mit Liste5 Artikel*/
};

/*****************************************************************************/
/*  ArticleQuota Table                                                       */
/*  ArticleQuota Table                                                       */
/*****************************************************************************/

struct tARTICLEQUOTA
{
	short          BranchNo;                     /* Branchnummer*/
	long           CustomerNo;                   /* Customernumber*/
	long           ArticleNo;                    /* Article Number*/
	long           Quota;                        /* Article Quota*/
	long           KumQty;                       /* Acumulated Quantity*/
	char           Validity;                     /* Validity T,M,J*/
	char           SDafueQuota;                  /* Dafue Quota*/
	long           DateFrom;                     /* Date From*/
	long           DateTo;                       /* Date To*/
	char           PharmacyGroupId[3+1];         /* Pharmacy Group Id*/
};

/*****************************************************************************/
/*  Parameter    Table                                                       */
/*  Parameter    Table                                                       */
/*****************************************************************************/

struct tPARAMETER
{
	short          FilialNr;                     /* Filialnummer */
	char           ProgrammName[15+1];           /* Programmname*/
	char           Zweck[20+1];                  /* Zweck*/
	char           ParameterName[20+1];          /* Parametername*/
	char           AusPraegung[254+1];           /* Auspraegung*/
	long           Wert;                         /* Wert*/
};

/*****************************************************************************/
/*  ArticleText  Table                                                       */
/*  ArticleText  Table                                                       */
/*****************************************************************************/

struct tARTICLETEXT
{
	short          BranchNo;                     /* Filialnummer */
	short          TextKey;                      /* Textkey*/
	char           Text[240+1];                  /* Articletext*/
	char           DisplayOnScreen;              /* display on screen*/
};

/*****************************************************************************/
/*  DelayedDeliveryCst  Table                                                */
/*  DelayedDeliveryCst  Table                                                */
/*****************************************************************************/

struct tDELAYEDDELIVERYCST
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	short          WeekDay;                      /* DayOfWeek*/
	long           Time;                         /* What time*/
	char           TourId[6+1];                  /* Tour Identifikation */
	char           Activ;                        /* Activ*/
	short          DelayedWeekDay;               /* Day of delayeddelivery*/
	char           NarCotic;                     /* Narcotic article*/
	char           ColdChain;                    /* Coldchain article*/
	char           Cool08;                       /* Cool 08   article*/
	char           Cool20;                       /* Cool 20   article*/
	long           DateFrom;                     /* Date from YYYYMMDD*/
	long           DateTo;                       /* Date to YYYYMMDD*/
};

/*****************************************************************************/
/*  Feiertag  Table                                                          */
/*  Feiertag  Table                                                          */
/*****************************************************************************/

struct tFEIERTAG
{
	short          FilialNr;                     /* Filialnummer */
	short          Modus;                        /* Modus*/
	short          Tag;                          /* Tag*/
	short          Von_Jahr;                     /* von Jahr*/
	short          Bis_Jahr;                     /* bis Jahr*/
};

/*****************************************************************************/
/*  Discount  Table                                                          */
/*  Discount  Table                                                          */
/*****************************************************************************/

struct tDISCOUNT
{
	short          BranchNo;                     /* Filialnummer */
	long           ArticleNo;                    /* Article Number*/
	long           DiscountGrpNo;                /* DiscountGroupNumber(Range)*/
	char           PharmacyGroupId[3+1];         /* Pharmacy Group Id*/
	long           CustomerNo;                   /* Customerno*/
	short          GrpDiscountTyp;               /* GroupDiscounttyp*/
	long           DateFrom;                     /* Date From*/
	long           DateTo;                       /* Date To*/
	long           BaseQty;                      /* base quantity just for Typbar*/
	short          DiscountSpec;                 /* Discountspecification*/
	short          DiscountType;                 /* DiscountType*/
	short          DiscountQty;                  /* DiscountQuantity*/
	double         DiscountValuePct;             /* DiscountValue Percent*/
	double         DiscountQtyPct;               /* Discount Quantity Percent*/
	double         SurchargePct;                 /* Discount Quantity Percent*/
	char           PharmGrpExcluded[3+1];        /* Pharmacy Group Id Excluded*/
	double         FixedPrice;                   /* Fixed Price*/
	double         RefundPct;                    /* Refund percentage*/
	char           InternalDiscount;             /* Internal Discount*/
	long           DiscountArticle;              /* Discount Article Number*/
	char           PharmGrpExcluded_2[3+1];      /* Pharmacy Group Id Excluded*/
	char           PharmGrpExcluded_3[3+1];      /* Pharmacy Group Id Excluded*/
	double         Base_Value;                   /* Base Value*/
	long           Base_Mult_STD_Qty;            /* Base multiple standard quantity*/
	char           No_Multiple_Qty;              /* KZ No_mutiple quantity*/
	double         FixedDiscountValue;           /* ??*/
	long           ManufacturerNo;               /* manufacturerno*/
	long           ArtCategoryNo;                /* ARTCATEGORYNO*/
	short          PaymentTargetNo;              /* PAYMENTTARGETNO*/
	double         GrossProfitPct;               /* GrossProfitPct*/
	char           AddonDiscountOk;              /* ADDONDISCOUNTOK*/
	char           PaymentTermType;              /* PaymentTermType*/
	long           TargetQty;                    /* TARGETQTY*/
	double         ExceedancePct;                /* EXCEEDANCEPCT*/
	short          RefundType;                   /* REFUNDTYPE*/
	long           Article_No_Pack;              /* Articleno(Steller)*/
	double         RefundValue;                  /* Refund Value */
	short          Promotion_No;                 /* Promotion No*/
	long           MaxQty;                       /* Max quantity to order*/
	char           TurnOverCalcImpact;           /* 0 = Monatsrabattierung 1 = nicht*/
	char           AddonDiscount;                /* ADDONDISCOUNT*/
	char           MonthlyDiscount;              /* Monthly Discount*/
	short          DiscountCalcFrom;             /* DISCOUNTCALCFROM*/
	short          DiscountApplyTo;              /* DISCOUNTAPPLYTO*/
};

/*****************************************************************************/
/*  ArticleReservation  Table                                                */
/*  ArticleReservation  Table                                                */
/*****************************************************************************/

struct tARTICLERESERVATION
{
	short          BranchNo;                     /* Filialnummer */
	char           PharmacyGroupId[3+1];         /* Pharmacy Group Id*/
	long           ArticleNo;                    /* Article Number*/
	short          ReservType;                   /* Reserve Type*/
	long           MaxQty;                       /* Maximum Quantity*/
	long           ReservedQty;                  /* Maximum Quantity*/
	short          ReservePct;                   /* Percentage*/
};

/*****************************************************************************/
/*  KdAuftragPosRab     Table                                                */
/*  KdAuftragPosRab     Table                                                */
/*****************************************************************************/

struct tKDAUFTRAGPOSRAB
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	short          DiscountType;                 /* DiscountType*/
	double         DiscountValuePct;             /* DiscountValue Percent*/
	char           PharmacyGroupId[3+1];         /* Pharmacy Group Id*/
	short          PaymentTargetNo;              /* PaymentTargetNo*/
	double         DiscountValPctMan;            /* DiscountValue Percent manual*/
	double         SurchargePct;                 /* Zuschlag percentage*/
	short          DiscountCategory;
	short          InternalDiscountFlag;
	double         RefundValuePct;
	double         FixedPrice;
	short          DiscountCalcFrom;             /* DISCOUNTCALCFROM*/
	short          DiscountApplyTo;              /* DISCOUNTAPPLYTO*/
};

/*****************************************************************************/
/*  DiscountGrp         Table                                                */
/*  DiscountGrp         Table                                                */
/*****************************************************************************/

struct tDISCOUNTGRP
{
	short          BranchNo;                     /* Filialnummer */
	long           DiscountGrpNo;                /* DiscountGroup Number */
	char           Description[254+1];           /* Description */
	short          DiscountGrpType;              /* DiscountGroupType*/
	long           CustomerNo;                   /* Customerno*/
};

/*****************************************************************************/
/*  DiscountGrpMem      Table                                                */
/*  DiscountGrpMem      Table                                                */
/*****************************************************************************/

struct tDISCOUNTGRPMEM
{
	short          BranchNo;                     /* Filialnummer */
	long           DiscountGrpNo;                /* DiscountGroup Number */
	long           ArticleNo;                    /* Article Number*/
	short          DiscountCondition;            /* DiscountCondition*/
	long           ManufacturerNo;               /* manufacturerno*/
};

/*****************************************************************************/
/*  DiscountOrderTyp    Table                                                */
/*  DiscountOrderTyp    Table                                                */
/*****************************************************************************/

struct tDISCOUNTORDERTYP
{
	short          DiscountType;                 /* DiscountType*/
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
};


/*****************************************************************************/
/*  NarcTransactTransfer Table                                               */
/*****************************************************************************/

struct tNARCTRANSACTIONTRANSFER
{
	long           TransferID;                   /* laufender Nummer serial*/
	short          BranchNo;                     /* Branch number*/
	long           ArticleNo;                    /* Article number*/
	long           TransactionDate;              /* Transaction Date*/
	long           TransactionTime;              /* Transaction Time*/
	long           CustomerSupplierNo;           /* CustomerID or SupplierID*/
	char           TransactionType[2+1];         /* Transaction type*/
	long           PurchaseOrderNo;              /* Purchase Ordernumber*/
	long           OrderNo;                      /* Ordernumber orderentry Host*/
	long           QtyTransaction;               /* Quantity ordered*/
	long           QtyInStock;                   /* Quantity in Stock at this time*/
	char           CompletedFlag;                /* Completion switch*/
	long           PosNo;                        /* Position numerber*/
	char           TourId[6+1];                  /* Tour Identifikation */
};

/*****************************************************************************/
/*  PositionParking     Table                                                */
/*****************************************************************************/

struct tPOSITIONPARKING
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	long           ArticleNo;                    /* Article number*/
	long           Date;                         /* Date*/
	long           OrderNoOrg;                   /* Original ordernumber*/
	long           OrderQty;                     /* Quantity ordered*/
};

/*****************************************************************************/
/*  ArticlePackUnit     Table                                                */
/*****************************************************************************/

struct tARTICLEPACKUNIT
{
	long           ArticleNo;                    /* Article number*/
	long           PackingUnit;                  /* PackingUnit(VE)*/
	short          RoundPct;                     /* Rounding percentage*/
};

/*****************************************************************************/
/*  TourPlantagWoche    Table                                                */
/*****************************************************************************/

struct tTOURPLANTAGWOCHE
{
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           KundenNr;                     /* Kunden Nummer VZ */
	char           TourId[6+1];                  /* Tour Identifikation */
	char           TagesTyp[6+1];                /* Tagestyp */
	short          WeekDay;                      /* DayOfWeek*/
	unsigned char  IstVerbundTour;               /* Schalter Ist Verbundtour */
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
	long           FahrtZeit;                    /* Fahrtzeit */
};

/*****************************************************************************/
/*  TourConsTime        Table                                                */
/*****************************************************************************/

struct tTOURCONSTIME
{
	short          FilialNr;                     /* Filialnummer */
	char           TourId[6+1];                  /* Tour Identifikation */
	long           DatumKommi;                   /* Datum Kommi */
	long           ConsTime;                     /* Consolidation Time */
	char           ProcessState;                 /* Process State 0/1*/
};

/*****************************************************************************/
/*  TourPlanConsTime     Table                                                */
/*****************************************************************************/

struct tTOURPLANCONSTIME
{
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	long           KundenNr;                     /* Kunden Nummer VZ */
	char           TourId[6+1];                  /* Tour Identifikation */
	long           DatumKommi;                   /* Datum Kommi */
	long           ConsTime;                     /* Consolidation Time */
	char           ProcessState;                 /* Process State 0/1*/
};


/*****************************************************************************/
/*  TourPlanWoche    Table                                                   */
/*****************************************************************************/

struct tTOURPLANWOCHE
{
	char           TourId[6+1];                  /* Tour Identifikation */
	char           TagesTyp[6+1];                /* Tagestyp */
	unsigned char  KZUpd;                        /* SKd Update */
	short          FilialNr;                     /* Filialnummer */
	short          WeekDay;                      /* DayOfWeek*/
	long           LagRechTour;                  /* Tour Identifikation Lagerrechner */
	short          KarenzZeit;                   /* KarenzZeit*/
};

/*****************************************************************************/
/*  DiscountList Table                                                       */
/*****************************************************************************/

struct tDISCOUNTLIST
{
	char           OrderType[2+1];               /* Customers Ordertype */
	char           SubOrderType[3+1];            /* Ordertype Sibordertype*/
	char           PharmacyGroupId[3+1];         /* Pharmacy Group Id*/
	char           PaymentTerm[4+1];            /* Payment condition*/
	double         MonthlyDiscPct;             /* DiscountValue Percent*/
	short          ValutaDays;                  /* Valuta days*/
};


/*****************************************************************************/
/*  CstDiscountCont Table                                                    */
/*****************************************************************************/

struct tCSTDISCOUNTCONT
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	char           OrderType[2+1];               /* Customers Ordertype */
	char           SubOrderType[3+1];            /* Ordertype Sibordertype*/
	char           PaymentTerm[4+1];             /* Payment condition*/
	short          ValutaDays;                   /* Valuta days*/
	double         MinOrderValue;                /* Low order value*/
	short          MinTubes;                     /* lowest count of tubes*/
	double         LossInDiscount;               /* Loss in Discount*/
};

/*****************************************************************************/
/*  TaxRates  Table                                                          */
/*****************************************************************************/

struct tTAXRATES
{
	short          TaxLevel;                     /* TaxLevel*/
	double         SalesTaxRate;                 /* MWST Level*/
};

/*****************************************************************************/
/*  SepOrderArtGrp  Table                                                    */
/*****************************************************************************/

struct tSEPORDERARTGRP
{
	short          BranchNo;                     /* Filialnummer */
	short          ArtGrp;                       /* ArticleGroup*/
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
	char           KoArt;                        /* Kommissionierungsart */
	char           BuchArt;                      /* Buchungsart */
	char           DeferOrder;                   /* Defer Order 0/1*/
	long           ManufacturerNo;               /* manufacturerno*/
};

/*****************************************************************************/
/*  ArticleOldPrice  Table                                                   */
/*****************************************************************************/

struct tARTICLEOLDPRICE
{
	short          BranchNo;                     /* Filialnummer */
	long           ArticleNo;                    /* Article number*/
	double         PreisEKApo;                   /* Preis EK Apotheke */
	double         PreisEKGrosso;                /* Preis EK Grosso */
	double         PreisEKGrossoNA;              /* Preis EK Grosso Nettoaktion */
	double         PreisVKApo;                   /* Preis VK Apotheke */
};

/*****************************************************************************/
/*  CountryCodes    Table                                                    */
/*****************************************************************************/

struct tCOUNTRYCODES
{
	short          BranchNo;                     /* Filialnummer */
	char           InfoCode[2+1];                /* InfoCode */
	char           ArticleActiv;                 /* ArtikelAktiv Kennzeichen*/
	char           AuxDelivery;                  /* Verbund Kennzeichen*/
	char           SeraCode[20+1];               /* SeraCode*/
	char           PrintCode[30+1];              /* Anzeige Text*/
	char           XMLCode[5+1];                 /* XML Code*/
	char           XMLText[100+1];               /* XML Text*/
};

/*****************************************************************************/
/*  ArticleLppr                                                              */
/*****************************************************************************/

struct tARTICLELPPR
{
	long           ArticleNo;                    /* Article number*/
	char           Reimbursement_Type;           /* Verg’tungstype*/
	double         ReimbursementPrice;           /* Verg’tungspreis */
};

/*****************************************************************************/
/*  OrderCriteria                                                            */
/*****************************************************************************/

struct tORDERCRITERIA
{
	short          BranchNo;                     /* Filialnummer */
	long           ArticleNo;                    /* Article number*/
	long           ManufacturerNo;               /* Article number*/
	char           PharmacyGroupId[3+1];         /* Pharmacy Group Id*/
	long           CustomerNo;                   /* Customerno*/
	char           OrderType[2+1];               /* Customers Ordertype */
	long           MinOrderQty;                  /* Low order quantity*/
	double         MinOrderValue;                /* Low order value*/
	char           LimitAction[2+1];             /* Limit action*/
	char           ActionRestriction[2+1];       /* Action Restriction*/
	long           AddOnChargeArtNo;             /* Add on charge ArticleNo*/
	double         AddOnChargePct;               /* Add on charge percentage*/
};

/*****************************************************************************/
/*  Kunde Auskunft Tabelle                                                   */
/*****************************************************************************/

struct tKNDAUSKU
{
	double         EilbotenZuschlag;             /* Eilbotenzuschlag */
	long           KundenNr;                     /* Kunden Nummer VZ */
	short          VertriebszentrumNr;           /* Vertriebszentrum */
	double         DispoGebuehr;                 /* Dispogebuehr     */
	double         BTMGebuehr;                   /* BTM Gebuehr      */
	double         DokuGebuehr;                  /* Doku Gebuehr     */
	double         LogistikAufschlag;            /* Logistik Aufschlag*/
};

/*****************************************************************************/
/*  SepOrderArtGrp  Table                                                    */
/*****************************************************************************/

struct tCSTSEPORDERARTGRP
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	short          ArtGrp;                       /* ArticleGroup*/
	char           KdAuftragArt[2+1];            /* Kunde Auftrag Art */
	char           KoArt;                        /* Kommissionierungsart */
	char           BuchArt;                      /* Buchungsart */
	char           DeferOrder;                   /* Defer Order 0/1*/
};

/*****************************************************************************/
/*  ArticleGroup  Table                                                    */
/*****************************************************************************/

struct tARTICLEGROUP
{
	long           ArticleNo;                    /* Articleno*/
	long           ArtCategoryNo;                /* ArtCategoryNo*/
};

/*****************************************************************************/
/*  ArtComPack  Table                                                        */
/*****************************************************************************/

struct tARTCOMPACK
{
	long           Article_No_Pack;              /* Articleno(Steller)*/
	long           Article_No_Element;           /* Articleno(Steller_Element)*/
	long           Quantity;                     /* Quantity*/
};

/*****************************************************************************/
/*  CstDiscAcc  Table  CustomerDiscountAccount                               */
/*****************************************************************************/

struct tCSTDISCACC
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	long           MainCstNo;                    /* Main Customerno*/
	double         Balance;                      /* Saldo*/
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           Date;                         /* Datum*/
	char           InvoiceNumber[15+1];          /* Invoicenumber*/
	double         InvoiceAmount;                /* Invoice Amount*/
	char           VoucherTyp[2+1];              /* Type of Voucher*/
	short          Preis_Typ;                    /* PriceType FV/KK */
	short          Priority;                     /* Priority */
	long           KdAuftragNrSplit;             /* Number of splitted order*/
	double         InvoicePaid;                  /* Invoice Amount paid*/
	short          PaymentTarget;                /* Paymenttartget */
	long           LfdNr;                        /* Laufende Nummer */
};

/*****************************************************************************/
/*  DealerVolume  Table  DealerVolume                                        */
/*****************************************************************************/

struct tDEALERVOLUME
{
	short          BranchNo;                     /* Filialnummer */
	long           Uid;                          /* Benutzer Nummer */
	long           InVoiceNo;                    /* Invoicenumber*/
	long           OrderNoVSE;                   /* Order Number VSE(Pharmos)*/
	long           OrderNoKSC;                   /* Order Number KSC*/
	long           DateInVoice;                  /* Date InVoice */
	long           TimeInVoice;                  /* Time InVoice */
	double         InVoiceVolume;                /* InVoice Volume*/
	double         Volume1;                      /* Volume 1*/
	double         Volume2;                      /* Volume 2*/
	double         Volume3;                      /* Volume 3*/
	double         Volume4;                      /* Volume 4*/
	long           CustomerNo;                   /* Customerno*/
	char           VolumeState;                  /* Orderstate 0 = ok, 1 = storno*/
};

/*****************************************************************************/
/*  CPValidityPeriod Table                                                   */
/*****************************************************************************/

struct tCPVALIDITYPERIOD
{
	long           Article_No_Pack;              /* Articleno(Steller)*/
	long           DateFrom;                     /* Date From*/
	long           DateTo;                       /* Date To*/
	short          Type;                         /* Type Values 1,2,3*/
};

/*****************************************************************************/
/*  TenderHead Table                                                        */
/*****************************************************************************/

struct tTENDERHEAD
{
	long           TenderNo;                     /* Tender Number*/
	long           TenderType;                   /* Type of Tender*/
	char           ContractNo[48+1];             /* Contract Number*/
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	short          AccBranchNo;                  /* Account Branchno*/
	long           AccCustomerNo;                /* Account Customerno*/
	long           DateFrom;                     /* Date From*/
	long           DateTo;                       /* Date To*/
	double         ExceedancePct;                /* Exeedancepct*/
	char           TenderState;                  /* Tenderstate*/
	long           ChangeDate;                   /* Date changed*/
	char           NameOfUser[30+1];             /* Name of User*/
	long           PharmacyChainNo;              /* Kettennummer*/
};

/*****************************************************************************/
/*  TenderPos Table                                                        */
/*****************************************************************************/

struct tTENDERPOS
{
	long           TenderNo;                     /* Tender Number*/
	long           ArticleNo;                    /* Articleno*/
	long           ContractQty;                  /* ContractQtyr*/
	double         ContractPrice;                /* ContractPrice*/
	long           RemainingLife;                /* Remaining Life in months*/
	double         AddDiscountPct;               /* Additional discount percentage*/
	double         Aep;                          /* Aep*/
	char           TenderState;                  /* Tenderstate*/
	long           ChangeDate;                   /* Date changed*/
	char           NameOfUser[30+1];             /* Name of User*/
	double         PriceDiff;                    /* Additional discount percentage*/
};

/*****************************************************************************/
/*  TenderProgress Table                                                        */
/*****************************************************************************/

struct tTENDERPROGRESS
{
    long    TenderNo;                     /* Tender Number*/
    long    ArticleNo;                    /* Articleno*/
    long    KdAuftragNr;                  /* KdAuftragNr*/
    long    OrderDate;                    /* Order Date*/
    long    DeliveryQty;                  /* Delivery Quantity*/
    double  ChargedPrice;                 /* Charged Price*/
    long    PosNr;                        /* Positionsnummer Kundenauftrag */
    long    ReturnQty;                    /* Return Quantity(Gutschriften)*/
    long	OrderTime;
    long	CustomerNo;
    double	AEP;
    long	BookingTenderNo;
    long	InvoiceNo;
    long	InvoiceDate;
    char	KdAuftragArt[3];
    double	GEP;
    long	InvoiceTime;
    short	BranchNo;
    double	DiscountPct;
    long	ChangeDate;
};

/*****************************************************************************/
/*  ArtikelZentralFr Table                                                     */
/*****************************************************************************/

struct tMARTIKELFR
{
	long           ArtikelNr;                    /* Artikelnummer */
	char           MatchCode[12+1];              /* MatchCode */
	char           Bezeichnung[30+1];            /* Bezeichnung */
	char           Einheit[9+1];                 /* Einheit */
	char           Darreichform[3+1];            /* Darreichform */
};

/*****************************************************************************/
/*  KdAuftragDiscAcc                                                         */
/*****************************************************************************/

struct tKDAUFTRAGDISCACC
{
	long           KdAuftragNr;                  /* KdAuftragNr*/
	short          SwChain;                      /* Switch Chain 0 = No,1 = Yes*/
	long           DateFrom;                     /* Date From*/
	long           DateTo;                       /* Date To*/
	short          BranchNo;                     /* Filialnummer */
};


/*****************************************************************************/
/*  ArtSpecialCond                                                           */
/*****************************************************************************/

struct tARTSPECIALCOND
{
	long           ArticleNo;                    /* Articleno*/
	double         Invoice_Rebate_Pct;           /* InvoiceRebatePct */
	double         Rebate_In_Kind_Pct;           /* RebateInKindPct */
	double         Annual_Inv_Reb_Pct;           /* AnnualInvRebPct */
	double         Annual_Reb_I_K_Pct;           /* AnnualRebIKPct */
	double         Cust_Reb_Red_Pct;             /* CustRebRedPct */
	double         Hi_ReimBursement;             /* HiReimBursement */
	double         Suppl_Hi_Reimb;               /* Supplier HiReimBursement*/
	double         Suppl_Fs_Reimb;               /* Supplier FsReimBursement*/
	double         Suppl_Discount_Pct;           /* Supplier Discount percentage*/
};

/*****************************************************************************/
/*  Promotions                                                               */
/*****************************************************************************/

struct tPROMOTIONS
{
	short          Promotion_No;                 /* Promotion Number*/
	char           Name[30+1];                   /* Name */
	char           Description[254+1];           /* Description */
	short          Promotion_Type;               /* Promotion Type*/
	char           AddOnPromoDiscOk;             /* AddOnPromoDiscOk*/
	char           AddOnStdDiscOk;               /* AddOnStdDiscOk*/
	short          Priority;                     /* Priority*/
	char           SNotBySaleseWeb;              /* = 1 promotion not valid for salesweb*/
};

/*****************************************************************************/
/*  CstPaymentTerms                                                             */
/*****************************************************************************/

struct tCSTPAYMENTTERMS
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	short          Preis_Typ;                    /* Preistype */
	short          PaymentTarget;                /* PaymentTarget*/
};

/*****************************************************************************/
/*  KdAuftragWerte                                                           */
/*****************************************************************************/

struct tKDAUFTRAGWERTE
{
	long           KdAuftragNr;                  /* AuftragNummer*/
	double         OrdValFtaxFSDisc;             /* Ordervalue full tax Freesale with rebate(Fakturpreis)*/
	double         OrdValFtaxFS;                 /* Ordervalue full tax Freesale without rebate(AEP)*/
	double         OrdValLtaxFSDisc;             /* Ordervalue low  tax Freesale with rebate(Fakturpreis)*/
	double         OrdValLtaxFS;                 /* Ordervalue low  tax Freesale without rebate(AEP)*/
	double         OrdValFtaxHFDisc;             /* Ordervalue full tax Healthfund with rebate(Fakturpreis)*/
	double         OrdValFtaxHF;                 /* Ordervalue full tax Healthfund without rebate(AEP)*/
	double         OrdValLtaxHFDisc;             /* Ordervalue low  tax Healthfund with rebate(Fakturpreis)*/
	double         OrdValLtaxHF;                 /* Ordervalue low  tax Healthfund without rebate(AEP)*/
	double         TaxValFtaxFSDisc;             /* Tax  full tax Freesale with rebate(Fakturpreis)*/
	double         TaxValFtaxFS;                 /* Tax  full tax Freesale without rebate(AEP)*/
	double         TaxValLtaxFSDisc;             /* Tax  low  tax Freesale with rebate(Fakturpreis)*/
	double         TaxValLtaxFS;                 /* Tax  low  tax Freesale without rebate(AEP)*/
	double         TaxValFtaxHFDisc;             /* Tax  full tax Healthfund with rebate(Fakturpreis)*/
	double         TaxValFtaxHF;                 /* Tax  full tax Healthfund without rebate(AEP)*/
	double         TaxValLtaxHFDisc;             /* Tax  low  tax Healthfund with rebate(Fakturpreis)*/
	double         TaxValLtaxHF;                 /* tax  low  tax Healthfund without rebate(AEP)*/
	double         OrdValFtaxRSDisc;             /* Ordervalue full tax Retail with rebate(Fakturpreis)*/
	double         OrdValFtaxRS;                 /* Ordervalue full tax Retail without rebate(AEP)*/
	double         OrdValLtaxRSDisc;             /* Ordervalue low  tax Retail with rebate(Fakturpreis)*/
	double         OrdValLtaxRS;                 /* Ordervalue low  tax Retail without rebate(AEP)*/
	double         TaxValFtaxRSDisc;             /* Tax  full tax Retail with rebate(Fakturpreis)*/
	double         TaxValFtaxRS;                 /* Tax  full tax Retail without rebate(AEP)*/
	double         TaxValLtaxRSDisc;             /* Tax  low  tax Retail with rebate(Fakturpreis)*/
	double         TaxValLtaxRS;                 /* Tax  low  tax Retail without rebate(AEP)*/
	double         OrdValNtaxFSDisc;             /* Ordervalue Null tax Freesale with rebate(Fakturpreis)*/
	double         OrdValNtaxFS;                 /* Ordervalue Null tax Freesale without rebate(AEP)*/
	double         OrdValNtaxHFDisc;             /* Ordervalue Null tax Healthfund with rebate(Fakturpreis)*/
	double         OrdValNtaxHF;                 /* Ordervalue Null tax Healthfund without rebate(AEP)*/
	double         OrdValNtaxRSDisc;             /* Ordervalue Null tax Retail with rebate(Fakturpreis)*/
	double         OrdValNtaxRS;                 /* Ordervalue Null tax Retail without rebate(AEP)*/
	double         TaxValNtaxFSDisc;             /* Tax  Null tax Freesale with rebate(Fakturpreis)*/
	double         TaxValNtaxFS;                 /* Tax  Null tax Freesale without rebate(AEP)*/
	double         TaxValNtaxHFDisc;             /* Tax  Null tax Healthfund with rebate(Fakturpreis)*/
	double         TaxValNtaxHF;                 /* Tax  Null tax Healthfund without rebate(AEP)*/
	double         TaxValNtaxRSDisc;             /* Tax  Null tax Retail with rebate(Fakturpreis)*/
	double         TaxValNtaxRS;                 /* Tax  Null tax Retail without rebate(AEP)*/

};

/*****************************************************************************/
/*  KdAuftragPosCharge     Table                                                */
/*****************************************************************************/

struct tKDAUFTRAGPOSCHARGE
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	char           ChargenNr[25+1];              /* Chargennummer*/
	long           QuantityOrdered;              /* Quantity ordered*/
	short		   FixBatch;					 /* 0=Wunschcharge 1=Pflichtcharge*/
};

/*****************************************************************************/
/*  ArticleCharge     Table                                                  */
/*****************************************************************************/

struct tARTICLECHARGE
{
	short          BranchNo;                     /* Filialnummer */
	long           ArticleNo;                    /* Articleno*/
	long           ExpiryDate;                   /* Datum Verfall */
	char           ChargenNr[25+1];              /* Chargennummer*/
	long           Stock;                        /* Stock*/
	char           StateCharge;                  /* State of Charge*/
};

/*****************************************************************************/
/*  KdAuftragRechArt     Table                                                */
/*****************************************************************************/

struct tKDAUFTRAGRECHART
{
	short          Print;                        /* Print */
	short          Deduction_Aep;                /* Deduction_Aep */
	short          Deduction_Avp;                /* Deduction_Avp */
	short          WithColumnNr;                 /* WithColumnNr */
	short          ByEmail;                      /* ByEmail */
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
};

/*****************************************************************************/
/*  KdAuftrPosRechArt     Table                                              */
/*****************************************************************************/

struct tKDAUFTRPOSRECHART
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	double         SurchargePct;                 /* SurchargePct */
	double         DeductionPct;                 /* DeductionPct */
	double         Surcharge_Calc;               /* Surcharge_Calc */
	double         CalcAvp;                      /* CALCAVP */
	double         Surcharge_Calc_Dis;           /* Surcharge_Calc_Dis */
	double         CalcAvp_Dis;                  /* CALCAVP_Dis */
};

/*****************************************************************************/
/*  GeneralCalcAvp     Table                                                 */
/*****************************************************************************/

struct tGENERALCALCAVP
{
	short          Price_Group;                  /* Price_Group */
	double         PercentPreScript;             /* PercentPreScript */
	double         PercentNoPerScript;           /* PercentNoPerScript*/
	short          PreisTyp;
};

/*****************************************************************************/
/*  CstCalcAvp     Table                                                     */
/*****************************************************************************/

struct tCSTCALCAVP
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	char           AbdaCode[5+1];                /* Abdacode */
	short          Surcharge_Basic;              /* Surcharge_Basic */
	short          Deduction_Basic;              /* Deduction_Basic */
	double         SurchargePct;                 /* SurchargePct*/
	double         DeductionPct;                 /* SurchargePct*/
	short          PriceGroup;
	short          PreisTyp;
};

/*****************************************************************************/
/*  CstPrint     Table                                                       */
/*****************************************************************************/

struct tCSTPRINT
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	short          Preis_Typ;                    /* Preistype(BG) */
	short          Deduction_Aep;                /* Deduction_Aep */
	short          Deduction_Avp;                /* Deduction_Avp */
	short          Print;                        /* Print */
};

/*****************************************************************************/
//  TaxTab     Table
/*****************************************************************************/

struct tTAXTAB
{
	char           TaxArt;
	long           TaxVonDm;
	long           TaxProz;
	long           TaxBetrag;
	long           TaxFixpreis;
	long           TaxMaxBetrag;
};

/*****************************************************************************/
//  KdAuftragPosRefund     Table
/*****************************************************************************/

struct tKDAUFTRAGPOSREFUND
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	double         RefundValue;                  /* Refund Value */
	short          RefundSrc;                                    /* Quelle der Erstattung */
	short          Promotion_No;                 /* Promotion No */
};


/*****************************************************************************/
/*  KdAuftragPosPromo  Table                                                */
/*****************************************************************************/

struct tKDAUFTRAGPOSPROMO
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	long           DiscountGrpNo;                /* DiscountGroupNumber(Range)*/
	char           PharmacyGroupId[3+1];         /* Pharmacy Group Id*/
	long           BaseQty;                      /* base quantity just for Typbar*/
	double         Base_Value;                   /* Base Value*/
	long           CustomerNo;                   /* Customerno*/
	short          Promotion_No;                 /* PromotionNo*/
	char           InternalDiscount;             // internal discount or manufacturer discount?
	double         DiscountValuePct;              /* DiscountValuePct*/
};

/*****************************************************************************/
/*  KdAuftragPosChange Table                                                */
/*****************************************************************************/

struct tKDAUFTRAGPOSCHANGE
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           PosNr;                        /* Positionsnummer Kundenauftrag */
	long           MengeBestellt;                /* Menge Bestellt */
	long           MengeBestaetigt;              /* Menge Bestaetigt */
	long           Menge_Alt;                    /* Menge Bestaetigt orig */
	char           SWChecked;                    /* State of Change*/
};

/*****************************************************************************/
/*  ArticleCodes     Table                                                   */
/*****************************************************************************/

struct tARTICLECODES
{
	long           ArticleNo;                    /* Articleno*/
	short          Code_Type;                    /* CodeType*/
	char           Article_Code[25+1];           /* ArticleCode*/
	short          Preferred_Flag;               /* PreferredFlag*/
};

/*****************************************************************************/
/*  KdAuftragproLink                                                         */
/*****************************************************************************/

struct tKDAUFTRAGPROLINK
{
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	char           InvoiceNumberPro[15+1];       /* Proforma Rechnungsnummer*/
	char           InvoiceNumber[15+1];          /* Rechnungsnummer*/
	long           DateProforma;                 /* Date Proforma Order*/
	long           KdAuftragNrPro;               /* Auftrag Nummer Proforma */

};

/*****************************************************************************/
/*  TenderCustomer                                                           */
/*****************************************************************************/

struct tTENDERCUSTOMER
{
	long           TenderNo;                     /* TenderNo(RS/BG)*/
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
};

/*****************************************************************************/
/*  Encloserscale                                                            */
/*****************************************************************************/

struct tENCLOSERSCALE
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	short          TimeDiff;                     /* TimeDiff */
	short          MaxPositions;                 /* MaxPositions*/
};

/*****************************************************************************/
/*  PromotionQuota                                                           */
/*****************************************************************************/

struct tPROMOTIONQUOTA
{
	short          BranchNo;                     /* Filialnummer */
	short          Promotion_No;                 /* PromotionNo*/
	long           BranchQuotaQty;               /* BranchQuotaQty*/
	long           CustomerQuotaQty;             /* CustomeQuotaQty*/
	long           SoldQtyBranch;                /* SoldQtyBranch*/
	char           Upd_Flag;                     /* Update Flag*/
	long           ArticleNo;                    /* Articleno*/
	long           CustomerMinQty;               /* CustomerMinQuantity*/
};

/*****************************************************************************/
/*  PromotionQuotaCst                                                        */
/*****************************************************************************/

struct tPROMOTIONQUOTACST
{
	short          BranchNo;                     /* Filialnummer */
	short          Promotion_No;                 /* PromotionNo*/
	long           CustomerQuotaQty;             /* CustomeQuotaQty*/
	long           SoldQtyCst;                   /* SoldQtyCustomer*/
	long           CustomerNo;                   /* Customerno*/
	long           ArticleNo;                    /* Articleno*/
};

/*****************************************************************************/
/*  PromotionQuotaCst                                                        */
/*****************************************************************************/

struct tCUSTOMERSURCHARGE
{
	short          BranchNo;                     /* Filialnummer */
	long           CustomerNo;                   /* Customerno*/
	long           ManufacturerNo;               /* manufacturerno*/
	double         SurchargePct;                 /* Zuschlag percentage*/
};

/*****************************************************************************/
/*  VARTIKELLOKAL  View für Verbund                                          */
/*****************************************************************************/

struct tVARTIKELLOKAL
{
	short          FilialNr;                     /* Filialnummer */
	long           ArtikelNr;                    /* Artikelnummer */
	long           Bestand;                      /* Bestand */
	char           Artikelaktiv;                 /* Kz Artikel Aktiv */
	char           VerbundArtikel;               /* Verbund Artikel */
	short 		   NLevelIBTTypeID;				 /* Verbundtyp N-Level-Verbund */
	short 		   IBTQtyAvailabilityPercentage; /* N-Level-Availability-Percentage */
};

/*****************************************************************************/
/*   Manufacturergroup                                                       */
/*****************************************************************************/

struct tMANUFACTURERGROUP
{
	char           PharmacyGroupID[3+1];         /* Einkaufsgruppe */
	long           KonsigPartnerNr;              /* Konsignationspartnernummer*/
};

/*****************************************************************************/
/*   TagPlan                                                       */
/*****************************************************************************/

struct tTAGPLAN
{
	short 			FilialNr;					/* Filialnummer */
	long 			Datum;						/* Datum */
	long 			Rufzeit;					/* Uhrzeit Anruf */
	short 			LfdAktion;					/* Aktuelle Aktion */
	short 			Prioritaet;					/* Prioritaet */
	char   			Wochentag[2+1];				/* Wochentag MO DI ..*/
	short 			PoolId;						/* Anrufer Pool */
	char   			AnrufArt[2+1];				/* Art des Anrufs */
	char   			Manuell[1+1];				/* Manuell */
	char   			STagRueckruf[1+1];			/* Rueckruf */
	short 			Zugriff;					/* ??? */
	char   			Bemerkung[240+1];			/* Bemerkung */
	char   			CallInfo[240+1];			/* Information zum Ruf */
};

/*****************************************************************************/
/*   TagPlan                                                       */
/*****************************************************************************/

struct tTAGPLANEREIGNIS
{
	long 			Datum;						/* Datum */
	long 			Rufzeit;					/* Uhrzeit Anruf */
	long 			IdfNr;						/* IDF des Kunden */
	short 			LfdAktion;					/* Aktuelle Aktion */
	long 			Status;						/* aktueller Status des Anrufs */
	short 			StatusAnrufsatz;			/* aktueller Status des Anrufs */
	short 			LoeschGrund;				/* Loesch Grund */
	long 			RufzeitGeaendert;			/* Zeit der Rufzeitaenderung */
	long 			Zeit;						/* Zeit */
	long 			UID;						/* Nummer des Bearbeiters */
	char   			Bemerkung[240+1];			/* Bemerkung */
	short 			FilialNr;					/* Filialnummer */

};

/*****************************************************************************/
/*                            SMTPDebtMail                                   */
/*****************************************************************************/
struct tCREMAMAIL
{
	long  PARTNERNO;
	long  ID;
	char    SERVER[51];
	short  EMAILTYPE;
	long  SMTPID;
	long  SMTPUSERGROUPID;
	long  TYPEDATAID;
	short  TYPE;
	double   THRESHOLDAMOUNT;
	double   DLPERCENTAGE;
	short  LEVELTYPE;
	double   LIMIT;
	short  REASONTYPE;
	long  TYPEID;
	long  IDFNR;
	short  SENDGVLMAIL;
	long  PORT;
	char    SENTFROMADDRESS[51];
	short  APPROVALPERSONSNEEDED;
	long  KDAUFTRAGNR;
	char    SENTTOADDRESS[51];
	char    GUID[37];
	char  URL[255];
	char  WASSEND;
	long  SENDDATE;
	long  CREMATYPEID;
	short  BRANCHNO;
	long SENDTIME;
	double   WERTAUFTRAG;
};

/*****************************************************************************/
/*                            KdauftragDebtRel                               */
/*****************************************************************************/
struct tKDAUFTRAGDEBTREL
{
	long  KdAuftragNr;
	char    RelReason[241];
	char    RelComment[241];
	char    RelUser[31];
	short  IsReleased;
	long  RelCounter;
	short  ApprovalCounter;
	short  CancelCounter;
	double DebtLimit;
	double UsedDebtLimit;
	double OrderValue;
	short DiscussionNeeded;
};

/*****************************************************************************/
/*  PromotionScale Table                                                     */
/*****************************************************************************/

struct tPROMOTIONSCALE
{
	long           BasePromotion;                /* BasePromotion Number*/
	short          Promotion_No;                 /* Promotion Number*/
};

/*****************************************************************************/
/*  OrderRemarkTypes  Table                                                  */
/*****************************************************************************/
struct tORDERREMARKTYPES
{
	short 			RemarkType;
	short 			Level;
	char   			RemarkName[50+1];
};

/*****************************************************************************/
/*  OrderRemarks  Table                                                      */
/*****************************************************************************/
struct tORDERREMARKS
{
	long 			CSCOrderNo;
	long 			PositionNo;
	short 			RemarkType;
	short 			TextNumber;
	char   			RemarkText[250+1];
};

/*****************************************************************************/
/*  Customergroup  Table                                                     */
/*****************************************************************************/
struct tCUSTOMERGROUP
{
	short 			BranchNo;
	short 			CustomerGroupNo;
	char   			Name[30+1];
	char   			Sales_Restr_PH[16+1];
	short 			Block_Flag;
	short 			BasisNatra_Flag;
	char 			UPD_Flag;
};

/*****************************************************************************/
/*  Customergrpflags  Table                                                  */
/*****************************************************************************/
struct tCUSTOMERGRPFLAGS
{
	short 			BranchNo;
	short 			CustomerGroupNo;
	short 			CustGrpFlagType;
	short 			CustomerGrpFlag;
	char 			UPD_Flag;
};

/*****************************************************************************/
/*  Custgrpflagtypes  Table                                                  */
/*****************************************************************************/
struct tCUSTGRPFLAGTYPES
{
	short 			BranchNo;
	short 			CustGrpFlagType;
	char   			Description[254+1];
	short 			Index_DKKGR;
	char 			UPD_Flag;
};

/*****************************************************************************/
/*  Oeorigintypes  Table                                                     */
/*****************************************************************************/
struct tOEORIGINTYPES
{
	short 			OriginType;
	char   			OriginDevice[20+1];
};

/*****************************************************************************/
/*  Oerestrictiontypes  Table                                                */
/*****************************************************************************/
struct tOERESTRICTIONTYPES
{
	short 			RestrictionType;
	char   			RestrictionName[254+1];
};

/*****************************************************************************/
/*  Orderentryrestrictions   Table                                           */
/*****************************************************************************/
struct tORDERENTRYRESTRICTIONS
{
	short 			BranchNo;
	short 			RestrictionType;
	short 			RestrictionValue;
	short 			OriginType;
};



/*****************************************************************************/
struct tCUSTOMERTOUR
{
	long 			CustomerNo;
	long 			PickingDate;
	char   			TourId[6+1];
	long 			DrivingDuration;
	unsigned char	IsIBTTour;
	short 			BranchNo;
	unsigned char	Disabled;
	short 			TransitionTime;
	unsigned char	AutoAssignable;
	char   			OrderType[2+1];
	short 			TourTransitionTime;
	short 			WeekDay;
	long 			TimeEndOfPicking;
	short 			IsCoolTour;
	short 			IsCoolBelow8Tour;
	short 			IsCoolBelow20Tour;
	short 			IsNarcoticsTour;
	char 			PickingType;
	short 			DeliveryTimeBuffer;
	long 			LagRechTour;
    short           ReturnsTour;
	short           IsPsychotropicTransportExcluded;
};

/*****************************************************************************/
/*                            EVENTREASON                                    */
/*****************************************************************************/

struct tEVENTREASONS
{
	short          EventCode;                    /* Event code beim Auftragstatus DF*/
	char           EventDescription[254+1];      /* Beschreibung event code*/
};

/*****************************************************************************/
/*  Kundenauftragpos ereignis                                                   */
/*****************************************************************************/

struct tKDAUFTRAGPOSEREIGNIS
{
	long           Datum;                        /* Datum */
	long           KdAuftragNr;                  /* Kunde Auftrag Nummer */
	long           SendId;                       /* SendId*/
	short          PosEreignisArt;               /* Ereignisart */
	long           PosNr;                        /* PosNr*/
	long           UhrZeit;                      /* UhrZeit*/
};

/*****************************************************************************/
/*  ToteINfo   Table                                                */
/*****************************************************************************/
struct tTOTEINFO
{
	long 	ID;
	char    DataInfoType[6];
	long  	ToteNo;
	long  	OrdernoIbt;
	short  	BranchNoIbt;
	long    PickingStartDateTime;
	char    TourID[7];
	short  	BranchNo;
};


/*****************************************************************************/
struct tKDAUFTRAGPOSTOUR
{
	long 			OrderNo;					// kdauftragpostour.kdauftragnr
	long 			LineNo;						// kdauftragpostour.posnr
	short 			DeliveryBranchNo;			// kdauftragpostour.deliverybranchno
	long 			DeliveryDate;				// kdauftragpostour.deliverydate
	short 			DeliveryTime;				// kdauftragpostour.deliverytime
	char   			TourId[6+1];				// kdauftragpostour.tourid
	long 			DepartureDate;				// kdauftragpostour.departuredate
	short 			DepartureTime;				// kdauftragpostour.departuretime
	long 			DrivingDuration;			// kdauftragpostour.drivingduration
	short 			DeliveryTimeBuffer;			// kdauftragpostour.deliverytimebuffer
	char   			IBTTourId[6+1];				// kdauftragpostour.ibttourid
	long 			IBTCustomerNo;				// kdauftragpostour.ibtcustomerno
	short 			IBTType;					// kdauftragpostour.ibttype
	short 			DayIBT;						// kdauftragpostour.dayibt
	long			IBTTourDate;				// kdauftragpostour.ibttourdate
};

/*****************************************************************************/
struct tIBTBRANCHES
{
	long 			ArticleNo;
	short 			BranchNo;
	short 			Priority;
	short 			IBTBranchNo;
	short 			IBTType;
	short 			DayIBT;
	long 			IBTCustomerNo;
	short 			ActiveFlag;
	short 			NLevelIBTTypeID;
	short 			NLevelIBTAssortmentTypeID;
};

/*****************************************************************************/

struct tCUSTOMERBUSINESSHOURS
{
	short Weekday;
	short BranchNo;
	long CustomerNo;
	long BusinesshoursStart;
	long BusinesshoursEnd;
};

/*****************************************************************************/

struct tCUSTOMERSPECIALS
{
	short    BranchNo;
	long     CustomerNo;
	long     UW_IDF;
	char     UW_Tour[6+1];
	short    WeekDay;
	char     Activ;
};

/*****************************************************************************/
/*  OrderRelationNoTypes  Table                                              */
/*****************************************************************************/
struct tORDERRELATIONNOTYPES
{
	short			RelationNoType;
	char   			RelationDescription[255+1];
};

/*****************************************************************************/
/*  OrderRelationNo  Table                                                   */
/*****************************************************************************/
struct tORDERRELATIONNO
{
	long			CSCOrderNo;
	short			RelationNoType;
	long			RelationNo;
};

/*****************************************************************************/
/*  Services  Table                                                          */
/*****************************************************************************/
struct tSERVICES
{
	short			Service_No;
	char			Name[30+1];
	short			ServiceTypeNo;
};

/*****************************************************************************/
struct tEMERGENCYSERVICEPLAN
{
	short BranchNo;
	long CustomerNo;
	long EmergencyServiceDate;
	long EmergencyServiceTimeFrom;
	long EmergencyServiceTimeTo;
	char Remarks[241];
	short DelayedDeliveryForNarcotics;
	short DelayedDeliveryForCoolChain;
	short DelayedDeliveryForCoolBelow8;
	short DelayedDeliveryForCoolBelow20;
};

/*****************************************************************************/
struct tIBTBRANCHARTICLECONFIG
{
	long ArticleNo;
	short BranchNo;
	short IBTTypeID;
	short IBTAssortmentTypeID;
};
/*****************************************************************************/
struct tIBTASSORTMENTTYPE
{
	short IBTAssortmentTypeID;
	char  AssortmentTypeName[20+1];
	short IBTCustomersOnly;
	short IBTPeriodNeeded;
};

#endif
