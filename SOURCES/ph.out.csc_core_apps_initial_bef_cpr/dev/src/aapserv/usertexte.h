/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_USERTEXTV_UID                  11
 #define L_USERTEXTV_TEXTART              6
 #define L_USERTEXTV_TEXT                 240


 #define L_USERTEXTV_PKEY 257

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define USERTEXTV_ANZ (int) ( sizeof(USERTEXTV_BES) / sizeof(struct buf_desc) )
#endif
 #define G_USERTEXTV sizeof(struct USERTEXTV)


 #define USERTEXTV_H

 #define USERTEXTV_LISTE \
 			USERTEXTE.UID, \
 			USERTEXTE.TEXTART, \
 			USERTEXTE.TEXT
 #define USERTEXTV_PLISTE \
 			"USERTEXTE.UID," \
 			"USERTEXTE.TEXTART," \
 			"USERTEXTE.TEXT " 

 #define USERTEXTV_PELISTE \
 			"UID," \
 			"TEXTART," \
 			"TEXT " 

 #define USERTEXTV_UPDLISTE \
 			"UID=?," \
 			"TEXTART=?," \
 			"TEXT=? " 

 #define USERTEXTVUID                           0
 #define USERTEXTVTEXTART                       1
 #define USERTEXTVTEXT                          2

 #define USERTEXTV_ZEIGER(xxx) \
 			:xxx->UID,\
 			:xxx->TEXTART,\
 			:xxx->TEXT

 #define USERTEXTV_UPDATE(xxx) \
 			UID = :xxx->UID,\
 			TEXTART = :xxx->TEXTART,\
 			TEXT = :xxx->TEXT

 #define LS_USERTEXTV_UID                  11
 #define LS_USERTEXTV_TEXTART              7
 #define LS_USERTEXTV_TEXT                 241
 #define LS_USERTEXTV_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct USERTEXTV {
		 long    UID;
		 short   TEXTART;
		 char    TEXT[240 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_USERTEXTV {
		 long    UID;
		 short   TEXTART;
		 char    TEXT[240 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_USERTEXTV {
		 short  UID;
		 short  TEXTART;
		 short  TEXT;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_USERTEXTV {
		 char    UID[11];
		 char    TEXTART[7];
		 char    TEXT[240 + 1];
		 char    FETCH_REL[11];
       };

 struct O_USERTEXTV {
		 char    UID[11];
		 char    TEXTART[7];
		 char    TEXT[240];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc USERTEXTV_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc USERTEXTV_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CUSERTEXTV
 {
  public:

  USERTEXTV s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, USERTEXTV_BES, USERTEXTV_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,USERTEXTV_BES, USERTEXTV_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,USERTEXTV_BES, USERTEXTV_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CUSERTEXTV()
  {
   ::buf_default((void *)&s, USERTEXTV_BES, USERTEXTV_ANZ);
  }
 };
#endif

#define USERTEXTV_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 UID INTEGER           ,\
		 TEXTART SMALLINT          ,\
		 TEXT CHAR(240)         ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 9 LOCK MODE ROW;

#define USERTEXTV_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_USERTEXTE_1      on yyy( UID, TEXTART, TEXT );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define USERTEXTV_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_USERTEXTE_1     ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

