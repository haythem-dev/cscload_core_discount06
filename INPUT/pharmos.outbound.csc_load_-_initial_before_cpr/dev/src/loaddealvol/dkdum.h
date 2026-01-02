/******************************************************************************/
/* INCLUDE FILE FOR LOADDEALVOL                                               */
/*     DEALER VOLUME                                                          */
/******************************************************************************/

#define L_DKDUM_BRANCHNO			 2
#define L_DKDUM_UID					 3
#define L_DKDUM_INVOICENO			10
#define L_DKDUM_VOLUMESTATE          1
#define L_DKDUM_ORDERNOPHARMOS		 5
#define L_DKDUM_ORDERNOKSC			 7
#define L_DKDUM_DATEINVOICE			 6
#define L_DKDUM_TIMEINVOICE			 6
#define L_DKDUM_VOLUME_INVOICE		11
#define N_DKDUM_VOLUME_INVOICE		 2
#define L_DKDUM_VOLUME1				11
#define N_DKDUM_VOLUME1		 		 2
#define L_DKDUM_VOLUME2				11
#define N_DKDUM_VOLUME2		 		 2
#define L_DKDUM_VOLUME3				11
#define N_DKDUM_VOLUME3		 		 2
#define L_DKDUM_VOLUME4				11
#define N_DKDUM_VOLUME4		 		 2
#define L_DKDUM_CUSTOMERNO	 		 7
#define L_DKDUM_FILLER				43



EXEC SQL BEGIN DECLARE SECTION;

struct O_DKDUM 
{
	char	BRANCHNO		[L_DKDUM_BRANCHNO  		];		 
	char  	UID				[L_DKDUM_UID       		];		 
	char    INVOICENO		[L_DKDUM_INVOICENO 		];		 
	char	VOLUMESTATE		[L_DKDUM_VOLUMESTATE	];
	char 	ORDERNOPHARMOS	[L_DKDUM_ORDERNOPHARMOS	];
	char 	ORDERNOKSC		[L_DKDUM_ORDERNOKSC		];
	char 	DATEINVOICE		[L_DKDUM_DATEINVOICE	];
	char 	TIMEINVOICE		[L_DKDUM_TIMEINVOICE	];
	char 	VOLUME_INVOICE	[L_DKDUM_VOLUME_INVOICE	];
	char	VOLUME1			[L_DKDUM_VOLUME1		];
	char	VOLUME2			[L_DKDUM_VOLUME2		];
	char	VOLUME3			[L_DKDUM_VOLUME3		];
	char	VOLUME4			[L_DKDUM_VOLUME4		];
	char	CUSTOMERNO		[L_DKDUM_CUSTOMERNO		];
	char 	FILLER 			[L_DKDUM_FILLER			];
};

EXEC SQL END DECLARE SECTION;

