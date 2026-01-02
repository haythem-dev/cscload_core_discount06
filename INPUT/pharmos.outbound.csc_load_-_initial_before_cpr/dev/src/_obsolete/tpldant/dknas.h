/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_DKNAS_NASFIL               2
 #define L_DKNAS_NASPZN               7
 #define L_DKNAS_NASDABE              7
 #define L_DKNAS_NASDAEN              7
 #define L_DKNAS_NASKONT              5
 #define L_DKNAS_NASRKON              5
 #define L_DKNAS_NASMEN1              3
 #define L_DKNAS_NASPREI1             7
 #define N_DKNAS_NASPREI1             2
 #define L_DKNAS_NASMEN2              3
 #define L_DKNAS_NASPREI2             7
 #define N_DKNAS_NASPREI2             2
 #define L_DKNAS_NASMEN3              3
 #define L_DKNAS_NASPREI3             7
 #define N_DKNAS_NASPREI3             2
 #define L_DKNAS_NASMEN4              3
 #define L_DKNAS_NASPREI4             7
 #define N_DKNAS_NASPREI4             2
 #define L_DKNAS_NASMEN5              3
 #define L_DKNAS_NASPREI5             7
 #define N_DKNAS_NASPREI5             2
 #define L_DKNAS_NASMEN6              3
 #define L_DKNAS_NASPREI6             7
 #define N_DKNAS_NASPREI6             2
 #define L_DKNAS_NASUMEN              5
 #define L_DKNAS_NASUWER              7
 #define L_DKNAS_NASLOE               1
 #define L_DKNAS_NASHV                1
 #define L_DKNAS_NASFILLER            32


 #define L_DKNAS_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DKNAS_ANZ ( sizeof(DKNAS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DKNAS sizeof(struct DKNAS)


 #define DKNAS_H

 #define DKNAS_LISTE \
 			DKNAS.NASFIL, \
 			DKNAS.NASPZN, \
 			DKNAS.NASDABE, \
 			DKNAS.NASDAEN, \
 			DKNAS.NASKONT, \
 			DKNAS.NASRKON, \
 			DKNAS.NASMEN1, \
 			DKNAS.NASPREI1, \
 			DKNAS.NASMEN2, \
 			DKNAS.NASPREI2, \
 			DKNAS.NASMEN3, \
 			DKNAS.NASPREI3, \
 			DKNAS.NASMEN4, \
 			DKNAS.NASPREI4, \
 			DKNAS.NASMEN5, \
 			DKNAS.NASPREI5, \
 			DKNAS.NASMEN6, \
 			DKNAS.NASPREI6, \
 			DKNAS.NASUMEN, \
 			DKNAS.NASUWER, \
 			DKNAS.NASLOE, \
 			DKNAS.NASHV, \
 			DKNAS.NASFILLER
 #define DKNAS_PLISTE \
 			"DKNAS.NASFIL," \
 			"DKNAS.NASPZN," \
 			"DKNAS.NASDABE," \
 			"DKNAS.NASDAEN," \
 			"DKNAS.NASKONT," \
 			"DKNAS.NASRKON," \
 			"DKNAS.NASMEN1," \
 			"DKNAS.NASPREI1," \
 			"DKNAS.NASMEN2," \
 			"DKNAS.NASPREI2," \
 			"DKNAS.NASMEN3," \
 			"DKNAS.NASPREI3," \
 			"DKNAS.NASMEN4," \
 			"DKNAS.NASPREI4," \
 			"DKNAS.NASMEN5," \
 			"DKNAS.NASPREI5," \
 			"DKNAS.NASMEN6," \
 			"DKNAS.NASPREI6," \
 			"DKNAS.NASUMEN," \
 			"DKNAS.NASUWER," \
 			"DKNAS.NASLOE," \
 			"DKNAS.NASHV," \
 			"DKNAS.NASFILLER " 

 #define DKNASNASFIL                        0
 #define DKNASNASPZN                        1
 #define DKNASNASDABE                       2
 #define DKNASNASDAEN                       3
 #define DKNASNASKONT                       4
 #define DKNASNASRKON                       5
 #define DKNASNASMEN1                       6
 #define DKNASNASPREI1                      7
 #define DKNASNASMEN2                       8
 #define DKNASNASPREI2                      9
 #define DKNASNASMEN3                       10
 #define DKNASNASPREI3                      11
 #define DKNASNASMEN4                       12
 #define DKNASNASPREI4                      13
 #define DKNASNASMEN5                       14
 #define DKNASNASPREI5                      15
 #define DKNASNASMEN6                       16
 #define DKNASNASPREI6                      17
 #define DKNASNASUMEN                       18
 #define DKNASNASUWER                       19
 #define DKNASNASLOE                        20
 #define DKNASNASHV                         21
 #define DKNASNASFILLER                     22

 #define DKNAS_ZEIGER(xxx) \
 			:xxx->NASFIL,\
 			:xxx->NASPZN,\
 			:xxx->NASDABE,\
 			:xxx->NASDAEN,\
 			:xxx->NASKONT,\
 			:xxx->NASRKON,\
 			:xxx->NASMEN1,\
 			:xxx->NASPREI1,\
 			:xxx->NASMEN2,\
 			:xxx->NASPREI2,\
 			:xxx->NASMEN3,\
 			:xxx->NASPREI3,\
 			:xxx->NASMEN4,\
 			:xxx->NASPREI4,\
 			:xxx->NASMEN5,\
 			:xxx->NASPREI5,\
 			:xxx->NASMEN6,\
 			:xxx->NASPREI6,\
 			:xxx->NASUMEN,\
 			:xxx->NASUWER,\
 			:xxx->NASLOE,\
 			:xxx->NASHV,\
 			:xxx->NASFILLER

 #define DKNAS_UPDATE(xxx) \
 			NASFIL = :xxx->NASFIL,\
 			NASPZN = :xxx->NASPZN,\
 			NASDABE = :xxx->NASDABE,\
 			NASDAEN = :xxx->NASDAEN,\
 			NASKONT = :xxx->NASKONT,\
 			NASRKON = :xxx->NASRKON,\
 			NASMEN1 = :xxx->NASMEN1,\
 			NASPREI1 = :xxx->NASPREI1,\
 			NASMEN2 = :xxx->NASMEN2,\
 			NASPREI2 = :xxx->NASPREI2,\
 			NASMEN3 = :xxx->NASMEN3,\
 			NASPREI3 = :xxx->NASPREI3,\
 			NASMEN4 = :xxx->NASMEN4,\
 			NASPREI4 = :xxx->NASPREI4,\
 			NASMEN5 = :xxx->NASMEN5,\
 			NASPREI5 = :xxx->NASPREI5,\
 			NASMEN6 = :xxx->NASMEN6,\
 			NASPREI6 = :xxx->NASPREI6,\
 			NASUMEN = :xxx->NASUMEN,\
 			NASUWER = :xxx->NASUWER,\
 			NASLOE = :xxx->NASLOE,\
 			NASHV = :xxx->NASHV,\
 			NASFILLER = :xxx->NASFILLER

 #define LS_DKNAS_NASFIL               3
 #define LS_DKNAS_NASPZN               8
 #define LS_DKNAS_NASDABE              8
 #define LS_DKNAS_NASDAEN              8
 #define LS_DKNAS_NASKONT              6
 #define LS_DKNAS_NASRKON              6
 #define LS_DKNAS_NASMEN1              4
 #define LS_DKNAS_NASPREI1             9
 #define LS_DKNAS_NASMEN2              4
 #define LS_DKNAS_NASPREI2             9
 #define LS_DKNAS_NASMEN3              4
 #define LS_DKNAS_NASPREI3             9
 #define LS_DKNAS_NASMEN4              4
 #define LS_DKNAS_NASPREI4             9
 #define LS_DKNAS_NASMEN5              4
 #define LS_DKNAS_NASPREI5             9
 #define LS_DKNAS_NASMEN6              4
 #define LS_DKNAS_NASPREI6             9
 #define LS_DKNAS_NASUMEN              6
 #define LS_DKNAS_NASUWER              8
 #define LS_DKNAS_NASLOE               2
 #define LS_DKNAS_NASHV                2
 #define LS_DKNAS_NASFILLER            33

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKNAS {
		 char    NASFIL[2 + 1];
		 char    NASPZN[7 + 1];
		 char    NASDABE[7 + 1];
		 char    NASDAEN[7 + 1];
		 char    NASKONT[5 + 1];
		 char    NASRKON[5 + 1];
		 char    NASMEN1[3 + 1];
		 double  NASPREI1;
		 char    NASMEN2[3 + 1];
		 double  NASPREI2;
		 char    NASMEN3[3 + 1];
		 double  NASPREI3;
		 char    NASMEN4[3 + 1];
		 double  NASPREI4;
		 char    NASMEN5[3 + 1];
		 double  NASPREI5;
		 char    NASMEN6[3 + 1];
		 double  NASPREI6;
		 char    NASUMEN[5 + 1];
		 char    NASUWER[7 + 1];
		 char    NASLOE[1 + 1];
		 char    NASHV[1 + 1];
		 char    NASFILLER[32 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_DKNAS {
		 char    NASFIL[2 + 1];
		 char    NASPZN[7 + 1];
		 char    NASDABE[7 + 1];
		 char    NASDAEN[7 + 1];
		 char    NASKONT[5 + 1];
		 char    NASRKON[5 + 1];
		 char    NASMEN1[3 + 1];
		 double  NASPREI1;
		 char    NASMEN2[3 + 1];
		 double  NASPREI2;
		 char    NASMEN3[3 + 1];
		 double  NASPREI3;
		 char    NASMEN4[3 + 1];
		 double  NASPREI4;
		 char    NASMEN5[3 + 1];
		 double  NASPREI5;
		 char    NASMEN6[3 + 1];
		 double  NASPREI6;
		 char    NASUMEN[5 + 1];
		 char    NASUWER[7 + 1];
		 char    NASLOE;
		 char    NASHV;
		 char    NASFILLER[32 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_DKNAS {
		 short  NASFIL;
		 short  NASPZN;
		 short  NASDABE;
		 short  NASDAEN;
		 short  NASKONT;
		 short  NASRKON;
		 short  NASMEN1;
		 short  NASPREI1;
		 short  NASMEN2;
		 short  NASPREI2;
		 short  NASMEN3;
		 short  NASPREI3;
		 short  NASMEN4;
		 short  NASPREI4;
		 short  NASMEN5;
		 short  NASPREI5;
		 short  NASMEN6;
		 short  NASPREI6;
		 short  NASUMEN;
		 short  NASUWER;
		 short  NASLOE;
		 short  NASHV;
		 short  NASFILLER;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_DKNAS {
		 char    NASFIL[2 + 1];
		 char    NASPZN[7 + 1];
		 char    NASDABE[7 + 1];
		 char    NASDAEN[7 + 1];
		 char    NASKONT[5 + 1];
		 char    NASRKON[5 + 1];
		 char    NASMEN1[3 + 1];
		 char    NASPREI1[7 + 2];
		 char    NASMEN2[3 + 1];
		 char    NASPREI2[7 + 2];
		 char    NASMEN3[3 + 1];
		 char    NASPREI3[7 + 2];
		 char    NASMEN4[3 + 1];
		 char    NASPREI4[7 + 2];
		 char    NASMEN5[3 + 1];
		 char    NASPREI5[7 + 2];
		 char    NASMEN6[3 + 1];
		 char    NASPREI6[7 + 2];
		 char    NASUMEN[5 + 1];
		 char    NASUWER[7 + 1];
		 char    NASLOE[1 + 1];
		 char    NASHV[1 + 1];
		 char    NASFILLER[32 + 1];
       };

 struct O_DKNAS {
		 char    NASFIL[2];
		 char    NASPZN[7];
		 char    NASDABE[7];
		 char    NASDAEN[7];
		 char    NASKONT[5];
		 char    NASRKON[5];
		 char    NASMEN1[3];
		 char    NASPREI1[7];
		 char    NASMEN2[3];
		 char    NASPREI2[7];
		 char    NASMEN3[3];
		 char    NASPREI3[7];
		 char    NASMEN4[3];
		 char    NASPREI4[7];
		 char    NASMEN5[3];
		 char    NASPREI5[7];
		 char    NASMEN6[3];
		 char    NASPREI6[7];
		 char    NASUMEN[5];
		 char    NASUWER[7];
		 char    NASLOE[1];
		 char    NASHV[1];
		 char    NASFILLER[32];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DKNAS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DKNAS_BES [] =
 {
	 { TYP_C,    2 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_D,    7 ,   2 },
	 { TYP_C,    3 ,   0 },
	 { TYP_D,    7 ,   2 },
	 { TYP_C,    3 ,   0 },
	 { TYP_D,    7 ,   2 },
	 { TYP_C,    3 ,   0 },
	 { TYP_D,    7 ,   2 },
	 { TYP_C,    3 ,   0 },
	 { TYP_D,    7 ,   2 },
	 { TYP_C,    3 ,   0 },
	 { TYP_D,    7 ,   2 },
	 { TYP_C,    5 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   32 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDKNAS
 {
  public:

  DKNAS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DKNAS_BES, DKNAS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DKNAS_BES, DKNAS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DKNAS_BES, DKNAS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDKNAS()
  {
   ::buf_default((void *)&s, DKNAS_BES, DKNAS_ANZ);
  }
 };
#endif

#define DKNAS_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 NASFIL             CHAR(2)         default " " NOT NULL,\
		 NASPZN             CHAR(7)         default " " NOT NULL,\
		 NASDABE            CHAR(7)         default " " NOT NULL,\
		 NASDAEN            CHAR(7)         default " " NOT NULL,\
		 NASKONT            CHAR(5)         default " " NOT NULL,\
		 NASRKON            CHAR(5)         default " " NOT NULL,\
		 NASMEN1            CHAR(3)         default " " NOT NULL,\
		 NASPREI1           DECIMAL(7,2)    default 0 NOT NULL,\
		 NASMEN2            CHAR(3)         default " " NOT NULL,\
		 NASPREI2           DECIMAL(7,2)    default 0 NOT NULL,\
		 NASMEN3            CHAR(3)         default " " NOT NULL,\
		 NASPREI3           DECIMAL(7,2)    default 0 NOT NULL,\
		 NASMEN4            CHAR(3)         default " " NOT NULL,\
		 NASPREI4           DECIMAL(7,2)    default 0 NOT NULL,\
		 NASMEN5            CHAR(3)         default " " NOT NULL,\
		 NASPREI5           DECIMAL(7,2)    default 0 NOT NULL,\
		 NASMEN6            CHAR(3)         default " " NOT NULL,\
		 NASPREI6           DECIMAL(7,2)    default 0 NOT NULL,\
		 NASUMEN            CHAR(5)         default " " NOT NULL,\
		 NASUWER            CHAR(7)         default " " NOT NULL,\
		 NASLOE             CHAR(1)         default " " NOT NULL,\
		 NASHV              CHAR(1)         default " " NOT NULL,\
		 NASFILLER          CHAR(32)        default " " NOT NULL  ) EXTENT SIZE 9;

#define DKNAS_CREATE_INDEX(yyy,xxx) \

#define DKNAS_DELETE_INDEX(xxx) \

