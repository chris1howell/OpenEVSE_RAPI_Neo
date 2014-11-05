#include <Adafruit_NeoPixel.h>

#define PIN 6
#define RAPI_BUFLEN 13

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);
int EVSE_STATE = 0;


class RAPI {
  int m_RAPIinByte; // RAPI byte being read in
  char m_RAPIinstr[RAPI_BUFLEN]; // RAPI byte being read in
  int m_RAPIstrCount; //RAPI string counter

public:
  RAPI();
  void Init();
  
  void flush() { 
    Serial.flush(); 
  }
  void getInput();
  uint8_t getInt();
};

RAPI g_RAPI;

RAPI::RAPI()
{
  m_RAPIstrCount = 0; 
}

void RAPI::Init()
{
 g_RAPI.flush();

}

uint8_t RAPI::getInt()
{
  uint8_t c;
  uint8_t num = 0;

  do {
    c = Serial.read(); // read the byte
    if ((c >= '0') && (c <= '9')) {
      num = (num * 10) + c - '0';
    }
  } while (c != 13);
  return num;
}

void RAPI::getInput()
{
  if(Serial.available()) { // if byte(s) are available to be read
    m_RAPIinByte = Serial.read(); // read the byte
    Serial.print(char(m_RAPIinByte));
    digitalWrite(13, HIGH);
    if(m_RAPIinByte != 13) {
      m_RAPIinstr[m_RAPIstrCount] = char(m_RAPIinByte);
      m_RAPIstrCount++;
    }
    if(m_RAPIinByte == 13) {
      if (strcmp(m_RAPIinstr, "$ST 1") == 0){ //if match 
        EVSE_STATE = 1;
           
      } 
      else if (strcmp(m_RAPIinstr, "$ST 2") == 0) { // string compare
        EVSE_STATE = 2;
      } 
      else if (strcmp(m_RAPIinstr, "$ST 3") == 0) { // string compare
        EVSE_STATE = 3;
      }
      else if (strcmp(m_RAPIinstr, "$ST 4") == 0) { // string compare
        EVSE_STATE = 4;
      }
      else if (strcmp(m_RAPIinstr, "$ST 5") == 0) { // string compare
        EVSE_STATE = 5;
      }
      else if (strcmp(m_RAPIinstr, "$ST 6") == 0) { // string compare
        EVSE_STATE = 6;
      }
      else if (strcmp(m_RAPIinstr, "$ST 7") == 0) { // string compare
        EVSE_STATE = 7;
      }
      g_RAPI.flush();
      m_RAPIstrCount = 0; // get ready for new input... reset strCount
      m_RAPIinByte = 0; // reset the inByte variable
      digitalWrite(13, LOW);
      for(int i = 0; m_RAPIinstr[i] != '\0'; i++) { // while the string does not have null
        m_RAPIinstr[i] = '\0'; // fill it with null to erase it
      }
    }
        
  
}
}


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  
{
 g_RAPI.getInput();
} 
   
      
         
  
  
  
  if(EVSE_STATE == 0) {
    colorWipe(strip.Color(16, 16, 16), 1); 
  
  }
  
  if (EVSE_STATE == 1) {
  colorWipe(strip.Color(0, 128, 0), 1); // Green
  //colorWipe(strip.Color(0, 64, 0), 1); // Green
  }
   if (EVSE_STATE == 2) {
  
  colorWipe(strip.Color(128, 128, 0), 1); // Yellow
  //colorWipe(strip.Color(64, 64, 0), 50); // Yellow
   }
   if (EVSE_STATE == 3) {
  
  colorWipe(strip.Color(0, 0, 128), 1); // Blue
  //colorWipe(strip.Color(0, 0, 64), 50); // Blue
   }
   if (EVSE_STATE > 3) {
  
  //colorWipe(strip.Color(255, 0, 0), 100); // Red
  colorWipe(strip.Color(64, 0, 0), 1); // Red
   }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
