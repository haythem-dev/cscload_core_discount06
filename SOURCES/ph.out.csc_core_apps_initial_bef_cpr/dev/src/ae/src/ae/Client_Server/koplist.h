/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KOPLIST_SATZNR               11
 #define L_KOPLIST_BEZEICHNUNG          35
 #define L_KOPLIST_ALTERNATIV_NAME      100
 #define L_KOPLIST_DISPO_HINWEIS        240
 #define L_KOPLIST_BEMERKUNG            240
 #define L_KOPLIST_PZN                  11


 #define L_KOPLIST_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KOPLIST_ANZ ( sizeof(KOPLIST_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KOPLIST sizeof(struct KOPLIST)


 #define KOPLIST_H

 #define KOPLIST_LISTE \
 			TELLIST.SATZNR, \
 			TELLIST.BEZEICHNUNG, \
 			TELLIST.ALTERNATIV_NAME, \
 			TELLIST.DISPO_HINWEIS, \
 			TELLIST.BEMERKUNG, \
 			TELLIST.PZN
 #define KOPLIST_PLISTE \
 			"TELLIST.SATZNR," \
 			"TELLIST.BEZEICHNUNG," \
 			"TELLIST.ALTERNATIV_NAME," \
 			"TELLIST.DISPO_HINWEIS," \
 			"TELLIST.BEMERKUNG," \
 			"TELLIST.PZN " 

 #define KOPLIST_PELISTE \
 			"SATZNR," \
 			"BEZEICHNUNG," \
 			"ALTERNATIV_NAME," \
 			"DISPO_HINWEIS," \
 			"BEMERKUNG," \
 			"PZN " 

 #define KOPLIST_UPDLISTE \
 			"SATZNR=?," \
 			"BEZEICHNUNG=?," \
 			"ALTERNATIV_NAME=?," \
 			"DISPO_HINWEIS=?," \
 			"BEMERKUNG=?," \
 			"PZN=? " 

 #define KOPLISTSATZNR                        0
 #define KOPLISTBEZEICHNUNG                   1
 #define KOPLISTALTERNATIV_NAME               2
 #define KOPLISTDISPO_HINWEIS                 3
 #define KOPLISTBEMERKUNG                     4
 #define KOPLISTPZN                           5

 #define KOPLIST_ZEIGER(xxx) \
 			:xxx->SATZNR,\
 			:xxx->BEZEICHNUNG,\
 			:xxx->ALTERNATIV_NAME,\
 			:xxx->DISPO_HINWEIS,\
 			:xxx->BEMERKUNG,\
 			:xxx->PZN

 #define KOPLIST_UPDATE(xxx) \
 			SATZNR = :xxx->SATZNR,\
 			BEZEICHNUNG = :xxx->BEZEICHNUNG,\
 			ALTERNATIV_NAME = :xxx->ALTERNATIV_NAME,\
 			DISPO_HINWEIS = :xxx->DISPO_HINWEIS,\
 			BEMERKUNG = :xxx->BEMERKUNG,\
 			PZN = :xxx->PZN

 #define LS_KOPLIST_SATZNR               11
 #define LS_KOPLIST_BEZEICHNUNG          36
 #define LS_KOPLIST_ALTERNATIV_NAME      101
 #define LS_KOPLIST_DISPO_HINWEIS        241
 #define LS_KOPLIST_BEMERKUNG            241
 #define LS_KOPLIST_PZN                  11
 #define LS_KOPLIST_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KOPLIST {
		 long    SATZNR;
		 char    BEZEICHNUNG[35 + 1];
		 char    ALTERNATIV_NAME[100 + 1];
		 char    DISPO_HINWEIS[240 + 1];
		 char    BEMERKUNG[240 + 1];
		 long    PZN;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KOPLIST {
		 long    SATZNR;
		 char    BEZEICHNUNG[35 + 1];
		 char    ALTERNATIV_NAME[100 + 1];
		 char    DISPO_HINWEIS[240 + 1];
		 char    BEMERKUNG[240 + 1];
		 long    PZN;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KOPLIST {
		 short  SATZNR;
		 short  BEZEICHNUNG;
		 short  ALTERNATIV_NAME;
		 short  DISPO_HINWEIS;
		 short  BEMERKUNG;
		 short  PZN;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KOPLIST {
		 char    SATZNR[11];
		 char    BEZEICHNUNG[35 + 1];
		 char    ALTERNATIV_NAME[100 + 1];
		 char    DISPO_HINWEIS[240 + 1];
		 char    BEMERKUNG[240 + 1];
		 char    PZN[11];
		 char    FETCH_REL[11];
       };

 struct O_KOPLIST {
		 char    SATZNR[11];
		 char    BEZEICHNUNG[35];
		 char    ALTERNATIV_NAME[100];
		 char    DISPO_HINWEIS[240];
		 char    BEMERKUNG[240];
		 char    PZN[11];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KOPLIST_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   35 ,   0 },
	 { TYP_C ,  100 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KOPLIST_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   35 ,   0 },
	 { TYP_C,  100 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKOPLIST
 {
  public:

  KOPLIST s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KOPLIST_BES, KOPLIST_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KOPLIST_BES, KOPLIST_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KOPLIST_BES, KOPLIST_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKOPLIST()
  {
   ::buf_default((void *)&s, KOPLIST_BES, KOPLIST_ANZ);
  }
 };
#endif

#define KOPLIST_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 SATZNR INTEGER           ,\
		 BEZEICHNUNG CHAR(35)          ,\
		 ALTERNATIV_NAME CHAR(100)         ,\
		 DISPO_HINWEIS CHAR(240)         ,\
		 BEMERKUNG CHAR(240)         ,\
		 PZN INTEGER           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 14676 LOCK MODE ROW;

#define KOPLIST_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_TELLIST_1        on yyy( SATZNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_TELLIST_2        on yyy( BEZEICHNUNG );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KOPLIST_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_TELLIST_1       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_TELLIST_2       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

