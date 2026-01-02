@echo off

set arch=%1
set project=csc_service_idl
set src_dir=%CD%
set ext_dir=%src_dir%\..\ext
set pkginstall_dir=%src_dir%\pkg-install\%project%
set export_dir=%src_dir%\..\..\export\csc_core_applications

:install

rmdir /S /Q %pkginstall_dir% >NUL
mkdir %pkginstall_dir% >NUL

robocopy ^
    %src_dir%\thrift\idl\ ^
    %pkginstall_dir%\idl\ ^
    *.thrift ^
    /s /NFL /NDL /NJH /NJS /nc /ns /np
if %ERRORLEVEL% GTR 1 exit /b %ERRORLEVEL%

robocopy ^
    %src_dir%\thrift\target\ ^
    %pkginstall_dir%\target\ ^
    *.targets ^
    /s /NFL /NDL /NJH /NJS /nc /ns /np
if %ERRORLEVEL% GTR 1 exit /b %ERRORLEVEL%

robocopy ^
    %src_dir%\pxverbund\include\types\ ^
    %pkginstall_dir%\idl\types\ ^
    *.inc ^
    /s /NFL /NDL /NJH /NJS /nc /ns /np
if %ERRORLEVEL% GTR 1 exit /b %ERRORLEVEL%

:package
REM note: most of this is done in parent export.bat

REM rmdir /S /Q %export_dir% >NUL
REM mkdir %export_dir% >NUL

echo zipping %pkginstall_dir%
pushd %pkginstall_dir% >NUL
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

7z.exe a %export_dir%\%project%.zip .
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

popd >NUL

REM copy %src_dir%\ivy.xml %export_dir%
REM copy %src_dir%\build.xml %export_dir%

:create-nuget

REM note: .nuspec file is copied via build.xml by ant
REM reason: to align version numbers (nuget <-> ivy.xml)

pushd %pkginstall_dir%
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

del *.nupkg

xcopy /Y /D %export_dir%\..\nuget\cscservice_idl.nuspec %pkginstall_dir%\
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

nuget pack cscservice_idl.nuspec
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

xcopy /Y /D *.nupkg %export_dir%\
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

popd
