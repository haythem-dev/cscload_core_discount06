#include "stdafx.h"
#include "OrderTypeModelMock.h"

COrderTypeModelMock::COrderTypeModelMock()
{
}

void COrderTypeModelMock::LeseAufArtenListeVZ(short sBranchNo, std::vector<auftragsartS>& lOrderType)
{
    if (OrderTypes.find(sBranchNo) == OrderTypes.end())
    {
        OrderTypes[sBranchNo] = std::vector<auftragsartS>();
    }
    lOrderType = OrderTypes[sBranchNo];
}
