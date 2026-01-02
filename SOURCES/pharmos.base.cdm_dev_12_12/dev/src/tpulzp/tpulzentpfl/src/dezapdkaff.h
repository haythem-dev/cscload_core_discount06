/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKAFF_ELEMENTE                7
 #define ANZ_DKAFF_FELDER_PRO_ELEMENT      6

 #define L_DEZAPDKAFF_ZAPSA11              2
 #define L_DEZAPDKAFF_ZAP11SKZ             1
 #define L_DEZAPDKAFF_ZAP11KUBZ            12
 #define L_DEZAPDKAFF_ZAP11PZN             7
 #define L_DEZAPDKAFF_ZAP11EINH            9
 #define L_DEZAPDKAFF_ZAP11ABEZ            30
 #define L_DEZAPDKAFF_ZAP11DRFO            3
 #define L_DEZAPDKAFF_ZAP11FILLER          64

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKAFF_ANZ ( sizeof(DEZAPDKAFF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKAFF sizeof(struct DEZAPDKAFF)

 #define DEZAPDKAFF_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKAFFZAPSA11                       0
 #define DEZAPDKAFFZAP11SKZ                      1
 #define DEZAPDKAFFZAP11KUBZ                     2
 #define DEZAPDKAFFZAP11PZN                      3
 #define DEZAPDKAFFZAP11EINH                     4
 #define DEZAPDKAFFZAP11ABEZ                     5
 #define DEZAPDKAFFZAP11DRFO                     6
 #define DEZAPDKAFFZAP11FILLER                   37

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKAFF_ELEMENT 
 {
	char    ZAP11SKZ[1];
	char    ZAP11KUBZ[12];
	char    ZAP11PZN[7];
	char    ZAP11EINH[9];
	char    ZAP11ABEZ[30];
	char    ZAP11DRFO[3];
 };

 struct O_DEZAPDKAFF {
		 char					ZAPSA11[2];
		 struct DKAFF_ELEMENT	ZAP11TABELLE[ANZ_DKAFF_ELEMENTE]; 
		 char					ZAP11FILLER[64];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKAFF_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   64 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKAFF_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   64 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKAFF
 {
  public:

  DEZAPDKAFF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKAFF_BES, DEZAPDKAFF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKAFF_BES, DEZAPDKAFF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKAFF_BES, DEZAPDKAFF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKAFF()
  {
   ::buf_default((void *)&s, DEZAPDKAFF_BES, DEZAPDKAFF_ANZ);
  }
 };
#endif

