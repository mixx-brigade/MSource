$path = "game/server/server_hl2.vcxproj"
if (-not (Test-Path $path)) { Write-Host "File not found: $path"; exit 1 }
$text = Get-Content -Path $path -Raw
$bak = $path + ".bak"
Copy-Item -Path $path -Destination $bak -Force
$new = $text -replace '<PrecompiledHeader>Use</PrecompiledHeader>','<PrecompiledHeader>NotUsing</PrecompiledHeader>'
if ($new -ne $text) { Set-Content -Path $path -Value $new -Encoding UTF8; Write-Host "Updated $path and backed up to $bak" } else { Write-Host "No changes made to $path" }
