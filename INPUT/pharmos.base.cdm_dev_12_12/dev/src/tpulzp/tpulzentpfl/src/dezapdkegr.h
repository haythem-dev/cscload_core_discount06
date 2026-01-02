/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKEGR_ELEMENTE                7
 #define ANZ_DKEGR_FELDER_PRO_ELEMENT      19

 #define L_DEZAPDKEGR_ZAPSA12              2
 #define L_DEZAPDKEGR_ZAP12FIL             2
 #define L_DEZAPDKEGR_ZAP12EGR             3
 #define L_DEZAPDKEGR_ZAP12BEZ             30
 #define L_DEZAPDKEGR_ZAP12AURAB           1
 #define L_DEZAPDKEGR_ZAP12PROZ            5
 #define L_DEZAPDKEGR_ZAP12MAXWERT         5
 #define L_DEZAPDKEGR_ZAP12BEITRAG         3
 #define L_DEZAPDKEGR_ZAP12EGRALT          5
 #define L_DEZAPDKEGR_ZAP12IDF             7
 #define L_DEZAPDKEGR_ZAP12OMGEKO          1
 #define L_DEZAPDKEGR_ZAP12TFILL1          1
 #define L_DEZAPDKEGR_ZAP12LOE             1
 #define L_DEZAPDKEGR_ZAP12AEPBAS          1
 #define L_DEZAPDKEGR_ZAP12BEAB            5
 #define L_DEZAPDKEGR_ZAP12OMGRF           1
 #define L_DEZAPDKEGR_ZAP12SOGRP           3
 #define L_DEZAPDKEGR_ZAP12REFNR           7
 #define L_DEZAPDKEGR_ZAP12GRPVIS          1
 #define L_DEZAPDKEGR_ZAP12TFILL2          4
 #define L_DEZAPDKEGR_ZAP12FILLER          8

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKEGR_ANZ ( sizeof(DEZAPDKEGR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKEGR sizeof(struct DEZAPDKEGR)

 #define DEZAPDKEGR_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKEGRZAPSA12                       0
 #define DEZAPDKEGRZAP12FIL                      1
 #define DEZAPDKEGRZAP12EKG                      2
 #define DEZAPDKEGRZAP12BEZ                      3
 #define DEZAPDKEGRZAP12AURAB                    4
 #define DEZAPDKEGRZAP12PROZ                     5
 #define DEZAPDKEGRZAP12MAXWERT                  6
 #define DEZAPDKEGRZAP12BEITRAG                  7
 #define DEZAPDKEGRZAP12EGRALT                   8
 #define DEZAPDKEGRZAP12IDF                      9
 #define DEZAPDKEGRZAP12OMGEKO                   10
 #define DEZAPDKEGRZAP12TFILL1                   11
 #define DEZAPDKEGRZAP12LOEKZ                    12
 #define DEZAPDKEGRZAP12AEPBAS                   13
 #define DEZAPDKEGRZAP12BEAB                     14
 #define DEZAPDKEGRZAP12OMGRF                    15
 #define DEZAPDKEGRZAP12SOGRP                    16
 #define DEZAPDKEGRZAP12REFNR                    17
 #define DEZAPDKEGRZAP12GRPVIS                   18
 #define DEZAPDKEGRZAP12TFILL2                   19
 #define DEZAPDKEGRZAP12FILLER                   134

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKEGR_ELEMENT 
 {
	char    ZAP12FIL[2];
	char    ZAP12EKG[3];
	char    ZAP12BEZ[30];
	char    ZAP12AURAB[1];
	char    ZAP12PROZ[5];
	char    ZAP12MAXWERT[5];
	char    ZAP12BEITRAG[3];
	char    ZAP12EGRALT[5];
	char    ZAP12IDF[7];
	char    ZAP12OMGEKO[1];
	char    ZAP12TFILL1[1];
	char    ZAP12LOEKZ[1];
	char    ZAP12AEPBAS[1];
	char    ZAP12BEAB[5];
	char    ZAP12OMGRF[1];
	char    ZAP12SOGRP[3];
	char    ZAP12REFNR[7];
	char    ZAP12GRPVIS[1];
	char    ZAP12TFILL2[4];
 };

 struct O_DEZAPDKEGR {
		 char					ZAPSA12[2];
		 struct DKEGR_ELEMENT	ZAP12TABELLE[ANZ_DKEGR_ELEMENTE]; 
		 char					ZAP12FILLER[8];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKEGR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKEGR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKEGR
 {
  public:

  DEZAPDKEGR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKEGR_BES, DEZAPDKEGR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKEGR_BES, DEZAPDKEGR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKEGR_BES, DEZAPDKEGR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKEGR()
  {
   ::buf_default((void *)&s, DEZAPDKEGR_BES, DEZAPDKEGR_ANZ);
  }
 };
#endif

