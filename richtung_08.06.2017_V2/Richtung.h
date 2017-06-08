#ifndef RICHTUNG_H
#define RICHTUNG_H


//ASICC CODE
//S   83
#define STRAIGHT            83
//L   76
#define STRAIGHT_LEFT       76
//R   82
#define STRAIGHT_RIGHT      82
//b   98
#define BACK                98
//l   108
#define BACK_LEFT           108     
//r   114
#define BACK_RIGHT          114


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
  Richtung(char v_startPixel,char v_pixelLang);
  Richtung();
  ~Richtung();
  int grad;
  char startPixel;
  char pixelLang;
  void set(char c_richtung);
  void clearRichtung(void);
  private:
  int convert(int v_in);
  void turn_on(int start);
};


#endif // RICHTUNG_H
