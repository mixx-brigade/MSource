$p='game/server/server_hl2.vcxproj'
if (-not (Test-Path $p)) { Write-Host "Missing $p"; exit 1 }
$t = Get-Content -Path $p -Raw
$bak = $p + '.twae_true.bak'
Copy-Item $p $bak -Force
$t2 = $t -replace '<TreatWarningAsError>\s*false\s*</TreatWarningAsError>','<TreatWarningAsError>true</TreatWarningAsError>'
if ($t2 -ne $t) { Set-Content -Path $p -Value $t2 -Encoding UTF8; Write-Host 'Patched to true' } else { Write-Host 'No change' }