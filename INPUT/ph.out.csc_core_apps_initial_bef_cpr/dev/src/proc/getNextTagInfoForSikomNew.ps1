#***********************************************************#
#                                                           #
# Extract the version number from ivy.xml and create the    #
# name of the next tag on the sikom-new branch. The script  #
# should be called after successful merge of the master-tag #
# into sikom-new branch                                     #
#                                                           #
# Author: D.Kondratyev                                      #
# Date:   07.01.2025                                        #
#                                                           #
#***********************************************************#

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

# Replace dots with underscores in the version number
$IVY_CURRENT_VERSION = $IVY_CURRENT_VERSION -replace '\.', '_'

# Extract the last two digits of the version number
if ($IVY_CURRENT_VERSION -match "\d+_\d+_\d+_(\d+)$")
{
    $lastTwoDigits = $matches[1]
}

# Construct the final tag name
$TAG_NAME = "UCC-UnifySikom-{0}-RC{1}" -f $IVY_CURRENT_VERSION, $lastTwoDigits

$comment = "Tagging release version $IVY_CURRENT_VERSION of $IVY_MODULE_NAME"

# Create a JSON object
$jsonOutput = @{
    TagName = $TAG_NAME
    Comment = $comment
} | ConvertTo-Json -Compress

# Set the JSON output as a pipeline variable
Write-Output "##vso[task.setvariable variable=TagAndComment]$jsonOutput"
