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
echo '- send output files started         -'
echo '-------------------------------------'
LocalDir="/software/wss/de/ksc/load/data/output"
RemoteDir="/software/wss/de/ksc/load/data/output"
Files="bestand-$BRANCHNO-*"
ftp -i -nv ode21 << EOF
user produser redR8-Wo3
lcd "$LocalDir"
cd "$RemoteDir"
mput "$Files"
bye
EOF
echo '-------------------------------------'
echo '- send output files done            -'
echo '-------------------------------------'

###################################################################
###################################################################
echo '-------------------------------------'
echo '- send input files started          -'
echo '-------------------------------------'
LocalDir="/software/wss/de/ksc/load/data/input"
RemoteDir="/software/wss/de/ksc/load/data/input"
FilesA="stocklevel-$BRANCHNO.*"
FilesB="stocklevel-$BRANCHNO-*"
ftp -i -nv ode21 << EOF
user produser redR8-Wo3
lcd "$LocalDir"
cd "$RemoteDir"
mput "$FilesA"
mput "$FilesB"
bye
EOF
echo '-------------------------------------'
echo '- send input files done             -'
echo '-------------------------------------'

###################################################################
###################################################################
echo '-------------------------------------'
echo '- move local output files started   -'
echo '-------------------------------------'
SOURCE="/software/wss/de/ksc/load/data/output/bestand-$BRANCHNO-*"
TARGET="/software/wss/de/ksc/load/data/output/old"
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

SOURCE="/software/wss/de/ksc/load/data/input/stocklevel-$BRANCHNO.*"
TARGET="/software/wss/de/ksc/load/data/input/old"
for FILE in `ls $SOURCE`; do
	echo $FILE
	mv $FILE $TARGET
done

SOURCE="/software/wss/de/ksc/load/data/input/stocklevel-$BRANCHNO-*"
TARGET="/software/wss/de/ksc/load/data/input/old"
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

