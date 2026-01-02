#include "stdafx.h"
#include "MainFrm.h"
#include "DCollectiveOrders.h"
#include <sstream>
#include <iomanip>
#include <time.h>
#include "allg.h"
#include "DCollectiveOrdersDE.h"
#include "DataTypeHelper.h"

static COLUMNS_TYPES Columns[] =
{
    0,  "",  90, LVCFMT_LEFT,
    1,  "",  55, LVCFMT_RIGHT,
    2,  "",  60, LVCFMT_CENTER,
    3,  "",  40, LVCFMT_LEFT,
    4,  "", 120, LVCFMT_LEFT,
    5,  "",  90, LVCFMT_LEFT,
    6,  "",  30, LVCFMT_RIGHT,
    7,  "",   0, LVCFMT_RIGHT,
    -1, "",   0, 0
};

IMPLEMENT_DYNAMIC(CDCollectiveOrdersDE, CDialog)

CDCollectiveOrdersDE::CDCollectiveOrdersDE(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCollectiveOrdersDE::IDD, pParent)
{
    this->fetchCount = 1;
    this->cursorEnd = true;
}

CDCollectiveOrdersDE::~CDCollectiveOrdersDE()
{
}

void CDCollectiveOrdersDE::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_COLL_ORDER, this->listCollOrders);
    DDX_Control(pDX, IDC_BTN_SELECT, this->btnSelect);
    DDX_Control(pDX, IDC_TXT_ORDERNO, this->txtOrderNo);
    DDX_Control(pDX, IDC_TXT_IDFNO, this->txtIdfNo);
    DDX_Control(pDX, IDC_TXT_ORDERSTOCLOSECOUNT, this->txtOrderCloseNumber);
    DDX_Control(pDX, IDC_BTN_CLOSEORDER, this->btnCloseOrder);
    DDX_Control(pDX, IDC_BTN_CANCEL, this->btnCancel);
    DDX_Control(pDX, IDC_BTN_GET_COUNT, this->btnSelCount);

    DDX_Control(pDX, IDC_LBL_OPENCOLLORDER, this->lblOpenCO);
    DDX_Control(pDX, IDC_LBL_SEARCH, this->lblSearch);
    DDX_Control(pDX, IDC_LBL_ORDERNO, this->lblOrderNo);
    DDX_Control(pDX, IDC_LBL_IDFNO, this->lblIDFNo);
    DDX_Control(pDX, IDC_LBL_ORDERCOUNTCLOSE, this->lblOrderCloseNumber);
    DDX_Control(pDX, IDC_LBL_COUNT_ROWS, this->lblRowCount);
    DDX_Control(pDX, IDC_LBL_COUNT_ROWS_VALUE, this->lblRowCountValue);

    CDialogMultiLang::DoDataExchange(pDX);
}

BOOL CDCollectiveOrdersDE::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    /*********************************LIST PARAMS***************************************/
    DWORD dwOldBits = this->listCollOrders.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    this->listCollOrders.SetExtendedStyle(dwOldBits);

    /*********************************LIST COLUMN TEXTS*********************************/
    //codes from resource.h
    Columns[COL_KURZ_AUFTR_NR].Columns = CResString::ex().getStrTblText(AETXT_KURZ_AUFTR_NR);
    Columns[COL_IDF_NR].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[COL_TOUR].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[COL_A_ART].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    Columns[COL_APOTHEKE].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[COL_ORT].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[COL_VZ].Columns = CResString::ex().getStrTblText(AETXT_VZ);

    /*********************************LIST COLUMN INIT*********************************/
    for (COLUMNS_TYPES* pType = Columns; pType->Index != -1; pType++)
    {
        if (this->listCollOrders.InsertColumn(pType->Index, pType->Columns.GetString(), pType->Align, pType->Width) == -1)
        {
            return FALSE;
        }
    }

    AllgSetColumnWidthUser(this->listCollOrders, "CDCOllectiveOrdersDE", KEY_PATH, 8);

    //translations
    this->btnCloseOrder.SetWindowText(CResString::ex().getStrTblText(AETXT_BUCHEN));
    this->lblOpenCO.SetWindowText(CResString::ex().getStrTblText(AETXT_OPENORDERS));
    this->lblSearch.SetWindowText(CResString::ex().getStrTblText(AETXT_SEARCH));
    this->lblIDFNo.SetWindowText(CResString::ex().getStrTblText(AETXT_IDF_NUMMER));
    this->lblOrderCloseNumber.SetWindowText(CResString::ex().getStrTblText(AETXT_CLOSEORDERNUMBER));
    this->btnSelCount.SetWindowText(CResString::ex().getStrTblText(AETXT_SEL_ROWCOUNT));
    this->lblRowCount.SetWindowText(CResString::ex().getStrTblText(AETXT_ROW_COUNT));

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDCollectiveOrdersDE::OnDestroy()
{
    AllgWriteColumnWidthUser(this->listCollOrders, "CDCOllectiveOrdersDE", KEY_PATH, 8);

    this->collOrder.CloseCursor();

    CDialogMultiLang::OnDestroy();
}

BEGIN_MESSAGE_MAP(CDCollectiveOrdersDE, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BTN_SELECT, OnBnClickedBtnSelect)
    ON_BN_CLICKED(IDC_BTN_CANCEL, OnBnClickedBtnCancel)
    ON_BN_CLICKED(IDC_BTN_CLOSEORDER, OnBnClickedBtnCloseorder)
    ON_BN_CLICKED(IDC_BTN_GET_COUNT, OnBnClickedButtonGetCount)
END_MESSAGE_MAP()

bool CDCollectiveOrdersDE::prepareSQL(CCOLLECTIVEORDERS& co)
{
    CString orderNo = "";
    CString idfNo = "";

    /******************GET USER INPUT******************************/
    this->txtOrderNo.GetWindowText(orderNo);
    this->txtIdfNo.GetWindowText(idfNo);

    /****************************USER INPUT CHECK********************************/
    std::string tmp = idfNo;
    if (tmp.empty() || !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_IDF_NOT_VALID));
        return false;
    }

    tmp = orderNo;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_ORDER_NO_NOT_VALID));
        return false;
    }

    /******************PREPARE SQL*********************************/
    co.SetFilialnr(AeGetApp()->VzNr());
    co.SetVertriebszentrumnr(AeGetApp()->VzNr());
    co.SetAnz_erfasst(this->fetchCount);
    co.SetKdauftragnr(orderNo.IsEmpty() ? 0 : atoi(orderNo));
    co.SetKundennr(idfNo.IsEmpty() ? 0 : atoi(idfNo));

    return true;
}

void CDCollectiveOrdersDE::fillTable()
{
    CStringArray recData;
    recData.SetSize(NUM_COLUMNS + 1);
    int rc = SRV_OK;

    for (int i = 0; i < ZEILEN; i++)
    {
        rc = collOrder.SelCVOrderDE();
        if (rc != SRV_OK)
        {
            //IF the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
            if (rc == SRV_SQLNOTFOUND && collOrder.CloseCursor() == SRV_OK)
            {
                collOrder.ClearStruct();
                this->cursorEnd = true;
            }

            //no more data
            break;
        }
        else
        {
            this->cursorEnd = false;
        }

        recData[COL_KURZ_AUFTR_NR] = DataTypeHelper::toString(collOrder.s.KDAUFTRAGNR).c_str();
        recData[COL_IDF_NR] = DataTypeHelper::toString(collOrder.s.IDFNR).c_str();

        AllgEntfSpaces(collOrder.s.TOURID);
        if (atol(collOrder.s.TOURID))
        {
            recData[COL_TOUR].Format("%2.2s:%2.2s/%2.2s", collOrder.s.TOURID, collOrder.s.TOURID + 2, collOrder.s.TOURID + 4);
        }
        else
        {
            recData[COL_TOUR] = "";
        }

        recData[COL_A_ART].Format("%s%s%s", collOrder.s.KDAUFTRAGART, collOrder.s.KOART, collOrder.s.BUCHART);

        AllgEntfSpaces(collOrder.s.NAMEAPO);
        recData[COL_APOTHEKE] = collOrder.s.NAMEAPO;

        recData[COL_ORT] = collOrder.s.ORT;

        recData[COL_VZ] = DataTypeHelper::toString(collOrder.s.VERTRIEBSZENTRUMNR).c_str();

        if (!CListCtrlHelper::AppendItem(listCollOrders, NUM_COLUMNS, recData))
        {
            break;
        }

        this->fetchCount++;
        collOrder.SetAnz_erfasst(this->fetchCount);
    }

    for (int i = 0; i < this->listCollOrders.GetHeaderCtrl()->GetItemCount(); ++i)
    {
        this->listCollOrders.SetColumnWidth(i, LVSCW_AUTOSIZE);
    }
}


int CDCollectiveOrdersDE::perfCountSQL()
{
    int count = 0;
    collOrderCount.SelCVOrderCount();

    count = collOrderCount.s.ANZPOS;

    collOrderCount.CloseCursor();
    collOrderCount.ClearStruct();

    return count;
}

void CDCollectiveOrdersDE::OnBnClickedButtonGetCount()
{
    if (this->prepareSQL(collOrderCount))
    {
        int count = perfCountSQL();
        std::ostringstream oss;
        oss << count;
        this->lblRowCountValue.SetWindowText(oss.str().c_str());
    }
}

void CDCollectiveOrdersDE::OnBnClickedBtnSelect()
{
    if (!this->cursorEnd)
    {
        collOrder.CloseCursor();
    }
    this->collOrder.ClearStruct();
    this->fetchCount = 1;
    this->getDataAndFillGui();

    //also show the count
    this->OnBnClickedButtonGetCount();
}

void CDCollectiveOrdersDE::getDataAndFillGui()
{
    BeginWaitCursor();

    this->listCollOrders.DeleteAllItems();

    /***************************PREPARE******************************************/
    if (!this->prepareSQL(collOrder))
    {
        return;
    }

    /*****************EXECUTE SQL AND FILL TABLE***********************************/
    this->fillTable();

    EndWaitCursor();
}


void CDCollectiveOrdersDE::OnBnClickedBtnCancel()
{
    AllgWriteColumnWidthUser(this->listCollOrders, "CDCOllectiveOrdersDE", KEY_PATH, 8);

    this->collOrder.CloseCursor();

    CDialogMultiLang::OnCancel();
}

void CDCollectiveOrdersDE::OnBnClickedBtnCloseorder()
{
    CloseOrdersList();
}

bool CDCollectiveOrdersDE::CloseOrderKSC(long orderNo)
{
    //Open order
    CAUFTRAG auftrag;
    auftrag.s.STATUS = ORD_ERFASST;
    auftrag.s.KDAUFTRAGNR = orderNo;

    BeginWaitCursor();

    auftrag.Server(AasrvOpenorder, PIPE_AE_SRV);
    if (auftrag.rc != SRV_OK)
    {
        return false;
    }

    //Reset date of delivery
    CTM time;
    time.Server(AafilGetdatetime);
    long m_lActDate = time.s.DATUM;

    if (auftrag.s.DATUMAUSLIEFERUNG > 0)
    {
        auftrag.s.DATUMAUSLIEFERUNG = m_lActDate;
        auftrag.Server(AasrvSetdelayeddate, PIPE_AE_SRV);
        if (auftrag.rc != SRV_OK)
        {
            return false;
        }
    }

    if (!strncmp(auftrag.s.KDAUFTRAGART, "CV", 2))
    {
        // Kommi und Buchungsart setzen
        strcpy(auftrag.s.KOART, "0");
        strcpy(auftrag.s.BUCHART, "0");
        auftrag.Server(AasrvChangeorder, PIPE_AE_SRV); //Auftrags- und Buchungsart setzen
        if (auftrag.rc != SRV_OK)
        {
            return false;
        }
    }

    //Close Order
    auftrag.s.STATUS = ORD_ERFASST;
    auftrag.Server(AasrvCloseorder, PIPE_AE_SRV);
    if (auftrag.rc != SRV_OK)
    {
        return false;
    }

    return true;
}

void CDCollectiveOrdersDE::CloseOrdersList()
{
    bool retValue = false;
    std::string orderNo = "";
    std::ostringstream dateStream;
    int rc = -1;
    int maxOrders = 0;
    int doneOrders = 0;

    this->fetchCount = 1;

    if (!this->cursorEnd)
    {
        collOrder.CloseCursor();
        collOrder.SetAnz_erfasst(fetchCount);
    }
    if (!this->prepareSQL(collOrder))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_SELECT_ERROR));
        return;
    }

    CString cnt_str = "";
    this->txtOrderCloseNumber.GetWindowText(cnt_str);

    CString cntOrders_str = "";
    this->lblRowCountValue.GetWindowText(cntOrders_str);

    if (cnt_str.IsEmpty() || !DataTypeHelper::isNumber(std::string(cnt_str)) || cntOrders_str.IsEmpty())
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_CLOSE_COUNT_ERROR));
        return;
    }

    int cnt = atoi(cnt_str);
    maxOrders = cnt;

    for (int i = 0; i < cnt; i++)
    {
        rc = collOrder.SelCVOrderDE();
        if (rc != SRV_OK)   //performs sql at the first time, gets its next row on the next time
        {
            //If the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
            if (rc == SRV_SQLNOTFOUND && collOrder.CloseCursor() == SRV_OK)
            {
                collOrder.ClearStruct();
                this->cursorEnd = true;
            }

            //no more data
            break;
        }
        else
        {
            this->cursorEnd = false;
            this->fetchCount++;
            collOrder.SetAnz_erfasst(this->fetchCount);
        }

        retValue = CloseOrderKSC(this->collOrder.s.KDAUFTRAGNR);
        if (retValue)
        {
            this->listCollOrders.DeleteItem(i);
            --i;
            --cnt;
            ++doneOrders;
        }
        else
        {
            break;
        }

        EndWaitCursor();
    }

    if (collOrder.CloseCursor() == 0)
    {
        collOrder.ClearStruct();
        this->cursorEnd = true;
    }

    CString msg = CResString::ex().getStrTblText(AETXT_ORDER_CLOSED_NUMBER);
    msg.Format(msg, maxOrders, doneOrders);
    AfxMessageBox(msg);
}
