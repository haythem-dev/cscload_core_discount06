@echo off

set PROJECT=cdm
set PWD=%CD%

set BASEDIR=%PWD%\..\..

set SRCDIR=%BASEDIR%\dev\src
set EXTDIR=%BASEDIR%\dev\ext
set DESTDIR=%BASEDIR%\export\%PROJECT%

echo -----------------------------------------------------
echo  copy %PROJECT% files to export directory 
echo       from %SRCDIR%
echo       from %EXTDIR%
echo       to   %DESTDIR%
echo  compress export files to %DESTDIR%\built.zip
echo -----------------------------------------------------

rmdir /S /Q %DESTDIR% 2>nul
mkdir %DESTDIR%

echo copy binaries ...
xcopy %SRCDIR%\ekzdp\release\Ekzdp.exe   			%DESTDIR%\   /d /y /s /e /q
xcopy %SRCDIR%\ekzdp\translation\bg\ekzdp_bg.txt  	%DESTDIR%\   /d /y /s /e /q
xcopy %SRCDIR%\ekzdp\translation\fr\ekzdp_fr.txt  	%DESTDIR%\   /d /y /s /e /q
xcopy %SRCDIR%\ekzdp\translation\hr\ekzdp_hr.txt  	%DESTDIR%\   /d /y /s /e /q
xcopy %SRCDIR%\zdputil\release\Zdputil.exe 			%DESTDIR%\   /d /y /s /e /q
xcopy %SRCDIR%\zdpdruck\release\Zdpdruck.exe 		%DESTDIR%\   /d /y /s /e /q
xcopy %SRCDIR%\misc\ini\*.ini 						%DESTDIR%\   /d /y /s /e /q

cd %DESTDIR%
echo zip %DESTDIR%
7z.exe a -sdel .\%PROJECT%.zip .

copy %SRCDIR%\build.xml %DESTDIR%\
copy %SRCDIR%\ivy.xml   %DESTDIR%\

cd /D %PWD%
