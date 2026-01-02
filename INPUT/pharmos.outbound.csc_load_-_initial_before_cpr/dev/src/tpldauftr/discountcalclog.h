#define DISCOUNTCALCLOG_PLISTE \
	"discountcalclog.orderno," \
	"discountcalclog.posno," \
	"discountcalclog.calculatortype," \
	"discountcalclog.discountvalue," \
	"discountcalclog.discountpercent," \
	"discountcalclog.discountqty," \
	"discountcalclog.rebateinkindposno"

#define DISCOUNTCALCLOG_LISTE_390 \
	orderno,\
	posno,\
	calculatortype,\
	discountvalue,\
	discountpercent,\
	discountqty,\
	rebateinkindposno

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

typedef struct N_DISCOUNTCALCLOG {
	long orderno;
	long posno;
	short calculatortype;
	double discountvalue;
	double discountpercent;
	short discountqty;
	long rebateinkindposno;
} discountcalclogS;

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

