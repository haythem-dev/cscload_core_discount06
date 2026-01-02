/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKSTE_ELEMENTE                6
 #define ANZ_DKSTE_FELDER_PRO_ELEMENT      10

 #define L_DEZAPDKSTE_ZAPSA13              2
 #define L_DEZAPDKSTE_ZAP13FIL             2
 #define L_DEZAPDKSTE_ZAP13PZN             7
 #define L_DEZAPDKSTE_ZAP13EPZN            7
 #define L_DEZAPDKSTE_ZAP13EMEN            5
 #define L_DEZAPDKSTE_ZAP13TFILL1          1
 #define L_DEZAPDKSTE_ZAP13LOE             1
 #define L_DEZAPDKSTE_ZAP13DATVON          8
 #define L_DEZAPDKSTE_ZAP13DATBIS          8
 #define L_DEZAPDKSTE_ZAP13TYP             3
 #define L_DEZAPDKSTE_ZAP13TFILL2          38
 #define L_DEZAPDKSTE_ZAP13FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKSTE_ANZ ( sizeof(DEZAPDKSTE_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKSTE sizeof(struct DEZAPDKSTE)

 #define DEZAPDKSTE_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKSTEZAPSA13                       0
 #define DEZAPDKSTEZAP13FIL                      1
 #define DEZAPDKSTEZAP13PZN                      2
 #define DEZAPDKSTEZAP13EPZN                     3
 #define DEZAPDKSTEZAP13EMEN                     4
 #define DEZAPDKSTEZAP13TFILL1                   5
 #define DEZAPDKSTEZAP13LOEKZ                    6
 #define DEZAPDKSTEZAP13DATVON                   7
 #define DEZAPDKSTEZAP13DATBIS                   8
 #define DEZAPDKSTEZAP13TYP                      9
 #define DEZAPDKSTEZAP13TFILL2                   10
 #define DEZAPDKSTEZAP13FILLER                   61

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKSTE_ELEMENT 
 {
	char    ZAP13FIL[2];
	char    ZAP13PZN[7];
	char    ZAP13EPZN[7];
	char    ZAP13EMEN[5];
	char    ZAP13TFILL1[1];
	char    ZAP13LOEKZ[1];
	char    ZAP13DATVON[8];
	char    ZAP13DATBIS[8];
	char    ZAP13TYP[3];
	char    ZAP13TFILL2[38];
 };

 struct O_DEZAPDKSTE {
		 char					ZAPSA13[2];
		 struct DKSTE_ELEMENT	ZAP13TABELLE[ANZ_DKSTE_ELEMENTE]; 
		 char					ZAP13FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKSTE_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKSTE_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKSTE
 {
  public:

  DEZAPDKSTE s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKSTE_BES, DEZAPDKSTE_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKSTE_BES, DEZAPDKSTE_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKSTE_BES, DEZAPDKSTE_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKSTE()
  {
   ::buf_default((void *)&s, DEZAPDKSTE_BES, DEZAPDKSTE_ANZ);
  }
 };
#endif
