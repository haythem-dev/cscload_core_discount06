#ifndef ARTICLE_OCPSTAGING_H_INCLUDE
#define ARTICLE_OCPSTAGING_H_INCLUDE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CArticleOCPStaging.h : header file
//
#include "OCPStagingDoc.h"
#include <eklibs/hamfcs/hDlg.h>
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>

#define ID_ARTOCPSTAGING_END  ( WM_USER + 20 )
#define ID_ARTOCPSTAGING_NEXT ( 0 )
#define ID_ARTOCPSTAGING_PREV ( 0 )

// ArticleOCPStaging dialog
class CArticleOCPStaging : public CDialogMultiLang
{
public:
	CArticleOCPStaging(CWnd* pParent = NULL);   // standard constructor
	CArticleOCPStaging(CView* pView1, CView* pView2);		 // modeless constructor
	virtual ~CArticleOCPStaging();

	BOOL Create(int fromWhere);
	void GoOn(int fromWhere);
	void OnF2Search();
	BOOL PrimeKeyOfSelectedRecord(long *PrimeKey1, long *PrimeKey2, long *PrimeKey3);
	BOOL PrimeKeyOfNextRecord(long *PrimeKey1, long *PrimeKey2, long *PrimeKey3);
	BOOL PrimeKeyOfPrevRecord(long *PrimeKey1, long *PrimeKey2, long *PrimeKey3);

// Dialog Data
	enum { IDD = IDD_ARTICLE_OCPSTAGING };
	enum { MAX_RECORD_COUNT = 10, MAX_OCP_IMPORT_COUNT = 365, MAX_OCP_ARTICLE_COUNT = 1000 };

	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnChangeOnlyOpenImports();
	afx_msg void OnChangeOCPImport();
	afx_msg void OnArticleCodesSearch();
	afx_msg void OnArticleCodesPrev();
	afx_msg void OnArticleCodesNext();
	afx_msg void OnArticlesSearch();
	afx_msg void OnArticlesPrev();
	afx_msg void OnArticlesNext();
	afx_msg void OnArticlePricesSearch();
	afx_msg void OnArticlePricesPrev();
	afx_msg void OnArticlePricesNext();
	afx_msg void OnArticleFranceSearch();
	afx_msg void OnArticleFrancePrev();
	afx_msg void OnArticleFranceNext();
	afx_msg void OnDblClickListArticleCodes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClickListArticles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClickListArticlePrices(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClickListArticleFrance(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelChangeCmbStagingStatus();
	afx_msg void OnKillFocusEditOCPArticleNo();
	afx_msg void OnClickedValidateRecords();
	afx_msg void OnClickedTransferRecords();
	afx_msg void OnClickedDeleteRecords();
	afx_msg void OnClickedReimportRecords();

	struct COCPIMPORT
	{
		long IMPORT_DATE = 0;
		long IMPORT_TIME = 0;
		CString IMPORT_FILE = "";
		long ARTICLECODE_IMPORT_RECORDS = 0;
		long ARTICLECODE_PROCESSED_RECORDS = 0;
		long ARTICLECODE_OPEN_RECORDS = 0;
		long ARTICLE_IMPORT_RECORDS = 0;
		long ARTICLE_PROCESSED_RECORDS = 0;
		long ARTICLE_OPEN_RECORDS = 0;
		long ARTICLEPRICE_IMPORT_RECORDS = 0;
		long ARTICLEPRICE_PROCESSED_RECORDS = 0;
		long ARTICLEPRICE_OPEN_RECORDS = 0;
		long ARTICLEFRANCE_IMPORT_RECORDS = 0;
		long ARTICLEFRANCE_PROCESSED_RECORDS = 0;
		long ARTICLEFRANCE_OPEN_RECORDS = 0;
	};

	struct COLUMN_TYPES
	{
		int Index;
		char* Columns;
		int Width;
		int Align;
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	// Searchbox events
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()

private:
	void MakeDialog();
	void InitMaintenance();
	void InitListbox(CListCtrlEx* pListbox, COLUMN_TYPES* pColtypes);
	void InitImportStatus();
	void ResetData();
	void ResetView();
	bool LoadArticleCodeData();
	bool LoadArticleData();
	bool LoadArticlePriceData();
	bool LoadArticleFranceData();
	void LoadCurrentArticles();
	int FindCurrentArticleIndex(long articleno);
	long GetCurrentArticleNo(int index);
	long GetArticleCount(long importDate, long importTime);
	void ValidateRecords(bool silent);
	CString ConvertStateToCString(LPSTR state);

	ChDlg m_objDlg;
	COCPStagingDoc m_objDoc;

	CButton	m_btnIDOK;
	CButton	m_btnIDCANCEL;
	ChDlgComboBox m_cmbImport;
	CButton m_chkOnlyOpenImports;
	CStatic m_edtImportInfos;
	CEdit m_edtOCPArticleNo;
	CComboBox m_cmbStagingStatus;

	CListCtrlEx m_lstArticleCodes;
	CStatic     m_edtArticleCodeImportCount;
	CStatic     m_edtArticleCodeProcessCount;
	CStatic     m_edtArticleCodeOpenCount;
	ChDlgButton m_btnArticleCodesPrev;
	ChDlgButton m_btnArticleCodesSearch;
	ChDlgButton m_btnArticleCodesNext;
	long        m_lngArticleCodesStartAt;

	CListCtrlEx m_lstArticles;
	CStatic     m_edtArticleImportCount;
	CStatic     m_edtArticleProcessCount;
	CStatic     m_edtArticleOpenCount;
	ChDlgButton m_btnArticlesPrev;
	ChDlgButton m_btnArticlesSearch;
	ChDlgButton m_btnArticlesNext;
	long        m_lngArticlesStartAt;

	CListCtrlEx m_lstArticlePrices;
	CStatic     m_edtArticlePriceImportCount;
	CStatic     m_edtArticlePriceProcessCount;
	CStatic     m_edtArticlePriceOpenCount;
	ChDlgButton m_btnArticlePricesPrev;
	ChDlgButton m_btnArticlePricesSearch;
	ChDlgButton m_btnArticlePricesNext;
	long        m_lngArticlePricesStartAt;

	CListCtrlEx m_lstArticleFrance;
	CStatic     m_edtArticleFranceImportCount;
	CStatic     m_edtArticleFranceProcessCount;
	CStatic     m_edtArticleFranceOpenCount;
	ChDlgButton m_btnArticleFrancePrev;
	ChDlgButton m_btnArticleFranceSearch;
	ChDlgButton m_btnArticleFranceNext;
	long        m_lngArticleFranceStartAt;

	CView* m_pobjView1;
	CView* m_pobjView2;
	bool m_blnWithoutViews;
	bool m_blnFirstInit;
	int	 m_intFromWhere;
	CString m_strArticleNoFilter;
	CString m_strLastError;
	std::vector<COCPIMPORT*> m_vecOCPImports;
	COCPIMPORT* m_pobjCurrentImport;
	std::vector<long> m_vecCurrentArticles;
	int m_intCurrentArticleIndex;
};
#endif // !defined(ARTICLE_OCPSTAGING_H_INCLUDE)