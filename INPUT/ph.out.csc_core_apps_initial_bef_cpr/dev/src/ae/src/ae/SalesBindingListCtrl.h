#pragma once

class CSalesBindingListCtrl : public CListCtrl
{
public:
    CSalesBindingListCtrl();

    bool SetActive(long lEtartklasse1, bool bPsycho);

private:
    void GetBindingsByCountry(UINT uiBindings[8]);
    void WriteBindingLines(const UINT uiBindings[8], const long lEtartklasse1, const bool bPsycho);
    void WriteLine(CString binding, bool bYesNo);
};
