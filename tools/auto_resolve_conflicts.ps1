<#
.SYNOPSIS
  Auto-resolve git merge/rebase conflicts for generated/binary files and leave source files for manual review.

.DESCRIPTION
  Scans for unmerged files (conflicts). For files that are likely generated or binary (Release/, .lib, .dll, .pdb, .so, .dylib, etc.)
  this script checks out "--ours" and stages them, so you can continue the rebase/merge. Source files (.cpp, .h, .rc, .vpc, etc.) are left unmodified and listed for manual resolution.

  The script also attempts a `git lfs install` and `git lfs pull` at start to recover LFS-tracked files.

.PARAMETER Continue
  If specified and no manual conflicts remain, the script will automatically run `git rebase --continue`.

.EXAMPLE
  .\tools\auto_resolve_conflicts.ps1
  .\tools\auto_resolve_conflicts.ps1 -Continue
#>
[CmdletBinding()]
param(
    [switch]$Continue
)

function Write-Err([string]$m){ Write-Host $m -ForegroundColor Red }
function Write-Ok([string]$m){ Write-Host $m -ForegroundColor Green }

# Ensure we are in a git repository
$top = git rev-parse --show-toplevel 2>$null
if ($LASTEXITCODE -ne 0) {
    Write-Err "Not a git repository (run this from inside your repo)."
    exit 1
}

# Try to ensure LFS objects are present
Write-Host "Running 'git lfs install' and attempting 'git lfs pull' to fetch pointer objects (if any)..."
git lfs install 2>$null
git lfs pull 2>$null

# Get list of unmerged/conflicted files
$conflicts = git diff --name-only --diff-filter=U
if (-not $conflicts) {
    Write-Ok "No merge/rebase conflicts detected."
    exit 0
}

$conflictFiles = $conflicts -split "`n" | ForEach-Object { $_.Trim() } | Where-Object { $_ -ne '' }

# Define a conservative set of source/text extensions that we WILL NOT auto-resolve
$sourceExt = @('.c', '.cpp', '.cc', '.cxx', '.h', '.hpp', '.hxx', '.inl', '.rc', '.rc2', '.idl', '.txt', '.py', '.pl', '.cs', '.js', '.java', '.json', '.xml', '.vpc', '.sln', '.props', '.filters', '.md', '.kv', '.bat', '.ps1', '.sh', '.mk')

$autoResolved = @()
$leftManual = @()

foreach ($f in $conflictFiles) {
    # Normalize path
    $path = $f.Trim()
    if ($path -eq '') { continue }

    $ext = [IO.Path]::GetExtension($path).ToLower()

    # Heuristics: if file is under a Release/Debug path or has a binary-like extension, auto-resolve
    $isGeneratedPath = $path -match '(?i)/Release/|\\Release\\|/Debug/|\\Debug\\|/bin/|\\bin\\'
    $binaryExts = @('.lib','.dll','.exe','.pdb','.so','.dylib','.a','.lib','.o','.obj','.class')

    $isBinaryExt = $binaryExts -contains $ext

    # Treat vcxproj CRC and many generated extension patterns as auto
    $isVPCcrc = $path -match '\.vcxproj\.vpc_crc$'
    $isLargeGenerated = $path -match '\\Release_|Release_' -or $path -match '\\Release\\' -or $path -match '/Release/'

    # If extension empty (binaries sometimes have none) and path contains Release or similar, treat as binary
    if (($ext -eq '' -or $ext -eq $null) -and ($isGeneratedPath -or $isLargeGenerated)) { $isBinaryExt = $true }

    # Decide whether to auto-resolve
    if ($isBinaryExt -or $isVPCcrc -or $isGeneratedPath -or ($sourceExt -notcontains $ext)) {
        # But still avoid auto-resolving core source files accidentally: if ext is in $sourceExt, skip
        if ($sourceExt -contains $ext) {
            $leftManual += $path
            continue
        }

        Write-Host "Auto-resolving (ours) : $path"
        git checkout --ours -- "$path" 2>$null
        if ($LASTEXITCODE -ne 0) {
            Write-Err "  git checkout --ours failed for $path"
            $leftManual += $path
            continue
        }
        git add -- "$path" 2>$null
        if ($LASTEXITCODE -ne 0) {
            Write-Err "  git add failed for $path"
            $leftManual += $path
            continue
        }
        $autoResolved += $path
    }
    else {
        Write-Host "Left for manual resolve: $path"
        $leftManual += $path
    }
}

Write-Host ""
Write-Ok ("Auto-resolved files: {0}" -f $autoResolved.Count)
if ($autoResolved.Count -gt 0) { $autoResolved | ForEach-Object { Write-Host "  $_" } }

Write-Host ""
if ($leftManual.Count -gt 0) {
    Write-Err ("Files remaining for manual resolution: {0}" -f $leftManual.Count)
    $leftManual | ForEach-Object { Write-Host "  $_" }
    Write-Host "`nResolve these manually, then run: git add <file> for each, then run 'git rebase --continue' or 'git merge --continue' as appropriate."
    exit 2
}
else {
    Write-Ok "No manual-conflict files remain."
    if ($Continue) {
        Write-Host "Running 'git rebase --continue'..."
        git rebase --continue
        exit $LASTEXITCODE
    }
    else {
        Write-Host "All conflicts staged. Run 'git rebase --continue' (or 'git merge --continue') to proceed."
        exit 0
    }
}
