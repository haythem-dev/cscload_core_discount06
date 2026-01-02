#ifndef __KUNDE_H__
#define __KUNDE_H____KUNDE_H__


//#####################################################################################################//
// includes
//#####################################################################################################//
#include <string.h>
#include "sql.h"
#include "structs.h"

#ifdef ESQL_C
	EXEC SQL BEGIN DECLARE SECTION;
#endif

//#####################################################################################################//
// struct S_SQLBLieSort
//#####################################################################################################//
struct S_SQLKUNDE
{
#ifndef ESQL_C
	void init()
	{
		KUNDENNR						= 0;
		VERTRIEBSZENTRUMNR				= 0;
        strncpy( NAMEAPO,			    " ", 40);
        strncpy( ORT,			        " ", 30);
		strncpy( KUNDE_TELNR,			" ", 20);
		strncpy( KZKDKLASSE,			" ", 3);
		strncpy( PHONEPRIORITY,			" ", 1);
		strncpy( CUSTOMERPHONENO_TELNR, " ", 20);
		strncpy( KZSPRACHE,				" ", 2);
	};

	bool isValidKunde_TelNr() const
	{
		if( strlen(KUNDE_TELNR) <= 4 ){
			return false;
		}
		return true;
	};
	bool isValidCustomerPhoneNo_TelNr() const
		{
			if( strlen(CUSTOMERPHONENO_TELNR) <= 4 ){
			return false;
		}
		return true;
	};

#endif

	long    KUNDENNR           ;
	short   VERTRIEBSZENTRUMNR ;
    char    NAMEAPO                 [40+1];
    char    ORT                     [30+1];
	char    KUNDE_TELNR				[20+1];
	char    KZKDKLASSE				[3+1];
	char    PHONEPRIORITY			[1+1];
	char    CUSTOMERPHONENO_TELNR   [20+1];
	char    KZSPRACHE				[2+1];
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
// struct SKundeSelect
//#####################################################################################################//
struct SKundeSelect
{
	SKundeSelect();
	~SKundeSelect();

	void init();
	bool prepare();
	void free();
	bool load();
    void trim( string& sSegment );

	
	const char* getErrMsg();
	void toStream( ostream& strm = std::cout );

	S_SQLKUNDE m_stSQLSTRUCT;
	S_Counter m_stS_Counter;
	tError m_stError;
};
#endif

//////////////////////////////////////////////////////////////////////////////////
// struct desciption
//////////////////////////////////////////////////////////////////////////////////
#define STRUCDESC_SKUNDESELECT	"lsc20c3c1c20"


#endif /* __KUNDE_H__ */
