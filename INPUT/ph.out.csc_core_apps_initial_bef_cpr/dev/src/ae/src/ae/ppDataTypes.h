#pragma once

//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDataTypes.h
   Author: A.Schmidt-Rehschuh
   made  : 07.02.2000
                            >No changes in this text may be made<
   declaration:
   own data types for the general use
*/

#include <ppstring.h>

typedef const char BTCHAR;

//--- precompiler ------------------------------------------------------------//

class ppGLanguageStringList;

//--- ppBool -----------------------------------------------------------------//
//--- Variable extension of the boolean one ones around the CharTyp('0','1') -//
//----------------------------------------------------------------------------//

class ppBool
{
public: //constructor
    ppBool(const short sLanguage = 1);
    ppBool(const bool b, const short sLanguage = 1);
    ppBool(const char ch, const short sLanguage = 1);
    ppBool(const int  i, const short sLanguage = 1);

public: //operator
    operator bool() const;
    operator BTCHAR() const;
    operator int() const;
    const bool operator=(const bool b);
    const bool operator=(const char ch);
    const bool operator=(const int i);
    const bool operator!();

public: //methodes
    const char GetSign() const;
    const char* GetText() const;

protected:
    void Bool2Char(const bool b);
    void Char2Bool(const char ch);
    void Int2Bool(const int i);
    void Init(const short sLanguage);

protected:
    bool        m_bValue;
    char        m_chValue;
    char        m_chSTrue;
    char        m_chSFalse;
    ppString    m_strTrue;
    ppString    m_strFalse;

protected:
    const char c_chTRUE;
    const char c_chFALSE;

private:
    ppBool& operator=(const ppBool& b);
};

//--- ppBitstrip -------------------------------------------------------------//
//--- read/wrirte bit from/to byte -------------------------------------------//
//----------------------------------------------------------------------------//

class ppBitstrip
{
#define MAX_BIT 65535
public: //constructor
    ppBitstrip();
    ppBitstrip(const unsigned long l);

public: //methodes
    void SetBit(const int iBitPos, const bool bIsOn);
    const bool GetBit(const int iBitPos);

public: //operator
    operator long() const;
    const long operator=(const ppBitstrip& Bitstrip);
    const ppBitstrip& operator=(const long l);
    const bool operator==(const ppBitstrip& Bitstrip);

protected:
    void SetBit(const int iBitPos);
    void UnsetBit(const int iBitPos);
    bool IsBitSet(const int iBitPos);

protected:
    unsigned long m_lBitstrip;
};

//--- ppRights ---------------------------------------------------------------//
//--- check userrights -------------------------------------------------------//
//----------------------------------------------------------------------------//

class ppRights
{
#define MAX_RIGTH_LENGTH 100
public: //constructor
    ppRights();
    ppRights(const ppString&);

public: //methodes
    void SetRight(const int iPos, const bool bIsOn);
    const bool GetRight(const int iPos);

public: //operator
    operator ppString() const;
    operator const char*() const;
    const bool operator==(const ppRights& Rights);
    const ppString& operator=(const ppRights& Rights);
    const ppRights& operator=(const ppString strRights);

protected:
    void SetRight(const int iBitPos);
    void UnsetRight(const int iBitPos);
    bool IsRightSet(const int iBitPos);

protected:
    ppString   m_strRights;
    const char c_TRUE;
    const char c_FALSE;
};

//--- ppLanguageText ---------------------------------------------------------//
//--- get textstring from languagefile ---------------------------------------//
//----------------------------------------------------------------------------//

class ppLanguageText
{
public: //constructor
    ppLanguageText();
    ppLanguageText(const ppGLanguageStringList* pLanguageStringList, const int iGroup);

public: //methodes
    void SetLanguageStringList(const ppGLanguageStringList* pLanguageStringList);
    const ppLanguageText& SetGroupNo(const int iGroup);
    const char* GetString(const int iTextNo);
    const char* GetString(const int iGroup, const int iTextNo);
    const char* GetPath() const;
    const short GetLanguage() const;
    const ppGLanguageStringList* GetLanguageStringList() const;

protected:
    int      m_iGroup;
    ppString m_strText;
    ppGLanguageStringList* m_pLanguageStringList;
};

//--- ppDate -----------------------------------------------------------------//
//--- change char* to int ----------------------------------------------------//
//----------------------------------------------------------------------------//

class ppDate
{
public: //constructor
    ppDate();
    ppDate(const ppString& strDate);
    ppDate(const long lDate);

public: //methodes
    void SetDate(const ppString& strDate);
    void SetDate(const long lDate);
    long GetDatum() { return m_lDate; }

public: //operator
    operator const char*() const;
    operator const long () const;
    const bool operator==(const ppDate& Rights);
    const ppDate& operator=(const ppDate& Rights);

protected: //methodes
    void Init();
    void SetDateStr(const ppString& strDate);
    void SetDateStr(const long lDate);
    const long GetDate();

protected: //members
    long     m_lDate;
    ppString m_strDate;
};

//--- ppDayType --------------------------------------------------------------//
//--- change char* to int ----------------------------------------------------//
//----------------------------------------------------------------------------//

class ppDayType
{
public:
    enum t_day
    {
        d_sunday    = 0,
        d_monday    = 1,
        d_tuesday   = 2,
        d_wednesday = 3,
        d_thursday  = 4,
        d_friday    = 5,
        d_saturday  = 6
    };

public: //constructor
    ppDayType(const short iLanguage=1);
    ppDayType(const ppString& str, const short iLanguage=1);
    ppDayType(const t_day day, const short iLanguage=1);
    ppDayType(const ppDayType& day);
    ppDayType(const ppDate& date);
    ~ppDayType();

public:
    const char c_char() const;
    const char* GetWeekDay() const;

public: //operator
    operator t_day() const;
    operator int() const;
    operator ppString() const;
    operator const char*() const;
    const bool operator==(const ppDayType& Rights);
    const ppDayType& operator=(const t_day Rights);
    const ppDayType& operator=(const ppString& Rights);

protected:
    char m_szaWeekDay[7][3];
    char m_szaDayText[7][11];
    int  m_iDayNo;

protected:
    void Initialize(const short iLanguage);
    int GetDayPos(const ppString& str);
    void SetDayNo(const ppDate& date);
};

//--- ppTime -----------------------------------------------------------------//
//--- change char* to int ----------------------------------------------------//
//----------------------------------------------------------------------------//

class ppTime
{
public: //enum's
    enum t_time
    {
        is_ok             = 0,
        is_false          = 1,
        is_hour_invalid   = 2,
        is_minute_invalid = 3,
        is_second_invalid = 4
    };

    enum t_timedisplay
    {
        display_hhmm   = 4,
        display_hhmmss = 6
    };

public: //constructor
    ppTime(const t_timedisplay eTimeDisplay = display_hhmm);
    ppTime(const ppString& strTime, const t_timedisplay eTimeDisplay = display_hhmm, const bool bIsCheck=false);
    ppTime(const long lTime, const t_timedisplay eTimeDisplay = display_hhmm);
    ppTime(const ppTime& Rights);

public: //methodes
    void SetTime(const ppString& strTime);
    void SetTime(const long lTime);
    const t_time GetState() const;
    const bool IsChanged() const;

    const char* GetTime() const;
    const int GetPos() const;

    const ppTime& Add(const short sAddMinute = 1);
    const ppTime& Sub(const short sSubMinute = 1);

public: //operator
    const ppTime& GetObject() const;
    const bool is_null() const;
    operator const char*() const;
    operator const long () const;
    const bool operator==(const ppTime& Rights);
    const ppTime& operator=(const ppTime& Rights);
    const bool operator<(const long Rights);
    const bool operator>(const long Rights);
    const bool operator<=(const long Rights);
    const bool operator>=(const long Rights);
    const long operator-(ppTime& Rights);
    const long operator+(ppTime& Rights);

protected: //methodes
    void SetTimeStr(const ppString& strTime);
    const long GetTime();
    void Init(const t_timedisplay eTimeDisplay);
    bool CheckTimeValue(ppString& str);
    bool CheckHour(ppString& str);
    bool CheckMinute(ppString& str);
    bool CheckSecond(ppString& str);
    void AdaptTimeStr(ppString& str);
    const long GetSecond();
    void SetNewTime(const long lSeconds);
    const short GetTHour();
    const short GetTMinute();
    const short GetTSecond();

protected: //members
    long     m_lTime;
    ppString m_strTime;
    t_time   m_eError;
    int      m_iPos;
    bool     m_bIsChanged;
    t_timedisplay m_iRegulation;
    bool     m_bIsCheck;
};

//--- ppFieldLength ----------------------------------------------------------//
//--- Length + decimalLength -------------------------------------------------//
//----------------------------------------------------------------------------//

class ppFieldLength
{
public: //constructor
    ppFieldLength(const short sLength, const short sDecimalPlace = 0);

public: //operator
    operator const long () const;

public: //methodes
    const bool IsDecimal() const;
    const short GetLength() const;
    const short GetDecimalPlace() const;

protected:
    short m_sLength;
    short m_sDecimalPlace;
};
