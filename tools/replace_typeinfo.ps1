$root=git rev-parse --show-toplevel 2>$null
if ($LASTEXITCODE -ne 0) { Write-Host "Not a git repo"; exit 1 }
$files = Get-ChildItem -Path $root -Recurse -Include *.h,*.hpp,*.cpp -ErrorAction SilentlyContinue
foreach ($f in $files) {
    $t = Get-Content -Path $f.FullName -Raw
    if ($t -match '<typeinfo.h>') {
        $new = $t -replace '<typeinfo.h>','<typeinfo>'
        Copy-Item $f.FullName ($f.FullName + '.bak') -Force
        Set-Content -Path $f.FullName -Value $new -Encoding UTF8
        Write-Host "Patched: $($f.FullName)"
    }
}
Write-Host "Done"