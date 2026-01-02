#!/bin/sh

#########################################################################
#
#   archive generated thrift files for deployment
#       - build
#       - runtime
#
#########################################################################

# exit immediately if a command exits with non-zero exit status
set -e

# include version variable
. ./version.inc


echo "create archive ../${PROJECT}-${THRIFT_VERSION}.tar.gz ..."
cd ..
mkdir -p ./tmp/${PROJECT}/${THRIFT_VERSION}/sharedlib

cp -r -P lib/ ./tmp/${PROJECT}/${THRIFT_VERSION}/sharedlib/
mv -f ./tmp/${PROJECT}/${THRIFT_VERSION}/sharedlib/lib \
	  ./tmp/${PROJECT}/${THRIFT_VERSION}/sharedlib/release
chmod -R ug=rwx,o=rx ./tmp/${PROJECT}/${THRIFT_VERSION}/sharedlib/release	    

tar -cz -C ./tmp -f ./${PROJECT}-${THRIFT_VERSION}.tar.gz .
rm -rf ./tmp


echo "runtime files archived"
