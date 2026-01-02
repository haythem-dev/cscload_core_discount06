@echo off

set project=thrift
set src_dir=%CD%
set export_dir=%CD%\..\..\export\%project%

echo zipping %src_dir%\pkg-install
pushd %src_dir%\pkg-install >NUL
7z.exe a %export_dir%\%project%.zip .
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

copy %src_dir%\ivy.xml %export_dir%
copy %src_dir%\build.xml %export_dir%

popd >NUL

REM C# nuget package

rem c# export
REM echo copy csharp libs - net35
REM cd %SRCDIR%\build.win\thrift_csharp\bin\Release\net35
REM 
REM robocopy . %DESTDIR%\csharp\lib\net35 Thrift.dll Thrift.pdb /S /NFL /NDL /NJH /NJS /nc /ns /np
REM 
REM echo copy csharp libs - net40
REM 
REM cd %SRCDIR%\build.win\thrift_csharp\bin\Release\net40
REM 
REM robocopy . %DESTDIR%\csharp\lib\net40 Thrift.dll Thrift.pdb /S /NFL /NDL /NJH /NJS /nc /ns /np
REM 
REM echo copy thrift.nuspec
REM 
REM cd %SRCDIR%\build.win\thrift_csharp\
REM 
REM rem note: nuspec is copied by ant script to align version numbers of nuget with ivy
REM rem robocopy . %DESTDIR%\csharp\ thrift.nuspec /S /NFL /NDL /NJH /NJS /nc /ns /np
REM 
REM robocopy . %DESTDIR%\csharp\ Pharmos.3rd_Party.Thrift.props  /S /NFL /NDL /NJH /NJS /nc /ns /np
REM 
REM cd %SRCDIR%\compiler
REM 
REM robocopy . %DESTDIR%\csharp\tools\ thrift-*.exe /NFL /NDL /NJH /NJS /nc /ns /np
REM 
REM robocopy %SRCDIR%\proc %DESTDIR%\csharp\tools\ thrift.cmd /NFL /NDL /NJH /NJS /nc /ns /np
REM 
REM cd %DESTDIR%\csharp
REM 
REM nuget pack thrift.nuspec -OutputDirectory %DESTDIR%
