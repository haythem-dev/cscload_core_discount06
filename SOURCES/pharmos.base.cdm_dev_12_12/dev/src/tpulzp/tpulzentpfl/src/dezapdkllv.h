/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKLLV_ELEMENTE                7
 #define ANZ_DKLLV_FELDER_PRO_ELEMENT      6

 #define L_DEZAPDKLLV_ZAPSA46              2
 #define L_DEZAPDKLLV_ZAP46LNR             3
 #define L_DEZAPDKLLV_ZAP46BEZ             30
 #define L_DEZAPDKLLV_ZAP46ART             3
 #define L_DEZAPDKLLV_ZAP46TFILL1          1
 #define L_DEZAPDKLLV_ZAP46LOEKZ           1
 #define L_DEZAPDKLLV_ZAP46TFILL2          32
 #define L_DEZAPDKLLV_ZAP46FILLER          8

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKLLV_ANZ ( sizeof(DEZAPDKLLV_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKLLV sizeof(struct DEZAPDKLLV)

 #define DEZAPDKLLV_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKLLVZAPSA46                       0
 #define DEZAPDKLLVZAP46LNR                      1
 #define DEZAPDKLLVZAP46BEZ                      2
 #define DEZAPDKLLVZAP46ART                      3
 #define DEZAPDKLLVZAP46TFILL1                   4
 #define DEZAPDKLLVZAP46LOEKZ                    5
 #define DEZAPDKLLVZAP46TFILL2                   6
 #define DEZAPDKLLVZAP46FILLER                   43

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKLLV_ELEMENT 
 {
	char    ZAP46LNR[3];
	char    ZAP46BEZ[30];
	char    ZAP46ART[3];
	char    ZAP46TFILL1[1];
	char    ZAP46LOEKZ[1];
	char    ZAP46TFILL2[32];
 };

 struct O_DEZAPDKLLV {
		 char					ZAPSA46[2];
		 struct DKLLV_ELEMENT	ZAP46TABELLE[ANZ_DKLLV_ELEMENTE]; 
		 char					ZAP46FILLER[8];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKLLV_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKLLV_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   32 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKLLV
 {
  public:

  DEZAPDKLLV s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKLLV_BES, DEZAPDKLLV_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKLLV_BES, DEZAPDKLLV_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKLLV_BES, DEZAPDKLLV_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKLLV()
  {
   ::buf_default((void *)&s, DEZAPDKLLV_BES, DEZAPDKLLV_ANZ);
  }
 };
#endif
