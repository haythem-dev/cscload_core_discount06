#ifndef __S_CMDLINE_H__
#define __S_CMDLINE_H__ __S_CMDLINE_H__

//#####################################################################################################//
// includes
//#####################################################################################################//
#include <iostream>
#include <sstream>

using namespace std;

//#####################################################################################################//
// struct SCmdLinePara fpr command line parameter names
//#####################################################################################################//
class SCmdLinePara
{
public:
	static const char* const SP_SRCDB;	
	static const char* const SP_DSTDB;	
    static const char* const SP_DSTFILE;
	static const char* const SP_BRANCHNO;
	static const char* const SP_VERSION;
};

//#####################################################################################################//
// class CmdLine
//#####################################################################################################//
class CmdLine
{
public:	
	virtual bool readCmdLine( int argc, char** argv ) = 0;
    virtual void toStream( ostream& strm = std::cout ) = 0;
    virtual const string& getResource() = 0;

    string			m_sProgName;
    unsigned int	m_uiDC;
    string			m_sSrcDatabase;
    ostringstream	m_osErrMsg;
	bool			m_bVersion;
	

protected:
    CmdLine();
};

//#####################################################################################################//
// struct S_CmdLine
//#####################################################################################################//
class CmdLineDB : public CmdLine
{
public:
	CmdLineDB();
	virtual bool readCmdLine( int argc, char** argv );
	virtual void toStream( ostream& strm = std::cout );
    virtual const string& getResource();

	string			m_sDstDatabase;
};

//#####################################################################################################//
// struct S_CmdLine
//#####################################################################################################//
class CmdLineFile : public CmdLine
{
public:
	CmdLineFile();
	virtual bool readCmdLine( int argc, char** argv );
	virtual void toStream( ostream& strm = std::cout );
    virtual const string& getResource();

	string			m_sDstFile;
};

#endif /* __S_CMDLINE_H__ */
