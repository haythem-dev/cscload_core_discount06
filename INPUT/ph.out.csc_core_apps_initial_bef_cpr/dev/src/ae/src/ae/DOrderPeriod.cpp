#include "stdafx.h"
#include "MainFrm.h"
#include <sstream>
#include <iomanip>
#include <time.h>
#include "allg.h"
#include <param.h>
#include "DOrderPeriod.h"
#include "DOrderPeriodChg.h"
#include "DataTypeHelper.h"
#include "OrderPeriodData.h"
#include "DataQueryHelper.h"
#include <vector>
#include <ctime>


static COLUMNS_TYPES Columns[] =
{
    0,  "", 90, LVCFMT_LEFT,
    1,  "", 60, LVCFMT_LEFT,
    2,  "", 60, LVCFMT_LEFT,
    3,  "", 60, LVCFMT_LEFT,
    4,  "", 90, LVCFMT_LEFT,
    5,  "", 50, LVCFMT_RIGHT,
    6,  "", 50, LVCFMT_RIGHT,
    7,  "", 50, LVCFMT_RIGHT,
    8,  "",  0, LVCFMT_RIGHT,
    9,  "",  0, LVCFMT_RIGHT,
    10, "",  0, LVCFMT_RIGHT,
    11, "",  0, LVCFMT_RIGHT,
    -1, "",  0, 0
};

IMPLEMENT_DYNAMIC(CDOrderPeriod, CDialog)

CDOrderPeriod::CDOrderPeriod(short branchNo, long idfNo, CWnd* pParent) : CDialogMultiLang(CDOrderPeriod::IDD, pParent)
{
    this->fetchCount = 1;
    this->cursorEnd = true;

    //handle like order creation(f8) = show no branch + idf entry disabled
    this->_branchNo = branchNo;
    this->_idfNo = idfNo;
    this->SORT_PARAMS_STRING[0] = "";
    this->SORT_PARAMS_STRING[1] = CResString::ex().getStrTblText(AETXT_TOUR);
    this->SORT_PARAMS_STRING[2] = CResString::ex().getStrTblText(AETXT_WEEKDAY);
    this->SORT_PARAMS_STRING[3] = CResString::ex().getStrTblText(AETXT_TIME_FROM);
}

CDOrderPeriod::~CDOrderPeriod()
{
}

/*******************************************************/
/*                GUI FUNCTIONS                        */
/*******************************************************/
void CDOrderPeriod::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_ORDER_PERIOD, this->lstOrderPeriod );

    DDX_Control(pDX, IDC_TXT_IDFNO, this->txtIdfNo );

    DDX_Control(pDX, IDC_BTN_SELECT_DATA, this->btnSelect );
    DDX_Control(pDX, IDC_BTN_CANCEL, this->btnCancel );
    DDX_Control(pDX, IDC_BTN_CHANGE_DATA, this->btnChangeData );
    DDX_Control(pDX, IDC_BTN_INSERT_DATA, this->btnInsertData );
    DDX_Control(pDX, IDC_BTN_RESET_SORT, this->btnResetSort );
    DDX_Control(pDX, IDC_BTN_DELETE_DATA, this->btnDeleteData );

    DDX_Control(pDX, IDC_CMB_TOURID, this->cmbTourID );
    DDX_Control(pDX, IDC_CMB_SORT_PARA_1, this->cmbSortPara1 );
    DDX_Control(pDX, IDC_CMB_SORT_PARA_2, this->cmbSortPara2 );
    DDX_Control(pDX, IDC_CMB_SORT_PARA_3, this->cmbSortPara3 );
    DDX_Control(pDX, IDC_CMB_DAY_OF_WEEK, this->cmbDayOfWeek );

    DDX_Control(pDX, IDC_LBL_IDFNO, this->lblIdfNo );
    DDX_Control(pDX, IDC_LBL_TOURID, this->lblTourID );
    DDX_Control(pDX, IDC_LBL_SORT_PARA_1, this->lblSortPara1 );
    DDX_Control(pDX, IDC_LBL_SORT_PARA_2, this->lblSortPara2 );
    DDX_Control(pDX, IDC_LBL_SORT_PARA_3, this->lblSortPara3 );
    DDX_Control(pDX, IDC_LBL_DAY_OF_WEEK, this->lblDayOfWeek );
    DDX_Control(pDX, IDC_LBL_HINT_USER_CHANGE, this->lblHintUserChange);

    DDX_Control(pDX, IDC_GBC_SEARCH, this->gbcSearch );
    DDX_Control(pDX, IDC_GBC_SORT, this->gbcSort );

    CDialogMultiLang::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDOrderPeriod, CDialogMultiLang)
    ON_EN_KILLFOCUS(IDC_TXT_IDFNO, OnIdfInputFinished)
    ON_CBN_SELENDOK(IDC_CMB_SORT_PARA_1,OnCmbSortPara1Choosen)
    ON_CBN_SELENDOK(IDC_CMB_SORT_PARA_2,OnCmbSortPara2Choosen)
    ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnClickedCancel)
    ON_BN_CLICKED(IDC_BTN_INSERT_DATA, OnBtnClickedInsert)
    ON_BN_CLICKED(IDC_BTN_CHANGE_DATA, OnBtnClickedUpdate)
    ON_BN_CLICKED(IDC_BTN_DELETE_DATA, OnBtnClickedDelete)
    ON_BN_CLICKED(IDC_BTN_RESET, OnBtnClickedResetComboBoxes)
    ON_BN_CLICKED(IDC_BTN_SELECT_DATA, OnBtnClickedSelect)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_ORDER_PERIOD, OnLvnKeydownListOrderPeriod)
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnListNMCustomdraw)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_ORDER_PERIOD, OnListNMCustomdraw)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_ORDER_PERIOD, OnDblClickList)
END_MESSAGE_MAP()

BOOL CDOrderPeriod::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    /*********************************LIST PARAMS***************************************/
    DWORD dwOldBits = this->lstOrderPeriod.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    this->lstOrderPeriod.SetExtendedStyle(dwOldBits);

    /*********************************LIST COLUMN TEXTS*********************************/
    //codes from resource.h
    Columns[COL_DAY_OF_WEEK].Columns = CResString::ex().getStrTblText(AETXT_WEEKDAY);
    Columns[COL_TIME_FROM].Columns = CResString::ex().getStrTblText(AETXT_TIME_FROM);
    Columns[COL_TIME_TILL].Columns = CResString::ex().getStrTblText(AETXT_TIME_TILL);
    Columns[COL_TIME_MAIN].Columns = CResString::ex().getStrTblText(AETXT_MAIN_TIME);
    Columns[COL_TOURID].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[COL_CLOSE_TIME_1].Columns = CResString::ex().getStrTblText(AETXT_CONSTIME)+" 1";
    Columns[COL_CLOSE_TIME_2].Columns = CResString::ex().getStrTblText(AETXT_CONSTIME)+" 2";
    Columns[COL_CLOSE_TIME_3].Columns = CResString::ex().getStrTblText(AETXT_CONSTIME)+" 3";

    int i=0;
    /*********************************LIST COLUMN INIT*********************************/
    for ( COLUMNS_TYPES* pType = Columns; pType->Index != -1; pType++ )
    {
        if (this->lstOrderPeriod.InsertColumn(pType->Index, pType->Columns.GetString(), pType->Align, pType->Width, i) == -1)
        {
            return FALSE;
        }
        i++;
    }

    AllgSetColumnWidthUser(this->lstOrderPeriod, "CDOrderPeriod", KEY_PATH, 9);

    //translations
    this->btnChangeData.SetWindowText(CResString::ex().getStrTblText(AETXT_OP_UPDATE));
    this->btnInsertData.SetWindowText(CResString::ex().getStrTblText(AETXT_OP_INSERT));
    this->btnSelect.SetWindowText(CResString::ex().getStrTblText(AETXT_SEARCH));
    this->btnCancel.SetWindowText(CResString::ex().getStrTblText(AETXT_CANCEL));
    this->btnDeleteData.SetWindowText(CResString::ex().getStrTblText(AETXT_OP_DELETE));
    this->btnResetSort.SetWindowText(CResString::ex().getStrTblText(AETXT_RESET));

    this->gbcSearch.SetWindowText(CResString::ex().getStrTblText(AETXT_SEARCH));
    this->gbcSort.SetWindowText(CResString::ex().getStrTblText(AETXT_SORT));
    this->lblIdfNo.SetWindowText(CResString::ex().getStrTblText(AETXT_IDF_NUMMER));
    this->lblTourID.SetWindowText(CResString::ex().getStrTblText(AETXT_TOURID));
    this->lblSortPara1.SetWindowText(CResString::ex().getStrTblText(AETXT_SORT_PARAM)+" 1");
    this->lblSortPara2.SetWindowText(CResString::ex().getStrTblText(AETXT_SORT_PARAM)+" 2");
    this->lblSortPara3.SetWindowText(CResString::ex().getStrTblText(AETXT_SORT_PARAM)+" 3");
    this->lblDayOfWeek.SetWindowText(CResString::ex().getStrTblText(AETXT_WEEKDAY));
    this->lblHintUserChange.SetWindowText(CResString::ex().getStrTblText(AETXT_OP_HINT_USER_CHANGE));

    this->InitComboBoxes();

    this->txtIdfNo.SetWindowText(DataTypeHelper::toString(this->_idfNo).c_str());
    this->OnIdfInputFinished();

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

bool CDOrderPeriod::InitComboBoxes()
{
    this->cmbDayOfWeek.ResetContent();

    this->cmbDayOfWeek.EnableWindow(TRUE);
    this->cmbTourID.EnableWindow(TRUE);

    //Init day of week combo box.
    this->cmbDayOfWeek.AddString( "" );
    this->cmbDayOfWeek.AddString( CResString::ex().getStrTblText(IDS_SUNDAY) );
    this->cmbDayOfWeek.AddString( CResString::ex().getStrTblText(IDS_MONDAY) );
    this->cmbDayOfWeek.AddString( CResString::ex().getStrTblText(IDS_TUESDAY) );
    this->cmbDayOfWeek.AddString( CResString::ex().getStrTblText(IDS_WEDNESDAY) );
    this->cmbDayOfWeek.AddString( CResString::ex().getStrTblText(IDS_THURSDAY) );
    this->cmbDayOfWeek.AddString( CResString::ex().getStrTblText(IDS_FRIDAY) );
    this->cmbDayOfWeek.AddString( CResString::ex().getStrTblText(IDS_SATURDAY) );

    this->cmbDayOfWeek.SetCurSel(0);
    this->cmbTourID.SetCurSel(0);

    this->ResetSortComboBoxes();

    return true;
}

void CDOrderPeriod::OnDestroy()
{
    AllgWriteColumnWidthUser(this->lstOrderPeriod, "CDOrderPeriod", KEY_PATH, 9);

    this->orderPeriod.CloseCursor();

    CDialogMultiLang::OnDestroy();
}

/*******************************************************/
/*                LOGIC FUNCTIONS                      */
/*******************************************************/
void CDOrderPeriod::GetDataAndFillGui()
{
    BeginWaitCursor();

    this->lstOrderPeriod.DeleteAllItems();

    /***************************PREPARE***************************************/
    if (!this->prepareSQL())
    {
        return;
    }

    /*****************EXECUTE SQL AND FILL TABLE******************************/
    this->fillTable();

    EndWaitCursor();
}

bool CDOrderPeriod::prepareSQL()
{
    CString idfNo = "";
    CString txtTour = "";
    CString txtSort1 = "";
    CString txtSort2 = "";
    CString txtSort3 = "";
    std::string tmp = "";
    int weekDay = 0;

    /******************GET USER INPUT******************************/
    this->txtIdfNo.GetWindowText(idfNo);
    this->cmbTourID.GetWindowText(txtTour);
    weekDay = this->cmbDayOfWeek.GetCurSel()-1;
    this->cmbSortPara1.GetWindowText(txtSort1);
    this->cmbSortPara2.GetWindowText(txtSort2);
    this->cmbSortPara3.GetWindowText(txtSort3);

    /****************************USER INPUT CHECK********************************/
    tmp = idfNo;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_IDF_NOT_VALID));
        return false;
    }

    /******************PREPARE SQL*********************************/
    orderPeriod.SetBranchno(this->_branchNo);
    orderPeriod.SetId(this->_branchNo);

    orderPeriod.SetTourid(txtTour);
    orderPeriod.SetCustomerno(atoi(idfNo));
    orderPeriod.SetWeekday(static_cast<short>(weekDay));

    //this is used in the esql to determine the order by
    CString curSelText;

    this->cmbSortPara1.GetWindowText(curSelText);
    int param1 = this->getSearchParamNumber(curSelText);

    curSelText="";
    this->cmbSortPara2.GetWindowText(curSelText);
    int param2 = this->getSearchParamNumber(curSelText);

    curSelText="";
    this->cmbSortPara3.GetWindowText(curSelText);
    int param3 = this->getSearchParamNumber(curSelText);

    orderPeriod.SetAnz_faktur(param1*100+param2*10+param3);

    orderPeriod.SetAnz_erfasst(this->fetchCount);

    return true;
}

int CDOrderPeriod::getSearchParamNumber(CString selectedValue)
{
    if (selectedValue == this->SORT_PARAMS_STRING[Tourid])
    {
        return Tourid;
    }
    else if (selectedValue == this->SORT_PARAMS_STRING[Day])
    {
        return Day;
    }
    else if (selectedValue == this->SORT_PARAMS_STRING[FromTime])
    {
        return FromTime;
    }
    else
    {
        return 0;
    }
}

void CDOrderPeriod::fillTable()
{
    CStringArray recData;
    recData.SetSize(NUM_COLUMNS + 1);
    int index = 0;
    int rc = SRV_OK;
    int fetchCountTime = 0;
    CORDERPERIOD orderPeriodTime;
    bool foundConsTime = false;

    for (int i = 0; i < ZEILEN; i++)
    {
        rc = orderPeriod.SelTourData();
        if (rc != SRV_OK)
        {
            //IF the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
            if (rc == SRV_SQLNOTFOUND && orderPeriod.CloseCursor() == SRV_OK)
            {
                orderPeriod.ClearStruct();
                this->cursorEnd = true;
            }

            //no more data
            break;
        }
        else
        {
            this->cursorEnd = false;
        }

        recData[COL_DAY_OF_WEEK] = this->GetDayOfWeekForSelection(orderPeriod.s.WEEKDAY).c_str();
        recData[COL_HIDDEN_WEEKDAY_INT] = DataTypeHelper::toString(orderPeriod.s.WEEKDAY).c_str();

        std::string test = DataTypeHelper::padString(DataTypeHelper::toString(orderPeriod.s.FROMTIME).c_str(), 4, '0');
        test.insert(2, ":");
        recData[COL_TIME_FROM] = test.c_str();

        test = DataTypeHelper::padString(DataTypeHelper::toString(orderPeriod.s.TOTIME).c_str(), 4, '0');
        test.insert(2, ":");
        recData[COL_TIME_TILL] = test.c_str();

        test = DataTypeHelper::padString(DataTypeHelper::toString(orderPeriod.s.MAINTIME).c_str(), 4, '0');
        test.insert(2, ":");
        recData[COL_TIME_MAIN] = test.c_str();

        recData[COL_HIDDEN_ID] = DataTypeHelper::toString(orderPeriod.s.ID).c_str();
        recData[COL_HIDDEN_ID_TIME] = DataTypeHelper::toString(orderPeriod.s.ORDER_PERIOD_ID).c_str();
        AllgEntfSpaces(orderPeriod.s.TOURID);
        if (atol(orderPeriod.s.TOURID))
        {
            recData[COL_TOURID].Format("%2.2s:%2.2s/%2.2s", orderPeriod.s.TOURID, orderPeriod.s.TOURID + 2, orderPeriod.s.TOURID + 4);
        }
        else
        {
            recData[COL_TOURID] = "";
        }

        recData[COL_HIDDEN_IDF] = DataTypeHelper::toString(orderPeriod.s.CUSTOMERNO).c_str();

        //get const times for this data
        fetchCountTime = 1;
        recData[COL_CLOSE_TIME_1] = "";
        recData[COL_CLOSE_TIME_2] = "";
        recData[COL_CLOSE_TIME_3] = "";

        for (int j = 0; j < 3;j++)
        {
            orderPeriodTime.SetCustomerno(orderPeriod.GetCustomerno());
            orderPeriodTime.SetTourid(orderPeriod.s.TOURID);
            orderPeriodTime.SetBranchno(orderPeriod.GetBranchno());
            orderPeriodTime.SetAnz_erfasst(fetchCountTime);
            orderPeriodTime.SetConstime(0);
            rc = orderPeriodTime.SelConsTime();
            if (rc != SRV_OK)
            {
                //IF the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
                if (rc == SRV_SQLNOTFOUND && orderPeriodTime.CloseCursor() == SRV_OK)
                {
                    orderPeriodTime.ClearStruct();
                }

                //no more data
                break;
            }

            if (orderPeriodTime.s.CONSTIME == 0)
            {
                continue;
            }
            foundConsTime = true;

            switch (fetchCountTime)
            {
            case 1:
                test = DataTypeHelper::padString(DataTypeHelper::toString(orderPeriodTime.s.CONSTIME).c_str(), 4, '0');
                test.insert(2, ":");
                recData[COL_CLOSE_TIME_1] = test.c_str();
                break;
            case 2:
                test = DataTypeHelper::padString(DataTypeHelper::toString(orderPeriodTime.s.CONSTIME).c_str(), 4, '0');
                test.insert(2, ":");
                recData[COL_CLOSE_TIME_2] = test.c_str();
                break;
            case 3:
                test = DataTypeHelper::padString(DataTypeHelper::toString(orderPeriodTime.s.CONSTIME).c_str(), 4, '0');
                test.insert(2, ":");
                recData[COL_CLOSE_TIME_3] = test.c_str();
                break;
            default:
                break;
            }
            ++fetchCountTime;
        }

        if (!foundConsTime)
        {
            CPARAUFBEARB paraufbearb;
            paraufbearb.s.FILIALNR = AeGetApp()->VzNr();
            paraufbearb.Server(AafilSelaufbearb);
            int wareHouseProcessingTime = paraufbearb.s.DURCHLAUFNORMAL;

            int tourid = atol(orderPeriod.s.TOURID);
            tourid = tourid / 100;    //Bahnhof entfernen
            tourid = tourid * 100;
            long lStdConsTime = 0;
            if (tourid < 240000)
            {
                AllgAddTimeSpan(tourid, wareHouseProcessingTime * -60, &lStdConsTime);
                lStdConsTime = lStdConsTime / 100;
                test = DataTypeHelper::padString(DataTypeHelper::toString(lStdConsTime).c_str(), 4, '0');
                test.insert(2, ":");
                recData[COL_CLOSE_TIME_1] = test.c_str();
            }
        }

        orderPeriodTime.CloseCursor();
        orderPeriodTime.ClearStruct();

        if ((index = this->lstOrderPeriod.InsertItem(i, recData[COL_DAY_OF_WEEK])) == -1)
        {
            break;
        }
        for (int iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
        {
            if (!this->lstOrderPeriod.SetItemText(index, iSubItem, recData[iSubItem]))
            {
                break;
            }
        }

        this->fetchCount++;
        orderPeriod.SetAnz_erfasst(this->fetchCount);
    }
}

std::string CDOrderPeriod::GetDayOfWeekForSelection(int selectedValue)
{
    std::string dayOfWeek="";

    switch(selectedValue)
    {
        case 0:
            dayOfWeek = CResString::ex().getStrTblText(AETXT_SHORT_WEEKDAY_SU);
            break;
        case 1:
            dayOfWeek = CResString::ex().getStrTblText(AETXT_SHORT_WEEKDAY_MO);
            break;
        case 2:
            dayOfWeek = CResString::ex().getStrTblText(AETXT_SHORT_WEEKDAY_TUE);
            break;
        case 3:
            dayOfWeek = CResString::ex().getStrTblText(AETXT_SHORT_WEEKDAY_WED);
            break;
        case 4:
            dayOfWeek = CResString::ex().getStrTblText(AETXT_SHORT_WEEKDAY_TH);
            break;
        case 5:
            dayOfWeek = CResString::ex().getStrTblText(AETXT_SHORT_WEEKDAY_FR);
            break;
        case 6:
        default:
            dayOfWeek = CResString::ex().getStrTblText(AETXT_SHORT_WEEKDAY_SA);
            break;
    }

    return dayOfWeek;
}



/*******************************************************/
/*                GUI EVENT FUNCTIONS                  */
/*******************************************************/
void CDOrderPeriod::OnLvnKeydownListOrderPeriod(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

    if (pLVKeyDow->wVKey == VK_NEXT && !this->cursorEnd)
    {
        //this->fetchCount += this->ZEILEN; -> not needed since its just "next"
        this->GetDataAndFillGui();
        *pResult = 1L;
    }
    else if (pLVKeyDow->wVKey == VK_PRIOR)
    {
        int rest = this->fetchCount % this->ZEILEN-1;//since the +1 for the count, is here -1

        //Depending on the Rest determine if we can make a page up or not
        if ((rest == 0 && this->fetchCount > this->ZEILEN * 2) || (rest != 0 && this->fetchCount > this->ZEILEN))
        {
            if (rest == 0)
            {
                rest = this->ZEILEN;
            }
            this->fetchCount -= this->ZEILEN + rest;

            this->GetDataAndFillGui();
            *pResult = 1L;
        }
    }
    else
    {
        *pResult = 0L;
    }
}

void CDOrderPeriod::OnIdfInputFinished()
{
    CString idfNo = "";
    CString dayOfWeek = "";
    std::string tmp = "";
    int weekDay = -1;

    weekDay = this->cmbDayOfWeek.GetCurSel();

    this->cmbDayOfWeek.GetWindowText(dayOfWeek);
    if (dayOfWeek.IsEmpty())
    {
        weekDay = -1;
    }

    this->txtIdfNo.GetWindowText(idfNo);

    tmp = idfNo;
    if (tmp.empty())
    {
        return;
    }
    else if (!DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_IDF_NOT_VALID));
        return;
    }

    this->cmbTourID.ResetContent();

    std::vector<std::pair<CString,bool> > tourIDList;
    int rc = DataQueryHelper::getTourIDsForIDF(atol(idfNo), this->_branchNo, weekDay, tourIDList);
    if (rc == -1)
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_NOTOURFORIDF));
        return;
    }

    this->cmbTourID.AddString("");
    for (std::vector<std::pair<CString, bool> >::iterator it = tourIDList.begin(); it != tourIDList.end(); ++it)
    {
        this->cmbTourID.AddString((*it).first);
    }
}

void CDOrderPeriod::ResetSortComboBoxes()
{
    this->cmbSortPara1.ResetContent();
    this->cmbSortPara2.ResetContent();
    this->cmbSortPara3.ResetContent();

    this->cmbSortPara1.AddString( this->SORT_PARAMS_STRING[Empty] );
    this->cmbSortPara1.AddString( this->SORT_PARAMS_STRING[Tourid] );
    this->cmbSortPara1.AddString( this->SORT_PARAMS_STRING[Day] );
    this->cmbSortPara1.AddString( this->SORT_PARAMS_STRING[FromTime] );

    this->cmbSortPara1.SetCurSel(0);
    this->cmbSortPara2.EnableWindow(FALSE);
    this->cmbSortPara3.EnableWindow(FALSE);
}

void CDOrderPeriod::OnCmbSortPara1Choosen()
{
    CString curSelText;
    CString curIterText;

    //first reset other comboboxes
    this->cmbSortPara2.ResetContent();
    this->cmbSortPara3.ResetContent();
    this->cmbSortPara2.EnableWindow(FALSE);
    this->cmbSortPara3.EnableWindow(FALSE);

    //then begin sort process anew
    this->cmbSortPara1.GetWindowText(curSelText);

    //active next combobox
    this->cmbSortPara2.EnableWindow(TRUE);

    //fill with remaining possible values
    for (int i = 0; i < this->cmbSortPara1.GetCount(); i++)
    {
        this->cmbSortPara1.GetLBText(i, curIterText);
        if (curIterText != curSelText)
        {
            this->cmbSortPara2.AddString(curIterText);
        }
    }
}

void CDOrderPeriod::OnCmbSortPara2Choosen()
{
    CString curSelText;
    CString curIterText;

    this->cmbSortPara2.GetWindowText(curSelText);

    //active next combobox
    this->cmbSortPara3.EnableWindow(TRUE);

    //fill with remaining possible values
    for (int i = 0; i < this->cmbSortPara2.GetCount(); i++)
    {
        this->cmbSortPara2.GetLBText(i, curIterText);
        if (curIterText != curSelText)
        {
            this->cmbSortPara3.AddString(curIterText);
        }
    }
}

void CDOrderPeriod::OnBtnClickedCancel()
{
    this->orderPeriod.CloseCursor();

    CDialogMultiLang::OnCancel();
}

void CDOrderPeriod::OnBtnClickedInsert()
{
    OrderPeriodData data;
    CString tmp = "";

    this->txtIdfNo.GetWindowText(tmp);
    data.setIdfNo(tmp);
    this->cmbTourID.GetWindowText(tmp);
    data.setTourID(tmp);
    this->cmbDayOfWeek.GetWindowText(tmp);
    data.setWeekDay(tmp);
    data.setBranchNo(this->_branchNo);

    CDOrderPeriodChg dlgOrderPeriodChg(CDOrderPeriodChg::INSERT, data);
    dlgOrderPeriodChg.DoModal();

    //get new actual data
    this->OnBtnClickedSelect();
}

void CDOrderPeriod::OnBtnClickedUpdate()
{
    int listIndex = this->lstOrderPeriod.GetSelectionMark();

    if (listIndex >= 0)
    {
        OrderPeriodData data;
        data.setID(atol(this->lstOrderPeriod.GetItemText(listIndex,COL_HIDDEN_ID)));
        data.setOrderPeriodTimeID(atol(this->lstOrderPeriod.GetItemText(listIndex,COL_HIDDEN_ID_TIME)));

        CString tmp=this->lstOrderPeriod.GetItemText(listIndex,COL_HIDDEN_IDF);
        data.setIdfNo(tmp);

        tmp = this->lstOrderPeriod.GetItemText(listIndex,COL_TOURID);
        tmp.Remove(':');
        tmp.Remove('/');
        data.setTourID(tmp);

        data.setWeekDay(this->lstOrderPeriod.GetItemText(listIndex,COL_DAY_OF_WEEK));
        data.setWeekDayAsInt(atol(this->lstOrderPeriod.GetItemText(listIndex,COL_HIDDEN_WEEKDAY_INT)));
        data.addConsTime(this->lstOrderPeriod.GetItemText(listIndex,COL_CLOSE_TIME_1));
        data.addConsTime(this->lstOrderPeriod.GetItemText(listIndex,COL_CLOSE_TIME_2));
        data.addConsTime(this->lstOrderPeriod.GetItemText(listIndex,COL_CLOSE_TIME_3));

        data.setFromTime(DataTypeHelper::padString(this->lstOrderPeriod.GetItemText(listIndex,COL_TIME_FROM),4,'0'));
        data.setToTime(DataTypeHelper::padString(this->lstOrderPeriod.GetItemText(listIndex,COL_TIME_TILL),4,'0'));
        data.setMainTime(DataTypeHelper::padString(this->lstOrderPeriod.GetItemText(listIndex,COL_TIME_MAIN),4,'0'));

        data.setBranchNo(this->_branchNo);

        CDOrderPeriodChg dlgOrderPeriodChg(CDOrderPeriodChg::CHANGE, data);
        dlgOrderPeriodChg.DoModal();

        //get new actual data
        this->OnBtnClickedSelect();
    }
}

int CDOrderPeriod::GetWeekdayCount(int opID)
{
    CORDERPERIOD op;

    //select tourids
    op.SetId(opID);
    op.SetAnz_erfasst(-1);

    op.SelOPChildCount();
    op.CloseCursor();

    return op.GetAnz_erfasst();
}

void CDOrderPeriod::OnBtnClickedDelete()
{
    CString tmp;
    int listIndex = this->lstOrderPeriod.GetSelectionMark();

    if (listIndex >= 0)
    {
        int childCount = GetWeekdayCount(atol(this->lstOrderPeriod.GetItemText(listIndex, COL_HIDDEN_ID)));

        if (childCount == -1)
        {
            AfxMessageBox(CResString::ex().getStrTblText(AETXT_OP_DELETE_ERROR));
            return;
        }
        else if (childCount > 1)
        {
            int idOPT = atol(this->lstOrderPeriod.GetItemText(listIndex, COL_HIDDEN_ID_TIME));

            CORDERPERIOD orderPeriodDelete;
            orderPeriodDelete.SetOrder_period_id(idOPT);

            if (orderPeriodDelete.DeleteOPT())
            {
                AfxMessageBox(CResString::ex().getStrTblText(AETXT_OP_DELETE_ERROR));
                return;
            }
        }
        else
        {
            int id = atol(this->lstOrderPeriod.GetItemText(listIndex, COL_HIDDEN_ID));

            CORDERPERIOD orderPeriodDelete;
            orderPeriodDelete.SetId(id);

            if (orderPeriodDelete.DeleteOPAndOPT())
            {
                AfxMessageBox(CResString::ex().getStrTblText(AETXT_OP_DELETE_ERROR));
                return;
            }
        }

        AfxMessageBox(CResString::ex().getStrTblText(AETXT_OP_DELETE_SUCCESS));

        //get new actual data
        this->OnBtnClickedSelect();
    }
}

void CDOrderPeriod::OnBtnClickedSelect()
{
    this->fetchCount = 1;
    if (orderPeriod.CloseCursor() == 0)
    {
        orderPeriod.ClearStruct();
        this->cursorEnd = true;
    }
    this->GetDataAndFillGui();
}

void CDOrderPeriod::OnBtnClickedResetComboBoxes()
{
    this->InitComboBoxes();
}

bool CDOrderPeriod::CheckRowPeriodMisMatch(int itemIndex)
{
    try
    {
        int highestTime = 0;
        int consTime1, consTime2, consTime3;
        CString consTime;
        consTime = this->lstOrderPeriod.GetItemText(itemIndex, COL_CLOSE_TIME_1);
        consTime.Remove(':');
        consTime1 = atol(consTime);
        consTime = this->lstOrderPeriod.GetItemText(itemIndex, COL_CLOSE_TIME_2);
        consTime.Remove(':');
        consTime2 = atol(consTime);
        consTime = this->lstOrderPeriod.GetItemText(itemIndex, COL_CLOSE_TIME_3);
        consTime.Remove(':');
        consTime3 = atol(consTime);

        CString endTime = this->lstOrderPeriod.GetItemText(itemIndex, COL_TIME_TILL);
        endTime.Remove(':');
        int orderPeriodEndTime = atol(endTime);

        if (consTime1 > consTime2 && consTime1 > consTime3)
        {
            highestTime = consTime1;
        }
        else if (consTime2 > consTime1 && consTime2 > consTime3)
        {
            highestTime = consTime2;
        }
        else
        {
            highestTime = consTime3;
        }

        if ((highestTime > 0 && orderPeriodEndTime >= highestTime))
        {
            return true;
        }
        return false;
    }
    catch(...)
    {
        return false;
    }
}

void CDOrderPeriod::OnListNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    NMTVCUSTOMDRAW* pLVCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);
    switch (pNMCD->dwDrawStage)
    {
        case CDDS_PREPAINT:
            // Item prepaint notification.
            *pResult = CDRF_NOTIFYITEMDRAW;
            break;
        case CDDS_ITEMPREPAINT:
            if (CheckRowPeriodMisMatch(pNMCD->dwItemSpec))
            {
                if ((CDIS_SELECTED == (pNMCD->uItemState & CDIS_SELECTED)))
                {
                    pNMCD->uItemState = CDIS_DEFAULT;
                    pLVCD->clrText = RGB(255, 255, 255);
                    pLVCD->clrTextBk = RGB(0, 0, 255);
                }
                else
                {
                    pNMCD->uItemState = CDIS_DEFAULT;
                    pLVCD->clrTextBk = RGB(255, 0, 0);
                }
            }
            break;
        default:
            *pResult = CDRF_DODEFAULT;
            break;
    }
}

void CDOrderPeriod::OnDblClickList(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
    int listIndex = this->lstOrderPeriod.GetSelectionMark();

    if (listIndex >= 0)
    {
        this->OnBtnClickedUpdate();
    }
}
