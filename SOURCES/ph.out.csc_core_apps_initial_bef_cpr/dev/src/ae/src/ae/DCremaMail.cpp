#include "stdafx.h"

#include "DCremaMail.h"

BEGIN_MESSAGE_MAP(DCremaMail, CDialogMultiLang)
    ON_CBN_SELENDOK(IDC_CBO_MAILGROUP, OnCmbSelectionChanged )
    ON_BN_CLICKED(  IDCLOSE,           OnBtnClickedClose     )
    ON_BN_CLICKED(IDC_BTN_ADD_MAIL,    OnBtnClickedAddMail   )
    ON_BN_CLICKED(IDC_BTN_DELETE_MAIL, OnBtnClickedDeleteMail)
    ON_EN_CHANGE(IDC_ED_MAIL,          OnEnChangeEdMail      )
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_MAILS, OnListItemChanged )
    ON_BN_CLICKED(IDC_BTN_CANCEL,      OnBnClickedCancel     )
    ON_BN_CLICKED(IDC_CK_GVL_MAIL,     OnBtnClickedGVL       )
    ON_BN_CLICKED(IDC_CHK_GVL_FULL,    OnBtnClickedGVLFull   )
    ON_BN_CLICKED(IDC_CHK_GVL_INFO_MAIL, OnBtnClickedGVLInfo )
    ON_BN_CLICKED(IDC_BTN_GVL_SAVE,    OnBtnClickedGVLSave   )
END_MESSAGE_MAP()

DCremaMail::DCremaMail(short branchNo, CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(DCremaMail::IDD, pParent), m_BranchNo(branchNo)
{
}

DCremaMail::~DCremaMail()
{
}

void DCremaMail::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_CBO_MAILGROUP,   m_cboMailGroup );
    DDX_Control(pDX, IDC_LST_MAILS,       m_lstMails     );
    DDX_Control(pDX, IDCLOSE,             m_btnClose     );
    DDX_Control(pDX, IDC_BTN_ADD_MAIL,    m_btnAddMail   );
    DDX_Control(pDX, IDC_BTN_CANCEL,      m_btnCancel    );
    DDX_Control(pDX, IDC_BTN_DELETE_MAIL, m_btnDeleteMail);
    DDX_Control(pDX, IDC_ED_MAIL,         m_edMail       );
    DDX_Control(pDX, IDC_CK_INFO_MAIL,    m_ckInfoMail   );
    DDX_Control(pDX, IDC_CK_NORM_MAIL,    m_ckNormalMail );
    DDX_Control(pDX, IDC_CK_GVL_MAIL,     m_ckGVLMail    );
    DDX_Control(pDX, IDC_CHK_GVL_FULL,    m_ckGVLMailFull);
    DDX_Control(pDX, IDC_CHK_GVL_INFO_MAIL, m_ckGVLMailInfo);
    DDX_Control(pDX, IDC_BTN_GVL_SAVE,    m_btnGVLSave   );
}

BOOL DCremaMail::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    SetupList();
    SetupComboBox();

    return TRUE;
}

void DCremaMail::SetupComboBox()
{
    CCREMAEMAILREASONS mailReasons;
    mailReasons.SetBranchno(m_BranchNo);

    for (mailReasons.SelEmailReasons(); mailReasons.rc == SRV_OK; mailReasons.SelEmailReasons())
    {
        CString group;

        switch (mailReasons.GetType())
        {
        case 0:
            group.Format("%s: %g", CResString::ex().getStrTblText(AETXT_PERCENTAGE).GetString(), mailReasons.GetDlpercentage() );
            break;
        case 1:
            group.Format("%s: %g", CResString::ex().getStrTblText(AETXT_AMOUNT).GetString(), mailReasons.GetThresholdamount() );
            break;
        default:
            // unknown value
            group = "Unknown value for crematype.type";
        }

        const int item = m_cboMailGroup.AddString(group);
        m_cboMailGroup.SetItemData(item, mailReasons.GetId());
    }
    if (mailReasons.rc == SRV_SQLNOTFOUND)
    {
        mailReasons.CloseCursor();
    }

    m_cboMailGroup.SetCurSel(0);

    updateTable();
}

void DCremaMail::SetupList()
{
    DWORD dwOldBits = m_lstMails.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_lstMails.SetExtendedStyle(dwOldBits);

    m_lstMails.InsertColumn(0, CResString::ex().getStrTblText(AETXT_MAIL), LVCFMT_LEFT, 180, 0);
    m_lstMails.InsertColumn(1, CResString::ex().getStrTblText(AETXT_TYP), LVCFMT_LEFT, 100, 1);
}

bool DCremaMail::validateMail(const char* mail)
{
    int        count = 0;
    const char* c, * domain;
    static char* rfc822_specials = "()<>@,;:\\\"[]";

    /* first we validate the name portion (name@domain) */
    for (c = mail; *c; c++)
    {
        if (*c == '\"' && (c == mail || *(c - 1) == '.' || *(c - 1) == '\"'))
        {
            while (*++c)
            {
                if (*c == '\"')
                    break;
                if (*c == '\\' && (*++c == ' '))
                    continue;
                if (*c <= ' ' || *c >= 127)
                    return false;
            }
            if (!*c++)
                return false;
            if (*c == '@')
                break;
            if (*c != '.')
                return false;
            continue;
        }
        if (*c == '@')
            break;
        if (*c <= ' ' || *c >= 127)
            return false;
        if (strchr(rfc822_specials, *c))
            return false;
    }
    if (c == mail || *(c - 1) == '.')
        return false;

    /* next we validate the domain portion (name@domain) */
    if (!*(domain = ++c))
        return false;
    do 
    {
        if (*c == '.')
        {
            if (c == domain || *(c - 1) == '.')
                return false;
            if (*(c + 1) == NULL)
                return false;
            ++count;
        }
        if (*c <= ' ' || *c >= 127)
            return false;
        if (strchr(rfc822_specials, *c))
            return false;
    }
    while (*++c);

    return (count >= 1);
}

void DCremaMail::clearInputFields()
{
    // unselect selected item
    m_lstMails.SetItemState(m_lstMails.GetSelectionMark(), 0, LVIS_SELECTED);

    m_edMail.SetWindowTextA("");
    m_ckInfoMail.SetCheck(0);
}

void DCremaMail::setGVLAccordingToSelectionTable()
{
    CCREMAEMAILADDRESSES mailAddresses;
    mailAddresses.SetEmailtype(-1);
    mailAddresses.SetSmtpusergroupid(m_cboMailGroup.GetItemData(m_cboMailGroup.GetCurSel()));

    m_ckGVLMail.SetCheck(BST_UNCHECKED);
    m_ckGVLMailFull.SetCheck(BST_UNCHECKED);
    m_ckGVLMailInfo.SetCheck(BST_UNCHECKED);
    m_ckGVLMailFull.EnableWindow(false);
    m_ckGVLMailInfo.EnableWindow(false);

    int row = 0;
    for (mailAddresses.SelEmailType(); mailAddresses.rc == SRV_OK; mailAddresses.SelEmailType(), row++)
    {
        if (mailAddresses.GetSendgvlmail() == 1)
        {
            m_ckGVLMail.SetCheck(BST_CHECKED);
            m_ckGVLMailFull.EnableWindow(true);
            m_ckGVLMailInfo.EnableWindow(true);

            if (mailAddresses.GetEmailtype() == 0)
            {
                m_ckGVLMailFull.SetCheck(BST_CHECKED);
            }
            else if (mailAddresses.GetEmailtype() == 1)
            {
                m_ckGVLMailInfo.SetCheck(BST_CHECKED);
            }
        }
    }
    if (mailAddresses.rc == SRV_SQLNOTFOUND)
    {
        mailAddresses.CloseCursor();
    }
}

void DCremaMail::updateTable()
{
    m_lstMails.DeleteAllItems();

    setGVLAccordingToSelectionTable();
    
    CCREMAEMAILADDRESSES mailAddresses;
    mailAddresses.SetSmtpusergroupid(m_cboMailGroup.GetItemData(m_cboMailGroup.GetCurSel()));

    int row = 0;
    for (mailAddresses.SelEmailAddresses(); mailAddresses.rc == SRV_OK; mailAddresses.SelEmailAddresses(), row++)
    {
        CString type;
        switch (mailAddresses.GetEmailtype())
        {
        case 0:
            type = CResString::ex().getStrTblText(AETXT_MAIL_STATIC);
            break;
        case 1:
            type = CResString::ex().getStrTblText(AETXT_MAIL_INFO);
            break;
        default:
            type = CResString::ex().getStrTblText(IDS_UNKNOWN);
        }

        ppString addr;

        if (strcmp(mailAddresses.GetSenttoaddress(addr), "") != 0)
        {
            int item = m_lstMails.InsertItem(row, mailAddresses.GetSenttoaddress(addr));
            m_lstMails.SetItemText(item, 1, type);

            m_lstMails.SetItemData(item, mailAddresses.GetId());
        }
    }
    if (mailAddresses.rc == SRV_SQLNOTFOUND)
    {
        mailAddresses.CloseCursor();
    }
}

void DCremaMail::switchToInsertMode()
{
    m_btnAddMail.SetWindowTextA(CResString::ex().getStrTblText(AETXT_ADD));
    m_btnDeleteMail.EnableWindow(FALSE);
    clearInputFields();
}

void DCremaMail::OnCmbSelectionChanged()
{
    updateTable();
}

void DCremaMail::OnBtnClickedClose()
{
    EndDialog(0);
}

void DCremaMail::OnBtnClickedAddMail()
{
    if (!CheckEmailType(FULLMAIL))
    {
        InsertType(FULLMAIL);
    }
    if (!CheckEmailType(INFOMAIL))
    {
        InsertType(INFOMAIL);
    }

    if (m_ckNormalMail.GetCheck() == BST_CHECKED)
    {
        CCREMAEMAILADDRESSES addresses;
        addresses.SetEmailtype(FULLMAIL);
        AddEmail(addresses);
    }
    if (m_ckInfoMail.GetCheck() == BST_CHECKED)
    {
        CCREMAEMAILADDRESSES addresses;
        addresses.SetEmailtype(INFOMAIL);
        AddEmail(addresses);
    }

    updateTable();
    clearInputFields();
    switchToInsertMode();
}

int DCremaMail::AddEmail(CCREMAEMAILADDRESSES addresses)
{
    CString mailAddr;
    DWORD_PTR data = m_cboMailGroup.GetItemData(m_cboMailGroup.GetCurSel());

    GetDlgItemText(IDC_ED_MAIL, mailAddr);
    addresses.SetSmtpusergroupid(data);
    addresses.SelEmailType();

    int smtpEmailTypeId = addresses.GetSmtpemailtypeid();

    if (smtpEmailTypeId != -1)
    {
        addresses.SetSmtpemailtypeid(smtpEmailTypeId);
        addresses.SetSenttoaddress(mailAddr);
    }

    CString label;
    m_btnAddMail.GetWindowTextA(label);
    const bool isChangeMode = (label == CResString::ex().getStrTblText(AETXT_CHANGE));
    int rc;
    if (isChangeMode)
    {
        addresses.SetId(m_mailID);
        rc = addresses.UpdateEmailAddress();
    }
    else
    {
        rc = addresses.InsertAddress();
    }

    return rc;
}

void DCremaMail::OnBtnClickedDeleteMail()
{
    DWORD_PTR data = m_lstMails.GetItemData(m_lstMails.GetSelectionMark());
    CCREMAEMAILADDRESSES addresses;
    addresses.SetId(data);
    addresses.DeleteAddress();

    updateTable();
}

void DCremaMail::OnEnChangeEdMail()
{
    // validate entered E-Mail address
    CString text;
    GetDlgItemText(IDC_ED_MAIL, text);

    m_btnAddMail.EnableWindow(validateMail(text));
}

void DCremaMail::OnListItemChanged(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if ((pNMListView->uChanged & LVIF_STATE))
    {
        if (pNMListView->uNewState & LVIS_SELECTED)
        {
            // item is selected
            m_btnDeleteMail.EnableWindow(TRUE);
            m_edMail.SetWindowTextA(m_lstMails.GetItemText(pNMListView->iItem, 0));

            const bool infoMailSet = m_lstMails.GetItemText(pNMListView->iItem, 1) == CResString::ex().getStrTblText(AETXT_MAIL_INFO);
            m_ckInfoMail.SetCheck(infoMailSet);

            const bool normalMailSet = m_lstMails.GetItemText(pNMListView->iItem, 1) == CResString::ex().getStrTblText(AETXT_MAIL_STATIC);
            m_ckNormalMail.SetCheck(normalMailSet);

            m_btnAddMail.SetWindowTextA(CResString::ex().getStrTblText(AETXT_CHANGE));
            m_mailID = m_lstMails.GetItemData(m_lstMails.GetSelectionMark());
        }
    }
    else
    {
        switchToInsertMode();
    }
}

void DCremaMail::OnBnClickedCancel()
{
    switchToInsertMode();
}

void DCremaMail::OnBtnClickedGVL()
{
    if (m_ckGVLMailFull.GetCheck() != BST_CHECKED && m_ckGVLMailInfo.GetCheck() != BST_CHECKED)
    {
        m_ckGVLMailFull.EnableWindow(true);
        m_ckGVLMailInfo.EnableWindow(true);
    }
}

void DCremaMail::OnBtnClickedGVLFull()
{
    if (m_ckGVLMailFull.GetCheck() != BST_CHECKED && m_ckGVLMailInfo.GetCheck() != BST_CHECKED)
    {
        m_ckGVLMail.SetCheck(BST_UNCHECKED);
    }
}

void DCremaMail::OnBtnClickedGVLInfo()
{
    if (m_ckGVLMailFull.GetCheck() != BST_CHECKED && m_ckGVLMailInfo.GetCheck() != BST_CHECKED)
    {
        m_ckGVLMail.SetCheck(BST_UNCHECKED);
    }
}

void DCremaMail::OnBtnClickedGVLSave()
{
    if (!SaveGVL())
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_SAVE_GVL_FAILED));
    }
}

bool DCremaMail::CheckEmailType(EMAILTYPES emailType)
{
    CCREMAEMAILADDRESSES mailAddresses;
    mailAddresses.SetSmtpusergroupid(m_cboMailGroup.GetItemData(m_cboMailGroup.GetCurSel()));

    if (emailType != -1)
    {
        mailAddresses.SetEmailtype((short)emailType);
    }

    int row = 0;
    for (mailAddresses.SelEmailType(); mailAddresses.rc == SRV_OK; mailAddresses.SelEmailType(), row++)
    {
    }

    if (mailAddresses.rc == SRV_SQLNOTFOUND)
    {
        mailAddresses.CloseCursor();
    }

    return row == 0 ? false : true;
}

int DCremaMail::InsertType(short type)
{
     //insert static type
    CCREMAEMAILADDRESSES mailAddresses;
    mailAddresses.SetSmtpusergroupid(m_cboMailGroup.GetItemData(m_cboMailGroup.GetCurSel()));
    mailAddresses.SetEmailtype(type);
    int rc = mailAddresses.InsertType();//get last inserted id smtpemailtypeid
    
    if (rc != SRV_OK)
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_SAVE_MAILTYPE_FAILED));
    }

    return mailAddresses.GetSmtpemailtypeid();
}

bool DCremaMail::SaveGVL()
{
    int rc = -1;

    if (m_ckGVLMail.GetCheck() == BST_CHECKED && (m_ckGVLMailFull.GetCheck() != BST_CHECKED && m_ckGVLMailInfo.GetCheck() != BST_CHECKED))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_GVL_ERROR));
        return false;
    }

    if (CheckEmailType(NONE))
    {
        CCREMAEMAILADDRESSES mailAddresses;
        mailAddresses.SetEmailtype(-1);
        mailAddresses.SetSmtpusergroupid(m_cboMailGroup.GetItemData(m_cboMailGroup.GetCurSel()));
        int row = 0;
        for (mailAddresses.SelEmailType(); mailAddresses.rc == SRV_OK; mailAddresses.SelEmailType(), row++)
        {
            CCREMAEMAILADDRESSES mailAddressesChange;
            if (mailAddresses.GetEmailtype() == 0)
            {
                mailAddressesChange.s = mailAddresses.s;
                mailAddressesChange.SetSendgvlmail(m_ckGVLMailFull.GetCheck() == BST_CHECKED && m_ckGVLMail.GetCheck() == BST_CHECKED);
                if (mailAddresses.GetSendgvlmail() == -1)
                {
                    rc = mailAddressesChange.InsertGVL();
                }
                else
                {
                    rc = mailAddressesChange.UpdateGVL();
                }
            }
            else if (mailAddresses.GetEmailtype() == 1)
            {
                mailAddressesChange.s = mailAddresses.s;
                mailAddressesChange.SetSendgvlmail(m_ckGVLMailInfo.GetCheck() == BST_CHECKED && m_ckGVLMail.GetCheck() == BST_CHECKED);
                if (mailAddresses.GetSendgvlmail() == -1)
                {
                    rc = mailAddressesChange.InsertGVL();
                }
                else
                {
                    rc = mailAddressesChange.UpdateGVL();
                }
            }
        }
        if (mailAddresses.rc == SRV_SQLNOTFOUND)
        {
            mailAddresses.CloseCursor();
        }
    }
    else
    {
        int smtpEmailTypeid = -1;
        rc = SRV_OK;
        //insert static type
        if (!CheckEmailType(FULLMAIL))
        {
            smtpEmailTypeid = InsertType(FULLMAIL);
        
            CCREMAEMAILADDRESSES mailAddressesInsertStatic;

            mailAddressesInsertStatic.SetSmtpemailtypeid(smtpEmailTypeid);
            mailAddressesInsertStatic.SetSendgvlmail(m_ckGVLMailFull.GetCheck() == BST_CHECKED && m_ckGVLMail.GetCheck() == BST_CHECKED);
            rc = mailAddressesInsertStatic.InsertGVL();
        }

        if (!CheckEmailType(INFOMAIL))
        {
            //insert info type
            smtpEmailTypeid = InsertType(INFOMAIL);
        
            CCREMAEMAILADDRESSES mailAddressesInsertInfo;

            mailAddressesInsertInfo.SetSmtpemailtypeid(smtpEmailTypeid);
            mailAddressesInsertInfo.SetSendgvlmail(m_ckGVLMailInfo.GetCheck() == BST_CHECKED && m_ckGVLMail.GetCheck() == BST_CHECKED);
            rc = mailAddressesInsertInfo.InsertGVL();
        }
    }

    return rc == SRV_OK ? true : false;
}
