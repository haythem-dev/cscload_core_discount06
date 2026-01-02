#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCallPlanUndertake.h
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000
                            >No changes in this text may be made<
   declaration:
*/

#include "ppdatatypes.h"
#include "pperror.h"

class CMCALLPLANUNDERTAKE;

class ppCallPlanUndertake : virtual public ppError
{
public: //constructor
    ppCallPlanUndertake(const ppString& strPath = "c:",
                        const short sLanguage = 1);
    ppCallPlanUndertake(const short sSaleCenterNo,
                        const ppString& strPath  = "c:",
                        const short sLanguage = 1);
    ~ppCallPlanUndertake();

public: //unique selection from data
    bool CheckEntries(const bool bIsSera = true);
    bool DeleteEntries();
    bool DeleteEvents();
    bool Undertake();
    bool UndertakePhon();
    bool DeleteEntriesPhon();
    bool DeleteEventsPhon();

public: //Data: Set- and Getmethodes
    void SetVertriebsZentrumNr(const short vertriebsZentrumNr);
    void SetLadeDatum(const ppDate& ladeDatum);
    // GetMethodes
    const short GetVertriebsZentrumNr() const;
    const ppDate GetLadeDatum() const;
    const long GetCount() const;

protected: //data-members
    CMCALLPLANUNDERTAKE* m_srvPlan;
    CMCALLPLANUNDERTAKE* m_srvPlanUP;
    long m_lEntries;

protected: //methodes
    bool IsInitialized();
};
