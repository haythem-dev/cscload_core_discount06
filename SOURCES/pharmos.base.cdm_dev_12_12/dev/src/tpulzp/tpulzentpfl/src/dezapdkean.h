/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKEAN_ELEMENTE                20
 #define ANZ_DKEAN_FELDER_PRO_ELEMENT      4

 #define L_DEZAPDKEAN_ZAPSA09              2
 #define L_DEZAPDKEAN_ZAP09EAN             13
 #define L_DEZAPDKEAN_ZAP09PZN             7
 #define L_DEZAPDKEAN_ZAP09LOEKZ           1
 #define L_DEZAPDKEAN_ZAP09VFIL            2
 #define L_DEZAPDKEAN_ZAP09FILLER          38

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKEAN_ANZ ( sizeof(DEZAPDKEAN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKEAN sizeof(struct DEZAPDKEAN)

 #define DEZAPDKEAN_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKEANZAPSA09                       0
 #define DEZAPDKEANZAP09EAN                      1
 #define DEZAPDKEANZAP09PZN                      2
 #define DEZAPDKEANZAP09LOEKZ                    3
 #define DEZAPDKEANZAP09VFIL                     4
 #define DEZAPDKEANZAP09FILLER                   81

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKEAN_ELEMENT 
 {
	char    ZAP09EAN[13];
	char    ZAP09PZN[7];
	char    ZAP09LOEKZ[1];
	char    ZAP09VFIL[2];
 };

 struct O_DEZAPDKEAN {
		 char					ZAPSA09[2];
		 struct DKEAN_ELEMENT	ZAP09TABELLE[ANZ_DKEAN_ELEMENTE]; 
		 char					ZAP09FILLER[38];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKEAN_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   38 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKEAN_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   38 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKEAN
 {
  public:

  DEZAPDKEAN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKEAN_BES, DEZAPDKEAN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKEAN_BES, DEZAPDKEAN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKEAN_BES, DEZAPDKEAN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKEAN()
  {
   ::buf_default((void *)&s, DEZAPDKEAN_BES, DEZAPDKEAN_ANZ);
  }
 };
#endif
