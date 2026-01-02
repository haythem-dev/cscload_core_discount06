/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTIKELNUMMERN_PZN                  11
 #define L_ARTIKELNUMMERN_EAN                  13
 #define L_ARTIKELNUMMERN_ARTIKEL_NR           11


 #define L_ARTIKELNUMMERN_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTIKELNUMMERN_ANZ ( sizeof(ARTIKELNUMMERN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTIKELNUMMERN sizeof(struct ARTIKELNUMMERN)


 #define ARTIKELNUMMERN_H

 #define ARTIKELNUMMERN_LISTE \
 			ARTIKELNUMMERN.PZN, \
 			ARTIKELNUMMERN.EAN, \
 			ARTIKELNUMMERN.ARTIKEL_NR
 #define ARTIKELNUMMERN_PLISTE \
 			"ARTIKELNUMMERN.PZN," \
 			"ARTIKELNUMMERN.EAN," \
 			"ARTIKELNUMMERN.ARTIKEL_NR " 

 #define ARTIKELNUMMERN_PELISTE \
 			"PZN," \
 			"EAN," \
 			"ARTIKEL_NR " 

 #define ARTIKELNUMMERN_UPDLISTE \
 			"PZN=?," \
 			"EAN=?," \
 			"ARTIKEL_NR=? " 

 #define ARTIKELNUMMERNPZN                           0
 #define ARTIKELNUMMERNEAN                           1
 #define ARTIKELNUMMERNARTIKEL_NR                    2

 #define ARTIKELNUMMERN_ZEIGER(xxx) \
 			:xxx->PZN,\
 			:xxx->EAN,\
 			:xxx->ARTIKEL_NR

 #define ARTIKELNUMMERN_UPDATE(xxx) \
 			PZN = :xxx->PZN,\
 			EAN = :xxx->EAN,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR

 #define LS_ARTIKELNUMMERN_PZN                  11
 #define LS_ARTIKELNUMMERN_EAN                  14
 #define LS_ARTIKELNUMMERN_ARTIKEL_NR           11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTIKELNUMMERN {
		 long    PZN;
		 char    EAN[13 + 1];
		 long    ARTIKEL_NR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTIKELNUMMERN {
		 long    PZN;
		 char    EAN[13 + 1];
		 long    ARTIKEL_NR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTIKELNUMMERN {
		 short  PZN;
		 short  EAN;
		 short  ARTIKEL_NR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTIKELNUMMERN {
		 char    PZN[11];
		 char    EAN[13 + 1];
		 char    ARTIKEL_NR[11];
       };

 struct O_ARTIKELNUMMERN {
		 char    PZN[11];
		 char    EAN[13];
		 char    ARTIKEL_NR[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTIKELNUMMERN_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELNUMMERN_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTIKELNUMMERN
 {
  public:

  ARTIKELNUMMERN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTIKELNUMMERN_BES, ARTIKELNUMMERN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTIKELNUMMERN_BES, ARTIKELNUMMERN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTIKELNUMMERN_BES, ARTIKELNUMMERN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTIKELNUMMERN()
  {
   ::buf_default((void *)&s, ARTIKELNUMMERN_BES, ARTIKELNUMMERN_ANZ);
  }
 };
#endif

#define ARTIKELNUMMERN_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 PZN                INTEGER         default 0 NOT NULL,\
		 EAN                CHAR(13)        default " " NOT NULL,\
		 ARTIKEL_NR         INTEGER         default 0 NOT NULL  ) EXTENT SIZE 30484 LOCK MODE ROW;

#define ARTIKELNUMMERN_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_ARTIKELNUMMERN_1 on yyy( PZN );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELNUMMERN_2 on yyy( EAN );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_ARTIKELNUMMERN_3 on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define ARTIKELNUMMERN_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_ARTIKELNUMMERN_1;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELNUMMERN_2;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_ARTIKELNUMMERN_3;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

