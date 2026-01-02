/******************************************************************************/
/* INCLUDE FILE FOR LOADCHARGE                                                */
/*     CHARGEN                                                                */
/******************************************************************************/

#define L_DSCHA_BRANCHNO			 2
#define L_DSCHA_ARTICLENO			 7
#define L_DSCHA_CHARGENNR			24
#define L_DSCHA_EXPIRYDATE	         8
#define L_DSCHA_STOCK				 7
#define L_DSCHA_STATECHARGE			 1
#define L_DSCHA_FILLER				51

EXEC SQL BEGIN DECLARE SECTION;

struct O_DSCHA 
{
	char	BRANCHNO		[L_DSCHA_BRANCHNO  		];		 
	char  	ARTICLENO		[L_DSCHA_ARTICLENO   	];		 
	char    CHARGENNR		[L_DSCHA_CHARGENNR 		];		 
	char	EXPIRYDATE		[L_DSCHA_EXPIRYDATE		];
	char 	STOCK			[L_DSCHA_STOCK			];
	char 	STATECHARGE		[L_DSCHA_STATECHARGE	];
	char 	FILLER			[L_DSCHA_FILLER			];
};

EXEC SQL END DECLARE SECTION;

