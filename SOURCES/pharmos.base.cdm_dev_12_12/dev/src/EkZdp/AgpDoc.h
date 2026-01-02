#ifndef AGPDOC_H_INCLUDE
#define AGPDOC_H_INCLUDE

// AgpDoc.h : header file
#include <voodoo_table_header/cagpart.h>
#include <voodoo_table_header/cagpoart.h>

#include <eklibs/wdbups/wpp_dbas.h>
#include "hDatum.h"

struct PFL_AGP
{
	CAGPOART cagpoart;
	CAGPART  cagpart;
};

class CAgpDoc
{

private:
	// members
	// Buffers for CAGPART structure
	struct PFL_AGP m_Buf;
	enum {AGPART_ANZ = 10};
	struct CAGPART m_AgpArtData[AGPART_ANZ];
	// Primary key condition
	char   m_PrimekeyCond[100];
	int    m_Fd;
	long   m_lStatus;

	// User name/id
	char   *m_Anwender;
	CString m_Database;
	ChDatum m_hDatum;

public:
	CAgpDoc();           // protected constructor used by dynamic creation
	virtual ~CAgpDoc();

	struct PFL_AGP* GetBuffer();
	struct CAGPART* GetAgpData(int index);
	// record read write delete
	void FreeBufferDesc();
	long ReadRecord(CString& cErrmld);
	int  InitRecord(CString& cErrmld);
	void InitPflegeDesc(char* Anwender);
	long DeleteAgpImport(long agpNr);
	int  GetPznAGPZeile(CString& errmld);
	long GetAgpImportDetail(CString& errmld);
	long GetAgpZeilenZahl(long agpNr);
private:
	int  GetBufferDescCagpArt(CString &cErrmld);
	int  GetBufferDescCagpoArt(CString &cErrmld);
	void SetPrimekeyCondition();
	void SetAgpKeyCondition();
};


#endif // AGPDOC_H_INCLUDE