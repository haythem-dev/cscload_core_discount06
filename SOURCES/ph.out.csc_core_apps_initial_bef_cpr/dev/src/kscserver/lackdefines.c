#include <string.h>
#include <stdio.h>
#include "lackdefines.h"

static stLACKREASONS tReasons[] =
{
	{0		,	{'0'},	""								},
	{33017  ,   {'W'},  "Transportausschluss"           },
	{50005	,	{'1'},	"fehlt zur Zeit"				},
	{50008	,	{'2'},	"nicht gefuehrt"				},
	{50004	,	{'3'},	"ausser Handel"					},
	{0		,	{'4'},	""								},
	{0		,	{'5'},	""								},
	{50007	,	{'6'},	"nicht geliefert Hersteller"	},
	{0		,	{'7'},	""								},
	{50006	,	{'8'},	"nicht lieferbar Hersteller"	},
	{0		,	{'9'},	""								},
	{50025	,	{'A'},	"nicht uber Grosshandel"		},
	{50009	,	{'B'},	"Nr. unbekannt"					},
	{0		,	{'C'},	""								},
	{50003	,	{'H'},	"keine Bezugsberechtigung"		},
	{0		,	{'M'},	""								},
	{0		,	{'N'},	""								},
	{0		,	{'P'},	""								},
	{0		,	{'Q'},	""								},
	{0		,	{'R'},	""								},
	{0		,	{'S'},	""								},
	{0		,	{'T'},	""								},
	{0		,	{'U'},	""								},
	{50036	,	{'2'},	"nicht gefuehrt"				},
	{50023	,	{'V'},	"Verbund moelich"				}
};

char *GetLackCodebyReason( long reason, char *Out )
{
    int i,x;
	Out[0] = '0';
	x = sizeof(tReasons) / sizeof(stLACKREASONS);
    for (i = 0; i < x; i++)
    {
		if(tReasons[i].lLackReason == reason)
		{
			strncpy(Out,tReasons[i].cLackCode,1);
			break;
		}
	}
	return Out;
}

