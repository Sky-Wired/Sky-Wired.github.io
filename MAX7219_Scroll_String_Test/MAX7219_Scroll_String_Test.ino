#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#include <SPI.h>
// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 8
#define CS_PIN 3

// Create a new instance of the MD_Parola class with hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


String hi = "HELLO";
const char *strHi = hi.c_str();

void setup(void)
{
  myDisplay.begin();
 // myDisplay.displayText(strHi, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
 myDisplay.displayScroll(strHi, PA_CENTER, PA_SCROLL_LEFT, 100);
}

void loop(void)
{
  myDisplay.displayAnimate();
}
