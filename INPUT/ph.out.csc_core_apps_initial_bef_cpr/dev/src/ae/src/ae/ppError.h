#pragma once

//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppError.h
   Author: A.Schmidt-Rehschuh
   made  : 03.02.2000
                            >No changes in this text may be made<
   declaration:
   Error-Base-Class
*/

class ppGLanguageStringList;
class ppError
{
public:
    enum t_Error
    {
        is_ok              = 0,     // ok
        is_file_not_open   = 1,     // message file coudn't be opened
        is_not_initialized = 2,     // no value given for select/update/etc.
        is_out_of_memory   = 3,     // wrong listid given
        is_notfound        = 4,     // no sentence found
        is_sqlerror        = 5,     // error in database
        is_data_error      = 6,     // corrupt data detected
        is_locked          = 7,     // row is locked in database
        is_exist           = 8,     // row exists in database
        is_read_only       = 9,     // only read rights
        is_not_modified    = 10,    // only read rights
        is_leg_exceeding   = 11,    // fieldlength oversize
        is_in_transaction  = 12,    // is already in transaction
        is_no_transaction  = 13,    // no transaction was started
        is_changed         = 14,    // sentence changed bevore update
        is_default         = 15,    // sentemnce not found, but initialized
        max_size_counter            // must be the last entry!
    };

public: //constructor
    ppError(const ppString& strPath = "c:\\ppErrorMsg",
            const short sLanguage = 1);
    ~ppError();

public: //ErrorState
    void  SetClassName(const ppString& strClass);
    void  SetFunctionName(const ppString& strFunction);
    const t_Error GetErrorState() const { return m_eError; }
    const char* GetErrorMsg(const t_Error eError=max_size_counter);
    const char* GetPath() const;
    const char* GetFile() const;
    const short GetLanguage() const;
    const ppGLanguageStringList* GetLanguageStringList() const;

protected: //members
    const ppString ERROR_FILE;
    ppGLanguageStringList *m_pLanguageStr;
    ppString m_strFile;
    short    m_sLanguage;
    bool     m_bIsInitialized;
    bool     m_bDoNotDelete;

private:
    ppError(const ppError& e);
    ppError& operator=(const ppError& e);

private:
    t_Error  m_eError;
    ppString m_strError;
    ppString m_strClass;
    ppString m_strFunction;

protected: //Setting-Methodes
    ppError(const ppGLanguageStringList* LanguageList);
    void SetErrorState( const t_Error eError ) { m_eError = eError; }
    bool Init();
};
