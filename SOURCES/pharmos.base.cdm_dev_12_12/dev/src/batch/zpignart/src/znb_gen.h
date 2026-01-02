
/* ---------------------------------------------------------------------- *
 *                        Z N B _ G E N . H                               *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : generiert die Nachbearbeitungsgruende               *
 *                    bei IFA-Aenderungen                                 *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 23.03.98                                            *
 *   letztes Update : 12.04.00                                            *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#ifndef NB_GEN_INCLUDED
#define NB_GEN_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define NO_WERT -1

/*----------  Felder in NB_PLAUSI ------------- */

#define  NOVALUE_PL     '9'

#define  PL_A00SSATZ     0
#define  PL_A00PZN       1
#define  PL_A00PBEZ      2
#define  PL_A00PGMENG    3
#define  PL_A00PGEINH    4
#define  PL_A00DARFO     5
#define  PL_A00ANBNR     6
#define  PL_A00ATYP      7
#define  PL_A00LKZ       8
#define  PL_A00EAN       9
#define  PL_A00ARTNR    10
#define  PL_A05VFDAT    11
#define  PL_A05LZEIT    12
#define  PL_A05KKETTE   13
#define  PL_A05TMAX     14
#define  PL_A05TMIN     15
#define  PL_A05LICHT    16
#define  PL_A05FEUCHT   17
#define  PL_A05LAGE     18
#define  PL_A05ZERBR    19
#define  PL_A04LAENGE   20
#define  PL_A04HOEHE    21
#define  PL_A04BREITE   22
#define  PL_A04GWCHT    23
#define  PL_A01AMPVAMG  24   
#define  PL_A01GEPDM    25
#define  PL_A01AEPDM    26
#define  PL_A01AVPDM    27
#define  PL_A01MWST     28
#define  PL_A02AM       29
#define  PL_A02MP       30
#define  PL_A02APPFL    31
#define  PL_A02VSPFL    32
#define  PL_A02BTM      33
#define  PL_A02TFG      34
#define  PL_A02DROCH    35
#define  PL_A02TIERAM   36
#define  PL_A02NEGLIS   37
#define  PL_A01SUVP     38
#define  PL_A03VTSTAT   39
#define  PL_A03VWGGH    40
#define  PL_A03VWGAPO   41
#define  PL_A03VWGKAP   42
#define  PL_A03VWGSEH   43
#define  PL_A03VKSTAT   44
#define  PL_A06PZNNF    45
#define  PL_ZUZAHL      46

#define  PL_A01SGEPDM   47
#define  PL_A01SAEPDM   48
#define  PL_A01SAVPDM   49

#define  PL_A02HMZV     50
#define  PL_A01AMPVSGB  51 
#define  PL_A01ZBV      52
#define  PL_TAXKENN     53
#define  PL_A01SZBV     54
#define  PL_A02LIFSTYL  55

#define  PL_A02AUSNREI  56
#define  PL_A02GENER	57
#define  PL_A02BIOSIEG  58
#define  PL_A02SDB		59
#define	 PL_A02NEM		60
#define	 PL_A06PZNORIG	61
#define	 PL_A02LEBENSM	62
#define	 PL_A02DIAET	63

#define	 PL_A02HOMOEO   64
#define	 PL_A02ANTHRO   65
#define	 PL_A02PHYTO    66
#define	 PL_A02BIOZID   67
#define	 PL_A02PSM      68
#define	 PL_A02TREZEP   69
#define	 PL_A0247AMG    70
#define  PL_A02ZULREG	71
#define  PL_A02KOSMET	72
#define  PL_A01SERSTAT  73
#define  PL_A02STERIL   74

#define  PL_A00PPN		75
#define  PL_A01SAB130A	76
#define  PL_A02VERIFIZ	77
#define  PL_A0252B		78
#define  PL_A01RESERV1	79
#define  PL_A01RESERV2	80
#define  PL_A01RESERV3	81
#define  PL_A02RESERV1	82
#define  PL_A02RESERV2	83
#define  PL_A02RESERV3	84
#define  PL_A02130A18	85
#define  PL_A02130A1A8	86
#define  PL_A01UVP      87
#define  PL_ABZUG_130	88
#define  PL_A02ELEKTRO  89
#define  PL_A02WIRKSTO  90
#define  PL_A00NTIN		91

#define  PL_A01PPU		92
#define  PL_A01APU783A  93
#define  PL_A01AEPPPU   94
#define  PL_A01AVPPPU	95
#define  PL_A02EB130B	96
#define  PL_A02EXPLOS	97
#define  PL_A02BIOTECH	98
#define	 PL_A02STIFEAR	99
#define	 PL_A02WEEEREG	100
#define	 PL_A02BATTG	101
#define  PL_A02BATTREG  PL_A02BATTG  // A02BATTREG ersetzt A02BATTG
#define	 PL_A02UNNR		102
#define	 PL_A11VERIPFL	103
#define  PL_A02SWUNDB   104
#define  PL_A02ATMP     105
#define  PL_A02AUSIMPF  106
#define  PL_A02EUNOVEL  107
#define  PL_A02ORDRUG   108
#define  PL_A02BEDZUL   109
#define  PL_A02ZULAUSN  110
#define  PL_A02AMNOG    111
#define  PL_A02PRSTRMO	112
#define  PL_A00GTIN		113
#define  PL_A00ZINNR    114
#define  PL_A00OEVNR    115

/* ---------- IFA Version 20244 -------------- */
#define  PL_A02AMDARKI  116
#define  PL_A02AMAUFFB  117
#define  PL_A02AMBEKI   118
#define  PL_A02AMVEKRW  119
#define  PL_A01DAPU78   120
#define  PL_A02D130A18  121

/* ---------- IFA Version 20248 -------------- */
#define  PL_A02MEDCG    122
#define  PL_A05LGTMPB   123

/* ---------- IFA Version 20252 -------------- */
#define  PL_A01B130B1C  124
#define  PL_A01DAT78    125
#define  PL_A01RAB130A  126
#define  PL_A01ZUZAH61  127

/*----------  Felder in NB_ZWING ------------- */

#define ZW_SONDER_GEP        0
#define ZW_AEP_GR_GEP        1
#define ZW_AVP_GR_AEP        2
#define ZW_PROZ_PLUS_MINUS   3
#define ZW_GEP_AUF_NULL      4
#define ZW_AEP_AUF_NULL      5
#define ZW_GEP_TROTZ_PPE     6
#define ZW_AEP_TROTZ_PPE     7
#define ZW_GEP_TROTZ_PARAM   8
#define ZW_AEP_TROTZ_PARAM   9
#define ZW_TAXPRUEFGROSSO   10
#define ZW_PRDIFF_OHNE_KEY  11
#define ZW_PRDIFF_SAMEDATE  12

#define ZW_LOESCH_KENN_NEU  13
#define ZW_ART_OHNE_PREIS   14
#define ZW_EAN_MEHRFACH     15
#define ZW_NTIN_MEHRFACH    16
#define ZW_GTIN_MEHRFACH    17
#define ZW_PROZ_PLUS        18
#define ZW_PROZ_MINUS       19
#define ZW_PZNNF_GLEICH     20
#define ZW_TAXPRUEF         21
#define ZW_PREISPRUEF       22
#define ZW_PREIS_ZUGROSS    23
#define ZW_IFA_COMPLETE     24
#define ZW_IFADAT_01012002  25
#define ZW_IFADAT_ARTDAT    ZW_IFADAT_01012002
#define ZW_REWE_SONDER_GEP	26
#define ZW_KOMB_LEBENSM_NEM_DIAET	27
#define ZW_NO_FMD_CHECK_REQUIRED 28

/*----------  Felder in NB_NZWING ------------- */

#define NZ_PRDIFF            0
#define NZ_PZNNF_NVOR        1
#define NZ_PZNNF_DIFF        2
#define NZ_PREISE_UNG        3
#define NZ_MWST_DIFF         4
#define NZ_LOESCH_AH_AV      5
#define NZ_AEN_BEI_AH        6
#define NZ_NURKVA_PRUEF      7
#define NZ_VTBIFA_PRUEF      8
#define NZ_IFA_COMPLETE      9
#define NZ_AEND_NEM			 10
#define NZ_NEM_DLM_LM_NEU	 11
#define NZ_AEP_EQ_GR_UEBN	 12
#define NZ_AEP_EQ_GR_CALC	 13
#define NZ_NO_BIOZID		 14
#define NZ_NO_PSM			 15
#define NZ_PREISE_GROSSO_AEP 16
#define NZ_EAN_DIFF          17
#define NZ_NTIN_DIFF         18
#define NZ_GTIN_DIFF		 19
#define NZ_UNNR_DIFF		 20
#define NZ_NO_KOSMETIKUM	 21
#define NZ_EAR_REG_MISSING   22
#define NZ_EAR_REG_REDUNDANT 23
#define NZ_REG_ELECTRO_IFA_REG_MISSING 24
#define NZ_REG_ELECTRO_IFA_EAR_MISSING 25
#define NZ_CHG_ELECTRO_REG	 26
#define NZ_CHG_BATTREG_REG	 27
#define NZ_CHG_BATTG_IFA     28
#define NZ_UNKNOWN_ELECTRO   29
#define NZ_WRONG_ELECTRO_REG 30
#define NZ_EAR_DIFF          31
#define NZ_EAN_DUPL_IGNORED  32
#define NZ_GROSSO_AEP_NULL_ART 33
#define NZ_GR_EQ_AEP_CALC    34
#define NZ_AEP_ART_GRO       35
#define NZ_IFA_AH_NOPRICE    36


/*----------  Structur der Meldung ------------ */

struct ERR_Meldung
{
  int key;
  char *meldung;
};

/* ---------- Prototyping ------------------------ */

char *GetIfaErrMeld( struct ERR_Meldung *err, int key );
void SetIfaErr( char* Wert, char *ZulWerte, char *Feld, int key );
void SetIfa2Err( char* Wert, char *ZulWerte, char *Feld, int key );
void SetIfaShortErr(short Wert, short minVal, short maxVal, char* Feld, int key);
void SetIfaShort2Err(short Wert, short minVal, short maxVal, short addVal, char* Feld, int key);
void SetIfaNumErr( long Wert, char *Feld, int key );
void SetIfaPdmErr( double Wert, char *Feld, int key );
void SetIfaNumBlankErr( char* Wert, char *Feld, int key );
void SetIfaGroesser( double Wert1, double Wert2, char *Feld, int key );
void SetIfaGleich( char* Wert1, char* Wert2, char *Feld, int key );
void SetIfaTrueFalse( int true_false, char *Feld, int key );
int  IsIfaFeldErr( char *Feld, int key );
int  IsIfaErr( char *Feld );
void SetIfaGueltigabErr( long datum, char *Feld, int key );
void SetIfaZuzahlErr( char *Wert, char *Feld, int key );
char *Get_ZW_ErrMeld( int key );
char *Get_NZ_ErrMeld( int key );
char *Get_PL_ErrMeld( int key );
void SetIfaCharNumErr(char* Wert, int minVal, int maxVal, int lng, char* Feld, int key);
void  SetIfaTaxeErr( char *Wert1, int key1, char *Wert2, int key2, char *Feld, int key ); 


#ifdef __cplusplus
}
#endif

#endif /* NB_GEN_INCLUDED */

