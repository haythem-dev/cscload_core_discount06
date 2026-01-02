#ifndef __PP_DISPOARTIKEL_H_
#define __PP_DISPOARTIKEL_H_

/******************************************************************************/
/* u:\dispoartikel ************************************************************/
/******************************************************************************/

/* Length-Define of DISPOARTIKEL **********************************************/

  #define L_DISPOARTIKEL_KDAUFTRAGNR 11
  #define L_DISPOARTIKEL_POSNR 11
  #define L_DISPOARTIKEL_DARREICHFORM 3
  #define L_DISPOARTIKEL_EINHEIT 9
  #define L_DISPOARTIKEL_BEZEICHNUNG 30
  #define L_DISPOARTIKEL_ETARTKLASSE1 5
  #define L_DISPOARTIKEL_ETARTKLASSE2 5
  #define L_DISPOARTIKEL_ETARTSCHALTER1 5
  #define L_DISPOARTIKEL_ETARTSCHALTER2 5
  #define L_DISPOARTIKEL_ETARTSCHALTER3 5
  #define L_DISPOARTIKEL_ETARTSCHALTER4 5
  #define L_DISPOARTIKEL_ETARTSCHALTER5 5
  #define L_DISPOARTIKEL_PREISEKAPO 9
  #define N_DISPOARTIKEL_PREISEKAPO 2
  #define L_DISPOARTIKEL_PREISEKGROSSO 9
  #define N_DISPOARTIKEL_PREISEKGROSSO 2
  #define L_DISPOARTIKEL_RABATTFESTDM 9
  #define N_DISPOARTIKEL_RABATTFESTDM 2
  #define L_DISPOARTIKEL_RABATTFEST 7
  #define N_DISPOARTIKEL_RABATTFEST 2
  #define L_DISPOARTIKEL_RABATTFAEHIG 2
  #define L_DISPOARTIKEL_WARENGRUPPEEIGEN 5
  #define L_DISPOARTIKEL_GEBUEHRBEARB 7
  #define N_DISPOARTIKEL_GEBUEHRBEARB 2
  #define L_DISPOARTIKEL_URSPRUNGAUFTRAGNR 11
  #define L_DISPOARTIKEL_URSPRUNGPOSNR 11
  #define L_DISPOARTIKEL_TAXLEVEL 6
  #define L_DISPOARTIKEL_NETPRICE 11
  #define N_DISPOARTIKEL_NETPRICE 4
  #define L_DISPOARTIKEL_SERVICE_NO 6

/* Length/Count-Define of DISPOARTIKEL ****************************************/

  #define LS_DISPOARTIKEL_KDAUFTRAGNR 10 + 1
  #define LS_DISPOARTIKEL_POSNR 10 + 1
  #define LS_DISPOARTIKEL_DARREICHFORM 3 + 1
  #define LS_DISPOARTIKEL_EINHEIT 9 + 1
  #define LS_DISPOARTIKEL_BEZEICHNUNG 30 + 1
  #define LS_DISPOARTIKEL_ETARTKLASSE1 5 + 1
  #define LS_DISPOARTIKEL_ETARTKLASSE2 5 + 1
  #define LS_DISPOARTIKEL_ETARTSCHALTER1 5 + 1
  #define LS_DISPOARTIKEL_ETARTSCHALTER2 5 + 1
  #define LS_DISPOARTIKEL_ETARTSCHALTER3 5 + 1
  #define LS_DISPOARTIKEL_ETARTSCHALTER4 5 + 1
  #define LS_DISPOARTIKEL_ETARTSCHALTER5 5 + 1
  #define LS_DISPOARTIKEL_PREISEKAPO 9 + 2
  #define LS_DISPOARTIKEL_PREISEKGROSSO 9 + 2
  #define LS_DISPOARTIKEL_RABATTFESTDM 9 + 2
  #define LS_DISPOARTIKEL_RABATTFEST 7 + 2
  #define LS_DISPOARTIKEL_RABATTFAEHIG 2 + 1
  #define LS_DISPOARTIKEL_WARENGRUPPEEIGEN 5 + 1
  #define LS_DISPOARTIKEL_GEBUEHRBEARB 7 + 2
  #define LS_DISPOARTIKEL_URSPRUNGAUFTRAGNR 10 + 1
  #define LS_DISPOARTIKEL_URSPRUNGPOSNR 10 + 1
  #define LS_DISPOARTIKEL_TAXLEVEL 5 + 1
  #define LS_DISPOARTIKEL_NETPRICE 11 + 2
  #define LS_DISPOARTIKEL_SERVICE_NO 5 + 1

  #define DISPOARTIKELKDAUFTRAGNR 0
  #define DISPOARTIKELPOSNR 1
  #define DISPOARTIKELDARREICHFORM 2
  #define DISPOARTIKELEINHEIT 3
  #define DISPOARTIKELBEZEICHNUNG 4
  #define DISPOARTIKELETARTKLASSE1 5
  #define DISPOARTIKELETARTKLASSE2 6
  #define DISPOARTIKELETARTSCHALTER1 7
  #define DISPOARTIKELETARTSCHALTER2 8
  #define DISPOARTIKELETARTSCHALTER3 9
  #define DISPOARTIKELETARTSCHALTER4 10
  #define DISPOARTIKELETARTSCHALTER5 11
  #define DISPOARTIKELPREISEKAPO 12
  #define DISPOARTIKELPREISEKGROSSO 13
  #define DISPOARTIKELRABATTFESTDM 14
  #define DISPOARTIKELRABATTFEST 15
  #define DISPOARTIKELRABATTFAEHIG 16
  #define DISPOARTIKELWARENGRUPPEEIGEN 17
  #define DISPOARTIKELGEBUEHRBEARB 18
  #define DISPOARTIKELURSPRUNGAUFTRAGNR 19
  #define DISPOARTIKELURSPRUNGPOSNR 20
  #define DISPOARTIKELTAXLEVEL 21
  #define DISPOARTIKELNETPRICE 22
  #define DISPOARTIKELSERVICE_NO 23

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DISPOARTIKEL_H
 #define DISPOARTIKEL_ANZ ( sizeof(DISPOARTIKEL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DISPOARTIKEL **************************************************/

 #define DISPOARTIKEL_LISTE \
         DISPOARTIKEL.KDAUFTRAGNR,\
         DISPOARTIKEL.POSNR,\
         DISPOARTIKEL.DARREICHFORM,\
         DISPOARTIKEL.EINHEIT,\
         DISPOARTIKEL.BEZEICHNUNG,\
         DISPOARTIKEL.ETARTKLASSE1,\
         DISPOARTIKEL.ETARTKLASSE2,\
         DISPOARTIKEL.ETARTSCHALTER1,\
         DISPOARTIKEL.ETARTSCHALTER2,\
         DISPOARTIKEL.ETARTSCHALTER3,\
         DISPOARTIKEL.ETARTSCHALTER4,\
         DISPOARTIKEL.ETARTSCHALTER5,\
         DISPOARTIKEL.PREISEKAPO,\
         DISPOARTIKEL.PREISEKGROSSO,\
         DISPOARTIKEL.RABATTFESTDM,\
         DISPOARTIKEL.RABATTFEST,\
         DISPOARTIKEL.RABATTFAEHIG,\
         DISPOARTIKEL.WARENGRUPPEEIGEN,\
         DISPOARTIKEL.GEBUEHRBEARB,\
         DISPOARTIKEL.URSPRUNGAUFTRAGNR,\
         DISPOARTIKEL.URSPRUNGPOSNR,\
         DISPOARTIKEL.TAXLEVEL,\
         DISPOARTIKEL.NETPRICE,\
         DISPOARTIKEL.SERVICE_NO

 #define DISPOARTIKEL_LISTE_390 \
         KDAUFTRAGNR,\
         POSNR,\
         DARREICHFORM,\
         EINHEIT,\
         BEZEICHNUNG,\
         ETARTKLASSE1,\
         ETARTKLASSE2,\
         ETARTSCHALTER1,\
         ETARTSCHALTER2,\
         ETARTSCHALTER3,\
         ETARTSCHALTER4,\
         ETARTSCHALTER5,\
         PREISEKAPO,\
         PREISEKGROSSO,\
         RABATTFESTDM,\
         RABATTFEST,\
         RABATTFAEHIG,\
         WARENGRUPPEEIGEN,\
         GEBUEHRBEARB,\
         URSPRUNGAUFTRAGNR,\
         URSPRUNGPOSNR,\
         TAXLEVEL,\
         NETPRICE,\
         SERVICE_NO

 #define DISPOARTIKEL_PLISTE \
         "DISPOARTIKEL.KDAUFTRAGNR,"\
         "DISPOARTIKEL.POSNR,"\
         "DISPOARTIKEL.DARREICHFORM,"\
         "DISPOARTIKEL.EINHEIT,"\
         "DISPOARTIKEL.BEZEICHNUNG,"\
         "DISPOARTIKEL.ETARTKLASSE1,"\
         "DISPOARTIKEL.ETARTKLASSE2,"\
         "DISPOARTIKEL.ETARTSCHALTER1,"\
         "DISPOARTIKEL.ETARTSCHALTER2,"\
         "DISPOARTIKEL.ETARTSCHALTER3,"\
         "DISPOARTIKEL.ETARTSCHALTER4,"\
         "DISPOARTIKEL.ETARTSCHALTER5,"\
         "DISPOARTIKEL.PREISEKAPO,"\
         "DISPOARTIKEL.PREISEKGROSSO,"\
         "DISPOARTIKEL.RABATTFESTDM,"\
         "DISPOARTIKEL.RABATTFEST,"\
         "DISPOARTIKEL.RABATTFAEHIG,"\
         "DISPOARTIKEL.WARENGRUPPEEIGEN,"\
         "DISPOARTIKEL.GEBUEHRBEARB,"\
         "DISPOARTIKEL.URSPRUNGAUFTRAGNR,"\
         "DISPOARTIKEL.URSPRUNGPOSNR,"\
         "DISPOARTIKEL.TAXLEVEL,"\
         "DISPOARTIKEL.NETPRICE,"\
         "DISPOARTIKEL.SERVICE_NO"

 #define DISPOARTIKEL_PELISTE \
         "KDAUFTRAGNR,"\
         "POSNR,"\
         "DARREICHFORM,"\
         "EINHEIT,"\
         "BEZEICHNUNG,"\
         "ETARTKLASSE1,"\
         "ETARTKLASSE2,"\
         "ETARTSCHALTER1,"\
         "ETARTSCHALTER2,"\
         "ETARTSCHALTER3,"\
         "ETARTSCHALTER4,"\
         "ETARTSCHALTER5,"\
         "PREISEKAPO,"\
         "PREISEKGROSSO,"\
         "RABATTFESTDM,"\
         "RABATTFEST,"\
         "RABATTFAEHIG,"\
         "WARENGRUPPEEIGEN,"\
         "GEBUEHRBEARB,"\
         "URSPRUNGAUFTRAGNR,"\
         "URSPRUNGPOSNR,"\
         "TAXLEVEL,"\
         "NETPRICE,"\
         "SERVICE_NO"

 #define DISPOARTIKEL_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "POSNR=?,"\
         "DARREICHFORM=?,"\
         "EINHEIT=?,"\
         "BEZEICHNUNG=?,"\
         "ETARTKLASSE1=?,"\
         "ETARTKLASSE2=?,"\
         "ETARTSCHALTER1=?,"\
         "ETARTSCHALTER2=?,"\
         "ETARTSCHALTER3=?,"\
         "ETARTSCHALTER4=?,"\
         "ETARTSCHALTER5=?,"\
         "PREISEKAPO=?,"\
         "PREISEKGROSSO=?,"\
         "RABATTFESTDM=?,"\
         "RABATTFEST=?,"\
         "RABATTFAEHIG=?,"\
         "WARENGRUPPEEIGEN=?,"\
         "GEBUEHRBEARB=?,"\
         "URSPRUNGAUFTRAGNR=?,"\
         "URSPRUNGPOSNR=?,"\
         "TAXLEVEL=?,"\
         "NETPRICE=?,"\
         "SERVICE_NO=?"

/* SqlMacros-Define of DISPOARTIKEL *******************************************/

 #define DISPOARTIKEL_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->DARREICHFORM,\
         :x->EINHEIT,\
         :x->BEZEICHNUNG,\
         :x->ETARTKLASSE1,\
         :x->ETARTKLASSE2,\
         :x->ETARTSCHALTER1,\
         :x->ETARTSCHALTER2,\
         :x->ETARTSCHALTER3,\
         :x->ETARTSCHALTER4,\
         :x->ETARTSCHALTER5,\
         :x->PREISEKAPO,\
         :x->PREISEKGROSSO,\
         :x->RABATTFESTDM,\
         :x->RABATTFEST,\
         :x->RABATTFAEHIG,\
         :x->WARENGRUPPEEIGEN,\
         :x->GEBUEHRBEARB,\
         :x->URSPRUNGAUFTRAGNR,\
         :x->URSPRUNGPOSNR,\
         :x->TAXLEVEL,\
         :x->NETPRICE,\
         :x->SERVICE_NO

 #define DISPOARTIKEL_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->DARREICHFORM,\
         :x->EINHEIT,\
         :x->BEZEICHNUNG,\
         :x->ETARTKLASSE1,\
         :x->ETARTKLASSE2,\
         :x->ETARTSCHALTER1,\
         :x->ETARTSCHALTER2,\
         :x->ETARTSCHALTER3,\
         :x->ETARTSCHALTER4,\
         :x->ETARTSCHALTER5,\
         :x->PREISEKAPO,\
         :x->PREISEKGROSSO,\
         :x->RABATTFESTDM,\
         :x->RABATTFEST,\
         :x->RABATTFAEHIG,\
         :x->WARENGRUPPEEIGEN,\
         :x->GEBUEHRBEARB,\
         :x->URSPRUNGAUFTRAGNR,\
         :x->URSPRUNGPOSNR,\
         :x->TAXLEVEL,\
         :x->NETPRICE,\
         :x->SERVICE_NO

 #define DISPOARTIKEL_UPDATE(x) \
         DISPOARTIKEL.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         DISPOARTIKEL.POSNR=:x->POSNR,\
         DISPOARTIKEL.DARREICHFORM=:x->DARREICHFORM,\
         DISPOARTIKEL.EINHEIT=:x->EINHEIT,\
         DISPOARTIKEL.BEZEICHNUNG=:x->BEZEICHNUNG,\
         DISPOARTIKEL.ETARTKLASSE1=:x->ETARTKLASSE1,\
         DISPOARTIKEL.ETARTKLASSE2=:x->ETARTKLASSE2,\
         DISPOARTIKEL.ETARTSCHALTER1=:x->ETARTSCHALTER1,\
         DISPOARTIKEL.ETARTSCHALTER2=:x->ETARTSCHALTER2,\
         DISPOARTIKEL.ETARTSCHALTER3=:x->ETARTSCHALTER3,\
         DISPOARTIKEL.ETARTSCHALTER4=:x->ETARTSCHALTER4,\
         DISPOARTIKEL.ETARTSCHALTER5=:x->ETARTSCHALTER5,\
         DISPOARTIKEL.PREISEKAPO=:x->PREISEKAPO,\
         DISPOARTIKEL.PREISEKGROSSO=:x->PREISEKGROSSO,\
         DISPOARTIKEL.RABATTFESTDM=:x->RABATTFESTDM,\
         DISPOARTIKEL.RABATTFEST=:x->RABATTFEST,\
         DISPOARTIKEL.RABATTFAEHIG=:x->RABATTFAEHIG,\
         DISPOARTIKEL.WARENGRUPPEEIGEN=:x->WARENGRUPPEEIGEN,\
         DISPOARTIKEL.GEBUEHRBEARB=:x->GEBUEHRBEARB,\
         DISPOARTIKEL.URSPRUNGAUFTRAGNR=:x->URSPRUNGAUFTRAGNR,\
         DISPOARTIKEL.URSPRUNGPOSNR=:x->URSPRUNGPOSNR,\
         DISPOARTIKEL.TAXLEVEL=:x->TAXLEVEL,\
         DISPOARTIKEL.NETPRICE=:x->NETPRICE,\
         DISPOARTIKEL.SERVICE_NO=:x->SERVICE_NO

/* SqlMacros390-Define of DISPOARTIKEL ****************************************/

 #define DISPOARTIKEL_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :POSNR,\
         :DARREICHFORM,\
         :EINHEIT,\
         :BEZEICHNUNG,\
         :ETARTKLASSE1,\
         :ETARTKLASSE2,\
         :ETARTSCHALTER1,\
         :ETARTSCHALTER2,\
         :ETARTSCHALTER3,\
         :ETARTSCHALTER4,\
         :ETARTSCHALTER5,\
         :PREISEKAPO,\
         :PREISEKGROSSO,\
         :RABATTFESTDM,\
         :RABATTFEST,\
         :RABATTFAEHIG,\
         :WARENGRUPPEEIGEN,\
         :GEBUEHRBEARB,\
         :URSPRUNGAUFTRAGNR,\
         :URSPRUNGPOSNR,\
         :TAXLEVEL,\
         :NETPRICE,\
         :SERVICE_NO

 #define DISPOARTIKEL_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         POSNR=:POSNR,\
         DARREICHFORM=:DARREICHFORM,\
         EINHEIT=:EINHEIT,\
         BEZEICHNUNG=:BEZEICHNUNG,\
         ETARTKLASSE1=:ETARTKLASSE1,\
         ETARTKLASSE2=:ETARTKLASSE2,\
         ETARTSCHALTER1=:ETARTSCHALTER1,\
         ETARTSCHALTER2=:ETARTSCHALTER2,\
         ETARTSCHALTER3=:ETARTSCHALTER3,\
         ETARTSCHALTER4=:ETARTSCHALTER4,\
         ETARTSCHALTER5=:ETARTSCHALTER5,\
         PREISEKAPO=:PREISEKAPO,\
         PREISEKGROSSO=:PREISEKGROSSO,\
         RABATTFESTDM=:RABATTFESTDM,\
         RABATTFEST=:RABATTFEST,\
         RABATTFAEHIG=:RABATTFAEHIG,\
         WARENGRUPPEEIGEN=:WARENGRUPPEEIGEN,\
         GEBUEHRBEARB=:GEBUEHRBEARB,\
         URSPRUNGAUFTRAGNR=:URSPRUNGAUFTRAGNR,\
         URSPRUNGPOSNR=:URSPRUNGPOSNR,\
         TAXLEVEL=:TAXLEVEL,\
         NETPRICE=:NETPRICE,\
         SERVICE_NO=:SERVICE_NO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of DISPOARTIKEL *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_DISPOARTIKEL {
         long KDAUFTRAGNR;
         long POSNR;
         char DARREICHFORM[4];
         char EINHEIT[10];
         char BEZEICHNUNG[31];
         long ETARTKLASSE1;
         long ETARTKLASSE2;
         long ETARTSCHALTER1;
         long ETARTSCHALTER2;
         long ETARTSCHALTER3;
         long ETARTSCHALTER4;
         long ETARTSCHALTER5;
         double PREISEKAPO;
         double PREISEKGROSSO;
         double RABATTFESTDM;
         double RABATTFEST;
         char RABATTFAEHIG[3];
         char WARENGRUPPEEIGEN[6];
         double GEBUEHRBEARB;
         long URSPRUNGAUFTRAGNR;
         long URSPRUNGPOSNR;
         short TAXLEVEL;
         double NETPRICE;
         short SERVICE_NO;
        } dispoartikelS;
 #else /*TRANSCLASS*/
 typedef struct N_DISPOARTIKEL {
         long KDAUFTRAGNR;
         long POSNR;
         char DARREICHFORM[4];
         char EINHEIT[10];
         char BEZEICHNUNG[31];
         long ETARTKLASSE1;
         long ETARTKLASSE2;
         long ETARTSCHALTER1;
         long ETARTSCHALTER2;
         long ETARTSCHALTER3;
         long ETARTSCHALTER4;
         long ETARTSCHALTER5;
         double PREISEKAPO;
         double PREISEKGROSSO;
         double RABATTFESTDM;
         double RABATTFEST;
         char RABATTFAEHIG[3];
         char WARENGRUPPEEIGEN[6];
         double GEBUEHRBEARB;
         long URSPRUNGAUFTRAGNR;
         long URSPRUNGPOSNR;
         short TAXLEVEL;
         double NETPRICE;
         short SERVICE_NO;

                        bool operator==(const N_DISPOARTIKEL& right) const {
                        return(
                                KDAUFTRAGNR == right.KDAUFTRAGNR &&
                                POSNR == right.POSNR &&
                                !strcmp(DARREICHFORM, right.DARREICHFORM) &&
                                !strcmp(EINHEIT, right.EINHEIT) &&
                                !strcmp(BEZEICHNUNG, right.BEZEICHNUNG) &&
                                ETARTKLASSE1 == right.ETARTKLASSE1 &&
                                ETARTKLASSE2 == right.ETARTKLASSE2 &&
                                ETARTSCHALTER1 == right.ETARTSCHALTER1 &&
                                ETARTSCHALTER2 == right.ETARTSCHALTER2 &&
                                ETARTSCHALTER3 == right.ETARTSCHALTER3 &&
                                ETARTSCHALTER4 == right.ETARTSCHALTER4 &&
                                ETARTSCHALTER5 == right.ETARTSCHALTER5 &&
                                PREISEKAPO == right.PREISEKAPO &&
                                PREISEKGROSSO == right.PREISEKGROSSO &&
                                RABATTFESTDM == right.RABATTFESTDM &&
                                RABATTFEST == right.RABATTFEST &&
                                !strcmp(RABATTFAEHIG, right.RABATTFAEHIG) &&
                                !strcmp(WARENGRUPPEEIGEN, right.WARENGRUPPEEIGEN) &&
                                GEBUEHRBEARB == right.GEBUEHRBEARB &&
                                URSPRUNGAUFTRAGNR == right.URSPRUNGAUFTRAGNR &&
                                URSPRUNGPOSNR == right.URSPRUNGPOSNR &&
                                TAXLEVEL == right.TAXLEVEL &&
                                NETPRICE == right.NETPRICE &&
                                SERVICE_NO == right.SERVICE_NO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                KDAUFTRAGNR = 0;
                                POSNR = 0;
                                strcpy(DARREICHFORM, " " );
                                strcpy(EINHEIT, " " );
                                strcpy(BEZEICHNUNG, " " );
                                ETARTKLASSE1 = 0;
                                ETARTKLASSE2 = 0;
                                ETARTSCHALTER1 = 0;
                                ETARTSCHALTER2 = 0;
                                ETARTSCHALTER3 = 0;
                                ETARTSCHALTER4 = 0;
                                ETARTSCHALTER5 = 0;
                                PREISEKAPO = 0;
                                PREISEKGROSSO = 0;
                                RABATTFESTDM = 0;
                                RABATTFEST = 0;
                                strcpy(RABATTFAEHIG, " " );
                                strcpy(WARENGRUPPEEIGEN, " " );
                                GEBUEHRBEARB = 0;
                                URSPRUNGAUFTRAGNR = 0;
                                URSPRUNGPOSNR = 0;
                                TAXLEVEL = 0;
                                NETPRICE = 0;
                                SERVICE_NO = 0;
#endif
                        }
         } dispoartikelS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DISPOARTIKEL **************************************/

 struct S_DISPOARTIKEL {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char DARREICHFORM[3 + 1];
         char EINHEIT[9 + 1];
         char BEZEICHNUNG[30 + 1];
         char ETARTKLASSE1[5 + 1];
         char ETARTKLASSE2[5 + 1];
         char ETARTSCHALTER1[5 + 1];
         char ETARTSCHALTER2[5 + 1];
         char ETARTSCHALTER3[5 + 1];
         char ETARTSCHALTER4[5 + 1];
         char ETARTSCHALTER5[5 + 1];
         char PREISEKAPO[9 + 2];
         char PREISEKGROSSO[9 + 2];
         char RABATTFESTDM[9 + 2];
         char RABATTFEST[7 + 2];
         char RABATTFAEHIG[2 + 1];
         char WARENGRUPPEEIGEN[5 + 1];
         char GEBUEHRBEARB[7 + 2];
         char URSPRUNGAUFTRAGNR[11];
         char URSPRUNGPOSNR[11];
         char TAXLEVEL[7];
         char NETPRICE[11 + 2];
         char SERVICE_NO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DISPOARTIKEL *********************/

 struct O_DISPOARTIKEL {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char DARREICHFORM[3];
         char EINHEIT[9];
         char BEZEICHNUNG[30];
         char ETARTKLASSE1[5];
         char ETARTKLASSE2[5];
         char ETARTSCHALTER1[5];
         char ETARTSCHALTER2[5];
         char ETARTSCHALTER3[5];
         char ETARTSCHALTER4[5];
         char ETARTSCHALTER5[5];
         char PREISEKAPO[9];
         char PREISEKGROSSO[9];
         char RABATTFESTDM[9];
         char RABATTFEST[7];
         char RABATTFAEHIG[2];
         char WARENGRUPPEEIGEN[5];
         char GEBUEHRBEARB[7];
         char URSPRUNGAUFTRAGNR[11];
         char URSPRUNGPOSNR[11];
         char TAXLEVEL[7];
         char NETPRICE[11];
         char SERVICE_NO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DISPOARTIKEL ********************************/

 struct C_DISPOARTIKEL {
         long KDAUFTRAGNR;
         long POSNR;
         char DARREICHFORM[4];
         char EINHEIT[10];
         char BEZEICHNUNG[31];
         long ETARTKLASSE1;
         long ETARTKLASSE2;
         long ETARTSCHALTER1;
         long ETARTSCHALTER2;
         long ETARTSCHALTER3;
         long ETARTSCHALTER4;
         long ETARTSCHALTER5;
         double PREISEKAPO;
         double PREISEKGROSSO;
         double RABATTFESTDM;
         double RABATTFEST;
         char RABATTFAEHIG[3];
         char WARENGRUPPEEIGEN[6];
         double GEBUEHRBEARB;
         long URSPRUNGAUFTRAGNR;
         long URSPRUNGPOSNR;
         short TAXLEVEL;
         double NETPRICE;
         short SERVICE_NO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DISPOARTIKEL ******************************/

 struct I_DISPOARTIKEL {
         short KDAUFTRAGNR;
         short POSNR;
         short DARREICHFORM;
         short EINHEIT;
         short BEZEICHNUNG;
         short ETARTKLASSE1;
         short ETARTKLASSE2;
         short ETARTSCHALTER1;
         short ETARTSCHALTER2;
         short ETARTSCHALTER3;
         short ETARTSCHALTER4;
         short ETARTSCHALTER5;
         short PREISEKAPO;
         short PREISEKGROSSO;
         short RABATTFESTDM;
         short RABATTFEST;
         short RABATTFAEHIG;
         short WARENGRUPPEEIGEN;
         short GEBUEHRBEARB;
         short URSPRUNGAUFTRAGNR;
         short URSPRUNGPOSNR;
         short TAXLEVEL;
         short NETPRICE;
         short SERVICE_NO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DISPOARTIKEL ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc DISPOARTIKEL_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 30, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 7, 2 },
   { TYP_C, 2, 0 },
   { TYP_C, 5, 0 },
   { TYP_D, 7, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 4 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DISPOARTIKEL_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 30, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L ,  11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 7, 2 },
   { TYP_C, 2, 0 },
   { TYP_C, 5, 0 },
   { TYP_D, 7, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 11, 4 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of DISPOARTIKEL **********************************/

 #define DISPOARTIKEL_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         char DARREICHFORM[4]; \
         char EINHEIT[10]; \
         char BEZEICHNUNG[31]; \
         long ETARTKLASSE1; \
         long ETARTKLASSE2; \
         long ETARTSCHALTER1; \
         long ETARTSCHALTER2; \
         long ETARTSCHALTER3; \
         long ETARTSCHALTER4; \
         long ETARTSCHALTER5; \
         double PREISEKAPO; \
         double PREISEKGROSSO; \
         double RABATTFESTDM; \
         double RABATTFEST; \
         char RABATTFAEHIG[3]; \
         char WARENGRUPPEEIGEN[6]; \
         double GEBUEHRBEARB; \
         long URSPRUNGAUFTRAGNR; \
         long URSPRUNGPOSNR; \
         short TAXLEVEL; \
         double NETPRICE; \
         short SERVICE_NO; \



/* Copy-Function Struct to single Data DISPOARTIKEL ***************************/

 #define DISPOARTIKEL_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
          strcpy(DARREICHFORM,_x_->DARREICHFORM);\
          strcpy(EINHEIT,_x_->EINHEIT);\
          strcpy(BEZEICHNUNG,_x_->BEZEICHNUNG);\
         ETARTKLASSE1=_x_->ETARTKLASSE1;\
         ETARTKLASSE2=_x_->ETARTKLASSE2;\
         ETARTSCHALTER1=_x_->ETARTSCHALTER1;\
         ETARTSCHALTER2=_x_->ETARTSCHALTER2;\
         ETARTSCHALTER3=_x_->ETARTSCHALTER3;\
         ETARTSCHALTER4=_x_->ETARTSCHALTER4;\
         ETARTSCHALTER5=_x_->ETARTSCHALTER5;\
         PREISEKAPO=_x_->PREISEKAPO;\
         PREISEKGROSSO=_x_->PREISEKGROSSO;\
         RABATTFESTDM=_x_->RABATTFESTDM;\
         RABATTFEST=_x_->RABATTFEST;\
          strcpy(RABATTFAEHIG,_x_->RABATTFAEHIG);\
          strcpy(WARENGRUPPEEIGEN,_x_->WARENGRUPPEEIGEN);\
         GEBUEHRBEARB=_x_->GEBUEHRBEARB;\
         URSPRUNGAUFTRAGNR=_x_->URSPRUNGAUFTRAGNR;\
         URSPRUNGPOSNR=_x_->URSPRUNGPOSNR;\
         TAXLEVEL=_x_->TAXLEVEL;\
         NETPRICE=_x_->NETPRICE;\
         SERVICE_NO=_x_->SERVICE_NO;\

 #define DISPOARTIKEL_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          strcpy(_x_->DARREICHFORM,DARREICHFORM);\
          strcpy(_x_->EINHEIT,EINHEIT);\
          strcpy(_x_->BEZEICHNUNG,BEZEICHNUNG);\
          _x_->ETARTKLASSE1=ETARTKLASSE1;\
          _x_->ETARTKLASSE2=ETARTKLASSE2;\
          _x_->ETARTSCHALTER1=ETARTSCHALTER1;\
          _x_->ETARTSCHALTER2=ETARTSCHALTER2;\
          _x_->ETARTSCHALTER3=ETARTSCHALTER3;\
          _x_->ETARTSCHALTER4=ETARTSCHALTER4;\
          _x_->ETARTSCHALTER5=ETARTSCHALTER5;\
          _x_->PREISEKAPO=PREISEKAPO;\
          _x_->PREISEKGROSSO=PREISEKGROSSO;\
          _x_->RABATTFESTDM=RABATTFESTDM;\
          _x_->RABATTFEST=RABATTFEST;\
          strcpy(_x_->RABATTFAEHIG,RABATTFAEHIG);\
          strcpy(_x_->WARENGRUPPEEIGEN,WARENGRUPPEEIGEN);\
          _x_->GEBUEHRBEARB=GEBUEHRBEARB;\
          _x_->URSPRUNGAUFTRAGNR=URSPRUNGAUFTRAGNR;\
          _x_->URSPRUNGPOSNR=URSPRUNGPOSNR;\
          _x_->TAXLEVEL=TAXLEVEL;\
          _x_->NETPRICE=NETPRICE;\
          _x_->SERVICE_NO=SERVICE_NO;\



/* FunctionNumber-Define of dispoartikel **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of dispoartikel **********************************/


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

class CDISPOARTIKEL : public ppDadeVirtual
{
        //data members
        public:
                dispoartikelS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<dispoartikelS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<dispoartikelS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<dispoartikelS>; Strip(s); dispoartikelS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<dispoartikelS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<dispoartikelS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<dispoartikelS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetKdauftragnr() const  { return s.KDAUFTRAGNR; }
                long            GetPosnr() const        { return s.POSNR; }
                const char*     GetDarreichform(ppString& t) const      { t = s.DARREICHFORM; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetEinheit(ppString& t) const   { t = s.EINHEIT; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetBezeichnung(ppString& t) const       { t = s.BEZEICHNUNG; t.erasespace(ppString::END); return t.c_str(); }
                long            GetEtartklasse1() const { return s.ETARTKLASSE1; }
                long            GetEtartklasse2() const { return s.ETARTKLASSE2; }
                long            GetEtartschalter1() const       { return s.ETARTSCHALTER1; }
                long            GetEtartschalter2() const       { return s.ETARTSCHALTER2; }
                long            GetEtartschalter3() const       { return s.ETARTSCHALTER3; }
                long            GetEtartschalter4() const       { return s.ETARTSCHALTER4; }
                long            GetEtartschalter5() const       { return s.ETARTSCHALTER5; }
                double          GetPreisekapo() const   { return s.PREISEKAPO; }
                double          GetPreisekgrosso() const        { return s.PREISEKGROSSO; }
                double          GetRabattfestdm() const { return s.RABATTFESTDM; }
                double          GetRabattfest() const   { return s.RABATTFEST; }
                const char*     GetRabattfaehig(ppString& t) const      { t = s.RABATTFAEHIG; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetWarengruppeeigen(ppString& t) const  { t = s.WARENGRUPPEEIGEN; t.erasespace(ppString::END); return t.c_str(); }
                double          GetGebuehrbearb() const { return s.GEBUEHRBEARB; }
                long            GetUrsprungauftragnr() const    { return s.URSPRUNGAUFTRAGNR; }
                long            GetUrsprungposnr() const        { return s.URSPRUNGPOSNR; }
                short           GetTaxlevel() const     { return s.TAXLEVEL; }
                double          GetNetprice() const     { return s.NETPRICE; }
                short           GetService_no() const   { return s.SERVICE_NO; }
                const dispoartikelS& GetStruct() const { return s; }
                void            SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
                void            SetPosnr(long t) { s.POSNR = t; }
                void            SetDarreichform(const ppString& t) { ppGStrCopy(s.DARREICHFORM,t.c_str() ,L_DISPOARTIKEL_DARREICHFORM); }
                void            SetEinheit(const ppString& t) { ppGStrCopy(s.EINHEIT,t.c_str() ,L_DISPOARTIKEL_EINHEIT); }
                void            SetBezeichnung(const ppString& t) { ppGStrCopy(s.BEZEICHNUNG,t.c_str() ,L_DISPOARTIKEL_BEZEICHNUNG); }
                void            SetEtartklasse1(long t) { s.ETARTKLASSE1 = t; }
                void            SetEtartklasse2(long t) { s.ETARTKLASSE2 = t; }
                void            SetEtartschalter1(long t) { s.ETARTSCHALTER1 = t; }
                void            SetEtartschalter2(long t) { s.ETARTSCHALTER2 = t; }
                void            SetEtartschalter3(long t) { s.ETARTSCHALTER3 = t; }
                void            SetEtartschalter4(long t) { s.ETARTSCHALTER4 = t; }
                void            SetEtartschalter5(long t) { s.ETARTSCHALTER5 = t; }
                void            SetPreisekapo(double t) { s.PREISEKAPO = t; }
                void            SetPreisekgrosso(double t) { s.PREISEKGROSSO = t; }
                void            SetRabattfestdm(double t) { s.RABATTFESTDM = t; }
                void            SetRabattfest(double t) { s.RABATTFEST = t; }
                void            SetRabattfaehig(const ppString& t) { ppGStrCopy(s.RABATTFAEHIG,t.c_str() ,L_DISPOARTIKEL_RABATTFAEHIG); }
                void            SetWarengruppeeigen(const ppString& t) { ppGStrCopy(s.WARENGRUPPEEIGEN,t.c_str() ,L_DISPOARTIKEL_WARENGRUPPEEIGEN); }
                void            SetGebuehrbearb(double t) { s.GEBUEHRBEARB = t; }
                void            SetUrsprungauftragnr(long t) { s.URSPRUNGAUFTRAGNR = t; }
                void            SetUrsprungposnr(long t) { s.URSPRUNGPOSNR = t; }
                void            SetTaxlevel(short t) { s.TAXLEVEL = t; }
                void            SetNetprice(double t) { s.NETPRICE = t; }
                void            SetService_no(short t) { s.SERVICE_NO = t; }
                void            SetStruct(const dispoartikelS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CDISPOARTIKEL()  //constructor
                {
                        ::buf_default((void *)&s, DISPOARTIKEL_BES, DISPOARTIKEL_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CDISPOARTIKEL()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, DISPOARTIKEL_BES, DISPOARTIKEL_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DISPOARTIKEL_BES, DISPOARTIKEL_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, DISPOARTIKEL_BES, DISPOARTIKEL_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_DISPOARTIKEL& d)
                {
#ifdef WIN32
                        ppGStripLast(d.DARREICHFORM);
                        ppGStripLast(d.EINHEIT);
                        ppGStripLast(d.BEZEICHNUNG);
                        ppGStripLast(d.RABATTFAEHIG);
                        ppGStripLast(d.WARENGRUPPEEIGEN);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, DISPOARTIKEL_BES, DISPOARTIKEL_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of DISPOARTIKEL *****************************************/

 #define DISPOARTIKEL_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         DARREICHFORM char(3) default " " not null,\
         EINHEIT char(9) default " " not null,\
         BEZEICHNUNG char(30) default " " not null,\
         ETARTKLASSE1 integer default 0 not null,\
         ETARTKLASSE2 integer default 0 not null,\
         ETARTSCHALTER1 integer default 0 not null,\
         ETARTSCHALTER2 integer default 0 not null,\
         ETARTSCHALTER3 integer default 0 not null,\
         ETARTSCHALTER4 integer default 0 not null,\
         ETARTSCHALTER5 integer default 0 not null,\
         PREISEKAPO decimal(9,2) default 0 not null,\
         PREISEKGROSSO decimal(9,2) default 0 not null,\
         RABATTFESTDM decimal(9,2) default 0 not null,\
         RABATTFEST decimal(7,2) default 0 not null,\
         RABATTFAEHIG char(2) default " " not null,\
         WARENGRUPPEEIGEN char(5) default " " not null,\
         GEBUEHRBEARB decimal(7,2) default 0 not null,\
         URSPRUNGAUFTRAGNR integer default 0 not null,\
         URSPRUNGPOSNR integer default 0 not null,\
         TAXLEVEL smallint default 0 not null,\
         NETPRICE decimal(11,4) default 0 not null,\
         SERVICE_NO smallint default 0 not null) in KscOrder extent size 52 next size 8 lock mode row;



/* CreateIndexStatement of DISPOARTIKEL ***************************************/

 #define DISPOARTIKEL_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_dispoartikel_1 on _X_(\
              kdauftragnr,\
              posnr ) in KscOrderIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of DISPOARTIKEL ***************************************/

 #define DISPOARTIKEL_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_dispoartikel_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
