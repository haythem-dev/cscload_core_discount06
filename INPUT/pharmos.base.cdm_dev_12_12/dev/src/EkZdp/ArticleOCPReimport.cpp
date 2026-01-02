// ArticleOCPReimport.cpp : implementation file
//

#include "stdafx.h"
#include "Ekzdp.h"
#include "ArticleOCPReimport.h"
#include "afxdialogex.h"
#include <libscsvoodoo/libscsvoodoo.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/wunxlocs/UnixSys.h>
#include "GetUnixFiles.h"
// ArticleOCPReimport dialog

IMPLEMENT_DYNAMIC(CArticleOCPReimport, CDialogEx)

CArticleOCPReimport::CArticleOCPReimport(long importdate, long importtime, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ARTICLE_OCPREIMPORT, pParent)
{
	m_lngStagingImportDate = importdate;
	m_lngStagingImportTime = importtime;
}

CArticleOCPReimport::~CArticleOCPReimport()
{
	ResetData();
}

void CArticleOCPReimport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REIMPORT_FILES, m_lstReimportFiles);
	DDX_Control(pDX, IDC_CHK_ONLY_MISSING_ARTICLES, m_chkOnlyMissingArticles);
}

BEGIN_MESSAGE_MAP(CArticleOCPReimport, CDialogEx)

	ON_BN_CLICKED(IDC_BTN_REIMPORT, &CArticleOCPReimport::OnClickedReImport)
END_MESSAGE_MAP()

void CArticleOCPReimport::ResetData()
{
	std::vector<OCP_IMPORT_FILE*>::iterator it;
	while (m_vecImportFiles.size() > 0)
	{
		it = m_vecImportFiles.begin();
		OCP_IMPORT_FILE* pOCP = *it;
		if (pOCP != NULL)
		{
			delete pOCP;
			pOCP = NULL;
		}
		m_vecImportFiles.erase(it);
	}
}

BOOL CArticleOCPReimport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// init the reimport area
	COLUMN_TYPES ImportFilesColumns[] =
	{
		0, "Filename", 250, LVCFMT_LEFT,
		1, "Import DateTime", 120, LVCFMT_LEFT,
		2, "Import Attempts", 100, LVCFMT_LEFT,
		3, "Imported Records", 90, LVCFMT_LEFT,
		4, "Failed Records", 90, LVCFMT_LEFT,
		-1, NULL, 0, 0
	};
	LV_COLUMN lvC;

	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for (COLUMN_TYPES* pType = ImportFilesColumns; pType->Index != -1; pType++)
	{
		lvC.iSubItem = pType->Index;
		lvC.pszText = LPTSTR(pType->Columns);
		lvC.fmt = pType->Align;
		lvC.cx = pType->Width;

		m_lstReimportFiles.InsertColumn(pType->Index, &lvC);
	}
	m_lstReimportFiles.ShowScrollBar(SB_VERT, 0);
	m_lstReimportFiles.SetExtendedStyle(m_lstReimportFiles.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_lstReimportFiles.SetSingleLineSelection();
	m_lstReimportFiles.SetFullRowSel(TRUE);

	ScanImportFiles();

	//default the checkbox for only missing records
	m_chkOnlyMissingArticles.SetCheck(1);
	m_chkOnlyMissingArticles.EnableWindow(FALSE);

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CArticleOCPReimport::ScanImportFiles()
{
	long lngStatus;
	long sqlStatus;
	int  sqlHandle;
	CString sqlQuery;
	int  intPos;
	int  intMode;
	char* chrPath;
	char chrFile[300];
	CString strFileName;
	CString strError;
	CString strPath = "/software/wss/fr/cdm/ws/data/ocp/";
	long import_date;
	long import_time;
	long import_code_cnt;
	long import_article_cnt;
	long import_price_cnt;
	long import_france_cnt;
	long import_attempts;
	long failed_code_cnt;
	long failed_article_cnt;
	long failed_price_cnt;
	long failed_france_cnt;
	int  selItem = -1;
	bool fndItem = false;
	ResetData();

	// Step 1: get the unix filenames directly from server as baseline
	chrPath = (char*)((LPCTSTR)strPath);
	intMode = DIR_DNORM;
	lngStatus = UnxDirEntry(chrPath, chrFile, &intMode);
	if (lngStatus == 0)
	{
		intPos = static_cast<int>(strlen(chrPath));
		while (lngStatus == 0)
		{
			// file name check
			strFileName = CString(chrFile);
			strFileName = strFileName.Mid(intPos);
			// if file is article master data (EPIC3)
			if (strFileName.Find("_ArtMaster_03") >= 0)
			{
				OCP_IMPORT_FILE* pFile = new OCP_IMPORT_FILE();
				pFile->IMPORT_ORGFILE = strFileName;
				if (strFileName.Right(9).CompareNoCase("_imported") == 0)
				{
					// cut the extension
					strFileName = strFileName.Left(strFileName.GetLength() - 9);
				}
				pFile->IMPORT_SHWFILE = strFileName;
				m_vecImportFiles.push_back(pFile);
			}
			lngStatus = UnxDirEntry(NULL, chrFile, &intMode);
		}
	}
	else
	{
		MessageBox("Cannot scan import file path on server", "Import file Scan", MB_OK);
	}

	//Step 2: scan the infos from last import for these found files
	std::vector<OCP_IMPORT_FILE*>::iterator it;
	for (it = m_vecImportFiles.begin(); it != m_vecImportFiles.end(); it++)
	{
		OCP_IMPORT_FILE* pOCP = *it;
		if (pOCP != NULL)
		{
			// enhance the import status infos
			sqlQuery = "SELECT import_date, import_time, import_code_records, import_article_records, import_price_records, import_france_records, ";
			sqlQuery += "import_attempt, failed_code_records, failed_article_records, failed_price_records, failed_france_records ";
			sqlQuery += "FROM cocp_stagein_status WHERE import_file = '" + pOCP->IMPORT_SHWFILE + "' ORDER BY import_date desc, import_time desc";
			sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
			if (sqlStatus != SQL_SUCCESS)
			{
				strError = DynErrmld();
				MsgBoxOK(strError);
				return;
			}
			import_date = 0;
			import_time = 0;
			import_code_cnt = 0;
			import_article_cnt = 0;
			import_price_cnt = 0;
			import_france_cnt = 0;
			import_attempts = -1;
			failed_code_cnt = 0;
			failed_article_cnt = 0;
			failed_price_cnt = 0;
			failed_france_cnt = 0;
			sqlStatus = SqlFetch(sqlHandle, 1, &import_date, &import_time, &import_code_cnt, &import_article_cnt, &import_price_cnt, &import_france_cnt, 
				&import_attempts, &failed_code_cnt, &failed_article_cnt, &failed_price_cnt, &failed_france_cnt, NULL);
			SqlCloseCs(sqlHandle);
			// transfer it into the structure (either default values or received values from DB)
			pOCP->IMPORT_DATE = import_date;
			pOCP->IMPORT_TIME = import_time;
			pOCP->IMPORT_SUCCESS_RECORDS = import_code_cnt + import_article_cnt + import_price_cnt + import_france_cnt;
			pOCP->IMPORT_FAILED_RECORDS = failed_code_cnt + failed_article_cnt + failed_price_cnt + failed_france_cnt;
			pOCP->IMPORT_ATTEMPTS = import_attempts;

			// add it into the list box on view
			selItem++; // as the list is backward, the selitem has to move with 
			int nItem = m_lstReimportFiles.InsertItem(0, pOCP->IMPORT_SHWFILE);
			char itemText[30];
			if (pOCP->IMPORT_DATE > 0)
			{
				sprintf(itemText, "%.2ld.%.2ld.%.4ld %.2ld:%.2ld:%.2ld", pOCP->IMPORT_DATE % 100, (pOCP->IMPORT_DATE % 10000) / 100, pOCP->IMPORT_DATE / 10000,
					pOCP->IMPORT_TIME / 10000, (pOCP->IMPORT_TIME % 10000) / 100, pOCP->IMPORT_TIME % 100);
				pOCP->IMPORT_DATETIME = CString(itemText);
				if ((m_lngStagingImportDate > 0) && (m_lngStagingImportDate == pOCP->IMPORT_DATE) && (m_lngStagingImportTime == pOCP->IMPORT_TIME))
				{
					// preselect the staging entry
					selItem = nItem;
					fndItem = true;
				}
			}
			else
			{
				sprintf(itemText, "-");
			}
			m_lstReimportFiles.SetItemText(nItem, 1, itemText);
			if (pOCP->IMPORT_ATTEMPTS >= 0)
			{
				sprintf(itemText, "%ld", pOCP->IMPORT_ATTEMPTS);
			}
			else
			{
				sprintf(itemText, "-");
			}
			m_lstReimportFiles.SetItemText(nItem, 2, itemText);
			sprintf(itemText, "%ld", pOCP->IMPORT_SUCCESS_RECORDS);
			m_lstReimportFiles.SetItemText(nItem, 3, itemText);
			sprintf(itemText, "%ld", pOCP->IMPORT_FAILED_RECORDS);
			m_lstReimportFiles.SetItemText(nItem, 4, itemText);
		}
	}
	if ((fndItem == true) && (selItem >= 0) && (selItem < m_lstReimportFiles.GetItemCount()))
	{
		m_lstReimportFiles.EnsureVisible(selItem, FALSE);
		m_lstReimportFiles.SetFocus();
		m_lstReimportFiles.SetItemState(selItem, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	}
}

void CArticleOCPReimport::OnClickedReImport()
{
	OCP_IMPORT_FILE* pOCP = NULL;
	int row = m_lstReimportFiles.GetSelectionMark();
	if (row >= 0)
	{
		// get the current selection
		CString strImportFile = m_lstReimportFiles.GetItemText(row, 0);
		CString strDateTimeText = m_lstReimportFiles.GetItemText(row, 1);
		pOCP = GetImportFile(strImportFile, strDateTimeText);
	}
	if (pOCP != NULL)
	{
		// remote call server program UNIX
		long lngStatus = 0;
		CString strUnixPathBin;
		CString strStatus;
		CString strDateTime;
		CGetUnixFiles gU;
		char chrCmd[251];
		char chrRec[251];
		int intLen = 0;

		// convert datetime to one string
		strDateTime.Format("%ld%ld", pOCP->IMPORT_DATE, pOCP->IMPORT_TIME);

		// get bin directory
		((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
		lngStatus = gU.GetWWSDateiUnterVerz(strUnixPathBin, bin, strStatus);
		if (lngStatus != 0)
		{
			MsgBoxOK(strStatus);
			return;
		}
		((CEkZdpApp*)AfxGetApp())->EndWaitAction();
		// the real binary is called by e.g. importocp.bin -db ifr21@zdev21_shm -log -inputcsv 'filename.txt' -datetime '20230621195300' -inexdb
		// but we have implemented to be called via a script to handle all unix environment variables correctly by e.g. reimportocp.sh -start -inputcsv filename.txt -datetime 20230621195300
		memset(chrRec, 0, 250);
		sprintf(chrCmd, "%s../proc/reimportocp.sh -start -inputcsv %s -datetime %s                                     \0",
			strUnixPathBin.GetString(),
			pOCP->IMPORT_ORGFILE.GetString(),
			strDateTime.GetString()
		);
		((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
		// execute binary with transfer of selected import date and time
		lngStatus = UnxPipwSystem(chrCmd, "", chrRec, &intLen);
		((CEkZdpApp*)AfxGetApp())->EndWaitAction();

		chrCmd[intLen] = '\0';

		if (lngStatus < 0 || intLen == 0)
		{
			strStatus = DynErrmld();
		}
		else
		{
			strStatus = chrRec;
		}
		if (strStatus.GetLength() > 0)
		{
			// there was an error in executing the unix part
			MsgBoxOK(strStatus);
			if (lngStatus == 0)
			{
				lngStatus = 1;
			}
		}
		if (lngStatus == 0)
		{
			// everything done, so check new counts and show a summary
			long lngOldSuccessRecords = pOCP->IMPORT_SUCCESS_RECORDS;
			long lngOldFailedRecords = pOCP->IMPORT_FAILED_RECORDS;
			// reload the status information for this entry
			ReloadImportFileStatus(pOCP);
			long lngNewSuccessRecords = pOCP->IMPORT_SUCCESS_RECORDS;
			long lngNewFailedRecords = pOCP->IMPORT_FAILED_RECORDS;
			CString msg;
			msg.Format("Re-Import Completed:\n"
				"Total Records in File before: %ld, after: %ld\n"
				"Successfully imported records before: %ld, after: %ld\n"
				"Failed to import records before: %ld, after: %ld\n",
				lngOldSuccessRecords + lngOldFailedRecords, lngNewSuccessRecords + lngNewFailedRecords,
				lngOldSuccessRecords, lngNewSuccessRecords,
				lngOldFailedRecords, lngNewFailedRecords);
			MessageBox(msg, "Re-Import Result", MB_OK);
			m_lngStagingImportDate = pOCP->IMPORT_DATE;
			m_lngStagingImportTime = pOCP->IMPORT_TIME;
			ScanImportFiles();
		}
	}
	else
	{
		MessageBox("Please select an OCP import for re-import!", "Re-Import Error", MB_OK);
	}
}

CArticleOCPReimport::OCP_IMPORT_FILE* CArticleOCPReimport::GetImportFile(CString strFile, CString strDateTime)
{
	OCP_IMPORT_FILE* ret = NULL;

	std::vector<OCP_IMPORT_FILE*>::iterator it = m_vecImportFiles.begin();
	bool fnd = false;

	while ((fnd == false) && (it != m_vecImportFiles.end()))
	{
		OCP_IMPORT_FILE* pOCP = *it;
		if (pOCP != NULL)
		{
			if ((pOCP->IMPORT_SHWFILE.CompareNoCase(strFile) == 0) &&
				(pOCP->IMPORT_DATETIME.CompareNoCase(strDateTime) == 0))
			{
				fnd = true;
				ret = pOCP;
			}
		}
		it++;
	}
	return ret;
}

void CArticleOCPReimport::ReloadImportFileStatus(OCP_IMPORT_FILE* pOCP)
{
	if (pOCP != NULL)
	{
		long sqlStatus;
		int  sqlHandle;
		CString sqlQuery;
		CString strError;
		long import_date;
		long import_time;
		long import_code_cnt;
		long import_article_cnt;
		long import_price_cnt;
		long import_france_cnt;
		long import_attempts;
		long failed_code_cnt;
		long failed_article_cnt;
		long failed_price_cnt;
		long failed_france_cnt;
		CString strDate, strTime;
		strDate.Format("%ld", pOCP->IMPORT_DATE);
		strTime.Format("%ld", pOCP->IMPORT_TIME);
		// reload the import status infos
		sqlQuery = "SELECT import_date, import_time, import_code_records, import_article_records, import_price_records, import_france_records, ";
		sqlQuery += "import_attempt, failed_code_records, failed_article_records, failed_price_records, failed_france_records ";
		sqlQuery += "FROM cocp_stagein_status WHERE import_file = '" + pOCP->IMPORT_SHWFILE + "' AND import_date=" + strDate + " AND import_time=" + strTime;
		sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
		if (sqlStatus != SQL_SUCCESS)
		{
			strError = DynErrmld();
			MsgBoxOK(strError);
			return;
		}
		import_date = 0;
		import_time = 0;
		import_code_cnt = 0;
		import_article_cnt = 0;
		import_price_cnt = 0;
		import_france_cnt = 0;
		import_attempts = -1;
		failed_code_cnt = 0;
		failed_article_cnt = 0;
		failed_price_cnt = 0;
		failed_france_cnt = 0;
		sqlStatus = SqlFetch(sqlHandle, 1, &import_date, &import_time, &import_code_cnt, &import_article_cnt, &import_price_cnt, &import_france_cnt,
			&import_attempts, &failed_code_cnt, &failed_article_cnt, &failed_price_cnt, &failed_france_cnt, NULL);
		SqlCloseCs(sqlHandle);
		// transfer it into the existing structure (either default values or received values from DB)
		pOCP->IMPORT_DATE = import_date;
		pOCP->IMPORT_TIME = import_time;
		pOCP->IMPORT_SUCCESS_RECORDS = import_code_cnt + import_article_cnt + import_price_cnt + import_france_cnt;
		pOCP->IMPORT_FAILED_RECORDS = failed_code_cnt + failed_article_cnt + failed_price_cnt + failed_france_cnt;
		pOCP->IMPORT_ATTEMPTS = import_attempts;
	}
}
