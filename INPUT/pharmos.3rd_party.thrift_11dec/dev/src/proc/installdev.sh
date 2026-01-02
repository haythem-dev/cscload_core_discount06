#!/bin/bash -e

src_dir=$(pwd)
install_dir=${src_dir}/pkg-export

project=thrift
version=$(xmllint --xpath "string(//ivy-module/info/@revision)" $src_dir/ivy.xml | sed -e 's/-${platform}//g' )

build_dir=${DEVLIB_PATH}/marathon/lib/$project/$version
runtime_dir=${WSS}/lib/$project/$version
compiler_path=${DEVLIB_PATH}/marathon/bin/thrift

echo "Installing $project files into $build_dir and $runtime_dir" >&2

mkdir -p $build_dir $runtime_dir/sharedlib

rsync -av $install_dir/ $build_dir/

#mkdir -p $runtime_dir/sharedlib/release
#rsync -av $install_dir/lib/ $runtime_dir/sharedlib/release/
ln -sf $build_dir/lib/ $runtime_dir/sharedlib/release

#echo "Relinking thrift-compiler to $compiler_path" >&2
#ln -sf $build_dir/bin/thrift ${compiler_path}

exit 0
