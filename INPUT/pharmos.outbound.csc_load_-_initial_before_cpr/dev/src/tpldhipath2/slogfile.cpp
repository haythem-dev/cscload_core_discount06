///////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition: SLogFile.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "define.h"
#include "macro.h"
#include "slogfile.h"
//#include "senv.h"
#include "scmdline.h"
//#include <typeinfo.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <sstream>


///////////////////////////////////////////////////////////////////////////////////////////////////////
// Initializing of the static Member-Variable
///////////////////////////////////////////////////////////////////////////////////////////////////////
SLogFile* SLogFile::m_Exemplar		= NULL;


///////////////////////////////////////////////////////////////////////////////////////////////////////
// SLogFile* Exemplar()
///////////////////////////////////////////////////////////////////////////////////////////////////////
SLogFile* SLogFile::Exemplar()
{
	__FUNCTION__(SLogFile::Exemplar)
	DEBUG_ENTER( fun )	

	if( m_Exemplar == NULL ){
		m_Exemplar = new SLogFile();
	}
	
	DEBUG_LEAVE( fun )	
	return m_Exemplar;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
SLogFile::SLogFile()
:	m_pLogFile(NULL),m_apConLogFile(new SLogFile::T_vecstring), m_usDCNo(0), 
	m_sLogPath(""), m_sDftLogFile(""), m_sProgName("")
{
	__FUNCTION__(SLogFile::SLogFile)
	DEBUG_ENTER( fun )
	DEBUG_LEAVE( fun )	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
SLogFile::~SLogFile()
{
	__FUNCTION__( ~SLogFile() )
	DEBUG_ENTER( fun )	
	
	cleanUp();

	DEBUG_LEAVE( fun )	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// void cleanUp()
///////////////////////////////////////////////////////////////////////////////////////////////////////
void SLogFile::cleanUp()
{
	__FUNCTION__( SLogFile::cleanUp() )
	DEBUG_ENTER( fun )	
	
	// first delete all dynamic elements in the container, then delete the container self
	SLogFile::const_itVec	it = m_apConLogFile->begin();
	while( it != m_apConLogFile->end() ){
		delete *it++;
	}
	m_apConLogFile->clear();
	
	DEBUG_LEAVE( fun )
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// SLogFile::SLogFile( const SLogFile& r )
///////////////////////////////////////////////////////////////////////////////////////////////////////
//SLogFile::SLogFile( const SLogFile& r )
//{
//	__FUNCTION__( SLogFile(const SLogFile& r) )
//	DEBUG_ENTER( fun )	
//
//	//throw BSN_Not_Implemented( static_cast<string>(fun) + TXT_NOT_IMPLEMENTED );
//
//	DEBUG_LEAVE( fun )
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// SLogFile* SLogFile::clone() const
///////////////////////////////////////////////////////////////////////////////////////////////////////
//SLogFile* SLogFile::clone() const
//{
//	__FUNCTION__( SLogFile::clone() )
//	DEBUG_ENTER( fun )	
//
//	//throw BSN_Not_Implemented( TXT_NOT_IMPLEMENTED );
//	
//	DEBUG_LEAVE( fun )
//	return NULL;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// SLogFile& SLogFile::operator=( const SLogFile& r )
///////////////////////////////////////////////////////////////////////////////////////////////////////
//SLogFile& SLogFile::operator=( const SLogFile& r )
//{
//	__FUNCTION__( SLogFile::operator=() )
//	DEBUG_ENTER( fun )	
//	
//	//throw BSN_Not_Implemented( TXT_NOT_IMPLEMENTED );
//	
//	DEBUG_LEAVE( fun )
//	return *this;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// bool SLogFile::operator==( const SLogFile& r ) const
///////////////////////////////////////////////////////////////////////////////////////////////////////
//bool SLogFile::operator==( const SLogFile& r ) const
//{
//	__FUNCTION__(SLogFile::cleanUp)
//	DEBUG_ENTER( fun )
//	
//	//throw BSN_Not_Implemented( TXT_NOT_IMPLEMENTED );
//	
//	DEBUG_LEAVE( fun )
//	return false;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// std::ofstream& SLogFile::giveLogFile()
///////////////////////////////////////////////////////////////////////////////////////////////////////
std::ofstream& SLogFile::giveLogFile()
{
	__FUNCTION__( SLogFile::giveLogFile() )
	DEBUG_ENTER( fun )
	if( m_pLogFile == NULL ){
		m_pLogFile = new std::ofstream();
	}

	DEBUG_LEAVE( fun )
	return *m_pLogFile;
}
//###################################################################################################//
// object operations
//###################################################################################################//
///////////////////////////////////////////////////////////////////////////////////////////////////////
// void SLogFile::log( const string& strClMethName, SLogFile::T_MsgMode eMsgMode, const string& strMsg )
///////////////////////////////////////////////////////////////////////////////////////////////////////
void SLogFile::log( const string& strClMethName, SLogFile::T_MsgMode eMsgMode, const string& strMsg )
{
	__FUNCTION__( SLogFile::log() )
	DEBUG_ENTER( fun )
	
	// if the last opened file should be open, it will be closed as a precaution
	if( giveLogFile().is_open() ){
		giveLogFile().close();
		giveLogFile().clear();
	}

	// 
	string strPathAndFile( m_sLogPath );
	strPathAndFile += TXT_SLASH + m_sDftLogFile;

	if( !m_sDftLogFile.empty() ){
		// error are always printed in the default file - mostly 'wws.log'
		if( SLogFile::ERROR == eMsgMode ){
			giveLogFile().open( strPathAndFile.c_str(), ios::out | ios::app );
			
			if( giveLogFile() ){
				giveLogFile()	<< static_cast<char>(eMsgMode)
								<< TXT_SPACE_CHAR
								<< setw( 2 ) << setfill('0') << right 
								<< m_usDCNo
								<< TXT_SPACE_CHAR
								<< getDateTime().str()
								<< TXT_SPACE_CHAR
								<< "pid="
								<< setw( 5 ) << setfill('0') << right
								<< getpid()
								<< TXT_SPACE_CHAR
								<< setw( 8 ) << setfill( TXT_SPACE_CHAR ) << right
								<< m_sProgName
								<< TXT_SPACE_CHAR
								//<< setw( 15 ) << left
								<< strClMethName
								<< TXT_SPACE_CHAR
								<< strMsg
								<< endl;
				giveLogFile().close();
				giveLogFile().clear();	// very important to reset the status flags
			}
		}
	}
	
	// all messages are printed into (a) programm specific log file(s) incl. errors
	SLogFile::const_itVec	it = m_apConLogFile->begin();
	while( it != m_apConLogFile->end() ){
		strPathAndFile = m_sLogPath + TXT_SLASH + **it++;
		
		giveLogFile().open( strPathAndFile.c_str(), ios::out | ios::app );

		if( giveLogFile() ){
			giveLogFile()	<< static_cast<char>(eMsgMode)
							<< TXT_SPACE_CHAR
							<< setw( 2 ) << setfill('0') << right 
							<< m_usDCNo
							<< TXT_SPACE_CHAR
							<< getDateTime().str()
							<< TXT_SPACE_CHAR
							<< "pid="
							<< setw( 5 ) << setfill('0') << right
							<< getpid()
							<< TXT_SPACE_CHAR
							<< setw( 8 ) << setfill( TXT_SPACE_CHAR ) << right
							<< m_sProgName
							<< TXT_SPACE_CHAR
							//<< setw( 15 ) << left
							<< strClMethName
							<< TXT_SPACE_CHAR
							<< strMsg
							<< endl;
			giveLogFile().close();
			giveLogFile().clear();	// very important to reset the status flags
		}
	}

//	DEBUG_PRINTF( 1, ("LEAVE %s m_usDCNo:>%ld<\n", fun, m_usDCNo) )
	DEBUG_LEAVE( fun )
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// const string& SLogFile::getDateTime() const
///////////////////////////////////////////////////////////////////////////////////////////////////////
const std::ostringstream& SLogFile::getDateTime() const
{
	__FUNCTION__( SLogFile::getDateTime() )
	DEBUG_ENTER( fun )

	struct tm *pTm;
	time_t tSec = time(NULL);
	pTm = localtime( &tSec );	

	static std::ostringstream os;
	os.str("");
	os	<< setw(2) << setfill('0') 
		<< pTm->tm_mday 
		<< TXT_DOT_CHAR 
		<< setw(2) << setfill('0') 
		<< (pTm->tm_mon+1) 
		<< TXT_DOT_CHAR 
		<< setw(2) << setfill('0') 
		<< ((pTm->tm_year+1900)%100)
		<< TXT_SPACE_CHAR 
		<< setw(2) << setfill('0') 
		<< pTm->tm_hour
		<< TXT_COLON
		<< setw(2) << setfill('0') 
		<< pTm->tm_min
		<< TXT_COLON
		<< setw(2) << setfill('0') 
		<< pTm->tm_sec;	

	DEBUG_LEAVE( fun )
	return os;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// void SLogFile::add( const string& r )
///////////////////////////////////////////////////////////////////////////////////////////////////////
void SLogFile::add( const string& r )
{
	__FUNCTION__( SLogFile::add() )
	DEBUG_ENTER( fun )
	
	m_apConLogFile->push_back( new string(r) );

	DEBUG_LEAVE( fun )
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// void SLogFile::setDCNo( unsigned short usDCNo )
///////////////////////////////////////////////////////////////////////////////////////////////////////
void SLogFile::setDCNo( unsigned short usDCNo )
{
	__FUNCTION__( SLogFile::setDCNo() )
	DEBUG_ENTER( fun )
    
	m_usDCNo = usDCNo;

	DEBUG_LEAVE( fun )
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// void SLogFile::setLogPath(		const string& rLogPath		)
///////////////////////////////////////////////////////////////////////////////////////////////////////
void SLogFile::setLogPath(		const string& rLogPath		)
{
	__FUNCTION__( SLogFile::setDCNo() )
	DEBUG_ENTER( fun )
	
	m_sLogPath = rLogPath;

	DEBUG_LEAVE( fun )
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// void SLogFile::setDftLogFile(	const string& rDftLogFile	)
///////////////////////////////////////////////////////////////////////////////////////////////////////
void SLogFile::setDftLogFile(	const string& rDftLogFile	)
{
	__FUNCTION__( SLogFile::setDCNo() )
	DEBUG_ENTER( fun )

	m_sDftLogFile = rDftLogFile;

	DEBUG_LEAVE( fun )
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// void SLogFile::setProgName(	const string& rProgName		)
///////////////////////////////////////////////////////////////////////////////////////////////////////
void SLogFile::setProgName(	const string& rProgName		)
{
	__FUNCTION__( SLogFile::setDCNo() )
	DEBUG_ENTER( fun )
	
	m_sProgName= rProgName;
	
	DEBUG_LEAVE( fun )
}