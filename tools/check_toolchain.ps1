# Check MSVC toolchain availability and standard includes
Write-Host "Checking for MSVC cl.exe..."
$cl = (& where.exe cl.exe) 2>$null
if ($LASTEXITCODE -ne 0) { Write-Host "cl.exe not found on PATH."; exit 1 }
Write-Host "cl.exe found at: $cl"
# Try to get include paths via 'cl /E /nologo /Bv' is not available; instead check VCToolsInstallDir env
if ($env:VCToolsInstallDir) { Write-Host "VCToolsInstallDir: $env:VCToolsInstallDir" }
else { Write-Host "VCToolsInstallDir not set; you should run from 'Developer Command Prompt for VS 2022'" }
# Create a temporary test file
$tmp = Join-Path $env:TEMP "msvc_header_test.cpp"
$code = @'
#include <typeinfo>
#include <iostream>
int main(){ std::cout<<"ok"; return 0; }
'@
$code | Out-File -FilePath $tmp -Encoding ascii
Write-Host "Compiling test file: $tmp"
& cl.exe /nologo /EHsc $tmp > $env:TEMP\msvc_test_out.txt 2>&1
$rc = $LASTEXITCODE
Get-Content $env:TEMP\msvc_test_out.txt | Write-Host
if ($rc -ne 0) { Write-Host "Compilation failed (exit $rc). Check above output."; exit $rc }
Write-Host "Compilation succeeded. Toolchain appears functional."; exit 0