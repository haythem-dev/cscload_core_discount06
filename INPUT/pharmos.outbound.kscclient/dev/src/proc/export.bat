@echo off

set arch=%1
set project=kscclient
set src_dir=%CD%
set ext_dir=%CD%\..\ext
set pkginstall_dir=%src_dir%\pkg-install
set export_dir=%src_dir%\..\..\export\%project%

set arch_dir=
if "%arch%" == "win64" (
    set arch_dir=x64\
    goto :install
)
:install

rmdir /S /Q %pkginstall_dir% >NUL
mkdir %pkginstall_dir% >NUL

xcopy /Y /D %ext_dir%\csc_core_applications\idl\kscserver\*.h %pkginstall_dir%\include\kscclient\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\*.h                                     %pkginstall_dir%\include\kscclient\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

xcopy /Y /D %src_dir%\%arch_dir%Debug\kscclient.lib   %pkginstall_dir%\lib\Debug\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D %src_dir%\%arch_dir%Debug\kscclient.pdb   %pkginstall_dir%\lib\Debug\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

xcopy /Y /D %src_dir%\%arch_dir%Release\kscclient.lib %pkginstall_dir%\lib\Release\
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

xcopy /Y /D "%src_dir%\%arch_dir%Debug SWIMP\kscclient.dll"   "%pkginstall_dir%\lib\Debug SWIMP\"
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D "%src_dir%\%arch_dir%Debug SWIMP\kscclient.lib"   "%pkginstall_dir%\lib\Debug SWIMP\"
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D "%src_dir%\%arch_dir%Debug SWIMP\kscclient.pdb"   "%pkginstall_dir%\lib\Debug SWIMP\"
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

xcopy /Y /D "%src_dir%\%arch_dir%Release SWIMP\kscclient.dll" "%pkginstall_dir%\lib\Release SWIMP\"
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
xcopy /Y /D "%src_dir%\%arch_dir%Release SWIMP\kscclient.lib" "%pkginstall_dir%\lib\Release SWIMP\"
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

:package

rmdir /S /Q %export_dir% >NUL
mkdir %export_dir% >NUL

echo zipping %pkginstall_dir%
pushd %pkginstall_dir% >NUL
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

7z.exe a %export_dir%\%project%.zip .
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

popd >NUL

copy %src_dir%\ivy.xml %export_dir%
copy %src_dir%\build.xml %export_dir%
