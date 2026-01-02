/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define L_DEZAPDKGAL_ZAPSA23         2
 #define L_DEZAPDKGAL_ZAP23PZN        7
 #define L_DEZAPDKGAL_ZAP23LOEKZ      1
 #define L_DEZAPDKGAL_ZAP23EAN        13
 #define L_DEZAPDKGAL_ZAP23WGR        11
 #define L_DEZAPDKGAL_ZAP23NG         1
 #define L_DEZAPDKGAL_ZAP23IKS        1
 #define L_DEZAPDKGAL_ZAP23KLIP       1
 #define L_DEZAPDKGAL_ZAP23ANRH       12
 #define L_DEZAPDKGAL_ZAP23AEP        7
 #define N_DEZAPDKGAL_ZAP23AEP        2
 #define L_DEZAPDKGAL_ZAP23AVP        7
 #define N_DEZAPDKGAL_ZAP23AVP        2
 #define L_DEZAPDKGAL_ZAP23GUELT      9
 #define L_DEZAPDKGAL_ZAP23MWST       1
 #define L_DEZAPDKGAL_ZAP23AHDL       1
 #define L_DEZAPDKGAL_ZAP23KUEHL      1
 #define L_DEZAPDKGAL_ZAP23AANR       7
 #define L_DEZAPDKGAL_ZAP23TOTBEZ     50
 #define L_DEZAPDKGAL_ZAP23EINH       9
 #define L_DEZAPDKGAL_ZAP23ABEZ       30
 #define L_DEZAPDKGAL_ZAP23DRFO       3
 #define L_DEZAPDKGAL_ZAP23AEDAT      9
 #define L_DEZAPDKGAL_ZAP23ARTKZ      1
 #define L_DEZAPDKGAL_ZAP23EANKZ      1
 #define L_DEZAPDKGAL_ZAP23TOTBEZF    50
 #define L_DEZAPDKGAL_ZAP23EINHF      9
 #define L_DEZAPDKGAL_ZAP23ABEZF      30
 #define L_DEZAPDKGAL_ZAP23DRFOF      3
 #define L_DEZAPDKGAL_ZAP23KKCODE     1
 #define L_DEZAPDKGAL_ZAP23KKLIM      1
 #define L_DEZAPDKGAL_ZAP23IKSNR      9
 #define L_DEZAPDKGAL_ZAP23THERGRP    7
 #define L_DEZAPDKGAL_ZAP23GF         1
 #define L_DEZAPDKGAL_ZAP23LDAU       3
 #define L_DEZAPDKGAL_ZAP23RETBED     3
 #define L_DEZAPDKGAL_ZAP23FOCODE     9
 #define L_DEZAPDKGAL_ZAP23BTM        1
 #define L_DEZAPDKGAL_ZAP23GIFT       1
 #define L_DEZAPDKGAL_ZAP23LTEMP      5
 #define L_DEZAPDKGAL_ZAP23GHNR       13
 #define L_DEZAPDKGAL_ZAP23AESA       1 
 #define L_DEZAPDKGAL_ZAP23FILLER     11
 #define L_DEZAPDKGAL_ZAP23FILLREST   198

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKGAH_ANZ ( sizeof(DEZAPDKGAH_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKGAH sizeof(struct DEZAPDKGAH)

 #define DEZAPDKGAH_H
 
 #define DEZAPDKGALZAPSA23                  0
 #define DEZAPDKGALZAP23PZN                 1
 #define DEZAPDKGALZAP23LOEKZ               2
 #define DEZAPDKGALZAP23EAN                 3
 #define DEZAPDKGALZAP23WGR                 4
 #define DEZAPDKGALZAP23NG                  5
 #define DEZAPDKGALZAP23IKS                 6
 #define DEZAPDKGALZAP23KLIP                7
 #define DEZAPDKGALZAP23ANRH                8
 #define DEZAPDKGALZAP23AEP                 9
 #define DEZAPDKGALZAP23AVP                 10
 #define DEZAPDKGALZAP23GUELT               11
 #define DEZAPDKGALZAP23MWST                12
 #define DEZAPDKGALZAP23AHDL                13
 #define DEZAPDKGALZAP23KUEHL               14
 #define DEZAPDKGALZAP23AANR                15
 #define DEZAPDKGALZAP23TOTBEZ              16
 #define DEZAPDKGALZAP23EINH                17
 #define DEZAPDKGALZAP23ABEZ                18
 #define DEZAPDKGALZAP23DRFO                19
 #define DEZAPDKGALZAP23AEDAT               20
 #define DEZAPDKGALZAP23ARTKZ               21
 #define DEZAPDKGALZAP23EANKZ               22
 #define DEZAPDKGALZAP23TOTBEZF             23
 #define DEZAPDKGALZAP23EINHF               24
 #define DEZAPDKGALZAP23ABEZF               25
 #define DEZAPDKGALZAP23DRFOF               26
 #define DEZAPDKGALZAP23KKCODE              27 
 #define DEZAPDKGALZAP23KKLIM               28
 #define DEZAPDKGALZAP23IKSNR               29
 #define DEZAPDKGALZAP23THERGRP             30
 #define DEZAPDKGALZAP23GF                  31
 #define DEZAPDKGALZAP23LDAU                32
 #define DEZAPDKGALZAP23RETBED              33
 #define DEZAPDKGALZAP23FOCODE              34
 #define DEZAPDKGALZAP23BTM                 35
 #define DEZAPDKGALZAP23GIFT                36
 #define DEZAPDKGALZAP23LTEMP               37
 #define DEZAPDKGALZAP23GHNR                38
 #define DEZAPDKGALZAP23AESA                39
 #define DEZAPDKGALZAP23FILLER              40
 #define DEZAPDKGALZAP23FILLREST            41

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct O_DEZAPDKGAL {
		 char    ZAPSA23[2];
		 char    ZAP23PZN[7];
		 char    ZAP23LOEKZ[1];
		 char    ZAP23EAN[13];
		 char    ZAP23WGR[11];
		 char    ZAP23NG[1];
		 char    ZAP23IKS[1];
		 char    ZAP23KLIP[1];
		 char    ZAP23ANRH[12];
		 char    ZAP23AEP[7];
		 char    ZAP23AVP[7];
		 char    ZAP23GUELT[9];
		 char    ZAP23MWST[1];
		 char    ZAP23AHDL[1];
		 char    ZAP23KUEHL[1];
		 char    ZAP23AANR[7];
		 char    ZAP23TOTBEZ[50];
		 char    ZAP23EINH[9];
		 char    ZAP23ABEZ[30];
		 char    ZAP23DRFO[3];
		 char    ZAP23AEDAT[9];
		 char    ZAP23ARTKZ[1];
		 char    ZAP23EANKZ[1];
		 char    ZAP23TOTBEZF[50];
		 char    ZAP23EINHF[9];
		 char    ZAP23ABEZF[30];
		 char    ZAP23DRFOF[3];
		 char    ZAP23KKCODE[1];
		 char    ZAP23KKLIM[1];
		 char    ZAP23IKSNR[9];
		 char    ZAP23THERGRP[7];
		 char    ZAP23GF[1];
		 char    ZAP23LDAU[3];
		 char    ZAP23RETBED[3];
		 char    ZAP23FOCODE[9];
		 char    ZAP23BTM[1];
		 char    ZAP23GIFT[1];
		 char    ZAP23LTEMP[5];
		 char    ZAP23GHNR[13];
		 char    ZAP23AESA[1];
		 char    ZAP23FILLER[11];
		 char    ZAP23FILLREST[198];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKLIF_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   11 ,   0 },
	 { TYP_C ,  198 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKGAL_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   50 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    9 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   11 ,   0 },
	 { TYP_C ,  198 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKGAL
 {
  public:

  DEZAPDKGAL s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKGAL_BES, DEZAPDKGAL_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKGAL_BES, DEZAPDKGAL_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKGAL_BES, DEZAPDKGAL_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKGAL()
  {
   ::buf_default((void *)&s, DEZAPDKGAL_BES, DEZAPDKGAL_ANZ);
  }
 };
#endif

