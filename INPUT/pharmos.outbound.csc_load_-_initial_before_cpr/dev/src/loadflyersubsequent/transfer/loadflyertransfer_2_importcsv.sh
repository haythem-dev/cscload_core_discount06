#! /usr/bin/ksh

echo "Loadflyer transfer process, this is step 2 of 4"

DATA_PATH=$WSS/de/ksc/load/data/flyer
REPORT_PATH=$WSS/de/ksc/load/data/flyer/report
ARCHIVE_PATH=$WSS/de/ksc/load/data/flyer/archive
PROC_PATH=$WSS/de/ksc/load/proc

cd $DATA_PATH

for file in $( ls -rtl *.csv | awk '{print $9}' )
do
	echo "import data file ${file}..."
	${PROC_PATH}/loadflyersubsequent.sh -start -inputcsv ${DATA_PATH}/${file}
        TIMESTAMP=$(date '+%Y%m%d_%H%M%S')
        FILENAMENOEXT="${file%.*}"
        mv "$file" "${ARCHIVE_PATH}/${FILENAMENOEXT}_${TIMESTAMP}.csv"
        echo "moved file ${file} and renamed to ${FILENAMENOEXT}_${TIMESTAMP}.csv"
done;

cd $REPORT_PATH

for file in $( ls -rtl *_report.csv | awk '{print $9}' )
do
        TIMESTAMP=$(date '+%Y%m%d_%H%M%S')
        FILENAMENOEXT="${file%.*}"
        mv "$file" "${FILENAMENOEXT}_${TIMESTAMP}.csv"
        echo "renamed file ${file} to ${FILENAMENOEXT}_${TIMESTAMP}.csv"
done;
