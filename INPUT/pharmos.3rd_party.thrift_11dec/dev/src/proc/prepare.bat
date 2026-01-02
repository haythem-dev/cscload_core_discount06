@echo off

set dev_dir=%CD%\..

echo extracting thrift sources to %dev_dir%\src...

7z.exe ^
    x ^
    -y ^
    -o%dev_dir%\ext\thrift_source ^
    %dev_dir%\ext\thrift_source\thrift*.tar.gz
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

7z.exe ^
    x ^
    -y ^
    -o%dev_dir%\src ^
    %dev_dir%\ext\thrift_source\thrift*.tar ^
    >NUL
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

del %dev_dir%\ext\thrift_source\thrift*.tar

echo done
echo.

echo extracting thrift compiler to %dev_dir%\src\compiler

7z.exe ^
    x ^
    -y ^
    -o%dev_dir%\src\compiler ^
    %dev_dir%\ext\thrift_source\thrift_compiler*.zip ^
    >NUL
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

echo done
echo.

echo patching source files

pushd %dev_dir%\src\thrift*
    xcopy /Y /E /S /D %dev_dir%\src\patch\lib lib\

    git apply -v --ignore-whitespace -p1 %dev_dir%\src\patch\cmake-DefineOptions.cmake.patch
    if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
    git apply -v --ignore-whitespace -p1 %dev_dir%\src\patch\lib-cpp-cmakelists.txt.patch
    if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
    git apply -v --ignore-whitespace -p1 %dev_dir%\src\patch\zlib-from-ext.patch
    if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
    git apply -v --ignore-whitespace -p1 %dev_dir%\src\patch\boost-functional.patch
    if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
    git apply -v --ignore-whitespace -p1 %dev_dir%\src\patch\tservertransport.h.patch
    if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
popd

echo done
echo.