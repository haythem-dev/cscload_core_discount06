/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTIKELSEKBEZ_ARTIKEL_MC           12
 #define L_ARTIKELSEKBEZ_ARTIKEL_NR           11
 #define L_ARTIKELSEKBEZ_ARTIKEL_NAME         30
 #define L_ARTIKELSEKBEZ_BEMERKUNGEN          240


 #define L_ARTIKELSEKBEZ_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTIKELSEKBEZ_ANZ ( sizeof(ARTIKELSEKBEZ_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTIKELSEKBEZ sizeof(struct ARTIKELSEKBEZ)


 #define ARTIKELSEKBEZ_H

 #define ARTIKELSEKBEZ_LISTE \
 			ARTIKELSEKBEZ.ARTIKEL_MC, \
 			ARTIKELSEKBEZ.ARTIKEL_NR, \
 			ARTIKELSEKBEZ.ARTIKEL_NAME, \
 			ARTIKELSEKBEZ.BEMERKUNGEN
 #define ARTIKELSEKBEZ_PLISTE \
 			"ARTIKELSEKBEZ.ARTIKEL_MC," \
 			"ARTIKELSEKBEZ.ARTIKEL_NR," \
 			"ARTIKELSEKBEZ.ARTIKEL_NAME," \
 			"ARTIKELSEKBEZ.BEMERKUNGEN " 
 #define ARTIKELSEKBEZ_PELISTE \
 			"ARTIKEL_MC," \
 			"ARTIKEL_NR," \
 			"ARTIKEL_NAME," \
 			"BEMERKUNGEN " 
 #define ARTIKELSEKBEZARTIKEL_MC                    0
 #define ARTIKELSEKBEZARTIKEL_NR                    1
 #define ARTIKELSEKBEZARTIKEL_NAME                  2
 #define ARTIKELSEKBEZBEMERKUNGEN                   3

 #define ARTIKELSEKBEZ_ZEIGER(xxx) \
 			:xxx->ARTIKEL_MC,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->ARTIKEL_NAME,\
 			:xxx->BEMERKUNGEN

 #define ARTIKELSEKBEZ_UPDATE(xxx) \
 			ARTIKEL_MC = :xxx->ARTIKEL_MC,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			ARTIKEL_NAME = :xxx->ARTIKEL_NAME,\
 			BEMERKUNGEN = :xxx->BEMERKUNGEN

 #define LS_ARTIKELSEKBEZ_ARTIKEL_MC           13
 #define LS_ARTIKELSEKBEZ_ARTIKEL_NR           11
 #define LS_ARTIKELSEKBEZ_ARTIKEL_NAME         31
 #define LS_ARTIKELSEKBEZ_BEMERKUNGEN          241

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTIKELSEKBEZ {
		 char    ARTIKEL_MC[12 + 1];
		 long    ARTIKEL_NR;
		 char    ARTIKEL_NAME[30 + 1];
		 char    BEMERKUNGEN[240 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTIKELSEKBEZ {
		 char    ARTIKEL_MC[12 + 1];
		 long    ARTIKEL_NR;
		 char    ARTIKEL_NAME[30 + 1];
		 char    BEMERKUNGEN[240 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTIKELSEKBEZ {
		 short  ARTIKEL_MC;
		 short  ARTIKEL_NR;
		 short  ARTIKEL_NAME;
		 short  BEMERKUNGEN;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTIKELSEKBEZ {
		 char    ARTIKEL_MC[12 + 1];
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NAME[30 + 1];
		 char    BEMERKUNGEN[240 + 1];
       };

 struct O_ARTIKELSEKBEZ {
		 char    ARTIKEL_MC[12];
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NAME[30];
		 char    BEMERKUNGEN[240];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTIKELSEKBEZ_BES [] =
 {
	 { TYP_C ,   12 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,  240 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELSEKBEZ_BES [] =
 {
	 { TYP_C,   12 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,  240 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTIKELSEKBEZ
 {
  public:

  ARTIKELSEKBEZ s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTIKELSEKBEZ_BES, ARTIKELSEKBEZ_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTIKELSEKBEZ_BES, ARTIKELSEKBEZ_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTIKELSEKBEZ_BES, ARTIKELSEKBEZ_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTIKELSEKBEZ()
  {
   ::buf_default((void *)&s, ARTIKELSEKBEZ_BES, ARTIKELSEKBEZ_ANZ);
  }
 };
#endif

#define ARTIKELSEKBEZ_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_MC         CHAR(12)        default " " NOT NULL,\
		 ARTIKEL_NR         INTEGER         default 0 NOT NULL,\
		 ARTIKEL_NAME       CHAR(30)        default " " NOT NULL,\
		 BEMERKUNGEN        VARCHAR(240,0)  default " " NOT NULL  ) EXTENT SIZE 15920 LOCK MODE ROW;

#define ARTIKELSEKBEZ_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE INDEX ARTIKELSEKBEZX     on yyy( ARTIKEL_MC, ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTIKELSEKBEZ_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX ARTIKELSEKBEZX    ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

