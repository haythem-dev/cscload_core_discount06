/////////////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES 
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "scmdline.h"
#include "macro.h"
#include "define.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cstring>

const char* const SCmdLinePara::SP_SRCDB	= "-srcdb@dbsrv";
const char* const SCmdLinePara::SP_DSTDB	= "-dstdb@dbsrv";
const char* const SCmdLinePara::SP_DSTFILE	= "-dstfile";
const char* const SCmdLinePara::SP_BRANCHNO = "-branchno";

//#####################################################################################################//
// Base class 4 command line 
//#####################################################################################################//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// CmdLine::CmdLine()
/////////////////////////////////////////////////////////////////////////////////////////////////////////
CmdLine::CmdLine()
: m_sProgName(""), m_uiDC( 0 ), m_sSrcDatabase("")
{
    m_osErrMsg << "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// bool CmdLine::readCmdLine( int argc, char** argv )
/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CmdLine::readCmdLine( int argc, char** argv )
{   
    __FUNCTION__( CmdLine::readCmdLine() )  
	DEBUG_ENTER( fun ) 

	///////////////////////////////////////////////////////////////////////////////////////////////
	// to determine the programm name
	///////////////////////////////////////////////////////////////////////////////////////////////
	string sProgName = argv[0];
	string::size_type stPos = sProgName.find_last_of('/');

	if( static_cast<int>( stPos ) >= 0 ){
		sProgName = sProgName.substr( static_cast<int>(stPos)+1, 
									sProgName.length()-static_cast<int>(stPos) );
	}
	m_sProgName = sProgName;

	///////////////////////////////////////////////////////////////////////////////////////////////
	// to determine remaining command parameter
	///////////////////////////////////////////////////////////////////////////////////////////////
	bool bSkip = false;
	for( int i = 1; i < argc; i++ ){
		if( bSkip ){
			bSkip = false;
			continue;
		}
		if( !strcmp(argv[i], SCmdLinePara::SP_SRCDB) ){
			m_sSrcDatabase = argv[i + 1];
			bSkip = true;
		} else if( !strcmp(argv[i], SCmdLinePara::SP_BRANCHNO) ){
			if( 0 != atol(argv[i + 1]) ){
				m_uiDC = (unsigned) atol( argv[i + 1] );
			}
			bSkip = true;
		} else {
			bSkip = false;
		}
	} /* ENDR FOR */                                            

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Checking command paras on existence
    ///////////////////////////////////////////////////////////////////////////////////////////////
    m_osErrMsg.str("");
    m_osErrMsg	<< TXT_USAGE            	<< TXT_COLON		<< " "
				<< m_sProgName				<< " "
				<< SCmdLinePara::SP_BRANCHNO		<< " <value_of_branchno>"
                << SCmdLinePara::SP_SRCDB	<< " <value_of_db@dbserver> ";

    if( argc == 1 || m_sSrcDatabase.empty() || m_uiDC == 0 || m_sProgName.empty() ){
	    m_osErrMsg	<< endl
                    << "No database or branchno passed.";
	    return false;
    }

    DEBUG_LEAVE( fun )
    return true;
}
void CmdLine::toStream( ostream& strm /* = std::cout */ )
{
	__FUNCTION__( CmdLine::toStream() )
	DEBUG_ENTER( fun )
	
    strm << "Programme name: " << m_sProgName.c_str()                 << ";" << endl;
    strm << SCmdLinePara::SP_BRANCHNO		<< ": " << m_uiDC                 << ";" << endl;
    strm << SCmdLinePara::SP_SRCDB	<< ": " << m_sSrcDatabase.c_str() << ";" << endl;

    DEBUG_LEAVE( fun ) 
}
//#####################################################################################################//
// Derived class for reading the command line for database action
//#####################################################################################################//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// CmdLineDB::CmdLineDB()
/////////////////////////////////////////////////////////////////////////////////////////////////////////
CmdLineDB::CmdLineDB()
: CmdLine(), m_sDstDatabase("")
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// const string& CmdLineDB::getResource()
/////////////////////////////////////////////////////////////////////////////////////////////////////////
const string& CmdLineDB::getResource()
{
    return m_sSrcDatabase;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// bool CmdLineDB::readCmdLine( int argc, char** argv )
/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CmdLineDB::readCmdLine( int argc, char** argv )
{
	__FUNCTION__( CmdLineDB::readCmdLine() )
	DEBUG_ENTER( fun ) 
	
    if( false == CmdLine::readCmdLine(argc, argv) ){
        return false;
    }

	///////////////////////////////////////////////////////////////////////////////////////////////
	// to determine remaining command parameter
	///////////////////////////////////////////////////////////////////////////////////////////////
	bool bSkip = false;
	for( int i = 1; i < argc; i++ ){
		if( bSkip ){
			bSkip = false;
			continue;
		}

		if( !strcmp(argv[i], SCmdLinePara::SP_DSTDB) ){
			m_sDstDatabase = argv[i + 1];
			bSkip = true;
        } else {
			bSkip = false;
		}
	} /* ENDR FOR */                                            

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Checking command paras on existence
	///////////////////////////////////////////////////////////////////////////////////////////////
    m_osErrMsg	<< " " << SCmdLinePara::SP_DSTDB << " <value_of_destination_db> ";
	if( m_sDstDatabase.empty() ){
		m_osErrMsg	<< endl
				    << "Variable for the destination database is not passed.";
		return false;
	}

	DEBUG_LEAVE( fun )
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// void CmdLineDB::toStream( ostream& strm /* = std::cout */ )
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CmdLineDB::toStream( ostream& strm /* = std::cout */ )
{
	__FUNCTION__( CmdLineDB::toStream() )
	DEBUG_ENTER( fun )

    CmdLine::toStream( strm );
    strm << SCmdLinePara::SP_DSTDB	<< ": " << m_sDstDatabase   << ";" << endl;

	DEBUG_LEAVE( fun ) 
}

//#####################################################################################################//
// // Derived class for reading the command line for file action
//#####################################################################################################//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// CmdLineFile::CmdLineFile()
/////////////////////////////////////////////////////////////////////////////////////////////////////////
CmdLineFile::CmdLineFile()
: CmdLine(), m_sDstFile("")
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// const string& CmdLineFile::getResource()
/////////////////////////////////////////////////////////////////////////////////////////////////////////
const string& CmdLineFile::getResource()
{
    return m_sDstFile;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// bool CmdLineFile::readCmdLine( int argc, char** argv )
/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CmdLineFile::readCmdLine( int argc, char** argv )
{
	__FUNCTION__( CmdLineFile::readCmdLine() )
	DEBUG_ENTER( fun ) 
	
    if( false == CmdLine::readCmdLine(argc, argv) ){
        return false;
    }

	///////////////////////////////////////////////////////////////////////////////////////////////
	// to determine remaining command parameter
	///////////////////////////////////////////////////////////////////////////////////////////////
	bool bSkip = false;
	for( int i = 1; i < argc; i++ ){
		if( bSkip ){
			bSkip = false;
			continue;
		}
		if( !strcmp(argv[i], SCmdLinePara::SP_DSTFILE) ){
			m_sDstFile = argv[i + 1];
			bSkip = true;
        } else {
			bSkip = false;
		}
	} /* ENDR FOR */                                            

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Checking command paras on existence
	///////////////////////////////////////////////////////////////////////////////////////////////
    m_osErrMsg	<< " " << SCmdLinePara::SP_DSTFILE	<< " <value_of_destination_file> ";
	if( m_sDstFile.empty() ){
		m_osErrMsg	<< endl
				    << "Variable for the destination file is not passed.";
		return false;
	}

	DEBUG_LEAVE( fun )
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// void CmdLineFile::toStream( ostream& strm /* = std::cout */ )
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CmdLineFile::toStream( ostream& strm /* = std::cout */ )
{
	__FUNCTION__( CmdLineFile::toStream() )
	DEBUG_ENTER( fun )

    CmdLine::toStream( strm );
    strm << SCmdLinePara::SP_DSTFILE << ": " << m_sDstFile << ";" << endl;

	DEBUG_LEAVE( fun ) 
}
