$p='game/server/server_hl2.vcxproj'
$t=Get-Content -Path $p -Raw
$needle='<TreatWarningAsError>true</TreatWarningAsError>'
$idx = $t.IndexOf($needle)
if ($idx -ge 0) {
    $t2 = $t.Substring(0,$idx) + '<TreatWarningAsError>false</TreatWarningAsError>' + $t.Substring($idx + $needle.Length)
    Copy-Item $p ($p + '.bak6') -Force
    Set-Content -Path $p -Value $t2 -Encoding UTF8
    Write-Host 'Replaced first occurrence'
} else { Write-Host 'Needle not found' }
