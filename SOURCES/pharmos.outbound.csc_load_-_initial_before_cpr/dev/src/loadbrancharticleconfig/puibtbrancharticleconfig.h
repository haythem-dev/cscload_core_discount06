#define PUIBTBRANCHARTICLECONFIG_PLISTE \
	"puibtbrancharticleconfig.ARTICLENO," \
	"puibtbrancharticleconfig.BRANCHNO," \
	"puibtbrancharticleconfig.IBTROLETYPEID," \
	"puibtbrancharticleconfig.ASSORTMENTTYPEID," \
	"puibtbrancharticleconfig.LASTCHANGEDATETIME," \
	"puibtbrancharticleconfig.RELEVANCEFLAG"

#define PUIBTBRANCHARTICLECONFIG_LISTE_390 \
	ARTICLENO,\
	BRANCHNO,\
	IBTROLETYPEID,\
	ASSORTMENTTYPEID,\
	LASTCHANGEDATETIME,\
	RELEVANCEFLAG

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

typedef struct N_PUIBTBRANCHARTICLECONFIG {
	long ARTICLENO;
	short BRANCHNO;
	short IBTROLETYPEID;
	short ASSORTMENTTYPEID;
	datetime LASTCHANGEDATETIME;
	short RELEVANCEFLAG;
} puibtbrancharticleconfigS;

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

