// DArtInf.cpp : implementation file
//

#include "stdafx.h"
#include <kndsel.h>
#include "DKndWahl.h"
#include "DArtInf.h"
#include "DArtDef.h"
#include <artsel.h>
#include "verbundbestand.h"
#include <customer.h>
#include "AeFView.h"
#include <artikel.h>
#include "haustab.h"
#include "DStellerAnz.h"
#include "DArtikelkonto.h"
#include <verbundcheck.h>
#include "DInfoListe.h"

/////////////////////////////////////////////////////////////////////////////
// CDArtInf

CDArtInf::CDArtInf()
{
    m_ArtikelNr = -1;
    InitData();
}

CDArtInf::CDArtInf(long ArtikelNr)
{
    m_ArtikelNr = ArtikelNr;
    InitData();
}

void CDArtInf::InitData()
{
    m_lQuota = 0;
    m_lKumqty = 0;
    m_lRest = 0;
    m_sPreistyp = 0;
    m_bCheck = true;
    m_bNoStellerTest = false;
    m_lKndNr = -1;
    m_FilialNr = AeGetApp()->FilialNrActual();
    m_OrgFilialNr = 0;
    m_sImportArticle = 2;

    m_bAufnahme = FALSE;
    m_CBemerkungKond = "";
    m_bNoPriceGroup2 = FALSE;
    m_bNoPriceGroup3 = FALSE;
}

int CDArtInf::DoModal()
{
    char str[81];
    CString Rabatt;

    if (m_ArtikelNr == -1)
    {
        //Definition Artikel
        CDArtDef dlgArtDef;
        dlgArtDef.m_bAufnahme = m_bAufnahme;
        m_bAufnahme = FALSE;
        if (dlgArtDef.DoModal() == IDOK)
        {
            m_bAufnahme = dlgArtDef.m_bAufnahme;
            m_ArtikelNr = dlgArtDef.GetArtNr();
            if (m_bAufnahme) return IDOK;
        }
        else
        {
            m_bAufnahme = FALSE;
            return IDCANCEL;
        }
    }
    m_bAufnahme = FALSE;
    //Ermittlung der Artikelinformationen
    if (m_lKndNr != -1)
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf.cpp", "DoModal", "Dialog started with customer");
        //Check ob Auftragart ohne Kontingentierung
        CString cAArt;
        ((CAeFView *)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
        if (GetOrderType().IsQuota(AeGetApp()->VzNr(), cAArt))
        {
            CARTIKELQUOTA quota;
            if (m_OrgFilialNr != 0)
            {
                quota.SetBranchno(GetOrgFilialNr());
            }
            else
            {
                quota.SetBranchno(GetFilialNr());
            }
            //quota.SetBranchno(GetFilialNr());
            quota.SetArticleno(m_ArtikelNr);
            quota.SetCustomerno(m_lKndNr);
            short sQuotaInheritance = CharToShort(AeGetApp()->QuotaInheritance());
            quota.SetQuotainheritance(sQuotaInheritance);
            if (!quota.CheckQuota())
            {
                m_lQuota = quota.GetQuota();
                //if (m_lQuota > 0)
                {
                    m_bCheck = false;
                    m_lKumqty = quota.GetKumqty();
                    m_lRest = m_lQuota-m_lKumqty;
                }
            }
            quota.CloseCursor();
        }
    }
    else
    {
        AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf.cpp", "DoModal", "Dialog started without customer");
    }

    //Ermittlung der Artikelinformationen
    CARTINF artinf;
    CARTPREIS artpreis;
    CARTVERFALL artverfall;
    CARTALT artalt;
    CARTAESEL artaesel;
    CARTIKELTEXT artikeltext;
    CARTICLETAX articletax;
    artinf.s.ARTIKEL_NR = m_ArtikelNr;
    artpreis.s.ARTIKEL_NR = m_ArtikelNr;
    artverfall.s.ARTIKEL_NR = m_ArtikelNr;
    artverfall.s.FILIALNR = m_FilialNr;
    artinf.s.FILIALNR = m_FilialNr;
    artaesel.s.FILIALNR = m_FilialNr;
    artinf.s.IMPORTARTICLE = m_sImportArticle;   //Entscheidung ob mit oder ohne Importartikel schon vorher gefallen
    AfxGetApp()->BeginWaitCursor();
    artinf.Server(AatartInf_art_nr);
    if (artinf.rc < SRV_OK)
        return IDCANCEL;
    if (!m_bNoStellerTest)
    {
        if (artinf.s.STELLER[0] == 'S')
        {
            AfxGetApp()->EndWaitCursor();
            CDStellerAnz steller;
            steller.m_lArtikelNr = m_ArtikelNr;
            steller.m_sVzNr = m_FilialNr;
            steller.DoModal();
            if (!steller.m_bNosteller)
                return IDCANCEL;
        }
    }

    artpreis.Server(AatartInf_preis);
    if (artpreis.rc < SRV_OK)
        return IDCANCEL;
    artverfall.Server( AatartInf_verfall );
    if (artverfall.rc < SRV_OK)
        return IDCANCEL;
    articletax.SetArtikel_nr(m_ArtikelNr);
    if (articletax.SelTax())
        return IDCANCEL;
    artaesel.s.CODE_TYPE = 0;
    artaesel.s.ARTIKEL_NR = m_ArtikelNr;
    artaesel.s.FILIALNR = m_FilialNr;
    artaesel.s.ETARTKLASSE1 = 65535; //alles - select wird nur fuer KK-Code gebraucht

    artaesel.Server(AatartAa_sel_artnr);
    if (artaesel.rc < SRV_OK)
    {
        artaesel.Server(AatartSel_Preferred);
        AllgEntfSpaces(artaesel.s.ARTICLE_CODE);
        artaesel.s.HEALTHFUNDCODE[0] = '\0';
    }

    int nomore = 0;
    int casa = 0;
    m_iBasis = 0;
    if (AeGetApp()->IsCH())
    {
        char error_msg[81];
        int rc = 0;
        CARTICLEOMG omg;              //OMG-Rabatt
        omg.s.BRANCHNO = GetFilialNr();
        omg.s.ARTICLENO = m_ArtikelNr;
        omg.s.CUSTOMERNO = m_lKndNr;
        for (;;)
        {
            rc = ::ServerNr(PIPE_AE_SRV, AasrvGetOMGRebates, (void*)&omg.s, ARTICLEOMG_BES, ARTICLEOMG_ANZ, error_msg);
            if (rc != 0) break;
            m_ArtInfDiscountData.m_bOMG = true;
            if (m_lKndNr > 0) m_ArtInfDiscountData.m_bOMGCst = true;
            m_ArtInfDiscountData.m_lOmg.push_back(omg.GetStruct());
        }
    }
    if (AeGetApp()->IsNewDiscount() && !m_ArtInfDiscountData.m_bOMGCst)
    {
        m_Discount.SetBranchno(GetFilialNr());
        m_Discount.SetArticleno(m_ArtikelNr);
        m_Discount.SetCustomerno(m_lKndNr);
        m_ArtInfDiscountData.m_lDisc.clear();
        if (   (AeGetApp()->IsRS()
            || (AeGetApp()->IsDE() && (CAeDoc*)((CAeFView*)AeGetApp()->m_pViewEing)->GetDocument()->IsModified())   //für DE Pricing nur wenn Auftrag offen
            || AeGetApp()->IsBG())
            && m_lKndNr != -1)
        {
            char error_msg[81];
            ::buf_default((void*)&m_Discount.s, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
            m_Discount.SetBranchno(GetFilialNr());
            m_Discount.SetArticleno(m_ArtikelNr);
            m_Discount.SetCustomerno(m_lKndNr);
            int rc = 0;
            for (;;)
            {
                rc = ::ServerNr(PIPE_AE_SRV, AasrvGetRebates, (void*)&m_Discount.s, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ, error_msg);
                if (rc != 0) break;
                m_ArtInfDiscountData.m_lDisc.push_back(m_Discount.GetStruct());
                if (m_Discount.GetPaymenttargetno() > 0)
                {
                    casa = 1;
                }
            }
            if (AeGetApp()->IsBG())
            {
                ::buf_default((void*)&m_Discount.s, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
                m_Discount.SetBranchno(GetFilialNr());
                m_Discount.SetArticleno(m_ArtikelNr);
                m_Discount.SetCustomerno(m_lKndNr);
                m_Discount.SetPreis_typ(1);
                for (;;)
                {
                    rc = ::ServerNr(PIPE_AE_SRV, AasrvGetRebates, (void*)&m_Discount.s, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ, error_msg);
                    if (rc != 0) break;
                    m_ArtInfDiscountData.m_lDisc.push_back(m_Discount.GetStruct() );
                }
            }
        }
        else
        {
            if (!AeGetApp()->IsDE())    //für DE Pricing nur Rabatte mit Kunde anzeigen
            {
                for (;;)
                {
                    if (m_lKndNr == -1)
                    {
                        if (m_Discount.SelList() != SRV_OK)
                            break;
                    }
                    else
                    {
                        if (m_Discount.SelListGrp() != SRV_OK)
                            break;
                        else if (m_Discount.GetCustomerno() > 0)
                        {
                            if (m_Discount.GetCustomerno() != m_lKndNr)
                                continue;
                        }
                        // workaround for CH, not clear why additional discounts will not be shown, so prevent hiding for CH
                        if (!AeGetApp()->IsCH())
                        {
                            nomore = 1;
                        }
                    }
                    // logistic addition data transfer will not be shown according to business request
                    if ((AeGetApp()->IsCH() == TRUE) && (m_Discount.GetDiscounttype() == 0) && (m_Discount.GetDiscountspec() == 12))
                    {
                        // skip the logistics addition datatransfer for CH
                        continue;
                    }
                    m_ArtInfDiscountData.m_lDisc.push_back(m_Discount.GetStruct());
                    if (m_Discount.GetPaymenttargetno() > 0)
                    {
                        casa = 1;
                    }
                    if (m_Discount.GetDiscounttype() == 10)
                    {
                        // Bei Sonderangebot -> loeschen weitere Rabatte aus Liste
                        m_ArtInfDiscountData.m_lDisc.clear();
                        m_ArtInfDiscountData.m_lDisc.push_back(m_Discount.GetStruct());
                        nomore = 1;
                        break;
                    }
                    else if (m_Discount.GetDiscounttype() == 8)
                    {
                        if (m_Discount.GetAddondiscountok() == '0')
                        {
                            if (m_lKndNr != -1 && m_Discount.GetBaseqty() <= 1)
                            {
                                // Bei Promotion und keine weiteren Rabatte -> loeschen weitere Rabatte aus Liste
                                for (vector<discountanzS>::iterator itDisc = m_ArtInfDiscountData.m_lDisc.begin(); itDisc < m_ArtInfDiscountData.m_lDisc.end(); itDisc++)
                                {
                                    if (itDisc->DISCOUNTTYPE != 8)
                                    {
                                        m_ArtInfDiscountData.m_lDisc.erase(itDisc);
                                    }
                                }
                                nomore = 1;
                            }
                        }
                    }
                }
                if (nomore == 0)
                {
                    m_Discount.SetBranchno(GetFilialNr());
                    m_Discount.SetManufacturerno(artinf.s.HERSTELLER_NR);
                    m_Discount.SetCustomerno(m_lKndNr);
                    for (;;)
                    {
                        if (m_lKndNr == -1)
                        {
                            if (m_Discount.SelListHerst() != SRV_OK)
                                break;
                        }
                        else
                        {
                            if (m_Discount.SelListGrpHerst() != SRV_OK)
                                break;
                            else if (m_Discount.GetCustomerno() > 0)
                            {
                                if (m_Discount.GetCustomerno() != m_lKndNr)
                                    continue;
                            }
                            // workaround for CH, not clear why additional discounts will not be shown in other countries, so prevent stopping here for CH
                            if (!AeGetApp()->IsCH())
                            {
                                nomore = 1;
                            }
                        }
                        m_ArtInfDiscountData.m_lDisc.push_back(m_Discount.GetStruct());
                        if (m_Discount.GetPaymenttargetno() > 0)
                        {
                            casa = 1;
                        }
                    }
                }
                if (nomore == 0)
                {
                    m_Discount.SetBranchno(GetFilialNr());
                    m_Discount.SetArticleno(m_ArtikelNr);
                    m_Discount.SetCustomerno(m_lKndNr);
                    for (;;)
                    {
                        if (m_lKndNr == -1)
                        {
                            if (m_Discount.SelListDG() != SRV_OK)
                                break;
                        }
                        else
                        {
                            if (m_Discount.SellListGrpDG())
                                break;
                            else if (m_Discount.GetCustomerno() > 0)
                            {
                                if (m_Discount.GetCustomerno() != m_lKndNr)
                                    continue;
                            }
                        }
                        m_ArtInfDiscountData.m_lDisc.push_back(m_Discount.GetStruct());
                        if (m_Discount.GetPaymenttargetno() > 0)
                        {
                            casa = 1;
                        }
                    }
                }
                // in Bulgarien check Einlesen Basisrabatt des Kunden
                if (AeGetApp()->IsBG())
                {
                    if (m_lKndNr != -1)
                    {
                        if (m_ArtInfDiscountData.m_lDisc.size() == 0)
                        {
                            m_Discount.SetBranchno(GetFilialNr());
                            m_Discount.SetCustomerno(m_lKndNr);
                            for (;;)
                            {
                                if (m_Discount.SelListCst() != SRV_OK)
                                    break;
                                m_ArtInfDiscountData.m_lDisc.push_back(m_Discount.GetStruct());
                                m_iBasis = 1;
                                break;
                            }
                        }
                        if (m_ArtInfDiscountData.m_lDisc.size() == 0)
                        {
                            m_Discount.SetBranchno(GetFilialNr());
                            m_Discount.SetCustomerno(m_lKndNr);
                            for (;;)
                            {
                                if (m_Discount.SelListCstEKG() != SRV_OK)
                                    break;
                                m_ArtInfDiscountData.m_lDisc.push_back(m_Discount.GetStruct());
                                m_iBasis = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (casa != 0)
        {
            CPAYTERM payterm;
            payterm.SetVertriebszentrumnr(m_FilialNr);
            payterm.SetKundennr(m_lKndNr);
            m_ArtInfDiscountData.m_lPay.clear();
            int count;
            for (count = 0;; count++)
            {
                if (payterm.SelList() != SRV_OK)
                    break;
                m_ArtInfDiscountData.m_lPay.push_back(payterm.GetStruct());
            }
            payterm.SetPaymentarget(0);
            for (; count < 10; count++)
            {
                m_ArtInfDiscountData.m_lPay.push_back(payterm.GetStruct());
            }
        }
    }
    AfxGetApp()->EndWaitCursor();

    //Ausgabe der Artikelinformationen
    CPSArtInf PSArtInf(CResString::ex().getStrTblText(AETXT_ARTIKELINFORMATION));
    CDArtInf1 DArtInf1(&m_ArtInfData, &m_ArtInfIbtData, &m_ArtInfDiscountData);
    CDArtInf2 DArtInf2(&m_ArtInfData, &m_ArtInfPackageData);
    CDArtInf3 DArtInf3(&m_ArtInfData);
    CDArtInf4 DArtInf4(&m_ArtInfData, &m_ArtInfIbtData);
    CDArtInf5 DArtInf5(&m_ArtInfData, &m_ArtInfDiscountData);
    CDArtInf6 DArtInf6(&m_ArtInfData);
    CDArtInf7 DArtInf7(&m_ArtInfData);
    CDArtInf8 DArtInf8(&m_ArtInfData);
    CDArtInf9 DArtInf9(&m_ArtInfData);

    if      (!strncmp(artinf.s.RABATTFAEHIG, "00", 2)) Rabatt = CResString::ex().getStrTblText(AETXT_RABATT_00);
    else if (!strncmp(artinf.s.RABATTFAEHIG, "01", 2)) Rabatt = CResString::ex().getStrTblText(AETXT_RABATT_01);
    else if (!strncmp(artinf.s.RABATTFAEHIG, "02", 2)) Rabatt = CResString::ex().getStrTblText(AETXT_RABATT_02);
    else if (!strncmp(artinf.s.RABATTFAEHIG, "03", 2)) Rabatt = CResString::ex().getStrTblText(AETXT_RABATT_03);
    else if (!strncmp(artinf.s.RABATTFAEHIG, "04", 2)) Rabatt = CResString::ex().getStrTblText(AETXT_RABATT_04);
    else                                          Rabatt = CResString::ex().getStrTblText(AETXT_RABATT_1X);

    if (   (AeGetApp()->IsNLevelIBT() && m_lKndNr == -1)
        || (AeGetApp()->IsNLevelIBTCst() && m_lKndNr != -1) )
    {
        CARTICLENLEVELIBTTYPE ibt;
        ppString typ;
        ppString sortiment;
        bool found = false;
        ibt.SetBranchno(m_FilialNr);
        ibt.SetArticleno(m_ArtikelNr);
        for (;;)
        {
            if (ibt.SelList() != SRV_OK) break;
            found = true;
            ibt.GetAssortmenttypename(sortiment);
            ibt.GetIbttypename(typ);
            m_ArtInfIbtData.m_assortmenttypename = sortiment.c_str();
            m_ArtInfIbtData.m_ibttypename.Add(typ.c_str());
            m_ArtInfIbtData.m_ibttypename.Add(typ.c_str());
        }
        if (!found)
        {
            m_ArtInfIbtData.m_assortmenttypename = "";
            m_ArtInfIbtData.m_ibttypename.Add(CResString::ex().getStrTblText(AETXT_VB_GESPERRT));
            m_ArtInfIbtData.m_ibttypename.Add(CResString::ex().getStrTblText(AETXT_VB_GESPERRT));
        }
    }

    //Einstellung Daten Kopfinformationen

    if (AeGetApp()->IsBG())
    {
        AllgEntfFirstSpaces(artaesel.s.HEALTHFUNDCODE);
        DArtInf1.m_CKKCode = artaesel.s.HEALTHFUNDCODE;
    }
    if (   artaesel.s.KZPSYCHOSTOFFE[0] == 'J'
        || artaesel.s.KZPSYCHOSTOFFE[0] == 'B'
        || artaesel.s.KZPSYCHOSTOFFE[0] == 'C'
        || artaesel.s.KZPSYCHOSTOFFE[0] == 'D'
        || artaesel.s.KZPSYCHOSTOFFE[0] == 'E'
        || artaesel.s.KZPSYCHOSTOFFE[0] == 'F'
        || artaesel.s.KZPSYCHOSTOFFE[0] == 'P'
        || artaesel.s.KZPSYCHOSTOFFE[0] == 'T')  // psychotrop
    DArtInf1.m_bPsycho = TRUE;
    if (artaesel.s.TFG[0] == '1')
        DArtInf1.m_bTFG = TRUE;
    if (artaesel.s.KONTINGENT_PPE[0] == '1')
        DArtInf1.m_bKontingent_PPE = TRUE;
    if (artaesel.s.MEDIZINPRODUKT[0] == '1')
        DArtInf1.m_bMedizinProdukt = TRUE;
    DArtInf1.m_cChargenArtikel[0] = artaesel.s.CHARGENARTIKEL[0];
    DArtInf1.m_CWafotyp[0] = artinf.s.WAFOTYP[0];
    DArtInf1.m_lDatumlieferbarab = artinf.s.DATUM_LIEFERBAR_AB;
    DArtInf1.m_TextkeyHosp = artaesel.s.TEXTKEY_HOSPITAL;
    if (artinf.s.FROZEN == 1) DArtInf1.m_bKuehlMittel = TRUE;
    else if (artinf.s.FROZEN == 2) DArtInf1.m_bKuehlUltra = TRUE;
    DArtInf1.m_CHC = artinf.s.HERSTELLER_CODE;

    m_ArtInfData.m_CRabatt = Rabatt;
    m_ArtInfData.m_CArtEinh = artinf.s.EINHEIT;
    m_ArtInfData.m_CArtName = AeGetApp()->IsBG() ? artinf.s.ARTIKEL_LANGNAME : artinf.s.ARTIKEL_NAME;

    if (AeGetApp()->IsRS() || AeGetApp()->IsHR())
    {
        m_ArtInfData.m_CInnField = artinf.s.ARTIKEL_LANGNAME;
    }
    //artInfData.m_CArtNr = _ltoa(artaesel.s.ARTIKEL_NR, str, 10);
    m_ArtInfData.m_CArtNr    = artaesel.s.ARTICLE_CODE;
    m_ArtInfData.m_CArtDarr  = artinf.s.DARREICHFORM;
    m_ArtInfData.m_CHerst    = _ltoa(artinf.s.HERSTELLER_NR, str, 10);
    m_ArtInfData.m_CLagArt   = _T("");
    m_ArtInfData.m_CNachfArt = _T("");
    m_ArtInfData.m_CTherapGr = artinf.s.THERAPIEGRUPPE;
    m_ArtInfData.m_CWarenGr  = artinf.s.WARENGRUPPE;
    m_ArtInfData.m_ArtikelNr = artinf.s.ARTIKEL_NR;
    m_ArtInfData.m_FilialNr  = m_FilialNr;
    m_ArtInfData.m_lKndNr    = m_lKndNr;

    //Einstellung Daten 1. Dialog
    DArtInf1.m_CBemerkung = m_CBemerkungKond;
    DArtInf1.m_bNoPriceGroup2 = m_bNoPriceGroup2;
    DArtInf1.m_bNoPriceGroup3 = m_bNoPriceGroup3;
    if (!m_bCheck)
    {
        if (m_lRest >= 0)
        {
            if (m_lRest < artinf.s.BESTAND) artinf.s.BESTAND = m_lRest;
        }
        else
        {
            artinf.s.BESTAND = 0;
        }
    }
    if (artinf.s.BESTAND < 0)
    {
        DArtInf1.m_CArtBest.Empty();
        DArtInf1.m_CReserviert.Empty();
        DArtInf1.m_CKontigent.Empty();
    }
    else
    {
        long mengreserv = 0;
        //mengreserv = artinf.s.BESTANDRESERVIERT;
        CSTOCKRESERVATION cstreserv;
        cstreserv.SetArticleno(artinf.s.ARTIKEL_NR);
        cstreserv.SetBranchno(m_FilialNr);
        if (!cstreserv.SelSum())
        {
            if (cstreserv.GetReservedqty() > 0)
            {
                mengreserv += cstreserv.GetReservedqty();
            }
        }
        DArtInf1.m_CArtBest    = _ltoa(artinf.s.BESTAND,str,10);
        //DArtInf1.m_CReserviert = _ltoa(artinf.s.BESTANDRESERVIERT,str,10);
        DArtInf1.m_CReserviert = _ltoa(mengreserv,str,10);
        DArtInf1.m_CKontigent  = _ltoa(artinf.s.KONTIGENTMENGE,str,10);
    }
    DArtInf1.m_CLagOrt  = _T("");
    DArtInf1.m_CStation = _T("");
    sprintf( str, "%02d/%02d", artverfall.s.DATUMVERFALL%100, artverfall.s.DATUMVERFALL/100 );
    DArtInf1.m_CVerfall = str;
    if (AeGetApp()->IsBG())
    {
        double dTax;
        char cStd;
        AeGetApp()->GetTaxRates(artinf.s.TAXLEVEL, cStd, dTax);
        artpreis.s.PREISEKAPO = artpreis.s.PREISEKAPO * (100 + dTax) / 100;
    }
    DArtInf1.m_sImportarticle = artinf.s.IMPORTARTICLE;
    DArtInf1.m_Taxlevel     = artinf.s.TAXLEVEL;
    DArtInf1.m_CAep         = AllgDoubleToDMText(artpreis.s.PREISEKAPO,str,(char *)CResString::ex().getStrTblText(AETXT_DM).GetString());
    DArtInf1.m_CAvp         = AllgDoubleToDMText(artpreis.s.PREISVKAPO,str,(char *)CResString::ex().getStrTblText(AETXT_DM).GetString());
    DArtInf1.m_CGep         = AllgDoubleToDMText(artpreis.s.PREISEKGROSSO,str,(char *)CResString::ex().getStrTblText(AETXT_DM).GetString());
    DArtInf1.m_CAGP         = AllgDoubleToDMText(artpreis.s.PREISAGP,str,(char *)CResString::ex().getStrTblText(AETXT_DM).GetString());
    DArtInf1.m_dAGP         = artpreis.s.PREISAGP;
    DArtInf5.m_dAGP         = artpreis.s.PREISAGP;
    DArtInf5.m_dGEP         = artpreis.s.PREISEKGROSSO;
    DArtInf5.m_dAEP         = artpreis.s.PREISEKAPO;
    DArtInf5.m_dGROSSO      = artpreis.s.PREISEKGROSSO;
    DArtInf5.m_iBasis       = m_iBasis;
    sprintf(str, "%.2f %%", articletax.s.SALESTAXRATE);
    DArtInf1.m_CMwst        = str;
    sprintf(str, "%.2f %%", artpreis.s.PREISPROZENT);
    DArtInf1.m_CProz        = "7%"; // vorläufig fester Wert
    DArtInf1.m_NatraStaffelNr   = artinf.s.NATRASTAFFELNR;
    DArtInf1.m_CArtikelaktiv[0] = artinf.s.ARTIKELAKTIV[0];
    m_ArtInfIbtData.m_CVerbundartikel = artinf.s.VERBUNDARTIKEL[0];
    DArtInf1.m_CPrisoart = artinf.s.PRISOART[0];
    DArtInf4.m_CPrisoart = artinf.s.PRISOART[0];
    DArtInf1.m_CPositivliste[0] = artinf.s.POSITIVLISTE[0];
    AllgBitleiste2Char((Bitleiste)artinf.s.ETARTKLASSE1, DArtInf1.m_Etartklasse1);
    AllgBitleiste2Char((Bitleiste)artinf.s.ETARTSCHALTER1, DArtInf1.m_Etartschalter1);
    AllgBitleiste2Char((Bitleiste)artinf.s.ETARTSCHALTER2, DArtInf1.m_Etartschalter2);
    AllgBitleiste2Char((Bitleiste)artinf.s.ETARTSCHALTER3, DArtInf1.m_Etartschalter3);
    AllgBitleiste2Char((Bitleiste)artinf.s.ETARTSCHALTER4, DArtInf1.m_Etartschalter4);
    AllgBitleiste2Char((Bitleiste)artinf.s.ETARTSCHALTER5, DArtInf1.m_Etartschalter5);
    DArtInf1.m_CAlter = _T("");
    if (AllgBitleisteN((Bitleiste)artinf.s.ETARTSCHALTER1,1))        // Nachfolgeartikel
    {
        artalt.s.ARTIKEL_NR = m_ArtikelNr;
        artalt.Server(AatartSel_art_altern);
        if (artalt.rc == SRV_OK)
        {
            artaesel.s.ARTIKEL_NR = artalt.s.ARTIKEL_NR_ALTERN;
            artaesel.s.FILIALNR = m_FilialNr;
            artaesel.s.ETARTKLASSE1 = 65535; //alles - select wird nur fuer KK-Code gebraucht
            if (AeGetApp()->IsPrintCode())
                artaesel.s.CODEBLOCAGE[0] = '1';
            else
                artaesel.s.CODEBLOCAGE[0] = '0';
            artaesel.Server(AatartAa_sel_artnr);
            CARTAESEL code;
            code.s.ARTIKEL_NR = artalt.s.ARTIKEL_NR_ALTERN;
            code.Server(AatartSel_Preferred);
            AllgEntfSpaces(code.s.ARTICLE_CODE);
            if (artalt.rc == SRV_OK)
            {
                AllgEntfFirstSpaces(artaesel.s.EINHEIT);
                AllgEntfFirstSpaces(artaesel.s.ARTIKEL_NAME);
                DArtInf1.m_CAlter.Format("%s\n%s: %s\n%s: %ld\n%s: %s\n%s: %s",
                    CResString::ex().getStrTblText(AETXT_ALTERNATIVARTIKEL).GetString(),
                    CResString::ex().getStrTblText(AETXT_ARTICLE_CODE).GetString(),
                    code.s.ARTICLE_CODE,
                    CResString::ex().getStrTblText(AETXT_BEST).GetString(),
                    artaesel.s.BESTAND,
                    CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
                    artaesel.s.EINHEIT,
                    CResString::ex().getStrTblText(AETXT_BEZEICHNUNG).GetString(),
                    artaesel.s.ARTIKEL_NAME);
            }
        }
    }
    DArtInf1.m_CArtText = _T("");
    if (AeGetApp()->IsDE() || AeGetApp()->IsCH())
    {
        if (DArtInf1.m_TextkeyHosp != 0)
        {
            artikeltext.s.BRANCHNO = 0;    //wird vielleicht mal angepasst
            artikeltext.s.TEXTKEY = DArtInf1.m_TextkeyHosp;
            if (!artikeltext.Select())
            {
                DArtInf1.m_CArtText.Format("%s:\n%s",
                CResString::ex().getStrTblText(AETXT_HINWEIS).GetString(),
                artikeltext.s.TEXTHOSPITAL);
            }
        }
    }
    if (artinf.s.TEXTKEY != 0 && DArtInf1.m_CArtText.IsEmpty())
    {
        artikeltext.s.BRANCHNO = 0;    //wird vielleicht mal angepasst
        artikeltext.s.TEXTKEY = artinf.s.TEXTKEY;
        if (!artikeltext.Select())
        {
            if (AeGetApp()->IsPrintCode())
            {
                DArtInf1.m_CArtText.Format("%s: %s",
                CResString::ex().getStrTblText(AETXT_SCHOBER).GetString(),
                artikeltext.s.TEXTHOSPITAL);
            }
            else
            {
                DArtInf1.m_CArtText.Format("%s: %s",
                CResString::ex().getStrTblText(AETXT_SCHOBER).GetString(),
                artikeltext.s.TEXT);
            }
        }
    }

    //Einstellung Daten 2.Dialog
    if (artinf.s.CONTAINERGROESSE == 0)
    {
        m_ArtInfPackageData.m_CContGr = CResString::ex().getStrTblText(AETXT_KEINE);
    }
    else
    {
        m_ArtInfPackageData.m_CContGr = _ltoa(artinf.s.CONTAINERGROESSE,str,10);
        m_ArtInfPackageData.m_CContGr += CResString::ex().getStrTblText(AETXT_STUECK);
    }
    m_ArtInfPackageData.m_CVke = _ltoa(artinf.s.VERKAUFEINHEIT,str,10);
    m_ArtInfPackageData.m_CBreite = _ltoa(artinf.s.BREITE,str,10);
    m_ArtInfPackageData.m_CBreite += " mm";
    m_ArtInfPackageData.m_CGewicht = _ltoa(artinf.s.GEWICHT,str,10);
    m_ArtInfPackageData.m_CGewicht += " gr";
    m_ArtInfPackageData.m_CHoehe = _ltoa(artinf.s.HOEHE,str,10);
    m_ArtInfPackageData.m_CHoehe += " mm";
    m_ArtInfPackageData.m_CLaenge = _ltoa(artinf.s.LAENGE,str,10);
    m_ArtInfPackageData.m_CLaenge += " mm";
    if (artinf.s.LAUFZEITMONATE == 0)
    {
        m_ArtInfPackageData.m_CLaufZeit += CResString::ex().getStrTblText(AETXT_KEINE);
    }
    else
    {
        m_ArtInfPackageData.m_CLaufZeit = _ltoa(artinf.s.LAUFZEITMONATE,str,10);
        m_ArtInfPackageData.m_CLaufZeit += CResString::ex().getStrTblText(AETXT_MONATE);
    }
    m_ArtInfPackageData.m_CNormPack = artinf.s.NORMPACKUNG;

    //Einstellung Daten 3.Dialog
    DArtInf3.m_lHerstNr = artinf.s.HERSTELLER_NR;

    //Einstellung Daten 4.Dialog
    DArtInf4.m_lRest = m_lRest;
    DArtInf4.m_bCheck = m_bCheck;

    //Zuordnung der Dialoge zum Gruppendialog
    PSArtInf.AddPage(&DArtInf1);
    PSArtInf.AddPage(&DArtInf2);
    PSArtInf.AddPage(&DArtInf3);
    PSArtInf.AddPage(&DArtInf4);
    PSArtInf.AddPage(&DArtInf5);
    PSArtInf.AddPage(&DArtInf6);
    PSArtInf.AddPage(&DArtInf7);
    if (AeGetApp()->IsFR())
        PSArtInf.AddPage(&DArtInf8);
    PSArtInf.AddPage(&DArtInf9);
    //PSArtInf.SetActivePage(5);

    return PSArtInf.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPSArtInf

IMPLEMENT_DYNAMIC(CPSArtInf, CPropertySheetMultiLang)

CPSArtInf::CPSArtInf(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheetMultiLang(nIDCaption, pParentWnd, iSelectPage)
{
}

CPSArtInf::CPSArtInf(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheetMultiLang(pszCaption, pParentWnd, iSelectPage)
{
}

CPSArtInf::~CPSArtInf()
{
    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf.cpp", "Deconstruct", "Dialog stopped");
}

BOOL CPSArtInf::OnInitDialog()
{
    BOOL bResult = CPropertySheetMultiLang::OnInitDialog();

    SetBtText(BT_OK, (char*)CResString::ex().getStrTblText(IDS_MSG_OK).GetString());
    SetBtText(BT_CANCEL, (char*)CResString::ex().getStrTblText(IDS_BT_CANCEL).GetString());
    SetBtText(BT_APPLY_NOW, (char*)CResString::ex().getStrTblText(AETXT_UEBERNEHM).GetString());

    return bResult;
}

BEGIN_MESSAGE_MAP(CPSArtInf, CPropertySheetMultiLang)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPSArtInf message handlers

/////////////////////////////////////////////////////////////////////////////
// CDArtInf1 property page

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES SpaltenNetto[] =
{
    0,  "",  53, LVCFMT_LEFT,
    1,  "",  55, LVCFMT_RIGHT,
    2,  "",  30, LVCFMT_CENTER,
    3,  "",   0, LVCFMT_RIGHT,
    4,  "",  73, LVCFMT_LEFT,
    5,  "",  73, LVCFMT_LEFT,
    6,  "",  30, LVCFMT_CENTER,
    7,  "", 150, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_NETTO 8

static COLUMNS_TYPES SpaltenNatra[] =
{
    0,  "",  55, LVCFMT_LEFT,
    1,  "",  55, LVCFMT_LEFT,
    2,  "",  30, LVCFMT_CENTER,
    3,  "",  30, LVCFMT_LEFT,
    4,  "", 150, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_NATRA 5

static COLUMNS_TYPES SpaltenOMG[] =
{
    0,  "", 300, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_OMG 1

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES Charge[] =
{
    0,  "", 150, LVCFMT_LEFT,
    1,  "",  90, LVCFMT_LEFT,
    2,  "",  60, LVCFMT_RIGHT,
    -1, "",   0, 0
};

#define NUM_CHARGE 3


IMPLEMENT_DYNCREATE(CDArtInf1, CPropertyPageMultiLang)

CDArtInf1::CDArtInf1()
{
}

CDArtInf1::CDArtInf1(SArtInfData* pArtInfData, SArtInfIbtData* pArtInfIbtData, SArtInfDiscountData* pArtInfDiscountData)
    : CPropertyPageMultiLang(CDArtInf1::IDD)
, m_pArtInfData(pArtInfData)
, m_pArtInfIbtData(pArtInfIbtData)
, m_pArtInfDiscountData(pArtInfDiscountData)
, m_CHC(_T(""))
, m_CArtText(_T(""))
, m_CKontigent(_T(""))
, m_CReserviert(_T(""))
, m_CMwst(_T(""))
, m_CLPPR(_T(""))
, m_CAGP(_T(""))
{
    m_CArtBest = _T("");
    m_CLagOrt = _T("");
    m_CStation = _T("");
    m_CVerfall = _T("");
    m_CAep = _T("");
    m_CAvp = _T("");
    m_CGep = _T("");
    m_CBemerkung = _T("");
    m_CProz = _T("");
    m_CAlter = _T("");
    m_init = false;
    m_bPsycho = FALSE;
    m_bTFG = FALSE;
    m_bKontingent_PPE = FALSE;
    m_bMedizinProdukt = FALSE;
    m_bKuehlMittel = FALSE;
    m_bKuehlUltra = FALSE;

    Charge[0].Columns = CResString::ex().getStrTblText(AETXT_CHARGE);
    Charge[1].Columns = CResString::ex().getStrTblText(AETXT_VERFALLDATUM);
    Charge[2].Columns = CResString::ex().getStrTblText(AETXT_BESTAND);
}

CDArtInf1::~CDArtInf1()
{
}

void CDArtInf1::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListKz);
    DDX_Control(pDX, IDC_LIST_NATRA, m_ListNatra);
    DDX_Control(pDX, IDC_LIST_NETTO, m_ListNetto);
    DDX_Text(pDX, IDC_ST_ARTIKEL_EINHEIT, m_pArtInfData->m_CArtEinh);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NAME, m_pArtInfData->m_CArtName);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NR, m_pArtInfData->m_CArtNr);
    DDX_Text(pDX, IDC_ST_BESTAND, m_CArtBest);
    DDX_Text(pDX, IDC_ST_DARREICHUNG, m_pArtInfData->m_CArtDarr);
    DDX_Text(pDX, IDC_ST_HERSTELLER, m_pArtInfData->m_CHerst);
    DDX_Text(pDX, IDC_ST_LAGERORT, m_CLagOrt);
    DDX_Text(pDX, IDC_ST_LAGERART, m_pArtInfData->m_CLagArt);
    DDX_Text(pDX, IDC_ST_NACHFOLGE, m_pArtInfData->m_CNachfArt);
    DDX_Text(pDX, IDC_ST_STATION, m_CStation);
    DDX_Text(pDX, IDC_ST_THERAPIE_GR, m_pArtInfData->m_CTherapGr);
    DDX_Text(pDX, IDC_ST_VERFALL, m_CVerfall);
    DDX_Text(pDX, IDC_ST_WAREN_GR, m_pArtInfData->m_CWarenGr);
    DDX_Text(pDX, IDC_ST_AEP, m_CAep);
    DDX_Text(pDX, IDC_ST_AVP, m_CAvp);
    DDX_Text(pDX, IDC_ST_GEP, m_CGep);
    DDX_Text(pDX, IDC_ST_BEMERKUNG, m_CBemerkung);
    DDX_Text(pDX, IDC_ST_PROZ, m_CProz);
    DDX_Text(pDX, IDC_STATIC_RABATT, m_pArtInfData->m_CRabatt);
    DDX_Text(pDX, IDC_STATIC_ALTER, m_CAlter);
    DDX_Text(pDX, IDC_STATIC_CODE_TEXT, m_CKKCode);
    DDX_Text(pDX, IDC_STATIC_HC, m_CHC);
    DDX_Text(pDX, IDC_STATIC_ART_TEXT, m_CArtText);
    DDX_Text(pDX, IDC_ST_KONTIGENT, m_CKontigent);
    DDX_Text(pDX, IDC_ST_RESERVIERT, m_CReserviert);
    DDX_Text(pDX, IDC_ST_MWST, m_CMwst);
    DDX_Text(pDX, IDC_ST_LPPR, m_CLPPR);
    DDX_Text(pDX, IDC_ST_AGP, m_CAGP);
    DDX_Text(pDX, IDC_ST_INN_FIELD, m_pArtInfData->m_CInnField);
    DDX_Control(pDX, IDC_LIST_CHARGE, m_ListCharge);
    DDX_Control(pDX, IDC_STATIC_ICON1, m_Icon[0]);
    DDX_Control(pDX, IDC_STATIC_ICON2, m_Icon[1]);
    DDX_Control(pDX, IDC_STATIC_ICON3, m_Icon[2]);
    DDX_Control(pDX, IDC_STATIC_ICON4, m_Icon[3]);
    DDX_Control(pDX, IDC_STATIC_ICON5, m_Icon[4]);
    DDX_Control(pDX, IDC_STATIC_ICON6, m_Icon[5]);
    DDX_Control(pDX, IDC_STATIC_ICON7, m_Icon[6]);
    DDX_Control(pDX, IDC_STATIC_ICON8, m_Icon[7]);
    DDX_Control(pDX, IDC_STATIC_ICON9, m_Icon[8]);
    DDX_Control(pDX, IDC_STATIC_ICON10, m_Icon[9]);
}

BOOL CDArtInf1::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();

    if (m_init)
    {
        return TRUE;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf1.cpp", "OnSetActive", "Page started");

    int i_IconActiv = 0;
    if (m_cChargenArtikel[0] == '1') //Charge
    {
        ShowIcon(m_Icon[i_IconActiv++], IDI_ICON_CHARGE);
    }
    if (m_Etartklasse1[6] == '1')  // BTM
    {
        ShowIcon(m_Icon[i_IconActiv++], IDI_ICON_BTM);
    }
    if (m_Etartschalter1[10] == '1')  // Kuehlkette
    {
        ShowIcon(m_Icon[i_IconActiv++], IDI_ICON_KUEHL);
    }
    if (m_Etartschalter1[8] == '1')  // Kuehlkette unter 8
    {
        ShowIcon(m_Icon[i_IconActiv++], IDI_ICON_KUEHL_U8);
    }
    if (m_Etartschalter1[9] == '1')  // Kuehl unter 20
    {
        ShowIcon(m_Icon[i_IconActiv++], IDI_ICON_K20);
    }
    if (m_bPsycho)  // Psychotroper Stoff
    {
        ShowIcon(m_Icon[i_IconActiv++], IDI_ICON_PTS);
    }
    if (m_bTFG)  // Transfusionsgesetz
    {
        ShowIcon(m_Icon[i_IconActiv++], IDI_ICON_TFG);
    }
    if (m_bKontingent_PPE)  // Herstellerkontingent
    {
        ShowIcon(m_Icon[i_IconActiv++], IDI_ICON_HQ);
    }
    if (m_bMedizinProdukt)  // Medizinprodukt
    {
        ShowIcon(m_Icon[i_IconActiv++], IDI_ICON_MDR);
    }
    if (m_bKuehlMittel || m_bKuehlUltra)  // Tiefgekühlt
    {
        ShowIcon(m_Icon[i_IconActiv++], m_bKuehlMittel ? IDI_ICON_MITTEL : IDI_ICON_ULTRA);
    }

    if (!m_pArtInfDiscountData->m_bOMGCst)
    {
        SpaltenNetto[0].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
        SpaltenNetto[1].Columns = CResString::ex().getStrTblText(AETXT_PREIS);
        SpaltenNetto[2].Columns = CResString::ex().getStrTblText(AETXT_RG);
        SpaltenNetto[3].Columns = CResString::ex().getStrTblText(AETXT_ZZ);
        SpaltenNetto[4].Columns = CResString::ex().getStrTblText(AETXT_VON);
        SpaltenNetto[5].Columns = CResString::ex().getStrTblText(AETXT_BIS);
        SpaltenNetto[6].Columns = CResString::ex().getStrTblText(AETXT_EK_GRP);
        if (AeGetApp()->IsDE())
        {
            SpaltenNetto[7].Index = -1;
        }
        else
        {
            SpaltenNetto[7].Columns = CResString::ex().getStrTblText(AETXT_EK_GRP);
        }

        SpaltenNatra[0].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
        SpaltenNatra[1].Columns = CResString::ex().getStrTblText(AETXT_STUECK);
        SpaltenNatra[2].Columns = CResString::ex().getStrTblText(AETXT_RG);
        SpaltenNatra[3].Columns = CResString::ex().getStrTblText(AETXT_ART);
        SpaltenNatra[4].Columns = CResString::ex().getStrTblText(AETXT_EK_GRP);
    }
    else
    {
        SpaltenOMG[0].Columns = CResString::ex().getStrTblText(AETXT_HINWEIS);
    }

    if (   (AeGetApp()->IsNLevelIBT() && m_pArtInfData->m_lKndNr == -1)
        || (AeGetApp()->IsNLevelIBTCst() && m_pArtInfData->m_lKndNr != -1) )
    {
        if (!m_pArtInfIbtData->m_ibttypename.GetAt(0).IsEmpty())
        {
            GetDlgItem(IDC_STATIC_VB_TYP)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_VB_TYP)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_IBT_TYPE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_IBT_TYPE)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_IBT_TYPE)->SetWindowTextA(m_pArtInfIbtData->m_ibttypename.GetAt(0));
        }
    }

    if (AeGetApp()->IsRS() || AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_INN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_INN)->EnableWindow(TRUE);
        GetDlgItem(IDC_ST_INN_FIELD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_INN_FIELD)->EnableWindow(TRUE);
    }

    if (AeGetApp()->IsHR()) 
    {
        CString CStr;
        if (m_lDatumlieferbarab > AeGetApp()->GetCurrentDate())
        {
            CStr.Format(CResString::ex().getStrTblText(AETXT_LIEFERBAR_AB), DDMMYYYYStringFromDateLong(m_lDatumlieferbarab));
            GetDlgItem(IDC_STATIC_LIEFERBAR)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_LIEFERBAR)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_LIEFERBAR)->SetWindowText(CStr);
        }
    }

    if (AeGetApp()->IsBG())
    {
        GetDlgItem(IDC_STATIC_FS_PRICE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_FS_PRICE)->EnableWindow(TRUE);
        if (!m_CKKCode.IsEmpty())
        {
            CARTPREIS kkpreis;
            kkpreis.s.PREIS_TYP = 1;
            kkpreis.s.ARTIKEL_NR = m_pArtInfData->m_ArtikelNr;
            kkpreis.Server(AatartInf_preis);
            if (kkpreis.rc < SRV_OK)
            {
            }    // keine KK-Preis vorhanden -> auch nix zu zeigen
            else
            {
                double dTax;
                char cStd;
                AeGetApp()->GetTaxRates(m_Taxlevel, cStd, dTax);
                GetDlgItem(IDC_STATIC_HF_PRICE)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_HF_PRICE)->EnableWindow(TRUE);
                GetDlgItem(IDC_ST_AEP_HF)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_ST_AEP_HF)->EnableWindow(TRUE);
                GetDlgItem(IDC_ST_AVP_HF)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_ST_AVP_HF)->EnableWindow(TRUE);
                GetDlgItem(IDC_ST_GEP_HF)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_ST_GEP_HF)->EnableWindow(TRUE);
                kkpreis.s.PREISEKAPO = kkpreis.s.PREISEKAPO * (100 + dTax) / 100;
                CString CStr;
                CStr.Format("%0.2lf", kkpreis.s.PREISEKAPO);
                GetDlgItem(IDC_ST_AEP_HF)->SetWindowText(CStr);
                CStr.Format("%0.2lf", kkpreis.s.PREISEKGROSSO);
                GetDlgItem(IDC_ST_GEP_HF)->SetWindowText(CStr);
                CStr.Format("%0.2lf", kkpreis.s.PREISVKAPO);
                GetDlgItem(IDC_ST_AVP_HF)->SetWindowText(CStr);
            }
        }
    }

    if (m_CKKCode.IsEmpty())
    {
        GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CODE_TEXT)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_CODE_TEXT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_CODE_TEXT)->SetWindowText(m_CKKCode);
    }
    CPHARMGRP pharmgrp;
    m_init = true;
    CString CStr;
    ppString Grp;
    ppString GrpName;
    if (AeGetApp()->IsPrintCode())
    {
        ppString text;
        CCODEBLOCAGEINFO code;
        code.SetFilialnr(m_pArtInfData->m_FilialNr);
        code.SetArtikel_nr(m_pArtInfData->m_ArtikelNr);
        if (!code.SelText())
        {
            code.GetPrintcode(text);
            m_ListKz.AddString(text);
        }
    }
    if (   (AeGetApp()->IsNLevelIBT() && (m_pArtInfData->m_lKndNr == -1))
        || (AeGetApp()->IsNLevelIBTCst() && (m_pArtInfData->m_lKndNr != -1)) )
    {
        CString verbund;
        verbund = m_pArtInfIbtData->m_assortmenttypename;
        int anz = m_pArtInfIbtData->m_ibttypename.GetCount();
        for (int count = 0; count < anz; count++)
        {
            verbund += " ";
            verbund += m_pArtInfIbtData->m_ibttypename.GetAt(count);
        }
        m_ListKz.AddString(verbund);
    }
    else
    {
        if      (m_pArtInfIbtData->m_CVerbundartikel == '0') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_GESPERRT));
        else if (m_pArtInfIbtData->m_CVerbundartikel == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_LOKAL));
        else if (m_pArtInfIbtData->m_CVerbundartikel == '2') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_PRISO));
        else if (m_pArtInfIbtData->m_CVerbundartikel == '3') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_VETO));
        else if (m_pArtInfIbtData->m_CVerbundartikel == '4') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_REGIONAL));
        else if (m_pArtInfIbtData->m_CVerbundartikel == '5') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_NATIONAL));
        else if (m_pArtInfIbtData->m_CVerbundartikel == '6') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_REG_NAT));
        else if (m_pArtInfIbtData->m_CVerbundartikel == '7') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_LOK_NAT));
        else if (m_pArtInfIbtData->m_CVerbundartikel == '8') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_LOK_REG));
        else                                                 m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VB_KOMPLETT));
    }
    if (AeGetApp()->IsDE())
    {
        if (m_CWafotyp[0] != '1')
            m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_NO_WAFO));
        if (m_lDatumlieferbarab > AeGetApp()->GetCurrentDate())
        {
            CStr.Format(CResString::ex().getStrTblText(AETXT_LIEFERBAR_AB), DDMMYYYYStringFromDateLong(m_lDatumlieferbarab));
            GetDlgItem(IDC_STATIC_LIEFERBAR)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_LIEFERBAR)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_LIEFERBAR)->SetWindowText(CStr);
        }
    }
    if (AeGetApp()->IsCH())
    {
        if (m_Etartklasse1[11] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_INLAND));
    }
    if (m_Etartklasse1[3] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_REZEPTPFLICHTIG));
    if (m_Etartklasse1[4] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_APOTHEKENPFLICHTIG));
    if (m_Etartschalter2[2] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_VERFALLDATUM));
    if (m_Etartschalter1[11] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_HERSTELLERDEFEKT));
    if (m_Etartschalter1[3] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_AUSSERHANDEL));
    if (m_Etartschalter1[4] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_AUSLAUF));
    if (m_Etartschalter3[7] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_NRAKTION));
    if (m_Etartschalter1[6] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_NETTOAKTION));
    if (m_Etartschalter1[13] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_NICHT_UEBER_GH));
    if (m_Etartschalter1[5] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_RUECKRUF));
    if (m_Etartschalter1[15] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_RETOUREN_SPERRE));
    if (m_Etartschalter2[15] == '0') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_NICHTGEF));
    if (m_Etartschalter2[4] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_ERMAESSIGTE_MWST));
    if (m_Etartschalter1[14] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_KLINIKPACKUNG));
    if (m_Etartschalter3[8] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_UEBERVORRAT));
    //if (m_Etartschalter1[11] == '1') m_ListKz.AddString("Verbund");
    if (m_CArtikelaktiv[0] == '0') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_ART_GESPERRT));
    if (m_CPositivliste[0] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_POSITIVLISTE));
    if (m_CPrisoart == '2') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_ZENTRAL_ART));
    if (m_Etartschalter4[14] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_OHNE_ZERTIFIKAT));
    if (m_Etartschalter3[5] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_POOL));
    if (m_Etartschalter5[8] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_MIDAS));
    if (m_Etartschalter5[9] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_STAMMLAGER));
    if (m_Etartschalter5[0] == '1') m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_EKS));
    if (m_sImportarticle == 1) m_ListKz.AddString(CResString::ex().getStrTblText(AETXT_IMPORTARTICLE));

    if (m_Etartklasse1[3] == '1' ||
        m_Etartklasse1[4] == '1' ||
        m_Etartklasse1[5] == '1' ||
        AeGetApp()->IsPrintCode() ||
        AeGetApp()->IsNewDiscount())
    {
        GetDlgItem(IDC_STATIC_PERS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_ST_PROZ)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_PERS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_PROZ)->ShowWindow(SW_SHOW);
    }

    if (!m_pArtInfDiscountData->m_bOMGCst)
    {
        if (   !CListCtrlHelper::AddColumns(SpaltenNetto, m_ListNetto)
            || !CListCtrlHelper::AddColumns(SpaltenNatra, m_ListNatra) )
        {
            return FALSE;
        }
    }
    else
    {
        GetDlgItem(IDC_LIST_NATRA)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LIST_NATRA)->EnableWindow(FALSE);
        if (!CListCtrlHelper::AddColumns(SpaltenOMG, m_ListNetto))
        {
            return FALSE;
        }
    }
    if (!CListCtrlHelper::AddColumns(Charge, m_ListCharge))
    {
        return FALSE;
    }

    if (AeGetApp()->IsNewDiscount() && AeGetApp()->IsDE())      //für DE Pricing
    {
        m_ListNetto.SetColumnWidth(2, 0);
    }

    //Nettolistbox füllen
    char str[81];
    CStringArray s;
    s.SetSize(NUM_SPALT_NETTO);
    if (!m_pArtInfDiscountData->m_bOMGCst)
    {
        for (vector<discountanzS>::iterator itDisc = m_pArtInfDiscountData->m_lDisc.begin(); itDisc < m_pArtInfDiscountData->m_lDisc.end(); itDisc++)
        {
            if (itDisc->FIXEDPRICE == 0 && !AeGetApp()->IsDE()) continue;
            if (itDisc->FIXEDPRICE > 0 && itDisc->DISCOUNTVALUEPCT > 0) continue;
            if (itDisc->CUSTOMERNO != 0 &&
                m_pArtInfData->m_lKndNr != -1 &&
                itDisc->CUSTOMERNO != m_pArtInfData->m_lKndNr) continue;
            //Ausgabe in die Listbox
            sprintf(str, "%d", itDisc->BASEQTY);
            s[0] = str;
            if (AeGetApp()->IsDE() && itDisc->DISCOUNTTYPE == 16)
            {
                sprintf(str, "GEP+%0.1f%%", itDisc->SURCHARGEPCT);
            }
            else if (AeGetApp()->IsDE() && itDisc->DISCOUNTTYPE == 13 && itDisc->FIXEDPRICE == 0.0)
            {
                sprintf(str, "");
            }
            else
            {
                sprintf(str, "%0.2f", itDisc->FIXEDPRICE);
            }
            s[1] = str;
            sprintf(str, "%d", itDisc->DISCOUNTTYPE);
            s[2] = str;
            s[3].Empty();
            if (itDisc->PAYMENTTARGETNO > 0)
            {
                m_ListNetto.SetColumnWidth(3, 27);
                s[3].Format("%d", m_pArtInfDiscountData->m_lPay.at(itDisc->PAYMENTTARGETNO - 1).PAYMENTARGET);
            }
            AllgDatumLong2CharTTMMJJJJ(itDisc->DATEFROM,str);
            s[4] = str;
            AllgDatumLong2CharTTMMJJJJ(itDisc->DATETO,str);
            s[5] = str;
            pharmgrp.SetPharmacygroupid(itDisc->PHARMACYGROUPID);
            pharmgrp.SetBranchno(m_pArtInfData->m_FilialNr);
            s[6] = itDisc->PHARMACYGROUPID;
            if (!pharmgrp.Sel())
                s[7] = pharmgrp.GetGroup_name(GrpName);
            else
                s[7].Empty();

            if (!CListCtrlHelper::AppendItem(m_ListNetto, NUM_SPALT_NETTO, s))
            {
                return FALSE;
            }
        }
    }
    else
    {
        if (m_ListNetto.InsertItem(0, CResString::ex().getStrTblText(AETXT_OMG_HINWEIS) ) == -1)
        {
            EndWaitCursor();
            return FALSE;
        }
    } //end netto

    //Natralistbox füllen
    s.SetSize(NUM_SPALT_NATRA);
    if (!m_pArtInfDiscountData->m_bOMGCst)
    {
        for (vector<discountanzS>::iterator itDisc = m_pArtInfDiscountData->m_lDisc.begin(); itDisc < m_pArtInfDiscountData->m_lDisc.end(); itDisc++)
        {
            if (itDisc->DISCOUNTQTY == 0) continue;
            if (itDisc->DISCOUNTQTY > 0 && itDisc->DISCOUNTARTICLE > 0 ) continue;
            if (itDisc->CUSTOMERNO != 0 &&
                m_pArtInfData->m_lKndNr != -1 &&
                itDisc->CUSTOMERNO != m_pArtInfData->m_lKndNr) continue;
    //Ausgabe in die Listbox
            sprintf(str, "%d", itDisc->BASEQTY);
            s[0] = str;
            sprintf(str, "%d", itDisc->DISCOUNTQTY);
            s[1] = str;
            sprintf(str, "%d", itDisc->DISCOUNTTYPE);
            s[2] = str;
            if (itDisc->INTERNALDISCOUNT[0] == '1')
                s[3] = CResString::ex().getStrTblText(AETXT_INTERN);
            else
                s[3].Empty();
            pharmgrp.SetPharmacygroupid(itDisc->PHARMACYGROUPID);
            pharmgrp.SetBranchno(m_pArtInfData->m_FilialNr);
            if (!pharmgrp.Sel())
                s[4] = pharmgrp.GetGroup_name(GrpName);
            else
                s[4] = itDisc->PHARMACYGROUPID;

            if (!CListCtrlHelper::AppendItem(m_ListNatra, NUM_SPALT_NATRA, s))
            {
                EndWaitCursor();
                return FALSE;
            }
        }
    }

    CARTLAGER lag;
    lag.s.FILIALNR   = m_pArtInfData->m_FilialNr;
    lag.s.ARTIKEL_NR = m_pArtInfData->m_ArtikelNr;
    lag.s.FETCH_REL  = 1;   //normaler Fetch
    BeginWaitCursor();
    lag.Server(AatartLagerinf);
    if (lag.rc >= SRV_OK)
    {
        CStr.Format("%d", lag.s.LAGERBEREICHNR);
        GetDlgItem(IDC_ST_LAGBER)->SetWindowText(CStr);
        GetDlgItem(IDC_ST_LAGERORT)->SetWindowText(lag.s.LAGERFACHNR);
        GetDlgItem(IDC_ST_STATION)->SetWindowText(lag.s.STATIONNR);
    }
    lag.s.FETCH_REL = 0;    //Close Cursor
    lag.Server(AatartLagerinf);

    // Reservierte Bestände
    CARTIKELRESERVE reserv;
    reserv.SetBranchno(m_pArtInfData->m_FilialNr);
    reserv.SetArticleno(m_pArtInfData->m_ArtikelNr);
    GetDlgItem(IDC_STATIC_RESERV)->SetWindowText(" ");
    GetDlgItem(IDC_STATIC_RESERV2)->SetWindowText(" ");
    if (m_pArtInfData->m_lKndNr == -1)
    {
        reserv.SetReservtype(0);
        if (!reserv.SelArt())
        {
            ppString EKGr;
            CStr.Format(AETXT_RESERV_BESTAND,reserv.GetReservedqty(),reserv.GetPharmacygroupid(EKGr));
            GetDlgItem(IDC_STATIC_RESERV)->SetWindowText(CStr);
        }
        reserv.SetReservtype(2);
        if (!reserv.SelArt())
        {
            ppString EKGr;
            CStr.Format(AETXT_RESERV_BESTAND2,reserv.GetReservedqty(),reserv.GetPharmacygroupid(EKGr));
            GetDlgItem(IDC_STATIC_RESERV2)->SetWindowText(CStr);
        }
    }
    else
    {
        reserv.SetCustomerno(m_pArtInfData->m_lKndNr);
        reserv.SetReservtype(0);
        if (!reserv.SelArtKnd())
        {
            ppString EKGr;
            CStr.Format(AETXT_RESERV_BESTAND,reserv.GetReservedqty(),reserv.GetPharmacygroupid(EKGr));
            GetDlgItem(IDC_STATIC_RESERV)->SetWindowText(CStr);
        }
        reserv.SetCustomerno(m_pArtInfData->m_lKndNr);
        reserv.SetReservtype(2);
        if (!reserv.SelArtKnd())
        {
            ppString EKGr;
            CStr.Format(AETXT_RESERV_BESTAND2,reserv.GetReservedqty(),reserv.GetPharmacygroupid(EKGr));
            GetDlgItem(IDC_STATIC_RESERV2)->SetWindowText(CStr);
        }
    }

    EndWaitCursor();
    GetDlgItem(IDC_STATIC_LPPR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ST_LPPR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_LPPR_CODE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ST_LPPR_CODE)->ShowWindow(SW_HIDE);
    CARTIKELLPPR lppr;
    lppr.SetArticleno(m_pArtInfData->m_ArtikelNr);
    if (lppr.SelList() == SRV_OK)
    {
        if (lppr.GetReimbursement_type() == '2') //nicht mehr hier geladen
        {
            /*CLPPRCODE code;
            ppString lpprcode;
            code.SetCode_lppr(lppr.GetCode_lppr(lpprcode));
            if (!code.Sel())
            {
                m_CLPPR = AllgDoubleToDMText(code.GetReimbursement_val(),str,(char *)CResString::ex().getStrTblText(AETXT_DM).GetString());
                GetDlgItem(IDC_ST_LPPR)->SetWindowText(m_CLPPR);
                GetDlgItem(IDC_ST_LPPR_CODE)->SetWindowText(lpprcode);
                GetDlgItem(IDC_STATIC_LPPR)->SetWindowText(CResString::ex().getStrTblText(AETXT_LPPR));
                GetDlgItem(IDC_STATIC_LPPR)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_ST_LPPR)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_LPPR_CODE)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_ST_LPPR_CODE)->ShowWindow(SW_SHOW);
            }*/
        }
        else if (lppr.GetReimbursement_type() == '1')
        {
            m_CLPPR = AllgDoubleToDMText(lppr.GetReimbursementprice(),str,(char *)CResString::ex().getStrTblText(AETXT_DM).GetString());
            GetDlgItem(IDC_ST_LPPR)->SetWindowText(m_CLPPR);
            GetDlgItem(IDC_STATIC_LPPR)->SetWindowText(CResString::ex().getStrTblText(AETXT_TFR));
            GetDlgItem(IDC_STATIC_LPPR)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_ST_LPPR)->ShowWindow(SW_SHOW);
        }
        else if (lppr.GetReimbursement_type() == '3')
        {
            m_CLPPR = AllgDoubleToDMText(lppr.GetReimbursementprice(),str,(char *)CResString::ex().getStrTblText(AETXT_DM).GetString());
            GetDlgItem(IDC_ST_LPPR)->SetWindowText(m_CLPPR);
            GetDlgItem(IDC_STATIC_LPPR)->SetWindowText(CResString::ex().getStrTblText(AETXT_VERGUETUNG));
            GetDlgItem(IDC_STATIC_LPPR)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_ST_LPPR)->ShowWindow(SW_SHOW);
        }
    }

    GetDlgItem(IDC_STATIC_ART_TEXT)->SetWindowText(m_CArtText);
    if (m_dAGP == 0)
    {
        GetDlgItem(IDC_STATIC_AGP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_ST_AGP)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_AGP)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_AGP)->ShowWindow(SW_SHOW);
    }
    CARTCHARGE charge;
    charge.SetBranchno(AeGetApp()->FilialNrActual());
    charge.SetArticleno(m_pArtInfData->m_ArtikelNr);
    //ChargenListbox füllen
    s.SetSize(NUM_CHARGE);
    m_ListCharge.DeleteAllItems();

    for (;;)
    {
        //Check ob Auftragart Quarantaene
        CString cAArt;
        ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_AA)->GetWindowText(cAArt);
        if (cAArt == "QA")
        {
            if (charge.SelListQua() != SRV_OK)
                break;
        }
        else
        {
            if (charge.SelList() != SRV_OK)
                break;
        }
        if (charge.GetStock() == 0)
            continue;
        ppString strcharge;
        charge.GetChargennr(strcharge);
        s[0] = strcharge;
        s[1] = DDMMYYYYStringFromDateLong(charge.GetExpirydate());
        s[2].Format("%d", charge.GetStock());

        if (!CListCtrlHelper::AppendItem(m_ListCharge, NUM_CHARGE, s))
        {
            return TRUE;
        }
    }

    //UpdateData(FALSE);
    return TRUE;
}

void CDArtInf1::ShowIcon(CStatic& icon, UINT nIDResource)
{
    icon.SetIcon(AfxGetApp()->LoadIcon(nIDResource));
    icon.ShowWindow(SW_SHOW);
}

HBRUSH CDArtInf1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPageMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_STATIC_ALTER)
        pDC->SetTextColor(RGB(0, 150, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_QUOTA)
        pDC->SetTextColor(RGB(255, 0, 0));
    else if ((pWnd->GetDlgCtrlID() == IDC_STATIC_ART_TEXT) && (m_TextkeyHosp != 0))
        pDC->SetTextColor(RGB(255, 0, 0));
    else if ((pWnd->GetDlgCtrlID() == IDC_STATIC_LIEFERBAR))
        pDC->SetTextColor(RGB(255, 0, 0));
    return hbr;
}

void CDArtInf1::OnBnClickedButtonArtikelkonto()
{
    CDArtikelkonto dlgArtikelkonto;
    if (m_pArtInfData->m_lKndNr > 0)
    {
        dlgArtikelkonto.m_CIdfNr.Format("%d", m_pArtInfData->m_lKndNr);
    }
    else
    {
        dlgArtikelkonto.m_CIdfNr.Empty();
    }
    dlgArtikelkonto.m_CFiliale.Format("%d", m_pArtInfData->m_FilialNr);
    dlgArtikelkonto.m_CArtikelNr = m_pArtInfData->m_CArtNr;
    dlgArtikelkonto.DoModal();
}

BEGIN_MESSAGE_MAP(CDArtInf1, CPropertyPageMultiLang)
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BUTTON_ARTIKELKONTO, OnBnClickedButtonArtikelkonto)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDArtInf1 message handlers
/////////////////////////////////////////////////////////////////////////////
// CDArtInf2 property page

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES SpaltenLagOrt[] =
{
    0,  "", 70, LVCFMT_LEFT,
    1,  "", 40, LVCFMT_RIGHT,
    2,  "", 30, LVCFMT_RIGHT,
    3,  "", 50, LVCFMT_RIGHT,
    4,  "", 50, LVCFMT_CENTER,
    -1, "",  0, 0
};

#define NUM_SPALT_LAGORT 5

IMPLEMENT_DYNCREATE(CDArtInf2, CPropertyPageMultiLang)

CDArtInf2::CDArtInf2()
{
}

CDArtInf2::CDArtInf2(SArtInfData* pArtInfData, SArtInfPackageData* pArtInfPackageData) : CPropertyPageMultiLang(CDArtInf2::IDD)
, m_pArtInfData(pArtInfData), m_pArtInfPackageData(pArtInfPackageData)
{
    m_init = false;

    SpaltenLagOrt[0].Columns = CResString::ex().getStrTblText(AETXT_LAGERORT);
    SpaltenLagOrt[1].Columns = CResString::ex().getStrTblText(AETXT_BER);
    SpaltenLagOrt[2].Columns = CResString::ex().getStrTblText(AETXT_ST);
    SpaltenLagOrt[3].Columns = CResString::ex().getStrTblText(AETXT_BEST);
    SpaltenLagOrt[4].Columns = CResString::ex().getStrTblText(AETXT_VERFALL);
}

CDArtInf2::~CDArtInf2()
{
}

void CDArtInf2::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_GEN_LAGORT, m_ListLagOrt);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NAME, m_pArtInfData->m_CArtName);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NR, m_pArtInfData->m_CArtNr);
    DDX_Text(pDX, IDC_ST_ARTIKEL_EINHEIT, m_pArtInfData->m_CArtEinh);
    DDX_Text(pDX, IDC_ST_HERSTELLER, m_pArtInfData->m_CHerst);
    DDX_Text(pDX, IDC_ST_DARREICHUNG, m_pArtInfData->m_CArtDarr);
    DDX_Text(pDX, IDC_ST_WAREN_GR, m_pArtInfData->m_CWarenGr);
    DDX_Text(pDX, IDC_ST_THERAPIE_GR, m_pArtInfData->m_CTherapGr);
    DDX_Text(pDX, IDC_ST_NACHFOLGE, m_pArtInfData->m_CNachfArt);
    DDX_Text(pDX, IDC_ST_LAGERART, m_pArtInfData->m_CLagArt);
    DDX_Text(pDX, IDC_ST_CONT_GR, m_pArtInfPackageData->m_CContGr);
    DDX_Text(pDX, IDC_ST_BREITE, m_pArtInfPackageData->m_CBreite);
    DDX_Text(pDX, IDC_ST_GEWICHT, m_pArtInfPackageData->m_CGewicht);
    DDX_Text(pDX, IDC_ST_HOEHE, m_pArtInfPackageData->m_CHoehe);
    DDX_Text(pDX, IDC_ST_LAENGE, m_pArtInfPackageData->m_CLaenge);
    DDX_Text(pDX, IDC_ST_LAUFZEIT_MON, m_pArtInfPackageData->m_CLaufZeit);
    DDX_Text(pDX, IDC_ST_NORM_PACK, m_pArtInfPackageData->m_CNormPack);
    DDX_Text(pDX, IDC_ST_RABATT, m_pArtInfData->m_CRabatt);
    DDX_Text(pDX, IDC_ST_VKE, m_pArtInfPackageData->m_CVke);
    DDX_Text(pDX, IDC_ST_INN_FIELD, m_pArtInfData->m_CInnField);
}

BOOL CDArtInf2::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();

    if (m_init)
    {
        return TRUE;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf2.cpp", "OnSetActive", "Page started");
    m_init = true;
    if (AeGetApp()->IsRS() || AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_INN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_INN)->EnableWindow(TRUE);
        GetDlgItem(IDC_ST_INN_FIELD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_INN_FIELD)->EnableWindow(TRUE);
    }

    if (!CListCtrlHelper::AddColumns(SpaltenLagOrt, m_ListLagOrt))
    {
        return FALSE;
    }

    //Lagerlistbox füllen
    char str[81];
    CStringArray s;
    s.SetSize(NUM_SPALT_LAGORT);
    CARTLAGER artlager;
    artlager.s.FILIALNR   = m_pArtInfData->m_FilialNr;
    artlager.s.ARTIKEL_NR = m_pArtInfData->m_ArtikelNr;
    artlager.s.FETCH_REL  = 1;         //normaler Fetch
    BeginWaitCursor();
    for (;;)
    {
        artlager.Server(AatartLagerinf);
        if (artlager.rc == SRV_SQLNOTFOUND)
            break;
        else if (artlager.rc < SRV_OK)
        {
            EndWaitCursor();
            return FALSE;
        }
        //Ausgabe in die Listbox
        s[0] = artlager.s.LAGERFACHNR;
        sprintf(str, "%d", artlager.s.LAGERBEREICHNR);
        s[1] = str;
        s[2] = artlager.s.STATIONNR;
        sprintf(str, "" /*artlager.s.BESTAND*/);       //nase
        s[3] = str;
        sprintf( str, "%02d/%02d", artlager.s.DATUMVERFALL%100, artlager.s.DATUMVERFALL/100 );
        s[4] = str;

        if (!CListCtrlHelper::AppendItem(m_ListLagOrt, NUM_SPALT_LAGORT, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    artlager.s.FETCH_REL = 0;          //Close Cursor
    artlager.Server(AatartLagerinf);
    EndWaitCursor();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDArtInf2, CPropertyPageMultiLang)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDArtInf2 message handlers
/////////////////////////////////////////////////////////////////////////////
// CDArtInf3 property page

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES SpaltenOffeneBestellungen[] =
{
    0,  "", 50, LVCFMT_LEFT,
    1,  "", 45, LVCFMT_RIGHT,
    2,  "", 47, LVCFMT_RIGHT,
    3,  "", 54, LVCFMT_LEFT,
    -1, "",  0, 0
};

#define NUM_SPALT_OFF_BEST 4

IMPLEMENT_DYNCREATE(CDArtInf3, CPropertyPageMultiLang)

CDArtInf3::CDArtInf3()
{
}

CDArtInf3::CDArtInf3(SArtInfData* pArtInfData) : CPropertyPageMultiLang(CDArtInf3::IDD), m_pArtInfData(pArtInfData)
{
    m_CHomePage = _T("");
    m_CEmail = _T("");
    m_init = false;

    SpaltenOffeneBestellungen[0].Columns = CResString::ex().getStrTblText(AETXT_DAT_WE);
    SpaltenOffeneBestellungen[1].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    SpaltenOffeneBestellungen[2].Columns = CResString::ex().getStrTblText(AETXT_BEST_NR);
    SpaltenOffeneBestellungen[3].Columns = CResString::ex().getStrTblText(AETXT_DAT_BEST);
}

CDArtInf3::~CDArtInf3()
{
}

void CDArtInf3::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_CListOffBest);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NAME, m_pArtInfData->m_CArtName);
    DDX_Text(pDX, IDC_ST_ARTIKEL_EINHEIT, m_pArtInfData->m_CArtEinh);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NR, m_pArtInfData->m_CArtNr);
    DDX_Text(pDX, IDC_ST_HERSTELLER, m_pArtInfData->m_CHerst);
    DDX_Text(pDX, IDC_ST_DARREICHUNG, m_pArtInfData->m_CArtDarr);
    DDX_Text(pDX, IDC_ST_WAREN_GR, m_pArtInfData->m_CWarenGr);
    DDX_Text(pDX, IDC_ST_THERAPIE_GR, m_pArtInfData->m_CTherapGr);
    DDX_Text(pDX, IDC_ST_LAGERART, m_pArtInfData->m_CLagArt);
    DDX_Text(pDX, IDC_ST_NACHFOLGE, m_pArtInfData->m_CNachfArt);
    DDX_Text(pDX, IDC_ST_RABATT, m_pArtInfData->m_CRabatt);
    DDX_Text(pDX, IDC_ST_INN_FIELD, m_pArtInfData->m_CInnField);
}

BEGIN_MESSAGE_MAP(CDArtInf3, CPropertyPageMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_INFOLISTE, OnButtonInfoliste)
    ON_BN_CLICKED(IDC_BUTTON_WISSENSDB, OnButtonWissensDB)
    ON_BN_CLICKED(IDC_BUTTON_INTERNET, OnButtonInternet)
    ON_BN_CLICKED(IDC_BUTTON_GOOGLE, OnButtonGoogle)
    ON_BN_CLICKED(IDC_BUTTON_EMAIL, OnButtonEMail)
END_MESSAGE_MAP()

BOOL CDArtInf3::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();

    if (m_init)
    {
        return TRUE;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf3.cpp", "OnSetActive", "Page started");
    m_init = true;
    if (!AeGetApp()->IsDE() && !AeGetApp()->IsCH())
    {
        GetDlgItem(IDC_BUTTON_INFOLISTE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_INFOLISTE)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_EMAIL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_EMAIL)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_INFOLISTE)->SetFocus();
    }
    if (AeGetApp()->IsRS() || AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_INN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_INN)->EnableWindow(TRUE);
        GetDlgItem(IDC_ST_INN_FIELD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_INN_FIELD)->EnableWindow(TRUE);
    }
    CARTINFHERSTE artinfherste;
    CARTLIEFER artliefer;
    artliefer.s.ARTIKEL_NR = m_pArtInfData->m_ArtikelNr;
    artliefer.Server(AatartSel_artlief);
    if (artliefer.rc == SRV_OK) //Satz wurde gefunden
    {
        GetDlgItem(IDC_STATIC_ARTIKEL_LIEFERANT)->SetWindowText(artliefer.s.ARTIKEL_NR_BLIEFER);
    }
    artinfherste.s.HERSTELLER_NR = m_lHerstNr;
    artinfherste.Server(AatartSel_hersteller);
    if (artinfherste.rc == SRV_OK) //Satz wurde gefunden
    {
        AllgEntfSpaces(artinfherste.s.HOMEPAGE);
        m_CHomePage = artinfherste.s.HOMEPAGE;
        GetDlgItem(IDC_STATIC_HERST_NAME   )->SetWindowText(artinfherste.s.NAME);
        GetDlgItem(IDC_STATIC_HERST_ORT    )->SetWindowText(artinfherste.s.ORT);
        GetDlgItem(IDC_STATIC_HERST_STRASSE)->SetWindowText(artinfherste.s.STRASSE);
        GetDlgItem(IDC_STATIC_HERST_VORW   )->SetWindowText(artinfherste.s.VORWAHL);
        GetDlgItem(IDC_STATIC_HERST_TEL    )->SetWindowText(artinfherste.s.TELEFON_NR);
        GetDlgItem(IDC_STATIC_HERST_VORW_FAX)->SetWindowText(artinfherste.s.VORWAHL_TELEFAX);
        GetDlgItem(IDC_STATIC_HERST_FAX    )->SetWindowText(artinfherste.s.FAX_NR);
    }

    if (!CListCtrlHelper::AddColumns(SpaltenOffeneBestellungen, m_CListOffBest))
    {
        return FALSE;
    }

    //Bestelllistbox füllen
    char str[81];
    CStringArray s;
    s.SetSize(NUM_SPALT_OFF_BEST);
    CARTINFBESTEL artinfbestel;
    artinfbestel.s.ARTIKEL_NR = m_pArtInfData->m_ArtikelNr;
    artinfbestel.s.FETCH_REL  = 1;             //normaler Fetch
    BeginWaitCursor();
    for (;;)
    {
        artinfbestel.Server(AatartSel_offene_bstlng);
        if (artinfbestel.rc == SRV_SQLNOTFOUND)
            break;
        else if (artinfbestel.rc < SRV_OK)
        {
            EndWaitCursor();
            return FALSE;
        }
        //Ausgabe in die Listbox
        if (artinfbestel.s.BEST_WIRKSAM[0] == '1')
        {
            s[0] = AllgDatumLong2CharTTMMJJ(artinfbestel.s.DATUM_WE_SOLL, str);
        }
        else
        {
            s[0] = "XX.XX.XX";
        }
        s[1].Format("%d", artinfbestel.s.MENGE_BESTELL);
        s[2].Format("%d", artinfbestel.s.BESTELL_NR);
        s[3] = AllgDatumLong2CharTTMMJJ(artinfbestel.s.DATUM_BESTELL, str);

        if (!CListCtrlHelper::AppendItem(m_CListOffBest, NUM_SPALT_OFF_BEST, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    artinfbestel.s.FETCH_REL = 0;          //Close Cursor
    artinfbestel.Server(AatartSel_offene_bstlng);
    EndWaitCursor();

    return TRUE;
}

void CDArtInf3::OnButtonEMail()
{
    if (m_pArtInfData->m_lKndNr == -1)
    {
        //Definition Kunde
        CDKndWahl dlgKndWahl;
        //dlgKndWahl.SetEnableAeGesperrt();  // Checkbutton muß enabled werden
        if (dlgKndWahl.DoModal() == IDOK)
        {
            m_pArtInfData->m_lKndNr = dlgKndWahl.GetIdfNr();
            m_pArtInfData->m_lKndNr = dlgKndWahl.GetKndNr();
            m_VzNr = dlgKndWahl.GetKndVz();
        }
    }
    else
    {
        m_VzNr = m_pArtInfData->m_FilialNr;
    }
    if (m_pArtInfData->m_lKndNr != -1)
    {
        CKNDINF kndinf;
        kndinf.s.IDFNR              = m_pArtInfData->m_lKndNr;
        kndinf.s.KUNDENNR           = m_pArtInfData->m_lKndNr;
        kndinf.s.VERTRIEBSZENTRUMNR = m_VzNr;
        kndinf.Server(AakundeSel_knd_info);
        AllgEntfSpaces(kndinf.s.EMAILADRESSE);
        m_CEmail = kndinf.s.EMAILADRESSE;
    }
    CString MailKopfDaten;
    MailKopfDaten.Format("mailto:%s?subject=%s", m_CEmail.GetString(), m_pArtInfData->m_CArtName.GetString());
    ShellExecute(this->GetSafeHwnd(), "open", MailKopfDaten, NULL, NULL, SW_SHOW);
}

void CDArtInf3::OnButtonInfoliste()
{
    GetDlgItem(IDC_BUTTON_INFOLISTE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_INFOLISTE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_WISSENSDB)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BUTTON_WISSENSDB)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_WISSENSDB)->SetFocus();
    CDInfoListe dlgInfoListe;
    dlgInfoListe.m_such = m_pArtInfData->m_CArtName.Left(26);
    dlgInfoListe.DoModal();
}

void CDArtInf3::OnButtonWissensDB()
{
    GetDlgItem(IDC_BUTTON_WISSENSDB)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_WISSENSDB)->EnableWindow(FALSE);
    if (!m_CHomePage.IsEmpty())
    {
        GetDlgItem(IDC_BUTTON_INTERNET)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_INTERNET)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_INTERNET)->SetFocus();
    }
    else
    {
        GetDlgItem(IDC_BUTTON_GOOGLE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_GOOGLE)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_GOOGLE)->SetFocus();
    }
    ShellExecute(0, NULL, "https://www.phoenix-online.de/apotheken/wissensdatenbank/recherche", NULL, NULL, SW_SHOWDEFAULT);
}

void CDArtInf3::OnButtonInternet()
{
    GetDlgItem(IDC_BUTTON_INTERNET)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_INTERNET)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_GOOGLE)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BUTTON_GOOGLE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_GOOGLE)->SetFocus();
    CString url;
    url.Format("http://%s", m_CHomePage.GetString());
    ShellExecute(0, NULL, url, NULL, NULL, SW_SHOWDEFAULT);
}

void CDArtInf3::OnButtonGoogle()
{
    GetDlgItem(IDC_BUTTON_GOOGLE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_GOOGLE)->EnableWindow(FALSE);
    CString url;
    url.Format("http://www.google.de/#q=%s", m_pArtInfData->m_CArtName.Left(26).GetString());
    ShellExecute(0, NULL, url, NULL, NULL, SW_SHOWDEFAULT);
}


/////////////////////////////////////////////////////////////////////////////
// CDArtInf3 message handlers
/////////////////////////////////////////////////////////////////////////////
// CDARTINF4 dialog

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES SpaltenBestand[] =
{
    0,  "",  40, LVCFMT_CENTER,
    1,  "",  50, LVCFMT_RIGHT,
    2,  "", 200, LVCFMT_LEFT,
    -1, "",   0, 0
};

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES SpaltenVerbund[] =
{
    0,  "", 40, LVCFMT_CENTER,
    1,  "", 50, LVCFMT_RIGHT,
    2,  "",  0, LVCFMT_LEFT,
    -1, "",  0, 0
};

#define NUM_SPALT_BESTAND 3

IMPLEMENT_DYNCREATE(CDArtInf4, CPropertyPageMultiLang)

CDArtInf4::CDArtInf4()
{
}

CDArtInf4::CDArtInf4(SArtInfData* pArtInfData, SArtInfIbtData* pArtInfIbtData) : CPropertyPageMultiLang(CDArtInf4::IDD)
, m_pArtInfData(pArtInfData), m_pArtInfIbtData(pArtInfIbtData)
{
    m_init = false;

    SpaltenBestand[0].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    SpaltenBestand[1].Columns = CResString::ex().getStrTblText(AETXT_KURZ_BESTAND);
    SpaltenBestand[2].Columns = CResString::ex().getStrTblText(AETXT_VB_TYP);

    SpaltenVerbund[0].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    SpaltenVerbund[1].Columns = CResString::ex().getStrTblText(AETXT_KURZ_BESTAND);
    SpaltenVerbund[2].Columns = CResString::ex().getStrTblText(AETXT_VB_TYP);
}

CDArtInf4::~CDArtInf4()
{
}

void CDArtInf4::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST3, m_ListStockNotActiveIbt);
    DDX_Control(pDX, IDC_LIST2, m_ListStockDailyStart);
    DDX_Control(pDX, IDC_LIST1, m_ListStockActive);
    DDX_Text(pDX, IDC_ST_ARTIKEL_EINHEIT, m_pArtInfData->m_CArtEinh);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NAME, m_pArtInfData->m_CArtName);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NR, m_pArtInfData->m_CArtNr);
    DDX_Text(pDX, IDC_ST_DARREICHUNG, m_pArtInfData->m_CArtDarr);
    DDX_Text(pDX, IDC_ST_HERSTELLER, m_pArtInfData->m_CHerst);
    DDX_Text(pDX, IDC_ST_LAGERART, m_pArtInfData->m_CLagArt);
    DDX_Text(pDX, IDC_ST_NACHFOLGE, m_pArtInfData->m_CNachfArt);
    DDX_Text(pDX, IDC_ST_THERAPIE_GR, m_pArtInfData->m_CTherapGr);
    DDX_Text(pDX, IDC_ST_WAREN_GR, m_pArtInfData->m_CWarenGr);
    DDX_Text(pDX, IDC_ST_RABATT, m_pArtInfData->m_CRabatt);
    DDX_Text(pDX, IDC_ST_INN_FIELD, m_pArtInfData->m_CInnField);
}

BOOL CDArtInf4::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();

    if (m_init)
    {
        return TRUE;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf4.cpp", "OnSetActive", "Page started");
    m_init = true;
    if (   (AeGetApp()->IsNLevelIBT() && m_pArtInfData->m_lKndNr == -1)
        || (AeGetApp()->IsNLevelIBTCst() && m_pArtInfData->m_lKndNr != -1) )
    {
        if (!m_pArtInfIbtData->m_ibttypename.GetAt(0).IsEmpty())
        {
            GetDlgItem(IDC_STATIC_VB_TYP)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_VB_TYP)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_IBT_TYPE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_IBT_TYPE)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_IBT_TYPE)->SetWindowTextA(m_pArtInfIbtData->m_ibttypename.GetAt(0));
        }
    }
    if (AeGetApp()->IsDE())
    {
        GetDlgItem(IDC_STATIC_ANFANG)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ANFANG)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LIST2)->EnableWindow(FALSE);
    }
    if (AeGetApp()->IsRS() || AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_INN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_INN)->EnableWindow(TRUE);
        GetDlgItem(IDC_ST_INN_FIELD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_INN_FIELD)->EnableWindow(TRUE);
    }

    if (   !CListCtrlHelper::AddColumns(SpaltenBestand, m_ListStockActive)
        || !CListCtrlHelper::AddColumns(SpaltenBestand, m_ListStockNotActiveIbt)
        || !CListCtrlHelper::AddColumns(SpaltenVerbund, m_ListStockDailyStart) )
    {
        return FALSE;
    }

    //Listbox füllen
    char str[81];
    CStringArray s;
    s.SetSize(NUM_SPALT_BESTAND);

    BeginWaitCursor();
    if (   (AeGetApp()->IsNLevelIBT() && m_pArtInfData->m_lKndNr == -1)
        || (AeGetApp()->IsNLevelIBTCst() && m_pArtInfData->m_lKndNr != -1) )
    {
        CString notfili;
        notfili.Format("(%d", m_pArtInfData->m_FilialNr);

        CAUFALTLAGORT aufaltlagort;
        aufaltlagort.s.ARTIKEL_NR = m_pArtInfData->m_ArtikelNr;
        aufaltlagort.s.FILIALNR = m_pArtInfData->m_FilialNr;

        for (;;) //aktive VB-Filialen
        {
            //break;
            aufaltlagort.Server( AasrvGetIBTStockLevel );
            if (aufaltlagort.rc != SRV_OK)
                break;
            sprintf(str, "%d", aufaltlagort.s.FILIALNR);
            notfili += ",";
            notfili += str;
            s[0] = str;
            s[1] = UpdateStock(aufaltlagort.s.BESTAND);
            s[2] = aufaltlagort.s.IBTTYPENAME;

            if (aufaltlagort.s.DELIVERYTIMEIBT == 1) //VB aktiv
            {
                if (!InsertStockActive(s))
                {
                    return FALSE;
                }
            }
            else  //VB nicht aktiv
            {
                if (!InsertStockNotActiveIbt(s))
                {
                    return FALSE;
                }
            }
        }

        notfili += ')';

        CARTSTOCK artstock;
        artstock.SetArtikel_nr(m_pArtInfData->m_ArtikelNr);
        artstock.SetExcludedbranches(notfili);
        for (;;) //nicht VB-Filialen
        {
            if (artstock.SelList() != SRV_OK) break;
            sprintf(str, "%d", artstock.GetFilialnr());
            s[0] = str;
            sprintf(str, "%ld", artstock.GetBestand() );
            s[1] = str;
            s[2].Empty();
            if (!InsertStockDailyStart(s))
            {
                return FALSE;
            }
        }
    }
    else if (   m_pArtInfIbtData->m_CVerbundartikel > '0'
             || m_CPrisoart == '2'
             || AeGetApp()->IsBG() )
    {
        CString cIBTType;
        int gefunden;
        short sVBTyp;

        CTM tm;
        tm.Server(AafilGetdatetime);

        CARTLAGER artlager;
        artlager.s.ARTIKEL_NR = m_pArtInfData->m_ArtikelNr;
        artlager.s.FILIALNR = m_pArtInfData->m_FilialNr;
        artlager.s.FETCH_REL = 1;         //normaler Fetch

        for (;;)
        {
            artlager.s.STATIONNR[0] = AeGetApp()->IsBG() ? '0' : '1';
            artlager.Server(AatartSel_lagerbest);
            if (artlager.rc == SRV_SQLNOTFOUND)
            {
                break;
            }
            else if (artlager.rc < SRV_OK)
            {
                EndWaitCursor();
                return FALSE;
            }
            cIBTType.Empty();
            gefunden = 0;
            sVBTyp = 99;
            if (   (AeGetApp()->UseTourManager() > 0 && m_pArtInfData->m_lKndNr == -1)
                || (AeGetApp()->UseTourManagerCst() > 0 && m_pArtInfData->m_lKndNr != -1) )
            {
                vector<nlevelibtbranchesS>::iterator nlt = AeGetApp()->m_ibtfil.beginList();
                for ( ;nlt != AeGetApp()->m_ibtfil.endList(); nlt++)
                {
                    if (artlager.s.FILIALNR == nlt->IBTBRANCHNO &&
                        tm.s.ZEIT >= nlt->ZEITBEGIN &&
                        tm.s.ZEIT <= nlt->ZEITENDE &&
                        m_pArtInfData->m_FilialNr == nlt->BRANCHNO )
                    {
                        if (nlt->IBTTYPE == 4) continue;    //ignore Tagverbund
                        if (m_pArtInfIbtData->m_CVerbundartikel != '2' && nlt->IBTTYPE == 1) continue; //Privatsortimt auch nur wenn der Artikel auch so gekennzeichnet ist
                        sVBTyp = nlt->IBTTYPE;
                        break;
                    }
                }
            }
            else
            {
                vector<vbfilialenS>::iterator it = AeGetApp()->m_vbfil.beginList();
                for ( ;it != AeGetApp()->m_vbfil.endList(); it++)
                {
                    if (artlager.s.FILIALNR == it->VERBUNDFILIALNR &&
                        tm.s.ZEIT >= it->ZEITBEGIN &&
                        tm.s.ZEIT <= it->ZEITENDE &&
                        m_pArtInfData->m_FilialNr == it->FILIALNR )
                    {
                        if (it->VBTYP == 4) continue;   //ignore Tagverbund
                        if (m_pArtInfIbtData->m_CVerbundartikel != '2' && it->VBTYP == 1) continue; //Privatsortimt auch nur wenn der Artikel auch so gekennzeichnet ist
                        sVBTyp = it->VBTYP;
                        break;
                    }
                }
            }
            if (GetIbtType(cIBTType, sVBTyp))
            {
                gefunden = 1;
            }

            if (gefunden != 1)
            {
                sVBTyp = 99;
                if (   (AeGetApp()->UseTourManager() > 0 && m_pArtInfData->m_lKndNr == -1)
                    || (AeGetApp()->UseTourManagerCst() > 0 && m_pArtInfData->m_lKndNr != -1) )
                {
                    vector<nlevelibtbranchesS>::iterator nlt = AeGetApp()->m_ibtfil.beginList();
                    for ( ;nlt != AeGetApp()->m_ibtfil.endList(); nlt++)
                    {
                        if (artlager.s.FILIALNR == nlt->IBTBRANCHNO &&
                            m_pArtInfData->m_FilialNr == nlt->BRANCHNO )
                        {
                            sVBTyp = nlt->IBTTYPE;
                            break;
                        }
                    }
                }
                else
                {
                    vector<vbfilialenS>::iterator it = AeGetApp()->m_vbfil.beginList();
                    for ( ;it != AeGetApp()->m_vbfil.endList(); it++)
                    {
                        if (artlager.s.FILIALNR == it->VERBUNDFILIALNR &&
                            m_pArtInfData->m_FilialNr == it->FILIALNR )
                        {
                            sVBTyp = it->VBTYP;
                            break;
                        }
                    }
                }
                if (GetIbtType(cIBTType, sVBTyp))
                {
                    gefunden = 2;
                }
            }

            //CString fili;
            //fili = artlager.s.FILIALNR -1;
            //tabelle[fili] = 0;
            // eigene Filiale nicht mit ausgeben !!
            if (artlager.s.FILIALNR == m_pArtInfData->m_FilialNr) continue;
            //Ausgabe in die Listbox
            sprintf(str, "%d", artlager.s.FILIALNR);
            s[0] = str;
            s[1] = UpdateStock(artlager.s.BESTAND);
            s[2] = cIBTType;
            if (gefunden == 1)
            {
                if (!InsertStockActive(s))
                {
                    return FALSE;
                }
            }
            else if (gefunden == 2)
            {
                if (!InsertStockNotActiveIbt(s))
                {
                    return FALSE;
                }
            }
            else
            {
                if (!InsertStockDailyStart(s))
                {
                    return FALSE;
                }
            }
        }
        artlager.s.FETCH_REL  = 0;             //Close Cursor
        artlager.Server(AatartSel_lagerbest);
    }

    EndWaitCursor();
    return TRUE;
}

bool CDArtInf4::GetIbtType(CString& ibtType, const short sIbtType)
{
    if (sIbtType == 99)
    {
        return false;
    }

    if (m_pArtInfIbtData->m_CVerbundartikel == '1' && sIbtType == 0)        //lokal
    {
        GetIbtType(ibtType, AETXT_VB_LOKAL, AETXT_LOKAL);
    }
    else if (m_pArtInfIbtData->m_CVerbundartikel == '2' && sIbtType == 1)   //Priso
    {
        GetIbtType(ibtType, AETXT_VB_PRISO, AETXT_PRIVATSORTIMENT);
    }
    else if (m_pArtInfIbtData->m_CVerbundartikel == '3' && sIbtType == 2)   //Veto
    {
        GetIbtType(ibtType, AETXT_VB_VETO, AETXT_VB_VETO);
    }
    else if (m_pArtInfIbtData->m_CVerbundartikel == '4' && sIbtType == 3)   //Regional
    {
        GetIbtType(ibtType, AETXT_VB_REGIONAL, AETXT_REGIONAL);
    }
    else if (m_pArtInfIbtData->m_CVerbundartikel == '5' && sIbtType == 5)   //National
    {
        GetIbtType(ibtType, AETXT_VB_NATIONAL, AETXT_NATIONAL);
    }
    else if (m_pArtInfIbtData->m_CVerbundartikel == '6')                    //Regional + National
    {
        if (sIbtType == 3)
        {
            GetIbtType(ibtType, AETXT_VB_REGIONAL, AETXT_REGIONAL);
        }
        else if (sIbtType == 5)
        {
            GetIbtType(ibtType, AETXT_VB_NATIONAL, AETXT_NATIONAL);
        }
        else
        {
            return false;
        }
    }
    else if (m_pArtInfIbtData->m_CVerbundartikel == '7')                    //Lokal + National
    {
        if (sIbtType == 0)
        {
            GetIbtType(ibtType, AETXT_VB_LOKAL, AETXT_LOKAL);
        }
        else if (sIbtType == 5)
        {
            GetIbtType(ibtType, AETXT_VB_NATIONAL, AETXT_NATIONAL);
        }
        else
        {
            return false;
        }
    }
    else if (m_pArtInfIbtData->m_CVerbundartikel == '8')                    //Lokal + Regional
    {
        if (sIbtType == 0)
        {
            GetIbtType(ibtType, AETXT_VB_LOKAL, AETXT_LOKAL);
        }
        else if (sIbtType == 3)
        {
            GetIbtType(ibtType, AETXT_VB_REGIONAL, AETXT_REGIONAL);
        }
        else
        {
            return false;
        }
    }
    else if (m_pArtInfIbtData->m_CVerbundartikel == '9')                    //Lokal + Regional + National
    {
        if (sIbtType == 0)
        {
            GetIbtType(ibtType, AETXT_VB_LOKAL, AETXT_LOKAL);
        }
        else if (sIbtType == 3)
        {
            GetIbtType(ibtType, AETXT_VB_REGIONAL, AETXT_REGIONAL);
        }
        else if (sIbtType == 5)
        {
            GetIbtType(ibtType, AETXT_VB_NATIONAL, AETXT_NATIONAL);
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

void CDArtInf4::GetIbtType(CString& ibtType, UINT uiTextIfEmpty, UINT uiTextElse)
{
    if (ibtType.IsEmpty())
    {
        ibtType = CResString::ex().getStrTblText(uiTextIfEmpty);
    }
    else
    {
        ibtType += " + ";
        ibtType += CResString::ex().getStrTblText(uiTextElse);
    }
}

bool CDArtInf4::InsertStockActive(CStringArray& s)
{
    if (!CListCtrlHelper::AppendItem(m_ListStockActive, NUM_SPALT_BESTAND, s))
    {
        EndWaitCursor();
        return false;
    }
    return true;
}

bool CDArtInf4::InsertStockNotActiveIbt(CStringArray& s)
{
    if (!CListCtrlHelper::AppendItem(m_ListStockNotActiveIbt, NUM_SPALT_BESTAND, s))
    {
        EndWaitCursor();
        return false;
    }
    return true;
}

bool CDArtInf4::InsertStockDailyStart(CStringArray& s)
{
    if (!CListCtrlHelper::AppendItem(m_ListStockDailyStart, NUM_SPALT_BESTAND, s))
    {
        EndWaitCursor();
        return false;
    }
    return true;
}

CString CDArtInf4::UpdateStock(long& lStock)
{
    if (!m_bCheck)
    {
        if (m_lRest >= 0)
        {
            if (m_lRest < lStock)
            {
                lStock = m_lRest;
            }
        }
        else
        {
            lStock = 0L;
        }
    }
    CString str;
    str.Format("%ld", lStock);
    return str;
}

BEGIN_MESSAGE_MAP(CDArtInf4, CPropertyPageMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDARTINF4 dialog

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES Rabatte[] =
{
    0,  "",  50, LVCFMT_CENTER,
    1,  "",  50, LVCFMT_RIGHT,
    2,  "",  40, LVCFMT_RIGHT,
    3,  "",  80, LVCFMT_LEFT,
    4,  "",   0, LVCFMT_RIGHT,
    5,  "",  70, LVCFMT_LEFT,
    6,  "",  70, LVCFMT_LEFT,
    7,  "", 150, LVCFMT_LEFT,
    8,  "",  80, LVCFMT_LEFT,
    9,  "",   0, LVCFMT_RIGHT,
    10, "",   0, LVCFMT_LEFT,
    11, "",   0, LVCFMT_LEFT,
    12, "",   0, LVCFMT_LEFT,
    13, "",   0, LVCFMT_LEFT,
    14, "",  40, LVCFMT_CENTER,
    15, "",  60, LVCFMT_CENTER,
    -1, "",   0, 0
};
#define NUM_RABATTE 16

static COLUMNS_TYPES OMGRabatte[] =
{
    0,  "", 100, LVCFMT_RIGHT,
    1,  "",  50, LVCFMT_RIGHT,
    2,  "",  80, LVCFMT_RIGHT,
    3,  "",  80, LVCFMT_LEFT,
    4,  "",  80, LVCFMT_LEFT,
    5,  "", 150, LVCFMT_LEFT,
    6,  "",  60, LVCFMT_CENTER,
    7,  "",  60, LVCFMT_CENTER,
    -1, "",   0, 0
};
#define NUM_OMGRABATTE 8

// CDArtInf5-Dialogfeld

IMPLEMENT_DYNAMIC(CDArtInf5, CPropertyPageMultiLang)

CDArtInf5::CDArtInf5(SArtInfData* pArtInfData, SArtInfDiscountData* pArtInfDiscountData)
    : CPropertyPageMultiLang(CDArtInf5::IDD), m_pArtInfData(pArtInfData), m_pArtInfDiscountData(pArtInfDiscountData)
{
    m_init = false;
    Rabatte[0].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Rabatte[1].Columns = CResString::ex().getStrTblText(AETXT_RABATT);
    Rabatte[2].Columns = CResString::ex().getStrTblText(AETXT_WERT);
    Rabatte[3].Columns = CResString::ex().getStrTblText(AETXT_ART);
    Rabatte[4].Columns = CResString::ex().getStrTblText(AETXT_ZZ);
    Rabatte[5].Columns = CResString::ex().getStrTblText(AETXT_VON);
    Rabatte[6].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    Rabatte[7].Columns = CResString::ex().getStrTblText(AETXT_EKGRUPPE);

    if (AeGetApp()->IsCH())
    {
        Rabatte[8].Columns = CResString::ex().getStrTblText(AETXT_IDF);
        Rabatte[9].Columns = CResString::ex().getStrTblText(AETXT_RBG);
    }

    Rabatte[10].Columns = CResString::ex().getStrTblText(AETXT_RABATT_FORM);
    Rabatte[11].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Rabatte[12].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Rabatte[13].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);

    if (AeGetApp()->IsCH())
    {
        Rabatte[14].Columns = CResString::ex().getStrTblText(AETXT_RABATT_AUF);
        Rabatte[15].Columns = CResString::ex().getStrTblText(AETXT_RABATT_ABG_VON);
    }

    OMGRabatte[0].Columns = CResString::ex().getStrTblText(AETXT_VEREINBART);
    OMGRabatte[1].Columns = CResString::ex().getStrTblText(AETXT_REST);
    OMGRabatte[2].Columns = CResString::ex().getStrTblText(AETXT_RABATT);
    OMGRabatte[3].Columns = CResString::ex().getStrTblText(AETXT_VON);
    OMGRabatte[4].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    OMGRabatte[5].Columns = CResString::ex().getStrTblText(AETXT_EKGRUPPE);

    if (AeGetApp()->IsCH())
    {
        OMGRabatte[6].Columns = CResString::ex().getStrTblText(AETXT_RABATT_AUF);
        OMGRabatte[7].Columns = CResString::ex().getStrTblText(AETXT_RABATT_ABG_VON);
    }
}

CDArtInf5::~CDArtInf5()
{
}

void CDArtInf5::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_LIST_OMG, m_ListOMG);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NAME, m_pArtInfData->m_CArtName);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NR, m_pArtInfData->m_CArtNr);
    DDX_Text(pDX, IDC_ST_ARTIKEL_EINHEIT, m_pArtInfData->m_CArtEinh);
    DDX_Text(pDX, IDC_ST_HERSTELLER, m_pArtInfData->m_CHerst);
    DDX_Text(pDX, IDC_ST_NACHFOLGE, m_pArtInfData->m_CNachfArt);
    DDX_Text(pDX, IDC_ST_DARREICHUNG, m_pArtInfData->m_CArtDarr);
    DDX_Text(pDX, IDC_ST_WAREN_GR, m_pArtInfData->m_CWarenGr);
    DDX_Text(pDX, IDC_ST_THERAPIE_GR, m_pArtInfData->m_CTherapGr);
    DDX_Text(pDX, IDC_ST_RABATT, m_pArtInfData->m_CRabatt);
    DDX_Text(pDX, IDC_ST_LAGERART, m_pArtInfData->m_CLagArt);
    DDX_Text(pDX, IDC_ST_INN_FIELD, m_pArtInfData->m_CInnField);
}

BEGIN_MESSAGE_MAP(CDArtInf5, CPropertyPage)
END_MESSAGE_MAP()

BOOL CDArtInf5::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();
    bool bIcon = false;
    if (m_init)
    {
        return TRUE;
    }

    if (!AeGetApp()->IsCH())
    {
        Rabatte[8].Width = 0;
        Rabatte[9].Width = 0;
        Rabatte[14].Width = 0;
        Rabatte[15].Width = 0;
        OMGRabatte[6].Width = 0;
        OMGRabatte[7].Width = 0;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf5.cpp", "OnSetActive", "Page started");
    m_init = true;
    if (AeGetApp()->IsRS() || AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_INN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_INN)->EnableWindow(TRUE);
        GetDlgItem(IDC_ST_INN_FIELD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_INN_FIELD)->EnableWindow(TRUE);
    }

    if (AeGetApp()->IsCH())
    {
        HICON hIcon;
        // create the small icon image list
        m_ImageSmall.Create(16, 16, FALSE, 3, 0);   // list won't grow

        hIcon = AfxGetApp()->LoadIcon(IDI_ICON_NOACHTUNG);
        ASSERT(hIcon != NULL);
        m_ImageSmall.Add(hIcon);
        hIcon = AfxGetApp()->LoadIcon(IDI_ICON_ACHTUNG);
        ASSERT(hIcon != NULL);
        m_ImageSmall.Add(hIcon);
        hIcon = AfxGetApp()->LoadIcon(IDI_ICON_OK_GREEN);
        ASSERT(hIcon != NULL);
        m_ImageSmall.Add(hIcon);

        m_List1.SetImageList(&m_ImageSmall, LVSIL_SMALL);

        m_ListOMG.SetImageList(&m_ImageSmall, LVSIL_SMALL);
    }

    if (!m_pArtInfDiscountData->m_bOMGCst)
    {
        if (!CListCtrlHelper::AddColumns(Rabatte, m_List1))
        {
            return FALSE;
        }
    }
    else
    {
        GetDlgItem(IDC_STATIC_RABATTSTAFFEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RABATTSTAFFEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
    }
    if (m_pArtInfDiscountData->m_bOMG)
    {
        if (!CListCtrlHelper::AddColumns(OMGRabatte, m_ListOMG))
        {
            return FALSE;
        }
    }
    else
    {
        GetDlgItem(IDC_STATIC_OMGRABATT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_OMGRABATT)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST_OMG)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LIST_OMG)->EnableWindow(FALSE);
    }

    //Discountlistbox füllen
    int index;
    char str[81];
    CPHARMGRP pharmgrp;
    ppString pStr;
    ppString Grp;
    ppString GrpName;
    CStringArray s;
    s.SetSize(NUM_RABATTE);
    if (!m_pArtInfDiscountData->m_bOMGCst)
    {
        for (vector<discountanzS>::iterator itDisc = m_pArtInfDiscountData->m_lDisc.begin(); itDisc < m_pArtInfDiscountData->m_lDisc.end(); itDisc++)
        {
            if (itDisc->FIXEDPRICE > 0 && itDisc->DISCOUNTVALUEPCT == 0)
            {
                if (AeGetApp()->IsRS())
                {
                    if (itDisc->PAYMENTTARGETNO == 0) continue;
                }
                else
                {
                    continue;
                }
            }
            if (itDisc->DISCOUNTQTY != 0 && itDisc->DISCOUNTARTICLE == 0) continue;
            if (itDisc->CUSTOMERNO != 0 &&
                m_pArtInfData->m_lKndNr != -1 &&
                itDisc->CUSTOMERNO != m_pArtInfData->m_lKndNr) continue;
        //Ausgabe in die Listbox
            sprintf(str, "%d", itDisc->BASEQTY);
            s[0] = str;
            sprintf(str, "%0.2lf", itDisc->DISCOUNTVALUEPCT);
            s[1] = str;
            s[2].Empty();
            if (itDisc->DISCOUNTTYPE == 1)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_SHORT);
            }
            else if (itDisc->DISCOUNTTYPE == 2)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_AKTION);
            }
            else if (itDisc->DISCOUNTTYPE == 3)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_DIABETES);
            }
            else if (itDisc->DISCOUNTTYPE == 4)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_GENERICA);
            }
            else if (itDisc->DISCOUNTTYPE == 5)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_PARTERNARIAT);
            }
            else if (itDisc->DISCOUNTTYPE == 7)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_BAR);
            }
            else if (itDisc->DISCOUNTTYPE == 8)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_PROMOTION);
            }
            else if (itDisc->GROSSPROFITPCT > 0)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_ROHERTRAG);
                sprintf(str, "%0.2lf", itDisc->GROSSPROFITPCT);
                s[2] = str;
            }
            else if (m_iBasis == 1)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_KND_RAB);
            }
            else if (itDisc->DISCOUNTARTICLE != 0)
            {
                s[3] = CResString::ex().getStrTblText(AETXT_NATRA);
                sprintf(str, "%d", itDisc->DISCOUNTQTY);
                s[2] = str;
            }
            else
            {
                s[3].Empty();
            }
            s[4].Empty();
            if (itDisc->PAYMENTTARGETNO > 0)
            {
                m_List1.SetColumnWidth(4, 27);
                s[4].Format("%d", m_pArtInfDiscountData->m_lPay.at(itDisc->PAYMENTTARGETNO - 1).PAYMENTARGET);
            }
            AllgDatumLong2CharTTMMJJJJ(itDisc->DATEFROM,str);
            s[5] = str;
            AllgDatumLong2CharTTMMJJJJ(itDisc->DATETO,str);
            s[6] = str;
            pharmgrp.SetPharmacygroupid(itDisc->PHARMACYGROUPID);
            pharmgrp.SetBranchno(m_pArtInfData->m_FilialNr);
            if (!pharmgrp.Sel())
                s[7] = pharmgrp.GetGroup_name(GrpName);
            else
                s[7] = itDisc->PHARMACYGROUPID;
            if (itDisc->DISCOUNTSPEC == 1)
            {
                s[10] = CResString::ex().getStrTblText(AETXT_LOG);
                sprintf(str, "%0.2lf", itDisc->SURCHARGEPCT);
                s[2] = str;
            }
            else if (itDisc->DISCOUNTSPEC == 2)
            {
                s[10] = CResString::ex().getStrTblText(AETXT_WH);
            }
            else if (itDisc->DISCOUNTSPEC == 3)
            {
                s[10] = CResString::ex().getStrTblText(AETXT_RE);
            }
            else if (itDisc->DISCOUNTSPEC == 4)
            {
                s[10] = CResString::ex().getStrTblText(AETXT_MON_POS);
            }
            else if (itDisc->DISCOUNTSPEC == 5)
            {
                s[10] = CResString::ex().getStrTblText(AETXT_MON_MON);
            }
            else if (itDisc->DISCOUNTSPEC == 6)
            {
                s[10] = CResString::ex().getStrTblText(AETXT_MON_QUA);
            }
            else if (itDisc->DISCOUNTSPEC == 7)
            {
                    s[10] = CResString::ex().getStrTblText(AETXT_INDUSTRIE);
            }
            else if (itDisc->DISCOUNTSPEC == 8)
            {
                    s[10] = CResString::ex().getStrTblText(AETXT_RAB_FREI);
            }
            else if (itDisc->DISCOUNTSPEC == 9)
            {
                    s[10] = CResString::ex().getStrTblText(AETXT_RAB_KKH);
            }
            else if (itDisc->DISCOUNTSPEC == 10)
            {
                s[10] = CResString::ex().getStrTblText(AETXT_OCCASSION);
            }
            else if (itDisc->DISCOUNTSPEC == 12)
            {
                s[10] = CResString::ex().getStrTblText(AETXT_LOGDATATRANSFER);
                sprintf(str, "%0.2lf", itDisc->SURCHARGEPCT);
                s[2] = str;
            }
            else
            {
                    s[10].Empty();
            }
            if (itDisc->DISCOUNTARTICLE > 0)
            {
                CARTINF artinf;
                artinf.s.ARTIKEL_NR = itDisc->DISCOUNTARTICLE;
                artinf.s.FILIALNR = AeGetApp()->VzNr();
                artinf.Server( AatartInf_art_nr );
                if (artinf.rc < SRV_OK)
                {
                    s[11].Empty();
                    s[12].Empty();
                    s[13].Empty();
                }
                else
                {
                    m_List1.SetColumnWidth(11, 50);
                    m_List1.SetColumnWidth(12, 64);
                    m_List1.SetColumnWidth(13, 170);
                    s[11].Format("%d", itDisc->DISCOUNTARTICLE);
                    s[12] = artinf.s.EINHEIT;
                    s[13] = artinf.s.ARTIKEL_NAME;
                }
            }

            if (AeGetApp()->IsCH())
            {
                s[8].Format("%d", itDisc->CUSTOMERNO);
                s[9].Format("%d", itDisc->DISCOUNTGRPNO);
                if (0 == itDisc->DISCOUNTCALCFROM)
                    s[14] = "GEP";
                else
                    s[14] = "AGP";
                if (0 == itDisc->DISCOUNTAPPLYTO)
                    s[15] = "GEP";
                else
                    s[15] = "AGP";

                if ((itDisc->DISCOUNTVALUEPCT > 0.0)
                    && (m_dAGP > 0.0)
                    && (((0 == itDisc->DISCOUNTCALCFROM) && (1 == itDisc->DISCOUNTAPPLYTO) && (m_dAGP < m_dGEP))
                     || ((1 == itDisc->DISCOUNTCALCFROM) && (0 == itDisc->DISCOUNTAPPLYTO) && (m_dAGP > m_dGEP))))
                {
                    bIcon = true;
                }
                else
                {
                    bIcon = false;
                }
            }
            else
            {
                s[8].Empty();
                s[9].Empty();
                s[14].Empty();
                s[15].Empty();
            }
            index = m_List1.GetItemCount();
            if (!CListCtrlHelper::AppendItem(m_List1, NUM_RABATTE, s))
            {
                EndWaitCursor();
                return FALSE;
            }

            if (AeGetApp()->IsCH())
            {
                if (bIcon == true)
                {
                    CListCtrlHelper::SetImageItem(m_List1, index, 0, 1); // attention
                }
                else
                {
                    CListCtrlHelper::SetImageItem(m_List1, index, 0, 2); // ok
                }
            }
        }
    }
    //else - stattdessen um in der Schweiz beides gleichzeitig anzuzeigen:
    if ((m_pArtInfDiscountData->m_bOMGCst) || (AeGetApp()->IsCH()))
    {
        for (vector<articleomgS>::iterator itOmg = m_pArtInfDiscountData->m_lOmg.begin(); itOmg < m_pArtInfDiscountData->m_lOmg.end(); itOmg++)
        {
            s[0].Format("%d", itOmg->CONTRACTQTY);
            s[1].Format("%d", itOmg->RESTQTY);
            s[2].Format("%0.2lf %%", itOmg->ADDDISCOUNTPCT);
            s[3] = DDMMYYYYStringFromDateLong(itOmg->DATEFROM);
            s[4] = DDMMYYYYStringFromDateLong(itOmg->DATETO);
            s[5] = itOmg->PHARMACYGROUPID;
            pharmgrp.SetPharmacygroupid(itOmg->PHARMACYGROUPID);
            pharmgrp.SetBranchno(m_pArtInfData->m_FilialNr);
            s[5] = pharmgrp.Sel() ? itOmg->PHARMACYGROUPID : pharmgrp.GetGroup_name(GrpName);

            if (AeGetApp()->IsCH())
            {
                if (0 == itOmg->DISCOUNTCALCFROM)
                    s[6] = "GEP";
                else
                    s[6] = "AGP";

                if (0 == itOmg->DISCOUNTAPPLYTO)
                    s[7] = "GEP";
                else
                    s[7] = "AGP";

                if ((itOmg->ADDDISCOUNTPCT > 0.0)
                    && (m_dAGP > 0.0)
                    && (((0 == itOmg->DISCOUNTCALCFROM) && (1 == itOmg->DISCOUNTAPPLYTO) && (m_dAGP < m_dGEP))
                     || ((1 == itOmg->DISCOUNTCALCFROM) && (0 == itOmg->DISCOUNTAPPLYTO) && (m_dAGP > m_dGEP))))
                {
                    bIcon = true;
                }
                else
                {
                    bIcon = false;
                }
            }
            else
            {
                s[6].Empty();
                s[7].Empty();
            }

            index = m_ListOMG.GetItemCount();
            if (!CListCtrlHelper::AppendItem(m_ListOMG, NUM_OMGRABATTE, s))
            {
                EndWaitCursor();
                return FALSE;
            }

            if (AeGetApp()->IsCH())
            {
                if (bIcon == true)
                {
                    CListCtrlHelper::SetImageItem(m_ListOMG, index, 0, 1); // attention
                }
                else
                {
                    CListCtrlHelper::SetImageItem(m_ListOMG, index, 0, 2); // ok
                }
            }
        }
    } //ende init

    if (AeGetApp()->IsCH())
    {
        m_pArtInfData->m_CInnField.Format("GEP: %0.2lf / AGP: %0.2lf", m_dGEP, m_dAGP);
        GetDlgItem(IDC_ST_INN_FIELD)->SetWindowText(m_pArtInfData->m_CInnField);
        GetDlgItem(IDC_ST_INN_FIELD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_INN_FIELD)->EnableWindow(TRUE);
    }

    return TRUE;
}

// CDArtInf6-Dialogfeld

IMPLEMENT_DYNAMIC(CDArtInf6, CPropertyPageMultiLang)

CDArtInf6::CDArtInf6(SArtInfData* pArtInfData) : CPropertyPageMultiLang(CDArtInf6::IDD), m_pArtInfData(pArtInfData)
{
    m_init = false;
    m_first = false;
}

CDArtInf6::~CDArtInf6()
{
}

void CDArtInf6::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_TEXT, m_CText);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NAME, m_pArtInfData->m_CArtName);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NR, m_pArtInfData->m_CArtNr);
    DDX_Text(pDX, IDC_ST_ARTIKEL_EINHEIT, m_pArtInfData->m_CArtEinh);
    DDX_Text(pDX, IDC_ST_HERSTELLER, m_pArtInfData->m_CHerst);
    DDX_Text(pDX, IDC_ST_NACHFOLGE, m_pArtInfData->m_CNachfArt);
    DDX_Text(pDX, IDC_ST_DARREICHUNG, m_pArtInfData->m_CArtDarr);
    DDX_Text(pDX, IDC_ST_WAREN_GR, m_pArtInfData->m_CWarenGr);
    DDX_Text(pDX, IDC_ST_THERAPIE_GR, m_pArtInfData->m_CTherapGr);
    DDX_Text(pDX, IDC_ST_RABATT, m_pArtInfData->m_CRabatt);
    DDX_Text(pDX, IDC_ST_LAGERART, m_pArtInfData->m_CLagArt);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_Edit_Text);
    DDX_Text(pDX, IDC_ST_INN_FIELD, m_pArtInfData->m_CInnField);
}

BEGIN_MESSAGE_MAP(CDArtInf6, CPropertyPageMultiLang)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CDArtInf6-Meldungshandler

BOOL CDArtInf6::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();
    if (m_init)
    {
        m_Edit_Text.SetSel(0, 0, FALSE);
        return TRUE;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf6.cpp", "OnSetActive", "Page started");
    m_init = true;
    if (AeGetApp()->IsRS() || AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_INN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_INN)->EnableWindow(TRUE);
        GetDlgItem(IDC_ST_INN_FIELD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_INN_FIELD)->EnableWindow(TRUE);
    }
    CARTINSERT Beilage;
    BeginWaitCursor();
    m_CText.Empty();
    Beilage.SetArticleno(m_pArtInfData->m_ArtikelNr);
    Beilage.SetArtinfotype(0);
    ppString text;
    CString helptext;
    CString spaces(' ',256);
    int len;
    for (;;)
    {
        if (Beilage.SelBeilage()) break;
        Beilage.GetInfotext(text);
        helptext = text;
        len = 256 - helptext.GetLength();
        helptext.Format("%s%*.*s"
            ,helptext.GetString()
            ,len
            ,len
            ,spaces.GetString());
        m_CText += helptext;
    }
    m_CText.TrimRight();
    Beilage.CloseCursor();
    EndWaitCursor();

    UpdateData(FALSE);

    //m_Edit_Text.SetFocus();
    //m_Edit_Text.SetSel( 0, -1, FALSE );
    m_Edit_Text.SetSel(0, 0, FALSE);
    return TRUE;
}

HBRUSH CDArtInf6::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPageMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_EDIT_TEXT)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
        if (!m_first)
        {
            m_first = true;
            m_Edit_Text.SetSel(0, 0, FALSE);
        }
        //SetCursorPos(0,0);
    }
    return hbr;
}

// CDArtInf7-Dialogfeld

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES Reserve[] =
{
    0,  "",  70, LVCFMT_CENTER,
    1,  "", 100, LVCFMT_RIGHT,
    2,  "",  70, LVCFMT_RIGHT,
    3,  "",  50, LVCFMT_RIGHT,
    4,  "", 300, LVCFMT_LEFT,
    5,  "",   0, LVCFMT_RIGHT,
    -1, "",   0, 0
};
#define NUM_RESERVE 6

IMPLEMENT_DYNAMIC(CDArtInf7, CPropertyPageMultiLang)
CDArtInf7::CDArtInf7(SArtInfData* pArtInfData) : CPropertyPageMultiLang(CDArtInf7::IDD), m_pArtInfData(pArtInfData)
{
    m_init = false;
    Reserve[0].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Reserve[1].Columns = CResString::ex().getStrTblText(AETXT_AUFTRAGSNUMMER);
    Reserve[2].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Reserve[3].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Reserve[4].Columns = CResString::ex().getStrTblText(AETXT_TYP);
    Reserve[5].Columns = CResString::ex().getStrTblText(AETXT_TYP);
}

CDArtInf7::~CDArtInf7()
{
}

void CDArtInf7::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NAME, m_pArtInfData->m_CArtName);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NR, m_pArtInfData->m_CArtNr);
    DDX_Text(pDX, IDC_ST_ARTIKEL_EINHEIT, m_pArtInfData->m_CArtEinh);
    DDX_Text(pDX, IDC_ST_HERSTELLER, m_pArtInfData->m_CHerst);
    DDX_Text(pDX, IDC_ST_NACHFOLGE, m_pArtInfData->m_CNachfArt);
    DDX_Text(pDX, IDC_ST_DARREICHUNG, m_pArtInfData->m_CArtDarr);
    DDX_Text(pDX, IDC_ST_WAREN_GR, m_pArtInfData->m_CWarenGr);
    DDX_Text(pDX, IDC_ST_THERAPIE_GR, m_pArtInfData->m_CTherapGr);
    DDX_Text(pDX, IDC_ST_RABATT, m_pArtInfData->m_CRabatt);
    DDX_Text(pDX, IDC_ST_LAGERART, m_pArtInfData->m_CLagArt);
    DDX_Control(pDX, IDC_LIST1, m_ListReserve);
    DDX_Text(pDX, IDC_ST_INN_FIELD, m_pArtInfData->m_CInnField);
}

BEGIN_MESSAGE_MAP(CDArtInf7, CPropertyPageMultiLang)
END_MESSAGE_MAP()

// CDArtInf7-Meldungshandler

BOOL CDArtInf7::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();

    if (m_init)
    {
        return TRUE;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf7.cpp", "OnSetActive", "Page started");
    m_init = true;
    if (AeGetApp()->IsRS() || AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_INN)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_INN)->EnableWindow(TRUE);
        GetDlgItem(IDC_ST_INN_FIELD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_INN_FIELD)->EnableWindow(TRUE);
    }

    if (!CListCtrlHelper::AddColumns(Reserve, m_ListReserve))
    {
        return FALSE;
    }

    //Natralistbox füllen
    CStringArray s;
    s.SetSize(NUM_RESERVE);
    CString str;
    CSTOCKRESERVATION cstreserv;
    cstreserv.SetArticleno(m_pArtInfData->m_ArtikelNr);
    cstreserv.SetBranchno(m_pArtInfData->m_FilialNr);
    BeginWaitCursor();
    for (;;)
    {
        if (cstreserv.SelList() != SRV_OK) break;
        //Ausgabe in die Listbox
        s[0] = DDMMYYYYStringFromDateLong(cstreserv.GetDatefrom());
        str.Format("%d", cstreserv.GetKdauftragnr());
        s[1] = str;
        str.Format("%d", cstreserv.GetCustomerno());
        s[2] = str;
        str.Format("%d", cstreserv.GetReservedqty());
        s[3] = str;
        if (cstreserv.GetReservtype() == 1)
        {
            s[4] = CResString::ex().getStrTblText(AETXT_RESERVETYPE_1);
        }
        else if (cstreserv.GetReservtype() == 6)
        {
            s[4] = CResString::ex().getStrTblText(AETXT_RESERVETYPE_6);
        }
        else if (cstreserv.GetReservtype() == 7)
        {
            s[4] = CResString::ex().getStrTblText(AETXT_RESERVETYPE_7);
        }
        else if (cstreserv.GetReservtype() == 8)
        {
            s[4] = CResString::ex().getStrTblText(AETXT_RESERVETYPE_8);
        }
        else if (cstreserv.GetReservtype() == 9)
        {
            s[4] = CResString::ex().getStrTblText(AETXT_RESERVETYPE_9);
        }
        else if (cstreserv.GetReservtype() == 10)
        {
            s[4] = CResString::ex().getStrTblText(AETXT_RESERVETYPE_10);
        }
        else if (cstreserv.GetReservtype() == 11)
        {
            s[4] = CResString::ex().getStrTblText(AETXT_RESERVETYPE_11);
        }
        else if (cstreserv.GetReservtype() == 12)
        {
            s[4] = CResString::ex().getStrTblText(AETXT_RESERVETYPE_12);
        }
        else
        {
            s[4] = CResString::ex().getStrTblText(AETXT_AUFTRAG);
        }
        str.Format("%d", cstreserv.GetReservtype());
        s[5] = str;

        if (!CListCtrlHelper::AppendItem(m_ListReserve, NUM_RESERVE, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    cstreserv.CloseCursor();
    EndWaitCursor();

    // Reservierte Bestände
    if (   !AddStockReserveToListBox(0, AETXT_RESERVETYPE_0)
        || !AddStockReserveToListBox(2, AETXT_RESERVETYPE_2)
        || !AddStockReserveToListBox(3, AETXT_RESERVETYPE_3)
        || !AddStockReserveToListBox(4, AETXT_RESERVETYPE_4)
        || !AddStockReserveToListBox(5, AETXT_RESERVETYPE_5)
        || !AddStockReserveToListBox(13, AETXT_RESERVETYPE_13)
        || !AddStockReserveToListBox(14, AETXT_RESERVETYPE_14)
        || !AddStockReserveToListBox(15, AETXT_RESERVETYPE_15)   // FMD
        || !AddStockReserveToListBox(16, AETXT_RESERVETYPE_16) ) // CMI
    {
        EndWaitCursor();
        return FALSE;
    }

    UpdateData(FALSE);
    return TRUE;
}

bool CDArtInf7::AddStockReserveToListBox(short reservType, UINT uiStringId)
{
    // Reservierte Bestände
    CARTIKELRESERVE reserv;
    reserv.SetBranchno(m_pArtInfData->m_FilialNr);
    reserv.SetArticleno(m_pArtInfData->m_ArtikelNr);
    reserv.SetReservtype(reservType);
    if (reserv.SelArt() != 0)
    {
        return true;
    }

    //Ausgabe in die Listbox
    CStringArray s;
    s.SetSize(NUM_RESERVE);

    s[0].Empty();
    s[1].Empty();
    s[2].Format("%d", reserv.GetCustomerno());
    s[3].Format("%d", reserv.GetReservedqty());
    s[4] = CResString::ex().getStrTblText(uiStringId);
    s[5].Format("%d", reserv.GetReservtype());

    if (!CListCtrlHelper::AppendItem(m_ListReserve, NUM_RESERVE, s))
    {
        return false;
    }

    return true;
}

// CDArtInf8-Dialogfeld

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES LPPR[] =
{
    0,  "",  70, LVCFMT_CENTER,
    1,  "",  70, LVCFMT_LEFT,
    2,  "",  50, LVCFMT_RIGHT,
    3,  "",  50, LVCFMT_LEFT,
    4,  "", 800, LVCFMT_LEFT,
    -1, "",   0, 0
};
#define NUM_LPPR 5

IMPLEMENT_DYNAMIC(CDArtInf8, CPropertyPageMultiLang)

CDArtInf8::CDArtInf8(SArtInfData* pArtInfData) : CPropertyPageMultiLang(CDArtInf8::IDD), m_pArtInfData(pArtInfData)
{
    m_init = false;
    LPPR[0].Columns = CResString::ex().getStrTblText(AETXT_LPPR);
    LPPR[1].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    LPPR[2].Columns = CResString::ex().getStrTblText(AETXT_BETRAG);
    LPPR[3].Columns = CResString::ex().getStrTblText(AETXT_REMB);
    LPPR[4].Columns = CResString::ex().getStrTblText(AETXT_BESCHREIBUNG);
}

CDArtInf8::~CDArtInf8()
{
}

void CDArtInf8::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NAME, m_pArtInfData->m_CArtName);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NR, m_pArtInfData->m_CArtNr);
    DDX_Text(pDX, IDC_ST_ARTIKEL_EINHEIT, m_pArtInfData->m_CArtEinh);
    DDX_Text(pDX, IDC_ST_HERSTELLER, m_pArtInfData->m_CHerst);
    DDX_Text(pDX, IDC_ST_NACHFOLGE, m_pArtInfData->m_CNachfArt);
    DDX_Text(pDX, IDC_ST_DARREICHUNG, m_pArtInfData->m_CArtDarr);
    DDX_Text(pDX, IDC_ST_WAREN_GR, m_pArtInfData->m_CWarenGr);
    DDX_Text(pDX, IDC_ST_THERAPIE_GR, m_pArtInfData->m_CTherapGr);
    DDX_Text(pDX, IDC_ST_RABATT, m_pArtInfData->m_CRabatt);
    DDX_Text(pDX, IDC_ST_LAGERART, m_pArtInfData->m_CLagArt);
    DDX_Control(pDX, IDC_LIST1, m_ListLPPR);
}

BEGIN_MESSAGE_MAP(CDArtInf8, CPropertyPageMultiLang)
END_MESSAGE_MAP()

// CDArtInf8-Meldungshandler

BOOL CDArtInf8::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();

    if (m_init)
    {
        return TRUE;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf8.cpp", "OnSetActive", "Page started");
    m_init = true;

    if (!CListCtrlHelper::AddColumns(LPPR, m_ListLPPR))
    {
        return FALSE;
    }

    //Natralistbox füllen
    CStringArray s;
    s.SetSize(NUM_LPPR);
    ppString hilfe;
    CARTICLELPPRREIMB lppr;
    lppr.SetArticleno(m_pArtInfData->m_ArtikelNr);
    BeginWaitCursor();
    for (;;)
    {
        if (lppr.SelListArt() != SRV_OK) break;
        //Ausgabe in die Listbox
        s[0] = lppr.GetCode_lppr(hilfe);
        s[1] = DDMMYYYYStringFromDateLong(lppr.GetDatefrom());
        s[2].Format("%0.2lf", lppr.GetReimbursement_val());
        s[3] = CResString::ex().getStrTblText((lppr.GetReimbcalcflag() == 0) ? AETXT_NEIN : AETXT_JA);
        s[4] = lppr.GetLppr_desc(hilfe);

        if (!CListCtrlHelper::AppendItem(m_ListLPPR, NUM_LPPR, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    lppr.CloseCursor();
    EndWaitCursor();

    UpdateData(FALSE);
    return TRUE;
}

// CDArtInf9-Dialogfeld

IMPLEMENT_DYNAMIC(CDArtInf9, CPropertyPageMultiLang)

CDArtInf9::CDArtInf9(SArtInfData* pArtInfData) : CPropertyPageMultiLang(CDArtInf9::IDD), m_pArtInfData(pArtInfData)
{
    m_init = false;
}

CDArtInf9::~CDArtInf9()
{
}

void CDArtInf9::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPageMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NAME, m_pArtInfData->m_CArtName);
    DDX_Text(pDX, IDC_ST_ARTIKEL_NR, m_pArtInfData->m_CArtNr);
    DDX_Text(pDX, IDC_ST_ARTIKEL_EINHEIT, m_pArtInfData->m_CArtEinh);
    DDX_Text(pDX, IDC_ST_HERSTELLER, m_pArtInfData->m_CHerst);
    DDX_Text(pDX, IDC_ST_NACHFOLGE, m_pArtInfData->m_CNachfArt);
    DDX_Text(pDX, IDC_ST_DARREICHUNG, m_pArtInfData->m_CArtDarr);
    DDX_Text(pDX, IDC_ST_WAREN_GR, m_pArtInfData->m_CWarenGr);
    DDX_Text(pDX, IDC_ST_THERAPIE_GR, m_pArtInfData->m_CTherapGr);
    DDX_Text(pDX, IDC_ST_RABATT, m_pArtInfData->m_CRabatt);
    DDX_Text(pDX, IDC_ST_LAGERART, m_pArtInfData->m_CLagArt);
    DDX_Control(pDX, IDC_LIST_BINDUNGEN, m_LstCtrlBindungen);
    DDX_Control(pDX, IDC_LIST_BINDUNGEN_CST, m_LstCtrlBindungenCst);
}

BEGIN_MESSAGE_MAP(CDArtInf9, CPropertyPageMultiLang)
END_MESSAGE_MAP()

// CDArtInf9-Meldungshandler

BOOL CDArtInf9::OnSetActive()
{
    CPropertyPageMultiLang::OnSetActive();

    if (m_init)
    {
        return TRUE;
    }

    AeGetApp()->m_AeLogging.WriteLine(2, "DArtInf9.cpp", "OnSetActive", "Page started");
    m_init = true;

    CARTBUYINGOPTIONS bindArticle;
    bindArticle.SetArtikel_nr(m_pArtInfData->m_ArtikelNr);

    BeginWaitCursor();
    bindArticle.SelBuyingOptions();
    EndWaitCursor();

    long lEtartklasse1 = bindArticle.GetEtartklasse1();
    bool bPsycho = bindArticle.GetKzpsychostoffe() != 'N';

    if (!m_LstCtrlBindungen.SetActive(lEtartklasse1, bPsycho))
    {
        return FALSE;
    }

    /* Jetzt die Kundendaten wenn gueltiger Kunde */
    if (m_pArtInfData->m_lKndNr != -1)
    {
        GetDlgItem(IDC_STATIC_KND_WERTE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_KND_WERTE)->EnableWindow(TRUE);
        GetDlgItem(IDC_LIST_BINDUNGEN_CST)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_LIST_BINDUNGEN_CST)->EnableWindow(TRUE);

        CCSTBUYINGOPTIONS bindCustomer;
        bindCustomer.SetKundennr(m_pArtInfData->m_lKndNr);
        bindCustomer.SetVertriebszentrumnr(m_pArtInfData->m_FilialNr);

        BeginWaitCursor();
        bindCustomer.SelBuyingOptions();
        EndWaitCursor();

        lEtartklasse1 = bindCustomer.GetEtartklasse1();
        bPsycho = bindCustomer.GetKzpsychostoffe() == '1';

        if (!m_LstCtrlBindungenCst.SetActive(lEtartklasse1, bPsycho))
        {
            return FALSE;
        }
    }

    UpdateData(FALSE);
    return TRUE;
}
