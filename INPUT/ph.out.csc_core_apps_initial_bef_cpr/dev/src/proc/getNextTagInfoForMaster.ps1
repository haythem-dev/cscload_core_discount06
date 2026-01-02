#**********************************************************#
#                                                          #
# Extract the version number from ivy.xml and return the   #
# name of the next tag on the master branch. The script    #
# should be called after successful merge of the pull      #
# request into master.                                     #
#                                                          #
# Author: D.Kondratyev                                     #
# Date:   18.12.2024                                       #
#                                                          #
#**********************************************************#

# Construct the path to the ivy.xml file relative to the script's location
$ivyXmlPath = Join-Path -Path $PSScriptRoot -ChildPath "..\ivy.xml"

# Load the ivy.xml file and cast the content to an XML data type
[xml]$xml = Get-Content -Path $ivyXmlPath

# Navigate to the info element and extract the module attribute value
$IVY_MODULE_NAME = $xml.SelectSingleNode("//info").module

# Navigate to the info element and extract the revision attribute value
$revision = $xml.SelectSingleNode("//info").revision

# Use regex to extract the version number before the hyphen
if ($revision -match "(\d+\.\d+\.\d+\.\d+)-")
{
    $IVY_CURRENT_VERSION = $matches[1]
}

# Get the list of tags and filter those that match the expected pattern
$tags = git tag | Where-Object { $_ -match "^rel\d+_" }

# Find the last tag that matches the pattern
$lastTag = $tags | Sort-Object | Select-Object -Last 1

# Extract the numerical part of the tag and define the next release number
if ($lastTag -match "^rel(\d+)_")
{
    $TAG_REL_NUMBER = [int]$matches[1]
    $TAG_REL_NUMBER++
}
else
{
    # No matching tags found or tag format is incorrect. Starting with 1.
    $TAG_REL_NUMBER = 1
}

# Get the current date in the format YYYYMMDD
$currentDate = Get-Date -Format "yyyyMMdd"

# Format the release number to be zero-padded to 4 digits
$formattedReleaseNumber = $TAG_REL_NUMBER.ToString("D4")

# Construct the final tag name
$TAG_NAME = "rel{0}_{1}_{2}" -f $formattedReleaseNumber, $currentDate, $IVY_CURRENT_VERSION

$comment = "Tagging release version $IVY_CURRENT_VERSION of $IVY_MODULE_NAME"

# Create a JSON object
$jsonOutput = @{
    TagName = $TAG_NAME
    Comment = $comment
} | ConvertTo-Json -Compress

# Set the JSON output as a pipeline variable
Write-Output "##vso[task.setvariable variable=TagAndComment]$jsonOutput"
