<#
.Auto: Force-accept "ours" for conflicted files matching generated/binary patterns and stage them.
Usage: run from repo root:
  powershell -ExecutionPolicy Bypass -File .\tools\force_accept_ours.ps1 [-Continue]

If -Continue is supplied and no manual conflicts remain, the script will run `git rebase --continue`.

Caveat: This forcibly accepts the local branch version for matched files. Use only for generated/binary files.
#>
param(
    [switch]$Continue
)

function Write-Err([string]$m){ Write-Host $m -ForegroundColor Red }
function Write-Ok([string]$m){ Write-Host $m -ForegroundColor Green }

$top = git rev-parse --show-toplevel 2>$null
if ($LASTEXITCODE -ne 0) { Write-Err "Not a git repository."; exit 1 }

Write-Host "Collecting unmerged files..."
$conflicts = git diff --name-only --diff-filter=U
if (-not $conflicts) { Write-Ok "No conflicts found."; exit 0 }

$files = $conflicts -split "`n" | ForEach-Object { $_.Trim() } | Where-Object { $_ -ne '' }

# Patterns to auto-accept (adjust if needed)
$patterns = @(
    '\\Release\\', '/Release/', '\\Debug\\', '/Debug/', '\\bin\\', '/bin/', '\.lib$', '\.dll$', '\.exe$', '\.pdb$', '\.so$', '\.dylib$', '\.vcxproj\.vpc_crc$', '\.vcxproj$', '\.filters$'
)

$auto = @()
$manual = @()
foreach ($f in $files) {
    $match = $false
    foreach ($p in $patterns) {
        if ($f -match $p) { $match = $true; break }
    }
    if ($match) {
        Write-Host "Attempting to accept OURS for: $f"
        git checkout --ours -- "$f" 2>$null
        if ($LASTEXITCODE -ne 0) {
            Write-Warning "  'git checkout --ours' failed for $f; trying --theirs"
            git checkout --theirs -- "$f" 2>$null
            if ($LASTEXITCODE -ne 0) {
                Write-Err "  Both checkout attempts failed for $f"
                $manual += $f
                continue
            }
        }
        git add -- "$f"
        if ($LASTEXITCODE -ne 0) {
            Write-Err "  git add failed for $f"
            $manual += $f
            continue
        }
        $auto += $f
    }
    else {
        $manual += $f
    }
}

Write-Ok ("Auto-accepted files: {0}" -f $auto.Count)
if ($auto.Count -gt 0) { $auto | ForEach-Object { Write-Host "  $_" } }

if ($manual.Count -gt 0) {
    Write-Err ("Files left for manual resolution: {0}" -f $manual.Count)
    $manual | ForEach-Object { Write-Host "  $_" }
    Write-Host "Resolve manually, git add <file>, then run 'git rebase --continue' or 'git merge --continue'."
    exit 2
}
else {
    Write-Ok "All conflicts auto-resolved and staged."
    if ($Continue) {
        Write-Host "Running 'git rebase --continue'..."
        git rebase --continue
        exit $LASTEXITCODE
    }
    else {
        Write-Host "Run 'git rebase --continue' (or 'git merge --continue') to proceed."
        exit 0
    }
}
