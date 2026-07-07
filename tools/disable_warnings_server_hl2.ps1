$path = "game/server/server_hl2.vcxproj"
if (-not (Test-Path $path)) { Write-Host "File not found: $path"; exit 1 }
$text = Get-Content -Path $path -Raw
$bak = $path + ".bak2"
Copy-Item -Path $path -Destination $bak -Force

# Try to append 4456 and 4459 to existing DisableSpecificWarnings entries
if ($text -match '<DisableSpecificWarnings>(.*?)</DisableSpecificWarnings>') {
    $new = [regex]::Replace($text, '<DisableSpecificWarnings>(.*?)</DisableSpecificWarnings>', { param($m) $inner = $m.Groups[1].Value; if ($inner -notmatch '4456') { $inner = $inner.TrimEnd(';') + ';4456' } if ($inner -notmatch '4459') { $inner = $inner.TrimEnd(';') + ';4459' } return "<DisableSpecificWarnings>$inner</DisableSpecificWarnings>" }, 'Singleline')
}
else {
    # Insert into first ClCompile block
    $new = [regex]::Replace($text, '(<ClCompile>)(.*?)', { param($m) return $m.Groups[1].Value + "`n      <DisableSpecificWarnings>;4316;4456;4459</DisableSpecificWarnings>" + $m.Groups[2].Value }, 'Singleline')
}

if ($new -ne $text) { Set-Content -Path $path -Value $new -Encoding UTF8; Write-Host "Patched $path -> disabled warnings 4456,4459" } else { Write-Host "No changes made" }
