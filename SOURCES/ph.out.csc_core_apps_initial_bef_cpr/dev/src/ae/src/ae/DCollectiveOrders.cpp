// DCollectiveOrders.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MainFrm.h"
#include "DCollectiveOrders.h"
#include <sstream>
#include <iomanip>
#include <time.h>
#include "allg.h"
#include "DataTypeHelper.h"

static COLUMNS_TYPES Columns[] =
{
    0,  "", 70, LVCFMT_LEFT, //+50 because of checkbox
    1,  "", 30, LVCFMT_LEFT,
    2,  "", 20, LVCFMT_CENTER,
    3,  "", 40, LVCFMT_RIGHT,
    4,  "", 55, LVCFMT_RIGHT,
    5,  "", 60, LVCFMT_CENTER,
    6,  "", 40, LVCFMT_LEFT,
    7,  "", 35, LVCFMT_RIGHT,
    8,  "", 35, LVCFMT_RIGHT,
    9,  "", 90, LVCFMT_LEFT,
    10, "", 45, LVCFMT_LEFT,
    11, "", 35, LVCFMT_CENTER,
    12, "", 60, LVCFMT_LEFT,
    13, "", 25, LVCFMT_CENTER,
    14, "", 40, LVCFMT_RIGHT,
    15, "", 30, LVCFMT_RIGHT,
    16, "",  0, LVCFMT_LEFT,
    -1, "",  0, 0
};

// CDCollectiveOrders-Dialogfeld

IMPLEMENT_DYNAMIC(CDCollectiveOrders, CDialog)

CDCollectiveOrders::CDCollectiveOrders(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCollectiveOrders::IDD, pParent)
{
    this->fetchCount = 1;
    this->cursorEnd = true;
    this->collectiveOrder = true;
}

CDCollectiveOrders::~CDCollectiveOrders()
{
}

void CDCollectiveOrders::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_COLL_ORDER, this->listCollOrders);
    DDX_Control(pDX, IDC_BTN_SELECT, this->btnSelect);
    DDX_Control(pDX, IDC_CMB_SORT, this->cmbSort);
    DDX_Control(pDX, IDC_CMB_MASKTYPE, this->cmbMaskType);
    DDX_Control(pDX, IDC_TXT_ORDERNO, this->txtOrderNo);
    DDX_Control(pDX, IDC_TXT_IDFNO, this->txtIdfNo);
    DDX_Control(pDX, IDC_TXT_CUSTCLASS, this->txtCustClass);
    DDX_Control(pDX, IDC_TXT_CUSTGROUP, this->txtRepresentative);
    DDX_Control(pDX, IDC_TXT_CREADATE, this->txtCreaDate);
    DDX_Control(pDX, IDC_TXT_DELIVERYDATE, this->txtDeliveryDate);
    DDX_Control(pDX, IDC_TXT_REGION, this->txtRegion);
    DDX_Control(pDX, IDC_TXT_ARTICLENO, this->txtArticleNo);
    DDX_Control(pDX, IDC_TXT_WHOLESALE_BRANCH, this->txtWholesaleBranch);
    DDX_Control(pDX, IDC_CMB_VIP, this->cmbVIP);
    DDX_Control(pDX, IDC_BTN_CLOSEORDER, this->btnCloseOrder);
    DDX_Control(pDX, IDC_BTN_CANCEL, this->btnCancel);

    DDX_Control(pDX, IDC_LBL_OPENCOLLORDER, this->lblOpenCO);
    DDX_Control(pDX, IDC_LBL_SEARCH, this->lblSearch);
    DDX_Control(pDX, IDC_LBL_ORDERNO, this->lblOrderNo);
    DDX_Control(pDX, IDC_LBL_IDFNO, this->lblIDFNo);
    DDX_Control(pDX, IDC_LBL_CUSTCLASS, this->lblCustClass);
    DDX_Control(pDX, IDC_LBL_CUSTGROUP, this->lblRepresentative);
    DDX_Control(pDX, IDC_LBL_CREATIONDATE, this->lblCreationDate);
    DDX_Control(pDX, IDC_LBL_DELIVERYDATE, this->lblDeliveryDate);
    DDX_Control(pDX, IDC_LBL_REGION, this->lblRegion);
    DDX_Control(pDX, IDC_LBL_SORT, this->lblSort);
    DDX_Control(pDX, IDC_LBL_FORMAT, this->lblFormat);
    DDX_Control(pDX, IDC_LBL_VIP, this->lblVIP);
    DDX_Control(pDX, IDC_LBL_MASKTYPE, this->lblMaskType);
    DDX_Control(pDX, IDC_LBL_ARTICLENO, this->lblArticleNo);
    DDX_Control(pDX, IDC_LBL_WHOLESALE_BRANCH, this->lblWholesaleBranch);

    CDialogMultiLang::DoDataExchange(pDX);
}

BOOL CDCollectiveOrders::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    /*********************************LIST PARAMS***************************************/
    DWORD dwOldBits = this->listCollOrders.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    dwOldBits |= LVS_EX_CHECKBOXES;
    this->listCollOrders.SetExtendedStyle(dwOldBits);

    /*********************************LIST COLUMN TEXTS*********************************/
    //codes from resource.h
    Columns[COL_KENNBUCHSTABE].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_ZUGRUND].Columns = CResString::ex().getStrTblText(AETXT_ZUGRUND);
    Columns[COL_KZ_PATA].Columns = CResString::ex().getStrTblText(AETXT_KZ_PATA);
    Columns[COL_KURZ_AUFTR_NR].Columns = CResString::ex().getStrTblText(AETXT_KURZ_AUFTR_NR);
    Columns[COL_IDF_NR].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[COL_TOUR].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[COL_A_ART].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    Columns[COL_DFU].Columns = CResString::ex().getStrTblText(AETXT_DFU);
    Columns[COL_PH].Columns = CResString::ex().getStrTblText(AETXT_PH);
    Columns[COL_APOTHEKE].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[COL_ORT].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[COL_ABC].Columns = CResString::ex().getStrTblText(AETXT_ABC);
    Columns[COL_ENDE].Columns = CResString::ex().getStrTblText(AETXT_ENDE);
    Columns[COL_KZ_ANZ_ALPHA_TXT].Columns = CResString::ex().getStrTblText(AETXT_KZ_ANZ_ALPHA_TXT);
    Columns[COL_TRM].Columns = CResString::ex().getStrTblText(AETXT_TRM);
    Columns[COL_VZ].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns[COL_ZG_WERT].Columns = CResString::ex().getStrTblText(AETXT_ZUGRUND);

    /*********************************LIST COLUMN INIT*********************************/
    for ( COLUMNS_TYPES* pType = Columns; pType->Index != -1; pType++ )
    {
        if (this->listCollOrders.InsertColumn(pType->Index, pType->Columns.GetString(), pType->Align, pType->Width) == -1)
        {
            return FALSE;
        }
    }

    AllgSetColumnWidthUser(this->listCollOrders, "CDCOllectiveOrders", KEY_PATH, 17);

    /*********************************COMBO INIT***************************************/
    this->cmbSort.AddString(CResString::ex().getStrTblText(AETXT_AUFTRAGSNUMMER));
    this->cmbSort.AddString(CResString::ex().getStrTblText(AETXT_KDKLASSE));
    this->cmbSort.AddString(CResString::ex().getStrTblText(AETXT_KZ_KUNDENGRUPPE));//TODO representantive
    this->cmbSort.AddString(CResString::ex().getStrTblText(AETXT_DATUM));
    this->cmbSort.AddString(CResString::ex().getStrTblText(AETXT_IDF_NUMMER));
    this->cmbSort.AddString(CResString::ex().getStrTblText(AETXT_EINHEIT));
    this->cmbSort.AddString(CResString::ex().getStrTblText(AETXT_ORT));

    this->lblArticleNo.SetWindowText(CResString::ex().getStrTblText(AETXT_ARTIKEL_NR));
    this->lblMaskType.SetWindowText(CResString::ex().getStrTblText(AETXT_MASKTYPE));
     this->cmbMaskType.AddString(CResString::ex().getStrTblText(AETXT_MASKTYPE_CV));
    this->cmbMaskType.AddString(CResString::ex().getStrTblText(AETXT_MASKTYPE_OTHER));

    this->cmbMaskType.SelectString(0, CResString::ex().getStrTblText(AETXT_MASKTYPE_CV));
    this->cmbSort.SelectString(0,CResString::ex().getStrTblText(AETXT_AUFTRAGSNUMMER));

    this->cmbVIP.AddString("");
    this->cmbVIP.AddString("Y");
    this->cmbVIP.AddString("N");

    this->cmbVIP.SelectString(0,"");

    if (AeGetApp()->GetCountry().IsPF() == false) // non france and non prewholesale, hide wholesale branch filter
    {
        this->lblWholesaleBranch.ShowWindow(SW_HIDE);
        this->txtWholesaleBranch.ShowWindow(SW_HIDE);
    }
    CRect cbSize;       // current size of combo box
    int Height;         // new height for drop-down portion of combo box

    this->cmbSort.GetClientRect(cbSize);
    Height = this->cmbSort.GetItemHeight(-1);       // start with size of the edit-box portion
    Height += this->cmbSort.GetItemHeight(0) * 7;   // add height of lines of text

    // Note: The use of SM_CYEDGE assumes that we're using Windows '95
    // Now add on the height of the border of the edit box
    Height += GetSystemMetrics(SM_CYEDGE) * 2; // top & bottom edges

    // The height of the border of the drop-down box
    Height += GetSystemMetrics(SM_CYEDGE) * 2; // top & bottom edges

    // now set the size of the window
    this->cmbSort.SetWindowPos(NULL,            // not relative to any other windows
        0, 0,                         // TopLeft corner doesn't change
        cbSize.right, Height,         // existing width, new height
        SWP_NOMOVE | SWP_NOZORDER     // don't move box or change z-ordering.
        );

    this->cmbVIP.GetClientRect(cbSize);
    Height = this->cmbSort.GetItemHeight(-1);       // start with size of the edit-box portion
    Height += this->cmbSort.GetItemHeight(0) * 7;   // add height of lines of text

    // Note: The use of SM_CYEDGE assumes that we're using Windows '95
    // Now add on the height of the border of the edit box
    Height += GetSystemMetrics(SM_CYEDGE) * 2; // top & bottom edges

    // The height of the border of the drop-down box
    Height += GetSystemMetrics(SM_CYEDGE) * 2; // top & bottom edges

    // now set the size of the window
    this->cmbVIP.SetWindowPos(NULL,            // not relative to any other windows
        0, 0,                         // TopLeft corner doesn't change
        cbSize.right, Height,         // existing width, new height
        SWP_NOMOVE | SWP_NOZORDER     // don't move box or change z-ordering.
        );

    //translations
    this->btnCloseOrder.SetWindowText(CResString::ex().getStrTblText(AETXT_BUCHEN));
    this->lblOpenCO.SetWindowText(CResString::ex().getStrTblText(AETXT_OPENORDERS));
    this->lblSearch.SetWindowText(CResString::ex().getStrTblText(AETXT_SEARCH));
    this->lblOrderNo.SetWindowText(CResString::ex().getStrTblText(AETXT_AUFTRAGSNUMMER));
    this->lblIDFNo.SetWindowText(CResString::ex().getStrTblText(AETXT_IDF_NUMMER));
    this->lblCustClass.SetWindowText(CResString::ex().getStrTblText(AETXT_KDKLASSE));
    this->lblRepresentative.SetWindowText(CResString::ex().getStrTblText(AETXT_CUSTOMERGROUP));
    this->lblCreationDate.SetWindowText(CResString::ex().getStrTblText(AETXT_CREATIONDATE));
    this->lblDeliveryDate.SetWindowText(CResString::ex().getStrTblText(AETXT_DELIVERYDATE));
    this->lblRegion.SetWindowText(CResString::ex().getStrTblText(AETXT_ORT));
    this->lblSort.SetWindowText(CResString::ex().getStrTblText(AETXT_SORT));
    this->lblVIP.SetWindowText(CResString::ex().getStrTblText(AETXT_VIP));
    this->lblWholesaleBranch.SetWindowText(CResString::ex().getStrTblText(AETXT_WHOLESALE_BRANCH));

    //set limit for entry
    this->txtRepresentative.SetLimitText(3);
    this->txtRegion.SetLimitText(2);
    this->txtCustClass.SetLimitText(3);
    this->txtCreaDate.SetLimitText(8);
    this->txtDeliveryDate.SetLimitText(8);
    this->txtArticleNo.SetLimitText(8);//max PZN8
    this->txtWholesaleBranch.SetLimitText(3);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDCollectiveOrders::OnDestroy()
{
    AllgWriteColumnWidthUser(this->listCollOrders, "CDCOllectiveOrders", KEY_PATH, 17);

    this->collOrder.CloseCursor();

    CDialogMultiLang::OnDestroy();
}

BEGIN_MESSAGE_MAP(CDCollectiveOrders, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BTN_SELECT, OnBnClickedBtnSelect)
    ON_BN_CLICKED(IDC_BTN_CANCEL, OnBnClickedBtnCancel)
    ON_BN_CLICKED(IDC_BTN_CLOSEORDER, OnBnClickedBtnCloseorder)
    ON_CBN_SELCHANGE(IDC_CMB_MASKTYPE, OnMaskTypeChoose)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_COLL_ORDER, OnLvnKeydownListCollOrder)
    ON_BN_CLICKED(IDC_BUTTON_MARK_ALL, OnBnClickedButtonMarkAll)
END_MESSAGE_MAP()

bool CDCollectiveOrders::prepareSQL()
{
    CString orderNo = "";
    CString idfNo = "";
    CString custClass = "";
    CString representative = "";
    CString creaDate = "";
    CString deliveryDate = "";
    CString region = "";
    CString vip = "";
    CString articleNo = "";
    CString wholesaleBranch = "";
    std::string tmp = "";

    /******************GET USER INPUT******************************/
    this->txtOrderNo.GetWindowText(orderNo);
    this->txtIdfNo.GetWindowText(idfNo);
    this->txtCustClass.GetWindowText(custClass);
    this->txtRepresentative.GetWindowText(representative);
    this->txtCreaDate.GetWindowText(creaDate);
    this->txtDeliveryDate.GetWindowText(deliveryDate);
    this->txtRegion.GetWindowText(region);
    this->cmbVIP.GetWindowText(vip);
    this->txtArticleNo.GetWindowText(articleNo);
    this->txtWholesaleBranch.GetWindowText(wholesaleBranch);

    /****************************USER INPUT CHECK********************************/
    if (!DataTypeHelper::CheckDate(creaDate))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_DATE_NOT_VALID));
        return false;
    }

    if (!DataTypeHelper::CheckDate(deliveryDate))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_DATE_NOT_VALID));
        return false;
    }

    tmp = idfNo;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
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

    tmp = articleNo;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_ARTICLE_NO_NOT_VALID));
        return false;
    }

    // can also be filled with alphanumeric
    //tmp = wholesaleBranch;
    //if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    //{
    //    AfxMessageBox(CResString::ex().getStrTblText(AETXT_WHOLESALE_BRANCH_NO_NOT_VALID));
    //    return false;
    //}

    /******************PREPARE SQL*********************************/
    collOrder.SetFilialnr(AeGetApp()->VzNr());
    collOrder.SetVertriebszentrumnr(AeGetApp()->VzNr());

    collOrder.SetKdauftragnr(orderNo.IsEmpty() ? 0 : atoi(orderNo));

    collOrder.SetKundennr(idfNo.IsEmpty() ? 0 : atoi(idfNo));

    if (!custClass.IsEmpty())
    {
        collOrder.SetKzkdklasse(custClass + "%");
    }

    if (!representative.IsEmpty())
    {
        collOrder.SetPersonalnrvertr(atoi(representative));
    }

    collOrder.SetErstellDatum(creaDate.IsEmpty() ? 0 : atoi(creaDate));
    collOrder.SetLieferDatum(deliveryDate.IsEmpty() ? 0 : atoi(deliveryDate));

    if (!region.IsEmpty())
    {
        collOrder.SetPostleitzahl(region);
    }

    if (!vip.IsEmpty())
    {
        collOrder.SetSkdvipkunde(vip[0]);
    }

    collOrder.SetArtikel_nr(articleNo.IsEmpty() ? 0 : atoi(articleNo));

    collOrder.SetKdauftragart(this->collectiveOrder ? "CV" : "ALL");

    if (!wholesaleBranch.IsEmpty())
    {
        collOrder.SetSkdTournee(wholesaleBranch);
    }

    //this is used in the esql to determine the order by
    collOrder.SetAnzpos(this->cmbSort.GetCurSel());

    collOrder.SetAnz_erfasst(this->fetchCount);

    return true;
}

void CDCollectiveOrders::fillTable()
{
    CStringArray recData;
    recData.SetSize(NUM_COLUMNS + 1);
    int rc = SRV_OK;

    CLetterMan kb;
    for (int i = 0; i < ZEILEN; i++)
    {
        rc = collOrder.SelCVOrder();
        if (rc != SRV_OK)
        {
            //IF the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
            if ((rc == SRV_SQLNOTFOUND) && (collOrder.CloseCursor() == SRV_OK))
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

        recData[COL_KENNBUCHSTABE] = kb.Next();

        recData[COL_ZUGRUND].Empty();
        if (collOrder.s.ZUGRUND[ZU_KREDITLIMIT] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_SHORT_KREDITLIMIT);
        }
        else if (collOrder.s.ZUGRUND[ZU_INTERNET] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_SHORT_INTERNET);
        }
        else if (collOrder.s.ZUGRUND[ZU_BACKROUTING] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_SHORT_BACKROUTING);
        }
        else if (collOrder.s.ZUGRUND[ZU_DD_OHNE] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_SHORT_DD);
        }
        else if (collOrder.s.ZUGRUND[ZU_BTM] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_ZU_BTM);
        }
        else if (collOrder.s.ZUGRUND[ZU_OV] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_ZU_OV);
        }
        else if (collOrder.s.ZUGRUND[ZU_WAHL_STELLER] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_ZU_WS);
        }
        else if (collOrder.s.ZUGRUND[ZU_NO_QTY_NR] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_NO_RAB_QTY);
        }
        else if (collOrder.s.ZUGRUND[ZU_NO_CICS] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_SHORT_NO_CICS);
        }
        if (collOrder.s.ZUGRUND[ZU_INVENTUR_HERST] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_ZU_IV);
        }
        if (collOrder.s.ZUGRUND[ZU_INVENTUR_KONSIG] == '1')
        {
            recData[COL_ZUGRUND] = CResString::ex().getStrTblText(AETXT_ZU_IV);
        }
        recData[COL_ZG_WERT] = collOrder.s.ZUGRUND ;

        recData[COL_KZ_PATA] = collOrder.s.KDAUFTRAGSTAT[AEORD_POS_PARA_AUFTRAG] == '1' ? "P" : "";
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

        recData[COL_DFU] = DataTypeHelper::toString(collOrder.s.ANZPOSDAFUE).c_str();
        recData[COL_PH] = DataTypeHelper::toString(collOrder.s.ANZPOS - collOrder.s.ANZPOSDAFUE).c_str();

        AllgEntfSpaces(collOrder.s.NAMEAPO);
        recData[COL_APOTHEKE] = collOrder.s.NAMEAPO;

        recData[COL_ORT] = collOrder.s.POSTLEITZAHL;

        AllgEntfSpaces(collOrder.s.KZKDKLASSE);
        recData[COL_ABC] = collOrder.s.KZKDKLASSE;

        recData[COL_ENDE] = HHmmStringFromTimeLong(collOrder.s.ZEITENDEPM);

        recData[COL_KZ_ANZ_ALPHA_TXT] = DataTypeHelper::toString(collOrder.s.ANZALPHATEXT).c_str();

        AllgEntfSpaces(collOrder.s.GERAETNAME);
        recData[COL_TRM] = collOrder.s.GERAETNAME;

        recData[COL_VZ] = DataTypeHelper::toString(collOrder.s.VERTRIEBSZENTRUMNR).c_str();

        if (!CListCtrlHelper::AppendItem(listCollOrders, NUM_COLUMNS, recData))
        {
            break;
        }

        ++fetchCount;
        collOrder.SetAnz_erfasst(fetchCount);
    }
}

void CDCollectiveOrders::OnMaskTypeChoose()
{
    CString selection = "";
    this->cmbMaskType.GetLBText(this->cmbMaskType.GetCurSel(), selection);
    this->collectiveOrder = (selection == CResString::ex().getStrTblText(AETXT_MASKTYPE_CV)) ? true : false;
}

void CDCollectiveOrders::OnBnClickedBtnSelect()
{
    if (!this->cursorEnd)
    {
        collOrder.CloseCursor();
    }
    this->collOrder.ClearStruct();
    this->fetchCount = 1;
    this->getDataAndFillGui();
}

void CDCollectiveOrders::getDataAndFillGui()
{
    BeginWaitCursor();

    this->listCollOrders.DeleteAllItems();

    /***************************PREPARE******************************************/
    if (!this->prepareSQL())
    {
        return;
    }

    /*****************EXECUTE SQL AND FILL TABLE***********************************/
    this->fillTable();

    EndWaitCursor();
}

void CDCollectiveOrders::OnBnClickedBtnCancel()
{
    AllgWriteColumnWidthUser(this->listCollOrders, "CDCOllectiveOrders", KEY_PATH, 17);

    this->collOrder.CloseCursor();

    CDialogMultiLang::OnCancel();
}

void CDCollectiveOrders::OnBnClickedBtnCloseorder()
{
    std::string orderNo = "";
    std::ostringstream dateStream;
    CString cZG;
    long orderNoConv;

    int cnt = this->listCollOrders.GetItemCount();
    for (int i = 0; i < cnt; i++)
    {
        if (this->listCollOrders.GetCheck(i))//if entry ist checked
        {
            orderNo = this->listCollOrders.GetItemText(i, COL_KURZ_AUFTR_NR);
            if (orderNo.empty())
            {
                continue;
            }

            //Open order
            CAUFTRAG auftrag;
            auftrag.s.STATUS = ORD_ERFASST;
            DataTypeHelper::tryParse(orderNo, orderNoConv);
            auftrag.s.KDAUFTRAGNR = orderNoConv;

            BeginWaitCursor();

            auftrag.Server(AasrvOpenorder, PIPE_AE_SRV);
            if (auftrag.rc != SRV_OK)
            {
                break;
            }

            //Reset date of delivery
            CTM time;
            time.Server(AafilGetdatetime);
            long m_lActDate = time.s.DATUM;

            auftrag.s.DATUMAUSLIEFERUNG = m_lActDate;
            auftrag.Server(AasrvSetdelayeddate, PIPE_AE_SRV);
            if (auftrag.rc != SRV_OK)
            {
                break;
            }

            if (!strncmp(auftrag.s.KDAUFTRAGART, "CV", 2))
            {
                // Kommi und Buchungsart setzen
                strcpy(auftrag.s.KOART, "0");
                strcpy(auftrag.s.BUCHART, "0");
                auftrag.Server(AasrvChangeorder, PIPE_AE_SRV); //Auftrags- und Buchungsart setzen
                if (auftrag.rc != SRV_OK)
                {
                    break;
                }
            }

            //Close Order
            auftrag.s.STATUS = ORD_ERFASST;
            cZG = this->listCollOrders.GetItemText(i, COL_ZG_WERT);
            if (cZG.GetAt(ZU_INVENTUR_HERST) == '1')
            {
                AeGetApp()->ClearZUGrund(ZU_INVENTUR_HERST);
                cZG.SetAt(ZU_INVENTUR_HERST, '0');
            }
            if (cZG.GetAt(ZU_INVENTUR_KONSIG) == '1')
            {
                AeGetApp()->ClearZUGrund(ZU_INVENTUR_KONSIG);
                cZG.SetAt(ZU_INVENTUR_KONSIG, '0');
            }
            auftrag.Server(AasrvCloseorder, PIPE_AE_SRV);
            if (auftrag.rc != SRV_OK)
            {
                break;
            }
            else
            {
                this->listCollOrders.DeleteItem(i);
                --i;
                --cnt;
            }

            EndWaitCursor();
        }
    }
}

void CDCollectiveOrders::OnLvnKeydownListCollOrder(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

    if (pLVKeyDow->wVKey == VK_NEXT && !this->cursorEnd)
    {
        //this->fetchCount += this->ZEILEN; -> not needed since its just "next"
        this->getDataAndFillGui();
        *pResult = 1L;
    }
    else if (pLVKeyDow->wVKey == VK_PRIOR)
    {
        int rest = this->fetchCount % this->ZEILEN - 1; //since the +1 for the count, is here -1

        //Depending on the Rest determine if we can make a page up or not
        if ((rest == 0 && this->fetchCount > this->ZEILEN * 2) || (rest != 0 && this->fetchCount > this->ZEILEN))
        {
            if (rest == 0)
            {
                rest = this->ZEILEN;
            }
            this->fetchCount -= this->ZEILEN + rest;

            this->getDataAndFillGui();
            *pResult = 1L;
        }
    }
    else
    {
        *pResult = 0L;
    }
}

void CDCollectiveOrders::OnBnClickedButtonMarkAll()
{
    int cnt = this->listCollOrders.GetItemCount();
    for (int i = 0; i < cnt; i++)
    {
        this->listCollOrders.SetCheck(i);
    }
}
