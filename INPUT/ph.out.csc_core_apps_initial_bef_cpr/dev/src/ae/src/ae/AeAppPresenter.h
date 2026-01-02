#pragma once

#include "IAeAppModel.h"
#include <boost/shared_ptr.hpp>

class CAeAppPresenter
{
private:
    boost::shared_ptr<IAeAppModel> _pModel;
    std::vector<PARKABAKOMB> _lKomb;
    std::vector<PARKOART> _lKoart;
    std::vector<branchnamesS> _lRechner;
    std::vector<remarktypesS> _lRemarktypes;
    bool _bRemarktypesRead;
    std::vector<PARBUCHART> _lBuart;
    std::vector<taxesS> _lTaxes;
    std::vector<Filiale> _lFilialen;
    bool _bFilialenRead;

public:
    CAeAppPresenter(boost::shared_ptr<IAeAppModel> pModel);

    bool IsKABAKomb(short sVZ, CString cAufArt, CString cKA, CString cBA);

    int GetKoArtenListeVZ(short sVZ, int index, CString& KoArt);
    void LeseBranchNames();
    void GetBranchName(short sVZ, CString& strBranchName);
    void GetRemarkTypes(short sRemarktype, CString& strRemarkName);
    int GetBuArtenListeVZ(short sVZ, int index, CString& strBuArt);
    int GetTaxRates(int index, char& cStd, double& TaxRate);

    const std::vector<Filiale>& GetBranchesOfRegion(short sBranchNo);
};
