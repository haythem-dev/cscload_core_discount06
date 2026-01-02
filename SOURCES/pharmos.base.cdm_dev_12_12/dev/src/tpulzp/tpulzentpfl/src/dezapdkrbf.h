/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKRBF_ELEMENTE                6
 #define ANZ_DKRBF_FELDER_PRO_ELEMENT      8

 #define L_DEZAPDKRBF_ZAPSA47              2
 #define L_DEZAPDKRBF_ZAP47RBF             5
 #define L_DEZAPDKRBF_ZAP47BEZ             30
 #define L_DEZAPDKRBF_ZAP47TFILL1          1
 #define L_DEZAPDKRBF_ZAP47LOE             1
 #define L_DEZAPDKRBF_ZAP47AKT  	   	   1
 #define L_DEZAPDKRBF_ZAP47ART	    	   2
 #define L_DEZAPDKRBF_ZAP47BABRREL 	   	   1
 #define L_DEZAPDKRBF_ZAP47TFILL2          39
 #define L_DEZAPDKRBF_ZAP47FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKRBF_ANZ ( sizeof(DEZAPDKRBF_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKRBF sizeof(struct DEZAPDKRBF)

 #define DEZAPDKRBF_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKRBFZAPSA47                       0
 #define DEZAPDKRBFZAP47RBF                      1
 #define DEZAPDKRBFZAP47BEZ                      2
 #define DEZAPDKRBFZAP47TFILL1                   3
 #define DEZAPDKRBFZAP47LOE                      4
 #define DEZAPDKRBFZAP47AKT                      5
 #define DEZAPDKRBFZAP47ART                      6
 #define DEZAPDKRBFZAP47BABRREL                  7
 #define DEZAPDKRBFZAP47TFILL2                   8
 #define DEZAPDKRBFZAP47FILLER                   49

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKRBF_ELEMENT 
 {
	char    ZAP47RBF[5];
	char    ZAP47BEZ[30];
	char    ZAP47TFILL1[1];
	char    ZAP47LOE[1];
	char    ZAP47AKT[1];
	char    ZAP47ART[2];
	char    ZAP47BABRREL[1];
	char    ZAP47TFILL2[39];
 };

 struct O_DEZAPDKRBF {
		 char					ZAPSA47[2];
		 struct DKRBF_ELEMENT	ZAP47TABELLE[ANZ_DKRBF_ELEMENTE]; 
		 char					ZAP47FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKRBF_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKRBF_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   39 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKRBF
 {
  public:

  DEZAPDKRBF s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKRBF_BES, DEZAPDKRBF_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKRBF_BES, DEZAPDKRBF_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKRBF_BES, DEZAPDKRBF_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKRBF()
  {
   ::buf_default((void *)&s, DEZAPDKRBF_BES, DEZAPDKRBF_ANZ);
  }
 };
#endif
