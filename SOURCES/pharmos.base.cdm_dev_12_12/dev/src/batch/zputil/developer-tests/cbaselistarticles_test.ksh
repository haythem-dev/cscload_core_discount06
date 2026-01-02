#!/usr/bin/ksh

HOWMANY=30
blids="OP"
blid="O"

mkdir -p t && rm -f t/*

show_and_clean_zpznpflege() {
    now=$(date +'%Y%m%d')
    printf "\n\n============================================\nChecking zpznpflege table from $now ...\n============================================\n"
    cat > t/go.sql << SQLF00
SELECT FIRST 20 * FROM ide21@zdev21_tcp:zpznpflege
WHERE dezap_sa='03' AND datum=$now
ORDER BY artikel_nr;

SELECT 'result: ' || CAST(COUNT(*) AS INTEGER)
FROM ide21@zdev21_tcp:zpznpflege
WHERE dezap_sa='03' AND datum=$now;
SQLF00
    cat t/go.sql | dbaccess ide21@zdev21_tcp > t/go.out 2>&1
    total=$(cat t/go.out | fgrep result: | cut -d: -f2)
    printf "... showing at most 20 records from a total of %d records\n\n" $total
    printf "artikel_nr   datum  dezap_sa\n----------------------------\n"
    cat t/go.out | fgrep $now | while read articleno datum dezapsa; do
	printf "%7d %10s %6s\n" $articleno $datum $dezapsa
    done

    if [ "$total" -eq 0 ]; then
	printf "\n==> Nothing to delete in zpznpflege.\n"
    else
	cat > t/go.sql << SQLF01
DELETE FROM ide21@zdev21_tcp:zpznpflege
WHERE dezap_sa='03' AND datum=$now;
SQLF01
	echo "Cleansing zpznpflege ..."
	cat t/go.sql | dbaccess ide21@zdev21_tcp > t/go.out 2>&1
	fgrep "deleted" t/go.out
    fi
} # show_and_clean_zpznpflege()

#
# Test case 1 (good): massupload to base list $blid
#
show_and_clean_zpznpflege

# Reserving some base list ids for the developer tests
# => make sure they do not clash with existing ones!!
cat > t/go.sql << SQL01
DELETE FROM ide21@zdev21_tcp:cbaselistarticles
WHERE baselist_id IN (
SELECT baselist_id
FROM ide21@zdev21_tcp:cbaselist
WHERE LOWER(baselist_name) LIKE 'developer test%'
);

DELETE FROM ide21@zdev21_tcp:cbaselist
WHERE LOWER(baselist_name) LIKE 'developer test%';

INSERT INTO ide21@zdev21_tcp:cbaselist
(baselist_id, baselist_name)
SELECT * 
FROM TABLE(LIST{
  ROW('O'::CHAR(1), 'DEVELOPER TEST 0'::CHAR(100)),
  ROW('P'::CHAR(1), 'DEVELOPER TEST 1'::CHAR(100))
}) T(baselist_id, baselist_name);

SELECT "id: [" || baselist_id || "], name: [" || TRIM(baselist_name) || "]" AS result
FROM ide21@zdev21_tcp:cbaselist
WHERE LOWER(baselist_name) LIKE 'developer test%';
SQL01

echo "Creating new article base list instances ..."
cat t/go.sql | dbaccess ide21@zdev21_tcp > t/go.out 2>&1
fgrep "name:" t/go.out

cat > t/go.sql << SQL02
SELECT FIRST $HOWMANY "result:" || z.artikel_nr AS result
FROM ide21@zdev21_tcp:zartikel z, ide21@zdev21_tcp:carticlecodes c
WHERE z.artikel_nr=c.articleno
AND c.preferred_flag = 1
AND z.artikel_nr > 10000;
SQL02

echo "Test Case 1 [GOOD]: creating upload with $HOWMANY proper articles in it ..."
cat t/go.sql | dbaccess ide21@zdev21_tcp > t/go.out 2>&1

i=$HOWMANY

printf "ARTIKEL_NR|BASELIST_ID|\nNEG_VALUES||\n" > t/massupload.csv
fgrep "result:" t/go.out | cut -d: -f2 | while read articleno; do
    i=$((i - 1))
    printf "[%04d] " $i
    echo "Preparing mass upload for article no. [$articleno] with an assignment to base list ID [$blid]."
    echo "$articleno|$blid|" >> t/massupload.csv
done
mv t/massupload.csv t/massupload_good_$HOWMANY.csv

printf "\n\nLaunching the mass upload ...\n"
$PWD/build/debug/zputil 24 t/massupload_good_$HOWMANY.csv ide21 0

#
# Test case 2 (bad): upload with wrong baselist ID 'N'
#
show_and_clean_zpznpflege

head -2  t/massupload_good_$HOWMANY.csv > t/massupload.csv
head -3  t/massupload_good_$HOWMANY.csv | tail -1 | sed -e 's#..$#qq&#' -e 's#qq.#N#' >> t/massupload.csv
fgrep \|$blid t/massupload_good_$HOWMANY.csv >> t/massupload.csv
mv t/massupload.csv t/massupload_bad_id_$HOWMANY.csv

printf "\n\nTest Case 2 [BAD]: Launching the mass upload with an invalid baselist ID ...\n"
$PWD/build/debug/zputil 24 t/massupload_bad_id_$HOWMANY.csv ide21 0

show_and_clean_zpznpflege

#
# Test case 3 (bad): upload with invalid article codes
#

cat > t/go.sql << SQL03
SELECT FIRST $HOWMANY "result:" || hnr_vse AS result
FROM ide21@zdev21_tcp:kddispo
WHERE hnr_vse > 1000 AND hnr_vse NOT IN (
SELECT CAST(article_code AS INTEGER)
FROM ide21@zdev21_tcp:carticlecodes ca
WHERE preferred_flag=1
);
SQL03

echo "Test Case 3 [BAD]: creating upload with $HOWMANY improper articles in it ..."
cat t/go.sql | dbaccess ide21@zdev21_tcp > t/go.out 2>&1

i=$HOWMANY

printf "ARTIKEL_NR|BASELIST_ID|\nNEG_VALUES||\n" > t/massupload.csv
fgrep "result:" t/go.out | cut -d: -f2 | while read articleno; do
    i=$((i - 1))
    printf "[%04d] " $i
    echo "Preparing mass upload for article no. [-$articleno] with an assignment to base list ID [$blid]."
    printf "-%d|%c|\n" $articleno $blid >> t/massupload.csv
done
mv t/massupload.csv t/massupload_bad_$HOWMANY.csv
echo "Trying mass upload ..."
$PWD/build/debug/zputil 24 t/massupload_bad_$HOWMANY.csv ide21 0

show_and_clean_zpznpflege

echo "Test Case 4 [BAD]: creating upload with $HOWMANY improper articles or IDs in it ..."
cat t/massupload_bad_$HOWMANY.csv | sed -e "/[0-9]\{5\}/s#$blid#J#" > t/massupload_very_bad_$HOWMANY.csv
echo "Trying mass upload ..."
$PWD/build/debug/zputil 24 t/massupload_very_bad_$HOWMANY.csv ide21 0


#
# Test case 5 (GOOD): mass upload with a feww duplicate entries
#
printf "\n\nTest Case 5 [GOOD]: Launching mass upload with a few duplicate entries ...\n"

show_and_clean_zpznpflege

cat t/massupload_good_$HOWMANY.csv > t/massupload_good_dups_$HOWMANY.csv
fgrep "$blid|" t/massupload_good_$HOWMANY.csv | head -10 >> t/massupload_good_dups_$HOWMANY.csv
$PWD/build/debug/zputil 24 t/massupload_good_dups_$HOWMANY.csv ide21 0

show_and_clean_zpznpflege
