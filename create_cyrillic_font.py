from PIL import Image, ImageDraw, ImageFont
import os

def create_cyrillic_font():
    # Размер одного символа
    CHAR_WIDTH = 20
    CHAR_HEIGHT = 20
    
    # Список кириллических символов в том же порядке, как в таблице символов
    cyrillic_chars = [
        "абвгдеёжзи",
        "йклмнопрст",
        "уфхцчшщъыь",
        "эюяАБВГДЕЁ",
        "ЖЗИЙКЛМНОП",
        "РСТУФХЦЧШЩ",
        "ЪЫЬЭЮЯ"
    ]
    
    # Вычисляем размеры изображения
    total_width = CHAR_WIDTH * 10  # 10 символов в строке
    total_height = CHAR_HEIGHT * len(cyrillic_chars)
    
    # Создаем новое изображение с черным фоном
    image = Image.new('RGB', (total_width, total_height), 'black')
    draw = ImageDraw.Draw(image)
    
    # Пытаемся загрузить шрифт, если не получается - используем дефолтный
    try:
        font = ImageFont.truetype("arial.ttf", CHAR_HEIGHT - 4)
    except:
        font = ImageFont.load_default()
    
    # Рисуем каждый символ по центру клетки
    for row_idx, row in enumerate(cyrillic_chars):
        for col_idx, char in enumerate(row):
            x = col_idx * CHAR_WIDTH
            y = row_idx * CHAR_HEIGHT
            # Получаем размер символа
            bbox = draw.textbbox((0, 0), char, font=font)
            w = bbox[2] - bbox[0]
            h = bbox[3] - bbox[1]
            # Центрируем
            cx = x + (CHAR_WIDTH - w) // 2
            cy = y + (CHAR_HEIGHT - h) // 2
            draw.text((cx, cy), char, fill='white', font=font)
    
    # Сохраняем изображение в формате BMP
    image.save('cyrillic.bmp')
    print(f"Файл cyrillic.bmp создан успешно!")
    print(f"Размер: {total_width}x{total_height} пикселей")

if __name__ == "__main__":
    create_cyrillic_font() 