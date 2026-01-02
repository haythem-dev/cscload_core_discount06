#include<bufkon.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<memory.h>
#include "artsel.h"
#include <texte.h>
#include <allg.h>
#include <ppgeneric.h>
#include "kndsel.h"
#include "verbundcheck.h"
#include "auftrag.h"
#include <stdbool.h>

int AatartSel_Preferred(struct ARTAESEL *d, char *error_msg);
void WriteLogInfo(const char *err_str, int err_num, int fehler_art);
void EscapeSingleQuotes(char* dest, const char* src);
void HandleNormPackage(char* dest, const char* src, const char* notSetChar);
short HandlePharmacyGroupID(const char* pharmacyGroupID);
void GetAatartSel_mc_Select(struct ARTSEL* a, bool bUsePackageSize);

#define UNUSED(x) (void)(x)

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

#define NOT_FOUND        1
#define FILE_NOT_FOUND   1
#define ERROR           -1
#define WARNING         -2

/*  externeGLOBALE C-VARIABLEN  */
extern char cCountry[3];


EXEC SQL BEGIN DECLARE SECTION;
char str[4096];
extern char haus_nr[4 + 1];
extern long UID;
extern short FilialNr;
extern int FREMDSPRACHE;
extern char ARTIKELZENTRAL_SPRACHE[20];
extern char ARTIKELSELECT_SPRACHE[20];
extern char ARTIKELINDEX_SPRACHE[20];
extern char ARTIKELSEKBEZ_SPRACHE[20];
extern short sVzNr;
extern long lKundenNr;
extern char cKdauftragArt[3];
short sActVz = -1;
char cSNewDiscount[2];
EXEC SQL END DECLARE SECTION;

/*** Ergänzung fuer Ivrilab *******************/

void AatartIvrylab(char* tab_name, char* EKG)
{
    char cKundennr[8];
    char cBranchno[3];
    UNUSED(EKG);
    sprintf(cBranchno, "%d", FilialNr);
    sprintf(cKundennr, "%d", lKundenNr);
    strcat(str, "and (");
    strcat(str, tab_name);
    strcat(str, ".konsig_partner_nr = 0 ");
    strcat(str, "or ");
    strcat(str, tab_name);
    strcat(str, ".konsig_partner_nr in ");
    strcat(str, "(select manufacturergroup.konsig_partner_nr from ");
    strcat(str, "manufacturergroup where ");
    strcat(str, "manufacturergroup.pharmacygroupid in ");
    strcat(str, "(select customerpharmacygr.pharmacygroupid from ");
    strcat(str, "customerpharmacygr where ");
    strcat(str, "customerpharmacygr.branchno = ");
    strcat(str, cBranchno);
    strcat(str, "and customerpharmacygr.customerno = ");
    strcat(str, cKundennr);
    strcat(str, " )))");
}

/*** AatartCheck_natra (Suchen EK-Gruppenbezogenen Natra) *******************/

//int AatartCheck_natra(struct ARTAESEL *d, char *error_msg)
//{
//static int fst = 1;
//EXEC SQL BEGIN DECLARE SECTION;
//struct ARTAESEL *b;
//int counter;
//EXEC SQL END DECLARE SECTION;
//
//b = d;
//
//if (fst) /* beim ersten mal oder bei neu deklarieren */
//{
//	fst = 0;
//	if(sActVz != sVzNr)
//	{
//		EXEC SQL select sNewDiscount
//			into :cSNewDiscount
//			from paraauftragbearb
//			where filialnr = :sVzNr;
//		sActVz = sVzNr;
//	}
//	if(cSNewDiscount[0] == '1')
//	{
//		return 0;
//	}
//	else
//	{
//		strcpy(str,"select count(*) from ");
//		strcat(str,"customerpharmacygr c, artikelnatra n ");
//		strcat(str,"where c.branchno = ? ");
//		strcat(str,"and c.customerno = ? ");
//		strcat(str,"and n.NATRASTAFFELNR = ? ");
//		strcat(str,"and c.branchno = n.vertriebszentrumnr ");
//		strcat(str,"and c.pharmacygroupid = n.einkaufsgruppe ");
//	}
//	EXEC SQL PREPARE dec_check_natra FROM :str;
//	if (sqlca.sqlcode < 0 )
//	{
//		fst = 1;
//		sprintf(error_msg, " AatartCheck_natra: declare dec_check_natra %ld %ld",
//				sqlca.sqlcode, sqlca.sqlerrd[1]);
//		WriteLogInfo(error_msg, -1 , -1);
//		return -1;
//	}
//    EXEC SQL declare Sel_check_natra scroll cursor with hold for dec_check_natra;
//}
//if(b->NATRASTAFFELNR == 0) return 0;
//if(AllgBitleisteN((Bitleiste)b->ETARTSCHALTER3,7)) return 0;
//EXEC SQL open Sel_check_natra
//	using
//	:sVzNr,
//	:lKundenNr,
//	:b->NATRASTAFFELNR;
//if (sqlca.sqlcode < 0 )
//{
//	fst = 1;
//	sprintf(error_msg, " AatartCheck_natra: open Sel_check_natra %ld", sqlca.sqlcode);
//	WriteLogInfo(error_msg, -1 , -1);
//	return -1;
//}
//EXEC SQL fetch Sel_check_natra into :counter;
//if (sqlca.sqlcode < 0 )
//{
//	fst = 1;
//	sprintf(error_msg, " AatartCheck_natra: fetch Sel_check_natra %ld", sqlca.sqlcode);
//	WriteLogInfo(error_msg, -1 , -1);
//	EXEC SQL close Sel_check_natra;
//	return -1;
//}
//if(counter > 0) b->ETARTSCHALTER3 += 256;
//return 0;
//}

/*** AatartCheck_mgpreis (Suchen EK-Gruppenbezogenen Rabatt) *******************/

//int AatartCheck_mgpreis(struct ARTAESEL *d, char *error_msg)
//{
//static int fst = 1;
//EXEC SQL BEGIN DECLARE SECTION;
//struct ARTAESEL *b;
//int counter;
//EXEC SQL END DECLARE SECTION;
//
//b = d;
//
//if (fst) /* beim ersten mal oder bei neu deklarieren */
//{
//	fst = 0;
//	strcpy(str,"select count(*) from ");
//	strcat(str,"validdiscountinfo n ");
//	strcat(str,"where n.branchno = ? ");
//	strcat(str,"and n.articleno = ? ");
//	strcat(str,"and n.pharmacygroupid = '000' ");
//	EXEC SQL PREPARE dec_check_mgpreis1 FROM :str;
//    EXEC SQL declare Sel_check_mgpreis1 scroll cursor with hold for dec_check_mgpreis1;
//	if (sqlca.sqlcode < 0 )
//	{
//		fst = 1;
//		sprintf(error_msg, " AatartCheck_mgpreis: declare dec_check_mgpreis1 %ld %ld",
//				sqlca.sqlcode, sqlca.sqlerrd[1]);
//		WriteLogInfo(error_msg, -1 , -1);
//		return -1;
//	}
//
//	strcpy(str,"select count(*) from ");
//	strcat(str,"customerpharmacygr c, validdiscountinfo n ");
//	strcat(str,"where c.branchno = ? ");
//	strcat(str,"and c.customerno = ? ");
//	strcat(str,"and n.articleno = ? ");
//	strcat(str,"and c.branchno = n.branchno ");
//	strcat(str,"and c.pharmacygroupid = n.pharmacygroupid ");
//	EXEC SQL PREPARE dec_check_mgpreis2 FROM :str;
//    EXEC SQL declare Sel_check_mgpreis2 scroll cursor with hold for dec_check_mgpreis2;
//	if (sqlca.sqlcode < 0 )
//	{
//		fst = 1;
//		sprintf(error_msg, " AatartCheck_mgpreis: declare dec_check_mgpreis2 %ld %ld",
//				sqlca.sqlcode, sqlca.sqlerrd[1]);
//		WriteLogInfo(error_msg, -1 , -1);
//		return -1;
//	}
//}
//if(AllgBitleisteN((Bitleiste)b->ETARTSCHALTER1,6)) return 0;
//EXEC SQL open Sel_check_mgpreis1
//	using
//	:sVzNr,
//	:b->ARTIKEL_NR;
//if (sqlca.sqlcode < 0 )
//{
//	fst = 1;
//	sprintf(error_msg, " AatartCheck_mgpreis: open Sel_check_mgpreis1 %ld", sqlca.sqlcode);
//	WriteLogInfo(error_msg, -1 , -1);
//	return -1;
//}
//EXEC SQL fetch Sel_check_mgpreis1 into :counter;
//if (sqlca.sqlcode < 0 )
//{
//	fst = 1;
//	sprintf(error_msg, " AatartCheck_mgpreis: fetch Sel_check_mgpreis1 %ld", sqlca.sqlcode);
//	WriteLogInfo(error_msg, -1 , -1);
//	EXEC SQL close Sel_check_mgpreis1;
//	return -1;
//}
//if(counter > 0)
//{
//	b->ETARTSCHALTER1 += 512;
//	return 0;
//}
//EXEC SQL open Sel_check_mgpreis2
//	using
//	:sVzNr,
//	:lKundenNr,
//	:b->ARTIKEL_NR;
//if (sqlca.sqlcode < 0 )
//{
//	fst = 1;
//	sprintf(error_msg, " AatartCheck_mgpreis: open Sel_check_mgpreis2 %ld", sqlca.sqlcode);
//	WriteLogInfo(error_msg, -1 , -1);
//	return -1;
//}
//EXEC SQL fetch Sel_check_mgpreis2 into :counter;
//if (sqlca.sqlcode < 0 )
//{
//	fst = 1;
//	sprintf(error_msg, " AatartCheck_mgpreis: fetch Sel_check_mgpreis2 %ld", sqlca.sqlcode);
//	WriteLogInfo(error_msg, -1 , -1);
//	EXEC SQL close Sel_check_mgpreis2;
//	return -1;
//}
//if(counter > 0) b->ETARTSCHALTER1 += 512;
//return 0;
//}

int AatartSel_art_nr(struct ARTSEL* d, char* error_msg)
{
    static short IMPORTARTICLE_ALT = 3;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTSEL* a;
    EXEC SQL END DECLARE SECTION;
    static int FREMDSPRACHE_ALT = 2;

    a = d;
    if (FREMDSPRACHE != FREMDSPRACHE_ALT || a->IMPORTARTICLE != IMPORTARTICLE_ALT)
    {
        FREMDSPRACHE_ALT = FREMDSPRACHE;
        IMPORTARTICLE_ALT = a->IMPORTARTICLE;
        EXEC SQL free dec_artnr;
        if (FREMDSPRACHE)
        {
            strcpy(str, "select ");
            strcat(str, "nvl(c.ARTIKEL_MC,z.ARTIKEL_MC), ");
            strcat(str, "z.PACKGROESSE, ");
            strcat(str, "nvl(c.DARREICHFORM,z.DARREICHFORM), ");
            strcat(str, "nvl(c.EINHEIT,z.EINHEIT), ");
            strcat(str, "nvl(c.ARTIKEL_NAME,z.ARTIKEL_NAME), ");
            strcat(str, "z.ARTIKEL_NR, ");
            strcat(str, "ARTIKELLOKAL.BESTAND, ");
            strcat(str, "z.NORMPACKUNG, ");
            strcat(str, "z.HERSTELLER_CODE, ");
            strcat(str, "z.IMPORTARTICLE ");
            strcat(str, "from artikelzentral z,outer artikellokal, outer ");
            strcat(str, ARTIKELZENTRAL_SPRACHE);
            strcat(str, " c ");
            strcat(str, "where z.artikel_nr = ? ");
            if (a->IMPORTARTICLE == 0)
            {
                strcat(str, "and z.importarticle = 0 ");
            }
            else if (a->IMPORTARTICLE == 1)
            {
                strcat(str, "and z.importarticle = 1 ");
            }
            strcat(str, "and c.artikel_nr = z.artikel_nr ");
            strcat(str, "and artikellokal.artikel_nr = z.artikel_nr ");
            strcat(str, "and artikellokal.filialnr = ? ");
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_MC, ");
            strcat(str, "ARTIKELZENTRAL.PACKGROESSE, ");
            strcat(str, "ARTIKELZENTRAL.DARREICHFORM, ");
            strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NR, ");
            strcat(str, "ARTIKELLOKAL.BESTAND, ");
            strcat(str, "ARTIKELZENTRAL.NORMPACKUNG, ");
            strcat(str, "ARTIKELZENTRAL.HERSTELLER_CODE, ");
            strcat(str, "ARTIKELZENTRAL.IMPORTARTICLE ");
            strcat(str, "from artikelzentral,outer artikellokal ");
            strcat(str, "where artikelzentral.artikel_nr = ? ");
            if (a->IMPORTARTICLE == 0)
            {
                strcat(str, "and artikelzentral.importarticle = 0 ");
            }
            else if (a->IMPORTARTICLE == 1)
            {
                strcat(str, "and artikelzentral.importarticle = 1 ");
            }
            strcat(str, "and artikellokal.artikel_nr = artikelzentral.artikel_nr ");
            strcat(str, "and artikellokal.filialnr = ? ");
        }

        EXEC SQL PREPARE dec_artnr FROM :str;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartSel_art_nr: declare dec_artnr %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }
    EXEC SQL EXECUTE dec_artnr
        into ARTSEL_ZEIGER(a)
        USING
        :a->ARTIKEL_NR,
        :FilialNr;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_art_nr select %ld", sqlca.sqlcode);
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, TXT_KEIN_ART_PZN);
        return -2;
    }
    return 0;
}

/*** AatartSel_mc (Matchcode suche ohne Zusatz nur Artikel) *******************/

int AatartSel_mc(struct ARTSEL* d, char* error_msg)
{
    static bool fst = true;
    static int FREMDSPRACHE_ALT = 2;
    static int BESTAND_ALT = 2;
    static short IMPORTARTICLE_ALT = 3;
    int iMax = 3;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTSEL* a;
    char NORMPACKUNG[5];
    char* arrArtikelName[L_ARTSEL_ARTIKEL_NAME + 2]; // ppGGetWhereFromStr requires 'const' but EXEC SQL not!
    EXEC SQL END DECLARE SECTION;

    a = d;

    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = false;
        AllgMakeToLike(a->ARTIKEL_MC, L_ARTSEL_ARTIKEL_MC);
        AllgMakeToLike(a->DARREICHFORM, L_ARTSEL_DARREICHFORM);
        ppGGetWhereFromStr(PPG_STATIC, a->ARTIKEL_NAME, (char*)0, (char*)0, (const char**)arrArtikelName, iMax);

        HandleNormPackage(NORMPACKUNG, a->NORMPACKUNG, "%");

        if (FREMDSPRACHE != FREMDSPRACHE_ALT || a->BESTAND != BESTAND_ALT || a->IMPORTARTICLE != IMPORTARTICLE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            BESTAND_ALT = a->BESTAND;
            IMPORTARTICLE_ALT = a->IMPORTARTICLE;

            GetAatartSel_mc_Select(a, false);

            EXEC SQL free dec_mc_art;
            EXEC SQL free Sel_mc_art;

            EXEC SQL PREPARE dec_mc_art FROM :str;
            if (sqlca.sqlcode < 0)
            {
                fst = true;
                sprintf(error_msg, " AatartSel_mc: declare dec_mc_art %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_mc_art scroll cursor with hold for dec_mc_art;
        }

        EXEC SQL open Sel_mc_art
            using
            :a->ARTIKEL_MC,
            :a->DARREICHFORM,
            :FilialNr,
            :NORMPACKUNG,
            :arrArtikelName[0],
            :arrArtikelName[1],
            :arrArtikelName[2];
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartSel_mc: open Sel_mc_art %ld", sqlca.sqlcode);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = true;
        EXEC SQL close Sel_mc_art;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartSel_mc: close Sel_mc_art %ld", sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_mc_art into ARTSEL_ZEIGER(a);
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartSel_mc: fetch Sel_mc_art %ld", sqlca.sqlcode);
        EXEC SQL close Sel_mc;
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

/*** AatartSel_mc_pkg (Matchcode suche ohne Zusatz nur Artikel) ***************/

int AatartSel_mc_pkgr(struct ARTSEL* d, char* error_msg)
{
    static bool fst = true;
    static int FREMDSPRACHE_ALT = 2;
    static int BESTAND_ALT = 2;
    static short IMPORTARTICLE_ALT = 3;
    int iMax = 3;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTSEL* a;
    char NORMPACKUNG[5];
    char* arrArtikelName[L_ARTSEL_ARTIKEL_NAME + 2]; // ppGGetWhereFromStr requires 'const' but EXEC SQL not!
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = false;
        AllgMakeToLike(a->ARTIKEL_MC, L_ARTSEL_ARTIKEL_MC);
        AllgMakeToLike(a->DARREICHFORM, L_ARTSEL_DARREICHFORM);
        ppGGetWhereFromStr(PPG_STATIC, a->ARTIKEL_NAME, (char*)0, (char*)0, (const char**)arrArtikelName, iMax);

        HandleNormPackage(NORMPACKUNG, a->NORMPACKUNG, "%");

        if (FREMDSPRACHE != FREMDSPRACHE_ALT || a->BESTAND != BESTAND_ALT || a->IMPORTARTICLE != IMPORTARTICLE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            BESTAND_ALT = a->BESTAND;
            IMPORTARTICLE_ALT = a->IMPORTARTICLE;

            GetAatartSel_mc_Select(a, true);

            EXEC SQL free dec_mc_pkgr;
            EXEC SQL free Sel_mc_pkgr;

            EXEC SQL PREPARE dec_mc_pkgr FROM :str;
            if (sqlca.sqlcode < 0)
            {
                fst = true;
                sprintf(error_msg, " AatartSel_mc_pkgr: declare dec_mc_pkgr %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }

            EXEC SQL declare Sel_mc_pkgr scroll cursor with hold for dec_mc_pkgr;
        }

        EXEC SQL open Sel_mc_pkgr
            using
            :a->ARTIKEL_MC,
            :a->PACKGROESSE,
            :a->DARREICHFORM,
            :FilialNr,
            :NORMPACKUNG,
            :arrArtikelName[0],
            :arrArtikelName[1],
            :arrArtikelName[2];

        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartSel_mc_pkgr: open Sel_mc_pkgr %ld", sqlca.sqlcode);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = true;
        EXEC SQL close Sel_mc_pkgr;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartSel_mc_pkgr: close Sel_mc_pkgr %ld", sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_mc_pkgr into ARTSEL_ZEIGER(a);
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartSel_mc_pkgr: fetch Sel_mc_pkgr %ld", sqlca.sqlcode);
        EXEC SQL close Sel_mc_pkgr;
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

int AatartInf_art_nr(struct ARTINF* d, char* error_msg)
{
    long pzn;
    static int FREMDSPRACHE_ALT = 2;
    static short IMPORTARTICLE_ALT = 3;

    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTINF* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    pzn = a->ARTIKEL_NR;
    if (FREMDSPRACHE != FREMDSPRACHE_ALT || a->IMPORTARTICLE != IMPORTARTICLE_ALT)
    {
        FREMDSPRACHE_ALT = FREMDSPRACHE;
        IMPORTARTICLE_ALT = a->IMPORTARTICLE;
        EXEC SQL free dec_infartnr;
        if (FREMDSPRACHE)
        {
            strcpy(str, "select ");
            strcat(str, "ARTIKELLOKAL.NATRASTAFFELNR, ");
            strcat(str, "nvl(c.ARTIKEL_MC,z.ARTIKEL_MC), ");
            strcat(str, "z.PACKGROESSE, ");
            strcat(str, "nvl(c.DARREICHFORM,z.DARREICHFORM), ");
            strcat(str, "z.NORMPACKUNG, ");
            strcat(str, "nvl(c.EINHEIT,z.EINHEIT), ");
            strcat(str, "nvl(c.ARTIKEL_NAME,z.ARTIKEL_NAME), ");
            strcat(str, "nvl(ARTIKELLOKAL.VERKAUFEINHEIT,0), ");
            strcat(str, "nvl(ARTIKELLOKAL.CONTAINERGROESSE,0), ");
            strcat(str, "z.ETARTKLASSE1, ");
            strcat(str, "0, ");
            strcat(str, "(z.ETARTSCHALTER1 + nvl(ARTIKELLOKAL.ETARTSCHALTER1,0) ), ");
            strcat(str, "(z.ETARTSCHALTER2 + nvl(ARTIKELLOKAL.ETARTSCHALTER2,0) ), ");
            strcat(str, "(z.ETARTSCHALTER3 + nvl(ARTIKELLOKAL.ETARTSCHALTER3,0) ), ");
            strcat(str, "(z.ETARTSCHALTER4 + nvl(ARTIKELLOKAL.ETARTSCHALTER4,0) ), ");
            strcat(str, "(z.ETARTSCHALTER5 + nvl(ARTIKELLOKAL.ETARTSCHALTER5,0) ), ");
            strcat(str, "z.HERSTELLER_NR, ");
            strcat(str, "z.WARENGRUPPEEIGEN, ");
            strcat(str, "z.THERAPIEGRUPPE, ");
            strcat(str, "z.LAENGE, ");
            strcat(str, "z.HOEHE, ");
            strcat(str, "z.BREITE, ");
            strcat(str, "z.GEWICHT, ");
            strcat(str, "z.LAUFZEITMONATE, ");
            strcat(str, "nvl(ARTIKELLOKAL.BESTAND,0), ");
            strcat(str, "nvl(ARTIKELLOKAL.NACHFRAGE,0), ");
            strcat(str, "nvl(ARTIKELLOKAL.ZUZAHLUNG,0), ");
            strcat(str, "z.ARTIKEL_NR, ");
            strcat(str, "nvl(ARTIKELLOKAL.RABATTFAEHIG,'0'), ");
            strcat(str, "nvl(ARTIKELLOKAL.ARTIKELAKTIV,'0'), ");
            strcat(str, "nvl(ARTIKELLOKAL.VERBUNDARTIKEL,'0'), ");
            strcat(str, "nvl(ARTIKELLOKAL.PRISOART,'0'), ");
            strcat(str, "z.HERSTELLER_CODE, ");
            strcat(str, "ARTIKELLOKAL.TEXTKEY, ");
            strcat(str, "nvl(ARTIKELLOKAL.KONTIGENTMENGE,0), ");
            strcat(str, "nvl(ARTIKELLOKAL.BESTANDRESERVIERT,0),");
            strcat(str, "z.STELLER,");
            strcat(str, "z.POSITIVLISTE,");
            strcat(str, "z.TAXLEVEL,");
            strcat(str, "z.ARTIKEL_LANGNAME,");
            strcat(str, "z.IMPORTARTICLE,");
            strcat(str, "ARTIKELLOKAL.WAFOTYP,");
            strcat(str, "z.DATUM_LIEFERBAR_AB,");
            strcat(str, "ARTIKELLOKAL.FILIALNR,");
            strcat(str, "z.FROZEN ");
            strcat(str, "from artikelzentral z,outer artikellokal,outer ");
            strcat(str, ARTIKELZENTRAL_SPRACHE);
            strcat(str, " c ");
            strcat(str, "where z.artikel_nr = ? ");
            if (a->IMPORTARTICLE == 0)
            {
                strcat(str, "and z.importarticle = 0 ");
            }
            else if (a->IMPORTARTICLE == 1)
            {
                strcat(str, "and z.importarticle = 1 ");
            }
            strcat(str, "and c.artikel_nr = z.artikel_nr ");
            strcat(str, "and artikellokal.artikel_nr = z.artikel_nr ");
            strcat(str, "and artikellokal.filialnr = ? ");
        }
        else
        {
            strcpy(str, "select ");
            strcat(str, "ARTIKELLOKAL.NATRASTAFFELNR, ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_MC, ");
            strcat(str, "ARTIKELZENTRAL.PACKGROESSE, ");
            strcat(str, "ARTIKELZENTRAL.DARREICHFORM, ");
            strcat(str, "ARTIKELZENTRAL.NORMPACKUNG, ");
            strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
            strcat(str, "nvl(ARTIKELLOKAL.VERKAUFEINHEIT,0), ");
            strcat(str, "nvl(ARTIKELLOKAL.CONTAINERGROESSE,0), ");
            strcat(str, "ARTIKELZENTRAL.ETARTKLASSE1, ");
            strcat(str, "0, ");
            strcat(str, "(ARTIKELZENTRAL.ETARTSCHALTER1 + nvl(ARTIKELLOKAL.ETARTSCHALTER1,0) ), ");
            strcat(str, "(ARTIKELZENTRAL.ETARTSCHALTER2 + nvl(ARTIKELLOKAL.ETARTSCHALTER2,0) ), ");
            strcat(str, "(ARTIKELZENTRAL.ETARTSCHALTER3 + nvl(ARTIKELLOKAL.ETARTSCHALTER3,0) ), ");
            strcat(str, "(ARTIKELZENTRAL.ETARTSCHALTER4 + nvl(ARTIKELLOKAL.ETARTSCHALTER4,0) ), ");
            strcat(str, "(ARTIKELZENTRAL.ETARTSCHALTER5 + nvl(ARTIKELLOKAL.ETARTSCHALTER5,0) ), ");
            strcat(str, "ARTIKELZENTRAL.HERSTELLER_NR, ");
            strcat(str, "ARTIKELZENTRAL.WARENGRUPPEEIGEN, ");
            strcat(str, "ARTIKELZENTRAL.THERAPIEGRUPPE, ");
            strcat(str, "ARTIKELZENTRAL.LAENGE, ");
            strcat(str, "ARTIKELZENTRAL.HOEHE, ");
            strcat(str, "ARTIKELZENTRAL.BREITE, ");
            strcat(str, "ARTIKELZENTRAL.GEWICHT, ");
            strcat(str, "ARTIKELZENTRAL.LAUFZEITMONATE, ");
            strcat(str, "nvl(ARTIKELLOKAL.BESTAND,0), ");
            strcat(str, "nvl(ARTIKELLOKAL.NACHFRAGE,0), ");
            strcat(str, "nvl(ARTIKELLOKAL.ZUZAHLUNG,0), ");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_NR, ");
            strcat(str, "nvl(ARTIKELLOKAL.RABATTFAEHIG,'0'), ");
            strcat(str, "nvl(ARTIKELLOKAL.ARTIKELAKTIV,'0'), ");
            strcat(str, "nvl(ARTIKELLOKAL.VERBUNDARTIKEL,'0'), ");
            strcat(str, "nvl(ARTIKELLOKAL.PRISOART,'0'), ");
            strcat(str, "ARTIKELZENTRAL.HERSTELLER_CODE, ");
            strcat(str, "ARTIKELLOKAL.TEXTKEY, ");
            strcat(str, "nvl(ARTIKELLOKAL.KONTIGENTMENGE,0), ");
            strcat(str, "nvl(ARTIKELLOKAL.BESTANDRESERVIERT,0), ");
            strcat(str, "ARTIKELZENTRAL.STELLER, ");
            strcat(str, "ARTIKELZENTRAL.POSITIVLISTE,");
            strcat(str, "ARTIKELZENTRAL.TAXLEVEL,");
            strcat(str, "ARTIKELZENTRAL.ARTIKEL_LANGNAME,");
            strcat(str, "ARTIKELZENTRAL.IMPORTARTICLE,");
            strcat(str, "ARTIKELLOKAL.WAFOTYP,");
            strcat(str, "ARTIKELZENTRAL.DATUM_LIEFERBAR_AB,");
            strcat(str, "ARTIKELLOKAL.FILIALNR,");
            strcat(str, "ARTIKELZENTRAL.FROZEN ");
            strcat(str, "from artikelzentral,outer artikellokal ");
            strcat(str, "where artikelzentral.artikel_nr = ? ");
            if (a->IMPORTARTICLE == 0)
            {
                strcat(str, "and artikelzentral.importarticle = 0 ");
            }
            else if (a->IMPORTARTICLE == 1)
            {
                strcat(str, "and artikelzentral.importarticle = 1 ");
            }
            strcat(str, "and artikellokal.artikel_nr = artikelzentral.artikel_nr ");
            strcat(str, "and artikellokal.filialnr = ? ");
        }

        EXEC SQL PREPARE dec_infartnr FROM :str;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartInf_art_nr: declare dec_infartnr %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }
    EXEC SQL EXECUTE dec_infartnr
        into ARTINF_ZEIGER(a)
        USING
        :a->ARTIKEL_NR,
        :a->FILIALNR;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartInf_art_nr select %ld", sqlca.sqlcode);
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
        return -2;
    }

    a->ARTIKEL_NR = pzn;
    if (a->ARTIKELAKTIV[0] > '2' || a->ARTIKELAKTIV[0] == 0)
        a->BESTAND = 0;

    return 0;
}

bool AatartSel_service_type_exists(const char* service_type, char * error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    const char* sql_service_type;
    char sql_result[15] = "\0";
    EXEC SQL END DECLARE SECTION;

    sql_service_type = service_type;

    EXEC SQL select order_type
    into :sql_result
    from servicetypes
    where order_type = :sql_service_type;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_service_type_exists select %d", sqlca.sqlcode);
        return false;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " AatartSel_service_type_exists - Abfrage lieferte kein Ergebnis");
        return false;
    }

    return sql_result[0] != '\0';
}

bool AatartSel_service_number_exists_and_valid(const char* service_no, const char* service_type, char * result, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    const char* sql_service_type;
    const char* sql_service_no;
    char sql_result[255] = "\0";
    EXEC SQL END DECLARE SECTION;

    sql_service_type = service_type;
    sql_service_no = service_no;

    EXEC SQL select services.name
        into : sql_result
        from services join servicetypes on servicetypes.servicetypeno = services.servicetypeno
    where servicetypes.order_type = : sql_service_type and services.service_no = :sql_service_no;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_service_number_exists_and_valid select %d", sqlca.sqlcode);
        return false;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " AatartSel_service_number_exists_and_valid - Abfrage lieferte kein Ergebnis");
        return false;
    }

    strcpy(result, sql_result);

    return sql_result[0] != '\0';
}

bool AatartSel_taxlevel_exists(const short taxlevel, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    short sql_taxlevel;
    short sql_count;
    EXEC SQL END DECLARE SECTION;

    sql_taxlevel = taxlevel;
    sql_count = 0;

    EXEC SQL select count(*)
        into : sql_count
        from taxrates
    where taxrates.taxlevel = : sql_taxlevel;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_taxlevel_exists select %d", sqlca.sqlcode);
        return false;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " AatartSel_taxlevel_exists - Abfrage lieferte kein Ergebnis");
        return false;
    }

    return sql_count > 0;
}


int AatartInf_preis(struct ARTPREIS* d, char* error_msg)
{
    long pzn;

    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTPREIS* a;
    long DATUM;
    double dAep;
    double dAvp;
    double dGrosso;
    EXEC SQL END DECLARE SECTION;

    a = d;
    pzn = a->ARTIKEL_NR;

    DATUM = AllgGetDate();
    EXEC SQL select ARTPREIS_LISTE into ARTPREIS_ZEIGER(a) from artikelpreis
    where   artikelpreis.artikel_nr = :a->ARTIKEL_NR and
            datumgueltigab <= :DATUM and
            datumgueltigbis >= :DATUM and
            preis_typ = :a->PREIS_TYP;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartInf_preis select %ld", sqlca.sqlcode);
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
        return -2;
    }
    EXEC SQL select PREISEKAPO,
                    PREISEKGROSSO,
                    PREISVKAPO
            into    :dAep,
                    :dGrosso,
                    :dAvp
            from    articleoldprice
            where   articleoldprice.articleno = :a->ARTIKEL_NR
            and     articleoldprice.branchno = :FilialNr;
    if (sqlca.sqlcode == 0)
    {
        a->PREISEKAPO = dAep;
        a->PREISVKAPO = dAvp;
        a->PREISEKGROSSO = dGrosso;
    }

    a->ARTIKEL_NR = pzn;
    return 0;
}

int AatartInf_verfall(struct ARTVERFALL* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTVERFALL* a;
    short ind;
    EXEC SQL END DECLARE SECTION;

    a = d;
    EXEC SQL select min(datumverfall) into :a->DATUMVERFALL indicator :ind
            from artikellagerort
            where   filialnr = :a->FILIALNR and
                    artikellagerort.artikel_nr = :a->ARTIKEL_NR;

    if (ind < 0)
        a->DATUMVERFALL = 0;
    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartInf_verfall select %ld", sqlca.sqlcode);
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
        return -2;
    }
    return 0;
}

int AatartLagerinf(struct ARTLAGER* d, char* error_msg)
{
    static bool fst = true;
    static long pzn;

    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTLAGER* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = false;
        pzn = a->ARTIKEL_NR;
        EXEC SQL declare Lagerinf scroll cursor with hold for
            select ARTLAGER_LISTE
            from artikellagerort
            where   artikellagerort.filialnr = :a->FILIALNR and
                    artikellagerort.artikel_nr = :a->ARTIKEL_NR;

        EXEC SQL open Lagerinf;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartLagerinf: open Lagerinf %ld", sqlca.sqlcode);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = true;
        EXEC SQL close Lagerinf;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartLagerinf: close Lagerinf %ld", sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Lagerinf into ARTLAGER_ZEIGER(a);
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartLagerinf: fetch Lagerinf %ld", sqlca.sqlcode);
        EXEC SQL close Lagerinf;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    a->ARTIKEL_NR = pzn;

    return 0;
}

//int AatartNatraaktion(struct ARTNAT *d, char *error_msg)
//{
//static int fst = 1;
//
//EXEC SQL BEGIN DECLARE SECTION;
//struct ARTNAT   *a;
//long				DATUM;
//EXEC SQL END DECLARE SECTION;
//
//a = d;
//if (fst) /* beim ersten mal oder bei neu deklarieren */
//   {
//    fst = 0;
//	DATUM = AllgGetDate();
///*	printf("datum = %ld",DATUM); */
//    EXEC SQL declare Natraaktion scroll cursor with hold for
//    select ARTNAT_LISTE
//    from artikelnatra
//    where	natrastaffelnr = :a->NATRASTAFFELNR and
//			datumgueltigab <= :DATUM and
//			datumgueltigbis >= :DATUM and
//			artikelnatra.vertriebszentrumnr = :FilialNr;
//
//
//     EXEC SQL open Natraaktion;
//     if (sqlca.sqlcode < 0 )
//      {
//       fst = 1;
//   sprintf(error_msg, " AatartNatraaktion: open Natraaktion %ld",
//         sqlca.sqlcode);
//       return -1;
//      }
//   }
//
//if(a->FETCH_REL == 0)   /* close cursor */
//  {
//     fst = 1;
//     EXEC SQL close Natraaktion;
//     if (sqlca.sqlcode < 0 )
//      {
//       sprintf(error_msg, " AatartNatraaktion: close Natraaktion %ld",
//       sqlca.sqlcode);
//       return -1;
//       }
//    return 1;
//  }
//
//EXEC SQL fetch relative :a->FETCH_REL Natraaktion into ARTNAT_ZEIGER(a);
//if (sqlca.sqlcode < 0 )
//  {
//   fst = 1;
//   sprintf(error_msg, " AatartNatraaktion: fetch Natraaktion %ld",
//   sqlca.sqlcode);
//   EXEC SQL close Natraaktion;
//   return -1;
//  }
//if (sqlca.sqlcode == SQLNOTFOUND)
//  {
//   return 1;
//  }
//
//return 0;
//}
//
//int AatartNettoaktion(struct ARTNET *d, char *error_msg)
//{
//static int fst = 1;
//static long pzn;
//
//EXEC SQL BEGIN DECLARE SECTION;
//struct ARTNET   *a;
//long	DATUM;
//EXEC SQL END DECLARE SECTION;
//
//a = d;
//if (fst) /* beim ersten mal oder bei neu deklarieren */
//   {
//    fst = 0;
//	DATUM = AllgGetDate();
//	pzn = a->ARTIKEL_NR;
//    EXEC SQL declare Nettoaktion scroll cursor with hold for
//    select ARTNET_LISTE
//    from artikelmgpreis
//    where	artikelmgpreis.artikel_nr = :a->ARTIKEL_NR and
//			datumgueltigab <= :DATUM and
//			datumgueltigbis >= :DATUM and
//			artikelmgpreis.vertriebszentrumnr = :FilialNr;
//
//     EXEC SQL open Nettoaktion;
//     if (sqlca.sqlcode < 0 )
//      {
//       fst = 1;
//   sprintf(error_msg, " AatartNettoaktion: open Nettoaktion %ld",
//         sqlca.sqlcode);
//       return -1;
//      }
//   }
//
//if(a->FETCH_REL == 0)   /* close cursor */
//  {
//     fst = 1;
//     EXEC SQL close Nettoaktion;
//     if (sqlca.sqlcode < 0 )
//      {
//       sprintf(error_msg, " AatartNettoaktion: close Nettoaktion %ld",
//       sqlca.sqlcode);
//       return -1;
//       }
//    return 1;
//  }
//
//EXEC SQL fetch relative :a->FETCH_REL Nettoaktion into ARTNET_ZEIGER(a);
//if (sqlca.sqlcode < 0 )
//  {
//   fst = 1;
//   sprintf(error_msg, " AatartNettoaktion: fetch Nettoaktion %ld",
//   sqlca.sqlcode);
//   EXEC SQL close Nettoaktion;
//   return -1;
//  }
//if (sqlca.sqlcode == SQLNOTFOUND)
//  {
//   return 1;
//  }
//a->ARTIKEL_NR = pzn;
//
//return 0;
//}

/*** AatartAa_sel_artnr (Eindeutiger Zugriff über PZN) ************************/

int AatartAa_sel_artnr(struct ARTAESEL *d, char *error_msg)
{
    static int FREMDSPRACHE_ALT = 2;
    static int SHORT = 0;
    static int SHORT_ALT = 2;
    static char cFrText;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTAESEL   *a;
    long DATUM;
    char aktiv[2];
    char str[2048];
    short sTextKey;
    char cTexte[500];
    char cCountryText[31];
    double dAep;
    EXEC SQL END DECLARE SECTION;

    a = d;
    DATUM = AllgGetDate();

    cFrText = a->CODEBLOCAGE[0];

    if (strncmp(a->PHARMACYGROUPID, "   ", L_ARTAESEL_PHARMACYGROUPID))
    {
        SHORT = 0;
    }
    else
    {
        SHORT = 1;
    }
    if (FREMDSPRACHE != FREMDSPRACHE_ALT || SHORT != SHORT_ALT)
    {
        SHORT_ALT = SHORT;
        FREMDSPRACHE_ALT = FREMDSPRACHE;
        EXEC SQL free pre_artnr;
        EXEC SQL free CAa_sel_artnr;
        if (FREMDSPRACHE)
        {
            strcpy(str, "select z.ARTIKEL_NR,");
            strcat(str, "nvl(c.ARTIKEL_MC,z.ARTIKEL_MC), ");
            strcat(str, "z.PACKGROESSE,");
            strcat(str, "nvl(c.DARREICHFORM,z.DARREICHFORM), ");
            strcat(str, "nvl(c.EINHEIT,z.EINHEIT), ");
            strcat(str, "nvl(c.ARTIKEL_NAME,z.ARTIKEL_NAME), ");
            strcat(str, "artikellagerort.DATUMVERFALL,");
            strcat(str, "( z.ETARTSCHALTER1 + nvl(artikellokal.ETARTSCHALTER1,0) ),");
            strcat(str, "( z.ETARTSCHALTER2 + nvl(artikellokal.ETARTSCHALTER2,0) ),");
            strcat(str, "( z.ETARTSCHALTER3 + nvl(artikellokal.ETARTSCHALTER3,0) ),");
            strcat(str, "( z.ETARTSCHALTER4 + nvl(artikellokal.ETARTSCHALTER4,0) ),");
            strcat(str, "( z.ETARTSCHALTER5 + nvl(artikellokal.ETARTSCHALTER5,0) ),");
            strcat(str, "artikellokal.PRISOART,");
            strcat(str, "artikelpreis.PREISEKAPO,");
            strcat(str, "artikelpreis.PREISEKGROSSO,");
            strcat(str, "artikelpreis.PREISEKGROSSONA,");
            strcat(str, "artikellokal.BESTAND,");
            strcat(str, "z.ETARTKLASSE1,");
            strcat(str, "artikellokal.artikelaktiv,");
            strcat(str, "artikellokal.chargenartikel,");
            strcat(str, "z.hersteller_code,");
            strcat(str, "artikellokal.wafotyp, ");
            strcat(str, "artikellokal.NATRASTAFFELNR, ");
            strcat(str, "artikellokal.TEXTKEY, ");
            strcat(str, "z.TEXTKEY_HOSPITAL, ");
            strcat(str, "artikellokal.CODEBLOCAGE, ");
            strcat(str, "z.POSITIVLISTE, ");
            strcat(str, "z.HEALTHFUNDCODE, ");
            strcat(str, "z.ARTIKEL_LANGNAME, ");
            strcat(str, "z.TAXLEVEL, ");
            strcat(str, "z.KZPSYCHOSTOFFE, ");
            strcat(str, "z.PRODUSERQUOTA, ");
            strcat(str, "artikellokal.ARTIKELAKTIV, ");
            strcat(str, "z.ARTIKEL_GESPERRT, ");
            strcat(str, "z.IMPORTARTICLE, ");
            strcat(str, "z.TFG, ");
            strcat(str, "z.KONTINGENT_PPE, ");
            strcat(str, "z.MEDIZINPRODUKT,");
            strcat(str, "z.FROZEN,");
            strcat(str, "z.ABDACODE ");
            strcat(str, "from ");
            strcat(str, "artikelzentral z,");
            strcat(str, "artikelpreis,");
            strcat(str, "artikellokal,");
            strcat(str, "outer artikellagerort, outer ");
            strcat(str, ARTIKELZENTRAL_SPRACHE);
            strcat(str, " c ");
            strcat(str, "where ");
            strcat(str, "z.artikel_nr = ? and ");
            strcat(str, "c.artikel_nr = z.artikel_nr and ");
            strcat(str, "artikelpreis.artikel_nr = z.artikel_nr and ");
            strcat(str, "artikelpreis.datumgueltigab <= ? and ");
            strcat(str, "artikelpreis.datumgueltigbis >= ? and ");
            strcat(str, "artikelpreis.preis_typ=0 and " );
            strcat(str, "artikellagerort.artikel_nr = z.artikel_nr and ");
            strcat(str, "artikellagerort.filialnr = ? and ");
            strcat(str, "artikellokal.artikel_nr = z.artikel_nr and ");
            strcat(str, "artikellokal.filialnr = ? ");
            if (cFrText != '1')
            {
                strcat(str, "and artikellokal.artikelaktiv != 0 ");
            }
            if (strncmp(a->PHARMACYGROUPID, "   ", L_ARTAESEL_PHARMACYGROUPID))
            {
                strcat(str, "and artikellokal.artikel_nr in  ");
                strcat(str, "(select d.articleno from discount d ");
                strcat(str, "where d.pharmacygroupid = '");
                strncat(str, a->PHARMACYGROUPID, L_ARTAESEL_PHARMACYGROUPID);
                strcat(str, "' and d.branchno = artikellokal.filialnr ");
                strcat(str, "and d.discounttype in ( ");
                strcat(str, "select discounttype from discountordertyp ");
                strcat(str, "where discountordertyp.kdauftragart = '");
                strcat(str, cKdauftragArt);
                strcat(str, "' ) ) ");
            }
            strcat(str, "and z.positivliste >= ? ");
            strcat(str, "and bitand(z.etartklasse1, ? ) = z.etartklasse1 ");
            if (FilialNr == 48)
                AatartIvrylab("z", a->PHARMACYGROUPID);
        }
        else
        {
            strcpy(str, "select artikelzentral.ARTIKEL_NR,");
            strcat(str, "artikelzentral.ARTIKEL_MC,");
            strcat(str, "artikelzentral.PACKGROESSE,");
            strcat(str, "artikelzentral.DARREICHFORM,");
            strcat(str, "artikelzentral.EINHEIT,");
            strcat(str, "artikelzentral.ARTIKEL_NAME,");
            strcat(str, "artikellagerort.DATUMVERFALL,");
            strcat(str, "( artikelzentral.ETARTSCHALTER1 + nvl(artikellokal.ETARTSCHALTER1,0) ),");
            strcat(str, "( artikelzentral.ETARTSCHALTER2 + nvl(artikellokal.ETARTSCHALTER2,0) ),");
            strcat(str, "( artikelzentral.ETARTSCHALTER3 + nvl(artikellokal.ETARTSCHALTER3,0) ),");
            strcat(str, "( artikelzentral.ETARTSCHALTER4 + nvl(artikellokal.ETARTSCHALTER4,0) ),");
            strcat(str, "( artikelzentral.ETARTSCHALTER5 + nvl(artikellokal.ETARTSCHALTER5,0) ),");
            strcat(str, "artikellokal.PRISOART,");
            strcat(str, "artikelpreis.PREISEKAPO,");
            strcat(str, "artikelpreis.PREISEKGROSSO,");
            strcat(str, "artikelpreis.PREISEKGROSSONA,");
            strcat(str, "artikellokal.BESTAND,");
            strcat(str, "artikelzentral.ETARTKLASSE1,");
            strcat(str, "artikellokal.artikelaktiv,");
            strcat(str, "artikellokal.chargenartikel,");
            strcat(str, "artikelzentral.hersteller_code,");
            strcat(str, "artikellokal.wafotyp, ");
            strcat(str, "artikellokal.NATRASTAFFELNR, ");
            strcat(str, "artikellokal.TEXTKEY, ");
            strcat(str, "artikelzentral.TEXTKEY_HOSPITAL, ");
            strcat(str, "artikellokal.CODEBLOCAGE, ");
            strcat(str, "artikelzentral.POSITIVLISTE, ");
            strcat(str, "artikelzentral.HEALTHFUNDCODE, ");
            strcat(str, "artikelzentral.ARTIKEL_LANGNAME, ");
            strcat(str, "artikelzentral.TAXLEVEL, ");
            strcat(str, "artikelzentral.KZPSYCHOSTOFFE, ");
            strcat(str, "artikelzentral.PRODUSERQUOTA, ");
            strcat(str, "artikellokal.ARTIKELAKTIV, ");
            strcat(str, "artikelzentral.ARTIKEL_GESPERRT, ");
            strcat(str, "artikelzentral.IMPORTARTICLE, ");
            strcat(str, "artikelzentral.TFG, ");
            strcat(str, "artikelzentral.KONTINGENT_PPE, ");
            strcat(str, "artikelzentral.MEDIZINPRODUKT,");
            strcat(str, "artikelzentral.FROZEN,");
            strcat(str, "artikelzentral.ABDACODE ");
            strcat(str, "from ");
            strcat(str, "artikelzentral,");
            strcat(str, "artikelpreis,");
            strcat(str, "artikellokal,");
            strcat(str, "outer artikellagerort ");

            strcat(str, "where ");
            strcat(str, "artikelzentral.artikel_nr = ? and ");
            strcat(str, "artikelpreis.artikel_nr = artikelzentral.artikel_nr and ");
            strcat(str, "artikelpreis.datumgueltigab <= ? and ");
            strcat(str, "artikelpreis.datumgueltigbis >= ? and ");
            strcat(str, "artikelpreis.preis_typ=0 and " );
            strcat(str, "artikellagerort.artikel_nr = artikelzentral.artikel_nr and ");
            strcat(str, "artikellagerort.filialnr = ? and ");
            strcat(str, "artikellokal.artikel_nr = artikelzentral.artikel_nr and ");
            strcat(str, "artikellokal.filialnr = ? ");
            if (cFrText != '1')
            {
                strcat(str, "and artikellokal.artikelaktiv != 0 ");
            }
            if (strncmp(a->PHARMACYGROUPID, "   ", L_ARTAESEL_PHARMACYGROUPID))
            {
                strcat(str, "and artikellokal.artikel_nr in  ");
                strcat(str, "(select d.articleno from discount d ");
                strcat(str, "where d.pharmacygroupid = '");
                strncat(str, a->PHARMACYGROUPID, L_ARTAESEL_PHARMACYGROUPID);
                strcat(str, "' and d.branchno = artikellokal.filialnr ");
                strcat(str, "and d.discounttype in ( ");
                strcat(str, "select discounttype from discountordertyp ");
                strcat(str, "where discountordertyp.kdauftragart = '");
                strcat(str, cKdauftragArt);
                strcat(str, "' ) ) ");
            }
            strcat(str, "and artikelzentral.positivliste >= ? ");
            strcat(str, "and bitand(artikelzentral.etartklasse1, ? ) = artikelzentral.etartklasse1 ");
            if (FilialNr == 48)
                AatartIvrylab("artikelzentral", a->PHARMACYGROUPID);
        }

        EXEC SQL prepare pre_artnr from :str;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, "prepare pre_artnr %ld/%ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        EXEC SQL declare CAa_sel_artnr cursor with hold for pre_artnr;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, "declare CAa_sel_artnr %ld/%ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
    }
    EXEC SQL open CAa_sel_artnr
        using
        :a->ARTIKEL_NR,
        :DATUM,
        :DATUM,
        :a->FILIALNR,
        :a->FILIALNR,
        :a->POSITIVLISTE,
        :a->ETARTKLASSE1;
    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, "open CAa_sel_artnr %ld/%ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }

    EXEC SQL fetch CAa_sel_artnr
    into    :a->ARTIKEL_NR,
            :a->ARTIKEL_MC,
            :a->PACKGROESSE,
            :a->DARREICHFORM,
            :a->EINHEIT,
            :a->ARTIKEL_NAME,
            :a->DATUMVERFALL,
            :a->ETARTSCHALTER1,
            :a->ETARTSCHALTER2,
            :a->ETARTSCHALTER3,
            :a->ETARTSCHALTER4,
            :a->ETARTSCHALTER5,
            :a->PRISOART,
            :a->PREISEKAPO,
            :a->PREISEKGROSSO,
            :a->PREISEKGROSSONA,
            :a->BESTAND,
            :a->ETARTKLASSE1,
            :aktiv,
            :a->CHARGENARTIKEL,
            :a->HERSTELLER_CODE,
            :a->WAFOTYP,
            :a->NATRASTAFFELNR,
            :sTextKey,
            :a->TEXTKEY_HOSPITAL,
            :a->CODEBLOCAGE,
            :a->POSITIVLISTE,
            :a->HEALTHFUNDCODE,
            :a->ARTIKEL_LANGNAME,
            :a->TAXLEVEL,
            :a->KZPSYCHOSTOFFE,
            :a->PRODUSERQUOTA,
            :a->ARTIKELAKTIV,
            :a->ARTIKEL_GESPERRT,
            :a->IMPORTARTICLE,
            :a->TFG,
            :a->KONTINGENT_PPE,
            :a->MEDIZINPRODUKT,
            :a->FROZEN,
            :a->ABDACODE;
    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, "fetch CAa_sel_artnr %ld/%ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
        return -2;
    }
    else if (aktiv[0] > '2' || aktiv[0] == '0')
    {
        a->BESTAND = 0;
    }

    a->TEXT[0] = '\0';
    cTexte[0] = '\0';

    if (!strcmp(cCountry, "CH"))
    {
        EXEC SQL select texthospital
            into :a->TEXT
            from articletext
            where textkey = :a->TEXTKEY_HOSPITAL;
    }

    if (cFrText == '1')
    {
        if (a->BESTAND == 0)
        {
            EXEC SQL select printcode
                into :cCountryText
                from countrycodes
                where branchno = :FilialNr
                and infocode = :a->CODEBLOCAGE;
        }
        else
        {
            cCountryText[0] = '\0';
        }
    }
    if (sTextKey != 0)
    {
        if (cFrText == '1')
        {
            EXEC SQL select texthospital
                into :cTexte
                from articletext
                where textkey = :sTextKey;
                sprintf(a->TEXT, "%5.5s %234.234s", cCountryText, cTexte);
        }
        else
        {
            EXEC SQL select text
                into :a->TEXT
                from articletext
                where textkey = :sTextKey;
        }
    }
    if (cFrText == '1')
    {
        sprintf(a->TEXT, "%5.5s %234.234s", cCountryText, cTexte);
    }
    EXEC SQL select PREISEKAPO
        into    :dAep
        from    articleoldprice
        where   articleoldprice.articleno = :a->ARTIKEL_NR
        and     articleoldprice.branchno = :a->FILIALNR;
    if (sqlca.sqlcode == 0)
    {
        a->PREISEKAPO = dAep;
    }

//	AatartCheck_natra(a, error_msg);
//	AatartCheck_mgpreis(a, error_msg);
    if (a->CODE_TYPE == 0)
        AatartSel_Preferred(a, error_msg);
    return 0;
}

/*** AatartSel_art_altern (Matchcode suche incl. Packungsgrösse) *******************/

int AatartSel_art_altern(struct ARTALT* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTALT* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    EXEC SQL select MAX(ARTIKEL_NR_ALTERN)
            into :a->ARTIKEL_NR_ALTERN
            from artikelaltern
            where   artikel_nr = :a->ARTIKEL_NR and
                    artikelaltern.filialnr = :FilialNr;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_art_altern select %ld", sqlca.sqlcode);
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, TXT_KEIN_ALT_ART);
        return -2;
    }

    return 0;
}

int AatartSel_hersteller(struct ARTINFHERSTE* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTINFHERSTE* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    EXEC SQL select ARTINFHERSTE_LISTE into ARTINFHERSTE_ZEIGER(a)
        from herstel HERSTEL
        where HERSTEL.HERSTELLER_NR = :a->HERSTELLER_NR;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_hersteller select %ld", sqlca.sqlcode);
        return 1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        strcpy(error_msg, " Abfrage lieferte kein Ergebnis");
        return -2;
    }
    return 0;
}

int AatartSel_offene_bstlng(struct ARTINFBESTEL* d, char* error_msg)
{
    static bool fst = true;
    static long pzn;

    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTINFBESTEL* a;
    long DATUM;
    char wirksam[2];
    EXEC SQL END DECLARE SECTION;

    a = d;
    DATUM = AllgGetDate();
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = false;
        pzn = a->ARTIKEL_NR;
        EXEC SQL declare Sel_offene_bstlng scroll cursor with hold for
            select  ARTINFBESTEL_LISTE, BESKOPF.BEST_WIRKSAM
            from    BESPOSI,
                    BESKOPF,
                    artikelzentral
            where   artikelzentral.artikel_nr = :a->ARTIKEL_NR and
                    BESPOSI.ARTIKEL_NR = artikelzentral.ARTIKEL_NR and
                    BESKOPF.BESTELL_NR = BESPOSI.BESTELL_NR and
                    BESKOPF.FILIALNR = :FilialNr and
                    BESPOSI.FILIALNR = :FilialNr and
                    (
                        BESKOPF.STATUS_AKT = 'A' or
                        (BESKOPF.STATUS_AKT = 'a' and BESKOPF.STATUS_NEU = 'Y') or
                        BESKOPF.DATUM_WE = :DATUM
                    )
            order by BESKOPF.DATUM_WE_SOLL;

        EXEC SQL open Sel_offene_bstlng;
        if (sqlca.sqlcode == -936 || sqlca.sqlcode == -908 || sqlca.sqlcode == -329)    /* fuze1 nicht erreichbar */
        {
            return 1;
        }
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartSel_offene_bstlng: open Sel_offene_bstlng %ld", sqlca.sqlcode);
            return 1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = true;
        EXEC SQL close Sel_offene_bstlng;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartSel_offene_bstlng: close Sel_offene_bstlng %ld", sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_offene_bstlng
        into ARTINFBESTEL_ZEIGER(a), :wirksam;
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartSel_offene_bstlng: fetch Sel_offene_bstlng %ld", sqlca.sqlcode);
        EXEC SQL close Sel_offene_bstlng;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    if (wirksam[0] == '1')
        a->BEST_WIRKSAM[0] = '1';
    else if (wirksam[0] == '0')
        a->BEST_WIRKSAM[0] = '0';
    a->ARTIKEL_NR = pzn;
    return 0;
}

int AatartAa_sel_index(struct ARTAESEL* d, char* error_msg)
{
    static bool fst = true;
    int iMax = 3;
    static int FREMDSPRACHE_ALT = 2;
    static int SHORT = 0;
    static int SHORT_ALT = 2;
    static char cFrText;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTAESEL* a;
    char NORMPACKUNG[5];
    long DATUM;
    char aktiv[2];
    char* arrArtikelName[L_ARTSEL_ARTIKEL_NAME + 2]; // ppGGetWhereFromStr requires 'const' but EXEC SQL not!
    short sTextKey;
    char cTexte[500];
    char cCountryText[31];
    double dAep;
    EXEC SQL END DECLARE SECTION;

    a = d;
    DATUM = AllgGetDate();
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = false;

        cFrText = a->CODEBLOCAGE[0];

        AllgMakeToLike(a->ARTIKEL_MC, L_ARTSEL_ARTIKEL_MC);
        AllgMakeToLike(a->DARREICHFORM, L_ARTSEL_DARREICHFORM);
        AllgMakeToLike(a->HERSTELLER_CODE, L_ARTSEL_HERSTELLER_CODE);

        ppGGetWhereFromStr(PPG_STATIC, a->ARTIKEL_NAME, (char*)0, (char*)0, (const char**)arrArtikelName, iMax);

        HandleNormPackage(NORMPACKUNG, a->NORMPACKUNG, "%");

        SHORT = HandlePharmacyGroupID(a->PHARMACYGROUPID);

        if (FREMDSPRACHE != FREMDSPRACHE_ALT || SHORT != SHORT_ALT)
        {
            SHORT_ALT = SHORT;
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            EXEC SQL free Aa_sel_index;
            EXEC SQL free dec_index;
            EXEC SQL free sel_tmpindex;
            EXEC SQL drop table tmpausgab1;
            EXEC SQL create temp table tmpausgab1(ARTIKEL_NR INTEGER);
            if (FREMDSPRACHE)
            {
                strcpy(str, "insert into tmpausgab1 ");
                strcat(str, "select ");
                strcat(str, "unique c.artikel_nr ");
                strcat(str, "from ");
                strcat(str, ARTIKELINDEX_SPRACHE);
                strcat(str, " c ");
                strcat(str, "where ");
                strcat(str, "c.suchbezeichner like ? ");
            }
            else
            {
                strcpy(str, "insert into tmpausgab1 ");
                strcat(str, "select ");
                strcat(str, "unique artikel_nr ");
                strcat(str, "from artikelindex ");
                strcat(str, "where ");
                strcat(str, "artikelindex.suchbezeichner like ? ");
            }

            EXEC SQL PREPARE sel_tmpindex FROM :str;
            if (sqlca.sqlcode < 0)
            {
                fst = true;
                sprintf(error_msg, " AatartAa_sel_index: declare sel_tmpindex %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            if (FREMDSPRACHE)
            {
                strcpy(str, "select ");
                strcat(str, "unique ");
                strcat(str, "z.ARTIKEL_NR, ");
                strcat(str, "c.ARTIKEL_MC, ");
                strcat(str, "z.PACKGROESSE, ");
                strcat(str, "c.DARREICHFORM, ");
                strcat(str, "c.EINHEIT, ");
                strcat(str, "c.ARTIKEL_NAME, ");
                strcat(str, "artikellagerort.DATUMVERFALL, ");
                strcat(str, "( z.ETARTSCHALTER1 + nvl(artikellokal.ETARTSCHALTER1,0) ), ");
                strcat(str, "( z.ETARTSCHALTER2 + nvl(artikellokal.ETARTSCHALTER2,0) ), ");
                strcat(str, "( z.ETARTSCHALTER3 + nvl(artikellokal.ETARTSCHALTER3,0) ), ");
                strcat(str, "( z.ETARTSCHALTER4 + nvl(artikellokal.ETARTSCHALTER4,0) ), ");
                strcat(str, "artikellokal.PRISOART, ");
                strcat(str, "artikelpreis.PREISEKAPO, ");
                strcat(str, "artikelpreis.PREISEKGROSSO, ");
                strcat(str, "artikelpreis.PREISEKGROSSONA, ");
                strcat(str, "artikellokal.BESTAND, ");
                strcat(str, "z.ETARTKLASSE1, ");
                strcat(str, "artikellokal.artikelaktiv, ");
                strcat(str, "artikellokal.chargenartikel, ");
                strcat(str, "z.hersteller_code, ");
                strcat(str, "artikellokal.wafotyp, ");
                strcat(str, "artikellokal.NATRASTAFFELNR, ");
                strcat(str, "artikellokal.TEXTKEY, ");
                strcat(str, "z.TEXTKEY_HOSPITAL, ");
                strcat(str, "artikellokal.CODEBLOCAGE, ");
                strcat(str, "z.POSITIVLISTE, ");
                strcat(str, "z.HEALTHFUNDCODE, ");
                strcat(str, "z.ARTIKEL_LANGNAME, ");
                strcat(str, "z.TAXLEVEL, ");
                strcat(str, "z.KZPSYCHOSTOFFE, ");
                strcat(str, "z.PRODUSERQUOTA ");
                strcat(str, "from artikelzentral z, ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c, ");
                strcat(str, "tmpausgab1, ");
                strcat(str, "artikelpreis, ");
                strcat(str, "artikellagerort, ");
                strcat(str, "artikellokal ");
                strcat(str, "where c.darreichform like ? and ");
                strcat(str, "artikellokal.bestand >= ? and ");
                strcat(str, "c.artikel_name[27,30] like ? and ");
                strcat(str, "c.artikel_name like ? and ");
                strcat(str, "c.artikel_name like ? and ");
                strcat(str, "c.artikel_name like ? ");
                strcat(str, "and z.artikel_nr = tmpausgab1.artikel_nr ");
                strcat(str, "and c.artikel_nr = tmpausgab1.artikel_nr ");
                strcat(str, "and z.artikel_nr = c.artikel_nr and ");
                strcat(str, "artikelpreis.artikel_nr = z.artikel_nr and ");
                strcat(str, "artikelpreis.datumgueltigab <= ? and ");
                strcat(str, "artikelpreis.datumgueltigbis >= ? and ");
                strcat(str, "artikelpreis.preis_typ=0 and ");
                strcat(str, "artikellagerort.artikel_nr = c.artikel_nr and ");
                strcat(str, "artikellagerort.filialnr = ? and ");
                strcat(str, "artikellokal.artikel_nr = c.artikel_nr and ");
                strcat(str, "artikellokal.filialnr = ? and ");
                strcat(str, "z.hersteller_code like ? ");
                if (cFrText != '1')
                {
                    strcat(str,"and artikellokal.artikelaktiv != 0 ");
                }
                if (strncmp(a->PHARMACYGROUPID, "   ", L_ARTAESEL_PHARMACYGROUPID))
                {
                    strcat(str, "and tmpausgab1.artikel_nr in  ");
                    strcat(str, "(select d.articleno from discount d ");
                    strcat(str, "where d.pharmacygroupid = '");
                    strncat(str, a->PHARMACYGROUPID, L_ARTAESEL_PHARMACYGROUPID);
                    strcat(str, "' and d.branchno = artikellokal.filialnr ");
                    strcat(str, "and d.discounttype in ( ");
                    strcat(str, "select discounttype from discountordertyp ");
                    strcat(str, "where discountordertyp.kdauftragart = '");
                    strcat(str, cKdauftragArt);
                    strcat(str, "' ) ) ");
                }
                strcat(str, "and z.positivliste >= ? ");
                strcat(str, "and bitand(z.etartklasse1, ? ) = z.etartklasse1 ");
                if (FilialNr == 48)
                    AatartIvrylab("z", a->PHARMACYGROUPID);
                if (!strcmp(cCountry, "BG"))
                {
                    strcat(str, "order by z.artikel_langname[1,26] ");
                }
                else
                {
                    strcat(str, "order by c.artikel_name[1,26] ");
                }
            }
            else
            {
                strcpy(str, "select ");
                strcat(str, "unique ");
                strcat(str, "artikelzentral.ARTIKEL_NR, ");
                strcat(str, "artikelzentral.ARTIKEL_MC, ");
                strcat(str, "artikelzentral.PACKGROESSE, ");
                strcat(str, "artikelzentral.DARREICHFORM, ");
                strcat(str, "artikelzentral.EINHEIT, ");
                strcat(str, "artikelzentral.ARTIKEL_NAME, ");
                strcat(str, "artikellagerort.DATUMVERFALL, ");
                strcat(str, "( artikelzentral.ETARTSCHALTER1 + nvl(artikellokal.ETARTSCHALTER1,0) ), ");
                strcat(str, "( artikelzentral.ETARTSCHALTER2 + nvl(artikellokal.ETARTSCHALTER2,0) ), ");
                strcat(str, "( artikelzentral.ETARTSCHALTER3 + nvl(artikellokal.ETARTSCHALTER3,0) ), ");
                strcat(str, "( artikelzentral.ETARTSCHALTER4 + nvl(artikellokal.ETARTSCHALTER4,0) ), ");
                strcat(str, "artikellokal.PRISOART, ");
                strcat(str, "artikelpreis.PREISEKAPO, ");
                strcat(str, "artikelpreis.PREISEKGROSSO, ");
                strcat(str, "artikelpreis.PREISEKGROSSONA, ");
                strcat(str, "artikellokal.BESTAND, ");
                strcat(str, "artikelzentral.ETARTKLASSE1, ");
                strcat(str, "artikellokal.artikelaktiv, ");
                strcat(str, "artikellokal.chargenartikel, ");
                strcat(str, "artikelzentral.hersteller_code, ");
                strcat(str, "artikellokal.wafotyp, ");
                strcat(str, "artikellokal.NATRASTAFFELNR, ");
                strcat(str, "artikellokal.TEXTKEY, ");
                strcat(str, "artikelzentral.TEXTKEY_HOSPITAL, ");
                strcat(str, "artikellokal.CODEBLOCAGE, ");
                strcat(str, "artikelzentral.POSITIVLISTE, ");
                strcat(str, "artikelzentral.HEALTHFUNDCODE, ");
                strcat(str, "artikelzentral.ARTIKEL_LANGNAME, ");
                strcat(str, "artikelzentral.TAXLEVEL, ");
                strcat(str, "artikelzentral.KZPSYCHOSTOFFE, ");
                strcat(str, "artikelzentral.PRODUSERQUOTA ");
                strcat(str, "from artikelzentral,tmpausgab1,artikelpreis,artikellagerort,artikellokal ");
                strcat(str, "where darreichform like ? and ");
                strcat(str, "artikellokal.bestand >= ? and ");
                strcat(str, "artikel_name[27,30] like ? and ");
                strcat(str, "artikel_name like ? and ");
                strcat(str, "artikel_name like ? and ");
                strcat(str, "artikel_name like ? ");
                strcat(str, "and artikelzentral.artikel_nr = tmpausgab1.artikel_nr and ");
                strcat(str, "artikelpreis.artikel_nr = artikelzentral.artikel_nr and ");
                strcat(str, "artikelpreis.datumgueltigab <= ? and ");
                strcat(str, "artikelpreis.datumgueltigbis >= ? and ");
                strcat(str, "artikelpreis.preis_typ=0 and ");
                strcat(str, "artikellagerort.artikel_nr = artikelzentral.artikel_nr and ");
                strcat(str, "artikellagerort.filialnr = ? and ");
                strcat(str, "artikellokal.artikel_nr = artikelzentral.artikel_nr and ");
                strcat(str, "artikellokal.filialnr = ? and ");
                strcat(str, "artikelzentral.hersteller_code like ? ");
                if (cFrText != '1')
                {
                    strcat(str, "and artikellokal.artikelaktiv != 0 ");
                }
                if (strncmp(a->PHARMACYGROUPID, "   ", L_ARTAESEL_PHARMACYGROUPID))
                {
                    strcat(str, "and tmpausgab1.artikel_nr in  ");
                    strcat(str, "(select d.articleno from discount d ");
                    strcat(str, "where d.pharmacygroupid = '");
                    strncat(str, a->PHARMACYGROUPID, L_ARTAESEL_PHARMACYGROUPID);
                    strcat(str, "' and d.branchno = artikellokal.filialnr ");
                    strcat(str, "and d.discounttype in ( ");
                    strcat(str, "select discounttype from discountordertyp ");
                    strcat(str, "where discountordertyp.kdauftragart = '");
                    strcat(str, cKdauftragArt);
                    strcat(str, "' ) ) ");
                }
                strcat(str, "and artikelzentral.positivliste >= ? ");
                strcat(str, "and bitand(artikelzentral.etartklasse1, ? ) = artikelzentral.etartklasse1 ");
                if (FilialNr == 48)
                    AatartIvrylab("artikelzentral", a->PHARMACYGROUPID);
                if (!strcmp(cCountry, "BG"))
                {
                    strcat(str, "order by artikel_langname[1,26] ");
                }
                else
                {
                    strcat(str, "order by artikel_name[1,26] ");
                }
            }

            EXEC SQL PREPARE dec_index FROM :str;
            if (sqlca.sqlcode < 0)
            {
                fst = true;
                sprintf(error_msg, " AatartAa_sel_index: declare dec_index %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Aa_sel_index scroll cursor with hold for dec_index;
        }

        EXEC SQL delete from tmpausgab1;
        EXEC SQL execute sel_tmpindex
            using
            :a->ARTIKEL_MC;

        EXEC SQL open Aa_sel_index
            using
            :a->DARREICHFORM,
            :a->BESTAND,
            :NORMPACKUNG,
            :arrArtikelName[0],
            :arrArtikelName[1],
            :arrArtikelName[2],
            :DATUM,
            :DATUM,
            :a->FILIALNR,
            :FilialNr,
            :a->HERSTELLER_CODE,
            :a->POSITIVLISTE,
            :a->ETARTKLASSE1;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartAa_sel_index: open Aa_sel_index %ld", sqlca.sqlcode);
            return -1;
        }
   }

   if (a->FETCH_REL == 0)
   {
       fst = true;
       EXEC SQL close Aa_sel_index;
       if (sqlca.sqlcode < 0)
       {
           sprintf(error_msg, " AatartAa_sel_index: close Aa_sel_index %ld", sqlca.sqlcode);
           return -1;
       }
       return 1;
   }

    EXEC SQL fetch relative :a->FETCH_REL Aa_sel_index
        into
        :a->ARTIKEL_NR,
        :a->ARTIKEL_MC,
        :a->PACKGROESSE,
        :a->DARREICHFORM,
        :a->EINHEIT,
        :a->ARTIKEL_NAME,
        :a->DATUMVERFALL,
        :a->ETARTSCHALTER1,
        :a->ETARTSCHALTER2,
        :a->ETARTSCHALTER3,
        :a->ETARTSCHALTER4,
        :a->PRISOART,
        :a->PREISEKAPO,
        :a->PREISEKGROSSO,
        :a->PREISEKGROSSONA,
        :a->BESTAND,
        :a->ETARTKLASSE1,
        :aktiv,
        :a->CHARGENARTIKEL,
        :a->HERSTELLER_CODE,
        :a->WAFOTYP,
        :a->NATRASTAFFELNR,
        :sTextKey,
        :a->TEXTKEY_HOSPITAL,
        :a->CODEBLOCAGE,
        :a->POSITIVLISTE,
        :a->HEALTHFUNDCODE,
        :a->ARTIKEL_LANGNAME,
        :a->TAXLEVEL,
        :a->KZPSYCHOSTOFFE,
        :a->PRODUSERQUOTA;
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartAa_sel_index: fetch Aa_sel_index %ld", sqlca.sqlcode);
        EXEC SQL close Aa_sel_index;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    else if (aktiv[0] > '2' || aktiv[0] == '0')
    {
        a->BESTAND = 0;
    }

    a->TEXT[0] = '\0';
    cTexte[0] = '\0';

    if (!strcmp(cCountry, "CH"))
    {
        EXEC SQL select texthospital
            into :a->TEXT
            from  articletext
            where textkey = :a->TEXTKEY_HOSPITAL;
    }

    if (cFrText == '1')
    {
        if (a->BESTAND == 0)
        {
            EXEC SQL select printcode
                into :cCountryText
                from  countrycodes
                where branchno = :FilialNr
                and   infocode = :a->CODEBLOCAGE;
        }
        else
        {
            cCountryText[0] = '\0';
        }
    }
    if (sTextKey != 0)
    {
        if (cFrText == '1')
        {
            EXEC SQL select texthospital
                into :cTexte
                from articletext
                where textkey = :sTextKey;
            sprintf(a->TEXT, "%5.5s %234.234s", cCountryText, cTexte);
        }
        else
        {
            EXEC SQL select text
                into :a->TEXT
                from articletext
                where textkey = :sTextKey;
        }
    }
    if (cFrText == '1')
    {
        sprintf(a->TEXT, "%5.5s %234.234s", cCountryText, cTexte);
    }
    EXEC SQL select PREISEKAPO
        into    :dAep
        from    articleoldprice
        where   articleoldprice.articleno = :a->ARTIKEL_NR
        and     articleoldprice.branchno = :a->FILIALNR;
    if (sqlca.sqlcode == 0)
    {
        a->PREISEKAPO = dAep;
    }

    //AatartCheck_natra(a, error_msg);
    //AatartCheck_mgpreis(a, error_msg);
    AatartSel_Preferred(a, error_msg);

    return 0;
}

int AatartSel_lagerbest(struct ARTLAGER *d, char *error_msg)
{
    static bool fst = true;

    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTLAGER   *a;
    char cVerbund[2];
    long lRest;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = false;
        cVerbund[0] = a->STATIONNR[0];
        cVerbund[1] = '\0';

        EXEC SQL declare Sel_lagerbest2 scroll cursor with hold for
            select
                ARTIKELLOKAL.ARTIKEL_NR,
                ARTIKELLOKAL.FILIALNR,
                ARTIKELLOKAL.BESTAND
            from artikellokal
            where artikellokal.artikel_nr  = :a->ARTIKEL_NR
            and artikellokal.verbundartikel >= :cVerbund
            order by artikellokal.bestand;

        EXEC SQL open Sel_lagerbest2;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartSel_lagerbest: open Sel_lagerbest2 %ld", sqlca.sqlcode);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = true;
        EXEC SQL close Sel_lagerbest2;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartSel_lagerbest: close Sel_lagerbest2 %ld", sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL
        Sel_lagerbest2 into
        :a->ARTIKEL_NR,
        :a->FILIALNR,
        :a->BESTAND;
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartSel_lagerbest: fetch Sel_lagerbest2 %ld/%d %s", sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
        EXEC SQL close Sel_lagerbest2;
        return -1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    EXEC SQL select (articlequota.quota - articlequota.kumqty) into :lRest
        from articlequota,filiale
        where articlequota.articleno = :a->ARTIKEL_NR
        and articlequota.branchno = :a->FILIALNR
        and articlequota.customerno = filiale.bganr_ek
        and filiale.bganr_ek > 0
        and filiale.filialnr = :FilialNr;
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartSel_lagerbest: select articlequota %ld/%d %s", sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
        EXEC SQL close Sel_lagerbest;
        return -1;
    }
    if (sqlca.sqlcode == 0)
    {
        if (lRest < a->BESTAND)
            a->BESTAND = lRest;
    }
    return 0;
}

int AatartSel_artlief(struct ARTLIEFER* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTLIEFER* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    EXEC SQL select
        ARTIKELZENTRAL.ARTIKEL_NR,
        ARTIKELZENTRAL.ARTIKEL_NR_HERST
        INTO ARTLIEFER_ZEIGER(a)
        FROM ARTIKELZENTRAL
        WHERE ARTIKELZENTRAL.ARTIKEL_NR = :a->ARTIKEL_NR;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_artlief select %ld", sqlca.sqlcode);
        return 1;
    }
    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    return 0;
}

int AatartSel_folge(struct ARTFOLGE* d, char* error_msg)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTFOLGE* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    EXEC SQL select artikellokal.artikel_nr
        into :a->ARTIKEL_NR
        from  artikellokal
        where artikellokal.artikel_nr = :a->ARTIKEL_NR
        and   artikellokal.filialnr = :FilialNr
        and   trunc(artikellokal.etartschalter1 / 16384) - 2 *
                trunc(artikellokal.etartschalter1 / (16384 * 2)) = 1;
    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_folge select artikel %ld", sqlca.sqlcode);
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    EXEC SQL select MAX(ARTIKEL_NR_ALTERN)
        into :a->ARTIKEL_NR from artikelaltern
        where artikel_nr = :a->ARTIKEL_NR
        and   filialnr = :FilialNr;

    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_folge select folge %ld", sqlca.sqlcode);
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    EXEC SQL select bestand,artikel_nr
        into :a->BESTAND, :a->ARTIKEL_NR from artikellokal
        where artikellokal.artikel_nr = :a->ARTIKEL_NR
        and   artikellokal.filialnr = :FilialNr;
    if (sqlca.sqlcode < 0)
    {
        sprintf(error_msg, " AatartSel_folge select bestand %ld", sqlca.sqlcode);
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    return 0;
}

/*****************************************************************************/
/* Umsetzen PZN nach interner Artikelnr                                      */
/*****************************************************************************/
long Pzn2Artikelnr(long pzn)
{
    EXEC SQL BEGIN DECLARE SECTION;
    long PZN;
    long artikel_nr;
    EXEC SQL END DECLARE SECTION;

    PZN = pzn;
    EXEC SQL select artikel_nr into :artikel_nr from artikelnummern
    where pzn = :PZN;

    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return PZN;
    }

    return artikel_nr;
}

/*****************************************************************************/
/* Umsetzen interne Artikelnr nach PZN                                       */
/*****************************************************************************/
long Artikelnr2Pzn(long artikelnr)
{
    EXEC SQL BEGIN DECLARE SECTION;
    long pzn;
    long artikel_nr;
    EXEC SQL END DECLARE SECTION;

    artikel_nr = artikelnr;
    EXEC SQL select pzn into :pzn from artikelnummern
    where artikel_nr = :artikel_nr;

    if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return artikel_nr;
    }

    return pzn;
}

int AatartFetch_artnrlief(struct ARTSEL* d, char* error_msg)
{
    static int iOpen = 1;
    int rc;

    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTSEL* a;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (iOpen) /* beim ersten mal oder bei neu deklarieren */
    {
        iOpen = 0;
        EXEC SQL declare CFetch_artnrlief cursor with hold for
        select
            artikelzentral.artikel_nr
            from artikelzentral
            where artikelzentral.artikel_nr_herst = :a->ARTIKEL_NAME;

            if (sqlca.sqlcode < 0)
            {
            iOpen = 1;
            sprintf(error_msg, " AatartFetch_artnrlief declare Cursor %ld/%ld", sqlca.sqlcode,sqlca.sqlerrd[1]);
            return 1;
        }

        EXEC SQL open CFetch_artnrlief;
        if (sqlca.sqlcode < 0)
        {
            iOpen = 1;
            sprintf(error_msg, " AatartFetch_artnrlief: open CFetch_artnrlief %ld/%ld", sqlca.sqlcode,sqlca.sqlerrd[1]);
            return 1;
        }
    }
    for (;;)
    {
        EXEC SQL fetch CFetch_artnrlief
            into
            :a->ARTIKEL_NR;
        if (sqlca.sqlcode == SQLNOTFOUND)
        {
            iOpen = 1;
            return 1;
        }
        if (sqlca.sqlcode < 0)
        {
            iOpen = 1;
            sprintf(error_msg, " AatartFetch_artnrlief select %ld/%ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
            return 1;
        }
        rc = AatartSel_art_nr(a, error_msg);
        if (rc == -2)
            continue;

        return rc;
    }
}

/*** AatartSel_ean *******************/

int AatartSel_ean(struct ARTSEL* d, char* error_msg)
{
    static bool fst = true;
    static int FREMDSPRACHE_ALT = 2;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTSEL* a;
    EXEC SQL END DECLARE SECTION;

    a = d;

    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = false;

        if (FREMDSPRACHE != FREMDSPRACHE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            EXEC SQL free dec_mc_ean;
            EXEC SQL free Sel_mc_ean;
            if (FREMDSPRACHE)
            {
                strcpy(str, "select ");
                strcat(str, "c.ARTIKEL_MC, ");
                strcat(str, "z.PACKGROESSE, ");
                strcat(str, "c.DARREICHFORM, ");
                strcat(str, "c.EINHEIT, ");
                strcat(str, "c.ARTIKEL_NAME, ");
                strcat(str, "artikelnummern.PZN, ");
                strcat(str, "ARTIKELLOKAL.BESTAND, ");
                strcat(str, "z.NORMPACKUNG, ");
                strcat(str, "z.HERSTELLER_CODE ");
                strcat(str, "from ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c ");
                strcat(str, ",artikelnummern ");
                strcat(str, ",artikelzentral z,outer artikellokal ");
                strcat(str, "where artikelnummern.ean = ? ");
                strcat(str, "and artikelnummern.artikel_nr = z.artikel_nr ");
                strcat(str, "and artikellokal.artikel_nr = z.artikel_nr ");
                strcat(str, "and c.artikel_nr = z.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
                strcat(str, "order by c.artikel_name,c.einheit ");
            }
            else
            {
                strcpy(str, "select ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_MC, ");
                strcat(str, "ARTIKELZENTRAL.PACKGROESSE, ");
                strcat(str, "ARTIKELZENTRAL.DARREICHFORM, ");
                strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
                strcat(str, "artikelnummern.PZN, ");
                strcat(str, "ARTIKELLOKAL.BESTAND, ");
                strcat(str, "ARTIKELZENTRAL.NORMPACKUNG, ");
                strcat(str, "ARTIKELZENTRAL.HERSTELLER_CODE ");
                strcat(str, "from artikelnummern,artikelzentral,outer artikellokal ");
                strcat(str, "where artikelnummern.ean = ? ");
                strcat(str, "and artikelnummern.artikel_nr = artikelzentral.artikel_nr ");
                strcat(str, "and artikellokal.artikel_nr = artikelzentral.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
                strcat(str, "order by artikelzentral.artikel_name,artikelzentral.einheit ");
            }
            EXEC SQL PREPARE dec_mc_ean FROM :str;
            if (sqlca.sqlcode < 0)
            {
                fst = true;
                sprintf(error_msg, " AatartSel_ean: declare dec_mc_ean %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_mc_ean scroll cursor with hold for dec_mc_ean;
        }
        EXEC SQL open Sel_mc_ean
            using
            :a->ARTIKEL_NAME,
            :FilialNr;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartSel_ean: open Sel_mc_ean %ld", sqlca.sqlcode);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = true;
        EXEC SQL close Sel_mc_ean;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartSel_ean: close Sel_mc_ean %ld", sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_mc_ean into ARTSEL_ZEIGER(a);
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartSel_ean: fetch Sel_mc_ean %ld", sqlca.sqlcode);
        EXEC SQL close Sel_ean;
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

/*** AatartSel_Preferred (Bevorzugten Artikelcode lesen) *******************/

int AatartSel_Preferred(struct ARTAESEL* d, char* error_msg)
{
    static bool fst = true;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTAESEL* a;
    EXEC SQL END DECLARE SECTION;

    a = d;

    if (fst) /* beim ersten mal deklarieren */
    {
        fst = false;

        strcpy(str, "select ");
        strcat(str, "ARTICLE_CODE, ");
        strcat(str, "CODE_TYPE ");
        strcat(str, "from ");
        strcat(str, "articlecodes ");
        strcat(str, "where articleno = ? ");
        strcat(str, "and preferred_flag = '1' ");
        EXEC SQL PREPARE dec_preferred FROM :str;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartSel_Preferred: declare dec_preferred %ld %ld %s", sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
        EXEC SQL declare Sel_preferred cursor for dec_preferred;
    }
    EXEC SQL open Sel_preferred using :a->ARTIKEL_NR;

    EXEC SQL fetch Sel_preferred into :a->ARTICLE_CODE, :a->CODE_TYPE;
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartSel_Preferred: fetch Sel_preferred %ld %ld %s", sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
        EXEC SQL close Sel_preferred;
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        a->ARTICLE_CODE[0] = '\0';
        a->CODE_TYPE = 0;
        return 1;
    }

    return 0;
}

/*** AatartSel_NoByCode (Artikelnr aus Artikelcode lesen) *******************/

int AatartSel_NoByCode(struct ARTAESEL* d, char* error_msg)
{
    static bool fst = true;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTAESEL* a;
    EXEC SQL END DECLARE SECTION;

    a = d;

    if (fst) /* beim ersten mal deklarieren */
    {
        fst = false;

        strcpy(str, "select ");
        strcat(str, "ARTICLENO, ");
        strcat(str, "CODE_TYPE ");
        strcat(str, "from ");
        strcat(str, "articlecodes ");
        strcat(str, "where article_code = ? ");
        EXEC SQL PREPARE dec_code FROM :str;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartSel_NoByCode: declare dec_code %ld %ld %s", sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
            return -1;
        }
        EXEC SQL declare Sel_code cursor for dec_code;
    }
    AllgEntfSpaces(a->ARTICLE_CODE);
    EXEC SQL open Sel_code using :a->ARTICLE_CODE;

    EXEC SQL fetch Sel_code into :a->ARTIKEL_NR, :a->CODE_TYPE;
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartSel_NoByCode: fetch Sel_code %ld %ld %s", sqlca.sqlcode, sqlca.sqlerrd[1], sqlca.sqlerrm);
        EXEC SQL close Sel_preferred;
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        a->ARTIKEL_NR = 0;
        a->CODE_TYPE = 0;
        return 1;
    }

    return 0;
}

/*** AatartSel_herstname ( Artikelsuche nach Hersteller) *******************/

int AatartSel_herstname(struct ARTSEL* d, char* error_msg)
{
    static bool fst = true;
    static int FREMDSPRACHE_ALT = 2;
    static int BESTAND_ALT = 2;
    static short IMPORTARTICLE_ALT = 3;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTSEL* a;
    EXEC SQL END DECLARE SECTION;

    a = d;

    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        fst = false;

        if (FREMDSPRACHE != FREMDSPRACHE_ALT || a->BESTAND != BESTAND_ALT || a->IMPORTARTICLE != IMPORTARTICLE_ALT)
        {
            FREMDSPRACHE_ALT = FREMDSPRACHE;
            BESTAND_ALT = a->BESTAND;
            IMPORTARTICLE_ALT = a->IMPORTARTICLE;
            EXEC SQL free dec_hc_art;
            EXEC SQL free Sel_hc_art;
            if (FREMDSPRACHE)
            {
                strcpy(str, "select ");
                strcat(str, "c.ARTIKEL_MC, ");
                strcat(str, "z.PACKGROESSE, ");
                strcat(str, "c.DARREICHFORM, ");
                strcat(str, "c.EINHEIT, ");
                strcat(str, "c.ARTIKEL_NAME, ");
                strcat(str, "z.ARTIKEL_NR, ");
                strcat(str, "ARTIKELLOKAL.BESTAND, ");
                strcat(str, "z.NORMPACKUNG, ");
                strcat(str, "z.HERSTELLER_CODE, ");
                strcat(str, "z.HERSTELLER_NR, ");
                strcat(str, "z.IMPORTARTICLE ");
                strcat(str, "from ");
                strcat(str, ARTIKELZENTRAL_SPRACHE);
                strcat(str, " c ");
                strcat(str, ",artikelzentral z");
                if (!strcmp(cCountry, "BG") && a->BESTAND > 0)
                {
                    strcat(str, ",artikellokal ");
                }
                else
                {
                    strcat(str, ",outer artikellokal ");
                }
                strcat(str, "where c.hersteller_nr = ? ");
                if (a->IMPORTARTICLE == 0)
                {
                    strcat(str, "and z.importarticle = 0 ");
                }
                else if (a->IMPORTARTICLE == 1)
                {
                    strcat(str, "and z.importarticle = 1 ");
                }
                strcat(str, "and artikellokal.artikel_nr = z.artikel_nr ");
                strcat(str, "and c.artikel_nr = z.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
                if (!strcmp(cCountry, "BG"))
                {
                    if (a->BESTAND > 0)
                    {
                        strcat(str, "and artikellokal.artikelaktiv in ('1','4') ");
                    }
                    strcat(str, "order by z.artikel_langname,c.einheit ");
                }
                else
                {
                    strcat(str, "order by c.artikel_name,c.einheit ");
                }
            }
            else
            {
                strcpy(str, "select ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_MC, ");
                strcat(str, "ARTIKELZENTRAL.PACKGROESSE, ");
                strcat(str, "ARTIKELZENTRAL.DARREICHFORM, ");
                strcat(str, "ARTIKELZENTRAL.EINHEIT, ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_NAME, ");
                strcat(str, "ARTIKELZENTRAL.ARTIKEL_NR, ");
                strcat(str, "ARTIKELLOKAL.BESTAND, ");
                strcat(str, "ARTIKELZENTRAL.NORMPACKUNG, ");
                strcat(str, "ARTIKELZENTRAL.HERSTELLER_CODE, ");
                strcat(str, "ARTIKELZENTRAL.HERSTELLER_NR, ");
                strcat(str, "ARTIKELZENTRAL.IMPORTARTICLE ");
                strcat(str, "from artikelzentral");
                if (!strcmp(cCountry, "BG") && a->BESTAND > 0)
                {
                    strcat(str, ",artikellokal ");
                }
                else
                {
                    strcat(str, ",outer artikellokal ");
                }
                strcat(str, "where artikelzentral.hersteller_nr = ? ");
                if (a->IMPORTARTICLE == 0)
                {
                    strcat(str, "and artikelzentral.importarticle = 0 ");
                }
                else if (a->IMPORTARTICLE == 1)
                {
                    strcat(str, "and artikelzentral.importarticle = 1 ");
                }
                strcat(str, "and artikellokal.artikel_nr = artikelzentral.artikel_nr ");
                strcat(str, "and artikellokal.filialnr = ? ");
                if (!strcmp(cCountry, "BG"))
                {
                    if (a->BESTAND > 0)
                    {
                        strcat(str, "and artikellokal.artikelaktiv in ('1','4') ");
                    }
                    strcat(str, "order by artikelzentral.artikel_langname,artikelzentral.einheit ");
                }
                else
                {
                    strcat(str, "order by artikelzentral.artikel_name,artikelzentral.einheit ");
                }
            }
            EXEC SQL PREPARE dec_hc_art FROM :str;
            if (sqlca.sqlcode < 0)
            {
                fst = true;
                sprintf(error_msg, " AatartSel_hc: declare dec_hc_art %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
                return -1;
            }
            EXEC SQL declare Sel_hc_art scroll cursor with hold for dec_hc_art;
        }
        EXEC SQL open Sel_hc_art
            using
            :a->HERSTELLER_NR,
            :FilialNr;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartSel_hc: open Sel_hc_art %ld", sqlca.sqlcode);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)   /* close cursor */
    {
        fst = true;
        EXEC SQL close Sel_hc_art;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartSel_hc: close Sel_hc_art %ld", sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Sel_hc_art into ARTSEL_ZEIGER(a);
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartSel_hc: fetch Sel_hc_art %ld", sqlca.sqlcode);
        EXEC SQL close Sel_hc;
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }

    return 0;
}

/*** AatartAa_select (Matchcode suche incl. Packungsgrösse) *******************/

int AatartAa_select(struct ARTAESEL* d, char* error_msg)
{
    static bool fst = true;
    int iMax = 3;
    static int FREMDSPRACHE_ALT = 2;
    static int SHORT = 0;
    static int SHORT_ALT = 2;
    static char cFrText;
    EXEC SQL BEGIN DECLARE SECTION;
    struct ARTAESEL* a;
    char NORMPACKUNG[5];
    char HERSTELLER_CODE[11];   // ARTAESEL size * 2 for escaping characters
    char ARTIKEL_MC[25];        // ARTAESEL size * 2 for escaping characters
    char ARTIKEL_NAME_0[61];    // ARTAESEL size * 2 for escaping characters
    char ARTIKEL_NAME_1[61];    // ARTAESEL size * 2 for escaping characters
    char ARTIKEL_NAME_2[61];    // ARTAESEL size * 2 for escaping characters
    long DATUM;
    char aktiv[2];
    const char* arrArtikelName[L_ARTSEL_ARTIKEL_NAME + 2];
    short sTextKey;
    char cTexte[500];
    char cCountryText[31];
    char cWert[11];
    double dAep;
    short sOnlyReserve;
    short sIndex;
    short sLiefnr;
    EXEC SQL END DECLARE SECTION;

    a = d;
    if (fst) /* beim ersten mal oder bei neu deklarieren */
    {
        exec sql begin declare section;
        char szBuf[512];
        char KdauftragArt[3];
        short sReserve;
        short sWithCpg = 0;
        exec sql end declare section;

        strncpy(KdauftragArt, cKdauftragArt, 2);

        exec sql drop table t_config;
        exec sql drop table t_cpg;
        sOnlyReserve = 0;
        exec sql select conf.id, conf.cscreservationtype, conf.reservedstockonly, res.withpharmacygroup from ordertypereservationconfig conf
            inner join cscreservationtypes res on res.cscreservationtype = conf.cscreservationtype
            where cscordertype = :KdauftragArt
            into temp t_config;
        exec sql select count(*) into :sReserve from t_config;
        if (sReserve > 0)
        {
            exec sql select count(*) into :sOnlyReserve from t_config where reservedstockonly = 1;
            exec sql select withpharmacygroup into :sWithCpg from t_config;
            if (sWithCpg)
            {
                exec sql select cpg.pharmacygroupid, conf.cscreservationtype from ordertypereservationconfigcpg cpg
                    inner join t_config conf on conf.id = cpg.ordertypereservationconfig_id
                    into temp t_cpg;
            }
        }
        cFrText = a->CODEBLOCAGE[0];

        exec sql free P_ARTSELNEU; /* only to be shure */
        strcpy(szBuf, "select artikelzentral.ARTIKEL_NR,");
        strcat(szBuf, "artikellagerort.DATUMVERFALL,");
        strcat(szBuf, "artikelpreis.PREISEKAPO,");
        strcat(szBuf, "artikelpreis.PREISEKGROSSO,");
        strcat(szBuf, "artikelpreis.PREISEKGROSSONA,");
        strcat(szBuf, "artikelzentral.ETARTKLASSE1 ");
        strcat(szBuf, "from artikelzentral,artikelpreis,artikellagerort ");
        strcat(szBuf, "where artikelzentral.artikel_nr=? ");
        strcat(szBuf, "and artikelpreis.artikel_nr=artikelzentral.artikel_nr ");
        strcat(szBuf, "and artikelpreis.datumgueltigab<=? ");
        strcat(szBuf, "and artikelpreis.datumgueltigbis>=? ");
        strcat(szBuf, "and artikelpreis.preis_typ=0 ");
        strcat(szBuf, "and artikellagerort.artikel_nr=artikelzentral.artikel_nr ");
        strcat(szBuf, "and artikellagerort.filialnr=? ");
        exec sql prepare P_ARTSELNEU from :szBuf;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartAa_select: prepare P_ARTSELNEU %ld", sqlca.sqlcode);
            return -1;
        }
        fst = false;

        HandleNormPackage(NORMPACKUNG, a->NORMPACKUNG, "");

        SHORT = HandlePharmacyGroupID(a->PHARMACYGROUPID);

        ppGStripLast(a->ARTIKEL_MC);
        ppGStripLast(a->DARREICHFORM);
        ppGStripLast(a->NORMPACKUNG);
        ppGStripLast(a->HERSTELLER_CODE);
        ppGStripLast(a->ARTIKEL_NAME);
        sIndex = 0;     //keine Abfrage ueber artikelindex
        sLiefnr = 0;    //keine Abfrage ueber Lieferantenartikel_nr
        if (a->ARTIKEL_MC[0] != '\0')
        {
            if (a->ARTIKEL_MC[strlen(a->ARTIKEL_MC) - 1] == '*')
            {
                sLiefnr = 1;    //Abfrage ueber Lieferantenartikel_nr
            }
            else if (a->ARTIKEL_MC[strlen(a->ARTIKEL_MC) - 1] == '%')
            {
                sIndex = 1; //Abfrage ueber Artikelindex
                EXEC SQL drop table tmpausgab1;
                EXEC SQL create temp table tmpausgab1(
                    ARTIKEL_NR INTEGER);
                if (FREMDSPRACHE)
                {
                    strcpy(str, "insert into tmpausgab1 ");
                    strcat(str, "select ");
                    strcat(str, "unique c.artikel_nr ");
                    strcat(str, "from ");
                    strcat(str, ARTIKELINDEX_SPRACHE);
                    strcat(str, " c ");
                    strcat(str, "where ");
                    strcat(str, "c.suchbezeichner like ? ");
                }
                else
                {
                    strcpy(str, "insert into tmpausgab1 ");
                    strcat(str, "select ");
                    strcat(str, "unique artikel_nr ");
                    strcat(str, "from artikelindex ");
                    strcat(str, "where ");
                    strcat(str, "artikelindex.suchbezeichner like ? ");
                }

                EscapeSingleQuotes(ARTIKEL_MC, a->ARTIKEL_MC);

                EXEC SQL PREPARE sel_tmpindexn FROM :str;
                if (sqlca.sqlcode < 0)
                {
                    fst = true;
                    sprintf(error_msg, " AatartAa_select: declare sel_tmpindexn %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
                    return -1;
                }
                EXEC SQL execute sel_tmpindexn
                    using
                    :ARTIKEL_MC;
            }
            else
            {
                AllgMakeToLike(a->ARTIKEL_MC, L_ARTSEL_ARTIKEL_MC);
                EscapeSingleQuotes(ARTIKEL_MC, a->ARTIKEL_MC);
            }
        }
        if (a->DARREICHFORM[0] != '\0')
        {
            AllgMakeToLike(a->DARREICHFORM, L_ARTSEL_DARREICHFORM);
        }
        if (a->HERSTELLER_CODE[0] != '\0')
        {
            AllgMakeToLike(a->HERSTELLER_CODE, L_ARTSEL_HERSTELLER_CODE);
            EscapeSingleQuotes(HERSTELLER_CODE, a->HERSTELLER_CODE);
        }
        if (a->ARTIKEL_NAME[0] != '\0')
        {
            ppGGetWhereFromStr(PPG_STATIC, a->ARTIKEL_NAME, (char*)0, (char*)0, arrArtikelName, iMax);
            EscapeSingleQuotes(ARTIKEL_NAME_0, arrArtikelName[0]);
            EscapeSingleQuotes(ARTIKEL_NAME_1, arrArtikelName[1]);
            EscapeSingleQuotes(ARTIKEL_NAME_2, arrArtikelName[2]);
        }
        if (FREMDSPRACHE != FREMDSPRACHE_ALT || SHORT != SHORT_ALT)
        {
            SHORT_ALT = SHORT;
            FREMDSPRACHE_ALT = FREMDSPRACHE;
        }
        EXEC SQL free dec_Aa_select;
        EXEC SQL free Aa_select;

        strcpy(str, "select ");
        strcat(str, "s.ARTIKEL_NR, ");
        strcat(str, "s.PACKGROESSE, ");
        if (FREMDSPRACHE)
        {
            strcat(str, "c.ARTIKEL_MC, ");
            strcat(str, "c.DARREICHFORM, ");
            strcat(str, "c.EINHEIT, ");
            strcat(str, "c.ARTIKEL_NAME, ");
            strcat(str, "( c.ETARTSCHALTER1 + nvl(l.ETARTSCHALTER1,0) ), ");
        }
        else
        {
            strcat(str, "s.ARTIKEL_MC, ");
            strcat(str, "s.DARREICHFORM, ");
            strcat(str, "s.EINHEIT, ");
            strcat(str, "s.ARTIKEL_NAME, ");
            strcat(str, "( s.ETARTSCHALTER1 + nvl(l.ETARTSCHALTER1,0) ), ");
        }
        strcat(str, "( z.ETARTSCHALTER2 + nvl(l.ETARTSCHALTER2,0) ), ");
        strcat(str, "( z.ETARTSCHALTER3 + nvl(l.ETARTSCHALTER3,0) ), ");
        strcat(str, "( z.ETARTSCHALTER4 + nvl(l.ETARTSCHALTER4,0) ), ");
        strcat(str, "l.PRISOART, ");
        if (sOnlyReserve)
        {
            strcat(str, "r.RESERVEDQTY, ");
        }
        else if (sReserve)
        {
            strcat(str, "( l.BESTAND + nvl(r.RESERVEDQTY,0) ), ");
        }
        else
        {
            strcat(str, "l.BESTAND, ");
        }
        strcat(str, "z.ETARTKLASSE1, ");
        strcat(str, "l.artikelaktiv, ");
        strcat(str, "l.chargenartikel, ");
        strcat(str, "z.hersteller_code, ");
        strcat(str, "l.wafotyp, ");
        strcat(str, "l.NATRASTAFFELNR, ");
        strcat(str, "l.TEXTKEY, ");
        strcat(str, "z.TEXTKEY_HOSPITAL, ");
        strcat(str, "l.CODEBLOCAGE, ");
        strcat(str, "z.POSITIVLISTE, ");
        strcat(str, "z.HEALTHFUNDCODE, ");
        strcat(str, "z.ARTIKEL_LANGNAME, ");
        strcat(str, "z.TAXLEVEL, ");
        strcat(str, "z.KZPSYCHOSTOFFE, ");
        strcat(str, "z.PRODUSERQUOTA, ");
        strcat(str, "z.IMPORTARTICLE, ");
        strcat(str, "z.MEDIZINPRODUKT, ");
        strcat(str, "z.FROZEN ");
        strcat(str, "from artikelzentral z ");
        strcat(str, "inner join artselect s on s.artikel_nr = z.artikel_nr ");
        strcat(str, "inner join artikellokal l on l.artikel_nr = z.artikel_nr ");
        if (FREMDSPRACHE)
        {
            strcat(str, "inner join  ");
            strcat(str, ARTIKELSELECT_SPRACHE);
            strcat(str, " c ");
            strcat(str, "on c.artikel_nr = z.artikel_nr ");
        }
        if (sIndex)
        {
            strcat(str, "inner join tmpausgab1 ind ");
            strcat(str, "on ind.artikel_nr = z.artikel_nr ");
        }
        if (sOnlyReserve)
        {
            strcat(str, "inner join articlereservation r ");
            strcat(str, "on r.articleno = z.artikel_nr and r.branchno = l.filialnr ");
            if (sWithCpg)
            {
                strcat(str, "inner join t_cpg cpg on cpg.pharmacygroupid = r.pharmacygroupid and cpg.cscreservationtype = r.reservtype ");
            }
            else
            {
                strcat(str, "inner join t_config conf on conf.cscreservationtype = r.reservtype ");
            }
        }
        else if (sReserve)
        {
            strcat(str, "left join articlereservation r ");
            strcat(str, "on r.articleno = z.artikel_nr and r.branchno = l.filialnr ");
            if (sWithCpg)
            {
                strcat(str, "left join t_cpg cpg on cpg.pharmacygroupid = r.pharmacygroupid and cpg.cscreservationtype = r.reservtype ");
            }
            else
            {
                strcat(str, "left join t_config conf on conf.cscreservationtype = r.reservtype ");
            }
        }
        strcat(str, "where l.filialnr = ");
        sprintf(cWert, "%d ", FilialNr);
        strcat(str, cWert);
        if (a->IMPORTARTICLE == 0)
        {
            strcat(str, "and z.importarticle = 0 ");
        }
        else if (a->IMPORTARTICLE == 1)
        {
            strcat(str, "and z.importarticle = 1 ");
        }
        if (a->ARTIKEL_NR != 0)
        {
            strcat(str, "and z.artikel_nr = ");
            sprintf(cWert, "%d ", a->ARTIKEL_NR);
            strcat(str, cWert);
        }
        else if (sLiefnr)
        {
            strcat(str, "and z.artikel_nr in ");
            strcat(str, "( select unique bl.artikel_nr from ARTNRBL bl where ");
            strcat(str, "bl.ARTIKEL_NR_BLIEFER matches '");
            strcat(str, ARTIKEL_MC);
            strcat(str, "' ");
            strcat(str, ") ");
        }
        else
        {
            if (FREMDSPRACHE)
            {
                if (!sIndex)
                {
                    if (a->ARTIKEL_MC[0] != '\0')
                    {
                        strcat(str, "and c.artikel_mc like '");
                        strcat(str, ARTIKEL_MC);
                        strcat(str, "' ");
                    }
                }
                if (a->PACKGROESSE > 0)
                {
                    strcat(str, "and c.packgroesse = ");
                    sprintf(cWert, "%d ", a->PACKGROESSE);
                    strcat(str, cWert);
                }
                if (a->DARREICHFORM[0] != '\0')
                {
                    strcat(str, "and c.darreichform like '");
                    strcat(str, a->DARREICHFORM);
                    strcat(str, "' ");
                }
                if (a->NORMPACKUNG[0] != '\0')
                {
                    strcat(str, "and c.artikel_name[27,30] like ' ");
                    strcat(str, NORMPACKUNG);
                    strcat(str, "' ");
                }
                if (a->ARTIKEL_NAME[0] != '\0')
                {
                    strcat(str, "and c.artikel_name like '");
                    strcat(str, ARTIKEL_NAME_0);
                    strcat(str, "' and c.artikel_name like '");
                    strcat(str, ARTIKEL_NAME_1);
                    strcat(str, "' and c.artikel_name like '");
                    strcat(str, ARTIKEL_NAME_2);
                    strcat(str, "' ");
                }
            }
            else
            {
                if (!sIndex)
                {
                    if (a->ARTIKEL_MC[0] != '\0')
                    {
                        strcat(str, "and s.artikel_mc like '");
                        strcat(str, ARTIKEL_MC);
                        strcat(str, "' ");
                    }
                }
                if (a->PACKGROESSE > 0)
                {
                    strcat(str, "and s.packgroesse = ");
                    sprintf(cWert, "%d ", a->PACKGROESSE);
                    strcat(str, cWert);
                }
                if (a->DARREICHFORM[0] != '\0')
                {
                    strcat(str, "and s.darreichform like '");
                    strcat(str, a->DARREICHFORM);
                    strcat(str, "' ");
                }
                if (a->NORMPACKUNG[0] != '\0')
                {
                    strcat(str, "and s.artikel_name[27,30] like ' ");
                    strcat(str, NORMPACKUNG);
                    strcat(str, "' ");
                }
                if (a->ARTIKEL_NAME[0] != '\0')
                {
                    strcat(str, "and s.artikel_name like '");
                    strcat(str, ARTIKEL_NAME_0);
                    strcat(str, "' and s.artikel_name like '");
                    strcat(str, ARTIKEL_NAME_1);
                    strcat(str, "' and s.artikel_name like '");
                    strcat(str, ARTIKEL_NAME_2);
                    strcat(str, "' ");
                }
            }
            if (a->BESTAND > 0)
            {
                strcat(str, "and l.bestand >= ");
                sprintf(cWert, "%d ", a->BESTAND);
                strcat(str, cWert);
            }
            if (cFrText != '1')
            {
                strcat(str, "and l.artikelaktiv != 0 ");
            }
            if (a->HERSTELLER_CODE[0] != '\0')
            {
                strcat(str, "and z.hersteller_code like '");
                strcat(str, HERSTELLER_CODE);
                strcat(str, "' ");
            }
            if (strncmp(a->PHARMACYGROUPID, "   ", L_ARTAESEL_PHARMACYGROUPID))
            {
                strcat(str, "and l.artikel_nr in  ");
                strcat(str, "(select d.articleno from discount d ");
                strcat(str, "where d.pharmacygroupid = '");
                strncat(str, a->PHARMACYGROUPID, L_ARTAESEL_PHARMACYGROUPID);
                strcat(str, "' and d.branchno = l.filialnr ");
                strcat(str, "and d.discounttype in ( ");
                strcat(str, "select discounttype from discountordertyp ");
                strcat(str, "where discountordertyp.kdauftragart = '");
                strcat(str, cKdauftragArt);
                strcat(str, "' ) ) ");
            }
            if (a->POSITIVLISTE[0] != ' ')
            {
                strcat(str, "and z.positivliste >= '");
                strcat(str, a->POSITIVLISTE);
                strcat(str, "' ");
            }
        }
        strcat(str, "and bitand(z.etartklasse1, ");
        sprintf(cWert, "%d) ", a->ETARTKLASSE1);
        strcat(str, cWert);
        strcat(str, "= z.etartklasse1 ");

        if (FilialNr == 48) AatartIvrylab("z", a->PHARMACYGROUPID);
        if (!strcmp(cCountry, "BG"))
        {
            strcat(str, "and z.HEALTHFUNDCODE >= '");
            strcat(str, a->HEALTHFUNDCODE);
            strcat(str, "' ");
            strcat(str, "order by z.artikel_langname[1,26],z.darreichform,z.einheit ");
        }
        else
        {
            if (FREMDSPRACHE)
            {
                strcat(str, "order by c.artikel_name[1,26],c.darreichform,c.einheit ");
            }
            else
            {
                strcat(str, "order by z.artikel_name[1,26],z.darreichform,z.einheit ");
            }
        }

        EXEC SQL PREPARE dec_Aa_select FROM :str;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartAa_select: prepare dec_Aa_select %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }
        EXEC SQL declare Aa_select scroll cursor with hold for dec_Aa_select;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartAa_select: declare Aa_select %ld %ld", sqlca.sqlcode, sqlca.sqlerrd[1]);
            return -1;
        }


        EXEC SQL open Aa_select;
        if (sqlca.sqlcode < 0)
        {
            fst = true;
            sprintf(error_msg, " AatartAa_select: open Aa_select %ld", sqlca.sqlcode);
            return -1;
        }
    }

    if (a->FETCH_REL == 0)
    {
        fst = true;
        EXEC SQL close Aa_select;
        if (sqlca.sqlcode < 0)
        {
            sprintf(error_msg, " AatartAa_select: close Aa_select %ld", sqlca.sqlcode);
            return -1;
        }
        return 1;
    }

    EXEC SQL fetch relative :a->FETCH_REL Aa_select
        into :a->ARTIKEL_NR,
        :a->PACKGROESSE,
        :a->ARTIKEL_MC,
        :a->DARREICHFORM,
        :a->EINHEIT,
        :a->ARTIKEL_NAME,
        :a->ETARTSCHALTER1,
        :a->ETARTSCHALTER2,
        :a->ETARTSCHALTER3,
        :a->ETARTSCHALTER4,
        :a->PRISOART,
        :a->BESTAND,
        :a->ETARTKLASSE1,
        :aktiv,
        :a->CHARGENARTIKEL,
        :a->HERSTELLER_CODE,
        :a->WAFOTYP,
        :a->NATRASTAFFELNR,
        :sTextKey,
        :a->TEXTKEY_HOSPITAL,
        :a->CODEBLOCAGE,
        :a->POSITIVLISTE,
        :a->HEALTHFUNDCODE,
        :a->ARTIKEL_LANGNAME,
        :a->TAXLEVEL,
        :a->KZPSYCHOSTOFFE,
        :a->PRODUSERQUOTA,
        :a->IMPORTARTICLE,
        :a->MEDIZINPRODUKT,
        :a->FROZEN;
    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartAa_select: fetch Aa_select %ld", sqlca.sqlcode);
        EXEC SQL close Aa_select;
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    else if (aktiv[0] > '2' || aktiv[0] == '0')
    {
        a->BESTAND = 0;
    }

    a->TEXT[0] = '\0';
    cTexte[0] = '\0';

    if (!strcmp(cCountry, "CH"))
    {
        EXEC SQL select texthospital
            into :a->TEXT
            from articletext
        where textkey = :a->TEXTKEY_HOSPITAL;
    }

    if (cFrText == '1')
    {
        if (a->BESTAND == 0)
        {
            EXEC SQL select printcode
                into :cCountryText
                from countrycodes
            where branchno = :FilialNr
            and infocode = :a->CODEBLOCAGE;
        }
        else
        {
            cCountryText[0] = '\0';
        }
    }
    if (sTextKey != 0)
    {
        if (cFrText == '1')
        {
            EXEC SQL select texthospital
                into :cTexte
                from articletext
            where textkey = :sTextKey;
            sprintf(a->TEXT, "%5.5s %234.234s", cCountryText, cTexte);
        }
        else
        {
            EXEC SQL select text
                into :a->TEXT
                from articletext
            where textkey = :sTextKey;
        }
    }
    if (cFrText == '1')
    {
        sprintf(a->TEXT, "%5.5s %234.234s", cCountryText, cTexte);
    }

    DATUM = AllgGetDate();
    EXEC SQL execute P_ARTSELNEU
        into :a->ARTIKEL_NR,
        :a->DATUMVERFALL,
        :a->PREISEKAPO,
        :a->PREISEKGROSSO,
        :a->PREISEKGROSSONA,
        :a->ETARTKLASSE1
        using :a->ARTIKEL_NR,
        :DATUM,
        :DATUM,
        :a->FILIALNR;

    if (sqlca.sqlcode < 0)
    {
        fst = true;
        sprintf(error_msg, " AatartAa_select: execute P_ARTSELNEU %ld", sqlca.sqlcode);
        EXEC SQL close Aa_select;
        return -1;
    }
    else if (sqlca.sqlcode == SQLNOTFOUND)
    {
        return 1;
    }
    EXEC SQL select PREISEKAPO
        into :dAep
        from    articleoldprice
    where   articleoldprice.articleno = :a->ARTIKEL_NR
    and     articleoldprice.branchno = :a->FILIALNR;
    if (sqlca.sqlcode == 0)
    {
        a->PREISEKAPO = dAep;
    }
    //AatartCheck_natra(a, error_msg);
    //AatartCheck_mgpreis(a, error_msg);
    AatartSel_Preferred(a, error_msg);

    return 0;
}

void EscapeSingleQuotes(char* dest, const char* src)
{
    while (*src != '\0')
    {
        if (*src == '\'')
        {
            *dest++ = *src;
        }
        *dest++ = *src;

        ++src;
    }
    *dest = '\0';
}

void HandleNormPackage(char* dest, const char* src, const char* notSetChar)
{
    if (src[0] == 'N' &&
        src[1] >= '1' &&
        src[1] <= '3' &&
        src[2] == '\0')
    {
        dest[0] = '%';
        strcpy(dest + 1, src);
    }
    else
    {
        strcpy(dest, notSetChar);
    }
}

short HandlePharmacyGroupID(const char* pharmacyGroupID)
{
    if (strncmp(pharmacyGroupID, "   ", L_ARTAESEL_PHARMACYGROUPID) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

void GetAatartSel_mc_Select(struct ARTSEL* a, bool bUsePackageSize)
{
    if (FREMDSPRACHE != 0)
    {
        strcpy(str, "select ");
        strcat(str, "c.ARTIKEL_MC, ");
        strcat(str, "z.PACKGROESSE, ");
        strcat(str, "c.DARREICHFORM, ");
        strcat(str, "c.EINHEIT, ");
        strcat(str, "c.ARTIKEL_NAME, ");
        strcat(str, "z.ARTIKEL_NR, ");
        strcat(str, "ARTIKELLOKAL.BESTAND, ");
        strcat(str, "z.NORMPACKUNG, ");
        strcat(str, "z.HERSTELLER_CODE, ");
        strcat(str, "z.HERSTELLER_NR, ");
        strcat(str, "z.IMPORTARTICLE ");
        strcat(str, "from ");
        strcat(str, ARTIKELZENTRAL_SPRACHE);
        strcat(str, " c ");
        strcat(str, ",artikelzentral z");
        if (!strcmp(cCountry, "BG") && a->BESTAND > 0)
        {
            strcat(str, ",artikellokal ");
        }
        else
        {
            strcat(str, ",outer artikellokal ");
        }
        strcat(str, "where c.artikel_mc like ? ");
        if (a->IMPORTARTICLE == 0)
        {
            strcat(str, "and z.importarticle = 0 ");
        }
        else if (a->IMPORTARTICLE == 1)
        {
            strcat(str, "and z.importarticle = 1 ");
        }
        if (bUsePackageSize)
        {
            strcat(str, "and z.packgroesse = ? ");
        }
        strcat(str, "and c.darreichform like ? ");
        strcat(str, "and artikellokal.artikel_nr = z.artikel_nr ");
        strcat(str, "and c.artikel_nr = z.artikel_nr ");
        strcat(str, "and artikellokal.filialnr = ? ");
        strcat(str, "and ");
        strcat(str, "c.artikel_name[27,30] like ? and ");
        strcat(str, "c.artikel_name like ? and ");
        strcat(str, "c.artikel_name like ? and ");
        strcat(str, "c.artikel_name like ? ");
        if (!strcmp(cCountry, "BG"))
        {
            if (a->BESTAND > 0)
            {
                strcat(str, "and artikellokal.artikelaktiv in ('1','4') ");
            }
            strcat(str, "order by z.artikel_langname,c.einheit ");
        }
        else
        {
            strcat(str, "order by c.artikel_name,c.einheit ");
        }
    }
    else
    {
        strcpy(str, "select ");
        strcat(str, "z.ARTIKEL_MC, ");
        strcat(str, "z.PACKGROESSE, ");
        strcat(str, "z.DARREICHFORM, ");
        strcat(str, "z.EINHEIT, ");
        strcat(str, "z.ARTIKEL_NAME, ");
        strcat(str, "z.ARTIKEL_NR, ");
        strcat(str, "ARTIKELLOKAL.BESTAND, ");
        strcat(str, "z.NORMPACKUNG, ");
        strcat(str, "z.HERSTELLER_CODE, ");
        strcat(str, "z.HERSTELLER_NR, ");
        strcat(str, "z.IMPORTARTICLE ");
        strcat(str, "from artikelzentral z");
        if (!strcmp(cCountry, "BG") && a->BESTAND > 0)
        {
            strcat(str, ",artikellokal ");
        }
        else
        {
            strcat(str, ",outer artikellokal ");
        }
        strcat(str, "where z.artikel_mc like ? ");
        if (a->IMPORTARTICLE == 0)
        {
            strcat(str, "and z.importarticle = 0 ");
        }
        else if (a->IMPORTARTICLE == 1)
        {
            strcat(str, "and z.importarticle = 1 ");
        }
        if (bUsePackageSize)
        {
            strcat(str, "and z.packgroesse = ? ");
        }
        strcat(str, "and z.darreichform like ? ");
        strcat(str, "and artikellokal.artikel_nr = z.artikel_nr ");
        strcat(str, "and artikellokal.filialnr = ? ");
        strcat(str, "and ");
        strcat(str, "z.artikel_name[27,30] like ? and ");
        strcat(str, "z.artikel_name like ? and ");
        strcat(str, "z.artikel_name like ? and ");
        strcat(str, "z.artikel_name like ? ");
        if (!strcmp(cCountry, "BG"))
        {
            if (a->BESTAND > 0)
            {
                strcat(str, "and artikellokal.artikelaktiv in ('1','4') ");
            }
            strcat(str, "order by z.artikel_langname,z.einheit ");
        }
        else
        {
            strcat(str, "order by z.artikel_name,z.einheit ");
        }
    }
}
