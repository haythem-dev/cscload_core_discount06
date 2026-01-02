#pragma once

#include <vector>
#include <auftragsart.h>

class IOrderTypeModel
{
public:
    virtual void LeseAufArtenListeVZ(short sBranchNo, std::vector<auftragsartS>& lOrderType) = 0;
};
