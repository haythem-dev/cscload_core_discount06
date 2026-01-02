/******************************************************************************/
/* INCLUDE FILE FOR LOADCSTDISCACC                                            */
/*     CUSTOMER DISCOUNT ACCOUNT                                              */
/******************************************************************************/

#define L_DKRKS_BRANCHNO			 2
#define L_DKRKS_CSTNO				 7
#define L_DKRKS_BELEG_TYP			 2
#define L_DKRKS_FILLER1				 1
#define L_DKRKS_BELEG_NR			10
#define L_DKRKS_LFDNR				 3
#define L_DKRKS_MAINCSTNO			 7
#define L_DKRKS_DATUM				 6
#define L_DKRKS_BETRAG				10
#define L_DKRKS_BALANCE				10
#define L_DKRKS_TARGET				 6
#define L_DKRKS_PRIO				 1
#define L_DKRKS_AUFNR				 7
#define L_DKRKS_AUFNR_TEIL			 7
#define L_DKRKS_ABRTYP				 1
#define L_DKRKS_FILLER				20


EXEC SQL BEGIN DECLARE SECTION;

struct O_DKRKS
{
	char    			BRANCHNO	[L_DKRKS_BRANCHNO	];
	char    			CSTNO		[L_DKRKS_CSTNO		];
	char    			BELEG_TYP	[L_DKRKS_BELEG_TYP	];
	char    			FILLER1		[L_DKRKS_FILLER1	];
	char    			BELEG_NR	[L_DKRKS_BELEG_NR	];
	char    			LFDNR		[L_DKRKS_LFDNR		];
	char    			MAINCSTNO	[L_DKRKS_MAINCSTNO	];
	char    			DATUM		[L_DKRKS_DATUM		];
	char    			BETRAG		[L_DKRKS_BETRAG		];
	char    			BALANCE		[L_DKRKS_BALANCE	];
	char    			TARGET		[L_DKRKS_TARGET		];
	char    			PRIO		[L_DKRKS_PRIO		];
	char    			AUFNR		[L_DKRKS_AUFNR		];
	char    			AUFNR_TEIL	[L_DKRKS_AUFNR_TEIL	];
	char    			ABRTYP		[L_DKRKS_ABRTYP		];
	char    			FILLER		[L_DKRKS_FILLER		];
};

EXEC SQL END DECLARE SECTION;

