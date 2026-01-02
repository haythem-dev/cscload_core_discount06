/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_DKTUR_TURFIL               2
 #define L_DKTUR_TURTOUR              6
 #define L_DKTUR_TURBEZ               30
 #define L_DKTUR_TURREF               30
 #define L_DKTUR_TURKM                3
 #define L_DKTUR_TURZEIT              7
 #define L_DKTUR_TURMO                1
 #define L_DKTUR_TURDI                1
 #define L_DKTUR_TURMI                1
 #define L_DKTUR_TURDO                1
 #define L_DKTUR_TURFR                1
 #define L_DKTUR_TURSA                1
 #define L_DKTUR_TURSO                1
 #define L_DKTUR_TURLOEKZ             1
 #define L_DKTUR_TURAKKD              5
 #define L_DKTUR_TURVTKZ              1
 #define L_DKTUR_TURKPKM              3
 #define N_DKTUR_TURKPKM              2
 #define L_DKTUR_TURKPST              5
 #define N_DKTUR_TURKPST              2
 #define L_DKTUR_TURSATOUR            3
 #define L_DKTUR_TURDTOUR             4
 #define L_DKTUR_TURKIPPZEIT          2
 #define L_DKTUR_TURNTOUR             1


 #define L_DKTUR_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DKTUR_ANZ ( sizeof(DKTUR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DKTUR sizeof(struct DKTUR)


 #define DKTUR_H

 #define DKTUR_LISTE \
 			DKTUR.TURFIL, \
 			DKTUR.TURTOUR, \
 			DKTUR.TURBEZ, \
 			DKTUR.TURREF, \
 			DKTUR.TURKM, \
 			DKTUR.TURZEIT, \
 			DKTUR.TURMO, \
 			DKTUR.TURDI, \
 			DKTUR.TURMI, \
 			DKTUR.TURDO, \
 			DKTUR.TURFR, \
 			DKTUR.TURSA, \
 			DKTUR.TURSO, \
 			DKTUR.TURLOEKZ, \
 			DKTUR.TURAKKD, \
 			DKTUR.TURVTKZ, \
 			DKTUR.TURKPKM, \
 			DKTUR.TURKPST, \
 			DKTUR.TURSATOUR, \
 			DKTUR.TURDTOUR, \
 			DKTUR.TURKIPPZEIT, \
 			DKTUR.TURNTOUR
 #define DKTUR_PLISTE \
 			"DKTUR.TURFIL," \
 			"DKTUR.TURTOUR," \
 			"DKTUR.TURBEZ," \
 			"DKTUR.TURREF," \
 			"DKTUR.TURKM," \
 			"DKTUR.TURZEIT," \
 			"DKTUR.TURMO," \
 			"DKTUR.TURDI," \
 			"DKTUR.TURMI," \
 			"DKTUR.TURDO," \
 			"DKTUR.TURFR," \
 			"DKTUR.TURSA," \
 			"DKTUR.TURSO," \
 			"DKTUR.TURLOEKZ," \
 			"DKTUR.TURAKKD," \
 			"DKTUR.TURVTKZ," \
 			"DKTUR.TURKPKM," \
 			"DKTUR.TURKPST," \
 			"DKTUR.TURSATOUR," \
 			"DKTUR.TURDTOUR," \
 			"DKTUR.TURKIPPZEIT," \
 			"DKTUR.TURNTOUR "

 #define DKTURTURFIL                        0
 #define DKTURTURTOUR                       1
 #define DKTURTURBEZ                        2
 #define DKTURTURREF                        3
 #define DKTURTURKM                         4
 #define DKTURTURZEIT                       5
 #define DKTURTURMO                         6
 #define DKTURTURDI                         7
 #define DKTURTURMI                         8
 #define DKTURTURDO                         9
 #define DKTURTURFR                         10
 #define DKTURTURSA                         11
 #define DKTURTURSO                         12
 #define DKTURTURLOEKZ                      13
 #define DKTURTURAKKD                       14
 #define DKTURTURVTKZ                       15
 #define DKTURTURKPKM                       16
 #define DKTURTURKPST                       17
 #define DKTURTURSATOUR                     18
 #define DKTURTURDTOUR                      19
 #define DKTURTURKIPPZEIT                   20
 #define DKTURTURNTOUR                      21

 #define DKTUR_ZEIGER(xxx) \
 			:xxx->TURFIL,\
 			:xxx->TURTOUR,\
 			:xxx->TURBEZ,\
 			:xxx->TURREF,\
 			:xxx->TURKM,\
 			:xxx->TURZEIT,\
 			:xxx->TURMO,\
 			:xxx->TURDI,\
 			:xxx->TURMI,\
 			:xxx->TURDO,\
 			:xxx->TURFR,\
 			:xxx->TURSA,\
 			:xxx->TURSO,\
 			:xxx->TURLOEKZ,\
 			:xxx->TURAKKD,\
 			:xxx->TURVTKZ,\
 			:xxx->TURKPKM,\
 			:xxx->TURKPST,\
 			:xxx->TURSATOUR,\
 			:xxx->TURDTOUR,\
 			:xxx->TURKIPPZEIT,\
 			:xxx->TURNTOUR

 #define DKTUR_UPDATE(xxx) \
 			TURFIL = :xxx->TURFIL,\
 			TURTOUR = :xxx->TURTOUR,\
 			TURBEZ = :xxx->TURBEZ,\
 			TURREF = :xxx->TURREF,\
 			TURKM = :xxx->TURKM,\
 			TURZEIT = :xxx->TURZEIT,\
 			TURMO = :xxx->TURMO,\
 			TURDI = :xxx->TURDI,\
 			TURMI = :xxx->TURMI,\
 			TURDO = :xxx->TURDO,\
 			TURFR = :xxx->TURFR,\
 			TURSA = :xxx->TURSA,\
 			TURSO = :xxx->TURSO,\
 			TURLOEKZ = :xxx->TURLOEKZ,\
 			TURAKKD = :xxx->TURAKKD,\
 			TURVTKZ = :xxx->TURVTKZ,\
 			TURKPKM = :xxx->TURKPKM,\
 			TURKPST = :xxx->TURKPST,\
 			TURSATOUR = :xxx->TURSATOUR,\
 			TURDTOUR = :xxx->TURDTOUR,\
 			TURKIPPZEIT = :xxx->TURKIPPZEIT,\
 			TURNTOUR = :xxx->TURNTOUR

 #define LS_DKTUR_TURFIL               3
 #define LS_DKTUR_TURTOUR              7
 #define LS_DKTUR_TURBEZ               31
 #define LS_DKTUR_TURREF               31
 #define LS_DKTUR_TURKM                4
 #define LS_DKTUR_TURZEIT              8
 #define LS_DKTUR_TURMO                2
 #define LS_DKTUR_TURDI                2
 #define LS_DKTUR_TURMI                2
 #define LS_DKTUR_TURDO                2
 #define LS_DKTUR_TURFR                2
 #define LS_DKTUR_TURSA                2
 #define LS_DKTUR_TURSO                2
 #define LS_DKTUR_TURLOEKZ             2
 #define LS_DKTUR_TURAKKD              6
 #define LS_DKTUR_TURVTKZ              2
 #define LS_DKTUR_TURKPKM              5
 #define LS_DKTUR_TURKPST              7
 #define LS_DKTUR_TURSATOUR            4
 #define LS_DKTUR_TURDTOUR             5
 #define LS_DKTUR_TURKIPPZEIT          3
 #define LS_DKTUR_TURNTOUR             2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKTUR {
		 char    TURFIL[2 + 1];
		 char    TURTOUR[6 + 1];
		 char    TURBEZ[30 + 1];
		 char    TURREF[30 + 1];
		 char    TURKM[3 + 1];
		 char    TURZEIT[7 + 1];
		 char    TURMO[1 + 1];
		 char    TURDI[1 + 1];
		 char    TURMI[1 + 1];
		 char    TURDO[1 + 1];
		 char    TURFR[1 + 1];
		 char    TURSA[1 + 1];
		 char    TURSO[1 + 1];
		 char    TURLOEKZ[1 + 1];
		 char    TURAKKD[5 + 1];
		 char    TURVTKZ[1 + 1];
		 double  TURKPKM;
		 double  TURKPST;
		 char    TURSATOUR[3 + 1];
		 char    TURDTOUR[4 + 1];
		 char    TURKIPPZEIT[2 + 1];
		 char    TURNTOUR[1 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_DKTUR {
		 char    TURFIL[2 + 1];
		 char    TURTOUR[6 + 1];
		 char    TURBEZ[30 + 1];
		 char    TURREF[30 + 1];
		 char    TURKM[3 + 1];
		 char    TURZEIT[7 + 1];
		 char    TURMO;
		 char    TURDI;
		 char    TURMI;
		 char    TURDO;
		 char    TURFR;
		 char    TURSA;
		 char    TURSO;
		 char    TURLOEKZ;
		 char    TURAKKD[5 + 1];
		 char    TURVTKZ;
		 double  TURKPKM;
		 double  TURKPST;
		 char    TURSATOUR[3 + 1];
		 char    TURDTOUR[4 + 1];
		 char    TURKIPPZEIT[2 + 1];
		 char    TURNTOUR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_DKTUR {
		 short  TURFIL;
		 short  TURTOUR;
		 short  TURBEZ;
		 short  TURREF;
		 short  TURKM;
		 short  TURZEIT;
		 short  TURMO;
		 short  TURDI;
		 short  TURMI;
		 short  TURDO;
		 short  TURFR;
		 short  TURSA;
		 short  TURSO;
		 short  TURLOEKZ;
		 short  TURAKKD;
		 short  TURVTKZ;
		 short  TURKPKM;
		 short  TURKPST;
		 short  TURSATOUR;
		 short  TURDTOUR;
		 short  TURKIPPZEIT;
		 short  TURNTOUR;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_DKTUR {
		 char    TURFIL[2 + 1];
		 char    TURTOUR[6 + 1];
		 char    TURBEZ[30 + 1];
		 char    TURREF[30 + 1];
		 char    TURKM[3 + 1];
		 char    TURZEIT[7 + 1];
		 char    TURMO[1 + 1];
		 char    TURDI[1 + 1];
		 char    TURMI[1 + 1];
		 char    TURDO[1 + 1];
		 char    TURFR[1 + 1];
		 char    TURSA[1 + 1];
		 char    TURSO[1 + 1];
		 char    TURLOEKZ[1 + 1];
		 char    TURAKKD[5 + 1];
		 char    TURVTKZ[1 + 1];
		 char    TURKPKM[3 + 2];
		 char    TURKPST[5 + 2];
		 char    TURSATOUR[3 + 1];
		 char    TURDTOUR[4 + 1];
		 char    TURKIPPZEIT[2 + 1];
		 char    TURNTOUR[1 + 1];
       };

 struct O_DKTUR {
		 char    TURFIL[2];
		 char    TURTOUR[6];
		 char    TURBEZ[30];
		 char    TURREF[30];
		 char    TURKM[3];
		 char    TURZEIT[7];
		 char    TURMO[1];
		 char    TURDI[1];
		 char    TURMI[1];
		 char    TURDO[1];
		 char    TURFR[1];
		 char    TURSA[1];
		 char    TURSO[1];
		 char    TURLOEKZ[1];
		 char    TURAKKD[5];
		 char    TURVTKZ[1];
		 char    TURKPKM[3];
		 char    TURKPST[5];
		 char    TURSATOUR[3];
		 char    TURDTOUR[4];
		 char    TURKIPPZEIT[2];
		 char    TURNTOUR[1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DKTUR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_D ,    3 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DKTUR_BES [] =
 {
	 { TYP_C,    2 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_D,    3 ,   2 },
	 { TYP_D,    5 ,   2 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_F,    1 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDKTUR
 {
  public:

  DKTUR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DKTUR_BES, DKTUR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DKTUR_BES, DKTUR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DKTUR_BES, DKTUR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDKTUR()
  {
   ::buf_default((void *)&s, DKTUR_BES, DKTUR_ANZ);
  }
 };
#endif

#define DKTUR_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 TURFIL             CHAR(2)         default " " NOT NULL,\
		 TURTOUR            CHAR(6)         default " " NOT NULL,\
		 TURBEZ             CHAR(30)        default " " NOT NULL,\
		 TURREF             CHAR(30)        default " " NOT NULL,\
		 TURKM              CHAR(3)         default " " NOT NULL,\
		 TURZEIT            CHAR(7)         default " " NOT NULL,\
		 TURMO              CHAR(1)         default " " NOT NULL,\
		 TURDI              CHAR(1)         default " " NOT NULL,\
		 TURMI              CHAR(1)         default " " NOT NULL,\
		 TURDO              CHAR(1)         default " " NOT NULL,\
		 TURFR              CHAR(1)         default " " NOT NULL,\
		 TURSA              CHAR(1)         default " " NOT NULL,\
		 TURSO              CHAR(1)         default " " NOT NULL,\
		 TURLOEKZ           CHAR(1)         default " " NOT NULL,\
		 TURAKKD            CHAR(5)         default " " NOT NULL,\
		 TURVTKZ            CHAR(1)         default " " NOT NULL,\
		 TURKPKM            DECIMAL(3,2)    default 0 NOT NULL,\
		 TURKPST            DECIMAL(5,2)    default 0 NOT NULL,\
		 TURSATOUR          CHAR(3)         default " " NOT NULL,\
		 TURDTOUR           CHAR(4)         default " " NOT NULL,\
		 TURKIPPZEIT        CHAR(2)         default " " NOT NULL,\
		 TURNTOUR           CHAR(1)         default " " NOT NULL  ) EXTENT SIZE 9;

#define DKTUR_CREATE_INDEX(yyy,xxx) \

#define DKTUR_DELETE_INDEX(xxx) \

