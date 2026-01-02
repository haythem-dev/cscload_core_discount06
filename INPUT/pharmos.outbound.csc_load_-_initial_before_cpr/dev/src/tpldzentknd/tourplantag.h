/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_TOURPLANTAG_IDFNR                11
 #define L_TOURPLANTAG_DATUMKOMMI           11
 #define L_TOURPLANTAG_TOURID               6
 #define L_TOURPLANTAG_REIHENFOLGENR        11
 #define L_TOURPLANTAG_FAHRTZEIT            6
 #define L_TOURPLANTAG_BEMERKUNGEN          240
 #define L_TOURPLANTAG_KZUPD                1
 #define L_TOURPLANTAG_ISTVERBUNDTOUR       1
 #define L_TOURPLANTAG_VERTRIEBSZENTRUMNR   6
 #define L_TOURPLANTAG_KUNDENNR             11
 #define L_TOURPLANTAG_TM_DATE              11
 #define L_TOURPLANTAG_TM_TIME              11
 #define L_TOURPLANTAG_LOGINID              11
 #define L_TOURPLANTAG_CHANGEID             1


 #define L_TOURPLANTAG_PKEY 28

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define TOURPLANTAG_ANZ ( sizeof(TOURPLANTAG_BES) / sizeof(struct buf_desc) )
#endif
 #define G_TOURPLANTAG sizeof(struct TOURPLANTAG)


 #define TOURPLANTAG_H

 #define TOURPLANTAG_LISTE \
 			TOURPLANTAG.IDFNR, \
 			TOURPLANTAG.DATUMKOMMI, \
 			TOURPLANTAG.TOURID, \
 			TOURPLANTAG.REIHENFOLGENR, \
 			TOURPLANTAG.FAHRTZEIT, \
 			TOURPLANTAG.BEMERKUNGEN, \
 			TOURPLANTAG.KZUPD, \
 			TOURPLANTAG.ISTVERBUNDTOUR, \
 			TOURPLANTAG.VERTRIEBSZENTRUMNR, \
 			TOURPLANTAG.KUNDENNR, \
 			TOURPLANTAG.TM_DATE, \
 			TOURPLANTAG.TM_TIME, \
 			TOURPLANTAG.LOGINID, \
 			TOURPLANTAG.CHANGEID
 #define TOURPLANTAG_PLISTE \
 			"TOURPLANTAG.IDFNR," \
 			"TOURPLANTAG.DATUMKOMMI," \
 			"TOURPLANTAG.TOURID," \
 			"TOURPLANTAG.REIHENFOLGENR," \
 			"TOURPLANTAG.FAHRTZEIT," \
 			"TOURPLANTAG.BEMERKUNGEN," \
 			"TOURPLANTAG.KZUPD," \
 			"TOURPLANTAG.ISTVERBUNDTOUR," \
 			"TOURPLANTAG.VERTRIEBSZENTRUMNR," \
 			"TOURPLANTAG.KUNDENNR," \
 			"TOURPLANTAG.TM_DATE," \
 			"TOURPLANTAG.TM_TIME," \
 			"TOURPLANTAG.LOGINID," \
 			"TOURPLANTAG.CHANGEID " 

 #define TOURPLANTAG_PELISTE \
 			"IDFNR," \
 			"DATUMKOMMI," \
 			"TOURID," \
 			"REIHENFOLGENR," \
 			"FAHRTZEIT," \
 			"BEMERKUNGEN," \
 			"KZUPD," \
 			"ISTVERBUNDTOUR," \
 			"VERTRIEBSZENTRUMNR," \
 			"KUNDENNR," \
 			"TM_DATE," \
 			"TM_TIME," \
 			"LOGINID," \
 			"CHANGEID " 

 #define TOURPLANTAG_UPDLISTE \
 			"IDFNR=?," \
 			"DATUMKOMMI=?," \
 			"TOURID=?," \
 			"REIHENFOLGENR=?," \
 			"FAHRTZEIT=?," \
 			"BEMERKUNGEN=?," \
 			"KZUPD=?," \
 			"ISTVERBUNDTOUR=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"KUNDENNR=?," \
 			"TM_DATE=?," \
 			"TM_TIME=?," \
 			"LOGINID=?," \
 			"CHANGEID=? " 

 #define TOURPLANTAGIDFNR                         0
 #define TOURPLANTAGDATUMKOMMI                    1
 #define TOURPLANTAGTOURID                        2
 #define TOURPLANTAGREIHENFOLGENR                 3
 #define TOURPLANTAGFAHRTZEIT                     4
 #define TOURPLANTAGBEMERKUNGEN                   5
 #define TOURPLANTAGKZUPD                         6
 #define TOURPLANTAGISTVERBUNDTOUR                7
 #define TOURPLANTAGVERTRIEBSZENTRUMNR            8
 #define TOURPLANTAGKUNDENNR                      9
 #define TOURPLANTAGTM_DATE                       10
 #define TOURPLANTAGTM_TIME                       11
 #define TOURPLANTAGLOGINID                       12
 #define TOURPLANTAGCHANGEID                      13

 #define TOURPLANTAG_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->DATUMKOMMI,\
 			:xxx->TOURID,\
 			:xxx->REIHENFOLGENR,\
 			:xxx->FAHRTZEIT,\
 			:xxx->BEMERKUNGEN,\
 			:xxx->KZUPD,\
 			:xxx->ISTVERBUNDTOUR,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->KUNDENNR,\
 			:xxx->TM_DATE,\
 			:xxx->TM_TIME,\
 			:xxx->LOGINID,\
 			:xxx->CHANGEID

 #define TOURPLANTAG_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			DATUMKOMMI = :xxx->DATUMKOMMI,\
 			TOURID = :xxx->TOURID,\
 			REIHENFOLGENR = :xxx->REIHENFOLGENR,\
 			FAHRTZEIT = :xxx->FAHRTZEIT,\
 			BEMERKUNGEN = :xxx->BEMERKUNGEN,\
 			KZUPD = :xxx->KZUPD,\
 			ISTVERBUNDTOUR = :xxx->ISTVERBUNDTOUR,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			TM_DATE = :xxx->TM_DATE,\
 			TM_TIME = :xxx->TM_TIME,\
 			LOGINID = :xxx->LOGINID,\
 			CHANGEID = :xxx->CHANGEID

 #define LS_TOURPLANTAG_IDFNR                11
 #define LS_TOURPLANTAG_DATUMKOMMI           11
 #define LS_TOURPLANTAG_TOURID               7
 #define LS_TOURPLANTAG_REIHENFOLGENR        11
 #define LS_TOURPLANTAG_FAHRTZEIT            7
 #define LS_TOURPLANTAG_BEMERKUNGEN          241
 #define LS_TOURPLANTAG_KZUPD                2
 #define LS_TOURPLANTAG_ISTVERBUNDTOUR       2
 #define LS_TOURPLANTAG_VERTRIEBSZENTRUMNR   7
 #define LS_TOURPLANTAG_KUNDENNR             11
 #define LS_TOURPLANTAG_TM_DATE              11
 #define LS_TOURPLANTAG_TM_TIME              11
 #define LS_TOURPLANTAG_LOGINID              11
 #define LS_TOURPLANTAG_CHANGEID             2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct TOURPLANTAG {
		 long    IDFNR;
		 long    DATUMKOMMI;
		 char    TOURID[6 + 1];
		 long    REIHENFOLGENR;
		 short   FAHRTZEIT;
		 char    BEMERKUNGEN[240 + 1];
		 char    KZUPD[1 + 1];
		 char    ISTVERBUNDTOUR[1 + 1];
		 short   VERTRIEBSZENTRUMNR;
		 long    KUNDENNR;
		 long    TM_DATE;
		 long    TM_TIME;
		 long    LOGINID;
		 char    CHANGEID[1 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_TOURPLANTAG {
		 long    IDFNR;
		 long    DATUMKOMMI;
		 char    TOURID[6 + 1];
		 long    REIHENFOLGENR;
		 short   FAHRTZEIT;
		 char    BEMERKUNGEN[240 + 1];
		 char    KZUPD;
		 char    ISTVERBUNDTOUR;
		 short   VERTRIEBSZENTRUMNR;
		 long    KUNDENNR;
		 long    TM_DATE;
		 long    TM_TIME;
		 long    LOGINID;
		 char    CHANGEID;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_TOURPLANTAG {
		 short  IDFNR;
		 short  DATUMKOMMI;
		 short  TOURID;
		 short  REIHENFOLGENR;
		 short  FAHRTZEIT;
		 short  BEMERKUNGEN;
		 short  KZUPD;
		 short  ISTVERBUNDTOUR;
		 short  VERTRIEBSZENTRUMNR;
		 short  KUNDENNR;
		 short  TM_DATE;
		 short  TM_TIME;
		 short  LOGINID;
		 short  CHANGEID;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_TOURPLANTAG {
		 char    IDFNR[11];
		 char    DATUMKOMMI[11];
		 char    TOURID[6 + 1];
		 char    REIHENFOLGENR[11];
		 char    FAHRTZEIT[7];
		 char    BEMERKUNGEN[240 + 1];
		 char    KZUPD[1 + 1];
		 char    ISTVERBUNDTOUR[1 + 1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1 + 1];
       };

 struct O_TOURPLANTAG {
		 char    IDFNR[11];
		 char    DATUMKOMMI[11];
		 char    TOURID[6];
		 char    REIHENFOLGENR[11];
		 char    FAHRTZEIT[7];
		 char    BEMERKUNGEN[240];
		 char    KZUPD[1];
		 char    ISTVERBUNDTOUR[1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc TOURPLANTAG_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TOURPLANTAG_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CTOURPLANTAG
 {
  public:

  TOURPLANTAG s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, TOURPLANTAG_BES, TOURPLANTAG_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,TOURPLANTAG_BES, TOURPLANTAG_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,TOURPLANTAG_BES, TOURPLANTAG_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CTOURPLANTAG()
  {
   ::buf_default((void *)&s, TOURPLANTAG_BES, TOURPLANTAG_ANZ);
  }
 };
#endif

#define TOURPLANTAG_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR              INTEGER         default 0 NOT NULL,\
		 DATUMKOMMI         INTEGER         default 0 NOT NULL,\
		 TOURID             CHAR(6)         default " " NOT NULL,\
		 REIHENFOLGENR      INTEGER         default 0 NOT NULL,\
		 FAHRTZEIT          SMALLINT        default 0 NOT NULL,\
		 BEMERKUNGEN        VARCHAR(240,0)  default " " NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 ISTVERBUNDTOUR     CHAR(1)         default " " NOT NULL,\
		 VERTRIEBSZENTRUMNR SMALLINT        default 0 NOT NULL,\
		 KUNDENNR           INTEGER         default 0 NOT NULL,\
		 TM_DATE            INTEGER         default 0 NOT NULL,\
		 TM_TIME            INTEGER         default 0 NOT NULL,\
		 LOGINID            INTEGER         default 0 NOT NULL,\
		 CHANGEID           CHAR(1)         default " " NOT NULL  ) EXTENT SIZE 340 LOCK MODE ROW;

#define TOURPLANTAG_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX TOURPLANTAGX       on yyy( IDFNR, DATUMKOMMI, TOURID );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define TOURPLANTAG_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX TOURPLANTAGX      ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

