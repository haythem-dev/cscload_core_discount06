/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_TOURINHALT_KDAUFTRAGNR          11
 #define L_TOURINHALT_KDAUFTRAGSTAT        16
 #define L_TOURINHALT_IDFNR                11
 #define L_TOURINHALT_TOURID               6
 #define L_TOURINHALT_KDAUFTRAGART         2
 #define L_TOURINHALT_ANZBTM               11
 #define L_TOURINHALT_ANZCONTAINER         11
 #define L_TOURINHALT_ANZBEHAELTWECHSEL    11
 #define L_TOURINHALT_ANZBEHAELT           11
 #define L_TOURINHALT_ANZSONDERWANNE       11
 #define L_TOURINHALT_NAMEAPO              40
 #define L_TOURINHALT_ORT                  30
 #define L_TOURINHALT_REIHENFOLGENR        11
 #define L_TOURINHALT_TOURIDALT            6
 #define L_TOURINHALT_TELKURZWAHL          4


 #define L_TOURINHALT_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define TOURINHALT_ANZ (int) ( sizeof(TOURINHALT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_TOURINHALT sizeof(struct TOURINHALT)


 #define TOURINHALT_H

 #define TOURINHALT_LISTE \
 			KDAUFTRAG.KDAUFTRAGNR, \
 			KDAUFTRAG.KDAUFTRAGSTAT, \
 			KDAUFTRAG.IDFNR, \
 			KDAUFTRAG.TOURID, \
 			KDAUFTRAG.KDAUFTRAGART, \
 			KDAUFTRAG.ANZBTM, \
 			KDAUFTRAG.ANZCONTAINER, \
 			KDAUFTRAG.ANZBEHAELTWECHSEL, \
 			KDAUFTRAG.ANZBEHAELT, \
 			KDAUFTRAG.ANZSONDERWANNE, \
 			KUNDE.NAMEAPO, \
 			KUNDE.ORT, \
 			TOURPLANTAG.REIHENFOLGENR, \
 			KDAUFTRAG.TOURIDALT, \
			KUNDE.TELKURZWAHL
 #define TOURINHALT_PLISTE \
 			"KDAUFTRAG.KDAUFTRAGNR," \
 			"KDAUFTRAG.KDAUFTRAGSTAT," \
 			"KDAUFTRAG.IDFNR," \
 			"KDAUFTRAG.TOURID," \
 			"KDAUFTRAG.KDAUFTRAGART," \
 			"KDAUFTRAG.ANZBTM," \
 			"KDAUFTRAG.ANZCONTAINER," \
 			"KDAUFTRAG.ANZBEHAELTWECHSEL," \
 			"KDAUFTRAG.ANZBEHAELT," \
 			"KDAUFTRAG.ANZSONDERWANNE," \
 			"KUNDE.NAMEAPO," \
 			"KUNDE.ORT," \
 			"TOURPLANTAG.REIHENFOLGENR," \
 			"KDAUFTRAG.TOURIDALT," \
			"KUNDE.TELKURZWAHL "

 #define TOURINHALT_PELISTE \
 			"KDAUFTRAGNR," \
 			"KDAUFTRAGSTAT," \
 			"IDFNR," \
 			"TOURID," \
 			"KDAUFTRAGART," \
 			"ANZBTM," \
 			"ANZCONTAINER," \
 			"ANZBEHAELTWECHSEL," \
 			"ANZBEHAELT," \
 			"ANZSONDERWANNE," \
 			"NAMEAPO," \
 			"ORT," \
 			"REIHENFOLGENR," \
 			"TOURIDALT," \
			"TELKURZWAHL "

 #define TOURINHALT_UPDLISTE \
 			"KDAUFTRAGNR=?," \
 			"KDAUFTRAGSTAT=?," \
 			"IDFNR=?," \
 			"TOURID=?," \
 			"KDAUFTRAGART=?," \
 			"ANZBTM=?," \
 			"ANZCONTAINER=?," \
 			"ANZBEHAELTWECHSEL=?," \
 			"ANZBEHAELT=?," \
 			"ANZSONDERWANNE=?," \
 			"NAMEAPO=?," \
 			"ORT=?," \
 			"REIHENFOLGENR=?," \
 			"TOURIDALT=?," \
			"TELKURZWAHL=? "

 #define TOURINHALTKDAUFTRAGNR                   0
 #define TOURINHALTKDAUFTRAGSTAT                 1
 #define TOURINHALTIDFNR                         2
 #define TOURINHALTTOURID                        3
 #define TOURINHALTKDAUFTRAGART                  4
 #define TOURINHALTANZBTM                        5
 #define TOURINHALTANZCONTAINER                  6
 #define TOURINHALTANZBEHAELTWECHSEL             7
 #define TOURINHALTANZBEHAELT                    8
 #define TOURINHALTANZSONDERWANNE                9
 #define TOURINHALTNAMEAPO                       10
 #define TOURINHALTORT                           11
 #define TOURINHALTREIHENFOLGENR                 12
 #define TOURINHALTTOURIDALT                     13
 #define TOURINHALTTELKURZWAHL                   14

 #define TOURINHALT_ZEIGER(xxx) \
 			:xxx->KDAUFTRAGNR,\
 			:xxx->KDAUFTRAGSTAT,\
 			:xxx->IDFNR,\
 			:xxx->TOURID,\
 			:xxx->KDAUFTRAGART,\
 			:xxx->ANZBTM,\
 			:xxx->ANZCONTAINER,\
 			:xxx->ANZBEHAELTWECHSEL,\
 			:xxx->ANZBEHAELT,\
 			:xxx->ANZSONDERWANNE,\
 			:xxx->NAMEAPO,\
 			:xxx->ORT,\
 			:xxx->REIHENFOLGENR,\
 			:xxx->TOURIDALT,\
 			:xxx->TELKURZWAHL

 #define TOURINHALT_UPDATE(xxx) \
 			KDAUFTRAGNR = :xxx->KDAUFTRAGNR,\
 			KDAUFTRAGSTAT = :xxx->KDAUFTRAGSTAT,\
 			IDFNR = :xxx->IDFNR,\
 			TOURID = :xxx->TOURID,\
 			KDAUFTRAGART = :xxx->KDAUFTRAGART,\
 			ANZBTM = :xxx->ANZBTM,\
 			ANZCONTAINER = :xxx->ANZCONTAINER,\
 			ANZBEHAELTWECHSEL = :xxx->ANZBEHAELTWECHSEL,\
 			ANZBEHAELT = :xxx->ANZBEHAELT,\
 			ANZSONDERWANNE = :xxx->ANZSONDERWANNE,\
 			NAMEAPO = :xxx->NAMEAPO,\
 			ORT = :xxx->ORT,\
 			REIHENFOLGENR = :xxx->REIHENFOLGENR,\
 			TOURIDALT = :xxx->TOURIDALT,\
 			TELKURZWAHL = :xxx->TELKURZWAHL

 #define LS_TOURINHALT_KDAUFTRAGNR          11
 #define LS_TOURINHALT_KDAUFTRAGSTAT        17
 #define LS_TOURINHALT_IDFNR                11
 #define LS_TOURINHALT_TOURID               7
 #define LS_TOURINHALT_KDAUFTRAGART         3
 #define LS_TOURINHALT_ANZBTM               11
 #define LS_TOURINHALT_ANZCONTAINER         11
 #define LS_TOURINHALT_ANZBEHAELTWECHSEL    11
 #define LS_TOURINHALT_ANZBEHAELT           11
 #define LS_TOURINHALT_ANZSONDERWANNE       11
 #define LS_TOURINHALT_NAMEAPO              41
 #define LS_TOURINHALT_ORT                  31
 #define LS_TOURINHALT_REIHENFOLGENR        11
 #define LS_TOURINHALT_TOURIDALT            7
 #define LS_TOURINHALT_TELKURZWAHL          5
 #define LS_TOURINHALT_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct TOURINHALT {
		 long    KDAUFTRAGNR;
		 char    KDAUFTRAGSTAT[16 + 1];
		 long    IDFNR;
		 char    TOURID[6 + 1];
		 char    KDAUFTRAGART[2 + 1];
		 long    ANZBTM;
		 long    ANZCONTAINER;
		 long    ANZBEHAELTWECHSEL;
		 long    ANZBEHAELT;
		 long    ANZSONDERWANNE;
		 char    NAMEAPO[40 + 1];
		 char    ORT[30 + 1];
		 long    REIHENFOLGENR;
		 char    TOURIDALT[6 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_TOURINHALT {
		 long    KDAUFTRAGNR;
		 char    KDAUFTRAGSTAT[16 + 1];
		 long    IDFNR;
		 char    TOURID[6 + 1];
		 char    KDAUFTRAGART[2 + 1];
		 long    ANZBTM;
		 long    ANZCONTAINER;
		 long    ANZBEHAELTWECHSEL;
		 long    ANZBEHAELT;
		 long    ANZSONDERWANNE;
		 char    NAMEAPO[40 + 1];
		 char    ORT[30 + 1];
		 long    REIHENFOLGENR;
		 char    TOURIDALT[6 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_TOURINHALT {
		 short  KDAUFTRAGNR;
		 short  KDAUFTRAGSTAT;
		 short  IDFNR;
		 short  TOURID;
		 short  KDAUFTRAGART;
		 short  ANZBTM;
		 short  ANZCONTAINER;
		 short  ANZBEHAELTWECHSEL;
		 short  ANZBEHAELT;
		 short  ANZSONDERWANNE;
		 short  NAMEAPO;
		 short  ORT;
		 short  REIHENFOLGENR;
		 short  TOURIDALT;
		 short  TELKURZWAHL;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_TOURINHALT {
		 char    KDAUFTRAGNR[11];
		 char    KDAUFTRAGSTAT[16 + 1];
		 char    IDFNR[11];
		 char    TOURID[6 + 1];
		 char    KDAUFTRAGART[2 + 1];
		 char    ANZBTM[11];
		 char    ANZCONTAINER[11];
		 char    ANZBEHAELTWECHSEL[11];
		 char    ANZBEHAELT[11];
		 char    ANZSONDERWANNE[11];
		 char    NAMEAPO[40 + 1];
		 char    ORT[30 + 1];
		 char    REIHENFOLGENR[11];
		 char    TOURIDALT[6 + 1];
		 char    TELKURZWAHL[4 + 1];
		 char    FETCH_REL[11];
       };

 struct O_TOURINHALT {
		 char    KDAUFTRAGNR[11];
		 char    KDAUFTRAGSTAT[16];
		 char    IDFNR[11];
		 char    TOURID[6];
		 char    KDAUFTRAGART[2];
		 char    ANZBTM[11];
		 char    ANZCONTAINER[11];
		 char    ANZBEHAELTWECHSEL[11];
		 char    ANZBEHAELT[11];
		 char    ANZSONDERWANNE[11];
		 char    NAMEAPO[40];
		 char    ORT[30];
		 char    REIHENFOLGENR[11];
		 char    TOURIDALT[6];
		 char    TELKURZWAHL[4];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc TOURINHALT_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TOURINHALT_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   16 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CTOURINHALT
 {
  public:

  TOURINHALT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, TOURINHALT_BES, TOURINHALT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,TOURINHALT_BES, TOURINHALT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,TOURINHALT_BES, TOURINHALT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CTOURINHALT()
  {
   ::buf_default((void *)&s, TOURINHALT_BES, TOURINHALT_ANZ);
  }
 };
#endif

#define TOURINHALT_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 KDAUFTRAGNR INTEGER           ,\
		 KDAUFTRAGSTAT CHAR(16)          ,\
		 IDFNR INTEGER           ,\
		 TOURID CHAR(6)           ,\
		 KDAUFTRAGART CHAR(2)           ,\
		 ANZBTM INTEGER           ,\
		 ANZCONTAINER INTEGER           ,\
		 ANZBEHAELTWECHSEL INTEGER           ,\
		 ANZBEHAELT INTEGER           ,\
		 ANZSONDERWANNE INTEGER           ,\
		 NAMEAPO CHAR(40)          ,\
		 ORT CHAR(30)          ,\
		 REIHENFOLGENR INTEGER           ,\
		 TOURIDALT CHAR(6)           ,\
		 TELKURZWAHL CHAR(4)           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 1094 LOCK MODE ROW;

#define TOURINHALT_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KDAUFTRAGX         on yyy( KDAUFTRAGNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_303    on yyy( KDAUFTRAGSTAT );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KDAUFTRAG_304    on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX KDAUFTRAGTOURX     on yyy( TOURID );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define TOURINHALT_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KDAUFTRAGX        ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAG_303   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KDAUFTRAG_304   ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KDAUFTRAGTOURX    ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_TOURUEBERS_TOURID               6
 #define L_TOURUEBERS_TOURSTAT             1
 #define L_TOURUEBERS_DRUCKSTAT            1
 #define L_TOURUEBERS_VORABSCHEINDRUCKEN   1
 #define L_TOURUEBERS_FAHRTZEIT            11
 #define L_TOURUEBERS_TOURSTRECKE          6
 #define L_TOURUEBERS_BEZEICHNUNG          30
 #define L_TOURUEBERS_DRUCKFACHNR          6
 #define L_TOURUEBERS_ANZ_WANNEN           11
 #define L_TOURUEBERS_ANZ_ERFASST          11
 #define L_TOURUEBERS_ANZ_FAKTUR           11
 #define L_TOURUEBERS_ANZ_KND_SOLL         11
 #define L_TOURUEBERS_ANZ_KND_IST          11


 #define L_TOURUEBERS_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define TOURUEBERS_ANZ (int) ( sizeof(TOURUEBERS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_TOURUEBERS sizeof(struct TOURUEBERS)


 #define TOURUEBERS_H

 #define TOURUEBERS_LISTE \
 			TOUR.TOURID, \
 			TOUR.TOURSTAT, \
 			TOUR.DRUCKSTAT, \
 			TOUR.VORABSCHEINDRUCKEN, \
 			TOUR.FAHRTZEIT, \
 			TOUR.TOURSTRECKE, \
 			TOUR.BEZEICHNUNG, \
 			TOUR.DRUCKFACHNR, \
 			AADUMMY.ANZ_WANNEN, \
 			AADUMMY.ANZ_ERFASST, \
 			AADUMMY.ANZ_FAKTUR, \
 			AADUMMY.ANZ_KND_SOLL, \
 			AADUMMY.ANZ_KND_IST
 #define TOURUEBERS_PLISTE \
 			"TOUR.TOURID," \
 			"TOUR.TOURSTAT," \
 			"TOUR.DRUCKSTAT," \
 			"TOUR.VORABSCHEINDRUCKEN," \
 			"TOUR.FAHRTZEIT," \
 			"TOUR.TOURSTRECKE," \
 			"TOUR.BEZEICHNUNG," \
 			"TOUR.DRUCKFACHNR," \
 			"AADUMMY.ANZ_WANNEN," \
 			"AADUMMY.ANZ_ERFASST," \
 			"AADUMMY.ANZ_FAKTUR," \
 			"AADUMMY.ANZ_KND_SOLL," \
 			"AADUMMY.ANZ_KND_IST " 

 #define TOURUEBERS_PELISTE \
 			"TOURID," \
 			"TOURSTAT," \
 			"DRUCKSTAT," \
 			"VORABSCHEINDRUCKEN," \
 			"FAHRTZEIT," \
 			"TOURSTRECKE," \
 			"BEZEICHNUNG," \
 			"DRUCKFACHNR," \
 			"ANZ_WANNEN," \
 			"ANZ_ERFASST," \
 			"ANZ_FAKTUR," \
 			"ANZ_KND_SOLL," \
 			"ANZ_KND_IST " 

 #define TOURUEBERS_UPDLISTE \
 			"TOURID=?," \
 			"TOURSTAT=?," \
 			"DRUCKSTAT=?," \
 			"VORABSCHEINDRUCKEN=?," \
 			"FAHRTZEIT=?," \
 			"TOURSTRECKE=?," \
 			"BEZEICHNUNG=?," \
 			"DRUCKFACHNR=?," \
 			"ANZ_WANNEN=?," \
 			"ANZ_ERFASST=?," \
 			"ANZ_FAKTUR=?," \
 			"ANZ_KND_SOLL=?," \
 			"ANZ_KND_IST=? " 

 #define TOURUEBERSTOURID                        0
 #define TOURUEBERSTOURSTAT                      1
 #define TOURUEBERSDRUCKSTAT                     2
 #define TOURUEBERSVORABSCHEINDRUCKEN            3
 #define TOURUEBERSFAHRTZEIT                     4
 #define TOURUEBERSTOURSTRECKE                   5
 #define TOURUEBERSBEZEICHNUNG                   6
 #define TOURUEBERSDRUCKFACHNR                   7
 #define TOURUEBERSANZ_WANNEN                    8
 #define TOURUEBERSANZ_ERFASST                   9
 #define TOURUEBERSANZ_FAKTUR                    10
 #define TOURUEBERSANZ_KND_SOLL                  11
 #define TOURUEBERSANZ_KND_IST                   12

 #define TOURUEBERS_ZEIGER(xxx) \
 			:xxx->TOURID,\
 			:xxx->TOURSTAT,\
 			:xxx->DRUCKSTAT,\
 			:xxx->VORABSCHEINDRUCKEN,\
 			:xxx->FAHRTZEIT,\
 			:xxx->TOURSTRECKE,\
 			:xxx->BEZEICHNUNG,\
 			:xxx->DRUCKFACHNR,\
 			:xxx->ANZ_WANNEN,\
 			:xxx->ANZ_ERFASST,\
 			:xxx->ANZ_FAKTUR,\
 			:xxx->ANZ_KND_SOLL,\
 			:xxx->ANZ_KND_IST

 #define TOURUEBERS_UPDATE(xxx) \
 			TOURID = :xxx->TOURID,\
 			TOURSTAT = :xxx->TOURSTAT,\
 			DRUCKSTAT = :xxx->DRUCKSTAT,\
 			VORABSCHEINDRUCKEN = :xxx->VORABSCHEINDRUCKEN,\
 			FAHRTZEIT = :xxx->FAHRTZEIT,\
 			TOURSTRECKE = :xxx->TOURSTRECKE,\
 			BEZEICHNUNG = :xxx->BEZEICHNUNG,\
 			DRUCKFACHNR = :xxx->DRUCKFACHNR,\
 			ANZ_WANNEN = :xxx->ANZ_WANNEN,\
 			ANZ_ERFASST = :xxx->ANZ_ERFASST,\
 			ANZ_FAKTUR = :xxx->ANZ_FAKTUR,\
 			ANZ_KND_SOLL = :xxx->ANZ_KND_SOLL,\
 			ANZ_KND_IST = :xxx->ANZ_KND_IST

 #define LS_TOURUEBERS_TOURID               7
 #define LS_TOURUEBERS_TOURSTAT             2
 #define LS_TOURUEBERS_DRUCKSTAT            2
 #define LS_TOURUEBERS_VORABSCHEINDRUCKEN   2
 #define LS_TOURUEBERS_FAHRTZEIT            11
 #define LS_TOURUEBERS_TOURSTRECKE          7
 #define LS_TOURUEBERS_BEZEICHNUNG          31
 #define LS_TOURUEBERS_DRUCKFACHNR          7
 #define LS_TOURUEBERS_ANZ_WANNEN           11
 #define LS_TOURUEBERS_ANZ_ERFASST          11
 #define LS_TOURUEBERS_ANZ_FAKTUR           11
 #define LS_TOURUEBERS_ANZ_KND_SOLL         11
 #define LS_TOURUEBERS_ANZ_KND_IST          11
 #define LS_TOURUEBERS_FETCH_REL            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct TOURUEBERS {
		 char    TOURID[6 + 1];
		 char    TOURSTAT[1 + 1];
		 char    DRUCKSTAT[1 + 1];
		 char    VORABSCHEINDRUCKEN[1 + 1];
		 long    FAHRTZEIT;
		 short   TOURSTRECKE;
		 char    BEZEICHNUNG[30 + 1];
		 short   DRUCKFACHNR;
		 long    ANZ_WANNEN;
		 long    ANZ_ERFASST;
		 long    ANZ_FAKTUR;
		 long    ANZ_KND_SOLL;
		 long    ANZ_KND_IST;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_TOURUEBERS {
		 char    TOURID[6 + 1];
		 char    TOURSTAT;
		 char    DRUCKSTAT;
		 char    VORABSCHEINDRUCKEN;
		 long    FAHRTZEIT;
		 short   TOURSTRECKE;
		 char    BEZEICHNUNG[30 + 1];
		 short   DRUCKFACHNR;
		 long    ANZ_WANNEN;
		 long    ANZ_ERFASST;
		 long    ANZ_FAKTUR;
		 long    ANZ_KND_SOLL;
		 long    ANZ_KND_IST;
		 long    FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_TOURUEBERS {
		 short  TOURID;
		 short  TOURSTAT;
		 short  DRUCKSTAT;
		 short  VORABSCHEINDRUCKEN;
		 short  FAHRTZEIT;
		 short  TOURSTRECKE;
		 short  BEZEICHNUNG;
		 short  DRUCKFACHNR;
		 short  ANZ_WANNEN;
		 short  ANZ_ERFASST;
		 short  ANZ_FAKTUR;
		 short  ANZ_KND_SOLL;
		 short  ANZ_KND_IST;
		 short  FETCH_REL;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_TOURUEBERS {
		 char    TOURID[6 + 1];
		 char    TOURSTAT[1 + 1];
		 char    DRUCKSTAT[1 + 1];
		 char    VORABSCHEINDRUCKEN[1 + 1];
		 char    FAHRTZEIT[11];
		 char    TOURSTRECKE[7];
		 char    BEZEICHNUNG[30 + 1];
		 char    DRUCKFACHNR[7];
		 char    ANZ_WANNEN[11];
		 char    ANZ_ERFASST[11];
		 char    ANZ_FAKTUR[11];
		 char    ANZ_KND_SOLL[11];
		 char    ANZ_KND_IST[11];
		 char    FETCH_REL[11];
       };

 struct O_TOURUEBERS {
		 char    TOURID[6];
		 char    TOURSTAT[1];
		 char    DRUCKSTAT[1];
		 char    VORABSCHEINDRUCKEN[1];
		 char    FAHRTZEIT[11];
		 char    TOURSTRECKE[7];
		 char    BEZEICHNUNG[30];
		 char    DRUCKFACHNR[7];
		 char    ANZ_WANNEN[11];
		 char    ANZ_ERFASST[11];
		 char    ANZ_FAKTUR[11];
		 char    ANZ_KND_SOLL[11];
		 char    ANZ_KND_IST[11];
		 char    FETCH_REL[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc TOURUEBERS_BES [] =
 {
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TOURUEBERS_BES [] =
 {
	 { TYP_C,    6 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CTOURUEBERS
 {
  public:

  TOURUEBERS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, TOURUEBERS_BES, TOURUEBERS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,TOURUEBERS_BES, TOURUEBERS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,TOURUEBERS_BES, TOURUEBERS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CTOURUEBERS()
  {
   ::buf_default((void *)&s, TOURUEBERS_BES, TOURUEBERS_ANZ);
  }
 };
#endif

#define TOURUEBERS_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 TOURID CHAR(6)           ,\
		 TOURSTAT CHAR(1)           ,\
		 DRUCKSTAT CHAR(1)           ,\
		 VORABSCHEINDRUCKEN CHAR(1)           ,\
		 FAHRTZEIT INTEGER           ,\
		 TOURSTRECKE SMALLINT          ,\
		 BEZEICHNUNG CHAR(30)          ,\
		 DRUCKFACHNR SMALLINT          ,\
		 ANZ_WANNEN INTEGER           ,\
		 ANZ_ERFASST INTEGER           ,\
		 ANZ_FAKTUR INTEGER           ,\
		 ANZ_KND_SOLL INTEGER           ,\
		 ANZ_KND_IST INTEGER           ,\
		 FETCH_REL INTEGER  ) EXTENT SIZE 358 LOCK MODE ROW;

#define TOURUEBERS_CREATE_INDEX(yyy,xxx) \

#define TOURUEBERS_DELETE_INDEX(xxx) \

