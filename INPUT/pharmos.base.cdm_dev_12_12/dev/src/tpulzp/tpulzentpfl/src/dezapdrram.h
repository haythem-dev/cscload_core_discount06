/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DEZAPDRRAM_ZAPSA35         2
 #define L_DEZAPDRRAM_ZAP35ART        3
 #define L_DEZAPDRRAM_ZAP35BEZ        25
 #define L_DEZAPDRRAM_ZAP35TFILL1     32
 #define L_DEZAPDRRAM_ZAP35BAS1       3
 #define L_DEZAPDRRAM_ZAP35BAS2       3
 #define L_DEZAPDRRAM_ZAP35BAS3       3
 #define L_DEZAPDRRAM_ZAP35BAS4       3
 #define L_DEZAPDRRAM_ZAP35BAS5       3
 #define L_DEZAPDRRAM_ZAP35BAS6       3
 #define L_DEZAPDRRAM_ZAP35BAS7       3
 #define L_DEZAPDRRAM_ZAP35BAS8       3
 #define L_DEZAPDRRAM_ZAP35BAS9       3
 #define L_DEZAPDRRAM_ZAP35BAS10      3
 #define L_DEZAPDRRAM_ZAP35TFILL2     3
 #define L_DEZAPDRRAM_ZAP35LOEKZ      1
 #define L_DEZAPDRRAM_ZAP35TFILL3     414

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDRRAM_ANZ ( sizeof(DEZAPDRRAM_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDRRAM sizeof(struct DEZAPDRRAM)

 #define DEZAPDRRAM_H
 
 #define DEZAPDRRAMZAPSA35                  0
 #define DEZAPDRRAMZAP35ART                 1
 #define DEZAPDRRAMZAP35BEZ                 2
 #define DEZAPDRRAMZAP35TFILL1              3
 #define DEZAPDRRAMZAP35BAS1                4
 #define DEZAPDRRAMZAP35BAS2                5
 #define DEZAPDRRAMZAP35BAS3                6
 #define DEZAPDRRAMZAP35BAS4                7
 #define DEZAPDRRAMZAP35BAS5                8
 #define DEZAPDRRAMZAP35BAS6                9
 #define DEZAPDRRAMZAP35BAS7                10
 #define DEZAPDRRAMZAP35BAS8                11
 #define DEZAPDRRAMZAP35BAS9                12
 #define DEZAPDRRAMZAP35BAS10               13
 #define DEZAPDRRAMZAP35TFILL2              14
 #define DEZAPDRRAMZAP35LOEKZ               15
 #define DEZAPDRRAMZAP35TFILL3              16

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct O_DEZAPDRRAM {
		 char    ZAPSA35[2];
		 char    ZAP35ART[3];
		 char    ZAP35BEZ[25];
		 char    ZAP35TFILL1[32];
		 char    ZAP35BAS1[3];
		 char    ZAP35BAS2[3];
		 char    ZAP35BAS3[3];
		 char    ZAP35BAS4[3];
		 char    ZAP35BAS5[3];
		 char    ZAP35BAS6[3];
		 char    ZAP35BAS7[3];
		 char    ZAP35BAS8[3];
		 char    ZAP35BAS9[3];
		 char    ZAP35BAS10[3];
		 char    ZAP35TFILL2[3];
		 char    ZAP35LOEKZ[1];
		 char    ZAP35TFILL3[414];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDRRAM_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,  414 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDRRAM_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,   25 ,   0 },
	 { TYP_C ,   32 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_D ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,  414 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDRRAM
 {
  public:

  DEZAPDRRAM s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDRRAM_BES, DEZAPDRRAM_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDRRAM_BES, DEZAPDRRAM_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDRRAM_BES, DEZAPDRRAM_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDRRAM()
  {
   ::buf_default((void *)&s, DEZAPDRRAM_BES, DEZAPDRRAM_ANZ);
  }
 };
#endif
