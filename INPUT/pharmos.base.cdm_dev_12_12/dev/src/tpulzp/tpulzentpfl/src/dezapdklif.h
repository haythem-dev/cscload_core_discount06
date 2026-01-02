/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKLIF_P09_ELEMENTE				10
 #define ANZ_DKLIF_P09_FELDER_PRO_ELEMENT	 2

 #define L_DEZAPDKLIF_ZAPSA20         2
 #define L_DEZAPDKLIF_ZAP20HNR        5
 #define L_DEZAPDKLIF_ZAP20KUBZ       30
 #define L_DEZAPDKLIF_ZAP20HNAME1     30
 #define L_DEZAPDKLIF_ZAP20HNAME2     30
 #define L_DEZAPDKLIF_ZAP20HPLZ       7
 #define L_DEZAPDKLIF_ZAP20HORT       30
 #define L_DEZAPDKLIF_ZAP20HSTR       30
 #define L_DEZAPDKLIF_ZAP20HTELNR     15
 #define L_DEZAPDKLIF_ZAP20HTFAX      15
 #define L_DEZAPDKLIF_ZAP20LKZ        3
 #define L_DEZAPDKLIF_ZAP20HBMERK     35
 #define L_DEZAPDKLIF_ZAP20HLOEKZ     1
 #define L_DEZAPDKLIF_ZAP20SHZDP      1
 #define L_DEZAPDKLIF_ZAP20PCODE      5
 #define L_DEZAPDKLIF_ZAP20PREISL     4
 #define L_DEZAPDKLIF_ZAP20RNAME1     30
 #define L_DEZAPDKLIF_ZAP20RPLZ       7
 #define L_DEZAPDKLIF_ZAP20RORT       30
 #define L_DEZAPDKLIF_ZAP20RSTR       30
 #define L_DEZAPDKLIF_ZAP20PAPA       5
 #define N_DEZAPDKLIF_ZAP20PAPA       2
 #define L_DEZAPDKLIF_ZAP20RNAME2     30
 #define L_DEZAPDKLIF_ZAP20P09ART     3
 #define L_DEZAPDKLIF_ZAP20P09WERT    5
 #define N_DEZAPDKLIF_ZAP20P09WERT    2
 #define L_DEZAPDKLIF_ZAP20FILLER     75

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKLIF_ANZ ( sizeof(DEZAPDKLIF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKLIF sizeof(struct DEZAPDKLIF)

 #define DEZAPDKLIF_H
 
 #define DEZAPDKLIFZAPSA20                  0
 #define DEZAPDKLIFZAP20HNR                 1
 #define DEZAPDKLIFZAP20KUBZ                2
 #define DEZAPDKLIFZAP20HNAME1              3
 #define DEZAPDKLIFZAP20HNAME2              4
 #define DEZAPDKLIFZAP20HPLZ                5
 #define DEZAPDKLIFZAP20HORT                6
 #define DEZAPDKLIFZAP20HSTR                7
 #define DEZAPDKLIFZAP20HTELNR              8
 #define DEZAPDKLIFZAP20HTFAX               9
 #define DEZAPDKLIFZAP20LKZ                 10
 #define DEZAPDKLIFZAP20HBMERK              11
 #define DEZAPDKLIFZAP20HLOEKZ              12
 #define DEZAPDKLIFZAP20SHZDP               13
 #define DEZAPDKLIFZAP20PCODE               14
 #define DEZAPDKLIFZAP20PREISL              15
 #define DEZAPDKLIFZAP20RNAME1              16
 #define DEZAPDKLIFZAP20RPLZ                17
 #define DEZAPDKLIFZAP20RORT                18
 #define DEZAPDKLIFZAP20RSTR                19
 #define DEZAPDKLIFZAP20PAPA                20
 #define DEZAPDKLIFZAP20RNAME2              21
 #define DEZAPDKLIFZAP20P09TAB              22
 #define DEZAPDKLIFZAP20FILLER              42

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKLIF_P09_ELEMENT 
 {
	char    ZAP20P09ART[3];
	char    ZAP20P09WERT[5];
 };

 struct O_DEZAPDKLIF {
		 char    ZAPSA20[2];
		 char    ZAP20HNR[5];
		 char    ZAP20KUBZ[30];
		 char    ZAP20HNAME1[30];
		 char    ZAP20HNAME2[30];
		 char    ZAP20HPLZ[7];
		 char    ZAP20HORT[30];
		 char    ZAP20HSTR[30];
		 char    ZAP20HTELNR[15];
		 char    ZAP20HTFAX[15];
		 char    ZAP20LKZ[3];
		 char    ZAP20HBMERK[35];
		 char    ZAP20HLOEKZ[1];
		 char    ZAP20SHZDP[1];
		 char    ZAP20PCODE[5];
		 char    ZAP20PREISL[4];
		 char    ZAP20RNAME1[30];
		 char    ZAP20RPLZ[7];
		 char    ZAP20RORT[30];
		 char    ZAP20RSTR[30];
		 char    ZAP20PAPA[5];
		 char    ZAP20RNAME2[30];
		 struct DKLIF_P09_ELEMENT	ZAP20PA09TAB[ANZ_DKLIF_P09_ELEMENTE]; 
		 char    ZAP20FILLER[75];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKLIF_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   35 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,   75 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKLIF_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   35 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   2 },
	 { TYP_C ,   75 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKLIF
 {
  public:

  DEZAPDKLIF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKLIF_BES, DEZAPDKLIF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKLIF_BES, DEZAPDKLIF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKLIF_BES, DEZAPDKLIF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKLIF()
  {
   ::buf_default((void *)&s, DEZAPDKLIF_BES, DEZAPDKLIF_ANZ);
  }
 };
#endif
