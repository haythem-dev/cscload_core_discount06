
//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppError.cpp
   Author: A.Schmidt-Rehschuh
   made  : 03.02.2000

   declaration:
   Error-Base-Class
*/

//--- include ----------------------------------------------------------------//

#include "ppgenercpp.h"
#include "pperror.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

ppError::ppError(const ppString& strPath, const short sLanguage)
: ERROR_FILE("\\pperrormsg")
{
    m_pLanguageStr = new ppGLanguageStringList;
    m_eError = is_ok;

    ppString str = strPath;
    str.lower();
    if (str.find(ERROR_FILE) == ppString::npos)
        m_strFile = strPath + ERROR_FILE;
    else
        m_strFile = strPath;

    m_sLanguage = sLanguage;
    m_bIsInitialized = false;
    m_bDoNotDelete = false;
    Init();
}

//--- constructor ------------------------------------------------------------//

ppError::ppError(const ppGLanguageStringList* LanguageList)
: ERROR_FILE("\\pperrormsg")
{
    m_pLanguageStr = (ppGLanguageStringList*)LanguageList;
    m_bIsInitialized = true;
    m_bDoNotDelete = true;
    Init();
}

//--- deconstructor ----------------------------------------------------------//

ppError::~ppError()
{
    if (m_pLanguageStr && !m_bDoNotDelete)
        delete m_pLanguageStr;
}

//--- Init (class-members) ---------------------------------------------------//

bool ppError::Init()
{
    m_strClass = "";
    m_strFunction = "";

    if (m_bIsInitialized)
        return true;

    m_strFile.lower();
    m_pLanguageStr->InitStringTable(m_strFile, m_sLanguage);
    if (!m_pLanguageStr->ErrorMsg.empty())
    {
       m_eError = is_file_not_open;
       return false;
    }

    return (m_bIsInitialized = true);
}

//----------------------------------------------------------------------------//
//--- ErrorStatte (description) ----------------------------------------------//
//----------------------------------------------------------------------------//

//--- GetErrorMsg ------------------------------------------------------------//

const char* ppError::GetErrorMsg(const t_Error eError)
{
    if (eError != max_size_counter && (eError < 0 || eError >= max_size_counter))
        return m_pLanguageStr->GetString(0, is_out_of_memory + 1, m_strError );

    t_Error eErr = eError == max_size_counter ? m_eError : eError;
    m_pLanguageStr->GetString(0, (int)eErr + 1, m_strError );

    if (!m_strClass.empty() && !m_strFunction.empty())
        m_strError = m_strClass + "(" + m_strFunction + "):" + m_strError;
    else if (m_strClass.empty() && m_strFunction.empty())
        m_strError = m_strFunction + ":" + m_strError;
    else if (!m_strClass.empty() && m_strFunction.empty())
        m_strError = m_strClass + ":" + m_strError;

    return m_strError;
}

//--- GetFile ----------------------------------------------------------------//

const char* ppError::GetFile() const
{
    return ERROR_FILE.c_str();
}

//--- GetPath ----------------------------------------------------------------//

const char* ppError::GetPath() const
{
    return m_pLanguageStr->GetPath().c_str();
}

//--- GetLanguage() ----------------------------------------------------------//

const short ppError::GetLanguage() const
{
    return m_pLanguageStr->GetLanguage();
}

//--- GetLanguageStringList --------------------------------------------------//

const ppGLanguageStringList* ppError::GetLanguageStringList() const
{
    return m_pLanguageStr;
}

//--- SetClassName -----------------------------------------------------------//

void ppError::SetClassName(const ppString& strClass)
{
    m_strClass = strClass;
}

//--- SetFunctionName --------------------------------------------------------//

void ppError::SetFunctionName(const ppString& strFunction)
{
    m_strFunction = strFunction;
}
