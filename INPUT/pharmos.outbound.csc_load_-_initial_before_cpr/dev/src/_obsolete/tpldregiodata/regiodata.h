#ifndef __PP_REGIODATA_H_
#define __PP_REGIODATA_H_

/******************************************************************************/
/* c:\prj\df\unix\tpulregiodata\regiodata *************************************/
/******************************************************************************/

/* Length-Define of REGIODATA *************************************************/

  #define L_REGIODATA_ARTIKEL_NR 11
  #define L_REGIODATA_BESLA_NR 11
  #define L_REGIODATA_DATUM_AKTIV 11
  #define L_REGIODATA_DATUM_PASSIV 11
  #define L_REGIODATA_DATUM_LIEFERBAR 11
  #define L_REGIODATA_DATUM_N_LIEFERBAR 11
  #define L_REGIODATA_BESTAND 11
  #define L_REGIODATA_NATRASTAFFELNR 11
  #define L_REGIODATA_LAGERBEREICHNR 6
  #define L_REGIODATA_STATIONNR 2
  #define L_REGIODATA_LAGERFACHNR 10
  #define L_REGIODATA_WOCHENNACHFRAGE 11
  #define L_REGIODATA_UMSATZ_LFD_JAHR 11
  #define L_REGIODATA_DURCHSCHNITTPREIS 9
  #define N_REGIODATA_DURCHSCHNITTPREIS 2
  #define L_REGIODATA_UMSATZ_LFD_MONAT 11
  #define L_REGIODATA_AUTOM_NR 9
  #define L_REGIODATA_ARTIKELAKTIV 1
  #define L_REGIODATA_KLASSE_FAKTOR 11
  #define L_REGIODATA_KLASSE_PARAM 11
  #define L_REGIODATA_BARRABATT 5
  #define N_REGIODATA_BARRABATT 2

 #define REGIODATA_PLISTE \
         "ARTIKEL.ARTIKEL_NR,"\
         "ARTFIL.BESLA_NR,"\
         "ARTFIL.DATUM_AKTIV,"\
         "ARTFIL.DATUM_PASSIV,"\
         "ARTFIL.DATUM_LIEFERBAR,"\
         "ARTFIL.DATUM_N_LIEFERBAR,"\
         "ARTIKEL.BESTAND,"\
         "ARTIKEL.NATRASTAFFELNR,"\
         "ARTIKEL.LAGERBEREICHNR,"\
         "ARTIKEL.STATIONNR,"\
         "ARTIKEL.LAGERFACHNR,"\
         "ARTFIL.WOCHENNACHFRAGE,"\
         "ARTFIL.UMSATZ_LFD_JAHR,"\
         "ARTIKEL.DURCHSCHNITTPREIS,"\
         "ARTFIL.UMSATZ_LFD_MONAT,"\
         "ARTFIL.AUTOM_NR,"\
         "ARTFIL.ARTIKELAKTIV,"\
         "ARTFIL.KLASSE_FAKTOR,"\
         "ARTFIL.KLASSE_PARAM,"\
         "ARTFIL.BARRABATT,"\
   	   "T_OFFBES.OBM_MENGE"

 #define ARTIKELF_PLISTE \
         "ARTIKELF.FILIALNR,"\
         "ARTIKELF.ARTIKEL_NR,"\
         "ARTIKELF.BESLA_NR,"\
         "ARTIKELF.DATUM_AKTIV,"\
         "ARTIKELF.DATUM_PASSIV,"\
         "ARTIKELF.DATUM_LIEFERBAR,"\
         "ARTIKELF.DATUM_N_LIEFERBAR,"\
         "ARTIKELF.BESTAND,"\
         "ARTIKELF.NATRASTAFFELNR,"\
         "ARTIKELF.LAGERBEREICHNR,"\
         "ARTIKELF.STATIONNR,"\
         "ARTIKELF.LAGERFACHNR,"\
         "ARTIKELF.WOCHENNACHFRAGE,"\
         "ARTIKELF.UMSATZ_LFD_JAHR,"\
         "ARTIKELF.DURCHSCHNITTPREIS,"\
         "ARTIKELF.UMSATZ_LFD_MONAT,"\
         "ARTIKELF.AUTOM_NR,"\
         "ARTIKELF.ARTIKELAKTIV,"\
         "ARTIKELF.BARRABATT,"\
         "ARTIKELF.OFFENE_BESTMENGE,"\
         "ARTIKELF.MENGE_AUSTAUSCHBAR,"\
         "ARTIKELF.INTERNESTEUERUNG"
 
 /* it' s a must that :x->OBM_MENGE	is on the end of the define! */ 
 #define REGIODATA_ZEIGER(x) \
         :x->ARTIKEL_NR,\
         :x->BESLA_NR,\
         :x->DATUM_AKTIV,\
         :x->DATUM_PASSIV,\
         :x->DATUM_LIEFERBAR,\
         :x->DATUM_N_LIEFERBAR,\
         :x->BESTAND,\
         :x->NATRASTAFFELNR,\
         :x->LAGERBEREICHNR,\
         :x->STATIONNR,\
         :x->LAGERFACHNR,\
         :x->WOCHENNACHFRAGE,\
         :x->UMSATZ_LFD_JAHR,\
         :x->DURCHSCHNITTPREIS,\
         :x->UMSATZ_LFD_MONAT,\
         :x->AUTOM_NR,\
         :x->ARTIKELAKTIV,\
         :x->KLASSE_FAKTOR,\
         :x->KLASSE_PARAM,\
         :x->BARRABATT,\
         :x->OBM_MENGE


 #define ARTIKELF_UPDLISTE \
         "FILIALNR=?,"\
         "ARTIKEL_NR=?,"\
         "DATUM_AKTIV=?,"\
         "DATUM_PASSIV=?,"\
         "DATUM_LIEFERBAR=?,"\
         "DATUM_N_LIEFERBAR=?,"\
         "BESTAND=?,"\
         "NATRASTAFFELNR=?,"\
         "LAGERBEREICHNR=?,"\
         "STATIONNR=?,"\
         "LAGERFACHNR=?,"\
         "UMSATZ_LFD_JAHR=?,"\
         "DURCHSCHNITTPREIS=?,"\
         "UMSATZ_LFD_MONAT=?,"\
         "AUTOM_NR=?,"\
         "ARTIKELAKTIV=?,"\
         "BARRABATT=?,"\
         "OFFENE_BESTMENGE=?,"\
         "MENGE_AUSTAUSCHBAR=?,"\
         "INTERNESTEUERUNG=?"

 #define ARTIKELF_ZEIGER_UPD(x) \
         :x->sBranchNo,\
         :x->ARTIKEL_NR,\
         :x->DATUM_AKTIV,\
         :x->DATUM_PASSIV,\
         :x->DATUM_LIEFERBAR,\
         :x->DATUM_N_LIEFERBAR,\
         :x->BESTAND,\
         :x->NATRASTAFFELNR,\
         :x->LAGERBEREICHNR,\
         :x->STATIONNR,\
         :x->LAGERFACHNR,\
         :x->UMSATZ_LFD_JAHR,\
         :x->DURCHSCHNITTPREIS,\
         :x->UMSATZ_LFD_MONAT,\
         :x->AUTOM_NR,\
         :x->ARTIKELAKTIV,\
         :x->BARRABATT,\
         :x->OBM_MENGE,\
         :x->BESTAND

 #define ARTIKELF_ZEIGER(x) \
         :x->sBranchNo,\
         :x->ARTIKEL_NR,\
         :x->BESLA_NR,\
         :x->DATUM_AKTIV,\
         :x->DATUM_PASSIV,\
         :x->DATUM_LIEFERBAR,\
         :x->DATUM_N_LIEFERBAR,\
         :x->BESTAND,\
         :x->NATRASTAFFELNR,\
         :x->LAGERBEREICHNR,\
         :x->STATIONNR,\
         :x->LAGERFACHNR,\
         :x->WOCHENNACHFRAGE,\
         :x->UMSATZ_LFD_JAHR,\
         :x->DURCHSCHNITTPREIS,\
         :x->UMSATZ_LFD_MONAT,\
         :x->AUTOM_NR,\
         :x->ARTIKELAKTIV,\
         :x->BARRABATT,\
         :x->OBM_MENGE,\
         :x->BESTAND
         
 #define ARTIKELF_UPDATE(x) \
         ARTIKELF.FILIALNR=:x->sBranchNo,\
         ARTIKELF.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ARTIKELF.DATUM_AKTIV=:x->DATUM_AKTIV,\
         ARTIKELF.DATUM_PASSIV=:x->DATUM_PASSIV,\
         ARTIKELF.DATUM_LIEFERBAR=:x->DATUM_LIEFERBAR,\
         ARTIKELF.DATUM_N_LIEFERBAR=:x->DATUM_N_LIEFERBAR,\
         ARTIKELF.BESTAND=:x->BESTAND,\
         ARTIKELF.NATRASTAFFELNR=:x->NATRASTAFFELNR,\
         ARTIKELF.LAGERBEREICHNR=:x->LAGERBEREICHNR,\
         ARTIKELF.STATIONNR=:x->STATIONNR,\
         ARTIKELF.LAGERFACHNR=:x->LAGERFACHNR,\
         ARTIKELF.WOCHENNACHFRAGE=:x->WOCHENNACHFRAGE,\
         ARTIKELF.UMSATZ_LFD_JAHR=:x->UMSATZ_LFD_JAHR,\
         ARTIKELF.DURCHSCHNITTPREIS=:x->DURCHSCHNITTPREIS,\
         ARTIKELF.UMSATZ_LFD_MONAT=:x->UMSATZ_LFD_MONAT,\
         ARTIKELF.AUTOM_NR=:x->AUTOM_NR,\
         ARTIKELF.ARTIKELAKTIV=:x->ARTIKELAKTIV,\
         ARTIKELF.KLASSE_FAKTOR=:x->KLASSE_FAKTOR,\
         ARTIKELF.KLASSE_PARAM=:x->KLASSE_PARAM,\
         ARTIKELF.BARRABATT=:x->BARRABATT,\
         ARTIKELF.OFFENE_BESTMENGE=:x->OBM_MENG,\
         ARTIKELF.MENGE_AUSTAUSCHBAR=:x->BESTAND
      	 
#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of REGIODATA **********************************************/

 typedef struct {
         short  sBranchNo; 
         long ARTIKEL_NR;
         long BESLA_NR;
         long DATUM_AKTIV;
         long DATUM_PASSIV;
         long DATUM_LIEFERBAR;
         long DATUM_N_LIEFERBAR;
         long BESTAND;
         long NATRASTAFFELNR;
         short LAGERBEREICHNR;
         char STATIONNR[3];
         char LAGERFACHNR[11];
         long WOCHENNACHFRAGE;
         long UMSATZ_LFD_JAHR;
         double DURCHSCHNITTPREIS;
         long UMSATZ_LFD_MONAT;
         char AUTOM_NR[10];
         char ARTIKELAKTIV[2];
         long KLASSE_FAKTOR;
         long KLASSE_PARAM;
         double BARRABATT;
         long OBM_MENGE;
         } regiodataS;

 typedef struct {
         long lArticleNo;
         long lOpenAmount;
 } toffbesS;

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* eigene Strucuren of REGIODATA **********************************************/

 typedef struct {
	    long  lDate;
		 short sBranchNo;
		 char  *spDatabase;
		 char  *spLogFile;
		 char  *spFile;
		 char  *spRemoteSystem;
		 char  *spRemoteDir;
 } tInit; /* init values */
#endif












