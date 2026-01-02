/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKLKR_ELEMENTE                6
 #define ANZ_DKLKR_FELDER_PRO_ELEMENT      8

 #define L_DEZAPDKLKR_ZAPSA48              2
 #define L_DEZAPDKLKR_ZAP48KRNR            3
 #define L_DEZAPDKLKR_ZAP48NAME            30
 #define L_DEZAPDKLKR_ZAP48AFNAME          10
 #define L_DEZAPDKLKR_ZAP48AFTYP           2
 #define L_DEZAPDKLKR_ZAP48AFWERT          10
 #define L_DEZAPDKLKR_ZAP48TFILL1          1
 #define L_DEZAPDKLKR_ZAP48LOEKZ           1
 #define L_DEZAPDKLKR_ZAP48TFILL2          23
 #define L_DEZAPDKLKR_ZAP48FILLER          18

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKLKR_ANZ ( sizeof(DEZAPDKLKR_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKLKR sizeof(struct DEZAPDKLKR)

 #define DEZAPDKLKR_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKLKRZAPSA48                       0
 #define DEZAPDKLKRZAP48KRNR                     1
 #define DEZAPDKLKRZAP48NAME                     2
 #define DEZAPDKLKRZAP48AFNAME                   3
 #define DEZAPDKLKRZAP48AFTYP                    4
 #define DEZAPDKLKRZAP48AFWERT                   5
 #define DEZAPDKLKRZAP48TFILL1                   6
 #define DEZAPDKLKRZAP48LOEKZ                    7
 #define DEZAPDKLKRZAP48TFILL2                   8
 #define DEZAPDKLKRZAP48FILLER                   49

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKLKR_ELEMENT 
 {
	char    ZAP48KRNR[3];
	char    ZAP48NAME[30];
	char    ZAP48AFNAME[10];
	char    ZAP48AFTYP[2];
	char    ZAP48AFWERT[10];
	char    ZAP48TFILL1[1];
	char    ZAP48LOEKZ[1];
	char    ZAP48TFILL2[23];
 };

 struct O_DEZAPDKLKR {
		 char					ZAPSA48[2];
		 struct DKLKR_ELEMENT	ZAP48TABELLE[ANZ_DKLKR_ELEMENTE]; 
		 char					ZAP48FILLER[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKLKR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKLKR_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   10 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   23 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKLKR
 {
  public:

  DEZAPDKLKR s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKLKR_BES, DEZAPDKLKR_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKLKR_BES, DEZAPDKLKR_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKLKR_BES, DEZAPDKLKR_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKLKR()
  {
   ::buf_default((void *)&s, DEZAPDKLKR_BES, DEZAPDKLKR_ANZ);
  }
 };
#endif
