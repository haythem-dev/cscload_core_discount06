/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKSPS_ELEMENTE                2
 #define ANZ_DKSPS_FELDER_PRO_ELEMENT      10

 #define L_DEZAPDKSPS_ZAPSA52              2
 #define L_DEZAPDKSPS_ZAP52SPNR            5
 #define L_DEZAPDKSPS_ZAP52NAME            30
 #define L_DEZAPDKSPS_ZAP52STR             30
 #define L_DEZAPDKSPS_ZAP52PLZ             7
 #define L_DEZAPDKSPS_ZAP52ORT             30
 #define L_DEZAPDKSPS_ZAP52SIREN		   9
 #define L_DEZAPDKSPS_ZAP52TFILL1          1
 #define L_DEZAPDKSPS_ZAP52LOE             1
 #define L_DEZAPDKSPS_ZAP52TFILL2          14
 #define L_DEZAPDKSPS_ZAP52TFILL3          113
 #define L_DEZAPDKSPS_ZAP52FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKSPS_ANZ ( sizeof(DEZAPDKSPS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKSPS sizeof(struct DEZAPDKSPS)

 #define DEZAPDKSPS_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKSPSZAPSA52                       0
 #define DEZAPDKSPSZAP52SPNR                     1
 #define DEZAPDKSPSZAP52NAME                     2
 #define DEZAPDKSPSZAP52STR                      3
 #define DEZAPDKSPSZAP52PLZ                      4
 #define DEZAPDKSPSZAP52ORT                      5
 #define DEZAPDKSPSZAP52SIREN                    6
 #define DEZAPDKSPSZAP52TFILL1                   7
 #define DEZAPDKSPSZAP52LOE                      8
 #define DEZAPDKSPSZAP52TFILL2                   9
 #define DEZAPDKSPSZAP52TFILL3                   10
 #define DEZAPDKSPSZAP52FILLER                   21

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKSPS_ELEMENT 
 {
	char    ZAP52SPNR[5];
	char    ZAP52NAME[30];
	char    ZAP52STR[30];
	char    ZAP52PLZ[7];
	char    ZAP52ORT[30];
	char    ZAP52SIREN[9];
	char    ZAP52TFILL1[1];
	char    ZAP52LOE[1];
	char    ZAP52TFILL2[14];
	char    ZAP52TFILL3[113];
 };

 struct O_DEZAPDKSPS {
		 char					ZAPSA52[2];
		 struct DKSPS_ELEMENT	ZAP52TABELLE[ANZ_DKSPS_ELEMENTE]; 
		 char					ZAP52FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKSPS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,  113 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,  113 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKSPS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,  113 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,  113 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKSPS
 {
  public:

  DEZAPDKSPS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKSPS_BES, DEZAPDKSPS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKSPS_BES, DEZAPDKSPS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKSPS_BES, DEZAPDKSPS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKSPS()
  {
   ::buf_default((void *)&s, DEZAPDKSPS_BES, DEZAPDKSPS_ANZ);
  }
 };
#endif
