/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KUNDEKONDI_IDFNR                11
 #define L_KUNDEKONDI_BUENDELRUNDUNGPROZ   3
 #define N_KUNDEKONDI_BUENDELRUNDUNGPROZ   1
 #define L_KUNDEKONDI_MENGENATRABASIS      11
 #define L_KUNDEKONDI_MENGENATRA           11
 #define L_KUNDEKONDI_SKDNATRARABATT04     1
 #define L_KUNDEKONDI_KZUPD                1
 #define L_KUNDEKONDI_VERTRIEBSZENTRUMNR   6
 #define L_KUNDEKONDI_KUNDENNR             11
 #define L_KUNDEKONDI_TM_DATE              11
 #define L_KUNDEKONDI_TM_TIME              11
 #define L_KUNDEKONDI_LOGINID              11
 #define L_KUNDEKONDI_CHANGEID             1


 #define L_KUNDEKONDI_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KUNDEKONDI_ANZ ( sizeof(KUNDEKONDI_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KUNDEKONDI sizeof(struct KUNDEKONDI)


 #define KUNDEKONDI_H

 #define KUNDEKONDI_LISTE \
 			KUNDEKONDI.IDFNR, \
 			KUNDEKONDI.BUENDELRUNDUNGPROZ, \
 			KUNDEKONDI.MENGENATRABASIS, \
 			KUNDEKONDI.MENGENATRA, \
 			KUNDEKONDI.SKDNATRARABATT04, \
 			KUNDEKONDI.KZUPD, \
 			KUNDEKONDI.VERTRIEBSZENTRUMNR, \
 			KUNDEKONDI.KUNDENNR, \
 			KUNDEKONDI.TM_DATE, \
 			KUNDEKONDI.TM_TIME, \
 			KUNDEKONDI.LOGINID, \
 			KUNDEKONDI.CHANGEID
 #define KUNDEKONDI_PLISTE \
 			"KUNDEKONDI.IDFNR," \
 			"KUNDEKONDI.BUENDELRUNDUNGPROZ," \
 			"KUNDEKONDI.MENGENATRABASIS," \
 			"KUNDEKONDI.MENGENATRA," \
 			"KUNDEKONDI.SKDNATRARABATT04," \
 			"KUNDEKONDI.KZUPD," \
 			"KUNDEKONDI.VERTRIEBSZENTRUMNR," \
 			"KUNDEKONDI.KUNDENNR," \
 			"KUNDEKONDI.TM_DATE," \
 			"KUNDEKONDI.TM_TIME," \
 			"KUNDEKONDI.LOGINID," \
 			"KUNDEKONDI.CHANGEID " 

 #define KUNDEKONDI_PELISTE \
 			"IDFNR," \
 			"BUENDELRUNDUNGPROZ," \
 			"MENGENATRABASIS," \
 			"MENGENATRA," \
 			"SKDNATRARABATT04," \
 			"KZUPD," \
 			"VERTRIEBSZENTRUMNR," \
 			"KUNDENNR," \
 			"TM_DATE," \
 			"TM_TIME," \
 			"LOGINID," \
 			"CHANGEID " 

 #define KUNDEKONDI_UPDLISTE \
 			"IDFNR=?," \
 			"BUENDELRUNDUNGPROZ=?," \
 			"MENGENATRABASIS=?," \
 			"MENGENATRA=?," \
 			"SKDNATRARABATT04=?," \
 			"KZUPD=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"KUNDENNR=?," \
 			"TM_DATE=?," \
 			"TM_TIME=?," \
 			"LOGINID=?," \
 			"CHANGEID=? " 

 #define KUNDEKONDIIDFNR                         0
 #define KUNDEKONDIBUENDELRUNDUNGPROZ            1
 #define KUNDEKONDIMENGENATRABASIS               2
 #define KUNDEKONDIMENGENATRA                    3
 #define KUNDEKONDISKDNATRARABATT04              4
 #define KUNDEKONDIKZUPD                         5
 #define KUNDEKONDIVERTRIEBSZENTRUMNR            6
 #define KUNDEKONDIKUNDENNR                      7
 #define KUNDEKONDITM_DATE                       8
 #define KUNDEKONDITM_TIME                       9
 #define KUNDEKONDILOGINID                       10
 #define KUNDEKONDICHANGEID                      11

 #define KUNDEKONDI_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->BUENDELRUNDUNGPROZ,\
 			:xxx->MENGENATRABASIS,\
 			:xxx->MENGENATRA,\
 			:xxx->SKDNATRARABATT04,\
 			:xxx->KZUPD,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->KUNDENNR,\
 			:xxx->TM_DATE,\
 			:xxx->TM_TIME,\
 			:xxx->LOGINID,\
 			:xxx->CHANGEID

 #define KUNDEKONDI_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			BUENDELRUNDUNGPROZ = :xxx->BUENDELRUNDUNGPROZ,\
 			MENGENATRABASIS = :xxx->MENGENATRABASIS,\
 			MENGENATRA = :xxx->MENGENATRA,\
 			SKDNATRARABATT04 = :xxx->SKDNATRARABATT04,\
 			KZUPD = :xxx->KZUPD,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			TM_DATE = :xxx->TM_DATE,\
 			TM_TIME = :xxx->TM_TIME,\
 			LOGINID = :xxx->LOGINID,\
 			CHANGEID = :xxx->CHANGEID

 #define LS_KUNDEKONDI_IDFNR                11
 #define LS_KUNDEKONDI_BUENDELRUNDUNGPROZ   5
 #define LS_KUNDEKONDI_MENGENATRABASIS      11
 #define LS_KUNDEKONDI_MENGENATRA           11
 #define LS_KUNDEKONDI_SKDNATRARABATT04     2
 #define LS_KUNDEKONDI_KZUPD                2
 #define LS_KUNDEKONDI_VERTRIEBSZENTRUMNR   7
 #define LS_KUNDEKONDI_KUNDENNR             11
 #define LS_KUNDEKONDI_TM_DATE              11
 #define LS_KUNDEKONDI_TM_TIME              11
 #define LS_KUNDEKONDI_LOGINID              11
 #define LS_KUNDEKONDI_CHANGEID             2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KUNDEKONDI {
		 long    IDFNR;
		 double  BUENDELRUNDUNGPROZ;
		 long    MENGENATRABASIS;
		 long    MENGENATRA;
		 char    SKDNATRARABATT04[1 + 1];
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

 struct C_KUNDEKONDI {
		 long    IDFNR;
		 double  BUENDELRUNDUNGPROZ;
		 long    MENGENATRABASIS;
		 long    MENGENATRA;
		 char    SKDNATRARABATT04;
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

 struct I_KUNDEKONDI {
		 short  IDFNR;
		 short  BUENDELRUNDUNGPROZ;
		 short  MENGENATRABASIS;
		 short  MENGENATRA;
		 short  SKDNATRARABATT04;
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

 struct S_KUNDEKONDI {
		 char    IDFNR[11];
		 char    BUENDELRUNDUNGPROZ[3 + 2];
		 char    MENGENATRABASIS[11];
		 char    MENGENATRA[11];
		 char    SKDNATRARABATT04[1 + 1];
		 char    KZUPD[1 + 1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1 + 1];
       };

 struct O_KUNDEKONDI {
		 char    IDFNR[11];
		 char    BUENDELRUNDUNGPROZ[3];
		 char    MENGENATRABASIS[11];
		 char    MENGENATRA[11];
		 char    SKDNATRARABATT04[1];
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
 static struct buf_desc KUNDEKONDI_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    3 ,   1 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
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
 static struct buf_desc KUNDEKONDI_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_D,    3 ,   1 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
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

 class CKUNDEKONDI
 {
  public:

  KUNDEKONDI s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KUNDEKONDI_BES, KUNDEKONDI_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KUNDEKONDI_BES, KUNDEKONDI_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KUNDEKONDI_BES, KUNDEKONDI_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKUNDEKONDI()
  {
   ::buf_default((void *)&s, KUNDEKONDI_BES, KUNDEKONDI_ANZ);
  }
 };
#endif

#define KUNDEKONDI_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR              INTEGER         default 0 NOT NULL,\
		 BUENDELRUNDUNGPROZ DECIMAL(3,1)    default 0 NOT NULL,\
		 MENGENATRABASIS    INTEGER         default 0 NOT NULL,\
		 MENGENATRA         INTEGER         default 0 NOT NULL,\
		 SKDNATRARABATT04   CHAR(1)         default " " NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 VERTRIEBSZENTRUMNR SMALLINT        default 0 NOT NULL,\
		 KUNDENNR           INTEGER         default 0 NOT NULL,\
		 TM_DATE            INTEGER         default 0 NOT NULL,\
		 TM_TIME            INTEGER         default 0 NOT NULL,\
		 LOGINID            INTEGER         default 0 NOT NULL,\
		 CHANGEID           CHAR(1)         default " " NOT NULL  ) EXTENT SIZE 253 LOCK MODE ROW;

#define KUNDEKONDI_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KUNDEKONDIX        on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KUNDEKONDI_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KUNDEKONDIX       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

