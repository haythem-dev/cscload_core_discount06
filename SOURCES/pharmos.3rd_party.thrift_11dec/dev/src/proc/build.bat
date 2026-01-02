@echo on

set PATH=%CD%\..\ext\cmake\bin;%PATH%

pushd %CD%\thrift*
    set src_dir=%CD%
popd

set build_dir=%CD%\build
set install_dir=%CD%\pkg-install
@rem We need to use / in ext_dir otherwise we get a weird: cmake error "Invalid character escape '\C'"
set ext_dir=%CD:\=/%/../ext

@rem Parse parameter set by ant script. Defaults to 64-bit build
set arch= x64
set arch_flags=-DBoost_LIB_VERSION=-x64

set generator="Visual Studio 17 2022"

for %%v in (Release, Debug) do (call :buildVariant %%v || exit %ERRORLEVEL%)

xcopy /Y /D %CD%\compiler\thrift-*.exe %install_dir%\bin\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

xcopy /Y /D %CD%\patch\bin\thrift.cmd %install_dir%\bin\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

set patch_dir=%CD%\patch
pushd %install_dir%

git apply -v --ignore-whitespace -p1 %patch_dir%\thrift-config.h.patch
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

popd

goto :eof

:buildVariant
    set variant=%1

    mkdir %build_dir%\%variant% >NUL 2>&1
    pushd %build_dir%\%variant% >NUL
    if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%

    set debug_flags=
    if "%variant%" == "Debug" (
        set debug_flags=-DCMAKE_C_FLAGS_DEBUG="/MDd /Z7 /Ob0 /Od /RTC1"
        goto buildVariant_afterSet
    )
:buildVariant_afterSet
    @echo generate solution ( %variant% )
    cmake ^
        -G %generator% ^
        -A %arch% ^
        -DCMAKE_INSTALL_PREFIX=%install_dir% ^
        -DCMAKE_INSTALL_BINDIR=bin/%variant% ^
        -DCMAKE_INSTALL_LIBDIR=lib/%variant% ^
        -DWITH_ZLIB=ON ^
        -DZLIB_ROOT=%ext_dir%/zlib ^
        -DBOOST_ROOT=%ext_dir%/boost ^
        -DWITH_BOOSTTHREADS=ON ^
        -DWITH_BOOST_FUNCTIONAL=ON ^
        -DWITH_BOOST_SMART_PTR=ON ^
        -DWITH_BOOST_STATIC=ON ^
        -DWITH_OPENSSL=ON ^
        -DOPENSSL_ROOT_DIR=%ext_dir%/openssl ^
        -DWITH_SHARED_LIB=OFF ^
        -DWITH_QT4=OFF ^
        -DWITH_QT5=OFF ^
        -DWITH_PYTHON=OFF ^
        -DWITH_JAVA=OFF ^
        -DBUILD_TESTING=OFF ^
        -DBUILD_EXAMPLES=OFF ^
        -DBUILD_COMPILER=OFF ^
        %debug_flags% ^
        %arch_flags% ^
        %src_dir%
    if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
    @echo done
    @echo.

    @echo build ( %variant% )
    cmake ^
        --build %CD% ^
        --target ALL_BUILD ^
        --config %variant%
    if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
    @echo done
    @echo.

    @echo install ( %variant% )
    cmake ^
        --build %CD% ^
        --target INSTALL ^
        --config %variant%
    if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
    @echo done
    @echo.

    popd >NUL
goto :eof
