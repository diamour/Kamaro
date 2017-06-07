#include <Adafruit_NeoPixel.h>
#include "Richtung.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

#define TOTAL_PIXELNUMBER   200
//the group we can use together, controlling which LED is on, the size can be changed
boolean Number[TOTAL_PIXELNUMBER];
//the group we can use together, controlling which LED has which color, the size can be changed
uint32_t Pixel_Color[TOTAL_PIXELNUMBER];


//**************************************************************************************//
//Function for clearing all the pixels
//**************************************************************************************//
void clear(void)
{
  for(int i=1;i<TOTAL_PIXELNUMBER;i++)
  {
    Number[i]=false;
    Pixel_Color[i]=pixels.Color(0, 0, 0);
  }
}

//**************************************************************************************//
//Function for judging which LED is on and showing its color
//**************************************************************************************//
void refreshLED(void)
{
  for(int i=1;i<TOTAL_PIXELNUMBER;i++)
  {
    if(Number[i]==1)
    {
      pixels.setPixelColor(i, Pixel_Color[i]); 
    }
  }
}

//define a Richtung object
//start in 10th, 30 long, 3rd is the middle
Richtung ri=Richtung(10,30,3);

//**************************************************************************************//
//setup function
//**************************************************************************************//
void setup() 
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pixels.begin(); // This initializes the NeoPixel library.

  //Clear all the group
  clear();
}

//**************************************************************************************//
//main
//**************************************************************************************//
void loop() 
{
  //clear richtung Pixel
  ri.clearRichtung();
  //grad 0-360 degree, e.g.
  ri.set(50);
  
  refreshLED();
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
}



