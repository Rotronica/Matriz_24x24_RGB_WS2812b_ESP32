 #include <FastLED.h>
#include "escarapela.h"
#include "bandera.h"
#include "escudo.h"
#include "mensaje.h"
#include <pgmspace.h>

#define LED_PIN     2      // Pin de datos GPIO_2
#define NUM_LEDS    576    // 24x24 = 576 LEDs
#define BRIGHTNESS  40    // Brillo (0-255)

CRGB leds[NUM_LEDS];

// Colores escarapela (en formato 0xRRGGBB)
const uint32_t COLOR_ROJO = 0x00FF0000;
const uint32_t COLOR_AMARILLO = 0x00FFFF00;
const uint32_t COLOR_VERDE = 0x00006000;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(115200);
}

void loop() {
  // SECUENCIA COMPLETA
  
  // 1. ESCARAPELA - Animación por colores y parpadeo 3 veces
  mostrarEscarapela();
  
  // 2. BANDERA - Animación por colores y parpadeo 3 veces
  mostrarBandera();
  
  // 3. ESCUDO - Solo parpadeo 4 veces
  mostrarEscudo();
  
  // 4. MENSAJE - Scroll de izquierda a derecha 3 veces
  mostrarMensaje();
  
  // Pausa antes de repetir todo el ciclo
  delay(2000);
}

// ===== FUNCIONES PARA ESCARAPELA =====
void mostrarEscarapela() {
  // Apagar todos los LEDs
  FastLED.clear();
  FastLED.show();
  delay(500);
  
  // Animación por colores
  animarColor(ledarray0, COLOR_ROJO, 10);
  animarColor(ledarray0, COLOR_AMARILLO, 10);
  animarColor(ledarray0, COLOR_VERDE, 10);
  
  // Parpadeo 3 veces
  parpadearImagen(ledarray0, 3, 1000);   //parpadearImagen(ledarray0, veces_parpadeo, duracion);
}

// ===== FUNCIONES PARA BANDERA =====
void mostrarBandera() {
  // Apagar todos los LEDs
  FastLED.clear();
  FastLED.show();
  delay(500);
  
  // Animación por colores de la bandera
  animarColor(ledarray1, COLOR_ROJO, 10);   //animarColor(ledarray1, COLOR_ROJO, velocidad);
  animarColor(ledarray1, COLOR_AMARILLO, 10);
  animarColor(ledarray1, COLOR_VERDE, 10);
  
  // Parpadeo 3 veces
  parpadearImagen(ledarray1, 3, 1000);
}

// ===== FUNCIONES PARA ESCUDO =====
void mostrarEscudo() {
  // Apagar todos los LEDs
  FastLED.clear();
  FastLED.show();
  delay(500);
  
  // Solo parpadeo 4 veces
  parpadearImagen(ledarray2, 4, 1000);
}

// ===== FUNCIONES PARA MENSAJE =====
void mostrarMensaje() {
  // Apagar todos los LEDs
  FastLED.clear();
  FastLED.show();
  delay(500);
  
  // Scroll de izquierda a derecha 3 veces
  scrollMensaje(3);   //scrollMensaje(veces)
}

// ===== FUNCIONES AUXILIARES =====

// Función optimizada para animar por colores
void animarColor(const uint32_t* array, uint32_t colorObjetivo, int velocidad) {
  bool huboCambio = false;
  for (int i = 0; i < NUM_LEDS; i++) {
    uint32_t colorPixel = array[i];
    if (colorPixel == colorObjetivo) {
      leds[i] = CRGB((colorPixel >> 16) & 0xFF, (colorPixel >> 8) & 0xFF, colorPixel & 0xFF);
      huboCambio = true;
    }
    // Solo mostrar cuando haya un cambio
    if (huboCambio) {
      FastLED.show();
      delay(velocidad);
      huboCambio = false;
    }
  }
  delay(300); // Pausa corta al terminar cada color
}

// Parpadea la imagen completa n veces
void parpadearImagen(const uint32_t* array, int veces, int duracion) {
  for (int v = 0; v < veces; v++) {
    // Encender la imagen
    for (int i = 0; i < NUM_LEDS; i++) {
      uint32_t colorPixel = array[i];
      leds[i] = CRGB((colorPixel >> 16) & 0xFF, (colorPixel >> 8) & 0xFF, colorPixel & 0xFF);
    }
    FastLED.show();
    delay(duracion);
    // Apagar
    FastLED.clear();
    FastLED.show();
    delay(duracion);
  }
}

// Scroll del mensaje de izquierda a derecha
void scrollMensaje(int veces) {
  const int ANCHO = 24; // Ancho de la matriz
  const int ALTO = 24;  // Alto de la matriz
  
  for (int ciclo = 0; ciclo < veces; ciclo++) {
    // Scroll de izquierda a derecha
    for (int offset = 0; offset < ANCHO; offset++) {
      FastLED.clear();
      
      // Copiar el mensaje con offset
      for (int fila = 0; fila < ALTO; fila++) {
        for (int col = 0; col < ANCHO; col++) {
          int posOriginal = fila * ANCHO + col;
          int posDestino = fila * ANCHO + (col + offset) % ANCHO;
          
          if (posDestino < NUM_LEDS) {
            uint32_t colorPixel = ledarray3[posOriginal];
            leds[posDestino] = CRGB((colorPixel >> 16) & 0xFF, (colorPixel >> 8) & 0xFF, colorPixel & 0xFF);
          }
        }
      }
      
      FastLED.show();
      delay(100); // Velocidad del scroll
    }
  }
}
