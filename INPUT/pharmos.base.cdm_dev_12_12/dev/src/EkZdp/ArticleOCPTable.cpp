// ArticleOCPTable.cpp : implementation file
//

#include "stdafx.h"
#include "Ekzdp.h"
#include "ArticleOCPTable.h"
#include "afxdialogex.h"
#include <libscsvoodoo/libscsvoodoo.h>
#include <eklibs/hamfcs/hMskChar.h>
// ArticleOCPTable dialog

IMPLEMENT_DYNAMIC(CArticleOCPTable, CDialogEx)

CArticleOCPTable::CArticleOCPTable(COCPStagingDoc* pDoc, int tabletype, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ARTICLE_OCPTABLE, pParent)
{
	m_pobjDoc = pDoc;
	m_intTableType = tabletype;
}

CArticleOCPTable::~CArticleOCPTable()
{
	ResetData();
}

void CArticleOCPTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ZDP_RECORDS, m_edtZDPRecordCount);
	DDX_Control(pDX, IDC_EDIT_OCP_RECORDS, m_edtOCPRecordCount);
	DDX_Control(pDX, IDC_LIST_ARTICLE_DETAIL_RECORDS, m_lstArticleDetailRecords);
}

BEGIN_MESSAGE_MAP(CArticleOCPTable, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_RELOADRECORDS, &CArticleOCPTable::OnClickedReloadRecords)
	ON_BN_CLICKED(IDC_BTN_SAVERECORDS, &CArticleOCPTable::OnClickedSaveRecords)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ARTICLE_DETAIL_RECORDS, &CArticleOCPTable::OnDblClickListArticleDetailRecords)
	ON_BN_CLICKED(IDC_BTN_SETRECORDPREFERRED, &CArticleOCPTable::OnClickedSetRecordPreferred)
END_MESSAGE_MAP()

void CArticleOCPTable::ResetData()
{
}

BOOL CArticleOCPTable::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// reset counters
	m_edtZDPRecordCount.SetWindowText("0");
	m_edtOCPRecordCount.SetWindowText("0");

	// table is article codes
	if (m_intTableType == 0)
	{
		COLUMN_TYPES TableColumns[] =
		{
			0, "Origin", 90, LVCFMT_LEFT,
			1, "OCP ArticleNo", 90, LVCFMT_LEFT,
			2, "Code Type", 100, LVCFMT_LEFT,
			3, "Article Code", 120, LVCFMT_LEFT,
			4, "Preferred Flag", 90, LVCFMT_LEFT,
			5, "Changed Date", 90, LVCFMT_LEFT,
			6, "Status", 240, LVCFMT_LEFT,
			-1, NULL, 0, 0
		};
		LV_COLUMN lvC;
		lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

		for (COLUMN_TYPES* pType = TableColumns; pType->Index != -1; pType++)
		{
			lvC.iSubItem = pType->Index;
			lvC.pszText = LPTSTR(pType->Columns);
			lvC.fmt = pType->Align;
			lvC.cx = pType->Width;

			m_lstArticleDetailRecords.InsertColumn(pType->Index, &lvC);
		}
	}
	// set the behavior of the table
	m_lstArticleDetailRecords.ShowScrollBar(SB_VERT, 0);
	m_lstArticleDetailRecords.SetExtendedStyle(m_lstArticleDetailRecords.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_GRIDLINES);
	m_lstArticleDetailRecords.SetSingleLineSelection();
	m_lstArticleDetailRecords.SetFullRowSel(FALSE);

	FillRecords();

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CArticleOCPTable::OnClickedReloadRecords()
{
	m_pobjDoc->ValidateOCPArticleCodes();
	FillRecords();
}

void CArticleOCPTable::FillRecords()
{
	CString owner = "";
	CString origin = "";
	m_lstArticleDetailRecords.DeleteAllItems();
	m_lstArticleDetailRecords.EnableWindow(true);
	int systemcnt = 0;
	int importcnt = 0;
	// fill the table
	if (m_intTableType == 0)
	{
		// write articleCode rows on the grid
		std::vector<COCP_STAGEOUT_ARTICLECODE*>::iterator itc;
		for (itc = m_pobjDoc->m_stageoutNewArticleCodes.begin(); itc != m_pobjDoc->m_stageoutNewArticleCodes.end(); itc++)
		{
			COCP_STAGEOUT_ARTICLECODE* pData = *itc;
			origin = CString(pData->USERNAME).Trim();
			if (origin.CompareNoCase("system") == 0)
			{
				origin = "ZDP (system)";
				systemcnt++;
			}
			else
			{
				origin = "OCP (import)";
				importcnt++;
			}
			int nItem = m_lstArticleDetailRecords.InsertItem(m_lstArticleDetailRecords.GetItemCount(), origin);
			m_lstArticleDetailRecords.SetItemText(nItem, 1, m_pobjDoc->ConvertLong2CString(pData->OCP_ARTICLE_NO, true).Trim());
			m_lstArticleDetailRecords.SetItemText(nItem, 2, m_pobjDoc->ConvertLong2CString(pData->CODE_TYPE, true));
			m_lstArticleDetailRecords.SetItemText(nItem, 3, CString(pData->ARTICLE_CODE).Trim());
			m_lstArticleDetailRecords.SetItemText(nItem, 4, m_pobjDoc->ConvertLong2CString(pData->PREFERRED_FLAG, true));
			m_lstArticleDetailRecords.SetItemText(nItem, 5, m_pobjDoc->ConvertDate2CString(pData->DATE_CHANGED, true));
			owner = "";
			if ((pData->SUM_STATE_FLAGS[0] == '2') || (pData->SUM_STATE_FLAGS[0] == '5') || (pData->SUM_STATE_FLAGS[0] == '8'))
			{
				if (origin.CompareNoCase("OCP (import)") != 0)
				{
					owner = " (updated by import)";
				}
			}
			else if ((pData->SUM_STATE_FLAGS[0] == '3') || (pData->SUM_STATE_FLAGS[0] == '6') || (pData->SUM_STATE_FLAGS[0] == '9'))
			{
				owner = " (updated by user)";
			}
			if ((pData->SUM_STATE_FLAGS[0] == '4') || (pData->SUM_STATE_FLAGS[0] == '5') || (pData->SUM_STATE_FLAGS[0] == '6'))
			{
				m_lstArticleDetailRecords.SetItemText(nItem, 6, "Validation Error" + owner);
			}
			else
			{
				m_lstArticleDetailRecords.SetItemText(nItem, 6, "Validation Successful" + owner);
			}
		}
		// set the counters
		m_edtZDPRecordCount.SetWindowText(m_pobjDoc->ConvertLong2CString(systemcnt, true));
		m_edtOCPRecordCount.SetWindowText(m_pobjDoc->ConvertLong2CString(importcnt, true));
	}
}

void CArticleOCPTable::OnClickedSaveRecords()
{
	int row = 0; 
	// check the values for any updates
	if (m_intTableType == 0)
	{
		// check at first if preferred_flag=1 is set once
		int prefcnt = 0;
		for (row = 0; row < m_lstArticleDetailRecords.GetItemCount(); row++)
		{
			CString val = m_lstArticleDetailRecords.GetItemText(row, 4).Left(1);
			if (val.Compare("1") == 0)
			{
				prefcnt++;
			}
		}
		if (prefcnt == 0)
		{
			MessageBox("At least one ArticleCode Mapping has to be set with Preferred Flag = 1\nRecords are not saved!", "Validation Error");
			return;
		}
		else if (prefcnt > 1)
		{
			MessageBox("Only one ArticleCode Mapping has to be set with Preferred Flag = 1\nRecords are not saved!", "Validation Error");
			return;
		}
		// check done, so save
		if (MessageBox("Are you sure you want to save the updated Article Code Mappings?", "Save Article Codes", MB_YESNO) == IDYES)
		{
			row = 0;
			std::vector<COCP_STAGEOUT_ARTICLECODE*>::iterator itc;
			for (itc = m_pobjDoc->m_stageoutNewArticleCodes.begin(); itc != m_pobjDoc->m_stageoutNewArticleCodes.end(); itc++)
			{
				COCP_STAGEOUT_ARTICLECODE* pData = *itc;
				CString val = m_lstArticleDetailRecords.GetItemText(row, 4).Left(1);
				int prefflag = atoi(val.GetString());
				if (pData->PREFERRED_FLAG != prefflag)
				{
					if (m_pobjDoc->UpdateOCPPreferredFlag(pData, prefflag, 2) == false)
					{
						CString msg;
						msg.Format("Error in saving ArticleCode Mapping Record %d with Preferred Flag = %d\nRecords are not saved!", row + 1, prefflag);
						MessageBox(msg, "Save Error");
						return;
					}
				}
				row++;
			} 
			MessageBox("Article Code Mappings saved successfully.", "Save Article Codes");
			m_pobjDoc->ValidateOCPArticleCodes();
			long allcnt = 0, updcnt = 0, errcnt = 0;
			m_pobjDoc->UpdateOCPDataStatus(allcnt, updcnt, errcnt);
		}
	}
	OnClickedReloadRecords();
}


void CArticleOCPTable::OnDblClickListArticleDetailRecords(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	LPNMITEMACTIVATE pitem = (LPNMITEMACTIVATE)pNMHDR;
	int row = pitem->iItem;
	int col = pitem->iSubItem;

	// scan all records to decide what to do
	if ((row >= 0) && (row < m_pobjDoc->m_stageoutNewArticleCodes.size()))
	{
		COCP_STAGEOUT_ARTICLECODE* pData = m_pobjDoc->m_stageoutNewArticleCodes.at(row);
		// allow to change preferred_flag (column index 4)
		if ((pData != NULL) && (col == 4))
		{
			CString val = m_lstArticleDetailRecords.GetItemText(row, col).Left(1);
			if ((pData->PREFERRED_FLAG == 1) && (val.Compare("1") == 0))
			{
				m_lstArticleDetailRecords.SetItemText(row, col, "0*");
				m_lstArticleDetailRecords.SetItemText(row, 6, "Updated manually (not yet saved)");
			}
			else if ((pData->PREFERRED_FLAG == 0) && (val.Compare("0") == 0))
			{
				m_lstArticleDetailRecords.SetItemText(row, col, "1*");
				m_lstArticleDetailRecords.SetItemText(row, 6, "Updated manually (not yet saved)");
			}
			else
			{
				m_lstArticleDetailRecords.SetItemText(row, col, m_pobjDoc->ConvertLong2CString(pData->PREFERRED_FLAG, true));
				m_lstArticleDetailRecords.SetItemText(row, 6, "Set back to previous value");
			}
		}
	}
}

void CArticleOCPTable::OnClickedSetRecordPreferred()
{
	int selrow = m_lstArticleDetailRecords.GetSelectionMark();
	// scan all records to decide what to do
	if ((selrow >= 0) && (selrow < m_pobjDoc->m_stageoutNewArticleCodes.size()))
	{
		// refresh the table first, that manual updates are removed
		FillRecords();
		int row = 0;
		std::vector<COCP_STAGEOUT_ARTICLECODE*>::iterator itc;
		for (itc = m_pobjDoc->m_stageoutNewArticleCodes.begin(); itc != m_pobjDoc->m_stageoutNewArticleCodes.end(); itc++)
		{
			COCP_STAGEOUT_ARTICLECODE* pData = *itc;
			// remove preferred flag if its not selected row
			if ((pData->PREFERRED_FLAG == 1) && (row != selrow))
			{
				m_lstArticleDetailRecords.SetItemText(row, 4, "0*");
				m_lstArticleDetailRecords.SetItemText(row, 6, "Updated manually (not yet saved)");
			}
			// set preferred flag if its the selected row
			if ((pData->PREFERRED_FLAG == 0) && (row == selrow))
			{
				m_lstArticleDetailRecords.SetItemText(row, 4, "1*");
				m_lstArticleDetailRecords.SetItemText(row, 6, "Updated manually (not yet saved)");
			}
			row++;
		}
		m_lstArticleDetailRecords.SetSelectionMark(selrow);
		m_lstArticleDetailRecords.SetFocus();
	}
}
