param(
    [string]$MinGWBin = $(if ($env:MINGW32_BIN) { $env:MINGW32_BIN } else { 'C:\mingw32\bin' }),
    [string]$WinBGImSource = $env:WINBGIM_SOURCE_DIR
)

$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
$compiler = Join-Path $MinGWBin 'g++.exe'
$runtimeNames = @('libgcc_s_dw2-1.dll', 'libstdc++-6.dll', 'libwinpthread-1.dll')

if (-not (Test-Path -LiteralPath $compiler)) {
    throw "MinGW g++ not found: $compiler. Set MINGW32_BIN to the MinGW 32-bit bin folder."
}
if ([string]::IsNullOrWhiteSpace($WinBGImSource) -or -not (Test-Path -LiteralPath (Join-Path $WinBGImSource 'libbgi.a'))) {
    throw 'WinBGIm libbgi.a not found. Set WINBGIM_SOURCE_DIR to the folder containing libbgi.a and graphics.h.'
}
foreach ($header in @('graphics.h', 'winbgim.h')) {
    if (-not (Test-Path -LiteralPath (Join-Path $WinBGImSource $header))) {
        throw "WinBGIm header not found: $(Join-Path $WinBGImSource $header)"
    }
}

$outputDir = Join-Path $projectRoot 'build'
New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
$targets = @(
    @{ Source = 'src\ball.cpp'; Output = 'ball.exe' },
    @{ Source = 'examples\physics.cpp'; Output = 'physics.exe' }
)
$linkLibraries = @('-lbgi', '-lgdi32', '-lcomdlg32', '-luuid', '-loleaut32', '-lole32')

foreach ($target in $targets) {
    $source = Join-Path $projectRoot $target.Source
    $output = Join-Path $outputDir $target.Output
    Write-Host "Building $($target.Output)..."
    $arguments = @($source, '-o', $output, '-I', $WinBGImSource, '-L', $WinBGImSource) + $linkLibraries
    & $compiler @arguments
    if ($LASTEXITCODE -ne 0) {
        throw "Build failed for $($target.Source) (exit code $LASTEXITCODE)."
    }
}

foreach ($runtime in $runtimeNames) {
    $source = Join-Path $MinGWBin $runtime
    if (-not (Test-Path -LiteralPath $source)) {
        throw "Required MinGW runtime DLL not found: $source"
    }
    Copy-Item -LiteralPath $source -Destination $outputDir -Force
}

Write-Host "Build complete. Executables and runtime DLLs are in: $outputDir"
