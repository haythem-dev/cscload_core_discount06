/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKRGR_ELEMENTE                9
 #define ANZ_DKRGR_FELDER_PRO_ELEMENT      10

 #define L_DEZAPDKRGR_ZAPSA26              2
 #define L_DEZAPDKRGR_ZAP26GRUPPE          3
 #define L_DEZAPDKRGR_ZAP26BEZ             30
 #define L_DEZAPDKRGR_ZAP26TFILL1          1
 #define L_DEZAPDKRGR_ZAP26LOEKZ           1
 #define L_DEZAPDKRGR_ZAP26PRBAS           1
 #define L_DEZAPDKRGR_ZAP26KEINRAB         1
 #define L_DEZAPDKRGR_ZAP26RABART          1
 #define L_DEZAPDKRGR_ZAP26DRGEP           1
 #define L_DEZAPDKRGR_ZAP26MAXIMUM         7
 #define N_DEZAPDKRGR_ZAP26MAXIMUM         2
 #define L_DEZAPDKRGR_ZAP26TFILL2          4
 #define L_DEZAPDKRGR_ZAP26FILLER          48

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKRGR_ANZ ( sizeof(DEZAPDKRGR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKRGR sizeof(struct DEZAPDKRGR)

 #define DEZAPDKRGR_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKRGRZAPSA26                       0
 #define DEZAPDKRGRZAP26GRUPPE                   1
 #define DEZAPDKRGRZAP26BEZ                      2
 #define DEZAPDKRGRZAP26TFILL1                   3
 #define DEZAPDKRGRZAP26LOEKZ                    4
 #define DEZAPDKRGRZAP26PRBAS                    5
 #define DEZAPDKRGRZAP26KEINRAB                  6
 #define DEZAPDKRGRZAP26RABART                   7
 #define DEZAPDKRGRZAP26DRGEP                    8
 #define DEZAPDKRGRZAP26MAXIMUM                  9
 #define DEZAPDKRGRZAP26TFILL2                   10
 #define DEZAPDKRGRZAP26FILLER                   91

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKRGR_ELEMENT 
 {
	char    ZAP26GRUPPE[3];
	char    ZAP26BEZ[30];
	char    ZAP26TFILL1[1];
	char    ZAP26LOEKZ[1];
	char    ZAP26PRBAS[1];
	char    ZAP26KEINRAB[1];
	char    ZAP26RABART[1];
	char    ZAP26DRGEP[1];
	char    ZAP26MAXIMUM[7];
	char    ZAP26TFILL2[4];
 };

 struct O_DEZAPDKRGR {
		 char					ZAPSA26[2];
		 struct DKRGR_ELEMENT	ZAP26TABELLE[ANZ_DKRGR_ELEMENTE]; 
		 char					ZAP26FILLER[48];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKRGR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKRGR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   2 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKRGR
 {
  public:

  DEZAPDKRGR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKRGR_BES, DEZAPDKRGR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKRGR_BES, DEZAPDKRGR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKRGR_BES, DEZAPDKRGR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKRGR()
  {
   ::buf_default((void *)&s, DEZAPDKRGR_BES, DEZAPDKRGR_ANZ);
  }
 };
#endif
