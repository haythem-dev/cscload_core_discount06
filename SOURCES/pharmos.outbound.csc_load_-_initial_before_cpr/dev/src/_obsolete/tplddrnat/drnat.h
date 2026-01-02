/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_DRNAT_NATSTF               3
 #define L_DRNAT_NATDABE              7
 #define L_DRNAT_NATDAEN              7
 #define L_DRNAT_NATKONT              5
 #define L_DRNAT_NATRKON              5
 #define L_DRNAT_NATBAS1              3
 #define L_DRNAT_NATMEN1              3
 #define L_DRNAT_NATBAS2              3
 #define L_DRNAT_NATMEN2              3
 #define L_DRNAT_NATBAS3              3
 #define L_DRNAT_NATMEN3              3
 #define L_DRNAT_NATBAS4              3
 #define L_DRNAT_NATMEN4              3
 #define L_DRNAT_NATBAS5              3
 #define L_DRNAT_NATMEN5              3
 #define L_DRNAT_NATBAS6              3
 #define L_DRNAT_NATMEN6              3
 #define L_DRNAT_NATLOE               1
 #define L_DRNAT_NATHV                1
 #define L_DRNAT_NATFILLER            57


 #define L_DRNAT_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DRNAT_ANZ ( sizeof(DRNAT_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DRNAT sizeof(struct DRNAT)


#define DRNAT_CREATE(xxx) \
 EXEC SQL CREATE TABLE xxx (\
		 NATSTF CHAR(3)            default " " NOT NULL,\
		 NATDABE CHAR(7)            default " " NOT NULL,\
		 NATDAEN CHAR(7)            default " " NOT NULL,\
		 NATKONT CHAR(5)            default " " NOT NULL,\
		 NATRKON CHAR(5)            default " " NOT NULL,\
		 NATBAS1 CHAR(3)            default " " NOT NULL,\
		 NATMEN1 CHAR(3)            default " " NOT NULL,\
		 NATBAS2 CHAR(3)            default " " NOT NULL,\
		 NATMEN2 CHAR(3)            default " " NOT NULL,\
		 NATBAS3 CHAR(3)            default " " NOT NULL,\
		 NATMEN3 CHAR(3)            default " " NOT NULL,\
		 NATBAS4 CHAR(3)            default " " NOT NULL,\
		 NATMEN4 CHAR(3)            default " " NOT NULL,\
		 NATBAS5 CHAR(3)            default " " NOT NULL,\
		 NATMEN5 CHAR(3)            default " " NOT NULL,\
		 NATBAS6 CHAR(3)            default " " NOT NULL,\
		 NATMEN6 CHAR(3)            default " " NOT NULL,\
		 NATLOE CHAR(1)            default " " NOT NULL,\
		 NATHV CHAR(1)            default " " NOT NULL,\
		 NATFILLER CHAR(57)           default " " NOT NULL  ) EXTENT SIZE 9;

#define DRNAT_CREATE_INDEX(yyy,xxx) \

#define DRNAT_DELETE_INDEX(xxx) \

 #define DRNAT_H

 #define DRNAT_LISTE \
 			DRNAT.NATSTF, \
 			DRNAT.NATDABE, \
 			DRNAT.NATDAEN, \
 			DRNAT.NATKONT, \
 			DRNAT.NATRKON, \
 			DRNAT.NATBAS1, \
 			DRNAT.NATMEN1, \
 			DRNAT.NATBAS2, \
 			DRNAT.NATMEN2, \
 			DRNAT.NATBAS3, \
 			DRNAT.NATMEN3, \
 			DRNAT.NATBAS4, \
 			DRNAT.NATMEN4, \
 			DRNAT.NATBAS5, \
 			DRNAT.NATMEN5, \
 			DRNAT.NATBAS6, \
 			DRNAT.NATMEN6, \
 			DRNAT.NATLOE, \
 			DRNAT.NATHV, \
 			DRNAT.NATFILLER
 #define DRNAT_PLISTE \
 			"DRNAT.NATSTF," \
 			"DRNAT.NATDABE," \
 			"DRNAT.NATDAEN," \
 			"DRNAT.NATKONT," \
 			"DRNAT.NATRKON," \
 			"DRNAT.NATBAS1," \
 			"DRNAT.NATMEN1," \
 			"DRNAT.NATBAS2," \
 			"DRNAT.NATMEN2," \
 			"DRNAT.NATBAS3," \
 			"DRNAT.NATMEN3," \
 			"DRNAT.NATBAS4," \
 			"DRNAT.NATMEN4," \
 			"DRNAT.NATBAS5," \
 			"DRNAT.NATMEN5," \
 			"DRNAT.NATBAS6," \
 			"DRNAT.NATMEN6," \
 			"DRNAT.NATLOE," \
 			"DRNAT.NATHV," \
 			"DRNAT.NATFILLER " 

 #define DRNATNATSTF                        0
 #define DRNATNATDABE                       1
 #define DRNATNATDAEN                       2
 #define DRNATNATKONT                       3
 #define DRNATNATRKON                       4
 #define DRNATNATBAS1                       5
 #define DRNATNATMEN1                       6
 #define DRNATNATBAS2                       7
 #define DRNATNATMEN2                       8
 #define DRNATNATBAS3                       9
 #define DRNATNATMEN3                       10
 #define DRNATNATBAS4                       11
 #define DRNATNATMEN4                       12
 #define DRNATNATBAS5                       13
 #define DRNATNATMEN5                       14
 #define DRNATNATBAS6                       15
 #define DRNATNATMEN6                       16
 #define DRNATNATLOE                        17
 #define DRNATNATHV                         18
 #define DRNATNATFILLER                     19

 #define DRNAT_ZEIGER(xxx) \
 			:xxx->NATSTF,\
 			:xxx->NATDABE,\
 			:xxx->NATDAEN,\
 			:xxx->NATKONT,\
 			:xxx->NATRKON,\
 			:xxx->NATBAS1,\
 			:xxx->NATMEN1,\
 			:xxx->NATBAS2,\
 			:xxx->NATMEN2,\
 			:xxx->NATBAS3,\
 			:xxx->NATMEN3,\
 			:xxx->NATBAS4,\
 			:xxx->NATMEN4,\
 			:xxx->NATBAS5,\
 			:xxx->NATMEN5,\
 			:xxx->NATBAS6,\
 			:xxx->NATMEN6,\
 			:xxx->NATLOE,\
 			:xxx->NATHV,\
 			:xxx->NATFILLER

 #define DRNAT_UPDATE(xxx) \
 			NATSTF = :xxx->NATSTF,\
 			NATDABE = :xxx->NATDABE,\
 			NATDAEN = :xxx->NATDAEN,\
 			NATKONT = :xxx->NATKONT,\
 			NATRKON = :xxx->NATRKON,\
 			NATBAS1 = :xxx->NATBAS1,\
 			NATMEN1 = :xxx->NATMEN1,\
 			NATBAS2 = :xxx->NATBAS2,\
 			NATMEN2 = :xxx->NATMEN2,\
 			NATBAS3 = :xxx->NATBAS3,\
 			NATMEN3 = :xxx->NATMEN3,\
 			NATBAS4 = :xxx->NATBAS4,\
 			NATMEN4 = :xxx->NATMEN4,\
 			NATBAS5 = :xxx->NATBAS5,\
 			NATMEN5 = :xxx->NATMEN5,\
 			NATBAS6 = :xxx->NATBAS6,\
 			NATMEN6 = :xxx->NATMEN6,\
 			NATLOE = :xxx->NATLOE,\
 			NATHV = :xxx->NATHV,\
 			NATFILLER = :xxx->NATFILLER

 #define LS_DRNAT_NATSTF               4
 #define LS_DRNAT_NATDABE              8
 #define LS_DRNAT_NATDAEN              8
 #define LS_DRNAT_NATKONT              6
 #define LS_DRNAT_NATRKON              6
 #define LS_DRNAT_NATBAS1              4
 #define LS_DRNAT_NATMEN1              4
 #define LS_DRNAT_NATBAS2              4
 #define LS_DRNAT_NATMEN2              4
 #define LS_DRNAT_NATBAS3              4
 #define LS_DRNAT_NATMEN3              4
 #define LS_DRNAT_NATBAS4              4
 #define LS_DRNAT_NATMEN4              4
 #define LS_DRNAT_NATBAS5              4
 #define LS_DRNAT_NATMEN5              4
 #define LS_DRNAT_NATBAS6              4
 #define LS_DRNAT_NATMEN6              4
 #define LS_DRNAT_NATLOE               2
 #define LS_DRNAT_NATHV                2
 #define LS_DRNAT_NATFILLER            58

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DRNAT {
		 char    NATSTF[3 + 1];
		 char    NATDABE[7 + 1];
		 char    NATDAEN[7 + 1];
		 char    NATKONT[5 + 1];
		 char    NATRKON[5 + 1];
		 char    NATBAS1[3 + 1];
		 char    NATMEN1[3 + 1];
		 char    NATBAS2[3 + 1];
		 char    NATMEN2[3 + 1];
		 char    NATBAS3[3 + 1];
		 char    NATMEN3[3 + 1];
		 char    NATBAS4[3 + 1];
		 char    NATMEN4[3 + 1];
		 char    NATBAS5[3 + 1];
		 char    NATMEN5[3 + 1];
		 char    NATBAS6[3 + 1];
		 char    NATMEN6[3 + 1];
		 char    NATLOE[1 + 1];
		 char    NATHV[1 + 1];
		 char    NATFILLER[57 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_DRNAT {
		 char    NATSTF[3 + 1];
		 char    NATDABE[7 + 1];
		 char    NATDAEN[7 + 1];
		 char    NATKONT[5 + 1];
		 char    NATRKON[5 + 1];
		 char    NATBAS1[3 + 1];
		 char    NATMEN1[3 + 1];
		 char    NATBAS2[3 + 1];
		 char    NATMEN2[3 + 1];
		 char    NATBAS3[3 + 1];
		 char    NATMEN3[3 + 1];
		 char    NATBAS4[3 + 1];
		 char    NATMEN4[3 + 1];
		 char    NATBAS5[3 + 1];
		 char    NATMEN5[3 + 1];
		 char    NATBAS6[3 + 1];
		 char    NATMEN6[3 + 1];
		 char    NATLOE;
		 char    NATHV;
		 char    NATFILLER[57 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_DRNAT {
		 short  NATSTF;
		 short  NATDABE;
		 short  NATDAEN;
		 short  NATKONT;
		 short  NATRKON;
		 short  NATBAS1;
		 short  NATMEN1;
		 short  NATBAS2;
		 short  NATMEN2;
		 short  NATBAS3;
		 short  NATMEN3;
		 short  NATBAS4;
		 short  NATMEN4;
		 short  NATBAS5;
		 short  NATMEN5;
		 short  NATBAS6;
		 short  NATMEN6;
		 short  NATLOE;
		 short  NATHV;
		 short  NATFILLER;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_DRNAT {
		 char    NATSTF[3 + 1];
		 char    NATDABE[7 + 1];
		 char    NATDAEN[7 + 1];
		 char    NATKONT[5 + 1];
		 char    NATRKON[5 + 1];
		 char    NATBAS1[3 + 1];
		 char    NATMEN1[3 + 1];
		 char    NATBAS2[3 + 1];
		 char    NATMEN2[3 + 1];
		 char    NATBAS3[3 + 1];
		 char    NATMEN3[3 + 1];
		 char    NATBAS4[3 + 1];
		 char    NATMEN4[3 + 1];
		 char    NATBAS5[3 + 1];
		 char    NATMEN5[3 + 1];
		 char    NATBAS6[3 + 1];
		 char    NATMEN6[3 + 1];
		 char    NATLOE[1 + 1];
		 char    NATHV[1 + 1];
		 char    NATFILLER[57 + 1];
       };

 struct O_DRNAT {
		 char    NATSTF[3];
		 char    NATDABE[7];
		 char    NATDAEN[7];
		 char    NATKONT[5];
		 char    NATRKON[5];
		 char    NATBAS1[3];
		 char    NATMEN1[3];
		 char    NATBAS2[3];
		 char    NATMEN2[3];
		 char    NATBAS3[3];
		 char    NATMEN3[3];
		 char    NATBAS4[3];
		 char    NATMEN4[3];
		 char    NATBAS5[3];
		 char    NATMEN5[3];
		 char    NATBAS6[3];
		 char    NATMEN6[3];
		 char    NATLOE[1];
		 char    NATHV[1];
		 char    NATFILLER[57];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DRNAT_BES [] =
 {
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    5 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   57 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DRNAT_BES [] =
 {
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_C,    5 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   57 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDRNAT
 {
  public:

  DRNAT s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DRNAT_BES, DRNAT_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DRNAT_BES, DRNAT_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DRNAT_BES, DRNAT_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDRNAT()
  {
   ::buf_default((void *)&s, DRNAT_BES, DRNAT_ANZ);
  }
 };
#endif

