#pragma once

#ifndef SUBARTDAN_INCLUDED
#define SUBARTDAN_INCLUDED

struct SUBARTDAN {
	long	PHAR;
	short	PICTOGRAM01_FLAG;
	short	PICTOGRAM02_FLAG;
	short	PICTOGRAM03_FLAG;
	short	PICTOGRAM04_FLAG;
	short	PICTOGRAM05_FLAG;
	short	PICTOGRAM06_FLAG;
	short	PICTOGRAM07_FLAG;
	short	PICTOGRAM08_FLAG;
	short	PICTOGRAM09_FLAG;
	char	GS_EXPLOSION     [2];
	char	GS_HOCHENTZ      [2];
	char	GS_LEICHTENTZ    [2];
	char	GS_BRAND         [2];
	char	GS_AETZEND       [2];
	char	GS_SEHRGIFTIG    [2];
	char	GS_GIFTIG        [2];
	char	GS_GESUNDHSCH    [2];
	char	GS_REIZEND       [2];
	char	GS_UMWELT        [2];
//	long	SDS_DATE_DE      ;
};

#endif /* SUBARTDAN_INCLUDED */
