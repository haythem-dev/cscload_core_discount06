#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <float.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CSV_SAFE_FREE(p) if(p != NULL) { free(p); p = NULL; }

#define CSVBUFFER_LENGTH	                        4096
#define CSVFORMAT_MAX_COLUMN_SIZE                   1024
#define CSVFORMAT_MAX_COLUMN_COUNT                  1024
#define CSV_MAX_STORED_ERRS                         512000
#define CSV_MAX_KEYS_COUNT                          1024000
#define CSV_MAX_KEY_SIZE                            2048
#define CSV_DUPLICATE_KEY_DELIM                     ";"

// Validation functions possible ret
#define CSVFORMAT_OK                                0
#define CSVFORMAT_INVALID                           1
#define CSVFORMAT_BADPTR                            2
#define CSVFORMAT_INVALID_SIZE                      3

// Errors ID
#define CSVERR_NO_ERROR                             -1
#define CSVERR_INFO                                 0
#define CSVERR_FILENAME_NULL_PTR                    1
#define CSVERR_NOT_SUPPORTED_DELIMITER              2
#define CSVERR_FAILED_OPEN_CSV_FILE                 3
#define CSVERR_HEADER_WRONG_COLUMNS_COUNT           4
#define CSVERR_HEADER_WRONG_COLUMN_NAME             5
#define CSVERR_HEADER_CROSSED_MAX_COLUMNS_COUNT     6
#define CSVERR_REACHED_EOF                          7
#define CSVERR_ROW_INSUFFICIENT_COLUMNS_COUNT       8
#define CSVERR_ROW_CROSSED_EXPECTED_COLUMNS_COUNT   9
#define CSVERR_ROW_CROSSED_MAXIMUM_COLUMN_SIZE      10
#define CSVERR_ROW_FAILED_TO_VALIDATE_COLUMN        11
#define CSVERR_KEY_CROSSED_MAXIMUM_COLUMNS_COUNT    12
#define CSVERR_KEY_INVALID_COLUMNS_COUNT_OR_PTR     13
#define CSVERR_KEY_INVALID_COLUMN_INDEX             14
#define CSVERR_KEY_CROSSED_MAXIMUM_KEYS_COUNT       15
#define CSVERR_KEY_FAILED_TO_BUILD_KEY              16
#define CSVERR_KEY_CROSSED_MAXIMUM_ALLOCATED_SIZE   17
#define CSVERR_KEY_DUPLICATED                       18
#define CSVERR_UNKNOWN_MULTIROW_STRUCT_ID           19
#define CSVERR_MAX_ID                               19

// Write TO CSV with errors constants
extern const char *CSV_NAME_COULMN_STATUS;
extern const char *CSV_COULMN_STATUS_OK;
extern const char *CSV_COULMN_STATUS_ERROR;
extern const char *CSV_NAME_COULMN_ERRORS;
extern const char *CSV_ERRORS_DELIMITER;

extern size_t lastCSVStrLen;
extern char lastCSVStr[CSVFORMAT_MAX_COLUMN_SIZE];

typedef int (*formatValidateCallback)(char *str);

int VerifPtrSize(char *str);
int VerifIsInteger32(char *str);
int VerifIsFloat(char *str);
int VerifIsDouble(char *str);
int VerifIsDate(char *str); // verify DATE stored in integer with format YYYYMMDD
int VerifIsNumericString(char *str); // verify string containing only digits (except start or endian trimmed spaces)
//
typedef struct CSvFieldFormat {
    char formatName[256];
    formatValidateCallback validateStr;
} CSvFieldFormat;

extern CSvFieldFormat CSvFormat_any;  // accept any string: it should be non null string with length less than CSVFORMAT_MAX_COLUMN_SIZE
extern CSvFieldFormat CSvFormat_int32; // validate signed 32bits integer
extern CSvFieldFormat CSvFormat_float; // validate float
extern CSvFieldFormat CSvFormat_double; // validate double
extern CSvFieldFormat CSvFormat_date; // validate YYYYMMDD date
extern CSvFieldFormat CSvFormat_Name;
extern CSvFieldFormat CSvFormat_time;
extern CSvFieldFormat CSvFormat_NumericString; // string containing only digits except starting and endian spaces

// Public

typedef struct CsvRow {
    char **fields;
    int numOfFields;
    int numOfAllocatedFields;
} CsvRow;

typedef struct CsvError {
    char    *errMsg;
    int     lineErr;
    int     errID;
} CsvError;

typedef struct CsvKey {
    char    *keyValue;
    int     lineOcc;
} CsvKey;

typedef struct RowStruct {
    // csv struct format validation and columns names
    int                 countFields;
    CSvFieldFormat      **fieldsFormat;
} RowStruct;

typedef struct RowKey {
    // key / duplicates handling
    char                keyName[CSVFORMAT_MAX_COLUMN_SIZE];
    char                curKey[CSV_MAX_KEY_SIZE]; // current handled key
    int                 countKeys; // count of already parsed keys
    int                 lastLineFoundKey; // number of the line of last found key, -1 else
    int                 keyIndexes[CSVFORMAT_MAX_COLUMN_COUNT]; // index of columns that form the final key
    int                 keyIndexesCount; // count of columns indexes of the key
    CsvKey              **keys; // sorted list of already parsed keys
} RowKey;

typedef struct CsvParser {
    // csv file handling
    FILE                *fileHandler;
    char                *filePath;
    char                CSVReadBuff[CSVBUFFER_LENGTH];
    int                 isEndOfFile;
    int                 lineCount;
    int                 availableBytes;
    int                 currentByteIter;
    int                 lastAvailableByte;
    char                delimiter;
    char                currByte;
    // csv data
    char                currField[CSVFORMAT_MAX_COLUMN_SIZE];
    CsvRow              *headerRow;
    CsvRow              *currentRow;
    // errors management
    CsvError            *errors; // ring buffer of last errors
    int                 countErrs;
    int                 firstErrIdx;
    // csv struct format validation and columns names
    int                 csvStructCountElements;
    CSvFieldFormat      **csvStruct;
    char                **columnsNames;
    // key / duplicates handling
    CsvKey              **keys; // sorted list of already parsed keys
    char                curKey[CSV_MAX_KEY_SIZE]; // current handled key
    char                keyName[CSVFORMAT_MAX_COLUMN_SIZE]; // string containing names of key columns separated by current delimiter
    int                 countKeys; // count of already parsed keys
    int                 lastLineFoundKey; // number of the line of last found key, -1 else
    int                 keyIndexes[CSVFORMAT_MAX_COLUMN_COUNT]; // index of columns that form the final key
    int                 keyIndexesCount; // count of columns indexes of the key
    // Multi-Row struct
    bool                multiRowStructs;
    int                 countMutiRows;
    int                 curRowStructIdx; // index of struct of last parsed row, else -1 if unknown/unset
    char                **rowsID; // list of string char * of the identifier of each row (on first row column), couldn't be an empty string
    RowStruct           *rowsStruct;
    RowKey              **rowsKey;
    CsvRow              **defaultRowsValue; // CsvRows pointer with default value for each rowID
} CsvParser;

// CsvParser ///////////////////////////

// single row struct
CsvParser *CsvParser_Create(const char *filePath, char delimiter, CSvFieldFormat **csvStruct, char **columnsNames, int countColumns);
void CsvParser_EnableKey(CsvParser *csvParser, int *keyIndexes, int countKeys);
void CsvParser_Destroy(CsvParser *csvParser);
CsvRow *CsvParser_getNextRow(CsvParser *csvParser, int getHeader);
void CsvParser_fwriteHeaderWithErrorsColumns(CsvParser *csvParser, FILE *csvFILE);
void CsvParser_fwriteCurRowWithErrors(CsvParser *csvParser, FILE *csvFILE);
// multi-row structs
CsvParser *CsvParser_CreateMultiRows(const char *filePath, char delimiter, RowStruct *rowsStruct, char **RowdsID, int countRowsStruct);
void CsvParser_EnableKeyMultiRows(CsvParser *csvParser, int **keyIndexes, int *countKeys);
void CsvParser_SetDefaultRowMultiRows(CsvParser *csvParser, CsvRow **defaultRows);
void CsvParser_DestroyMultiRows(CsvParser *csvParser);
CsvRow *CsvParser_getNextRowMultiRows(CsvParser *csvParser);
// common
int CsvParser_isFinished(CsvParser *csvParser);
char *CsvParser_getErrorMessage(CsvParser *csvParser, int *errID, int *lineErr);
int CsvParser_getLastErrorID(CsvParser *csvParser);
char *CsvParser_getLastErrorMessage(CsvParser *csvParser);
void CsvParser_setErrorMessage(CsvParser *csvParser, int deltaLine, int errID, const char *errorMessageFormat, ...);
int CsvParser_getCurRowErrorsCount(CsvParser *csvParser);

// CsvRow ///////////////////////////////

CsvRow *CsvRow_Create(int numOfFields, size_t maxColumnSize);
void CsvRow_destroy(CsvRow *csvRow);
CsvRow *CsvRow_duplicate(CsvRow *csvRow);
void CsvRow_copy(CsvRow *dstCsvRow, CsvRow *srcCsvRow);
void CsvRow_ResetValues(CsvRow *csvRow, int countFields);
void CsvRow_setValues(CsvRow *csvRow, int countFields, char **Values);

// Private

void _CsvParser_validateStruct(CsvParser *csvParser, CsvRow *csvRow);
int _CsvParser_validateKey(CsvParser *csvParser, CsvRow *csvRow);
char * _CsvParser_buildKey(CsvParser *csvParser, CsvRow *csvRow, char *columnsDelim);
void _CsvParser_insertKey(CsvParser *csvParser, char *key);
int _CsvParser_KeyExist(CsvParser *csvParser, char *key);
int _CsvParser_delimiterIsAccepted(char delimiter);
char * _CsvParser_duplicate(const char *str, size_t len, int trim);
void _gotoNextLine(CsvParser *csvParser);
void _ReadNextBuff(CsvParser *csvParser);
char _GetNextByte(CsvParser *csvParser);
char _GetCurrByte(CsvParser *csvParser);

#ifdef __cplusplus
}
#endif

#endif
