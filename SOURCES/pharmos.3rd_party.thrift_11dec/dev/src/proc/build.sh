#!/usr/bin/bash -e

ext_dir=$(pwd)/../ext
src_dir=$(pwd)/thrift*
build_dir=$(pwd)/build
install_dir=$(pwd)/pkg-install
patch_dir=$(pwd)/patch

export PATH=${ext_dir}/cmake/bin:${ext_dir}/flex/bin:${ext_dir}/bison/bin:$PATH
export BISON_PKGDATADIR=${ext_dir}/bison/share/bison

for variant in Release Debug ; do
    mkdir -p ${build_dir}/${variant} >/dev/null 2>&1
    pushd ${build_dir}/${variant} >/dev/null

    echo "generate solution ( ${variant} )" >&2
    cmake \
        -DCMAKE_INSTALL_PREFIX=${install_dir} \
        -DCMAKE_BUILD_TYPE=${variant} \
        -DCMAKE_INSTALL_BINDIR=bin/${variant} \
        -DCMAKE_INSTALL_LIBDIR=lib/${variant} \
        -DWITH_ZLIB=ON \
        -DBOOST_ROOT=${ext_dir}/boost \
        -DWITH_BOOSTTHREADS=ON \
        -DWITH_BOOST_FUNCTIONAL=ON \
        -DWITH_BOOST_SMART_PTR=ON \
        -DWITH_OPENSSL=ON \
        -DOPENSSL_ROOT_DIR=${ext_dir}/openssl \
        -DWITH_SHARED_LIB=ON \
        -DWITH_STATIC_LIB=ON \
        -DWITH_QT4=OFF \
        -DWITH_QT5=OFF \
        -DWITH_PYTHON=OFF \
        -DWITH_JAVA=OFF \
        -DBUILD_TESTING=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_TUTORIALS=OFF \
        -DCMAKE_CXX_STANDARD=98 \
        ${src_dir}
    echo "done" >&2
    echo "" >&2

    echo "build ( ${variant} )" >&2
    cmake \
        --build $(pwd) \
        --target all \
        --config $variant
    echo "done" >&2
    echo "" >&2

    echo "install ( ${variant} )" >&2
    cmake \
        --build $(pwd) \
        --target install \
        --config $variant
    echo "done" >&2
    echo "" >&2

    popd >/dev/null
done

pushd $install_dir >/dev/null

git apply -v --ignore-whitespace -p1 $patch_dir/thrift-config.h.patch

popd >/dev/null
