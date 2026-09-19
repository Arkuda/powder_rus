$ErrorActionPreference = "Stop"
Set-Location $PSScriptRoot

Write-Host "Building Tiles..."
$tilesets = @("classic", "distorted", "adambolt", "nethack", "ascii", "akoimeexx", "akoi12", "akoi10", "ibsongrey", "lomaka")
foreach ($tileset in $tilesets) {
    Write-Host "Building $tileset tiles..."
    Push-Location $tileset
    & "../../support/tile2c/tile2c.exe"
    if ($LASTEXITCODE -ne 0) { throw "tile2c failed for $tileset" }
    Pop-Location
}

Write-Host "Building Akoi3x..."
Push-Location "akoi3x"
$input = [IO.File]::OpenRead("sprite16_3x.bmp.gz")
$output = [IO.File]::Create("sprite16_3x.bmp")
try {
    $gzip = [IO.Compression.GZipStream]::new($input, [IO.Compression.CompressionMode]::Decompress)
    try { $gzip.CopyTo($output) } finally { $gzip.Dispose() }
} finally { $output.Dispose(); $input.Dispose() }
& "../../support/bmp2c/bmp2c.exe" "sprite16_3x.bmp"
if ($LASTEXITCODE -ne 0) { throw "bmp2c failed for Akoi3x" }
Pop-Location

Write-Host "Building background images..."
foreach ($bmpFile in @("tridude_goodbye.bmp", "tridude_goodbye_hires.bmp", "icon_sdl.bmp")) {
    & "../support/bmp2c/bmp2c.exe" $bmpFile
    if ($LASTEXITCODE -ne 0) { throw "bmp2c failed for $bmpFile" }
}

python ../create_cyrillic_font.py
if ($LASTEXITCODE -ne 0) { throw "Cyrillic atlas conversion failed" }
Remove-Item "all_bitmaps.o" -ErrorAction SilentlyContinue
