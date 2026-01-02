/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KDBETRIEBSENDE_IDFNR                11
 #define L_KDBETRIEBSENDE_TAGESTYP             6
 #define L_KDBETRIEBSENDE_ZEITBEGINAM          11
 #define L_KDBETRIEBSENDE_ZEITENDEAM           11
 #define L_KDBETRIEBSENDE_ZEITBEGINPM          11
 #define L_KDBETRIEBSENDE_ZEITENDEPM           11
 #define L_KDBETRIEBSENDE_KZUPD                1
 #define L_KDBETRIEBSENDE_VERTRIEBSZENTRUMNR   6
 #define L_KDBETRIEBSENDE_KUNDENNR             11
 #define L_KDBETRIEBSENDE_TM_DATE              11
 #define L_KDBETRIEBSENDE_TM_TIME              11
 #define L_KDBETRIEBSENDE_LOGINID              11
 #define L_KDBETRIEBSENDE_CHANGEID             1
 #define L_KDBETRIEBSENDE_WEEKDAY              6


 #define L_KDBETRIEBSENDE_PKEY 17

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KDBETRIEBSENDE_ANZ ( sizeof(KDBETRIEBSENDE_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KDBETRIEBSENDE sizeof(struct KDBETRIEBSENDE)


 #define KDBETRIEBSENDE_H

 #define KDBETRIEBSENDE_LISTE \
 			KDBETRIEBSENDE.IDFNR, \
 			KDBETRIEBSENDE.TAGESTYP, \
 			KDBETRIEBSENDE.ZEITBEGINAM, \
 			KDBETRIEBSENDE.ZEITENDEAM, \
 			KDBETRIEBSENDE.ZEITBEGINPM, \
 			KDBETRIEBSENDE.ZEITENDEPM, \
 			KDBETRIEBSENDE.KZUPD, \
 			KDBETRIEBSENDE.VERTRIEBSZENTRUMNR, \
 			KDBETRIEBSENDE.KUNDENNR, \
 			KDBETRIEBSENDE.TM_DATE, \
 			KDBETRIEBSENDE.TM_TIME, \
 			KDBETRIEBSENDE.LOGINID, \
 			KDBETRIEBSENDE.CHANGEID, \
 			KDBETRIEBSENDE.WEEKDAY
 #define KDBETRIEBSENDE_PLISTE \
 			"KDBETRIEBSENDE.IDFNR," \
 			"KDBETRIEBSENDE.TAGESTYP," \
 			"KDBETRIEBSENDE.ZEITBEGINAM," \
 			"KDBETRIEBSENDE.ZEITENDEAM," \
 			"KDBETRIEBSENDE.ZEITBEGINPM," \
 			"KDBETRIEBSENDE.ZEITENDEPM," \
 			"KDBETRIEBSENDE.KZUPD," \
 			"KDBETRIEBSENDE.VERTRIEBSZENTRUMNR," \
 			"KDBETRIEBSENDE.KUNDENNR," \
 			"KDBETRIEBSENDE.TM_DATE," \
 			"KDBETRIEBSENDE.TM_TIME," \
 			"KDBETRIEBSENDE.LOGINID," \
 			"KDBETRIEBSENDE.CHANGEID," \
 			"KDBETRIEBSENDE.WEEKDAY " 

 #define KDBETRIEBSENDE_PELISTE \
 			"IDFNR," \
 			"TAGESTYP," \
 			"ZEITBEGINAM," \
 			"ZEITENDEAM," \
 			"ZEITBEGINPM," \
 			"ZEITENDEPM," \
 			"KZUPD," \
 			"VERTRIEBSZENTRUMNR," \
 			"KUNDENNR," \
 			"TM_DATE," \
 			"TM_TIME," \
 			"LOGINID," \
 			"CHANGEID," \
 			"WEEKDAY " 

 #define KDBETRIEBSENDE_UPDLISTE \
 			"IDFNR=?," \
 			"TAGESTYP=?," \
 			"ZEITBEGINAM=?," \
 			"ZEITENDEAM=?," \
 			"ZEITBEGINPM=?," \
 			"ZEITENDEPM=?," \
 			"KZUPD=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"KUNDENNR=?," \
 			"TM_DATE=?," \
 			"TM_TIME=?," \
 			"LOGINID=?," \
 			"CHANGEID=?," \
 			"WEEKDAY=? " 

 #define KDBETRIEBSENDEIDFNR                         0
 #define KDBETRIEBSENDETAGESTYP                      1
 #define KDBETRIEBSENDEZEITBEGINAM                   2
 #define KDBETRIEBSENDEZEITENDEAM                    3
 #define KDBETRIEBSENDEZEITBEGINPM                   4
 #define KDBETRIEBSENDEZEITENDEPM                    5
 #define KDBETRIEBSENDEKZUPD                         6
 #define KDBETRIEBSENDEVERTRIEBSZENTRUMNR            7
 #define KDBETRIEBSENDEKUNDENNR                      8
 #define KDBETRIEBSENDETM_DATE                       9
 #define KDBETRIEBSENDETM_TIME                       10
 #define KDBETRIEBSENDELOGINID                       11
 #define KDBETRIEBSENDECHANGEID                      12
 #define KDBETRIEBSENDEWEEKDAY                       13

 #define KDBETRIEBSENDE_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->TAGESTYP,\
 			:xxx->ZEITBEGINAM,\
 			:xxx->ZEITENDEAM,\
 			:xxx->ZEITBEGINPM,\
 			:xxx->ZEITENDEPM,\
 			:xxx->KZUPD,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->KUNDENNR,\
 			:xxx->TM_DATE,\
 			:xxx->TM_TIME,\
 			:xxx->LOGINID,\
 			:xxx->CHANGEID,\
 			:xxx->WEEKDAY

 #define KDBETRIEBSENDE_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			TAGESTYP = :xxx->TAGESTYP,\
 			ZEITBEGINAM = :xxx->ZEITBEGINAM,\
 			ZEITENDEAM = :xxx->ZEITENDEAM,\
 			ZEITBEGINPM = :xxx->ZEITBEGINPM,\
 			ZEITENDEPM = :xxx->ZEITENDEPM,\
 			KZUPD = :xxx->KZUPD,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			TM_DATE = :xxx->TM_DATE,\
 			TM_TIME = :xxx->TM_TIME,\
 			LOGINID = :xxx->LOGINID,\
 			CHANGEID = :xxx->CHANGEID,\
 			WEEKDAY = :xxx->WEEKDAY

 #define LS_KDBETRIEBSENDE_IDFNR                11
 #define LS_KDBETRIEBSENDE_TAGESTYP             7
 #define LS_KDBETRIEBSENDE_ZEITBEGINAM          11
 #define LS_KDBETRIEBSENDE_ZEITENDEAM           11
 #define LS_KDBETRIEBSENDE_ZEITBEGINPM          11
 #define LS_KDBETRIEBSENDE_ZEITENDEPM           11
 #define LS_KDBETRIEBSENDE_KZUPD                2
 #define LS_KDBETRIEBSENDE_VERTRIEBSZENTRUMNR   7
 #define LS_KDBETRIEBSENDE_KUNDENNR             11
 #define LS_KDBETRIEBSENDE_TM_DATE              11
 #define LS_KDBETRIEBSENDE_TM_TIME              11
 #define LS_KDBETRIEBSENDE_LOGINID              11
 #define LS_KDBETRIEBSENDE_CHANGEID             2
 #define LS_KDBETRIEBSENDE_WEEKDAY              7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KDBETRIEBSENDE {
		 long    IDFNR;
		 char    TAGESTYP[6 + 1];
		 long    ZEITBEGINAM;
		 long    ZEITENDEAM;
		 long    ZEITBEGINPM;
		 long    ZEITENDEPM;
		 char    KZUPD[1 + 1];
		 short   VERTRIEBSZENTRUMNR;
		 long    KUNDENNR;
		 long    TM_DATE;
		 long    TM_TIME;
		 long    LOGINID;
		 char    CHANGEID[1 + 1];
		 short   WEEKDAY;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KDBETRIEBSENDE {
		 long    IDFNR;
		 char    TAGESTYP[6 + 1];
		 long    ZEITBEGINAM;
		 long    ZEITENDEAM;
		 long    ZEITBEGINPM;
		 long    ZEITENDEPM;
		 char    KZUPD;
		 short   VERTRIEBSZENTRUMNR;
		 long    KUNDENNR;
		 long    TM_DATE;
		 long    TM_TIME;
		 long    LOGINID;
		 char    CHANGEID;
		 short   WEEKDAY;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KDBETRIEBSENDE {
		 short  IDFNR;
		 short  TAGESTYP;
		 short  ZEITBEGINAM;
		 short  ZEITENDEAM;
		 short  ZEITBEGINPM;
		 short  ZEITENDEPM;
		 short  KZUPD;
		 short  VERTRIEBSZENTRUMNR;
		 short  KUNDENNR;
		 short  TM_DATE;
		 short  TM_TIME;
		 short  LOGINID;
		 short  CHANGEID;
		 short  WEEKDAY;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KDBETRIEBSENDE {
		 char    IDFNR[11];
		 char    TAGESTYP[6 + 1];
		 char    ZEITBEGINAM[11];
		 char    ZEITENDEAM[11];
		 char    ZEITBEGINPM[11];
		 char    ZEITENDEPM[11];
		 char    KZUPD[1 + 1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1 + 1];
		 char    WEEKDAY[7];
       };

 struct O_KDBETRIEBSENDE {
		 char    IDFNR[11];
		 char    TAGESTYP[6];
		 char    ZEITBEGINAM[11];
		 char    ZEITENDEAM[11];
		 char    ZEITBEGINPM[11];
		 char    ZEITENDEPM[11];
		 char    KZUPD[1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1];
		 char    WEEKDAY[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KDBETRIEBSENDE_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDBETRIEBSENDE_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKDBETRIEBSENDE
 {
  public:

  KDBETRIEBSENDE s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KDBETRIEBSENDE_BES, KDBETRIEBSENDE_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KDBETRIEBSENDE_BES, KDBETRIEBSENDE_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KDBETRIEBSENDE_BES, KDBETRIEBSENDE_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKDBETRIEBSENDE()
  {
   ::buf_default((void *)&s, KDBETRIEBSENDE_BES, KDBETRIEBSENDE_ANZ);
  }
 };
#endif

#define KDBETRIEBSENDE_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR              INTEGER         default 0 NOT NULL,\
		 TAGESTYP           CHAR(6)         default " " NOT NULL,\
		 ZEITBEGINAM        INTEGER         default 0 NOT NULL,\
		 ZEITENDEAM         INTEGER         default 0 NOT NULL,\
		 ZEITBEGINPM        INTEGER         default 0 NOT NULL,\
		 ZEITENDEPM         INTEGER         default 0 NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 VERTRIEBSZENTRUMNR SMALLINT        default 0 NOT NULL,\
		 KUNDENNR           INTEGER         default 0 NOT NULL,\
		 TM_DATE            INTEGER         default 0 NOT NULL,\
		 TM_TIME            INTEGER         default 0 NOT NULL,\
		 LOGINID            INTEGER         default 0 NOT NULL,\
		 CHANGEID           CHAR(1)         default " " NOT NULL,\
		 WEEKDAY            SMALLINT        default " " NOT NULL  ) EXTENT SIZE 675 LOCK MODE ROW;

#define KDBETRIEBSENDE_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDBETRIEBSENDEX    on yyy( IDFNR, TAGESTYP );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KDBETRIEBSENDE_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDBETRIEBSENDEX   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

