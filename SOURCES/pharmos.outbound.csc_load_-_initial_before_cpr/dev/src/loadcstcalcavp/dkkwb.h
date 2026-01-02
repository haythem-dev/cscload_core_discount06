/******************************************************************************/
/* INCLUDE FILE FOR loaddkkwb                                                 */
/******************************************************************************/

#define L_DKKWB_BRANCHNO			 2
#define L_DKKWB_CUSTOMERNO			 7
#define L_DKKWB_ABDACODE			 2
#define L_DKKWB_SURCHARGEPCT		 5
#define L_DKKWB_BASIS				 1
#define L_DKKWB_DEDUCTIONPCT		 5
#define L_DKKWB_FVKK				 1
#define L_DKKWB_FILLER				 7	

EXEC SQL BEGIN DECLARE SECTION;

struct O_DKKWB 
{
	char	BRANCHNO		[L_DKKWB_BRANCHNO  		];		 
	char  	CUSTOMERNO		[L_DKKWB_CUSTOMERNO   	];		 
	char    ABDACODE		[L_DKKWB_ABDACODE 		];		 
	char	SURCHARGEPCT	[L_DKKWB_SURCHARGEPCT	];
	char 	BASIS			[L_DKKWB_BASIS			];
	char 	DEDUCTIONPCT	[L_DKKWB_DEDUCTIONPCT	];
	char 	FVKK			[L_DKKWB_FVKK			];
	char 	FILLER			[L_DKKWB_FILLER			];
};

EXEC SQL END DECLARE SECTION;

