#include "StdAfx.h"
#include "OrderType.h"
#include "IOrderTypeModel.h"


COrderType::COrderType(boost::shared_ptr<IOrderTypeModel> pOrderTypeModel)
    : _pOrderTypeModel(pOrderTypeModel)
{
}

int COrderType::GetAufArtenListeVZ(short sBranchNo, int index, CString& strOrderType)
{
    bool bFresh;
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo, bFresh);
    if (pOrderType == NULL)
    {
        return -1;
    }

    for (int i = 0; i < 2; ++i) // Two rounds if order types are reloaded
    {
        auftragsartS auftragsart;
        int count = 0;

        for (size_t i = 0; i < pOrderType->size(); i++)
        {
            auftragsart = pOrderType->at(i);
            if (auftragsart.SBILDSCHIRM[0] == '0')
            {
                continue;
            }
            if (count == index)
            {
                strOrderType.Format("%*.*s - %*.*s",
                    L_AUFTRAGSART_KDAUFTRAGART,
                    L_AUFTRAGSART_KDAUFTRAGART,
                    auftragsart.KDAUFTRAGART,
                    L_AUFTRAGSART_BEZEICHNUNG,
                    L_AUFTRAGSART_BEZEICHNUNG,
                    auftragsart.BEZEICHNUNG);
                return auftragsart.SSTANDARD[0] == '1' ? 1 : 0;
            }
            ++count;
        }
        if (count > 0)
        {
            return -1; // order types for "Bildschirm" output exist, but no index match
        }

        // Maybe order type list was outdated !?
        // Reload order types and try again
        if (bFresh) // order type list were freshly loaded, so no reload necessary
        {
            return -1;
        }

        bFresh = true;
        LoadOrderTypesToMap(sBranchNo);
        pOrderType = GetOrderTypeFromMap(sBranchNo);
        if (pOrderType == NULL)
        {
            return -1;
        }
    }
    return -1; // should never be reached because of bFresh
}

int COrderType::LoadOrderTypesToMap(short sBranchNo)
{
    std::vector<auftragsartS> lOrderType;
    _pOrderTypeModel->LeseAufArtenListeVZ(sBranchNo, lOrderType);
    if (lOrderType.size() > 0)
    {
        _mapOrderType[sBranchNo] = lOrderType;
    }
    return lOrderType.size();
}

std::vector<auftragsartS>* COrderType::GetOrderTypeFromMap(short sBranchNo, bool& bWasLoadedFromServer, bool bLoadFromServer /*=true*/)
{
    std::map<short, std::vector<auftragsartS> >::iterator iterOrderType = _mapOrderType.find(sBranchNo);
    if (iterOrderType == _mapOrderType.end())
    {
        if (!bLoadFromServer)
        {
            bWasLoadedFromServer = false;
            return NULL;
        }
        bWasLoadedFromServer = true;
        LoadOrderTypesToMap(sBranchNo);
        bool bDummy; // bWasLoadedFromServer must not be overriden, so use a dummy !
        return GetOrderTypeFromMap(sBranchNo, bDummy, false);
    }
    bWasLoadedFromServer = false;
    return &iterOrderType->second;
}

std::vector<auftragsartS>* COrderType::GetOrderTypeFromMap(short sBranchNo)
{
    bool bDummy;
    return GetOrderTypeFromMap(sBranchNo, bDummy);
}

bool COrderType::IsOnlyEH(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).SONLYEH[0] == '1') ? true : false;
        }
    }

    return false;
}

bool COrderType::IsNatraAufArt(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).DISINKINDENTERABLE[0] == '1') ? true : false;
        }
    }

    return false;
}

bool COrderType::IsAufArtDefaultKennung(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).SDEFAULTKENNUNG == 1) ? true : false;
        }
    }

    return false;
}

bool COrderType::IsAufArtNoPromo(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).SNOPROMOTIONS == 1) ? true : false;
        }
    }

    return false;
}

bool COrderType::IsGlobalAufArt(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).SGLOBAL[0] == '1') ? true : false;
        }
    }

    return false;
}

bool COrderType::IsAufArtIVCNo(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).SIVCVOUCHERNO == 1) ? true : false;
        }
    }

    return false;
}

bool COrderType::IsAufArtOriginalInvoiceNo(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).SORIGINALINVOICENO == 1) ? true : false;
        }
    }

    return false;
}

bool COrderType::IsAufArtMustHeadline(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).SMUSTHEADLINE == 1) ? true : false;
        }
    }

    return false;
}

bool COrderType::IsMustSubOrder(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).SMUSTSUBORDER[0] == '1') ? true : false;
        }
    }

    return false;
}

bool COrderType::IsNoVideoAufArt(short sBranchNo, CString cAufArt)
{
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return true;
    }

    for (size_t i = 0; i < pOrderType->size(); i++)
    {
        if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
        {
            return (pOrderType->at(i).SBILDSCHIRM[0] == '1') ? false : true;
        }
    }

    return true;
}

bool COrderType::IsFreePrice(short sBranchNo, CString cAufArt)
{
    bool bFresh;
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo, bFresh);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (int i = 0; i < 2; ++i) // Two rounds if order types are reloaded
    {
        for (size_t i = 0; i < pOrderType->size(); i++)
        {
            if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
            {
                return (pOrderType->at(i).SFREEPRICE[0] == '1') ? true : false;
            }
        }

        if (!TryReloadOrderTypes(sBranchNo, pOrderType, bFresh))
        {
            return false;
        }
    }

    return false;
}

bool COrderType::IsNachlief(short sBranchNo, CString cAufArt)
{
    bool bFresh;
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo, bFresh);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (int i = 0; i < 2; ++i) // Two rounds if order types are reloaded
    {
        for (size_t i = 0; i < pOrderType->size(); i++)
        {
            if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
            {
                return (pOrderType->at(i).SRESTDEL[0] == '1') ? true : false;
            }
        }

        if (!TryReloadOrderTypes(sBranchNo, pOrderType, bFresh))
        {
            return false;
        }
    }

    return false;
}

bool COrderType::IsQuota(short sBranchNo, CString cAufArt)
{
    bool bFresh;
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo, bFresh);
    if (pOrderType == NULL)
    {
        return true;
    }

    for (int i = 0; i < 2; ++i) // Two rounds if order types are reloaded
    {
        for (size_t i = 0; i < pOrderType->size(); i++)
        {
            if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
            {
                return (pOrderType->at(i).SNOQUOTA[0] == '1') ? false : true;
            }
        }

        if (!TryReloadOrderTypes(sBranchNo, pOrderType, bFresh))
        {
            return true;
        }
    }

    return true;
}

bool COrderType::IsNoDD(short sBranchNo, CString cAufArt)
{
    bool bFresh;
    std::vector<auftragsartS>* pOrderType = GetOrderTypeFromMap(sBranchNo, bFresh);
    if (pOrderType == NULL)
    {
        return false;
    }

    for (int i = 0; i < 2; ++i) // Two rounds if order types are reloaded
    {
        for (size_t i = 0; i < pOrderType->size(); i++)
        {
            if (cAufArt == pOrderType->at(i).KDAUFTRAGART)
            {
                return (pOrderType->at(i).SNODD[0] == '1') ? true : false;
            }
        }

        if (!TryReloadOrderTypes(sBranchNo, pOrderType, bFresh))
        {
            return false;
        }
    }

    return false;
}

bool COrderType::TryReloadOrderTypes(short sBranchNo, std::vector<auftragsartS>* pOrderType, bool& bFresh)
{
    // Maybe order type list was outdated !?
    // Reload order types and try again
    if (bFresh) // order type list were freshly loaded, so no reload necessary
    {
        return false;
    }

    bFresh = true;
    LoadOrderTypesToMap(sBranchNo);
    pOrderType = GetOrderTypeFromMap(sBranchNo);
    if (pOrderType == NULL)
    {
        return false;
    }

    return true;
}
