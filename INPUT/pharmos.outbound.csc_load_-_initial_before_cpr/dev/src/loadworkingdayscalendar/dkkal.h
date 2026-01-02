#define L_DKKAL_FIL				2

#define L_DKKAL_DATUM_JAHR		4
#define L_DKKAL_DATUM_MONAT		2
#define L_DKKAL_DATUM_TAG		2

#define L_DKKAL_LFD				3 // lfdnr. Tag im  Jahr
#define L_DKKAL_KW				2 // Kalenderwoche

#define L_DKKAL_TAGESNAME		2

#define L_DKKAL_MOZAHL			2 // lfdnr. Arbeitstag pro Monat ohne Samstag
#define L_DKKAL_JOZAHL			3 // lfdnr. Arbeitstag pro Jahr ohne Samstag
#define L_DKKAL_KOZAHL			1 // lfdnr. Arbeitstag pro Woche ohne Samstag

#define L_DKKAL_AF				1 // Arbeitstag/Feiertag (A/F)

#define L_DKKAL_MOZTA			2 // lfdnr. Arbeitstag pro Monat mit Samstag
#define L_DKKAL_JOZTA			3 // lfdnr. Arbeitstag pro Jahr mit Samstag
#define L_DKKAL_KOZTA			1 // lfdnr. Arbeitstag pro Woche mit Samstag

#define L_DKKAL_MONATSABSCHLUSS 1 // Monatsabschluss (J/N)


#define WORKINGDAYSCALENDAR_LIST \
        WORKINGDAYSCALENDAR.BRANCHNO,\
        WORKINGDAYSCALENDAR.CALENDARDATE,\
        WORKINGDAYSCALENDAR.DAYOFYEAR,\
        WORKINGDAYSCALENDAR.WEEKOFYEAR,\
        WORKINGDAYSCALENDAR.WORKINGDAYOFMONTH,\
        WORKINGDAYSCALENDAR.WORKINGDAYOFYEAR,\
        WORKINGDAYSCALENDAR.WORKINGDAYOFWEEK,\
        WORKINGDAYSCALENDAR.DAYTYPE

#define WORKINGDAYSCALENDAR_UPDLISTE \
        "BRANCHNO=?,"\
        "CALENDARDATE=?,"\
        "DAYOFYEAR=?,"\
        "WEEKOFYEAR=?,"\
        "WORKINGDAYOFMONTH=?,"\
        "WORKINGDAYOFYEAR=?,"\
        "WORKINGDAYOFWEEK=?,"\
        "DAYTYPE=?"

EXEC SQL BEGIN DECLARE SECTION;

struct O_DKKAL
{
	char FIL				[L_DKKAL_FIL];

	char DATUMJAHR			[L_DKKAL_DATUM_JAHR];
	char DATUMMONAT			[L_DKKAL_DATUM_MONAT];
	char DATUMTAG			[L_DKKAL_DATUM_TAG];

	char LFD				[L_DKKAL_LFD];
	char KW					[L_DKKAL_KW];

	char TAGESNAME			[L_DKKAL_TAGESNAME];

	char MOZAHL				[L_DKKAL_MOZAHL];
	char JOZAHL				[L_DKKAL_JOZAHL];
	char KOZAHL				[L_DKKAL_KOZAHL];

	char AF					[L_DKKAL_AF];

	char MOZTA				[L_DKKAL_MOZTA];
	char JOZTA				[L_DKKAL_JOZTA];
	char KOZTA				[L_DKKAL_KOZTA];

	char MONATSABSCHLUSS	[L_DKKAL_MONATSABSCHLUSS];
};

EXEC SQL END DECLARE SECTION;
