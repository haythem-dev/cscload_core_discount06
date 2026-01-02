/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKRAL_ELEMENTE                12
 #define ANZ_DKRAL_FELDER_PRO_ELEMENT      10

 #define L_DEZAPDKRAL_ZAPSA29              2
 #define L_DEZAPDKRAL_ZAP29FIL             2
 #define L_DEZAPDKRAL_ZAP29AART            2 
 #define L_DEZAPDKRAL_ZAP29SUBAA           3 
 #define L_DEZAPDKRAL_ZAP29EGR             3 
 #define L_DEZAPDKRAL_ZAP29ZAHLBED         4 
 #define L_DEZAPDKRAL_ZAP29MONRAB          5 
 #define N_DEZAPDKRAL_ZAP29MONRAB          2
 #define L_DEZAPDKRAL_ZAP29VALTAGE         3 
 #define L_DEZAPDKRAL_ZAP29TFILL1          1 
 #define L_DEZAPDKRAL_ZAP29LOEKZ           1
 #define L_DEZAPDKRAL_ZAP29TFILL2          19
 #define L_DEZAPDKRAL_ZAP29FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKRAL_ANZ ( sizeof(DEZAPDKRAL_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKRAL sizeof(struct DEZAPDKRAL)

 #define DEZAPDKRAL_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKRALZAPSA29                       0
 #define DEZAPDKRALZAP29FIL                      1
 #define DEZAPDKRALZAP29AART                     2
 #define DEZAPDKRALZAP29SUBAA                    3
 #define DEZAPDKRALZAP29EGR                      4
 #define DEZAPDKRALZAP29ZAHLBED                  5
 #define DEZAPDKRALZAP29MONRAB                   6
 #define DEZAPDKRALZAP29VALTAGE                  7
 #define DEZAPDKRALZAP29TFILL1                   8
 #define DEZAPDKRALZAP29LOEKZ                    9
 #define DEZAPDKRALZAP29TFILL2                   10
 #define DEZAPDKRALZAP29FILLER                   121

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKRAL_ELEMENT 
 {
	char    ZAP29FIL[2];
	char    ZAP29AART[2];
	char    ZAP29SUBAA[3];
	char    ZAP29EGR[3];
	char    ZAP29ZAHLBED[4];
	char    ZAP29MONRAB[5];
	char    ZAP29VALTAGE[3];
	char    ZAP29TFILL1[1];
	char    ZAP29LOEKZ[1];
	char    ZAP29TFILL2[19];
 };

 struct O_DEZAPDKRAL {
		 char					ZAPSA29[2];
		 struct DKRAL_ELEMENT	ZAP29TABELLE[ANZ_DKRAL_ELEMENTE]; 
		 char					ZAP29FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKRAL_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKRAL_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   19 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKRAL
 {
  public:

  DEZAPDKRAL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKRAL_BES, DEZAPDKRAL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKRAL_BES, DEZAPDKRAL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKRAL_BES, DEZAPDKRAL_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKRAL()
  {
   ::buf_default((void *)&s, DEZAPDKRAL_BES, DEZAPDKRAL_ANZ);
  }
 };
#endif

