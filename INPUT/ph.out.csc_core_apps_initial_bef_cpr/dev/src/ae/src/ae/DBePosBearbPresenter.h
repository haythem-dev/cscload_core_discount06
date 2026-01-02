#pragma once

struct CDBePosBearbData;
class CDBePosBearbModelIF;

class CDBePosBearbPresenter
{
private:
    CDBePosBearbData& m_Data;
    CDBePosBearbModelIF& m_Model;

public:
    CDBePosBearbPresenter(CDBePosBearbData& rBePosBearbData, CDBePosBearbModelIF& rBePosBearbModel);

    void InitDialog();

    void InitVerbund();
    void DeaktVerbund();
    void SetVerbund(bool bVerbund);
};
