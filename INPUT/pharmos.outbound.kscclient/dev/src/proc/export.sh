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

PROJECT=kscclient

SAVEDIR=`pwd`
BASEDIR=`CDPATH=. cd $SAVEDIR/../.. && pwd`
SRCDIR=$BASEDIR/dev/src
EXTDIR=$BASEDIR/dev/ext
DESTDIR=$BASEDIR/export/$PROJECT

echo "-----------------------------------------------------"
echo " copy $PROJECT files to export directory" 
echo "      from $SRCDIR"
echo "      to   $DESTDIR"
echo " compress export files to $DESTDIR/built.tar.gz"
echo "-----------------------------------------------------"

rm -rf $DESTDIR
mkdir -p $DESTDIR

echo "copy header files"
mkdir -p $DESTDIR/include/$PROJECT/
cp $EXTDIR/csc_core_applications/idl/kscserver/*.h	$DESTDIR/include/$PROJECT/
cp $SRCDIR/*.h			$DESTDIR/include/$PROJECT/

echo "copy library files"
mkdir -p $DESTDIR/lib
cp -r $SRCDIR/build/debug $DESTDIR/lib
cp -r $SRCDIR/build/release $DESTDIR/lib

cd $DESTDIR
echo "move files in archive ${PROJECT}.tar.gz"
tar -czf ./${PROJECT}.tar.gz include lib
rm -rf include/ lib/

cp $SRCDIR/ivy.xml $DESTDIR/
cp $SRCDIR/build.xml $DESTDIR/

cd $SAVEDIR

