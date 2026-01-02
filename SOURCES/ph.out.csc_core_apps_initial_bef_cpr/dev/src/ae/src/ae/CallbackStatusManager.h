#pragma once

#include "stdafx.h"
#include <callback.h>
#include <vector>
#include <string>
using namespace std;

#define CALLBACKSTATUS_TAG_OPEN 1
#define CALLBACKSTATUS_TAG_CLOSE 2

class CallbackStatus
{
public:
    short STATUSID;
    ppString  STATUSNAME;
    short STATUSTAG;

    CallbackStatus() {}
    CallbackStatus(short statusID, ppString statusName, short statusTag)
        :STATUSID(statusID), STATUSNAME(statusName), STATUSTAG(statusTag)
    {
    }

    ~CallbackStatus() {}
};

class CCallbackStatusManager
{
public:
    CCallbackStatusManager();
    virtual ~CCallbackStatusManager() {}

    void FillCombobox(CComboBox& combobox);
    short GetOpenStatusID();
    bool IsCloseStatus(short statusID);
    short GetStatusID(ppString statusName);
    ppString GetStatusName(short statusID);

    static bool GetIsCBStatusUsed();

protected:
    vector<CallbackStatus> m_vecCallbackStatus;
};