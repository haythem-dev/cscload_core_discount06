/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKGHZ_ELEMENTE                8
 #define ANZ_DKGHZ_FELDER_PRO_ELEMENT      7

 #define L_DEZAPDKGHZ_ZAPSA37              2
 #define L_DEZAPDKGHZ_ZAP37FIL             2
 #define L_DEZAPDKGHZ_ZAP37KUKLA           1
 #define L_DEZAPDKGHZ_ZAP37ABTAGE          3
 #define L_DEZAPDKGHZ_ZAP37GEB             5
 #define N_DEZAPDKGHZ_ZAP37GEB             2
 #define L_DEZAPDKGHZ_ZAP37TFILL1          1
 #define L_DEZAPDKGHZ_ZAP37LOEKZ           1
 #define L_DEZAPDKGHZ_ZAP37TFILL2          49
 #define L_DEZAPDKGHZ_ZAP37FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKGHZ_ANZ ( sizeof(DEZAPDKGHZ_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKGHZ sizeof(struct DEZAPDKGHZ)

 #define DEZAPDKGHZ_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKGHZZAPSA37                       0
 #define DEZAPDKGHZZAP37FIL                      1
 #define DEZAPDKGHZZAP37KUKLA                    2
 #define DEZAPDKGHZZAP37ABTAGE                   3
 #define DEZAPDKGHZZAP37GEB                      4
 #define DEZAPDKGHZZAP37TFILL1                   5
 #define DEZAPDKGHZZAP37LOEKZ                    6
 #define DEZAPDKGHZZAP37TFILL2                   7
 #define DEZAPDKGHZZAP37FILLER                   57

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKGHZ_ELEMENT 
 {
	char    ZAP37FIL[2];
	char    ZAP37KUKLA[1];
	char    ZAP37ABTAGE[3];
	char    ZAP37GEB[5];
	char    ZAP37TFILL1[1];
	char    ZAP37LOEKZ[1];
	char    ZAP37TFILL2[49];
 };

 struct O_DEZAPDKGHZ {
		 char					ZAPSA37[2];
		 struct DKGHZ_ELEMENT	ZAP37TABELLE[ANZ_DKGHZ_ELEMENTE]; 
		 char					ZAP37FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKGHZ_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKGHZ_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_D ,    5 ,   2 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   49 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };

#endif

#ifdef TRANSCLASS

 class CDEZAPDKGHZ
 {
  public:

  DEZAPDKGHZ s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKGHZ_BES, DEZAPDKGHZ_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKGHZ_BES, DEZAPDKGHZ_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKGHZ_BES, DEZAPDKGHZ_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKGHZ()
  {
   ::buf_default((void *)&s, DEZAPDKGHZ_BES, DEZAPDKGHZ_ANZ);
  }
 };
#endif

