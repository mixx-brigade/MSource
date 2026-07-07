$path = "game/server/server_hl2.vcxproj"
if (-not (Test-Path $path)) { Write-Host "File not found: $path"; exit 1 }
$text = Get-Content -Path $path -Raw
$bak = $path + ".pch.bak"
Copy-Item -Path $path -Destination $bak -Force
$new = $text -replace '<PrecompiledHeader>NotUsing</PrecompiledHeader>','<PrecompiledHeader>Use</PrecompiledHeader>'
if ($new -ne $text) { Set-Content -Path $path -Value $new -Encoding UTF8; Write-Host "Updated $path (backup: $bak)" } else { Write-Host "No changes made" }
