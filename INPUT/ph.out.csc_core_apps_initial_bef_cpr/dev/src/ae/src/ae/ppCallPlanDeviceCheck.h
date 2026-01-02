#pragma once

//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCallPlanDeviceCheck.h
   Author: R.von-der-Gruen
   made  : 19.07.2000
                            >No changes in this text may be made<
   declaration:
   Customer-Base-Class
*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppError.h"
#include "ppRegion.h"

class CMDEVICEPLANCHECK;

class ppCallPlanDeviceCheck : public ppDadeScroll<CMDEVICEPLANCHECK>, virtual public ppError
{
public:
    enum t_checktyp
    {
        m_devicecheck = 1,
        m_umkcheck    = 2
    };
    enum t_modem
    {
        m_isfree      = 0,  /* modem is free; ready for calling */
        m_isengaged   = 1,  /* modem is working */
        m_iswarning   = 2,  /* dafü is ready but no response from umk */
        m_iserror     = 3,  /* modem don't work */
        m_isnotactive = 4,  /* modem is deactivated */
        m_isfreecall  = 5,  /* modem is incall and freecallno */
        m_max_entry
    };

public:
    enum t_terminal
    {
        t_free          = 0, /*F*/
        t_calling       = 1, /*B*/
        t_sending       = 2, /*D*/
        t_break_off     = 3, /*A*/
        t_call_is_ended = 4, /*R*/
        t_error         = 5,
        t_max_entry     = 6  /*-*/
    };

    enum t_modemcontrol
    {
        c_outcall    = 0,
        c_incall     = 1,
        c_nightorder = 2,
        c_max
    };

protected:
    enum t_active
    {
        is_callout    = 'P',
        is_callin     = 'O',
        is_nightorder = 'N'
    };

public: //constructor
    ppCallPlanDeviceCheck(const ppString& strPath = "c:\\ppErrorMsg",
                          const short sLanguage = 1);
    ppCallPlanDeviceCheck(const short sSaleCenterNo,
                          const ppString& strPath = "c:\\ppErrorMsg",
                          const short sLanguage = 1);
    ~ppCallPlanDeviceCheck();

public: //clear/check methodes
    void Release();

public: //unique selections
    bool GetUni();
    bool UpdateUMK();
    bool Update();

public: //list selection from data, page-scrolling
    bool StartBrowse();                                   //start to fill list
    bool SetNextPage(const t_checktyp e = m_devicecheck); //start to fill the next page
    bool SetPreviousPage();                               //set to previous page
    bool GetNext(const t_checktyp e = m_devicecheck);     //get data from list
    bool SetElement(const unsigned nPos);                 //get an element from list and set to classmembers

    const t_modem GetModemState(const ppTime& time);     //it announces the current state of the modem.

public: //Data: Set- and Getmethodes
    void SetVertriebsZentrumNr(const short sSaleCenterNo);
    void SetAktiv(const ppBool& b);
    //Get-Methodes
    const short GetFilialNr() const;
    const char* GetGeraeteId();
    const short GetUmkNr() const;
    const long GetGeraetNst() const;
    const t_modemcontrol GetGeraeteVerw1() const;
    const char* GetGeraeteVerw1Text() const;
    const long GetSequenzNr() const;
    const t_terminal GetTerminalStatus();
    const ppTime& GetStartZeit();
    const ppTime& GetEndeZeit();
    const ppTime GetUrrufZeit() const;
    const short GetVertriebsZentrumNr() const;
    const long GetKundenNr() const;
    const ppDate GetDatum() const;
    const char GetAuftragstatus() const;
    const long GetKdauftragnr1() const;
    const short GetPoolnr() const;
    const char* GetTerminalStatusText();
    const ppBool GetAktiv() const;
    const ppBool GetIsAktiv() const;

protected:
    bool IsInitialized();
    void SetRegionenTyp(const ppRegion::t_region eRegion = ppRegion::r_modem);
    void Init();
    const int GetTerminalPos();

protected: //data-members
    CMDEVICEPLANCHECK* m_srvCallPlanDevice;
    CMDEVICEPLANCHECK* m_srvCallPlanDeviceUP;

protected: //data-members
    ppTime   m_Time;
    ppString m_str;
    ppString m_strText[t_max_entry];
    int      m_iTerminal[t_max_entry];
    ppString m_strPlan;

protected: //constant factor
    ppString m_straDevice[c_max];
};
