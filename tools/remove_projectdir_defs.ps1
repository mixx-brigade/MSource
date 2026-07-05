# Remove hardcoded PROJECTDIR=... preprocessor definitions from generated project files
$root = git rev-parse --show-toplevel 2>$null
if ($LASTEXITCODE -ne 0) { Write-Host "Not in a git repo"; exit 1 }
$files = Get-ChildItem -Path $root -Recurse -Include *.vcxproj,*.vcxproj.vpc_crc,*.vcxproj.filters,*.props -ErrorAction SilentlyContinue
if (-not $files) { Write-Host "No project files found"; exit 0 }
foreach ($f in $files) {
    $path = $f.FullName
    $text = Get-Content -Path $path -Raw -ErrorAction Continue
    if ($null -eq $text) { continue }
    $new = [regex]::Replace($text, 'PROJECTDIR=[^;\r\n\<\>]*;?', '', 'IgnoreCase')
    if ($new -ne $text) {
        Copy-Item -Path $path -Destination ($path + '.bak') -Force
        Set-Content -Path $path -Value $new -Encoding UTF8
        Write-Host "Patched: $path"
    }
}
Write-Host "Done. Please regenerate projects and try build."