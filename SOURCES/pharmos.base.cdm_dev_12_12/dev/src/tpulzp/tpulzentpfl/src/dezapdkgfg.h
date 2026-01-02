/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DEZAPDKGFG_ZAPSA10              2
 #define L_DEZAPDKGFG_ZAP10FIL             2
 #define L_DEZAPDKGFG_ZAP10PZN             7
 #define L_DEZAPDKGFG_ZAP10TFILL1          14
 #define L_DEZAPDKGFG_ZAP10UNNR            4
 #define L_DEZAPDKGFG_ZAP10KLA             3
 #define L_DEZAPDKGFG_ZAP10ZIF             2
 #define L_DEZAPDKGFG_ZAP10ALPHA           3
 #define L_DEZAPDKGFG_ZAP10TFILL2          174
 #define L_DEZAPDKGFG_ZAP10VBF	           4
 #define L_DEZAPDKGFG_ZAP10WGK	           2
 #define L_DEZAPDKGFG_ZAP10TFILL3          4
 #define L_DEZAPDKGFG_ZAP10VCI	           4
 #define L_DEZAPDKGFG_ZAP10GSFP            1
 #define L_DEZAPDKGFG_ZAP10GSF             1
 #define L_DEZAPDKGFG_ZAP10GSE             1
 #define L_DEZAPDKGFG_ZAP10GSO             1
 #define L_DEZAPDKGFG_ZAP10GSC             1
 #define L_DEZAPDKGFG_ZAP10GSTP            1
 #define L_DEZAPDKGFG_ZAP10GST             1
 #define L_DEZAPDKGFG_ZAP10GSXN            1
 #define L_DEZAPDKGFG_ZAP10GSXI            1
 #define L_DEZAPDKGFG_ZAP10GSN             1  
 #define L_DEZAPDKGFG_ZAP10TFILL4          167
 #define L_DEZAPDKGFG_ZAP10FILLER          98

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKGFG_ANZ ( sizeof(DEZAPDKGFG_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKGFG sizeof(struct DEZAPDKGFG)

 #define DEZAPDKGFG_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKGFGZAPSA10                       0
 #define DEZAPDKGFGZAP10FIL                      1
 #define DEZAPDKGFGZAP10PZN                      2
 #define DEZAPDKGFGZAP10TFILL1                   3
 #define DEZAPDKGFGZAP10UNNR                     4
 #define DEZAPDKGFGZAP10KLA                      5
 #define DEZAPDKGFGZAP10ZIF                      6
 #define DEZAPDKGFGZAP10ALPHA                    7
 #define DEZAPDKGFGZAP10TFILL2                   8
 #define DEZAPDKGFGZAP10VBF                      9
 #define DEZAPDKGFGZAP10WGK                      10
 #define DEZAPDKGFGZAP10TFILL3                   11
 #define DEZAPDKGFGZAP10VCI                      12
 #define DEZAPDKGFGZAP10GSFP                     13
 #define DEZAPDKGFGZAP10GSF                      14
 #define DEZAPDKGFGZAP10GSE                      15
 #define DEZAPDKGFGZAP10GSO                      16
 #define DEZAPDKGFGZAP10GSC                      17
 #define DEZAPDKGFGZAP10GSTP                     18
 #define DEZAPDKGFGZAP10GST                      19
 #define DEZAPDKGFGZAP10GSXN                     20
 #define DEZAPDKGFGZAP10GSXI                     21
 #define DEZAPDKGFGZAP10GSN                      22
 #define DEZAPDKGFGZAP10TFILL4                   23
 #define DEZAPDKGFGZAP10FILLER                   24

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct O_DEZAPDKGFG {
		 char					ZAPSA10[2];
		 char    ZAP10FIL[2];
		 char    ZAP10PZN[7];
		 char    ZAP10TFILL1[14];
		 char    ZAP10UNNR[4];
		 char    ZAP10KLA[3];
		 char    ZAP10ZIF[2];
		 char    ZAP10ALPHA[3];
		 char    ZAP10TFILL2[174];
		 char    ZAP10VBF[4];
		 char    ZAP10WGK[2];
		 char    ZAP10TFILL3[4];
		 char    ZAP10VCI[4];
		 char    ZAP10GSFP[1];
		 char    ZAP10GSF[1];
		 char    ZAP10GSE[1];
		 char    ZAP10GSO[1];
		 char    ZAP10GSC[1];
		 char    ZAP10GSTP[1];
		 char    ZAP10GST[1];
		 char    ZAP10GSXN[1];
		 char    ZAP10GSXI[1];
		 char    ZAP10GSN[1];
		 char    ZAP10TFILL4[167];
		 char 	 ZAP10FILLER[98];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKGFG_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,  174 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,  167 ,   0 },
	 { TYP_C ,   98 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKGFG_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,  174 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,  167 ,   0 },
	 { TYP_C ,   98 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKGFG
 {
  public:

  DEZAPDKGFG s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKGFG_BES, DEZAPDKGFG_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKGFG_BES, DEZAPDKGFG_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKGFG_BES, DEZAPDKGFG_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKGFG()
  {
   ::buf_default((void *)&s, DEZAPDKGFG_BES, DEZAPDKGFG_ANZ);
  }
 };
#endif
