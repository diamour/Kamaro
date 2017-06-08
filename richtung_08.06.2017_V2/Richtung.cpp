#include "Richtung.h"

//**************************************************************************************//
//Richtung initial construction function
//Recontruction
//**************************************************************************************//
Richtung::Richtung(char v_startPixel,char v_pixelLang)
{
  //set which area of LED richtung can use
  startPixel=v_startPixel;
  //how many LED richtung uses
  pixelLang=v_pixelLang;
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
  pixelLang=5;
}
Richtung::~Richtung()
{
}
//**************************************************************************************//
//Richtung set function
//Val: v_grad 0-360 degree
//**************************************************************************************//
void Richtung::set(char c_richtung)
{
  int grad_wechsel=0;
  int lenkung_mid=0;
  int lenkung_vor=0;
  int lenkung_nach=0;

  switch(c_richtung)
  {
    case STRAIGHT:turn_on(0);
    case STRAIGHT_LEFT:turn_on(5*lenkung_mid);
    case STRAIGHT_RIGHT:turn_on(lenkung_mid);
    case BACK:turn_on(3*lenkung_mid);
    case BACK_LEFT:turn_on(4*lenkung_mid);
    case BACK_RIGHT:turn_on(2*lenkung_mid);
    default:return clearRichtung();
  }
  
  //turn the 3 LED on
  //Number[startPixel+lenkung_mid]=1;
  //Number[startPixel+lenkung_vor]=1;
  //Number[startPixel+lenkung_nach]=1;
  
  //set the 3 LED's colour
  //Pixel_Color[startPixel+lenkung_mid]=RICHTUNGFARBE;
  //Pixel_Color[startPixel+lenkung_vor]=RICHTUNGFARBE;
  //Pixel_Color[startPixel+lenkung_nach]=RICHTUNGFARBE;
}

//**************************************************************************************//
//clear richtung area of LED
//**************************************************************************************//
void Richtung::clearRichtung(void)
{
  for(int i=1;i<pixelLang*6;i++)
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

void Richtung::turn_on(int start)
{
  for(int i=0;i<pixelLang;i++)
  {
    Number[start+i+startPixel]=1;
  }
}
