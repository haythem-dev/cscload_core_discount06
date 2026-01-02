@echo off

set arch=%1
set project=csc_legacy_idl
set src_dir=%CD%
set ext_dir=%src_dir%\..\ext
set pkginstall_dir=%src_dir%\pkg-install\%project%
set export_dir=%src_dir%\..\..\export\csc_core_applications

:install

rmdir /S /Q %pkginstall_dir% >NUL
mkdir %pkginstall_dir% >NUL

robocopy ^
    %src_dir%\kscserver\ ^
    %pkginstall_dir%\idl\kscserver\ ^
    kscsrv.h kscsrvdata.h kscsrvfkt.h ^
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
