#pragma once

class CAeDoc;

class CMAufDef
{
private:
    // in
    bool m_bGebucht;                    // bereits Positionen gebucht
    bool m_bNeuSetzen;                  // erzwingt das Setzen der Auftragsart, bzw daß definieren einer anderen
    bool m_bBemerkungEing;              // Auftragskopftext eingeben
    long m_lBatchschreiben;
    long m_KndNr;                       // Kundennummer
    long m_IdfNr;                       // IDF-nummer
    short m_VzNr;                       // VZ-nummer
    bool m_bMitRab;                     // Kunde hat Rabattkonto
    bool m_bShowCashOrder;
    CAeDoc* m_pDoc;                     // Zeiger auf das Dokument

    // in/out
    bool m_bCashOrder;
    long m_lDatumDelayedDelivery;       // Datum verzögerte Auslieferung
    long m_lValuta;                     // Valutamonate
    long m_lDatumValuta;                // Valutamdatum
    CString m_ABemerkung;               // Auftragsbemerkung
    CString m_Tour;                     // eingestellte Tour
    long m_lDeliveryDate;               // Lieferdatum
    long m_lTenderNo;                   // Tendernummer
    short m_sServType;
    CString m_cZuGrund;                 // Rückstellgründe
    long m_lIVC;                        // IVC-Nummer
    bool m_bNoRabattKonto;
    CString m_AArt;                     // Auftragsart
    CString m_SubType;                  // SubOrderType
    CString m_BuchArt;                  // Buchungsart
    CString m_KommArt;                  // Kommiart

    // out
    double m_dBalance;
    double m_dBalance2;
    long m_lAnzDef;                     // Anzahl der durch Umbuchung verursachten Defekte

    friend class CDAufDef;

public:
    CMAufDef(CAeDoc* ptrDoc);

    // in
    void SetGebucht(bool bGebucht);
    void SetNeuSetzen(bool bNeuSetzen);
    void SetBemerkungEing(bool bBemerkungEing);
    void SetBatchschreiben(long lBatchschreiben);
    void SetKndNr(long kndNr);
    void SetIdfNr(long idfNr);
    void SetVzNr(short vzNr);
    void SetMitRab(bool bMitRab);
    void SetShowCashOrder(bool bShowCashOrder);

    // in/out
    void SetCashOrder(bool bCashOrder);
    void SetDatumDelayedDelivery(long lDatumDelayedDelivery);
    void SetValuta(long lValuta);
    void SetDatumValuta(long lDatumValuta);
    void SetABemerkung(CString aBemerkung);
    void SetTour(CString tour);
    void SetDeliveryDate(long lDeliveryDate);
    void SetTenderNo(long lTenderNo);
    void SetServType(short sServType);
    void SetZuGrund(CString cZuGrund);
    void SetIVC(long lIVC);
    void SetNoRabattKonto(bool bNoRabattKonto);
    void SetAArt(CString AArt);
    void SetSubType(CString SubType);
    void SetBuchArt(CString BuchArt);
    void SetKommArt(CString KommArt);

    const bool& GetCashOrder();
    const long& GetDatumDelayedDelivery();
    const long& GetValuta();
    const long& GetDatumValuta();
    const CString& GetABemerkung();
    const CString& GetTour();
    const long& GetDeliveryDate();
    const long& GetTenderNo();
    const short& GetServType();
    const CString& GetZuGrund();
    const long& GetIVC();
    const bool& GetNoRabattKonto();
    const CString& GetAArt();
    const CString& GetSubType();
    const CString& GetBuchArt();
    const CString& GetKommArt();

    // out
    const double& GetBalance();
    const double& GetBalance2();
    const long& GetAnzDef();

private:
    // in
    CAeDoc* GetDoc();
    const bool& GetGebucht();
    const bool& GetNeuSetzen();
    const bool& GetBemerkungEing();
    const long& GetBatchschreiben();
    const long& GetKndNr();
    const long& GetIdfNr();
    const short& GetVzNr();
    const bool& GetMitRab();
    const bool& GetShowCashOrder();

    // out
    void SetBalance(double dBalance);
    void SetBalance2(double dBalance2);
    void SetAnzDef(long AnzDef);
};
