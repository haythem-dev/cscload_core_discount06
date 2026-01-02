#!/usr/bin/bash -e

top_dir=$(pwd)
dev_dir=${top_dir}/..
src_pattern=thrift*

echo "extracting ${src_pattern} sources to ${dev_dir}/src..." >&2

tar -C ${dev_dir}/src -zxf ${dev_dir}/ext/thrift_source/${src_pattern}.tar.gz 

echo "done" >&2
echo "" >&2

src_dir=${top_dir}/$(cd ${top_dir} && ls -d ${src_pattern}/ | sort | tail -n 1)

echo "patching files..." >&2

pushd ${src_dir} >/dev/null

rsync -av ${dev_dir}/src/patch/lib/ lib/

git apply -v --ignore-whitespace -p1 ${dev_dir}/src/patch/lib-cpp-cmakelists.txt.patch
git apply -v --ignore-whitespace -p1 ${dev_dir}/src/patch/aix-lib-cpp-cmakelists.txt.patch
git apply -v --ignore-whitespace -p1 ${dev_dir}/src/patch/zlib-from-ext.patch
git apply -v --ignore-whitespace -p1 ${dev_dir}/src/patch/aix-remove-include-system.patch
git apply -v --ignore-whitespace -p1 ${dev_dir}/src/patch/aix-lib-cpp-src-thrift-transport-thttpserver.cpp.patch
git apply -v --ignore-whitespace -p1 ${dev_dir}/src/patch/boost-functional.patch
git apply -v --ignore-whitespace -p1 ${dev_dir}/src/patch/tservertransport.h.patch

popd >/dev/null

echo "done" >&2
echo "" >&2
