@echo off
setlocal enabledelayedexpansion

echo ###########################################################
echo # CPR0003319 Impact Analysis Scan
echo ###########################################################
echo.

set "SEARCH_ROOT=%CD%"
set "OUTPUT_FILE=%SEARCH_ROOT%\cpr_impact_report.txt"

echo Scanning for BranchNo/Discount dependencies... > "%OUTPUT_FILE%"
echo Date: %DATE% %TIME% >> "%OUTPUT_FILE%"
echo ----------------------------------------------------------- >> "%OUTPUT_FILE%"

:: Define target tables
set "TABLES=discount promotionquota promotionquotacst promotionscale discountgrp discountgrpmem customerpharmacygr"

:: 1. Search in C++ and CXX files for SQL patterns
echo [1/3] Scanning C++/ESQL source files...
for %%T in (%TABLES%) do (
    echo. >> "%OUTPUT_FILE%"
    echo === Table: %%T === >> "%OUTPUT_FILE%"
    findstr /S /I /C:"%%T" /C:"BRANCHNO" *.cxx *.cpp *.h *.pc *.sqc >> "%OUTPUT_FILE%"
)

:: 2. Search in Shell Scripts for loop patterns
echo [2/3] Scanning Shell scripts for branch loops...
findstr /S /I /C:"for" /C:"vz" /C:"01" /C:"02" *.sh *.vars *.option >> "%OUTPUT_FILE%"

:: 3. Search for specific loader parameters
echo [3/3] Scanning for loader parameter usage...
findstr /S /I /C:"-vz" /C:"-branchno" *.cxx *.cpp >> "%OUTPUT_FILE%"

echo.
echo Scan Complete. Results saved to: %OUTPUT_FILE%
echo Please check the file for the list of impacted locations.
pause
