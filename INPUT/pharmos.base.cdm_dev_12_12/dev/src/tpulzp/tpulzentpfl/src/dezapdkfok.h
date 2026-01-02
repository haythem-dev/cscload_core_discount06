/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKFOK_ELEMENTE                7
 #define ANZ_DKFOK_FELDER_PRO_ELEMENT      5

 #define L_DEZAPDKFOK_ZAPSA51              2
 #define L_DEZAPDKFOK_ZAP51FORMKZ          2
 #define L_DEZAPDKFOK_ZAP51BEZ             50
 #define L_DEZAPDKFOK_ZAP51TFILL1          1
 #define L_DEZAPDKFOK_ZAP51LOEKZ           1
 #define L_DEZAPDKFOK_ZAP51TFILL2          16
 #define L_DEZAPDKFOK_ZAP51FILLER          8

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKFOK_ANZ ( sizeof(DEZAPDKFOK_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKFOK sizeof(struct DEZAPDKFOK)

 #define DEZAPDKFOK_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKFOKZAPSA51                       0
 #define DEZAPDKFOKZAP51FORMKZ                   1
 #define DEZAPDKFOKZAP51BEZ                      2
 #define DEZAPDKFOKZAP51TFILL1                   3
 #define DEZAPDKFOKZAP51LOEKZ                    4
 #define DEZAPDKFOKZAP51TFILL2                   5
 #define DEZAPDKFOKZAP51FILLER                   36

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKFOK_ELEMENT 
 {
	char    ZAP51FORMKZ[2];
	char    ZAP51BEZ[50];
	char    ZAP51TFILL1[1];
	char    ZAP51LOEKZ[1];
	char    ZAP51TFILL2[16];
 };

 struct O_DEZAPDKFOK {
		 char					ZAPSA51[2];
		 struct DKFOK_ELEMENT	ZAP51TABELLE[ANZ_DKFOK_ELEMENTE]; 
		 char					ZAP51FILLER[8];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKFOK_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    8 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKFOK_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   16 ,   0 },
	 { TYP_C ,    8 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKFOK
 {
  public:

  DEZAPDKFOK s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKFOK_BES, DEZAPDKFOK_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKFOK_BES, DEZAPDKFOK_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKFOK_BES, DEZAPDKFOK_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKFOK()
  {
   ::buf_default((void *)&s, DEZAPDKFOK_BES, DEZAPDKFOK_ANZ);
  }
 };
#endif

