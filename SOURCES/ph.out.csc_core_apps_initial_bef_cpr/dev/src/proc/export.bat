@echo off

set arch=%1
set project=csc_core_applications
set src_dir=%CD%
set export_dir=%src_dir%\..\..\export\%project%

:install

rmdir /S /Q %export_dir% >NUL
mkdir %export_dir% >NUL

:install-ae
pushd %src_dir%\ae\src
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

cmd /c proc\export.bat %*
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

popd

:install-thrift_idl

cmd /c %src_dir%\proc\export-thrift_idl.bat %*
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

:install-legacy_idl

cmd /c %src_dir%\proc\export-legacy_idl.bat %*
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

:package

copy %src_dir%\ivy.xml %export_dir%
copy %src_dir%\build.xml %export_dir%
