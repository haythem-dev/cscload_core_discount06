#! /usr/bin/ksh

BRANCHNO=$1
if [ "$BRANCHNO" = "" ]
then
	echo "Es muss eine Filialnummer als Script-Parameter angegeben werden!"
	exit 99;
fi

echo '==========================================================='
echo 'Script started'
echo '==========================================================='

###################################################################
###################################################################
echo '-------------------------------------'
echo '- delete output files started       -'
echo '-------------------------------------'
LocalDir="/software/wss/de/ksc/load/data/output"
RemoteDir="/software/wss/de/ksc/load/data/output"
Files="bestand-$BRANCHNO-*"
ftp -i -nv ode21 << EOF
user produser redR8-Wo3
lcd "$LocalDir"
cd "$RemoteDir"
mdel "$Files"
bye
EOF
echo '-------------------------------------'
echo '- delete output files done          -'
echo '-------------------------------------'

###################################################################
###################################################################
echo '-------------------------------------'
echo '- delete input files started        -'
echo '-------------------------------------'
LocalDir="/software/wss/de/ksc/load/data/input"
RemoteDir="/software/wss/de/ksc/load/data/input"
FilesA="stocklevel-$BRANCHNO.*"
FilesB="stocklevel-$BRANCHNO-*"
ftp -i -nv ode21 << EOF
user produser redR8-Wo3
lcd "$LocalDir"
cd "$RemoteDir"
mdel "$FilesA"
mdel "$FilesB"
bye
EOF
echo '-------------------------------------'
echo '- delete input files done           -'
echo '-------------------------------------'

###################################################################
###################################################################
echo '-------------------------------------'
echo '- move local output files started   -'
echo '-------------------------------------'
SOURCE="/software/wss/de/ksc/load/data/output/old/bestand-$BRANCHNO-*"
TARGET="/software/wss/de/ksc/load/data/output"
for FILE in `ls $SOURCE`; do
	echo $FILE
	mv $FILE $TARGET
done
echo '-------------------------------------'
echo '- move local output files done      -'
echo '-------------------------------------'

###################################################################
###################################################################
echo '-------------------------------------'
echo '- move local input files started    -'
echo '-------------------------------------'

SOURCE="/software/wss/de/ksc/load/data/input/old/stocklevel-$BRANCHNO.*"
TARGET="/software/wss/de/ksc/load/data/input"
for FILE in `ls $SOURCE`; do
	echo $FILE
	mv $FILE $TARGET
done

SOURCE="/software/wss/de/ksc/load/data/input/old/stocklevel-$BRANCHNO-*"
TARGET="/software/wss/de/ksc/load/data/input"
for FILE in `ls $SOURCE`; do
	echo $FILE
	mv $FILE $TARGET
done

echo '-------------------------------------'
echo '- move local input files done       -'
echo '-------------------------------------'

echo '==========================================================='
echo 'Script finished'
echo '==========================================================='
