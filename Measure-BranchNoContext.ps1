<#
.SYNOPSIS
    Intelligent BranchNo Context Classifier.
.DESCRIPTION
    Analyzes scan results and classifies usage based on context keywords.
#>
param (
    [string]$InputFile = "scan_results.json",
    [string]$OutputFile = "classified_results.json"
)

if (-not (Test-Path $InputFile)) {
    Write-Error "Input file $InputFile not found."
    exit 1
}

$ScanData = Get-Content -Path $InputFile -Raw | ConvertFrom-Json
$ClassifiedData = @()

$Stats = @{
    DISCOUNT_LOOKUP = 0
    OPERATIONAL     = 0
    MIXED           = 0
    UNCLEAR         = 0
}

foreach ($Item in $ScanData) {
    $Text = $Item.matched_text.ToLower()
    $Context = ($Item.context_before + $Item.context_after).ToLower()
    $FullBlock = "$Text $Context"
    
    $ScoreDiscount = 0
    $ScoreOperational = 0
    
    # --- Scoring Logic ---
    
    # Discount Indicators
    if ($FullBlock -match "(discount|discountgrp|cstdiscountcont)") { $ScoreDiscount += 50 }
    if ($FullBlock -match "(select.*from.*discount)") { $ScoreDiscount += 40 }
    if ($FullBlock -match "(pricesanddiscounts)") { $ScoreDiscount += 30 }
    if ($Text -match "where" -and $Text -match "branchno") { $ScoreDiscount += 20 }
    
    # Operational Indicators
    if ($FullBlock -match "(order|customer|delivery|shipment)") { $ScoreOperational += 30 }
    if ($Text -match "(log|print|printf|write-host|console)") { $ScoreOperational += 50 }
    if ($FullBlock -match "(report|analytics)") { $ScoreOperational += 40 }
    if ($FullBlock -match "insert into orders") { $ScoreOperational += 100 }
    
    # Classification
    $Classification = "UNCLEAR"
    $Confidence = 0
    
    if ($ScoreDiscount -gt 80 -and $ScoreOperational -lt 30) {
        $Classification = "DISCOUNT_LOOKUP"
        $Confidence = [Math]::Min($ScoreDiscount, 100)
    }
    elseif ($ScoreOperational -gt 80 -and $ScoreDiscount -lt 30) {
        $Classification = "OPERATIONAL"
        $Confidence = [Math]::Min($ScoreOperational, 100)
    }
    elseif ($ScoreDiscount -gt 40 -and $ScoreOperational -gt 40) {
        $Classification = "MIXED"
        $Confidence = 50
    }
    
    $Stats[$Classification]++
    
    # Add properties to object
    $Item | Add-Member -MemberType NoteProperty -Name "classification" -Value $Classification
    $Item | Add-Member -MemberType NoteProperty -Name "confidence" -Value $Confidence
    $Item | Add-Member -MemberType NoteProperty -Name "manual_review_required" -Value (($Confidence -lt 70) -or ($Classification -eq "MIXED"))
    
    $ClassifiedData += $Item
}

$ClassifiedData | ConvertTo-Json -Depth 5 | Out-File -FilePath $OutputFile -Encoding UTF8

Write-Host "Classification Complete:" -ForegroundColor Green
$Stats.GetEnumerator() | Format-Table -AutoSize