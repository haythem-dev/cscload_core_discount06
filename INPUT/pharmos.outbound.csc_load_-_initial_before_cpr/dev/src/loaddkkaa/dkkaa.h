/******************************************************************************/
/* INCLUDE FILE FOR LOADPAYTERM                                               */
/*     SAP PAYMENT TERMS                                                      */
/******************************************************************************/

#define L_DKKAA_FIL        2
#define L_DKKAA_IDF        7
#define L_DKKAA_AA         2
#define L_DKKAA_ART        3
#define L_DKKAA_STF        5
#define L_DKKAA_VVMO       2
#define L_DKKAA_VMO        2
#define L_DKKAA_NATRA      1
#define L_DKKAA_NETTO      1
#define L_DKKAA_BANR       1
#define L_DKKAA_MORAB      1
#define L_DKKAA_VSP        1
#define L_DKKAA_VBSP       1
#define L_DKKAA_MSV3       1
#define L_DKKAA_FRAUKE     2
#define L_DKKAA_TLIEF      1
#define L_DKKAA_AKENN      10
#define L_DKKAA_FILL       32


EXEC SQL BEGIN DECLARE SECTION;

struct O_DKKAA 
{
	char    			FIL        [L_DKKAA_FIL		];
	char    			IDF        [L_DKKAA_IDF		];
	char    			AA         [L_DKKAA_AA		];
	char    			ART        [L_DKKAA_ART		];
	char    			STF        [L_DKKAA_STF		];
	char    			VVMO       [L_DKKAA_VVMO	];
	char    			VMO        [L_DKKAA_VMO		];
	char    			NATRA      [L_DKKAA_NATRA	];
	char    			NETTO      [L_DKKAA_NETTO	];
	char    			BANR       [L_DKKAA_BANR	];
	char    			MORAB      [L_DKKAA_MORAB	];
	char    			VSP        [L_DKKAA_VSP		];
	char    			VBSP       [L_DKKAA_VBSP	];
	char    			MSV3       [L_DKKAA_MSV3	];
	char    			FRAUKE     [L_DKKAA_FRAUKE	];
	char    			TLIEF      [L_DKKAA_TLIEF	];
	char    			AKENN      [L_DKKAA_AKENN	];
	char    			FILL       [L_DKKAA_FILL	];
};

EXEC SQL END DECLARE SECTION;

