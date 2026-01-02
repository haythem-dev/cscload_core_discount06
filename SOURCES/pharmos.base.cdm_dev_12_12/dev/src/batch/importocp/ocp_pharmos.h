#ifndef OCP_PARMOS_H_INCLUDED
#define OCP_PARMOS_H_INCLUDED

// exclusion ocp_no map ////////////////////////////////////////////
#define MAX_COUNT_EXCLUDED_OCPNO    2048*1024

extern int countExcludedOCPNo;
extern long ListExcludedOCPNo[MAX_COUNT_EXCLUDED_OCPNO];


bool InitOCPNoExclusionMap(long inDate, long inTime);
bool IsExcludedOCPNo(long ocpNo);

// Input PINT TO CSV Map ////////////////////////////////////////////


typedef struct RowMapPINTToCSV {
    char ID[6];
    int  FieldsLength[1024];
} RowMapPINTToCSV;

extern int countArrayPINTToCSV;
extern char PINTToCSVSep;


bool ConvPINTToCSV(char *inFileName, char *outFileName);

// Input CSV parsing DATA ///////////////////////////////////////////

#define IN_OCP_MAX_COUNT    2048*1024

typedef struct InOCPNoFLAGS {
    int     ocp_art_no;
    int     art_no;
    int     FLAGS;
} InOCPNoFLAGS;

#define IN_OCPNO_HAS_ART_NO            (1<<0)  // found mapping from OCP_no to artikel_nr in carticlecodes
#define IN_OCPNO_HAS_IN_ART            (1<<1)  // found article row in input CSV
#define IN_OCPNO_HAS_IN_ART_CODE       (1<<2)  // found article_code row in input CSV
#define IN_OCPNO_HAS_IN_ART_PRICE      (1<<3)  // found article_price row in input CSV
#define IN_OCPNO_HAS_IN_ART_FRANCE     (1<<4)  // found article_france row in input CSV
#define IN_OCPNO_HAS_PH_ART            (1<<5)  // found article row in Master Data
#define IN_OCPNO_HAS_PH_ART_CODE       (1<<6)  // found article_code row in Master Data
#define IN_OCPNO_HAS_PH_ART_PRICE      (1<<7)  // found article_price row in Master Data
#define IN_OCPNO_HAS_PH_ART_FRANCE     (1<<8)  // found article_france row in Master Data
#define IN_OCPNO_HAS_INCSV_ART_NO      (1<<9)  // found OCP artNo mapping inside input CSV

#define IN_OCPNO_MDATA_FLAGS_DELETE ((int)(IN_OCPNO_HAS_PH_ART|IN_OCPNO_HAS_PH_ART_CODE|IN_OCPNO_HAS_PH_ART_PRICE|IN_OCPNO_HAS_PH_ART_FRANCE) ^ (int)(0xffffffff))

bool ExistOCP_NO(int ocp_no); // return true if ocp_no exist
InOCPNoFLAGS *GetInOCPNoFLAGS(int ocp_no); // return pointer to found element, else NULL
InOCPNoFLAGS *GetInCharOCPNoFLAGS(char *cocp_no); // return pointer to found element, else NULL
InOCPNoFLAGS* InsertInOCPNo(int ocp_no, int init_flags); // no checking if exist, will create duplicates of already exist
void UpdateMasterDATA_FLAGS(char *articleNo, int *FLAGS);


extern InOCPNoFLAGS InOCPNoList[IN_OCP_MAX_COUNT];
extern InOCPNoFLAGS *InOCPNoMap[IN_OCP_MAX_COUNT];
extern int InOCPNoCount;

// cocp_stagein_XXXX tables defines

#define OCP_ARTICLE_NO_IDX      0

// article codes struct /////////////////////////////////////////////
#define ARTICLE_CODES_FIELDS_COUNT 5
// fields idx
#define ARTICLE_CODES_CODE_TYPE_IDX           1
#define ARTICLE_CODES_ARTICLE_CODE_IDX        2
#define ARTICLE_CODES_PREFERRED_FLAG_IDX      3
#define ARTICLE_CODES_CHANGED_DATE_IDX        4

extern int article_code_incsv_map[];

// article struct //////////////////////////////////////////////////
#define ARTICLE_FIELDS_COUNT 40
// fields idx
#define ARTICLE_LONG_NAME_IDX           1
#define ARTICLE_UNIT_IDX                2
#define ARTICLE_DOSAGE_FORM_IDX         3
#define ARTICLE_PRODUCT_GROUP_IDX       4
#define ARTICLE_PRODUCT_TYPE_IDX        5
#define ARTICLE_MANUFACTURER_NO_IDX     6
#define ARTICLE_SUPPLIER_NO_IDX         7
#define ARTICLE_LENGTH_IDX              8
#define ARTICLE_WIDTH_IDX               9
#define ARTICLE_HEIGHT_IDX              10
#define ARTICLE_WEIGHT_IDX              11
#define ARTICLE_PACKAGE_UNIT_1_IDX      12
#define ARTICLE_PACKAGE_UNIT_2_IDX      13
#define ARTICLE_PACKAGE_UNIT_3_IDX      14
#define ARTICLE_PACKAGE_UNIT_4_IDX      15
#define ARTICLE_CREATION_DATE_IDX       16
#define ARTICLE_MODIFICATION_DATE_IDX   17
#define ARTICLE_EXPIRY_DATE_IDX         18
#define ARTICLE_OUT_OF_MARKET_DATE_IDX  19
#define ARTICLE_DURATION_MONTHS_IDX     20
#define ARTICLE_NEGATIVE_LIST_IDX       21
#define ARTICLE_BATCH_ARTICLE_IDX       22
#define ARTICLE_COOLING_ARTICLE_IDX     23
#define ARTICLE_NARCOTICS_IDX           24
#define ARTICLE_FMD_RELEVANT_IDX        25
#define ARTICLE_VETERINARY_IDX          26
#define ARTICLE_PRESCRIPTION_NEEDED_IDX 27
#define ARTICLE_PSYCHOTROPE_IDX         28
#define ARTICLE_ZYTOSTATIC_IDX          29
#define ARTICLE_BLOCKED_IDX             30
#define ARTICLE_NOT_ALLOWED_IDX         31
#define ARTICLE_TAX_IDX                 32
#define ARTICLE_PHARMACY_ONLY_IDX       33
#define ARTICLE_MEDICATION_IDX          34
#define ARTICLE_TOXIC_IDX               35
#define ARTICLE_VERY_TOXIC_IDX          36
#define ARTICLE_HARMFUL_IDX             37
#define ARTICLE_HOMEOPATHY_IDX          38
#define ARTICLE_MEDICAL_GASES_IDX       39

extern int article_incsv_map[];

// cocp_stagein_status database table struct ////////////////////////
#define OCP_STATUS_IMPORT_DATE_IDX              0
#define OCP_STATUS_IMPORT_TIME_IDX              1
#define OCP_STATUS_IMPORT_FILE_IDX              2
#define OCP_STATUS_IMPORT_CODE_RECORDS_IDX      3
#define OCP_STATUS_IMPORT_ARTICLE_RECORDS_IDX   4
#define OCP_STATUS_IMPORT_PRICE_RECORDS_IDX     5
#define OCP_STATUS_IMPORT_FRANCE_RECORDS_IDX    6

// article price struct //////////////////////////////////////////////
#define ARTICLE_PRICE_FIELDS_COUNT 17

#define ARTICLE_PRICE_VALID_FROM_DATE_IDX           1
#define ARTICLE_PRICE_MANUFACTURER_BASE_PRICE_IDX   2
#define ARTICLE_PRICE_SUPPLIER_BASE_PRICE_IDX       3
#define ARTICLE_PRICE_PHARMACY_BASE_PRICE_IDX       4
#define ARTICLE_PRICE_PHARMACY_BUY_PRICE_IDX        5
#define ARTICLE_PRICE_MAX_PHARMACY_BUY_PRICE_IDX    6
#define ARTICLE_PRICE_PHARMACY_SELL_PRICE_IDX       7
#define ARTICLE_PRICE_RECOM_PHARMACY_SELL_PRICE_IDX 8
#define ARTICLE_PRICE_MAX_PHARMACY_SELL_PRICE_IDX   9
#define ARTICLE_PRICE_MANUFACTURER_PERCENTAGE_IDX   10
#define ARTICLE_PRICE_REFUND_AMOUNT                 11
#define ARTICLE_PRICE_VAT_CODE_IDX                  12
#define ARTICLE_PRICE_PRICE_TYPE_IDX                13
#define ARTICLE_PRICE_PRICE_MODEL_IDX               14
#define ARTICLE_PRICE_DISCOUNT_DEDUCED_YET_IDX      15
#define ARTICLE_PRICE_PUBLICATION_NUMBER_IDX        16

extern int article_price_incsv_map[];

// article france struct ////////////////////////////////////////////////

#define ARTICLE_FRANCE_FIELDS_COUNT 16

#define ARTICLE_FRANCE_REIMBURSEMENT_PERC_IDX       1
#define ARTICLE_FRANCE_REIMBURSEMENT_VAL_IDX        2
#define ARTICLE_FRANCE_UNIT_MULTIPLE_IDX            3
#define ARTICLE_FRANCE_QTY_SUBMULTIPLE_IDX          4
#define ARTICLE_FRANCE_RESERVE_HOSP_IDX             5
#define ARTICLE_FRANCE_REIMBURSEMENT_TYPE_IDX       6
#define ARTICLE_FRANCE_NOT_VIA_EDI_IDX              7
#define ARTICLE_FRANCE_CODE_BLOCAGE_IDX             8
#define ARTICLE_FRANCE_CODE_LPPR_IDX                9
#define ARTICLE_FRANCE_TFR_BASE_PRICE_IDX           10
#define ARTICLE_FRANCE_DISTR_RESTR_EXPORT_IDX       11
#define ARTICLE_FRANCE_DISTR_RESTR_LEGAL_IDX        12
#define ARTICLE_FRANCE_DISTR_RESTR_BREIZH_IDX       13
#define ARTICLE_FRANCE_DISTR_RESTR_HOSP_IDX         14
#define ARTICLE_FRANCE_REBATE_GROUP_SPEC_IDX        15

extern int article_france_incsv_map[];

////////////////////////////////////////////////////////////////////////////
// STAGEOUT struct and constants ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


// from/to databse table to csvRow maps

typedef struct TableToFromRowElem {
	char Type; // ' ' space take as is; 'B' Boolean 0/1, 'Y' Boolean 'Y'/'N'; 'F' float/decimal check for any ',' and replace by '.'
	char* FieldsName;
	int mapToFromRowIdx;
} TableToFromRowElem;


typedef struct TableToFromRowMap {
	char* nameDbTable;
	char *IDFieldName;
	int countFields;
	bool master; // content if this table is required, else import fail
	TableToFromRowElem elemsMap[256];
} TableToFromRowMap;

typedef struct SetTablesToFromRowMap {
	int countMaps;
	int countRowsToMap;
	int maxSizeField;
	char *targetTable;
	TableToFromRowMap maps[32];
} SetTablesToFromRowMap;

/*char * TableToFromRowMapToSQLUpd(TableToFromRowMap *tableMap, char *outSql);
char * TableToFromRowMapToSQLIns(TableToFromRowMap *tableMap, char *outSql);*/
char * TableToFromRowMapToSQLSel(TableToFromRowMap *tableMap, char *outSql, char *Id);

// default rows
extern char *oarticleDefaults[];
extern CsvRow *oarticleDefaultRow;

extern char *oarticleCodesDefaults[];
extern CsvRow *oarticleCodesDefaultRow;

extern char *oarticlePriceDefaults[];
extern CsvRow *oarticlePriceDefaultRow;

extern char *oarticleFranceDefaults[];
extern CsvRow *oarticleFranceDefaultRow;

void CreateStageoutDefaultRows();

// stageout article constants

// fields FLAGS
#define STATE_PHARMOS    0x01
#define STATE_IMPORT_OK  0x02
#define STATE_IMPORT_KO  0x04
#define STATE_MANUAL_FIX 0x08
#define STATE_VALID      0x10

#define DEFAULT_STATE    (char)(0x01)

// stageout article
#define OARTICLE_FIELDS_COUNT               50

#define OARTICLE_OCP_NO_IDX                 0
#define OARTICLE_NO_IDX                     1
#define OARTICLE_LONG_NAME_IDX              2
#define OARTICLE_UNIT_IDX                   3
#define OARTICLE_DOSAGE_FORM_IDX            4
#define OARTICLE_DKART_PRODUCT_GROUP_IDX    5
#define OARTICLE_PRODUCT_TYPE_IDX           6
#define OARTICLE_MANUFACTURER_NO_IDX        7
#define OARTICLE_AWL1_IDX                   8
#define OARTICLE_LENGTH_IDX                 9
#define OARTICLE_WIDTH_IDX                  10
#define OARTICLE_HEIGHT_IDX                 11
#define OARTICLE_WEIGHT_IDX                 12
#define OARTICLE_PACKAGE_UNIT_1_IDX         13
#define OARTICLE_PACKAGE_UNIT_2_IDX         14
#define OARTICLE_PACKAGE_UNIT_3_IDX         15
#define OARTICLE_PACKAGE_UNIT_4_IDX         16
#define OARTICLE_CREATION_DATE_IDX          17
#define OARTICLE_MODIFICATION_DATE_IDX      18
#define OARTICLE_EXPIRY_DATE_IDX            19
#define OARTICLE_OUT_OF_MARKET_DATE_IDX     20
#define OARTICLE_DURATION_MONTHS_IDX        21
#define OARTICLE_NEGATIVE_LIST_IDX          22
#define OARTICLE_BATCH_ARTICLE_IDX          23
#define OARTICLE_COOLING_ARTICLE_IDX        24
#define OARTICLE_NARCOTICS_IDX              25
#define OARTICLE_FMD_IDX                    26
#define OARTICLE_VETERINARY_IDX             27
#define OARTICLE_PRESCRIPTION_NEEDED_IDX    28
#define OARTICLE_PSYCHOTROPE_IDX            29
#define OARTICLE_ZYTOSTATIC_IDX             30
#define OARTICLE_BLOCKED_IDX                31
#define OARTICLE_NOT_ALLOWED_IDX            32
#define OARTICLE_TAX_IDX                    33
#define OARTICLE_PHARMACY_ONLY_IDX          34
#define OARTICLE_MEDICATION_IDX             35
#define OARTICLE_TOXIC_IDX                  36
#define OARTICLE_VERY_TOXIC_IDX             37
#define OARTICLE_HARMFUL_IDX                38
#define OARTICLE_HOMEOPATHY_IDX             39
#define OARTICLE_MEDICAL_GASES_IDX          40
#define OARTICLE_SEASON_GROUP_1_IDX         41
#define OARTICLE_SEASON_GROUP_2_IDX         42
#define OARTICLE_SEASON_GROUP_3_IDX         43
#define OARTICLE_ATC_CODE_IDX               44

#define OARTICLE_STATE_FLAG_IDX             45
#define OARTICLE_SUM_STATE_FLAG_IDX         46
#define OARTICLE_USERNAME_IDX               47
#define OARTICLE_LAST_CHANGE_DATE_IDX       48
#define OARTICLE_LAST_CHANGE_TIME_IDX       49


//////////////////////////////////////////////
#define OARTICLE_CODES_FIELDS_COUNT        11

#define OARTICLE_CODES_OCP_NO_IDX           0
#define OARTICLE_CODES_ARTICLENO_IDX        1
#define OARTICLE_CODES_CODE_TYPE_IDX        2
#define OARTICLE_CODES_ARTICLE_CODE_IDX     3
#define OARTICLE_CODES_PREFERRED_FLAG_IDX   4
#define OARTICLE_CODES_DATE_CHANGED_IDX     5

#define OARTICLE_CODES_STATE_FLAG_IDX       6
#define OARTICLE_CODES_SUM_STATE_FLAG_IDX   7
#define OARTICLE_CODES_USERNAME_IDX         8
#define OARTICLE_CODES_LAST_CHANGE_DATE_IDX 9
#define OARTICLE_CODES_LAST_CHANGE_TIME_IDX 10


#define OARTICLE_PRICE_FIELDS_COUNT                23

#define OARTICLE_PRICE_OCP_NO_IDX                  0
#define OARTICLE_PRICE_ARTICLE_NO_IDX              1
#define OARTICLE_PRICE_DATE_VALID_FROM_IDX         2
#define OARTICLE_PRICE_GROUND_PRICE_IDX            3
#define OARTICLE_PRICE_SUPPLIER_BASE_PRICE_IDX     4
#define OARTICLE_PRICE_PHARMACY_BASE_PRICE_IDX     5
#define OARTICLE_PRICE_PHARMACY_BUYING_PRICE_IDX   6
#define OARTICLE_PRICE_MAX_AEP_IDX                 7
#define OARTICLE_PRICE_PHARMACY_SELLING_PRICE_IDX  8
#define OARTICLE_PRICE_EAVP_IDX                    9
#define OARTICLE_PRICE_MAX_AVP_IDX                 10
#define OARTICLE_PRICE_HERST_PROZENT_IDX           11
#define OARTICLE_PRICE_ERSTATTBETRAG_IDX           12
#define OARTICLE_PRICE_KE_MWST_IDX                 13
#define OARTICLE_PRICE_PRICE_TYPE_IDX              14
#define OARTICLE_PRICE_PRICE_MODEL_IDX             15
#define OARTICLE_PRICE_DISC_DEDUCED_YET_IDX        16
#define OARTICLE_PRICE_PUBLICATION_NUMBER_IDX      17

#define OARTICLE_PRICE_STATE_FLAG_IDX              18
#define OARTICLE_PRICE_SUM_STATE_FLAG_IDX          19
#define OARTICLE_PRICE_USERNAME_IDX                20
#define OARTICLE_PRICE_LAST_CHANGE_DATE_IDX        21
#define OARTICLE_PRICE_LAST_CHANGE_TIME_IDX        22


#define OARTICLE_FRANCE_FIELDS_COUNT                22

#define OARTICLE_FRANCE_OCP_NO_IDX                  0
#define OARTICLE_FRANCE_ARTICLE_NO_IDX              1
#define OARTICLE_FRANCE_REIMBURSEMENT_PERC_IDX      2
#define OARTICLE_FRANCE_REIMBURSEMENT_VAL_IDX       3
#define OARTICLE_FRANCE_UNIT_MULTIPLE_IDX           4
#define OARTICLE_FRANCE_QTY_SUBMULTIPLE_IDX         5
#define OARTICLE_FRANCE_RESERVE_HOSP_IDX            6
#define OARTICLE_FRANCE_REIMBURSEMENT_TYPE_IDX      7
#define OARTICLE_FRANCE_NOT_VIA_EDI_IDX             8
#define OARTICLE_FRANCE_CODE_BLOCAGE_IDX            9
#define OARTICLE_FRANCE_CODE_LPPR_IDX               10
#define OARTICLE_FRANCE_TFR_BASE__PRICE_IDX         11
#define OARTICLE_FRANCE_DISTR_RESTR_EXPORT_IDX      12
#define OARTICLE_FRANCE_DISTR_RESTR_LEGAL_IDX       13
#define OARTICLE_FRANCE_DISTR_RESTR_BREIZH_IDX      14
#define OARTICLE_FRANCE_DISTR_RESTR_HOSP_IDX        15
#define OARTICLE_FRANCE_REBATE_GROUP_SPEC_IDX       16

#define OARTICLE_FRANCE_STATE_FLAG_IDX              17
#define OARTICLE_FRANCE_SUM_STATE_FLAG_IDX          18
#define OARTICLE_FRANCE_USERNAME_IDX                19
#define OARTICLE_FRANCE_LAST_CHANGE_DATE_IDX        20
#define OARTICLE_FRANCE_LAST_CHANGE_TIME_IDX        21

extern char esqlRows[128][256];

#define ESQL_ROWS_INTO :esqlRows[0], :esqlRows[1], :esqlRows[2], :esqlRows[3], :esqlRows[4], :esqlRows[5], :esqlRows[6], :esqlRows[7],\
                       :esqlRows[8], :esqlRows[9], :esqlRows[10], :esqlRows[11], :esqlRows[12], :esqlRows[13], :esqlRows[14], :esqlRows[15],\
                       :esqlRows[16], :esqlRows[17], :esqlRows[18], :esqlRows[19], :esqlRows[20], :esqlRows[21], :esqlRows[22], :esqlRows[23], :esqlRows[24],\
                       :esqlRows[25], :esqlRows[26], :esqlRows[27], :esqlRows[28], :esqlRows[29], :esqlRows[30], :esqlRows[31], :esqlRows[32], :esqlRows[33],\
                       :esqlRows[34], :esqlRows[35], :esqlRows[36], :esqlRows[37], :esqlRows[38], :esqlRows[39], :esqlRows[40], :esqlRows[41], :esqlRows[42],\
                       :esqlRows[43], :esqlRows[44], :esqlRows[45], :esqlRows[46], :esqlRows[47], :esqlRows[48], :esqlRows[49], :esqlRows[50], :esqlRows[51],\
                       :esqlRows[52], :esqlRows[53], :esqlRows[54], :esqlRows[55], :esqlRows[56], :esqlRows[57], :esqlRows[58], :esqlRows[59], :esqlRows[60],\
                       :esqlRows[61], :esqlRows[62], :esqlRows[63], :esqlRows[64], :esqlRows[65], :esqlRows[66], :esqlRows[67], :esqlRows[68], :esqlRows[69],\
                       :esqlRows[70], :esqlRows[71], :esqlRows[72], :esqlRows[73], :esqlRows[74], :esqlRows[75], :esqlRows[76], :esqlRows[77], :esqlRows[78],\
                       :esqlRows[79], :esqlRows[80], :esqlRows[81], :esqlRows[82], :esqlRows[83], :esqlRows[84], :esqlRows[85], :esqlRows[86], :esqlRows[87],\
                       :esqlRows[88], :esqlRows[89], :esqlRows[90], :esqlRows[91], :esqlRows[92], :esqlRows[93], :esqlRows[94], :esqlRows[95], :esqlRows[96],\
                       :esqlRows[97], :esqlRows[98], :esqlRows[99], :esqlRows[100], :esqlRows[101], :esqlRows[102], :esqlRows[103], :esqlRows[104], :esqlRows[105]


extern SetTablesToFromRowMap mapArticleRow;
extern SetTablesToFromRowMap mapArticleCodesRow;
extern SetTablesToFromRowMap mapArticlePriceRow;
extern SetTablesToFromRowMap mapArticleFranceRow;

bool GetStageoutArticle(CsvRow * outRow, char *ArticleNo);

bool GetStageoutArticleCode(CsvRow * outRow, char *ArticleNo, char *CodeType);
bool GetStageoutArticleFrance(CsvRow * outRow, char *ArticleNo);
bool GetStageoutArticlePrice(CsvRow *outRow, char *date_valid, char *ArticleNo);
// given a master table map and articleNo check of ArticleNo master data occurence
bool ExistMasterArticle(char *ArticleNo, SetTablesToFromRowMap *masterTableMap);
bool GetTransferReadyOCPNo(char *OCP_ArticleNo, long date, long time);
bool GetOCPNoToArticleNo(char *OCP_ArticleNo, char *articleNo);
bool ImportReadyCharOCPNo(char *socp_no, int *OCP_FLAGS);
bool ImportReadyOCPNo(int ocp_no, int *OCP_FLAGS);

void GetStageoutArticleFromStagein(CsvRow * outRow, char **stageinRow, char *ArticleNo);
void GetStageoutArticleCodeFromStagein(CsvRow * outRow, char **stageinRow, char *ArticleNo);
void GetStageoutArticleFranceFromStagein(CsvRow * outRow, char **stageinRow, char *ArticleNo);
void GetStageoutArticlePriceFromStagein(CsvRow *outRow, char **stageinRow, char *ArticleNo);
void GetSeasonGroup(char *article_no, char *grp_2, char *grp_5, char *grp_A, char *grp_G);

void ExistStageoutArticle(bool *existArticle, bool *existPackageUnit);
bool ExistStageoutArticleCode();
bool ExistStageoutArticleFrance();
bool ExistStageoutArticlePrice();
bool ExistSeasonGroup(char *article_no, char *grp);

bool PutStageoutArticle();
bool PutStageoutArticleCode();
bool PutStageoutArticleFrance();
bool PutStageoutArticlePrice();
bool PutSeasonGroup(char *article_no, char *grp_2, char *grp_5, char *grp_A, char *grp_G);

// function to fix any possible data problem on input rows
void CleanArticleStageinRow(char **inRow);
void CleanArticleCodeStageinRow(char **inRow);
void CleanArticlePriceStageinRow(char **inRow);
void CleanArticleFranceStageinRow(char **inRow);

// utils
void EnsureNotNullValues(char **stageinRow, int countValues);
void EnsureNotNullRowValues(CsvRow *outRow);
void CopyDefaultValueIfEmpty(char *dst, char *src, char *defaultv);
void TrimStr(char *str);
void ReplaceCharStr(char *str, char orgVal, char modVal);

//int GetCountStageoutArticlePrices(char *ArticleNo);


#endif // OCP_PARMOS_H_INCLUDED
