#pragma once
#include "afxwin.h"
#include <vector>
#include <map>
#include "voodoo_table_header/cagpoart.h"
#include "voodoo_table_header/cagpart.h"
#include "ProgressDlg.h"

#define ROW_STATUS_PASS		0
#define ROW_STATUS_WARN		1
#define ROW_STATUS_ERROR	2

#define MIN_PZN_VALUE		100
#define MAX_PZN_VALUE		9999999

#define MIN_AGP_VALUE		0
#define MAX_AGP_VALUE		9999999

#define MAX_MONTH_VALUE		6

#define COLUMN_DELIMITER	";"
#define ROW_DELIMITER		"\n"

#define CHUNK_SIZE			50
#define DIFF_GROSSO_PCT		20

#define TXN_STATUS_NOT_IMPORTED 0
#define TXN_STATUS_IMPORTED		1
#define TXN_STATUS_TRANSFERRED	2
#define TXN_STATUS_ARCHIVED		3
#define TXN_STATUS_DELETED		4

// helper struct to take originals as well as converted values
struct CAGPARTIMP 
{
	char	PZN_IMP[50];
	char	AGP_IMP[50];
	char	VAL_IMP[50];
	CAGPART PARAMS;
};

class ArtAgpImporter
{
public:
	ArtAgpImporter();
	~ArtAgpImporter();

	void SetProgressDlg(ProgressDlg* pProgress);
	BOOL LoadLocalCSVFile(CString strFile);
	BOOL ValidateCSVData();
	BOOL SaveLocalCSVCheckFile(CString strFile);
	BOOL SaveMasterDataToDB(CString user);
	BOOL SaveDetailDataToDB();
	long GetFileLineCount() { return m_lngFileLineCnt; };
	long GetDataCount() { return (long)m_objAGPDetails.size(); };
	long GetPassCount() { return m_lngPassCnt; };
	long GetWarnCount() { return m_lngWarnCnt; };
	long GetErrorCount() { return m_lngErrCnt; };
	long GetSavedCount() { return m_lngSavedCnt; };

private:

	void ResetData();
	BOOL ReadPZNGrossoDataFromDB(std::vector<CAGPARTIMP*>::iterator it);
	BOOL SetAndCheckPZN(CAGPARTIMP* pDetails, CString strData);
	BOOL SetAndCheckPrice(CAGPARTIMP* pDetails, CString strData);
	BOOL SetAndCheckDate(CAGPARTIMP* pDetails, CString strData);
	BOOL GetNextBufferLine(CString& strLine);

	ProgressDlg* m_pobjProgress;
	CString m_strImportFile;
	long m_lngFileLineCnt;
	long m_lngToday;
	long m_lngPassCnt;
	long m_lngWarnCnt;
	long m_lngErrCnt;
	long m_lngSavedCnt;
	char* m_chrFileBuffer;
	UINT m_intLastBufferPos;
	UINT m_intBufferSize;

	CAGPOART m_objAGPMaster;
	std::vector<CAGPARTIMP*> m_objAGPDetails;
	std::map<long, double>	 m_objGrossos;
};