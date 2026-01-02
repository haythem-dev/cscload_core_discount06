#pragma once

#include <map>
#include <vector>
#include <auftragsart.h>
#include <boost/shared_ptr.hpp>
#include "IOrderTypeModel.h"

class COrderType
{
private:
    boost::shared_ptr<IOrderTypeModel> _pOrderTypeModel;
    std::map<short, std::vector<auftragsartS> > _mapOrderType;

public:
    COrderType(boost::shared_ptr<IOrderTypeModel> pOrderTypeModel);

    //liefert einen Eintrag der Auftragsarten-Liste
    //aus der entsprechenden Filiale
    //z.B.: "NO Normal"
    //Rückgabewerte: -1 Ende
    //                0 normale Auftragsart
    //                1 Standard-Auftragsart
    int GetAufArtenListeVZ(short sBranchNo, int index, CString& strOrderType);

    bool IsOnlyEH(short sBranchNo, CString cAufArt);        //Nur Einzelhandel bei Auftragsart erlaubt ?
    bool IsNatraAufArt(short sBranchNo, CString cAufArt);   //Natra-Eingabe bei Auftragsart erlaubt ?
    bool IsNoVideoAufArt(short sBranchNo, CString cAufArt); //Dialogauftragsart ?
    bool IsFreePrice(short sBranchNo, CString cAufArt);     //Auftragsart mit freier Preiseingabe ?
    bool IsGlobalAufArt(short sBranchNo, CString cAufArt);  //globale Auftragsart ?
    bool IsMustSubOrder(short sBranchNo, CString cAufArt);  //Auftragsart mit Subordertype?
    bool IsNachlief(short sBranchNo, CString cAufArt);      //Nachlieferungen fuer Auftragsart erlaubt?
    bool IsQuota(short sBranchNo, CString cAufArt);       //Kein Kontingente fuer Auftragsart erlaubt?
    bool IsNoDD(short sBranchNo, CString cAufArt);          //Kein verzoegerte Auslieferung fuer Auftragsart erlaubt?
    bool IsAufArtNoPromo(short sBranchNo, CString cAufArt); //Keine Standardrabatte bei Auftragsart erlaubt ?
    bool IsAufArtDefaultKennung(short sBranchNo, CString cAufArt);  //Auftragsart mit Standartkennung eroeffnen ?
    bool IsAufArtIVCNo(short sBranchNo, CString cAufArt);   //Auftragsart mit Eingabe IVC Beleg Nummer ?
    bool IsAufArtOriginalInvoiceNo(short sBranchNo, CString cAufArt);  //Auftragsart mit Eingabe orginal Rechnungs-Nummer ?
    bool IsAufArtMustHeadline(short sBranchNo, CString cAufArt);    //Auftragsart mit Eingabepflicht Kopfzeile ?

private:
    int LoadOrderTypesToMap(short sBranchNo);
    std::vector<auftragsartS>* GetOrderTypeFromMap(short sBranchNo, bool& bWasLoadedFromServer, bool bLoadFromServer = true);
    std::vector<auftragsartS>* GetOrderTypeFromMap(short sBranchNo);
    bool TryReloadOrderTypes(short sBranchNo, std::vector<auftragsartS>* pOrderType, bool& bFresh);
};
