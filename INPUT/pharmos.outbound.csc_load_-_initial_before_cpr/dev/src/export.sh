#! /usr/bin/ksh

#set -x

PROJECT=csc_load

CWD=`pwd`

EXPORT_DIR=${CWD}/../../export/$PROJECT

rm -rf ${EXPORT_DIR}
mkdir -p ${EXPORT_DIR}

EXPORT_DIR=$(cd $EXPORT_DIR && pwd)

#aditional scripts
cp -r "${CWD}/_scripts/bin" "${EXPORT_DIR}"
#additionals sql scripts
cp -r "${CWD}/_scripts/data" "${EXPORT_DIR}"
#config and ini files
cp -r "${CWD}/_scripts/ini" "${EXPORT_DIR}"
#shell scripts and options for all countries
cp -r "${CWD}/_scripts/proc" "${EXPORT_DIR}"
#vars configruations
cp -r "${CWD}/_scripts/vars" "${EXPORT_DIR}"

BINSOURCE="release"

LOAD_DIRS=`ls -d act* del* load* longtermlack* reset* set* tpld*`

for dir in $LOAD_DIRS; do
	cp "${CWD}/$dir/build/${BINSOURCE}/$dir.bin"	"${EXPORT_DIR}/bin/$dir.bin";
done

cp prep_deploy.sh ${EXPORT_DIR}

cd $EXPORT_DIR

EXPORTS=$(ls bin/* data/* ini/* proc/* vars/*)

tar -czf $PROJECT.tar.gz $EXPORTS
rm -rf $EXPORTS

cd $CWD

cp build.xml $EXPORT_DIR
cp ivy.xml $EXPORT_DIR
