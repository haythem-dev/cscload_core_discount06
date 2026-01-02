/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTIKELNATRA_NATRASTAFFELNR       11
 #define L_ARTIKELNATRA_RABATTSCHLUESSEL     6
 #define L_ARTIKELNATRA_DATUMGUELTIGAB       11
 #define L_ARTIKELNATRA_DATUMGUELTIGBIS      11
 #define L_ARTIKELNATRA_KONDGRUPPENNR        11
 #define L_ARTIKELNATRA_MENGENATRABASIS      11
 #define L_ARTIKELNATRA_MENGENATRA           11
 #define L_ARTIKELNATRA_VERTRIEBSZENTRUMNR   6
 #define L_ARTIKELNATRA_NRINTERN             1


 #define L_ARTIKELNATRA_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTIKELNATRA_ANZ ( sizeof(ARTIKELNATRA_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTIKELNATRA sizeof(struct ARTIKELNATRA)


 #define ARTIKELNATRA_H

 #define ARTIKELNATRA_LISTE \
 			ARTIKELNATRA.NATRASTAFFELNR, \
 			ARTIKELNATRA.RABATTSCHLUESSEL, \
 			ARTIKELNATRA.DATUMGUELTIGAB, \
 			ARTIKELNATRA.DATUMGUELTIGBIS, \
 			ARTIKELNATRA.KONDGRUPPENNR, \
 			ARTIKELNATRA.MENGENATRABASIS, \
 			ARTIKELNATRA.MENGENATRA, \
 			ARTIKELNATRA.VERTRIEBSZENTRUMNR, \
 			ARTIKELNATRA.NRINTERN
 #define ARTIKELNATRA_PLISTE \
 			"ARTIKELNATRA.NATRASTAFFELNR," \
 			"ARTIKELNATRA.RABATTSCHLUESSEL," \
 			"ARTIKELNATRA.DATUMGUELTIGAB," \
 			"ARTIKELNATRA.DATUMGUELTIGBIS," \
 			"ARTIKELNATRA.KONDGRUPPENNR," \
 			"ARTIKELNATRA.MENGENATRABASIS," \
 			"ARTIKELNATRA.MENGENATRA," \
 			"ARTIKELNATRA.VERTRIEBSZENTRUMNR," \
 			"ARTIKELNATRA.NRINTERN "
 #define ARTIKELNATRA_PELISTE \
 			"NATRASTAFFELNR," \
 			"RABATTSCHLUESSEL," \
 			"DATUMGUELTIGAB," \
 			"DATUMGUELTIGBIS," \
 			"KONDGRUPPENNR," \
 			"MENGENATRABASIS," \
 			"MENGENATRA," \
 			"VERTRIEBSZENTRUMNR," \
 			"NRINTERN "

 #define ARTIKELNATRANATRASTAFFELNR                0
 #define ARTIKELNATRARABATTSCHLUESSEL              1
 #define ARTIKELNATRADATUMGUELTIGAB                2
 #define ARTIKELNATRADATUMGUELTIGBIS               3
 #define ARTIKELNATRAKONDGRUPPENNR                 4
 #define ARTIKELNATRAMENGENATRABASIS               5
 #define ARTIKELNATRAMENGENATRA                    6
 #define ARTIKELNATRAVERTRIEBSZENTRUMNR            7
 #define ARTIKELNATRANRINTERN                      8

 #define ARTIKELNATRA_ZEIGER(xxx) \
 			:xxx->NATRASTAFFELNR,\
 			:xxx->RABATTSCHLUESSEL,\
 			:xxx->DATUMGUELTIGAB,\
 			:xxx->DATUMGUELTIGBIS,\
 			:xxx->KONDGRUPPENNR,\
 			:xxx->MENGENATRABASIS,\
 			:xxx->MENGENATRA,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->NRINTERN

 #define ARTIKELNATRA_UPDATE(xxx) \
 			NATRASTAFFELNR = :xxx->NATRASTAFFELNR,\
 			RABATTSCHLUESSEL = :xxx->RABATTSCHLUESSEL,\
 			DATUMGUELTIGAB = :xxx->DATUMGUELTIGAB,\
 			DATUMGUELTIGBIS = :xxx->DATUMGUELTIGBIS,\
 			KONDGRUPPENNR = :xxx->KONDGRUPPENNR,\
 			MENGENATRABASIS = :xxx->MENGENATRABASIS,\
 			MENGENATRA = :xxx->MENGENATRA,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			NRINTERN = :xxx->NRINTERN

 #define LS_ARTIKELNATRA_NATRASTAFFELNR       11
 #define LS_ARTIKELNATRA_RABATTSCHLUESSEL     7
 #define LS_ARTIKELNATRA_DATUMGUELTIGAB       11
 #define LS_ARTIKELNATRA_DATUMGUELTIGBIS      11
 #define LS_ARTIKELNATRA_KONDGRUPPENNR        11
 #define LS_ARTIKELNATRA_MENGENATRABASIS      11
 #define LS_ARTIKELNATRA_MENGENATRA           11
 #define LS_ARTIKELNATRA_VERTRIEBSZENTRUMNR   7
 #define LS_ARTIKELNATRA_NRINTERN             2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTIKELNATRA {
		 long    NATRASTAFFELNR;
		 short   RABATTSCHLUESSEL;
		 long    DATUMGUELTIGAB;
		 long    DATUMGUELTIGBIS;
		 long    KONDGRUPPENNR;
		 long    MENGENATRABASIS;
		 long    MENGENATRA;
		 short   VERTRIEBSZENTRUMNR;
		 char    NRINTERN[1 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTIKELNATRA {
		 long    NATRASTAFFELNR;
		 short   RABATTSCHLUESSEL;
		 long    DATUMGUELTIGAB;
		 long    DATUMGUELTIGBIS;
		 long    KONDGRUPPENNR;
		 long    MENGENATRABASIS;
		 long    MENGENATRA;
		 short   VERTRIEBSZENTRUMNR;
		 char    NRINTERN;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTIKELNATRA {
		 short  NATRASTAFFELNR;
		 short  RABATTSCHLUESSEL;
		 short  DATUMGUELTIGAB;
		 short  DATUMGUELTIGBIS;
		 short  KONDGRUPPENNR;
		 short  MENGENATRABASIS;
		 short  MENGENATRA;
		 short  VERTRIEBSZENTRUMNR;
		 short  NRINTERN;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTIKELNATRA {
		 char    NATRASTAFFELNR[11];
		 char    RABATTSCHLUESSEL[7];
		 char    DATUMGUELTIGAB[11];
		 char    DATUMGUELTIGBIS[11];
		 char    KONDGRUPPENNR[11];
		 char    MENGENATRABASIS[11];
		 char    MENGENATRA[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    NRINTERN[1 + 1];
       };

 struct O_ARTIKELNATRA {
		 char    NATRASTAFFELNR[11];
		 char    RABATTSCHLUESSEL[7];
		 char    DATUMGUELTIGAB[11];
		 char    DATUMGUELTIGBIS[11];
		 char    KONDGRUPPENNR[11];
		 char    MENGENATRABASIS[11];
		 char    MENGENATRA[11];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    NRINTERN[1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTIKELNATRA_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELNATRA_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTIKELNATRA
 {
  public:

  ARTIKELNATRA s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTIKELNATRA_BES, ARTIKELNATRA_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTIKELNATRA_BES, ARTIKELNATRA_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTIKELNATRA_BES, ARTIKELNATRA_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTIKELNATRA()
  {
   ::buf_default((void *)&s, ARTIKELNATRA_BES, ARTIKELNATRA_ANZ);
  }
 };
#endif

#define ARTIKELNATRA_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 NATRASTAFFELNR     INTEGER         default 0 NOT NULL,\
		 RABATTSCHLUESSEL   SMALLINT        default 0 NOT NULL,\
		 DATUMGUELTIGAB     INTEGER         default 0 NOT NULL,\
		 DATUMGUELTIGBIS    INTEGER         default 0 NOT NULL,\
		 KONDGRUPPENNR      INTEGER         default 0 NOT NULL,\
		 MENGENATRABASIS    INTEGER         default 0 NOT NULL,\
		 MENGENATRA         INTEGER         default 0 NOT NULL,\
		 VERTRIEBSZENTRUMNR SMALLINT        default 0 NOT NULL,\
		 NRINTERN			CHAR(1)			default " " NOT NULL  ) EXTENT SIZE 12121;

#define ARTIKELNATRA_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_ARTIKELNATRA_1   on yyy( NATRASTAFFELNR, RABATTSCHLUESSEL, DATUMGUELTIGAB, KONDGRUPPENNR, MENGENATRABASIS );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTIKELNATRA_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKELNATRA_1  ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

