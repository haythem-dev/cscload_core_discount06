/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKPRO_ELEMENTE                6
 #define ANZ_DKPRO_FELDER_PRO_ELEMENT      11

 #define L_DEZAPDKPRO_ZAPSA54              2
 #define L_DEZAPDKPRO_ZAP54PROMONR         5
 #define L_DEZAPDKPRO_ZAP54NAME            30
 #define L_DEZAPDKPRO_ZAP54TYP			   2
 #define L_DEZAPDKPRO_ZAP54KZKOPR	   	   1
 #define L_DEZAPDKPRO_ZAP54KZKOSR	   	   1
 #define L_DEZAPDKPRO_ZAP54PRIO			   3
 #define L_DEZAPDKPRO_ZAP54KZNSWEB    	   1
 #define L_DEZAPDKPRO_ZAP54TFILL1          1
 #define L_DEZAPDKPRO_ZAP54LOE             1
 #define L_DEZAPDKPRO_ZAP54TFILL2          14
 #define L_DEZAPDKPRO_ZAP54TFILL3          21
 #define L_DEZAPDKPRO_ZAP54FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKPRO_ANZ ( sizeof(DEZAPDKPRO_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKPRO sizeof(struct DEZAPDKPRO)

 #define DEZAPDKPRO_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKPROZAPSA54                       0
 #define DEZAPDKPROZAP54PROMONR                  1
 #define DEZAPDKPROZAP54NAME                     2
 #define DEZAPDKPROZAP54TYP                      3
 #define DEZAPDKPROZAP54KZKOPR                   4
 #define DEZAPDKPROZAP54KZKOSR                   5
 #define DEZAPDKPROZAP54PRIO                     6
 #define DEZAPDKPROZAP54KZNSWEB                  7
 #define DEZAPDKPROZAP54TFILL1                   8
 #define DEZAPDKPROZAP54LOE                      9
 #define DEZAPDKPROZAP54TFILL2                   10
 #define DEZAPDKPROZAP54TFILL3                   11
 #define DEZAPDKPROZAP54FILLER                   67

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKPRO_ELEMENT 
 {
	char    ZAP54PROMONR[5];
	char    ZAP54NAME[30];
	char    ZAP54TYP[2];
	char    ZAP54KZKOPR[1];
	char    ZAP54KZKOSR[1];
	char    ZAP54PRIO[3];
	char    ZAP54KZNSWEB[1];
	char    ZAP54TFILL1[1];
	char    ZAP54LOE[1];
	char    ZAP54TFILL2[14];
	char    ZAP54TFILL3[21];
 };

 struct O_DEZAPDKPRO {
		 char					ZAPSA54[2];
		 struct DKPRO_ELEMENT	ZAP54TABELLE[ANZ_DKPRO_ELEMENTE]; 
		 char					ZAP54FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKPRO_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKPRO_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   14 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKPRO
 {
  public:

  DEZAPDKPRO s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKPRO_BES, DEZAPDKPRO_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKPRO_BES, DEZAPDKPRO_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKPRO_BES, DEZAPDKPRO_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKPRO()
  {
   ::buf_default((void *)&s, DEZAPDKPRO_BES, DEZAPDKPRO_ANZ);
  }
 };
#endif
