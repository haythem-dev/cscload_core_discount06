/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKRAB_ELEMENTE                2
 #define ANZ_DKRAB_FELDER_PRO_ELEMENT      38

 #define L_DEZAPDKRAB_ZAPSA28              2
 #define L_DEZAPDKRAB_ZAP28FIL             2
 #define L_DEZAPDKRAB_ZAP28PZN             7
 #define L_DEZAPDKRAB_ZAP28RGN             5
 #define L_DEZAPDKRAB_ZAP28HNR             5
 #define L_DEZAPDKRAB_ZAP28AGN             5
 #define L_DEZAPDKRAB_ZAP28EGR             3
 #define L_DEZAPDKRAB_ZAP28IDF             7
 #define L_DEZAPDKRAB_ZAP28BASIS           5
 #define L_DEZAPDKRAB_ZAP28BASWERT         8
 #define N_DEZAPDKRAB_ZAP28BASWERT         2
 #define L_DEZAPDKRAB_ZAP28BASMULT         5
 #define L_DEZAPDKRAB_ZAP28DABE            8
 #define L_DEZAPDKRAB_ZAP28DAEN            8
 #define L_DEZAPDKRAB_ZAP28RGT             3
 #define L_DEZAPDKRAB_ZAP28RABTYP          3 
 #define L_DEZAPDKRAB_ZAP28RABSPEZ         3
 #define L_DEZAPDKRAB_ZAP28ZZNR            2
 #define L_DEZAPDKRAB_ZAP28NRMENG          5 
 #define L_DEZAPDKRAB_ZAP28PROZWERT        5 
 #define N_DEZAPDKRAB_ZAP28PROZWERT        2
 #define L_DEZAPDKRAB_ZAP28PROZMENG        5 
 #define N_DEZAPDKRAB_ZAP28PROZMENG        2
 #define L_DEZAPDKRAB_ZAP28AUFSCHLAG       5 
 #define N_DEZAPDKRAB_ZAP28AUFSCHLAG       2
 #define L_DEZAPDKRAB_ZAP28NGEG1           3
 #define L_DEZAPDKRAB_ZAP28NGEG2           3
 #define L_DEZAPDKRAB_ZAP28NGEG3           3
 #define L_DEZAPDKRAB_ZAP28FIXPREIS        7
 #define N_DEZAPDKRAB_ZAP28FIXPREIS        2
 #define L_DEZAPDKRAB_ZAP28PROZERST        5
 #define N_DEZAPDKRAB_ZAP28PROZERST        2
 #define L_DEZAPDKRAB_ZAP28INTERN          1
 #define L_DEZAPDKRAB_ZAP28MONRAB          1
 #define L_DEZAPDKRAB_ZAP28NRPZN           7
 #define L_DEZAPDKRAB_ZAP28TFILL1          1
 #define L_DEZAPDKRAB_ZAP28LOE             1
 #define L_DEZAPDKRAB_ZAP28NOPROP          1
 #define L_DEZAPDKRAB_ZAP28FIXWERT         7
 #define N_DEZAPDKRAB_ZAP28FIXWERT         2
 #define L_DEZAPDKRAB_ZAP28ROHERTR         5
 #define N_DEZAPDKRAB_ZAP28ROHERTR         2
 #define L_DEZAPDKRAB_ZAP28ZURABOK         1
 #define L_DEZAPDKRAB_ZAP28ZAHLART         1
 #define L_DEZAPDKRAB_ZAP28ERSTTYP         3
 #define L_DEZAPDKRAB_ZAP28STPZN           7
 #define L_DEZAPDKRAB_ZAP28TFILL2          69
 #define L_DEZAPDKRAB_ZAP28FILLER          98

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKRAB_ANZ ( sizeof(DEZAPDKRAB_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKRAB sizeof(struct DEZAPDKRAB)

 #define DEZAPDKRAB_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKRABZAPSA28                       0
 #define DEZAPDKRABZAP28FIL                      1
 #define DEZAPDKRABZAP28PZN                      2
 #define DEZAPDKRABZAP28RGN                      3
 #define DEZAPDKRABZAP28HNR                      4
 #define DEZAPDKRABZAP28AGN                      5
 #define DEZAPDKRABZAP28EGR                      6
 #define DEZAPDKRABZAP28IDF                      7
 #define DEZAPDKRABZAP28BASIS                    8
 #define DEZAPDKRABZAP28BASWERT                  9
 #define DEZAPDKRABZAP28BASMULT                  10 
 #define DEZAPDKRABZAP28DABE                     11
 #define DEZAPDKRABZAP28DAEN                     12
 #define DEZAPDKRABZAP28RGT                      13
 #define DEZAPDKRABZAP28RABTYP                   14
 #define DEZAPDKRABZAP28RABSPEZ                  15
 #define DEZAPDKRABZAP28ZZNR                     16
 #define DEZAPDKRABZAP28NRMENG                   17
 #define DEZAPDKRABZAP28PROZWERT                 18
 #define DEZAPDKRABZAP28PROZMENG                 19
 #define DEZAPDKRABZAP28AUFSCHLAG                20
 #define DEZAPDKRABZAP28NGEG1                    21
 #define DEZAPDKRABZAP28NGEG2                    22
 #define DEZAPDKRABZAP28NGEG3                    23
 #define DEZAPDKRABZAP28FIXPREIS                 24
 #define DEZAPDKRABZAP28PROZERST                 25
 #define DEZAPDKRABZAP28INTERN                   26
 #define DEZAPDKRABZAP28MONRAB                   27
 #define DEZAPDKRABZAP28NRPZN                    28
 #define DEZAPDKRABZAP28TFILL1                   29
 #define DEZAPDKRABZAP28LOEKZ                    30  
 #define DEZAPDKRABZAP28NOPROP                   31  
 #define DEZAPDKRABZAP28FIXWERT                  32
 #define DEZAPDKRABZAP28ROHERTR                  33
 #define DEZAPDKRABZAP28ZURABOK                  34
 #define DEZAPDKRABZAP28ZAHLART                  35
 #define DEZAPDKRABZAP28ERSTTYP                  36
 #define DEZAPDKRABZAP28STPZN                    37
 #define DEZAPDKRABZAP28TFILL2                   38 
 #define DEZAPDKRABZAP28FILLER                   77

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKRAB_ELEMENT 
 {
	char    ZAP28FIL[2];
	char    ZAP28PZN[7];
	char    ZAP28RGN[5];
	char    ZAP28HNR[5];
	char    ZAP28AGN[5];
	char    ZAP28EGR[3];
	char    ZAP28IDF[7];
	char    ZAP28BASIS[5];
	char    ZAP28BASWERT[8];
	char    ZAP28BASMULT[5];
	char    ZAP28DABE[8];
	char    ZAP28DAEN[8];
	char    ZAP28RGT[3];
	char    ZAP28RABTYP[3];
	char    ZAP28RABSPEZ[3];
	char    ZAP28ZZNR[2];
	char    ZAP28NRMENG[5];
	char    ZAP28PROZWERT[5];
	char    ZAP28PROZMENG[5];
	char    ZAP28AUFSCHLAG[5];
	char    ZAP28NGEG1[3];
	char    ZAP28NGEG2[3];
	char    ZAP28NGEG3[3];
	char    ZAP28FIXPREIS[7];
	char    ZAP28PROZERST[5];
	char    ZAP28INTERN[1];
	char    ZAP28MONRAB[1];
	char    ZAP28NRPZN[7];
	char    ZAP28TFILL1[1];
	char    ZAP28LOEKZ[1];
	char    ZAP28NOPROP[1];
	char    ZAP28FIXWERT[7];
	char    ZAP28ROHERTR[5];
	char    ZAP28ZURABOK[1];
	char    ZAP28ZAHLART[1];
	char    ZAP28ERSTTYP[3];
	char    ZAP28STPZN[7];
	char    ZAP28TFILL2[69];
 };

 struct O_DEZAPDKRAB {
		 char					ZAPSA28[2];
		 struct DKRAB_ELEMENT	ZAP28TABELLE[ANZ_DKRAB_ELEMENTE]; 
		 char					ZAP28FILLER[98];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKRAB_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   69 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   69 ,   0 },
	 { TYP_C ,   98 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKRAB_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   69 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   69 ,   0 },
	 { TYP_C ,   98 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKRAB
 {
  public:

  DEZAPDKRAB s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKRAB_BES, DEZAPDKRAB_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKRAB_BES, DEZAPDKRAB_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKRAB_BES, DEZAPDKRAB_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKRAB()
  {
   ::buf_default((void *)&s, DEZAPDKRAB_BES, DEZAPDKRAB_ANZ);
  }
 };
#endif

