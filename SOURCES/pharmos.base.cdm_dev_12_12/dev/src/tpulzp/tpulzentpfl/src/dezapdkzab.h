/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKZAB_ELEMENTE                4
 #define ANZ_DKZAB_FELDER_PRO_ELEMENT      15

 #define L_DEZAPDKZAB_ZAPSA27              2
 #define L_DEZAPDKZAB_ZAP27BEDI            4
 #define L_DEZAPDKZAB_ZAP27LST1            3 
 #define L_DEZAPDKZAB_ZAP27LST2            3 
 #define L_DEZAPDKZAB_ZAP27LST3            3 
 #define L_DEZAPDKZAB_ZAP27SKMP            5 
 #define N_DEZAPDKZAB_ZAP27SKMP            2
 #define L_DEZAPDKZAB_ZAP27SKHMP           5 
 #define N_DEZAPDKZAB_ZAP27SKHMP           2
 #define L_DEZAPDKZAB_ZAP27SDEKA           5 
 #define N_DEZAPDKZAB_ZAP27SDEKA           2
 #define L_DEZAPDKZAB_ZAP27TFILL1          5 
 #define L_DEZAPDKZAB_ZAP27LOEKZ           1
 #define L_DEZAPDKZAB_ZAP27TFILL2          10
 #define L_DEZAPDKZAB_ZAP27NTAG            3
 #define L_DEZAPDKZAB_ZAP27TFILL3          1
 #define L_DEZAPDKZAB_ZAP27LST0            3 
 #define L_DEZAPDKZAB_ZAP27SKWO            5 
 #define N_DEZAPDKZAB_ZAP27SKWO            2
 #define L_DEZAPDKZAB_ZAP27TFILL4          53
 #define L_DEZAPDKZAB_ZAP27FILLER          98

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKZAB_ANZ ( sizeof(DEZAPDKZAB_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKZAB sizeof(struct DEZAPDKZAB)

 #define DEZAPDKZAB_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKZABZAPSA27                       0
 #define DEZAPDKZABZAP27BEDI                     1
 #define DEZAPDKZABZAP27LST1                     2
 #define DEZAPDKZABZAP27LST2                     3
 #define DEZAPDKZABZAP27LST3                     4
 #define DEZAPDKZABZAP27SKMP                     5
 #define DEZAPDKZABZAP27SKHMP                    6
 #define DEZAPDKZABZAP27SDEKA                    7
 #define DEZAPDKZABZAP27TFILL1                   8
 #define DEZAPDKZABZAP27LOEKZ                    9
 #define DEZAPDKZABZAP27TFILL2                   10
 #define DEZAPDKZABZAP27NTAG                     11
 #define DEZAPDKZABZAP27TFILL3                   12
 #define DEZAPDKZABZAP27LST0                     13
 #define DEZAPDKZABZAP27SKWO                     14
 #define DEZAPDKZABZAP27TFILL4                   15
 #define DEZAPDKZABZAP27FILLER                   61

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKZAB_ELEMENT 
 {
	char    ZAP27BEDI[4];
	char    ZAP27LST1[3];
	char    ZAP27LST2[3];
	char    ZAP27LST3[3];
	char    ZAP27SKMP[5];
	char    ZAP27SKHMP[5];
	char    ZAP27SDEKA[5];
	char    ZAP27TFILL1[5];
	char    ZAP27LOEKZ[1];
	char    ZAP27TFILL2[10];
	char    ZAP27NTAG[3];
	char    ZAP27TFILL3[1];
	char    ZAP27LST0[3];
	char    ZAP27SKWO[5];
	char    ZAP27TFILL4[53];
 };

 struct O_DEZAPDKZAB {
		 char					ZAPSA27[2];
		 struct DKZAB_ELEMENT	ZAP27TABELLE[ANZ_DKZAB_ELEMENTE]; 
		 char					ZAP27FILLER[98];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKZAB_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,   53 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,   53 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,   53 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,   53 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKZAB_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,   53 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,   53 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,   53 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,   53 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKZAB
 {
  public:

  DEZAPDKZAB s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKZAB_BES, DEZAPDKZAB_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKZAB_BES, DEZAPDKZAB_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKZAB_BES, DEZAPDKZAB_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKZAB()
  {
   ::buf_default((void *)&s, DEZAPDKZAB_BES, DEZAPDKZAB_ANZ);
  }
 };
#endif

