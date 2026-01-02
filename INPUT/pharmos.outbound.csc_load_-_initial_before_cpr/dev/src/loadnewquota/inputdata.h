#ifndef _INPUTDATA_H
#   define _INPUTDATA_H

#include <iostream>
#include <string>
#include <vector>

#ifndef __GNUC__
#include <regex>
#else
#include <regex.h>
#endif

#include "utils.h"
#include "csvparser.h"

// columns Index
#define IDX_BRANCHNO        0
#define IDX_CUSTOMERNO      1
#define IDX_ARTICLE_CODE    2
#define IDX_QUOTA           3
#define IDX_VALIDITY        4
#define IDX_DATEFROM        5
#define IDX_DATETO          6
#define IDX_PHARMACYGROUPID 7
#define MANDATORY_FIELDS_NUMBER 6

extern char g_cDelimiter;

typedef struct QUOTA_INTERN
{
    long        BRANCHNO;
    long        CUSTOMERNO;
    std::string ARTICLE_CODE;
    long        QUOTA;
    char        VALIDITY;
    long        DATEFROM;
    long        DATETO;
    long        PHARMACYGROUPID;
} QuotaIntern;

/////////////////////////////////////////////////// class QuotaTulpe
class QuotaTulpe
{
private:
    std::vector<QuotaIntern>&   m_vecQuotas;
    unsigned long               m_lineNum;
    bool                        m_bFilterPresent;

#ifndef __GNUC__
    std::regex m_reFilter;
#else
    regex_t m_reFilter;
#endif

public:
    QuotaTulpe(std::vector<QuotaIntern>& container)
        : m_vecQuotas(container), m_lineNum(0), m_bFilterPresent(false)
    {
    }

    QuotaTulpe(std::vector<QuotaIntern>& container, const std::string& filter)
        : m_vecQuotas(container), m_lineNum(0), m_bFilterPresent(true)
    {
#ifndef __GNUC__
        m_reFilter = std::regex(filter);
#else
        regcomp(&m_reFilter, filter.c_str(), REG_EXTENDED);
#endif
    }

    int ParseFields(const std::vector<std::string>& vecStrings, QuotaIntern &quotaIntern)
    {
        if(vecStrings.size() < MANDATORY_FIELDS_NUMBER)
            return false;
        if (!convertStringToLong(vecStrings[IDX_BRANCHNO], quotaIntern.BRANCHNO))
            return false;
        if (vecStrings[IDX_CUSTOMERNO].size() != 0)
        {
            if (!convertStringToLong(vecStrings[IDX_CUSTOMERNO], quotaIntern.CUSTOMERNO))
                return false;
        }
        else
        {
            quotaIntern.CUSTOMERNO = -1;
        }
        quotaIntern.ARTICLE_CODE = vecStrings[IDX_ARTICLE_CODE];
        if (!convertStringToLong(vecStrings[IDX_QUOTA], quotaIntern.QUOTA))
            return false;
        if (vecStrings[IDX_VALIDITY].size() < 1)
            return false;
        quotaIntern.VALIDITY = vecStrings[IDX_VALIDITY].at(0);
        if (!convertStringToLong(vecStrings[IDX_DATEFROM], quotaIntern.DATEFROM))
            return false;
        if (!convertStringToLong(vecStrings[IDX_DATETO], quotaIntern.DATETO))
            return false;
        if (quotaIntern.CUSTOMERNO == -1)
        {
            if (vecStrings.size() < (MANDATORY_FIELDS_NUMBER + 1) || !convertStringToLong(vecStrings[7], quotaIntern.PHARMACYGROUPID))
                return false;
        }
        else
        {
            quotaIntern.PHARMACYGROUPID = -1;
        }
        return true;
    }

    void Parse(const std::vector<std::string>& vecStrings)
    {
        QuotaIntern quotaIntern;
        bool        bParseSucceed = false;
        bool        bDataExists = false;
        std::string sData = "";
        std::string currentLine; // the whole line

        for (int i = 0; i < vecStrings.size(); i++)
        {
            if (!currentLine.empty()) currentLine += g_cDelimiter;
            sData = std::string(vecStrings[i]);
            trim(sData);
            currentLine += sData;
            if (sData.size() > 0)
            {
                bDataExists = true;
            }
        }

        m_lineNum++;
        if (bDataExists == true)
        {
            bParseSucceed = ParseFields(vecStrings, quotaIntern);
            if (bParseSucceed == true)
            {
                // check article number contains digits only
                if (!m_bFilterPresent || ApplyFilter(quotaIntern.ARTICLE_CODE, m_reFilter))
                {
                    m_vecQuotas.push_back(quotaIntern);
                }
                else
                {
                    LogError("Line: %ld: Failed Filter: %s", m_lineNum, currentLine.c_str());
                }
            }
            else
            {
                LogError("Line: %ld: Failed to parse: %s", m_lineNum, currentLine.c_str());
            }
        }
        else
        {
            LogWarning("Line: %ld, empty line, will be ignored", m_lineNum);
        }
    }

};

/////////////////////////////////////////////////// class InputData
class InputData
{
private:
    std::vector<QuotaIntern>    m_vecQuotas;
    CsvParser                   m_csvParser;

public:
    void LoadFromFile(const std::string csvFileName, const std::string& filter)
    {
        if (m_csvParser.OpenFile(csvFileName) != 0)
        {
            LogError("Fail to open file: %s", csvFileName.c_str());
            return;
        }
        std::vector<std::string>    curCSVRow;
        QuotaTulpe                  quotaTulpe(m_vecQuotas, filter);
        while (m_csvParser.CsvGetNextRow(curCSVRow))
        {
            quotaTulpe.Parse(curCSVRow);
        }
        m_csvParser.CloseFile();
    }

    InputData()
        :m_csvParser(g_cDelimiter)
    {
    }

    InputData(const std::string csvFileName, const std::string& filter)
        :m_csvParser(g_cDelimiter)
    {
        LoadFromFile(csvFileName, filter);
    }

    size_t RecCount() const { return m_vecQuotas.size(); }

    QUOTA_INTERN operator [](unsigned int idx) const
    {
        if (idx < RecCount())
        {
            return m_vecQuotas[idx];
        }
        else
        {
            QUOTA_INTERN dummy;
            return dummy;
        }
    }
};

#endif // _INPUTDATA_H
