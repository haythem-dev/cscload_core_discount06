#include <list>
#include <vector>
#include "ppgenercpp.h"
using namespace std;
// DWannauswahl.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class ppNTubPosition : public ppGBaseUniqueNumber
{
public:
    ppNTubPosition() {}
    ppString Lager_ort;
    long Pos_nr;
    virtual bool operator ==(const ppNTubPosition& x) const { return ( Number == x.Number && Lager_ort == x.Lager_ort); }
    virtual bool operator !=(const ppNTubPosition& x) const { return !(*this == x); }
    virtual bool operator  <(const ppNTubPosition& x) const { return ( Number < x.Number || (Number == x.Number && Lager_ort < x.Lager_ort) ); }
    virtual bool operator  >(const ppNTubPosition& x) const { return ( Number > x.Number || (Number == x.Number && Lager_ort > x.Lager_ort) ); }
};

struct ppNTubPositionCompare : greater<ppNTubPosition>
{
    bool operator() (const ppNTubPosition& x, const ppNTubPosition& y) const
    {
        return (x.Number > y.Number);
    }
};

class CDWannauswahl : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDWannauswahl(CWnd* pParent = NULL);   // standard constructor
    CImageList m_ImageSmall;
    long m_datum;
    CString m_Datum;
    CString m_IDF_Nr;
    CString m_Wertig;
    CString m_Inhaber;
    CString m_Apotheke;
    CString m_PLZ;
    CString m_Kndtext;
    CString m_Ort;
    CString m_Tel;
    CString m_Tel_KW;
    CString m_Dafue_Typ;
    CString m_Zln;
    CString m_AW;
    CString m_Lif_Wert;
    CString m_Dzw;
    CString m_AA;
    CString m_BA;
    CString m_KA;
    CString m_Auftr_Nr;
    CString m_Tour;
    CString m_Rech_Nr;
    CString m_LA_Nr;
    CString m_Lauft_Nr;
    CString m_Bemerk;
    CString m_Vsenr;

    CListCtrl m_ListCtl;
    vector <AUFPOSBUCH> *m_lAuf;
    vector <AUFPOSBUCH>::iterator it;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    BOOL FillList();                        // List-Box mit Eintraegen versorgen
    list <ppNTubPosition> m_Wann;
    list <ppNTubPosition>::iterator wann_it;
    CDruckAuftrag m_DruckAuftrag;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg void OnButtonAll();
    afx_msg void OnButtonSelected();
    afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonAnzSeite();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);

    void SetMarked(int pos);
    void DelMarked(int pos);
    void Druck(int pos);

    enum { IDD = IDD_AE_WANN_AUSWAHL };

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDWannAnz dialog

class CDWannAnz : public CDialogMultiLang
{
// Construction
public:
    CDWannAnz(CWnd* pParent = NULL);   // standard constructor
    struct ANZ
    {
        char LAGERORT[8+1];
        long MENGEBESTELLT;
        long MENGE;
        char EINHEIT[9 + 1];
        char DARREICHFORM[3 + 1];
        char ARTIKEL_NAME[30 + 1];
        char ARTICLE_CODE[13 + 1];
        long ARTIKEL_NR;
        long POSNR;
        char BEMERKUNG[240 + 1];
    };

    vector <ANZ> m_lAuf;
    vector <ANZ>::iterator it;

    CListCtrl m_ListCtl;
    CString m_CAufNr;
    CString m_CSeite;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    virtual BOOL OnInitDialog();

    enum { IDD = IDD_AE_WANN_ANZ };

    DECLARE_MESSAGE_MAP()
};
