/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKBGR_ELEMENTE                9
 #define ANZ_DKBGR_FELDER_PRO_ELEMENT      5

 #define L_DEZAPDKBGR_ZAPSA18              2
 #define L_DEZAPDKBGR_ZAP18GRUPPE          3
 #define L_DEZAPDKBGR_ZAP18BEZ             30
 #define L_DEZAPDKBGR_ZAP18TFILL1          1
 #define L_DEZAPDKBGR_ZAP18LOEKZ           1
 #define L_DEZAPDKBGR_ZAP18TFILL2          15
 #define L_DEZAPDKBGR_ZAP18FILLER          48

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKBGR_ANZ ( sizeof(DEZAPDKBGR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKBGR sizeof(struct DEZAPDKBGR)

 #define DEZAPDKBGR_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKBGRZAPSA18                       0
 #define DEZAPDKBGRZAP18GRUPPE                   1
 #define DEZAPDKBGRZAP18BEZ                      2
 #define DEZAPDKBGRZAP18TFILL1                   3
 #define DEZAPDKBGRZAP18LOEKZ                    4
 #define DEZAPDKBGRZAP18TFILL2                   5
 #define DEZAPDKBGRZAP18FILLER                   46

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKBGR_ELEMENT 
 {
	char    ZAP18GRUPPE[3];
	char    ZAP18BEZ[30];
	char    ZAP18TFILL1[1];
	char    ZAP18LOEKZ[1];
	char    ZAP18TFILL2[15];
 };

 struct O_DEZAPDKBGR {
		 char					ZAPSA18[2];
		 struct DKBGR_ELEMENT	ZAP18TABELLE[ANZ_DKBGR_ELEMENTE]; 
		 char					ZAP18FILLER[48];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKBGR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKBGR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKBGR
 {
  public:

  DEZAPDKBGR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKBGR_BES, DEZAPDKBGR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKBGR_BES, DEZAPDKBGR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKBGR_BES, DEZAPDKBGR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKBGR()
  {
   ::buf_default((void *)&s, DEZAPDKBGR_BES, DEZAPDKBGR_ANZ);
  }
 };
#endif

