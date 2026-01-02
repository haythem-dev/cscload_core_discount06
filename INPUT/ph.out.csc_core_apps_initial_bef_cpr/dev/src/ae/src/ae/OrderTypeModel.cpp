#include "StdAfx.h"
#include "OrderTypeModel.h"

void COrderTypeModel::LeseAufArtenListeVZ(short sBranchNo, std::vector<auftragsartS>& lOrderType)
{
    CAUFTRAGSART aart;  //vorhandene Auftragarten einlesen
    aart.SetBranchno(sBranchNo);
    char error_msg[81];

    for (;;)
    {
        int rc = ServerNr(PIPE_AE_SRV, AasrvSelAllCscOrderType, (void*)&aart.s, AUFTRAGSART_BES, AUFTRAGSART_ANZ, error_msg);
        if (rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        lOrderType.push_back(aart.s);
    }
}
