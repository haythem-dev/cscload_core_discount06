#include "stdafx.h"
#include "Ekzdp.h"
#include "ArtAgpImporter.h"
#include "ServerDatum.h"
#include "libscsvoodoo/libscsvoodoo.h"
#include "eklibs/wdbups/wpp_prot.h"
#include "eklibs/wdbups/wpp_dbas.h"

ArtAgpImporter::ArtAgpImporter()
{
	m_chrFileBuffer = NULL;
	ResetData();
}

ArtAgpImporter::~ArtAgpImporter()
{
	ResetData();
}

void ArtAgpImporter::ResetData()
{
	std::vector<CAGPARTIMP*>::iterator it;
	memset(&m_objAGPMaster, 0, sizeof(CAGPOART));
	while (m_objAGPDetails.size() > 0)
	{
		it = m_objAGPDetails.begin();
		CAGPARTIMP* data = *it;
		m_objAGPDetails.erase(it);
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
	}
	m_lngFileLineCnt = 0;
	m_strImportFile = "";
	m_lngToday = ::Today();
	m_objGrossos.clear();
	m_lngPassCnt = 0;
	m_lngWarnCnt = 0;
	m_lngErrCnt = 0;
	m_lngSavedCnt = 0;
	if (m_chrFileBuffer != NULL)
	{
		delete m_chrFileBuffer;
		m_chrFileBuffer = NULL;
	}
	m_intBufferSize = 0;
	m_intLastBufferPos = 0;
}

void ArtAgpImporter::SetProgressDlg(ProgressDlg* pProgress)
{
	m_pobjProgress = pProgress;
}

BOOL ArtAgpImporter::LoadLocalCSVFile(CString strFile)
{
	CFile f;
	CFileException e;
	CString strLine;
	CString strData;
	int pos = 0;
	ResetData();
	BOOL ret = TRUE;

	if (f.Open(strFile, CFile::modeRead | CFile::shareDenyNone, &e) == FALSE)
	{
		return FALSE;
	}
	//fill buffer with file data
	m_strImportFile = f.GetFileName();
	UINT fs = (UINT)f.GetLength();
	m_chrFileBuffer = new char[fs];
	m_intBufferSize = f.Read(m_chrFileBuffer, fs);
	m_intLastBufferPos = 0;
	f.Close();

	// set progress details
	if (m_pobjProgress != NULL)
	{
		m_pobjProgress->SetHeader("Lade CSV Datei...");
		m_pobjProgress->SetBar((int)m_intBufferSize, (int)m_intLastBufferPos);
		m_pobjProgress->SetText("");
		m_pobjProgress->ForceRefresh();
	}
	// ignore header line
	GetNextBufferLine(strLine);
	while (GetNextBufferLine(strLine) == TRUE)
	{
		// ignore empty lines
		if (strLine.GetLength() > 0)
		{
			m_lngFileLineCnt++;
			if (m_pobjProgress != NULL)
			{ 
				m_pobjProgress->SetBar((int)m_intBufferSize, (int)m_intLastBufferPos);
				strData.Format("Import Datei: %s\nLese Datensätze: %ld...", m_strImportFile, m_lngFileLineCnt);
				m_pobjProgress->SetText(strData);
			}
			// process each line and fill details data
			CAGPARTIMP* pDetails = new CAGPARTIMP();
			memset(pDetails, 0, sizeof(CAGPARTIMP));
			pDetails->PARAMS.ZEILE_NR = m_lngFileLineCnt + 1;
			// get PZN (article number)
			pos = strLine.Find(COLUMN_DELIMITER);
			if (pos >= 0)
			{
				strData = strLine.Left(pos);
				strLine = strLine.Mid(pos + 1);
			}
			else
			{
				strData = strLine;
				strLine = "";
			}
			SetAndCheckPZN(pDetails, strData);
			// get AGP price
			pos = strLine.Find(COLUMN_DELIMITER);
			if (pos >= 0)
			{
				strData = strLine.Left(pos);
				strLine = strLine.Mid(pos + 1);
			}
			else
			{
				strData = strLine;
				strLine = "";
			}
			SetAndCheckPrice(pDetails, strData);
			// get valid from date
			pos = strLine.Find(COLUMN_DELIMITER);
			if (pos >= 0)
			{
				strData = strLine.Left(pos);
				strLine = strLine.Mid(pos + 1);
			}
			else
			{
				strData = strLine;
				strLine = "";
			}
			SetAndCheckDate(pDetails, strData);
			if (pDetails->PARAMS.ZEILE_STATUS == ROW_STATUS_PASS)
			{
				m_lngPassCnt++;
			}
			else if (pDetails->PARAMS.ZEILE_STATUS == ROW_STATUS_WARN)
			{
				m_lngWarnCnt++;
			}
			else
			{
				m_lngErrCnt++;
				ret = FALSE;
			}
			// store details in vector
			m_objAGPDetails.push_back(pDetails);
			strData = "";
		}
	}
	delete m_chrFileBuffer;
	m_chrFileBuffer = NULL;
	m_intBufferSize = 0;
	m_intLastBufferPos = 0;
	return ret;
}

BOOL ArtAgpImporter::GetNextBufferLine(CString& strLine)
{
	if ((m_intBufferSize == 0) || (m_chrFileBuffer == NULL) || (m_intLastBufferPos >= m_intBufferSize))
	{
		return FALSE;
	}
	char line[1000];
	int pos = 0;
	memset(line, 0, 1000);
	BOOL blnEOL = FALSE;
	while ((blnEOL == FALSE) && (m_intLastBufferPos < m_intBufferSize))
	{
		if ((m_chrFileBuffer[m_intLastBufferPos] != '\r') && (m_chrFileBuffer[m_intLastBufferPos] != '\n'))
		{
			line[pos] = m_chrFileBuffer[m_intLastBufferPos];
			pos++;
		}
		else
		{
			blnEOL = TRUE;
			strLine = CString(line);
			if (m_chrFileBuffer[m_intLastBufferPos] == '\r')
			{
				if (m_chrFileBuffer[m_intLastBufferPos + 1] == '\n')
				{
					m_intLastBufferPos++;
				}
			}
		}
		m_intLastBufferPos++;
	}
	if ((blnEOL == FALSE) && (m_intLastBufferPos >= m_intBufferSize))
	{
		// end of buffer, so also end of line
		blnEOL = TRUE;
		strLine = CString(line);
	}
	
	return blnEOL;
}

BOOL ArtAgpImporter::ValidateCSVData()
{
	CAGPARTIMP prevDetails;
	memset(&prevDetails, 0, sizeof(CAGPARTIMP));

	long datacnt = (long)m_objAGPDetails.size();
	long dataact = 0;
	CString strData;
	BOOL ret = TRUE;

	m_lngPassCnt = 0;
	m_lngWarnCnt = 0;
	m_lngErrCnt = 0;
	if (m_pobjProgress != NULL)
	{
		m_pobjProgress->SetHeader("Validiere CSV Daten...");
		m_pobjProgress->SetBar((int)datacnt, 0);
		strData.Format("Import Datei: %s\nGelesene Datensätze: %ld\nValidiere Datensätze...", m_strImportFile, m_lngFileLineCnt);
		m_pobjProgress->ForceRefresh();
	}

	std::vector<CAGPARTIMP*>::iterator it;
	for (it = m_objAGPDetails.begin(); it != m_objAGPDetails.end(); it++)
	{
		if (m_pobjProgress != NULL)
		{
			m_pobjProgress->SetBar((int)datacnt, (int)dataact);
			strData.Format("Import Datei: %s\nGelesene Datensätze: %ld\nValidiere Datensätze: %ld...", m_strImportFile, m_lngFileLineCnt, dataact);
			m_pobjProgress->SetText(strData);
		}

		CAGPARTIMP* pDetails = *it;
		// validate only if its not yet an error
		if (pDetails->PARAMS.ZEILE_STATUS != ROW_STATUS_ERROR)
		{
			// first compare with previous one if same PZN
			if (pDetails->PARAMS.PZN == prevDetails.PARAMS.PZN)
			{
				// same, so compare valid from date if same
				if (pDetails->PARAMS.GUELTIG_AB == prevDetails.PARAMS.GUELTIG_AB)
				{
					// its a duplicate, now check AGP price if same
					if (pDetails->PARAMS.AGP != prevDetails.PARAMS.AGP)
					{
						pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
						snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_PZN_DATE_AGP_DIFF));
					}
				}
			}
			// read database data
			ReadPZNGrossoDataFromDB(it);
			// now validate, if PZN exists
			if (m_objGrossos.count(pDetails->PARAMS.PZN) <= 0)
			{
				pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
				snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_PZN_DOESNT_EXSIST));
			}
			else
			{
				// validate price only if set
				double grosso = m_objGrossos[pDetails->PARAMS.PZN];
				if ((pDetails->PARAMS.AGP > 0) && (grosso > 0))
				{
					// then check, that AGP is not too far from grosso
					double ratio;
					if (grosso > pDetails->PARAMS.AGP)
					{
						ratio = grosso / pDetails->PARAMS.AGP;
					}
					else
					{
						ratio = pDetails->PARAMS.AGP / grosso;
					}
					if (((ratio - 1) * 100) > DIFF_GROSSO_PCT)
					{
						pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_WARN;
						snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_AGP_GROSSO_DIFF), grosso);
					}
				}
			}
		}
		if (pDetails->PARAMS.ZEILE_STATUS == ROW_STATUS_PASS)
		{
			m_lngPassCnt++;
		}
		else if (pDetails->PARAMS.ZEILE_STATUS == ROW_STATUS_WARN)
		{
			m_lngWarnCnt++;
		}
		else
		{
			m_lngErrCnt++;
			ret = FALSE;
		}
		// take over the current values as previous for the next one
		memcpy(&prevDetails, pDetails, sizeof(CAGPARTIMP));
		dataact++;
	}
	return ret;
}

BOOL ArtAgpImporter::SaveLocalCSVCheckFile(CString strFile)
{
	CStdioFile f;
	CFileException e;
	CString strLine;
	CString strData;
	CString strDel = COLUMN_DELIMITER;
	CString strLF = ROW_DELIMITER;

	if (f.Open(strFile, CFile::modeWrite | CFile::modeCreate | CFile::shareDenyWrite, &e) == FALSE)
	{
		return FALSE;
	}
	// write header
	strLine = "PZN" + strDel + "AGP" + strDel + "GUELTIG AB" + strDel + "ZEILE NR" + strDel + "STATUS" + strDel + "VALIDIERUNGSTEXT" + strLF;
	f.WriteString(strLine);
	// write details
	std::vector<CAGPARTIMP*>::iterator it;
	for (it = m_objAGPDetails.begin(); it != m_objAGPDetails.end(); it++)
	{
		CAGPARTIMP* pDetails = *it;
		// PZN org and converted
		strLine = pDetails->PZN_IMP + strDel;
		//strData.Format("%ld", pDetails->PARAMS.PZN);
		//strLine += strData + strDel;
		// AGP Price org and converted
		strLine += pDetails->AGP_IMP + strDel;
		//strData.Format("%.2f", pDetails->PARAMS.AGP);
		//strLine += strData + strDel;
		// Valid From Date org and converted
		strLine += pDetails->VAL_IMP + strDel;
		//strData.Format("%2d.%2d.%4d", (pDetails->PARAMS.GUELTIG_AB % 100), ((pDetails->PARAMS.GUELTIG_AB / 100) % 100), (pDetails->PARAMS.GUELTIG_AB / 10000));
		//strLine += strData + strDel;
		// Line No
		strData.Format("%ld", pDetails->PARAMS.ZEILE_NR);
		strLine += strData + strDel;
		// Status
		strData = "Erfolg";
		if (pDetails->PARAMS.ZEILE_STATUS == ROW_STATUS_WARN)
		{
			strData = "Warnung";
		}
		else if (pDetails->PARAMS.ZEILE_STATUS == ROW_STATUS_ERROR)
		{
			strData = "Fehler";
		}
		strLine += strData + strDel;
		// Status Text
		strLine += pDetails->PARAMS.STATUS_DETAIL + strLF;
		// Write Line into file
		f.WriteString(strLine);
	}
	f.Close();
	return TRUE;
}

// syntax check of PZN (articleno)
BOOL ArtAgpImporter::SetAndCheckPZN(CAGPARTIMP* pDetails, CString strData)
{
	if (pDetails == NULL)
	{
		return FALSE;
	}

	try
	{
		// remove optional quotes
		strData.Replace("\"","");
		// trim the data
		strData.Trim();
		// take over original value
		snprintf(pDetails->PZN_IMP, 50, strData);
		// try to convert data into long value
		pDetails->PARAMS.PZN = atol(strData);
		if (pDetails->PARAMS.ZEILE_STATUS == ROW_STATUS_ERROR)
		{
			// already a status, so do not overwrite it
			return FALSE;
		}
		// first of all check if any value given
		if (strData.GetLength() <= 0)
		{
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_PZN_VALUE_MISSING));
			return FALSE;
		}
		if (strData.SpanIncluding("0123456789") != strData)
		{
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_PZN_VALUE_NOTANUMBER));
			return FALSE;
		}
		// check size
		if (pDetails->PARAMS.PZN < MIN_PZN_VALUE)
		{
			// too small
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_PZN_VALUE_TOO_SMALL));
			return FALSE;
		}
		if (pDetails->PARAMS.PZN > MAX_PZN_VALUE)
		{
			// too big
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_PZN_VALUE_TOO_LARGE));
			return FALSE;
		}
	}
	catch (...)
	{
		if (pDetails->PARAMS.ZEILE_STATUS != ROW_STATUS_ERROR)
		{
			// not a long value
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_PZN_VALUE_NOTANUMBER));
		}
		return FALSE;
	}
	return TRUE;
}

// syntax check for AGP price
BOOL ArtAgpImporter::SetAndCheckPrice(CAGPARTIMP* pDetails, CString strData)
{
	if (pDetails == NULL)
	{
		return FALSE;
	}

	try
	{
		// remove optional quotes
		strData.Replace("\"", "");
		// trim the data
		strData.Trim();
		// take over original value 
		snprintf(pDetails->AGP_IMP, 50, strData);
		// convert comma decimal place to point
		strData.Replace(",", ".");
		// try to convert data into double value
		pDetails->PARAMS.AGP = atof(strData);
		if (pDetails->PARAMS.ZEILE_STATUS == ROW_STATUS_ERROR)
		{
			// already a status, so do not overwrite it
			return FALSE;
		}
		// first of all check if any value given
		if (strData.GetLength() <= 0)
		{
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_AGP_VALUE_MISSING));
			return FALSE;
		}
		// then check if number
		if (strData.SpanIncluding("-+0123456789.,") != strData)
		{
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_AGP_VALUE_NOTANUMBER));
			return FALSE;
		}
		// check decimal places
		int pos = strData.Find(".");
		if ((pos >= 0) && (pos < strData.GetLength()-3))
		{
			// more than 2 decimal places given
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_AGP_VALUE_TOO_MANY_DEC));
			return FALSE;
		}
		// check size
		if (pDetails->PARAMS.AGP < MIN_AGP_VALUE)
		{
			// too small
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_AGP_VALUE_NEGATIVE));
			return FALSE;
		}
		if (pDetails->PARAMS.AGP > MAX_AGP_VALUE)
		{
			// too big
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_AGP_VALUE_TOO_LARGE));
			return FALSE;
		}
	}
	catch (...)
	{
		if (pDetails->PARAMS.ZEILE_STATUS != ROW_STATUS_ERROR)
		{
			// not a double value
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_AGP_VALUE_NOTANUMBER));
		}
		return FALSE;
	}
	return TRUE;
}

BOOL ArtAgpImporter::SetAndCheckDate(CAGPARTIMP* pDetails, CString strData)
{
	if (pDetails == NULL)
	{
		return FALSE;
	}

	try
	{
		// remove optional quotes
		strData.Replace("\"", "");
		// trim the data
		strData.Trim();
		// take over original value 
		snprintf(pDetails->VAL_IMP, 50, strData);
		// read in expected date format DD.MM.YYYY
		int vday = atoi(strData.Left(2));
		int vmon = atoi(strData.Mid(3, 2));
		int vyear = atoi(strData.Right(4));
		// create long value YYYYMMDD
		pDetails->PARAMS.GUELTIG_AB = vyear * 10000 + vmon * 100 + vday;
		if (pDetails->PARAMS.ZEILE_STATUS == ROW_STATUS_ERROR)
		{
			// already a status, so do not overwrite it
			return FALSE;
		}
		// first of all, validate format
		if (strData.SpanIncluding("0123456789.") != strData)
		{
			// date is different, so import value is wrong
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_DATE_FORMAT));
			return FALSE;
		}
		// then validate date
		CTime checkTime = CTime(vyear, vmon, vday, 0, 0, 0);
		if (checkTime.Format("%d.%m.%Y").Compare(strData) != 0)
		{
			// date is different, so import value is wrong
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_DATE_INVALID));
			return FALSE;
		}
		// now check if its in future
		long vtoday = m_lngToday;
		if (pDetails->PARAMS.GUELTIG_AB <= vtoday)
		{
			// date is today or older
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_DATE_TOO_OLD));
			return FALSE;
		}
		// now check, that its not too far in future
		long vdays = vyear * 365 + vmon * 30 + vday;
		long cdays = (vtoday / 10000) * 365 + ((vtoday / 100) % 100) * 30 + (vtoday % 100);
		if (vdays > (cdays + MAX_MONTH_VALUE*30))
		{
			// date is too far in future (more than x month)
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_DATE_TOO_FAR));
			return FALSE;
		}
	}
	catch (...)
	{
		if (pDetails->PARAMS.ZEILE_STATUS != ROW_STATUS_ERROR)
		{
			// not a date value
			pDetails->PARAMS.ZEILE_STATUS = ROW_STATUS_ERROR;
			snprintf(pDetails->PARAMS.STATUS_DETAIL, 50, CResString::ex().getStrTblText(IDS_AGP_STAT_ERR_DATE_FORMAT));
		}
		return FALSE;
	}
	return TRUE;
}

BOOL ArtAgpImporter::ReadPZNGrossoDataFromDB(std::vector<CAGPARTIMP*>::iterator it)
{
	HDYNSQL dbHandle;
	long status = 0;
	long pzn = 0;
	double grosso = 0.0f;
	int intCnt;
	CString strSQL;
	CString strData;

	CAGPARTIMP* refDetails = *it;

	// check if PZN and Grosso already loaded
	if (m_objGrossos.count(refDetails->PARAMS.PZN) > 0)
	{
		// yesyes, so return immediatelly
		return TRUE;
	}

	// define sql for a specific amount of articles
	strSQL = "SELECT a.artikel_nr, a.grosso FROM zartpreis a INNER JOIN( ";
	strSQL += "SELECT artikel_nr, MAX(datumgueltigab) AS datumgueltigab FROM zartpreis WHERE artikel_nr IN (";
	intCnt = 0;
	while ((intCnt < CHUNK_SIZE) && (it != m_objAGPDetails.end()))
	{
		intCnt++;
		strData.Format("%ld", (*it)->PARAMS.PZN);
		if ((intCnt > 1) && (intCnt < CHUNK_SIZE))
		{
			strSQL += ",";
		}
		strSQL += strData;
		it++;
	}
	strSQL += ") GROUP BY artikel_nr) b ON a.artikel_nr = b.artikel_nr AND a.datumgueltigab = b.datumgueltigab";

	status = SqlOpenCs(&dbHandle, (LPCTSTR)strSQL);
	while (0L == status)
	{
		status = SqlFetch(dbHandle, 1, &pzn, &grosso, NULL);
		if (0L == status && !m_objGrossos.count(pzn))
		{
			m_objGrossos[pzn] = grosso;
		}
	}
	status = SqlCloseCs(dbHandle);
	if (status == 0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL ArtAgpImporter::SaveMasterDataToDB(CString user)
{
	char constraint[100];
	char buf[500];
	char sql[100];
	long result;
	long agpnr;
	int  dbHandle = -1;
	memset(buf, '\0', sizeof(buf));

	// read next import index
	snprintf(sql, sizeof(sql) - 1, "SELECT MAX(agp_nr) FROM cagpoart");
	(void)SqlRead(sql, &agpnr, NULL);

	// fill master data
	m_objAGPMaster.AGP_NR = agpnr+1;
	m_objAGPMaster.DATUM_ANLAGE = m_lngToday;
	m_objAGPMaster.ZEIT_ANLAGE = ::ActualTime();
	m_objAGPMaster.DATUM_AENDER = 0;
	m_objAGPMaster.DATUM_ARCHIV = 0;
	strncpy(m_objAGPMaster.ANWENDER, user, 8);
	strncpy(m_objAGPMaster.IMPORT_DATEI, m_strImportFile, 30);
	m_objAGPMaster.REC_ERFOLG = m_lngPassCnt;
	m_objAGPMaster.REC_WARN = m_lngWarnCnt;
	m_objAGPMaster.REC_FEHLER = m_lngErrCnt;
	m_objAGPMaster.TXN_STATUS = TXN_STATUS_IMPORTED;

	// write master data into db (with voodoo framework)
	result = OpenBufferDesc(&dbHandle, "cagpoart", NULL, NULL, V_PROTOKOL, buf);
	if (result == 0L)
	{
		snprintf(constraint, sizeof(constraint) - 1, "agp_nr = %ld", m_objAGPMaster.AGP_NR);
		result = FdInsertRecord(dbHandle, &m_objAGPMaster, constraint, buf);
	}
	if (dbHandle >= 0)
	{
		CloseBufferDesc();
	}

	return TRUE;
}

BOOL ArtAgpImporter::SaveDetailDataToDB()
{
	char constraint[100];
	char buf[500];
	long result;
	int  dbHandle = -1;
	memset(buf, '\0', sizeof(buf));
	std::vector<CAGPARTIMP*>::iterator it;
	CString strData;
	long totalCnt;
	long savedCnt;

	if (m_objAGPMaster.AGP_NR <= 0)
	{
		// nonono, Master is not saved yet, so no AGP NR available
		return FALSE;
	}
	totalCnt = (long)m_objAGPDetails.size();
	savedCnt = 0;
	if (m_pobjProgress != NULL)
	{
		m_pobjProgress->SetHeader("Speichere Daten in der Datenbank...");
		m_pobjProgress->SetBar((int)totalCnt, 0);
		strData.Format("Import Datei: %s\nGelesene Datensätze: %ld\nValidierte Datensätze: %ld\nSpeichere Datensätze...", m_strImportFile, m_lngFileLineCnt, totalCnt);
		m_pobjProgress->SetText(strData);
		m_pobjProgress->ForceRefresh();
	}
	// prepare db for inserts
	result = OpenBufferDesc(&dbHandle, "cagpart", NULL, NULL, V_PROTOKOL, buf);
	for (it = m_objAGPDetails.begin(); it != m_objAGPDetails.end(); it++)
	{
		CAGPARTIMP* pDetails = *it;
		if (m_pobjProgress != NULL)
		{
			m_pobjProgress->SetBar(totalCnt, savedCnt);
			strData.Format("Import Datei: %s\nGelesene Datensätze: %ld\nValidierte Datensätze: %ld\nSpeichere Datensatz %ld...", m_strImportFile, m_lngFileLineCnt, totalCnt, savedCnt);
			m_pobjProgress->SetText(strData);
		}
		// set the agp nr and save details if it doesnt have errors
		pDetails->PARAMS.AGP_NR = m_objAGPMaster.AGP_NR;
		if (pDetails->PARAMS.ZEILE_STATUS != ROW_STATUS_ERROR)
		{
			snprintf(constraint, sizeof(constraint) - 1, "agp_nr = %ld AND zeile_nr=%ld", pDetails->PARAMS.AGP_NR, pDetails->PARAMS.ZEILE_NR);
			result = FdInsertRecord(dbHandle, &(pDetails->PARAMS), constraint, buf);
			if (result == 0L)
			{
				savedCnt++;
			}
		}
	}
	// close db handle
	if (dbHandle >= 0)
	{
		CloseBufferDesc();
	}
	m_lngSavedCnt = savedCnt;
	return TRUE;
}