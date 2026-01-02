/**************************************************************************/
/*    ...  module: csvParser                                              */
/*        Header : csvparser.h                                            */
/*          Autor: Fakhri Feki                                            */
/*        Created: 03.05.2024                                             */
/*       language: C++                                                    */
/*           Task: import csv file into vectors of strings                */
/**************************************************************************/
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

class CsvParser
{

public:
	CsvParser(char delimiter);
	~CsvParser();
	int OpenFile(std::string filename);
	int CloseFile();
	bool CsvGetNextRow(std::vector<std::string>& curRow);

protected:
	bool CsvGetNextColumn(char* out, size_t maxOutSize, bool* newRow = NULL, bool* overLength = NULL);
	char CsvGetNextByte();

	std::ifstream inputfile;

	// csv parser
	bool isEOF;
	int  lineCount;
	int  lastAvailableByte;
	char csvDelimiter;
	char currByte;
};

// implementation
CsvParser::CsvParser(char delimiter)
{
    csvDelimiter = delimiter;
}

CsvParser::~CsvParser()
{

}

int CsvParser::OpenFile(std::string filename)
{
    inputfile.open(filename.c_str(), std::ios_base::in);

    if (inputfile.fail())
    {
        return 1;
    }
    isEOF = false;
    lastAvailableByte = false;
    lineCount = 0;
    currByte = 0;

    return 0;
}

int CsvParser::CloseFile()
{
    inputfile.close();
    return 0;
}

bool CsvParser::CsvGetNextRow(std::vector<std::string>& curRow)
{
    const int CSV_MAX_COLUMN_SIZE = 8192;
    char currField[CSV_MAX_COLUMN_SIZE] = "";
    bool newLine = false;
    bool OverSize = false;

    curRow.clear();
    if (isEOF)
        return false;
    while (CsvGetNextColumn(currField, CSV_MAX_COLUMN_SIZE - 1, &newLine, &OverSize))
    {
        curRow.push_back(currField);
        if (newLine)
        {
            break;
        }
    }

    return true;
}

bool CsvParser::CsvGetNextColumn(char* currField, size_t maxOutSize, bool* newRow, bool* overLength)
{
    int fieldIter = 0;
    int inside_complex_field = 0;
    int currFieldCharIter = 0;
    int seriesOfQuotesLength = 0;
    int lastCharIsQuote = 0;
    int isEndOfFile = 0;
    int lastLenField = 0;
    bool overLengthMode = false;

    if (newRow != NULL)
        *newRow = false;
    if (overLength != NULL)
        *overLength = false;

    for (;;)
    {
        char currChar = CsvGetNextByte();
        if (isEOF)
        {
            // reached end of file or last row contains less than expected columns
            if (currFieldCharIter == 0 && fieldIter == 0)
            {
                return false;
            }
            //currChar = '\n';
            isEndOfFile = 1;
        }

        if (!isEndOfFile)
        {
            if (currChar == '\r')
            {
                continue;
            }
            if (currChar == '\"' && inside_complex_field == 0)
            {
                inside_complex_field = 1;
                lastCharIsQuote = 1;
                continue;
            }
            if (currChar == '\"' && inside_complex_field == 1 && lastCharIsQuote == 0 && currFieldCharIter == 0)
            {
                inside_complex_field = 0;
                currFieldCharIter++;
                lastCharIsQuote = 1;
                continue;
            }
            if (currFieldCharIter == 0 && !lastCharIsQuote)
            {
                if (currChar == '\"') {
                    inside_complex_field = 1;
                    lastCharIsQuote = 1;
                    continue;
                }
            }
            else if (currChar == '\"')
            {
                seriesOfQuotesLength++;
                inside_complex_field = (seriesOfQuotesLength % 2 == 0);
                if (inside_complex_field) {
                    currFieldCharIter--;
                }
            }
            else
            {
                seriesOfQuotesLength = 0;
            }
        }
        if (isEndOfFile || ((currChar == csvDelimiter || currChar == '\n') && !inside_complex_field))
        {
            if (lastCharIsQuote && currFieldCharIter > 0)
            {
                lastLenField = (currFieldCharIter - 1);
            }
            else
            {
                lastLenField = currFieldCharIter;
            }
            lastCharIsQuote = 0;
            currField[lastLenField] = '\0';
            //TrimStr(currField, lastLenField);

            if (currChar == '\n' || isEndOfFile)
            {
                lineCount++;
                if (newRow != NULL)
                {
                    *newRow = true;
                }
            }
            return true;
        }
        else
        {
            if (!overLengthMode)
            {
                currField[currFieldCharIter] = currChar;
                currFieldCharIter++;
                // column buffer full ?
                if (currFieldCharIter > maxOutSize - 1)
                {
                    if (overLength != NULL)
                    {
                        *overLength = true;
                        overLengthMode = true;
                        currField[currFieldCharIter] = 0; // we get only max size
                    }
                }
            }
        }
        lastCharIsQuote = (currChar == '\"') ? 1 : 0;
    }
}

char CsvParser::CsvGetNextByte()
{
    char gByte = 0;
    if (inputfile.is_open() && !isEOF)
    {
        inputfile.get(gByte);
        isEOF = inputfile.eof();
        lastAvailableByte = isEOF;
        return gByte;
    }
    return 0;
}