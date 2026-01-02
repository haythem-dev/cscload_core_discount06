#include "StdAfx.h"
#include "AeAppPresenter.h"

CAeAppPresenter::CAeAppPresenter(boost::shared_ptr<IAeAppModel> pModel) : _pModel(pModel)
{
    _bRemarktypesRead = false;
    _bFilialenRead = false;
}

bool CAeAppPresenter::IsKABAKomb(short sVZ, CString cAufArt, CString cKA, CString cBA)
{
    int vzfound = 0;
    for (int x = 0; x < 2; ++x) // Two rounds if values are reloaded
    {
        for (size_t i = 0; i < _lKomb.size(); i++)
        {
            if (_lKomb.at(i).VERTRIEBSZENTRUMNR != sVZ)
                continue;
            vzfound = 1;
            if (cAufArt == _lKomb.at(i).KDAUFTRAGART)
            {
                if (cKA != _lKomb.at(i).KOART)
                    continue;
                if (cBA != _lKomb.at(i).BUCHART)
                    continue;
                return true;
            }
        }
        if (vzfound > 0)
            break;
        _pModel->LeseKABAKombListeVZ(sVZ, _lKomb);
    }
    return false;
}

int CAeAppPresenter::GetKoArtenListeVZ(short sVZ, int index, CString& KoArt)
{
    if (_lKoart.empty())
        _pModel->LeseKoArtenListeVZ(sVZ, _lKoart);
    int count = 0;
    for (int x = 0; x < 2; ++x) // Two rounds if values are reloaded
    {
        for (size_t i = 0; i < _lKoart.size(); i++)
        {
            PARKOART s = _lKoart.at(i);
            if (s.BRANCHNO != sVZ)
                continue;
            if (count == index)
            {
                KoArt.Format("%*.*s - %*.*s",
                    L_PARKOART_KOART, L_PARKOART_KOART, s.KOART,
                    L_PARKOART_BEZEICHNUNG, L_PARKOART_BEZEICHNUNG, s.BEZEICHNUNG);
                return 0;
            }
            ++count;
        }
        if (count > 0)
            return -1;
        _pModel->LeseKoArtenListeVZ(sVZ, _lKoart);
    }
    return -1;
}

void CAeAppPresenter::LeseBranchNames()
{
    _pModel->LeseBranchNames(_lRechner);
}

void CAeAppPresenter::GetBranchName(short sVZ, CString& strBranchName)
{
    if (_lRechner.empty())
    {
        LeseBranchNames();
    }

    for (size_t i = 0; i < _lRechner.size(); i++)
    {
        branchnamesS s = _lRechner.at(i);
        if (s.FILIALNR != sVZ)
            continue;
        strBranchName = s.STANDORT;
        return;
    }
    strBranchName.Empty();
}

void CAeAppPresenter::GetRemarkTypes(short sRemarktype, CString& strRemarkName)
{
    if (!_bRemarktypesRead)
    {
        _bRemarktypesRead = true;
        _pModel->LeseRemarkTypes(_lRemarktypes);
    }
    remarktypesS remarktypes;
    for (size_t i = 0; i < _lRemarktypes.size(); i++)
    {
        remarktypes = _lRemarktypes.at(i);
        if (remarktypes.REMARKTYPE != sRemarktype)
            continue;
        strRemarkName = remarktypes.REMARKNAME;
        return;
    }
    strRemarkName.Empty();
}

int CAeAppPresenter::GetBuArtenListeVZ(short sVZ, int index, CString& strBuArt)
{
    if (_lBuart.empty())
        _pModel->LeseBuArtenListeVZ(sVZ, _lBuart);
    int count = 0;
    for (int x = 0; x < 2; ++x) // Two rounds if values are reloaded
    {
        for (size_t i = 0;i < _lBuart.size(); i++)
        {
            PARBUCHART s = _lBuart.at(i);
            if (s.BRANCHNO != sVZ)
                continue;
            if (count == index)
            {
                strBuArt.Format("%*.*s - %*.*s",
                    L_PARBUCHART_BUCHART, L_PARBUCHART_BUCHART, s.BUCHART,
                    L_PARBUCHART_BEZEICHNUNG, L_PARBUCHART_BEZEICHNUNG, s.BEZEICHNUNG);
                return 0;
            }
            ++count;
        }
        if (count > 0)
            return -1;
        _pModel->LeseBuArtenListeVZ(sVZ, _lBuart);
    }
    return -1;
}

int CAeAppPresenter::GetTaxRates(int index, char& cStd, double& TaxRate)
{
    if (_lTaxes.empty())
        _pModel->LeseTaxRates(_lTaxes);
    int count = 0;
    for (int x = 0; x < 2; ++x) // Two rounds if values are reloaded
    {
        for (size_t i = 0; i < _lTaxes.size(); i++)
        {
            N_TAXES s = _lTaxes.at(i);
            if (count == index)
            {
                TaxRate = s.SALESTAXRATE;
                cStd = s.DEFAULTTAX[0];
                return 0;
            }
            ++count;
        }
        if (count > 0)
            return -1;
        _pModel->LeseTaxRates(_lTaxes);
    }
    return -1;
}

const std::vector<Filiale>& CAeAppPresenter::GetBranchesOfRegion(short sBranchNo)
{
    if (!_bFilialenRead)
    {
        _pModel->LeseFiliale(sBranchNo, _lFilialen);
        _bFilialenRead = true;
    }
    return _lFilialen;
}
