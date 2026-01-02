/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKSOA_ELEMENTE                24
 #define ANZ_DKSOA_FELDER_PRO_ELEMENT      6

 #define L_DEZAPDKSOA_ZAPSA03              2
 #define L_DEZAPDKSOA_ZAP03PZN             7 
 #define L_DEZAPDKSOA_ZAP03KZ              1
 #define L_DEZAPDKSOA_ZAP03MENGE           3 
 #define L_DEZAPDKSOA_ZAP03PREIS           7
 #define L_DEZAPDKSOA_ZAP03LOEKZ           1
 #define L_DEZAPDKSOA_ZAP03TFILL2          2
 #define L_DEZAPDKSOA_ZAP03FILLER          90

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKSOA_ANZ ( sizeof(DEZAPDKSOA_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKSOA sizeof(struct DEZAPDKSOA)

 #define DEZAPDKSOA_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKSOAZAPSA03                       0
 #define DEZAPDKSOAZAP03PZN                      1
 #define DEZAPDKSOAZAP03KZ                       2
 #define DEZAPDKSOAZAP03MENGE                    3
 #define DEZAPDKSOAZAP03PREIS                    4
 #define DEZAPDKSOAZAP03LOEKZ                    5
 #define DEZAPDKSOAZAP03TFILL2                   6
 #define DEZAPDKSOAZAP03FILLER                   145

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKSOA_ELEMENT 
 {
	char    ZAP03PZN[7];
	char    ZAP03KZ[1];
	char    ZAP03MENGE[3];
	char    ZAP03PREIS[7];
	char    ZAP03LOEKZ[1];
	char    ZAP03TFILL2[2];
 };

 struct O_DEZAPDKSOA {
		 char					ZAPSA03[2];
		 struct DKSOA_ELEMENT	ZAP03TABELLE[ANZ_DKSOA_ELEMENTE]; 
		 char					ZAP03FILLER[90];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKSOA_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKSOA_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKSOA
 {
  public:

  DEZAPDKSOA s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKSOA_BES, DEZAPDKSOA_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKSOA_BES, DEZAPDKSOA_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKSOA_BES, DEZAPDKSOA_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKSOA()
  {
   ::buf_default((void *)&s, DEZAPDKSOA_BES, DEZAPDKSOA_ANZ);
  }
 };
#endif
