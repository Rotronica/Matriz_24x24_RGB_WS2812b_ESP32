from PIL import Image
import numpy as np

# Carga y redimensiona la imagen a 24x24 píxeles
imagen = Image.open("Escarapela_en_acuarela.png").convert('RGB')
imagen = imagen.resize((24, 24))

# Convierte cada píxel a código FastLED
for y in range(24):
    for x in range(24):
        r, g, b = imagen.getpixel((x, y))
        print(f"leds[getPixelIndex({x}, {y})] = CRGB({r}, {g}, {b});")