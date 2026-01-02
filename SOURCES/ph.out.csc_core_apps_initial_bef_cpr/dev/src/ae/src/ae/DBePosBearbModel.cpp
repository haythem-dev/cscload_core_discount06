#include "stdafx.h"
#include "DBePosBearbModel.h"

#include "DBePosBearbData.h"
#include <artsel.h>
#include <artikel.h>

void CDBePosBearbModel::ReadArticle(long lArticleNo, ARTAESEL& article)
{
    //Liefermoeglichkeiten ausgeben
    CARTAESEL artaesel;
    artaesel.s.ARTIKEL_NR = lArticleNo;
    artaesel.s.FILIALNR = AeGetApp()->FilialNrActual();
    artaesel.s.ETARTKLASSE1 = AeGetApp()->KndKlasse1();
    artaesel.s.CODEBLOCAGE[0] = AeGetApp()->IsPrintCode() ? '1' : '0';
    artaesel.Server(AatartAa_sel_artnr);

    memcpy_s(&article, sizeof(ARTAESEL), &artaesel.s, sizeof(ARTAESEL));
}

bool CDBePosBearbModel::ReadImportArticle(long lArticleNo)
{
    CCHECKIMEXBLOCKEXIST checkimexblockexist;
    checkimexblockexist.SetArticleno(lArticleNo);
    return checkimexblockexist.SelExist() != 0;
}

void CDBePosBearbModel::ReadOpenOrders(long lArticleNo, CStringArray& openOrders)
{
    CARTINFBESTEL artinfbestel;
    artinfbestel.s.ARTIKEL_NR = lArticleNo;
    artinfbestel.s.FETCH_REL = 1;    //normaler Fetch

    for (;;)
    {
        CString best;
        artinfbestel.Server(AatartSel_offene_bstlng);
        if ((artinfbestel.rc == 1) || (artinfbestel.rc < 0))
        {
            break;
        }
        if (artinfbestel.s.BEST_WIRKSAM[0] == '1')
        {
            char str[128];
            best.Format("%s %ld", ppGDateLongToCharTTMMJJ(artinfbestel.s.DATUM_WE_SOLL, str), artinfbestel.s.MENGE_BESTELL);
        }
        else
        {
            best = "XX.XX.XX";
        }
        openOrders.Add(best);
    }
    artinfbestel.s.FETCH_REL = 0;          //Close Cursor
    artinfbestel.Server(AatartSel_offene_bstlng);
}

int CDBePosBearbModel::ReadIbtPossible(long lArticleNo, short sIbtBranchNo, std::vector<AUFALTLAGORT>& ibtData)
{
    //Verbund moeglich

    int nIbtPosition = 0;
    ibtData.clear();

    CAUFALTLAGORT aa;
    aa.s.ARTIKEL_NR = lArticleNo;

    for (;;)
    {
        aa.Server(AasrvGetVerbMoegl);
        if (aa.rc != 0)
        {
            break;
        }
        if (aa.s.FILIALNR == sIbtBranchNo)
        {
            nIbtPosition = ibtData.size();
            ibtData.push_back(aa.s);
        }
    }

    return nIbtPosition;
}

bool CDBePosBearbModel::ReadDispoInfo(long lArticleNo, CString& cInfo)
{
    CDISPOINFO Info;
    Info.SetArtikel_nr(lArticleNo);
    Info.SetBezeichnung("HH");
    if (Info.SelDispoInfo() == 0)
    {
        ppString sRemark;
        Info.GetBemerkung(sRemark);
        ppString sNote;
        Info.GetDispo_hinweis(sNote);
        cInfo.Format("%s\r\n%s", (const char*)sRemark, (const char*)sNote);
        return true;
    }

    cInfo.Empty();
    return false;
}

bool CDBePosBearbModel::IsNachlieferung(const CString& cAArt)
{
    return GetOrderType().IsNachlief(AeGetApp()->VzNr_Kunde(), cAArt);
}

bool CDBePosBearbModel::IsDE()
{
    return AeGetApp()->IsDE() ? true : false;
}

bool CDBePosBearbModel::IsDEGetter()
{
    return AeGetApp()->m_pAeUser->IsDEGetter() ? true : false;
}

char CDBePosBearbModel::GetKndNLTyp()
{
    return AeGetApp()->KndNLTyp();
}

bool CDBePosBearbModel::IsNLevelIBTCst()
{
    return AeGetApp()->IsNLevelIBTCst() ? true : false;
}

CString CDBePosBearbModel::GetBranchName(short branchNo)
{
    CString name;
    AeGetApp()->GetBranchName(branchNo, name);
    return name;
}

CString CDBePosBearbModel::GetTextFromResource(UINT uiStringId)
{
    return CResString::ex().getStrTblText(uiStringId);
}

CString CDBePosBearbModel::GetDDMMYYYYStringFromDateLong(long lDate)
{
    return DDMMYYYYStringFromDateLong(lDate);
}
