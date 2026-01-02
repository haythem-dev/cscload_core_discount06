#pragma once
#include "afxcmn.h"

// ArticleOCPReimport dialog

class CArticleOCPReimport : public CDialogEx
{
	DECLARE_DYNAMIC(CArticleOCPReimport)

public:
	CArticleOCPReimport(long importdate, long importtime, CWnd* pParent = NULL);   // standard constructor
	virtual ~CArticleOCPReimport();

	void ResetData();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARTICLE_OCPREIMPORT };
#endif
	afx_msg void OnClickedReImport();
	CButton m_chkOnlyMissingArticles;

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

	struct OCP_IMPORT_FILE
	{
		long IMPORT_DATE = 0;
		long IMPORT_TIME = 0;
		CString IMPORT_DATETIME = "";
		CString IMPORT_ORGFILE = "";
		CString IMPORT_SHWFILE = "";
		long IMPORT_ATTEMPTS = 0;
		long IMPORT_SUCCESS_RECORDS = 0;
		long IMPORT_FAILED_RECORDS = 0;
	};
	long m_lngStagingImportDate;
	long m_lngStagingImportTime;
	CListCtrlEx m_lstReimportFiles;
	std::vector<OCP_IMPORT_FILE*> m_vecImportFiles;

	void ScanImportFiles();
	OCP_IMPORT_FILE* GetImportFile(CString strFile, CString strDateTime);
	void ReloadImportFileStatus(OCP_IMPORT_FILE* pOCP);
};
