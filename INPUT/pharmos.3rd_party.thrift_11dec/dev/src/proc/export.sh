#!/usr/bin/bash -e

project=thrift
src_dir=$(pwd)
export_dir=$(pwd)/../../export/${project}

echo "exporting ${project} to ${export_dir}..." >&2

if [ ! -d ${src_dir}/pkg-install ] ; then
	echo "error: ${project} has not been built." >&2
	exit 1
fi

rm -rf ${src_dir}/pkg-export
cp -r ${src_dir}/pkg-install/ ${src_dir}/pkg-export/

pushd ${src_dir}/pkg-export >/dev/null

# move out static libraries, and symlink shared ones to use with aix
mkdir -p libstatic
mv lib/*.a libstatic

popd >/dev/null

mkdir -p ${export_dir}
tar -C ${src_dir}/pkg-export -cvzf ${export_dir}/${project}.tar.gz .

cp ${src_dir}/ivy.xml ${export_dir}
cp ${src_dir}/build.xml ${export_dir}

echo "done" >&2
echo "" >&2
