#ifndef RICHTUNG_H
#define RICHTUNG_H

#include <Adafruit_NeoPixel.h>

#define RICHTUNGFARBE  pixels.Color(255, 255, 255);

//extern main value in to this file
extern Adafruit_NeoPixel pixels;
extern boolean Number[];
extern uint32_t Pixel_Color[];

//**************************************************************************************//
//Class for Richtung
//Writer: Hao
//Time: 07.06.2017
//**************************************************************************************//
class Richtung{
  public:
  //construction 
  Richtung(char v_startPixel,char v_pixelLang,char v_middlePixel);
  Richtung();
  ~Richtung();
  int grad;
  char startPixel;
  char pixelLang;
  char middlePixel;
  void set(int v_grad);
  void clearRichtung(void);
  private:
  int convert(int v_in);
};


#endif // RICHTUNG_H
