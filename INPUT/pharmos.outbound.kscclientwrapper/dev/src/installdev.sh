#!/bin/sh

#########################################################################
#
#   install generated hdatum files to development directories:
#       - build
#
#########################################################################

# exit immediately if a command exits with non-zero exit status
#set -e
set -x

# include version variable
. ./version.inc

PROJECT="kscclientwrapper"

BLDDIR="$DEVLIB_PATH/marathon/orderentry/$PROJECT/$KSCCLIENTWRAPPER_VERSION"

echo "copy build files to $BLDDIR ..."
rm -rf $BLDDIR
mkdir -p $BLDDIR
mkdir -p $BLDDIR/include
mkdir -p $BLDDIR/lib
mkdir -p $BLDDIR/lib/debug
mkdir -p $BLDDIR/lib/release

cp -f ./include/* $BLDDIR/include
cp -r ./lib/debug/* $BLDDIR/lib/debug
cp -r ./lib/release/* $BLDDIR/lib/release


echo "build files installed"

