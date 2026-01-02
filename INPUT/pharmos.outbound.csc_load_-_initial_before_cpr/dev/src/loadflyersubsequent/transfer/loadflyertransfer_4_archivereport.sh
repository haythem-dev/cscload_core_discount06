#! /usr/bin/ksh

echo "echo Loadflyer transfer process, this is step 4 of 4"

DATA_PATH=$WSS/de/ksc/load/data/flyer
REPORT_PATH=$WSS/de/ksc/load/data/flyer/report
ARCHIVE_PATH=$WSS/de/ksc/load/data/flyer/archive
PROC_PATH=$WSS/de/ksc/load/proc

cd $REPORT_PATH

for file in $( ls -rtl *.csv | awk '{print $9}' )
do
        mv "$file" "${ARCHIVE_PATH}/$file"
        echo "moved file ${file} to archive"
done;
