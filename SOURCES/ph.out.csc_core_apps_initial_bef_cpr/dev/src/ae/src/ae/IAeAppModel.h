#pragma once

#include <vector>
#include <param.h>
#include <filialpartner.h>
#include <orders.h>
#include <controlling.h>

struct Filiale
{
    CString Name;
    short RegionTeilNr;
};

class IAeAppModel
{
public:
    virtual void LeseKABAKombListeVZ(short sVZ, std::vector<PARKABAKOMB>& lKomb) = 0;
    virtual void LeseKoArtenListeVZ(short sVZ, std::vector<PARKOART>& lKoart) = 0;
    virtual void LeseBranchNames(std::vector<branchnamesS>& lRechner) = 0;
    virtual void LeseRemarkTypes(std::vector<remarktypesS>& lRemarktypes) = 0;
    virtual void LeseBuArtenListeVZ(short sVZ, std::vector<PARBUCHART>& lBuart) = 0;
    virtual void LeseTaxRates(std::vector<taxesS>& lTaxes) = 0;
    virtual void LeseFiliale(short sBranchNo, std::vector<Filiale>& lFilialen) = 0;
};
