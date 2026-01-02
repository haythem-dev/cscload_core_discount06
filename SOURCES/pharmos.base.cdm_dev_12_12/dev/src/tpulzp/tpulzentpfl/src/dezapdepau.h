/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DEPAU_ELEMENTE                5
 #define ANZ_DEPAU_FELDER_PRO_ELEMENT      9

 #define L_DEZAPDEPAU_ZAPSA39              2
 #define L_DEZAPDEPAU_ZAP39FIL             2
 #define L_DEZAPDEPAU_ZAP39SA              2
 #define L_DEZAPDEPAU_ZAP39PZNPSEU         7
 #define L_DEZAPDEPAU_ZAP39PZNECHT         7
 #define L_DEZAPDEPAU_ZAP39MANRALT         15
 #define L_DEZAPDEPAU_ZAP39MANRNEU         15
 #define L_DEZAPDEPAU_ZAP39DATUM           8
 #define L_DEZAPDEPAU_ZAP39STATUS          2
 #define L_DEZAPDEPAU_ZAP39TFILL2          32
 #define L_DEZAPDEPAU_ZAP39FILLER          48

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDEPAU_ANZ ( sizeof(DEZAPDEPAU_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDEPAU sizeof(struct DEZAPDEPAU)

 #define DEZAPDEPAU_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDEPAUZAPSA39                       0
 #define DEZAPDEPAUZAP39FIL                      1
 #define DEZAPDEPAUZAP39SA                       2
 #define DEZAPDEPAUZAP39PZNPSEU                  3
 #define DEZAPDEPAUZAP39PZNECHT                  4
 #define DEZAPDEPAUZAP39MANRALT                  5
 #define DEZAPDEPAUZAP39MANRNEU                  6
 #define DEZAPDEPAUZAP39DATUM                    7
 #define DEZAPDEPAUZAP39STATUS	                 8
 #define DEZAPDEPAUZAP39TFILL2                   9
 #define DEZAPDEPAUZAP39FILLER                   46

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DEPAU_ELEMENT 
 {
	char    ZAP39FIL[2];
	char    ZAP39SA[2];
	char    ZAP39PZNPSEU[7];
	char    ZAP39PZNECHT[7];
	char    ZAP39MANRALT[15];
	char    ZAP39MANRNEU[15];
	char    ZAP39DATUM[8];
	char    ZAP39STATUS[2];
	char    ZAP39TFILL2[32];
 };

 struct O_DEZAPDEPAU {
		 char					ZAPSA39[2];
		 struct DEPAU_ELEMENT	ZAP39TABELLE[ANZ_DEPAU_ELEMENTE]; 
		 char					ZAP39FILLER[48];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDEPAU_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDEPAU_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_C ,   48 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDEPAU
 {
  public:

  DEZAPDEPAU s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDEPAU_BES, DEZAPDEPAU_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDEPAU_BES, DEZAPDEPAU_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDEPAU_BES, DEZAPDEPAU_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDEPAU()
  {
   ::buf_default((void *)&s, DEZAPDEPAU_BES, DEZAPDEPAU_ANZ);
  }
 };
#endif
