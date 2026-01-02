#pragma once

#include <IAeAppModel.h>
#include <map>

class CAeAppModelMock : public IAeAppModel
{

public:
    CAeAppModelMock();

    std::map<short, std::vector<PARKABAKOMB> > KaBaKomb;
    std::map<short, std::vector<PARKOART> > KoArt;
    std::map<short, std::vector<PARBUCHART> > BuArt;
    std::map<short, std::vector<Filiale> > Filialen;

    std::vector<branchnamesS> Rechner;
    std::vector<remarktypesS> Remarktypes;
    std::vector<taxesS> Taxes;

    // Inherited via IAeAppModel
    virtual void LeseKABAKombListeVZ(short sVZ, std::vector<PARKABAKOMB>& lKomb);
    virtual void LeseKoArtenListeVZ(short sVZ, std::vector<PARKOART>& lKoart);
    virtual void LeseBranchNames(std::vector<branchnamesS>& lRechner);
    virtual void LeseRemarkTypes(std::vector<remarktypesS>& lRemarktypes);
    virtual void LeseBuArtenListeVZ(short sVZ, std::vector<PARBUCHART>& lBuart);
    virtual void LeseTaxRates(std::vector<taxesS>& lTaxes);
    virtual void LeseFiliale(short sBranchNo, std::vector<Filiale>& lFilialen);
};
