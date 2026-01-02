/* ---------------------------------------------------------------------- *
 *                       ZPLFZART_FORM.H                                  *
 * ---------------------------------------------------------------------- */

#ifndef ZPLFZART_FORM_INCLUDED
#define ZPLFZART_FORM_INCLUDED

#define MAX_LENGTH_MWE 80 /* maximum length of one row in mwe.txt */
#define MAX_LENGTH_EAN 80 /* maximum length of one row in ean.txt */
#define MAX_LENGTH_HI  80 /* maximum length of one row in abda- files */

#define FILENAME_MWE "/mwe.txt"
#define FILENAME_EAN "/ean.txt"

#define FILENAME_HI_IZG "/IZG_APO.txt"
#define FILENAME_HI_IKZ "/IKZ_APO.txt"
#define FILENAME_HI_PZG "/PZG_APO.txt"
#define FILENAME_ATC	"/PAC_APO.txt"

/* --------  file -------------- */
#define FILE_DELIMITER_MWE	";"
#define NUMBER_FIELDS_MWE	8

#define FILE_DELIMITER_EAN	";"
#define NUMBER_FIELDS_EAN	2

#define FILE_DELIMITER_ABDA	";"
#define NUMBER_FIELDS_ABDA	3

int  OpenMWEDatei  ( FILE **fd, const char * const datei, char *errmld );
void CloseMWEDatei ( FILE *fd );
int  GetMWEZeile   ( FILE * fd, char *zeile );
FILE	  *fd_mwefile; /* Handle auf mwe.txt */

int  OpenEANDatei  ( FILE **fd, const char * const datei, char *errmld );
void CloseEANDatei ( FILE *fd );
int  GetEANZeile   ( FILE * fd, char *zeile );
FILE	  *fd_eanfile; /* Handle auf mwe.txt */

int  OpenHealthInsuranceDatei  ( FILE **fd, const char * const datei, char *errmld );
void CloseHealthInsuranceDatei ( FILE *fd );
int  GetHealthInsuranceZeile   ( FILE * fd, char *zeile );
FILE	  *fd_healthinsurancefile; /* Handle auf izg_apo.txt / ikz_apo.txt / pzg_apo.txt */

#endif
