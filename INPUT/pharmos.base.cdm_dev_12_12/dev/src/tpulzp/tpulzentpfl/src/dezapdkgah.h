/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DEZAPDKGAH_ZAPSA24         2
 #define L_DEZAPDKGAH_ZAP24HNR        13
 #define L_DEZAPDKGAH_ZAP24LOEKZ      1
 #define L_DEZAPDKGAH_ZAP24EAN        13
 #define L_DEZAPDKGAH_ZAP24KUBZ       20
 #define L_DEZAPDKGAH_ZAP24NAME       60
 #define L_DEZAPDKGAH_ZAP24STR        30
 #define L_DEZAPDKGAH_ZAP24LKZ        3
 #define L_DEZAPDKGAH_ZAP24PLZ        7
 #define L_DEZAPDKGAH_ZAP24ORT        30
 #define L_DEZAPDKGAH_ZAP24RTEL       20
 #define L_DEZAPDKGAH_ZAP24BTEL       20
 #define L_DEZAPDKGAH_ZAP24FAX        20
 #define L_DEZAPDKGAH_ZAP24AEDAT      9
 #define L_DEZAPDKGAH_ZAP24FILLER     47
 #define L_DEZAPDKGAH_ZAP24FILLREST   198

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKGAH_ANZ ( sizeof(DEZAPDKGAH_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKGAH sizeof(struct DEZAPDKGAH)

 #define DEZAPDKGAH_H
 
 #define DEZAPDKGAHZAPSA24                  0
 #define DEZAPDKGAHZAP24HNR                 1
 #define DEZAPDKGAHZAP24LOEKZ               2
 #define DEZAPDKGAHZAP24EAN                 3
 #define DEZAPDKGAHZAP24KUBZ                4
 #define DEZAPDKGAHZAP24NAME1               5
 #define DEZAPDKGAHZAP24STR                 6
 #define DEZAPDKGAHZAP24LKZ                 7
 #define DEZAPDKGAHZAP24PLZ                 8
 #define DEZAPDKGAHZAP24ORT                 9
 #define DEZAPDKGAHZAP24RTEL                10
 #define DEZAPDKGAHZAP24BTEL                11
 #define DEZAPDKGAHZAP24FAX                 12
 #define DEZAPDKGAHZAP24AEDAT               13
 #define DEZAPDKGAHZAP24FILLER              14
 #define DEZAPDKGAHZAP24FILLREST            15

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct O_DEZAPDKGAH {
		 char    ZAPSA24[2];
		 char    ZAP24HNR[13];
		 char    ZAP24LOEKZ[1];
		 char    ZAP24EAN[13];
		 char    ZAP24KUBZ[20];
		 char    ZAP24NAME[60];
		 char    ZAP24STR[40];
		 char    ZAP24LKZ[3];
		 char    ZAP24PLZ[7];
		 char    ZAP24ORT[40];
		 char    ZAP24RTEL[20];
		 char    ZAP24BTEL[20];
		 char    ZAP24FAX[20];
		 char    ZAP24AEDAT[9];
		 char    ZAP24FILLER[47];
		 char    ZAP24FILLREST[198];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKGAH_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   60 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   47 ,   0 },
	 { TYP_C ,  198 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKGAH_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   60 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   47 ,   0 },
	 { TYP_C ,  198 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKGAH
 {
  public:

  DEZAPDKGAH s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKGAH_BES, DEZAPDKGAH_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKGAH_BES, DEZAPDKGAH_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKGAH_BES, DEZAPDKGAH_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKGAH()
  {
   ::buf_default((void *)&s, DEZAPDKGAH_BES, DEZAPDKGAH_ANZ);
  }
 };
#endif

