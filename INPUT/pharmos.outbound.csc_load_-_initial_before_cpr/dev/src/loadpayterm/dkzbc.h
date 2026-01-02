/******************************************************************************/
/* INCLUDE FILE FOR LOADPAYTERM                                               */
/*     SAP PAYMENT TERMS                                                      */
/******************************************************************************/

#define L_DKZBC_SAPCODE				 4
#define L_DKZBC_ZMOD				 3
#define L_DKZBC_TAB					10
#define L_DKZBC_TAB_DAYS			 3
#define L_DKZBC_TAB_CASHDISCOUNT	 4
#define N_DKZBC_TAB_CASHDISCOUNT	 2
#define L_DKZBC_CHANGEDATE			 8
#define L_DKZBC_USER				 3
#define L_DKZBC_DELFLAG				 1
#define L_DKZBC_FILLER				61


EXEC SQL BEGIN DECLARE SECTION;

struct O_DKZBC_TAB
{
	char	DAYS			[L_DKZBC_TAB_DAYS        ];		/* PAYMENT PERIOD IN DAYS */
	char	CASHDISCOUNT	[L_DKZBC_TAB_CASHDISCOUNT];		/* CASH DISCOUNT          */
};

struct O_DKZBC 
{
	char    			SAPCODE		[L_DKZBC_SAPCODE   ];		 
	char    			ZMOD		[L_DKZBC_ZMOD      ];		 
	struct O_DKZBC_TAB	TABLE		[L_DKZBC_TAB       ];		 
	char    			CHANGEDATE	[L_DKZBC_CHANGEDATE];		 
	char    			USER		[L_DKZBC_USER      ];		 
	char    			DELFLAG		[L_DKZBC_DELFLAG   ];		 
	char				FILLER		[L_DKZBC_FILLER    ];		 
};

EXEC SQL END DECLARE SECTION;

