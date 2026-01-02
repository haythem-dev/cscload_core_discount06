/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_KUNDE_IDFNR                11
 #define L_KUNDE_MATCHCODE            12
 #define L_KUNDE_FILIALNR             6
 #define L_KUNDE_KDNR                 11
 #define L_KUNDE_ETARTKLASSE1         5
 #define L_KUNDE_ETARTKLASSE2         5
 #define L_KUNDE_ETKDMERKMAL1         5
 #define L_KUNDE_ETKDMERKMAL2         5
 #define L_KUNDE_ANREDEKZ             6
 #define L_KUNDE_NAMEAPO              40
 #define L_KUNDE_NAMEINHABER          30
 #define L_KUNDE_STRASSE              40
 #define L_KUNDE_ORT                  30
 #define L_KUNDE_POSTLEITZAHL         7
 #define L_KUNDE_TELNR                20
 #define L_KUNDE_TELNRDAFUE           20
 #define L_KUNDE_FAXNR                20
 #define L_KUNDE_TELKURZWAHL          4
 #define L_KUNDE_IMSBEZIRKNR          11
 #define L_KUNDE_KDGRUPPE             2
 #define L_KUNDE_PERSONALNRVERTR      11
 #define L_KUNDE_DAFUESYSTEM          2
 #define L_KUNDE_KZKDDOPPELKONTR      1
 #define L_KUNDE_LAGERFACHNRRGBEI     4
 #define L_KUNDE_ANZPOSLS_RG          6
 #define L_KUNDE_ANZPOSSORTBEHAELT    6
 #define L_KUNDE_KZKDKLASSE           3
 #define L_KUNDE_ORIGINALFILIALNR     6
 #define L_KUNDE_NOTFILIALNR          6
 #define L_KUNDE_BEMERKUNGEN          240
 #define L_KUNDE_KUNDETEXT            240
 #define L_KUNDE_VERBUNDKUNDE         1
 #define L_KUNDE_STDAUFKOBUART        4
 #define L_KUNDE_PASSWORD             8
 #define L_KUNDE_VZKK1                1
 #define L_KUNDE_KUEHLBOX             1
 #define L_KUNDE_TOURENKIPPZEIT       11
 #define L_KUNDE_KZUPD                1
 #define L_KUNDE_IMS3000              11
 #define L_KUNDE_LAND                 3
 #define L_KUNDE_DRUCKREIMPORTLISTE   1
 #define L_KUNDE_PRISMADISKETTE       1
 #define L_KUNDE_AZYXKREISNR          10
 #define L_KUNDE_PHARMAKREISNR        11
 #define L_KUNDE_UMSATZSTEUERID       15
 #define L_KUNDE_IMSAPONR             8
 #define L_KUNDE_IMSKUNDENART         1
 #define L_KUNDE_VERTRIEBSZENTRUMNR   6
 #define L_KUNDE_KUNDENNR             11
 #define L_KUNDE_BUNDESLAND           6
 #define L_KUNDE_TM_DATE              11
 #define L_KUNDE_TM_TIME              11
 #define L_KUNDE_LOGINID              11
 #define L_KUNDE_CHANGEID             1


 #define L_KUNDE_PKEY 11

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define KUNDE_ANZ ( sizeof(KUNDE_BES) / sizeof(struct buf_desc) )
#endif
 #define G_KUNDE sizeof(struct KUNDE)


 #define KUNDE_H

 #define KUNDE_LISTE \
 			KUNDE.IDFNR, \
 			KUNDE.MATCHCODE, \
 			KUNDE.FILIALNR, \
 			KUNDE.KDNR, \
 			KUNDE.ETARTKLASSE1, \
 			KUNDE.ETARTKLASSE2, \
 			KUNDE.ETKDMERKMAL1, \
 			KUNDE.ETKDMERKMAL2, \
 			KUNDE.ANREDEKZ, \
 			KUNDE.NAMEAPO, \
 			KUNDE.NAMEINHABER, \
 			KUNDE.STRASSE, \
 			KUNDE.ORT, \
 			KUNDE.POSTLEITZAHL, \
 			KUNDE.TELNR, \
 			KUNDE.TELNRDAFUE, \
 			KUNDE.FAXNR, \
 			KUNDE.TELKURZWAHL, \
 			KUNDE.IMSBEZIRKNR, \
 			KUNDE.KDGRUPPE, \
 			KUNDE.PERSONALNRVERTR, \
 			KUNDE.DAFUESYSTEM, \
 			KUNDE.KZKDDOPPELKONTR, \
 			KUNDE.LAGERFACHNRRGBEI, \
 			KUNDE.ANZPOSLS_RG, \
 			KUNDE.ANZPOSSORTBEHAELT, \
 			KUNDE.KZKDKLASSE, \
 			KUNDE.ORIGINALFILIALNR, \
 			KUNDE.NOTFILIALNR, \
 			KUNDE.BEMERKUNGEN, \
 			KUNDE.KUNDETEXT, \
 			KUNDE.VERBUNDKUNDE, \
 			KUNDE.STDAUFKOBUART, \
 			KUNDE.PASSWORD, \
 			KUNDE.VZKK1, \
 			KUNDE.KUEHLBOX, \
 			KUNDE.TOURENKIPPZEIT, \
 			KUNDE.KZUPD, \
 			KUNDE.IMS3000, \
 			KUNDE.LAND, \
 			KUNDE.DRUCKREIMPORTLISTE, \
 			KUNDE.PRISMADISKETTE, \
 			KUNDE.AZYXKREISNR, \
 			KUNDE.PHARMAKREISNR, \
 			KUNDE.UMSATZSTEUERID, \
 			KUNDE.IMSAPONR, \
 			KUNDE.IMSKUNDENART, \
 			KUNDE.VERTRIEBSZENTRUMNR, \
 			KUNDE.KUNDENNR, \
 			KUNDE.BUNDESLAND, \
 			KUNDE.TM_DATE, \
 			KUNDE.TM_TIME, \
 			KUNDE.LOGINID, \
 			KUNDE.CHANGEID
 #define KUNDE_PLISTE \
 			"KUNDE.IDFNR," \
 			"KUNDE.MATCHCODE," \
 			"KUNDE.FILIALNR," \
 			"KUNDE.KDNR," \
 			"KUNDE.ETARTKLASSE1," \
 			"KUNDE.ETARTKLASSE2," \
 			"KUNDE.ETKDMERKMAL1," \
 			"KUNDE.ETKDMERKMAL2," \
 			"KUNDE.ANREDEKZ," \
 			"KUNDE.NAMEAPO," \
 			"KUNDE.NAMEINHABER," \
 			"KUNDE.STRASSE," \
 			"KUNDE.ORT," \
 			"KUNDE.POSTLEITZAHL," \
 			"KUNDE.TELNR," \
 			"KUNDE.TELNRDAFUE," \
 			"KUNDE.FAXNR," \
 			"KUNDE.TELKURZWAHL," \
 			"KUNDE.IMSBEZIRKNR," \
 			"KUNDE.KDGRUPPE," \
 			"KUNDE.PERSONALNRVERTR," \
 			"KUNDE.DAFUESYSTEM," \
 			"KUNDE.KZKDDOPPELKONTR," \
 			"KUNDE.LAGERFACHNRRGBEI," \
 			"KUNDE.ANZPOSLS_RG," \
 			"KUNDE.ANZPOSSORTBEHAELT," \
 			"KUNDE.KZKDKLASSE," \
 			"KUNDE.ORIGINALFILIALNR," \
 			"KUNDE.NOTFILIALNR," \
 			"KUNDE.BEMERKUNGEN," \
 			"KUNDE.KUNDETEXT," \
 			"KUNDE.VERBUNDKUNDE," \
 			"KUNDE.STDAUFKOBUART," \
 			"KUNDE.PASSWORD," \
 			"KUNDE.VZKK1," \
 			"KUNDE.KUEHLBOX," \
 			"KUNDE.TOURENKIPPZEIT," \
 			"KUNDE.KZUPD," \
 			"KUNDE.IMS3000," \
 			"KUNDE.LAND," \
 			"KUNDE.DRUCKREIMPORTLISTE," \
 			"KUNDE.PRISMADISKETTE," \
 			"KUNDE.AZYXKREISNR," \
 			"KUNDE.PHARMAKREISNR," \
 			"KUNDE.UMSATZSTEUERID," \
 			"KUNDE.IMSAPONR," \
 			"KUNDE.IMSKUNDENART," \
 			"KUNDE.VERTRIEBSZENTRUMNR," \
 			"KUNDE.KUNDENNR," \
 			"KUNDE.BUNDESLAND," \
 			"KUNDE.TM_DATE," \
 			"KUNDE.TM_TIME," \
 			"KUNDE.LOGINID," \
 			"KUNDE.CHANGEID " 

 #define KUNDE_PELISTE \
 			"IDFNR," \
 			"MATCHCODE," \
 			"FILIALNR," \
 			"KDNR," \
 			"ETARTKLASSE1," \
 			"ETARTKLASSE2," \
 			"ETKDMERKMAL1," \
 			"ETKDMERKMAL2," \
 			"ANREDEKZ," \
 			"NAMEAPO," \
 			"NAMEINHABER," \
 			"STRASSE," \
 			"ORT," \
 			"POSTLEITZAHL," \
 			"TELNR," \
 			"TELNRDAFUE," \
 			"FAXNR," \
 			"TELKURZWAHL," \
 			"IMSBEZIRKNR," \
 			"KDGRUPPE," \
 			"PERSONALNRVERTR," \
 			"DAFUESYSTEM," \
 			"KZKDDOPPELKONTR," \
 			"LAGERFACHNRRGBEI," \
 			"ANZPOSLS_RG," \
 			"ANZPOSSORTBEHAELT," \
 			"KZKDKLASSE," \
 			"ORIGINALFILIALNR," \
 			"NOTFILIALNR," \
 			"BEMERKUNGEN," \
 			"KUNDETEXT," \
 			"VERBUNDKUNDE," \
 			"STDAUFKOBUART," \
 			"PASSWORD," \
 			"VZKK1," \
 			"KUEHLBOX," \
 			"TOURENKIPPZEIT," \
 			"KZUPD," \
 			"IMS3000," \
 			"LAND," \
 			"DRUCKREIMPORTLISTE," \
 			"PRISMADISKETTE," \
 			"AZYXKREISNR," \
 			"PHARMAKREISNR," \
 			"UMSATZSTEUERID," \
 			"IMSAPONR," \
 			"IMSKUNDENART," \
 			"VERTRIEBSZENTRUMNR," \
 			"KUNDENNR," \
 			"BUNDESLAND," \
 			"TM_DATE," \
 			"TM_TIME," \
 			"LOGINID," \
 			"CHANGEID " 

 #define KUNDE_UPDLISTE \
 			"IDFNR=?," \
 			"MATCHCODE=?," \
 			"FILIALNR=?," \
 			"KDNR=?," \
 			"ETARTKLASSE1=?," \
 			"ETARTKLASSE2=?," \
 			"ETKDMERKMAL1=?," \
 			"ETKDMERKMAL2=?," \
 			"ANREDEKZ=?," \
 			"NAMEAPO=?," \
 			"NAMEINHABER=?," \
 			"STRASSE=?," \
 			"ORT=?," \
 			"POSTLEITZAHL=?," \
 			"TELNR=?," \
 			"TELNRDAFUE=?," \
 			"FAXNR=?," \
 			"TELKURZWAHL=?," \
 			"IMSBEZIRKNR=?," \
 			"KDGRUPPE=?," \
 			"PERSONALNRVERTR=?," \
 			"DAFUESYSTEM=?," \
 			"KZKDDOPPELKONTR=?," \
 			"LAGERFACHNRRGBEI=?," \
 			"ANZPOSLS_RG=?," \
 			"ANZPOSSORTBEHAELT=?," \
 			"KZKDKLASSE=?," \
 			"ORIGINALFILIALNR=?," \
 			"NOTFILIALNR=?," \
 			"BEMERKUNGEN=?," \
 			"KUNDETEXT=?," \
 			"VERBUNDKUNDE=?," \
 			"STDAUFKOBUART=?," \
 			"PASSWORD=?," \
 			"VZKK1=?," \
 			"KUEHLBOX=?," \
 			"TOURENKIPPZEIT=?," \
 			"KZUPD=?," \
 			"IMS3000=?," \
 			"LAND=?," \
 			"DRUCKREIMPORTLISTE=?," \
 			"PRISMADISKETTE=?," \
 			"AZYXKREISNR=?," \
 			"PHARMAKREISNR=?," \
 			"UMSATZSTEUERID=?," \
 			"IMSAPONR=?," \
 			"IMSKUNDENART=?," \
 			"VERTRIEBSZENTRUMNR=?," \
 			"KUNDENNR=?," \
 			"BUNDESLAND=?," \
 			"TM_DATE=?," \
 			"TM_TIME=?," \
 			"LOGINID=?," \
 			"CHANGEID=? " 

 #define KUNDEIDFNR                         0
 #define KUNDEMATCHCODE                     1
 #define KUNDEFILIALNR                      2
 #define KUNDEKDNR                          3
 #define KUNDEETARTKLASSE1                  4
 #define KUNDEETARTKLASSE2                  5
 #define KUNDEETKDMERKMAL1                  6
 #define KUNDEETKDMERKMAL2                  7
 #define KUNDEANREDEKZ                      8
 #define KUNDENAMEAPO                       9
 #define KUNDENAMEINHABER                   10
 #define KUNDESTRASSE                       11
 #define KUNDEORT                           12
 #define KUNDEPOSTLEITZAHL                  13
 #define KUNDETELNR                         14
 #define KUNDETELNRDAFUE                    15
 #define KUNDEFAXNR                         16
 #define KUNDETELKURZWAHL                   17
 #define KUNDEIMSBEZIRKNR                   18
 #define KUNDEKDGRUPPE                      19
 #define KUNDEPERSONALNRVERTR               20
 #define KUNDEDAFUESYSTEM                   21
 #define KUNDEKZKDDOPPELKONTR               22
 #define KUNDELAGERFACHNRRGBEI              23
 #define KUNDEANZPOSLS_RG                   24
 #define KUNDEANZPOSSORTBEHAELT             25
 #define KUNDEKZKDKLASSE                    26
 #define KUNDEORIGINALFILIALNR              27
 #define KUNDENOTFILIALNR                   28
 #define KUNDEBEMERKUNGEN                   29
 #define KUNDEKUNDETEXT                     30
 #define KUNDEVERBUNDKUNDE                  31
 #define KUNDESTDAUFKOBUART                 32
 #define KUNDEPASSWORD                      33
 #define KUNDEVZKK1                         34
 #define KUNDEKUEHLBOX                      35
 #define KUNDETOURENKIPPZEIT                36
 #define KUNDEKZUPD                         37
 #define KUNDEIMS3000                       38
 #define KUNDELAND                          39
 #define KUNDEDRUCKREIMPORTLISTE            40
 #define KUNDEPRISMADISKETTE                41
 #define KUNDEAZYXKREISNR                   42
 #define KUNDEPHARMAKREISNR                 43
 #define KUNDEUMSATZSTEUERID                44
 #define KUNDEIMSAPONR                      45
 #define KUNDEIMSKUNDENART                  46
 #define KUNDEVERTRIEBSZENTRUMNR            47
 #define KUNDEKUNDENNR                      48
 #define KUNDEBUNDESLAND                    49
 #define KUNDETM_DATE                       50
 #define KUNDETM_TIME                       51
 #define KUNDELOGINID                       52
 #define KUNDECHANGEID                      53

 #define KUNDE_ZEIGER(xxx) \
 			:xxx->IDFNR,\
 			:xxx->MATCHCODE,\
 			:xxx->FILIALNR,\
 			:xxx->KDNR,\
 			:xxx->ETARTKLASSE1,\
 			:xxx->ETARTKLASSE2,\
 			:xxx->ETKDMERKMAL1,\
 			:xxx->ETKDMERKMAL2,\
 			:xxx->ANREDEKZ,\
 			:xxx->NAMEAPO,\
 			:xxx->NAMEINHABER,\
 			:xxx->STRASSE,\
 			:xxx->ORT,\
 			:xxx->POSTLEITZAHL,\
 			:xxx->TELNR,\
 			:xxx->TELNRDAFUE,\
 			:xxx->FAXNR,\
 			:xxx->TELKURZWAHL,\
 			:xxx->IMSBEZIRKNR,\
 			:xxx->KDGRUPPE,\
 			:xxx->PERSONALNRVERTR,\
 			:xxx->DAFUESYSTEM,\
 			:xxx->KZKDDOPPELKONTR,\
 			:xxx->LAGERFACHNRRGBEI,\
 			:xxx->ANZPOSLS_RG,\
 			:xxx->ANZPOSSORTBEHAELT,\
 			:xxx->KZKDKLASSE,\
 			:xxx->ORIGINALFILIALNR,\
 			:xxx->NOTFILIALNR,\
 			:xxx->BEMERKUNGEN,\
 			:xxx->KUNDETEXT,\
 			:xxx->VERBUNDKUNDE,\
 			:xxx->STDAUFKOBUART,\
 			:xxx->PASSWORD,\
 			:xxx->VZKK1,\
 			:xxx->KUEHLBOX,\
 			:xxx->TOURENKIPPZEIT,\
 			:xxx->KZUPD,\
 			:xxx->IMS3000,\
 			:xxx->LAND,\
 			:xxx->DRUCKREIMPORTLISTE,\
 			:xxx->PRISMADISKETTE,\
 			:xxx->AZYXKREISNR,\
 			:xxx->PHARMAKREISNR,\
 			:xxx->UMSATZSTEUERID,\
 			:xxx->IMSAPONR,\
 			:xxx->IMSKUNDENART,\
 			:xxx->VERTRIEBSZENTRUMNR,\
 			:xxx->KUNDENNR,\
 			:xxx->BUNDESLAND,\
 			:xxx->TM_DATE,\
 			:xxx->TM_TIME,\
 			:xxx->LOGINID,\
 			:xxx->CHANGEID

 #define KUNDE_UPDATE(xxx) \
 			IDFNR = :xxx->IDFNR,\
 			MATCHCODE = :xxx->MATCHCODE,\
 			FILIALNR = :xxx->FILIALNR,\
 			KDNR = :xxx->KDNR,\
 			ETARTKLASSE1 = :xxx->ETARTKLASSE1,\
 			ETARTKLASSE2 = :xxx->ETARTKLASSE2,\
 			ETKDMERKMAL1 = :xxx->ETKDMERKMAL1,\
 			ETKDMERKMAL2 = :xxx->ETKDMERKMAL2,\
 			ANREDEKZ = :xxx->ANREDEKZ,\
 			NAMEAPO = :xxx->NAMEAPO,\
 			NAMEINHABER = :xxx->NAMEINHABER,\
 			STRASSE = :xxx->STRASSE,\
 			ORT = :xxx->ORT,\
 			POSTLEITZAHL = :xxx->POSTLEITZAHL,\
 			TELNR = :xxx->TELNR,\
 			TELNRDAFUE = :xxx->TELNRDAFUE,\
 			FAXNR = :xxx->FAXNR,\
 			TELKURZWAHL = :xxx->TELKURZWAHL,\
 			IMSBEZIRKNR = :xxx->IMSBEZIRKNR,\
 			KDGRUPPE = :xxx->KDGRUPPE,\
 			PERSONALNRVERTR = :xxx->PERSONALNRVERTR,\
 			DAFUESYSTEM = :xxx->DAFUESYSTEM,\
 			KZKDDOPPELKONTR = :xxx->KZKDDOPPELKONTR,\
 			LAGERFACHNRRGBEI = :xxx->LAGERFACHNRRGBEI,\
 			ANZPOSLS_RG = :xxx->ANZPOSLS_RG,\
 			ANZPOSSORTBEHAELT = :xxx->ANZPOSSORTBEHAELT,\
 			KZKDKLASSE = :xxx->KZKDKLASSE,\
 			ORIGINALFILIALNR = :xxx->ORIGINALFILIALNR,\
 			NOTFILIALNR = :xxx->NOTFILIALNR,\
 			BEMERKUNGEN = :xxx->BEMERKUNGEN,\
 			KUNDETEXT = :xxx->KUNDETEXT,\
 			VERBUNDKUNDE = :xxx->VERBUNDKUNDE,\
 			STDAUFKOBUART = :xxx->STDAUFKOBUART,\
 			PASSWORD = :xxx->PASSWORD,\
 			VZKK1 = :xxx->VZKK1,\
 			KUEHLBOX = :xxx->KUEHLBOX,\
 			TOURENKIPPZEIT = :xxx->TOURENKIPPZEIT,\
 			KZUPD = :xxx->KZUPD,\
 			IMS3000 = :xxx->IMS3000,\
 			LAND = :xxx->LAND,\
 			DRUCKREIMPORTLISTE = :xxx->DRUCKREIMPORTLISTE,\
 			PRISMADISKETTE = :xxx->PRISMADISKETTE,\
 			AZYXKREISNR = :xxx->AZYXKREISNR,\
 			PHARMAKREISNR = :xxx->PHARMAKREISNR,\
 			UMSATZSTEUERID = :xxx->UMSATZSTEUERID,\
 			IMSAPONR = :xxx->IMSAPONR,\
 			IMSKUNDENART = :xxx->IMSKUNDENART,\
 			VERTRIEBSZENTRUMNR = :xxx->VERTRIEBSZENTRUMNR,\
 			KUNDENNR = :xxx->KUNDENNR,\
 			BUNDESLAND = :xxx->BUNDESLAND,\
 			TM_DATE = :xxx->TM_DATE,\
 			TM_TIME = :xxx->TM_TIME,\
 			LOGINID = :xxx->LOGINID,\
 			CHANGEID = :xxx->CHANGEID

 #define LS_KUNDE_IDFNR                11
 #define LS_KUNDE_MATCHCODE            13
 #define LS_KUNDE_FILIALNR             7
 #define LS_KUNDE_KDNR                 11
 #define LS_KUNDE_ETARTKLASSE1         6
 #define LS_KUNDE_ETARTKLASSE2         6
 #define LS_KUNDE_ETKDMERKMAL1         6
 #define LS_KUNDE_ETKDMERKMAL2         6
 #define LS_KUNDE_ANREDEKZ             7
 #define LS_KUNDE_NAMEAPO              41
 #define LS_KUNDE_NAMEINHABER          31
 #define LS_KUNDE_STRASSE              41
 #define LS_KUNDE_ORT                  31
 #define LS_KUNDE_POSTLEITZAHL         8
 #define LS_KUNDE_TELNR                21
 #define LS_KUNDE_TELNRDAFUE           21
 #define LS_KUNDE_FAXNR                21
 #define LS_KUNDE_TELKURZWAHL          5
 #define LS_KUNDE_IMSBEZIRKNR          11
 #define LS_KUNDE_KDGRUPPE             3
 #define LS_KUNDE_PERSONALNRVERTR      11
 #define LS_KUNDE_DAFUESYSTEM          3
 #define LS_KUNDE_KZKDDOPPELKONTR      2
 #define LS_KUNDE_LAGERFACHNRRGBEI     5
 #define LS_KUNDE_ANZPOSLS_RG          7
 #define LS_KUNDE_ANZPOSSORTBEHAELT    7
 #define LS_KUNDE_KZKDKLASSE           4
 #define LS_KUNDE_ORIGINALFILIALNR     7
 #define LS_KUNDE_NOTFILIALNR          7
 #define LS_KUNDE_BEMERKUNGEN          241
 #define LS_KUNDE_KUNDETEXT            241
 #define LS_KUNDE_VERBUNDKUNDE         2
 #define LS_KUNDE_STDAUFKOBUART        5
 #define LS_KUNDE_PASSWORD             9
 #define LS_KUNDE_VZKK1                2
 #define LS_KUNDE_KUEHLBOX             2
 #define LS_KUNDE_TOURENKIPPZEIT       11
 #define LS_KUNDE_KZUPD                2
 #define LS_KUNDE_IMS3000              11
 #define LS_KUNDE_LAND                 4
 #define LS_KUNDE_DRUCKREIMPORTLISTE   2
 #define LS_KUNDE_PRISMADISKETTE       2
 #define LS_KUNDE_AZYXKREISNR          11
 #define LS_KUNDE_PHARMAKREISNR        11
 #define LS_KUNDE_UMSATZSTEUERID       16
 #define LS_KUNDE_IMSAPONR             9
 #define LS_KUNDE_IMSKUNDENART         2
 #define LS_KUNDE_VERTRIEBSZENTRUMNR   7
 #define LS_KUNDE_KUNDENNR             11
 #define LS_KUNDE_BUNDESLAND           7
 #define LS_KUNDE_TM_DATE              11
 #define LS_KUNDE_TM_TIME              11
 #define LS_KUNDE_LOGINID              11
 #define LS_KUNDE_CHANGEID             2

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct KUNDE {
		 long    IDFNR;
		 char    MATCHCODE[12 + 1];
		 short   FILIALNR;
		 long    KDNR;
		 long    ETARTKLASSE1;
		 long    ETARTKLASSE2;
		 long    ETKDMERKMAL1;
		 long    ETKDMERKMAL2;
		 short   ANREDEKZ;
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELNRDAFUE[20 + 1];
		 char    FAXNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    IMSBEZIRKNR;
		 char    KDGRUPPE[2 + 1];
		 long    PERSONALNRVERTR;
		 char    DAFUESYSTEM[2 + 1];
		 char    KZKDDOPPELKONTR[1 + 1];
		 char    LAGERFACHNRRGBEI[4 + 1];
		 short   ANZPOSLS_RG;
		 short   ANZPOSSORTBEHAELT;
		 char    KZKDKLASSE[3 + 1];
		 short   ORIGINALFILIALNR;
		 short   NOTFILIALNR;
		 char    BEMERKUNGEN[240 + 1];
		 char    KUNDETEXT[240 + 1];
		 char    VERBUNDKUNDE[1 + 1];
		 char    STDAUFKOBUART[4 + 1];
		 char    PASSWORD[8 + 1];
		 char    VZKK1[1 + 1];
		 char    KUEHLBOX[1 + 1];
		 long    TOURENKIPPZEIT;
		 char    KZUPD[1 + 1];
		 long    IMS3000;
		 char    LAND[3 + 1];
		 char    DRUCKREIMPORTLISTE[1 + 1];
		 char    PRISMADISKETTE[1 + 1];
		 double  AZYXKREISNR;
		 long    PHARMAKREISNR;
		 char    UMSATZSTEUERID[15 + 1];
		 char    IMSAPONR[8 + 1];
		 char    IMSKUNDENART[1 + 1];
		 short   VERTRIEBSZENTRUMNR;
		 long    KUNDENNR;
		 char    BUNDESLAND[6 + 1];
		 long    TM_DATE;
		 long    TM_TIME;
		 long    LOGINID;
		 char    CHANGEID[1 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_KUNDE {
		 long    IDFNR;
		 char    MATCHCODE[12 + 1];
		 short   FILIALNR;
		 long    KDNR;
		 long    ETARTKLASSE1;
		 long    ETARTKLASSE2;
		 long    ETKDMERKMAL1;
		 long    ETKDMERKMAL2;
		 short   ANREDEKZ;
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELNRDAFUE[20 + 1];
		 char    FAXNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 long    IMSBEZIRKNR;
		 char    KDGRUPPE[2 + 1];
		 long    PERSONALNRVERTR;
		 char    DAFUESYSTEM[2 + 1];
		 char    KZKDDOPPELKONTR;
		 char    LAGERFACHNRRGBEI[4 + 1];
		 short   ANZPOSLS_RG;
		 short   ANZPOSSORTBEHAELT;
		 char    KZKDKLASSE[3 + 1];
		 short   ORIGINALFILIALNR;
		 short   NOTFILIALNR;
		 char    BEMERKUNGEN[240 + 1];
		 char    KUNDETEXT[240 + 1];
		 char    VERBUNDKUNDE;
		 char    STDAUFKOBUART[4 + 1];
		 char    PASSWORD[8 + 1];
		 char    VZKK1;
		 char    KUEHLBOX;
		 long    TOURENKIPPZEIT;
		 char    KZUPD;
		 long    IMS3000;
		 char    LAND[3 + 1];
		 char    DRUCKREIMPORTLISTE;
		 char    PRISMADISKETTE;
		 double  AZYXKREISNR;
		 long    PHARMAKREISNR;
		 char    UMSATZSTEUERID[15 + 1];
		 char    IMSAPONR[8 + 1];
		 char    IMSKUNDENART;
		 short   VERTRIEBSZENTRUMNR;
		 long    KUNDENNR;
		 char    BUNDESLAND[6 + 1];
		 long    TM_DATE;
		 long    TM_TIME;
		 long    LOGINID;
		 char    CHANGEID;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_KUNDE {
		 short  IDFNR;
		 short  MATCHCODE;
		 short  FILIALNR;
		 short  KDNR;
		 short  ETARTKLASSE1;
		 short  ETARTKLASSE2;
		 short  ETKDMERKMAL1;
		 short  ETKDMERKMAL2;
		 short  ANREDEKZ;
		 short  NAMEAPO;
		 short  NAMEINHABER;
		 short  STRASSE;
		 short  ORT;
		 short  POSTLEITZAHL;
		 short  TELNR;
		 short  TELNRDAFUE;
		 short  FAXNR;
		 short  TELKURZWAHL;
		 short  IMSBEZIRKNR;
		 short  KDGRUPPE;
		 short  PERSONALNRVERTR;
		 short  DAFUESYSTEM;
		 short  KZKDDOPPELKONTR;
		 short  LAGERFACHNRRGBEI;
		 short  ANZPOSLS_RG;
		 short  ANZPOSSORTBEHAELT;
		 short  KZKDKLASSE;
		 short  ORIGINALFILIALNR;
		 short  NOTFILIALNR;
		 short  BEMERKUNGEN;
		 short  KUNDETEXT;
		 short  VERBUNDKUNDE;
		 short  STDAUFKOBUART;
		 short  PASSWORD;
		 short  VZKK1;
		 short  KUEHLBOX;
		 short  TOURENKIPPZEIT;
		 short  KZUPD;
		 short  IMS3000;
		 short  LAND;
		 short  DRUCKREIMPORTLISTE;
		 short  PRISMADISKETTE;
		 short  AZYXKREISNR;
		 short  PHARMAKREISNR;
		 short  UMSATZSTEUERID;
		 short  IMSAPONR;
		 short  IMSKUNDENART;
		 short  VERTRIEBSZENTRUMNR;
		 short  KUNDENNR;
		 short  BUNDESLAND;
		 short  TM_DATE;
		 short  TM_TIME;
		 short  LOGINID;
		 short  CHANGEID;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_KUNDE {
		 char    IDFNR[11];
		 char    MATCHCODE[12 + 1];
		 char    FILIALNR[7];
		 char    KDNR[11];
		 char    ETARTKLASSE1[5 + 1];
		 char    ETARTKLASSE2[5 + 1];
		 char    ETKDMERKMAL1[5 + 1];
		 char    ETKDMERKMAL2[5 + 1];
		 char    ANREDEKZ[7];
		 char    NAMEAPO[40 + 1];
		 char    NAMEINHABER[30 + 1];
		 char    STRASSE[40 + 1];
		 char    ORT[30 + 1];
		 char    POSTLEITZAHL[7 + 1];
		 char    TELNR[20 + 1];
		 char    TELNRDAFUE[20 + 1];
		 char    FAXNR[20 + 1];
		 char    TELKURZWAHL[4 + 1];
		 char    IMSBEZIRKNR[11];
		 char    KDGRUPPE[2 + 1];
		 char    PERSONALNRVERTR[11];
		 char    DAFUESYSTEM[2 + 1];
		 char    KZKDDOPPELKONTR[1 + 1];
		 char    LAGERFACHNRRGBEI[4 + 1];
		 char    ANZPOSLS_RG[7];
		 char    ANZPOSSORTBEHAELT[7];
		 char    KZKDKLASSE[3 + 1];
		 char    ORIGINALFILIALNR[7];
		 char    NOTFILIALNR[7];
		 char    BEMERKUNGEN[240 + 1];
		 char    KUNDETEXT[240 + 1];
		 char    VERBUNDKUNDE[1 + 1];
		 char    STDAUFKOBUART[4 + 1];
		 char    PASSWORD[8 + 1];
		 char    VZKK1[1 + 1];
		 char    KUEHLBOX[1 + 1];
		 char    TOURENKIPPZEIT[11];
		 char    KZUPD[1 + 1];
		 char    IMS3000[11];
		 char    LAND[3 + 1];
		 char    DRUCKREIMPORTLISTE[1 + 1];
		 char    PRISMADISKETTE[1 + 1];
		 char    AZYXKREISNR[10 + 2];
		 char    PHARMAKREISNR[11];
		 char    UMSATZSTEUERID[15 + 1];
		 char    IMSAPONR[8 + 1];
		 char    IMSKUNDENART[1 + 1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    BUNDESLAND[6 + 1];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1 + 1];
       };

 struct O_KUNDE {
		 char    IDFNR[11];
		 char    MATCHCODE[12];
		 char    FILIALNR[7];
		 char    KDNR[11];
		 char    ETARTKLASSE1[5];
		 char    ETARTKLASSE2[5];
		 char    ETKDMERKMAL1[5];
		 char    ETKDMERKMAL2[5];
		 char    ANREDEKZ[7];
		 char    NAMEAPO[40];
		 char    NAMEINHABER[30];
		 char    STRASSE[40];
		 char    ORT[30];
		 char    POSTLEITZAHL[7];
		 char    TELNR[20];
		 char    TELNRDAFUE[20];
		 char    FAXNR[20];
		 char    TELKURZWAHL[4];
		 char    IMSBEZIRKNR[11];
		 char    KDGRUPPE[2];
		 char    PERSONALNRVERTR[11];
		 char    DAFUESYSTEM[2];
		 char    KZKDDOPPELKONTR[1];
		 char    LAGERFACHNRRGBEI[4];
		 char    ANZPOSLS_RG[7];
		 char    ANZPOSSORTBEHAELT[7];
		 char    KZKDKLASSE[3];
		 char    ORIGINALFILIALNR[7];
		 char    NOTFILIALNR[7];
		 char    BEMERKUNGEN[240];
		 char    KUNDETEXT[240];
		 char    VERBUNDKUNDE[1];
		 char    STDAUFKOBUART[4];
		 char    PASSWORD[8];
		 char    VZKK1[1];
		 char    KUEHLBOX[1];
		 char    TOURENKIPPZEIT[11];
		 char    KZUPD[1];
		 char    IMS3000[11];
		 char    LAND[3];
		 char    DRUCKREIMPORTLISTE[1];
		 char    PRISMADISKETTE[1];
		 char    AZYXKREISNR[10];
		 char    PHARMAKREISNR[11];
		 char    UMSATZSTEUERID[15];
		 char    IMSAPONR[8];
		 char    IMSKUNDENART[1];
		 char    VERTRIEBSZENTRUMNR[7];
		 char    KUNDENNR[11];
		 char    BUNDESLAND[6];
		 char    TM_DATE[11];
		 char    TM_TIME[11];
		 char    LOGINID[11];
		 char    CHANGEID[1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc KUNDE_BES [] =
 {
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,   40 ,   0 },
	 { TYP_C ,   30 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,   20 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,  240 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    4 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    3 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_D ,   10 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,   15 ,   0 },
	 { TYP_C ,    8 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_S ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    6 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_L ,   11 ,   0 },
	 { TYP_C ,    1 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KUNDE_BES [] =
 {
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   12 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,   40 ,   0 },
	 { TYP_C,   30 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,   20 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_C,  240 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,    4 ,   0 },
	 { TYP_C,    8 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    3 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_D,   10 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,   15 ,   0 },
	 { TYP_C,    8 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_S,    5 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_C,    6 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_L,   11 ,   0 },
	 { TYP_F,    1 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CKUNDE
 {
  public:

  KUNDE s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, KUNDE_BES, KUNDE_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,KUNDE_BES, KUNDE_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,KUNDE_BES, KUNDE_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CKUNDE()
  {
   ::buf_default((void *)&s, KUNDE_BES, KUNDE_ANZ);
  }
 };
#endif

#define KUNDE_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 IDFNR              INTEGER         default 0 NOT NULL,\
		 MATCHCODE          CHAR(12)        default " " NOT NULL,\
		 FILIALNR           SMALLINT        default 0 NOT NULL,\
		 KDNR               INTEGER         default 0 NOT NULL,\
		 ETARTKLASSE1       INTEGER         default 0 NOT NULL,\
		 ETARTKLASSE2       INTEGER         default 0 NOT NULL,\
		 ETKDMERKMAL1       INTEGER         default 0 NOT NULL,\
		 ETKDMERKMAL2       INTEGER         default 0 NOT NULL,\
		 ANREDEKZ           SMALLINT        default 0 NOT NULL,\
		 NAMEAPO            CHAR(40)        default " " NOT NULL,\
		 NAMEINHABER        CHAR(30)        default " " NOT NULL,\
		 STRASSE            CHAR(40)        default " " NOT NULL,\
		 ORT                CHAR(30)        default " " NOT NULL,\
		 POSTLEITZAHL       CHAR(7)         default " " NOT NULL,\
		 TELNR              CHAR(20)        default " " NOT NULL,\
		 TELNRDAFUE         CHAR(20)        default " " NOT NULL,\
		 FAXNR              CHAR(20)        default " " NOT NULL,\
		 TELKURZWAHL        CHAR(4)         default " " NOT NULL,\
		 IMSBEZIRKNR        INTEGER         default 0 NOT NULL,\
		 KDGRUPPE           CHAR(2)         default " " NOT NULL,\
		 PERSONALNRVERTR    INTEGER         default 0 NOT NULL,\
		 DAFUESYSTEM        CHAR(2)         default " " NOT NULL,\
		 KZKDDOPPELKONTR    CHAR(1)         default " " NOT NULL,\
		 LAGERFACHNRRGBEI   CHAR(4)         default " " NOT NULL,\
		 ANZPOSLS_RG        SMALLINT        default 0 NOT NULL,\
		 ANZPOSSORTBEHAELT  SMALLINT        default 0 NOT NULL,\
		 KZKDKLASSE         CHAR(3)         default " " NOT NULL,\
		 ORIGINALFILIALNR   SMALLINT        default 0 NOT NULL,\
		 NOTFILIALNR        SMALLINT        default 0 NOT NULL,\
		 BEMERKUNGEN        VARCHAR(240,0)  default " " NOT NULL,\
		 KUNDETEXT          VARCHAR(240,0)  default " " NOT NULL,\
		 VERBUNDKUNDE       CHAR(1)         default " " NOT NULL,\
		 STDAUFKOBUART      CHAR(4)         default " " NOT NULL,\
		 PASSWORD           CHAR(8)         default " " NOT NULL,\
		 VZKK1              CHAR(1)         default " " NOT NULL,\
		 KUEHLBOX           CHAR(1)         default " " NOT NULL,\
		 TOURENKIPPZEIT     INTEGER         default 0 NOT NULL,\
		 KZUPD              CHAR(1)         default " " NOT NULL,\
		 IMS3000            INTEGER         default 0 NOT NULL,\
		 LAND               CHAR(3)         default " " NOT NULL,\
		 DRUCKREIMPORTLISTE CHAR(1)         default " " NOT NULL,\
		 PRISMADISKETTE     CHAR(1)         default " " NOT NULL,\
		 AZYXKREISNR        DECIMAL(10,0)   default 0 NOT NULL,\
		 PHARMAKREISNR      INTEGER         default 0 NOT NULL,\
		 UMSATZSTEUERID     CHAR(15)        default " " NOT NULL,\
		 IMSAPONR           CHAR(8)         default " " NOT NULL,\
		 IMSKUNDENART       CHAR(1)         default " " NOT NULL,\
		 VERTRIEBSZENTRUMNR SMALLINT        default 0 NOT NULL,\
		 KUNDENNR           INTEGER         default 0 NOT NULL,\
		 BUNDESLAND         CHAR(6)         default " " NOT NULL,\
		 TM_DATE            INTEGER         default 0 NOT NULL,\
		 TM_TIME            INTEGER         default 0 NOT NULL,\
		 LOGINID            INTEGER         default 0 NOT NULL,\
		 CHANGEID           CHAR(1)         default " " NOT NULL  ) EXTENT SIZE 2270 LOCK MODE ROW;

#define KUNDE_CREATE_INDEX(yyy,xxx) \
 EXEC SQL CREATE UNIQUE INDEX KUNDEX             on yyy( IDFNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX KDMATCHCODEX       on yyy( MATCHCODE );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL CREATE INDEX I_KUNDE_315        on yyy( KDNR );\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

#define KUNDE_DELETE_INDEX(xxx) \
 EXEC SQL DROP INDEX KUNDEX            ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX KDMATCHCODEX      ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \
 EXEC SQL DROP INDEX I_KUNDE_315       ;\
 if( sqlca.sqlcode != 0 ) xxx = sqlca.sqlcode; \

