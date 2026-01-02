
/* ---------------------------------------------------------------------- *
 *   Aufgabe        : generiert die Nachbearbeitungsgruende               *
 *                    bei LogINdex-Aenderungen                            *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 31.01.2005                                          *
 *   Autor          : Hörath                                              *
 * ---------------------------------------------------------------------- */

#ifndef NB_GEN_LI_INCLUDED
#define NB_GEN_LI_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define NO_WERT -1

/*NB_PLAUSI, NB_ZWING, NB_NZWING*/
#define NB_PL_NO_VAL '9'
#define NB_PL_OK	 '0'
#define NB_PL_ERR	 '1'

/*LISTATUS*/
#define LISTATUS_FREIGEG	"F"
#define LISTATUS_GESPERRT	"S"

/*ZAENDERUNG*/
#define ZAENDERUNG_AEND				"1"
#define ZAENDERUNG_NEU				"0"
#define ZAENDERUNG_AEND_UNVOLLST	"3"
#define ZAENDERUNG_NEU_UNVOLLST		"2"

/*NBSTATUS */
#define NBSTATUS_NO_ERR		"0"
#define NBSTATUS_PLAUSI		"4"
#define NBSTATUS_ZWING		"2"
#define NBSTATUS_NZWING		"1"
#define NBSTATUS_ZWING_PL	"6"
#define NBSTATUS_ZW_PL_NZW	"7"
#define NBSTATUS_ZWING_NZW	"3"
#define NBSTATUS_NZW_PL		"5"

/*----------  Feldpositionen in NB_PLAUSI ------------- */
#define PL_PHAR			0
#define PL_CDSO1		1
#define PL_PRDNO		2
#define PL_SMCAT		3
#define PL_SMNO			4
#define PL_CLINCD		5
#define PL_VAT			6
#define PL_COOL			7
#define PL_CDBG			8
#define PL_BG			9
#define PL_EXP			10
#define PL_QTY			11
#define PL_DSCRD		12
#define PL_DSCRF		13
#define PL_DSCRLONGD	14
#define PL_DSCRLONGF	15
#define PL_QTYUD		16
#define PL_QTYUF		17
#define PL_PCKTYPD		18
#define PL_PCKTYPF		19
#define PL_NOPCS		20
#define PL_NINCD		21
#define PL_DEPCD		22
#define PL_OUTSAL		23
#define PL_STTOX		24
#define PL_CE			25
#define PL_SMCDAT		26
#define PL_SIST			27
#define PL_ESIST		28
#define PL_BIOCID		29
#define PL_BAGNO		30
#define PL_BAGDOSSIER	31
#define PL_COMPNO		32
#define PL_BC			33
#define PL_PHAR2		34
#define PL_VDAT			35
#define PL_PRICE_PEXF	36
#define PL_PRICE_PPUB	37
#define PL_MIGCD		38
#define PL_GENCD		39
#define PL_ATC			40	
#define PL_ARTNO1		41
#define PL_SUPPLNO		42
#define PL_PICTOGRAM01_FLAG		43
#define PL_PICTOGRAM02_FLAG		44
#define PL_PICTOGRAM03_FLAG		45
#define PL_PICTOGRAM04_FLAG		46
#define PL_PICTOGRAM05_FLAG		47
#define PL_PICTOGRAM06_FLAG		48
#define PL_PICTOGRAM07_FLAG		49
#define PL_PICTOGRAM08_FLAG		50
#define PL_PICTOGRAM09_FLAG		51
#define PL_GS_EXPLOSION			52
#define PL_GS_HOCHENTZ			53
#define PL_GS_LEICHTENTZ		54
#define PL_GS_BRAND				55
#define PL_GS_AETZEND			56
#define PL_GS_SEHRGIFTIG		57
#define PL_GS_GIFTIG			58
#define PL_GS_GESUNDHSCH		59
#define PL_GS_REIZEND			60
#define PL_GS_UMWELT			61
#define PL_SDS_DATE_DE			62
#define PL_HAZARDSTATEMENT		63
#define PL_GTIN14				64
#define PL_SALECD				65
#define PL_GRPCD				66
#define PL_BLOOD				67
#define PL_PRDGRPCD				68
#define PL_G_UN_NR				69  
#define PL_FMD_FLAG             70  
#define PL_SDS_DATE_IT			71
#define PL_SDS_DATE_EN			72
#define PL_SDS_DATE_FR			73
#define PL_BIOSIM				74

#define PL_AFTER_LAST			75

/*----------  Felder in NB_ZWING -------------- */
#define ZW_GEP_ERR			 0
#define ZW_EAN_DIFF			 1
#define ZW_EAN_MEHRFACH		 2
#define ZW_PZNNF_GLEICH      3
#define ZW_HNR_UNSET		 4
#define ZW_CHANGE_BTM		 5 
#define ZW_CHANGE_PSYCHOTROP 6
#define ZW_CHANGE_COOL		 7
#define ZW_CHANGE_NAME		 8
#define ZW_CHANGE_HNR		 9
#define ZW_CHANGE_AWL		 10
#define ZW_GTIN14_EXISTS	 11
#define ZW_CHANGE_PRICE		 12

/*----------  Felder in NB_NZWING -------------- */
#define NZ_GEP_HINW				0
#define NZ_AH_PRICE_CHANGE		1
// #define NZ_CHANGE_BTM		2 // not used anymore
#define NZ_CHANGE_AH			3
#define NZ_CHANGE_RR			4
#define NZ_CHANGE_IKSCODE		5
#define NZ_PZNNF_NVOR			6
#define NZ_CHANGE_HAZARDNOTES	7
#define NZ_HINT_BLOOD		    8


/*----------  Structur der Meldung ------------ */
struct ERR_MeldungLI
{
  int key;
  char *meldung;
};

/* ---------- Prototyping ------------------------ */
void SetLIErr( char* Wert, char *ZulWerte, char *Feld, int key );
void SetLIErrInt( int Wert, char *ZulWerte, char *Feld, int key );
void SetLI2Err( char* Wert, char *ZulWerte, char *Feld, int key );
void SetLINumErr( long Wert, char *Feld, int key );
void SetLIPreisErr( double Wert, char *Feld, int key );
void SetLINumBlankErr( char* Wert, char *Feld, int key );

void SetLIGroesser( double Wert1, double Wert2, char *Feld, int key );
void SetLIGleich( char* Wert1, char* Wert2, char *Feld, int key );
void SetLITrueFalse( int true_false, char *Feld, int key );
void SetLIGueltigabErr( long datum, char *Feld, int key );

int  IsLIFeldErr( char *Feld, int key );
int  IsLIErr( char *Feld );

char *GetLIErrMeld( struct ERR_MeldungLI *err, int key );
char *Get_ZW_ErrMeldLI( int key );
char *Get_NZ_ErrMeldLI( int key );
char *Get_PL_ErrMeldLI( int key );

#ifdef __cplusplus
}
#endif

#endif /* NB_GEN_LI_INCLUDED */
