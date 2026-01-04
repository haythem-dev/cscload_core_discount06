<#
.SYNOPSIS
    Enhanced BranchNo Reference Scanner - Fixed & Optimized Version (v2.3)
    
.DESCRIPTION
    Advanced scanner for CPR0003319 with SQL context detection, table analysis,
    multi-branch protection, function detection, and performance safeguards.
    
    This version preserves ALL original functionality and analysis logic,
    but fixes two critical issues that prevented completion:
    1. File discovery now correctly finds all files (fixed the -Include bug)
    2. Uses Select-String for ultra-fast matching and safe context handling
       → eliminates hanging at 99.8% on small repetitive files like version.c
    
.PARAMETER Path
    Root directory to scan
    
.PARAMETER OutputFile
    JSON output file path
    
.PARAMETER FileTypes
    Extensions to scan
    
.PARAMETER MaxMatchesPerFile
    Maximum matches per file - default 500
    
.PARAMETER MaxFileSizeMB
    Skip files larger than this (MB) - default 20
    
.EXAMPLE
    .\Enhanced-Scan-BranchNo_v2.3.ps1 -Path "pharmos.outbound.csc_core_applications/dev/src" -OutputFile "scan_results.json"
#>

param(
    [Parameter(Mandatory=$true)]
    [string]$Path,
    
    [Parameter(Mandatory=$false)]
    [string]$OutputFile = "enhanced_scan_results.json",
    
    [Parameter(Mandatory=$false)]
    [string[]]$FileTypes = @(".cpp", ".cxx", ".h", ".sh", ".hpp", ".c", ".cc"),
    
    [int]$MaxMatchesPerFile = 500,
    
    [int]$MaxFileSizeMB = 20
)

# Configuration
$CONTEXT_LINES = 20
$MAX_LINE_LENGTH = 10000

# Patterns - exactly as in original
$BRANCHNO_PATTERNS = @("branchno","filialNr","filialnr","vertriebszentrum","branchNo","FilialNr","branch_no","BRANCHNO","FILIALNR")
$PATTERN_JOINED = '\b(' + ($BRANCHNO_PATTERNS -join '|') + ')\b'

$SQL_KEYWORDS = @{
    DML       = @("SELECT","INSERT","UPDATE","DELETE","EXEC SQL")
    CLAUSES   = @("WHERE","FROM","INTO","SET","VALUES","JOIN","ON")
    OPERATORS = @("=","!=","<>","IN","NOT IN","BETWEEN")
}
$DISCOUNT_TABLES = @("discount","discountgrp","discountgrpmem","cstdiscountcont","lddiscount","zdiscount","pricelist","pricerange")
$MULTI_BRANCH_KEYWORDS = @("ibtbranchno","destbranchno","sourcebranchno","srcbranchno","targetbranchno","frombranchno","tobranchno")

$script:Stats = @{
    TotalFiles = 0; ProcessedFiles = 0; SkippedFiles = 0; TotalMatches = 0
    SQLMatches = 0; DiscountTableMatches = 0; MultiBranchMatches = 0; FunctionMatches = 0; Errors = 0
}

#region Helpers

function Write-Progress-Info {
    param([string]$Message, [string]$Color = "Cyan")
    Write-Host "[$(Get-Date -Format 'HH:mm:ss')] $Message" -ForegroundColor $Color
}

function Extract-TableNames {
    param([string]$SqlContext)
    $tables = @()
    foreach ($kw in "FROM","INTO","UPDATE","JOIN") {
        if ($SqlContext -match "$kw\s+(\w+)") { $tables += $matches[1] }
    }
    return $tables | Select-Object -Unique
}

function Detect-SQL-Keywords {
    param([string]$Context)
    $found = @{ DML=@(); CLAUSES=@(); OPERATORS=@() }
    foreach ($cat in $SQL_KEYWORDS.Keys) {
        foreach ($kw in $SQL_KEYWORDS[$cat]) {
            if ($Context -match "\b$kw\b") { $found[$cat] += $kw }
        }
    }
    return $found
}

function Detect-Multi-Branch-Keywords {
    param([string]$Context)
    $MULTI_BRANCH_KEYWORDS | Where-Object { $Context -imatch "\b$_\b" }
}

function Get-Function-Signature {
    param([string]$Context)
    if ($Context -match "(void|int|short|long|bool|double|float|char|string|RETCODE)\s+(\w+)\s*\([^)]*branchno[^)]*\)") {
        return @{ HasFunction=$true; ReturnType=$matches[1]; FunctionName=$matches[2]; FullSignature=$matches[0] }
    }
    return @{ HasFunction=$false }
}

function Analyze-Context {
    param([string]$Context)
    $analysis = @{
        has_sql = $false; sql_keywords = @{}; tables = @(); discount_tables = @()
        multi_branch_keywords = @(); function_info = @{}; context_type = "UNKNOWN"
    }

    $sqlKw = Detect-SQL-Keywords -Context $Context
    if ($sqlKw.DML.Count -gt 0 -or $sqlKw.CLAUSES.Count -gt 0) {
        $analysis.has_sql = $true
        $analysis.sql_keywords = $sqlKw
        $script:Stats.SQLMatches++
    }

    if ($analysis.has_sql) {
        $tables = Extract-TableNames -SqlContext $Context
        $analysis.tables = $tables
        foreach ($t in $tables) {
            if ($DISCOUNT_TABLES -contains $t.ToLower()) {
                $analysis.discount_tables += $t
                $script:Stats.DiscountTableMatches++
            }
        }
    }

    $multi = Detect-Multi-Branch-Keywords -Context $Context
    if ($multi.Count -gt 0) {
        $analysis.multi_branch_keywords = $multi
        $script:Stats.MultiBranchMatches++
    }

    $func = Get-Function-Signature -Context $Context
    if ($func.HasFunction) {
        $analysis.function_info = $func
        $script:Stats.FunctionMatches++
    }

    if ($analysis.discount_tables.Count -gt 0)       { $analysis.context_type = "DISCOUNT_SQL" }
    elseif ($analysis.multi_branch_keywords.Count -gt 0) { $analysis.context_type = "MULTI_BRANCH" }
    elseif ($analysis.has_sql)                       { $analysis.context_type = "OTHER_SQL" }
    elseif ($func.HasFunction)                       { $analysis.context_type = "FUNCTION_DEF" }
    elseif ($Context -match "log|print|cout|fprintf|sprintf|cerr") { $analysis.context_type = "LOGGING" }
    else                                             { $analysis.context_type = "UNCLEAR" }

    return $analysis
}

function Get-Enhanced-Context {
    param([Microsoft.PowerShell.Commands.MatchInfo]$ssMatch)
    $lines = @()
    $contentsForFull = @()
    $currentLine = $ssMatch.LineNumber - $ssMatch.Context.PreContext.Count

    foreach ($line in $ssMatch.Context.PreContext) {
        $truncated = if ($line.Length -gt $MAX_LINE_LENGTH) { $line.Substring(0, $MAX_LINE_LENGTH) + "..." } else { $line }
        $lines += @{ line_number = $currentLine++; content = $truncated; is_match = $false }
        $contentsForFull += $truncated
    }

    $matchLine = if ($ssMatch.Line.Length -gt $MAX_LINE_LENGTH) { $ssMatch.Line.Substring(0, $MAX_LINE_LENGTH) + "..." } else { $ssMatch.Line }
    $lines += @{ line_number = $ssMatch.LineNumber; content = $matchLine; is_match = $true }
    $contentsForFull += $matchLine

    $currentLine = $ssMatch.LineNumber + 1
    foreach ($line in $ssMatch.Context.PostContext) {
        $truncated = if ($line.Length -gt $MAX_LINE_LENGTH) { $line.Substring(0, $MAX_LINE_LENGTH) + "..." } else { $line }
        $lines += @{ line_number = $currentLine++; content = $truncated; is_match = $false }
        $contentsForFull += $truncated
    }

    return @{ lines = $lines; full_text = ($contentsForFull -join "`n") }
}

function Scan-File {
    param([System.IO.FileInfo]$File)

    try {
        if ($File.Length -gt ($MaxFileSizeMB * 1MB)) {
            Write-Progress-Info "  SKIPPED (size > $($MaxFileSizeMB)MB): $($File.Name)" "Yellow"
            $script:Stats.SkippedFiles++
            return @()
        }

        Write-Progress-Info "  Processing: $($File.Name) ($([math]::Round($File.Length/1KB,1)) KB)" "Gray"

        # Ultra-fast and safe matching using Select-String
        $ssMatches = Select-String -Path $File.FullName -Pattern $PATTERN_JOINED -AllMatches -CaseSensitive:$false -Context $CONTEXT_LINES,$CONTEXT_LINES

        if (-not $ssMatches) {
            $script:Stats.ProcessedFiles++
            return @()
        }

        if ($ssMatches.Count -gt $MaxMatchesPerFile) {
            Write-Progress-Info "  CAPPED: $($ssMatches.Count) → $MaxMatchesPerFile matches in $($File.Name)" "Yellow"
            $ssMatches = $ssMatches[0..($MaxMatchesPerFile-1)]
        }

        $matches = @()
        foreach ($ssMatch in $ssMatches) {
            $matched_pattern = $ssMatch.Matches.Groups[1].Value

            $ctx = Get-Enhanced-Context -ssMatch $ssMatch
            $analysis = Analyze-Context -Context $ctx.full_text

            $matches += @{
                file_path       = $File.FullName -replace ([regex]::Escape($Path + [IO.Path]::DirectorySeparatorChar)), ""
                file_name       = $File.Name
                file_type       = $File.Extension
                line_number     = $ssMatch.LineNumber
                matched_pattern = $matched_pattern
                line_content    = $ssMatch.Line
                context         = $ctx.lines
                full_context    = $ctx.full_text
                analysis        = $analysis
                timestamp       = (Get-Date -Format "o")
            }
            $script:Stats.TotalMatches++
        }

        Write-Progress-Info "  Found $($matches.Count) matches in $($File.Name)" "Green"
        $script:Stats.ProcessedFiles++
        return $matches

    } catch {
        Write-Warning "Error processing $($File.Name): $_"
        $script:Stats.Errors++
        $script:Stats.SkippedFiles++
        return @()
    }
}

#endregion

#region Main

Write-Progress-Info "========================================" "Green"
Write-Progress-Info "ENHANCED BRANCHNO SCANNER v2.3 - CPR0003319" "Green"
Write-Progress-Info "========================================" "Green"

if (-not (Test-Path $Path -PathType Container)) {
    Write-Host "ERROR: Path not found or not a directory: $Path" -ForegroundColor Red
    exit 1
}

Write-Progress-Info "Source: $Path" "Yellow"
Write-Progress-Info "Output: $OutputFile" "Yellow"
Write-Progress-Info "Limits: Max $MaxMatchesPerFile matches/file, skip > $MaxFileSizeMB MB" "Yellow"

# FIXED: Reliable file discovery with case-insensitive extension matching
$allFiles = Get-ChildItem -Path $Path -Recurse -File -ErrorAction SilentlyContinue | 
            Where-Object { $FileTypes -contains $_.Extension.ToLower() }

$script:Stats.TotalFiles = $allFiles.Count
Write-Progress-Info "Found $($allFiles.Count) files to scan" "Green"

if ($allFiles.Count -eq 0) {
    Write-Progress-Info "WARNING: No files found matching extensions $($FileTypes -join ', '). Check path and content." "Red"
}

$allMatches = @()
$counter = 0

foreach ($file in $allFiles) {
    $counter++
    if ($counter % 20 -eq 0 -or $counter -eq $allFiles.Count) {
        $pct = [math]::Round(($counter / $allFiles.Count) * 100, 1)
        Write-Progress-Info "Progress: $counter/$($allFiles.Count) ($pct%) - $($file.Name)"
    }
    $fileMatches = Scan-File -File $file
    $allMatches += $fileMatches
}

$contextBreakdown = @{}
$allMatches | Group-Object { $_.analysis.context_type } | ForEach-Object {
    $contextBreakdown[$_.Name] = $_.Count
}

$summary = @{
    scan_metadata = @{ scan_date = (Get-Date -Format "o"); source_path = $Path; scanner_version = "2.3-FIXED" }
    statistics = $script:Stats
    context_type_breakdown = $contextBreakdown
    matches = $allMatches
}

$summary | ConvertTo-Json -Depth 10 -Compress | Set-Content -Path $OutputFile -Encoding UTF8

Write-Progress-Info ""
Write-Progress-Info "SCAN COMPLETE" "Green"
Write-Progress-Info "Total Matches: $($script:Stats.TotalMatches)" "Yellow"
Write-Progress-Info "  SQL: $($script:Stats.SQLMatches) | Discount Tables: $($script:Stats.DiscountTableMatches) | Multi-Branch: $($script:Stats.MultiBranchMatches) | Functions: $($script:Stats.FunctionMatches)"

Write-Progress-Info ""
Write-Progress-Info "Context Distribution:" "Yellow"
foreach ($type in ($contextBreakdown.Keys | Sort-Object)) {
    $count = $contextBreakdown[$type]
    $pct = if ($script:Stats.TotalMatches -gt 0) { [math]::Round(($count / $script:Stats.TotalMatches) * 100, 1) } else { 0 }
    Write-Progress-Info ("  {0}: {1} ({2}%)" -f $type.PadRight(15), $count, $pct)
}

Write-Progress-Info ""
Write-Progress-Info "Results saved to: $OutputFile" "Green"
Write-Progress-Info "========================================" "Green"

#endregion