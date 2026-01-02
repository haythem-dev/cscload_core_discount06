#!/usr/bin/ksh

typeset branchNo=8
typeset smallAmount=10
typeset bigAmount=1000
typeset atMost=20
typeset rowsRetrieved=0
typeset testsFailed=0
typeset testsPassed=0
typeset now=$(date +'%Y%m%d')

. $(dirname "$0")/devtest-fun.ksh

mkdir -p t && rm -rf t/*

# remove all quota entries for the current branch
cleanArticleQuota
showArticleQuota

# create and launch a big upload
# -> because of the "clean" this should cause
# a lot of inserts for the new entries
doBigDeltaUpload
showArticleQuota

# there might be updates, but heuristically less than 10%
# printf "Got %d fresh from %d totally.\n" $rowsRetrieved $bigAmount

if [ $rowsRetrieved -gt $((bigAmount * 4 / 5)) ] ; then
    testHasPassed
else
    testHasFailed
fi

# move the update date for the existing entries
# one day into the past, so full upload should
# delete them
ageQuotaUpdateInfo
showArticleQuota

# create a small full upload
# -> all entries from before should be
#    discarded, and we should see inserts only
doSmallFullUpload
showArticleQuota
if [ $rowsRetrieved -eq $smallAmount ] ; then
    testHasPassed
else
    testHasFailed
fi

# repeat big delta upload
# -> we should now see inserts & updates
doBigDeltaUpload
showArticleQuota

# printf "Got %d fresh from %d totally.\n" $rowsRetrieved $bigAmount
if [ $rowsRetrieved -gt $((bigAmount * 4 / 5)) -a $rowsRetrieved -gt $smallAmount ] ; then
    testHasPassed
else
    testHasFailed
fi

doTestSummary
