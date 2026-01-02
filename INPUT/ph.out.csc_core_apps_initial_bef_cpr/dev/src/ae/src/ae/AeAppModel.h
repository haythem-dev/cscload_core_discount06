#pragma once

#include "IAeAppModel.h"
#include "ppRegion.h"

class CAeAppModel : public IAeAppModel
{
private:
    ppRegion _filialen;                 //Liste der in der Region vorhandenen Filialen

public:
    virtual void LeseKABAKombListeVZ(short sVZ, std::vector<PARKABAKOMB>& lKomb);
    virtual void LeseKoArtenListeVZ(short sVZ, std::vector<PARKOART>& lKoart);
    virtual void LeseBranchNames(std::vector<branchnamesS>& lRechner);
    virtual void LeseRemarkTypes(std::vector<remarktypesS>& lRemarktypes);
    virtual void LeseBuArtenListeVZ(short sVZ, std::vector<PARBUCHART>& lBuart);
    virtual void LeseTaxRates(std::vector<taxesS>& lTaxes);
    virtual void LeseFiliale(short sBranchNo, std::vector<Filiale>& lFilialen);
};
