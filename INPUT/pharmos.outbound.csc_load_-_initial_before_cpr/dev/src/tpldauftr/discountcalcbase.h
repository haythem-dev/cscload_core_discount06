#define DISCOUNTCALCBASE_PLISTE \
	"discountcalcbase.orderno," \
	"discountcalcbase.posno," \
	"discountcalcbase.posno," \
	"discountcalcbase.discountid," \
	"discountcalcbase.articleno," \
	"discountcalcbase.discountgrpno," \
	"discountcalcbase.pharmacygroupid," \
	"discountcalcbase.customerno," \
	"discountcalcbase.grpdiscounttyp," \
	"discountcalcbase.datefrom," \
	"discountcalcbase.dateto," \
	"discountcalcbase.baseqty," \
	"discountcalcbase.discountspec," \
	"discountcalcbase.discounttype," \
	"discountcalcbase.discountqty," \
	"discountcalcbase.discountvaluepct," \
	"discountcalcbase.discountqtypct," \
	"discountcalcbase.surchargepct," \
	"discountcalcbase.pharmgrpexcluded," \
	"discountcalcbase.fixedprice," \
	"discountcalcbase.refundpct," \
	"discountcalcbase.internaldiscount," \
	"discountcalcbase.discountarticle," \
	"discountcalcbase.updatesign," \
	"discountcalcbase.pharmgrpexcl_2," \
	"discountcalcbase.pharmgrpexcl_3," \
	"discountcalcbase.base_value," \
	"discountcalcbase.base_mult_std_qty," \
	"discountcalcbase.no_multiple_qty," \
	"discountcalcbase.fixeddiscountvalue," \
	"discountcalcbase.manufacturerno," \
	"discountcalcbase.artcategoryno," \
	"discountcalcbase.paymenttargetno," \
	"discountcalcbase.grossprofitpct," \
	"discountcalcbase.addondiscountok," \
	"discountcalcbase.paymenttermtype," \
	"discountcalcbase.targetqty," \
	"discountcalcbase.exceedancepct," \
	"discountcalcbase.refundtype," \
	"discountcalcbase.article_no_pack," \
	"discountcalcbase.refundvalue," \
	"discountcalcbase.promotion_no," \
	"discountcalcbase.maxqty," \
	"discountcalcbase.turnovercalcimpact," \
	"discountcalcbase.addondiscount," \
	"discountcalcbase.monthlydiscount"

#define DISCOUNTCALCBASE_LISTE_390 \
	orderno,\
	posno,\
	discountid,\
	articleno,\
	discountgrpno,\
	pharmacygroupid,\
	customerno,\
	grpdiscounttyp,\
	datefrom,\
	dateto,\
	baseqty,\
	discountspec,\
	discounttype,\
	discountqty,\
	discountvaluepct,\
	discountqtypct,\
	surchargepct,\
	pharmgrpexcluded,\
	fixedprice,\
	refundpct,\
	internaldiscount,\
	discountarticle,\
	updatesign,\
	pharmgrpexcl_2,\
	pharmgrpexcl_3,\
	base_value,\
	base_mult_std_qty,\
	no_multiple_qty,\
	fixeddiscountvalue,\
	manufacturerno,\
	artcategoryno,\
	paymenttargetno,\
	grossprofitpct,\
	addondiscountok,\
	paymenttermtype,\
	targetqty,\
	exceedancepct,\
	refundtype,\
	article_no_pack,\
	refundvalue,\
	promotion_no,\
	maxqty,\
	turnovercalcimpact,\
	addondiscount,\
	monthlydiscount

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

typedef struct N_DISCOUNTCALCBASE {
	long orderno;
	long posno;
	short discountid;
	long articleno;
	long discountgrpno;
	char pharmacygroupid[4];
	long customerno;
	short grpdiscounttyp;
	long datefrom;
	long dateto;
	long baseqty;
	short discountspec;
	short discounttype;
	short discountqty;
	double discountvaluepct;
	double discountqtypct;
	double surchargepct;
	char pharmgrpexcluded[4];
	double fixedprice;
	double refundpct;
	char internaldiscount[2];
	long discountarticle;
	char updatesign;
	char pharmgrpexcl_2[4];
	char pharmgrpexcl_3[4];
	double base_value;
	long base_mult_std_qty;
	char no_multiple_qty[2];
	double fixeddiscountvalue;
	long manufacturerno;
	long artcategoryno;
	short paymenttargetno;
	double grossprofitpct;
	char addondiscountok[2];
	char paymenttermtype[2];
	long targetqty;
	double exceedancepct;
	short refundtype;
	long article_no_pack;
	double refundvalue;
	short promotion_no;
	long maxqty;
	char turnovercalcimpact[2];
	char addondiscount[2];
	char monthlydiscount[2];

} discountcalcbaseS;

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif
