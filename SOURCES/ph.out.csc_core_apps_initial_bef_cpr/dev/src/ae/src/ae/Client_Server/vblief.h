/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_VBLIEF_IDFNR                11
 #define L_VBLIEF_DATUM                11
 #define L_VBLIEF_ARTIKEL_NR           11
 #define L_VBLIEF_EINHEIT              9
 #define L_VBLIEF_MENGE                11
 #define L_VBLIEF_ARTIKEL_NAME         30
 #define L_VBLIEF_NAMEAPO              40
 #define L_VBLIEF_TELNR                20
 #define L_VBLIEF_TELKURZWAHL          4


 #define L_VBLIEF_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define VBLIEF_ANZ ( sizeof(VBLIEF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_VBLIEF sizeof(struct VBLIEF)


 #define VBLIEF_H

 #define VBLIEF_LISTE \
 			KUNDE.IDFNR, \
 			NACHLIEFERPOS.DATUM, \
 			NACHLIEFERPOS.ARTIKEL_NR, \
 			ARTIKEL.EINHEIT, \
 			NACHLIEFERPOS.MENGE, \
 			ARTIKEL.ARTIKEL_NAME, \
 			KUNDE.NAMEAPO, \
 			KUNDE.TELNR, \
 			KUNDE.TELKURZWAHL
 #define VBLIEF_PLISTE \
 			"KUNDE.IDFNR," \
 			"NACHLIEFERPOS.DATUM," \
 			"NACHLIEFERPOS.ARTIKEL_NR," \
 			"ARTIKEL.EINHEIT," \
 			"NACHLIEFERPOS.MENGE," \
 			"ARTIKEL.ARTIKEL_NAME," \
 			"KUNDE.NAMEAPO," \
 			"KUNDE.TELNR," \
 			"KUNDE.TELKURZWAHL " 

 #define VBLIEF_PELISTE \
 			"IDFNR," \
 			"DATUM," \
 			"ARTIKEL_NR," \
 			"EINHEIT," \
 			"MENGE," \
 			"ARTIKEL_NAME," \
 			"NAMEAPO," \
 			"TELNR," \
 			"TELKURZWAHL " 

 #define VBLIEF_UPDLISTE \
 			"IDFNR=?," \
 			"DATUM=?," \
 			"ARTIKEL_NR=?," \
 			"EINHEIT=?," \
 			"MENGE=?," \
 			"ARTIKEL_NAME=?," \
 			"NAMEAPO=?," \
 			"TELNR=?," \
 			"TELKURZWAHL=? " 

 #define VBLIEFIDFNR                         0
 #define VBLIEFDATUM                         1
 #define VBLIEFARTIKEL_NR                    2
 #define VBLIEFEINHEIT                       3
 #define VBLIEFMENGE                         4
 #define VBLIEFARTIKEL_NAME                  5
 #define VBLIEFNAMEAPO                       6
 #define VBLIEFTELNR                         7
 #define VBLIEFTELKURZWAHL                   8

 #define VBLIEF_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->DATUM,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->EINHEIT,\
 			:xxx->MENGE,\
 			:xxx->ARTIKEL_NAME,\
 			:xxx->NAMEAPO,\
 			:xxx->TELNR,\
 			:xxx->TELKURZWAHL

 #define VBLIEF_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			DATUM = :xxx->DATUM,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			EINHEIT = :xxx->EINHEIT,\
 			MENGE = :xxx->MENGE,\
 			ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
 			NAMEAPO = :xxx->NAMEAPO,\
 			TELNR = :xxx->TELNR,\
 			TELKURZWAHL = :xxx->TELKURZWAHL

 #define LS_VBLIEF_IDFNR                11
 #define LS_VBLIEF_DATUM                11
 #define LS_VBLIEF_ARTIKEL_NR           11
 #define LS_VBLIEF_EINHEIT              10
 #define LS_VBLIEF_MENGE                11
 #define LS_VBLIEF_ARTIKEL_NAME         31
 #define LS_VBLIEF_NAMEAPO              41
 #define LS_VBLIEF_TELNR                21
 #define LS_VBLIEF_TELKURZWAHL          5
 #define LS_VBLIEF_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct VBLIEF {
		 long    IDFNR;
		 long    DATUM;
		 long    ARTIKEL_NR;
		 char    EINHEIT[9 + 1];
		 long    MENGE;
		 char    ARTIKEL_NAME[30 + 1];
		 char    NAMEAPO[40 + 1];
		 char    TELNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_VBLIEF {
		 long    IDFNR;
		 long    DATUM;
		 long    ARTIKEL_NR;
		 char    EINHEIT[9 + 1];
		 long    MENGE;
		 char    ARTIKEL_NAME[30 + 1];
		 char    NAMEAPO[40 + 1];
		 char    TELNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_VBLIEF {
		 short  IDFNR;
		 short  DATUM;
		 short  ARTIKEL_NR;
		 short  EINHEIT;
		 short  MENGE;
		 short  ARTIKEL_NAME;
		 short  NAMEAPO;
		 short  TELNR;
		 short  TELKURZWAHL;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_VBLIEF {
		 char    IDFNR[11];
		 char    DATUM[11];
		 char    ARTIKEL_NR[11];
		 char    EINHEIT[9 + 1];
		 char    MENGE[11];
		 char    ARTIKEL_NAME[30 + 1];
		 char    NAMEAPO[40 + 1];
		 char    TELNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 char    FETCH_REL[11];
       };

 struct O_VBLIEF {
		 char    IDFNR[11];
		 char    DATUM[11];
		 char    ARTIKEL_NR[11];
		 char    EINHEIT[9];
		 char    MENGE[11];
		 char    ARTIKEL_NAME[30];
		 char    NAMEAPO[40];
		 char    TELNR[20];
		 char    TELKURZWAHL[4];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc VBLIEF_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc VBLIEF_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    9 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CVBLIEF
 {
  public:

  VBLIEF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, VBLIEF_BES, VBLIEF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,VBLIEF_BES, VBLIEF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,VBLIEF_BES, VBLIEF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CVBLIEF()
  {
   ::buf_default((void *)&s, VBLIEF_BES, VBLIEF_ANZ);
  }
 };
#endif

#define VBLIEF_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR INTEGER           ,\
		 DATUM INTEGER           ,\
		 ARTIKEL_NR INTEGER           ,\
		 EINHEIT CHAR(9)           ,\
		 MENGE INTEGER           ,\
		 ARTIKEL_NAME CHAR(30)          ,\
		 NAMEAPO CHAR(40)          ,\
		 TELNR CHAR(20)          ,\
		 TELKURZWAHL CHAR(4)           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 699 LOCK MODE ROW;

#define VBLIEF_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KUNDEX             on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define VBLIEF_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KUNDEX            ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

