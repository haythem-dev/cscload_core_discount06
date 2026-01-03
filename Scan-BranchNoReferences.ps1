<#
.SYNOPSIS
    Universal BranchNo Reference Scanner for CPR0003319.
.DESCRIPTION
    Scans specified directory for branchno references in C++, SQL, Thrift, and Script files.
    Exports findings to JSON format with context lines.
.PARAMETER Path
    Root path to scan. Defaults to current directory.
.PARAMETER OutputFile
    Path for the output JSON file.
#>
param (
    [string]$Path = ".",
    [string]$OutputFile = "scan_results.json"
)

$ErrorActionPreference = "Stop"
$SearchPatterns = @("*.cxx", "*.cpp", "*.h", "*.hpp", "*.sh", "*.thrift", "*.sql", "*.xml")
$RegexPattern = "(?i)(branchno|branch_no|filialnr)"

Write-Host "[INFO] Starting scan in: $Path" -ForegroundColor Cyan

# Find all matching files
$FilesToScan = Get-ChildItem -Path $Path -Include $SearchPatterns -Recurse -File

$Results = New-Object System.Collections.Generic.List[PSObject]

foreach ($File in $FilesToScan) {
    try {
        # Read file content efficiently
        $Content = Get-Content -Path $File.FullName -ErrorAction SilentlyContinue
        
        for ($i = 0; $i -lt $Content.Count; $i++) {
            if ($Content[$i] -match $RegexPattern) {
                
                # Extract Context (5 lines before and after)
                $StartLine = [Math]::Max(0, $i - 5)
                $EndLine = [Math]::Min($Content.Count - 1, $i + 5)
                
                # Join lines for context blocks
                $ContextBefore = ($Content[$StartLine..($i-1)]) -join "`n"
                $ContextAfter = ($Content[($i+1)..$EndLine]) -join "`n"

                $MatchObject = [PSCustomObject]@{
                    file_path      = $File.FullName
                    line_number    = $i + 1
                    matched_text   = $Content[$i].Trim()
                    context_before = $ContextBefore
                    context_after  = $ContextAfter
                    file_type      = $File.Extension
                    timestamp      = (Get-Date).ToString("yyyy-MM-ddTHH:mm:ssZ")
                }
                
                $Results.Add($MatchObject)
            }
        }
    }
    catch {
        Write-Warning "Could not read file: $($File.FullName)"
    }
}

# Export to JSON
$Results | ConvertTo-Json -Depth 5 | Out-File -FilePath $OutputFile -Encoding UTF8
Write-Host "[SUCCESS] Found $($Results.Count) matches. Saved to $OutputFile" -ForegroundColor Green