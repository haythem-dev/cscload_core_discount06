#!/bin/sh

#########################################################################
#
#   install generated hdatum files to development directories:
#       - build
#
#########################################################################

# exit immediately if a command exits with non-zero exit status
set -e

# include version variable
. ./version.inc

PROJECT="kscclient"

BLDDIR="${DEVLIB_PATH}/marathon/orderentry/${PROJECT}/${KSCCLIENT_VERSION}"

echo "copy build files to $BLDDIR ..."
rm -rf $BLDDIR 2>/dev/null
mkdir -p $BLDDIR
cp -r ./include $BLDDIR
cp -r ./lib     $BLDDIR


echo "build files installed"

