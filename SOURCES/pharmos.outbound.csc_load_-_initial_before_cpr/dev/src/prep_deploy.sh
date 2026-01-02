#!/usr/bin/ksh

set -e

CWD=$(pwd)

function copynewversion
{
	local readonly _SOURCE=${1};
	local readonly _TARGET=${2};
	echo "   copying ${_SOURCE} to ${_TARGET}";
	rm -rf ${_TARGET};
	cp -f ${_SOURCE} ${_TARGET};
	chmod 777 ${_TARGET};	
	touch ${_TARGET};
}



PRODSERVER="ode21 oat21 obg21 och21 ofr21 ohr21"

# contains(string, substring)
#
# Returns 0 if the specified string contains the specified substring,
# otherwise returns 1.
function contains
{
	string="$1"
	substring="$2"
	if test "${string#*$substring}" != "$string"
	then
		return 0    # $substring is in $string
	else
		return 1    # $substring is not in $string
	fi
}

function copy_binaries
{
	local readonly COUNTRY=$1

	LOAD_BIN_DIR=./tmp/$COUNTRY/ksc/load/bin/release
	mkdir -p ${LOAD_BIN_DIR}
	echo "Copy binaries: " $COUNTRY
	
	BINS=`ls act* del* load* reset* set* tpld*`

	for bin in $BINS; do
		copynewversion "./$bin"	"${LOAD_BIN_DIR}/$bin";
	done
}

function create_tarball_server
{
	local readonly _SERVER=$1

	COUNTRY=`echo $_SERVER | cut -c 2-3`
	if [[ $COUNTRY == "at" || $COUNTRY == "ch" || $COUNTRY == "fr" ]]; then
		PREWHOLE="p"$COUNTRY
	else
		PREWHOLE=
	fi

	echo "Server: " ${_SERVER}
	copy_binaries $COUNTRY
	if [[ $PREWHOLE"" != "" ]]; then
		copy_binaries $PREWHOLE
	fi
	
	
	TARBALL=csc_load_${_SERVER}.tar.gz
	if [[ ! -f ./${TARBALL} ]]; then
		echo "--- tar ${EXPORT_DIR}/${TARBALL} ..."
		cd ./tmp
		TARDIRS=`ls -d */`
		gtar -czf ../${TARBALL} ${TARDIRS}
		rm -rf ./${TARDIRS}
		cd ${CWD}
		echo "--- tarball contains:"
		gtar -tzf ${TARBALL} ${TARDIRS}
	fi
}

#determine_svnpath

if [[ $# > 0 ]]; then
	while [[ $# > 0 ]]; do
		SERVER=$1
		contains "$PRODSERVER" $SERVER || (echo "unknown server, supported are: " $PRODSERVER && return 0)
		create_tarball_server $SERVER
		shift;
	done
else
	for SERVER in $PRODSERVER; do
		echo "create_tarball_server $SERVER"
		create_tarball_server $SERVER
	done
fi

rmdir ./tmp
