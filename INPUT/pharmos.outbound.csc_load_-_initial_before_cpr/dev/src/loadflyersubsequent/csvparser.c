#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <float.h>
#include <stdarg.h>

#include "csvparser.h"

#ifdef __cplusplus
extern "C" {
#endif

const char *CSV_NAME_COULMN_STATUS = "Status";
const char *CSV_COULMN_STATUS_OK = "OK";
const char *CSV_COULMN_STATUS_ERROR = "ERROR";
const char *CSV_NAME_COULMN_ERRORS = "Errors";
const char *CSV_ERRORS_DELIMITER = "\n";

CsvParser *CsvParser_Create(const char *filePath, char delimiter, CSvFieldFormat **csvStruct, char **columnsNames, int countColumns) {
    CsvParser *csvParser = NULL;
    CsvRow *headerRow = NULL;
    FILE *csvFILE = NULL;
    int i = 0;

    if ((csvParser = (CsvParser*)malloc(sizeof(CsvParser))) == NULL)
        return NULL;

    csvParser->countErrs = 0;
    csvParser->firstErrIdx = 0;
    csvParser->lineCount = 0;

    csvParser->fileHandler = NULL;
    csvParser->filePath = NULL;

    csvParser->headerRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
    csvParser->currentRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);

    csvParser->fileHandler = NULL;
    csvParser->filePath = NULL;
    csvParser->keys = (CsvKey**) malloc(sizeof(CsvKey*) * CSV_MAX_KEYS_COUNT);
    csvParser->errors = (CsvError*) malloc(sizeof(CsvError) * CSV_MAX_STORED_ERRS);
    csvParser->errors[0].errMsg = NULL;
    csvParser->errors[0].lineErr = 0;
    csvParser->countErrs = 0;
    csvParser->firstErrIdx = 0;

    csvParser->delimiter = 0;

    csvParser->isEndOfFile = 0;
    csvParser->availableBytes = 0;
    csvParser->currentByteIter = 0;
    csvParser->lastAvailableByte = 0;
    csvParser->lineCount = 1;

    if (filePath == NULL) {
        CsvParser_setErrorMessage(csvParser, 0, CSVERR_FILENAME_NULL_PTR, "Supplied CSV file path is NULL");
        return csvParser;
    }

    if (!_CsvParser_delimiterIsAccepted(delimiter)) {
        CsvParser_setErrorMessage(csvParser, 0, CSVERR_NOT_SUPPORTED_DELIMITER, "Supplied delimiter '%c' is not supported", delimiter);
        return csvParser;
    }
    csvParser->delimiter = delimiter;

    if ((csvFILE = fopen(filePath, "r")) == NULL) {
        int errorNum = errno;
        const char *errStr = strerror(errorNum);
        CsvParser_setErrorMessage(csvParser,  0, CSVERR_FAILED_OPEN_CSV_FILE, "Error opening '%s' CSV file for reading: '%s'", filePath, errStr);
        return csvParser;
    }

    csvParser->fileHandler = csvFILE;
    csvParser->filePath = _CsvParser_duplicate(filePath, 0, 0);

    // enable checking if columns count > 0
    csvParser->csvStruct = NULL;
    csvParser->columnsNames = NULL;
    csvParser->csvStructCountElements = 0;
    if (countColumns > 0) {
        if (csvStruct != NULL) {
            csvParser->csvStruct = csvStruct;
        }
        if (columnsNames != NULL) {
            csvParser->columnsNames = columnsNames;
        }
        if ((csvStruct != NULL) || (columnsNames != NULL)) {
            csvParser->csvStructCountElements = countColumns;
        }
    }

    // get header columns
    headerRow = CsvParser_getNextRow(csvParser, 1);
    // header parsed correctly ?
    if (headerRow != NULL) {
        if (csvParser->csvStructCountElements > 0) {
            // check columns count ?
            if (csvParser->headerRow->numOfFields != csvParser->csvStructCountElements) {
                csvParser->lineCount = 1;
                CsvParser_setErrorMessage(csvParser, 0, CSVERR_HEADER_WRONG_COLUMNS_COUNT, "Wrong header columns count: expecting %i, found %i column(s)", csvParser->csvStructCountElements, csvParser->headerRow->numOfFields);
            }
            // check columns names
            if (csvParser->columnsNames != NULL) { // expected columns names provided ?
                for (i = 0; i < csvParser->csvStructCountElements && i < csvParser->headerRow->numOfFields; i++) {
                    if (strcmp(csvParser->columnsNames[i], csvParser->headerRow->fields[i]) != 0) {
                        csvParser->lineCount = 1;
                        CsvParser_setErrorMessage(csvParser, 0, CSVERR_HEADER_WRONG_COLUMN_NAME, "Wrong header column[%i] name: expecting '%s', found '%s'", i, csvParser->columnsNames[i], csvParser->headerRow->fields[i]);
                    }
                }
            }
        }
    }

    // by default no key
    csvParser->countKeys = 0;
    csvParser->keyIndexesCount = 0;

    // Finish the csvParser if any error occured
    if (csvParser->countErrs > 0) {
        if (csvParser->fileHandler != NULL) {
            fclose(csvParser->fileHandler);
            csvParser->fileHandler = NULL;
        }
    }

    return csvParser;
}

void CsvParser_EnableKey(CsvParser *csvParser, int *keyIndexes, int countKeys) {
    int i = 0;
    char delim[2] = { '\0', '\0' };

    // free any existing key data and reset counters
    for (i = 0; i < csvParser->countKeys; i++) {
        CSV_SAFE_FREE(csvParser->keys[i]);
    }
    csvParser->countKeys = 0;
    csvParser->keyIndexesCount = 0;

    // insert the new key if valid
    if (countKeys > 0 && keyIndexes != NULL && csvParser->headerRow->numOfFields > 0 && CsvParser_isFinished(csvParser) == 0) {
        delim[0] = csvParser->delimiter;
        if (countKeys <= CSV_MAX_KEYS_COUNT) {
            // check column indexes
            for (i = 0; i < countKeys; i++) {
                if (keyIndexes[i] >= csvParser->headerRow->numOfFields) {
                    CsvParser_setErrorMessage(csvParser, 0, CSVERR_KEY_INVALID_COLUMN_INDEX,
                        "Invalid Key index %i, value[%i] should be less than [%i]", i, keyIndexes[i], csvParser->headerRow->numOfFields);
                    return;
                }
                if (i == 0) {
                    strcpy(csvParser->keyName, csvParser->headerRow->fields[keyIndexes[i]]);
                } else {
                    strcat(csvParser->keyName, csvParser->headerRow->fields[keyIndexes[i]]);
                }
                // adds delimiter if there is more names
                if (countKeys > 1 && (i + 1) < countKeys) {
                    strcat(csvParser->keyName, delim);
                }
            }
            // copy indexes and reset counters
            memcpy(csvParser->keyIndexes, keyIndexes, sizeof(int) * countKeys);
            csvParser->keyIndexesCount = countKeys;
        } else {
            CsvParser_setErrorMessage(csvParser, 0, CSVERR_KEY_CROSSED_MAXIMUM_COLUMNS_COUNT,
                "Key indexes crossed maximum allocated count [%i]", countKeys);
        }
    } else {
            CsvParser_setErrorMessage(csvParser, 0,
                CSVERR_KEY_INVALID_COLUMNS_COUNT_OR_PTR, "Invalid keys index count or indexes pointer");
    }
}

void CsvParser_Destroy(CsvParser *csvParser) {
    int i = 0;
    int errIdx = 0;

    if (csvParser == NULL) {
        return;
    }
    CSV_SAFE_FREE(csvParser->filePath);

    for (i = 0; i < csvParser->countErrs; i++) {
        errIdx = (csvParser->firstErrIdx + i) % CSV_MAX_STORED_ERRS;
        CSV_SAFE_FREE(csvParser->errors[errIdx].errMsg);
    }
    CSV_SAFE_FREE(csvParser->errors);

    if (csvParser->fileHandler != NULL) {
        fclose(csvParser->fileHandler);
        csvParser->fileHandler = NULL;
    }
    if (csvParser->headerRow != NULL) {
        CsvRow_destroy(csvParser->headerRow);
    }
    if (csvParser->currentRow != NULL) {
        CsvRow_destroy(csvParser->currentRow);
    }
    if (csvParser->countKeys > 0) {
        for (i = 0; i < csvParser->countKeys; i++) {
            CSV_SAFE_FREE(csvParser->keys[i]->keyValue);
            CSV_SAFE_FREE(csvParser->keys[i]);
        }
    }
    CSV_SAFE_FREE(csvParser->keys);
    CSV_SAFE_FREE(csvParser);
}

CsvRow *CsvParser_getNextRow(CsvParser *csvParser, int getHeader) {

    if (csvParser == NULL) {
        return NULL;
    }
    // reset number of fields
    csvParser->currentRow->numOfFields = 0;
    int fieldIter = 0;
    //char *currField = (char*)malloc(acceptedCharsInField);
    int inside_complex_field = 0;
    int currFieldCharIter = 0;
    int seriesOfQuotesLength = 0;
    int lastCharIsQuote = 0;
    int isEndOfFile = 0;
    int lastLenField = 0;
    CsvRow *csvRow = NULL;

    if (getHeader == 1) {
        csvRow = csvParser->headerRow;
    } else {
        csvRow = csvParser->currentRow;
    }
    csvRow->numOfFields = 0;

    for (;;) {
        char currChar = _GetNextByte(csvParser);
        if (CsvParser_isFinished(csvParser) == 1) {
            // reached end of file or last row contains less than expected columns
            if (currFieldCharIter == 0 && fieldIter == 0) {
                CsvParser_setErrorMessage(csvParser, 0, CSVERR_REACHED_EOF, "Reached EOF");
                return NULL;
           }
            //currChar = '\n';
            isEndOfFile = 1;
        }

        if (!isEndOfFile) {
            if (currChar == '\r') {
                continue;
            }
            if (currChar == '\"' && inside_complex_field == 0) {
                inside_complex_field = 1;
                lastCharIsQuote = 1;
                continue;
            }
            if (currChar == '\"' && inside_complex_field == 1 && lastCharIsQuote == 0 && currFieldCharIter ==0) {
                inside_complex_field = 0;
                currFieldCharIter++;
                lastCharIsQuote = 1;
                continue;
            }
            if (currFieldCharIter == 0  && !lastCharIsQuote) {
                if (currChar == '\"') {
                    inside_complex_field = 1;
                    lastCharIsQuote = 1;
                    continue;
                }
            } else if (currChar == '\"') {
                seriesOfQuotesLength++;
                inside_complex_field = (seriesOfQuotesLength % 2 == 0);
                if (inside_complex_field) {
                    currFieldCharIter--;
                }
            } else {
                seriesOfQuotesLength = 0;
            }
        }
        if (isEndOfFile || ((currChar == csvParser->delimiter || currChar == '\n') && !inside_complex_field) ) {
            if (getHeader == 1 && csvRow->numOfFields==CSVFORMAT_MAX_COLUMN_COUNT) {
                CsvParser_setErrorMessage(csvParser, 0, CSVERR_HEADER_CROSSED_MAX_COLUMNS_COUNT, "header crossed maximum allocated columns count");
                csvParser->lineCount++;
                return NULL;
            }
            if (lastCharIsQuote && currFieldCharIter >0) {
                lastLenField = (currFieldCharIter - 1);
            }
            else {
                lastLenField = currFieldCharIter;
            }
            lastCharIsQuote = 0;
            csvParser->currField[lastLenField] = '\0';
            csvRow->fields[fieldIter] = _CsvParser_duplicate(csvParser->currField, lastLenField, 1);
            csvRow->numOfFields++;
            if (currChar == '\n' || isEndOfFile) {
                if (getHeader == 1) {
                    csvParser->lineCount++;
                    return csvRow;
                } else {
                    if (csvRow->numOfFields == csvParser->headerRow->numOfFields) {
                        _CsvParser_validateStruct(csvParser, csvRow);
                        _CsvParser_validateKey(csvParser, csvRow);
                        csvParser->lineCount++;
                        return CsvRow_duplicate(csvRow);
                    } else if (csvRow->numOfFields < csvParser->headerRow->numOfFields) {
                        CsvParser_setErrorMessage(csvParser, 0, CSVERR_ROW_INSUFFICIENT_COLUMNS_COUNT, "insufficient columns count: expected '%i', found '%i'",
                                                  csvParser->headerRow->numOfFields, csvRow->numOfFields);
                        csvParser->lineCount++;
                        return CsvRow_duplicate(csvRow);
                    } else {
                        CsvParser_setErrorMessage(csvParser, 0, CSVERR_ROW_CROSSED_EXPECTED_COLUMNS_COUNT, "crossed count of expected columns: expected '%i', found '%i'",
                                                  csvParser->headerRow->numOfFields, csvRow->numOfFields);
                        csvParser->lineCount++;
                        return CsvRow_duplicate(csvRow);
                    }
                }
            }

            if (csvRow->numOfFields > csvParser->headerRow->numOfFields) {
                CsvParser_setErrorMessage(csvParser, 0, CSVERR_ROW_CROSSED_EXPECTED_COLUMNS_COUNT, "crossed count of expected columns: expected '%i', found '%i'",
                                                  csvParser->headerRow->numOfFields, csvRow->numOfFields);
                _gotoNextLine(csvParser);
                csvParser->lineCount++;
                return CsvRow_duplicate(csvRow);
            }
            currFieldCharIter = 0;
            fieldIter++;
            inside_complex_field = 0;
        } else {
            csvParser->currField[currFieldCharIter] = currChar;
            currFieldCharIter++;
            // column buffer full ?
            if (currFieldCharIter > CSVFORMAT_MAX_COLUMN_SIZE-1) {
                CsvParser_setErrorMessage(csvParser, 0, CSVERR_ROW_CROSSED_MAXIMUM_COLUMN_SIZE, "crossed maximum allocated columns size");
                csvParser->lineCount++;
                return CsvRow_duplicate(csvRow);
            }
        }
        lastCharIsQuote = (currChar == '\"') ? 1 : 0;
    }
}

int CsvParser_isFinished(CsvParser *csvParser) {
    if ((csvParser->isEndOfFile && csvParser->availableBytes == 0 && csvParser->lastAvailableByte == 0) || csvParser->fileHandler == NULL) {
        return 1;
    }
    return 0;
}

char * CsvParser_getErrorMessage(CsvParser *csvParser, int *errID, int *lineErr) {
    char *errMsg = NULL;
    if (csvParser->countErrs > 0) {
        errMsg = csvParser->errors[csvParser->firstErrIdx].errMsg;
        if (errID != NULL) {
            *errID = csvParser->errors[csvParser->firstErrIdx].errID;
        }
        if (lineErr != NULL) {
            *lineErr = csvParser->errors[csvParser->firstErrIdx].lineErr;
        }
        csvParser->firstErrIdx = (csvParser->firstErrIdx + 1) % CSV_MAX_STORED_ERRS;
        csvParser->countErrs --;
    }
    return errMsg;
}

int CsvParser_getLastErrorID(CsvParser *csvParser) {
    if (csvParser->countErrs > 0) {
        return csvParser->errors[csvParser->firstErrIdx].errID;
    }
    return CSVERR_NO_ERROR;
}

char *CsvParser_getLastErrorMessage(CsvParser *csvParser) {
    if (csvParser->countErrs > 0) {
        return csvParser->errors[csvParser->firstErrIdx].errMsg;
    }
    return NULL;
}


void CsvParser_setErrorMessage(CsvParser *csvParser, int deltaLine, int errID, const char *errorMessageFormat, ...) {
    va_list arg_ptr;
    char tmpErr[4096] = "";
    int indexNewErr = (csvParser->firstErrIdx + csvParser->countErrs) % CSV_MAX_STORED_ERRS;

    // ring buffer of errors saturated ?
    if (csvParser->countErrs >= CSV_MAX_STORED_ERRS) {
        return;
    }
    va_start(arg_ptr, errorMessageFormat);

    if (csvParser->errors[indexNewErr].errMsg != NULL) {
        CSV_SAFE_FREE(csvParser->errors[indexNewErr].errMsg);
    }
    vsprintf(tmpErr, errorMessageFormat, arg_ptr);
    csvParser->errors[indexNewErr].errMsg = _CsvParser_duplicate(tmpErr, 0, 0);
    csvParser->errors[indexNewErr].lineErr = csvParser->lineCount + deltaLine;
    csvParser->errors[indexNewErr].errID = errID;

    va_end(arg_ptr);
    csvParser->countErrs++;
}

int CsvParser_getCurRowErrorsCount(CsvParser *csvParser) {
    int errCount = 0;
    int errIdx = 0;
    int i = 0;
    int currLine = csvParser->lineCount - 1;

    if (csvParser->countErrs > 0) {
        for (i = csvParser->countErrs - 1; i >= 0; i--) {
            errIdx = (csvParser->firstErrIdx + i) % CSV_MAX_STORED_ERRS;
            if (csvParser->errors[errIdx].lineErr > currLine)
                continue;
            if (csvParser->errors[errIdx].lineErr < currLine)
                break;
            errCount ++;
        }
    }
    return errCount;
}

void CsvParser_fwriteHeaderWithErrorsColumns(CsvParser *csvParser, FILE *csvFILE) {
    if (csvParser == NULL || csvFILE == NULL || csvParser->headerRow->numOfFields <= 0 ||
        csvParser->lineCount <= 1) {
        return;
    }
    size_t sizeTmp = sizeof(char) * (csvParser->headerRow->numOfFields+2) * CSVFORMAT_MAX_COLUMN_SIZE * 2;
    char *tmpRow = (char*)malloc(sizeTmp);
    int rowIter = 0;
    int fieldLen = 0;
    int i = 0, j = 0;

    if (tmpRow == NULL) {
        return;
    }
    // create the new header row with status & errors columns
    for (i = 0; i < csvParser->headerRow->numOfFields+2; i++) {
        // merge the field on the new row
        if (i < csvParser->headerRow->numOfFields) {
            tmpRow[rowIter] = '"';
            rowIter++;
            fieldLen = strlen(csvParser->headerRow->fields[i]);
            for (j = 0; j < fieldLen; j++) {
                tmpRow[rowIter] = csvParser->headerRow->fields[i][j];
                rowIter++;
                if (tmpRow[rowIter-1] == '"') {
                    tmpRow[rowIter] = '"';
                    rowIter++;
                }
            }

            tmpRow[rowIter] = '"';
            rowIter++;
            tmpRow[rowIter] = csvParser->delimiter;
            rowIter++;
        } else if (i == csvParser->headerRow->numOfFields) { // status column
            fieldLen = strlen(CSV_NAME_COULMN_STATUS);
            tmpRow[rowIter] = '"';
            rowIter ++;
            strncpy(&tmpRow[rowIter], CSV_NAME_COULMN_STATUS, fieldLen);
            rowIter += fieldLen;
            tmpRow[rowIter] = '"';
            rowIter ++;
            tmpRow[rowIter] = csvParser->delimiter;
            rowIter++;
        } else if (i == csvParser->headerRow->numOfFields + 1) { // errors column
            fieldLen = strlen(CSV_NAME_COULMN_ERRORS);
            tmpRow[rowIter] = '"';
            rowIter ++;
            strncpy(&tmpRow[rowIter], CSV_NAME_COULMN_ERRORS, fieldLen);
            rowIter += fieldLen;
            tmpRow[rowIter] = '"';
            rowIter ++;
        }
    }
    tmpRow[rowIter] = '\n';
    rowIter++;
    fwrite(tmpRow, rowIter, 1, csvFILE);


    CSV_SAFE_FREE(tmpRow);
}

void CsvParser_fwriteCurRowWithErrors(CsvParser *csvParser, FILE *csvFILE) {
    if (csvParser == NULL || csvFILE == NULL || csvParser->currentRow->numOfFields <= 0 ||
        csvParser->lineCount <= 2 || csvParser->headerRow->numOfFields <= 0) {
        return;
    }
    size_t sizeTmp = sizeof(char) * (csvParser->headerRow->numOfFields+2) * CSVFORMAT_MAX_COLUMN_SIZE * 2;
    char *tmpRow = (char*)malloc(sizeTmp);
    int currLine = csvParser->lineCount - 1; // should be two or more for data rows
    int i = 0, j = 0, k = 0;
    int rowIter = 0;
    int errCount = 0;
    int lastErrIdx = 0;
    int errIdx = 0;
    int fieldLen = 0;
    int errDelimLen = strlen(CSV_ERRORS_DELIMITER);

    if (tmpRow == NULL) {
        return;
    }
    // count number of line errors without modifying errors ring buffer
    if (csvParser->countErrs > 0) {
        for (i = csvParser->countErrs - 1; i >= 0; i--) {
            errIdx = (csvParser->firstErrIdx + i) % CSV_MAX_STORED_ERRS;
            if (csvParser->errors[errIdx].lineErr > currLine)
                continue;
            if (csvParser->errors[errIdx].lineErr < currLine)
                break;
            if (errCount == 0) {
                lastErrIdx = errIdx;
            }
            errCount ++;
        }
    }
    // create the new row with status & errors columns
    for (i = 0; i < csvParser->headerRow->numOfFields+2; i++) {
        // merge the field on the new row
        if (i < csvParser->currentRow->numOfFields && i < csvParser->headerRow->numOfFields) {
            tmpRow[rowIter] = '"';
            rowIter++;
            fieldLen = strlen(csvParser->currentRow->fields[i]);
            for (j = 0; j < fieldLen; j++) {
                tmpRow[rowIter] = csvParser->currentRow->fields[i][j];
                rowIter++;
                if (tmpRow[rowIter-1] == '"') {
                    tmpRow[rowIter] = '"';
                    rowIter++;
                }
            }

            tmpRow[rowIter] = '"';
            rowIter++;
            tmpRow[rowIter] = csvParser->delimiter;
            rowIter++;

        } else if (i < csvParser->headerRow->numOfFields) { // happen if not enough columns in curRow
            tmpRow[rowIter] = csvParser->delimiter;
            rowIter++;
        } else if (i == csvParser->headerRow->numOfFields) { // status column
            if (errCount == 0) { // no errors: OK
                fieldLen = strlen(CSV_COULMN_STATUS_OK);
                strncpy(&tmpRow[rowIter], CSV_COULMN_STATUS_OK, fieldLen);
                rowIter += fieldLen;
                tmpRow[rowIter] = csvParser->delimiter;
                rowIter++;
            } else { // error
                fieldLen = strlen(CSV_COULMN_STATUS_ERROR);
                strncpy(&tmpRow[rowIter], CSV_COULMN_STATUS_ERROR, fieldLen);
                rowIter += fieldLen;
                tmpRow[rowIter] = csvParser->delimiter;
                rowIter++;
            }
        } else if (i == csvParser->headerRow->numOfFields + 1) { // errors column
            if (errCount > 0) { // add errors
                tmpRow[rowIter] = '"';
                rowIter++;
                for (j = errCount -1; j >= 0; j--) {
                    errIdx = (lastErrIdx - j) % CSV_MAX_STORED_ERRS;
                    fieldLen = strlen(csvParser->errors[errIdx].errMsg);
                    for (k = 0; k < fieldLen; k++) {
                        tmpRow[rowIter] = csvParser->errors[errIdx].errMsg[k];
                        rowIter++;
                        if (tmpRow[rowIter-1] == '"') {
                            tmpRow[rowIter] = '"';
                            rowIter++;
                        }
                    }
                    // add errors delimiter
                    if (j > 0) {
                        strncpy(&tmpRow[rowIter], CSV_ERRORS_DELIMITER, errDelimLen);
                        rowIter += errDelimLen;
                    }
                }
                tmpRow[rowIter] = '"';
                rowIter++;
            }
        }
    }
    tmpRow[rowIter] = '\n';
    rowIter++;
    fwrite(tmpRow, rowIter, 1, csvFILE);

    CSV_SAFE_FREE(tmpRow);
}

// CsvRow

CsvRow *CsvRow_Create(int numOfFields, size_t maxColumnSize) {
    CsvRow *newRow = (CsvRow*)malloc(sizeof(CsvRow));
    int i = 0;

    if (newRow != NULL) {
        newRow->fields = (char**)malloc(sizeof(char*)*numOfFields);
        newRow->numOfFields = 0;
        if (newRow->fields != NULL) {
            newRow->numOfAllocatedFields = numOfFields;
            for (i = 0 ; i < numOfFields ; i++) {
                newRow->fields[i] = (char*)malloc(maxColumnSize);
            }
        } else {
            newRow->numOfAllocatedFields = 0;
        }
    }
    return newRow;
}

void CsvRow_destroy(CsvRow *csvRow) {
    int i;
    if (csvRow == NULL) {
        return;
    }
    if (csvRow->fields != NULL) {
        for (i = 0 ; i < csvRow->numOfAllocatedFields ; i++) {
            CSV_SAFE_FREE(csvRow->fields[i]);
        }
        CSV_SAFE_FREE(csvRow->fields);
    }
    CSV_SAFE_FREE(csvRow);
}


CsvRow * CsvRow_duplicate(CsvRow *csvRow) {
    int i;
    CsvRow *dupRow = (CsvRow*)malloc(sizeof(CsvRow));
    if (dupRow != NULL) {
        dupRow->fields = (char**)malloc(sizeof(char*)*csvRow->numOfFields);
        if (dupRow->fields != NULL) {
            dupRow->numOfFields = csvRow->numOfFields;
            dupRow->numOfAllocatedFields = csvRow->numOfFields;
            for (i = 0 ; i < csvRow->numOfFields ; i++) {
                dupRow->fields[i] = _CsvParser_duplicate(csvRow->fields[i], 0, 0);
            }
        } else {
            dupRow->numOfFields = 0;
            dupRow->numOfAllocatedFields = 0;
        }
    }
    return dupRow;
}


// private CsvParser

void _CsvParser_validateStruct(CsvParser *csvParser, CsvRow *csvRow) {
    int i = 0;

    if (csvParser->csvStructCountElements > 0 && csvParser->csvStruct != NULL) {
        for (i = 0; i < csvParser->csvStructCountElements && i < csvRow->numOfFields; i++) {
            if (csvParser->csvStruct[i]->validateStr(csvRow->fields[i]) != CSVFORMAT_OK) {
                if (csvParser->columnsNames != NULL) {
                    CsvParser_setErrorMessage(csvParser, 0, CSVERR_ROW_FAILED_TO_VALIDATE_COLUMN, "Failed to validate column[%s] with Format[%s], current value '%s'",
                                              csvParser->columnsNames[i], csvParser->csvStruct[i]->formatName, csvRow->fields[i]);
                } else {
                    CsvParser_setErrorMessage(csvParser, 0, CSVERR_ROW_FAILED_TO_VALIDATE_COLUMN, "Failed to validate column number[%i] with Format[%s], current value '%s'",
                                              i, csvParser->csvStruct[i]->formatName, csvRow->fields[i]);
                }
            }
        }
    }
}

int _CsvParser_validateKey(CsvParser *csvParser, CsvRow *csvRow) {
    char *key = NULL;
    if (csvParser->keyIndexesCount > 0) {
        if ((key = _CsvParser_buildKey(csvParser, csvRow, NULL)) == NULL) {
            return 1; // fail build the key
        }
        if (_CsvParser_KeyExist(csvParser, key) == 0) {
            // rebuild key with delimiter for better error reading
            free(key);
            if ((key = _CsvParser_buildKey(csvParser, csvRow, CSV_DUPLICATE_KEY_DELIM)) != NULL) {
                CsvParser_setErrorMessage(csvParser, 0, CSVERR_KEY_DUPLICATED,
                    "Duplicated Key [%s] value [%s] defined on line %i", csvParser->keyName, key, csvParser->lastLineFoundKey);
                free(key);
            } else {
                CsvParser_setErrorMessage(csvParser, 0, CSVERR_KEY_DUPLICATED, "Duplicated Key [%s] defined on line %i", csvParser->keyName, csvParser->lastLineFoundKey);
            }
            return 2;
        }
        _CsvParser_insertKey(csvParser, key);
    }
    return 0; // success
}

char * _CsvParser_buildKey(CsvParser *csvParser, CsvRow *csvRow, char *columnsDelim) {
    int i = 0;
    int keyLength = 0;
    int idx = 0;
    int fieldLen = 0;
    int delimLen = 0;

    if (columnsDelim != NULL) {
        delimLen = strlen(columnsDelim);
    }
    for (i = 0; i < csvParser->keyIndexesCount; i++) {
        idx = csvParser->keyIndexes[i];
        if (csvRow->numOfFields > idx && csvRow->fields[idx] != NULL) {
            fieldLen = strlen(csvRow->fields[idx]);
            if ((keyLength + fieldLen) < CSV_MAX_KEY_SIZE) {
                if (i == 0) {
                    strcpy(csvParser->curKey, csvRow->fields[idx]);
                } else {
                    strcat(csvParser->curKey, csvRow->fields[idx]);
                }
                if (columnsDelim != NULL && i < csvParser->keyIndexesCount - 1) {
                   strcat(csvParser->curKey, columnsDelim);
                   keyLength += delimLen;
                }
                keyLength += fieldLen;
            } else {
                CsvParser_setErrorMessage(csvParser, 0, CSVERR_KEY_CROSSED_MAXIMUM_ALLOCATED_SIZE, "Key crossed maximum allocated size");
                return NULL;
            }
        } else {
            CsvParser_setErrorMessage(csvParser, 0, CSVERR_KEY_FAILED_TO_BUILD_KEY, "Failed to build key");
            return NULL;
        }
    }
    return _CsvParser_duplicate(csvParser->curKey, keyLength, 0);
}

int _strCmpfunc (const void * a, const void * b) {
    const CsvKey* s1 = *(const CsvKey**) a;
    const CsvKey* s2 = *(const CsvKey**) b;

    return strcmp(s1->keyValue, s2->keyValue );
}

// just insert without verification of length or existence
void _CsvParser_insertKey(CsvParser *csvParser, char *key) {
    if (key != NULL) {
        if (csvParser->countKeys < CSV_MAX_KEYS_COUNT) {
            CsvKey *newKey = (CsvKey*)malloc(sizeof(CsvKey));
            if (newKey != NULL) {
                newKey->keyValue = key;
                newKey->lineOcc = csvParser->lineCount;
                csvParser->keys[csvParser->countKeys] = newKey; // insert new key on the last position
                csvParser->countKeys++;
                // sort new list to put the new key on the right position
                if (csvParser->countKeys > 1) {
                    qsort(csvParser->keys, csvParser->countKeys, sizeof(CsvKey*), _strCmpfunc);
                }
            } else {
                // out of memory !
            }
        } else {
            CsvParser_setErrorMessage(csvParser, 0, CSVERR_KEY_CROSSED_MAXIMUM_KEYS_COUNT, "Crossed maximum keys count");
        }
    }
}

int _CsvParser_KeyExist(CsvParser *csvParser, char *key) {
    CsvKey **foundKey = NULL;
    CsvKey searchKey;
    CsvKey *keyPtr = &searchKey;
    searchKey.lineOcc = -1;
    searchKey.keyValue = key;

    csvParser->lastLineFoundKey = -1;

    if (key != NULL && csvParser->countKeys > 0) {
        if(csvParser->countKeys > 1) {
            foundKey = (CsvKey **)bsearch(&keyPtr, csvParser->keys, csvParser->countKeys, sizeof(char*), _strCmpfunc);
        } else {
            if (strcmp(key, csvParser->keys[0]->keyValue) == 0) {
                foundKey = &csvParser->keys[0];
            }
        }
        if (foundKey != NULL) {
            csvParser->lastLineFoundKey = (*foundKey)->lineOcc;
            return 0;
        } else {
            return 1;
        }
    }
    return -1;
}

int _CsvParser_delimiterIsAccepted(char delimiter) {
    if (delimiter == '\n' || delimiter == '\r' || delimiter == '\0' || delimiter == '\"') {
        return 0;
    }
    return 1;
}

void _gotoNextLine(CsvParser *csvParser) {
    while (csvParser->currByte != '\n') {
        _GetNextByte(csvParser);
        if(csvParser->availableBytes == 0 && csvParser->lastAvailableByte ==0) {
            break;
        }
    }
}

void _ReadNextBuff(CsvParser *csvParser) {
    if (csvParser->fileHandler == NULL || csvParser->isEndOfFile || csvParser->availableBytes > 0)
        return;
    csvParser->availableBytes = fread(csvParser->CSVReadBuff, 1, CSVBUFFER_LENGTH, csvParser->fileHandler);
    if (feof(csvParser->fileHandler) || csvParser->availableBytes ==0) {
        csvParser->isEndOfFile = 1;
    }
    csvParser->currentByteIter = 0;
}

char _GetNextByte(CsvParser *csvParser) {
    char cret = 0;

    csvParser->lastAvailableByte = 0; // reset value for each byte to get

    if (csvParser->availableBytes == 0 && csvParser->isEndOfFile == 0) {
        _ReadNextBuff(csvParser);
    }
    if (csvParser->availableBytes > 0) {
        cret = csvParser->CSVReadBuff[csvParser->currentByteIter];
        csvParser->currentByteIter ++;
        csvParser->availableBytes --;
        if (csvParser->availableBytes == 0) {
            csvParser->lastAvailableByte = 1;
        }
    }
    csvParser->currByte = cret;
    return cret;
}

char * _CsvParser_duplicate(const char *str, size_t len, int trim) {
    size_t duplen = 0;
    char *dupstr = NULL;
    const char *ptrCpy = str;

    if (str == NULL) {
        return NULL;
    }
    if (len == 0) {
        duplen = strlen(str);
    } else {
        duplen = len;
    }
    // TRIM string
    if (trim) {
        // jump starting white spaces
        while(duplen>0 && isspace(*ptrCpy)) {
            ptrCpy++;
            duplen--;
        }
        // count endian white spaces
        while(duplen>0 && isspace(ptrCpy[duplen-1])) {
            duplen--;
        }
    }

    if ((dupstr = (char*)malloc(duplen + 1)) != NULL) {
        strncpy(dupstr, ptrCpy, duplen);
        dupstr[duplen] = 0;
    }
    return dupstr;
}

// GENERIC Format verification *****************************************************************************

CSvFieldFormat CSvFormat_any = { "ANY", VerifPtrSize };
CSvFieldFormat CSvFormat_int32 = { "INT32", VerifIsInteger32 };
CSvFieldFormat CSvFormat_float = { "FLOAT", VerifIsFloat };
CSvFieldFormat CSvFormat_double = { "DOUBLE", VerifIsDouble };
CSvFieldFormat CSvFormat_date = { "DATE", VerifIsDate };
CSvFieldFormat CSvFormat_Name = { "NAME", VerifPtrSize }; // todo
CSvFieldFormat CSvFormat_time = { "TIME", VerifPtrSize }; // todo
CSvFieldFormat CSvFormat_NumericString = { "NumericString", VerifIsNumericString };

size_t lastCSVStrLen;
char lastCSVStr[CSVFORMAT_MAX_COLUMN_SIZE];

// By default char *[str] is trimmed from spaces at start/end and copied to char *[lastCSVStr], final trimmed string length stored in [lastCSVStrLen]
int VerifPtrSize(char *str) {
    char *ptrCpy = str;

    if (str == NULL) {
        return CSVFORMAT_BADPTR;
    }
    if ((lastCSVStrLen = strlen(str)) >= CSVFORMAT_MAX_COLUMN_SIZE) {
        return CSVFORMAT_INVALID_SIZE;
    }
    // TRIM string
    // jump starting white spaces
    while(lastCSVStrLen>0 && isspace(*ptrCpy)) {
        ptrCpy++;
        lastCSVStrLen--;
    }
    // count endian white spaces
    while(lastCSVStrLen>0 && isspace(ptrCpy[lastCSVStrLen-1])) {
        lastCSVStrLen--;
    }
    if (lastCSVStrLen > 0) {
        strncpy(lastCSVStr, ptrCpy, lastCSVStrLen);
        lastCSVStr[lastCSVStrLen] = '\0';
    }
    else {
        lastCSVStr[0] = '\0';
    }
    return CSVFORMAT_OK;
}

int VerifIsInteger32(char *str) {
    int rc = VerifPtrSize(str);
    if (rc != CSVFORMAT_OK) {
        return rc; // return error code
    }
    if (lastCSVStrLen == 0) {
        return CSVFORMAT_INVALID;
    }

    int64_t v = 0;
    int cpos = 0;
    int neg = 0;
    int i = 0, c = 0;

    if (lastCSVStr[0]=='-') {
        neg = 1;
        cpos++;
    } else if (lastCSVStr[0]=='+' ) {
        cpos++;
    }

    if (!isdigit((int)(lastCSVStr[cpos]))) {
        return CSVFORMAT_INVALID;
    }
    // jump any left zeros
    while( lastCSVStr[cpos]=='0' ) {
        cpos++;
    }
    // convert left numbers to integer
    for(i=0; cpos<(int)lastCSVStrLen; i++) {
        c = lastCSVStr[cpos] - '0';
        if ((i > 10) || (c < 0 || c > 9)) {
            return CSVFORMAT_INVALID;
        }
        v = v*10 + c;
        cpos++;
    }

    if( v-neg > 2147483647 ) {
        return CSVFORMAT_INVALID;
    }

    return CSVFORMAT_OK;
}

int VerifIsFloat(char *str) {
    int rc = VerifPtrSize(str);

    if (rc != CSVFORMAT_OK) {
        return rc; // return error code
    }
    if (lastCSVStrLen == 0) {
        return CSVFORMAT_INVALID;
    }

    char *endptr = NULL;
    double val;

    errno = 0;    /* reset errno to zero */
    val = strtod(lastCSVStr, &endptr);

    // multiple values or out of range or out of float range ? error
    if ((*endptr != '\0') || (errno == ERANGE && (val > FLT_MAX || val < -FLT_MAX)) || (errno != 0 && val == 0.0))
    {
        return CSVFORMAT_INVALID;
    }

    return CSVFORMAT_OK;
}

int VerifIsDouble(char *str) {
    int rc = VerifPtrSize(str);
    if (rc != CSVFORMAT_OK) {
        return rc; // return error code
    }
    if (lastCSVStrLen == 0) {
        return CSVFORMAT_INVALID;
    }

    char *endptr = NULL;
    double val;

    errno = 0;    /* reset errno to zero */
    val = strtod(lastCSVStr, &endptr);

    // multiple values or out of range or out of float range ? error
    if ((*endptr != '\0') || (errno == ERANGE && (val == HUGE_VAL || val == -HUGE_VAL)) || (errno != 0 && val == 0.0))
    {
        return CSVFORMAT_INVALID;
    }

    return CSVFORMAT_OK;
}

// verify DATE stored in integer with format YYYYMMDD
int VerifIsDate(char *str) {
    #define MAX_VALID_YR 9999
    #define MIN_VALID_YR 1900

    int rc = VerifPtrSize(str);
    int i = 0;
    if (rc != CSVFORMAT_OK) {
        return rc; // return error code
    }
    if (lastCSVStrLen != 8) {
        return CSVFORMAT_INVALID;
    }

    int valYear = 0;
    int valMonth = 0;
    int valDay = 0;

    // verify all 8 chars are digits
    for (i = 0; i < (int)lastCSVStrLen; i++) {
        if (!isdigit((int)(lastCSVStr[i]))) {
            return CSVFORMAT_INVALID;
        } else {
            lastCSVStr[i] -= '0'; // convert to number value
        }
    }

    // get values of year, month and day
    valYear = (int)(lastCSVStr[0]) * 1000 + (int)(lastCSVStr[1]) * 100 + (int)(lastCSVStr[2]) * 10 + (int)(lastCSVStr[3]);
    valMonth = (int)(lastCSVStr[4]) * 10 + (int)(lastCSVStr[5]);
    valDay = (int)(lastCSVStr[6]) * 10 + (int)(lastCSVStr[7]);

    // If year, month and day are not in given range
    if ((valYear > MAX_VALID_YR || valYear < MIN_VALID_YR) || (valMonth < 1 || valMonth > 12) || (valDay < 1 || valDay > 31)) {
        return CSVFORMAT_INVALID;
    }

    switch (valMonth) {
    case 2:
        // Handle February month with leap year
        if (((((valYear % 4 == 0) && (valYear % 100 != 0)) || (valYear % 400 == 0))) && (valDay > 28)) {
        return CSVFORMAT_INVALID;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        // Handle Months of April, June, Sept and Nov must have number of days less than or equal to 30.
        if (valDay > 30) {
        return CSVFORMAT_INVALID;
        }
        break;
    }

    return CSVFORMAT_OK;
}

int VerifIsNumericString(char *str) {
    int rc = VerifPtrSize(str);
    int i = 0;
    if (rc != CSVFORMAT_OK) {
        return rc; // return error code
    }
    // verify all chars are digits
    for (i = 0; i < (int)lastCSVStrLen; i++) {
        if (!isdigit((int)(lastCSVStr[i]))) {
            return CSVFORMAT_INVALID;
        }
    }
    return CSVFORMAT_OK;
}

#ifdef __cplusplus
}
#endif
