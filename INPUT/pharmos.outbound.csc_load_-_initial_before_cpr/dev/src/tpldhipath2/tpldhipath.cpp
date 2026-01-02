///////////////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <list>
#include <sstream>
#include <unistd.h>

#include "macro.h"
#include "define.h"
#include "scmdline.h"
#include "persistence.h"
#include "persistencedb.h"
#include "persistencefile.h"
#include "slogfile.h"
#include "sql.h"
#include "customerroutingtable.h"
#include "date.h"

using std::cout;
using std::cerr;
using std::endl;
using std::left;
using std::setw;
using std::setfill;
using std::right;
using std::list;
using std::ostringstream;
using std::string;

#include "csc_load_version.h"
#include "versioninfo.h"

#define PROJECTNAME	 "tpldhipath"

static const char versioninfo[] = "@(#)" PROJECTNAME "\t" CSC_LOAD_VERSION " " PROJECTCONFIG;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VERSION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
VERSIONIERUNG:	
V-NR		Date		COMMENT
------------------------------------------------------------------------------------------------
0.0.0.1		
------------------------------------------------------------------------------------------------
0.0.0.2		27.01.05	SCustomRoutingTable::save()
                        Methoden-lokale Variable 'bSaved' wurde faelschlicherweise 
						nochmal lokal in einer if-Anweisung angelegt und somit der 
						der alte (falsche) Wert der Methoden-lokalen Var. 
						zurueckgeliefert
------------------------------------------------------------------------------------------------
0.0.1.3		22.02.05	- neue Methode, die diejenigen Kunden loescht, die pro Lauf nicht 
                            aktualisiert oder eingefuegt wurden; und zwar nach VZ
                        - beim Einfuegen in die NT-DB wird das Attribut 'caption'
                            aus 2-stelligen VZ-Nr und der 7-stelligen IDFNR auch noch 
                            aus einem 8-stelligen Datum aufgebaut, um feststellen zu können
                            welche Datensaetze pro Lauf 'angefasst' wurden
------------------------------------------------------------------------------------------------
0.0.1.4		24.02.05	- Methode 'static bool saveCustomers()' beruecksichtigt die ab sofort 
                            in dem Attribut 'phonepriority' auch ein 'S' und setzt in 
                            CALLTYPE "AA_Sonder" und in INITIALPRIORITY = 89;
                        - Methode 'retClient prepareSKundeSelect( tError* pstError )', die den 
                            SELECT fuer die Kunden praepartiert, selektiert jetzt nur noch auf 
                            --> phonepriority in ( 'V', 'S', 'A', 'B', 'C', 'D' ) <--
------------------------------------------------------------------------------------------------
0.0.1.5		30.03.05	Methode 'static bool saveCustomers()' angepasst:
                            -   bei jedem Schleifendurchlauf wird das Objekt objSCustomRoutingTable
                                der Klasse SCustomRoutingTable reinitialisiert;
                            -   pro Schleifendurchlauf wird nur noch ein Datensatz mit der TelNr 
                                aus der Tabelle 'customerphoneno' in die Tabelle 'customroutingtable' 
                                weggeschrieben 
                            FRUEHER:    - ein Datensatz fuer die TelNr aus der Tabelle 'kunde' und 
                                        - ein Datensatz fuer die TelNr aus der Tabelle 'customerphoneno'
------------------------------------------------------------------------------------------------
0.0.1.6		11.05.05	Methode 'retClient prepareSKundeSelect()' angepasst:
                            - bei Kunden-Select werden noch zusaetzlich die Kunden-Attribute 
                              'NameApo' und 'Ort' selektiert
                        Methode 'retClient eraseSCustomRoutingTable()' angepasst:
                            - bei Löschen von alten Saetzen via Datum, muss auf das Verschieben 
                              des Datums Ruecksicht genommen werden
------------------------------------------------------------------------------------------------
0.0.1.7		11.05.05	Aufbau von customroutingtabel:caption:
                        'VZ00IDFNR000DATUMAPONAME ORT'
------------------------------------------------------------------------------------------------
0.0.1.8		02.12.05	Dem Attribut 'CALLTYPE' des struct 'SQLSCUSTOMROUTINGTABLE'
						wird ueber die init()-Methode der Wert 'AA_Netzweit' zugewiesen.
------------------------------------------------------------------------------------------------
0.0.1.9		23.01.06	Fuer die Filialen 12, 13 und 14 im Attribut 'calltype' der Tabelle 
						'customroutingtable' ein Undeline und das erste Zeichen des Attributes 
						'kzsprache' der Tabelle 'kunde' angehaengt.
------------------------------------------------------------------------------------------------
0.0.1.10	23.01.06	Filialspezifische if eingebaut.
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
0.0.1.11	20.06.07	Bestimmte Kunden werden am Schluss des programmes geloescht.
						Fuer diesen Vorgang muss/wird das aktuelle Datum herangezogen.
						Dieses datum wird jedoch ers generiert, wenn das entsprechende 
						Delete-Statement gebaut wird.
						Nun gab es am folgenden Vorfall:
						Start des Programmes:	19.06.07 23:59:19 
						Ende des Programmes:	20.06.07 00:00:03
						Hieraus wird ersichtlich, dass das Programm in den neuen Tag rein lief
						und deswegen fuer den Delete das Datum des neuen Tages zog.
						Aufgrund dieser Auswirkung wurden die falschen Kunden geloescht.
						ABHILFE:	es wird am Anfang/Start des Programmes gleich das Datum eingelesen
									und nicht mehr veraendert. Ein Tageswechsel waehrend des 
									Programmlaufes hat somit keine (fehlerhafte) Auswirkungen 
									mehr auf das Loeschen von Kunden.
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
0.0.1.12	25.06.07	in der Methode 'static bool saveCustomers()' wurde immer noch der Aufruf 
						'CDate::getDateJJJJMMDD()' verwendet und nicht gegen die Variable 
						'lDateOfRunning' ersetzt.
------------------------------------------------------------------------------------------------
0.0.2.00	26.06.09	
------------------------------------------------------------------------------------------------
0.0.2.001   22.09.09	Fuer alle VZs wird der Kunden-Select (kundesql.cxx) angepasst, um 
                        "and (k.originalfilialnr = k.vertriebszentrumnr or k.originalfilialnr = 0) "
------------------------------------------------------------------------------------------------
0.0.2.02    21.08.20	Added "and k.kdgruppe in ('01','02','03','06') " in order to include only
                        the direct users.
------------------------------------------------------------------------------------------------
*/
///////////////////////////////////////////////////////////////////////////////////////
// version defines
///////////////////////////////////////////////////////////////////////////////////////
#define PROGNAME			"tpldhipath" 
#define PROG_VERSION         "0.0.2.02" // update version-history at the top

#ifndef NDEBUG // DEBUG-MODUS 
	#define PRZ_PROG_NAME   PROGNAME" dbg -v "PROG_VERSION
#else
	#define PRZ_PROG_NAME   PROGNAME" rel -v "PROG_VERSION
#endif

static char *SCCSID=(char *)"@(#)PRZ GMBH Stand "PRZ_PROG_NAME;


#define ANZ_DBGLOOP 100000

//////////////////////////////////////////////////
// forward declaration 
//////////////////////////////////////////////////
static void		prepareLogging();
static void		cleanUp();
static string	assSpecLogFile();
static string	assStartEndMsg( const string& sStartEnd );
static void		logStatusMsg();
static bool		loadCustomers();
static bool		getEnvVars();
static bool		saveCustomers();
static bool		eraseCustomers();

//////////////////////////////////////////////////
// modul gloabl variables 
//////////////////////////////////////////////////
static const long lDateOfRunning = CDate::getDateJJJJMMDD();
static string m_cbErrMsg;
typedef list<S_SQLKUNDE> TCON_SKUNDESELECT;
static TCON_SKUNDESELECT _objVecSKundeSelect;

//////////////////////////////////////////////////////////////////////////////
// struct 4 environment variables
//////////////////////////////////////////////////////////////////////////////
struct EnvVar
{
    EnvVar()
    :_bsLogDftFile( "" ), _bsLogErrFile( "" ), _bsLogPath( "" ), 
    _bsDataPath( "" ), _bsPersistenceMode( "" ), _bsFileDelimiter(""), _uiNoTransAction( 0 )
    {
    }
    string       _bsLogDftFile;
    string       _bsLogErrFile;
    string       _bsLogPath;
    string       _bsDataPath;
    string       _bsPersistenceMode;
    string       _bsFileDelimiter;
    unsigned int _uiNoTransAction;


    static const char* const SPNUMBER_TRANSACTIONS;
    static const char* const SPLOG_DFT_FILE;
	static const char* const SPLOG_ERR_FILE;
	static const char* const SPLOG_PATH;
	static const char* const SPDATA_PATH;
	static const char* const SPPERSISTENCE_MODE;
    static const char* const SP_FILE_SAVE;
    static const char* const SP_DB_SAVE;
    static const char* const SPFILE_DELIMITER;
};
const char* const EnvVar::SPNUMBER_TRANSACTIONS = "NUMBER_TRANSACTIONS";
const char* const EnvVar::SPLOG_DFT_FILE		= "LOG_DFT_FILE";
const char* const EnvVar::SPLOG_ERR_FILE		= "LOG_ERR_FILE";
const char* const EnvVar::SPLOG_PATH			= "LOG_PATH";
const char* const EnvVar::SPDATA_PATH		    = "DATA_PATH";
const char* const EnvVar::SPPERSISTENCE_MODE	= "PERSISTENCE_MODE";
const char* const EnvVar::SPFILE_DELIMITER      = "FILE_DELIMITER";
const char* const EnvVar::SP_FILE_SAVE          = "1";
const char* const EnvVar::SP_DB_SAVE            = "0";

EnvVar _envVar;

ostringstream _osErrMsg;
static struct S_Counter stS_CounterKundeSel;
static struct S_Counter stS_CounterCRTUpsIns;


///////////////////////////////////////////////////////////////////////////////
// enum ESQLRet
///////////////////////////////////////////////////////////////////////////////
enum ESQLRet
{
	OK,
	ERR
};

///////////////////////////////////////////////////////////////////////////////
// factory method
///////////////////////////////////////////////////////////////////////////////
static CmdLine* cmdLine = 0;
CmdLine* getCmdLine()
{
    if( 0 == cmdLine ){
        if( EnvVar::SP_DB_SAVE == _envVar._bsPersistenceMode ){
            cmdLine = new CmdLineDB();
        } else if( EnvVar::SP_FILE_SAVE  == _envVar._bsPersistenceMode ){
           cmdLine = new CmdLineFile();
        }
    }
    return cmdLine;
}

static Persistence* persistence = 0;
//static PersistenceDB persistence;

//PersistenceDB* getPersistence()
//{
//    return &persistence;
//}
Persistence* getPersistence()
{
    if( 0 == persistence ){
        if( EnvVar::SP_DB_SAVE == _envVar._bsPersistenceMode ){
            persistence = new PersistenceDB();
            //persistence = &persistenceDB;
        } else if( EnvVar::SP_FILE_SAVE  == _envVar._bsPersistenceMode ){
            persistence = new PersistenceFile( _envVar._bsFileDelimiter );
        }
    }
    return persistence;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// int main(int argc, char* argv[])
///////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	__FUNCTION__( main() )
	DEBUG_ENTER( fun ) 

	enum E_RC{ OK = 0, ERROR = 1, WARNING = 2 };

	///////////////////////////////////////////////////////////////////////////
	// start message
	///////////////////////////////////////////////////////////////////////////
	cout << "Programm gestartet: " << argv[0] << endl;

	///////////////////////////////////////////////////////////////////////////
	// read in environment variables
	///////////////////////////////////////////////////////////////////////////
	if( getEnvVars()== false ){
		cerr << _osErrMsg.str().c_str() << endl;
		return ERROR;
	}

	////////////////////////////////////////////////////////
	// commandline parameters will be read
	////////////////////////////////////////////////////////
    if( getCmdLine()->readCmdLine( argc, argv ) == false ){
		cout << getCmdLine()->m_osErrMsg.str() << endl;		
		return ERROR;
	}
	if(getCmdLine()->m_bVersion){
		printVersion(versioninfo);
		return OK;
	}
	


#ifndef NDEBUG
	//getCmdLine()->toStream();
    //return 0;
#endif
	////////////////////////////////////////////////////////
	// prepare the logging
	////////////////////////////////////////////////////////
	prepareLogging();
	
	////////////////////////////////////////////////////////
	// start logging
	////////////////////////////////////////////////////////
	SLogFile::Exemplar()->log( fun, SLogFile::OK, assStartEndMsg(TXT_START) );

	ostringstream os;
	os << "Datum des Laufes: >" << lDateOfRunning << "<";
	SLogFile::Exemplar()->log( fun, SLogFile::OK, os.str().c_str() );
    
    ////////////////////////////////////////////////////////
	// try to open the source-database
	////////////////////////////////////////////////////////
	tError stError;
	if( OpenDb( getCmdLine()->m_sSrcDatabase.c_str(), &stError ) != IS_OK ){
		SLogFile::Exemplar()->log( fun, SLogFile::ERROR, stError.spError );
		return ERROR;
	}

	if( SetIsolation(DIRTY_READ, &stError) != IS_OK ){
		SLogFile::Exemplar()->log( fun, SLogFile::ERROR, stError.spError );
		return ERROR;
	}

	///////////////////////////////////////////////////////////////////////////
	//  select customer
	///////////////////////////////////////////////////////////////////////////
	if( loadCustomers() == false ){
		SLogFile::Exemplar()->log( fun, SLogFile::ERROR, _osErrMsg.str().c_str() );
		if( CloseDb( &stError ) != IS_OK ){
			SLogFile::Exemplar()->log( fun, SLogFile::ERROR, stError.spError );
		}
		return ERROR;
	}

	////////////////////////////////////////////////////////
	// close the source-database
	////////////////////////////////////////////////////////
	if( CloseDb( &stError ) != IS_OK ){
		SLogFile::Exemplar()->log( fun, SLogFile::ERROR, stError.spError );
		return ERROR;
	}

    //################################################################################################//
	////////////////////////////////////////////////////////
	// try to open the DESTINATION-database
	////////////////////////////////////////////////////////
    if( false == getPersistence()->open(getCmdLine()->getResource()) ){
        SLogFile::Exemplar()->log( fun, SLogFile::ERROR, getPersistence()->getErrMsg() );
		return ERROR;
    }

	////////////////////////////////////////////////////////
	// save table 'customroutingtable'
	////////////////////////////////////////////////////////
    std::pair<bool, S_Counter > retSave = getPersistence()->processAndSave( _objVecSKundeSelect, lDateOfRunning ); 
    stS_CounterCRTUpsIns = retSave.second;
    if( false == retSave.first ){
        SLogFile::Exemplar()->log( fun, SLogFile::ERROR, getPersistence()->getErrMsg() );
		return ERROR;
    }
    
    ////////////////////////////////////////////////////////
	// delete customers not inserted or updated
	////////////////////////////////////////////////////////
    std::pair<bool, unsigned long> retErase = getPersistence()->erase( getCmdLine()->m_uiDC, lDateOfRunning );
    stS_CounterCRTUpsIns.ulDel = retErase.second;
    if( false == retErase.first ){
        SLogFile::Exemplar()->log( fun, SLogFile::ERROR, getPersistence()->getErrMsg() );
		return ERROR;
    }

	///////////////////////////////////////////////////////////////////////////
	// close the destination-database
	///////////////////////////////////////////////////////////////////////////
    if( false == getPersistence()->close() ){
        SLogFile::Exemplar()->log( fun, SLogFile::ERROR, getPersistence()->getErrMsg() );
		return ERROR;
    }

	////////////////////////////////////////////////////////
	// status messages
	////////////////////////////////////////////////////////
	logStatusMsg();
	SLogFile::Exemplar()->log( fun, SLogFile::OK, assStartEndMsg(TXT_STOP) );
	
    ////////////////////////////////////////////////////////
	// relase of dynamic memory
	////////////////////////////////////////////////////////
	cleanUp();

	///////////////////////////////////////////////////////////////////////////
	// start message
	///////////////////////////////////////////////////////////////////////////
	cout << "Programm beendet: " << argv[0] << endl;
	
	DEBUG_LEAVE(fun)
	return OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// static bool eraseCustomers()
///////////////////////////////////////////////////////////////////////////////////////////////////
static void cleanUp()
{
	__FUNCTION__( eraseCustomers() )
	DEBUG_ENTER( fun ) 	
    
    delete cmdLine;
    delete persistence;

	DEBUG_LEAVE( fun )
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// static bool eraseCustomers()
///////////////////////////////////////////////////////////////////////////////////////////////////
static bool eraseCustomers()
{
	__FUNCTION__( eraseCustomers() )
	DEBUG_ENTER( fun ) 	
    
	ostringstream os;
	os << "Aufruf Methode 'SCustomRoutingTable::erase(" << getCmdLine()->m_uiDC << ", " << lDateOfRunning << ")'";
	SLogFile::Exemplar()->log( fun, SLogFile::OK, os.str().c_str() );
    
	SCustomRoutingTable objSCustomRoutingTable;
	bool bErased =  objSCustomRoutingTable.erase( getCmdLine()->m_uiDC, lDateOfRunning );
    
    _osErrMsg.str("");
    _osErrMsg << objSCustomRoutingTable.getErrMsg();    

    stS_CounterCRTUpsIns.ulDel = objSCustomRoutingTable.m_stS_Counter.ulDel;

	DEBUG_LEAVE( fun )
	return bErased;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// static bool saveCustomers()
///////////////////////////////////////////////////////////////////////////////////////////////////
static bool saveCustomers()
{
	__FUNCTION__( saveCustomers() )
    DEBUG_ENTER( fun )

	bool bSaved = true;
	SCustomRoutingTable objSCustomRoutingTable;
	ostringstream os;
	_osErrMsg.str("");
	unsigned int uiNoTransAction = 0;
	TCON_SKUNDESELECT::const_iterator it;
	for( it = _objVecSKundeSelect.begin(); it != _objVecSKundeSelect.end(); ++it ){
		uiNoTransAction++;
        objSCustomRoutingTable.init();

		if( it->isValidCustomerPhoneNo_TelNr() == false ){
        	continue;
        }
        os.str("");
		os << "0" << it->CUSTOMERPHONENO_TELNR;
		strcpy( objSCustomRoutingTable.m_stSQLSTRUCT.ORIGIN, os.str().c_str() );

        //  CALLTYPE
		if( strlen(it->PHONEPRIORITY) > 0 ){
			switch( it->PHONEPRIORITY[0] ){
				case 'V':	os.str("");
							os << "AA_VIP";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable.m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable.m_stSQLSTRUCT.INITIALPRIORITY = 89;
							break;
				case 'A':	os.str("");
							os << "AA_Netzweit";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable.m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable.m_stSQLSTRUCT.INITIALPRIORITY = 80;
							break;
				case 'B':	os.str("");
							os << "AA_Netzweit";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable.m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable.m_stSQLSTRUCT.INITIALPRIORITY = 60;
							break;
				case 'C':	os.str("");
							os << "AA_Netzweit";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable.m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable.m_stSQLSTRUCT.INITIALPRIORITY = 40;
							break;
				case 'D':	os.str("");
							os << "AA_Netzweit";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable.m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable.m_stSQLSTRUCT.INITIALPRIORITY = 20;
							break;
				case 'S':	os.str("");
							os << "AA_Sonder";
							if( (12 == it->VERTRIEBSZENTRUMNR) || 
								(13 == it->VERTRIEBSZENTRUMNR) || 
								(14 == it->VERTRIEBSZENTRUMNR) ){
									os << "_" << it->KZSPRACHE[0];
							}
							strcpy( objSCustomRoutingTable.m_stSQLSTRUCT.CALLTYPE, os.str().c_str() );
							objSCustomRoutingTable.m_stSQLSTRUCT.INITIALPRIORITY = 89;
							break;

				default:	continue;
			}
		}
		//  CAPTION
		os.str("");
		os  << right << setw( 2 )   << setfill( '0' )   << it->VERTRIEBSZENTRUMNR
		    << right << setw( 7 )                       << it->KUNDENNR 
		    << right << setw( 8 )                       << lDateOfRunning
            << right                                    << " " 
            << right                                    << it->NAMEAPO 
            << right                                    << " " 
            << right                                    << it->ORT;
		strcpy( objSCustomRoutingTable.m_stSQLSTRUCT.CAPTION, os.str().c_str() );

#ifndef NDEBUG
		objSCustomRoutingTable.toStream();
#endif
        if( objSCustomRoutingTable.save() == false ){
			_osErrMsg.str("");
			_osErrMsg << objSCustomRoutingTable.getErrMsg();
			bSaved = false;
			break;
		}
	} // ENDE FOR
	
    stS_CounterCRTUpsIns.ulUpd = objSCustomRoutingTable.m_stS_Counter.ulUpd;
    stS_CounterCRTUpsIns.ulIns = objSCustomRoutingTable.m_stS_Counter.ulIns;

	return bSaved;
}

///////////////////////////////////////////////////////////////////////////////////
// static bool loadCustomers()
///////////////////////////////////////////////////////////////////////////////////
static bool loadCustomers()
{
	__FUNCTION__( loadCustomers() )
	DEBUG_ENTER( fun )

	_osErrMsg.str(""); 

	SKundeSelect objSKundeSelect;
	if( objSKundeSelect.prepare() == false ){
		_osErrMsg << objSKundeSelect.getErrMsg();
		return false;
	}

	int iDbgLoop = 0;
	objSKundeSelect.m_stSQLSTRUCT.VERTRIEBSZENTRUMNR = getCmdLine()->m_uiDC;
	while( objSKundeSelect.load() ){
		iDbgLoop++;
		/*
		if( 0 == (objSKundeSelect.m_stS_Counter.ulSel % 100) ){
			_osErrMsg.str(""); 
			_osErrMsg << fun << "Treffer-Sel.: " << objSKundeSelect.m_stS_Counter.ulSel;
			SLogFile::Exemplar()->log( fun, SLogFile::OK, _osErrMsg.str().c_str() );			
		}
		*/
		_objVecSKundeSelect.push_back( objSKundeSelect.m_stSQLSTRUCT );

#ifndef NDEBUG
		//objSKundeSelect.toStream();
		if( ANZ_DBGLOOP == iDbgLoop ){
			break;
		}
#endif
	} // ENDE WHILE 

	objSKundeSelect.free();
	stS_CounterKundeSel = objSKundeSelect.m_stS_Counter;

	DEBUG_LEAVE( fun )
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// static bool getEnvVars()
////////////////////////////////////////////////////////////////////////////////////////////////////
static bool getEnvVars()
{
	__FUNCTION__( getEnvVars() )	
	DEBUG_ENTER( fun )

	bool bRead = true;
	
    char* spEnvVar = getenv( EnvVar::SPNUMBER_TRANSACTIONS );
    if( spEnvVar != 0 ){
        _envVar._uiNoTransAction = atoi(spEnvVar);
    }
    
    spEnvVar = getenv( EnvVar::SPLOG_DFT_FILE );
    if( spEnvVar != 0 ){
        _envVar._bsLogDftFile = spEnvVar;
    }
    
    spEnvVar = getenv( EnvVar::SPLOG_ERR_FILE );
    if( spEnvVar != 0 ){
        _envVar._bsLogErrFile = spEnvVar;
    }
    
    spEnvVar = getenv( EnvVar::SPLOG_PATH );
    if( spEnvVar != 0 ){
        _envVar._bsLogPath = spEnvVar;
    }

    spEnvVar = getenv( EnvVar::SPDATA_PATH );
    if( spEnvVar != 0 ){
        _envVar._bsDataPath = spEnvVar;
    }

    spEnvVar = getenv( EnvVar::SPPERSISTENCE_MODE );
    if( spEnvVar != 0 ){
        _envVar._bsPersistenceMode = spEnvVar;
    }
    
    spEnvVar = getenv( EnvVar::SPFILE_DELIMITER );
    if( spEnvVar != 0 ){
        _envVar._bsFileDelimiter = spEnvVar;
    } 

	if( _envVar._bsLogDftFile.empty()	    || _envVar._bsLogErrFile.empty()	|| 
		_envVar._bsLogPath.empty()		    || _envVar._bsDataPath.empty()      || 
        _envVar._bsPersistenceMode.empty()  || (_envVar._uiNoTransAction == 0)	){
		bRead = false;
	}
	_osErrMsg	<< "Folgende Umgebungs-Variablen muessen gesetzt sein: "
				<< EnvVar::SPNUMBER_TRANSACTIONS	<< ", " 
				<< EnvVar::SPLOG_DFT_FILE			<< ", " 
				<< EnvVar::SPLOG_ERR_FILE			<< ", " 
				<< EnvVar::SPLOG_PATH				<< ", "
				<< EnvVar::SPDATA_PATH				<< ", "
    		    << EnvVar::SPPERSISTENCE_MODE       << ";";
	
	DEBUG_LEAVE( fun )
	return bRead;
}
//#####################################################################################################//
// std::string assSpecLog File()
//#####################################################################################################//
static string assSpecLogFile()
{
	__FUNCTION__( assSpecLogFile() )
	DEBUG_ENTER( fun )

	// to assemble the programm specific log file name
	ostringstream os;
	os	<< getCmdLine()->m_sProgName
		<< TXT_DOT_CHAR
		<< getCmdLine()->m_uiDC
		<< TXT_DOT_CHAR
		<< TXT_LOG_FILE_EXT;


	DEBUG_LEAVE( fun )
	return os.str();
}
//####################################################################################//
// std::string assStartEndMsg( const string& sStartEnd )
//####################################################################################//
static string assStartEndMsg( const string& sStartEnd )
{
	__FUNCTION__( main::assStartEndMsg() )
	DEBUG_ENTER( fun )

	// assembling start string 
	ostringstream os;
    if( sStartEnd == TXT_START ){
        os << setw( 90 ) << setfill( '=' ) << "=" << endl; 
    }
	os	<< setw( 3 ) << setfill(TXT_EQUALS_SIGN_CHAR) << TXT_EQUALS_SIGN_CHAR 
		<< TXT_SPACE_CHAR
		<< setw( sStartEnd.length() ) << setfill('=') 
		<< sStartEnd << TXT_COLON 
		<< " "
		<< PROGNAME			
		<< " "
		<< "(" 
		<< PROG_VERSION         
		<< ")" 
		<< " "
		<< PRZ_PROG_NAME		
		<< " ";
    getCmdLine()->toStream( os );
		/*<< SCmdLinePara::SP_SRCDB
		<< " "
		<< getCmdLine()->m_sSrcDatabase
		<< " "
		<< SCmdLinePara::SP_DSTDB
		<< " "
		<< getCmdLine()->m_sDstDatabase
		<< " "
		<< SCmdLinePara::SP_DC
		<< " "
		<< getCmdLine()->m_uiDC;*/
    os << setw( 3 ) << left << setfill(' ') << TXT_EQUALS_SIGN_CHAR;
    if( sStartEnd == TXT_STOP ){
        os << setw( 90 ) << setfill( '=' ) << "=" << endl; 
    }

	DEBUG_LEAVE( fun )
	return os.str();
}
//####################################################################################//
// void logStatusMsg()
//####################################################################################//
static void logStatusMsg()
{
	__FUNCTION__( main::logStatusMsg() )
	DEBUG_ENTER( fun )

	char spMsg[80];	
	
	// load customer 
	sprintf( spMsg, TXT_NO_TAB_SEL, "kunde", stS_CounterKundeSel.ulSel );
	SLogFile::Exemplar()->log( fun, SLogFile::OK, spMsg );
	
	// update/insert customroutingtable
	sprintf( spMsg, TXT_NO_TAB_UPS, "customroutingtable", stS_CounterCRTUpsIns.ulUpd );
	SLogFile::Exemplar()->log( fun, SLogFile::OK, static_cast<string>(spMsg) );

	sprintf( spMsg, TXT_NO_TAB_INS, "customroutingtable", stS_CounterCRTUpsIns.ulIns );
	SLogFile::Exemplar()->log( fun, SLogFile::OK, static_cast<string>(spMsg) );

	sprintf( spMsg, TXT_NO_TAB_DEL, "customroutingtable", stS_CounterCRTUpsIns.ulDel );
	SLogFile::Exemplar()->log( fun, SLogFile::OK, static_cast<string>(spMsg) );

	sprintf( spMsg, TXT_NO_TAB_SER, "customroutingtable", stS_CounterCRTUpsIns.ulSerialized );
	SLogFile::Exemplar()->log( fun, SLogFile::OK, static_cast<string>(spMsg) );
	
	DEBUG_LEAVE( fun )
}
//####################################################################################//
// static void prepareLogging()
//####################################################################################//
static void prepareLogging()
{	
	__FUNCTION__( main::prepareLogging() )
	DEBUG_ENTER( fun )

	SLogFile::Exemplar()->setDCNo( static_cast<unsigned short>(getCmdLine()->m_uiDC) );
	SLogFile::Exemplar()->setProgName(		getCmdLine()->m_sProgName );
	SLogFile::Exemplar()->setLogPath(		_envVar._bsLogPath );
	SLogFile::Exemplar()->setDftLogFile(	_envVar._bsLogDftFile );
	SLogFile::Exemplar()->add(				assSpecLogFile() );
	
	DEBUG_LEAVE( fun )
}

