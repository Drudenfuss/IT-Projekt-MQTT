/*
   MQTT-Controller

   Test Software


   Hardeware:
   
   WeMos D1 Mini ESP 8266
   BH1750 I2C Luxmeter
   PIR Bewegungsmelder
   10x RGB LED WS2811

   Lutz Ackermann
   BZTG Oldenburg ETS 1

   04.10.2018 V 1.0a
   12.10.2018 V 1.1  Release

   www.github.com/drudenfuss

   License: GNU GPLv3

   Verwendete Biblotheken:

   Adafruit_Neopixel.h    RGB LED Ansteuerung
   Wire.h                 I2C Bus
   BH1750.h ^             Lux-Meter

*/

#include <Adafruit_NeoPixel.h>                                                  // Einbindung Biblothek WS2811 RGB LED
#include <Wire.h>                                                               // Einbindung I2C Buskommunikation
#include <BH1750.h>                                                             // Einbindung Biblothek BH1750 Luxmeter

float lux = 0;                                                                  // Varriable Beleuchtungsstärke
int i = 0;
bool pir = false;                                                               // PIR Bewegungsmelder Merker
const unsigned NLEDS = 10;                                                      // Anzahl LED´s

BH1750 lightMeter;                                                              // BH 1750 Luxmeter Setup
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NLEDS, D7, NEO_RGB + NEO_KHZ800);  // RGB WS2811 Setup

void setup()
{
  pinMode(D6, INPUT);                                                               // PIR Bewegungsmelder, Pull up
  Wire.begin ();
  pixels.begin();                                                                   // Initialisierung RGB LEDs
  lightMeter.begin();                                                               // Initialisierung Luxmeter
  Serial.begin(9600);
}
void loop()
{
  pir = digitalRead(D6);
  Serial.println(pir);

  if (pir == false)
  {
    lux = lightMeter.readLightLevel();                    // Auslesen Lux-Wert
    Serial.println(lux);
    delay (140);                                          // Abfragezeit Luxmeter mindestens 120 ms Zyklus
    uint8_t c = i + (lux / 7);
    Serial.println(c);
    delay (0);
    for (int k = 0; k < NLEDS; k++)                       // Ansteuerungs Schleife  RGB LED´s mit Lux Offset
    {
      pixels.setPixelColor(k, pixels.Color(c, c, c));
      pixels.show();
    }
  }
  if (pir == true)
  {
    for (int k = 0; k < NLEDS; k++)                      // Abschaltungs Schleife RGB LED´s durch PIR
    {
      pixels.setPixelColor(k, pixels.Color(0, 0, 0));
      pixels.show();
    }
  }
}

