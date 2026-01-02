/* ---------------------------------------------------------------------- *
 *                            DC_FORM.H                                  *
 * ---------------------------------------------------------------------- */

#ifndef DC_FORM_INCLUDED
#define DC_FORM_INCLUDED

#define NO_SIGNS 315
#define FILENAME "/datacare.txt"

#define PROTNAME "/protokol/p"
#define PROTEND "a.dc"
#define LINES_PER_PAGE	60

#define POSANZ_UNUSED 20

#define DCDATPOS 29
#define DCNOPOS 13

#define SPACE "  "

int  OpenDCDatei  ( FILE **fd, const char * const datei, char *errmld );
void CloseDCDatei ( FILE *fd );
int  GetDCZeile   ( FILE * fd, char *zeile );
FILE	  *fd_file; /* Handle auf datacare.txt */

int  OpenProtDatei	( FILE **fd, const char * const datei, const long date, char *errmld );
void CloseProtDatei ( FILE *fd );
int  WriteProtZeile ( FILE * fd, const struct ZDCART * const dc );
void WriteProtHead1 ( FILE * fd );
void WriteProtHead2 ( FILE * fd );
FILE	  *fd_prot; /* Handle auf protokol */

char daydate[10];
int linecount;
int pagecount;


/* Feldlängen in datacare.txt */
#define L_PZN			7
#define L_ARTKURZTXT	28
#define L_ARTTXT		28
#define L_ARTMENGE		5
#define L_ARTEINHEIT	2
#define L_KZTAXE		1
#define L_KZAPOVERL		1
#define L_ZREZEPT		2
#define L_ZKASSE		3
#define L_ZKASSEZUS		2
#define L_KZCODEIN		1
#define L_GEP			9
#define L_AEP			9
#define L_KKP			9
#define L_AVP			9
#define L_KZOHNEPRBESCH	1
#define L_MWSTCODEGR	1
#define L_MWSTCODEAPO	1
#define L_CHARGE		1 
#define L_EXPLOSIVSTOFF	1
#define L_BIOSIEGEL		1
#define L_ANTIBIOTIKUM	1
#define L_FAELSCHSICHER	1
#define L_REZEPTPFL		1
#define L_FREI_2    	1
#define L_KZVERMREZGEB	1
#define L_LIEFERANT		5
#define L_LIEFARTNR		15
#define L_DEFEKTUR		1
#define L_MINDABN		3
#define L_KZNVERFVERL	1
#define L_KZNVERFGR		1
#define L_HOEHE			4
#define L_BREITE		4
#define L_TIEFE			4
#define L_LAGERHINW		1
#define L_GEFAHRHINW	6
#define L_KZABLAUF		1
#define L_KZAPOPFL		1
#define L_REGNR			6
#define L_THERAPIEGRP	2
#define L_ARTGRP		1
#define L_KZMINIBASIS	1
#define L_AENDERCODE	1
#define L_HERSTCODE		5
#define L_GEWICHT		6
/* die beiden folgenden Felder wurden eliminiert und durch die 8 dahinterliegenden ersetzt
#define L_GRPHERSTOEKO	6	
#define L_KZOEKO		2 */
#define L_GENERIKUM 	1
#define L_ORIGINALPROD  1
#define L_ARZNEIMITTEL  1
#define L_ABGR_VERORD   1
#define L_SG_ZUBEREIT   1
#define L_SG_SUBSTANZ   1
#define L_DAT_LT_GHS	1
#define L_BEFOERD_LT_ADR 1
#define L_KZ_ABGBESCHR	2 // #define L_PSYCHOTROP	1 + #define L_NUTZTIERARZ   1
#define L_KZVERKEHR		1
#define L_KKPHAUSAPO	9
#define L_HERKUNFT		3
/* das folgende Feld wurde eliminiert und durch die 4 dahinterliegenden ersetzt
#define L_SORTINGRP		4 */
#define L_DROGAGSKAT1   1
#define L_DROGAGSKAT2   1
#define L_DROGAGSKAT3   1
#define L_BLUTKONSERVE  1
#define L_BOXERSTATT	1
#define L_DAR			3
#define L_DATERSTANL	8
#define L_DATLETZTAEND	8
#define L_DATGUELTAB	8
#define L_AUSLIEFVERS	8
#define L_NEUANLEGER	5
/* die beiden folgenden Felder wurden eliminiert und durch die 11 dahinterliegenden ersetzt
#define L_PARTNERNR		5 
#define L_REFERENZNR	9 */
#define L_RAD_AKT_ARZ	1
#define L_FUETTERARZ	1
#define L_ARZ_GEWERBE   1
#define L_DENTALARZ 	1
#define L_MEDIZINGAS	1
#define L_KONTAKTLINSE  1
#define L_ALK_UNVERST	1
#define L_ALK_VERGAELLT 1
#define L_GIFT      	1
#define L_ZYTOSTATIKUM  1

#define L_PFLANZENSCH	1
#define L_MEDPROD_ABGVO	1
#define L_MEDPROD_KLASS	1
#define L_ARTGRP_LTVO	1
//#define L_FREI_2    	4

#define L_KZNGR			1
#define L_WGRPAPOVERL	2
#define L_ARTBEZ2		28
#define L_UNNR			4

/* Feldpositionen in datacare.txt */
#define P_PZN			0
#define P_ARTKURZTXT	P_PZN			+ L_PZN
#define P_ARTTXT		P_ARTKURZTXT	+ L_ARTKURZTXT
#define P_ARTMENGE		P_ARTTXT		+ L_ARTTXT
#define P_ARTEINHEIT	P_ARTMENGE		+ L_ARTMENGE
#define P_KZTAXE		P_ARTEINHEIT	+ L_ARTEINHEIT
#define P_KZAPOVERL		P_KZTAXE		+ L_KZTAXE
#define P_ZREZEPT		P_KZAPOVERL		+ L_KZAPOVERL
#define P_ZKASSE		P_ZREZEPT		+ L_ZREZEPT
#define P_ZKASSEZUS		P_ZKASSE		+ L_ZKASSE
#define P_KZCODEIN		P_ZKASSEZUS		+ L_ZKASSEZUS
#define P_GEP			P_KZCODEIN		+ L_KZCODEIN
#define P_AEP			P_GEP			+ L_GEP
#define P_KKP			P_AEP			+ L_AEP
#define P_AVP			P_KKP			+ L_KKP
#define P_KZOHNEPRBESCH	P_AVP			+ L_AVP
#define P_MWSTCODEGR	P_KZOHNEPRBESCH + L_KZOHNEPRBESCH
#define P_MWSTCODEAPO	P_MWSTCODEGR	+ L_MWSTCODEGR
#define P_CHARGE		P_MWSTCODEAPO	+ L_MWSTCODEAPO

#define P_EXPLOSIVSTOFF	P_CHARGE		+ L_CHARGE 
#define P_BIOSIEGEL		P_EXPLOSIVSTOFF	+ L_EXPLOSIVSTOFF
#define P_ANTIBIOTIKUM  P_BIOSIEGEL		+ L_BIOSIEGEL
#define P_FAELSCHSICHER	P_ANTIBIOTIKUM	+ L_ANTIBIOTIKUM
#define P_REZEPTPFL		P_FAELSCHSICHER	+ L_FAELSCHSICHER
#define P_FREI_2		P_REZEPTPFL		+ L_REZEPTPFL
#define P_KZVERMREZGEB	P_FREI_2		+ L_FREI_2

#define P_LIEFERANT		P_KZVERMREZGEB	+ L_KZVERMREZGEB
#define P_LIEFARTNR		P_LIEFERANT		+ L_LIEFERANT
#define P_DEFEKTUR		P_LIEFARTNR		+ L_LIEFARTNR
#define P_MINDABN		P_DEFEKTUR		+ L_DEFEKTUR
#define P_KZNVERFVERL	P_MINDABN		+ L_MINDABN
#define P_KZNVERFGR		P_KZNVERFVERL	+ L_KZNVERFVERL
#define P_HOEHE			P_KZNVERFGR		+ L_KZNVERFGR
#define P_BREITE		P_HOEHE			+ L_HOEHE
#define P_TIEFE			P_BREITE		+ L_BREITE
#define P_LAGERHINW		P_TIEFE			+ L_TIEFE
#define P_GEFAHRHINW	P_LAGERHINW		+ L_LAGERHINW
#define P_KZABLAUF		P_GEFAHRHINW	+ L_GEFAHRHINW
#define P_KZAPOPFL		P_KZABLAUF		+ L_KZABLAUF
#define P_REGNR			P_KZAPOPFL		+ L_KZAPOPFL
#define P_THERAPIEGRP	P_REGNR			+ L_REGNR
#define P_ARTGRP		P_THERAPIEGRP	+ L_THERAPIEGRP
#define P_KZMINIBASIS	P_ARTGRP		+ L_ARTGRP
#define P_AENDERCODE	P_KZMINIBASIS	+ L_KZMINIBASIS
#define P_HERSTCODE		P_AENDERCODE	+ L_AENDERCODE
#define P_GEWICHT		P_HERSTCODE		+ L_HERSTCODE

/* die beiden folgenden Felder wurden eliminiert und durch die 8 dahinterliegenden ersetzt
#define P_GRPHERSTOEKO	P_GEWICHT		+ L_GEWICHT
#define P_KZOEKO		P_GRPHERSTOEKO	+ L_GRPHERSTOEKO */
#define P_GENERIKUM		P_GEWICHT		+ L_GEWICHT
#define P_ORIGINALPROD  P_GENERIKUM		+ L_GENERIKUM
#define P_ARZNEIMITTEL  P_ORIGINALPROD	+ L_ORIGINALPROD
#define P_ABGR_VERORD   P_ARZNEIMITTEL	+ L_ARZNEIMITTEL
#define P_SG_ZUBEREIT   P_ABGR_VERORD	+ L_ABGR_VERORD
#define P_SG_SUBSTANZ   P_SG_ZUBEREIT	+ L_SG_ZUBEREIT
#define P_DAT_LT_GHS	P_SG_SUBSTANZ	+ L_SG_SUBSTANZ
#define P_BEFOERD_LT_ADR P_DAT_LT_GHS	+ L_DAT_LT_GHS

#define P_KZ_ABGBESCHR	P_BEFOERD_LT_ADR	+ L_BEFOERD_LT_ADR // 1. Stelle Psychotrop; 2. Stelle Nutztierarznei
#define P_KZVERKEHR		P_KZ_ABGBESCHR	+ L_KZ_ABGBESCHR
#define P_KKPHAUSAPO	P_KZVERKEHR		+ L_KZVERKEHR
#define P_HERKUNFT		P_KKPHAUSAPO	+ L_KKPHAUSAPO

/* das folgende Feld wurde eliminiert und durch die 4 dahinterliegenden ersetzt
#define P_SORTINGRP		P_HERKUNFT		+ L_HERKUNFT */
#define P_DROGAGSKAT1	P_HERKUNFT		+ L_HERKUNFT 
#define P_DROGAGSKAT2	P_DROGAGSKAT1	+ L_DROGAGSKAT1 
#define P_DROGAGSKAT3	P_DROGAGSKAT2	+ L_DROGAGSKAT2 
#define P_BLUTKONSERVE 	P_DROGAGSKAT3	+ L_DROGAGSKAT3

#define P_BOXERSTATT	P_BLUTKONSERVE	+ L_BLUTKONSERVE
#define P_DAR			P_BOXERSTATT	+ L_BOXERSTATT
#define P_DATERSTANL	P_DAR			+ L_DAR
#define P_DATLETZTAEND	P_DATERSTANL	+ L_DATERSTANL
#define P_DATGUELTAB	P_DATLETZTAEND	+ L_DATLETZTAEND
#define P_AUSLIEFVERS	P_DATGUELTAB	+ L_DATGUELTAB
#define P_NEUANLEGER	P_AUSLIEFVERS	+ L_AUSLIEFVERS

/* die beiden folgenden Felder wurden eliminiert und durch die 11 dahinterliegenden ersetzt
#define P_PARTNERNR		P_NEUANLEGER + L_NEUANLEGER
#define P_REFERENZNR	P_PARTNERNR + L_PARTNERNR */
#define P_RAD_AKT_ARZ	P_NEUANLEGER	+ L_NEUANLEGER
#define P_FUETTERARZ	P_RAD_AKT_ARZ	+ L_RAD_AKT_ARZ
#define P_ARZ_GEWERBE	P_FUETTERARZ	+ L_FUETTERARZ
#define P_DENTALARZ 	P_ARZ_GEWERBE	+ L_ARZ_GEWERBE
#define P_MEDIZINGAS	P_DENTALARZ		+ L_DENTALARZ
#define P_KONTAKTLINSE	P_MEDIZINGAS	+ L_MEDIZINGAS
#define P_ALK_UNVERST	P_KONTAKTLINSE	+ L_KONTAKTLINSE
#define P_ALK_VERGAELLT	P_ALK_UNVERST	+ L_ALK_UNVERST
#define P_GIFT      	P_ALK_VERGAELLT	+ L_ALK_VERGAELLT
#define P_ZYTOSTATIKUM	P_GIFT			+ L_GIFT

#define P_PFLANZENSCH  	P_ZYTOSTATIKUM	+ L_ZYTOSTATIKUM
#define P_MEDPROD_ABGVO P_PFLANZENSCH	+ L_PFLANZENSCH
#define P_MEDPROD_KLASS	P_MEDPROD_ABGVO	+ L_MEDPROD_ABGVO
#define P_ARTGRP_LTVO 	P_MEDPROD_KLASS	+ L_MEDPROD_KLASS

#define P_KZNGR			P_ARTGRP_LTVO	+ L_ARTGRP_LTVO
#define P_WGRPAPOVERL	P_KZNGR			+ L_KZNGR
#define P_ARTBEZ2		P_WGRPAPOVERL	+ L_WGRPAPOVERL
#define P_UNNR			P_ARTBEZ2		+ L_ARTBEZ2

#endif
