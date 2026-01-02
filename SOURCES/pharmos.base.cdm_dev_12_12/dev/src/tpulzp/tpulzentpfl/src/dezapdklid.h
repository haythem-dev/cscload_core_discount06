/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKLID_ELEMENTE                4 
 #define ANZ_DKLID_FELDER_PRO_ELEMENT      17

 #define L_DEZAPDKLID_ZAPSA25         2
 #define L_DEZAPDKLID_ZAP25HNR        5
 #define L_DEZAPDKLID_ZAP25KONTAKT    30
 #define L_DEZAPDKLID_ZAP25EDISPO     1 
 #define L_DEZAPDKLID_ZAP25MAWERT     7 
 #define L_DEZAPDKLID_ZAP25MAM1       3
 #define L_DEZAPDKLID_ZAP25MAM2       3 
 #define L_DEZAPDKLID_ZAP25MMZU       7 
 #define L_DEZAPDKLID_ZAP25MMZUW      7 
 #define L_DEZAPDKLID_ZAP25VKOST      7 
 #define L_DEZAPDKLID_ZAP25VKOSTW     7 
 #define L_DEZAPDKLID_ZAP25LZIEL      2 
 #define L_DEZAPDKLID_ZAP25RZIEL      2 
 #define L_DEZAPDKLID_ZAP25LZMIN      3
 #define L_DEZAPDKLID_ZAP25LZMAX      3
 #define L_DEZAPDKLID_ZAP25VART1      4
 #define L_DEZAPDKLID_ZAP25VART2      4
 #define L_DEZAPDKLID_ZAP25TEXT       40
 #define L_DEZAPDKLID_ZAP25FILLER     34 

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKLID_ANZ ( sizeof(DEZAPDKLID_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKLID sizeof(struct DEZAPDKLID)

 #define DEZAPDKLID_H
 
 #define DEZAPDKLIDZAPSA25                  0
 #define DEZAPDKLIDZAP25HNR                 1
 #define DEZAPDKLIDZAP25KONTAKT             2
 #define DEZAPDKLIDZAP25EDISPO              3
 #define DEZAPDKLIDZAP25MAWERT              4
 #define DEZAPDKLIDZAP25MAM1                5
 #define DEZAPDKLIDZAP25MAM2                6
 #define DEZAPDKLIDZAP25MMZU                7
 #define DEZAPDKLIDZAP25MMZUW               8
 #define DEZAPDKLIDZAP25VKOST               9
 #define DEZAPDKLIDZAP25VKOSTW              10
 #define DEZAPDKLIDZAP25LZIEL               11
 #define DEZAPDKLIDZAP25RZIEL               12
 #define DEZAPDKLIDZAP25LZMIN               13
 #define DEZAPDKLIDZAP25LZMAX               14
 #define DEZAPDKLIDZAP25VART1               15
 #define DEZAPDKLIDZAP25VART2               16
 #define DEZAPDKLIDZAP25TEXT                17
 #define DEZAPDKLIDZAP25FILLER              69

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKLID_ELEMENT 
 {
	char    ZAP25HNR[5];
	char    ZAP25KONTAKT[30];
	char    ZAP25EDISPO[1];
	char    ZAP25MAWERT[7];
	char    ZAP25MAM1[3];
	char    ZAP25MAM2[3];
	char    ZAP25MMZU[7];
	char    ZAP25MMZUW[7];
	char    ZAP25VKOST[7];
	char    ZAP25VKOSTW[7];
	char    ZAP25LZIEL[2];
	char    ZAP25RZIEL[2];
	char    ZAP25LZMIN[3];
	char    ZAP25LZMAX[3];
	char    ZAP25VART1[4];
	char    ZAP25VART2[4];
	char    ZAP25TEXT[40];
 };

 struct O_DEZAPDKLID {
		 char					ZAPSA25[2];
		 struct DKLID_ELEMENT	ZAP25TABELLE[ANZ_DKLID_ELEMENTE]; 
		 char					ZAP25FILLER[34];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKLID_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   34 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKLID_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   34 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKLID
 {
  public:

  DEZAPDKLID s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKLID_BES, DEZAPDKLID_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKLID_BES, DEZAPDKLID_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKLID_BES, DEZAPDKLID_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKLID()
  {
   ::buf_default((void *)&s, DEZAPDKLID_BES, DEZAPDKLID_ANZ);
  }
 };
#endif

