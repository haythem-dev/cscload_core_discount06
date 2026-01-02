#!/bin/sh

#########################################################################
#
# copy project files to export directory (tar.gz)
#   - header files
#   - libraries	
#   - shell scripts for installation
#
#########################################################################

# exit immediately if a command exits with non-zero exit status
set -e

PROJECT=kscclientwrapper

SAVEDIR=`pwd`
BASEDIR=`CDPATH=. cd $SAVEDIR/../.. && pwd`
SRCDIR=$BASEDIR/dev/src
DESTDIR=$BASEDIR/export/$PROJECT

VERSION=`grep -w "KSCCLIENTWRAPPER_VERSION" $SRCDIR/version.h | cut -f3 -d' '`

echo "-----------------------------------------------------"
echo " copy $PROJECT files to export directory" 
echo "      from $SRCDIR"
echo "      to   $DESTDIR"
echo " compress export files to $DESTDIR/built.tar.gz"
echo "-----------------------------------------------------"

rm -rf $DESTDIR
mkdir -p $DESTDIR

echo "copy header files"
mkdir -p $DESTDIR/include
cp $SRCDIR/*.h     $DESTDIR/include/

echo "copy library files"
mkdir -p $DESTDIR/lib
cp -r $SRCDIR/build/debug $DESTDIR/lib
cp -r $SRCDIR/build/release $DESTDIR/lib

echo "create version file"
echo "KSCCLIENTWRAPPER_VERSION=$VERSION" > $SRCDIR/version.inc

echo "copy script files"
cp $SRCDIR/install*.sh $DESTDIR/
cp $SRCDIR/version.inc $DESTDIR/

cd $DESTDIR
echo "move files in archive $PROJECT.tar.gz"
gtar -czf ./$PROJECT.tar.gz include lib ./*.sh ./*.inc
rm -rf include/ lib/ ./*.sh ./*.inc

cp $SRCDIR/build.xml $DESTDIR
cp $SRCDIR/ivy.xml $DESTDIR

cd $SAVEDIR

