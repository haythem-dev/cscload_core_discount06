/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

/* Aufteilung der INN auf 2 Felder, weil im WandelCobol der Puffer nur mit maximal 256 definiert ist und es sonst zu einem Segmentation Fault kommt */
/* Hinweis: WandelCobol() ist im File ascitocobol.c implementiert, das sich wiederum in der Bibliothek libtpld befindet (im TFS unter pharmos.base.libtpld) */

 #define L_DEZAPDKAIN_ZAPSA55              2
 #define L_DEZAPDKAIN_ZAP55FIL             2
 #define L_DEZAPDKAIN_ZAP55WIRK            5
 #define L_DEZAPDKAIN_ZAP55INN1            240
 #define L_DEZAPDKAIN_ZAP55INN2            240
 #define L_DEZAPDKAIN_ZAP55TFILL1          3
 #define L_DEZAPDKAIN_ZAP55LOEKZ           1
 #define L_DEZAPDKAIN_ZAP55TFILL2          7

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKAIN_ANZ ( sizeof(DEZAPDKAIN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKAIN sizeof(struct DEZAPDKAIN)

 #define DEZAPDKAIN_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKAINZAPSA55                       0
 #define DEZAPDKAINZAP55FIL                      1
 #define DEZAPDKAINZAP55WIRK                     2
 #define DEZAPDKAINZAP55INN1                     3
 #define DEZAPDKAINZAP55INN2                     4
 #define DEZAPDKAINZAP55TFILL1                   5
 #define DEZAPDKAINZAP55LOEKZ                    6
 #define DEZAPDKAINZAP55TFILL2                   7

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct O_DEZAPDKAIN {
		 char	 ZAPSA55[2];
		 char    ZAP55FIL[2];
		 char    ZAP55WIRK[5];
		 char    ZAP55INN1[240];
		 char    ZAP55INN2[240];
		 char    ZAP55TFILL1[3];
		 char    ZAP55LOEKZ[1];
		 char    ZAP55TFILL2[7];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKAIN_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKAIN_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKAIN
 {
  public:

  DEZAPDKAIN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKAIN_BES, DEZAPDKAIN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKAIN_BES, DEZAPDKAIN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKAIN_BES, DEZAPDKAIN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKAIN()
  {
   ::buf_default((void *)&s, DEZAPDKAIN_BES, DEZAPDKAIN_ANZ);
  }
 };
#endif
