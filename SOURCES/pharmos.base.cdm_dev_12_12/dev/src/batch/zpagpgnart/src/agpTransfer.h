#pragma once

typedef struct argopts {
	char  dbname[20];
	char  srvname[20];
	long  pznFrom;
	long  pznTo;
	int   importNo;
	int   progNr;
} argopts_t;

void ProgUsage(char *buf);
long ProgAuswahl(argopts_t* argopts, char *buf, size_t buflen);