#!/usr/bin/ksh

# tool functions for the developer tests

testHasPassed()
{
    printf "\n==> Test was successful.\n"
    testsPassed=$((testsPassed + 1))
}

testHasFailed()
{
    printf "\n==> Test was NOT successful!\n"
    testsFailed=$((testsFailed + 1))
}

doTestSummary()
{
    printf "\nTest Summary: %d tests in total, %d succeeded and %d failed.\n" \
	   $((testsPassed + testsFailed)) $testsPassed $testsFailed
}

goSql()
{
    cat t/go.sql | dbaccess ide21@zdev21_tcp > t/go.out 2>&1
    rowsRetrieved=$(fgrep retrieved t/go.out | cut -dr -f1)
}

cleanArticleQuota()
{
    printf "\n#####################\n# %s #\n#####################\n" cleanArticleQuota
    cat > t/go.sql <<SQL00
DELETE FROM ode21@zdev21_tcp:articlequota
WHERE branchno=$branchNo AND dateupdate=$now;
SQL00

    goSql
    fgrep deleted t/go.out
}

ageQuotaUpdateInfo()
{
    printf "\n######################\n# %s #\n######################\n" ageQuotaUpdateInfo
    cat > t/go.sql <<SQL00
UPDATE ode21@zdev21_tcp:articlequota
SET dateupdate=CAST(TO_CHAR(EXTEND(CURRENT - 1 UNITS DAY, YEAR TO DAY), '%Y%m%d') AS INTEGER)
WHERE branchno=$branchNo AND dateupdate=$now;
SQL00

    goSql
    fgrep updated t/go.out
}

#
# Note: the script uses order data from branch $branchNo
# to artificially create article quota test data
#
doSmallFullUpload()
{
    printf "\n#####################\n# %s #\n#####################\n" doSmallFullUpload
    rm -f loadnewquota.$now.log
    cat > t/go.sql <<SQL00
SELECT FIRST $smallAmount $branchNo||';'||oh.kundennr||';'||TRIM(ac.article_code)||';'|| op.mengebestellt+5 ||';M;'||
oh.datumorg||';'|| CAST(TO_CHAR(EXTEND(CURRENT + 10 UNITS DAY, YEAR TO DAY), '%Y%m%d') AS INTEGER)
FROM ode21@zdev21_tcp:kdauftrag oh,
ode21@zdev21_tcp:kdauftragpos op,
ode21@zdev21_tcp:articlecodes ac
WHERE ac.preferred_flag=1 AND
ac.articleno=op.artikel_nr AND
oh.filialnr=5 AND oh.datumorg>0 AND
oh.kdauftragnr=op.kdauftragnr;
SQL00

    goSql
    cat t/go.out | fgrep expression | cut "-d " -f2- |\
	sed -e "s# ##g" > t/upload.$smallAmount.br$branchNo.csv
    
    ./build/release/loadnewquota.bin --inputcsv 1 t/upload.$smallAmount.br$branchNo.csv --db ode21@zdev21_shm
    egrep '(records |with )' loadnewquota.$now.log
}

doBigDeltaUpload()
{
    printf "\n####################\n# %s #\n####################\n" doBigDeltaUpload
    rm -f loadnewquota.$now.log
    cat > t/go.sql <<SQL00
SELECT FIRST $bigAmount $branchNo||';'||oh.kundennr||';'||TRIM(ac.article_code)||';'|| op.mengebestellt+5 ||';M;'||
oh.datumorg||';'|| CAST(TO_CHAR(EXTEND(CURRENT + 10 UNITS DAY, YEAR TO DAY), '%Y%m%d') AS INTEGER)
FROM ode21@zdev21_tcp:kdauftrag oh,
ode21@zdev21_tcp:kdauftragpos op,
ode21@zdev21_tcp:articlecodes ac
WHERE ac.preferred_flag=1 AND
ac.articleno=op.artikel_nr AND
oh.filialnr=5 AND oh.datumorg>0 AND
oh.kdauftragnr=op.kdauftragnr;
SQL00

    goSql
    cat t/go.out | fgrep expression | cut "-d " -f2- |\
	sed -e "s# ##g" > t/upload.$bigAmount.br$branchNo.csv
    
    ./build/release/loadnewquota.bin --inputcsv 1 t/upload.$bigAmount.br$branchNo.csv --db ode21@zdev21_shm --nodelete
    egrep '(records |with )' loadnewquota.$now.log
}

showArticleQuota()
{
    cat > t/go.sql <<SQL00
SELECT FIRST $atMost ':'||branchno||' '||customerno||' '||articleno||' '||quota||' '||
kumqty||' '||validity||' '||dateupdate||' '||datefrom||' '||dateto
FROM ode21@zdev21_tcp:articlequota
WHERE branchno=$branchNo
ORDER BY dateupdate DESC, articleno, customerno;

SELECT 'rows:' || CAST(COUNT(*) AS INTEGER) AS gimmeall
FROM ode21@zdev21_tcp:articlequota
WHERE branchno=$branchNo AND dateupdate=$now;
SQL00

    goSql

    # patch the result to what we would have got without the display limitation
    rowsRetrieved=$(cat t/go.out | fgrep rows: | cut -d: -f2)
    
    printf "\nShowing at most %d entries from a total of %d entries ...\n" $atMost $rowsRetrieved
    printf "\n%2s %-7s %-7s %-3s %-6s %-3s  %-9s %-9s %-9s\n%s\n" \
	   br custom article qot kumqty vty update date-from date-to \
           ===============================================================
    cat t/go.out | fgrep expression | cut -d: -f2- |\
	while read bno cno ano quota kumqty valid udate fdate tdate; do
	    printf "%02d %7s %7s %3d %6s %3s %9s %9s %9s\n" \
		   $bno $cno $ano $quota $kumqty $valid $udate $fdate $tdate
	done
}
