
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif



// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN_M            4
#define PIN_R            5
#define PIN_S            6
#define PIN_V            7

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS_R      30
#define NUMPIXELS_S      24
#define NUMPIXELS_V      20
#define NUMPIXELS_M      40

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels_M = Adafruit_NeoPixel(NUMPIXELS_M, PIN_M, NEO_GRB + NEO_KHZ800); // Maiskolben
Adafruit_NeoPixel pixels_R = Adafruit_NeoPixel(NUMPIXELS_R, PIN_R, NEO_GRB + NEO_KHZ800); // Richtungsanzeige
Adafruit_NeoPixel pixels_S = Adafruit_NeoPixel(NUMPIXELS_S, PIN_S, NEO_GRB + NEO_KHZ800); // Statusanzeige
Adafruit_NeoPixel pixels_V = Adafruit_NeoPixel(NUMPIXELS_V, PIN_V, NEO_GRB + NEO_KHZ800); // Geschwindigkeitsanzeige

//Algorithmus zur Abfrage der seriellen Daten aus dem Pufferspeicher

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels_M.begin(); // This initializes the NeoPixel library.
  pixels_M.setBrightness(150); //Limits the maximum brightness of the LEDs
  
  pixels_R.begin();
  pixels_R.setBrightness(150);

  pixels_S.begin();
  pixels_S.setBrightness(150);
  
  pixels_V.begin(); 
  pixels_V.setBrightness(150);
  
// Serielle Kommunikation
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void stAnzeige(char input);// Prototyp Statusanzeige
void GesAnzeige(char v);//Prototyp Geschwindigkeitsanzeige

//***********************************RICHTUNG************************************************//
//ASICC CODE
//S   83
#define STRAIGHT            'S'
//L   76
#define STRAIGHT_LEFT       'L'
//R   82
#define STRAIGHT_RIGHT      'R'
//b   98
#define BACK                'b'
//l   108
#define BACK_LEFT           'l'     
//r   114
#define BACK_RIGHT          'r'

#define RICHTUNGFARBE  pixels_R.Color(255, 255, 255)
void RichtungAnzeige(char c_richtung);
boolean ri_Number[NUMPIXELS_R];
void turn_on(int start,int wide);
//***********************************RICHTUNG_END************************************************//


void loop() {
  if (Serial.available() > 0){ // Prüfen, ob zeichen im Pufferspeicher liegen
    char strzeichen;
    do{
      strzeichen = Serial.read(); //Zeichen auslesen, bis ein 'R', 'S' oder 'V' im Pufferspeicher liegen
    }while(strzeichen != 'R' && strzeichen != 'S' && strzeichen != 'V');
    Serial.print(strzeichen);
    delay(10);
    if (Serial.available() > 0){
      char verarbeitung = Serial.read(); //Auslesen des Werts, der an die Funktion übergeben werden soll
      Serial.print(verarbeitung);
      switch (strzeichen){
        case 'R': RichtungAnzeige(verarbeitung);//Funktionsaufrauf Richtung
          break;
        case 'S': stAnezige(verarbeitung);//Serial.print(verarbeitung);//Funktionsaufruf Status
          break;
        case 'V': GesAnzeige(verarbeitung);
          break;
        default: Serial.print('F');
          break;
      }
    }
  }
}

// Funktionen
// Statusanzeige
void stAnezige(char input){
  switch(input){
//Beim einschalten
case 'E':
  for(int i=0;i<NUMPIXELS_S;i++){
    pixels_S.setPixelColor(i, pixels_S.Color(0,0,255)); // Moderately bright blue color.
  }
  break;

//Fehler
case 'F':
  for(int i=0;i<NUMPIXELS_S;i++){
    pixels_S.setPixelColor(i, pixels_S.Color(255,100,0)); // Moderately bright yellow color.
  }
  break;

//standby
case 'S':
  for(int i=0;i<NUMPIXELS_S;i++){
    pixels_S.setPixelColor(i, pixels_S.Color(255,155,0)); // Moderately bright yellow color.
  }
  break;

//Unkraut erkannt
case 'U':
  for(int i=0;i<NUMPIXELS_S;i++){
    pixels_S.setPixelColor(i, pixels_S.Color(255,0,0)); // Moderately bright red color.
  }
  break;

// Alle LEDs ausschalten

case 'a':for(int i = 0; i<NUMPIXELS_S;i++){
      pixels_S.setPixelColor(i,0,0,0);
    }
  break;
//Manuel gefahren
case 'M':
  for(int i=0;i<NUMPIXELS_S;i++){
    pixels_S.setPixelColor(i, pixels_S.Color(255,0,255)); // Moderately bright purple color.
  }
  break;

default:
  for(int i=0;i<NUMPIXELS_S;i++){
    pixels_S.setPixelColor(i, pixels_S.Color(0,255,0)); // Moderately bright green color.
  }
  break;
}
pixels_S.show();
}

// Geschwindigkeitsanzeige
void GesAnzeige(char v){
  //Farben bei verschiedenen Geschwindigkeiten
  uint32_t v0 = pixels_V.Color(50,255,0), v1 = pixels_V.Color(100,255,0), v2 = pixels_V.Color(150,255,0), v3 = pixels_V.Color(200,255,0), v4 = pixels_V.Color(255,255,0);
  uint32_t v5 = pixels_V.Color(255,200,0), v6 = pixels_V.Color(255,150,0), v7 =pixels_V.Color(255,100,0), v8 =pixels_V.Color(255,50,0), v9 =pixels_V.Color(255,0,0);

    //Beginn der Funtion
    //Alle LEDs ausschalten
    for(int i = 0; i<NUMPIXELS_V;i++){
      pixels_V.setPixelColor(i,0,0,0);
    }

    // Von der Geschwindigkeit abhängig LEDs ansteuern
    // Von char 'v' an wird jede einelne LED eingeschaltet
    switch(v){
      case '9': pixels_V.setPixelColor(9,v9);
                pixels_V.setPixelColor(10,v9);
      case '8': pixels_V.setPixelColor(8,v8);
                pixels_V.setPixelColor(11,v8);
      case '7': pixels_V.setPixelColor(7,v7);
                pixels_V.setPixelColor(12,v7);
      case '6': pixels_V.setPixelColor(6,v6);
                pixels_V.setPixelColor(13,v6);
      case '5': pixels_V.setPixelColor(5,v5);
                pixels_V.setPixelColor(14,v5);
      case '4': pixels_V.setPixelColor(4,v4);
                pixels_V.setPixelColor(15,v4);
      case '3': pixels_V.setPixelColor(3,v3);
                pixels_V.setPixelColor(16,v3);
      case '2': pixels_V.setPixelColor(2,v2);
                pixels_V.setPixelColor(17,v2);
      case '1': pixels_V.setPixelColor(1,v1);
                pixels_V.setPixelColor(18,v1);
      case '0': pixels_V.setPixelColor(0,v0);
                pixels_V.setPixelColor(19,v0);
          break;
      default: break;
    }
    pixels_V.show(); //Erst hier wird das Signal an die LEDs gesendet bzw. der Befehl ausgeführt
}

void RichtungAnzeige(char c_richtung)
{
  for(int i=0;i<NUMPIXELS_R;i++)
  {
    ri_Number[i]=false;
  }
  switch(c_richtung)
  {
    case STRAIGHT:turn_on(0,5);
    case STRAIGHT_LEFT:turn_on(25,5);
    case STRAIGHT_RIGHT:turn_on(5,5);
    case BACK:turn_on(15,5);
    case BACK_LEFT:turn_on(20,5);
    case BACK_RIGHT:turn_on(10,5);
    default:break;
  }
  
  for(int i=0;i<NUMPIXELS_R;i++)
  {
    if(ri_Number[i]==true)
    {
      pixels_R.setPixelColor(i, RICHTUNGFARBE); 
    }
  }
}

void turn_on(int start,int wide)
{
  for(int i=0;i<wide;i++)
  {
    ri_Number[start+i]=true;
  }
}
