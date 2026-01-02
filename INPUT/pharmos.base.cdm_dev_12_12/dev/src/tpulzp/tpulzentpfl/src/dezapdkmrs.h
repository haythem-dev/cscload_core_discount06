/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKMRS_ELEMENTE                3
 #define ANZ_DKMRS_FELDER_PRO_ELEMENT      28

 #define L_DEZAPDKMRS_ZAPSA36              2
 #define L_DEZAPDKMRS_ZAP36MORASO          3
 #define L_DEZAPDKMRS_ZAP36OBER            30
 #define L_DEZAPDKMRS_ZAP36BEZ             30
 #define L_DEZAPDKMRS_ZAP36TFILL1          1
 #define L_DEZAPDKMRS_ZAP36LOEKZ           1
 #define L_DEZAPDKMRS_ZAP36PROG            6
 #define L_DEZAPDKMRS_ZAP36RABART          2
 #define L_DEZAPDKMRS_ZAP36SKF			   2
 #define L_DEZAPDKMRS_ZAP36TYP			   2
 #define L_DEZAPDKMRS_ZAP36UMSBAS    	   2
 #define L_DEZAPDKMRS_ZAP36SOCKEL		   2
 #define L_DEZAPDKMRS_ZAP36DECKRP          5
 #define N_DEZAPDKMRS_ZAP36DECKRP          2
 #define L_DEZAPDKMRS_ZAP36DECKRS          7
 #define N_DEZAPDKMRS_ZAP36DECKRS          2
 #define L_DEZAPDKMRS_ZAP36KRABBU		   2
 #define L_DEZAPDKMRS_ZAP36STFORM		   2
 #define L_DEZAPDKMRS_ZAP36UMBUCH		   2
 #define L_DEZAPDKMRS_ZAP36SOSKOTYP		   2
 #define L_DEZAPDKMRS_ZAP36SOSKOPROZ       5
 #define N_DEZAPDKMRS_ZAP36SOSKOPROZ       2
 #define L_DEZAPDKMRS_ZAP36SOSKOPROG       6
 #define L_DEZAPDKMRS_ZAP36GDPAUS		   4
 #define L_DEZAPDKMRS_ZAP36KVAREL		   2
 #define L_DEZAPDKMRS_ZAP36FILAPO		   2
 #define L_DEZAPDKMRS_ZAP36DECKITRBB	   3
 #define L_DEZAPDKMRS_ZAP36USREDUZ		   2
 #define L_DEZAPDKMRS_ZAP36HOPR 		   1
 #define L_DEZAPDKMRS_ZAP36RRBERART		   2
 #define L_DEZAPDKMRS_ZAP36KEINENV		   1
 #define L_DEZAPDKMRS_ZAP36TFILL2          21
 #define L_DEZAPDKMRS_ZAP36FILLER          48

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKMRS_ANZ ( sizeof(DEZAPDKMRS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKMRS sizeof(struct DEZAPDKMRS)

 #define DEZAPDKMRS_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKMRSZAPSA36                       0
 #define DEZAPDKMRSZAP36MORASO                   1
 #define DEZAPDKMRSZAP36OBER                     2
 #define DEZAPDKMRSZAP36BEZ                      3
 #define DEZAPDKMRSZAP36TFILL1                   4
 #define DEZAPDKMRSZAP36LOEKZ                    5
 #define DEZAPDKMRSZAP36PROG                     6
 #define DEZAPDKMRSZAP36RABART                   7
 #define DEZAPDKMRSZAP36SKF                      8
 #define DEZAPDKMRSZAP36TYP                      9
 #define DEZAPDKMRSZAP36UMSBAS                   10
 #define DEZAPDKMRSZAP36SOCKEL                   11
 #define DEZAPDKMRSZAP36DECKRP                   12
 #define DEZAPDKMRSZAP36DECKRS                   13
 #define DEZAPDKMRSZAP36KRABBU                   14
 #define DEZAPDKMRSZAP36STFORM                   15
 #define DEZAPDKMRSZAP36UMBUCH                   16
 #define DEZAPDKMRSZAP36SOSKOTYP                 17
 #define DEZAPDKMRSZAP36SOSKOPROZ                18
 #define DEZAPDKMRSZAP36SOSKOPROG                19
 #define DEZAPDKMRSZAP36GDPAUS		             20
 #define DEZAPDKMRSZAP36KVAREL	                 21
 #define DEZAPDKMRSZAP36FILAPO	                 22
 #define DEZAPDKMRSZAP36DECKITRBB                23
 #define DEZAPDKMRSZAP36USREDUZ	                 24
 #define DEZAPDKMRSZAP36HOPR	                 25
 #define DEZAPDKMRSZAP36RRBERART                 26
 #define DEZAPDKMRSZAP36KEINENV                  27
 #define DEZAPDKMRSZAP36TFILL2                   28
 #define DEZAPDKMRSZAP36FILLER                   85

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKMRS_ELEMENT 
 {
	char    ZAP36MORASO[3];
	char    ZAP36OBER[30];
	char    ZAP36BEZ[30];
	char    ZAP36TFILL1[1];
	char    ZAP36LOEKZ[1];
	char    ZAP36PROG[6];
	char    ZAP36RABART[2];
	char    ZAP36SKF[2];
	char    ZAP36TYP[2];
	char    ZAP36UMSBAS[2];
	char    ZAP36SOCKEL[2];
	char    ZAP36DECKRP[5];
	char    ZAP36DECKRS[7];
	char    ZAP36KRABBU[2];
	char    ZAP36STFORM[2];
	char    ZAP36UMBUCH[2];
	char    ZAP36SOSKOTYP[2];
	char    ZAP36SOSKOPROZ[5];
	char    ZAP36SOSKOPROG[6];
	char    ZAP36GDPAUS[4];
	char    ZAP36KVAREL[2];
	char    ZAP36FILAPO[2];
	char    ZAP36DECKITRBB[3];
	char    ZAP36USREDUZ[2];
	char    ZAP36HOPR[1];
	char    ZAP36RRBERART[2];
	char    ZAP36KEINENV[1];
	char    ZAP36TFILL2[21];
 };

 struct O_DEZAPDKMRS {
		 char					ZAPSA36[2];
		 struct DKMRS_ELEMENT	ZAP36TABELLE[ANZ_DKMRS_ELEMENTE]; 
		 char					ZAP36FILLER[48];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKMRS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKMRS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKMRS
 {
  public:

  DEZAPDKMRS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKMRS_BES, DEZAPDKMRS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKMRS_BES, DEZAPDKMRS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKMRS_BES, DEZAPDKMRS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKMRS()
  {
   ::buf_default((void *)&s, DEZAPDKMRS_BES, DEZAPDKMRS_ANZ);
  }
 };
#endif
