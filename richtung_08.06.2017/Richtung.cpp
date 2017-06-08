#include "Richtung.h"

//**************************************************************************************//
//Richtung initial construction function
//Recontruction
//**************************************************************************************//
Richtung::Richtung(char v_startPixel,char v_pixelLang,char v_middlePixel)
{
  //set which area of LED richtung can use
  startPixel=v_startPixel;
  //how many LED richtung uses
  pixelLang=v_pixelLang;
  //the richtung LED is a circle, which one is the forward direction
  middlePixel=v_middlePixel;
}

//**************************************************************************************//
//Richtung initial construction function
//Contruction
//**************************************************************************************//
Richtung::Richtung()
{
  //if richtung LED start in first pixel
  startPixel=0;
  //richtung uses 30 LEDs
  pixelLang=30;
  //the third LED is the forward direction
  middlePixel=3;
}
Richtung::~Richtung()
{
}
//**************************************************************************************//
//Richtung set function
//Val: v_grad 0-360 degree
//**************************************************************************************//
void Richtung::set(int v_grad)
{
  int grad_wechsel=0;
  int lenkung_mid=0;
  int lenkung_vor=0;
  int lenkung_nach=0;

  grad=v_grad;

  //convert grad to the which LED
  grad_wechsel=grad*pixelLang/255;
  
  //turn on the 3 Pixel, the middle one is the richtung. to make it brighter. it is a circle
  lenkung_mid=middlePixel+grad_wechsel;
  lenkung_vor=lenkung_mid-1;
  lenkung_nach=lenkung_mid+1;
  
  //cause it is a circle
  lenkung_mid=convert(lenkung_mid);
  lenkung_vor=convert(lenkung_vor);
  lenkung_nach=convert(lenkung_nach);
  
  //turn the 3 LED on
  Number[startPixel+lenkung_mid]=1;
  Number[startPixel+lenkung_vor]=1;
  Number[startPixel+lenkung_nach]=1;
  
  //set the 3 LED's colour
  Pixel_Color[startPixel+lenkung_mid]=RICHTUNGFARBE;
  Pixel_Color[startPixel+lenkung_vor]=RICHTUNGFARBE;
  Pixel_Color[startPixel+lenkung_nach]=RICHTUNGFARBE;
}

//**************************************************************************************//
//clear richtung area of LED
//**************************************************************************************//
void Richtung::clearRichtung(void)
{
  for(int i=1;i<pixelLang;i++)
  {
    Number[i+startPixel]=false;
    Pixel_Color[i]=pixels.Color(0, 0, 0);
  }
}

//cause it is a circle,should be changed when knows communication way
int Richtung::convert(int v_in)
{
  if(v_in<0) return (v_in+pixelLang);
  if(v_in>=pixelLang) return (v_in-pixelLang);
}
