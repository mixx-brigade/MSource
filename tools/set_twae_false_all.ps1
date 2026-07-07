$p='game/server/server_hl2.vcxproj'
$t=Get-Content -Path $p -Raw
$bak=$p+'.bak5'
Copy-Item $p $bak -Force
$t2=$t -replace '<TreatWarningAsError>\s*true\s*</TreatWarningAsError>','<TreatWarningAsError>false</TreatWarningAsError>'
if($t2 -ne $t){ Set-Content -Path $p -Value $t2 -Encoding UTF8; Write-Host 'Patched all occurrences'; } else { Write-Host 'No occurrences found'; }
