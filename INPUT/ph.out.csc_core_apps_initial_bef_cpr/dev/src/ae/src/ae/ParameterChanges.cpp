// ParameterChanges.cpp : implementation file
//

#include "stdafx.h"
#include "ParameterChanges.h"


#define COL_CHANGE_BRANCH           0
#define COL_CHANGE_USER             1
#define COL_CHANGE_DATE             2
#define COL_CHANGE_TIME             3
#define COL_CHANGE_PARAMETER_NAME   4
#define COL_CHANGE_PARAMETER_TABLE  5
#define COL_CHANGE_OLD_VALUE        6
#define COL_CHANGE_NEW_VALUE        7
#define NUM_COL_CHANGE              8


static COLUMNS_TYPES Columns_changes[] =
{
    COL_CHANGE_BRANCH,          "",     50, LVCFMT_LEFT,
    COL_CHANGE_USER,            "",     90, LVCFMT_LEFT,
    COL_CHANGE_DATE,            "",     60, LVCFMT_LEFT,
    COL_CHANGE_TIME,            "",     50, LVCFMT_LEFT,
    COL_CHANGE_PARAMETER_NAME,  "",    180, LVCFMT_LEFT,
    COL_CHANGE_PARAMETER_TABLE, "",    180, LVCFMT_LEFT,
    COL_CHANGE_OLD_VALUE,       "",    180, LVCFMT_LEFT,
    COL_CHANGE_NEW_VALUE,       "",    180, LVCFMT_LEFT,
    -1,                         "",   0, 0
};


IMPLEMENT_DYNAMIC(CParameterChanges, CDialogEx)


CParameterChanges::CParameterChanges( CWnd* pParent /*=NULL*/ )
    : CDialogMultiLang( IDD_PARAMETER_CHANGES, pParent )
    , m_dateFromBiggerThanDateToWarningCounter( 0 )
{
}

CParameterChanges::~CParameterChanges()
{
}

void CParameterChanges::DoDataExchange( CDataExchange* pDX )
{
    CDialogMultiLang::DoDataExchange( pDX );


    DDX_Control( pDX, IDC_COMBO_BOX_BRANCH_NUMBER, m_comboBoxBranchNumber );

    DDX_Control( pDX, IDC_DATETIMEPICKER_FROM_DATE, m_dateTimePickerFromDate );

    DDX_Control( pDX, IDC_DATETIMEPICKER_TO_DATE, m_dateTimePickerToDate );

    DDX_Control( pDX, IDC_COMBO_BOX_PARAMETER, m_comboBoxParameter );

    DDX_Control( pDX, IDC_LIST_CONTROL_RESULTS, m_listControlResults );
}

void CParameterChanges::initBranchNumberComboBox()
{
    CString filiale;

    ppString ort;

    m_comboBoxBranchNumber.AddString(CResString::ex().getStrTblText(AETXT_ALLE));

    CREGIONBRANCHES regio;
    regio.SetRegionnr(AeGetApp()->VzNr());

    for (;;)
    {
        if (regio.SelList() != SRV_OK)
        {
            break;
        }

        filiale.Format("%d %s", regio.GetRegionteilnr(), regio.GetStandort_lang(ort));

        m_comboBoxBranchNumber.AddString(filiale);

        if (m_Regionliste.IsEmpty())
        {
            m_Regionliste.Format("%d", regio.GetRegionteilnr());
        }
        else
        {
            m_Regionliste.AppendFormat(",%d", regio.GetRegionteilnr());
        }
    }

    m_comboBoxBranchNumber.SetCurSel(0);
}

void CParameterChanges::setDefaultDateForFromDate()
{
    CTimeSpan minus(7, 0, 0, 0);


    CTime time( CTime::GetCurrentTime().GetYear(),
                CTime::GetCurrentTime().GetMonth(),
                CTime::GetCurrentTime().GetDay(), 0, 0, 0 );

    time -= minus; // "From date" must be 7 days earlier than the current date.


    COleDateTime date;

    date.SetDate(time.GetYear(), time.GetMonth(), time.GetDay());


    m_dateTimePickerFromDate.SetTime(date);
}

void CParameterChanges::setDefaultDateForToDate()
{
    COleDateTime date;

    date.SetDate( CTime::GetCurrentTime().GetYear(),
                  CTime::GetCurrentTime().GetMonth(),
                  CTime::GetCurrentTime().GetDay() );

    m_dateTimePickerToDate.SetTime(date);
}

void CParameterChanges::initDateTimePickers()
{
    setRangeForDateTimePickers();

    setDefaultDateForFromDate();

    setDefaultDateForToDate();
}

void CParameterChanges::setRangeForDateTimePickers()
{
    CTime endTime( CTime::GetCurrentTime().GetYear(),
                   CTime::GetCurrentTime().GetMonth(),
                   CTime::GetCurrentTime().GetDay(),
                   0,
                   0,
                   0 );

    CTimeSpan twoYears(730, 0, 0, 0); //730 ~= 2 years

    CTime beginTime = endTime - twoYears;

    m_dateTimePickerFromDate.SetRange(&beginTime, &endTime);

    m_dateTimePickerToDate.SetRange(&beginTime, &endTime);
}

void CParameterChanges::initParametersComboBox()
{
    m_comboBoxParameter.AddString(CResString::ex().getStrTblText(AETXT_ALLE));

    CPARAMETER_CHANGE_LOG_DEFS parameter_change_defs;

    BeginWaitCursor();

    parameter_change_defs.s.FETCH_REL = 1;

    for (;;)
    {
        parameter_change_defs.Server(AafilSelLogParameterDefinitions);

        if (parameter_change_defs.rc == SRV_SQLNOTFOUND)
        {
            break;
        }

        m_comboBoxParameter.AddString(parameter_change_defs.GetStruct().PARAMETER_NAME);
    }

    parameter_change_defs.s.FETCH_REL = 0;

    parameter_change_defs.Server(AafilSelLogParameterDefinitions);

    EndWaitCursor();

    m_comboBoxParameter.SetCurSel(0);
}

void CParameterChanges::initResultsListControl()
{
    createColumnsInResultsListControl();

    insertColumnsInResultsListControl();

    //The following line is added in order to create the possibility to highlight an entire row in the result list control.
    m_listControlResults.SetExtendedStyle( m_listControlResults.GetExtendedStyle() | LVS_EX_FULLROWSELECT );

    CenterWindow();

    UpdateData( FALSE );
}

void CParameterChanges::createColumnsInResultsListControl()
{
    Columns_changes[COL_CHANGE_BRANCH].Columns = CResString::ex().getStrTblText( AETXT_FILIALE );

    Columns_changes[COL_CHANGE_USER].Columns = CResString::ex().getStrTblText( IDS_ANWENDER );

    Columns_changes[COL_CHANGE_DATE].Columns = CResString::ex().getStrTblText( AETXT_DATUM );

    Columns_changes[COL_CHANGE_TIME].Columns = CResString::ex().getStrTblText( IDS_TIME );

    Columns_changes[COL_CHANGE_PARAMETER_NAME].Columns = CResString::ex().getStrTblText( AETXT_PARAM_NAME );

    Columns_changes[COL_CHANGE_PARAMETER_TABLE].Columns = CResString::ex().getStrTblText( AETXT_PARAM_TABLE );

    Columns_changes[COL_CHANGE_OLD_VALUE].Columns = CResString::ex().getStrTblText( AETXT_OLD_VALUE );

    Columns_changes[COL_CHANGE_NEW_VALUE].Columns = CResString::ex().getStrTblText( AETXT_NEW_VALUE );
}

// Add the colums one by one in the results list control before filling with data.
void CParameterChanges::insertColumnsInResultsListControl()
{
    int index = 0;

    for (;;)
    {
        m_listControlResults.InsertColumn(index, Columns_changes[index].Columns, LVCFMT_LEFT, Columns_changes[index].Width);

        ++index;

        if (Columns_changes[index].Index == -1)
        {
            break;
        }
    }
}

void CParameterChanges::setBranchNumberToParameterChangeLogging( CPARAMETER_CHANGE_LOGGING & parameterChangeLogging )
{
    CString comboBoxBranchText;

    m_comboBoxBranchNumber.GetLBText( m_comboBoxBranchNumber.GetCurSel(), comboBoxBranchText );

    const char comboBoxBranchNumber[2] = { comboBoxBranchText[0], comboBoxBranchText[1] };

    short branchNumber = static_cast<short>( atoi( comboBoxBranchNumber ) );

    parameterChangeLogging.SetBranchno( branchNumber );
}

void CParameterChanges::setDateToParameterChangeLogging( CPARAMETER_CHANGE_LOGGING & parameterChangeLogging )
{
    long fromDate = 0, toDate = 0;


    getDatesFromDateTimePickers( fromDate, toDate );


    parameterChangeLogging.SetDate_change( fromDate );

    parameterChangeLogging.SetDate_change_to( toDate );
}

void CParameterChanges::getDatesFromDateTimePickers( long & fromDate, long & toDate )
{
    CTime time;


    m_dateTimePickerFromDate.GetTime( time );


    fromDate = time.GetYear();

    fromDate = fromDate * 100 + time.GetMonth();

    fromDate = fromDate * 100 + time.GetDay();



    m_dateTimePickerToDate.GetTime( time );


    toDate = time.GetYear();

    toDate = toDate * 100 + time.GetMonth();

    toDate = toDate * 100 + time.GetDay();
}

void CParameterChanges::setParameterToParameterChangeLogging( CPARAMETER_CHANGE_LOGGING& parameterChangeLogging )
{
    CString selectedParameter;

    m_comboBoxParameter.GetLBText(m_comboBoxParameter.GetCurSel(), selectedParameter);

    if (selectedParameter != CResString::ex().getStrTblText(AETXT_ALLE))
    {
        parameterChangeLogging.SetParameter_name(selectedParameter.GetString());
    }
}

void CParameterChanges::obtainDataForListControl(CStringArray& rawInListControl, CPARAMETER_CHANGE_LOGGING& parameterChangeLogging)
{
    rawInListControl[COL_CHANGE_BRANCH].Format("%d", parameterChangeLogging.s.BRANCHNO);

    rawInListControl[COL_CHANGE_USER].Format("%s", parameterChangeLogging.s.USERNAME);

    rawInListControl[COL_CHANGE_DATE].Format("%d", parameterChangeLogging.s.DATE_CHANGE);

    rawInListControl[COL_CHANGE_TIME].Format("%d", parameterChangeLogging.s.TIME_CHANGE);

    rawInListControl[COL_CHANGE_PARAMETER_NAME].Format("%s", parameterChangeLogging.s.PARAMETER_NAME);

    rawInListControl[COL_CHANGE_PARAMETER_TABLE].Format("%s", parameterChangeLogging.s.PARAMETER_TABLE);

    rawInListControl[COL_CHANGE_OLD_VALUE].Format("%s", parameterChangeLogging.s.OLD_VALUE);

    rawInListControl[COL_CHANGE_NEW_VALUE].Format("%s", parameterChangeLogging.s.NEW_VALUE);
}

void CParameterChanges::insertDataInListControl(CStringArray& rawInListControl)
{
    auto index = m_listControlResults.GetItemCount();

    m_listControlResults.InsertItem(index, rawInListControl[COL_CHANGE_BRANCH]);

    m_listControlResults.SetItemText(index, COL_CHANGE_USER, rawInListControl[COL_CHANGE_USER]);

    m_listControlResults.SetItemText(index, COL_CHANGE_DATE, rawInListControl[COL_CHANGE_DATE]);

    m_listControlResults.SetItemText(index, COL_CHANGE_TIME, rawInListControl[COL_CHANGE_TIME]);

    m_listControlResults.SetItemText(index, COL_CHANGE_PARAMETER_NAME, rawInListControl[COL_CHANGE_PARAMETER_NAME]);

    m_listControlResults.SetItemText(index, COL_CHANGE_PARAMETER_TABLE, rawInListControl[COL_CHANGE_PARAMETER_TABLE]);

    m_listControlResults.SetItemText(index, COL_CHANGE_OLD_VALUE, rawInListControl[COL_CHANGE_OLD_VALUE]);

    m_listControlResults.SetItemText(index, COL_CHANGE_NEW_VALUE, rawInListControl[COL_CHANGE_NEW_VALUE]);
}

BEGIN_MESSAGE_MAP(CParameterChanges, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CParameterChanges::OnBnClickedButtonSearch)
    ON_BN_CLICKED(IDC_BUTTON_RESET, &CParameterChanges::OnBnClickedButtonReset)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_FROM_DATE, &CParameterChanges::OnDtnDatetimechangeDatetimepickerFromDate)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_TO_DATE, &CParameterChanges::OnDtnDatetimechangeDatetimepickerToDate)
END_MESSAGE_MAP()


// CParameterChanges message handlers


void CParameterChanges::OnBnClickedButtonSearch()
{
    CPARAMETER_CHANGE_LOGGING parameterChangeLogging;

    setBranchNumberToParameterChangeLogging(parameterChangeLogging);

    setDateToParameterChangeLogging(parameterChangeLogging);

    setParameterToParameterChangeLogging(parameterChangeLogging);

    CStringArray rawInListControl;

    rawInListControl.SetSize(NUM_COL_CHANGE);

    m_listControlResults.DeleteAllItems();

    BeginWaitCursor();

    parameterChangeLogging.s.FETCH_REL = 1;     //normaler Fetch

    for (;;)
    {
        parameterChangeLogging.Server(AafilSelLogParameter);

        parameterChangeLogging.s.FETCH_REL = 1; //normaler Fetch

        if (parameterChangeLogging.rc == SRV_SQLNOTFOUND)
        {
            break;
        }

        obtainDataForListControl(rawInListControl, parameterChangeLogging);

        insertDataInListControl(rawInListControl);
    }

    parameterChangeLogging.s.FETCH_REL = 0;

    parameterChangeLogging.Server(AafilSelLogParameter);

    EndWaitCursor();
}


void CParameterChanges::OnBnClickedButtonReset()
{
    m_comboBoxBranchNumber.SetCurSel( 0 );

    setDefaultDateForFromDate();

    setDefaultDateForToDate();

    m_comboBoxParameter.SetCurSel( 0 );

    m_listControlResults.DeleteAllItems();
}

BOOL CParameterChanges::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    initBranchNumberComboBox();

    initDateTimePickers();

    initParametersComboBox();

    initResultsListControl();

    return true;
}

void CParameterChanges::warningDateFromBiggerThanDateTo()
{
    CTime time;

    m_dateTimePickerFromDate.GetTime(time);

    long fromDate = time.GetYear() * 10000 +
        time.GetMonth() * 100 +
        time.GetDay();


    m_dateTimePickerToDate.GetTime(time);

    long toDate = time.GetYear() * 10000 +
        time.GetMonth() * 100 +
        time.GetDay();

    if (toDate < fromDate)
    {
        if (m_dateFromBiggerThanDateToWarningCounter == 0)
        {
            MsgBoxOK(AETXT_DATE_VON_BIS);

            ++m_dateFromBiggerThanDateToWarningCounter;
        }
        else
        {
            --m_dateFromBiggerThanDateToWarningCounter;
        }

        setDefaultDateForFromDate();

        setDefaultDateForToDate();
    }
}

void CParameterChanges::OnDtnDatetimechangeDatetimepickerFromDate(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    warningDateFromBiggerThanDateTo();

    *pResult = 0L;
}


void CParameterChanges::OnDtnDatetimechangeDatetimepickerToDate(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    warningDateFromBiggerThanDateTo();

    *pResult = 0L;
}
