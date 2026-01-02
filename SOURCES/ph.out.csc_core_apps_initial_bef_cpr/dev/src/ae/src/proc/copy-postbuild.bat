@echo off

echo ==========================================================================
echo  postbuild copy - START
echo ==========================================================================

echo %1 %2 %3 %4 %5

set ProjectName=%1
set Platform=%2
set Configuration=%3
set SolutionDir=%4
set OutDir=%5

xcopy /Y /D %SolutionDir%ini\TEST\ksc.ini %OutDir%
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

REM ###################################################################################
REM copying log4clus lib(s)
REM ###################################################################################
echo --------------------------------------------------------------------------
echo copy log4plus lib(s):
echo --------------------------------------------------------------------------
set configFile=Debug\log4cplusd.dll
echo "%Configuration%" | find /i "Release">nul && set configFile=Release\log4cplus.dll

echo configFile = %configFile%

REM xcopy /Y /D %SolutionDir%..\ext\log4cplus\bin\%configFile%\log4cplus*.dll %OutDir%
REM xcopy /Y /D %SolutionDir%..\ext\log4cplus\bin\%configFile%\log4cplus*.dll %OutDir%
xcopy %SolutionDir%..\ext\log4cplus\bin\%configFile% %OutDir% /Y /D
REM robocopy source dest file(s) [options]  

if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

echo ==========================================================================
echo  postbuild copy - END
echo ==========================================================================
echo.
echo.
