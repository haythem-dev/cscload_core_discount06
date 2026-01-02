#ifndef __SCUSTOMROUTINGTABLE_H__
#define __SCUSTOMROUTINGTABLE_H__ __SCUSTOMROUTINGTABLE_H__

//#####################################################################################################//
// includes
//#####################################################################################################//
#include "sql.h"
#include "structs.h"

#ifndef ESQL_C
#include <iostream>
#endif

#ifdef ESQL_C
	EXEC SQL BEGIN DECLARE SECTION;
#endif

//#####################################################################################################//
// struct SQLSTRUCT
//#####################################################################################################//
struct SQLSCUSTOMROUTINGTABLE
{
#ifndef ESQL_C
    SQLSCUSTOMROUTINGTABLE()
        : m_Delimiter( "|" )
    {
        init();
    }

    SQLSCUSTOMROUTINGTABLE( const string& delimiter)
    : m_Delimiter( delimiter == "" ? "|" : delimiter )
    {
        init(); 
    }

	void init()
	{
		strncpy( ORIGIN,			" ", 80);
		
		strncpy( CALLTYPE,			" ", 16);
		strcpy(  CALLTYPE,			"AA_Netzweit");

		INITIALPRIORITY  = 0;
		strncpy( RESERVEAGENTID,	" ", 8);
		strncpy( RESERVEAGENTSITE,	" ", 16);
		RESERVEAGENTTIME = 0;
		strncpy( CAPTION,			" ", 100);
		strncpy( CALLDATA,			" ", 1000);
		strncpy( DDE,				" ", 1000);

        //datecreated          char(9)  no
        //flagdatatype         smallint no
	};

    void toSerialize( S_Counter& counter, std::ostream& strm = std::cout )
    {
        strm    <<  eraseSpace( ORIGIN )            << m_Delimiter
	            <<  eraseSpace( CALLTYPE )          << m_Delimiter
	            <<  INITIALPRIORITY                 << m_Delimiter
	            <<  eraseSpace( RESERVEAGENTID )    << m_Delimiter
	            <<  eraseSpace( RESERVEAGENTSITE )  << m_Delimiter
	            <<  RESERVEAGENTTIME                << m_Delimiter
	            <<  eraseSpace( CAPTION )           << m_Delimiter
	            <<  eraseSpace( CALLDATA )          << m_Delimiter
	            <<  eraseSpace( DDE )               << m_Delimiter
	            <<  " "                             << m_Delimiter
	            <<  2                               
	            <<  std::endl;  
        /*
        strm    <<  ORIGIN            << m_Delimiter
	            <<  CALLTYPE          << m_Delimiter
	            <<  INITIALPRIORITY   << m_Delimiter
	            <<  RESERVEAGENTID    << m_Delimiter
	            <<  RESERVEAGENTSITE  << m_Delimiter
	            <<  RESERVEAGENTTIME  << m_Delimiter
	            <<  CAPTION           << m_Delimiter
	            <<  CALLDATA          << m_Delimiter
	            <<  DDE               << m_Delimiter
	            <<  " "               << m_Delimiter
	            <<  0                 << m_Delimiter
	            <<  std::endl;  */

        counter.ulSerialized++;
    }

    string eraseSpace( string str )
    {
        if( 1 < str.length() ){
            string::size_type pos = string::npos;
            pos = str.find_last_not_of( ' ' );
            if( string::npos != pos ){
                str = str.substr( 0, pos+1 );
            }
            pos = str.find_first_not_of( ' ' );
            if( string::npos != pos ){
                str = str.substr( pos );
            }
        }
        return str;
    } 

    const string m_Delimiter;
#endif

	char    ORIGIN           [81];
	char    CALLTYPE         [17];
	short   INITIALPRIORITY  ;
	char    RESERVEAGENTID   [9];
	char    RESERVEAGENTSITE [17];
	short   RESERVEAGENTTIME ;
	char    CAPTION          [101];
	char    CALLDATA         [1001];
	char    DDE              [1001];
};

#ifdef ESQL_C
	EXEC SQL END DECLARE SECTION;
#endif

#ifndef ESQL_C

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//#####################################################################################################//
// struct SCustomRoutingTable
//#####################################################################################################//
struct SCustomRoutingTable
{
	SCustomRoutingTable();
    SCustomRoutingTable( const string& delimiter );
	~SCustomRoutingTable();

	void init();
	bool prepare();
	void free();
	bool save();
    bool erase( const unsigned int, const long );
    void toSerialize( ostream& strm = std::cout );

	const char* getErrMsg();
	void toStream( ostream& strm = std::cout );

	SQLSCUSTOMROUTINGTABLE m_stSQLSTRUCT;
	S_Counter m_stS_Counter;
	tError m_stError;
};
#endif

//////////////////////////////////////////////////////////////////////////////////
// struct description
//////////////////////////////////////////////////////////////////////////////////
#define STRUCDESC_CUSTOMROUTINGTABLE	"c80c16sc8c16sc100c1000c1000"

#define CRT_UPDATE_LIST					"ORIGIN = ?,"					\
										"CALLTYPE = ?,"					\
										"INITIALPRIORITY = ?,"			\
										"RESERVEAGENTID = ?,"			\
										"RESERVEAGENTSITE = ?,"			\
										"RESERVEAGENTTIME = ?,"			\
										"CAPTION = ?,"					\
										"CALLDATA = ?,"					\
										"DDE = ?"

#define CRT_INSUPD_ARGUMENTS( argu )	:argu->ORIGIN,				\
										:argu->CALLTYPE,			\
										:argu->INITIALPRIORITY,		\
										:argu->RESERVEAGENTID,		\
										:argu->RESERVEAGENTSITE,	\
										:argu->RESERVEAGENTTIME,	\
										:argu->CAPTION,				\
										:argu->CALLDATA,			\
										:argu->DDE

#define CRT_ATTRIBUTLISTE_AS_STRING									\
										"ORIGIN,"					\
										"CALLTYPE,"					\
										"INITIALPRIORITY,"			\
										"RESERVEAGENTID,"			\
										"RESERVEAGENTSITE,"			\
										"RESERVEAGENTTIME,"			\
										"CAPTION,"					\
										"CALLDATA,"					\
										"DDE"
#endif /* __SCUSTOMROUTINGTABLE_H__ */

