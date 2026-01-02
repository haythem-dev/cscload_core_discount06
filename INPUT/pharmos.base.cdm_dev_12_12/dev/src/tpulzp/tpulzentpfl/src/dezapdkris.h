/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/

 #define ANZ_DKRIS_TABELEMENTE             12
 #define ANZ_DKRIS_FELDER_PRO_TABELEMENT   6

 #define L_DEZAPDKRIS_ZAPSA08              2
 #define L_DEZAPDKRIS_ZAP08FIL1            2
 #define L_DEZAPDKRIS_ZAP08KUBZ            12
 #define L_DEZAPDKRIS_ZAP08PZN1            7
 #define L_DEZAPDKRIS_ZAP08PZN2            7
 #define L_DEZAPDKRIS_ZAP08FIL2            2
 #define L_DEZAPDKRIS_ZAP08TPZN            7
 #define L_DEZAPDKRIS_ZAP08TKZMAN          1
 #define L_DEZAPDKRIS_ZAP08TFIL1           5
 #define L_DEZAPDKRIS_ZAP08TSORKZ          1
 #define L_DEZAPDKRIS_ZAP08TVKART          1
 #define L_DEZAPDKRIS_ZAP08TFIL2           15
 #define L_DEZAPDKRIS_ZAP08HV              1
 #define L_DEZAPDKRIS_ZAP08LOEKZ           1
 #define L_DEZAPDKRIS_ZAP08OPZN            7
 #define L_DEZAPDKRIS_ZAP08HNR             5
 #define L_DEZAPDKRIS_ZAP08FILLER          8
 #define L_DEZAPDKRIS_ZAP08FILLREST        148

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPDKRIS_ANZ ( sizeof(DEZAPDKRIS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPDKRIS sizeof(struct DEZAPDKRIS)

 #define DEZAPDKRIS_H

/* Indezes für struct AUFB-Struktur beim CONV-Aufruf */
 #define DEZAPDKRISZAPSA08                       0
 #define DEZAPDKRISZAP08FIL1                     1
 #define DEZAPDKRISZAP08KUBZ                     2
 #define DEZAPDKRISZAP08PZN1                     3
 #define DEZAPDKRISZAP08PZN2                     4
 #define DEZAPDKRISZAP08FIL2                     5
 #define DEZAPDKRISZAP08TPZN                     6
 #define DEZAPDKRISZAP08TKZMAN                   7
 #define DEZAPDKRISZAP08TFIL1                    8
 #define DEZAPDKRISZAP08TSORKZ                   9
 #define DEZAPDKRISZAP08TVKART                   10
 #define DEZAPDKRISZAP08TFIL2                    11
 #define DEZAPDKRISZAP08HV                       78
 #define DEZAPDKRISZAP08LOEKZ                    79
 #define DEZAPDKRISZAP08OPZN                     80
 #define DEZAPDKRISZAP08HNR                      81
 #define DEZAPDKRISZAP08FILLER                   82
 #define DEZAPDKRISZAP08FILLREST                 83

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKRIS_TABELEMENT 
 {
	char    ZAP08TPZN[7];
	char    ZAP08TKZMAN[1];
	char    ZAP08TFIL1[5];
	char    ZAP08TSORKZ[1];
	char    ZAP08TVKART[1];
	char    ZAP08TFIL2[15];
 };

 struct O_DEZAPDKRIS {
		 char						ZAPSA08[2];
		 char						ZAP08FIL1[2];
		 char						ZAP08KUBZ[12];
		 char						ZAP08PZN1[7];
		 char						ZAP08PZN2[7];
		 char						ZAP08FIL2[2];
		 struct DKRIS_TABELEMENT	ZAP08TABELLE[ANZ_DKRIS_TABELEMENTE]; 
		 char						ZAP08HV[1];
		 char						ZAP08LOEKZ[1];
		 char						ZAP08OPZN[1];
		 char						ZAP08HNR[1];
		 char						ZAP09FILLER[8];
		 char						ZAP09FILLREST[148];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPDKRIS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,  148 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPDKRIS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,  148 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPDKRIS
 {
  public:

  DEZAPDKRIS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPDKRIS_BES, DEZAPDKRIS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPDKRIS_BES, DEZAPDKRIS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPDKRIS_BES, DEZAPDKRIS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPDKRIS()
  {
   ::buf_default((void *)&s, DEZAPDKRIS_BES, DEZAPDKRIS_ANZ);
  }
 };
#endif
