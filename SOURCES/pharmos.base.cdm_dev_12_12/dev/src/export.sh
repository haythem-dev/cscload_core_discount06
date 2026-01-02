#!/bin/sh

#########################################################################
#
# copy project files to export directory (tar.gz)
#   - header files
#
#########################################################################

# exit immediately if a command exits with non-zero exit status
set -e

PROJECT=cdm

SAVEDIR=`pwd`
BASEDIR=`CDPATH=. cd $SAVEDIR/../.. && pwd`
SRCDIR=$BASEDIR/dev/src
DESTDIR=$BASEDIR/export/$PROJECT

echo "-----------------------------------------------------"
echo " copy $PROJECT files to export directory" 
echo "      from $SRCDIR"
echo "      to   $DESTDIR"
echo " compress export files to $DESTDIR/built.tar.gz"
echo "-----------------------------------------------------"

rm -rf $DESTDIR
mkdir -p $DESTDIR/bin
mkdir -p $DESTDIR/ini
mkdir -p $DESTDIR/proc
mkdir -p $DESTDIR/vars

# TODO: loadcontractshr is used in HR since 2021, but not yet added to export.sh (KT - 09.08.2024)

echo "copy binaries"
cp -r $SRCDIR/batch/zpexpensv/build/release/* $DESTDIR/bin/
cp -r $SRCDIR/batch/zpexpensv/unix/proc/* $DESTDIR/proc/
cp -r $SRCDIR/batch/zpexpensv/unix/vars/* $DESTDIR/vars/
cp -r $SRCDIR/batch/importocp/build/release/* $DESTDIR/bin/
cp -r $SRCDIR/batch/importocp/unix/proc/* $DESTDIR/proc/
cp -r $SRCDIR/batch/importocp/unix/vars/* $DESTDIR/vars/
cp -r $SRCDIR/batch/importmedreg/build/release/* $DESTDIR/bin/
cp -r $SRCDIR/batch/importmedreg/unix/ini/* $DESTDIR/ini/
cp -r $SRCDIR/batch/importmedreg/unix/proc/* $DESTDIR/proc/
cp -r $SRCDIR/batch/importmedreg/unix/vars/* $DESTDIR/vars/
cp -r $SRCDIR/batch/subsequentdeliveryrelevantcalculator/subsequentdeliveryrelevantcalculator/build/release/* $DESTDIR/bin/
cp -r $SRCDIR/batch/subsequentdeliveryrelevantcalculator/subsequentdeliveryrelevantcalculator/unix/subsequentdeliveryrelevantcalculator.sh $DESTDIR/proc/
cp -r $SRCDIR/batch/subsequentdeliveryrelevantcalculator/subsequentdeliveryrelevantcalculator/unix/subsequentdeliveryrelevantcalculator.option $DESTDIR/proc/
cp -r $SRCDIR/batch/subsequentdeliveryrelevantcalculator/subsequentdeliveryrelevantcalculator/unix/subsequentdeliveryrelevantcalculator.cfg $DESTDIR/ini/
cp -r $SRCDIR/batch/importpricelist/importpricelist/build/release/* $DESTDIR/bin/
cp -r $SRCDIR/batch/importpricelist/importpricelist/unix/importpricelist.sh $DESTDIR/proc/
cp -r $SRCDIR/batch/importpricelist/importpricelist/unix/importpricelist.option $DESTDIR/proc/
cp -r $SRCDIR/batch/importpricelist/importpricelist/unix/importpricelist.cfg $DESTDIR/ini/
cp -r $SRCDIR/batch/importarticlegenerator/build/release/* $DESTDIR/bin/
cp -r $SRCDIR/batch/zpiartik/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpignart/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpagpgnart/build/release/*     	    $DESTDIR/bin/
cp -r $SRCDIR/batch/zpagpgnart/unix/zpagpgnart.sh           $DESTDIR/proc/
cp -r $SRCDIR/batch/zpagpgnart/unix/zpagpgnart.option       $DESTDIR/proc/
cp -r $SRCDIR/batch/zpagpgnart/unix/zpagpgnart.vars         $DESTDIR/vars/
cp -r $SRCDIR/batch/zpagpgnart/unix/zpagpgnart_clean.sh     $DESTDIR/proc/
cp -r $SRCDIR/batch/zpagpgnart/unix/zpagpgnart_clean.option $DESTDIR/proc/
cp -r $SRCDIR/batch/zpagpgnart/unix/zpagpgnart_clean.vars   $DESTDIR/vars/
cp -r $SRCDIR/batch/zpadglf/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/srvzdpdruck/build/release/*     $DESTDIR/bin/
cp -r $SRCDIR/batch/zpadgreimp/build/release/*      $DESTDIR/bin/
cp -r $SRCDIR/batch/zpautidm/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpcalcprice/build/release/*     $DESTDIR/bin/
cp -r $SRCDIR/batch/zpcalcrg/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpcronpf/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpdailyclosing/build/release/*  $DESTDIR/bin/
cp -r $SRCDIR/batch/zpdatacarelf/build/release/*    $DESTDIR/bin/
cp -r $SRCDIR/batch/zpdcartik/build/release/*       $DESTDIR/bin/
cp -r $SRCDIR/batch/zpdcgnart/build/release/*       $DESTDIR/bin/
cp -r $SRCDIR/batch/zpdefpa/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpdrupro/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpifalf/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpifestb/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpiherst/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpimswgr/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpisichg/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zplfzart/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpliartik/build/release/*       $DESTDIR/bin/
cp -r $SRCDIR/batch/zplieums/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zplignart/build/release/*       $DESTDIR/bin/
cp -r $SRCDIR/batch/zplilf/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpmasaen/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpprotok/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zppwartik/build/release/*       $DESTDIR/bin/
cp -r $SRCDIR/batch/zpumldir/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zputil/build/release/*       	$DESTDIR/bin/
cp -r $SRCDIR/batch/zpconsig/build/release/*       	$DESTDIR/bin/

cp -r $SRCDIR/tpulzp/tpulzpfrance/build/release/*   $DESTDIR/bin/
cp -r $SRCDIR/tpulzp/tpulzentpfl/build/release/*   	$DESTDIR/bin/
cp -r $SRCDIR/tpulzp/tpulzpbulgaria/build/release/* $DESTDIR/bin/

cp -r $SRCDIR/batch/mainwarehousearticlesrelevantcalculator/build/release/*       									$DESTDIR/bin/
cp -r $SRCDIR/batch/mainwarehousearticlesrelevantcalculator/mainwarehousearticlesrelevantcalculator/unix/*       	$DESTDIR/proc/
cp -r $SRCDIR/batch/mainwarehousearticlesrelevantcalculator/mainwarehousearticlesrelevantcalculator/*.cfg		    $DESTDIR/ini/

cp -r $SRCDIR/batch/ibtrelevantcalculator/ibtrelevantcalculator/build/release/* $DESTDIR/bin/
cp -r $SRCDIR/batch/ibtrelevantcalculator/ibtrelevantcalculator/unix/*       	$DESTDIR/proc/
cp -r $SRCDIR/batch/ibtrelevantcalculator/ibtrelevantcalculator/*.cfg		    $DESTDIR/ini/

cp -r $SRCDIR/batch/fmdrelevantcalculator/fmdrelevantcalculator/build/release/* $DESTDIR/bin/
cp -r $SRCDIR/batch/fmdrelevantcalculator/fmdrelevantcalculator/unix/*       	$DESTDIR/proc/
cp -r $SRCDIR/batch/fmdrelevantcalculator/fmdrelevantcalculator/*.cfg		    $DESTDIR/ini/

cp -r $SRCDIR/batch/exportarticlecalculator/exportarticlecalculator/build/release/* $DESTDIR/bin/
cp -r $SRCDIR/batch/exportarticlecalculator/exportarticlecalculator/unix/*       	$DESTDIR/proc/
cp -r $SRCDIR/batch/exportarticlecalculator/exportarticlecalculator/*.cfg		    $DESTDIR/ini/

cp -r $SRCDIR/batch/zpldcust/zpldcust/release/zpldcust  $DESTDIR/bin/
cp -r $SRCDIR/batch/zpldcust/zpldcust/zpldcust.sh       $DESTDIR/proc/
cp -r $SRCDIR/batch/zpldcust/zpldcust/zpldcust.option   $DESTDIR/proc/
cp -r $SRCDIR/batch/zpldcust/zpldcust/zpldcust.cfg	    $DESTDIR/ini/

cp -r $SRCDIR/batch/exportproductdataforpharmacyportals/*.sh $DESTDIR/proc/
cp -r $SRCDIR/batch/exportproductdataforpharmacyportals/*.option $DESTDIR/proc/

cd $DESTDIR
echo "move unix files in archive built.tar.gz"
TARDIRS=`ls -d *`
tar --remove-files -czf ./$PROJECT.tar.gz $TARDIRS
rm -rf $TARDIRS

cp $SRCDIR/build.xml $DESTDIR
cp $SRCDIR/ivy.xml   $DESTDIR

cd $SAVEDIR

