 #! /usr/bin/ksh
 # set -x
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:			f.nauman
 #Creation-Date:	21.11.2015
 #Purpose:			checks wrong reservations in all PROD databases (until the day before)
 ###############################################################################################

 ###############################################################################################
 # VARIABLES
 ###############################################################################################
 
DATABASES="
	oat21@oat21_tcp
	oat21pre@oat21_tcp
	och21@och21_tcp
	och21pre@och21_tcp
	ode21@ode21_tcp
	ode22@ode22_tcp
	ofr21@ofr21_tcp
	ofr21pre@ofr21_tcp
	ohr21@ohr21_tcp
	ors21@ors21_tcp";

DATABASE_BG="obg21@obg21_tcp";

RESULTFILE="/tmp/stockbooking_test.txt";
TESTFILE="/tmp/stockbooking_part.txt";
 
#---------------------------------------------------------------------------------------------
# Selects in database and writes result to $RESULTFILE if 1 or more rows found.
# Parameter 1: database
# Parameter 2: SQL string to execute 
#---------------------------------------------------------------------------------------------
function doSelect
{
	DB=$1;
	SQL="$2";

	echo "------------------------"	>  $TESTFILE 2>&1;
	echo ${DB}						>> $TESTFILE 2>&1;
	echo ${SQL} | dbaccess ${DB}	>> $TESTFILE 2>&1;

	if [[ `grep 'row(s) retrieved' $TESTFILE` != "" ]]; then
		cat $TESTFILE | grep -v "Database" | grep -v "Isolation" >> $RESULTFILE;
	fi;
	
	rm -rf $TESTFILE;
}

#---------------------------------------------------------------------------------------------
# Checks for wrong reservations
# Parameter 1: database
#---------------------------------------------------------------------------------------------
function selectWrongReservations
{
	DB=$1
#---------------------------------------------------------------------------------------------
#-- selektiere fehlerhafte Auftragsreservierungen type 11, 12
#		AND k.kdauftragstat[9] != '1'    -- Fakturiert
#		AND k.kdauftragstat[10] != '1'   -- Storniert
#---------------------------------------------------------------------------------------------

	SQL="SET ISOLATION DIRTY READ;
		SELECT r.branchno, r.articleno, r.customerno, r.datefrom, r.timefrom, r.reservtype
		FROM cststockreserved r
		WHERE reservtype IN (11, 12)
			AND r.datefrom < CAST(TO_CHAR(CURRENT, '%4Y%2m%2d') AS INTEGER)
			AND NOT EXISTS (
				SELECT k.kdauftragnr
				FROM kdauftrag k, kdauftragpos p
				WHERE k.filialnr = r.branchno
					AND k.kdauftragnr = r.kdauftragnr
					AND k.kdauftragstat[9] != '1'
					AND k.kdauftragstat[10] != '1'
					AND k.kdauftragnr = p.kdauftragnr
					AND p.artikel_nr = r.articleno
			)
		ORDER BY r.datefrom";

	doSelect $DB "${SQL}";

#---------------------------------------------------------------------------------------------
#-- selektiere fehlerhafte Verbundreservierungen type 9, 10
#	WHERE k.vbstatus != '5'            -- Fakturiert
#		AND k.vbstatus != '4'          -- Storniert
#		AND p.processingstatus != '2'  -- Verarbeitet
#---------------------------------------------------------------------------------------------

	SQL="SET ISOLATION DIRTY READ;
		SELECT r.branchno, r.articleno, r.customerno, r.datefrom, r.timefrom, r.reservtype
		FROM cststockreserved r
		WHERE reservtype IN (9, 10)
			AND branchno != 27
			AND r.datefrom < CAST(TO_CHAR(CURRENT, '%4Y%2m%2d') AS INTEGER)
			AND NOT EXISTS (
				SELECT k.kdauftragnr
				FROM kdverbund k,kdverbundpos p, paraauftragbearb a
				WHERE k.vbstatus != '5'
					AND k.vbstatus != '4'
					AND p.processingstatus != '2'
					AND k.kdauftragnr = p.kdauftragnr AND k.filialnr = p.filialnr
					AND k.herkunftfiliale=a.filialnr
					AND k.filialnr = r.branchno AND p.artikel_nr = r.articleno
			)
		ORDER BY r.datefrom"

	doSelect $DB "$SQL";

#---------------------------------------------------------------------------------------------
#-- selektiere fehlerhafte Nachlieferreservierungen type 7, 8
#---------------------------------------------------------------------------------------------
	SQL="SET ISOLATION DIRTY READ;
		SELECT r.branchno, r.articleno, r.customerno, r.datefrom, r.timefrom, r.reservtype
		FROM cststockreserved r
		WHERE reservtype IN (7, 8)
			AND r.datefrom < CAST(TO_CHAR(CURRENT, '%4Y%2m%2d') AS INTEGER)
			AND NOT EXISTS (
				SELECT vertriebszentrumnr, idfnr, artikel_nr
				FROM nachlieferpos p
				WHERE postyp = 5
					AND r.branchno=p.vertriebszentrumnr
					AND r.articleno=p.artikel_nr 
			)
		ORDER BY r.datefrom";

	doSelect $DB "$SQL";
}

#---------------------------------------------------------------------------------------------
# Switches environment to access bulgarian database
#---------------------------------------------------------------------------------------------
function switchLocaleToBulgaria
{
	CLIENT_LOCALE=bg_bg.8859-5
	DB_LOCALE=bg_bg.8859-5
	DBMONEY=.
	DBDATE=MDY4/
	export CLIENT_LOCALE DB_LOCALE DBMONEY DBDATE
}

#---------------------------------------------------------------------------------------------
# main script starts here
#---------------------------------------------------------------------------------------------

rm -rf $RESULTFILE;

for database in $DATABASES; do
	selectWrongReservations $database;
done;

switchLocaleToBulgaria;
selectWrongReservations $DATABASE_BG;


if [[ -e $RESULTFILE ]]; then
	winmail -e "f.naumann@phoenixgroup.eu;a.egerer@phoenixgroup.eu" -b "Reservierungsfehler" -t $RESULTFILE -no -nocc -dos;
fi;

rm -rf $RESULTFILE;
