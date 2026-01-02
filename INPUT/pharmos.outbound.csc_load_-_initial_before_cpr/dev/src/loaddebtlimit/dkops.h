/******************************************************************************/
/* INCLUDE FILE FOR LOADDEBTLIMIT	                                          */
/* OFFENE BETRAEGE				                                              */
/******************************************************************************/

#define L_DKOPS_BRANCHNO			 2
#define L_DKOPS_IDF					 7
#define L_DKOPS_BETRAG				11
#define L_DKOPS_KRED				 9
#define L_DKOPS_BETRAGL5			11
#define L_DKOPS_KREDK1				 9
#define L_DKOPS_LISTE5				 1
#define L_DKOPS_FILLER				30


EXEC SQL BEGIN DECLARE SECTION;

struct O_DKOPS
{
	char    			BRANCHNO	[L_DKOPS_BRANCHNO	];
	char    			IDF			[L_DKOPS_IDF		];
	char    			BETRAG		[L_DKOPS_BETRAG		];
	char    			KRED		[L_DKOPS_KRED		];
	char    			BETRAGL5	[L_DKOPS_BETRAG		];
	char    			KREDK1		[L_DKOPS_KRED		];
	char    			LISTE5		[L_DKOPS_LISTE5		];
	char    			FILLER		[L_DKOPS_FILLER		];
};

EXEC SQL END DECLARE SECTION;
