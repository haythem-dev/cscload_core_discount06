#ifndef GUARD_CSCLOAD_VERSION_H
#define GUARD_CSCLOAD_VERSION_H

#define CSC_LOAD_VERSION	"01.01.07.29"

/*******************************************************************************************/
/*!
\mainpage notitle

\version 01.01.07.29
\date 2025-11-20
\internal
- SCTASK0113354- Anpassung Einspielung Kontingente aus dem OBM (Einkauf),
 adding kundegruppe 07','08','09','16','17' in das Programm loadtempquota
\endinternal

\version 01.01.07.27
\date 2025-10-07
\internal
- CPR0003163 Freiburg Crisis - Adaption tpldzentknd.
\endinternal

\version 01.01.07.26
\date 2025-07-18
\internal
- CPR-240019 add callbackstatus option to delkdkritik.sh for austria.
\endinternal

\version 01.01.07.25
\date 2025-05-27
\internal
- CPR0002201 IBT Handling in France: adapt delvb27.sh to new IBT logic.
\endinternal

\version 01.01.07.24
\date 2025-05-21
\internal
- CPR-240732 adding skdtournee into tplddkkui customer transfer wholesale branch from host 
..to ksc kundeschalter table (mainly used for prewholesale)
\endinternal

\version 01.01.07.23
\date 2025-04-30
\internal
- CPR-240759 Transportausschluss für psychotrope Stoffe - Anpassung des Ladeprogramms loadroutes
\endinternal

\version 01.01.07.22
\date 2025-03-11
\internal
- CPR-240868 modified delvaccinsubsequent to delete via warengruppeeigen (article group) 
\endinternal

\version 01.01.07.21
\date 2025-03-06
\internal
- CPR-240624 Cleanup of CSC Load Applications
  Following apps which were part of csc_load apps has been removed and moved to _obselete folder
  since they are not used anymore for any of the countries with exception of RS
    - loadcucosrs.bin
    - loadimexpermission.bin
    - loadmanquants.bin
    - loadplannedcalls.bin
    - loadreturnperiods.bin
    - loadsaparticlestock.bin
    - loadsupplierarticlenumber.bin
    - loadsupport.bin
    - tpldagp.bin
    - tplddb.bin
    - tpldhipath.bin
    - tpldoldprice.bin
    - tpldreakauft.bin
    - tpldregiodata.bin
    - tpldtabmic.bin
\endinternal

\date 2025-03-04
\internal
- CPR-240750 enhance loadnewquota with allowing also customergroups in CSV to optimize import files
\endinternal

\version 01.01.07.20
\date 2025-02-19
\internal
- CPR-240377 update loadcscarticleprognosis, add loadcscpubatchorderpos
\endinternal

\version 01.01.07.19
\date 2025-01-29
\internal
- CPR-240377 add loadcscarticleprognosis, loadcscbrancharticle, loadpubranchsupplier, loadsupplier 
- CPR-240073 add logfilewatchdog script for internal monitoring logfiles and mail alerting
\endinternal

\version 01.01.07.18
\date 2025-01-13
\internal
- CPR-240377 create new loadsupplier.bin from inbound:liefer to outbound:supplier
\endinternal

\version 01.01.07.17
\date 2024-11-29
\internal
- CPR-240864 adjust tpldzentral to increase performance
- I-24102811 To check exactly with weekday=0
\endinternal

\version 01.01.07.16
\date 2024-11-05
\internal
- I-24096466 - reintegrate Hageda now, explicit deactivation removed
\endinternal

\version 01.01.07.15
\date 2024-10-28
\internal
- CPR-231093 update quota for commit pause 
\endinternal

\version 01.01.07.14
\date 2024-10-01
\internal
- CPR-231093 new quota load for full and delta imports 
\endinternal

\version 01.01.07.13
\date 2024-09-30
\internal
- CPR-230575 activate WAFOTYP for France from zartfrance.nachlieferung to artikellokal
\endinternal

\version 01.01.07.12
\date 2023-08-13
\internal
- SR-24100247 deaktivate synchronization of WAFOTYP from host for Hageda branch 21
- hotfix for tpldlokalart, only - deactivation of WAFOTYP from deakz-host-file
\endinternal

\version 01.01.07.11
\date 2024-06-11
\internal
-  SR-24066777 loadtempquota: Added customer group 2,3,14 and branch 21
\endinternal

\version 01.01.07.10
\date 2024-05-02
\internal
-  Loadcscbeskopfandposi using the merge command to insert and updaste into cscbeskopf and posi
\endinternal

\version 01.01.07.09
\date 2024-02-15
\internal
-  I-24010021(BG) loaddebtlimit.bin fixed
\endinternal

\version 01.01.07.08
\date 2024-01-19
\internal
-  I-23072381 delvaccinesubsequent fixed
\endinternal

\version 01.01.07.07
\date 2023-10-24
\internal
- CPR-220467 (P-ONE - CHI) Erweiterung tpldauftr um neue Spalten ( tourstopsequence + carrier ).
- CPR-220467 (P-ONE - CHI) SAP-Partnerfunktionen zum Auftrag archivieren.
\endinternal

\version 01.01.07.06
\date 2023-09-28
\internal
- SR-23106189 Load program to copy from inbound table beskopf and besposi into outbound tables cscbeskopf and cscbesposi.
\endinternal

\version 01.01.07.05
\date 2023-09-15
\internal
- CPR-200793 Operational credit limit HR.
- Updated script for credit limit load in HR.
\endinternal

\version 01.01.07.04
\date 2023-09-04
\internal
- CPR-211062 language correction for crema BG.
- language set to BG for Bulgaria when crema enabled "tpldzentknd".
\endinternal

\version 01.01.07.03
\date 2023-07-20
\internal
- P-23000205 Reorganisation Tabelle Artikelkonto.
- neues Löschprogramm "delartikelkonto".
\endinternal

\version 01.01.07.02
\date 2023-07-20
\internal
- CPR-210210 subsequentdelivery synchronization from CDM to CSC
- I-23039339 - Hageda Branch 21 disabled for synchronization
- hotfix for tpldlokalart, only - reactivation of WAFOTYP from deakz-host-file
\endinternal

\version 01.01.07.01
\date 2023-07-17
\internal
- CPR-210210 subsequentdelivery synchronization from CDM to CSC
- I-23039339 - status 8 and 9 transfered to 1 and 0 when synchronized to artikellokal
- hotfix for loadbrancharticleconfig only
\endinternal
________________________________________________________________________________________
\version 01.01.07.00
\date 2023-05-30
\internal
- CPR-210210 subsequentdelivery synchronization from CDM to CSC
- move / rename loadibtbrancharticleconfig to loadbrancharticleconfig and added sync of subsequent delivery
- changed tpldlokalart - disabled loading artikellokal.wafotyp from hostfile except for Switzerland (CH)
\endinternal

________________________________________________________________________________________
\version 01.01.06.00
\date 2023-05-30
\internal
- CPR-220467 (P-ONE-CHI-Integration of CSC) loadsupplierarticlenumber - neues Ladeprogramm
\endinternal
________________________________________________________________________________________
\version 01.01.05.00
\date 2023-03-30
\internal
- P-23000038: Pricing DE clean up - remove obsolete jobs, adapt tpldlokalart to remove artikelnatra actions 
\endinternal
________________________________________________________________________________________
\version 01.01.04.00
\date 2023-03-08
\internal
- loadflyersubsequent add for importing flyers into nachlieferpos (CPR-220071)
\endinternal
________________________________________________________________________________________
\version 01.01.03.00
\date 2023-02-06
\internal
- loadconditions adapted for use in future with unqiue index in table discount
\endinternal
________________________________________________________________________________________
\version 01.01.02.00
\date 2023-02-06
\internal
- AMICO addition of discount flags (in discount table) to be transferred to KSC
\endinternal
________________________________________________________________________________________
\version 01.01.01.00
\date 2022-06-20
\internal
- export updated
\endinternal
________________________________________________________________________________________
\version 01.01.00.00
\date 2022-05-31
\internal
- CPR-210692 ID166 Spannenkappung
- Includes updated to latest externals
\endinternal
________________________________________________________________________________________
\version 01.00.06.04
\date 2022-04-06
\internal
- CPR-210692 DE Pricing: loadpricelist - neues Ladeprogramm für Hageda Preise
                         loadpharmgrpvse - neues Ladeprogramm für Einkaufsgruppen (DKEGR)
\endinternal
________________________________________________________________________________________
\version 01.00.06.03
\date 2022-03-21
\internal
- (FN) CPR-210692 DE Pricing: tplddkkui RXA Kennzeichen in KSC importieren.
\endinternal
________________________________________________________________________________________
\version 01.00.06.02
\date 2022-01-24
\internal
- Project CMI21: Adjust tpldzentral and load CMI_FLAG from zartikel to artikelzentral
\endinternal
________________________________________________________________________________________
\version 01.00.06.01
\date 2021-10-01
\internal
- CPR-200938 CH Add AGP (Amedis Groundprice) from ZDP (zartpreis) to KSC (artikelpreis) table
\endinternal
________________________________________________________________________________________
\version 01.00.06.00
\date 2020-10-22
\internal
- CPR-210623Der longtermlackloader, zur Ermittlung der Dauerdefekte (Tabelle ), muss dahingehend erweitert dass Artikel, für die min. 
   eine Reimport-Substitution hinterlegt ist , diese nicht in der Tabelle longtermlack aufgenommen werden.  
   Wenn ein Artikel in der artikelreimport.artikel_nr vorhanden und min. ein Eintrag artikelreimport.kzaktivpassiv = 1
   dann den original Artikel (article_nr) NICHT in die longtermlack aufnehmen.
\endinternal
________________________________________________________________________________________
\version 01.00.05.00
\date 2020-10-22
\internal
- I-20041902 LongTermLack/Substitution select was modified to not use branch no 0, which no one knows when it's set.
\endinternal
________________________________________________________________________________________
\version 01.00.04.05
\date 2020-08-26
\internal
- In the hipath2 program, the kunden select was modified in order to select only the direct
customers.
\endinternal
________________________________________________________________________________________
\version 01.00.04.04
\date 2019-12-03
\internal
- (BB) longtermlackloader: parameterization of persistence startegy of table 'longtermlack'.
                           New parameter (UADM): 'PERSISTENCE_STRATEGY': 0 = Delete; 1 = db table Truncate;
\endinternal
________________________________________________________________________________________
\version 01.00.04.02
\date 2019-10-09
\internal
- (BB) longtermlackloader: new binary load new table 'longtermlack'.
\endinternal
________________________________________________________________________________________
\version 01.00.04.00
\date 2018-09-27
\internal
- (RI) tpldauftr: I-18042525 APX Abbruch (Error in DeleteOldCSV).
\endinternal
________________________________________________________________________________________
\version 01.00.03.00
\date 2018-09-13
\internal
- (RI) loadroutes: load new field in tourplantag & tourplantagwoche: RETURNSTOUR.
- (RI) New program: loadreturnperiods: load new tables returnperiod & returnperiodarticletype.
- new program loadworkingdayscalenadar
- (FN) tpldauftr.cxx: delete old csv and Log files on the server
\endinternal
_______________________________________________________________________________________
\version 01.00.02.00
\date 2018-07-11
\internal
- (RI) tpldzentral: load new field in artikelzentral: BATCHRECALLDATERETURNS.
- (RI) tpldzentral: load new field in artikelzentral: IMPORTARTICLE.
- (FN) tpldzentral: load new field in artikelzentral: BTM_FAKTOR.
- (RI) tpldzentknd: Bundeslandzuordnung von ims3000 auf pharmakreisnr geändert.
- (RI) tpldzentknd: Korrektur BG SR-18054045
- (RI) tpldauftrag: fixcharge mit in Historie übernehmen.
\endinternal
________________________________________________________________________________________
\version 01.00.01.00
\date 2017-07-18
\internal
- (RI) tpldtour.cxx: load new field in tour: snighttour
- (RI) tpldauftr.cxx: delete old nachlieferpos with status 2
- (FN) Doxygen style changelog.
- (FN) Versionsabfrage analog csc_core_applications.
- (FN) change version information from svn:keywords to git info
\endinternal
_______________________________________________________________________________________
*/

/*
Here is the template for a version description.
Copy this section to the top of the version history to create a new version history entry.
________________________________________________________________________________________
\version 01.01.07.28
\date 2025-10-07
\internal
\endinternal
*/

#ifdef NDEBUG
#define PROJECTCONFIG	"rel"
#else
#define PROJECTCONFIG	"dbg"
#endif

#endif // GUARD_CSCLOAD_VERSION_H
