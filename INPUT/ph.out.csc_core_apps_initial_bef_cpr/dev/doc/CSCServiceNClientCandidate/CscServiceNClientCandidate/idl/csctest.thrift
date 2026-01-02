namespace cpp csc.test
namespace csharp Csc.Test

enum CountryEnum
{
	COUNTRY_AUSTRIA 				= 0,	// "AT"
	COUNTRY_AUSTRIA_PREWHOLE		= 1,	// "AU"
	COUNTRY_BULGARIA				= 2,	// "BG"
	COUNTRY_CROATIA 				= 3,	// "HR"
	COUNTRY_GERMANY_NORTH			= 4,	// "DE"
	COUNTRY_GERMANY_SOUTH			= 5,	// "DE"
	COUNTRY_FRANCE					= 6,	// "FR"
	COUNTRY_FRANCE_PREWHOLE 		= 7,	// "PF"
	COUNTRY_SERBIA					= 8,	// "RS"
	COUNTRY_SWITZERLAND 			= 9,	// "CH"
	COUNTRY_SWITZERLAND_PREWHOLE	= 10,	// "CH"
}

enum DeveloperEnum
{
	DEV_KESSLING = 1,
	DEV_EGERER,
	DEV_BOUMA,
	DEV_IMSCHWEILER,
	DEV_HOERATH,
	DEV_HEINLEIN,
	DEV_ZOEPHEL,
	DEV_MEIER,
	DEV_NAUMANN,
	DEV_KAPUSTA,
	DEV_CSCTEST,
	DEV_BARTH,
	DEV_ZDJELAR,
	DEV_JABLONSKY,
}

struct ConnectionInfo
{
	1: string Host,
	2: i32 Port,
}

const map<CountryEnum, ConnectionInfo> TestConnection = 
{
	Countries.COUNTRY_AUSTRIA : 				{ "Host": "zdev21", "Port": 56111 },
	Countries.COUNTRY_AUSTRIA_PREWHOLE :		{ "Host": "zdev21", "Port": 56191 },

	Countries.COUNTRY_BULGARIA :				{ "Host": "zdev21", "Port": 56161 },

	Countries.COUNTRY_CROATIA : 				{ "Host": "zdev21", "Port": 56201 },

	Countries.COUNTRY_GERMANY_NORTH :			{ "Host": "zdev21", "Port": 56001 },
	Countries.COUNTRY_GERMANY_SOUTH :			{ "Host": "zdev21", "Port": 56181 },

	Countries.COUNTRY_FRANCE :					{ "Host": "zdev21", "Port": 56121 },
	Countries.COUNTRY_FRANCE_PREWHOLE : 		{ "Host": "zdev21", "Port": 56131 },

	Countries.COUNTRY_SERBIA :					{ "Host": "zdev21", "Port": 56171 },

	Countries.COUNTRY_SWITZERLAND : 			{ "Host": "zdev21", "Port": 56101 },
	Countries.COUNTRY_SWITZERLAND_PREWHOLE :	{ "Host": "zdev21", "Port": 56141 },
}

const map<DeveloperEnum, ConnectionInfo> DeveloperConnection = 
{
	Developer.DEV_KESSLING		: { "Host": "zdev21", "Port": 56060 },
	Developer.DEV_EGERER		: { "Host": "zdev21", "Port": 56063 },
	Developer.DEV_BOUMA			: { "Host": "zdev21", "Port": 56066 },
	Developer.DEV_IMSCHWEILER	: { "Host": "zdev21", "Port": 56069 },
	Developer.DEV_HOERATH		: { "Host": "zdev21", "Port": 56072 },
	Developer.DEV_HEINLEIN		: { "Host": "zdev21", "Port": 56075 },
	Developer.DEV_ZOEPHEL		: { "Host": "zdev21", "Port": 56078 },
	Developer.DEV_MEIER			: { "Host": "zdev21", "Port": 56081 },
	Developer.DEV_NAUMANN		: { "Host": "zdev21", "Port": 56084 },
	Developer.DEV_KAPUSTA		: { "Host": "zdev21", "Port": 56087 },
	Developer.DEV_CSCTEST		: { "Host": "zdev21", "Port": 56090 },
	Developer.DEV_BARTH			: { "Host": "zdev21", "Port": 56093 },
	Developer.DEV_ZDJELAR		: { "Host": "zdev21", "Port": 56078 },
	Developer.DEV_JABLONSKY		: { "Host": "zdev21", "Port": 56096 },
}
