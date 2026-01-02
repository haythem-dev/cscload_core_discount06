#pragma once
// DAufZlBearb.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAufZlBearb dialog
#include "afxwin.h"

class CDAufZlBearb : public CDialogMultiLang
{
// Construction
public:
    CDAufZlBearb(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_ZL_BEARB };
    CEdit   m_EditNatRab;
    CComboBox m_CBoxBuchStat;
    CEdit   m_EditBemerkung;
    CEdit   m_EditAngefMenge;
    CString m_CArtNr;
    CString m_CBestMenge;
    long    m_AngefMenge;
    CString m_CNatRabMenge;
    CString m_CArtName;
    CString m_CArtEinh;
    CString m_CBemerkung;
    int     m_BuchStat;
    int     m_Plus;         //wenn zugesagt nicht in combobox enthalten ist
    CString m_CVerbundMenge;
    CString m_CVerbundFiliale;
    CString m_CNatRab;
    BOOL    m_bNN;
    long    m_lKndNr;
    CString m_CAufArt;
    CEdit   m_EditPct;
    CString m_CPct;
    CEdit   m_EditPctMan;
    CString m_CPctMan;
    CString m_CCharge;
    int     m_Typ;
    long    m_lTenderNo;
    double  m_dPct;
    long    m_lBestand;
    long    m_lDeliveryqty;
    long    m_lContractqty;
    long    m_lMaxqty;
    BOOL    m_bFixCharge;
    BOOL    m_bChargenExist;    //Chargen vorhanden
    CString m_CArtCode;
    CString m_CPreis;
    short   m_CDiscountMode;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CARTAESEL m_hin;
    long    m_save_AngefMenge;
    long    m_save_BestMenge;
    long    m_save_NatRab;
    CString m_save_CBemerkung;
    CString m_save_CPreis;
    int     m_save_BuchStat;
    int     m_save_Typ;
    BOOL    m_save_bNN;
    CString m_save_CPctMan;
    CString m_save_CCharge;
    BOOL    m_save_bFixCharge;
    CEdit m_EditPreis;
    CComboBox m_Combo_FreePrice;
    CComboBox m_ComboTyp;
    CListCtrl m_List1;

    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEdittext();
    afx_msg void OnChangeEditBestMenge();
    afx_msg void OnSelchangeComboBuchStat();
    virtual void OnOK();
    afx_msg void OnChangeEditNatrab();
    afx_msg void OnChangeEditPreis();
    afx_msg void OnSelchangeComboTyp();
    afx_msg void OnChangeEditPctMan();
    afx_msg void OnRadioBatch();
    afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};
