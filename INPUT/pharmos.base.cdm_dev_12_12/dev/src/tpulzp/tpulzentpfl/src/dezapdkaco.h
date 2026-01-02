/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKACO_ELEMENTE                3
 #define ANZ_DKACO_FELDER_PRO_ELEMENT      13

 #define L_DEZAPDKACO_ZAPSA34              2
 #define L_DEZAPDKACO_ZAP34FIL             2
 #define L_DEZAPDKACO_ZAP34PZN             7
 #define L_DEZAPDKACO_ZAP34PREF            1
 #define L_DEZAPDKACO_ZAP34CODE	          25
 #define L_DEZAPDKACO_ZAP34CTYP            3
 #define L_DEZAPDKACO_ZAP34FIL2            2
 #define L_DEZAPDKACO_ZAP34CODE2          25
 #define L_DEZAPDKACO_ZAP34PZN2            7
 #define L_DEZAPDKACO_ZAP34CTYP2           3
 #define L_DEZAPDKACO_ZAP34LFD             3
 #define L_DEZAPDKACO_ZAP34TFILL1          1
 #define L_DEZAPDKACO_ZAP34LOE             1
 #define L_DEZAPDKACO_ZAP34TFILL2         80
 #define L_DEZAPDKACO_ZAP34FILLER         18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKACO_ANZ ( sizeof(DEZAPDKACO_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKACO sizeof(struct DEZAPDKACO)

 #define DEZAPDKACO_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKACOZAPSA34                       0
 #define DEZAPDKACOZAP34FIL                      1
 #define DEZAPDKACOZAP34PZN                      2
 #define DEZAPDKACOZAP34PREF                     3
 #define DEZAPDKACOZAP34CODE                     4
 #define DEZAPDKACOZAP34CTYP                     5
 #define DEZAPDKACOZAP34FIL2                     6
 #define DEZAPDKACOZAP34CODE2                    7
 #define DEZAPDKACOZAP34PZN2                     8
 #define DEZAPDKACOZAP34CTYP2                    9
 #define DEZAPDKACOZAP34LFD		                 10
 #define DEZAPDKACOZAP34TFILL1                   11
 #define DEZAPDKACOZAP34LOEKZ                    12
 #define DEZAPDKACOZAP34TFILL2                   13
 #define DEZAPDKACOZAP34FILLER                   40

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKACO_ELEMENT 
 {
	char    ZAP34FIL[2];
	char    ZAP34PZN[7];
	char    ZAP34PREF[1];
	char    ZAP34CODE[25];
	char    ZAP34CTYP[3];
	char    ZAP34FIL2[2];
	char    ZAP34CODE2[25];
	char    ZAP34PZN2[7];
	char    ZAP34CTYP2[3];
	char    ZAP34LFD[3];
	char    ZAP34TFILL1[1];
	char    ZAP34LOEKZ[1];
	char    ZAP34TFILL2[80];
 };

 struct O_DEZAPDKACO {
		 char					ZAPSA34[2];
		 struct DKACO_ELEMENT	ZAP34TABELLE[ANZ_DKACO_ELEMENTE]; 
		 char					ZAP34FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKACO_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   80 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   80 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   80 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKACO_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   80 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   80 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   80 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKACO
 {
  public:

  DEZAPDKACO s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKACO_BES, DEZAPDKACO_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKACO_BES, DEZAPDKACO_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKACO_BES, DEZAPDKACO_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKACO()
  {
   ::buf_default((void *)&s, DEZAPDKACO_BES, DEZAPDKACO_ANZ);
  }
 };
#endif

