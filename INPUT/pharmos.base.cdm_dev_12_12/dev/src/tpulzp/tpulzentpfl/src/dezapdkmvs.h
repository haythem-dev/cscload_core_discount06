/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKMVS_ELEMENTE                8
 #define ANZ_DKMVS_FELDER_PRO_ELEMENT      8

 #define L_DEZAPDKMVS_ZAPSA45              2
 #define L_DEZAPDKMVS_ZAP45MOVISO          3
 #define L_DEZAPDKMVS_ZAP45BEZ             30
 #define L_DEZAPDKMVS_ZAP45ART             2
 #define L_DEZAPDKMVS_ZAP45TFILL1          1
 #define L_DEZAPDKMVS_ZAP45LOEKZ           1
 #define L_DEZAPDKMVS_ZAP45SORT			   2
 #define L_DEZAPDKMVS_ZAP45HOPR	    	   1
 #define L_DEZAPDKMVS_ZAP45TFILL2          20
 #define L_DEZAPDKMVS_ZAP45FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKMVS_ANZ ( sizeof(DEZAPDKMVS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKMVS sizeof(struct DEZAPDKMVS)

 #define DEZAPDKMVS_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKMVSZAPSA45                       0
 #define DEZAPDKMVSZAP45MOVISO                   1
 #define DEZAPDKMVSZAP45BEZ                      2
 #define DEZAPDKMVSZAP45ART                      3
 #define DEZAPDKMVSZAP45TFILL1                   4
 #define DEZAPDKMVSZAP45LOEKZ                    5
 #define DEZAPDKMVSZAP45SORT                     6
 #define DEZAPDKMVSZAP45HOPR                     7
 #define DEZAPDKMVSZAP45TFILL2                   8
 #define DEZAPDKMVSZAP45FILLER                   65

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKMVS_ELEMENT 
 {
	char    ZAP45MOVISO[3];
	char    ZAP45BEZ[30];
	char    ZAP45ART[2];
	char    ZAP45TFILL1[1];
	char    ZAP45LOEKZ[1];
	char    ZAP45SORT[2];
	char    ZAP45HOPR[1];
	char    ZAP45TFILL2[20];
 };

 struct O_DEZAPDKMVS {
		 char					ZAPSA45[2];
		 struct DKMVS_ELEMENT	ZAP45TABELLE[ANZ_DKMVS_ELEMENTE]; 
		 char					ZAP45FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKMVS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKMVS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKMVS
 {
  public:

  DEZAPDKMVS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKMVS_BES, DEZAPDKMVS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKMVS_BES, DEZAPDKMVS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKMVS_BES, DEZAPDKMVS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKMVS()
  {
   ::buf_default((void *)&s, DEZAPDKMVS_BES, DEZAPDKMVS_ANZ);
  }
 };
#endif
