@echo off

set arch=%1
set project=ae
set src_dir=%CD%
set ext_dir=%src_dir%\..\ext
set pkginstall_dir=%src_dir%\pkg-install
set export_dir=%src_dir%\..\..\..\..\export\csc_core_applications

:install

rmdir /S /Q %pkginstall_dir% >NUL
mkdir %pkginstall_dir% >NUL

xcopy /Y /D %src_dir%\ae\WinRel\ae.exe                            %pkginstall_dir%\WinRel\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
copy /Y %src_dir%\ae\WinRel\ae.exe                                %pkginstall_dir%\WinRel\Aech.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
copy /Y %src_dir%\ae\WinRel\ae.exe                                %pkginstall_dir%\WinRel\Aede_hs.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\WinRel\ae.pdb                            %pkginstall_dir%\WinRel\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
copy /Y %src_dir%\ini\PROD\KSC.INI                                %pkginstall_dir%\WinRel\ksc.ini
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\multilang\ae_fr.txt                      %pkginstall_dir%\WinRel\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\multilang\pperrormsg.*                   %pkginstall_dir%\WinRel\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %ext_dir%\hipath_old\HPPCProxyLib\custctilink.dll     %pkginstall_dir%\WinRel\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %ext_dir%\hipath_old\HPPCProxyLib\Release\vc100.pdb   %pkginstall_dir%\WinRel\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

rem xcopy ae with new hipath lib
xcopy /Y /D %src_dir%\ae\ReleaseHipathNew\ae.exe                  %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
copy /Y %src_dir%\ae\ReleaseHipathNew\ae.exe                      %pkginstall_dir%\ReleaseHipathNew\Aeau.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
copy /Y %src_dir%\ae\ReleaseHipathNew\ae.exe                      %pkginstall_dir%\ReleaseHipathNew\Aebg.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
copy /Y %src_dir%\ae\ReleaseHipathNew\ae.exe                      %pkginstall_dir%\ReleaseHipathNew\Aefr.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
copy /Y %src_dir%\ae\ReleaseHipathNew\ae.exe                      %pkginstall_dir%\ReleaseHipathNew\Aehr.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
copy /Y %src_dir%\ae\ReleaseHipathNew\ae.exe                      %pkginstall_dir%\ReleaseHipathNew\Aers.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
copy /Y %src_dir%\ae\ReleaseHipathNew\ae.exe                      %pkginstall_dir%\ReleaseHipathNew\Aede.exe
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\ReleaseHipathNew\ae.pdb                  %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

copy /Y %src_dir%\ini\PROD\KSC.INI                                %pkginstall_dir%\ReleaseHipathNew\ksc.ini
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\multilang\ae_bg.txt                      %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\multilang\ae_en.txt                      %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\multilang\ae_fr.txt                      %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\multilang\ae_hr.txt                      %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\multilang\ae_rs.txt                      %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\ae\multilang\pperrormsg.*                   %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

REM =======================================================================================================
REM 
REM =======================================================================================================
xcopy /Y /D %ext_dir%\hipath\HPPCProxyLib\cocc*                %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %ext_dir%\hipath\HPPCProxyLib\Release\XCPTHLR.dll  %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

xcopy /Y /D %ext_dir%\log4cplus\bin\Release\log4cplus.dll  %pkginstall_dir%\ReleaseHipathNew\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

:package
REM note: most of this is done in parent export.bat

REM rmdir /S /Q %export_dir% >NUL
REM mkdir %export_dir% >NUL

echo zipping %src_dir%\pkg-install
pushd %src_dir%\pkg-install >NUL

7z.exe a %export_dir%\%project%.zip .
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

popd >NUL

REM copy %src_dir%\ivy.xml %export_dir%
REM copy %src_dir%\build.xml %export_dir%
