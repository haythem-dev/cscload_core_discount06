#pragma once

#include "IOrderTypeModel.h"

class COrderTypeModel : public IOrderTypeModel
{
public:
    virtual void LeseAufArtenListeVZ(short sBranchNo, std::vector<auftragsartS>& lOrderType);
};
