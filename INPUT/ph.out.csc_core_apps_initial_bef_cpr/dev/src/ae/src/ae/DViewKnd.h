#pragma once

// CDViewKnd-Dialogfeld

class CKREDITLIMIT;

class CDViewKnd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDViewKnd)

public:
    CDViewKnd(CWnd* pParent = NULL);   // Standardkonstruktor
    CDViewKnd(CView* pWview);
    BOOL Create();
    virtual ~CDViewKnd();
    CStatic m_cs_Info;

// Dialogfelddaten
    enum { IDD = IDD_AE_VIEW_KND };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    afx_msg void OnDestroy();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()

public:
    short m_sFilialnr;
    long m_lKndNr;

private:
    CView* m_pView;
    double m_dKLWert1;
    double m_dKLWert2;
//  double m_dKLWert3;
    bool m_bVersion;

protected: //methodes
    void RepositionWindow();
    COLORREF wert_kl1;
    COLORREF wert_kl2;
//  COLORREF wert_kl3;
    COLORREF is_kk;
    COLORREF is_eh;
    COLORREF wert_fv;
    COLORREF wert_kk;
    COLORREF wert_l5;
    COLORREF liz_apo;
    COLORREF liz_btm;

public:
    void InitCreditLimitValues();
    void ResetCreditLimitValues();
    void UpdateCreditLimitValues();

    void SetAndShowCreditLimitValue1(double creditValue);
    void SetAndShowCreditLimitValue2(double creditValue);
//  void SetAndShowCreditLimitValue3(double creditValue);

    double GetCreditLimitValue1();
    double GetCreditLimitValue2();
//  double GetCreditLimitValue3();

    void InitalWerte();

private:
    void ShowCreditLimitLine(const short creditLimitControlNo, CKREDITLIMIT& kl);
    void HideCreditLimitLine(const short creditLimitControlNo);
    void GetCreditLimitControlIds(const short creditLimitControlNo, int& idLabel, int& idValue);
    void ShowCreditLimitValue(double creditValue, const short creditLimitControlNo);
};
