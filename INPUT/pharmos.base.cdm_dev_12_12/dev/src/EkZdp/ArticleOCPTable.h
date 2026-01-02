#pragma once
#include "afxcmn.h"
#include "OCPStagingDoc.h"

// ArticleOCPTableDlg dialog

class CArticleOCPTable : public CDialogEx
{
	DECLARE_DYNAMIC(CArticleOCPTable)

public:
	CArticleOCPTable(COCPStagingDoc* pDoc, int tabletype, CWnd* pParent = NULL);   // standard constructor
	virtual ~CArticleOCPTable();

	void ResetData();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARTICLE_OCPTABLE };
#endif

	afx_msg void OnClickedReloadRecords();
	afx_msg void OnClickedSaveRecords();
	afx_msg void OnClickedSetRecordPreferred();
	afx_msg void OnDblClickListArticleDetailRecords(NMHDR* pNMHDR, LRESULT* pResult);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	struct COLUMN_TYPES
	{
		int Index;
		char* Columns;
		int Width;
		int Align;
	};

	void FillRecords();

	CStatic			m_edtZDPRecordCount;
	CStatic			m_edtOCPRecordCount;
	COCPStagingDoc* m_pobjDoc;
	int				m_intTableType;
	CListCtrlEx		m_lstArticleDetailRecords;
};
