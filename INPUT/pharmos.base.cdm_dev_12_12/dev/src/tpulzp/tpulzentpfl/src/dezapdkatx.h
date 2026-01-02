/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKATX_ELEMENTE                3
 #define ANZ_DKATX_FELDER_PRO_ELEMENT      11

 #define L_DEZAPDKATX_ZAPSA21              2
 #define L_DEZAPDKATX_ZAP21FIL             2
 #define L_DEZAPDKATX_ZAP21TXSCHL          2
 #define L_DEZAPDKATX_ZAP21TEXT1           30
 #define L_DEZAPDKATX_ZAP21TEXT2           30
 #define L_DEZAPDKATX_ZAP21DRRE            1
 #define L_DEZAPDKATX_ZAP21DRKB            1
 #define L_DEZAPDKATX_ZAP21ANKS            1
 #define L_DEZAPDKATX_ZAP21DRBV            1
 #define L_DEZAPDKATX_ZAP21TFILL1          3
 #define L_DEZAPDKATX_ZAP21LOE             1
 #define L_DEZAPDKATX_ZAP21TFILL2          78
 #define L_DEZAPDKATX_ZAP21FILLER          48

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKATX_ANZ ( sizeof(DEZAPDKATX_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKATX sizeof(struct DEZAPDKATX)

 #define DEZAPDKATX_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKATXZAPSA21                       0
 #define DEZAPDKATXZAP21FIL                      1
 #define DEZAPDKATXZAP21TXSCHL                   2
 #define DEZAPDKATXZAP21TEXT1                    3
 #define DEZAPDKATXZAP21TEXT2                    4
 #define DEZAPDKATXZAP21DRRE                     5
 #define DEZAPDKATXZAP21DRKB                     6
 #define DEZAPDKATXZAP21ANKS                     7
 #define DEZAPDKATXZAP21DRBV                     8
 #define DEZAPDKATXZAP21TFILL1                   9
 #define DEZAPDKATXZAP21LOEKZ                    10
 #define DEZAPDKATXZAP21TFILL2                   11
 #define DEZAPDKATXZAP21FILLER                   34

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKATX_ELEMENT 
 {
	char    ZAP21FIL[2];
	char    ZAP21TXSCHL[2];
	char    ZAP21TEXT1[30];
	char    ZAP21TEXT2[30];
	char    ZAP21DRRE[1];
	char    ZAP21DRKB[1];
	char    ZAP21ANKS[1];
	char    ZAP21DRBV[1];
	char    ZAP21TFILL1[3];
	char    ZAP21LOEKZ[1];
	char    ZAP21TFILL2[78];
 };

 struct O_DEZAPDKATX {
		 char					ZAPSA21[2];
		 struct DKATX_ELEMENT	ZAP21TABELLE[ANZ_DKATX_ELEMENTE]; 
		 char					ZAP21FILLER[48];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKATX_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   78 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   78 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   78 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKATX_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   78 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   78 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   78 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKATX
 {
  public:

  DEZAPDKATX s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKATX_BES, DEZAPDKATX_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKATX_BES, DEZAPDKATX_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKATX_BES, DEZAPDKATX_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKATX()
  {
   ::buf_default((void *)&s, DEZAPDKATX_BES, DEZAPDKATX_ANZ);
  }
 };
#endif

