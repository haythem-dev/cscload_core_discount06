#pragma once

#define SQL_SETISOLA_ERROR   (-554)
#include <string>
#include <unordered_set>
#include <set>
#include <vector>

/// Main class CZPExpensive

class CZPExpensive
{
public:
	CZPExpensive();
	virtual ~CZPExpensive();

	void Usage();
	void Reset();
	bool Init(int argc, char* argv[]);
	int  Run();

protected:
	bool OpenDatabase();
	bool CloseDatabase();
	bool WriteLogFile(int logtype, std::string log);
	void Round_ModF(double* value, int digits);
	int  getExpensiveTreshholdValue(double& expthreshholdval, char* errMsg);
	int  updateExpensiveFlag(double expthreshholdval, char* errMsg);

private:
	HNMP						m_pipConnection;
	std::string					m_strAppName;
	std::string					m_strDBName;
	std::string					m_strServerName;
	std::string					m_strServiceName;
	int							m_intPort;

	std::string					m_strLogFile;

	struct ARTICLEDATA
	{
		long   ARTICLENO;
		double GROSSO;
		double INVOICE_REBATE_PCT;
		double REBATE_IN_KIND_PCT;
		double GEPNA;
		short  EXPENSIVE;
		ARTICLEDATA() = default;
		ARTICLEDATA(long _artno, double _grosso, double _ipct, double _rpct, double _gepna, short _exp) 
		{
			ARTICLENO = _artno; GROSSO = _grosso; INVOICE_REBATE_PCT = _ipct; REBATE_IN_KIND_PCT = _rpct; GEPNA = _gepna; EXPENSIVE = _exp;
		}
	};

};
