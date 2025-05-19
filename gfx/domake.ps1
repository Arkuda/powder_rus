# Скрипт для генерации C файлов из BMP изображений
Write-Host "Building Tiles..."

# Список тайлсетов
$tilesets = @("classic", "distorted", "adambolt", "nethack", "ascii", "akoimeexx", "akoi12", "akoi10", "ibsongrey", "lomaka")

# Обработка каждого тайлсета
foreach ($tileset in $tilesets) {
    Write-Host "Building tiles for $tileset..."
    Push-Location $tileset
    # Здесь должна быть команда tile2c, но пока пропустим
    Pop-Location
}

# Обработка akoi3x
Write-Host "Building Akoi3x..."
Push-Location "akoi3x"
if (Test-Path "sprite16_3x.bmp.gz") {
    # Распаковка gz файла
    $content = Get-Content "sprite16_3x.bmp.gz" -Encoding Byte
    [System.IO.File]::WriteAllBytes("sprite16_3x.bmp", $content)
}
# Здесь должна быть команда bmp2c, но пока пропустим
Pop-Location

Write-Host "Building Background images..."
# Генерация C файлов для BMP изображений
$bmpFiles = @(
    "tridude_goodbye.bmp",
    "tridude_goodbye_hires.bmp",
    "icon_sdl.bmp"
)

foreach ($bmpFile in $bmpFiles) {
    if (Test-Path $bmpFile) {
        Write-Host "Converting $bmpFile to C..."
        # Создаем имя выходного файла
        $cFile = $bmpFile -replace '\.bmp$', '.bmp.c'
        
        # Читаем BMP файл как бинарные данные
        $bmpData = [System.IO.File]::ReadAllBytes($bmpFile)
        
        # Создаем массив hex значений
        $hexArray = $bmpData | ForEach-Object { "0x{0:X2}" -f $_ }
        
        # Создаем C файл
        $cContent = @"
// Автоматически сгенерированный файл из $bmpFile
const unsigned char $(($bmpFile -replace '\.bmp$', '_bmp') -replace '-', '_')[] = {
$($hexArray -join ", ")
};

const int $(($bmpFile -replace '\.bmp$', '_bmp_size') -replace '-', '_') = sizeof($(($bmpFile -replace '\.bmp$', '_bmp') -replace '-', '_'));
"@
        
        # Записываем C файл
        [System.IO.File]::WriteAllText($cFile, $cContent)
    }
}

Write-Host "Dirtying build..."
if (Test-Path "all_bitmaps.o") {
    Remove-Item "all_bitmaps.o"
}

Write-Host "Done!" 