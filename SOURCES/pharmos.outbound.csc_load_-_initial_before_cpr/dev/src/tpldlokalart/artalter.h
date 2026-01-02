/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_ARTIKELALTERN_ARTIKEL_NR           11
 #define L_ARTIKELALTERN_ARTIKEL_NR_ALTERN    11
 #define L_ARTIKELALTERN_BEMERKUNGEN          240
 #define L_ARTIKELALTERN_FILIALNR             6


 #define L_ARTIKELALTERN_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTIKELALTERN_ANZ ( sizeof(ARTIKELALTERN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTIKELALTERN sizeof(struct ARTIKELALTERN)


 #define ARTIKELALTERN_H

 #define ARTIKELALTERN_LISTE \
 			ARTIKELALTERN.ARTIKEL_NR, \
 			ARTIKELALTERN.ARTIKEL_NR_ALTERN, \
 			ARTIKELALTERN.BEMERKUNGEN, \
			ARTIKELALTERN_FILIALNR
 #define ARTIKELALTERN_PLISTE \
 			"ARTIKELALTERN.ARTIKEL_NR," \
 			"ARTIKELALTERN.ARTIKEL_NR_ALTERN," \
 			"ARTIKELALTERN.BEMERKUNGEN," \
			"ARTIKELALTERN_FILIALNR "

 #define ARTIKELALTERN_PELISTE \
 			"ARTIKEL_NR," \
 			"ARTIKEL_NR_ALTERN," \
 			"BEMERKUNGEN," \
			"FILIALNR "

 #define ARTIKELALTERNARTIKEL_NR                    0
 #define ARTIKELALTERNARTIKEL_NR_ALTERN             1
 #define ARTIKELALTERNBEMERKUNGEN                   2
 #define ARTIKELALTERNFILIALNR                      3

 #define ARTIKELALTERN_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->ARTIKEL_NR_ALTERN,\
 			:xxx->BEMERKUNGEN,\
 			:xxx->FILIALNR

 #define ARTIKELALTERN_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			ARTIKEL_NR_ALTERN = :xxx->ARTIKEL_NR_ALTERN,\
 			BEMERKUNGEN = :xxx->BEMERKUNGEN,\
 			FILIALNR = :xxx->FILIALNR

 #define LS_ARTIKELALTERN_ARTIKEL_NR           11
 #define LS_ARTIKELALTERN_ARTIKEL_NR_ALTERN    11
 #define LS_ARTIKELALTERN_BEMERKUNGEN          241
 #define LS_ARTIKELALTERN_FILIALNR             7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTIKELALTERN {
		 long    ARTIKEL_NR;
		 long    ARTIKEL_NR_ALTERN;
		 char    BEMERKUNGEN[240 + 1];
		 short   FILIALNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTIKELALTERN {
		 long    ARTIKEL_NR;
		 long    ARTIKEL_NR_ALTERN;
		 char    BEMERKUNGEN[240 + 1];
		 short   FILIALNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTIKELALTERN {
		 short  ARTIKEL_NR;
		 short  ARTIKEL_NR_ALTERN;
		 short  BEMERKUNGEN;
		 short  FILIALNR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTIKELALTERN {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NR_ALTERN[11];
		 char    BEMERKUNGEN[240 + 1];
		 char    FILIALNR[7];
       };

 struct O_ARTIKELALTERN {
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NR_ALTERN[11];
		 char    BEMERKUNGEN[240];
		 char    FILIALNR[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTIKELALTERN_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELALTERN_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_S,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTIKELALTERN
 {
  public:

  ARTIKELALTERN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTIKELALTERN_BES, ARTIKELALTERN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTIKELALTERN_BES, ARTIKELALTERN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTIKELALTERN_BES, ARTIKELALTERN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTIKELALTERN()
  {
   ::buf_default((void *)&s, ARTIKELALTERN_BES, ARTIKELALTERN_ANZ);
  }
 };
#endif

#define ARTIKELALTERN_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR         INTEGER         default 0 NOT NULL,\
		 ARTIKEL_NR_ALTERN  INTEGER         default 0 NOT NULL,\
		 BEMERKUNGEN        VARCHAR(240,0)  default " " NOT NULL,\
		 FILIALNR           SMALLINT        default 0 NOT NULL  ) EXTENT SIZE 9 LOCK MODE ROW;


