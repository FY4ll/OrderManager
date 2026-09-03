param(
    [string]$QtPath = $env:QT_ROOT,
    [string]$BuildDirectory = "build-windows"
)

$ErrorActionPreference = "Stop"

function Require-Command([string]$Name) {
    if (-not (Get-Command $Name -ErrorAction SilentlyContinue)) {
        throw "$Name was not found in PATH. Install it before running this script."
    }
}

Require-Command "cmake"
Require-Command "ninja"
Require-Command "makensis"

if (-not $QtPath) {
    $QtPath = Get-ChildItem "C:\Qt" -Directory -ErrorAction SilentlyContinue |
        ForEach-Object { Get-ChildItem $_.FullName -Directory -ErrorAction SilentlyContinue } |
        Where-Object { $_.Name -in @("mingw_64", "msvc2022_64") } |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1 -ExpandProperty FullName
}

if (-not $QtPath -or -not (Test-Path $QtPath)) {
    throw "Qt 6 was not found. Use -QtPath with the path to a Qt kit, for example C:\Qt\6.8.3\mingw_64."
}

$QtPath = (Resolve-Path $QtPath).Path

cmake -S . -B $BuildDirectory -G Ninja `
    "-DCMAKE_PREFIX_PATH=$QtPath" `
    -DCMAKE_BUILD_TYPE=Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cmake --build $BuildDirectory
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cpack --config "$BuildDirectory\CPackConfig.cmake" -G NSIS
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

$Installer = Join-Path (Get-Location) "OrderManager_Installer.exe"
if (-not (Test-Path $Installer)) {
    throw "CPack finished but OrderManager_Installer.exe was not created."
}

Write-Host "Installer created: $Installer"