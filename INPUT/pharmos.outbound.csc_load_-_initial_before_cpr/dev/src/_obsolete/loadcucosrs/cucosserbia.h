#ifndef __PP_CUCOSSERBIA_H_
#define __PP_CUCOSSERBIA_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadcucosrs\cucosserbia *************************************/
/******************************************************************************/

/* Length-Define of CUCOSSERBIA ***********************************************/

  #define L_CUCOSSERBIA_BRANCHNO 6
  #define L_CUCOSSERBIA_CUSTOMERNO 11
  #define L_CUCOSSERBIA_ARTICLENO 11
  #define L_CUCOSSERBIA_PREISEKAPO 9
  #define N_CUCOSSERBIA_PREISEKAPO 2
  #define L_CUCOSSERBIA_BASEQTY 11
  #define L_CUCOSSERBIA_DISCOUNTVALUEPCT 5
  #define N_CUCOSSERBIA_DISCOUNTVALUEPCT 2
  #define L_CUCOSSERBIA_DISCOUNTPRICE 11
  #define N_CUCOSSERBIA_DISCOUNTPRICE 2
  #define L_CUCOSSERBIA_DISCOUNTPCT1 5
  #define N_CUCOSSERBIA_DISCOUNTPCT1 2
  #define L_CUCOSSERBIA_DISCOUNTPRICE1 11
  #define N_CUCOSSERBIA_DISCOUNTPRICE1 2
  #define L_CUCOSSERBIA_PAYTERM1 6
  #define L_CUCOSSERBIA_DISCOUNTPCT2 5
  #define N_CUCOSSERBIA_DISCOUNTPCT2 2
  #define L_CUCOSSERBIA_DISCOUNTPRICE2 11
  #define N_CUCOSSERBIA_DISCOUNTPRICE2 2
  #define L_CUCOSSERBIA_PAYTERM2 6
  #define L_CUCOSSERBIA_DISCOUNTPCT3 5
  #define N_CUCOSSERBIA_DISCOUNTPCT3 2
  #define L_CUCOSSERBIA_DISCOUNTPRICE3 11
  #define N_CUCOSSERBIA_DISCOUNTPRICE3 2
  #define L_CUCOSSERBIA_PAYTERM3 6
  #define L_CUCOSSERBIA_DISCOUNTPCT4 5
  #define N_CUCOSSERBIA_DISCOUNTPCT4 2
  #define L_CUCOSSERBIA_DISCOUNTPRICE4 11
  #define N_CUCOSSERBIA_DISCOUNTPRICE4 2
  #define L_CUCOSSERBIA_PAYTERM4 6
  #define L_CUCOSSERBIA_DISCOUNTPCT5 5
  #define N_CUCOSSERBIA_DISCOUNTPCT5 2
  #define L_CUCOSSERBIA_DISCOUNTPRICE5 11
  #define N_CUCOSSERBIA_DISCOUNTPRICE5 2
  #define L_CUCOSSERBIA_PAYTERM5 6
  #define L_CUCOSSERBIA_DISCOUNTPCT6 5
  #define N_CUCOSSERBIA_DISCOUNTPCT6 2
  #define L_CUCOSSERBIA_DISCOUNTPRICE6 11
  #define N_CUCOSSERBIA_DISCOUNTPRICE6 2
  #define L_CUCOSSERBIA_PAYTERM6 6
  #define L_CUCOSSERBIA_CASCADE 6

/* Length/Count-Define of CUCOSSERBIA *****************************************/

  #define LS_CUCOSSERBIA_BRANCHNO 5 + 1
  #define LS_CUCOSSERBIA_CUSTOMERNO 10 + 1
  #define LS_CUCOSSERBIA_ARTICLENO 10 + 1
  #define LS_CUCOSSERBIA_PREISEKAPO 9 + 2
  #define LS_CUCOSSERBIA_BASEQTY 10 + 1
  #define LS_CUCOSSERBIA_DISCOUNTVALUEPCT 5 + 2
  #define LS_CUCOSSERBIA_DISCOUNTPRICE 11 + 2
  #define LS_CUCOSSERBIA_DISCOUNTPCT1 5 + 2
  #define LS_CUCOSSERBIA_DISCOUNTPRICE1 11 + 2
  #define LS_CUCOSSERBIA_PAYTERM1 5 + 1
  #define LS_CUCOSSERBIA_DISCOUNTPCT2 5 + 2
  #define LS_CUCOSSERBIA_DISCOUNTPRICE2 11 + 2
  #define LS_CUCOSSERBIA_PAYTERM2 5 + 1
  #define LS_CUCOSSERBIA_DISCOUNTPCT3 5 + 2
  #define LS_CUCOSSERBIA_DISCOUNTPRICE3 11 + 2
  #define LS_CUCOSSERBIA_PAYTERM3 5 + 1
  #define LS_CUCOSSERBIA_DISCOUNTPCT4 5 + 2
  #define LS_CUCOSSERBIA_DISCOUNTPRICE4 11 + 2
  #define LS_CUCOSSERBIA_PAYTERM4 5 + 1
  #define LS_CUCOSSERBIA_DISCOUNTPCT5 5 + 2
  #define LS_CUCOSSERBIA_DISCOUNTPRICE5 11 + 2
  #define LS_CUCOSSERBIA_PAYTERM5 5 + 1
  #define LS_CUCOSSERBIA_DISCOUNTPCT6 5 + 2
  #define LS_CUCOSSERBIA_DISCOUNTPRICE6 11 + 2
  #define LS_CUCOSSERBIA_PAYTERM6 5 + 1
  #define LS_CUCOSSERBIA_CASCADE 5 + 1

  #define CUCOSSERBIABRANCHNO 0
  #define CUCOSSERBIACUSTOMERNO 1
  #define CUCOSSERBIAARTICLENO 2
  #define CUCOSSERBIAPREISEKAPO 3
  #define CUCOSSERBIABASEQTY 4
  #define CUCOSSERBIADISCOUNTVALUEPCT 5
  #define CUCOSSERBIADISCOUNTPRICE 6
  #define CUCOSSERBIADISCOUNTPCT1 7
  #define CUCOSSERBIADISCOUNTPRICE1 8
  #define CUCOSSERBIAPAYTERM1 9
  #define CUCOSSERBIADISCOUNTPCT2 10
  #define CUCOSSERBIADISCOUNTPRICE2 11
  #define CUCOSSERBIAPAYTERM2 12
  #define CUCOSSERBIADISCOUNTPCT3 13
  #define CUCOSSERBIADISCOUNTPRICE3 14
  #define CUCOSSERBIAPAYTERM3 15
  #define CUCOSSERBIADISCOUNTPCT4 16
  #define CUCOSSERBIADISCOUNTPRICE4 17
  #define CUCOSSERBIAPAYTERM4 18
  #define CUCOSSERBIADISCOUNTPCT5 19
  #define CUCOSSERBIADISCOUNTPRICE5 20
  #define CUCOSSERBIAPAYTERM5 21
  #define CUCOSSERBIADISCOUNTPCT6 22
  #define CUCOSSERBIADISCOUNTPRICE6 23
  #define CUCOSSERBIAPAYTERM6 24
  #define CUCOSSERBIACASCADE 25

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CUCOSSERBIA_H
 #define CUCOSSERBIA_ANZ ( sizeof(CUCOSSERBIA_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUCOSSERBIA ***************************************************/

 #define CUCOSSERBIA_LISTE \
         CUCOSSERBIA.BRANCHNO,\
         CUCOSSERBIA.CUSTOMERNO,\
         CUCOSSERBIA.ARTICLENO,\
         CUCOSSERBIA.PREISEKAPO,\
         CUCOSSERBIA.BASEQTY,\
         CUCOSSERBIA.DISCOUNTVALUEPCT,\
         CUCOSSERBIA.DISCOUNTPRICE,\
         CUCOSSERBIA.DISCOUNTPCT1,\
         CUCOSSERBIA.DISCOUNTPRICE1,\
         CUCOSSERBIA.PAYTERM1,\
         CUCOSSERBIA.DISCOUNTPCT2,\
         CUCOSSERBIA.DISCOUNTPRICE2,\
         CUCOSSERBIA.PAYTERM2,\
         CUCOSSERBIA.DISCOUNTPCT3,\
         CUCOSSERBIA.DISCOUNTPRICE3,\
         CUCOSSERBIA.PAYTERM3,\
         CUCOSSERBIA.DISCOUNTPCT4,\
         CUCOSSERBIA.DISCOUNTPRICE4,\
         CUCOSSERBIA.PAYTERM4,\
         CUCOSSERBIA.DISCOUNTPCT5,\
         CUCOSSERBIA.DISCOUNTPRICE5,\
         CUCOSSERBIA.PAYTERM5,\
         CUCOSSERBIA.DISCOUNTPCT6,\
         CUCOSSERBIA.DISCOUNTPRICE6,\
         CUCOSSERBIA.PAYTERM6,\
         CUCOSSERBIA.CASCADE

 #define CUCOSSERBIA_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         ARTICLENO,\
         PREISEKAPO,\
         BASEQTY,\
         DISCOUNTVALUEPCT,\
         DISCOUNTPRICE,\
         DISCOUNTPCT1,\
         DISCOUNTPRICE1,\
         PAYTERM1,\
         DISCOUNTPCT2,\
         DISCOUNTPRICE2,\
         PAYTERM2,\
         DISCOUNTPCT3,\
         DISCOUNTPRICE3,\
         PAYTERM3,\
         DISCOUNTPCT4,\
         DISCOUNTPRICE4,\
         PAYTERM4,\
         DISCOUNTPCT5,\
         DISCOUNTPRICE5,\
         PAYTERM5,\
         DISCOUNTPCT6,\
         DISCOUNTPRICE6,\
         PAYTERM6,\
         CASCADE

 #define CUCOSSERBIA_PLISTE \
         "CUCOSSERBIA.BRANCHNO,"\
         "CUCOSSERBIA.CUSTOMERNO,"\
         "CUCOSSERBIA.ARTICLENO,"\
         "CUCOSSERBIA.PREISEKAPO,"\
         "CUCOSSERBIA.BASEQTY,"\
         "CUCOSSERBIA.DISCOUNTVALUEPCT,"\
         "CUCOSSERBIA.DISCOUNTPRICE,"\
         "CUCOSSERBIA.DISCOUNTPCT1,"\
         "CUCOSSERBIA.DISCOUNTPRICE1,"\
         "CUCOSSERBIA.PAYTERM1,"\
         "CUCOSSERBIA.DISCOUNTPCT2,"\
         "CUCOSSERBIA.DISCOUNTPRICE2,"\
         "CUCOSSERBIA.PAYTERM2,"\
         "CUCOSSERBIA.DISCOUNTPCT3,"\
         "CUCOSSERBIA.DISCOUNTPRICE3,"\
         "CUCOSSERBIA.PAYTERM3,"\
         "CUCOSSERBIA.DISCOUNTPCT4,"\
         "CUCOSSERBIA.DISCOUNTPRICE4,"\
         "CUCOSSERBIA.PAYTERM4,"\
         "CUCOSSERBIA.DISCOUNTPCT5,"\
         "CUCOSSERBIA.DISCOUNTPRICE5,"\
         "CUCOSSERBIA.PAYTERM5,"\
         "CUCOSSERBIA.DISCOUNTPCT6,"\
         "CUCOSSERBIA.DISCOUNTPRICE6,"\
         "CUCOSSERBIA.PAYTERM6,"\
         "CUCOSSERBIA.CASCADE"

 #define CUCOSSERBIA_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "ARTICLENO,"\
         "PREISEKAPO,"\
         "BASEQTY,"\
         "DISCOUNTVALUEPCT,"\
         "DISCOUNTPRICE,"\
         "DISCOUNTPCT1,"\
         "DISCOUNTPRICE1,"\
         "PAYTERM1,"\
         "DISCOUNTPCT2,"\
         "DISCOUNTPRICE2,"\
         "PAYTERM2,"\
         "DISCOUNTPCT3,"\
         "DISCOUNTPRICE3,"\
         "PAYTERM3,"\
         "DISCOUNTPCT4,"\
         "DISCOUNTPRICE4,"\
         "PAYTERM4,"\
         "DISCOUNTPCT5,"\
         "DISCOUNTPRICE5,"\
         "PAYTERM5,"\
         "DISCOUNTPCT6,"\
         "DISCOUNTPRICE6,"\
         "PAYTERM6,"\
         "CASCADE"

 #define CUCOSSERBIA_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "ARTICLENO=?,"\
         "PREISEKAPO=?,"\
         "BASEQTY=?,"\
         "DISCOUNTVALUEPCT=?,"\
         "DISCOUNTPRICE=?,"\
         "DISCOUNTPCT1=?,"\
         "DISCOUNTPRICE1=?,"\
         "PAYTERM1=?,"\
         "DISCOUNTPCT2=?,"\
         "DISCOUNTPRICE2=?,"\
         "PAYTERM2=?,"\
         "DISCOUNTPCT3=?,"\
         "DISCOUNTPRICE3=?,"\
         "PAYTERM3=?,"\
         "DISCOUNTPCT4=?,"\
         "DISCOUNTPRICE4=?,"\
         "PAYTERM4=?,"\
         "DISCOUNTPCT5=?,"\
         "DISCOUNTPRICE5=?,"\
         "PAYTERM5=?,"\
         "DISCOUNTPCT6=?,"\
         "DISCOUNTPRICE6=?,"\
         "PAYTERM6=?,"\
         "CASCADE=?"

/* SqlMacros-Define of CUCOSSERBIA ********************************************/

 #define CUCOSSERBIA_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ARTICLENO,\
         :x->PREISEKAPO,\
         :x->BASEQTY,\
         :x->DISCOUNTVALUEPCT,\
         :x->DISCOUNTPRICE,\
         :x->DISCOUNTPCT1,\
         :x->DISCOUNTPRICE1,\
         :x->PAYTERM1,\
         :x->DISCOUNTPCT2,\
         :x->DISCOUNTPRICE2,\
         :x->PAYTERM2,\
         :x->DISCOUNTPCT3,\
         :x->DISCOUNTPRICE3,\
         :x->PAYTERM3,\
         :x->DISCOUNTPCT4,\
         :x->DISCOUNTPRICE4,\
         :x->PAYTERM4,\
         :x->DISCOUNTPCT5,\
         :x->DISCOUNTPRICE5,\
         :x->PAYTERM5,\
         :x->DISCOUNTPCT6,\
         :x->DISCOUNTPRICE6,\
         :x->PAYTERM6,\
         :x->CASCADE

 #define CUCOSSERBIA_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ARTICLENO,\
         :x->PREISEKAPO,\
         :x->BASEQTY,\
         :x->DISCOUNTVALUEPCT,\
         :x->DISCOUNTPRICE,\
         :x->DISCOUNTPCT1,\
         :x->DISCOUNTPRICE1,\
         :x->PAYTERM1,\
         :x->DISCOUNTPCT2,\
         :x->DISCOUNTPRICE2,\
         :x->PAYTERM2,\
         :x->DISCOUNTPCT3,\
         :x->DISCOUNTPRICE3,\
         :x->PAYTERM3,\
         :x->DISCOUNTPCT4,\
         :x->DISCOUNTPRICE4,\
         :x->PAYTERM4,\
         :x->DISCOUNTPCT5,\
         :x->DISCOUNTPRICE5,\
         :x->PAYTERM5,\
         :x->DISCOUNTPCT6,\
         :x->DISCOUNTPRICE6,\
         :x->PAYTERM6,\
         :x->CASCADE

 #define CUCOSSERBIA_UPDATE(x) \
         CUCOSSERBIA.BRANCHNO=:x->BRANCHNO,\
         CUCOSSERBIA.CUSTOMERNO=:x->CUSTOMERNO,\
         CUCOSSERBIA.ARTICLENO=:x->ARTICLENO,\
         CUCOSSERBIA.PREISEKAPO=:x->PREISEKAPO,\
         CUCOSSERBIA.BASEQTY=:x->BASEQTY,\
         CUCOSSERBIA.DISCOUNTVALUEPCT=:x->DISCOUNTVALUEPCT,\
         CUCOSSERBIA.DISCOUNTPRICE=:x->DISCOUNTPRICE,\
         CUCOSSERBIA.DISCOUNTPCT1=:x->DISCOUNTPCT1,\
         CUCOSSERBIA.DISCOUNTPRICE1=:x->DISCOUNTPRICE1,\
         CUCOSSERBIA.PAYTERM1=:x->PAYTERM1,\
         CUCOSSERBIA.DISCOUNTPCT2=:x->DISCOUNTPCT2,\
         CUCOSSERBIA.DISCOUNTPRICE2=:x->DISCOUNTPRICE2,\
         CUCOSSERBIA.PAYTERM2=:x->PAYTERM2,\
         CUCOSSERBIA.DISCOUNTPCT3=:x->DISCOUNTPCT3,\
         CUCOSSERBIA.DISCOUNTPRICE3=:x->DISCOUNTPRICE3,\
         CUCOSSERBIA.PAYTERM3=:x->PAYTERM3,\
         CUCOSSERBIA.DISCOUNTPCT4=:x->DISCOUNTPCT4,\
         CUCOSSERBIA.DISCOUNTPRICE4=:x->DISCOUNTPRICE4,\
         CUCOSSERBIA.PAYTERM4=:x->PAYTERM4,\
         CUCOSSERBIA.DISCOUNTPCT5=:x->DISCOUNTPCT5,\
         CUCOSSERBIA.DISCOUNTPRICE5=:x->DISCOUNTPRICE5,\
         CUCOSSERBIA.PAYTERM5=:x->PAYTERM5,\
         CUCOSSERBIA.DISCOUNTPCT6=:x->DISCOUNTPCT6,\
         CUCOSSERBIA.DISCOUNTPRICE6=:x->DISCOUNTPRICE6,\
         CUCOSSERBIA.PAYTERM6=:x->PAYTERM6,\
         CUCOSSERBIA.CASCADE=:x->CASCADE

/* SqlMacros390-Define of CUCOSSERBIA *****************************************/

 #define CUCOSSERBIA_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :ARTICLENO,\
         :PREISEKAPO,\
         :BASEQTY,\
         :DISCOUNTVALUEPCT,\
         :DISCOUNTPRICE,\
         :DISCOUNTPCT1,\
         :DISCOUNTPRICE1,\
         :PAYTERM1,\
         :DISCOUNTPCT2,\
         :DISCOUNTPRICE2,\
         :PAYTERM2,\
         :DISCOUNTPCT3,\
         :DISCOUNTPRICE3,\
         :PAYTERM3,\
         :DISCOUNTPCT4,\
         :DISCOUNTPRICE4,\
         :PAYTERM4,\
         :DISCOUNTPCT5,\
         :DISCOUNTPRICE5,\
         :PAYTERM5,\
         :DISCOUNTPCT6,\
         :DISCOUNTPRICE6,\
         :PAYTERM6,\
         :CASCADE

 #define CUCOSSERBIA_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         ARTICLENO=:ARTICLENO,\
         PREISEKAPO=:PREISEKAPO,\
         BASEQTY=:BASEQTY,\
         DISCOUNTVALUEPCT=:DISCOUNTVALUEPCT,\
         DISCOUNTPRICE=:DISCOUNTPRICE,\
         DISCOUNTPCT1=:DISCOUNTPCT1,\
         DISCOUNTPRICE1=:DISCOUNTPRICE1,\
         PAYTERM1=:PAYTERM1,\
         DISCOUNTPCT2=:DISCOUNTPCT2,\
         DISCOUNTPRICE2=:DISCOUNTPRICE2,\
         PAYTERM2=:PAYTERM2,\
         DISCOUNTPCT3=:DISCOUNTPCT3,\
         DISCOUNTPRICE3=:DISCOUNTPRICE3,\
         PAYTERM3=:PAYTERM3,\
         DISCOUNTPCT4=:DISCOUNTPCT4,\
         DISCOUNTPRICE4=:DISCOUNTPRICE4,\
         PAYTERM4=:PAYTERM4,\
         DISCOUNTPCT5=:DISCOUNTPCT5,\
         DISCOUNTPRICE5=:DISCOUNTPRICE5,\
         PAYTERM5=:PAYTERM5,\
         DISCOUNTPCT6=:DISCOUNTPCT6,\
         DISCOUNTPRICE6=:DISCOUNTPRICE6,\
         PAYTERM6=:PAYTERM6,\
         CASCADE=:CASCADE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CUCOSSERBIA ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_CUCOSSERBIA {
         short BRANCHNO;
         long CUSTOMERNO;
         long ARTICLENO;
         double PREISEKAPO;
         long BASEQTY;
         double DISCOUNTVALUEPCT;
         double DISCOUNTPRICE;
         double DISCOUNTPCT1;
         double DISCOUNTPRICE1;
         short PAYTERM1;
         double DISCOUNTPCT2;
         double DISCOUNTPRICE2;
         short PAYTERM2;
         double DISCOUNTPCT3;
         double DISCOUNTPRICE3;
         short PAYTERM3;
         double DISCOUNTPCT4;
         double DISCOUNTPRICE4;
         short PAYTERM4;
         double DISCOUNTPCT5;
         double DISCOUNTPRICE5;
         short PAYTERM5;
         double DISCOUNTPCT6;
         double DISCOUNTPRICE6;
         short PAYTERM6;
         short CASCADE;
        } cucosserbiaS;
 #else /*TRANSCLASS*/
 typedef struct N_CUCOSSERBIA {
         short BRANCHNO;
         long CUSTOMERNO;
         long ARTICLENO;
         double PREISEKAPO;
         long BASEQTY;
         double DISCOUNTVALUEPCT;
         double DISCOUNTPRICE;
         double DISCOUNTPCT1;
         double DISCOUNTPRICE1;
         short PAYTERM1;
         double DISCOUNTPCT2;
         double DISCOUNTPRICE2;
         short PAYTERM2;
         double DISCOUNTPCT3;
         double DISCOUNTPRICE3;
         short PAYTERM3;
         double DISCOUNTPCT4;
         double DISCOUNTPRICE4;
         short PAYTERM4;
         double DISCOUNTPCT5;
         double DISCOUNTPRICE5;
         short PAYTERM5;
         double DISCOUNTPCT6;
         double DISCOUNTPRICE6;
         short PAYTERM6;
         short CASCADE;

			bool operator==(const N_CUCOSSERBIA& right) const {
			return(
				BRANCHNO == right.BRANCHNO &&
				CUSTOMERNO == right.CUSTOMERNO &&
				ARTICLENO == right.ARTICLENO &&
				PREISEKAPO == right.PREISEKAPO &&
				BASEQTY == right.BASEQTY &&
				DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
				DISCOUNTPRICE == right.DISCOUNTPRICE &&
				DISCOUNTPCT1 == right.DISCOUNTPCT1 &&
				DISCOUNTPRICE1 == right.DISCOUNTPRICE1 &&
				PAYTERM1 == right.PAYTERM1 &&
				DISCOUNTPCT2 == right.DISCOUNTPCT2 &&
				DISCOUNTPRICE2 == right.DISCOUNTPRICE2 &&
				PAYTERM2 == right.PAYTERM2 &&
				DISCOUNTPCT3 == right.DISCOUNTPCT3 &&
				DISCOUNTPRICE3 == right.DISCOUNTPRICE3 &&
				PAYTERM3 == right.PAYTERM3 &&
				DISCOUNTPCT4 == right.DISCOUNTPCT4 &&
				DISCOUNTPRICE4 == right.DISCOUNTPRICE4 &&
				PAYTERM4 == right.PAYTERM4 &&
				DISCOUNTPCT5 == right.DISCOUNTPCT5 &&
				DISCOUNTPRICE5 == right.DISCOUNTPRICE5 &&
				PAYTERM5 == right.PAYTERM5 &&
				DISCOUNTPCT6 == right.DISCOUNTPCT6 &&
				DISCOUNTPRICE6 == right.DISCOUNTPRICE6 &&
				PAYTERM6 == right.PAYTERM6 &&
				CASCADE == right.CASCADE
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				BRANCHNO = 0;
				CUSTOMERNO = 0;
				ARTICLENO = 0;
				PREISEKAPO = 0;
				BASEQTY = 0;
				DISCOUNTVALUEPCT = 0;
				DISCOUNTPRICE = 0;
				DISCOUNTPCT1 = 0;
				DISCOUNTPRICE1 = 0;
				PAYTERM1 = 0;
				DISCOUNTPCT2 = 0;
				DISCOUNTPRICE2 = 0;
				PAYTERM2 = 0;
				DISCOUNTPCT3 = 0;
				DISCOUNTPRICE3 = 0;
				PAYTERM3 = 0;
				DISCOUNTPCT4 = 0;
				DISCOUNTPRICE4 = 0;
				PAYTERM4 = 0;
				DISCOUNTPCT5 = 0;
				DISCOUNTPRICE5 = 0;
				PAYTERM5 = 0;
				DISCOUNTPCT6 = 0;
				DISCOUNTPRICE6 = 0;
				PAYTERM6 = 0;
				CASCADE = 0;
#endif
			}
         } cucosserbiaS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUCOSSERBIA ***************************************/

 struct S_CUCOSSERBIA {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ARTICLENO[11];
         char PREISEKAPO[9 + 2];
         char BASEQTY[11];
         char DISCOUNTVALUEPCT[5 + 2];
         char DISCOUNTPRICE[11 + 2];
         char DISCOUNTPCT1[5 + 2];
         char DISCOUNTPRICE1[11 + 2];
         char PAYTERM1[7];
         char DISCOUNTPCT2[5 + 2];
         char DISCOUNTPRICE2[11 + 2];
         char PAYTERM2[7];
         char DISCOUNTPCT3[5 + 2];
         char DISCOUNTPRICE3[11 + 2];
         char PAYTERM3[7];
         char DISCOUNTPCT4[5 + 2];
         char DISCOUNTPRICE4[11 + 2];
         char PAYTERM4[7];
         char DISCOUNTPCT5[5 + 2];
         char DISCOUNTPRICE5[11 + 2];
         char PAYTERM5[7];
         char DISCOUNTPCT6[5 + 2];
         char DISCOUNTPRICE6[11 + 2];
         char PAYTERM6[7];
         char CASCADE[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUCOSSERBIA **********************/

 struct O_CUCOSSERBIA {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ARTICLENO[11];
         char PREISEKAPO[9];
         char BASEQTY[11];
         char DISCOUNTVALUEPCT[5];
         char DISCOUNTPRICE[11];
         char DISCOUNTPCT1[5];
         char DISCOUNTPRICE1[11];
         char PAYTERM1[7];
         char DISCOUNTPCT2[5];
         char DISCOUNTPRICE2[11];
         char PAYTERM2[7];
         char DISCOUNTPCT3[5];
         char DISCOUNTPRICE3[11];
         char PAYTERM3[7];
         char DISCOUNTPCT4[5];
         char DISCOUNTPRICE4[11];
         char PAYTERM4[7];
         char DISCOUNTPCT5[5];
         char DISCOUNTPRICE5[11];
         char PAYTERM5[7];
         char DISCOUNTPCT6[5];
         char DISCOUNTPRICE6[11];
         char PAYTERM6[7];
         char CASCADE[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUCOSSERBIA *********************************/

 struct C_CUCOSSERBIA {
         short BRANCHNO;
         long CUSTOMERNO;
         long ARTICLENO;
         double PREISEKAPO;
         long BASEQTY;
         double DISCOUNTVALUEPCT;
         double DISCOUNTPRICE;
         double DISCOUNTPCT1;
         double DISCOUNTPRICE1;
         short PAYTERM1;
         double DISCOUNTPCT2;
         double DISCOUNTPRICE2;
         short PAYTERM2;
         double DISCOUNTPCT3;
         double DISCOUNTPRICE3;
         short PAYTERM3;
         double DISCOUNTPCT4;
         double DISCOUNTPRICE4;
         short PAYTERM4;
         double DISCOUNTPCT5;
         double DISCOUNTPRICE5;
         short PAYTERM5;
         double DISCOUNTPCT6;
         double DISCOUNTPRICE6;
         short PAYTERM6;
         short CASCADE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUCOSSERBIA *******************************/

 struct I_CUCOSSERBIA {
         short BRANCHNO;
         short CUSTOMERNO;
         short ARTICLENO;
         short PREISEKAPO;
         short BASEQTY;
         short DISCOUNTVALUEPCT;
         short DISCOUNTPRICE;
         short DISCOUNTPCT1;
         short DISCOUNTPRICE1;
         short PAYTERM1;
         short DISCOUNTPCT2;
         short DISCOUNTPRICE2;
         short PAYTERM2;
         short DISCOUNTPCT3;
         short DISCOUNTPRICE3;
         short PAYTERM3;
         short DISCOUNTPCT4;
         short DISCOUNTPRICE4;
         short PAYTERM4;
         short DISCOUNTPCT5;
         short DISCOUNTPRICE5;
         short PAYTERM5;
         short DISCOUNTPCT6;
         short DISCOUNTPRICE6;
         short PAYTERM6;
         short CASCADE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUCOSSERBIA *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc CUCOSSERBIA_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CUCOSSERBIA_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of CUCOSSERBIA ***********************************/

 #define CUCOSSERBIA_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long ARTICLENO; \
         double PREISEKAPO; \
         long BASEQTY; \
         double DISCOUNTVALUEPCT; \
         double DISCOUNTPRICE; \
         double DISCOUNTPCT1; \
         double DISCOUNTPRICE1; \
         short PAYTERM1; \
         double DISCOUNTPCT2; \
         double DISCOUNTPRICE2; \
         short PAYTERM2; \
         double DISCOUNTPCT3; \
         double DISCOUNTPRICE3; \
         short PAYTERM3; \
         double DISCOUNTPCT4; \
         double DISCOUNTPRICE4; \
         short PAYTERM4; \
         double DISCOUNTPCT5; \
         double DISCOUNTPRICE5; \
         short PAYTERM5; \
         double DISCOUNTPCT6; \
         double DISCOUNTPRICE6; \
         short PAYTERM6; \
         short CASCADE; \



/* Copy-Function Struct to single Data CUCOSSERBIA ****************************/

 #define CUCOSSERBIA_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         ARTICLENO=_x_->ARTICLENO;\
         PREISEKAPO=_x_->PREISEKAPO;\
         BASEQTY=_x_->BASEQTY;\
         DISCOUNTVALUEPCT=_x_->DISCOUNTVALUEPCT;\
         DISCOUNTPRICE=_x_->DISCOUNTPRICE;\
         DISCOUNTPCT1=_x_->DISCOUNTPCT1;\
         DISCOUNTPRICE1=_x_->DISCOUNTPRICE1;\
         PAYTERM1=_x_->PAYTERM1;\
         DISCOUNTPCT2=_x_->DISCOUNTPCT2;\
         DISCOUNTPRICE2=_x_->DISCOUNTPRICE2;\
         PAYTERM2=_x_->PAYTERM2;\
         DISCOUNTPCT3=_x_->DISCOUNTPCT3;\
         DISCOUNTPRICE3=_x_->DISCOUNTPRICE3;\
         PAYTERM3=_x_->PAYTERM3;\
         DISCOUNTPCT4=_x_->DISCOUNTPCT4;\
         DISCOUNTPRICE4=_x_->DISCOUNTPRICE4;\
         PAYTERM4=_x_->PAYTERM4;\
         DISCOUNTPCT5=_x_->DISCOUNTPCT5;\
         DISCOUNTPRICE5=_x_->DISCOUNTPRICE5;\
         PAYTERM5=_x_->PAYTERM5;\
         DISCOUNTPCT6=_x_->DISCOUNTPCT6;\
         DISCOUNTPRICE6=_x_->DISCOUNTPRICE6;\
         PAYTERM6=_x_->PAYTERM6;\
         CASCADE=_x_->CASCADE;\

 #define CUCOSSERBIA_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->PREISEKAPO=PREISEKAPO;\
          _x_->BASEQTY=BASEQTY;\
          _x_->DISCOUNTVALUEPCT=DISCOUNTVALUEPCT;\
          _x_->DISCOUNTPRICE=DISCOUNTPRICE;\
          _x_->DISCOUNTPCT1=DISCOUNTPCT1;\
          _x_->DISCOUNTPRICE1=DISCOUNTPRICE1;\
          _x_->PAYTERM1=PAYTERM1;\
          _x_->DISCOUNTPCT2=DISCOUNTPCT2;\
          _x_->DISCOUNTPRICE2=DISCOUNTPRICE2;\
          _x_->PAYTERM2=PAYTERM2;\
          _x_->DISCOUNTPCT3=DISCOUNTPCT3;\
          _x_->DISCOUNTPRICE3=DISCOUNTPRICE3;\
          _x_->PAYTERM3=PAYTERM3;\
          _x_->DISCOUNTPCT4=DISCOUNTPCT4;\
          _x_->DISCOUNTPRICE4=DISCOUNTPRICE4;\
          _x_->PAYTERM4=PAYTERM4;\
          _x_->DISCOUNTPCT5=DISCOUNTPCT5;\
          _x_->DISCOUNTPRICE5=DISCOUNTPRICE5;\
          _x_->PAYTERM5=PAYTERM5;\
          _x_->DISCOUNTPCT6=DISCOUNTPCT6;\
          _x_->DISCOUNTPRICE6=DISCOUNTPRICE6;\
          _x_->PAYTERM6=PAYTERM6;\
          _x_->CASCADE=CASCADE;\



/* FunctionNumber-Define of cucosserbia ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of cucosserbia ***********************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS
#include<vector>
using namespace std;

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual
{
	public:
		virtual    ~ppDadeVirtual() {};
		virtual int SelList      (int FetchRel = 1, int pos = 0) = 0;
		virtual int SelListHist  (int FetchRel = 1, int pos = 0) = 0;
		virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
		virtual int Load         (int pos = 0                  ) = 0;
 		virtual int Delete       (int pos = 0                  ) = 0;
		virtual int Save         (int pos = 0                  ) = 0;
};
#endif

class CCUCOSSERBIA : public ppDadeVirtual
{
	//data members
	public:
		cucosserbiaS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<cucosserbiaS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<cucosserbiaS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<cucosserbiaS>; Strip(s); cucosserbiaS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<cucosserbiaS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<cucosserbiaS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<cucosserbiaS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetBranchno() const	{ return s.BRANCHNO; }
		long		GetCustomerno() const	{ return s.CUSTOMERNO; }
		long		GetArticleno() const	{ return s.ARTICLENO; }
		double		GetPreisekapo() const	{ return s.PREISEKAPO; }
		long		GetBaseqty() const	{ return s.BASEQTY; }
		double		GetDiscountvaluepct() const	{ return s.DISCOUNTVALUEPCT; }
		double		GetDiscountprice() const	{ return s.DISCOUNTPRICE; }
		double		GetDiscountpct1() const	{ return s.DISCOUNTPCT1; }
		double		GetDiscountprice1() const	{ return s.DISCOUNTPRICE1; }
		short		GetPayterm1() const	{ return s.PAYTERM1; }
		double		GetDiscountpct2() const	{ return s.DISCOUNTPCT2; }
		double		GetDiscountprice2() const	{ return s.DISCOUNTPRICE2; }
		short		GetPayterm2() const	{ return s.PAYTERM2; }
		double		GetDiscountpct3() const	{ return s.DISCOUNTPCT3; }
		double		GetDiscountprice3() const	{ return s.DISCOUNTPRICE3; }
		short		GetPayterm3() const	{ return s.PAYTERM3; }
		double		GetDiscountpct4() const	{ return s.DISCOUNTPCT4; }
		double		GetDiscountprice4() const	{ return s.DISCOUNTPRICE4; }
		short		GetPayterm4() const	{ return s.PAYTERM4; }
		double		GetDiscountpct5() const	{ return s.DISCOUNTPCT5; }
		double		GetDiscountprice5() const	{ return s.DISCOUNTPRICE5; }
		short		GetPayterm5() const	{ return s.PAYTERM5; }
		double		GetDiscountpct6() const	{ return s.DISCOUNTPCT6; }
		double		GetDiscountprice6() const	{ return s.DISCOUNTPRICE6; }
		short		GetPayterm6() const	{ return s.PAYTERM6; }
		short		GetCascade() const	{ return s.CASCADE; }
		const cucosserbiaS& GetStruct() const { return s; }
		void 		SetBranchno(short t) { s.BRANCHNO = t; }
		void 		SetCustomerno(long t) { s.CUSTOMERNO = t; }
		void 		SetArticleno(long t) { s.ARTICLENO = t; }
		void 		SetPreisekapo(double t) { s.PREISEKAPO = t; }
		void 		SetBaseqty(long t) { s.BASEQTY = t; }
		void 		SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
		void 		SetDiscountprice(double t) { s.DISCOUNTPRICE = t; }
		void 		SetDiscountpct1(double t) { s.DISCOUNTPCT1 = t; }
		void 		SetDiscountprice1(double t) { s.DISCOUNTPRICE1 = t; }
		void 		SetPayterm1(short t) { s.PAYTERM1 = t; }
		void 		SetDiscountpct2(double t) { s.DISCOUNTPCT2 = t; }
		void 		SetDiscountprice2(double t) { s.DISCOUNTPRICE2 = t; }
		void 		SetPayterm2(short t) { s.PAYTERM2 = t; }
		void 		SetDiscountpct3(double t) { s.DISCOUNTPCT3 = t; }
		void 		SetDiscountprice3(double t) { s.DISCOUNTPRICE3 = t; }
		void 		SetPayterm3(short t) { s.PAYTERM3 = t; }
		void 		SetDiscountpct4(double t) { s.DISCOUNTPCT4 = t; }
		void 		SetDiscountprice4(double t) { s.DISCOUNTPRICE4 = t; }
		void 		SetPayterm4(short t) { s.PAYTERM4 = t; }
		void 		SetDiscountpct5(double t) { s.DISCOUNTPCT5 = t; }
		void 		SetDiscountprice5(double t) { s.DISCOUNTPRICE5 = t; }
		void 		SetPayterm5(short t) { s.PAYTERM5 = t; }
		void 		SetDiscountpct6(double t) { s.DISCOUNTPCT6 = t; }
		void 		SetDiscountprice6(double t) { s.DISCOUNTPRICE6 = t; }
		void 		SetPayterm6(short t) { s.PAYTERM6 = t; }
		void 		SetCascade(short t) { s.CASCADE = t; }
		void 		SetStruct(const cucosserbiaS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CCUCOSSERBIA()  //constructor
		{
			::buf_default((void *)&s, CUCOSSERBIA_BES, CUCOSSERBIA_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CCUCOSSERBIA()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, CUCOSSERBIA_BES, CUCOSSERBIA_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUCOSSERBIA_BES, CUCOSSERBIA_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, CUCOSSERBIA_BES, CUCOSSERBIA_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_CUCOSSERBIA& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, CUCOSSERBIA_BES, CUCOSSERBIA_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of CUCOSSERBIA ******************************************/

 #define CUCOSSERBIA_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ARTICLENO integer default 0 not null,\
         PREISEKAPO decimal(9,2) default 0 not null,\
         BASEQTY integer default 0 not null,\
         DISCOUNTVALUEPCT decimal(5,2) default 0 not null,\
         DISCOUNTPRICE decimal(11,2) default 0 not null,\
         DISCOUNTPCT1 decimal(5,2) default 0 not null,\
         DISCOUNTPRICE1 decimal(11,2) default 0 not null,\
         PAYTERM1 smallint default 0 not null,\
         DISCOUNTPCT2 decimal(5,2) default 0 not null,\
         DISCOUNTPRICE2 decimal(11,2) default 0 not null,\
         PAYTERM2 smallint default 0 not null,\
         DISCOUNTPCT3 decimal(5,2) default 0 not null,\
         DISCOUNTPRICE3 decimal(11,2) default 0 not null,\
         PAYTERM3 smallint default 0 not null,\
         DISCOUNTPCT4 decimal(5,2) default 0 not null,\
         DISCOUNTPRICE4 decimal(11,2) default 0 not null,\
         PAYTERM4 smallint default 0 not null,\
         DISCOUNTPCT5 decimal(5,2) default 0 not null,\
         DISCOUNTPRICE5 decimal(11,2) default 0 not null,\
         PAYTERM5 smallint default 0 not null,\
         DISCOUNTPCT6 decimal(5,2) default 0 not null,\
         DISCOUNTPRICE6 decimal(11,2) default 0 not null,\
         PAYTERM6 smallint default 0 not null,\
         CASCADE smallint default 0 not null) in ksc extent size 94116 next size 9412 lock mode row;



/* CreateIndexStatement of CUCOSSERBIA ****************************************/

 #define CUCOSSERBIA_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_cucosserbia_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUCOSSERBIA ****************************************/

 #define CUCOSSERBIA_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_cucosserbia_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
