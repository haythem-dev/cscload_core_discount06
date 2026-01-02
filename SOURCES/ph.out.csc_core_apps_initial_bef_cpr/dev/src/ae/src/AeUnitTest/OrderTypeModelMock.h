#pragma once

#include <IOrderTypeModel.h>
#include <map>

class COrderTypeModelMock : public IOrderTypeModel
{

public:
    std::map<short, std::vector<auftragsartS> > OrderTypes;

    COrderTypeModelMock();

    virtual void LeseAufArtenListeVZ(short sBranchNo, std::vector<auftragsartS>& lOrderType);
};
