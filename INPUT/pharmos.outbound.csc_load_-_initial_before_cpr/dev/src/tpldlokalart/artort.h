/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTIKELLAGERORT_FILIALNR             6
 #define L_ARTIKELLAGERORT_ARTIKEL_NR           11
 #define L_ARTIKELLAGERORT_LAGERBEREICHNR       6
 #define L_ARTIKELLAGERORT_STATIONNR            2
 #define L_ARTIKELLAGERORT_LAGERFACHNR          10
 #define L_ARTIKELLAGERORT_DATUMVERFALL         11
 #define L_ARTIKELLAGERORT_BESTAND              11
 #define L_ARTIKELLAGERORT_VERBUNDARTIKEL       1


 #define L_ARTIKELLAGERORT_PKEY 35

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTIKELLAGERORT_ANZ ( sizeof(ARTIKELLAGERORT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTIKELLAGERORT sizeof(struct ARTIKELLAGERORT)


 #define ARTIKELLAGERORT_H

 #define ARTIKELLAGERORT_LISTE \
 			ARTIKELLAGERORT.FILIALNR, \
 			ARTIKELLAGERORT.ARTIKEL_NR, \
 			ARTIKELLAGERORT.LAGERBEREICHNR, \
 			ARTIKELLAGERORT.STATIONNR, \
 			ARTIKELLAGERORT.LAGERFACHNR, \
 			ARTIKELLAGERORT.DATUMVERFALL, \
 			ARTIKELLAGERORT.BESTAND, \
 			ARTIKELLAGERORT.VERBUNDARTIKEL
 #define ARTIKELLAGERORT_PLISTE \
 			"ARTIKELLAGERORT.FILIALNR," \
 			"ARTIKELLAGERORT.ARTIKEL_NR," \
 			"ARTIKELLAGERORT.LAGERBEREICHNR," \
 			"ARTIKELLAGERORT.STATIONNR," \
 			"ARTIKELLAGERORT.LAGERFACHNR," \
 			"ARTIKELLAGERORT.DATUMVERFALL," \
 			"ARTIKELLAGERORT.BESTAND," \
 			"ARTIKELLAGERORT.VERBUNDARTIKEL "

 #define ARTIKELLAGERORT_PELISTE \
 			"FILIALNR," \
 			"ARTIKEL_NR," \
 			"LAGERBEREICHNR," \
 			"STATIONNR," \
 			"LAGERFACHNR," \
 			"DATUMVERFALL," \
 			"BESTAND," \
 			"VERBUNDARTIKEL " 

 #define ARTIKELLAGERORT_UPDLISTE \
 			"FILIALNR=?," \
 			"ARTIKEL_NR=?," \
 			"LAGERBEREICHNR=?," \
 			"STATIONNR=?," \
 			"LAGERFACHNR=?," \
 			"DATUMVERFALL=?," \
 			"BESTAND=?," \
 			"VERBUNDARTIKEL=? " 

 #define ARTIKELLAGERORTFILIALNR                      0
 #define ARTIKELLAGERORTARTIKEL_NR                    1
 #define ARTIKELLAGERORTLAGERBEREICHNR                2
 #define ARTIKELLAGERORTSTATIONNR                     3
 #define ARTIKELLAGERORTLAGERFACHNR                   4
 #define ARTIKELLAGERORTDATUMVERFALL                  5
 #define ARTIKELLAGERORTBESTAND                       6
 #define ARTIKELLAGERORTVERBUNDARTIKEL                7

 #define ARTIKELLAGERORT_ZEIGER(xxx) \
 			:xxx->FILIALNR,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->LAGERBEREICHNR,\
 			:xxx->STATIONNR,\
 			:xxx->LAGERFACHNR,\
 			:xxx->DATUMVERFALL,\
 			:xxx->BESTAND,\
 			:xxx->VERBUNDARTIKEL

 #define ARTIKELLAGERORT_UPDATE(xxx) \
 			FILIALNR = :xxx->FILIALNR,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			LAGERBEREICHNR = :xxx->LAGERBEREICHNR,\
 			STATIONNR = :xxx->STATIONNR,\
 			LAGERFACHNR = :xxx->LAGERFACHNR,\
 			DATUMVERFALL = :xxx->DATUMVERFALL,\
 			BESTAND = :xxx->BESTAND,\
 			VERBUNDARTIKEL = :xxx->VERBUNDARTIKEL

 #define LS_ARTIKELLAGERORT_FILIALNR             7
 #define LS_ARTIKELLAGERORT_ARTIKEL_NR           11
 #define LS_ARTIKELLAGERORT_LAGERBEREICHNR       7
 #define LS_ARTIKELLAGERORT_STATIONNR            3
 #define LS_ARTIKELLAGERORT_LAGERFACHNR          11
 #define LS_ARTIKELLAGERORT_DATUMVERFALL         11
 #define LS_ARTIKELLAGERORT_BESTAND              11
 #define LS_ARTIKELLAGERORT_VERBUNDARTIKEL       2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTIKELLAGERORT {
		 short   FILIALNR;
		 long    ARTIKEL_NR;
		 short   LAGERBEREICHNR;
		 char    STATIONNR[2 + 1];
		 char    LAGERFACHNR[10 + 1];
		 long    DATUMVERFALL;
		 long    BESTAND;
		 char    VERBUNDARTIKEL[1 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTIKELLAGERORT {
		 short   FILIALNR;
		 long    ARTIKEL_NR;
		 short   LAGERBEREICHNR;
		 char    STATIONNR[2 + 1];
		 char    LAGERFACHNR[10 + 1];
		 long    DATUMVERFALL;
		 long    BESTAND;
		 char    VERBUNDARTIKEL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTIKELLAGERORT {
		 short  FILIALNR;
		 short  ARTIKEL_NR;
		 short  LAGERBEREICHNR;
		 short  STATIONNR;
		 short  LAGERFACHNR;
		 short  DATUMVERFALL;
		 short  BESTAND;
		 short  VERBUNDARTIKEL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTIKELLAGERORT {
		 char    FILIALNR[7];
		 char    ARTIKEL_NR[11];
		 char    LAGERBEREICHNR[7];
		 char    STATIONNR[2 + 1];
		 char    LAGERFACHNR[10 + 1];
		 char    DATUMVERFALL[11];
		 char    BESTAND[11];
		 char    VERBUNDARTIKEL[1 + 1];
       };

 struct O_ARTIKELLAGERORT {
		 char    FILIALNR[7];
		 char    ARTIKEL_NR[11];
		 char    LAGERBEREICHNR[7];
		 char    STATIONNR[2];
		 char    LAGERFACHNR[10];
		 char    DATUMVERFALL[11];
		 char    BESTAND[11];
		 char    VERBUNDARTIKEL[1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTIKELLAGERORT_BES [] =
 {
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELLAGERORT_BES [] =
 {
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C,   10 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTIKELLAGERORT
 {
  public:

  ARTIKELLAGERORT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTIKELLAGERORT_BES, ARTIKELLAGERORT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTIKELLAGERORT_BES, ARTIKELLAGERORT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTIKELLAGERORT_BES, ARTIKELLAGERORT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTIKELLAGERORT()
  {
   ::buf_default((void *)&s, ARTIKELLAGERORT_BES, ARTIKELLAGERORT_ANZ);
  }
 };
#endif

#define ARTIKELLAGERORT_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 FILIALNR           SMALLINT        default 0 NOT NULL,\
		 ARTIKEL_NR         INTEGER         default 0 NOT NULL,\
		 LAGERBEREICHNR     SMALLINT        default 0 NOT NULL,\
		 STATIONNR          CHAR(2)         default " " NOT NULL,\
		 LAGERFACHNR        CHAR(10)        default " " NOT NULL,\
		 DATUMVERFALL       INTEGER         default 0 NOT NULL,\
		 BESTAND            INTEGER         default 0 NOT NULL,\
		 VERBUNDARTIKEL     CHAR(1)         default " " NOT NULL  ) EXTENT SIZE 53693 LOCK MODE ROW;

#define ARTIKELLAGERORT_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_5 on yyy( FILIALNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_2 on yyy( FILIALNR, ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKELLAGERORT_ on yyy( FILIALNR, ARTIKEL_NR, LAGERBEREICHNR, STATIONNR, LAGERFACHNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELLAGEROR_4 on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTIKELLAGERORT_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_5;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_2;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGERORT_;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELLAGEROR_4;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

