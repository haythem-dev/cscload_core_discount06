/* ---------------------------------------------------------------------- *
 *                            PROTOKOL.H                                  *
 * ---------------------------------------------------------------------- */
#define LINES_PER_PAGE	60

static struct QTYSINSTOCK {
	long Qty_71;
	long Qty_72;
	long Qty_73;
	long Qty_74;
	long Qty_77;
	long Qty_Sum;
} BufQtyInStock;

struct STOCKVALUEDIFF {
	double Diff_71;
	double Diff_72;
	double Diff_73;
	double Diff_74;
	double Diff_77;
	double Diff_Sum;
} BufStockValueDiff;

int  OpenProtDatei	( FILE **fd, char * datei, const long date, const long time, const char * const user );
void CloseProtDatei ( FILE *fd );
int  WriteProtZeile ( FILE * fd, const struct ZARTIKEL * const BufArt, struct QTYSINSTOCK * const BufQtys, const double grosso_old, const double grosso_new, const double exrate_old, const double exrate_new, const long datgueltab );
void WriteProtHead1 ( FILE * fd );
void WriteProtHead2 ( FILE * fd );
FILE	  *fd_prot;/* Handle auf protokol */

char daydate [10];
char daytime [10];
char username [10];
