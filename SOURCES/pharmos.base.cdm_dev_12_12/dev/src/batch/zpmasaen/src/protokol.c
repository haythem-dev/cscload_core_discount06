
/* ---------------------------------------------------------------------- *
 *                          protokol.c                                     *
 * ---------------------------------------------------------------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <zartikel.h>

#include "protokol.h"

/* ---------------------------------------------------------------------- */
void  WriteProtHead1 ( FILE * fd ) 
{
	/* 1st headerline */
	fputs("PROGRAM:  ZPMASAEN  (9)  ", fd);
	fputs("CONVERTED ARTICLE PRICES    ", fd);
	fputs("       DATE:  ", fd);
	fputs(daydate, fd);
	fputs("       TIME:  ", fd);
	fputs(daytime, fd);
	fputs("       USER:  ", fd);
	fputs(username, fd);
	fputs("\n", fd);
	fputs("\n", fd);
}

/* ---------------------------------------------------------------------- */
void  WriteProtHead2 ( FILE * fd )
{
	/* 2nd headerline */
	fputs(" ARTICLENO    UNITY     ARTICLENAME                      SUPPLIERNO  DATE_VALID_FROM  PURCH_PRICE-OLD  PURCH_PRICE-NEW  EXCHANGE_RATE-OLD  EXCHANGE_RATE-NEW  QTY_71  QTY_72  QTY_73  QTY_74  QTY_77 QTY_TOTAL\n",fd);
	fputs("\n", fd);
}

/* ---------------------------------------------------------------------- */
int  OpenProtDatei	( FILE **fd, char * datei, const long date, const long time, const char * const user )
{
	char dat [100];
    	
	sprintf(daydate, "%ld", date);
	sprintf(daytime, "%06ld", time);
	sprintf(username, "%s", user);

	strcpy(dat, datei);
	strcat(dat, daydate);
	strcat(dat, "-");
	strcat(dat, daytime);
	strcat(dat, ".cep");

	*fd = fopen(dat, "wt");
	if (*fd == NULL)
	{
		return 1;
    }
	else
	{
		WriteProtHead1(*fd);
		WriteProtHead2(*fd);
	}
	
    return 0;
}

/* ---------------------------------------------------------------------- */
void CloseProtDatei ( FILE *fd )
{
	char value[20];
	char * replace;
	
	if (fd != NULL)
	{
		fputs("\n   STOCK VALUE DIFFERENCES   71: ", fd);
		sprintf(value, "%012.2f", BufStockValueDiff.Diff_71);
		replace = strchr(value, '.');
		*replace = ',';
		fputs(value, fd);
		
		fputs(";    72: ", fd);
		sprintf(value, "%012.2f", BufStockValueDiff.Diff_72);
		replace = strchr(value, '.');
		*replace = ',';
		fputs(value, fd);	

		fputs(";    73: ", fd);
		sprintf(value, "%012.2f", BufStockValueDiff.Diff_73);
		replace = strchr(value, '.');
		*replace = ',';
		fputs(value, fd);	
		
		fputs(";    74: ", fd);
		sprintf(value, "%012.2f", BufStockValueDiff.Diff_74);
		replace = strchr(value, '.');
		*replace = ',';
		fputs(value, fd);	

		fputs(";    77: ", fd);
		sprintf(value, "%012.2f", BufStockValueDiff.Diff_77);
		replace = strchr(value, '.');
		*replace = ',';
		fputs(value, fd);	

		fputs(";    TOTAL: ", fd);
		sprintf(value, "%012.2f", BufStockValueDiff.Diff_Sum);
		replace = strchr(value, '.');
		*replace = ',';
		fputs(value, fd);	

		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int  WriteProtZeile ( FILE * fd, const struct ZARTIKEL * const BufArt, struct QTYSINSTOCK * const BufQtys, const double grosso_old, const double grosso_new, const double exrate_old, const double exrate_new, const long datgueltab)
{
	char val[64];
	char * replace;
	
	sprintf(val, " %07ld    ", BufArt->ARTIKEL_NR);
	fputs(val, fd);

	fputs(BufArt->EINHEIT, fd);
	fputs("   ", fd);
	
	fputs(BufArt->ARTIKEL_NAME, fd);
	
	sprintf(val, "       %04ld      ", BufArt->HERSTELLER_NR);
	fputs(val, fd);

	sprintf(val, "%ld          ", datgueltab);
	fputs(val, fd);

	sprintf(val, "%09.2f        ", grosso_old);
	replace = strchr(val, '.');
	*replace = ',';
	fputs(val, fd);

	sprintf(val, "%09.2f        ", grosso_new);
	replace = strchr(val, '.');
	*replace = ',';
	fputs(val, fd);

	sprintf(val, "%09.5f          ", exrate_old);
	replace = strchr(val, '.');
	*replace = ',';
	fputs(val, fd);

	sprintf(val, "%09.5f        ", exrate_new);
	replace = strchr(val, '.');
	*replace = ',';
	fputs(val, fd);

	sprintf(val, "%05ld   ", BufQtys->Qty_71);
	fputs(val, fd);

	sprintf(val, "%05ld   ", BufQtys->Qty_72);
	fputs(val, fd);

	sprintf(val, "%05ld   ", BufQtys->Qty_73);
	fputs(val, fd);

	sprintf(val, "%05ld   ", BufQtys->Qty_74);
	fputs(val, fd);

	sprintf(val, "%05ld   ", BufQtys->Qty_77);
	fputs(val, fd);

	sprintf(val, "%05ld", BufQtys->Qty_Sum);
	fputs(val, fd);


	/* linefeed*/
	fputs("\n", fd);
	
	// calculate stock value differences to print at last protocol line:
	BufStockValueDiff.Diff_71 += ( grosso_new - grosso_old ) * BufQtys->Qty_71;
	BufStockValueDiff.Diff_72 += ( grosso_new - grosso_old ) * BufQtys->Qty_72;
	BufStockValueDiff.Diff_73 += ( grosso_new - grosso_old ) * BufQtys->Qty_73;
	BufStockValueDiff.Diff_74 += ( grosso_new - grosso_old ) * BufQtys->Qty_74;
	BufStockValueDiff.Diff_77 += ( grosso_new - grosso_old ) * BufQtys->Qty_77;
	BufStockValueDiff.Diff_Sum +=( grosso_new - grosso_old ) * BufQtys->Qty_Sum;

	return 0;
}
