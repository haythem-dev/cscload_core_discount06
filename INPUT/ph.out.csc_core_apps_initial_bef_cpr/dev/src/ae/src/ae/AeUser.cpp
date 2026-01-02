// AeUser.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

extern "C"
{
#include "allg.h"
}

CAeUser::CAeUser()
{
    m_bInit = FALSE;
}

BOOL CAeUser::InitUser(CString userName, BOOL bMsg)
{
    CAEPWD pwd;
    pwd.s.FILIALNR = AeGetApp()->VzNr();
    AllgStrCopy(pwd.s.USERNAME, userName, L_AEPWD_USERNAME);
    pwd.Server(AafilReadpasswd);
    if (pwd.rc != SRV_OK)
    {
        if (bMsg) MsgBoxOK(IDP_UNGUELT_USER);
        SetInit(FALSE);
        return FALSE;
    }
    AllgEntfSpaces(pwd.s.PASSWORD);
    AllgEntfSpaces(pwd.s.USERNAME);
    AllgEntfSpaces(pwd.s.TERMID);
    AllgEntfSpaces(pwd.s.AGENTID);
    SetUser(pwd.s);
    SetInit();
    return TRUE;
}

void CAeUser::SetPasswd(CString passwd)
{
    if (!IsInit()) return;
    AllgStrCopy(m_aepwd.s.PASSWORD, passwd, L_AEPWD_PASSWORD);
    m_aepwd.Server(AafilUpdpasswd);
}

void CAeUser::UpdateUserDB()                            //Aendert Zugriffsrechte auf DB
{
    if (!IsInit()) return;

    m_aepwd.s.DAT_LOESCH = 0;
    m_aepwd.Server(AafilUpdpasswd);
}

BOOL CAeUser::NewUserDB(CString Name, CString Password) //legt neuen User auf DB an (Def. UID und TERMID)
{
    m_aepwd.buf_default();
    AllgStrCopy(m_aepwd.s.USERNAME, Name, L_AEPWD_USERNAME);
    AllgStrCopy(m_aepwd.s.PASSWORD, Password, L_AEPWD_PASSWORD);
    m_aepwd.s.FILIALNR = AeGetApp()->VzNr();
    m_aepwd.s.UID_ANLAGE = GetAeUser().GetUID();
    m_aepwd.Server(AafilInspasswd);
    if (m_aepwd.rc < SRV_OK)
        return FALSE;
    SetInit();
    return TRUE;
}

void CAeUser::DeleteUserDB()                            //Kennzeichnet einen User als inaktiv
{
    if (!IsInit()) return;
    CTM tm;
    strcpy(m_aepwd.s.PASSWORD, "xxxxxxxx");
    tm.Server(AafilGetdatetime);
    m_aepwd.s.DAT_LOESCH = tm.s.DATUM;
    m_aepwd.Server(AafilUpdpasswd);
}

void CAeUser::SetBit(char& aa, BOOL b)
{
    aa = b ? '1' : '0';
}

BOOL CAeUser::IsBitSet(const char& aa) const
{
    return aa == '1' ? TRUE : FALSE;
}