// ArtikelAgp.cpp : implementation file
//

#include "stdafx.h"
#include "Ekzdp.h"
#include "ArtikelAgp.h"
#include "ProgressDlg.h"
#include "ArtAgpImporter.h"
#include "ArtAgpImportGen.h"
#include "afxdialogex.h"
#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/wunxlocs/UnixSys.h>
#include <hdatum/phodate.h>
#include "MenuNumbers.h"
#include "ServerDatum.h"
#include <phxlib/EanTest.h>
#include "eklibs/wdbups/wpp_prot.h"
#include "eklibs/wdbups/wpp_dbas.h"

//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// CAGPMBox1

CAGPMBox1::CAGPMBox1()
{
}

CAGPMBox1::~CAGPMBox1()
{
	CloseCursor();
}

// Forms sql to select list control items.
CString CAGPMBox1::InitSelect(CString SuchBegriff)
{
	CString sql;

	// Parse SuchBegriff and get keywords [ARTSTATUS, AGPNR, PZN, GULTIGAB DATUM]
	CString keywrd;
	CString restStr;
	int iPos = 0;
	int keywrdcnt = 0;
	CString keywrds[4]; // Expects only 4 keywords
	char str[20];

	iPos = SuchBegriff.Find('\n', 0);
	keywrd = SuchBegriff.Left(iPos);
	keywrd.Trim();
	restStr = SuchBegriff.Mid(iPos + 1);
	keywrds[keywrdcnt] = keywrd;
	keywrdcnt++;
	while (keywrdcnt < 4)
	{
		iPos = restStr.Find('\n', 0);
		keywrd = restStr.Left(iPos);
		keywrd.Trim();
		restStr = restStr.Mid(iPos + 1);
		keywrds[keywrdcnt] = keywrd;
		keywrdcnt++;
	}


	sql = "select unique AGP_NR, PZN,AGP, GUELTIG_AB, ZEILE_STATUS, STATUS_DETAIL from CAGPART ";
	sql += " where AGP_NR=";

	// sets AGP Number Filter
	sql += keywrds[1];

	// sets PZN Filter
	if (!keywrds[2].IsEmpty())
	{
		if (IsNumber(keywrds[2]))
		{
			sql += " and PZN=";
			sql += keywrds[2];
		}
		else
		{
			sql += " and PZN=-1";
		}
	}


	// sets Gültig Ab condition format dd.mm.yyyy
	if (!keywrds[3].IsEmpty() && keywrds[3].GetLength() == 10)
	{
		keywrds[3].Remove('.');
		if (IsNumber(keywrds[3]))
		{
			long date = atol(keywrds[3]);
			sprintf(str, " %.4ld%.2ld%.2ld", date % 10000, (date / 10000) % 100, date / 1000000);
			sql += " and GUELTIG_AB=";
			sql += str;
		}
	}

	// sets Ziele Status condition
	if (IsNumber(keywrds[0]))
	{
		if (keywrds[0] == _T("3"))
		{
			sql += " and ZEILE_STATUS IN (1, 2) ";
		}
		else
		{
			sql += " and ZEILE_STATUS=";
			sql += keywrds[0];
		}
	}

	sql += " order by AGP_NR, PZN, GUELTIG_AB DESC";


	return sql;
}

// Fills list control row buffer
void CAGPMBox1::FillBuffer(CStringArray& s, void **VecPtr)
{
	s.SetSize(6);

	char str[16];

	sprintf(str, "%.7ld", m_SelBuf.PZN);
	s[0] = str;
	s[0].TrimRight();
	sprintf(str, "%.2f", m_SelBuf.AGP);
	s[1] = str;
	s[1].TrimRight();
	sprintf(str, "%.2ld.%.2ld.%.4ld", m_SelBuf.GUELTIG_AB % 100, (m_SelBuf.GUELTIG_AB % 10000) / 100, m_SelBuf.GUELTIG_AB / 10000);
	s[2] = str;
	s[2].TrimRight();
	s[3] = GetZeileStatus(m_SelBuf.ZEILE_STATUS);
	s[3].TrimRight();

	s[4] = m_SelBuf.STATUS_DETAIL;
	s[4].TrimRight();

	sprintf(str, "%.ld", m_SelBuf.AGP_NR);
	s[5] = str;
	s[5].TrimRight();

	m_VecBuf.AGP_NR = m_SelBuf.AGP_NR;
	m_VecBuf.PZN = m_SelBuf.PZN;
	m_VecBuf.GUELTIG_AB = m_SelBuf.GUELTIG_AB;
	*VecPtr = &m_VecBuf;
}

// Initialize search box columns
void CAGPMBox1::InitSuchBox()
{
	ListColumns Fields[] =
	{
		PZN,			 _strdup(CResString::ex().getStrTblText(IDS_PZN)),60,LVCFMT_LEFT, 1, // must be left aligned
		AGP,			 _strdup(CResString::ex().getStrTblText(IDS_AGP)), 80,LVCFMT_RIGHT, 0,
		GUELTIGAB,		 _strdup(CResString::ex().getStrTblText(IDS_GUELTIGAB)),80,LVCFMT_LEFT, 0,
		ZEILESTATUS,     _strdup(CResString::ex().getStrTblText(IDS_STATUS)),80,LVCFMT_LEFT, 0,
		STATUS_DETAIL,	 _strdup(CResString::ex().getStrTblText(IDS_STATUS_DETAIL)),240,LVCFMT_LEFT, 0,
		-1         ,   "",             0,   0,			0
	};

	InitBox(PUFFER_ANZAHL, Fields, sizeof(struct VecBuf));

	for (short ColNr = 0; ColNr < GetFieldCount(); ColNr++)
		free(Fields[ColNr].Columns);

	SetSelectBuffer(&m_SelBuf);
}

int CAGPMBox1::PrimeKeyOfSelectedRecord(long *PrimeKey1, long *PrimeKey2, long *Key3)
{
	struct VecBuf *Info;
	Info = (struct VecBuf *) GetSelectedVector();
	*PrimeKey1 = Info->AGP_NR;
	*PrimeKey2 = Info->PZN;
	*Key3 = Info->GUELTIG_AB;
	return 0;
}

int CAGPMBox1::PrimeKeyOfNextRecord(long *PrimeKey1, long *PrimeKey2, long *Key3)
{
	long lStatus;
	lStatus = GetNextSelect();
	if (lStatus != 0) return -1;
	*PrimeKey1 = m_SelBuf.AGP_NR;
	*PrimeKey2 = m_SelBuf.PZN;
	*Key3 = m_SelBuf.GUELTIG_AB;
	return 0;
}

int CAGPMBox1::PrimeKeyOfPrevRecord(long *PrimeKey1, long *PrimeKey2, long *Key3)
{
	long lStatus;
	lStatus = GetPrevSelect();
	if (lStatus != 0) return -1;
	*PrimeKey1 = m_SelBuf.AGP_NR;
	*PrimeKey2 = m_SelBuf.PZN;
	*Key3 = m_SelBuf.GUELTIG_AB;
	return 0;
}

bool CAGPMBox1::IsNumber(CString cStr)
{
	CString str;
	str = cStr;
	str.TrimLeft();
	str.TrimRight();
	if (str.IsEmpty()) return false;

	int i;
	i = 0;
	while (i < str.GetLength())
	{
		if (!isdigit((unsigned char)str.GetAt(i)))
			return false;
		i++;
	}
	return true;
}



// Gets Zeile status in text form 
CString CAGPMBox1::GetZeileStatus(short status)
{
	if (status >= 0)
	{
		switch (status)
		{
		case 0: return CResString::ex().getStrTblText(IDS_STRING1536);
			break;
		case 1: return CResString::ex().getStrTblText(IDS_STRING1537);
			break;
		case 2: return CResString::ex().getStrTblText(IDS_STRING1538);
			break;
		default:
			break;
		}
	}

	return "NA";

}


// ArtikelAgp dialog

CArtikelAgp::CArtikelAgp(CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(IDD_ARTIKEL_AGP, pParent)
{

}

CArtikelAgp::CArtikelAgp(CView* pView1, CView* pView2) // modeless constructor
	: CDialogMultiLang()
{
	m_pView1 = pView1;
	m_pView2 = pView2;
	if (pView1 == NULL || pView2 == NULL)
		m_bWithoutViews = TRUE;
	else
		m_bWithoutViews = FALSE;
	m_bFirstInit = TRUE;
	MakeDialog();
}

CArtikelAgp::~CArtikelAgp()
{
}

void CArtikelAgp::DoDataExchange(CDataExchange* pDX)
{
	CDialogMultiLang::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_ARTAGP_SUCHPZN, m_ARTSUCHPZN);
	DDX_Control(pDX, IDC_ED_ARTAGP_SUCHGUTAB, m_ARTSUCHGUTAB);
	DDX_Control(pDX, IDC_CB_ARTAGP_SUCHSTATUS, m_ARTSUCHSTATUS);
	DDX_Control(pDX, IDC_CB_ARTAGP_AGPNR, m_AGPNR);
	DDX_Control(pDX, IDC_LC_ARTAGP_BOX, m_ARTBOX);
	DDX_Control(pDX, IDC_ST_AGP_STATS, m_AGP_STATS);
	DDX_Control(pDX, IDC_ST_AGP_IMPBY, m_IMPORTBY);
	DDX_Control(pDX, IDC_ST_AGP_IMPDT, m_IMPORTDATUMZEIT);
	DDX_Control(pDX, IDC_ST_AGP_STATUS, m_IMPORTSTATUS);
	DDX_Control(pDX, IDC_PB_ARTAGP_RUEBL, m_RUEBL);
	DDX_Control(pDX, IDC_PB_ARTAGP_SUCHE, m_SUCHE);
	DDX_Control(pDX, IDC_PB_ARTAGP_VORBL, m_VORBL);
	DDX_Control(pDX, IDC_PB_ARTAGP_AGPNEU, m_cAGPNEU);
	DDX_Control(pDX, IDC_PB_ARTAGP_VALREPORT, m_cVALIDREPORT);
	DDX_Control(pDX, IDC_PB_ARTAGP_AGPDEL, m_cAGPLOESCHEN);
	DDX_Control(pDX, IDC_PB_ARTAGP_AGPDUPL, m_cAGPDUPLIZIEREN);
	DDX_Control(pDX, IDOK, m_cIDOK);
	DDX_Control(pDX, IDCANCEL, m_cIDCANCEL);
}

BEGIN_MESSAGE_MAP(CArtikelAgp, CDialogMultiLang)

	ON_BN_CLICKED(IDC_PB_ARTAGP_RUEBL, &CArtikelAgp::OnPbArtAgpRuebl)
	ON_BN_CLICKED(IDC_PB_ARTAGP_SUCHE, &CArtikelAgp::OnPbArtAgpSuche)
	ON_BN_CLICKED(IDC_PB_ARTAGP_VORBL, &CArtikelAgp::OnPbArtAgpVorbl)
	ON_BN_CLICKED(IDC_PB_ARTAGP_AGPNEU, &CArtikelAgp::OnPbArtAgpNeu)
	ON_BN_CLICKED(IDC_PB_ARTAGP_VALREPORT, &CArtikelAgp::OnPbArtAgpValReport)
	ON_BN_CLICKED(IDC_PB_ARTAGP_AGPDEL, &CArtikelAgp::OnPbArtAgpLoeschen)
	ON_BN_CLICKED(IDC_PB_ARTAGP_AGPDUPL, &CArtikelAgp::OnPbArtAgpDuplizieren)

	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_CB_ARTAGP_AGPNR, &CArtikelAgp::OnAgpnrSelChange)
	ON_NOTIFY(NM_DBLCLK, IDC_LC_ARTAGP_BOX, &CArtikelAgp::OnDblclkLcArtagpBox)
END_MESSAGE_MAP()



////////////////////////////////////////////////////////
// Suche Ueber F2

void CArtikelAgp::F2Suche()
{
	OnPbArtAgpSuche();
}

class CO_ArtikelAGP_Com : public ChComBase
{
public:
	CO_ArtikelAGP_Com(CArtikelAgp* pView) : ChComBase(pView) {};
	void DoIt(UINT nChar)
	{
		if (nChar == VK_F2)
			((CArtikelAgp*)m_pWnd)->F2Suche();
	}
};

// ArtikelAgp message handlers

void CArtikelAgp::GoOn(int woher)
{
	BOOL bOk;
	int  mRichtung;
	bOk = m_ARTBOX.ActualSelect(mRichtung);
	ShowWindow(SW_SHOW);
	if (bOk)
	{
		if (mRichtung == 1)			// vorgeblaettert
		{
			m_RUEBL.EnableWindow(TRUE);
		}
		else if (mRichtung == -1)		// rueckgeblaettert
		{
			m_VORBL.EnableWindow(TRUE);
		}
	}
	m_nWoher = woher;
}

BOOL CArtikelAgp::InitAgp()
{
	BOOL bOk = TRUE;
	CString errmld;

	if (m_bFirstInit)
	{
		((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
		m_nAgpAnz = SelectAgpNr(errmld);
		((CEkZdpApp*)AfxGetApp())->EndWaitAction();
		if (m_nAgpAnz > 0)
		{
			m_bFirstInit = FALSE;
		}
		else
		{
			bOk = FALSE;
		}
	}

	if (m_nAgpAnz > 0)
	{
		bOk = FillBoxAgpNr(errmld) == 0;
	}

	if (bOk)
	{
		m_AGPNR.SetMask(m_AgpMask, &m_cAgpnr, 0);

		m_dlg.DataExchangeFromBuffer();
	}
	else
	{
		MsgBoxOK(errmld);
	}

	return TRUE;
}

BOOL CArtikelAgp::Create(int woher)	// create on modeless constuctor
{
	BOOL bOk = CDialogMultiLang::Create(CArtikelAgp::IDD);
	if (bOk)
	{
		ShowWindow(SW_SHOW);
	}
	else
	{
		MsgBoxOK(CResString::ex().getStrTblText(IDS_AGP_CREATE_ERR));
	}
	m_nWoher = woher;
	return bOk;
}

void CArtikelAgp::InitPflege()
{

	m_pBuf = m_Doc.GetBuffer();

	//	MakeDialog();	// hier nicht, sondern im Constructor
	m_ARTBOX.InitSuchBox();
	m_SUCHE.SetMask(IDB_BM_SUCHE1, new CBitmap, NULL);
	m_VORBL.SetMask(IDB_BM_VORBL1, new CBitmap, NULL);
	m_RUEBL.SetMask(IDB_BM_RUEBL1, new CBitmap, NULL);

	// Scroll-Information
	m_ARTBOX.SetScrollInfo(ID_ARTIFA_VORBL2, ID_ARTIFA_RUEBL2, TRUE);

	m_ARTSUCHPZN.SetMask(ED_CHAR, ED_UPPER, m_cArtSuchPZN, L_ARTSUCHPZN, new ChMaskChar);
	m_ARTSUCHPZN.SetCommandHandler(new CO_ArtikelAGP_Com(this));

	m_ARTSUCHGUTAB.SetMask(ED_CHAR, ED_UPPER, m_cArtSuchGutAb, L_ARTSUCHGUTAB, new ChMaskChar);
	m_ARTSUCHGUTAB.SetCommandHandler(new CO_ArtikelAGP_Com(this));

	m_AGPNR.SetMask("A", &m_cAgpnr, 0);
	m_ARTSUCHSTATUS.SetMask("x0123", &m_cArtStatus, 0);

	m_VORBL.EnableWindow(FALSE);
	m_RUEBL.EnableWindow(FALSE);

	// Dialog aktivieren
	m_dlg.SetDialog(TRUE);

	m_cArtStatus = 'x';
	m_ARTSUCHSTATUS.p_SetInput();
}

int CArtikelAgp::PrimeKeyOfSelectedRecord(long *PrimeKey1, long *PrimeKey2, long *Key3)
{
	return m_ARTBOX.PrimeKeyOfSelectedRecord(PrimeKey1, PrimeKey2, Key3);
}

int CArtikelAgp::PrimeKeyOfNextRecord(long *PrimeKey1, long *PrimeKey2, long *Key3)
{
	return m_ARTBOX.PrimeKeyOfNextRecord(PrimeKey1, PrimeKey2, Key3);
}

int CArtikelAgp::PrimeKeyOfPrevRecord(long *PrimeKey1, long *PrimeKey2, long *Key3)
{
	return m_ARTBOX.PrimeKeyOfPrevRecord(PrimeKey1, PrimeKey2, Key3);
}


BOOL CArtikelAgp::OnInitDialog()
{
	CDialogMultiLang::OnInitDialog();

	InitPflege();

	FillComboBox();
	if (!InitAgp())
	{
		if (m_bWithoutViews)
		{
			EndDialog(-1);
		}
	}

	FillImportData();
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CArtikelAgp::MakeDialog()
{
	m_dlg.InitDialog(m_ARTSUCHPZN);
	m_dlg.InitDialog(m_ARTSUCHGUTAB);
	m_dlg.InitDialog(m_ARTSUCHSTATUS);
	m_dlg.InitDialog(m_AGPNR);
	m_dlg.InitDialog(m_RUEBL);
	m_dlg.InitDialog(m_SUCHE);
	m_dlg.InitDialog(m_VORBL);
	m_dlg.InitDialog(m_SUCHE);
}

void CArtikelAgp::OnCancel()
{
	if (m_bWithoutViews)
		CDialogMultiLang::OnCancel();
	else
	{
		m_pView1->SendMessage(ID_ARTAGP_END, IDCANCEL);	// AGP_View
	}
}

void CArtikelAgp::OnOK()
{
	CWnd *wnd = GetFocus();

	if (wnd == &m_ARTSUCHPZN)
	{
		OnPbArtAgpSuche();
		return;
	}

	if (!(wnd == &m_ARTBOX || wnd == &m_cIDOK))
	{
		NextDlgCtrl();
		return;
	}

	m_dlg.DataExchangeToBuffer();
	if (!m_ARTBOX.ItemChoise())
	{
		OnClose();
	}
	else
	{
		if (m_bWithoutViews)
			CDialogMultiLang::OnOK();
		else
			m_pView1->SendMessage(ID_ARTAGP_END, IDOK); // AGP_View
	}
}

// Loads previous batch of Artikels
void CArtikelAgp::OnPbArtAgpRuebl()
{

	if (m_ARTBOX.PrevSelect())
		m_VORBL.EnableWindow(TRUE);
	else
		m_RUEBL.EnableWindow(FALSE);
}

// Search Artikel based on Filters
void CArtikelAgp::OnPbArtAgpSuche()
{
	// Suchbegriff :  "STATUS\nAGPNR\nPZN\nGULTIG_AB" 	
	char str[20];
	CString suchb;
	CString suchtext;
	int index;


	m_ARTSUCHSTATUS.p_GetInput();
	sprintf(str, "%c", m_cArtStatus);
	suchb = str;
	suchb += '\n';
	// Agp Nr
	index = SelectAgpIndexFromCB();
	if (index >= 0 && index < m_nAgpAnz)
	{
		sprintf(str, "%ld", m_AGPKopf[index].AGP_NR);
		suchb += str;

		// PZN, Gültig ab and status
		m_ARTSUCHPZN.GetWindowText(suchtext);
		suchb += '\n';
		suchb += suchtext;
		m_ARTSUCHGUTAB.GetWindowText(suchtext);
		suchb += '\n';
		suchb += suchtext;
		suchb += '\n';

		if (m_ARTBOX.StartSelect(suchb, WITH_SCROLL | WITH_HOLD))
			m_VORBL.EnableWindow(TRUE);
		else
		{
			m_VORBL.EnableWindow(FALSE);
			m_SUCHE.SetFocus();
		}
		m_RUEBL.EnableWindow(FALSE);
	}
}

// Loads next batch of Artikels
void CArtikelAgp::OnPbArtAgpVorbl()
{

	if (m_ARTBOX.NextSelect())
		m_RUEBL.EnableWindow(TRUE);
	else
		m_VORBL.EnableWindow(FALSE);
}

/*
** Request the import of a new AGP File
*/
void CArtikelAgp::OnPbArtAgpNeu()
{
	char BASED_CODE szFilter[] = "CSV Dateien (.csv)|*.csv|Textdateien (*.txt)|*.txt|Alle Dateien (*.*)|*.*||";

	CFileDialog dlg(TRUE, "csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	// Selection AGP Import File
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	CString strFile = dlg.GetPathName();
	CString strFilename = dlg.GetFileName();
	CString strTitle = dlg.GetFileTitle();
	CString strReportFile = strFile.Left(strFile.GetLength()- strFilename.GetLength()) + strTitle + "_checked.csv";
	char*   anwender = ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender();
	CTime	startTime = CTime::GetCurrentTime();

	if (strFile.GetLength() <= 0)
	{
		return;
	}

	// create progress dialog
	ProgressDlg* pProgressDlg = new ProgressDlg();
	pProgressDlg->Create(IDD_PROGRESS, this);
	pProgressDlg->ShowWindow(SW_SHOW);
	pProgressDlg->InitData();
	// create importer
	ArtAgpImporter objImporter;
	objImporter.SetProgressDlg(pProgressDlg);
	// load file into memory
	BOOL ret = objImporter.LoadLocalCSVFile(strFile);
	ret = objImporter.ValidateCSVData();
	// save validation result into adhoc report
	objImporter.SaveLocalCSVCheckFile(strReportFile);

	if (ret == TRUE)
	{
		// insert data into database
		((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
		// create and save master data
		ret = objImporter.SaveMasterDataToDB(anwender);
		if (ret == TRUE)
		{
			// save detail data
			ret = objImporter.SaveDetailDataToDB();
		}
		((CEkZdpApp*)AfxGetApp())->EndWaitAction();
		RefreshSearchBox();
	}
	objImporter.SetProgressDlg(NULL);
	delete pProgressDlg;

	CTime endTime = CTime::GetCurrentTime();
	long diff = (long)(endTime.GetTime() - startTime.GetTime());
	char statsmsg[300];
	snprintf(statsmsg, 300, "Import war%s erfolgreich (Dauer 00:%02d:%02d).\nProtokoll %s erzeugt\n\n"
		"Gelesen: %ld, Validiert: %ld\nGültig: %ld - Warnungen : %ld - Fehler : %ld\n"
		"Es wurden %d neue Datenbank-Einträge erzeugt." , (ret==FALSE ? " nicht" : ""),
		(diff / 60) % 60, diff % 60, (LPCTSTR)strReportFile, objImporter.GetFileLineCount(), objImporter.GetDataCount(),
		objImporter.GetPassCount(), objImporter.GetWarnCount(), objImporter.GetErrorCount(), objImporter.GetSavedCount());
	MsgBoxOK(statsmsg, ret == FALSE ? MB_ICONEXCLAMATION : MB_ICONINFORMATION);

	return;
}

void CArtikelAgp::RefreshSearchBox()
{
	m_bFirstInit = TRUE;
	m_cAgpnr = 'A'; // Resets AGP Nr to first item.
	OnInitDialog();
}

// Generates validation report for import
void CArtikelAgp::OnPbArtAgpValReport()
{
	int status = -1;

	CFileDialog saveFileDialog(FALSE, NULL, CString("Prüfbericht"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Comma Separated Values (*.csv)|*.CSV"), 0);
	if (saveFileDialog.DoModal() == IDOK)
	{
		CFile validationfile;
		CFileException fe;
		CString fileName = _T("");
		if (saveFileDialog.GetFileExt().IsEmpty())
		{
			fileName = saveFileDialog.GetFolderPath() + "\\" + saveFileDialog.GetFileName() + ".csv";
		}
		else
		{
			fileName = saveFileDialog.GetFolderPath() + "\\" + saveFileDialog.GetFileName();
		}
		if (validationfile.Open(fileName, CFile::modeCreate | CFile::modeWrite, &fe) == TRUE)
		{
			((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
			status = GenerateValidationReport(validationfile);
			((CEkZdpApp*)AfxGetApp())->EndWaitAction();
			if (status != 0)
			{
				MsgBoxOK(CResString::ex().getStrTblText(IDS_AGP_PRUFBERICHT_ERR));
			}
			else
			{
				MsgBoxOK(CResString::ex().getStrTblText(IDS_AGP_PRUFBERICHT_SUCCESS), MB_ICONINFORMATION);
			}
			validationfile.Close();
		}
		else
		{
			MsgBoxOK(CResString::ex().getStrTblText(IDS_AGP_PRUFBERICHT_ERR));
		}
	}
}

// Deletes existing AGP import
void CArtikelAgp::OnPbArtAgpLoeschen()
{
	char msgcfm[200];
	int index = 0;
	// Gets selected Agp Nr
	index = SelectAgpIndexFromCB();

	sprintf(msgcfm, CResString::ex().getStrTblText(IDS_AGP_LOSCHEN_CONF), m_AGPKopf[index].AGP_INDEX);

	if (MsgBoxYesNo(msgcfm, MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
	{
		long c_delRowCount = 0;
		int lStatus = -1;
		// Begins wait
		((CEkZdpApp*)AfxGetApp())->BeginWaitAction();

		// Gets count of rows to delete
		c_delRowCount = m_Doc.GetAgpZeilenZahl(m_AGPKopf[index].AGP_NR);

		// Löschen AGP datei
		lStatus = m_Doc.DeleteAgpImport(m_AGPKopf[index].AGP_NR);

		// Ends wait
		((CEkZdpApp*)AfxGetApp())->EndWaitAction();

		if (lStatus != 0)
		{
			MsgBoxOK(CResString::ex().getStrTblText(IDS_AGP_FEHLER_LOSCHEN));
		}
		else
		{
			char msg[100];
			sprintf(msg, CResString::ex().getStrTblText(IDS_AGP_LOSCHEN_SUCCESS), c_delRowCount, m_AGPKopf[index].AGP_INDEX);
			MsgBoxOK(msg, MB_ICONINFORMATION);
			m_bFirstInit = TRUE;
			m_cAgpnr = 'A'; // Resets AGP Nr to first item.
			OnInitDialog();
		}
	}

}

void CArtikelAgp::OnClose()
{
	if (m_bWithoutViews)
	{
		CDialogMultiLang::OnClose();
	}
	else
	{
		m_pView2->SendMessage(ID_ARTAGP_END, IDCANCEL);	// Artikel_View
	}
}

int CArtikelAgp::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogMultiLang::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	return 0;
}

void CArtikelAgp::FillComboBox()
{
	m_ARTSUCHSTATUS.ResetContent();
	// Fills atrikel status combobox
	m_ARTSUCHSTATUS.AddString(CResString::ex().getStrTblText(IDS_STRING10134));
	m_ARTSUCHSTATUS.AddString(CResString::ex().getStrTblText(IDS_STRING1536));
	m_ARTSUCHSTATUS.AddString(CResString::ex().getStrTblText(IDS_STRING1537));
	m_ARTSUCHSTATUS.AddString(CResString::ex().getStrTblText(IDS_STRING1538));
	m_ARTSUCHSTATUS.AddString(CResString::ex().getStrTblText(IDS_STRING1549));
}

// Selects AGP Numbers from cagpoart table
int CArtikelAgp::SelectAgpNr(CString &errmld)
{
	long s;
	int  fd;
	int  anz;

	long agp_nr;
	long datum_anlage;
	long zeit_anlage;
	char anwender[9];
	char import_datei[31];
	short txn_status;
	long rec_erfolg;
	long rec_warnung;
	long rec_fehler;

	// show all AGP imports
	s = SqlOpenCs(&fd, "SELECT UNIQUE AGP_NR, DATUM_ANLAGE, ZEIT_ANLAGE, ANWENDER, IMPORT_DATEI, TXN_STATUS, REC_ERFOLG, REC_WARN, REC_FEHLER FROM CAGPOART "
		" ORDER BY DATUM_ANLAGE DESC, ZEIT_ANLAGE DESC");
	if (s != 0)
	{
		errmld = DynErrmld();
		return -1;
	}

	s = SqlFetch(fd, 1, &agp_nr, &datum_anlage, &zeit_anlage, &anwender, &import_datei, &txn_status, &rec_erfolg, &rec_warnung, &rec_fehler, NULL);
	if (s == 100)
	{
		errmld = CResString::ex().getStrTblText(IDS_NO_AGPIMPORT);
		SqlCloseCs(fd);
		return -1;
	}

	anz = 0;

	do
	{
		char index[30];
		sprintf(index, "%.4ld/%.2ld/%.2ld %.2ld:%.2ld:%.2ld (%ld)", datum_anlage / 10000, (datum_anlage % 10000) / 100, datum_anlage % 100,
			zeit_anlage / 10000, (zeit_anlage % 10000) / 100, zeit_anlage % 100, agp_nr);

		m_AGPKopf[anz].AGP_NR = agp_nr;
		strcpy(m_AGPKopf[anz].AGP_INDEX, index);
		strcpy(m_AGPKopf[anz].ANWENDER, anwender);
		strcpy(m_AGPKopf[anz].IMPORTDATEI, import_datei);
		m_AGPKopf[anz].DATUM_ANLAGE = datum_anlage;
		m_AGPKopf[anz].ZEIT_ANLAGE = zeit_anlage;
		m_AGPKopf[anz].TXN_STATUS = txn_status;
		m_AGPKopf[anz].REC_ERFOLG = rec_erfolg;
		m_AGPKopf[anz].REC_WARNUNG = rec_warnung;
		m_AGPKopf[anz].REC_FEHLER = rec_fehler;
		anz++;
		s = SqlFetch(fd, 1, &agp_nr, &datum_anlage, &zeit_anlage, &anwender, &import_datei, &txn_status, &rec_erfolg, &rec_warnung, &rec_fehler, NULL);
	} while (s == 0 && anz < MAX_AGP_ANZ);

	if (s < 0)
	{
		errmld = DynErrmld();
		SqlCloseCs(fd);
		return -1;
	}
	SqlCloseCs(fd);

	return anz;
}

// Fills AGP_NR combobox
int CArtikelAgp::FillBoxAgpNr(CString &errmld)
{
	int i;
	int nStatus;
	char mask;

	m_AGPNR.ResetContent();
	i = 0;
	nStatus = 0;
	mask = 'A';
	while (i < m_nAgpAnz && nStatus >= 0)
	{
		m_AgpMask[i] = mask++;
		nStatus = m_AGPNR.AddString(m_AGPKopf[i++].AGP_INDEX);
		if (nStatus == CB_ERR)
		{
			errmld = CResString::ex().getStrTblText(IDS_AGP_FILL_ERR);
		}
		else if (nStatus == CB_ERRSPACE)
		{
			errmld = CResString::ex().getStrTblText(IDS_AGP_FILL_NOT_ALL);
		}
	}
	m_AgpMask[i] = '\0';

	if (nStatus >= 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void  CArtikelAgp::FillImportData()
{
	int index;
	CString importStatDat;
	CString anwender;
	CString datumzeit_anlage;
	CString txn_status;

	BOOL pruefbutton = FALSE;
	BOOL deletebutton = FALSE;
	BOOL duplbutton = FALSE;

	char importVal[100];

	importStatDat = _T("");
	anwender = _T("");
	datumzeit_anlage = _T("");
	txn_status = _T("");
	// Agp Nr
	index = SelectAgpIndexFromCB();

	if ((index >= 0) && (index < m_nAgpAnz))
	{
		sprintf(importVal, "Datei:%s\nErfolg:%ld\nWarnung:%ld\nFehler:%ld", m_AGPKopf[index].IMPORTDATEI, m_AGPKopf[index].REC_ERFOLG, m_AGPKopf[index].REC_WARNUNG, m_AGPKopf[index].REC_FEHLER);
		importStatDat = importVal;
		importStatDat.TrimRight();

		anwender = m_AGPKopf[index].ANWENDER;
		anwender = anwender.Left(8);
		anwender.TrimRight();

		sprintf(importVal, "%.2ld.%.2ld.%.4ld %.2ld:%.2ld:%.2ld", m_AGPKopf[index].DATUM_ANLAGE % 100, (m_AGPKopf[index].DATUM_ANLAGE % 10000) / 100, m_AGPKopf[index].DATUM_ANLAGE / 10000,
			m_AGPKopf[index].ZEIT_ANLAGE / 10000, (m_AGPKopf[index].ZEIT_ANLAGE % 10000) / 100, m_AGPKopf[index].ZEIT_ANLAGE % 100);
		datumzeit_anlage = importVal;
		datumzeit_anlage.TrimRight();

		txn_status = GetTransactionStatus(m_AGPKopf[index].TXN_STATUS);
		txn_status.TrimRight();
		if (m_AGPKopf[index].TXN_STATUS == TXN_STATUS_IMPORTED)
		{
			// imported status enables report and delete buttons
			pruefbutton = TRUE;
			deletebutton = TRUE;
			if (m_AGPKopf[index].DATUM_ANLAGE == ::Today())
			{
				// enable duplication only if its from same day
				duplbutton = TRUE;
			}
		}
		else if (m_AGPKopf[index].TXN_STATUS == TXN_STATUS_TRANSFERRED)
		{
			// transferred status enables only report button
			pruefbutton = TRUE;
		}
	}
	// set data into UI fields
	m_AGP_STATS.SetWindowText(importStatDat);
	m_IMPORTBY.SetWindowText(anwender);
	m_IMPORTDATUMZEIT.SetWindowText(datumzeit_anlage);
	m_IMPORTSTATUS.SetWindowText(txn_status);

	// enable or disable buttons based on data
	m_cVALIDREPORT.EnableWindow(pruefbutton);
	m_cAGPLOESCHEN.EnableWindow(deletebutton);
	m_cAGPDUPLIZIEREN.EnableWindow(duplbutton);
}

void CArtikelAgp::OnAgpnrSelChange()
{
	FillImportData();
}


void CArtikelAgp::OnPbArtAgpArtpfl()
{
	m_dlg.DataExchangeToBuffer();
	if (!m_ARTBOX.ItemChoise())
	{
		OnClose();
	}
	else
	{
		if (m_bWithoutViews)
		{
			CDialogMultiLang::OnOK();
		}
		else
		{
			m_pView2->SendMessage(ID_ARTAGP_END, IDOK); // Agp_View
		}
	}
}

void CArtikelAgp::OnDblclkLcArtagpBox(NMHDR*, LRESULT *pResult)
{
	*pResult = 0;
	//  Doppelklickk wie OnOK()
	if (m_nWoher == 1)
		OnOK();					 // goto AGP View
	else
		OnPbArtAgpArtpfl(); // goto AGP Artikel View
}

// Gets the transaction status in text format
CString CArtikelAgp::GetTransactionStatus(short status)
{
	CString answer;

	if (status >= 0)
	{
		switch (status)
		{
		case TXN_STATUS_NOT_IMPORTED:
			answer = CResString::ex().getStrTblText(IDS_STRING1543);
			break;
		case TXN_STATUS_IMPORTED:
			answer = CResString::ex().getStrTblText(IDS_STRING1539);
			break;
		case TXN_STATUS_TRANSFERRED:
			answer = CResString::ex().getStrTblText(IDS_STRING1540);
			break;
		case TXN_STATUS_DELETED:
			answer = CResString::ex().getStrTblText(IDS_STRING1541);
			break;
		case TXN_STATUS_ARCHIVED:
			answer = CResString::ex().getStrTblText(IDS_STRING1542);
			break;
		default:
			answer = _T("Unbekannte Transaktion");
		}
	}
	return answer;
}

// Selects Agp Nr from combobox
int CArtikelAgp::SelectAgpIndexFromCB()
{
	int index = 0;
	// Agp Nr
	m_AGPNR.p_GetInput();
	index = (int)(m_cAgpnr - 'A');
	return index;
}

// Selects Agp Nr in combobox
void CArtikelAgp::SelectAgpIndexInCB(long agpnr)
{
	int index = 0;
	BOOL bFnd = FALSE;

	while ((index < m_nAgpAnz) && (bFnd == FALSE))
	{
		if (m_AGPKopf[index].AGP_NR == agpnr)
		{
			m_cAgpnr = (char)('A' + index);
			m_AGPNR.SetCurSel(index);
			bFnd = TRUE;
			FillImportData();
		}
		index++;
	}
}

// Generates validation report
int CArtikelAgp::GenerateValidationReport(CFile &file)
{
	int status = -1;
	int index;
	// Selects AGP Index
	index = SelectAgpIndexFromCB();
	if ((index >= 0) && (index < m_nAgpAnz))
	{
		CString sql;
		CString sqlFilters;
		CString pznFilter;
		CString ga_Filter;
		CString zeileStatus;
		long s;
		int  fd;
		long agpNr;
		long countMaxRows = 0;
		long anz = 0;
		sql = _T("");
		sqlFilters = _T("");
		ga_Filter = _T("");
		pznFilter = _T("");
		zeileStatus = _T("");

		// Gets AGR Nr
		agpNr = m_AGPKopf[index].AGP_NR;
		// Gets STATUS
		m_ARTSUCHSTATUS.p_GetInput();

		// PZN
		m_ARTSUCHPZN.GetWindowText(pznFilter);
		// Gültig Ab
		m_ARTSUCHGUTAB.GetWindowText(ga_Filter);


		// Sets cursor query
		sql += _T("SELECT AGP_NR, PZN, ZEILE_NR, AGP, GUELTIG_AB, ZEILE_STATUS, STATUS_DETAIL FROM ");

		sqlFilters.Format(" CAGPART WHERE AGP_NR = %ld ", agpNr);


		// Sets PZN Filter
		if (!pznFilter.IsEmpty())
		{
			sqlFilters += _T(" AND PZN = ") + pznFilter;
		}

		// Get Gültig Ab filter value
		if (!ga_Filter.IsEmpty() && ga_Filter.GetLength() == 10)
		{
			ga_Filter.Remove('.');
			if (m_ARTBOX.IsNumber(ga_Filter))
			{
				long date = atol(ga_Filter);
				ga_Filter.Format("%.4ld%.2ld%.2ld", date % 10000, (date / 10000) % 100, date / 1000000);
				sqlFilters += _T(" AND GUELTIG_AB = ") + ga_Filter;
			}
		}

		// sets Ziele Status condition
		if (m_ARTBOX.IsNumber(m_cArtStatus))
		{
			if (m_cArtStatus == '3') // Checks if Warnung & Fehler is selected
			{
				sqlFilters += _T(" AND ZEILE_STATUS IN (1, 2) ");
			}
			else
			{
				sqlFilters += _T(" AND ZEILE_STATUS = ") + CString(m_cArtStatus);
			}
		}

		sql += sqlFilters;
		sql += _T(" ORDER BY ZEILE_NR ASC");

		// Gets database row count
		SqlCount(sqlFilters, &countMaxRows);

		if (countMaxRows > 0)
		{
			char statsmsg[300];
			ProgressDlg* pProgressDlg = new ProgressDlg();
			pProgressDlg->Create(IDD_PROGRESS, this);
			pProgressDlg->ShowWindow(SW_SHOW);
			pProgressDlg->InitData();
			pProgressDlg->SetHeader("AGP Prüfbericht");
			pProgressDlg->SetBar(countMaxRows, 0);
			snprintf(statsmsg, 300, "Prüfbericht: %s\nDatensätze gefunden: %i", file.GetFileName().GetString(), countMaxRows);
			pProgressDlg->SetText(statsmsg);

			// Open DB Cursor
			s = SqlOpenCs(&fd, sql);
			if (s != 0)
			{
				status = -1;
			}

			// Header line	
			char *KopfZeile = "PZN;AGP;GUELTIG AB;ZEILE NR;STATUS;VALIDIERUNGSTEXT";
			char reportLine[150];
			char separator = ';';
			char strDate[10];
			char strStatus[10];
			CString strAGP;
			int pct = 0;

			file.Write(KopfZeile, (UINT)strlen(KopfZeile));
			// Begin Fetch
			s = SqlFetch(fd, 1, &m_ValReportBuf, NULL);

			do
			{
				pct = anz * 100 / countMaxRows;
				snprintf(statsmsg, 300, "AGP Prüfbericht: %i%%", pct);
				pProgressDlg->SetHeader(statsmsg);
				pProgressDlg->SetBar(countMaxRows, anz);
				snprintf(statsmsg, 300, "Prüfbericht: %s\nDatensätze gefunden: %i\nExportierter Datensatz %i...", file.GetFileName().GetString(), countMaxRows, anz);
				pProgressDlg->SetText(statsmsg);

				// Formats Gültig Ab datum
				sprintf(strDate, "%.2ld.%.2ld.%.4ld", m_ValReportBuf.GUELTIG_AB % 100, (m_ValReportBuf.GUELTIG_AB % 10000) / 100,
					m_ValReportBuf.GUELTIG_AB / 10000);
				strcpy(strStatus, m_ARTBOX.GetZeileStatus(m_ValReportBuf.ZEILE_STATUS));

				// convert AGP into different format
				strAGP.Format("%.2f", m_ValReportBuf.AGP);
				strAGP.Replace(".", ",");
				// PZN, AGP, ZEILE_NR, GUELTIG_AB, ZEILE_STATUS, STATUS_DETAIL
				sprintf(reportLine, "\n%ld%c%s%c%s%c%ld%c%s%c%s", m_ValReportBuf.PZN, separator, (LPCTSTR)strAGP, separator
					, strDate, separator, m_ValReportBuf.ZEILE_NR, separator, strStatus, separator, m_ValReportBuf.STATUS_DETAIL);

				file.Write(reportLine, (UINT)strlen(reportLine));

				s = SqlFetch(fd, 1, &m_ValReportBuf, NULL);
				anz++;
			} while (s == 0 && anz < countMaxRows);

			SqlCloseCs(fd);
			// Delete the progress dialog once done
			delete pProgressDlg;

			status = (s < 0) ? -1 : 0;
		}
	}

	return status;
}

/*
** Duplicate records of currently selected import.
*/
void CArtikelAgp::OnPbArtAgpDuplizieren()
{
	int index = SelectAgpIndexFromCB();
	CString importname = _T(m_AGPKopf[index].IMPORTDATEI);
	CArtAgpImportGen generateImpDlg(m_AGPKopf[index].AGP_NR, importname);

	if (generateImpDlg.DoModal() == IDOK)
	{
		long agpnr = generateImpDlg.GetNewAGPNr();
		this->RefreshSearchBox();
		if (agpnr != 0)
		{
			this->SelectAgpIndexInCB(agpnr);
		}
	}
}
