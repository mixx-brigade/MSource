$p = "game/server/server_hl2.vcxproj"
if (-not (Test-Path $p)) { Write-Host "Missing $p"; exit 1 }
$t = Get-Content -Path $p -Raw
$t2 = $t -replace '<TreatWarningAsError>true</TreatWarningAsError>','<TreatWarningAsError>false</TreatWarningAsError>'
if ($t2 -ne $t) { Copy-Item $p ($p + '.bak4') -Force; Set-Content -Path $p -Value $t2 -Encoding UTF8; Write-Host 'Updated file' } else { Write-Host 'No changes' }
