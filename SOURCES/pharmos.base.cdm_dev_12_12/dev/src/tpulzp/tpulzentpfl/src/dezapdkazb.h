/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKAZB_ELEMENTE                4
 #define ANZ_DKAZB_FELDER_PRO_ELEMENT      6

 #define L_DEZAPDKAZB_ZAPSA33              2
 #define L_DEZAPDKAZB_ZAP33FIL             2
 #define L_DEZAPDKAZB_ZAP33PZN             7 
 #define L_DEZAPDKAZB_ZAP33LABEZ           50 
 #define L_DEZAPDKAZB_ZAP33TFILL1          1 
 #define L_DEZAPDKAZB_ZAP33LOEKZ           1
 #define L_DEZAPDKAZB_ZAP33TFILL2          59
 #define L_DEZAPDKAZB_ZAP33FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKAZB_ANZ ( sizeof(DEZAPDKAZB_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKAZB sizeof(struct DEZAPDKAZB)

 #define DEZAPDKAZB_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKAZBZAPSA33                       0
 #define DEZAPDKAZBZAP33FIL                      1
 #define DEZAPDKAZBZAP33PZN                      2
 #define DEZAPDKAZBZAP33LABEZ                    3
 #define DEZAPDKAZBZAP33TFILL1                   4
 #define DEZAPDKAZBZAP33LOEKZ                    5
 #define DEZAPDKAZBZAP33TFILL2                   6
 #define DEZAPDKAZBZAP33FILLER                   25

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKAZB_ELEMENT 
 {
	char    ZAP33FIL[2];
	char    ZAP33PZN[7];
	char    ZAP33LABEZ[50];
	char    ZAP33TFILL1[1];
	char    ZAP33LOEKZ[1];
	char    ZAP33TFILL2[59];
 };

 struct O_DEZAPDKAZB {
		 char					ZAPSA33[2];
		 struct DKAZB_ELEMENT	ZAP33TABELLE[ANZ_DKAZB_ELEMENTE]; 
		 char					ZAP33FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKAZB_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   59 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   59 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   59 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   59 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKAZB_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   59 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   59 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   59 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   59 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKAZB
 {
  public:

  DEZAPDKAZB s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKAZB_BES, DEZAPDKAZB_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKAZB_BES, DEZAPDKAZB_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKAZB_BES, DEZAPDKAZB_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKAZB()
  {
   ::buf_default((void *)&s, DEZAPDKAZB_BES, DEZAPDKAZB_ANZ);
  }
 };
#endif
