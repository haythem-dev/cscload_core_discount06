
param(
[string]$module_filename,
[string]$ivy_filename)

$server="zdev21";
$user="devuser";
$pass="phosix+";
#fingerprint - putty seems to use ecdsa
$zdev21_fingerprint1="9a:5a:a7:99:e2:69:93:fd:43:d1:5e:ad:1e:ac:d7:8e";  #denu1uazdev21 (ED25519) 256 MD5 on 22.01.2020
$zdev21_fingerprint2="d9:af:2d:bc:94:02:17:a7:19:e1:48:bf:d1:24:dc:b1";  #denu2uazdev21 (ED25519) 256 MD5 on 22.01.2020

#get version
$version = (Select-String -Path $ivy_filename -Pattern 'revision="(.+)-\$\{platform\}"').Matches.Groups[1].Value
#get module name
$module_split = $module_filename.Split(".");
$module_name = $module_split[0];

Write-Host "uploading file $module_filename..."
scp $module_filename "$user@${server}:/software/wss/release/${module_name}_$version.tar.gz"
Write-Host "extracting file..."
plink $user@$server -pw $pass -batch -hostkey $zdev21_fingerprint1 -hostkey $zdev21_fingerprint2 "mkdir -p /software/wss/release/$module_name/$version; /opt/freeware/bin/tar xzf /software/wss/release/${module_name}_$version.tar.gz -C /software/wss/release/$module_name/$version; chmod -R 0777 /software/wss/release/$module_name/$version; rm /software/wss/release/${module_name}_$version.tar.gz"
#making duplicate of cscservice.bin to cscservice70 to 77.bin
$arr = 70, 71, 72, 73, 74, 75, 76, 77
foreach ($n in $arr)
{
plink $user@$server -pw $pass -batch -hostkey $zdev21_fingerprint1 -hostkey $zdev21_fingerprint2 "cp /software/wss/release/$module_name/$version/server/bin/release/cscservice.bin /software/wss/release/$module_name/$version/server/bin/release/cscservice$n.bin"
}