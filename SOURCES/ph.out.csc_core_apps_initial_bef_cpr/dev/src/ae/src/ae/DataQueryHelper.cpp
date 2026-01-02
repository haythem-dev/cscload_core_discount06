#include "stdafx.h"
#include "DataQueryHelper.h"
#include <customer.h>
#include <orders.h>

DataQueryHelper::DataQueryHelper()
{
}

DataQueryHelper::~DataQueryHelper()
{
}

int DataQueryHelper::getTourIDsForIDF(int idfNo, short branchNo, int weekDay, std::vector<std::pair<CString, bool> >& tourIDList)
{
    int rc = -1;
    int count = 0;
    CORDERPERIOD orderPeriod;

    //select tourids
    orderPeriod.SetBranchno(branchNo);
    orderPeriod.SetCustomerno(idfNo);
    orderPeriod.SetWeekday(static_cast<short>(weekDay));

    //actual date will be set in the dade generated code
    while (rc != SRV_SQLNOTFOUND)
    {
        ++count;
        orderPeriod.SetAnz_erfasst(count);

        if ((rc = orderPeriod.SelTourForIDF()) != SRV_OK)
        {
            //IF the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
            if (rc == SRV_SQLNOTFOUND && orderPeriod.CloseCursor() == SRV_OK)
            {
                orderPeriod.ClearStruct();
            }

            //no more data
            break;
        }

        AllgEntfSpaces(orderPeriod.s.TOURID);
        AllgEntfSpaces(orderPeriod.s.TOURINAKTIV);
        tourIDList.push_back(std::make_pair(orderPeriod.s.TOURID, strcmp(orderPeriod.s.TOURINAKTIV, "1") == 0 ? true : false));
    }
    return rc;
}
