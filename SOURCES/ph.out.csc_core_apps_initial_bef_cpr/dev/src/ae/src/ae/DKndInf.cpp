// dkndinf.cpp : implementation file
//

#include "stdafx.h"
#include <kndsel.h>
#include "zeitart.h"
#include "DKndWahl.h"
#include "DKndInf.h"
#include "AeFView.h"
#include "aarufpl.h"
#include <artikel.h>
#include <filialpartner.h>
#include <msv3.h>
#include <tourdelay.h>
#include "DHPMakeCall.h"

#define PLAN_DAFUE_PARA     '1'
#define PLAN_DAFUE_SERA     '2'
#define PLAN_PHONETIK       '3'
#define PLAN_DAFUE_AUTO     '4'

/////////////////////////////////////////////////////////////////////////////
// CKndInf

int CKndInf::DoModal()
{
    char str[81];
    CString cstr;
    m_KzAeGesperrt = false;
    m_bKtoExist = false;
    if (m_IdfNr != -1 && m_KndNr == -1)
    {
        //static CKNDSEL kndsel;
        CKNDSEL kndsel;
        kndsel.s.IDFNR = m_IdfNr;
        kndsel.s.VERTRIEBSZENTRUMNR = m_VzNr;
        kndsel.s.REGIONNR = AeGetApp()->VzNr();
        kndsel.s.SKDKUNDEAEGESPERRT[0] = '1';
        kndsel.s.FETCH_REL = 1;
        kndsel.Server(AakundeSel_idf);
        if (kndsel.rc == SRV_OK)
            m_KndNr = kndsel.s.KUNDENNR;
        kndsel.s.FETCH_REL = 0;
        kndsel.Server(AakundeSel_idf);
    }
    if (m_KndNr == -1)
    {
        //Definition Kunde
        CDKndWahl dlgKndWahl;
        if (m_IdfNr != -1)
            dlgKndWahl.m_CKndNr.Format("%d", m_IdfNr);
        dlgKndWahl.SetEnableAeGesperrt();    // Checkbutton muß enabled werden
        if (dlgKndWahl.DoModal() == IDOK)
        {
            m_IdfNr = dlgKndWahl.GetIdfNr();
            m_KndNr = dlgKndWahl.GetKndNr();
            m_VzNr = dlgKndWahl.GetKndVz();
            m_KzAeGesperrt = dlgKndWahl.GetKzAeGesperrt();
        }
        else
        {
            return IDCANCEL;
        }
    }
    AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf.cpp", "DoModal", "Dialog started");
    //Ermittlung der Kundeninformationen
    CKNDAUSKU kndausku;
    kndausku.s.IDFNR               = m_IdfNr;
    kndausku.s.KUNDENNR            = m_KndNr;
    kndausku.s.VERTRIEBSZENTRUMNR  = m_VzNr;
    CKNDINF kndinf;
    kndinf.s.IDFNR               = m_IdfNr;
    kndinf.s.KUNDENNR            = m_KndNr;
    kndinf.s.VERTRIEBSZENTRUMNR  = m_VzNr;
    CMCUSTOMERVACATION mcustomervacation;
    mcustomervacation.SetVertriebszentrumnr(m_VzNr);
    mcustomervacation.SetKundennr(m_KndNr);

    AfxGetApp()->BeginWaitCursor();
    CTM tm;
    tm.Server(AafilGetdatetime);
    kndausku.Server(AakundeSel_ausku);
    kndinf.Server(AakundeSel_knd_info);
    AfxGetApp()->EndWaitCursor();
    if (kndausku.rc < SRV_OK)
        return IDCANCEL;

    //Ausgabe der Artikelinformationen
    CPSKndInf   PSKndInf(CResString::ex().getStrTblText(AETXT_KUNDENINFORMATION));
    CDKndInf1   DKndInf1;
    CDKndInf2   DKndInf2;
    CDKndInf3   DKndInf3;
    CDKndInf4   DKndInf4;
    CDKndInf5   DKndInf5;
    CDKndInf6   DKndInf6;
    CDKndInf7   DKndInf7;
    CDKndInf8   DKndInf8;
    CDKndInf9   DKndInf9;
    CDKndInf10  DKndInf10;
    CDKndInf11  DKndInf11;

    CKNDSCHALTER kndschalter;
    kndschalter.s.IDFNR               = m_IdfNr;
    kndschalter.s.KUNDENNR            = m_KndNr;
    kndschalter.s.VERTRIEBSZENTRUMNR  = m_VzNr;
    kndschalter.Server(AakundeSel_kndschalter);
    DKndInf1.m_CVerbund.Empty();
    if (kndschalter.s.SKDVERBUNDGANZ[0] == '1')
        DKndInf1.m_CVerbund = CResString::ex().getStrTblText(AETXT_KZ_JA);
    else
    {
        CZEITARTV zeitartv;
        sprintf(zeitartv.s.ZEITSCHLUESSEL, "%ld", m_KndNr);
        zeitartv.s.VERTRIEBSZENTRUMNR = m_VzNr;
        zeitartv.s.FETCH_REL = 1;  // normaler Fetch
        for (int i = 0; i < 2; i++)
        {
            zeitartv.Server(AafilSel_verbund);
            if (zeitartv.rc != SRV_OK)
                break;
            if (i > 0)
                DKndInf1.m_CVerbund += " / ";
            ppGTimeLongToCharHHMM(zeitartv.s.ZEITBEGIN, str);
            DKndInf1.m_CVerbund += str;
            DKndInf1.m_CVerbund += " - ";
            ppGTimeLongToCharHHMM(zeitartv.s.ZEITENDE, str);
            DKndInf1.m_CVerbund += str;
        }
        zeitartv.s.FETCH_REL = 0;  // Schliessen cursor
        zeitartv.Server(AafilSel_verbund);
    }
    if (AeGetApp()->IsBG())
    {
        if ((CAeDoc*)((CAeFView*)AeGetApp()->m_pViewEing)->GetDocument()->IsModified())     //Auftrag offen
        {
            m_MainNr = AeGetApp()->MainCstNo();
        }
        else
        {
            CCSTBULGARIA cstbulgaria;
            cstbulgaria.SetKundennr(kndausku.s.KUNDENNR);
            cstbulgaria.SetVertriebszentrumnr(kndausku.s.VERTRIEBSZENTRUMNR);
            if (!cstbulgaria.SelCst())
            {
                m_MainNr = cstbulgaria.GetMaincstno();
            }
            else
            {
                m_MainNr = 0;
            }
        }

        if (m_MainNr == 0)
        {
            CCSTDISCACC cstdiscacc;
            cstdiscacc.SetBranchno(m_VzNr);
            cstdiscacc.SetCustomerno(m_KndNr);
            if (!cstdiscacc.CheckExist())
            {
                m_bKtoExist = true;
            }
        }
        else
        {
            m_bKtoExist = true;
        }
    }

    //Einstellung Daten Kopfinformationen
    DKndInf1.m_IdfNr        = DKndInf2.m_IdfNr          = DKndInf4.m_IdfNr      = m_IdfNr;
    DKndInf1.m_KzAeGesperrt = DKndInf2.m_KzAeGesperrt   = m_KzAeGesperrt;
    DKndInf1.m_KndNr        = DKndInf2.m_KndNr          = DKndInf3.m_KndNr      = DKndInf4.m_KndNr = m_KndNr;
    DKndInf1.m_VzNr         = DKndInf2.m_VzNr           = DKndInf3.m_VzNr       = DKndInf4.m_VzNr  = m_VzNr;
    DKndInf1.m_CApoName     = DKndInf2.m_CApoName       = DKndInf4.m_CApoName   = kndausku.s.NAMEAPO;
    DKndInf1.m_CIdfNummer   = DKndInf2.m_CIdfNummer     = DKndInf4.m_CIdfNummer = _ltoa(kndausku.s.IDFNR, str, 10);
    DKndInf1.m_CKundeName   = DKndInf2.m_CKundeName     = DKndInf4.m_CKundeName = kndausku.s.NAMEINHABER;
    DKndInf1.m_COrt         = DKndInf2.m_COrt           = DKndInf4.m_COrt       = kndausku.s.ORT;
    DKndInf1.m_CPlz         = DKndInf2.m_CPlz           = DKndInf4.m_CPlz       = kndausku.s.POSTLEITZAHL;
    DKndInf1.m_CStrasse     = DKndInf2.m_CStrasse       = DKndInf4.m_CStrasse   = kndausku.s.STRASSE;
    DKndInf1.m_CTeleKw      = DKndInf2.m_CTeleKw        = DKndInf4.m_CTeleKw    = kndausku.s.TELKURZWAHL;
    DKndInf1.m_CTeleNr      = DKndInf2.m_CTeleNr        = DKndInf4.m_CTeleNr    = kndausku.s.TELNR;
    DKndInf1.m_CAbc         = DKndInf2.m_CAbc           = DKndInf4.m_CAbc       = kndinf.s.KZKDKLASSE;
    AllgEntfSpaces(kndinf.s.EMAILADRESSE);
    DKndInf1.m_CEmail       = kndinf.s.EMAILADRESSE;

    DKndInf5.m_KndNr        = DKndInf1.m_KndNr;
    DKndInf5.m_VzNr         = DKndInf1.m_VzNr;
    DKndInf5.m_CApoName     = DKndInf1.m_CApoName;
    DKndInf5.m_CIdfNummer   = DKndInf1.m_CIdfNummer;
    DKndInf5.m_CKundeName   = DKndInf1.m_CKundeName;
    DKndInf5.m_COrt         = DKndInf1.m_COrt;
    DKndInf5.m_CPlz         = DKndInf1.m_CPlz;
    DKndInf5.m_CStrasse     = DKndInf1.m_CStrasse;
    DKndInf5.m_CTeleKw      = DKndInf1.m_CTeleKw;
    DKndInf5.m_CTeleNr      = DKndInf1.m_CTeleNr;
    DKndInf5.m_CAbc         = DKndInf1.m_CAbc;

    if (AeGetApp()->IsBG() && m_MainNr > 0)
    {
        DKndInf6.m_MainNr       = m_MainNr;
        DKndInf6.m_KndNr        = DKndInf1.m_KndNr;
        DKndInf6.m_VzNr         = DKndInf1.m_VzNr;
        DKndInf6.m_CApoName     = DKndInf1.m_CApoName;
        DKndInf6.m_CIdfNummer   = DKndInf1.m_CIdfNummer;
        DKndInf6.m_CKundeName   = DKndInf1.m_CKundeName;
        DKndInf6.m_COrt         = DKndInf1.m_COrt;
        DKndInf6.m_CPlz         = DKndInf1.m_CPlz;
        DKndInf6.m_CStrasse     = DKndInf1.m_CStrasse;
        DKndInf6.m_CTeleKw      = DKndInf1.m_CTeleKw;
        DKndInf6.m_CTeleNr      = DKndInf1.m_CTeleNr;
        DKndInf6.m_CAbc         = DKndInf1.m_CAbc;
    }
    if (AeGetApp()->IsBG() && m_bKtoExist)
    {
        DKndInf7.m_TMZeit       = tm.s;
        DKndInf7.m_MainNr       = m_MainNr;
        DKndInf7.m_bKtoExist    = m_bKtoExist;
        DKndInf7.m_KndNr        = DKndInf1.m_KndNr;
        DKndInf7.m_VzNr         = DKndInf1.m_VzNr;
        DKndInf7.m_CApoName     = DKndInf1.m_CApoName;
        DKndInf7.m_CIdfNummer   = DKndInf1.m_CIdfNummer;
        DKndInf7.m_CKundeName   = DKndInf1.m_CKundeName;
        DKndInf7.m_COrt         = DKndInf1.m_COrt;
        DKndInf7.m_CPlz         = DKndInf1.m_CPlz;
        DKndInf7.m_CStrasse     = DKndInf1.m_CStrasse;
        DKndInf7.m_CTeleKw      = DKndInf1.m_CTeleKw;
        DKndInf7.m_CTeleNr      = DKndInf1.m_CTeleNr;
        DKndInf7.m_CAbc         = DKndInf1.m_CAbc;
    }
    if (AeGetApp()->IsBG())
    {
        DKndInf8.m_TMZeit       = tm.s;
        DKndInf8.m_KndNr        = DKndInf1.m_KndNr;
        DKndInf8.m_VzNr         = DKndInf1.m_VzNr;
        DKndInf8.m_CApoName     = DKndInf1.m_CApoName;
        DKndInf8.m_CIdfNummer   = DKndInf1.m_CIdfNummer;
        DKndInf8.m_CKundeName   = DKndInf1.m_CKundeName;
        DKndInf8.m_COrt         = DKndInf1.m_COrt;
        DKndInf8.m_CPlz         = DKndInf1.m_CPlz;
        DKndInf8.m_CStrasse     = DKndInf1.m_CStrasse;
        DKndInf8.m_CTeleKw      = DKndInf1.m_CTeleKw;
        DKndInf8.m_CTeleNr      = DKndInf1.m_CTeleNr;
        DKndInf8.m_CAbc         = DKndInf1.m_CAbc;
    }
    if (AeGetApp()->IsBG())
    {
        DKndInf9.m_KndNr        = DKndInf1.m_KndNr;
        DKndInf9.m_VzNr         = DKndInf1.m_VzNr;
        DKndInf9.m_CApoName     = DKndInf1.m_CApoName;
        DKndInf9.m_CIdfNummer   = DKndInf1.m_CIdfNummer;
        DKndInf9.m_CKundeName   = DKndInf1.m_CKundeName;
        DKndInf9.m_COrt         = DKndInf1.m_COrt;
        DKndInf9.m_CPlz         = DKndInf1.m_CPlz;
        DKndInf9.m_CStrasse     = DKndInf1.m_CStrasse;
        DKndInf9.m_CTeleKw      = DKndInf1.m_CTeleKw;
        DKndInf9.m_CTeleNr      = DKndInf1.m_CTeleNr;
        DKndInf9.m_CAbc         = DKndInf1.m_CAbc;
    }
    if (AeGetApp()->IsDE())
    {
        DKndInf10.m_KndNr       = DKndInf1.m_KndNr;
        DKndInf10.m_VzNr        = DKndInf1.m_VzNr;
        DKndInf10.m_CApoName    = DKndInf1.m_CApoName;
        DKndInf10.m_CIdfNummer  = DKndInf1.m_CIdfNummer;
        DKndInf10.m_CKundeName  = DKndInf1.m_CKundeName;
        DKndInf10.m_COrt        = DKndInf1.m_COrt;
        DKndInf10.m_CPlz        = DKndInf1.m_CPlz;
        DKndInf10.m_CStrasse    = DKndInf1.m_CStrasse;
        DKndInf10.m_CTeleKw     = DKndInf1.m_CTeleKw;
        DKndInf10.m_CTeleNr     = DKndInf1.m_CTeleNr;
        DKndInf10.m_CAbc        = DKndInf1.m_CAbc;
    }

    DKndInf11.m_KndNr       = DKndInf1.m_KndNr;
    DKndInf11.m_VzNr        = DKndInf1.m_VzNr;
    DKndInf11.m_CApoName    = DKndInf1.m_CApoName;
    DKndInf11.m_CIdfNummer  = DKndInf1.m_CIdfNummer;
    DKndInf11.m_CKundeName  = DKndInf1.m_CKundeName;
    DKndInf11.m_COrt        = DKndInf1.m_COrt;
    DKndInf11.m_CPlz        = DKndInf1.m_CPlz;
    DKndInf11.m_CStrasse    = DKndInf1.m_CStrasse;
    DKndInf11.m_CTeleKw     = DKndInf1.m_CTeleKw;
    DKndInf11.m_CTeleNr     = DKndInf1.m_CTeleNr;
    DKndInf11.m_CAbc        = DKndInf1.m_CAbc;

    //Einstellung Daten 1. Dialog
    DKndInf1.m_dLinefee     = kndinf.s.LINEFEE;
    DKndInf1.m_dPackagefee  = kndinf.s.PACKAGEFEE;
    DKndInf1.m_cSendcollectivinvoice[0] = kndinf.s.SENDCOLLECTIVINVOICE[0];

    DKndInf1.m_OrgFili      = kndinf.s.ORIGINALFILIALNR;
    DKndInf1.m_TMZeit       = tm.s;
    DKndInf1.m_CFaxNr       = kndausku.s.FAXNR;
    DKndInf1.m_CImsKreis.Format("%07ld / %09ld", kndausku.s.IMSBEZIRKNR, kndausku.s.IMS3000);
    DKndInf1.m_CTeleNrDafue = kndausku.s.TELNRDAFUE;
    DKndInf1.m_CVb1.Format("%ld", kndausku.s.PERSONALNRVERTR);
    DKndInf1.m_CVb2.Format("%ld", kndausku.s.VERTRETER_2);
    sprintf(str, "%.2lf %s", kndausku.s.VERSAND_KOSTEN,CResString::ex().getStrTblText(AETXT_DM).GetString());
    DKndInf1.m_CVersandKosten = str;
    DKndInf1.m_CEilGebuehr = AllgDoubleToDMText(kndausku.s.EILBOTENZUSCHLAG, str, (char*)CResString::ex().getStrTblText(AETXT_DM).GetString());
    if (GetAeUser().IsErwKndInfo())
        DKndInf1.m_CLfdUms = AllgDoubleToDMText(kndausku.s.MONATSUMSATZ, str, (char*)CResString::ex().getStrTblText(AETXT_DM).GetString());
    else
        DKndInf1.m_CLfdUms = "********";
    sprintf(str, "%.2lf %%", kndausku.s.MALUSFREI_PROZ);
    DKndInf1.m_CPhonoMalus = str;
    DKndInf1.m_dLog = kndausku.s.LOGISTIKAUFSCHLAG;
    DKndInf1.m_CLog.Format("%.2lf %%", kndausku.s.LOGISTIKAUFSCHLAG);
    strcpy(DKndInf1.m_Schwerpunkt1, kndausku.s.SKDSCHWERPUNKT1);
    strcpy(DKndInf1.m_Schwerpunkt2, kndausku.s.SKDSCHWERPUNKT2);
    strcpy(DKndInf1.m_Schwerpunkt3, kndausku.s.SKDSCHWERPUNKT3);
    strcpy(DKndInf1.m_Schwerpunkt4, kndausku.s.SKDSCHWERPUNKT4);
    strcpy(DKndInf1.m_Schwerpunkt5, kndausku.s.SKDSCHWERPUNKT5);
    strcpy(DKndInf1.m_Anrufgenerell, kndschalter.s.SKDANRUFGENERELL);
    strcpy(DKndInf1.m_AuftragZusammen, kndschalter.s.SKDAUFTRAGZUSAMMEN);
    strcpy(DKndInf1.m_Kritisch, kndausku.s.SKDKDKRITISCH);
    strcpy(DKndInf1.m_Vipkunde, kndausku.s.SKDVIPKUNDE);
    strcpy(DKndInf1.m_Midas, kndschalter.s.SKDMIDAS);
    strcpy(DKndInf1.m_RetailPermit, kndschalter.s.SKDRETAILPERMIT);
    DKndInf1.m_sMailB2SR = kndschalter.s.SKDMAILINVOICE;
    DKndInf1.m_sMailCDB = kndschalter.s.SKDMAILBATCHCHANGEADVICE;

    if      (!strcmp(kndinf.s.DAFUESYSTEM,"01")) cstr = "PARA";
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"02")) cstr = "SERA";
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"00")) cstr = "PHON";
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"04")) cstr = "XML ";
    else if (!strcmp(kndinf.s.DAFUESYSTEM,"03")) cstr = "MSV3";
    else                                    cstr = kndinf.s.DAFUESYSTEM;
    DKndInf1.m_CDfuArt = cstr;
    DKndInf1.m_CInfoPhono = kndinf.s.KUNDETEXT;
    DKndInf1.m_CInfoVersand = kndinf.s.BEMERKUNGEN;
    if (!strcmp(kndausku.s.SKDEILSPERRE, "1")) DKndInf1.m_CEilSperre = 'J';
    else                                DKndInf1.m_CEilSperre = 'N';
    sprintf(DKndInf1.m_CBasisNatrab.GetBuffer(20), "%d/%d", kndausku.s.MENGENATRABASIS, kndausku.s.MENGENATRA);
    DKndInf1.m_CBasisNatrab.ReleaseBuffer( );
    AllgBitleiste2Char((Bitleiste)kndausku.s.ETKDMERKMAL1, DKndInf1.m_Etkdmerkmal1);
    AllgBitleiste2Char((Bitleiste)kndausku.s.ETKDMERKMAL2, DKndInf1.m_Etkdmerkmal2);
    if (mcustomervacation.SelNextEffective() != 0 || mcustomervacation.GetDatumgueltigab() == 0)
    {
        DKndInf1.m_CUrlaub = CResString::ex().getStrTblText(AETXT_KEINER);
    }
    else
    {
        DKndInf1.m_CUrlaub = (CString)AllgDatumLong2CharTTMMJJJJ(mcustomervacation.GetDatumgueltigab(), str) + " - "
                           + (CString)AllgDatumLong2CharTTMMJJJJ(mcustomervacation.GetDatumgueltigbis(), str);
    }
    if (kndausku.s.KUNDE_SEIT == 0)
    {
        DKndInf1.m_CDatumNeu = "";
    }
    else
    {
        DKndInf1.m_CDatumNeu = (CString)AllgDatumLong2CharTTMMJJJJ(kndausku.s.KUNDE_SEIT,str);
    }
    char tagart[7];
    switch (tm.s.WTAG)
    {
    case 0 : strcpy(tagart, "SO"); break;
    case 1 : strcpy(tagart, "MO"); break;
    case 2 : strcpy(tagart, "DI"); break;
    case 3 : strcpy(tagart, "MI"); break;
    case 4 : strcpy(tagart, "DO"); break;
    case 5 : strcpy(tagart, "FR"); break;
    case 6 : strcpy(tagart, "SA"); break;
    }
    CKNDOFFEN kndoffen;
    kndoffen.s.IDFNR              = m_IdfNr;
    kndoffen.s.KUNDENNR           = m_KndNr;
    kndoffen.s.VERTRIEBSZENTRUMNR = m_VzNr;
    strcpy(kndoffen.s.TAGESTYP, tagart);
    kndoffen.Server(AakundeSel_offen);
    if ((kndoffen.s.ZEITBEGINAM == 0) && (kndoffen.s.ZEITENDEAM == 0))
    {
        DKndInf1.m_COffen1 = CResString::ex().getStrTblText(AETXT_KEINE);
    }
    else
    {
        if ((kndoffen.s.ZEITBEGINAM != 0) && (kndoffen.s.ZEITENDEAM != 0))
        {
            sprintf(DKndInf1.m_COffen1.GetBuffer(20), "%s - %s",
                HHmmStringFromTimeLong(kndoffen.s.ZEITBEGINAM),
                HHmmStringFromTimeLong(kndoffen.s.ZEITENDEAM));
        }
        else if (kndoffen.s.ZEITBEGINAM != 0)
        {
            sprintf(DKndInf1.m_COffen1.GetBuffer(20), "%s", HHmmStringFromTimeLong(kndoffen.s.ZEITBEGINAM));
        }
    }
    if ((kndoffen.s.ZEITBEGINPM == 0) && (kndoffen.s.ZEITENDEPM == 0))
    {
        DKndInf1.m_COffen2 = CResString::ex().getStrTblText(AETXT_KEINE);
    }
    else if ((kndoffen.s.ZEITBEGINAM != 0) && (kndoffen.s.ZEITENDEAM != 0))
    {
        sprintf(DKndInf1.m_COffen2.GetBuffer(20), "%s - %s",
            HHmmStringFromTimeLong(kndoffen.s.ZEITBEGINPM),
            HHmmStringFromTimeLong(kndoffen.s.ZEITENDEPM));
    }
    else if (kndoffen.s.ZEITENDEPM != 0)
    {
        sprintf(DKndInf1.m_COffen2.GetBuffer(20), "%s", HHmmStringFromTimeLong(kndoffen.s.ZEITENDEPM));
    }
    DKndInf1.m_COffen1.ReleaseBuffer();
    DKndInf1.m_COffen2.ReleaseBuffer();
    PSKndInf.AddPage(&DKndInf1);
    if (GetAeUser().IsErwKndInfo())
    {
        PSKndInf.AddPage(&DKndInf2);
    }
    PSKndInf.AddPage(&DKndInf3);
    PSKndInf.AddPage(&DKndInf4);
    PSKndInf.m_KettePage = -1;
    int kette = 3;
    //if (AeGetApp()->IsBG() || AeGetApp()->IsRS())
    if (GetAeUser().IsErwKndInfo())
    {
        PSKndInf.AddPage(&DKndInf5);
        ++kette;
    }
    if (AeGetApp()->IsBG() && (m_MainNr > 0))
    {
        ++kette;
        PSKndInf.AddPage(&DKndInf6);
        PSKndInf.m_KettePage = kette;
    }
    if (AeGetApp()->IsBG() && m_bKtoExist)
    {
        PSKndInf.AddPage(&DKndInf7);
    }
    if (AeGetApp()->IsBG())
    {
        PSKndInf.AddPage(&DKndInf8);
        PSKndInf.AddPage(&DKndInf9);
    }
    if (AeGetApp()->IsDE())
    {
        PSKndInf.AddPage(&DKndInf10);
    }
    PSKndInf.AddPage(&DKndInf11);
    return PSKndInf.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CPSKndInf

IMPLEMENT_DYNAMIC(CPSKndInf, CPropertySheetMultiLang)

CPSKndInf::CPSKndInf(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheetMultiLang(nIDCaption, pParentWnd, iSelectPage)
{
}

CPSKndInf::CPSKndInf(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheetMultiLang(pszCaption, pParentWnd, iSelectPage)
{
}

CPSKndInf::~CPSKndInf()
{
    AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf.cpp", "Deconstruct", "Dialog stopped");
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CPSKndInf::OnHookFkt(WPARAM wParam, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        if (m_KettePage < 0)
            return 1L;                      //Message wird nicht weitergeleitet

        CPropertyPage* active;
        CPropertyPage* wished;
        active = GetActivePage();
        wished = GetPage(m_KettePage);
        if (active == wished)
        {
            ((CDKndInf6*)GetActivePage())->OnHookFkt(wParam, lpMsg);
        }
        return 1L;                      //Message wird nicht weitergeleitet
    }
    return 0L;
}

BOOL CPSKndInf::OnInitDialog()
{
    BOOL bResult = CPropertySheetMultiLang::OnInitDialog();

    SetBtText(BT_OK, (char *)CResString::ex().getStrTblText(IDS_MSG_OK).GetString());
    SetBtText(BT_CANCEL, (char *)CResString::ex().getStrTblText(IDS_BT_CANCEL).GetString());
    SetBtText(BT_APPLY_NOW, (char *)CResString::ex().getStrTblText(AETXT_UEBERNEHM).GetString());

    return bResult;
}

BEGIN_MESSAGE_MAP(CPSKndInf, CPropertySheetMultiLang)
   ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPSKndInf message handlers

/////////////////////////////////////////////////////////////////////////////
// CDKndInf1 property page

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES SpaltenAufart[] =
{
    0,  "", 27, LVCFMT_LEFT,
    1,  "", 30, LVCFMT_RIGHT,
    2,  "", 26, LVCFMT_LEFT,
    3,  "", 20, LVCFMT_LEFT,
    4,  "", 20, LVCFMT_LEFT,
    5,  "", 20, LVCFMT_LEFT,
    6,  "", 20, LVCFMT_LEFT,
    7,  "", 20, LVCFMT_LEFT,
    8,  "", 20, LVCFMT_LEFT,
    -1, "",  0, 0
};

#define NUM_SPALT_AA 9

static COLUMNS_TYPES SpaltenTouren[] =
{
    0,  "", 53, LVCFMT_LEFT,
    1,  "", 30, LVCFMT_RIGHT,
    2,  "", 42, LVCFMT_LEFT,
    3,  "",  0, LVCFMT_LEFT,
    4,  "", 37, LVCFMT_RIGHT,
    5,  "", 26, LVCFMT_LEFT,
    6,  "", 32, LVCFMT_LEFT,
    7,  "", 32, LVCFMT_LEFT,
    8,  "", 50, LVCFMT_LEFT,
    -1, "",  0, 0
};

#define NUM_SPALT_TOUR 9

static COLUMNS_TYPES SpaltenRufe[] =
{
    0,  "", 38, LVCFMT_LEFT,
    1,  "", 42, LVCFMT_RIGHT,
    2,  "", 28, LVCFMT_RIGHT,
    3,  "", 57, LVCFMT_RIGHT,
    -1, "",  0, 0
};

#define NUM_SPALT_RUFE 4

static COLUMNS_TYPES SpaltenEKGruppe[] =
{
    0,  "",  25, LVCFMT_LEFT,
    1,  "",  35, LVCFMT_LEFT,
    2,  "", 240, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_EK_GRUPPE 3

IMPLEMENT_DYNCREATE(CDKndInf1, CPropertyPageMultiLang)

CDKndInf1::CDKndInf1() : CPropertyPageMultiLang(CDKndInf1::IDD)
, m_CLog(_T(""))
{
    m_CApoName = _T("");
    m_CBasisNatrab = _T("");
    m_CDatumNeu = _T("");
    m_CEilGebuehr = _T("");
    m_CEilSperre = _T("");
    m_CIdfNummer = _T("");
    m_CImsKreis = _T("");
    m_CInfo = _T("");
    m_CInfoPhono = _T("");
    m_CInfoPhono2 = _T("");
    m_CInfoPhono3 = _T("");
    m_CInfoVersand = _T("");
    m_CInfoVersand2 = _T("");
    m_CKundeName = _T("");
    m_CLfdUms = _T("");
    m_COffen1 = _T("");
    m_COffen2 = _T("");
    m_COrt = _T("");
    m_CPhonoMalus = _T("");
    m_CPlz = _T("");
    m_CStrasse = _T("");
    m_CTeleKw = _T("");
    m_CTeleNr = _T("");
    m_CTeleNrDafue = _T("");
    m_CTeleNr2 = _T("");
    m_CUrlaub = _T("");
    m_CVb = _T("");
    m_CVb1 = _T("");
    m_CVb2 = _T("");
    m_CVersandKosten = _T("");
    m_CFaxNr = _T("");
    m_CVerbund = _T("");
    m_CDfuArt = _T("");
    m_CAbc = _T("");
    m_CEmail = _T("");
    m_init = FALSE;
    m_sMailB2SR = 0;
    m_sMailCDB = 0;
    m_dLinefee = 0.0;
    m_dPackagefee = 0.0;
    m_cSendcollectivinvoice[0] = ' ';
    m_bCall = false;

    SpaltenAufart[0].Columns = CResString::ex().getStrTblText(AETXT_KZ_AUFTRAGSART);
    SpaltenAufart[1].Columns = CResString::ex().getStrTblText(AETXT_KURZ_VALUTA);
    SpaltenAufart[2].Columns = CResString::ex().getStrTblText(AETXT_KURZ_VALUTAAUTO);
    SpaltenAufart[3].Columns = CResString::ex().getStrTblText(AETXT_KZ_NATRA);
    SpaltenAufart[4].Columns = CResString::ex().getStrTblText(AETXT_KZ_NETTO);
    SpaltenAufart[5].Columns = CResString::ex().getStrTblText(AETXT_KZ_BASIS_NATRA);
    SpaltenAufart[6].Columns = CResString::ex().getStrTblText(AETXT_KZ_MONRAB);
    SpaltenAufart[7].Columns = CResString::ex().getStrTblText(AETXT_KZ_VERBUNDSPERRE);
    SpaltenAufart[8].Columns = CResString::ex().getStrTblText(AETXT_KZ_VALUTASPERRE);

    SpaltenTouren[0].Columns = CResString::ex().getStrTblText(AETXT_KURZ_TOUR_ID);
    SpaltenTouren[1].Columns = CResString::ex().getStrTblText(AETXT_KURZ_FOLGE);
    SpaltenTouren[2].Columns = CResString::ex().getStrTblText(IDS_TIME);
    SpaltenTouren[3].Columns = CResString::ex().getStrTblText(AETXT_DELAY);
    SpaltenTouren[4].Columns = CResString::ex().getStrTblText(AETXT_DEC);
    SpaltenTouren[5].Columns = CResString::ex().getStrTblText(AETXT_VB);
    SpaltenTouren[6].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    SpaltenTouren[7].Columns = CResString::ex().getStrTblText(AETXT_RT);
    SpaltenTouren[8].Columns = CResString::ex().getStrTblText(AETXT_KIPPZEIT);

    SpaltenRufe[0].Columns = CResString::ex().getStrTblText(IDS_TIME);
    SpaltenRufe[1].Columns = CResString::ex().getStrTblText(AETXT_ART);
    SpaltenRufe[2].Columns = CResString::ex().getStrTblText(AETXT_ND);
    SpaltenRufe[3].Columns = CResString::ex().getStrTblText(AETXT_TOURID);

    SpaltenEKGruppe[0].Columns = CResString::ex().getStrTblText(AETXT_SHORT_PR);
    SpaltenEKGruppe[1].Columns = CResString::ex().getStrTblText(AETXT_EK_GRP);
    SpaltenEKGruppe[2].Columns = CResString::ex().getStrTblText(AETXT_EK_GRP);
}

CDKndInf1::~CDKndInf1()
{
}

void CDKndInf1::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_KA_INFO, m_ListInfo);
    DDX_Control(pDX, IDC_KA_VB, m_ListVb);
    DDX_Control(pDX, IDC_LIST_TOUR, m_ListTour);
    DDX_Control(pDX, IDC_LIST_RUFE, m_ListRufe);
    DDX_Control(pDX, IDC_LIST_AUFARTEN, m_ListAufarten);
    DDX_Text(pDX, IDC_KA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_KA_BASIS_NATRAB, m_CBasisNatrab);
    DDX_Text(pDX, IDC_KA_DATUM_NEU, m_CDatumNeu);
    DDX_Text(pDX, IDC_KA_EIL_GEBUEHR, m_CEilGebuehr);
    DDX_Text(pDX, IDC_KA_EIL_SPERRE, m_CEilSperre);
    DDX_Text(pDX, IDC_KA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_KA_IMS_KREIS, m_CImsKreis);
    DDX_LBString(pDX, IDC_KA_INFO, m_CInfo);
    DDX_Text(pDX, IDC_KA_INFO_PHONO, m_CInfoPhono);
    DDX_Text(pDX, IDC_KA_INFO_PHONO2, m_CInfoPhono2);
    DDX_Text(pDX, IDC_KA_INFO_PHONO3, m_CInfoPhono3);
    DDX_Text(pDX, IDC_KA_INFO_VERSAND, m_CInfoVersand);
    DDX_Text(pDX, IDC_KA_INFO_VERSAND2, m_CInfoVersand2);
    DDX_Text(pDX, IDC_KA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_KA_LFD_UMS, m_CLfdUms);
    DDX_Text(pDX, IDC_KA_OFFEN1, m_COffen1);
    DDX_Text(pDX, IDC_KA_OFFEN2, m_COffen2);
    DDX_Text(pDX, IDC_KA_ORT, m_COrt);
    DDX_Text(pDX, IDC_KA_PHONO_MALUS, m_CPhonoMalus);
    DDX_Text(pDX, IDC_KA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_KA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_KA_TELE_KW, m_CTeleKw);
    DDX_Text(pDX, IDC_KA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_KA_TELE_NR_DAFUE, m_CTeleNrDafue);
    DDX_Text(pDX, IDC_KA_TELE_NR2, m_CTeleNr2);
    DDX_Text(pDX, IDC_KA_URLAUB, m_CUrlaub);
    DDX_LBString(pDX, IDC_KA_VB, m_CVb);
    DDX_Text(pDX, IDC_KA_VB1, m_CVb1);
    DDX_Text(pDX, IDC_KA_VB2, m_CVb2);
    DDX_Text(pDX, IDC_KA_VERSAND_KOSTEN, m_CVersandKosten);
    DDX_Text(pDX, IDC_KA_FAX_NR, m_CFaxNr);
    DDX_Text(pDX, IDC_KA_VERBUND, m_CVerbund);
    DDX_Text(pDX, IDC_KA_DFU_ART, m_CDfuArt);
    DDX_Text(pDX, IDC_STATIC_ABC, m_CAbc);
    DDX_Control(pDX, IDC_LIST_EK_GRUPPE, m_ListEKGruppe);
    DDX_Text(pDX, IDC_ST_LOG, m_CLog);
}

BOOL CDKndInf1::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

BOOL CDKndInf1::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();

    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf1.cpp", "OnSetActive", "Page started");
        CPHARMGRP pharmgrp;
        m_init = TRUE;
        CString Wert;
        char error_msg[81];
        ppString text;
        int rc;

        if (m_dLinefee > 0)
        {
            GetDlgItem(IDC_STATIC_LINEFEE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_LINEFEE)->EnableWindow(TRUE);
            GetDlgItem(IDC_ST_LINEFEE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_ST_LINEFEE)->EnableWindow(TRUE);
            Wert.Format("%0.2f", m_dLinefee);
            GetDlgItem(IDC_ST_LINEFEE)->SetWindowTextA(Wert);
        }
        if (m_dPackagefee > 0)
        {
            GetDlgItem(IDC_STATIC_PACKAGEFEE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_PACKAGEFEE)->EnableWindow(TRUE);
            GetDlgItem(IDC_ST_PACKAGEFEE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_ST_PACKAGEFEE)->EnableWindow(TRUE);
            Wert.Format("%0.2f", m_dPackagefee);
            GetDlgItem(IDC_ST_PACKAGEFEE)->SetWindowTextA(Wert);
        }
        if (m_cSendcollectivinvoice[0] == 'P')
        {
            GetDlgItem(IDC_STATIC_SAMMELRECHNUG_PORTAL)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_SAMMELRECHNUG_PORTAL)->EnableWindow(TRUE);
        }
        if (m_sMailB2SR == 1)
        {
            GetDlgItem(IDC_STATIC_MAIL_BELEG)->ShowWindow(SW_SHOW);;
        }
        if (m_sMailCDB == 1)
        {
            GetDlgItem(IDC_STATIC_MAIL_BELEG2)->ShowWindow(SW_SHOW);;
        }
        if (AeGetApp()->IsHR())
        {
            if (m_Schwerpunkt2[0] == '1')
            {
                GetDlgItem(IDC_STATIC_ERACUN)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_ERACUN)->EnableWindow(TRUE);
            }
            else
            {
                GetDlgItem(IDC_STATIC_ERACUN)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_STATIC_ERACUN)->EnableWindow(FALSE);
            }
        }

        if (!m_CEmail.IsEmpty() && (AeGetApp()->IsDE() || AeGetApp()->IsCH()))
        {
            GetDlgItem(IDC_BUTTON_MAIL)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_BUTTON_MAIL)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_MAIL)->SetWindowText(m_CEmail);
        }
        if (AeGetApp()->m_ProCenter.IsHiPathLogon())
        {
            GetDlgItem(IDC_BUTTON_CALL)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_BUTTON_CALL)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANRUFEN));
        }
        if (m_dLog == 0)
        {
            GetDlgItem(IDC_STATIC_LOG)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_ST_LOG)->ShowWindow(SW_HIDE);
        }
        else
        {
            GetDlgItem(IDC_STATIC_LOG)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_ST_LOG)->ShowWindow(SW_SHOW);
        }
        if (strcmp(m_AuftragZusammen, "1"))
            GetDlgItem(IDC_STATIC_AUFTRAG_ZUSAMMEN)->ShowWindow(SW_HIDE);
        if (strcmp(m_Anrufgenerell, "1"))
            GetDlgItem(IDC_STATIC_RUF_GENERELL)->ShowWindow(SW_HIDE);
        if (!strcmp(m_Schwerpunkt1, "1")) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_HOME_CARE));
        if (!strcmp(m_Schwerpunkt2, "1")) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_POOL_KUNDE));
        if (!strcmp(m_Schwerpunkt3, "1")) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_ARB_KREIS_AKTUELL));
        if (!strcmp(m_Schwerpunkt4, "1")) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_TEAM_KUNDE));
        if (!strcmp(m_Schwerpunkt5, "1")) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_DIABETES));
        if (!strcmp(m_Kritisch, "1")) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_KRITISCH));
        if (!strcmp(m_Vipkunde, "1")) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_VIP_KUNDE));
        if (!strcmp(m_Midas, "1")) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_MIDAS));
        if (!strcmp(m_RetailPermit, "1")) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_RETAILPERMIT));
        if (m_KzAeGesperrt) m_ListInfo.AddString(CResString::ex().getStrTblText(AETXT_ART_GESPERRT));
        if (m_Etkdmerkmal1[8] == '1') m_ListVb.AddString(CResString::ex().getStrTblText(AETXT_ALLGEMEIN));
        if (m_Etkdmerkmal1[12] == '1') m_ListVb.AddString(CResString::ex().getStrTblText(AETXT_VICHY));
        if (m_Etkdmerkmal1[13] == '1') m_ListVb.AddString(CResString::ex().getStrTblText(AETXT_BOUHON));
        if (m_Etkdmerkmal1[14] == '1') m_ListVb.AddString(CResString::ex().getStrTblText(AETXT_POOL));
        if (m_Etkdmerkmal1[15] == '1') m_ListVb.AddString(CResString::ex().getStrTblText(AETXT_BUECHER));

        if (!CListCtrlHelper::AddColumns(SpaltenAufart, m_ListAufarten)
            || !CListCtrlHelper::AddColumns(SpaltenTouren, m_ListTour)
            || !CListCtrlHelper::AddColumns(SpaltenRufe, m_ListRufe)
            || !CListCtrlHelper::AddColumns(SpaltenEKGruppe, m_ListEKGruppe))
        {
            return FALSE;
        }

        if (AeGetApp()->IsDE())
        {
            m_ListTour.SetColumnWidth(3, 240);
        }

        {
            // Ausgabe der Listbox fuer Auftragsarten
            CStringArray s;
            s.SetSize(NUM_SPALT_AA);
            CKNDAUFART kndaufart;
            kndaufart.s.IDFNR = m_IdfNr;
            kndaufart.s.KUNDENNR = m_KndNr;
            kndaufart.s.VERTRIEBSZENTRUMNR = m_VzNr;
            kndaufart.s.FETCH_REL = 1;          //normaler Fetch
            CTime Jetzt;
            Jetzt.GetCurrentTime();
            BeginWaitCursor();
            for (;;)
            {
                kndaufart.Server(AakundeSel_aufart);
                if (kndaufart.rc == SRV_SQLNOTFOUND)
                    break;
                else if (kndaufart.rc < SRV_OK)
                {
                    EndWaitCursor();
                    return FALSE;
                }
                //Ausgabe in die Listbox
                CString CStr;
                s[0] = kndaufart.s.KDAUFTRAGART;
                if (kndaufart.s.VALUTAMONATE > 0)
                {
                    if (AeGetApp()->IsRS())
                    {
                        long ltag;
                        long lmonat;
                        long ljahr;
                        ltag = Jetzt.GetDay();
                        lmonat = Jetzt.GetMonth();
                        ljahr = Jetzt.GetYear();
                        lmonat += kndaufart.s.VALUTAMONATE;
                        if (lmonat > 12)
                        {
                            ljahr += 1;
                            lmonat -= 12;
                        }
                        else if (lmonat < 1)
                        {
                            ljahr -= 1;
                            lmonat += 12;
                        }
                        CTime Valutadatum(ljahr, lmonat, ltag, 0, 0, 0);
                        CTimeSpan Spanne = Valutadatum - Jetzt;
                        // in BG und RS Valuta in Tagen
                        CStr.Format("%d", Spanne.GetDays());
                    }
                    else
                    {
                        CStr.Format("%d", kndaufart.s.VALUTAMONATE);
                    }
                }
                else
                {
                    CStr.Format("%d", kndaufart.s.VALUTAMONATE);
                }
                s[1] = CStr;
                CStr.Format("%d", kndaufart.s.VALUTAMONAUTO);
                s[2] = CStr;
                s[3] = kndaufart.s.SKDAUFTRAGARTNATRA[0] == '1' ? CResString::ex().getStrTblText(AETXT_KZ_JA) : CResString::ex().getStrTblText(AETXT_KZ_NEIN);
                s[4] = kndaufart.s.SKDAUFTRAGARTNETTO[0] == '1' ? CResString::ex().getStrTblText(AETXT_KZ_JA) : CResString::ex().getStrTblText(AETXT_KZ_NEIN);
                s[5] = kndaufart.s.SKDAUFTRAGARTBANR[0] == '1' ? CResString::ex().getStrTblText(AETXT_KZ_JA) : CResString::ex().getStrTblText(AETXT_KZ_NEIN);
                s[6] = kndaufart.s.SKDAUFTRAGARTMONAT[0] == '1' ? CResString::ex().getStrTblText(AETXT_KZ_JA) : CResString::ex().getStrTblText(AETXT_KZ_NEIN);
                s[7] = kndaufart.s.SKDAUFTRAGVERBUND[0] == '1' ? CResString::ex().getStrTblText(AETXT_KZ_JA) : CResString::ex().getStrTblText(AETXT_KZ_NEIN);
                s[8] = kndaufart.s.SKDAUFTRAGARTVALS[0] == '1' ? CResString::ex().getStrTblText(AETXT_KZ_JA) : CResString::ex().getStrTblText(AETXT_KZ_NEIN);

                if (!CListCtrlHelper::AppendItem(m_ListAufarten, NUM_SPALT_AA, s))
                {
                    EndWaitCursor();
                    return FALSE;
                }
            }
            kndaufart.s.FETCH_REL = 0;          //Close Cursor
            kndaufart.Server(AakundeSel_aufart);
            CListCtrlHelper::SetFocusSelectedFocused(m_ListAufarten, 0);
            EndWaitCursor();
        } //end aufarten

        {
            // Ausgabe der Listbox fuer Kundenanrufe
            char str[81];
            CStringArray s;
            CString CStr;
            s.SetSize(NUM_SPALT_RUFE);
            CRUFPMASTER rufpmaster;
            //rufpmaster.s.FILIALNR = AeGetApp()->FilialNrActual();
            //rufpmaster.s.IDFNR             = m_IdfNr;
            //rufpmaster.s.KUNDENNR          = m_KndNr;
            //rufpmaster.s.VERTRIEBSZENTRUMNR = m_VzNr;
            rufpmaster.s.FILIALNR = m_VzNr;
            rufpmaster.s.IDFNR = m_KndNr;
            rufpmaster.s.FETCH_REL = 1;      //normaler Fetch
            BeginWaitCursor();
            for (;;)
            {
                //nase ersetzen durch
                //m_pCallPlan = new ppCustomerCallPlanDay(*pCallPlan);

                rufpmaster.Server(AaplanSel_mplan_idf);
                if (rufpmaster.rc == SRV_SQLNOTFOUND)
                    break;
                else if (rufpmaster.rc < SRV_OK)
                {
                    EndWaitCursor();
                    return FALSE;
                }
                if (m_TMZeit.WTAG == ALLG_SONNTAG && rufpmaster.s.AKTIVSONNTAG[0] != '1') continue;
                if (m_TMZeit.WTAG == ALLG_MONTAG && rufpmaster.s.AKTIVMONTAG[0] != '1') continue;
                if (m_TMZeit.WTAG == ALLG_DIENSTAG && rufpmaster.s.AKTIVDIENSTAG[0] != '1') continue;
                if (m_TMZeit.WTAG == ALLG_MITTWOCH && rufpmaster.s.AKTIVMITTWOCH[0] != '1') continue;
                if (m_TMZeit.WTAG == ALLG_DONNERSTAG && rufpmaster.s.AKTIVDONNERSTAG[0] != '1') continue;
                if (m_TMZeit.WTAG == ALLG_FREITAG && rufpmaster.s.AKTIVFREITAG[0] != '1') continue;
                if (m_TMZeit.WTAG == ALLG_SONNABEND && rufpmaster.s.AKTIVSAMSTAG[0] != '1') continue;
                //Ausgabe in die Listbox
                sprintf(str, "%02d:%02d", rufpmaster.s.RUFZEIT / 100, rufpmaster.s.RUFZEIT % 100);
                s[0] = str;
                if      (rufpmaster.s.PROTOKOLLART[0] == PLAN_DAFUE_PARA) s[1] = CResString::ex().getStrTblText(AETXT_PARA);
                else if (rufpmaster.s.PROTOKOLLART[0] == PLAN_DAFUE_SERA) s[1] = CResString::ex().getStrTblText(AETXT_SERA);
                else if (rufpmaster.s.PROTOKOLLART[0] == PLAN_PHONETIK)   s[1] = CResString::ex().getStrTblText(AETXT_PHON);
                else if (rufpmaster.s.PROTOKOLLART[0] == PLAN_DAFUE_AUTO) s[1] = CResString::ex().getStrTblText(AETXT_AUTO);
                else                                             s[1] = "";
                s[2] = rufpmaster.s.VERARBEITUNGART[0] == '1' ? 'X' : ' ';
                AllgEntfSpaces(rufpmaster.s.TOURID);
                if (strlen(rufpmaster.s.TOURID) == 0)
                {
                    CStr.Empty();
                }
                else
                {
                    CStr.Format("%.2s:%.2s/%.2s", rufpmaster.s.TOURID, rufpmaster.s.TOURID + 2, rufpmaster.s.TOURID + 4);
                }
                s[3] = CStr;

                if (!CListCtrlHelper::AppendItem(m_ListRufe, NUM_SPALT_RUFE, s))
                {
                    EndWaitCursor();
                    return FALSE;
                }
            }
            rufpmaster.s.FETCH_REL = 0;          //Close Cursor
            rufpmaster.Server(AaplanSel_mplan_idf);
            CListCtrlHelper::SetItemStateSelectedFocused(m_ListRufe, 0);
            EndWaitCursor();
        } //end rufe

        {
            // Ausgabe der Listbox fuer Touren
            char str[81];
            long rufzeit, ankunftzeit, fahrzeit;
            CString CStr;
            CStringArray s;
            s.SetSize(NUM_SPALT_TOUR);
            CKNDTOUREN kndtouren;
            CTOURDELAY tourdelay;
            kndtouren.s.IDFNR = m_IdfNr;
            kndtouren.s.KUNDENNR = m_KndNr;
            kndtouren.s.VERTRIEBSZENTRUMNR = m_VzNr;
            kndtouren.s.FETCH_REL = 1;          //normaler Fetch
            BeginWaitCursor();
            for (;;)
            {
                kndtouren.Server(AakundeSel_touren);
                if (kndtouren.rc == SRV_SQLNOTFOUND)
                    break;
                else if (kndtouren.rc < SRV_OK)
                {
                    EndWaitCursor();
                    return FALSE;
                }
                //Ausgabe in die Listbox
                CStr.Format("%.2s:%.2s/%.2s", kndtouren.s.TOURID, kndtouren.s.TOURID + 2, kndtouren.s.TOURID + 4);
                s[0] = CStr;
                sprintf(str, "%d", kndtouren.s.REIHENFOLGENR);
                s[1] = str;
                CStr.Format("%.4s", kndtouren.s.TOURID);
                rufzeit = atol(CStr);
                for (;;)
                {
                    if (rufzeit > 2400) rufzeit -= 2400;
                    else break;
                }
                fahrzeit = (kndtouren.s.FAHRTZEIT / 60 * 100 + kndtouren.s.FAHRTZEIT % 60) * 100;
                AllgAddTime((rufzeit * 100), fahrzeit, &ankunftzeit);
                ankunftzeit = ankunftzeit / 100;
                for (;;)
                {
                    if (ankunftzeit > 2400) ankunftzeit -= 2400;
                    else break;
                }
                sprintf(str, "% 2d:%02d", ankunftzeit / 100, ankunftzeit % 100);
                s[2] = str;

                s[3].Empty();
                if (AeGetApp()->IsDE())
                {
                    //Tourverspätung
                    tourdelay.SetVertriebszentrumnr(kndtouren.s.VERTRIEBSZENTRUMNR);
                    tourdelay.SetKundennr(kndtouren.s.KUNDENNR);
                    tourdelay.SetTourid(kndtouren.s.TOURID);
                    tourdelay.SetDatumkommi(kndtouren.s.DATUMVERSAND);
                    tourdelay.SetKdauftragnr(0);
                    rc = ::ServerNr(PIPE_AE_SRV, AasrvSelTourDelay, (void*)&tourdelay.s, TOURDELAY_BES, TOURDELAY_ANZ, error_msg);
                    if (rc < SRV_OK)
                    {
                        FehlerBehandlung(rc, error_msg);
                        s[3].Empty();
                    }
                    if (rc == SRV_SQLNOTFOUND)    //Kein ETA-Eintrag
                    {
                        s[3].Empty();
                    }
                    else
                    {
                        tourdelay.GetDelaytext(text);
                        s[3].Format(text, CResString::ex().getStrTblText(AETXT_DELAY_TEXT).GetString());
                    }
                }

                sprintf(str, "%ld", kndtouren.s.LAGRECHTOUR);
                s[4] = str;
                if (kndtouren.s.ISTVERBUNDTOUR[0] == '1')
                    s[5] = CResString::ex().getStrTblText(AETXT_KZ_JA);
                else s[5] = " ";
                s[6] = kndtouren.s.KDAUFTRAGART;
                if (kndtouren.s.RETURNSTOUR == 1)
                    s[7] = CResString::ex().getStrTblText(AETXT_KZ_JA);
                else s[7] = " ";
                sprintf(str, "%d", kndtouren.s.KIPPZEIT);
                s[8] = str;

                if (!CListCtrlHelper::AppendItem(m_ListTour, NUM_SPALT_TOUR, s))
                {
                    EndWaitCursor();
                    return FALSE;
                }
            }
            kndtouren.s.FETCH_REL = 0;          //Close Cursor
            kndtouren.Server(AakundeSel_touren);
            if (AeGetApp()->IsNewSuivra())
            {
                if (m_OrgFili > 0)
                {
                    if (m_OrgFili != m_VzNr)
                    {
                        CVERBUNDIDF verbundidf;
                        verbundidf.SetFilialnr(m_OrgFili);
                        if (!verbundidf.SelVBIdf())
                        {
                            kndtouren.s.IDFNR = verbundidf.GetBganr_ek();
                            kndtouren.s.KUNDENNR = verbundidf.GetBganr_ek();
                            kndtouren.s.VERTRIEBSZENTRUMNR = m_VzNr;
                            kndtouren.s.FETCH_REL = 1;          //normaler Fetch
                            BeginWaitCursor();
                            for (;;)
                            {
                                kndtouren.Server(AakundeSel_touren);
                                if (kndtouren.rc == SRV_SQLNOTFOUND)
                                    break;
                                else if (kndtouren.rc < SRV_OK)
                                {
                                    EndWaitCursor();
                                    return FALSE;
                                }
                                //Ausgabe in die Listbox
                                CStr.Format("%.2s:%.2s/%.2s", kndtouren.s.TOURID, kndtouren.s.TOURID + 2, kndtouren.s.TOURID + 4);
                                s[0] = CStr;
                                sprintf(str, "%d", kndtouren.s.REIHENFOLGENR);
                                s[1] = str;
                                CStr.Format("%.4s", kndtouren.s.TOURID);
                                rufzeit = atol(CStr);
                                fahrzeit = (kndtouren.s.FAHRTZEIT / 60 * 100 + kndtouren.s.FAHRTZEIT % 60) * 100;
                                AllgAddTime((rufzeit * 100), fahrzeit, &ankunftzeit);
                                if ((ankunftzeit = ankunftzeit / 100) > 4700)
                                    sprintf(str, "24:00");
                                else
                                    sprintf(str, "% 2d:%02d", ankunftzeit / 100, ankunftzeit % 100);
                                s[2] = str;
                                sprintf(str, "%ld", kndtouren.s.LAGRECHTOUR);
                                s[3] = str;
                                s[4].Format("%d", m_OrgFili);

                                if (!CListCtrlHelper::AppendItem(m_ListTour, NUM_SPALT_TOUR, s))
                                {
                                    EndWaitCursor();
                                    return FALSE;
                                }
                            }
                            kndtouren.s.FETCH_REL = 0;          //Close Cursor
                            kndtouren.Server(AakundeSel_touren);
                        }
                    }
                }
            }
            CListCtrlHelper::SetItemStateSelectedFocused(m_ListTour, 0);
            EndWaitCursor();
        } //end touren
        {
            // Ausgabe der Listbox fuer Einkaufsgruppen
            ppString cGroup;
            ppString GrpName;
            CStringArray s;
            s.SetSize(NUM_SPALT_EK_GRUPPE);
            CCUSTPHARMA custpharma;
            custpharma.SetCustomerno(m_KndNr);
            custpharma.SetBranchno(m_VzNr);
            BeginWaitCursor();
            for (;;)
            {
                custpharma.SelList();
                if (custpharma.rc == SRV_SQLNOTFOUND)
                    break;
                else if (custpharma.rc < SRV_OK)
                {
                    EndWaitCursor();
                    return FALSE;
                }
                //Ausgabe in die Listbox
                s[0].Format("%d", custpharma.GetRanking());
                pharmgrp.SetPharmacygroupid(custpharma.GetPharmacygroupid(cGroup));
                pharmgrp.SetBranchno(m_VzNr);
                s[1] = custpharma.GetPharmacygroupid(cGroup);
                if (!pharmgrp.Sel())
                    s[2] = pharmgrp.GetGroup_name(GrpName);
                else
                    s[2].Empty();

                if (!CListCtrlHelper::AppendItem(m_ListEKGruppe, NUM_SPALT_EK_GRUPPE, s))
                {
                    EndWaitCursor();
                    return FALSE;
                }
            }
            custpharma.CloseCursor();
            CListCtrlHelper::SetItemStateSelectedFocused(m_ListEKGruppe, 0);
            EndWaitCursor();
        } //end Einkaufsgruppen
    } //ende init
    return TRUE;
}

void CDKndInf1::OnButtonMail()
{
    CString MailKopfDaten;
    MailKopfDaten.Format("mailto:%s", m_CEmail.GetString());
    ShellExecute(this->GetSafeHwnd(),"open",MailKopfDaten,NULL,NULL,SW_SHOW);
}

void CDKndInf1::OnButtonCall()
{
    if (m_bCall)
    {
        AeGetApp()->m_ProCenter.DisconnectCall();
        GetDlgItem(IDC_BUTTON_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANRUFEN));
        m_bCall = false;
    }
    else
    {
        CString cTelNr = m_CTeleNr;
        if (cTelNr.IsEmpty())
        {
            CDHPMakeCall dlgHPMakeCall;
            if (dlgHPMakeCall.DoModal() == IDOK)
            {
                cTelNr = dlgHPMakeCall.m_csTelNr;
            }
            else
                return;
        }
        cTelNr = '0' + cTelNr;
        cTelNr.TrimRight();
        AeGetApp()->m_ProCenter.MakeCall(cTelNr);
        GetDlgItem(IDC_BUTTON_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_AUFLEGEN));
        m_bCall = true;
    }
}

HBRUSH CDKndInf1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPageMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
    if (m_KzAeGesperrt)
    {
        if (pWnd->GetDlgCtrlID() == IDC_KA_KUNDE_NAME)
            pDC->SetTextColor(RGB(200, 0, 0));
    }
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_AUFTRAG_ZUSAMMEN)
        pDC->SetTextColor(RGB(49, 142, 96));
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_MAIL_BELEG)
        pDC->SetTextColor(RGB(49, 142, 96));
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_MAIL_BELEG2)
        pDC->SetTextColor(RGB(49, 142, 96));
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_ERACUN)
        pDC->SetTextColor(RGB(200, 0, 0));
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_SAMMELRECHNUG_PORTAL)
        pDC->SetTextColor(RGB(0, 0, 200));

    return hbr;
}

BEGIN_MESSAGE_MAP(CDKndInf1, CPropertyPageMultiLang)
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BUTTON_MAIL, OnButtonMail)
    ON_BN_CLICKED(IDC_BUTTON_CALL, OnButtonCall)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDKndInf1 message handlers
/////////////////////////////////////////////////////////////////////////////
// CDKndInf2 property page

IMPLEMENT_DYNCREATE(CDKndInf2, CPropertyPageMultiLang)

CDKndInf2::CDKndInf2() : CPropertyPageMultiLang(CDKndInf2::IDD)
{
    m_CApoName = _T("");
    m_CIdfNummer = _T("");
    m_CKundeName = _T("");
    m_COrt = _T("");
    m_CPlz = _T("");
    m_CStrasse = _T("");
    m_CTeleKw = _T("");
    m_CTeleNr = _T("");
    m_CUmsatz = _T("");
    m_CWert1 = _T("");
    m_CWert10 = _T("");
    m_CWert11 = _T("");
    m_CWert12 = _T("");
    m_CWert2 = _T("");
    m_CWert3 = _T("");
    m_CWert4 = _T("");
    m_CWert5 = _T("");
    m_CWert6 = _T("");
    m_CWert7 = _T("");
    m_CWert8 = _T("");
    m_CWert9 = _T("");
    m_CMonat1 = _T("");
    m_CMonat10 = _T("");
    m_CMonat11 = _T("");
    m_CMonat12 = _T("");
    m_CMonat2 = _T("");
    m_CMonat3 = _T("");
    m_CMonat4 = _T("");
    m_CMonat5 = _T("");
    m_CMonat6 = _T("");
    m_CMonat7 = _T("");
    m_CMonat8 = _T("");
    m_CMonat9 = _T("");
    m_CAbc = _T("");
    m_init = FALSE;
    m_pstr[0] = &m_CWert1;
    m_pstr[1] = &m_CWert2;
    m_pstr[2] = &m_CWert3;
    m_pstr[3] = &m_CWert4;
    m_pstr[4] = &m_CWert5;
    m_pstr[5] = &m_CWert6;
    m_pstr[6] = &m_CWert7;
    m_pstr[7] = &m_CWert8;
    m_pstr[8] = &m_CWert9;
    m_pstr[9] = &m_CWert10;
    m_pstr[10] = &m_CWert11;
    m_pstr[11] = &m_CWert12;
    m_pmon[0] = &m_CMonat1;
    m_pmon[1] = &m_CMonat2;
    m_pmon[2] = &m_CMonat3;
    m_pmon[3] = &m_CMonat4;
    m_pmon[4] = &m_CMonat5;
    m_pmon[5] = &m_CMonat6;
    m_pmon[6] = &m_CMonat7;
    m_pmon[7] = &m_CMonat8;
    m_pmon[8] = &m_CMonat9;
    m_pmon[9] = &m_CMonat10;
    m_pmon[10] = &m_CMonat11;
    m_pmon[11] = &m_CMonat12;
}

CDKndInf2::~CDKndInf2()
{
}

void CDKndInf2::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_KA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_KA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_KA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_KA_ORT, m_COrt);
    DDX_Text(pDX, IDC_KA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_KA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_KA_TELE_KW, m_CTeleKw);
    DDX_Text(pDX, IDC_KA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_STATIC_UMSATZ, m_CUmsatz);
    DDX_Text(pDX, IDC_STATIC_WERTE_1, m_CWert1);
    DDX_Text(pDX, IDC_STATIC_WERTE_10, m_CWert10);
    DDX_Text(pDX, IDC_STATIC_WERTE_11, m_CWert11);
    DDX_Text(pDX, IDC_STATIC_WERTE_12, m_CWert12);
    DDX_Text(pDX, IDC_STATIC_WERTE_2, m_CWert2);
    DDX_Text(pDX, IDC_STATIC_WERTE_3, m_CWert3);
    DDX_Text(pDX, IDC_STATIC_WERTE_4, m_CWert4);
    DDX_Text(pDX, IDC_STATIC_WERTE_5, m_CWert5);
    DDX_Text(pDX, IDC_STATIC_WERTE_6, m_CWert6);
    DDX_Text(pDX, IDC_STATIC_WERTE_7, m_CWert7);
    DDX_Text(pDX, IDC_STATIC_WERTE_8, m_CWert8);
    DDX_Text(pDX, IDC_STATIC_WERTE_9, m_CWert9);
    DDX_Text(pDX, IDC_STATIC_MONAT_1, m_CMonat1);
    DDX_Text(pDX, IDC_STATIC_MONAT_10, m_CMonat10);
    DDX_Text(pDX, IDC_STATIC_MONAT_11, m_CMonat11);
    DDX_Text(pDX, IDC_STATIC_MONAT_12, m_CMonat12);
    DDX_Text(pDX, IDC_STATIC_MONAT_2, m_CMonat2);
    DDX_Text(pDX, IDC_STATIC_MONAT_3, m_CMonat3);
    DDX_Text(pDX, IDC_STATIC_MONAT_4, m_CMonat4);
    DDX_Text(pDX, IDC_STATIC_MONAT_5, m_CMonat5);
    DDX_Text(pDX, IDC_STATIC_MONAT_6, m_CMonat6);
    DDX_Text(pDX, IDC_STATIC_MONAT_7, m_CMonat7);
    DDX_Text(pDX, IDC_STATIC_MONAT_8, m_CMonat8);
    DDX_Text(pDX, IDC_STATIC_MONAT_9, m_CMonat9);
    DDX_Text(pDX, IDC_STATIC_ABC, m_CAbc);
}

BOOL CDKndInf2::OnSetActive( )
{
    CPropertyPageMultiLang::OnSetActive( );
    //Listboxen aufbauen
    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf2.cpp", "OnSetActive", "Page started");
        m_init = TRUE;
        m_anz = ReadPos();
        OnButtonUmsAe();
    }
    return TRUE;
}

BEGIN_MESSAGE_MAP(CDKndInf2, CPropertyPageMultiLang)
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_BUTTON_AUFTR, OnButtonAuftr)
    ON_BN_CLICKED(IDC_BUTTON_UMS_AE, OnButtonUmsAe)
    ON_BN_CLICKED(IDC_BUTTON_UMS_GP, OnButtonUmsGp)
    ON_BN_CLICKED(IDC_BUTTON_UMS_NN, OnButtonUmsNn)
    ON_BN_CLICKED(IDC_BUTTON_ZEIL, OnButtonZeil)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDKndInf2 message handlers

int CDKndInf2::ReadPos()
{
    int i;
    lMonUms.clear();
    CKNDMONUMS mon;
    BeginWaitCursor();
    mon.s.IDFNR                 = m_IdfNr;
    mon.s.KUNDENNR              = m_KndNr;
    mon.s.VERTRIEBSZENTRUMNR    = m_VzNr;
    for (i = 0; i < 12; i++)
    {
        mon.s.FETCH_REL = 1;
        mon.Server(AakundeSel_monums);
        if (mon.rc != 0)
        {
            break;
        }
        lMonUms.insert(lMonUms.end(), mon.s);
    }
    mon.s.FETCH_REL = 0;
    mon.Server(AakundeSel_monums);
    EndWaitCursor();
    return i;
}

void CDKndInf2::OnPaint()
{
    int xposvon,yposbis,i;
    int breite;
    float faktor;
    int start;
    tagRECT x;
    CPaintDC dc(this); // device context for painting
    CWnd* pWnd = GetDlgItem(IDC_STATIC_UMSATZ);
    CDC* pControlDC = pWnd->GetDC();
    CBrush NewBrush(RGB(0,128,0));
    CBrush* pOldBrush;
    pWnd->GetWindowRect(&x);
    breite = (x.right - x.left) / 12 - 2;
    faktor = (float)(x.bottom - x.top) / (float)m_max;
    start = x.bottom - x.top;
    pWnd->Invalidate();
    pWnd->UpdateWindow();
    pOldBrush = pControlDC->SelectObject(&NewBrush);
    for (i = 0, xposvon = 0; i < m_anz; i++, xposvon += breite + 2)
    {
        yposbis = (int)(start - hoch[i] * faktor);
        pControlDC->Rectangle(xposvon, yposbis, xposvon + breite, start);
    }
    pControlDC->SelectObject(pOldBrush);
    pWnd->ReleaseDC(pControlDC);

    // Do not call CPropertyPageMultiLang::OnPaint() for painting messages
}

void CDKndInf2::OnButtonAuftr()
{
    int i;
    m_max = 0;
    GetDlgItem(IDC_STATIC_TITEL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANZ_AUFTR));
    if (lMonUms.empty())
        return;
    for (it = lMonUms.end() - 1, i = 0;; it--, i++)
    {
        if (GetAeUser().IsErwKndInfo())
        {
            m_pstr[i]->Format("%7d",it->ANZAUFTRAG);
            hoch[i] = it->ANZAUFTRAG;
            if (m_max < it->ANZAUFTRAG)
                m_max = it->ANZAUFTRAG;
        }
        else
        {
            m_pstr[i]->Format("******");
            hoch[i] = 0 ;
        }
        m_pmon[i]->Format("%02d.%04d", it->MONAT, it->JAHR);
        if (it == lMonUms.begin())
            break;
    }
    UpdateData(FALSE);
    Invalidate();
}

void CDKndInf2::OnButtonUmsAe()
{
    int i;
    m_max = 0;
    GetDlgItem(IDC_STATIC_TITEL)->SetWindowText(CResString::ex().getStrTblText(AETXT_UMS_AEP));
    if (lMonUms.empty())
        return;
    for (it = lMonUms.end() - 1, i = 0;; it--, i++)
    {
        if (GetAeUser().IsErwKndInfo())
        {
            m_pstr[i]->Format("%9.0lf", it->BRUTTOUMS_AEP);
            hoch[i] = (long)it->BRUTTOUMS_AEP;
            if (m_max < it->BRUTTOUMS_AEP)
                m_max = it->BRUTTOUMS_AEP;
        }
        else
        {
            m_pstr[i]->Format("******");
            hoch[i] = 0 ;
        }
        m_pmon[i]->Format("%02d.%04d", it->MONAT, it->JAHR);
        if (it == lMonUms.begin())
            break;
    }
    UpdateData(FALSE);
    Invalidate();
}

void CDKndInf2::OnButtonUmsGp()
{
    int i;
    m_max = 0;
    GetDlgItem(IDC_STATIC_TITEL)->SetWindowText(CResString::ex().getStrTblText(AETXT_UMS_GP));
    if (lMonUms.empty())
        return;
    for (it = lMonUms.end() - 1, i = 0;; it--, i++)
    {
        if (GetAeUser().IsErwKndInfo())
        {
            m_pstr[i]->Format("%9.0lf", it->BRUTTOUMS_GEP);
            hoch[i] = (long)it->BRUTTOUMS_GEP;
            if (m_max < it->BRUTTOUMS_GEP)
                m_max = it->BRUTTOUMS_GEP;
        }
        else
        {
            m_pstr[i]->Format("******");
            hoch[i] = 0 ;
        }
        m_pmon[i]->Format("%02d.%04d", it->MONAT, it->JAHR);
        if (it == lMonUms.begin())
            break;
    }
    UpdateData(FALSE);
    Invalidate();
}

void CDKndInf2::OnButtonUmsNn()
{
    int i;
    m_max = 0;
    GetDlgItem(IDC_STATIC_TITEL)->SetWindowText(CResString::ex().getStrTblText(AETXT_UMS_NN));
    if (lMonUms.empty())
        return;
    for (it = lMonUms.end() - 1, i = 0;; it--, i++)
    {
        if (GetAeUser().IsErwKndInfo())
        {
            m_pstr[i]->Format("%9.0lf", it->UMSNN_NNAEP);
            hoch[i] = (long)it->UMSNN_NNAEP;
            if (m_max < it->UMSNN_NNAEP)
                m_max = it->UMSNN_NNAEP;
        }
        else
        {
            m_pstr[i]->Format("******");
            hoch[i] = 0 ;
        }
        m_pmon[i]->Format("%02d.%04d", it->MONAT, it->JAHR);
        if (it == lMonUms.begin())
            break;
    }
    UpdateData(FALSE);
    Invalidate();
}

void CDKndInf2::OnButtonZeil()
{
    int i;
    m_max = 0;
    GetDlgItem(IDC_STATIC_TITEL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANZ_ZEILEN));
    if (lMonUms.empty())
        return;
    for (it = lMonUms.end() - 1, i = 0;; it--, i++)
    {
        if (GetAeUser().IsErwKndInfo())
        {
            m_pstr[i]->Format("%7d", it->ANZZEILEN);
            hoch[i] = it->ANZZEILEN;
            if (m_max < it->ANZZEILEN)
                m_max = it->ANZZEILEN;
        }
        else
        {
            m_pstr[i]->Format("******");
            hoch[i] = 0;
        }
        m_pmon[i]->Format("%02d.%04d", it->MONAT, it->JAHR);
        if (it == lMonUms.begin())
            break;
    }
    UpdateData(FALSE);
    Invalidate();
}

HBRUSH CDKndInf2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPageMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (m_KzAeGesperrt)
    {
        if (pWnd->GetDlgCtrlID() == IDC_KA_KUNDE_NAME)
            pDC->SetTextColor(RGB(200, 0, 0));
    }
    return hbr;
}

BOOL CDKndInf2::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

// CDKndInf3-Dialogfeld

IMPLEMENT_DYNAMIC(CDKndInf3, CPropertyPage)
CDKndInf3::CDKndInf3()
    : CPropertyPageMultiLang(CDKndInf3::IDD)
{
    m_init = FALSE;
}

CDKndInf3::~CDKndInf3()
{
}

void CDKndInf3::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_BTM, m_edit_BTM);
    DDX_Control(pDX, IDC_EDIT_DISPO, m_edit_Dispo);
    DDX_Control(pDX, IDC_EDIT_DOKU, m_edit_Doku);
    DDX_Control(pDX, IDC_EDIT_KIPPZEIT, m_edit_Kippzeit);
    DDX_Control(pDX, IDC_EDIT_LAGER, m_edit_Lager);
    DDX_Control(pDX, IDC_EDIT_EIL, m_edti_Eil);
    DDX_Control(pDX, IDC_EDIT_TOUR, m_edit_Tour);
    DDX_Control(pDX, IDC_EDIT_FILINF, m_edit_Filinf);
    DDX_Control(pDX, IDC_EDIT_FILINF2, m_edit_Filinf2);

}


BEGIN_MESSAGE_MAP(CDKndInf3, CPropertyPageMultiLang)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDKndInf3-Meldungshandler

BOOL CDKndInf3::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive( );
    //Ausgaben aufbauen
    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf3.cpp", "OnSetActive", "Page started");

        CFont  objCFont;
        CFont  objCFont2;
        LOGFONT lf;
        LOGFONT lf2;

        CFont* pobjCFont = m_edit_Filinf.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont.CreateFontIndirect(&lf);

        m_edit_Filinf.SetFont(&objCFont);

        CFont* pobjCFont2 = m_edit_Filinf2.GetFont();
        pobjCFont2->GetLogFont(&lf2);
        lf2.lfWeight *= 2;
        objCFont2.CreateFontIndirect(&lf2);

        m_edit_Filinf2.SetFont(&objCFont2);

        m_init = TRUE;
        CString CStr;
        ppString Info;
        CBRANCHINFO fil;
        CKNDFILINFO knd;
        CKNDFILINFO2 knd2;
        fil.SetBranchno(m_VzNr);
        knd.SetVertriebszentrumnr(m_VzNr);
        knd.SetKundennr(m_KndNr);
        knd2.SetFilialnr(m_VzNr);
        BeginWaitCursor();
        knd.SelKnd();
        knd2.SelInfo();
        CStr.Format("% 15.2lf %s", knd.GetBtmgebuehr(), CResString::ex().getStrTblText(AETXT_DM).GetString());
        GetDlgItem(IDC_EDIT_BTM)->SetWindowText(CStr);
        CStr.Format("% 15.2lf %s", knd.GetDispogebuehr(), CResString::ex().getStrTblText(AETXT_DM).GetString());
        GetDlgItem(IDC_EDIT_DISPO)->SetWindowText(CStr);
        CStr.Format("% 15.2lf %s", knd.GetDokugebuehr(), CResString::ex().getStrTblText(AETXT_DM).GetString());
        GetDlgItem(IDC_EDIT_DOKU)->SetWindowText(CStr);
        if (knd.GetTourenkippzeit() == 0)
        {
            CStr.Format("% 15d %s", knd2.GetTourenkippzeit(), CResString::ex().getStrTblText(AETXT_MIN).GetString());
            GetDlgItem(IDC_EDIT_KIPPZEIT)->SetWindowText(CStr);
        }
        else
        {
            CStr.Format("% 15d %s", knd.GetTourenkippzeit(), CResString::ex().getStrTblText(AETXT_MIN).GetString());
            GetDlgItem(IDC_EDIT_KIPPZEIT)->SetWindowText(CStr);
        }
        CStr.Format("% 15d %s", knd2.GetDurchlaufnormal(), CResString::ex().getStrTblText(AETXT_MIN).GetString());
        GetDlgItem(IDC_EDIT_LAGER)->SetWindowText(CStr);
        CStr.Format("% 15d %s", knd2.GetDurchlaufeilbote(), CResString::ex().getStrTblText(AETXT_MIN).GetString());
        GetDlgItem(IDC_EDIT_EIL)->SetWindowText(CStr);
        CStr.Format("% 15d %s", knd2.GetTourverspaetung(), CResString::ex().getStrTblText(AETXT_MIN).GetString());
        GetDlgItem(IDC_EDIT_TOUR)->SetWindowText(CStr);
        fil.SetBranchinfotype(0);
        if (!fil.SelInfo())
        {
            fil.GetInformation(Info);
            GetDlgItem(IDC_EDIT_FILINF)->SetWindowText(Info);
            GetDlgItem(IDC_EDIT_FILINF)->RedrawWindow();
            m_edit_Filinf.SetSel(0, -1, FALSE);
        }
        fil.SetBranchinfotype(1);
        if (!fil.SelInfo())
        {
            fil.GetInformation(Info);
            GetDlgItem(IDC_EDIT_FILINF2)->SetWindowText(Info);
            GetDlgItem(IDC_EDIT_FILINF2)->RedrawWindow();
            m_edit_Filinf2.SetSel(0, -1, FALSE);
        }
        EndWaitCursor();
        // damit die Textausrichtung klappt
        m_edit_BTM.SetSel(0, -1, FALSE);
        m_edit_Dispo.SetSel(0, -1, FALSE);
        m_edit_Doku.SetSel(0, -1, FALSE);
        m_edit_Kippzeit.SetSel(0, -1, FALSE);
        m_edit_Lager.SetSel(0, -1, FALSE);
        m_edti_Eil.SetSel(0, -1, FALSE);
        m_edit_Tour.SetSel(0, -1, FALSE);
    }
    return TRUE;
}

HBRUSH CDKndInf3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPageMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_EDIT_BTM)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_DISPO)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_DOKU)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_KIPPZEIT)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_LAGER)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_EIL)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_TOUR)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_FILINF)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_FILINF2)
    {
        pDC->SetTextColor(RGB(255, 0, 0));      // rot
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }

    return hbr;
}

/////////////////////////////////////////////////////////////////////////////
// CDKndInf4 property page

IMPLEMENT_DYNAMIC(CDKndInf4, CPropertyPageMultiLang)

#define COL_TOUR_ID     0
#define COL_TOUR_MAIN   1
#define COL_TOUR_TILL   2
#define COL_TOUR_VB     3
#define COL_TOUR_BTM    4
#define COL_TOUR_KK     5
#define COL_TOUR_K08    6
#define COL_TOUR_K20    7
#define COL_TOUR_PSY    8
#define COL_TOUR_KT     9
#define COL_TOUR_CONS1  10
#define COL_TOUR_CONS2  11
#define COL_TOUR_CONS3  12
#define COL_TOUR_AART   13

//Listcontrol-Spalten-Typ für gefüllte Listbox
    static COLUMNS_TYPES SpaltenTourenWocheBefuellt[] =
    {
        COL_TOUR_ID,    "", 53, LVCFMT_LEFT,
        COL_TOUR_MAIN,  "", 40, LVCFMT_RIGHT,
        COL_TOUR_TILL,  "", 40, LVCFMT_RIGHT,
        COL_TOUR_VB,    "", 28, LVCFMT_RIGHT,
        COL_TOUR_BTM,   "", 35, LVCFMT_RIGHT,
        COL_TOUR_KK,    "", 28, LVCFMT_RIGHT,
        COL_TOUR_K08,   "", 32, LVCFMT_RIGHT,
        COL_TOUR_K20,   "", 32, LVCFMT_RIGHT,
        COL_TOUR_PSY,   "", 38, LVCFMT_RIGHT,
        COL_TOUR_KT,    "", 28, LVCFMT_RIGHT,
        COL_TOUR_CONS1, "", 42, LVCFMT_RIGHT,
        COL_TOUR_CONS2, "", 42, LVCFMT_RIGHT,
        COL_TOUR_CONS3, "", 42, LVCFMT_RIGHT,
        COL_TOUR_AART,  "", 32, LVCFMT_RIGHT,
        -1,             "",  0, 0
    };

#define NUM_SPALT_TOUR_WOCHE_BEFUELLT  14

//Listcontrol-Spalten-Typ für leere Listbox (-> keine Treffer für den Wochentag)
    static COLUMNS_TYPES SpaltenTourenWocheLeer[] =
    {
        0,  "", 200, LVCFMT_LEFT,
        -1, "",   0, 0
    };


#define NUM_SPALT_TOUR_WOCHE_LEER 1


CDKndInf4::CDKndInf4(CWnd* /*pParent*/ /*=NULL*/)
    : CPropertyPageMultiLang(CDKndInf4::IDD)
{
    m_init = FALSE;

    m_pvecTourWocheTour = NULL;

//alle Schalter für Treffer auf der Datenbank auf FALSE
    m_binitMO = FALSE;
    m_binitDI = FALSE;
    m_binitMI = FALSE;
    m_binitDO = FALSE;
    m_binitFR = FALSE;
    m_binitSA = FALSE;
    m_binitSO = FALSE;


//Multilanguage-Texte für Listcontrol-Spalten
    SpaltenTourenWocheBefuellt[COL_TOUR_ID].Columns = CResString::ex().getStrTblText(AETXT_KURZ_TOUR_ID);
    SpaltenTourenWocheBefuellt[COL_TOUR_MAIN].Columns = CResString::ex().getStrTblText(AETXT_HBZ);
    SpaltenTourenWocheBefuellt[COL_TOUR_TILL].Columns = CResString::ex().getStrTblText(AETXT_BFE);
    SpaltenTourenWocheBefuellt[COL_TOUR_VB].Columns = CResString::ex().getStrTblText(AETXT_VB);
    SpaltenTourenWocheBefuellt[COL_TOUR_BTM].Columns = CResString::ex().getStrTblText(AETXT_BTM);
    SpaltenTourenWocheBefuellt[COL_TOUR_KK].Columns = CResString::ex().getStrTblText(AETXT_KK);
    SpaltenTourenWocheBefuellt[COL_TOUR_K08].Columns = CResString::ex().getStrTblText(AETXT_K08);
    SpaltenTourenWocheBefuellt[COL_TOUR_K20].Columns = CResString::ex().getStrTblText(AETXT_K20);
    SpaltenTourenWocheBefuellt[COL_TOUR_PSY].Columns = CResString::ex().getStrTblText(AETXT_PSY);
    SpaltenTourenWocheBefuellt[COL_TOUR_KT].Columns = CResString::ex().getStrTblText(AETXT_RT);
    SpaltenTourenWocheBefuellt[COL_TOUR_CONS1].Columns = CResString::ex().getStrTblText(AETXT_CONS_TIME1);
    SpaltenTourenWocheBefuellt[COL_TOUR_CONS2].Columns = CResString::ex().getStrTblText(AETXT_CONS_TIME2);
    SpaltenTourenWocheBefuellt[COL_TOUR_CONS3].Columns = CResString::ex().getStrTblText(AETXT_CONS_TIME3);
    SpaltenTourenWocheBefuellt[COL_TOUR_AART].Columns = CResString::ex().getStrTblText(AETXT_A_ART);

    SpaltenTourenWocheLeer[0].Columns = CResString::ex().getStrTblText(AETXT_KURZ_TOUR_ID);
}

CDKndInf4::~CDKndInf4()
{
    //Destruktor: Inhalt des Vektors wird aus dem Speicher entfernt
    vector<TOURWOCHE_TOUR>::iterator itPtr;

    if (m_pvecTourWocheTour != NULL)
    {
        for (itPtr=m_pvecTourWocheTour->begin(); itPtr != m_pvecTourWocheTour->end();)
        {
            itPtr = m_pvecTourWocheTour->erase(itPtr);
            /*
            if (itPtr == m_pvecTourWocheTour->end())
            {
                break;
            }
            */
        }

        delete m_pvecTourWocheTour;
    }
}



void CDKndInf4::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_TOUR_MON, m_ListTourenMO);
    DDX_Control(pDX, IDC_LIST_TOUR_DIE, m_ListTourenDI);
    DDX_Control(pDX, IDC_LIST_TOUR_MIT, m_ListTourenMI);
    DDX_Control(pDX, IDC_LIST_TOUR_DON, m_ListTourenDO);
    DDX_Control(pDX, IDC_LIST_TOUR_FRE, m_ListTourenFR);
    DDX_Control(pDX, IDC_LIST_TOUR_SAM, m_ListTourenSA);
    DDX_Control(pDX, IDC_LIST_TOUR_SON, m_ListTourenSO);

    DDX_Text(pDX, IDC_TA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_TA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_TA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_TA_ORT, m_COrt);
    DDX_Text(pDX, IDC_TA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_TA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_TA_TELE_KW, m_CTeleKw);
    DDX_Text(pDX, IDC_TA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_STATIC_TA_ABC, m_CAbc);
}



CWnd* CDKndInf4::getDialogforTagesTyp(const int iWeekDay) const
{
    //Liefert das dem Wochentag zugeordnete Listcontrol als Pointer zurück
    if (iWeekDay == 1)
        return GetDlgItem(IDC_LIST_TOUR_MON);
    else if (iWeekDay == 2)
        return GetDlgItem(IDC_LIST_TOUR_DIE);
    else if (iWeekDay == 3)
        return GetDlgItem(IDC_LIST_TOUR_MIT);
    else if (iWeekDay == 4)
        return GetDlgItem(IDC_LIST_TOUR_DON);
    else if (iWeekDay == 5)
        return GetDlgItem(IDC_LIST_TOUR_FRE);
    else if (iWeekDay == 6)
        return GetDlgItem(IDC_LIST_TOUR_SAM);
    else if (iWeekDay == 0)
        return GetDlgItem(IDC_LIST_TOUR_SON);
    else
        return NULL;
}


BOOL CDKndInf4::getInitStateforTagesTyp(const int iWeekDay) const
{
    //Liefert den Wert des Schalters, der dem Wochentag zugeordnet ist (m_binitMO - m_binitSO)
    if (iWeekDay == 1)
        return m_binitMO;
    else if (iWeekDay == 2)
        return m_binitDI;
    else if (iWeekDay == 3)
        return m_binitMI;
    else if (iWeekDay == 4)
        return m_binitDO;
    else if (iWeekDay == 5)
        return m_binitFR;
    else if (iWeekDay == 6)
        return m_binitSA;
    else if (iWeekDay == 0)
        return m_binitSO;
    else
        return FALSE;
}


BOOL CDKndInf4::initListBox(const int iWeekDay)
{
    //Initialisiert das dem Wochentag zugeordnete Listcontrol

    CListCtrl* lCtrlCurrentListCtrl = (CListCtrl*)getDialogforTagesTyp(iWeekDay); //Listcontrol des Wochtags ermitteln

    BOOL bInitState = getInitStateforTagesTyp(iWeekDay); //Wert des Initialisierungsschalters holen

    if (bInitState)
    {
        //Ist der Schalter true (-> Werte für den Wochentag vorhanden), so wird das Listcontrol mit allen nötigen Spalten initialisiert
        if (!CListCtrlHelper::AddColumns(SpaltenTourenWocheBefuellt, *lCtrlCurrentListCtrl))
        {
            return FALSE;
        }
        if (!AeGetApp()->IsDE())
        {
            lCtrlCurrentListCtrl->SetColumnWidth(COL_TOUR_MAIN, 0);
            lCtrlCurrentListCtrl->SetColumnWidth(COL_TOUR_TILL, 0);
        }
    }
    else
    {
        //Ist der Schalter false (-> keine Werte für den Wochentag vorhanden), so wird das Listcontrol mit einer Dummy-Spalte und einem Dummywert initialisiert
        if (!CListCtrlHelper::AddColumns(SpaltenTourenWocheLeer, *lCtrlCurrentListCtrl))
        {
            return FALSE;
        }

        if (lCtrlCurrentListCtrl->InsertItem(0, CResString::ex().getStrTblText(AETXT_CONS_TIME_NODATAFOUND)) == -1)
            return FALSE;
    }

    return TRUE;
}

void CDKndInf4::setDialogTourWeekDayEnabled(const int iWeekDay)
{
    //setzt die Schalter m_binitMO - m_binitSO abhängig vom Wochentag auf true
    if ((iWeekDay == 1) && !(m_binitMO))
        m_binitMO=TRUE;
    else if ((iWeekDay == 2) && !(m_binitDI))
        m_binitDI=TRUE;
    else if ((iWeekDay == 3) && !(m_binitMI))
        m_binitMI=TRUE;
    else if ((iWeekDay == 4) && !(m_binitDO))
        m_binitDO=TRUE;
    else if ((iWeekDay == 5) && !(m_binitFR))
        m_binitFR=TRUE;
    else if ((iWeekDay == 6) && !(m_binitSA))
        m_binitSA=TRUE;
    else if ((iWeekDay == 0) && !(m_binitSO))
        m_binitSO=TRUE;
}


BOOL CDKndInf4::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;
}


BOOL CDKndInf4::OnSetActive()
{
    //Befüllen Property Page KndInfo4
    CPropertyPageMultiLang::OnSetActive( );

    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf4.cpp", "OnSetActive", "Page started");
        m_init = TRUE;

        CPARAUFBEARB paraufbearb;

        paraufbearb.s.FILIALNR = m_VzNr;
        paraufbearb.Server(AafilSelaufbearb);
        m_lStdMinutenConsTime = paraufbearb.s.AUFTRAGZUSAMMENMMM;

        TOURWOCHE_TOUR* pTourWocheTour_AT;
        TOURWOCHE_TOUR* pTourWocheTour_KT;

        CListCtrl* lCtrlCurrentListCtrl;

        CKNDTOURFENSTER             op; //DADE: Bestellfenster
        CKNDTOURWOCHE               t1; //DADE: Join der Tabellen tourplanwoche und tourplantagwoche
        CKNDTOURWOCHE2              t2; //DADE: Tabelle tourplanconstime
        CKNDTOURWOCHE3              t3; //DADE: Tabelle tourconstime

        long                        lCurrentDate;  //Tagesdatum
        long                        lStdConsTime; //Standardwert bei nicht gesetzter Constime
        int                         iWeekDay;

        ppString                    CTemp;
        ppString                    tourid;
        ppString                    AArt;

        BOOL                        bConsTimeFound_AT = FALSE;
        BOOL                        bConsTimeFound_KT = FALSE;
        int                         index;

        lCurrentDate = AeGetApp()->GetCurrentDate();

        t1.SetVertriebszentrumnr(m_VzNr);
        t1.SetKundennr(m_KndNr);
        t2.SetVertriebszentrumnr(m_VzNr);
        t2.SetKundennr(m_KndNr);
        t2.SetDatumkommi(lCurrentDate);
        t3.SetFilialnr(m_VzNr);
        t3.SetDatumkommi(lCurrentDate);

        lStdConsTime = 0;

        /***************************************************************/
        BeginWaitCursor();
        m_pvecTourWocheTour = new vector<TOURWOCHE_TOUR>;
        for (;;)
        {
            bConsTimeFound_AT = FALSE;
            bConsTimeFound_KT = FALSE;

            t1.SelList(); //Nächster Wert für Join der Tabellen tourplanwoche und tourplantagwoche
            if (t1.rc == SRV_SQLNOTFOUND)
                break;
            else if (t1.rc < SRV_OK)
            {
                EndWaitCursor();
                return FALSE;
            }
            pTourWocheTour_KT = new TOURWOCHE_TOUR;

            pTourWocheTour_KT->CStrTour = t1.s.TOURID;
            pTourWocheTour_KT->CStrTourID.Format("%.2s:%.2s/%.2s", t1.s.TOURID, t1.s.TOURID + 2, t1.s.TOURID + 4);
            pTourWocheTour_KT->iWochenTag = t1.GetWeekday();

            iWeekDay = t1.GetWeekday();
            setDialogTourWeekDayEnabled(iWeekDay); //Aktivieren des Schalters für das ListControl

            pTourWocheTour_KT->CStrAArt = t1.GetKdauftragart(AArt);

            if (t1.GetIstverbundtour() == '1')
                pTourWocheTour_KT->CStrVBTour = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else pTourWocheTour_KT->CStrVBTour.Empty();

            if (t1.GetIsbtm() == 1)
                pTourWocheTour_KT->CStrBTM = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else pTourWocheTour_KT->CStrBTM.Empty();

            if (t1.GetIskk() == 1)
                pTourWocheTour_KT->CStrKK = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else pTourWocheTour_KT->CStrKK.Empty();

            if (t1.GetIsk08() == 1)
                pTourWocheTour_KT->CStrK08 = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else pTourWocheTour_KT->CStrK08.Empty();

            if (t1.GetIsk20() == 1)
                pTourWocheTour_KT->CStrK20 = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else pTourWocheTour_KT->CStrK20.Empty();

            if (t1.GetReturnstour() == 1)
                pTourWocheTour_KT->CStrRT = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else pTourWocheTour_KT->CStrRT.Empty();

            if (t1.GetTranspexclpsycho() == 0)
                pTourWocheTour_KT->CStrPsycho = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else pTourWocheTour_KT->CStrPsycho.Empty();

            t1.GetTourid(CTemp);
            t2.SetTourid(CTemp);
            for (int i = 1; i <= 3; i++)
            {
                //zunächst wird überprüft, ob für die TourID und den Kunde Werte in Tabelle tourplanconstime existieren
                t2.SelList(); //nächster Wert Tabelle tourplanconstime

                if (t2.rc < SRV_OK)
                {
                    EndWaitCursor();
                    delete pTourWocheTour_KT;
                    return FALSE;
                }
                else if (t2.rc == SRV_OK)
                {
                    bConsTimeFound_KT = TRUE;
                    pTourWocheTour_KT->SetConsTime(i, t2.GetConstime()); //Befüllen des entsprechenden Feldes in der Struktur
                }
                else
                {
                    for (int a = i; a <= 3; a++) //Auffüllen der Struktur mit Dummy-Einträgen
                        pTourWocheTour_KT->SetConsTimeUnavailabe(a);

                    break;
                }
            }
            t2.CloseCursor();

            pTourWocheTour_AT = new TOURWOCHE_TOUR;
            pTourWocheTour_AT->CStrTourID.Format("%.2s:%.2s/%.2s", t1.s.TOURID, t1.s.TOURID + 2, t1.s.TOURID + 4);
            pTourWocheTour_AT->iWochenTag = t1.GetWeekday();

            pTourWocheTour_KT->CStrAArt = t1.GetKdauftragart(AArt);

            t1.GetTourid(CTemp);
            t3.SetTourid(CTemp);
            for (int i = 1; i <= 3; i++)
            {
                //zunächst wird überprüft, ob für die TourID Werte in Tabelle tourconstime existieren
                t3.SelList(); //nächster Wert Tabelle tourconstime

                if (t3.rc < SRV_OK)
                {
                    EndWaitCursor();
                    delete pTourWocheTour_AT;
                    return FALSE;
                }
                else if (t3.rc == SRV_OK)
                {
                    bConsTimeFound_AT = TRUE;
                    pTourWocheTour_AT->SetConsTime(i, t3.GetConstime()); //Befüllen des entsprechenden Feldes in der Struktur
                }
                else
                {
                    for (int a = i; a <= 3; a++) //Auffüllen der Struktur mit Dummy-Einträgen
                        pTourWocheTour_AT->SetConsTimeUnavailabe(a);

                    break;
                }
            }
            t3.CloseCursor();

            if (AeGetApp()->IsDE())
            {
                if (bConsTimeFound_KT)
                {
                    m_pvecTourWocheTour->push_back(*pTourWocheTour_KT);
                    delete pTourWocheTour_AT;
                }
                else if ((bConsTimeFound_AT))
                {
                    m_pvecTourWocheTour->push_back(*pTourWocheTour_AT);
                    delete pTourWocheTour_KT;
                }
                else
                {
                    m_pvecTourWocheTour->push_back(*pTourWocheTour_KT);
                    delete pTourWocheTour_AT;
                }
            }
            else
            {
                if (!bConsTimeFound_AT && !bConsTimeFound_KT)
                {
                    if (atol(t1.s.TOURID) < 240000)
                    {
                        AllgAddTimeSpan(atol(t1.s.TOURID), m_lStdMinutenConsTime * (-60), &lStdConsTime);
                        lStdConsTime = lStdConsTime / 100;
                        pTourWocheTour_KT->SetConsTime(1, lStdConsTime);
                    }

                    m_pvecTourWocheTour->push_back(*pTourWocheTour_KT);

                    delete pTourWocheTour_AT;
                }
                else if (bConsTimeFound_AT && bConsTimeFound_KT)
                {
                    m_pvecTourWocheTour->push_back(*pTourWocheTour_AT);

                    m_pvecTourWocheTour->push_back(*pTourWocheTour_KT);
                }
                else if (bConsTimeFound_AT && !bConsTimeFound_KT)
                {
                    m_pvecTourWocheTour->push_back(*pTourWocheTour_AT);

                    delete pTourWocheTour_KT;

                }
                else if (bConsTimeFound_KT && !bConsTimeFound_AT)
                {
                    m_pvecTourWocheTour->push_back(*pTourWocheTour_KT);
                    delete pTourWocheTour_AT;
                }
            }
        }
        t1.CloseCursor();

        /***************************************************************/
        for (int a = 0; a < 7; a++) //Vorbereitung der Listcontrol-Felder des Dialogs
        {
            if (!initListBox(a))
            {
                EndWaitCursor();
                return FALSE;
            }
        }

        //alle Sätze im Vektor werden nun in das dem Wochentag entsprechende Listcontrol eingefügt
        vector<TOURWOCHE_TOUR>::iterator itPtr;

        for (itPtr = m_pvecTourWocheTour->begin(); itPtr < m_pvecTourWocheTour->end(); itPtr++)
        {
            iWeekDay = itPtr->iWochenTag;

            lCtrlCurrentListCtrl = (CListCtrl*)getDialogforTagesTyp(iWeekDay);

            if (!lCtrlCurrentListCtrl) //Ermittlung Listcontrol-Feld des Wochentags
                return FALSE;

            index = lCtrlCurrentListCtrl->GetItemCount();

            //Einfügen des Satzes in das Listcontrol
            if (lCtrlCurrentListCtrl->InsertItem(index, itPtr->CStrTourID) == -1)
                return FALSE;

            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_CONS1, itPtr->CStrConsTime1);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_CONS2, itPtr->CStrConsTime2);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_CONS3, itPtr->CStrConsTime3);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_BTM, itPtr->CStrBTM);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_KK, itPtr->CStrKK);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_K08, itPtr->CStrK08);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_K20, itPtr->CStrK20);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_PSY, itPtr->CStrPsycho);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_KT, itPtr->CStrRT);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_VB, itPtr->CStrVBTour);
            lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_AART, itPtr->CStrAArt);
            if (AeGetApp()->IsDE())
            {
                CStrMain.Empty();
                CStrTill.Empty();
                op.SetBranchno(m_VzNr);
                op.SetCustomerno(m_KndNr);
                op.SetWeekday((short)itPtr->iWochenTag);
                op.SetTourid(itPtr->CStrTour);
                for (int i = 0;;i++)
                {
                    if (op.SelPeriods())
                        break;

                    if (i > 0)
                    {
                        index = lCtrlCurrentListCtrl->GetItemCount();
                        //Einfügen des Satzes in das Listcontrol
                        if (lCtrlCurrentListCtrl->InsertItem(index, itPtr->CStrTourID) == -1)
                            return FALSE;
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_CONS1, itPtr->CStrConsTime1);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_CONS2, itPtr->CStrConsTime2);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_CONS3, itPtr->CStrConsTime3);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_BTM, itPtr->CStrBTM);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_KK, itPtr->CStrKK);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_K08, itPtr->CStrK08);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_K20, itPtr->CStrK20);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_PSY, itPtr->CStrPsycho);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_KT, itPtr->CStrRT);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_VB, itPtr->CStrVBTour);
                        lCtrlCurrentListCtrl->SetItemText(index,COL_TOUR_AART, itPtr->CStrAArt);
                    }
                    CStrMain.Format("%d:%02d", op.GetMaintime() / 100, op.GetMaintime() % 100);
                    CStrTill.Format("%d:%02d", op.GetTotime() / 100, op.GetTotime() % 100);
                    lCtrlCurrentListCtrl->SetItemText(index, COL_TOUR_MAIN, CStrMain);
                    lCtrlCurrentListCtrl->SetItemText(index, COL_TOUR_TILL, CStrTill);
                }
                op.CloseCursor();
            }

        }
        /***************************************************************/

        UpdateData(FALSE);

        EndWaitCursor();
    }

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDKndInf4, CPropertyPageMultiLang)
END_MESSAGE_MAP()


// CDKndInf5-Dialogfeld

/////////////////////////////////////////////////////////////////////////////
// CDKndInf5 property page

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES SpaltenZahlbed[] =
{
    0,  "",  90, LVCFMT_LEFT,
    1,  "", 130, LVCFMT_LEFT,
    -1, "",   0, 0
};

static COLUMNS_TYPES SpaltenKredit[] =
{
    0,  "", 80, LVCFMT_RIGHT,
    1,  "", 80, LVCFMT_RIGHT,
    2,  "", 80, LVCFMT_RIGHT,
    3,  "", 80, LVCFMT_RIGHT,
    4,  "", 80, LVCFMT_RIGHT,
    5,  "", 80, LVCFMT_RIGHT,
    6,  "", 80, LVCFMT_RIGHT,
    7,  "", 90, LVCFMT_RIGHT,
    8,  "",  0, LVCFMT_LEFT,
    -1, "",  0, 0
};


#define NUM_SPALT_ZAHLBED 2
#define NUM_SPALT_KREDIT  9

IMPLEMENT_DYNAMIC(CDKndInf5, CPropertyPage)
CDKndInf5::CDKndInf5()
    : CPropertyPageMultiLang(CDKndInf5::IDD)
    , m_CKundeName(_T(""))
    , m_CApoName(_T(""))
    , m_CPlz(_T(""))
    , m_COrt(_T(""))
    , m_CStrasse(_T(""))
    , m_CIdfNummer(_T(""))
    , m_CAbc(_T(""))
    , m_CTeleNr(_T(""))
    , m_CTeleKw(_T(""))
{
    m_init = FALSE;
    SpaltenZahlbed[0].Columns = CResString::ex().getStrTblText(AETXT_TAGE);
    SpaltenZahlbed[1].Columns = CResString::ex().getStrTblText(AETXT_PREIS_TYP);

    SpaltenKredit[0].Columns = CResString::ex().getStrTblText(AETXT_KL_SALDO);
    SpaltenKredit[1].Columns = CResString::ex().getStrTblText(AETXT_KL_LIMIT);
    SpaltenKredit[2].Columns = CResString::ex().getStrTblText(AETXT_KL_DEBIT);
    SpaltenKredit[3].Columns = CResString::ex().getStrTblText(AETXT_KL_KREDIT);
    SpaltenKredit[4].Columns = CResString::ex().getStrTblText(AETXT_KL_MONAT);
    SpaltenKredit[5].Columns = CResString::ex().getStrTblText(AETXT_KL_TAG);
    SpaltenKredit[6].Columns = CResString::ex().getStrTblText(AETXT_KL_RETURNS);
    SpaltenKredit[7].Columns = CResString::ex().getStrTblText(AETXT_KL_GOODS);
    SpaltenKredit[8].Columns = CResString::ex().getStrTblText(AETXT_KL_TYP);
}

CDKndInf5::~CDKndInf5()
{
}

void CDKndInf5::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_TA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_TA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_TA_ORT, m_COrt);
    DDX_Text(pDX, IDC_TA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_TA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_STATIC_TA_ABC, m_CAbc);
    DDX_Text(pDX, IDC_TA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_TA_TELE_KW, m_CTeleKw);
    DDX_Control(pDX, IDC_LIST_ZAHLBED, m_LstCtrl);
    DDX_Control(pDX, IDC_LIST_DEBTLIMIT, m_LstCtrlDebt);
}


BEGIN_MESSAGE_MAP(CDKndInf5, CPropertyPageMultiLang)
END_MESSAGE_MAP()


// CDKndInf5-Meldungshandler

BOOL CDKndInf5::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;
}

BOOL CDKndInf5::OnSetActive()
{
    //Befüllen Property Page KndInfo4
    CPropertyPageMultiLang::OnSetActive();

    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf5.cpp", "OnSetActive", "Page started");
        m_init = TRUE;

        if (   !CListCtrlHelper::AddColumns(SpaltenZahlbed, m_LstCtrl)
            || !CListCtrlHelper::AddColumns(SpaltenKredit, m_LstCtrlDebt) )
        {
            return FALSE;
        }
        if (AeGetApp()->IsBG())
        {
            m_LstCtrlDebt.SetColumnWidth(8, 20);
        }
        else
        {
            m_LstCtrl.SetColumnWidth(1, 0);
        }
        // Ausgabe der Listbox fuer Zahlungsziele
        ppString Payterm;
        CStringArray s;
        s.SetSize(NUM_SPALT_ZAHLBED);
        BeginWaitCursor();
        if (AeGetApp()->IsBG())
        {
            CCSTPAYTERM cstpayterm;
            cstpayterm.SetCustomerno(m_KndNr);
            cstpayterm.SetBranchno(m_VzNr);
            for (;;)
            {
                if (cstpayterm.SelList() != SRV_OK)
                    break;
                s[0].Format("%d", cstpayterm.GetPaymentarget());
                if (cstpayterm.GetPreis_typ() == 0)
                    s[1] = CResString::ex().getStrTblText(AETXT_RAB_FREI);
                else if (cstpayterm.GetPreis_typ() == 1)
                    s[1] = CResString::ex().getStrTblText(AETXT_RAB_KKH);
                else if (cstpayterm.GetPreis_typ() == 5)
                    s[1] = CResString::ex().getStrTblText(AETXT_LISTE5);

                if (!CListCtrlHelper::AppendItem(m_LstCtrl, NUM_SPALT_ZAHLBED, s))
                {
                    return FALSE;
                }
            }
        }
        else if (AeGetApp()->IsRS())
        {
            CPAYTERM payterm;
            payterm.SetVertriebszentrumnr(m_VzNr);
            payterm.SetKundennr(m_KndNr);
            for (;;)
            {
                if (payterm.SelList() != SRV_OK)
                    break;
                s[0].Format("%d", payterm.GetPaymentarget());
                //s[1].Format("%.2lf", payterm.GetCashdisount());

                if (!CListCtrlHelper::AppendItem(m_LstCtrl, NUM_SPALT_ZAHLBED, s))
                {
                    return FALSE;
                }
            }
        }
        else
        {
            GetDlgItem(IDC_LIST_ZAHLBED)->EnableWindow(FALSE);
            GetDlgItem(IDC_LIST_ZAHLBED)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_LIST_ZAHLBED)->EnableWindow(FALSE);
            GetDlgItem(IDC_LIST_ZAHLBED)->ShowWindow(SW_HIDE);
        }
        // Ausgabe der Listbox fuer Kreditlimit
        CKREDITLIMIT kreditlimit;
        kreditlimit.SetKundennr(m_KndNr);
        kreditlimit.SetVertriebszentrumnr(m_VzNr);
        //if (1)
        if (!AeGetApp()->IsBG())
        {
            if (kreditlimit.SelLimit())
            {
                GetDlgItem(IDC_LIST_DEBTLIMIT)->EnableWindow(FALSE);
                GetDlgItem(IDC_LIST_DEBTLIMIT)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_STATIC_KL2)->EnableWindow(FALSE);
                GetDlgItem(IDC_STATIC_KL2)->ShowWindow(SW_HIDE);
            }
            else
            {
                FillKL(&kreditlimit);
            }
        }
        else
        {
            GetDlgItem(IDC_LIST_DEBTLIMIT)->EnableWindow(FALSE);
            GetDlgItem(IDC_LIST_DEBTLIMIT)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_KL2)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_KL2)->ShowWindow(SW_HIDE);
            if (!kreditlimit.SelLimit2())
            {
                GetDlgItem(IDC_LIST_DEBTLIMIT)->EnableWindow(TRUE);
                GetDlgItem(IDC_LIST_DEBTLIMIT)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_KL2)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_KL2)->ShowWindow(SW_SHOW);
                FillKL(&kreditlimit);
            }
            if (!kreditlimit.SelLimitMain())
            {
                GetDlgItem(IDC_LIST_DEBTLIMIT)->EnableWindow(TRUE);
                GetDlgItem(IDC_LIST_DEBTLIMIT)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_KL2)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_KL2)->ShowWindow(SW_SHOW);
                FillKL(&kreditlimit);
            }
            else if (!kreditlimit.SelLimit1())
            {
                GetDlgItem(IDC_LIST_DEBTLIMIT)->EnableWindow(TRUE);
                GetDlgItem(IDC_LIST_DEBTLIMIT)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_KL2)->EnableWindow(TRUE);
                GetDlgItem(IDC_STATIC_KL2)->ShowWindow(SW_SHOW);
                FillKL(&kreditlimit);
            }
        }
        EndWaitCursor();
    }
    UpdateData(FALSE);

    return TRUE;
}

void CDKndInf5::FillKL(CKREDITLIMIT* pKL)
{
    CStringArray s;
    s.SetSize(NUM_SPALT_KREDIT);
    s[0].Format("%.2lf", pKL->GetLimit()
                        -pKL->GetSum_debitside()
                        -pKL->GetSum_creditside()
                        -pKL->GetSum_monturnover()
                        -pKL->GetSum_dayturnover()
                        +pKL->GetSum_returns()
                        +pKL->GetSum_goodsreceipt());
    s[1].Format("%.2lf", pKL->GetLimit());
    s[2].Format("%.2lf", pKL->GetSum_debitside());
    s[3].Format("%.2lf", pKL->GetSum_creditside());
    s[4].Format("%.2lf", pKL->GetSum_monturnover());
    s[5].Format("%.2lf", pKL->GetSum_dayturnover());
    s[6].Format("%.2lf", pKL->GetSum_returns());
    s[7].Format("%.2lf", pKL->GetSum_goodsreceipt());
    if (AeGetApp()->IsBG())
    {
        s[8].Format("%d", pKL->GetLimittype());
    }

    CListCtrlHelper::AppendItem(m_LstCtrlDebt, NUM_SPALT_KREDIT, s);
}

//Definition der Tabellenbreite und der Ueberschriften

static COLUMNS_TYPES SpaltenGruppe[] =
{
    0,  "",  80, LVCFMT_RIGHT,
    1,  "", 240, LVCFMT_LEFT,
    2,  "", 160, LVCFMT_LEFT,
    3,  "", 160, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_GRUPPE 4

// CDKndInf6-Dialogfeld

IMPLEMENT_DYNAMIC(CDKndInf6, CPropertyPage)
CDKndInf6::CDKndInf6()
    : CPropertyPageMultiLang(CDKndInf6::IDD)
{
    m_init = FALSE;
    SpaltenGruppe[0].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    SpaltenGruppe[1].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    SpaltenGruppe[2].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    SpaltenGruppe[3].Columns = CResString::ex().getStrTblText(AETXT_STRASSE);
}

CDKndInf6::~CDKndInf6()
{
}

void CDKndInf6::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_TA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_TA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_TA_ORT, m_COrt);
    DDX_Text(pDX, IDC_TA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_TA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_STATIC_TA_ABC, m_CAbc);
    DDX_Text(pDX, IDC_TA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_TA_TELE_KW, m_CTeleKw);
    DDX_Control(pDX, IDC_LIST1, m_LstCtrl1);
    DDX_Control(pDX, IDC_LIST2, m_LstCtrl2);
}


BEGIN_MESSAGE_MAP(CDKndInf6, CPropertyPageMultiLang)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


// CDKndInf6-Meldungshandler

BOOL CDKndInf6::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;
}


BOOL CDKndInf6::OnSetActive()
{
    //Befüllen Property Page KndInfo4
    CPropertyPageMultiLang::OnSetActive( );

    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf6.cpp", "OnSetActive", "Page started");
        m_init = TRUE;

        if (   !CListCtrlHelper::AddColumns(SpaltenGruppe, m_LstCtrl1)
            || !CListCtrlHelper::AddColumns(SpaltenGruppe, m_LstCtrl2) )
        {
            return FALSE;
        }
        // Ausgabe der Listbox fuer Hauptidf
        ppString nameapo;
        ppString ort;
        ppString strasse;
        CStringArray s;
        s.SetSize(NUM_SPALT_GRUPPE);
        CCHAINCUSTOMERS cstchain;

        BeginWaitCursor();
        cstchain.SetVertriebszentrumnr(m_VzNr);
        cstchain.SetMaincstno(m_MainNr);
        for (;;)
        {
            if (cstchain.SelList() != SRV_OK)
                break;
            s[0].Format("%d", cstchain.GetKundennr());
            cstchain.GetNameapo(nameapo);
            s[1] = nameapo;
            cstchain.GetOrt(ort);
            s[2] = ort;
            cstchain.GetStrasse(strasse);
            s[3] = strasse;

            if (!CListCtrlHelper::AppendItem(m_LstCtrl2, NUM_SPALT_GRUPPE, s))
            {
                return FALSE;
            }
        }
        EndWaitCursor();
    }
    UpdateData(FALSE);

    return TRUE;
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDKndInf6::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        CKndInf dlgKndInf;
        int pos = m_LstCtrl1.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString CStr = m_LstCtrl1.GetItemText(pos, 0);
            dlgKndInf.SetIdfNr(atol(CStr));
            dlgKndInf.SetKndVz(m_VzNr);
            dlgKndInf.DoModal();
        }
        else
        {
            pos = m_LstCtrl2.GetNextItem(-1, LVNI_SELECTED);
            if (pos >= 0)
            {
                CString CStr = m_LstCtrl2.GetItemText(pos, 0);
                dlgKndInf.SetIdfNr(atol(CStr));
                dlgKndInf.SetKndVz(m_VzNr);
                dlgKndInf.DoModal();
            }
        }
    }
    return 1L;  //Message wird nicht weitergeleitet
}

//Definition der Tabellenbreite und der Ueberschriften

static COLUMNS_TYPES SpaltenKonto[] =
{
    0,  "",  70, LVCFMT_RIGHT,
    1,  "", 110, LVCFMT_RIGHT,
    2,  "",  30, LVCFMT_LEFT,
    3,  "",  30, LVCFMT_LEFT,
    4,  "",  30, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_KONTO 5

// CDKndInf7-Dialogfeld

IMPLEMENT_DYNAMIC(CDKndInf7, CPropertyPage)
CDKndInf7::CDKndInf7()
    : CPropertyPageMultiLang(CDKndInf7::IDD)
    , m_tVon(0)
    , m_tBis(0)
{
    m_init = FALSE;
    SpaltenKonto[0].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    SpaltenKonto[1].Columns = CResString::ex().getStrTblText(AETXT_WERT);
    SpaltenKonto[2].Columns = CResString::ex().getStrTblText(AETXT_ART);
    SpaltenKonto[3].Columns = CResString::ex().getStrTblText(AETXT_ZAHLUNG);
    SpaltenKonto[4].Columns = CResString::ex().getStrTblText(AETXT_BEZAHLT);
}

CDKndInf7::~CDKndInf7()
{
}

void CDKndInf7::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_TA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_TA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_TA_ORT, m_COrt);
    DDX_Text(pDX, IDC_TA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_TA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_STATIC_TA_ABC, m_CAbc);
    DDX_Text(pDX, IDC_TA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_TA_TELE_KW, m_CTeleKw);
    DDX_Control(pDX, IDC_LIST1, m_LstCtrl1);
    DDX_Control(pDX, IDC_LIST2, m_LstCtrl2);
    DDX_Control(pDX, IDC_DATETIMEPICKER_VON, m_DT_Von);
    DDX_Control(pDX, IDC_DATETIMEPICKER_BIS, m_DT_Bis);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_VON, m_tVon);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIS, m_tBis);
}


BEGIN_MESSAGE_MAP(CDKndInf7, CPropertyPageMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_ANZ, OnBnClickedButtonAnz)
END_MESSAGE_MAP()


// CDKndInf7-Meldungshandler

BOOL CDKndInf7::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;
}


BOOL CDKndInf7::OnSetActive()
{
    //Befüllen Property Page KndInfo7
    CPropertyPageMultiLang::OnSetActive( );

    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf7.cpp", "OnSetActive", "Page started");
        m_init = TRUE;
        CTime end = CTimeFromDateLongMinTime(m_TMZeit.DATUM);
        CTime start(2001, 1, 1, 0, 0, 0);
        m_DT_Von.SetRange(&start, &end);
        m_DT_Von.SetTime(&start);
        m_DT_Bis.SetRange(&start, &end);
        m_DT_Bis.SetTime(&end);

        if (   !CListCtrlHelper::AddColumns(SpaltenKonto, m_LstCtrl1)
            || !CListCtrlHelper::AddColumns(SpaltenKonto, m_LstCtrl2) )
        {
            return FALSE;
        }
        FillLists(20010101, m_TMZeit.DATUM);
    }
    UpdateData(FALSE);
    return TRUE;
}

void CDKndInf7::FillLists(long von,long bis)
{
    // Ausgabe der Listbox fuer Hauptidf
    double sumown = 0;
    double sumgrp = 0;
    ppString nameapo;
    ppString ort;
    ppString strasse;

    CCSTDISCACC disc;
    disc.SetBranchno(m_VzNr);
    disc.SetCustomerno(m_KndNr);
    disc.SetDatum(von);
    disc.SetDate(bis);
    m_LstCtrl1.DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        if (disc.SelListCst() != SRV_OK)
            break;

        if (!FillList(disc, sumown, m_LstCtrl1))
        {
            return;
        }
    }
    if (m_MainNr == 0)
    {
        GetDlgItem(IDC_STATIC_GRP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LIST2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SUM_GRP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SUM_GES)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_SUM_GRP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_SUM_GES)->ShowWindow(SW_HIDE);
    }
    else
    {
        disc.SetDatum(von);
        disc.SetDate(bis);
        disc.SetMaincstno(m_MainNr);
        m_LstCtrl2.DeleteAllItems();
        for (;;)
        {
            if (disc.SelListGrp() != SRV_OK)
                break;

            if (!FillList(disc, sumgrp, m_LstCtrl2))
            {
                return;
            }
        }
    }
    EndWaitCursor();

    CString cSumOwn;
    cSumOwn.Format("%0.2lf", sumown);
    GetDlgItem(IDC_EDIT_SUM_OWN)->SetWindowText(cSumOwn);
    CString cSumGrp;
    cSumGrp.Format("%0.2lf", sumgrp);
    GetDlgItem(IDC_EDIT_SUM_GRP)->SetWindowText(cSumGrp);
    CString cSumGes;
    cSumGes.Format("%0.2lf", sumown+sumgrp);
    GetDlgItem(IDC_EDIT_SUM_GES)->SetWindowText(cSumGes);
}

/*static*/
bool CDKndInf7::FillList(CCSTDISCACC& disc, double& sum, CListCtrl& listCtrl)
{
    if (disc.GetBalance() == 0)
    {
        return true;
    }

    CStringArray s;
    s.SetSize(NUM_SPALT_KONTO);

    s[0] = DDMMYYYYStringFromDateLong(disc.GetDate());

    ppString vtyp;;
    disc.GetVouchertyp(vtyp);
    s[2] = vtyp;

    if (disc.GetPaymentarget() > 0)
    {
        CTime Rechnung = CTimeFromDateLongMinTime(disc.GetDate());
        CTimeSpan Ziel(disc.GetPaymentarget(), 0, 0, 0);
        Rechnung += Ziel;
        s[3].Format("%02d.%02d.%04d", Rechnung.GetDay(), Rechnung.GetMonth(), Rechnung.GetYear());
    }
    else
    {
        s[3].Empty();
    }

    s[4].Format("%0.2lf", disc.GetInvoicepaid());

    if (vtyp != "GU")
    {
        sum += disc.GetBalance();
        s[1].Format("%0.2lf", disc.GetBalance());
    }
    else
    {
        sum -= disc.GetBalance();
        s[1].Format("%0.2lf", disc.GetBalance() * (-1));
    }

    if (!CListCtrlHelper::AppendItem(listCtrl, NUM_SPALT_KONTO, s))
    {
        return false;
    }
    return true;
}

void CDKndInf7::OnBnClickedButtonAnz()
{
    UpdateData();
    if (m_tVon.GetTime() > m_tBis.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_VON));
        return;
    }
    long von = m_tVon.GetYear() * 10000 +
               m_tVon.GetMonth() * 100 +
               m_tVon.GetDay();
    long bis = m_tBis.GetYear() * 10000 +
               m_tBis.GetMonth() * 100 +
               m_tBis.GetDay();
    FillLists(von, bis);
    UpdateData(FALSE);
}

//Definition der Tabellenbreite und der Ueberschriften

static COLUMNS_TYPES SpaltenOPO[] =
{
    0,  "", 75, LVCFMT_LEFT,
    1,  "", 70, LVCFMT_LEFT,
    2,  "", 70, LVCFMT_LEFT,
    3,  "", 90, LVCFMT_RIGHT,
    4,  "", 90, LVCFMT_RIGHT,
    5,  "", 90, LVCFMT_RIGHT,
    -1, "",  0, 0
};

#define NUM_SPALT_OPO 6


// CDKndInf8-Dialogfeld

IMPLEMENT_DYNAMIC(CDKndInf8, CPropertyPage)
CDKndInf8::CDKndInf8()
    : CPropertyPageMultiLang(CDKndInf8::IDD)
{
    m_init = FALSE;
    SpaltenOPO[0].Columns = CResString::ex().getStrTblText(AETXT_RECHNUNG_NR);
    SpaltenOPO[1].Columns = CResString::ex().getStrTblText(AETXT_RECH_DATE);
    SpaltenOPO[2].Columns = CResString::ex().getStrTblText(AETXT_ZAHL_DATE);
    SpaltenOPO[3].Columns = CResString::ex().getStrTblText(AETXT_BETRAG);
    SpaltenOPO[4].Columns = CResString::ex().getStrTblText(AETXT_BEZAHLT);
    SpaltenOPO[5].Columns = CResString::ex().getStrTblText(AETXT_RR_OFFEN);
}

CDKndInf8::~CDKndInf8()
{
}

void CDKndInf8::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_TA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_TA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_TA_ORT, m_COrt);
    DDX_Text(pDX, IDC_TA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_TA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_STATIC_TA_ABC, m_CAbc);
    DDX_Text(pDX, IDC_TA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_TA_TELE_KW, m_CTeleKw);
    DDX_Control(pDX, IDC_LIST1, m_LstCtrl1);
    DDX_Control(pDX, IDC_LIST2, m_LstCtrl2);
    DDX_Control(pDX, IDC_LIST3, m_LstCtrl3);
    DDX_Control(pDX, IDC_EDIT_SUM_OFFEN, m_edit_sum_offen);
    DDX_Control(pDX, IDC_EDIT_SUM_DUE, m_edit_sum_due);
    DDX_Control(pDX, IDC_EDIT_SUM_OVERDUE, m_edit_sum_overdue);
    DDX_Control(pDX, IDC_EDIT_SUM_OFFEN_ZZ, m_edit_sum_offen_zz);
    DDX_Control(pDX, IDC_EDIT_SUM_DUE_ZZ, m_edit_sum_due_zz);
    DDX_Control(pDX, IDC_EDIT_SUM_OVERDUE_ZZ, m_edit_sum_overdue_zz);
    DDX_Control(pDX, IDC_EDIT_SUM_OFFEN_CASH, m_edit_sum_offen_cash);
    DDX_Control(pDX, IDC_EDIT_SUM_DUE_CASH, m_edit_sum_due_cash);
    DDX_Control(pDX, IDC_EDIT_SUM_OVERDUE_CASH, m_edit_sum_overdue_cash);
}


BEGIN_MESSAGE_MAP(CDKndInf8, CPropertyPageMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
    ON_BN_CLICKED(IDC_BUTTON_DUE, OnButtonDue)
    ON_BN_CLICKED(IDC_BUTTON_OVERDUE, OnButtonOverdue)
END_MESSAGE_MAP()


// CDKndInf7-Meldungshandler

BOOL CDKndInf8::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;
}


BOOL CDKndInf8::OnSetActive()
{
    //Befüllen Property Page KndInfo8
    CPropertyPageMultiLang::OnSetActive( );

    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf8.cpp", "OnSetActive", "Page started");
        m_init = TRUE;
        CFont*  pobjCFont;
        CFont  objCFont1;
        CFont  objCFont2;
        CFont  objCFont3;
        CFont  objCFont4;
        CFont  objCFont5;
        CFont  objCFont6;
        CFont  objCFont7;
        CFont  objCFont8;
        CFont  objCFont9;
        LOGFONT lf;

        pobjCFont = m_edit_sum_offen.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont1.CreateFontIndirect(&lf);
        m_edit_sum_offen.SetFont(&objCFont1);

        pobjCFont = m_edit_sum_due.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont2.CreateFontIndirect(&lf);
        m_edit_sum_due.SetFont(&objCFont2);

        pobjCFont = m_edit_sum_overdue.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont3.CreateFontIndirect(&lf);
        m_edit_sum_overdue.SetFont(&objCFont3);

        pobjCFont = m_edit_sum_offen_zz.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont4.CreateFontIndirect(&lf);
        m_edit_sum_offen_zz.SetFont(&objCFont4);

        pobjCFont = m_edit_sum_due_zz.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont5.CreateFontIndirect(&lf);
        m_edit_sum_due_zz.SetFont(&objCFont5);

        pobjCFont = m_edit_sum_overdue_zz.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont6.CreateFontIndirect(&lf);
        m_edit_sum_overdue_zz.SetFont(&objCFont6);

        pobjCFont = m_edit_sum_offen_cash.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont7.CreateFontIndirect(&lf);
        m_edit_sum_offen_cash.SetFont(&objCFont7);

        pobjCFont = m_edit_sum_due_cash.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont8.CreateFontIndirect(&lf);
        m_edit_sum_due_cash.SetFont(&objCFont8);

        pobjCFont = m_edit_sum_overdue_cash.GetFont();
        pobjCFont->GetLogFont(&lf);
        lf.lfWeight *= 2;
        objCFont9.CreateFontIndirect(&lf);
        m_edit_sum_overdue_cash.SetFont(&objCFont9);

        if (   !CListCtrlHelper::AddColumns(SpaltenOPO, m_LstCtrl1)
            || !CListCtrlHelper::AddColumns(SpaltenOPO, m_LstCtrl2)
            || !CListCtrlHelper::AddColumns(SpaltenOPO, m_LstCtrl3) )
        {
            return FALSE;
        }
        // Ausgabe der Listboxen
        double sumopenzz = 0;
        double sumduezz = 0;
        double sumoverduezz = 0;
        double sumopen = 0;
        double sumdue = 0;
        double sumoverdue = 0;
        ppString invoiceno;
        ppString ort;
        ppString strasse;
        ppString vtyp;;
        CStringArray s;
        s.SetSize(NUM_SPALT_OPO);
        CPAYMENTLIST paylist;
        paylist.SetBranchno(m_VzNr);
        paylist.SetCustomerno(m_KndNr);
        BeginWaitCursor();
        double testbetrag;
        for (;;)
        {
            if (paylist.SelList() != SRV_OK)
                break;
            s[1] = DDMMYYYYStringFromDateLong(paylist.GetInvoicedate());
            paylist.GetInvoicenumber(invoiceno);
            s[0] = invoiceno;
            s[2] = DDMMYYYYStringFromDateLong(paylist.GetPaymentdate());
            testbetrag = paylist.GetTotalinvoiceamount();
            testbetrag = paylist.GetOpeninvoiceamount();
            testbetrag = paylist.GetPaidinvoiceamount();
            s[3].Format("%0.2lf", paylist.GetTotalinvoiceamount());
            s[4].Format("%0.2lf", paylist.GetPaidinvoiceamount());
            s[5].Format("%0.2lf", paylist.GetOpeninvoiceamount());
            if (paylist.GetPaymentdate() > m_TMZeit.DATUM)
            {
                if (paylist.GetPaymentspec() == 'Z')
                {
                    sumopenzz += paylist.GetOpeninvoiceamount();
                }
                else
                {
                    sumopen += paylist.GetOpeninvoiceamount();
                }
                WriteList1(s);
            }
            else if (paylist.GetPaymentdate() < m_TMZeit.DATUM)
            {
                if (paylist.GetPaymentspec() == 'Z')
                {
                    sumopenzz += paylist.GetOpeninvoiceamount();
                    sumoverduezz += paylist.GetOpeninvoiceamount();
                }
                else
                {
                    sumopen += paylist.GetOpeninvoiceamount();
                    sumoverdue += paylist.GetOpeninvoiceamount();
                }
                WriteList1(s);
                WriteList3(s);
            }
            else
            {
                if (paylist.GetPaymentspec() == 'Z')
                {
                    sumopenzz += paylist.GetOpeninvoiceamount();
                    sumduezz += paylist.GetOpeninvoiceamount();
                }
                else
                {
                    sumopen += paylist.GetOpeninvoiceamount();
                    sumdue += paylist.GetOpeninvoiceamount();
                }
                WriteList1(s);
                WriteList2(s);
            }
        }
        EndWaitCursor();

        GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LIST3)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_KIND)->SetWindowText(CResString::ex().getStrTblText(AETXT_ALL_OPEN));

        CString cSumme;
        cSumme.Format("%0.2lf", sumopenzz + sumopen);
        GetDlgItem(IDC_EDIT_SUM_OFFEN)->SetWindowText(cSumme);
        cSumme.Format("%0.2lf", sumduezz + sumdue);
        GetDlgItem(IDC_EDIT_SUM_DUE)->SetWindowText(cSumme);
        cSumme.Format("%0.2lf", sumoverduezz + sumoverdue);
        GetDlgItem(IDC_EDIT_SUM_OVERDUE)->SetWindowText(cSumme);
        cSumme.Format("%0.2lf", sumopenzz);
        GetDlgItem(IDC_EDIT_SUM_OFFEN_ZZ)->SetWindowText(cSumme);
        cSumme.Format("%0.2lf", sumduezz);
        GetDlgItem(IDC_EDIT_SUM_DUE_ZZ)->SetWindowText(cSumme);
        cSumme.Format("%0.2lf", sumoverduezz);
        GetDlgItem(IDC_EDIT_SUM_OVERDUE_ZZ)->SetWindowText(cSumme);
        cSumme.Format("%0.2lf", sumopen);
        GetDlgItem(IDC_EDIT_SUM_OFFEN_CASH)->SetWindowText(cSumme);
        cSumme.Format("%0.2lf", sumdue);
        GetDlgItem(IDC_EDIT_SUM_DUE_CASH)->SetWindowText(cSumme);
        cSumme.Format("%0.2lf", sumoverdue);
        GetDlgItem(IDC_EDIT_SUM_OVERDUE_CASH)->SetWindowText(cSumme);
    }
    UpdateData(FALSE);
    return TRUE;
}

void CDKndInf8::OnButtonOpen()
{
    GetDlgItem(IDC_LIST1)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_LIST2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LIST3)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_KIND)->SetWindowText(CResString::ex().getStrTblText(AETXT_ALL_OPEN));
}

void CDKndInf8::OnButtonDue()
{
    GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LIST2)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_LIST3)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_KIND)->SetWindowText(CResString::ex().getStrTblText(AETXT_ALL_DUE));
}

void CDKndInf8::OnButtonOverdue()
{
    GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LIST2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LIST3)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_KIND)->SetWindowText(CResString::ex().getStrTblText(AETXT_ALL_OVERDUE));
}

BOOL CDKndInf8::WriteList1(CStringArray &s)
{
    if (!CListCtrlHelper::AppendItem(m_LstCtrl1, NUM_SPALT_OPO, s))
    {
        return FALSE;
    }
    return TRUE;
}

BOOL CDKndInf8::WriteList2(CStringArray &s)
{
    if (!CListCtrlHelper::AppendItem(m_LstCtrl2, NUM_SPALT_OPO, s))
    {
        return FALSE;
    }
    return TRUE;
}

BOOL CDKndInf8::WriteList3(CStringArray &s)
{
    if (!CListCtrlHelper::AppendItem(m_LstCtrl3, NUM_SPALT_OPO, s))
    {
        return FALSE;
    }
    return TRUE;
}

//Definition der Tabellenbreite und der Ueberschriften

static COLUMNS_TYPES SpaltenL5[] =
{
    0,  "",  75, LVCFMT_RIGHT,
    1,  "", 200, LVCFMT_LEFT,
    2,  "",  90, LVCFMT_RIGHT,
    3,  "",  90, LVCFMT_RIGHT,
    -1, "",   0, 0
};

#define NUM_SPALT_L5 4

// CDKndInf9-Dialogfeld

IMPLEMENT_DYNAMIC(CDKndInf9, CPropertyPage)
CDKndInf9::CDKndInf9()
    : CPropertyPageMultiLang(CDKndInf9::IDD)
{
    m_init = FALSE;
    SpaltenL5[0].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    SpaltenL5[1].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    SpaltenL5[2].Columns = CResString::ex().getStrTblText(AETXT_PREIS_FV);
    SpaltenL5[3].Columns = CResString::ex().getStrTblText(AETXT_PREIS_KK);
}

CDKndInf9::~CDKndInf9()
{
}

void CDKndInf9::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_TA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_TA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_TA_ORT, m_COrt);
    DDX_Text(pDX, IDC_TA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_TA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_STATIC_TA_ABC, m_CAbc);
    DDX_Text(pDX, IDC_TA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_TA_TELE_KW, m_CTeleKw);
    DDX_Control(pDX, IDC_LIST1, m_LstCtrl1);
}


BEGIN_MESSAGE_MAP(CDKndInf9, CPropertyPageMultiLang)
END_MESSAGE_MAP()


// CDKndInf9-Meldungshandler

BOOL CDKndInf9::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;
}


BOOL CDKndInf9::OnSetActive()
{
    //Befüllen Property Page KndInfo9
    CPropertyPageMultiLang::OnSetActive( );

    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf9.cpp", "OnSetActive", "Page started");
        m_init = TRUE;
        CStringArray s;
        s.SetSize(NUM_SPALT_L5);
        CLISTE5 liste5;
        ppString Name;
        long lartikelnr = -1;
        double dpreis;
        double dTax;
        char cStd;

        if (!CListCtrlHelper::AddColumns(SpaltenL5, m_LstCtrl1))
        {
            return FALSE;
        }
        liste5.SetBranchno(m_VzNr);
        liste5.SetCustomerno(m_KndNr);
        m_LstCtrl1.DeleteAllItems();
        BeginWaitCursor();
        for (;;)
        {
            if (liste5.SelList() != SRV_OK)
                break;
            if (lartikelnr != liste5.GetArticleno())
            {
                s[0].Format("%d", liste5.GetArticleno());
                s[1] = liste5.GetArtikel_langname(Name);
                s[2].Empty();
                s[3].Empty();
            }
            dpreis = liste5.GetPreisekapo();
            AeGetApp()->GetTaxRates(liste5.GetTaxlevel(), cStd, dTax);
            dpreis = dpreis * (100 + dTax) / 100;
            if (liste5.GetPreis_typ() == 0)
            {
                s[2].Format("%0.2lf", dpreis);
            }
            else
            {
                s[3].Format("%0.2lf", dpreis);
            }
            if (lartikelnr != liste5.GetArticleno())
            {
                if (!CListCtrlHelper::AppendItem(m_LstCtrl1, NUM_SPALT_L5, s))
                {
                    return FALSE;
                }
            }
            else
            {
                if (liste5.GetPreis_typ() == 0)
                {
                    m_LstCtrl1.SetItemText(0, 2, s[2]);
                }
                else
                {
                    m_LstCtrl1.SetItemText(0, 3, s[3]);
                }
            }
            lartikelnr = liste5.GetArticleno();
        }
    }
    UpdateData(FALSE);
    return TRUE;
}

//Definition der Tabellenbreite und der Ueberschriften

static COLUMNS_TYPES SpaltenAufArt[] =
{
    0,  "",  80, LVCFMT_LEFT,
    1,  "",  80, LVCFMT_LEFT,
    2,  "", 100, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_AART 3

static COLUMNS_TYPES SpaltenOrders[] =
{
    0,  "",  50, LVCFMT_LEFT,
    1,  "",  70, LVCFMT_LEFT,
    2,  "",  50, LVCFMT_LEFT,
    3,  "", 120, LVCFMT_LEFT,
    4,  "",  45, LVCFMT_LEFT,
    5,  "",  45, LVCFMT_LEFT,
    6,  "",  50, LVCFMT_LEFT,
    7,  "",  50, LVCFMT_LEFT,
    8,  "",  80, LVCFMT_LEFT,
    9,  "",  70, LVCFMT_LEFT,
    10, "",  70, LVCFMT_LEFT,
    11, "",  70, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_ORDERS 12

#define COL_BF_ID   0
#define COL_BF_MAIN 1
#define COL_BF_TILL 2
#define COL_BF_VB   3
#define COL_BF_BTM  4
#define COL_BF_KK   5
#define COL_BF_K08  6
#define COL_BF_K20  7
#define COL_BF_RT   8

//Listcontrol-Spalten-Typ für Bestellfenster
static COLUMNS_TYPES SpaltenBFToday[] =
{
    COL_BF_ID,   "", 53, LVCFMT_LEFT,
    COL_BF_MAIN, "", 42, LVCFMT_RIGHT,
    COL_BF_TILL, "", 42, LVCFMT_RIGHT,
    COL_BF_VB,   "", 32, LVCFMT_RIGHT,
    COL_BF_BTM,  "", 36, LVCFMT_RIGHT,
    COL_BF_KK,   "", 32, LVCFMT_RIGHT,
    COL_BF_K08,  "", 36, LVCFMT_RIGHT,
    COL_BF_K20,  "", 36, LVCFMT_RIGHT,
    COL_BF_RT,   "", 32, LVCFMT_RIGHT,
    -1,          "",  0, 0
};

#define NUM_SPALT_BFTODAY 9

#define COL_VDAT_TYP    0
#define COL_VDAT_TEXT   1

//Listcontrol-Spalten-Typ für Vertragsdaten
static COLUMNS_TYPES SpaltenVDat[] =
{
    COL_VDAT_TYP,  "", 200, LVCFMT_LEFT,
    COL_VDAT_TEXT, "", 200, LVCFMT_LEFT,
    -1,            "",   0, 0
};

#define NUM_SPALT_VDAT 2

// CDKndInf10-Dialogfeld

IMPLEMENT_DYNAMIC(CDKndInf10, CPropertyPage)
CDKndInf10::CDKndInf10()
    : CPropertyPageMultiLang(CDKndInf10::IDD)
{
    m_init = FALSE;
    SpaltenAufArt[0].Columns = CResString::ex().getStrTblText(AETXT_AUFTRAGSART);
    SpaltenAufArt[1].Columns = CResString::ex().getStrTblText(AETXT_VEREINBART);
    SpaltenAufArt[2].Columns = CResString::ex().getStrTblText(AETXT_FREE_LABEL);

    SpaltenOrders[0].Columns = CResString::ex().getStrTblText(AETXT_AUF_NR);
    SpaltenOrders[1].Columns = CResString::ex().getStrTblText(AETXT_ANZ_POS);
    SpaltenOrders[2].Columns = CResString::ex().getStrTblText(AETXT_TOURID);
    SpaltenOrders[3].Columns = CResString::ex().getStrTblText(AETXT_FREE_LABEL);
    SpaltenOrders[4].Columns = CResString::ex().getStrTblText(AETXT_HBZ);
    SpaltenOrders[5].Columns = CResString::ex().getStrTblText(AETXT_BFE);
    SpaltenOrders[6].Columns = CResString::ex().getStrTblText(AETXT_BF_TOUR);
    SpaltenOrders[7].Columns = CResString::ex().getStrTblText(AETXT_SENDID);
    SpaltenOrders[8].Columns = CResString::ex().getStrTblText(AETXT_POS_SEND);
    SpaltenOrders[9].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    SpaltenOrders[10].Columns = CResString::ex().getStrTblText(IDS_TIME);
    SpaltenOrders[11].Columns = CResString::ex().getStrTblText(AETXT_ORIGIN);

    SpaltenBFToday[COL_BF_ID].Columns = CResString::ex().getStrTblText(AETXT_TOURID);
    SpaltenBFToday[COL_BF_MAIN].Columns = CResString::ex().getStrTblText(AETXT_HBZ);
    SpaltenBFToday[COL_BF_TILL].Columns = CResString::ex().getStrTblText(AETXT_BFE);
    SpaltenBFToday[COL_BF_VB].Columns = CResString::ex().getStrTblText(AETXT_VB);
    SpaltenBFToday[COL_BF_BTM].Columns = CResString::ex().getStrTblText(AETXT_BTM);
    SpaltenBFToday[COL_BF_KK].Columns = CResString::ex().getStrTblText(AETXT_KK);
    SpaltenBFToday[COL_BF_K08].Columns = CResString::ex().getStrTblText(AETXT_K08);
    SpaltenBFToday[COL_BF_K20].Columns = CResString::ex().getStrTblText(AETXT_K20);
    SpaltenBFToday[COL_BF_RT].Columns = CResString::ex().getStrTblText(AETXT_RT);

    SpaltenVDat[0].Columns = CResString::ex().getStrTblText(AETXT_TYP);
    SpaltenVDat[1].Columns = CResString::ex().getStrTblText(AETXT_WERT);
}

CDKndInf10::~CDKndInf10()
{
}

void CDKndInf10::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_TA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_TA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_TA_ORT, m_COrt);
    DDX_Text(pDX, IDC_TA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_TA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_STATIC_TA_ABC, m_CAbc);
    DDX_Text(pDX, IDC_TA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_TA_TELE_KW, m_CTeleKw);
    DDX_Control(pDX, IDC_LIST_AART, m_LstCtrlAArt);
    DDX_Control(pDX, IDC_LIST_ORDERS, m_LstCtrlOrders);
    DDX_Control(pDX, IDC_LIST_BF_TODAY, m_LstCtrlBFToday);
    DDX_Control(pDX, IDC_LIST_VDAT, m_LstCtrlVDat);
}


BEGIN_MESSAGE_MAP(CDKndInf10, CPropertyPageMultiLang)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDKndInf10-Meldungshandler

BOOL CDKndInf10::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;
}


BOOL CDKndInf10::OnSetActive()
{
    //Befüllen Property Page KndInfo7
    CPropertyPageMultiLang::OnSetActive( );

    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf10.cpp", "OnSetActive", "Page started");
        m_init = TRUE;
        CStringArray s;
        CMSV3INFO msv3;
        CMSV3ORDERINFO msv3orders;
        CMSV3EINSTELLUNGEN msv3adjust;
        CMSV3TOURINFO tour;
        CMSV3CSTINFO msv3cst;
        ppString AArt;
        ppString Label;
        ppString TourID;
        ppString BFTourID;
        ppString Origindevice;
        ppString MSV3InfoDescription;
        ppString MSV3CstInfoValue ;

        //MSV3 Auftragsarten
        s.SetSize(NUM_SPALT_AART);

        if (!CListCtrlHelper::AddColumns(SpaltenAufArt, m_LstCtrlAArt))
        {
            return FALSE;
        }
        msv3.SetKundennr(m_KndNr);
        msv3.SetVertriebszentrumnr(m_VzNr);
        msv3adjust.SetKundennr(m_KndNr);
        msv3adjust.SetVertriebszentrumnr(m_VzNr);
        m_LstCtrlAArt.DeleteAllItems();
        BeginWaitCursor();
        for (;;)
        {
            if (msv3.SelMSV3())
                break;
            s[0] = msv3.GetKdauftragart(AArt);
            if (msv3.GetMsv3vereinbart() == 1)
                s[1] = CResString::ex().getStrTblText(AETXT_JA);
            else s[1] = CResString::ex().getStrTblText(AETXT_NEIN);
            s[2].Format("%d", msv3.GetFreiekennungen());

            if (!CListCtrlHelper::AppendItem(m_LstCtrlAArt, NUM_SPALT_AART, s))
            {
                return FALSE;
            }
        }

        //Now The Orders
        s.SetSize(NUM_SPALT_ORDERS);

        if (!CListCtrlHelper::AddColumns(SpaltenOrders, m_LstCtrlOrders))
        {
            return FALSE;
        }
        msv3orders.SetKundennr(m_KndNr);
        msv3orders.SetVertriebszentrumnr(m_VzNr);
        m_LstCtrlOrders.DeleteAllItems();
        for (;;)
        {
            if (msv3orders.SelMSV3Orders())
                break;
            s[0].Format("%d", msv3orders.GetKdauftragnr());
            s[1].Format("%d", msv3orders.GetAnzpos());
            s[2] = msv3orders.GetTourid(TourID);
            s[3] = msv3orders.GetOrderlabel(Label);
            s[4].Format("%02d:%02d", msv3orders.GetMaintime() / 100, msv3orders.GetMaintime() % 100);
            s[5].Format("%02d:%02d", msv3orders.GetTotime() / 100, msv3orders.GetTotime() % 100);
            s[6] = msv3orders.GetBftour(BFTourID);
            s[7].Format("%d", msv3orders.GetSendid());
            s[8].Format("%d", msv3orders.GetPostransfered());
            s[9] = DDMMYYYYStringFromDateLong(msv3orders.GetDatum());
            s[10].Format("%02d:%02d:%02d", msv3orders.GetZeit_von() / 10000000, msv3orders.GetZeit_von() / 100000 % 100, msv3orders.GetZeit_von() / 1000 % 100);
            s[11] = msv3orders.GetOrigindevice(Origindevice);

            if (!CListCtrlHelper::AppendItem(m_LstCtrlOrders, NUM_SPALT_ORDERS, s))
            {
                return FALSE;
            }
        }

        //Now The Tours
        s.SetSize(NUM_SPALT_BFTODAY);

        if (!CListCtrlHelper::AddColumns(SpaltenBFToday, m_LstCtrlBFToday))
        {
            return FALSE;
        }
        tour.SetCustomerno(m_KndNr);
        tour.SetBranchno(m_VzNr);
        m_LstCtrlBFToday.DeleteAllItems();
        CString cTourID;
        for (;;)
        {
            if (tour.SelBFToday())
                break;
            cTourID = tour.GetTourid(TourID);
            s[COL_BF_ID].Format("%.2s:%.2s/%.2s", cTourID.Left(2).GetString(), cTourID.Mid(2, 2).GetString(), cTourID.Right(2).GetString());
            s[COL_BF_MAIN].Format("%d:%02d", tour.GetMaintime() / 100, tour.GetMaintime() % 100);
            s[COL_BF_TILL].Format("%d:%02d", tour.GetTotime() / 100, tour.GetTotime() % 100);
            if (tour.GetIstverbundtour() == '1')
                s[COL_BF_VB] = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else
                s[COL_BF_VB].Empty();
            if (tour.GetIsbtm() == 1)
                s[COL_BF_BTM] = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else
                s[COL_BF_BTM].Empty();
            if (tour.GetIskk() == 1)
                s[COL_BF_KK] = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else
                s[COL_BF_KK].Empty();
            if (tour.GetIsk08() == 1)
                s[COL_BF_K08] = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else
                s[COL_BF_K08].Empty();
            if (tour.GetIsk20() == 1)
                s[COL_BF_K20] = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else
                s[COL_BF_K20].Empty();
            if (tour.GetReturnstour() == 1)
                s[COL_BF_RT] = CResString::ex().getStrTblText(AETXT_KZ_JA);
            else
                s[COL_BF_RT].Empty();

            if (!CListCtrlHelper::AppendItem(m_LstCtrlBFToday, NUM_SPALT_BFTODAY, s))
            {
                return FALSE;
            }
        }

        //Now The Vertragsdaten
        s.SetSize(NUM_SPALT_VDAT);

        if (!CListCtrlHelper::AddColumns(SpaltenVDat, m_LstCtrlVDat))
        {
            return FALSE;
        }
        msv3cst.SetCustomerno(m_KndNr);
        msv3cst.SetBranchno(m_VzNr);
        m_LstCtrlVDat.DeleteAllItems();
        int found = 0;
        for (;;)
        {
            if (msv3cst.SelCstInfo())
                break;
            ++found;
            s[COL_VDAT_TYP] = msv3cst.GetMsv3infodescription(MSV3InfoDescription);
            s[COL_VDAT_TEXT] = msv3cst.GetMsv3cstinfovalue(MSV3CstInfoValue);

            if (!CListCtrlHelper::AppendItem(m_LstCtrlVDat, NUM_SPALT_VDAT, s))
            {
                return FALSE;
            }
        }
        if (found > 0)
        {
            GetDlgItem(IDC_STATIC_VDAT)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_VDAT)->EnableWindow(TRUE);
            GetDlgItem(IDC_LIST_VDAT)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_LIST_VDAT)->EnableWindow(TRUE);
        }

        //Now The Adjustments
        msv3adjust.SetKundennr(m_KndNr);
        msv3adjust.SetVertriebszentrumnr(m_VzNr);
        if (!msv3adjust.SelAdjustments())   //kanns nicht geben
        {
            if (msv3adjust.GetSkdauftragzusammen() == '1')
            {
                GetDlgItem(IDC_STATIC_ZUSAMMEN)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_ZUSAMMEN)->EnableWindow(TRUE);
            }
            if (msv3adjust.GetXmlinfolevel() == '1')
            {
                GetDlgItem(IDC_STATIC_INFOLEVEL1)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_INFOLEVEL1)->EnableWindow(TRUE);
            }
            else if (msv3adjust.GetXmlinfolevel() == '2')
            {
                GetDlgItem(IDC_STATIC_INFOLEVEL2)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_INFOLEVEL2)->EnableWindow(TRUE);
            }
            else if (msv3adjust.GetXmlinfolevel() == '3')
            {
                GetDlgItem(IDC_STATIC_INFOLEVEL3)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_INFOLEVEL3)->EnableWindow(TRUE);
            }
            else if (msv3adjust.GetXmlinfolevel() == '4')
            {
                GetDlgItem(IDC_STATIC_INFOLEVEL4)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_INFOLEVEL4)->EnableWindow(TRUE);
            }
            else
            {
                GetDlgItem(IDC_STATIC_INFOLEVEL0)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_INFOLEVEL0)->EnableWindow(TRUE);
            }
            if (msv3adjust.GetSkdauftragzurueck() == '1')
            {
                GetDlgItem(IDC_STATIC_ZURUECK)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_ZURUECK)->EnableWindow(TRUE);
            }
            if (msv3adjust.GetSkdnoclosedefvb() == '1')
            {
                GetDlgItem(IDC_STATIC_ZURUECK_DEF)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_ZURUECK_DEF)->EnableWindow(TRUE);
            }
            if (msv3adjust.GetSkdnosub() == '1')
            {
                GetDlgItem(IDC_STATIC_NOSUB)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_NOSUB)->EnableWindow(TRUE);
            }
        }
        EndWaitCursor();
        UpdateData(FALSE);
    }
    return TRUE;

}

HBRUSH CDKndInf10::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPageMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_ZUSAMMEN)
        pDC->SetTextColor(RGB(49, 142, 96));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFOLEVEL0)
        pDC->SetTextColor(RGB(0, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFOLEVEL1)
        pDC->SetTextColor(RGB(0, 0, 255));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFOLEVEL2)
        pDC->SetTextColor(RGB(49, 142, 96));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFOLEVEL3)
        pDC->SetTextColor(RGB(200, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_INFOLEVEL4)
        pDC->SetTextColor(RGB(255, 0, 0));

    return hbr;
}

IMPLEMENT_DYNAMIC(CDKndInf11, CPropertyPage)

CDKndInf11::CDKndInf11()
    : CPropertyPageMultiLang(CDKndInf11::IDD)
{
    m_init = FALSE;
}

CDKndInf11::~CDKndInf11()
{
}

void CDKndInf11::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TA_KUNDE_NAME, m_CKundeName);
    DDX_Text(pDX, IDC_TA_APO_NAME, m_CApoName);
    DDX_Text(pDX, IDC_TA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_TA_ORT, m_COrt);
    DDX_Text(pDX, IDC_TA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_TA_IDF_NUMMER, m_CIdfNummer);
    DDX_Text(pDX, IDC_STATIC_TA_ABC, m_CAbc);
    DDX_Text(pDX, IDC_TA_TELE_NR, m_CTeleNr);
    DDX_Text(pDX, IDC_TA_TELE_KW, m_CTeleKw);
    DDX_Control(pDX, IDC_LIST_BINDUNGEN, m_LstCtrlBindungen);
}


BEGIN_MESSAGE_MAP(CDKndInf11, CPropertyPageMultiLang)
END_MESSAGE_MAP()


// CDKndInf11-Meldungshandler

BOOL CDKndInf11::OnInitDialog()
{
    CPropertyPageMultiLang::OnInitDialog();

    return TRUE;
}

BOOL CDKndInf11::OnSetActive()
{
    //Befüllen Property Page KndInfo7
    CPropertyPageMultiLang::OnSetActive( );

    if (!m_init)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DDKndInf11.cpp", "OnSetActive", "Page started");
        m_init = TRUE;

        CCSTBUYINGOPTIONS bind;
        bind.SetKundennr(m_KndNr);
        bind.SetVertriebszentrumnr(m_VzNr);

        BeginWaitCursor();
        bind.SelBuyingOptions();
        EndWaitCursor();

        long lEtartklasse1 = bind.GetEtartklasse1();
        bool bPsycho = bind.GetKzpsychostoffe() == '1';

        if (!m_LstCtrlBindungen.SetActive(lEtartklasse1, bPsycho))
        {
            return FALSE;
        }
    }
    UpdateData(FALSE);
    return TRUE;

}
