/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_FILINF_FILIALNR             6
 #define L_FILINF_NAME                 30
 #define L_FILINF_STANDORT_KURZ        2
 #define L_FILINF_STANDORT_LANG        15
 #define L_FILINF_ORT                  30
 #define L_FILINF_CLOSED_FROM          11
 #define L_FILINF_CLOSED_UNTIL         11
 #define L_FILINF_LAGERORTLEN          6
 #define L_FILINF_PROCENTERNAME        16
 #define L_FILINF_VORWAHL			   10
 #define L_FILINF_PROCENTERLOCATION    16
 #define L_FILINF_TELNR				   20
 #define L_FILINF_FAXNR				   25
 #define L_FILINF_POSTLEITZAHL		   10
 #define L_FILINF_STRASSE			   30
 #define L_FILINF_BALANCE1		       16
 #define L_FILINF_BALANCE2		       16
 #define L_FILINF_BGANR_EK		       11
 #define L_FILINF_REGIONNO             6


 #define L_FILINF_PKEY 6

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define FILINF_ANZ ( sizeof(FILINF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_FILINF sizeof(struct FILINF)


 #define FILINF_H

 #define FILINF_LISTE \
 			FILIALE.FILIALNR, \
 			FILIALE.NAME, \
 			FILIALE.STANDORT_KURZ, \
 			FILIALE.STANDORT_LANG, \
 			FILIALE.ORT, \
 			FILIALE.CLOSED_FROM, \
 			FILIALE.CLOSED_UNTIL, \
 			FILIALE.LAGERORTLEN, \
 			FILIALE.PROCENTERNAME, \
 			FILIALE.VORWAHL, \
 			FILIALE.PROCENTERLOCATION, \
 			FILIALE.TELNR, \
 			FILIALE.FAXNR, \
 			FILIALE.POSTLEITZAHL, \
 			FILIALE.STRASSE, \
 			FILIALE.BALANCE1, \
 			FILIALE.BALANCE2, \
 			FILIALE.BGANR_EK, \
 			FILIALE.REGIONNO
 #define FILINF_PLISTE \
 			"FILIALE.FILIALNR," \
 			"FILIALE.NAME," \
 			"FILIALE.STANDORT_KURZ," \
 			"FILIALE.STANDORT_LANG," \
 			"FILIALE.ORT," \
 			"FILIALE.CLOSED_FROM," \
 			"FILIALE.CLOSED_UNTIL," \
 			"FILIALE.LAGERORTLEN," \
 			"FILIALE.PROCENTERNAME," \
 			"FILIALE.VORWAHL," \
 			"FILIALE.PROCENTERLOCATION," \
 			"FILIALE.TELNR," \
 			"FILIALE.FAXNR," \
 			"FILIALE.POSTLEITZAHL," \
 			"FILIALE.STRASSE," \
 			"FILIALE.BALANCE1," \
 			"FILIALE.BALANCE2," \
 			"FILIALE.BGANR_EK," \
 			"FILIALE.REGIONNO "

 #define FILINF_PELISTE \
 			"FILIALNR," \
 			"NAME," \
 			"STANDORT_KURZ," \
 			"STANDORT_LANG," \
 			"ORT," \
 			"CLOSED_FROM," \
 			"CLOSED_UNTIL," \
 			"LAGERORTLEN," \
 			"PROCENTERNAME," \
 			"VORWAHL," \
 			"PROCENTERLOCATION," \
 			"TELNR," \
 			"FAXNR," \
 			"POSTLEITZAHL," \
 			"STRASSE," \
 			"BALANCE1," \
 			"BALANCE2," \
 			"BGANR_EK," \
 			"REGIONNO "

 #define FILINF_UPDLISTE \
 			"FILIALNR=?," \
 			"NAME=?," \
 			"STANDORT_KURZ=?," \
 			"STANDORT_LANG=?," \
 			"ORT=?," \
 			"CLOSED_FROM=?," \
 			"CLOSED_UNTIL=?," \
 			"LAGERORTLEN=?," \
 			"PROCENTERNAME=?," \
 			"VORWAHL=?," \
 			"PROCENTERLOCATION=?," \
 			"TELNR=?," \
 			"FAXNR=?," \
 			"POSTLEITZAHL=?," \
 			"STRASSE=?," \
 			"BALANCE1=?," \
 			"BALANCE2=?," \
 			"BGANR_EK=?," \
 			"REGIONNO=? "

 #define FILINFFILIALNR                      0
 #define FILINFNAME                          1
 #define FILINFSTANDORT_KURZ                 2
 #define FILINFSTANDORT_LANG                 3
 #define FILINFORT                           4
 #define FILINFCLOSED_FROM                   5
 #define FILINFCLOSED_UNTIL                  6
 #define FILINFLAGERORTLEN                   7
 #define FILINFPROCENTERNAME                 8
 #define FILINFVORWAHL                       9
 #define FILINFPROCENTERLOCATION             10
 #define FILINFTELNR						 11
 #define FILINFFAXNR					     12
 #define FILINFPOSTLEITZAHL				     13
 #define FILINFSTRASSE						 14
 #define FILINFBALANCE1						 15
 #define FILINFBALANCE2						 16
 #define FILINFBGANR_EK						 17
 #define FILINFREGIONNO						 18

 #define FILINF_ZEIGER(xxx) \
 			:xxx->FILIALNR,\
 			:xxx->NAME,\
 			:xxx->STANDORT_KURZ,\
 			:xxx->STANDORT_LANG,\
 			:xxx->ORT,\
 			:xxx->CLOSED_FROM,\
 			:xxx->CLOSED_UNTIL,\
 			:xxx->LAGERORTLEN,\
 			:xxx->PROCENTERNAME,\
 			:xxx->VORWAHL,\
 			:xxx->PROCENTERLOCATION,\
 			:xxx->TELNR,\
 			:xxx->FAXNR,\
 			:xxx->POSTLEITZAHL,\
 			:xxx->STRASSE,\
 			:xxx->BALANCE1,\
 			:xxx->BALANCE2,\
 			:xxx->BGANR_EK,\
 			:xxx->REGIONNO

 #define FILINF_UPDATE(xxx) \
 			FILIALNR = :xxx->FILIALNR,\
 			NAME = :xxx->NAME,\
 			STANDORT_KURZ = :xxx->STANDORT_KURZ,\
 			STANDORT_LANG = :xxx->STANDORT_LANG,\
 			ORT = :xxx->ORT,\
 			CLOSED_FROM = :xxx->CLOSED_FROM,\
 			CLOSED_UNTIL = :xxx->CLOSED_UNTIL,\
 			LAGERORTLEN = :xxx->LAGERORTLEN,\
 			PROCENTERNAME = :xxx->PROCENTERNAME,\
 			VORWAHL = :xxx->VORWAHL,\
 			PROCENTERLOCATION = :xxx->PROCENTERLOCATION,\
 			TELNR = :xxx->TELNR,\
 			FAXNR = :xxx->FAXNR,\
 			POSTLEITZAHL = :xxx->POSTLEITZAHL,\
 			STRASSE = :xxx->STRASSE,\
 			BALANCE1 = :xxx->BALANCE1,\
 			BALANCE2 = :xxx->BALANCE2,\
 			BGANR_EK = :xxx->BGANR_EK,\
 			REGIONNO = :xxx->REGIONNO

 #define LS_FILINF_FILIALNR             7
 #define LS_FILINF_NAME                 31
 #define LS_FILINF_STANDORT_KURZ        3
 #define LS_FILINF_STANDORT_LANG        16
 #define LS_FILINF_ORT                  31
 #define LS_FILINF_CLOSED_FROM          11
 #define LS_FILINF_CLOSED_UNTIL         11
 #define LS_FILINF_LAGERORTLEN          7
 #define LS_FILINF_PROCENTERNAME        17
 #define LS_FILINF_VORWAHL              11
 #define LS_FILINF_PROCENTERLOCATION    17
 #define LS_FILINF_TELNR				21
 #define LS_FILINF_FAXNR				26
 #define LS_FILINF_POSTLEITZAHL		    11
 #define LS_FILINF_STRASSE			    31
 #define LS_FILINF_BALANCE1		        17
 #define LS_FILINF_BALANCE2		        17
 #define LS_FILINF_BGANR_EK		        11
 #define LS_FILINF_REGIONNO             7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct FILINF {
		 short   FILIALNR;
		 char    NAME[30 + 1];
		 char    STANDORT_KURZ[2 + 1];
		 char    STANDORT_LANG[15 + 1];
		 char    ORT[30 + 1];
		 long    CLOSED_FROM;
		 long    CLOSED_UNTIL;
		 short   LAGERORTLEN;
		 char    PROCENTERNAME[16 + 1];
		 char    VORWAHL[10 + 1];
		 char    PROCENTERLOCATION[16 + 1];
		 char    TELNR[20 + 1];
		 char    FAXNR[25 + 1];
		 char    POSTLEITZAHL[10 + 1];
		 char    STRASSE[30 + 1];
		 char    BALANCE1[16 + 1];
		 char    BALANCE2[16 + 1];
		 long    BGANR_EK;
		 short   REGIONNO;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_FILINF {
		 short   FILIALNR;
		 char    NAME[30 + 1];
		 char    STANDORT_KURZ[2 + 1];
		 char    STANDORT_LANG[15 + 1];
		 char    ORT[30 + 1];
		 long    CLOSED_FROM;
		 long    CLOSED_UNTIL;
		 short   LAGERORTLEN;
		 char    PROCENTERNAME[16 + 1];
		 char    VORWAHL[10 + 1];
		 char    PROCENTERLOCATION[16 + 1];
		 char    TELNR[20 + 1];
		 char    FAXNR[25 + 1];
		 char    POSTLEITZAHL[10 + 1];
		 char    STRASSE[30 + 1];
		 char    BALANCE1[16 + 1];
		 char    BALANCE2[16 + 1];
		 long    BGANR_EK;
		 short   REGIONNO;
      };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_FILINF {
		 short  FILIALNR;
		 short  NAME;
		 short  STANDORT_KURZ;
		 short  STANDORT_LANG;
		 short  ORT;
		 short  CLOSED_FROM;
		 short  CLOSED_UNTIL;
		 short  LAGERORTLEN;
		 short  PROCENTERNAME;
		 short  VORWAHL;
		 short  PROCENTERLOCATION;
		 short  TELNR;
		 short  FAXNR;
		 short  POSTLEITZAHL;
		 short  STRASSE;
		 short  BALANCE1;
		 short  BALANCE2;
		 short  BGANR_EK;
		 short  REGIONNO;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_FILINF {
		 char    FILIALNR[7];
		 char    NAME[30 + 1];
		 char    STANDORT_KURZ[2 + 1];
		 char    STANDORT_LANG[15 + 1];
		 char    ORT[30 + 1];
		 char    CLOSED_FROM[11];
		 char    CLOSED_UNTIL[11];
		 char    LAGERORTLEN[7];
		 char    PROCENTERNAME[16 + 1];
		 char    VORWAHL[10 + 1];
		 char    PROCENTERLOCATION[16 + 1];
		 char    TELNR[20 + 1];
		 char    FAXNR[25 + 1];
		 char    POSTLEITZAHL[10 + 1];
		 char    STRASSE[30 + 1];
		 char    BALANCE1[16 + 1];
		 char    BALANCE2[16 + 1];
		 char    BGANR_EK[11];
		 char    REGIONNO[7];
       };

 struct O_FILINF {
		 char    FILIALNR[7];
		 char    NAME[30];
		 char    STANDORT_KURZ[2];
		 char    STANDORT_LANG[15];
		 char    ORT[30];
		 char    CLOSED_FROM[11];
		 char    CLOSED_UNTIL[11];
		 char    LAGERORTLEN[7];
		 char    PROCENTERNAME[16];
		 char    VORWAHL[10];
		 char    PROCENTERLOCATION[16];
		 char    TELNR[20];
		 char    FAXNR[25];
		 char    POSTLEITZAHL[10];
		 char    STRASSE[30];
		 char    BALANCE1[16];
		 char    BALANCE2[16];
		 char    BGANR_EK[11];
		 char    REGIONNO[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc FILINF_BES [] =
 {
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc FILINF_BES [] =
 {
	 { TYP_S,    5 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C,   15 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_C,   10 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,   25 ,   0 },
	 { TYP_C,   10 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CFILINF
 {
  public:

  FILINF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, FILINF_BES, FILINF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,FILINF_BES, FILINF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,FILINF_BES, FILINF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CFILINF()
  {
   ::buf_default((void *)&s, FILINF_BES, FILINF_ANZ);
  }
 };
#endif

#define FILINF_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 FILIALNR SMALLINT          ,\
		 NAME CHAR(30)          ,\
		 STANDORT_KURZ CHAR(2)           ,\
		 STANDORT_LANG CHAR(15)          ,\
		 ORT CHAR(30)          ,\
		 CLOSED_FROM INTEGER           ,\
		 CLOSED_UNTIL INTEGER           ,\
		 LAGERORTLEN SMALLINT           ,\
		 PROCENTERNAME CHAR(16)           ,\
		 VORWAHL CHAR(10)           ,\
		 PROCENTERNAME CHAR(16)           ,\
		 TELNR CHAR(20)           ,\
		 FAXNR CHAR(25)           ,\
		 POSTLEITZAHL CHAR(10)           ,\
		 STRASSE CHAR(30)			,\
		 BALANCE1 CHAR(10)           ,\
		 BALANCE2 CHAR(10)           ,\
		 BGANR_EK INTEGER           ,\
		 REGIONNO SMALLINT            ) EXTENT SIZE 9 LOCK MODE ROW;

#define FILINF_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_FILIALE_1        on yyy( FILIALNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define FILINF_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_FILIALE_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

