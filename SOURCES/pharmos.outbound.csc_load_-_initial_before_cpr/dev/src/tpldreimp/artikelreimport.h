/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_ARTIKELREIMPORT_FILIALNR             6
 #define L_ARTIKELREIMPORT_ARTIKEL_NR           11
 #define L_ARTIKELREIMPORT_ARTIKEL_NR_ALTERN    11
 #define L_ARTIKELREIMPORT_KZUPD                1
 #define L_ARTIKELREIMPORT_KZAKTIVPASSIV        1
 #define L_ARTIKELREIMPORT_REIHENFOLGE          6


 #define L_ARTIKELREIMPORT_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define ARTIKELREIMPORT_ANZ ( sizeof(ARTIKELREIMPORT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_ARTIKELREIMPORT sizeof(struct ARTIKELREIMPORT)


 #define ARTIKELREIMPORT_H

 #define ARTIKELREIMPORT_LISTE \
 			ARTIKELREIMPORT.FILIALNR, \
 			ARTIKELREIMPORT.ARTIKEL_NR, \
 			ARTIKELREIMPORT.ARTIKEL_NR_ALTERN, \
 			ARTIKELREIMPORT.KZUPD, \
			ARTIKELREIMPORT.KZAKTIVPASSIV, \
			ARTIKELREIMPORT.REIHENFOLGE
 #define ARTIKELREIMPORT_PLISTE \
 			"ARTIKELREIMPORT.FILIALNR," \
 			"ARTIKELREIMPORT.ARTIKEL_NR," \
 			"ARTIKELREIMPORT.ARTIKEL_NR_ALTERN," \
 			"ARTIKELREIMPORT.KZUPD," \
			"ARTIKELREIMPORT.KZAKTIVPASSIV," \
			"ARTIKELREIMPORT.REIHENFOLGE "

 #define ARTIKELREIMPORT_PELISTE \
 			"FILIALNR," \
 			"ARTIKEL_NR," \
 			"ARTIKEL_NR_ALTERN," \
 			"KZUPD," \
			"KZAKTIVPASSIV," \
			"REIHENFOLGE "

 #define ARTIKELREIMPORT_UPDLISTE \
 			"FILIALNR=?," \
 			"ARTIKEL_NR=?," \
 			"ARTIKEL_NR_ALTERN=?," \
 			"KZUPD=?," \
			"KZAKTIVPASSIV=?," \
			"REIHENFOLGE=? "

 #define ARTIKELREIMPORTFILIALNR                      0
 #define ARTIKELREIMPORTARTIKEL_NR                    1
 #define ARTIKELREIMPORTARTIKEL_NR_ALTERN             2
 #define ARTIKELREIMPORTKZUPD                         3
 #define ARTIKELREIMPORTKZAKTIVPASSIV                 4
 #define ARTIKELREIMPORTREIHENFOLGE                   5

 #define ARTIKELREIMPORT_ZEIGER(xxx) \
 			:xxx->FILIALNR,\
 			:xxx->ARTIKEL_NR,\
 			:xxx->ARTIKEL_NR_ALTERN,\
 			:xxx->KZUPD,\
 			:xxx->KZAKTIVPASSIV,\
 			:xxx->REIHENFOLGE

 #define ARTIKELREIMPORT_UPDATE(xxx) \
 			FILIALNR = :xxx->FILIALNR,\
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			ARTIKEL_NR_ALTERN = :xxx->ARTIKEL_NR_ALTERN,\
 			KZUPD = :xxx->KZUPD,\
 			KZAKTIVPASSIV = :xxx->KZAKTIVPASSIV,\
 			REIHENFOLGE = :xxx->REIHENFOLGE

 #define LS_ARTIKELREIMPORT_FILIALNR             7
 #define LS_ARTIKELREIMPORT_ARTIKEL_NR           11
 #define LS_ARTIKELREIMPORT_ARTIKEL_NR_ALTERN    11
 #define LS_ARTIKELREIMPORT_KZUPD                2
 #define LS_ARTIKELREIMPORT_KZAKTIVPASSIV        2
 #define LS_ARTIKELREIMPORT_REIHENFOLGE          7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct ARTIKELREIMPORT {
		 short   FILIALNR;
		 long    ARTIKEL_NR;
		 long    ARTIKEL_NR_ALTERN;
		 char    KZUPD[1 + 1];
		 char    KZAKTIVPASSIV[1 + 1];
		 short   REIHENFOLGE;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_ARTIKELREIMPORT {
		 short   FILIALNR;
		 long    ARTIKEL_NR;
		 long    ARTIKEL_NR_ALTERN;
		 char    KZUPD;
		 char    KZAKTIVPASSIV;
		 short   REIHENFOLGE;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_ARTIKELREIMPORT {
		 short  FILIALNR;
		 short  ARTIKEL_NR;
		 short  ARTIKEL_NR_ALTERN;
		 short  KZUPD;
		 short  KZAKTIVPASSIV;
		 short  REIHENFOLGE;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_ARTIKELREIMPORT {
		 char    FILIALNR[7];
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NR_ALTERN[11];
		 char    KZUPD[1 + 1];
		 char    KZAKTIVPASSIV[1 + 1];
		 char    REIHENFOLGE[7];
       };

 struct O_ARTIKELREIMPORT {
		 char    FILIALNR[7];
		 char    ARTIKEL_NR[11];
		 char    ARTIKEL_NR_ALTERN[11];
		 char    KZUPD[1];
		 char    KZAKTIVPASSIV[1];
		 char    REIHENFOLGE[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc ARTIKELREIMPORT_BES [] =
 {
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELREIMPORT_BES [] =
 {
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CARTIKELREIMPORT
 {
  public:

  ARTIKELREIMPORT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTIKELREIMPORT_BES, ARTIKELREIMPORT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTIKELREIMPORT_BES, ARTIKELREIMPORT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTIKELREIMPORT_BES, ARTIKELREIMPORT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTIKELREIMPORT()
  {
   ::buf_default((void *)&s, ARTIKELREIMPORT_BES, ARTIKELREIMPORT_ANZ);
  }
 };
#endif

#define ARTIKELREIMPORT_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 FILIALNR           SMALLINT        default 0 NOT NULL,\
		 ARTIKEL_NR         INTEGER         default 0 NOT NULL,\
		 ARTIKEL_NR_ALTERN  INTEGER         default 0 NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 KZAKTIVPASSIV      CHAR(1)         default " " NOT NULL,\
		 REIHENFOLGE        SMALLINT        default " " NOT NULL  ) EXTENT SIZE 108 LOCK MODE ROW;

#define ARTIKELREIMPORT_CREATE_INDEX(yyy,xxx) \

#define ARTIKELREIMPORT_DELETE_INDEX(xxx) \

