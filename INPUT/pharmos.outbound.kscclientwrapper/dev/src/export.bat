@echo off

set PWD=%CD%

SET PROJECT=kscclientwrapper

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


rmdir /S /Q %DESTDIR% > NUL


mkdir %DESTDIR%
mkdir %DESTDIR%\include
mkdir %DESTDIR%\lib
mkdir %DESTDIR%\lib\debug
mkdir %DESTDIR%\lib\release

copy /y %SRCDIR%\*.h		%DESTDIR%\include
copy /y %SRCDIR%\*.hpp		%DESTDIR%\include

copy /y %SRCDIR%\debug\%PROJECT%.lib	%DESTDIR%\lib\debug
copy /y %SRCDIR%\debug\%PROJECT%.pdb	%DESTDIR%\lib\debug
copy /y %SRCDIR%\release\%PROJECT%.lib	%DESTDIR%\lib\release
copy /y %SRCDIR%\release\%PROJECT%.pdb	%DESTDIR%\lib\release


cd %DESTDIR%
echo zip %DESTDIR%\%PROJECT%.zip ...
7z a -sdel .\%PROJECT%.zip .\

copy /y %SRCDIR%\build.xml %DESTDIR%
copy /y %SRCDIR%\ivy.xml %DESTDIR%

cd /D %PWD%

