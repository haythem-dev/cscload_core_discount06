/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_TOUR_DATUMKOMMI           11
 #define L_TOUR_TOURID               6
 #define L_TOUR_ZEITKOENDE           11
 #define L_TOUR_DATUMVERSAND         11
 #define L_TOUR_ZEITVERSAND          11
 #define L_TOUR_BAHNHOFVERSAND       6
 #define L_TOUR_TOURSTAT             1
 #define L_TOUR_DRUCKSTAT            1
 #define L_TOUR_VORABSCHEINDRUCKEN   1
 #define L_TOUR_TOURMITVERBUND       1
 #define L_TOUR_FAHRTZEIT            11
 #define L_TOUR_TOURSTRECKE          6
 #define L_TOUR_BEZEICHNUNG          30
 #define L_TOUR_BEMERKUNGEN          240
 #define L_TOUR_DRUCKFACHNR          6
 #define L_TOUR_LAGRECHTOUR          11
 #define L_TOUR_KZUPD                1
 #define L_TOUR_FILIALNR             6
 #define L_TOUR_KDAUFTRAGART         2
 #define L_TOUR_SNIGHTTOUR           6


 #define L_TOUR_PKEY 17

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define TOUR_ANZ ( sizeof(TOUR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_TOUR sizeof(struct TOUR)


 #define TOUR_H

 #define TOUR_LISTE \
 			TOUR.DATUMKOMMI, \
 			TOUR.TOURID, \
 			TOUR.ZEITKOENDE, \
 			TOUR.DATUMVERSAND, \
 			TOUR.ZEITVERSAND, \
 			TOUR.BAHNHOFVERSAND, \
 			TOUR.TOURSTAT, \
 			TOUR.DRUCKSTAT, \
 			TOUR.VORABSCHEINDRUCKEN, \
 			TOUR.TOURMITVERBUND, \
 			TOUR.FAHRTZEIT, \
 			TOUR.TOURSTRECKE, \
 			TOUR.BEZEICHNUNG, \
 			TOUR.BEMERKUNGEN, \
 			TOUR.DRUCKFACHNR, \
 			TOUR.LAGRECHTOUR, \
 			TOUR.KZUPD, \
			TOUR.FILIALNR, \
			TOUR.KDAUFTRAGART, \
			TOUR.SNIGHTTOUR
 #define TOUR_PLISTE \
 			"TOUR.DATUMKOMMI," \
 			"TOUR.TOURID," \
 			"TOUR.ZEITKOENDE," \
 			"TOUR.DATUMVERSAND," \
 			"TOUR.ZEITVERSAND," \
 			"TOUR.BAHNHOFVERSAND," \
 			"TOUR.TOURSTAT," \
 			"TOUR.DRUCKSTAT," \
 			"TOUR.VORABSCHEINDRUCKEN," \
 			"TOUR.TOURMITVERBUND," \
 			"TOUR.FAHRTZEIT," \
 			"TOUR.TOURSTRECKE," \
 			"TOUR.BEZEICHNUNG," \
 			"TOUR.BEMERKUNGEN," \
 			"TOUR.DRUCKFACHNR," \
 			"TOUR.LAGRECHTOUR," \
 			"TOUR.KZUPD," \
			"TOUR.FILIALNR," \
			"TOUR.KDAUFTRAGART," \
			"TOUR.SNIGHTTOUR "

 #define TOUR_PELISTE \
 			"DATUMKOMMI," \
 			"TOURID," \
 			"ZEITKOENDE," \
 			"DATUMVERSAND," \
 			"ZEITVERSAND," \
 			"BAHNHOFVERSAND," \
 			"TOURSTAT," \
 			"DRUCKSTAT," \
 			"VORABSCHEINDRUCKEN," \
 			"TOURMITVERBUND," \
 			"FAHRTZEIT," \
 			"TOURSTRECKE," \
 			"BEZEICHNUNG," \
 			"BEMERKUNGEN," \
 			"DRUCKFACHNR," \
 			"LAGRECHTOUR," \
 			"KZUPD," \
			"FILIALNR," \
			"KDAUFTRAGART," \
			"SNIGHTTOUR "

 #define TOUR_UPDLISTE \
 			"DATUMKOMMI=?," \
 			"TOURID=?," \
 			"ZEITKOENDE=?," \
 			"DATUMVERSAND=?," \
 			"ZEITVERSAND=?," \
 			"BAHNHOFVERSAND=?," \
 			"TOURSTAT=?," \
 			"DRUCKSTAT=?," \
 			"VORABSCHEINDRUCKEN=?," \
 			"TOURMITVERBUND=?," \
 			"FAHRTZEIT=?," \
 			"TOURSTRECKE=?," \
 			"BEZEICHNUNG=?," \
 			"BEMERKUNGEN=?," \
 			"DRUCKFACHNR=?," \
 			"LAGRECHTOUR=?," \
 			"KZUPD=?," \
			"FILIALNR=?," \
			"KDAUFTRAGART=?," \
			"SNIGHTTOUR=? "

 #define TOURDATUMKOMMI                    0
 #define TOURTOURID                        1
 #define TOURZEITKOENDE                    2
 #define TOURDATUMVERSAND                  3
 #define TOURZEITVERSAND                   4
 #define TOURBAHNHOFVERSAND                5
 #define TOURTOURSTAT                      6
 #define TOURDRUCKSTAT                     7
 #define TOURVORABSCHEINDRUCKEN            8
 #define TOURTOURMITVERBUND                9
 #define TOURFAHRTZEIT                     10
 #define TOURTOURSTRECKE                   11
 #define TOURBEZEICHNUNG                   12
 #define TOURBEMERKUNGEN                   13
 #define TOURDRUCKFACHNR                   14
 #define TOURLAGRECHTOUR                   15
 #define TOURKZUPD                         16
 #define TOURFILIALNR                      17
 #define TOURKDAUFTRAGART				   18
 #define TOURSNIGHTTOUR					   19

 #define TOUR_ZEIGER(xxx) \
 			:xxx->DATUMKOMMI,\
 			:xxx->TOURID,\
 			:xxx->ZEITKOENDE,\
 			:xxx->DATUMVERSAND,\
 			:xxx->ZEITVERSAND,\
 			:xxx->BAHNHOFVERSAND,\
 			:xxx->TOURSTAT,\
 			:xxx->DRUCKSTAT,\
 			:xxx->VORABSCHEINDRUCKEN,\
 			:xxx->TOURMITVERBUND,\
 			:xxx->FAHRTZEIT,\
 			:xxx->TOURSTRECKE,\
 			:xxx->BEZEICHNUNG,\
 			:xxx->BEMERKUNGEN,\
 			:xxx->DRUCKFACHNR,\
 			:xxx->LAGRECHTOUR,\
 			:xxx->KZUPD,\
			:xxx->FILIALNR,\
			:xxx->KDAUFTRAGART,\
			:xxx->SNIGHTTOUR

 #define TOUR_UPDATE(xxx) \
 			DATUMKOMMI = :xxx->DATUMKOMMI,\
 			TOURID = :xxx->TOURID,\
 			ZEITKOENDE = :xxx->ZEITKOENDE,\
 			DATUMVERSAND = :xxx->DATUMVERSAND,\
 			ZEITVERSAND = :xxx->ZEITVERSAND,\
 			BAHNHOFVERSAND = :xxx->BAHNHOFVERSAND,\
 			TOURSTAT = :xxx->TOURSTAT,\
 			DRUCKSTAT = :xxx->DRUCKSTAT,\
 			VORABSCHEINDRUCKEN = :xxx->VORABSCHEINDRUCKEN,\
 			TOURMITVERBUND = :xxx->TOURMITVERBUND,\
 			FAHRTZEIT = :xxx->FAHRTZEIT,\
 			TOURSTRECKE = :xxx->TOURSTRECKE,\
 			BEZEICHNUNG = :xxx->BEZEICHNUNG,\
 			BEMERKUNGEN = :xxx->BEMERKUNGEN,\
 			DRUCKFACHNR = :xxx->DRUCKFACHNR,\
 			LAGRECHTOUR = :xxx->LAGRECHTOUR,\
 			KZUPD = :xxx->KZUPD,\
			FILIALNR = :xxx->FILIALNR,\
			KDAUFTRAGART = :xxx->KDAUFTRAGART,\
			SNIGHTTOUR = :xxx->SNIGHTTOUR

 #define LS_TOUR_DATUMKOMMI           11
 #define LS_TOUR_TOURID               7
 #define LS_TOUR_ZEITKOENDE           11
 #define LS_TOUR_DATUMVERSAND         11
 #define LS_TOUR_ZEITVERSAND          11
 #define LS_TOUR_BAHNHOFVERSAND       7
 #define LS_TOUR_TOURSTAT             2
 #define LS_TOUR_DRUCKSTAT            2
 #define LS_TOUR_VORABSCHEINDRUCKEN   2
 #define LS_TOUR_TOURMITVERBUND       2
 #define LS_TOUR_FAHRTZEIT            11
 #define LS_TOUR_TOURSTRECKE          7
 #define LS_TOUR_BEZEICHNUNG          31
 #define LS_TOUR_BEMERKUNGEN          241
 #define LS_TOUR_DRUCKFACHNR          7
 #define LS_TOUR_LAGRECHTOUR          11
 #define LS_TOUR_KZUPD                2
 #define LS_TOUR_FILIALNR             7
 #define LS_TOUR_KDAUFTRAGART		  3
 #define LS_TOUR_SNIGHTTOUR             7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct TOUR {
		 long    DATUMKOMMI;
		 char    TOURID[6 + 1];
		 long    ZEITKOENDE;
		 long    DATUMVERSAND;
		 long    ZEITVERSAND;
		 short   BAHNHOFVERSAND;
		 char    TOURSTAT[1 + 1];
		 char    DRUCKSTAT[1 + 1];
		 char    VORABSCHEINDRUCKEN[1 + 1];
		 char    TOURMITVERBUND[1 + 1];
		 long    FAHRTZEIT;
		 short   TOURSTRECKE;
		 char    BEZEICHNUNG[30 + 1];
		 char    BEMERKUNGEN[240 + 1];
		 short   DRUCKFACHNR;
		 long    LAGRECHTOUR;
		 char    KZUPD[1 + 1];
		 short   FILIALNR;
		 char    KDAUFTRAGART[2 + 1];
		 short   SNIGHTTOUR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_TOUR {
		 long    DATUMKOMMI;
		 char    TOURID[6 + 1];
		 long    ZEITKOENDE;
		 long    DATUMVERSAND;
		 long    ZEITVERSAND;
		 short   BAHNHOFVERSAND;
		 char    TOURSTAT;
		 char    DRUCKSTAT;
		 char    VORABSCHEINDRUCKEN;
		 char    TOURMITVERBUND;
		 long    FAHRTZEIT;
		 short   TOURSTRECKE;
		 char    BEZEICHNUNG[30 + 1];
		 char    BEMERKUNGEN[240 + 1];
		 short   DRUCKFACHNR;
		 long    LAGRECHTOUR;
		 char    KZUPD;
		 short   FILIALNR;
		 char    KDAUFTRAGART[2 + 1];
		 short   SNIGHTTOUR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_TOUR {
		 short  DATUMKOMMI;
		 short  TOURID;
		 short  ZEITKOENDE;
		 short  DATUMVERSAND;
		 short  ZEITVERSAND;
		 short  BAHNHOFVERSAND;
		 short  TOURSTAT;
		 short  DRUCKSTAT;
		 short  VORABSCHEINDRUCKEN;
		 short  TOURMITVERBUND;
		 short  FAHRTZEIT;
		 short  TOURSTRECKE;
		 short  BEZEICHNUNG;
		 short  BEMERKUNGEN;
		 short  DRUCKFACHNR;
		 short  LAGRECHTOUR;
		 short  KZUPD;
		 short  FILIALNR;
		 short  KDAUFTRAGART;
		 short  SNIGHTTOUR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_TOUR {
		 char    DATUMKOMMI[11];
		 char    TOURID[6 + 1];
		 char    ZEITKOENDE[11];
		 char    DATUMVERSAND[11];
		 char    ZEITVERSAND[11];
		 char    BAHNHOFVERSAND[7];
		 char    TOURSTAT[1 + 1];
		 char    DRUCKSTAT[1 + 1];
		 char    VORABSCHEINDRUCKEN[1 + 1];
		 char    TOURMITVERBUND[1 + 1];
		 char    FAHRTZEIT[11];
		 char    TOURSTRECKE[7];
		 char    BEZEICHNUNG[30 + 1];
		 char    BEMERKUNGEN[240 + 1];
		 char    DRUCKFACHNR[7];
		 char    LAGRECHTOUR[11];
		 char    KZUPD[1 + 1];
		 char    FILIALNR[7];
		 char    KDAUFTRAGART[2 + 1];
		 char    SNIGHTTOUR[7];
       };

 struct O_TOUR {
		 char    DATUMKOMMI[11];
		 char    TOURID[6];
		 char    ZEITKOENDE[11];
		 char    DATUMVERSAND[11];
		 char    ZEITVERSAND[11];
		 char    BAHNHOFVERSAND[7];
		 char    TOURSTAT[1];
		 char    DRUCKSTAT[1];
		 char    VORABSCHEINDRUCKEN[1];
		 char    TOURMITVERBUND[1];
		 char    FAHRTZEIT[11];
		 char    TOURSTRECKE[7];
		 char    BEZEICHNUNG[30];
		 char    BEMERKUNGEN[240];
		 char    DRUCKFACHNR[7];
		 char    LAGRECHTOUR[11];
		 char    KZUPD[1];
		 char    FILIALNR[7];
		 char    KDAUFTRAGART[2];
		 char    SNIGHTTOUR[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc TOUR_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_S ,    6 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TOUR_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_S,    5 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CTOUR
 {
  public:

  TOUR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, TOUR_BES, TOUR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,TOUR_BES, TOUR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,TOUR_BES, TOUR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CTOUR()
  {
   ::buf_default((void *)&s, TOUR_BES, TOUR_ANZ);
  }
 };
#endif

#define TOUR_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 DATUMKOMMI         INTEGER         default 0 NOT NULL,\
		 TOURID             CHAR(6)         default " " NOT NULL,\
		 ZEITKOENDE         INTEGER         default 0 NOT NULL,\
		 DATUMVERSAND       INTEGER         default 0 NOT NULL,\
		 ZEITVERSAND        INTEGER         default 0 NOT NULL,\
		 BAHNHOFVERSAND     SMALLINT        default 0 NOT NULL,\
		 TOURSTAT           CHAR(1)         default " " NOT NULL,\
		 DRUCKSTAT          CHAR(1)         default " " NOT NULL,\
		 VORABSCHEINDRUCKEN CHAR(1)         default " " NOT NULL,\
		 TOURMITVERBUND     CHAR(1)         default " " NOT NULL,\
		 FAHRTZEIT          INTEGER         default 0 NOT NULL,\
		 TOURSTRECKE        SMALLINT        default 0 NOT NULL,\
		 BEZEICHNUNG        CHAR(30)        default " " NOT NULL,\
		 BEMERKUNGEN        VARCHAR(240,0)  default " " NOT NULL,\
		 DRUCKFACHNR        SMALLINT        default 0 NOT NULL,\
		 LAGRECHTOUR        INTEGER         default 0 NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 FILIALNR           SMALLINT        default 0 NOT NULL,\
		 KDAUFTRAGART       CHAR(2)         default " " NOT NULL,\
		 SNIGHTTOUR         SMALLINT        default 0 NOT NULL, ) EXTENT SIZE 467 LOCK MODE ROW;

#define TOUR_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX TOURX              on yyy( DATUMKOMMI, FILIALNR, TOURID );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define TOUR_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX TOURX             ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

