/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTSELECT_ARTIKEL_NR           11
 #define L_ARTSELECT_ARTIKEL_MC           12
 #define L_ARTSELECT_PACKGROESSE          11
 #define L_ARTSELECT_DARREICHFORM         3
 #define L_ARTSELECT_EINHEIT              9
 #define L_ARTSELECT_ARTIKEL_NAME         30
 #define L_ARTSELECT_ETARTSCHALTER1       5
 #define L_ARTSELECT_ETARTSCHALTER2       5
 #define L_ARTSELECT_ETARTSCHALTER3       5
 #define L_ARTSELECT_ETARTSCHALTER4       5
 #define L_ARTSELECT_ETBESTAND            5
 #define L_ARTSELECT_DATUMVERFALL         11
 #define L_ARTSELECT_PRISOART             1
 #define L_ARTSELECT_PREISEKAPO           9
 #define N_ARTSELECT_PREISEKAPO           2


 #define L_ARTSELECT_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTSELECT_ANZ ( sizeof(ARTSELECT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTSELECT sizeof(struct ARTSELECT)


 #define ARTSELECT_H

 #define ARTSELECT_LISTE \
 			ARTSELECT.ARTIKEL_NR, \
 			ARTSELECT.ARTIKEL_MC, \
 			ARTSELECT.PACKGROESSE, \
 			ARTSELECT.DARREICHFORM, \
 			ARTSELECT.EINHEIT, \
 			ARTSELECT.ARTIKEL_NAME, \
 			ARTSELECT.ETARTSCHALTER1, \
 			ARTSELECT.ETARTSCHALTER2, \
 			ARTSELECT.ETARTSCHALTER3, \
 			ARTSELECT.ETARTSCHALTER4, \
 			ARTSELECT.ETBESTAND, \
 			ARTSELECT.DATUMVERFALL, \
 			ARTSELECT.PRISOART, \
 			ARTSELECT.PREISEKAPO
 #define ARTSELECT_PLISTE \
 			"ARTSELECT.ARTIKEL_NR," \
 			"ARTSELECT.ARTIKEL_MC," \
 			"ARTSELECT.PACKGROESSE," \
 			"ARTSELECT.DARREICHFORM," \
 			"ARTSELECT.EINHEIT," \
 			"ARTSELECT.ARTIKEL_NAME," \
 			"ARTSELECT.ETARTSCHALTER1," \
 			"ARTSELECT.ETARTSCHALTER2," \
 			"ARTSELECT.ETARTSCHALTER3," \
 			"ARTSELECT.ETARTSCHALTER4," \
 			"ARTSELECT.ETBESTAND," \
 			"ARTSELECT.DATUMVERFALL," \
 			"ARTSELECT.PRISOART," \
 			"ARTSELECT.PREISEKAPO " 
 #define ARTSELECT_PELISTE \
 			"ARTIKEL_NR," \
 			"ARTIKEL_MC," \
 			"PACKGROESSE," \
 			"DARREICHFORM," \
 			"EINHEIT," \
 			"ARTIKEL_NAME," \
 			"ETARTSCHALTER1," \
 			"ETARTSCHALTER2," \
 			"ETARTSCHALTER3," \
 			"ETARTSCHALTER4," \
 			"ETBESTAND," \
 			"DATUMVERFALL," \
 			"PRISOART," \
 			"PREISEKAPO " 

 #define ARTSELECTARTIKEL_NR                    0
 #define ARTSELECTARTIKEL_MC                    1
 #define ARTSELECTPACKGROESSE                   2
 #define ARTSELECTDARREICHFORM                  3
 #define ARTSELECTEINHEIT                       4
 #define ARTSELECTARTIKEL_NAME                  5
 #define ARTSELECTETARTSCHALTER1                6
 #define ARTSELECTETARTSCHALTER2                7
 #define ARTSELECTETARTSCHALTER3                8
 #define ARTSELECTETARTSCHALTER4                9
 #define ARTSELECTETBESTAND                     10
 #define ARTSELECTDATUMVERFALL                  11
 #define ARTSELECTPRISOART                      12
 #define ARTSELECTPREISEKAPO                    13

 #define ARTSELECT_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->ARTIKEL_MC,\
 			:xxx->PACKGROESSE,\
 			:xxx->DARREICHFORM,\
 			:xxx->EINHEIT,\
 			:xxx->ARTIKEL_NAME,\
 			:xxx->ETARTSCHALTER1,\
 			:xxx->ETARTSCHALTER2,\
 			:xxx->ETARTSCHALTER3,\
 			:xxx->ETARTSCHALTER4,\
 			:xxx->ETBESTAND,\
 			:xxx->DATUMVERFALL,\
 			:xxx->PRISOART,\
 			:xxx->PREISEKAPO

 #define ARTSELECT_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			ARTIKEL_MC = :xxx->ARTIKEL_MC,\
 			PACKGROESSE = :xxx->PACKGROESSE,\
 			DARREICHFORM = :xxx->DARREICHFORM,\
 			EINHEIT = :xxx->EINHEIT,\
 			ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
 			ETARTSCHALTER1 = :xxx->ETARTSCHALTER1,\
 			ETARTSCHALTER2 = :xxx->ETARTSCHALTER2,\
 			ETARTSCHALTER3 = :xxx->ETARTSCHALTER3,\
 			ETARTSCHALTER4 = :xxx->ETARTSCHALTER4,\
 			ETBESTAND = :xxx->ETBESTAND,\
 			DATUMVERFALL = :xxx->DATUMVERFALL,\
 			PRISOART = :xxx->PRISOART,\
 			PREISEKAPO = :xxx->PREISEKAPO

 #define LS_ARTSELECT_ARTIKEL_NR           11
 #define LS_ARTSELECT_ARTIKEL_MC           13
 #define LS_ARTSELECT_PACKGROESSE          11
 #define LS_ARTSELECT_DARREICHFORM         4
 #define LS_ARTSELECT_EINHEIT              10
 #define LS_ARTSELECT_ARTIKEL_NAME         31
 #define LS_ARTSELECT_ETARTSCHALTER1       6
 #define LS_ARTSELECT_ETARTSCHALTER2       6
 #define LS_ARTSELECT_ETARTSCHALTER3       6
 #define LS_ARTSELECT_ETARTSCHALTER4       6
 #define LS_ARTSELECT_ETBESTAND            6
 #define LS_ARTSELECT_DATUMVERFALL         11
 #define LS_ARTSELECT_PRISOART             2
 #define LS_ARTSELECT_PREISEKAPO           11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTSELECT {
		 long    ARTIKEL_NR;
		 char    ARTIKEL_MC[12 + 1];
		 long    PACKGROESSE;
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    ETARTSCHALTER1;
		 long    ETARTSCHALTER2;
		 long    ETARTSCHALTER3;
		 long    ETARTSCHALTER4;
		 long    ETBESTAND;
		 long    DATUMVERFALL;
		 char    PRISOART[1 + 1];
		 double  PREISEKAPO;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTSELECT {
		 long    ARTIKEL_NR;
		 char    ARTIKEL_MC[12 + 1];
		 long    PACKGROESSE;
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 long    ETARTSCHALTER1;
		 long    ETARTSCHALTER2;
		 long    ETARTSCHALTER3;
		 long    ETARTSCHALTER4;
		 long    ETBESTAND;
		 long    DATUMVERFALL;
		 char    PRISOART;
		 double  PREISEKAPO;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTSELECT {
		 short  ARTIKEL_NR;
		 short  ARTIKEL_MC;
		 short  PACKGROESSE;
		 short  DARREICHFORM;
		 short  EINHEIT;
		 short  ARTIKEL_NAME;
		 short  ETARTSCHALTER1;
		 short  ETARTSCHALTER2;
		 short  ETARTSCHALTER3;
		 short  ETARTSCHALTER4;
		 short  ETBESTAND;
		 short  DATUMVERFALL;
		 short  PRISOART;
		 short  PREISEKAPO;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTSELECT {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_MC[12 + 1];
		 char    PACKGROESSE[11];
		 char    DARREICHFORM[3 + 1];
		 char    EINHEIT[9 + 1];
		 char    ARTIKEL_NAME[30 + 1];
		 char    ETARTSCHALTER1[5 + 1];
		 char    ETARTSCHALTER2[5 + 1];
		 char    ETARTSCHALTER3[5 + 1];
		 char    ETARTSCHALTER4[5 + 1];
		 char    ETBESTAND[5 + 1];
		 char    DATUMVERFALL[11];
		 char    PRISOART[1 + 1];
		 char    PREISEKAPO[9 + 2];
       };

 struct O_ARTSELECT {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_MC[12];
		 char    PACKGROESSE[11];
		 char    DARREICHFORM[3];
		 char    EINHEIT[9];
		 char    ARTIKEL_NAME[30];
		 char    ETARTSCHALTER1[5];
		 char    ETARTSCHALTER2[5];
		 char    ETARTSCHALTER3[5];
		 char    ETARTSCHALTER4[5];
		 char    ETBESTAND[5];
		 char    DATUMVERFALL[11];
		 char    PRISOART[1];
		 char    PREISEKAPO[9];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTSELECT_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_D ,    9 ,   2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTSELECT_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   12 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    9 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_D,    9 ,   2 },
 };
#endif

#ifdef TRANSCLASS

 class CARTSELECT
 {
  public:

  ARTSELECT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTSELECT_BES, ARTSELECT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTSELECT_BES, ARTSELECT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTSELECT_BES, ARTSELECT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTSELECT()
  {
   ::buf_default((void *)&s, ARTSELECT_BES, ARTSELECT_ANZ);
  }
 };
#endif

#define ARTSELECT_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR         INTEGER         default 0 NOT NULL,\
		 ARTIKEL_MC         CHAR(12)        default " " NOT NULL,\
		 PACKGROESSE        INTEGER         default 0 NOT NULL,\
		 DARREICHFORM       CHAR(3)         default " " NOT NULL,\
		 EINHEIT            CHAR(9)         default " " NOT NULL,\
		 ARTIKEL_NAME       CHAR(30)        default " " NOT NULL,\
		 ETARTSCHALTER1     INTEGER         default 0 NOT NULL,\
		 ETARTSCHALTER2     INTEGER         default 0 NOT NULL,\
		 ETARTSCHALTER3     INTEGER         default 0 NOT NULL,\
		 ETARTSCHALTER4     INTEGER         default 0 NOT NULL,\
		 ETBESTAND          INTEGER         default 0 NOT NULL,\
		 DATUMVERFALL       INTEGER         default 0 NOT NULL,\
		 PRISOART           CHAR(1)         default " " NOT NULL,\
		 PREISEKAPO         DECIMAL(9,2)    default 0 NOT NULL  ) EXTENT SIZE 40290 LOCK MODE ROW;

#define ARTSELECT_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX I_ARTSELECT_1      on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTSELECT_2      on yyy( ARTIKEL_MC );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTSELECT_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTSELECT_1     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTSELECT_2     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

