/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define ARTSEL_LISTE \
 			ART.ART_NR, \
 			ART.AUSW_ART_NR, \
 			ART.AEP, \
 			ART.AVP, \
 			ART.ART_NAME_KURZ, \
 			ART.ART_EINH, \
 			ART.ART_NAME, \
 			ART.DARR_FORM, \
 			ART.PACK_GR, \
 			ART.BESTAND

 #define ARTSEL_ZEIGER(xxx) \
 			:xxx->ART_NR,\
 			:xxx->AUSW_ART_NR,\
 			:xxx->AEP,\
 			:xxx->AVP,\
 			:xxx->ART_NAME_KURZ,\
 			:xxx->ART_EINH,\
 			:xxx->ART_NAME,\
 			:xxx->DARR_FORM,\
 			:xxx->PACK_GR,\
 			:xxx->BESTAND

 #define L_ARTSEL_ART_NR               11
 #define L_ARTSEL_AUSW_ART_NR          11
 #define L_ARTSEL_AEP                  7
 #define N_ARTSEL_AEP                  2
 #define L_ARTSEL_AVP                  7
 #define N_ARTSEL_AVP                  2
 #define L_ARTSEL_ART_NAME_KURZ        12
 #define L_ARTSEL_ART_EINH             9
 #define L_ARTSEL_ART_NAME             30
 #define L_ARTSEL_DARR_FORM            3
 #define L_ARTSEL_PACK_GR              11
 #define L_ARTSEL_BESTAND              11
 #define L_ARTSEL_FETCH_REL            11


 #define ARTSEL_ANZ (int) ( sizeof(ARTSEL_BES) / sizeof(struct buf_desc) )
 #define G_ARTSEL sizeof(struct ARTSEL)


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct ARTSEL {
		 long    ART_NR;
		 long    AUSW_ART_NR;
		 double  AEP;
		 double  AVP;
		 char    ART_NAME_KURZ[12 + 1];
		 char    ART_EINH[9 + 1];
		 char    ART_NAME[30 + 1];
		 char    DARR_FORM[3 + 1];
		 long    PACK_GR;
		 long    BESTAND;
		 long    FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 #ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
 #endif

 struct I_ARTSEL {
		 short  ART_NR;
		 short  AUSW_ART_NR;
		 short  AEP;
		 short  AVP;
		 short  ART_NAME_KURZ;
		 short  ART_EINH;
		 short  ART_NAME;
		 short  DARR_FORM;
		 short  PACK_GR;
		 short  BESTAND;
		 short  FETCH_REL;
       };

 #ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
 #endif


 static struct buf_desc ARTSEL_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_D ,    7 ,   2 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };

 #ifdef __cplusplus

 class CARTSEL
 {
  public:

  ARTSEL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, ARTSEL_BES, ARTSEL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
   #ifdef Win32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,ARTSEL_BES, ARTSEL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,ARTSEL_BES, ARTSEL_ANZ, error_msg);
   #endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CARTSEL()
  {
   ::buf_default((void *)&s, ARTSEL_BES, ARTSEL_ANZ);
  }
 };
 #endif

