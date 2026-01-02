#define ORDERPOSITIONDISCOUNT_PLISTE \
	"orderpositiondiscount.orderno," \
	"orderpositiondiscount.posno," \
	"orderpositiondiscount.discountmode," \
	"orderpositiondiscount.discountvalue," \
	"orderpositiondiscount.discountpercent," \
	"orderpositiondiscount.discountqty," \
	"orderpositiondiscount.rebateinkindorderno," \
	"orderpositiondiscount.rebateinkindposno," \
	"orderpositiondiscount.pharmacygroupid"

#define ORDERPOSITIONDISCOUNT_LISTE_390 \
	orderno,\
	posno,\
	discountmode,\
	discountvalue,\
	discountpercent,\
	discountqty,\
	rebateinkindorderno,\
	rebateinkindposno,\
	pharmacygroupid

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

typedef struct N_ORDERPOSITIONDISCOUNT {
	long orderno;
	long posno;
	short discountmode;
	double discountvalue;
	double discountpercent;
	short discountqty;
	long rebateinkindorderno;
	long rebateinkindposno;
	char pharmacygroupid[4];
} orderpositiondiscountS;

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif
