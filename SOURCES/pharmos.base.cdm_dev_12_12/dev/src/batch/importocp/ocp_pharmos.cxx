#include "../../cdm_version.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <libgen.h>
#include <stdarg.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include "define.h"
#include "csvparser.h"
#include "ocp_pharmos.h"
#include "sql_reqs.h"

exec sql begin declare section;
    mint               db_exception_count;
    mint               db_row_count;
exec sql end declare section;


extern void PrintMsg(char *fun, char mld, char *error_msgFormat, ...);

/********************************************************************************/
/* MACROS */
/********************************************************************************/
#define ERROR_MSG(x, sqlError)    if(SQLCODE < 0) { PrintMsg( fun, FEHLER, x ); sqlError = true; }
#define OCP_SAFE_DELETE(ptr) if ( ptr != NULL) { free(ptr); ptr = NULL; }

// exclusion ocp_no map ////////////////////////////////////////////

int countExcludedOCPNo = 0;
long ListExcludedOCPNo[MAX_COUNT_EXCLUDED_OCPNO];

int _cmpLongFunc (const void * a, const void * b) {
    long x = *(long*)a;
    long y = *(long*)b;

    if (x > y)
        return 1;
    if (x < y)
        return -1;
    return 0;
}

bool InitOCPNoExclusionMap(long inDate, long inTime) {

    char    *fun = "InitOCPNoExclusionMap";
    bool    bDbSqlError = false;

exec sql begin declare section;
    long    cDate = inDate;
    long    cTime = inTime;
    long    cOCPNo = 0;
    char    tmpSql[4096];
exec sql end declare section;


    PSQL_STR_SEL_OCPNO_COCP_STAGEIN_XXX_IMPORT_DATETIME(tmpSql);
    EXEC SQL PREPARE preSelectOCPNo_cocp_stagein_xxx_datetime from :tmpSql;
    ERROR_MSG("prepare preSelectOCPNo_cocp_stagein_xxx_datetime", bDbSqlError);
    EXEC SQL DECLARE selectOCPNo_cocp_stagein_xxx_datetime cursor with hold for preSelectOCPNo_cocp_stagein_xxx_datetime;
    ERROR_MSG("prepare selectOCPNo_cocp_stagein_xxx_datetime", bDbSqlError);
    EXEC SQL FREE preSelectOCPNo_cocp_stagein_xxx_datetime;

    if (bDbSqlError) {
        return false;
    }

    EXEC SQL OPEN selectOCPNo_cocp_stagein_xxx_datetime using :cDate, :cTime, :cDate, :cTime, :cDate, :cTime, :cDate, :cTime;
    EXEC SQL FETCH selectOCPNo_cocp_stagein_xxx_datetime into :cOCPNo;

    while(SQLCODE==0) {
        ListExcludedOCPNo[countExcludedOCPNo] = cOCPNo;
        countExcludedOCPNo++;

        EXEC SQL FETCH selectOCPNo_cocp_stagein_xxx_datetime into :cOCPNo;
    }

    // sort list of ocpno
    if (countExcludedOCPNo > 0) {
        qsort(ListExcludedOCPNo, countExcludedOCPNo, sizeof(long), _cmpLongFunc);
    }

    return true;
}

bool IsExcludedOCPNo(long ocpNo) {
    long searchKey = ocpNo;
    long *keyPtr = &searchKey;

    long *foundKey = NULL;
    searchKey = ocpNo;

    foundKey = (long *)bsearch(keyPtr, ListExcludedOCPNo, countExcludedOCPNo, sizeof(long), _cmpLongFunc);
    if (foundKey != NULL) {
        return true;
    }
    return false;
}


// Input PINT TO CSV Map ////////////////////////////////////////////

#define PINT_SIZE_MARKER 6

int countArrayPINTToCSV = 4;
char PINTToCSVSep = ';';

RowMapPINTToCSV arrayMapPINTToCSV[] = {
    { "CART  ", { 10, 5, 25, 5, 10, 0 } },
    { "ZART  ", { 10, 30, 9, 3, 5, 1, 10, 10, 1, 1, 1, 1, 10, 1, 1, 10, 1, 10, 10, 1, 1, 10, 10, 10, 10, 10, 1, 1, 10, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 0 } },
    { "ZPREIS", { 10, 10, 12, 12, 12, 1, 12, 12, 12, 5, 12, 12, 12, 5, 12, 20, 5, 0 } },
    { "ZFRAN ", { 10, 12, 12, 10, 5, 1, 1, 1, 15, 1, 1, 1, 3, 1, 12, 5, 0 } }
};

bool ConvPINTToCSV(char *inFileName, char *outFileName) {
    char *fun = "ConvPINTToCSV";
    #define MAX_SIZE_IN_LINE 2048
    char inLine[MAX_SIZE_IN_LINE];
    char outLine[MAX_SIZE_IN_LINE*2];
    int lineAvailBytes = 0;
    int linePos = 0;
    int olinePos = 0;

    int lineCount = 1;
    char LINEMARK[PINT_SIZE_MARKER] = "";
    FILE *inFILE = NULL;
    FILE *outFile = NULL;

    if ((inFILE = fopen(inFileName, "rt")) == NULL) {
        PrintMsg(fun, FEHLER, "Fatal i/o error, failed to open '%s' for reading", inFileName);
        return false;
    }
    if ((outFile = fopen(outFileName, "wt")) == NULL) {
        PrintMsg(fun, FEHLER, "Fatal i/o error, failed to open '%s' for writing", outFileName);
        fclose(inFILE);
        return false;
    }

    while (fgets(inLine, MAX_SIZE_IN_LINE, inFILE) != NULL) {
        bool lineHandled = false;
        bool lineValid = true;
        int sizeCurColumn = 0;
        lineAvailBytes = strlen(inLine);
        // remove any endian \n \r at the end of the line
        while (lineAvailBytes > 0) {
            if (inLine[lineAvailBytes-1] == '\n' || inLine[lineAvailBytes-1] == '\r') {
                lineAvailBytes--;
            } else {
                break;
            }
        }
        linePos = 0;
        olinePos = 0;
        if (lineAvailBytes <= PINT_SIZE_MARKER) {
            PrintMsg(fun, FEHLER, "Line %i, is too short, skipping!", lineCount);
            lineCount++;
            continue;
        }

        for (int idRow = 0; idRow < countArrayPINTToCSV; idRow ++)
        {
            if (strncmp(inLine, arrayMapPINTToCSV[idRow].ID, PINT_SIZE_MARKER) == 0) {
                lineHandled = true;
                strncpy(&outLine[olinePos], &inLine[linePos], PINT_SIZE_MARKER);
                olinePos += PINT_SIZE_MARKER;
                outLine[olinePos] = PINTToCSVSep;
                olinePos++;
                lineAvailBytes -= PINT_SIZE_MARKER;
                linePos += PINT_SIZE_MARKER;
                for (int idColumn=0;(sizeCurColumn = arrayMapPINTToCSV[idRow].FieldsLength[idColumn]) > 0; idColumn++) {
                    if (lineAvailBytes < sizeCurColumn) {
                        PrintMsg(fun, FEHLER, "Line %i, is too short, rowId %s, column %i, skipping!", lineCount, arrayMapPINTToCSV[idRow].ID, idColumn);
                        lineValid = false;
                        break;
                    }
                    strncpy(&outLine[olinePos], &inLine[linePos], sizeCurColumn);
                    olinePos += sizeCurColumn;
                    // not the last column ?
                    if (arrayMapPINTToCSV[idRow].FieldsLength[idColumn+1] > 0)
                    {
                        outLine[olinePos] = PINTToCSVSep;
                        olinePos++;
                    }
                    lineAvailBytes -= sizeCurColumn;
                    linePos += sizeCurColumn;
                }
                if (lineValid) {
                    if (lineAvailBytes > 0) {
                        PrintMsg(fun, HINWEIS, "Line %i, Warning %i left unused bytes", lineCount, lineAvailBytes);
                    }
                    outLine[olinePos] = 0; // marker end of line
                    fprintf(outFile,"%s\n", outLine);
                }
                break;
            }
        }
        if (!lineHandled) {
            PrintMsg(fun, FEHLER, "Line %i, unknow ID!", lineCount);
        }
        lineCount++;
    }
    fclose(inFILE);
    fclose(outFile);
    return true;
}


// Input CSV parsing DATA ///////////////////////////////////////////

// all FLAGS must enabled else import rejected
int InOCPImportMustStates[] = {
    // old pharmos existing
    IN_OCPNO_HAS_ART_NO | IN_OCPNO_HAS_PH_ART,
    // new article
    IN_OCPNO_HAS_ART_NO | IN_OCPNO_HAS_IN_ART,
    // end marker
    0
};

// at least one FLAG should be enabled else import rejected
int InOCPImportAnyStates[] = {
    // old pharmos existing
    IN_OCPNO_HAS_IN_ART | IN_OCPNO_HAS_IN_ART_CODE | IN_OCPNO_HAS_IN_ART_PRICE | IN_OCPNO_HAS_IN_ART_FRANCE,
    // new article
    0
};


InOCPNoFLAGS InOCPNoList[IN_OCP_MAX_COUNT];
InOCPNoFLAGS *InOCPNoMap[IN_OCP_MAX_COUNT];
int InOCPNoCount = 0;

int _cmpInOCPNofunc (const void * a, const void * b) {
    const InOCPNoFLAGS* s1 = *(const InOCPNoFLAGS**) a;
    const InOCPNoFLAGS* s2 = *(const InOCPNoFLAGS**) b;
    return (s1->ocp_art_no - s2->ocp_art_no);
}

bool ImportReadyCharOCPNo(char *socp_no, int *OCP_FLAGS) {
    return ImportReadyOCPNo(atoi(socp_no), OCP_FLAGS);
}

bool ImportReadyOCPNo(int ocp_no, int *OCP_FLAGS) {
    InOCPNoFLAGS *OCPNoFLAG = GetInOCPNoFLAGS(ocp_no);

    // not found
    if (OCPNoFLAG == NULL) {
        *OCP_FLAGS = 0;
        return false;
    }
    // set flags value
    if (OCP_FLAGS != NULL) {
        *OCP_FLAGS = OCPNoFLAG->FLAGS;
    }
    // Search for valid state of FLAGS
    for (int i=0; InOCPImportMustStates[i] != 0; i++) {
        // check must flag, all bit should be enabled
        if ((OCPNoFLAG->FLAGS & InOCPImportMustStates[i]) == InOCPImportMustStates[i]) {
            // check any flag, if not zero, at least one flag should be enabled
            if (InOCPImportAnyStates[i] == 0 || ((OCPNoFLAG->FLAGS & InOCPImportAnyStates[i]) > 0)) {
                return true;
            }
        }
    }
    return false;
}

InOCPNoFLAGS *GetInCharOCPNoFLAGS(char *cocp_no) {
    return GetInOCPNoFLAGS(atoi(cocp_no));
}

bool ExistOCP_NO(int ocp_no) {
    return (GetInOCPNoFLAGS(ocp_no) != NULL);
}

InOCPNoFLAGS *GetInOCPNoFLAGS(int ocp_no) {
    InOCPNoFLAGS searchKey;
    InOCPNoFLAGS *keyPtr = &searchKey;

    InOCPNoFLAGS **foundKey = NULL;
    searchKey.ocp_art_no = ocp_no;

    if (InOCPNoCount > 1) {
        foundKey = (InOCPNoFLAGS **)bsearch(&keyPtr, InOCPNoMap, InOCPNoCount, sizeof(InOCPNoFLAGS*), _cmpInOCPNofunc);
    } else {
        if (ocp_no == InOCPNoMap[0]->ocp_art_no) {
            foundKey = &InOCPNoMap[0];
        }
    }
    return *foundKey;
}

InOCPNoFLAGS* InsertInOCPNo(int ocp_no, int init_flags) {
    if (InOCPNoCount >= IN_OCP_MAX_COUNT) {
        return NULL;
    }

    char cocp_no[32];
    char cart_no[32];
    InOCPNoList[InOCPNoCount].ocp_art_no = ocp_no;
    InOCPNoList[InOCPNoCount].art_no = -1;
    InOCPNoList[InOCPNoCount].FLAGS = init_flags;

    // check if it has article_code entry with article_no
    sprintf(cocp_no,"%i",ocp_no); // convert ocp_no to (char *)
    if (GetOCPNoToArticleNo(cocp_no, cart_no)) {
        InOCPNoList[InOCPNoCount].art_no = atoi(cart_no);
        if (InOCPNoList[InOCPNoCount].art_no != 0) {
            InOCPNoList[InOCPNoCount].FLAGS |= IN_OCPNO_HAS_ART_NO;
            UpdateMasterDATA_FLAGS(cart_no, &InOCPNoList[InOCPNoCount].FLAGS);
        }
    }

    // first element
    if (InOCPNoCount == 0) {
        InOCPNoMap[0] = &InOCPNoList[0];
    } else {
        InOCPNoMap[InOCPNoCount] = &InOCPNoList[InOCPNoCount];
        qsort(InOCPNoMap, (InOCPNoCount+1), sizeof(InOCPNoFLAGS*), _cmpInOCPNofunc);
    }
    InOCPNoCount++;
    return &InOCPNoList[InOCPNoCount-1];
}

void UpdateMasterDATA_FLAGS(char *articleNo, int *FLAGS)
{

    TrimStr(articleNo);

    if (articleNo != NULL && FLAGS != NULL)
    {
        *FLAGS &= IN_OCPNO_MDATA_FLAGS_DELETE;
        if (ExistMasterArticle(articleNo, &mapArticleRow))
        {
            *FLAGS |= IN_OCPNO_HAS_PH_ART;
        }
        if (ExistMasterArticle(articleNo, &mapArticleCodesRow)) // search for any existing what ever code_type value
        {
            *FLAGS |= IN_OCPNO_HAS_PH_ART_CODE;
        }
        if (ExistMasterArticle(articleNo, &mapArticlePriceRow))
        {
            *FLAGS |= IN_OCPNO_HAS_PH_ART_PRICE;
        }
        if (ExistMasterArticle(articleNo, &mapArticleFranceRow))
        {
            *FLAGS |= IN_OCPNO_HAS_PH_ART_FRANCE;
        }
    }
}

// Input CSV maps and default rows ///////////////////////////////////

int article_code_incsv_map[] = {
	OCP_ARTICLE_NO_IDX,
	ARTICLE_CODES_CODE_TYPE_IDX,
	ARTICLE_CODES_ARTICLE_CODE_IDX,
	ARTICLE_CODES_PREFERRED_FLAG_IDX,
	ARTICLE_CODES_CHANGED_DATE_IDX
};

int article_incsv_map[] = {
	OCP_ARTICLE_NO_IDX,
	ARTICLE_LONG_NAME_IDX,
	ARTICLE_UNIT_IDX,
	ARTICLE_DOSAGE_FORM_IDX,
	ARTICLE_PRODUCT_GROUP_IDX,
	ARTICLE_PRODUCT_TYPE_IDX,
	ARTICLE_MANUFACTURER_NO_IDX,
	ARTICLE_SUPPLIER_NO_IDX,
	ARTICLE_NEGATIVE_LIST_IDX,
	ARTICLE_BATCH_ARTICLE_IDX,
	ARTICLE_COOLING_ARTICLE_IDX,
	ARTICLE_NARCOTICS_IDX,
	ARTICLE_EXPIRY_DATE_IDX,
	ARTICLE_VETERINARY_IDX,
	ARTICLE_PRESCRIPTION_NEEDED_IDX,
	ARTICLE_DURATION_MONTHS_IDX,
	ARTICLE_PSYCHOTROPE_IDX,
	ARTICLE_CREATION_DATE_IDX,
	ARTICLE_MODIFICATION_DATE_IDX,
	ARTICLE_FMD_RELEVANT_IDX,
	ARTICLE_ZYTOSTATIC_IDX,
	ARTICLE_OUT_OF_MARKET_DATE_IDX,
	ARTICLE_LENGTH_IDX,
	ARTICLE_WIDTH_IDX,
	ARTICLE_HEIGHT_IDX,
	ARTICLE_WEIGHT_IDX,
	ARTICLE_BLOCKED_IDX,
	ARTICLE_NOT_ALLOWED_IDX,
	ARTICLE_PACKAGE_UNIT_1_IDX,
	ARTICLE_PACKAGE_UNIT_2_IDX,
	ARTICLE_PACKAGE_UNIT_3_IDX,
	ARTICLE_PACKAGE_UNIT_4_IDX,
	ARTICLE_TAX_IDX,
	ARTICLE_PHARMACY_ONLY_IDX,
	ARTICLE_TOXIC_IDX,
	ARTICLE_VERY_TOXIC_IDX,
	ARTICLE_HARMFUL_IDX,
	ARTICLE_MEDICATION_IDX,
	ARTICLE_HOMEOPATHY_IDX,
	ARTICLE_MEDICAL_GASES_IDX
};

int article_price_incsv_map[] = {
	OCP_ARTICLE_NO_IDX,
	ARTICLE_PRICE_VALID_FROM_DATE_IDX,
	ARTICLE_PRICE_MANUFACTURER_BASE_PRICE_IDX,
	ARTICLE_PRICE_PHARMACY_BUY_PRICE_IDX,
	ARTICLE_PRICE_PHARMACY_SELL_PRICE_IDX,
	ARTICLE_PRICE_VAT_CODE_IDX,
	ARTICLE_PRICE_MANUFACTURER_PERCENTAGE_IDX,
	ARTICLE_PRICE_RECOM_PHARMACY_SELL_PRICE_IDX,
	ARTICLE_PRICE_MAX_PHARMACY_SELL_PRICE_IDX,
	ARTICLE_PRICE_PRICE_TYPE_IDX,
	ARTICLE_PRICE_SUPPLIER_BASE_PRICE_IDX,
	ARTICLE_PRICE_MAX_PHARMACY_BUY_PRICE_IDX,
	ARTICLE_PRICE_REFUND_AMOUNT,
	ARTICLE_PRICE_DISCOUNT_DEDUCED_YET_IDX,
	ARTICLE_PRICE_PHARMACY_BASE_PRICE_IDX,
	ARTICLE_PRICE_PUBLICATION_NUMBER_IDX,
	ARTICLE_PRICE_PRICE_MODEL_IDX
};

int article_france_incsv_map[] = {
	OCP_ARTICLE_NO_IDX,
	ARTICLE_FRANCE_REIMBURSEMENT_PERC_IDX,
	ARTICLE_FRANCE_REIMBURSEMENT_VAL_IDX ,
	ARTICLE_FRANCE_UNIT_MULTIPLE_IDX     ,
	ARTICLE_FRANCE_QTY_SUBMULTIPLE_IDX   ,
	ARTICLE_FRANCE_RESERVE_HOSP_IDX      ,
	ARTICLE_FRANCE_REIMBURSEMENT_TYPE_IDX,
	ARTICLE_FRANCE_NOT_VIA_EDI_IDX       ,
	ARTICLE_FRANCE_CODE_LPPR_IDX         ,
	ARTICLE_FRANCE_CODE_BLOCAGE_IDX      ,
	ARTICLE_FRANCE_DISTR_RESTR_LEGAL_IDX ,
	ARTICLE_FRANCE_DISTR_RESTR_BREIZH_IDX,
	ARTICLE_FRANCE_REBATE_GROUP_SPEC_IDX  ,
	ARTICLE_FRANCE_DISTR_RESTR_HOSP_IDX  ,
	ARTICLE_FRANCE_TFR_BASE_PRICE_IDX    ,
	ARTICLE_FRANCE_DISTR_RESTR_EXPORT_IDX
};

// default stageout rows
char *oarticleDefaults[OARTICLE_FIELDS_COUNT] =
    {   "0", "0", "", "", "", "", "", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
        "0", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N",
        "N", "N", "N", "N", "N", "N",
        "11111111111111111111"\
        "11111111111111111111"\
        "11111",
        "1",
        "system", "0", "0"
    };
CsvRow *oarticleDefaultRow = NULL;

char *oarticleCodesDefaults[OARTICLE_CODES_FIELDS_COUNT] =
    { "0", "0", "", "0", "0", "0",
      "111111",
      "1",
      "system", "0", "0"
    };
CsvRow *oarticleCodesDefaultRow = NULL;

char *oarticlePriceDefaults[OARTICLE_PRICE_FIELDS_COUNT] =
    { "0", "0", "0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "", "0", "0", "0", "",
        "1111111111111111111",
        "1",
        "system", "0", "0"
     };

CsvRow *oarticlePriceDefaultRow = NULL;

char *oarticleFranceDefaults[OARTICLE_FRANCE_FIELDS_COUNT] =
    { "0", "0", "0.0", "0.0", "", "0", "", "", "", "0", "", "0.0", "0", "", "", "", "",
        "11111111111111111",
        "1",
        "system", "0", "0"
      };
CsvRow *oarticleFranceDefaultRow = NULL;

void CreateStageoutDefaultRows() {
        oarticleCodesDefaultRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
        if (oarticleCodesDefaultRow != NULL) {
            CsvRow_setValues(oarticleCodesDefaultRow, OARTICLE_CODES_FIELDS_COUNT, oarticleCodesDefaults);
        }
        oarticleDefaultRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
        if (oarticleDefaultRow != NULL) {
            CsvRow_setValues(oarticleDefaultRow, OARTICLE_FIELDS_COUNT, oarticleDefaults);
        }
        oarticlePriceDefaultRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
        if (oarticlePriceDefaultRow != NULL) {
            CsvRow_setValues(oarticlePriceDefaultRow, OARTICLE_PRICE_FIELDS_COUNT, oarticlePriceDefaults);
        }
        oarticleFranceDefaultRow = CsvRow_Create(CSVFORMAT_MAX_COLUMN_COUNT, CSVFORMAT_MAX_COLUMN_SIZE);
        if (oarticleFranceDefaultRow != NULL) {
            CsvRow_setValues(oarticleFranceDefaultRow, OARTICLE_FRANCE_FIELDS_COUNT, oarticleFranceDefaults);
        }
}

// conversion copy
void CopyPharmosToStageout(char *dstField, char *srcField, char fieldType) {
    switch (fieldType) {
    case ' ': // neutral - just copy with trim
        strcpy(dstField, srcField);
        TrimStr(dstField);
        break;
    case 'B': // Boolean 0/1
        if (srcField[0] == '1') {
            strcpy(dstField, "Y");
        } else {
            strcpy(dstField, "N");
        }
        break;
    case 'Y': // Boolean N/Y
        if (srcField[0] == 'Y') {
            strcpy(dstField, "Y");
        } else {
            strcpy(dstField, "N");
        }
        break;
    case 'F': // Float/decimal
        strcpy(dstField, srcField);
        TrimStr(dstField);
        ReplaceCharStr(dstField, ',', '.');
        break;
    }
}

void CopyStageoutToPharmos(char *dstField, char *srcField, char fieldType) {

    switch (fieldType) {
    case ' ': // neutral - just copy with trim
        strcpy(dstField, srcField);
        TrimStr(dstField);
        break;
    case 'B': // Boolean 0/1
        if (srcField[0] == 'Y') {
            strcpy(dstField, "1");
        } else {
            strcpy(dstField, "0");
        }
        break;
    case 'Y': // Boolean N/Y
        if (srcField[0] == 'Y') {
            strcpy(dstField, "Y");
        } else {
            strcpy(dstField, "N");
        }
        break;
    case 'F': // Float/decimal
        strcpy(dstField, srcField);
        TrimStr(dstField);
        ReplaceCharStr(dstField, ',', '.');
        break;
    }
}

// maps from/to stageout/pharmos ///////////////////////////////////////////////////


SetTablesToFromRowMap mapArticleRow =
{
    2,
    OARTICLE_FIELDS_COUNT,
    256,
    "cocp_stageout_article",
    {
        // 	Zarticle fromTo Row Map
        {
            "zartikel", // database table
            "artikel_nr",
            34, // count fields to get/set
            true,
            // fields names
            {
                {	' ', "artikel_nr",                    OARTICLE_NO_IDX },
                {	' ', "artikel_name",                  OARTICLE_LONG_NAME_IDX },
                {	' ', "einheit",                       OARTICLE_UNIT_IDX },
                {	' ', "darreichform",                  OARTICLE_DOSAGE_FORM_IDX },
                {	' ', "produktart",                    OARTICLE_PRODUCT_TYPE_IDX },
                {	' ', "hersteller_nr",                 OARTICLE_MANUFACTURER_NO_IDX },
                {	' ', "awl1",                          OARTICLE_AWL1_IDX },
                {	' ', "laenge",                        OARTICLE_LENGTH_IDX },
                {	' ', "breite",                        OARTICLE_WIDTH_IDX },
                {	' ', "hoehe",                         OARTICLE_HEIGHT_IDX },
                {	' ', "gewicht",                       OARTICLE_WEIGHT_IDX },
                {	' ', "datum_anlage",                  OARTICLE_CREATION_DATE_IDX },
                {	' ', "datum_aender",                  OARTICLE_MODIFICATION_DATE_IDX },
                {	' ', "datum_av",                      OARTICLE_EXPIRY_DATE_IDX },
                {	' ', "datum_ah",                      OARTICLE_OUT_OF_MARKET_DATE_IDX },
                {	' ', "laufzeitmonate",                OARTICLE_DURATION_MONTHS_IDX },
                {	'B', "negativliste",                  OARTICLE_NEGATIVE_LIST_IDX },
                {	'B', "chargenartikel",                OARTICLE_BATCH_ARTICLE_IDX },
                {	' ', "kuehlartikel",                  OARTICLE_COOLING_ARTICLE_IDX },
                {	'B', "btm",                           OARTICLE_NARCOTICS_IDX },
                {	'B', "fmd_relevant",                  OARTICLE_FMD_IDX },
                {	'B', "tierarznei",                    OARTICLE_VETERINARY_IDX },
                {	'B', "rezeptpfl",                     OARTICLE_PRESCRIPTION_NEEDED_IDX },
                {	'Y', "psychotrop",                    OARTICLE_PSYCHOTROPE_IDX },
                {	'B', "zytostatika",                   OARTICLE_ZYTOSTATIC_IDX },
                {	'B', "zentr_eksperre",                OARTICLE_BLOCKED_IDX },
                {	'B', "bestellsperre",                 OARTICLE_NOT_ALLOWED_IDX },
                {	'B', "taxpfl",                        OARTICLE_TAX_IDX },
                {	'B', "apothekenpfl",                  OARTICLE_PHARMACY_ONLY_IDX },
                {	'B', "gs_giftig",                     OARTICLE_TOXIC_IDX },
                {	'B', "gs_sehrgiftig",                 OARTICLE_VERY_TOXIC_IDX },
                {	'B', "gs_gesundhsch",                 OARTICLE_HARMFUL_IDX },
                {	'B', "homoeopathikum",                OARTICLE_HOMEOPATHY_IDX },
                {	'B', "medizinische_gase",             OARTICLE_MEDICAL_GASES_IDX }
            }
        },

        {
            "artve", // artikel_nr
            "artikel_nr",
            4,
            false,
            {
                { ' ', "verpackeinheit1", OARTICLE_PACKAGE_UNIT_1_IDX },
                { ' ', "verpackeinheit2", OARTICLE_PACKAGE_UNIT_2_IDX },
                { ' ', "verpackeinheit3", OARTICLE_PACKAGE_UNIT_3_IDX },
                { ' ', "verpackeinheit4", OARTICLE_PACKAGE_UNIT_4_IDX }
            }
        }
    }

};


SetTablesToFromRowMap mapArticleCodesRow =
{
    1,
    OARTICLE_CODES_FIELDS_COUNT,
    256,
    "cocp_stageout_articlecode",
    {
        // 	Zarticle fromTo Row Map
        {
            "carticlecodes", // database table
            "article_code",
            5, // count fields to get/set
            true,
            // fields names
            {
                {	' ', "articleno",                  OARTICLE_CODES_ARTICLENO_IDX },
                {	' ', "code_type",                  OARTICLE_CODES_CODE_TYPE_IDX },
                {	' ', "article_code",               OARTICLE_CODES_ARTICLE_CODE_IDX },
                {	' ', "preferred_flag",             OARTICLE_CODES_PREFERRED_FLAG_IDX },
                {	' ', "date_changed",               OARTICLE_CODES_DATE_CHANGED_IDX }
            }
        }
     }
};

SetTablesToFromRowMap mapArticlePriceRow =
{
    1,
    OARTICLE_PRICE_FIELDS_COUNT,
    256,
    "cocp_stageout_articleprice",
    {
        // 	Zarticle fromTo Row Map
        {
            "zartpreis", // database table
            "artikel_nr",
            17, // count fields to get/set
            true,
            // fields names
            {
                {	' ', "artikel_nr",                   OARTICLE_PRICE_ARTICLE_NO_IDX   },
                {	' ', "datumgueltigab",               OARTICLE_PRICE_DATE_VALID_FROM_IDX  },
                {	'F', "grosso",                       OARTICLE_PRICE_GROUND_PRICE_IDX          },
                {	'F', "aep",                          OARTICLE_PRICE_PHARMACY_BUYING_PRICE_IDX    },
                {	'F', "avp",                          OARTICLE_PRICE_PHARMACY_SELLING_PRICE_IDX   },
                {	' ', "ke_mwst",                      OARTICLE_PRICE_KE_MWST_IDX  },
                {	'F', "herst_prozent",                OARTICLE_PRICE_HERST_PROZENT_IDX  },
                {	'F', "eavp",                         OARTICLE_PRICE_EAVP_IDX          },
                {	'F', "maxavp",                       OARTICLE_PRICE_MAX_AVP_IDX    },
                {	' ', "preis_typ",                    OARTICLE_PRICE_PRICE_TYPE_IDX    },
                {	'F', "lieferbasispreis",             OARTICLE_PRICE_SUPPLIER_BASE_PRICE_IDX       },
                {	'F', "maxaep",                       OARTICLE_PRICE_MAX_AEP_IDX       },
                {	' ', "pricemodel",                   OARTICLE_PRICE_PRICE_MODEL_IDX      },
                {	' ', "disc_deduced_yet",             OARTICLE_PRICE_DISC_DEDUCED_YET_IDX          },
                {	'F', "pharmacy_baseprice",           OARTICLE_PRICE_PHARMACY_BASE_PRICE_IDX    },
                {	' ', "publicationnumber",            OARTICLE_PRICE_PUBLICATION_NUMBER_IDX        },
                {	'F', "erstattbetrag",                OARTICLE_PRICE_ERSTATTBETRAG_IDX      }
            }
        }
     }
};

SetTablesToFromRowMap mapArticleFranceRow =
{
    1,
    OARTICLE_FRANCE_FIELDS_COUNT,
    256,
    "cocp_stageout_article_france",
    {
        // 	Zarticle fromTo Row Map
        {
            "zartfrance", // database table
            "articleno",
            16, // count fields to get/set
            true,
            // fields names
            {
                {	' ', "articleno",                    OARTICLE_FRANCE_ARTICLE_NO_IDX            },
                {	'F', "reimbursement_perc",           OARTICLE_FRANCE_REIMBURSEMENT_PERC_IDX    },
                {	'F', "reimbursement_val",            OARTICLE_FRANCE_REIMBURSEMENT_VAL_IDX     },
                {	' ', "unit_multiple",                OARTICLE_FRANCE_UNIT_MULTIPLE_IDX         },
                {	' ', "qty_submultiple",              OARTICLE_FRANCE_QTY_SUBMULTIPLE_IDX       },
                {	' ', "reserve_hosp",                 OARTICLE_FRANCE_RESERVE_HOSP_IDX          },
                {	' ', "reimbursement_type",           OARTICLE_FRANCE_REIMBURSEMENT_TYPE_IDX    },
                {	' ', "not_via_edi",                  OARTICLE_FRANCE_NOT_VIA_EDI_IDX           },
                {	' ', "code_bloquage",                OARTICLE_FRANCE_CODE_BLOCAGE_IDX          },
                {	' ', "code_lppr",                    OARTICLE_FRANCE_CODE_LPPR_IDX             },
                {	' ', "tfr_base_price",               OARTICLE_FRANCE_TFR_BASE__PRICE_IDX       },
                {	' ', "distr_restr_export",           OARTICLE_FRANCE_DISTR_RESTR_EXPORT_IDX    },
                {	' ', "distr_restr_legall",           OARTICLE_FRANCE_DISTR_RESTR_LEGAL_IDX     },
                {	' ', "distr_restr_breizh",           OARTICLE_FRANCE_DISTR_RESTR_BREIZH_IDX    },
                {	' ', "distr_restr_hosp",             OARTICLE_FRANCE_DISTR_RESTR_HOSP_IDX      },
                {	' ', "rebate_group_spec",            OARTICLE_FRANCE_REBATE_GROUP_SPEC_IDX     }
            }
        }
     }
};


exec sql begin declare section;
char esqlRows[128][256];
exec sql end declare section;

char * TableToFromRowMapToSQLSel(TableToFromRowMap *tableMap, char *outSql, char *Id) {
    strcpy(outSql, "select ");
    for (int i = 0; i < tableMap->countFields; i++)
    {
        strcat(outSql, tableMap->elemsMap[i].FieldsName);
        (i < (tableMap->countFields - 1)) ? strcat(outSql, ", ") :  strcat(outSql, " ");
    }
    strcat(outSql, "from ");
    strcat(outSql, tableMap->nameDbTable);
    strcat(outSql, " where ");
    strcat(outSql, tableMap->IDFieldName);
    strcat(outSql, " = '");
    strcat(outSql, Id);
    strcat(outSql, "'");


    return outSql;
}


bool GetStageoutArticle(CsvRow * outRow, char *ArticleNo)
{
    exec sql begin declare section;
    char tmpSql[4096];
    exec sql end declare section;
    char *trimStr = NULL;

    CsvRow_copy(outRow, oarticleDefaultRow);

    // get Fields
    for (int i =0; i < mapArticleRow.countMaps; i++) {
        TableToFromRowMapToSQLSel(&mapArticleRow.maps[i], tmpSql, ArticleNo);
        // execute sql
        EXEC SQL PREPARE preSelArticle from :tmpSql;
        EXEC SQL DECLARE curSelArticle cursor with hold for preSelArticle;
        if (SQLCODE < 0)
        {
          // failed to create Cursor SelArticlePrice
          return false;
        }
        exec sql free preSelArticle;
        EXEC SQL OPEN curSelArticle;
        EXEC SQL FETCH curSelArticle into ESQL_ROWS_INTO;

        if (NOT_FOUND) {
            if (mapArticleRow.maps[i].master) {
              exec sql free curSelArticle;
              return false;
            } else {
              exec sql free curSelArticle;
              continue;
            }
        }

        // copy extracted values

        for (int j = 0; j < mapArticleRow.maps[i].countFields; j++) {
            CopyPharmosToStageout(outRow->fields[mapArticleRow.maps[i].elemsMap[j].mapToFromRowIdx], esqlRows[j],
              mapArticleRow.maps[i].elemsMap[j].Type);
        }
        exec sql free curSelArticle;
    }
    // get season group fields
    GetSeasonGroup(ArticleNo, outRow->fields[OARTICLE_DKART_PRODUCT_GROUP_IDX], outRow->fields[OARTICLE_SEASON_GROUP_1_IDX],
            outRow->fields[OARTICLE_SEASON_GROUP_2_IDX], outRow->fields[OARTICLE_SEASON_GROUP_3_IDX]);
    return true;
}

// get season group 2, 5, A and G else empty cgar
void GetSeasonGroup(char *article_no, char *grp_2, char *grp_5, char *grp_A, char *grp_G) {
    char *fun = "GetSeasonGroup()";
    bool bDbSqlError = false;
    exec sql begin declare section;
    char str[2048] = "";
    char grpRes[32] = "";
    char *pArt_no = article_no;
    char *Grp2="2";
    char *Grp5="5";
    char *GrpA="A";
    char *GrpG="G";
    exec sql end declare section;

    strcpy(grp_2, "");
    strcpy(grp_5, "");
    strcpy(grp_A, "");
    strcpy(grp_G, "");

    PSQL_STR_SELECT_SEASON_GROUP_ZARTWG(str);
    EXEC SQL PREPARE preSelectSeasonGroupZartwg from :str;
    ERROR_MSG("prepare preSelectSeasonGroupZartwg", bDbSqlError);
    EXEC SQL DECLARE selectSeasonGroupZartwg cursor with hold for preSelectSeasonGroupZartwg;
    ERROR_MSG("prepare selectSeasonGroupZartwg", bDbSqlError);
    EXEC SQL FREE preSelectSeasonGroupZartwg;

    EXEC SQL OPEN selectSeasonGroupZartwg using :pArt_no, :Grp2;
    EXEC SQL FETCH selectSeasonGroupZartwg into :grpRes;
    if (SQLCODE == 0) {
        TrimStr(grpRes);
        strcpy(grp_2, grpRes);
    }

    EXEC SQL OPEN selectSeasonGroupZartwg using :pArt_no, :Grp5;
    EXEC SQL FETCH selectSeasonGroupZartwg into :grpRes;
    if (SQLCODE == 0) {
        TrimStr(grpRes);
        strcpy(grp_5, grpRes);
    }

    EXEC SQL OPEN selectSeasonGroupZartwg using :pArt_no, :GrpA;
    EXEC SQL FETCH selectSeasonGroupZartwg into :grpRes;
    if (SQLCODE == 0) {
        TrimStr(grpRes);
        strcpy(grp_A, grpRes);
    }

    EXEC SQL OPEN selectSeasonGroupZartwg using :pArt_no, :GrpG;
    EXEC SQL FETCH selectSeasonGroupZartwg into :grpRes;
    if (SQLCODE == 0) {
        TrimStr(grpRes);
        strcpy(grp_G, grpRes);
    }
}

bool PutSeasonGroup(char *article_no, char *grp_2, char *grp_5, char *grp_A, char *grp_G) {
    char *fun = "PutSeasonGroup()";
    bool bDbSqlError = false;
    bool bRes = true;
    exec sql begin declare section;
    char str[2048] = "";
    char grpPut[32] = "";
    char *pArt_no = article_no;
    char *GrpsF[] = { "2", "5", "A", "G", NULL };
    char *GrpsD[] = { grp_2, grp_5, grp_A, grp_G };
    exec sql end declare section;

    PSQL_STR_INS_SEASON_GROUP_ZARTWG(str);
    EXEC SQL PREPARE insSeasonGroupZartwg from : str;
    ERROR_MSG("prepare insSeasonGroupZartwg", bDbSqlError);

    PSQL_STR_UPDATE_SEASON_GROUP_ZARTWG(str);
    EXEC SQL PREPARE updateSeasonGroupZartwg from : str;
    ERROR_MSG("prepare updateSeasonGroupZartwg", bDbSqlError);

    for (int i = 0; GrpsF[i] != NULL; i++) {
        TrimStr(GrpsD[i]);
        if (GrpsD[i][0] == 0) {
            continue; // skip the empty ones
        }
        // if not exist update
        if (ExistSeasonGroup(pArt_no, GrpsF[i])) {
            exec sql execute updateSeasonGroupZartwg using :pArt_no, :GrpsF[i], :GrpsD[i], :pArt_no, :GrpsF[i];
            bRes = (SQLCODE == 0);
        } else {
        // else try insert
            exec sql execute insSeasonGroupZartwg using :pArt_no, :GrpsF[i], :GrpsD[i];
            bRes = (SQLCODE == 0);
        }
    }
    if (!bRes) {
        PrintMsg(fun, FEHLER, "Failure to update/insert Season group (ArticleNo '%s')", pArt_no);
        return false;
    }

    return true;
}

bool ExistMasterArticle(char *ArticleNo, SetTablesToFromRowMap *masterTableMap) {
    exec sql begin declare section;
    char tmpSql[4096];
    exec sql end declare section;
    char *trimStr = NULL;

    // get Fields
    for (int i =0; i < masterTableMap->countMaps; i++) {
        TableToFromRowMapToSQLSel(&masterTableMap->maps[i], tmpSql, ArticleNo);
        // execute sql
        EXEC SQL PREPARE preSelArticleE from :tmpSql;
        EXEC SQL DECLARE curSelArticleE cursor with hold for preSelArticleE;
        if (SQLCODE < 0)
        {
          // failed to create Cursor SelArticle
          return false;
        }
        exec sql free preSelArticleE;
        EXEC SQL OPEN curSelArticleE;
        EXEC SQL FETCH curSelArticleE into ESQL_ROWS_INTO;

        if (NOT_FOUND) {
            if (masterTableMap->maps[i].master) {
              exec sql free curSelArticleE;
              return false;
            } else {
              exec sql free curSelArticleE;
              continue;
            }
        }

    }
    return true;
}

void ExistStageoutArticle(bool *existArticle, bool *existPackageUnit) {
    exec sql begin declare section;
    char tmpSql[4096] = "";
    char artNo[32] = "";
    exec sql end declare section;

    if (existArticle != NULL) {
        PSQL_STR_SELECT_EXIST_ARTICLE_ZARTIKEL(tmpSql);
        // execute sql
        EXEC SQL PREPARE preSelArticleEx from :tmpSql;
        EXEC SQL DECLARE curSelArticleEx cursor with hold for preSelArticleEx;
        if (SQLCODE < 0) {
          // failed to create Cursor SelArticle
          *existArticle = false;
        } else {
            exec sql free preSelArticleEx;
            EXEC SQL OPEN curSelArticleEx using :esqlRows[OARTICLE_NO_IDX];
            EXEC SQL FETCH curSelArticleEx into :artNo;
            *existArticle = (SQLCODE == 0);
        }
    }

    if (existPackageUnit != NULL) {
        PSQL_STR_SELECT_EXIST_PACKAGE_UNIT_ARTVE(tmpSql);
        // execute sql
        EXEC SQL PREPARE preSelPackageUEx from :tmpSql;
        EXEC SQL DECLARE curSelPackageUEx cursor with hold for preSelPackageUEx;
        if (SQLCODE < 0)
        {
          // failed to create Cursor SelArticle
          *existPackageUnit = false;
        } else {
            exec sql free preSelPackageUEx;
            EXEC SQL OPEN curSelPackageUEx using :esqlRows[OARTICLE_NO_IDX];
            EXEC SQL FETCH curSelPackageUEx into :artNo;
            *existPackageUnit = (SQLCODE == 0);
        }
    }
}

bool ExistStageoutArticleCode() {
    exec sql begin declare section;
    char tmpSql[4096] = "";
    char artNo[32] = "";
    exec sql end declare section;

    PSQL_STR_SELECT_EXIST_ARTICLECODES(tmpSql);
    // execute sql
    EXEC SQL PREPARE preSelArticleCodeEx from :tmpSql;
    EXEC SQL DECLARE curSelArticleCodeEx cursor with hold for preSelArticleCodeEx;
    if (SQLCODE < 0) {
      // failed to create Cursor SelArticleCode
      return false;
    }
    exec sql free preSelArticleCodeEx;
    EXEC SQL OPEN curSelArticleCodeEx using :esqlRows[OARTICLE_CODES_ARTICLENO_IDX], :esqlRows[OARTICLE_CODES_CODE_TYPE_IDX];
    EXEC SQL FETCH curSelArticleCodeEx into :artNo;

    return (SQLCODE == 0);
}

bool ExistStageoutArticleFrance() {
    exec sql begin declare section;
    char tmpSql[4096] = "";
    char artNo[32] = "";
    exec sql end declare section;

    PSQL_STR_SELECT_EXIST_FRANCE_ZARTFRANCE(tmpSql);
    // execute sql
    EXEC SQL PREPARE preSelArticleFranceEx from :tmpSql;
    EXEC SQL DECLARE curSelArticleFranceEx cursor with hold for preSelArticleFranceEx;
    if (SQLCODE < 0) {
      // failed to create Cursor SelArticleFrance
      return false;
    }
    exec sql free preSelArticleFranceEx;
    EXEC SQL OPEN curSelArticleFranceEx using :esqlRows[OARTICLE_FRANCE_ARTICLE_NO_IDX];
    EXEC SQL FETCH curSelArticleFranceEx into :artNo;

    return (SQLCODE == 0);
}

bool ExistStageoutArticlePrice() {
    exec sql begin declare section;
    char tmpSql[4096] = "";
    char artNo[32] = "";
    exec sql end declare section;

    PSQL_STR_SELECT_EXIST_PRICE_ZARTPREIS(tmpSql);
    // execute sql
    EXEC SQL PREPARE preSelArticlePriceEx from :tmpSql;
    EXEC SQL DECLARE curSelArticlePriceEx cursor with hold for preSelArticlePriceEx;
    if (SQLCODE < 0) {
      // failed to create Cursor SelArticleCode
      return false;
    }
    exec sql free preSelArticlePriceEx;
    EXEC SQL OPEN curSelArticlePriceEx using :esqlRows[OARTICLE_PRICE_ARTICLE_NO_IDX], :esqlRows[OARTICLE_PRICE_DATE_VALID_FROM_IDX];
    EXEC SQL FETCH curSelArticlePriceEx into :artNo;

    return (SQLCODE == 0);

}

bool ExistSeasonGroup(char *article_no, char *grp) {
    exec sql begin declare section;
    char tmpSql[4096] = "";
    char artNo[32] = "";
    char *pInArtNo = article_no;
    char *pInGrp = grp;
    exec sql end declare section;

    PSQL_STR_SELECT_EXIST_SEASON_GROUP_ZARTWG(tmpSql);
    // execute sql
    EXEC SQL PREPARE preSelSeasonGroupEx from :tmpSql;
    EXEC SQL DECLARE curSelSeasonGroupEx cursor with hold for preSelSeasonGroupEx;
    if (SQLCODE < 0) {
      // failed to create Cursor SelSeasonGroup
      return false;
    }
    exec sql free preSelSeasonGroupEx;
    EXEC SQL OPEN curSelSeasonGroupEx using :pInArtNo, :pInGrp;
    EXEC SQL FETCH curSelSeasonGroupEx into :artNo;

    return (SQLCODE == 0);
}

// put stageout_article (in esqlRows) into pharmos db, try first an update, then insert
bool PutStageoutArticle()
{
    exec sql begin declare section;
    char tmpSql[8192] = "";
    double updateCount = 0.0;
    exec sql end declare section;
    char fieldV[256];
    char *fun="PutStageoutArticle()";
    bool existArticle = false;
    bool existPackageUnit = false;

    TrimStr(esqlRows[OARTICLE_NO_IDX]);
    ExistStageoutArticle(&existArticle, &existPackageUnit);

    for (int i =0; i < mapArticleRow.countMaps; i++) {
        // build update sql request ********************
        if ((i==0 && existArticle) || (i==1 && existPackageUnit))  {
            strcpy(tmpSql, "UPDATE ");
            strcat(tmpSql, mapArticleRow.maps[i].nameDbTable);
            strcat(tmpSql, " SET ");
            for (int j = 0; j < mapArticleRow.maps[i].countFields; j++) {
                strcat(tmpSql, mapArticleRow.maps[i].elemsMap[j].FieldsName);
                strcat(tmpSql, "='");
                CopyStageoutToPharmos(fieldV, esqlRows[mapArticleRow.maps[i].elemsMap[j].mapToFromRowIdx], mapArticleRow.maps[i].elemsMap[j].Type);
                strcat(tmpSql, fieldV);
                // not last field ?
                if (j < mapArticleRow.maps[i].countFields - 1) {
                    strcat(tmpSql, "', ");
                }
            }
            strcat(tmpSql, "' WHERE ");
            strcat(tmpSql, mapArticleRow.maps[i].IDFieldName);
            strcat(tmpSql, " = '");
            strcat(tmpSql, esqlRows[OARTICLE_NO_IDX]);
            strcat(tmpSql, "'");
            EXEC SQL PREPARE updateCocp_article from : tmpSql;
            exec sql execute updateCocp_article;
            PrintMsg(fun, HINWEIS, "%i SQL UPDATE:<<%s>>, SQLCODE:<<%i>>", i, tmpSql,SQLCODE);
            EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
            if (db_exception_count > 1 || db_row_count <= 0) {
                PrintMsg(fun, FEHLER, "Update failed!");
                return false;
            }
        } else { // insert
            // build insert sql request **************************
            strcpy(tmpSql, "INSERT INTO ");
            strcat(tmpSql, mapArticleRow.maps[i].nameDbTable);
            // field names
            strcat(tmpSql, " ( ");
            if (!mapArticleRow.maps[i].master) {
                strcat(tmpSql, mapArticleRow.maps[i].IDFieldName);
                if (mapArticleRow.maps[i].countFields > 0) {
                    strcat(tmpSql, ", ");
                }
            }
            for (int j = 0; j < mapArticleRow.maps[i].countFields; j++) {
                strcat(tmpSql, mapArticleRow.maps[i].elemsMap[j].FieldsName);
                // not last field ?
                if (j < mapArticleRow.maps[i].countFields - 1) {
                    strcat(tmpSql, ", ");
                }
            }
            strcat(tmpSql, ") ");
            // values
            strcat(tmpSql, " VALUES ( ");
            if (!mapArticleRow.maps[i].master) {
                strcat(tmpSql, "'");
                strcat(tmpSql, esqlRows[OARTICLE_NO_IDX]);
                strcat(tmpSql, "'");

                if (mapArticleRow.maps[i].countFields > 0) {
                    strcat(tmpSql, ", ");
                }
            }
            for (int j = 0; j < mapArticleRow.maps[i].countFields; j++) {
                CopyStageoutToPharmos(fieldV, esqlRows[mapArticleRow.maps[i].elemsMap[j].mapToFromRowIdx], mapArticleRow.maps[i].elemsMap[j].Type);
                strcat(tmpSql,"'");
                strcat(tmpSql, fieldV);
                // not last field ?
                if (j < mapArticleRow.maps[i].countFields - 1) {
                    strcat(tmpSql, "', ");
                }
            }
            strcat(tmpSql, "')");
            PrintMsg(fun, HINWEIS, "%i SQL INSERT :<<%s>>", i, tmpSql);
            EXEC SQL EXECUTE IMMEDIATE :tmpSql;
            if (SQLCODE != 0) {
                return false;
            }
        }
    }
    if (!PutSeasonGroup(esqlRows[OARTICLE_NO_IDX], esqlRows[OARTICLE_DKART_PRODUCT_GROUP_IDX], esqlRows[OARTICLE_SEASON_GROUP_1_IDX],
            esqlRows[OARTICLE_SEASON_GROUP_2_IDX], esqlRows[OARTICLE_SEASON_GROUP_3_IDX])) {
        return false;
    }
    return true;
}

bool GetStageoutArticleCode(CsvRow * outRow, char *ArticleNo, char *CodeType)
{
    exec sql begin declare section;
    char tmpSql[4096];
    exec sql end declare section;
    char trimCodeType[64] = "";
    // set default Values
    CsvRow_copy(outRow, oarticleCodesDefaultRow);

    strcpy(trimCodeType, CodeType);
    TrimStr(trimCodeType);
    // get Fields
    strcpy(tmpSql, "select articleno, code_type, article_code, preferred_flag, date_changed from carticlecodes where articleno='");
    strcat(tmpSql, ArticleNo);
    strcat(tmpSql, "' and code_type='");
    strcat(tmpSql, trimCodeType);
    strcat(tmpSql, "'");
    // prepare exec sql
    EXEC SQL PREPARE preSelArticleCode from :tmpSql;
    EXEC SQL DECLARE curSelArticleCode cursor with hold for preSelArticleCode;
    if (SQLCODE < 0)
    {
      // failed to create Cursor SelArticlePrice
        return false;
    }
    exec sql free preSelArticleCode;
    EXEC SQL OPEN curSelArticleCode;
    EXEC SQL FETCH curSelArticleCode into ESQL_ROWS_INTO;

    if (NOT_FOUND) {
        exec sql free curSelArticleCode;
        return false;
    }

    // copy extracted values
    for (int j = 0; j < mapArticleCodesRow.maps[0].countFields; j++) {
        CopyPharmosToStageout(outRow->fields[mapArticleCodesRow.maps[0].elemsMap[j].mapToFromRowIdx], esqlRows[j],
          mapArticleCodesRow.maps[0].elemsMap[j].Type);
    }
    exec sql free curSelArticleCode;
    return true;
}

bool PutStageoutArticleCode() {
    exec sql begin declare section;
    char tmpSql[8192] = "";
    exec sql end declare section;
    char fieldV[256];
    char *fun="PutStageoutArticleCode()";
    bool bExistC = false;

    TrimStr(esqlRows[OARTICLE_CODES_ARTICLENO_IDX]);
    TrimStr(esqlRows[OARTICLE_CODES_CODE_TYPE_IDX]);
    bExistC = ExistStageoutArticleCode();

    for (int i =0; i < mapArticleCodesRow.countMaps; i++) {
        // build update sql request ********************
        if (bExistC) {
            strcpy(tmpSql, "UPDATE ");
            strcat(tmpSql, mapArticleCodesRow.maps[i].nameDbTable);
            strcat(tmpSql, " SET ");
            for (int j = 0; j < mapArticleCodesRow.maps[i].countFields; j++) {
                strcat(tmpSql, mapArticleCodesRow.maps[i].elemsMap[j].FieldsName);
                strcat(tmpSql, "='");
                CopyStageoutToPharmos(fieldV, esqlRows[mapArticleCodesRow.maps[i].elemsMap[j].mapToFromRowIdx], mapArticleCodesRow.maps[i].elemsMap[j].Type);
                strcat(tmpSql, fieldV);
                // not last field ?
                if (j < mapArticleCodesRow.maps[i].countFields - 1) {
                    strcat(tmpSql, "', ");
                }
            }
            strcat(tmpSql, "' WHERE articleno = '");
            strcat(tmpSql, esqlRows[OARTICLE_CODES_ARTICLENO_IDX]);
            strcat(tmpSql, "' and code_type='");
            strcat(tmpSql, esqlRows[OARTICLE_CODES_CODE_TYPE_IDX]);
            strcat(tmpSql, "'");
            PrintMsg(fun, HINWEIS, "%i SQL UPDATE:<<%s>>", i, tmpSql);
            EXEC SQL PREPARE updateCocp_articleCode from : tmpSql;
            exec sql execute updateCocp_articleCode;
            EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
            if (db_exception_count > 1 || db_row_count <= 0) {
                PrintMsg(fun, FEHLER, "Update failed!");
                return false;
            }

        } else {
            // build insert sql request **************************
            strcpy(tmpSql, "INSERT INTO ");
            strcat(tmpSql, mapArticleCodesRow.maps[i].nameDbTable);
            // field names
            strcat(tmpSql, " ( ");
            for (int j = 0; j < mapArticleCodesRow.maps[i].countFields; j++) {
                strcat(tmpSql, mapArticleCodesRow.maps[i].elemsMap[j].FieldsName);
                // not last field ?
                if (j < mapArticleCodesRow.maps[i].countFields - 1) {
                    strcat(tmpSql, ", ");
                }
            }
            strcat(tmpSql, ") ");
            // values
            strcat(tmpSql, " VALUES ( ");
            for (int j = 0; j < mapArticleCodesRow.maps[i].countFields; j++) {
                CopyStageoutToPharmos(fieldV, esqlRows[mapArticleCodesRow.maps[i].elemsMap[j].mapToFromRowIdx], mapArticleCodesRow.maps[i].elemsMap[j].Type);
                strcat(tmpSql,"'");
                strcat(tmpSql, fieldV);
                // not last field ?
                if (j < mapArticleCodesRow.maps[i].countFields - 1) {
                    strcat(tmpSql, "', ");
                }
            }
            strcat(tmpSql, "')");
            PrintMsg(fun, HINWEIS, "%i SQL INSERT :<<%s>>", i, tmpSql);
            EXEC SQL EXECUTE IMMEDIATE :tmpSql;
            if (SQLCODE != 0) {
                return false;
            }
        }
    }
    return true;
}

bool GetOCPNoToArticleNo(char *OCP_ArticleNo, char *articleNo) {
    exec sql begin declare section;
    char resArtNo[32];
    char tmpSql[4096];
    exec sql end declare section;

    char *trimStr = NULL;

    strcpy(tmpSql, "SELECT articleno FROM carticlecodes ");
    strcat(tmpSql, "where article_code = '");
    strcat(tmpSql, OCP_ArticleNo);
    strcat(tmpSql, "' and code_type=27");
    EXEC SQL PREPARE preSelArticleNo from :tmpSql;
    EXEC SQL DECLARE curSelArticleNo cursor with hold for preSelArticleNo;

    EXEC SQL OPEN curSelArticleNo;
    EXEC SQL FETCH curSelArticleNo into :resArtNo;
    if (SQLCODE != 0)
    {
      strcpy(articleNo, "-1");
      exec sql free curSelArticleNo;
      return false;
    }
    trimStr =  _CsvParser_duplicate(resArtNo, 0, 1);

    strcpy(articleNo, trimStr);
    free(trimStr);
    exec sql free curSelArticleNo;
    return true;
}

bool GetTransferReadyOCPNo(char *OCP_ArticleNo, long ocpdate, long ocptime) {
    static char *validTransferSumStateList="'7','8','9'";
    char *fun="GetTransferReadyOCPNo()";
    bool articleReady = true;
    bool articleFranceReady = true;
    bool articlePriceReady = true;
    bool articleCodeReady = true;

    exec sql begin declare section;
    double countSql = 0.0;
    char tmpSql[4096];
    exec sql end declare section;

    // check Article
    sprintf(tmpSql, "select count(*) from cocp_stageout_article where ocp_article_no='%s' and sum_state_flags in (%s)", OCP_ArticleNo, validTransferSumStateList);

    EXEC SQL PREPARE preSelArticleReadyNo from :tmpSql;
    EXEC SQL DECLARE curSelArticleReadyNo cursor with hold for preSelArticleReadyNo;
    EXEC SQL FREE preSelArticleReadyNo;
    EXEC SQL OPEN curSelArticleReadyNo;
    EXEC SQL FETCH curSelArticleReadyNo into :countSql;
    if (SQLCODE != 0 || countSql == 0.0) {
        articleReady = false;
    }

    // check Article france ///////////
    sprintf(tmpSql, "select count(*) from cocp_stageout_article_france where ocp_article_no='%s' and sum_state_flags in (%s)", OCP_ArticleNo, validTransferSumStateList);

    EXEC SQL PREPARE preSelArticleFranceReadyNo from :tmpSql;
    EXEC SQL DECLARE curSelArticleFranceReadyNo cursor with hold for preSelArticleFranceReadyNo;
    EXEC SQL FREE preSelArticleFranceReadyNo;
    EXEC SQL OPEN curSelArticleFranceReadyNo;
    EXEC SQL FETCH curSelArticleFranceReadyNo into :countSql;
    if (SQLCODE != 0 || countSql == 0.0) {
        articleFranceReady = false;
    }
    // check article price ///////////
    // count not ready price ?
    sprintf(tmpSql, "select count(*) from cocp_stageout_articleprice where ocp_article_no='%s' and sum_state_flags not in (%s) "\
        "and lastchange_date=%i and lastchange_time=%i" , OCP_ArticleNo, validTransferSumStateList, ocpdate, ocptime);

    EXEC SQL PREPARE preSelArticlePriceReadyNo from :tmpSql;
    EXEC SQL DECLARE curSelArticlePriceReadyNo cursor with hold for preSelArticlePriceReadyNo;
    EXEC SQL FREE preSelArticlePriceReadyNo;
    EXEC SQL OPEN curSelArticlePriceReadyNo;
    EXEC SQL FETCH curSelArticlePriceReadyNo into :countSql;
    if (SQLCODE != 0 || countSql > 0.0) {
        articlePriceReady = false;
    }

    // check article code ///////////
    // count not ready code ?
    sprintf(tmpSql, "select count(*) from cocp_stageout_articlecode where ocp_article_no='%s' and sum_state_flags not in (%s) "\
        "and lastchange_date=%i and lastchange_time=%i" , OCP_ArticleNo, validTransferSumStateList, ocpdate, ocptime);

    EXEC SQL PREPARE preSelArticleCodeReadyNo from :tmpSql;
    EXEC SQL DECLARE curSelArticleCodeReadyNo cursor with hold for preSelArticleCodeReadyNo;
    EXEC SQL FREE preSelArticleCodeReadyNo;
    EXEC SQL OPEN curSelArticleCodeReadyNo;
    EXEC SQL FETCH curSelArticleCodeReadyNo into :countSql;
    if (SQLCODE != 0 || countSql > 0.0) {
        articleCodeReady = false;
    }

    EXEC SQL FREE curSelArticleReadyNo;
    EXEC SQL FREE curSelArticleFranceReadyNo;
    EXEC SQL FREE curSelArticlePriceReadyNo;
    EXEC SQL FREE curSelArticleCodeReadyNo;

    if (articleReady && articleFranceReady &&  articlePriceReady && articleCodeReady) {
        PrintMsg(fun, HINWEIS, "ArticleOCPNo '%s', (date %08i/time %06i) Ready for transfer", OCP_ArticleNo, ocpdate, ocptime);
        return true;
    }
    PrintMsg(fun, FEHLER, "ArticleOCPNo '%s', (date %08i/time %06i) Not Ready for transfer! (Article|Price|France|Code)(%i|%i|%i|%i)",
        OCP_ArticleNo, ocpdate, ocptime, articleReady, articlePriceReady, articleFranceReady, articleCodeReady);
    return false;

}

bool GetStageoutArticlePrice(CsvRow *outRow, char *date_valid, char *ArticleNo) {

    exec sql begin declare section;
    char tmpSql[4096];
    exec sql end declare section;
    char *trimStr = NULL;
    // init with default Values
    CsvRow_copy(outRow, oarticlePriceDefaultRow);

    TableToFromRowMapToSQLSel(&mapArticlePriceRow.maps[0], tmpSql, ArticleNo);
    // and date_valid_from condition
    strcat(tmpSql, " and datumgueltigab='");
    strcat(tmpSql, date_valid);
    strcat(tmpSql, "'");

    // prepare sql, exec sql
    EXEC SQL PREPARE preSelArticlePrice from :tmpSql;
    EXEC SQL DECLARE curSelArticlePrice cursor with hold for preSelArticlePrice;
    if (SQLCODE < 0)
    {
      // failed to create Cursor SelArticlePrice
      return false;
    }
    exec sql free preSelArticlePrice;
    EXEC SQL OPEN curSelArticlePrice;
    EXEC SQL FETCH curSelArticlePrice into ESQL_ROWS_INTO;

    if (NOT_FOUND)
    {
      // failed to fetch Cursor ArticlePrice
      exec sql free curSelArticlePrice;
      return false;
    }

    // copy extracted values
    for (int j = 0; j < mapArticlePriceRow.maps[0].countFields; j++) {
        CopyPharmosToStageout(outRow->fields[mapArticlePriceRow.maps[0].elemsMap[j].mapToFromRowIdx], esqlRows[j],
          mapArticlePriceRow.maps[0].elemsMap[j].Type);
    }
    exec sql free curSelArticlePrice;
    return true;
}

bool PutStageoutArticlePrice() {
    exec sql begin declare section;
    char tmpSql[8192] = "";
    exec sql end declare section;
    char fieldV[256];
    char *fun="PutStageoutArticlePrice()";
    bool bExistP = false;

    TrimStr(esqlRows[OARTICLE_PRICE_ARTICLE_NO_IDX]);
    TrimStr(esqlRows[OARTICLE_PRICE_DATE_VALID_FROM_IDX]);
    bExistP = ExistStageoutArticlePrice();

    for (int i =0; i < mapArticlePriceRow.countMaps; i++) {
        // build update sql request ********************
        if (bExistP) {
            strcpy(tmpSql, "UPDATE ");
            strcat(tmpSql, mapArticlePriceRow.maps[i].nameDbTable);
            strcat(tmpSql, " SET ");
            for (int j = 0; j < mapArticlePriceRow.maps[i].countFields; j++) {
                strcat(tmpSql, mapArticlePriceRow.maps[i].elemsMap[j].FieldsName);
                strcat(tmpSql, "='");
                CopyStageoutToPharmos(fieldV, esqlRows[mapArticlePriceRow.maps[i].elemsMap[j].mapToFromRowIdx], mapArticlePriceRow.maps[i].elemsMap[j].Type);
                strcat(tmpSql, fieldV);
                // not last field ?
                if (j < mapArticlePriceRow.maps[i].countFields - 1) {
                    strcat(tmpSql, "', ");
                }
            }
            strcat(tmpSql, "' WHERE ");
            strcat(tmpSql, mapArticlePriceRow.maps[i].IDFieldName);
            strcat(tmpSql, " = '");
            strcat(tmpSql, esqlRows[OARTICLE_PRICE_ARTICLE_NO_IDX]);
            strcat(tmpSql, "' and datumgueltigab ='");
            strcat(tmpSql, esqlRows[OARTICLE_PRICE_DATE_VALID_FROM_IDX]);
            strcat(tmpSql, "'");
            PrintMsg(fun, HINWEIS, "%i SQL UPDATE:<<%s>>", i, tmpSql);
            EXEC SQL PREPARE updateCocp_articlePrice from : tmpSql;
            exec sql execute updateCocp_articlePrice;
            EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
            if (db_exception_count > 1 || db_row_count <= 0) {
                PrintMsg(fun, FEHLER, "Update failed!");
                return false;
            }
        } else {
            // build insert sql request **************************
            strcpy(tmpSql, "INSERT INTO ");
            strcat(tmpSql, mapArticlePriceRow.maps[i].nameDbTable);
            // field names
            strcat(tmpSql, " ( ");
            if (!mapArticlePriceRow.maps[i].master) {
                strcat(tmpSql, mapArticlePriceRow.maps[i].IDFieldName);
                if (mapArticlePriceRow.maps[i].countFields > 0) {
                    strcat(tmpSql, ", ");
                }
            }
            for (int j = 0; j < mapArticlePriceRow.maps[i].countFields; j++) {
                strcat(tmpSql, mapArticlePriceRow.maps[i].elemsMap[j].FieldsName);
                // not last field ?
                if (j < mapArticlePriceRow.maps[i].countFields - 1) {
                    strcat(tmpSql, ", ");
                }
            }
            strcat(tmpSql, ") ");
            // values
            strcat(tmpSql, " VALUES ( ");
            if (!mapArticlePriceRow.maps[i].master) {
                strcat(tmpSql, "'");
                strcat(tmpSql, esqlRows[OARTICLE_PRICE_ARTICLE_NO_IDX]);
                strcat(tmpSql, "'");

                if (mapArticlePriceRow.maps[i].countFields > 0) {
                    strcat(tmpSql, ", ");
                }
            }
            for (int j = 0; j < mapArticlePriceRow.maps[i].countFields; j++) {
                CopyStageoutToPharmos(fieldV, esqlRows[mapArticlePriceRow.maps[i].elemsMap[j].mapToFromRowIdx], mapArticlePriceRow.maps[i].elemsMap[j].Type);
                strcat(tmpSql,"'");
                strcat(tmpSql, fieldV);
                // not last field ?
                if (j < mapArticlePriceRow.maps[i].countFields - 1) {
                    strcat(tmpSql, "', ");
                }
            }
            strcat(tmpSql, "')");
            PrintMsg(fun, HINWEIS, "%i SQL INSERT :<<%s>>", i, tmpSql);
            EXEC SQL EXECUTE IMMEDIATE :tmpSql;
            if (SQLCODE!=0) {
                return false;
            }
        }
    }
    return true;
}


bool GetStageoutArticleFrance(CsvRow * outRow, char *ArticleNo)
{
    exec sql begin declare section;
    char tmpSql[4096];
    exec sql end declare section;
    char *trimStr = NULL;

    // set default Values
    CsvRow_copy(outRow, oarticleFranceDefaultRow);

    // get Fields
    for (int i =0; i < mapArticleFranceRow.countMaps; i++) {
        TableToFromRowMapToSQLSel(&mapArticleFranceRow.maps[i], tmpSql, ArticleNo);
        // execute sql
        // prepare sql, exec sql
        EXEC SQL PREPARE preSelArticleFrance from :tmpSql;
        EXEC SQL DECLARE curSelArticleFrance cursor with hold for preSelArticleFrance;
        if (SQLCODE < 0)
        {
          // failed to create Cursor SelArticleFrance
          return false;
        }
        exec sql free preSelArticleFrance;
        EXEC SQL OPEN curSelArticleFrance;
        EXEC SQL FETCH curSelArticleFrance into ESQL_ROWS_INTO;
        if (NOT_FOUND)
        {
            // failed to fetch Cursor ArticlePrice
            exec sql free curSelArticleFrance;
            if (mapArticleRow.maps[i].master) {
                return false;
            } else {
                continue;
            }
        }

        // copy extracted values
        for (int j = 0; j < mapArticleFranceRow.maps[i].countFields; j++) {
            CopyPharmosToStageout(outRow->fields[mapArticleFranceRow.maps[i].elemsMap[j].mapToFromRowIdx], esqlRows[j],
              mapArticleFranceRow.maps[i].elemsMap[j].Type);
        }
    }
    return true;
}

bool PutStageoutArticleFrance() {
    exec sql begin declare section;
    char tmpSql[8192] = "";
    exec sql end declare section;
    char fieldV[256];
    char *fun="PutStageoutArticleFrance()";
    bool bExistF = false;


    TrimStr(esqlRows[OARTICLE_FRANCE_ARTICLE_NO_IDX]);
    bExistF = ExistStageoutArticleFrance();

    for (int i =0; i < mapArticleFranceRow.countMaps; i++) {
        // build update sql request ********************
        if (bExistF) {
            strcpy(tmpSql, "UPDATE ");
            strcat(tmpSql, mapArticleFranceRow.maps[i].nameDbTable);
            strcat(tmpSql, " SET ");
            for (int j = 0; j < mapArticleFranceRow.maps[i].countFields; j++) {
                strcat(tmpSql, mapArticleFranceRow.maps[i].elemsMap[j].FieldsName);
                strcat(tmpSql, "='");
                CopyStageoutToPharmos(fieldV, esqlRows[mapArticleFranceRow.maps[i].elemsMap[j].mapToFromRowIdx], mapArticleFranceRow.maps[i].elemsMap[j].Type);
                strcat(tmpSql, fieldV);

                // not last field ?
                if (j < mapArticleFranceRow.maps[i].countFields - 1) {
                    strcat(tmpSql, "', ");
                }
            }
            strcat(tmpSql, "' WHERE ");
            strcat(tmpSql, mapArticleFranceRow.maps[i].IDFieldName);
            strcat(tmpSql, " = '");
            strcat(tmpSql, esqlRows[OARTICLE_FRANCE_ARTICLE_NO_IDX]);
            strcat(tmpSql, "'");
            PrintMsg(fun, HINWEIS, "%i SQL UPDATE:<<%s>>", i, tmpSql);
            EXEC SQL PREPARE updateCocp_articleFrance from : tmpSql;
            exec sql execute updateCocp_articleFrance;
            EXEC SQL get diagnostics :db_exception_count = NUMBER, :db_row_count = ROW_COUNT;
            if (db_exception_count > 1 || db_row_count <= 0) {
                PrintMsg(fun, FEHLER, "Update failed!");
                return false;
            }
        } else {
            // build insert sql request **************************
            strcpy(tmpSql, "INSERT INTO ");
            strcat(tmpSql, mapArticleFranceRow.maps[i].nameDbTable);
            // field names
            strcat(tmpSql, " ( ");
            if (!mapArticlePriceRow.maps[i].master) {
                strcat(tmpSql, mapArticleFranceRow.maps[i].IDFieldName);
                if (mapArticleFranceRow.maps[i].countFields > 0) {
                    strcat(tmpSql, ", ");
                }
            }
            for (int j = 0; j < mapArticleFranceRow.maps[i].countFields; j++) {
                strcat(tmpSql, mapArticleFranceRow.maps[i].elemsMap[j].FieldsName);
                // not last field ?
                if (j < mapArticleFranceRow.maps[i].countFields - 1) {
                    strcat(tmpSql, ", ");
                }
            }
            strcat(tmpSql, ") ");
            // values
            strcat(tmpSql, " VALUES ( ");
            if (!mapArticleFranceRow.maps[i].master) {
                strcat(tmpSql, "'");
                strcat(tmpSql, esqlRows[OARTICLE_FRANCE_ARTICLE_NO_IDX]);
                strcat(tmpSql, "'");

                if (mapArticleFranceRow.maps[i].countFields > 0) {
                    strcat(tmpSql, ", ");
                }
            }
            for (int j = 0; j < mapArticleFranceRow.maps[i].countFields; j++) {
                strcat(tmpSql,"'");
                CopyStageoutToPharmos(fieldV, esqlRows[mapArticleFranceRow.maps[i].elemsMap[j].mapToFromRowIdx], mapArticleFranceRow.maps[i].elemsMap[j].Type);
                strcat(tmpSql, fieldV);
                // not last field ?
                if (j < mapArticleFranceRow.maps[i].countFields - 1) {
                    strcat(tmpSql, "', ");
                }
            }
            strcat(tmpSql, "')");
            PrintMsg(fun, HINWEIS, "%i SQL INSERT :<<%s>>", i, tmpSql);
            EXEC SQL EXECUTE IMMEDIATE :tmpSql;
            if (SQLCODE != 0) {
                return false;
            }
        }
    }
    return true;
}


void GetStageoutArticleFromStagein(CsvRow * outRow, char **stageinRow, char *ArticleNo) {
    int inPckgUnit1 = atoi(stageinRow[ARTICLE_PACKAGE_UNIT_1_IDX]);
    int inPckgUnit2 = atoi(stageinRow[ARTICLE_PACKAGE_UNIT_2_IDX]);
    int inPckgUnit3 = atoi(stageinRow[ARTICLE_PACKAGE_UNIT_3_IDX]);
    int inPckgUnit4 = atoi(stageinRow[ARTICLE_PACKAGE_UNIT_4_IDX]);
    bool bGetPharmosRow = (inPckgUnit1 == 0 || inPckgUnit2 == 0 || inPckgUnit3 == 0 || inPckgUnit4 == 0);
    bool bValidPharmosRow = false;
    CsvRow *pharmosRow = (bGetPharmosRow) ? (CsvRow_Create(OARTICLE_FIELDS_COUNT, CSVFORMAT_MAX_COLUMN_SIZE)) : NULL;

    // copy default stageout article values
    strcpy(outRow->fields[OARTICLE_OCP_NO_IDX              ] , stageinRow[OCP_ARTICLE_NO_IDX]                 );
    strcpy(outRow->fields[OARTICLE_NO_IDX                  ] , ArticleNo                                      );
    strcpy(outRow->fields[OARTICLE_LONG_NAME_IDX           ] , stageinRow[ARTICLE_LONG_NAME_IDX             ] );
    strcpy(outRow->fields[OARTICLE_DOSAGE_FORM_IDX         ] , "0" ); // stageout DosageFORM from pharmos else take 0 value
    strcpy(outRow->fields[OARTICLE_PRODUCT_TYPE_IDX        ] , "0" ); // stageout productType from pharmos else take 0 value
    strcpy(outRow->fields[OARTICLE_MANUFACTURER_NO_IDX     ] , "0" ); // stageout manufacturer_id from pharmos else take 0 value
    strcpy(outRow->fields[OARTICLE_AWL1_IDX                ] , "0" ); // stageout supplier_id from pharmos else take 0 value
    strcpy(outRow->fields[OARTICLE_UNIT_IDX                ] , "0" ); // stageout Unit from pharmos else take 0 value
    strcpy(outRow->fields[OARTICLE_LENGTH_IDX              ] , stageinRow[ARTICLE_LENGTH_IDX                ] );
    strcpy(outRow->fields[OARTICLE_WIDTH_IDX               ] , stageinRow[ARTICLE_WIDTH_IDX                 ] );
    strcpy(outRow->fields[OARTICLE_HEIGHT_IDX              ] , stageinRow[ARTICLE_HEIGHT_IDX                ] );
    strcpy(outRow->fields[OARTICLE_WEIGHT_IDX              ] , stageinRow[ARTICLE_WEIGHT_IDX                ] );
    strcpy(outRow->fields[OARTICLE_PACKAGE_UNIT_1_IDX      ] , stageinRow[ARTICLE_PACKAGE_UNIT_1_IDX        ] );
    strcpy(outRow->fields[OARTICLE_PACKAGE_UNIT_2_IDX      ] , stageinRow[ARTICLE_PACKAGE_UNIT_2_IDX        ] );
    strcpy(outRow->fields[OARTICLE_PACKAGE_UNIT_3_IDX      ] , stageinRow[ARTICLE_PACKAGE_UNIT_3_IDX        ] );
    strcpy(outRow->fields[OARTICLE_PACKAGE_UNIT_4_IDX      ] , stageinRow[ARTICLE_PACKAGE_UNIT_4_IDX        ] );
    strcpy(outRow->fields[OARTICLE_CREATION_DATE_IDX       ] , stageinRow[ARTICLE_CREATION_DATE_IDX         ] );
    strcpy(outRow->fields[OARTICLE_MODIFICATION_DATE_IDX   ] , stageinRow[ARTICLE_MODIFICATION_DATE_IDX     ] );
    strcpy(outRow->fields[OARTICLE_EXPIRY_DATE_IDX         ] , stageinRow[ARTICLE_EXPIRY_DATE_IDX           ] );
    strcpy(outRow->fields[OARTICLE_OUT_OF_MARKET_DATE_IDX  ] , stageinRow[ARTICLE_OUT_OF_MARKET_DATE_IDX    ] );
    strcpy(outRow->fields[OARTICLE_DURATION_MONTHS_IDX     ] , stageinRow[ARTICLE_DURATION_MONTHS_IDX       ] );
    strcpy(outRow->fields[OARTICLE_NEGATIVE_LIST_IDX       ] , stageinRow[ARTICLE_NEGATIVE_LIST_IDX         ] );
    strcpy(outRow->fields[OARTICLE_BATCH_ARTICLE_IDX       ] , stageinRow[ARTICLE_BATCH_ARTICLE_IDX         ] );
    strcpy(outRow->fields[OARTICLE_COOLING_ARTICLE_IDX     ] , stageinRow[ARTICLE_COOLING_ARTICLE_IDX       ] );
    strcpy(outRow->fields[OARTICLE_NARCOTICS_IDX           ] , stageinRow[ARTICLE_NARCOTICS_IDX             ] );
    strcpy(outRow->fields[OARTICLE_FMD_IDX                 ] , stageinRow[ARTICLE_FMD_RELEVANT_IDX          ] );
    strcpy(outRow->fields[OARTICLE_VETERINARY_IDX          ] , stageinRow[ARTICLE_VETERINARY_IDX            ] );
    strcpy(outRow->fields[OARTICLE_PRESCRIPTION_NEEDED_IDX ] , stageinRow[ARTICLE_PRESCRIPTION_NEEDED_IDX   ] );
    strcpy(outRow->fields[OARTICLE_PSYCHOTROPE_IDX         ] , stageinRow[ARTICLE_PSYCHOTROPE_IDX           ] );
    strcpy(outRow->fields[OARTICLE_ZYTOSTATIC_IDX          ] , stageinRow[ARTICLE_ZYTOSTATIC_IDX            ] );
    strcpy(outRow->fields[OARTICLE_BLOCKED_IDX             ] , stageinRow[ARTICLE_BLOCKED_IDX               ] );
    strcpy(outRow->fields[OARTICLE_NOT_ALLOWED_IDX         ] , stageinRow[ARTICLE_NOT_ALLOWED_IDX           ] );
    strcpy(outRow->fields[OARTICLE_TAX_IDX                 ] , stageinRow[ARTICLE_TAX_IDX                   ] );
    strcpy(outRow->fields[OARTICLE_PHARMACY_ONLY_IDX       ] , stageinRow[ARTICLE_PHARMACY_ONLY_IDX         ] );
    strcpy(outRow->fields[OARTICLE_MEDICATION_IDX          ] , stageinRow[ARTICLE_MEDICATION_IDX            ] );
    strcpy(outRow->fields[OARTICLE_TOXIC_IDX               ] , stageinRow[ARTICLE_TOXIC_IDX                 ] );
    strcpy(outRow->fields[OARTICLE_VERY_TOXIC_IDX          ] , stageinRow[ARTICLE_VERY_TOXIC_IDX            ] );
    strcpy(outRow->fields[OARTICLE_HARMFUL_IDX             ] , stageinRow[ARTICLE_HARMFUL_IDX               ] );
    strcpy(outRow->fields[OARTICLE_HOMEOPATHY_IDX          ] , stageinRow[ARTICLE_HOMEOPATHY_IDX            ] );
    strcpy(outRow->fields[OARTICLE_MEDICAL_GASES_IDX       ] , stageinRow[ARTICLE_MEDICAL_GASES_IDX         ] );
    strcpy(outRow->fields[OARTICLE_ATC_CODE_IDX            ] , " "                                            );

    strcpy(outRow->fields[OARTICLE_STATE_FLAG_IDX          ] , "222222222222222222222222222222222222222222222" );
    strcpy(outRow->fields[OARTICLE_SUM_STATE_FLAG_IDX      ] , "2"                                         );
    strcpy(outRow->fields[OARTICLE_USERNAME_IDX            ] , "import"                                         );
    strcpy(outRow->fields[OARTICLE_LAST_CHANGE_DATE_IDX    ] , ""                                             );
    strcpy(outRow->fields[OARTICLE_LAST_CHANGE_TIME_IDX    ] , ""                                             );
    // handle season group ************************************
    TrimStr(stageinRow[ARTICLE_PRODUCT_GROUP_IDX]);
    // initial stagein / empty values
    strcpy(outRow->fields[OARTICLE_DKART_PRODUCT_GROUP_IDX ] , "" );
    strcpy(outRow->fields[OARTICLE_SEASON_GROUP_1_IDX      ] , "" );
    strcpy(outRow->fields[OARTICLE_SEASON_GROUP_2_IDX      ] , "" );
    strcpy(outRow->fields[OARTICLE_SEASON_GROUP_3_IDX      ] , "" );

    // get Pharmos Row if required
    if (bGetPharmosRow) {
        bValidPharmosRow = GetStageoutArticle(pharmosRow, ArticleNo);
    }

    // get pharmos season groups values, if a pharmosRow is already valid then use it
    if (!bGetPharmosRow) {
    GetSeasonGroup(ArticleNo, outRow->fields[OARTICLE_DKART_PRODUCT_GROUP_IDX], outRow->fields[OARTICLE_SEASON_GROUP_1_IDX],
        outRow->fields[OARTICLE_SEASON_GROUP_2_IDX], outRow->fields[OARTICLE_SEASON_GROUP_3_IDX]);
    } else if (bValidPharmosRow) {
        strcpy(outRow->fields[OARTICLE_DKART_PRODUCT_GROUP_IDX ] , pharmosRow->fields[OARTICLE_DKART_PRODUCT_GROUP_IDX ] );
        strcpy(outRow->fields[OARTICLE_SEASON_GROUP_1_IDX      ] , pharmosRow->fields[OARTICLE_SEASON_GROUP_1_IDX      ] );
        strcpy(outRow->fields[OARTICLE_SEASON_GROUP_2_IDX      ] , pharmosRow->fields[OARTICLE_SEASON_GROUP_2_IDX      ] );
        strcpy(outRow->fields[OARTICLE_SEASON_GROUP_3_IDX      ] , pharmosRow->fields[OARTICLE_SEASON_GROUP_3_IDX      ] );
    }

    // if pharmos DKART value exist take it, else take stagein value
    if (outRow->fields[OARTICLE_DKART_PRODUCT_GROUP_IDX][0] != 0) {
        outRow->fields[OARTICLE_STATE_FLAG_IDX][OARTICLE_DKART_PRODUCT_GROUP_IDX] = '1'; // update pharmos state for DKART
    } else {
        strcpy(outRow->fields[OARTICLE_DKART_PRODUCT_GROUP_IDX ] , stageinRow[ARTICLE_PRODUCT_GROUP_IDX] );
    }
    // if available pharmos value, modify the state to pharmos
    if (outRow->fields[OARTICLE_SEASON_GROUP_1_IDX][0] != 0) {
        outRow->fields[OARTICLE_STATE_FLAG_IDX][OARTICLE_SEASON_GROUP_1_IDX] = '1'; // pharmos state
    }

    if (outRow->fields[OARTICLE_SEASON_GROUP_2_IDX][0] != 0) {
        outRow->fields[OARTICLE_STATE_FLAG_IDX][OARTICLE_SEASON_GROUP_2_IDX] = '1'; // pharmos state
    }

    if (outRow->fields[OARTICLE_SEASON_GROUP_3_IDX][0] != 0) {
        outRow->fields[OARTICLE_STATE_FLAG_IDX][OARTICLE_SEASON_GROUP_3_IDX] = '1'; // pharmos state
    }

    // handle packageUnit values (take Pharmos value if inp value equal to zero):
    // if (bValidPharmosRow && stagein_pckgUnit[N] == 0) then (stageout_pckgUnit[N] = pharmos_pckgUnit[N]) else (stageout_pckgUnit[N] = stagein_pckgUnit[N]);
    if (bValidPharmosRow)
    {
        if (inPckgUnit1 == 0 && atoi(pharmosRow->fields[OARTICLE_PACKAGE_UNIT_1_IDX]) != 0) {
            strcpy(outRow->fields[OARTICLE_PACKAGE_UNIT_1_IDX], pharmosRow->fields[OARTICLE_PACKAGE_UNIT_1_IDX]);
            outRow->fields[OARTICLE_STATE_FLAG_IDX][OARTICLE_PACKAGE_UNIT_1_IDX] = '1'; // pharmos state
        }
        if (inPckgUnit2 == 0 && atoi(pharmosRow->fields[OARTICLE_PACKAGE_UNIT_2_IDX]) != 0) {
            strcpy(outRow->fields[OARTICLE_PACKAGE_UNIT_2_IDX], pharmosRow->fields[OARTICLE_PACKAGE_UNIT_2_IDX]);
            outRow->fields[OARTICLE_STATE_FLAG_IDX][OARTICLE_PACKAGE_UNIT_2_IDX] = '1'; // pharmos state
        }
        if (inPckgUnit3 == 0 && atoi(pharmosRow->fields[OARTICLE_PACKAGE_UNIT_3_IDX]) != 0) {
            strcpy(outRow->fields[OARTICLE_PACKAGE_UNIT_3_IDX], pharmosRow->fields[OARTICLE_PACKAGE_UNIT_3_IDX]);
            outRow->fields[OARTICLE_STATE_FLAG_IDX][OARTICLE_PACKAGE_UNIT_3_IDX] = '1'; // pharmos state
        }
        if (inPckgUnit4 == 0 && atoi(pharmosRow->fields[OARTICLE_PACKAGE_UNIT_4_IDX]) != 0) {
            strcpy(outRow->fields[OARTICLE_PACKAGE_UNIT_4_IDX], pharmosRow->fields[OARTICLE_PACKAGE_UNIT_4_IDX]);
            outRow->fields[OARTICLE_STATE_FLAG_IDX][OARTICLE_PACKAGE_UNIT_4_IDX] = '1'; // pharmos state
        }
    }

    // set count of fields
    outRow->numOfFields = OARTICLE_FIELDS_COUNT;

    // destroy Pharmos row if any
    if (bGetPharmosRow && pharmosRow != NULL)
    {
        CsvRow_destroy(pharmosRow);
    }
}

void GetStageoutArticleCodeFromStagein(CsvRow * outRow, char **stageinRow, char *ArticleNo)
{
    TrimStr(stageinRow[OCP_ARTICLE_NO_IDX]);
    TrimStr(stageinRow[ARTICLE_CODES_CODE_TYPE_IDX]);
    TrimStr(stageinRow[ARTICLE_CODES_ARTICLE_CODE_IDX]);


    strcpy(outRow->fields[OARTICLE_CODES_OCP_NO_IDX], stageinRow[OCP_ARTICLE_NO_IDX]);
    strcpy(outRow->fields[OARTICLE_CODES_ARTICLENO_IDX], ArticleNo);

    if (atoi(stageinRow[ARTICLE_CODES_CODE_TYPE_IDX]) == 27) {
        strcpy(outRow->fields[OARTICLE_CODES_ARTICLE_CODE_IDX], stageinRow[OCP_ARTICLE_NO_IDX]);
    } else {
        strcpy(outRow->fields[OARTICLE_CODES_ARTICLE_CODE_IDX], stageinRow[ARTICLE_CODES_ARTICLE_CODE_IDX]);
    }

    strcpy(outRow->fields[OARTICLE_CODES_CODE_TYPE_IDX           ] , stageinRow[ARTICLE_CODES_CODE_TYPE_IDX       ] );
    strcpy(outRow->fields[OARTICLE_CODES_PREFERRED_FLAG_IDX      ] , stageinRow[ARTICLE_CODES_PREFERRED_FLAG_IDX  ] );
    strcpy(outRow->fields[OARTICLE_CODES_DATE_CHANGED_IDX        ] , stageinRow[ARTICLE_CODES_CHANGED_DATE_IDX    ] );

    strcpy(outRow->fields[OARTICLE_CODES_STATE_FLAG_IDX          ] , "222222"          );
    strcpy(outRow->fields[OARTICLE_CODES_SUM_STATE_FLAG_IDX      ] , "2"                                         );
    strcpy(outRow->fields[OARTICLE_CODES_USERNAME_IDX            ] , "import"                                         );
    strcpy(outRow->fields[OARTICLE_CODES_LAST_CHANGE_DATE_IDX    ] , ""                                             );
    strcpy(outRow->fields[OARTICLE_CODES_LAST_CHANGE_TIME_IDX    ] , ""                                             );
    outRow->numOfFields = OARTICLE_CODES_FIELDS_COUNT;

}

// force '0' value for empty fields for (reserve_hosp, not_via_edi, code_bloquage, distr_restr_legall, distr_restr_breizh, distr_restr_hosp)

void GetStageoutArticleFranceFromStagein(CsvRow * outRow, char **stageinRow, char *ArticleNo) {
    char *zeroStr = "0";

    strcpy(outRow->fields[OARTICLE_FRANCE_OCP_NO_IDX              ] , stageinRow[OCP_ARTICLE_NO_IDX]                 );
    strcpy(outRow->fields[OARTICLE_FRANCE_ARTICLE_NO_IDX          ] , ArticleNo                                      );

    strcpy(outRow->fields[OARTICLE_FRANCE_REIMBURSEMENT_PERC_IDX ] , stageinRow[ARTICLE_FRANCE_REIMBURSEMENT_PERC_IDX  ] );
    strcpy(outRow->fields[OARTICLE_FRANCE_REIMBURSEMENT_VAL_IDX  ] , stageinRow[ARTICLE_FRANCE_REIMBURSEMENT_VAL_IDX   ] );
    strcpy(outRow->fields[OARTICLE_FRANCE_UNIT_MULTIPLE_IDX      ] , stageinRow[ARTICLE_FRANCE_UNIT_MULTIPLE_IDX       ] );
    strcpy(outRow->fields[OARTICLE_FRANCE_QTY_SUBMULTIPLE_IDX    ] , stageinRow[ARTICLE_FRANCE_QTY_SUBMULTIPLE_IDX     ] );
    CopyDefaultValueIfEmpty(outRow->fields[OARTICLE_FRANCE_RESERVE_HOSP_IDX] , stageinRow[ARTICLE_FRANCE_RESERVE_HOSP_IDX], zeroStr);
    strcpy(outRow->fields[OARTICLE_FRANCE_REIMBURSEMENT_TYPE_IDX ] , stageinRow[ARTICLE_FRANCE_REIMBURSEMENT_TYPE_IDX  ] );
    CopyDefaultValueIfEmpty(outRow->fields[OARTICLE_FRANCE_NOT_VIA_EDI_IDX        ] , stageinRow[ARTICLE_FRANCE_NOT_VIA_EDI_IDX         ], zeroStr);
    CopyDefaultValueIfEmpty(outRow->fields[OARTICLE_FRANCE_CODE_BLOCAGE_IDX       ] , stageinRow[ARTICLE_FRANCE_CODE_BLOCAGE_IDX        ], zeroStr);
    strcpy(outRow->fields[OARTICLE_FRANCE_CODE_LPPR_IDX          ] , stageinRow[ARTICLE_FRANCE_CODE_LPPR_IDX           ] );
    strcpy(outRow->fields[OARTICLE_FRANCE_TFR_BASE__PRICE_IDX    ] , stageinRow[ARTICLE_FRANCE_TFR_BASE_PRICE_IDX      ] );
    strcpy(outRow->fields[OARTICLE_FRANCE_DISTR_RESTR_EXPORT_IDX ] , stageinRow[ARTICLE_FRANCE_DISTR_RESTR_EXPORT_IDX  ] );
    CopyDefaultValueIfEmpty(outRow->fields[OARTICLE_FRANCE_DISTR_RESTR_LEGAL_IDX  ] , stageinRow[ARTICLE_FRANCE_DISTR_RESTR_LEGAL_IDX   ] , zeroStr);
    CopyDefaultValueIfEmpty(outRow->fields[OARTICLE_FRANCE_DISTR_RESTR_BREIZH_IDX ] , stageinRow[ARTICLE_FRANCE_DISTR_RESTR_BREIZH_IDX  ] , zeroStr);
    CopyDefaultValueIfEmpty(outRow->fields[OARTICLE_FRANCE_DISTR_RESTR_HOSP_IDX   ] , stageinRow[ARTICLE_FRANCE_DISTR_RESTR_HOSP_IDX    ] , zeroStr);
    strcpy(outRow->fields[OARTICLE_FRANCE_REBATE_GROUP_SPEC_IDX  ] , stageinRow[ARTICLE_FRANCE_REBATE_GROUP_SPEC_IDX   ] );

    strcpy(outRow->fields[OARTICLE_FRANCE_STATE_FLAG_IDX          ] , "22222222222222222"       );
    strcpy(outRow->fields[OARTICLE_FRANCE_SUM_STATE_FLAG_IDX      ] , "2"                                         );
    strcpy(outRow->fields[OARTICLE_FRANCE_USERNAME_IDX            ] , "import"                                         );
    strcpy(outRow->fields[OARTICLE_FRANCE_LAST_CHANGE_DATE_IDX    ] , ""                                             );
    strcpy(outRow->fields[OARTICLE_FRANCE_LAST_CHANGE_TIME_IDX    ] , ""                                             );

    outRow->numOfFields = OARTICLE_FRANCE_FIELDS_COUNT;
}

void GetStageoutArticlePriceFromStagein(CsvRow *outRow, char **stageinRow, char *ArticleNo) {
    strcpy(outRow->fields[OARTICLE_PRICE_OCP_NO_IDX               ] , stageinRow[OCP_ARTICLE_NO_IDX]                 );
    strcpy(outRow->fields[OARTICLE_PRICE_ARTICLE_NO_IDX           ] , ArticleNo                                      );

    strcpy(outRow->fields[OARTICLE_PRICE_DATE_VALID_FROM_IDX        ] , stageinRow[ARTICLE_PRICE_VALID_FROM_DATE_IDX          ]);
    strcpy(outRow->fields[OARTICLE_PRICE_GROUND_PRICE_IDX           ] , stageinRow[ARTICLE_PRICE_MANUFACTURER_BASE_PRICE_IDX  ]);
    strcpy(outRow->fields[OARTICLE_PRICE_PHARMACY_BUYING_PRICE_IDX  ] , stageinRow[ARTICLE_PRICE_PHARMACY_BUY_PRICE_IDX       ]);
    strcpy(outRow->fields[OARTICLE_PRICE_PHARMACY_SELLING_PRICE_IDX ] , stageinRow[ARTICLE_PRICE_PHARMACY_SELL_PRICE_IDX      ]);
    strcpy(outRow->fields[OARTICLE_PRICE_SUPPLIER_BASE_PRICE_IDX    ] , stageinRow[ARTICLE_PRICE_SUPPLIER_BASE_PRICE_IDX      ]);
    strcpy(outRow->fields[OARTICLE_PRICE_PHARMACY_BASE_PRICE_IDX    ] , stageinRow[ARTICLE_PRICE_PHARMACY_BASE_PRICE_IDX      ]);
    strcpy(outRow->fields[OARTICLE_PRICE_KE_MWST_IDX                ] , stageinRow[ARTICLE_PRICE_VAT_CODE_IDX                 ]);
    strcpy(outRow->fields[OARTICLE_PRICE_HERST_PROZENT_IDX          ] , stageinRow[ARTICLE_PRICE_MANUFACTURER_PERCENTAGE_IDX  ]);
    strcpy(outRow->fields[OARTICLE_PRICE_EAVP_IDX                   ] , stageinRow[ARTICLE_PRICE_RECOM_PHARMACY_SELL_PRICE_IDX]);
    strcpy(outRow->fields[OARTICLE_PRICE_MAX_AVP_IDX                ] , stageinRow[ARTICLE_PRICE_MAX_PHARMACY_SELL_PRICE_IDX  ]);
    strcpy(outRow->fields[OARTICLE_PRICE_PRICE_TYPE_IDX             ] , stageinRow[ARTICLE_PRICE_PRICE_TYPE_IDX               ]);
    strcpy(outRow->fields[OARTICLE_PRICE_PRICE_MODEL_IDX            ] , stageinRow[ARTICLE_PRICE_PRICE_MODEL_IDX              ]);
    strcpy(outRow->fields[OARTICLE_PRICE_MAX_AEP_IDX                ] , stageinRow[ARTICLE_PRICE_MAX_PHARMACY_BUY_PRICE_IDX   ]);
    strcpy(outRow->fields[OARTICLE_PRICE_ERSTATTBETRAG_IDX          ] , stageinRow[ARTICLE_PRICE_REFUND_AMOUNT                ]);
    strcpy(outRow->fields[OARTICLE_PRICE_DISC_DEDUCED_YET_IDX       ] , stageinRow[ARTICLE_PRICE_DISCOUNT_DEDUCED_YET_IDX     ]);
    strcpy(outRow->fields[OARTICLE_PRICE_PUBLICATION_NUMBER_IDX     ] , stageinRow[ARTICLE_PRICE_PUBLICATION_NUMBER_IDX       ]);

    strcpy(outRow->fields[OARTICLE_PRICE_STATE_FLAG_IDX           ] , "222222222222222222"       );
    strcpy(outRow->fields[OARTICLE_PRICE_SUM_STATE_FLAG_IDX       ] , "2"                                         );
    strcpy(outRow->fields[OARTICLE_PRICE_USERNAME_IDX             ] , "import"                                         );
    strcpy(outRow->fields[OARTICLE_PRICE_LAST_CHANGE_DATE_IDX     ] , ""                                             );
    strcpy(outRow->fields[OARTICLE_PRICE_LAST_CHANGE_TIME_IDX     ] , ""                                             );
    outRow->numOfFields = OARTICLE_PRICE_FIELDS_COUNT;
}

// functions that 'try' to fix/clean input rows

void CleanArticleStageinRow(char **inRow) {
    EnsureNotNullValues(inRow, ARTICLE_FIELDS_COUNT);
}

void CleanArticleCodeStageinRow(char **inRow) {
    EnsureNotNullValues(inRow, ARTICLE_CODES_FIELDS_COUNT);
}

void CleanArticlePriceStageinRow(char **inRow) {
    EnsureNotNullValues(inRow, ARTICLE_PRICE_FIELDS_COUNT);
    // replace any possible ',' with "." for decimal/float fields
    ReplaceCharStr(inRow[ARTICLE_PRICE_MANUFACTURER_BASE_PRICE_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_PRICE_PHARMACY_BUY_PRICE_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_PRICE_PHARMACY_SELL_PRICE_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_PRICE_MANUFACTURER_PERCENTAGE_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_PRICE_RECOM_PHARMACY_SELL_PRICE_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_PRICE_MAX_PHARMACY_SELL_PRICE_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_PRICE_SUPPLIER_BASE_PRICE_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_PRICE_MAX_PHARMACY_BUY_PRICE_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_PRICE_PHARMACY_BASE_PRICE_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_PRICE_REFUND_AMOUNT], ',', '.');
}

void CleanArticleFranceStageinRow(char **inRow) {
    EnsureNotNullValues(inRow, ARTICLE_FRANCE_FIELDS_COUNT);
    // replace any possible ',' with "." for decimal/float fields
    ReplaceCharStr(inRow[ARTICLE_FRANCE_REIMBURSEMENT_PERC_IDX], ',', '.');
    ReplaceCharStr(inRow[ARTICLE_FRANCE_REIMBURSEMENT_VAL_IDX], ',', '.');
}

// utils

void EnsureNotNullValues(char **stageinRow, int countValues)
{
    for (int i = 0; i < countValues;i++) {
        if (stageinRow[i][0] == 0) {
            strcpy(stageinRow[i], " ");
        }
    }
}

void EnsureNotNullRowValues(CsvRow *outRow) {
    for (int i = 0; i < outRow->numOfFields; i++) {
        if (outRow->fields[i][0] == 0) {
            strcpy(outRow->fields[i], " ");
        }
    }
}

void CopyDefaultValueIfEmpty(char *dst, char *src, char *defaultv) {
    char *trimVal = _CsvParser_duplicate(src, 0, 1);
    if (strlen(trimVal) == 0) {
        strcpy(dst, defaultv);
    } else {
        strcpy(dst, src);
    }
    free(trimVal);
}

void TrimStr(char *str) {
    int lenstr = (int)strlen(str);
    char *tmpStr = (char*)malloc(sizeof(char)*(lenstr+1));
    char *ptrCpy = str;

    // jump starting white spaces
    while(lenstr>0 && isspace(*ptrCpy)) {
        ptrCpy++;
        lenstr--;
    }
    // count endian white spaces
    while(lenstr>0 && isspace(ptrCpy[lenstr-1])) {
        lenstr--;
    }
    // copy result
    strncpy(tmpStr, ptrCpy, lenstr);
    tmpStr[lenstr] = 0;
    strcpy(str,tmpStr);
    free(tmpStr);
}

void ReplaceCharStr(char *str, char orgVal, char modVal) {
    char *ptrStr = str;
    while (ptrStr != NULL && *ptrStr != '\0') {
        if ((*ptrStr) == orgVal) {
            *ptrStr = modVal;
        }
        ptrStr++;
    }
}
