/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKCRR_ELEMENTE                5
 #define ANZ_DKCRR_FELDER_PRO_ELEMENT      10

 #define L_DEZAPDKCRR_ZAPSA22              2
 #define L_DEZAPDKCRR_ZAP22FIL             2
 #define L_DEZAPDKCRR_ZAP22PZN             7
 #define L_DEZAPDKCRR_ZAP22CHARGE          24
 #define L_DEZAPDKCRR_ZAP22RRKZ            1
 #define L_DEZAPDKCRR_ZAP22DERST           8
 #define L_DEZAPDKCRR_ZAP22TFILL1          1
 #define L_DEZAPDKCRR_ZAP22LOE             1
 #define L_DEZAPDKCRR_ZAP22EINSCHR         2
 #define L_DEZAPDKCRR_ZAP22LOEDAT          8
 #define L_DEZAPDKCRR_ZAP22TFILL2          36
 #define L_DEZAPDKCRR_ZAP22FILLER          48

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKCRR_ANZ ( sizeof(DEZAPDKCRR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKCRR sizeof(struct DEZAPDKCRR)

 #define DEZAPDKCRR_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKCRRZAPSA22                       0
 #define DEZAPDKCRRZAP22FIL                      1
 #define DEZAPDKCRRZAP22PZN                      2
 #define DEZAPDKCRRZAP22CHARGE                   3
 #define DEZAPDKCRRZAP22RRKZ                     4
 #define DEZAPDKCRRZAP22DERST                    5
 #define DEZAPDKCRRZAP22TFILL1                   6
 #define DEZAPDKCRRZAP22LOEKZ                    7
 #define DEZAPDKCRRZAP22EINSCHR                  8
 #define DEZAPDKCRRZAP22LOEDAT                   9
 #define DEZAPDKCRRZAP22TFILL2                   10
 #define DEZAPDKCRRZAP22FILLER                   51

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKCRR_ELEMENT 
 {
	char    ZAP22FIL[2];
	char    ZAP22PZN[7];
	char    ZAP22CHARGE[24];
	char    ZAP22RRKZ[1];
	char    ZAP22DERST[8];
	char    ZAP22TFILL1[1];
	char    ZAP22LOEKZ[1];
	char    ZAP22EINSCHR[2];
	char    ZAP22LOEDAT[8];
	char    ZAP22TFILL2[36];
 };

 struct O_DEZAPDKCRR {
		 char					ZAPSA22[2];
		 struct DKCRR_ELEMENT	ZAP22TABELLE[ANZ_DKCRR_ELEMENTE]; 
		 char					ZAP22FILLER[48];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKCRR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKCRR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   24 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,   36 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKCRR
 {
  public:

  DEZAPDKCRR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKCRR_BES, DEZAPDKCRR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKCRR_BES, DEZAPDKCRR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKCRR_BES, DEZAPDKCRR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKCRR()
  {
   ::buf_default((void *)&s, DEZAPDKCRR_BES, DEZAPDKCRR_ANZ);
  }
 };
#endif

