#include "stdafx.h"
#include "AeAppModelMock.h"

CAeAppModelMock::CAeAppModelMock()
{
}

void CAeAppModelMock::LeseKABAKombListeVZ(short sVZ, std::vector<PARKABAKOMB>& lKomb)
{
    if (KaBaKomb.find(sVZ) == KaBaKomb.end())
    {
        KaBaKomb[sVZ] = std::vector<PARKABAKOMB>();
    }
    lKomb = KaBaKomb[sVZ];
}

void CAeAppModelMock::LeseKoArtenListeVZ(short sVZ, std::vector<PARKOART>& lKoart)
{
    if (KoArt.find(sVZ) == KoArt.end())
    {
        KoArt[sVZ] = std::vector<PARKOART>();
    }
    lKoart = KoArt[sVZ];
}

void CAeAppModelMock::LeseBranchNames(std::vector<branchnamesS>& lRechner)
{
    lRechner = Rechner;
}

void CAeAppModelMock::LeseRemarkTypes(std::vector<remarktypesS>& lRemarktypes)
{
    lRemarktypes = Remarktypes;
}

void CAeAppModelMock::LeseBuArtenListeVZ(short sVZ, std::vector<PARBUCHART>& lBuart)
{
    if (BuArt.find(sVZ) == BuArt.end())
    {
        BuArt[sVZ] = std::vector<PARBUCHART>();
    }
    lBuart = BuArt[sVZ];
}

void CAeAppModelMock::LeseTaxRates(std::vector<taxesS>& lTaxes)
{
    lTaxes = Taxes;
}

void CAeAppModelMock::LeseFiliale(short sBranchNo, std::vector<Filiale>& lFilialen)
{
    if (Filialen.find(sBranchNo) == Filialen.end())
    {
        Filialen[sBranchNo] = std::vector<Filiale>();
    }
    lFilialen = Filialen[sBranchNo];
}
