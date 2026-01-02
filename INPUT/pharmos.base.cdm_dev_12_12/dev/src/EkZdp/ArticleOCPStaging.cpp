// ArticleOCPStaging.cpp : implementation file
//

#include "stdafx.h"
#include "Ekzdp.h"
#include "ArticleOCPStaging.h"
#include "ArticleOCPReimport.h"
#include "afxdialogex.h"
#include <libscsvoodoo/libscsvoodoo.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/wunxlocs/UnixSys.h>
#include "GetUnixFiles.h"
//#include <hdatum/phodate.h>
#include "MenuNumbers.h"
//#include "ServerDatum.h"

// ArticleOCPStaging dialog

CArticleOCPStaging::CArticleOCPStaging(CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(IDD_ARTICLE_OCPSTAGING, pParent)
{
	m_strLastError = "";
	m_blnFirstInit = true;
	m_blnWithoutViews = true;
	m_pobjCurrentImport = NULL;
	m_lngArticleCodesStartAt = 0;
	m_lngArticlesStartAt = 0;
	m_lngArticlePricesStartAt = 0;
	m_lngArticleFranceStartAt = 0;
	m_strArticleNoFilter = "";
	m_vecCurrentArticles.clear();
	m_intCurrentArticleIndex = -1;
}

CArticleOCPStaging::CArticleOCPStaging(CView* pView1, CView* pView2) // modeless constructor
	: CDialogMultiLang()
{
	m_strLastError = "";
	m_pobjView1 = pView1;
	m_pobjView2 = pView2;
	if ((pView1 == NULL || pView2 == NULL))
	{
		m_blnWithoutViews = true;
	}
	else
	{
		m_blnWithoutViews = false;
	}
	m_blnFirstInit = true;
	MakeDialog();
}

CArticleOCPStaging::~CArticleOCPStaging()
{
	ResetData();
}

void CArticleOCPStaging::DoDataExchange(CDataExchange* pDX)
{
	CDialogMultiLang::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_IMPORTCODES, m_edtArticleCodeImportCount);
	DDX_Control(pDX, IDC_EDIT_PROCESSCODES, m_edtArticleCodeProcessCount);
	DDX_Control(pDX, IDC_EDIT_OPENCODES, m_edtArticleCodeOpenCount);
	DDX_Control(pDX, IDC_BTN_CODES_PREV, m_btnArticleCodesPrev);
	DDX_Control(pDX, IDC_BTN_CODES_SEARCH, m_btnArticleCodesSearch);
	DDX_Control(pDX, IDC_BTN_CODES_NEXT, m_btnArticleCodesNext);

	DDX_Control(pDX, IDC_EDIT_IMPORTARTICLES, m_edtArticleImportCount);
	DDX_Control(pDX, IDC_EDIT_PROCESSARTICLES, m_edtArticleProcessCount);
	DDX_Control(pDX, IDC_EDIT_OPENARTICLES, m_edtArticleOpenCount);
	DDX_Control(pDX, IDC_BTN_ARTICLES_PREV, m_btnArticlesPrev);
	DDX_Control(pDX, IDC_BTN_ARTICLES_SEARCH, m_btnArticlesSearch);
	DDX_Control(pDX, IDC_BTN_ARTICLES_NEXT, m_btnArticlesNext);

	DDX_Control(pDX, IDC_EDIT_IMPORTPRICES, m_edtArticlePriceImportCount);
	DDX_Control(pDX, IDC_EDIT_PROCESSPRICES, m_edtArticlePriceProcessCount);
	DDX_Control(pDX, IDC_EDIT_OPENPRICES, m_edtArticlePriceOpenCount);
	DDX_Control(pDX, IDC_BTN_PRICES_PREV, m_btnArticlePricesPrev);
	DDX_Control(pDX, IDC_BTN_PRICES_SEARCH, m_btnArticlePricesSearch);
	DDX_Control(pDX, IDC_BTN_PRICES_NEXT, m_btnArticlePricesNext);

	DDX_Control(pDX, IDC_EDIT_IMPORTFRANCE, m_edtArticleFranceImportCount);
	DDX_Control(pDX, IDC_EDIT_PROCESSFRANCE, m_edtArticleFranceProcessCount);
	DDX_Control(pDX, IDC_EDIT_OPENFRANCE, m_edtArticleFranceOpenCount);
	DDX_Control(pDX, IDC_BTN_FRANCE_PREV, m_btnArticleFrancePrev);
	DDX_Control(pDX, IDC_BTN_FRANCE_SEARCH, m_btnArticleFranceSearch);
	DDX_Control(pDX, IDC_BTN_FRANCE_NEXT, m_btnArticleFranceNext);

	DDX_Control(pDX, IDOK, m_btnIDOK);
	DDX_Control(pDX, IDCANCEL, m_btnIDCANCEL);
	DDX_Control(pDX, IDC_CHK_ONLYOPENIMPORTS, m_chkOnlyOpenImports);
	DDX_Control(pDX, IDC_CMB_OCPIMPORT, m_cmbImport);
	DDX_Control(pDX, IDC_EDIT_IMPORTINFOS, m_edtImportInfos);
	DDX_Control(pDX, IDC_CMB_STAGINGSTATUS, m_cmbStagingStatus);
	DDX_Control(pDX, IDC_EDIT_OCPARTICLENO, m_edtOCPArticleNo);
	DDX_Control(pDX, IDC_LIST_ARTICLECODES, m_lstArticleCodes);
	DDX_Control(pDX, IDC_LIST_ARTICLES, m_lstArticles);
	DDX_Control(pDX, IDC_LIST_ARTICLEPRICES, m_lstArticlePrices);
	DDX_Control(pDX, IDC_LIST_ARTICLEFRANCE, m_lstArticleFrance);
}

BEGIN_MESSAGE_MAP(CArticleOCPStaging, CDialogMultiLang)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_CHK_ONLYOPENIMPORTS, &CArticleOCPStaging::OnChangeOnlyOpenImports)
	ON_CBN_SELCHANGE(IDC_CMB_OCPIMPORT, &CArticleOCPStaging::OnChangeOCPImport)
	ON_BN_CLICKED(IDC_BTN_CODES_SEARCH, &CArticleOCPStaging::OnArticleCodesSearch)
	ON_BN_CLICKED(IDC_BTN_CODES_PREV, &CArticleOCPStaging::OnArticleCodesPrev)
	ON_BN_CLICKED(IDC_BTN_CODES_NEXT, &CArticleOCPStaging::OnArticleCodesNext)
	ON_BN_CLICKED(IDC_BTN_ARTICLES_SEARCH, &CArticleOCPStaging::OnArticlesSearch)
	ON_BN_CLICKED(IDC_BTN_ARTICLES_PREV, &CArticleOCPStaging::OnArticlesPrev)
	ON_BN_CLICKED(IDC_BTN_ARTICLES_NEXT, &CArticleOCPStaging::OnArticlesNext)
	ON_BN_CLICKED(IDC_BTN_PRICES_SEARCH, &CArticleOCPStaging::OnArticlePricesSearch)
	ON_BN_CLICKED(IDC_BTN_PRICES_PREV, &CArticleOCPStaging::OnArticlePricesPrev)
	ON_BN_CLICKED(IDC_BTN_PRICES_NEXT, &CArticleOCPStaging::OnArticlePricesNext)
	ON_BN_CLICKED(IDC_BTN_FRANCE_SEARCH, &CArticleOCPStaging::OnArticleFranceSearch)
	ON_BN_CLICKED(IDC_BTN_FRANCE_PREV, &CArticleOCPStaging::OnArticleFrancePrev)
	ON_BN_CLICKED(IDC_BTN_FRANCE_NEXT, &CArticleOCPStaging::OnArticleFranceNext)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ARTICLECODES, &CArticleOCPStaging::OnDblClickListArticleCodes)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ARTICLES, &CArticleOCPStaging::OnDblClickListArticles)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ARTICLEPRICES, &CArticleOCPStaging::OnDblClickListArticlePrices)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ARTICLEFRANCE, &CArticleOCPStaging::OnDblClickListArticleFrance)
	ON_CBN_SELCHANGE(IDC_CMB_STAGINGSTATUS, &CArticleOCPStaging::OnSelChangeCmbStagingStatus)
	ON_EN_KILLFOCUS(IDC_EDIT_OCPARTICLENO, &CArticleOCPStaging::OnKillFocusEditOCPArticleNo)
	ON_BN_CLICKED(IDC_BTN_VALIDATERECORDS, &CArticleOCPStaging::OnClickedValidateRecords)
	ON_BN_CLICKED(IDC_BTN_TRANSFERRECORDS, &CArticleOCPStaging::OnClickedTransferRecords)
	ON_BN_CLICKED(IDC_BTN_DELETERECORDS, &CArticleOCPStaging::OnClickedDeleteRecords)
	ON_BN_CLICKED(IDC_BTN_REIMPORTRECORDS, &CArticleOCPStaging::OnClickedReimportRecords)
END_MESSAGE_MAP()

void CArticleOCPStaging::ResetData()
{
	std::vector<COCPIMPORT*>::iterator it;

	m_pobjCurrentImport = NULL;
	m_lngArticleCodesStartAt = 0;
	m_lngArticlesStartAt = 0;
	m_lngArticlePricesStartAt = 0;
	m_lngArticleFranceStartAt = 0;
	while (m_vecOCPImports.size() > 0)
	{
		it = m_vecOCPImports.begin();
		COCPIMPORT* pOCP = *it;
		if (pOCP != NULL)
		{
			delete pOCP;
			pOCP = NULL;
		}
		m_vecOCPImports.erase(it);
	}
	m_vecCurrentArticles.clear();
	m_intCurrentArticleIndex = -1;
}

void CArticleOCPStaging::ResetView()
{
	m_vecCurrentArticles.clear();
	m_intCurrentArticleIndex = -1;

	m_cmbImport.ResetContent();
	m_edtImportInfos.SetWindowText("");
	m_cmbStagingStatus.ResetContent();
	m_edtOCPArticleNo.SetWindowText("");

	m_edtArticleCodeImportCount.SetWindowText("0");
	m_edtArticleCodeProcessCount.SetWindowText("0");
	m_edtArticleCodeOpenCount.SetWindowText("0");
	m_lstArticleCodes.DeleteAllItems();
	m_btnArticleCodesPrev.EnableWindow(FALSE);
	m_btnArticleCodesSearch.EnableWindow(FALSE);
	m_btnArticleCodesNext.EnableWindow(FALSE);

	m_edtArticleImportCount.SetWindowText("0");
	m_edtArticleProcessCount.SetWindowText("0");
	m_edtArticleOpenCount.SetWindowText("0");
	m_lstArticles.DeleteAllItems();
	m_btnArticlesPrev.EnableWindow(FALSE);
	m_btnArticlesSearch.EnableWindow(FALSE);
	m_btnArticlesNext.EnableWindow(FALSE);

	m_edtArticlePriceImportCount.SetWindowText("0");
	m_edtArticlePriceProcessCount.SetWindowText("0");
	m_edtArticlePriceOpenCount.SetWindowText("0");
	m_lstArticlePrices.DeleteAllItems();
	m_btnArticlePricesPrev.EnableWindow(FALSE);
	m_btnArticlePricesSearch.EnableWindow(FALSE);
	m_btnArticlePricesNext.EnableWindow(FALSE);

	m_edtArticleFranceImportCount.SetWindowText("0");
	m_edtArticleFranceProcessCount.SetWindowText("0");
	m_edtArticleFranceOpenCount.SetWindowText("0");
	m_lstArticleFrance.DeleteAllItems();
	m_btnArticleFrancePrev.EnableWindow(FALSE);
	m_btnArticleFranceSearch.EnableWindow(FALSE);
	m_btnArticleFranceNext.EnableWindow(FALSE);
}

////////////////////////////////////////////////////////
// search via F2
void CArticleOCPStaging::OnF2Search()
{
	MessageBox("F2", "F2", MB_OK);
}

class CO_ArticleOCPStaging_Com : public ChComBase
{
public:
	CO_ArticleOCPStaging_Com(CArticleOCPStaging* pView) : ChComBase(pView) {};
	void DoIt(UINT nChar)
	{
		if (nChar == VK_F2)
		{
			((CArticleOCPStaging*)m_pWnd)->OnF2Search();
		}
	}
};

// CArticleOCPStaging message handlers

void CArticleOCPStaging::GoOn(int fromWhere)
{
	ShowWindow(SW_SHOW);
	m_intFromWhere = fromWhere;
}

BOOL CArticleOCPStaging::Create(int fromWhere)	// create on modeless constuctor
{
	BOOL blnOk = CDialogMultiLang::Create(CArticleOCPStaging::IDD);
	if (blnOk == TRUE)
	{
		ShowWindow(SW_SHOW);
	}
	else
	{
		MsgBoxOK(CResString::ex().getStrTblText(IDS_OCPSTAGING_CREATE_ERR));
	}
	m_intFromWhere = fromWhere;
	return blnOk;
}

void CArticleOCPStaging::InitMaintenance()
{
	// init the article code area
	COLUMN_TYPES ArticleCodeColumns[] =
	{
		0, "OCP ArticleNo", 80, LVCFMT_LEFT,
		1, "PHX ArticleNo", 80, LVCFMT_LEFT, 
		2, "Code Type", 100, LVCFMT_LEFT,
		3, "Article Code", 90, LVCFMT_LEFT,
		4, "Import Status", 130, LVCFMT_LEFT,
		-1, NULL, 0, 0
	};
	InitListbox(&m_lstArticleCodes, ArticleCodeColumns);
	m_lstArticleCodes.ShowScrollBar(SB_VERT, 0);
	m_lstArticleCodes.SetExtendedStyle(m_lstArticleCodes.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_lstArticleCodes.SetFullRowSel(TRUE);
	m_btnArticleCodesPrev.SetMask(IDB_BM_RUEBL1, new CBitmap, NULL);
	m_btnArticleCodesSearch.SetMask(IDB_BM_SUCHE1, new CBitmap, NULL);
	m_btnArticleCodesNext.SetMask(IDB_BM_VORBL1, new CBitmap, NULL);

	// init the article area
	COLUMN_TYPES ArticleColumns[] =
	{
		0, "OCP ArticleNo", 80, LVCFMT_LEFT,
		1, "PHX ArticleNo", 80, LVCFMT_LEFT,
		2, "Article Name", 190, LVCFMT_LEFT,
		3, "Import Status", 130, LVCFMT_LEFT,
		-1, NULL, 0, 0
	};
	InitListbox(&m_lstArticles, ArticleColumns);
	m_lstArticles.ShowScrollBar(SB_VERT, 0);
	m_lstArticles.SetExtendedStyle(m_lstArticles.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_lstArticles.SetFullRowSel(TRUE);
	m_btnArticlesPrev.SetMask(IDB_BM_RUEBL1, new CBitmap, NULL);
	m_btnArticlesSearch.SetMask(IDB_BM_SUCHE1, new CBitmap, NULL);
	m_btnArticlesNext.SetMask(IDB_BM_VORBL1, new CBitmap, NULL);

	// init the article price area
	COLUMN_TYPES ArticlePriceColumns[] =
	{
		0, "OCP ArticleNo", 80, LVCFMT_LEFT,
		1, "PHX ArticleNo", 80, LVCFMT_LEFT,
		2, "Valid From", 70, LVCFMT_LEFT,
		3, "Buy Price", 60, LVCFMT_RIGHT,
		4, "Sell Price", 60, LVCFMT_RIGHT,
		5, "Import Status", 130, LVCFMT_LEFT,
		-1, NULL, 0, 0
	};
	InitListbox(&m_lstArticlePrices, ArticlePriceColumns);
	m_lstArticlePrices.ShowScrollBar(SB_VERT, 0);
	m_lstArticlePrices.SetExtendedStyle(m_lstArticlePrices.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_lstArticlePrices.SetFullRowSel(TRUE);
	m_btnArticlePricesPrev.SetMask(IDB_BM_RUEBL1, new CBitmap, NULL);
	m_btnArticlePricesSearch.SetMask(IDB_BM_SUCHE1, new CBitmap, NULL);
	m_btnArticlePricesNext.SetMask(IDB_BM_VORBL1, new CBitmap, NULL);

	// init the article france area
	COLUMN_TYPES ArticleFranceColumns[] =
	{
		0, "OCP ArticleNo", 80, LVCFMT_LEFT,
		1, "PHX ArticleNo", 80, LVCFMT_LEFT,
		2, "ReturnType", 70, LVCFMT_LEFT,
		3, "ReturnVal", 60, LVCFMT_LEFT,
		4, "Return % Index", 60, LVCFMT_LEFT,
		5, "Import Status", 130, LVCFMT_LEFT,
		-1, NULL, 0, 0
	};
	InitListbox(&m_lstArticleFrance, ArticleFranceColumns);
	m_lstArticleFrance.ShowScrollBar(SB_VERT, 0);
	m_lstArticleFrance.SetExtendedStyle(m_lstArticleFrance.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_lstArticleFrance.SetFullRowSel(TRUE);
	m_btnArticleFrancePrev.SetMask(IDB_BM_RUEBL1, new CBitmap, NULL);
	m_btnArticleFranceSearch.SetMask(IDB_BM_SUCHE1, new CBitmap, NULL);
	m_btnArticleFranceNext.SetMask(IDB_BM_VORBL1, new CBitmap, NULL);

	m_chkOnlyOpenImports.SetCheck(1);
	// activate Dialog
	m_objDlg.SetDialog(TRUE);

}

BOOL CArticleOCPStaging::OnInitDialog()
{
	CDialogMultiLang::OnInitDialog();

	InitMaintenance();
	InitImportStatus();

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CArticleOCPStaging::MakeDialog()
{
	m_objDlg.InitDialog(m_btnArticleCodesPrev);
	m_objDlg.InitDialog(m_btnArticleCodesSearch);
	m_objDlg.InitDialog(m_btnArticleCodesNext);

	m_objDlg.InitDialog(m_btnArticlesPrev);
	m_objDlg.InitDialog(m_btnArticlesSearch);
	m_objDlg.InitDialog(m_btnArticlesNext);

	m_objDlg.InitDialog(m_btnArticlePricesPrev);
	m_objDlg.InitDialog(m_btnArticlePricesSearch);
	m_objDlg.InitDialog(m_btnArticlePricesNext);

	m_objDlg.InitDialog(m_btnArticleFrancePrev);
	m_objDlg.InitDialog(m_btnArticleFranceSearch);
	m_objDlg.InitDialog(m_btnArticleFranceNext);

	// prefill list of data for validation once at start
	m_objDoc.GenerateExchangeParams();
}

void CArticleOCPStaging::OnCancel()
{
	if (m_blnWithoutViews == true)
	{
		CDialogMultiLang::OnCancel();
	}
	else
	{
		m_pobjView1->SendMessage(ID_ARTOCPSTAGING_END, IDCANCEL);	// OCPSTAGING_View
	}
}

void CArticleOCPStaging::OnOK()
{
	CWnd *wnd = GetFocus();
	// in case of pressing return decide based on current selected control, what should be done

	if ((wnd == &m_btnIDOK) || (wnd == &m_lstArticleCodes) || (wnd == &m_lstArticles) || (wnd == &m_lstArticlePrices) || (wnd == &m_lstArticleFrance))
	{
		if (m_blnWithoutViews == true)
		{
			CDialogMultiLang::OnOK();
		}
		else
		{
			m_pobjView1->SendMessage(ID_ARTOCPSTAGING_END, IDOK); // OCPSTAGING_View
		}
	}
	else if (wnd == &m_edtOCPArticleNo)
	{
		OnKillFocusEditOCPArticleNo();
	}
}

void CArticleOCPStaging::OnClose()
{
	if (m_blnWithoutViews == true)
	{
		CDialogMultiLang::OnClose();
	}
	else
	{
		m_pobjView2->SendMessage(ID_ARTOCPSTAGING_END, IDCANCEL);	// ARTICLE_View
	}
}

int CArticleOCPStaging::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogMultiLang::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	return 0;
}

void CArticleOCPStaging::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if ((nIDCtl == IDC_PIC_ARTICLECODES) || (nIDCtl == IDC_PIC_ARTICLES) || (nIDCtl == IDC_PIC_ARTICLEPRICES) || (nIDCtl == IDC_PIC_ARTICLEFRANCE))
	{
		CWnd* pItem = GetDlgItem(nIDCtl);
		CDC* pDC = pItem->GetDC();
		CRect rect;
		pItem->GetClientRect(&rect);

		CBrush bru(RGB(119, 183, 119));
		CBrush* pbru = pDC->SelectObject(&bru);
		CPen pen(PS_SOLID, 1, RGB(119, 183, 119));
		CPen* ppen = pDC->SelectObject(&pen);

		pDC->Rectangle(rect);

		pDC->SelectObject(ppen);
		pDC->SelectObject(pbru);

		pItem->ReleaseDC(pDC);
	}
	CDialogMultiLang::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CArticleOCPStaging::InitListbox(CListCtrlEx* pListbox, COLUMN_TYPES* pColtypes)
{
	if ((pListbox == NULL) || (pColtypes == NULL))
	{
		return;
	}
	LV_COLUMN lvC;

	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for (COLUMN_TYPES* pType = pColtypes; pType->Index != -1; pType++)
	{
		lvC.iSubItem = pType->Index;
		lvC.pszText = LPTSTR(pType->Columns);
		lvC.fmt = pType->Align;
		lvC.cx = pType->Width;

		if (pListbox->InsertColumn(pType->Index, &lvC) == -1)
		{
			MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING327));
			return;
		}
	}
}

void CArticleOCPStaging::InitImportStatus()
{
	long sqlStatus;
	int  sqlHandle;
	CString sqlQuery;
	long sqlCount;

	long import_date;
	long import_time;

	bool chkonlyopen = true;
	if (m_chkOnlyOpenImports.GetCheck() == 0)
	{
		chkonlyopen = false;
	}

	// reset everything content wise
	ResetData();
	ResetView();
	m_cmbStagingStatus.AddString("All Status");
	m_cmbStagingStatus.AddString("Not Yet Validated");
	m_cmbStagingStatus.AddString("Validated Successfully");
	m_cmbStagingStatus.AddString("Validated with Errors");
	m_cmbStagingStatus.SetCurSel(0);

	// load all imports
	sqlQuery = "SELECT DISTINCT s.import_date, s.import_time FROM cocp_stagein_status as s ";
	if (chkonlyopen == true)
	{
		sqlQuery += "WHERE (SELECT COUNT(DISTINCT c.import_date) FROM cocp_stagein_articlecode AS c WHERE s.import_date = c.import_date and s.import_time = c.import_time) > 0 ";
		sqlQuery += "OR (SELECT COUNT(DISTINCT a.import_date) FROM cocp_stagein_article AS a WHERE s.import_date = a.import_date and s.import_time = a.import_time) > 0 ";
		sqlQuery += "OR (SELECT COUNT(DISTINCT p.import_date) FROM cocp_stagein_articleprice AS p WHERE s.import_date = p.import_date and s.import_time = p.import_time) > 0 ";
		sqlQuery += "OR (SELECT COUNT(DISTINCT f.import_date) FROM cocp_stagein_article_france AS f WHERE s.import_date = f.import_date and s.import_time = f.import_time) > 0 ";
	}
	sqlQuery += "ORDER BY s.import_date DESC, s.import_time DESC ";

	sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
	if (sqlStatus != SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		MsgBoxOK(m_strLastError);
		return;
	}

	sqlStatus = SqlFetch(sqlHandle, 1, &import_date, &import_time, NULL);
	if (sqlStatus == SQL_NOTFOUND)
	{
		m_strLastError = CResString::ex().getStrTblText(IDS_NO_OCPIMPORT);
		SqlCloseCs(sqlHandle);
		MsgBoxOK(m_strLastError);
		return;
	}

	sqlCount = 0;
	do
	{
		// add into combo box
		char index[30];
		sprintf(index, "%.2ld.%.2ld.%.4ld %.2ld:%.2ld:%.2ld", import_date % 100, (import_date % 10000) / 100, import_date / 10000,
			import_time / 10000, (import_time % 10000) / 100, import_time % 100);
		m_cmbImport.AddString(index);
		// add into vector
		COCPIMPORT* pOCP = new COCPIMPORT();
		pOCP->IMPORT_DATE = import_date;
		pOCP->IMPORT_TIME = import_time;
		m_vecOCPImports.push_back(pOCP);
		// get next
		sqlCount++;
		sqlStatus = SqlFetch(sqlHandle, 1, &import_date, &import_time, NULL);
	} 
	while ((sqlStatus == SQL_SUCCESS) && (sqlCount < MAX_OCP_IMPORT_COUNT));

	if (sqlStatus < SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		SqlCloseCs(sqlHandle);
		MsgBoxOK(m_strLastError);
		return;
	}
	SqlCloseCs(sqlHandle);
}

void CArticleOCPStaging::OnChangeOnlyOpenImports()
{
	//refresh combo box of imports
	InitImportStatus();
}

void CArticleOCPStaging::OnChangeOCPImport()
{
	// reset
	m_lngArticleCodesStartAt = 0;
	m_lngArticlesStartAt = 0;
	m_lngArticlePricesStartAt = 0;
	m_lngArticleFranceStartAt = 0;
	// load the current selection details
	int index = m_cmbImport.GetCurSel();
	if ((index < 0) || (index >= m_vecOCPImports.size()))
	{
		// no valid selection
		return;
	}
	m_pobjCurrentImport = m_vecOCPImports.at(index);
	if (m_pobjCurrentImport == NULL)
	{
		// no valid object
		return;
	}
	// read at first the general status of the selected import
	long sqlStatus;
	int  sqlHandle;
	CString sqlQuery;
	char import_file[51];
	long imp_code_records;
	long imp_article_records;
	long imp_price_records;
	long imp_france_records;
	long db_records;

	sqlQuery += "SELECT import_file, import_code_records, import_article_records, import_price_records, import_france_records ";
	sqlQuery += "FROM cocp_stagein_status WHERE import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE,true) + " AND import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME,true);

	sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
	if (sqlStatus != SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		MsgBoxOK(m_strLastError);
		return;
	}

	sqlStatus = SqlFetch(sqlHandle, 1, &import_file, &imp_code_records, &imp_article_records, &imp_price_records, &imp_france_records, NULL);
	if (sqlStatus == SQL_NOTFOUND)
	{
		m_strLastError = CResString::ex().getStrTblText(IDS_NO_OCPIMPORT_DATA);
		SqlCloseCs(sqlHandle);
		MsgBoxOK(m_strLastError);
		return;
	}
	// show the status details on the screen
	char infos[200];
	sprintf(infos, "file: %s\ndate: %.2ld.%.2ld.%.4ld\ntime: %.2ld:%.2ld:%.2ld", import_file, 
		m_pobjCurrentImport->IMPORT_DATE % 100, (m_pobjCurrentImport->IMPORT_DATE % 10000) / 100, m_pobjCurrentImport->IMPORT_DATE / 10000,
		m_pobjCurrentImport->IMPORT_TIME / 10000, (m_pobjCurrentImport->IMPORT_TIME % 10000) / 100, m_pobjCurrentImport->IMPORT_TIME % 100);
	m_edtImportInfos.SetWindowTextA(infos);
	// store the values into the vector item
	m_pobjCurrentImport->IMPORT_FILE = CString(import_file);
	m_pobjCurrentImport->ARTICLECODE_IMPORT_RECORDS = imp_code_records;
	m_pobjCurrentImport->ARTICLE_IMPORT_RECORDS = imp_article_records;
	m_pobjCurrentImport->ARTICLEPRICE_IMPORT_RECORDS = imp_price_records;
	m_pobjCurrentImport->ARTICLEFRANCE_IMPORT_RECORDS = imp_france_records;

	if (sqlStatus < SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		SqlCloseCs(sqlHandle);
		MsgBoxOK(m_strLastError);
		return;
	}
	SqlCloseCs(sqlHandle);

	// now load the real counts for the records
	sqlQuery = "SELECT CAST(count(*) as INTEGER) from cocp_stagein_articlecode WHERE import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " AND import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true);
	sqlStatus = SqlRead(sqlQuery, &db_records, NULL);
	if (sqlStatus == SQL_SUCCESS)
	{
		m_pobjCurrentImport->ARTICLECODE_OPEN_RECORDS = db_records;
		m_pobjCurrentImport->ARTICLECODE_PROCESSED_RECORDS = m_pobjCurrentImport->ARTICLECODE_IMPORT_RECORDS - db_records;
	}
	m_edtArticleCodeImportCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLECODE_IMPORT_RECORDS, true));
	m_edtArticleCodeProcessCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLECODE_PROCESSED_RECORDS, true));
	m_edtArticleCodeOpenCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLECODE_OPEN_RECORDS, true));
	OnArticleCodesSearch();

	sqlQuery = "SELECT CAST(count(*) as INTEGER) from cocp_stagein_article WHERE import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " AND import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true);
	sqlStatus = SqlRead(sqlQuery, &db_records, NULL);
	if (sqlStatus == SQL_SUCCESS)
	{
		m_pobjCurrentImport->ARTICLE_OPEN_RECORDS = db_records;
		m_pobjCurrentImport->ARTICLE_PROCESSED_RECORDS = m_pobjCurrentImport->ARTICLE_IMPORT_RECORDS - db_records;
	}
	m_edtArticleImportCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLE_IMPORT_RECORDS, true));
	m_edtArticleProcessCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLE_PROCESSED_RECORDS, true));
	m_edtArticleOpenCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLE_OPEN_RECORDS, true));
	OnArticlesSearch();

	sqlQuery = "SELECT CAST(count(*) as INTEGER) from cocp_stagein_articleprice WHERE import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " AND import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true);
	sqlStatus = SqlRead(sqlQuery, &db_records, NULL);
	if (sqlStatus == SQL_SUCCESS)
	{
		m_pobjCurrentImport->ARTICLEPRICE_OPEN_RECORDS = db_records;
		m_pobjCurrentImport->ARTICLEPRICE_PROCESSED_RECORDS = m_pobjCurrentImport->ARTICLEPRICE_IMPORT_RECORDS - db_records;
	}
	m_edtArticlePriceImportCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLEPRICE_IMPORT_RECORDS, true));
	m_edtArticlePriceProcessCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLEPRICE_PROCESSED_RECORDS, true));
	m_edtArticlePriceOpenCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLEPRICE_OPEN_RECORDS, true));
	OnArticlePricesSearch();

	sqlQuery = "SELECT CAST(count(*) as INTEGER) from cocp_stagein_article_france WHERE import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " AND import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true);
	sqlStatus = SqlRead(sqlQuery, &db_records, NULL);
	if (sqlStatus == SQL_SUCCESS)
	{
		m_pobjCurrentImport->ARTICLEFRANCE_OPEN_RECORDS = db_records;
		m_pobjCurrentImport->ARTICLEFRANCE_PROCESSED_RECORDS = m_pobjCurrentImport->ARTICLEFRANCE_IMPORT_RECORDS - db_records;
	}
	m_edtArticleFranceImportCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLEFRANCE_IMPORT_RECORDS, true));
	m_edtArticleFranceProcessCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLEFRANCE_PROCESSED_RECORDS, true));
	m_edtArticleFranceOpenCount.SetWindowText(m_objDoc.ConvertLong2CString(m_pobjCurrentImport->ARTICLEFRANCE_OPEN_RECORDS, true));
	OnArticleFranceSearch();
	// read all distinct article no's for views navigation
	LoadCurrentArticles();
}

void CArticleOCPStaging::OnKillFocusEditOCPArticleNo()
{
	CString strFilter = "";
	m_edtOCPArticleNo.GetWindowText(strFilter);
	if (strFilter.Compare(m_strArticleNoFilter) != 0)
	{
		m_lngArticleCodesStartAt = 0;
		m_lngArticlesStartAt = 0;
		m_lngArticlePricesStartAt = 0;
		m_lngArticleFranceStartAt = 0;

		m_strArticleNoFilter = strFilter;
		OnArticleCodesSearch();
		OnArticlesSearch();
		OnArticlePricesSearch();
		OnArticleFranceSearch();
		LoadCurrentArticles();
	}
}

void CArticleOCPStaging::OnSelChangeCmbStagingStatus()
{
	// auto reload the records with the new filter
	OnArticleCodesSearch();
	OnArticlesSearch();
	OnArticlePricesSearch();
	OnArticleFranceSearch();
	LoadCurrentArticles();
}

bool CArticleOCPStaging::LoadArticleCodeData()
{
	long sqlStatus;
	int  sqlHandle;
	long sqlCount;
	CString sqlSelQuery;
	CString sqlCntQuery;
	CString sqlQuery;
	CString sqlOrdQuery;
	CString strTemp;
	if (m_pobjCurrentImport == NULL)
	{
		return false;
	}
	// get the filters
	CString articleno = "";
	m_edtOCPArticleNo.GetWindowText(articleno);
	int curStatusFilter = m_cmbStagingStatus.GetCurSel();
	// reset the list box
	m_lstArticleCodes.DeleteAllItems();
	// find imported articlecodes
	long        ocpcode_ocparticleno;
	short       ocpcode_codetype;
	char        ocpcode_typename[31];
	char        ocpcode_articlecode[26];
	long		ocpcode_phxarticleno;
	char		ocpcode_sumstateflag[2];
	sqlCntQuery = "SELECT CAST(count(*) as INTEGER) ";
	sqlSelQuery = "SELECT SKIP " + m_objDoc.ConvertLong2CString(m_lngArticleCodesStartAt, true) + " FIRST " + m_objDoc.ConvertLong2CString(MAX_RECORD_COUNT, true) + " ";
	sqlSelQuery += "ci.ocp_article_no, ci.code_type, t.name AS code_type_name, ci.article_code, co.article_no, co.sum_state_flags ";
	sqlQuery = "FROM cocp_stagein_articlecode ci, ccodetypes t, cocp_stageout_articlecode co ";
	sqlQuery += "WHERE ci.import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " ";
	sqlQuery += "AND ci.import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true) + " AND ci.code_type = t.code_type ";
	sqlQuery += "AND ci.ocp_article_no=co.ocp_article_no AND ci.code_type=co.code_type ";
	if (articleno.IsEmpty() == false)
	{
		sqlQuery += "AND CAST(ci.ocp_article_no AS char(10)) LIKE '%" + articleno.Trim() + "%' ";
	}
	if (curStatusFilter == 1) // not yet validated
	{
		sqlQuery += "AND co.sum_state_flags in ('0','1','2','3') ";
	}
	else if (curStatusFilter == 2) // validation successful
	{
		sqlQuery += "AND co.sum_state_flags in ('7','8','9') ";
	}
	else if (curStatusFilter == 3) // validation errors
	{
		sqlQuery += "AND co.sum_state_flags in ('4','5','6') ";
	}
	sqlOrdQuery = "ORDER BY ci.ocp_article_no, ci.code_type ";

	// get at first the count
	sqlStatus = SqlRead(sqlCntQuery + sqlQuery, &sqlCount, NULL);
	if (sqlStatus >= SQL_SUCCESS)
	{
		// set the up and down buttons according to the count
		m_btnArticleCodesPrev.EnableWindow(m_lngArticleCodesStartAt > 0);
		m_btnArticleCodesNext.EnableWindow((m_lngArticleCodesStartAt + MAX_RECORD_COUNT) < sqlCount);
	}
	// then get the data
	sqlStatus = SqlOpenCs(&sqlHandle, sqlSelQuery + sqlQuery + sqlOrdQuery);
	if (sqlStatus != SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		MsgBoxOK(m_strLastError);
		return false;
	}
	sqlCount = 0;
	sqlStatus = SqlFetch(sqlHandle, 1, &ocpcode_ocparticleno, &ocpcode_codetype, &ocpcode_typename, &ocpcode_articlecode, &ocpcode_phxarticleno, &ocpcode_sumstateflag, NULL);
	if (sqlStatus == SQL_NOTFOUND)
	{
		// no article code data found for this import with given filters
		m_strLastError = CResString::ex().getStrTblText(IDS_NO_OCPIMPORT_DATA);
		SqlCloseCs(sqlHandle);
		return false;
	}
	// show the article code details on the list box
	do
	{
		int nItem = m_lstArticleCodes.InsertItem(0, std::to_string(ocpcode_ocparticleno).c_str());
		m_lstArticleCodes.SetItemText(nItem, 1, std::to_string(ocpcode_phxarticleno).c_str());
		strTemp = m_objDoc.ConvertLong2CString(ocpcode_codetype, true) + " (" + CString(ocpcode_typename).Trim() + ")";
		m_lstArticleCodes.SetItemText(nItem, 2, strTemp);
		m_lstArticleCodes.SetItemText(nItem, 3, CString(ocpcode_articlecode).Trim());
		m_lstArticleCodes.SetItemText(nItem, 4, ConvertStateToCString(ocpcode_sumstateflag));
		sqlCount++;
		sqlStatus = SqlFetch(sqlHandle, 1, &ocpcode_ocparticleno, &ocpcode_codetype, &ocpcode_typename, &ocpcode_articlecode, &ocpcode_phxarticleno, &ocpcode_sumstateflag, NULL);
	}
	while ((sqlStatus == SQL_SUCCESS) && (sqlCount < MAX_RECORD_COUNT));

	if (sqlStatus < SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		SqlCloseCs(sqlHandle);
		MsgBoxOK(m_strLastError);
		return false;
	}
	SqlCloseCs(sqlHandle);
	return true;
}

void CArticleOCPStaging::OnArticleCodesSearch()
{
	m_btnArticleCodesSearch.EnableWindow(LoadArticleCodeData());
}

void CArticleOCPStaging::OnArticleCodesPrev()
{
	m_lngArticleCodesStartAt = max(0, m_lngArticleCodesStartAt - MAX_RECORD_COUNT);
	OnArticleCodesSearch();
}

void CArticleOCPStaging::OnArticleCodesNext()
{
	m_lngArticleCodesStartAt = m_lngArticleCodesStartAt + MAX_RECORD_COUNT;
	OnArticleCodesSearch();
}

bool CArticleOCPStaging::LoadArticleData()
{
	long sqlStatus;
	int  sqlHandle;
	long sqlCount;
	CString sqlSelQuery;
	CString sqlCntQuery;
	CString sqlQuery;
	CString sqlOrdQuery;
	if (m_pobjCurrentImport == NULL)
	{
		return false;
	}
	// get the filters
	CString articleno = "";
	m_edtOCPArticleNo.GetWindowText(articleno);
	int curStatusFilter = m_cmbStagingStatus.GetCurSel();
	// reset the list box
	m_lstArticles.DeleteAllItems();
	// find imported articles
	long        ocpcode_ocparticleno;
	char        ocpcode_articlename[31];
	long		ocpcode_phxarticleno;
	char		ocpcode_sumstateflag[2];
	sqlCntQuery = "SELECT CAST(count(*) as INTEGER) ";
	sqlSelQuery = "SELECT SKIP " + m_objDoc.ConvertLong2CString(m_lngArticlesStartAt, true) + " FIRST " + m_objDoc.ConvertLong2CString(MAX_RECORD_COUNT, true) + " ";
	sqlSelQuery += "ci.ocp_article_no, ci.long_name, co.article_no, co.sum_state_flags ";
	sqlQuery = "FROM cocp_stagein_article ci, cocp_stageout_article co ";
	sqlQuery += "WHERE ci.import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " ";
	sqlQuery += "AND ci.import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true) + " ";
	sqlQuery += "AND ci.ocp_article_no = co.ocp_article_no ";
	if (articleno.IsEmpty() == false)
	{
		sqlQuery += "AND CAST(ci.ocp_article_no AS char(10)) LIKE '%" + CString(articleno).Trim() + "%' ";
	}
	if (curStatusFilter == 1) // not yet validated
	{
		sqlQuery += "AND co.sum_state_flags in ('0','1','2','3') ";
	}
	else if (curStatusFilter == 2) // validation successful
	{
		sqlQuery += "AND co.sum_state_flags in ('7','8','9') ";
	}
	else if (curStatusFilter == 3) // validation errors
	{
		sqlQuery += "AND co.sum_state_flags in ('4','5','6') ";
	}
	sqlOrdQuery = "ORDER BY ci.ocp_article_no";

	// get at first the count
	sqlStatus = SqlRead(sqlCntQuery + sqlQuery, &sqlCount, NULL);
	if (sqlStatus >= SQL_SUCCESS)
	{
		// set the up and down buttons according to the count
		m_btnArticlesPrev.EnableWindow(m_lngArticlesStartAt > 0);
		m_btnArticlesNext.EnableWindow((m_lngArticlesStartAt + MAX_RECORD_COUNT) < sqlCount);
	}
	// then get the data
	sqlStatus = SqlOpenCs(&sqlHandle, sqlSelQuery + sqlQuery + sqlOrdQuery);
	if (sqlStatus != SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		MsgBoxOK(m_strLastError);
		return false;
	}
	sqlCount = 0;
	sqlStatus = SqlFetch(sqlHandle, 1, &ocpcode_ocparticleno, &ocpcode_articlename, &ocpcode_phxarticleno, &ocpcode_sumstateflag, NULL);
	if (sqlStatus == SQL_NOTFOUND)
	{
		// no article data found for this import with given filters
		m_strLastError = CResString::ex().getStrTblText(IDS_NO_OCPIMPORT_DATA);
		SqlCloseCs(sqlHandle);
		return false;
	}
	// show the article details on the list box
	do
	{
		int nItem = m_lstArticles.InsertItem(0, m_objDoc.ConvertLong2CString(ocpcode_ocparticleno, true));
		m_lstArticles.SetItemText(nItem, 1, m_objDoc.ConvertLong2CString(ocpcode_phxarticleno, true));
		m_lstArticles.SetItemText(nItem, 2, CString(ocpcode_articlename).Trim());
		m_lstArticles.SetItemText(nItem, 3, ConvertStateToCString(ocpcode_sumstateflag));
		sqlCount++;
		sqlStatus = SqlFetch(sqlHandle, 1, &ocpcode_ocparticleno, &ocpcode_articlename, &ocpcode_phxarticleno, &ocpcode_sumstateflag, NULL);
	} while ((sqlStatus == SQL_SUCCESS) && (sqlCount < MAX_RECORD_COUNT));

	if (sqlStatus < SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		SqlCloseCs(sqlHandle);
		MsgBoxOK(m_strLastError);
		return false;
	}
	SqlCloseCs(sqlHandle);
	return true;
}

void CArticleOCPStaging::OnArticlesSearch()
{
	m_btnArticlesSearch.EnableWindow(LoadArticleData());
}

void CArticleOCPStaging::OnArticlesPrev()
{
	m_lngArticlesStartAt = max(0, m_lngArticlesStartAt - MAX_RECORD_COUNT);
	OnArticlesSearch();
}

void CArticleOCPStaging::OnArticlesNext()
{
	m_lngArticlesStartAt = m_lngArticlesStartAt + MAX_RECORD_COUNT;
	OnArticlesSearch();
}

bool CArticleOCPStaging::LoadArticlePriceData()
{
	long sqlStatus;
	int  sqlHandle;
	long sqlCount;
	CString sqlSelQuery;
	CString sqlCntQuery;
	CString sqlQuery;
	CString sqlOrdQuery;
	char chrTemp[30];
	if (m_pobjCurrentImport == NULL)
	{
		return false;
	}
	// get the filters
	CString articleno = "";
	m_edtOCPArticleNo.GetWindowText(articleno);
	int curStatusFilter = m_cmbStagingStatus.GetCurSel();
	// reset the list box
	m_lstArticlePrices.DeleteAllItems();
	// find imported article prices
	long        ocpcode_ocparticleno;
	long        ocpcode_validfrom;
	double      ocpcode_buyprice;
	double      ocpcode_sellprice;
	long		ocpcode_phxarticleno;
	char		ocpcode_sumstateflag[2];
	sqlCntQuery = "SELECT CAST(count(*) as INTEGER) ";
	sqlSelQuery = "SELECT SKIP " + m_objDoc.ConvertLong2CString(m_lngArticlePricesStartAt, true) + " FIRST " + m_objDoc.ConvertLong2CString(MAX_RECORD_COUNT, true) + " ";
	sqlSelQuery += "ci.ocp_article_no, ci.valid_from_date, ci.manufacturer_base_price, ci.pharmacy_base_price, co.article_no, co.sum_state_flags ";
	sqlQuery += "FROM cocp_stagein_articleprice ci, cocp_stageout_articleprice co ";
	sqlQuery += "WHERE ci.import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " ";
	sqlQuery += "AND ci.import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true) + " ";
	sqlQuery += "AND ci.ocp_article_no=co.ocp_article_no AND ci.valid_from_date=co.valid_from_date ";
	if (articleno.IsEmpty() == false)
	{
		sqlQuery += "AND CAST(ci.ocp_article_no AS char(10)) LIKE '%" + CString(articleno).Trim() + "%' ";
	}
	if (curStatusFilter == 1) // not yet validated
	{
		sqlQuery += "AND co.sum_state_flags in ('0','1','2','3') ";
	}
	else if (curStatusFilter == 2) // validation successful
	{
		sqlQuery += "AND co.sum_state_flags in ('7','8','9') ";
	}
	else if (curStatusFilter == 3) // validation errors
	{
		sqlQuery += "AND co.sum_state_flags in ('4','5','6') ";
	}
	sqlOrdQuery = "ORDER BY ci.ocp_article_no, ci.valid_from_date ";

	// get at first the count
	sqlStatus = SqlRead(sqlCntQuery + sqlQuery, &sqlCount, NULL);
	if (sqlStatus >= SQL_SUCCESS)
	{
		// set the up and down buttons according to the count
		m_btnArticlePricesPrev.EnableWindow(m_lngArticlePricesStartAt > 0);
		m_btnArticlePricesNext.EnableWindow((m_lngArticlePricesStartAt + MAX_RECORD_COUNT) < sqlCount);
	}
	// then get the data
	sqlStatus = SqlOpenCs(&sqlHandle, sqlSelQuery + sqlQuery + sqlOrdQuery);
	if (sqlStatus != SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		MsgBoxOK(m_strLastError);
		return false;
	}
	sqlCount = 0;
	sqlStatus = SqlFetch(sqlHandle, 1, &ocpcode_ocparticleno, &ocpcode_validfrom, &ocpcode_buyprice, &ocpcode_sellprice, &ocpcode_phxarticleno, &ocpcode_sumstateflag, NULL);
	if (sqlStatus == SQL_NOTFOUND)
	{
		// no article price data found for this import with given filters
		m_strLastError = CResString::ex().getStrTblText(IDS_NO_OCPIMPORT_DATA);
		SqlCloseCs(sqlHandle);
		return false;
	}
	// show the article price details on the list box
	do
	{
		int nItem = m_lstArticlePrices.InsertItem(0, std::to_string(ocpcode_ocparticleno).c_str());
		m_lstArticlePrices.SetItemText(nItem, 1, std::to_string(ocpcode_phxarticleno).c_str());
		sprintf(chrTemp, "%.2ld.%.2ld.%.4ld", ocpcode_validfrom % 100, (ocpcode_validfrom % 10000) / 100, ocpcode_validfrom / 10000);
		m_lstArticlePrices.SetItemText(nItem, 2, CString(chrTemp).Trim());
		sprintf(chrTemp, "%0.2f", ocpcode_buyprice);
		m_lstArticlePrices.SetItemText(nItem, 3, CString(chrTemp).Trim());
		sprintf(chrTemp, "%0.2f", ocpcode_sellprice);
		m_lstArticlePrices.SetItemText(nItem, 4, CString(chrTemp).Trim());
		m_lstArticlePrices.SetItemText(nItem, 5, ConvertStateToCString(ocpcode_sumstateflag));
		sqlCount++;
		sqlStatus = SqlFetch(sqlHandle, 1, &ocpcode_ocparticleno, &ocpcode_validfrom, &ocpcode_buyprice, &ocpcode_sellprice, &ocpcode_phxarticleno, &ocpcode_sumstateflag, NULL);
	} while ((sqlStatus == SQL_SUCCESS) && (sqlCount < MAX_RECORD_COUNT));

	if (sqlStatus < SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		SqlCloseCs(sqlHandle);
		MsgBoxOK(m_strLastError);
		return false;
	}
	SqlCloseCs(sqlHandle);
	return true;
}

void CArticleOCPStaging::OnArticlePricesSearch()
{
	m_btnArticlePricesSearch.EnableWindow(LoadArticlePriceData());
}

void CArticleOCPStaging::OnArticlePricesPrev()
{
	m_lngArticlePricesStartAt = max(0, m_lngArticlePricesStartAt - MAX_RECORD_COUNT);
	OnArticlePricesSearch();
}

void CArticleOCPStaging::OnArticlePricesNext()
{
	m_lngArticlePricesStartAt = m_lngArticlePricesStartAt + MAX_RECORD_COUNT;
	OnArticlePricesSearch();
}

bool CArticleOCPStaging::LoadArticleFranceData()
{
	long sqlStatus;
	int  sqlHandle;
	long sqlCount;
	CString sqlSelQuery;
	CString sqlCntQuery;
	CString sqlQuery;
	CString sqlOrdQuery;
	char chrTemp[30];
	if (m_pobjCurrentImport == NULL)
	{
		return false;
	}
	// get the filters
	CString articleno = "";
	m_edtOCPArticleNo.GetWindowText(articleno);
	int curStatusFilter = m_cmbStagingStatus.GetCurSel();
	// reset the list box
	m_lstArticleFrance.DeleteAllItems();
	// find imported article france
	long        ocpcode_ocparticleno;
	char        ocpcode_returntype[2];
	double      ocpcode_returnvalue;
	double      ocpcode_returnpercentage;
	long		ocpcode_phxarticleno;
	char		ocpcode_sumstateflag[2];
	sqlCntQuery = "SELECT CAST(count(*) as INTEGER) ";
	sqlSelQuery = "SELECT SKIP " + m_objDoc.ConvertLong2CString(m_lngArticleFranceStartAt, true) + " FIRST " + m_objDoc.ConvertLong2CString(MAX_RECORD_COUNT, true) + " ";
	sqlSelQuery += "ci.ocp_article_no, ci.reimbursement_type, ci.reimbursement_val, ci.reimbursement_perc, co.article_no, co.sum_state_flags ";
	sqlQuery += "FROM cocp_stagein_article_france ci, cocp_stageout_article_france co ";
	sqlQuery += "WHERE ci.import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " ";
	sqlQuery += "AND ci.import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true) + " ";
	sqlQuery += "AND ci.ocp_article_no=co.ocp_article_no ";
	if (articleno.IsEmpty() == false)
	{
		sqlQuery += "AND CAST(ci.ocp_article_no AS char(10)) LIKE '%" + CString(articleno).Trim() + "%' ";
	}
	if (curStatusFilter == 1) // not yet validated
	{
		sqlQuery += "AND co.sum_state_flags in ('0','1','2','3') ";
	}
	else if (curStatusFilter == 2) // validation successful
	{
		sqlQuery += "AND co.sum_state_flags in ('7','8','9') ";
	}
	else if (curStatusFilter == 3) // validation errors
	{
		sqlQuery += "AND co.sum_state_flags in ('4','5','6') ";
	}
	sqlOrdQuery = "ORDER BY ci.ocp_article_no";

	// get at first the count
	sqlStatus = SqlRead(sqlCntQuery + sqlQuery, &sqlCount, NULL);
	if (sqlStatus >= SQL_SUCCESS)
	{
		// set the up and down buttons according to the count
		m_btnArticleFrancePrev.EnableWindow(m_lngArticleFranceStartAt > 0);
		m_btnArticleFranceNext.EnableWindow((m_lngArticleFranceStartAt + MAX_RECORD_COUNT) < sqlCount);
	}
	// then get the data
	sqlStatus = SqlOpenCs(&sqlHandle, sqlSelQuery + sqlQuery + sqlOrdQuery);
	if (sqlStatus != SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		MsgBoxOK(m_strLastError);
		return false;
	}
	sqlCount = 0;
	sqlStatus = SqlFetch(sqlHandle, 1, &ocpcode_ocparticleno, &ocpcode_returntype, &ocpcode_returnvalue, &ocpcode_returnpercentage, &ocpcode_phxarticleno, &ocpcode_sumstateflag, NULL);
	if (sqlStatus == SQL_NOTFOUND)
	{
		// no article france data found for this import with given filters
		m_strLastError = CResString::ex().getStrTblText(IDS_NO_OCPIMPORT_DATA);
		SqlCloseCs(sqlHandle);
		return false;
	}
	// show the article france details on the list box
	do
	{
		int nItem = m_lstArticleFrance.InsertItem(0, std::to_string(ocpcode_ocparticleno).c_str());
		m_lstArticleFrance.SetItemText(nItem, 1, std::to_string(ocpcode_phxarticleno).c_str());
		m_lstArticleFrance.SetItemText(nItem, 2, CString(ocpcode_returntype).Trim());
		sprintf(chrTemp, "%0.2f", ocpcode_returnvalue);
		m_lstArticleFrance.SetItemText(nItem, 3, CString(chrTemp).Trim());
		sprintf(chrTemp, "%0.2f", ocpcode_returnpercentage);
		m_lstArticleFrance.SetItemText(nItem, 4, CString(chrTemp).Trim());
		m_lstArticleFrance.SetItemText(nItem, 5, ConvertStateToCString(ocpcode_sumstateflag));
		sqlCount++;
		sqlStatus = SqlFetch(sqlHandle, 1, &ocpcode_ocparticleno, &ocpcode_returntype, &ocpcode_returnvalue, &ocpcode_returnpercentage, &ocpcode_phxarticleno, &ocpcode_sumstateflag, NULL);
	} while ((sqlStatus == SQL_SUCCESS) && (sqlCount < MAX_RECORD_COUNT));

	if (sqlStatus < SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		SqlCloseCs(sqlHandle);
		MsgBoxOK(m_strLastError);
		return false;
	}
	SqlCloseCs(sqlHandle);
	return true;
}

void CArticleOCPStaging::OnArticleFranceSearch()
{
	m_btnArticleFranceSearch.EnableWindow(LoadArticleFranceData());
}

void CArticleOCPStaging::OnArticleFrancePrev()
{
	m_lngArticleFranceStartAt = max(0, m_lngArticleFranceStartAt - MAX_RECORD_COUNT);
	OnArticleFranceSearch();
}

void CArticleOCPStaging::OnArticleFranceNext()
{
	m_lngArticleFranceStartAt = m_lngArticleFranceStartAt + MAX_RECORD_COUNT;
	OnArticleFranceSearch();
}

void CArticleOCPStaging::OnDblClickListArticleCodes(NMHDR* pNMHDR, LRESULT* pResult)
{
	pNMHDR;
	*pResult = 0;
	int row = m_lstArticleCodes.GetSelectionMark();
	if ((row >= 0) && (m_pobjCurrentImport != NULL))
	{
		CString sArticleNo = m_lstArticleCodes.GetItemText(row, 0);
		m_intCurrentArticleIndex = FindCurrentArticleIndex(atol(sArticleNo));
	}
	OnOK();
}

void CArticleOCPStaging::OnDblClickListArticles(NMHDR* pNMHDR, LRESULT* pResult)
{
	pNMHDR;
	*pResult = 0;
	int row = m_lstArticles.GetSelectionMark();
	if ((row >= 0) && (m_pobjCurrentImport != NULL))
	{
		CString sArticleNo = m_lstArticles.GetItemText(row, 0);
		m_intCurrentArticleIndex = FindCurrentArticleIndex(atol(sArticleNo));
	}
	OnOK();
}

void CArticleOCPStaging::OnDblClickListArticlePrices(NMHDR* pNMHDR, LRESULT* pResult)
{
	pNMHDR;
	*pResult = 0;
	int row = m_lstArticlePrices.GetSelectionMark();
	if ((row >= 0) && (m_pobjCurrentImport != NULL))
	{
		CString sArticleNo = m_lstArticlePrices.GetItemText(row, 0);
		m_intCurrentArticleIndex = FindCurrentArticleIndex(atol(sArticleNo));
	}
	OnOK();
}

void CArticleOCPStaging::OnDblClickListArticleFrance(NMHDR* pNMHDR, LRESULT* pResult)
{
	pNMHDR;
	*pResult = 0;
	int row = m_lstArticleFrance.GetSelectionMark();
	if ((row >= 0) && (m_pobjCurrentImport != NULL))
	{
		CString sArticleNo = m_lstArticleFrance.GetItemText(row, 0);
		m_intCurrentArticleIndex = FindCurrentArticleIndex(atol(sArticleNo));
	}
	OnOK();
}

void CArticleOCPStaging::LoadCurrentArticles()
{
	m_vecCurrentArticles.clear();
	m_intCurrentArticleIndex = -1;
	if (m_pobjCurrentImport != NULL)
	{
		long sqlStatus;
		int  sqlHandle;
		long sqlCount;
		CString sqlQuery;
		CString sqlWhere;
		long ocparticleno;
		// get the filters
		CString articleno = "";
		m_edtOCPArticleNo.GetWindowText(articleno);
		int curStatusFilter = m_cmbStagingStatus.GetCurSel();
		// define the common where condition with the given filters
		sqlWhere = "WHERE ci.import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " ";
		sqlWhere += "AND ci.import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true) + " ";
		sqlWhere += "AND ci.ocp_article_no=co.ocp_article_no ";
		if (articleno.IsEmpty() == false)
		{
			sqlWhere += "AND CAST(ci.ocp_article_no AS char(10)) LIKE '%" + articleno.Trim() + "%' ";
		}
		if (curStatusFilter == 1) // not yet validated
		{
			sqlWhere += "AND co.sum_state_flags in ('0','1','2','3') ";
		}
		else if (curStatusFilter == 2) // validation successful
		{
			sqlWhere += "AND co.sum_state_flags in ('7','8','9') ";
		}
		else if (curStatusFilter == 3) // validation errors
		{
			sqlWhere += "AND co.sum_state_flags in ('4','5','6') ";
		}
		// read all article no's with the given filters across all 4 tables
		sqlQuery = "SELECT distinct ci.ocp_article_no FROM cocp_stagein_articlecode ci, cocp_stageout_articlecode co " + sqlWhere + " ";
		sqlQuery += "UNION SELECT distinct ci.ocp_article_no FROM cocp_stagein_article ci, cocp_stageout_article co " + sqlWhere + " ";
		sqlQuery += "UNION SELECT distinct ci.ocp_article_no FROM cocp_stagein_articleprice ci, cocp_stageout_articleprice co " + sqlWhere + " ";
		sqlQuery += "UNION SELECT distinct ci.ocp_article_no FROM cocp_stagein_article_france ci, cocp_stageout_article_france co " + sqlWhere + " ";
		sqlQuery += "ORDER BY ci.ocp_article_no ";
		// store it into the current vector for navigating in the view (prev, next button)
		sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
		if (sqlStatus != SQL_SUCCESS)
		{
			m_strLastError = DynErrmld();
			MsgBoxOK(m_strLastError);
			return;
		}
		sqlCount = 0;
		sqlStatus = SqlFetch(sqlHandle, 1, &ocparticleno, NULL);
		while ((sqlStatus == SQL_SUCCESS) && (sqlCount < MAX_OCP_ARTICLE_COUNT))
		{
			m_vecCurrentArticles.push_back(ocparticleno);
			sqlCount++;
			sqlStatus = SqlFetch(sqlHandle, 1, &ocparticleno, NULL);
		}
		if (sqlStatus < SQL_SUCCESS)
		{
			m_strLastError = DynErrmld();
			SqlCloseCs(sqlHandle);
			MsgBoxOK(m_strLastError);
			return;
		}
		SqlCloseCs(sqlHandle);
	}
}

int CArticleOCPStaging::FindCurrentArticleIndex(long articleno)
{
	int ret = -1;
	bool fnd = false;
	int index = 0;
	while ((index < m_vecCurrentArticles.size()) && (fnd == false))
	{
		long artno = m_vecCurrentArticles.at(index);
		if (artno == articleno)
		{
			fnd = true;
			ret = index;
		}
		else
		{
			index++;
		}
	}
	return ret;
}

long CArticleOCPStaging::GetCurrentArticleNo(int index)
{
	long ret = 0;
	if ((index >= 0) && (index < m_vecCurrentArticles.size()))
	{
		ret = m_vecCurrentArticles.at(index);
	}
	return ret;
}

BOOL CArticleOCPStaging::PrimeKeyOfSelectedRecord(long* PrimeKey1, long* PrimeKey2, long* PrimeKey3)
{
	*PrimeKey1 = 0;
	*PrimeKey2 = 0;
	*PrimeKey3 = 0;
	if (m_pobjCurrentImport == NULL)
	{
		return FALSE;
	}
	*PrimeKey1 = m_pobjCurrentImport->IMPORT_DATE;
	*PrimeKey2 = m_pobjCurrentImport->IMPORT_TIME;
	*PrimeKey3 = GetCurrentArticleNo(m_intCurrentArticleIndex);
	return TRUE;
}

BOOL CArticleOCPStaging::PrimeKeyOfNextRecord(long* PrimeKey1, long* PrimeKey2, long* PrimeKey3)
{
	*PrimeKey1 = 0;
	*PrimeKey2 = 0;
	*PrimeKey3 = 0;
	if (m_pobjCurrentImport == NULL)
	{
		return FALSE;
	}
	*PrimeKey1 = m_pobjCurrentImport->IMPORT_DATE;
	*PrimeKey2 = m_pobjCurrentImport->IMPORT_TIME;
	if ((m_intCurrentArticleIndex + 1) < m_vecCurrentArticles.size())
	{
		m_intCurrentArticleIndex++;
	}
	*PrimeKey3 = GetCurrentArticleNo(m_intCurrentArticleIndex);
	return TRUE;
}

BOOL CArticleOCPStaging::PrimeKeyOfPrevRecord(long* PrimeKey1, long* PrimeKey2, long* PrimeKey3)
{
	*PrimeKey1 = 0;
	*PrimeKey2 = 0;
	*PrimeKey3 = 0;
	if (m_pobjCurrentImport == NULL)
	{
		return FALSE;
	}
	*PrimeKey1 = m_pobjCurrentImport->IMPORT_DATE;
	*PrimeKey2 = m_pobjCurrentImport->IMPORT_TIME;
	if (m_intCurrentArticleIndex > 0)
	{
		m_intCurrentArticleIndex--;
	}
	*PrimeKey3 = GetCurrentArticleNo(m_intCurrentArticleIndex);
	return TRUE;
}

void CArticleOCPStaging::OnClickedValidateRecords()
{
	if (m_pobjCurrentImport != NULL)
	{
		ValidateRecords(false);
		OnChangeOCPImport();
	}
	else
	{
		MessageBox("Please select an OCP import for validation!", "Validation Error", MB_OK);
	}
}

void CArticleOCPStaging::ValidateRecords(bool silent)
{
		long sqlStatus;
		int  sqlHandle;
		CString sqlQuery;
		CString sqlWhere;
		long ocparticleno;
		std::vector<long> vecArticles;
		long lngArticleCount = 0;
		long lngLoadCount = 0;
		long lngValidateCount = 0;
		long lngErrorCount = 0;
		long lngUpdateCount = 0;

		//
		// Step 1: read at first all imported articleno from the current selected import date and time
		//
		sqlWhere = "WHERE import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " AND import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true) + " ";
		sqlQuery = "SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_articlecode " + sqlWhere + " UNION ";
		sqlQuery += "SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_article " + sqlWhere + " UNION ";
		sqlQuery += "SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_articleprice " + sqlWhere + " UNION ";
		sqlQuery += "SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_article_france " + sqlWhere + " ";
		sqlQuery += "ORDER BY ocp_article_no ";
		sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
		if (sqlStatus != SQL_SUCCESS)
		{
			m_strLastError = DynErrmld();
			MsgBoxOK(m_strLastError);
			return;
		}
		lngArticleCount = 0;
		sqlStatus = SqlFetch(sqlHandle, 1, &ocparticleno, NULL);
		if (sqlStatus == SQL_NOTFOUND)
		{
			// no article data found for this import
			m_strLastError = CResString::ex().getStrTblText(IDS_NO_OCPIMPORT_DATA);
			SqlCloseCs(sqlHandle);
		}
		// store the article no's in a temp list
		do
		{
			vecArticles.push_back(ocparticleno);
			lngArticleCount++;
			sqlStatus = SqlFetch(sqlHandle, 1, &ocparticleno, NULL);
	} while (sqlStatus == SQL_SUCCESS);

		if (sqlStatus < SQL_SUCCESS)
		{
			m_strLastError = DynErrmld();
			SqlCloseCs(sqlHandle);
			MsgBoxOK(m_strLastError);
		}
		SqlCloseCs(sqlHandle);

		//
		// Step 2: load the predefined values for valiation from masterdata
		//
		m_strLastError = m_objDoc.LoadOCPListData();
		if (m_strLastError.IsEmpty() == false)
		{
			MsgBoxOK(m_strLastError);
		}
		// 
		// Step 3: load the article details of all 4 records from stageout for each article found
		//
		((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
		std::vector<long>::iterator it;
		for (it = vecArticles.begin(); it != vecArticles.end(); it++)
		{
			ocparticleno = *it;
			m_strLastError = m_objDoc.LoadOCPData(m_pobjCurrentImport->IMPORT_DATE, m_pobjCurrentImport->IMPORT_TIME, ocparticleno);
			if (m_strLastError.IsEmpty() == true)
			{
				lngLoadCount++;
				//
				// Step 4: validate each article found
				//
				if (m_objDoc.ValidateOCPData() == true)
				{
					lngValidateCount++;
				}
				else
				{
					lngErrorCount++;
				}
				//
				// Step 5: update only status for each article found
				//
				long allcnt = 0, updcnt = 0, errcnt = 0;
				if (m_objDoc.UpdateOCPDataStatus(allcnt, updcnt, errcnt) == true)
				{
					if (updcnt > 0)
					{
						lngUpdateCount++;
					}
				}
			}
		}
		((CEkZdpApp*)AfxGetApp())->EndWaitAction();
		//
		// Step 6: show result to user
		//
	if (silent == false)
	{
		CString msg = "Validation Completed:\nFound Articles: " + m_objDoc.ConvertLong2CString(lngArticleCount, true) + "\n";
		msg += "Successfully Validated Articles: " + m_objDoc.ConvertLong2CString(lngValidateCount, true) + "\n";
		msg += "Validated with Errors Articles: " + m_objDoc.ConvertLong2CString(lngErrorCount, true) + "\n";
		msg += "Updated Validation Status: " + m_objDoc.ConvertLong2CString(lngUpdateCount, true);
		MessageBox(msg, "Validation Result", MB_OK);
	}
}

void CArticleOCPStaging::OnClickedTransferRecords()
{
	if (m_pobjCurrentImport != NULL)
	{
		// first do a re-validation silently to prevent obsolete verifications
		ValidateRecords(true);
		// remote call server program UNIX
		long lngStatus = 0;
		CString strUnixPathBin;
		CString strStatus;
		CString strDateTime;
		CString strTempTime;
		CString strUsername;
		CGetUnixFiles gU;
		char chrCmd[251];
		char chrRec[251];
		int intLen = 0;

		long lngFullArticleCount = GetArticleCount(m_pobjCurrentImport->IMPORT_DATE, m_pobjCurrentImport->IMPORT_TIME);
		strDateTime = m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true);
		strTempTime = m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true);
		while (strTempTime.GetLength() < 6)
		{
			// add leading zeros
			strTempTime = "0" + strTempTime;
		}
		strDateTime += strTempTime;
		strUsername = ((CEkZdpApp*)AfxGetApp())->GetUserNameA();
		// get bin directory
		((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
		lngStatus = gU.GetWWSDateiUnterVerz(strUnixPathBin, bin, strStatus);
		if (lngStatus != 0)
		{
			MsgBoxOK(strStatus);
			return;
		}
		((CEkZdpApp*)AfxGetApp())->EndWaitAction();
		// the real binary is called by e.g. importocp.bin -db ifr21@zdev21_shm -log -outpharmos '20230621195300'
		// but we have implemented to be called via a script to handle all unix environment variables correctly by e.g. transferocp.sh -start -outpharmos 20230621195300
		memset(chrRec, 0, 250);
		sprintf(chrCmd, "%s../proc/transferocp.sh -start -outpharmos %s -username %s                                    \0",
			strUnixPathBin.GetString(),
			strDateTime.GetString(),
			strUsername.GetString()
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
			// everything find, show a summary
			long lngLeftArticleCount = GetArticleCount(m_pobjCurrentImport->IMPORT_DATE, m_pobjCurrentImport->IMPORT_TIME);
			CString msg = "Transfer Completed:\nFound Articles: " + m_objDoc.ConvertLong2CString(lngFullArticleCount, true) + "\n";
			msg += "Successfully Transferred Articles: " + m_objDoc.ConvertLong2CString(lngFullArticleCount - lngLeftArticleCount, true) + "\n";
			msg += "Not Transferred Articles (Validation Errors): " + m_objDoc.ConvertLong2CString(lngLeftArticleCount, true) + "\n";
			MessageBox(msg, "Transfer Result", MB_OK);
			InitImportStatus();
		}
	}
	else
	{
		MessageBox("Please select an OCP import for transfer!", "Transfer Error", MB_OK);
	}
}

void CArticleOCPStaging::OnClickedDeleteRecords()
{
	if (m_pobjCurrentImport != NULL)
	{
		long sqlStatus;
		int  sqlHandle;
		CString sqlQuery;
		CString sqlWhere;
		long ocparticleno;
		std::vector<long> vecArticles;
		long lngArticleCount = 0;
		long lngLoadCount = 0;
		long lngDeleteCount = 0;

		//
		// Step 1: read at first all imported articleno from the current selected import date and time
		//
		sqlWhere = "WHERE import_date=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_DATE, true) + " AND import_time=" + m_objDoc.ConvertLong2CString(m_pobjCurrentImport->IMPORT_TIME, true) + " ";
		sqlQuery = "SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_articlecode " + sqlWhere + " UNION ";
		sqlQuery += "SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_article " + sqlWhere + " UNION ";
		sqlQuery += "SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_articleprice " + sqlWhere + " UNION ";
		sqlQuery += "SELECT DISTINCT(ocp_article_no) FROM cocp_stagein_article_france " + sqlWhere + " ";
		sqlQuery += "ORDER BY ocp_article_no ";
		sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
		if (sqlStatus != SQL_SUCCESS)
		{
			m_strLastError = DynErrmld();
			MsgBoxOK(m_strLastError);
			return;
		}
		lngArticleCount = 0;
		sqlStatus = SqlFetch(sqlHandle, 1, &ocparticleno, NULL);
		if (sqlStatus == SQL_NOTFOUND)
		{
			// no article data found for this import
			m_strLastError = CResString::ex().getStrTblText(IDS_NO_OCPIMPORT_DATA);
			SqlCloseCs(sqlHandle);
		}
		// store the article no's in a temp list
		do
		{
			vecArticles.push_back(ocparticleno);
			lngArticleCount++;
			sqlStatus = SqlFetch(sqlHandle, 1, &ocparticleno, NULL);
		}
		while (sqlStatus == SQL_SUCCESS);

		if (sqlStatus < SQL_SUCCESS)
		{
			m_strLastError = DynErrmld();
			SqlCloseCs(sqlHandle);
			MsgBoxOK(m_strLastError);
		}
		SqlCloseCs(sqlHandle);
		//
		// Step 2: ask user to confirm the deletion
		//
		CString msg = "Are you sure to delete imported data:\nImport Date: " + m_objDoc.ConvertDate2CString(m_pobjCurrentImport->IMPORT_DATE, true);
		msg += "\nImport Time: " + m_objDoc.ConvertTime2CString(m_pobjCurrentImport->IMPORT_TIME, true);
		msg += "\nFound Articles: " + m_objDoc.ConvertLong2CString(lngArticleCount, true);
		int ret = MessageBox(msg, "Delete Confirmation", MB_YESNO);
		if (ret == IDYES)
		{
			//
			// Step 3: load the article details of all 4 records from stageout for each article found
			//
			((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
			std::vector<long>::iterator it;
			for (it = vecArticles.begin(); it != vecArticles.end(); it++)
			{
				ocparticleno = *it;
				m_strLastError = m_objDoc.LoadOCPData(m_pobjCurrentImport->IMPORT_DATE, m_pobjCurrentImport->IMPORT_TIME, ocparticleno);
				if (m_strLastError.IsEmpty() == true)
				{
					lngLoadCount++;
					//
					// Step 4: delete each article found
					//
					long allcnt = 0, delcnt = 0, errcnt = 0;
					if (m_objDoc.DeleteOCPData(allcnt, delcnt, errcnt) == true)
					{
						if (delcnt > 0)
						{
							lngDeleteCount++;
						}
					}
					else
					{
						m_strLastError = m_objDoc.m_strLastError;
					}
				}
			}
			((CEkZdpApp*)AfxGetApp())->EndWaitAction();
			//
			// Step 5: show result to user
			//
			if (m_strLastError.IsEmpty() == true)
			{
				msg = "Deletion Completed:\nFound Articles: " + m_objDoc.ConvertLong2CString(lngArticleCount, true) + "\n";
				msg += "Deleted Articles: " + m_objDoc.ConvertLong2CString(lngDeleteCount, true);
				MessageBox(msg, "Deletion Result", MB_OK);
				InitImportStatus();
			}
			else
			{
				msg = "Cannot delete articles of this import\nFound Articles: " + m_objDoc.ConvertLong2CString(lngArticleCount, true) + "\n";
				msg += "Error: " + m_strLastError;
				MessageBox(msg, "Delete Error", MB_OK);
			}
		}
	}
	else
	{
		MessageBox("Please select an OCP import for deletion!", "Delete Error", MB_OK);
	}
}

void CArticleOCPStaging::OnClickedReimportRecords()
{
	long importdate = 0;
	long importtime = 0;
	int index = m_cmbImport.GetCurSel();
	if ((index >= 0) && (index < m_vecOCPImports.size()) && (m_pobjCurrentImport != NULL))
	{
		importdate = m_pobjCurrentImport->IMPORT_DATE;
		importtime = m_pobjCurrentImport->IMPORT_TIME;
	}
	CArticleOCPReimport dlg(importdate, importtime, this);
	dlg.DoModal();
}

long CArticleOCPStaging::GetArticleCount(long importDate, long importTime)
{
	long sqlStatus;
	int  sqlHandle;
	CString sqlQuery;
	long sqlCount = 0;
	long articlono;

	CString strImportDate = m_objDoc.ConvertLong2CString(importDate, true);
	CString strImportTime = m_objDoc.ConvertLong2CString(importTime, true);

	// get all articles across the stagein tables
	sqlQuery = "SELECT DISTINCT ocp_article_no FROM cocp_stagein_articlecode WHERE import_date = " + strImportDate + " AND import_time = " + strImportTime;
	sqlQuery += "UNION SELECT DISTINCT ocp_article_no FROM cocp_stagein_article WHERE import_date = " + strImportDate + " AND import_time = " + strImportTime;
	sqlQuery += "UNION SELECT DISTINCT ocp_article_no FROM cocp_stagein_articleprice WHERE import_date = " + strImportDate + " AND import_time = " + strImportTime;
	sqlQuery += "UNION SELECT DISTINCT ocp_article_no FROM cocp_stagein_article_france WHERE import_date = " + strImportDate + " AND import_time = " + strImportTime;
	sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
	if (sqlStatus == SQL_SUCCESS)
	{
		do
		{
			sqlStatus = SqlFetch(sqlHandle, 1, &articlono, NULL);
			if (sqlStatus == SQL_SUCCESS)
			{
				sqlCount++;
			}
		}
		while (sqlStatus == SQL_SUCCESS);
	}
	if (sqlStatus < SQL_SUCCESS)
	{
		m_strLastError = DynErrmld();
		SqlCloseCs(sqlHandle);
		MsgBoxOK(m_strLastError);
		return 0;
	}
	SqlCloseCs(sqlHandle);
	return sqlCount;
}

CString CArticleOCPStaging::ConvertStateToCString(LPSTR state)
{
	if ((state[0] == '7') || (state[0] == '8') || (state[0] == '9'))
	{
		return "Validated Successfully";
	}
	else if ((state[0] == '4') || (state[0] == '5') || (state[0] == '6'))
	{
		return "Validated with Errors";
	}
	return "Not Yet Validated";
}

