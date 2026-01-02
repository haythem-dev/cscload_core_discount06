#include "StdAfx.h"
#include "CDeleteReservation.h"
#include "DKndWahl.h"
#include <pxverbund_version.h>
#include <artikel.h>

/////////////////////////////////////////////////////////////////////////////
// CDeleteReservations dialog

#define NUM_COLUMNS     12

static enum ColumnPos
{
    CharacterId = 0,
    Date = 1,
    BranchNo = 2,
    BranchName = 3,
    CustomerNo = 4,
    OrderNo = 5,
    ArticleNo = 6,
    ArticleCode = 7,
    Quantity = 8,
    ReserveType = 9,
    ReserveTypeName = 10,
    LongDate = 11
};

static COLUMNS_TYPES Columns[] =
{
    CharacterId, "", 20, LVCFMT_LEFT,
    Date, "", 70, LVCFMT_LEFT,
    BranchNo, "", 30, LVCFMT_RIGHT,
    BranchName, "", 80, LVCFMT_LEFT,
    CustomerNo,  "", 60, LVCFMT_RIGHT,
    OrderNo, "", 100, LVCFMT_RIGHT,
    ArticleNo, "", 80, LVCFMT_RIGHT,
    ArticleCode, "",26,LVCFMT_RIGHT,
    Quantity, "", 50, LVCFMT_RIGHT,
    ReserveType, "", 30, LVCFMT_RIGHT,
    ReserveTypeName, "", 350, LVCFMT_LEFT,
    LongDate,"",10,LVCFMT_LEFT,
    -1, "",  0, 0
};

IMPLEMENT_DYNAMIC(CDeleteReservation, CDialog)

CDeleteReservation::CDeleteReservation(CWnd* pParent) 
    : CDialogMultiLang(IDD_DELETERESERVATION, pParent)
    , m_CstockReservation_Search()
    , m_CstockReservation_Delete()
{
    Columns[CharacterId].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[Date].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[BranchNo].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns[BranchName].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns[CustomerNo].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[OrderNo].Columns = CResString::ex().getStrTblText(AETXT_AUFTRAGSNUMMER);
    Columns[ArticleNo].Columns = CResString::ex().getStrTblText(AETXT_ARTIKEL_NR); 
    Columns[ArticleCode].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[Quantity].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[ReserveType].Columns = CResString::ex().getStrTblText(AETXT_TYP);
    Columns[ReserveTypeName].Columns = CResString::ex().getStrTblText(AETXT_TYP_MANAGER4);    

    m_ReserveTypeNames.SetSize(17);
    m_ReserveTypeNames.SetAt(0, CResString::ex().getStrTblText(AETXT_RESERVETYPE_0));
    m_ReserveTypeNames.SetAt(1, CResString::ex().getStrTblText(AETXT_RESERVETYPE_1));
    m_ReserveTypeNames.SetAt(2, CResString::ex().getStrTblText(AETXT_RESERVETYPE_2));
    m_ReserveTypeNames.SetAt(3, CResString::ex().getStrTblText(AETXT_RESERVETYPE_3));
    m_ReserveTypeNames.SetAt(4, CResString::ex().getStrTblText(AETXT_RESERVETYPE_4));
    m_ReserveTypeNames.SetAt(5, CResString::ex().getStrTblText(AETXT_RESERVETYPE_5));
    m_ReserveTypeNames.SetAt(6, CResString::ex().getStrTblText(AETXT_RESERVETYPE_6));
    m_ReserveTypeNames.SetAt(7, CResString::ex().getStrTblText(AETXT_RESERVETYPE_7));
    m_ReserveTypeNames.SetAt(8, CResString::ex().getStrTblText(AETXT_RESERVETYPE_8));
    m_ReserveTypeNames.SetAt(9, CResString::ex().getStrTblText(AETXT_RESERVETYPE_9));
    m_ReserveTypeNames.SetAt(10, CResString::ex().getStrTblText(AETXT_RESERVETYPE_10));
    m_ReserveTypeNames.SetAt(11, CResString::ex().getStrTblText(AETXT_RESERVETYPE_11));
    m_ReserveTypeNames.SetAt(12, CResString::ex().getStrTblText(AETXT_RESERVETYPE_12));
    m_ReserveTypeNames.SetAt(13, CResString::ex().getStrTblText(AETXT_RESERVETYPE_13));
    m_ReserveTypeNames.SetAt(14, CResString::ex().getStrTblText(AETXT_RESERVETYPE_14));
    m_ReserveTypeNames.SetAt(15, CResString::ex().getStrTblText(AETXT_RESERVETYPE_15));
    m_ReserveTypeNames.SetAt(16, CResString::ex().getStrTblText(AETXT_RESERVETYPE_16));
    
    m_init = FALSE;
}

BEGIN_MESSAGE_MAP(CDeleteReservation, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDeleteReservation::OnBnClickedButtonSearch)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDeleteReservation::OnBnClickedButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_SELECT_CUSTOMER, &CDeleteReservation::OnBnClickedButtonSelectCustomer)
END_MESSAGE_MAP()

void CDeleteReservation::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATE_FROM, m_DateFrom);
    DDX_Control(pDX, IDC_DATE_TO, m_DateTo);
    DDX_Control(pDX, IDC_EDIT_ORDER_NO, m_EditOrderNo);
    DDX_Control(pDX, IDC_EDIT_IDF_NO, m_EditCustomerIDF);
    DDX_Control(pDX, IDC_EDIT_ARTICLE_NO, m_EditArticleNo);
    DDX_Control(pDX, IDC_COMBO_RESTYPE, m_ComboReserveTypeBox);
    DDX_Control(pDX, IDC_COMBO_BRANCH_NO, m_ComboBranch);
    DDX_Control(pDX, IDC_LIST_RESERVATIONS, m_ListCtlReservations);
}

BOOL CDeleteReservation::OnInitDialog() 
{
    BOOL retVal = CDialogMultiLang::OnInitDialog();
    m_ListCtlReservations.DeleteAllItems();
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtlReservations))
    {
        retVal = FALSE;
    }

    // fill combox for posible reservetypes (default all)
    m_ComboReserveTypeBox.ResetContent();
    m_ComboReserveTypeBox.AddString(CResString::ex().getStrTblText(AETXT_ALLE));
    m_ComboReserveTypeBox.AddString(CResString::ex().getStrTblText(AETXT_RESTYPE_7));
    m_ComboReserveTypeBox.AddString(CResString::ex().getStrTblText(AETXT_RESTYPE_8));
    m_ComboReserveTypeBox.AddString(CResString::ex().getStrTblText(AETXT_RESTYPE_9));
    m_ComboReserveTypeBox.AddString(CResString::ex().getStrTblText(AETXT_RESTYPE_10));
    m_ComboReserveTypeBox.AddString(CResString::ex().getStrTblText(AETXT_RESTYPE_11));
    m_ComboReserveTypeBox.AddString(CResString::ex().getStrTblText(AETXT_RESTYPE_12));
    m_ComboReserveTypeBox.SetCurSel(0);

    // fill combox with all possible branches for current region
    m_ComboBranch.AddString(CResString::ex().getStrTblText(AETXT_ALL_BRANCHES));
    CREGIONBRANCHES regioBranchSelection;
    long currentBranch = AeGetApp()->VzNr();
    regioBranchSelection.SetRegionnr(currentBranch);
    for (;;)
    {
        if (regioBranchSelection.SelList() != SRV_OK)
            break;

        CString branchText;
        ppString branchLocation;
        int branchNo = regioBranchSelection.GetRegionteilnr();
        CString branchName = regioBranchSelection.GetStandort_lang(branchLocation);
        branchText.Format("%d %s", branchNo, branchName);
        if (m_BranchNames.GetSize() < branchNo + 1)
        {
            m_BranchNames.SetSize(branchNo + 1);
        }
        m_BranchNames.SetAt(branchNo, branchName);
        
        m_ComboBranch.AddString(branchText);
    }
    // set default selection to current branch
    m_ComboBranch.SetCurSel(0); // initialized to all if no branch was found
    CString curBranchStr;
    curBranchStr.Format("%ld", currentBranch);
    for (int branchIndex = 0; branchIndex < m_ComboBranch.GetCount(); branchIndex++)
    {
        m_ComboBranch.SetCurSel(branchIndex);
        CString branchText;
        m_ComboBranch.GetWindowText(branchText);
        CString branchNo;
        branchNo = branchText.Left(curBranchStr.GetLength());
        if (branchNo.CompareNoCase(curBranchStr) == 0)
            break;
    }

    // set default Date for from and toDate 
    // with toDate = currentDate and fromDate = currentDate - 14 days
    time_t currentTime = time(0);
    CTime currentDate(currentTime);
    
    m_DateTo.SetTime(&currentDate);
    CTimeSpan dateRange(14, 0, 0, 0);
    CTime startDate = currentDate - dateRange;
    m_DateFrom.SetTime(&startDate);

    // Default button to execute on button Return
    CDialog::SetDefID(IDC_BUTTON_SEARCH);

    CenterWindow();
    return retVal;    
}

// Button next to Customer No
void CDeleteReservation::OnBnClickedButtonSelectCustomer()
{
    // Open the Customer Select Window
    CDKndWahl dlgKndWahl;
    CString strIDF;
    m_EditCustomerIDF.GetWindowText(strIDF);
    if (atol(strIDF) > 0)
    {
        dlgKndWahl.m_CKndNr = strIDF;
    }
    else
    {
        dlgKndWahl.m_CKndNr = "";
    }

    dlgKndWahl.SetEnableAeGesperrt();  
    if (dlgKndWahl.DoModal() == IDOK)
    {
        // Take current Selection from subdialog 
        m_IdfNr = dlgKndWahl.GetIdfNr();
        strIDF.Format("%ld", m_IdfNr);
        m_EditCustomerIDF.SetWindowText(strIDF);
        m_KndNr = dlgKndWahl.GetKndNr();
        m_VzNr = dlgKndWahl.GetKndVz();
        m_KzAeGesperrt = dlgKndWahl.GetKzAeGesperrt();
    }
}

void CDeleteReservation::ResetSearchCriteria()
{
    m_CstockReservation_Search.SetDatefrom(0);
    m_CstockReservation_Search.SetDateto(0);
    m_CstockReservation_Search.SetBranchno(0);
    m_CstockReservation_Search.SetCustomerno(0);
    m_CstockReservation_Search.SetKdauftragnr(0);
    m_CstockReservation_Search.SetArticleno(0);
    m_CstockReservation_Search.SetArticle_code("");
    m_CstockReservation_Search.SetReservtype(0);
    m_CstockReservation_Search.SetReservedqty(0);
}

void CDeleteReservation::ResetDeleteCriteria()
{
    m_CstockReservation_Delete.SetDatefrom(0);
    m_CstockReservation_Delete.SetDateto(0);
    m_CstockReservation_Delete.SetBranchno(0);
    m_CstockReservation_Delete.SetCustomerno(0);
    m_CstockReservation_Delete.SetKdauftragnr(0);
    m_CstockReservation_Delete.SetArticleno(0);
    m_CstockReservation_Delete.SetArticle_code("");
    m_CstockReservation_Delete.SetReservtype(0);
    m_CstockReservation_Delete.SetReservedqty(0);
    m_order.SetFilialnr(0);
    m_order.SetIdfnr(0);
    m_order.SetKdauftragart("");
    m_order.SetKdauftragnr(0);
    m_order.SetKdauftragstat("");
    m_order.SetKundennr(0);
    m_order.SetZugrund("");
    m_ibtrequest.SetArticleno(0);
    m_ibtrequest.SetBranchno(0);
    m_ibtrequest.SetCscorderno(0);
    m_ibtrequest.SetCscorderposno(0);
    m_ibtrequest.SetCustomerno(0);
    m_ibtrequest.SetIbtbranchno(0);
    m_ibtrequest.SetIbtcustomerno(0);
    m_ibtrequest.SetIbtrequestid(0);
    m_ibtrequest.SetProcessingstate(0);
    m_ibtrequest.SetQuantity(0);
    m_nachlieferpos.SetArtikel_nr(0);
    m_nachlieferpos.SetDatum(0);
    m_nachlieferpos.SetIdfnr(0);
    m_nachlieferpos.SetKdauftragnr(0);
    m_nachlieferpos.SetMenge(0);
    m_nachlieferpos.SetPosnr(0);
    m_nachlieferpos.SetPostyp(0);
    m_nachlieferpos.SetStatus(0);
    m_articlereserv.SetArticleno(0);
    m_articlereserv.SetBranchno(0);
    m_articlereserv.SetMaxqty(0);
    m_articlereserv.SetPharmacygroupid("");
    m_articlereserv.SetReservedqty(0);
    m_articlereserv.SetReservtype(0);
    m_artikellokal.SetArtikel_nr(0);
    m_artikellokal.SetBestand(0);
    m_artikellokal.SetFilialnr(0);
    m_artikellokal.SetLagerbereichnr(0);
    m_artikellokal.SetLagerfachnr("");
    m_artikellokal.SetStationnr("");  
}

// Update selected Reservations according to current
// selection
void CDeleteReservation::OnBnClickedButtonSearch()
{
    ResetSearchCriteria();

    // Get selected Date range
    CTime dateFrom;
    CTime dateTo;
    m_DateFrom.GetTime(dateFrom);
    m_DateTo.GetTime(dateTo);
    m_CstockReservation_Search.SetDatefrom(dateFrom.GetYear() * 10000 + dateFrom.GetMonth() * 100 + dateFrom.GetDay());
    m_CstockReservation_Search.SetDateto(dateTo.GetYear() * 10000 + dateTo.GetMonth() * 100 + dateTo.GetDay());

    // Get select Branch
    CString branchText;
    m_ComboBranch.GetWindowText(branchText);
    branchText = branchText.Left(2).Trim(); // first two chars only, if branchno is only on digit it will be followed by blank
    m_CstockReservation_Search.SetBranchno(static_cast<short>(atoi(branchText)));

    // Get selected Customer
    CString customerText;
    m_EditCustomerIDF.GetWindowText(customerText);
    customerText = customerText.Trim();
    if (!customerText.IsEmpty())
        m_CstockReservation_Search.SetCustomerno(atol(customerText));

    // Get selected Order No.
    CString orderNoText;
    m_EditOrderNo.GetWindowText(orderNoText);
    orderNoText = orderNoText.Trim();
    if (!orderNoText.IsEmpty())
        m_CstockReservation_Search.SetKdauftragnr(atol(orderNoText));

    // Get article no
    CString articleNoText;
    m_EditArticleNo.GetWindowText(articleNoText);
    articleNoText = articleNoText.Trim();
    if (!articleNoText.IsEmpty())
        m_CstockReservation_Search.SetArticle_code(articleNoText);

    // Get reservetyp
    int currentReserveType = m_ComboReserveTypeBox.GetCurSel();
    if (currentReserveType == 0)
        m_CstockReservation_Search.SetReservtype(static_cast<short>(currentReserveType));
    else
        m_CstockReservation_Search.SetReservtype(static_cast<short>(currentReserveType + 6));

    GetPage();
}

void CDeleteReservation::GetPage()
{
    CStringArray row;
    row.SetSize(NUM_COLUMNS);
    CLetterMan charKeyIdGenerator;

    m_ListCtlReservations.DeleteAllItems();

    BeginWaitCursor();
    int countRecords = 0; 
    for (;;)
    {
        if (m_CstockReservation_Search.SelListAll() != SRV_OK)
            break;

        countRecords++;
        ppString code = "";
        m_CstockReservation_Search.GetArticle_code(code);
        row[CharacterId] = charKeyIdGenerator.Next();
        row[Date] = DDMMYYYYStringFromDateLong(m_CstockReservation_Search.GetDatefrom());
        row[LongDate].Format("%ld", m_CstockReservation_Search.GetDatefrom());
        row[ArticleCode] = m_CstockReservation_Search.GetArticle_code(code);
        row[BranchNo].Format("%d", m_CstockReservation_Search.GetBranchno());
        row[BranchName] = m_BranchNames.GetAt(m_CstockReservation_Search.GetBranchno());
        row[CustomerNo].Format("%ld", m_CstockReservation_Search.GetCustomerno());
        row[OrderNo].Format("%ld", m_CstockReservation_Search.GetKdauftragnr());
        row[ArticleNo].Format("%ld", m_CstockReservation_Search.GetArticleno());
        row[Quantity].Format("%ld", m_CstockReservation_Search.GetReservedqty());
        row[ReserveType].Format("%d", m_CstockReservation_Search.GetReservtype());
        if (m_CstockReservation_Search.GetReservtype() < m_ReserveTypeNames.GetCount())
            row[ReserveTypeName] = m_ReserveTypeNames.GetAt(m_CstockReservation_Search.GetReservtype());

        // formated row parameters for possible logging
        CString rowParams;
        rowParams.Format("%ld: date: %ld branchno: %ld customerno: %ld orderno: %ld articleno: %ld quantity: %ld reservetype: %d",
            countRecords,
            m_CstockReservation_Search.GetDatefrom(),
            m_CstockReservation_Search.GetBranchno(),
            m_CstockReservation_Search.GetCustomerno(),
            m_CstockReservation_Search.GetKdauftragnr(),
            m_CstockReservation_Search.GetArticleno(),
            m_CstockReservation_Search.GetReservedqty(),
            m_CstockReservation_Search.GetReservtype());

        if (!CListCtrlHelper::AppendItem(m_ListCtlReservations, NUM_COLUMNS, row))
        {
            CString errorMsg;
            errorMsg.Format("add row to listbox failed: %s", rowParams);
            AeGetApp()->m_AeLogging.WriteLine(Error, "CDeleteReservation", "GetPage()", errorMsg);            
            break;
        }
    }
    m_CstockReservation_Search.CloseCursor();
    EndWaitCursor();
    if (m_ListCtlReservations.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST_RESERVATIONS));
    // No preselection of any Items from List, because explicit Item must be selected by user before deletion
}

void CDeleteReservation::OnBnClickedButtonDelete()
{
    CString msgString = "";
    CString resString = "";
    ppString bufString = "";

    boolean mayDelete = true;

    UpdateData();
    int currentSelectedPos = m_ListCtlReservations.GetNextItem(-1, LVNI_SELECTED);
    if (currentSelectedPos >= 0)
    {
        ResetDeleteCriteria();
        BeginWaitCursor();

        // get current reservation parameters for deletion
        short branchNo = (short)atoi(m_ListCtlReservations.GetItemText(currentSelectedPos, BranchNo));
        long customerNo = atol(m_ListCtlReservations.GetItemText(currentSelectedPos, CustomerNo));
        long orderNo = atol(m_ListCtlReservations.GetItemText(currentSelectedPos, OrderNo));
        long articleNo = atol(m_ListCtlReservations.GetItemText(currentSelectedPos, ArticleNo));
        long articleCode = atol(m_ListCtlReservations.GetItemText(currentSelectedPos, ArticleCode));
        short reserveType = (short) atoi(m_ListCtlReservations.GetItemText(currentSelectedPos, ReserveType));
        long reservedQty = atol(m_ListCtlReservations.GetItemText(currentSelectedPos, Quantity));
        CString strDateFrom = m_ListCtlReservations.GetItemText(currentSelectedPos, Date);
        long lDateFrom = atol(m_ListCtlReservations.GetItemText(currentSelectedPos, LongDate));
        long lTimeFrom = 0;

        resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_CSTRES_INFO),
            branchNo,
            customerNo,
            orderNo,
            articleNo,
            articleCode,
            reserveType,
            reservedQty,
            strDateFrom); // remember if no entry will be found

        // get data for selected stockreservation
        m_stockreservation.SetBranchno(branchNo);
        m_stockreservation.SetCustomerno(customerNo);
        m_stockreservation.SetKdauftragnr(orderNo);
        m_stockreservation.SetArticleno(articleNo);
        m_stockreservation.SetArticle_code(m_ListCtlReservations.GetItemText(currentSelectedPos, ArticleCode));
        m_stockreservation.SetReservtype(reserveType);
        m_stockreservation.SetDatefrom(lDateFrom);
        m_stockreservation.SetDateto(lDateFrom);
        
        // check single item to be deleted
        int countSelectedItem = 0;
        for (;;)
        {
            if (m_stockreservation.SelListAll() != SRV_OK)
                break;
            countSelectedItem++;

            branchNo = m_stockreservation.GetBranchno();
            customerNo = m_stockreservation.GetCustomerno();
            orderNo = m_stockreservation.GetKdauftragnr();
            articleNo = m_stockreservation.GetArticleno();
            ppString code = "";
            m_stockreservation.GetArticle_code(code);
            articleCode = atol(code.c_str());
            reserveType = m_stockreservation.GetReservtype();
            reservedQty = m_stockreservation.GetReservedqty();
            lDateFrom = m_stockreservation.GetDatefrom();
            lTimeFrom = m_stockreservation.GetTimefrom();

            resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_CSTRES_INFO),
                branchNo,
                customerNo,
                orderNo,
                articleNo,
                articleCode,
                reserveType,
                reservedQty,
                strDateFrom);
            msgString.Append(resString);
        }
        m_stockreservation.CloseCursor();

        if (countSelectedItem == 0)
        {
            // record not found - not deletable
            msgString.Append(resString); // reference seleced item from the list
            msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_NOTFOUND));
            mayDelete = false;
        }
        else if (countSelectedItem > 1)
        {
            // selected item not unique - not deletable
            msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_NOTUNIQUE));
            mayDelete = false;
        }

        if (mayDelete)
        {
            // get corresponding order state
            OrderState orderState = OrderDoesNotExist;

            if (orderNo > 0)
            {
                m_order.SetKdauftragnr(orderNo);
                m_order.SetFilialnr(branchNo);
                m_order.SetKundennr(customerNo);
                if (m_order.SelOrder() == 0)
                {
                    if (m_order.GetSize() > 0)
                    {
                        // current order information for message
                        m_order.GetKdauftragstat(bufString);

                        resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_ORDERINFO), m_order.GetFilialnr(), m_order.GetKdauftragnr(), m_order.GetKundennr(), bufString.c_str());
                        msgString.Append(resString);
                        orderState = OrderDoesNotExist;
                        if (m_order.GetDatum() > 0)
                        {
                            // the order is from archive - check if valid for current cstockreserved
                            // the ordernumber for each branch may be reused after a specific period of time
                            // usually the archived entry then is several month older then the current cstreservedstock entry
                            long age = abs(m_order.GetDatum() - m_stockreservation.GetDatefrom());
                            if (age < 60) // two months
                            {
                                orderState = OrderIsActive;
                            }
                            else
                            {
                                resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_ORDER_MISMATCH), m_order.GetDatum(), m_order.GetKdauftragnr());
                                msgString.Append(resString);
                            }
                        }
                        else
                        {
                            orderState = OrderIsActive;
                        }
                        if (orderState == OrderIsActive)
                        {
                            if (bufString.c_str()[AEORD_POS_FAKTUR_ENDE] == '1')
                            {
                                orderState = OrderIsCompleted;
                            }
                            else if (bufString.c_str()[AEORD_POS_STORNIERT] == '1')
                            {
                                orderState = OrderIsStorno;
                            }
                            else
                            {
                                msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_ORDERACTIVE));
                                mayDelete = false;
                            }
                        }
                    }
                    else
                    {
                        msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_ORDERMISSING));
                    }
                }
                else
                {
                    msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_ORDERMISSING));
                }
            }

            // get current stock values from localarticles
            boolean stockEntryExists = false;
            long stockQty = 0;
            long stockStorageLocation = 0;
            ppString stockStorageShelfNo = "";

            m_artikellokal.SetArtikel_nr(articleNo);
            m_artikellokal.SetFilialnr(branchNo);

            if (m_artikellokal.SelArtikelLokal() == 0)
            {
                if (m_artikellokal.GetSize() > 0)
                {
                    stockEntryExists = true;
                    stockQty = m_artikellokal.GetBestand();
                    stockStorageLocation = m_artikellokal.GetLagerbereichnr();
                    m_artikellokal.GetLagerfachnr(stockStorageShelfNo);

                    resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_ARTLOKAL_STOCK),
                        branchNo,
                        articleNo,
                        articleCode,
                        stockQty,
                        stockStorageLocation,
                        stockStorageShelfNo.c_str());
                    msgString.Append(resString);
                }
            }

            // get current stock values from reseved articles
            boolean reservedStockEntryExists = false;
            long reservedStockQty = 0;

            m_articlereserv.SetBranchno(branchNo);
            m_articlereserv.SetArticleno(articleNo);
            m_articlereserv.SetReservtype(reserveType);

            if (m_articlereserv.SelArticleReservation() == 0)
            {
                if (m_articlereserv.GetSize() > 0)
                {
                    reservedStockEntryExists = true;
                    reservedStockQty = m_articlereserv.GetReservedqty();

                    if (stockEntryExists)
                    {
                        resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_RESART_STOCK),
                            branchNo,
                            articleNo,
                            articleCode,
                            reservedStockQty,
                            stockStorageLocation,
                            stockStorageShelfNo.c_str());
                        msgString.Append(resString);
                    }
                }
            }

            // get possible subsequent delivery entries
            boolean subsequentDeliveryEntryExists = false;
            long subsequentDeliveryQty = 0;

            // check for subsquent delivery positions
            // open cursor select for more then one possible entry
            m_nachlieferpos.s.FETCH_REL = 1;
            m_nachlieferpos.SetKdauftragnr(orderNo);
            m_nachlieferpos.SetArtikel_nr(articleNo);
            m_nachlieferpos.SetIdfnr(customerNo);

            if (m_nachlieferpos.SelNachlieferPos() == 0)
            {
                for (unsigned int nNachlieferPos = 0; nNachlieferPos < m_nachlieferpos.GetSize(); nNachlieferPos++)
                {
                    subsequentDeliveryEntryExists = true;
                    subsequentDeliveryQty = m_nachlieferpos.GetMenge();

                    resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_SUBDEL_QTY),
                        orderNo,
                        articleNo,
                        articleCode,
                        subsequentDeliveryQty);
                    msgString.Append(resString);
                    m_nachlieferpos.SelNachlieferPos(); // next
                }
            }
            m_nachlieferpos.CloseCursor();

            // check for possible interbranch transfer entry
            boolean ibtRequestExists = false;
            long ibtID = 0;
            long ibtOrderingBranch = 0;
            long ibtOrderingCustomer = 0;
            long ibtQty = 0;
            IbtProcessState ibtProcessState = Processed;

            m_ibtrequest.SetIbtbranchno(branchNo);
            m_ibtrequest.SetIbtcustomerno(customerNo);
            m_ibtrequest.SetArticleno(articleNo);
            m_ibtrequest.SetDatefrom(lDateFrom);
            m_ibtrequest.SetTimefrom(lTimeFrom);

            if (m_ibtrequest.SelIbtRequest() == 0)
            {
                if (m_ibtrequest.GetSize() > 0)
                {
                    ibtRequestExists = true;
                    ibtID = m_ibtrequest.GetIbtrequestid();
                    ibtOrderingBranch = m_ibtrequest.GetBranchno();
                    ibtOrderingCustomer = m_ibtrequest.GetCustomerno();
                    ibtQty = m_ibtrequest.GetQuantity();
                    switch ((short)m_ibtrequest.GetProcessingstate())
                    {
                        case 0:
                            ibtProcessState = Open;
                            break;
                        case 1:
                            ibtProcessState = ReadyForProcessing;
                            break;
                        case 2:
                            ibtProcessState = Processed;
                            break;
                        default:
                            ibtProcessState = Processed;
                            break;
                    }

                    resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_IBTREQ_QTY),
                           orderNo,
                           articleNo,
                           articleCode,
                           ibtID,
                           ibtOrderingBranch,
                           ibtOrderingCustomer,
                           ibtQty);
                    msgString.Append(resString);
                }
            }

            if (orderState == OrderDoesNotExist ||
                orderState == OrderIsStorno ||
                orderState == OrderWasAbandoned ||
                orderState == OrderIsCompleted)
            {
                switch (reserveType)
                {
                case 7:
                    // independed of any orderstate in case 7 the order has not been processed
                    // it must be assumed that the cststockreserved entry had been abandoned
                    // and the quantity may not be returned to the current stock
                    if (subsequentDeliveryEntryExists)
                    {
                        // Inconsistent status, a new order had been created but the articles are not on stock
                        // the cstockreserved entry and subsequent delivery entries will be deleted but the current stock not adjusted
                        // the night synchronization process will adjust the artikellokal.bestand value
                        msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_SUBDEL_EXISTS));
                    }
                    msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_ARTLOK_NOT_MODIFIED));

                    break;
                case 8:
                    // similar to case 7 independent of any order state, we must assume this entry
                    // has been abandoned and cststockreserved has not been processed
                    // therefore quantity of reserved article stock has not been reduced
                    // and current quanty may not be returen to the stock
                    if (subsequentDeliveryEntryExists)
                    {
                        // Inconsistent status, a new order had been created but the articles are not on stock
                        // the cstockreserved entry and subsequent delivery entries will be deleted but the current stock not adjusted
                        // the night synchronization process will adjust the artikellokal.bestand value
                        msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_SUBDEL_EXISTS));
                    }
                    msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_RESART_NOT_MODIFIED));
                    break;
                case 9:
                    // reserved quantity will be restored to local article if ibt request has not been processed
                    // and possible subesequent delivery entry will be deleted
                    if (ibtRequestExists)
                    {
                        if (ibtProcessState == Processed)
                        {
                            // the reserved entries may be deleted, but the quanties may not be returned to stock
                            resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_IBTREQ_PROC),
                                articleCode,
                                reservedQty);
                            msgString.Append(resString);
                        }
                        else
                        {
                            // the open ibt request will be deleted
                            resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_IBTREQ_MODIFY_LOKART),
                                articleCode,
                                reservedQty,
                                stockQty,
                                reservedQty,
                                stockQty + reservedQty);
                            msgString.Append(resString);
                        }
                    }
                    break;
                case 10:
                    // reserved quantity will be restored to reserved articles if ibt request has not been processed
                    // and possible subsequent delivery entry will be deleted
                    if (ibtRequestExists)
                    {
                        if (ibtProcessState == Processed)
                        {
                            // the reserved entries may be deleted, but the quanties may not be returned to stock                                                
                            resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_IBTREQ_PROC),
                                articleCode,
                                reservedQty);
                            msgString.Append(resString);

                        }
                        else
                        {
                            // the open ibt request will be deleted
                            resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_IBTREQ_MODIFY_RESART),
                                articleCode,
                                reservedQty,
                                stockQty,
                                reservedQty,
                                stockQty + reservedQty);
                            msgString.Append(resString);
                        }
                    }
                    break;
                case 11:
                    if (mayDelete)
                    {
                        if (orderState == OrderDoesNotExist && orderNo > 0)
                        {
                            msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_ARTLOK_PROC));
                        }
                        else if (orderState == OrderIsStorno || orderNo == 0)
                        {
                            resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_ARTLOK_MODIFY),
                                articleCode,
                                reservedQty,
                                stockQty,
                                reservedQty,
                                stockQty + reservedQty);
                            msgString.Append(resString);

                        }
                        else if (orderState == OrderWasAbandoned || orderState == OrderIsCompleted)
                        {
                            msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_ARTLOK_PROC));
                        }
                    }
                    break;
                case 12:
                    // reserved quantity for open order may be processed if and only if the order does not exist
                    // or has been abandoned
                    if (mayDelete)
                    {
                        if (orderState == OrderDoesNotExist && orderNo > 0) 
                        {
                            msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_RESART_PROC));
                        }
                        else if (orderState == OrderIsStorno || orderNo == 0)
                        {
                            resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_RESART_MODIFY),
                                articleCode,
                                reservedQty,
                                stockQty,
                                reservedQty,
                                stockQty + reservedQty);
                            msgString.Append(resString);

                        }
                        else if (orderState == OrderWasAbandoned || orderState == OrderIsCompleted)
                        {
                            msgString.Append(CResString::ex().getStrTblText(IDS_TXT_DELRES_RESART_PROC));
                        }
                    }
                    break;
                default:
                    resString.Format(CResString::ex().getStrTblText(IDS_TXT_DELRES_UNKNOWN_RESTYPE),
                        reserveType);
                    msgString.Append(resString);
                    mayDelete = false;
                    break;
                }
            }

            if (!mayDelete)
            {
                MsgBoxOK(msgString, MB_ICONSTOP);
            }
            else
            {
                if (MsgBoxYesNo(msgString, MB_ICONWARNING) == IDNO)
                {
                    mayDelete = false;
                }
            }
        }

        if (mayDelete)
        {
            m_CstockReservation_Delete.s.FETCH_REL = 1;

            m_CstockReservation_Delete.SetDatefrom(lDateFrom);
            m_CstockReservation_Delete.SetBranchno(branchNo);
            m_CstockReservation_Delete.SetCustomerno(customerNo);
            m_CstockReservation_Delete.SetKdauftragnr(orderNo);
            m_CstockReservation_Delete.SetArticleno(articleNo);
            m_CstockReservation_Delete.SetArticle_code(m_ListCtlReservations.GetItemText(currentSelectedPos, ArticleCode));
            m_CstockReservation_Delete.SetReservtype(reserveType);
            m_CstockReservation_Delete.SetReservedqty(reservedQty);
            m_CstockReservation_Delete.DeleteEntry();
            OnBnClickedButtonSearch(); // Update List from Scratch
        }
        EndWaitCursor();
        return;
    }
}




