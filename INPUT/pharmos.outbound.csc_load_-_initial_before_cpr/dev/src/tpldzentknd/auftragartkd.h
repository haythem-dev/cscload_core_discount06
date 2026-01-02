/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_AUFTRAGARTKD_IDFNR                11
 #define L_AUFTRAGARTKD_KDAUFTRAGART         2
 #define L_AUFTRAGARTKD_VALUTAMONATE         6
 #define L_AUFTRAGARTKD_SKDAUFTRAGARTNATRA   1
 #define L_AUFTRAGARTKD_SKDAUFTRAGARTNETTO   1
 #define L_AUFTRAGARTKD_SKDAUFTRAGARTBANR    1
 #define L_AUFTRAGARTKD_SKDAUFTRAGARTMONAT   1
 #define L_AUFTRAGARTKD_SKDAUFTRAGVERBUND    1
 #define L_AUFTRAGARTKD_SKDAUFTRAGARTVALS    1
 #define L_AUFTRAGARTKD_VALUTAMONAUTO        6
 #define L_AUFTRAGARTKD_KZUPD                1
 #define L_AUFTRAGARTKD_RABATTART            6
 #define L_AUFTRAGARTKD_KUNDESTAFFELNR       11
 #define L_AUFTRAGARTKD_VERTRIEBSZENTRUMNR   6
 #define L_AUFTRAGARTKD_KUNDENNR             11
 #define L_AUFTRAGARTKD_TM_DATE              11
 #define L_AUFTRAGARTKD_TM_TIME              11
 #define L_AUFTRAGARTKD_LOGINID              11
 #define L_AUFTRAGARTKD_CHANGEID             1
 #define L_AUFTRAGARTKD_SKDAUFTRAGARTDD      1


 #define L_AUFTRAGARTKD_PKEY 13

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define AUFTRAGARTKD_ANZ ( sizeof(AUFTRAGARTKD_BES) / sizeof(struct buf_desc) )
#endif
 #define G_AUFTRAGARTKD sizeof(struct AUFTRAGARTKD)


 #define AUFTRAGARTKD_H

 #define AUFTRAGARTKD_LISTE \
 			AUFTRAGARTKD.IDFNR, \
 			AUFTRAGARTKD.KDAUFTRAGART, \
 			AUFTRAGARTKD.VALUTAMONATE, \
 			AUFTRAGARTKD.SKDAUFTRAGARTNATRA, \
 			AUFTRAGARTKD.SKDAUFTRAGARTNETTO, \
 			AUFTRAGARTKD.SKDAUFTRAGARTBANR, \
 			AUFTRAGARTKD.SKDAUFTRAGARTMONAT, \
 			AUFTRAGARTKD.SKDAUFTRAGVERBUND, \
 			AUFTRAGARTKD.SKDAUFTRAGARTVALS, \
 			AUFTRAGARTKD.VALUTAMONAUTO, \
 			AUFTRAGARTKD.KZUPD, \
 			AUFTRAGARTKD.RABATTART, \
 			AUFTRAGARTKD.KUNDESTAFFELNR, \
 			AUFTRAGARTKD.VERTRIEBSZENTRUMNR, \
 			AUFTRAGARTKD.KUNDENNR, \
 			AUFTRAGARTKD.TM_DATE, \
 			AUFTRAGARTKD.TM_TIME, \
 			AUFTRAGARTKD.LOGINID, \
 			AUFTRAGARTKD.CHANGEID, \
 			AUFTRAGARTKD.SKDAUFTRAGARTDD
 #define AUFTRAGARTKD_PLISTE \
 			"AUFTRAGARTKD.IDFNR," \
 			"AUFTRAGARTKD.KDAUFTRAGART," \
 			"AUFTRAGARTKD.VALUTAMONATE," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTNATRA," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTNETTO," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTBANR," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTMONAT," \
 			"AUFTRAGARTKD.SKDAUFTRAGVERBUND," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTVALS," \
 			"AUFTRAGARTKD.VALUTAMONAUTO," \
 			"AUFTRAGARTKD.KZUPD," \
 			"AUFTRAGARTKD.RABATTART," \
 			"AUFTRAGARTKD.KUNDESTAFFELNR," \
 			"AUFTRAGARTKD.VERTRIEBSZENTRUMNR," \
 			"AUFTRAGARTKD.KUNDENNR," \
 			"AUFTRAGARTKD.TM_DATE," \
 			"AUFTRAGARTKD.TM_TIME," \
 			"AUFTRAGARTKD.LOGINID," \
 			"AUFTRAGARTKD.CHANGEID," \
 			"AUFTRAGARTKD.SKDAUFTRAGARTDD "

 #define AUFTRAGARTKD_PELISTE \
 			"IDFNR," \
 			"KDAUFTRAGART," \
 			"VALUTAMONATE," \
 			"SKDAUFTRAGARTNATRA," \
 			"SKDAUFTRAGARTNETTO," \
 			"SKDAUFTRAGARTBANR," \
 			"SKDAUFTRAGARTMONAT," \
 			"SKDAUFTRAGVERBUND," \
 			"SKDAUFTRAGARTVALS," \
 			"VALUTAMONAUTO," \
 			"KZUPD," \
 			"RABATTART," \
 			"KUNDESTAFFELNR," \
 			"VERTRIEBSZENTRUMNR," \
 			"KUNDENNR," \
 			"TM_DATE," \
 			"TM_TIME," \
 			"LOGINID," \
 			"CHANGEID," \
 			"SKDAUFTRAGARTDD "

 #define AUFTRAGARTKD_UPDLISTE \
 			"IDFNR=?," \
 			"KDAUFTRAGART=?," \
 			"VALUTAMONATE=?," \
 			"SKDAUFTRAGARTNATRA=?," \
 			"SKDAUFTRAGARTNETTO=?," \
 			"SKDAUFTRAGARTBANR=?," \
 			"SKDAUFTRAGARTMONAT=?," \
 			"SKDAUFTRAGVERBUND=?," \
 			"SKDAUFTRAGARTVALS=?," \
 			"VALUTAMONAUTO=?," \
 			"KZUPD=?," \
 			"RABATTART=?," \
 			"KUNDESTAFFELNR=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"KUNDENNR=?," \
 			"TM_DATE=?," \
 			"TM_TIME=?," \
 			"LOGINID=?," \
 			"CHANGEID=?," \
 			"SKDAUFTRAGARTDD=? "

 #define AUFTRAGARTKDIDFNR                         0
 #define AUFTRAGARTKDKDAUFTRAGART                  1
 #define AUFTRAGARTKDVALUTAMONATE                  2
 #define AUFTRAGARTKDSKDAUFTRAGARTNATRA            3
 #define AUFTRAGARTKDSKDAUFTRAGARTNETTO            4
 #define AUFTRAGARTKDSKDAUFTRAGARTBANR             5
 #define AUFTRAGARTKDSKDAUFTRAGARTMONAT            6
 #define AUFTRAGARTKDSKDAUFTRAGVERBUND             7
 #define AUFTRAGARTKDSKDAUFTRAGARTVALS             8
 #define AUFTRAGARTKDVALUTAMONAUTO                 9
 #define AUFTRAGARTKDKZUPD                         10
 #define AUFTRAGARTKDRABATTART                     11
 #define AUFTRAGARTKDKUNDESTAFFELNR                12
 #define AUFTRAGARTKDVERTRIEBSZENTRUMNR            13
 #define AUFTRAGARTKDKUNDENNR                      14
 #define AUFTRAGARTKDTM_DATE                       15
 #define AUFTRAGARTKDTM_TIME                       16
 #define AUFTRAGARTKDLOGINID                       17
 #define AUFTRAGARTKDCHANGEID                      18
 #define AUFTRAGARTKDSKDAUFTRAGARTDD               19

 #define AUFTRAGARTKD_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->KDAUFTRAGART,\
 			:xxx->VALUTAMONATE,\
 			:xxx->SKDAUFTRAGARTNATRA,\
 			:xxx->SKDAUFTRAGARTNETTO,\
 			:xxx->SKDAUFTRAGARTBANR,\
 			:xxx->SKDAUFTRAGARTMONAT,\
 			:xxx->SKDAUFTRAGVERBUND,\
 			:xxx->SKDAUFTRAGARTVALS,\
 			:xxx->VALUTAMONAUTO,\
 			:xxx->KZUPD,\
 			:xxx->RABATTART,\
 			:xxx->KUNDESTAFFELNR,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->KUNDENNR,\
 			:xxx->TM_DATE,\
 			:xxx->TM_TIME,\
 			:xxx->LOGINID,\
 			:xxx->CHANGEID,\
 			:xxx->CHANGEID

 #define AUFTRAGARTKD_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			KDAUFTRAGART = :xxx->KDAUFTRAGART,\
 			VALUTAMONATE = :xxx->VALUTAMONATE,\
 			SKDAUFTRAGARTNATRA = :xxx->SKDAUFTRAGARTNATRA,\
 			SKDAUFTRAGARTNETTO = :xxx->SKDAUFTRAGARTNETTO,\
 			SKDAUFTRAGARTBANR = :xxx->SKDAUFTRAGARTBANR,\
 			SKDAUFTRAGARTMONAT = :xxx->SKDAUFTRAGARTMONAT,\
 			SKDAUFTRAGVERBUND = :xxx->SKDAUFTRAGVERBUND,\
 			SKDAUFTRAGARTVALS = :xxx->SKDAUFTRAGARTVALS,\
 			VALUTAMONAUTO = :xxx->VALUTAMONAUTO,\
 			KZUPD = :xxx->KZUPD,\
 			RABATTART = :xxx->RABATTART,\
 			KUNDESTAFFELNR = :xxx->KUNDESTAFFELNR,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			TM_DATE = :xxx->TM_DATE,\
 			TM_TIME = :xxx->TM_TIME,\
 			LOGINID = :xxx->LOGINID,\
 			CHANGEID = :xxx->CHANGEID,\
 			SKDAUFTRAGARTDD = :xxx->SKDAUFTRAGARTDD

 #define LS_AUFTRAGARTKD_IDFNR                11
 #define LS_AUFTRAGARTKD_KDAUFTRAGART         3
 #define LS_AUFTRAGARTKD_VALUTAMONATE         7
 #define LS_AUFTRAGARTKD_SKDAUFTRAGARTNATRA   2
 #define LS_AUFTRAGARTKD_SKDAUFTRAGARTNETTO   2
 #define LS_AUFTRAGARTKD_SKDAUFTRAGARTBANR    2
 #define LS_AUFTRAGARTKD_SKDAUFTRAGARTMONAT   2
 #define LS_AUFTRAGARTKD_SKDAUFTRAGVERBUND    2
 #define LS_AUFTRAGARTKD_SKDAUFTRAGARTVALS    2
 #define LS_AUFTRAGARTKD_VALUTAMONAUTO        7
 #define LS_AUFTRAGARTKD_KZUPD                2
 #define LS_AUFTRAGARTKD_RABATTART            7
 #define LS_AUFTRAGARTKD_KUNDESTAFFELNR       11
 #define LS_AUFTRAGARTKD_VERTRIEBSZENTRUMNR   7
 #define LS_AUFTRAGARTKD_KUNDENNR             11
 #define LS_AUFTRAGARTKD_TM_DATE              11
 #define LS_AUFTRAGARTKD_TM_TIME              11
 #define LS_AUFTRAGARTKD_LOGINID              11
 #define LS_AUFTRAGARTKD_CHANGEID             2
 #define LS_AUFTRAGARTKD_SKDAUFTRAGARTDD      2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct AUFTRAGARTKD {
		 long    IDFNR;
		 char    KDAUFTRAGART[2 + 1];
		 short   VALUTAMONATE;
		 char    SKDAUFTRAGARTNATRA[1 + 1];
		 char    SKDAUFTRAGARTNETTO[1 + 1];
		 char    SKDAUFTRAGARTBANR[1 + 1];
		 char    SKDAUFTRAGARTMONAT[1 + 1];
		 char    SKDAUFTRAGVERBUND[1 + 1];
		 char    SKDAUFTRAGARTVALS[1 + 1];
		 short   VALUTAMONAUTO;
		 char    KZUPD[1 + 1];
		 short   RABATTART;
		 long    KUNDESTAFFELNR;
		 short   VERTRIEBSZENTRUMNR;
		 long    KUNDENNR;
		 long    TM_DATE;
		 long    TM_TIME;
		 long    LOGINID;
		 char    CHANGEID[1 + 1];
		 char    SKDAUFTRAGARTDD[1 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_AUFTRAGARTKD {
		 long    IDFNR;
		 char    KDAUFTRAGART[2 + 1];
		 short   VALUTAMONATE;
		 char    SKDAUFTRAGARTNATRA;
		 char    SKDAUFTRAGARTNETTO;
		 char    SKDAUFTRAGARTBANR;
		 char    SKDAUFTRAGARTMONAT;
		 char    SKDAUFTRAGVERBUND;
		 char    SKDAUFTRAGARTVALS;
		 short   VALUTAMONAUTO;
		 char    KZUPD;
		 short   RABATTART;
		 long    KUNDESTAFFELNR;
		 short   VERTRIEBSZENTRUMNR;
		 long    KUNDENNR;
		 long    TM_DATE;
		 long    TM_TIME;
		 long    LOGINID;
		 char    CHANGEID;
		 char    SKDAUFTRAGARTDD;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_AUFTRAGARTKD {
		 short  IDFNR;
		 short  KDAUFTRAGART;
		 short  VALUTAMONATE;
		 short  SKDAUFTRAGARTNATRA;
		 short  SKDAUFTRAGARTNETTO;
		 short  SKDAUFTRAGARTBANR;
		 short  SKDAUFTRAGARTMONAT;
		 short  SKDAUFTRAGVERBUND;
		 short  SKDAUFTRAGARTVALS;
		 short  VALUTAMONAUTO;
		 short  KZUPD;
		 short  RABATTART;
		 short  KUNDESTAFFELNR;
		 short  VERTRIEBSZENTRUMNR;
		 short  KUNDENNR;
		 short  TM_DATE;
		 short  TM_TIME;
		 short  LOGINID;
		 short  CHANGEID;
		 short  SKDAUFTRAGARTDD;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_AUFTRAGARTKD {
		 char    IDFNR[11];
		 char    KDAUFTRAGART[2 + 1];
		 char    VALUTAMONATE[7];
		 char    SKDAUFTRAGARTNATRA[1 + 1];
		 char    SKDAUFTRAGARTNETTO[1 + 1];
		 char    SKDAUFTRAGARTBANR[1 + 1];
		 char    SKDAUFTRAGARTMONAT[1 + 1];
		 char    SKDAUFTRAGVERBUND[1 + 1];
		 char    SKDAUFTRAGARTVALS[1 + 1];
		 char    VALUTAMONAUTO[7];
		 char    KZUPD[1 + 1];
		 char    RABATTART[7];
		 char    KUNDESTAFFELNR[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1 + 1];
		 char    SKDAUFTRAGARTDD[1 + 1];
       };

 struct O_AUFTRAGARTKD {
		 char    IDFNR[11];
		 char    KDAUFTRAGART[2];
		 char    VALUTAMONATE[7];
		 char    SKDAUFTRAGARTNATRA[1];
		 char    SKDAUFTRAGARTNETTO[1];
		 char    SKDAUFTRAGARTBANR[1];
		 char    SKDAUFTRAGARTMONAT[1];
		 char    SKDAUFTRAGVERBUND[1];
		 char    SKDAUFTRAGARTVALS[1];
		 char    VALUTAMONAUTO[7];
		 char    KZUPD[1];
		 char    RABATTART[7];
		 char    KUNDESTAFFELNR[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1];
		 char    SKDAUFTRAGARTDD[1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc AUFTRAGARTKD_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AUFTRAGARTKD_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CAUFTRAGARTKD
 {
  public:

  AUFTRAGARTKD s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CAUFTRAGARTKD()
  {
   ::buf_default((void *)&s, AUFTRAGARTKD_BES, AUFTRAGARTKD_ANZ);
  }
 };
#endif

#define AUFTRAGARTKD_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR              INTEGER         default 0 NOT NULL,\
		 KDAUFTRAGART       CHAR(2)         default " " NOT NULL,\
		 VALUTAMONATE       SMALLINT        default 0 NOT NULL,\
		 SKDAUFTRAGARTNATRA CHAR(1)         default " " NOT NULL,\
		 SKDAUFTRAGARTNETTO CHAR(1)         default " " NOT NULL,\
		 SKDAUFTRAGARTBANR  CHAR(1)         default " " NOT NULL,\
		 SKDAUFTRAGARTMONAT CHAR(1)         default " " NOT NULL,\
		 SKDAUFTRAGVERBUND  CHAR(1)         default " " NOT NULL,\
		 SKDAUFTRAGARTVALS  CHAR(1)         default " " NOT NULL,\
		 VALUTAMONAUTO      SMALLINT        default 0 NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 RABATTART          SMALLINT        default 0 NOT NULL,\
		 KUNDESTAFFELNR     INTEGER         default 0 NOT NULL,\
		 VERTRIEBSZENTRUMNR SMALLINT        default 0 NOT NULL,\
		 KUNDENNR           INTEGER         default 0 NOT NULL,\
		 TM_DATE            INTEGER         default 0 NOT NULL,\
		 TM_TIME            INTEGER         default 0 NOT NULL,\
		 LOGINID            INTEGER         default 0 NOT NULL,\
		 CHANGEID           CHAR(1)         default " " NOT NULL,\
		 SKDAUFTRAGARTDD    CHAR(1)         default " " NOT NULL  ) EXTENT SIZE 9 LOCK MODE ROW;

#define AUFTRAGARTKD_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX AUFTRAGARTKDX      on yyy( IDFNR, KDAUFTRAGART );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define AUFTRAGARTKD_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX AUFTRAGARTKDX     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

