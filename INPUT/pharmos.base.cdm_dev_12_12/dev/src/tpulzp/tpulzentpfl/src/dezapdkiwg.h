/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKIWG_ELEMENTE                12
 #define ANZ_DKIWG_FELDER_PRO_ELEMENT      4

 #define L_DEZAPDKIWG_ZAPSA16              2
 #define L_DEZAPDKIWG_ZAP16GRUPPE          5
 #define L_DEZAPDKIWG_ZAP16BEZ             30
 #define L_DEZAPDKIWG_ZAP16TFILL1          4
 #define L_DEZAPDKIWG_ZAP16LOEKZ           1
 #define L_DEZAPDKIWG_ZAP16FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKIWG_ANZ ( sizeof(DEZAPDKIWG_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKIWG sizeof(struct DEZAPDKIWG)

 #define DEZAPDKIWG_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKIWGZAPSA16                       0
 #define DEZAPDKIWGZAP16GRUPPE                   1
 #define DEZAPDKIWGZAP16BEZ                      2
 #define DEZAPDKIWGZAP16TFILL1                   3
 #define DEZAPDKIWGZAP16LOEKZ                    4
 #define DEZAPDKIWGZAP16FILLER                   49

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKIWG_ELEMENT 
 {
	char    ZAP16GRUPPE[5];
	char    ZAP16BEZ[30];
	char    ZAP16TFILL1[4];
	char    ZAP16LOEKZ[1];
 };

 struct O_DEZAPDKIWG {
		 char					ZAPSA16[2];
		 struct DKIWG_ELEMENT	ZAP16TABELLE[ANZ_DKIWG_ELEMENTE]; 
		 char					ZAP16FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKIWG_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKIWG_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKIWG
 {
  public:

  DEZAPDKIWG s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKIWG_BES, DEZAPDKIWG_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKIWG_BES, DEZAPDKIWG_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKIWG_BES, DEZAPDKIWG_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKIWG()
  {
   ::buf_default((void *)&s, DEZAPDKIWG_BES, DEZAPDKIWG_ANZ);
  }
 };
#endif

