#include "stdafx.h"
#include "ekzdp.h"
#include "AgpDoc.h"
#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_bufd.h>

#include <libscsvoodoo/libscsvoodoo.h>
#include "znb_gen_li.h"
#include "ServerDatum.h"




//--------------------------------------------------------------------//
CAgpDoc::CAgpDoc()
{
}

//--------------------------------------------------------------------//
CAgpDoc::~CAgpDoc()
{
}

//--------------------------------------------------------------------//
void CAgpDoc::InitPflegeDesc( char* Anwender)
{
	m_Anwender = Anwender;
	m_Fd = -1;
}

//--------------------------------------------------------------------//
struct CAGPART* CAgpDoc::GetAgpData(int index)
{
	return &m_AgpArtData[index];
}

struct PFL_AGP* CAgpDoc::GetBuffer()
{
	return &m_Buf;
}
//--------------------------------------------------------------------//
int CAgpDoc::InitRecord(CString &cErrmld)
{
	if (GetBufferDescCagpArt(cErrmld) != 0 && GetBufferDescCagpoArt(cErrmld) != 0)
		return -1;

	long agpnr;
	//long satznr;
	long pzn;

	agpnr = m_Buf.cagpoart.AGP_NR;
	// satznr = m_Buf.cagpart.ZEILE_NR;
	pzn = m_Buf.cagpart.PZN;

	FdInitTabBuf(m_Fd, &m_Buf);

	m_Buf.cagpart.PZN = pzn;
	//m_Buf.cagpart.ZEILE_NR = satznr;
	m_Buf.cagpoart.AGP_NR = agpnr;

	return 0;
}

//--------------------------------------------------------------------//
void CAgpDoc::SetAgpKeyCondition()
{
	sprintf(m_PrimekeyCond, "AGP_NR=%ld",
		m_Buf.cagpart.AGP_NR);
}

//--------------------------------------------------------------------//
void CAgpDoc::SetPrimekeyCondition()
{
	sprintf(m_PrimekeyCond, "AGP_NR=%ld and PZN=%.7ld",
		m_Buf.cagpart.AGP_NR, m_Buf.cagpart.PZN);
}

//--------------------------------------------------------------------//
int CAgpDoc::GetBufferDescCagpoArt(CString &cErrmld)
{
	char *tabelle = "cagpoart";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if (m_Fd >= 0)
		return 0;

	lStatus = OpenBufferDesc(&m_Fd, tabelle,
		NULL, NULL, V_PROTOKOL, errmld);
	if (lStatus != 0)
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd = -1;
		return -1;
	}
	return 0;
}

int CAgpDoc::GetBufferDescCagpArt(CString &cErrmld)
{
	char *tabelle = "cagpart";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if (m_Fd >= 0)
		return 0;

	lStatus = OpenBufferDesc(&m_Fd, tabelle,
		NULL, NULL, V_PROTOKOL, errmld);
	if (lStatus != 0)
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd = -1;
		return -1;
	}
	return 0;
}

//--------------------------------------------------------------------//
void CAgpDoc::FreeBufferDesc()
{
	if (m_Fd >= 0)
		CloseOneBufferDesc(m_Fd);

	m_Fd = -1;
}

//--------------------------------------------------------------------//
long CAgpDoc::ReadRecord(CString &cErrmld)
{
	long lStatus;
	char errmld[200];

	SetPrimekeyCondition();
	if (GetBufferDescCagpArt(cErrmld) != 0) return -1;

	lStatus = ::FdReadRecord(m_Fd, m_PrimekeyCond, &m_Buf.cagpart, errmld);

	if (lStatus == 0)
	{  
		cErrmld = _T("");
	}
	else
		cErrmld = errmld;

	m_lStatus = lStatus;

	return lStatus;
}

// Returns total 
int CAgpDoc::GetPznAGPZeile(CString &errmld)
{

	long s;
	int  fd;
	int  anz;
	char sql[150];
	double agp;
	long gueltig_ab;

	anz = 0;
	while (anz < AGPART_ANZ)
	{

		m_AgpArtData[anz].AGP = -1;
		m_AgpArtData[anz].GUELTIG_AB = -1;
		anz++;
	} 

	// Excludes deleted and archived AGP imports

	sprintf(sql, "SELECT AGP, GUELTIG_AB FROM CAGPART WHERE AGP_NR=%ld and PZN=%.7ld ORDER BY GUELTIG_AB ASC", m_Buf.cagpart.AGP_NR, m_Buf.cagpart.PZN);
	s = SqlOpenCs(&fd, sql);
	if (s != 0)
	{
		errmld = DynErrmld();
		return -1;
	}

	s = SqlFetch(fd, 1, &agp, &gueltig_ab, NULL);
	if (s == 100)
	{
		errmld = CResString::ex().getStrTblText(IDS_LOGINDEX_NO); // TODO CHANGE to AGP
		SqlCloseCs(fd);
		return -1;
	}

	anz = 0;
	do
	{		

		m_AgpArtData[anz].AGP = agp;
		m_AgpArtData[anz].GUELTIG_AB = gueltig_ab;
		anz++;
		s = SqlFetch(fd, 1, &agp, &gueltig_ab, NULL);
	} while (s == 0 && anz < AGPART_ANZ);

	if (s < 0)
	{
		errmld = DynErrmld();
		SqlCloseCs(fd);
		return -1;
	}
	SqlCloseCs(fd);

	return anz;
}

// Gets AGP import details
long CAgpDoc::GetAgpImportDetail(CString& cErrmld)
{
	long lStatus;
	char errmld[200];

	SetAgpKeyCondition();
	if (GetBufferDescCagpoArt(cErrmld) != 0) return -1;

	lStatus = ::FdReadRecord(m_Fd, m_PrimekeyCond, &m_Buf.cagpoart, errmld);

	if (lStatus == 0)
	{
		cErrmld = _T("");
	}
	else
		cErrmld = errmld;

	m_lStatus = lStatus;

	return lStatus;
}


// Deletes AGP Import data and mark AGP entry as deleted
long CAgpDoc::DeleteAgpImport(long agpNr)
{
	long lStatus = -1;
	CString sql;

	sql = _T("");
	lStatus = SqlBeginWork();

	if (lStatus != 0)
	{
		return -1;
	}

	// Deletes the CAGPART datei
	sql.Format("DELETE FROM CAGPART WHERE AGP_NR = %ld", agpNr);
	lStatus = SqlExecuteImm(sql);
	if (lStatus != 0)
	{
		lStatus = -1;
	}
	else
	{
		sql = _T(""); // Sets sql to blanck;
		// Updates sttaus of CAGPOART to deleted
		sql.Format("UPDATE CAGPOART SET TXN_STATUS = 4, DATUM_AENDER = %ld WHERE AGP_NR = %ld", ::Today(), agpNr);
		lStatus = SqlExecuteImm(sql);
		if (lStatus != 0)
		{
			lStatus = -1;
		}
	}
	if (lStatus == 0)
		SqlCommitWork();
	else		
		SqlRollbackWork();

	return lStatus;
}

// Gets AGP Import data row count
long CAgpDoc::GetAgpZeilenZahl(long agpNr)
{
	char sql[100];
	long lStatus;
	long count = 0;
	sprintf(sql, "CAGPART WHERE AGP_NR = %ld ", agpNr);

	lStatus = SqlCount(sql, &count);

	return count;

}
