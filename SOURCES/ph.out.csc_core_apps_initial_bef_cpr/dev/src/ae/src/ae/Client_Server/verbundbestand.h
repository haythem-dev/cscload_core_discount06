/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_VERBUNDBESTAND_ARTIKEL_NR           11
 #define L_VERBUNDBESTAND_BESTAND1             11
 #define L_VERBUNDBESTAND_BESTAND2             11
 #define L_VERBUNDBESTAND_BESTAND3             11
 #define L_VERBUNDBESTAND_BESTAND4             11
 #define L_VERBUNDBESTAND_BESTAND5             11
 #define L_VERBUNDBESTAND_BESTAND6             11
 #define L_VERBUNDBESTAND_BESTAND7             11
 #define L_VERBUNDBESTAND_BESTAND8             11
 #define L_VERBUNDBESTAND_BESTAND9             11
 #define L_VERBUNDBESTAND_BESTAND10            11
 #define L_VERBUNDBESTAND_BESTAND11            11
 #define L_VERBUNDBESTAND_BESTAND12            11
 #define L_VERBUNDBESTAND_BESTAND13            11
 #define L_VERBUNDBESTAND_BESTAND14            11
 #define L_VERBUNDBESTAND_BESTAND15            11
 #define L_VERBUNDBESTAND_BESTAND16            11
 #define L_VERBUNDBESTAND_BESTAND17            11
 #define L_VERBUNDBESTAND_BESTAND18            11
 #define L_VERBUNDBESTAND_BESTAND19            11
 #define L_VERBUNDBESTAND_BESTAND20            11
 #define L_VERBUNDBESTAND_BESTAND21            11
 #define L_VERBUNDBESTAND_BESTAND22            11
 #define L_VERBUNDBESTAND_BESTAND23            11
 #define L_VERBUNDBESTAND_BESTAND24            11


 #define L_VERBUNDBESTAND_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define VERBUNDBESTAND_ANZ ( sizeof(VERBUNDBESTAND_BES) / sizeof(struct buf_desc) )
#endif
 #define G_VERBUNDBESTAND sizeof(struct VERBUNDBESTAND)


 #define VERBUNDBESTAND_H

 #define VERBUNDBESTAND_LISTE \
 			VERBUNDBESTAND.ARTIKEL_NR, \
 			VERBUNDBESTAND.BESTAND1, \
 			VERBUNDBESTAND.BESTAND2, \
 			VERBUNDBESTAND.BESTAND3, \
 			VERBUNDBESTAND.BESTAND4, \
 			VERBUNDBESTAND.BESTAND5, \
 			VERBUNDBESTAND.BESTAND6, \
 			VERBUNDBESTAND.BESTAND7, \
 			VERBUNDBESTAND.BESTAND8, \
 			VERBUNDBESTAND.BESTAND9, \
 			VERBUNDBESTAND.BESTAND10, \
 			VERBUNDBESTAND.BESTAND11, \
 			VERBUNDBESTAND.BESTAND12, \
 			VERBUNDBESTAND.BESTAND13, \
 			VERBUNDBESTAND.BESTAND14, \
 			VERBUNDBESTAND.BESTAND15, \
 			VERBUNDBESTAND.BESTAND16, \
 			VERBUNDBESTAND.BESTAND17, \
 			VERBUNDBESTAND.BESTAND18, \
 			VERBUNDBESTAND.BESTAND19, \
 			VERBUNDBESTAND.BESTAND20, \
 			VERBUNDBESTAND.BESTAND21, \
 			VERBUNDBESTAND.BESTAND22, \
 			VERBUNDBESTAND.BESTAND23, \
 			VERBUNDBESTAND.BESTAND24
 #define VERBUNDBESTAND_PLISTE \
 			"VERBUNDBESTAND.ARTIKEL_NR," \
 			"VERBUNDBESTAND.BESTAND1," \
 			"VERBUNDBESTAND.BESTAND2," \
 			"VERBUNDBESTAND.BESTAND3," \
 			"VERBUNDBESTAND.BESTAND4," \
 			"VERBUNDBESTAND.BESTAND5," \
 			"VERBUNDBESTAND.BESTAND6," \
 			"VERBUNDBESTAND.BESTAND7," \
 			"VERBUNDBESTAND.BESTAND8," \
 			"VERBUNDBESTAND.BESTAND9," \
 			"VERBUNDBESTAND.BESTAND10," \
 			"VERBUNDBESTAND.BESTAND11," \
 			"VERBUNDBESTAND.BESTAND12," \
 			"VERBUNDBESTAND.BESTAND13," \
 			"VERBUNDBESTAND.BESTAND14," \
 			"VERBUNDBESTAND.BESTAND15," \
 			"VERBUNDBESTAND.BESTAND16," \
 			"VERBUNDBESTAND.BESTAND17," \
 			"VERBUNDBESTAND.BESTAND18," \
 			"VERBUNDBESTAND.BESTAND19," \
 			"VERBUNDBESTAND.BESTAND20," \
 			"VERBUNDBESTAND.BESTAND21," \
 			"VERBUNDBESTAND.BESTAND22," \
 			"VERBUNDBESTAND.BESTAND23," \
 			"VERBUNDBESTAND.BESTAND24 " 

 #define VERBUNDBESTAND_PELISTE \
 			"ARTIKEL_NR," \
 			"BESTAND1," \
 			"BESTAND2," \
 			"BESTAND3," \
 			"BESTAND4," \
 			"BESTAND5," \
 			"BESTAND6," \
 			"BESTAND7," \
 			"BESTAND8," \
 			"BESTAND9," \
 			"BESTAND10," \
 			"BESTAND11," \
 			"BESTAND12," \
 			"BESTAND13," \
 			"BESTAND14," \
 			"BESTAND15," \
 			"BESTAND16," \
 			"BESTAND17," \
 			"BESTAND18," \
 			"BESTAND19," \
 			"BESTAND20," \
 			"BESTAND21," \
 			"BESTAND22," \
 			"BESTAND23," \
 			"BESTAND24 " 

 #define VERBUNDBESTAND_UPDLISTE \
 			"ARTIKEL_NR=?," \
 			"BESTAND1=?," \
 			"BESTAND2=?," \
 			"BESTAND3=?," \
 			"BESTAND4=?," \
 			"BESTAND5=?," \
 			"BESTAND6=?," \
 			"BESTAND7=?," \
 			"BESTAND8=?," \
 			"BESTAND9=?," \
 			"BESTAND10=?," \
 			"BESTAND11=?," \
 			"BESTAND12=?," \
 			"BESTAND13=?," \
 			"BESTAND14=?," \
 			"BESTAND15=?," \
 			"BESTAND16=?," \
 			"BESTAND17=?," \
 			"BESTAND18=?," \
 			"BESTAND19=?," \
 			"BESTAND20=?," \
 			"BESTAND21=?," \
 			"BESTAND22=?," \
 			"BESTAND23=?," \
 			"BESTAND24=? " 

 #define VERBUNDBESTANDARTIKEL_NR                    0
 #define VERBUNDBESTANDBESTAND1                      1
 #define VERBUNDBESTANDBESTAND2                      2
 #define VERBUNDBESTANDBESTAND3                      3
 #define VERBUNDBESTANDBESTAND4                      4
 #define VERBUNDBESTANDBESTAND5                      5
 #define VERBUNDBESTANDBESTAND6                      6
 #define VERBUNDBESTANDBESTAND7                      7
 #define VERBUNDBESTANDBESTAND8                      8
 #define VERBUNDBESTANDBESTAND9                      9
 #define VERBUNDBESTANDBESTAND10                     10
 #define VERBUNDBESTANDBESTAND11                     11
 #define VERBUNDBESTANDBESTAND12                     12
 #define VERBUNDBESTANDBESTAND13                     13
 #define VERBUNDBESTANDBESTAND14                     14
 #define VERBUNDBESTANDBESTAND15                     15
 #define VERBUNDBESTANDBESTAND16                     16
 #define VERBUNDBESTANDBESTAND17                     17
 #define VERBUNDBESTANDBESTAND18                     18
 #define VERBUNDBESTANDBESTAND19                     19
 #define VERBUNDBESTANDBESTAND20                     20
 #define VERBUNDBESTANDBESTAND21                     21
 #define VERBUNDBESTANDBESTAND22                     22
 #define VERBUNDBESTANDBESTAND23                     23
 #define VERBUNDBESTANDBESTAND24                     24

 #define VERBUNDBESTAND_ZEIGER(xxx) \
 			:xxx->ARTIKEL_NR,\
 			:xxx->BESTAND1,\
 			:xxx->BESTAND2,\
 			:xxx->BESTAND3,\
 			:xxx->BESTAND4,\
 			:xxx->BESTAND5,\
 			:xxx->BESTAND6,\
 			:xxx->BESTAND7,\
 			:xxx->BESTAND8,\
 			:xxx->BESTAND9,\
 			:xxx->BESTAND10,\
 			:xxx->BESTAND11,\
 			:xxx->BESTAND12,\
 			:xxx->BESTAND13,\
 			:xxx->BESTAND14,\
 			:xxx->BESTAND15,\
 			:xxx->BESTAND16,\
 			:xxx->BESTAND17,\
 			:xxx->BESTAND18,\
 			:xxx->BESTAND19,\
 			:xxx->BESTAND20,\
 			:xxx->BESTAND21,\
 			:xxx->BESTAND22,\
 			:xxx->BESTAND23,\
 			:xxx->BESTAND24

 #define VERBUNDBESTAND_UPDATE(xxx) \
 			ARTIKEL_NR = :xxx->ARTIKEL_NR,\
 			BESTAND1 = :xxx->BESTAND1,\
 			BESTAND2 = :xxx->BESTAND2,\
 			BESTAND3 = :xxx->BESTAND3,\
 			BESTAND4 = :xxx->BESTAND4,\
 			BESTAND5 = :xxx->BESTAND5,\
 			BESTAND6 = :xxx->BESTAND6,\
 			BESTAND7 = :xxx->BESTAND7,\
 			BESTAND8 = :xxx->BESTAND8,\
 			BESTAND9 = :xxx->BESTAND9,\
 			BESTAND10 = :xxx->BESTAND10,\
 			BESTAND11 = :xxx->BESTAND11,\
 			BESTAND12 = :xxx->BESTAND12,\
 			BESTAND13 = :xxx->BESTAND13,\
 			BESTAND14 = :xxx->BESTAND14,\
 			BESTAND15 = :xxx->BESTAND15,\
 			BESTAND16 = :xxx->BESTAND16,\
 			BESTAND17 = :xxx->BESTAND17,\
 			BESTAND18 = :xxx->BESTAND18,\
 			BESTAND19 = :xxx->BESTAND19,\
 			BESTAND20 = :xxx->BESTAND20,\
 			BESTAND21 = :xxx->BESTAND21,\
 			BESTAND22 = :xxx->BESTAND22,\
 			BESTAND23 = :xxx->BESTAND23,\
 			BESTAND24 = :xxx->BESTAND24

 #define LS_VERBUNDBESTAND_ARTIKEL_NR           11
 #define LS_VERBUNDBESTAND_BESTAND1             11
 #define LS_VERBUNDBESTAND_BESTAND2             11
 #define LS_VERBUNDBESTAND_BESTAND3             11
 #define LS_VERBUNDBESTAND_BESTAND4             11
 #define LS_VERBUNDBESTAND_BESTAND5             11
 #define LS_VERBUNDBESTAND_BESTAND6             11
 #define LS_VERBUNDBESTAND_BESTAND7             11
 #define LS_VERBUNDBESTAND_BESTAND8             11
 #define LS_VERBUNDBESTAND_BESTAND9             11
 #define LS_VERBUNDBESTAND_BESTAND10            11
 #define LS_VERBUNDBESTAND_BESTAND11            11
 #define LS_VERBUNDBESTAND_BESTAND12            11
 #define LS_VERBUNDBESTAND_BESTAND13            11
 #define LS_VERBUNDBESTAND_BESTAND14            11
 #define LS_VERBUNDBESTAND_BESTAND15            11
 #define LS_VERBUNDBESTAND_BESTAND16            11
 #define LS_VERBUNDBESTAND_BESTAND17            11
 #define LS_VERBUNDBESTAND_BESTAND18            11
 #define LS_VERBUNDBESTAND_BESTAND19            11
 #define LS_VERBUNDBESTAND_BESTAND20            11
 #define LS_VERBUNDBESTAND_BESTAND21            11
 #define LS_VERBUNDBESTAND_BESTAND22            11
 #define LS_VERBUNDBESTAND_BESTAND23            11
 #define LS_VERBUNDBESTAND_BESTAND24            11

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct VERBUNDBESTAND {
		 long    ARTIKEL_NR;
		 long    BESTAND1;
		 long    BESTAND2;
		 long    BESTAND3;
		 long    BESTAND4;
		 long    BESTAND5;
		 long    BESTAND6;
		 long    BESTAND7;
		 long    BESTAND8;
		 long    BESTAND9;
		 long    BESTAND10;
		 long    BESTAND11;
		 long    BESTAND12;
		 long    BESTAND13;
		 long    BESTAND14;
		 long    BESTAND15;
		 long    BESTAND16;
		 long    BESTAND17;
		 long    BESTAND18;
		 long    BESTAND19;
		 long    BESTAND20;
		 long    BESTAND21;
		 long    BESTAND22;
		 long    BESTAND23;
		 long    BESTAND24;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_VERBUNDBESTAND {
		 long    ARTIKEL_NR;
		 long    BESTAND1;
		 long    BESTAND2;
		 long    BESTAND3;
		 long    BESTAND4;
		 long    BESTAND5;
		 long    BESTAND6;
		 long    BESTAND7;
		 long    BESTAND8;
		 long    BESTAND9;
		 long    BESTAND10;
		 long    BESTAND11;
		 long    BESTAND12;
		 long    BESTAND13;
		 long    BESTAND14;
		 long    BESTAND15;
		 long    BESTAND16;
		 long    BESTAND17;
		 long    BESTAND18;
		 long    BESTAND19;
		 long    BESTAND20;
		 long    BESTAND21;
		 long    BESTAND22;
		 long    BESTAND23;
		 long    BESTAND24;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_VERBUNDBESTAND {
		 short  ARTIKEL_NR;
		 short  BESTAND1;
		 short  BESTAND2;
		 short  BESTAND3;
		 short  BESTAND4;
		 short  BESTAND5;
		 short  BESTAND6;
		 short  BESTAND7;
		 short  BESTAND8;
		 short  BESTAND9;
		 short  BESTAND10;
		 short  BESTAND11;
		 short  BESTAND12;
		 short  BESTAND13;
		 short  BESTAND14;
		 short  BESTAND15;
		 short  BESTAND16;
		 short  BESTAND17;
		 short  BESTAND18;
		 short  BESTAND19;
		 short  BESTAND20;
		 short  BESTAND21;
		 short  BESTAND22;
		 short  BESTAND23;
		 short  BESTAND24;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_VERBUNDBESTAND {
		 char    ARTIKEL_NR[11];
		 char    BESTAND1[11];
		 char    BESTAND2[11];
		 char    BESTAND3[11];
		 char    BESTAND4[11];
		 char    BESTAND5[11];
		 char    BESTAND6[11];
		 char    BESTAND7[11];
		 char    BESTAND8[11];
		 char    BESTAND9[11];
		 char    BESTAND10[11];
		 char    BESTAND11[11];
		 char    BESTAND12[11];
		 char    BESTAND13[11];
		 char    BESTAND14[11];
		 char    BESTAND15[11];
		 char    BESTAND16[11];
		 char    BESTAND17[11];
		 char    BESTAND18[11];
		 char    BESTAND19[11];
		 char    BESTAND20[11];
		 char    BESTAND21[11];
		 char    BESTAND22[11];
		 char    BESTAND23[11];
		 char    BESTAND24[11];
       };

 struct O_VERBUNDBESTAND {
		 char    ARTIKEL_NR[11];
		 char    BESTAND1[11];
		 char    BESTAND2[11];
		 char    BESTAND3[11];
		 char    BESTAND4[11];
		 char    BESTAND5[11];
		 char    BESTAND6[11];
		 char    BESTAND7[11];
		 char    BESTAND8[11];
		 char    BESTAND9[11];
		 char    BESTAND10[11];
		 char    BESTAND11[11];
		 char    BESTAND12[11];
		 char    BESTAND13[11];
		 char    BESTAND14[11];
		 char    BESTAND15[11];
		 char    BESTAND16[11];
		 char    BESTAND17[11];
		 char    BESTAND18[11];
		 char    BESTAND19[11];
		 char    BESTAND20[11];
		 char    BESTAND21[11];
		 char    BESTAND22[11];
		 char    BESTAND23[11];
		 char    BESTAND24[11];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc VERBUNDBESTAND_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc VERBUNDBESTAND_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CVERBUNDBESTAND
 {
  public:

  VERBUNDBESTAND s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, VERBUNDBESTAND_BES, VERBUNDBESTAND_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,VERBUNDBESTAND_BES, VERBUNDBESTAND_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,VERBUNDBESTAND_BES, VERBUNDBESTAND_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CVERBUNDBESTAND()
  {
   ::buf_default((void *)&s, VERBUNDBESTAND_BES, VERBUNDBESTAND_ANZ);
  }
 };
#endif

#define VERBUNDBESTAND_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 ARTIKEL_NR         INTEGER         default 0 NOT NULL,\
		 BESTAND1           INTEGER         default 0 NOT NULL,\
		 BESTAND2           INTEGER         default 0 NOT NULL,\
		 BESTAND3           INTEGER         default 0 NOT NULL,\
		 BESTAND4           INTEGER         default 0 NOT NULL,\
		 BESTAND5           INTEGER         default 0 NOT NULL,\
		 BESTAND6           INTEGER         default 0 NOT NULL,\
		 BESTAND7           INTEGER         default 0 NOT NULL,\
		 BESTAND8           INTEGER         default 0 NOT NULL,\
		 BESTAND9           INTEGER         default 0 NOT NULL,\
		 BESTAND10          INTEGER         default 0 NOT NULL,\
		 BESTAND11          INTEGER         default 0 NOT NULL,\
		 BESTAND12          INTEGER         default 0 NOT NULL,\
		 BESTAND13          INTEGER         default 0 NOT NULL,\
		 BESTAND14          INTEGER         default 0 NOT NULL,\
		 BESTAND15          INTEGER         default 0 NOT NULL,\
		 BESTAND16          INTEGER         default 0 NOT NULL,\
		 BESTAND17          INTEGER         default 0 NOT NULL,\
		 BESTAND18          INTEGER         default 0 NOT NULL,\
		 BESTAND19          INTEGER         default 0 NOT NULL,\
		 BESTAND20          INTEGER         default 0 NOT NULL,\
		 BESTAND21          INTEGER         default 0 NOT NULL,\
		 BESTAND22          INTEGER         default 0 NOT NULL,\
		 BESTAND23          INTEGER         default 0 NOT NULL,\
		 BESTAND24          INTEGER         default 0 NOT NULL  ) EXTENT SIZE 34396 LOCK MODE ROW;

#define VERBUNDBESTAND_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX I_VERBUNDBESTAND_1 on yyy( ARTIKEL_NR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define VERBUNDBESTAND_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX I_VERBUNDBESTAND_1;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

