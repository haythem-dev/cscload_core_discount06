#include "StdAfx.h"
#include "AeAppModel.h"

void CAeAppModel::LeseKABAKombListeVZ(short sVZ, std::vector<PARKABAKOMB>& lKomb)
{
    CPARKABAKOMB parkabakomb; //vorhandene Auftragarten einlesen
    parkabakomb.s.VERTRIEBSZENTRUMNR = sVZ;
    for (;;)
    {
        parkabakomb.s.FETCH_REL = 1;                  //normaler Fetch
        parkabakomb.Server(AafilSelkabakomb);
        if (parkabakomb.rc == SRV_SQLNOTFOUND)
        {
            parkabakomb.s.FETCH_REL = 0;              //close Cursor
            parkabakomb.Server(AafilSelkabakomb);
            break;
        }
        lKomb.push_back(parkabakomb.s);
    }
}

void CAeAppModel::LeseKoArtenListeVZ(short sVZ, std::vector<PARKOART>& lKoart)
{
    CPARKOART parkoart;    //vorhandene Kommiarten einlesen
    parkoart.s.BRANCHNO = sVZ;
    for (;;)
    {
        parkoart.s.FETCH_REL = 1;                  //normaler Fetch
        parkoart.Server(AafilSelkoart);
        if (parkoart.rc == SRV_SQLNOTFOUND)
        {
            parkoart.s.FETCH_REL = 0;              //close Cursor
            parkoart.Server(AafilSelkoart);
            break;
        }
        lKoart.push_back(parkoart.s);
    }
}

void CAeAppModel::LeseBranchNames(std::vector<branchnamesS>& lRechner)
{
    CBRANCHNAMES branchnames; //vorhandene Einträge aus Rechner einlesen
    for (;;)
    {
        if (branchnames.SelList() != SRV_OK)
            break;
        lRechner.push_back(branchnames.s);
    }
}

void CAeAppModel::LeseRemarkTypes(std::vector<remarktypesS>& lRemarktypes)
{
    CREMARKTYPES remarktypes; //vorhandene Einträge aus Rechner einlesen
    for (;;)
    {
        if (remarktypes.SelList() != SRV_OK)
            break;
        lRemarktypes.push_back(remarktypes.s);
    }
}

void CAeAppModel::LeseBuArtenListeVZ(short sVZ, std::vector<PARBUCHART>& lBuart)
{
    CPARBUCHART parbuchart;  //vorhandene Kommiarten einlesen
    parbuchart.s.BRANCHNO = sVZ;
    for (;;)
    {
        parbuchart.s.FETCH_REL = 1;                  //normaler Fetch
        parbuchart.Server(AafilSelbuchart);
        if (parbuchart.rc == SRV_SQLNOTFOUND)
        {
            parbuchart.s.FETCH_REL = 0;              //close Cursor
            parbuchart.Server(AafilSelbuchart);
            break;
        }
        lBuart.push_back(parbuchart.s);
    }
}

void CAeAppModel::LeseTaxRates(std::vector<taxesS>& lTaxes)
{
    CTAXES taxes;   //vorhandene TaxRates einlesen
    for (;;)
    {
        if (taxes.SelList() != SRV_OK)
        {
            taxes.CloseCursor();        //close Cursor
            break;
        }
        lTaxes.push_back(taxes.s);
    }
}

void CAeAppModel::LeseFiliale(short sBranchNo, std::vector<Filiale>& lFilialen)
{
    lFilialen.clear();

    ppRegion region;
    region.SetRegionNr(sBranchNo);
    region.SetRegionenTyp(ppRegion::r_salecenter);
    region.SetCountPerPage(100);
    region.StartBrowse();
    region.SetNextPage();

    while (region.GetNext())
    {
        Filiale filiale;
        filiale.Name = region.GetName();
        filiale.RegionTeilNr = region.GetRegionTeilNr();
        lFilialen.push_back(filiale);
    }
}
