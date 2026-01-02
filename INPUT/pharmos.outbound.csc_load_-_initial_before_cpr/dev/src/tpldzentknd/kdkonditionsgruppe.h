/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KDKONDITIONGRUPPE_IDFNR                11
 #define L_KDKONDITIONGRUPPE_KONDGRUPPENNR        11
 #define L_KDKONDITIONGRUPPE_KZUPD                1
 #define L_KDKONDITIONGRUPPE_VERTRIEBSZENTRUMNR   6
 #define L_KDKONDITIONGRUPPE_KUNDENNR             11
 #define L_KDKONDITIONGRUPPE_TM_DATE              11
 #define L_KDKONDITIONGRUPPE_TM_TIME              11
 #define L_KDKONDITIONGRUPPE_LOGINID              11
 #define L_KDKONDITIONGRUPPE_CHANGEID             1


 #define L_KDKONDITIONGRUPPE_PKEY 22

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KDKONDITIONGRUPPE_ANZ ( sizeof(KDKONDITIONGRUPPE_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KDKONDITIONGRUPPE sizeof(struct KDKONDITIONGRUPPE)


 #define KDKONDITIONGRUPPE_H

 #define KDKONDITIONGRUPPE_LISTE \
 			KDKONDITIONGRUPPE.IDFNR, \
 			KDKONDITIONGRUPPE.KONDGRUPPENNR, \
 			KDKONDITIONGRUPPE.KZUPD, \
 			KDKONDITIONGRUPPE.VERTRIEBSZENTRUMNR, \
 			KDKONDITIONGRUPPE.KUNDENNR, \
 			KDKONDITIONGRUPPE.TM_DATE, \
 			KDKONDITIONGRUPPE.TM_TIME, \
 			KDKONDITIONGRUPPE.LOGINID, \
 			KDKONDITIONGRUPPE.CHANGEID
 #define KDKONDITIONGRUPPE_PLISTE \
 			"KDKONDITIONGRUPPE.IDFNR," \
 			"KDKONDITIONGRUPPE.KONDGRUPPENNR," \
 			"KDKONDITIONGRUPPE.KZUPD," \
 			"KDKONDITIONGRUPPE.VERTRIEBSZENTRUMNR," \
 			"KDKONDITIONGRUPPE.KUNDENNR," \
 			"KDKONDITIONGRUPPE.TM_DATE," \
 			"KDKONDITIONGRUPPE.TM_TIME," \
 			"KDKONDITIONGRUPPE.LOGINID," \
 			"KDKONDITIONGRUPPE.CHANGEID " 

 #define KDKONDITIONGRUPPE_PELISTE \
 			"IDFNR," \
 			"KONDGRUPPENNR," \
 			"KZUPD," \
 			"VERTRIEBSZENTRUMNR," \
 			"KUNDENNR," \
 			"TM_DATE," \
 			"TM_TIME," \
 			"LOGINID," \
 			"CHANGEID " 

 #define KDKONDITIONGRUPPE_UPDLISTE \
 			"IDFNR=?," \
 			"KONDGRUPPENNR=?," \
 			"KZUPD=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"KUNDENNR=?," \
 			"TM_DATE=?," \
 			"TM_TIME=?," \
 			"LOGINID=?," \
 			"CHANGEID=? " 

 #define KDKONDITIONGRUPPEIDFNR                         0
 #define KDKONDITIONGRUPPEKONDGRUPPENNR                 1
 #define KDKONDITIONGRUPPEKZUPD                         2
 #define KDKONDITIONGRUPPEVERTRIEBSZENTRUMNR            3
 #define KDKONDITIONGRUPPEKUNDENNR                      4
 #define KDKONDITIONGRUPPETM_DATE                       5
 #define KDKONDITIONGRUPPETM_TIME                       6
 #define KDKONDITIONGRUPPELOGINID                       7
 #define KDKONDITIONGRUPPECHANGEID                      8

 #define KDKONDITIONGRUPPE_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->KONDGRUPPENNR,\
 			:xxx->KZUPD,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->KUNDENNR,\
 			:xxx->TM_DATE,\
 			:xxx->TM_TIME,\
 			:xxx->LOGINID,\
 			:xxx->CHANGEID

 #define KDKONDITIONGRUPPE_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			KONDGRUPPENNR = :xxx->KONDGRUPPENNR,\
 			KZUPD = :xxx->KZUPD,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			TM_DATE = :xxx->TM_DATE,\
 			TM_TIME = :xxx->TM_TIME,\
 			LOGINID = :xxx->LOGINID,\
 			CHANGEID = :xxx->CHANGEID

 #define LS_KDKONDITIONGRUPPE_IDFNR                11
 #define LS_KDKONDITIONGRUPPE_KONDGRUPPENNR        11
 #define LS_KDKONDITIONGRUPPE_KZUPD                2
 #define LS_KDKONDITIONGRUPPE_VERTRIEBSZENTRUMNR   7
 #define LS_KDKONDITIONGRUPPE_KUNDENNR             11
 #define LS_KDKONDITIONGRUPPE_TM_DATE              11
 #define LS_KDKONDITIONGRUPPE_TM_TIME              11
 #define LS_KDKONDITIONGRUPPE_LOGINID              11
 #define LS_KDKONDITIONGRUPPE_CHANGEID             2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KDKONDITIONGRUPPE {
		 long    IDFNR;
		 long    KONDGRUPPENNR;
		 char    KZUPD[1 + 1];
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

 struct C_KDKONDITIONGRUPPE {
		 long    IDFNR;
		 long    KONDGRUPPENNR;
		 char    KZUPD;
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

 struct I_KDKONDITIONGRUPPE {
		 short  IDFNR;
		 short  KONDGRUPPENNR;
		 short  KZUPD;
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

 struct S_KDKONDITIONGRUPPE {
		 char    IDFNR[11];
		 char    KONDGRUPPENNR[11];
		 char    KZUPD[1 + 1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1 + 1];
       };

 struct O_KDKONDITIONGRUPPE {
		 char    IDFNR[11];
		 char    KONDGRUPPENNR[11];
		 char    KZUPD[1];
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
 static struct buf_desc KDKONDITIONGRUPPE_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDKONDITIONGRUPPE_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
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

 class CKDKONDITIONGRUPPE
 {
  public:

  KDKONDITIONGRUPPE s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KDKONDITIONGRUPPE_BES, KDKONDITIONGRUPPE_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KDKONDITIONGRUPPE_BES, KDKONDITIONGRUPPE_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KDKONDITIONGRUPPE_BES, KDKONDITIONGRUPPE_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKDKONDITIONGRUPPE()
  {
   ::buf_default((void *)&s, KDKONDITIONGRUPPE_BES, KDKONDITIONGRUPPE_ANZ);
  }
 };
#endif

#define KDKONDITIONGRUPPE_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR              INTEGER         default 0 NOT NULL,\
		 KONDGRUPPENNR      INTEGER         default 0 NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 VERTRIEBSZENTRUMNR SMALLINT        default 0 NOT NULL,\
		 KUNDENNR           INTEGER         default 0 NOT NULL,\
		 TM_DATE            INTEGER         default 0 NOT NULL,\
		 TM_TIME            INTEGER         default 0 NOT NULL,\
		 LOGINID            INTEGER         default 0 NOT NULL,\
		 CHANGEID           CHAR(1)         default " " NOT NULL  ) EXTENT SIZE 95 LOCK MODE ROW;

#define KDKONDITIONGRUPPE_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_KDKONDITIONGRU_1 on yyy( IDFNR, KONDGRUPPENNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KDKONDITIONGRUPPE_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_KDKONDITIONGRU_1;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

