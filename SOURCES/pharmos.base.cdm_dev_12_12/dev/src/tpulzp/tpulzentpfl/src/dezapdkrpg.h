/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKRPG_ELEMENTE                6
 #define ANZ_DKRPG_FELDER_PRO_ELEMENT      15

 #define L_DEZAPDKRPG_ZAPSA31              2
 #define L_DEZAPDKRPG_ZAP31FIL             2
 #define L_DEZAPDKRPG_ZAP31RPG             5
 #define L_DEZAPDKRPG_ZAP31PZN             7
 #define L_DEZAPDKRPG_ZAP31HNR             5
 #define L_DEZAPDKRPG_ZAP31FIL2            2
 #define L_DEZAPDKRPG_ZAP31PZN2            7
 #define L_DEZAPDKRPG_ZAP31HNR2            5
 #define L_DEZAPDKRPG_ZAP31IDF2            7
 #define L_DEZAPDKRPG_ZAP31RPG2            5
 #define L_DEZAPDKRPG_ZAP31TFILL0          4
 #define L_DEZAPDKRPG_ZAP31KOND            2
 #define L_DEZAPDKRPG_ZAP31TFILL1          1
 #define L_DEZAPDKRPG_ZAP31LOE             1
 #define L_DEZAPDKRPG_ZAP31GRPART          3
 #define L_DEZAPDKRPG_ZAP31TFILL2          24
 #define L_DEZAPDKRPG_ZAP31FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKRPG_ANZ ( sizeof(DEZAPDKRPG_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKRPG sizeof(struct DEZAPDKRPG)

 #define DEZAPDKRPG_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKRPGZAPSA31                       0
 #define DEZAPDKRPGZAP31FIL                      1
 #define DEZAPDKRPGZAP31RPG                      2
 #define DEZAPDKRPGZAP31PZN                      3
 #define DEZAPDKRPGZAP31HNR                      4
 #define DEZAPDKRPGZAP31FIL2                     5
 #define DEZAPDKRPGZAP31PZN2                     6
 #define DEZAPDKRPGZAP31HNR2                     7
 #define DEZAPDKRPGZAP31IDF2                     8
 #define DEZAPDKRPGZAP31RPG2                     9
 #define DEZAPDKRPGZAP31TFILL0                   10
 #define DEZAPDKRPGZAP31KOND                     11
 #define DEZAPDKRPGZAP31TFILL1                   12
 #define DEZAPDKRPGZAP31LOEKZ                    13
 #define DEZAPDKRPGZAP31GRPART                   14
 #define DEZAPDKRPGZAP31TFILL2                   15
 #define DEZAPDKRPGZAP31FILLER                   91

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKRPG_ELEMENT 
 {
	char    ZAP31FIL[2];
	char    ZAP31RPG[5];
	char    ZAP31PZN[7];
	char    ZAP31HNR[5];
	char    ZAP31FIL2[2];
	char    ZAP31PZN2[7];
	char    ZAP31HNR2[5];
	char    ZAP31IDF2[7];
	char    ZAP31RPG2[5];
	char    ZAP31TFILL0[4];
	char    ZAP31KOND[2];
	char    ZAP31TFILL1[1];
	char    ZAP31LOEKZ[1];
	char    ZAP31GRPART[3];
	char    ZAP31TFILL2[24];
 };

 struct O_DEZAPDKRPG {
		 char					ZAPSA31[2];
		 struct DKRPG_ELEMENT	ZAP31TABELLE[ANZ_DKRPG_ELEMENTE]; 
		 char					ZAP31FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKRPG_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKRPG_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };

#endif

#ifdef TRANSCLASS

 class CDEZAPDKRPG
 {
  public:

  DEZAPDKRPG s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKRPG_BES, DEZAPDKRPG_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKRPG_BES, DEZAPDKRPG_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKRPG_BES, DEZAPDKRPG_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKRPG()
  {
   ::buf_default((void *)&s, DEZAPDKRPG_BES, DEZAPDKRPG_ANZ);
  }
 };
#endif

