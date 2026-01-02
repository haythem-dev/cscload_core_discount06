#pragma once
#include <vector>
#include <iostream>
#include <string>

class DataQueryHelper
{
public:
    DataQueryHelper();
    ~DataQueryHelper();

    static int getTourIDsForIDF(int idfNo, short branchNo, int weekDay, std::vector<std::pair<CString, bool> >& tourIDList);
};
