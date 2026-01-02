/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DEAKY_AKYFIL               2
 #define L_DEAKY_AKYPZN               7
 #define L_DEAKY_AKYKUBZ              12
 #define L_DEAKY_AKYSKUBZ             12
 #define L_DEAKY_AKYKZBUEN            1
 #define L_DEAKY_AKYAPCK              5
 #define L_DEAKY_AKYEINH              9
 #define L_DEAKY_AKYABEZ              30
 #define L_DEAKY_AKYDRFO              3
 #define L_DEAKY_AKYIMSC              5
 #define L_DEAKY_AKYTHER              5
 #define L_DEAKY_AKYWGR               5
 #define L_DEAKY_AKYLZEIT             3
 #define L_DEAKY_AKYLGE               5
 #define L_DEAKY_AKYBRE               5
 #define L_DEAKY_AKYHOE               5
 #define L_DEAKY_AKYGEW               5
 #define L_DEAKY_AKYAEP               7
 #define L_DEAKY_AKYAVP               7
 #define L_DEAKY_AKYGEP               7
 #define L_DEAKY_AKYGEPNA             7
 #define L_DEAKY_AKYSABEZ             30
 #define L_DEAKY_AKYZEKS              1
 #define L_DEAKY_AKYHLNR              5
 #define L_DEAKY_AKYPSS               1
 #define L_DEAKY_AKYAGPCH             7
 #define L_DEAKY_AKYFILL2             9

 #define L_DEAKY_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEAKY_ANZ ( sizeof(DEAKY_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEAKY sizeof(struct DEAKY)


 #define DEAKY_H

 #define DEAKY_LISTE \
 			DEAKY.AKYFIL, \
 			DEAKY.AKYPZN, \
			DEAKY.AKYKUBZ, \
			DEAKY.AKYSKUBZ, \
			DEAKY.AKYKZBUEN, \
			DEAKY.AKYAPCK, \
			DEAKY.AKYEINH, \
			DEAKY.AKYABEZ, \
			DEAKY.AKYDRFO, \
			DEAKY.AKYIMSC, \
			DEAKY.AKYTHER, \
			DEAKY.AKYWGR, \
			DEAKY.AKYLZEIT, \
			DEAKY.AKYLGE, \
			DEAKY.AKYBRE, \
			DEAKY.AKYHOE, \
			DEAKY.AKYGEW, \
			DEAKY.AKYAEP, \
			DEAKY.AKYAVP, \
			DEAKY.AKYGEP, \
			DEAKY.AKYGEPNA, \
			DEAKY.AKYSABEZ, \
			DEAKY.AKYZEKS, \
			DEAKY.AKYHLNR, \
			DEAKY.AKYPSS, \
			DEAKY.AKYAGPCH, \
			DEAKY.AKYFILL2

#define DEAKY_PLISTE \
 			"DEAKY.AKYFIL," \
 			"DEAKY.AKYPZN," \
			"DEAKY.AKYKUBZ," \
			"DEAKY.AKYSKUBZ," \
			"DEAKY.AKYKZBUEN," \
			"DEAKY.AKYAPCK," \
			"DEAKY.AKYEINH," \
			"DEAKY.AKYABEZ," \
			"DEAKY.AKYDRFO," \
			"DEAKY.AKYIMSC," \
			"DEAKY.AKYTHER," \
			"DEAKY.AKYWGR," \
			"DEAKY.AKYLZEIT," \
			"DEAKY.AKYLGE," \
			"DEAKY.AKYBRE," \
			"DEAKY.AKYHOE," \
			"DEAKY.AKYGEW," \
			"DEAKY.AKYAEP," \
			"DEAKY.AKYAVP," \
			"DEAKY.AKYGEP," \
			"DEAKY.AKYGEPNA," \
			"DEAKY.AKYSABEZ," \
			"DEAKY.AKYZEKS," \
			"DEAKY.AKYHLNR," \
			"DEAKY.AKYPSS," \
			"DEAKY.AKYAGPCH," \
			"DEAKY.AKYFILL2 "

 #define DEAKY_PELISTE \
 			"AKYFIL," \
 			"AKYPZN," \
			"AKYKUBZ," \
			"AKYSKUBZ," \
			"AKYKZBUEN," \
			"AKYAPCK," \
			"AKYEINH," \
			"AKYABEZ," \
			"AKYDRFO," \
			"AKYIMSC," \
			"AKYTHER," \
			"AKYWGR," \
			"AKYLZEIT," \
			"AKYLGE," \
			"AKYBRE," \
			"AKYHOE," \
			"AKYGEW," \
			"AKYAEP," \
			"AKYAVP," \
			"AKYGEP," \
			"AKYGEPNA," \
			"AKYSABEZ," \
			"AKYZEKS," \
			"AKYHLNR," \
			"AKYPSS," \
			"AKYAGPCH," \
			"AKYFILL2 "

 #define DEAKY_UPDLISTE \
 			"AKYFIL=?," \
 			"AKYPZN=?," \
			"AKYKUBZ=?," \
			"AKYSKUBZ=?," \
			"AKYKZBUEN=?," \
			"AKYAPCK=?," \
			"AKYEINH=?," \
			"AKYABEZ=?," \
			"AKYDRFO=?," \
			"AKYIMSC=?," \
			"AKYTHER=?," \
			"AKYWGR=?," \
			"AKYLZEIT=?," \
			"AKYLGE=?," \
			"AKYBRE=?," \
			"AKYHOE=?," \
			"AKYGEW=?," \
			"AKYAEP=?," \
			"AKYAVP=?," \
			"AKYGEP=?," \
			"AKYGEPNA=?," \
			"AKYSABEZ=?," \
			"AKYZEKS=?," \
			"AKYHLNR=?," \
			"AKYPSS=?," \
			"AKYAGPCH=?," \
			"AKYFILL2=? "

 #define DEAKYAKYFIL               0
 #define DEAKYAKYPZN               1
 #define DEAKYAKYKUBZ              2
 #define DEAKYAKYSKUBZ             3
 #define DEAKYAKYKZBUEN            4
 #define DEAKYAKYAPCK              5
 #define DEAKYAKYEINH              6
 #define DEAKYAKYABEZ              7
 #define DEAKYAKYDRFO              8
 #define DEAKYAKYIMSC              9
 #define DEAKYAKYTHER              10
 #define DEAKYAKYWGR               11
 #define DEAKYAKYLZEIT             12
 #define DEAKYAKYLGE               13
 #define DEAKYAKYBRE               14
 #define DEAKYAKYHOE               15
 #define DEAKYAKYGEW               16
 #define DEAKYAKYAEP               17
 #define DEAKYAKYAVP               18
 #define DEAKYAKYGEP               19
 #define DEAKYAKYGEPNA             20
 #define DEAKYAKYSABEZ             21
 #define DEAKYAKYZEKS              22
 #define DEAKYAKYHLNR              23
 #define DEAKYAKYPSS               24
 #define DEAKYAKYAGPCH             25
 #define DEAKYAKYFILL2             26

 #define DEAKY_ZEIGER(xxx) \
 			:xxx->AKYFIL, \
 			:xxx->AKYPZN, \
			:xxx->AKYKUBZ, \
			:xxx->AKYSKUBZ, \
			:xxx->AKYKZBUEN, \
			:xxx->AKYAPCK, \
			:xxx->AKYEINH, \
			:xxx->AKYABEZ, \
			:xxx->AKYDRFO, \
			:xxx->AKYIMSC, \
			:xxx->AKYTHER, \
			:xxx->AKYWGR, \
			:xxx->AKYLZEIT, \
			:xxx->AKYLGE, \
			:xxx->AKYBRE, \
			:xxx->AKYHOE, \
			:xxx->AKYGEW, \
			:xxx->AKYAEP, \
			:xxx->AKYAVP, \
			:xxx->AKYGEP, \
			:xxx->AKYGEPNA, \
			:xxx->AKYSABEZ, \
			:xxx->AKYZEKS, \
			:xxx->AKYHLNR, \
			:xxx->AKYPSS, \
			:xxx->AKYAGPCH, \
			:xxx->AKYFILL2

 #define DEAKY_UPDATE(xxx) \
 			AKYFIL = :xxx->AKYFIL, \
 			AKYPZN = :xxx->AKYPZN, \
			AKYKUBZ = :xxx->AKYKUBZ, \
			AKYSKUBZ = :xxx->AKYSKUBZ, \
			AKYKZBUEN = :xxx->AKYKZBUEN, \
			AKYAPCK = :xxx->AKYAPCK, \
			AKYEINH = :xxx->AKYEINH, \
			AKYABEZ = :xxx->AKYABEZ, \
			AKYDRFO = :xxx->AKYDRFO, \
			AKYIMSC = :xxx->AKYIMSC, \
			AKYTHER = :xxx->AKYTHER, \
			AKYWGR = :xxx->AKYWGR, \
			AKYLZEIT = :xxx->AKYLZEIT, \
			AKYLGE = :xxx->AKYLGE, \
			AKYBRE = :xxx->AKYBRE, \
			AKYHOE = :xxx->AKYHOE, \
			AKYGEW = :xxx->AKYGEW, \
			AKYAEP = :xxx->AKYAEP, \
			AKYAVP = :xxx->AKYAVP, \
			AKYGEP = :xxx->AKYGEP, \
			AKYGEPNA = :xxx->AKYGEPNA, \
			AKYSABEZ = :xxx->AKYSABEZ, \
			AKYZEKS = :xxx->AKYZEKS, \
			AKYHLNR = :xxx->AKYHLNR, \
			AKYPSS = :xxx->AKYPSS, \
			AKYAGPCH = :xxx->AKYAGPCH, \
			AKYFILL2 = :xxx->AKYFILL2

 #define LS_DEAKY_AKYFIL               3
 #define LS_DEAKY_AKYPZN               8
 #define LS_DEAKY_AKYKUBZ              13
 #define LS_DEAKY_AKYSKUBZ             13
 #define LS_DEAKY_AKYKZBUEN            2
 #define LS_DEAKY_AKYAPCK              6
 #define LS_DEAKY_AKYEINH              10
 #define LS_DEAKY_AKYABEZ              31
 #define LS_DEAKY_AKYDRFO              4
 #define LS_DEAKY_AKYIMSC              6
 #define LS_DEAKY_AKYTHER              6
 #define LS_DEAKY_AKYWGR               6
 #define LS_DEAKY_AKYLZEIT             4
 #define LS_DEAKY_AKYLGE               6
 #define LS_DEAKY_AKYBRE               6
 #define LS_DEAKY_AKYHOE               6
 #define LS_DEAKY_AKYGEW               6
 #define LS_DEAKY_AKYAEP               8
 #define LS_DEAKY_AKYAVP               8
 #define LS_DEAKY_AKYGEP               8
 #define LS_DEAKY_AKYGEPNA             8
 #define LS_DEAKY_AKYSABEZ             31
 #define LS_DEAKY_AKYZEKS              2
 #define LS_DEAKY_AKYHLNR              6
 #define LS_DEAKY_AKYPSS               2
 #define LS_DEAKY_AKYAGPCH             8
 #define LS_DEAKY_AKYFILL2             10

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DEAKY {
		 char    AKYFIL[2 + 1];
		 char    AKYPZN[7 + 1];
		 char    AKYKUBZ[12 + 1];
		 char    AKYSKUBZ[12 + 1];
		 char    AKYKZBUEN[1 + 1];
		 char    AKYAPCK[5 + 1];
		 char    AKYEINH[9 + 1];
		 char    AKYABEZ[30 + 1];
		 char    AKYDRFO[3 + 1];
		 char    AKYIMSC[5 + 1];
		 char    AKYTHER[5 + 1];
		 char    AKYWGR[5 + 1];
		 char    AKYLZEIT[3 + 1];
		 char    AKYLGE[5 + 1];
		 char    AKYBRE[5 + 1];
		 char    AKYHOE[5 + 1];
		 char    AKYGEW[5 + 1];
		 char    AKYAEP[7 + 1];
		 char    AKYAVP[7 + 1];
		 char    AKYGEP[7 + 1];
		 char    AKYGEPNA[7 + 1];
		 char    AKYSABEZ[30 + 1];
		 char    AKYZEKS[1 + 1];
		 char    AKYHLNR[5 + 1];
		 char    AKYPSS[1 + 1];
		 char    AKYAGPCH[7 + 1];
		 char    AKYFILL2[9 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_DEAKY {
		 char    AKYFIL[2 + 1];
		 char    AKYPZN[7 + 1];
		 char    AKYKUBZ[12 + 1];
		 char    AKYSKUBZ[12 + 1];
		 char    AKYKZBUEN;
		 char    AKYAPCK[5 + 1];
		 char    AKYEINH[9 + 1];
		 char    AKYABEZ[30 + 1];
		 char    AKYDRFO[3 + 1];
		 char    AKYIMSC[5 + 1];
		 char    AKYTHER[5 + 1];
		 char    AKYWGR[5 + 1];
		 char    AKYLZEIT[3 + 1];
		 char    AKYLGE[5 + 1];
		 char    AKYBRE[5 + 1];
		 char    AKYHOE[5 + 1];
		 char    AKYGEW[5 + 1];
		 char    AKYAEP[7 + 1];
		 char    AKYAVP[7 + 1];
		 char    AKYGEP[7 + 1];
		 char    AKYGEPNA[7 + 1];
		 char    AKYSABEZ[30 + 1];
		 char    AKYZEKS;
		 char    AKYHLNR[5 + 1];
		 char    AKYPSS[1 + 1];
		 char    AKYAGPCH[7 + 1];
		 char    AKYFILL2[9 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_DEAKY {
		 short  AKYFIL;
		 short  AKYPZN;
		 short  AKYKUBZ;
		 short  AKYSKUBZ;
		 short  AKYKZBUEN;
		 short  AKYAPCK;
		 short  AKYEINH;
		 short  AKYABEZ;
		 short  AKYDRFO;
		 short  AKYIMSC;
		 short  AKYTHER;
		 short  AKYWGR;
		 short  AKYLZEIT;
		 short  AKYLGE;
		 short  AKYBRE;
		 short  AKYHOE;
		 short  AKYGEW;
		 short  AKYAEP;
		 short  AKYAVP;
		 short  AKYGEP;
		 short  AKYGEPNA;
		 short  AKYSABEZ;
		 short  AKYZEKS;
		 short  AKYHLNR;
		 short  AKYPSS;
		 short  AKYAGPCH;
		 short  AKYFILL2;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_DEAKY {
		 char    AKYFIL[2 + 1];
		 char    AKYPZN[7 + 1];
		 char    AKYKUBZ[12 + 1];
		 char    AKYSKUBZ[12 + 1];
		 char    AKYKZBUEN[1 + 1];
		 char    AKYAPCK[5 + 1];
		 char    AKYEINH[9 + 1];
		 char    AKYABEZ[30 + 1];
		 char    AKYDRFO[3 + 1];
		 char    AKYIMSC[5 + 1];
		 char    AKYTHER[5 + 1];
		 char    AKYWGR[5 + 1];
		 char    AKYLZEIT[3 + 1];
		 char    AKYLGE[5 + 1];
		 char    AKYBRE[5 + 1];
		 char    AKYHOE[5 + 1];
		 char    AKYGEW[5 + 1];
		 char    AKYAEP[7 + 1];
		 char    AKYAVP[7 + 1];
		 char    AKYGEP[7 + 1];
		 char    AKYGEPNA[7 + 1];
		 char    AKYSABEZ[30 + 1];
		 char    AKYZEKS[1 + 1];
		 char    AKYHLNR[5 + 1];
		 char    AKYPSS[1 + 1];
		 char    AKYAGPCH[7 + 1];
		 char    AKYFILL2[9 + 1];
       };

 struct O_DEAKY {
		 char    AKYFIL[2];
		 char    AKYPZN[7];
		 char    AKYKUBZ[12];
		 char    AKYSKUBZ[12];
		 char    AKYKZBUEN[1];
		 char    AKYAPCK[5];
		 char    AKYEINH[9];
		 char    AKYABEZ[30];
		 char    AKYDRFO[3];
		 char    AKYIMSC[5];
		 char    AKYTHER[5];
		 char    AKYWGR[5];
		 char    AKYLZEIT[3];
		 char    AKYLGE[5];
		 char    AKYBRE[5];
		 char    AKYHOE[5];
		 char    AKYGEW[5];
		 char    AKYAEP[7];
		 char    AKYAVP[7];
		 char    AKYGEP[7];
		 char    AKYGEPNA[7];
		 char    AKYSABEZ[30];
		 char    AKYZEKS[1];
		 char    AKYHLNR[5];
		 char    AKYPSS[1];
		 char    AKYAGPCH[7];
		 char    AKYFILL2[9];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEAKY_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEAKY_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_F ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_F ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_F ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEAKY
 {
  public:

  DEAKY s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEAKY_BES, DEAKY_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEAKY_BES, DEAKY_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEAKY_BES, DEAKY_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEAKY()
  {
   ::buf_default((void *)&s, DEAKY_BES, DEAKY_ANZ);
  }
 };
#endif

