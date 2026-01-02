#pragma once

//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCallPlanDeviceMaintenance.h
   Author: A.Schmidt-Rehschuh
   made  : 21.07.2000
                            >No changes in this text may be made<
   declaration:
   Customer-Base-Class
*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppError.h"
#include "ppRegion.h"

class CMDEVICEPLANMAINTENANCE;

class ppCallPlanDeviceMaintenance : public ppDadeScroll<CMDEVICEPLANMAINTENANCE>, virtual public ppError
{
public:
    enum t_modem
    {
        m_modem = 'M'
    };

    enum t_modemcontrol
    {
        c_outcall    = 0,
        c_incall     = 1,
        c_nightorder = 2,
        c_max
    };

    enum t_modemtyp
    {
        m_direct = 'D',
        m_para   = 'P',
        m_seriel = 'S',
        m_max    = 3
    };

    enum t_active
    {
        is_callout = 'O',
        is_callin  = 'P',
    };

protected:
    enum i_modemcontrol
    {
        ic_outcall    = 'P',
        ic_incall     = 'O',
        ic_nightorder = 'N'
    };

public: //constructor
    ppCallPlanDeviceMaintenance(const ppString& strPath = "c:\\ppErrorMsg",
                          const short sLanguage = 1);
    ppCallPlanDeviceMaintenance(const short sSaleCenterNo,
                          const ppString& strPath = "c:\\ppErrorMsg",
                          const short sLanguage = 1);
    ~ppCallPlanDeviceMaintenance();

public: //check changes
    bool IsChanged();
    void Restore();

public: //unique selection from data
    bool GetUni();
    bool Update();
    bool Insert();
    bool Delete();

public: //list selection from data, page-scrolling
    bool StartBrowse();                                 //start to fill list
    bool SetNextPage();                                 //start to fill the next page
    bool SetPreviousPage();                             //set to previous page
    bool GetNext();                                     //get data from list
    bool SetElement(const unsigned nPos);               //get an element from list and set to classmembers

public: // Const TextStrings
    const char* GetTextDeviceTyp();
    const char* GetTextModemTyp();
    const int FindModemTypPos(const char chModemTyp);
    const t_modemtyp FindModemTyp(const ppString& strModemTyp);

public: //Data: Set- and Getmethodes
    void SetVertriebsZentrumNr(const short sSaleCenterNo);
    void SetFilialNr(const short s);
    void SetGeraeteID(const ppString& s);
    void SetGeraeteArt(const char ch);
    void SetGeraetNst(const long l);
    void SetGeraeteverw1(const t_modemcontrol t);
    void SetModemTyp(const char ch);
    void SetUmkNr(const short s);
    void SetLoginID(const long l);
    void SetAktiv(const ppBool& l);
    void SetUmkNst(const short s);
    //Get-Methodes
    const short GetVertriebsZentrumNr() const;
    const short GetFilialNr() const;
    const char* GetGeraeteId();
    const short GetUmkNr() const;
    const long GetGeraetNst() const;
    const t_modemcontrol GetGeraeteVerw1() const;
    const char* GetGeraeteVerw1Text(const t_modemcontrol t) const;
    const char* GetGeraeteVerw1Text() const;
    const char GetGeraeteArt() const;
    const char GetModemTyp() const;
    const long GetLoginID() const;
    const ppDate GetDate() const;
    const ppTime GetTime() const;
    const ppBool GetAktiv() const;
    const short GetUmkNst() const;

protected:
    void Init();
    bool IsInitialized();
    void SetRegionenTyp(const ppRegion::t_region eRegion = ppRegion::r_modem);

protected: //data-members
    CMDEVICEPLANMAINTENANCE* m_srvCallPlanDevice;
    CMDEVICEPLANMAINTENANCE* m_srvCallPlanDeviceUP;
    short    m_sSaleCenterNo;
    ppString m_str;
    int      m_iPosDevice;
    int      m_iPosDeviceTyp;

protected: //constant factor
    ppString m_straDevice[c_max];
    struct stDevice
    {
        ppString   s_strDeviceTyp;
        t_modemtyp s_eTyp;
        void Add(const ppString& strDeviceTyp, const t_modemtyp eTyp)
        {
            s_strDeviceTyp = strDeviceTyp;
            s_eTyp = eTyp;
        }
        const char* GetDeviceTyp() { return s_strDeviceTyp.c_str(); }
        const t_modemtyp GetModemTyp() { return s_eTyp; }
    } ;

    ppString m_straDeviceTyp[c_max];
    stDevice m_staDevice[m_max];
};
