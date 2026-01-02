#ifndef __PP_TKUNDGRP_H_
#define __PP_TKUNDGRP_H_

/******************************************************************************/
/* c:\phosix\tkundgrp *********************************************************/
/******************************************************************************/

/* Length-Define of KUNDENGRUPPE **********************************************/

  #define L_KUNDENGRUPPE_KDGRUPPE 2
  #define L_KUNDENGRUPPE_BEZEICHNUNG 30
  #define L_KUNDENGRUPPE_SARTGIFTKLASSE1 1
  #define L_KUNDENGRUPPE_SARTGIFTKLASSE2 1
  #define L_KUNDENGRUPPE_SARTGIFTKLASSE3 1
  #define L_KUNDENGRUPPE_SARTREZEPTPFL 1
  #define L_KUNDENGRUPPE_SARTAPOTHEKENPFL 1
  #define L_KUNDENGRUPPE_SARTTAXPFL 1
  #define L_KUNDENGRUPPE_SARTOPIAT 1
  #define L_KUNDENGRUPPE_SARTTIERARZNEI 1
  #define L_KUNDENGRUPPE_SARTVERTRIEBSGEB 1
  #define L_KUNDENGRUPPE_SARTLIEFERSPERRE 1
  #define L_KUNDENGRUPPE_SARTABSCHLAG 1
  #define L_KUNDENGRUPPE_SARTPREISERMAESS 1
  #define L_KUNDENGRUPPE_SARTVERTRIEBSBIND1 1
  #define L_KUNDENGRUPPE_SARTVERTRIEBSBIND2 1
  #define L_KUNDENGRUPPE_SARTVERTRIEBSBIND3 1
  #define L_KUNDENGRUPPE_SARTVERTRIEBSBIND4 1
  #define L_KUNDENGRUPPE_KDGRUPPESPERRKZ 1
  #define L_KUNDENGRUPPE_KDGRUPPEFREIKZ 1

/* Length/Count-Define of KUNDENGRUPPE ****************************************/

  #define LS_KUNDENGRUPPE_KDGRUPPE 2 + 1
  #define LS_KUNDENGRUPPE_BEZEICHNUNG 30 + 1
  #define LS_KUNDENGRUPPE_SARTGIFTKLASSE1 1 + 1
  #define LS_KUNDENGRUPPE_SARTGIFTKLASSE2 1 + 1
  #define LS_KUNDENGRUPPE_SARTGIFTKLASSE3 1 + 1
  #define LS_KUNDENGRUPPE_SARTREZEPTPFL 1 + 1
  #define LS_KUNDENGRUPPE_SARTAPOTHEKENPFL 1 + 1
  #define LS_KUNDENGRUPPE_SARTTAXPFL 1 + 1
  #define LS_KUNDENGRUPPE_SARTOPIAT 1 + 1
  #define LS_KUNDENGRUPPE_SARTTIERARZNEI 1 + 1
  #define LS_KUNDENGRUPPE_SARTVERTRIEBSGEB 1 + 1
  #define LS_KUNDENGRUPPE_SARTLIEFERSPERRE 1 + 1
  #define LS_KUNDENGRUPPE_SARTABSCHLAG 1 + 1
  #define LS_KUNDENGRUPPE_SARTPREISERMAESS 1 + 1
  #define LS_KUNDENGRUPPE_SARTVERTRIEBSBIND1 1 + 1
  #define LS_KUNDENGRUPPE_SARTVERTRIEBSBIND2 1 + 1
  #define LS_KUNDENGRUPPE_SARTVERTRIEBSBIND3 1 + 1
  #define LS_KUNDENGRUPPE_SARTVERTRIEBSBIND4 1 + 1
  #define LS_KUNDENGRUPPE_KDGRUPPESPERRKZ 1 + 1
  #define LS_KUNDENGRUPPE_KDGRUPPEFREIKZ 1 + 1

  #define KUNDENGRUPPEKDGRUPPE 0
  #define KUNDENGRUPPEBEZEICHNUNG 1
  #define KUNDENGRUPPESARTGIFTKLASSE1 2
  #define KUNDENGRUPPESARTGIFTKLASSE2 3
  #define KUNDENGRUPPESARTGIFTKLASSE3 4
  #define KUNDENGRUPPESARTREZEPTPFL 5
  #define KUNDENGRUPPESARTAPOTHEKENPFL 6
  #define KUNDENGRUPPESARTTAXPFL 7
  #define KUNDENGRUPPESARTOPIAT 8
  #define KUNDENGRUPPESARTTIERARZNEI 9
  #define KUNDENGRUPPESARTVERTRIEBSGEB 10
  #define KUNDENGRUPPESARTLIEFERSPERRE 11
  #define KUNDENGRUPPESARTABSCHLAG 12
  #define KUNDENGRUPPESARTPREISERMAESS 13
  #define KUNDENGRUPPESARTVERTRIEBSBIND1 14
  #define KUNDENGRUPPESARTVERTRIEBSBIND2 15
  #define KUNDENGRUPPESARTVERTRIEBSBIND3 16
  #define KUNDENGRUPPESARTVERTRIEBSBIND4 17
  #define KUNDENGRUPPEKDGRUPPESPERRKZ 18
  #define KUNDENGRUPPEKDGRUPPEFREIKZ 19

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KUNDENGRUPPE_H
 #define KUNDENGRUPPE_ANZ ( sizeof(KUNDENGRUPPE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KUNDENGRUPPE **************************************************/

 #define KUNDENGRUPPE_LISTE \
         KUNDENGRUPPE.KDGRUPPE,\
         KUNDENGRUPPE.BEZEICHNUNG,\
         KUNDENGRUPPE.SARTGIFTKLASSE1,\
         KUNDENGRUPPE.SARTGIFTKLASSE2,\
         KUNDENGRUPPE.SARTGIFTKLASSE3,\
         KUNDENGRUPPE.SARTREZEPTPFL,\
         KUNDENGRUPPE.SARTAPOTHEKENPFL,\
         KUNDENGRUPPE.SARTTAXPFL,\
         KUNDENGRUPPE.SARTOPIAT,\
         KUNDENGRUPPE.SARTTIERARZNEI,\
         KUNDENGRUPPE.SARTVERTRIEBSGEB,\
         KUNDENGRUPPE.SARTLIEFERSPERRE,\
         KUNDENGRUPPE.SARTABSCHLAG,\
         KUNDENGRUPPE.SARTPREISERMAESS,\
         KUNDENGRUPPE.SARTVERTRIEBSBIND1,\
         KUNDENGRUPPE.SARTVERTRIEBSBIND2,\
         KUNDENGRUPPE.SARTVERTRIEBSBIND3,\
         KUNDENGRUPPE.SARTVERTRIEBSBIND4,\
         KUNDENGRUPPE.KDGRUPPESPERRKZ,\
         KUNDENGRUPPE.KDGRUPPEFREIKZ

 #define KUNDENGRUPPE_LISTE_390 \
         KDGRUPPE,\
         BEZEICHNUNG,\
         SARTGIFTKLASSE1,\
         SARTGIFTKLASSE2,\
         SARTGIFTKLASSE3,\
         SARTREZEPTPFL,\
         SARTAPOTHEKENPFL,\
         SARTTAXPFL,\
         SARTOPIAT,\
         SARTTIERARZNEI,\
         SARTVERTRIEBSGEB,\
         SARTLIEFERSPERRE,\
         SARTABSCHLAG,\
         SARTPREISERMAESS,\
         SARTVERTRIEBSBIND1,\
         SARTVERTRIEBSBIND2,\
         SARTVERTRIEBSBIND3,\
         SARTVERTRIEBSBIND4,\
         KDGRUPPESPERRKZ,\
         KDGRUPPEFREIKZ

 #define KUNDENGRUPPE_PLISTE \
         "KUNDENGRUPPE.KDGRUPPE,"\
         "KUNDENGRUPPE.BEZEICHNUNG,"\
         "KUNDENGRUPPE.SARTGIFTKLASSE1,"\
         "KUNDENGRUPPE.SARTGIFTKLASSE2,"\
         "KUNDENGRUPPE.SARTGIFTKLASSE3,"\
         "KUNDENGRUPPE.SARTREZEPTPFL,"\
         "KUNDENGRUPPE.SARTAPOTHEKENPFL,"\
         "KUNDENGRUPPE.SARTTAXPFL,"\
         "KUNDENGRUPPE.SARTOPIAT,"\
         "KUNDENGRUPPE.SARTTIERARZNEI,"\
         "KUNDENGRUPPE.SARTVERTRIEBSGEB,"\
         "KUNDENGRUPPE.SARTLIEFERSPERRE,"\
         "KUNDENGRUPPE.SARTABSCHLAG,"\
         "KUNDENGRUPPE.SARTPREISERMAESS,"\
         "KUNDENGRUPPE.SARTVERTRIEBSBIND1,"\
         "KUNDENGRUPPE.SARTVERTRIEBSBIND2,"\
         "KUNDENGRUPPE.SARTVERTRIEBSBIND3,"\
         "KUNDENGRUPPE.SARTVERTRIEBSBIND4,"\
         "KUNDENGRUPPE.KDGRUPPESPERRKZ,"\
         "KUNDENGRUPPE.KDGRUPPEFREIKZ"

 #define KUNDENGRUPPE_PELISTE \
         "KDGRUPPE,"\
         "BEZEICHNUNG,"\
         "SARTGIFTKLASSE1,"\
         "SARTGIFTKLASSE2,"\
         "SARTGIFTKLASSE3,"\
         "SARTREZEPTPFL,"\
         "SARTAPOTHEKENPFL,"\
         "SARTTAXPFL,"\
         "SARTOPIAT,"\
         "SARTTIERARZNEI,"\
         "SARTVERTRIEBSGEB,"\
         "SARTLIEFERSPERRE,"\
         "SARTABSCHLAG,"\
         "SARTPREISERMAESS,"\
         "SARTVERTRIEBSBIND1,"\
         "SARTVERTRIEBSBIND2,"\
         "SARTVERTRIEBSBIND3,"\
         "SARTVERTRIEBSBIND4,"\
         "KDGRUPPESPERRKZ,"\
         "KDGRUPPEFREIKZ"

 #define KUNDENGRUPPE_UPDLISTE \
         "KDGRUPPE=?,"\
         "BEZEICHNUNG=?,"\
         "SARTGIFTKLASSE1=?,"\
         "SARTGIFTKLASSE2=?,"\
         "SARTGIFTKLASSE3=?,"\
         "SARTREZEPTPFL=?,"\
         "SARTAPOTHEKENPFL=?,"\
         "SARTTAXPFL=?,"\
         "SARTOPIAT=?,"\
         "SARTTIERARZNEI=?,"\
         "SARTVERTRIEBSGEB=?,"\
         "SARTLIEFERSPERRE=?,"\
         "SARTABSCHLAG=?,"\
         "SARTPREISERMAESS=?,"\
         "SARTVERTRIEBSBIND1=?,"\
         "SARTVERTRIEBSBIND2=?,"\
         "SARTVERTRIEBSBIND3=?,"\
         "SARTVERTRIEBSBIND4=?,"\
         "KDGRUPPESPERRKZ=?,"\
         "KDGRUPPEFREIKZ=?"

/* SqlMacros-Define of KUNDENGRUPPE *******************************************/

 #define KUNDENGRUPPE_ZEIGER(x) \
         :x->KDGRUPPE,\
         :x->BEZEICHNUNG,\
         :x->SARTGIFTKLASSE1,\
         :x->SARTGIFTKLASSE2,\
         :x->SARTGIFTKLASSE3,\
         :x->SARTREZEPTPFL,\
         :x->SARTAPOTHEKENPFL,\
         :x->SARTTAXPFL,\
         :x->SARTOPIAT,\
         :x->SARTTIERARZNEI,\
         :x->SARTVERTRIEBSGEB,\
         :x->SARTLIEFERSPERRE,\
         :x->SARTABSCHLAG,\
         :x->SARTPREISERMAESS,\
         :x->SARTVERTRIEBSBIND1,\
         :x->SARTVERTRIEBSBIND2,\
         :x->SARTVERTRIEBSBIND3,\
         :x->SARTVERTRIEBSBIND4,\
         :x->KDGRUPPESPERRKZ,\
         :x->KDGRUPPEFREIKZ

 #define KUNDENGRUPPE_UPDATE(x) \
         KUNDENGRUPPE.KDGRUPPE=:x->KDGRUPPE,\
         KUNDENGRUPPE.BEZEICHNUNG=:x->BEZEICHNUNG,\
         KUNDENGRUPPE.SARTGIFTKLASSE1=:x->SARTGIFTKLASSE1,\
         KUNDENGRUPPE.SARTGIFTKLASSE2=:x->SARTGIFTKLASSE2,\
         KUNDENGRUPPE.SARTGIFTKLASSE3=:x->SARTGIFTKLASSE3,\
         KUNDENGRUPPE.SARTREZEPTPFL=:x->SARTREZEPTPFL,\
         KUNDENGRUPPE.SARTAPOTHEKENPFL=:x->SARTAPOTHEKENPFL,\
         KUNDENGRUPPE.SARTTAXPFL=:x->SARTTAXPFL,\
         KUNDENGRUPPE.SARTOPIAT=:x->SARTOPIAT,\
         KUNDENGRUPPE.SARTTIERARZNEI=:x->SARTTIERARZNEI,\
         KUNDENGRUPPE.SARTVERTRIEBSGEB=:x->SARTVERTRIEBSGEB,\
         KUNDENGRUPPE.SARTLIEFERSPERRE=:x->SARTLIEFERSPERRE,\
         KUNDENGRUPPE.SARTABSCHLAG=:x->SARTABSCHLAG,\
         KUNDENGRUPPE.SARTPREISERMAESS=:x->SARTPREISERMAESS,\
         KUNDENGRUPPE.SARTVERTRIEBSBIND1=:x->SARTVERTRIEBSBIND1,\
         KUNDENGRUPPE.SARTVERTRIEBSBIND2=:x->SARTVERTRIEBSBIND2,\
         KUNDENGRUPPE.SARTVERTRIEBSBIND3=:x->SARTVERTRIEBSBIND3,\
         KUNDENGRUPPE.SARTVERTRIEBSBIND4=:x->SARTVERTRIEBSBIND4,\
         KUNDENGRUPPE.KDGRUPPESPERRKZ=:x->KDGRUPPESPERRKZ,\
         KUNDENGRUPPE.KDGRUPPEFREIKZ=:x->KDGRUPPEFREIKZ

/* SqlMacros390-Define of KUNDENGRUPPE ****************************************/

 #define KUNDENGRUPPE_ZEIGER_390 \
         :KDGRUPPE,\
         :BEZEICHNUNG,\
         :SARTGIFTKLASSE1,\
         :SARTGIFTKLASSE2,\
         :SARTGIFTKLASSE3,\
         :SARTREZEPTPFL,\
         :SARTAPOTHEKENPFL,\
         :SARTTAXPFL,\
         :SARTOPIAT,\
         :SARTTIERARZNEI,\
         :SARTVERTRIEBSGEB,\
         :SARTLIEFERSPERRE,\
         :SARTABSCHLAG,\
         :SARTPREISERMAESS,\
         :SARTVERTRIEBSBIND1,\
         :SARTVERTRIEBSBIND2,\
         :SARTVERTRIEBSBIND3,\
         :SARTVERTRIEBSBIND4,\
         :KDGRUPPESPERRKZ,\
         :KDGRUPPEFREIKZ

 #define KUNDENGRUPPE_UPDATE_390 \
         KDGRUPPE=:KDGRUPPE,\
         BEZEICHNUNG=:BEZEICHNUNG,\
         SARTGIFTKLASSE1=:SARTGIFTKLASSE1,\
         SARTGIFTKLASSE2=:SARTGIFTKLASSE2,\
         SARTGIFTKLASSE3=:SARTGIFTKLASSE3,\
         SARTREZEPTPFL=:SARTREZEPTPFL,\
         SARTAPOTHEKENPFL=:SARTAPOTHEKENPFL,\
         SARTTAXPFL=:SARTTAXPFL,\
         SARTOPIAT=:SARTOPIAT,\
         SARTTIERARZNEI=:SARTTIERARZNEI,\
         SARTVERTRIEBSGEB=:SARTVERTRIEBSGEB,\
         SARTLIEFERSPERRE=:SARTLIEFERSPERRE,\
         SARTABSCHLAG=:SARTABSCHLAG,\
         SARTPREISERMAESS=:SARTPREISERMAESS,\
         SARTVERTRIEBSBIND1=:SARTVERTRIEBSBIND1,\
         SARTVERTRIEBSBIND2=:SARTVERTRIEBSBIND2,\
         SARTVERTRIEBSBIND3=:SARTVERTRIEBSBIND3,\
         SARTVERTRIEBSBIND4=:SARTVERTRIEBSBIND4,\
         KDGRUPPESPERRKZ=:KDGRUPPESPERRKZ,\
         KDGRUPPEFREIKZ=:KDGRUPPEFREIKZ

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KUNDENGRUPPE *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_KUNDENGRUPPE {
         char KDGRUPPE[3];
         char BEZEICHNUNG[31];
         char SARTGIFTKLASSE1[2];
         char SARTGIFTKLASSE2[2];
         char SARTGIFTKLASSE3[2];
         char SARTREZEPTPFL[2];
         char SARTAPOTHEKENPFL[2];
         char SARTTAXPFL[2];
         char SARTOPIAT[2];
         char SARTTIERARZNEI[2];
         char SARTVERTRIEBSGEB[2];
         char SARTLIEFERSPERRE[2];
         char SARTABSCHLAG[2];
         char SARTPREISERMAESS[2];
         char SARTVERTRIEBSBIND1[2];
         char SARTVERTRIEBSBIND2[2];
         char SARTVERTRIEBSBIND3[2];
         char SARTVERTRIEBSBIND4[2];
         char KDGRUPPESPERRKZ[2];
         char KDGRUPPEFREIKZ[2];
        } kundengruppeS;
 #else /*TRANSCLASS*/
 typedef struct N_KUNDENGRUPPE {
         char KDGRUPPE[3];
         char BEZEICHNUNG[31];
         char SARTGIFTKLASSE1[2];
         char SARTGIFTKLASSE2[2];
         char SARTGIFTKLASSE3[2];
         char SARTREZEPTPFL[2];
         char SARTAPOTHEKENPFL[2];
         char SARTTAXPFL[2];
         char SARTOPIAT[2];
         char SARTTIERARZNEI[2];
         char SARTVERTRIEBSGEB[2];
         char SARTLIEFERSPERRE[2];
         char SARTABSCHLAG[2];
         char SARTPREISERMAESS[2];
         char SARTVERTRIEBSBIND1[2];
         char SARTVERTRIEBSBIND2[2];
         char SARTVERTRIEBSBIND3[2];
         char SARTVERTRIEBSBIND4[2];
         char KDGRUPPESPERRKZ[2];
         char KDGRUPPEFREIKZ[2];

			bool operator==(const N_KUNDENGRUPPE& right) const {
			return(
				!strcmp(KDGRUPPE, right.KDGRUPPE) &&
				!strcmp(BEZEICHNUNG, right.BEZEICHNUNG) &&
				!strcmp(SARTGIFTKLASSE1, right.SARTGIFTKLASSE1) &&
				!strcmp(SARTGIFTKLASSE2, right.SARTGIFTKLASSE2) &&
				!strcmp(SARTGIFTKLASSE3, right.SARTGIFTKLASSE3) &&
				!strcmp(SARTREZEPTPFL, right.SARTREZEPTPFL) &&
				!strcmp(SARTAPOTHEKENPFL, right.SARTAPOTHEKENPFL) &&
				!strcmp(SARTTAXPFL, right.SARTTAXPFL) &&
				!strcmp(SARTOPIAT, right.SARTOPIAT) &&
				!strcmp(SARTTIERARZNEI, right.SARTTIERARZNEI) &&
				!strcmp(SARTVERTRIEBSGEB, right.SARTVERTRIEBSGEB) &&
				!strcmp(SARTLIEFERSPERRE, right.SARTLIEFERSPERRE) &&
				!strcmp(SARTABSCHLAG, right.SARTABSCHLAG) &&
				!strcmp(SARTPREISERMAESS, right.SARTPREISERMAESS) &&
				!strcmp(SARTVERTRIEBSBIND1, right.SARTVERTRIEBSBIND1) &&
				!strcmp(SARTVERTRIEBSBIND2, right.SARTVERTRIEBSBIND2) &&
				!strcmp(SARTVERTRIEBSBIND3, right.SARTVERTRIEBSBIND3) &&
				!strcmp(SARTVERTRIEBSBIND4, right.SARTVERTRIEBSBIND4) &&
				!strcmp(KDGRUPPESPERRKZ, right.KDGRUPPESPERRKZ) &&
				!strcmp(KDGRUPPEFREIKZ, right.KDGRUPPEFREIKZ)
				);
			}
			void clear() { memset((char*)this,0,sizeof(*this)); }
         } kundengruppeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KUNDENGRUPPE **************************************/

 struct S_KUNDENGRUPPE {
         char KDGRUPPE[2 + 1];
         char BEZEICHNUNG[30 + 1];
         char SARTGIFTKLASSE1[1 + 1];
         char SARTGIFTKLASSE2[1 + 1];
         char SARTGIFTKLASSE3[1 + 1];
         char SARTREZEPTPFL[1 + 1];
         char SARTAPOTHEKENPFL[1 + 1];
         char SARTTAXPFL[1 + 1];
         char SARTOPIAT[1 + 1];
         char SARTTIERARZNEI[1 + 1];
         char SARTVERTRIEBSGEB[1 + 1];
         char SARTLIEFERSPERRE[1 + 1];
         char SARTABSCHLAG[1 + 1];
         char SARTPREISERMAESS[1 + 1];
         char SARTVERTRIEBSBIND1[1 + 1];
         char SARTVERTRIEBSBIND2[1 + 1];
         char SARTVERTRIEBSBIND3[1 + 1];
         char SARTVERTRIEBSBIND4[1 + 1];
         char KDGRUPPESPERRKZ[1 + 1];
         char KDGRUPPEFREIKZ[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KUNDENGRUPPE *********************/

 struct O_KUNDENGRUPPE {
         char KDGRUPPE[2];
         char BEZEICHNUNG[30];
         char SARTGIFTKLASSE1[1];
         char SARTGIFTKLASSE2[1];
         char SARTGIFTKLASSE3[1];
         char SARTREZEPTPFL[1];
         char SARTAPOTHEKENPFL[1];
         char SARTTAXPFL[1];
         char SARTOPIAT[1];
         char SARTTIERARZNEI[1];
         char SARTVERTRIEBSGEB[1];
         char SARTLIEFERSPERRE[1];
         char SARTABSCHLAG[1];
         char SARTPREISERMAESS[1];
         char SARTVERTRIEBSBIND1[1];
         char SARTVERTRIEBSBIND2[1];
         char SARTVERTRIEBSBIND3[1];
         char SARTVERTRIEBSBIND4[1];
         char KDGRUPPESPERRKZ[1];
         char KDGRUPPEFREIKZ[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of KUNDENGRUPPE *********************************/

 struct C_KUNDENGRUPPE {
         char KDGRUPPE[3];
         char BEZEICHNUNG[31];
         char SARTGIFTKLASSE1;
         char SARTGIFTKLASSE2;
         char SARTGIFTKLASSE3;
         char SARTREZEPTPFL;
         char SARTAPOTHEKENPFL;
         char SARTTAXPFL;
         char SARTOPIAT;
         char SARTTIERARZNEI;
         char SARTVERTRIEBSGEB;
         char SARTLIEFERSPERRE;
         char SARTABSCHLAG;
         char SARTPREISERMAESS;
         char SARTVERTRIEBSBIND1;
         char SARTVERTRIEBSBIND2;
         char SARTVERTRIEBSBIND3;
         char SARTVERTRIEBSBIND4;
         char KDGRUPPESPERRKZ;
         char KDGRUPPEFREIKZ;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of KUNDENGRUPPE *******************************/

 struct I_KUNDENGRUPPE {
         short KDGRUPPE;
         short BEZEICHNUNG;
         short SARTGIFTKLASSE1;
         short SARTGIFTKLASSE2;
         short SARTGIFTKLASSE3;
         short SARTREZEPTPFL;
         short SARTAPOTHEKENPFL;
         short SARTTAXPFL;
         short SARTOPIAT;
         short SARTTIERARZNEI;
         short SARTVERTRIEBSGEB;
         short SARTLIEFERSPERRE;
         short SARTABSCHLAG;
         short SARTPREISERMAESS;
         short SARTVERTRIEBSBIND1;
         short SARTVERTRIEBSBIND2;
         short SARTVERTRIEBSBIND3;
         short SARTVERTRIEBSBIND4;
         short KDGRUPPESPERRKZ;
         short KDGRUPPEFREIKZ;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KUNDENGRUPPE ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc KUNDENGRUPPE_BES [] =
 {
   { TYP_C, 2, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KUNDENGRUPPE_BES [] =
 {
   { TYP_C, 2, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of KUNDENGRUPPE **********************************/

 #define KUNDENGRUPPE_S390 \
         char KDGRUPPE[3]; \
         char BEZEICHNUNG[31]; \
         char SARTGIFTKLASSE1; \
         char SARTGIFTKLASSE2; \
         char SARTGIFTKLASSE3; \
         char SARTREZEPTPFL; \
         char SARTAPOTHEKENPFL; \
         char SARTTAXPFL; \
         char SARTOPIAT; \
         char SARTTIERARZNEI; \
         char SARTVERTRIEBSGEB; \
         char SARTLIEFERSPERRE; \
         char SARTABSCHLAG; \
         char SARTPREISERMAESS; \
         char SARTVERTRIEBSBIND1; \
         char SARTVERTRIEBSBIND2; \
         char SARTVERTRIEBSBIND3; \
         char SARTVERTRIEBSBIND4; \
         char KDGRUPPESPERRKZ; \
         char KDGRUPPEFREIKZ; \



/* Copy-Function Struct to single Data KUNDENGRUPPE ***************************/

 #define KUNDENGRUPPE_S390_COPY_TO_SINGLE(_x_) \
          strcpy(KDGRUPPE,_x_->KDGRUPPE);\
          strcpy(BEZEICHNUNG,_x_->BEZEICHNUNG);\
         SARTGIFTKLASSE1=_x_->SARTGIFTKLASSE1;\
         SARTGIFTKLASSE2=_x_->SARTGIFTKLASSE2;\
         SARTGIFTKLASSE3=_x_->SARTGIFTKLASSE3;\
         SARTREZEPTPFL=_x_->SARTREZEPTPFL;\
         SARTAPOTHEKENPFL=_x_->SARTAPOTHEKENPFL;\
         SARTTAXPFL=_x_->SARTTAXPFL;\
         SARTOPIAT=_x_->SARTOPIAT;\
         SARTTIERARZNEI=_x_->SARTTIERARZNEI;\
         SARTVERTRIEBSGEB=_x_->SARTVERTRIEBSGEB;\
         SARTLIEFERSPERRE=_x_->SARTLIEFERSPERRE;\
         SARTABSCHLAG=_x_->SARTABSCHLAG;\
         SARTPREISERMAESS=_x_->SARTPREISERMAESS;\
         SARTVERTRIEBSBIND1=_x_->SARTVERTRIEBSBIND1;\
         SARTVERTRIEBSBIND2=_x_->SARTVERTRIEBSBIND2;\
         SARTVERTRIEBSBIND3=_x_->SARTVERTRIEBSBIND3;\
         SARTVERTRIEBSBIND4=_x_->SARTVERTRIEBSBIND4;\
         KDGRUPPESPERRKZ=_x_->KDGRUPPESPERRKZ;\
         KDGRUPPEFREIKZ=_x_->KDGRUPPEFREIKZ;\

 #define KUNDENGRUPPE_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->KDGRUPPE,KDGRUPPE);\
          strcpy(_x_->BEZEICHNUNG,BEZEICHNUNG);\
          _x_->SARTGIFTKLASSE1=SARTGIFTKLASSE1;\
          _x_->SARTGIFTKLASSE2=SARTGIFTKLASSE2;\
          _x_->SARTGIFTKLASSE3=SARTGIFTKLASSE3;\
          _x_->SARTREZEPTPFL=SARTREZEPTPFL;\
          _x_->SARTAPOTHEKENPFL=SARTAPOTHEKENPFL;\
          _x_->SARTTAXPFL=SARTTAXPFL;\
          _x_->SARTOPIAT=SARTOPIAT;\
          _x_->SARTTIERARZNEI=SARTTIERARZNEI;\
          _x_->SARTVERTRIEBSGEB=SARTVERTRIEBSGEB;\
          _x_->SARTLIEFERSPERRE=SARTLIEFERSPERRE;\
          _x_->SARTABSCHLAG=SARTABSCHLAG;\
          _x_->SARTPREISERMAESS=SARTPREISERMAESS;\
          _x_->SARTVERTRIEBSBIND1=SARTVERTRIEBSBIND1;\
          _x_->SARTVERTRIEBSBIND2=SARTVERTRIEBSBIND2;\
          _x_->SARTVERTRIEBSBIND3=SARTVERTRIEBSBIND3;\
          _x_->SARTVERTRIEBSBIND4=SARTVERTRIEBSBIND4;\
          _x_->KDGRUPPESPERRKZ=KDGRUPPESPERRKZ;\
          _x_->KDGRUPPEFREIKZ=KDGRUPPEFREIKZ;\



/* FunctionNumber-Define of kundengruppe **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kundengruppe **********************************/


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
		virtual int SelList(int FetchRel = 1,int pos=0)	{ return 1; }
		virtual int SelListHist(int FetchRel = 1,int pos=0)	{ return 1; }
		virtual int SelListFuture(int FetchRel = 1,int pos=0)	{ return 1; }
};
#endif

class CKUNDENGRUPPE : public ppDadeVirtual
{
	//data members
	public:
		kundengruppeS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kundengruppeS> *pl; // pointer to class list

	//functions
	public:

		const int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) {	if (GetSize() <= i)	return false; vector<kundengruppeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kundengruppeS>; Strip(s); kundengruppeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kundengruppeS>::iterator itPtr = pl->begin() + i; if ( itPtr ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kundengruppeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kundengruppeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const char*	GetKdgruppe(ppString& t) const 	{ t = s.KDGRUPPE; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetBezeichnung(ppString& t) const 	{ t = s.BEZEICHNUNG; t.erasespace(ppString::END); return t.c_str(); }
		const char&		GetSartgiftklasse1() const	{ return s.SARTGIFTKLASSE1[0]; }
		const char&		GetSartgiftklasse2() const	{ return s.SARTGIFTKLASSE2[0]; }
		const char&		GetSartgiftklasse3() const	{ return s.SARTGIFTKLASSE3[0]; }
		const char&		GetSartrezeptpfl() const	{ return s.SARTREZEPTPFL[0]; }
		const char&		GetSartapothekenpfl() const	{ return s.SARTAPOTHEKENPFL[0]; }
		const char&		GetSarttaxpfl() const	{ return s.SARTTAXPFL[0]; }
		const char&		GetSartopiat() const	{ return s.SARTOPIAT[0]; }
		const char&		GetSarttierarznei() const	{ return s.SARTTIERARZNEI[0]; }
		const char&		GetSartvertriebsgeb() const	{ return s.SARTVERTRIEBSGEB[0]; }
		const char&		GetSartliefersperre() const	{ return s.SARTLIEFERSPERRE[0]; }
		const char&		GetSartabschlag() const	{ return s.SARTABSCHLAG[0]; }
		const char&		GetSartpreisermaess() const	{ return s.SARTPREISERMAESS[0]; }
		const char&		GetSartvertriebsbind1() const	{ return s.SARTVERTRIEBSBIND1[0]; }
		const char&		GetSartvertriebsbind2() const	{ return s.SARTVERTRIEBSBIND2[0]; }
		const char&		GetSartvertriebsbind3() const	{ return s.SARTVERTRIEBSBIND3[0]; }
		const char&		GetSartvertriebsbind4() const	{ return s.SARTVERTRIEBSBIND4[0]; }
		const char&		GetKdgruppesperrkz() const	{ return s.KDGRUPPESPERRKZ[0]; }
		const char&		GetKdgruppefreikz() const	{ return s.KDGRUPPEFREIKZ[0]; }
		const kundengruppeS& GetStruct() const { return s; }
		void 		SetKdgruppe(const ppString& t) { ppGStrCopy(s.KDGRUPPE,t.c_str() ,L_KUNDENGRUPPE_KDGRUPPE); }
		void 		SetBezeichnung(const ppString& t) { ppGStrCopy(s.BEZEICHNUNG,t.c_str() ,L_KUNDENGRUPPE_BEZEICHNUNG); }
		void 		SetSartgiftklasse1(char t) { s.SARTGIFTKLASSE1[0] = t; s.SARTGIFTKLASSE1[1] = '\0';}
		void 		SetSartgiftklasse2(char t) { s.SARTGIFTKLASSE2[0] = t; s.SARTGIFTKLASSE2[1] = '\0';}
		void 		SetSartgiftklasse3(char t) { s.SARTGIFTKLASSE3[0] = t; s.SARTGIFTKLASSE3[1] = '\0';}
		void 		SetSartrezeptpfl(char t) { s.SARTREZEPTPFL[0] = t; s.SARTREZEPTPFL[1] = '\0';}
		void 		SetSartapothekenpfl(char t) { s.SARTAPOTHEKENPFL[0] = t; s.SARTAPOTHEKENPFL[1] = '\0';}
		void 		SetSarttaxpfl(char t) { s.SARTTAXPFL[0] = t; s.SARTTAXPFL[1] = '\0';}
		void 		SetSartopiat(char t) { s.SARTOPIAT[0] = t; s.SARTOPIAT[1] = '\0';}
		void 		SetSarttierarznei(char t) { s.SARTTIERARZNEI[0] = t; s.SARTTIERARZNEI[1] = '\0';}
		void 		SetSartvertriebsgeb(char t) { s.SARTVERTRIEBSGEB[0] = t; s.SARTVERTRIEBSGEB[1] = '\0';}
		void 		SetSartliefersperre(char t) { s.SARTLIEFERSPERRE[0] = t; s.SARTLIEFERSPERRE[1] = '\0';}
		void 		SetSartabschlag(char t) { s.SARTABSCHLAG[0] = t; s.SARTABSCHLAG[1] = '\0';}
		void 		SetSartpreisermaess(char t) { s.SARTPREISERMAESS[0] = t; s.SARTPREISERMAESS[1] = '\0';}
		void 		SetSartvertriebsbind1(char t) { s.SARTVERTRIEBSBIND1[0] = t; s.SARTVERTRIEBSBIND1[1] = '\0';}
		void 		SetSartvertriebsbind2(char t) { s.SARTVERTRIEBSBIND2[0] = t; s.SARTVERTRIEBSBIND2[1] = '\0';}
		void 		SetSartvertriebsbind3(char t) { s.SARTVERTRIEBSBIND3[0] = t; s.SARTVERTRIEBSBIND3[1] = '\0';}
		void 		SetSartvertriebsbind4(char t) { s.SARTVERTRIEBSBIND4[0] = t; s.SARTVERTRIEBSBIND4[1] = '\0';}
		void 		SetKdgruppesperrkz(char t) { s.KDGRUPPESPERRKZ[0] = t; s.KDGRUPPESPERRKZ[1] = '\0';}
		void 		SetKdgruppefreikz(char t) { s.KDGRUPPEFREIKZ[0] = t; s.KDGRUPPEFREIKZ[1] = '\0';}
		void 		SetStruct(const kundengruppeS& t) { s = t; }

		CKUNDENGRUPPE()  //constructor
		{
			::buf_default((void *)&s,KUNDENGRUPPE_BES,KUNDENGRUPPE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		~CKUNDENGRUPPE()  //destructor
		{
			if(pl) delete pl;
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KUNDENGRUPPE_BES, KUNDENGRUPPE_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_KUNDENGRUPPE& d)
		{
			ppGStripLast(d.KDGRUPPE);
			ppGStripLast(d.BEZEICHNUNG);
		}

		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,KUNDENGRUPPE_BES,KUNDENGRUPPE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KUNDENGRUPPE *****************************************/

 #define KUNDENGRUPPE_CREATE(x) exec sql create table x (\
         KDGRUPPE char(2) default " " not null,\
         BEZEICHNUNG char(30) default " " not null,\
         SARTGIFTKLASSE1 char(1) default " " not null,\
         SARTGIFTKLASSE2 char(1) default " " not null,\
         SARTGIFTKLASSE3 char(1) default " " not null,\
         SARTREZEPTPFL char(1) default " " not null,\
         SARTAPOTHEKENPFL char(1) default " " not null,\
         SARTTAXPFL char(1) default " " not null,\
         SARTOPIAT char(1) default " " not null,\
         SARTTIERARZNEI char(1) default " " not null,\
         SARTVERTRIEBSGEB char(1) default " " not null,\
         SARTLIEFERSPERRE char(1) default " " not null,\
         SARTABSCHLAG char(1) default " " not null,\
         SARTPREISERMAESS char(1) default " " not null,\
         SARTVERTRIEBSBIND1 char(1) default " " not null,\
         SARTVERTRIEBSBIND2 char(1) default " " not null,\
         SARTVERTRIEBSBIND3 char(1) default " " not null,\
         SARTVERTRIEBSBIND4 char(1) default " " not null,\
         KDGRUPPESPERRKZ char(1) default " " not null,\
         KDGRUPPEFREIKZ char(1) default " " not null) in zp extent size 8 lock mode row;



/* CreateIndexStatement of KUNDENGRUPPE ***************************************/

 #define KUNDENGRUPPE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_kundengruppe_1 on _X_(\
              kdgruppe ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KUNDENGRUPPE ***************************************/

 #define KUNDENGRUPPE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kundengruppe_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\


#endif
