<#
.SYNOPSIS
    Smart BranchNo Classification with Table-Aware Logic
    
.DESCRIPTION
    Intelligent classifier for CPR0003319 that categorizes branchNo references:
    - CRITICAL-WRITE: INSERT/UPDATE on discount tables (MUST change to 0)
    - CRITICAL-READ: SELECT with WHERE branchno = (MUST change to 0)
    - PRESERVE: Multi-branch transfer logic (DO NOT change)
    - LOW: Logging, display, non-critical operations
    - UNCLEAR: Needs manual review
    
    Includes confidence scoring and automated action recommendations.
    
.PARAMETER ScanResultsFile
    JSON file from Enhanced-Scan-BranchNo.ps1
    
.PARAMETER OutputFile
    Classified results output file (default: classified_results.json)
    
.PARAMETER ConfidenceThreshold
    Minimum confidence for automated classification (default: 60)
    
.EXAMPLE
    .\Smart-Classification.ps1 -ScanResultsFile "enhanced_scan_results.json" -OutputFile "classified.json"
#>

param(
    [Parameter(Mandatory=$true)]
    [string]$ScanResultsFile,
    
    [Parameter(Mandatory=$false)]
    [string]$OutputFile = "classified_results.json",
    
    [Parameter(Mandatory=$false)]
    [int]$ConfidenceThreshold = 60
)

# Classification rules priority
$CLASSIFICATION_RULES = @(
    @{
        Name = "CRITICAL-WRITE-DISCOUNT"
        Priority = 1
        Category = "CRITICAL-WRITE"
        Action = "MUST change branchno to 0 in INSERT/UPDATE"
        CPR_Phase = "Phase II"
        Confidence = 95
        Patterns = @(
            "INSERT\s+INTO\s+(discount|discountgrp|cstdiscountcont|discountgrpmem)",
            "UPDATE\s+(discount|discountgrp|cstdiscountcont|discountgrpmem)\s+SET"
        )
        RequiresSQLContext = $true
    },
    @{
        Name = "CRITICAL-READ-DISCOUNT-WHERE"
        Priority = 2
        Category = "CRITICAL-READ"
        Action = "MUST change WHERE branchno = X to branchno = 0"
        CPR_Phase = "Phase II"
        Confidence = 90
        Patterns = @(
            "WHERE\s+.*(discount|discountgrp|cstdiscountcont).*\.branchno\s*=",
            "WHERE\s+branchno\s*=.*FROM\s+(discount|discountgrp)"
        )
        RequiresSQLContext = $true
    },
    @{
        Name = "CRITICAL-LOADER-HARDCODE"
        Priority = 3
        Category = "CRITICAL-LOAD"
        Action = "MUST change hardcoded branchno values to 0"
        CPR_Phase = "Phase I"
        Confidence = 95
        Patterns = @(
            "loadconditions",
            "lddiscount",
            "zdiscount"
        )
        FilePatterns = @(".sh", ".cxx", ".h")
        RequiresSQLContext = $false
    },
    @{
        Name = "PRESERVE-MULTI-BRANCH-IBT"
        Priority = 4
        Category = "PRESERVE"
        Action = "DO NOT CHANGE - Multi-branch transfer logic"
        CPR_Phase = "N/A"
        Confidence = 85
        Patterns = @(
            "ibtbranchno",
            "destbranchno",
            "sourcebranchno",
            "branchno\s*!=",
            "!=\s*branchno"
        )
        RequiresSQLContext = $false
    },
    @{
        Name = "CRITICAL-FUNCTION-PARAM-DISCOUNT"
        Priority = 5
        Category = "CRITICAL-FUNCTION"
        Action = "Review function - likely needs branchno=0 in calls"
        CPR_Phase = "Phase II"
        Confidence = 75
        Patterns = @(
            "Select.*branchno.*discount",
            "Get.*branchno.*discount",
            "Load.*branchno.*discount"
        )
        RequiresSQLContext = $false
    },
    @{
        Name = "LOW-LOGGING-DISPLAY"
        Priority = 6
        Category = "LOW"
        Action = "Review - likely logging only, minimal impact"
        CPR_Phase = "Phase III"
        Confidence = 70
        Patterns = @(
            "log|print|cout|fprintf|sprintf|cerr|std::cout",
            "toString|getString|format"
        )
        AntiPatterns = @("SELECT", "INSERT", "UPDATE", "WHERE")
        RequiresSQLContext = $false
    },
    @{
        Name = "UNCLEAR-FUNCTION-PARAMETER"
        Priority = 7
        Category = "UNCLEAR"
        Action = "MANUAL REVIEW - Analyze function call chain"
        CPR_Phase = "TBD"
        Confidence = 0
        Patterns = @(
            "void.*\(.*branchno",
            "int.*\(.*branchno",
            "short.*\(.*branchno"
        )
        RequiresSQLContext = $false
    },
    @{
        Name = "LOW-NON-DISCOUNT-TABLE"
        Priority = 8
        Category = "LOW"
        Action = "Review - non-discount table, likely not affected by CPR"
        CPR_Phase = "Phase III"
        Confidence = 65
        Patterns = @(
            "artikel(?!.*discount)",
            "customer(?!.*discount)",
            "bestellung",
            "tmpvbfilialen"
        )
        RequiresSQLContext = $true
    }
)

$script:ClassificationStats = @{
    Total = 0
    CRITICAL_WRITE = 0
    CRITICAL_READ = 0
    CRITICAL_LOAD = 0
    CRITICAL_FUNCTION = 0
    PRESERVE = 0
    LOW = 0
    UNCLEAR = 0
    HighConfidence = 0
    MediumConfidence = 0
    LowConfidence = 0
}

function Write-Progress-Info {
    param([string]$Message, [string]$Color = "Cyan")
    Write-Host "[$(Get-Date -Format 'HH:mm:ss')] $Message" -ForegroundColor $Color
}

function Test-RuleMatch {
    param(
        [object]$Match,
        [hashtable]$Rule
    )
    
    $context = $Match.full_context
    $fileName = $Match.file_name
    $analysis = $Match.analysis
    
    # Check if SQL context is required but missing
    if ($Rule.RequiresSQLContext -and -not $analysis.has_sql) {
        return $false
    }
    
    # Check file patterns if specified
    if ($Rule.FilePatterns) {
        $matchesFileType = $false
        foreach ($pattern in $Rule.FilePatterns) {
            if ($fileName -like "*$pattern") {
                $matchesFileType = $true
                break
            }
        }
        if (-not $matchesFileType) {
            return $false
        }
    }
    
    # Check anti-patterns (must NOT match)
    if ($Rule.AntiPatterns) {
        foreach ($antiPattern in $Rule.AntiPatterns) {
            if ($context -match $antiPattern) {
                return $false
            }
        }
    }
    
    # Check positive patterns
    foreach ($pattern in $Rule.Patterns) {
        if ($context -imatch $pattern) {
            return $true
        }
    }
    
    return $false
}

function Get-Additional-Context-Info {
    param([object]$Match)
    
    $info = @{
        sql_operation = "NONE"
        tables_involved = @()
        is_write_operation = $false
        is_read_operation = $false
        has_where_clause = $false
        has_join = $false
    }
    
    if ($Match.analysis.has_sql) {
        $context = $Match.full_context
        
        # Determine SQL operation type
        if ($context -match "\bINSERT\b") {
            $info.sql_operation = "INSERT"
            $info.is_write_operation = $true
        }
        elseif ($context -match "\bUPDATE\b") {
            $info.sql_operation = "UPDATE"
            $info.is_write_operation = $true
        }
        elseif ($context -match "\bDELETE\b") {
            $info.sql_operation = "DELETE"
            $info.is_write_operation = $true
        }
        elseif ($context -match "\bSELECT\b") {
            $info.sql_operation = "SELECT"
            $info.is_read_operation = $true
        }
        
        # Get tables
        $info.tables_involved = $Match.analysis.tables
        
        # Check for WHERE clause
        $info.has_where_clause = $context -match "\bWHERE\b"
        
        # Check for JOINs
        $info.has_join = $context -match "\bJOIN\b"
    }
    
    return $info
}

function Classify-BranchNoReference {
    param([object]$Match)
    
    # Apply rules in priority order
    foreach ($rule in $CLASSIFICATION_RULES | Sort-Object Priority) {
        if (Test-RuleMatch -Match $Match -Rule $rule) {
            # Get additional context information
            $contextInfo = Get-Additional-Context-Info -Match $Match
            
            # Adjust confidence based on context quality
            $adjustedConfidence = $rule.Confidence
            
            # Boost confidence for discount table matches
            if ($Match.analysis.discount_tables.Count -gt 0) {
                $adjustedConfidence = [Math]::Min(100, $adjustedConfidence + 5)
            }
            
            # Reduce confidence if context is incomplete
            if ($Match.full_context.Length -lt 100) {
                $adjustedConfidence = [Math]::Max(0, $adjustedConfidence - 10)
            }
            
            # Build classification result
            $classification = @{
                rule_matched = $rule.Name
                category = $rule.Category
                priority = $rule.Priority
                action_required = $rule.Action
                cpr_phase = $rule.CPR_Phase
                confidence = $adjustedConfidence
                requires_manual_review = ($adjustedConfidence -lt $ConfidenceThreshold)
                context_info = $contextInfo
                reasoning = Build-Classification-Reasoning -Match $Match -Rule $rule -ContextInfo $contextInfo
            }
            
            # Update statistics
            $categoryKey = $rule.Category -replace '-', '_'
            if ($script:ClassificationStats.ContainsKey($categoryKey)) {
                $script:ClassificationStats[$categoryKey]++
            }
            
            if ($adjustedConfidence -ge 80) {
                $script:ClassificationStats.HighConfidence++
            }
            elseif ($adjustedConfidence -ge 60) {
                $script:ClassificationStats.MediumConfidence++
            }
            else {
                $script:ClassificationStats.LowConfidence++
            }
            
            return $classification
        }
    }
    
    # Default: UNCLEAR
    $script:ClassificationStats.UNCLEAR++
    $script:ClassificationStats.LowConfidence++
    
    return @{
        rule_matched = "NO_RULE_MATCHED"
        category = "UNCLEAR"
        priority = 99
        action_required = "MANUAL REVIEW REQUIRED - No classification rule matched"
        cpr_phase = "TBD"
        confidence = 0
        requires_manual_review = $true
        context_info = Get-Additional-Context-Info -Match $Match
        reasoning = "No classification rule matched this reference. Manual analysis required."
    }
}

function Build-Classification-Reasoning {
    param(
        [object]$Match,
        [hashtable]$Rule,
        [hashtable]$ContextInfo
    )
    
    $reasons = @()
    
    # Rule match reason
    $reasons += "Matched rule: $($Rule.Name)"
    
    # SQL context
    if ($Match.analysis.has_sql) {
        $reasons += "SQL context detected: $($ContextInfo.sql_operation)"
    }
    
    # Table involvement
    if ($Match.analysis.discount_tables.Count -gt 0) {
        $reasons += "Involves discount table(s): $($Match.analysis.discount_tables -join ', ')"
    }
    elseif ($Match.analysis.tables.Count -gt 0) {
        $reasons += "Involves table(s): $($Match.analysis.tables -join ', ')"
    }
    
    # Multi-branch
    if ($Match.analysis.multi_branch_keywords.Count -gt 0) {
        $reasons += "Multi-branch keywords detected: $($Match.analysis.multi_branch_keywords -join ', ')"
    }
    
    # Function
    if ($Match.analysis.function_info.HasFunction) {
        $reasons += "Function signature: $($Match.analysis.function_info.FunctionName)"
    }
    
    # Context type
    $reasons += "Context type: $($Match.analysis.context_type)"
    
    return $reasons -join " | "
}

function Generate-Implementation-Recommendations {
    param([array]$ClassifiedMatches)
    
    $recommendations = @{
        critical_items = @()
        preserve_items = @()
        low_priority_items = @()
        unclear_items = @()
        implementation_order = @()
    }
    
    # Group by category
    $byCategoryGroups = $ClassifiedMatches | Group-Object { $_.classification.category }
    
    foreach ($group in $byCategoryGroups) {
        $category = $group.Name
        $items = $group.Group
        
        switch -Wildcard ($category) {
            "CRITICAL-*" {
                $recommendations.critical_items += @{
                    category = $category
                    count = $items.Count
                    files = ($items | Select-Object -ExpandProperty file_path -Unique)
                    priority = "HIGH"
                }
            }
            "PRESERVE" {
                $recommendations.preserve_items += @{
                    category = $category
                    count = $items.Count
                    files = ($items | Select-Object -ExpandProperty file_path -Unique)
                    priority = "DO-NOT-CHANGE"
                }
            }
            "LOW" {
                $recommendations.low_priority_items += @{
                    category = $category
                    count = $items.Count
                    files = ($items | Select-Object -ExpandProperty file_path -Unique)
                    priority = "LOW"
                }
            }
            "UNCLEAR" {
                $recommendations.unclear_items += @{
                    category = $category
                    count = $items.Count
                    files = ($items | Select-Object -ExpandProperty file_path -Unique)
                    priority = "MANUAL-REVIEW"
                }
            }
        }
    }
    
    # Define implementation order
    $recommendations.implementation_order = @(
        @{ Phase = "Phase I"; Focus = "Shell script loaders (loadconditions.sh)"; Category = "CRITICAL-LOAD" },
        @{ Phase = "Phase II-A"; Focus = "INSERT/UPDATE operations"; Category = "CRITICAL-WRITE" },
        @{ Phase = "Phase II-B"; Focus = "SELECT WHERE operations"; Category = "CRITICAL-READ" },
        @{ Phase = "Phase II-C"; Focus = "Function parameters"; Category = "CRITICAL-FUNCTION" },
        @{ Phase = "Phase III"; Focus = "Low priority items"; Category = "LOW" },
        @{ Phase = "Manual Review"; Focus = "Unclear items"; Category = "UNCLEAR" }
    )
    
    return $recommendations
}

#region Main Execution

Write-Progress-Info "========================================" "Green"
Write-Progress-Info "SMART BRANCHNO CLASSIFICATION - CPR0003319" "Green"
Write-Progress-Info "========================================" "Green"
Write-Progress-Info ""

# Validate input file
if (-not (Test-Path -Path $ScanResultsFile)) {
    Write-Host "ERROR: Scan results file not found: $ScanResultsFile" -ForegroundColor Red
    exit 1
}

Write-Progress-Info "Loading scan results from: $ScanResultsFile" "Yellow"
$scanData = Get-Content -Path $ScanResultsFile -Raw | ConvertFrom-Json

Write-Progress-Info "Total matches to classify: $($scanData.matches.Count)" "Cyan"
Write-Progress-Info "Confidence threshold: $ConfidenceThreshold%" "Cyan"
Write-Progress-Info ""

# Classify all matches
Write-Progress-Info "Classifying references..." "Yellow"
$classifiedMatches = @()
$progressCounter = 0

foreach ($match in $scanData.matches) {
    $progressCounter++
    $script:ClassificationStats.Total++
    
    if ($progressCounter % 50 -eq 0) {
        Write-Progress-Info "  Classified: $progressCounter/$($scanData.matches.Count)"
    }
    
    $classification = Classify-BranchNoReference -Match $match
    
    # Combine original match with classification
    $classifiedMatch = $match | ConvertTo-Json -Depth 10 | ConvertFrom-Json
    $classifiedMatch | Add-Member -NotePropertyName "classification" -NotePropertyValue $classification
    
    $classifiedMatches += $classifiedMatch
}

Write-Progress-Info ""
Write-Progress-Info "Classification complete!" "Green"
Write-Progress-Info ""

# Generate recommendations
Write-Progress-Info "Generating implementation recommendations..." "Yellow"
$recommendations = Generate-Implementation-Recommendations -ClassifiedMatches $classifiedMatches

# Build output structure
$output = @{
    metadata = @{
        classification_date = (Get-Date -Format "o")
        source_scan_file = $ScanResultsFile
        classifier_version = "1.0-SMART"
        confidence_threshold = $ConfidenceThreshold
        total_rules = $CLASSIFICATION_RULES.Count
    }
    statistics = $script:ClassificationStats
    recommendations = $recommendations
    classified_matches = $classifiedMatches
}

# Save results
Write-Progress-Info "Saving classified results to: $OutputFile" "Yellow"
$output | ConvertTo-Json -Depth 15 | Set-Content -Path $OutputFile -Encoding UTF8

# Display summary
Write-Progress-Info ""
Write-Progress-Info "========================================" "Green"
Write-Progress-Info "CLASSIFICATION STATISTICS" "Green"
Write-Progress-Info "========================================" "Green"
Write-Progress-Info "Total References:         $($script:ClassificationStats.Total)"
Write-Progress-Info ""
Write-Progress-Info "By Category:" "Yellow"
Write-Progress-Info "  CRITICAL-WRITE:         $($script:ClassificationStats.CRITICAL_WRITE)" "Red"
Write-Progress-Info "  CRITICAL-READ:          $($script:ClassificationStats.CRITICAL_READ)" "Red"
Write-Progress-Info "  CRITICAL-LOAD:          $($script:ClassificationStats.CRITICAL_LOAD)" "Red"
Write-Progress-Info "  CRITICAL-FUNCTION:      $($script:ClassificationStats.CRITICAL_FUNCTION)" "Red"
Write-Progress-Info "  PRESERVE:               $($script:ClassificationStats.PRESERVE)" "Magenta"
Write-Progress-Info "  LOW:                    $($script:ClassificationStats.LOW)" "Green"
Write-Progress-Info "  UNCLEAR:                $($script:ClassificationStats.UNCLEAR)" "Gray"
Write-Progress-Info ""
Write-Progress-Info "By Confidence:" "Yellow"
Write-Progress-Info "  High (>=80%):           $($script:ClassificationStats.HighConfidence)" "Green"
Write-Progress-Info "  Medium (60-79%):        $($script:ClassificationStats.MediumConfidence)" "Yellow"
Write-Progress-Info "  Low (<60%):             $($script:ClassificationStats.LowConfidence)" "Red"
Write-Progress-Info ""

# Calculate success metrics
$criticalCount = $script:ClassificationStats.CRITICAL_WRITE + $script:ClassificationStats.CRITICAL_READ + $script:ClassificationStats.CRITICAL_LOAD
$automatedRate = [math]::Round((1 - ($script:ClassificationStats.UNCLEAR / $script:ClassificationStats.Total)) * 100, 1)

Write-Progress-Info "Quality Metrics:" "Yellow"
Write-Progress-Info "  Critical Items Found:   $criticalCount"
Write-Progress-Info "  Automated Classification: $automatedRate%"
Write-Progress-Info "  Manual Review Required: $($script:ClassificationStats.UNCLEAR) items"
Write-Progress-Info ""
Write-Progress-Info "Results saved to: $OutputFile" "Green"
Write-Progress-Info "========================================" "Green"

#endregion
