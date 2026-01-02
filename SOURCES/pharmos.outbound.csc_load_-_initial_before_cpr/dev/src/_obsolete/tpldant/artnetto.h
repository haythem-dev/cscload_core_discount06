/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTIKELMGPREIS_ARTIKEL_NR           11
 #define L_ARTIKELMGPREIS_DATUMGUELTIGAB       11
 #define L_ARTIKELMGPREIS_DATUMGUELTIGBIS      11
 #define L_ARTIKELMGPREIS_KONDGRUPPENNR        11
 #define L_ARTIKELMGPREIS_MENGE                11
 #define L_ARTIKELMGPREIS_PREISEKAPONETTO      9
 #define N_ARTIKELMGPREIS_PREISEKAPONETTO      2
 #define L_ARTIKELMGPREIS_KZUPD                1


 #define L_ARTIKELMGPREIS_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTIKELMGPREIS_ANZ ( sizeof(ARTIKELMGPREIS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTIKELMGPREIS sizeof(struct ARTIKELMGPREIS)


 #define ARTIKELMGPREIS_H

 #define ARTIKELMGPREIS_LISTE \
 			ARTIKELMGPREIS.ARTIKEL_NR, \
 			ARTIKELMGPREIS.DATUMGUELTIGAB, \
 			ARTIKELMGPREIS.DATUMGUELTIGBIS, \
 			ARTIKELMGPREIS.KONDGRUPPENNR, \
 			ARTIKELMGPREIS.MENGE, \
 			ARTIKELMGPREIS.PREISEKAPONETTO, \
 			ARTIKELMGPREIS.KZUPD
 #define ARTIKELMGPREIS_PLISTE \
 			"ARTIKELMGPREIS.ARTIKEL_NR," \
 			"ARTIKELMGPREIS.DATUMGUELTIGAB," \
 			"ARTIKELMGPREIS.DATUMGUELTIGBIS," \
 			"ARTIKELMGPREIS.KONDGRUPPENNR," \
 			"ARTIKELMGPREIS.MENGE," \
 			"ARTIKELMGPREIS.PREISEKAPONETTO," \
 			"ARTIKELMGPREIS.KZUPD " 

 #define ARTIKELMGPREIS_PELISTE \
 			"ARTIKEL_NR," \
 			"DATUMGUELTIGAB," \
 			"DATUMGUELTIGBIS," \
 			"KONDGRUPPENNR," \
 			"MENGE," \
 			"PREISEKAPONETTO," \
 			"KZUPD " 

 #define ARTIKELMGPREIS_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"DATUMGUELTIGAB=?," \
 			"DATUMGUELTIGBIS=?," \
 			"KONDGRUPPENNR=?," \
 			"MENGE=?," \
 			"PREISEKAPONETTO=?," \
 			"KZUPD=? " 

 #define ARTIKELMGPREISARTIKEL_NR                    0
 #define ARTIKELMGPREISDATUMGUELTIGAB                1
 #define ARTIKELMGPREISDATUMGUELTIGBIS               2
 #define ARTIKELMGPREISKONDGRUPPENNR                 3
 #define ARTIKELMGPREISMENGE                         4
 #define ARTIKELMGPREISPREISEKAPONETTO               5
 #define ARTIKELMGPREISKZUPD                         6

 #define ARTIKELMGPREIS_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->DATUMGUELTIGAB,\
 			:xxx->DATUMGUELTIGBIS,\
 			:xxx->KONDGRUPPENNR,\
 			:xxx->MENGE,\
 			:xxx->PREISEKAPONETTO,\
 			:xxx->KZUPD

 #define ARTIKELMGPREIS_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			DATUMGUELTIGAB = :xxx->DATUMGUELTIGAB,\
 			DATUMGUELTIGBIS = :xxx->DATUMGUELTIGBIS,\
 			KONDGRUPPENNR = :xxx->KONDGRUPPENNR,\
 			MENGE = :xxx->MENGE,\
 			PREISEKAPONETTO = :xxx->PREISEKAPONETTO,\
 			KZUPD = :xxx->KZUPD

 #define LS_ARTIKELMGPREIS_ARTIKEL_NR           11
 #define LS_ARTIKELMGPREIS_DATUMGUELTIGAB       11
 #define LS_ARTIKELMGPREIS_DATUMGUELTIGBIS      11
 #define LS_ARTIKELMGPREIS_KONDGRUPPENNR        11
 #define LS_ARTIKELMGPREIS_MENGE                11
 #define LS_ARTIKELMGPREIS_PREISEKAPONETTO      11
 #define LS_ARTIKELMGPREIS_KZUPD                2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTIKELMGPREIS {
		 long    ARTIKEL_NR;
		 long    DATUMGUELTIGAB;
		 long    DATUMGUELTIGBIS;
		 long    KONDGRUPPENNR;
		 long    MENGE;
		 double  PREISEKAPONETTO;
		 char    KZUPD[1 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTIKELMGPREIS {
		 long    ARTIKEL_NR;
		 long    DATUMGUELTIGAB;
		 long    DATUMGUELTIGBIS;
		 long    KONDGRUPPENNR;
		 long    MENGE;
		 double  PREISEKAPONETTO;
		 char    KZUPD;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTIKELMGPREIS {
		 short  ARTIKEL_NR;
		 short  DATUMGUELTIGAB;
		 short  DATUMGUELTIGBIS;
		 short  KONDGRUPPENNR;
		 short  MENGE;
		 short  PREISEKAPONETTO;
		 short  KZUPD;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTIKELMGPREIS {
		 char    ARTIKEL_NR[11];
		 char    DATUMGUELTIGAB[11];
		 char    DATUMGUELTIGBIS[11];
		 char    KONDGRUPPENNR[11];
		 char    MENGE[11];
		 char    PREISEKAPONETTO[9 + 2];
		 char    KZUPD[1 + 1];
       };

 struct O_ARTIKELMGPREIS {
		 char    ARTIKEL_NR[11];
		 char    DATUMGUELTIGAB[11];
		 char    DATUMGUELTIGBIS[11];
		 char    KONDGRUPPENNR[11];
		 char    MENGE[11];
		 char    PREISEKAPONETTO[9];
		 char    KZUPD[1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTIKELMGPREIS_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    9 ,   2 },
	 { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELMGPREIS_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_D,    9 ,   2 },
	 { TYP_F,    1 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTIKELMGPREIS
 {
  public:

  ARTIKELMGPREIS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTIKELMGPREIS_BES, ARTIKELMGPREIS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTIKELMGPREIS_BES, ARTIKELMGPREIS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTIKELMGPREIS_BES, ARTIKELMGPREIS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTIKELMGPREIS()
  {
   ::buf_default((void *)&s, ARTIKELMGPREIS_BES, ARTIKELMGPREIS_ANZ);
  }
 };
#endif

#define ARTIKELMGPREIS_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR         INTEGER         default 0 NOT NULL,\
		 DATUMGUELTIGAB     INTEGER         default 0 NOT NULL,\
		 DATUMGUELTIGBIS    INTEGER         default 0 NOT NULL,\
		 KONDGRUPPENNR      INTEGER         default 0 NOT NULL,\
		 MENGE              INTEGER         default 0 NOT NULL,\
		 PREISEKAPONETTO    DECIMAL(9,2)    default 0 NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL  ) EXTENT SIZE 2253 LOCK MODE ROW;

#define ARTIKELMGPREIS_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_ARTIKELMGPREIS_1 on yyy( ARTIKEL_NR, DATUMGUELTIGAB, KONDGRUPPENNR, MENGE );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTIKELMGPREIS_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKELMGPREIS_1;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

