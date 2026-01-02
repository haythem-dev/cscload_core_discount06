/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKSER_ELEMENTE                5
 #define ANZ_DKSER_FELDER_PRO_ELEMENT      10

 #define L_DEZAPDKSER_ZAPSA30              2
 #define L_DEZAPDKSER_ZAP30FIL             2
 #define L_DEZAPDKSER_ZAP30SNR             3 
 #define L_DEZAPDKSER_ZAP30BEZ             30 
 #define L_DEZAPDKSER_ZAP30WERT            7
 #define N_DEZAPDKSER_ZAP30WERT            2
 #define L_DEZAPDKSER_ZAP30TXSCHL          2 
 #define L_DEZAPDKSER_ZAP30TFILL1          1 
 #define L_DEZAPDKSER_ZAP30LOEKZ           1
 #define L_DEZAPDKSER_ZAP30AEDAT           7 
 #define L_DEZAPDKSER_ZAP30STYP            5 
 #define L_DEZAPDKSER_ZAP30TFILL2          38
 #define L_DEZAPDKSER_ZAP30FILLER          48

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKSER_ANZ ( sizeof(DEZAPDKSER_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKSER sizeof(struct DEZAPDKSER)

 #define DEZAPDKSER_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKSERZAPSA30                       0
 #define DEZAPDKSERZAP30FIL                      1
 #define DEZAPDKSERZAP30SNR                      2
 #define DEZAPDKSERZAP30BEZ                      3
 #define DEZAPDKSERZAP30WERT	                 4
 #define DEZAPDKSERZAP30TXSCHL                   5
 #define DEZAPDKSERZAP30TFILL1                   6
 #define DEZAPDKSERZAP30LOEKZ                    7
 #define DEZAPDKSERZAP30AEDAT	                 8
 #define DEZAPDKSERZAP30STYP	                 9
 #define DEZAPDKSERZAP30TFILL2                   10
 #define DEZAPDKSERZAP30FILLER                   51

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKSER_ELEMENT 
 {
	char    ZAP30FIL[2];
	char    ZAP30SNR[3];
	char    ZAP30BEZ[30];
	char    ZAP30WERT[7];
	char    ZAP30TXSCHL[2];
	char    ZAP30TFILL1[1];
	char    ZAP30LOEKZ[1];
	char    ZAP30AEDAT[7];
	char    ZAP30STYP[5];
	char    ZAP30TFILL2[38];
 };

 struct O_DEZAPDKSER {
		 char					ZAPSA30[2];
		 struct DKSER_ELEMENT	ZAP30TABELLE[ANZ_DKSER_ELEMENTE]; 
		 char					ZAP30FILLER[48];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKSER_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKSER_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   38 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKSER
 {
  public:

  DEZAPDKSER s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKSER_BES, DEZAPDKSER_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKSER_BES, DEZAPDKSER_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKSER_BES, DEZAPDKSER_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKSER()
  {
   ::buf_default((void *)&s, DEZAPDKSER_BES, DEZAPDKSER_ANZ);
  }
 };
#endif
