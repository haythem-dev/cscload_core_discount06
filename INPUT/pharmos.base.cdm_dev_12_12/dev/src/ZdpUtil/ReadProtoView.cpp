// ReadProtoView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZdpUtil.h"
#include "ReadProtoView.h"

#include <libscsvoodoo/libscsvoodoo.h>  // for Unix file operations

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadProtoView

IMPLEMENT_DYNCREATE(CReadProtoView, CFormView)

CReadProtoView::CReadProtoView()
	: ChPflegeView(CReadProtoView::IDD)
{
	//{{AFX_DATA_INIT(CReadProtoView)
	//}}AFX_DATA_INIT
	theApp = ((CZdpUtilApp*)AfxGetApp());
	m_bDoResize  = false;
}

CReadProtoView::~CReadProtoView()
{
}

void CReadProtoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadProtoView)
	DDX_Control(pDX, IDC_ED_NAME_CSV, m_CSV_Filename);
	DDX_Control(pDX, IDC_CB_PROTO_FILES, m_cbProtoFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReadProtoView, CFormView)
	//{{AFX_MSG_MAP(CReadProtoView)
	ON_BN_CLICKED(IDC_BT_SEARCH_CSV, OnReadProtoSearchCsv)
	ON_BN_CLICKED(IDC_BT_SEARCH_PROTO, OnReadProtoSearchUnx)
	ON_BN_CLICKED(IDC_BT_TRANSFER_PROTO, OnReadProtoTransferToWin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Diagnose CReadProtoView

#ifdef _DEBUG
void CReadProtoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CReadProtoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////
// Implementation

//#define MAX_SPALTE 50
//
//void CReadProtoView::InitPflege()
//{
////	m_SPALTE.SetLimitText( MAX_SPALTE );
//}

void CReadProtoView::InitVariables()
{
	m_CSV_Filename.SetWindowText("");
	m_CSV_Filename.SetFocus();
	m_cbProtoFiles.ResetContent();
	m_cbProtoFiles.EnableWindow(false);
}


/////////////////////////////////////////////////////////////////////////////
// Virtuals aus ChPfegeView

//int  CReadProtoView::BearbeiteSatz()

//int  CReadProtoView::SpeichereSatz( )

//int  CReadProtoView::UndoSatz()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CReadProtoView 

void CReadProtoView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CReadProtoView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
		if ( pActivateView != pDeactiveView )
		{
			m_bDoResize = true;
			if ( !m_bComeBack )
			{
				InitVariables();
				theApp->SetMenuOnOff( 1, 1, -1, -1, -1, -1 ); 
			}
			else
			{
				m_bComeBack = false;
				theApp->PopMenuState(  );
				theApp->SetMenuOnOff( 1, 1, -1, -1, -1, -1 ); 
			}
		}		
	}
}



////////////////////////////////////////////////
// Drucken

//bool CReadProtoView::GetInfoFromCallingView( CString& cStr, int nAction )
//{
//	return true;
//}

////////////////////////////////////////////////
// Name der .csv-Datei holen

void CReadProtoView::OnReadProtoSearchCsv()
{
	// Input 
	char BASED_CODE szFilter[] = 
		 "(*.csv)|*.csv||";
	CFileDialog dlg( TRUE,  "*",
							NULL,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							szFilter );         

	if ( dlg.DoModal() != IDOK )
		return;

	CString sFileName;
	sFileName = dlg.GetFileName();	
	if ( sFileName.IsEmpty( ) )
		return;	

	m_CSV_Filename.SetWindowText( sFileName );

	return;
}

////////////////////////////////////////////////
// Suche nach Protokoll-Dateien zur CSV-Datei

void CReadProtoView::OnReadProtoSearchUnx() 
{
	int len;
	CString cErrmld;
	char CSV_Filename[130];

	len = m_CSV_Filename.GetLine(128, CSV_Filename);
	if (0 == len)
	{
		cErrmld += "Fehler: Dateiname der .csv-Datei fehlt\n";
		MsgBoxOK(cErrmld);
		return;
	}

	CSV_Filename[len] = '_';
	len++;		// length of search string
	CSV_Filename[len] = '\0';

	CString cProtoSearch(CSV_Filename);

	CString cDirec;
	CStringArray cFileNames;
	long s = GetWWSDateiUnterVerz(cDirec, util, cErrmld);
	if (s != 0)
	{
		MsgBoxOK(cErrmld);
		return;
	}

	s = GetFileNames(cDirec, cFileNames, cErrmld);
	if (s != 0)
	{
		cErrmld += "Fehler beim Laden der Protokoll-Dateien";
		MsgBoxOK(cErrmld);
		return;
	}

	int numNames = (int) cFileNames.GetCount();

	// check if filename begins with the search string
	// if yes, add it to the combobox
	// array indices from numNames-1 to 0 descending (to show newest file in position 0)
	m_cbProtoFiles.ResetContent();

	int i = numNames;
	while (i > 0)
	{
		i--;
		if ((cFileNames.GetAt(i)).Left(len) == cProtoSearch)
		{
			m_cbProtoFiles.AddString((LPCTSTR) cFileNames.GetAt(i));
		}
	}

	if (m_cbProtoFiles.GetCount() == 0)
	{
		cErrmld += "Keine Protokoll-Dateien gefunden";
		MsgBoxOK(cErrmld);
		return;
	}

	m_cbProtoFiles.SetCurSel(0);

	m_cbProtoFiles.EnableWindow(true);


	return;	
}

////////////////////////////////////////////////
// Protokoll-Datei nach Windows übertragen

void CReadProtoView::OnReadProtoTransferToWin()
{
	const int buf_size = 500000;   // default stack size is 1MB (VS 2015)
	short Index;
	CString cFilename;
	CString cPath;
	CString cErrmld;
	long s;
	int  fd;
	char buf[buf_size + 1];
	int file_len = buf_size;

	Index = m_cbProtoFiles.GetCurSel();
	m_cbProtoFiles.GetLBText(Index, cFilename);

	s = GetWWSDateiUnterVerz(cPath, util, cErrmld);
	if (s != 0)
	{
		MsgBoxOK(cErrmld);
		return;
	}

	cPath += cFilename;
	if (UnxFopen(&fd, cPath, "r") != 0)
	{
		cErrmld += DynErrmld();
		cErrmld += " - Fehler beim Öffnen der Datei (UnxFopen)\n";
		MsgBoxOK(cErrmld);

		return;
	}

	if (UnxFread(fd, buf, &file_len) != 0)   // size of buf has to be at least file_len+1 to prevend buffer overflow
	{
		if (0 == file_len)
		{
			cErrmld += "Die Protokoll-Datei ist leer";
		}
		else {
			cErrmld += DynErrmld();
			cErrmld += " - Fehler beim Lesen der Datei (UnxFread)\n";
		}
		MsgBoxOK(cErrmld);
		UnxFclose(fd);

		return;
	}
	UnxFclose(fd);

	if (file_len == buf_size)
	{
		if (IDNO == MsgBoxYesNo("Protokoll-Datei kann nicht vollständig übertragen werden (Puffer zu klein)!\nTrotzdem übertragen?"))
			return;
	}

	CFileDialog dlg( FALSE, NULL, (LPCTSTR) cFilename );


	if ( dlg.DoModal() == IDOK )
	{
		CString cWinPath = dlg.GetPathName();
		CFile cProtocolFile(cWinPath, CFile::modeCreate | CFile::modeWrite);
		cProtocolFile.Write( buf, (UINT) file_len );
		cProtocolFile.Close();
	}

	return;
}

long CReadProtoView::GetFileNames(CString cPfad, CStringArray& DateiNamen, CString& errmld)
{
	long s;
	int  i;
	//int  j;
	int  mode = DIR_DNORM;
	char *log_path;
	char datei[300];
	CString cName;

	log_path = (char *)((LPCTSTR)cPfad);

	i = 0;
	s = UnxDirEntry(log_path, datei, &mode);

	while (s == 0)
	{	
		if ( mode == DIR_DNORM )
		{
			ExtractDateiName(datei, cName);
			DateiNamen.SetSize(i + 1);
			DateiNamen[i++] = cName;
		}
		s = UnxDirEntry(NULL, datei, &mode);
	}

	if (i == 0)
	{
		if (mode == DIR_ERROR)
		{
			//errmld = CResString::ex().getStrTblText(IDS_STRINGxxx);
		}
		else
			errmld = DynErrmld();
		s = -1;
	}
	else
		s = 0;

	return s;
}

void CReadProtoView::ExtractDateiName(char *name, CString& cName)
{
	int pos;

	cName = name;
	pos = 0;
	while (pos >= 0)
	{
		pos = cName.Find('/');
		if (pos >= 0)
			cName = cName.Mid(pos + 1);
	}
}