// DKritikErf.cpp : implementation file
//

#include "stdafx.h"
#include <kndsel.h>
#include <kritiksatz.h>
#include "DKritikErf.h"

/////////////////////////////////////////////////////////////////////////////
// CDKritikErf dialog


CDKritikErf::CDKritikErf(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDKritikErf::IDD, pParent)
{
    m_CIdf = _T("");
    m_CKundenName = _T("");
    m_CPlz = _T("");
    m_COrt = _T("");
    m_CTelefon = _T("");
    m_CApotheke = _T("");
    m_CStrasse = _T("");
    m_CKurzwahl = _T("");
}


void CDKritikErf::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_KA_IDF_NUMMER, m_CIdf);
    DDX_Text(pDX, IDC_KA_KUNDE_NAME, m_CKundenName);
    DDX_Text(pDX, IDC_KA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_KA_ORT, m_COrt);
    DDX_Text(pDX, IDC_KA_TELE_NR, m_CTelefon);
    DDX_Text(pDX, IDC_KA_APO_NAME, m_CApotheke);
    DDX_Text(pDX, IDC_KA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_KA_TELE_KW, m_CKurzwahl);
}


BEGIN_MESSAGE_MAP(CDKritikErf, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDKritikErf message handlers

BOOL CDKritikErf::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CKNDINF kndinf;
    kndinf.s.IDFNR = atol(m_CIdf);
    kndinf.s.KUNDENNR = atol(m_CIdf);
    kndinf.s.VERTRIEBSZENTRUMNR = GetKndVz();
    kndinf.Server( AakundeSel_knd_info );
    if (kndinf.rc != SRV_OK)
    {
        OnCancel();
        return FALSE;
    }
    AllgEntfSpaces(kndinf.s.NAMEINHABER);
    m_CKundenName = kndinf.s.NAMEINHABER;
    AllgEntfSpaces(kndinf.s.POSTLEITZAHL);
    m_CPlz = kndinf.s.POSTLEITZAHL;
    AllgEntfSpaces(kndinf.s.ORT);
    m_COrt = kndinf.s.ORT;
    AllgEntfSpaces(kndinf.s.TELNR);
    m_CTelefon = kndinf.s.TELNR;
    AllgEntfSpaces(kndinf.s.NAMEAPO);
    m_CApotheke = kndinf.s.NAMEAPO;
    AllgEntfSpaces(kndinf.s.STRASSE);
    m_CStrasse = kndinf.s.STRASSE;
    AllgEntfSpaces(kndinf.s.TELKURZWAHL);
    m_CKurzwahl = kndinf.s.TELKURZWAHL;

    UpdateData(FALSE);

    CenterWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDKritikErf::OnOK()
{
    CString CStr;
    CKRITIKKOPF kritikkopf;
    CKRITIKPOS kritikpos;
    char textfeld[LS_KRITIKPOS_KRITIKTEXT];
    kritikkopf.s.IDFNR = atol(m_CIdf);
    kritikkopf.s.KUNDENNR = atol(m_CIdf);
    kritikkopf.s.UID = GetAeUser().GetUID();
    kritikkopf.s.VERTRIEBSZENTRUMNR = GetKndVz();
    kritikkopf.s.FILIALNR = AeGetApp()->VzNr();
    GetDlgItem(IDC_EDIT_TITEL)->GetWindowText(CStr);
    AllgStrCopy(kritikkopf.s.TITEL, CStr, L_KRITIKKOPF_TITEL);
    kritikkopf.Server(AakritikSchreibe_kopf);
    GetDlgItem(IDC_EDIT_KRITIK)->GetWindowText(CStr);
    if (!CStr.IsEmpty())
    {
        kritikpos.s.KRITIKNR = kritikkopf.s.KRITIKNR;
        kritikpos.s.KZPOSART[0] = '0';
        kritikpos.s.UID = kritikkopf.s.UID;
        kritikpos.s.FILIALNR = AeGetApp()->VzNr();
        AllgStrCopy(textfeld, CStr, L_KRITIKPOS_KRITIKTEXT);
        for (int i = 0, j = 0; i < LS_KRITIKPOS_KRITIKTEXT; i++)
        {
            if (textfeld[i] == '\0')
            {
                kritikpos.s.KRITIKTEXT[j] = '\0';
                if ((strlen(kritikpos.s.KRITIKTEXT)) != 0)
                    kritikpos.Server(AakritikSchreibe_pos);
                j = 0;
                break;
            }
            else if (textfeld[i] == VK_RETURN)
            {
                kritikpos.s.KRITIKTEXT[j] = '\0';
                if ((strlen(kritikpos.s.KRITIKTEXT)) != 0)
                    kritikpos.Server(AakritikSchreibe_pos);
                j = 0;
            }
            else if (textfeld[i] != 10)
            {
                kritikpos.s.KRITIKTEXT[j] = textfeld [i];
                ++j;
            }
        }
    }
    GetDlgItem(IDC_EDIT_KRITIK2)->GetWindowText(CStr);
    if (!CStr.IsEmpty())
    {
        kritikpos.s.KRITIKNR = kritikkopf.s.KRITIKNR;
        kritikpos.s.KZPOSART[0] = '1';
        kritikpos.s.UID = kritikkopf.s.UID;
        kritikpos.s.FILIALNR =  AeGetApp()->VzNr();
        AllgStrCopy(textfeld, CStr, L_KRITIKPOS_KRITIKTEXT);
        for (int i = 0, j = 0; i < LS_KRITIKPOS_KRITIKTEXT; i++)
        {
            if (textfeld[i] == '\0')
            {
                kritikpos.s.KRITIKTEXT[j] = '\0';
                if ((strlen(kritikpos.s.KRITIKTEXT)) != 0)
                    kritikpos.Server(AakritikSchreibe_pos);
                j = 0;
                break;
            }
            else if (textfeld[i] == VK_RETURN)
            {
                kritikpos.s.KRITIKTEXT[j] = '\0';
                if ((strlen(kritikpos.s.KRITIKTEXT)) != 0)
                    kritikpos.Server(AakritikSchreibe_pos);
                j = 0;
            }
            else if (textfeld[i] != 10)
            {
                kritikpos.s.KRITIKTEXT[j] = textfeld [i];
                ++j;
            }
        }
    }
    CDialogMultiLang::OnOK();
}
