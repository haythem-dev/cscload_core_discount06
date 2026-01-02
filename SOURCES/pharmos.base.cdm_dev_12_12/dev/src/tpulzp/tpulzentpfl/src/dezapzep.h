#ifndef __PP_DEZAPZEP_H_
#define __PP_DEZAPZEP_H_

/******************************************************************************/
/* d:\prj\df\unix\tpulzentpfl\DezapZep ****************************************/
/******************************************************************************/

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DEZAPZARTIKEL_H
 #define DEZAPZARTIKEL_ANZ ( sizeof(DEZAPZARTIKEL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DEZAPZARTIKEL ************************************************/

 #define DEZAPZARTIKEL_PLISTE \
         "ZARTIKEL.ARTIKEL_NR,"\
         "ZARTIKEL.ARTIKEL_MC,"\
         "ZARTIKEL.ARTIKEL_NAME,"\
         "ZARTIKEL.EINHEIT,"\
         "ZARTIKEL.DARREICHFORM,"\
         "ZARTIKEL.ERSATZ_NR_AKTIV,"\
         "ZARTIKEL.ERSATZ_NR,"\
         "ZARTIKEL.HERSTELLER_NR,"\
         "ZARTIKEL.LAENGE,"\
         "ZARTIKEL.HOEHE,"\
         "ZARTIKEL.BREITE,"\
         "ZARTIKEL.GEWICHT,"\
         "ZARTIKEL.LAUFZEITMONATE,"\
         "ZARTIKEL.RABATTFAEHIG,"\
         "ZARTIKEL.PRIVATSORTIMENT,"\
         "ZARTIKEL.DATUM_IFAAENDER,"\
         "ZARTIKEL.DATUM_AH,"\
         "ZARTIKEL.DATUM_RR,"\
         "ZARTIKEL.DATUM_IFALOESCH,"\
         "ZARTIKEL.FESTBETRAG1,"\
         "ZARTIKEL.PERSONALRABATT,"\
         "ZARTIKEL.FESTBREGEL,"\
         "ZARTIKEL.WIRKSTOFF_NR,"\
         "ZARTIKEL.SONDERGROSSO,"\
         "ZARTIKEL.BESTANDSBUCHUNG,"\
         "ZARTIKEL.SKONTOFAEHIG,"\
         "ZARTIKEL.PREIS0ARTIKEL,"\
         "ZARTIKEL.MELDEPFL,"\
         "ZARTIKEL.NEGATIVLISTE,"\
         "ZARTIKEL.SICHTWAHL,"\
         "ZARTIKEL.RETOURENSPERRE,"\
         "ZARTIKEL.ZENTR_EKSPERRE,"\
         "ZARTIKEL.ARTIKEL_GELOESCHT,"\
         "ZARTIKEL.SOMMER_KK,"\
         "ZARTIKEL.PRODUKTART,"\
         "ZARTIKEL.KATALOG,"\
         "ZARTIKEL.ZUZAHLUNG_IFA,"\
         "ZARTIKEL.ARTIKEL_GESPERRT,"\
         "ZARTIKEL.TAXPFL,"\
         "ZARTIKEL.REZEPTPFL,"\
         "ZARTIKEL.APOTHEKENPFL,"\
         "ZARTIKEL.BTM,"\
         "ZARTIKEL.TIERARZNEI,"\
         "ZARTIKEL.VERTRBIND,"\
         "ZARTIKEL.VERTRBIND_IFA,"\
         "ZARTIKEL.NETTOARTIKEL,"\
         "ZARTIKEL.NICHTUEBERGH,"\
         "ZARTIKEL.KLINIKPACKUNG,"\
         "ZARTIKEL.KUEHLARTIKEL,"\
         "ZARTIKEL.VERFALL,"\
         "ZARTIKEL.NURKVA,"\
         "ZARTIKEL.PRISMAEDISK,"\
         "ZARTIKEL.PRISMAEWOCHE,"\
         "ZARTIKEL.GS_EXPLOSION,"\
         "ZARTIKEL.GS_BRAND,"\
         "ZARTIKEL.GS_LEICHTENTZ,"\
         "ZARTIKEL.GS_HOCHENTZ,"\
         "ZARTIKEL.GS_GIFTIG,"\
         "ZARTIKEL.GS_SEHRGIFTIG,"\
         "ZARTIKEL.GS_GESUNDHSCH,"\
         "ZARTIKEL.GS_REIZEND,"\
         "ZARTIKEL.GS_AETZEND,"\
         "ZARTIKEL.GS_UMWELT,"\
         "ZARTIKEL.GS_VORSLAGERN,"\
         "ZARTIKEL.GS_SVORSLAGERN,"\
         "ZARTIKEL.AWL_AKTIV,"\
         "ZARTIKEL.AWL1,"\
         "ZARTIKEL.AWL2,"\
         "ZARTIKEL.SORTIMENT_1,"\
         "ZARTIKEL.SORTIMENT_2,"\
         "ZARTIKEL.SORTIMENT_3,"\
         "ZARTIKEL.SORTIMENT_4,"\
         "ZARTIKEL.SORTIMENT_5,"\
         "ZARTIKEL.MINDESTBEZUG,"\
         "ZARTIKEL.VPE_PHARMOS,"\
         "ZARTIKEL.ZYTOSTATIKA,"\
         "ZARTIKEL.HERST_PROZENT,"\
         "ZARTIKEL.ARTIKEL_NR_HERST,"\
         "ZARTIKEL.BESTELLSPERRE,"\
         "ZARTIKEL.TFG,"\
         "ZARTIKEL.PERF,"\
         "ZARTIKEL.NAHRUNGSTEST,"\
         "ZARTIKEL.NAHRUNGSERGAENZUNG,"\
         "ZARTIKEL.BSSICHG,"\
         "ZARTIKEL.ZENTRALPPELIST,"\
         "ZARTIKEL.ARZNEIMITTEL,"\
         "ZARTIKEL.EKORIGINALHS"

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DEZAPZARTIKEL *************************************/

 struct S_DEZAPZARTIKEL {
         char ARTIKEL_NR[11];
         char ARTIKEL_MC[12 + 1];
         char ARTIKEL_NAME[30 + 1];
         char EINHEIT[9 + 1];
         char DARREICHFORM[3 + 1];
         char ERSATZ_NR_AKTIV[1 + 1];
         char ERSATZ_NR[11];
         char HERSTELLER_NR[11];
         char LAENGE[11];
         char HOEHE[11];
         char BREITE[11];
         char GEWICHT[11];
         char LAUFZEITMONATE[11];
         char RABATTFAEHIG[2 + 1];
         char PRIVATSORTIMENT[1 + 1];
         char DATUM_IFAAENDER[11];
         char DATUM_AH[11];
         char DATUM_RR[11];
         char DATUM_IFALOESCH[11];
         char FESTBETRAG1[9 + 2];
         char PERSONALRABATT[5 + 2];
         char FESTBREGEL[3 + 1];
         char WIRKSTOFF_NR[3 + 1];
         char SONDERGROSSO[1 + 1];
         char BESTANDSBUCHUNG[1 + 1];
         char SKONTOFAEHIG[1 + 1];
         char PREIS0ARTIKEL[1 + 1];
         char MELDEPFL[1 + 1];
         char NEGATIVLISTE[1 + 1];
         char SICHTWAHL[1 + 1];
         char RETOURENSPERRE[1 + 1];
         char ZENTR_EKSPERRE[1 + 1];
         char ARTIKEL_GELOESCHT[1 + 1];
         char SOMMER_KK[1 + 1];
         char PRODUKTART[1 + 1];
         char KATALOG[1 + 1];
         char ZUZAHLUNG_IFA[7 + 1];
         char ARTIKEL_GESPERRT[1 + 1];
         char TAXPFL[1 + 1];
         char REZEPTPFL[1 + 1];
         char APOTHEKENPFL[1 + 1];
         char BTM[1 + 1];
         char TIERARZNEI[1 + 1];
         char VERTRBIND[1 + 1];
         char VERTRBIND_IFA[1 + 1];
         char NETTOARTIKEL[1 + 1];
         char NICHTUEBERGH[1 + 1];
         char KLINIKPACKUNG[1 + 1];
         char KUEHLARTIKEL[1 + 1];
         char VERFALL[1 + 1];
         char NURKVA[1 + 1];
         char PRISMAEDISK[1 + 1];
         char PRISMAEWOCHE[11];
         char GS_EXPLOSION[1 + 1];
         char GS_BRAND[1 + 1];
         char GS_LEICHTENTZ[1 + 1];
         char GS_HOCHENTZ[1 + 1];
         char GS_GIFTIG[1 + 1];
         char GS_SEHRGIFTIG[1 + 1];
         char GS_GESUNDHSCH[1 + 1];
         char GS_REIZEND[1 + 1];
         char GS_AETZEND[1 + 1];
         char GS_UMWELT[1 + 1];
         char GS_VORSLAGERN[1 + 1];
         char GS_SVORSLAGERN[1 + 1];
         char AWL_AKTIV[1 + 1];
         char AWL1[11];
         char AWL2[11];
         char SORTIMENT_1[1 + 1];
         char SORTIMENT_2[1 + 1];
         char SORTIMENT_3[1 + 1];
         char SORTIMENT_4[1 + 1];
         char SORTIMENT_5[1 + 1];
         char MINDESTBEZUG[11];
         char VPE_PHARMOS[11];
         char ZYTOSTATIKA[1 + 1];
         char HERST_PROZENT[5 + 2];
         char ARTIKEL_NR_HERST[15 + 1];
         char BESTELLSPERRE[1 + 1];
         char TFG[1 + 1];
         char PERF[1 + 1];
         char NAHRUNGSTEST[1 + 1];
         char NAHRUNGSERGAENZUNG[1 + 1];
         char BSSICHG[1 + 1];
         char ZENTRALPPELIST[1 + 1];
         char ARZNEIMITTEL[1 + 1];
         char EKORIGINALHS[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#endif

