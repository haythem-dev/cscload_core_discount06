#ifndef _ZPMASAEN_COMMON_H_
#define _ZPMASAEN_COMMON_H_

/*
** Prog 1 options, raw (as per
** command line) and "cooked"
*/
typedef struct {
	char progname[100];
	char db[9];
	char user[9];
	char cHnr[7];
	char cGroAlt[12];
	char cAepAlt[12];
	char cAvpAlt[12];
	char cEAvpAlt[12];
	char cAgpAlt[12];
	char cGroNeu[12];
	char cAepNeu[12];
	char cAvpNeu[12];
	char cEAvpNeu[12];
	char cAgpNeu[12];
	char cDatum[10];
	long   lHnr;
	double dGroAlt;
	double dAepAlt;
	double dAvpAlt;
	double dEAvpAlt;
	double dAgpAlt;
	double dGroNeu;
	double dAepNeu;
	double dAvpNeu;
	double dEAvpNeu;
	double dAgpNeu;
	long   lDatum;
        char   hasAGP;
} opt_prog1_t;

#endif
