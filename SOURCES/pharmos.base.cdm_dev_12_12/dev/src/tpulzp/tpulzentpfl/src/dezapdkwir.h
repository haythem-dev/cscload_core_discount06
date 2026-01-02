/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKWIR_ELEMENTE                15
 #define ANZ_DKWIR_FELDER_PRO_ELEMENT      6

 #define L_DEZAPDKWIR_ZAPSA19              2
 #define L_DEZAPDKWIR_ZAP19GRUPPE          3
 #define L_DEZAPDKWIR_ZAP19BEZ             20
 #define L_DEZAPDKWIR_ZAP19AKTIV           1
 #define L_DEZAPDKWIR_ZAP19TFILL1          1
 #define L_DEZAPDKWIR_ZAP19LOEKZ           1
 #define L_DEZAPDKWIR_ZAP19TFILL2          6
 #define L_DEZAPDKWIR_ZAP19FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKWIR_ANZ ( sizeof(DEZAPDKWIR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKWIR sizeof(struct DEZAPDKWIR)

 #define DEZAPDKWIR_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKWIRZAPSA19                       0
 #define DEZAPDKWIRZAP19GRUPPE                   1
 #define DEZAPDKWIRZAP19BEZ                      2
 #define DEZAPDKWIRZAP19AKTIV                    3
 #define DEZAPDKWIRZAP19TFILL1                   4
 #define DEZAPDKWIRZAP19LOEKZ                    5
 #define DEZAPDKWIRZAP19TFILL2                   6
 #define DEZAPDKWIRZAP19FILLER                   91

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKWIR_ELEMENT 
 {
	char    ZAP19GRUPPE[3];
	char    ZAP19BEZ[20];
	char    ZAP19AKTIV[1];
	char    ZAP19TFILL1[1];
	char    ZAP19LOEKZ[1];
	char    ZAP19TFILL2[6];
 };

 struct O_DEZAPDKWIR {
		 char					ZAPSA19[2];
		 struct DKWIR_ELEMENT	ZAP19TABELLE[ANZ_DKWIR_ELEMENTE]; 
		 char					ZAP19FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKWIR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKWIR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKWIR
 {
  public:

  DEZAPDKWIR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKWIR_BES, DEZAPDKWIR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKWIR_BES, DEZAPDKWIR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKWIR_BES, DEZAPDKWIR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKWIR()
  {
   ::buf_default((void *)&s, DEZAPDKWIR_BES, DEZAPDKWIR_ANZ);
  }
 };
#endif

