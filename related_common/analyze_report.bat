@echo off
setlocal enabledelayedexpansion

set "REPORT_FILE=cpr_impact_report.txt"
set "SUMMARY_FILE=cpr_summary.txt"

if not exist "%REPORT_FILE%" (
    echo Error: %REPORT_FILE% not found.
    pause
    exit /b
)

echo ########################################################### > "%SUMMARY_FILE%"
echo # CPR0003319 Consolidated Impact Summary
echo ########################################################### >> "%SUMMARY_FILE%"
echo. >> "%SUMMARY_FILE%"

echo === 1. CDM (Global Data Model) === >> "%SUMMARY_FILE%"
findstr /I "pharmos.base.cdm" "%REPORT_FILE%" | findstr /I ".cxx .cpp .h" >> "%SUMMARY_FILE%"
echo. >> "%SUMMARY_FILE%"

echo === 2. CSC_CORE (Application Logic) === >> "%SUMMARY_FILE%"
echo --- PXDB (Database Layer) --- >> "%SUMMARY_FILE%"
findstr /I "csc_core" "%REPORT_FILE%" | findstr /I "pxdb" >> "%SUMMARY_FILE%"
echo. >> "%SUMMARY_FILE%"
echo --- AAPSERV (Business Logic) --- >> "%SUMMARY_FILE%"
findstr /I "csc_core" "%REPORT_FILE%" | findstr /I "aapserv" >> "%SUMMARY_FILE%"
echo. >> "%SUMMARY_FILE%"
echo --- PXVERBUND (Calculation) --- >> "%SUMMARY_FILE%"
findstr /I "csc_core" "%REPORT_FILE%" | findstr /I "pxverbund" >> "%SUMMARY_FILE%"
echo. >> "%SUMMARY_FILE%"

echo === 3. CSC_LOAD (Batch Loaders) === >> "%SUMMARY_FILE%"
echo --- Loaders Source --- >> "%SUMMARY_FILE%"
findstr /I "csc_load" "%REPORT_FILE%" | findstr /I "load" | findstr /I ".cxx .cpp" >> "%SUMMARY_FILE%"
echo. >> "%SUMMARY_FILE%"
echo --- Shell Scripts (Loops) --- >> "%SUMMARY_FILE%"
findstr /I "csc_load" "%REPORT_FILE%" | findstr /I ".sh .vars .option" >> "%SUMMARY_FILE%"
echo. >> "%SUMMARY_FILE%"

echo Analysis complete. Summary saved to: %SUMMARY_FILE%
echo.
echo Critical Files Found Count:
find /c /v "" "%SUMMARY_FILE%"
pause
