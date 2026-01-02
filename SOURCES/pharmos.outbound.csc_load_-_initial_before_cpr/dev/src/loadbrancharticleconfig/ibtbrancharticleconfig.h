#define IBTBRANCHARTICLECONFIG_PLISTE \
	"ibtbrancharticleconfig.articleno," \
	"ibtbrancharticleconfig.branchno," \
	"ibtbrancharticleconfig.ibttypeid," \
	"ibtbrancharticleconfig.ibtassortmenttypeid," \
	"ibtbrancharticleconfig.ibtonlyflag," \
	"ibtbrancharticleconfig.lastchangedatetime"

#define IBTBRANCHARTICLECONFIG_LISTE_390 \
	articleno,\
	branchno,\
	ibttypeid,\
	ibtassortmenttypeid,\
	ibtonlyflag,\
	lastchangedatetime

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

typedef struct N_IBTBRANCHARTICLECONFIG {
	long articleno;
	short branchno;
	short ibttypeid;
	short ibtassortmenttypeid;
	short ibtonlyflag;
	datetime lastchangedatetime;
} ibtbrancharticleconfigS;

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

