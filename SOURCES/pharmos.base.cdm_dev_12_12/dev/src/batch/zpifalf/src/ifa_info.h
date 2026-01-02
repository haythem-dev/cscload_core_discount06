
/* ---------------------------------------------------------------------- *
 *                         ifa_info.h                                     *
 * ---------------------------------------------------------------------- */

#ifndef IFA_INFO_INCLUDED
#define IFA_INFO_INCLUDED

int IfaSatzName ( char *datei, char *OwnSatz, char *IfaSatz, char *errmld );

int IfaLieferung( char *liefer_datei, char *item, char **datei, int datei_max,
                  long *liefer_datum, char *idd_file, char *errmld );

int IfaLieferDatum( long *liefer_datum, char *liefer_datei, char *idd_file,
                    char *errmld );

int DatacareLieferung( char *liefer_datei, char *item, char **datei, int datei_max,
                  long *liefer_datum, char *idd_file, char *errmld );

int DatacareLieferDatum( long *liefer_datum, char *liefer_datei, char *idd_file,
                    char *errmld );
#endif

