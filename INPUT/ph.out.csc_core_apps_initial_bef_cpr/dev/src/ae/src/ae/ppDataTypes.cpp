//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDataTypes.cpp
   Author: A.Schmidt-Rehschuh
   made  : 07.02.2000

   declaration:
   own data types for the general use
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "ppdatatypes.h"
#include <assert.h>
#include <time.h>
#include <ppgenercpp.h>

//----------------------------------------------------------------------------//
//--- ppBool (boolean Variable with char-Typecast ----------------------------//
//----------------------------------------------------------------------------//

//--- (ppBool)standard constructor -------------------------------------------//

ppBool::ppBool(const short sLanguage /* =1 */) : c_chTRUE('1'), c_chFALSE('0')
{
    Init(sLanguage);
    m_bValue = false;
    m_chValue = c_chFALSE;
}

//--- (ppBool)constructor for boolean Value ----------------------------------//

ppBool::ppBool(const bool b, const short sLanguage /* =1 */) : c_chTRUE('1'), c_chFALSE('0')
{
    Init(sLanguage);
    m_bValue = b;
    Bool2Char(b);
}

//--- (ppBool)constructor for char Value -------------------------------------//

ppBool::ppBool(const char ch, const short sLanguage /* =1 */) : c_chTRUE('1'), c_chFALSE('0')
{
    Init(sLanguage);
    m_chValue = ch == c_chTRUE ? c_chTRUE : c_chFALSE;
    Char2Bool(m_chValue);
}

//--- (ppBool)constructor for char Value -------------------------------------//

ppBool::ppBool(const int i, const short sLanguage /* =1 */) : c_chTRUE('1'), c_chFALSE('0')
{
    Init(sLanguage);
    m_chValue = i == 1 ? c_chTRUE : c_chFALSE;
    Int2Bool(i);
}

//--- (ppBool)Typecast operator (bool) ---------------------------------------//

ppBool::operator bool() const
{
    return m_bValue;
}

//--- (ppBool)Typecast operator (char) ---------------------------------------//

ppBool::operator BTCHAR() const
{
    return m_chValue;
}

//--- (ppBool)Typecast operator (char) ---------------------------------------//

ppBool::operator int() const
{
    return m_bValue ? 1 : 0;
}

//--- (ppBool)Assignment operator (char) -------------------------------------//

const bool ppBool::operator=(const bool b)
{
    m_bValue = b;
    Bool2Char(b);
    return m_bValue;
}

//--- (ppBool)Assignment operator (bool) -------------------------------------//

const bool ppBool::operator=(const char ch)
{
    m_chValue = ch == c_chTRUE ? c_chTRUE : c_chFALSE;
    Char2Bool(m_chValue);
    return m_bValue;
}

//--- (ppBool)Assignment operator (int) --------------------------------------//

const bool ppBool::operator=(const int i)
{
    m_chValue = i == 1 ? c_chTRUE : c_chFALSE;
    Int2Bool(i);
    return m_bValue;
}

//--- (ppBool)Unassignment operator (bool) -----------------------------------//

const bool ppBool::operator!()
{
    return m_bValue ? false : true;
}

//--- (ppBool)GetSign --------------------------------------------------------//

const char ppBool::GetSign() const
{
    return m_bValue ? m_chSTrue : m_chSFalse;
}

//--- (ppBool)GetSign --------------------------------------------------------//

const char* ppBool::GetText() const
{
    return m_bValue ? m_strTrue.c_str() : m_strFalse.c_str();
}

//--- (ppBool)Bool2Char (protected) ------------------------------------------//

void ppBool::Bool2Char(const bool b)
{
    m_chValue = b ? c_chTRUE : c_chFALSE;
}

//--- (ppBool)Char2Bool (protected) ------------------------------------------//

void ppBool::Char2Bool(const char ch)
{
    m_bValue = ch == c_chTRUE ? true : false;
}

//--- (ppBool)Int2Bool (protected) -------------------------------------------//

void ppBool::Int2Bool(const int i)
{
    m_bValue = (i == 1) ? true : false;
}

void ppBool::Init(const short sLanguage)
{
    if (sLanguage == 0)
    {
       m_chSTrue = 'Y';
       m_chSFalse = 'N';
       m_strTrue = "Yes";
       m_strFalse = "No";
    }
    else if (sLanguage == 1)
    {
       m_chSTrue = 'J';
       m_chSFalse = 'N';
       m_strTrue = "Ja";
       m_strFalse = "Nein";
    }
}

//----------------------------------------------------------------------------//
//--- ppBitstrip (convert bits (as boolean) to integer) ----------------------//
//----------------------------------------------------------------------------//

//--- (ppBitstrip)standard constructor ---------------------------------------//

ppBitstrip::ppBitstrip()
{
    m_lBitstrip = 0;
}

//--- (ppBitstrip) constructor (long) ----------------------------------------//

ppBitstrip::ppBitstrip(const unsigned long l)
{
    m_lBitstrip = (l > MAX_BIT || l < 0) ? 0L : l;
}

//--- (ppBitstrip) methodes (SetBit) -----------------------------------------//

void ppBitstrip::SetBit(const int iBitPos, const bool bIsOn)
{
    bIsOn ? SetBit(iBitPos) : UnsetBit(iBitPos);
}

//--- (ppBitstrip) methodes (GetBit) -----------------------------------------//

const bool ppBitstrip::GetBit(const int iBitPos)
{
    return IsBitSet(iBitPos);
}

//--- (ppBitstrip)Typecast operator (long) -----------------------------------//

ppBitstrip::operator long() const
{
    return m_lBitstrip;
}

//--- (ppBitstrip)Assignment operator (long) ---------------------------------//

const long ppBitstrip::operator=(const ppBitstrip& Bitstrip)
{
    m_lBitstrip = Bitstrip.m_lBitstrip;
    return m_lBitstrip;
}

//--- (ppBitstrip)Assignment operator (ppBitStrip&) --------------------------//

const ppBitstrip& ppBitstrip::operator=(const long l)
{
    m_lBitstrip = (l > MAX_BIT || l <= -1) ? 0L : l;
    return *this;
}

//--- (ppBitstrip)operator == (ppBitStrip&) ----------------------------------//

const bool ppBitstrip::operator==(const ppBitstrip& Bitstrip)
{
    return (m_lBitstrip == Bitstrip.m_lBitstrip);
}

//--- (ppBitstrip)SetBit (protected) -----------------------------------------//

void ppBitstrip::SetBit(const int iBitPos)
{
    assert(iBitPos >= 0 && iBitPos <= 15);

    int iBit = 0x0001;
    iBit <<= 15 - iBitPos;
    m_lBitstrip |= iBit;
}

//--- (ppBitstrip)UnsetBit (protected) ---------------------------------------//

void ppBitstrip::UnsetBit(const int iBitPos)
{
    assert(iBitPos >= 0 && iBitPos <= 15);

    int iBit = 0x0001;
    iBit <<= 15 - iBitPos;
    m_lBitstrip &= ~iBit;
}

//--- (ppBitstrip)IsBit (protected) ------------------------------------------//

bool ppBitstrip::IsBitSet(const int iBitPos)
{
    assert(iBitPos >= 0 && iBitPos <= 15);

    return ((m_lBitstrip >> (15 - iBitPos)) % 2) ? true : false;
}

//----------------------------------------------------------------------------//
//--- ppRights (check rights form const char*) -------------------------------//
//----------------------------------------------------------------------------//

//--- (ppRights)standard constructor -----------------------------------------//

ppRights::ppRights() : c_TRUE('1'), c_FALSE('0')
{
    char szFill[MAX_RIGTH_LENGTH + 1];
    memset(szFill, '0', MAX_RIGTH_LENGTH);
    szFill[MAX_RIGTH_LENGTH] = '\0';
    m_strRights = szFill;
}

//--- (ppRights) constructor (long) ------------------------------------------//

ppRights::ppRights(const ppString&) : c_TRUE('1'), c_FALSE('0')
{
    char szFill[MAX_RIGTH_LENGTH + 1];
    memset(szFill, '0', MAX_RIGTH_LENGTH);
    szFill[MAX_RIGTH_LENGTH] = '\0';
    m_strRights = szFill;
}

//--- (ppRights) methodes (SetBit) -------------------------------------------//

void ppRights::SetRight(const int iPos, const bool bIsOn)
{
    bIsOn ? SetRight(iPos) : UnsetRight(iPos);
}

//--- (ppRights) methodes (GetBit) -------------------------------------------//

const bool ppRights::GetRight(const int iPos)
{
    return IsRightSet(iPos);
}

//--- (ppRights)Typecast operator (ppString) ---------------------------------//

ppRights::operator ppString() const
{
    return m_strRights;
}

//--- (ppRights)operator == (ppRights&) --------------------------------------//

const bool ppRights::operator==(const ppRights& Rights)
{
    return (m_strRights == Rights.m_strRights);
}

//--- (ppRights)Assignment operator (ppRights&) ------------------------------//

const ppString& ppRights::operator=(const ppRights& Rights)
{
    if (this == &Rights)
        return m_strRights;
    m_strRights = Rights.m_strRights;
    return m_strRights;
}

//--- (ppRights)Assignment operator (ppString&) ------------------------------//

const ppRights& ppRights::operator=(const ppString strRights)
{
    if (m_strRights == strRights)
        return *this;
    m_strRights = strRights;
    if (strRights.length() < MAX_RIGTH_LENGTH)
    {
       char szFill[MAX_RIGTH_LENGTH+1];
       memset( szFill, '0', MAX_RIGTH_LENGTH - strRights.length() );
       szFill[MAX_RIGTH_LENGTH - strRights.length()] = '\0';
       m_strRights.append(szFill);
    }
    return *this;
}

//--- (ppRights)SetRights (protected) ----------------------------------------//

void ppRights::SetRight(const int iPos)
{
    assert(m_strRights.length() > static_cast<unsigned int>(iPos));

    m_strRights.at(iPos) = c_TRUE;
}

//--- (ppRights)UnsetBit (protected) -----------------------------------------//

void ppRights::UnsetRight(const int iPos)
{
    assert(m_strRights.length() > static_cast<unsigned int>(iPos));

    m_strRights.at(iPos) = c_FALSE;
}

//--- (ppRights)IsBit (protected) ------------------------------------------//

bool ppRights::IsRightSet(const int iPos)
{
    assert(m_strRights.length() > static_cast<unsigned int>(iPos));

    return m_strRights.at(iPos) == c_TRUE ? true : false;
}

//----------------------------------------------------------------------------//
//--- ppLanguageText (get textstring from languagefile) ----------------------//
//----------------------------------------------------------------------------//

//--- (ppLanguageText)standard constructor -----------------------------------//

ppLanguageText::ppLanguageText()
{
    m_pLanguageStringList = NULL;
    m_iGroup = -1;
}

//--- (ppLanguageText) constructor (ppGLanguageStringList) -------------------//

ppLanguageText::ppLanguageText(const ppGLanguageStringList* pLanguageStringList, const int iGroup)
{
    m_pLanguageStringList = (ppGLanguageStringList*)pLanguageStringList;
    m_iGroup = iGroup;
}

//--- (ppLanguageText) SetLanguageStringList ---------------------------------//

void ppLanguageText::SetLanguageStringList(const ppGLanguageStringList* pLanguageStringList)
{
    m_pLanguageStringList = (ppGLanguageStringList*)pLanguageStringList;
}

const ppGLanguageStringList* ppLanguageText::GetLanguageStringList() const
{
    return m_pLanguageStringList;
}

//--- (ppLanguageText) SetGroupNo --------------------------------------------//

const ppLanguageText&  ppLanguageText::SetGroupNo(const int iGroup)
{
    m_iGroup = iGroup;
    return *this;
}

//--- (ppLanguageText) GetString ---------------------------------------------//

const char* ppLanguageText::GetString(const int iTextNo)
{
    return m_pLanguageStringList->GetString(m_iGroup, iTextNo, m_strText);
}

//--- (ppLanguageText) GetString ---------------------------------------------//

const char* ppLanguageText::GetString(const int iGroup, const int iTextNo)
{
    return m_pLanguageStringList->GetString(iGroup, iTextNo, m_strText);
}

//--- (ppLanguageText) GetPath -----------------------------------------------//

const char* ppLanguageText::GetPath() const
{
    return m_pLanguageStringList->GetPath().c_str();
}

//--- (ppLanguageText) GetLanguage -------------------------------------------//

const short ppLanguageText::GetLanguage() const
{
    return m_pLanguageStringList->GetLanguage();
}

//--- ppDayType --------------------------------------------------------------//
//--- change char* to int ----------------------------------------------------//
//----------------------------------------------------------------------------//

//--- (ppDayType)standard constructor ----------------------------------------//

ppDayType::ppDayType(const short iLanguage)
{
    Initialize(iLanguage);
}

//--- (ppDayType)constructor (ppString) --------------------------------------//

ppDayType::ppDayType(const ppString& str, const short iLanguage)
{
    Initialize(iLanguage);
    *this = str;
}

//--- (ppDayType)constructor (t_day) -----------------------------------------//

ppDayType::ppDayType(const t_day day, const short iLanguage)
{
    Initialize(iLanguage);
    *this = day;
}

//--- (ppDayType)constructor (t_day) -----------------------------------------//

ppDayType::ppDayType(const ppDayType& day)
{
    for (int i = 0; i < 7; i++)
        strcpy(m_szaWeekDay[i], day.m_szaWeekDay[i]);
    m_iDayNo = day.m_iDayNo;
}

//--- (ppDayType)constructor (ppDate) -----------------------------------------//

ppDayType::ppDayType(const ppDate& date)
{
    SetDayNo(date);
}

//--- (ppDayType)deconstructor -----------------------------------------------//

ppDayType::~ppDayType()
{
}

//--- (ppDayType)(const char) ------------------------------------------------//

const char ppDayType::c_char() const
{
    return static_cast<char>(m_iDayNo + '0');
}

const char* ppDayType::GetWeekDay() const
{
    return m_szaDayText[m_iDayNo];
}

//--- (ppDayType)Typecast operator (ppString) --------------------------------//

ppDayType::operator ppString() const
{
    return m_szaWeekDay[m_iDayNo];
}

//--- (ppDayType)Typecast operator (const char*) -----------------------------//

ppDayType::operator const char*() const
{
    return m_szaWeekDay[m_iDayNo];
}

//--- (ppDayType)Typecast operator (int) -------------------------------------//

ppDayType::operator int() const
{
    return m_iDayNo;
}

//--- (ppDayType)Typecast operator (t_day) -----------------------------------//

ppDayType::operator ppDayType::t_day() const
{
    return (t_day)m_iDayNo;
}


//--- (ppDayType)operator == (ppRights&) -------------------------------------//

const bool ppDayType::operator==(const ppDayType& Rights)
{
    return (m_iDayNo == Rights.m_iDayNo);
}

//--- (ppDayType)Assignment operator (t_day) ---------------------------------//

const ppDayType& ppDayType::operator=(const t_day Rights)
{
    if (m_iDayNo == (int)Rights)
        return *this;

    assert(Rights >= d_sunday && Rights <= d_saturday);
    m_iDayNo = (int)Rights;
    return *this;
}

//--- (ppDayType)Assignment operator (ppString&) -----------------------------//

const ppDayType& ppDayType::operator=(const ppString& str)
{
    m_iDayNo = GetDayPos(str);
    return *this;
}

//--- (ppDayType)Initialize (protected) --------------------------------------//

void ppDayType::Initialize(const short iLanguage)
{
    m_iDayNo = 0;
    const char* pGerDay[] = { "SO", "MO", "DI", "MI", "DO", "FR", "SA" };
    const char* pEngDay[] = { "SU", "MO", "TU", "WE", "TH", "FR", "SA" };
    const char **pDay = (iLanguage == 1) ? pGerDay : pEngDay;
    for (int i = 0; i < 7; i++)
    {
        strcpy(m_szaWeekDay[i], pDay[i]);
    }

    const char* pGerText[] = { "Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag" };
    const char* pEngText[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    const char **pText = iLanguage == 1 ? pGerText : pEngText;
    for (int x = 0; x < 7; x++)
    {
        strcpy(m_szaDayText[x], pText[x]);
    }
}

//--- (ppDayType)getDayPos (protected) ---------------------------------------//

int ppDayType::GetDayPos(const ppString& str)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        if (str == m_szaWeekDay[i])
            return i;
    }

    assert(i > 0 && i < 7);
    return 0;
}

//--- (ppDayType)SetDayNo (protected) ----------------------------------------//

void ppDayType::SetDayNo(const ppDate& date)
{
   tm tmTime;
   tm* ptmTime;

   tmTime.tm_year  = (int)((date  / 10000L) - 1900L);
   tmTime.tm_mon   = (int)(((date / 100L) % 100L) - 1L);
   tmTime.tm_mday  = (int)(date % 100L);
   tmTime.tm_hour  = 0;
   tmTime.tm_min   = 0;
   tmTime.tm_sec   = 0;
   tmTime.tm_isdst = -1;
   time_t lDate = mktime(&tmTime);
   if (lDate == -1)
   {
      m_iDayNo = 0;
      return;
   }

   ptmTime = localtime(&lDate);
   m_iDayNo = ptmTime->tm_wday;
}

//--- ppTime -----------------------------------------------------------------//
//--- display long to char* with dots ----------------------------------------//
//----------------------------------------------------------------------------//

//--- (ppTime)standard constructor -------------------------------------------//

ppTime::ppTime(const t_timedisplay eTimeDisplay)
{
    Init(eTimeDisplay);
}

//--- (ppTime)constructor (ppString) -----------------------------------------//

ppTime::ppTime(const ppString& strTime, const t_timedisplay eTimeDisplay, const bool bIsCheck)
{
    Init(eTimeDisplay);
    SetTimeStr(strTime);
    m_lTime = GetTime();
    m_bIsCheck = bIsCheck;
}

//--- (ppTime)constructor (long) ---------------------------------------------//

ppTime::ppTime(const long lTime, const t_timedisplay eTimeDisplay)
{
    Init(eTimeDisplay);
    m_bIsCheck = true;
    SetTimeStr(lTime);
    m_lTime = GetTime();
}

//--- (ppTime)copy constructor (long) ----------------------------------------//

ppTime::ppTime(const ppTime& Rights)
{
    *this = Rights;
}

//--- (ppTime)Typecast operator (const char*) --------------------------------//

const ppTime& ppTime::GetObject() const
{
    return *this;
}

//--- (ppTime)is_null (const bool) -------------------------------------------//

const bool ppTime::is_null() const
{
    return (m_lTime == 0) ? true : false;
}

//--- (ppTime)Typecast operator (const char*) --------------------------------//

ppTime::operator const char*() const
{
    return m_strTime.c_str();
}

//--- (ppTime)Typecast operator (const long) ---------------------------------//

ppTime::operator const long() const
{
    return m_lTime;
}

//--- (ppTime)operator == (ppRights&) ----------------------------------------//

const bool ppTime::operator==(const ppTime& Rights)
{
    return ( m_strTime == Rights.m_strTime &&
             m_lTime   == Rights.m_lTime &&
             m_iRegulation == Rights.m_iRegulation );
}

//--- (ppTime)Assignment operator (t_day) ------------------------------------//

const ppTime& ppTime::operator=(const ppTime& Rights)
{
    if (this == &Rights)
        return *this;

    m_strTime = Rights.m_strTime;
    m_lTime   = Rights.m_lTime;
    m_iRegulation = Rights.m_iRegulation;
    return *this;
}

//--- (ppTime)lower then operator (t_day) ------------------------------------//

const bool ppTime::operator<(const long Rights)
{
    ppTime t(Rights, m_iRegulation);
    return GetSecond() < t.GetSecond();
}

//--- (ppTime)greater then operator (t_day) ----------------------------------//

const bool ppTime::operator>(const long Rights)
{
    ppTime t(Rights, m_iRegulation);
    return GetSecond() > t.GetSecond();
}

//--- (ppTime)lower equal operator (t_day) -----------------------------------//

const bool ppTime::operator<=(const long Rights)
{
    ppTime t(Rights, m_iRegulation);
    return GetSecond() <= t.GetSecond();
}

//--- (ppTime)greater equal operator (t_day) ---------------------------------//

const bool ppTime::operator>=(const long Rights)
{
    ppTime t(Rights, m_iRegulation);
    return GetSecond() >= t.GetSecond();
}

const long ppTime::operator-(ppTime& Rights)
{
    return GetSecond() - Rights.GetSecond();
}

const long ppTime::operator+(ppTime& Rights)
{
    return GetSecond() + Rights.GetSecond();
}

//--- (ppTime)SetTime (ppString) ---------------------------------------------//

void ppTime::SetTime(const ppString& strTime)
{
    SetTimeStr(strTime);
    m_lTime = GetTime();
}

//--- (ppTime)SetTime (long) -------------------------------------------------//

void ppTime::SetTime(const long lTime)
{
    m_bIsCheck = true;
    SetTimeStr(lTime);
    m_lTime = GetTime();
    m_bIsChanged = false;
}

//--- (ppTime)GetState (t_time) ----------------------------------------------//

const ppTime::t_time ppTime::GetState() const
{
    return m_eError;
}

//--- (ppTime)IsChanged (bool) -----------------------------------------------//

const bool ppTime::IsChanged() const
{
    return m_bIsChanged;
}

//--- (ppTime)GetTime (const char*) ------------------------------------------//

const char* ppTime::GetTime() const
{
    return m_strTime.c_str();
}

//--- (ppTime)SetTime (long) -------------------------------------------------//

const int ppTime::GetPos() const
{
    return m_iPos;
}

//--- (ppTime)Add (minutes) --------------------------------------------------//

const ppTime& ppTime::Add(const short sAddMinute)
{
    long lSeconds = GetSecond();
    lSeconds += (sAddMinute * 60); //Add the minutes

    SetNewTime(lSeconds);
    SetTimeStr(m_lTime);
    return *this;
}

//--- (ppTime)Sub (minutes) --------------------------------------------------//

const ppTime& ppTime::Sub(const short sSubMinute)
{
    long lSeconds = GetSecond();
    lSeconds -= (sSubMinute * 60); //Add the minutes

    SetNewTime(lSeconds);
    SetTimeStr(m_lTime);
    return *this;
}

//--- (ppTime)GetSecond ------------------------------------------------------//

const long ppTime::GetSecond()
{
    short sHour   = GetTHour();
    short sMinute = GetTMinute();
    short sSecond = GetTSecond();

    return (sHour * 60 * 60) + (sMinute * 60) + sSecond;
}

const short ppTime::GetTHour()
{
    long divisor = (m_iRegulation == display_hhmm) ? 100 : 10000;

    long hours = m_lTime / divisor;
    return static_cast<short>(hours);
}

const short ppTime::GetTMinute()
{
    return (m_iRegulation == display_hhmm) ? m_lTime % 100 : (m_lTime / 100L) % 100L;
}

const short ppTime::GetTSecond()
{
    return (m_iRegulation == display_hhmm) ? 0 : m_lTime % 100;
}

//--- (ppTime)GetSecond ------------------------------------------------------//

void ppTime::SetNewTime(const long lSeconds)
{
    long hour = lSeconds / 3600;
    long minute = (lSeconds % 3600) / 60;
    long second = (lSeconds % 3600) % 60;
    m_lTime =   hour * (m_iRegulation==display_hhmm ? 100 : 10000);
    m_lTime +=  minute * (m_iRegulation==display_hhmm ? 1 : 100);
    m_lTime +=  second;
}

//--- (ppTime)GetTime (ppString) ---------------------------------------------//

void ppTime::SetTimeStr(const ppString& strTime)
{
    ppString str = strTime;
    while (str.find(":") != ppString::npos)
        str.remove(":");

    for (; m_bIsCheck && (str.length() < static_cast<unsigned int>(m_iRegulation));)
    {
       str = "0" + str;
    }

    if (!CheckTimeValue(str) || !CheckHour(str) || !CheckMinute(str) || !CheckSecond(str))
    {
       m_strTime = "";
       return;
    }

    m_iPos = 0;
    m_strTime = "";
    for (unsigned int i = 0; i < str.length(); i++, m_iPos++)
    {
        if (i != 0 && i % 2 == 0 && i != static_cast<unsigned int>(m_iRegulation))
        {
           m_strTime += ":";
           m_iPos++;
        }
        m_strTime += ppString(str.at(i));
    }

    m_bIsChanged = (str.length() == m_strTime.length()) ? false : true;
}

//--- (ppTime)GetTime (long) -------------------------------------------------//

const long ppTime::GetTime()
{
    ppString str = m_strTime;
    while (str.find(":") != ppString::npos)
        str.remove(":");
    return str.stol();
}

//--- (ppTime)Init (protected) -----------------------------------------------//

void ppTime::Init(const t_timedisplay eTimeDisplay)
{
    m_strTime = "";
    m_lTime = 0;
    m_eError = is_ok;
    m_iPos = 0;
    m_bIsChanged = false;
    m_iRegulation = eTimeDisplay;
    m_bIsCheck = false;
}

//--- (ppTime)CheckTimeValue (protected) -------------------------------------//

bool ppTime::CheckTimeValue(ppString& str)
{
    const int iTimeCheck = (m_iRegulation == display_hhmm) ? 2400 : 240000;

    if (str.stol() < 0 || str.stol() > iTimeCheck || str.length() > static_cast<unsigned int>(m_iRegulation))
    {
        if (str.length() <= static_cast<unsigned int>(m_iRegulation))
        {
            m_eError = is_false;
            m_iPos = 0;
            return false;
        }
        else
            str.at(m_iRegulation) = '\0';
    }
    return true;
}

//--- (ppTime)CheckHour (protected) ------------------------------------------//

bool ppTime::CheckHour(ppString& str)
{
    AdaptTimeStr(str);
    str.exchange( " ", "0" );
    if (str.stol() / (m_iRegulation == display_hhmm ? 100 : 10000) > 24)
    {
        m_eError = is_hour_invalid;
        return false;
    }
    return true;
}

//--- (ppTime)CheckMinute (protected) ----------------------------------------//

bool ppTime::CheckMinute(ppString& str)
{
    AdaptTimeStr(str);
    str.exchange(" ", "0");
    int iMin = 0;
    int iLen = str.length();

    if (m_iRegulation == display_hhmm)
    {
        if (iLen == 3)
            iMin = str.stol() % 10;
        else if (iLen == 4)
            iMin = str.stol() % 100;
    }
    else
    {
        if ((iLen) == 3)
            iMin = str.stol() % 10;
        else if (iLen == 4)
            iMin = str.stol() % 100;
    }

    if (iMin > 59)
    {
        m_eError = is_minute_invalid;
        return false;
    }
    return true;
}

//--- (ppTime)CheckSecond (protected) ----------------------------------------//

bool ppTime::CheckSecond(ppString& str)
{
    if (m_iRegulation == display_hhmm)
        return true;

    AdaptTimeStr(str);
    str.exchange(" ", "0");
    if (str.stol() % 100 > 59)
    {
        m_eError = is_second_invalid;
        return false;
    }
    return true;
}

//--- (ppTime)GetTimeStr (protected) -----------------------------------------//

void ppTime::AdaptTimeStr(ppString& str)
{
    char szTime[display_hhmmss + 3];

    if (str.length() > 1 && str.at(0) == '0')
    {
        return;
    }
    else if (str.length() > 1 && str.at(0) > '2') //read from persitenz
    {
        sprintf(szTime, "%0*ld", m_iRegulation, atol(str.c_str()));
    }
    else
    {
        return;
    }

    str = szTime;
}

//--- ppDate -----------------------------------------------------------------//
//--- display long to char* with dots ----------------------------------------//
//----------------------------------------------------------------------------//

//--- (ppDate)standard constructor -------------------------------------------//

ppDate::ppDate()
{
    Init();
}

//--- (ppDate)constructor (ppString) -----------------------------------------//

ppDate::ppDate(const ppString& strDate)
{
    Init();
    SetDateStr(strDate);
    m_lDate = GetDate();
}

//--- (ppDate)constructor (long) ---------------------------------------------//

ppDate::ppDate(const long lDate)
{
    Init();
    SetDateStr(lDate);
    m_lDate = lDate;
}

//--- (ppDate)Typecast operator (const char*) --------------------------------//

ppDate::operator const char*() const
{
    return m_strDate.c_str();
}

//--- (ppDate)Typecast operator (const long) ---------------------------------//

ppDate::operator const long () const
{
    return m_lDate;
}

//--- (ppDate)operator == (ppRights&) ----------------------------------------//

const bool ppDate::operator==(const ppDate& Rights)
{
    return ( m_strDate == Rights.m_strDate &&
             m_lDate   == Rights.m_lDate );
}

//--- (ppDate)Assignment operator (t_day) ------------------------------------//

const ppDate& ppDate::operator=(const ppDate& Rights)
{
    if (this == &Rights)
        return *this;

    m_strDate = Rights.m_strDate;
    m_lDate   = Rights.m_lDate;
    return *this;
}

//--- (ppDate)SetTime (ppString) ---------------------------------------------//

void ppDate::SetDate(const ppString& strDate)
{
    SetDateStr(strDate);
    m_lDate = GetDate();
}

//--- (ppDate)SetTime (long) -------------------------------------------------//

void ppDate::SetDate(const long lDate)
{
    SetDateStr(lDate);
    m_lDate = lDate;
}

//--- (ppDate)Init (protected) -----------------------------------------------//

void ppDate::Init()
{
    m_strDate = "";
    m_lDate = 0;
}

//--- (ppDate)SetDateStr (protected) -----------------------------------------//

void ppDate::SetDateStr(const ppString& strDate)
{
    ppString str = strDate;
    if (str.length() == 7)
        str = "0" + str;
    while (str.find(".") != ppString::npos)
        str.remove(".");

    m_strDate = "";
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (i != 0 && i % 2 == 0 && i < 5)
        {
           m_strDate += ".";
        }
        m_strDate += ppString(str.at(i));
    }
}

//--- (ppDate)SetDateStr (protected) -----------------------------------------//

void ppDate::SetDateStr(const long lDateYMD)
{
    long sYear  = lDateYMD / 10000;
    long sMonth = (lDateYMD % 10000) / 100;
    long sDay   = lDateYMD % 100;

    long lDate = (sDay * 1000000) + (sMonth * 10000) + sYear;
    SetDateStr(ppString(lDate));
}

//--- (ppDate)GetDate (protected) --------------------------------------------//

const long ppDate::GetDate()
{
    ppString str = m_strDate;
    while (str.find(".") != ppString::npos)
        str.remove(".");
    long lDate = str.stol();
    long sYear = lDate % 10000;
    long sMonth = (lDate / 10000) % 100;
    long sDay = lDate / 1000000;

    return (sYear * 10000) + (sMonth * 100) + sDay;
}

//--- ppFieldLength ----------------------------------------------------------//
//--- Length + decimalLength -------------------------------------------------//
//----------------------------------------------------------------------------//

//--- (ppFieldLength)standard constructor ------------------------------------//

ppFieldLength::ppFieldLength(const short sLength, const short sDecimalPlace/*=0*/)
{
    m_sLength = sLength;
    m_sDecimalPlace = sDecimalPlace;
}

//--- (ppFieldLength)Typecast operator (const long) --------------------------//

ppFieldLength::operator const long () const
{
    return m_sLength;
}

//--- (ppFieldLength)IsDecimal -----------------------------------------------//

const bool ppFieldLength::IsDecimal() const
{
    return (m_sDecimalPlace > 0) ? true : false;
}

//--- (ppFieldLength)GetLength -----------------------------------------------//

const short ppFieldLength::GetLength() const
{
    return m_sLength;
}

//--- (ppFieldLength)GetDecimalPlace -----------------------------------------//

const short ppFieldLength::GetDecimalPlace() const
{
    return m_sDecimalPlace;
}
