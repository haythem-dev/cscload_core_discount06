// ArtAgpImportGen.cpp : implementation file
//

#include "stdafx.h"
#include "Ekzdp.h"
#include "libscsvoodoo/libscsvoodoo.h"
#include "voodoo_table_header/cagpoart.h"
#include "eklibs/wdbups/wpp_prot.h"
#include "ServerDatum.h"
#include "ArtAgpImportGen.h"
#include "afxdialogex.h"

#ifndef SQL_OK
#define SQL_OK   0L
#define SQL_NOK -1L
#endif

// CArtAgpImportGen dialog

IMPLEMENT_DYNAMIC(CArtAgpImportGen, CDialogEx)

CArtAgpImportGen::CArtAgpImportGen(long lngCurrentAGPNr, CString strCurrentImportName, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ARTAGP_IMPGEN, pParent)
{
	m_curAGPNr = lngCurrentAGPNr;
	m_curImportName = strCurrentImportName.Trim();
	m_curImportName.Replace(".csv", "");
	m_newImportName.Format("%s_dupl(%ld).csv", m_curImportName, m_curAGPNr);
	m_newAGPNr = 0;
}

CArtAgpImportGen::~CArtAgpImportGen()
{
}

void CArtAgpImportGen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CArtAgpImportGen, CDialogEx)
	ON_BN_CLICKED(ID_PB_PASS, &CArtAgpImportGen::OnPbPass)
	ON_BN_CLICKED(ID_PB_PASS_WARN, &CArtAgpImportGen::OnPbPassWarn)
	ON_BN_CLICKED(IDCANCEL, &CArtAgpImportGen::OnPbCancel)
END_MESSAGE_MAP()


// CArtAgpImportGen message handlers

BOOL CArtAgpImportGen::OnInitDialog()
{
	BOOL response = CDialogEx::OnInitDialog();

	// Set default content for duplicated import file name entry field
	GetDlgItem(IDC_CUR_IMPORT_NAME)->SetWindowTextA(m_curImportName);
	GetDlgItem(IDC_NEW_IMPORT_NAME)->SetWindowTextA(m_newImportName);

	return response;
}

void CArtAgpImportGen::OnPbPass()
{
	BOOL ret = generateImport(false);
	if (ret == TRUE)
	{
		CDialogEx::OnOK();
	}
	else
	{
		CDialogEx::OnCancel();
	}
}

void CArtAgpImportGen::OnPbPassWarn()
{
	BOOL ret = generateImport(true);
	if (ret == TRUE)
	{
		CDialogEx::OnOK();
	}
	else
	{
		CDialogEx::OnCancel();
	}
}

void CArtAgpImportGen::OnPbCancel()
{
	CDialogEx::OnCancel();
}

long CArtAgpImportGen::updateImportMaster(bool withWarnings)
{
	struct CAGPOART master, refMaster;
	CString sql = _T("");
	char constraint[20];
	char buf[200];
	int  dbHandle;
	long s;
	long newAgpNr;

	memset(&master,    0, sizeof(struct CAGPOART));
	memset(&refMaster, 0, sizeof(struct CAGPOART));

	// read max value of AGP index and add one for duplication
	sql.Format("SELECT MAX(agp_nr) FROM cagpoart");
	if (SQL_OK != (s = SqlRead(sql, &newAgpNr, NULL))) 
	{
		MsgBoxOK("Fehler: Kann neuen AGP Index nicht ermitteln!", MB_ICONEXCLAMATION);
		return s;
	}
	newAgpNr++;

	// read header data from AGP from current AGP import
	snprintf(constraint, sizeof(constraint) - 1, "AGP_NR=%ld", m_curAGPNr);
	if (SQL_OK != (s = OpenBufferDesc(&dbHandle, "cagpoart", NULL, NULL, V_PROTOKOL, buf)))
	{
		MsgBoxOK("Fehler: Kann AGP Kopfdaten nicht laden!", MB_ICONEXCLAMATION);
		return s;
	}

	if (SQL_OK != (s = FdReadRecord(dbHandle, constraint, &refMaster, buf)))
	{
		MsgBoxOK("Fehler: Kann AGP Kopfdaten nicht laden!", MB_ICONEXCLAMATION);
		CloseBufferDesc();
		return s;
	}

	// create data for new header
	GetDlgItem(IDC_NEW_IMPORT_NAME)->GetWindowTextA(m_newImportName);
	snprintf(constraint, sizeof(constraint) - 1, "AGP_NR=%ld", newAgpNr);

	master.AGP_NR       = newAgpNr;
	master.DATUM_ANLAGE = refMaster.DATUM_ANLAGE;
	master.ZEIT_ANLAGE  = refMaster.ZEIT_ANLAGE;
	master.DATUM_AENDER = ::Today();
	master.TXN_STATUS   = 1; /* imported */
	strncpy(master.ANWENDER, ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender(), sizeof(master.ANWENDER) - 1);
	strncpy(master.IMPORT_DATEI, (LPCTSTR)m_newImportName, sizeof(master.IMPORT_DATEI) - 1);
	master.REC_ERFOLG   = refMaster.REC_ERFOLG;
	master.REC_WARN     = withWarnings ? refMaster.REC_WARN : 0;
	// insert header data into database
	if (SQL_OK != (s = FdInsertRecord(dbHandle, &master, constraint, buf)))
	{
		MsgBoxOK("Fehler: Kann AGP Kopfdaten nicht schreiben!", MB_ICONEXCLAMATION);
		m_newAGPNr = 0;
	}
	else
	{
		// successful, so take over the new AGP index
		m_newAGPNr = newAgpNr;
	}
	CloseBufferDesc();
	return s;
}

BOOL CArtAgpImportGen::generateImport(bool withWarnings)
{
	const char* detail_columns = "agp_nr, pzn, zeile_nr, agp, gueltig_ab, zeile_status, status_detail";
	short statusMax = withWarnings ? 1 : 0;
	CString sql = _T("");
	long s;

	if ((SQL_OK != this->updateImportMaster(withWarnings)) || (m_newAGPNr == 0))
	{
		// something wrong with header data
		return FALSE;
	}

	if (SQL_OK != (s = SqlBeginWork())) 
	{
		MsgBoxOK("Kann Transaktion nicht starten!", MB_ICONEXCLAMATION);
		return FALSE;
	}

	sql.Format("INSERT INTO cagpart(%s)"
		"  SELECT %ld AS %s"
		"  FROM cagpart"
		"  WHERE agp_nr=%ld AND zeile_status BETWEEN 0 AND %d",
		detail_columns, m_newAGPNr, detail_columns, m_curAGPNr, statusMax);

	if (SQL_OK == SqlExecuteImm(sql))
	{
		SqlCommitWork();
		return TRUE;
	}
	else
	{
		SqlRollbackWork();
	}
	return FALSE;
}
