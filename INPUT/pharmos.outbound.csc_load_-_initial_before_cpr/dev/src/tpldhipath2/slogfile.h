#ifndef __SLOGFILE_H__
#define __SLOGFILE_H__ __SLOGFILE_H__

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes 
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <memory>
#include <string>

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////
// class SLogFile
///////////////////////////////////////////////////////////////////////////////////////////////////////
class SLogFile
{
////////////////////////////////////////////////////////////////////////
// public: 
////////////////////////////////////////////////////////////////////////
public:
	enum T_MsgMode { WARNING = 87, OK = 79, HINT = 72, ERROR = 69 };
	
	static SLogFile*	Exemplar();
	virtual				~SLogFile();	
	void				log( const string& strClMethName, SLogFile::T_MsgMode eMsgMode, const string& strMsg );
	void				add( const string& r );
	void				setDCNo( unsigned short usDCNo );
	void				setLogPath(		const string& rLogPath		);
	void				setDftLogFile(	const string& rDftLogFile	);
	void				setProgName(	const string& rProgName		);

////////////////////////////////////////////////////////////////////////
// protected: 
////////////////////////////////////////////////////////////////////////
protected:
	SLogFile();

////////////////////////////////////////////////////////////////////////
// private: 
////////////////////////////////////////////////////////////////////////
private:
	typedef vector<const string*> T_vecstring;
	typedef T_vecstring::const_iterator const_itVec;

private: // methods
	SLogFile( const SLogFile& r );
	/*virtual */SLogFile* clone() const;
	SLogFile& operator=( const SLogFile& r );
	/*virtual */bool operator ==( const SLogFile& r ) const;
	void cleanUp();
	std::ofstream& giveLogFile();
	const std::ostringstream& getDateTime() const;
	
private: // members
	static SLogFile*				m_Exemplar;

	std::ofstream*					m_pLogFile;
	std::auto_ptr<T_vecstring>	m_apConLogFile;
	unsigned short					m_usDCNo;


	
	std::string m_sLogPath;
	std::string m_sDftLogFile;
	std::string m_sProgName;
};

#endif // __SLOGFILE_H__
