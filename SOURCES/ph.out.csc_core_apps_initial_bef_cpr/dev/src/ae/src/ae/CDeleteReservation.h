#pragma once

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#include "artikel.h"

class CSTOCKRESERVATION;

class CDeleteReservation : public CDialogMultiLang
{

    DECLARE_DYNAMIC(CDeleteReservation)
public:
    CDeleteReservation(CWnd* pParent = NULL);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DELETERESERVATION };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedButtonSearch();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnBnClickedButtonSelectCustomer();

    // Fill the list entries in Reservations using current settings from m_CstockReservation_Search
    void ResetSearchCriteria();
    void ResetDeleteCriteria();
    void GetPage();     

private:
    enum OrderState
    {
        OrderDoesNotExist,
        OrderIsActive,
        OrderIsStorno,
        OrderWasAbandoned,
        OrderIsCompleted
    };

    enum IbtProcessState
    {
        Open,
        ReadyForProcessing,
        Processed
    };

    CListCtrl     m_ListCtlReservations;
    CDateTimeCtrl m_DateFrom;
    CDateTimeCtrl m_DateTo;
    CComboBox     m_ComboBranch;
    CEdit         m_EditCustomerIDF;
    CEdit         m_EditOrderNo;
    CEdit         m_EditArticleNo;
    CComboBox     m_ComboReserveTypeBox;
    BOOL          m_init;

    CStringArray  m_BranchNames;
    CStringArray  m_ReserveTypeNames;

    // store current customer selection, we might need these detailed parameters later
    long m_IdfNr;
    long m_KndNr;
    BOOL m_KzAeGesperrt;
    short m_VzNr;

    CSTOCKRESERVATION m_stockreservation;           // current selected item
    CSTOCKRESERVATIONNACHLIEFERPOS m_nachlieferpos; // last nachlieferpos, could be more than one
    CSTOCKRESERVATIONARTICLERESERV m_articlereserv; // corresponding reserved article stock
    CSTOCKRESERVATIONARTIKELLOKAL m_artikellokal;   // corresponding local article stock
    CSTOCKRESERVATIONIBTREQUEST m_ibtrequest;       // corresponding ibt request
    CSTOCKRESERVATIONORDER m_order;                 // corresponging order (kdauftrag)
    CSTOCKRESERVATION m_CstockReservation_Search;   // own Server for Search to keep current selection active for update of table after delete
    CSTOCKRESERVATION m_CstockReservation_Delete;   // selections and delete for specific item on seconde delete server
};
 